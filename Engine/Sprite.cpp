#include "Camera.h"
#include "CallDef.h"
#include "Sprite.h"

using namespace DirectX;

Sprite::Sprite() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), index_(0)
{
}

//�f�X�g���N�^��RELEASE���Ăяo��
Sprite::~Sprite()
{
	Release();
}


HRESULT Sprite::Initialize(LPCWSTR filename)
{
	HRESULT hr;

	// ���_���
	VERTEX vertices[] =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i����j
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E��j
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�E���j
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },	// �l�p�`�̒��_�i�����j
	};

	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	HR_FAILED(hr, L"�o�b�t�@�̍쐬�Ɏ��s���܂���");

	//�C���f�b�N�X���
	int index[] = { 0,1,2, 0,2,3 };
	index_ = (int)std::size(index);

	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.ByteWidth = sizeof(index);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	HR_FAILED(hr, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���");

	hr = ConBuf(filename);
	return hr;
}

HRESULT Sprite::ConBuf(LPCWSTR filename) {
	HRESULT hr;
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	HR_FAILED(hr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���");

	pTexture_ = new Texture;
	hr = Load(filename);

	return S_OK;
}

HRESULT Sprite::Load(LPCWSTR filename) {
	HRESULT hr;
	//�e�N�X�`�������[�h
	hr = pTexture_->Load(filename);
	return hr;
}

void Sprite::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_2D);

	//XMMATRIX Size = ((float)pTexture_->GetFileSize()->FileWidth,pTexture_->GetFileSize()->FileHeight,0.0f,0.0f);
	CONSTANT_BUFFER cb;

	//�s��̌v�Z�����āA���[���h�s���Ԃ�
	transform.Calclation();
	cb.matW = XMMatrixTranspose(transform.GetWorldMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
	Direct3D::pContext->DrawIndexed(index_, 0, 0);
}

void Sprite::Release()
{
	SAFE_RELEASE(pTexture_);
	SAFE_DELETE(pTexture_);	//new�����̂�DELETE���s��
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
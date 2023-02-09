#include "AStar2D.h"
#include "Engine/CallDef.h"

AStar2D::AStar2D(short size) : MapSize_(size), Start_(), Goal_(), totalMove_(0), ppCost_()
{
	Unexplored_.clear();
	Explored_.clear();
	Routelist_.clear();
	MapData_.clear();
}

AStar2D::~AStar2D()
{
	for (int i = 0; i < MapSize_; i++)
	{
		SAFE_DELETE_ARRAY(ppCost_);
	}
	SAFE_DELETE_ARRAY(ppCost_);
	Unexplored_.clear();
	Explored_.clear();
	Routelist_.clear();
	MapData_.clear();
}

void AStar2D::SetStart(std::pair<int, int> start)
{
	Start_ = start;
	ppCost_[Start_.first][Start_.second] = 0;
}

void AStar2D::SetGoal(std::pair<int, int> goal)
{
	Goal_ = goal;
}

void AStar2D::SetData(std::vector<std::vector<char>> MapData)
{
	for (int i = 0; i < MapSize_; i++)
	{
		MapData_.push_back(MapData.at(i));
	}
	//�e�f�[�^�ɏ����l��ݒ�
	for (int x = 0; x < MapSize_; x++)
	{
		for (int z = 0; z < MapSize_; z++)
		{
			ppCost_[x][z] = CostMax_;
			if (MapData_[x][z] == 1)
			{
				ppCost_[x][z] = -1;
			}
			Unexplored_.push_back({ x,z });
		}
	}
}

float AStar2D::GetDistance(std::pair<int, int> pos1)
{
	float ans = (float)sqrt(pow(((double)pos1.first - (double)Goal_.first), 2) + pow(((double)pos1.second - (double)Goal_.second), 2));
	return ans;
}

bool AStar2D::Passable(int X, int Z)
{
	if (X >= 0 && Z >= 0)
	if (MapData_.at(X).at(Z) == 0)
	{
		return true;
	}
	return false;
}

void AStar2D::Initialize()
{
	ppCost_ = new float* [MapSize_];
	//ppMapData_ = new char* [MapSize_];
	for (int i = 0; i < MapSize_; i++)
	{
		ppCost_[i] = new float[MapSize_];
		//ppMapData_[i] = new char[MapSize_];
	}
}

void AStar2D::Adjacent(Move next)
{
	totalMove_++;
	bool IsSearched = false;
	for (Move Dir : Direction)	//���݈ʒu�ɗׂ荇���Ă���4�n�_�ɃR�X�g������U���Ă���
	{
		int nextW = next.moveLR + Dir.moveLR;
		int nextH = next.moveHL + Dir.moveHL;
		if (Passable(nextW, nextH))
		{
			if (ppCost_[nextW][nextH] == CostMax_)
			{
				std::pair<int, int> nextpos = std::pair<int, int>(nextW, nextH);

				int movesX = Start_.first - (int)nextpos.first;
				int movesZ = Start_.second - (int)nextpos.second;
				if (movesX < 0)
				{
					movesX = -movesX;
				}
				if (movesZ < 0)
				{
					movesZ = -movesZ;
				}
				int Moves = movesX + movesZ;
				ppCost_[nextW][nextH] = GetDistance(nextpos) + totalMove_;

				//�S�[���Ȃ�ΒT���I��
				if (GetDistance(nextpos) < 0.5f)
				{
					return;
				}
				IsSearched = true;
			}
		}
	}

	Unexplored_.remove({ next.moveLR, next.moveHL });
	Explored_.push_back({ next.moveLR, next.moveHL });
	std::pair<float, std::pair<int, int>> Min;
	Min.first = CostMax_;
	Min.second = std::pair<int, int>(0, 0);

	//4�_�̏��Ȃ��Ƃ�1�ȏ�T�����ł����ꍇ�A���̒��ŃR�X�g���ł��������ʒu�Ɉړ�����
	if (IsSearched)
	{
		for (auto itr = Unexplored_.begin(); itr != Unexplored_.end(); itr++)
		{
			if (ppCost_[(*itr).first][(*itr).second] < Min.first && ppCost_[(*itr).first][(*itr).second] > 0)
			{
				Min.first = ppCost_[(*itr).first][(*itr).second];
				Min.second = std::pair<int, int>((*itr).first, (*itr).second);
			}
		}
	}
	//��������ł��Ȃ������ꍇ�A���݈ʒu�̃R�X�g�̎��ɏ������R�X�g�����ʒu�Ɉړ�����
	else
	{
		float Died = ppCost_[next.moveLR][next.moveHL];

		for (auto itr = Unexplored_.begin(); itr != Unexplored_.end(); itr++)
		{
			if (ppCost_[(*itr).first][(*itr).second] < Min.first && ppCost_[(*itr).first][(*itr).second] > Died)
			{
				Min.first = ppCost_[(*itr).first][(*itr).second];
				Min.second = std::pair<int, int>((*itr).first, (*itr).second);
			}
		}
	}

	if (Min.first != CostMax_)
	{
		Adjacent({ (int)Min.second.first, (int)Min.second.second });
	}
}

void AStar2D::Route(std::pair<int, int> pos)
{
	std::pair<int, int> next = pos;
	float necos = CostMax_;

	for (Move Dir : Direction)
	{
		int nextW = pos.first + Dir.moveLR;
		int nextH = pos.second + Dir.moveHL;

		if (std::pair<int, int>(nextW, nextH) == Start_)
		{
			return;
		}

		//�ׂ荇���v�f�ōł��R�X�g���Ⴂ�v�f��I������
		if(nextW >= 0 && nextH >= 0)
		if (ppCost_[nextW][nextH] < necos && ppCost_[nextW][nextH] >= 0)
		{
			necos = ppCost_[nextW][nextH];
			next = std::pair<int, int>(nextW, nextH);
		}
	}
	Routelist_.push_back(next);
	Route(next);
}

void AStar2D::GetRoute(std::list<std::pair<int, int>>& Routelist)
{
	memcpy_s(&Routelist, std::size(Routelist_), &Routelist_, std::size(Routelist_));
}
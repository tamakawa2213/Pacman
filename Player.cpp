#include "Player.h"
#include "Engine/Input.h"
#include "PlayerState.h"

void Player::Input()
{
    PlayerState::SetPlayerPosition(transform_.position_);
    PlayerState::SetPlayerPosition(intPosX, intPosZ);

    //����awsd�Ə㉺���E�L�[�̂ǂ���ł���
   if (Input::IsKey(DIK_UP) || Input::IsKey(DIK_W))
   {
       GoAbove();
   }
   if (Input::IsKey(DIK_DOWN) || Input::IsKey(DIK_S))
   {
       GoUnder();
      
   }
   if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
   {
       GoRight();
       
   }
   if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
   {
       GoLeft();
   }
}

Player::Player(GameObject* parent)
	:Character(parent, "Player")
{
    PlayerState::SetPlayerPosition(transform_.position_);
}

Player::~Player()
{
}

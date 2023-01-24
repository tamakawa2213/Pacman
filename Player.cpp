#include "Player.h"
#include "Engine/Input.h"
#include "PlayerState.h"

void Player::Input()
{
    PlayerState::SetPlayerPosition(transform_.position_);

    //操作awsdと上下左右キーのどちらでも可
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
}

Player::~Player()
{
}

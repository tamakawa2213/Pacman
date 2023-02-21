#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "PlayerState.h"

void Player::Input()
{
    PlayerState::SetPlayerPosition(transform_.position_);
    PlayerState::SetPlayerPosition(intPosX, intPosZ);

    //ëÄçÏawsdÇ∆è„â∫ç∂âEÉLÅ[ÇÃÇ«ÇøÇÁÇ≈Ç‡â¬
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
    MLoad(hModel_, "Assets\\player.fbx");
}

Player::~Player()
{
}

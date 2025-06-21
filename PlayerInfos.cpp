#include "PlayerInfos.h"

PlayerInfos* PlayerInfos::instance = nullptr;

PlayerInfos::PlayerInfos():
	mMoney{ 25 },
	mLife{ 100 },
	mHasWin{ false }
{
	if (instance == nullptr)
	{
		instance = this;
	}
}

PlayerInfos::~PlayerInfos()
{
}

PlayerInfos* PlayerInfos::GetInstance()
{
	return instance;
}

void PlayerInfos::Reset()
{
	mMoney = 25;
	mLife = 100;
	mHasWin = false;
}

int PlayerInfos::GetMoney() const
{
	return mMoney;
}

int PlayerInfos::GetLife() const
{
	return mLife;
}

void PlayerInfos::AddMoney(int money)
{
	mMoney += money;
}

void PlayerInfos::AddLife(int life)
{
	mLife += life;
}

void PlayerInfos::SetMoney(int money)
{
	mMoney = money;
}

void PlayerInfos::SetLife(int life)
{
	mLife = life;
}

void PlayerInfos::SetHasWin(bool hasWin)
{
	mHasWin = hasWin;
}

bool PlayerInfos::GetHasWin() const
{
	return mHasWin;
}





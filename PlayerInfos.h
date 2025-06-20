#pragma once

#include "AssetBank.h"

class PlayerInfos
{
private :
	int mMoney;
	int mLife;

public :
	PlayerInfos();
	~PlayerInfos();

	static PlayerInfos* instance;
	static PlayerInfos* GetInstance();

	int GetMoney() const;
	int GetLife() const;

	void AddMoney(int money);
	void AddLife(int life);

	void SetMoney(int money);
	void SetLife(int life);
};


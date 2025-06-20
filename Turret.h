#pragma once

#include "BulletBank.h"

class Turret
{
private:
	Vector2 mPosition;
	short mType;  // 0 = ground, 1 = air
	short mPower; // 0, 1
	float mDamage;
	float mFirerate;
	float mCooldown;
	float mRange;

	Vector2 mSize;
	float mRotation;

	EnemySpawner* mpEnemySpawner;
	BulletBank* mpBulletBank;

public:
	Turret();
	Turret(short type, short power, Vector2 position, EnemySpawner* enemySpawner, BulletBank* bulletBank , Vector2 size);
	~Turret();

	void Update();
	void Draw() const;

	short GetType() const;
	short GetPower() const;
	Vector2 GetPosition() const;
	Vector2 GetSize() const;


};


#pragma once
#include "AssetBank.h"

class Bullet
{
private:
	short mType;
	Vector2 mPosition;
	Vector2 mSize;
	
	Vector2 mDirection;
	float mSpeed;

	float mDamage;

	float mLifespan;

public:
	Bullet();
	Bullet(short type, Vector2 position, Vector2 direction, float speed, float damage, float lifespan);
	~Bullet();

	void Update();
	void Draw() const;

	float GetLifetime() const;
	float GetRadius() const;
	Vector2 GetPosition() const;
	short GetType() const;
	float GetDamage() const;
};


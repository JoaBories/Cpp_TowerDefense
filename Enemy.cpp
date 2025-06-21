#include "enemy.h"

Enemy::Enemy():
	mType{ 0 },
	mPower{ 0 },
	mCurrentWaypoint{ 0 },
	mHealth{ 0 },
	mSpeed{ 0 },
	mPosition{ 0, 0 },
	mWaypoints{ },
	mRotation{ 0 },
	mSize{ 0, 0 },
	mIsWaitingForKill{ false },
	mGotCastle{ false }
{
}

Enemy::Enemy(Vector2 position, int type, int power, vector<Vector2> waypoints):
	mType{ type },
	mPower{ power }, 
	mCurrentWaypoint{ 1 },
	mHealth{ 0 }, 
	mSpeed{ 0 }, 
	mPosition{ position },
	mWaypoints{ waypoints },
	mRotation{ 0 },
	mSize{ 40, 40 },
	mIsWaitingForKill{ false },
	mGotCastle{ false }
{
	switch (type)
	{
	case 0:
		switch (power)
		{
		case 0:
			mHealth = 100;
			mSpeed = 30;
			break;

		case 1:
			mHealth = 250;
			mSpeed = 20;
			break;
		}
		break;

	case 1:
		switch (power)
		{
		case 0:
			mHealth = 100;
			mSpeed = 30;
			break;

		case 1:
			mHealth = 100;
			mSpeed = 30;
			break;
		}
		break;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Vector2 target = mWaypoints[mCurrentWaypoint];

	Vector2 distance = Utils::Vector2Substract(target, mPosition);
	Vector2 direction = Utils::Normalize(distance);

	mPosition = Utils::Vector2Add(mPosition, Utils::Vector2Scale(direction, mSpeed * GetFrameTime()));

	direction = Utils::Vector2Scale(direction, mSpeed );

	if (Utils::SqrLenght(distance) <= 0.5f) 
	{
		mCurrentWaypoint++;

		if (mCurrentWaypoint >= mWaypoints.size())
		{
			mIsWaitingForKill = true;
			mGotCastle = true;
		}
	}

	mRotation = Utils::RotFromVector2(direction);
}

void Enemy::Draw() const
{
	int index = mType + mPower;
	Texture* text = AssetBank::GetInstance()->GetEnemyTexture(index);

	Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	
	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, mRotation, WHITE);
	//DrawCircleV(mPosition, GetRadius(), {255,0,0,100});
}

void Enemy::TakeDamage(float damage)
{
	mHealth -= damage;

	if (mHealth <= 0)
	{
		mIsWaitingForKill = true;
	}
}

bool Enemy::IsWaitingForKill() const
{
	return mIsWaitingForKill;
}

bool Enemy::GotCastle() const
{
	return mGotCastle;
}

Vector2 Enemy::GetPosition() const
{
	return mPosition;
}

float Enemy::GetRadius() const
{
	return mSize.x * 0.5f;
}

int Enemy::GetType() const
{
	return mType;
}

int Enemy::GetPower() const
{
	return mPower;
}

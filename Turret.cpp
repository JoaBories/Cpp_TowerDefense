#include "Turret.h"

Turret::Turret() :
	mPosition{ 0,0 },
	mType{ 0 },
	mPower{ 0 },
	mDamage{ 0 },
	mFirerate{ 0 },
	mCooldown{ 0 },
	mRange{ 0 },
	mSize{ 0,0 },
	mRotation{ 0 },
	mpEnemySpawner{ nullptr },
	mpBulletBank{ nullptr }
{
}

Turret::Turret(short type, short power, Vector2 position, EnemySpawner* enemySpawner, BulletBank* bulletBank, Vector2 size) :
	mPosition{ position },
	mType{ type },
	mPower{ power },
	mDamage{ 0 },
	mFirerate{ 0 },
	mCooldown{ 0 },
	mRange{ 0 },
	mpEnemySpawner{ enemySpawner },
	mpBulletBank{ bulletBank },
	mSize{ size },
	mRotation{ 0 }
{
	switch (type)
	{
	case 0:
		switch (power)
		{
		case 0:
			mDamage = 25;
			mFirerate = 1;
			mRange = 300;
			break;

		case 1:
			mDamage = 50;
			mFirerate = 2;
			mRange = 450;
			break;
		}
		break;

	case 1:
		switch (power)
		{
		case 0:
			mDamage = 25;
			mFirerate = 0.5f;
			mRange = 400;
			break;

		case 1:
			mDamage = 50;
			mFirerate = 1;
			mRange = 600;
			break;
		}
		break;
	}
}

Turret::~Turret()
{
}

void Turret::Update()
{
	mCooldown -= GetFrameTime();

	Enemy* pClosestEnemy = nullptr;
	float squaredClosestEnemyDistance = FLT_MAX;
	vector<Enemy*> enemies = (mType == 0) ? mpEnemySpawner->GetGroundsEnemies() : mpEnemySpawner->GetAirEnemies();

	for (Enemy* enemy : enemies)
	{
		float squaredDist = Utils::SqrLenght(Utils::Vector2Substract(mPosition, enemy->GetPosition()));

		if (squaredDist <= mRange * mRange)
		{
			if (squaredDist < squaredClosestEnemyDistance) 
			{
				pClosestEnemy = enemy;
				squaredClosestEnemyDistance = squaredDist;
			}
		}
	}

	if (pClosestEnemy != nullptr)
	{
		Vector2 direction = Utils::Normalize(Utils::Vector2Substract(pClosestEnemy->GetPosition(), mPosition));

		mRotation = Utils::RotFromVector2(direction);

		if (mCooldown <= 0)
		{
			mpBulletBank->SpawnBullet(mType, mPosition, direction, mDamage);
			mCooldown = 1 / mFirerate;
		}
	}
}

void Turret::Draw() const
{
	int index = mType + mPower;
	Texture* text = AssetBank::GetInstance()->GetTurretTexture(index);

	Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };

	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, mRotation, WHITE);
}

short Turret::GetType() const
{
	return mType;
}

short Turret::GetPower() const
{
	return mPower;
}

Vector2 Turret::GetPosition() const
{
	return mPosition;
}

Vector2 Turret::GetSize() const
{
	return mSize;
}

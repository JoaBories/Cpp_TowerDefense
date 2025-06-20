#include "BulletBank.h"

BulletBank::BulletBank():
	mBullets{ },
	mpEnemySpawner{ nullptr }
{
}

BulletBank::BulletBank(EnemySpawner* enemySpawner) :
	mBullets{ },
	mpEnemySpawner{ enemySpawner }
{
}

BulletBank::~BulletBank()
{
}

void BulletBank::Update()
{
	for (size_t i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->Update();
		
		if (mBullets[i]->GetLifetime() <= 0)
		{
			delete mBullets[i];
			mBullets.erase(mBullets.begin() + i);
			i--;
			continue;
		}

		vector<Enemy*> enemies = (mBullets[i]->GetType() == 0) ? mpEnemySpawner->GetGroundsEnemies() : mpEnemySpawner->GetAirEnemies();

		float collisionRadius = 0;

		if (enemies.size() > 0)
		{
			collisionRadius = mBullets[i]->GetRadius() + enemies[0]->GetRadius();
		}

		for (size_t j = 0; j < enemies.size(); j++)
		{
			float squaredDist = Utils::SqrLenght(Utils::Vector2Substract(mBullets[i]->GetPosition(), enemies[j]->GetPosition()));
			if (squaredDist <= collisionRadius * collisionRadius)
			{
				enemies[j]->TakeDamage(mBullets[i]->GetDamage());

				delete mBullets[i];
				mBullets.erase(mBullets.begin() + i);
				i--;
				break;
			}
		}
	}
}

void BulletBank::Draw() const
{
	for (Bullet* bullet : mBullets)
	{
		bullet->Draw();
	}
}

void BulletBank::SpawnBullet(short type, Vector2 position, Vector2 direction, float damage)
{
	mBullets.push_back(new Bullet(type, position, direction, 500, damage, 2));
}

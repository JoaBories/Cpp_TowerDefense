#include "EnemySpawner.h"

int EnemySpawner::EnemyCount = 0;

EnemySpawner::EnemySpawner() :
	mSpawnRate{ 0 },
	mCooldown{ 0 },
	mCurrentWaveIndex{ 0 },
	mCurrentGroupIndex{ 0 },
	mCurrentEnemyIndex{ 0 },
	mWaves{ },
	mTerrain{ nullptr },
	mGroundEnemies{ },
	mAirEnemies{ },
	mStopSpawning{ false }
{
}

EnemySpawner::EnemySpawner(Terrain* terrain) :
	mSpawnRate{ 0 },
	mCooldown{ 5 },
	mCurrentWaveIndex{ 0 },
	mCurrentGroupIndex{ 0 },
	mCurrentEnemyIndex{ 0 },
	mTerrain{ terrain },
	mGroundEnemies{ },
	mAirEnemies{ },
	mStopSpawning{ false }
{
	EnemyData enemy1 = { 0,0 };
	EnemyData enemy2 = { 0,1 };
	EnemyData enemy3 = { 1,0 };
	EnemyData enemy4 = { 1,1 };

	mWaves.push_back({ { {enemy1, 10} }, 0.5f, 10 });
	mWaves.push_back({ { {enemy1, 10}, {enemy2, 2} }, 0.75f, 10 });
	mWaves.push_back({ { {enemy1, 10}, {enemy2, 2}, {enemy1, 10}, {enemy2, 2} }, 1, 20 });
	mWaves.push_back({ { {enemy2, 10}, {enemy1, 20}, {enemy2, 10} }, 1.5f, 20 });
	mWaves.push_back({ { {enemy2, 20}, {enemy1, 20} }, 2, 20 });
	mWaves.push_back({ { {enemy2, 25}, {enemy1, 25} }, 3, 20 });
	mWaves.push_back({ { {enemy2, 40}, {enemy1, 40} }, 3, 20 });
	mWaves.push_back({ { {enemy2, 40}, {enemy1, 40} }, 10, 20 });
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Update()
{
	mCooldown -= GetFrameTime();

	if (mCooldown <= 0 && !mStopSpawning)
	{
		EnemyData currentEnemyData = mWaves[mCurrentWaveIndex].enemies[mCurrentGroupIndex].enemyType;
		SpawnEnemy(currentEnemyData.type, currentEnemyData.power);

		mCooldown = 1 / mWaves[mCurrentWaveIndex].spawnRate;
		
		mCurrentEnemyIndex++;

		if (mCurrentEnemyIndex >= mWaves[mCurrentWaveIndex].enemies[mCurrentGroupIndex].number)
		{
			mCurrentGroupIndex++;
			mCurrentEnemyIndex = 0;

			if (mCurrentGroupIndex >= mWaves[mCurrentWaveIndex].enemies.size())
			{
				mCurrentWaveIndex++;
				mCurrentGroupIndex = 0;

				if (mCurrentWaveIndex >= mWaves.size())
				{
					mStopSpawning = true;
					return;
				}

				mCooldown = mWaves[mCurrentWaveIndex].cooldown;
			}
		}
	}
	else if (mStopSpawning)
	{
		if (EnemyCount == 0)
		{
			PlayerInfos::GetInstance()->SetHasWin(true);
		}
	}

	for (size_t i = 0; i < mGroundEnemies.size(); i++)
	{
		mGroundEnemies[i]->Update();

		if (mGroundEnemies[i]->IsWaitingForKill())
		{
			int enemyPower = 1 + 0 + (mGroundEnemies[i]->GetPower()+1) * 2;
			if (mGroundEnemies[i]->GotCastle())
			{
				PlayerInfos::GetInstance()->AddLife(-enemyPower);
			}
			PlayerInfos::GetInstance()->AddMoney(2*enemyPower);

			delete mGroundEnemies[i];
			mGroundEnemies.erase(mGroundEnemies.begin() + i);
			i--;
			EnemyCount--;
		}
	}

	for (size_t i = 0; i < mAirEnemies.size(); i++)
	{
		mAirEnemies[i]->Update();

		if (mAirEnemies[i]->IsWaitingForKill())
		{
			int enemyPower = 1 + 1 + (mAirEnemies[i]->GetPower()) * 2;
			if (mAirEnemies[i]->GotCastle())
			{
				PlayerInfos::GetInstance()->AddLife(-enemyPower);
			}
			PlayerInfos::GetInstance()->AddMoney(2*enemyPower);

			delete mAirEnemies[i];
			mAirEnemies.erase(mAirEnemies.begin() + i);
			i--;
			EnemyCount--;
		}
	}
}

void EnemySpawner::Draw() const
{
	for (Enemy* enemy : mGroundEnemies)
	{
		enemy->Draw();
	}
}

void EnemySpawner::SpawnEnemy(int type, int power)
{
	if (type == 0)
	{
		mGroundEnemies.push_back(new Enemy(mTerrain->GetObjects()->GetEnemyPath()[0], type, power, mTerrain->GetObjects()->GetEnemyPath()));
	}
	else
	{
		mAirEnemies.push_back(new Enemy(mTerrain->GetObjects()->GetEnemyPath()[0], type, power, mTerrain->GetObjects()->GetEnemyPath()));
	}
	EnemyCount++;
}

vector<Enemy*> EnemySpawner::GetGroundsEnemies() const
{
	return mGroundEnemies;
}

vector<Enemy*> EnemySpawner::GetAirEnemies() const
{
	return mAirEnemies;
}

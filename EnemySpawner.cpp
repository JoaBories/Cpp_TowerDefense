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
	mCooldown{ 0 },
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

	mWaves.push_back({ { {enemy1, 10} }, 1, 20 });
	mWaves.push_back({ { {enemy1, 10}, {enemy2, 2} }, 1, 20 });
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
					//win
					mStopSpawning = true;
					return;
				}

				mCooldown = mWaves[mCurrentWaveIndex].cooldown;
			}
		}
	}

	for (size_t i = 0; i < mGroundEnemies.size(); i++)
	{
		mGroundEnemies[i]->Update();

		if (mGroundEnemies[i]->IsWaitingForKill())
		{
			if (mGroundEnemies[i]->GotCastle())
			{
				//attack castle
			}

			delete mGroundEnemies[i];
			mGroundEnemies.erase(mGroundEnemies.begin() + i);
			i--;
		}
	}

	for (size_t i = 0; i < mAirEnemies.size(); i++)
	{
		mAirEnemies[i]->Update();

		if (mAirEnemies[i]->IsWaitingForKill())
		{
			if (mAirEnemies[i]->GotCastle())
			{
				//attack castle
			}

			delete mAirEnemies[i];
			mAirEnemies.erase(mAirEnemies.begin() + i);
			i--;
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
	if (/*type == 1*/ true)
	{
		mGroundEnemies.push_back(new Enemy(mTerrain->GetObjects()->GetEnemyPath()[0], type, power, 100, mTerrain->GetObjects()->GetEnemyPath(), 50));
		EnemyCount++;
	}
	cout << mGroundEnemies.size() << " enemies spawned." << endl;
}

#pragma once

#include "Enemy.h"
#include "Terrain.h"


struct EnemyData
{
	int type;
	int power;
};

struct EnemyGroup
{
	EnemyData enemyType;
	int number;
};

struct EnemyWave 
{
	vector<EnemyGroup> enemies;
	float spawnRate;
	float cooldown;
};

class EnemySpawner
{
private :
	int mSpawnRate;
	float mCooldown;

	int mCurrentWaveIndex;
	int mCurrentGroupIndex;
	int mCurrentEnemyIndex;
	vector<EnemyWave> mWaves;

	Terrain* mTerrain;

	vector<Enemy*> mGroundEnemies;
	vector<Enemy*> mAirEnemies;

	bool mStopSpawning;
	
public :
	static int EnemyCount;

	EnemySpawner();
	EnemySpawner(Terrain* terrain);
	~EnemySpawner();

	void Update();
	void Draw() const;

	void SpawnEnemy(int type, int power);

};


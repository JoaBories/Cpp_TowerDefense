#pragma once

#include "Bullet.h"
#include "EnemySpawner.h"

class BulletBank
{
private:
	vector<Bullet*> mBullets;
	EnemySpawner* mpEnemySpawner;

public:
	BulletBank();
	BulletBank(EnemySpawner* enemySpawner);
	~BulletBank();

	void Update();
	void Draw() const;

	void SpawnBullet(short type, Vector2 position, Vector2 direction, float damage);

};


#pragma once
#include <string>
#include "TileCursor.h"
#include "EnemySpawner.h"
#include "Turret.h"

enum GameState
{
	StartState,
	EditorState,
	DefendState,
	FinishState
};

class Engine
{
private :
	TileCursor* mTileCursor;
	Terrain* mTerrain;

	GameState mGameState;

	Color mOrange;

	EnemySpawner* mEnemySpawner;
	BulletBank* mBulletBank;
	vector<Turret*> mTurrets;

	void StartGame();
	void MouseCheckUpdate();
	void MouseCheckDraw();
	void DrawGameUI() const;

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};


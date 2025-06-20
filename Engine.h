#pragma once
#include <string>
#include "TileCursor.h"
#include "EnemySpawner.h"

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

	void StartGame();

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};


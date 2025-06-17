#pragma once
#include <string>
#include "TileCursor.h"

enum GameState
{
	StartState,
	EditorState,
	RaceState,
	FinishState
};

class Engine
{
private :
	TileCursor* mTileCursor;
	Terrain* mTerrain;

	GameState mGameState;

	Color mOrange;

	void StartGame();

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};


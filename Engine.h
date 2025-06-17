#pragma once
#include <string>
#include "Track.h"
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
	Terrain* mTrack;

	GameState mGameState;

	Color mOrange;

	void StartRace();

public :
	Engine();
	~Engine();

	void Init();
	void Update();
	void Draw();
};


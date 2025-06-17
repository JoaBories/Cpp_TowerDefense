#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

#include "TurretBase.h"


struct Checkpoint
{
	Vector2 position;
	Vector2 size;
	Vector2 direction;
	int rotation;
};

class TrackObjects
{
private :
	Checkpoint mStart;
	Checkpoint mCheckpoint;
	vector<TurretBase> mObstacles;

public :
	TrackObjects();
	~TrackObjects();

	void DrawTurretBases() const;

	void SetStart(Vector2 position, Vector2 size, Vector2 direction, int rotation);
	void SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction, int rotation);

	Checkpoint GetStart() const;
	Checkpoint GetCheckpoint() const;

	vector<TurretBase> GetTurretBases() const;
	void AddTurretBase(TurretBase obstacle);
	void RemoveTurretBase(int index);
	void ClearTurretBases();
};


#pragma once
#include "raylib.h"
#include <vector>

using std::vector;

#include "TurretBase.h"

class Objects
{
private :
	vector<TurretBase> mTurretBases;

	vector<Vector2> mEnemyPath;

public :
	Objects();
	~Objects();

	void DrawEnemyPath() const;
	vector<Vector2> GetEnemyPath() const;
	void AddEnemyWaypoint(Vector2 waypoint);
	void RemoveEnemyWaypoint(int index);
	void ClearEnemyPath();

	void DrawTurretBases() const;
	vector<TurretBase> GetTurretBases() const;
	void AddTurretBase(TurretBase turretBase);
	void RemoveTurretBase(int index);
	void ClearTurretBases();
};


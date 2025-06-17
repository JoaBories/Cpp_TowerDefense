#include "TrackObjects.h"

#include "Utils.h"

TrackObjects::TrackObjects() :
	mStart{ { 0, 0 }, { 0, 0 }, { 0, 0 } },
	mCheckpoint{ { 0, 0 }, { 0, 0 }, { 0, 0 } },
	mObstacles{}
{
}

TrackObjects::~TrackObjects()
{
}

void TrackObjects::DrawTurretBases() const
{
	for (TurretBase obstacle : mObstacles)
	{
		obstacle.Draw();
	}
}

void TrackObjects::SetStart(Vector2 position, Vector2 size, Vector2 direction, int rotation)
{
	mStart = { position, size, direction, rotation };
}

void TrackObjects::SetCheckpoint(Vector2 position, Vector2 size, Vector2 direction, int rotation)
{
	mCheckpoint = { position, size, direction, rotation };
}

Checkpoint TrackObjects::GetStart() const
{
	return mStart;
}

Checkpoint TrackObjects::GetCheckpoint() const
{
	return mCheckpoint;
}

vector<TurretBase> TrackObjects::GetTurretBases() const
{
	return mObstacles;
}

void TrackObjects::AddTurretBase(TurretBase obstacle)
{
	mObstacles.push_back(obstacle);
}

void TrackObjects::RemoveTurretBase(int index)
{
	mObstacles.erase(mObstacles.begin() + index);
}

void TrackObjects::ClearTurretBases()
{
	mObstacles.clear();
}

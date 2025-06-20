#include "Objects.h"

#include "Utils.h"

Objects::Objects() :
	mTurretBases{},
	mEnemyPath{}
{
}

Objects::~Objects()
{
}

void Objects::DrawEnemyPath() const
{
	if (mEnemyPath.size() > 0)
	{
		for (int i = 0; i < mEnemyPath.size(); i++)
		{
			DrawCircle(mEnemyPath[i].x, mEnemyPath[i].y, 10, RED);

			if (i > 0)
			{
				DrawLineEx(mEnemyPath[i - 1], mEnemyPath[i], 5, RED);
				Vector2 middlePoint = { (mEnemyPath[i - 1].x + mEnemyPath[i].x) * 0.5f, (mEnemyPath[i - 1].y + mEnemyPath[i].y) * 0.5f };
				Vector2 direction = Utils::Normalize({ mEnemyPath[i].x - mEnemyPath[i - 1].x, mEnemyPath[i].y - mEnemyPath[i - 1].y });
				Vector2 pointA = Utils::Vector2Add(middlePoint, Utils::Vector2Scale(direction, 20));
				Vector2 pointB = Utils::Vector2Substract(middlePoint, Utils::Vector2PerpendicularClockWise(Utils::Vector2Scale(direction, 10)));
				Vector2 pointC = Utils::Vector2Substract(middlePoint, Utils::Vector2PerpendicularClockWise(Utils::Vector2Scale(direction, -10)));

				DrawTriangle(pointB, pointA, pointC, RED);
			}
		}
	}
}

vector<Vector2> Objects::GetEnemyPath() const
{
	return mEnemyPath;
}

void Objects::AddEnemyWaypoint(Vector2 waypoint)
{
	mEnemyPath.push_back(waypoint);
}

void Objects::RemoveEnemyWaypoint(int index)
{
	mEnemyPath.erase(mEnemyPath.begin() + index);
}

void Objects::ClearEnemyPath()
{
	mEnemyPath.clear();
}

void Objects::DrawTurretBases() const
{
	for (TurretBase base : mTurretBases)
	{
		base.Draw();
	}
}

vector<TurretBase> Objects::GetTurretBases() const
{
	return mTurretBases;
}

void Objects::AddTurretBase(TurretBase turretBase)
{
	mTurretBases.push_back(turretBase);
}

void Objects::RemoveTurretBase(int index)
{
	mTurretBases.erase(mTurretBases.begin() + index);
}

void Objects::ClearTurretBases()
{
	mTurretBases.clear();
}

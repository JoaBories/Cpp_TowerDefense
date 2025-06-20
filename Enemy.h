#pragma once
#include "Utils.h"	
#include <vector>
#include "AssetBank.h"

using std::vector;

class Enemy
{
	private:
		int mType;  // 0 = ground, 1 = air
		int mPower; // 0,1
		int mCurrentWaypoint;
		float mHealth;
		float mSpeed;
		Vector2 mPosition;
		vector<Vector2> mWaypoints;
		float mRotation;
		Vector2 mSize;
		bool mIsWaitingForKill;
		bool mGotCastle;

	public:
		Enemy();
		Enemy(Vector2 position, int type, int power, float health, vector<Vector2> waypoints, float speed);
		~Enemy();

		void Update();
		void Draw() const;

		void TakeDamage(float damage);

		bool IsWaitingForKill() const;
		bool GotCastle() const;


};


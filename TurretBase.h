#pragma once
#include "raylib.h"

class TurretBase
{
private:
	Vector2 mPosition;
	Vector2 mSize;

public:
	TurretBase();
	~TurretBase();
	TurretBase(Vector2 position, Vector2 size);

	void Draw() const;

	Vector2 GetPosition() const;
	Vector2 GetSize() const;

};


#pragma once
#include "Track.h"

enum CursorType
{
	SetTiles,
	SetTurretBases
};


class TileCursor
{
private:
	int mRowIndex;
	int mColIndex;
	int mRowMax;
	int mColMax;
	int mRotation;
	Vector2 mSize;

	CursorType mType;

	Terrain* mTerrain;

	Texture *mTileTexture;

	bool hasSaved;


public:
	TileCursor();
	~TileCursor();
	TileCursor(Vector2 size, Terrain* track);

	void Update();
	void Draw() const;

	int GetRowIndex() const;
	int GetColIndex() const;

	bool isTrackValid() const;
	bool HasSaved() const;
	void Reset();
};


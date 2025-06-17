#pragma once
#include "Tilemap.h"
#include "TrackObjects.h"


class Terrain
{
private :
	Tilemap* mTilemap;
	TrackObjects* mObjects;

	string mFileName = "resources/track/01.track";

public :
	Terrain();
	~Terrain();

	void Draw() const;

	Tilemap* GetTilemap() const;
	TrackObjects* GetObjects() const;

	bool IsThereASave() const;

	void SaveTerrain() const;
	void LoadTerrain();

};


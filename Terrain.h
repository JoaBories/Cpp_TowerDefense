#pragma once
#include "Tilemap.h"
#include "Objects.h"


class Terrain
{
private :
	Tilemap* mTilemap;
	Objects* mObjects;

	string mFileName = "resources/track/01.track";

public :
	Terrain();
	~Terrain();

	void Draw() const;

	Tilemap* GetTilemap() const;
	Objects* GetObjects() const;

	bool IsThereASave() const;

	void SaveTerrain() const;
	void LoadTerrain();

};


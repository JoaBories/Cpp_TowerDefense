#pragma once
#include "Tilemap.h"
#include "Objects.h"


class Terrain
{
private :
	Tilemap* mpTilemap;
	Objects* mpObjects;

	string mFileName = "resources/map/01.map";

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


#pragma once
#include "raylib.h"
#include <map>
#include "Utils.h"

using std::map;

struct TileLayer // 0,0,0 -> empty layer
{
public :

	int type;
	int index;
	int rotation; // 0,90,180,270

	TileLayer(int type, int index, int rot) :
		type{type},
		index{index},
		rotation{rot}
	{
	}

	bool operator<(const TileLayer& other) const {
		// Comparison set it work with map
		return std::tie(type, index, rotation) < std::tie(other.type, other.index, other.rotation);
	}
};


class AssetBank
{
private :
	map<TileLayer, Texture*> mTileLayers;
	vector<Texture*> mTurretTextures;
	Texture* mErrorTexture;
	Texture* mEditorControlsTexture;
	Texture* mTurretBaseTexture;

	Texture* LoadTextureFromSource(const char* source);

public :
	AssetBank();
	~AssetBank();

	static AssetBank* instance;
	static AssetBank* GetInstance();

	Texture* GetTileLayerTexture(TileLayer layer);
	Texture* GetErrorTexture() const;
	Texture* GetEditorControlsTexture() const;
	Texture* GetTurretTexture(int index) const;
	Texture* GetTurretBaseTexture() const;
};


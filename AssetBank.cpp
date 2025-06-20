#include "AssetBank.h"
using std::pair;

AssetBank* AssetBank::instance = nullptr;

Texture* AssetBank::LoadTextureFromSource(const char* source)
{
    Image img = LoadImage(source);
    Texture* textPtr = new Texture(LoadTextureFromImage(img));

    UnloadImage(img);

    return textPtr;
}

AssetBank::AssetBank()
{
    if (instance == nullptr) 
    {
        instance = this;
    }

	mErrorTexture = LoadTextureFromSource("resources/img/error.png");
	mEditorControlsTexture = LoadTextureFromSource("resources/img/editor_controls.png");

    mTurretTextures.push_back(LoadTextureFromSource("resources/img/turret_ground_1.png"));
	mTurretTextures.push_back(LoadTextureFromSource("resources/img/turret_ground_2.png"));
	mTurretTextures.push_back(LoadTextureFromSource("resources/img/turret_air_1.png"));
	mTurretTextures.push_back(LoadTextureFromSource("resources/img/turret_air_2.png"));

	mEnemyTextures.push_back(LoadTextureFromSource("resources/img/soldier_1.png"));
	mEnemyTextures.push_back(LoadTextureFromSource("resources/img/soldier_2.png"));
	mEnemyTextures.push_back(LoadTextureFromSource("resources/img/plane_1.png"));
	mEnemyTextures.push_back(LoadTextureFromSource("resources/img/plane_2.png"));

    mBulletTextures.push_back(LoadTextureFromSource("resources/img/bullet_ground.png"));
    mBulletTextures.push_back(LoadTextureFromSource("resources/img/bullet_air.png"));

	mTurretBaseTexture = LoadTextureFromSource("resources/img/turret_base.png");

    mTileLayers[{0, 1, 0}] = LoadTextureFromSource("resources/img/grass_1.png");

	mTileLayers[{1, 1, 0}] = LoadTextureFromSource("resources/img/path_1.png");
	mTileLayers[{1, 2, 0}] = LoadTextureFromSource("resources/img/path_2.png");
	mTileLayers[{1, 3, 0}] = LoadTextureFromSource("resources/img/path_3.png");
	mTileLayers[{1, 4, 0}] = LoadTextureFromSource("resources/img/path_4.png");
	mTileLayers[{1, 5, 0}] = LoadTextureFromSource("resources/img/path_5.png");
	mTileLayers[{1, 6, 0}] = LoadTextureFromSource("resources/img/path_6.png");
}

AssetBank::~AssetBank()
{
    for (pair<TileLayer, Texture*> entry : mTileLayers) 
    {
        UnloadTexture(*entry.second);
        delete entry.second;
    }

    delete mErrorTexture;
    delete mEditorControlsTexture;

}

AssetBank* AssetBank::GetInstance()
{
    return instance;
}

Texture* AssetBank::GetTileLayerTexture(TileLayer layer)
{
	if (!mTileLayers[layer])
	{
		return mErrorTexture;
	}

    return mTileLayers[layer];
}

Texture* AssetBank::GetErrorTexture() const
{
    return mErrorTexture;
}

Texture* AssetBank::GetEditorControlsTexture() const
{
	return mEditorControlsTexture;
}

Texture* AssetBank::GetTurretTexture(int index) const
{
    if (!mTurretTextures[index])
    {
        return mErrorTexture;
    }

    return mTurretTextures[index];
}

Texture* AssetBank::GetEnemyTexture(int index) const
{
    if (!mEnemyTextures[index])
    {
        return mErrorTexture;
    }
    return mEnemyTextures[index];
}

Texture* AssetBank::GetBulletTexture(int index) const
{
    if (!mBulletTextures[index])
    {
        return mErrorTexture;
    }
    return mBulletTextures[index];
}

Texture* AssetBank::GetTurretBaseTexture() const
{
    return mTurretBaseTexture;
}

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
	mStartTexture = LoadTextureFromSource("resources/img/start.png");
	mCheckpointTexture = LoadTextureFromSource("resources/img/checkpoint.png");
	mObstacleTexture = LoadTextureFromSource("resources/img/obstacle.png");
	mEditorControlsTexture = LoadTextureFromSource("resources/img/editor_controls.png");

	mSkidMarkTexture = LoadTextureFromSource("resources/img/skid_mark.png");

    mTileLayers[{0, 1, 0}] = LoadTextureFromSource("resources/img/grass_1.png");

    mTileLayers[{1, 1, 0}] = LoadTextureFromSource("resources/img/road_1.png");
    mTileLayers[{1, 2, 0}] = LoadTextureFromSource("resources/img/road_2.png");
    mTileLayers[{1, 3, 0}] = LoadTextureFromSource("resources/img/road_3.png");
    mTileLayers[{1, 4, 0}] = LoadTextureFromSource("resources/img/road_4.png");
    mTileLayers[{1, 5, 0}] = LoadTextureFromSource("resources/img/road_5.png");
    mTileLayers[{1, 6, 0}] = LoadTextureFromSource("resources/img/road_6.png");
    mTileLayers[{1, 7, 0}] = LoadTextureFromSource("resources/img/road_7.png");
    mTileLayers[{1, 8, 0}] = LoadTextureFromSource("resources/img/road_8.png");
    mTileLayers[{1, 9, 0}] = LoadTextureFromSource("resources/img/road_9.png");
}

AssetBank::~AssetBank()
{
    for (pair<TileLayer, Texture*> entry : mTileLayers) 
    {
        UnloadTexture(*entry.second);
        delete entry.second;
    }

    delete mErrorTexture;
    delete mStartTexture;
    delete mCheckpointTexture;
    delete mObstacleTexture;
    delete mEditorControlsTexture;
    delete mCar1Texture;
    delete mSkidMarkTexture;

}

AssetBank* AssetBank::GetInstance()
{
    return instance;
}

Texture* AssetBank::GetTileLayerTexture(TileLayer layer)
{
	if (mTileLayers[layer] == nullptr)
	{
		return mErrorTexture;
	}

    return mTileLayers[layer];
}

Texture* AssetBank::GetErrorTexture() const
{
    return mErrorTexture;
}

Texture* AssetBank::GetStartTexture() const
{
	return mStartTexture;
}

Texture* AssetBank::GetCheckpointTexture() const
{
	return mCheckpointTexture;
}

Texture* AssetBank::GetObstacleTexture() const
{
	return mObstacleTexture;
}

Texture* AssetBank::GetEditorControlsTexture() const
{
	return mEditorControlsTexture;
}

Texture* AssetBank::GetCarTexture(int number) const
{
    switch (number)
    {
        case 1:
			return mCar1Texture;
			break;
        case 2:
            return mCar2Texture;
			break;
        default:
			return mErrorTexture;
            break;
    }
}

Texture* AssetBank::GetSkidMarkTexture() const
{
    return mSkidMarkTexture;
}
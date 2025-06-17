#include "TileCursor.h"

bool TileCursor::isTrackValid() const
{
	if (mTerrain->GetObjects()->GetStart().position.x != 0 || mTerrain->GetObjects()->GetStart().position.y != 0) 
	{
		if (mTerrain->GetObjects()->GetCheckpoint().position.x != 0 || mTerrain->GetObjects()->GetCheckpoint().position.y != 0)
		{
			return true;
		}
	}

	return false;
}

TileCursor::TileCursor() :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ 0 },
	mColMax{ 0 },
	mRotation{ 0 },
	mSize{ 0, 0 },
	mType{ SetTiles },
	mTerrain{ nullptr },
	mTileTexture{ nullptr },
	hasSaved{ false }
{
}

TileCursor::~TileCursor()
{
}

TileCursor::TileCursor(Vector2 size, Terrain* track) :
	mRowIndex{ 0 },
	mColIndex{ 0 },
	mRowMax{ track->GetTilemap()->GetRows()},
	mColMax{ track->GetTilemap()->GetCols()},
	mRotation{ 0 },
	mSize{ size },
	mType{ SetTiles },
	mTerrain{ track },
	mTileTexture{ nullptr },
	hasSaved{ false }
{
	Image img = LoadImage("resources/img/cursor.png");
	mTileTexture = new Texture(LoadTextureFromImage(img));
	UnloadImage(img);
}

void TileCursor::Update()
{
	if (IsKeyPressed(KEY_UP) && mRowIndex > 0)
	{
		mRowIndex--;
	}
	if (IsKeyPressed(KEY_DOWN) && mRowIndex < mRowMax - 1)
	{
		mRowIndex++;
	}
	if (IsKeyPressed(KEY_LEFT) && mColIndex > 0)
	{
		mColIndex--;
	}
	if (IsKeyPressed(KEY_RIGHT) && mColIndex < mColMax - 1)
	{
		mColIndex++;
	}

	if (IsKeyPressed(KEY_S) && isTrackValid())
	{
		mTerrain->SaveTerrain();
		hasSaved = true;
	}

	switch (mType)
	{
	case SetTiles:
		if (IsKeyPressed(KEY_E))
		{
			int index = mTerrain->GetTilemap()->GetTile(mRowIndex, mColIndex)->GetLayer1Index();
			index++;

			if (index == 7)
			{
				index = 0;
			}

			mTerrain->GetTilemap()->GetTile(mRowIndex, mColIndex)->SetLayer1Index(index);
		}

		if (IsKeyPressed(KEY_R))
		{
			int rot = mTerrain->GetTilemap()->GetTile(mRowIndex, mColIndex)->GetLayer1Rot();
			rot += 90;

			if (rot == 360)
			{
				rot = 0;
			}

			mTerrain->GetTilemap()->GetTile(mRowIndex, mColIndex)->SetLayer1Rot(rot);
		}
		break;

	case SetTurretBases:
		
		if (IsKeyPressed(KEY_E))
		{
			bool isSamePos = false;
			int index = 0;
			vector<TurretBase> bases = mTerrain->GetObjects()->GetTurretBases();
			for (int i = 0; i < bases.size(); i++)
			{
				TurretBase base = bases[i];

				if ( base.GetPosition().x == mSize.x * (0.5f + mColIndex) && base.GetPosition().y == mSize.y * (0.5f + mRowIndex))
				{
					isSamePos = true;
					index = i;
				}
			}

			if (!isSamePos)
			{
				mTerrain->GetObjects()->AddTurretBase(TurretBase({ mSize.x * (0.5f + mColIndex), mSize.y * (0.5f + mRowIndex) }, mTerrain->GetTilemap()->GetTileSize()));
			}
			else
			{
				mTerrain->GetObjects()->RemoveTurretBase(index);
			}
		}

		break;

	}

	if (IsKeyPressed(KEY_ENTER))
	{
		switch (mType)
		{
		case SetTiles:
			mType = SetTurretBases;
			mRotation = 0;
			break;

		case SetTurretBases:
			mType = SetTiles;
			mRotation = 0;
			break;
		}
	}
}

void TileCursor::Draw() const
{
	Rectangle rect = { 0, 0, 0, 0 };
	Texture* text = nullptr;

	//Cursor
	Vector2 pos = { mSize.x * (0.5 + mColIndex), mSize.y * (0.5 + mRowIndex) };
	rect = { pos.x, pos.y, mSize.x, mSize.y };
	text = mTileTexture;

	switch (mType)
	{
	case SetTiles:
		break;

	case SetTurretBases:
		text = AssetBank::GetInstance()->GetTurretBaseTexture();

		break;
	}

	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, mRotation, WHITE);
}

int TileCursor::GetRowIndex() const
{
	return mRowIndex;
}

int TileCursor::GetColIndex() const
{
	return mColIndex;
}

bool TileCursor::HasSaved() const
{
	return hasSaved;
}

void TileCursor::Reset()
{
	mRowIndex = 0;
	mColIndex = 0;
	mRotation = 0;
	mType = SetTiles;
	hasSaved = false;
}

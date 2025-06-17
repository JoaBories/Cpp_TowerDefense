#include "TurretBase.h"
#include "Utils.h"
#include "AssetBank.h"

TurretBase::TurretBase() :
	mPosition{ 0, 0 },
	mSize{ 0, 0 }
{
}

TurretBase::~TurretBase()
{
}

TurretBase::TurretBase(Vector2 position, Vector2 size) :
	mPosition{ position },
	mSize{ size }
{
}

void TurretBase::Draw() const
{
	int squareSide = Utils::Max(mSize.x, mSize.y);
	Rectangle rect1{ mPosition.x, mPosition.y, squareSide, squareSide };
	Texture* text = AssetBank::GetInstance()->GetTurretBaseTexture();
	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect1, { rect1.width * 0.5f, rect1.height * 0.5f }, 0, WHITE);
}

Vector2 TurretBase::GetPosition() const
{
	return mPosition;
}

Vector2 TurretBase::GetSize() const
{
	return mSize;
}

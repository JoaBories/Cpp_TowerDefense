#include "Bullet.h"

Bullet::Bullet() :
	mType{ 0 },
	mPosition{ 0,0 },
	mSize{ 0,0 },
	mDirection{ 0,0 },
	mSpeed{ 0 },
	mDamage{ 0 },
	mLifespan{ 0 }
{
}

Bullet::Bullet(short type, Vector2 position, Vector2 direction, float speed, float damage, float lifespan):
	mType{ type },
	mPosition{ position },
	mSize{ 15,15 },
	mDirection{ direction },
	mSpeed{ speed },
	mDamage{ damage },
	mLifespan{ lifespan }
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	mLifespan -= GetFrameTime();
	mPosition = Utils::Vector2Add(mPosition, Utils::Vector2Scale(mDirection, mSpeed * GetFrameTime()));
}

void Bullet::Draw() const
{
	Texture* text = AssetBank::GetInstance()->GetBulletTexture(mType);

	Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
	float rotation = Utils::RotFromVector2(mDirection);

	DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, rotation, WHITE);
	//DrawCircleV(mPosition, GetRadius(), { 255,0,0,100 });
}

float Bullet::GetLifetime() const
{
	return mLifespan;
}

float Bullet::GetRadius() const
{
	return mSize.x * 0.5f;
}

Vector2 Bullet::GetPosition() const
{
	return mPosition;
}

short Bullet::GetType() const
{
	return mType;
}

float Bullet::GetDamage() const
{
	return mDamage;
}

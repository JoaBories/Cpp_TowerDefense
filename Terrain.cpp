#include "Terrain.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

Terrain::Terrain()
{
	mTilemap = new Tilemap(14, 20);
	mObjects = new Objects();
}

Terrain::~Terrain()
{
}

void Terrain::Draw() const
{
	mTilemap->Draw();
	mObjects->DrawTurretBases();
}

Tilemap* Terrain::GetTilemap() const
{
	return mTilemap;
}

Objects* Terrain::GetObjects() const
{
	return mObjects;
}

bool Terrain::IsThereASave() const
{
	ifstream file(mFileName);
	return file.good();
}

void Terrain::SaveTerrain() const
{
	ofstream file(mFileName);
	if (!file) return;
	
	vector<TurretBase> turretBases = mObjects->GetTurretBases();
	file << turretBases.size() << endl;
	for (size_t i = 0; i < turretBases.size(); i++)
	{
		file << turretBases[i].GetPosition().x << " " << turretBases[i].GetPosition().y << " " << turretBases[i].GetSize().x << " " << turretBases[i].GetSize().y << endl;
	}

	file << mTilemap->GetRows() << " " << mTilemap->GetCols() << endl;
	for (size_t r = 0; r < mTilemap->GetRows(); r++)
	{
		for (size_t c = 0; c < mTilemap->GetCols(); c++)
		{
			file << mTilemap->GetTile(r, c)->GetLayer1Index() << " " << mTilemap->GetTile(r, c)->GetLayer1Rot() << "   ";
		}
		file << endl;
	}

	file << mObjects->GetEnemyPath().size() << endl;
	for (size_t i = 0; i < mObjects->GetEnemyPath().size(); i++)
	{
		file << mObjects->GetEnemyPath()[i].x << " " << mObjects->GetEnemyPath()[i].y << endl;
	}

	file << "End" << endl;

	file.close();
}

void Terrain::LoadTerrain()
{

	if (IsThereASave())
	{
		ifstream file(mFileName);
		if (!file) return;

		float a, b, c, d, e, f, g;

		file >> a;
		mObjects->ClearTurretBases();
		for (size_t i = 0; i < a; i++)
		{
			file >> b >> c >> d >> e;
			mObjects->AddTurretBase(TurretBase({ b, c }, { d, e }));
		}

		file >> a >> b;

		for (size_t row = 0; row < a; row++)
		{
			for (size_t col = 0; col < b; col++)
			{
				file >> c >> d;
				mTilemap->GetTile(row, col)->SetLayer1Index(c);
				mTilemap->GetTile(row, col)->SetLayer1Rot(d);
			}
		}

		file >> a;
		mObjects->ClearEnemyPath();
		for (size_t i = 0; i < a; i++)
		{
			file >> b >> c;
			mObjects->AddEnemyWaypoint({ b, c });
		}
	}

}

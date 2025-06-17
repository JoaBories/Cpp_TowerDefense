#include "Track.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

Terrain::Terrain()
{
	mTilemap = new Tilemap(14, 20);
	mObjects = new TrackObjects();
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

TrackObjects* Terrain::GetObjects() const
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
	file << "TurretBases " << turretBases.size() << endl;
	for (size_t i = 0; i < turretBases.size(); i++)
	{
		file << i << "- " << turretBases[i].GetPosition().x << " " << turretBases[i].GetPosition().y << " " << turretBases[i].GetSize().x << " " << turretBases[i].GetSize().y << endl;
	}

	file << "Tilemap " << mTilemap->GetRows() << " " << mTilemap->GetCols() << endl;
	for (size_t r = 0; r < mTilemap->GetRows(); r++)
	{
		for (size_t c = 0; c < mTilemap->GetCols(); c++)
		{
			file << mTilemap->GetTile(r, c)->GetLayer1Index() << " " << mTilemap->GetTile(r, c)->GetLayer1Rot() << "   ";
		}
		file << endl;
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

		int a, b, c, d, e, f, g;
		string label;

		file >> label;
		file >> a;

		mObjects->ClearTurretBases();
		for (size_t i = 0; i < a; i++)
		{
			file >> label;
			file >> b >> c >> d >> e;
			mObjects->AddTurretBase(TurretBase({ (float)b, (float)c }, { (float)d, (float)e }));
		}

		file >> label;
		file >> a >> b;

		for (size_t r = 0; r < a; r++)
		{
			for (size_t col = 0; col < b; col++)
			{
				file >> c >> d;
				mTilemap->GetTile(r, col)->SetLayer1Index(c);
				mTilemap->GetTile(r, col)->SetLayer1Rot(d);
			}
		}
	}

}

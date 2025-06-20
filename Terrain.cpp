#include "Terrain.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

Terrain::Terrain()
{
	mpTilemap = new Tilemap(14, 20);
	mpObjects = new Objects();
}

Terrain::~Terrain()
{
}

void Terrain::Draw() const
{
	mpTilemap->Draw();
	mpObjects->DrawTurretBases();
}

Tilemap* Terrain::GetTilemap() const
{
	return mpTilemap;
}

Objects* Terrain::GetObjects() const
{
	return mpObjects;
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
	
	vector<TurretBase> turretBases = mpObjects->GetTurretBases();
	file << turretBases.size() << endl;
	for (size_t i = 0; i < turretBases.size(); i++)
	{
		file << turretBases[i].GetPosition().x << " " << turretBases[i].GetPosition().y << " " << turretBases[i].GetSize().x << " " << turretBases[i].GetSize().y << endl;
	}

	file << mpTilemap->GetRows() << " " << mpTilemap->GetCols() << endl;
	for (size_t r = 0; r < mpTilemap->GetRows(); r++)
	{
		for (size_t c = 0; c < mpTilemap->GetCols(); c++)
		{
			file << mpTilemap->GetTile(r, c)->GetLayer1Index() << " " << mpTilemap->GetTile(r, c)->GetLayer1Rot() << "   ";
		}
		file << endl;
	}

	file << mpObjects->GetEnemyPath().size() << endl;
	for (size_t i = 0; i < mpObjects->GetEnemyPath().size(); i++)
	{
		file << mpObjects->GetEnemyPath()[i].x << " " << mpObjects->GetEnemyPath()[i].y << endl;
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
		mpObjects->ClearTurretBases();
		for (size_t i = 0; i < a; i++)
		{
			file >> b >> c >> d >> e;
			mpObjects->AddTurretBase(TurretBase({ b, c }, { d, e }));
		}

		file >> a >> b;

		for (size_t row = 0; row < a; row++)
		{
			for (size_t col = 0; col < b; col++)
			{
				file >> c >> d;
				mpTilemap->GetTile(row, col)->SetLayer1Index(c);
				mpTilemap->GetTile(row, col)->SetLayer1Rot(d);
			}
		}

		file >> a;
		mpObjects->ClearEnemyPath();
		for (size_t i = 0; i < a; i++)
		{
			file >> b >> c;
			mpObjects->AddEnemyWaypoint({ b, c });
		}
	}

}

#include "Engine.h"

void Engine::StartGame()
{
	mGameState = DefendState;
	mTerrain->LoadTerrain();
}

void Engine::MouseCheckUpdate()
{
	vector<TurretBase> bases = mTerrain->GetObjects()->GetTurretBases();
	Vector2 mousePosition = GetMousePosition();

	for (TurretBase base : bases)
	{
		bool leftSide = mousePosition.x >= base.GetPosition().x - base.GetSize().x * 0.5f;
		bool rightSide = mousePosition.x <= base.GetPosition().x + base.GetSize().x * 0.5f;
		bool topSide = mousePosition.y >= base.GetPosition().y - base.GetSize().y * 0.5f;
		bool bottomSide = mousePosition.y <= base.GetPosition().y + base.GetSize().y * 0.5f;

		if (leftSide && rightSide && topSide && bottomSide)
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				bool thereIsAlreadyOne = false;
				for (Turret* turret : mTurrets)
				{
					if (turret->GetPosition().x == base.GetPosition().x && turret->GetPosition().y == base.GetPosition().y)
					{
						thereIsAlreadyOne = true;
					}
				}

				if (!thereIsAlreadyOne && PlayerInfos::GetInstance()->GetMoney() >= 25)
				{
					mTurrets.push_back(new Turret(0, 0, base.GetPosition(), mEnemySpawner, mBulletBank, base.GetSize()));
					PlayerInfos::GetInstance()->AddMoney(-25);
				}
			}

			break;
		}
	}
}

void Engine::MouseCheckDraw()
{
	vector<TurretBase> bases = mTerrain->GetObjects()->GetTurretBases();
	Vector2 mousePosition = GetMousePosition();

	for (TurretBase base : bases)
	{
		bool leftSide = mousePosition.x >= base.GetPosition().x - base.GetSize().x * 0.5f;
		bool rightSide = mousePosition.x <= base.GetPosition().x + base.GetSize().x * 0.5f;
		bool topSide = mousePosition.y >= base.GetPosition().y - base.GetSize().y * 0.5f;
		bool bottomSide = mousePosition.y <= base.GetPosition().y + base.GetSize().y * 0.5f;

		if (leftSide && rightSide && topSide && bottomSide)
		{
			Rectangle rect = { base.GetPosition().x - base.GetSize().x * 0.5f, base.GetPosition().y - base.GetSize().y * 0.5f, base.GetSize().x, base.GetSize().y };

			bool thereIsAlreadyOne = false;
			for (Turret* turret : mTurrets)
			{
				if (turret->GetPosition().x == base.GetPosition().x && turret->GetPosition().y == base.GetPosition().y)
				{
					thereIsAlreadyOne = true;
				}
			}

			if (thereIsAlreadyOne || PlayerInfos::GetInstance()->GetMoney() < 25)
			{
				DrawRectangleRec(rect, RED);
			}
			else
			{
				DrawRectangleRec(rect, GREEN);
			}
		}
	}
}

void Engine::DrawGameUI() const
{
	string texte = "";
	texte = "Life : " + std::to_string( PlayerInfos::GetInstance()->GetLife());
	Utils::DrawTextWithBackground(texte, { (float)GetScreenWidth() * 0.9f, (float)GetScreenHeight() * 0.1f }, 40, WHITE, mOrange, 10);
	texte = "Money : " + std::to_string(PlayerInfos::GetInstance()->GetMoney());
	Utils::DrawTextWithBackground(texte, { (float)GetScreenWidth() * 0.9f, (float)GetScreenHeight() * 0.2f }, 40, WHITE, mOrange, 10);
}

Engine::Engine() :
	mTileCursor{ nullptr },
	mTerrain{ nullptr },
	mGameState{ StartState },
	mOrange{ 245, 155, 20, 255 },
	mEnemySpawner{ nullptr },
	mBulletBank{ nullptr },
	mTurrets{}
{
}

Engine::~Engine()
{
	delete mTileCursor;
	delete mTerrain;
	delete mEnemySpawner;
	delete mBulletBank;
}

void Engine::Init()
{
	mTerrain = new Terrain();
	mTileCursor = new TileCursor(mTerrain->GetTilemap()->GetTileSize(), mTerrain);
	mEnemySpawner = new EnemySpawner(mTerrain);
	mBulletBank = new BulletBank(mEnemySpawner);
}

void Engine::Reset()
{
	PlayerInfos::GetInstance()->Reset();
	delete mEnemySpawner;
	delete mBulletBank;
	for (Turret* turret : mTurrets)
	{
		delete turret;
	}
	mTurrets.clear();
	Init();
}

void Engine::Update()
{
	switch (mGameState)
	{
	case StartState:
		if (IsKeyPressed(KEY_E))
		{
			mGameState = EditorState;
			mTerrain->LoadTerrain();
		}

		else if (IsKeyPressed(KEY_P) && mTerrain->IsThereASave())
		{
			StartGame();
		}
		break;

	case EditorState:
		mTileCursor->Update();
		if (mTileCursor->HasSaved())
		{
			mGameState = StartState;
			mTileCursor->Reset();
		}
		break;

	case DefendState:
		mEnemySpawner->Update();
		MouseCheckUpdate();
		
		for (Turret* turret : mTurrets)
		{
			turret->Update();
		}

		mBulletBank->Update();

		if (PlayerInfos::GetInstance()->GetLife() <= 0)
		{
			mGameState = FinishStateLost;
		}
		else if (PlayerInfos::GetInstance()->GetHasWin())
		{
			mGameState = FinishStateWon;
		}

		break;

	case FinishStateLost:
		if (IsKeyPressed(KEY_ENTER))
		{
			mGameState = StartState;

			Reset();
		}
		break;

	case FinishStateWon:
		if (IsKeyPressed(KEY_ENTER))
		{
			mGameState = StartState;

			Reset();
		}
		break;
	}
}

void Engine::Draw()
{
	Rectangle rect = { 0, 0, 0, 0 };
	Texture* text = nullptr;


	switch (mGameState)
	{
	case StartState:
		Utils::DrawTextCentered("Mini TD", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 }, 20, mOrange);
		
		if (mTerrain->IsThereASave())
		{
			Utils::DrawTextCentered("Play - P", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20, mOrange);
		}
		break;

	case EditorState:
		mTerrain->Draw();
		mTileCursor->Draw();

		rect = { (float) GetScreenWidth() - 100, (float) GetScreenHeight() - 50, 200, 200};
		text = AssetBank::GetInstance()->GetEditorControlsTexture();
		DrawTexturePro(*text, { 0,0,(float)text->width,(float)text->height }, rect, { rect.width * 0.5f, rect.height * 0.5f }, 0, WHITE);
		Utils::DrawTextCentered("Enter to change mode", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 125 }, 20);

		if (mTileCursor->isTrackValid()) 
		{
			Utils::DrawTextCentered("S to Save", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 150 }, 20);
		}
		else
		{
			Utils::DrawTextCentered("Map invalid", { (float)GetScreenWidth() - 125, (float)GetScreenHeight() - 150 }, 20);
		}

		break;

	case DefendState:
		mTerrain->Draw();
		mEnemySpawner->Draw();

		MouseCheckDraw();
		
		for (Turret* turret : mTurrets)
		{
			turret->Draw();
		}

		mBulletBank->Draw();
		DrawGameUI();

		break;

	case FinishStateLost:
		Utils::DrawTextCentered("You lost !", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 }, 20, mOrange);
		Utils::DrawTextCentered("Press Enter to return to menu", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20, mOrange);
		break;

	case FinishStateWon:
		Utils::DrawTextCentered("You won !", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 3 }, 20, mOrange);
		Utils::DrawTextCentered("Press Enter to return to menu", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20, mOrange);
		break;

	}
	
}

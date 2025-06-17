#include "Engine.h"

void Engine::StartRace()
{
	mGameState = RaceState;
	mTrack->LoadTerrain();
}

Engine::Engine() :
	mTileCursor{ nullptr },
	mTrack{ nullptr },
	mGameState{ StartState },
	mOrange{ 245, 155, 20, 255 }
{
}

Engine::~Engine()
{
	delete mTileCursor;
	delete mTrack;
}

void Engine::Init()
{
	mTrack = new Terrain();
	mTileCursor = new TileCursor(mTrack->GetTilemap()->GetTileSize(), mTrack);
}

void Engine::Update()
{
	switch (mGameState)
	{
	case StartState:
		if (IsKeyPressed(KEY_E))
		{
			mGameState = EditorState;
			mTrack->LoadTerrain();
		}

		else if (IsKeyPressed(KEY_P) && mTrack->IsThereASave())
		{
			StartRace();
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

	case RaceState:
		break;

	case FinishState:
		if (IsKeyPressed(KEY_ENTER))
		{
			mGameState = StartState;
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
		
		if (mTrack->IsThereASave())
		{
			Utils::DrawTextCentered("Play - P", { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, 20, mOrange);
		}
		break;

	case EditorState:
		mTrack->Draw();
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

	case RaceState:
		mTrack->Draw();	
		
		break;

	case FinishState:

		break;

	}
	
}

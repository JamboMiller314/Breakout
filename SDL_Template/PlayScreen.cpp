#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mStartLabel = new GLTexture("START", "emulogic.ttf", 32, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);
	

	mBackground = new GLTexture("Space.png", 0, 0, 1024, 896, true);
	mBackground->Parent(this);
	mBackground->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);

	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 10.0f);
	mTopBar->Parent(this);

	mPlayerOne = new GLTexture("SCORE<1>", "emulogic.ttf", 22, {238, 130, 238 });
	mPlayerOne->Parent(mTopBar);
	mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.3f, 30.0f);

	mPlayerTwo = new GLTexture("SCORE<2>", "emulogic.ttf", 22, { 238, 130, 238 });
	mPlayerTwo->Parent(mTopBar);
	mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.30f, 30.0f);

	mHiScore = new GLTexture("HI-SCORE", "emulogic.ttf", 22, { 238, 130, 238 });
	mHiScore->Parent(mTopBar);
	mHiScore->Position(-15.0f, 30.0f);

	mPlayerOneScore = new Scoreboard();
	mPlayerTwoScore = new Scoreboard();
	mTopScore = new Scoreboard();

	mPlayerOneScore->Parent(mTopBar);
	mPlayerTwoScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.23f, 80.0f);
	mPlayerTwoScore->Position(Graphics::SCREEN_WIDTH * 0.32f, 80.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 80.0f);
	mTopScore->Score(0);
	
	mBall = nullptr;
	mPlayer = Player::Instance();
	mPlayer->Parent(this);
	StartNewGame();
	generateBlocks();

	
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHiScore;
	mHiScore = nullptr;
	delete mBackground;
	mBackground = nullptr;
	
}

void PlayScreen::handleCollisions()
{
	for (int i = mBlocks.size() - 1; i >= 0; i--) {
		if (mBlocks[i] != nullptr)
		{
			if (mBlocks[i]->WasHit() && mBlocks[i]->Active()) {
				
				if (mBlocks[i]->getBlockType() == Blocks::BlockType::Purple) {
					mPlayer->AddScore(30);
					mBlocks[i]->Active(false);
					
				}
				else if (mBlocks[i]->getBlockType() == Blocks::BlockType::Red) {
					mPlayer->AddScore(20);
					mBlocks[i]->Active(false);
					
				}
				else if (mBlocks[i]->getBlockType() == Blocks::BlockType::Yellow) {
					mPlayer->AddScore(10);
					mBlocks[i]->Active(false);
					
				}
				else if (mBlocks[i]->getBlockType() == Blocks::BlockType::Green)
				{
					mPlayer->AddScore(20);
					mBlocks[i]->Active(false);
					
				}
				mPlayerOneScore->Score(mPlayer->Score());
			}
		}
		
	}
}

void PlayScreen::generateBlocks()
{
	int k = 0;

	for (int i =0; i < 4; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == 0)
			{
				mBlocks.push_back(new Blocks(Blocks::BlockType::Purple));
			}
			else if (i == 1)
			{
				mBlocks.push_back(new Blocks(Blocks::BlockType::Red));
			}
			else if (i == 2)
			{
				mBlocks.push_back(new Blocks(Blocks::BlockType::Yellow));
			}
			else if (i == 3)
			{
				mBlocks.push_back(new Blocks(Blocks::BlockType::Green));
			}
			mBlocks[k]->Position((Graphics::SCREEN_WIDTH * 0.15f) + (j * 59.0f), (Graphics::SCREEN_HEIGHT * 0.2f) + (i * 50.0f));
			k++;
		}
	}
}

void PlayScreen::StartNewGame() {
	
	
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);
	delete mBall;
	mBall = new Ball();
	mBall->Parent(this);
	mBall->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
	
	
}

void PlayScreen::Update() {
	mPlayer->Update();		
	mBall->Update();
	mPlayerOne->Update();
	mPlayerTwo->Update();
	mHiScore->Update();
	mPlayerOneScore->Update();
	mPlayerTwoScore->Update();
	mTopScore->Update();
	
	for (int i = 0; i < mBlocks.size(); i++)
	{
		
		if(mBlocks[i] != nullptr)
		{
			if (mBlocks[i]->WasHit())
			{
				delete mBlocks[i];
				mBlocks[i] = nullptr;
				
			}
			
		}
		
		if(mBlocks[i] != nullptr)
		{
			mBlocks[i]->Update();
		}
		handleCollisions();
	}
	
}

void PlayScreen::Render() {
	
	mBackground->Render();
	mPlayer->Render();	
	mBall->Render();
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	mPlayerOneScore->Render();
	mPlayerTwoScore->Render();
	mTopScore->Render();
	
	for (int i = 0; i < mBlocks.size(); i++)
	{
		if (mBlocks[i] != nullptr)
		{
			mBlocks[i]->Render();
		}
		
	}
	
}

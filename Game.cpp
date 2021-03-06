#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>
#include <iostream>
#include <fstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "KinematicUnit.h"
#include "WallUnit.h"
#include "PlayerMoveToMessage.h"

// new stuff
#include "UnitManager.h"
#include "InputManager.h"
#include "UIManager.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpSample(NULL)
	,mBackgroundBufferID(INVALID_ID)
	,mpUnitManager()
	,mpInputManager()
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{

	// start random
	srand(time(NULL));

	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//startup allegro
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpSpriteManager = new SpriteManager();

	//startup a lot of allegro stuff

	//load image loader addon
	if( !al_init_image_addon() )
	{
		fprintf(stderr, "image addon failed to load!\n");
		return false;
	}

	//install audio stuff
	if( !al_install_audio() )
	{
		fprintf(stderr, "failed to initialize sound!\n");
		return false;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	// initialize the inputManager so that the font can load
	mpInputManager = new InputManager();

	//show the mouse
	if( !al_hide_mouse_cursor( mpGraphicsSystem->getDisplay() ) )
	{
		printf( "Mouse cursor not able to be hidden!\n" ); 
		return false;
	}

	if( !al_init_primitives_addon() )
	{
		printf( "Primitives addon not added!\n" ); 
		return false;
	}

	//load the sample
	mpSample = al_load_sample( "clapping.wav" );
	if (!mpSample)
	{
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}

	mpMessageManager = new GameMessageManager();

	mpUIManager = new UIManager();

	//load buffers
	mBackgroundBufferID = mpGraphicsBufferManager->loadBuffer("wallpaper.bmp");
	mPlayerIconBufferID = mpGraphicsBufferManager->loadBuffer("arrow.bmp");
	mEnemyIconBufferID = mpGraphicsBufferManager->loadBuffer("enemy-arrow.bmp");
	mWallBufferID = mpGraphicsBufferManager->loadBuffer("horWall.bmp");
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer( mEnemyIconBufferID );
	GraphicsBuffer* pWallBuffer = mpGraphicsBufferManager->getBuffer(mWallBufferID);

	if( pAIBuffer != NULL )
	{
		mpEnemyArrow = mpSpriteManager->createAndManageSprite( AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight() );
	}

	// read from the file if one exists
	ifstream fin;
	fin.open(FILENAME);

	// if the file opened, read the values and assign the weights accordingly
	if (fin.is_open())
	{
		string tmp1, tmp2, tmp3;

		getline(fin, tmp1);
		getline(fin, tmp2);
		getline(fin, tmp3);

		//convert to floats
		mStartCohWeight = stof(tmp1);
		mStartSepWeight = stof(tmp2);
		mStartAlgnWeight = stof(tmp3);

		fin.close();
	}
	// if the file wasn't opened, initialize the values at zero instead
	else
	{
		std::cout << "could not open file or file did not exist" << std::endl;

		mStartCohWeight = 0;
		mStartSepWeight = 0;
		mStartAlgnWeight = 0;

		fin.close();
	}

	mpUnitManager = new UnitManager();

	// the four walls
	mpUnitManager->AddWallUnit(new WallUnit(Vector2D(0, 0), Vector2D(mpGraphicsSystem->getWidth(), WALL_THICKNESS)));
	mpUnitManager->AddWallUnit(new WallUnit(Vector2D(0, 0), Vector2D(WALL_THICKNESS, mpGraphicsSystem->getHeight())));
	mpUnitManager->AddWallUnit(new WallUnit(Vector2D(mpGraphicsSystem->getWidth() - WALL_THICKNESS, 0), Vector2D(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight())));
	mpUnitManager->AddWallUnit(new WallUnit(Vector2D(0, mpGraphicsSystem->getHeight() - WALL_THICKNESS), Vector2D(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight())));

	// the player
	Vector2D pos( -100.0f, -100.0f );
	Vector2D vel( 0.0f, 0.0f );
	mpUnitManager->AddUnit(new KinematicUnit(pArrowSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f, CHARACTER_SIDE, CHARACTER_SIDE), 0);

	return true;
}

void Game::cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;

	al_destroy_sample(mpSample);
	mpSample = NULL;

	// new stuff
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpInputManager;
	mpInputManager = NULL;
	delete mpUIManager;
	mpUIManager = NULL;

	//shutdown components
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}
	
void Game::processLoop()
{
	//update units
	mpUnitManager->UnitUpdate(LOOP_TARGET_TIME / 1000.0f);
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	pBackgroundSprite->draw( *(mpGraphicsSystem->getBackBuffer()), 0, 0 );

	//draw units
	mpUnitManager->UnitDraw(GRAPHICS_SYSTEM->getBackBuffer());

	// get inputs
	mpInputManager->Update();

	// process messages
	mpMessageManager->processMessagesForThisframe();

	// update UI
	mpUIManager->doUI();

	// swap things off of the backbuffer
	GRAPHICS_SYSTEM->swap();
}

Game* Game::getInstance()
{
	// return the instance of game
	if (gpGame != NULL)
	{
		return gpGame;
	}
	return NULL;
}

bool Game::endLoop()
{
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

void Game::createArriveUnit()
{
	// creates a new unit with the behavior to arrive at the player
	Vector2D tmpPos(mpUnitManager->GetUnit(0)->getPosition().getX() + SPAWN_DISTANCE_ARRIVE, mpUnitManager->GetUnit(0)->getPosition().getY());
	Vector2D tmpVel(0.0f, 0.0f);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, tmpPos, 1, tmpVel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 1);
}

void Game::createWanderSOFUnit(bool shouldFlee)
{
	// creates a new unit with the behavior to arrive at the player
	Vector2D tmpPos(mpUnitManager->GetUnit(0)->getPosition().getX() + SPAWN_DISTANCE_WANDERSEEK, mpUnitManager->GetUnit(0)->getPosition().getY());
	Vector2D tmpVel(0.0f, 0.0f);
	if (shouldFlee)
	{
		// 4 refers to wander and flee
		mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, tmpPos, 1, tmpVel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 4);
	}
	else
	{
		// 3 refers to wander and seek
		mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, tmpPos, 1, tmpVel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 3);
	}
}

void Game::createSeekUnit()
{
	// creates a new unit with the behavior to seek at the player
	Vector2D tmpPos(mpUnitManager->GetUnit(0)->getPosition().getX() + SPAWN_DISTANCE_SEEK, mpUnitManager->GetUnit(0)->getPosition().getY());
	Vector2D tmpVel(0.0f, 0.0f);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, tmpPos, 1, tmpVel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 2);
}

void Game::deleteRandomUnit()
{
	// calls the unit manager to delete a random unit
	mpUnitManager->RemoveRandomUnit();
}

void Game::createFiveBoids()
{
	Vector2D pos = (mpGraphicsSystem->getWidth() / 2, mpGraphicsSystem->getHeight() / 2);
	Vector2D vel = (0, 0);

	// add 5 boids
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, pos, 1, vel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 5);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, pos, 1, vel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 5);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, pos, 1, vel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 5);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, pos, 1, vel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 5);
	mpUnitManager->AddUnit(new KinematicUnit(mpEnemyArrow, pos, 1, vel, 0.0f, 180.0f, 100.0f, CHARACTER_SIDE, CHARACTER_SIDE), 5);
}

// these functions tell all units to change their values (assignment 3)
void Game::changeWeightCohesion(bool add)
{
	if (add)
	{
		mStartCohWeight += WEIGHT_CHANGE;
	}
	else
	{
		mStartCohWeight -= WEIGHT_CHANGE;
	}
}

void Game::changeWeightSeparation(bool add)
{
	if (add)
	{
		mStartSepWeight += WEIGHT_CHANGE;
	}
	else
	{
		mStartSepWeight -= WEIGHT_CHANGE;
	}
}

void Game::changeWeightAllignment(bool add)
{
	if (add)
	{
		mStartAlgnWeight += WEIGHT_CHANGE;
	}
	else
	{
		mStartAlgnWeight -= WEIGHT_CHANGE;
	}
}

void Game::saveValues()
{
	ofstream fout;
	fout.open(FILENAME);

	// output weights to file
	if (fout.is_open())
	{
		fout << mStartCohWeight << std::endl;
		fout << mStartSepWeight << std::endl;
		fout << mStartAlgnWeight << std::endl;
	}

	std::cout << "Saved weights." << std::endl;

	fout.close();
}
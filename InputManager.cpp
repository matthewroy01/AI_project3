#include "InputManager.h"

#include "Game.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

// message types
#include "UnitCreateArriveMessage.h"
#include "UnitCreateSeekMessage.h"
#include "UnitDeleteRandomMessage.h"
#include "UnitCreateWanderSOFMessage.h"
#include "ChangeModeValueMessage.h"
#include "ChangeModeMessage.h"
#include "ToggleDisplayInfoMessage.h"
#include "UnitCreateFiveBoidsMessage.h"
#include "SaveValuesMessage.h"

InputManager::InputManager()
{
	/*mSdown = false;
	mFdown = false;
	mDdown = false;
	mIdown = false;
	mPlusdown = false;
	mMinusdown = false;
	mVdown = false;
	mRdown = false;
	mAdown = false;*/

	mCdown = false;
	mSdown = false;
	mAdown = false;
	mCTRLdown = false;

	if (!init())
	{
		// something wasn't installed
	}
}

InputManager::~InputManager()
{
	
}

bool InputManager::init()
{
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
		return false;
	}

	if (!al_install_mouse())
	{
		printf("Mouse not installed!\n");
		return false;
	}

	return true;
}

void InputManager::Update()
{
	//get current keyboard state
	al_get_keyboard_state(&keyState);

	//if 'escape' key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		GET_GAME->setShouldExit(true);
	}

	//if 'c' key is pressed, change current mode to "cohesion"
	if (al_key_down(&keyState, ALLEGRO_KEY_C) && !mCdown)
	{
		mCdown = true;
		GameMessage* pMessage = new ChangeModeMessage(0);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 's' key is pressed, change current mode to "separation"
	if (al_key_down(&keyState, ALLEGRO_KEY_S) && !mSdown && !mCTRLdown)
	{
		mSdown = true;
		GameMessage* pMessage = new ChangeModeMessage(1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'a' key is pressed, change current mode to "allignment"
	if (al_key_down(&keyState, ALLEGRO_KEY_A) && !mAdown)
	{
		mAdown = true;
		GameMessage* pMessage = new ChangeModeMessage(2);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'i' key is pressed, spawn 5 boids
	if (al_key_down(&keyState, ALLEGRO_KEY_I) && !mIdown)
	{
		mIdown = true;
		GameMessage* pMessage = new UnitCreateFiveBoidsMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'd' key is pressed delete a random unit
	if (al_key_down(&keyState, ALLEGRO_KEY_D) && !mDdown)
	{
		mDdown = true;
		GameMessage* pMessage = new UnitDeleteRandomMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if '+' key is pressed increase the currently selected variable
	if (al_key_down(&keyState, ALLEGRO_KEY_EQUALS) && !mPlusdown)
	{
		mPlusdown = true;
		int tmpMode = GET_GAME->getUnitManager()->GetCurrentMode();

		GameMessage* pMessage = new ChangeModeValueMessage(tmpMode, true);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if '-' key is pressed increase the currently selected variable
	if (al_key_down(&keyState, ALLEGRO_KEY_MINUS) && !mMinusdown)
	{
		mMinusdown = true;
		int tmpMode = GET_GAME->getUnitManager()->GetCurrentMode();

		GameMessage* pMessage = new ChangeModeValueMessage(tmpMode, false);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'ctrl' current weights are saved
	if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL) && al_key_down(&keyState, ALLEGRO_KEY_S) && !mCTRLdown)
	{
		mCTRLdown = true;
		mSdown = true;

		GameMessage* pMessage = new SaveValuesMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	/*//left mouse click
	al_get_mouse_state(&mouseState);
	if (al_mouse_button_down(&mouseState, 1))
	{
	Vector2D pos(mouseState.x, mouseState.y);
	GameMessage* pMessage = new PlayerMoveToMessage(pos);
	MESSAGE_MANAGER->addMessage(pMessage, 0);
	}*/

	/*//if 's' key is pressed create a unit that WANDERS and SEEKS
	if (al_key_down(&keyState, ALLEGRO_KEY_S) && !mSdown)
	{
		mSdown = true;
		GameMessage* pMessage = new UnitCreateWanderSOFMessage(false);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'f' key is pressed create a unit that WANDERS and FLEES
	if (al_key_down(&keyState, ALLEGRO_KEY_F) && !mFdown)
	{
		mFdown = true;
		GameMessage* pMessage = new UnitCreateWanderSOFMessage(true);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}*/

	/*//if 'i' key is pressed toggle the info
	if (al_key_down(&keyState, ALLEGRO_KEY_I) && !mIdown)
	{
		mIdown = true;
		GameMessage* pMessage = new ToggleDisplayInfoMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}*/

	/*//if 'v' key is pressed select velocity
	if (al_key_down(&keyState, ALLEGRO_KEY_V) && !mVdown)
	{
		mVdown = true;
		GameMessage* pMessage = new ChangeModeMessage(0);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'r' key is pressed select detection radius
	if (al_key_down(&keyState, ALLEGRO_KEY_R) && !mRdown)
	{
		mRdown = true;
		GameMessage* pMessage = new ChangeModeMessage(1);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	//if 'a' key is pressed select angular velocity
	if (al_key_down(&keyState, ALLEGRO_KEY_A) && !mAdown)
	{
		mAdown = true;
		GameMessage* pMessage = new ChangeModeMessage(2);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}*/

	// check to see if you're still pressing the button so you can't create or delete a unit by just holding the key
	if (!al_key_down(&keyState, ALLEGRO_KEY_C)) { mCdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_S)) { mSdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_A)) { mAdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_I)) { mIdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_D)) { mDdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_EQUALS)) { mPlusdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_MINUS)) { mMinusdown = false; }
	if (!al_key_down(&keyState, ALLEGRO_KEY_LCTRL)) { mCTRLdown = false; }
	//if (!al_key_down(&keyState, ALLEGRO_KEY_F)) { mFdown = false; }
	//if (!al_key_down(&keyState, ALLEGRO_KEY_V)) { mVdown = false; }
	//if (!al_key_down(&keyState, ALLEGRO_KEY_R)) { mRdown = false; }
}

Vector2D InputManager::getInputMousePos()
{
	//create mouse text
	std::stringstream mousePos;
	Vector2D tmp(mouseState.x, mouseState.y);
	return tmp;
	//mousePos << tmp.setX(mouseState.x) << ":" << mouseState.y;
}
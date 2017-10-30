#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>
#include <stdio.h>

class Game;
class Vector2D;

class InputManager : public Trackable
{
	private :
		// bools that keep track of whether or not a key is still being pressed (sort of a way to cheat in "al_key_up")
		// assignment 2
		//bool mSdown, mFdown, mDdown, mIdown, mPlusdown, mMinusdown, mVdown, mRdown, mAdown;
		//assignment 3
		bool mCdown, mSdown, mAdown, mCTRLdown, mIdown, mDdown, mMinusdown, mPlusdown, mTOGGLEdown;

		// mouse and keyboard state
		ALLEGRO_MOUSE_STATE mouseState;
		ALLEGRO_KEYBOARD_STATE keyState;

		// the mouse position
		std::stringstream mousePos;

		bool mShouldDisplayInfo = false;

	public :
		InputManager();
		~InputManager();

		bool init();

		void Update(); 
		
		Vector2D getInputMousePos();
};

#endif
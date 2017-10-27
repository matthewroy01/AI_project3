#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Trackable.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class UIManager : public Trackable
{
	private :
		bool Init();

		// the font
		ALLEGRO_FONT* mpFont;

		// for info display when pressing "I"
		bool mShouldDisplayInfo;

	public :
		UIManager();
		~UIManager();

		void doUI();

		void toggleShouldDisplayInfo() { mShouldDisplayInfo = !mShouldDisplayInfo; };
};

#endif
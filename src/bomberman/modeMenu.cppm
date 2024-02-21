module;

import viewAPI;
import Event;
import gameVars;
#include <iostream>

export module modeMenu;

export void loadMainTitleAssets( Assets &assets){

    assets.addTex("mainTitle.jpg");//1
    assets.addTex("menuBackground.png");//2
    assets.addTex("menuEntryBackground.png");//3
    assets.addTex("menuCursor.png");//4

    assets.addSoundBuffer("cursorMove.mp3");
    assets.addSoundBuffer("validateMenu.mp3");
    assets.selectMusic("Dire_Dire_Docks.ogg");
    

    //addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //MJOY: Main Joycontroller

}
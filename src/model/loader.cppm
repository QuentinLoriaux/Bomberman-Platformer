module;

#include <iostream>
#include <vector>
import viewAPI;
import tMode;

export module loader;



void loadMainTitleAssets( Assets &assets){

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

void loadGameAssets( Assets &assets){

    assets.addTex("mainTitle.jpg");//1
    assets.addTex("menuBackground.png");//2
    assets.addTex("menuEntryBackground.png");//3
    assets.addTex("menuCursor.png");//4

    assets.addSoundBuffer("cursorMove.mp3");
    assets.addSoundBuffer("validateMenu.mp3");
    assets.selectMusic("Dire_Dire_Docks.ogg");
    

}



export void loadAssets(mode &gameMode, Assets &assets){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(assets); break;
        case EDITOR : loadMainTitleAssets(assets); break;
        case GAME : loadGameAssets(assets); break;
        case WIN_SCREEN : loadMainTitleAssets(assets); break;
    }

}




module;

#include <iostream>
#include <vector>
import viewAPI;
import tMode;

export module loader;






void loadMainTitleAssets( std::vector<Texture> &textureList,
                          std::vector<SoundBuffer> &soundBufferList,
                          Music &musique){

    textureList.push_back(Texture("mainTitle.jpg"));//1
    textureList.push_back(Texture("menuBackground.png"));//2
    textureList.push_back(Texture("menuEntryBackground.png"));//3
    textureList.push_back(Texture("menuCursor.png"));//4


    soundBufferList.push_back(SoundBuffer("cursorMove.mp3"));//1
    soundBufferList.push_back(SoundBuffer("validateMenu.mp3"));//2
    musique.openFromFile("Dire_Dire_Docks.ogg");//3
    

    //addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //MJOY: Main Joycontroller

}


export void loadAssets(mode &gameMode,
                       std::vector<Texture> &textureList,
                       std::vector<SoundBuffer> &soundBufferList,
                       Music &musique){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(textureList, soundBufferList, musique); break;
        case EDITOR : loadMainTitleAssets(textureList, soundBufferList, musique); break;
        case GAME : loadMainTitleAssets(textureList, soundBufferList, musique); break;
        case WIN_SCREEN : loadMainTitleAssets(textureList, soundBufferList, musique); break;
    }

}




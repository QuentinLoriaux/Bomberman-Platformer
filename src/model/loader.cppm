module;

#include <iostream>
#include <vector>
import viewAPI;
import tMode;

export module loader;



export void quitGame(mode &gameMode){gameMode = END;std::cout << "YESSS\n";}



void loadMainTitleAssets( std::vector<Texture> &textureList,
                          std::vector<Sprite> &spriteList,
                          std::vector<Sound> &soundList,
                          Music &musique){

    textureList.push_back(Texture("mainTitle.jpg"));
    textureList.push_back(Texture("menuBackground.png"));//To ADD
    textureList.push_back(Texture("menuEntryBackground.png"));//To ADD
    textureList.push_back(Texture("menuCursor.png"));//To ADD
    spriteList.push_back(Sprite(textureList[1]));
    spriteList.push_back(Sprite(textureList[2]));
    spriteList.push_back(Sprite(textureList[3]));
    spriteList.push_back(Sprite(textureList[4]));

    //textList.push_back(Text("Bomberman Plateformer!", fontList[0], 50));

    soundList.push_back(Sound("cursorMove.mp3"));
    soundList.push_back(Sound("validateMenu.mp3"));
    std::cout << "toto\n";
    musique.openFromFile("Dire_Dire_Docks.ogg");
    

    //addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //MJOY: Main Joycontroller

}


export void loadAssets(mode gameMode,
                       std::vector<Texture> &textureList,
                       std::vector<Sprite> &spriteList,
                       std::vector<Sound> &soundList,
                       Music &musique){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(textureList, spriteList, soundList, musique); break;
        case EDITOR : loadMainTitleAssets(textureList, spriteList, soundList, musique); break;
        case GAME : loadMainTitleAssets(textureList, spriteList, soundList, musique); break;
        case WIN_SCREEN : loadMainTitleAssets(textureList, spriteList, soundList, musique); break;
    }

}




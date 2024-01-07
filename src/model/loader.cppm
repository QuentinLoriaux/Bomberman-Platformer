module;

#include <vector>
import viewAPI;
import tMode;

export module loader;



export mode quitGame(){ return END; }



void loadMainTitleAssets(std::vector<Sprite> &spriteList,
                          std::vector<Sound> &soundList,
                          std::vector<Music> &musicList){

    spriteList.push_back(Sprite("mainTitle.jpg"));
    spriteList.push_back(Sprite("menuBackground.png"));//To ADD
    spriteList.push_back(Sprite("menuEntryBackground.png"));//To ADD
    spriteList.push_back(Sprite("menuCursor.png"));//To ADD
    

    //textList.push_back(Text("Bomberman Plateformer!", fontList[0], 50));

    soundEffects.push_back(Sound("cursorMove.mp3"));
    soundEffects.push_back(Sound("validateMenu.mp3"));
    musicList.push_back(Music("Dire_Dire_Docks.ogg"));
    

    //addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //MJOY: Main Joycontroller

}


export void loadAssets(mode gameMode,
                       std::vector<Sprite> &spriteList,
                       std::vector<Sound> &soundList,
                       std::vector<Music> &musicList){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(std::vector<Sprite> &spriteList,
                                              std::vector<Sound> &soundList,
                                              std::vector<Music> &musicList); break;
        case EDITOR : loadMainTitleAssets(std::vector<Sprite> &spriteList,
                                              std::vector<Sound> &soundList,
                                              std::vector<Music> &musicList); break;
        case GAME : loadMainTitleAssets(std::vector<Sprite> &spriteList,
                                              std::vector<Sound> &soundList,
                                              std::vector<Music> &musicList); break;
        case WIN_SCREEN : loadMainTitleAssets(std::vector<Sprite> &spriteList,
                                              std::vector<Sound> &soundList,
                                              std::vector<Music> &musicList); break;
    }

}




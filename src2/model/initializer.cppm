module;

import tMode;
import viewAPI;
import Event;

import Menu;
import Board;

#include <vector>
#include <any>
#include <iostream>


export module initializer;

export void quitGame(mode &gameMode){gameMode = END;}
export void testSound(Assets &assets){assets.getSfx(0).play();}

export class GameVariables{
    public :

        //MAIN_TITLE
        std::vector<MenuEntry> menu;
        menuState menuState;
        int menuCursor;

        //GAME
        Board board;

};

// void initMainTitle(Event &event,
//                    std::vector<Font> &fontList,
//                    std::vector<Text> &textList,

//                    mode &gameMode,
//                    std::vector<MenuEntry> &menu,
//                    int &menuCursor,
//                    menuState &menuState){
   
//     menuCursor = 0;
//     menuState = MENU_MAIN_TITLE;

//     menu.push_back(MenuEntry(loadSoloMenu, std::ref(menuState))); //0
//     menu.push_back(MenuEntry(loadMultiMenu, std::ref(menuState))); //1
//     menu.push_back(MenuEntry(loadEditorFromMenu, std::ref(gameMode))); //2
//     menu.push_back(MenuEntry(quitGame, std::ref(gameMode))); //3

//     //Il faudra adapter la taille du texte à la fenêtre
//     textList.push_back(Text("SOLO", fontList[0], 50)); //1
//     textList.push_back(Text("MULTIPLAYER", fontList[0], 50)); //2
//     textList.push_back(Text("EDITOR", fontList[0], 50)); //3
//     textList.push_back(Text("QUIT", fontList[0], 50)); //4


//     // EventBinding evProceed(proceedMenu, std::ref(menu), std::ref(menuCursor));
//     //     evProceed.addTypes(ENTER);
//     //     eventsMonitored.push_back(evProceed); //1

//     // EventBinding evBack(backMenu, std::ref(menuState));
//     //     evBack.addTypes(BACKSPACE);
//     //     eventsMonitored.push_back(evBack); //2
    

// }

void initGame(Event &event, TextManager texts, GameVariables &gameVars){
    std::cout <<"yo\n";
}


export void initialize(mode &gameMode,
                       Event &event,
                       TextManager &texts,

                       GameVariables &gameVars
                       
                       ){
    
    switch (gameMode){
        case MAIN_TITLE : initGame(event, texts,gameVars); break;
        case EDITOR : initGame(event, texts, gameVars); break;
        case GAME : initGame(event, texts, gameVars); break;
        case WIN_SCREEN : initGame(event, texts, gameVars); break;
    }

}

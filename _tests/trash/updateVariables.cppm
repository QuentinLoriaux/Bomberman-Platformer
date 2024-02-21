module;

import tMode;
import viewAPI;
import Event;
import initializer;

#include <iostream>

export module updateVariables;


void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    std::cout <<"yo\n";
}

export void updateVars(mode &gameMode,
                       Event &event,
                       TextManager &texts,
                       GameVariables &gameVars
                       ){

    switch (gameMode){
        case MAIN_TITLE : updateGame(event, texts,gameVars); break;
        case EDITOR : updateGame(event, texts, gameVars); break;
        case GAME : updateGame(event, texts, gameVars); break;
        case WIN_SCREEN : updateGame(event, texts, gameVars); break;
    }

}
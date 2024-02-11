module;

import tMode;
import viewAPI;
import Event;

export module updateVariables;




xport void updateVars(mode &gameMode,
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
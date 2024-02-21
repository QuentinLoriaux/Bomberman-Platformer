module;

import viewAPI;
import Event;
import gameVars;

import modeGame;
import modeMenu;
#include <functional>

export module modes;



// ========================== Test functions ==========================

export void quitGame(mode &gameMode){gameMode = END;}
export void testSound(Assets &assets){assets.getSfx(0).play();}



// ========================== Main functions ==========================



export void loadAssets(mode &gameMode, Assets &assets){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(assets); break;
        case EDITOR : loadMainTitleAssets(assets); break;
        case GAME : loadGameAssets(assets); break;
        case WIN_SCREEN : loadMainTitleAssets(assets); break;
    }

}


export void initialize(mode &gameMode,
                       Event &event,
                       TextManager &texts,

                       GameVariables &gameVars,
                       Assets &assets
                       
                       ){
    event.addEvent(quitGame, std::ref(gameMode));
    event.addBinding(0, CROSS, ESC);//ESC for testing
    


    switch (gameMode){
        case MAIN_TITLE : initGame(event, texts, gameVars, assets); break;
        case EDITOR : initGame(event, texts, gameVars, assets); break;
        case GAME : initGame(event, texts, gameVars, assets); break;
        case WIN_SCREEN : initGame(event, texts, gameVars, assets); break;
    }

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

export void display(mode &gameMode,
                       RenderWindow &rWindow,
                       Assets &assets,
                       TextManager &texts,
                       GameVariables &gameVars
                       ){

    rWindow.clear();
    switch (gameMode){
        case MAIN_TITLE : dispGame(rWindow, assets, texts,gameVars); break;
        case EDITOR : dispGame(rWindow, assets, texts,gameVars); break;
        case GAME : dispGame(rWindow, assets, texts,gameVars); break;
        case WIN_SCREEN : dispGame(rWindow, assets, texts,gameVars); break;
    }
    rWindow.display();
}

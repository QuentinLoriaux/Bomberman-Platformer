module;

import viewAPI;
import Event;
import gameVars;

import modeGame;
import modeEditor;
import modeMenu;
#include <functional>

export module modes;



// ========================== Test functions ==========================

export void quitGame(mode &gameMode){gameMode = END;}
export void resizeWindow(Event& event){event.resize();}
export void testSound(Assets &assets){assets.getSfx(0).play();}



// ========================== Main functions ==========================



export void loadAssets(mode &gameMode, Assets &assets){
    
    switch (gameMode){
        case MAIN_TITLE : loadMainTitleAssets(assets); break;
        case EDITOR : loadEditorAssets(assets); break;
        case GAME : loadGameAssets(assets); break;
        case WIN_SCREEN : loadMainTitleAssets(assets); break;
        case END : break;
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

    event.addEvent(resizeWindow, std::ref(event));
    event.addBinding(1, RESIZE);


    switch (gameMode){
        case MAIN_TITLE : initGame(event, texts, gameVars, assets); break;
        case EDITOR : initEditor(event, texts, gameVars, assets); break;
        case GAME : initGame(event, texts, gameVars, assets); break;
        case WIN_SCREEN : initGame(event, texts, gameVars, assets); break;
        case END : break;
    }

}

export void updateVars(mode &gameMode,
                       Event &event,
                       TextManager &texts,
                       GameVariables &gameVars
                       ){

    switch (gameMode){
        case MAIN_TITLE : updateGame(event, texts,gameVars); break;
        case EDITOR : updateEditor(event, texts, gameVars); break;
        case GAME : updateGame(event, texts, gameVars); break;
        case WIN_SCREEN : updateGame(event, texts, gameVars); break;
        case END : break;
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
        case MAIN_TITLE : dispGame(rWindow, assets, texts, gameVars); break;
        case EDITOR : dispEditor(rWindow, assets, texts, gameVars); break;
        case GAME : dispGame(rWindow, assets, texts, gameVars); break;
        case WIN_SCREEN : dispGame(rWindow, assets, texts, gameVars); break;
        case END : break;
    }
    rWindow.display();
}

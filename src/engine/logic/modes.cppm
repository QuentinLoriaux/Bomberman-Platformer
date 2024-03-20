module;

import viewAPI;
import Event;
import gameVars;

import modeGame;
import modeEditor;
import modeMenu;
#include <functional>
#include <iostream>

export module modes;



// ========================== Test functions ==========================

export void quitGame(mode &gameMode){gameMode = END;}
export void resizeWindow(Event& event){event.resize();}
export void testSound(Assets &assets){assets.addSound(0);}
export void changeMode(mode &gameMode){gameMode = (gameMode == GAME)? EDITOR:GAME;}



// ========================== Main functions ==========================



export void loadAssets(GameVariables& gameVars){

    gameVars.assets.addTex("notFound.png");
    gameVars.assets.addSoundBuffer("notFound.mp3");
    gameVars.assets.selectMusic("notFound.ogg");

    gameVars.texts.addFont("arial.ttf");
    gameVars.texts.addText("Not Found", 0, 50);
    
    switch (gameVars.params->gameMode){
        // case MAIN_TITLE : loadMainTitleAssets(assets); break;
        case GAME : loadGameAssets(gameVars.assets); break;
        case EDITOR : loadEditorAssets(gameVars.assets); break;
        // case WIN_SCREEN : loadMainTitleAssets(assets); break;
        case END : break;
        default: break;
    }

    gameVars.assets.addSprite(0,0);

}


export void initialize(GameVariables& gameVars){
    gameVars.event.addEvent(quitGame, std::ref(gameVars.params->gameMode));
    gameVars.event.addBinding(0, CROSS, ESC);//ESC for testing

    gameVars.event.addEvent(resizeWindow, std::ref(gameVars.event));
    gameVars.event.addBinding(1, RESIZE);

    gameVars.event.addEvent(changeMode, std::ref(gameVars.params->gameMode));
    gameVars.event.addBinding(2 , BACKSPACE);

    switch (gameVars.params->gameMode){
        // case MAIN_TITLE : initGame(event, texts, gameVars, assets); break;
        case GAME : initGame(gameVars); break;
        case EDITOR : initEditor(gameVars); break;
        // case WIN_SCREEN : initGame(event, texts, gameVars, assets); break;
        case END : break;
        default : break;
    }



}

export void updateVars(GameVariables &gameVars){

    switch (gameVars.params->gameMode){
        // case MAIN_TITLE : updateGame(event, texts,gameVars); break;
        case GAME : updateGame(gameVars); break;
        case EDITOR : updateEditor(gameVars); break;
        // case WIN_SCREEN : updateGame(event, texts, gameVars); break;
        case END : break;
        default : break;
    }

}

export void display(GameVariables &gameVars){

    gameVars.rWindow->clear();
    
    switch (gameVars.params->gameMode){
        // case MAIN_TITLE : dispGame(rWindow, assets, texts, gameVars); break;
        case GAME : dispGame(gameVars); break;
        case EDITOR : dispEditor(gameVars); break;
        // case WIN_SCREEN : dispGame(rWindow, assets, texts, gameVars); break;
        case END : break;
        default: break;
    }
    gameVars.rWindow->display();
}

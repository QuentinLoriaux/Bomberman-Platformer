module;

import viewAPI;
import Event;
import gameVars;
import assetsBindings;
import Entity;
import Board;
#include <vector>
#include <cstdlib>

export module modeEditor;



export void loadEditorAssets(Assets &assets){
    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    assets.addTex("monster.png");//3
    assets.addTex("bomberman.png");//4
    assets.addTex("editorButtons.png");//5
    assets.addTex("editorBloc.png");//6
    assets.addTex("cursor.png");//7

    assets.selectMusic("editor.ogg");

}


export void initEditor(Event &event, TextManager& texts, GameVariables& gameVars, Assets& assets){

    event.window->hideCursor();

    //background
    assets.addSprite(1);

    //Mouse
    assets.addSprite(7);

}


export void updateEditor(Event &event, TextManager texts, GameVariables &gameVars){

}

export void dispEditor(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){

    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1));


    //draw cursor
    float xCursor; float yCursor;
    rWindow.getCursorPos(xCursor, yCursor);
    assets.getSp(2).setPos(xCursor, yCursor);
    rWindow.draw(assets.getSp(2));

}
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

    assets.selectMusic("editor.ogg");

}


export void initEditor(Event &event, TextManager& texts, GameVariables& gameVars, Assets& assets){

    //background
    assets.addSprite(1);


}


export void updateEditor(Event &event, TextManager texts, GameVariables &gameVars){

}

export void dispEditor(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){

    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1));


}
module;

import viewAPI;
import Event;
import gameVars;
#include <iostream>

export module modeGame;



export void loadGameAssets(Assets &assets){

    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    // assets.addTex("menuEntryBackground.png");//3
    // assets.addTex("menuCursor.png");//4

    assets.addSoundBuffer("cursorMove.mp3");
    assets.addSoundBuffer("validateMenu.mp3");
    assets.selectMusic("Dire_Dire_Docks.ogg");
    

}

export void initGame(Event &event, TextManager& texts, GameVariables& gameVars, Assets& assets){
    std::cout <<"initGame\n";

    //background
    assets.addSprite(1);
    float xSize; float ySize;
    event.window->getSize(xSize, ySize);
    assets.getSp(1).resize(xSize, ySize);

    //blocs
    gameVars.board.createSprites(assets);
    gameVars.board.textureBinding(assets);
    
    float xStart; float yStart; 
    gameVars.board.updateBlocLength(*event.window, xStart, yStart);
    float side = gameVars.board.blocLength;


    float xOffset; float yOffset;
    for (auto k = 0; k < gameVars.board.cases.size(); k++){
        gameVars.board.computeOffset(k, xOffset, yOffset);

        auto sp = assets.getSp(2+k);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
    } 

}

export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    std::cout <<"updateGame\n";
}

export void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);

    //draw background
    rWindow.draw(assets.getSp(1));



    //draw Board
    gameVars.board.textureBinding(assets);//Idéalement, ne le faire que pour sprites changés
    float xStart; float yStart; 
    gameVars.board.updateBlocLength(rWindow, xStart, yStart);
    float side = gameVars.board.blocLength;



    float xOffset; float yOffset;
    for (auto k = 0; k < gameVars.board.cases.size(); k++){
        gameVars.board.computeOffset(k, xOffset, yOffset);

        auto sp = assets.getSp(2+k);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }
    // assets.getSp(1).setPos(xStart, yStart);
    // rWindow.draw(assets.getSp(1));

    //draw Entities

}
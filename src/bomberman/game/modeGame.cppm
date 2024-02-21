module;

import viewAPI;
import Event;
import gameVars;
#include <iostream>

export module modeGame;



export void loadGameAssets(Assets &assets){

    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    assets.addTex("monster.png");//3
    assets.addTex("bomberman.png");//4
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
    
    //Board
    gameVars.board.createSprites(assets);

    //Entities
    gameVars.board.createMonsters(assets);
    // gameVars.board.createPlayers(assets, gameVars.nbPlayers);//we need to add events for each player!

}

export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    std::cout <<"updateGame\n";
}

export void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){

    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1));



    float xStart; float yStart; 
    gameVars.board.updateBlocLength(rWindow, xStart, yStart);
    float side = gameVars.board.blocLength;
    float xOffset; float yOffset;

    //draw Board
    gameVars.board.textureBinding(assets);//Idéalement, ne le faire que pour sprites changés? OSEF en vrai
    for (int k = 0; k < gameVars.board.cases.size(); k++){
        gameVars.board.computeOffset(k, xOffset, yOffset);

        auto sp = assets.getSp(2+k);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }

    //draw Entities
    //change sprite according to animation
    float xSize; float ySize;
    for (int k = 0; k < gameVars.board.entities.size(); k++){
        //compute offset
        gameVars.board.sharePosition(k, xOffset, yOffset);

        auto sp = assets.getSp(2+gameVars.board.cases.size()+k);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        gameVars.board.shareSize(k, xSize, ySize);
        sp.resize(side*xSize, side*ySize);
        rWindow.draw(sp);
    }

}
module;

import viewAPI;
import Event;
import gameVars;
import assetsBindings;
import Entity;
#include <iostream>
#include <vector>
#include <memory>

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
    auto board = &(gameVars.board);


    //background
    assets.addSprite(1);
    
    //Board
    for (unsigned int k = 0 ; k < gameVars.board.cases.size() ; k++){
        assets.addSprite(2);
    }

    //Entities
    for (unsigned int k = 0 ; k < board->cases.size() ; k++){
        if (board->cases[k]->monsterSpawn){
            board->addMonster(k);
            assets.addSprite(3);
        }
    }

    int k = 0; int cpt = 0;
    while (cpt < gameVars.nbPlayers){
        if (board->cases[k]->playerSpawn){
            board->addPlayer(k);
            auto& player = *(board->players[cpt]);
            player.playerId = cpt;
            
            // add Bindings for the player (les events commencent à 2)
            event.addEvent(jump, std::ref(player));
            event.addBinding(2, SPACE);

            event.addEvent(move, std::ref(player));
            event.addBinding(3, D);

            assets.addSprite(4);
            cpt++;
            std::cout <<"yes\n";
        }
        k++;
    }

}








export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    gameVars.board.updateEntityPos();
}









export void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    auto board = &(gameVars.board);
    int nbCases = board->cases.size();
    int nbEntites = board->entities.size();



    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1));






    float xStart; float yStart; 
    board->updateBlocLength(rWindow, xStart, yStart);
    float side = board->blocLength;

    float xOffset; float yOffset;



    //draw Board
    for (unsigned int k = 0; k < nbCases; k++){
        auto sp = assets.getSp(2+k);
        board->setBlocSprite(sp, k);

        board->blocOffset(k, xOffset, yOffset);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }



    //draw Entities
    float xSize; float ySize;
    for (unsigned int k = 0; k < nbEntites; k++){
        auto ent = board->entities[k]; 
        xOffset = ent->xPos; yOffset = ent->yPos;
        xSize = ent->xSize;  ySize = ent->ySize;
        

        auto sp = assets.getSp(2 + nbCases + k);
        //change sprite according to animation
        board->setEntitySprite(sp, k);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        // board->shareSize(k, xSize, ySize);
        sp.resize(side*xSize, side*ySize);
        rWindow.draw(sp);
    }


}
module;

import viewAPI;
import Event;
import gameVars;
import assetsBindings;
import Entity;
import Board;
#include <iostream>
#include <vector>
#include <memory>

export module modeGame;



export void loadGameAssets(Assets &assets){

    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    assets.addTex("monster.png");//3
    assets.addTex("bomberman.png");//4


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
    Entity::setWidth(board->width);
    for (unsigned int k = 0 ; k < board->cases.size() ; k++){
        if (board->cases[k]->monsterSpawn){
            board->addMonster(k);
            assets.addSprite(3);
        }
    }

    int k = 0; int cpt = 0; int nbActions = 7;
    while (cpt < gameVars.nbPlayers){
        if (board->cases[k]->playerSpawn){
            board->addPlayer(k);
            auto& player = *(board->players[cpt]);
            player.playerId = cpt;
            
            // add Bindings for the player (les events commencent à 2)
            event.addEvent(jump, std::ref(player));
            event.addBinding(2 + nbActions*cpt, SPACE);

            event.addEvent(walkLeft, std::ref(player));
            event.addBinding(3 + nbActions*cpt, Q);

            event.addEvent(stopWalkLeft, std::ref(player));
            event.addBinding(4 + nbActions*cpt, Q_RELEASE);
            
            event.addEvent(walkRight, std::ref(player));
            event.addBinding(5 + nbActions*cpt, D);
            
            event.addEvent(stopWalkRight, std::ref(player));
            event.addBinding(6 + nbActions*cpt, D_RELEASE);

            event.addEvent(placeBomb, std::ref(player), std::ref(*board));
            event.addBinding(7 + nbActions*cpt, TAB);

            event.addEvent(debug, std::ref(player));
            event.addBinding(8 + nbActions*cpt, ENTER);

            assets.addSprite(4);
            cpt++;
            std::cout <<"yes\n";
        }
        k++;
    }

    board->setFirstTimeEntityPos();
}








export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    auto board = &(gameVars.board);

    for (unsigned int k = 0 ; k < board->entities.size() ; k++){
        auto& ent = *(board->entities[k]);
        ent.tryPos();
        ent.updateBlocIndex();
        ent.updateCloseBlocs();
        for (auto it = ent.closeBlocs.begin(); it != ent.closeBlocs.end(); it++){
            auto& bloc = *(board->cases[*it]);
            if (! bloc.crossable){
                direction dir = ent.collideBloc(*it);
                ent.correctPos(dir);
                
            }
        }
        ent.updatePos();
    }
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
    float side = board->blocLength;//unit reference

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
        auto sp = assets.getSp(2 + nbCases + k);
        auto ent = board->entities[k]; 
        ent->setSprite(sp);//change sprite according to animation 

        xOffset = ent->xPos*side; yOffset = ent->yPos*side;
        xSize = ent->xSize*side;  ySize = ent->ySize*side;
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(xSize, ySize, ent->facing == LEFT);
        rWindow.draw(sp);
    }


}
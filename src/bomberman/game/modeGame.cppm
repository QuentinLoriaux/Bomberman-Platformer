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
#include <chrono>
#include <string>

export module modeGame;



export void loadGameAssets(Assets &assets){

    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    assets.addTex("monster.png");//3
    assets.addTex("bomberman.png");//4

    assets.addSpriteVec();//1 : blocs
    assets.addSpriteVec();//2 : entities


    assets.addSoundBuffer("explosion.mp3");//1
    assets.addSoundBuffer("playerWins.mp3");//2
    assets.addSoundBuffer("gameOver.mp3");//3
    assets.selectMusic("gameBattle.ogg");
    
}






export void initGame(Event &event, TextManager& texts, GameVariables& gameVars, Assets& assets){
    std::cout <<"initGame\n";
    auto board = &(gameVars.board);

   

    //background
    assets.addSprite(1,0);
    
    //Board
    for (unsigned int k = 0 ; k < gameVars.board.cases.size() ; k++){
        assets.addSprite(2,1);
    }

    //Entities

    //Monsters
    Entity::setBoardDims(board->width, board->height);
    for (unsigned int k = 0 ; k < board->cases.size() ; k++){
        if (board->cases[k]->monsterSpawn){
            board->addMonster(k);
            assets.addSprite(3,2);
        }
    }

    //players
    int k = 0; int cpt = 0; int nbActions = 7; int actionsOffset = event.eventList.size();
    while (cpt < gameVars.nbPlayers){
        if (board->cases[k]->playerSpawn){
            board->addPlayer(k);
            auto& player = *(board->players[cpt]);
            player.playerId = cpt;
            
            // add Bindings for the player (les events commencent à 2)
            event.addEvent(jump, std::ref(player));
            event.addBinding(actionsOffset + nbActions*cpt, SPACE);

            event.addEvent(walkLeft, std::ref(player));
            event.addBinding(actionsOffset + 1 + nbActions*cpt, Q);

            event.addEvent(stopWalkLeft, std::ref(player));
            event.addBinding(actionsOffset + 2 + nbActions*cpt, Q_RELEASE);
            
            event.addEvent(walkRight, std::ref(player));
            event.addBinding(actionsOffset + 3 + nbActions*cpt, D);
            
            event.addEvent(stopWalkRight, std::ref(player));
            event.addBinding(actionsOffset + 4 + nbActions*cpt, D_RELEASE);

            event.addEvent(placeBomb, std::ref(player), std::ref(*board));
            event.addBinding(actionsOffset + 5 + nbActions*cpt, TAB);

            event.addEvent(debug, std::ref(player));
            event.addBinding(actionsOffset + 6 + nbActions*cpt, ENTER);

            assets.addSprite(4,2);
            cpt++;
            std::cout <<"yes\n";
        }
        k++;
    }
    board->setFirstTimeEntityPos();

}








export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    auto board = &(gameVars.board);



    //Blocs
    for (unsigned int k = 0 ; k < board->cases.size() ; k++){
        auto bloc = board->cases[k];
        if (bloc->displayId == 6){
            std::shared_ptr<BombBloc> bBloc = std::dynamic_pointer_cast<BombBloc>(bloc);
            if (bBloc->endedCountDown()){
                gameVars.soundPlay = board->explode(k, *(bBloc->player));
                //add explosion sound effect
            }
        }
        if (bloc->displayId == 7){
                std::shared_ptr<BombFlare> fBloc = std::dynamic_pointer_cast<BombFlare>(bloc);
                if (fBloc->endedLifeTime()){
                    
                    board->freeSpace(k);
                }
        }
 
    }

    //Entités
    for (unsigned int k = 0 ; k < board->entities.size() ; k++){
        auto& ent = *(board->entities[k]);
        if (ent.isAlive()){
            ent.tryPos();
            ent.updateBlocIndex();
            ent.updateCloseBlocs();
            for (auto it = ent.closeBlocs.begin(); it != ent.closeBlocs.end(); it++){
                auto& bloc = *(board->cases[*it]);
                if (bloc.damaging){
                    ent.hp--;
                }
                if (! bloc.crossable){
                    direction dir = ent.collideBloc(*it);
                    ent.correctPos(dir);
                    
                }
                
            }
            ent.updatePos();
        }
    }




}











export void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    auto board = &(gameVars.board);
    unsigned int nbCases = board->cases.size();
    unsigned int nbEntites = board->entities.size();
    
    //sound
    switch (gameVars.soundPlay){
        case 1: //explosion
            assets.addSound(1);
            break;
        default:
            break;
    }
    gameVars.soundPlay = 0;
    assets.freeSounds();

    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1,0).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1,0));






    float xStart; float yStart; 
    board->updateBlocLength(rWindow, xStart, yStart);
    float side = board->blocLength;//unit reference

    float xOffset; float yOffset;



    //draw Board
    for (unsigned int k = 0; k < nbCases; k++){
        auto sp = assets.getSp(k,1);
        board->setBlocSprite(sp, k);

        board->blocOffset(k, xOffset, yOffset);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }



    //draw Entities
    unsigned int livingPlayers = 0;
    unsigned int livingEntities = 0;

    float xSize; float ySize;
    for (unsigned int k = 0; k < nbEntites; k++){
        auto sp = assets.getSp(k,2);
        auto ent = board->entities[k]; 
        ent->setSprite(sp);//change sprite according to animation 

        if (ent->isAlive()){
            livingEntities ++;
            if (ent->entityId == 0){livingPlayers++;}
            xOffset = ent->xPos*side; yOffset = ent->yPos*side;
            xSize = ent->xSize*side;  ySize = ent->ySize*side;
            sp.setPos(xStart + xOffset, yStart + yOffset);
            sp.resize(xSize, ySize, ent->facing == LEFT);
            rWindow.draw(sp);
        }
    }


                
    //end of the game

    //text to print
    if (texts.textList.size()== 1){
        switch (livingPlayers){
            case 0 ://everyone loses
                texts.addText("Game Over - no Winner", 0, 50);
                assets.addSound(3);
                break;
            case 1 ://a player wins
                if (livingPlayers == livingEntities){
                    int numWin = 0;
                    for (unsigned int k = 0; k < gameVars.nbPlayers; k++){
                        auto player = board->players[k]; 
                        if (player->isAlive()){
                            numWin = k+1;
                            break;
                        }
                    }
                    texts.addText("Game Over - The winner is Player " + std::to_string(numWin) + " !", 0, 50);
                    assets.addSound(2);
                }
                break;
            default:
                break;
        }
    }

    //Display text
    if (livingPlayers == 0 || (livingPlayers == livingEntities && livingPlayers == 1)){
        static std::chrono::_V2::steady_clock::time_point timer = std::chrono::steady_clock::now();
        const std::chrono::duration<double> second(1.0);
        auto now = std::chrono::steady_clock::now();

        auto finalText = texts.getText(1);
        finalText.setPos(0, yScreen/2);
        rWindow.draw(finalText);

        if (now - timer > 5*second){
            *(gameVars.gameMode) = END;
        }

    }
        


}
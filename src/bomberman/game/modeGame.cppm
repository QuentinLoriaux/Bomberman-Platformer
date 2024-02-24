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
            int num = board->addPlayer(k);
            auto& player = dynamic_cast<Player&>(*(board->entities[num]));
            player.playerId = cpt;
            
            add Bindings for the player (les events commencent à 2)
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
    // board->createPlayers(assets, gameVars.nbPlayers);//we need to add events for each player!

}








export void updateGame(Event &event, TextManager texts, GameVariables &gameVars){
    gameVars.board.updateEntityPos();
}









export void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    static std::vector<int> monsterSprites = monsterTexBinding() ;
    static std::vector<int> bombermanSprites = bombermanTexBinding() ;
    static std::vector<int> boardSprites = boardTexBinding() ;
    auto board = &(gameVars.board);

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
    for (unsigned int k = 0; k < board->cases.size(); k++){
        board->blocOffset(k, xOffset, yOffset);

        auto sp = assets.getSp(2+k);
        sp.setTexRect(board->cases[k]->displayId, boardSprites);
        //plus tard, mettre les tableaux en static dans les classes
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }

    //draw Entities
    float xSize; float ySize;
    for (unsigned int k = 0; k < board->entities.size(); k++){
        board->sharePosition(k, xOffset, yOffset);

        auto sp = assets.getSp(2+board->cases.size()+k);
        //change sprite according to animation
        switch (board->entities[k]->entityId){
            case 0: //player
                sp.setTexRect(board->entities[k]->SpriteId, bombermanSprites);
                break;
            case 1: //monster
                sp.setTexRect(board->entities[k]->SpriteId, monsterSprites);
                break;
        }
        sp.setPos(xStart + xOffset, yStart + yOffset);
        board->shareSize(k, xSize, ySize);
        sp.resize(side*xSize, side*ySize);
        rWindow.draw(sp);
    }

}
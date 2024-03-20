module;

import Board;
import gameVars;
import parser;
#include <iostream>
#include <string>
#include <vector>
#include <memory>


export module Editor;


export void click(bool& clickPressed){clickPressed=true;}
export void release(bool& clickPressed){clickPressed=false;}

export void saveBoard(std::shared_ptr<BoardEditor>& board){//HERE
    std::vector<std::string> cases;
    for (unsigned int k = 0; k < board->cases.size(); k++){
        switch (board->cases[k]->displayId)
        {
        case 0:
            cases.push_back("Undefined");
            break;
        case 1:
            cases.push_back("Wall");
            break;
        case 2:
            cases.push_back("Air");
            break;
        case 3:
            cases.push_back("playerSpawn");
            break;
        case 4:
            cases.push_back("monsterSpawn");
            break;
        case 5:
            cases.push_back("BonusBloc");
            break;
        case 6:
            cases.push_back("BreakableWall");
            break;
        default:
            break;
        }
    }

    saveXML(board->width, board->height, cases);
}

//a transformer en méthode
export void expandBoard(GameVariables& gameVars){
    switch(gameVars.hoverSprite){
        case 1://left
            gameVars.board->width++;
            for (int k = 0; k < gameVars.board->height; k++){
                gameVars.board->cases.insert(gameVars.board->cases.begin() + ((k)*gameVars.board->width), std::make_shared<Air>());
                gameVars.assets.addSprite(2,2);
            }
            break;
        case 2://up
            gameVars.board->height++;
            for (int k = 0; k < gameVars.board->width; k++){
                gameVars.board->cases.insert(gameVars.board->cases.begin(), std::make_shared<Air>());
                gameVars.assets.addSprite(2,2);
            }
            break;
        case 3://right
            for (int k = 0; k < gameVars.board->height -1; k++){
                gameVars.board->cases.insert(gameVars.board->cases.begin() + ((k+1)*gameVars.board->width + k), std::make_shared<Air>());
                gameVars.assets.addSprite(2,2);
            }
            gameVars.board->width++;
            gameVars.board->cases.push_back(std::make_shared<Air>());
            gameVars.assets.addSprite(2,2);
            break;
        case 4://down
            gameVars.board->height++;
            for (int k = 0; k < gameVars.board->width; k++){
                gameVars.board->cases.push_back(std::make_shared<Air>());
                gameVars.assets.addSprite(2,2);
            }
            break;
        default:
            break;
    }
}
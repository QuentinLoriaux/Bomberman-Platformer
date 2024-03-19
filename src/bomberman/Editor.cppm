module;

import Board;
import parser;
#include <iostream>
#include <string>
#include <vector>


export module Editor;


export void click(bool& clickPressed){clickPressed=true;}
export void release(bool& clickPressed){clickPressed=false;}

export void saveBoard(Board& board){
    std::vector<std::string> cases;
    for (unsigned int k = 0; k < board.cases.size(); k++){
        switch (board.cases[k]->displayId)
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

    saveXML(board.width, board.height, cases);
}
module;

import viewAPI;
import Event;

import menu;
import Board;

#include <iostream>
#include <vector>


export module gameVars;


// ========================== Classes/Types ==========================


export typedef enum _Mode{
    MAIN_TITLE,
    EDITOR,
    GAME,
    WIN_SCREEN,
    END
} mode;

export class GameVariables{
    public :

        //MAIN_TITLE
        // std::vector<MenuEntry> menu;
        // menuState menuState;
        // int menuCursor;

        //GAME
        Board board;

        GameVariables(RenderWindow& rWindow): board(Board(rWindow)){}


};

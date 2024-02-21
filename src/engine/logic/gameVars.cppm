module;

import viewAPI;
import Event;

import menu;
import Board;

#include <iostream>



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
        int nbPlayers;
        Board board;


        GameVariables(RenderWindow& rWindow): nbPlayers(1), board(Board(rWindow)){}
        GameVariables(RenderWindow& rWindow, int _nbPlayers): nbPlayers(_nbPlayers), board(Board(rWindow)){}


};

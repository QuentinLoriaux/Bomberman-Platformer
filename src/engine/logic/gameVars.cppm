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

        //MODE
        mode* gameMode;

        //GAME
        int nbPlayers;
        int soundPlay;
        Board board;


        GameVariables(RenderWindow& rWindow, mode& _gameMode): nbPlayers(1), soundPlay(0), board(Board(rWindow)), gameMode(&_gameMode){}
        GameVariables(RenderWindow& rWindow, int _nbPlayers): nbPlayers(_nbPlayers), board(Board(rWindow)){}


};

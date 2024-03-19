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
        bool gameEnded;
        Board board;

        //EDITOR
        int hoverSprite;
        int hoverList;
        bool clickPressed;
        int selectedBloc;



        GameVariables(mode& _gameMode): gameMode(&_gameMode), nbPlayers(1), soundPlay(0), board(Board("./game_files/boards/map0.xml")){}
        // GameVariables(int _nbPlayers): nbPlayers(_nbPlayers), board(Board()){}


};

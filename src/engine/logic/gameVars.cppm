module;

import viewAPI;
import Event;
import menu;
import Board;

#include <iostream>
#include <memory>
#include <string>


export module gameVars;


// ========================== Classes/Types ==========================


export typedef enum _Mode{
    MAIN_TITLE,
    EDITOR,
    GAME,
    WIN_SCREEN,
    END
} mode;

export class GameParams{
    public :
        mode gameMode;
        int nbPlayers;
        std::string map;

        GameParams(mode _gameMode, int _nbPlayers, std::string _map): gameMode(_gameMode), nbPlayers(_nbPlayers), map(_map) {}

};

export class GameVariables{
    public :

        //MAIN_TITLE
        // std::vector<MenuEntry> menu;
        // menuState menuState;
        // int menuCursor;

        GameParams* params;
        RenderWindow* rWindow;
        Assets assets;
        TextManager texts;
        Event event;

        std::shared_ptr<Board> board;

        //GAME
        int soundPlay;
        bool gameEnded;

        //EDITOR
        int hoverSprite;
        int hoverList;
        bool clickPressed;
        int selectedBloc;



        GameVariables(GameParams& _params, RenderWindow& _rWindow):
        params(&_params), rWindow(&_rWindow), assets(Assets()), texts(TextManager()), event(Event(_rWindow)),
        soundPlay(0), gameEnded(false),
        hoverSprite(-1), hoverList(-1), clickPressed(false), selectedBloc(0){
            std::string parDef = "default";
            switch(_params.gameMode){
                case GAME:
                    board = (_params.map.compare(parDef)==0) ? std::make_shared<BoardGame>()
                            : std::make_shared<BoardGame>(_params.map);
                            
                    break;
                case EDITOR:
                    board = (_params.map.compare(parDef)==0) ? std::make_shared<BoardEditor>()
                            : std::make_shared<BoardEditor>(_params.map);
                    break;
                default: //should not happen
                    board = (_params.map.compare(parDef)==0) ? std::make_shared<BoardEditor>()
                            : std::make_shared<BoardEditor>(_params.map);
                    break;
            }
        }
        // GameVariables(mode& _gameMode): gameMode(&_gameMode), nbPlayers(1), soundPlay(0), board(Board("./game_files/boards/map0.xml")){}
        // GameVariables(int _nbPlayers): nbPlayers(_nbPlayers), board(Board()){}


};

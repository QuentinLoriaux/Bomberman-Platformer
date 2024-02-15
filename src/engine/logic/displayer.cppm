module;

import viewAPI;
import initializer;

export module displayer;



void dispGame(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    std::cout <<"yo\n";
    
    rWindow.draw(assets.getSp(1)); //draw background

    //draw Board
    
    rWindow.draw(assets.getSp(1));
}


export void display(mode &gameMode,
                       RenderWindow &rWindow,
                       Assets &assets,
                       TextManager &texts,
                       GameVariables &gameVars
                       ){

    rWindow.clear();
    switch (gameMode){
        case MAIN_TITLE : dispGame(rWindow, assets, texts,gameVars); break;
        case EDITOR : dispGame(rWindow, assets, texts,gameVars); break;
        case GAME : dispGame(rWindow, assets, texts,gameVars); break;
        case WIN_SCREEN : dispGame(rWindow, assets, texts,gameVars); break;
    }
    rWindow.display();
}

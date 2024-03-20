module;

import viewAPI;
import Event;
import gameVars;
import assetsBindings;
import Board;
import Editor;
#include <vector>
#include <cstdlib>
#include <iostream>
#include <memory>

export module modeEditor;



export void loadEditorAssets(Assets &assets){
    assets.addTex("background.jpg");//1
    assets.addTex("boardTextures.png");//2
    assets.addTex("monster.png");//3
    assets.addTex("bomberman.png");//4
    assets.addTex("editorButtons.png");//5
    assets.addTex("editorBloc.png");//6
    assets.addTex("cursor.png");//7

    //0 for non interactive sprites
    assets.addSpriteVec();// 1 : for interactive sprites
    assets.addSpriteVec();// 2 : for Board
    assets.addSpriteVec();// 3 : for blocMenu
    

    assets.selectMusic("editor.ogg");

}


export void initEditor(GameVariables& gameVars){
    std::cout << "test\n";
    Assets& assets = (gameVars.assets);
    Event& event = (gameVars.event);

    std::vector<int> buttonsSprites = editorButtonBinding();    
    std::vector<int> menuSprites = editorMenuBinding();    
    std::vector<int> boardSprites = boardTexBinding();
    event.window->hideCursor();

    // ======== Non Interactive Sprites ========

    //background
    assets.addSprite(1,0);//1
    //Board background
    assets.addSprite(5,0);//2
    assets.getSp(2,0).setTexRect(9,11,2,2);//just to get gray color, too lazy to implement rectangle

    //Mouse
    assets.addSprite(7,0);//3
    int actionsOffset = event.eventList.size(); 
    event.addEvent(click, std::ref(gameVars.clickPressed));
    event.addBinding(actionsOffset, CLICK_LEFT_PRESS);
    event.addEvent(release, std::ref(gameVars.clickPressed));
    event.addBinding(actionsOffset+1, CLICK_LEFT_RELEASE);

    //selected bloc
    gameVars.selectedBloc = 0;
    assets.addSprite(2,0);//4
    //selector
    assets.addSprite(6,0);//5
    assets.getSp(5,0).setTexRect(2, menuSprites);

    //Bloc Menu
    assets.addSprite(6,0);//6 background
    assets.getSp(6,0).setTexRect(0, menuSprites);

    // ======== Interactive Sprites ========

    //Buttons
    assets.addSprite(5,1);//0 save
    assets.getSp(0,1).setTexRect(0, buttonsSprites);
    assets.addSprite(5,1);//1 left border    
    assets.getSp(1,1).setTexRect(2, buttonsSprites);
    assets.getSp(1,1).setRotation(90);
    assets.addSprite(5,1);//2 up border  
    assets.getSp(2,1).setTexRect(2, buttonsSprites);
    assets.getSp(2,1).setRotation(180);
    assets.addSprite(5,1);//3 right border    
    assets.getSp(3,1).setTexRect(2, buttonsSprites);
    assets.getSp(3,1).setRotation(270);
    assets.addSprite(5,1);//4 down border    
    assets.getSp(4,1).setTexRect(2, buttonsSprites);
    assets.addSprite(5,1);//5 nameFile
    assets.getSp(5,1).setTexRect(1, buttonsSprites);


    //Board
    for (unsigned int k = 0 ; k < gameVars.board->cases.size() ; k++){
        assets.addSprite(2,2);
    }


    // icons in menu
    int nbBlocs = 8; 
    for (int k = 0; k < nbBlocs; k++){
        if (k==0){assets.addSprite(7,3);}//mouse
        else{
            assets.addSprite(2,3);//bloc
            assets.getSp(2*k,3).setTexRect(k, boardSprites);
        }
        assets.addSprite(6,3);//cadre
        assets.getSp(2*k+1,3).setTexRect(1, menuSprites);
    }

 
}












export void updateEditor(GameVariables &gameVars){
    static bool waitRelease = false;
    std::shared_ptr<BoardEditor> board = std::dynamic_pointer_cast<BoardEditor>(gameVars.board);

    //Click Handler
    if (gameVars.clickPressed && !waitRelease){
        
        switch(gameVars.hoverList){
            case 1://button
                waitRelease = true;
                switch (gameVars.hoverSprite){
                    case 0://save
                        saveBoard(board);
                        break;
                    case 1://left button
                    case 2://up button
                    case 3://right button
                    case 4://down button
                        expandBoard(gameVars);
                        break;
                    case 5://namefile
                        break;
                    default:
                        break;
                }
                break;

            case 2://board
                board->changeBloc(gameVars.hoverSprite, gameVars.selectedBloc);
                break;
            case 3://BlocMenu
                gameVars.selectedBloc = gameVars.hoverSprite/2;
                break;
            default: break;
        }
    }
    if (!gameVars.clickPressed){waitRelease =false;}


    //Check if there is a row/column to remove
    int cpt = 0;
    //left
    for (int k = 0 ; k< board->height; k++){if (board->cases[k*board->width]->displayId == 0){cpt++;}}
    if (cpt==board->height){
        for (int k = 0 ; k< board->height; k++){
            board->cases.erase(board->cases.begin() + k*board->width -k);
            gameVars.assets.pop_backSprite(2);    
        }
        board->width--;
    }
    cpt = 0;
    //up
    for (int k = 0 ; k< board->width; k++){if (board->cases[k]->displayId == 0){cpt++;}}
    if (cpt==board->width){
        for (int k = 0 ; k< board->width; k++){
            board->cases.erase(board->cases.begin());
            gameVars.assets.pop_backSprite(2);
        }
        board->height--;
    }
    cpt = 0;
    //right
    for (int k = 0 ; k< board->height; k++){if (board->cases[(k+1)*board->width-1]->displayId == 0){cpt++;}}
    if (cpt==board->height){
        for (int k = 0 ; k< board->height; k++){
            board->cases.erase(board->cases.begin()+(k+1)*board->width -1 -k);
            gameVars.assets.pop_backSprite(2);
        }
        // board->cases.pop_back();
        board->width--;
        
    }
    cpt = 0;
    //down
    for (int k = 0 ; k< board->width; k++){if (board->cases[(board->height-1)*board->width+k]->displayId == 0){cpt++;}}
    if (cpt==board->width){
        for (int k = 0 ; k< board->width; k++){
            board->cases.pop_back();
            gameVars.assets.pop_backSprite(2);
        }
        board->height--;
    }
    
    // std::cout<< cpt << "  " << board->height << " \n";

}









export void dispEditor(GameVariables &gameVars){
    Assets& assets = (gameVars.assets);
    RenderWindow& rWindow = *(gameVars.rWindow);
    std::shared_ptr<BoardEditor> board = std::dynamic_pointer_cast<BoardEditor>(gameVars.board);

    unsigned int nbCases = board->cases.size();
    unsigned int nbDiffBlocs = assets.spriteList[3].size()/2;

    float xStart; float yStart; 
    float xOffset; float yOffset;
    float xCursor; float yCursor;
    rWindow.getCursorPos(xCursor, yCursor);
    board->updateBlocLengthEditor(rWindow, xStart, yStart);
    float side = board->blocLength;//unit reference
    float fButton = 1./16.;//facteurs multiplicatifs
    float fBoard = 3./4.;
    float fOffset = 1./64.;

    // ================= MOUSE MANAGEMENT =================

    gameVars.hoverList=-1; gameVars.hoverSprite = -1;
    for (unsigned int i = 1 ; i < assets.spriteList.size(); i++){
        for (unsigned int j = 0 ; j < assets.spriteList[i].size(); j++){
            auto sp = assets.getSp(j,i);
            if (sp.contains(xCursor,yCursor)){
                gameVars.hoverList = i ; gameVars.hoverSprite = j; break;
            }
        }
        if (gameVars.hoverSprite != -1){break;}
    }




    // ================= DRAWING =================

    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    assets.getSp(1,0).resize(xScreen, yScreen);
    rWindow.draw(assets.getSp(1,0));


    //sp._x=fButton; sp._y=fButton; sp._w=fBoard; sp._h=fButton;
    //sp.adaptToWindow(xScreen, yScreen, yScreen, xScreen);

    //draw expand buttons
    //left button
    assets.getSp(1,1).setPos(xScreen*fButton, yScreen*fButton);
    assets.getSp(1,1).resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(assets.getSp(1,1));
    //up button
    assets.getSp(2,1).setPos(xScreen*(fButton + fBoard), yScreen*fButton);
    assets.getSp(2,1).resize(xScreen*fBoard,yScreen*fButton);
    rWindow.draw(assets.getSp(2,1));
    // right button
    assets.getSp(3,1).setPos(xScreen*(fButton + fBoard),  yScreen*(fButton + fBoard));
    assets.getSp(3,1).resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(assets.getSp(3,1));
    // down button
    assets.getSp(4,1).setPos(xScreen*fButton, yScreen*(fButton + fBoard));
    assets.getSp(4,1).resize(xScreen*fBoard, yScreen*fButton);
    rWindow.draw(assets.getSp(4,1));





    //draw BlocMenu
    //background
    xOffset = 0;
    yOffset = yScreen*2*fButton + yScreen*fBoard;
    assets.getSp(6,0).setPos(xOffset, yOffset);
    assets.getSp(6,0).resize(xScreen*(2*fButton + fBoard), yScreen - yOffset);
    rWindow.draw(assets.getSp(6,0));
    //items
    xOffset += xScreen* fOffset;
    yOffset += yScreen*fOffset;
    float ySize = yScreen - yOffset- yScreen*fOffset;
    for (unsigned int k = 0; k < nbDiffBlocs; k++){
        //bloc
        assets.getSp(2*k,3).setPos(xOffset, yOffset); 
        assets.getSp(2*k,3).resize(ySize, ySize);
        rWindow.draw(assets.getSp(2*k,3));
        //cadre
        assets.getSp(2*k+1,3).setPos(xOffset, yOffset); 
        assets.getSp(2*k+1,3).resize(ySize, ySize);
        rWindow.draw(assets.getSp(2*k+1,3));

        xOffset += ySize + fOffset*xScreen;
    }



    //draw Board
    assets.getSp(2,0).setPos(xScreen*fButton, yScreen*fButton);
    assets.getSp(2,0).resize(xScreen*fBoard, yScreen*fBoard);
    rWindow.draw(assets.getSp(2,0));
    for (unsigned int k = 0; k < nbCases; k++){
        board->setBlocSprite(assets.getSp(k,2), k);

        board->blocOffset(k, xOffset, yOffset);
        assets.getSp(k,2).setPos(xStart + xOffset, yStart + yOffset);
        assets.getSp(k,2).resize(side, side);
        rWindow.draw(assets.getSp(k,2));
    }
    //selector
    if (gameVars.hoverList == 2){
        board->blocOffset(gameVars.hoverSprite, xOffset, yOffset);
        assets.getSp(5,0).setPos(xStart + xOffset, yStart + yOffset);
        assets.getSp(5,0).resize(side, side);
        rWindow.draw(assets.getSp(5,0));
    }


    //draw save button
    xOffset = xScreen*(2*fButton + fBoard + fOffset/2);
    yOffset = yScreen*fOffset/2;
    assets.getSp(0,1).setPos(xOffset, yOffset);
    assets.getSp(0,1).resize(xScreen - xOffset - xScreen*fOffset/2, yScreen*2*fButton);
    rWindow.draw(assets.getSp(0,1));

    //draw nameFile button?
    yOffset += yScreen*2*fButton + yScreen*fOffset/2;
    assets.getSp(5,1).setPos(xOffset, yOffset);
    assets.getSp(5,1).resize(xScreen - xOffset - xScreen*fOffset/2, yScreen*2*fButton);
    // rWindow.draw(assets.getSp(5,1));


    //draw cursor
    assets.getSp(3,0).setPos(xCursor, yCursor);
    rWindow.draw(assets.getSp(3,0));
    //draw selectedBLoc
    static std::vector<int> boardSprites = boardTexBinding();
    float selectOffset = 45;
    int sizeSelectedBloc = 40;
    assets.getSp(4,0).setTexRect(gameVars.selectedBloc, boardSprites);
    assets.getSp(4,0).setPos(xCursor + selectOffset , yCursor + selectOffset);
    assets.getSp(4,0).resize(sizeSelectedBloc, sizeSelectedBloc);
    
    rWindow.draw(assets.getSp(4,0));


}
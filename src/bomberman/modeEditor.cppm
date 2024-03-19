module;

import viewAPI;
import Event;
import gameVars;
import assetsBindings;
// import Entity;
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

    assets.addSpriteVec();// 1 : for Board
    assets.addSpriteVec();// 2 : for blocMenu
    

    assets.selectMusic("editor.ogg");

}


export void initEditor(Event &event, TextManager& texts, GameVariables& gameVars, Assets& assets){
    event.window->hideCursor();
    auto buttonsSprites = editorButtonBinding();    
    auto menuSprites = editorMenuBinding();    
    auto boardSprites = boardTexBinding();

    //background
    assets.addSprite(1,0);//1

    //Mouse
    assets.addSprite(7,0);//2
    int actionsOffset = event.eventList.size(); 
    event.addEvent(click, std::ref(gameVars.clickPressed));
    event.addBinding(actionsOffset, CLICK_LEFT_PRESS);
    event.addEvent(release, std::ref(gameVars.clickPressed));
    event.addBinding(actionsOffset+1, CLICK_LEFT_RELEASE);

    //Buttons
    assets.addSprite(5,0);//3 save
    assets.getSp(3,0).setTexRect(0, buttonsSprites);
    assets.addSprite(5,0);//4 nameFile
    assets.getSp(4,0).setTexRect(1, buttonsSprites);
    assets.addSprite(5,0);//5 left border    
    assets.getSp(5,0).setTexRect(2, buttonsSprites);
    assets.getSp(5,0).setRotation(90);
    assets.addSprite(5,0);//6 up border  
    assets.getSp(6,0).setTexRect(2, buttonsSprites);
    assets.getSp(6,0).setRotation(180);
    assets.addSprite(5,0);//7 right border    
    assets.getSp(7,0).setTexRect(2, buttonsSprites);
    assets.getSp(7,0).setRotation(270);
    assets.addSprite(5,0);//8 down border    
    assets.getSp(8,0).setTexRect(2, buttonsSprites);

    //Bloc Menu
    assets.addSprite(6,0);//9 background
    assets.getSp(9,0).setTexRect(0, menuSprites);
    assets.addSprite(6,0);//10 selector
    assets.getSp(10,0).setTexRect(2, menuSprites);

    int nbBlocs = 8; // icons in menu
    for (int k = 0; k < nbBlocs; k++){
        if (k==0){assets.addSprite(7,2);}//mouse
        else{
            assets.addSprite(2,2);//bloc
            assets.getSp(2*k,2).setTexRect(k, boardSprites);
        }
        assets.addSprite(6,2);//cadre
        assets.getSp(2*k+1,2).setTexRect(1, menuSprites);
    }


    //Board background
    assets.addSprite(5,0);//11
    assets.getSp(11,0).setTexRect(9,11,2,2);//just to get gray color, too lazy to implement rectangle


    //Board
    auto board = &(gameVars.board);
    for (unsigned int k = 0 ; k < gameVars.board.cases.size() ; k++){
        assets.addSprite(2,1);
    }

    //selected bloc
    gameVars.selectedBloc = 0;
    assets.addSprite(2,0);//12
    assets.getSp(12,0).setTexRect(gameVars.selectedBloc, boardSprites);
}












export void updateEditor(Event &event, TextManager texts, GameVariables &gameVars){
    if (gameVars.clickPressed){
        switch(gameVars.hoverList){
            case 0://button
                switch (gameVars.hoverSprite){
                    case 3://save
                        saveBoard(gameVars.board);
                        break;
                    case 4://namefile
                        break;
                    case 5://left button
                        break;
                    case 6://up button
                        break;
                    case 7://right button
                        break;
                    case 8://down button
                        break;
                    default:
                        break;
                }
            case 1://board
                gameVars.board.changeBloc(gameVars.hoverSprite, gameVars.selectedBloc);
                break;
            case 2://BlocMenu
                gameVars.selectedBloc = gameVars.hoverSprite/2;
                break;
            default: break;
        }
    }
}
//hover sprite function needed, use getglobalbounds + contains









export void dispEditor(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    auto board = &(gameVars.board);
    unsigned int nbCases = board->cases.size();
    unsigned int nbDiffBlocs = assets.spriteList[2].size()/2;

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
    for (unsigned int i = 0 ; i < assets.spriteList.size(); i++){
        for (unsigned int j = 0 ; j < assets.spriteList[i].size(); j++){
            if (i==0){//skip non interactive sprites
                switch (j){
                    case 0: j = 3; break;//skip background, not found
                    case 9: i = 1; j = 0; break; //skip stuff
                    default : break;
                }
            }
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



    //draw expand buttons
    //left button
    //sp._x=fButton; sp._y=fButton; sp._w=fBoard; sp._h=fButton;
    //sp.adaptToWindow(xScreen, yScreen, yScreen, xScreen);
    assets.getSp(5,0).setPos(xScreen*fButton, yScreen*fButton);
    assets.getSp(5,0).resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(assets.getSp(5,0));
    //up button
    assets.getSp(6,0).setPos(xScreen*(fButton + fBoard), yScreen*fButton);
    assets.getSp(6,0).resize(xScreen*fBoard,yScreen*fButton);
    rWindow.draw(assets.getSp(6,0));
    // right button
    assets.getSp(7,0).setPos(xScreen*(fButton + fBoard),  yScreen*(fButton + fBoard));
    assets.getSp(7,0).resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(assets.getSp(7,0));
    // down button
    assets.getSp(8,0).setPos(xScreen*fButton, yScreen*(fButton + fBoard));
    assets.getSp(8,0).resize(xScreen*fBoard, yScreen*fButton);
    rWindow.draw(assets.getSp(8,0));





    //draw BlocMenu
    //background
    xOffset = 0;
    yOffset = yScreen*2*fButton + yScreen*fBoard;
    assets.getSp(9,0).setPos(xOffset, yOffset);
    assets.getSp(9,0).resize(xScreen*(2*fButton + fBoard), yScreen - yOffset);
    rWindow.draw(assets.getSp(9,0));
    //items
    xOffset += xScreen* fOffset;
    yOffset += yScreen*fOffset;
    float ySize = yScreen - yOffset- yScreen*fOffset;
    for (unsigned int k = 0; k < nbDiffBlocs; k++){
        //bloc
        assets.getSp(2*k,2).setPos(xOffset, yOffset); 
        assets.getSp(2*k,2).resize(ySize, ySize);
        rWindow.draw(assets.getSp(2*k,2));
        //cadre
        assets.getSp(2*k+1,2).setPos(xOffset, yOffset); 
        assets.getSp(2*k+1,2).resize(ySize, ySize);
        rWindow.draw(assets.getSp(2*k+1,2));

        xOffset += ySize + fOffset*xScreen;
    }



    //draw Board
    assets.getSp(11,0).setPos(xScreen*fButton, yScreen*fButton);
    assets.getSp(11,0).resize(xScreen*fBoard, yScreen*fBoard);
    rWindow.draw(assets.getSp(11,0));
    for (unsigned int k = 0; k < nbCases; k++){
        board->setBlocSprite(assets.getSp(k,1), k);

        board->blocOffset(k, xOffset, yOffset);
        assets.getSp(k,1).setPos(xStart + xOffset, yStart + yOffset);
        assets.getSp(k,1).resize(side, side);
        rWindow.draw(assets.getSp(k,1));
    }
    //selector
    if (gameVars.hoverList == 1){
        board->blocOffset(gameVars.hoverSprite, xOffset, yOffset);
        assets.getSp(10,0).setPos(xStart + xOffset, yStart + yOffset);
        assets.getSp(10,0).resize(side, side);
        rWindow.draw(assets.getSp(10,0));
    }


    //draw save button
    xOffset = xScreen*(2*fButton + fBoard + fOffset/2);
    yOffset = yScreen*fOffset/2;
    assets.getSp(3,0).setPos(xOffset, yOffset);
    assets.getSp(3,0).resize(xScreen - xOffset - xScreen*fOffset/2, yScreen*2*fButton);
    rWindow.draw(assets.getSp(3,0));

    //draw nameFile button?
    yOffset += yScreen*2*fButton + yScreen*fOffset/2;
    assets.getSp(4,0).setPos(xOffset, yOffset);
    assets.getSp(4,0).resize(xScreen - xOffset - xScreen*fOffset/2, yScreen*2*fButton);
    rWindow.draw(assets.getSp(4,0));


    //draw cursor
    assets.getSp(2,0).setPos(xCursor, yCursor);
    rWindow.draw(assets.getSp(2,0));

}
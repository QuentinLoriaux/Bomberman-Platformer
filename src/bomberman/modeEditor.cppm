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

    int nbBlocs = 5; // icons in menu
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


}












export void updateEditor(Event &event, TextManager texts, GameVariables &gameVars){

}
//hover sprite function needed, use getglobalbounds + contains









export void dispEditor(RenderWindow& rWindow, Assets &assets, TextManager& texts, GameVariables &gameVars){
    auto board = &(gameVars.board);
    unsigned int nbCases = board->cases.size();
    unsigned int nbDiffBlocs = assets.spriteList[2].size()/2;


    //draw background
    float xScreen; float yScreen;
    rWindow.getSize(xScreen, yScreen);
    auto sp = assets.getSp(1,0); sp.resize(xScreen, yScreen);
    rWindow.draw(sp);


    


    float xStart; float yStart; 
    board->updateBlocLengthEditor(rWindow, xStart, yStart);
    float side = board->blocLength;//unit reference
    float fButton = 1./16.;//facteurs multiplicatifs
    float fBoard = 3./4.;

    float xOffset; float yOffset;




    //draw add_row/column buttons
    //left button
    sp = assets.getSp(5,0); sp.setPos(xScreen*fButton, yScreen*fButton);
    sp.resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(sp);
    //up button
    sp = assets.getSp(6,0); sp.setPos(xScreen*fButton + xScreen*fBoard, yScreen*fButton);
    sp.resize(xScreen*fBoard,yScreen*fButton);
    rWindow.draw(sp);
    // right button
    sp = assets.getSp(7,0); sp.setPos(xScreen*fButton + xScreen*fBoard,  yScreen*fButton + yScreen*fBoard);
    sp.resize(yScreen*fBoard,xScreen*fButton);
    rWindow.draw(sp);
    // down button
    sp = assets.getSp(8,0); sp.setPos(xScreen*fButton, yScreen*fButton + yScreen*fBoard);
    sp.resize(xScreen*fBoard, yScreen*fButton);
    rWindow.draw(sp);





    //draw BlocMenu
    xOffset = 0;
    yOffset = yScreen*2*fButton + yScreen*fBoard;
    sp = assets.getSp(9,0); sp.setPos(xOffset, yOffset);
    sp.resize(2*xScreen*fButton + xScreen*fBoard, yScreen - yOffset);
    rWindow.draw(sp);

    float fOffset = 1./64. ;
    xOffset += xScreen* fOffset;
    yOffset += yScreen*fOffset;
    float ySize = yScreen - yOffset- yScreen*fOffset;
    for (unsigned int k = 0; k < nbDiffBlocs; k++){
        //bloc
        sp = assets.getSp(2*k,2); sp.setPos(xOffset, yOffset); 
        sp.resize(ySize, ySize);
        rWindow.draw(sp);
        //cadre
        sp = assets.getSp(2*k+1,2); sp.setPos(xOffset, yOffset); 
        sp.resize(ySize, ySize);
        rWindow.draw(sp);

        xOffset += ySize + fOffset*xScreen;
    }





    //draw Board
    sp = assets.getSp(11,0); sp.setPos(xScreen*fButton, yScreen*fButton);
    sp.resize(xScreen*fBoard, yScreen*fBoard);
    rWindow.draw(sp);
    for (unsigned int k = 0; k < nbCases; k++){
        auto sp = assets.getSp(k,1);
        board->setBlocSprite(sp, k);

        board->blocOffset(k, xOffset, yOffset);
        sp.setPos(xStart + xOffset, yStart + yOffset);
        sp.resize(side, side);
        rWindow.draw(sp);
    }



    fOffset = fOffset/2;
    //draw save button
    xOffset = xScreen*(2*fButton + fBoard + fOffset);
    yOffset = yScreen*fOffset;
    sp = assets.getSp(3,0); sp.setPos(xOffset, yOffset);
    sp.resize(xScreen - xOffset - xScreen*fOffset, yScreen*2*fButton);
    rWindow.draw(sp);

    //draw nameFile button?
    yOffset += yScreen*2*fButton + yScreen*fOffset;
    sp = assets.getSp(4,0); sp.setPos(xOffset, yOffset);
    sp.resize(xScreen - xOffset - xScreen*fOffset, yScreen*2*fButton);
    rWindow.draw(sp);



    //draw cursor
    float xCursor; float yCursor;
    rWindow.getCursorPos(xCursor, yCursor);
    assets.getSp(2,0).setPos(xCursor, yCursor);
    rWindow.draw(assets.getSp(2,0));

}
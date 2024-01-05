module;


#include <iostream>



export module loader;

export void doNothing() { std::cout << "Just doing nothing." << std::endl; }
export void quitGame(){ isGaming = false; }//does not work


export void loadMainTitle(){

    //Chargement des assets
    loadSprite("mainTitle.jpg");
    loadMusic("Dire_Dire_Docks.ogg");   

    //Chargement du texte
    loadText("Start Game", MAIN_TITLE);

    //évènements à gérer
    addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //Il faut toujours gérer l'évènement quit...
    //MJOY: Main Joycontroller


}

export void loadMenu(){
    //Clean previous menu...
    //switch case selon le sous-menu à charger

    //La gestion des events se fait à l'intérieur

    createMenu();
    createCursorMenu();

}

export void loadEditor(){
    mode = EDITOR;


}
module;

// import mode;
#include <iostream>
#include <vector>
#include <string>
#include <any>
#include <functional>


export module menu;



export typedef enum _menuState{
    MENU_MAIN_TITLE,
    MAIN_MENU,
    SOLO,
    MULTIPLAYER,
    ONLINE,
    CHOOSE_MAP
} menuState;

export class MenuEntry {

    private:
        template<typename... Args>
        using type_func = std::function<void(Args...)>;
        
        type_func<> func;
       
    public:

        //****************************************************************************************************************
        //ATTENTION il faut absolument noter les éléments passés en référence de la sorte : std::ref<arg> sinon ça marche pas
        //****************************************************************************************************************
        template<typename Func, typename... Args>
        MenuEntry(Func _fun, Args&&... args) :
            func(std::bind(_fun, std::forward<Args>(args)...)) {}

        void execute(){func();}
};



// export void loadEditorFromMenu(mode &gameMode){gameMode = EDITOR;}

// export void unloadMenu(menuState &menuState){menuState = MENU_MAIN_TITLE;}
// export void loadMainMenu(menuState &menuState){menuState = MAIN_MENU;}
// export void loadSoloMenu(menuState &menuState){menuState = SOLO;}
// export void loadMultiMenu(menuState &menuState){menuState = MULTIPLAYER;}


export void proceedMenu(std::vector<MenuEntry> &menu, int &menuCursor){
    menu[menuCursor].execute(); // A voir, soit le calcul de la position clc, soit c'est l'indice du menu
}

export void backMenu(menuState &menuState){
    switch (menuState){
        case MENU_MAIN_TITLE : break;
        case MAIN_MENU : menuState = MENU_MAIN_TITLE; break;
        case SOLO: case MULTIPLAYER : menuState = MAIN_MENU; break;
    }
}

void addMenuEntry(){}//Faut anticiper la nécessité de créer des entries pour les maps du joueur.

void displayMenu(menuState &menuState){}

void displayCursor(int &menuCursor){

}

// void createMainMenu(std::vector<MenuEntry> &menu){createMenu(menu, MAIN_MENU);}
// void createSoloMenu(std::vector<MenuEntry> &menu){createMenu(menu, SOLO);}
// void createMultiplayerMenu(std::vector<MenuEntry> &menu){createMenu(menu, MULTIPLAYER);}

// void createMenu(std::vector<MenuEntry> &menu, menuType mType){
//     menu.clear();
//     switch (mType){

//         case MAIN_MENU:
//             menu.push_back(MenuEntry());
//             menu.push_back(MenuEntry("SOLO", &createSoloMenu));
//             menu.push_back(MenuEntry("MULTIPLAYER", &createMultiplayerMenu));
//             menu.push_back(MenuEntry("EDITOR", &loadEditor));
//             menu.push_back(MenuEntry("QUIT", &quitGame));
//             break;

//         case SOLO:
//             menu.push_back(MenuEntry());
//             menu.push_back(MenuEntry("BACK", &createMainMenu);)
//             break;

//         case MULTIPLAYER:
//             menu.push_back(MenuEntry());
//             menu.push_back(MenuEntry("BACK", &createMainMenu);)
//             break;
//     }
// }


// tout loader et ensuite, de n'afficher que les entrées correspondantes au mType
//On peut remplacer BACK par un évènement sur le bouton ESC ou le bouton B.
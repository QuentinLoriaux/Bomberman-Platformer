module;

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

import tMenuType;

export module menu;




void createMainMenu(std::vector<MenuEntry> &menu){createMenu(menu, MAIN_MENU);}
void createSoloMenu(std::vector<MenuEntry> &menu){createMenu(menu, SOLO);}
void createMultiplayerMenu(std::vector<MenuEntry> &menu){createMenu(menu, MULTIPLAYER);}

void createMenu(std::vector<MenuEntry> &menu, menuType mType){
    menu.clear();
    switch (mType){

        case MAIN_MENU:
            menu.push_back(MenuEntry());
            menu.push_back(MenuEntry("SOLO", &createSoloMenu));
            menu.push_back(MenuEntry("MULTIPLAYER", &createMultiplayerMenu));
            menu.push_back(MenuEntry("EDITOR", &loadEditor));
            menu.push_back(MenuEntry("QUIT", &quitGame));
            break;

        case SOLO:
            menu.push_back(MenuEntry());
            menu.push_back(MenuEntry("BACK", &createMainMenu);)
            break;

        case MULTIPLAYER:
            menu.push_back(MenuEntry());
            menu.push_back(MenuEntry("BACK", &createMainMenu);)
            break;
    }
}

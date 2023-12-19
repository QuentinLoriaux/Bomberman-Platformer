#include "../include/window.hpp"
#include <vector>
#include "../include/global.hpp"

void refreshWindowSize(){
    //modify the global variables
    windowHeight = sf::RenderWindow::getSize().y;
    windowWidth = sf::RenderWindow::getSize().x;
}


void createMenu(int nbEntries){
    std::vector<MenuEntry> menuEntries;
    for (int i = 0; i < nbEntries; i++){
        menuEntries.push_back(MenuEntry("entry" + std::to_string(i)));
    }
}

void displayMenu(int nbEntries){
    float ratioWidth = 0.8;
    int padding = static_cast<int>(windowHeight/nbEntries * ratioWidth * 0.1);
    int menuHeight = static_cast<int>(windowHeight/nbEntries * ratioWidth * 0.9);
    int menuWidth = static_cast<int>(windowWidth * ratioWidth);
}

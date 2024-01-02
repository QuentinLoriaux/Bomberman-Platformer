module;

#include <vector>
#include <string>
#include <iostream>
#include "global.hpp"

export module window;


#define RATIOWIDTH 0.8

int padding;
int menuHeight;
int menuWidth;

using namespace std;

class MenuEntry {
    private:
        string name;
        void* function;
    public:
        MenuEntry(): name(""), function(&doNothing) {}
        MenuEntry(string m_name): name(m_name), function(&doNothing) {}
        void loadFunction() {}
        void doNothing() {
            std::cout < "Nothing to do here" << std::endl;
        }
        void setName(string n_name){
            name = n_name;
        }
        string getName(){
            return name;
        }
};



export void refreshWindowSize(){
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
    // float RATIOWIDTH = 0.8;
    padding = static_cast<int>(windowHeight/nbEntries * RATIOWIDTH * 0.1);
    menuHeight = static_cast<int>(windowHeight/nbEntries * RATIOWIDTH * 0.9);
    menuWidth = static_cast<int>(windowWidth * RATIOWIDTH);
}


// mettre des entries semble mieux que de donner des caractéristiques au menu (source stackoverflow)
void displayMenuEntry(MenuEntry entry, int nbEntries){
    displayMenu(nbEntries);
    int entryHeight = static_cast<int>(menuHeight/nbEntries * 0.9);
    int entryWidth = static_cast<int>(menuWidth * 0.9);
    int entryPadding = static_cast<int>(menuHeight/nbEntries * 0.1);
    int entryX = static_cast<int>(windowWidth * (1-RATIOWIDTH)/2 + menuWidth * 0.05);
    int entryY = static_cast<int>(windowHeight * (1-RATIOWIDTH)/2 + menuHeight * 0.05 + nbEntries * (entryHeight + entryPadding));
    sf::RectangleShape entryShape(sf::Vector2f(entryWidth, entryHeight));
    entryShape.setPosition(entryX, entryY);
    entryShape.setFillColor(sf::Color::White);
    sf::Text entryText;
    entryText.setFont(font);
    entryText.setString(entry.text);
    entryText.setCharacterSize(entryHeight);
    entryText.setFillColor(sf::Color::Black);
    entryText.setPosition(entryX, entryY);
    sf::FloatRect textRect = entryText.getLocalBounds();
    entryText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    entryText.setPosition(sf::Vector2f(entryX + entryWidth/2.0f, entryY + entryHeight/2.0f));
    window.draw(entryShape);
    window.draw(entryText);
}
#include "../include/window.hpp"
#include <vector>
#include "../include/global.hpp"

#define ratioWidth 0.8;
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
    // float ratioWidth = 0.8;
    padding = static_cast<int>(windowHeight/nbEntries * ratioWidth * 0.1);
    menuHeight = static_cast<int>(windowHeight/nbEntries * ratioWidth * 0.9);
    menuWidth = static_cast<int>(windowWidth * ratioWidth);
}


// mettre des entries semble mieux que de donner des caractéristiques au menu (source stackoverflow)
void displayMenuEntry(MenuEntry entry, int nbEntries){
    displayMenu(nbEntries);
    int entryHeight = static_cast<int>(menuHeight/nbEntries * 0.9);
    int entryWidth = static_cast<int>(menuWidth * 0.9);
    int entryPadding = static_cast<int>(menuHeight/nbEntries * 0.1);
    int entryX = static_cast<int>(windowWidth * (1-ratioWidth)/2 + menuWidth * 0.05);
    int entryY = static_cast<int>(windowHeight * (1-ratioWidth)/2 + menuHeight * 0.05 + nbEntries * (entryHeight + entryPadding));
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
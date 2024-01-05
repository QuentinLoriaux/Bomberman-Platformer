module;

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


export module display;


//Il faut se débrouiller pour que de l'extérieur, on n'appelle jamais directement SFML



//========================= WINDOW =========================

export typedef sf::RenderWindow RenderWindow;

RenderWindow::RenderWindow(unsigned int width, unsigned int height, const std::string& title):
    RenderWindow(sf::VideoMode(width, height), title){}



//========================= TEXTURES and SPRITES =========================

export typedef sf::Texture Texture;

//Créer une texture et l'attribuer directement
Texture::Texture(const std::string &nameTex): Texture(){
    if (!this->loadFromFile(nameTex)){
        std::cout << "Error :" << nameTex << " texture not found" << std::endl;
    }   
}

export typedef sf::Sprite Sprite;

void loadSprite(const std::string& name){
    
}

//========================= OTHERS =========================

export typedef sf::Font Font;

//Créer une font et l'attribuer directement
Font::Font(const std::string &nameFont): Font() {
    if (!this->loadFromFile(nameFont)){
        std::cout << "Error :" << nameFont << " font not found" << std::endl;
    }
}

export typedef sf::Text Text;

export typedef sf::Music Music;

Music::Music(const std::string &nameMusic): Music(){
    if (!this->openFromFile(nameMusic)){
        std::cout << "Error :" << nameMusic << " music not found" << std::endl;
    }
}

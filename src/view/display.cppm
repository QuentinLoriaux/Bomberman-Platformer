module;

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


export module display;


//Il faut se débrouiller pour que de l'extérieur, on n'appelle jamais directement SFML
export class RenderWindow;
export class Texture;
export class Sprite;
export class Font;
export class Text;
export class Music;

//========================= WINDOW =========================

class RenderWindow : public sf::RenderWindow {
    public :
        RenderWindow(unsigned int width, unsigned int height, const std::string& title):
            sf::RenderWindow(sf::VideoMode(width, height), title){}

        //void draw(sf::Sprite sp){this->draw(sp);}
};



//========================= TEXTURES and SPRITES =========================

class Texture : public sf::Texture{
    public:
        Texture(const std::string &nameTex): sf::Texture(){
            if (!this->loadFromFile(nameTex)){
                std::cout << "Error :" << nameTex << " texture not found" << std::endl;
            }    
        }
};

class Sprite : public sf::Sprite{
    public :
        Sprite(Texture tex): sf::Sprite((sf::Texture) tex){}
};



//========================= OTHERS =========================

class Font : public sf::Font{
    public:
        Font(const std::string &nameFont): sf::Font() {
            if (!this->loadFromFile(nameFont)){
                std::cout << "Error :" << nameFont << " font not found" << std::endl;
            }
        }
};

class Text : public sf::Text{
    public:
        Text(const std::string &content,Font font, int size):
            sf::Text(content, (sf::Font) font, size){}
};

class Music : public sf::Music{
    public:
        Music(const std::string &nameMusic): sf::Music(){
            if (!this->openFromFile(nameMusic)){
                std::cout << "Error :" << nameMusic << " music not found" << std::endl;
            }
        }
};




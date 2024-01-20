module;

#include <iostream>
#include <string>
#include <variant>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


export module viewAPI;


//Il faut se débrouiller pour que de l'extérieur, on n'appelle jamais directement SFML






//========================= GRAPHICS =========================

//-------------------- Sprite --------------------

export class Texture{
    public :
        sf:: Texture tex;

        Texture(const std::string& nameTex) : tex(sf::Texture()){
            if (!tex.loadFromFile("./assets/img/" + nameTex)){
                std::cout << "Error : texture '" << nameTex << "' not found" << std::endl;
            }
        }

};

export class Sprite{

    public :
        sf::Sprite sp;

        Sprite(Texture& _tex): sp(sf::Sprite(_tex.tex)) {}//Directement assigner une image au sprite

};


//-------------------- Text --------------------

export class Font{

    public :
        sf::Font ft;
        
        Font(const std::string &nameFont): ft(sf::Font()){//Créer une font et l'attribuer directement
            if (!ft.loadFromFile("./assets/font/" + nameFont)){
                std::cout << "Error : Font '" << nameFont << "' not found" << std::endl;
            }   
        }

};



export class Text{

    
    public :
        sf::Text text;

        Text(const std::string& content, const Font& _ft, int size):
            text(sf::Text(content, _ft.ft, size)){}

        
};



//========================= WINDOW =========================
export class RenderWindow {

    public :
        sf::RenderWindow rWindow;

        RenderWindow(unsigned int width, unsigned int height, const std::string& title):
            rWindow(sf::VideoMode(width, height), title){}

        void draw(Sprite &_sp){rWindow.draw(_sp.sp);}
        void draw(Text &_txt){rWindow.draw(_txt.text);}
        void clear(){rWindow.clear();}
        void display(){rWindow.display();}
        void setFramerateLimit(int fps){rWindow.setFramerateLimit(fps);}
};


//========================= AUDIO =========================


export class SoundBuffer{

    public :
        sf::SoundBuffer sfxBuf;
    
        SoundBuffer(const std::string& nameSfx): sfxBuf(sf::SoundBuffer()){
            if (!sfxBuf.loadFromFile("./assets/sound/" + nameSfx)){
                std::cout << "Error : Sound '" << nameSfx << "' not found" << std::endl;
            }
        }

};

export class Sound{
    private :
        sf::Sound sfx;
    
    public :
        Sound(SoundBuffer &_sfxBuf): sfx(sf::Sound(_sfxBuf.sfxBuf)) {}
   
        void play(){sfx.play();}

};

export class Music{
    private :
        sf::Music mus;
    public : 
        Music(): mus(sf::Music()){}
        Music(const std::string &nameMusic): mus(sf::Music()){//Créer une Musique et l'attribuer directement
            if (!mus.openFromFile("./assets/music/" + nameMusic)){
                std::cout << "Error : Music '" << nameMusic << "' not found" << std::endl;
            }
        }
        
        bool openFromFile(const std::string &nameMusic){return mus.openFromFile("./assets/music/" + nameMusic);}
        void play(){mus.play();}
};

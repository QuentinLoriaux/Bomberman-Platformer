module;

#include <iostream>
#include <string>
#include <variant>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


export module viewAPI;


//Il faut se débrouiller pour que de l'extérieur, on n'appelle jamais directement SFML






//========================= DRAWABLE =========================

//-------------------- Sprite --------------------

export class Sprite{
    private :
        sf::Texture tex;
        sf::Sprite sp;
    
    public :
        Sprite(const std::string& nameTex): tex(sf::Texture()) {
            if (!tex.loadFromFile("./assets/img/" + nameTex)){
                std::cout << "Error : texture '" << nameTex << "' not found" << std::endl;
            }
            sp = sf::Sprite(tex);
        }//Directement assigner une image au sprite

        sf:: Sprite getSp(){return sp;}
        sf::Texture getTex(){return tex;}
};


//-------------------- Text --------------------

export class Font{
    private :
        sf::Font ft;
    
    public :
        Font(const std::string &nameFont): ft(sf::Font()){//Créer une font et l'attribuer directement
            if (!ft.loadFromFile("./assets/font/" + nameFont)){
                std::cout << "Error : Font '" << nameFont << "' not found" << std::endl;
            }   
        }

        sf::Font getFt(){return ft;;}
};



export class Text{
    private :
        sf::Text text;
    
    public :
        Text(const std::string& content, Font& ft, int size): text(sf::Text(content, ft.getFt(), size)){}

        sf::Text getText(){return text;}
};



//========================= WINDOW =========================
export class RenderWindow {
    private :
        sf::RenderWindow rWindow;
    
    public : 
        RenderWindow(unsigned int width, unsigned int height, const std::string& title):
            rWindow(sf::VideoMode(width, height), title){}

        void draw(Sprite sp){rWindow.draw(sp.getSp());}
        void draw(Text txt){rWindow.draw(txt.getText());}
};


//========================= OTHERS =========================

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

module;

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <deque>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


export module viewAPI;


//Il faut se débrouiller pour que de l'extérieur, on n'appelle jamais directement SFML






//========================= GRAPHICS =========================

//-------------------- Sprite --------------------

export class Texture{
    public :
        sf::Texture tex;

        Texture(const std::string nameTex) : tex(sf::Texture()){
            if (!tex.loadFromFile("./assets/img/" + nameTex)){
                std::cout << "Error : texture '" << nameTex << "' not found" << std::endl;
            }
        }

};

export class Sprite{

    public :
        sf::Sprite sp;

        Sprite(Texture& _tex): sp(sf::Sprite(_tex.tex)) {}//Directement assigner une image au sprite
        
        void setTexRect(int x, int y, int w, int h){
            sf::Rect rect(x, y, w, h);
            sp.setTextureRect(rect);
        }
        void setTexRect(int num, std::vector<int>& bindings){
            setTexRect(bindings[4*num], bindings[4*num+1], bindings[4*num+2], bindings[4*num+3]);
        }


        void setPos(float x, float y){sp.setPosition(x,y);}


        #ifdef SFML_2_6_0
        void resize(float w, float h, bool flip){
            
            auto size = sp.getTextureRect().getSize();
           
            sp.setScale(w/size.x, h/size.y);
            if (flip){
                auto size = sp.getTextureRect().getSize();
                sp.setOrigin(size.x, 0);
                sp.scale(sf::Vector2f(-1.0,1.0));
            }
            else{
                sp.setOrigin(0,0);
            }
        }
        #else
        void resize(float w, float h, bool flip){
            
            sf::Vector2<float> size(sp.getTextureRect().width, sp.getTextureRect().height);
           
            sp.setScale(w/size.x, h/size.y);
            if (flip){
                sf::Vector2<float> size(sp.getTextureRect().width, sp.getTextureRect().height);
                sp.setOrigin(size.x, 0);
                sp.scale(sf::Vector2f(-1.0,1.0));
            }
            else{
                sp.setOrigin(0,0);
            }
        }
        #endif
        void resize(float w, float h){resize(w,h,false);}


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

        //provisoire hein
        void setPos(float x, float y){text.setPosition(x,y);}

};

export class TextManager{
    public :
        std::vector<Font> fontList;
        std::vector<Text> textList;

        TextManager(): fontList(std::vector<Font>()), textList(std::vector<Text>()){}

        void addFont(const std::string &nameFont){fontList.push_back(Font(nameFont));}

        void addText(const std::string &content, int numFont, int size){textList.push_back(Text(content, fontList[numFont], size));}

        Text& getText(int numText){return textList[numText];}

        void removeText(int numText){
            textList.erase(textList.begin() + numText);
        }



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
        bool playing(){return sfx.getStatus() == sf::Sound::Status::Playing;}

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

//========================= ASSETS =========================

export class Assets{
    public :
        std::vector<Texture> textureList;
        std::vector<std::vector<Sprite>> spriteList;
        std::vector<SoundBuffer> sfxBufList;
        std::deque<Sound> soundList;
        Music mus;

        Assets(): textureList(std::vector<Texture>()), spriteList(std::vector<std::vector<Sprite>>()), sfxBufList(std::vector<SoundBuffer>()), soundList(std::deque<Sound>()), mus(Music()) {
            spriteList.push_back(std::vector<Sprite>());//Default list
        }
        

        // ----------- Texture -----------
        void addTex(const std::string &nameTex){textureList.push_back(Texture(nameTex));}

        void addSpriteVec(){
            spriteList.push_back(std::vector<Sprite>());
        }

        int addSprite(int numTex, int numSubVec){
            int size = textureList.size();
            int sizeVec = spriteList.size();
            if (numTex < size && numSubVec < sizeVec){spriteList[numSubVec].push_back(textureList[numTex]);}
            else{
                std::cout << "Erreur : il y a " << size << " textures enregistrées, vous avez demandé la n°" << numTex << ".\n";
                std::cout << "         il y a " << sizeVec << " sous-vecteurs, vous avez demandé le n°" << numSubVec << ".\n";
                spriteList[0].push_back(textureList[0]);
            }
            return spriteList.size()-1;
        }

        Sprite& getSp(int numSp, int numSubVec){
            int size = spriteList.size();
            
            if (numSubVec < size ){
                int sizeVec = spriteList[numSubVec].size();

                if (numSp < sizeVec){return spriteList[numSubVec][numSp];}
                else{std::cout << "Erreur : il n'y a que " << sizeVec << " sprites enregistrés or vous avez demandé le n°" << numSp << ".\n";}
                
            }
            else{std::cout << "Erreur : il n'y a que " << size << " sous-vecteurs, or vous avez demandé le n°" << numSubVec << ".\n";}

            return spriteList[0][0];
        }

        // ----------- Sons -----------

        void addSoundBuffer(const std::string &nameSfx){sfxBufList.push_back(SoundBuffer(nameSfx));}

        void addSound(int numSfx){//add and play sound
            int size = sfxBufList.size();
            if (numSfx < size ){
                soundList.push_back(sfxBufList[numSfx]);
                soundList.back().play();
            }
            else{
                std::cout << "Erreur : il n'y a que " << size << " soundBuffer enregistrés or vous avez demandé le n°" << numSfx << ".\n";
                soundList.push_back(sfxBufList[0]);
            }
        }

        void freeSounds(){
            while (!soundList.empty() && !soundList.front().playing()){
                soundList.pop_front();
            }
        }

        // Sound& getSfx(int numSfx){
        //     int size = soundList.size();
        //     if (numSfx < size ){return soundList[numSfx];}
        //     else{
        //         std::cout << "Erreur : il n'y a que " << size << " sons enregistrés or vous avez demandé le n°" << numSfx << ".\n";
        //         return soundList[0];
        //     }            
        // }

        // ----------- Musique -----------

        void selectMusic(const std::string &nameMusic){mus.openFromFile(nameMusic);}

        Music& getMus(){return mus;}

};



//========================= WINDOW =========================
export class RenderWindow {

    public :
        sf::RenderWindow rWindow;

        RenderWindow(unsigned int width, unsigned int height, const std::string& title):
            rWindow(sf::VideoMode(width, height), title){}

        void draw(Sprite &_sp){rWindow.draw(_sp.sp);}
        void draw(Text &_txt){rWindow.draw(_txt.text);}
        void clear(){rWindow.clear(sf::Color::Black);}
        void display(){rWindow.display();}
        void setFramerateLimit(int fps){rWindow.setFramerateLimit(fps);}
        
        void getSize(float& xSize, float& ySize){
            auto vec = rWindow.getSize();
            xSize = vec.x;
            ySize = vec.y;
        }

        void hideCursor(){rWindow.setMouseCursorVisible(false);}
        void getCursorPos(float& x, float& y){
            auto pos = sf::Mouse::getPosition(rWindow);
            x = pos.x;
            y = pos.y;    
        }


};

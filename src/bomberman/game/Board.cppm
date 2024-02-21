module;

import parser;
import Entity;
import viewAPI;
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>

export module Board;

#define NB_EFFECTS 10

//related to the chosen boardTexture.png
#define TEX_OFFSET 64
#define TEX_PER_LINE 16


//--------------------------------- TYPES OF BLOCS ---------------------------------

export class Bloc{
    protected:
        bool crossable;//traversable
        bool crossUp;//par en dessous
        bool crossDown;//par au dessus
        bool damaging;
        bool breakable;

        std::vector<Entity*> entities;

    public:
        int displayId;

        Bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable, int b_ID): 
            crossable(b_crossable), crossUp(b_crossUp), crossDown(b_crossDown), damaging(b_damaging), breakable(b_breakable), displayId(b_ID){}
        
        int getOffset(){return TEX_OFFSET*displayId;}

        virtual void printInfo() const {
            std::cout << "Generic Bloc" << std::endl;
        }

        virtual ~Bloc(){}
};


export class Wall: public Bloc{
    private:
    public:
        Wall(): Bloc(false, false, false, true, false, 1){}

        void printInfo() const override {
            std::cout << "Wall ";
        }
};

export class Air: public Bloc{
    private:
    public:
        Air(): Bloc(true, true, true, false, false, 2){}

        void printInfo() const override {
            std::cout << "Air ";
        }
};



class BonusBloc: public Bloc{
    private:
        Effect c_effect;
    public:
        BonusBloc(Effect b_effet): c_effect(b_effet), Bloc(true, true, true, false, true, 3){}
};

class BreakableWall: public Bloc{
    private:
        //bool bonus;
    public:
        BreakableWall():  Bloc(false, false, false, true, true, 4){}

        BonusBloc generateBonus(){
            Effect item = Effect(rand()%NB_EFFECTS);
            return BonusBloc(item);
        }
};

class ThinPlatform: public Bloc{
    private:
    public:
        ThinPlatform(): Bloc(false, true, false, false, false, 5){}
};

class BombBloc: public Bloc{
    private:
    public:
        BombBloc(): Bloc(false, false, false,  false, false, 6){}
};

class BombFlare: public Bloc{
    private:
    public:
        BombFlare(): Bloc(true, true, true, true, false, 7){}
};

//--------------------------------- BOARD ---------------------------------

export class Board{
    public:
        int width;
        int height;
        std::vector<std::unique_ptr<Bloc>> cases;
        float blocLength;
        
        Board(const std::string& xmlFilePath, RenderWindow& rWindow){
            loadBoard(xmlFilePath);
            updateBlocLength(rWindow);
        }
        Board(RenderWindow& rWindow): Board("./game_files/boards/default.xml",rWindow){}


        void loadBoard(const std::string& xmlFilePath){
            parsedXML xmlFile(xmlFilePath);
            width = xmlFile.width;
            height = xmlFile.height;
            for (auto it = xmlFile.cases.begin() ; it != xmlFile.cases.end() ; it++){
                if (*it == "Wall"){cases.push_back(std::make_unique<Wall>());}
                else if (*it == "Air"){cases.push_back(std::make_unique<Air>());}
            }
        }

        //for debug
        void displayBoard() const {
            int k = 0;
            for (const auto& bloc : cases) {
                if (k++%width == 0) {std::cout << std::endl;}
                bloc->printInfo();
            }
            std::cout << std::endl;
        }


        //Display related methods
        void updateBlocLength(RenderWindow& rWindow, float& xStart, float& yStart){
            float xSize; float ySize;
            rWindow.getSize(xSize, ySize);

            if (ySize/height > xSize/width){
                blocLength = xSize/width;
                xStart = 0;
                yStart = ySize/2 - blocLength*height/2;
            }
            else{
                blocLength = ySize/height;
                xStart = xSize/2 - blocLength*width/2 ;
                yStart = 0;
            }
        }
        void updateBlocLength(RenderWindow& rWindow){
            float unused; updateBlocLength(rWindow, unused, unused);   
        }

        void createSprites(Assets& assets){
            for (auto it = cases.begin() ; it != cases.end(); it++){assets.addSprite(2);}
        }

        void textureBinding(Assets& assets){
            for (auto k = 0; k < cases.size(); k++){assets.getSp(2+k).setTexRect(cases[k]->displayId, TEX_OFFSET, TEX_PER_LINE);}
        }

        void computeOffset(int k, float& xOffset, float& yOffset){
            xOffset=blocLength*(k%width); yOffset = blocLength*(k/height);
        }

};




//--------------------------------- COLLISION ---------------------------------

void collide(Entity ent){

}
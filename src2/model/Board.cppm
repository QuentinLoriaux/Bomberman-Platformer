module;

import parser;
import Entity;
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>

export module Board;

#define NB_EFFECTS 10




//--------------------------------- TYPES OF BLOCS ---------------------------------

export class Bloc{
    protected:
        bool crossable;//traversable
        bool crossUp;//par en dessous
        bool crossDown;//par au dessus
        bool damaging;
        bool breakable;
        bool bumpable;//fait bounce

        std::vector<Entity*> entities;

    public:
        Bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable, bool b_bumpable): 
            crossable(b_crossable), crossUp(b_crossUp), crossDown(b_crossDown), damaging(b_damaging), breakable(b_breakable), bumpable(b_bumpable){}
        
        virtual void printInfo() const {
            std::cout << "Generic Bloc" << std::endl;
        }

        virtual ~Bloc(){}
};


export class Wall: public Bloc{
    private:
    public:
        Wall(): Bloc(false, false, false, true, false, false){}

        void printInfo() const override {
            std::cout << "Wall ";
        }
};

export class Air: public Bloc{
    private:
    public:
        Air(): Bloc(true, true, true, false, false, false){}

        void printInfo() const override {
            std::cout << "Air ";
        }
};



class BonusBloc: public Bloc{
    private:
        Effect c_effect;
    public:
        BonusBloc(Effect b_effet): c_effect(b_effet), Bloc(true, true, true, false, true, false){}
};

class BreakableWall: public Bloc{
    private:
        //bool bonus;
    public:
        BreakableWall():  Bloc(false, false, false, true, true, false){}

        BonusBloc generateBonus(){
            Effect item = Effect(rand()%NB_EFFECTS);
            return BonusBloc(item);
        }
};

class ThinPlatform: public Bloc{
    private:
    public:
        ThinPlatform(): Bloc(false, true, false, false, false, false){}
};

class BombBloc: public Bloc{
    private:
    public:
        BombBloc(): Bloc(false, false, false,  false, false, false){}
};

class BombFlare: public Bloc{
    private:
    public:
        BombFlare(): Bloc(true, true, true, true, false, false){}
};

//--------------------------------- BOARD ---------------------------------

export class Board{
    private:
        int width;
        int height;
        std::vector<std::unique_ptr<Bloc>> cases;

    public:
        Board(){loadBoard("./game_files/boards/default.xml");}
        Board(const std::string& xmlFilePath){loadBoard(xmlFilePath);}

        void loadBoard(const std::string& xmlFilePath){
            parsedXML xmlFile(xmlFilePath);
            width = xmlFile.width;
            height = xmlFile.height;
            for (auto it = xmlFile.cases.begin() ; it != xmlFile.cases.end() ; it++){
                if (*it == "Wall"){cases.push_back(std::make_unique<Wall>());}
                else if (*it == "Air"){cases.push_back(std::make_unique<Air>());}
            }
        }


        void displayBoard() const {
            for (const auto& bloc : cases) {
                bloc->printInfo();
            }
            std::cout << std::endl;
        }
};




//--------------------------------- COLLISION ---------------------------------

void collide(Entity ent){

}
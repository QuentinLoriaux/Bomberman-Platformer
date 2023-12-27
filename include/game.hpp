#ifndef GAME_HPP
#define GAME_HPP


#include <vector>
#include <cstdlib> 

#define NB_EFFECTS 10


class Board{
    private:
        const int width;
        const int height;
        std::vector<Bloc> cases;

    public:
};

class Bloc{
    protected:
        bool crossable;
        bool crossUp;
        bool crossDown;
        bool damaging;
        bool breakable;
        bool bumpable;



    public:
        Bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable): 
            crossable(b_crossable), crossUp(b_crossUp), crossDown(b_crossDown), damaging(b_damaging), breakable(b_breakable), bumpable(b_bumpable){}
        
};

//--------------------------------- TYPES OF BLOCS ---------------------------------

class Wall: public Bloc{
    private:
    public:
        Wall(): Bloc(false, false, false, true, false, false){}
};

class Air: public Bloc{
    private:
    public:
        Air(): Bloc(true, true, true, false, false, false){}
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

class BonusBloc: public Bloc{
    private:
        Effect c_effect;
    public:
        BonusBloc(Effect b_effet): c_effect(b_effet), Bloc(true, true, true, false, true, true){}
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

//--------------------------------- bonus/malus effects ---------------------------------



class Effect{
    private:
        int id;
    public:
        Effect(int b_id): id(b_id){};
};


//--------------------------------- Entities ---------------------------------


// Contrairement aux Blocs, les entités peuvent se déplacer 
class Entity{
    protected:
        int wCoord;// index tableau
        int hCoord;
        float wPos;// position réelle
        float hPos;

        int hp;
        int speed;


    public:

};

class Player: public Entity{
    private:
        int playerId;
        int controllerId;
        int maxBomb;
        int activeBomb;// à l'écran

        std::vector<Effect> effects;

    public:
        void move(){}// Gauche ou Droite
        void jump(){}
        bool isAlive(){return hp==0;}
        bool pause(){}
        bool cameraMode(){}// 0: fixe | 1: suit le joueur 
};




class Monster: public Entity{
    private:
    public:
        void move(){}
        //void jump(){}
        bool isAlive(){return hp==0;}
};



#endif
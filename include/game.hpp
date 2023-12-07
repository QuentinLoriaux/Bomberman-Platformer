#ifndef GAME_HPP
#define GAME_HPP


#include <vector>
#include <cstdlib> 

#define NB_EFFECTS 10


class board{
    private:
        const int width;
        const int height;
        std::vector<bloc> cases;

    public:
};

class bloc{
    protected:
        bool crossable;
        bool crossUp;
        bool crossDown;
        bool damaging;
        bool breakable;



    public:
        bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable): 
            crossable(b_crossable), crossUp(b_crossUp), crossDown(b_crossDown), damaging(b_damaging), breakable(b_breakable){}
        
};

//--------------------------------- TYPES OF BLOCS ---------------------------------

class Wall: public bloc{
    private:
    public:
        Wall(): bloc(false, false, false, true, false){}
};

class Air: public bloc{
    private:
    public:
        Air(): bloc(true, true, true, false, false){}
};

class BreakableWall: public bloc{
    private:
        //bool bonus;
    public:
        BreakableWall():  bloc(false, false, false, true, true){}

        BonusBloc generateBonus(){
            Effect item = Effect(rand()%NB_EFFECTS);
            return BonusBloc(item);
        }
};

class BonusBloc: public bloc{
    private:
        Effect c_effect;
    public:
        BonusBloc(Effect b_effet): c_effect(b_effet), bloc(true, true, true, false, true){}
};

class ThinPlatform: public bloc{
    private:
    public:
        ThinPlatform(): bloc(false, true, false, false, false){}
};

class BombBloc: public bloc{
    private:
    public:
        BombBloc(): bloc(false, false, false,  false, false){}
};

class BombFlare: public bloc{
    private:
    public:
        BombFlare(): bloc(true, true, true, true, false){}
};

//--------------------------------- bonus/malus effects ---------------------------------



class Effect{
    private:
        int id;
    public:
        Effect(int b_id): id(b_id){};
};


//--------------------------------- Entities ---------------------------------


// Contrairement aux blocs, les entités peuvent se déplacer 
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
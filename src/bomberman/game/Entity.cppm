module;

#include <vector>

export module Entity;

//--------------------------------- bonus/malus effects ---------------------------------

export class Effect{
    private:
        int id;
    public:
        Effect(int b_id): id(b_id){};
};

//--------------------------------- Entities ---------------------------------

#define GRAVITY 3
#define TIME 0.3

export typedef enum _direction{
    NO_DIR,
    LEFT,
    RIGHT,
    DOWN,
    UP
} direction;




// Contrairement aux Blocs, les entités peuvent se déplacer 
export class Entity{
    // protected:
    public:
        int hCoord;// index tableau
        int vCoord;
        float hPos;// position réelle
        float vPos;
        bool grounded;

        direction dir; //input direction
        float vSpeed;
        float hSpeed;
        
        std::vector<int> closeBlocs;

        int hp;
        




        bool isAlive(){return hp==0;}

        void updateHSpeed(){
            if (grounded){ hSpeed = 0};
            else{
                float newSpeed = vSpeed - GRAVITY*TIME;
                if (newSpeed > - GRAVITY){vSpeed = newSpeed;}  
            }
        }

        void setGrounded(){grounded = true;}

        void updatePos(){
            switch (dir){
                case LEFT : hPos += hSpeed * TIME; break;
                case RIGHT : hPos -= hSpeed * TIME; break;
                default:
                    break;
            }             
            vPos = vSpeed * TIME;
        }


};

export class Player: public Entity{
    private:
        
        bool dirPressed;// for horizontal movement
        
        
        int playerId;
        int controllerId;

        int maxBomb;
        int activeBomb;// à l'écran

        std::vector<Effect> effects;



    public:
        void move(){}// Gauche ou Droite
        void jump(){}
        
        bool pause(){}
        bool cameraMode(){}// 0: fixe | 1: suit le joueur 
};




export class Monster: public Entity{
    private:
    public:
        void move(){}
        //void jump(){}
        // bool isAlive(){return hp==0;}
};


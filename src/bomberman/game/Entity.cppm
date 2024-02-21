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
        int blocIndex;// index tableau pour bombes
        float xPos;// position réelle
        float yPos;
        

        direction dir; //input direction
        float ySpeed;
        float xSpeed;
        bool grounded;

        float xSize;//1 = côté d'une case
        float ySize;
        
        std::vector<int> closeBlocs;

        int hp;
        

        Entity(int _blocIndex, float _xPos, float _yPos): blocIndex(_blocIndex), xPos(_xPos), yPos(_yPos), dir(NO_DIR), ySpeed(0), xSpeed(0), grounded(true),
                xSize(0.5), ySize(0.75), closeBlocs(std::vector<int>()), hp(1) {}


        bool isAlive(){return hp==0;}

        void updateYSpeed(){
            if (grounded){ xSpeed = 0;}
            else{
                float newSpeed = ySpeed - GRAVITY*TIME;
                if (newSpeed > - GRAVITY){ySpeed = newSpeed;}  
            }
        }

        void setGrounded(){grounded = true;}

        void updatePos(){
            switch (dir){
                case LEFT : xPos += xSpeed * TIME; break;
                case RIGHT : xPos -= xSpeed * TIME; break;
                default:
                    break;
            }             
            yPos = ySpeed * TIME;
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
        Monster(int _blocIndex, float _xPos, float _yPos): Entity(_blocIndex, _xPos, _yPos){}

        void move(){}
        //void jump(){}
};


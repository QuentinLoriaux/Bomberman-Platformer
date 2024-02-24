module;

#include <vector>
#include <iostream>
#include <chrono>

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

#define X_SIZE 0.5
#define Y_SIZE 0.75

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
        std::vector<int> closeBlocs; //pour collisions
        int blocIndex;// indice tableau pour bombes
        float xPos;// position réelle
        float yPos;

        float xSize;//1 = côté d'une case
        float ySize;        

        direction dir; //input direction
        float ySpeed;
        float xSpeed;
        bool grounded;

        int hp;
        int SpriteId;
        int entityId;
        

        Entity(int _blocIndex, float _size, int _entityId): blocIndex(_blocIndex), xPos(0), yPos(0), dir(NO_DIR), ySpeed(0), xSpeed(0), grounded(true),
                xSize(X_SIZE*_size), ySize(Y_SIZE*_size), closeBlocs(std::vector<int>()), hp(1), entityId(_entityId) {}
        
        // virtual ~Entity(){};


        bool isAlive(){return hp==0;}
        void setGrounded(){grounded = true;}

        void updateYSpeed(){
            if (grounded){ ySpeed = 0;}
            else{
                float newSpeed = ySpeed - GRAVITY*TIME;
                if (newSpeed > - GRAVITY){ySpeed = newSpeed;}  
            }
        }

        void updatePos(){
            switch (dir){
                case LEFT : xPos += xSpeed * TIME; break;
                case RIGHT : xPos -= xSpeed * TIME; break;
                default:
                    break;
            }             
            yPos = ySpeed * TIME;
        }

        void animation(){std::cout << "hello, I wanna moooove" << std::endl;}


};

export class Player: public Entity{
    public:
        
        bool dirPressed;// for horizontal movement
        
        
        int playerId;
        int controllerId;

        int maxBomb;
        int activeBomb;// à l'écran

        std::vector<Effect> effects;


        Player(int _blocIndex, float _size): Entity(_blocIndex, _size, 0){}
        // ~Player(){}

        // void move(){}// Gauche ou Droite
        // void jump(){ySpeed = GRAVITY;}
        
        void pause(){}
        void cameraMode(){}// 0: fixe | 1: suit le joueur 

        void animation(){
            static auto startFrameTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now(); 
        }
};




export class Monster: public Entity{
    private:
    public:
        // Monster(int _blocIndex, float _xPos, float _yPos): Entity(_blocIndex, _xPos, _yPos){}
        Monster(int _blocIndex, float _size): Entity(_blocIndex, _size, 1){}
        // ~Monster(){};

        void move(){}
        //void jump(){}
        void animation(){
            static auto startFrameTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now(); 
        }
};



// =============== Actions for bindings ===============


export void jump(Player& player){
    player.ySpeed = GRAVITY;
}

export void move(Player& player){
    player.dirPressed = true;
}
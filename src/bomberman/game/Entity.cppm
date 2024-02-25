module;

import assetsBindings;
import viewAPI;
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

#define GRAVITY 5
#define TIME 0.01

#define X_SIZE 0.5
#define Y_SIZE 0.75

#define X_SPEED 3

export typedef enum _direction{
    NO_DIR,
    LEFT,
    RIGHT,
    DOWN,
    UP
} direction;



export class Entity{
    public:
        std::vector<int> closeBlocs; //pour collisions
        int blocIndex;// indice tableau pour bombes
        float xPos;// position réelle
        float yPos;

        float xSize;// 1 = blocLength
        float ySize;        

        direction dir; // input direction
        float ySpeed;
        float xSpeed;
        bool grounded;

        int hp;
        int spriteId;
        int entityId;
        

        Entity(int _blocIndex, float _size, int _entityId):  blocIndex(_blocIndex), xPos(0), yPos(0), dir(NO_DIR), xSize(X_SIZE*_size), ySize(Y_SIZE*_size), ySpeed(0), xSpeed(0), grounded(true),
                 hp(1), spriteId(0), entityId(_entityId) {}
        
        virtual ~Entity(){};


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
            updateYSpeed();
            switch (dir){
                case LEFT : xPos -= xSpeed; break;
                case RIGHT : xPos += xSpeed; break;
                default:
                    break;
            }             
            yPos -= ySpeed;
        }

        void animation(){std::cout << "hello, I wanna moooove" << std::endl;}

        virtual void setSprite(Sprite& sp){std::cout << "Im da best sprite eva" << std::endl;}

};







export class Player: public Entity{
    public:
        
        
        int playerId;
        int controllerId;

        int maxBomb;
        int activeBomb;// à l'écran

        
        std::vector<Effect> effects;


        Player(int _blocIndex, float _size): Entity(_blocIndex, _size, 0){}

        // void move(){}// Gauche ou Droite
        // void jump(){ySpeed = GRAVITY;}
        
        // void pause(){}
        // void cameraMode(){}// 0: fixe | 1: suit le joueur 

        void animation(){
            static auto startFrameTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now(); 
        }

        void setSprite(Sprite& sp){
            static std::vector<int> playerSprites = bombermanTexBinding();
            sp.setTexRect(spriteId, playerSprites);
        }
};




export class Monster: public Entity{
    private:
    public:
        Monster(int _blocIndex, float _size): Entity(_blocIndex, _size, 1){}

        //void jump(){}
        void animation(){
            static auto startFrameTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now(); 
        }

        void setSprite(Sprite& sp){
            static std::vector<int> monsterSprites = monsterTexBinding();
            sp.setTexRect(spriteId, monsterSprites);
        }
};



// =============== Actions for bindings ===============


export void jump(Player& player){
    if (player.grounded){
        player.ySpeed = GRAVITY;
        player.grounded = false;
    }
}

export void walkLeft(Player& player){
    player.xSpeed = X_SPEED;
    player.dir = LEFT;
}
export void walkRight(Player& player){
    player.xSpeed = X_SPEED;
    player.dir = RIGHT;
}

export void stopWalkLeft(Player& player){
    if (player.dir == LEFT) {player.dir = NO_DIR; player.xSpeed = 0;}
}
export void stopWalkRight(Player& player){
    if (player.dir == RIGHT) {player.dir = NO_DIR; player.xSpeed = 0;}
}
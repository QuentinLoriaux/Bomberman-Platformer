module;

import assetsBindings;
import viewAPI;
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

export module Entity;

//--------------------------------- bonus/malus effects ---------------------------------

export class Effect{
    private:
        int id;
    public:
        Effect(int b_id): id(b_id){};
};

//--------------------------------- Entities ---------------------------------

#define GRAVITY 0.05
#define TIME 0.03

#define X_SIZE 0.5
#define Y_SIZE 0.75

#define X_SPEED 0.05


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
        float xTry;//supposant pas de collision
        float yTry;
        static int width;

        float xSize;// 1 = blocLength
        float ySize;        

        direction dir; // input direction
        direction facing;
        float ySpeed;
        float xSpeed;
        bool grounded;

        int hp;
        int entityId;
        

        Entity(int _blocIndex, float _size, int _entityId):  blocIndex(_blocIndex), xPos(0), yPos(0), dir(NO_DIR), xSize(X_SIZE*_size), ySize(Y_SIZE*_size), ySpeed(0), xSpeed(0), grounded(true),
                 hp(1), entityId(_entityId), facing(RIGHT) {}
        
        virtual ~Entity(){};

        static void setWidth(int _width){width = _width;}

        bool isAlive(){return hp==0;}
        void setGrounded(){
            grounded = true;
        }

        void updateYSpeed(){
            if (grounded){ ySpeed = 0;}
            else{
                float newSpeed = ySpeed - GRAVITY*TIME;
                if (newSpeed > - GRAVITY){ySpeed = newSpeed;}  
            }
        }

        void tryPos(){
            updateYSpeed();
            switch (dir){
                case LEFT : xTry = xPos - xSpeed; break;
                case RIGHT : xTry = xPos + xSpeed; break;
                default:
                    break;
            }             
            yTry = yPos - ySpeed;
        }

        void correctPos(direction collDir){
            switch (collDir){
                case LEFT : 
                case RIGHT : 
                    xTry = xPos; break;
                case UP : 
                    std::cout << "UP\n";
                    yTry = yPos;
                    ySpeed = 0;
                case DOWN :
                    std::cout << "DOWN\n";
                    yTry = yPos;
                    setGrounded();
                default:
                    break;
            }             
        }

        void updatePos(){xPos = xTry; yPos = yTry;}

        void updateBlocIndex(){
            int xCenter = xPos + xSize/2;
            int yCenter = yPos + ySize/2;
            blocIndex = xCenter+width*yCenter;
        }

        void updateCloseBlocs(){
            int x1 = xTry - 0.1;
            int x2 = xTry + xSize;
            int y1 = width*(int)yTry;
            int y2 = width*(int)(yTry+ySize);
            closeBlocs.assign({
                //gauche
                x1 + y1 -1,
                x1 + y2 -1,
                //droite
                x2 + y1 +1,
                x2 + y2 +1,
                //rectangle collision
                x1 + y1,
                x2 + y1,
                x1 + y2,
                x2 + y2,
            });
            if (!grounded){
                closeBlocs.push_back(x1 + y2 + width); 
                closeBlocs.push_back(x2+ y2 + width); 
            }
            //remove redundancies
            std::sort(closeBlocs.begin(), closeBlocs.end());
            auto it = std::unique(closeBlocs.begin(), closeBlocs.end());
            closeBlocs.erase(it, closeBlocs.end());
        }

        direction collideBloc(int k){
            bool headIn = (k/width < yTry && yTry < k/width+1);
            bool footIn = (k/width < yTry+ySize && yTry+ySize < k/width+1);
            bool leftIn =  (k%width < xTry && xTry < k%width+1);
            bool rightIn = (k%width < xTry+xSize && xTry+xSize < k%width+1);
            bool vertiAlign = headIn && footIn;
            bool horizAlign =  leftIn && rightIn;

            if (!grounded && horizAlign){
                if (headIn){return UP;}
                else if (footIn){return DOWN;}
            }
            if (vertiAlign){
                if (leftIn){return LEFT;}
                else if (rightIn){return RIGHT;}
            }


            //coins...
            //ne pas tomber d'une plateforme
            if (headIn && leftIn){
                return (yTry - k/width > xTry - k%width) ? LEFT:UP;
            }
            if (headIn && rightIn){
                return (yTry - k/width > xTry + xSize - k%width) ? RIGHT:UP;
            }
            if (!grounded && footIn && leftIn){
                return (yTry + ySize - k/width > xTry - k%width) ? LEFT:DOWN;
            }
            if (!grounded && footIn && rightIn){
                return (yTry + ySize - k/width > xTry + xSize - k%width) ? RIGHT:DOWN;
            }
            return NO_DIR;
        }


        virtual void setSprite(Sprite& sp){std::cout << "Im da best sprite eva" << std::endl;}

};

int Entity::width = 0;





export class Player: public Entity{
    public:
        
        
        int playerId;
        int controllerId;

        int maxBomb;
        int activeBomb;// à l'écran

        
        std::vector<Effect> effects;


        Player(int _blocIndex, float _size): Entity(_blocIndex, _size, 0), maxBomb(1), activeBomb(0){}


        
        // void pause(){}
        // void cameraMode(){}// 0: fixe | 1: suit le joueur 



        void setSprite(Sprite& sp){
            static std::vector<int> playerSprites = bombermanTexBinding();

            static auto begin = std::chrono::steady_clock::now();
            const std::chrono::duration<double> second(1.0);
            auto now = std::chrono::steady_clock::now();
            auto timer =  now - begin;
            
            int spriteId = 0;
            

            if (!grounded){
                spriteId = 6;
                if (timer > 0.4*second){
                    begin = now;
                    // sp.mirror();
                    facing = (facing == LEFT) ? RIGHT:LEFT; 
                }
            }
            else if (dir == NO_DIR) {
                spriteId = 7;
            }
            else {
                if (timer < 0.2*second){spriteId = 3;}
                else if (timer < 0.4*second){spriteId = 4;}
                else if (timer < 0.6*second){spriteId = 3;}
                else if (timer < 0.8*second){spriteId = 1;}
                else{begin = now;}
                
                facing = dir;
            }
            
            sp.setTexRect(spriteId, playerSprites);
            
        }
};




export class Monster: public Entity{
    private:
    public:
        Monster(int _blocIndex, float _size): Entity(_blocIndex, _size, 1){}

        //void jump(){}


        void setSprite(Sprite& sp){
            static std::vector<int> monsterSprites = monsterTexBinding();
            
            static auto startFrameTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now(); 
            
            sp.setTexRect(0, monsterSprites);
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

export void debug(Player& player){
    std::cout << 
    "blocIndex : " << player.blocIndex <<
    "\nxPos : " << player.xPos <<
    "\nyPos : " << player.yPos <<
    "\nxSize : " << player.xSize <<
    "\nySize : " << player.ySize <<
    "\nxSpeed : " << player.xSpeed <<
    "\nySpeed : " << player.ySpeed <<
    "\nhp : " << player.hp <<
    "\ncloseBlocs : " ;
    for (auto& bloc : player.closeBlocs) { 
        std::cout << bloc << " "; 
    } 
    std::cout << std::endl;

}
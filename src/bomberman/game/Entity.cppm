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

#define GRAVITY 0.003

#define X_SIZE 0.5
#define Y_SIZE 0.75

#define X_SPEED 0.05
#define Y_SPEED 0.12


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
        static int height;

        float xSize;// 1 = blocLength
        float ySize;        

        direction dir; // input direction
        direction facing;
        float xSpeed;
        float ySpeed;
        bool grounded;

        int hp;
        int entityId;
        std::chrono::time_point<std::chrono::steady_clock> spriteTimer;
        

        Entity(int _blocIndex, float _size, int _entityId):  blocIndex(_blocIndex), xPos(0), yPos(0), xSize(X_SIZE*_size), ySize(Y_SIZE*_size), dir(NO_DIR), facing(RIGHT), xSpeed(0), ySpeed(0),
                 hp(1), entityId(_entityId), spriteTimer(std::chrono::steady_clock::now()){}
        
        virtual ~Entity(){};

        static void setBoardDims(int _width, int _height){width = _width; height = _height;}

        bool isAlive(){return hp>0;}


        void updateYSpeed(){
                float newSpeed = ySpeed - GRAVITY;
                if (newSpeed > - Y_SPEED){ySpeed = newSpeed;}  

                if (ySpeed < - 2 * GRAVITY) { grounded = false;}
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

            //Borders of the board
            if (xTry + xSize > width || xTry < 0) {xTry = xPos;}
            if (yTry > height || yTry < 0) {yTry = yPos; ySpeed = 0;}
        }

        void correctPos(direction collDir){
            switch (collDir){
                case LEFT : 
                case RIGHT : 
                    xTry = xPos; break;
                case UP : 
                    // std::cout << "UP\n";
                    yTry = yPos;
                    ySpeed = 0;
                    break;
                case DOWN :
                    // std::cout << "DOWN\n";
                    yTry = static_cast<int>(yTry+ySize)-ySize;
                    ySpeed = 0;
                    grounded = true;
                    break;
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

        virtual void updateCloseBlocs(){
            int x1 = xTry;
            int x2 = xTry + xSize;
            int y1 = width*(int)yTry;
            int y2 = width*(int)(yTry+ySize);
            closeBlocs.assign({
                //rectangle collision
                x1 + y1,
                x2 + y1,
                x1 + y2,
                x2 + y2,
            });

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
            bool goLeft = xTry < xPos;
            bool goRight = xTry > xPos;
            bool goUp = yTry < yPos;
            bool goDown = yTry > yPos;

            if (!grounded && horizAlign){
                if (headIn && goUp){ return UP;}
                else if (footIn && goDown){return DOWN;}
            }
            if (vertiAlign){
                if (leftIn && goLeft){return LEFT;}
                else if (rightIn && goRight){return RIGHT;}
            }


            //coins...
            if (headIn && leftIn){
                if (k/width +1 - yTry > k%width + 1 - xTry){
                    if (goLeft) return LEFT;
                }
                else {
                    if (goUp) return UP;
                } 
            }
            if (headIn && rightIn){
                // return (k/width +1 - yTry > xTry + xSize - k%width) ? RIGHT:UP;
                if (k/width +1 - yTry > xTry + xSize - k%width){
                    if (goRight) return RIGHT;
                }
                else {
                    if (goUp) return UP;
                } 
            }
            if (footIn && leftIn){
                // return (yTry + ySize - k/width > k%width + 1 - xTry) ? LEFT:DOWN;
                if (yTry + ySize - k/width > k%width + 1 - xTry){
                    if (goLeft && !grounded) return LEFT;
                }
                else {
                    if (goDown) return DOWN;
                } 
            }
            if (footIn && rightIn){
                // return (yTry + ySize - k/width > xTry + xSize - k%width) ? RIGHT:DOWN;
                if (yTry + ySize - k/width > xTry + xSize - k%width){
                    if (goRight) return RIGHT;
                }
                else {
                    if (goDown) return DOWN;
                } 
            }
            return NO_DIR;
        }


        virtual void setSprite(Sprite& sp){std::cout << "Im da best sprite eva" << std::endl;}

};

int Entity::width = 0;
int Entity::height = 0;





export class Player: public Entity{
    public:
        
        
        int playerId;
        int controllerId;

        int maxBomb;
        int activeBomb;// à l'écran
        
        int crossableBomb;//to prevent collision with bomb when placing it
        
        std::vector<Effect> effects;


        Player(int _blocIndex, float _size): Entity(_blocIndex, _size, 0),
        maxBomb(1), activeBomb(0), crossableBomb(-1){}

        // void pause(){}
        // void cameraMode(){}// 0: fixe | 1: suit le joueur 

        void updateCloseBlocs(){
            Entity::updateCloseBlocs();
            
            //can move freely through placed bomb until out
            if (std::find(closeBlocs.begin(), closeBlocs.end(),crossableBomb)!=closeBlocs.end()){
                closeBlocs.erase(std::remove(closeBlocs.begin(), closeBlocs.end(), crossableBomb), closeBlocs.end());
            }
            else{
                crossableBomb = -1;
            }
            
        }


        void setSprite(Sprite& sp){
            static std::vector<int> playerSprites = bombermanTexBinding();

            const std::chrono::duration<double> second(1.0);
            auto now = std::chrono::steady_clock::now();
            auto timer =  now - spriteTimer;
            
            int spriteId = 0;
            

            if (!grounded){
                spriteId = 6;
                if (timer > 0.4*second){
                    spriteTimer = now;
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
                else{spriteTimer = now;}
                
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
            
            auto currentTime = std::chrono::steady_clock::now(); 
            
            sp.setTexRect(0, monsterSprites);
        }

        void updateCloseBlocs(){
            Entity::updateCloseBlocs();
        }
};



// =============== Actions for bindings ===============


export void jump(Player& player){
    if (player.grounded){
        player.ySpeed = Y_SPEED;
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
    "\ngrounded : " << player.grounded <<
    "\ncloseBlocs : " ;
    for (auto& bloc : player.closeBlocs) { 
        std::cout << bloc << " "; 
    } 
    std::cout << std::endl;

}
module;

import parser;
import Entity;
import viewAPI;
import assetsBindings;
#include <memory>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>

export module Board;

#define NB_EFFECTS 10



//--------------------------------- TYPES OF BLOCS ---------------------------------

export class Bloc{
    public:
        bool crossable;//traversable
        bool crossUp;//par en dessous
        bool crossDown;//par au dessus

        bool damaging; bool breakable;
        int displayId;
        bool playerSpawn; bool monsterSpawn;

        // std::vector<Entity*> entities;

        
        Bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable, int b_ID): 
            crossable(b_crossable), crossUp(b_crossUp), crossDown(b_crossDown),
            damaging(b_damaging), breakable(b_breakable), displayId(b_ID),
            playerSpawn(false), monsterSpawn(false){}

        Bloc(bool b_crossable, bool b_crossUp, bool b_crossDown, bool b_damaging, bool b_breakable, int b_ID, bool b_playerSpawn, bool b_monsterSpawn): 
            Bloc(b_crossable, b_crossUp, b_crossDown, b_damaging, b_breakable, b_ID) {playerSpawn = b_playerSpawn; monsterSpawn = b_monsterSpawn;}
        

        

        virtual void printInfo() const {
            std::cout << "Generic Bloc" << std::endl;
        }

        virtual ~Bloc(){}
};

export class Undefined: public Bloc{
    private:
    public:
        Undefined(): Bloc(false, false, false, 
                     false, false, 0){}

        void printInfo() const override {
            std::cout << "Undefined ";
        }
};

export class Wall: public Bloc{
    private:
    public:
        Wall(): Bloc(false, false, false, 
                     false, false, 1){}

        void printInfo() const override {
            std::cout << "Wall ";
        }
};

export class Air: public Bloc{
    private:
        

    public:
        Air(): Bloc(true, true, true,
                    false, false, 2){}

        void printInfo() const override {
            std::cout << "Air ";
        }
};

export class playerSpawn: public Bloc{
    private:
    public:
        playerSpawn(): Bloc(true, true, true,
                            false, false, 3,//provisoire
                            true, false){}

        void printInfo() const override {
            std::cout << "playerSpawn ";
        }
};

export class monsterSpawn: public Bloc{
    private:
    public:
        monsterSpawn(): Bloc(true, true, true,
                            false, false, 4,//provisoire
                            false, true){}

        void printInfo() const override {
            std::cout << "monsterSpawn ";
        }
};

class BonusBloc: public Bloc{
    private:
        Effect c_effect;
    public:
        BonusBloc(Effect b_effet): Bloc(true, true, true,
                                        false, true, 5),
                                    c_effect(b_effet){}
        BonusBloc(): Bloc(true, true, true,
                        false, true, 5){}
};

class BreakableWall: public Bloc{
    private:
        //bool bonus;
    public:
        BreakableWall():  Bloc(false, false, false,
                               true, true, 6){}

        BonusBloc generateBonus(){
            Effect item = Effect(rand()%NB_EFFECTS);
            return BonusBloc(item);
        }
};

class ThinPlatform: public Bloc{
    private:
    public:
        ThinPlatform(): Bloc(false, true, false,
                             false, false, 7){}
};

export class BombBloc: public Bloc{
    public:
        Player* player;
        std::chrono::time_point<std::chrono::steady_clock> countDown;
    
        BombBloc(Player& _player): Bloc(false, false, false, 
                         false, false, 8),
                         player(&_player),
                         countDown(std::chrono::steady_clock::now()){}
        
        bool endedCountDown(){
            const std::chrono::duration<double> second(1.0);
            auto now = std::chrono::steady_clock::now();
            return (now - countDown > 2*second);
        }


};

export class BombFlare: public Bloc{
    private:
        std::chrono::time_point<std::chrono::steady_clock> lifeTime;
    public:
        BombFlare(): Bloc(true, true, true,
                          true, false, 9),
                          lifeTime(std::chrono::steady_clock::now()){}
        
        bool endedLifeTime(){
            const std::chrono::duration<double> second(1.0);
            auto now = std::chrono::steady_clock::now();
            return (now - lifeTime > 0.5*second);
        }

};

//--------------------------------- BOARD ---------------------------------

//idéalement, séparer Board/gameBoard/editorBoard
export class Board{
    public:
        int width;
        int height;
        std::vector<std::shared_ptr<Bloc>> cases;
        std::vector<std::shared_ptr<Entity>> entities;
        std::vector<std::shared_ptr<Player>> players;
        float blocLength;
        
        Board(const std::string& xmlFilePath){
            loadBoard(xmlFilePath);
            // updateBlocLength(rWindow);
        }
        // Board(RenderWindow& rWindow): Board("./game_files/boards/default.xml",rWindow){}

        Board(){//default map so we don't need a file to start it
            width = 7; height = 5;
            for (int k = 0 ; k <8; k++){cases.push_back(std::make_shared<Air>());}
            cases.push_back(std::make_shared<monsterSpawn>());
            for (int k = 0 ; k <3; k++){cases.push_back(std::make_shared<Air>());}
            cases.push_back(std::make_shared<monsterSpawn>());
            cases.push_back(std::make_shared<Air>());
            for (int k = 0 ; k <2; k++){cases.push_back(std::make_shared<Wall>());}
            for (int k = 0 ; k <3; k++){cases.push_back(std::make_shared<Air>());}
            for (int k = 0 ; k <3; k++){cases.push_back(std::make_shared<Wall>());}
            for (int k = 0 ; k <2; k++){cases.push_back(std::make_shared<Air>());}
            cases.push_back(std::make_shared<playerSpawn>());
            cases.push_back(std::make_shared<Air>());
            cases.push_back(std::make_shared<playerSpawn>());
            cases.push_back(std::make_shared<Air>());
            for (int k = 0 ; k <7; k++){cases.push_back(std::make_shared<Wall>());}
        }


        void loadBoard(const std::string& xmlFilePath){
            parsedXML xmlFile(xmlFilePath);
            width = xmlFile.width;
            height = xmlFile.height;
            for (auto it = xmlFile.cases.begin() ; it != xmlFile.cases.end() ; it++){
                if (*it == "Undefined"){cases.push_back(std::make_shared<Undefined>());}
                else if (*it == "Wall"){cases.push_back(std::make_shared<Wall>());}
                else if (*it == "Air"){cases.push_back(std::make_shared<Air>());}
                else if (*it == "playerSpawn"){cases.push_back(std::make_shared<playerSpawn>());}
                else if (*it == "monsterSpawn"){cases.push_back(std::make_shared<monsterSpawn>());}
                else if (*it == "BonusBloc"){cases.push_back(std::make_shared<BonusBloc>());}
            }
        }

        // ====== for debug ====== 
        void displayBoard() const {
            int k = 0;
            for (const auto& bloc : cases) {
                if (k++%width == 0) {std::cout << std::endl;}
                bloc->printInfo();
            }
            std::cout << std::endl;
        }




        // ====== For Board ======
        void updateBlocLength(RenderWindow& rWindow, float& xStart, float& yStart){
            float xSize; float ySize;
            rWindow.getSize(xSize, ySize);
            // std::cout << xSize << "," << ySize << std::endl;

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

        void blocOffset(int k, float& xOffset, float& yOffset){
            xOffset=blocLength*(k%width); yOffset = blocLength*(k/width);
        }

        void setBlocSprite(Sprite& sp, int k){
            static std::vector<int> boardSprites = boardTexBinding();
            sp.setTexRect(cases[k]->displayId, boardSprites);}

        // ====== For entities ======



        template<typename T>
        int addEntity(int blocIndex, int size){//size = 1 => 0.75*blocLength

            entities.push_back(std::make_shared<T>(blocIndex, size));
            auto ent = entities[entities.size()-1];
            ent->xPos = (blocIndex%width)*blocLength;
            ent->yPos = (blocIndex/width + 1 - ent->ySize)*blocLength;
            return entities.size() - 1;
        }
        template<typename T>
        int addEntity(int blocIndex){return addEntity<T>(blocIndex, 1);} 

        int addMonster(int blocIndex){return addEntity<Monster>(blocIndex);}


        int addPlayer(int blocIndex){
            players.push_back(std::make_shared<Player>(blocIndex, 1));
            auto player = players[players.size()-1];
            player->xPos = (blocIndex%width)*blocLength;
            player->yPos = (blocIndex/width + 1 - player->ySize)*blocLength;
            entities.push_back(player);
            return players.size()-1;
        }


        void setFirstTimeEntityPos(){
            for (unsigned int k = 0 ; k < entities.size() ; k++){
                auto& ent = *entities[k];
                int position = ent.blocIndex;
                ent.xPos = position%width; ent.yPos =  position/width + 1 - ent.ySize;
                ent.xTry = ent.xPos; ent.yTry = ent.yPos;
            }
        }

        // ====== game mechanics ======
        int explode(int k, Player& player){
            player.activeBomb--;
            player.crossableBomb = -1;
            cases[k] = std::make_shared<BombFlare>();
            if (k > width && cases[k-width]->displayId == 2 ){//bloc du haut
                cases[k-width] = std::make_shared<BombFlare>();
            }

            if (k < width*(height - 1) && cases[k+width]->displayId == 2 ){//bloc du bas
                cases[k+width] = std::make_shared<BombFlare>();
            }


            if (k%width > 0 && cases[k-1]->displayId == 2 ){//bloc de gauche
                cases[k-1] = std::make_shared<BombFlare>();
            }


            if (k%width < width && cases[k+1]->displayId == 2 ){//bloc du haut
                cases[k+1] = std::make_shared<BombFlare>();
            }

            return 1;
        }
        //if breakableWall : bonus or not

        void freeSpace(int k){
            cases[k] = std::make_shared<Air>();
        }


        // ====== for Editor ======

        void updateBlocLengthEditor(RenderWindow& rWindow, float& xStart, float& yStart){
            float xSize; float ySize;
            rWindow.getSize(xSize, ySize);
            // std::cout << xSize << "," << ySize << std::endl;
            xStart = xSize*(1./16.);// taille du bouton gauche
            yStart = ySize*(1./16.);// taille du bouton haut

            if (ySize/height > xSize/width){
                blocLength = (xSize/width)*(3./4.);
                xStart += 0;
                yStart += (ySize/2)*(3./4.) - blocLength*height/2;
            }
            else{
                blocLength = (ySize/height)*(3./4.);
                xStart += (xSize/2)*(3./4.) - blocLength*width/2 ;
                yStart += 0;
            }
        }

        void changeBloc(int k, int newBlocId){
            switch (newBlocId)
            {
            case 0:
                cases[k]=std::make_shared<Undefined>(); break;
            case 1:
                cases[k]=std::make_shared<Wall>(); break;
            case 2:
                cases[k]=std::make_shared<Air>(); break;
            case 3:
                cases[k]=std::make_shared<playerSpawn>(); break;
            case 4:
                cases[k]=std::make_shared<monsterSpawn>(); break;
            case 5:
                cases[k]=std::make_shared<BonusBloc>(); break;
            default:
                break;
            }
        }
};




//--------------------------------- COLLISION ---------------------------------


// =============== Actions modifying board ===============



export void placeBomb(Player& player, Board& board){
    if (player.activeBomb < player.maxBomb && player.isAlive()){
        player.activeBomb++;
        board.cases[player.blocIndex]= std::make_shared<BombBloc>(player);
        player.crossableBomb = player.blocIndex;
    }
}
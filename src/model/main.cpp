#include <vector>
#include <iostream>
#include <any>
import tMode;

import Event;
import viewAPI;

import loader;
import initializer;

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define FPS 60



int main()
{
    
    // Create the main window
    RenderWindow rWindow(W_WIDTH, W_HEIGHT, "Bomberman Platformer");

    // load fonts
    std::vector<Font> fontList;
    fontList.push_back(Font("arial.ttf"));

    // Initialize game mode
    mode gameMode = MAIN_TITLE;

    // App loop
    while (gameMode != END){
        //=========================== VARIABLES ===========================

        //===== General variables =====
        //std::vector<std::any*> drawOrder; //Contiendra des pointeurs sur chaque élément à dessiner, dans l'ordre    
        Event event(rWindow);
        std::vector<EventBinding> &eventsMonitored;
            

        //assets
        std::vector<Sprite> spriteList;
        std::vector<Text> textList;
        
        std::vector<Sound> soundList;
        std::vector<Music> musicList;



        //===== Menu Variables ===== 
        //std::vector<MenuEntry> menu;
        //int menuCursor;
        
        //===== Editor Variables ===== 
        // Tableau de blocs etc...

        //=========================== LOAD & INIT ===========================

        loadAssets(gameMode, spriteList, soundList, musicList);

        // initialisation de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // Ex : menu...

        EventBinding evQuit(quitGame);
        evQuit.addTypes(CROSS, ESC);//ESC for testing
        eventsMonitored.push_back(evQuitGame);

        initialize(gameMode, eventsMonitored, ...)//TODO

        



        // On va loader le reste des textes plus tard, selon les besoins
        // idem pour la liste evenements


        //=========================== MAIN LOOP ===========================
        
        //Play Music
        musicList[0].play();

        while (gameMode != END){
            
            // Process events + play sounds
                //close window, button pressed (Menu, Movement), Request to load a game mode...
            while (event.poll()){
                for (auto it = eventsMonitored.begin(); it != eventsMonitored.end() ; it++){
                    if (event.isMonitored(it->getTypes())){ it-> execute();}
                }
            }
            
            


            
            // Update variables ---> SPECIFIC TO EACH MODE
                /*
                    Se fait conjointement aux events
                    (y a des trucs qui ne dépendent pas d'events et qui sont soumis à un TIMER comme l'animation d'une bombe)

                    Menu : cursor position 
                    Editor : FavMenu, current cursor item, state of the map...

                    display_state

                    On peut se débrouiller pour ne calculer les positions relatives à l'écran que lorsque l'on display 
                    (à chaque frame)
                */




            // Display (tous les 1/60s)
            //BESOIN D'UN TIMER
            
            // for (auto it = drawOrder.begin(); it != drawOrder.end() ; it++ ){
            //     rWindow.draw(*it);
            // }
            std::cout << "toto" << std::endl;
        }
    }//End of App loop

    std::cout << "/nGoodBye!/n";

    return EXIT_SUCCESS;
}
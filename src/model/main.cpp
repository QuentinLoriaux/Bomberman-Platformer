#include <vector>
#include <iostream>
#include <any>
import tMode;

import viewAPI;
import loader;

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define FPS 60


//Drawable contains the SPRITES and also the POSITION of each sprite 



mode mainLoop(mode gameMode){
    //Initialize local variables
    
    std::vector<Sprite> spriteList;
    std::vector<Font> fontList;
        fontList.push_back(Font("arial.ttf"));
    std::vector<Text> textList;
    std::vector<std::any*> drawOrder;//Contiendra des pointeurs sur chaque élément à dessiner dans l'ordre
    
    //std::vector<Sound> soundEffects;
    Music playingMusic;
    
    //std::vector<Events> eventsMonitored;
    //addEvent(&quitGame, CROSS, ESC);

    void (*stateUpdate)();
    
    switch (gameMode){
        
        case MAIN_TITLE:{
            //std::vector<MenuEntry> menu;
            int cursor = 0;
            //stateUpdate = &updateMenu;
            loadMainTitle(spriteList, fontList, textList,
                /*soundEffects,*/ playingMusic/*, eventsMonitored*/);
            break;}

        case EDITOR:
            // Tableau de blocs etc...
            break;
        case GAME:
            // entities...
            break;
        case WIN_SCREEN:
            //scores...
            break;
        case END:
            std::cout << "This should not happen.\n";
            break;
    }

    //Play Music
    playingMusic.play();

    while (gameMode != END){
         // Process events + play sounds
            /*
                close window?
                button pressed? (Menu, Movement)

                Request to load a game mode?

            */
        


           
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
    return END;
}

int main()
{
    //Game Context
    mode gameMode = MAIN_TITLE;

    // Create the main window
    RenderWindow rWindow(W_WIDTH, W_HEIGHT, "Bomberman Platformer");

    // game loop
    while (gameMode != END){gameMode = mainLoop(gameMode);}

    std::cout << "/nGoodBye!/n";

    return EXIT_SUCCESS;
}
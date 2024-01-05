#include <vector>
#include <iostream>
import loader;


#define W_WIDTH 1920
#define W_HEIGHT 1080
typedef enum _Mode{
    MAIN_TITLE,
    EDITOR,
    GAME,
    WIN_SCREEN,
    END
} Mode;

//Drawable contains the SPRITES and also the POSITION of each sprite 



Mode mainLoop(Mode mode){
    //Initialize local variables
    std::vector<Drawable> drawTable;
    std::vector<Sound> soundEffects;
    Music playingMusic;

    std::vector<Events> eventsMonitored;
    //add the QUIT event (always present)

    void (*stateUpdate)();
    
    switch (mode){
        case MAIN_TITLE:
            std::vector<MenuEntry> menu;
            stateUpdate = &updateMenu;
            loadMainTitle(drawTable, soundEffects, playingMusic, eventsMonitored);
            break;
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

    while (mode != END){
         // Process events + play sounds
            /*
                close window?
                button pressed? (Menu, Movement)

                Request to load a game mode?

            */
        
           
        // Update variables ---> SPECIFIC TO EACH MODE
            /*
                Menu : cursor position 
                Editor : FavMenu, current cursor item, state of the map...

                display_state

                On peut se débrouiller pour ne calculer les positions relatives à l'écran que lorsque l'on display 
                (à chaque frame)
            */

        // Display (tous les 1/60s)
        //BESOIN D'UN TIMER
    }
    return END;
}

int main()
{
    //Game Context
    Mode mode = MAIN_TITLE;

    // Create the main window
    createWindow(W_WIDTH, W_HEIGHT, "Bomberman Platformer");

    // game loop
    while (mode != END){mode = mainLoop(mode);}

    std::cout << "/nGoodBye!/n";

    return EXIT_SUCCESS;
}
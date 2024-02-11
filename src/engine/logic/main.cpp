import tMode;
import Menu;

import viewAPI;
import Event;

import loader;
import initializer;
// import updateVariables;

#include <iostream>
#include <vector>
#include <any>
#include <chrono>
#include <thread>
#include <pthread.h>



#define W_WIDTH 1920
#define W_HEIGHT 1080
#define FPS 60



int main()
{
    // // Create different threads
    // // structure : std::thread threadName(functionName, args)
    // std::thread getKeyboardInput(getKeyboard);
    // std::thread screenDisplay(display);
    // std::thread gameDisplay(game);


    // // Order threads by priority
    // // pthread_setschedprio() is a POSIX function that sets the scheduling priority for the thread
    // // structure : pthread_setschedprio(threadName.native_handle(), SCHED_FIFO (for first in first out), &params)
    // struct sched_param params; // built in on POSIX systems

    // params.sched_priority = 1;
    // pthread_setschedprio(getKeyboardInput.native_handle(), SCHED_FIFO, &params);
    // params.sched_priority = 2;
    // pthread_setschedprio(screenDisplay.native_handle(), SCHED_FIFO, &params);
    // params.sched_priority = 3;
    // pthread_setschedprio(gameDisplay.native_handle(), SCHED_FIFO, &params);



    // Create the main window
    RenderWindow rWindow(W_WIDTH, W_HEIGHT, "Bomberman Platformer");

    // Set the framerate limit
    rWindow.setFramerateLimit(FPS);

    // load fonts
    TextManager texts;
    texts.addFont("arial.ttf");

    // Initialize game mode
    mode gameMode = GAME;

    // Initialize fps counter
    auto startFrameTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> targetFrameDuration(1.0 / static_cast<double>(FPS));

    // App loop
    while (gameMode != END){
        //=========================== VARIABLES ===========================

        //===== General variables =====
        //std::vector<std::any*> drawOrder; //Contiendra des pointeurs sur chaque élément à dessiner, dans l'ordre    
        mode currentGameMode = gameMode;
        Event event(rWindow);
            

        //assets & texts
        Assets assets;
        assets.addTex("notFound.png");
        assets.addSoundBuffer("notFound.mp3");
        assets.selectMusic("notFound.ogg");

        texts.addText("Not Found", 0, 50);

        //game variables
        GameVariables gameVars;


        //=========================== LOAD & INIT ===========================
  
        loadAssets(gameMode, assets);
    
        assets.addSprite(0);//problèmes si on change textureList après avoir créé des sprites
        assets.addSprite(1);
        assets.addSound(0);

        // initialisation des variables du mode  
        // création de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // (certains sprites, textes, évènements, ...)

        
        initialize(gameMode, event, texts, gameVars);

        
        gameVars.board.displayBoard();
        




        //=========================== MAIN LOOP ===========================
        
        //Play Music
        assets.getMus().play();

        while ((gameMode != END) && (gameMode == currentGameMode)){
   
            // Process events + play sounds
                //close window, button pressed (Menu, Movement), Request to load a game mode...
                
            event.processEvents();
            

            //updateVars(gameMode, event, tesxts, gameVars);
            
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




            //BESOIN D'UN TIMER
            
            // for (auto it = drawOrder.begin(); it != drawOrder.end() ; it++ ){
            //     rWindow.draw(*it);
            // }

            
            // Display (toutes les 1/60s)
            // On perd l'aspect thread avec ce code
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startFrameTime);
            if (elapsedTime >= targetFrameDuration) {
                // Update the time for the next frame
                startFrameTime = currentTime;
                rWindow.clear();
                rWindow.draw(assets.getSp(1));
                rWindow.draw(texts.getText(0));
                rWindow.display();
            }

        }
    }//End of App loop

    std::cout << "\nGoodBye!\n";

    return EXIT_SUCCESS;
}
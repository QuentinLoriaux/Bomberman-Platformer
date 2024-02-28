
import Event;
import viewAPI;
import modes;
import gameVars;



#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <pthread.h>



#define W_WIDTH 1000
#define W_HEIGHT 500
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
    // Initialize fps counter
    auto startFrameTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> targetFrameDuration(1.0 / static_cast<double>(FPS));

    // load fonts
    TextManager texts;
    texts.addFont("arial.ttf");


    // Initialize game mode
    mode gameMode = GAME;

    // App loop
    while (gameMode != END){
        //=========================== VARIABLES ===========================

        //===== General variables =====
        mode currentGameMode = gameMode;
        Event event(rWindow);
            

        //assets & texts
        Assets assets;
        assets.addTex("notFound.png");
        assets.addSoundBuffer("notFound.mp3");
        assets.selectMusic("notFound.ogg");

        texts.addText("Not Found", 0, 50);

        //game variables
        GameVariables gameVars(rWindow);


        //=========================== LOAD & INIT ===========================
  
        loadAssets(gameMode, assets);
    
        assets.addSprite(0);//problèmes si on change textureList après avoir créé des sprites
        assets.addSound(0);

        // initialisation des variables du mode  
        // création de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // (certains sprites, textes, évènements, ...)

        
        initialize(gameMode, event, texts, gameVars, assets);

        // event.addEvent(testSound, std::ref(assets));
        // event.addBinding(2,SPACE);

        gameVars.board.displayBoard();
        




        //=========================== MAIN LOOP ===========================
        
        //Play Music
        assets.getMus().play();

        while ((gameMode != END) && (gameMode == currentGameMode)){
   
                
            event.processEvents();
            
            
            
            // Update variables 
                /*
                    Menu : cursor position 
                    Editor : FavMenu, current cursor item, state of the map...

                */


            
            // Display (toutes les 1/60s)
            // On perd l'aspect thread avec ce code
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startFrameTime);
            if (elapsedTime >= targetFrameDuration) {
                startFrameTime = currentTime;
                updateVars(gameMode, event, texts, gameVars);
                display(gameMode, rWindow, assets, texts, gameVars);
                
            }

        }
    }//End of App loop

    std::cout << "\nGoodBye!\n";

    return EXIT_SUCCESS;
}
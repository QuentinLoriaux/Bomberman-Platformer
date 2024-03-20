
import Event;
import viewAPI;
import modes;
import gameVars;



#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
// #include <thread>
// #include <pthread.h>



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

    #ifdef SFML_2_6_0
        std::cout << "Using SFML 2.6.0\n";
    #endif

    // Create the main window
    RenderWindow rWindow (W_WIDTH, W_HEIGHT, "Bomberman Platformer");

    // Set the framerate limit
    // rWindow.setFramerateLimit(FPS);
    rWindow->setVsync(true);
    // Initialize fps counter
    auto startFrameTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> targetFrameDuration(1.0 / static_cast<double>(FPS));


    // Initialize game mode
    GameParams params(GAME, 2, "./game_files/boards/map0.xml");

    // App loop
    while (gameMode != END){
        //=========================== VARIABLES ===========================

        GameVariables gameVars(params, rWindow);
        mode currentGameMode = params.gameMode;


        //=========================== LOAD & INIT ===========================
  
        //problèmes si on change textureList ou soundBufferList après avoir créé des sprites/soundBuffers
        loadAssets(gameVars);
    

        // initialisation des variables du mode  
        // création de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // (certains sprites, textes, évènements, ...)
        // diffère légèrement du constructeur
        
        initialize(gameVars);

        // event.addEvent(testSound, std::ref(assets));
        // event.addBinding(2,SPACE);

        gameVars.board->displayBoard();
        




        //=========================== MAIN LOOP ===========================
        
        //Play Music
        assets.getMus().play();

        while ((params.gameMode != END) && (gameMode == currentGameMode)){
   
                
            gameVars.event.processEvents();
            



            
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
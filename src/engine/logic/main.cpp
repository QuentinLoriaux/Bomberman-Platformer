
import viewAPI;
import modes;
import gameVars;



#include <iostream>
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

    // rWindow.setVsync(true);
    // Initialize fps counter
    auto startFrameTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> targetFrameDuration(1.0 / static_cast<double>(FPS));


    // Initialize parameters
    GameParams params(GAME, 1, "./game_files/boards/map0.xml");

    // App loop
    while (params.gameMode != END){
        //=========================== VARIABLES ===========================

        GameVariables gameVars(params, rWindow);
        mode currentGameMode = params.gameMode;


        //=========================== LOAD & INIT ===========================
  
        //problèmes si on change textureList ou soundBufferList après avoir créé des sprites/soundBuffers à cause des vecteurs
        loadAssets(gameVars);
    

        // initialisation des variables du mode  
        // création de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // (certains sprites, textes, évènements, ...)
        // diffère légèrement du constructeur
        
        initialize(gameVars);

        //debug
        gameVars.board->displayBoard();
        

        //=========================== MAIN LOOP ===========================
        
        //Play Music
        gameVars.assets.getMus().play();

        while ((params.gameMode != END) && (params.gameMode == currentGameMode)){
   
            gameVars.event.processEvents();
            

            // update (toutes les 1/60s)
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startFrameTime);
            if (elapsedTime >= targetFrameDuration) {
                startFrameTime = currentTime;
                updateVars(gameVars);
                display(gameVars);
            }

        }
    }//End of App loop

    std::cout << "\nGoodBye!\n";

    return EXIT_SUCCESS;
}
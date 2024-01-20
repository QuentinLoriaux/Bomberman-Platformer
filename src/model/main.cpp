#include <vector>
#include <iostream>
#include <any>
#include <chrono>
#include <thread>
#include <pthread.h>

import tMode;
import Menu;

import viewAPI;
import Event;

import loader;
import initializer;

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

    // Set the framerate limit to 60 fps
    rWindow.setFramerateLimit(FPS);

    // load fonts
    std::vector<Font> fontList;
    fontList.push_back(Font("arial.ttf"));

    // Initialize game mode
    mode gameMode = MAIN_TITLE;

    // Initialize fps counter
    auto startFrameTime = std::chrono::steady_clock::now();
    const std::chrono::duration<double> targetFrameDuration(1.0 / static_cast<double>(FPS));

    // App loop
    while (gameMode != END){
        //=========================== VARIABLES ===========================

        //===== General variables =====
        //std::vector<std::any*> drawOrder; //Contiendra des pointeurs sur chaque élément à dessiner, dans l'ordre    
        mode currentGameMode = gameMode; // pour changer facilement de mode
        Event event(rWindow);
        std::vector<EventBinding> eventsMonitored;
            

        //assets & texts
        std::vector<Texture> textureList;
        std::vector<Sprite> spriteList;
            textureList.push_back(Texture("notFound.png"));
            spriteList.push_back(Sprite(textureList[0]));

        std::vector<Text> textList;
            textList.push_back(Text("Not Found", fontList[0], 50));
        
        std::vector<SoundBuffer> soundBufferList;
        std::vector<Sound> soundList;
            soundBufferList.push_back(SoundBuffer("notFound.mp3"));
            soundList.push_back(Sound(soundBufferList[0]));

        Music musique("notFound.ogg");


        //===== Menu Variables ===== 
        std::vector<MenuEntry> menu;
        menuState menuState;
        int menuCursor;
        
        //===== Editor Variables ===== 
        // Tableau de blocs etc...

        //=========================== LOAD & INIT ===========================
  
        loadAssets(gameMode, textureList, soundBufferList, musique);

        // initialisation des variables du mode  
        // création de tout ce qui est supposé ne pas changer/être retiré le long du gameplay
        // (certains textes, évènements, ...)
  
        EventBinding evQuit(quitGame, std::ref(gameMode));
        evQuit.addTypes(CROSS, ESC);//ESC for testing
        eventsMonitored.push_back(evQuit);

        initialize(gameMode, eventsMonitored, fontList, textList,
            menu, menuCursor, menuState);

        



        // On va loader le reste des textes plus tard, selon les besoins
        // idem pour la liste evenements


        //=========================== MAIN LOOP ===========================
        
        //Play Music
        musique.play();

        while ((gameMode != END) && (gameMode == currentGameMode)){
   
            // Process events + play sounds
                //close window, button pressed (Menu, Movement), Request to load a game mode...
            while (event.poll()){
                for (auto it = eventsMonitored.begin(); it != eventsMonitored.end() ; it++){
                    if (event.isMonitored(it->types)){ it-> execute();}
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




            //BESOIN D'UN TIMER
            
            // for (auto it = drawOrder.begin(); it != drawOrder.end() ; it++ ){
            //     rWindow.draw(*it);
            // }
            rWindow.clear();
            rWindow.draw(spriteList[1]);
            rWindow.draw(textList[0]);
            
            // Display (toutes les 1/60s)
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime);
            if (elapsedTime >= targetFrameDuration) {
                // Update the time for the next frame
                startTime = currentTime;
                window.display();
            }

        }
    }//End of App loop

    std::cout << "\nGoodBye!\n";

    return EXIT_SUCCESS;
}
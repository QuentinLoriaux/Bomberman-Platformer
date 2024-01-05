module;


#include <iostream>
#include <vector>

import viewAPI;
import tTextType;
import tMode;
//import cMenuEntry;

export module loader;



export mode quitGame(){ return END; }


export void loadMainTitle(std::vector<Sprite> &spriteList,
                          std::vector<Font> &fontList,
                          std::vector<Text> &textList,
                          //std::vector<Sound> &soundEffects,
                          Music &playingMusic
                          //std::vector<Events> &eventsMonitored
                          ){

    //Chargement des assets et du texte
    spriteList.push_back(Sprite("mainTitle.jpg"));
    textList.push_back(Text("Bomberman Plateformer!", fontList[0], 50));

    playingMusic.openFromFile("Dire_Dire_Docks.ogg");   
    //son du curseur + validation menu/retour menu à mettre

    //évènements à gérer
    //addEvent(&loadMenu, ENTER, CLICK, MJOY_START);
    //MJOY: Main Joycontroller

}

// export void loadMenu(std::vector<MenuEntry> &menu,
//                      std::vector<Sprite> &spriteList,
//                      std::vector<Text> &textList){
   
//     //La gestion des events se fait en partie à l'intérieur (boutons...)
//     createMainMenu(menu);

//     spriteList.push_back(Sprite("entryBox"));// On pourrait le faire dès le loading de main title, c'est vrai et je m'en tape
//     spriteList.push_back(Sprite("cursor.png"));    
//     for (auto it = menu.begin(); it != menu.end; it++){
//         textList.push_back(Text(it.getName()));
//     }

// }

// export void loadEditor(){


// }
#include "../include/SFML/Graphics.hpp"
//#include <dlfcn.h>

#include <iostream>


int main() {
    // void *graphics;
    // bool (*choice)();

    // graphics = dlopen("/home/quentin/_dev/Git/Bomberman-Platformer/lib/libsfml-graphics.so.2.6.0", RTLD_LAZY);
    // if (!graphics) {
    //     fprintf(stderr, "Impossible de charger la bibliothèque: %s\n", dlerror());
    //     return 1;
    // }



    // choice = reinterpret_cast<bool (*)()>(dlsym(graphics, "Font::loadFromFile"));
    // if (!choice) {
    //     fprintf(stderr, "Impossible de trouver le symbole: %s\n", dlerror());
    //     dlclose(graphics);
    //     return 1;
    // }    
    std::cout << "prout" << std::endl; 
    sf::Font merde;
    if (merde.loadFromFile("../assets/font/arial.ttf")) std::cout << "MERDE" << std::endl;

    // dlclose(graphics);
    return 0;
}
module;

#include <vector>

export module assetsBindings;

export std::vector<int> monsterTexBinding(){
    std::vector<int> tab = {
        0,0,30,30,
        30,0,30,30,
        60,0,30,30,
        90,0,30,30,
        120,0,30,30
    };
    return tab;
}

export std::vector<int> bombermanTexBinding(){
    std::vector<int> tab = {
        1,7,55,85,
        68,7,55,85,
        132,7,55,85,
        193,7,55,85,
        261,7,55,85,
        325,10,55,85,
        389,10,55,85,
        451,8,55,85
    };
    return tab;
}

export std::vector<int> boardTexBinding(){
    std::vector<int> tab = {
        0,0,64,64,
        64,0,64,64,
        128,0,64,64,
        192,0,64,64,
        256,0,64,64,
        320,0,64,64,
        384,0,64,64,
        448,0,64,64,
        512,0,64,64,
        576,0,64,64,
        620,0,64,64

    };
    return tab;
}
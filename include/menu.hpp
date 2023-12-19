#ifndef GAME_HPP
#define GAME_HPP
#include <string>

class MenuEntry {
    private:
        string name;
        void* function;
    public:
        void setName(string n_name){
            name = n_name;
        }
        string getName(){
            return name;
        }
        void loadFunction() {}
        
}



#endif
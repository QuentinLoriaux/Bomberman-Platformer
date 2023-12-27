#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <iostream>

int padding;
int menuHeight;
int menuWidth;

class MenuEntry {
    private:
        string name;
        void* function;
    public:
        void MenuEntry(): name(""), function(&doNothing) {}
        void MenuEntry(string m_name): name(m_name), function(&doNothing) {}
        void loadFunction() {}
        void doNothing() {
            std::cout < "Nothing to do here" << std::endl;
        }
        void setName(string n_name){
            name = n_name;
        }
        string getName(){
            return name;
        }
}



#endif
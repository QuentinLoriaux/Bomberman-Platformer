module;

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

export module menu;




export class MenuEntry {
    private:
        std::string name;
        void (*function)();
    public:
        MenuEntry(): name("test"), function(&doNothing) {}//Debug
        MenuEntry(std::string m_name, void (*m_function)();): name(m_name), function(&m_function) {}
        

        //void setName(std::string n_name) {name = n_name;}
        std::string getName()  {return name;}
};

void createMenu(int nbEntries){
    std::vector<MenuEntry> Menu;
    for (int i = 0; i < nbEntries; i++){
        menuEntries.push_back(MenuEntry("entry" + std::to_string(i)));
    }
}

void createCursorMenu(){}
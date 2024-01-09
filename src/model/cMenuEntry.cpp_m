module;

#include <iostream>
#include <functional>
#include <any>

export module cMenuEntry;

//Faudra faire pareil que pour les EventBindings
export class MenuEntry {
    private:
        std::string name;
        std::function<std::any> func;
        //La fonction peut être : quit, sous-menu + paramètre, changerMode, ...
    public:
        MenuEntry(): name("test"), function([]()-> void {std::cout << "Just doing nothing." << std::endl;}) {}//Debug
        MenuEntry(std::string m_name, std::function<std::any> m_func): name(m_name), func(m_func) {}
        

        //void setName(std::string n_name) {name = n_name;}
        std::string getName()  {return name;}
};
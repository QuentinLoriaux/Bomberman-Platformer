module;

import tMode;
import viewAPI;

#include <vector>
#include <any>
#include <functional>
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



export module Event;

export typedef enum _evType{
    NOT_MAPPED,
    CROSS,

    //Keys
    ESC,
    ENTER,
    SPACE,
    BACKSPACE,
    TAB,
    Z, Q, S, D,
    ARROW_U, ARROW_D, ARROW_L, ARROW_R,
    
    //Joycontroller
    JOY_A, JOY_B, JOY_START

} evType;



class EventBinding{//Toujours initialiser avec le constructeur(fonction) puis ajouter les keys avec addTypes()
    private :
        template<typename... Args>
        using type_func = std::function<void(Args...)>;
        
        type_func<> func;
        
        
    public :
        std::vector<evType> types;

        //****************************************************************************************************************
        //ATTENTION il faut absolument noter les éléments passés en référence de la sorte : std::ref<arg> sinon ça marche pas
        //****************************************************************************************************************
        template<typename Func, typename... Args>
        EventBinding(Func _fun, Args&&... args) : func(std::bind(_fun, std::forward<Args>(args)...)) {}




        template<typename... Args>
        void addTypes(evType type, Args... args) {
            types.push_back(type);
            addTypes(args...);
        }
        void addTypes(evType type) {types.push_back(type);}

        void removeTypes(){types.clear();}

        std::vector<evType>& getTypes(){return types;}

        
        void execute(){func();}
};



export class Event{
    private :
        sf::Event ev;
        RenderWindow* window;
        std::vector<EventBinding> eventList;
        std::vector<int> monitoredList;
    public :
        //On passe la fenêtre en référence
        Event(RenderWindow &_rWindow) : ev(sf::Event()), window(&_rWindow) {}

        bool poll(){return window->rWindow.pollEvent(ev);}

        evType getType(){//Merci ChatGPT
            switch (ev.type) {

                case sf::Event::Closed:
                    return CROSS;

                case sf::Event::KeyPressed:
                    switch (ev.key.code) {
                        case sf::Keyboard::Escape:
                            return ESC;
                        case sf::Keyboard::Enter:
                            return ENTER;
                        case sf::Keyboard::Space:
                            return SPACE;
                        case sf::Keyboard::Backspace:
                            return BACKSPACE;
                        case sf::Keyboard::Tab:
                            return TAB;
                        case sf::Keyboard::Z:
                            return Z;
                        case sf::Keyboard::Q:
                            return Q;
                        case sf::Keyboard::S:
                            return S;
                        case sf::Keyboard::D:
                            return D;
                        case sf::Keyboard::Up:
                            return ARROW_U;
                        case sf::Keyboard::Down:
                            return ARROW_D;
                        case sf::Keyboard::Left:
                            return ARROW_L;
                        case sf::Keyboard::Right:
                            return ARROW_R;
                        default:
                            return NOT_MAPPED;
                    }
                    break;

                case sf::Event::JoystickButtonPressed:
                    switch (ev.joystickButton.button) {
                        case 0: // Replace with your joy A button index
                            return JOY_A;
                        case 1: // Replace with your joy B button index
                            return JOY_B;
                        case 7: // Replace with your joy Start button index
                            return JOY_START;
                        default:
                            return NOT_MAPPED;
                    }
                    break;
                
                default : return NOT_MAPPED;
            }
        }

        void processEvents(){
            while (this->poll()){
                for (auto num = monitoredList.begin(); num != monitoredList.end(); num++){//on parcourt monitoredList
                    for (auto it = eventList[*num].getTypes().begin(); it != eventList[*num].getTypes().end(); it++){//On parcourt les bindings de l'eventBinding
                        if (this->getType()==*it){
                            eventList[*num].execute();
                            break;//De cette manière, des evenements simultanés pour un seul input sont possibles
                        }
                    }
                }
            }
        }


        // --------- EventBindings ---------

        template<typename Func, typename... Args>
        void addEvent(Func _fun, Args&&... args){eventList.push_back(EventBinding(_fun, std::forward<Args>(args)...));}



        template<typename... Args>
        void addBinding(int evNum, evType type, Args... args) {
            eventList[evNum].addTypes(type);
            addBinding(evNum, args...);
        }
        void addBinding(int evNum, evType type) {
            auto it = std::find(monitoredList.begin(), monitoredList.end(), evNum);
            if (it == monitoredList.end()){monitoredList.push_back(evNum);}//add event to monitoredList if not already monitored

            eventList[evNum].addTypes(type);
        }



        void clearBinding(int evNum){
            auto it = std::find(monitoredList.begin(), monitoredList.end(), evNum);
            if (it != monitoredList.end()){monitoredList.erase(it);}//remove from monitoredList

            eventList[evNum].removeTypes();
        }
        

};

//Serait-ce possible de découpler l'event de window? Question nulle, les évènements sont forcément rattachés à une fenêtre
//ex : clic souris
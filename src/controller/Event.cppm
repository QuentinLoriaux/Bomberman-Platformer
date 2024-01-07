module;

#include <SFML/Window/Event.hpp>
#include <any>
#include <functional>
#include <vector>

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



export class Event{
    private :
        sf::Event ev;
        sf::RenderWindow rWindow;
    public :
        //On passe la fenêtre en référence
        Event(RenderWindow &_rWindow) : ev(sf::Event), rWindow(_rWindow) {}

        bool poll(){return rWindow.pollEvent(ev);}

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

        bool isMonitored(std::vector<evType> &vec){
            for (auto it = vec.begin(); it != vec.end(); it++){
                if (this->getType()==*it){return true;}
            }
            return false;
        }

};

export class EventBinding{//Toujours initialiser avec le constructeur(fonction) puis ajouter les keys avec addTypes()
    private :
        template<typename... Args>
        using type_func = std::function<void(Args...)>;
        
        type_func<> func;
        std::vector<evType> types;
        
    public :
        //****************************************************************************************************************
        //ATTENTION il faut absolument noter les éléments passés en référence de la sorte : std::ref<arg> sinon ça marche pas
        //****************************************************************************************************************
        template<typename Func, typename... Args>
        EventBinding(Func _fun, Args&&... args) : func(std::bind(_fun, std::forward<Args>(args)...)) {}




        void addTypes(evType... _types){types.insert(types.end(), {_types...});}
        std::vector<evType> getTypes(){return types;}
        
        void execute(){func();}
}



//Serait-ce possible de découpler l'event de window? Question nulle, les évènements sont forcément rattachés à une fenêtre
//ex : clic souris
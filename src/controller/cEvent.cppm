module;

#include <SFML/Window/Event.hpp>

export module cEvent;

export class Event{
    private :
        sf::Event ev;
        sf::RenderWindow* rWindow;
    public :
        Event() : ev(sf::Event){}

};

//Serait-ce possible de découpler l'event de window?
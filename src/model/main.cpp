#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


import display;

#define W_WIDTH 1200
#define W_HEIGHT 600


int main()
{
    // Create the main window
    RenderWindow window(W_WIDTH, W_HEIGHT, "Bomberman Platformer");


    // Load a sprite to display
    Texture tex("assets/img/cute_image.png");
    Sprite sprite(tex);

    // Create a graphical text to display
    // Font font("assets/font/arial.ttf");
    // Text text("Hello SFML", font, 50);


    // Load a music to play
    Music music("assets/music/Dire_Dire_Docks.ogg");

    // Play the music
    music.play();



    // Start the game loop
    while (window.isOpen())
    {
        //refreshWindowSize();
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        // window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
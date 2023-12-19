#include "../include/global.hpp"
#include "window.cpp"


int main()
{
    // Create the main window
    refreshWindowSize();
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("assets/img/cute_image.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("assets/font/arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);


    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("assets/music/Dire_Dire_Docks.ogg"))
        return EXIT_FAILURE;


    // Play the music
    music.play();



    // Start the game loop
    while (window.isOpen())
    {
        refreshWindowSize();
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
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
#include <SFML/Audio.hpp>
#include <iomanip>  // setprecision, setw
#include "CelestialBody.h"
#include "Universe.h"

int main (int argc, const char* argv[]) 
{
    //Take in arguments T and deltaT
    double T = atof(argv[1]), deltaT = atof(argv[2]);

    //Load up the background
    sf::Image image;
    if (!image.loadFromFile("background.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    
    //Set up the window
    sf::Vector2u size = image.getSize();
    double windowSize;
    if (size.x < size.y)
    {
        windowSize = size.x;        
    } else {
        windowSize = size.y;
    }

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "The Solar System");

    //Getting the number of particles
    int N;
    std::cin >> N;

    //Getting the radius of the universe
    double R;
    std::cin >> R; 
    
    //Instance for vector
    Universe vector_ptr;
    vector_ptr.setR(R);
    vector_ptr.setWindowSize(windowSize);

    //Obtaining information for each celestial body
    std::unique_ptr<CelestialBody> ptr; 
    for (int i = 0; i < N; i++)
    {
        ptr = std::make_unique<CelestialBody>();
        std::cin >> *ptr;
        ptr->applyTexture();
        ptr->applySprite();
        vector_ptr.bodiesPtr.push_back(std::move(ptr));
    }

    //Load sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("V-Lights.wav")) {
        std::cout << "ERROR: FAILED TO LOAD THE ADUDIO FILE" << std::endl;
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(12.5);
    sound.play();

    //Timer
    double seconds = 0;
    sf::Time elapsed;
    sf::Clock clock;
    
    //Start SFML display loop
    while (window.isOpen())
    {
        //Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear();
        
        window.setFramerateLimit(41);
        elapsed = clock.getElapsedTime();
        
        if (seconds < T)
        {
            clock.getElapsedTime();
            window.draw(sprite);
            vector_ptr.step(deltaT);
            window.draw(vector_ptr);
        }  

        window.display();   
    }
    
    //Out put the final state of the universe
    std::cout << std::endl;
    std::cout << "/*******************************************************************************" << std::endl;
    std::cout << "Elapsed time           : " << elapsed.asSeconds() << " seconds" << std::endl; 
    std::cout << "Number of particles    : " << N << std::endl;
    std::cout << std::scientific << std::setprecision(2);
    std::cout << "Radius of the Universe : " << R << std::endl << std::endl;
 
    std::cout << " x-coord       y-coord      x-velocity   y-velocity   mass           image-file" << std::endl << std::endl;
    std::cout << std::scientific << std::setprecision(4);
    for (auto i = vector_ptr.bodiesPtr.begin(); i < vector_ptr.bodiesPtr.end(); i++)
    {
        std::cout << **i << std::endl;
    }
    std::cout << "*******************************************************************************/" << std::endl << std::endl;

    return 0;
}
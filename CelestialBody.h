#ifndef CelestialBody_h
#define CelestialBody_h

#include <iostream>
#include <vector> 
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class CelestialBody : public sf::Drawable {
public:
    CelestialBody();

    //Accessor functions
    double getXPos(void) const;
    double getYPos(void) const;
    double getMass(void) const;

    //Mutator functions
    void applyTexture(void);
    void applySprite(void);
    void set_body_pos(double, double);

    void modify_xVel(void);
    void modify_yVel(void);
    void calculate_vel(std::vector<std::unique_ptr<CelestialBody> >&, double);

    friend std::istream &operator >>(std::istream&, CelestialBody&);
    friend std::ostream &operator <<(std::ostream&, CelestialBody&);

    void drawObj(sf::RenderTarget& target, sf::RenderStates states);


private:
    double xPos, yPos, xVel, yVel, mass, pixelXPos,pixelYPos;
    std::string particleFile;
    sf::Texture particleTexture;
    sf::Sprite particleSprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
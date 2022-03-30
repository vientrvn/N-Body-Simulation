#ifndef Universe_h
#define Universe_h

#include "CelestialBody.h"

class Universe : public sf::Drawable {
public:
    std::vector< std::unique_ptr<CelestialBody> > bodiesPtr;
    void step(double);

    //Mutator functions
    void setR(double);
    void setWindowSize(double);

    friend std::ostream &operator <<(std::ostream& outStream, Universe&);
private:
    double R, windowSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
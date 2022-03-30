#include "Universe.h"

void Universe::step(double deltaT) {
    for (auto &i:bodiesPtr)
    {
        i->calculate_vel(bodiesPtr, deltaT);
        i->set_body_pos(R, windowSize);
    }
}

void Universe::setR(double aR) {
    R = aR;
}

void Universe::setWindowSize(double aWindowSize) {
    windowSize = aWindowSize;
}

std::ostream& operator <<(std::ostream& outStream, Universe& src) {
    for (auto &each:src.bodiesPtr)
    {
        outStream << *each << std::endl;
    }
    
    return outStream;
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    for (auto &&i:bodiesPtr)
    {
        i->drawObj(target, states);
    }
    
}
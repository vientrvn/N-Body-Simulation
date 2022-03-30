#include <cmath>
#include "CelestialBody.h"
#include <iomanip> //setprecision, setw

CelestialBody::CelestialBody() {}

double CelestialBody::getXPos(void) const {
    return xPos;
}

double CelestialBody::getYPos(void) const {
    return yPos;
}

double CelestialBody::getMass(void) const {
    return mass;
}

void CelestialBody::applyTexture(void) {
    particleTexture.loadFromFile(particleFile);
}

void CelestialBody::applySprite(void) {
    particleSprite.setTexture(particleTexture);
}

void CelestialBody::set_body_pos(double R, double windowSize) {
    pixelXPos = ((R + xPos) * (windowSize / (2*R))) ;
    pixelYPos = ((R - yPos) * (windowSize / (2*R)));
    particleSprite.setPosition(pixelXPos, pixelYPos);
}

void CelestialBody::calculate_vel(std::vector<std::unique_ptr<CelestialBody>> &src, double deltaT)
{
    double r, deltaX, deltaY, force, Fx = 0, Fy = 0, G = 6.67e-11, aX, aY;

    for (auto& i:src)
    {
        if (i.get() == this)
        {
            continue;
        }

        //Calculate pairwise force
        deltaX = i->getXPos() - xPos;
        deltaY = i->getYPos() - yPos;
        r = sqrt(pow(deltaX, 2) + pow(deltaY, 2)); 
        force = (G * i->getMass() * mass) / pow(r, 2);
        
        //Net force
        Fx += force * (deltaX / r);
        Fy += force * (deltaY / r);
    }

    aX = Fx / mass;
    aY = Fy / mass;

    xVel = xVel + deltaT * aX;
    yVel = yVel + deltaT * aY;

    xPos = xPos + deltaT * xVel;
    yPos = yPos + deltaT * yVel;
}

std::ostream &operator <<(std::ostream& outStream, CelestialBody& src) 
{
    outStream << " " << std::setw(11) << src.xPos << "  " << std::setw(11) << src.yPos << "  " << std::setw(11) << src.xVel << "  " << std::setw(11) << src.yVel << "  " << std::setw(11) << src.mass << "  " << std::setw(13) << src.particleFile;
    
    return outStream;
}

std::istream &operator >>(std::istream& inStream, CelestialBody &dst) 
{
    inStream >> dst.xPos >> dst.yPos >> dst.xVel >> dst.yVel >> dst.mass >> dst.particleFile;
    
    return inStream;
}

void CelestialBody::drawObj(sf::RenderTarget& target, sf::RenderStates states)
{
    draw(target, states);
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(particleSprite, states);
}
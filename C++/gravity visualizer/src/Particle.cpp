#include "../include/Particle.h"

// Constructor
Particle::Particle(int positionX, int positionY, double mass, double elasticity, double velocityX, double velocityY) 
        : _mass(mass), _elasticity(elasticity), _positionX(positionX), _positionY(positionY), _velocityX(velocityX), _velocityY(velocityY){}


// getter functions to get object parameters
auto Particle::mass() const -> double { return _mass;}

auto Particle::elasticity() const -> double { return _elasticity;}

auto Particle::positionX() const -> int { return _positionX;}

auto Particle::positionY() const -> int { return _positionY;}

auto Particle::velocityX() const -> double { return _velocityX;}

auto Particle::velocityY() const -> double { return _velocityY;}

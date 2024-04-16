#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
private:
  double mass, elasticity, velocityX, velocityY;
  int positionX, positionY;

public:
  Particle(double mass, double elasticity, int positionX, int positionY, double velocityX, double velocityY);

};

#endif // PARTICLE_H
#ifndef WORLD_H
#define WORLD_H

#include "Display.h"

class Particle; // Forward declaration

class World {
public:
  // World constructor
  World(const double gravityY, double landElasticity, const int width, const int height);

  // Add a particle to the world
  void addObject(Particle* particle);

  // Update the state of the world (simulation loop)
  void update();

  // Function to draw particles on the display
  void drawParticles() {
    // ... (code from previous version to draw particles on the display)
  }

private:
  // Gravity vector (constant acceleration due to gravity)
  double gravityY;

  // Elasticity coefficient of the land (affects collision behavior)
  double landElasticity;

  // List of particles in the world
  std::vector<Particle*> particles;

  // Display object for visual representation
  Display display;

  // Function for handling particle collision with the land
  void handleCollisionWithLand(Particle* particle);
};

#endif // WORLD_H
#include "../include/World.h"

World::World(const double gravityY, double landElasticity, const int width, const int height)
  : gravityY(gravityY), landElasticity(landElasticity), width(width), height(height) {}

void World::addObject(Particle* particle) {
  particles.push_back(particle);
}

void World::update() {
  for (Particle* particle : particles) {
    particle->update();
    particle->applyForce(0.0, gravityY); // Apply constant gravity
    // Add collision handling logic here (e.g., check for land collision and update particle)
  }
}

void World::drawParticles() {
  // Implement logic to draw particles on the display using display methods
  // You can access particle positions and other properties from the particles_ vector
  // ... (code to draw particles on the display)
}

void World::handleCollisionWithLand(Particle* particle) {
  // Check if particle is below the land (y-position + particle radius < 0)
  if (particle->y + particle->radius < 0) {
    // Calculate normal force based on particle velocity and land elasticity
    double normalForce = -particle->vy * landElasticity;

    // Update particle's vertical velocity based on the normal force
    particle->vy = std::min(normalForce, 0.0); // Prevent upward force
    particle->y = -particle->radius; // Set position to land surface
  }
}
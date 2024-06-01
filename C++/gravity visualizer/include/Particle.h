#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

/**
 * @class Particle
 * @brief A class to represent a particle with basic physical properties such as mass, elasticity, position, and velocity.
 */
class Particle {
public:
  /**
   * @brief Constructor for the Particle class.
   * @param positionX Initial x position of the particle. Defaults to DEFAULT_X_POSITION.
   * @param positionY Initial y position of the particle. Defaults to DEFAULT_Y_POSITION.
   * @param mass Mass of the particle. Defaults to DEFAULT_MASS.
   * @param elasticity Elasticity of the particle. Defaults to DEFAULT_ELASTICITY.
   * @param velocityX Initial x velocity of the particle. Defaults to DEFAULT_X_VELOCITY.
   * @param velocityY Initial y velocity of the particle. Defaults to DEFAULT_Y_VELOCITY.
   */
  Particle(int positionX = DEFAULT_X_POSITION, int positionY = DEFAULT_Y_POSITION, 
            double mass = DEFAULT_MASS, double elasticity = DEFAULT_ELASTICITY, 
            double velocityX = DEFAULT_X_VELOCITY, double velocityY = DEFAULT_Y_VELOCITY);
  
  /**
   * @brief Get the mass of the particle.
   * @return The mass of the particle.
   */
  auto mass() const -> double;
  
  /**
   * @brief Get the elasticity of the particle.
   * @return The elasticity of the particle.
   */
  auto elasticity() const -> double;
  
  /**
   * @brief Get the x position of the particle.
   * @return The x position of the particle.
   */
  auto positionX() const -> int;
  
  /**
   * @brief Get the y position of the particle.
   * @return The y position of the particle.
   */
  auto positionY() const -> int;
  
  /**
   * @brief Get the x velocity of the particle.
   * @return The x velocity of the particle.
   */
  auto velocityX() const -> double;
  
  /**
   * @brief Get the y velocity of the particle.
   * @return Y velocity of the particle.
   */
  auto velocityY() const -> double;


private:
  //  Default values for particle members properties
  static constexpr int DEFAULT_X_POSITION = 38;         //  Default x position
  static constexpr int DEFAULT_Y_POSITION = 50;         //  Default y position 
  static constexpr double DEFAULT_X_VELOCITY = 0;       //  Default x velocity
  static constexpr double DEFAULT_Y_VELOCITY = 0;       //  Default y velocity
  static constexpr double DEFAULT_MASS = 1.0;           //  Defailt mass
  static constexpr double DEFAULT_ELASTICITY = 1.0;     //  Default Elasticity for collisions

  //  Private Member Variable
  double _mass;           //  Mass of the particle
  double _elasticity;     //  Elasiticity of the particle
  double _velocityX;      //  Velocity of the particle in x direction
  double _velocityY;      //  Velocity of the particle in y direction
  int _positionX;         //  Initial X position of the particle
  int _positionY;         //  Initial Y position of the particle

};

#endif // PARTICLE_H
#ifndef WORLD_H
#define WORLD_H

#define GRAVITY_DEFAULT 9.8
#define ELASTISITY_DEFAULT 1.0

#include "Particle.h"
#include <vector>
#include <memory>
#include <iostream>
#include <cstdarg>

class World {
private:
    std::vector<std::reference_wrapper<Particle>> particles;
    std::vector<double> _elasticity;
    double _gravity;

    auto getParticleData() const -> void;

public:
    // Default constructor with default gravity value
    

    template<typename... Args>
    World(Args&&... args) {
        this->_gravity = GRAVITY_DEFAULT;
        this->_elasticity.resize((size_t)4);
        this->_elasticity[0] = ELASTISITY_DEFAULT;
        this->_elasticity[1] = ELASTISITY_DEFAULT;
        this->_elasticity[2] = ELASTISITY_DEFAULT;
        this->_elasticity[3] = ELASTISITY_DEFAULT;
        addParticles(std::forward<Args>(args)...);
    }

    // Overloaded constructor with custom gravity value
    template<typename... Args>
    World(int gravity_value, Args&&... args) : _gravity(gravity_value) {
        if (gravity_value < 0) {
            std::cerr << "Error: Gravity value cannot be negative!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->_elasticity.resize((size_t)4);
        this->_elasticity[0] = ELASTISITY_DEFAULT;
        this->_elasticity[1] = ELASTISITY_DEFAULT;
        this->_elasticity[2] = ELASTISITY_DEFAULT;
        this->_elasticity[3] = ELASTISITY_DEFAULT;
        addParticles(std::forward<Args>(args)...);
    }
    

    auto debugData() const -> void;
    auto gravity() const -> double;
    auto setGravity(const double gravity) -> void;
    auto setElasticity(const double elastic_value_all) -> void;
    auto setElasticity(const double elastic_value_top_bottom, const double elastic_value_left_right) -> void;
    auto setElasticity(const double elastic_value_top, const double elastic_value_right, const double elastic_value_bottom, const double elastic_value_left) -> void;
    auto elasticityTop() const -> double;
    auto elasticityRight() const -> double;
    auto elasticityBottom() const -> double;
    auto elasticityLeft() const -> double;

private:
    template<typename T, typename... Args>
    void addParticles(T&& particle, Args&&... args) {
        particles.emplace_back(std::ref(particle));
        addParticles(std::forward<Args>(args)...);
    }

    void addParticles() {} // Base case for recursion
};


#endif  // WORLD_H 
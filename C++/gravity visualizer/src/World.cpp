#include "../include/World.h"

auto World::getParticleData() const -> void {
    int i = 1;
    for(auto &it: particles) {
        std::cout << "Particle " << i << std::endl;
        std::cout << "Particle Mass = " << it.get().mass() << std::endl;
        std::cout << "Particle Initial PositionX = " << it.get().positionX() << std::endl;
        std::cout << "Particle Initial PositionY = " << it.get().positionY() << std::endl;
        std::cout << "Particle Initial VelocityX = " << it.get().velocityX() << std::endl;
        std::cout << "Particle Initial VelocityY = " << it.get().velocityY() << std::endl;
        std::cout << "Particle Elasticity = " << it.get().elasticity() << std::endl;
       
        std::cout << std::endl;
        i++;
    }
}

auto World::debugData() const -> void {
    std::cout << "Gravity: " << this->_gravity << std::endl;
    std::cout << "Elasticity : ";
    for(auto &it: this->_elasticity) {
        std::cout << it << " ";
    }
    std::cout << std::endl << std::endl;
    this->getParticleData();
}

auto World::gravity() const -> double { return this->_gravity; }

auto World::setGravity(const double gravity) -> void { 
    if (gravity < 0) {
        std::cerr << "Error: Gravity value cannot be negative!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->_gravity = gravity; 
}

auto World::setElasticity(const double elastic_value_all) -> void {
    if (elastic_value_all < 0 || elastic_value_all > 1) {
        std::cerr << "Error: Elasticity value must be in the range [0, 1]." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 4; ++i) {
        this->_elasticity[0] = elastic_value_all;
        this->_elasticity[1] = elastic_value_all;
        this->_elasticity[2] = elastic_value_all;
        this->_elasticity[3] = elastic_value_all;
    }
}

auto World::setElasticity(const double elastic_value_top_bottom, const double elastic_value_left_right) -> void {
    if (elastic_value_top_bottom < 0 || elastic_value_top_bottom > 1 || elastic_value_left_right < 0 || elastic_value_left_right > 1) {
        std::cerr << "Error: Elasticity value must be in the range [0, 1]." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->_elasticity[0] = elastic_value_top_bottom;
    this->_elasticity[1] = elastic_value_left_right;
    this->_elasticity[2] = elastic_value_top_bottom;
    this->_elasticity[3] = elastic_value_left_right;
}

auto World::setElasticity(const double elastic_value_top, const double elastic_value_right, const double elastic_value_bottom, const double elastic_value_left) -> void {
    if (elastic_value_top < 0 || elastic_value_top > 1 || elastic_value_left < 0 || elastic_value_left > 1 || elastic_value_bottom < 0 || elastic_value_bottom > 1 || elastic_value_right < 0 || elastic_value_right > 1) {
        std::cerr << "Error: Elasticity value must be in the range [0, 1]." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->_elasticity[0] = elastic_value_top;
    this->_elasticity[1] = elastic_value_right;
    this->_elasticity[2] = elastic_value_bottom;
    this->_elasticity[3] = elastic_value_left;
}

auto World::elasticityTop() const -> double { return this->_elasticity[0]; }

auto World::elasticityRight() const -> double { return this->_elasticity[1]; }

auto World::elasticityBottom() const -> double { return this->_elasticity[2]; }

auto World::elasticityLeft() const -> double { return this->_elasticity[3]; }


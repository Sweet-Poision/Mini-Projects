#include <thread>
#include <chrono>
#include <vector>
#include "include/Display.h"
// #include "include/Particle.h"

class Particle {
private:
    static constexpr int DEFAULT_X_POSITION = 38;
    static constexpr int DEFAULT_Y_POSITION = 50;
    static constexpr double DEFAULT_X_VELOCITY = 0;
    static constexpr double DEFAULT_Y_VELOCITY = 0;
    static constexpr double DEFAULT_MASS = 1.0;
    static constexpr double DEFAULT_ELASTICITY = 1.0;

    double _mass, _elasticity, _velocityX, _velocityY;
    int _positionX, _positionY;

public:
    Particle(int positionX = DEFAULT_X_POSITION, int positionY = DEFAULT_Y_POSITION, double mass = DEFAULT_MASS, double elasticity = DEFAULT_ELASTICITY, double velocityX = DEFAULT_X_VELOCITY, double velocityY = DEFAULT_Y_VELOCITY) : _mass(mass), _elasticity(elasticity), _positionX(positionX), _positionY(positionY), _velocityX(velocityX), _velocityY(velocityY){}

    // Particle() : _positionX(DEFAULT_X_POSITION), _positionY(DEFAULT_Y_POSITION), _mass(DEFAULT_MASS), _elasticity(DEFAULT_ELASTICITY),  _velocityX(DEFAULT_X_VELOCITY), _velocityY(DEFAULT_Y_VELOCITY){}

    auto mass() const -> double { return _mass;}
    auto elasticity() const -> double { return _elasticity;}
    auto positionX() const -> int { return _positionX;}
    auto positionY() const -> int { return _positionY;}
    auto velocityX() const -> double { return _velocityX;}
    auto velocityY() const -> double { return _velocityY;}
};

class World {
private:
    std::vector<std::unique_ptr<Particle>> particles;
    std::unique_ptr<Display> display;
    double gravity;

public:
    World(Particle &particle_param, ...) : gravity(9.8) {
        display = std::make_unique<Display>();
        particles.push_back(std::make_unique<Particle>(&particle_param));
        va_list args;
        va_start(args, particle_param);
        while (va_arg(args, Particle *) != nullptr) {
            Particle *particle = va_arg(args, Particle *);
            particles.push_back(std::make_unique<Particle>(&particle));
        }
        va_end(args);
    }
    World(double gravity, ...) : gravity(gravity) {
        va_list args;
        va_start(args, gravity);

        while (va_arg(args, Particle *) != nullptr) {
            Particle *particle = va_arg(args, Particle *);
            particles.push_back(std::make_unique<Particle>(particle));
        }
        va_end(args);
    };

    auto myThreadFunction(const Particle &particle) -> void {
        display->turnOn(particle.positionX(), particle.positionY());
        std::this_thread::sleep_for(std::chrono::seconds(5));

    }

    auto buildWorld() const -> void {
        const int numParticles = static_cast<int>(particles.size());
        std::thread threads[numParticles], renderThread;
        display->startRendering(renderThread);
        int threadCount = 0;
        for (auto &particle : particles) {
            threads[threadCount] = std::thread(World::myThreadFunction, this, std::cref(particle));
            ++threadCount;
        }
        for (auto &thread : threads) {
            thread.join();
        }
        display->stopRendering();
        renderThread.join();

    }
};

int main() {
    
    Particle myParticle1, myParticle2(12);
    World myWorld(myParticle1, myParticle2);
    myWorld.buildWorld();

    // for (int i = 0; i < 5; ++i) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     myDisplay.turnOn(4, 4);
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     myDisplay.turnOff(4, 4);
    // }

    
}
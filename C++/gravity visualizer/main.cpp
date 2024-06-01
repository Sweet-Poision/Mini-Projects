#include "include/Display.h"
#include "include/Particle.h"
#include "include/World.h"

#include <cmath>
#include <iomanip>

auto simulate() -> void {
    std::thread render;
    Display myDisplay;

    myDisplay.startRendering(render);
    
    bool special_case = false;
    constexpr double g = 9.8;
    constexpr double a = 0;
    double u =0, v = 0, y = 10, _y = 10, x = 10.0, u_x = 0, v_x = 0.0, _x = 10.0;
    constexpr int t_ms = 33;
    constexpr double t = t_ms * 0.001;

    while(true) {
        // std::cout << std::fixed << std::setprecision(18);
        // std::cout << std::endl << std::endl;
        // std:: cout << "Y posiion : " << y << " Current Velocity : " << u << std::endl;
        if(y >= 39.0 && x < 99.0 && x > 1.0) {
            // std::cout << "Case >= 39.0" << std::endl;
            myDisplay.turnOn(38, x);
            std::this_thread::sleep_for(std::chrono::milliseconds(t_ms));
            myDisplay.turnOff(38, x);
            u *= -1;
            y = _y;
        }
        else if ( y < 1.0 && x < 99.0 && x > 1.0) {
            // std::cout << "Case <= 0.0" << std::endl;
            myDisplay.turnOn(1, x);
            std::this_thread::sleep_for(std::chrono::milliseconds(t_ms));
            myDisplay.turnOff(1, x);
            u *= -1;
            y = _y;
        }
        if(special_case) {

        }
        // std::cout << "turning on pixel" << std::endl;
        myDisplay.turnOn(y, x);

        //
        if(y < 39.0 && y >= 38.0) {
            // std::cout << "Case: Just touching the bottom boundary" << std::endl;
            const double remaining_distance = 39.0 - y;
            v = u*u + 2*g*remaining_distance;
            v = sqrtl(v);
            double temp_t = (v - u) * 1000;
            temp_t /= g;
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(2 * temp_t)));
            u *= -1;
        }

        //
        else if(y < 2.0 && y >= 1.0) {
            // std::cout << "Case: Just touching the top boundary" << std::endl;
            const double remaining_distance = 0.0 - y;
            v = u*u + 2*g*remaining_distance;
            v = sqrtl(v);
            v = 0 - v;
            double temp_t = (v -u) * 1000;
            temp_t /= g;
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(2 * temp_t)));
            u *= -1;

        }
        _y = y;
        _x = x;
        // std::cout << "Calculating data for this position and waiting for required time." << std::endl;
        y += u * t + 0.5 * g * t * t;
        v = u + g * t;
        u = v;

        x += u_x * t + 0.5 * a * t * t;
        v_x = u_x + a * t;
        u_x = v_x;

        std::this_thread::sleep_for(std::chrono::milliseconds(t_ms));
        // std::cout << "turning off pixel" << std::endl;
        myDisplay.turnOff(_y, _x);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    myDisplay.stopRendering();

    render.join();
}


int main() {
    Particle myParticle1, myParticle2(12), myParticle3(10);
    World myWorld(myParticle1, myParticle2, myParticle3);
    // Display myDisplay;
    simulate();
}

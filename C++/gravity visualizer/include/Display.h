#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <memory>
#include <atomic>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdlib>
#endif

/**
 * @class Display
 * @brief Manages the visual representation of the simulation within a terminal window.
 *
 * This class creates a grid of pixels (using a flattened array of bytes), handles turning pixels on/off,
 * and renders the scene continuously in a separate thread for smooth animation.
 *
 * Class Invariants:
 * - The `displayArray` always has a size equal to `flattenedSize` and reflects the current state
 *   of the on/off pixels in the display grid.
 */
class Display {
private:
    static constexpr int WIDTH = 100;
    static constexpr int HEIGHT = 40;
    static constexpr int BITS_IN_BYTE = 8;
    static constexpr char PIXEL_ON = '*';
    static constexpr char PIXEL_OFF = ' ';

    const int flattenedSize;
    std::unique_ptr<unsigned char[]> displayArray;
    std::atomic<bool> running;

    auto getFlattenedIndex(const int row, const int column) const -> std::pair<int, int>;

    auto resetConsoleCursorPosition() -> void;

    auto renderScene() -> void;

    auto validIndex(const int row, const int column) const -> bool;

    auto setConsoleWindowSize(const int width, const int height) const -> void;

    auto setTerminalSize(const int width, const int height) const -> void;

    auto createRenderWindow(const int width, const int height) const -> void;

    auto showCursor() const -> void;

    auto hideCursor() const -> void;

    auto clearConsoleDisplay() const -> void;

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the display dimensions and sets up the display array.
     */
    explicit Display();

    /**
     * @brief Destructor.
     *
     * Cleans up resources and shows the cursor.
     */
    ~Display();

    /**
     * @brief Starts a separate thread to continuously render the scene.
     *
     * @param render_thread Reference to a std::thread object where the rendering thread will be stored.
     */
    auto startRendering(std::thread &render_thread) -> void;

    /**
     * @brief Stops the rendering thread.
     */
    auto stopRendering() -> void;

    /**
     * @brief Turns off a pixel at the given coordinates.
     *
     * @param row The row index of the pixel (0-based).
     * @param column The column index of the pixel (0-based).
     *
     * @throws std::out_of_range if the coordinates are outside the valid display area.
     */
    auto turnOff(const int row, const int column) -> void;

    /**
     * @brief Turns on a pixel at the given coordinates.
     *
     * @param row The row index of the pixel (0-based).
     * @param column The column index of the pixel (0-based).
     *
     * @throws std::out_of_range if the coordinates are outside the valid display area.
     */
    auto turnOn(const int row, const int column) -> void;
};

#endif // DISPLAY_H
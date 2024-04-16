#include "../include/Display.h"

Display::Display() : running(true), flattenedSize(HEIGHT * WIDTH / BITS_IN_BYTE) {
    displayArray = std::make_unique<unsigned char[]>(flattenedSize);

    #ifdef _WIN32
    // set the console window size and clear the screen (Windows Specific)
    setConsoleWinowSize(WIDTH+1, HEIGHT+1);
    
    #else
    // Set the terminal size and clear the screen (Unix/ Linux specific)
    setTerminalSize(WIDTH+1, HEIGHT+1);

    #endif

    clearConsoleDisplay();

    hideCursor();
    
    // Initialize the display array with borders as the on pixel    
    for(int row = 0; row < HEIGHT; ++row) {
        for(int column = 0; column < WIDTH; ++column) {
            if( row == 0 or row == HEIGHT - 1 or column == 0 or column == WIDTH - 1) {
                this->turnOn(row, column);
            }
            else {
                this->turnOff(row, column);
            }
        }
    }
}

Display::~Display() {
    // Show the cursor before exiting
    showCursor();
}

auto Display::startRendering(std::thread &render_thread) -> void {
    render_thread = std::thread(&Display::renderScene, this);
}

auto Display::stopRendering() -> void {

    running = false;
    clearConsoleDisplay();
}

auto Display::turnOff(const int row, const int column) -> void {
    if(!validIndex(row, column)) {
        throw std::out_of_range("Index out of range");
    }
    auto [byteIndex, bitOffset] = getFlattenedIndex(row, column);
    displayArray[byteIndex] = displayArray[byteIndex] & (~(1 << (BITS_IN_BYTE - bitOffset - 1)));    
}

auto Display::turnOn(const int row, const int column) -> void {
    if(!validIndex(row, column)) {
        throw std::out_of_range("Index out of range");
    }
    auto [byteIndex, bitOffset] = getFlattenedIndex(row, column);
    displayArray[byteIndex] = displayArray[byteIndex] | (1 << (BITS_IN_BYTE - bitOffset - 1));
}

auto Display::getFlattenedIndex(const int row, const int column) const -> std::pair<int, int> {
    int index = (WIDTH * row) + column;
    int byteIndex = index / BITS_IN_BYTE;
    int bitOffset = index % BITS_IN_BYTE;
    return std::make_pair(byteIndex, bitOffset);
}

auto Display::resetConsoleCursorPosition() -> void {
    std::cout << std::flush;
    #ifdef _WIN32

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {1, 1};
    SetConsoleCursorPosition(hConsole, coord);

    #else

    std::cout << "\033[1;1H";

    #endif
}

auto Display::renderScene() -> void {
    while (running) {
        for (int index = 0, rowElementCount = 1; index < flattenedSize; ++index) {
            unsigned char setbit = (1 << (BITS_IN_BYTE - 1));
            for(int bitIndex = 0; bitIndex < BITS_IN_BYTE; ++bitIndex) {
                std::cout << ((displayArray[index] & setbit) != 0 ? PIXEL_ON : PIXEL_OFF);

                if(rowElementCount == WIDTH) {
                    std::cout << std::endl;
                    rowElementCount = 0;
                }
                rowElementCount++;
                setbit >>=  1;
            }
        } 
        resetConsoleCursorPosition();
    }
}

auto Display::validIndex(const int row, const int column) const -> bool {
    return row >= 0 && row < HEIGHT && column >= 0 && column < WIDTH;
}

auto Display::setTerminalSize(const int width, const int height) const -> void {
    std::cout << "\033[8;" << height << ";" << width << "t";
}

auto Display::setConsoleWindowSize(const int width, const int height) const -> void {
    #ifdef _WIN32
    HANFLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, (SHORT)(width - 1), (SHORT)(height - 1)};
    setConsoleWindowInfo(console, TRUE, &rect);
    #endif
}

auto Display::hideCursor() const -> void {
    #ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // Hide the cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    #else
    std::cout << "\033[?25l";   // Hide the cursor
    #endif
}

auto Display::showCursor() const -> void {
    #ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = true; // Show the cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    #else
    std::cout << "\033[?25h";   // Shows the cursor
    #endif
}

auto Display::clearConsoleDisplay() const -> void {
    #ifdef _WIN32
    // set the console window size and clear the screen (Windows Specific)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', WIDTH * HEIGHT, coordScreen, &written);
    SetConsoleCursorPosition(hConsole, coordScreen);

    #else
    // Set the terminal size and clear the screen (Unix/ Linux specific)
    setTerminalSize(WIDTH+1, HEIGHT+1);
    system("clear");

    #endif
}
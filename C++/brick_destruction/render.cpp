#include <iostream>
#include <unistd.h> // For usleep() function
#include <termios.h> // For setting terminal attributes
#include <stdio.h> // For getchar() function
#include <sstream> // For string manipulation
#include <vector> // For vector manipulation
using namespace std;

int array[10][10];

#define array (::array)

auto draw() -> void
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            switch (array[i][j])
            {
            case 0:
                cout << " ";
                break;
            case 1:
                cout << "#";
                break;
            case 2:
                cout << "*";
                break;
            }
        }
        cout << endl;
    }
}

auto moveUp() -> void
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (array[i][j] == 2)
            {
                array[i][j] = 0;
                if (i > 0)
                    array[i - 1][j] = 2;
                return;
            }
        }
    }
}

auto moveDown() -> void
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (array[i][j] == 2)
            {
                array[i][j] = 0;
                if (i < 9)
                    array[i + 1][j] = 2;
                return;
            }
        }
    }
}

auto moveLeft() -> void
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (array[i][j] == 2)
            {
                array[i][j] = 0;
                if (j > 0)
                    array[i][j - 1] = 2;
                return;
            }
        }
    }
}

auto moveRight() -> void
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (array[i][j] == 2)
            {
                array[i][j] = 0;
                if (j < 9)
                    array[i][j + 1] = 2;
                return;
            }
        }
    }
}

// Function to disable canonical mode and echoing
void initTermios(int echo) 
{
    struct termios newTermios;
    tcgetattr(0, &newTermios);
    newTermios.c_lflag &= ~ICANON;
    newTermios.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newTermios);
}

// Function to reset terminal settings
void resetTermios(void) 
{
    struct termios newTermios;
    tcgetattr(0, &newTermios);
    newTermios.c_lflag |= ICANON;
    newTermios.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &newTermios);
}

// Function to read arrow key presses
string readArrowKeyPress()
{
    char input;
    vector<char> buffer;

    // Read escape sequence
    while (true)
    {
        input = getchar();
        buffer.push_back(input);
        if (input == '[')
        {
            break;
        }
    }

    // Read arrow key identifier
    while (true)
    {
        input = getchar();
        buffer.push_back(input);
        if (input == 'A' || input == 'B' || input == 'C' || input == 'D')
        {
            break;
        }
    }

    // Convert buffer to string
    stringstream ss;
    for (char c : buffer)
    {
        ss << c;
    }

    return ss.str();
}

int main()
{
    // Initialize terminal settings
    initTermios(0);

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            array[i][j] = 0;
        }
    }
    for (int i = 0; i < 10; i += 9)
    {
        for (int j = 0; j < 10; ++j)
        {
            array[i][j] = 1;
            array[j][i] = 1;
        }
    }
    array[7][3] = 2;
    while (true)
    {
        system("clear"); // Clear the screen
        draw();
        string key = readArrowKeyPress();
        if (key == "\x1B[A") // Up arrow key
            moveUp();
        else if (key == "\x1B[B") // Down arrow key
            moveDown();
        else if (key == "\x1B[D") // Left arrow key
            moveLeft();
        else if (key == "\x1B[C") // Right arrow key
            moveRight();
    }

    // Reset terminal settings
    resetTermios();
}

#ifndef __GAME__
#define __GAME__

#include "game_data.h"
#include <iostream>

#ifndef OS_CONSOLE_INTERFACE
#define OS_CONSOLE_INTERFACE

#define TIME 1000

#ifdef _WIN32
#include <windows.h>
#define CLEAR system("cls")
#define WAIT Sleep(TIME)

#elif __APPLE__
#include <unistd.h>
#define WAIT usleep(TIME*1000)
#define CLEAR system("clear")

#elif __linux__
#include <unistd.h>
#define WAIT usleep(TIME*1000)
#define CLEAR system("clear")
#endif

#endif

#ifndef CLASS_TICTACTOE
#define CLASS_TICTACTOE
class TicTacToe
{
private:
    map<pair<string, int>, pair<int, int>> key;
    int *board, *total_match, number_of_matches, computer;
    string player_first, player_second;
    bool players;

    bool isValidPosition(int position) {
        if(board[position-1] == (-1 * position))
            return true;
        return false;
    }

    inline void markPosition(int position, int player) {
        board[position-1] = player;
    }

    char getSignChar(int k) {
        if(board[k-1] == 0) return 'o';
        else if(board[k-1] == 1) return 'x';
        return k + 48;
    }

    string status() {
        for(int i = 0; i < 3; i+=3) 
            if(board[i] == board[i+1] && board[i+1] == board[i+2])
                return (board[i] == 'o')?"PLAYER1":"PLAYER2";
            for(int i = 0; i < 3; ++i) 
                if(board[i] == board[i+3] && board[i+3] == board[i+6])
                    return (board[i] == 'o')?"PLAYER1":"PLAYER2";
            if(board[0] == board[4] && board[4] == board[8])
                return (board[4] == 'o')?"PLAYER1":"PLAYER2";
            if(board[2] == board[4] && board[4] == board[6])
                return (board[4] == 'o')?"PLAYER1":"PLAYER2";
            for(int i = 0; i < 9; ++i)
                if(board[i] < 0) 
                    return "CONTINUE";
            return "DRAW";
    }

    void drawBoard() {
        char sign = ' ';
        string space = "  ";
        for(int i = 0, k = 1; i < 3; ++i, ++k) {
            for(int j = 0; j < 2; ++j, ++k) {
                sign = getSignChar(k);
                std::cout << space + sign + space + "|";
            }
            sign = getSignChar(k);
            std::cout << space + sign + space << std::endl;
            if(i < 2) {
                for(int j = 0; j < 17; ++j) {
                    std::cout << "-";
                }
                std::cout << std::endl;
            }
        }
    }

public:
    TicTacToe() {
        ifstream data_file;
        data_file.open("data.dat", ios::in);
        while(true) {
            if(data_file.is_open()) {
                string temp;
                int key_id, value1, value2;
                while(data_file >> temp) {
                    data_file >> key_id >> value1 >> value2;
                    key.insert({{temp, key_id}, {value1, value2}}) ;
                }
                data_file.close();
                break;
            }
            else {
                data_file.close();
                makeData();
                data_file.open("data.dat");
            }
        }
        if(!this->players) {
            this->player_first = "Player1";
            this->player_second = "Player2";
        } 
        computer = -1;
    }
    TicTacToe (string player_first, string player_second) {
        this->players = true;
        TicTacToe();
        this->player_first = player_first;
        this->player_second = player_second;
        this->number_of_matches = 0;
        if(this->player_first == "COMPUTER") 
            this->computer++;
        if(this->player_second == "COMPUTER") 
            this->computer++;
        
    }
    TicTacToe (string player_first, string player_second, int number_of_matches) {
        TicTacToe(player_first, player_second);
        this->number_of_matches = number_of_matches;
        this->total_match = new int[number_of_matches];
        board = new int[9];
        for(int i = 0; i < 9; ++i) {
            board[i] = -1 * (i+1);
        }
    }

    string play() {
        // should return one string, with value "PLAYER_NAME MATCH_COUNT MATCH_WON" 
        string game_status = "CONTINUE";
        int current_player = 0;
        // while(game_status == "CONTINUE") {
        //     CLEAR;
        //     this->drawBoard();
        //     int position;
        //     // while(true) {
        //     //     cout << "Choose a ";
        //     // }
        // }
        return "Utsav Raj 2 3";
    }
};

#endif

#endif
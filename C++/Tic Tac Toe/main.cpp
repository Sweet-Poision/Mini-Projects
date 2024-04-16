#include <iostream>
using namespace std;

#ifdef _WIN32
#define CLEAR system("cls")

#elif __APPLE__
#define CLEAR system("clear")

#elif __linux__
#define CLEAR system("clear")
#endif

class Game {
    private:
    int *arrayOfBoard;
    string player1, player2;
    public:
    Game(string player1, string player2) {
        arrayOfBoard = new int[9];
        for(int i = 0; i < 9; ++i) 
            arrayOfBoard[i] = -1*(i+1);
        this->player1 = player1;
        this->player2 = player2;
    }

    char getSignChar(int k) {
        if(arrayOfBoard[k-1] == 0) return 'o';
        else if(arrayOfBoard[k-1] == 1) return 'x';
        return k + 48;
    }

    string status() {
        for(int i = 0; i < 3; i+=3)
            if(arrayOfBoard[i] == arrayOfBoard[i+1] && arrayOfBoard[i+1] == arrayOfBoard[i+2])
                return (arrayOfBoard[i] == 'o')?"PLAYER1":"PLAYER2";
        for(int i = 0; i < 3; ++i)
            if(arrayOfBoard[i] == arrayOfBoard[i+3] && arrayOfBoard[i+3] == arrayOfBoard[i+6])
                return (arrayOfBoard[i] == 'o')?"PLAYER1":"PLAYER2";
        if(arrayOfBoard[0] == arrayOfBoard[4] && arrayOfBoard[4] == arrayOfBoard[8])
            return (arrayOfBoard[4] == 'o')?"PLAYER1":"PLAYER2";
        if(arrayOfBoard[2] == arrayOfBoard[4] && arrayOfBoard[4] == arrayOfBoard[6])
            return (arrayOfBoard[4] == 'o')?"PLAYER1":"PLAYER2";
        for(int i = 0; i < 9; ++i) {
            if(arrayOfBoard[i] < 0) 
                return "CONTINUE";
        }
        return "DRAW";
    }

    void drawBoard() {
        char sign = ' ';
        string space = "  ";
        for(int i = 0, k = 1; i < 3; ++i, ++k) {
            for(int j = 0; j < 2; ++j, ++k) {
                sign = getSignChar(k);
                cout << space + sign + space + "|";
            }
            sign = getSignChar(k);
            cout << space + sign + space << endl;
            if(i < 2) {
                for(int j = 0; j < 17; ++j) {
                    cout << "-";
                }
                cout << endl;
            }
        }
    }

    inline void markPosition(int position, int player) {
        arrayOfBoard[position-1] = player;
    }

    bool isValidPosition(int position) {
        if(arrayOfBoard[position-1] == (-1 * position))
            return true;
        return false;
    }

    string play() {
        string game_status = "CONTINUE";
        int current_player = 0;
        while(game_status == "CONTINUE") {
            CLEAR;
            this->drawBoard();
            int position;
            while(true) {
                cout << "Choose a position : ";
                cin >> position;
                if(isValidPosition(position)) 
                    break;
                cout << "Invalid Position" << endl;
            }
            markPosition(position, current_player);

            current_player++;
            current_player %= 2;
            game_status = this->status();
        } 
        current_player--;
        if(game_status == "PLAYER1")
            return this->player1;
        else if(game_status == "PLAYER2")
            return this->player2;
        return "DRAW";
    }
};

int main() {
    while(true) {
        string winner, player1, player2;
        cout << "Enter Player1 Name: " << endl;
        getline(cin, player1);
        cout << "Enter player2 Name: " << endl;
        getline(cin, player2);
        Game newGame(player1, player2);
        winner = newGame.play();
        CLEAR;
        if(winner == "DRAW") {
            cout << "Draw" << endl;
        }
        else {
            cout << winner << " Won!" << endl;
        }
        char answer;
        do {
            cout << "Do you want to play again : (Y/N) " << endl;
            cin.clear();
            cin >> answer;
            if(answer != 'Y' && answer != 'N') {
                cout << "Incorrect input" << endl;
            }
        }
        while (answer != 'Y' && answer != 'N');
        if(answer == 'N')
            break;
    }    
}
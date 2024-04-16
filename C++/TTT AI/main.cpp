#include <map>
#include <iostream>
#include "game.h"
using namespace std;

void showResultScreen(string result_string) {
    // should have one string, with value "PLAYER_NAME MATCH_COUNT MATCH_WON" 
    reverse(result_string.begin(), result_string.end());
    string match_won = "";
    string match_count = "";
    string player_name = "";
    int space_flag = 0;
    for(int i = 0; i < result_string.size(); ++i) {
        if(result_string[i] != ' ') {
            if(space_flag == 0) {
                match_won += result_string[i];
            }
            else if(space_flag == 1) {
                match_count += result_string[i];
            }
            else if(space_flag >= 2) {
                player_name += result_string[i];
            }
        }
    }
    // show result, data stored successfully
}

string startGame(char match_type, int player_type, int number_of_matches) {
    map<int, string> match_type_name = { { 1, "Single Player" }, { 2, "Tournament" } };
    CLEAR;
    TicTacToe *game;
    cout << "TIC TAC TOE\n" << match_type_name[match_type] << "\n" << endl;
    if(player_type == 1 || player_type == 2) {
        string player_name;
        cout << "Enter Player Name: ";
        getline(cin >> ws, player_name);
        if(player_type == 1)
            game = new TicTacToe(player_name, "COMPUTER", number_of_matches);
        else if(player_type == 2)
            game = new TicTacToe("COMPUTER", player_name, number_of_matches);
    }
    else if(player_type == 3) {
        string player_one, player_two;
        cout << "Enter Player_1 Name: " << endl;
        getline(cin >> ws, player_one);
        cout << "Enter Player_2 Name: " << endl;
        getline(cin >> ws, player_two);
        game = new TicTacToe(player_one, player_two, number_of_matches);
    }
    CLEAR;
    cout << "Let's Begin" << endl;
    WAIT;
    CLEAR;
    string s = game->play();
    cout << s << endl;
    int x;
    cin >> x;
    return s;
}

int main() {
    int answer;
    CLEAR;
    while(true) {
        string result = "NA";
        cout << "TIC TAC TOE" << endl;
        cout << "Choose an option: " << endl;
        cout << "1. Single Match" << endl;
        cout << "2. Tournament" << endl;
        cin >> answer;
        if(answer != 1 && answer != 2) {
            cout << "Invalid Input" << endl;
            WAIT;
        }
        else if(answer == 1) {
            while(true) {
                CLEAR;
                cout << "TIC TAC TOE\nSingle Match\n" << endl;
                cout << "Choose an option: " << endl;
                cout << "1. Player vs Computer" << endl;
                cout << "2. Computer vs Player" << endl;
                cout << "3. Player vs Player" << endl;
                cin >> answer;
                if(answer != 1 && answer != 2 && answer != 3) {
                    cout << "Invalid Input" << endl;
                    WAIT;
                }
                else {
                    result = startGame('S', answer,1);
                    break;
                }
            }
        }
        else if (answer == 2) {
            while(true) {
                CLEAR;
                cout << "TIC TAC TOE" << endl;
                cout << "Enter number of matches to be played: " << endl;
                cin >> answer;
                if(answer <= 0 || answer > 10) {
                    cout << "Invalid Input!\nChoose between [1,10]" << endl;
                    WAIT;
                    WAIT;
                }
                else {
                    int number_of_matches = answer;
                    while (true) {
                        CLEAR;
                        cout << "TIC TAC TOE" << endl;
                        cout << "Tournament with " << number_of_matches << " matches" << endl;
                        cout << "\nChoose and option: " << endl;
                        cout << "1. Player vs Computer" << endl;
                        cout << "2. Computer vs Player" << endl;
                        cout << "3. Player vs Player" << endl;
                        cin >> answer;
                        if(answer != 1 && answer != 2 && answer != 3) {
                            cout << "Invalid Input" << endl;
                            WAIT;
                        }
                        else {
                            result = startGame('T', answer, number_of_matches);
                            break;
                        }
                    }   
                }
            }
        } 
        if(result == "NA") 
            continue;
        CLEAR;
        showResultScreen(result);
        char answer_for_new_game;
        while(true) {
            CLEAR;
            cout << "Do you want to play again? (Y/N): " << endl;
            cin >> answer_for_new_game;
            if(answer_for_new_game != 'Y' && answer_for_new_game != 'N') {
                cout << "Invalid Input" << endl;
                WAIT;
            }
            else 
                break;
        }
        if(answer_for_new_game == 'Y') 
            continue;
        else if(answer_for_new_game == 'N')
            break;
    } 
    CLEAR;
    cout << "Thanks for Playing!" << endl;
    return 0;
}
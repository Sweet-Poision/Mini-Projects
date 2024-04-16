#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

map<pair<string, int>, vector<pair<int, pair<double, double>>>> key;
map<pair<string, int>, pair<int, int>> manipulated_key;

void manipulateMap()
{
    int total;
    for (auto &it : key)
    {
        for (auto &itv : it.second)
        {
            total = itv.second.first + itv.second.second;
            itv.second.first = (itv.second.first * 100.0) / total;
            itv.second.second = (itv.second.second * 100.0) / total;
        }
    }
    for (auto &it : key)
    {
        pair<int, double> max_zero = {0, -1.0};
        pair<int, double> max_one = {0, -1.0};
        for (auto &itv : it.second)
        {
            if (itv.second.first > max_zero.second)
            {
                max_zero.second = itv.second.first;
                max_zero.first = itv.first;
            }
            if (itv.second.second > max_one.second)
            {
                max_one.second = itv.second.second;
                max_one.first = itv.first;
            }
        }
        manipulated_key[it.first] = {max_zero.first, max_one.first};
    }
}

int isWinning(string str)
{
    for (int i = 0; i < 3; ++i)
    {
        if (str[i] == str[i + 3] && str[i + 3] == str[i + 6] && str[i] != 'x')
            return (str[0] - 48);
    }
    for (int i = 0; i < 7; i += 3)
    {
        if (str[i] == str[i + 1] && str[i + 1] == str[i + 2] && str[i] != 'x')
            return (str[0] - 48);
    }
    if (str[4] != 'x' && str[0] == str[4] && str[4] == str[8])
        return (str[0] - 48);
    if (str[4] != 'x' && str[2] == str[4] && str[4] == str[6])
        return (str[0] - 48);
    return -1;
}

pair<int, int> createMap(string data, int id)
{
    pair<int, int> score = {0, 0};
    pair<int, int> temp_score;
    int win_status = isWinning(data);
    if (win_status == 0)
        return {1, 0};
    else if (win_status == 1)
        return {0, 1};

    for (int i = 0; i < (int)data.size(); ++i)
    {
        temp_score = {0, 0};
        if (data[i] != 'x')
            continue;
        data[i] = (char)id + 48;
        temp_score = createMap(data, (id + 1) % 2);
        data[i] = 'x';
        key[{data, id}].push_back({i, temp_score});
        score.first += temp_score.first;
        score.second += temp_score.second;
    }
    return score;
}

void output() {
    ofstream ai_data("data.dat", ios::out);
    for(auto &it : manipulated_key) {
        ai_data << it.first.first << " " << it.first.second << " " << it.second.first << " " << it.second.second << endl;
    }
    ai_data.close();
    cout << "Data Writing Successfull" << endl;
}

// Debuggin and printing map
void printMap()
{
    cout << "{ " << endl;
    for (auto &it : manipulated_key)
    {
        cout << "{ { \"" << it.first.first << "\", " << it.first.second << " }, { ";
        cout << it.second.first << ", " << it.second.second << " } }," << endl;
    }
    cout << "}";
}
void makeData()
{
    string data = "xxxxxxxxx";
    createMap(data, 0);
    manipulateMap();
    output();
    // printMap();
    key.clear();
}
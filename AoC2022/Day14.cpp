#include "stdafx.h"

#include "Day14.h"

using namespace std;

static bool GetTestLine(string& ret, bool reset = false)
{
    const vector res =
    {
        "498,4 -> 498,6 -> 496,6",
        "503,4 -> 502,4 -> 502,9 -> 494,9"
    };

    static size_t i = 0;
    if (reset)
    {
        i = 0;
        return true;
    }

    if (i >= res.size())
        return false;
    ret = res[i++];
    return true;
}

static vector<vector<char>> LoadMap()
{
    ifstream file("input-day14.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return {};
    }

    regex expr(R"((\d+),(\d+))");

    // Get the size of the map's grid first
    // (could have read in the values in pair and iterate over them later, but I decided against allocating that temp memory)
    int maxX = -1, maxY = -1;
    int minX = INT_MAX, minY = INT_MAX;
    string line;
    GetTestLine(line, true);
    //while (GetTestLine(line))
    while (getline(file, line))
    {
        for (sregex_iterator it(line.begin(), line.end(), expr), end; it != end; ++it)
        {
            int x = stoi((*it)[1].str());
            if (x > maxX)
                maxX = x;
            else if (x < minX)
                minX = x;

            int y = stoi((*it)[2].str());
            if (y > maxY)
                maxY = y;
            else if (y < minY)
                minY = y;
        }
    }

    maxX++;
    maxY++;

    // Allocate the map (the sizes are made to fit problem 2)
    vector<vector<char>> map = vector(maxY+2, vector(2*maxX, ' '));

    // Read the file again, and build the map (unsure if the best way would
    GetTestLine(line, true);

    file.clear();
    file.seekg(0, ios::beg);
    //while (GetTestLine(line))
    while (getline(file, line))
    {
        bool first = true;
        int currX = 0, currY = 0;
        for (sregex_iterator it(line.begin(), line.end(), expr), end; it != end; ++it)
        {
            int tgtX = stoi((*it)[1].str());
            int tgtY = stoi((*it)[2].str());
            if (!first)
                for (int y = min(currY, tgtY), yend = max(currY, tgtY); y <= yend; y++)
                    for (int x = min(currX, tgtX), xend = max(currX, tgtX); x <= xend; x++)
                        map[y][x] = '#';

            currX = tgtX;
            currY = tgtY;
            first = false;
        }
    }

    return map;
}

static bool NextSandPos(const vector<vector<char>>& map, pair<int, int>& pos)
{
    // not elegant, but it works
    int x = pos.first;
    int y = pos.second + 1;
    if (y >= map.size())
    {
        pos = pair(x, y);
        return false;
    }

    if (map[y][x] == ' ')
    {
        pos = pair(x, y);
        return true;
    }

    x -= 1;
    if (map[y][x] == ' ')
    {
        pos = pair(x, y);
        return true;
    }

    x += 2;
    if (map[y][x] == ' ')
    {
        pos = pair(x, y);
        return true;
    }

    return false;

}

int Day14::CountUnitsOfSand()
{
    auto map = LoadMap();

    int count = 0;
    for(;;)
    {
        auto pos = pair(500, 0);
        while (NextSandPos(map, pos)) {}
        if (pos.second >= map.size())
            break;
        count++;
        map[pos.second][pos.first] = 'o';
    }

    //cout << endl;

    //for (int y = 0; y < 10; y++)
    //{
    //    for (int x = 494; x < 504; x++)
    //    {
    //        cout << map[y][x];
    //    }
    //    cout << endl;
    //}
    return count;
}

int Day14::CountUnitsOfSand2()
{
    auto map = LoadMap();
    map[map.size() - 1] = vector(map[0].size(), '#');

    int count = 0;
    for (;;)
    {
        auto pos = pair(500, 0);
        while (NextSandPos(map, pos)) {}
        if (pos.second >= map.size() || map[0][500] != ' ')
            break;
        count++;
        map[pos.second][pos.first] = 'o';
    }

    return count;
}

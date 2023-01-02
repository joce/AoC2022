#include "stdafx.h"

#include "Day12.h"

using namespace std;

static bool LoadMap(vector<string>& map, pair<int, int>& startPos, pair<int, int>& endPos)
{
#if 1
    ifstream file("input-day12.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return false;
    }

    string line;
    int lineCnt = 0;
    bool startFound = false, endFound = false;
    while (getline(file, line))
    {
        if (!startFound)
        {
            auto colCnt = line.find('S');
            if (colCnt != string::npos)
            {
                startPos = pair(static_cast<int>(colCnt), lineCnt);
                startFound = true;
            }
        }

        if (!endFound)
        {
            auto colCnt = line.find('E');
            if (colCnt != string::npos)
            {
                endPos = pair(static_cast<int>(colCnt), lineCnt);
                endFound = true;
            }
        }

        map.push_back(line);
        lineCnt++;
    }
#else
    map.emplace_back("Sabqponm");
    map.emplace_back("abcryxxl");
    map.emplace_back("accszExk");
    map.emplace_back("acctuvwj");
    map.emplace_back("abdefghi");

    startPos = pair(0, 0);
    endPos = pair(5, 2);
#endif
    return true;
}

static int GetPathLength(vector<string>& map, const pair<int, int>& endPos, bool findFirstA = false)
{
    bool show = false;

    const int rowCnt = static_cast<int>(map.size());
    const int colCnt = static_cast<int>(map[0].length());

    auto visited = vector(rowCnt, vector(colCnt, false));

    set<pair<int, int>> toVisit[2];
    int curToVisit = 0;
    int nextToVisit = 1;
    toVisit[curToVisit].insert(endPos);

    int steps = 0;

    auto canMove = [&map, &visited](char atPos, pair<int, int>&& newPos) -> bool
    {
        return !visited[newPos.second][newPos.first] &&
            ((atPos >= 'a' && atPos - 1 <= map[newPos.second][newPos.first]) || (atPos == 'a' && map[newPos.second][newPos.first] == 'S'));
    };

    bool found = false;
    for (;;)
    {
        for (const auto& pos : toVisit[curToVisit])
        {
            visited[pos.second][pos.first] = true;
            char atPos = map[pos.second][pos.first];

            if ((findFirstA && atPos == 'a') || atPos == 'S')
                return steps;

            if (atPos == 'E')
                atPos = 'z';

            if (pos.first > 0 && canMove(atPos, pair(pos.first - 1, pos.second)))
                toVisit[nextToVisit].emplace(pos.first - 1, pos.second);

            if (pos.first < colCnt - 1 && canMove(atPos, pair(pos.first + 1, pos.second)))
                toVisit[nextToVisit].emplace(pos.first + 1, pos.second);

            if (pos.second > 0 && canMove(atPos, pair(pos.first, pos.second - 1)))
                toVisit[nextToVisit].emplace(pos.first, pos.second - 1);

            if (pos.second < rowCnt - 1 && canMove(atPos, pair(pos.first, pos.second + 1)))
                toVisit[nextToVisit].emplace(pos.first, pos.second + 1);
        }

        if (toVisit[nextToVisit].empty())
            return -1;

        // DEBUG
        if (/*toVisit[nextToVisit].empty()*/show)
        {
            cout << endl;
            for (int i = 0; i < rowCnt; ++i)
            {
                for (int j = 0; j < colCnt; ++j)
                {
                    cout << static_cast<char>(visited[i][j] ? toupper(map[i][j]) : map[i][j]);
                }
                cout << endl;
            }
            cout << endl;
        }

        steps++;

        const int t = curToVisit;
        curToVisit = nextToVisit;
        nextToVisit = t;
        toVisit[nextToVisit].clear();
    }
}


int Day12::GetFewestSteps()
{
    vector<string> map;
    pair<int, int> startPos, endPos;
    if (!LoadMap(map, startPos, endPos))
        return -1;

    return GetPathLength(map, endPos);
}

int Day12::GetFewestStepsFromA()
{
    vector<string> map;
    pair<int, int> startPos, endPos;
    if (!LoadMap(map, startPos, endPos))
        return -1;

    return GetPathLength(map, endPos, true);
}

#include "stdafx.h"

#include "Day8.h"

using namespace std;

static vector<string> LoadGrid()
{
#if 1
    vector<string> ret;

    ifstream file("input-day8.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return ret;
    }

    string line;
    while (getline(file, line))
        ret.push_back(line);
#else

    vector<string> ret {
    "30373",
    "25512",
    "65332",
    "33549",
    "35390"
    };

#endif
    return ret;
}

int Day8::CountVisibleTrees()
{
    const auto grid = LoadGrid();

    set<pair<int, int>> positions;

    vector highestCols(grid[0].size(), '/');
    vector highestInvCols(grid[0].size(), '/');

    for (int y = 0, yend = static_cast<int>(grid.size()); y < yend; y++)
    {
        auto highestRow = '/';
        auto& s = grid[y];
        for (int x = 0, xend = static_cast<int>(s.length()); x < xend; x++)
        {
            if (s[x] > highestRow)
            {
                highestRow = s[x];
                positions.insert(pair(x, y));
            }

            if (s[x] > highestCols[x])
            {
                highestCols[x] = s[x];
                positions.insert(pair(x, y));
            }
        }

        highestRow = '/';
        for (int x = static_cast<int>(s.length()) - 1; x >= 0; x--)
        {
            if (s[x] > highestRow)
            {
                highestRow = s[x];
                positions.insert(pair(x, y));
            }
        }
    }

    ranges::fill(highestCols, '/');

    for (int y = static_cast<int>(grid.size()) - 1; y >= 0; y--)
    {
        auto& s = grid[y];
        for (int x = 0, xend = static_cast<int>(s.length()); x < xend; x++)
        {
            if (s[x] > highestCols[x])
            {
                highestCols[x] = s[x];
                positions.insert(pair(x, y));
            }
        }
    }

    return static_cast<int>(positions.size());
}

int Day8::GetScenicScore()
{
    const auto grid = LoadGrid();

    auto ComputeScenicScore = [&grid](int x, int y) -> int
    {
        auto val = grid[y][x];
        int score = 1;

        int cnt = 0;
        for (int yy = y + 1, yend = static_cast<int>(grid.size()); yy < yend; yy++)
        {
            cnt++;
            if (val <= grid[yy][x])
                break;
        }
        score *= cnt ? cnt : 1;

        cnt = 0;
        for (int yy = y - 1; yy >= 0; yy--)
        {
            cnt++;
            if (val <= grid[yy][x])
                break;
        }
        score *= cnt ? cnt : 1;

        const auto& s = grid[y];

        cnt = 0;
        for (int xx = x+1, xend = static_cast<int>(s.size()); xx < xend; xx++)
        {
            cnt++;
            if (val <= grid[y][xx])
                break;
        }
        score *= cnt ? cnt : 1;

        cnt = 0;
        for (int xx = x - 1; xx >=0; xx--)
        {
            cnt++;
            if (val <= grid[y][xx])
                break;
        }
        score *= cnt ? cnt : 1;

        return score;
    };

    int bestScore = -1;

    for (int y = 0, yend = static_cast<int>(grid.size()); y < yend; y++)
    {
        auto& s = grid[y];
        for (int x = 0, xend = static_cast<int>(s.length()); x < xend; x++)
        {
            const auto score = ComputeScenicScore(x, y);
            if (score > bestScore)
            {
                bestScore = score;
            }
        }
    }

    return bestScore;
}


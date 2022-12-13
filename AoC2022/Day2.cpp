#include "stdafx.h"

#include "Day2.h"

using namespace std;

enum RPS
{
    Rock,
    Paper,
    Scissors
};

int Day2::ComputeScore()
{
    ifstream file("input-day2.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int score = 0;

    string line;
    while (getline(file, line))
    {
        // We here assume properly formatted strings.
        const RPS otherHand = static_cast<RPS>(line[0] - 'A');
        const RPS myHand = static_cast<RPS>(line[2] - 'X');

        score += myHand + 1;

        const int result = (myHand - otherHand + 3) % 3;
        if (result == 0)
            // The values are identical. This is a draw.
            score += 3;
        else if (result == 1)
            // Distance of 1 means a win.
            score += 6;
    }

    return score;
}

int Day2::ComputeScore2()
{
    ifstream file("input-day2.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int score = 0;

    string line;
    while (getline(file, line))
    {
        // We here assume properly formatted strings.
        const RPS otherHand = static_cast<RPS>(line[0] - 'A');
        const int result = line[2] - 'Y';
        const RPS myHand = static_cast<RPS>((otherHand + result + 3) % 3);

        score += myHand + 1;

        if (result == 0)
            // The values are identical. This is a draw.
            score += 3;
        else if (result == 1)
            // Distance of 1 means a win.
            score += 6;
    }

    return score;
}

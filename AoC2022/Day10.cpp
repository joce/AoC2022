#include "stdafx.h"

#include "Day10.h"

using namespace std;

bool GetTestLine(string& res)
{
    static int cnt = 0;
    vector values = {
        "addx 15",
        "addx -11",
        "addx 6",
        "addx -3",
        "addx 5",
        "addx -1",
        "addx -8",
        "addx 13",
        "addx 4",
        "noop",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx -35",
        "addx 1",
        "addx 24",
        "addx -19",
        "addx 1",
        "addx 16",
        "addx -11",
        "noop",
        "noop",
        "addx 21",
        "addx -15",
        "noop",
        "noop",
        "addx -3",
        "addx 9",
        "addx 1",
        "addx -3",
        "addx 8",
        "addx 1",
        "addx 5",
        "noop",
        "noop",
        "noop",
        "noop",
        "noop",
        "addx -36",
        "noop",
        "addx 1",
        "addx 7",
        "noop",
        "noop",
        "noop",
        "addx 2",
        "addx 6",
        "noop",
        "noop",
        "noop",
        "noop",
        "noop",
        "addx 1",
        "noop",
        "noop",
        "addx 7",
        "addx 1",
        "noop",
        "addx -13",
        "addx 13",
        "addx 7",
        "noop",
        "addx 1",
        "addx -33",
        "noop",
        "noop",
        "noop",
        "addx 2",
        "noop",
        "noop",
        "noop",
        "addx 8",
        "noop",
        "addx -1",
        "addx 2",
        "addx 1",
        "noop",
        "addx 17",
        "addx -9",
        "addx 1",
        "addx 1",
        "addx -3",
        "addx 11",
        "noop",
        "noop",
        "addx 1",
        "noop",
        "addx 1",
        "noop",
        "noop",
        "addx -13",
        "addx -19",
        "addx 1",
        "addx 3",
        "addx 26",
        "addx -30",
        "addx 12",
        "addx -1",
        "addx 3",
        "addx 1",
        "noop",
        "noop",
        "noop",
        "addx -9",
        "addx 18",
        "addx 1",
        "addx 2",
        "noop",
        "noop",
        "addx 9",
        "noop",
        "noop",
        "noop",
        "addx -1",
        "addx 2",
        "addx -37",
        "addx 1",
        "addx 3",
        "noop",
        "addx 15",
        "addx -21",
        "addx 22",
        "addx -6",
        "addx 1",
        "noop",
        "addx 2",
        "addx 1",
        "noop",
        "addx -10",
        "noop",
        "noop",
        "addx 20",
        "addx 1",
        "addx 2",
        "addx 2",
        "addx -6",
        "addx -11",
        "noop",
        "noop",
        "noop"
    };
    if (cnt < values.size())
    {
        res = values[cnt++];
        return true;
    }
    return false;
}

int Day10::SignalStrength()
{
    ifstream file("input-day10.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int strength = 0;

    int value = 1;
    auto incrementCycle = [&value, &strength, cycleCount = 0]() mutable
    {
        cycleCount++;
        if (cycleCount == 20 || cycleCount == 60 || cycleCount == 100 || cycleCount == 140 || cycleCount == 180 || cycleCount == 220)
        {
            strength += cycleCount * value;
        }
    };

    string line;
    while (getline(file, line))
    //while(GetTestLine(line))
    {
        if (line.starts_with("noop"))
        {
            incrementCycle();
        }
        else if (line.starts_with("addx"))
        {
            incrementCycle();
            incrementCycle();
            value += atoi(line.c_str() + 5);
        }
    }

    return strength;
}

void Day10::DrawCRT()
{
    ifstream file("input-day10.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return;
    }

    int spritePosition = 1;
    auto incrementCycle = [&spritePosition, drawPosition = 0]() mutable
    {
        const int usedPos = drawPosition % 40;
        if (drawPosition > 0 && !usedPos)
            cout << endl;

        if (usedPos == spritePosition || usedPos == spritePosition + 1 || usedPos == spritePosition - 1)
            cout << '#';
        else
            cout << ' ';

        drawPosition++;
    };

    string line;
    while (getline(file, line))
    //while(GetTestLine(line))
    {
        if (line.starts_with("noop"))
        {
            incrementCycle();
        }
        else if (line.starts_with("addx"))
        {
            incrementCycle();
            incrementCycle();
            spritePosition += atoi(line.c_str() + 5);
        }
    }
}

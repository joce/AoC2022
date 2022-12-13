#include "stdafx.h"

#include "Day1.h"

using namespace std;

int Day1::GetTopCalories()
{
    int maxCalories = -1;
    std::ifstream file("input-day1.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    string line;
    int currCalories = 0;
    while (getline(file, line))
    {
        if (line.empty())
        {
            if (currCalories > maxCalories)
                maxCalories = currCalories;
            currCalories = 0;
        }
        else
        {
            currCalories += stoi(line);
        }
    }

    if (currCalories > maxCalories)
        maxCalories = currCalories;

    return maxCalories;
}

int Day1::GetTop3Calories()
{
    std::ifstream file("input-day1.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int currCalories = 0;
    int maxCalories[3] = {0, 0, 0};

    auto checkMax = [&currCalories, &maxCalories]()
    {
        // Probably not worth the effort here given the size of the array to deal with.
        //for (int i = 0; i < 3; i++)
        //{
        //    if (currCalories > maxCalories[i])
        //    {
        //        for (int j = 2; j > i; j--)
        //            maxCalories[j] = maxCalories[j - 1];

        //        maxCalories[i] = currCalories;
        //        break;
        //    }
        //}

        if (currCalories > maxCalories[0])
        {
            maxCalories[2] = maxCalories[1];
            maxCalories[1] = maxCalories[0];
            maxCalories[0] = currCalories;
        }
        else if (currCalories > maxCalories[1])
        {
            maxCalories[2] = maxCalories[1];
            maxCalories[1] = currCalories;
        }
        else if (currCalories > maxCalories[2])
        {
            maxCalories[2] = currCalories;
        }
    };

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            checkMax();
            currCalories = 0;
        }
        else
        {
            currCalories += stoi(line);
        }
    }

    checkMax();

//    return accumulate(maxCalories, maxCalories + 3, 0);
    return maxCalories[0] + maxCalories[1] + maxCalories[2];
}

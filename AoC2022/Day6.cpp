#include "stdafx.h"

#include "Day6.h"

using namespace std;

int Day6::FindStartOfPacket()
{
    ifstream file("input-day6.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return {};
    }

    string line;
    if (getline(file, line))
    {
        const char* c = line.c_str();

        for (int i = 0, j = 1, k = 2, m = 3, end = static_cast<int>(line.size()); m < end; i++, j++, k++, m++)
        {
            if (c[i] != c[j] && c[i] != c[k] && c[i] != c[m] &&
                                c[j] != c[k] && c[j] != c[m] &&
                                                c[k] != c[m])
            {
                return m+1;
            }
        }
    }

    return -1;
}

int Day6::FindStartOfMessage()
{
    ifstream file("input-day6.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return {};
    }

    string line;
    if (getline(file, line))
    {
        const char* c = line.c_str();

        for (int i = 0, end = static_cast<int>(line.length())-14; i < end; i++)
        {
            bool dup = false;
            for (int j = i; j < i+13; j++)
            {
                for (int k = j+1; k < i+14; k++)
                {
                    if (c[j] == c[k])
                    {
                        dup = true;
                        goto EndCheck;
                    }
                }
            }
            EndCheck:
            if (!dup)
                return i + 14;
        }
    }

    return -1;
}

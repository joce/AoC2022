#include "stdafx.h"

#include "Day3.h"

using namespace std;

int Day3::CheckRucksack()
{
    ifstream file("input-day3.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int priorities = 0;

    string line;
    while (getline(file, line))
    {
        int64_t items_1 = 0; // used as bitfield for compartment 1
        int64_t items_2 = 0; // used as bitfield for compartment 2
        const int compartmentSize = line.length() / 2;
        for (int i = 0, j = compartmentSize; i < compartmentSize; i++, j++)
        {
            unsigned compt1 = line[i];
            unsigned compt2 = line[j];
            items_1 |= (1ll << (compt1 <= 'Z' ? (compt1 - 'A' + 26) : (compt1 - 'a')));
            items_2 |= (1ll << (compt2 <= 'Z' ? (compt2 - 'A' + 26) : (compt2 - 'a')));
        }

        int64_t res = items_1 & items_2;
        if (!res)
            continue;

        int priority = 0;
        for (int i = 0; i < 52; i++)
        {
            if (res & (1ll << i))
                priority += (i+1);
        }
        priorities += priority;
    }

    return priorities;
}

int Day3::CheckBadges()
{
    ifstream file("input-day3.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    int priorities = 0;

    string line;
    while (getline(file, line))
    {
        int64_t allItems = 0; // used as bitfield for compartment 1
        const int sackSize = line.length();
        for (int i = 0; i < sackSize; i++)
        {
            const unsigned item = line[i];
            allItems |= (1ll << (item <= 'Z' ? (item - 'A' + 26) : (item - 'a')));
        }

        for (int cnt = 0; cnt < 2; cnt++)
        {
            int64_t lineItems = 0;
            string line2;
            getline(file, line2);
            const int sackSize = line2.length();
            for (int i = 0; i < sackSize; i++)
            {
                const unsigned item = line2[i];
                lineItems |= (1ll << (item <= 'Z' ? (item - 'A' + 26) : (item - 'a')));
            }
            allItems &= lineItems;
        }

        for (int i = 0; i < 52; i++)
        {
            if (allItems & (1ll << i))
                priorities += (i + 1);
        }
    }

    return priorities;
}

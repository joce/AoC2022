#include "stdafx.h"

#include "Day11.h"

using namespace std;

struct Monkey
{
    list<uint64_t> m_Items;
    function<int(uint64_t&)> m_Operation;
    uint64_t m_InspectCount = 0;
};

// Input was small enough, I decided against parsing. 
static vector<Monkey> GetTestMonkeys()
{
    // Compute the modulo value to be used to shrink the item stress level
    constexpr int lcm = 23 * 19 * 13 * 17;
    return vector<Monkey>
    {
        {
            { 79, 98 },
            [](uint64_t& i) -> int
            {
                //i = (i * 19) / 3;
                i = ((i % lcm) * 19) % lcm;
                return (i % 23 == 0) ? 2 : 3;
            }
        },
        {
            { 54, 65, 75, 74 },
            [](uint64_t& i) -> int
            {
                //i = (i + 6) / 3;
                i = ((i % lcm) + 6) % lcm;
                return (i % 19 == 0) ? 2 : 0;
            }
        },
        {
            { 79, 60, 97 },
            [](uint64_t& i) -> int
            {
                //i = (i * i) / 3;
                i = (i*i) % lcm;
                return (i % 13 == 0) ? 1 : 3;
            }
        },
        {
            { 74 },
            [](uint64_t& i) -> int
            {
                //i = (i + 3) / 3;
                i = ((i % lcm) + 3) %lcm;
                return (i % 17 == 0) ? 0 : 1;
            }
        }
    };
}

static vector<Monkey> GetRealMonkeys()
{
    // Compute the modulo value to be used to shrink the item stress level
    constexpr int lcm = 11 * 19 * 5 * 2 * 13 * 7 * 3 * 17;
    return vector<Monkey>
    {
        { // 0
            { 97, 81, 57, 57, 91, 61 },
                [](uint64_t& i) -> int
            {
                //i = (i * 7) / 3;
                i = ((i % lcm) * 7) % lcm;
                return (i % 11 == 0) ? 5 : 6;
            }
        },
        { // 1
            { 88, 62, 68, 90 },
            [](uint64_t& i) -> int
            {
                //i = (i * 17) / 3;
                i = ((i % lcm) * 17) % lcm;
                return (i % 19 == 0) ? 4 : 2;
            }
        },
        { // 2
            { 74, 87 },
            [](uint64_t& i) -> int
            {
                //i = (i + 2) / 3;
                i = ((i % lcm) + 2) % lcm;
                return (i % 5 == 0) ? 7 : 4;
            }
        },
        { // 3
            { 53, 81, 60, 87, 90, 99, 75 },
            [](uint64_t& i) -> int
            {
                //i = (i + 1) / 3;
                i = ((i % lcm) + 1) % lcm;
                return (i % 2 == 0) ? 2 : 1;
            }
        },
        { // 4
            { 57 },
            [](uint64_t& i) -> int
            {
                //i = (i + 6) / 3;
                i = ((i % lcm) + 6) % lcm;
                return (i % 13 == 0) ? 7 : 0;
            }
        },
        { // 5
            { 54, 84, 91, 55, 59, 72, 75, 70 },
            [](uint64_t& i) -> int
            {
                //i = (i * i) / 3;
                i = (i * i) % lcm;
                return (i % 7 == 0) ? 6 : 3;
            }
        },
        { // 6
            { 95, 79, 79, 68, 78 },
            [](uint64_t& i) -> int
            {
                //i = (i + 3) / 3;
                i = ((i % lcm) + 3) % lcm;
                return (i % 3 == 0) ? 1 : 3;
            }
        },
        { // 7
            { 61, 97, 67 },
            [](uint64_t& i) -> int
            {
                //i = (i + 4) / 3;
                i = ((i % lcm) + 4) % lcm;
                return (i % 17 == 0) ? 0 : 5;
            }
        }
    };
}

uint64_t Day11::GetMonkeyBusinessLevel()
{
    constexpr int roundsCount = 10000;
    auto monkeys = GetRealMonkeys();

    // Do the monkey business
    for (int r = 0; r < roundsCount; r++)
    {
        for (Monkey& monkey : monkeys)
        {
            monkey.m_InspectCount += static_cast<int>(monkey.m_Items.size());
            for (uint64_t item : monkey.m_Items)
            {
                const int dest = monkey.m_Operation(item);
                monkeys[dest].m_Items.push_front(item);
            }
            monkey.m_Items.clear();
        }
    }

    // Get the top 2 items.
    uint64_t best[2] = {0,0};

    for (const auto& monkey : monkeys)
    {
        if (monkey.m_InspectCount > best[0])
        {
            best[1] = best[0];
            best[0] = monkey.m_InspectCount;
            continue;
        }

        if (monkey.m_InspectCount > best[1])
            best[1] = monkey.m_InspectCount;
    }

    return best[0] * best[1];
}

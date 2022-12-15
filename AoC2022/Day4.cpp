#include "stdafx.h"

#include "Day4.h"

#include <tuple>

using namespace std;

template <typename F>
static int CountOverlap(const F& contains)
{
    ifstream file("input-day4.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    regex expr(R"((\d+)-(\d+),(\d+)-(\d+))");

    int contained = 0;

    string line;
    while (getline(file, line))
    {
        auto match = smatch{};
        if (!regex_match(line, match, expr))
        {
            cerr << "Can't parse line \"" << line << "\"" << endl;
            continue;
        }

        tuple<int, int> a(stoi(match[1].str()), stoi(match[2].str()));
        tuple<int, int> b(stoi(match[3].str()), stoi(match[4].str()));
        if (contains(a, b) || contains(b, a))
        {
            contained++;
        }
    }

    return contained;
}

int Day4::CountOverlaps()
{
    auto contains = [](const tuple<int, int>& a, const tuple<int, int>& b) -> bool
    {
        return get<0>(a) <= get<0>(b) && get<1>(a) >= get<1>(b);
    };

    return CountOverlap(contains);
}


int Day4::CountPartialOverlaps()
{
    auto contains = [](const tuple<int, int>& a, const tuple<int, int>& b) -> bool
    {
        return (get<0>(a) <= get<0>(b) && get<1>(a) >= get<0>(b)) ||
            (get<0>(b) <= get<0>(a) && get<1>(b) >= get<0>(a));
    };

    return CountOverlap(contains);
}

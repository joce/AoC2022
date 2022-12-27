#include "stdafx.h"

#include "Day9.h"

#include <functional>

using namespace std;

class Rope
{
    vector<pair<int, int>> m_Knots;

    const int m_KnotsCount;

    set<pair<int, int>> m_TailPlaces;

public:

    Rope(int knotsCount) :
        m_KnotsCount(knotsCount)
    {
        m_Knots.reserve(knotsCount);
        for (int i = 0; i < knotsCount; i++)
        {
            m_Knots.emplace_back(500, 500);
        }
        m_TailPlaces.insert(m_Knots.back());
    }

    int TailPlaces() const
    {
        return static_cast<int>(m_TailPlaces.size());
    }

    void AdjustKnot(int k)
    {
        int currX = m_Knots[k].first;
        int currY = m_Knots[k].second;
        int prevX = m_Knots[k - 1].first;
        int prevY = m_Knots[k - 1].second;

        int distX = prevX - currX;
        int distY = prevY - currY;

        if (abs(distX) <= 1 &&    // ***
            abs(distY) <= 1)      // *#*
            return;               // ***

        if (distX < 0)
        {
            if (distY < -1) // (-2, -2)
            {
                m_Knots[k].first--;
                m_Knots[k].second--;
            }
            else if (distY > 1) // (-2, 2)
            {
                m_Knots[k].first--;
                m_Knots[k].second++;
            }
            else // (-2, -1), (-2, 0) or (-2, 1)
            {
                m_Knots[k].first--;
                m_Knots[k].second = prevY;
            }
        }
        else if (distX > 0)
        {
            if (distY < -1) // (2, -2)
            {
                m_Knots[k].first++;
                m_Knots[k].second--;
            }
            else if (distY > 1) // (2, 2)
            {
                m_Knots[k].first++;
                m_Knots[k].second++;
            }
            else // (2, -1), (2, 0) or (2, 1)
            {
                m_Knots[k].first++;
                m_Knots[k].second = prevY;
            }
        }
        else
        {
            if (distY < -1) // (-1, -2), (0, -2) or (1, -2)
            {
                m_Knots[k].first = prevX;
                m_Knots[k].second--;
            }
            else if (distY > 1) // (-1, 2), (0, 2) or (1, 2)
            {
                m_Knots[k].first = prevX;
                m_Knots[k].second++;
            }
        }
    }

    void Move(char dir, int count)
    {
        function<void()> ajdustHead;
        if (dir == 'U')
            ajdustHead = [this] { m_Knots[0].second--; };

        else if (dir == 'D')
            ajdustHead = [this] { m_Knots[0].second++; };

        else if (dir == 'L')
            ajdustHead = [this] { m_Knots[0].first--; };

        else if (dir == 'R')
            ajdustHead = [this] { m_Knots[0].first++; };

        for (int i = 0; i < count; i++)
        {
            ajdustHead();
            for (int k = 1; k < m_KnotsCount; k++)
                AdjustKnot(k);
            m_TailPlaces.insert(m_Knots.back());
        }
    }
};

int Day9::CountTailPositions(int knotCount)
{
    ifstream file("input-day9.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return -1;
    }

    Rope rope(knotCount);
    string line;
    while (getline(file, line))
        rope.Move(line[0], atoi(line.c_str() + 2));

    return rope.TailPlaces();
}

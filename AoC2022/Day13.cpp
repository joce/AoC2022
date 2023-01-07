#include "stdafx.h"

#include "Day13.h"

using namespace std;

struct Item
{
    int value = -1;
    shared_ptr<vector<Item>> items;

    void Print() const
    {
        if (value >= 0)
            cout << value;
        else
        {
            cout << "[";
            if (items)
            {
                bool first = true;
                for (const auto& item : *items)
                {
                    if (first)
                        first = false;
                    else
                        cout << ",";
                    item.Print();
                }
            }
            cout << "]";
        }
    }

    bool operator==(const Item& other) const
    {
        return Compare(*this, other) == 0;
    }

    static bool IsSmaller(const Item& left, const Item& right)
    {
        return Compare(left, right) < 0;
    }

    static int Compare(const Item& left, const Item& right)
    {
        // i, i
        if (left.value > -1 && right.value > -1)
            return left.value == right.value ? 0 : (left.value < right.value ? -1 : 1);

        // v, v
        if (left.items && right.items)
        {
            const int leftSize = static_cast<int>(left.items->size());
            const int rightSize = static_cast<int>(right.items->size());
            for (int i = 0; i < leftSize && i < rightSize; i++)
            {
                const int cmp = Compare(left.items->at(i), right.items->at(i));
                if (cmp)
                    return cmp;
            }
            return leftSize == rightSize ? 0 : leftSize < rightSize ? -1 : 1;
        }

        if (left.items)
        {
            // v[0], i
            if (right.value > -1)
            {
                const int res = Compare(left.items->front(), right);
                return res != 0 ? res : left.items->size() > 1 ? 1 : 0;
            }
            // v[0], []
            return 1;
        }
            
        if (right.items)
        {
            // i, v[0]
            if (left.value > -1)
            {
                const int res = Compare(left, right.items->front());
                return res != 0 ? res : right.items->size() > 1 ? -1 : 0;
            }
            // [], v[0]
            return -1;
        }

        if (left.value > -1)
            return 1;

        if (right.value > -1)
            return -1;

        return 0;
    }
};

void LoadItem(string::iterator& toParse, const string::iterator& end, Item& item)
{
    while (toParse != end)
    {
        char curr = *toParse;
        if (curr == ']')
        {
            ++toParse;
            break;
        }
        if (curr == '[')
        {
            if (!item.items)
                item.items = make_shared<vector<Item>>();
            ++toParse;
            item.items->emplace_back(Item());
            LoadItem(toParse, end, item.items->back());
        }
        else if (curr == ',')
            ++toParse;
        else if (curr >= '0' && curr <= '9')
        {
            auto start = toParse;
            while (*toParse >= '0' && *toParse <= '9')
                ++toParse;
            int res;
            std::from_chars(&*start, &*toParse, res);
            if (!item.items)
                item.items = make_shared<vector<Item>>();
            item.items->emplace_back(Item());
            item.items->back().value = res;
        }
    }
}

static bool GetTestLine(string & ret)
{
    const vector res=
    {
        "[1,1,3,1,1]",
        "[1,1,5,1,1]",
        "",
        "[[1],[2,3,4]]",
        "[[1],4]",
        "",
        "[9]",
        "[[8,7,6]]",
        "",
        "[[4,4],4,4]",
        "[[4,4],4,4,4]",
        "",
        "[7,7,7,7]",
        "[7,7,7]",
        "",
        "[]",
        "[3]",
        "",
        "[[[]]]",
        "[[]]",
        "",
        "[1,[2,[3,[4,[5,6,7]]]],8,9]",
        "[1,[2,[3,[4,[5,6,0]]]],8,9]",
        "",
        "[[1],[2,3,4]]",
        "[[1],[2,3,4]]",
        "",
        "[10,7,10,9,7]",
        "[10,7,10,9]"
    };
    static size_t i = 0;
    if (i >= res.size())
        return false;
    ret = res[i++];
    return true;
}

bool LoadItems(vector<Item>& toFill)
{
    ifstream file("input-day13.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return false;
    }

    string line;
//    while (GetTestLine(line))
    while (getline(file, line))
    {
        if (line.length() == 0)
            continue;

        auto start = line.begin() + 1;
        toFill.emplace_back();
        LoadItem(start, line.end(), toFill.back());
    }

    return true;
}

int Day13::SumOfPairIndices()
{
    vector<Item> res;
    if (!LoadItems(res))
        return -1;

    int idx = 1;
    int sum = 0;
    for (int i = 0, size = static_cast<int>(res.size()); i < size; i++)
    {
        if (i%2)
        {
            if (Item::Compare(res[i-1], res[i]) < 0)
                sum += idx;
            idx++;
        }
    }

    return sum;
}

int Day13::SortAllPackets()
{
    vector<Item> res;
    if (!LoadItems(res))
        return -1;
    
    res.emplace_back(-1, make_shared<vector<Item>>());
    res.back().items->emplace_back(-1, make_shared<vector<Item>>());
    res.back().items->back().items->emplace_back(2);
    const Item two = res.back();

    res.emplace_back(-1, make_shared<vector<Item>>());
    res.back().items->emplace_back(-1, make_shared<vector<Item>>());
    res.back().items->back().items->emplace_back(6);
    const Item six = res.back();

    ranges::sort(res, Item::IsSmaller);

    const int twoIdx = static_cast<int>(distance(res.begin(), ranges::find(res, two)));
    const int sixIdx = static_cast<int>(distance(res.begin(), ranges::find(res, six)));

    return (twoIdx+1) * (sixIdx+1);
}

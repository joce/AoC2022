#include "stdafx.h"

#include "Day5.h"

#include <map>

using namespace std;

template <typename F>
static string ProcessStacks(const F&& process)
{
    ifstream file("input-day5.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return {};
    }

    // The stack definition
    vector<string> tempStacksDef;

    const regex stacksNumbersExp(R"(^\s(\d\s{3})+\d\s$)");

    map<const int, vector<char>> stacks;

    string line;
    // we will need to read the stack first
    while (getline(file, line))
    {
        if (regex_match(line, stacksNumbersExp))
        {
            // We've reached the bottom of the definition. Create the stacks.
            for (size_t i = 0, lineEnd = line.length(); i < lineEnd; i++)
            {
                if (line[i] != ' ')
                {
                    stacks.emplace(line[i] - '0', vector<char>());
                    auto& stack = stacks[line[i] - '0'];
                    for (auto stk = tempStacksDef.rbegin(), end = tempStacksDef.rend(); stk != end; ++stk)
                    {
                        const char curr = (*stk)[i];
                        if (curr != ' ')
                            stack.push_back(curr);
                        else
                            break;
                    }
                }
            }
            break;
        }
        else
            tempStacksDef.push_back(line);
    }

    const regex commandExp(R"(^move (\d+) from (\d+) to (\d+)$)");
    while (getline(file, line))
    {
        auto match = smatch{};
        if (regex_match(line, match, commandExp))
            process(stoi(match[1]), stacks[stoi(match[2])], stacks[stoi(match[3])]);
    }

    string ret;
    ret.reserve(stacks.size() + 1);

    for (const auto& stack : stacks)
        ret.push_back(stack.second.back());

    ret.push_back('\0');

    return ret;
}

string Day5::ProcessStacks()
{
    return ::ProcessStacks(
        [](int&& cnt, vector<char>& src, vector<char>& dst)
        {
            for (int i = 0; i < cnt; i++)
            {
                dst.push_back(src.back());
                src.pop_back();
            }
        }
    );
}

string Day5::ProcessStacks2()
{
    return ::ProcessStacks(
        [](int&& cnt, vector<char>& src, vector<char>& dst)
        {
            const auto it = src.begin() + (src.size() - cnt);
            dst.insert(dst.end(), it, src.end());
            src.erase(it, src.end());
        }
    );
}

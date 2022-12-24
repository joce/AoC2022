#include "stdafx.h"

#include "Day7.h"

class DirNode;
using namespace std;

class Node
{
    const string m_name;

protected:
    const weak_ptr<DirNode> m_parent;

public:
    virtual ~Node() = default;

    Node(string name, weak_ptr<DirNode> parent) :
        m_name(std::move(name)),
        m_parent(std::move(parent))
    {}

    [[nodiscard]]
    virtual size_t Size() const = 0;

    [[nodiscard]]
    const string& GetName() const { return m_name; }

    [[nodiscard]]
    weak_ptr<DirNode> GetParent() const { return m_parent; }
};

class DirNode : public Node
{
    vector<shared_ptr<Node>> children;

public:
    DirNode(string name, weak_ptr<DirNode> parent) :
        Node(std::move(name), std::move(parent))
    {}

    DirNode(string name) :
        Node(std::move(name), std::weak_ptr<DirNode>())
    {}

    void AddChild(shared_ptr<Node>&& child)
    {
        children.push_back(std::move(child));
    }

    [[nodiscard]]
    weak_ptr<Node> GetNode(const string& name) const
    {
        for (const auto& child : children)
            if (child->GetName() == name)
                return child;

        throw exception(("No node named " + name + " found in " + GetName() + ".").c_str());
    }

    [[nodiscard]]
    const vector<shared_ptr<Node>>& GetNodes() const { return children; }

    [[nodiscard]]
    size_t Size() const override
    {
        size_t ret = 0;
        for (const auto& node : children)
            ret += node->Size();

        return ret;
    }
};

class FileNode : public Node
{
    size_t m_Size;

public:
    FileNode(string name, size_t size, weak_ptr<DirNode>& parent) :
        Node(std::move(name), std::move(parent)),
        m_Size(size)
    {}

    [[nodiscard]]
    size_t Size() const override { return m_Size; }
};

static shared_ptr<Node> BuildFileTree()
{
    auto root = make_shared<DirNode>(string("\\"));
    weak_ptr<DirNode> currNode;
    currNode = root;

    ifstream file("input-day7.txt");
    if (!file.is_open())
    {
        cerr << "Can't open file for reading";
        return root;
    }

    const regex cdRegex(R"(^\$ cd (\w+|\/|\.\.)$)");
    const regex dirRegex(R"(^dir (\w+)$)");
    const regex fileRegex(R"(^(\d+) ([\w|\.]+)$)");

    string line;
    while (getline(file, line))
    {
        auto cn = currNode.lock();
        if (!cn)
            continue;

        auto match = smatch{};
        if (regex_match(line, match, cdRegex))
        {
            const string dirName = match[1];
            if (dirName == "..")
                currNode = cn->GetParent();
            else if (dirName == "/")
                currNode = root;
            else
            {
                auto toDir = cn->GetNode(dirName).lock();
                currNode = static_pointer_cast<DirNode>(toDir);
            }
        }
        else if (regex_match(line, match, dirRegex))
            cn->AddChild(make_shared<DirNode>(match[1], currNode));
        else if (regex_match(line, match, fileRegex))
            cn->AddChild(make_shared<FileNode>(match[2], stoi(match[1].str()), currNode));
    }

    return root;
}

static void PrintTree(const weak_ptr<Node>& node, int indent)
{
    for (int i = 0; i < indent; i++)
        cout << " ";

    const auto n = node.lock();

    if (const auto d = dynamic_pointer_cast<DirNode>(n))
    {
        cout << d->GetName() << endl;
        for (auto c : d->GetNodes())
            PrintTree(c, indent + 4);
    }
    else if (const auto f = dynamic_pointer_cast<FileNode>(n))
        cout << f->GetName() << "\t" << f->Size() << endl;
    else
        throw exception("HHHHHAAAAAAARGH!");
}

static void CalcSize(const weak_ptr<Node>& node, size_t& totalSize)
{
    const auto n = node.lock();

    if (const auto d = dynamic_pointer_cast<DirNode>(n))
    {
        if (const auto size = n->Size(); size <= 100000)
            totalSize += size;

        for (const auto c : d->GetNodes())
            CalcSize(c, totalSize);
    }
}

static void FindSize(const weak_ptr<Node>& node, size_t toDelete, size_t& best)
{
    const auto n = node.lock();

    if (const auto d = dynamic_pointer_cast<DirNode>(n))
    {
        const auto size = d->Size();

        if (size < toDelete)
            return;

        if (size < best)
            best = size;

        for (const auto c : d->GetNodes())
            FindSize(c, toDelete, best);
    }
}

size_t Day7::SumOfAllDirs()
{
    const auto tree = BuildFileTree();
    //PrintTree(tree, 0);

    size_t size = 0;
    CalcSize(tree, size);

    return size;
}

size_t Day7::SizeOfDirToDelete()
{
    const auto tree = BuildFileTree();

    const auto unusedSpace = 70000000 - tree->Size();
    const auto needed = 30000000 - unusedSpace;

    auto best = SIZE_MAX;

    FindSize(tree, needed, best);

    return best;
}

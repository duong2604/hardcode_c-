#include <bits/stdc++.h>
using namespace std;

// ── Data ────────────────────────────────────────────────────────────────────
struct Graph
{
    int nodeCount, edgeCount;
    map<string, int> h;              // heuristic values
    map<string, vector<string>> adj; // adjacency list (ordered)
    string start, goal;
};

// ── I/O ─────────────────────────────────────────────────────────────────────
Graph readInput(const string &filename)
{
    Graph g;
    ifstream fin(filename);
    if (!fin)
        throw runtime_error("Cannot open " + filename);

    fin >> g.nodeCount >> g.edgeCount;
    fin.ignore();

    for (int i = 0; i < g.nodeCount; i++)
    {
        string name;
        int val;
        fin >> name >> val;
        g.h[name] = val;
    }
    fin.ignore();

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        istringstream iss(line);
        string token;
        iss >> token;

        if (token == "START")
        {
            iss >> g.start;
        }
        else if (token == "GOAL")
        {
            iss >> g.goal;
        }
        else
        {
            string nb;
            while (iss >> nb)
                g.adj[token].push_back(nb);
        }
    }
    return g;
}

// ── Algorithm ────────────────────────────────────────────────────────────────
//  OPEN list = sorted vector of (h_value, insertion_order, node_name).
//  Sorting by (h, order) gives min-h first, with FIFO tiebreak.
//  inOpen set prevents re-inserting a node already waiting in OPEN.
//  closed set prevents re-expanding an already-processed node.
void solve(const Graph &g, const string &outFile)
{
    ofstream fout(outFile);
    if (!fout)
        throw runtime_error("Cannot open " + outFile);

    using Entry = tuple<int, int, string>; // (h, insert_order, name)
    vector<Entry> open;
    set<string> inOpen, closed;
    int counter = 0;

    auto addToOpen = [&](const string &node)
    {
        if (closed.count(node) || inOpen.count(node))
            return;
        open.push_back({g.h.at(node), counter++, node});
        inOpen.insert(node);
        sort(open.begin(), open.end()); // keep ascending by (h, order)
    };

    auto openStr = [&]() -> string
    {
        string s;
        for (size_t i = 0; i < open.size(); i++)
        {
            if (i)
                s += ",";
            s += get<2>(open[i]) + to_string(get<0>(open[i]));
        }
        return s;
    };

    addToOpen(g.start);

    fout << "Phat trien TT | Trang thai ke | Danh sach L\n";

    while (!open.empty())
    {
        auto [hval, ord, current] = open.front();
        open.erase(open.begin());
        inOpen.erase(current);
        closed.insert(current);

        string nodeStr = current + to_string(g.h.at(current));

        if (current == g.goal)
        {
            fout << nodeStr << " | TTKT-DUNG\n";
            break;
        }

        // Collect neighbors (from adjacency list; empty if leaf node)
        const vector<string> &neighbors =
            g.adj.count(current) ? g.adj.at(current)
                                 : (const vector<string> &)vector<string>{};

        // Build neighbor display string, then add each to OPEN
        string nbStr;
        for (size_t i = 0; i < neighbors.size(); i++)
        {
            if (i)
                nbStr += ",";
            nbStr += neighbors[i] + to_string(g.h.at(neighbors[i]));
        }
        for (const string &nb : neighbors)
            addToOpen(nb);

        fout << nodeStr << " | " << nbStr << " | " << openStr() << "\n";
    }
}

// ── Entry point ──────────────────────────────────────────────────────────────
int main()
{
    try
    {
        Graph g = readInput("input.txt");
        solve(g, "output.txt");
        cout << "Done. Output written to output.txt\n";
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}

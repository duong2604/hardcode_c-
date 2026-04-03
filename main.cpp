#include <bits/stdc++.h>

using namespace std;

struct Graph
{
    int nodeCount, edgeCount;
    map<string, int> h;
    map<string, vector<string>> adj;
    string start, goal;
};

Graph readInput(const string &filename)
{
    ifstream fin("input.txt");
    if (!fin)
        runtime_error("cannot open" + filename);

    Graph g;

    fin >> g.nodeCount >> g.edgeCount;
    fin.ignore();

    for (int i = 0; i < g.nodeCount; i++)
    {
        string node;
        int val;
        fin >> node >> val;
        g.h[node] = val;
    }

    fin.ignore();

    string line;
    while (getline(fin, line))
    {
        if (line.empty())
        {
            continue;
        }

        istringstream iss(line);
        string token;

        iss >> token;

        if (token == "START")
        {
            g.start = token;
        }
        else if (token == "GOAL")
        {
            g.goal = token;
        }
        else
        {
            string nb;
            while (iss >> nb)
            {
                g.adj[token].push_back(nb);
            }
        }
    }

    return g;
}

int main()
{
    try
    {
        /* code */
        Graph g = readInput("input.txt");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
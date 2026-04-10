#include <bits/stdc++.h>

using namespace std;

int n, m;
map<string, vector<string>> adj;
map<string, int> h;
string start, goal;
vector<pair<string, int>> L;
map<string, string> parent;

const int W1 = 16;
const int W2 = 20;
const int W3 = 36;

void printSeparator(ofstream &fout)
{
    int tong = W1 + W2 + W3 + 13;
    string duong(tong, '-');
    cout << duong << "\n";
    fout << duong << "\n";
}

void printRowData(ofstream &fout,
                  string col1,
                  string col2,
                  string col3)
{
    stringstream ss;
    ss << "| " << left << setw(W1) << col1
       << "| " << left << setw(W2) << col2
       << "| " << left << setw(W3) << col3
       << "|";

    cout << ss.str() << "\n";
    fout << ss.str() << "\n";
}

void readInput(const string &filename)
{
    ifstream fin(filename);
    if (!fin)
    {
        throw runtime_error("cannot open" + filename);
    }
    fin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string node;
        int val;
        fin >> node >> val;
        h[node] = val;
    }
    fin.ignore();

    for (int i = 0; i < m; i++)
    {
        string x, y;
        fin >> x >> y;
        adj[x].push_back(y);
    }
    fin >> start >> goal;
    fin.close();
}

string printListL(vector<pair<string, int>> &L)
{
    string res = "";
    for (int i = 0; i < L.size(); i++)
    {
        res += L[i].first + to_string(L[i].second);
        if (i < L.size() - 1)
        {
            res += ",";
        }
    }
    return res;
}

string printAdjList(vector<string> &adj)
{
    if (adj.empty())
        return "";

    string res = "";
    for (int i = 0; i < adj.size(); i++)
    {
        res += adj[i] + to_string(h[adj[i]]);
        if (i < adj.size() - 1)
        {
            res += ",";
        }
    }

    return res;
}

void insertL(vector<pair<string, int>> &L, string u)
{

    for (int i = 0; i < L.size(); i++)
    {
        if (h[u] <= L[i].second)
        {
            L.insert(L.begin() + i, {u, h[u]});
            return;
        }
    }
    L.push_back({u, h[u]});
}

void printPath(ofstream &fout)
{
    vector<string> path;
    string node = goal;
    while (node != "")
    {
        path.push_back(node);
        node = parent[node];
    }

    reverse(path.begin(), path.end());

    string s = "";
    for (int i = 0; i < path.size(); i++)
    {
        s += path[i];
        if (i < path.size() - 1)
        {
            s += "-->";
        }
    }
    cout << "Path: " << s << endl;
    fout << "Path: " << s << endl;
}

void bestFirstSearch(ofstream &fout)
{

    printSeparator(fout);
    printRowData(fout, "Phat trien TT", "Trang thai ke", "Danh sach L");
    printSeparator(fout);

    insertL(L, start);
    parent[start] = "";

    printRowData(fout, "", "", printListL(L));
    printSeparator(fout);

    while (true)
    {
        if (L.empty())
        {
            printRowData(fout, "Not Found", "", "");
            printSeparator(fout);
            cout << "Tim kiem that bai!" << endl;
            return;
        }

        auto u = L.front();
        L.erase(L.begin());

        if (u.first == goal)
        {
            printRowData(fout, u.first + to_string(u.second), "TTKT-DUNG", "");
            printSeparator(fout);
            printPath(fout);

            return;
        }

        for (string v : adj[u.first])
        {

            if (parent.find(v) == parent.end())
            {
                parent[v] = u.first;
            }
            insertL(L, v);
        }
        printRowData(fout, u.first + to_string(u.second), printAdjList(adj[u.first]), printListL(L));
        printSeparator(fout);
    }
}

int main()
{

    try
    {
        /* code */
        ofstream fout("output.txt");
        cout << "=== BEST FIRST SEARCH ===\n\n";
        fout << "=== BEST FIRST SEARCH ===\n\n";
        readInput("input.txt");
        bestFirstSearch(fout);

        fout.close();
        cout << "\n=> Da ghi ket qua vao file output.txt\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
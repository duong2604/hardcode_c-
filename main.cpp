#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
int start, goal;

void input()
{
    cin >> n >> m;

    adj.resize(n + 1);
    visited.assign(n + 1, false);
    parent.assign(n + 1, -1);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for (int i = 1; i <= n; i++)
    {
        sort(adj[i].begin(), adj[i].end());
    }

    cin >> start >> goal;
}

bool dfs(int u)
{

    visited[u] = true;

    if (u == goal)
    {
        return true;
    }

    for (int &v : adj[u])
    {
        if (!visited[v])
        {
            parent[v] = u;
            if (dfs(v))
                return true;
        }
    }

    return false;
}

int main()
{
    input();
    dfs(start);

    vector<int> path;
    int cur = goal;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    cout << "\n\nPath from " << start << " to " << goal << ":\n";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }

    return 0;
}

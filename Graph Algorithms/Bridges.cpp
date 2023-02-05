// algo for finding bridges in UNDIRECTED graph G
// bridge : an edge, which when removed, results in the graph having greater number of connected components than before

// use MAXN, adj[MAXN], 1-indexed vertices
set<pall> bridges;      //all bridges will be stored here finally
vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
            bridges.insert({v, to}), bridges.insert({to, v});            
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(MAXN, false);
    tin.assign(MAXN, -1);
    low.assign(MAXN, -1);
    for (int i = 1; i < MAXN; ++i) {            //1 indexed vertices
        if (!visited[i])
            dfs(i);
    }
}
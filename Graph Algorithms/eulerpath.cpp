ll MAXN = 1e5 + 1;
vector<vector<int>> adj(MAXN);
vector<int> vis(MAXN), path;

//finally, the "path" vector will contain the euler path
void dfs(int u)
{
    vis[u] = 1;
    path.pb(u);
    for(auto v : adj[u])
        if(!vis[v])
            dfs(v), path.pb(u);
}
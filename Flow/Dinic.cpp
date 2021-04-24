struct Dinic {
    const int INF = 1e18;
    struct edge {
        int u, v, cap, flow;
        edge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0) {}
    };
    vector<edge> edges;
    vector<vector<int>> adj;
    vector<int> level, num;
    queue<int> q;
    int n, s, t, cnt = 0; //To maintain the id of edges

    void init(int nn, int ss, int tt) {
        n = nn + 1, s = ss, t = tt;
        adj.resize(n);
        level.resize(n);
        num.resize(n);
    }

    void add_edge(int u, int v, int cap) {
        edges.push_back({u, v, cap});
        edges.push_back({v, u, 0});
        adj[u].push_back(cnt++);
        adj[v].push_back(cnt++);
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto eid : adj[u]) {
                edge e = edges[eid];

                //We only pass the edge that has positive capacity
                if (e.cap - e.flow <= 0 || level[e.v] != -1)
                    continue;

                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }

        //If we cannot reach t, then there is no Augmenting Path
        return level[t] != -1;
    }

    int dfs(int u, int now) {
        if (now == 0)
            return 0;

        if (u == t)
            return now;

        for (; num[u] < adj[u].size(); num[u]++) {
            edge e = edges[adj[u][num[u]]];

            if (level[e.v] != level[u] + 1 || e.cap - e.flow <= 0)
                continue;

            int f = dfs(e.v, min(now, e.cap - e.flow));

            if (!f)
                continue;

            edges[adj[u][num[u]]].flow += f;
            edges[adj[u][num[u]] ^ 1].flow -= f;
            return f;
        }

        return 0;
    }

    int get_flow() {
        int res = 0, now;

        while (true) {
            if (!bfs())
                break;

            fill(num.begin(), num.end(), 0);

            while (now = dfs(s, INF)) {
                res += now;
            }
        }

        return res;
    }
} flow;

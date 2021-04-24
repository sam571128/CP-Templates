struct MCMF {
    static const int N = 500, INF = 1e18;
    int n, s, t;
    struct Edge {
        int v, cap, f, cost;
        Edge(int v, int cap, int f, int cost): v(v), cap(cap), f(f), cost(cost) {}
    };
    vector<Edge> edges;
    vector<vector<int>> adj;

    void init(int n_, int s_, int t_) {
        n = n_ + 1, s = s_, t = t_;
        adj.resize(n);
    }

    void add_edge(int u, int v, int cap, int cost) {
        adj[u].push_back(edges.size());
        edges.push_back({v, cap, 0, cost});
        adj[v].push_back(edges.size());
        edges.push_back({u, 0, 0, -cost});
    }

    int dis[N], p[N], pe[N], inque[N];

    void SPFA() {
        for (int i = 0; i <= n; i++)
            dis[i] = INF, p[i] = -1, pe[i] = -1, inque[i] = 0;

        dis[s] = 0;
        queue<int> q;
        q.push(s);
        inque[s] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inque[u] = false;

            for (auto x : adj[u]) {
                auto e = edges[x];

                if (e.cap > 0 && dis[e.v] > dis[u] + e.cost) {
                    dis[e.v] = dis[u] + e.cost;
                    p[e.v] = u;
                    pe[e.v] = x;

                    if (!inque[e.v])
                        inque[e.v] = true, q.push(e.v);
                }
            }
        }
    }

    pair<int, int> min_cost() {
        int flow = 0, cost = 0;

        while (true) {
            SPFA();

            if (dis[t] == INF)
                break;

            int min_flow = INF;

            int now = t;

            while (now != s) {
                min_flow = min(min_flow, edges[pe[now]].cap);
                now = p[now];
            };

            flow += min_flow, cost += min_flow * dis[t];

            now = t;

            while (now != s) {
                edges[pe[now]].cap -= min_flow;
                edges[pe[now] ^ 1].cap += min_flow;
                now = p[now];
            }
        }

        return {flow, cost};
    }
} flow;


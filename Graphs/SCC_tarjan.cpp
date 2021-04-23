const int N = 1e6+5;
vector<int> adj[N];
int dfn[N], low[N], inst[N], scc[N], sccid = 0, cnt = 0;
stack<int> st;

void dfs(int u){
	dfn[u] = low[u] = ++cnt;
	st.push(u);
	inst[u] = 1;
	for(auto v : adj[u]){
		if(!dfn[v]){
			dfs(v);
			low[u] = min(low[u],low[v]);
		}else if(inst[v]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		int x;
		do{
			x = st.top();
			st.pop();
			scc[x] = sccid;
			inst[x] = 0;
		}while(x!=u);
		sccid++;
	}
}
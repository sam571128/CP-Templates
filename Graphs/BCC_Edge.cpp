void dfs(int u, int p){
	dfn[u] = low[u] = ++t;
	st.emplace(u);
	for(int v : adj[u]){
		if(v == p) continue;
		if(!dfn[v]){
			dfs(v,u);
			low[u] = min(low[u],low[v]);
		}
		low[u] = min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		bccid++;
		int tmp;
		do{
			tmp = st.top(); st.pop();
			bcc[tmp] = bccid;
            sz[bccid]++;
		}while(tmp!=u);
	}
}

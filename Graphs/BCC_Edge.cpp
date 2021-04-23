void dfs(int u, int a){
	d[u] = l[u] = t++;
	st.emplace(u);
	for(int v : adj[u]){
		if(v == a) continue;
		if(!d[v]){
			dfs(v,u);
			//if(d[u] < l[v]) bridges.emplace_back(u,v);
			l[u] = min(l[u],l[v]);
		}
		l[u] = min(l[u],d[v]);
	}
	if(l[u]==d[u]){
		bccid++;
		int tmp;
		do{
			tmp = st.top(); st.pop();
			bcc[tmp] = bccid;
		}while(tmp!=u);
	}
}
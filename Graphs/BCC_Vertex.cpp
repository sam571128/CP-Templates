const int N = 2e5+5;
vector<int> adj[N], adj2[N], bccids[N];

int low[N], dfn[N], bccid[N], bcccnt, w[N], cutbcc[N], cutid[N];
int cut[N], inst[N], t, tt;
 
void dfs(int u, int par){
	low[u] = dfn[u] = ++t;
	int cnt = 0;
	st.push(u);
	for(auto v : adj[u]){
		if(v == par) continue;
		if(!dfn[v]){
			dfs(v,u); cnt++;
			low[u] = min(low[u],low[v]);
			if(low[v] >= dfn[u]){
				cut[u] = 1;
				++bcccnt;
				int x;
				do{
					if(st.empty()) break;
					x = st.top(); st.pop();
					//if(bccid[x]) bcc[bccid[x]].erase(bcc[bccid[x]].find(w[x]));
					bccids[x].push_back(bcccnt);
					bccid[x] = bcccnt;
				}while(x!=v);
				//if(bccid[u]) bcc[bccid[u]].erase(bcc[bccid[u]].find(w[u]));
				bccids[u].push_back(bcccnt);
				bccid[u] = bcccnt;
			}
		}else if(dfn[v] < dfn[u]){
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(par==-1&&cnt < 2) cut[u] = 0;
}
priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({0,s});
dis[s] = 0;
inq[s] = 1;
while(!pq.empty()){
	auto [ww,u] = pq.top(); pq.pop();
	inq[u] = 0;
	for(auto [v,w] : adj[u]){
		if(dis[v] > dis[u]+ w){
			dis[v] = dis[u]+w;
			if(!inq[v]){
				pq.push({dis[v],v});
				inq[v] = 1;
			}
		}
	}
}
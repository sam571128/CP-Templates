struct SegT{
	const int MAXN = 1e5+5;
	int tr[MAXN*4], arr[MAXN], tag[MAXN*4]; 

	int combine(int a, int b){
	    return max(a,b);
	}

	void build(int idx, int l, int r){
	    if(l==r){
	        tr[idx] = arr[l]; 
	    }else{
	        int m = (l+r)/2;
	        build(idx*2,l,m); 
	        build(idx*2+1,m+1,r); 
	        tr[idx] = combine(tr[idx*2],tr[idx*2+1]); 
	    }
	}

	void push(int idx){
	    if(tag[idx]){
	        tr[idx<<1] = max(tr[idx<<1], tag[idx]);
	        tr[idx<<1|1] = max(tr[idx<<1|1], tag[idx]);
	        tag[idx<<1] = max(tag[idx<<1], tag[idx]);
	        tag[idx<<1|1] = max(tag[idx<<1|1], tag[idx]);
	        tag[idx] = 0;
	    }
	}

	void modify(int ql, int qr, int val, int idx, int l, int r){
	    if(l!=r) push(idx); //當節點並非葉節點時，下推標記
	    if(ql <= l && r <= qr){
	        tr[idx] = max(tr[idx],val);
	        tag[idx] = max(tag[idx],val);
	        return;
	    }
	    int m = (l+r)/2;
	    if(qr > m) modify(ql, qr, val, idx*2+1, m+1, r);
	    if(ql <= m) modify(ql, qr, val, idx*2, l, m);
	    tr[idx] = combine(tr[idx<<1],tr[idx<<1|1]);
	}

	int query(int ql, int qr, int idx, int l, int r){
	    if(l!=r) push(idx); 
	    if(ql <= l && r <= qr){
	        return tr[idx];
	    }
	    int m = (l+r)/2;
	    if(ql > m){
	        return query(ql, qr, idx*2+1, m+1, r);
	    }
	    if(qr <= m){
	        return query(ql, qr, idx*2, l, m);
	    }
	    return combine(query(ql, qr, idx*2, l, m), query(ql, qr, idx*2+1, m+1, r));
	}
}
struct SegT{
	int d[4*N];
	int lazy_tag[4*N];
	int combine(int a, int b){
		return a+b;
	}
	void build(int a[], int ind = 1, int l = 0, int r = N-1){
		if(l==r){
			d[ind]=a[l];
		}else{
			int mid = (l+r)/2;
			build(a,ind<<1,l,mid);
			build(a,ind<<1|1,mid+1,r);
			d[ind] = combine(d[ind<<1],d[ind<<1|1]);
		}
	}
	void modify(int pos, int val, int ind = 1, int l = 0, int r = N-1){
		if(l==r){
			d[ind] = val;
		}else{
			int mid = (l+r)/2;
			if(pos<=mid) modify(pos,val,ind<<1,l,mid);
			else modify(pos,val,ind<<1|1,mid+1,r);
			d[ind] = combine(d[ind<<1],d[ind<<1|1]);
		}
	}
	void range_modify(int ml, int mr, int val, int ind = 1, int l = 0, int r = N-1){
		if(ml>r||mr<l) return;
		if(ml<=l&&mr>=r){
			lazy_tag[ind] += val;
			d[ind] += (r-l+1)*val;
			return;
		}
		int mid = (l+r)/2;
		range_modify(ml,mr,val,ind<<1,l,mid);
		range_modify(ml,mr,val,ind<<1|1,mid+1,r);
		d[ind] = combine(d[ind<<1],d[ind<<1|1]);
	}
	void apply(int ind, int val, int l, int r){
		if(ind>=0&&ind<4*N){
			d[ind] += (r-l+1)*val;
			lazy_tag[ind] += val;
		}
	}
	int query(int ql, int qr, int ind = 1, int l = 0, int r = N-1){
		if(ql>r||qr<l) return 0;
		if(ql<=l&&qr>=r) return d[ind];
		int mid = (l+r)/2;
		if(lazy_tag[ind]){
			apply(ind<<1, lazy_tag[ind], l, mid);
			apply(ind<<1|1, lazy_tag[ind], mid+1, r);
			d[ind] = combine(d[ind<<1],d[ind<<1|1]);
			lazy_tag[ind] = 0;
		}
		return combine(query(ql,qr,ind<<1,l,mid),query(ql,qr,ind<<1|1,mid+1,r));
	}
};
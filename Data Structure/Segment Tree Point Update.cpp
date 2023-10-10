int tr[MAXN<<2], arr[MAXN];

int combine(int a, int b){
    return min(a,b);  // this can be any associative operation
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

void update(int pos, int val, int idx, int l, int r){
    if(l==r){
        tr[idx] = val;
        return;
    }
    int m = (l+r)/2;
    if(pos <= m) update(pos, val, idx*2, l, m);
    else update(pos, val, idx*2+1, m+1, r);
    tr[idx] = combine(tr[idx*2],tr[idx*2+1]);
}

int query(int ql, int qr, int idx, int l, int r){
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

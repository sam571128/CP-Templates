struct Treap{
	Treap *l, *r;
	int val, size, sum;
	Treap(int v): l(nullptr), r(nullptr), val(v), size(1), sum(v){}
	void pull();
};
 
void Treap::pull(){
	size = 1, sum = val;
	if(l!=nullptr) size += l->size, sum += l->sum;
	if(r!=nullptr) size += r->size, sum += r->sum;
}
 
int sz(Treap *t){
	return (t==nullptr ? 0 : t->size);
}
 
Treap *merge(Treap *a, Treap *b){
	if(a==nullptr) return b;
	if(b==nullptr) return a;
	if(rand()%(a->size+b->size) <a->size){
		a->r = merge(a->r,b);
		a->pull();
		return a;
	}else{
		b->l = merge(a,b->l);
		b->pull();
		return b;
	}
}
 
void split(Treap *t, Treap *&a, Treap *&b, int k){
	if(t==nullptr){
		a = b = nullptr;
		return;
	}
	if(sz(t->l) < k){
		a = t;
		split(t->r,a->r,b,k-sz(t->l)-1);
		a->pull();
	}else{
		b = t;
		split(t->l,a,b->l,k);
		b->pull();
	}
}
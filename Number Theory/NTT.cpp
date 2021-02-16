const int N = 5e5+5, MOD = 998244353, G = 3;

int fastpow(int n, int p){
	int res = 1;
	while(p){
		if(p&1) res = res * n % MOD;
		n = n * n % MOD;
		p >>= 1;
	}
	return res;
}

struct NTT{
	int n, inv, rev[N];
	int omega[N], iomega[N];
	void init(int n_){
		n = n_;
		inv = fastpow(n,MOD-2);
		int k = __lg(n);
		int x = fastpow(G, (MOD-1)/n);
		omega[0] = 1;
		for(int i = 1;i < n;i++)
			omega[i] = omega[i-1] * x % MOD;
		iomega[n-1] = fastpow(omega[n-1],MOD-2);
		for(int i = n-2; i >= 0; i--)
			iomega[i] = iomega[i+1] * x % MOD;
		for(int i = 0;i < n;i++){
			int t = 0;
			for(int j = 0;j < k;j++)
				if(i&(1<<j)) t |= (1<<k-j-1);
			rev[i] = t;
		}
	}
	void transform(vector<int> &a, int *xomega){
		for(int i = 0;i < n;i++)
			if(i < rev[i]) swap(a[i],a[rev[i]]);
		for(int len = 2;len <= n;len <<= 1){
			int mid = len>>1;
			int r = n/len;
			for(int j = 0;j < n;j += len){
				for(int i = 0;i < mid;i++){
					int tmp = xomega[r*i] * a[j+mid+i] % MOD;
					a[j+mid+i] = (a[j+i] - tmp + MOD) % MOD;
					a[j+i] = (a[j+i]+tmp)%MOD;
				}
			}
		}
	}
	void dft(vector<int> &a){transform(a,omega);}
	void idft(vector<int> &a){transform(a,iomega); for(int i = 0;i < n;i++) a[i] = a[i]*inv %MOD;}
} NTT;
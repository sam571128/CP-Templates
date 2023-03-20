const int MOD = 998244353, G = 3;
int fastpow(int n, int p){
    int res = 1;
    while(p){
        if(p&1) res = res * n % MOD;
        n = n * n % MOD;
        p >>= 1;
    }
    return res;
}

int inv(int x){
    return fastpow(x,MOD-2);
}

struct polynomial{
    void fft(vector<int> &a, bool invert){
        int n = a.size();

        for(int i = 1, j = 0; i < n; i++){
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            int k = len>>1;
            int wn = fastpow(G,(MOD-1)/len);
            for(int i = 0; i < n; i += len){
                int w = 1;
                for(int j = 0; j < k; j++){
                    int u = a[i+j], v = a[i+j+k]*w % MOD;
                    a[i+j] = (u+v)%MOD;
                    a[i+j+k] = (u-v+MOD)%MOD;
                    w *= wn; w %= MOD;
                }
            }
        }

        if(invert){
            reverse(a.begin()+1,a.begin()+n);
            int n_1 = inv(n);
            for(auto &x : a){
                x = x * n_1 % MOD;
            }
        }
    }
    
    vector<int> multiply(vector<int> const &a, vector<int> const &b){
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while(n < a.size() + b.size()){
            n <<= 1;
        }
        fa.resize(n);
        fb.resize(n);

        fft(fa,false);
        fft(fb,false);

        for(int i = 0; i < n; i++){
            fa[i] *= fb[i], fa[i] %= MOD;
        }
        
        fft(fa,true);

        vector<int> result(n);
        for(int i = 0; i < n; i++){
            result[i] = fa[i];
        }
        return result;
    }
} poly;

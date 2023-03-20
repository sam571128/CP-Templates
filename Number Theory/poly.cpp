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
        while(n < (int)a.size() + (int)b.size()){
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
        result.resize(a.size()+b.size()-1);
        return result;
    }

    vector<int> deriv(vector<int> const &a){
        int n = a.size();
        vector<int> res(a.begin(),a.end());
        for(int i = 0; i < n-1; i++){
            res[i] = a[i+1] * (i+1) % MOD;
        }
        res[n-1] = 0;
        return res;
    }

    vector<int> integ(vector<int> const &a){
        int n = a.size()+1;
        vector<int> res(a.begin(),a.end());
        res.resize(n);
        for(int i = 1; i < n; i++){
            res[i] = a[i-1] * inv(i) % MOD;
        }
        res[0] = 0;
        return res;
    }

    vector<int> inverse(vector<int> const &a){
        //Sieveking-Kung Algorithm
        assert(a[0] != 0);
        int n = 1;
        while(n < (int)a.size())
            n <<= 1;

        vector<int> b; b.push_back(inv(a[0]));
        for(int len = 2; len <= n; len <<= 1){
            vector<int> tmp(a.begin(),a.begin()+len);
            vector<int> nxt = multiply(tmp,b);
            for(int i = 0; i < len; i++){
                nxt[i] = (-nxt[i]+MOD)%MOD;
            }
            nxt[0] = (2+nxt[0])%MOD;
            nxt = multiply(b,nxt);
            nxt.resize(len);
            b = nxt;
        }

        b.resize(a.size());
        return b;
    }

    vector<int> ln(vector<int> const &a){
        vector<int> v1 = deriv(a);
        vector<int> v2 = inverse(a);
        v1 = multiply(v1,v2);
        v1.resize(a.size());
        v1 = integ(v1);
        v1.resize(a.size());
        return v1;
    }

    vector<int> exp(vector<int> const &a){
        assert(a[0] == 0);
        int n = 1;
        while(n < (int)a.size())
            n <<= 1;

        vector<int> b; b.push_back(1);
        for(int len = 2; len <= n; len <<= 1){
            vector<int> nxt = ln(b);
            nxt.resize(len);
            for(int i = 0; i < len; i++){
                nxt[i] = (a[i]-nxt[i]+2*MOD) % MOD;
            }
            nxt[0] = (1+nxt[0])%MOD;
            nxt = multiply(b,nxt);
            nxt.resize(len*2);
            b = nxt;
        }
        b.resize(a.size());
        return b;
    }

    vector<int> sqrt(vector<int> const &a){
        assert(a[0] == 1);
        int n = 1;
        while(n < (int)a.size())
            n <<= 1;
        
        int inv2 = inv(2);
        vector<int> b; b.push_back(1);
        
        for(int len = 2; len <= n; len <<= 1){
            vector<int> nxt = inverse(b);
            vector<int> tmp(a.begin(),a.begin()+len);
            nxt = multiply(tmp,nxt); nxt.resize(len*2);
            b.resize(len);
            for(int i = 0; i < len*2; i++)
                nxt[i] = nxt[i] * inv2 % MOD;
            
            for(int i = 0; i < len; i++)
                nxt[i] = (nxt[i] + inv2 * b[i] % MOD) % MOD;

            b = nxt;
        }
        b.resize(a.size());
        return b;
    }

    vector<int> pow(vector<int> const &a, int k){
        //Find the first term of a which is not zero
        int n = a.size(), tmp = 0, idx = -1;
        for(int i = 0; i < n; i++){
            if(a[i]){
                tmp = a[i];
                idx = i;
                break;
            }
        }

        if(idx == -1){
            if(k==0){
                vector<int> v(n,0);
                v[0] = 1;
                return v;
            }else{
                return a;
            }
        }

        if(idx != 0 && k > n){
            return vector<int>(n,0);
        }

        int invt = inv(tmp);

        vector<int> t(a.begin()+idx,a.end());
        for(int i = 0; i < (int)t.size(); i++){
            t[i] *= invt, t[i] %= MOD;
        }

        t = ln(t);

        for(int i = 0; i < (int)t.size(); i++){
            t[i] *= (k%MOD), t[i] %= MOD;
        }

        t = exp(t);

        vector<int> res(n); int powa = fastpow(tmp,k%(MOD-1));
        for(int i = 0; i < (int)t.size(); i++){
            if(i+(__int128) k*idx < n){
                res[i+k*idx] = t[i] * powa % MOD;
            }
        }
        
        return res;
    }
} poly;

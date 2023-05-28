const int N = 2e5+5;
struct Splay{
    int rt, num, fa[N], ch[N][2], val[N], cnt[N], sz[N];

    void pull(int x){
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
    }

    bool isright(int x){
        return x == ch[fa[x]][1];
    }

    void clear(int x){
        ch[x][0] = ch[x][1] = fa[x] = val[x] = cnt[x] = sz[x] = 0;
    }

    void rotate(int x){
        int y = fa[x], z = fa[y], check = isright(x);
        ch[y][check] = ch[x][check^1];
        if(ch[x][check^1]) fa[ch[x][check^1]] = y; //if x has right child, set its parent to y
        ch[x][check^1] = y;
        fa[x] = z;
        fa[y] = x;
        if(z) ch[z][y == ch[z][1]] = x;
        pull(y);
        pull(x);
    }

    void splay(int x){
        for(int f = fa[x]; f = fa[x], f; rotate(x)){
            if(fa[f]) rotate(isright(x) == isright(f) ? f : x);
        }
        rt = x;
    }

    void insert(int k){
        if(!rt){
            val[++num] = k;
            cnt[num]++;
            rt = num;
            pull(rt);
            return;
        }

        int curr = rt, f = 0;
        while(true){
            if(val[curr] == k){
               cnt[curr]++;
               pull(f);
               pull(curr);
               splay(curr);
               return;
            }

            f = curr;
            curr = ch[curr][val[curr] < k];

            if(!curr){
                val[++num] = k;
                cnt[num]++;
                fa[num] = f;
                ch[f][val[f] < k] = num;
                pull(num);
                pull(f);
                splay(num);
                return;
            }
        }
    }

    int rk(int k){
        int res = 0, curr = rt;
        while(true){
            if(k < val[curr]){
                curr = ch[curr][0];
            } else {
                res += sz[ch[curr][0]];
                if(val[curr] == k){
                    splay(curr);
                    return res + 1;
                }
                res += cnt[curr];
                curr = ch[curr][1];
            }
        }
    }

    int kth(int k){
        int curr = rt;
        while(true){
            if(ch[curr][0] && k <= sz[ch[curr][0]]){
                curr = ch[curr][0];
            }else{
                k -= sz[ch[curr][0]] + cnt[curr];
                if(k <= 0){
                    splay(curr);
                    return val[curr];
                }
                curr = ch[curr][1];
            }
        }
    }

    int predecessor() {
        //return predecessor of the root
        int curr = ch[rt][0];
        if (!curr) return curr;
        while (ch[curr][1]) curr = ch[curr][1];
        splay(curr);
        return curr;
    }

    int successor(){
        //return successor of the root
        int curr = ch[rt][1];
        if(!curr) return curr;
        while (ch[curr][0]) curr = ch[curr][0];
        splay(curr);
        return curr;
    }


    void del(int k){
        rk(k);
        if(cnt[rt] > 1){
            cnt[rt]--;
            pull(rt);
            return;
        }

        if(!ch[rt][0] && !ch[rt][1]){
            clear(rt);
            rt = 0;
            return;
        }

        if(!ch[rt][0]){
            int curr = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(curr);
            return;
        }

        if(!ch[rt][1]){
            int curr = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(curr);
            return;
        }

        int curr = rt, x = predecessor();
        fa[ch[curr][1]] = x;
        ch[x][1] = ch[curr][1];
        clear(curr);
        pull(rt);
    }
};

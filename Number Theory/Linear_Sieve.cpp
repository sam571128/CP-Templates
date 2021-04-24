const int N = 1e5+5;
int k, lpf[N];
 
vector<int> primes;
void init(){
    fill(lpf,lpf+N,1);
    for(int i = 2;i < N;i++){
        if(lpf[i]==1){
            lpf[i] = i;
            primes.push_back(i);
        }
        for(int x : primes){
            if(x*i > N) break;
            lpf[x*i]=x;
            if(x==lpf[i]) break;
        }
    }
}

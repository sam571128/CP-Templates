const int N = 1e6 + 5;
int f[N];

void build_failure(string s) {
    int p = f[0] = -1;

    for (int i = 1; i < s.size(); i++) {
        while (p != -1 && s[p + 1] != s[i])
            p = f[p];

        if (s[p + 1] == s[i])
            p++;

        f[i] = p;
    }
}

int KMP(string s, string t) {
    int cnt = 0;
    int p = -1;

    for (int i = 0; i < t.size(); i++) {
        while (p != -1 && s[p + 1] != t[i])
            p = f[p];

        if (s[p + 1] == t[i])
            p++;

        if (p + 1 == s.size()) {
            cnt++;
        }
    }

    return cnt;
}

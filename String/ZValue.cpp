vector<int> z(const string& s)
{
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        z[i] = max(min(z[i-l],r-i),0);
        while(i+z[i] < n && s[z[i]]==s[i+z[i]])
            l = i, r = i+z[i], z[i]++;
    }
    return z;
}

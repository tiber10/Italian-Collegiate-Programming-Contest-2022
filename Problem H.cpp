#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <random>
 
using namespace std;

typedef long long ll;

const int maxn = 2e5 + 7;

ll prefix[maxn];

ll count(vector<ll>& s, ll bound) {
    ll cnt = 0;
    int n = s.size();
    for (int i = 0; i < n; i++){
        if (s[i] >= bound)
            continue;
        ll l = 1;
        ll r = n - i + 1;
        while (l + 1 < r){
            int m = (l + r) / 2;
            if (prefix[i + m] - prefix[i] >= bound)
                r = m;
            else
                l = m;
        }
        cnt += l;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> s(n);
    for (ll& x : s)
        cin >> x;
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + s[i];
    ll l = 0;
    ll r = 1e18;
    while (l + 1 < r) {
        ll m = (l + r) / 2;
        if (count(s, m) < k)
            l = m;
        else
            r = m;
    }
    ll x = l;
    ll kek = k - count(s, l);
    for (int i = 0; i < n; i++){
        if (s[i] > x)
            continue;
        int l = 1;
        int r = n - i + 1;
        while (l + 1 < r){
            int m = (l + r) / 2;
            if (prefix[i + m] - prefix[i] > x)
                r = m;
            else
                l = m;
        }
        if (prefix[i + l] - prefix[i] == x){
            if (kek == 1) {
                cout << i << ' ' << i + l - 1 << endl;
                return 0;
            }
            else
                kek--;
        }
    }
    return 0;       
}

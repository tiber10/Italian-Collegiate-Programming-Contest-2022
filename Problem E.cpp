#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <random>
 
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, l, L;
    cin >> n >> l >> L;
    vector<pair<ll, int>> s;
    for (int i = 0; i < n; i++){
        ll x;
        cin >> x;
        s.push_back({max(x - l, 0LL), 1});
        s.push_back({min(x + l + 1, L + 1), 0});
    }
    sort(s.begin(), s.end());
    if (s[0].first > 0 || s.back().first <= L){
        cout << 0 << endl;
        return 0;
    }
    int cnt = 0;
    int mini = n;
    for (int i = 0; i < s.size(); i++) {
        if (!s[i].second){
            cnt--;
            if (s[i].first < L + 1)
                mini = min(mini, cnt);
        } else {
            cnt++;
            if (i + 1 == s.size() || s[i + 1].first != s[i].first)
                mini = min(mini, cnt);
        }
    }
    cout << mini << endl;
    return 0;       
}


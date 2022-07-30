#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <random>
#include <numeric>
#include <set>

#define prev asldknad
#define rank asdaskasd
 
using namespace std;

typedef long long ll;

const int maxk = 25;

int cnt[maxk], xor_all[maxk];

int get_ans(){
    int res = 0;
    for (int i = 0; i < maxk; i++) {
        if (cnt[i] > 0) {
            if (xor_all[i])
                res = max(res, cnt[i]);
            res = max(res, cnt[i] - 1);
        }
    }
    return res;
}

void add(int val, int d){
    int v = val;
    for (int i = 0; i < maxk; i++){
        int x = val & 1;
        cnt[i] += x * d;
        if (x)
            xor_all[i] ^= v;
        val >>= 1;
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> s(n);
    for (int& x : s) {
        cin >> x;
        add(x, 1);
    }
    cout << get_ans() << '\n';
    for (int i = 0; i < q; i++){
        int pos, val;
        cin >> pos >> val;
        add(s[pos - 1], -1);
        s[pos - 1] = val;
        add(s[pos - 1], 1);
        cout << get_ans() << '\n';
    }
    return 0;
}

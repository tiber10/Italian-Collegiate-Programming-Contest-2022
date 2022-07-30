#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <random>
#include <cassert>
 
using namespace std;

typedef long long ll;

const int maxn = 25e4 + 7;

vector<int> s[maxn];
int parent[maxn], cnt[maxn], color[maxn], tin[maxn];

vector<int> euler;

const int maxb = (1 << 18);
int tree[maxb * 2 - 1];

int get_sum(int v, int vl, int vr, int l, int r){
    if (vl >= r || vr <= l)
        return 0;
    if (vl >= l && vr <= r)
        return tree[v];
    int vm = (vl + vr) / 2;
    return get_sum(v * 2 + 1, vl, vm, l, r) + get_sum(v * 2 + 2, vm, vr, l, r);
}

void update(int v, int vl, int vr, int x){
    if (vl > x || vr <= x)
        return;
    if (vl + 1 == vr){
        tree[v] ^= 1;
        return;
    }
    int vm = (vl + vr) / 2;
    update(v * 2 + 1, vl, vm, x);
    update(v * 2 + 2, vm, vr, x);
    tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
}

void dfs_cnt(int v){
    cnt[v] = 1;
    color[v] = 1;
    tin[v] = euler.size();
    euler.push_back(v);
    for (int u : s[v]){
        if (!color[u]){
            parent[u] = v;
            dfs_cnt(u);
            euler.push_back(v);
            cnt[v] += cnt[u];
        }
    }
}

vector<int> order;
int id[maxn], id_prev[maxn];

void dfs_order(int v){
    id[v] = order.size();
    order.push_back(v);
    int sonv = -1;
    for (int u : s[v]){
        if (parent[u] == v && (sonv == -1 || cnt[u] > cnt[sonv]))
            sonv = u;
    }
    if (sonv != -1){
        id_prev[sonv] = id_prev[v];
        dfs_order(sonv);
    }
    for (int u : s[v]){
        if (parent[u] == v && u != sonv){
            id_prev[u] = u;
            dfs_order(u);
        }
    }
}

const int maxk = 19;
int power[maxn * 2], sparse[maxk][maxn * 2];

void build(){
    parent[0] = -1;
    dfs_cnt(0);
    dfs_order(0);
    for (int i = 0; i < euler.size(); i++)
        sparse[0][i] = euler[i];
    for (int i = 0; i < maxk - 1; i++){
        for (int j = 0; j < euler.size(); j++){
            sparse[i + 1][j] = sparse[i][j];
            if ((1 << i) + j < euler.size() && tin[sparse[i][j]] > tin[sparse[i][(1 << i) + j]])
                sparse[i + 1][j] = sparse[i][(1 << i) + j];
        }
    }
    for (int i = 2; i <= euler.size(); i++){
        power[i] = power[i - 1];
        if (!((i - 1) & i))
            power[i]++;
    }
}

int get_lca(int v, int u){
    if (tin[v] > tin[u])
        swap(v, u);
    int k = power[tin[u] - tin[v] + 1];
    int p1 = sparse[k][tin[v]];
    int p2 = sparse[k][tin[u] - (1 << k) + 1];
    return tin[p1] < tin[p2] ? p1 : p2;
}

int cntt(int v){
    int summa = 0;
    while (v != -1){
        summa += get_sum(0, 0, maxb, id[id_prev[v]], id[v] + 1);
        v = parent[id_prev[v]];
    }
    return summa;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++){
        int x, y;
        cin >> x >> y;
        s[x - 1].push_back(y - 1);
        s[y - 1].push_back(x - 1);
    }
    build();
    int summa = 0;
    for (int i = 0; i < q; i++){
        int t, x, y;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 1){
            assert(parent[x] == y || parent[y] == x);
            if (parent[x] == y)
                swap(x, y);
            update(0, 0, maxb, id[y]);
        } else {
            x = (x + summa) % n;
            y = (y + summa) % n;
            int cnt_closed = cntt(x) + cntt(y) - 2 * cntt(get_lca(x, y));
            int res = (cnt_closed == 0 ? cnt_closed : 0);
            summa += res;
            cout << res << '\n';
        }
    }
    return 0;       
}


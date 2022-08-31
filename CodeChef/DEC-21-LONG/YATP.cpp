#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<pl> vpl;
typedef vector<ld> vld;
typedef pair<ld, ld> pld;
typedef vector<pi> vpi;

//typedef tree<ll, null_type, less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
template<typename T>
ostream &operator<<(ostream &os, vector<T> &a) {
    os << "[";
    for (int i = 0; i < ll(a.size()); i++) { os << a[i] << ((i != ll(a.size() - 1) ? " " : "")); }
    os << "]\n";
    return os;
}

#define all(x) x.begin(),x.end()
#define YES out("YES")
#define NO out("NO")
#define out(x){cout << x << "\n"; return;}
#define GLHF ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL)
#define print(x){for(auto ait:x) cout << ait << " "; cout << "\n";}
#define pb push_back
#define umap unordered_map

template<typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &os, pair<T1, T2> &p) {
    os << "" << p.first << " " << p.second << "";
    return os;
}

void usaco(string taskname) {
    string fin = taskname + ".in";
    string fout = taskname + ".out";
    const char *FIN = fin.c_str();
    const char *FOUT = fout.c_str();
    freopen(FIN, "r", stdin);
    freopen(FOUT, "w", stdout);
}

template<typename T>
void read(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n; i++)
        cin >> v[i];
}

template<typename T>
vector<T> UNQ(vector<T> a) {
    vector<T> ans;
    for (T t: a)
        if (ans.empty() || t != ans.back())
            ans.push_back(t);
    return ans;
}

void solve();

int main() {
    GLHF;
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
const int maxn=1e5+1;
int par[maxn];
umap<ll,ll> queries[maxn];
vl ans;
map<pl,ll>W;


int get(int x){return par[x]=(x==par[x]?x:get(par[x]));}
void unite(int u,int v){
    ll w=W[{u,v}];
    u=get(u),v=get(v);
    if(u==v)
        return;

    if(queries[u].size()<queries[v].size())
        swap(queries[u],queries[v]);

    for(auto it:queries[v]){
        ans[it.first]+=w*queries[u][it.first]*queries[v][it.first];
        queries[u][it.first]+=it.second;
    }

    par[v]=u;
}
void solve() {
    int n,q;
    cin >> n >> q;
    vvl E;
    ans.clear();
    W.clear();
    for(int i=1; i<=n; i++)
        queries[i].clear();

    for(int i=2; i<=n; i++){
        ll x;
        cin >> x;
        E.pb({-1,i,x});
    }
    for(int i=0; i<n-1; i++) {
        cin >> E[i][0];
        ll u=E[i][1],v=E[i][2],w=E[i][0];
        W[{u,v}]=W[{v,u}]=w;
    }
    sort(all(E));
    ans.resize(q+1);

    for(int i=0; i<q; i++){
        ll k;
        cin >> k;
        for(int j=0; j<k; j++){
            ll x;
            cin >> x;
            queries[x][i+1]++;
        }
    }

    for(int i=1; i<=n; i++)
        par[i]=i;
    for(int i=0; i<n-1; i++){
        ll u=E[i][1],v=E[i][2];
        unite(u,v);
    }
    for(int i=1; i<ans.size(); i++)
        cout << ans[i] << " ";
    out("")
}

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
    //cin >> t;
    while (t--)
        solve();
}

vvi up,g;
vi dep,d;
void dfs(int src,int par){
    if(par!=-1)
        dep[src]=dep[par]+1;
    up[src][0]=par;
    for(int nbr:g[src])
        if(nbr!=par)
            dfs(nbr,src);
}
void dfs2(int src,int par){
    for(int nbr:g[src])
        if(nbr!=par)
            dfs2(nbr,src),d[src]+=d[nbr];
}
int lg=20;
int lca(int u,int v){
    if(u==v)return u;
    if(dep[u]<dep[v])
        swap(u,v);
    for(int i=0; i<lg; i++)
        if((dep[u]-dep[v])&(1<<i))
            u=up[u][i];
    if(u==v)return u;
    for(int i=lg-1; 0<=i; i--)
        if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
    if(u!=v)
        u=up[u][0];
    return u;
}

map<pl,ll>C1,C2;

void solve() {
    int n;
    cin >> n;

    g.resize(n+1);
    dep.resize(n+1);
    up.resize(n+1,vi(lg,-1));

    for(int i=0; i<n-1;i++){
        ll u,v,c1,c2;
        cin >> u >> v >> c1 >> c2;
        g[u].pb(v);
        g[v].pb(u);
        C1[{u,v}]=C1[{v,u}]=c1;
        C2[{u,v}]=C2[{v,u}]=c2;
    }

    ll ans=0;
    dfs(1,-1);
    for(int j=1; j<lg ; j ++)
        for(int i=1; i<=n; i++)
            if(up[i][j-1]!=-1)
                up[i][j]=up[up[i][j-1]][j-1];

    d.resize(n+1);
    for(int i=1; i<n; i++){
        int l=lca(i,i+1);
        d[i]++,d[i+1]++;
        d[l]-=2;
    }
    dfs2(1,-1);

    for(int i=2; i<=n; i++){
        ll t=d[i];
        ll mn=min(t*C1[{i,up[i][0]}],
                  C2[{i,up[i][0]}] );
        ans+=mn;
    }
    out(ans)
}

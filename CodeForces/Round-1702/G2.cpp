/*
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 */
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int>vi;
typedef vector<vector<int>>vvi;
typedef vector<ll>vl;
typedef vector<vl> vvl;
typedef pair<int,int>pi;
typedef pair<ll,ll> pl;
typedef vector<pl> vpl;
typedef vector<ld> vld;
typedef pair<ld,ld> pld;
typedef vector<pi> vpi;

//typedef tree<ll, null_type, less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
template<typename T> ostream& operator<<(ostream& os, vector<T>& a){os<<"[";for(int i=0; i<ll(a.size()); i++){os << a[i] << ((i!=ll(a.size()-1)?" ":""));}os << "]\n"; return os;}

#define all(x) x.begin(),x.end()
#define YES out("YES")
#define NO out("NO")
#define out(x){cout << x << "\n"; return;}
#define outfl(x){cout << x << endl;return;}
#define GLHF ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define print(x){for(auto ait:x) cout << ait << " "; cout << "\n";}
#define pb push_back
#define umap unordered_map

template<typename T1, typename T2> istream& operator>>(istream& is, pair<T1, T2>& p){is >> p.first >> p.second;return is;}
template<typename T1, typename T2> ostream& operator<<(ostream& os, pair<T1, T2>& p){os <<"" << p.first << " " << p.second << ""; return os;}
void usaco(string taskname){
    string fin = taskname + ".in";
    string fout = taskname + ".out";
    const char* FIN = fin.c_str();
    const char* FOUT = fout.c_str();
    freopen(FIN, "r", stdin);
    freopen(FOUT, "w", stdout);
}
template<typename T>
void read(vector<T>& v){
    int n=v.size();
    for(int i=0; i<n; i++)
        cin >> v[i];
}
template<typename T>
vector<T>UNQ(vector<T>a){
    vector<T>ans;
    for(T t:a)
        if(ans.empty() || t!=ans.back())
            ans.push_back(t);
    return ans;
}



void solve();
int main(){
    GLHF;
    int t=1;
    //cin >> t;
    while(t--)
        solve();
}
vi tin,tout;
int n,q;
vvi g,up;
int timer=0,lg=19;
vi dep;

int lca(int u,int v){
    if(dep[u]<dep[v])
        swap(u,v);
    //dep[u]>=dep[v]
    for(int i=0; i<lg; i++)
        if((dep[u]-dep[v])&(1<<i))
            u=up[u][i];

    for(int i=lg-1; i>=0; i--)
        if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
    if(u!=v)
        u=up[u][0];
    return u;
}

bool qur(vi a){
    int n=a.size();
    if(n<=2)return 1;

    vvi b;


    auto add_edge=[&](int u,int v){
        g[u].pb(v);
        g[v].pb(u);
    };

    for(int i=0; i<n; i++){
        b.pb({tin[a[i]],0,a[i]});
    }
    sort(all(b));
    for(int i=0; i<n-1; i++)
        a.pb(lca(b[i][2],b[i+1][2]));
    stack<int>s;
    b=vvi();
    sort(all(a));
    a=UNQ(a);
    n=a.size();

    for(int i=0; i<n; i++){
        b.pb({tin[a[i]],0,a[i]});
        b.pb({tout[a[i]],1,a[i]});
    }
    sort(all(b));
    for(int i=0; i<b.size(); i++){
        int x=b[i][2];
        if(b[i][1]){
            //close
            s.pop();
            if(s.size())
                add_edge(x,s.top());
        }
        else{
            //open
            s.push(x);
        }
    }

    int d1=0,d2=0;
    bool ans=1;

    for(int i=0; i<n; i++) {
        if (g[a[i]].size() > 2)ans=0;
        if(!g[a[i]].size())ans=0;

        if(g[a[i]].size()==1)d1++;
        if(g[a[i]].size()==2)d2++;
    }
    if(d1==2 && d2==n-2)ans= 1;
    else ans= 0;

    for(int x:a)g[x].clear();
    return ans;
}



void dfs(int x,int p){
    tin[x]=++timer;
    up[x][0]=p;
    for(int j=1; j<lg && up[x][j-1]!=-1;j++)
        up[x][j]=up[up[x][j-1]][j-1];
    dep[x]=(p==-1?0:dep[p]+1);

    for(int nbr:g[x])
        if(nbr!=p)
            dfs(nbr,x);
    tout[x]=++timer;
}

void solve() {
    cin >> n ;
    g.resize(n+1);
    tin.resize(n+1);
    tout.resize(n+1);
    up.resize(n+1,vi(lg,-1));
    dep.resize(n+1);

    for(int i=0; i<n-1; i++){
        int u,v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,-1);
    for(int i=1; i<=n; i++)
        g[i].clear();

    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vi a(k);
        read(a);
        if(qur(a))
            cout << "YES\n";
        else
            cout << "NO\n";
        cout.flush();
    }
}

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
vector<vpi>g;
string side;
vi d;

bool bipartite(){
    int n=g.size()-1;
    vector<bool>in(n+1);

    for(int i=1; i<=n; i++){
        if(in[i])continue;
        queue<int>q;
        q.push(i);
        side[i]='L';
        in[i]=1;

        while(q.size()){
            int x=q.front();
            q.pop();

            for(pi p:g[x]){
                int nbr=p.second;
                if(side[nbr]==side[x])return 0;
                if(in[nbr])continue;
                side[nbr]='R'+'L'-side[x];
                in[nbr]=1;
                q.push(nbr);
            }
        }
    }
    return 1;
}

vvi g2;

void solve() {
    int n,m;
    cin >> n >> m;
    g.resize(n+1);

    for(int i=0;i<m; i++){
        int t,u,v;
        cin >> t >> u >> v;
        g[u].pb({t,v});
        g[v].pb({t,u});
    }
    side=string(n+1,' ');
    if(!bipartite())NO


    g2.resize(n+1);
    for(int i=1; i<=n; i++)
        for(pi p:g[i]){
            int nbr=p.second,t=p.first;
            if(t==1){
                if(side[i]=='R')
                    g2[i].pb(nbr);
                else
                    g2[nbr].pb(i);
            }
            else{
                if(side[i]=='L')
                    g2[i].pb(nbr);
                else
                    g2[nbr].pb(i);
            }
        }
    vi in_deg(n+1);

    for(int i=1; i<=n; i++){
        sort(all(g2[i]));
        g2[i]=UNQ(g2[i]);
        for(int j:g2[i])
            in_deg[j]++;
    }
    d.resize(n+1);


    vi vis(n+1);
    int timer=0,ok=0;


    auto dfs=[&](int src,int par,auto&& dfs)->void{
        vis[src]=1;
        for(int nbr:g2[src])
            if(nbr!=par){
                if(vis[nbr]==1){
                    cout << "NO\n";
                    exit(0);
                }
                else if(!vis[nbr])
                    dfs(nbr,src,dfs);
            }

        d[src]=++timer;
        vis[src]=2;
    };


    for(int i=1; i<=n; i++)
        if(!vis[i] && !in_deg[i])
            dfs(i,-1,dfs),ok=1;

    if(!ok)NO
    cout << "YES\n";
    for(int i=1; i<=n; i++)
        cout << side[i] << " " << d[i] << "\n";
}

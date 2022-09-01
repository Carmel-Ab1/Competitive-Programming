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
    cin >> t;
    while(t--)
        solve();
}
map<pi,vi>vals;//segment to value
map<pi,int>id;//id of segment
vvi g;
vpi segs;
vector<bool>vis;

multiset<int>dfs(int x){
    multiset<int>ans;
    vis[x]=1;

    int d=segs[x].second-segs[x].first+1;
    for(int nbr:g[x]) {
        multiset<int>cur=dfs(nbr);
        if(ans.size()<cur.size())
            swap(ans,cur);

        for(int x:cur)ans.insert(x);
    }
    int l=segs[x].first,r=segs[x].second;

    for(int v:vals[{l,r}])
        ans.insert(v);

    while(ans.size()>d)
        ans.erase(ans.begin());
    return ans;
}

void solve() {
    segs.clear();
    vals.clear();
    id.clear();
    g.clear();

    int n;
    cin >> n;
    g.resize(n);
    for(int i=0; i<n; i++){
        int l,r,v;
        cin >> l >> r >> v;
        vals[{l,r}].pb(v);
        id[{l,r}]=i;
        segs.pb({l,r});
    }

    sort(all(segs),[&](pi p1,pi p2){
        if(p1.first<p2.first)return 1;
        if(p1.first>p2.first)return 0;
        if(p1.first==p2.first)return p1.second>p2.second?1:0;
    });
    segs=UNQ(segs);
    n=segs.size();

    multiset<pi>Ls;
    vvi sweep;
    for(int i=0; i<n; i++){
        sweep.pb({segs[i].first,0,i});
        sweep.pb({segs[i].second,1,i});
    }
    sort(all(sweep));

    for(int i=0; i<2*n; i++){
        bool open=!sweep[i][1];
        int ix=sweep[i][2];

        if(open){
            if(Ls.size()){
                int p=Ls.rbegin()->second;
                g[p].pb(ix);
            }
            Ls.insert({sweep[i][0], ix});
        }
        else
            Ls.erase(Ls.find({segs[ix].first,ix}));
    }
    vis.clear();
    vis.resize(n);

    ll ans=0;
    for(int i=0; i<n; i++)
        if(!vis[i]) {
            multiset<int>s=dfs(i);
            for(int x:s)ans+=x;
        }

    outfl(ans)
}

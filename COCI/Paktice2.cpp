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
bool in(int i,int j,int n,int m){
    return 0<=i && 0<=j && i<n && j<m;
}
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string>a(n);
    read(a);

    deque<vi>q;
    vector<vector<bool>>vis(n,vector<bool>(m));
    vvi d(n,vi(m,1e9));

    vector<vector<pi>>prv(n,vpi(m,{-1,-1}));

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(a[i][j]=='o')
                q.pb({0,i,j,-1,-1});

    while(q.size()){
        vi cur=q.front();
        q.pop_front();
        int i=cur[1],j=cur[2],dst=cur[0];

        if(vis[i][j])
            continue;

        prv[i][j]={cur[3],cur[4]};
        vis[i][j]=1;
        d[i][j]=dst;

        if(a[i][j]=='x')
            continue;

        if(a[i][j]=='o' ){
            for(int dx:{-1,0,1})
                for(int dy:{-1,0,1})
                    if((dx==0)^(dy==0) && in(i+dx,j+dy,n,m) && !vis[i+dx][j+dy])
                        q.push_front({dst+(a[i][j]=='.'),i+dx,j+dy,i,j});
            continue;
        }
        else if(a[i][j]=='.'){
            for(int dx:{-1,0,1})
                for(int dy:{-1,0,1})
                    if((dx==0)^(dy==0) && in(i+dx,j+dy,n,m) && !vis[i+dx][j+dy])
                        q.push_back({dst+(a[i][j]=='.'),i+dx,j+dy,i,j});
            continue;
        }
        if(a[i][j]=='>' && j<m-1 && !vis[i][j+1])
            q.push_front({dst,i,j+1,i,j});

        else if(a[i][j]=='<' && j && !vis[i][j-1])
            q.push_front({dst,i,j-1,i,j});

        else if(a[i][j]=='v' && i!=n-1 && !vis[i+1][j])
            q.push_front({dst,i+1,j,i,j});

        else if(a[i][j]=='^' && i && !vis[i-1][j])
            q.push_front({dst,i-1,j,i,j});

        for(int dx:{-1,0,1})
            for(int dy:{-1,0,1})
                if((dx==0)^(dy==0) && in(i+dx,j+dy,n,m) && !vis[i+dx][j+dy])
                    q.push_back({dst+1,i+dx,j+dy,i,j});
    }
    pi cur={-1,-1};
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(a[i][j]=='x') {
                assert(d[i][j]!=1e9);
                cur = {i, j}, cout << d[i][j] << "\n";
            }
    while(1){
        int i=cur.first,j=cur.second;
        if(a[prv[i][j].first][prv[i][j].second]=='o')
            break;

        int pi=prv[i][j].first,pj=prv[i][j].second;
        if(pj==j-1)
            a[i][j-1]='>';
        else if(pj==j+1)
            a[i][j+1]='<';
        else if(pi==i-1)
            a[i-1][j]='v';
        else if(pi==i+1)
            a[i+1][j]='^';

        cur=prv[i][j];
    }
    for(string s:a)cout << s << "\n";
}

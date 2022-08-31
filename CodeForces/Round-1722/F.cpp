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
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string>a(n);
    read(a);

    auto edge_nbrs=[&](int i,int j)->vpi{
        vpi ans;
        for(int dx:{-1,0,1})
            for(int dy:{-1,0,1})
                if((i+dx>=0 && j+dy>=0) && i+dx<n && j+dy<m && (a[i+dx][j+dy]=='*') && ((dx==0)^(dy==0)))
                    ans.pb({i+dx,j+dy});
        return ans;
    };
    auto corner_nbrs=[&](int i,int j)->vpi{
        vpi ans;
        for(int dx:{-1,0,1})
            for(int dy:{-1,0,1})
                if((i+dx>=0 && j+dy>=0) && i+dx<n && j+dy<m && (a[i+dx][j+dy]=='*') && ((dx!=0)||(dy!=0)))
                    ans.pb({i+dx,j+dy});
        return ans;
    };

    vector<vector<bool>>done(n,vector<bool>(m));

    for(int i=0; i<n ;i++)
        for(int j=0; j<m; j++){
            if(a[i][j]=='.')continue;

            vpi edge=edge_nbrs(i,j);
            if(edge.size()>2)NO
            if(edge.size()!=2)continue;

            if(i && i+1<n && a[i-1][j]==a[i+1][j] && a[i-1][j]=='*')NO
            if(j && j+1<m && a[i][j-1]==a[i][j+1] && a[i][j-1]=='*')NO

            done[i][j]=1;
            for(auto [ni,nj]:edge){
                done[ni][nj]=1;
                vpi v=corner_nbrs(ni,nj);
                for(pi p:v)
                    if(p!=(pi){i,j} && !count(all(edge),p))NO
            }
            for(pi p:corner_nbrs(i,j))
                if(p!=(pi){i,j} && !count(all(edge),p))NO
        }
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(a[i][j]=='*' && !done[i][j])NO
    YES
}

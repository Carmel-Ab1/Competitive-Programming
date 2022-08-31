#include<bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
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
int n;
inline int calc(int i,int j){
    return n*i+j;
}

int pref[500*500];

inline int sum(int i1,int j1,int i2,int j2){
    int ans=pref[calc(i2,j2)];
    if(i1)
        ans-=pref[calc(i1-1,j2)];
    if(j1)
        ans-=pref[calc(i2,j1-1)];
    if(i1 && j1)
        ans+=pref[calc(i1-1,j1-1)];
    return ans;
}
void solve() {
    cin >> n;

    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
            pref[calc(i,j)] = (i ? pref[calc(i - 1,j)] : 0) + (j ? pref[calc(i,j - 1)] : 0) - ((i && j) ? pref[calc(i - 1,j - 1)] : 0) +(s[j] == '1');
    }

    int ans=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) {
            int l=0,r=min(n-i-1,n-j-1),mx=-1;
            while(l<=r){
                int k=(l+r)/2;
                if(sum(i,j,i,j+k)==k+1 && sum(i,j,i+k,j)==k+1)
                    mx=k,l=k+1;
                else
                    r=k-1;
            }
            for(int k=0; k<=mx; k++)
                if(sum(i,j+k,i+k,j+k)==k+1 && sum(i+k,j,i+k,j+k)==k+1)
                    ans++;
        }
    out(ans)
}

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
vl f,inv;
ll mod=1e9+7;
ll bpow(ll a,ll b){
    if(!b)return 1;
    ll r=bpow(a,b/2);
    r=(r*r)%mod;
    if(b&1)r=(r*a)%mod;
    return r;
}
ll C(ll n,ll k){
    ll ans=f[n];
    ans=(ans*inv[k])%mod;
    ans=(ans*inv[n-k])%mod;
    return ans;
}

ll hockey(ll n,ll r){
    return C(n+1,r+1);
}

void solve() {
    int n;
    cin >> n;
    vi a(n+1);
    read(a);

    int maxn=4e5+10;
    vl dp(maxn);//dp[i] = how many stones of row i
    dp[0]=1;

    f.resize(maxn);
    f[0]=1;
    for(int i=1; i<maxn; i++)
        f[i]=(f[i-1]*i)%mod;
    inv.resize(maxn);
    inv.back()=bpow(f.back(),mod-2);
    for(int i=inv.size()-2; 0<=i ;i--)
        inv[i]=((i+1)*inv[i+1])%mod;

    ll ans=0;
    for(int i=0; i<=n; i++){
        // for(int j=0; j<a[i]; j++)
        //ans=(ans+(C(i+j,i)))%mod;

        if(!a[i])break;
        ll cur= hockey(i+a[i]-1,i);
        ans=(ans+cur)%mod;
    }

    out(ans)
}

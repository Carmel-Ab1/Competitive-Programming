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

ll power(ll base, ll exp,ll M=1e18){//(base^exp)%M
    ll ans=1;
    while(exp){
        if(exp%2==1)ans=((ans%M)*(base%M))%M;
        base=((base%M)*(base%M))%M;
        exp/=2;
    }
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
const ll sqr=1e5;
ll anti_tri(ll x){
    ll l=1,r=sqr,ans=-1;
    while(l<=r){
        ll m=(l+r)/2;
        if((m*(m-1))/2 <x)
            ans=m,l=m+1;
        else
            r=m-1;
    }
    return ans;
}

ll mod=1e9+7;
vl f;
ll C(ll n,ll k){
    if(!f.size()){
        f.resize(sqr);
        f[0]=1;
        for(int i=1; i<sqr; i++)
            f[i]=(i*f[i-1])%mod;
    }
    ll ans=f[n];
    ans=(ans*power(f[k],mod-2,mod))%mod;
    ans=(ans*power(f[n-k],mod-2,mod))%mod;
    return ans;
}



ll calc(int s,int e){
    if(s==e)
        return 1;

    ll r1= anti_tri(s),r2= anti_tri(e);

    ll c1=s-(r1*(r1-1))/2;
    ll c2=e-(r2*(r2-1))/2;
    if(r1>r2 || c1>c2 || r1==r2)return 0;

    ll D=r2-r1,R=c2-c1;
    if(D<R)return 0;
    D-=R;
    return (C(R+D,D))%mod;
}
void solve() {
    int s,e;
    cin >> s >> e;
    out(calc(s,e))

}

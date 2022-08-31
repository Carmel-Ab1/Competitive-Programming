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
ll ceil(ll a,ll b){
    ll ans=a/b;
    if(a%b)ans++;
    return ans;
}
ld log (ld a,ld b){return log(b)/log(a);}
ll power(ll base, ll exp,ll M=1e18){//(base^exp)%M
    ll ans=1;
    while(exp){
        if(exp%2==1)ans=((ans%M)*(base%M))%M;
        base=((base%M)*(base%M))%M;
        exp/=2;
    }
    return ans;
}

string to_base(int n,int new_base){
    string s;
    int nn=n;
    while(nn){
        s+=to_string(nn%new_base);
        nn/=new_base;
    }
    reverse(all(s));
    return s;
}
ll gcd(ll a,ll b){
    if(a<b)swap(a,b);
    if(b==0)return a;
    return gcd(b,a%b);
}
ll lcm(ll a,ll b){
    ll x= (a/gcd(a,b));
    return b*x;
}
vl generate_array(ll n,ll mn=1,ll mx=1e18+1){
    if(mx==1e18+1)
        mx=n;
    vl ans(n);
    for(int i=0; i<n;i++)
        ans[i]=(mn+rand()%(mx-mn+1));
    return ans;
}
string substr(string s,int l,int r){
    string ans;
    for(int i=l; i<=r; i++)
        ans+=s[i];
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
int calc(int x){

}
void solve() {
    int n;
    cin >> n;
    vi a(n);
    read(a);

    if(a==vi(n,a[0]))out(0)
    map<int,int>cnt;
    int mx=0;
    for(int i=0; i<n; i++)
        cnt[a[i]]++,mx=max(mx,cnt[a[i]]);

    if(mx==1)out(-1)

    int ans=2,all=n-mx,odd=0;
    while(all>1){
        if(all%2==0)
            ans+=all/2,all/=2;
        else{
            ans++;
            all--;
        }
    }
    out(ans)
}

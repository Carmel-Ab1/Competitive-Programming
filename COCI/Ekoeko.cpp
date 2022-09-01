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


void solve();
int main(){
    GLHF;
    int t=1;
    //cin >> t;
    while(t--)
        solve();
}

struct seg{
    vl t;
    ll sz=1;
    seg(int n){
        while(sz<=2*n)
            sz*=2;
        t.resize(sz);
    }

    void upd(int i,int v){
        t[i+=sz/2]+=v;
        while(i){
            t[i/2]=t[i]+t[i^1];
            i/=2;
        }
    }

    ll qur(ll l,ll r){
        ll ans=0;
        for(l+=sz/2,r+=sz/2 +1; l<r; l/=2,r/=2){
            if(l&1)ans+=t[l++];
            if(r&1)ans+=t[--r];
        }
        return ans;
    }
};

ll count(string s,string t){
    int n=s.size();
    vi to(n);

    vvi c(26);
    for(int i=0; i<n; i++)
        c[s[i]-'a'].pb(i);

    for(int i=n-1; 0<=i; i--){
        to[c[t[i]-'a'].back()]=i;
        c[t[i]-'a'].pop_back();
    }

    ll ans=0;
    seg ST(n);
    for(int i=0; i<n; i++){
        ans+=ST.qur(to[i]+1,n);
        ST.upd(to[i],1);
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    string s1,s2;


    map<int,int>cnt,cur;
    for(char c:s)
        cnt[c]++;

    for(int i=0; i<2*n; i++){
        cur[s[i]]++;

        if(2*cur[s[i]]<=cnt[s[i]])
            s1+=s[i];
    }

    cur.clear();
    for(int i=2*n-1; 0<=i ;i--){
        cur[s[i]]++;

        if(2*cur[s[i]]<=cnt[s[i]])
            s2+=s[i];
    }

    reverse(all(s2));

    out(min(count(s,s1+s1),count(s,s2+s2)))
}


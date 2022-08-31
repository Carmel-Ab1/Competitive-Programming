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
ll gcd(ll a,ll b){return a+b;}
int N=1001,M=1001,q;
struct seg1{
    int l,r;
    seg1* lp=0,*rp=0;
    ll g=0;

    seg1(int l,int r):l(l),r(r){}

    inline void upd(int i,ll v){
        if(l+1==r){
            g=v;
            return;
        }
        if(i<(l+r)/2){
            if(!lp)lp=new seg1(l,(l+r)/2);
            lp->upd(i,v);
            g=gcd(lp->g,rp?rp->g:0);
        }
        else {
            if(!rp)rp=new seg1((l+r)/2,r);
            rp->upd(i,v);
            g=gcd(rp->g,lp?lp->g:0);
        }
    }
    inline ll qur(int a,int b){
        if(b<=l || r<=a)return 0;
        if(a<=l && r<=b)
            return g;

        return gcd(lp?lp->qur(a,b):0,rp?rp->qur(a,b):0);
    }
};

struct seg2{
    int l,r;
    seg2* lp=0,*rp=0;
    seg1* s=0;

    seg2(){}
    seg2(int l,int r):l(l),r(r){s=new seg1(0,M);}


    inline void upd(int i,int j,ll v){
        if(l+1==r){
            s->upd(j,v);
            return;
        }

        if(i<(l+r)/2) {
            if(!lp)lp=new seg2(l,(l+r)/2);
            lp->upd(i, j, v);
        }
        else {
            if(!rp)rp=new seg2((l+r)/2,r);
            rp->upd(i, j, v);
        }

        s->upd(j,gcd(lp?lp->s->qur(j,j+1):0,rp? rp->s->qur(j,j+1):0));

    }
    inline ll qur(int a1,int b1,int a2,int b2){
        if(b1<=l || r<=a1)return 0;
        if(a1<=l && r<=b1)
            return s->qur(a2,b2);
        return gcd(lp?lp->qur(a1,b1,a2,b2):0,rp?rp->qur(a1,b1,a2,b2):0);
    }
};
void solve() {
    int n,q;
    cin >> n >> q;

    vpi a(n);
    read(a);

    vvl b(1001,vl(1001));
    for(auto [x,y]:a)
        b[x][y]+=1ll*x*y;

    for(int i=1; i<=1000; i++)
        for(int j=1; j<=1000; j++){
            b[i][j]+=b[i-1][j];
            b[i][j]+=b[i][j-1];
            b[i][j]-=b[i-1][j-1];
        }

    while(q--){
        int h1,w1,h2,w2;
        cin >> h1 >> w1 >> h2 >> w2;
        ll ans=b[h2-1][w2-1];
        ans-=b[h2-1][w1];
        ans-=b[h1][w2-1];
        ans+=b[h1][w1];
        cout << ans << "\n";
    }
}

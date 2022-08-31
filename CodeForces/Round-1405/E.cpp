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
struct SegSum{
    vi t;
    int sz=1;

    SegSum(int n){
        sz=2*n;
        t.resize(2*sz);
    }
    void upd(int i,int v){
        t[i+=sz/2]+=v;
        while(i>1){
            t[i/2]=t[i]+t[i^1];
            i/=2;
        }
    }
    int qur(int l,int r){
        int ans=0;
        for(l+=sz/2,r+=sz/2 +1; l<r; l/=2,r/=2){
            if(l&1)ans+=t[l++];
            if(r&1)ans+=t[--r];
        }
        return ans;
    }
};
struct seg{//range+=, range {min,argmin} segment tree
    int l,r,m;
    seg* lp=0,*rp=0;

    pl mn;
    ll prop=0;

    seg(int l,int r):l(l),r(r),m((l+r)/2){
        if(l+1==r)
            mn={0,l};
        else{
            lp=new seg(l,m);
            rp=new seg(m,r);
            mn=min(lp->mn,rp->mn);
        }
    }

    void add(ll x){
        mn.first+=x;
        prop+=x;
    }
    void push(){
        lp->add(prop);
        rp->add(prop);
        prop=0;
    }
    void upd(int a,int b,ll v){
        if(r<=a || b<=l)
            return;
        else if(a<=l && r<=b){
            add(v);
            return;
        }
        push();
        lp->upd(a,b,v);
        rp->upd(a,b,v);
        mn=min(lp->mn,rp->mn);
    }
    pl qur(int a,int b){
        if(r<=a || b<=l)
            return {1e9,-1};
        else if(a<=l && r<=b)
            return mn;
        push();
        return min(lp->qur(a,b),rp->qur(a,b));
    }
};
void solve() {
    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i=1; i<=n; i++){
        cin >> a[i];
        a[i]=i-a[i];
        if(a[i]<0)
            a[i]=1e9;
    }
    //take last 0 decrement suffix


    vector<vvi> queries(n+1);
    for(int i=0; i<q; i++){
        int l,r;
        cin >> l >> r;
        l++;
        r=n-r;
        queries[l].pb({r,i});
    }

    vi ans(q);
    SegSum active(n+2);
    seg need(0,n+2);//how much more I need to become active
    for(int i=1; i<=n; i++)
        need.upd(i,i+1,a[i]);

    for(int i=n; 1<=i; i--){

        while(1){
            pi p=need.qur(i,n+1);
            int first=p.second,val=p.first;
            if(first==-1)break;
            if(val>0)break;
            active.upd(first,1);
            need.upd(first,first+1,1e9);
            need.upd(first,n+1,-1);
        }



        for(vi query:queries[i]){
            int l=i,r=query[0],ix=query[1];
            ans[ix]=active.qur(l,r);
        }
    }

    print(ans)
}

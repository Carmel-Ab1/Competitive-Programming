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
void compress(vpi& a){
    vi s;
    int n=a.size();
    for(int i=0; i<n; i++){
        s.pb(a[i].first);
        s.pb(a[i].second);
    }
    sort(all(s));
    umap<int,int>conv;
    for(int i=0; i<2*n; i++)
        conv[s[i]]=i;
    for(int i=0; i<n; i++)
        a[i]={conv[a[i].first],conv[a[i].second]};
}
struct seg{
    int l,r,m;
    seg* lp,*rp;

    int mx=-1,prop=-1;

    seg(int l,int  r):l(l),r(r),m((l+r)/2){
        if(l+1<r){
            lp=new seg(l,m);
            rp=new seg(m,r);
        }
    }

    void apply(int x){
        mx=max(mx,x);
        prop=max(prop,x);
    }
    void push(){
        if(l+1==r)return;
        lp->apply(prop);
        rp->apply(prop);
        prop=-1;
    }

    void upd(int a,int b,int x){
        if(r<=a || b<=l)
            return;
        else if(a<=l && r<=b){
            apply(x);
            return;
        }
        push();
        lp->upd(a,b,x);
        rp->upd(a,b,x);
        mx=max(mx,lp->mx);
        mx=max(mx,rp->mx);
    }
    int qur(int a,int b){
        if(r<=a || b<=l)
            return -1;
        else if(a<=l && r<=b)
            return mx;
        push();
        return max(lp->qur(a,b),rp->qur(a,b));
    }
};
void solve() {
    int n;
    cin >> n ;
    vpi a(n);
    read(a);
    compress(a);
    int lg=18;

    vvi dp(n,vi(lg,-1));
    seg s(0,2*n+1);
    for(int i=0; i<n; i++){
        if(i)
            dp[i][0]=dp[i-1][0];
        dp[i][0]=max(dp[i][0],s.qur(a[i].first,a[i].second+1));

        s.upd(a[i].first,a[i].second+1,i);
    }

    for(int j=1; j<lg; j++)
        for(int i=0; i<n; i++) {
            if(i)
                dp[i][j]=dp[i-1][j];
            if(dp[i][j-1]!=-1)
                dp[i][j]=max(dp[i][j],dp[dp[i][j-1]][j-1]);
        }


    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;

        int ans=0;

        for(int i=lg-1; 0<=i; i--)
            if(dp[r][i]>=l)
                ans+=(1<<i),r=dp[r][i];
        for(int i=0; i<lg; i++)
            if(dp[r][i]<=l){
                ans+=(1<<i);
                break;
            }
        cout << ans << "\n";
    }
}

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
bool brute_force(vi a){
    int n=a.size();
    for(int i=0; i<(1<<n); i++){
        vi s;
        for(int j=0; j<n ;j++)
            if(i&(1<<j))
                s.pb(a[j]);
        for(int j=0; j<n ;j++)
            if(!(i&(1<<j)))
                s.pb(a[j]);
        if(is_sorted(all(s)))
            return 1;
    }
    return 0;
}
void make_tests(int n){
    freopen("output.txt","w",stdout);
    int tests=1e3;
    cout << tests << "\n";
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    while(tests--){
        cout << n << "\n";
        for(int i=0; i<n; i++)
            cout << uniform_int_distribution<>(0,2*n)(rng) << " ";
        cout << "\n";
    }
    exit(0);
}
vi b;

void compress(vi& a){
    b=a;
    int n=a.size();
    vpi s(n);
    for(int i=0; i<n;i++)
        s[i]={a[i],i};
    sort(all(s));
    vi ans(n);
    for(int i=0; i<n;i ++)
        ans[s[i].second]=i;
    a=ans;
}

bool calc(vi a){
    int n=a.size();
    vi s(a);
    sort(all(s));
    vector<bool>done(n);

    for(int i=0,j=0; i<n; i++)
        if(a[i]==s[j])
            done[i]=1,j++;
    vi P,Q;
    for(int i=0; i<n;i ++)
        if(done[i])
            P.pb(a[i]);
        else
            Q.pb(a[i]);

    vi S(P);
    for(int x:Q)
        S.pb(x);
    if(is_sorted(all(S)))
        return 1;
    else
        return 0;
}

void solve() {
    int n;
    cin >> n;
    //make_tests(n);
    vi a(n);
    read(a);

    bool ans=calc(a);
    if(ans)YES
    else NO
}

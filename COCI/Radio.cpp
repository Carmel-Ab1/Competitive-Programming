#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int>vi;
#define out(x){cout << x << "\n"; return;}
#define GLHF ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


void solve();
int main(){
    GLHF;
    int t=1;
    //cin >> t;
    while(t--)
        solve();
}


vi a,sieve;
set<int> active[int(1e6+1)],start_here[int(1e6+1)];
vi t;


int sz=1;

void add(int i){
    i+=sz/2;
    t[i]=*start_here[i-sz/2].begin();

    while(i){
        t[i/2]=min(t[i],t[i^1]);
        i/=2;
    }
}
void del(int i){
    i+=sz/2;
    t[i]=(start_here[i-sz/2].size()?*start_here[i-sz/2].begin():1e9);
    while(i){
        t[i/2]=min(t[i],t[i^1]);
        i/=2;
    }
}

int qurmin(int l,int r){
    int ans=1e9;
    for(l+=sz/2,r+=sz/2 +1; l<r; l/=2,r/=2){
        if(l&1){
            ans=min(ans,t[l]);
            l++;
        }
        if(r&1){
            r--;
            ans=min(ans,t[r]);
        }
    }
    return ans;
}

void add_seg(int l,int r){
    start_here[l].insert(r);
    add(l);
}
void del_seg(int l,int r){
    start_here[l].erase(r);
    del(l);
}

void start(int x){
    if(!a[x]){
        int cur=x;
        while(cur>1){
            int d=sieve[cur];

            if(active[d].size()){
                int R=(x<*active[d].rbegin()?*active[d].upper_bound(x):-1);
                int L=(x>*active[d].begin()?*(--active[d].upper_bound(x)):-1);


                if(L!=-1 && R!=-1)
                    del_seg(L,R);
                if(L!=-1)
                    add_seg(L,x);
                if(R!=-1)
                    add_seg(x,R);
            }
            active[d].insert(x);
            while(cur>1 && cur%d==0)
                cur/=d;
        }
    }
    else{
        int cur=x;
        while(cur>1){
            int d=sieve[cur];

            if(active[d].size()){
                int R=(x<*active[d].rbegin()?*active[d].upper_bound(x):-1);
                int L=(x>*active[d].begin()?*(--active[d].lower_bound(x)):-1);

                if(L!=-1)
                    del_seg(L,x);
                if(R!=-1)
                    del_seg(x,R);
                if(L!=-1 && R!=-1)
                    add_seg(L,R);
            }
            active[d].erase(x);
            while(cur>1 && cur%d==0)
                cur/=d;
        }
    }
    a[x]^=1;
}


void qur(int l,int r){
    if(qurmin(l,r)<=r)out("DA")
    out("NE")
}

void solve() {
    int n,q;
    cin >> n >> q;

    a.resize(n+1),sieve.resize(n+1,1);

    for(ll i=2; i<=n; i++){
        if(sieve[i]!=1)continue;
        sieve[i]=i;
        for(ll j=i*i; j<=n; j+=i)
            sieve[j]=i;
    }
    sz=2*(n+2);
    t.resize(sz,1e9);

    while(q--){
        char op;
        cin >> op;

        if(op=='S'){
            int x;
            cin >> x;
            start(x);
        }
        else{
            int l,r;
            cin >> l >> r;
            qur(l,r);
        }
    }

    out("")
}
/*
 10 4
S 3
S 6
S 9
S 6

 */

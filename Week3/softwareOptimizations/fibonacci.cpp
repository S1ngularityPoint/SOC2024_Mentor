#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pll pair<ll,ll>
#define pp pair<pll,pll>
#define mp make_pair
// #define f first
// #define s second 

ll naive (ll n) {
    ll dp[n+1];
    dp[1] = 1;
    dp[2] = 1;
    for (ll i=3; i<=n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

pp m(pp &p1, pp &p2){ 
    return mp(mp(p1.first.first*p2.first.first + p1.first.second*p2.second.first, p1.first.first*p2.first.second + p1.first.second*p2.second.second), mp(p1.second.first*p2.first.first + p1.second.second*p2.second.first, p1.second.first*p2.first.second + p1.second.second*p2.second.second));
}

ll optim(ll n){
    ll t = n-1;
    pp x = mp(mp(1,1),mp(1,0));
    pp ans = mp(mp(1,0),mp(0,1));
    while(t > 0){
        if(t&1) ans = m(ans,x);
        x = m(x,x);
        t = t>>1;
    }
    return ans.first.first;
}

int main(){
    ll n; cin >> n;
    auto startNaive = chrono::high_resolution_clock::now();
    ll slow = naive(n);
    auto endNaive = chrono::high_resolution_clock::now();
    auto naiveTime = chrono::duration_cast<chrono::duration<double>>(endNaive - startNaive);

    auto startOptim = chrono::high_resolution_clock::now();
    ll fast = optim(n);
    auto endOptim = chrono::high_resolution_clock::now();
    auto optimTime = chrono::duration_cast<chrono::duration<double>>(endOptim - startOptim);

    cout<<"Answer from naive technique : "<<slow<<endl;
    cout<<"Answer from optimal technique : "<<fast<<endl;
    cout<<"Time taken by naive technique : "<<naiveTime.count()<<endl;
    cout<<"Time taken by optimal technique : "<<optimTime.count()<<endl;

}
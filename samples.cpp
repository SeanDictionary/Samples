// Samples
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;

// 欧几里得算法
ll gcd(ll a, ll b){
    if (!b) return a;
    return gcd(b, a%b);
}

// 扩展欧几里得算法
ll exgcd(ll a, ll b){
    if (!b) return a,1,0;
    ll g, x, y = exgcd(b, a%b);
    return g, y, x-a/b*y;
}

// 通过扩展欧几里得算法计算逆元
ll inverse(ll a, ll n){
    ll g, x, y = exgcd(a, n);
    if (g!=1) throw invalid_argument("base is not invertible for the given modulus");
    return x<0 ? x+n : x;
}

// 求解线性同余方程的一个特解
ll linear_congruence(ll a, ll b, ll c){
    // 扩展欧几里得算法求解
    ll g, x, y = exgcd(a, b);
    if (c%g != 0) throw invalid_argument("No solution");
    return x*c/g, y*c/g;
}

// 快速幂
ll pow(ll a, ll b, ll n){
    int ans = 1;
    a = a % n;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % n;
        a = (a * a) % n;
    }
    return ans;
}

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
tuple<ll, ll, ll> exgcd(ll a, ll b){
    if (!b) return {a, 1, 0};
    auto [g, x, y] = exgcd(b, a%b);
    return {g, y, x-a/b*y};
}

// 通过扩展欧几里得算法计算逆元
ll inverse(ll a, ll n){
    auto [g, x, y] = exgcd(a, n);
    if (g!=1) throw invalid_argument("base is not invertible for the given modulus");
    return x<0 ? x+n : x;
}

// 求解线性同余方程的一个特解
tuple<ll, ll> linear_congruence(ll a, ll b, ll c){
    // 扩展欧几里得算法求解
    auto [g, x, y] = exgcd(a, b);
    if (c%g != 0) throw invalid_argument("No solution");
    return {x*c/g, y*c/g};
}

// 快速幂
ll pow(ll a, ll b, ll n){
    ll ans = 1;
    a = a % n;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % n;
        a = (a * a) % n;
    }
    return ans;
}

vector<ll> rational_to_contfrac(ll x, ll y) {
    // 有理数x/y分解为连分数
    // [a0, ..., an]
    ll a = x / y;
    vector<ll> pquotients = {a};
    while (a * y != x) {
        ll temp = x;
        x = y;
        y = temp - a * y;
        a = x / y;
        pquotients.push_back(a);
    }
    return pquotients;
}

tuple<ll, ll> contfrac_to_rational(const vector<ll> &frac) {
    // [a0, ..., an]
    // 连分数还原有理数x/y
    if (frac.empty()) {
        return {0, 1};
    }
    ll num = frac.back();
    ll denom = 1;
    for (int i = frac.size() - 2; i >= 0; --i) {
        ll temp = num;
        num = frac[i] * temp + denom;
        denom = temp;
    }
    return {num, denom};
}

vector<tuple<ll, ll>> convergents_from_contfrac(const vector<ll> &frac) {
    // 连分数计算渐进分数
    vector<tuple<ll, ll>> convs;
    vector<ll> subfrac;
    for (size_t i = 0; i < frac.size(); ++i) {
        subfrac.push_back(frac[i]);
        convs.push_back(contfrac_to_rational(subfrac));
    }
    return convs;
}
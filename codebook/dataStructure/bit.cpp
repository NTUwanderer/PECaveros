typedef long long ll;
ll sum(ll x, ll c[]){
    ll ans = 0;
    for (ll i = x; i > 0; i -= (i & (-i)))
        ans += c[i];
    return ans;
}

void modify(ll x, ll d, ll c[]){
    for (ll i = x; i <= M ; i += (i & (-i)))
        c[i] += d;
}

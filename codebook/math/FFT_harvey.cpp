#define fore(i,l,r) for(int i=int(l); i<int(r); i++)
#define forn(i,n) fore(i,0,n)
#define sz(a) int((a).size())

typedef long long ll;
typedef vector<ll> vc;
ll aa[maxn], bb[maxn], cc[maxn];
ll const modulo = 998244353;
ll const LOGN = 22;
int g = 3;
inline ll mul(ll a, ll b){
  return (a * b) % modulo;
}
inline ll norm(ll a) {
  if(a >= modulo)
    a -= modulo;
  if(a < 0)
    a += modulo;
  return a;
}
inline ll binPow(ll a, ll k) {
  ll ans = 1;
  while(k > 0) {
    if(k & 1)
      ans = mul(ans, a);
    a = mul(a, a);
    k >>= 1;
  }
  return ans;
}
inline ll inv(ll a) {
  return binPow(a, modulo - 2);
}
vc w[LOGN], rv[LOGN];
void precalc() {
  ll wb = binPow(g, (modulo - 1) / (1 << LOGN));
  for(ll st = 0; st < LOGN - 1; st++) {
    w[st].assign(1 << st, 1);
    ll bw = binPow(wb, 1 << (LOGN - st - 1));
    ll cw = 1;
    for (ll k = 0; k < (1 << st); k++) {
      w[st][k] = cw;
      cw = mul(cw, bw);
    }
  }
  for(ll st = 0; st < LOGN; st++) {
    rv[st].assign(1 << st, 0);

    if(st == 0) {
      rv[st][0] = 0;
      continue;
    }
    ll h = (1 << (st - 1));
    for(ll k = 0; k < (1 << st); k++)
      rv[st][k] = (rv[st - 1][k & (h - 1)] << 1) | (k >= h);
  }
}
inline void fft(ll a[maxn], ll n, bool inverse) {
  ll ln = 0;
  while((1 << ln) < n)
    ln++;
  assert((1 << ln) < maxn);
  n = (1 << ln);
  forn(i, n) {
    ll ni = rv[ln][i];
    if(i < ni)
      swap(a[i], a[ni]);
  }
  for(ll st = 0; (1 << st) < n; st++) {
    ll len = (1 << st);
    for(ll k = 0; k < n; k += (len << 1)) {
      for(ll pos = k; pos < k + len; pos++) {
        ll l = a[pos];
        ll r = mul(a[pos + len], w[st][pos - k]);

        a[pos] = norm(l + r);
        a[pos + len] = norm(l - r);
      }
    }
  }
  if(inverse) {
    ll in = inv(n);
    forn(i, n)
      a[i] = mul(a[i], in);
    reverse(a + 1, a + n);
  }
}


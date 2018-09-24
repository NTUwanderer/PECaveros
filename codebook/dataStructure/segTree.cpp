#define maxn 200005
typedef long long ll;
struct seg {
	int lson, rson;
	int smallCount;
};

seg tree[maxn*10];

void build(ll root, ll l, ll r) {
	tree[root].smallCount = 0;
	if (l == r) return;
	tree[root].lson = (root << 1);
	tree[root].rson = (root << 1)+1;
	build(tree[root].lson, l, (l+r)/2);
	build(tree[root].rson, (l+r)/2+1, r);
}
bool update(ll root, ll l, ll r, ll ind) {
	ll lid = tree[root].lson, rid = tree[root].rson;
	if (l == r) {
		tree[root].smallCount++;
		return true;
	} else if (ind <= (l+r) / 2) {
		if (update(lid, l, (l+r)/2, ind) == false)
			return false;
	} else {
		if (update(rid, (l+r)/2+1, r, ind) == false)
			return false;
	}
	tree[root].smallCount = min(tree[lid].smallCount,
                                tree[rid].smallCount);
	return true;
}

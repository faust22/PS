#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

template<size_t sz>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1), lazy(sz << 1) {}
	void update(int l, int r, int val, int node = 1, int L = 1, int R = sz) { //[l, r] += val
		if (r < L || R < l) return;
		if (l <= L && R <= r) lazy[node] += val;
		else {
			int mid = L + R >> 1;
			update(l, r, val, node << 1, L, mid);
			update(l, r, val, node << 1 | 1, mid + 1, R);
		}
		if (lazy[node]) tree[node] = R - L + 1;
		else tree[node] = node < sz ? tree[node << 1] + tree[node << 1 | 1] : 0;
	}
	int query(int l, int r, int node = 1, int L = 1, int R = sz) { //Sum[v[i] > 0, {i, l, r}]
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return query(l, r, node << 1, L, mid) + query(l, r, node << 1 | 1, mid + 1, R);
	}
	int query() { return query(1, sz); }
};

struct Event {
	int x, y1, y2, delta;
	bool operator < (const Event& i) const {
		return x < i.x || x == i.x && delta < i.delta;
	}
};

SegTree<1 << 15> ST;

int main() {
	fastio;
	int n; cin >> n;
	vector<Event> v;
	for (int i = 0; i < n; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		v.push_back({ a, b + 1, d, 1 });
		v.push_back({ c, b + 1, d, -1 });
	}
	sort(v.begin(), v.end());
	int ans = 0, prev = 0;
	for (const auto& [x, y1, y2, delta] : v) {
		ans += ST.query() * (x - prev);
		prev = x;
		ST.update(y1, y2, delta);
	}
	cout << ans << '\n';
}
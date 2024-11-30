// source : https://usaco.guide/adv/count-min?lang=cpp
const int MAXN = 2e5;

struct Node {
	int val = INT32_MAX, cnt = 1;
} tree[2 * MAXN];

// combines two segment tree nodes
Node merge(Node a, Node b) {
	if (a.val < b.val) {
		return a;
	} else if (a.val > b.val) {
		return b;
	}
	return {a.val, a.cnt + b.cnt};
}

// updates the ith value to v
void update(int i, int v) {
	for (tree[i += MAXN] = {v, 1}; i > 1; i >>= 1) {
		tree[i >> 1] = merge(tree[i], tree[i ^ 1]);
	}
}

// returns the minimum and occurences between indices l and r
Node query(int l, int r) {
	Node res;
	for (l += MAXN, r += MAXN + 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = merge(res, tree[l++]);
		if (r & 1) res = merge(res, tree[--r]);
	}
	return res;
}
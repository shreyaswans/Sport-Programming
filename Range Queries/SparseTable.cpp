template<typename Node>
struct SparseTable {
	vector<vector<Node>> table;
	int n;
	int maxLog;
	vector<ll> a;
	SparseTable(int n1, vector<ll> &arr) {
		n = n1;
		a = arr;
		table.resize(n);
		maxLog = log2_floor(n);
		for (int i = 0; i < n; i++) {
			table[i].resize(maxLog + 1);
			fill(all(table[i]), Node());
		}
		build();
	}
	void build() {
		for (int i = 0; i < n; i++) {
			table[i][0] = Node(a[i]);
		}
		for (int i = 1; i <= maxLog; i++) {
			for (int j = 0; (j + (1 << i)) <= n; j++) {
				table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
//0 - indexed query
	Node queryNormal(int left, int right) {
		Node ans = Node();
		for (int j = log2_floor(right - left + 1); j >= 0; j--) {
			if ((1 << j) <= right - left + 1) {
				ans.merge(ans, table[left][j]);
				left += (1 << j);
			}
		}
		return ans;
	}
// 0 - indexed query
	Node queryIdempotent(int left, int right) {
		int j = log2_floor(right - left + 1);
		Node ans = Node();
		ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
		return ans;
	}
};
struct Node1 {
	ll val, mn, mx; // store more info if required
	Node1() { // Identity Element
		val = 0;
		mn = 0;
		mx = 0;
	}
	Node1(ll v) {
		val = v;
		mn = v;
		mx = v;
	}
	void merge(Node1 &l, Node1 &r) {
		val = l.val + r.val;
		mn = min(l.mn, r.mn);
		mx = max(l.mx, r.mx);
	}
};
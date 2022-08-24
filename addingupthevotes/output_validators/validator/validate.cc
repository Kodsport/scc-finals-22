#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

const int MAX_Q = 30;

int main(int argc, char **argv) {
	init_io(argc, argv);

	ll N;
	judge_in >> N;
	vi color(N);
	rep(i,0,N) judge_in >> color[i];
	map<int, int> co;
	rep(i,0,N) co[color[i]]++;
	int majority = -1;
	trav(pa, co) if (pa.second > N/2) majority = pa.first;

	cout << N << endl;

	int queries = 0;
	string que;
	for (;;) {
		cin >> que;
		if (!cin) wrong_answer("eof");
		if (que == "?") {
			queries++;
			if (queries > MAX_Q) wrong_answer("too many queries");
			vi inp(N);
			rep(i,0,N) cin >> inp[i];
			if (!cin) wrong_answer("eof2");
			rep(i,0,N) if (inp[i] <= 0 || inp[i] > N) wrong_answer("oob");
			string res(N, 'x');
			rep(i,0,N) res[i] = (char)('0' + (color[i] == color[inp[i] - 1]));
			cout << res << endl;
		} else if (que == "!") {
			int ans;
			cin >> ans;
			if (!cin) wrong_answer("eof3");
			if (ans == -1) {
				if (majority != -1) wrong_answer("wa: answered -1 but there was a majority");
			} else {
				if (ans <= 0 || ans > N) wrong_answer("wa: oob answer");
				int val = color[ans - 1];
				if (val != majority) wrong_answer("wa: item at pos %d was %d, but majority is %d", ans, val, majority);
			}
			break;
		} else {
			wrong_answer("bad query type");
		}
	}
	if (cin >> que) wrong_answer("expected eof");
	judge_message("%d queries", queries);
	accept_with_score(queries);
}

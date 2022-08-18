/* @EXPECTED_GRADES@ AC WA WA WA WA */
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int W, H, xs1, ys1, xd1, yd1, xs2, ys2, xd2, yd2;

int dist(pii a, pii b) { return abs(a.first - b.first) + abs(a.second - b.second); }
int dir(int coord, int goal) { return (coord < goal) - (coord > goal); }

bool within(int l, int m, int r) {
    if (l == m) return true;
    if (dir(l, m) != dir(l, r)) return false;
    if (abs(l - m) > abs(l - r)) return false;
    return true;
}

void move(int& coord, int goal, int steps) {
    assert(steps <= abs(coord - goal));
    coord += steps * dir(coord, goal);
}

void shift(pii& start, pii& dest, int moves) {
    if (start.first == dest.first) move(start.second, dest.second, moves);
    else move(start.first, dest.first,moves);
}

bool crossing(int xs1, int ys1, int yd1, int xs2, int ys2, int xd2) {
    int t1 = abs(xs2 - xs1), t2 = abs(ys1 - ys2);
    if (t1 > abs(ys1 - yd1) || t1 > abs(xs2 - xd2)) return false;
    move(ys1, yd1, t1);
    move(xs2, xd2, t1);
    return xs1 == xs2 && ys1 == ys2;
}

bool line(int ys1, int yd1, int ys2, int yd2) {
    int timetocoll = abs(ys1 - ys2) / 2;
    if (timetocoll > min(abs(ys1 - yd1), abs(ys2 - yd2))) return false;
    move(ys1, yd1, timetocoll);
    move(ys2, yd2, timetocoll);
    return ys1 == ys2;
}

bool intersects(pair<pii, pii> a, pair<pii, pii> b, int ashift, int bshift) {
    if (ashift > dist(a.first, a.second) || bshift > dist(b.first, b.second)) return false;
    shift(a.first, a.second, ashift);
    shift(b.first, b.second, bshift);

     if (a.first.second == a.second.second && b.first.second == b.second.second)
        return a.first.second == b.first.second && line(a.first.first, a.second.first, b.first.first, b.second.first);
     else if (a.first.first == a.second.first && b.first.second == b.second.second)
        return crossing(a.first.first, a.first.second, a.second.second, b.first.first, b.first.second, b.second.first);
     else
         return crossing(b.first.first, b.first.second, b.second.second, a.first.first, a.first.second, a.second.first);
}

bool collides(vector<pair<pii, pii>> a, vector<pair<pii, pii>> b) {
    int t1 = dist(a[0].first, a[0].second),
        t2 = dist(b[0].first, b[0].second);
    if (t1 > t2) {
        swap(a, b);
        swap(t1, t2);
    }
    return intersects(a[0], b[0], 0, 0) || intersects(a[1], b[0], 0, t1) || intersects(a[1], b[1], t2 - t1, 0);
}

bool mustCrash() {
    vector<pair<pii, pii>> xy1 = {make_pair(pii(xs1, ys1), pii(xd1, ys1)), make_pair(pii(xd1, ys1), pii(xd1, yd1))};
    vector<pair<pii, pii>> xy2 = {make_pair(pii(xs2, ys2), pii(xd2, ys2)), make_pair(pii(xd2, ys2), pii(xd2, yd2))};
    vector<pair<pii, pii>> yx1 = {make_pair(pii(xs1, ys1), pii(xs1, yd1)), make_pair(pii(xs1, yd1), pii(xd1, yd1))};
    vector<pair<pii, pii>> yx2 = {make_pair(pii(xs2, ys2), pii(xs2, yd2)), make_pair(pii(xs2, yd2), pii(xd2, yd2))};
    return collides(xy1, xy2) && collides(xy1, yx2) && collides(yx1, xy2) && collides(yx1, yx2);
}

void fixSameDir() {
    if (within(xs1, xs2, xd1) && (dir(xs1, xd1) == dir(xs2, xd2) || !dir(xs2, xd2))) {
        int mmoves = min(abs(xs1 - xs2), min(abs(ys2 - yd2), abs(xs1 - xd1)));
        move(xs1, xd1, mmoves);
        move(ys2, yd2, mmoves);
    }
    if (within(xs2, xs1, xd2) && (dir(xs1, xd1) == dir(xs2, xd2) || !dir(xs1, xd1))) {
        int mmoves = min(abs(xs1 - xs2), min(abs(ys1 - yd1), abs(xs2 - xd2)));
        move(xs2, xd2, mmoves);
        move(ys1, yd1, mmoves);
    }
}

bool mayCrash() {
    fixSameDir();
    swap(xs1, ys1);
    swap(xs2, ys2);
    swap(xd1, yd1);
    swap(xd2, yd2);
    fixSameDir();

    if (xs1 < xs2 && (dir(xs1, xd1) != 1 || dir(xs2, xd2) != -1)) return false;
    if (xs1 > xs2 && (dir(xs1, xd1) != -1 || dir(xs2, xd2) != 1)) return false;
    if (ys1 < ys2 && (dir(ys1, yd1) != 1 || dir(ys2, yd2) != -1)) return false;
    if (ys1 > ys2 && (dir(ys1, yd1) != -1 || dir(ys2, yd2) != 1)) return false;

    int needx = abs(xs1 - xs2), needy = abs(ys1 - ys2);
    int hasx1 = abs(xs2 - xd2), hasx2 = abs(xs1 - xd1);
    int hasy1 = abs(ys2 - yd2), hasy2 = abs(ys1 - yd1);
    int selfx1 = needx - hasx2 * 2, selfx2 = needx - hasx1 * 2;
    int selfy1 = needy - hasy2 * 2, selfy2 = needy - hasy1 * 2;

    if (needx > hasx1 + hasx2 || needy > hasy1 + hasy2) return false;
    if (selfx1 > needy || selfx2 > needy) return false;
    if (selfy1 > needx || selfy2 > needx) return false;
    return true;
}

void solve() {
    cin >> W >> H;
    cin >> xs1 >> ys1 >> xd1 >> yd1 >> xs2 >> ys2 >> xd2 >> yd2;

    if (xd1 == xd2 && yd1 == yd2) {
        cout << "IMMINENT DISASTER" << endl;
        return;
    }

    if (dist(pii(xs1, ys1), pii(xd1, yd1)) < dist(pii(xs2, ys2), pii(xd2, yd2))) {
        swap(xs1, xs2);
        swap(ys1, ys2);
        swap(xd1, xd2);
        swap(yd1, yd2);
    }
    bool canCrash = within(xs1, xd2, xd1) && within(ys1, yd2, yd1) && dist(pii(xs1, ys1), pii(xd2, yd2)) >= dist(pii(xs2, ys2), pii(xd2, yd2));
    bool canAvoid = !canCrash || (xs1 != xd1 && ys1 != yd1);

    if ((xs1 + ys1)%2 == (xs2 + ys2)%2) {
        canAvoid &= !mustCrash();
        canCrash |= mayCrash();
    }

    if (canCrash && canAvoid) cout << "MAYHEM POSSIBLE" << endl;
    else if (canCrash && !canAvoid) cout << "IMMINENT DISASTER" << endl;
    else if (!canCrash && canAvoid) cout << "CRISIS AVERTED" << endl;
    else assert(false && "can't crash and can't avoid???");
}

int main(int argc, char** argv) {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

    int TC = 0;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        if (i%100000 == 0) cerr << i << " ";
        solve();
    }
}

#include <bits/stdc++.h>
#include "validate.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

void check_case(int score, bool partial){
    int N, M;
    judge_in >> N >> M;
    rep(i,0,M) {
        int ig;
        judge_in >> ig >> ig;
    }
    int Q;
    judge_in >> Q;

    bool correct = true;
    bool factor2 = true;
    rep(i,0,Q) {
        int ans;
        judge_ans >> ans;
        int team_ans;
        if (!(author_out >> team_ans)) wrong_answer("Could not read query %d", i);

        if (correct && ans != team_ans) {
            judge_message("First fail query %d: got %d, wanted %d\n", i, team_ans, ans);
            correct = false;
        }
        if (factor2 && ans != -1 && !(team_ans <= ans && ans <= team_ans * 2)) {
            judge_message("First non-factor 2 query %d: got %d, wanted %d\n", i, team_ans, ans);
            factor2 = false;
        }
    }

    string trash;
    if (author_out >> trash) {
        wrong_answer("Trailing output\n");
    }

    if (correct) accept_with_score(score);
    else if (partial && factor2) accept_with_score(score / 2);
    else wrong_answer("Incorrect answer (partial allowed: %d)\n", partial);
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    int score = 0;
    bool partial = false;
    if (argc >= 5) score = stoi(argv[4]); 
    if (argc >= 6) partial = true;

    check_case(score, partial);
    return 0;
}

#!/usr/bin/env python3

import sys

def first_error(verdicts):
    for verdict in verdicts:
        if verdict != 'AC':
            return verdict
    return 'AC'

try:
    sample = "sample" in sys.argv
    data = sys.stdin.read().split()
    verdicts = data[0::2]
    scores = list(map(float, data[1::2]))
    assert len(verdicts) == len(scores)
    verdict = first_error(verdicts)
    max_queries = max(scores + [0])
    if verdict == 'AC':
        if sample:
            score = 0
        elif max_queries <= 3:
            score = 115
        elif max_queries == 4:
            score = 100
        elif max_queries == 5:
            score = 80
        elif max_queries <= 9:
            score = 40 + (9 - max_queries) * 7
        elif max_queries <= 18:
            score = 20 + (18 - max_queries) * 2
        else:
            score = 0
            verdict = 'WA'
    else:
        score = 0
    print('%s %f' % (verdict, score))
except Exception:
    print('JE 0')


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
            score = 30
        elif max_queries <= 10:
            score = 20
        elif max_queries <= 30:
            score = 10
        else:
            score = 0
            verdict = 'WA'
    else:
        score = 0
    print('%s %f' % (verdict, score))
except Exception:
    print('JE 0')


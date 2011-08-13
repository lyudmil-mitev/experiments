#!/usr/bin/env python

def greatest_common_divisor(m,n):
    '''
       Euclid's algorithm for finding the
       greatest common divisor of m,n
    '''
    r = m % n
    if r == 0: return n
    else: return greatest_common_divisor(n, r)

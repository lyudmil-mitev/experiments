#!/bin/env python

def sqrt(number):
 '''
  A slow and naive sqrt implementation
  works for exact squares only
  (e.g. 4 16 36 121)
 '''
 m = 0
 if number < 0: raise ValueError("math domain error")
 while number > 0:
  number = number - (2*m + 1)
  m += 1
 if number != 0: return None
 return m

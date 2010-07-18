#!/usr/bin/env python2
import unittest
from random import randint
from sorting import *

class TestSortingAlgorithms(unittest.TestCase):
 def validate(self, data):
  '''
  Checks if a list is sorted
  '''
  for index in range(0, len(data)-1):
   if data[index] > data[index+1]: return False

  return True

 def randomlist(self, minsize=5, maxsize=1000):
  '''
  Create a random list of random integers
  '''
  size = randint(minsize, maxsize)
  return [ randint(0, 100) for item in range(0, size) ]

 def generic_test(self, algorithm, repeats=5):
  for repeat in range(0, repeats):
   data = self.randomlist()
   self.assertTrue(self.validate(algorithm(data)))
 
 def test_selection(self):
  self.generic_test(selection)

 def test_bubble(self):
  self.generic_test(selection)

 def test_insertion(self):
  self.generic_test(insertion)

 def test_merge(self):
  self.generic_test(merge)

 def test_bogo(self):
  data = self.randomlist(minsize=5, maxsize=6)
  self.assertTrue(self.validate(bogo(data)))

 def test_quick(self):
  self.generic_test(quick)

if __name__ == "__main__":
 suite = unittest.TestLoader().loadTestsFromTestCase(TestSortingAlgorithms)
 unittest.TextTestRunner(verbosity=1).run(suite)


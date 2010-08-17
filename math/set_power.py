from itertools import combinations
from functools import reduce

class set(set):
 '''
  Adds a method to compute the power (aka boolean) of the set
  it's somewhat limited because the builtin set class does not
  allow a set of sets
 '''
 def __repr__(self):
  result = "{"
  for element in self: result += str(element) + ", "
  result += "}"
  return result 
 def power(self):
  result = set()
  for step in range(1, len(self)+1):
   temp = combinations(self, step)
   result = result.union( temp )
  return list(map(set, result))

if __name__ == "__main__":
 test = set([1,2,3])
 print(test.power())

def largest_occurance_sum(sequence):
  '''
  A function that, given a list of integers returns the integer that has
  the highest total when you sum togeter all of the integer's appearances

  >>> largest_occurance_sum([1, 1, 1, 2])
  1
  >>> largest_occurance_sum([1, 2, 1, 1, 2])
  2

  If there are multiple integers with equivalent sums, return the integer which is larger:
  >>> largest_occurance_sum([1, 1, 3, 1])
  3

  '''
  occurance_map = {}
  for number in sequence:
    if number in occurance_map.keys():
       occurance_map[number] += 1
    else:
       occurance_map[number] = 1

  answer = 0 
  biggest = 0
  for number, value in occurance_map.items():
    if (number * value) > biggest:
       biggest = number * value
    if (number * value) == biggest:
       answer  = number if number > answer else answer

  return answer

if __name__ == "__main__":
  import doctest
  doctest.testmod()

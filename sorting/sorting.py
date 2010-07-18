#!/usr/bin/env python2
from copy import deepcopy
from random import randrange, shuffle

def selection(data):
 '''
 Probably the most naive sort. It is only useful in the rare cases when you're looking for a minimum number of swaps
 Complexity:
	Time: O(n^2)
	Space: O(1)
	Adaptive: NO
	Stable: NO
 '''
 data = deepcopy( data )
 for repeat in range(0, len(data)):
  for index, number in enumerate(data):
   if index < len(data)-1 and data[index] > data[index+1]:
    data[index], data[index+1] = data[index+1], data[index]
    
 return data

def bubble(data):
 '''
 The classic bubble sort
 Complexity:
	Time: O(n^2)
	Space: O(1)
	Adaptive: YES, O(n) when nearly sorted
	Stable: YES
 '''
 data = deepcopy( data )
 for repeat in range(0, len(data)-1):
  index = 0
  while(index < len(data) - 1):
   if data[index] > data[index + 1] :
    # Swap variables
    data[index], data[index + 1] = data[index + 1], data[index]
   index += 1
 return data

def insertion(data):
 '''
 The classic insertion sort
 Complexity:
	Time: O(n^2)
	Space: O(1)
	Adaptive: YES, O(n) when nearly sorted
	Stable: YES
 '''
 data = deepcopy( data )
 for repeat in range(0, len(data)):
  index = repeat
  while index > 0 and data[index] < data[index - 1]:
   data[index], data[index - 1] = data[index - 1], data[index]
   index -= 1 
 return data

def merge(data):
 '''
 Recursive merge sort
 '''
 data = deepcopy( data )
 if len(data) <= 1: return data
 left, right = [], []
 middle = len(data) // 2
 
 left = data[:middle]
 right = data[middle:]

 left = merge(left)
 right = merge(right)

 result = __merge(left, right)
 return result

def __merge(left, right):
 '''
 Sorts the contents of two lists
 '''
 result = []
 while len(left) > 0 and len(right) > 0:
  if left[0] < right[0]: result.append(left.pop(0))
  else: result.append(right.pop(0))
 
 if len(left) > 0: result += left
 elif len(right) > 0: result += right

 return result

def validate(data):
 '''
 Checks if a list is sorted
 '''
 for index in range(0, len(data)-1):
  if data[index] > data[index+1]: return False

 return True


def bogo(data):
 '''
 This is a joke sort
 works by shuffling the list until the order is right :)
 '''
 data = deepcopy( data )
 while( not validate(data) ):
  shuffle(data)
 return data

def quick(data):
 if data == []: return []
 else:
  pivot = data.pop(randrange(len(data)))
  lesser = quick([l for l in data if l < pivot])
  greater = quick([l for l in data if l >= pivot])
  return lesser + [pivot] + greater
 

 return data 

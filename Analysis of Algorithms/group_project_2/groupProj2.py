##!/usr/bin/python

# filename: groupProj1.py
# authors:  Dylan Camus, Braden Ackles, Mihai Dan
# date:     1/12/2016

import sys
import random
import string
import time
import numpy
import math
import itertools

def dynaLocker(n, m ,t, keys, balls):
   keys = sorted(keys)
   balls = sorted(balls)
   leftCount = 0
   rightCount = 0
   ballIndex = 0
   keyIndex = 1
   total = 0
   ballCount = 0
   if m == 1:
      total = balls[t - 1] - balls[0] + 1
      if keys[0] < balls[0]:
         total += balls[0] - keys[0]
      elif keys[0] > balls[t - 1]:
         total += keys[0] - balls[t - 1]
      return total
   leftKey = keys[0]
   rightKey = keys[1]
   if balls[0] < keys[0]:
      total = keys[0] - balls[0] + 1
      while balls[ballIndex] <= keys[0]:
	 ballIndex += 1
      leftKey = keys[0] + 1
   while True:
      if ballIndex == t:   # Check if all balls have been collected
         return total
      for i in range(rightKey - leftKey - 1):
	 if ballIndex + i < t:
	    if balls[ballIndex + i] < rightKey:
	       ballCount += 1
      if ballCount == rightKey - leftKey - 1 and balls[t - 1] >= rightKey and ballCount >= 2 and balls[ballIndex] != leftKey:
	 total -= 1
      ballCount = 0
      if balls[ballIndex] <= rightKey:   # Check if any balls are left in segment
         leftCount = abs(leftKey - balls[ballIndex]) + 1
         rightCount = abs(rightKey - balls[ballIndex]) + 1
         if rightCount <= leftCount:   # Compare number of lockers opened starting
	    total += rightCount        # from left with number of lockers starting from
	    leftCount = 0              # right. If the path starting from right is smaller,
	    rightCount = 0             # than this means all balls have been collected
	    keyIndex += 1              # in that segment
	    leftKey = rightKey + 1
	    while balls[ballIndex] <= rightKey:  # Count the number of balls left in segment
	       if ballIndex == t - 1:            # and add incrment the ballIndex to account
	          return total                   # for them. Also, check if all balls have
	       ballIndex += 1                    # been collected
	    if keyIndex == m:   # If this is last segment, check for balls after last key
	       total +=  balls[t - 1] - keys[m - 1]
               return total
	    else:
	       rightKey = keys[keyIndex]   # If not last segment, go to next segment
	 else:
	    total += leftCount              # Since rightCount > than leftCount in this case,
	    leftKey = leftKey + leftCount   # we add leftCount to the total and move the
	    ballIndex += 1                  # leftKey up, leaving the right key where it is
	    leftCount = 0
	    rightCount = 0
      else:                                 # In this case, there are no more balls left
         keyIndex += 1                      # in the segment, so go to next segment
         leftKey = rightKey
         if keyIndex == m:   # If this is last segment, check for balls after last key
	    total += balls[t - 1] - keys[m - 1] + 1
	    return total
         else:
	    rightKey = keys[keyIndex]

def evalSegment(pair, lockers):
   leftKey = 0
   leftCount = 0
   rightCount = 0
   total = 0
   length = pair[1] - pair[0]
   for i in range(0, length):
      if lockers[pair[0] + i] == 1:
	 leftCount = 1 + i - leftKey
	 rightCount = length - i - 1
         if leftCount < rightCount:
	    total += leftCount
	    leftKey += leftCount
         else:
	    total += rightCount
	    return total
   return total

def checkLeft(key, ball):
   if ball < key:
      return key - ball
   else:
      return 0

def checkRight(key, ball):
   if ball > key:
      return ball - key
   else:
      return 0

def enumLocker(n, m, t, keys, balls):
   minLockers = n
   balls = sorted(balls)
   keys = sorted(keys)
   x = 0
   lockers = [0] * n
   for i in range(0, n):
      if x < t:
         if balls[x] - 1 == i:
	    lockers[i] = 1
	    x += 1
   for i in range(1, m + 1):
      for keySet in itertools.combinations(keys, i):
	 count = 0
	 segments = list()
	 if i == 1:
	    total = balls[t - 1] - balls[0] + 1
            if keySet[0] < balls[0]:
	       total += balls[0] - keySet[0]
            elif keySet[0] > balls[t - 1]:
	       total += keySet[0] - balls[t - 1]
            count = total
	 else:
	    count = i
	    for j in range(0, len(keySet) - 1):
               segments.append([keySet[j], keySet[j + 1]])
	    for pair in segments:
	       count += evalSegment(pair, lockers)
	    count += checkLeft(keySet[0], balls[0])
	    count += checkRight(keySet[i - 1], balls[t - 1])
	 minLockers = min(minLockers, count)
   return minLockers

print "Enumeration answers\n"

print "%d" % enumLocker(19, 9, 10, [5, 2, 18, 16, 9, 12, 17, 15, 6], [5, 19, 2, 6, 16, 14, 7, 17, 15, 9])
print "%d" % enumLocker(14, 4, 14, [2, 6, 1, 12], [8, 2, 7, 14, 13, 5, 12, 10, 11, 4, 1, 3, 9, 6])
print "%d" % enumLocker(10, 9, 7, [1, 5, 10, 4, 8, 2, 9, 3, 7], [7, 10, 6, 1, 2, 4, 8])
print "%d" % enumLocker(16, 3, 14, [7, 14, 2], [16, 6, 15, 4, 13, 2, 1, 12, 10, 3, 8, 14, 9, 7])
print "%d" % enumLocker(19, 5, 17, [14, 6, 13, 5, 4], [3, 10, 1, 13, 6, 14, 8, 17, 11, 5, 7, 12, 19, 4, 18, 16, 2])
print "%d" % enumLocker(12, 6, 1, [4, 5, 8, 12, 10, 3], [10])
print "%d" % enumLocker(18, 18, 15, [6, 10, 7, 18, 12, 14, 3, 11, 4, 1, 17, 2, 9, 15, 8, 5, 16, 13], [15, 2, 14, 3, 8, 6, 17, 1, 7, 11, 10, 5, 18, 9, 13])
print "%d" % enumLocker(14, 12, 8, [14, 13, 11, 1, 3, 4, 7, 9, 8, 6, 2, 5], [8, 6, 2, 12, 9, 11, 7, 13])

print "\nDynamic answers\n"

arr1 = "82 5 94 47 21"
arr2 = "51 70 21 11 1 31 9 93 76 65 38 92 20 81 45 32 63 2 23 55 40 64 4 73 97 84 42 83 90 43 18 100 27 52 50 15 85 5 94 96 54 79 25 36 102 34 89 17 69 26 77 80 12 67 14 47 62 103 101 74 29 41 60 87 19 16 3 24 6 7 61 44 95 88 72 28 78 48 75"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(104, 5, 79, arr1, arr2)

arr1 = "84 6 2 54 24 99 29 35 56 12 27 26 7 93 46 32 64 37 75 4 71 81 68 48 49 92 96 94 23 11 97 9 86 14 50 15 69 38 91 13 65 5 34 36 85 40 30 83 60 59 77 101 41 8 66 76 28 90 25 89 53 18 43 74 72 62 61 70 17"
arr2 = "86 55 94 54 82 31 69 68 62 20 10 48 93 76 56 59 50"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(102, 69, 17, arr1, arr2)

arr1 = "38 30 92 77 36 28 85 14 89 17 57 82 13 97 1 68 55 42 49 62 27 84 26 18 100 16 71 91 102 3 78 53 31 64 81 48 11 33 29 90 20"
arr2 = "80 22 10 5 59 37 63 104 87 73 88 83 17 96 39 50 51 92 1 44 52 102 58 100 9 53 67 43 3 60 97 25 76 24 30 48 27 77 49 23 95 28 85 62 15 35 12 72 55 99 78 79 11 105 57 45 68 13"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(105, 41, 58, arr1, arr2)

arr1 = "59 19 36 76 78 96 3 81 61 85 10 48 103 14 100 87 35 29 67 80 43 65 68 70 15 30 26 69 21 60 62 74 20 88 4 5 91 9 49 77 18 7 71 47 64 39 95 28 53 82 89 92 93 72 83 79 31 56 2 16 8 58 50 12 37 45 32 94 55 75 22 102 23 63 73 40 54 44 11 25 86 66 97 34 13 52 98 41 51 24 38 1 6 84 99 90 101 104 17 27 33 57 46 42"
arr2 = "58 94 71 30 92 4 75 29 87 96 24 49 83 68 91 44 54 17 73 76 46 41 103 33 97 101 25 34 53 26 16"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(104, 104, 31, arr1, arr2)

arr1 = "40 56 12 54 87 65 96 1 81 97 16 36 33 24 51 82 66 67 75 93 46 15 17 41 19 102 32"
arr2 = "8 97 67 73 14 57 16 86 50 89 18 27 26 33 92 35 96 78 53 60 5 12 6 51 46 107 59 23 87 66 82 2 15 13 91 83 93 100 103 37 88 74 11 45 98 85 101 19 104 65 3 32 72 95 106 79 61 84 81 29 68 75 102 43 63 36 56 94 77 31 52 80 28 49 40 48 99 58 76 20 41 71 10 1 39 70 69 9 34 44 38 47 62 42 30 25 54 7 24 21 22 64"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(107, 27, 102, arr1, arr2)

arr1 = "86 42 98 96 78 91 38 67 16 87 70 25 73 29 41 32 57 35 6 68 17 100 15 105 31 27 71 44 99 7 79 48 18 55 89 60 28 97 20 77 103 90 9 26 61 104 2 5 62 63 81 102 106 84 46 34 45 51 69 39 21 49 10 101 40 14 33 30 92 4 75 37 11 64 47 59 13 66 82"
arr2 = "74 101 22 88 73 99 41 10 30 35 68 104 1 85 89 40 71 96 57 76 17 27 95 48 37 103"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(106, 79, 26, arr1, arr2)

arr1 = "61 1 32 17 40 57 55 23 106 54 82 8 100 44 9 101 59 84 94 49 92 34 35 33 16 48 31 26 60 45 3 38 50 105 87 36 43 96 75 4 79 47 85 13 29 14 37 80 81 67 56 97 24 27 91 58 53 77 52 88 7 107 15 90 71 109 70 64 2 18 10 46 12 25 76 78 62 22 39 19 66 95 63 11 73 99 108 74 5 103 98 28 104 6 21 86 30 102 72 68 83 20 41 42 51 65 93 89"
arr2 = "8 33 107 72 35 37 41 7 32 103 34 79 15 18 25 6 59 94 76 58 106 52 50 23 48 83 90 53 102 31 5 85 36 77 61 78 108 21 12 54 56 80 74 64 14 75 96 3 39 43 100 17 60 2 16 87 20 62 55 65 63 38 4 92 73 49 88 98 42 1 11 51 40 70 99 68 66 28 93 91 71 101 109 24 30 67 27"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(109, 108, 87, arr1, arr2)

arr1 = "81 5 44 53 30 93 76 97 59 98 10 74 95 27 90 46 35 11 94 19 70 77 32 80 40 48 7 58 24 39 26 31 36 45 2 33 103 88 41 25 92 86 104 37 12 20 49 63 78 4 69 73 22 105 87 61 42 43 23 72 85 84 64 68 83 89 28 8 34 60 100 1 108 101 91 47 15 107 3 50 99 66 52 62 16 38 13 17 14 79 71 9 102 65 54 6 51 67 29 82 55 106 18"
arr2 = "56 45 25 72 33 10 87 76 52 31 73 79 92 94 23 42 21 57 41 39 67 46 81 107 18 62 13 9 93 19 27 85 69 78 34 63 5 83 98 84 2 3 40 89 16 12 65 75 24 91 105 49 61 96 51 103 59 100 7 14 88 28 97 104 43 30 101 108 15 99 4 50 66 54 8 53 74 44 102 37 71"
arr1 = map(int, arr1.split())
arr2 = map(int, arr2.split())
print "%d" % dynaLocker(108, 103, 81, arr1, arr2)

# About the project
This is a task that was given to me as part of a job interview. This is my solution, and I give no guarantee that it is correct, or efficient as was requested. This is merely my best effort at the time.

# Task
The questions should be answered in C++, in the most efficient way you can, all answers should be explained in detail.

Given an ordered array of distinct integer numbers, return an element whose value is equal to its index, or -1 if none is found with those conditions.

ex: [-3, 0, 2, 34] = 2, [1, 7, 9, 13] = -1

# Usage
The program can be used in 4 ways.

1. Calling the program with no parameters will make it generate an array of random numbers and perform the search on it.

   ex: `./FindArrayValueEqualIndex`

2. Piping a sequence of integers to the program will use that sequence as the array to be searched.

   ex: `echo -3, 0, 2, 34 | ./FindArrayValueEqualIndex`

3. Passing a list of numbers to the program as parameters will use them as the array to be searched.

   ex: `./FindArrayValueEqualIndex -3, 0, 2, 34`

4. You can also generate an array with random numbers with certain restrictions by making the first parameter alphanumeric, followed by 4 numbers: array length, lowest value, minimum step to next value, maximum step to next value.

   ex: `./FindArrayValueEqualIndex set 100 -100 1 5`

# Thought process and ideas
## Search
We are given an ordered array, hence we can use binary search, giving us a worst case runtime of O(log n).

We do not compare to a constant value in our search, so we cannot use the std::binary_search algorithm.

Because we have distinct integers that are sorted, this has 2 implications:

- We can only have more than one match if after the first match we have a sequence of mubers that increase by 1. However I don't see a way to exploit this fact, since we only need one match to fulfill the requirements, and any of those values would do.
- If the last value is smaller than the last index, there is definitely no match in the array. The same is true if the first value is greater than 0. This means if we check the first and last values first, there are cases when we can return -1 right away and skip the rest of the algorithm.

No negative value can give a match, because array indices are always positive. So if we had the position of the first non-negative number, we could reduce the input size when passing the array to the search algorithm. However we do not get it, and finding that first would not be any more efficient than running binary search on the entire array.

## Intersecting lines
Another way to view this task would be as a search for an intersection point of 2 functions, where one is fi(x)=x (representing the indices), and the other one is a strictly monotonously growing function with the slope at all points being >=1 (representing the values, let's call it fv(x)), the formula for which we do not know.

We could take a line l connecting 1st and last point of fv in the interval, calculate the intersecting point p between l and fi, and use round(p.x) for determining the new interval in the same fashion as with binary search.

Assuming large enough arrays with equally likely random numbers, the value function fv(x) will be very close to a straight line with just a bit of statistical noise. In this case the first line l we draw would already end up intersecting close to the intersection of fi and fv, so this algorithm would converge on that point in very few steps. With a different distribution though (for example one where fi and fv run parallel for most of the distribution, and only jump to intersect close to the beginning or the end of the interval), this would result in O(n) runtime. Combined with the increased computational cost in each step with this algorithm, this is unlikely to be an improvement without additional information about the distribution of the values.

## Conclusion
Considering that we do not know the statistical distribution of the values or the size of the array, the safest bet would be binary search with a few checks for easy edge cases.

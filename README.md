# ClosestPairs
Various methods of solving the [closest pairs problem](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1186).

## Method 1: Divide and Conqquer
The first approach to solving the  is a divide and conquer approach. This approach achieves a time complexity of O(nlog(n)) by using basic computational geometry to rule out many of the possibilities. This approach is implemented in *working.cpp*.


## Method 2: L-R Heuristic
The second approach to solving the closest pair problem is a left to right heuristic where we compute the distance between the two left most points and proceed right, recalculating is the x distance is less than the closest previous distance. This approach is implemented in *alternate.cpp*.

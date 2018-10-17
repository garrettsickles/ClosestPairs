Given a set of points in a two dimensional space, you will have to  nd the distance between the closest
two points.

Input
The input  le contains several sets of input.
Each set of input starts with an integer N (0 <= N <= 10000),
which denotes the number of points in this set.
The next N line contains the coordinates of N two-dimensional points.
The first of the two numbers denotes the X-coordinate and the latter denotes the
Y-coordinate. The input is terminated by a set whose N = 0.
This set should not be processed.
The value of the coordinates will be less than 40000 and non-negative.

Output
For each set of input produce a single line of output containing a  oating point number (with four
digits after the decimal point) which denotes the distance between the closest two points. If there is
no such two points in the input whose distance is less than 10000, print the line INFINITY.

Sample Input
3
0 0
10000 10000
20000 20000
5
0 2
6 67
43 71
39 107
189 140
0

Sample Output
INFINITY
36.2215

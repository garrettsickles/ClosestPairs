#include <math.h>
#include <stdio.h>
#define MAX_DISTANCE 10000.0001
#define SIZE 40000

using namespace std;

struct point
{
	double x,y;
};

point points[SIZE];
int count, right, left;
double d = MAX_DISTANCE;
double temp = MAX_DISTANCE;

inline double area(const point& l, const point& r) { return ((l.x-r.x)*(l.x-r.x))+((l.y-r.y)*(l.y-r.y)); }
inline void swap(point* l, point* r) {
	point p = *l;
	*l = *r;
	*r = p;
}

void quickSort(int l, int r)
{
	int i = l;
	int j = r;
	point buffer;
	point pivot = points[(l+r)/2];
	while(i <= j) {
		while(points[i].x < pivot.x) i++;
		while(points[j].x > pivot.x) j--;
		if(i <= j) swap(points[i++], points[j--])
	}
	if(l < j) sortPointsX(l, j);
	if(i < r) sortPointsX(i, r);
}

void findClosestPair()
{
	if(count<2)
		return;
	sortPointsX(0,count-1);
	d = sqrt(distSq(points[0],points[1]));

	for(right=1; right<count; right++) {
		for(left=right-1; l>=0 && points[left].x>points[right].x-delta; l--) {
			if(points[left].y<points[right].y+delta && points[left].y>points[right].y-delta) {
				temp=distSq(points[right],points[l]);
				if(temp<delta*delta)
				{
					delta=sqrt(temp);
				}
			}
		}
	}
}

int main()
{
	int i;
	while(true)
	{
		delta = SIZE;
		scanf("%d", &lenPoints);
		if(!lenPoints)
			break;

		for(i=0; i<lenPoints; i++)
		{
			scanf("%lf", &points[i].x);
			scanf("%lf", &points[i].y);
		}
		findClosestPair();

		if(delta>=SIZE)
		{
			printf("%s","INFINITY\n");
		}
		else
		{
			printf("%.4lf\n",delta);
		}
	}
	return 0;
}

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM_POINTS 40000

double	points[MAX_NUM_POINTS][2];

#define X_DISPLACEMENT(LEFT,RIGHT) (points[LEFT][0]-points[RIGHT][0])
#define Y_DISPLACEMENT(LEFT,RIGHT) (points[LEFT][1]-points[RIGHT][1])

#define SQUARE(VALUE) (VALUE*VALUE)

#define HYPOTENUSE_AREA(LEFT,RIGHT) (SQUARE(X_DISPLACEMENT(LEFT,RIGHT))+SQUARE(Y_DISPLACEMENT(LEFT,RIGHT)))
#define HYPOTENUSE_LENGTH(LEFT,RIGHT) sqrt(HYPOTENUSE_AREA(LEFT,RIGHT))

double MAX_DISTANCE = 10000.0;

int point_count;
int right, left;
double buffer[2];
double hyp_buffer;
double hyp_area;
double hyp_length;


void swap_points(int l, int r)
{
	buffer[0]	=	points[l][0];
	buffer[1]	=	points[l][1];
	points[l][0]	=	points[r][0];
	points[l][1]	=	points[r][1];
	points[r][0]	=	buffer[0];
	points[r][1]	=	buffer[1];
}

void quicksort(int l, int r)
{
	int i = l;
	int j = r;

	double pivot = points[(l+r)/2][0];

	while(i <= j)
	{
		while(points[i][0] < pivot) i++;
		while(points[j][0] > pivot) j--;
		if(i <= j) swap_points(i++, j--);
	}

	if(l < j) quicksort(l, j);
	if(i < r) quicksort(i, r);
}

void find_closest_pair()
{
	hyp_length = MAX_DISTANCE;
	hyp_area = SQUARE(MAX_DISTANCE);

	if(point_count < 2) return;
	else
	{
		quicksort(0, point_count-1);
		for(right = 1; right < point_count; right++)
		{
			for(left = right-1; left >= 0 && points[left][0] > (points[right][0] - hyp_length); left--)
			{
				if(points[left][1] < (points[right][1] + hyp_length) && points[left][1] > (points[right][1] - hyp_length)) {
					hyp_buffer = HYPOTENUSE_AREA(left, right);
					if(hyp_buffer < hyp_area)
					{
						hyp_area = hyp_buffer;
						hyp_length = sqrt(hyp_buffer);
					}
				}
			}
		}
	}
}

int main()
{
	int i;

#ifdef ONLINE_JUDGE
	while(1)
	{
		scanf("%d", &point_count);

		if(point_count == 0) break;

		for(i = 0; i < point_count; i++) scanf("%lf %lf", &points[i][0], &points[i][1]);
	}
#else
	FILE *file;
	char filename[15];
	printf("Enter Input Filename (15 Characters Max) or RANDOM for random input: ");
	scanf("%s", filename);

	if(strcmp(filename, "RANDOM") == 0)
	{
		time_t t;
		srand((unsigned)time(&t));

		printf("How many points?\n");
		scanf("%d", &point_count);

		for(i = 0; i < point_count; i++)
		{
			points[i][0] = ((double)(rand())/(double)(RAND_MAX))*20000.0 + ((double)(rand())/(double)(RAND_MAX))*20000.0+((double)(rand())/(double)(RAND_MAX));
			points[i][1] = ((double)(rand())/(double)(RAND_MAX))*20000.0 + ((double)(rand())/(double)(RAND_MAX))*20000.0+((double)(rand())/(double)(RAND_MAX));
		}
	}
	else
	{
		if((file = fopen(filename,"r")) == NULL)
		{
			printf("\nInvalid Filename, \'%s\'...\nNow Exiting!\n\n", filename);
			return 0;
		}
		while(1)
		{
			fscanf(file, "%d", &point_count);
			if(point_count == 0) break;
			for(i = 0; i < point_count; i++) fscanf(file, "%lf %lf", &points[i][0], &points[i][1]);
		}
	}
#endif
	find_closest_pair();
	if(hyp_length >= MAX_DISTANCE) printf("%s","INFINITY\n");
	else printf("%.4lf\n", hyp_length);
	return 0;
}

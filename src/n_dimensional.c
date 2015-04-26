#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM_POINTS 40000

#define X_INDEX 		0
#define Y_INDEX 		1
#define CARDINALITY 	2

double 	MAX_DISTANCE	= 10000.0;
double	points[MAX_NUM_POINTS][CARDINALITY];

#define MIN(A, B)		(B < A ? B : A)
#define MAX(A, B)		(B > A ? B : A)
#define SQUARE(VALUE)	(VALUE * VALUE)


double rand_double(double max, int prec)
{
	int d = RAND_MAX;
	int i = 0;
	double coefficient;
	double num = 0.0;

	while(d != 0) {
		d /= 10;
		++i;
	}
	coefficient = pow(10, i - 1);
	num += ((double)(rand())/(double)(RAND_MAX)) * coefficient;
	return num;
}


inline double displacement(int l, int r, double** _points, int index)
{
	return _points[r][index] - _points[r][index];
}

double area(int l, int r, double** _points, int card)
{
	double a = 0.0;
	for(int i = 0; i < card; i++) a += SQAURE(displacement(l, r, _points, i));
	return a;
}

double length(int l, int r, double** _points, int card)
{
	return sqrt(area(l, r, _points));
}

void swap_points(int l, int r, double** _points, int card)
{
	double buffer;
	for(int i = 0; i < card; i++)
	{
		buffer = _points[l][i];
		_points[l][i] = _points[r][i];
		_points[r][i] = buffer;
	}
}

void quicksort_points(int l, int r, double** _points, int index)
{
	int i = l;
	int j = r;
	double pivot = points[(l+r)/2][index];

	while(i <= j)
	{
		while(points[i][index] < pivot) i++;
		while(points[j][index] > pivot) j--;
		if(i <= j) swap_points(i++, j--, _points);
	}

	if(l < j) quicksort_points(l, j, _points, index);
	if(i < r) quicksort_points(i, r, _points, index);
}

double heuristic(int start, int end, double** _points, int index, int card)
{
	int i		= 0;
	int right 	= 0;
	int left 	= 0;
	int	size	= end - start + 1;

	double 	hyp_buffer 	= 0.0;
	double 	hyp_length 	= MAX_DISTANCE;
	double 	hyp_area	= SQUARE(MAX_DISTANCE);

	if(size < 2);
	else if(size == 2) hyp_length = length(start, end, _points);
	else
	{
		quicksort_points(start, end, _points, index);
		for(right = start; right <= end; right++)
		{
			for(left = right-1; left >= 0 && _points[left][index] > (_points[right][index] - hyp_length); left--)
			{
				for(i = 0; i < card; i++)
					if(i != index)
						if(_points[left][i] >= (_points[right][i] + hyp_length) || _points[left][i] <= (_points[right][i] - hyp_length))
							break;
				if(i == card)
				{
					hyp_buffer = area(left, right, _points);
					if(hyp_buffer < hyp_area)
					{
						hyp_area = hyp_buffer;
						hyp_length = sqrt(hyp_buffer);
					}
				}
			}
		}
	}
	return hyp_length;
}

double exhaustive(int start, int end, double** _points, int card)
{
	int i		= 0;
	int j		= 0;
	int size 	= end - start + 1;

	double hyp_area = SQUARE(MAX_DISTANCE);

	if(size < 2);
	else if(size == 2) hyp_area = area(0, 1, _points, card);
	else
		for(i = start; i < size; i++)
			for(j = start; j < size; j++)
				if(i != j)
					hyp_area = MIN(hyp_area, area(i, j, _points, card));
	return sqrt(hyp_area);
}

double divide_and_conquer(int start, int end, double** _points, int card)
{
	int i 		= 0;
	int j 		= 0;
	int size 	= end - start + 1;

	double length = 0.0;

	double ***sorted_points = (double***)malloc(card * sizeof(double**));

	for(i = 0; i < card; i++)
	{
		sorted_points[i] = (double**)malloc(size * sizeof(double*));
		for(j = 0; j < size; j++) sorted_points[i][j] = (double*)malloc(sizeof(double));
	}

	for(i = 0; i < card; i++)
		for(j = 0; j < size; j++)
			memcpy(sorted_points[i][j], _points[j], card * sizeof(double));

	for(i = 0; i < card; i++)
		quicksort_points(start, end, sorted_points[i], i);

	//length = divide_and_conquer_recursive(start, end, sorted_points);

	for(i = 0; i < card; i++)
	{
		for(j = 0; j < size; j++) free(sorted_points[i][j]);
		free(sorted_points[i]);
	}
	free(sorted_points);

	return(length);
}

double find_closest_pair()
{
	return 0.0;
}

int main()
{
	int i = 0;
	int j = 0;
	int point_count = 0;
	int card = 0;
	double hyp_length = MAX_DISTANCE;

#ifdef ONLINE_JUDGE
	while(1)
	{
		scanf("%d", &point_count);
		scanf("%d", &card);
		if(point_count == 0) break;
		else
			for(i = 0; i < point_count; i++)
				for(j = 0; j < card; j++)
					scanf("%lf", &points[i][j]);
		hyp_length = find_closest_pair();
		if(hyp_length >= MAX_DISTANCE) printf("%s","INFINITY\n");
		else printf("%.4lf\n", hyp_length);
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
		printf("What is the cardinality?\n");
		scanf("%d", &card);

		for(i = 0; i < point_count; i++)
			for(j = 0; j < card; j++)
			points[i][X_INDEX] = ((double)(rand())/(double)(RAND_MAX))*20000.0 + ((double)(rand())/(double)(RAND_MAX))*20000.0+((double)(rand())/(double)(RAND_MAX));
			points[i][Y_INDEX] = ((double)(rand())/(double)(RAND_MAX))*20000.0 + ((double)(rand())/(double)(RAND_MAX))*20000.0+((double)(rand())/(double)(RAND_MAX));
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
			for(i = 0; i < point_count; i++) fscanf(file, "%lf %lf", &points[i][X_INDEX], &points[i][Y_INDEX]);
			hyp_length = find_closest_pair();
			if(hyp_length >= MAX_DISTANCE) printf("%s","INFINITY\n");
			else printf("%.4lf\n", hyp_length);
		}
	}
#endif
	return 0;
}

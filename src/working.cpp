//
//  main.cpp
//  ClosestPairs
//
//  Created by Garrett Frank Sickles on 1/21/15.
//  Copyright (c) 2015 Garrett Frank Sickles. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

const double INVALID_DIST = 10000.0001;
const double INVALID_AREA = 100000002.0;

struct point {
    double x;
    double y;
};

inline double min(double a, double b) {return a < b ? a : b;}
inline bool compare_y(point& l, point& r) {return (l.y)<(r.y);}
inline bool compare_x(point& l, point& r) {return (l.x) < (r.x);}
inline double distance(point& l, point& r) {return sqrt((l.x-r.x)*(l.x-r.x)+(l.y-r.y)*(l.y-r.y));}
inline double area(point& l, point& r) {return (l.x-r.x)*(l.x-r.x)+(l.y-r.y)*(l.y-r.y);}


double closest_pair_exhaustive(point* v, unsigned int size) {
    if(size == 1) return INVALID_AREA;
    else if(size == 2) return area(v[0], v[1]);
    else {
        double d = INVALID_AREA;
        for(unsigned int i = 0; i < size; i++)
            for(unsigned int j = 0; j < size; j++)
                if(i != j) d = min(d, area(v[i], v[j]));
        return d;
    }
}


double closest_pair_recursive(unsigned int s, unsigned int e, point* x, point* y) {
    double dist;
    unsigned int size = e-s+1;
    
    if(size <= 3) return closest_pair_exhaustive(x+s, size);
    else {
        unsigned int mid = (e-s)/2;
        double med = (x[mid+s].x + x[(size)/2+s].x)/2.0;
        double m;
        std::vector<point> l,r,ly,ry;
        l.reserve(size/2 + 1);
        r.reserve(size/2 + 1);
        ly.reserve(size/2 + 1);
        ry.reserve(size/2 + 1);
        for(unsigned int i = 0; i < size; i++) {
            if(y[i].x <= med) ly.push_back(y[i]);
            else ry.push_back(y[i]);
        }
        dist = min(closest_pair_recursive(s,mid+s,x,ly.data()), closest_pair_recursive(mid+s+1,e,x,ry.data()));
        for(unsigned int i = 0; i < size; i++) {
            m = y[i].x;
            if(m > (med - dist) && m <= med) l.push_back(y[i]);
            else if(m > med && m < (med + dist)) r.push_back(y[i]);
            else;
        }
        unsigned int lsize = l.size();
        unsigned int rsize = r.size();
        unsigned int j = 0;
        for(unsigned int i = 0; i < lsize; i++) {
            while(j < rsize && r.at(j).y < (l.at(i).y - dist)) j++;
            for(int k = 0; k < 5; k++) {
                if((j+k) < rsize) dist = min(dist, area(l.at(i), r.at(j+k)));
                else break;
            }
        }
    }
    return dist;
}

double closest_pair_dac(point* v, unsigned int n) {
    std::vector<point> vx(v, v+n);
    std::vector<point> vy(v, v+n);
    
    std::sort(vx.begin(), vx.end(), compare_x);
    std::sort(vy.begin(), vy.end(), compare_y);
    return(closest_pair_recursive(0, n - 1, vx.data(),vy.data()));
}


int main() {
    unsigned int n;
    double dist;
    point* buffer;
    scanf("%d", &n);
    while(n > 0) {
        buffer = new point[n];
        for(int i = 0; i < n; i++) {
            scanf("%lf", &(buffer[i].x));
            scanf("%lf", &(buffer[i].y));
        }
        dist = sqrt(closest_pair_dac(buffer, n));
        //dist = closest_pair_exhaustive(tmp.at(count).data(), tmp.at(count).size());
        
        if(dist <= 10000.0 && dist >= 0.0) printf("%.4f\n", dist);
        else printf("INFINITY\n");
        scanf("%d", &n);
    }
    /*
     for(int count = 0; count < tmp.size(); count++) {
     dist = sqrt(closest_pair_dac(tmp.at(count)));
     //dist = closest_pair_exhaustive(tmp.at(count).data(), tmp.at(count).size());
     
     if(dist <= 10000.0 && dist >= 0.0) printf("%.4f\n", dist);
     else std::cout << "INFINITY\n";
     }
     */
    return 0;
}

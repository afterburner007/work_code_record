#ifndef DISTANCE_H
#define DISTANCE_H


#include "fstream"
#include "string"
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include "wykobi_instantiate.hpp"
using namespace wykobi;



float distance_point_to_point(point2d<float> point1, point2d<float> point2);
float max_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4);
float min_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4);
bool collision_range(circle<float> circlemin, circle<float> circlemax, point2d<float> point);
float *solving_equations(float a, float b, float c);
point2d<float> *point_of_intersection(point2d<float> point1, point2d<float> point2, circle<float> circles);
point2d<float> intersection_segment_to_circle(point2d<float> pointd, point2d<float> pointc, circle<float> circles);
float angle(point2d<float> point, point2d<float> collision, point2d<float> intersection);
float get_mindistance_code(float Radius, int shiftpos, float wheelangle, point2d<float>* objpoints, int ObjNUM);
#endif;
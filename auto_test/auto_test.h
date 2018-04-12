#ifndef AUTO_TEST_H
#define AUTO_TEST_H


#include "wykobi_instantiate.hpp"
#include "iostream"
#include "fstream"
#include "string"
#include <vector>
#include <stdlib.h>
#include <sstream>
#include<math.h>
using namespace wykobi;
using namespace std;
typedef quadix<float, 2> Quadix;
bool quadix_in_quadix(Quadix quadix1, Quadix quadix2);
float area_quadix(Quadix quadix1);
float proportion(Quadix quadix1, Quadix quadix2, float accuracy);
#endif
#ifndef DECISION_MAKER_H
#define DECISION_MAKER_H
#include "Global.h"

#include <math.h>
#include <stdlib.h>

#ifndef PI
#define PI 3.14159265f
#endif

#ifndef EARTH_R
#define EARTH_R 6371.0f
#endif

float rad_convert(float coordinate);
float Distance_bt_2Point(char nmea_sentence[][20],struct my_fixed_halls *halls,char index);

#endif

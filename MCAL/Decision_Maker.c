#include "Decision_Maker.h"
#include "math.h"
#include <stdlib.h>
//calc_distance
 float rad_convert(float coordinate)
{
    int  coordinate_D;
    float coordinate_M;
    coordinate_D = (int)coordinate / 100;
    coordinate_M = coordinate - (float)coordinate_D * 100.0f;
    return ((coordinate_D + (coordinate_M / 60.0f)) * PI / 180.0f);
}
float Distance_bt_2Point(char nmea_sentence[][20],struct my_fixed_halls *halls,char index)
{
	
	  float lat_D  = 0.0f;
    float long_D = 0.0f;
    float fixed_lat = 0.0f;
    float a, angular_D;

    switch ((int)(index - '0')) {
    case 0:
        lat_D = halls->hall_0[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D = halls->hall_0[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat = halls->hall_0[0];
        break;
    case 1:
        lat_D = halls->hall_1[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D = halls->hall_1[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat = halls->hall_1[0];
        break;
    case 2:
        lat_D= halls->hall_2[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D = halls->hall_2[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat= halls->hall_2[0];
        break;
    case 3:
        lat_D = halls->hall_3[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D= halls->hall_3[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat= halls->hall_3[0];
        break;
    case 4:
        lat_D= halls->hall_4[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D= halls->hall_4[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat= halls->hall_4[0];
        break;
		case 5:
        lat_D = halls->hall_5[0] - rad_convert((float)atof(nmea_sentence[0]));
        long_D = halls->hall_5[1] - rad_convert((float)atof(nmea_sentence[1]));
        fixed_lat = halls->hall_5[0];
    }

    a= powf(sinf(lat_D * 0.5f), 2.0f)+ cosf(rad_convert((float)atof(nmea_sentence[0]))) * cosf(fixed_lat)* powf(sinf(long_D * 0.5f), 2.0f);
    angular_D = 2.0f * atan2f(sqrtf(a), sqrtf(1.0f - a));
    return (EARTH_R * angular_D);
}


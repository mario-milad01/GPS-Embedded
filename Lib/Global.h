#ifndef GLOBAL_H
#define GLOBAL_H

extern char gps[2][20];
struct my_fixed_halls {
    float hall_0[2];
    float hall_1[2];
    float hall_2[2];
    float hall_3[2];
    float hall_4[2];
   	float hall_5[2];
};
extern struct my_fixed_halls myHalls;
#endif

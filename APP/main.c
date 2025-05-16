#include "GPIO.h"
#include "UART.h"
#include "LCD_Driver.h"
#include "Systick.h"
#include "Decision_Maker.h"
#include "math.h"
#include "string.h"
#include "stdint.h"
#include <stdlib.h>
#include "GPS.h"
#include "Global.h"
//Main app code.
void nearest_hall(void)
{
    int   min_index = 0;
    float min_dis;
    int c;
    GPS_read();
    min_dis = Distance_bt_2Point(gps, &myHalls, '0');
    for (c = 1; c < 6; c++) {
        if (min_dis > Distance_bt_2Point(gps, &myHalls, ((char)c)) ){
            min_dis   = Distance_bt_2Point(gps, &myHalls, ((char)c));
            min_index = c;
        }
    }
    Lcd_display(((char)min_index));
}
	struct my_fixed_halls myHalls;
		char gps[2][20];
int main(void)
{
	
    myHalls.hall_0[0] = rad_convert((float)atof("30.064654"));
    myHalls.hall_0[1] = rad_convert((float)atof("31.280371"));
	
    myHalls.hall_1[0] = rad_convert((float)atof("30.064172"));
    myHalls.hall_1[1] = rad_convert((float)atof("31.280199"));
	
    myHalls.hall_2[0] = rad_convert((float)atof("30.06365"));
    myHalls.hall_2[1] = rad_convert((float)atof("31.28044"));
	
    myHalls.hall_3[0] = rad_convert((float)atof("30.063229"));
    myHalls.hall_3[1] = rad_convert((float)atof("31.279513"));
	
    myHalls.hall_4[0] = rad_convert((float)atof("30.063474,"));
    myHalls.hall_4[1] = rad_convert((float)atof("31.278262"));
	
		myHalls.hall_4[0] = rad_convert((float)atof("31.279513"));
    myHalls.hall_4[1] = rad_convert((float)atof("31.277598"));
    UART4_Init();
    SYSTICK_Init();
	  portC_Pin0_Init();
    while (1) {
			  BUZZER_ON ;
			  SYSTICK_Wait_seconds(2);
			  BUZZER_OFF;
        nearest_hall();
        SYSTICK_Wait_seconds(8);
    }
}

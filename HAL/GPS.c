#include "TM4C123GH6PM.h"
#include "Systick.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "GPS.h"
#include "UART.h"
#include "Decision_Maker.h"
#include "LCD_Driver.h"
#include "Global.h"

 void GPS_read(void)
{
    int  i = 0;
    int  k = 0;
    int  j;
    bool flag = true;
    char c;
    char GPS_logName[] = "$GPGGA,";

    do {
        flag = true;
        for (j = 0; j < 7; j++) {
            if (UART4_Receive() != GPS_logName[j]) {
                flag = false;
                break;
            }
        }

        if (flag) {
         
            i = 0;
            while (i < 2) {
                c = UART4_Receive();
                if (c == ',') { i++; }
            }

     
            k = 0;
            while ((c = UART4_Receive()) != ',') {
                if (k < 19) { gps[0][k++] = c; }
            }
            gps[0][k] = '\0';

     
            UART4_Receive();
            UART4_Receive();

  
            k = 0;
            while ((c = UART4_Receive()) != ',') {
                if (k < 19) { gps[1][k++] = c; }
            }
            gps[1][k] = '\0';
        }
    } while (!flag);
}


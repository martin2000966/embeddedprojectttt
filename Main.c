#include "../UART/UART.h"
#include "../GPIO/GPIO.h"
#include "../GPS/GPS.h"
#include "../SysTick/SYSTICK.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//#include "sevenSegment.h"
//char temp;

	
/*int main(){
	
	UART0_Init(9600);
	UART5_Init(9600);				
	while(1){
		temp = UART5_ReadChar();
		WriteUart0(temp);
	}
}*/
	
 double lat1=0,lon1=0 ,lat2=0 ,lon2=0;
 double remainDistance ;
 double totalDistance=0;
 int totcounter =0;     // to update the total distance 
int main(){
	
	//float remainDistance ;
	char flag=0; 
	//intialize lcd (law fih)(prt d)
    initPortF();
	  UART5_Init(9600);
	  UART0_Init(9600);   //only to track the data by my computer 
	


	//variables :
	//float lat1=0 ,lon1=0 ,lat2=0 ,lon2=0;
	       //0 not pressed --- 1 pressed and initialized (red) -----2  we re close(10m)(blue)---3 done (green)

	GPS_read(&lat2,&lon2);
	while (1){
		totcounter++;
		if (flag!= 0){
			lat1 = lat2;
			lon1 = lon2;
			GPS_read(&lat2,&lon2);
				if(totcounter%2 ==0){
				totalDistance += GPS_getDistance(lat1 ,lon1 ,lat2 , lon2); //update total distance every 10 cycles
					totcounter =0;
				}
				remainDistance = GPS_getDistance(lat2 ,lon2,3003.658254,3114.987874);
				if(remainDistance <10 && remainDistance>3){flag =2;}
				else if(remainDistance<5){flag=3;}
			}
			
		
		switch (flag){
			case 0 :    
				if(!(GPIO_PORTF_DATA_R&0x1)){   //assuming PDN
					flag=1;
					//LCD (unitialized )
				}
			break;

			case 1 :   //el distance >10m
				
				led(2);
			break;

			case 2 :
				led(4);    //when remaindistance <10 && >3
				
				break;

			case 3 :
			    led(8);		//when remain distance < 3 m 
				
				while(1){}   //infinite loop when arrived 
				
			 
		}
	}

}

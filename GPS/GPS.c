#include "../TM4C123GH6PM.h"
#include "../UART/UART.h"
#include "../GPIO/GPIO.h"
#include "GPS.h"
//#include "SYSTICK.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>




void GPS_read(double *newLat , double *newLon){
	char GPS_logName[]="$GPRMC,";  //the name of the needed log 
	char valid ;
	char lat[15];
	char lon[15];
	char NorS ;
	char EorW ;
	char speed[15];
	char counter =0;
	char  recievedChar;
	char i =0 ;
	char flag =1;       
	
	do {
		while (UART5_ReadChar() != GPS_logName[i]){
		i=0;
		}
		i++;
	}while(i !=7);

	
	while(1){
		if (flag){
			//recievedChar = UART5_ReadChar();
			if(recievedChar == ','){counter++;}
		}
		switch (counter){
			case 0 : recievedChar = UART5_ReadChar();WriteUart0(recievedChar);break;

			case 1 : recievedChar = UART5_ReadChar(); 
			if (recievedChar != ',')valid = recievedChar;WriteUart0(recievedChar);
			break;

			case 2 : UART5_ReadString(lat, ',') ;counter++;flag=0 ;if (valid =='A'){*newLat = atof(lat);}break;
			
			case 3 : recievedChar = UART5_ReadChar();
			if (recievedChar != ',')NorS= recievedChar;
			flag=1;
			WriteUart0(recievedChar);
			break;

			case 4 : UART5_ReadString(lon, ',') ;counter++;flag=0 ;if (valid =='A'){*newLon = atof(lon);}break;

			case 5 :  recievedChar = UART5_ReadChar();
			if (recievedChar != ',')EorW= recievedChar;
			flag=1;
			WriteUart0(recievedChar);
			break;

			case 6 : UART5_ReadString(speed, ',') ;counter++;flag=0 ;WriteUart0(recievedChar);break;
		}
		if (counter == 7 ){break;}
	}
	
}




float ToDegree (float angle){
	int degree = (int)angle /100;
	float minutes = angle -(float)degree*100;
	return(degree + (minutes/60));
}
float ToRad(float angle){
	return angle * (PI/ 180) ;
}



float GPS_getDistance (double currentLong, double currentLat, double destLong,double destLat)	{
	
	float currentLongRad =ToRad(ToDegree (currentLong));
    float currentLatRad = ToRad (ToDegree (currentLat)); 
	float destLongRad = ToRad (ToDegree (destLong));
    float destLatRad = ToRad (ToDegree(destLat));


  float longDiff = destLongRad - currentLongRad ;
  float latDiff = destLatRad - currentLatRad ;

// Calculate Distance

float a = pow(sin(latDiff/2),2)+cos(currentLatRad)*cos(destLatRad)*pow(sin(longDiff/2),2);
	// Haversins formula: a ain" (80/2) + cos yl D cos 20

 double c = 2  * atan2(sqrt(a), sqrt(1 - a));
	return EARTH_RADIUS * c ;
}


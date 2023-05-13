#include <sevenSeg.h>
#include <"../TM4C123GH6PM.h">

unsigned char counter=0;
unsigned seg1, seg2, seg3;
unsigned char sevenSeg_array[10]={0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F};

void setSevenSeg(unsigned char indexofarray){
    GPIO_PORTB_Data_R = sevenSeg_array[indexofarray];
    //if the 7 segment is common anode, invert(~) the sevenSeg_array[indexofarray]
}

void SplitDistance(float distance){
    int d = (int)distance;

    seg1 = d%10;
    d/=10;
    seg2 = d%10;
    d/=10;
    seg3 = d%10;
    d/=10;
}

void show(int digit, char value){
    GPIO_PORTB_DATA_R = 0x00;
    GPIO_PORTE_DATA_R = digit;
    setSevenSeg(value);
}

//wait half second
void Systick_Init(){ 
    NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 80000-1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x7;
	while((NVIC_ST_CTRL_R & 0x00010000) == 0){};
}

void Systick_handler(){
    if(counter==0){
        show(8,seg3);
        counter++;
    }

    if(counter==1){
        show(4,seg2);
        counter++;
    }

    if(counter==2){
        show(2,seg1);
        counter=0;
    }
}

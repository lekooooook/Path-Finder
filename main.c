#include "common.h"
#include "include.h"

extern void Steerconfig();
uint8 cross_warning=0;
extern int center;
uint32 steerduty=SteerMid;
extern void img_transform();
extern  uint8 whiteR[60][5];

//舵机+++向左。716
   void  main(void)
{  
  
  DisableInterrupts;                                                  //关闭总中断
  system_init(); 
  uart_clear();
  EnableInterrupts;  
  gpio_init (PTA13, GPO,0);
  printf("\n\n\nNOTICE:Version2016.01.31");
  uint8 con=0;
  while(1)
  {   
    
    
DELAY_MS(10);


  } 
  
  
}


void main_PIT()
{
      PIT_Flag_Clear(PIT0);
}


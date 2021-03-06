#include "Direction.h"
#include "math.h"
#include "common.h"
#include "include.h"


#define judge 95    //边界阈       值
#define SteerMid 767//舵机中值（10000精度）
#define Kp1 2.5
#define Kp2 1.25 //由斜率关系，若在两段曲线之间的结合点可微，则Kp2=Kp1的一半
#define E1 20
#define E2 50
#define Kv 1

uint8 Lost_CenterL[128] = {68,68,68,68,68,68,68,68,    //8
                           68,68,68,68,68,68,68,68,     //16
                           68,68,68,68,68,68,68,68,     //24
                           69,69,69,69,70,70,70,70,     //32
                           71,71,71,71,71,72,73,74,     //40
                           75,76,77,78,79,80,80,81,     //48
                           81,82,82,83,83,83,84,84,     //56
                           84,85,85,86,86,87,88,89,    //64
                           89,90,91,92,93,94,95,96,  //72
                           97,98,99,100,101,102,103,104,  //80
                           105,106,107,108,109,110,110,110,  //88
                           110,110,110,110,110,110,110,110,  //96
                           110,110,110,110,110,110,110,110,  //12
                           110,110,110,110,110,110,110,110,  //13
                           110,110,110,110,110,110,110,110,
                           110,110,110,110,110,110,110,110,};
uint8 Lost_CenterR[128] = {19,19,19,19,19,19,19,19,    //8
                           19,19,19,19,19,19,19,19,    //16
                           19,19,19,19,20,20,20,20,    //24
                           20,20,20,20,20,20,20,20,    //32
                           20,20,19,19,19,19,18,20,    //40
                           20,21,22,23,24,25,26,27,    //48
                           28,29,30,31,31,32,32,33,    //56
                           33,34,34,35,35,36,36,37,    //64
                           37,38,38,39,39,40,40,41,    //72
                           42,44,45,46,47,48,49,50,    //80
                           51,52,53,53,54,54,55,55,
                           56,56,56,56,57,57,58,58,
                           60,60,60,60,60,60,60,60,
                           60,60,60,60,60,60,60,60,  
                           60,60,60,60,60,60,60,60};
uint8 control_L[65]={                            
                    0, 
                    3, 6, 9, 12,15,18,21,24,28,          //0 
                    32,36,40,44,48,52,56,60,64,             //10   
                    68,72,75,75,75,76,76,76,76,             //20  
                    77,77,77,77,78,78,80,80,82,             //30   
                    82,82,83,83,83,83,84,84,84,             //40  
                    85,85,85,86,86,86,86,86,86,             //50  
                    86,86,86,86,86                          //60
                    };
uint8 control_R[65]={                            
                    0,
                    3, 6, 9, 12,15,18,21,24,28,             //0  
                    32,36,40,44,48,52,56,60,64,                //10  
                    68,72,75,75,75,76,76,76,76,                //20   
                    77,77,77,77,78,78,80,80,82,                //30    
                    82,82,83,83,83,83,84,84,84,                //40   
                    85,85,85,86,86,86,86,86,86,                //50    
                    86,86,86,86,86                             //60
                    };













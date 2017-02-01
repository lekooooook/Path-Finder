#include "Image.h"

#define white 255          //255对应图像白色
#define black 0            //0对应图像黑色
#define RoadCenter  39     //赛道中心
extern uint8 imgbuff[CAMERA_SIZE];  //图像缓存，用于DMA采集图像
extern uint8 img[CAMERA_H][CAMERA_W]; //二维数组，把DMA采集的图像整理成二维数组
void find_center()
{

}


//建议摄像头组把图像处理的函数放到这里面，具体函数自己添加
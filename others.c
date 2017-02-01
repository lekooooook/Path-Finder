#include "common.h"
#include "include.h"

#define DATALINE                 CAMERA_H
#define DATACOUNT                CAMERA_W
#define white 255          //255对应图像白色
#define black 0            //0对应图像黑色
#define hang_max 60



void uint8send(uint8 ch)
{
     //等待发送缓冲区空
    while(!(UART_S1_REG(UARTN[FIRE_PORT]) & UART_S1_TDRE_MASK));

    //发送数据
    UART_D_REG(UARTN[FIRE_PORT]) = (uint8)ch;

}
extern uint8 img[CAMERA_H][CAMERA_W]; //二维数组，把DMA采集的图像整理成二维数组
void vcan_sendimg2(uint8 *imgaddr, uint32 imgsize)
{
#define CMD_IMG     1
    uint8 cmdf[2] = {CMD_IMG, ~CMD_IMG};    //山外上位机 使用的命令
    uint8 cmdr[2] = {~CMD_IMG, CMD_IMG};    //山外上位机 使用的命令

    uart_putbuff(FIRE_PORT, cmdf, sizeof(cmdf));    //先发送命令

    uart_putbuff(FIRE_PORT, imgaddr, imgsize); //再发送图像

    uart_putbuff(FIRE_PORT, cmdr, sizeof(cmdr));    //先发送命令
}
//发送图像到上位机显示
//不同的上位机，不同的命令
//如果使用其他上位机，则需要修改代码

/***************************************************/
/*!
 *  @brief      二值化图像解压（空间 换 时间 解压）
 *  @param      dst             图像解压目的地址
 *  @param      src             图像解压源地址
 *  @param      srclen          二值化图像的占用空间大小
 *  @since      v5.0          
 */
void img_extract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {white, black}; //0 和 1 分别对应的颜色
    //注：山外的摄像头 0 表示 白色，1表示 黑色
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}

//红树上位机程序
void com_pc(uint8 (*img)[CAMERA_W])
{
  uint8 i,j;
  uart_putchar(FIRE_PORT,0xff);
  for(i=0;i<DATALINE;i++)
  {
    for(j=0;j<DATACOUNT;j++)
    {
      if(img[i][j]==0xff)
      {
        img[i][j]=0xfe;
      }
      uart_putchar(FIRE_PORT,img[i][j]);
    }
  }
  
  uart_putchar(FIRE_PORT,0xff);
}

/*!
 *  @brief      山外多功能调试助手上位机，虚拟示波器显示函数
 *  @param      wareaddr    波形数组起始地址
 *  @param      waresize    波形数组占用空间的大小
 *  @since      v5.0
*  Sample usage:
             具体用法参考这帖子:
            【山外资料】陀螺仪和加速度 上位机显示例程 - 智能车资料区
             http://vcan123.com/forum.php?mod=viewthread&tid=6253&ctid=27
 */
void vcan_sendware(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3               //00000011 --------11111100   252
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart_putbuff(UART1, cmdf, sizeof(cmdf));    //先发送前命令
    uart_putbuff(UART1, (uint8_t *)wareaddr, waresize);    //发送数据
    uart_putbuff(UART1, cmdr, sizeof(cmdr));    //发送后命令

}
void send_img(void)
{
  uint8 i,j;
  uart_putchar(UART3,0xff);
  for(i=0;i<hang_max;i++)
  {
    for(j=0;j<CAMERA_W;j++)
    {
      if(img[i][j]==0xff)
      {
        img[i][j]=0xfe;
      }
      uart_putchar(UART3,img[i][j]);
    }
  }

}
void Up_send(int ch1,int ch2,int ch3)
{
    ch1*=10;
    ch2*=10;
    ch3*=10;
    
    uart_putchar(UART1,0XFF);//数据帧头
    uart_putchar(UART1,0XFF);
    
    uart_putchar(UART1,ch1/256);//通道一
    uart_putchar(UART1,ch1%256);
    
    uart_putchar(UART1,ch2/256);//通道二
    uart_putchar(UART1,ch2%256);
    
    uart_putchar(UART1,ch3/256);//通道三
    uart_putchar(UART1,ch3%256);
}

void uart_clear()
{
  char dispose;int i;
  for(i=0;i<8;i++)
  {
   if(uart_query (UART0) == 1)     //查询是否接收到数据
    {
    uart_getchar (UART0,&dispose);  //等待接收一个数据，保存到 ch里
    }
   DELAY_MS(2);
  }
}

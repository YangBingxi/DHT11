
/**
  ******************************************************************************
  * 文件名程: main.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:TM4C123G对DHT11的驱动
  * 编写日期: 2017.12.12
  ******************************************************************************
  * 说明：
  * 硬件平台：TM4C123G
  *   *****
  * 软件设计说明：
  *   *****
  * Github：
  ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "uartstdio/uartstdio.h"
#include "DHT11/DHT11.h"
#include "delay/delay.h"
int main(void)
{
    //使能FPU
    FPUEnable();
    FPULazyStackingEnable();
    //设置时钟直接使用外部晶振
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //配置PA0和PA1为串口0引脚
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //配置UART0为115200,8-N-1
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 |
          UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTStdioConfig(0,115200,SysCtlClockGet());
    //使能中断
    IntMasterEnable();
    //使能串口中断
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //发送提示信息
    uint8_t temperature;
    uint8_t humidity;
    while(DHT11_Init()) //DHT11初始化
    {
        Delay_ms(200);
        UARTprintf("DHT11 Error\n");
        Delay_ms(200);
    }
    while(1)
    {
        DHT11_Read_Data(&temperature,&humidity);    //读取温湿度值
        UARTprintf("temperature:%d;humidity:%d\n",temperature,humidity);
        SysCtlDelay(5*SysCtlClockGet()/3);     //5sec
    }
}

/**
  ******************************************************************************
  * �ļ�����: main.c
  * ��    ��: By Sw Young
  * ��    ��: V1.0
  * ��    ��:TM4C123G��DHT11������
  * ��д����: 2017.12.12
  ******************************************************************************
  * ˵����
  * Ӳ��ƽ̨��TM4C123G
  *   *****
  * ������˵����
  *   *****
  * Github��
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
    //ʹ��FPU
    FPUEnable();
    FPULazyStackingEnable();
    //����ʱ��ֱ��ʹ���ⲿ����
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //����PA0��PA1Ϊ����0����
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //����UART0Ϊ115200,8-N-1
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 |
          UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTStdioConfig(0,115200,SysCtlClockGet());
    //ʹ���ж�
    IntMasterEnable();
    //ʹ�ܴ����ж�
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //������ʾ��Ϣ
    uint8_t temperature;
    uint8_t humidity;
    while(DHT11_Init()) //DHT11��ʼ��
    {
        Delay_ms(200);
        UARTprintf("DHT11 Error\n");
        Delay_ms(200);
    }
    while(1)
    {
        DHT11_Read_Data(&temperature,&humidity);    //��ȡ��ʪ��ֵ
        UARTprintf("temperature:%d;humidity:%d\n",temperature,humidity);
        SysCtlDelay(5*SysCtlClockGet()/3);     //5sec
    }
}

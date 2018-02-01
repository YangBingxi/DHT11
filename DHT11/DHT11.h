/*
 * DHT11.h
 *
 *  Created on: 2018年1月30日
 *      Author: Sw Young
 */

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

#ifndef DHT11_DHT11_H_
#define DHT11_DHT11_H_

//#define DATA_DISENABLE GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0, 0);
//#define DATA_ENABLE GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0, GPIO_PIN_0);

//IO方向设置
#define DHT11_IO_IN()  {GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);}
#define DHT11_IO_OUT() {GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);}
//IO操作函数
#define DHT11_DQ_OUT_ENABLE() {GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4, GPIO_PIN_4);} //数据端口
#define DHT11_DQ_OUT_DISENABLE() {GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4, 0);} //数据端口
#define DHT11_DQ_IN()  {GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)}  //数据端口

uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//读取温湿度
uint8_t DHT11_Read_Byte(void);//读出一个字节
uint8_t DHT11_Read_Bit(void);//读出一个位
uint8_t DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11

#endif /* DHT11_DHT11_H_ */

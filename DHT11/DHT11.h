/*
 * DHT11.h
 *
 *  Created on: 2018��1��30��
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

//IO��������
#define DHT11_IO_IN()  {GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);}
#define DHT11_IO_OUT() {GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);}
//IO��������
#define DHT11_DQ_OUT_ENABLE() {GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4, GPIO_PIN_4);} //���ݶ˿�
#define DHT11_DQ_OUT_DISENABLE() {GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4, 0);} //���ݶ˿�
#define DHT11_DQ_IN()  {GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)}  //���ݶ˿�

uint8_t DHT11_Init(void);//��ʼ��DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//��ȡ��ʪ��
uint8_t DHT11_Read_Byte(void);//����һ���ֽ�
uint8_t DHT11_Read_Bit(void);//����һ��λ
uint8_t DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11

#endif /* DHT11_DHT11_H_ */

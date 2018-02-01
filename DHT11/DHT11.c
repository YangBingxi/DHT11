/*
 * DHT11.c
 *
 *  Created on: 2018��1��30��
 *      Author: Sw Young
 */
#include "DHT11.h"
#include "delay/delay.h"
//��λDHT11
void DHT11_Rst(void)
{
    DHT11_IO_OUT();     //SET OUTPUT
//    DHT11_DQ_OUT=0;     //DQ=0
    DHT11_DQ_OUT_DISENABLE();     //����DQ
    Delay_ms(30);       //��������18ms
//    DHT11_DQ_OUT=1;     //DQ=1
    DHT11_DQ_OUT_ENABLE();  //DQ=1
    Delay_us(30);       //��������20~40us
}
//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
uint8_t DHT11_Check(void)
{
    uint8_t retry=0;
    DHT11_IO_IN();//SET INPUT
    while (GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)&&(retry<100))//DHT11������40~80us
    {
        retry++;
        Delay_us(1);
    };
    if(retry>=100)return 1;
    else retry=0;
    while ((!GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4))&&(retry<100))//DHT11���ͺ���ٴ�����40~80us
    {
        retry++;
        Delay_us(1);
    };
    if(retry>=100)return 1;
    return 0;
}
//��DHT11��ȡһ��λ
//����ֵ��1/0
uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry=0;
    while(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)&&retry<100)//�ȴ���Ϊ�͵�ƽ
    {
        retry++;
        Delay_us(1);
    }
    retry=0;
    while(!GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4)&&retry<100)//�ȴ���ߵ�ƽ
    {
        retry++;
        Delay_us(1);
    }
    Delay_us(40);//�ȴ�40us
    if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4))return 1;
    else return 0;
}
//��DHT11��ȡһ���ֽ�
//����ֵ������������
uint8_t DHT11_Read_Byte(void)
{
    uint8_t i,dat;
    dat=0;
    for (i=0;i<8;i++)
    {
        dat<<=1;
        dat|=DHT11_Read_Bit();
    }
    return dat;
}
//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    DHT11_Rst();
    if(DHT11_Check()==0||1)
    {
        for(i=0;i<5;i++)//��ȡ40λ����
        {
            buf[i]=DHT11_Read_Byte();
        }
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
        {
            *humi=buf[0];
            *temp=buf[2];
        }
    }else return 1;
    return 0;
}
//��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
//����1:������
//����0:����
uint8_t DHT11_Init(void)
{
//    GPIO_InitTypeDef  GPIO_InitStructure;
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);    //ʹ��PG�˿�ʱ��
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               //PG11�˿�����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOG, &GPIO_InitStructure);               //��ʼ��IO��
//    GPIO_SetBits(GPIOG,GPIO_Pin_11);                         //PG11 �����

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4, GPIO_PIN_4);     //��ʼ��Ϊ��


    DHT11_Rst();  //��λDHT11
    return DHT11_Check();//�ȴ�DHT11�Ļ�Ӧ
}

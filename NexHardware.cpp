/**
 * @file NexHardware.cpp
 *
 * The implementation of base API for using Nextion. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include "NexHardware.h"
#include <functional>

#ifdef NEX_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
SoftwareSerial nexSerial(NEX_RX,NEX_TX);
#endif


#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)     
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_AUTOMATIC_SLEEP             (0x86)
#define NEX_RET_AUTOMATIC_WAKE_UP           (0x87)
#define NEX_RET_START_UP                    (0x88)
#define NEX_RET_START_SD_UPGRADE            (0x89)

#define NEX_RET_INVALID_CMD             (0x00)
#define NEX_RET_CMD_FINISHED            (0x01)
#define NEX_RET_INVALID_COMPONENT_ID    (0x02)
#define NEX_RET_INVALID_PAGE_ID         (0x03)
#define NEX_RET_INVALID_PICTURE_ID      (0x04)
#define NEX_RET_INVALID_FONT_ID         (0x05)
#define NEX_RET_INVALID_BAUD            (0x11)
#define NEX_RET_INVALID_VARIABLE        (0x1A)
#define NEX_RET_INVALID_OPERATION       (0x1B)

std::function<void(uint8_t)> currentPageIdCallback=nullptr;
std::function<void(uint16_t,uint16_t,uint8_t)> touchCoordinateCallback=nullptr;
std::function<void(uint16_t,uint16_t,uint8_t)> touchEventInSleepModeCallback=nullptr;
std::function<void()> automaticSleepCallback=nullptr;
std::function<void()> automaticWakeUpCallback=nullptr;
std::function<void()> systemStartUpCallback=nullptr;
std::function<void()> startSdUpgradeCallback=nullptr;

/*
 * Receive unt32_t data. 
 * 
 * @param number - save uint32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool recvRetNumber(uint32_t *number, uint32_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = ((uint32_t)temp[4] << 24) | ((uint32_t)temp[3] << 16) | ((uint32_t)temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret) 
    {
        dbSerialPrint("recvRetNumber :");
        dbSerialPrintln(*number);
    }
    else
    {
        dbSerialPrintln("recvRetNumber err");
    }
    
    return ret;
}

/*
 * Receive int32_t data. 
 * 
 * @param number - save int32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool recvRetNumber(int32_t *number, uint32_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = ((int32_t)temp[4] << 24) | ((int32_t)temp[3] << 16) | ((int32_t)temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret) 
    {
        dbSerialPrint("recvRetNumber :");
        dbSerialPrintln(*number);
    }
    else
    {
        dbSerialPrintln("recvRetNumber err");
    }
    
    return ret;
}

/*
 * Receive string data. 
 * 
 * @param str - save string data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool recvRetString(String &str, uint32_t timeout)
{
    str = "";
    bool ret{false};
    bool str_start_flag = false;
    uint8_t cnt_0xff = 0;
    uint8_t c = 0;
    long start;

    start = millis();
    while (millis() - start <= timeout && ret == false)
    {
        while (nexSerial.available())
        {
            c = nexSerial.read();
            if (str_start_flag)
            {
                if (0xFF == c)
                {
                    cnt_0xff++;                    
                    if (cnt_0xff >= 3)
                    {
                        ret = true;
                        break;
                    }
                }
                else
                {
                    str += (char)c;
                }
            }
            else if (NEX_RET_STRING_HEAD == c)
            {
                str_start_flag = true;
            }
        }
    }

    dbSerialPrint("recvRetString[");
    dbSerialPrint(str.length());
    dbSerialPrint(",");
    dbSerialPrint(str);
    dbSerialPrintln("]");

    return ret;
}

/*
 * Receive string data. 
 * 
 * @param buffer - save string data. 
 * @param len - in buffer len / out saved string len excluding null char. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool recvRetString(char *buffer, uint16_t &len, uint32_t timeout)
{
    String temp;
    bool ret = recvRetString(temp,timeout);

    if(ret && len)
    {
        len=temp.length()>len?len:temp.length();
        strncpy(buffer,temp.c_str(), len);
    }
    return ret;
}

/*
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void sendCommand(const char* cmd)
{
    while (nexSerial.available())
    {
        nexSerial.read();
    }
    
    nexSerial.print(cmd);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
}


/*
 * Command is executed successfully. 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool recvRetCommandFinished(uint32_t timeout)
{    
    bool ret = false;
    uint8_t temp[4] = {0};
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        ret = false;
    }

    if (temp[0] == NEX_RET_CMD_FINISHED
        && temp[1] == 0xFF
        && temp[2] == 0xFF
        && temp[3] == 0xFF
        )
    {
        ret = true;
    }

    if (ret) 
    {
        dbSerialPrintln("recvRetCommandFinished ok");
    }
    else
    {
        dbSerialPrintln("recvRetCommandFinished err");
    }
    
    return ret;
}


bool nexInit(void)
{
    bool ret1 = false;
    bool ret2 = false;
    
    nexSerial.begin(9600);
    sendCommand("");
    sendCommand("bkcmd=1");
    ret1 = recvRetCommandFinished();
    sendCommand("page 0");
    ret2 = recvRetCommandFinished();
    return ret1 && ret2;
}

void nexLoop(NexTouch *nex_listen_list[])
{
    static uint8_t __buffer[10];
    
    uint16_t i;
    uint8_t c;  
    
    while (nexSerial.available() > 0)
    {   
        delay(10);
        c = nexSerial.read();
        switch(c)
        {
            case NEX_RET_EVENT_TOUCH_HEAD:
            {
                if (nexSerial.available() >= 6)
                {
                    __buffer[0] = c;  
                    for (i = 1; i < 7; i++)
                    {
                        __buffer[i] = nexSerial.read();
                    }
                    __buffer[i] = 0x00;
                    
                    if (0xFF == __buffer[4] && 0xFF == __buffer[5] && 0xFF == __buffer[6])
                    {
                        NexTouch::iterate(nex_listen_list, __buffer[1], __buffer[2], __buffer[3]);
                    }
                    
                }
                break;
            }
            case NEX_RET_CURRENT_PAGE_ID_HEAD:
            {
                if(nexSerial.available()>=4)
                {
                    __buffer[0] = c;  
                    for (i = 1; i < 5; i++)
                    {
                        __buffer[i] = nexSerial.read();
                    }
                    __buffer[i] = 0x00;
                    
                    if (0xFF == __buffer[2] && 0xFF == __buffer[3] && 0xFF == __buffer[4])
                    {
                        if(currentPageIdCallback!=nullptr)
                        {
                            currentPageIdCallback(__buffer[1]);
                        }
                    }
                }
                break;
            }
            case NEX_RET_EVENT_POSITION_HEAD:
            case NEX_RET_EVENT_SLEEP_POSITION_HEAD:
            {
                if(nexSerial.available()>=8)
                {
                    __buffer[0] = c;  
                    for (i = 1; i < 9; i++)
                    {
                        __buffer[i] = nexSerial.read();
                    }
                    __buffer[i] = 0x00;
                    
                    if (0xFF == __buffer[6] && 0xFF == __buffer[7] && 0xFF == __buffer[8])
                    {
                        if(__buffer[0] == NEX_RET_EVENT_POSITION_HEAD && touchCoordinateCallback!=nullptr)
                        {
                             
                            touchCoordinateCallback(((int16_t)__buffer[2] << 8) | (__buffer[1]), ((int16_t)__buffer[4] << 8) | (__buffer[3]),__buffer[5]);
                        }
                        else if(__buffer[0] == NEX_RET_EVENT_SLEEP_POSITION_HEAD && touchCoordinateCallback!=nullptr)
                        {
                             
                            touchEventInSleepModeCallback(((int16_t)__buffer[2] << 8) | (__buffer[1]), ((int16_t)__buffer[4] << 8) | (__buffer[3]),__buffer[5]);
                        }
                    }
                }
                break;
            }
            case NEX_RET_AUTOMATIC_SLEEP:
            case NEX_RET_AUTOMATIC_WAKE_UP:
            {
                if(nexSerial.available()>=3)
                {
                    __buffer[0] = c;  
                    for (i = 1; i < 4; i++)
                    {
                        __buffer[i] = nexSerial.read();
                    }
                    __buffer[i] = 0x00;
                    
                    if (0xFF == __buffer[1] && 0xFF == __buffer[2] && 0xFF == __buffer[3])
                    {
                        if(__buffer[0]==NEX_RET_AUTOMATIC_SLEEP && automaticSleepCallback!=nullptr)
                        {
                            automaticSleepCallback();
                        }
                        else if(__buffer[0]==NEX_RET_AUTOMATIC_WAKE_UP && automaticWakeUpCallback!=nullptr)
                        {
                            automaticWakeUpCallback();
                        }
                    }
                }
                break;
            }
            case NEX_RET_START_UP:
            {
                if(systemStartUpCallback!=nullptr)
                {
                    systemStartUpCallback();
                }
                break;
            }
            case NEX_RET_START_SD_UPGRADE:
            {
                if(startSdUpgradeCallback!=nullptr)
                {
                    startSdUpgradeCallback();
                }
                break;
            }
        };      
    }
}

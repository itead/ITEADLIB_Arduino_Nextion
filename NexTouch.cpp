/**
 * @file NexTouch.cpp
 *
 * API of Nextion. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include "NexTouch.h"

uint8_t NexTouch::__buffer[256] = {0};

/**
 * Watting for Nextion's touch event.
 * 
 * @param list - index to Nextion Components list. 
 * 
 */
uint8_t NexTouch::mainEventLoop(NexTouch **list)
{
    uint16_t i;
    uint8_t c;  
    while (nexSerial.available() > 0)
    {   
        delay(10);
        c = nexSerial.read();
        
        if (NEX_RET_EVENT_TOUCH_HEAD == c)
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
                    iterate(list, (NexPid)__buffer[1], (NexCid)__buffer[2], (NexEventType)__buffer[3]);
                }
                
            }
        }
    }
    return 0;
}

/**
 * Constructor of Nextouch. 
 * 
 * @param pid - page id. 
 * @param cid - component id.    
 * @param name - component name. 
 * @param pop - pop event function pointer.   
 * @param pop_ptr - the parameter was transmitted to pop event function pointer.  
 * @param push - push event function pointer. 
 * @param push_ptr - the parameter was transmitted to push event function pointer.
 *   
 */
NexTouch::NexTouch(NexPid pid, NexCid cid, char *name, 
    NexTouchEventCb pop, void *pop_ptr,
    NexTouchEventCb push, void *push_ptr)
{
    this->pid = pid;
    this->cid = cid;
    this->name = name;
    this->cbPush = push;
    this->cbPop = pop;
    this->__cbpop_ptr = pop_ptr;
    this->__cbpush_ptr = push_ptr;
}

/**
 * Get page id.
 *
 * @return the id of page.  
 */
NexPid NexTouch::getPid(void)
{
    return pid;
}

/**
 * Get component id.
 *
 * @return the id of component.  
 */
NexCid NexTouch::getCid(void)
{
    return cid;
}

/**
 * Get component name.
 *
 * @return the name of component. 
 */
const char* NexTouch::getObjName(void)
{
    return name;
}

/**
 * Print current object address,page id,component id,
 * component name,pop event function address,push event function address. 
 *  
 */
void NexTouch::print(void)
{
    dbSerialPrint("[");
    dbSerialPrint((uint32_t)this);
    dbSerialPrint(":");
    dbSerialPrint(pid);
    dbSerialPrint(",");
    dbSerialPrint(cid);
    dbSerialPrint(",");
    if (name)
    {
        dbSerialPrint(name);
    }
    else
    {
        dbSerialPrint("(null)");
    }
    dbSerialPrint(",");
    dbSerialPrint((uint32_t)cbPush);
    dbSerialPrint(",");
    dbSerialPrint((uint32_t)cbPop);
    dbSerialPrintln("]");
}

void NexTouch::attachPush(NexTouchEventCb push, void *ptr)
{
    this->cbPush = push;
    this->__cbpush_ptr = ptr;
}

void NexTouch::detachPush(void)
{
    this->cbPush = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPop(NexTouchEventCb pop, void *ptr)
{
    this->cbPop = pop;
    this->__cbpop_ptr = ptr;
}

void NexTouch::detachPop(void)
{
    this->cbPop = NULL;    
    this->__cbpop_ptr = NULL;
}

void NexTouch::iterate(NexTouch **list, NexPid pid, NexCid cid, NexEventType event)
{
    NexTouch *e = NULL;
    uint16_t i = 0;

    if (NULL == list)
    {
        return;
    }
    
    for(i = 0; (e = list[i]) != NULL; i++)
    {
        if (e->getPid() == pid && e->getCid() == cid)
        {
            e->print();
            if (NEX_EVENT_PUSH == event)
            {
                e->push();
            }
            else if (NEX_EVENT_POP == event)
            {
                e->pop();
            }
            
            break;
        }
    }
}

void NexTouch::push(void)
{
    if (cbPush)
    {
        cbPush(__cbpush_ptr);
    }
}

void NexTouch::pop(void)
{
    if (cbPop)
    {
        cbPop(__cbpop_ptr);
    }
}

/**
 * Command is executed successfully. 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool NexTouch::recvRetCommandFinished(uint32_t timeout)
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

/**
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void NexTouch::sendCommand(const char* cmd)
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

/**
 * Receive string data. 
 * 
 * @param buffer - save string data. 
 * @param len - string buffer length. 
 * @param timeout - set timeout time. 
 *
 * @return the length of string buffer.
 *
 */
uint16_t NexTouch::recvRetString(char *buffer, uint16_t len, uint32_t timeout)
{
    uint16_t ret = 0;
    bool str_start_flag = false;
    uint8_t cnt_0xff = 0;
    String temp = String("");
    uint8_t c = 0;
    long start;

    if (!buffer || len == 0)
    {
        goto __return;
    }
    
    start = millis();
    while (millis() - start <= timeout)
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
                        break;
                    }
                }
                else
                {
                    temp += (char)c;
                }
            }
            else if (NEX_RET_STRING_HEAD == c)
            {
                str_start_flag = true;
            }
        }
        
        if (cnt_0xff >= 3)
        {
            break;
        }
    }

    ret = temp.length();
    ret = ret > len ? len : ret;
    strncpy(buffer, temp.c_str(), ret);
    
__return:

    dbSerialPrint("recvRetString[");
    dbSerialPrint(temp.length());
    dbSerialPrint(",");
    dbSerialPrint(temp);
    dbSerialPrintln("]");

    return ret;
}

/**
 * Receive uint32_t data. 
 * 
 * @param number - save uint32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool NexTouch::recvRetNumber(uint32_t *number, uint32_t timeout)
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
        *number = (temp[4] << 24) | (temp[3] << 16) | (temp[2] << 8) | (temp[1]);
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

/**
 * Init Nextion's baudrate,page id.    
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool nexInit(void)
{
    dbSerialBegin(9600);
    nexSerial.begin(9600);
    NexTouch::sendCommand("");
    NexTouch::sendCommand("bkcmd=1");
    NexTouch::recvRetCommandFinished();
    NexTouch::sendCommand("page 0");
    NexTouch::recvRetCommandFinished();
    return true;
}

/**
 * Call mainEventLoop,watting for Nextion's touch event.  
 *  
 * @param nex_listen_list - index to Nextion Components list. 
 * 
 * @retval false - failed. 
 */
bool nexLoop(NexTouch **nex_listen_list)
{
    NexTouch::mainEventLoop(nex_listen_list);
    return false;
}

#if 0
/**
 * Return current page id.   
 *  
 * @param pageId - output parameter,to save page id.  
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool sendCurrentPageId(uint8_t* pageId)
{

    bool ret = false;
    uint8_t temp[5] = {0};

    if (!pageId)
    {
        goto __return;
    }
    NexTouch::sendCommand("sendme");
    delay(50);
    nexSerial.setTimeout(500);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_CURRENT_PAGE_ID_HEAD
    && temp[2] == 0xFF
    && temp[3] == 0xFF
    && temp[4] == 0xFF
    )
    {
        *pageId = temp[1];
        ret = true;
    }

    __return:

    if (ret) 
    {
        dbSerialPrint("recvPageId :");
        dbSerialPrintln(*pageId);
    }
    else
    {
        dbSerialPrintln("recvPageId err");
    }

    return ret;

}

/**
 * Touch screen calibration. 
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool touchCalibration(void)
{
    bool ret = false;
    NexTouch::sendCommand("touch_j");
    delay(10);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("TouchCalibration ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("TouchCalibration err ");
    }
    
    return ret;
}

/**
 * Disable all touch hot.  
 *
 * @retval true - success. 
 * @retval false - failed.
 */
bool  disableTouchFocus(void)
{
    bool ret = false;
    NexTouch::sendCommand("cle_c");
    delay(10);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("disableTouchFocus ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("disableTouchFocus err ");
    }
    
    return ret;
}

/**
 * Pause serial instruction execution. 
 *
 * @retval true - success. 
 * @retval false - failed.
 */
bool pauseSerialCommand(void)
{

    bool ret = false;
    NexTouch::sendCommand("com_stop");
    delay(10);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("pauseSerialCommand ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("pauseSerialCommand err ");
    }

    return ret;
}

/**
 * Recovery serial instruction execution. 
 *
 * @retval true - success. 
 * @retval false - failed.
 */
bool recoverySerialCommand(void)               
{  
    bool ret = false;
    NexTouch::sendCommand("com_star");
    delay(10);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("recoverySerialCommand ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("recoverySerialCommand err ");
    }

    return ret;	
}

/**
 * Set current backlight brightness value. 
 *
 * @param dimValue - current backlight brightness value.
 * 
 * @retval true - success. 
 * @retval false - failed.
 */
bool setCurrentBrightness(uint8_t dimValue)
{
    bool ret = false;
    char buf[10] = {0};
    String cmd;
    utoa(dimValue, buf, 10);
    cmd += "dim=";
    cmd += buf;
    NexTouch::sendCommand(cmd.c_str());
    delay(10);

    if(NexTouch::recvRetCommandFinished())
    {   
        dbSerialPrint("setCurrentBrightness[ ");
        dbSerialPrint(dimValue);
        dbSerialPrintln("]ok ");
      
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("setCurrentBrightness err ");
    }

    return ret;    
}

/**
 * Set default backlight brightness value.  
 *
 * @param dimDefaultValue - default backlight brightness value.
 * 
 * @retval true - success. 
 * @retval false - failed.
 */
bool setDefaultBrightness(uint8_t dimDefaultValue)
{
    bool ret = false;
    char buf[10] = {0};
    String cmd;
    utoa(dimDefaultValue, buf, 10);
    cmd += "dims=";
    cmd += buf;
    NexTouch::sendCommand(cmd.c_str());
    delay(10);

    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrint("setDefaultBrightness[");
        dbSerialPrint(dimDefaultValue);
        dbSerialPrintln("]ok");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("setDefaultBrightness err ");
    }

    return ret; 
}

/**
 * Set device in sleep mode.
 *
 * @param  mode - 1:into sleep mode,0:exit sleep mode.  
 * 
 * @retval true - success. 
 * @retval false - failed.
 */
bool sleepMode(uint8_t mode)
{
    bool ret = false;
    char buf[10] = {0};
    String cmd;
    if(mode != 0 && mode != 1)
    {
        dbSerialPrintln("mode input ok ");
        return ret;
    }
    utoa(mode, buf, 10);
    cmd += "sleep=";
    cmd += buf;
    NexTouch::sendCommand(cmd.c_str());
    delay(10);

    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("sleepMode ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("sleepMode err ");
    }

    return ret; 
}

/**
 * Set current baudrate. 
 *
 * @param  baudrate - current baudrate,it supports 2400,4800,9600,19200,38400,57600,115200.
 * 
 * @retval true - success. 
 * @retval false - failed.
 */
bool setCurrentBaudrate(uint32_t baudrate)
{
    bool ret = false;
    char buf[10] = {0};
    String cmd;
    utoa(baudrate, buf, 10);
    cmd += "baud=";
    cmd += buf;
    NexTouch::sendCommand(cmd.c_str());
    delay(10);

    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("setCurrentBaudrate ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("setCurrentBaudrate err ");
    }

    return ret; 
}

/**
 * Set default baudrate. 
 *
 * @param  defaultBaudrate - default baudrate,it supports 2400,4800,9600,19200,38400,57600,115200.
 * 
 * @retval true - success. 
 * @retval false - failed.
 */  
bool setDefaultBaudrate(uint32_t defaultBaudrate)
{
    bool ret = false;
    char buf[10] = {0};
    String cmd;
    utoa(defaultBaudrate, buf, 10);
    cmd += "bauds=";
    cmd += buf;
    NexTouch::sendCommand(cmd.c_str());
    delay(10);

    if(NexTouch::recvRetCommandFinished())
    {
        dbSerialPrintln("setDefaultBaudrate ok ");
        ret = true; 
    }
    else 
    {
        dbSerialPrintln("setDefaultBaudrate err ");
    }

    return ret; 
}

#endif

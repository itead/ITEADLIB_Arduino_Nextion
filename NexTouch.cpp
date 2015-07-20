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
    
    while (true)
    {
        while (nexSerial.available() > 0)
        {   
            delay(10);
            c = nexSerial.read();
            
            if (NEX_RET_EVENT_TOUCH_HEAD == c)
            {
                if (nexSerial.available() >= 6)
                {
                    //memset(__buffer, 0, sizeof(__buffer));
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
    dbSerial.print("[");
    dbSerial.print((uint32_t)this);
    dbSerial.print(":");
    dbSerial.print(pid);
    dbSerial.print(",");
    dbSerial.print(cid);
    dbSerial.print(",");
    if (name)
    {
        dbSerial.print(name);
    }
    else
    {
        dbSerial.print("(null)");
    }
    dbSerial.print(",");
    dbSerial.print((uint32_t)cbPush);
    dbSerial.print(",");
    dbSerial.print((uint32_t)cbPop);
    dbSerial.println("]");
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
        dbSerial.println("recvRetCommandFinished ok");
    }
    else
    {
        dbSerial.println("recvRetCommandFinished err");
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

    dbSerial.print("recvRetString[");
    dbSerial.print(temp.length());
    dbSerial.print(",");
    dbSerial.print(temp);
    dbSerial.println("]");

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
        dbSerial.print("recvRetNumber :");
        dbSerial.println(*number);
    }
    else
    {
        dbSerial.println("recvRetNumber err");
    }
    
    return ret;
}

bool NexTouch::setBrightness(uint32_t brightness)
{    
    char buf[10] = {0};
    String cmd;
    
    utoa(brightness, buf, 10);
    cmd += "dim=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexTouch::getBrightness(uint32_t *brightness)
{
    sendCommand("get dim");
    return recvRetNumber(brightness);
}


/**
 * Init Nextion's baudrate,page id.    
 * 
 * @retval true - success. 
 * @retval false - failed. 
 */
bool nexInit(void)
{
    nexSerial.begin(9600);
    NexTouch::sendCommand("");
    NexTouch::sendCommand("page 0");
    delay(100);
    return true;
}

/**
 * Call mainEventLoop,watting for Nextion's touch event.  
 *  
 * @param nexListenList - index to Nextion Components list. 
 * 
 * @retval false - failed. 
 */
bool nexLoop(NexTouch **nexListenList)
{
    NexTouch::mainEventLoop(nexListenList);
    return false;
}

/*add for new function*/
bool sendCurrentPageId(uint8_t* pageId,uint32_t timeout)
{

        bool ret = false;
        uint8_t temp[5] = {0};
    
        if (!pageId)
        {
            goto __return;
        }
        NexTouch::sendCommand("sendme");
        delay(50);
        nexSerial.setTimeout(timeout);
        if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
        {
            goto __return;
        }
    
        if (temp[0] == NEX_RET_NUMBER_HEAD
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
            dbSerial.print("recvPageId :");
            dbSerial.println(*pageId);
        }
        else
        {
            dbSerial.println("recvPageId err");
        }
        
        return ret;

}


bool touchCalibration(uint32_t timeout)
{
    bool ret = false;
    NexTouch::sendCommand("touch_j");
    delay(10);
    
    nexSerial.setTimeout(timeout);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerial.println("TouchCalibration ok ");
        ret = true; 
    }
    else 
    {
        dbSerial.println("TouchCalibration err ");
    }
    
    return ret;
}

bool  disableTouchFocus(uint32_t timeout)
{
    bool ret = false;
    NexTouch::sendCommand("clec_c");
    delay(10);
    
    nexSerial.setTimeout(timeout);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerial.println("disableTouchFocus ok ");
        ret = true; 
    }
    else 
    {
        dbSerial.println("disableTouchFocus err ");
    }
    
    return ret;

}

bool pauseSerialCommand(uint32_t timeout)
{

    bool ret = false;
    NexTouch::sendCommand("com_stop");
    delay(10);

    nexSerial.setTimeout(timeout);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerial.println("pauseSerialCommand ok ");
        ret = true; 
    }
    else 
    {
        dbSerial.println("pauseSerialCommand err ");
    }

    return ret;

}

bool recoverySerialCommand(uint32_t timeout)               
{  
    bool ret = false;
    NexTouch::sendCommand("com_star");
    delay(10);

    nexSerial.setTimeout(timeout);
    if(NexTouch::recvRetCommandFinished())
    {
        dbSerial.println("recoverySerialCommand ok ");
        ret = true; 
    }
    else 
    {
        dbSerial.println("recoverySerialCommand err ");
    }

    return ret;	
}

bool setDim(uint8_t dimValue)
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
          dbSerial.print("setDim[ ");
          dbSerial.print(dimValue);
          dbSerial.println("]ok ");
          
          ret = true; 
      }
      else 
      {
          dbSerial.println("setDim err ");
      }
  
      return ret;    
  }


  bool setDefaultDim(uint8_t dimDefaultValue)
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
          dbSerial.print("setDefaultDim[");
          dbSerial.print(dimDefaultValue);
          dbSerial.println("]ok");
          ret = true; 
      }
      else 
      {
          dbSerial.println("setDefaultDim err ");
      }
  
      return ret; 
  }

  bool sleepMode(uint8_t mode)
  {
      bool ret = false;
      char buf[10] = {0};
      String cmd;
      utoa(mode, buf, 10);
      cmd += "sleep=";
      cmd += buf;
      NexTouch::sendCommand(cmd.c_str());
      delay(10);

      if(NexTouch::recvRetCommandFinished())
      {
          dbSerial.println("sleepMode ok ");
          ret = true; 
      }
      else 
      {
          dbSerial.println("sleepMode err ");
      }
  
      return ret; 


  }
  
  bool setDeviceDelay(uint32_t delayMs)
  {
      bool ret = false;
      char buf[10] = {0};
      String cmd;
      utoa(delayMs, buf, 10);
      cmd += "delay=";
      cmd += buf;
      NexTouch::sendCommand(cmd.c_str());
      delay(10);

      if(NexTouch::recvRetCommandFinished())
      {
          dbSerial.println("setDeviceDelay ok ");
          ret = true; 
      }
      else 
      {
          dbSerial.println("setDeviceDelay err ");
      }
  
      return ret; 

  }
  
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
          dbSerial.println("setCurrentBaudrate ok ");
          ret = true; 
      }
      else 
      {
          dbSerial.println("setCurrentBaudrate err ");
      }
  
      return ret; 


  }
  
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
          dbSerial.println("setDefaultBaudrate ok ");
          ret = true; 
      }
      else 
      {
          dbSerial.println("setDefaultBaudrate err ");
      }
  
      return ret; 

  }






















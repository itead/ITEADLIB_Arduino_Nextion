/**
 * @example CompButton.ino
 *
 * @par Show how to use API of class NexButton.  
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

#if 0
bool  sendCurrentPageId(uint8_t* pageId,uint32_t timeout);
bool touchCalibration(uint32_t timeout);
bool disableTouchFocus(uint32_t timeout); 
bool pauseSerialCommand(uint32_t timeout); 
bool recoverySerialCommand(uint32_t timeout);
bool clearSerialSurplusCommand(uint32_t timeout);
bool setDim(uint8_t dimValue);
bool setDefaultDim(uint8_t dimDefaultValue);
bool sleepMode(uint8_t mode);
bool setDeviceDelay(uint32_t delayMs);
bool setCurrentBaudrate(uint32_t baudrate);
bool setDefaultBaudrate(uint32_t baudrate);

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
          dbSerial.println("setDim ok ");
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
          dbSerial.println("setDefaultDim ok ");
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

#endif 

void setup(void)
{   
    uint8_t temp;
    dbSerial.begin(9600);
    nexInit();  

    #if 0
    if(sendCurrentPageId(&temp,500))
    {
        dbSerial.print(temp);
        dbSerial.println();
    }
    #endif 

    setDefaultDim(60);
    #if 0
    touchCalibration(500);
    disableTouchFocus(500);
    pauseSerialCommand(500);
    recoverySerialCommand(500);
    setDim(50);
    setDefaultDim(60);
    sleepMode(0);
    setDeviceDelay(200);
    setCurrentBaudrate(9600);
    setDefaultBaudrate(12400);
    #endif 
    dbSerial.println("setup done");  
}

void loop(void)
{
    dbSerial.println("nexLoop");
    while(1);
}

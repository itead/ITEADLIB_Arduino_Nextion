/**
 * @file NexWaveform.cpp
 *
 * The implementation of class NexWaveform. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
 * @author Jyrki Berg 3/3/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include "NexWaveform.h"

#ifdef STD_SUPPORT
#include <type_traits>
#endif

NexWaveform::NexWaveform(uint8_t pid, uint8_t cid, const char *name, const NexObject* page):
        NexTouch(pid, cid, name, page), m_minVal{0},m_maxVal{255},m_scale{1.0},m_hight{255}
{
}

NexWaveform::NexWaveform(uint8_t pid, uint8_t cid, const char *name, 
    float minVal, float maxVal, uint8_t hight,
    const NexObject* page):NexWaveform(pid, cid, name, page)
{
    m_minVal = minVal;
    m_maxVal = maxVal;
    m_hight = hight;
    m_scale =((float)hight)/(maxVal-minVal);
}    



bool NexWaveform::Get_background_color_bco(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexWaveform::Set_background_color_bco(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".bco=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd="";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexWaveform::Get_grid_color_gdc(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".gdc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexWaveform::Set_grid_color_gdc(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".gdc=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd="";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexWaveform::Get_grid_width_gdw(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".gdw";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexWaveform::Set_grid_width_gdw(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".gdw=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd="";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexWaveform::Get_grid_height_gdh(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".gdh";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexWaveform::Set_grid_height_gdh(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".gdh=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd="";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexWaveform::Get_channel_color(uint8_t ch, uint32_t *number)
{
    char buf[4] = {0};
    utoa(ch, buf, 10);
 
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexWaveform::Set_channel_color(uint8_t ch, uint32_t number)
{
    char buf[10] = {0};
    utoa(ch, buf, 10);
    String cmd;
    
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    cmd += buf;
    cmd += "=";
    utoa(number, buf, 10);
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd="";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}
 
 bool NexWaveform::Clear(uint8_t ch)
 {
    char buf[4] = {0};
    utoa(getObjCid(), buf, 10);
    String cmd;
    cmd = "cle ";
    cmd += buf;
    cmd += ",";
    utoa(ch, buf, 10);
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
 }


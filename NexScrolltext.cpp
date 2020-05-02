/**
 * @file NexScrolltext.cpp
 *
 * The implementation of class NexScrolltext. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/13
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include "NexScrolltext.h"

NexScrolltext::NexScrolltext(uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(pid, cid, name, page)
{
}

bool NexScrolltext::getText(String &str)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(str);
}


bool NexScrolltext::getText(char *buffer, uint16_t &len)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexScrolltext::setText(const char *buffer)
{
    String cmd;
    getObjGlobalPageName(cmd);
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

uint32_t NexScrolltext::Get_background_color_bco(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_background_color_bco(uint32_t number)
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

uint32_t NexScrolltext::Get_font_color_pco(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_font_color_pco(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pco=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_place_xcen(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".xcen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_place_xcen(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".xcen=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_place_ycen(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".ycen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_place_ycen(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".ycen=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::getFont(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".font";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::setFont(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".font=";
    cmd += buf;
    sendCommand(cmd.c_str());

    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_background_crop_picc(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_background_crop_picc(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".picc=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_background_image_pic(uint32_t *number)
{
    String cmd = String("get ");
    getObjGlobalPageName(cmd);
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_background_image_pic(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic=";
    cmd += buf;
	sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_scroll_dir(uint32_t *number)
{
    String cmd = String("get ");
    getObjGlobalPageName(cmd);
    cmd += ".dir";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_scroll_dir(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".dir=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_scroll_distance(uint32_t *number)
{
    String cmd = String("get ");
    getObjGlobalPageName(cmd);
    cmd += ".dis";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_scroll_distance(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    if (number < 2)
    {
        number = 2;
    }
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".dis=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexScrolltext::Get_cycle_tim(uint32_t *number)
{
    String cmd = String("get ");
    getObjGlobalPageName(cmd);
    cmd += ".tim";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexScrolltext::Set_cycle_tim(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    if (number < 8)
    {
        number = 8;
    }
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".tim=";
    cmd += buf;
    sendCommand(cmd.c_str());
	
    cmd = "";
    cmd += "ref ";
    getObjGlobalPageName(cmd);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


bool NexScrolltext::enable(void)
{
    char buf[10] = {0};
    String cmd;
    utoa(1, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".en=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexScrolltext::disable(void)
{
    char buf[10] = {0};
    String cmd;
    utoa(0, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".en=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

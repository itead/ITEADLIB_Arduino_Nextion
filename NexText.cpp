/**
 * @file NexText.cpp
 *
 * The implementation of class NexText. 
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
#include "NexText.h"

NexText::NexText(uint8_t pid, uint8_t cid, const char *name, const NexObject* page)
    :NexTouch(pid, cid, name, page)
{
}

bool NexText::getText(String &str)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(str);
}


bool NexText::getText(char *buffer, uint16_t &len)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexText::setText(const char *buffer)
{
    String cmd;
    getObjGlobalPageName(cmd);
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

uint32_t NexText::Get_background_color_bco(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_background_color_bco(uint32_t number)
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

uint32_t NexText::Get_font_color_pco(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_font_color_pco(uint32_t number)
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

uint32_t NexText::Get_place_xcen(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".xcen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_place_xcen(uint32_t number)
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

uint32_t NexText::Get_place_ycen(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".ycen";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_place_ycen(uint32_t number)
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

uint32_t NexText::getFont(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".font";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::setFont(uint32_t number)
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

uint32_t NexText::Get_background_crop_picc(uint32_t *number)
{
    String cmd;
    cmd += "get ";
    getObjGlobalPageName(cmd);
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_background_crop_picc(uint32_t number)
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

uint32_t NexText::Get_background_image_pic(uint32_t *number)
{
    String cmd = String("get ");
    getObjGlobalPageName(cmd);
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexText::Set_background_image_pic(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    getObjGlobalPageName(cmd);
    cmd += ".pic=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}





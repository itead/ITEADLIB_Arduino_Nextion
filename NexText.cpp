/**
 * @file NexText.cpp
 *
 * API of NexText. 
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

#include "NexText.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexText::NexText(NexPid pid, NexCid cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

/**
 * Get the value of text.
 *
 * @param buffer - text value buffer. 
 * @param len - the length of text value buffer.
 *
 * @return the length of text value buffer.
 */
uint16_t NexText::getText(char *buffer, uint16_t len)
{
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

/**
 * Set the value of text.
 *
 * @param buffer - text value buffer. 
 *
 * @retval true - success.
 * @retval false - failed. 
 */
bool NexText::setText(const char *buffer)
{
    String cmd;
    cmd += getObjName();
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}


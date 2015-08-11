/**
 * @file NexWaveform.h
 *
 * API of NexWaveform. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
 
#ifndef __NEXPOINTER_H__
#define __NEXPOINTER_H__
#ifdef __cplusplus
#include "NexTouch.h"

/**
 * NexWaveform,subclass of NexTouch,provides simple methods to control NexWaveform component.
 *
 */
class NexWaveform: public NexTouch
{
public: /* methods */
    NexWaveform(NexPid pid, NexCid cid, char *name);
    bool addValue(uint8_t ch, uint8_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPOINTER_H__ */

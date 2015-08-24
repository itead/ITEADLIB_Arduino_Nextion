/**
 * @file NexWaveform.h
 *
 * The definition of class NexWaveform. 
 *
 * @author Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date 2015/8/13
 *
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#ifndef __NEXWAVEFORM_H__
#define __NEXWAVEFORM_H__

#include "NexTouch.h"
#include "NexHardware.h"
/**
 * @addtogroup Component 
 * @{ 
 */

/**
 * NexWaveform component.
 */
class NexWaveform: public NexObject
{
public: /* methods */
    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name);
     */
    NexWaveform(uint8_t pid, uint8_t cid, const char *name);
    
    /**
     * Add value to show. 
     *
     * @param ch - channel of waveform(0-3). 
     * @param number - the value of waveform.  
     *
     * @retval true - success. 
     * @retval false - failed. 
     */
    bool addValue(uint8_t ch, uint8_t number);
};

/**
 * @}
 */

#endif /* #ifndef __NEXWAVEFORM_H__ */

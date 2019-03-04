/**
 * @file NexWaveform.h
 *
 * The definition of class NexWaveform. 
 *
 * @author Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date 2015/8/13
 * @author Jyrki Berg 3/3/2019 (https://github.com/jyberg)
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
class NexWaveform: public NexTouch
{
public: /* methods */
    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name, const NexObject* page=nullptr);
     */
    NexWaveform(uint8_t pid, uint8_t cid, const char *name, const NexObject* page=nullptr);

    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name, 
     * int32_t minVal, int32_t maxVal, uint8_t hight,
     * const NexObject* page=nullptr);
     * 
     * Constructor with value scaling parameters, Scales added value to set Waveform scale 
     */
    NexWaveform(uint8_t pid, uint8_t cid, const char *name, 
        int32_t minVal, int32_t maxVal, uint8_t hight,
        const NexObject* page=nullptr);

    /**
     * Add value to show. 
     *
     * @param ch - channel of waveform(0-3). 
     * @param value - the value of waveform.  
     *
     * @retval true - success. 
     * @retval false - failed. 
     */
    bool addValue(uint8_t ch, int32_t value);
	
    /**
     * Get bco attribute of component
     *
     * @param number - buffer storing data retur
     * @return true if success, false for failure
     */
    bool Get_background_color_bco(uint32_t *number);
	
    /**
     * Set bco attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_background_color_bco(uint32_t number);
	
    /**
     * Get gdc attribute of component
     *
     * @param number - buffer storing data retur
     * @return true if success, false for failure
     */
    bool Get_grid_color_gdc(uint32_t *number);	

    /**
     * Set gdc attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_grid_color_gdc(uint32_t number);			
	
    /**
     * Get gdw attribute of component
     *
     * @param number - buffer storing data retur
     * @return true if success, false for failure
     */
    bool Get_grid_width_gdw(uint32_t *number);	

    /**
     * Set gdw attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_grid_width_gdw(uint32_t number);			
	
    /**
     * Get gdh attribute of component
     *
     * @param number - buffer storing data retur
     * @return true if success, false for failure
     */
    bool Get_grid_height_gdh(uint32_t *number);

    /**
     * Set gdh attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_grid_height_gdh(uint32_t number);			
	
    /**
     * Get pco<x> attribute of component
     *
     * @param ch - channel of waveform(0-3). 
     * @param number - buffer storing data retur
     * @return true if success, false for failure
     */
    bool Get_channel_color(uint8_t ch, uint32_t *number);	

    /**
     * Set pco<x> attribute of component
     *
     * @param ch - channel of waveform(0-3). 
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_channel_color(uint8_t ch, uint32_t number);

private:
    int32_t m_minVal;
    int32_t m_maxVal;
    uint8_t m_hight;
    double m_scale;
};

/**
 * @}
 */

#endif /* #ifndef __NEXWAVEFORM_H__ */

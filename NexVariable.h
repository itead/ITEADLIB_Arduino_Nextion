/**
 * @file NexButton.h
 *
 * The definition of class NexButton. 
 *
 * @author huang xiaoming (email:<xiaoming.huang@itead.cc>)
 * @date 2016/9/13
 * @author Jyrki Berg 2/17/2019 (https://github.com/jyberg)
 *
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef __NEXVARRIABLE_H__
#define __NEXVARRIABLE_H__

#include "NexTouch.h"
#include "NexHardware.h"
/**
 * @addtogroup Component 
 * @{ 
 */

/**
 * NexButton component. 
 *
 * Commonly, you want to do something after push and pop it. It is recommanded that only
 * call @ref NexTouch::attachPop to satisfy your purpose. 
 * 
 * @warning Please do not call @ref NexTouch::attachPush on this component, even though you can. 
 */
class NexVariable: public NexTouch
{
public: /* methods */

    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name, const NexObject* page=nullptr);
     */
    NexVariable(uint8_t pid, uint8_t cid, const char *name, const NexObject* page=nullptr);

    /*
    * Get text attribute of component. 
    * 
    * @param str - String storing text returned. 
    *
    * @retval true - success. 
    * @retval false - failed.
    *
    */
    bool getText(String &str);

    /**
     * Get text attribute of component.
     *
     * @param buffer - buffer storing text returned. 
     * @param len - in buffer len / out saved string len excluding null char.  
     * 
     * @retval true - success. 
     * @retval false - failed.
     */
    bool getText(char *buffer, uint16_t &len);   

    /**
     * Set text attribute of component.
     *
     * @param buffer - text buffer terminated with '\0'. 
     * @return true if success, false for failure. 
     */
    bool setText(const char *buffer);    
	
    /**
     * Get val attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
    uint32_t getValue(int32_t *number);
	
    /**
     * Set val attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool setValue(int32_t number);
};
/**
 * @}
 */


#endif /* #ifndef __NEXVARRIABLE_H__*/

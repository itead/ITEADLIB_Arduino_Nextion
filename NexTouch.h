/**
 * @file NexTouch.h
 *
 * The definition of class NexTouch. 
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

#ifndef __NEXTOUCH_H__
#define __NEXTOUCH_H__

#include "application.h"
#include "NexConfig.h"
#include "NexObject.h"

/**
 * @addtogroup TouchEvent 
 * @{ 
 */



/**
 * Type of callback funciton when an touch event occurs. 
 * 
 * @param ptr - user pointer for any purpose. Commonly, it is a pointer to a object. 
 * @return none. 
 */
typedef void (*NexTouchEventCb)(void *ptr);

/**
 * Father class of the components with touch events.  
 *
 * Derives from NexObject and provides methods allowing user to attach
 * (or detach) a callback function called when push(or pop) touch event occurs.
 */
class NexTouch: public NexObject
{
public: /* static methods */    
    static void iterate(NexTouch **list, uint8_t pid, uint8_t cid, int32_t event, void *value);

public: /* methods */

    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name, void *value);
     */
    NexTouch(uint8_t pid, uint8_t cid, const char *name, void *value);

    /**
     * Attach an callback function of push touch event. 
     *
     * @param push - callback called with ptr when a push touch event occurs. 
     * @param ptr - parameter passed into push[default:NULL]. 
     * @return none. 
     *
     * @note If calling this method multiply, the last call is valid. 
     */
    void attachPush(NexTouchEventCb push, void *ptr = NULL);

    /**
     * Detach an callback function. 
     * 
     * @return none. 
     */
    void detachPush(void);

    /**
     * Attach an callback function of pop touch event. 
     *
     * @param pop - callback called with ptr when a pop touch event occurs. 
     * @param ptr - parameter passed into pop[default:NULL]. 
     * @return none. 
     *
     * @note If calling this method multiply, the last call is valid. 
     */
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);

    /**
     * Detach an callback function. 
     * 
     * @return none. 
     */
    void detachPop(void);
    
    
        /**
     * Attach an callback function of value touch event. 
     *
     * @param value - callback called with ptr when a value touch event occurs. 
     * @param ptr - parameter passed into value[default:NULL]. 
     * @return none. 
     *
     * @note If calling this method multiply, the last call is valid. 
     */
    void attachValue(NexTouchEventCb value, void *ptr = NULL);

    /**
     * Detach an callback function. 
     * 
     * @return none. 
     */
    void detachValue(void);
    
private: /* methods */ 
    void push(void);
    void pop(void);
    void value(uint8_t type, void *value);
    
private: /* data */ 
    NexTouchEventCb __cb_push;
    void *__cbpush_ptr;
    NexTouchEventCb __cb_pop;
    void *__cbpop_ptr;
    NexTouchEventCb __cb_value;
    void *__cbvalue_ptr;
};

/**
 * @}
 */

#endif /* #ifndef __NEXTOUCH_H__ */

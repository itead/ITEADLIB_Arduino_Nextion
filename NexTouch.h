/**
 * @file NexTouch.h
 *
 * API of Nextion. 
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

#ifndef __NEXTOUCH_H__
#define __NEXTOUCH_H__
#ifdef __cplusplus
#include <Arduino.h>
#include "NexSerialConfig.h"

typedef uint8_t NexPid;
typedef uint8_t NexCid;

typedef enum {
    NEX_EVENT_POP = 0x00,
    NEX_EVENT_PUSH = 0x01,
    NEX_EVENT_NULL
} NexEventType;

/*The first byte of Nextoin's return value*/
#define NEX_RET_CMD_FINISHED            (0x01)
#define NEX_RET_EVENT_LAUNCHED          (0x88)
#define NEX_RET_EVENT_UPGRADED          (0x89)
#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)     
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_INVALID_CMD             (0x00)
#define NEX_RET_INVALID_COMPONENT_ID    (0x02)
#define NEX_RET_INVALID_PAGE_ID         (0x03)
#define NEX_RET_INVALID_PICTURE_ID      (0x04)
#define NEX_RET_INVALID_FONT_ID         (0x05)
#define NEX_RET_INVALID_BAUD            (0x11)
#define NEX_RET_INVALID_VARIABLE        (0x1A)
#define NEX_RET_INVALID_OPERATION       (0x1B)


typedef void (*NexTouchEventCb)(void *ptr);

/**
 * Root Class of Nextion Components. 
 *
 */
class NexTouch 
{
public: /* static methods */ 
    static uint8_t mainEventLoop(NexTouch **list);
    static void sendCommand(const char *cmd); 
    static bool recvRetCommandFinished(uint32_t timeout = 100);
    static uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout = 500);
    static bool recvRetNumber(uint32_t *number, uint32_t timeout = 500);

public: /* methods */
    NexTouch(NexPid pid, NexCid cid, char *name, 
        NexTouchEventCb pop = NULL, void *pop_ptr = NULL,
        NexTouchEventCb push = NULL, void *push_ptr = NULL);

    NexPid getPid(void);    
    NexCid getCid(void);
    const char *getObjName(void);
    void print(void);

protected: /* static methods */    
    static bool setBrightness(uint32_t brightness);
    static bool getBrightness(uint32_t *brightness);

protected: /* methods */    
    void attachPush(NexTouchEventCb push, void *ptr = NULL);
    void detachPush(void);
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

private: /* static methods */     
    static void iterate(NexTouch **list, NexPid pid, NexCid cid, NexEventType event); 
    
private: /* methods */ 
    void push(void);
    void pop(void);
    
private: /* static data */
    static uint8_t __buffer[256];

private: /* data */ 
    NexPid pid; /* Page ID */
    NexCid cid; /* Component ID */
    char *name; /* An unique name */
    NexTouchEventCb cbPush;
    void *__cbpush_ptr;
    NexTouchEventCb cbPop;
    void *__cbpop_ptr;
};

bool nexInit(void);
bool nexLoop(NexTouch **nexListenList);

/* add new function */
bool  sendCurrentPageId(uint8_t* pageId,uint32_t timeout);
bool TouchCalibration(uint32_t timeout);
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

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXTOUCH_H__ */

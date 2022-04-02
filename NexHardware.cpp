/**
 * @file NexHardware.cpp
 *
 * The implementation of base API for using Nextion. 
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
#include "NexHardware.h"

#define NEX_RET_STARTUP                         (0x00)
#define NEX_RET_CMD_FINISHED                    (0x01)
#define NEX_RET_BUFFER_OVERFLOW                 (0x24)
#define NEX_RET_EVENT_TOUCH_HEAD                (0x65)
#define NEX_RET_CURRENT_PAGE_ID_HEAD            (0x66)
#define NEX_RET_EVENT_POSITION_HEAD             (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD       (0x68)
#define NEX_RET_STRING_HEAD                     (0x70)
#define NEX_RET_NUMBER_HEAD                     (0x71)
#define NEX_RET_SLEEP_MODE_ACTIVATE             (0x86)
#define NEX_RET_SLEEP_MODE_AWAKE                (0x87)
#define NEX_RET_EVENT_LAUNCHED                  (0x88)
#define NEX_RET_EVENT_UPGRADED                  (0x89)
#define NEX_RET_TRANSPARENT_FINISHED            (0XFD)
#define NEX_RET_TRANSPARENT_READY               (0XFE)

#define NEX_RET_INVALID_CMD                     (0x00)
#define NEX_RET_INVALID_COMPONENT_ID            (0x02)
#define NEX_RET_INVALID_PAGE_ID                 (0x03)
#define NEX_RET_INVALID_PICTURE_ID              (0x04)
#define NEX_RET_INVALID_FONT_ID                 (0x05)
#define NEX_RET_INVALID_FILE_OPERATION          (0x06)
#define NEX_RET_INVALID_CRC                     (0x09)
#define NEX_RET_INVALID_BAUD                    (0x11)
#define NEX_RET_INVALID_WAVEFORM                (0x12)
#define NEX_RET_INVALID_VARIABLE                (0x1A)
#define NEX_RET_INVALID_VARIABLE_OPERATION      (0x1B)
#define NEX_RET_INVALID_ASSIGNMENT              (0x1C)
#define NEX_RET_INVALID_EEPROM_OPERATION        (0x1D)
#define NEX_RET_INVALID_QUANTITY                (0x1E)
#define NEX_RET_INVALID_IO_OPERATION            (0x1F)
#define NEX_RET_INVALID_ESCAPE                  (0x20)
#define NEX_RET_INVALID_VARIABLE_NAME           (0x23)

uint16_t nex_coordinates[2] = {};

/*
 * Receive uint32_t data. 
 * 
 * @param number - save uint32_t data. 
 * @param timeout - set timeout time. 
 *
 * @retval true - success. 
 * @retval false - failed.
 *
 */
bool recvRetNumber(uint32_t *number, uint32_t timeout) {
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number) {
        goto __return;
    }
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp))) {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD && temp[5] == 0xFF && temp[6] == 0xFF && temp[7] == 0xFF) {
        *number = ((uint32_t)temp[4] << 24) | ((uint32_t)temp[3] << 16) | (temp[2] << 8) | (temp[1]);
        ret = true;
    }

    __return:

    if (ret) {
        dbSerialPrint("recvRetNumber :");
        dbSerialPrintln(*number);
    } else {
        dbSerialPrintln("recvRetNumber err");
    }
    
    return ret;
}


/*
 * Receive string data. 
 * 
 * @param buffer - save string data. 
 * @param len - string buffer length. 
 * @param timeout - set timeout time. 
 *
 * @return the length of string buffer.
 *
 */
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout) {
    uint16_t ret = 0;
    bool str_start_flag = false;
    uint8_t cnt_0xff = 0;
    String temp = String("");
    uint8_t c = 0;
    long start;

    if (!buffer || len == 0) {
        goto __return;
    }
    
    start = millis();
    while (millis() - start <= timeout) {
        while (nexSerial.available()) {
            c = nexSerial.read();
            if (str_start_flag) {
                if (0xFF == c) {
                    cnt_0xff++;                    
                    if (cnt_0xff >= 3) {
                        break;
                    }
                } else {
                    temp += (char)c;
                }
            }
            else if (NEX_RET_STRING_HEAD == c) {
                str_start_flag = true;
            }
        }
        
        if (cnt_0xff >= 3) {
            break;
        }
    }

    ret = temp.length();
    ret = ret > len ? len : ret;
    strncpy(buffer, temp.c_str(), ret);
    
__return:

    dbSerialPrint("recvRetString[");
    dbSerialPrint(temp.length());
    dbSerialPrint(",");
    dbSerialPrint(temp);
    dbSerialPrintln("]");

    return ret;
}

/*
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void sendCommand(const char* cmd) {
    while (nexSerial.available()) {
        nexSerial.read();
    }
    
    nexSerial.print(cmd);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
    delay(10);
}


/*
 * Command is executed successfully. 
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed. 
 *
 */
bool recvRetCommandFinished(uint32_t timeout) {    
    bool ret = false;
    uint8_t temp[4] = {0};
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))     {
        ret = false;
    }

    if (temp[0] == NEX_RET_CMD_FINISHED && temp[1] == 0xFF && temp[2] == 0xFF && temp[3] == 0xFF) {
        ret = true;
    }

    if (ret) {
        dbSerialPrintln("recvRetCommandFinished ok");
    } else {
        dbSerialPrintln("recvRetCommandFinished err");
    }
    
    return ret;
}


bool nexInit(void) {
    bool ret1 = false;
    bool ret2 = false;
    
    dbSerialBegin(115200); //(9600);
    nexSerial.begin(115200); //(9600);
    sendCommand("");
    sendCommand("bkcmd=0"); //("bkcmd=1")
    ret1 = recvRetCommandFinished();
    sendCommand("page 0");
    ret2 = recvRetCommandFinished();
    return ret1 && ret2;
}

void nexLoop(NexTouch *nex_listen_list[]) {
    static uint8_t __buffer[10];
    
    uint16_t i;
    uint8_t c;  
    
    
    while (nexSerial.available() > 0) {   
        delay(20);
        dbSerialPrint(nexSerial.peek(), HEX);
        switch(nexSerial.peek()) {
            case NEX_RET_STARTUP || NEX_RET_INVALID_CMD: 
                nexSerial.readBytes(__buffer,4); // 0x00 0xFF 0xFF 0xFF
                if(__buffer[1] == 0xFF && __buffer[2] == 0xFF && __buffer[3] == 0xFF) {
                    dbSerialPrintln(" Invalid Instruction");
                } else {
                    dbSerialPrintln(" Nextion Startup"); // 0x00 0x00 0x00 0xFF 0xFF 0xFF
                    __buffer[4] = nexSerial.read();
                    __buffer[5] = nexSerial.read();
                }
                break;
            case NEX_RET_CMD_FINISHED: // 0x01 0xFF 0xFF 0xFF
                dbSerialPrintln(" Command succsessfull");
                nexSerial.readBytes(__buffer, 4);
                break;
            case NEX_RET_BUFFER_OVERFLOW:
                dbSerialPrintln(" Buffer Overflow");
                nexSerial.readBytes(__buffer, 4); // 0x24 0xFF 0xFF 0xFF
                break;
            case NEX_RET_EVENT_TOUCH_HEAD:
                dbSerialPrintln(" Touch Event");
                nexSerial.readBytes(__buffer, 7); // 0x65 0x00 0x01 0x01 0xFF 0xFF 0xFF
                NexTouch::iterate(nex_listen_list, __buffer[1], __buffer[2], (int32_t)__buffer[3]);
                break;
            case NEX_RET_CURRENT_PAGE_ID_HEAD:
                dbSerialPrintln(" Current Page Number");
                nexSerial.readBytes(__buffer, 5); // 0x66 0x01 0xFF 0xFF 0xFF
                NexTouch::iterate(nex_listen_list, __buffer[1], 0, 1);
                break;
            case NEX_RET_EVENT_POSITION_HEAD:
                dbSerialPrintln(" Touch Coordinate (awake)");
                nexSerial.readBytes(__buffer, 9); // 0x67 0x00 0x7A 0x00 0x1E 0x01 0xFF 0xFF 0xFF
                nex_coordinates[0] = ((uint16_t)__buffer[1] << 8) + __buffer[2];
                nex_coordinates[1] = ((uint16_t)__buffer[3] << 8) + __buffer[4];
                nex_coordinates[2] = __buffer[5];
                break;
            case NEX_RET_EVENT_SLEEP_POSITION_HEAD:
                dbSerialPrintln(" Touch Coordinate (sleep)");
                nexSerial.readBytes(__buffer, 9); // 0x68 0x00 0x7A 0x00 0x1E 0x01 0xFF 0xFF 0xFF
                break;
            case NEX_RET_STRING_HEAD: // 0x70 0x61 0x62 0x31 0x32 0x33 0xFF 0xFF 0xFF
                dbSerialPrintln(" String Data Enclosed");

                break;
            case NEX_RET_NUMBER_HEAD:
                dbSerialPrintln(" Numeric Data Enclosed");
                //nexSerial.readBytes(__buffer, 8); // 0x71 0x01 0x02 0x03 0x04 0xFF 0xFF 0xFF
                //__buffer[4] << 24 + __buffer[3] << 16 + __buffer[2] << 8 + __buffer[1];
                break;
            case NEX_RET_SLEEP_MODE_ACTIVATE:
                dbSerialPrintln(" Auto Entered Sleep Mode");
                nexSerial.readBytes(__buffer, 4); // 0x86 0xFF 0xFF 0xFF
                break;
            case NEX_RET_SLEEP_MODE_AWAKE:
                dbSerialPrintln(" Auto Wake from Sleep");
                nexSerial.readBytes(__buffer, 4); // 0x87 0xFF 0xFF 0xFF
                break;
            case NEX_RET_EVENT_LAUNCHED:
                dbSerialPrintln(" Nextion Ready");
                nexSerial.readBytes(__buffer, 4); // 0x88 0xFF 0xFF 0xFF
                break;
            case NEX_RET_EVENT_UPGRADED:
                dbSerialPrintln(" Start microSD Upgrade");
                nexSerial.readBytes(__buffer, 4); // 0x89 0xFF 0xFF 0xFF
                break;
            case NEX_RET_TRANSPARENT_FINISHED:
                dbSerialPrintln(" Transparent Data Finished");
                nexSerial.readBytes(__buffer, 4); // 0xFD 0xFF 0xFF 0xFF
                break;
            case NEX_RET_TRANSPARENT_READY:
                dbSerialPrintln(" Transparent Data Ready");
                nexSerial.readBytes(__buffer, 4); // 0xFE 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_COMPONENT_ID:
                dbSerialPrintln(" Invalid Component ID");
                nexSerial.readBytes(__buffer, 4); // 0x02 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_PAGE_ID:
                dbSerialPrintln(" Invalid Page ID"); 
                nexSerial.readBytes(__buffer, 4); // 0x03 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_PICTURE_ID:
                dbSerialPrintln(" Invalid Picture ID"); 
                nexSerial.readBytes(__buffer, 4); // 0x04 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_FONT_ID:
                dbSerialPrintln(" Invalid Font ID"); 
                nexSerial.readBytes(__buffer, 4); // 0x05 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_FILE_OPERATION:
                dbSerialPrintln(" Invalid File Operation"); 
                nexSerial.readBytes(__buffer, 4); // 0x06 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_CRC:
                dbSerialPrintln(" Invalid CRC"); 
                nexSerial.readBytes(__buffer, 4); // 0x09 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_BAUD:
                dbSerialPrintln(" Invalid Baud rate Setting"); 
                nexSerial.readBytes(__buffer, 4); // 0x11 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_WAVEFORM:
                dbSerialPrintln(" Invalid Waveform ID or Channel #"); 
                nexSerial.readBytes(__buffer, 4); // 0x12 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_VARIABLE:
                dbSerialPrintln(" Invalid Variable name or attribute"); 
                nexSerial.readBytes(__buffer, 4); // 0x1A 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_VARIABLE_OPERATION:
                dbSerialPrintln(" Invalid Variable Operation"); 
                nexSerial.readBytes(__buffer, 4); // 0x1B 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_ASSIGNMENT:
                dbSerialPrintln(" Assignment failed to assign"); 
                nexSerial.readBytes(__buffer, 4); // 0x1C 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_EEPROM_OPERATION:
                dbSerialPrintln(" Assignment failed to assign"); 
                nexSerial.readBytes(__buffer, 4); // 0x1D 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_QUANTITY:
                dbSerialPrintln(" Invalid Quantity of Parameters"); 
                nexSerial.readBytes(__buffer, 4); // 0x1E 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_IO_OPERATION:
                dbSerialPrintln(" IO Operation failed"); 
                nexSerial.readBytes(__buffer, 4); // 0x1F 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_ESCAPE:
                dbSerialPrintln(" IO Operation failed"); 
                nexSerial.readBytes(__buffer, 4); // 0x20 0xFF 0xFF 0xFF
                break;
            case NEX_RET_INVALID_VARIABLE_NAME:
                dbSerialPrintln(" Variable name too long"); 
                nexSerial.readBytes(__buffer, 4); // 0x23 0xFF 0xFF 0xFF
                break;
            default:
                nexSerial.read();
                break;
        }
    }
}


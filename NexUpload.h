/**
 * @file NexUpload.h
 *
 * The definition of class NexUpload. 
 *
 * @author Chen Zengpeng (email:<zengpeng.chen@itead.cc>)
 * @date 2016/3/29
 *
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#ifndef __NEXUPLOAD_H__
#define __NEXUPLOAD_H__
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "NexHardware.h"

/**
 * @addtogroup CoreAPI 
 * @{ 
 */

/**
 *
 * Provides the API for nextion to download the ftf file.
 */
class NexUpload
{
public: /* methods */

    /**
     * Constructor. 
     * 
     * @param file_name - tft file name. 
     * @param SD_chip_select - sd chip select pin.
     * @param download_baudrate - set download baudrate.
     */
    NexUpload(const char *file_name,const uint8_t SD_chip_select,uint32_t download_baudrate);
    
    /**
     * Constructor. 
     * 
     * @param file_Name - tft file name. 
     * @param SD_chip_select - sd chip select pin.
     * @param download_baudrate - set download baudrate.
     */
    NexUpload(const String file_Name,const uint8_t SD_chip_select,uint32_t download_baudrate); 
    
    /**
     * destructor. 
     * 
     */
    ~NexUpload(){}
    
    /*
     * start download.
     *
     * @return none.
     */
    void upload();

private: /* methods */

    /*
     * get communicate baudrate. 
     * 
     * @return communicate baudrate.
     *
     */
    uint16_t _getBaudrate(void);
    
    /*
     * check tft file.
     *
     * @return true if success, false for failure. 
     */
    bool _checkFile(void);

    /*
     * search communicate baudrate.
     *
     * @param baudrate - communicate baudrate.
     *   
     * @return true if success, false for failure. 
     */
    bool _searchBaudrate(uint32_t baudrate);

    /*
     * set download baudrate.
     *
     * @param baudrate - set download baudrate.
     *   
     * @return true if success, false for failure. 
     */
    bool _setDownloadBaudrate(uint32_t baudrate);
    
    /**
     * start dowload tft file to nextion. 
     * 
     * @return none. 
     */
    bool _downloadTftFile(void);
    
    /*
     * Send command to Nextion.
     *
     * @param cmd - the string of command.
     *
     * @return none.
     */
    void sendCommand(const char* cmd);

    /*
     * Receive string data. 
     * 
     * @param buffer - save string data.  
     * @param timeout - set timeout time. 
     * @param recv_flag - if recv_flag is true,will braak when receive 0x05.
     *
     * @return the length of string buffer.
     *
     */   
    uint16_t recvRetString(String &string, uint32_t timeout = 100,bool recv_flag = false);
    
private: /* data */ 
    uint32_t _baudrate; /*nextion serail baudrate*/
    const char *_file_name; /*nextion tft file name*/
    File _myFile; /*nextion ftf file*/
    uint32_t _undownloadByte; /*undownload byte of tft file*/
    uint8_t _SD_chip_select; /*sd chip select pin*/
    uint32_t _download_baudrate; /*download baudrate*/
};
/**
 * @}
 */

#endif /* #ifndef __NEXDOWNLOAD_H__ */

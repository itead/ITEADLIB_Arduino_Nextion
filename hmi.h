/**
  * @file hmi.h
  * @brief The definition of class HMI. 
  * @author laicheng.zhang@itead.cc
  * @date 2015.04
  */
#ifndef  __HMI_H__
#define  __HMI_H__
#include "arduino.h"

/**
  * You can modify the macro to choose sofware serial or hardware serial. 
  */
//#define HMI_SOFTWARE_SERIAL

#ifdef HMI_SOFTWARE_SERIAL 
#include "SoftwareSerial.h"
typedef SoftwareSerial HMISerial; 	
#else 		  
typedef HardwareSerial HMISerial; 
#endif /* #ifdef HMI_SOFTWARE_SERIAL */

/** 
  *  HMI class. 
  *
  *  used to operate LCD touch screen.  
  */
class HMI
{    		
public:

    /**
      * Constuctor. 
      *
      * @param uart - an reference of user serial object. 
      * @param baud - the buad rate to communicate with LCD touch screen(default:9600). 
      *  
      */
    HMI(HMISerial &uart, uint32_t baud = 9600);
	
    /** 
      * Edit text. 
      *
      * @param  text_id - text id.  
      * @param  value - text value.  	 
      * @retval true - success.  
      * @retval false - failure.
      *	
      */
    bool textEdit(char *text_id,char *value); 
	
    /** 
      * Edit picture. 
      *
      * @param  picture_id - picture name.    
      * @param  value - picture value. 	 
      * @retval true - success.  
      * @retval false - failure.
      *	
      */
    bool pictureEdit(char *picture_id,uint32_t value);    
    
     /** 
       * Progress bar edit. 
       *
       * @param  bar_id - progress bar name.    
       * @param  value - progress bar value. 	 
       * @retval true - success.   
       * @retval false - failure. 
       *	
       */
    bool progressBarEdit(char *bar_id,uint32_t value);  
    
     /** 
       * Cut picture. 
       *
       * @param  picture_id - picture name.    
       * @param  value - picture value. 	 
       * @retval true - success.  
       * @retval false - failure. 
       *	
       */
     bool cutPicture(char *picture_id,uint32_t value); 

     /** 
       * Page change. 
       *
       * @param  page_id - page id.     	 
       * @retval true - success. 
       * @retval false - failure. 
       *	
       */
    bool pageChange(uint32_t page_id); 

    /** 
      * The LCD touch screen calibration. 
      *   	 
      * @param  data_buffer - get data from LCD ,it is a input parameter.  
      *  
      */
    void readLcdData(unsigned char *data_buffer); 

    /** 
      * The LCD touch screen calibration. 
      *   	 
      * @retval true - success. 
      * @retval false - failure. 	 
      *  
      */
    bool touchCalibration(void);

    /** 
      * Disable touch focus.  
      *   	 
      * @retval true - success. 
      * @retval false - failure. 	 
      *  
      */
    bool disableTouchFocus(void); 

     /** 
       * Pause serial command from UNO. 
       *   	 
       * @retval true - success. 
       * @retval false - failure. 	 
       *  
       */
    bool pauseSerialCommand(void); 

     /** 
       * Recovery serial command from UNO. 
       *   	 
       * @retval true - success. 
       * @retval false - failure. 	 
       *  
       */
    bool recoverySerialCommand(void);

     /** 
       * Empty serial command from UNO. 
       *   	 
       * @retval true - success. 
       * @retval false - failure. 	 
       *  
       */
    bool emptySerialCommand(void); 
	
     /** 
       * Return current page id.  
       *   	 
       * @retval >=0 - current page id.  
       * @retval <0 - return page id failure. 	 
       *  
       */
    uint32_t  returnPageId(void);      	
private:
	
     /** 
       * The return value judgement. 
       *   	 
       * @retval true - success. 
       * @retval false - failure. 	 
       *  
       */
    bool returnIsRight(void); 
	
    /**
      * Clean data receive buffer,from LCD serial. 
      */
    void cleanBuffer(void);    
	
     /**
       * Clear serial buffer. 
       */
    void setRxEmpty(void);

    /**
      * Data receive buffer, from LCD serial. 
      */     
    unsigned char buffer[100];
    
    /**
      * Command end flag. 
      */ 	
    void commandEnd(void);   
	
    /**
      * Point to the current user serial.  
      */ 
    HMISerial *my_uart;        
};
#endif














/**
  * @file hmi.cpp
  * @brief The implementation of class HMI. 
  * @author laicheng.zhang@itead.cc
  * @date 2015.04
  */

#include "hmi.h"
HMI::HMI(HMISerial &uart,uint32_t baud)
{
	my_uart = &uart; 
        my_uart->begin(baud);
        setRxEmpty();
}
	 
bool HMI::textEdit(char *text_id,char *value)
{
	/*t0.txt="abc"*/ 
	char cmd[50] = {0};
	strcat(cmd,text_id);
	strcat(cmd,".txt=\"");
	strcat(cmd,value);
	strcat(cmd,"\"");
	my_uart->print(cmd);
        commandEnd();
	 
	if (returnIsRight() == 0)
		return true;
        else 
		return false;	
} 

bool HMI::pictureEdit(char *picture_id,uint32_t value)
{
	/*p0.pic=6*/ 
	char cmd[50] = {0};
	char valuetemp[25] = {0};
	itoa(value,valuetemp,10);
	strcat(cmd,picture_id);
	strcat(cmd,".pic=");
	strcat(cmd,valuetemp);
		
	my_uart->print(cmd);
	commandEnd();
    
	if (returnIsRight() == 0)
	return true;
		else 
	return false;	
}

bool HMI::progressBarEdit(char *bar_id,uint32_t value)
{
	char  cmd[50] = {0};
	char valuetemp[25] = {0};
	itoa(value,valuetemp,10);
	strcat(cmd,bar_id);
	strcat(cmd,".val=");
	strcat(cmd,valuetemp);
	
	my_uart->print(cmd);
	commandEnd();
	
	if (returnIsRight() == 0)
		return true;
	else 
		return false;				
}

bool HMI::cutPicture(char *picture_id,uint32_t value)
{  
	char cmd[50] = {0};
	char valuetemp[25] = {0};
	itoa(value,valuetemp,10);
	strcat(cmd,picture_id);
	strcat(cmd,".pic=");
	strcat(cmd,valuetemp);
    
	my_uart->print(cmd);
	commandEnd();
    
	if (returnIsRight() == 0)
		return true;
	else 
		return false;
}

bool HMI::pageChange(uint32_t page_id)
{        
	char  cmd[50] = {0};
	char page_idtemp[25] = {0};
	itoa(page_id,page_idtemp,10);
	strcat(cmd,"page");
	strcat(cmd," ");
	strcat(cmd,page_idtemp);
	my_uart->print(cmd);
	
	commandEnd();  
	delay(200);
	if (returnIsRight() == 0)
		return true;
	else 
		return false; 		
}

void HMI::readLcdData(unsigned char *data_buffer)
{   
	delay(10);
	cleanBuffer();
	uint32_t i = 0;
	while(my_uart->available() <= 0);
	while(my_uart->available() > 0)
	{   
		delay(3);     
		buffer[i] = (unsigned char)my_uart->read();
		i++;
	}
	if (buffer[0] == 0x70)
	{
		uint32_t j = 0;
		uint32_t k = 1;
		for(j=0;j<strlen((char*)buffer)-4;)
		{
			data_buffer[j]=buffer[k];	
			j++;
			k++;
		}			
	}			
}

bool HMI::returnIsRight(void)
{
	delay(10);
	uint32_t tempid = 0;
	unsigned char temp[20] = {0};
	unsigned char temp1[4] = {0x01,0xFF,0xFF,0xFF};
	    
	tempid = my_uart->available();
	uint32_t i = 0;
	while(my_uart->available())
	{
		temp[i] = (unsigned char)my_uart->read();
		i++;
	}
	if((tempid==4)&&(strncmp((char*)temp1,(char*)temp,4)==0))
	{  
		return 0;
	}
	else
	{   
		return -1;
	} 	
}

bool HMI::touchCalibration(void)                  
{   
	/*Serial.println("touch Calibration");*/
	my_uart->print("touch_j");
	commandEnd(); 	
	delay(5000);
	if (returnIsRight() == 0)
		return true;
	else 
		return false;
		
}

bool HMI::disableTouchFocus(void)                   
{  
	    /*Serial.println("disableTouchFocus");*/
	my_uart->print("cle_c");
	commandEnd();
	if (returnIsRight() == 0)
		return true;
	else 
		return false;	
}

bool HMI::pauseSerialCommand(void)                  
{   
	/*Serial.println("pauseSerialCommand");*/
	my_uart->print("com_stop");
	commandEnd();
	if (returnIsRight() == 0)
		return true;
	else 
		return false;		
}

bool HMI::recoverySerialCommand(void)               
{  
	/*Serial.println("recoverySerialCommand");*/
	my_uart->print("com_star");
	commandEnd();
	if (returnIsRight() == 0)
		return true;
	else 
		return false;	
}

bool HMI::emptySerialCommand(void)                  
{   
	/*Serial.println("emptySerialCommand");*/
	my_uart->print("code_c");
	commandEnd();
	if (returnIsRight() == 0)
		return true;
	else 
		return false;
}

uint32_t HMI::returnPageId(void)                      
{    
	my_uart->print("sendme"); 
	commandEnd();
	
	delay(50);
	unsigned char temp1[] = {0x66,0xFF,0xFF,0xFF};
	unsigned char temp[10] = {0};
	uint32_t j = 0;
	while(my_uart->available() > 0)
	{
		temp[j] = (unsigned char)my_uart->read();
		delay(3);
		j++;
	}
	
	if(!strcmp((char*)temp1[0],(char*)temp[0]))
	{    
		return (uint32_t)temp[1];
	}	
	else 
		return -1;		
}

void HMI::setRxEmpty(void)
{
	while(my_uart->available() > 0)
	{
		my_uart->read();
	}
}

void HMI::cleanBuffer(void)
{
	memset(buffer,0,strlen((char*)buffer));	
}

void HMI::commandEnd(void)
{
	my_uart->write(0xFF);
        my_uart->write(0xFF);
        my_uart->write(0xFF);		
}




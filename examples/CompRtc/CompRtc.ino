#include "Nextion.h"

NexText t0 = NexText(0,1,"t0");
NexRtc  rtc;
uint32_t  time[7] = {2016,11,25,12,34,50};
uint8_t time_buf[30] = {0};

void setup() 
{
    nexSerial.begin(115200);
    rtc.write_rtc_time(time);
}

void loop() 
{
    rtc.read_rtc_time(time_buf,30);
    t0.setText(time_buf);
    delay(1000);
}

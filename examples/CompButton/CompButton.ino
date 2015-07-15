#include "NexButton.h"

NexButton b0 = NexButton(0, 1, "b0");
char buffer[100] = {0};

NexTouch *nexListenList[] = 
{
    &b0,
    NULL
};

void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    NexButton *btn = (NexButton *)ptr;
    
    dbSerial.println("b0PopCallback");
    dbSerial.print("ptr=");
    dbSerial.println((uint32_t)ptr);
    
    memset(buffer, 0, sizeof(buffer));
    btn->getText(buffer, sizeof(buffer));
    
    number = atoi(buffer);
    number += 1;

    memset(buffer, 0, sizeof(buffer));
    itoa(number, buffer, 10);
    
    btn->setText(buffer);
}

void setup(void)
{
    dbSerial.begin(9600);
    nexInit();
    b0.attachPop(b0PopCallback, &b0);
    dbSerial.println("setup done");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}

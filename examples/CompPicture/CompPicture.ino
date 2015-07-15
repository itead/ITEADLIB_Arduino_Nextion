#include "NexPicture.h"

NexPicture p0 = NexPicture(0, 1, "p0");

NexTouch *nexListenList[] = 
{
    &p0,
    NULL
};

void p0PopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerial.println("p0PopCallback");

    p0.getPic(&number);

    if (number == 1)
    {
        number = 2;    
    }
    else
    {
        number = 1;
    }
    
    p0.setPic(number);
}


void setup(void)
{
    dbSerial.begin(9600);
    nexInit();
    p0.attachPop(p0PopCallback);
    dbSerial.println("setup done");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}


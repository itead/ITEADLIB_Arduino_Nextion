#include "NexSlice.h"

NexSlice q0 = NexSlice(0, 1, "q0");

NexTouch *nexListenList[] = 
{
    &q0,
    NULL
};

void q0PopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerial.println("q0PopCallback");

    q0.getPic(&number);

    number += 1;
    number %= 2;
    
    q0.setPic(number);
}


void setup(void)
{
    dbSerial.begin(9600);
    nexInit();
    q0.attachPop(q0PopCallback);
    dbSerial.println("setup done");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}


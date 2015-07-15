#include "NexPointer.h"
#include "NexButton.h"

NexPointer pointer  = NexPointer(0, 1, "pointer");
NexButton btn_up   = NexButton(0, 2, "btn_up");
NexButton btn_down = NexButton(0, 3, "btn_down");

NexTouch *nexListenList[] = 
{
    &btn_up,
    &btn_down,
    NULL
};

void buttonUpPopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerial.println("buttonUpPopCallback");

    pointer.getValue(&number);

    number += 5;
    if (number >= 360)
    {
        number = 0;
    }
    
    pointer.setValue(number);
}
void buttonDownPopCallback(void *ptr)
{
    uint32_t number = 0;
    dbSerial.println("buttonDownPopCallback");

    pointer.getValue(&number);

    if (number >= 5)
    {
        number -= 5;
    }
    
    pointer.setValue(number);
}



void setup(void)
{
    dbSerial.begin(9600);
    nexInit();
    btn_up.attachPop(buttonUpPopCallback);
    btn_down.attachPop(buttonDownPopCallback);
    dbSerial.println("setup done");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}


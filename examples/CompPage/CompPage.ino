#include "NexPage.h"

NexPage page0    = NexPage(0, 0, "page0");
NexPage page1    = NexPage(1, 0, "page1");
NexPage page2    = NexPage(2, 0, "page2");
NexPage page3    = NexPage(3, 0, "page3");

NexTouch *nexListenList[] = 
{
    &page0,
    &page1,
    &page2,
    &page3,
    NULL
};

void page0PopCallback(void *ptr)
{
    dbSerial.println("page0PopCallback");
    page1.show();
}

void page1PopCallback(void *ptr)
{
    dbSerial.println("page1PopCallback");
    page2.show();
}

void page2PopCallback(void *ptr)
{
    dbSerial.println("page2PopCallback");
    page3.show();
}

void page3PopCallback(void *ptr)
{
    dbSerial.println("page3PopCallback");
    page0.show();
}

void setup(void)
{   
    dbSerial.begin(9600);
    nexInit();
    dbSerial.println("setup begin");
    
    page0.attachPop(page0PopCallback);
    page1.attachPop(page1PopCallback);
    page2.attachPop(page2PopCallback);
    page3.attachPop(page3PopCallback);
    
    dbSerial.println("setup end");
}

void loop(void)
{
    dbSerial.println("nexLoop");
    nexLoop(nexListenList);
}

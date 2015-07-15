#include "NexPage.h"

NexPage::NexPage(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

bool NexPage::show(void)
{
    uint8_t buffer[4] = {0};

    const char *name = getObjName();
    if (!name)
    {
        return false;
    }
    
    String cmd = String("page ");
    cmd += name;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

void NexPage::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

void NexPage::detachPop(void)
{
    NexTouch::detachPop();   
}

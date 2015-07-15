#include "NexPicture.h"


NexPicture::NexPicture(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

bool NexPicture::getPic(uint32_t *number)
{
    String cmd = String("get ");
    cmd += getObjName();
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexPicture::setPic(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".pic=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


void NexPicture::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

void NexPicture::detachPop(void)
{
    NexTouch::detachPop();   
}
 

#include "NexSlice.h"


NexSlice::NexSlice(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

bool NexSlice::getPic(uint32_t *number)
{
    String cmd = String("get ");
    cmd += getObjName();
    cmd += ".picc";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexSlice::setPic(uint32_t number)
{
    char buf[10] = {0};
    String cmd;
    
    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".picc=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


void NexSlice::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

void NexSlice::detachPop(void)
{
    NexTouch::detachPop();   
}
 

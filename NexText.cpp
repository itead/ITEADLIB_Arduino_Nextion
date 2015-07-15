#include "NexText.h"


NexText::NexText(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop, void *pop_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr)
{
}

uint16_t NexText::getText(char *buffer, uint16_t len)
{
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexText::setText(const char *buffer)
{
    String cmd;
    cmd += getObjName();
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

void NexText::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

void NexText::detachPop(void)
{
    NexTouch::detachPop();   
}
 

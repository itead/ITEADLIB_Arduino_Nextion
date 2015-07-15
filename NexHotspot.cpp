#include "NexHotspot.h"

NexHotspot::NexHotspot(NexPid pid, NexCid cid, char *name, 
    NexTouchEventCb pop, void *pop_ptr,
    NexTouchEventCb push, void *push_ptr)
    :NexTouch(pid, cid, name, pop, pop_ptr, push, push_ptr)
{
}

void NexHotspot::attachPush(NexTouchEventCb push, void *ptr)
{
    NexTouch::attachPush(push, ptr);
}

void NexHotspot::detachPush(void)
{
    NexTouch::detachPush();
}

void NexHotspot::attachPop(NexTouchEventCb pop, void *ptr)
{
    NexTouch::attachPop(pop, ptr);
}

void NexHotspot::detachPop(void)
{
    NexTouch::detachPop();   
}

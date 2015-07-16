#ifndef __NEXPOINTER_H__
#define __NEXPOINTER_H__
#ifdef __cplusplus
#include "NexTouch.h"

/**
 * NexPointer,subclass of NexTouch,provides simple methods to control pointer component.
 *
 */
class NexPointer: public NexTouch
{
public: /* methods */
    NexPointer(NexPid pid, NexCid cid, char *name);
    
    bool getValue(uint32_t *number);
    bool setValue(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPOINTER_H__ */

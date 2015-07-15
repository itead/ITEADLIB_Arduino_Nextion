#ifndef __NEXPROGRESSBAR_H__
#define __NEXPROGRESSBAR_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * NexProgressBar
 */
class NexProgressBar: public NexTouch
{
public: /* methods */
    NexProgressBar(NexPid pid, NexCid cid, char *name);
    
    bool getValue(uint32_t *number);
    bool setValue(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPROGRESSBAR_H__ */

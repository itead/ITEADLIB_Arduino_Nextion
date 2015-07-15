#ifndef __NEXSLICE_H__
#define __NEXSLICE_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * NexSlice
 */
class NexSlice: public NexTouch
{
public: /* methods */
    NexSlice(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

    bool getPic(uint32_t *number);
    bool setPic(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXSLICE_H__ */

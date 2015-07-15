#ifndef __NEXHOTSPOT_H__
#define __NEXHOTSPOT_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * Hotspot
 */
class NexHotspot: public NexTouch
{
public: /* methods */
    NexHotspot(NexPid pid, NexCid cid, char *name, 
        NexTouchEventCb pop = NULL, void *pop_ptr = NULL,
        NexTouchEventCb push = NULL, void *push_ptr = NULL);

    void attachPush(NexTouchEventCb push, void *ptr = NULL);
    void detachPush(void);
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXHOTSPOT_H__ */

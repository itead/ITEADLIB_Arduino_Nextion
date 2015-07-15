#ifndef __NEXPICTURE_H__
#define __NEXPICTURE_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * NexPicture
 */
class NexPicture: public NexTouch
{
public: /* methods */
    NexPicture(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

    bool getPic(uint32_t *number);
    bool setPic(uint32_t number);
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPICTURE_H__ */

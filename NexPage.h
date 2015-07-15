#ifndef __NEXPAGE_H__
#define __NEXPAGE_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * Page
 */
class NexPage: public NexTouch
{
public: /* methods */
    NexPage(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    bool show(void);

    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXPAGE_H__ */

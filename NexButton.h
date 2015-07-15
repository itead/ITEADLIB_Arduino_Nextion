#ifndef __NEXBUTTON_H__
#define __NEXBUTTON_H__
#ifdef __cplusplus
#include "NexTouch.h"


/*
 * Button
 */
class NexButton: public NexTouch
{
public: /* methods */
    NexButton(NexPid pid, NexCid cid, char *name, NexTouchEventCb pop = NULL, void *pop_ptr = NULL);
    
    void attachPop(NexTouchEventCb pop, void *ptr = NULL);
    void detachPop(void);

    uint16_t getText(char *buffer, uint16_t len);    
    bool setText(const char *buffer);    
};

#endif /* #ifdef __cplusplus */
#endif /* #ifndef __NEXBUTTON_H__ */

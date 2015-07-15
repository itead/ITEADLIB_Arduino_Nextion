#include "NexTouch.h"

uint8_t NexTouch::__buffer[256] = {0};

uint8_t NexTouch::mainEventLoop(NexTouch **list)
{
    uint16_t i;
    uint8_t c;
    
    while (true)
    {
        while (nexSerial.available() > 0)
        {   
            delay(10);
            c = nexSerial.read();
            
            if (NEX_RET_EVENT_TOUCH_HEAD == c)
            {
                if (nexSerial.available() >= 6)
                {
                    //memset(__buffer, 0, sizeof(__buffer));
                    __buffer[0] = c;  
                    for (i = 1; i < 7; i++)
                    {
                        __buffer[i] = nexSerial.read();
                    }
                    __buffer[i] = 0x00;
                    
                    if (0xFF == __buffer[4] && 0xFF == __buffer[5] && 0xFF == __buffer[6])
                    {
                        iterate(list, (NexPid)__buffer[1], (NexCid)__buffer[2], (NexEventType)__buffer[3]);
                    }
                    
                }
            }
        }
    }        
    return 0;
}

NexTouch::NexTouch(NexPid pid, NexCid cid, char *name, 
    NexTouchEventCb pop, void *pop_ptr,
    NexTouchEventCb push, void *push_ptr)
{
    this->pid = pid;
    this->cid = cid;
    this->name = name;
    this->cbPush = push;
    this->cbPop = pop;
    this->__cbpop_ptr = pop_ptr;
    this->__cbpush_ptr = push_ptr;
}

NexPid NexTouch::getPid(void)
{
    return pid;
}

NexCid NexTouch::getCid(void)
{
    return cid;
}

const char* NexTouch::getObjName(void)
{
    return name;
}

void NexTouch::print(void)
{
    dbSerial.print("[");
    dbSerial.print((uint32_t)this);
    dbSerial.print(":");
    dbSerial.print(pid);
    dbSerial.print(",");
    dbSerial.print(cid);
    dbSerial.print(",");
    if (name)
    {
        dbSerial.print(name);
    }
    else
    {
        dbSerial.print("(null)");
    }
    dbSerial.print(",");
    dbSerial.print((uint32_t)cbPush);
    dbSerial.print(",");
    dbSerial.print((uint32_t)cbPop);
    dbSerial.println("]");
}

void NexTouch::attachPush(NexTouchEventCb push, void *ptr)
{
    this->cbPush = push;
    this->__cbpush_ptr = ptr;
}

void NexTouch::detachPush(void)
{
    this->cbPush = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPop(NexTouchEventCb pop, void *ptr)
{
    this->cbPop = pop;
    this->__cbpop_ptr = ptr;
}

void NexTouch::detachPop(void)
{
    this->cbPop = NULL;    
    this->__cbpop_ptr = NULL;
}

    
void NexTouch::iterate(NexTouch **list, NexPid pid, NexCid cid, NexEventType event)
{
    NexTouch *e = NULL;
    uint16_t i = 0;

    if (NULL == list)
    {
        return;
    }
    
    for(i = 0; (e = list[i]) != NULL; i++)
    {
        if (e->getPid() == pid && e->getCid() == cid)
        {
            e->print();
            if (NEX_EVENT_PUSH == event)
            {
                e->push();
            }
            else if (NEX_EVENT_POP == event)
            {
                e->pop();
            }
            
            break;
        }
    }
}


void NexTouch::push(void)
{
    if (cbPush)
    {
        cbPush(__cbpush_ptr);
    }
}

void NexTouch::pop(void)
{
    if (cbPop)
    {
        cbPop(__cbpop_ptr);
    }
}

bool NexTouch::recvRetCommandFinished(uint32_t timeout)
{    
    bool ret = false;
    uint8_t temp[4] = {0};
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        ret = false;
    }

    if (temp[0] == NEX_RET_CMD_FINISHED
        && temp[1] == 0xFF
        && temp[2] == 0xFF
        && temp[3] == 0xFF
        )
    {
        ret = true;
    }

    if (ret) 
    {
        dbSerial.println("recvRetCommandFinished ok");
    }
    else
    {
        dbSerial.println("recvRetCommandFinished err");
    }
    
    return ret;
}

void NexTouch::sendCommand(const char* cmd)
{
    while (nexSerial.available())
    {
        nexSerial.read();
    }
    
    nexSerial.print(cmd);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
    nexSerial.write(0xFF);
}

/* 0X70 0X61 0X62 0X63 0x... 0XFF 0XFF 0XFF */
uint16_t NexTouch::recvRetString(char *buffer, uint16_t len, uint32_t timeout)
{
    uint16_t ret = 0;
    bool str_start_flag = false;
    uint8_t cnt_0xff = 0;
    String temp = String("");
    uint8_t c = 0;
    long start;

    if (!buffer || len == 0)
    {
        goto __return;
    }
    
    start = millis();
    while (millis() - start <= timeout)
    {
        while (nexSerial.available())
        {
            c = nexSerial.read();
            if (str_start_flag)
            {
                if (0xFF == c)
                {
                    cnt_0xff++;                    
                    if (cnt_0xff >= 3)
                    {
                        break;
                    }
                }
                else
                {
                    temp += (char)c;
                }
            }
            else if (NEX_RET_STRING_HEAD == c)
            {
                str_start_flag = true;
            }
        }
        
        if (cnt_0xff >= 3)
        {
            break;
        }
    }

    ret = temp.length();
    ret = ret > len ? len : ret;
    strncpy(buffer, temp.c_str(), ret);
    
__return:

    dbSerial.print("recvRetString[");
    dbSerial.print(temp.length());
    dbSerial.print(",");
    dbSerial.print(temp);
    dbSerial.println("]");

    return ret;
}

/* 0X71 0X66 0X00 0X00 0X00 0XFF 0XFF 0XFF */
bool NexTouch::recvRetNumber(uint32_t *number, uint32_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }
    
    nexSerial.setTimeout(timeout);
    if (sizeof(temp) != nexSerial.readBytes((char *)temp, sizeof(temp)))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = (temp[4] << 24) | (temp[3] << 16) | (temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret) 
    {
        dbSerial.print("recvRetNumber :");
        dbSerial.println(*number);
    }
    else
    {
        dbSerial.println("recvRetNumber err");
    }
    
    return ret;
}

bool NexTouch::setBrightness(uint32_t brightness)
{    
    char buf[10] = {0};
    String cmd;
    
    utoa(brightness, buf, 10);
    cmd += "dim=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexTouch::getBrightness(uint32_t *brightness)
{
    sendCommand("get dim");
    return recvRetNumber(brightness);
}

bool nexInit(void)
{
    nexSerial.begin(9600);
    NexTouch::sendCommand("");
    NexTouch::sendCommand("page 0");
    delay(100);
    return true;
}

bool nexLoop(NexTouch **nexListenList)
{
    NexTouch::mainEventLoop(nexListenList);
    return false;
}



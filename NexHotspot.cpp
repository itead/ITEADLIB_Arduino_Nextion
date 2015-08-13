/**
 * @file NexHotspot.cpp
 *
 * API of NexHotspot. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
 
#include "NexHotspot.h"

/**
 * Constructor,inherited NexTouch's constructor function.
 *
 */
NexHotspot::NexHotspot(NexPid pid, NexCid cid, const char *name)
    :NexTouch(pid, cid, name)
{
}


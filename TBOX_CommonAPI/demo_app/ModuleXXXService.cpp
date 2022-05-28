// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <thread>

#include "ModuleXXXServiceImpl.hpp"
#include "string.h"

void sayHello(char *name, char *returnMessage)
{
    memcpy((void *)returnMessage, (void *)name, strlen(name)+1);
    //printf("server:%s->%s\n", name, returnMessage);
}

void fun_array_test(uint8_t *name, uint8_t *returnMessage)
{
    memcpy((void *)returnMessage, (void *)name, 100);
    //printf("server:%s->%s\n", name, returnMessage);
}

void funxxx(int x, int *ret_y)
{
    *ret_y = x*x;
}

int main() 
{
    static int cnt = 0;
    module_xxx_register_server();
    module_xxx_sayHello_callback_register(sayHello);
    module_xxx_funxxx_callback_register(funxxx);
    module_xxx_fun_array_test_callback_register(fun_array_test);
    while (true) 
    {
        module_xxx_evtxxx_broadcast(cnt++);
        usleep(1000);
    }

    return 0;
}


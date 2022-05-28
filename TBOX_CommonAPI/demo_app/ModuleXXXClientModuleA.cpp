// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _WIN32
#include <unistd.h>
#endif

#include "ModuleXXXClientImpl.hpp"
#include "string.h"

int main() 
{
    module_xxx_register_client("ModuleXXX_Client_ModuleA");
    module_xxx_evtxxx_subscribe();
    while(1)
    {
        char req_msg[] = "module_xxx_sayHello_call ModuleA", ret_msg[50];
        static int x = 0, ret_y;
        uint8_t req_msg_array[] = "module_xxx_fun_array_test_call ModuleA", ret_msg_array[100];

        module_xxx_sayHello_call(req_msg, ret_msg);
        printf("clientA:%s->%s\n", req_msg, ret_msg);

        module_xxx_fun_array_test_call(req_msg_array, ret_msg_array);
        printf("clientA:%s->%s\n", req_msg_array, ret_msg_array);

        x += 2;
        module_xxx_funxxx_call(&x, &ret_y);
        printf("clientA:%d->%d\n", x, ret_y);

        module_xxx_funxxx_call_async(&x);
        usleep(1000);
    }
    return 0;
}


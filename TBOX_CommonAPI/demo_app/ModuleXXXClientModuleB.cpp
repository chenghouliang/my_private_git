// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _WIN32
#include <unistd.h>
#endif
#include "ModuleXXXClientImpl.hpp"
#include "string.h"

void module_xxx_method_val_test_call_async_callback(uint8_t *err_code, int32_t *out_val)
{
    if (*err_code != 0)
    {
        printf("method_val_test sync error: FAULT\n");
    }
    printf("clientB:module_xxx_method_val_test_call async %d\n",*out_val);
}

void module_xxx_evtxxx_subscribe_callback(int32_t *out_val)
{
    printf("clientB:Received broadcast:  %d\n",*out_val);
}

int main() 
{
    module_xxx_register_client("ModuleXXX_Client_ModuleB");
    module_xxx_method_val_test_call_async_regiester_callback(module_xxx_method_val_test_call_async_callback);
    module_xxx_evtxxx_subscribe(module_xxx_evtxxx_subscribe_callback);
    while(1)
    {
        static int in_val = 0, out_val;
        uint8_t in_array[] = "module_xxx_method_array_test_call ModuleB", out_array[100];

        module_xxx_method_array_test_call(in_array, out_array);
        printf("clientB:%s->%s\n", in_array, out_array);

        in_val += 2;
        module_xxx_method_val_test_call(&in_val, &out_val);
        printf("clientB:module_xxx_method_val_test_call sync %d->%d\n", in_val, out_val);

        module_xxx_method_val_test_call_async(&in_val);
        usleep(1000);
    }
    return 0;
}


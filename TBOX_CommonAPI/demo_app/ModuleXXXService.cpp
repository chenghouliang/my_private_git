// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <thread>

#include "ModuleXXXServiceImpl.hpp"
#include "string.h"

void method_array_test(uint8_t *name, uint8_t *returnMessage)
{
    memcpy((void *)returnMessage, (void *)name, 100);
}

void method_val_test(int *in_val, int *out_val)
{
    *out_val = (*in_val)*(*in_val);
}

int main() 
{
    static int cnt = 0;
    module_xxx_register_server();
    module_xxx_method_val_test_callback_register(method_val_test);
    module_xxx_method_array_test_callback_register(method_array_test);
    while (true) 
    {
        module_xxx_evtxxx_broadcast(cnt++);
        usleep(1000);
    }

    return 0;
}


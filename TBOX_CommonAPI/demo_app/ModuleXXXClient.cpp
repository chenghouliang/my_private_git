// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef _WIN32
#include <unistd.h>
#endif
#include <CommonAPI/CommonAPI.hpp>
#include "ModuleXXXClientImpl.hpp"
#include "string.h"

//using namespace v0::commonapi::examples;

int main() 
{
    module_xxx_register_client();
    module_xxx_evtxxx_subscribe();
    while(1)
    {
        char req_msg[50], ret_msg[50];
        int x1, ret_y1;
        char x2[50], ret_y2[50];

        module_xxx_sayHello_call(req_msg, ret_msg);
        module_xxx_funxxx_call(x1, x2, &ret_y1, ret_y2);
        module_xxx_funxxx_call_async();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}


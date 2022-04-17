// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <thread>

#include <CommonAPI/CommonAPI.hpp>
#include "ModuleXXXServiceImpl.hpp"
#include "string.h"

//using namespace std;

void sayHello(char *name, char *returnMessage)
{
    std::cout << "Hello, sayHello-->ChengHouliang" << std::endl;
}

void funxxx(int x1, char *x2, int *ret_y1, char *ret_y2)
{
    static int i = 0;
    *ret_y1 = i++;
    std::cout << "Hello, funxxx-->ChengHouliang" << std::endl;
    //strcpy(ret_y2, "Hello, funxxx-->ChengHouliang");
}

int main() 
{
    static int cnt = 0;
    module_xxx_register_server();
    module_xxx_sayHello_callback_register(sayHello);
    module_xxx_funxxx_callback_register(funxxx);
    while (true) 
    {
        module_xxx_evtxxx_broadcast(cnt++);
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}


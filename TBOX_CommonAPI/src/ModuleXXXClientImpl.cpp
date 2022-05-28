// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <iostream>
#include <string>
#include <cstring>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/examples/ModuleXXXProxy.hpp>

using namespace v0::commonapi::examples;

std::shared_ptr< CommonAPI::Runtime > runtime;
std::shared_ptr<ModuleXXXProxy<>> myProxy;

int module_xxx_register_client(char *client_name)
{
    CommonAPI::Runtime::setProperty("LogContext", "ModuleXXXC");
    CommonAPI::Runtime::setProperty("LogApplication", "ModuleXXXC");
    CommonAPI::Runtime::setProperty("LibraryBase", "ModuleXXX");

    runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ModuleXXX";
    std::string connection(client_name, 20);

    myProxy = runtime->buildProxy<ModuleXXXProxy>(domain,instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;
    return 0;
}

int module_xxx_sayHello_call(char *req_mag, char *ret_msg)
{
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    myProxy->sayHello(req_mag, callStatus, returnMessage, &info);
    if (callStatus != CommonAPI::CallStatus::SUCCESS) 
    {
        std::cout << "sayHello sync callStatus: NO_SUCCESS"<< std::endl;
        return -1;
    }
    info.timeout_ = info.timeout_ + 1000;
    strcpy(ret_msg, returnMessage.c_str());
    return 0;
}

int module_xxx_fun_array_test_call(uint8_t *req_mag, uint8_t *ret_msg)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::stdErrorTypeEnum_array methodError;
    std::vector< uint8_t> in_array(100), out_array(100);
    int i = 0;
    for (i = 0; i < 100; i++)
	{
		in_array[i] = req_mag[i];
	}
    // Synchronous call
    myProxy->fun_array_test(in_array, callStatus, methodError, out_array);
    for (i = 0; i < 100; i++)
	{
		ret_msg[i] = out_array[i];
	}

    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "fun_array_test sync callStatus: NO_SUCCESS"<< std::endl;
    }

    if (methodError != ModuleXXX::stdErrorTypeEnum_array::NO_FAULT)
    {
        std::cout << "fun_array_test sync error: MY_FAULT"<< std::endl;
    }

    return 0;
}

int module_xxx_funxxx_call(int *x, int *ret_y)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::stdErrorTypeEnum methodError;

    // Synchronous call
    myProxy->funxxx(*x, callStatus, methodError, *ret_y);

    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "funxxx sync callStatus: NO_SUCCESS"<< std::endl;
    }

    if (methodError != ModuleXXX::stdErrorTypeEnum::NO_FAULT)
    {
        std::cout << "funxxx sync error: MY_FAULT"<< std::endl;
    }

    return 0;
}

void funxxx_recv_cb(const CommonAPI::CallStatus& callStatus,
             const ModuleXXX::stdErrorTypeEnum& methodError,
             const int32_t& y) 
{
    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "funxxx sync callStatus: NO_SUCCESS"<< std::endl;
    }

    if (methodError != ModuleXXX::stdErrorTypeEnum::NO_FAULT)
    {
        std::cout << "funxxx sync error: MY_FAULT"<< std::endl;
    }
    std::cout << "funxxx async: y = " << y << std::endl;
}

int module_xxx_funxxx_call_async(int *x)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::stdErrorTypeEnum methodError;
    int32_t outY1;

    // Asynchronous call
    std::function<void(const CommonAPI::CallStatus&,
                        const ModuleXXX::stdErrorTypeEnum&,
                        const int32_t&)> fcb = funxxx_recv_cb;
    myProxy->funxxxAsync(*x, funxxx_recv_cb);
    return 0;
}

int module_xxx_evtxxx_subscribe(void)
{
    // Subscribe to broadcast
    myProxy->getMyStatusEvent().subscribe([&](const int32_t& val) {
        std::cout << "Client Received broadcast: " << val << std::endl;
    });
    return 0;
}

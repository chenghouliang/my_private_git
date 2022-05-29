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
#include "ModuleXXXClientImpl.hpp"
using namespace v0::commonapi::examples;

std::shared_ptr< CommonAPI::Runtime > runtime;
std::shared_ptr<ModuleXXXProxy<>> myProxy;

module_xxx_method_val_test_call_async_cb_f module_xxx_method_val_test_call_async_cb_handle = NULL;
module_xxx_evtxxx_subscribe_cb_f module_xxx_evtxxx_subscribe_cb_handle = NULL;
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

int module_xxx_method_array_test_call(uint8_t *in_array, uint8_t *out_array)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::ErrCode methodError;
    ModuleXXX::U8Array req_mag(100), ret_msg(100);
    int i = 0;
    for (i = 0; i < 100; i++)
	{
		req_mag[i] = in_array[i];
	}
    // Synchronous call
    myProxy->method_array_test(req_mag, callStatus, methodError, ret_msg);
    for (i = 0; i < 100; i++)
	{
		out_array[i] = ret_msg[i];
	}

    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "method_array_test sync callStatus: NO_SUCCESS"<< std::endl;
        return -1;
    }

    if (methodError != ModuleXXX::ErrCode::NO_FAULT)
    {
        std::cout << "method_array_test sync error: FAULT"<< std::endl;
        return -1;
    }

    return 0;
}

int module_xxx_method_val_test_call(int *in_val, int *out_val)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::ErrCode methodError;

    // Synchronous call
    myProxy->method_val_test(*in_val, callStatus, methodError, *out_val);

    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "method_val_test sync callStatus: NO_SUCCESS"<< std::endl;
        return -1;
    }

    if (methodError != ModuleXXX::ErrCode::NO_FAULT)
    {
        std::cout << "method_val_test sync error: FAULT"<< std::endl;
        return -1;
    }

    return 0;
}

int module_xxx_method_val_test_call_async_regiester_callback(module_xxx_method_val_test_call_async_cb_f cb)
{
    module_xxx_method_val_test_call_async_cb_handle = cb;
    return 0;
}

void method_val_test_recv_cb(const CommonAPI::CallStatus& callStatus,
             const ModuleXXX::ErrCode& methodError,
             const int32_t& out_val) 
{
    uint8_t method_error = (uint8_t)methodError;
    int32_t outVal = (uint32_t)out_val;

    if (callStatus != CommonAPI::CallStatus::SUCCESS)
    {
        std::cout << "method_val_test sync callStatus: NO_SUCCESS"<< std::endl;
    }

    if(module_xxx_method_val_test_call_async_cb_handle != NULL)
    {
        module_xxx_method_val_test_call_async_cb_handle(&method_error, &outVal);
    }
}

int module_xxx_method_val_test_call_async(int *in_val)
{
    CommonAPI::CallStatus callStatus;
    ModuleXXX::ErrCode methodError;

    // Asynchronous call
    std::function<void(const CommonAPI::CallStatus&,
                        const ModuleXXX::ErrCode&,
                        const int32_t&)> fcb = method_val_test_recv_cb;
    myProxy->method_val_testAsync(*in_val, fcb);
    return 0;
}

int module_xxx_evtxxx_subscribe(module_xxx_evtxxx_subscribe_cb_f cb)
{
    // Subscribe to broadcast
    module_xxx_evtxxx_subscribe_cb_handle = cb;
    myProxy->getBroadcastStatusEvent().subscribe([&](const int32_t& val) {
        if (module_xxx_evtxxx_subscribe_cb_handle != NULL)
        {
            int32_t u32_val = val;
            module_xxx_evtxxx_subscribe_cb_handle(&u32_val);
        }
    });
    return 0;
}

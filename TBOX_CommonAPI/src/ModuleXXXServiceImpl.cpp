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
#include "ModuleXXXServiceImpl.hpp"
#include <v0/commonapi/examples/ModuleXXXProxy.hpp>
#include <v0/commonapi/examples/ModuleXXXStubDefault.hpp>

using namespace v0_1::commonapi::examples;

module_xxx_method_val_test_cb_f module_xxx_method_val_test_handle = NULL;
module_xxx_method_array_test_cb_f module_xxx_method_array_test_handle = NULL;

class ModuleXXXStubImpl: public v0_1::commonapi::examples::ModuleXXXStubDefault 
{
    public:
        ModuleXXXStubImpl();
        virtual ~ModuleXXXStubImpl();

        virtual void method_val_test(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _in_val, method_val_testReply_t _reply);
        virtual void method_array_test(const std::shared_ptr<CommonAPI::ClientId> _client, ModuleXXX::U8Array _in_array, method_array_testReply_t _reply);
};

ModuleXXXStubImpl::ModuleXXXStubImpl() {
}

ModuleXXXStubImpl::~ModuleXXXStubImpl() {
}

void ModuleXXXStubImpl::method_val_test(const std::shared_ptr<CommonAPI::ClientId> _client, 
                int32_t _in_val, method_val_testReply_t _reply)
{
    ModuleXXX::ErrCode methodError = ModuleXXX::ErrCode::FAULT;
    int32_t ret_y = 0;

    if (module_xxx_method_val_test_handle != NULL)
    {
        module_xxx_method_val_test_handle(&_in_val, &ret_y);
        methodError = ModuleXXX::ErrCode::NO_FAULT;
    }
    else
    {
        std::cout << "method_val_test call failed" <<"'\n";
    }

    _reply(methodError, ret_y);
}

void ModuleXXXStubImpl::method_array_test(const std::shared_ptr<CommonAPI::ClientId> _client,
                ModuleXXX::U8Array _in_array, method_array_testReply_t _reply) 
{
    ModuleXXX::ErrCode methodError = ModuleXXX::ErrCode::FAULT;
    ModuleXXX::U8Array ret_y(100);
    uint8_t in_array[100], out_array[100];
    int i = 0;
    if (module_xxx_method_array_test_handle != NULL)
    {
        for(i = 0; i < 100; i++)
        {
            in_array[i] = _in_array[i];
        }

        module_xxx_method_array_test_handle(in_array, out_array);
        methodError = ModuleXXX::ErrCode::NO_FAULT;

        for(i = 0; i < 100; i++)
        {
            ret_y[i] = out_array[i];
        }
    }
    else
    {
        std::cout << "method_array_test call failed" <<"'\n";
    }

    _reply(methodError, ret_y);
}

std::shared_ptr<CommonAPI::Runtime> runtime;
std::shared_ptr<ModuleXXXStubImpl> myService;

int module_xxx_register_server(void)
{
    CommonAPI::Runtime::setProperty("LogContext", "ModuleXXXS");
    CommonAPI::Runtime::setProperty("LogApplication", "ModuleXXXS");
    CommonAPI::Runtime::setProperty("LibraryBase", "ModuleXXX");

    runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ModuleXXX";
    std::string connection = "ModuleXXX_Service";

    myService = std::make_shared<ModuleXXXStubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService, connection);

    while (!successfullyRegistered) 
    {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService, connection);
    }

    std::cout << "Successfully Registered Service!" << std::endl;
    return 0;
}

int module_xxx_method_array_test_callback_register(module_xxx_method_array_test_cb_f method_array_test_funptr)
{
    module_xxx_method_array_test_handle = method_array_test_funptr;
    return 0;
}

int module_xxx_method_val_test_callback_register(module_xxx_method_val_test_cb_f method_val_test_funptr)
{
    module_xxx_method_val_test_handle = method_val_test_funptr;
    return 0;
}

int module_xxx_evtxxx_broadcast(int cnt)
{
    myService->fireBroadcastStatusEvent((int32_t) cnt);
    return 0;
}
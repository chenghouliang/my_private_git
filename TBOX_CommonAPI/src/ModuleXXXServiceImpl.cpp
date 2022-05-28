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

module_xxx_sayHello_cb_f module_xxx_sayHello_handle = NULL;
module_xxx_funxxx_cb_f module_xxx_funxxx_handle = NULL;
module_xxx_fun_array_test_cb_f module_xxx_fun_array_test_handle = NULL;

class ModuleXXXStubImpl: public v0_1::commonapi::examples::ModuleXXXStubDefault 
{
    public:
        ModuleXXXStubImpl();
        virtual ~ModuleXXXStubImpl();

        virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _reply);
        virtual void funxxx(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _x, funxxxReply_t _reply);
        virtual void fun_array_test(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t> _x, fun_array_testReply_t _reply);

};

ModuleXXXStubImpl::ModuleXXXStubImpl() {
}

ModuleXXXStubImpl::~ModuleXXXStubImpl() {
}

void ModuleXXXStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) 
{
    std::stringstream messageStream;

    if (module_xxx_sayHello_handle != NULL)
    {
        char returnMessage[20];
        char name[100];
        strcpy(name, _name.c_str());
        module_xxx_sayHello_handle(name, returnMessage);
        messageStream << returnMessage;
    }
    else
    {
        std::cout << "sayHello call faile" <<"'\n";
    }
    _reply(messageStream.str());
}

void ModuleXXXStubImpl::fun_array_test(const std::shared_ptr<CommonAPI::ClientId> _client,
                std::vector< uint8_t> _x, fun_array_testReply_t _reply) 
{
    ModuleXXX::stdErrorTypeEnum_array methodError = ModuleXXX::stdErrorTypeEnum_array::MY_FAULT;
    std::vector< uint8_t> ret_y(100);
    uint8_t in_array[100], out_array[100];
    int i = 0;
    if (module_xxx_fun_array_test_handle != NULL)
    {
        for(i = 0; i < 100; i++)
        {
            in_array[i] = _x[i];
        }

        module_xxx_fun_array_test_handle(in_array, out_array);
        methodError = ModuleXXX::stdErrorTypeEnum_array::NO_FAULT;

        for(i = 0; i < 100; i++)
        {
            ret_y[i] = out_array[i];
        }
    }
    else
    {
        std::cout << "fun_array_test call failed" <<"'\n";
    }

    _reply(methodError, ret_y);
}

void ModuleXXXStubImpl::funxxx(const std::shared_ptr<CommonAPI::ClientId> _client,
                int32_t _x, funxxxReply_t _reply) 
{
    ModuleXXX::stdErrorTypeEnum methodError = ModuleXXX::stdErrorTypeEnum::MY_FAULT;
    int32_t ret_y = 0;

    if (module_xxx_funxxx_handle != NULL)
    {
        module_xxx_funxxx_handle(_x, &ret_y);
        methodError = ModuleXXX::stdErrorTypeEnum::NO_FAULT;
    }
    else
    {
        std::cout << "funxxx call failed" <<"'\n";
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

int module_xxx_sayHello_callback_register(module_xxx_sayHello_cb_f sayHello_fun_ptr)
{
    module_xxx_sayHello_handle = sayHello_fun_ptr;
    return 0;
}

int module_xxx_fun_array_test_callback_register(module_xxx_fun_array_test_cb_f fun_array_test_funptr)
{
    module_xxx_fun_array_test_handle = fun_array_test_funptr;
    return 0;
}

int module_xxx_funxxx_callback_register(module_xxx_funxxx_cb_f funxxx_funptr)
{
    module_xxx_funxxx_handle = funxxx_funptr;
    return 0;
}

int module_xxx_evtxxx_broadcast(int cnt)
{
    myService->fireMyStatusEvent((int32_t) cnt);
    //std::cout << "Server send broadcast = " << cnt << std::endl;
    return 0;
}
// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <iostream>
#include <string>

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

class ModuleXXXStubImpl: public v0_1::commonapi::examples::ModuleXXXStubDefault 
{
    public:
        ModuleXXXStubImpl();
        virtual ~ModuleXXXStubImpl();

        virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);
        virtual void foo(const std::shared_ptr<CommonAPI::ClientId> _client,
                int32_t _x1, std::string _x2,
                fooReply_t _reply);
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
        char name[20],returnMessage[20];
        //strcpy(name, _name.c_str);
        //strlen(y2, ret_y2, strlen(ret_y2));
        module_xxx_sayHello_handle(name, returnMessage);
        //messageStream << "Hello " << returnMessage << "!";
        messageStream << "Hello ok"<< "!";
    }
    else
    {
        messageStream << "Hello error" << _name << "!";
        std::cout << "sayHello error '" <<"'\n";
    }
    _reply(messageStream.str());
};

void ModuleXXXStubImpl::foo(const std::shared_ptr<CommonAPI::ClientId> _client,
                int32_t _x1, std::string _x2,
                fooReply_t _reply) 
{

    std::cout << "foo called, setting new values." << std::endl;

    ModuleXXX::stdErrorTypeEnum methodError = ModuleXXX::stdErrorTypeEnum::MY_FAULT;
    int32_t y1 = 42;
    std::string y2 = "xyz";

    if (module_xxx_funxxx_handle != NULL)
    {
        int x1, ret_y1;
        char x2[20], ret_y2[20];
        module_xxx_funxxx_handle(x1, x2, &ret_y1, ret_y2);
        y1 = ret_y1;
        //y2 <<ret_y2<< "!";
        //memcpy(y2, ret_y2, strlen(ret_y2));
    }
    else
    {

    }

    _reply(methodError, y1, y2);
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
    std::string connection = "service-sample";

    myService = std::make_shared<ModuleXXXStubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService, connection);

    while (!successfullyRegistered) {
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

int module_xxx_funxxx_callback_register(module_xxx_funxxx_cb_f funxxx_funptr)
{
    module_xxx_funxxx_handle = funxxx_funptr;
    return 0;
}

int module_xxx_evtxxx_broadcast(int cnt)
{
    myService->fireMyStatusEvent((int32_t) cnt);
    std::cout << "New counter value = " << cnt << "!" << std::endl;

    return 0;
}
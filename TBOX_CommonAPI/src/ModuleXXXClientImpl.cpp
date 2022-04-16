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
#include <v0/commonapi/examples/ModuleXXXProxy.hpp>

using namespace v0::commonapi::examples;

std::shared_ptr< CommonAPI::Runtime > runtime;
std::shared_ptr<ModuleXXXProxy<>> myProxy;

void recv_cb(const CommonAPI::CallStatus& callStatus,
             const ModuleXXX::stdErrorTypeEnum& methodError,
             const int32_t& y1,
             const std::string& y2) 
{
    std::cout << "Result of asynchronous call of foo: " << std::endl;
    std::cout << "   callStatus: " << ((callStatus == CommonAPI::CallStatus::SUCCESS) ? "SUCCESS" : "NO_SUCCESS")
                    << std::endl;
    std::cout << "   error: "
                    << ((methodError == ModuleXXX::stdErrorTypeEnum::NO_FAULT) ? "NO_FAULT" :
                                    "MY_FAULT") << std::endl;
    std::cout << "   Output values: y1 = " << y1 << ", y2 = " << y2 << std::endl;
}

int module_xxx_register_client(void)
{
    CommonAPI::Runtime::setProperty("LogContext", "ModuleXXXC");
    CommonAPI::Runtime::setProperty("LogApplication", "ModuleXXXC");
    CommonAPI::Runtime::setProperty("LibraryBase", "ModuleXXX");

    runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ModuleXXX";
    std::string connection = "client-sample";

    myProxy = runtime->buildProxy<ModuleXXXProxy>(domain,instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;
    return 0;

}

int module_xxx_sayHello_call(char *req_mag, char *ret_msg)
{
    const std::string name = "World";
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    myProxy->sayHello(name, callStatus, returnMessage, &info);
    if (callStatus != CommonAPI::CallStatus::SUCCESS) {
        std::cerr << "Remote call failed!\n";
        return -1;
    }
    info.timeout_ = info.timeout_ + 1000;

    std::cout << "Got message: '" << returnMessage << "'\n";
    return 0;

}

int module_xxx_funxxx_call(int x1, char *x2, int *ret_y1, char *ret_y2)
{
    int32_t inX1 = 5;
    std::string inX2 = "abc";
    CommonAPI::CallStatus callStatus;
    ModuleXXX::stdErrorTypeEnum methodError;
    int32_t outY1;
    std::string outY2;

    // Synchronous call
    std::cout << "Call foo with synchronous semantics ..." << std::endl;
    myProxy->foo(inX1, inX2, callStatus, methodError, outY1, outY2);

    std::cout << "Result of synchronous call of foo: " << std::endl;
    std::cout << "   callStatus: " << ((callStatus == CommonAPI::CallStatus::SUCCESS) ? "SUCCESS" : "NO_SUCCESS")
                << std::endl;
    std::cout << "   error: "
                << ((methodError == ModuleXXX::stdErrorTypeEnum::NO_FAULT) ? "NO_FAULT" : "MY_FAULT")
                << std::endl;
    std::cout << "   Input values: x1 = " << inX1 << ", x2 = " << inX2 << std::endl;
    std::cout << "   Output values: y1 = " << outY1 << ", y2 = " << outY2 << std::endl;
    return 0;
}

int module_xxx_funxxx_call_async(void)
{
    int32_t inX1 = 5;
    std::string inX2 = "abc";
    CommonAPI::CallStatus callStatus;
    ModuleXXX::stdErrorTypeEnum methodError;
    int32_t outY1;
    std::string outY2;

    // Asynchronous call
    std::function<void(const CommonAPI::CallStatus&,
                        const ModuleXXX::stdErrorTypeEnum&,
                        const int32_t&,
                        const std::string&)> fcb = recv_cb;
    std::cout << "Call foo with asynchronous semantics ..." << std::endl;
    myProxy->fooAsync(inX1, inX2, recv_cb);
    return 0;
}

int module_xxx_evtxxx_subscribe(void)
{
    // Subscribe to broadcast
    myProxy->getMyStatusEvent().subscribe([&](const int32_t& val) {
        std::cout << "Received status event: " << val << std::endl;
    });
    return 0;
}

// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_CLIENTIMPL_HPP_
#define ModuleXXX_CLIENTIMPL_HPP_

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

#ifndef _WIN32
#include <unistd.h>
#endif

//#include <CommonAPI/CommonAPI.hpp>
//#include <v0/commonapi/examples/ModuleXXXProxy.hpp>

extern int module_xxx_register_client(char *client_name);
extern int module_xxx_sayHello_call(char *req_msg, char *ret_msg);
extern int module_xxx_funxxx_call(int *x, int *ret_y);
extern int module_xxx_fun_array_test_call(uint8_t *req_msg, uint8_t *ret_msg);
extern int module_xxx_funxxx_call_async(int *x);
extern int module_xxx_evtxxx_subscribe(void);

#endif // ModuleXXX_CLIENTIMPL_HPP_






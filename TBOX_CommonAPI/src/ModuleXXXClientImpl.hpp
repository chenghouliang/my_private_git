// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_CLIENTIMPL_HPP_
#define ModuleXXX_CLIENTIMPL_HPP_

#include <iostream>
#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

//#include <CommonAPI/CommonAPI.hpp>
//#include <v0/commonapi/examples/ModuleXXXProxy.hpp>

extern int module_xxx_register_client(void);
extern int module_xxx_sayHello_call(char *req_msg, char *ret_msg);
extern int module_xxx_funxxx_call(int x1, char *x2, int *ret_y1, char *ret_y2);
extern int module_xxx_funxxx_call_async(void);
extern int module_xxx_evtxxx_subscribe(void);

#endif // ModuleXXX_CLIENTIMPL_HPP_






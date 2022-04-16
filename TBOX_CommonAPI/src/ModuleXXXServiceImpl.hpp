// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_SERVICEIMPL_HPP_
#define ModuleXXX_SERVICEIMPL_HPP_

#include <iostream>
#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

//#include <CommonAPI/CommonAPI.hpp>
//#include <v0/commonapi/examples/ModuleXXXStubDefault.hpp>

typedef void (*module_xxx_sayHello_cb_f)(char *name, char *returnMessage);
typedef void (*module_xxx_funxxx_cb_f)(int x1, char *x2, int *ret_y1, char *ret_y2);
extern int module_xxx_register_server(void);
extern int module_xxx_sayHello_callback_register(module_xxx_sayHello_cb_f sayHello_fun_ptr);
extern int module_xxx_funxxx_callback_register(module_xxx_funxxx_cb_f funxxx_funptr);
extern int module_xxx_evtxxx_broadcast(int cnt);

#endif // ModuleXXX_SERVICEIMPL_HPP_

// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_SERVICEIMPL_HPP_
#define ModuleXXX_SERVICEIMPL_HPP_

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>

#ifndef _WIN32
#include <unistd.h>
#endif

typedef void (*module_xxx_sayHello_cb_f)(char *name, char *returnMessage);
typedef void (*module_xxx_funxxx_cb_f)(int x, int *ret_y);
typedef void (*module_xxx_fun_array_test_cb_f)(uint8_t *x, uint8_t *ret_y);
extern int module_xxx_register_server(void);
extern int module_xxx_sayHello_callback_register(module_xxx_sayHello_cb_f sayHello_fun_ptr);
extern int module_xxx_funxxx_callback_register(module_xxx_funxxx_cb_f funxxx_funptr);
extern int module_xxx_fun_array_test_callback_register(module_xxx_fun_array_test_cb_f fun_array_test_funptr);
extern int module_xxx_evtxxx_broadcast(int cnt);

#endif // ModuleXXX_SERVICEIMPL_HPP_

// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_SERVICEIMPL_HPP_
#define ModuleXXX_SERVICEIMPL_HPP_

#include <iostream>
#include <string>
#include <cstdint>

#ifndef _WIN32
#include <unistd.h>
#endif

typedef void (*module_xxx_method_val_test_cb_f)(int *in_val, int *out_val);
typedef void (*module_xxx_method_array_test_cb_f)(uint8_t *in_array, uint8_t *out_array);
extern int module_xxx_register_server(void);
extern int module_xxx_method_val_test_callback_register(module_xxx_method_val_test_cb_f method_val_test_funptr);
extern int module_xxx_method_array_test_callback_register(module_xxx_method_array_test_cb_f method_array_test_funptr);
extern int module_xxx_evtxxx_broadcast(int cnt);

#endif // ModuleXXX_SERVICEIMPL_HPP_

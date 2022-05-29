// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ModuleXXX_CLIENTIMPL_HPP_
#define ModuleXXX_CLIENTIMPL_HPP_

#include <iostream>
#include <string>
#include <cstdint>

#ifndef _WIN32
#include <unistd.h>
#endif

typedef void (*module_xxx_method_val_test_call_async_cb_f)(uint8_t *err_code, int32_t *out_val);
typedef void (*module_xxx_evtxxx_subscribe_cb_f)(int32_t *out_val);
extern int module_xxx_register_client(char *client_name);
extern int module_xxx_method_val_test_call(int *in_val, int *out_val);
extern int module_xxx_method_val_test_call_async_regiester_callback(module_xxx_method_val_test_call_async_cb_f cb);
extern int module_xxx_method_val_test_call_async(int *in_val);
extern int module_xxx_method_array_test_call(uint8_t *in_array, uint8_t *out_array);
extern int module_xxx_evtxxx_subscribe(module_xxx_evtxxx_subscribe_cb_f cb);

#endif // ModuleXXX_CLIENTIMPL_HPP_






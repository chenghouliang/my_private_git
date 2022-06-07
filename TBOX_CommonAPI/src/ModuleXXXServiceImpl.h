#ifndef ModuleXXX_SERVICEIMPL_HPP_
#define ModuleXXX_SERVICEIMPL_HPP_

#include <inttypes.h>

typedef void (*module_xxx_method_val_test_cb_f)(int *in_val, int *out_val);
typedef void (*module_xxx_method_array_test_cb_f)(uint8_t *in_array, uint8_t *out_array);
extern int module_xxx_register_server(void);
extern int module_xxx_method_val_test_callback_register(module_xxx_method_val_test_cb_f method_val_test_funptr);
extern int module_xxx_method_array_test_callback_register(module_xxx_method_array_test_cb_f method_array_test_funptr);
extern int module_xxx_evtxxx_broadcast(int cnt);

#endif // ModuleXXX_SERVICEIMPL_HPP_

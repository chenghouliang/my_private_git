#include <string.h>
#include <unistd.h>
#include "ModuleXXXServiceImpl.h"

void method_array_test(uint8_t *name, uint8_t *returnMessage)
{
    memcpy((void *)returnMessage, (void *)name, 100);
}

void method_val_test(int *in_val, int *out_val)
{
    *out_val = (*in_val)*(*in_val);
}

int main() 
{
    static int cnt = 0;
    module_xxx_register_server("ModuleXXX_Service");
    module_xxx_method_val_test_callback_register(method_val_test);
    module_xxx_method_array_test_callback_register(method_array_test);
    while (1) 
    {
        module_xxx_evtxxx_broadcast(cnt++);
        usleep(1000);
    }

    return 0;
}


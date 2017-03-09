#ifndef NATIVE_DT_USER_H
#define NATIVE_DT_USER_H

#include <cstddef>
#include <cstdint>

typedef struct _MyNotifyDT
{
    size_t size;
    // input data
    uint16_t u16_data1;
    uint32_t u32_data2;
    // output data
    char c_str_data3[32];
    uint32_t u32_data4;
} MyNotifyDT;

#endif /* NATIVE_DT_USER_H */


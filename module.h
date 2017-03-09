#ifndef MODULE_H
#define MODULE_H

#include "util.h"

#include "pybind11/pybind11.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_rts
    extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initrts
    extern "C" void INIT_MODULE();
#endif

typedef struct _NotifyDT
{
    size_t size;
    uint8_t user[1];
} NotifyDT;

class NotifyDTWrapper final
{
public:
    NotifyDTWrapper(NotifyDT* d) :
        data(d) { }
    void setData(py::bytes const& d)
        {
            ::memcpy(data, PyBytes_AsString(d.ptr()), PyBytes_Size(d.ptr()));
        }
    py::bytes getData() const
        {
            return py::bytes(
                reinterpret_cast<char const*>(data),
                data->size
            );
        }

private:
    NotifyDT* data;
};

#endif /* MODULE_H */

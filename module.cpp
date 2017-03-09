#include "module.h"
#include "util.h"
#include "native_dt.h"

#include <iostream>

PYBIND11_PLUGIN(rts)
{
    py::module m("rts", "pybind11 example plugin");

    py::class_<Scheduler>(m, "Scheduler")
        .def_readonly("tasks", &Scheduler::tasks)
        .def_readonly("accuracy", &Scheduler::accuracy)
        .def("getTasks", &Scheduler::getTasks)
        .def("getConfig", &Scheduler::getConfig)
        .def("setMember", &Scheduler::setMember)
        ;

    py::class_<RTSConfig>(m, "RTSConfig")
        .def("someMethod", &RTSConfig::someMethod)
        ;

    py::class_<NotifyDTWrapper>(m, "NotifyDTWrapper")
        .def_property("data", &NotifyDTWrapper::getData, &NotifyDTWrapper::setData)
        ;

    return m.ptr();
}

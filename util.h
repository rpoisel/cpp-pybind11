#ifndef UTIL_H
#define UTIL_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

py::object import_helper(const std::string& module, const std::string& path, py::object& globals);

#endif /* UTIL_H */

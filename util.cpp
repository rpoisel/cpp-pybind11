#include "util.h"

#include <pybind11/eval.h>

py::object import_helper(const std::string& module, const std::string& path, py::object& globals)
{
    py::dict locals;
    locals["module_name"] = py::cast(module);
    locals["path"]        = py::cast(path);

    py::eval<py::eval_statements>(
        "import imp\n"
        "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
        globals,
        locals);

    return locals["new_module"];
}


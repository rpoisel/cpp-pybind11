#include "util.h"
#include "module.h"
#include "native_dt.h"
#include "native_dt_user.h"

#include <cstring>

#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Invalid command-line arguments." << std::endl;
    return 1;
  }

  PyImport_AppendInittab("rts", &PyInit_rts);
  Py_Initialize();

  try
  {
    py::object main = py::module::import("__main__");
    py::object globals = main.attr("__dict__");

    py::object module = import_helper("rtss", argv[1], globals);
    py::object rt_dll_initterm = module.attr("rt_dll_initterm");
    py::object notifyFunc = rt_dll_initterm();

    MyNotifyDT notifyData;
    NotifyDT* abstractNotifyData = reinterpret_cast<NotifyDT*>(&notifyData);

    memset(&notifyData, 0, sizeof(notifyData));
    notifyData.size = sizeof(notifyData);
    notifyData.u16_data1 = 0x1234;
    notifyData.u32_data2 = 0xdeadbeef;
    strcpy(notifyData.c_str_data3, "There we go.");
    notifyData.u32_data4 = 0xaffeaffe;

    std::cout << "Sizeof notifyData: "
        << sizeof(notifyData)
        << " and size_t: "
        << sizeof(size_t)
        << std::endl;
    std::cout << "size in abstractNotifyData: "
        << abstractNotifyData->size << std::endl;
    std::cout << "abstractNotifyData + sizeof(size_t) as uint16_t: 0x"
        << std::hex << *reinterpret_cast<uint16_t*>(abstractNotifyData->user)
        << std::endl;

    Scheduler sched(3, 5.5);
    std::cout << std::dec << sched.getMember() << std::endl;

    NotifyDTWrapper wrapper(abstractNotifyData);
    notifyFunc(&sched, 2, 3, &wrapper);

    std::cout << "Notification data member: " << notifyData.c_str_data3 << std::endl;
    std::cout << "Notification data member: 0x" << std::hex << notifyData.u32_data4 << std::endl;
    std::cout << "Scheduler member: " << std::dec << sched.getMember() << std::endl;

    return 0;
  }
  catch (py::error_already_set& exc)
  {
    std::cerr << ">>> Error! Uncaught exception:" << exc.what() << std::endl;
    return 1;
  }
}

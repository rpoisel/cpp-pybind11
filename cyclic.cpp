#include "util.h"
#include "module.h"
#include "native_dt.h"
#include "native_dt_user.h"

#include <unity.h>

#include <cstring>
#include <iostream>

#define CYCLIC_RUNS                          10000

static int s_argc = 0;
static char** s_argv = NULL;
static py::object notifyFunc = py::none();

void setUp(void)
{
  PyImport_AppendInittab("rts", &PyInit_rts);
  Py_Initialize();

  try
  {
    py::object main = py::module::import("__main__");
    py::object globals = main.attr("__dict__");

    py::object module = import_helper("rtss", s_argv[1], globals);
    py::object rt_dll_initterm = module.attr("rt_dll_initterm");
    notifyFunc = rt_dll_initterm();
  }
  catch (py::error_already_set& exc)
  {
    TEST_FAIL_MESSAGE(exc.what());
  }
}

void tearDown(void)
{
}

static void invoke_script_periodically(void)
{
  MyNotifyDT notifyData;
  NotifyDT* abstractNotifyData = reinterpret_cast<NotifyDT*>(&notifyData);

  memset(&notifyData, 0, sizeof(notifyData));
  notifyData.size = sizeof(notifyData);

  Scheduler sched(3, 5.5);
  NotifyDTWrapper wrapper(abstractNotifyData);
  for (uint32_t cnt = 0; cnt < CYCLIC_RUNS; cnt++)
  {
    notifyData.u16_data1 = cnt + 1;
    notifyData.u32_data2 = cnt + 2;
    strcpy(notifyData.c_str_data3, "There we go.");
    notifyData.u32_data4 = 0xaffeaffe;

    notifyFunc(&sched, 0xbeefbeef, 0xabcdabcd, &wrapper);

    TEST_ASSERT_EQUAL_STRING_MESSAGE("Hello, World!", notifyData.c_str_data3,
        "C-String from Python code is incorrect"
        );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(notifyData.u16_data1 + notifyData.u32_data2, notifyData.u32_data4,
        "32-bit unsigned from Python code is incorrect"
        );
    TEST_ASSERT_EQUAL_INT_MESSAGE(23 + cnt, sched.getMember(), "Scheduler member is incorrect");
  }
}

int main(int argc, char* argv[])
{
  s_argc = argc;
  s_argv = argv;

  if (argc < 2)
  {
    std::cout << "Incorrect command-line parameters." << std::endl;
    return 1;
  }

  UNITY_BEGIN();

  RUN_TEST(invoke_script_periodically);

  return UNITY_END();
}

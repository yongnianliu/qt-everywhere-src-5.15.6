
cmake_minimum_required(VERSION 2.8)

project(qmake_cmake_files)

enable_testing()

find_package(Qt5Core REQUIRED)

include("${_Qt5CTestMacros}")

set(qt_module_includes
    Script QScriptEngine
)

if (NOT NO_WIDGETS)
    list(APPEND qt_module_includes
        ScriptTools QScriptEngineDebugger
    )
endif()

test_module_includes(
    ${qt_module_includes}
)

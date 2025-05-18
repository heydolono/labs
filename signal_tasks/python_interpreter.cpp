#include "python_interpreter.h"
#include <iostream>

PythonInterpreter::PythonInterpreter() {
    Py_Initialize();
}

PythonInterpreter::~PythonInterpreter() {
    Py_Finalize();
}

PyObject* PythonInterpreter::module(const std::string& name) {
    if (modules.find(name) != modules.end()) {
        return modules[name];
    }

    PyObject* mod = PyImport_ImportModule(name.c_str());
    if (!mod) {
        PyErr_Print();
        throw std::runtime_error("Failed to import Python module: " + name);
    }
    modules[name] = mod;
    return mod;
}

PyObject* PythonInterpreter::function(PyObject* module, const std::string& func) {
    PyObject* fn = PyObject_GetAttrString(module, func.c_str());
    if (!fn || !PyCallable_Check(fn)) {
        PyErr_Print();
        throw std::runtime_error("Function not found or not callable: " + func);
    }
    return fn;
}
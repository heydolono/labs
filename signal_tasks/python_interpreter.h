#pragma once

#include <Python.h>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

class PythonInterpreter {
public:
    static PythonInterpreter& get() {
        static PythonInterpreter instance;
        return instance;
    }

    PyObject* module(const std::string& name);
    PyObject* function(PyObject* module, const std::string& func);

private:
    PythonInterpreter();
    ~PythonInterpreter();

    std::map<std::string, PyObject*> modules;
};
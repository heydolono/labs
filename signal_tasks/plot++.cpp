#include "plot++.h"
#include "python_interpreter.h"
#include <numpy/arrayobject.h>
#include <stdexcept>

void PlotPlusPlus::plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyArray_FromVector(x));
    PyTuple_SetItem(args, 1, PyArray_FromVector(y));
    PyTuple_SetItem(args, 2, PyUnicode_FromString(fmt.c_str()));

    PyObject* fn = py.function(plt, "plot");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::xlabel(const std::string& label) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(label.c_str()));

    PyObject* fn = py.function(plt, "xlabel");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::ylabel(const std::string& label) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(label.c_str()));

    PyObject* fn = py.function(plt, "ylabel");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::title(const std::string& title) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(title.c_str()));

    PyObject* fn = py.function(plt, "title");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::show() {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* fn = py.function(plt, "show");
    PyObject_CallObject(fn, nullptr);

    Py_DECREF(fn);
}

void PlotPlusPlus::grid(bool enable) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, enable ? Py_True : Py_False);

    PyObject* fn = py.function(plt, "grid");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::savefig(const std::string& filename) {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(filename.c_str()));

    PyObject* fn = py.function(plt, "savefig");
    PyObject_CallObject(fn, args);

    Py_DECREF(args);
    Py_DECREF(fn);
}

void PlotPlusPlus::close() {
    auto& py = PythonInterpreter::get();
    PyObject* plt = py.module("matplotlib.pyplot");

    PyObject* fn = py.function(plt, "close");
    PyObject_CallObject(fn, nullptr);

    Py_DECREF(fn);
}
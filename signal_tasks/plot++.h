#pragma once

#include <vector>
#include <string>
#include <map>
#include <Python.h>

class PlotPlusPlus {
public:
    static void plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& fmt = "");
    static void xlabel(const std::string& label);
    static void ylabel(const std::string& label);
    static void title(const std::string& title);
    static void show();
    static void grid(bool enable = true);
    static void savefig(const std::string& filename);
    static void close();
};
#include "plot++.h"
#include <vector>

int main() {
    // Инициализация NumPy
    import_array();

    std::vector<double> x(100), y(100);
    for (int i = 0; i < 100; ++i) {
        x[i] = i * 0.1;
        y[i] = sin(x[i]);
    }

    PlotPlusPlus::plot(x, y, "r-o");
    PlotPlusPlus::xlabel("X axis");
    PlotPlusPlus::ylabel("Y axis");
    PlotPlusPlus::title("Sine Wave");
    PlotPlusPlus::grid(true);
    PlotPlusPlus::savefig("output.png");
    PlotPlusPlus::show();
    PlotPlusPlus::close();

    return 0;
}
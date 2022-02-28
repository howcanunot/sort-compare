#include "metrics/metrics.h"

int main() {
    try {
        Metrics metric;
        metric.start();
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}

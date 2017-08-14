#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "mbed.h"
#pragma GCC diagnostic pop

// DigitalIn  s(p9);
DigitalOut l1(p10);
DigitalOut l2(p11);
DigitalOut l3(p12);

int main() {
    int k = 0;
    while (true) {
        k++;
        l1 = (k    ) % 3 == 0;
        l2 = (k + 1) % 3 == 0;
        l3 = (k + 2) % 3 == 0;
        wait(0.300);
    }
    error("WTF!?");
    return 0;
}

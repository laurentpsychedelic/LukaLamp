#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "mbed.h"
#pragma GCC diagnostic pop

DigitalIn  s (dp13);
DigitalOut l1(dp9 );
DigitalOut l2(dp10);
DigitalOut l3(dp11);

struct Pattern {
    float duration; // s
    bool* pattern;
};
struct Loop {
    int len;
    Pattern* patterns;
};
struct Loops {
    int len;
    Loop* loops;
};

// 000/111
bool _pattern1_1[3] = { true , true , true  };
bool _pattern1_2[3] = { false, false, false };
Pattern pattern1_1 = { 0.1f, _pattern1_1 };
Pattern pattern1_2 = { 0.1f, _pattern1_2 };
Pattern patterns1[2] = { pattern1_1, pattern1_2 };
Loop loop1 = { 2, patterns1 };
// 100*
bool _pattern2_1[3] = { true , false, false };
bool _pattern2_2[3] = { false, true , false };
bool _pattern2_3[3] = { false, false, true  };
Pattern pattern2_1 = { 0.1f, _pattern2_1 };
Pattern pattern2_2 = { 0.1f, _pattern2_2 };
Pattern pattern2_3 = { 0.1f, _pattern2_3 };
Pattern patterns2[3] = { pattern2_1, pattern2_2, pattern2_3 };
Loop loop2 = { 3, patterns2 };
// 110*
bool _pattern3_1[3] = { true , false, true  };
bool _pattern3_2[3] = { false, true , true  };
bool _pattern3_3[3] = { true , true , false };
Pattern pattern3_1 = { 0.1f, _pattern3_1 };
Pattern pattern3_2 = { 0.1f, _pattern3_2 };
Pattern pattern3_3 = { 0.1f, _pattern3_3 };
Pattern patterns3[3] = { pattern3_1, pattern3_2, pattern3_3 };
Loop loop3 = { 3, patterns3 };

Loop _loops[3] = { loop1, loop2, loop3 };
Loops loops = { 3, _loops };

int duration_factors[3] = { 1, 4, 8 };

int main() {
    int loop_counter = 0;
    int pattern_counter = 0;
    bool _switch = s;
    int duration_factor_index = 0;
    while (true) {
        const Loop loop = loops.loops[loop_counter];
        const Pattern pattern = loop.patterns[pattern_counter];

        l1 = pattern.pattern[0];
        l2 = pattern.pattern[1];
        l3 = pattern.pattern[2];

        wait(pattern.duration * duration_factors[duration_factor_index]);

        pattern_counter++;
        if (pattern_counter >= loop.len)
            pattern_counter = 0;

        const bool _s = s;
        if (_s != _switch) {
            _switch = _s;
            loop_counter++;
            if (loop_counter >= loops.len) {
                pattern_counter = 0;
                loop_counter = 0;
                duration_factor_index++;
                if (duration_factor_index >= 3)
                    duration_factor_index = 0;
            }
        }
    }
    error("WTF!?");
    return 0;
}

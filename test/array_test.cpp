#include <string.h>
#include "gtest/gtest.h"
extern "C" {
#include <array.h>
}

namespace {
    class array_test : public testing::Test {
    public:
        bdsm_array array;

        void SetUp() { bdsm_array_new(&array, 5, 15); }
        void TearDown() { bdsm_array_free(&array); }
    };

    TEST_F(array_test, making_array) {
        EXPECT_EQ(array.element_size, 5);
        EXPECT_EQ(array.size, 15);
    }

    TEST_F(array_test, set_and_get) {
        char fill[] = "hel0";

        for(int i = 0; i < 15; i++) {
            fill[3] = 'a' + i;
            memcpy(bdsm_array_at(&array, i), fill, 5);
        }

        for(int i = 0; i < 15; i++) {
            fill[3] = 'a' + i;
            EXPECT_EQ(strcmp((char*)bdsm_array_at(&array, i), fill),
                      0);
        }
    }
}

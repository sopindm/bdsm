#include "gtest/gtest.h"
extern "C" {
#include <alloc.h>
}

namespace {
    class alloc_test : public testing::Test {
    public:
        void SetUp() {}

        void TearDown() {}
    };

    TEST_F(alloc_test, allocating_memory) {
        int8_t* memory = (int8_t*)bdsm_alloc(10);
        for(int i = 0; i < 10; i++)
            memory[i] = i;

        for(int i = 0; i < 10; i++)
            EXPECT_EQ(memory[i], i);

        bdsm_free(memory);
    }
}

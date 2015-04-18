#include <string.h>
#include "gtest/gtest.h"
extern "C" {
#include <heap.h>
}

namespace {
    static int compare_ints(bdsm_heap*, const void* i1,
                            const void* i2) {
        return *(const int*)i1 < *(const int*)i2;
    }

    class heap_test : public testing::Test {
    public:
        bdsm_heap heap;

        void SetUp() {
            bdsm_vector_new(&heap.vector, sizeof(int), 0, nullptr);
            bdsm_heap_init(&heap, compare_ints);
        }
        void TearDown() { bdsm_vector_free(&heap.vector); }
    };

    TEST_F(heap_test, making_heap) {
        EXPECT_EQ(bdsm_heap_size(&heap), 0);
        EXPECT_EQ(heap.less, &compare_ints);
    }

    bool is_heap(bdsm_vector* vector) {
        for(size_t i = 0; i < vector->size / 2; i++) {
            if(*(int*)bdsm_vector_at(vector, i) >
               *(int*)bdsm_vector_at(vector, 2 * i + 1))
                return false;

            if(vector->size > (i * 2 + 2) &&
               *(int*)bdsm_vector_at(vector, i) >
                   *(int*)bdsm_vector_at(vector, 2 * i + 2))
                return false;
        }

        return true;
    }

    TEST_F(heap_test, making_non_empty_heap) {
        for(int i = 0; i < 99; i++)
            *(int*)bdsm_vector_push(&heap.vector) = 98 - i;

        bdsm_heap_init(&heap, compare_ints);

        EXPECT_EQ(bdsm_heap_size(&heap), 99);
        EXPECT_TRUE(is_heap(&heap.vector));
    }

    // heap top / head pop / heap sort
}

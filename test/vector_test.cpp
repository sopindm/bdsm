#include <string.h>
#include "gtest/gtest.h"
extern "C" {
#include <vector.h>
}

namespace {
    class vector_test : public testing::Test {
    public:
        bdsm_vector vector;

        void SetUp() {
            bdsm_vector_new(&vector, sizeof(int), 10, nullptr);
        }
        void TearDown() { bdsm_vector_free(&vector); }
    };

    TEST_F(vector_test, making_vector) {
        EXPECT_EQ(vector.element_size, sizeof(int));
        EXPECT_EQ(vector.size, 10);
        EXPECT_GE(vector.allocated_size, 10);
    }

    TEST_F(vector_test, accessing_vector) {
        for(int i = 0; i < 10; i++)
            *(int*)bdsm_vector_at(&vector, i) = i;

        for(int i = 0; i < 10; i++)
            EXPECT_EQ(*(int*)bdsm_vector_at(&vector, i), i);
    }

    TEST_F(vector_test, resizing_vector) {
        for(int i = 0; i < 10; i++)
            *(int*)bdsm_vector_at(&vector, i) = i;

        bdsm_vector_resize(&vector, 20);
        EXPECT_EQ(vector.size, 20);
        for(int i = 10; i < 20; i++)
            *(int*)bdsm_vector_at(&vector, i) = i - 20;

        for(int i = 0; i < 10; i++)
            EXPECT_EQ(*(int*)bdsm_vector_at(&vector, i), i);
        for(int i = 10; i < 20; i++)
            EXPECT_EQ(*(int*)bdsm_vector_at(&vector, i), i - 20);

        bdsm_vector_resize(&vector, 5);
        EXPECT_EQ(vector.size, 5);
        for(int i = 0; i < 5; i++)
            EXPECT_EQ(*(int*)bdsm_vector_at(&vector, i), i);
    }

    int count = 0;
    void copier(bdsm_vector*, void* to, void* from) {
        memcpy(to, from, sizeof(int));
        count++;
    }

    TEST_F(vector_test, resizing_vector_with_mover) {
        vector.mover = copier;

        for(int i = 0; i < 10; i++)
            *(int*)bdsm_vector_at(&vector, i) = i;
        bdsm_vector_resize(&vector, 20);

        EXPECT_EQ(count, 10);

        bdsm_vector_resize(&vector, 5);
        EXPECT_EQ(count, 10);
    }

    TEST_F(vector_test, pusing_to_vector) {
        for(int i = 0; i < 20; i++)
            *(int*)bdsm_vector_push(&vector) = i;

        for(int i = 10; i < 30; i++)
            EXPECT_EQ(*(int*)bdsm_vector_at(&vector, i), i - 10);
    }

    TEST_F(vector_test, popping_from_vector) {
        for(int i = 0; i < 5; i++)
            bdsm_vector_pop(&vector);

        EXPECT_EQ(vector.size, 5);
    }
}

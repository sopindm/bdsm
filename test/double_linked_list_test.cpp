#include "gtest/gtest.h"
extern "C" {
#include <dlist.h>
}

namespace {
    class dlist_test : public testing::Test {
    public:
        bdsm_dlist list;

        void SetUp() { bdsm_dlist_init(&list); }
        void TearDown() { bdsm_dlist_free(&list); }
    };

    TEST_F(dlist_test, making_empty_list) {
        EXPECT_EQ(list.size, 0);

        auto begin = bdsm_dlist_begin(&list);
        auto end = bdsm_dlist_end(&list);

        EXPECT_EQ(begin->prev, nullptr);
        EXPECT_EQ(end->prev, nullptr);
    }

    TEST_F(dlist_test, inserting_element_into_empty_list) {
        auto data =
            bdsm_dlist_insert(&list, bdsm_dlist_end(&list), 10);

        EXPECT_EQ(list.size, 1);

        auto begin = bdsm_dlist_begin(&list);
        auto end = bdsm_dlist_end(&list);

        EXPECT_EQ(bdsm_dlist_get(begin), data);

        EXPECT_EQ(begin->next, end);
        EXPECT_EQ(begin->prev, nullptr);
        EXPECT_EQ(end->prev, begin);
    }

    TEST_F(dlist_test, inserting_several_elements) {
        for(int i = 0; i < 10; i++)
            *(int*)bdsm_dlist_insert(&list, bdsm_dlist_end(&list),
                                     sizeof(int)) = i;

        EXPECT_EQ(list.size, 10);

        auto it = bdsm_dlist_begin(&list);
        EXPECT_EQ(it->prev, nullptr);

        for(int i = 0; i < 10; i++) {
            ASSERT_NE(it, bdsm_dlist_end(&list));

            EXPECT_EQ(*(int*)bdsm_dlist_get(it), i);
            it = it->next;
        }

        it = bdsm_dlist_end(&list)->prev;
        for(int i = 0; i < 10; i++) {
            ASSERT_NE(it, nullptr);

            EXPECT_EQ(*(int*)bdsm_dlist_get(it), 9 - i);
            it = it->prev;
        }
    }

    TEST_F(dlist_test, erasing_elements) {
        for(int i = 0; i < 10; i++)
            *(int*)bdsm_dlist_insert(&list, bdsm_dlist_begin(&list),
                                     sizeof(int)) = i;

        auto it = bdsm_dlist_begin(&list)->next;
        for(int i = 0; i < 5; i++) {
            bdsm_dlist_erase(&list, it);
            it = it->next->next;
        }

        it = bdsm_dlist_begin(&list);
        EXPECT_EQ(it->prev, nullptr);

        for(int i = 0; i < 5; i++) {
            EXPECT_EQ(*(int*)bdsm_dlist_get(it), (4 - i) * 2);
            it = it->next;
        }
        EXPECT_EQ(it, bdsm_dlist_end(&list));
    }

    // insert after
    // erase after
}

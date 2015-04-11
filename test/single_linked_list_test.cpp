#include "gtest/gtest.h"
extern "C" {
#include <slist.h>
}

namespace {
    class slist_test : public testing::Test {
    public:
        bdsm_slist list;

        void SetUp() { bdsm_slist_init(&list, 64); }
        void TearDown() {
            for(auto it = &list.root; it->next != nullptr;)
                bdsm_slist_erase(&list, it);
        }
    };

    TEST_F(slist_test, making_empty_list) {
        EXPECT_EQ(list.alignment, 64);
        EXPECT_EQ(list.size, 0);

        auto begin = bdsm_slist_begin(&list);
        auto end = bdsm_slist_end(&list);

        EXPECT_EQ(begin, nullptr);
        EXPECT_EQ(end, nullptr);
    }

    TEST_F(slist_test, inserting_element_into_empty_begin) {
        auto node = &list.root;

        auto data = bdsm_slist_insert(&list, node, 15);
        EXPECT_EQ((size_t)data % 64, 0);

        EXPECT_EQ(list.size, 1);
        EXPECT_EQ(bdsm_slist_get(&list, node->next), data);
        EXPECT_EQ(bdsm_slist_begin(&list), node->next);
        EXPECT_EQ(bdsm_slist_end(&list), node->next);
        EXPECT_EQ(node->next->next, nullptr);
    }

    TEST_F(slist_test, inserting_element_into_end) {
        *(int*)bdsm_slist_insert(&list, &list.root, 8) = 1;
        *(int*)bdsm_slist_insert(&list, bdsm_slist_begin(&list), 8) =
            2;

        EXPECT_EQ(list.size, 2);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, list.root.next), 1);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, list.root.next->next),
                  2);
    }

    TEST_F(slist_test, multiple_inserts) {
        for(int i = 0; i < 100; i++) {
            auto it =
                (i % 2) == 0 ? &list.root : bdsm_slist_end(&list);

            *(int*)bdsm_slist_insert(&list, it, sizeof(int)) = i;
        }

        ASSERT_EQ(list.size, 100);
        EXPECT_EQ(
            *(int*)bdsm_slist_get(&list, bdsm_slist_begin(&list)),
            98);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, bdsm_slist_end(&list)),
                  99);

        auto it = bdsm_slist_begin(&list);
        for(int i = 0; i < 100; i++) {
            auto value = (i < 50) ? (98 - i * 2) : (i * 2 - 99);

            EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), value);
            it = it->next;
        }
    }

    TEST_F(slist_test, inserting_into_middle) {
        *(int*)bdsm_slist_insert(&list, &list.root, sizeof(int)) = 0;
        for(int i = 1; i < 4; i++)
            *(int*)bdsm_slist_insert(&list, bdsm_slist_end(&list),
                                     sizeof(int)) = i;

        *(int*)bdsm_slist_insert(&list, bdsm_slist_begin(&list)->next,
                                 sizeof(int)) = 10;

        auto it = bdsm_slist_begin(&list);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 0);

        it = it->next;
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 1);

        it = it->next;
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 10);

        it = it->next;
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 2);

        it = it->next;
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 3);
    }

    TEST_F(slist_test, erasing_element_from_begin) {
        for(int i = 0; i < 10; i++)
            *(int*)bdsm_slist_insert(&list, &list.root, sizeof(int)) =
                i;

        for(int i = 0; i < 5; i++)
            bdsm_slist_erase(&list, &list.root);

        EXPECT_EQ(list.size, 5);

        auto it = bdsm_slist_begin(&list);
        for(int i = 0; i < 5; i++, it = it->next)
            EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), 4 - i);
    }

    TEST_F(slist_test, erasing_at_end) {
        *(int*)bdsm_slist_insert(&list, &list.root, sizeof(int)) = 1;
        *(int*)bdsm_slist_insert(&list, bdsm_slist_end(&list),
                                 sizeof(int)) = 2;

        bdsm_slist_erase(&list, list.root.next);
        EXPECT_EQ(bdsm_slist_end(&list), list.root.next);

        bdsm_slist_erase(&list, &list.root);
        EXPECT_EQ(bdsm_slist_begin(&list), nullptr);
        EXPECT_EQ(bdsm_slist_end(&list), nullptr);
    }
}

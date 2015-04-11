#include "gtest/gtest.h"
extern "C" {
#include <list.h>
}

namespace {
    class list_test : public testing::Test {
    public:
        void SetUp() {}

        void TearDown() {}
    };

    TEST_F(list_test, making_empty_list) {
        bdsm_slist list;
        bdsm_slist_new(&list, 64);

        EXPECT_EQ(list.alignment, 64);
        EXPECT_EQ(list.size, 0);

        auto begin = bdsm_slist_begin(&list);
        auto end = bdsm_slist_end(&list);

        EXPECT_EQ(begin, nullptr);
        EXPECT_EQ(end, nullptr);
    }

    TEST_F(list_test, inserting_element_into_empty_begin) {
        bdsm_slist list;
        bdsm_slist_new(&list, 64);

        auto node = &list.root;

        auto data = bdsm_slist_insert(&list, node, 15);
        EXPECT_EQ((size_t)data % 64, 0);

        EXPECT_EQ(list.size, 1);
        EXPECT_EQ(bdsm_slist_get(&list, node->next), data);
        EXPECT_EQ(bdsm_slist_begin(&list), node->next);
        EXPECT_EQ(bdsm_slist_end(&list), node->next);
        EXPECT_EQ(node->next->next, nullptr);

        bdsm_slist_erase(&list, node);
    }

    TEST_F(list_test, inserting_element_into_end) {
        bdsm_slist list;
        bdsm_slist_new(&list, 8);

        *(int*)bdsm_slist_insert(&list, &list.root, 8) = 1;
        *(int*)bdsm_slist_insert(&list, bdsm_slist_begin(&list), 8) =
            2;

        EXPECT_EQ(list.size, 2);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, list.root.next), 1);
        EXPECT_EQ(*(int*)bdsm_slist_get(&list, list.root.next->next),
                  2);

        bdsm_slist_erase(&list, list.root.next);
        bdsm_slist_erase(&list, &list.root);
    }

    TEST_F(list_test, multiple_inserts) {
        bdsm_slist list;
        bdsm_slist_new(&list, 8);

        for(int i = 0; i < 100; i++) {
            auto it =
                (i % 2) == 0 ? &list.root : bdsm_slist_end(&list);

            *(int*)bdsm_slist_insert(&list, it, sizeof(int)) = i;
        }

        ASSERT_EQ(list.size, 100);

        auto it = bdsm_slist_begin(&list);
        for(int i = 0; i < 100; i++) {
            auto value = (i < 50) ? (98 - i * 2) : (i * 2 - 99);

            EXPECT_EQ(*(int*)bdsm_slist_get(&list, it), value);
            it = it->next;
        }

        for(auto it = &list.root; it->next != nullptr;)
            bdsm_slist_erase(&list, it);
    }

    // moving iterator forward + several inserts

    // inserting element into empty begin
    // inserting element into empty end
    // inserting element into non-empty begin
    // inserting element into non-empty end
    // inserting element into middle

    // erasing elements
    //   from middle
    //   from begin
    //   from end
    //   erasing last element
}

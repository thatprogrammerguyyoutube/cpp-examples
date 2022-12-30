#include "doctest.h"
#include "BinarySearchTree.h"

TEST_SUITE("[binary_search_tree]") {
    TEST_CASE("[add]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3);
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE_EQ(bst.size(), 5);
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[add][dedup]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(3, 3, 3, 3, 3);
        REQUIRE(bst.contains(3));
        REQUIRE_EQ(bst.size(), 1);
        REQUIRE(!bst.empty());
        bst.remove(3);
        REQUIRE(!bst.contains(3));
        REQUIRE(bst.empty());
    }

    TEST_CASE("[remove][nothing][populated]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3);
        REQUIRE(!bst.remove(40));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][nothing][empty]") {
        auto bst = BinarySearchTree<int>{};
        REQUIRE(!bst.remove(40));
        REQUIRE(!bst.contains(7));
        REQUIRE(!bst.contains(6));
        REQUIRE(!bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(!bst.contains(3));
        REQUIRE(!bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(bst.empty());
    }

    TEST_CASE("[remove][root]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3);
        REQUIRE(bst.remove(4));
        REQUIRE_EQ(bst.size(), 4);
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][no_child][right]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3);
        REQUIRE(bst.remove(3));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(!bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][no_child][left]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3, 1);
        REQUIRE(bst.remove(1));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][no_child][root]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4);
        REQUIRE(bst.remove(4));
        REQUIRE(!bst.contains(7));
        REQUIRE(!bst.contains(6));
        REQUIRE(!bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(!bst.contains(3));
        REQUIRE(!bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(bst.empty());
    }

    TEST_CASE("[remove][one_child][left]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 5, 3);
        REQUIRE(bst.remove(6));
        REQUIRE(!bst.contains(7));
        REQUIRE(!bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][one_child][right]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 6, 2, 7, 3);
        REQUIRE(bst.remove(6));
        REQUIRE(bst.contains(7));
        REQUIRE(!bst.contains(6));
        REQUIRE(!bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][one_child][chain]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(1, 2, 3, 4, 5, 6, 7);
        REQUIRE(bst.remove(4));
        REQUIRE(bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][two_child][direct_successor]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 3, 8);
        REQUIRE(bst.remove(7));
        REQUIRE(bst.contains(8));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][two_child][indirect_successor]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 9, 3, 8);
        REQUIRE(bst.remove(7));
        REQUIRE(bst.contains(9));
        REQUIRE(bst.contains(8));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][two_child][indirect_successor][successor_child]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        REQUIRE(bst.remove(7));
        REQUIRE(bst.contains(10));
        REQUIRE(bst.contains(9));
        REQUIRE(bst.contains(8));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][many][all_present]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        REQUIRE(bst.remove(7, 4, 3, 5));
        REQUIRE(bst.contains(10));
        REQUIRE(bst.contains(9));
        REQUIRE(bst.contains(8));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(!bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(!bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][many][some_present]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        REQUIRE(bst.remove(7, 4, 3, 25));
        REQUIRE(bst.contains(10));
        REQUIRE(bst.contains(9));
        REQUIRE(bst.contains(8));
        REQUIRE(!bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(!bst.contains(4));
        REQUIRE(!bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[remove][many][none_present]") {
        auto bst = BinarySearchTree<int>{};
        bst.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        REQUIRE(!bst.remove(57, 54, 53, 25));
        REQUIRE(bst.contains(10));
        REQUIRE(bst.contains(9));
        REQUIRE(bst.contains(8));
        REQUIRE(bst.contains(7));
        REQUIRE(bst.contains(6));
        REQUIRE(bst.contains(5));
        REQUIRE(bst.contains(4));
        REQUIRE(bst.contains(3));
        REQUIRE(bst.contains(2));
        REQUIRE(!bst.contains(1));
        REQUIRE(!bst.empty());
    }

    TEST_CASE("[copy][constructor][is_deep_copy]") {
        auto bst1 = BinarySearchTree<int>{};
        bst1.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        auto bst2 = BinarySearchTree<int>{bst1};
        bst2.add(25).remove(10);
        bst1.add(32).remove(2, 5);

        REQUIRE(bst2.contains(2, 5, 25));
        REQUIRE(!bst2.contains(32));

        REQUIRE(bst1.contains(32, 10));
        REQUIRE(!bst1.contains(2, 5));
    }

    TEST_CASE("[copy][operator][is_deep_copy]") {
        auto bst1 = BinarySearchTree<int>{};
        bst1.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        auto bst2 = BinarySearchTree<int>{};
        bst2 = bst1;
        bst2.add(25).remove(10);
        bst1.add(32).remove(2, 5);

        REQUIRE(bst2.contains(2, 5, 25));
        REQUIRE(!bst2.contains(32));

        REQUIRE(bst1.contains(32, 10));
        REQUIRE(!bst1.contains(2, 5));
    }

    TEST_CASE("[copy][operator][no_recursion][is_deep_copy]") {
        auto bst1 = BinarySearchTree<int, std::less<>>{};
        bst1.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        auto bst2 = bst1.copy_queue();
        bst2 = bst1;
        bst2.add(25).remove(10);
        bst1.add(32).remove(2, 5);

        REQUIRE(bst2.contains(2, 5, 25));
        REQUIRE(!bst2.contains(32));

        REQUIRE(bst1.contains(32, 10));
        REQUIRE(!bst1.contains(2, 5));
    }

    TEST_CASE("[copy][operator][recursion][is_deep_copy]") {
        auto bst1 = BinarySearchTree<int, std::less<>>{};
        bst1.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        auto bst2 = bst1.copy_recursive();
        bst2 = bst1;
        bst2.add(25).remove(10);
        bst1.add(32).remove(2, 5);

        REQUIRE(bst2.contains(2, 5, 25));
        REQUIRE(!bst2.contains(32));

        REQUIRE(bst1.contains(32, 10));
        REQUIRE(!bst1.contains(2, 5));
    }

    TEST_CASE("[move]") {
        auto bst1 = BinarySearchTree<int>{};
        bst1.add(4, 7, 2, 5, 6, 10, 3, 8, 9);
        auto bst2 = BinarySearchTree<int>{};
        bst2 = bst1;
        bst2.add(25).remove(10);
        bst1.add(32).remove(2, 5);
        std::swap(bst1, bst2);

        REQUIRE(bst1.contains(2, 5, 25));
        REQUIRE(!bst1.contains(32));

        REQUIRE(bst2.contains(32, 10));
        REQUIRE(!bst2.contains(2, 5));
    }
}

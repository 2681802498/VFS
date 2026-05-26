#include <catch2/catch_test_macros.hpp>

#include "test_helpers.h"

static void setup_fs() {
    reset_globals();
    fs_cleanup();
    format();
    /* install() loads the fresh superblock; iget(1) returns nullptr
       but filsys data is loaded correctly */
    install();
}

TEST_CASE("balloc() allocates blocks in LIFO order", "[balloc]") {
    setup_fs();

    /* After format: s_free[0..49] = [3, 4, ..., 52], s_pfree = 49 */

    /* First allocation returns the top of the stack */
    uint32_t b1 = balloc();
    REQUIRE(b1 == 3 + NICFREE - 1); /* block 52 */
    REQUIRE(g_filsys.s_nfree == NICFREE - 1);
    REQUIRE(g_filsys.s_pfree == NICFREE - 2);

    /* Second allocation */
    uint32_t b2 = balloc();
    REQUIRE(b2 == 3 + NICFREE - 2); /* block 51 */

    fs_cleanup();
}

TEST_CASE("bfree() returns block to free stack", "[bfree]") {
    setup_fs();

    uint32_t b1 = balloc(); /* allocate one block */
    uint32_t nfree_before = g_filsys.s_nfree;
    uint32_t pfree_before = g_filsys.s_pfree;

    bfree(b1);
    REQUIRE(g_filsys.s_nfree == nfree_before + 1);
    REQUIRE(g_filsys.s_pfree == pfree_before + 1);
    REQUIRE(g_filsys.s_free[g_filsys.s_pfree] == b1);

    fs_cleanup();
}

TEST_CASE("bfree() spills to disk when stack is full", "[bfree]") {
    setup_fs();

    /* Allocate blocks until s_nfree reaches 1, then one more to trigger group load.
       After format: s_nfree=50, s_pfree=49. 50 allocations drain the initial stack. */
    for (int i = 0; i < 50; i++) {
        balloc();
    }

    /* Fill the stack back up to NICFREE properly */
    for (uint16_t i = 0; i < NICFREE; i++) {
        g_filsys.s_free[i] = 200 + i;
    }
    g_filsys.s_nfree = NICFREE;
    g_filsys.s_pfree = NICFREE - 1;
    REQUIRE(g_filsys.s_nfree == NICFREE);

    /* Now bfree should spill: write current stack to disk, put block in slot 0 */
    uint32_t spill_block = 999;
    bfree(spill_block);

    REQUIRE(g_filsys.s_nfree == 1);
    REQUIRE(g_filsys.s_pfree == 0);
    REQUIRE(g_filsys.s_free[0] == spill_block);

    fs_cleanup();
}

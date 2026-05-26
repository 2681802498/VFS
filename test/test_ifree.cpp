#include <catch2/catch_test_macros.hpp>

#include "test_helpers.h"

TEST_CASE("ifree() adds inode back to free stack", "[ifree]") {
    reset_globals();

    g_filsys.s_ninode = 10;
    g_filsys.s_pinode = 9;
    g_filsys.s_rinode = 4;

    ifree(100);

    /* Stack should have one more entry */
    REQUIRE(g_filsys.s_ninode == 11);
    REQUIRE(g_filsys.s_pinode == 10);
    REQUIRE(g_filsys.s_inode[10] == 100);
    REQUIRE(g_filsys.s_fmod == SUPDATE);
}

TEST_CASE("ifree() updates s_rinode for lower-numbered inode", "[ifree]") {
    reset_globals();

    g_filsys.s_ninode = 5;
    g_filsys.s_pinode = 4;
    g_filsys.s_rinode = 50; /* remembered inode */

    ifree(30); /* lower than current s_rinode */

    REQUIRE(g_filsys.s_rinode == 30);
    REQUIRE(g_filsys.s_ninode == 6);
    REQUIRE(g_filsys.s_pinode == 5);
}

TEST_CASE("ifree() does not update s_rinode for higher-numbered inode", "[ifree]") {
    reset_globals();

    g_filsys.s_ninode = 5;
    g_filsys.s_pinode = 4;
    g_filsys.s_rinode = 50;

    ifree(80); /* higher than current s_rinode */

    REQUIRE(g_filsys.s_rinode == 50); /* unchanged */
}

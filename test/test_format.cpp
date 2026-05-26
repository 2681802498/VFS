#include <cstdio>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

#include "test_helpers.h"

TEST_CASE("format() creates the virtual disk file", "[format]") {
    reset_globals();
    fs_cleanup();

    format();

    FILE *f = std::fopen("filesystem", "rb");
    REQUIRE(f != nullptr);
    std::fclose(f);
    fs_cleanup();
}

TEST_CASE("format() writes correct superblock values", "[format]") {
    reset_globals();
    fs_cleanup();
    format();

    /* Re-open and read the superblock directly */
    FILE *f = std::fopen("filesystem", "rb");
    REQUIRE(f != nullptr);

    filsys sb;
    std::fseek(f, BLOCKSIZ, SEEK_SET);
    std::fread(&sb, sizeof(sb), 1, f);
    std::fclose(f);

    REQUIRE(sb.s_isize == DINODEBLK);
    REQUIRE(sb.s_fsize == FILEBLK);
    REQUIRE(sb.s_nfree == NICFREE);
    REQUIRE(sb.s_pfree == NICFREE - 1);
    /* First free block should be block 3 (after boot, superblock, inode area) */
    REQUIRE(sb.s_free[sb.s_pfree] == 3 + NICFREE - 1);

    fs_cleanup();
}

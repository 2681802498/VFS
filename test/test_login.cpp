#include <catch2/catch_test_macros.hpp>

#include "test_helpers.h"

static void setup_passwords() {
    reset_globals();
    g_pwd[0].p_uid = 0;
    g_pwd[0].p_gid = 0;
    std::strcpy(g_pwd[0].password, "root");

    g_pwd[1].p_uid = 1;
    g_pwd[1].p_gid = 1;
    std::strcpy(g_pwd[1].password, "pass1");
}

TEST_CASE("login() with correct credentials succeeds", "[login]") {
    setup_passwords();

    int32_t result = login(0, "root");
    REQUIRE(result == 1);
    REQUIRE(g_user_id == 0);
    REQUIRE(g_user[0].u_uid == 0);
    REQUIRE(g_user[0].u_gid == 0);
    REQUIRE(g_user[0].u_default_mode == DEFAULTMODE);
}

TEST_CASE("login() with wrong password fails", "[login]") {
    setup_passwords();

    int32_t result = login(0, "wrong");
    REQUIRE(result == 0);
    REQUIRE(g_user_id == -1);
}

TEST_CASE("login() with unknown uid fails", "[login]") {
    setup_passwords();

    int32_t result = login(99, "root");
    REQUIRE(result == 0);
}

TEST_CASE("login() fills the first available user slot", "[login]") {
    setup_passwords();

    /* Pre-fill slot 0 */
    g_user[0].u_uid = 5;
    g_user[1].u_uid = 0; /* empty */

    int32_t result = login(1, "pass1");
    REQUIRE(result == 1);
    REQUIRE(g_user_id == 1); /* should use slot 1 */
    REQUIRE(g_user[1].u_uid == 1);
    REQUIRE(g_user[1].u_gid == 1);
}

TEST_CASE("logout() clears user session", "[logout]") {
    setup_passwords();
    login(0, "root");

    int32_t result = logout(0);
    REQUIRE(result == 1);
    REQUIRE(g_user[0].u_uid == 0);
    REQUIRE(g_user[0].u_gid == 0);
    REQUIRE(g_user[0].u_default_mode == 0);
    REQUIRE(g_user_id == -1);
}

TEST_CASE("logout() with unknown uid returns 0", "[logout]") {
    setup_passwords();

    int32_t result = logout(99);
    REQUIRE(result == 0);
}

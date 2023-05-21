#ifndef LUA_MBED_BIGINT_H__
#define LUA_MBED_BIGINT_H__
// #if defined(MBEDTLS_BIGNUM_C)
#include "lua.h"

#define LUA_MBED_BIGINT_METATABLE "MBED_BIGINT"

int l_mbed_new_bigint(lua_State *L);
int l_mbed_bigint_add(lua_State *L);
int l_mbed_bigint_add_abs(lua_State *L);
int l_mbed_bigint_sub(lua_State *L);
int l_mbed_bigint_sub_abs(lua_State *L);
int l_mbed_bigint_mul(lua_State *L);
int l_mbed_bigint_div(lua_State *L);
int l_mbed_bigint_mod(lua_State *L);
int l_mbed_bigint_neg(lua_State *L);
int l_mbed_bigint_exp(lua_State *L);
int l_mbed_bigint_exp_mod(lua_State *L);
int l_mbed_bigint_lt(lua_State *L);
int l_mbed_bigint_le(lua_State *L);
int l_mbed_bigint_len(lua_State *L);
int l_mbed_bigint_tostring(lua_State *L);
int l_mbed_bigint_create_meta(lua_State *L);
int l_mbed_bigint_tobinary(lua_State *L);
int l_mbed_bigint_tobinary_le(lua_State *L);
int l_mbed_bigint_frombinary(lua_State *L);
int l_mbed_bigint_frombinary_le(lua_State *L);

#endif
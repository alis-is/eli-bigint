#ifndef ELI_BIGINT_H__
#define ELI_BIGINT_H__
// #if defined(MBEDTLS_BIGNUM_C)
#include "lua.h"

#define ELI_BIGINT_METATABLE "ELI_BIGINT_METATABLE"

int eli_new_bigint(lua_State *L);
int eli_bigint_add(lua_State *L);
int eli_bigint_add_abs(lua_State *L);
int eli_bigint_sub(lua_State *L);
int eli_bigint_sub_abs(lua_State *L);
int eli_bigint_mul(lua_State *L);
int eli_bigint_div(lua_State *L);
int eli_bigint_mod(lua_State *L);
int eli_bigint_neg(lua_State *L);
int eli_bigint_exp(lua_State *L);
int eli_bigint_exp_mod(lua_State *L);
int eli_bigint_lt(lua_State *L);
int eli_bigint_le(lua_State *L);
int eli_bigint_len(lua_State *L);
int eli_bigint_tostring(lua_State *L);
int eli_bigint_create_meta(lua_State *L);

#endif
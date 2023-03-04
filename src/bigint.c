#include "bigint.h"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "mbedtls/bignum.h"
#include <math.h>
#include <stdlib.h>


/*
 * internal function to create a new bigint userdata on the stack and return it.
 */
mbedtls_mpi *new_eli_bigint(lua_State *L) {
  mbedtls_mpi *bi = (mbedtls_mpi *)lua_newuserdatauv(L, sizeof(mbedtls_mpi), 0);
  if (bi) {
    mbedtls_mpi_init(bi);
    luaL_getmetatable(L, ELI_BIGINT_METATABLE);
    lua_setmetatable(L, -2);
  }
  return bi;
}

/*
 * Get stack element at index as bigint.x
 */
mbedtls_mpi *stack_element_to_bigint(lua_State *L, int index) {
  switch (lua_type(L, index)) {
  case LUA_TNUMBER: {
    int n = 0;
    if (lua_isinteger(L, index)) {
      n = lua_tointeger(L, index);
    } else {
      lua_Number d = l_floor(luaL_checknumber(L, index));
      lua_Integer li;
      if (lua_numbertointeger(d, &li)) {
        n = (int)li;
      } else {
        luaL_error(L, "cannot conver float to integer");
        return NULL;
      }
    }
    mbedtls_mpi *bi = new_eli_bigint(L);
    int res = mbedtls_mpi_lset(bi, n);
    if (res != 0) {
      luaL_error(L, "error setting bigint value: %d", res);
      return NULL;
    }
    return bi;
  }
  case LUA_TSTRING: {
    mbedtls_mpi *bi = new_eli_bigint(L);
    int res = mbedtls_mpi_read_string(bi, 10, lua_tostring(L, index));
    if (res != 0) {
      luaL_error(L, "error setting bigint value: %d", res);
      return NULL;
    }
    return bi;
  }
  case LUA_TUSERDATA:
    return (mbedtls_mpi *)luaL_checkudata(L, index, ELI_BIGINT_METATABLE);
  default:
    return NULL;
  }
}

/*
 * Create a new bigint userdata on the stack and return it.
 */
int eli_new_bigint(lua_State *L) {
  mbedtls_mpi *bi = new_eli_bigint(L);

  switch (lua_type(L, 1)) {
  case LUA_TNUMBER: {
    int res = mbedtls_mpi_lset(bi, lua_tointeger(L, 1));
    if (res != 0) {
      return luaL_error(L, "error setting bigint value: %d", res);
    }
    break;
  }
  case LUA_TSTRING: {
    int res = mbedtls_mpi_read_string(bi, 10, lua_tostring(L, 1));
    if (res != 0) {
      return luaL_error(L, "error setting bigint value: %d", res);
    }
    break;
  }
  case LUA_TNIL:
    break;
  case LUA_TUSERDATA: {
    mbedtls_mpi *bi1 =
        (mbedtls_mpi *)luaL_checkudata(L, 1, ELI_BIGINT_METATABLE);
    int res = mbedtls_mpi_copy(bi, bi1);
    if (res != 0) {
      return luaL_error(L, "error setting bigint value: %d", res);
    }
    break;
  }
  default:
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  return 1;
}

int eli_bigint_add(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_add_mpi(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error adding bigints: %d", res);
  }
  return 1;
}

int eli_bigint_add_abs(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_add_abs(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error adding bigints: %d", res);
  }
  return 1;
}

int eli_bigint_sub(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_sub_mpi(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error subtracting bigints: %d", res);
  }
  return 1;
}

int eli_bigint_sub_abs(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_sub_abs(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error subtracting bigints: %d", res);
  }
  return 1;
}

int eli_bigint_mul(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_mul_mpi(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error multiplying bigints: %d", res);
  }
  return 1;
}

int eli_bigint_div(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_div_mpi(bi3, NULL, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error dividing bigints: %d", res);
  }
  return 1;
}

int eli_bigint_mod(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_mod_mpi(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error modding bigints: %d", res);
  }
  return 1;
}

int eli_bigint_neg(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }

  mbedtls_mpi *bi2 = new_eli_bigint(L);
  if (bi2 == NULL) {
    return luaL_error(L, "error creating bigint");
  }
  int res = mbedtls_mpi_lset(bi2, -1);
  if (res != 0) {
    return luaL_error(L, "error setting bigint: %d", res);
  }

  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  res = mbedtls_mpi_mul_mpi(bi3, bi1, bi2);
  if (res != 0) {
    return luaL_error(L, "error negating bigint: %d", res);
  }
  return 1;
}

int eli_bigint_exp(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = new_eli_bigint(L);
  if (bi3 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  if (mbedtls_mpi_cmp_int(bi2, 0) == 0) {
    mbedtls_mpi_lset(bi3, 1);
    return 1;
  }

  int res = mbedtls_mpi_copy(bi3, bi1);
  if (res != 0) {
    return luaL_error(L, "error exponentiating bigints: %d", res);
  }

  if (mbedtls_mpi_cmp_int(bi2, 1) == 0) {
    return 1;
  }

  mbedtls_mpi *bi4 = new_eli_bigint(L);
  if (bi4 == NULL) {
    return luaL_error(L, "error creating bigint");
  }
  res = mbedtls_mpi_copy(bi4, bi2);
  if (res != 0) {
    return luaL_error(L, "error exponentiating bigints: %d", res);
  }

  while (mbedtls_mpi_cmp_int(bi4, 1) > 0) {
    int res = mbedtls_mpi_mul_mpi(bi3, bi3, bi1);
    if (res != 0) {
      return luaL_error(L, "error exponentiating bigints: %d", res);
    }
    res = mbedtls_mpi_sub_int(bi4, bi4, 1);
    if (res != 0) {
      return luaL_error(L, "error exponentiating bigints: %d", res);
    }
  }
  lua_pop(L, 1); // pop bi4
  return 1;
}

int eli_bigint_exp_mod(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  mbedtls_mpi *bi3 = stack_element_to_bigint(L, 3);
  if (bi3 == NULL) {
    return luaL_typeerror(L, 3, "number or string or bigint");
  }
  mbedtls_mpi *bi4;
  switch (lua_type(L, 4)) {
  case LUA_TNIL:
    break;
  default:
    bi4 = luaL_checkudata(L, 4, ELI_BIGINT_METATABLE);
    break;
  }
  mbedtls_mpi *bi5 = new_eli_bigint(L);
  if (bi5 == NULL) {
    return luaL_error(L, "error creating bigint");
  }

  int res = mbedtls_mpi_exp_mod(bi5, bi1, bi2, bi3, bi4);
  if (res != 0) {
    return luaL_error(L, "error exponentiating bigints: %d", res);
  }
  return 1;
}

int eli_bigint_idiv(lua_State *L) { return eli_bigint_div(L); }

int eli_bigint_eq(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  lua_pushboolean(L, mbedtls_mpi_cmp_mpi(bi1, bi2) == 0);
  return 1;
}

int eli_bigint_lt(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  lua_pushboolean(L, mbedtls_mpi_cmp_mpi(bi1, bi2) < 0);
  return 1;
}

int eli_bigint_le(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  mbedtls_mpi *bi2 = stack_element_to_bigint(L, 2);
  if (bi2 == NULL) {
    return luaL_typeerror(L, 2, "number or string or bigint");
  }
  lua_pushboolean(L, mbedtls_mpi_cmp_mpi(bi1, bi2) <= 0);
  return 1;
}

int eli_bigint_len(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  lua_pushinteger(L, mbedtls_mpi_size(bi1));
  return 1;
}

int eli_bigint_tostring(lua_State *L) {
  mbedtls_mpi *bi1 = stack_element_to_bigint(L, 1);
  if (bi1 == NULL) {
    return luaL_typeerror(L, 1, "number or string or bigint");
  }
  // find size with bufflen = 0
  size_t bufflen = 0;
  if (mbedtls_mpi_write_string(bi1, 10, NULL, bufflen, &bufflen) !=
      MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL) {
    return luaL_error(L, "mbedtls_mpi_write_string failed");
  }
  char *str = (char *)malloc(bufflen);
  int res = mbedtls_mpi_write_string(bi1, 10, str, bufflen, &bufflen);
  lua_pushlstring(L, str, bufflen - 1);
  free(str);
  if (res == 0) {
    return 1;
  }

  lua_pushnil(L);
  lua_pushfstring(L, "mbedtls_mpi_write_string failed: %d", res);
  return 2;
}

int eli_bigint_free(lua_State *L) {
  mbedtls_mpi *bi1 = (mbedtls_mpi *)luaL_checkudata(L, 1, ELI_BIGINT_METATABLE);
  if (bi1 != NULL) {
    mbedtls_mpi_free(bi1);
  }
  return 0;
}

int eli_bigint_create_meta(lua_State *L) {
  luaL_newmetatable(L, ELI_BIGINT_METATABLE);

  /* metatable fields*/
  lua_pushcfunction(L, eli_bigint_add);
  lua_setfield(L, -2, "__add");
  lua_pushcfunction(L, eli_bigint_sub);
  lua_setfield(L, -2, "__sub");
  lua_pushcfunction(L, eli_bigint_mul);
  lua_setfield(L, -2, "__mul");
  lua_pushcfunction(L, eli_bigint_div);
  lua_setfield(L, -2, "__div");
  lua_pushcfunction(L, eli_bigint_mod);
  lua_setfield(L, -2, "__mod");
  lua_pushcfunction(L, eli_bigint_exp);
  lua_setfield(L, -2, "__pow");
  lua_pushcfunction(L, eli_bigint_neg);
  lua_setfield(L, -2, "__unm");
  lua_pushcfunction(L, eli_bigint_idiv);
  lua_setfield(L, -2, "__idiv");
  lua_pushcfunction(L, eli_bigint_eq);
  lua_setfield(L, -2, "__eq");
  lua_pushcfunction(L, eli_bigint_lt);
  lua_setfield(L, -2, "__lt");
  lua_pushcfunction(L, eli_bigint_le);
  lua_setfield(L, -2, "__le");
  lua_pushcfunction(L, eli_bigint_len);
  lua_setfield(L, -2, "__len");
  lua_pushcfunction(L, eli_bigint_tostring);
  lua_setfield(L, -2, "__tostring");
  lua_pushstring(L, ELI_BIGINT_METATABLE);
  lua_setfield(L, -2, "__type");
  lua_pushcfunction(L, eli_bigint_free);
  lua_setfield(L, -2, "__gc");

  /* methods under __index */
  lua_newtable(L);
  lua_pushcfunction(L, eli_bigint_add);
  lua_setfield(L, -2, "add");
  lua_pushcfunction(L, eli_bigint_sub);
  lua_setfield(L, -2, "sub");
  lua_pushcfunction(L, eli_bigint_mul);
  lua_setfield(L, -2, "mul");
  lua_pushcfunction(L, eli_bigint_div);
  lua_setfield(L, -2, "div");
  lua_pushcfunction(L, eli_bigint_mod);
  lua_setfield(L, -2, "mod");
  lua_pushcfunction(L, eli_bigint_exp);
  lua_setfield(L, -2, "pow");
  lua_pushcfunction(L, eli_bigint_neg);
  lua_setfield(L, -2, "unm");
  lua_pushcfunction(L, eli_bigint_idiv);
  lua_setfield(L, -2, "idiv");
  lua_pushcfunction(L, eli_bigint_eq);
  lua_setfield(L, -2, "eq");
  lua_pushcfunction(L, eli_bigint_lt);
  lua_setfield(L, -2, "lt");
  lua_pushcfunction(L, eli_bigint_le);
  lua_setfield(L, -2, "le");
  lua_pushcfunction(L, eli_bigint_len);
  lua_setfield(L, -2, "len");
  lua_pushcfunction(L, eli_bigint_tostring);
  lua_setfield(L, -2, "tostring");
  lua_pushstring(L, ELI_BIGINT_METATABLE);
  lua_setfield(L, -2, "__type");

  lua_setfield(L, -2, "__index");

  return 1;
}
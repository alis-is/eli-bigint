#include "lua.h"
#include "lauxlib.h"
#include "bigint.h"

static const struct luaL_Reg eliBigint[] = {
    {"new", eli_new_bigint},
	{"add", eli_bigint_add},
	{"add_abs", eli_bigint_add_abs},
	{"sub", eli_bigint_sub},
	{"sub_abs", eli_bigint_sub_abs},
	{"mul", eli_bigint_mul},
	{"div", eli_bigint_div},
	{"mod", eli_bigint_mod},
	{"neg", eli_bigint_neg},
	{"exp", eli_bigint_exp},
	{"exp_mod", eli_bigint_exp_mod},
    {NULL, NULL},
};


int luaopen_eli_bigint(lua_State *L) {
	eli_bigint_create_meta(L);
	lua_newtable(L);
	luaL_setfuncs(L, eliBigint, 0);
	return 1;
}
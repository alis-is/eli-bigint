#include "lua.h"
#include "lauxlib.h"
#include "bigint.h"

static const struct luaL_Reg luaBigint[] = {
    {"new", l_mbed_new_bigint},
	{"add", l_mbed_bigint_add},
	{"add_abs", l_mbed_bigint_add_abs},
	{"sub", l_mbed_bigint_sub},
	{"sub_abs", l_mbed_bigint_sub_abs},
	{"mul", l_mbed_bigint_mul},
	{"div", l_mbed_bigint_div},
	{"mod", l_mbed_bigint_mod},
	{"neg", l_mbed_bigint_neg},
	{"exp", l_mbed_bigint_exp},
	{"exp_mod", l_mbed_bigint_exp_mod},
	{"tobinary", l_mbed_bigint_tobinary},
	{"tobinary_le", l_mbed_bigint_tobinary_le},
	{"frombinary", l_mbed_bigint_frombinary},
	{"frombinary_le", l_mbed_bigint_frombinary_le},
    {NULL, NULL},
};


int luaopen_l_mbed_bigint(lua_State *L) {
	l_mbed_bigint_create_meta(L);
	lua_newtable(L);
	luaL_setfuncs(L, luaBigint, 0);
	return 1;
}
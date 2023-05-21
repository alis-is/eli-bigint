#ifndef LUA_MBED_BIGINT_H__
#define LUA_MBED_BIGINT_H__
// #if defined(MBEDTLS_BIGNUM_C)
#include "lua.h"

/*
---#DES 'MBED_BIGINT'
---
---The MBED_BIGINT class represents a context for handling large integers.
---It provides methods for performing various operations on big integers,
---A MBED_BIGINT can be instantiated with `bigint.new`.
---@class MBED_BIGINT
*/
#define LUA_MBED_BIGINT_METATABLE "MBED_BIGINT"

/*
---#DES 'bigint.new'
---
---Creates a new bigint userdata on the stack and returns it.
---If an error occurs during the initialization, 
---the function returns nil and an error message.
---@return bigint|nil, nil|string: the new bigint userdata, or nil and an error message in case of errors.
*/
int l_mbed_new_bigint(lua_State *L);
/*
---#DES 'bigint.add'
---
---Adds two big integers together.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the first big integer to add.
---@param bi2 MBED_BIGINT: the second big integer to add.
---@return MBED_BIGINT|nil, nil|string: the result of the addition, or nil and an error message in case of errors.
*/
int l_mbed_bigint_add(lua_State *L);
/*
---#DES 'bigint.add_abs'
---
---Adds the absolute values of two big integers together.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the first big integer to add.
---@param bi2 MBED_BIGINT: the second big integer to add.
---@return MBED_BIGINT|nil, nil|string: the result of the addition, or nil and an error message in case of errors.
*/
int l_mbed_bigint_add_abs(lua_State *L);
/*
---#DES 'bigint.sub'
---
---Subtracts the second big integer from the first.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the minuend big integer.
---@param bi2 MBED_BIGINT: the subtrahend big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the subtraction, or nil and an error message in case of errors.
*/
int l_mbed_bigint_sub(lua_State *L);
/*
---#DES 'bigint.sub_abs'
---
---Subtracts the absolute value of the second big integer from the absolute value of the first.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the first big integer.
---@param bi2 MBED_BIGINT: the second big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the subtraction, or nil and an error message in case of errors.
*/
int l_mbed_bigint_sub_abs(lua_State *L);
/*
---#DES 'bigint.mul'
---
---Multiplies two big integers together.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the first big integer to multiply.
---@param bi2 MBED_BIGINT: the second big integer to multiply.
---@return MBED_BIGINT|nil, nil|string: the result of the multiplication, or nil and an error message in case of errors.
*/
int l_mbed_bigint_mul(lua_State *L);
/*
---#DES 'bigint.div'
---
---Divides the first big integer by the second.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the dividend big integer.
---@param bi2 MBED_BIGINT: the divisor big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the division, or nil and an error message in case of errors.
*/
int l_mbed_bigint_div(lua_State *L);
/*
---#DES 'bigint.mod'
---
---Calculates the modulus of the first big integer by the second.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the dividend big integer.
---@param bi2 MBED_BIGINT: the divisor big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the modulus operation, or nil and an error message in case of errors.
*/
int l_mbed_bigint_mod(lua_State *L);
/*
---#DES 'bigint.neg'
---
---Negates a big integer.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the big integer to negate.
---@return MBED_BIGINT|nil, nil|string: the negated big integer, or nil and an error message in case of errors.
*/
int l_mbed_bigint_neg(lua_State *L);
/*
---#DES 'bigint.exp'
---
---Performs exponentiation operation on big integers.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the base big integer.
---@param bi2 MBED_BIGINT: the exponent big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the exponentiation, or nil and an error message in case of errors.
*/
int l_mbed_bigint_exp(lua_State *L);
/*
---#DES 'bigint.exp_mod'
---
---Performs modular exponentiation on big integers.
---If an error occurs during the operation, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the base big integer.
---@param bi2 MBED_BIGINT: the exponent big integer.
---@param bi3 MBED_BIGINT: the modulus big integer.
---@return MBED_BIGINT|nil, nil|string: the result of the modular exponentiation, or nil and an error message in case of errors.
*/
int l_mbed_bigint_exp_mod(lua_State *L);

int l_mbed_bigint_eq(lua_State *L);
int l_mbed_bigint_lt(lua_State *L);
int l_mbed_bigint_le(lua_State *L);
int l_mbed_bigint_len(lua_State *L);
int l_mbed_bigint_tostring(lua_State *L);

/*
---#DES 'bigint.tobinary'
---
---Converts a big integer into a binary representation.
---If the input is not a big integer, 
---the function throws a type error. If the conversion fails, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the big integer.
---@return string|nil, nil|string: the binary representation of the big integer, or nil and an error message in case of errors.
*/
int l_mbed_bigint_tobinary(lua_State *L);
/*
---#DES 'bigint.tobinary_le'
---
---Converts a big integer into a binary representation in little endian order.
---If the input is not a big integer, 
---the function throws a type error. If the conversion fails, 
---the function returns an error message.
---@param bi1 MBED_BIGINT: the big integer.
---@return string|nil, nil|string: the little-endian binary representation of the big integer, or nil and an error message in case of errors.
*/
int l_mbed_bigint_tobinary_le(lua_State *L);
/*
---#DES 'bigint.frombinary'
---
---Creates a big integer from a binary string.
---If the input is not a string, 
---the function throws a type error. If the creation fails, 
---the function returns an error message.
---@param str string: the binary string.
---@return MBED_BIGINT|nil, nil|string: the created big integer, or nil and an error message in case of errors.
*/
int l_mbed_bigint_frombinary(lua_State *L);
/*
---#DES 'bigint.frombinary_le'
---
---Creates a big integer from a binary string in little endian order.
---If the input is not a string, 
---the function throws a type error. If the creation fails, 
---the function returns an error message.
---@param str string: the little-endian binary string.
---@return MBED_BIGINT|nil, nil|string: the created big integer, or nil and an error message in case of errors.
*/
int l_mbed_bigint_frombinary_le(lua_State *L);

int l_mbed_bigint_create_meta(lua_State *L);
#endif
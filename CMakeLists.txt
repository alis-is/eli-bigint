project (lua_mbed_bigint)

file(GLOB lua_mbed_bigint_sources ./src/**.c)
set(lua_mbed_bigint ${lua_mbed_bigint_sources})

add_library(lua_mbed_bigint ${lua_mbed_bigint})
target_link_libraries(lua_mbed_bigint)
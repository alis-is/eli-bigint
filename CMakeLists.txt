project (eli_bigint)

file(GLOB eli_bigint_sources ./src/**.c)
set(eli_bigint ${eli_bigint_sources})

add_library(eli_bigint ${eli_bigint})
target_link_libraries(eli_bigint)
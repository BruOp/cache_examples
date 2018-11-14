file(GLOB MY_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MY_INCLUDE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(naive_simple ${MY_SOURCE} ${MY_INCLUDE})
target_include_directories(naive_simple PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties(naive_simple PROPERTIES FOLDER "" )

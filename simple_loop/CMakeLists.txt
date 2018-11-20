file(GLOB MY_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MY_INCLUDE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(simple_loop ${MY_SOURCE} ${MY_INCLUDE})
target_include_directories(simple_loop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties(simple_loop PROPERTIES FOLDER "" )

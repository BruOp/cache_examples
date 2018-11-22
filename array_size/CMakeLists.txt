file(GLOB MY_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MY_INCLUDE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(array_size ${MY_SOURCE} ${MY_INCLUDE})
target_include_directories(array_size PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties(array_size PROPERTIES FOLDER "" )

file(GLOB MY_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB MY_INCLUDE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(matrix_multiplication ${MY_SOURCE} ${MY_INCLUDE})
target_include_directories(matrix_multiplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties(matrix_multiplication PROPERTIES FOLDER "" )


cmake_minimum_required(VERSION 2.6)

project(backlight)

add_executable(bl bl.c)

set(CMAKE_C_FLAGS "-std=c99")

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bm
	COMMAND ln -sr ${CMAKE_CURRENT_BINARY_DIR}/bl ${CMAKE_CURRENT_BINARY_DIR}/bm
	DEPENDS bl
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bp
	COMMAND ln -sr ${CMAKE_CURRENT_BINARY_DIR}/bl ${CMAKE_CURRENT_BINARY_DIR}/bp
	DEPENDS bl
)
add_custom_target(
	symlinks ALL
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bm ${CMAKE_CURRENT_BINARY_DIR}/bp
)

install(
	TARGETS bl
	DESTINATION bin
	PERMISSIONS SETUID SETGID WORLD_EXECUTE
)

install(
	FILES bm bp
	DESTINATION bin
)


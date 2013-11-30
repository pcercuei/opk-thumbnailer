cmake_minimum_required(VERSION 2.8.8)
project(opk-thumbnailer C)

set(VERSION "0.1")

find_package(PkgConfig)
pkg_check_modules(LIBOPK QUIET libopk)
if (NOT LIBOPK_FOUND)
	message(FATAL_ERROR "'libopk' must be installed first!")
endif()

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${LIBOPK_CFLAGS_OTHER})
include_directories(${LIBOPK_INCLUDE_DIRS})

set(THUMB_THUMBNAILER ${CMAKE_CURRENT_BINARY_DIR}/opk.thumbnailer)
configure_file(opk.thumbnailer.cmakein ${THUMB_THUMBNAILER} @ONLY)
install(FILES ${THUMB_THUMBNAILER} DESTINATION "${CMAKE_INSTALL_PREFIX}/share/thumbnails")

set(THUMB_CFILES opk-thumbnailer.c)

add_executable(opk-thumbnailer ${THUMB_CFILES})
target_link_libraries(opk-thumbnailer ${LIBOPK_LIBRARIES})
install(TARGETS opk-thumbnailer RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

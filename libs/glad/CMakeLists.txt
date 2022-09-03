cmake_minimum_required (VERSION 3.8)

set(HEADER_FILES include/glad/glad.h include/KHR/khrplatform.h)

add_library(glad
	src/glad.c

	${HEADER_FILES}
)

target_include_directories(glad PRIVATE include)
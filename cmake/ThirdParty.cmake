include(FetchContent)
include(ExternalProject)

if (NOT GTest_FOUND)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.11.0
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
endif()

if (NOT FMT_FOUND)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt.git
	GIT_TAG        8.0.1
)
FetchContent_MakeAvailable(fmt)
endif()
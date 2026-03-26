cmake_minimum_required(VERSION 3.16)

project(libgitpp VERSION 0.1.0 LANGUAGES CXX)

if(CMAKE_SOURCE_DIR MATCHES CMAKE_BINARY_DIR)
      message(STATUS "Please do an out-of-tree build:")
      message(STATUS "rm -f CMakeCache.txt && mkdir build && cd build; cmake .. && make")
      message(FATAL_ERROR "In-tree-build detected!")
endif()

include(CMakeDependentOption)

#-----------------------------------------------------------------------------
# BUILD SYSTEM
#-----------------------------------------------------------------------------

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

#-----------------------------------------------------------------------------
# DEPENDENCIES
#-----------------------------------------------------------------------------

set (CMAKE_MODULE_PATH "/usr/local/lib/cmake;/usr/local/lib64/cmake;${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# load the package to obtain information from pkgconfig
# ensure that packages etc. in /usr/local are found
# do NOT use CMAKE_PREFIX_PATH as it is used by qtcreator to select the Qt version
set(ENV{PKG_CONFIG_PATH} "${PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig:/usr/local/lib64/pkgconfig:/usr/local/share/pkgconfig")
find_package(PkgConfig REQUIRED)

# find Lua+SOL2 for scripting
pkg_check_modules(LIBGIT2 IMPORTED_TARGET REQUIRED libgit2)

#-----------------------------------------------------------------------------
# OPTIONS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# COMPILE DEFINITIONS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# BUILD ALL COMPONENTS
#-----------------------------------------------------------------------------

add_subdirectory(src)

include_directories(BEFORE ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(tests)


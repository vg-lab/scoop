cmake_minimum_required( VERSION 3.1 FATAL_ERROR )
project( scoop VERSION 0.1.1 )
set( scoop_VERSION_ABI 1)

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
  message( FATAL "no in source building allowed." )
endif()

list( APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common )

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions( -DDEBUG )
endif( )

include(GitExternal)

set( SCOOP_DESCRIPTION "Scoop - ColoR pAleTtes and mappERs" )
set( COMMON_PROJECT_DOMAIN gmrv.es )


include( Common )
common_find_package(Qt5Gui SYSTEM REQUIRED)
common_find_package(Qt5Widgets SYSTEM REQUIRED)
common_find_package(Boost COMPONENTS unit_test_framework)
common_find_package_post( )

set( SCOOP_DEPENDENT_LIBRARIES Qt5Widgets Qt5Gui )

add_subdirectory( scoop )
add_subdirectory( examples )
# add_subdirectory( tests )

include( CPackConfig )
include( DoxygenRule )

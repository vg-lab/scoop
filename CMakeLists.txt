cmake_minimum_required( VERSION 3.1 FATAL_ERROR )
project( scoop VERSION 0.1.4 )
set( scoop_VERSION_ABI 2)

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
  message( FATAL "no in source building allowed." )
endif()

list( APPEND CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common )

if( NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake )
  message(FATAL_ERROR "CMake/common missing, run: git submodule update --init" )
endif()

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions( -DDEBUG )
endif( )

option( SCOOP_WITH_EXAMPLES "SCOOP_WITH_EXAMPLES" ON )
option( SCOOP_WITH_TESTS "SCOOP_WITH_TESTS" ON )

set( SCOOP_DESCRIPTION "Scoop - ColoR pAleTtes and mappERs" )
set( COMMON_PROJECT_DOMAIN gmrv.es )


include( Common )
common_find_package( Qt5Gui SYSTEM REQUIRED )
common_find_package( Qt5Widgets SYSTEM REQUIRED )
common_find_package( Boost COMPONENTS unit_test_framework )
common_find_package_post( )

set( SCOOP_DEPENDENT_LIBRARIES Qt5Widgets Qt5Gui )

add_subdirectory( scoop )
add_subdirectory( examples )
add_subdirectory( tests )

set( DOCS README.md LICENSE.txt )
install( FILES ${DOCS} DESTINATION share/vmmlib COMPONENT dev )

set( DOXYGEN_MAINPAGE_MD README.md )
set( DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md )
include( DoxygenRule )

include( CPackConfig )
include( CTest )

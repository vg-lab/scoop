include_directories(
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/include
  )

add_compile_options(-fPIC)

set( SCOOPCATEGORICALCOLORMAP_HEADERS )
set( SCOOPCATEGORICALCOLORMAP_SOURCES CategoricalColorMap.cpp )
set( SCOOPCATEGORICALCOLORMAP_LINK_LIBRARIES
	scoop
  )
common_application( scoopCategoricalColorMap )


set( SCOOPSEQUENTIALCOLORMAP_HEADERS )
set( SCOOPSEQUENTIALCOLORMAP_SOURCES SequentialColorMap.cpp )
set( SCOOPSEQUENTIALCOLORMAP_LINK_LIBRARIES
	scoop
  )
common_application( scoopSequentialColorMap )


set( SCOOPCOLORPALETTE_HEADERS )
set( SCOOPCOLORPALETTE_SOURCES ColorPalette.cpp )
set( SCOOPCOLORPALETTE_LINK_LIBRARIES
	scoop
  )
common_application( scoopColorPalette )

if ( SCOOP_WITH_EXAMPLES )

  include_directories(
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/include
    )

  add_compile_options(-fPIC)

  set( SCOOPCATEGORICALCOLORMAP_HEADERS )
  set( SCOOPCATEGORICALCOLORMAP_SOURCES CategoricalColorMap.cpp )
  set( SCOOPCATEGORICALCOLORMAP_LINK_LIBRARIES scoop )
  common_application( scoopCategoricalColorMap )
  list( APPEND SCOOP_EXAMPLES_FILES ${SCOOPCATEGORICALCOLORMAP_SOURCES} )

  set( SCOOPSEQUENTIALCOLORMAP_HEADERS )
  set( SCOOPSEQUENTIALCOLORMAP_SOURCES SequentialColorMap.cpp )
  set( SCOOPSEQUENTIALCOLORMAP_LINK_LIBRARIES scoop )
  common_application( scoopSequentialColorMap )
  list( APPEND SCOOP_EXAMPLES_FILES ${SCOOPSEQUENTIALCOLORMAP_SOURCES} )


  set( SCOOPCOLORPALETTE_HEADERS )
  set( SCOOPCOLORPALETTE_SOURCES ColorPalette.cpp )
  set( SCOOPCOLORPALETTE_LINK_LIBRARIES scoop )
  common_application( scoopColorPalette )
  list( APPEND SCOOP_EXAMPLES_FILES ${SCOOPCOLORPALETTE_SOURCES} )

  include(InstallFiles)
  install_files(share/scoop/examples FILES ${SCOOP_EXAMPLES_FILES} COMPONENT
    examples )

endif( SCOOP_WITH_EXAMPLES )

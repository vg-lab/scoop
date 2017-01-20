source_group(\\ FILES CMakeLists.txt)

set(SCOOP_PUBLIC_HEADERS
  Color.h
  ColorPalette.h
  CategoricalColorMap.h
  SequentialColorMap.h
)

set(SCOOP_HEADERS
)

set(SCOOP_SOURCES
  Color.cpp
  ColorPalette.cpp
  SequentialColorMap.cpp
)

set(SCOOP_LINK_LIBRARIES
  Qt5::Widgets

  )

common_library( scoop )

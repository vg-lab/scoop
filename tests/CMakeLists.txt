if ( SCOOP_WITH_TESTS )

  if (${Boost_FOUND})
    set(TEST_LIBRARIES
      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
      scoop
      ${Qt5Core_LIBRARIES}
      )
    include(CommonCTest)
  endif()

endif( SCOOP_WITH_TESTS )

/*
 * Copyright (c) 2016  VG-Lab/URJC/UPM.
 *
 * Authors: Pablo Toharia <pablo.toharia@upm.es>
 *
 * This file is part of Scoop
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#include <scoop/scoop.h>
#include "scoopTests.h"
#include <math.h>

bool valueSizeMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL( ex.what( ), std::string( "Less than two values provided" ));
  return true;
}

bool valuesAndPaletteSizesMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL(
    ex.what( ), std::string( "Palette and values sizes do not match" ));
  return true;
}


bool interpolationUnknownMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL(
    ex.what( ), std::string( "Interpolation type unknown" ));
  return true;
}

typedef enum
{
  CATEGORY1 = 0,
  CATEGORY2,
  CATEGORY3
} TCategory;

BOOST_AUTO_TEST_CASE( sequentialColorMap )
{
  {
    scoop::SequentialColorMap scm;

    BOOST_CHECK_EQUAL( scm.minValue( ), 0.0f );
    BOOST_CHECK_EQUAL( scm.maxValue( ), 1.0f );
    BOOST_CHECK_EQUAL( scm.getColor( scm.minValue( )),
                       scoop::Color( 0, 0, 0 ));
    BOOST_CHECK_EQUAL( scm.getColor( scm.maxValue( )),
                       scoop::Color( 255, 255, 255 ));
    BOOST_CHECK_EQUAL( scm.getColor( scm.minValue( ) - 1.0f ),
                       scoop::Color( 0, 0, 0 ));
    BOOST_CHECK_EQUAL( scm.getColor( scm.maxValue( ) + 1.0f ),
                       scoop::Color( 255, 255, 255 ));
  }

  {
    scoop::SequentialColorMap scm( 1.0f, scoop::Color( 50, 60, 70 ),
                                   2.0f, scoop::Color( 100, 110, 120 ));

    BOOST_CHECK_EQUAL( scm.minValue( ), 1.0f );
    BOOST_CHECK_EQUAL( scm.maxValue( ), 2.0f );
    BOOST_CHECK_EQUAL( scm.getColor( scm.minValue( )),
                       scoop::Color( 50, 60, 70 ));
    BOOST_CHECK_EQUAL( scm.getColor( scm.maxValue( )),
                       scoop::Color( 100, 110, 120 ));
  }

  {
    scoop::SequentialColorMap scm(
      { 1.0f, 2.0f, 3.0f },
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 ));

    BOOST_CHECK_EQUAL( scm.minValue( ), 1.0f );
    BOOST_CHECK_EQUAL( scm.maxValue( ), 3.0f );
    BOOST_CHECK_EQUAL( scm.getColor( 1.0f ), scoop::Color( "#e0ecf4" ));
    BOOST_CHECK_EQUAL( scm.getColor( 2.0f ), scoop::Color( "#9ebcda" ));
    BOOST_CHECK_EQUAL( scm.getColor( 3.0f ), scoop::Color( "#8856a7" ));

  }

  {
    scoop::SequentialColorMap scm(
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 ),
      1.0f, 3.0f );

    BOOST_CHECK_EQUAL( scm.minValue( ), 1.0f );
    BOOST_CHECK_EQUAL( scm.maxValue( ), 3.0f );
    BOOST_CHECK_EQUAL( scm.getColor( 1.0f ), scoop::Color( "#e0ecf4" ));
    BOOST_CHECK_EQUAL( scm.getColor( 2.0f ), scoop::Color( "#9ebcda" ));
    BOOST_CHECK_EQUAL( scm.getColor( 3.0f ), scoop::Color( "#8856a7" ));

  }

  {
    scoop::SequentialColorMap scm;

    scm.setFromPalette( { 1.0f, 2.0f, 3.0f },
                        scoop::ColorPalette::colorBrewerSequential(
                          scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 ));

    BOOST_CHECK_EQUAL( scm.minValue( ), 1.0f );
    BOOST_CHECK_EQUAL( scm.maxValue( ), 3.0f );
    BOOST_CHECK_EQUAL( scm.getColor( 1.0f ), scoop::Color( "#e0ecf4" ));
    BOOST_CHECK_EQUAL( scm.getColor( 2.0f ), scoop::Color( "#9ebcda" ));
    BOOST_CHECK_EQUAL( scm.getColor( 3.0f ), scoop::Color( "#8856a7" ));

    BOOST_CHECK_EXCEPTION(
      scm.setFromPalette(
        { 1.0f },
        scoop::ColorPalette::colorBrewerSequential(
          scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 )),
      std::runtime_error, valuesAndPaletteSizesMessage );

    BOOST_CHECK_EXCEPTION(
      scm.setFromPalette(
        { 1.0f },
        scoop::ColorPalette::colorBrewerQualitative(
          scoop::ColorPalette::Accent, 1 )),
      std::runtime_error, valueSizeMessage );
  }


  // Simple RGB interpolation
  {
    scoop::Color c1 = scoop::Color( 50, 60, 70 );
    scoop::Color c2 = scoop::Color( 100, 110, 120 );
    scoop::SequentialColorMap scm( 1.0f, c1,
                                   2.0f, c2);

    for ( auto v = 1.0f; v < 2.1f; v += 0.1f )
    {
      BOOST_CHECK_EQUAL(
        scm.getColor( v ),
        scoop::Color( c1.red( ) + ( c2.red( ) - c1.red( )) * ( v - 1.0f ),
                      c1.green( ) + ( c2.green( ) - c1.green( )) * ( v - 1.0f ),
                      c1.blue( ) + ( c2.blue( ) - c1.blue( )) * ( v - 1.0f )));
    }
  }

  // Simple HSV interpolation
  {
    scoop::Color c1, c2;
    c1.setHsv( 50, 60, 70 );
    c2.setHsv( 100, 110, 120 );
    scoop::SequentialColorMap scm( 1.0f, c1, 2.0f, c2 );

    int h1, s1, v1;
    c1.getHsv( &h1, &s1, &v1 );

    int h2, s2, v2;
    c2.getHsv( &h2, &s2, &v2 );

    for ( auto val = 1.0f; val < 2.1f; val += 0.1f )
    {
      auto color = scm.getColor( val,
                                 scoop::SequentialColorMap::HSV_INTERPOLATION );
      int h, s, v;
      color.getHsv( &h, &s, &v );

      BOOST_CHECK( fabs( h - ( h1 + ( h2 - h1 ) * ( val - 1.0f ))) < 0.1f );
      BOOST_CHECK( fabs( s - ( s1 + ( s2 - s1 ) * ( val - 1.0f ))) < 0.1f );
      BOOST_CHECK( fabs( v - ( v1 + ( v2 - v1 ) * ( val - 1.0f ))) < 0.1f );
    }
  }

  // Unknown interpolation
  {
    scoop::SequentialColorMap scm;
    BOOST_CHECK_EXCEPTION(
      scm.getColor( 0.5f, scoop::SequentialColorMap::ColorInterpolation( -10 )),
      std::runtime_error, interpolationUnknownMessage );
  }
}

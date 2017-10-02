/*
 * Copyright (c) 2016 GMRV/URJC/UPM.
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


BOOST_AUTO_TEST_CASE( emptyPalette )
{
  scoop::ColorPalette p;

  auto& colors = p.colors( );
  const auto& colorsConst = p.colors( );

  BOOST_CHECK_EQUAL( colors.size( ), 0 );
  BOOST_CHECK_EQUAL( colorsConst.size( ), 0 );
  BOOST_CHECK_EQUAL( p.size( ), 0 );
}


bool paletteSizeInvalidMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL( ex.what( ), std::string( "Palette size invalid" ));
  return true;
}

BOOST_AUTO_TEST_CASE( colorBrewerSequential )
{

  for ( auto reverse : { true, false } )
  {
    for ( auto name : { scoop::ColorPalette::BuGn,  scoop::ColorPalette::BuPu,
          scoop::ColorPalette::GnBu, scoop::ColorPalette::OrRd,
          scoop::ColorPalette::PuBu, scoop::ColorPalette::PuBuGn,
          scoop::ColorPalette::PuRd, scoop::ColorPalette::RdPu,
          scoop::ColorPalette::YlGn, scoop::ColorPalette::YlGnBu,
          scoop::ColorPalette::YlOrBr, scoop::ColorPalette::YlOrRd,
          scoop::ColorPalette::Blues, scoop::ColorPalette::Greens,
          scoop::ColorPalette::Greys, scoop::ColorPalette::Oranges,
          scoop::ColorPalette::Purples, scoop::ColorPalette::Reds } )
    {

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerSequential( name, 2, reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerSequential( name, 10, reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      for ( auto i = 3; i < 10; ++i )
      {
        auto p =
          scoop::ColorPalette::colorBrewerSequential( name, i, reverse );
        BOOST_CHECK_EQUAL( p.size( ), i );
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( colorBrewerDiverging )
{
  for ( auto reverse : { true, false } )
  {
    for ( auto name : { scoop::ColorPalette::BrBG, scoop::ColorPalette::PiYG,
          scoop::ColorPalette::PRGn, scoop::ColorPalette::PurOr,
          scoop::ColorPalette::RdBu, scoop::ColorPalette::RdGy,
          scoop::ColorPalette::RdYlBu, scoop::ColorPalette::RdYlGn,
          scoop::ColorPalette::Spectral })
    {

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerDiverging( name, 2, reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerDiverging( name, 12, reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      for ( auto i = 3; i < 12; ++i )
      {
        auto p =
          scoop::ColorPalette::colorBrewerDiverging( name, i, reverse );
        BOOST_CHECK_EQUAL( p.size( ), i );
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( colorBrewerQualitative )
{
  const unsigned int cbQualitativeSizes[8] =
    {
      8,  // Accent
      8,  // Dark2
      12, // Paired
      9,  // Pastel1
      8,  // Pastel2
      9,  // Set1
      9,  // Set2
      12, // Set3
    };

  for ( auto reverse : { true, false } )
  {
    for ( auto name : { scoop::ColorPalette::Accent, scoop::ColorPalette::Dark2,
          scoop::ColorPalette::Paired, scoop::ColorPalette::Pastel1,
          scoop::ColorPalette::Pastel2, scoop::ColorPalette::Set1,
          scoop::ColorPalette::Set2, scoop::ColorPalette::Set3 })
    {

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerQualitative(
          name, 0,reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      BOOST_CHECK_EXCEPTION(
        scoop::ColorPalette::colorBrewerQualitative(
          name, cbQualitativeSizes[name] + 1, reverse ),
        std::runtime_error, paletteSizeInvalidMessage );

      for ( unsigned int i = 1; i < cbQualitativeSizes[name] + 1; ++i )
      {
        auto p =
          scoop::ColorPalette::colorBrewerQualitative( name, i, reverse );
        BOOST_CHECK_EQUAL( p.size( ), i );
      }
    }
  }
}

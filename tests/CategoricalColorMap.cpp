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

bool nonExistingCategoryMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL( ex.what( ), std::string( "Category does not exist." ));
  return true;
}

bool categoriesAndPaletteSizesMessage( const std::runtime_error& ex )
{
  BOOST_CHECK_EQUAL(
    ex.what( ), std::string( "Palette and categories sizes do not match" ));
  return true;
}

typedef enum
{
  CATEGORY1 = 0,
  CATEGORY2,
  CATEGORY3
} TCategory;

BOOST_AUTO_TEST_CASE( emptyCategoricalColorMap )
{
  scoop::CategoricalColorMap<> ccm;

  BOOST_CHECK_EXCEPTION( ccm.getColor( 0 ),
                         std::runtime_error, nonExistingCategoryMessage );

  scoop::CategoricalColorMap< TCategory > ccm2;

  BOOST_CHECK_EXCEPTION( ccm2.getColor( CATEGORY1 ),
                         std::runtime_error, nonExistingCategoryMessage );

  scoop::CategoricalColorMap< std::string,
                              std::hash< std::string >> ccm3;

  BOOST_CHECK_EXCEPTION( ccm3.getColor( "test" ),
                         std::runtime_error, nonExistingCategoryMessage );
}


BOOST_AUTO_TEST_CASE( categoricalColorMap )
{
  scoop::Color color( 50, 100, 150 );

  scoop::CategoricalColorMap<> ccm;
  ccm.setColor( 1, color );
  BOOST_CHECK_EQUAL( ccm.getColor( 1 ), color );
  BOOST_CHECK_EXCEPTION( ccm.getColor( 0 ),
                         std::runtime_error, nonExistingCategoryMessage );

  scoop::CategoricalColorMap< TCategory > ccm2;
  ccm2.setColor( CATEGORY1, color );
  BOOST_CHECK_EQUAL( ccm2.getColor( CATEGORY1 ), color );
  BOOST_CHECK_EXCEPTION( ccm2.getColor( CATEGORY2 ),
                         std::runtime_error, nonExistingCategoryMessage );

  scoop::CategoricalColorMap< std::string,
                              std::hash< std::string >> ccm3;
  ccm3.setColor( "test", color );
  BOOST_CHECK_EQUAL( ccm3.getColor( "test" ), color );
  BOOST_CHECK_EXCEPTION( ccm3.getColor( std::string( "test2" )),
                         std::runtime_error, nonExistingCategoryMessage );

  BOOST_CHECK_EXCEPTION(
      scoop::CategoricalColorMap< TCategory > ccm4(
    { CATEGORY1, CATEGORY2 },
    scoop::ColorPalette::colorBrewerSequential(
      scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 )),
      std::runtime_error, categoriesAndPaletteSizesMessage );

  scoop::CategoricalColorMap< TCategory > ccm5(
    { CATEGORY1, CATEGORY2, CATEGORY3 },
    scoop::ColorPalette::colorBrewerSequential(
      scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 ));

  BOOST_CHECK_EQUAL( ccm5.getColor( CATEGORY1 ), scoop::Color( "#e0ecf4" ));
  BOOST_CHECK_EQUAL( ccm5.getColor( CATEGORY2 ), scoop::Color( "#9ebcda" ));
  BOOST_CHECK_EQUAL( ccm5.getColor( CATEGORY3 ), scoop::Color( "#8856a7" ));

}

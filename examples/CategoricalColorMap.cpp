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
#include <iostream>


int main ( void )
{
  typedef enum
  {
    CATEGORY1 = 0,
    CATEGORY2,
    CATEGORY3
  } TCategory;

  {
    // enum-based categories
    scoop::CategoricalColorMap< TCategory > categoricalColorMap;

    // establish category-colo mappings
    categoricalColorMap.setColor( CATEGORY1, scoop::Color( 255, 0, 0 ));
    categoricalColorMap.setColor( CATEGORY2, scoop::Color( 0, 255, 0 ));
    categoricalColorMap.setColor( CATEGORY3, scoop::Color( 0, 0, 255 ));

    // get color mappings
    const auto& color = categoricalColorMap.getColor( CATEGORY2 );
    std::cout << color << std::endl;
  }
  {
    // creating a colormap from a palette
    scoop::ColorPalette cp =
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 );
    scoop::CategoricalColorMap< TCategory > categoricalColorMap(
      { CATEGORY1, CATEGORY2, CATEGORY3 }, cp );

    // get color mappings
    const auto& color = categoricalColorMap.getColor( CATEGORY2 );
    std::cout << color << std::endl;
  }

  // int-based categories
  scoop::CategoricalColorMap< int > categoricalColorMap3;

  // string-based categories
  scoop::CategoricalColorMap< std::string,
                              std::hash< std::string >> categoricalColorMap4;

  return 0;
}

/*
 * Copyright (c) 2016 GMRV/URJC/UPM.
 *
 * Authors: Pablo Toharia <pablo.toharia@upm.es>
 *
 * This file is part of scoop
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
#include "ColorPalette.h"
#include "ColorBrewerPalettes.h"
#include <iostream>

namespace scoop
{
  const ColorPalette::Colors& ColorPalette::colors( void ) const
  {
    return _colors;
  };

  ColorPalette::Colors& ColorPalette::colors( void )
  {
    return _colors;
  };

  unsigned int ColorPalette::size( void )
  {
    return ( unsigned int ) _colors.size( );
  }

  ColorPalette ColorPalette::colorBrewerSequential(
    ColorBrewerSequential cbPalette,
    unsigned int size,
    bool reverse )
  {
    if ( size > 9 || size < 3 )
      throw std::runtime_error( "Palette size invalid" );

    ColorPalette palette;
    auto stringifiedPalette = cbSequential[ cbPalette ];
    auto& colors = palette.colors( );
    colors.reserve( size );
    for ( unsigned int i = 0; i < size; ++i )
      colors.push_back( Color( stringifiedPalette[size-3][i] ));

    if ( reverse )
      std::reverse( colors.begin( ), colors.end( ));

    return palette;
  }

  ColorPalette ColorPalette::colorBrewerDiverging(
    ColorBrewerDiverging cbPalette,
    unsigned int size,
    bool reverse )
  {
    if ( size > 11 || size < 3 )
      throw std::runtime_error( "Palette size invalid" );

    ColorPalette palette;
    auto stringifiedPalette = cbDiverging[ cbPalette ];
    auto& colors = palette.colors( );
    colors.reserve( size );
    for ( unsigned int i = 0; i < size; ++i )
      colors.push_back( Color( stringifiedPalette[size-3][i] ));

    if ( reverse )
      std::reverse( colors.begin( ), colors.end( ));

    return palette;
  }

  ColorPalette ColorPalette::colorBrewerQualitative(
    ColorBrewerQualitative cbPalette,
    unsigned int size,
    bool reverse )
  {
    if ( size > cbQualitativeSizes[cbPalette] || size < 3 )
      throw std::runtime_error( "Palette size invalid" );

    ColorPalette palette;
    auto stringifiedPalette = cbQualitative[cbPalette];
    auto& colors = palette.colors( );
    colors.reserve( size );
    for ( unsigned int i = 0; i < size; ++i )
      colors.push_back( Color( stringifiedPalette[size-3][i] ));

    if ( reverse )
      std::reverse( colors.begin( ), colors.end( ));

    return palette;
  }

}

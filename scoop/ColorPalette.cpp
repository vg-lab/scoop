/*
 * Copyright (c) 2016  VG-Lab/URJC/UPM.
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
#include "MatplotlibPalettes.h"
#include <iostream>

namespace scoop
{
  const ColorPalette::Colors& ColorPalette::colors( void ) const
  {
    return _colors;
  }

  ColorPalette::Colors& ColorPalette::colors( void )
  {
    return _colors;
  }

  unsigned int ColorPalette::size( void ) const
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
    {
      colors.push_back( Color( stringifiedPalette[size-3][i] ));
    }

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
    if ( size > cbQualitativeSizes[cbPalette] || size == 0 )
      throw std::runtime_error( "Palette size invalid" );

    ColorPalette palette;
    auto stringifiedPalette = cbQualitative[cbPalette];
    auto& colors = palette.colors( );
    colors.reserve( size );
    for ( unsigned int i = 0; i < size; ++i )
      colors.push_back( Color( stringifiedPalette[i] ));

    if ( reverse )
      std::reverse( colors.begin( ), colors.end( ));

    return palette;
  }

#define __CREATE_MPL_COLOR_VECTOR__( __NAME__ )                         \
  for ( int i = ( reverse ? 255 : 0 );                         \
        i != ( reverse ? -1 : 256 ); ( reverse ? --i : ++i ))            \
    colors.emplace_back( Color::fromRgbF( __NAME__[i][0] , __NAME__[i][1], __NAME__[i][2] ));

  ColorPalette ColorPalette::matplotlibPerceptualUniform(
    MatplotlibPerceptualUniform mplPalette,
    bool reverse )
  {
    ColorPalette palette;
    auto& colors = palette.colors( );
    colors.reserve( 256 );

    switch ( mplPalette )
    {
    case MatplotlibPerceptualUniform::Viridis:
      __CREATE_MPL_COLOR_VECTOR__( mplViridis );
      break;
    case MatplotlibPerceptualUniform::Magma:
      __CREATE_MPL_COLOR_VECTOR__( mplMagma );
      break;
    case MatplotlibPerceptualUniform::Plasma:
      __CREATE_MPL_COLOR_VECTOR__( mplPlasma );
      break;
    case MatplotlibPerceptualUniform::Inferno:
      __CREATE_MPL_COLOR_VECTOR__( mplInferno );
      break;
    default:
      throw std::runtime_error( "mpl color palette unknown" );
    }


    return palette;
  }

}

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

  const char* cbBuGn[][9] =
  {{ "#2ca25f", "#e5f5f9" },
   { "#2ca25f", "#99d8c9", "#e5f5f9" },
   { "#238b45", "#66c2a4", "#b2e2e2", "#edf8fb" },
   { "#006d2c", "#2ca25f", "#66c2a4", "#b2e2e2", "#edf8fb" },
   { "#006d2c", "#2ca25f", "#66c2a4", "#99d8c9", "#ccece6", "#edf8fb" },
   { "#005824", "#238b45", "#41ae76", "#66c2a4", "#99d8c9", "#ccece6",
     "#edf8fb" },
   { "#005824", "#238b45", "#41ae76", "#66c2a4", "#99d8c9", "#ccece6",
     "#e5f5f9", "#f7fcfd" },
   { "#00441b", "#006d2c", "#238b45", "#41ae76", "#66c2a4", "#99d8c9",
     "#ccece6", "#e5f5f9", "#f7fcfd" }};

  const char* cbBuPu[][9] =
  {{ "#8856a7", "#e0ecf4"},
   { "#8856a7", "#9ebcda", "#e0ecf4"},
   { "#88419d", "#8c96c6", "#b3cde3", "#edf8fb"},
   { "#810f7c", "#8856a7", "#8c96c6", "#b3cde3", "#edf8fb"},
   { "#810f7c", "#8856a7", "#8c96c6", "#9ebcda", "#bfd3e6", "#edf8fb"},
   { "#6e016b", "#88419d", "#8c6bb1", "#8c96c6", "#9ebcda", "#bfd3e6",
     "#edf8fb"},
   { "#6e016b", "#88419d", "#8c6bb1", "#8c96c6", "#9ebcda", "#bfd3e6",
     "#e0ecf4", "#f7fcfd"},
   { "#4d004b", "#810f7c", "#88419d", "#8c6bb1", "#8c96c6", "#9ebcda",
     "#bfd3e6", "#e0ecf4", "#f7fcfd"}};

  ColorPalette ColorPalette::colorBrewerSequential(
    ColorBrewerSequential cbPalette,
    unsigned int size )
  {
    // char (*p)[][7][9];
    if ( size > 9 || size < 2 )
      throw std::runtime_error( "Palette size invalid" );

    ColorPalette palette;
    auto stringifiedPalette = cbBuGn;
    if ( cbPalette == ColorBrewerSequential::BuGn )
      stringifiedPalette = cbBuGn;
    else if ( cbPalette == ColorBrewerSequential::BuPu )
      stringifiedPalette = cbBuPu;
    else
      throw std::runtime_error( "Unknown palette" );
    auto& colors = palette.colors( );
    colors.reserve( size );
    for ( unsigned int i = 0; i < size; ++i )
      colors.push_back( Color( stringifiedPalette[size-2][i] ));
    return palette;
  }
}

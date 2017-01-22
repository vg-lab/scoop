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
#ifndef __SCOOP__COLOR_PALETTE__
#define __SCOOP__COLOR_PALETTE__

#include "Color.h"
#include <scoop/api.h>
#include <vector>

namespace scoop
{
  class ColorPalette
  {
  public:

    typedef std::vector< Color > Colors;

    typedef enum
    {
      BuGn = 0, BuPu, GnBu, OrRd, PuBu, PuBuGn,
      PuRd, RdPu, YlGn, YlGnBu, YlOrBr, YlOrRd,
      Blues, Greens, Greys, Oranges, Purples, Reds
    } ColorBrewerSequential;

    typedef enum
    {
      BrBG, PiYG, PRGn, PurOr,
      RdBu, RdGy, RdYlBu, RdYlGn, Spectral
    } ColorBrewerDiverging;

    typedef enum
    {
      Accent, Dark2, Paired, Pastel1,
      Pastel2, Set1, Set2, Set3,
    } ColorBrewerQualitative;

    SCOOP_API const Colors& colors( void ) const;
    SCOOP_API Colors& colors( void );
    SCOOP_API unsigned int size( void ) const;

    SCOOP_API static ColorPalette colorBrewerSequential(
      ColorBrewerSequential cbPalette = ColorBrewerSequential::BuGn,
      unsigned int size = 3, bool reverse = true );
    SCOOP_API static ColorPalette colorBrewerDiverging(
      ColorBrewerDiverging cbPalette = ColorBrewerDiverging::BrBG,
      unsigned int size = 3, bool reverse = true );
    SCOOP_API static ColorPalette colorBrewerQualitative(
      ColorBrewerQualitative cbPalette = ColorBrewerQualitative::Accent,
      unsigned int size = 3, bool reverse = false );

    protected:
    std::vector< Color > _colors;
  };
}

#endif

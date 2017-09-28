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
  /** Class for color palette
   *
   *  A color palette is simply a container of Color objects
   */
  class ColorPalette
  {
  public:

    //! Container of color objects
    typedef std::vector< Color > Colors;

    //! Possible ColorBrewer sequential color palette names
    typedef enum
    {
      BuGn = 0, BuPu, GnBu, OrRd, PuBu, PuBuGn,
      PuRd, RdPu, YlGn, YlGnBu, YlOrBr, YlOrRd,
      Blues, Greens, Greys, Oranges, Purples, Reds
    } ColorBrewerSequential;

    //! Possible ColorBrewer diverging color palette names
    typedef enum
    {
      BrBG, PiYG, PRGn, PurOr,
      RdBu, RdGy, RdYlBu, RdYlGn, Spectral
    } ColorBrewerDiverging;

    //! Possible ColorBrewer qualitative color palette names
    typedef enum
    {
      Accent, Dark2, Paired, Pastel1,
      Pastel2, Set1, Set2, Set3,
    } ColorBrewerQualitative;

    /**
     * Returns the container of colors of the palette
     *
     * @returns a const reference to the container
    */
    SCOOP_API const Colors& colors( void ) const;

    /**
     * Returns the container of colors of the palette
     *
     * @returns a copy of the colors in the container
    */
    SCOOP_API Colors& colors( void );

    /**
     * Returns the size of the palette
     *
     * @returns the number of colors of the palette
    */
    SCOOP_API unsigned int size( void ) const;

    /**
     * Static method to create a palette based on ColorBrewer's sequential
     * palettes
     *
     * @param[in] cbPalette: the name of the ColorBrewer's sequential pelette
     * @param[in] size: the size of the palette. Size must be between 3 and 9.
     * @param[in] reverse: if the palette is created backwards
     * @returns the color palette
    */
    SCOOP_API static ColorPalette colorBrewerSequential(
      ColorBrewerSequential cbPalette = ColorBrewerSequential::BuGn,
      unsigned int size = 3, bool reverse = true );

    /**
     * Static method to create a palette based on ColorBrewer's diverging
     * palettes
     *
     * @param[in] cbPalette: the name of the ColorBrewer's diverging pelette
     * @param[in] size: the size of the palette. Size must be between 3 and 11
     * @param[in] reverse: if the palette is created backwards
     * @returns the color palette
    */
    SCOOP_API static ColorPalette colorBrewerDiverging(
      ColorBrewerDiverging cbPalette = ColorBrewerDiverging::BrBG,
      unsigned int size = 3, bool reverse = true );

    /**
     * Static method to create a palette based on ColorBrewer's qualitative
     * palettes
     *
     * @param[in] cbPalette: the name of the ColorBrewer's qualitative pelette
     * @param[in] size: the size of the palette. Size must be 3 or greater and
     *                  lower than the number of colors available for the palette
     *                  chosen.
     * @param[in] reverse: if the palette is created backwards
     * @returns the color palette
    */
    SCOOP_API static ColorPalette colorBrewerQualitative(
      ColorBrewerQualitative cbPalette = ColorBrewerQualitative::Accent,
      unsigned int size = 3, bool reverse = false );

    protected:

    //! Container of the colors in the palette
    Colors _colors;
  };
}

#endif

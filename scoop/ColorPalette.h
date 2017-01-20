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
      BuGn,
      BuPu
    } ColorBrewerSequential;

    SCOOP_API const Colors& colors( void ) const;
    SCOOP_API Colors& colors( void );
    SCOOP_API unsigned int size( void );
    SCOOP_API static ColorPalette colorBrewerSequential(
      ColorBrewerSequential cbPalette = ColorBrewerSequential::BuGn,
      unsigned int size = 3 );

    protected:
    std::vector< Color > _colors;
  };
}

#endif

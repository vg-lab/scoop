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
#ifndef __SCOOP__SEQUENTIALCOLORMAP__
#define __SCOOP__SEQUENTIALCOLORMAP__

#include "Color.h"
#include "ColorPalette.h"
#include <scoop/api.h>
#include <vector>
#include <map>

namespace scoop
{
  class SequentialColorMap
  {
  public:
    SCOOP_API
    SequentialColorMap( float minValue_ = 0.f,
                        const Color& minColor = Color( 0, 0, 0 ),
                        float maxValue_ = 1.f,
                        const Color& maxColor = Color( 255, 255, 255 ));
    SCOOP_API
    SequentialColorMap( std::vector< float > values,
                        ColorPalette palette );

    SCOOP_API void setMinValue( const float minValue_ );
    SCOOP_API void setMaxValue( const float maxValue_ );
    SCOOP_API float minValue( void );
    SCOOP_API float maxValue( void );
    SCOOP_API void addColor( const float value, const Color& color );
    SCOOP_API Color getColor( const float value ) const;

  protected:

    Color _hsvInterpolation( const Color& color1,
                             const Color& color2,
                             float normDist ) const;
    float _minValue;
    float _maxValue;
    std::map< float, Color > _valuesToColors;
  };


} // namespace scoop

#endif

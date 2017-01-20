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
#include "SequentialColorMap.h"
#include <cmath>
#include <map>
#include <stdexcept>

namespace scoop
{
  SequentialColorMap::SequentialColorMap( float minValue_,
                                          const Color& minColor,
                                          float maxValue_,
                                          const Color& maxColor )
    : _minValue( minValue_ )
    , _maxValue( maxValue_ )
  {
    _valuesToColors[ minValue_ ] = minColor;
    _valuesToColors[ maxValue_ ] = maxColor;
  }

  SequentialColorMap::SequentialColorMap( std::vector< float > values,
                                          ColorPalette palette )
  {
    if ( values.size( ) != palette.size( ))
      throw std::runtime_error( "Palette and values sizes do not match" );
    if ( values.size( ) < 2 )
      throw std::runtime_error( "Provide at least 2 values" );

    // Assuming values are sorted
    _minValue = values[0];
    _maxValue = values[values.size( )-1];

    const auto& colors = palette.colors( );
    for ( unsigned int i = 0; i < values.size( ); ++i )
      addColor( values[i], colors[i] );

  }

  void SequentialColorMap::setMinValue( const float minValue_ )
  {
    _minValue = minValue_;
  }

  void SequentialColorMap::setMaxValue( const float maxValue_ )
  {
    _maxValue = maxValue_;
  }

  float SequentialColorMap::minValue( void )
  {
    return _minValue;
  }

  float SequentialColorMap::maxValue( void )
  {
    return _maxValue;
  }

  void SequentialColorMap::addColor( const float value, const Color& color )
  {
    _valuesToColors[ value ] = color;
  }

  Color SequentialColorMap::getColor( const float value ) const
  {
    if ( _valuesToColors.size( ) < 2 )
      throw( std::runtime_error( "SequentialColorMap with "
                                 "not enough values" ));
    // Case with value outside range
    if ( value < _minValue )
      return _valuesToColors.at( _minValue );

    if ( value > _maxValue )
      return _valuesToColors.at( _maxValue );

    // Case where value exists
    {
      const auto& valueColorPair = _valuesToColors.find( value );
      if ( valueColorPair != _valuesToColors.end( ))
      {
        return valueColorPair->second;
      }
    }

    // Case of interpolation
    {
      // Find nearest values
      float nearestSmallerValue = 0.;
      float nearestGreaterValue = 0.;
      auto previousValue = _valuesToColors.begin( )->first;
      for ( const auto& valueColorPair : _valuesToColors )
      {
        if ( previousValue < value &&
             valueColorPair.first > value )
        {
          nearestSmallerValue = previousValue;
          nearestGreaterValue = valueColorPair.first;
          break;
        }
        else
        {
          previousValue = valueColorPair.first;
        }
      }

      // Interpolate color
      return _hsvInterpolation(
        _valuesToColors.at( nearestSmallerValue ),
        _valuesToColors.at( nearestGreaterValue ),
        ( value - nearestSmallerValue ) /
        ( nearestGreaterValue - nearestSmallerValue ));
    }
  }

  // Based on http://www.alanzucconi.com/2016/01/06/colour-interpolation/2/
  Color SequentialColorMap::_hsvInterpolation( const Color& color1,
                                               const Color& color2,
                                               float normDist ) const
  {
    if ( normDist > 1.f && normDist < 0.f )
      throw( std::runtime_error( "normDist outside [0,1] range" ));

    double h1, s1, v1, a1;
    double h2, s2, v2, a2;
    color1.getHsvF( &h1, &s1, &v1, &a1 );
    color2.getHsvF( &h2, &s2, &v2, &a2 );

    double newHue = 0.;
    double hueDist = h2 - h1;
    if ( h1 > h2 )
    {
      // Swap hues
      std::swap( h1, h2 );
      hueDist = -hueDist;
      normDist = 1 - normDist;
    }

    if ( hueDist > 0.5 ) // 180deg
    {
      h1 += 1; // 360deg
      float integralPart;
      newHue = std::modf(( h1 + normDist * ( h2 - h1)),
                         &integralPart ); // % 1; // 360deg
    }
    else if ( hueDist <= 0.5 ) // 180deg
    {
      newHue = h1 + normDist * hueDist;
    }

    Color color;
    color.setHsvF( newHue,
                   s1 + normDist * ( s2 - s1 ),
                   v1 + normDist * ( v2 - v1 ),
                   a1 + normDist * ( a2 - a1 ));
    return color;
  }


} // namespace scoop

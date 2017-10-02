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
#include <iostream>

namespace scoop
{
  SequentialColorMap::SequentialColorMap( float minValue_,
                                          const Color& minColor,
                                          float maxValue_,
                                          const Color& maxColor )
  {
    _valuesToColors[ minValue_ ] = minColor;
    _valuesToColors[ maxValue_ ] = maxColor;
  }

  SequentialColorMap::SequentialColorMap( const std::vector< float >& values,
                                          const ColorPalette& palette )
  {
    this->setFromPalette( values, palette );
  }

  SequentialColorMap::SequentialColorMap(
    const ColorPalette& palette,
    float minValue_ , float maxValue_ )
  {
    std::vector< float > values;
    values.reserve( palette.size( ));
    auto delta = ( maxValue_ - minValue_ ) / ( palette.size( ) - 1 );
    for ( unsigned int i = 0; i < palette.size( ); ++i )
      values.push_back( minValue_ + i * delta );
    this->setFromPalette( values, palette );
  }

  float SequentialColorMap::minValue( void ) const
  {
    return _valuesToColors.begin( )->first;
  }

  float SequentialColorMap::maxValue( void ) const
  {
    return _valuesToColors.rbegin( )->first;
  }

  void SequentialColorMap::setFromPalette( const std::vector< float >& values,
                                           const ColorPalette& palette )
  {
    if ( values.size( ) != palette.size( ))
      throw std::runtime_error( "Palette and values sizes do not match" );
    if ( values.size( ) < 2 )
      throw std::runtime_error( "Less than two values provided" );

    _valuesToColors.clear( );

    const auto& colors = palette.colors( );
    for ( unsigned int i = 0; i < values.size( ); ++i )
      addColor( values[i], colors[i] );
  }

  void SequentialColorMap::addColor( const float value, const Color& color )
  {
    _valuesToColors[ value ] = color;
  }

  Color SequentialColorMap::getColor(
    const float value,
    const ColorInterpolation interpolation ) const
  {

    // Case with value outside range
    if ( value < minValue( ))
      return _valuesToColors.at( minValue( ));

    if ( value > maxValue( ))
      return _valuesToColors.at( maxValue( ));

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
      if ( interpolation == RGB_INTERPOLATION )
        return _rgbInterpolation(
          _valuesToColors.at( nearestSmallerValue ),
          _valuesToColors.at( nearestGreaterValue ),
          ( value - nearestSmallerValue ) /
          ( nearestGreaterValue - nearestSmallerValue ));
      else if ( interpolation == HSV_INTERPOLATION )
        return _hsvInterpolation(
          _valuesToColors.at( nearestSmallerValue ),
          _valuesToColors.at( nearestGreaterValue ),
          ( value - nearestSmallerValue ) /
          ( nearestGreaterValue - nearestSmallerValue ));
      else
        throw std::runtime_error( "Interpolation type unknown" );

      return Color( );
    }
  }

  Color SequentialColorMap::_rgbInterpolation( const Color& color1,
                                               const Color& color2,
                                               float normDist ) const
  {
    return Color(
      color1.red( ) + normDist * ( color2.red( ) - color1.red( )),
      color1.green( ) + normDist * ( color2.green( ) - color1.green( )),
      color1.blue( ) + normDist * ( color2.blue( ) - color1.blue( )),
      color1.alpha( ) + normDist * ( color2.alpha( ) - color1.alpha( )));
  }

  // Based on http://www.alanzucconi.com/2016/01/06/colour-interpolation/2/
  Color SequentialColorMap::_hsvInterpolation( const Color& color1,
                                               const Color& color2,
                                               float normDist ) const
  {

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

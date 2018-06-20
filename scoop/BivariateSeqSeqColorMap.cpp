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
#include "BivariateSeqSeqColorMap.h"
#include <cmath>
#include <iostream>

namespace scoop
{

  BivariateSeqSeqColorMap::BivariateSeqSeqColorMap(
    BivariateSeqSeqColorMapCont valuesToColors_ )
    : _valuesToColors{ valuesToColors_ }
  {
  }


  float BivariateSeqSeqColorMap::minValueX( void ) const
  {
    float minValX = std::numeric_limits< float >::max( );
    for ( const auto& valuesColorPair : _valuesToColors )
      minValX = std::min( minValX, valuesColorPair.first.first );
    return minValX;
  }

  float BivariateSeqSeqColorMap::maxValueX( void ) const
  {
    float maxValX = std::numeric_limits< float >::min( );
    for ( const auto& valuesColorPair : _valuesToColors )
      maxValX = std::max( maxValX, valuesColorPair.first.first );
    return maxValX;
  }

    float BivariateSeqSeqColorMap::minValueY( void ) const
  {
    float minValY = std::numeric_limits< float >::max( );
    for ( const auto& valuesColorPair : _valuesToColors )
      minValY = std::min( minValY, valuesColorPair.first.second );
    return minValY;
  }

  float BivariateSeqSeqColorMap::maxValueY( void ) const
  {
    float maxValY = std::numeric_limits< float >::min( );
    for ( const auto& valuesColorPair : _valuesToColors )
      maxValY = std::max( maxValY, valuesColorPair.first.second );
    return maxValY;
  }


  Color BivariateSeqSeqColorMap::getColor(
    const float  value1,
    const float value2,
    const SequentialColorMap::ColorInterpolation // interpolation
    ) const
  {

    std::cout << "num values to color: " << _valuesToColors.size( ) << std::endl;

    float minX = minValueX( );
    float maxX = maxValueX( );
    float minY = minValueY( );
    float maxY = maxValueY( );

    float vX = qBound( minX, value1, maxX );
    float vY = qBound( minY, value2, maxY );

    // Case where value exists
    {
      const auto& valueColorPair = _valuesToColors.find( { vX, vY} );
      if ( valueColorPair != _valuesToColors.end( ))
      {
        std::cout << "Found!" << std::endl;
        std::cout << valueColorPair->first.first << " " << valueColorPair->first.second << std::endl;
        return valueColorPair->second;
      }
    }

    // Case of interpolation
    {
      // nearestSmallerX = minX;
      // nearestGreatestX = maxX;
      // nearestSmallerY = minY;
      // nearestGreatestY = maxY;
      float mindistQuad[4] =
        {
          std::numeric_limits< float >::max( ),
          std::numeric_limits< float >::max( ),
          std::numeric_limits< float >::max( ),
          std::numeric_limits< float >::max( )
        };// = std::numeric_limits< float >::max( );
      // float mindistQ2 = std::numeric_limits< float >::max( );
      // float mindistQ3 = std::numeric_limits< float >::max( );
      // float mindistQ4 = std::numeric_limits< float >::max( );
      // for ( auto i = 0; i < 4; ++i ) mindistQ4[i] = 

      float qx[4] = { maxX, minX, minX, maxX };
      float qy[4] = { minY, minY, maxY, maxY };
      // qx[0] = maxX, q1y = minY;
      // qx[1] = minX, q2y = minY;
      // qx[2] = minX, q3y = maxY;
      // qx[3] = maxX, q4y = maxY;

      static const float degrees90inRadians = 90 * float( M_PI ) / 180.0f;
      std::cout << "num values to color: " << _valuesToColors.size( ) << std::endl;
      for ( const auto& valuesColorPair : _valuesToColors )
      {
        auto angle =
          std::atan2( valuesColorPair.first.second - vY,
                      valuesColorPair.first.first - vX );
        auto dist =
          std::sqrt(( valuesColorPair.first.second - vY ) *
                    ( valuesColorPair.first.second - vY ) +
                    ( valuesColorPair.first.first - vX ) *
                    ( valuesColorPair.first.first - vX ));

        std::cout << "new value: " << valuesColorPair.first.first
                  << " " << valuesColorPair.first.second << " "
                  << vX << " " << vY
                  << std::endl;
        std::cout << dist << " " << angle << std::endl;

#define Q1 0
#define Q2 1
#define Q3 2
#define Q4 3

        // Q1 [ -0, -90 ]
        // Q2 [ -90, -180 ]
        // Q3 [ 90, 180 ]
        // Q4 [ 0, 90 ]

        int quad;
        quad = ( angle <= 0 ?
                 (( angle >= -degrees90inRadians ) ? Q1 : Q2 ) :
                 (( angle >= degrees90inRadians ) ? Q3 : Q4 ));

        std::cout << "Q" << quad+1 << std::endl;

        if ( dist < mindistQuad[ quad ] )
        {
          mindistQuad[ quad ] = dist;
          qx[ quad ] = valuesColorPair.first.first;
          qy[ quad ] = valuesColorPair.first.second;
        }
      }

      std::cout << "Q1 : " << qx[0] << " " << qy[0] << std::endl;
      std::cout << "Q2 : " << qx[1] << " " << qy[1] << std::endl;
      std::cout << "Q3 : " << qx[2] << " " << qy[2] << std::endl;
      std::cout << "Q4 : " << qx[3] << " " << qy[3] << std::endl;
    }

    return Color( );
  }

}

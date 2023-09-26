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
#ifndef __SCOOP__SEQUENTIALCOLORMAP__
#define __SCOOP__SEQUENTIALCOLORMAP__

#include "Color.h"
#include "ColorPalette.h"
#include <scoop/api.h>
#include <vector>
#include <map>

namespace scoop
{

  /** Class for sequential color mapppers
   *
   *  This class allows to define a sequential color mapper. It allows to define
   *  a set of key values (floats) associated to colors. It also provides
   *  methods to get a color in between key values and obtain the interpolated
   *  color, both in RGB and HSV space. In order to be created at least two key
   *  points and two colors have to be defined, otherwise it will use 0.0f and
   *  1.0f as key values and black and white as theis associated colors.
   */
  class SequentialColorMap
  {
  public:

    //! Types of interpolation supported
    typedef enum
    {
      RGB_INTERPOLATION = 0,
      HSV_INTERPOLATION
    } ColorInterpolation;

    /**
     * Default constructor.
     *
     * @param[in] minValue_: minimum key value
     * @param[in] minColor: color associated to maximum key value
     * @param[in] maxValue_: maximum key value
     * @param[in] maxColor: color associated to maximum key value
     */
    SCOOP_API
    SequentialColorMap( float minValue_ = 0.f,
                        const Color& minColor = Color( 0, 0, 0 ),
                        float maxValue_ = 1.f,
                        const Color& maxColor = Color( 255, 255, 255 ));


    /**
     * Constructs a sequential color mapper based on a container of values and
     * a color palette. The size of the container of values and the palette have
     * to be the same and at least 2, otherwise an exception will be raised.
     *
     * @param[in] values: container of values
     * @param[in] palette: palette to be used
     */
    SCOOP_API
    SequentialColorMap( const std::vector< float >& values,
                        const ColorPalette& palette );

    /**
     * Constructs a sequential color mapper based on a min and max values and
     * a color palette. A set of key values, of the size of the palette, will
     * ba created  equally distributed in the range [minValue_,maxValue_]
     *
     * @param[in] palette: palette to be used
     * @param[in] minValue: minimum key value
     * @param[in] maxValue: maximum key value
     */
    SCOOP_API
    SequentialColorMap( const ColorPalette& palette,
                        float minValue = 0.f, float maxValue = 1.f );

    /**
     * Sets the sequential color mapper based on a container of values and
     * a color palette. The size of the container of values and the palette have
     * to be the same and at least 2, otherwise an exception will be raised.
     * Current key values and colors are cleared.
     *
     * @param[in] values: container of values
     * @param[in] palette: palette to be used
     */
    SCOOP_API void setFromPalette( const std::vector< float >& values,
                                   const ColorPalette& palette );

     /**
     * Returns the minimum key value
     *
     * @return maximum key value
     */
    SCOOP_API float minValue( void ) const;

    /**
     * Returns the maximum key value
     *
     * @return maximum key value
     */
    SCOOP_API float maxValue( void ) const;

    /**
     * Adds a new key value and its associated color. If key valye exists
     * the color will be overwritten
     *
     * @param[in] value: new key value
     * @param[in] color: color to be assoaciated to the key value
     */
    SCOOP_API void addColor( const float value, const Color& color );

    /**
     * Gets the color associated to a value. If the value has not been registered
     * with a color then the color returned will be interpolated in RGB os HSV
     * color space.
     *
     * @param[in] value: value to query its color
     * @param[in] interpolation: space in which the interpolation, if needed,
     *                           will be carried out
     * @return the color associated to the input value
     */
    SCOOP_API Color getColor(
      const float value,
      const ColorInterpolation interpolation = RGB_INTERPOLATION ) const;

  protected:

    Color _rgbInterpolation( const Color& color1,
                             const Color& color2,
                             float normDist ) const;
    Color _hsvInterpolation( const Color& color1,
                             const Color& color2,
                             float normDist ) const;

    //! Ordered container with the mapping between values and colors
    std::map< float, Color > _valuesToColors;
  };


} // namespace scoop

#endif

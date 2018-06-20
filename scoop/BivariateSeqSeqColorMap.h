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
#ifndef __SCOOP__BIVARIATESEQUENTIALCOLORMAP__
#define __SCOOP__BIVARIATESEQUENTIALCOLORMAP__

#include "Color.h"
#include "ColorPalette.h"
#include "SequentialColorMap.h"
#include <scoop/api.h>
#include <vector>
#include <map>

namespace scoop
{

  class BivariateSeqSeqColorMap
  {
  public:

    typedef std::map< std::pair< float, float>, Color > BivariateSeqSeqColorMapCont;
    SCOOP_API
    BivariateSeqSeqColorMap(
      BivariateSeqSeqColorMapCont = {} );

    /**
     * Returns the minimum key value
     *
     * @return maximum key value
     */
    SCOOP_API float minValueX( void ) const;

    /**
     * Returns the maximum key value
     *
     * @return maximum key value
     */
    SCOOP_API float maxValueX( void ) const;

    /**
     * Returns the minimum key value
     *
     * @return maximum key value
     */
    SCOOP_API float minValueY( void ) const;

    /**
     * Returns the maximum key value
     *
     * @return maximum key value
     */
    SCOOP_API float maxValueY( void ) const;

    SCOOP_API Color getColor(
      const float value1, const float value2,
      const SequentialColorMap::ColorInterpolation interpolation =
      SequentialColorMap::RGB_INTERPOLATION ) const;

  protected:

    BivariateSeqSeqColorMapCont _valuesToColors;

  };


} // namespace scoop

#endif

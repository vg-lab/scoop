/*
 * Copyright (c) 2016 GMRV/URJC/UPM.
 *
 * Authors: Pablo Toharia <pablo.toharia@upm.es>
 *
 * This file is part of Scoop
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
#include <scoop/scoop.h>
#include "scoopTests.h"

#include <iostream>
#include <sstream>

BOOST_AUTO_TEST_CASE( operators )
{
  scoop::Color c1( 0, 0, 0 );
  scoop::Color c2( 0, 0, 0, 128 );
  scoop::Color c3( 0, 100, 200, 255 );

  {
    std::stringstream out;
    out << c1;
    BOOST_CHECK_EQUAL( out.str( ), "Color(0,0,0,255)" );
  }
  {
    std::stringstream out;
    out << c2;
    BOOST_CHECK_EQUAL( out.str( ), "Color(0,0,0,128)" );
  }
  {
    std::stringstream out;
    out << c3;
    BOOST_CHECK_EQUAL( out.str( ), "Color(0,100,200,255)" );
  }
}

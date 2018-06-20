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
#include <scoop/scoop.h>
#include <iostream>
#include <cmath>

using namespace scoop;

void printMapping( const scoop::SequentialColorMap& cm,
                   float min, float max, float incr )
{
  std::cout << "<div>" << std::endl;
  for ( float i = min ; i <= max; i += incr )
  {
    auto color = cm.getColor( i );
    int h,s,v;
    color.getHsv( &h, &s, &v );
    std::cout << "<div style=\"width:5px; height: 30px; background: "
              << color.name( ).toStdString( ) << "; float: left\"></div>" << std::endl;
  }
  std::cout << "</div>" << std::endl;
}

int main ( void )
{
  // std::cout << std::atan2( 6 - 7, 2 - 3 )  * 180 / 3.14f << std::endl;
  // std::cout << std::atan2( 8 - 7, 1 - 3 )  * 180 / 3.14f << std::endl;
  // std::cout << std::atan2( 5 - 7, 4 - 3 )  * 180 / 3.14f << std::endl;
  // std::cout << std::atan2( 8 - 7, 4 - 3 )  * 180 / 3.14f << std::endl;

  scoop::BivariateSeqSeqColorMap bsscp(
    {
      {{ 1.0f, 5.0f }, Color( 0, 0, 0) },
      {{ 4.0f, 5.0f }, Color( 255, 0, 0) },
      {{ 1.0f, 8.0f }, Color( 0, 255, 0) },
      {{ 4.0f, 8.0f }, Color( 255, 255, 0) },
      {{ 2.0f, 6.0f }, Color( 0, 0, 255) }
    } );

  std::cout << bsscp.getColor( 1, 5 ) << std::endl<< std::endl;
  std::cout << bsscp.getColor( 4, 5 ) << std::endl<< std::endl;
  std::cout << bsscp.getColor( 1, 8 ) << std::endl<< std::endl;
  std::cout << bsscp.getColor( 4, 8 ) << std::endl<< std::endl;
  std::cout << bsscp.getColor( 3, 7 ) << std::endl<< std::endl;

  // std::cout
  //   << bsscp.minValueX( ) << " "
  //   << bsscp.maxValueX( ) << " "
  //   << bsscp.minValueY( ) << " "
  //   << bsscp.maxValueY( ) << " "
  //   << std::endl;

  return 0;

}

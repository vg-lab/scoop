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
#include <iostream>
#include <scoop/SequentialColorMap.h>

void printMapping( const scoop::SequentialColorMap& cm,
                   float min, float max, float incr )
{
  for ( float i = min ; i <= max; i += incr )
  {
    auto color = cm.getColor( i );
    int h,s,v;
    color.getHsv( &h, &s, &v );
    std::cout << "#" << i << ":\t"
              << color.red( ) << "\t" << color.green( ) << "\t"
              << color.blue( ) << "\t" << color.alpha( )
              << "\thsv(" << h << "," << s << "," << v << ")"
              << std::endl;
  }
}

int main ( void )
{
  // Setting up a mapper based on RGB colors
  {
    scoop::SequentialColorMap cm( 0.0f, scoop::Color( 255, 0, 0 ),
                                  1.0f, scoop::Color( 0, 255, 0 ));
    printMapping( cm, 0.0f, 1.1f, 0.1f );
    std::cout << "-----------" << std::endl;

    cm.addColor( 0.5f, scoop::Color( 0, 0, 255, 0 ));
    printMapping( cm, 0.0f, 1.1f, 0.1f );
    std::cout << "-----------" << std::endl;
  }


  // Setting up a mapper based on a palette
  {
    scoop::ColorPalette cp =
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 );
    scoop::SequentialColorMap cm( { 0.0f, 0.5f, 1.0f }, cp );
    printMapping( cm, 0.0f, 1.1f, 0.1f );
    std::cout << "-----------" << std::endl;
  }

  // Setting up a mapper based on HSV colors
  {
    scoop::Color c1, c2;
    c1.setHsv( 180, 255, 255 );
    c2.setHsv( 180, 0, 0 );
    scoop::SequentialColorMap cm( 0.0f, c1, 1.0f, c2 );
    printMapping( cm, 0.0f, 1.1f, 0.1f );
    std::cout << "-----------" << std::endl;

  }
  return 0;
}

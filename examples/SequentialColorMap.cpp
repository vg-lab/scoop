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
#include <iostream>
#include <scoop/SequentialColorMap.h>

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
  // Setting up a mapper based on RGB colors
  {
    scoop::SequentialColorMap cm( 0.0f, scoop::Color( 255, 0, 0 ),
                                  1.0f, scoop::Color( 0, 255, 0 ));

    std::cout << "<div style=\"min-height:70px\"><div>Mapper based on RGB colors</div>" << std::endl;
    printMapping( cm, 0.0f, 1.1f, 0.01f );
    std::cout << "</div>" << std::endl;

    cm.addColor( 0.5f, scoop::Color( 0, 0, 255, 0 ));
    std::cout << "<div style=\"min-height:70px\"><div>Mapper based on RGB colors adding one more color</div>" << std::endl;
    printMapping( cm, 0.0f, 1.1f, 0.01f );
    std::cout << "</div>" << std::endl;
  }

  // Setting up a mapper based on a palette
  {
    scoop::ColorPalette cp =
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3 );
    scoop::SequentialColorMap cm( { 0.0f, 0.5f, 1.0f }, cp );
    std::cout << "<div style=\"min-height:70px\"><div>Mapper based on a ColorBrewer palette</div>" << std::endl;
    printMapping( cm, 0.0f, 1.1f, 0.01f );
    std::cout << "</div>" << std::endl;
  }

  // Setting up a mapper based on a palette reversed
  {
    scoop::ColorPalette cp =
      scoop::ColorPalette::colorBrewerSequential(
        scoop::ColorPalette::ColorBrewerSequential::BuPu, 3, false );
    scoop::SequentialColorMap cm( { 0.0f, 0.5f, 1.0f }, cp );
    std::cout << "<div style=\"min-height:70px\"><div>Mapper based on a ColorBrewer palette reversed</div>" << std::endl;
    printMapping( cm, 0.0f, 1.1f, 0.01f );
    std::cout << "</div>" << std::endl;
  }

  // Setting up a mapper based on HSV colors
  {
    scoop::Color c1, c2;
    c1.setHsv( 180, 255, 255 );
    c2.setHsv( 180, 0, 0 );
    scoop::SequentialColorMap cm( 0.0f, c1, 1.0f, c2 );
    std::cout << "<div style=\"min-height:70px\"><div>Mapper based on HSV colors</div>" << std::endl;
    printMapping( cm, 0.0f, 1.1f, 0.01f );
    std::cout << "</div>" << std::endl;
  }

  // Setting up a mapper based on a matplotlib palette
  std::cout << "<div style=\"min-height:70px\"><div>Mappers based on mpl palettes</div>" << std::endl;
  for ( const auto& colorPalette :
    { scoop::ColorPalette::MatplotlibPerceptualUniform::Viridis,
        scoop::ColorPalette::MatplotlibPerceptualUniform::Magma,
        scoop::ColorPalette::MatplotlibPerceptualUniform::Inferno,
        scoop::ColorPalette::MatplotlibPerceptualUniform::Plasma } )
  {
    {
      scoop::ColorPalette cp =
        scoop::ColorPalette::matplotlibPerceptualUniform(
          colorPalette, false);
      scoop::SequentialColorMap cm( cp, 0.0f, 1.0f );
      std::cout << "<div style=\"min-height:70px\">" << std::endl;
      printMapping( cm, 0.0f, 1.1f, 0.01f );
      std::cout << "</div>" << std::endl;
    }
  }
  std::cout << "</div>" << std::endl;
  return 0;
}

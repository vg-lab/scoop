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
#ifndef __SCOOP__CATEGORICALCOLORMAP__
#define __SCOOP__CATEGORICALCOLORMAP__

#include "Color.h"
#include "ColorPalette.h"
#include <unordered_map>
#include <stdexcept>

namespace scoop
{
  template< class Category = int,
            class Hash = std::hash< int >>
  class CategoricalColorMap
  {
  public:
    CategoricalColorMap( void ) {};
    CategoricalColorMap( std::vector< Category > categories,
                         ColorPalette palette );

    void setColor( const Category& category, const Color& color );
    const Color& getColor( const Category& category ) const;

  protected:
    std::unordered_map< Category, Color, Hash > _categoriesToColors;
  };

  template< class Category, class Hash  >
  CategoricalColorMap< Category, Hash >::CategoricalColorMap(
    std::vector< Category> categories,
    ColorPalette palette )
  {
    if ( categories.size( ) != palette.size( ))
      throw std::runtime_error( "Palette and categories sizes do not match" );
    const auto& colors = palette.colors( );
    for ( unsigned int i = 0; i < categories.size( ); ++i )
      setColor( categories[i], colors[i] );
  }

  template< class Category, class Hash  >
  void CategoricalColorMap< Category, Hash >::setColor(
    const Category& category, const Color& color)
  {
    _categoriesToColors[ category ] = color;
  }

  template< class Category, class Hash >
  const Color& CategoricalColorMap< Category, Hash >::getColor(
    const Category& category ) const
  {
    if ( _categoriesToColors.count( category ) != 1 )
      throw( std::runtime_error( "Category does not exist." ));
    else
      return _categoriesToColors.at( category );
  }

} // namespace scoop

#endif

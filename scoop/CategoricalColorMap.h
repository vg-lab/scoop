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
  /** Class for categorical color maps
   *
   *  This class allows to define a categorical color mapper. It provides the
   *  methods needed to establish the relationship between categories and the
   *  associated colors. This class is template because it can be use for
   *  different types of categories
   */
  template< class Category = int,
            class Hash = std::hash< int >>
  class CategoricalColorMap
  {
  public:

    /**
     * Default constructor. Creates an empty color mapper
     *
     */
    CategoricalColorMap( void ) {};

    /**
     * Constructorbased on a vector of categories and a color palette. This size
     * of the provided categories and the palette has to be the same, otherwise
     * an exception will be raised.
     *
     * @param[in] categories: input categories
     * @param[in] palette: input palette
     *
     */
    CategoricalColorMap( const std::vector< Category >& categories,
                         const ColorPalette& palette );

    /**
     * Set a color for a category
     *
     * @param[in] category: category which will be associated
     * @param[in] color: color to be associated to the category
     *
     */
    void setColor( const Category& category, const Color& color );

    /**
     * Get a color for a category
     *
     * @param[in] category: input category
     *
     */
    const Color& getColor( const Category& category ) const;

  protected:

    //! Container that associates each category to a color
    std::unordered_map< Category, Color, Hash > _categoriesToColors;
  };


  //// Impl ////


  template< class Category, class Hash  >
  CategoricalColorMap< Category, Hash >::CategoricalColorMap(
    const std::vector< Category>& categories,
    const ColorPalette& palette )
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

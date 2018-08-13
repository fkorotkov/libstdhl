//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                <https://github.com/casm-lang/libstdhl>
//
//  This file is part of libstdhl.
//
//  libstdhl is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libstdhl is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libstdhl. If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  libstdhl is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libstdhl
//  statically or dynamically with other modules is making a combined work
//  based on libstdhl. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libstdhl give you permission to link libstdhl
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libstdhl. If you modify libstdhl, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#ifndef _LIBSTDHL_CPP_HASH_H_
#define _LIBSTDHL_CPP_HASH_H_

#include <libstdhl/type/Type>

#include <functional>

/**
   @brief    TODO

   TODO
*/

namespace libstdhl
{
    /**
       @extends Stdhl

       inspired from LLVM's hashing code, see:
       http://llvm.org/docs/doxygen/html/Hashing_8h_source.html
    */
    namespace Hash
    {
        class Code
        {
          public:
            Code( void ) = default;

            Code( const std::size_t value )
            : m_value( value )
            {
            }

            inline operator std::size_t( void ) const
            {
                return m_value;
            }

            inline std::size_t value( void ) const
            {
                return m_value;
            }

            inline u1 operator==( const Code& rhs ) const
            {
                return m_value == rhs.value();
            }

            inline u1 operator!=( const Code& rhs ) const
            {
                return m_value != rhs.value();
            }

            friend std::size_t value( const Code& code )
            {
                return code.m_value;
            }

          private:
            std::size_t m_value;
        };

        inline std::size_t value( const u64 data )
        {
            return std::hash< u64 >()( data );
        }

        inline std::size_t value( const std::string& str )
        {
            return std::hash< std::string >()( str );
        }

        /**
           from boost, see:
           http://www.boost.org/doc/libs/1_55_0/boost/functional/hash/hash.hpp
         */
        inline constexpr std::size_t combine( const std::size_t seed, const std::size_t hash )
        {
            return seed ^ ( hash + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 ) );
        }
    }
}

#endif  // _LIBSTDHL_CPP_HASH_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//

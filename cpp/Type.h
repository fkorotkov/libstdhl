//
//  Copyright (c) 2014-2017 Philipp Paulweber
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libstdhl
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

#ifndef _LIB_STDHL_CPP_TYPE_H_
#define _LIB_STDHL_CPP_TYPE_H_

#include "cpp/Default.h"

#include "c/type.h"

#include <array>
#include <bitset>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Hash.h"

/**
   @brief    TODO

   TODO
*/

namespace libstdhl
{
    /**
       @extends Stdhl
    */
    namespace Type
    {
        enum Radix : u8
        {
            BINARY = 2,
            OCTAL = 8,
            DECIMAL = 10,
            HEXADECIMAL = 16,
            SEXAGESIMAL = 60,
            RADIX64 = 64,
        };

        enum Literal : u8
        {
            NONE = 0,
            STDHL = 1,
            C = 2,
            CPP14 = 3,
            BASE64 = 10,
            UNIX = 20
        };

        //
        // Boolean
        //

        class Boolean;

        Boolean createBoolean( const std::string& value );

        Boolean createBoolean( const u1 value );

        //
        // Integer
        //

        class Integer;

        Integer createInteger(
            const std::string& value, const Radix radix = DECIMAL );

        Integer createInteger( const u64 value );

        Integer createInteger( const i64 value );

        //
        // Natural
        //

        class Natural;

        Natural createNatural(
            const std::string& value, const Radix radix = DECIMAL );

        Natural createNatural( const Integer& value );

        Natural createNatural( const u64 value );

        //
        // Rational
        //

        class Rational;

        Rational createRational(
            const std::string& value, const Radix radix = DECIMAL );

        Rational createRational(
            const Integer& numerator, const Integer& denominator );

        //
        // Floating
        //

        class Floating;

        Floating createFloating(
            const std::string& value, const Radix radix = DECIMAL );

        Floating createFloating( const double value );

        //
        // String
        //

        class String;

        String createString( const std::string& value );
    }
}

#endif // _LIB_STDHL_CPP_TYPE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//

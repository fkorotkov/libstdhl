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

#include "uts/main.h"

using namespace libstdhl;

template < typename... Args >
static std::size_t func_size( Args&&... args )
{
    return Variadic< Args... >::size;
}

TEST( libstdhl_cpp_Variadic, argument_size )
{
    EXPECT_EQ( func_size( 0, 1, 2, 3 ), 4 );
    EXPECT_EQ( func_size( 10, "asdf", 'g', 4.8, true ), 5 );
    EXPECT_EQ( func_size( true, false, true ), 3 );
}

// template < typename... Args >
// static std::size_t func_sum( Args&&... args )
// {
//     std::size_t sum = 0;

//     Variadic< Args... >::iterate(
//         [&]( std::size_t index, i64&& value ) { sum += value; },
//         std::forward< Args >( args )... );

//     return sum;
// }

// TEST( libstdhl_cpp_Variadic, argument_sum )
// {
//     EXPECT_EQ( func_sum( 1, 2, 3, 4 ), 10 );
// }

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//

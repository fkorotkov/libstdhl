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

#include "Timestamp.h"

#include "Formatter.h"

#include <iomanip>
#include <sstream>

using namespace libstdhl;
using namespace Log;

static inline std::string time2str( const std::tm* datetime, const char* format )
{
#if not __clang__ and __GNUC__ < 5
    char buffer[ 512 ];
    if( not strftime( buffer, sizeof( buffer ), format, datetime ) )
    {
        throw std::domain_error( "unable to format the timestamp with 'strftime'" );
    }
    return std::string( buffer );
#else
    std::stringstream buffer;
    buffer << std::put_time( datetime, format );
    return buffer.str();
#endif
}

//
// Timestamp
//

Timestamp::Timestamp( void )
: Item( Item::ID::TIMESTAMP )
, m_timestamp( std::chrono::system_clock::now() )
{
}

std::chrono::system_clock::time_point Timestamp::timestamp( void ) const
{
    return m_timestamp;
}

std::time_t Timestamp::c_timestamp( void ) const
{
    return std::chrono::system_clock::to_time_t( m_timestamp );
}

std::string Timestamp::local( const std::string& format ) const
{
    const auto t = c_timestamp();
    return time2str( std::localtime( &t ), format.c_str() );
}

std::string Timestamp::utc( const std::string& format ) const
{
    const auto t = c_timestamp();
    return time2str( std::gmtime( &t ), format.c_str() );
}

std::string Timestamp::accept( Formatter& formatter )
{
    return formatter.visit( *this );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//

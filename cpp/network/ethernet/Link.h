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

#ifndef _LIB_STDHL_CPP_NETWORK_ETHERNET_LINK_H_
#define _LIB_STDHL_CPP_NETWORK_ETHERNET_LINK_H_

#include "../Interface.h"

#include "Packet.h"

namespace libstdhl
{
    namespace Network
    {
        namespace Ethernet
        {
            class Link final : public Network::Interface< Packet >
            {
              public:
                using Ptr = std::shared_ptr< Link >;

                Link( const std::string& name );

                void send( const Packet& data ) override;

                void send( const std::string& data ) override;

                void send( const std::vector< u8 >& data );

                void receive( Packet& data ) override;

                Packet receive( std::string& data ) override;

                void receive( std::vector< u8 >& data );
            };
        }
    };
}

#endif // _LIB_STDHL_CPP_NETWORK_ETHERNET_LINK_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
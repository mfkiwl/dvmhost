/**
* Digital Voice Modem - Converged FNE Software
* GPLv2 Open Source. Use is subject to license terms.
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
*
* @package DVM / Converged FNE Software
*
*/
/*
*   Copyright (C) 2023-2024 by Bryan Biedenkapp N2PLL
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#if !defined(__FNE__TAG_DMR_DATA_H__)
#define __FNE__TAG_DMR_DATA_H__

#include "fne/Defines.h"
#include "common/dmr/DMRDefines.h"
#include "common/dmr/data/Data.h"
#include "common/Clock.h"
#include "network/FNENetwork.h"

#include <deque>

namespace network
{
    namespace fne
    {
        // ---------------------------------------------------------------------------
        //  Class Declaration
        //      Implements the DMR data FNE networking logic.
        // ---------------------------------------------------------------------------

        class HOST_SW_API TagDMRData {
        public:
            /// <summary>Initializes a new instance of the TagDMRData class.</summary>
            TagDMRData(FNENetwork* network, bool debug);
            /// <summary>Finalizes a instance of the TagDMRData class.</summary>
            ~TagDMRData();

            /// <summary>Process a data frame from the network.</summary>
            bool processFrame(const uint8_t* data, uint32_t len, uint32_t peerId, uint16_t pktSeq, uint32_t streamId, bool fromPeer = false);

            /// <summary>Helper to playback a parrot frame to the network.</summary>
            void playbackParrot();
            /// <summary>Helper to determine if there are stored parrot frames.</summary>
            bool hasParrotFrames() const { return m_parrotFramesReady && !m_parrotFrames.empty(); }

        private:
            FNENetwork* m_network;

            std::deque<std::tuple<uint8_t*, uint32_t, uint16_t, uint32_t>> m_parrotFrames;
            bool m_parrotFramesReady;

            class RxStatus {
            public:
                system_clock::hrc::hrc_t callStartTime;
                uint32_t srcId;
                uint32_t dstId;
                uint8_t slotNo;
                uint32_t streamId;
            };
            typedef std::pair<const uint32_t, RxStatus> StatusMapPair;
            std::unordered_map<uint32_t, RxStatus> m_status;

            bool m_debug;

            /// <summary>Helper to route rewrite the network data buffer.</summary>
            void routeRewrite(uint8_t* buffer, uint32_t peerId, dmr::data::Data dmrData, uint8_t dataType, uint32_t dstId, uint32_t slotNo, bool outbound = true);
            /// <summary>Helper to route rewrite destination ID and slot.</summary>
            bool peerRewrite(uint32_t peerId, uint32_t& dstId, uint32_t& slotNo, bool outbound = true);

            /// <summary>Helper to determine if the peer is permitted for traffic.</summary>
            bool isPeerPermitted(uint32_t peerId, dmr::data::Data& data, uint32_t streamId);
            /// <summary>Helper to validate the DMR call stream.</summary>
            bool validate(uint32_t peerId, dmr::data::Data& data, uint32_t streamId);
        };
    } // namespace fne
} // namespace network

#endif // __FNE__TAG_DMR_DATA_H__
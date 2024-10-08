// SPDX-License-Identifier: PROPRIETARY
/*
 * Digital Voice Modem - FNE Affiliations View
 * GPLv2 Open Source. Use is subject to license terms.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 *  Copyright (C) 2024 Bryan Biedenkapp, N2PLL
 *
 */
/**
 * @defgroup fneAffView_network Networking
 * @brief Implementation for the FNE networking.
 * @ingroup fneAffView
 *
 * @file PeerNetwork.h
 * @ingroup fneAffView_network
 * @file PeerNetwork.cpp
 * @ingroup fneAffView_network
 */
#if !defined(__PEER_NETWORK_H__)
#define __PEER_NETWORK_H__

#include "Defines.h"
#include "host/network/Network.h"

#include <string>
#include <cstdint>

namespace network
{
    // ---------------------------------------------------------------------------
    //  Class Declaration
    //      Implements the core peer networking logic.
    // ---------------------------------------------------------------------------

    class HOST_SW_API PeerNetwork : public Network {
    public:
        /**
         * @brief Initializes a new instance of the PeerNetwork class.
         * @param address Network Hostname/IP address to connect to.
         * @param port Network port number.
         * @param local 
         * @param peerId Unique ID on the network.
         * @param password Network authentication password.
         * @param duplex Flag indicating full-duplex operation.
         * @param debug Flag indicating whether network debug is enabled.
         * @param dmr Flag indicating whether DMR is enabled.
         * @param p25 Flag indicating whether P25 is enabled.
         * @param nxdn Flag indicating whether NXDN is enabled.
         * @param slot1 Flag indicating whether DMR slot 1 is enabled for network traffic.
         * @param slot2 Flag indicating whether DMR slot 2 is enabled for network traffic.
         * @param allowActivityTransfer Flag indicating that the system activity logs will be sent to the network.
         * @param allowDiagnosticTransfer Flag indicating that the system diagnostic logs will be sent to the network.
         * @param updateLookup Flag indicating that the system will accept radio ID and talkgroup ID lookups from the network.
         */
        PeerNetwork(const std::string& address, uint16_t port, uint16_t localPort, uint32_t peerId, const std::string& password,
            bool duplex, bool debug, bool dmr, bool p25, bool nxdn, bool slot1, bool slot2, bool allowActivityTransfer, bool allowDiagnosticTransfer, bool updateLookup, bool saveLookup);

        /**
         * @brief Map of peer status.
         */
        std::unordered_map<uint32_t, json::object> peerStatus;

    protected:
        /**
         * @brief User overrideable handler that allows user code to process network packets not handled by this class.
         * @param peerId Peer ID.
         * @param opcode FNE network opcode pair.
         * @param[in] data Buffer containing message to send to peer.
         * @param length Length of buffer.
         * @param streamId Stream ID.
         */
        void userPacketHandler(uint32_t peerId, FrameQueue::OpcodePair opcode, const uint8_t* data = nullptr, uint32_t length = 0U,
            uint32_t streamId = 0U) override;

        /**
         * @brief Writes configuration to the network.
         * @returns bool True, if configuration was sent, otherwise false.
         */
        bool writeConfig() override;
    };
} // namespace network

#endif // __PEER_NETWORK_H__

// SPDX-License-Identifier: GPL-2.0-only
/**
* Digital Voice Modem - Modem Host Software
* GPLv2 Open Source. Use is subject to license terms.
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
*
* @package DVM / Modem Host Software
* @derivedfrom MMDVMHost (https://github.com/g4klx/MMDVMHost)
* @license GPLv2 License (https://opensource.org/licenses/GPL-2.0)
*
*   Copyright (C) 2015,2016,2017 Jonathan Naylor, G4KLX
*   Copyright (C) 2017-2022 Bryan Biedenkapp, N2PLL
*
*/
#if !defined(__DMR_PACKET_CONTROL_SIGNALING_H__)
#define __DMR_PACKET_CONTROL_SIGNALING_H__

#include "Defines.h"
#include "common/dmr/data/Data.h"
#include "common/dmr/data/EmbeddedData.h"
#include "common/dmr/lc/LC.h"
#include "common/dmr/lc/CSBK.h"
#include "common/network/BaseNetwork.h"
#include "common/RingBuffer.h"
#include "common/StopWatch.h"
#include "common/Timer.h"
#include "modem/Modem.h"

#include <vector>

namespace dmr
{
    // ---------------------------------------------------------------------------
    //  Class Prototypes
    // ---------------------------------------------------------------------------

    class HOST_SW_API Slot;

    namespace packet
    {
        // ---------------------------------------------------------------------------
        //  Class Declaration
        //      This class implements core logic for handling DMR control signaling (CSBK)
        //      packets.
        // ---------------------------------------------------------------------------

        class HOST_SW_API ControlSignaling
        {
        public:
            /// <summary>Process a data frame from the RF interface.</summary>
            bool process(uint8_t* data, uint32_t len);
            /// <summary>Process a data frame from the network.</summary>
            void processNetwork(const data::Data& dmrData);

            /// <summary>Helper to write P25 adjacent site information to the network.</summary>
            void writeAdjSSNetwork();

            /// <summary>Helper to write a extended function packet on the RF interface.</summary>
            void writeRF_Ext_Func(uint32_t func, uint32_t arg, uint32_t dstId);
            /// <summary>Helper to write a call alert packet on the RF interface.</summary>
            void writeRF_Call_Alrt(uint32_t srcId, uint32_t dstId);

        private:
            friend class dmr::Slot;
            Slot* m_slot;

            bool m_dumpCSBKData;
            bool m_verbose;
            bool m_debug;

            /// <summary>Initializes a new instance of the ControlSignaling class.</summary>
            ControlSignaling(Slot* slot, network::BaseNetwork* network, bool dumpCSBKData, bool debug, bool verbose);
            /// <summary>Finalizes a instance of the ControlSignaling class.</summary>
            ~ControlSignaling();

            /*
            ** Modem Frame Queuing
            */

            /// <summary>Helper to write a immediate CSBK packet.</summary>
            void writeRF_CSBK_Imm(lc::CSBK *csbk) { writeRF_CSBK(csbk, true); }
            /// <summary>Helper to write a CSBK packet.</summary>
            void writeRF_CSBK(lc::CSBK* csbk, bool imm = false);
            /// <summary>Helper to write a network CSBK packet.</summary>
            void writeNet_CSBK(lc::CSBK* csbk);

            /*
            ** Control Signalling Logic
            */

            /// <summary>Helper to write a ACK RSP packet.</summary>
            void writeRF_CSBK_ACK_RSP(uint32_t dstId, uint8_t reason, uint8_t responseInfo);
            /// <summary>Helper to write a NACK RSP packet.</summary>
            void writeRF_CSBK_NACK_RSP(uint32_t dstId, uint8_t reason, uint8_t service);
            /// <summary>Helper to write a grant packet.</summary>
            bool writeRF_CSBK_Grant(uint32_t srcId, uint32_t dstId, uint8_t serviceOptions, bool grp, bool net = false, bool skip = false, uint32_t chNo = 0U);
            /// <summary>Helper to write a data grant packet.</summary>
            bool writeRF_CSBK_Data_Grant(uint32_t srcId, uint32_t dstId, uint8_t serviceOptions, bool grp, bool net = false, bool skip = false, uint32_t chNo = 0U);
            /// <summary>Helper to write a unit registration response packet.</summary>
            void writeRF_CSBK_U_Reg_Rsp(uint32_t srcId, uint8_t serviceOptions);

            /// <summary>Helper to write a TSCC late entry channel grant packet on the RF interface.</summary>
            void writeRF_CSBK_Grant_LateEntry(uint32_t dstId, uint32_t srcId, bool grp);
            /// <summary>Helper to write a payload activation to a TSCC payload channel on the RF interface.</summary>
            void writeRF_CSBK_Payload_Activate(uint32_t dstId, uint32_t srcId, bool grp, bool voice, bool imm = false);
            /// <summary>Helper to write a payload clear to a TSCC payload channel on the RF interface.</summary>
            void writeRF_CSBK_Payload_Clear(uint32_t dstId, uint32_t srcId, bool grp, bool imm = false);

            /// <summary>Helper to write a TSCC Aloha broadcast packet on the RF interface.</summary>
            void writeRF_TSCC_Aloha();
            /// <summary>Helper to write a TSCC Ann-Wd broadcast packet on the RF interface.</summary>
            void writeRF_TSCC_Bcast_Ann_Wd(uint32_t channelNo, bool annWd, uint32_t systemIdentity, bool requireReg);
            /// <summary>Helper to write a TSCC Sys_Parm broadcast packet on the RF interface.</summary>
            void writeRF_TSCC_Bcast_Sys_Parm();
            /// <summary>Helper to write a TSCC Git Hash broadcast packet on the RF interface.</summary>
            void writeRF_TSCC_Git_Hash();
        };
    } // namespace packet
} // namespace dmr

#endif // __DMR_PACKET_CONTROL_SIGNALING_H__

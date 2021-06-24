<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_अघोषित _ISCI_PHY_H_
#घोषणा _ISCI_PHY_H_

#समावेश <scsi/sas.h>
#समावेश <scsi/libsas.h>
#समावेश "isci.h"
#समावेश "sas.h"

/* This is the समयout value क्रम the SATA phy to रुको क्रम a SIGNATURE FIS
 * beक्रमe restarting the starting state machine.  Technically, the old parallel
 * ATA specअगरication required up to 30 seconds क्रम a device to issue its
 * signature FIS as a result of a soft reset.  Now we see that devices respond
 * generally within 15 seconds, but we'll use 25 क्रम now.
 */
#घोषणा SCIC_SDS_SIGNATURE_FIS_TIMEOUT    25000

/* This is the समयout क्रम the SATA OOB/SN because the hardware करोes not
 * recognize a hot plug after OOB संकेत but beक्रमe the SN संकेतs.  We need to
 * make sure after a hotplug समयout अगर we have not received the speed event
 * notअगरication from the hardware that we restart the hardware OOB state
 * machine.
 */
#घोषणा SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT  250

/**
 * isci_phy - hba local phy infraकाष्ठाure
 * @sm:
 * @protocol: attached device protocol
 * @phy_index: physical index relative to the controller (0-3)
 * @bcn_received_जबतक_port_unasचिन्हित: bcn to report after port association
 * @sata_समयr: समयout SATA signature FIS arrival
 */
काष्ठा isci_phy अणु
	काष्ठा sci_base_state_machine sm;
	काष्ठा isci_port *owning_port;
	क्रमागत sas_linkrate max_negotiated_speed;
	क्रमागत sas_protocol protocol;
	u8 phy_index;
	bool bcn_received_जबतक_port_unasचिन्हित;
	bool is_in_link_training;
	काष्ठा sci_समयr sata_समयr;
	काष्ठा scu_transport_layer_रेजिस्टरs __iomem *transport_layer_रेजिस्टरs;
	काष्ठा scu_link_layer_रेजिस्टरs __iomem *link_layer_रेजिस्टरs;
	काष्ठा asd_sas_phy sas_phy;
	u8 sas_addr[SAS_ADDR_SIZE];
	जोड़ अणु
		काष्ठा sas_identअगरy_frame iaf;
		काष्ठा dev_to_host_fis fis;
	पूर्ण frame_rcvd;
पूर्ण;

अटल अंतरभूत काष्ठा isci_phy *to_iphy(काष्ठा asd_sas_phy *sas_phy)
अणु
	काष्ठा isci_phy *iphy = container_of(sas_phy, typeof(*iphy), sas_phy);

	वापस iphy;
पूर्ण

काष्ठा sci_phy_cap अणु
	जोड़ अणु
		काष्ठा अणु
			/*
			 * The SAS specअगरication indicates the start bit shall
			 * always be set to
			 * 1.  This implementation will have the start bit set
			 * to 0 अगर the PHY CAPABILITIES were either not
			 * received or speed negotiation failed.
			 */
			u8 start:1;
			u8 tx_ssc_type:1;
			u8 res1:2;
			u8 req_logical_linkrate:4;

			u32 gen1_no_ssc:1;
			u32 gen1_ssc:1;
			u32 gen2_no_ssc:1;
			u32 gen2_ssc:1;
			u32 gen3_no_ssc:1;
			u32 gen3_ssc:1;
			u32 res2:17;
			u32 parity:1;
		पूर्ण;
		u32 all;
	पूर्ण;
पूर्ण  __packed;

/* this data काष्ठाure reflects the link layer transmit identअगरication reg */
काष्ठा sci_phy_proto अणु
	जोड़ अणु
		काष्ठा अणु
			u16 _r_a:1;
			u16 smp_iport:1;
			u16 stp_iport:1;
			u16 ssp_iport:1;
			u16 _r_b:4;
			u16 _r_c:1;
			u16 smp_tport:1;
			u16 stp_tport:1;
			u16 ssp_tport:1;
			u16 _r_d:4;
		पूर्ण;
		u16 all;
	पूर्ण;
पूर्ण __packed;


/**
 * काष्ठा sci_phy_properties - This काष्ठाure defines the properties common to
 *    all phys that can be retrieved.
 *
 *
 */
काष्ठा sci_phy_properties अणु
	/**
	 * This field specअगरies the port that currently contains the
	 * supplied phy.  This field may be set to शून्य
	 * अगर the phy is not currently contained in a port.
	 */
	काष्ठा isci_port *iport;

	/**
	 * This field specअगरies the link rate at which the phy is
	 * currently operating.
	 */
	क्रमागत sas_linkrate negotiated_link_rate;

	/**
	 * This field specअगरies the index of the phy in relation to other
	 * phys within the controller.  This index is zero relative.
	 */
	u8 index;
पूर्ण;

/**
 * काष्ठा sci_sas_phy_properties - This काष्ठाure defines the properties,
 *    specअगरic to a SAS phy, that can be retrieved.
 *
 *
 */
काष्ठा sci_sas_phy_properties अणु
	/**
	 * This field delineates the Identअगरy Address Frame received
	 * from the remote end poपूर्णांक.
	 */
	काष्ठा sas_identअगरy_frame rcvd_iaf;

	/**
	 * This field delineates the Phy capabilities काष्ठाure received
	 * from the remote end poपूर्णांक.
	 */
	काष्ठा sci_phy_cap rcvd_cap;

पूर्ण;

/**
 * काष्ठा sci_sata_phy_properties - This काष्ठाure defines the properties,
 *    specअगरic to a SATA phy, that can be retrieved.
 *
 *
 */
काष्ठा sci_sata_phy_properties अणु
	/**
	 * This field delineates the signature FIS received from the
	 * attached target.
	 */
	काष्ठा dev_to_host_fis signature_fis;

	/**
	 * This field specअगरies to the user अगर a port selector is connected
	 * on the specअगरied phy.
	 */
	bool is_port_selector_present;

पूर्ण;

/**
 * क्रमागत sci_phy_counter_id - This क्रमागतeration depicts the various pieces of
 *    optional inक्रमmation that can be retrieved क्रम a specअगरic phy.
 *
 *
 */
क्रमागत sci_phy_counter_id अणु
	/**
	 * This PHY inक्रमmation field tracks the number of frames received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME,

	/**
	 * This PHY inक्रमmation field tracks the number of frames transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_FRAME,

	/**
	 * This PHY inक्रमmation field tracks the number of DWORDs received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_WORD,

	/**
	 * This PHY inक्रमmation field tracks the number of DWORDs transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_FRAME_DWORD,

	/**
	 * This PHY inक्रमmation field tracks the number of बार DWORD
	 * synchronization was lost.
	 */
	SCIC_PHY_COUNTER_LOSS_OF_SYNC_ERROR,

	/**
	 * This PHY inक्रमmation field tracks the number of received DWORDs with
	 * running disparity errors.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DISPARITY_ERROR,

	/**
	 * This PHY inक्रमmation field tracks the number of received frames with a
	 * CRC error (not including लघु or truncated frames).
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_CRC_ERROR,

	/**
	 * This PHY inक्रमmation field tracks the number of DONE (ACK/NAK TIMEOUT)
	 * primitives received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DONE_ACK_NAK_TIMEOUT,

	/**
	 * This PHY inक्रमmation field tracks the number of DONE (ACK/NAK TIMEOUT)
	 * primitives transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_DONE_ACK_NAK_TIMEOUT,

	/**
	 * This PHY inक्रमmation field tracks the number of बार the inactivity
	 * समयr क्रम connections on the phy has been utilized.
	 */
	SCIC_PHY_COUNTER_INACTIVITY_TIMER_EXPIRED,

	/**
	 * This PHY inक्रमmation field tracks the number of DONE (CREDIT TIMEOUT)
	 * primitives received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DONE_CREDIT_TIMEOUT,

	/**
	 * This PHY inक्रमmation field tracks the number of DONE (CREDIT TIMEOUT)
	 * primitives transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_DONE_CREDIT_TIMEOUT,

	/**
	 * This PHY inक्रमmation field tracks the number of CREDIT BLOCKED
	 * primitives received.
	 * @note Depending on remote device implementation, credit blocks
	 *       may occur regularly.
	 */
	SCIC_PHY_COUNTER_RECEIVED_CREDIT_BLOCKED,

	/**
	 * This PHY inक्रमmation field contains the number of लघु frames
	 * received.  A लघु frame is simply a frame smaller then what is
	 * allowed by either the SAS or SATA specअगरication.
	 */
	SCIC_PHY_COUNTER_RECEIVED_SHORT_FRAME,

	/**
	 * This PHY inक्रमmation field contains the number of frames received after
	 * credit has been exhausted.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_WITHOUT_CREDIT,

	/**
	 * This PHY inक्रमmation field contains the number of frames received after
	 * a DONE has been received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_AFTER_DONE,

	/**
	 * This PHY inक्रमmation field contains the number of बार the phy
	 * failed to achieve DWORD synchronization during speed negotiation.
	 */
	SCIC_PHY_COUNTER_SN_DWORD_SYNC_ERROR
पूर्ण;

/**
 * क्रमागत sci_phy_states - phy state machine states
 * @SCI_PHY_INITIAL: Simply the initial state क्रम the base करोमुख्य state
 *		     machine.
 * @SCI_PHY_STOPPED: phy has successfully been stopped.  In this state
 *		     no new IO operations are permitted on this phy.
 * @SCI_PHY_STARTING: the phy is in the process of becomming पढ़ोy.  In
 *		      this state no new IO operations are permitted on
 *		      this phy.
 * @SCI_PHY_SUB_INITIAL: Initial state
 * @SCI_PHY_SUB_AWAIT_OSSP_EN: Wait state क्रम the hardware OSSP event
 *			       type notअगरication
 * @SCI_PHY_SUB_AWAIT_SAS_SPEED_EN: Wait state क्रम the PHY speed
 *				    notअगरication
 * @SCI_PHY_SUB_AWAIT_IAF_UF: Wait state क्रम the IAF Unsolicited frame
 *			      notअगरication
 * @SCI_PHY_SUB_AWAIT_SAS_POWER: Wait state क्रम the request to consume
 *				 घातer
 * @SCI_PHY_SUB_AWAIT_SATA_POWER: Wait state क्रम request to consume
 *				  घातer
 * @SCI_PHY_SUB_AWAIT_SATA_PHY_EN: Wait state क्रम the SATA PHY
 *				   notअगरication
 * @SCI_PHY_SUB_AWAIT_SATA_SPEED_EN: Wait क्रम the SATA PHY speed
 *				     notअगरication
 * @SCI_PHY_SUB_AWAIT_SIG_FIS_UF: Wait state क्रम the SIGNATURE FIS
 *				  unsolicited frame notअगरication
 * @SCI_PHY_SUB_FINAL: Exit state क्रम this state machine
 * @SCI_PHY_READY: phy is now पढ़ोy.  Thus, the user is able to perक्रमm
 *		   IO operations utilizing this phy as दीर्घ as it is
 *		   currently part of a valid port.  This state is
 *		   entered from the STARTING state.
 * @SCI_PHY_RESETTING: phy is in the process of being reset.  In this
 *		       state no new IO operations are permitted on this
 *		       phy.  This state is entered from the READY state.
 * @SCI_PHY_FINAL: Simply the final state क्रम the base phy state
 *		   machine.
 */
#घोषणा PHY_STATES अणु\
	C(PHY_INITIAL),\
	C(PHY_STOPPED),\
	C(PHY_STARTING),\
	C(PHY_SUB_INITIAL),\
	C(PHY_SUB_AWAIT_OSSP_EN),\
	C(PHY_SUB_AWAIT_SAS_SPEED_EN),\
	C(PHY_SUB_AWAIT_IAF_UF),\
	C(PHY_SUB_AWAIT_SAS_POWER),\
	C(PHY_SUB_AWAIT_SATA_POWER),\
	C(PHY_SUB_AWAIT_SATA_PHY_EN),\
	C(PHY_SUB_AWAIT_SATA_SPEED_EN),\
	C(PHY_SUB_AWAIT_SIG_FIS_UF),\
	C(PHY_SUB_FINAL),\
	C(PHY_READY),\
	C(PHY_RESETTING),\
	C(PHY_FINAL),\
	पूर्ण
#अघोषित C
#घोषणा C(a) SCI_##a
क्रमागत sci_phy_states PHY_STATES;
#अघोषित C

व्योम sci_phy_स्थिरruct(
	काष्ठा isci_phy *iphy,
	काष्ठा isci_port *iport,
	u8 phy_index);

काष्ठा isci_port *phy_get_non_dummy_port(काष्ठा isci_phy *iphy);

व्योम sci_phy_set_port(
	काष्ठा isci_phy *iphy,
	काष्ठा isci_port *iport);

क्रमागत sci_status sci_phy_initialize(
	काष्ठा isci_phy *iphy,
	काष्ठा scu_transport_layer_रेजिस्टरs __iomem *transport_layer_रेजिस्टरs,
	काष्ठा scu_link_layer_रेजिस्टरs __iomem *link_layer_रेजिस्टरs);

क्रमागत sci_status sci_phy_start(
	काष्ठा isci_phy *iphy);

क्रमागत sci_status sci_phy_stop(
	काष्ठा isci_phy *iphy);

क्रमागत sci_status sci_phy_reset(
	काष्ठा isci_phy *iphy);

व्योम sci_phy_resume(
	काष्ठा isci_phy *iphy);

व्योम sci_phy_setup_transport(
	काष्ठा isci_phy *iphy,
	u32 device_id);

क्रमागत sci_status sci_phy_event_handler(
	काष्ठा isci_phy *iphy,
	u32 event_code);

क्रमागत sci_status sci_phy_frame_handler(
	काष्ठा isci_phy *iphy,
	u32 frame_index);

क्रमागत sci_status sci_phy_consume_घातer_handler(
	काष्ठा isci_phy *iphy);

व्योम sci_phy_get_sas_address(
	काष्ठा isci_phy *iphy,
	काष्ठा sci_sas_address *sas_address);

व्योम sci_phy_get_attached_sas_address(
	काष्ठा isci_phy *iphy,
	काष्ठा sci_sas_address *sas_address);

व्योम sci_phy_get_protocols(
	काष्ठा isci_phy *iphy,
	काष्ठा sci_phy_proto *protocols);
क्रमागत sas_linkrate sci_phy_linkrate(काष्ठा isci_phy *iphy);

काष्ठा isci_host;
व्योम isci_phy_init(काष्ठा isci_phy *iphy, काष्ठा isci_host *ihost, पूर्णांक index);
पूर्णांक isci_phy_control(काष्ठा asd_sas_phy *phy, क्रमागत phy_func func, व्योम *buf);

#पूर्ण_अगर /* !defined(_ISCI_PHY_H_) */

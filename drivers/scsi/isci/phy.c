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

#समावेश "isci.h"
#समावेश "host.h"
#समावेश "phy.h"
#समावेश "scu_event_codes.h"
#समावेश "probe_roms.h"

#अघोषित C
#घोषणा C(a) (#a)
अटल स्थिर अक्षर *phy_state_name(क्रमागत sci_phy_states state)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = PHY_STATES;

	वापस strings[state];
पूर्ण
#अघोषित C

/* Maximum arbitration रुको समय in micro-seconds */
#घोषणा SCIC_SDS_PHY_MAX_ARBITRATION_WAIT_TIME  (700)

क्रमागत sas_linkrate sci_phy_linkrate(काष्ठा isci_phy *iphy)
अणु
	वापस iphy->max_negotiated_speed;
पूर्ण

अटल काष्ठा isci_host *phy_to_host(काष्ठा isci_phy *iphy)
अणु
	काष्ठा isci_phy *table = iphy - iphy->phy_index;
	काष्ठा isci_host *ihost = container_of(table, typeof(*ihost), phys[0]);

	वापस ihost;
पूर्ण

अटल काष्ठा device *sciphy_to_dev(काष्ठा isci_phy *iphy)
अणु
	वापस &phy_to_host(iphy)->pdev->dev;
पूर्ण

अटल क्रमागत sci_status
sci_phy_transport_layer_initialization(काष्ठा isci_phy *iphy,
				       काष्ठा scu_transport_layer_रेजिस्टरs __iomem *reg)
अणु
	u32 tl_control;

	iphy->transport_layer_रेजिस्टरs = reg;

	ग_लिखोl(SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX,
		&iphy->transport_layer_रेजिस्टरs->stp_rni);

	/*
	 * Hardware team recommends that we enable the STP prefetch क्रम all
	 * transports
	 */
	tl_control = पढ़ोl(&iphy->transport_layer_रेजिस्टरs->control);
	tl_control |= SCU_TLCR_GEN_BIT(STP_WRITE_DATA_PREFETCH);
	ग_लिखोl(tl_control, &iphy->transport_layer_रेजिस्टरs->control);

	वापस SCI_SUCCESS;
पूर्ण

अटल क्रमागत sci_status
sci_phy_link_layer_initialization(काष्ठा isci_phy *iphy,
				  काष्ठा scu_link_layer_रेजिस्टरs __iomem *llr)
अणु
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;
	काष्ठा sci_phy_user_params *phy_user;
	काष्ठा sci_phy_oem_params *phy_oem;
	पूर्णांक phy_idx = iphy->phy_index;
	काष्ठा sci_phy_cap phy_cap;
	u32 phy_configuration;
	u32 parity_check = 0;
	u32 parity_count = 0;
	u32 llctl, link_rate;
	u32 clksm_value = 0;
	u32 sp_समयouts = 0;

	phy_user = &ihost->user_parameters.phys[phy_idx];
	phy_oem = &ihost->oem_parameters.phys[phy_idx];
	iphy->link_layer_रेजिस्टरs = llr;

	/* Set our IDENTIFY frame data */
	#घोषणा SCI_END_DEVICE 0x01

	ग_लिखोl(SCU_SAS_TIID_GEN_BIT(SMP_INITIATOR) |
	       SCU_SAS_TIID_GEN_BIT(SSP_INITIATOR) |
	       SCU_SAS_TIID_GEN_BIT(STP_INITIATOR) |
	       SCU_SAS_TIID_GEN_BIT(DA_SATA_HOST) |
	       SCU_SAS_TIID_GEN_VAL(DEVICE_TYPE, SCI_END_DEVICE),
	       &llr->transmit_identअगरication);

	/* Write the device SAS Address */
	ग_लिखोl(0xFEDCBA98, &llr->sas_device_name_high);
	ग_लिखोl(phy_idx, &llr->sas_device_name_low);

	/* Write the source SAS Address */
	ग_लिखोl(phy_oem->sas_address.high, &llr->source_sas_address_high);
	ग_लिखोl(phy_oem->sas_address.low, &llr->source_sas_address_low);

	/* Clear and Set the PHY Identअगरier */
	ग_लिखोl(0, &llr->identअगरy_frame_phy_id);
	ग_लिखोl(SCU_SAS_TIPID_GEN_VALUE(ID, phy_idx), &llr->identअगरy_frame_phy_id);

	/* Change the initial state of the phy configuration रेजिस्टर */
	phy_configuration = पढ़ोl(&llr->phy_configuration);

	/* Hold OOB state machine in reset */
	phy_configuration |=  SCU_SAS_PCFG_GEN_BIT(OOB_RESET);
	ग_लिखोl(phy_configuration, &llr->phy_configuration);

	/* Configure the SNW capabilities */
	phy_cap.all = 0;
	phy_cap.start = 1;
	phy_cap.gen3_no_ssc = 1;
	phy_cap.gen2_no_ssc = 1;
	phy_cap.gen1_no_ssc = 1;
	अगर (ihost->oem_parameters.controller.करो_enable_ssc) अणु
		काष्ठा scu_afe_रेजिस्टरs __iomem *afe = &ihost->scu_रेजिस्टरs->afe;
		काष्ठा scu_afe_transceiver __iomem *xcvr = &afe->scu_afe_xcvr[phy_idx];
		काष्ठा isci_pci_info *pci_info = to_pci_info(ihost->pdev);
		bool en_sas = false;
		bool en_sata = false;
		u32 sas_type = 0;
		u32 sata_spपढ़ो = 0x2;
		u32 sas_spपढ़ो = 0x2;

		phy_cap.gen3_ssc = 1;
		phy_cap.gen2_ssc = 1;
		phy_cap.gen1_ssc = 1;

		अगर (pci_info->orom->hdr.version < ISCI_ROM_VER_1_1)
			en_sas = en_sata = true;
		अन्यथा अणु
			sata_spपढ़ो = ihost->oem_parameters.controller.ssc_sata_tx_spपढ़ो_level;
			sas_spपढ़ो = ihost->oem_parameters.controller.ssc_sas_tx_spपढ़ो_level;

			अगर (sata_spपढ़ो)
				en_sata = true;

			अगर (sas_spपढ़ो) अणु
				en_sas = true;
				sas_type = ihost->oem_parameters.controller.ssc_sas_tx_type;
			पूर्ण

		पूर्ण

		अगर (en_sas) अणु
			u32 reg;

			reg = पढ़ोl(&xcvr->afe_xcvr_control0);
			reg |= (0x00100000 | (sas_type << 19));
			ग_लिखोl(reg, &xcvr->afe_xcvr_control0);

			reg = पढ़ोl(&xcvr->afe_tx_ssc_control);
			reg |= sas_spपढ़ो << 8;
			ग_लिखोl(reg, &xcvr->afe_tx_ssc_control);
		पूर्ण

		अगर (en_sata) अणु
			u32 reg;

			reg = पढ़ोl(&xcvr->afe_tx_ssc_control);
			reg |= sata_spपढ़ो;
			ग_लिखोl(reg, &xcvr->afe_tx_ssc_control);

			reg = पढ़ोl(&llr->stp_control);
			reg |= 1 << 12;
			ग_लिखोl(reg, &llr->stp_control);
		पूर्ण
	पूर्ण

	/* The SAS specअगरication indicates that the phy_capabilities that
	 * are transmitted shall have an even parity.  Calculate the parity.
	 */
	parity_check = phy_cap.all;
	जबतक (parity_check != 0) अणु
		अगर (parity_check & 0x1)
			parity_count++;
		parity_check >>= 1;
	पूर्ण

	/* If parity indicates there are an odd number of bits set, then
	 * set the parity bit to 1 in the phy capabilities.
	 */
	अगर ((parity_count % 2) != 0)
		phy_cap.parity = 1;

	ग_लिखोl(phy_cap.all, &llr->phy_capabilities);

	/* Set the enable spinup period but disable the ability to send
	 * notअगरy enable spinup
	 */
	ग_लिखोl(SCU_ENSPINUP_GEN_VAL(COUNT,
			phy_user->notअगरy_enable_spin_up_insertion_frequency),
		&llr->notअगरy_enable_spinup_control);

	/* Write the ALIGN Insertion Ferequency क्रम connected phy and
	 * inpendent of connected state
	 */
	clksm_value = SCU_ALIGN_INSERTION_FREQUENCY_GEN_VAL(CONNECTED,
			phy_user->in_connection_align_insertion_frequency);

	clksm_value |= SCU_ALIGN_INSERTION_FREQUENCY_GEN_VAL(GENERAL,
			phy_user->align_insertion_frequency);

	ग_लिखोl(clksm_value, &llr->घड़ी_skew_management);

	अगर (is_c0(ihost->pdev) || is_c1(ihost->pdev)) अणु
		ग_लिखोl(0x04210400, &llr->afe_lookup_table_control);
		ग_लिखोl(0x020A7C05, &llr->sas_primitive_समयout);
	पूर्ण अन्यथा
		ग_लिखोl(0x02108421, &llr->afe_lookup_table_control);

	llctl = SCU_SAS_LLCTL_GEN_VAL(NO_OUTBOUND_TASK_TIMEOUT,
		(u8)ihost->user_parameters.no_outbound_task_समयout);

	चयन (phy_user->max_speed_generation) अणु
	हाल SCIC_SDS_PARM_GEN3_SPEED:
		link_rate = SCU_SAS_LINK_LAYER_CONTROL_MAX_LINK_RATE_GEN3;
		अवरोध;
	हाल SCIC_SDS_PARM_GEN2_SPEED:
		link_rate = SCU_SAS_LINK_LAYER_CONTROL_MAX_LINK_RATE_GEN2;
		अवरोध;
	शेष:
		link_rate = SCU_SAS_LINK_LAYER_CONTROL_MAX_LINK_RATE_GEN1;
		अवरोध;
	पूर्ण
	llctl |= SCU_SAS_LLCTL_GEN_VAL(MAX_LINK_RATE, link_rate);
	ग_लिखोl(llctl, &llr->link_layer_control);

	sp_समयouts = पढ़ोl(&llr->sas_phy_समयouts);

	/* Clear the शेष 0x36 (54us) RATE_CHANGE समयout value. */
	sp_समयouts &= ~SCU_SAS_PHYTOV_GEN_VAL(RATE_CHANGE, 0xFF);

	/* Set RATE_CHANGE समयout value to 0x3B (59us).  This ensures SCU can
	 * lock with 3Gb drive when SCU max rate is set to 1.5Gb.
	 */
	sp_समयouts |= SCU_SAS_PHYTOV_GEN_VAL(RATE_CHANGE, 0x3B);

	ग_लिखोl(sp_समयouts, &llr->sas_phy_समयouts);

	अगर (is_a2(ihost->pdev)) अणु
		/* Program the max ARB समय क्रम the PHY to 700us so we
		 * पूर्णांकer-operate with the PMC expander which shuts करोwn
		 * PHYs अगर the expander PHY generates too many अवरोधs.
		 * This समय value will guarantee that the initiator PHY
		 * will generate the अवरोध.
		 */
		ग_लिखोl(SCIC_SDS_PHY_MAX_ARBITRATION_WAIT_TIME,
		       &llr->maximum_arbitration_रुको_समयr_समयout);
	पूर्ण

	/* Disable link layer hang detection, rely on the OS समयout क्रम
	 * I/O समयouts.
	 */
	ग_लिखोl(0, &llr->link_layer_hang_detection_समयout);

	/* We can निकास the initial state to the stopped state */
	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);

	वापस SCI_SUCCESS;
पूर्ण

अटल व्योम phy_sata_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा isci_phy *iphy = container_of(पंचांगr, typeof(*iphy), sata_समयr);
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	dev_dbg(sciphy_to_dev(iphy),
		 "%s: SCIC SDS Phy 0x%p did not receive signature fis before "
		 "timeout.\n",
		 __func__,
		 iphy);

	sci_change_state(&iphy->sm, SCI_PHY_STARTING);
करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

/**
 * phy_get_non_dummy_port() - This method वापसs the port currently containing
 * this phy. If the phy is currently contained by the dummy port, then the phy
 * is considered to not be part of a port.
 *
 * @iphy: This parameter specअगरies the phy क्रम which to retrieve the
 *    containing port.
 *
 * This method वापसs a handle to a port that contains the supplied phy.
 * शून्य This value is वापसed अगर the phy is not part of a real
 * port (i.e. it's contained in the dummy port). !शून्य All other
 * values indicate a handle/poपूर्णांकer to the port containing the phy.
 */
काष्ठा isci_port *phy_get_non_dummy_port(काष्ठा isci_phy *iphy)
अणु
	काष्ठा isci_port *iport = iphy->owning_port;

	अगर (iport->physical_port_index == SCIC_SDS_DUMMY_PORT)
		वापस शून्य;

	वापस iphy->owning_port;
पूर्ण

/*
 * sci_phy_set_port() - This method will assign a port to the phy object.
 */
व्योम sci_phy_set_port(
	काष्ठा isci_phy *iphy,
	काष्ठा isci_port *iport)
अणु
	iphy->owning_port = iport;

	अगर (iphy->bcn_received_जबतक_port_unasचिन्हित) अणु
		iphy->bcn_received_जबतक_port_unasचिन्हित = false;
		sci_port_broadcast_change_received(iphy->owning_port, iphy);
	पूर्ण
पूर्ण

क्रमागत sci_status sci_phy_initialize(काष्ठा isci_phy *iphy,
				   काष्ठा scu_transport_layer_रेजिस्टरs __iomem *tl,
				   काष्ठा scu_link_layer_रेजिस्टरs __iomem *ll)
अणु
	/* Perfrom the initialization of the TL hardware */
	sci_phy_transport_layer_initialization(iphy, tl);

	/* Perofrm the initialization of the PE hardware */
	sci_phy_link_layer_initialization(iphy, ll);

	/* There is nothing that needs to be करोne in this state just
	 * transition to the stopped state
	 */
	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);

	वापस SCI_SUCCESS;
पूर्ण

/**
 * sci_phy_setup_transport() - This method assigns the direct attached device ID क्रम this phy.
 *
 * @iphy: The phy क्रम which the direct attached device id is to
 *       be asचिन्हित.
 * @device_id: The direct attached device ID to assign to the phy.
 *       This will either be the RNi क्रम the device or an invalid RNi अगर there
 *       is no current device asचिन्हित to the phy.
 */
व्योम sci_phy_setup_transport(काष्ठा isci_phy *iphy, u32 device_id)
अणु
	u32 tl_control;

	ग_लिखोl(device_id, &iphy->transport_layer_रेजिस्टरs->stp_rni);

	/*
	 * The पढ़ो should guarantee that the first ग_लिखो माला_लो posted
	 * beक्रमe the next ग_लिखो
	 */
	tl_control = पढ़ोl(&iphy->transport_layer_रेजिस्टरs->control);
	tl_control |= SCU_TLCR_GEN_BIT(CLEAR_TCI_NCQ_MAPPING_TABLE);
	ग_लिखोl(tl_control, &iphy->transport_layer_रेजिस्टरs->control);
पूर्ण

अटल व्योम sci_phy_suspend(काष्ठा isci_phy *iphy)
अणु
	u32 scu_sas_pcfg_value;

	scu_sas_pcfg_value =
		पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
	scu_sas_pcfg_value |= SCU_SAS_PCFG_GEN_BIT(SUSPEND_PROTOCOL_ENGINE);
	ग_लिखोl(scu_sas_pcfg_value,
		&iphy->link_layer_रेजिस्टरs->phy_configuration);

	sci_phy_setup_transport(iphy, SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX);
पूर्ण

व्योम sci_phy_resume(काष्ठा isci_phy *iphy)
अणु
	u32 scu_sas_pcfg_value;

	scu_sas_pcfg_value =
		पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
	scu_sas_pcfg_value &= ~SCU_SAS_PCFG_GEN_BIT(SUSPEND_PROTOCOL_ENGINE);
	ग_लिखोl(scu_sas_pcfg_value,
		&iphy->link_layer_रेजिस्टरs->phy_configuration);
पूर्ण

व्योम sci_phy_get_sas_address(काष्ठा isci_phy *iphy, काष्ठा sci_sas_address *sas)
अणु
	sas->high = पढ़ोl(&iphy->link_layer_रेजिस्टरs->source_sas_address_high);
	sas->low = पढ़ोl(&iphy->link_layer_रेजिस्टरs->source_sas_address_low);
पूर्ण

व्योम sci_phy_get_attached_sas_address(काष्ठा isci_phy *iphy, काष्ठा sci_sas_address *sas)
अणु
	काष्ठा sas_identअगरy_frame *iaf;

	iaf = &iphy->frame_rcvd.iaf;
	स_नकल(sas, iaf->sas_addr, SAS_ADDR_SIZE);
पूर्ण

व्योम sci_phy_get_protocols(काष्ठा isci_phy *iphy, काष्ठा sci_phy_proto *proto)
अणु
	proto->all = पढ़ोl(&iphy->link_layer_रेजिस्टरs->transmit_identअगरication);
पूर्ण

क्रमागत sci_status sci_phy_start(काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;

	अगर (state != SCI_PHY_STOPPED) अणु
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_change_state(&iphy->sm, SCI_PHY_STARTING);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_phy_stop(काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_PHY_SUB_INITIAL:
	हाल SCI_PHY_SUB_AWAIT_OSSP_EN:
	हाल SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
	हाल SCI_PHY_SUB_AWAIT_SAS_POWER:
	हाल SCI_PHY_SUB_AWAIT_SATA_POWER:
	हाल SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
	हाल SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
	हाल SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
	हाल SCI_PHY_SUB_FINAL:
	हाल SCI_PHY_READY:
		अवरोध;
	शेष:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_change_state(&iphy->sm, SCI_PHY_STOPPED);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_phy_reset(काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;

	अगर (state != SCI_PHY_READY) अणु
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	sci_change_state(&iphy->sm, SCI_PHY_RESETTING);
	वापस SCI_SUCCESS;
पूर्ण

क्रमागत sci_status sci_phy_consume_घातer_handler(काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_PHY_SUB_AWAIT_SAS_POWER: अणु
		u32 enable_spinup;

		enable_spinup = पढ़ोl(&iphy->link_layer_रेजिस्टरs->notअगरy_enable_spinup_control);
		enable_spinup |= SCU_ENSPINUP_GEN_BIT(ENABLE);
		ग_लिखोl(enable_spinup, &iphy->link_layer_रेजिस्टरs->notअगरy_enable_spinup_control);

		/* Change state to the final state this substate machine has run to completion */
		sci_change_state(&iphy->sm, SCI_PHY_SUB_FINAL);

		वापस SCI_SUCCESS;
	पूर्ण
	हाल SCI_PHY_SUB_AWAIT_SATA_POWER: अणु
		u32 scu_sas_pcfg_value;

		/* Release the spinup hold state and reset the OOB state machine */
		scu_sas_pcfg_value =
			पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
		scu_sas_pcfg_value &=
			~(SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOLD) | SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE));
		scu_sas_pcfg_value |= SCU_SAS_PCFG_GEN_BIT(OOB_RESET);
		ग_लिखोl(scu_sas_pcfg_value,
			&iphy->link_layer_रेजिस्टरs->phy_configuration);

		/* Now restart the OOB operation */
		scu_sas_pcfg_value &= ~SCU_SAS_PCFG_GEN_BIT(OOB_RESET);
		scu_sas_pcfg_value |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE);
		ग_लिखोl(scu_sas_pcfg_value,
			&iphy->link_layer_रेजिस्टरs->phy_configuration);

		/* Change state to the final state this substate machine has run to completion */
		sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_PHY_EN);

		वापस SCI_SUCCESS;
	पूर्ण
	शेष:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

अटल व्योम sci_phy_start_sas_link_training(काष्ठा isci_phy *iphy)
अणु
	/* जारी the link training क्रम the phy as अगर it were a SAS PHY
	 * instead of a SATA PHY. This is करोne because the completion queue had a SAS
	 * PHY DETECTED event when the state machine was expecting a SATA PHY event.
	 */
	u32 phy_control;

	phy_control = पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
	phy_control |= SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOLD);
	ग_लिखोl(phy_control,
	       &iphy->link_layer_रेजिस्टरs->phy_configuration);

	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SAS_SPEED_EN);

	iphy->protocol = SAS_PROTOCOL_SSP;
पूर्ण

अटल व्योम sci_phy_start_sata_link_training(काष्ठा isci_phy *iphy)
अणु
	/* This method जारीs the link training क्रम the phy as अगर it were a SATA PHY
	 * instead of a SAS PHY.  This is करोne because the completion queue had a SATA
	 * SPINUP HOLD event when the state machine was expecting a SAS PHY event. none
	 */
	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_POWER);

	iphy->protocol = SAS_PROTOCOL_SATA;
पूर्ण

/**
 * sci_phy_complete_link_training - perक्रमm processing common to
 *    all protocols upon completion of link training.
 * @iphy: This parameter specअगरies the phy object क्रम which link training
 *    has completed.
 * @max_link_rate: This parameter specअगरies the maximum link rate to be
 *    associated with this phy.
 * @next_state: This parameter specअगरies the next state क्रम the phy's starting
 *    sub-state machine.
 *
 */
अटल व्योम sci_phy_complete_link_training(काष्ठा isci_phy *iphy,
					   क्रमागत sas_linkrate max_link_rate,
					   u32 next_state)
अणु
	iphy->max_negotiated_speed = max_link_rate;

	sci_change_state(&iphy->sm, next_state);
पूर्ण

अटल स्थिर अक्षर *phy_event_name(u32 event_code)
अणु
	चयन (scu_get_event_code(event_code)) अणु
	हाल SCU_EVENT_PORT_SELECTOR_DETECTED:
		वापस "port selector";
	हाल SCU_EVENT_SENT_PORT_SELECTION:
		वापस "port selection";
	हाल SCU_EVENT_HARD_RESET_TRANSMITTED:
		वापस "tx hard reset";
	हाल SCU_EVENT_HARD_RESET_RECEIVED:
		वापस "rx hard reset";
	हाल SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT:
		वापस "identify timeout";
	हाल SCU_EVENT_LINK_FAILURE:
		वापस "link fail";
	हाल SCU_EVENT_SATA_SPINUP_HOLD:
		वापस "sata spinup hold";
	हाल SCU_EVENT_SAS_15_SSC:
	हाल SCU_EVENT_SAS_15:
		वापस "sas 1.5";
	हाल SCU_EVENT_SAS_30_SSC:
	हाल SCU_EVENT_SAS_30:
		वापस "sas 3.0";
	हाल SCU_EVENT_SAS_60_SSC:
	हाल SCU_EVENT_SAS_60:
		वापस "sas 6.0";
	हाल SCU_EVENT_SATA_15_SSC:
	हाल SCU_EVENT_SATA_15:
		वापस "sata 1.5";
	हाल SCU_EVENT_SATA_30_SSC:
	हाल SCU_EVENT_SATA_30:
		वापस "sata 3.0";
	हाल SCU_EVENT_SATA_60_SSC:
	हाल SCU_EVENT_SATA_60:
		वापस "sata 6.0";
	हाल SCU_EVENT_SAS_PHY_DETECTED:
		वापस "sas detect";
	हाल SCU_EVENT_SATA_PHY_DETECTED:
		वापस "sata detect";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

#घोषणा phy_event_dbg(iphy, state, code) \
	dev_dbg(sciphy_to_dev(iphy), "phy-%d:%d: %s event: %s (%x)\n", \
		phy_to_host(iphy)->id, iphy->phy_index, \
		phy_state_name(state), phy_event_name(code), code)

#घोषणा phy_event_warn(iphy, state, code) \
	dev_warn(sciphy_to_dev(iphy), "phy-%d:%d: %s event: %s (%x)\n", \
		phy_to_host(iphy)->id, iphy->phy_index, \
		phy_state_name(state), phy_event_name(code), code)


अटल व्योम scu_link_layer_set_txcomsas_समयout(काष्ठा isci_phy *iphy, u32 समयout)
अणु
	u32 val;

	/* Extend समयout */
	val = पढ़ोl(&iphy->link_layer_रेजिस्टरs->transmit_comsas_संकेत);
	val &= ~SCU_SAS_LLTXCOMSAS_GEN_VAL(NEGTIME, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_MASK);
	val |= SCU_SAS_LLTXCOMSAS_GEN_VAL(NEGTIME, समयout);

	ग_लिखोl(val, &iphy->link_layer_रेजिस्टरs->transmit_comsas_संकेत);
पूर्ण

क्रमागत sci_status sci_phy_event_handler(काष्ठा isci_phy *iphy, u32 event_code)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_PHY_SUB_AWAIT_OSSP_EN:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_SAS_PHY_DETECTED:
			sci_phy_start_sas_link_training(iphy);
			iphy->is_in_link_training = true;
			अवरोध;
		हाल SCU_EVENT_SATA_SPINUP_HOLD:
			sci_phy_start_sata_link_training(iphy);
			iphy->is_in_link_training = true;
			अवरोध;
		हाल SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT:
		       /* Extend समयout value */
		       scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_EXTENDED);

		       /* Start the oob/sn state machine over again */
		       sci_change_state(&iphy->sm, SCI_PHY_STARTING);
		       अवरोध;
		शेष:
			phy_event_dbg(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SAS_SPEED_EN:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_SAS_PHY_DETECTED:
			/*
			 * Why is this being reported again by the controller?
			 * We would re-enter this state so just stay here */
			अवरोध;
		हाल SCU_EVENT_SAS_15:
		हाल SCU_EVENT_SAS_15_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_1_5_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			अवरोध;
		हाल SCU_EVENT_SAS_30:
		हाल SCU_EVENT_SAS_30_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_3_0_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			अवरोध;
		हाल SCU_EVENT_SAS_60:
		हाल SCU_EVENT_SAS_60_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_6_0_GBPS,
						       SCI_PHY_SUB_AWAIT_IAF_UF);
			अवरोध;
		हाल SCU_EVENT_SATA_SPINUP_HOLD:
			/*
			 * We were करोing SAS PHY link training and received a SATA PHY event
			 * जारी OOB/SN as अगर this were a SATA PHY */
			sci_phy_start_sata_link_training(iphy);
			अवरोध;
		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT:
		       /* Extend the समयout value */
		       scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_EXTENDED);

		       /* Start the oob/sn state machine over again */
		       sci_change_state(&iphy->sm, SCI_PHY_STARTING);
		       अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_IAF_UF:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_SAS_PHY_DETECTED:
			/* Backup the state machine */
			sci_phy_start_sas_link_training(iphy);
			अवरोध;
		हाल SCU_EVENT_SATA_SPINUP_HOLD:
			/* We were करोing SAS PHY link training and received a
			 * SATA PHY event जारी OOB/SN as अगर this were a
			 * SATA PHY
			 */
			sci_phy_start_sata_link_training(iphy);
			अवरोध;
		हाल SCU_EVENT_RECEIVED_IDENTIFY_TIMEOUT:
			/* Extend the समयout value */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_EXTENDED);

			/* Start the oob/sn state machine over again */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_LINK_FAILURE:
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);
			fallthrough;
		हाल SCU_EVENT_HARD_RESET_RECEIVED:
			/* Start the oob/sn state machine over again */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SAS_POWER:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SATA_POWER:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_SATA_SPINUP_HOLD:
			/* These events are received every 10ms and are
			 * expected जबतक in this state
			 */
			अवरोध;

		हाल SCU_EVENT_SAS_PHY_DETECTED:
			/* There has been a change in the phy type beक्रमe OOB/SN क्रम the
			 * SATA finished start करोwn the SAS link traning path.
			 */
			sci_phy_start_sas_link_training(iphy);
			अवरोध;

		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SATA_PHY_EN:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_SATA_SPINUP_HOLD:
			/* These events might be received since we करोnt know how many may be in
			 * the completion queue जबतक रुकोing क्रम घातer
			 */
			अवरोध;
		हाल SCU_EVENT_SATA_PHY_DETECTED:
			iphy->protocol = SAS_PROTOCOL_SATA;

			/* We have received the SATA PHY notअगरication change state */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_SPEED_EN);
			अवरोध;
		हाल SCU_EVENT_SAS_PHY_DETECTED:
			/* There has been a change in the phy type beक्रमe OOB/SN क्रम the
			 * SATA finished start करोwn the SAS link traning path.
			 */
			sci_phy_start_sas_link_training(iphy);
			अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SATA_SPEED_EN:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_SATA_PHY_DETECTED:
			/*
			 * The hardware reports multiple SATA PHY detected events
			 * ignore the extras */
			अवरोध;
		हाल SCU_EVENT_SATA_15:
		हाल SCU_EVENT_SATA_15_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_1_5_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			अवरोध;
		हाल SCU_EVENT_SATA_30:
		हाल SCU_EVENT_SATA_30_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_3_0_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			अवरोध;
		हाल SCU_EVENT_SATA_60:
		हाल SCU_EVENT_SATA_60_SSC:
			sci_phy_complete_link_training(iphy, SAS_LINK_RATE_6_0_GBPS,
						       SCI_PHY_SUB_AWAIT_SIG_FIS_UF);
			अवरोध;
		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_SAS_PHY_DETECTED:
			/*
			 * There has been a change in the phy type beक्रमe OOB/SN क्रम the
			 * SATA finished start करोwn the SAS link traning path. */
			sci_phy_start_sas_link_training(iphy);
			अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण

		वापस SCI_SUCCESS;
	हाल SCI_PHY_SUB_AWAIT_SIG_FIS_UF:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_SATA_PHY_DETECTED:
			/* Backup the state machine */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_SPEED_EN);
			अवरोध;

		हाल SCU_EVENT_LINK_FAILURE:
			/* Change the समयout value to शेष */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;

		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_READY:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_LINK_FAILURE:
			/* Set शेष समयout */
			scu_link_layer_set_txcomsas_समयout(iphy, SCU_SAS_LINK_LAYER_TXCOMSAS_NEGTIME_DEFAULT);

			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		हाल SCU_EVENT_BROADCAST_CHANGE:
		हाल SCU_EVENT_BROADCAST_SES:
		हाल SCU_EVENT_BROADCAST_RESERVED0:
		हाल SCU_EVENT_BROADCAST_RESERVED1:
		हाल SCU_EVENT_BROADCAST_EXPANDER:
		हाल SCU_EVENT_BROADCAST_AEN:
			/* Broadcast change received. Notअगरy the port. */
			अगर (phy_get_non_dummy_port(iphy) != शून्य)
				sci_port_broadcast_change_received(iphy->owning_port, iphy);
			अन्यथा
				iphy->bcn_received_जबतक_port_unasचिन्हित = true;
			अवरोध;
		हाल SCU_EVENT_BROADCAST_RESERVED3:
		हाल SCU_EVENT_BROADCAST_RESERVED4:
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE_INVALID_STATE;
		पूर्ण
		वापस SCI_SUCCESS;
	हाल SCI_PHY_RESETTING:
		चयन (scu_get_event_code(event_code)) अणु
		हाल SCU_EVENT_HARD_RESET_TRANSMITTED:
			/* Link failure change state back to the starting state */
			sci_change_state(&iphy->sm, SCI_PHY_STARTING);
			अवरोध;
		शेष:
			phy_event_warn(iphy, state, event_code);
			वापस SCI_FAILURE_INVALID_STATE;
		पूर्ण
		वापस SCI_SUCCESS;
	शेष:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_phy_frame_handler(काष्ठा isci_phy *iphy, u32 frame_index)
अणु
	क्रमागत sci_phy_states state = iphy->sm.current_state_id;
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;
	क्रमागत sci_status result;
	अचिन्हित दीर्घ flags;

	चयन (state) अणु
	हाल SCI_PHY_SUB_AWAIT_IAF_UF: अणु
		u32 *frame_words;
		काष्ठा sas_identअगरy_frame iaf;

		result = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								  frame_index,
								  (व्योम **)&frame_words);

		अगर (result != SCI_SUCCESS)
			वापस result;

		sci_swab32_cpy(&iaf, frame_words, माप(iaf) / माप(u32));
		अगर (iaf.frame_type == 0) अणु
			u32 state;

			spin_lock_irqsave(&iphy->sas_phy.frame_rcvd_lock, flags);
			स_नकल(&iphy->frame_rcvd.iaf, &iaf, माप(iaf));
			spin_unlock_irqrestore(&iphy->sas_phy.frame_rcvd_lock, flags);
			अगर (iaf.smp_tport) अणु
				/* We got the IAF क्रम an expander PHY go to the final
				 * state since there are no घातer requirements क्रम
				 * expander phys.
				 */
				state = SCI_PHY_SUB_FINAL;
			पूर्ण अन्यथा अणु
				/* We got the IAF we can now go to the aरुको spinup
				 * semaphore state
				 */
				state = SCI_PHY_SUB_AWAIT_SAS_POWER;
			पूर्ण
			sci_change_state(&iphy->sm, state);
			result = SCI_SUCCESS;
		पूर्ण अन्यथा
			dev_warn(sciphy_to_dev(iphy),
				"%s: PHY starting substate machine received "
				"unexpected frame id %x\n",
				__func__, frame_index);

		sci_controller_release_frame(ihost, frame_index);
		वापस result;
	पूर्ण
	हाल SCI_PHY_SUB_AWAIT_SIG_FIS_UF: अणु
		काष्ठा dev_to_host_fis *frame_header;
		u32 *fis_frame_data;

		result = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								  frame_index,
								  (व्योम **)&frame_header);

		अगर (result != SCI_SUCCESS)
			वापस result;

		अगर ((frame_header->fis_type == FIS_REGD2H) &&
		    !(frame_header->status & ATA_BUSY)) अणु
			sci_unsolicited_frame_control_get_buffer(&ihost->uf_control,
								 frame_index,
								 (व्योम **)&fis_frame_data);

			spin_lock_irqsave(&iphy->sas_phy.frame_rcvd_lock, flags);
			sci_controller_copy_sata_response(&iphy->frame_rcvd.fis,
							  frame_header,
							  fis_frame_data);
			spin_unlock_irqrestore(&iphy->sas_phy.frame_rcvd_lock, flags);

			/* got IAF we can now go to the aरुको spinup semaphore state */
			sci_change_state(&iphy->sm, SCI_PHY_SUB_FINAL);

			result = SCI_SUCCESS;
		पूर्ण अन्यथा
			dev_warn(sciphy_to_dev(iphy),
				 "%s: PHY starting substate machine received "
				 "unexpected frame id %x\n",
				 __func__, frame_index);

		/* Regardless of the result we are करोne with this frame with it */
		sci_controller_release_frame(ihost, frame_index);

		वापस result;
	पूर्ण
	शेष:
		dev_dbg(sciphy_to_dev(iphy), "%s: in wrong state: %s\n",
			__func__, phy_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

पूर्ण

अटल व्योम sci_phy_starting_initial_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	/* This is just an temporary state go off to the starting state */
	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_OSSP_EN);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sas_घातer_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;

	sci_controller_घातer_control_queue_insert(ihost, iphy);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sas_घातer_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;

	sci_controller_घातer_control_queue_हटाओ(ihost, iphy);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_घातer_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;

	sci_controller_घातer_control_queue_insert(ihost, iphy);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_घातer_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_host *ihost = iphy->owning_port->owning_controller;

	sci_controller_घातer_control_queue_हटाओ(ihost, iphy);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_phy_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_mod_समयr(&iphy->sata_समयr, SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_phy_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_del_समयr(&iphy->sata_समयr);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_speed_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_mod_समयr(&iphy->sata_समयr, SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sata_speed_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_del_समयr(&iphy->sata_समयr);
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sig_fis_uf_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	अगर (sci_port_link_detected(iphy->owning_port, iphy)) अणु

		/*
		 * Clear the PE suspend condition so we can actually
		 * receive SIG FIS
		 * The hardware will not respond to the XRDY until the PE
		 * suspend condition is cleared.
		 */
		sci_phy_resume(iphy);

		sci_mod_समयr(&iphy->sata_समयr,
			      SCIC_SDS_SIGNATURE_FIS_TIMEOUT);
	पूर्ण अन्यथा
		iphy->is_in_link_training = false;
पूर्ण

अटल व्योम sci_phy_starting_aरुको_sig_fis_uf_substate_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_del_समयr(&iphy->sata_समयr);
पूर्ण

अटल व्योम sci_phy_starting_final_substate_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	/* State machine has run to completion so निकास out and change
	 * the base state machine to the पढ़ोy state
	 */
	sci_change_state(&iphy->sm, SCI_PHY_READY);
पूर्ण

/**
 * scu_link_layer_stop_protocol_engine()
 * @iphy: This is the काष्ठा isci_phy object to stop.
 *
 * This method will stop the काष्ठा isci_phy object. This करोes not reset the
 * protocol engine it just suspends it and places it in a state where it will
 * not cause the end device to घातer up. none
 */
अटल व्योम scu_link_layer_stop_protocol_engine(
	काष्ठा isci_phy *iphy)
अणु
	u32 scu_sas_pcfg_value;
	u32 enable_spinup_value;

	/* Suspend the protocol engine and place it in a sata spinup hold state */
	scu_sas_pcfg_value =
		पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
	scu_sas_pcfg_value |=
		(SCU_SAS_PCFG_GEN_BIT(OOB_RESET) |
		 SCU_SAS_PCFG_GEN_BIT(SUSPEND_PROTOCOL_ENGINE) |
		 SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOLD));
	ग_लिखोl(scu_sas_pcfg_value,
	       &iphy->link_layer_रेजिस्टरs->phy_configuration);

	/* Disable the notअगरy enable spinup primitives */
	enable_spinup_value = पढ़ोl(&iphy->link_layer_रेजिस्टरs->notअगरy_enable_spinup_control);
	enable_spinup_value &= ~SCU_ENSPINUP_GEN_BIT(ENABLE);
	ग_लिखोl(enable_spinup_value, &iphy->link_layer_रेजिस्टरs->notअगरy_enable_spinup_control);
पूर्ण

अटल व्योम scu_link_layer_start_oob(काष्ठा isci_phy *iphy)
अणु
	काष्ठा scu_link_layer_रेजिस्टरs __iomem *ll = iphy->link_layer_रेजिस्टरs;
	u32 val;

	/** Reset OOB sequence - start */
	val = पढ़ोl(&ll->phy_configuration);
	val &= ~(SCU_SAS_PCFG_GEN_BIT(OOB_RESET) |
		 SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE) |
		 SCU_SAS_PCFG_GEN_BIT(HARD_RESET));
	ग_लिखोl(val, &ll->phy_configuration);
	पढ़ोl(&ll->phy_configuration); /* flush */
	/** Reset OOB sequence - end */

	/** Start OOB sequence - start */
	val = पढ़ोl(&ll->phy_configuration);
	val |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE);
	ग_लिखोl(val, &ll->phy_configuration);
	पढ़ोl(&ll->phy_configuration); /* flush */
	/** Start OOB sequence - end */
पूर्ण

/**
 * scu_link_layer_tx_hard_reset()
 * @iphy: This is the काष्ठा isci_phy object to stop.
 *
 * This method will transmit a hard reset request on the specअगरied phy. The SCU
 * hardware requires that we reset the OOB state machine and set the hard reset
 * bit in the phy configuration रेजिस्टर. We then must start OOB over with the
 * hard reset bit set.
 */
अटल व्योम scu_link_layer_tx_hard_reset(
	काष्ठा isci_phy *iphy)
अणु
	u32 phy_configuration_value;

	/*
	 * SAS Phys must रुको क्रम the HARD_RESET_TX event notअगरication to transition
	 * to the starting state. */
	phy_configuration_value =
		पढ़ोl(&iphy->link_layer_रेजिस्टरs->phy_configuration);
	phy_configuration_value &= ~(SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE));
	phy_configuration_value |=
		(SCU_SAS_PCFG_GEN_BIT(HARD_RESET) |
		 SCU_SAS_PCFG_GEN_BIT(OOB_RESET));
	ग_लिखोl(phy_configuration_value,
	       &iphy->link_layer_रेजिस्टरs->phy_configuration);

	/* Now take the OOB state machine out of reset */
	phy_configuration_value |= SCU_SAS_PCFG_GEN_BIT(OOB_ENABLE);
	phy_configuration_value &= ~SCU_SAS_PCFG_GEN_BIT(OOB_RESET);
	ग_लिखोl(phy_configuration_value,
	       &iphy->link_layer_रेजिस्टरs->phy_configuration);
पूर्ण

अटल व्योम sci_phy_stopped_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_port *iport = iphy->owning_port;
	काष्ठा isci_host *ihost = iport->owning_controller;

	/*
	 * @toकरो We need to get to the controller to place this PE in a
	 * reset state
	 */
	sci_del_समयr(&iphy->sata_समयr);

	scu_link_layer_stop_protocol_engine(iphy);

	अगर (iphy->sm.previous_state_id != SCI_PHY_INITIAL)
		sci_controller_link_करोwn(ihost, phy_get_non_dummy_port(iphy), iphy);
पूर्ण

अटल व्योम sci_phy_starting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_port *iport = iphy->owning_port;
	काष्ठा isci_host *ihost = iport->owning_controller;

	scu_link_layer_stop_protocol_engine(iphy);
	scu_link_layer_start_oob(iphy);

	/* We करोn't know what kind of phy we are going to be just yet */
	iphy->protocol = SAS_PROTOCOL_NONE;
	iphy->bcn_received_जबतक_port_unasचिन्हित = false;

	अगर (iphy->sm.previous_state_id == SCI_PHY_READY)
		sci_controller_link_करोwn(ihost, phy_get_non_dummy_port(iphy), iphy);

	sci_change_state(&iphy->sm, SCI_PHY_SUB_INITIAL);
पूर्ण

अटल व्योम sci_phy_पढ़ोy_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);
	काष्ठा isci_port *iport = iphy->owning_port;
	काष्ठा isci_host *ihost = iport->owning_controller;

	sci_controller_link_up(ihost, phy_get_non_dummy_port(iphy), iphy);
पूर्ण

अटल व्योम sci_phy_पढ़ोy_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	sci_phy_suspend(iphy);
पूर्ण

अटल व्योम sci_phy_resetting_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_phy *iphy = container_of(sm, typeof(*iphy), sm);

	/* The phy is being reset, thereक्रमe deactivate it from the port.  In
	 * the resetting state we करोn't notअगरy the user regarding link up and
	 * link करोwn notअगरications
	 */
	sci_port_deactivate_phy(iphy->owning_port, iphy, false);

	अगर (iphy->protocol == SAS_PROTOCOL_SSP) अणु
		scu_link_layer_tx_hard_reset(iphy);
	पूर्ण अन्यथा अणु
		/* The SCU करोes not need to have a discrete reset state so
		 * just go back to the starting state.
		 */
		sci_change_state(&iphy->sm, SCI_PHY_STARTING);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sci_base_state sci_phy_state_table[] = अणु
	[SCI_PHY_INITIAL] = अणु पूर्ण,
	[SCI_PHY_STOPPED] = अणु
		.enter_state = sci_phy_stopped_state_enter,
	पूर्ण,
	[SCI_PHY_STARTING] = अणु
		.enter_state = sci_phy_starting_state_enter,
	पूर्ण,
	[SCI_PHY_SUB_INITIAL] = अणु
		.enter_state = sci_phy_starting_initial_substate_enter,
	पूर्ण,
	[SCI_PHY_SUB_AWAIT_OSSP_EN] = अणु पूर्ण,
	[SCI_PHY_SUB_AWAIT_SAS_SPEED_EN] = अणु पूर्ण,
	[SCI_PHY_SUB_AWAIT_IAF_UF] = अणु पूर्ण,
	[SCI_PHY_SUB_AWAIT_SAS_POWER] = अणु
		.enter_state = sci_phy_starting_aरुको_sas_घातer_substate_enter,
		.निकास_state  = sci_phy_starting_aरुको_sas_घातer_substate_निकास,
	पूर्ण,
	[SCI_PHY_SUB_AWAIT_SATA_POWER] = अणु
		.enter_state = sci_phy_starting_aरुको_sata_घातer_substate_enter,
		.निकास_state  = sci_phy_starting_aरुको_sata_घातer_substate_निकास
	पूर्ण,
	[SCI_PHY_SUB_AWAIT_SATA_PHY_EN] = अणु
		.enter_state = sci_phy_starting_aरुको_sata_phy_substate_enter,
		.निकास_state  = sci_phy_starting_aरुको_sata_phy_substate_निकास
	पूर्ण,
	[SCI_PHY_SUB_AWAIT_SATA_SPEED_EN] = अणु
		.enter_state = sci_phy_starting_aरुको_sata_speed_substate_enter,
		.निकास_state  = sci_phy_starting_aरुको_sata_speed_substate_निकास
	पूर्ण,
	[SCI_PHY_SUB_AWAIT_SIG_FIS_UF] = अणु
		.enter_state = sci_phy_starting_aरुको_sig_fis_uf_substate_enter,
		.निकास_state  = sci_phy_starting_aरुको_sig_fis_uf_substate_निकास
	पूर्ण,
	[SCI_PHY_SUB_FINAL] = अणु
		.enter_state = sci_phy_starting_final_substate_enter,
	पूर्ण,
	[SCI_PHY_READY] = अणु
		.enter_state = sci_phy_पढ़ोy_state_enter,
		.निकास_state = sci_phy_पढ़ोy_state_निकास,
	पूर्ण,
	[SCI_PHY_RESETTING] = अणु
		.enter_state = sci_phy_resetting_state_enter,
	पूर्ण,
	[SCI_PHY_FINAL] = अणु पूर्ण,
पूर्ण;

व्योम sci_phy_स्थिरruct(काष्ठा isci_phy *iphy,
			    काष्ठा isci_port *iport, u8 phy_index)
अणु
	sci_init_sm(&iphy->sm, sci_phy_state_table, SCI_PHY_INITIAL);

	/* Copy the rest of the input data to our locals */
	iphy->owning_port = iport;
	iphy->phy_index = phy_index;
	iphy->bcn_received_जबतक_port_unasचिन्हित = false;
	iphy->protocol = SAS_PROTOCOL_NONE;
	iphy->link_layer_रेजिस्टरs = शून्य;
	iphy->max_negotiated_speed = SAS_LINK_RATE_UNKNOWN;

	/* Create the SIGNATURE FIS Timeout समयr क्रम this phy */
	sci_init_समयr(&iphy->sata_समयr, phy_sata_समयout);
पूर्ण

व्योम isci_phy_init(काष्ठा isci_phy *iphy, काष्ठा isci_host *ihost, पूर्णांक index)
अणु
	काष्ठा sci_oem_params *oem = &ihost->oem_parameters;
	u64 sci_sas_addr;
	__be64 sas_addr;

	sci_sas_addr = oem->phys[index].sas_address.high;
	sci_sas_addr <<= 32;
	sci_sas_addr |= oem->phys[index].sas_address.low;
	sas_addr = cpu_to_be64(sci_sas_addr);
	स_नकल(iphy->sas_addr, &sas_addr, माप(sas_addr));

	iphy->sas_phy.enabled = 0;
	iphy->sas_phy.id = index;
	iphy->sas_phy.sas_addr = &iphy->sas_addr[0];
	iphy->sas_phy.frame_rcvd = (u8 *)&iphy->frame_rcvd;
	iphy->sas_phy.ha = &ihost->sas_ha;
	iphy->sas_phy.lldd_phy = iphy;
	iphy->sas_phy.enabled = 1;
	iphy->sas_phy.class = SAS;
	iphy->sas_phy.iproto = SAS_PROTOCOL_ALL;
	iphy->sas_phy.tproto = 0;
	iphy->sas_phy.type = PHY_TYPE_PHYSICAL;
	iphy->sas_phy.role = PHY_ROLE_INITIATOR;
	iphy->sas_phy.oob_mode = OOB_NOT_CONNECTED;
	iphy->sas_phy.linkrate = SAS_LINK_RATE_UNKNOWN;
	स_रखो(&iphy->frame_rcvd, 0, माप(iphy->frame_rcvd));
पूर्ण


/**
 * isci_phy_control() - This function is one of the SAS Doमुख्य Template
 *    functions. This is a phy management function.
 * @sas_phy: This parameter specअगरies the sphy being controlled.
 * @func: This parameter specअगरies the phy control function being invoked.
 * @buf: This parameter is specअगरic to the phy function being invoked.
 *
 * status, zero indicates success.
 */
पूर्णांक isci_phy_control(काष्ठा asd_sas_phy *sas_phy,
		     क्रमागत phy_func func,
		     व्योम *buf)
अणु
	पूर्णांक ret = 0;
	काष्ठा isci_phy *iphy = sas_phy->lldd_phy;
	काष्ठा asd_sas_port *port = sas_phy->port;
	काष्ठा isci_host *ihost = sas_phy->ha->lldd_ha;
	अचिन्हित दीर्घ flags;

	dev_dbg(&ihost->pdev->dev,
		"%s: phy %p; func %d; buf %p; isci phy %p, port %p\n",
		__func__, sas_phy, func, buf, iphy, port);

	चयन (func) अणु
	हाल PHY_FUNC_DISABLE:
		spin_lock_irqsave(&ihost->scic_lock, flags);
		scu_link_layer_start_oob(iphy);
		sci_phy_stop(iphy);
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
		अवरोध;

	हाल PHY_FUNC_LINK_RESET:
		spin_lock_irqsave(&ihost->scic_lock, flags);
		scu_link_layer_start_oob(iphy);
		sci_phy_stop(iphy);
		sci_phy_start(iphy);
		spin_unlock_irqrestore(&ihost->scic_lock, flags);
		अवरोध;

	हाल PHY_FUNC_HARD_RESET:
		अगर (!port)
			वापस -ENODEV;

		ret = isci_port_perक्रमm_hard_reset(ihost, port->lldd_port, iphy);

		अवरोध;
	हाल PHY_FUNC_GET_EVENTS: अणु
		काष्ठा scu_link_layer_रेजिस्टरs __iomem *r;
		काष्ठा sas_phy *phy = sas_phy->phy;

		r = iphy->link_layer_रेजिस्टरs;
		phy->running_disparity_error_count = पढ़ोl(&r->running_disparity_error_count);
		phy->loss_of_dword_sync_count = पढ़ोl(&r->loss_of_sync_error_count);
		phy->phy_reset_problem_count = पढ़ोl(&r->phy_reset_problem_count);
		phy->invalid_dword_count = पढ़ोl(&r->invalid_dword_counter);
		अवरोध;
	पूर्ण

	शेष:
		dev_dbg(&ihost->pdev->dev,
			   "%s: phy %p; func %d NOT IMPLEMENTED!\n",
			   __func__, sas_phy, func);
		ret = -ENOSYS;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

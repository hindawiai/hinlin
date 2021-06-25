<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "igc_mac.h"
#समावेश "igc_hw.h"

/**
 * igc_disable_pcie_master - Disables PCI-express master access
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Returns 0 (0) अगर successful, अन्यथा वापसs -10
 * (-IGC_ERR_MASTER_REQUESTS_PENDING) अगर master disable bit has not caused
 * the master requests to be disabled.
 *
 * Disables PCI-Express master access and verअगरies there are no pending
 * requests.
 */
s32 igc_disable_pcie_master(काष्ठा igc_hw *hw)
अणु
	s32 समयout = MASTER_DISABLE_TIMEOUT;
	s32 ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);
	ctrl |= IGC_CTRL_GIO_MASTER_DISABLE;
	wr32(IGC_CTRL, ctrl);

	जबतक (समयout) अणु
		अगर (!(rd32(IGC_STATUS) &
		    IGC_STATUS_GIO_MASTER_ENABLE))
			अवरोध;
		usleep_range(2000, 3000);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		hw_dbg("Master requests are pending.\n");
		ret_val = -IGC_ERR_MASTER_REQUESTS_PENDING;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_init_rx_addrs - Initialize receive addresses
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @rar_count: receive address रेजिस्टरs
 *
 * Setup the receive address रेजिस्टरs by setting the base receive address
 * रेजिस्टर to the devices MAC address and clearing all the other receive
 * address रेजिस्टरs to 0.
 */
व्योम igc_init_rx_addrs(काष्ठा igc_hw *hw, u16 rar_count)
अणु
	u8 mac_addr[ETH_ALEN] = अणु0पूर्ण;
	u32 i;

	/* Setup the receive address */
	hw_dbg("Programming MAC Address into RAR[0]\n");

	hw->mac.ops.rar_set(hw, hw->mac.addr, 0);

	/* Zero out the other (rar_entry_count - 1) receive addresses */
	hw_dbg("Clearing RAR[1-%u]\n", rar_count - 1);
	क्रम (i = 1; i < rar_count; i++)
		hw->mac.ops.rar_set(hw, mac_addr, i);
पूर्ण

/**
 * igc_set_fc_watermarks - Set flow control high/low watermarks
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Sets the flow control high/low threshold (watermark) रेजिस्टरs.  If
 * flow control XON frame transmission is enabled, then set XON frame
 * transmission as well.
 */
अटल s32 igc_set_fc_watermarks(काष्ठा igc_hw *hw)
अणु
	u32 fcrtl = 0, fcrth = 0;

	/* Set the flow control receive threshold रेजिस्टरs.  Normally,
	 * these रेजिस्टरs will be set to a शेष threshold that may be
	 * adjusted later by the driver's runसमय code.  However, अगर the
	 * ability to transmit छोड़ो frames is not enabled, then these
	 * रेजिस्टरs will be set to 0.
	 */
	अगर (hw->fc.current_mode & igc_fc_tx_छोड़ो) अणु
		/* We need to set up the Receive Threshold high and low water
		 * marks as well as (optionally) enabling the transmission of
		 * XON frames.
		 */
		fcrtl = hw->fc.low_water;
		अगर (hw->fc.send_xon)
			fcrtl |= IGC_FCRTL_XONE;

		fcrth = hw->fc.high_water;
	पूर्ण
	wr32(IGC_FCRTL, fcrtl);
	wr32(IGC_FCRTH, fcrth);

	वापस 0;
पूर्ण

/**
 * igc_setup_link - Setup flow control and link settings
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Determines which flow control settings to use, then configures flow
 * control.  Calls the appropriate media-specअगरic link configuration
 * function.  Assuming the adapter has a valid link partner, a valid link
 * should be established.  Assumes the hardware has previously been reset
 * and the transmitter and receiver are not enabled.
 */
s32 igc_setup_link(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = 0;

	/* In the हाल of the phy reset being blocked, we alपढ़ोy have a link.
	 * We करो not need to set it up again.
	 */
	अगर (igc_check_reset_block(hw))
		जाओ out;

	/* If requested flow control is set to शेष, set flow control
	 * to the both 'rx' and 'tx' छोड़ो frames.
	 */
	अगर (hw->fc.requested_mode == igc_fc_शेष)
		hw->fc.requested_mode = igc_fc_full;

	/* We want to save off the original Flow Control configuration just
	 * in हाल we get disconnected and then reconnected पूर्णांकo a dअगरferent
	 * hub or चयन with dअगरferent Flow Control capabilities.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	hw_dbg("After fix-ups FlowControl is now = %x\n", hw->fc.current_mode);

	/* Call the necessary media_type subroutine to configure the link. */
	ret_val = hw->mac.ops.setup_physical_पूर्णांकerface(hw);
	अगर (ret_val)
		जाओ out;

	/* Initialize the flow control address, type, and PAUSE समयr
	 * रेजिस्टरs to their शेष values.  This is करोne even अगर flow
	 * control is disabled, because it करोes not hurt anything to
	 * initialize these रेजिस्टरs.
	 */
	hw_dbg("Initializing the Flow Control address, type and timer regs\n");
	wr32(IGC_FCT, FLOW_CONTROL_TYPE);
	wr32(IGC_FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	wr32(IGC_FCAL, FLOW_CONTROL_ADDRESS_LOW);

	wr32(IGC_FCTTV, hw->fc.छोड़ो_समय);

	ret_val = igc_set_fc_watermarks(hw);

out:
	वापस ret_val;
पूर्ण

/**
 * igc_क्रमce_mac_fc - Force the MAC's flow control settings
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Force the MAC's flow control settings.  Sets the TFCE and RFCE bits in the
 * device control रेजिस्टर to reflect the adapter settings.  TFCE and RFCE
 * need to be explicitly set by software when a copper PHY is used because
 * स्वतःnegotiation is managed by the PHY rather than the MAC.  Software must
 * also configure these bits when link is क्रमced on a fiber connection.
 */
s32 igc_क्रमce_mac_fc(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);

	/* Because we didn't get link via the पूर्णांकernal स्वतः-negotiation
	 * mechanism (we either क्रमced link or we got link via PHY
	 * स्वतः-neg), we have to manually enable/disable transmit an
	 * receive flow control.
	 *
	 * The "Case" statement below enables/disable flow control
	 * according to the "hw->fc.current_mode" parameter.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो
	 *          frames but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          frames but we करो not receive छोड़ो frames).
	 *      3:  Both Rx and TX flow control (symmetric) is enabled.
	 *  other:  No other values should be possible at this poपूर्णांक.
	 */
	hw_dbg("hw->fc.current_mode = %u\n", hw->fc.current_mode);

	चयन (hw->fc.current_mode) अणु
	हाल igc_fc_none:
		ctrl &= (~(IGC_CTRL_TFCE | IGC_CTRL_RFCE));
		अवरोध;
	हाल igc_fc_rx_छोड़ो:
		ctrl &= (~IGC_CTRL_TFCE);
		ctrl |= IGC_CTRL_RFCE;
		अवरोध;
	हाल igc_fc_tx_छोड़ो:
		ctrl &= (~IGC_CTRL_RFCE);
		ctrl |= IGC_CTRL_TFCE;
		अवरोध;
	हाल igc_fc_full:
		ctrl |= (IGC_CTRL_TFCE | IGC_CTRL_RFCE);
		अवरोध;
	शेष:
		hw_dbg("Flow control param set incorrectly\n");
		ret_val = -IGC_ERR_CONFIG;
		जाओ out;
	पूर्ण

	wr32(IGC_CTRL, ctrl);

out:
	वापस ret_val;
पूर्ण

/**
 * igc_clear_hw_cntrs_base - Clear base hardware counters
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Clears the base hardware counters by पढ़ोing the counter रेजिस्टरs.
 */
व्योम igc_clear_hw_cntrs_base(काष्ठा igc_hw *hw)
अणु
	rd32(IGC_CRCERRS);
	rd32(IGC_MPC);
	rd32(IGC_SCC);
	rd32(IGC_ECOL);
	rd32(IGC_MCC);
	rd32(IGC_LATECOL);
	rd32(IGC_COLC);
	rd32(IGC_RERC);
	rd32(IGC_DC);
	rd32(IGC_RLEC);
	rd32(IGC_XONRXC);
	rd32(IGC_XONTXC);
	rd32(IGC_XOFFRXC);
	rd32(IGC_XOFFTXC);
	rd32(IGC_FCRUC);
	rd32(IGC_GPRC);
	rd32(IGC_BPRC);
	rd32(IGC_MPRC);
	rd32(IGC_GPTC);
	rd32(IGC_GORCL);
	rd32(IGC_GORCH);
	rd32(IGC_GOTCL);
	rd32(IGC_GOTCH);
	rd32(IGC_RNBC);
	rd32(IGC_RUC);
	rd32(IGC_RFC);
	rd32(IGC_ROC);
	rd32(IGC_RJC);
	rd32(IGC_TORL);
	rd32(IGC_TORH);
	rd32(IGC_TOTL);
	rd32(IGC_TOTH);
	rd32(IGC_TPR);
	rd32(IGC_TPT);
	rd32(IGC_MPTC);
	rd32(IGC_BPTC);

	rd32(IGC_PRC64);
	rd32(IGC_PRC127);
	rd32(IGC_PRC255);
	rd32(IGC_PRC511);
	rd32(IGC_PRC1023);
	rd32(IGC_PRC1522);
	rd32(IGC_PTC64);
	rd32(IGC_PTC127);
	rd32(IGC_PTC255);
	rd32(IGC_PTC511);
	rd32(IGC_PTC1023);
	rd32(IGC_PTC1522);

	rd32(IGC_ALGNERRC);
	rd32(IGC_RXERRC);
	rd32(IGC_TNCRS);
	rd32(IGC_HTDPMC);
	rd32(IGC_TSCTC);

	rd32(IGC_MGTPRC);
	rd32(IGC_MGTPDC);
	rd32(IGC_MGTPTC);

	rd32(IGC_IAC);

	rd32(IGC_RPTHC);
	rd32(IGC_TLPIC);
	rd32(IGC_RLPIC);
	rd32(IGC_HGPTC);
	rd32(IGC_RXDMTC);
	rd32(IGC_HGORCL);
	rd32(IGC_HGORCH);
	rd32(IGC_HGOTCL);
	rd32(IGC_HGOTCH);
	rd32(IGC_LENERRS);
पूर्ण

/**
 * igc_rar_set - Set receive address रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @addr: poपूर्णांकer to the receive address
 * @index: receive address array रेजिस्टर
 *
 * Sets the receive address array रेजिस्टर at index to the address passed
 * in by addr.
 */
व्योम igc_rar_set(काष्ठा igc_hw *hw, u8 *addr, u32 index)
अणु
	u32 rar_low, rar_high;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] |
		   ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) | ((u32)addr[3] << 24));

	rar_high = ((u32)addr[4] | ((u32)addr[5] << 8));

	/* If MAC address zero, no need to set the AV bit */
	अगर (rar_low || rar_high)
		rar_high |= IGC_RAH_AV;

	/* Some bridges will combine consecutive 32-bit ग_लिखोs पूर्णांकo
	 * a single burst ग_लिखो, which will malfunction on some parts.
	 * The flushes aव्योम this.
	 */
	wr32(IGC_RAL(index), rar_low);
	wrfl();
	wr32(IGC_RAH(index), rar_high);
	wrfl();
पूर्ण

/**
 * igc_check_क्रम_copper_link - Check क्रम link (Copper)
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Checks to see of the link status of the hardware has changed.  If a
 * change in link status has been detected, then we पढ़ो the PHY रेजिस्टरs
 * to get the current speed/duplex अगर link exists.
 */
s32 igc_check_क्रम_copper_link(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_mac_info *mac = &hw->mac;
	bool link = false;
	s32 ret_val;

	/* We only want to go out to the PHY रेजिस्टरs to see अगर Auto-Neg
	 * has completed and/or अगर our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error पूर्णांकerrupt.
	 */
	अगर (!mac->get_link_status) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	/* First we want to see अगर the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = igc_phy_has_link(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (!link)
		जाओ out; /* No link detected */

	mac->get_link_status = false;

	/* Check अगर there was DownShअगरt, must be checked
	 * immediately after link-up
	 */
	igc_check_करोwnshअगरt(hw);

	/* If we are क्रमcing speed/duplex, then we simply वापस since
	 * we have alपढ़ोy determined whether we have link or not.
	 */
	अगर (!mac->स्वतःneg) अणु
		ret_val = -IGC_ERR_CONFIG;
		जाओ out;
	पूर्ण

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	igc_config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-स्वतःneg with a
	 * dअगरferent link partner.
	 */
	ret_val = igc_config_fc_after_link_up(hw);
	अगर (ret_val)
		hw_dbg("Error configuring flow control\n");

out:
	/* Now that we are aware of our link settings, we can set the LTR
	 * thresholds.
	 */
	ret_val = igc_set_ltr_i225(hw, link);

	वापस ret_val;
पूर्ण

/**
 * igc_config_collision_dist - Configure collision distance
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Configures the collision distance to the शेष value and is used
 * during link setup. Currently no func poपूर्णांकer exists and all
 * implementations are handled in the generic version of this function.
 */
व्योम igc_config_collision_dist(काष्ठा igc_hw *hw)
अणु
	u32 tctl;

	tctl = rd32(IGC_TCTL);

	tctl &= ~IGC_TCTL_COLD;
	tctl |= IGC_COLLISION_DISTANCE << IGC_COLD_SHIFT;

	wr32(IGC_TCTL, tctl);
	wrfl();
पूर्ण

/**
 * igc_config_fc_after_link_up - Configures flow control after link
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Checks the status of स्वतः-negotiation after link up to ensure that the
 * speed and duplex were not क्रमced.  If the link needed to be क्रमced, then
 * flow control needs to be क्रमced also.  If स्वतः-negotiation is enabled
 * and did not fail, then we configure flow control based on our link
 * partner.
 */
s32 igc_config_fc_after_link_up(काष्ठा igc_hw *hw)
अणु
	u16 mii_status_reg, mii_nway_adv_reg, mii_nway_lp_ability_reg;
	काष्ठा igc_mac_info *mac = &hw->mac;
	u16 speed, duplex;
	s32 ret_val = 0;

	/* Check क्रम the हाल where we have fiber media and स्वतः-neg failed
	 * so we had to क्रमce link.  In this हाल, we need to क्रमce the
	 * configuration of the MAC to match the "fc" parameter.
	 */
	अगर (mac->स्वतःneg_failed)
		ret_val = igc_क्रमce_mac_fc(hw);

	अगर (ret_val) अणु
		hw_dbg("Error forcing flow control settings\n");
		जाओ out;
	पूर्ण

	/* Check क्रम the हाल where we have copper media and स्वतः-neg is
	 * enabled.  In this हाल, we need to check and see अगर Auto-Neg
	 * has completed, and अगर so, how the PHY and link partner has
	 * flow control configured.
	 */
	अगर (mac->स्वतःneg) अणु
		/* Read the MII Status Register and check to see अगर AutoNeg
		 * has completed.  We पढ़ो this twice because this reg has
		 * some "sticky" (latched) bits.
		 */
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS,
					       &mii_status_reg);
		अगर (ret_val)
			जाओ out;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS,
					       &mii_status_reg);
		अगर (ret_val)
			जाओ out;

		अगर (!(mii_status_reg & MII_SR_AUTONEG_COMPLETE)) अणु
			hw_dbg("Copper PHY and Auto Neg has not completed.\n");
			जाओ out;
		पूर्ण

		/* The AutoNeg process has completed, so we now need to
		 * पढ़ो both the Auto Negotiation Advertisement
		 * Register (Address 4) and the Auto_Negotiation Base
		 * Page Ability Register (Address 5) to determine how
		 * flow control was negotiated.
		 */
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_AUTONEG_ADV,
					       &mii_nway_adv_reg);
		अगर (ret_val)
			जाओ out;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_LP_ABILITY,
					       &mii_nway_lp_ability_reg);
		अगर (ret_val)
			जाओ out;
		/* Two bits in the Auto Negotiation Advertisement Register
		 * (Address 4) and two bits in the Auto Negotiation Base
		 * Page Ability Register (Address 5) determine flow control
		 * क्रम both the PHY and the link partner.  The following
		 * table, taken out of the IEEE 802.3ab/D6.0 dated March 25,
		 * 1999, describes these PAUSE resolution bits and how flow
		 * control is determined based upon these settings.
		 * NOTE:  DC = Don't Care
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | NIC Resolution
		 *-------|---------|-------|---------|--------------------
		 *   0   |    0    |  DC   |   DC    | igc_fc_none
		 *   0   |    1    |   0   |   DC    | igc_fc_none
		 *   0   |    1    |   1   |    0    | igc_fc_none
		 *   0   |    1    |   1   |    1    | igc_fc_tx_छोड़ो
		 *   1   |    0    |   0   |   DC    | igc_fc_none
		 *   1   |   DC    |   1   |   DC    | igc_fc_full
		 *   1   |    1    |   0   |    0    | igc_fc_none
		 *   1   |    1    |   0   |    1    | igc_fc_rx_छोड़ो
		 *
		 * Are both PAUSE bits set to 1?  If so, this implies
		 * Symmetric Flow Control is enabled at both ends.  The
		 * ASM_सूची bits are irrelevant per the spec.
		 *
		 * For Symmetric Flow Control:
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |   DC    |   1   |   DC    | IGC_fc_full
		 *
		 */
		अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
		    (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE)) अणु
			/* Now we need to check अगर the user selected RX ONLY
			 * of छोड़ो frames.  In this हाल, we had to advertise
			 * FULL flow control because we could not advertise RX
			 * ONLY. Hence, we must now check to see अगर we need to
			 * turn OFF  the TRANSMISSION of PAUSE frames.
			 */
			अगर (hw->fc.requested_mode == igc_fc_full) अणु
				hw->fc.current_mode = igc_fc_full;
				hw_dbg("Flow Control = FULL.\n");
			पूर्ण अन्यथा अणु
				hw->fc.current_mode = igc_fc_rx_छोड़ो;
				hw_dbg("Flow Control = RX PAUSE frames only.\n");
			पूर्ण
		पूर्ण

		/* For receiving PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   0   |    1    |   1   |    1    | igc_fc_tx_छोड़ो
		 */
		अन्यथा अगर (!(mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			 (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
			 (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
			hw->fc.current_mode = igc_fc_tx_छोड़ो;
			hw_dbg("Flow Control = TX PAUSE frames only.\n");
		पूर्ण
		/* For transmitting PAUSE frames ONLY.
		 *
		 *   LOCAL DEVICE  |   LINK PARTNER
		 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
		 *-------|---------|-------|---------|--------------------
		 *   1   |    1    |   0   |    1    | igc_fc_rx_छोड़ो
		 */
		अन्यथा अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			 (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
			 !(mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
			 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
			hw->fc.current_mode = igc_fc_rx_छोड़ो;
			hw_dbg("Flow Control = RX PAUSE frames only.\n");
		पूर्ण
		/* Per the IEEE spec, at this poपूर्णांक flow control should be
		 * disabled.  However, we want to consider that we could
		 * be connected to a legacy चयन that करोesn't advertise
		 * desired flow control, but can be क्रमced on the link
		 * partner.  So अगर we advertised no flow control, that is
		 * what we will resolve to.  If we advertised some kind of
		 * receive capability (Rx Pause Only or Full Flow Control)
		 * and the link partner advertised none, we will configure
		 * ourselves to enable Rx Flow Control only.  We can करो
		 * this safely क्रम two reasons:  If the link partner really
		 * didn't want flow control enabled, and we enable Rx, no
		 * harm करोne since we won't be receiving any PAUSE frames
		 * anyway.  If the पूर्णांकent on the link partner was to have
		 * flow control enabled, then by us enabling RX only, we
		 * can at least receive छोड़ो frames and process them.
		 * This is a good idea because in most हालs, since we are
		 * preकरोminantly a server NIC, more बार than not we will
		 * be asked to delay transmission of packets than asking
		 * our link partner to छोड़ो transmission of frames.
		 */
		अन्यथा अगर ((hw->fc.requested_mode == igc_fc_none) ||
			 (hw->fc.requested_mode == igc_fc_tx_छोड़ो) ||
			 (hw->fc.strict_ieee)) अणु
			hw->fc.current_mode = igc_fc_none;
			hw_dbg("Flow Control = NONE.\n");
		पूर्ण अन्यथा अणु
			hw->fc.current_mode = igc_fc_rx_छोड़ो;
			hw_dbg("Flow Control = RX PAUSE frames only.\n");
		पूर्ण

		/* Now we need to करो one last check...  If we स्वतः-
		 * negotiated to HALF DUPLEX, flow control should not be
		 * enabled per IEEE 802.3 spec.
		 */
		ret_val = hw->mac.ops.get_speed_and_duplex(hw, &speed, &duplex);
		अगर (ret_val) अणु
			hw_dbg("Error getting link speed and duplex\n");
			जाओ out;
		पूर्ण

		अगर (duplex == HALF_DUPLEX)
			hw->fc.current_mode = igc_fc_none;

		/* Now we call a subroutine to actually क्रमce the MAC
		 * controller to use the correct flow control settings.
		 */
		ret_val = igc_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			hw_dbg("Error forcing flow control settings\n");
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_get_स्वतः_rd_करोne - Check क्रम स्वतः पढ़ो completion
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Check EEPROM क्रम Auto Read करोne bit.
 */
s32 igc_get_स्वतः_rd_करोne(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = 0;
	s32 i = 0;

	जबतक (i < AUTO_READ_DONE_TIMEOUT) अणु
		अगर (rd32(IGC_EECD) & IGC_EECD_AUTO_RD)
			अवरोध;
		usleep_range(1000, 2000);
		i++;
	पूर्ण

	अगर (i == AUTO_READ_DONE_TIMEOUT) अणु
		hw_dbg("Auto read by HW from NVM has not completed.\n");
		ret_val = -IGC_ERR_RESET;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_get_speed_and_duplex_copper - Retrieve current speed/duplex
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @speed: stores the current speed
 * @duplex: stores the current duplex
 *
 * Read the status रेजिस्टर क्रम the current speed/duplex and store the current
 * speed and duplex क्रम copper connections.
 */
s32 igc_get_speed_and_duplex_copper(काष्ठा igc_hw *hw, u16 *speed,
				    u16 *duplex)
अणु
	u32 status;

	status = rd32(IGC_STATUS);
	अगर (status & IGC_STATUS_SPEED_1000) अणु
		/* For I225, STATUS will indicate 1G speed in both 1 Gbps
		 * and 2.5 Gbps link modes. An additional bit is used
		 * to dअगरferentiate between 1 Gbps and 2.5 Gbps.
		 */
		अगर (hw->mac.type == igc_i225 &&
		    (status & IGC_STATUS_SPEED_2500)) अणु
			*speed = SPEED_2500;
			hw_dbg("2500 Mbs, ");
		पूर्ण अन्यथा अणु
			*speed = SPEED_1000;
			hw_dbg("1000 Mbs, ");
		पूर्ण
	पूर्ण अन्यथा अगर (status & IGC_STATUS_SPEED_100) अणु
		*speed = SPEED_100;
		hw_dbg("100 Mbs, ");
	पूर्ण अन्यथा अणु
		*speed = SPEED_10;
		hw_dbg("10 Mbs, ");
	पूर्ण

	अगर (status & IGC_STATUS_FD) अणु
		*duplex = FULL_DUPLEX;
		hw_dbg("Full Duplex\n");
	पूर्ण अन्यथा अणु
		*duplex = HALF_DUPLEX;
		hw_dbg("Half Duplex\n");
	पूर्ण

	वापस 0;
पूर्ण

/**
 * igc_put_hw_semaphore - Release hardware semaphore
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Release hardware semaphore used to access the PHY or NVM
 */
व्योम igc_put_hw_semaphore(काष्ठा igc_hw *hw)
अणु
	u32 swsm;

	swsm = rd32(IGC_SWSM);

	swsm &= ~(IGC_SWSM_SMBI | IGC_SWSM_SWESMBI);

	wr32(IGC_SWSM, swsm);
पूर्ण

/**
 * igc_enable_mng_pass_thru - Enable processing of ARP's
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Verअगरies the hardware needs to leave पूर्णांकerface enabled so that frames can
 * be directed to and from the management पूर्णांकerface.
 */
bool igc_enable_mng_pass_thru(काष्ठा igc_hw *hw)
अणु
	bool ret_val = false;
	u32 fwsm, factps;
	u32 manc;

	अगर (!hw->mac.asf_firmware_present)
		जाओ out;

	manc = rd32(IGC_MANC);

	अगर (!(manc & IGC_MANC_RCV_TCO_EN))
		जाओ out;

	अगर (hw->mac.arc_subप्रणाली_valid) अणु
		fwsm = rd32(IGC_FWSM);
		factps = rd32(IGC_FACTPS);

		अगर (!(factps & IGC_FACTPS_MNGCG) &&
		    ((fwsm & IGC_FWSM_MODE_MASK) ==
		    (igc_mng_mode_pt << IGC_FWSM_MODE_SHIFT))) अणु
			ret_val = true;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((manc & IGC_MANC_SMBUS_EN) &&
		    !(manc & IGC_MANC_ASF_EN)) अणु
			ret_val = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igc_hash_mc_addr - Generate a multicast hash value
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr: poपूर्णांकer to a multicast address
 *
 *  Generates a multicast address hash value which is used to determine
 *  the multicast filter table array address and new table value.  See
 *  igc_mta_set()
 **/
अटल u32 igc_hash_mc_addr(काष्ठा igc_hw *hw, u8 *mc_addr)
अणु
	u32 hash_value, hash_mask;
	u8 bit_shअगरt = 0;

	/* Register count multiplied by bits per रेजिस्टर */
	hash_mask = (hw->mac.mta_reg_count * 32) - 1;

	/* For a mc_filter_type of 0, bit_shअगरt is the number of left-shअगरts
	 * where 0xFF would still fall within the hash mask.
	 */
	जबतक (hash_mask >> bit_shअगरt != 0xFF)
		bit_shअगरt++;

	/* The portion of the address that is used क्रम the hash table
	 * is determined by the mc_filter_type setting.
	 * The algorithm is such that there is a total of 8 bits of shअगरting.
	 * The bit_shअगरt क्रम a mc_filter_type of 0 represents the number of
	 * left-shअगरts where the MSB of mc_addr[5] would still fall within
	 * the hash_mask.  Case 0 करोes this exactly.  Since there are a total
	 * of 8 bits of shअगरting, then mc_addr[4] will shअगरt right the
	 * reमुख्यing number of bits. Thus 8 - bit_shअगरt.  The rest of the
	 * हालs are a variation of this algorithm...essentially raising the
	 * number of bits to shअगरt mc_addr[5] left, जबतक still keeping the
	 * 8-bit shअगरting total.
	 *
	 * For example, given the following Destination MAC Address and an
	 * MTA रेजिस्टर count of 128 (thus a 4096-bit vector and 0xFFF mask),
	 * we can see that the bit_shअगरt क्रम हाल 0 is 4.  These are the hash
	 * values resulting from each mc_filter_type...
	 * [0] [1] [2] [3] [4] [5]
	 * 01  AA  00  12  34  56
	 * LSB                 MSB
	 *
	 * हाल 0: hash_value = ((0x34 >> 4) | (0x56 << 4)) & 0xFFF = 0x563
	 * हाल 1: hash_value = ((0x34 >> 3) | (0x56 << 5)) & 0xFFF = 0xAC6
	 * हाल 2: hash_value = ((0x34 >> 2) | (0x56 << 6)) & 0xFFF = 0x163
	 * हाल 3: hash_value = ((0x34 >> 0) | (0x56 << 8)) & 0xFFF = 0x634
	 */
	चयन (hw->mac.mc_filter_type) अणु
	शेष:
	हाल 0:
		अवरोध;
	हाल 1:
		bit_shअगरt += 1;
		अवरोध;
	हाल 2:
		bit_shअगरt += 2;
		अवरोध;
	हाल 3:
		bit_shअगरt += 4;
		अवरोध;
	पूर्ण

	hash_value = hash_mask & (((mc_addr[4] >> (8 - bit_shअगरt)) |
				  (((u16)mc_addr[5]) << bit_shअगरt)));

	वापस hash_value;
पूर्ण

/**
 *  igc_update_mc_addr_list - Update Multicast addresses
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mc_addr_list: array of multicast addresses to program
 *  @mc_addr_count: number of multicast addresses to program
 *
 *  Updates entire Multicast Table Array.
 *  The caller must have a packed mc_addr_list of multicast addresses.
 **/
व्योम igc_update_mc_addr_list(काष्ठा igc_hw *hw,
			     u8 *mc_addr_list, u32 mc_addr_count)
अणु
	u32 hash_value, hash_bit, hash_reg;
	पूर्णांक i;

	/* clear mta_shaकरोw */
	स_रखो(&hw->mac.mta_shaकरोw, 0, माप(hw->mac.mta_shaकरोw));

	/* update mta_shaकरोw from mc_addr_list */
	क्रम (i = 0; (u32)i < mc_addr_count; i++) अणु
		hash_value = igc_hash_mc_addr(hw, mc_addr_list);

		hash_reg = (hash_value >> 5) & (hw->mac.mta_reg_count - 1);
		hash_bit = hash_value & 0x1F;

		hw->mac.mta_shaकरोw[hash_reg] |= BIT(hash_bit);
		mc_addr_list += ETH_ALEN;
	पूर्ण

	/* replace the entire MTA table */
	क्रम (i = hw->mac.mta_reg_count - 1; i >= 0; i--)
		array_wr32(IGC_MTA, i, hw->mac.mta_shaकरोw[i]);
	wrfl();
पूर्ण

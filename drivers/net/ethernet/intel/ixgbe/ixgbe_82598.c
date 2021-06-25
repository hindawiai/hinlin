<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_phy.h"

#घोषणा IXGBE_82598_MAX_TX_QUEUES 32
#घोषणा IXGBE_82598_MAX_RX_QUEUES 64
#घोषणा IXGBE_82598_RAR_ENTRIES   16
#घोषणा IXGBE_82598_MC_TBL_SIZE  128
#घोषणा IXGBE_82598_VFT_TBL_SIZE 128
#घोषणा IXGBE_82598_RX_PB_SIZE	 512

अटल s32 ixgbe_setup_copper_link_82598(काष्ठा ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool स्वतःneg_रुको_to_complete);
अटल s32 ixgbe_पढ़ो_i2c_eeprom_82598(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				       u8 *eeprom_data);

/**
 *  ixgbe_set_pcie_completion_समयout - set pci-e completion समयout
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The शेषs क्रम 82598 should be in the range of 50us to 50ms,
 *  however the hardware शेष क्रम these parts is 500us to 1ms which is less
 *  than the 10ms recommended by the pci-e spec.  To address this we need to
 *  increase the value to either 10ms to 250ms क्रम capability version 1 config,
 *  or 16ms to 55ms क्रम version 2.
 **/
अटल व्योम ixgbe_set_pcie_completion_समयout(काष्ठा ixgbe_hw *hw)
अणु
	u32 gcr = IXGBE_READ_REG(hw, IXGBE_GCR);
	u16 pcie_devctl2;

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस;

	/* only take action अगर समयout value is शेषed to 0 */
	अगर (gcr & IXGBE_GCR_CMPL_TMOUT_MASK)
		जाओ out;

	/*
	 * अगर capababilities version is type 1 we can ग_लिखो the
	 * समयout of 10ms to 250ms through the GCR रेजिस्टर
	 */
	अगर (!(gcr & IXGBE_GCR_CAP_VER2)) अणु
		gcr |= IXGBE_GCR_CMPL_TMOUT_10ms;
		जाओ out;
	पूर्ण

	/*
	 * क्रम version 2 capabilities we need to ग_लिखो the config space
	 * directly in order to set the completion समयout value क्रम
	 * 16ms to 55ms
	 */
	pcie_devctl2 = ixgbe_पढ़ो_pci_cfg_word(hw, IXGBE_PCI_DEVICE_CONTROL2);
	pcie_devctl2 |= IXGBE_PCI_DEVICE_CONTROL2_16ms;
	ixgbe_ग_लिखो_pci_cfg_word(hw, IXGBE_PCI_DEVICE_CONTROL2, pcie_devctl2);
out:
	/* disable completion समयout resend */
	gcr &= ~IXGBE_GCR_CMPL_TMOUT_RESEND;
	IXGBE_WRITE_REG(hw, IXGBE_GCR, gcr);
पूर्ण

अटल s32 ixgbe_get_invariants_82598(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;

	/* Call PHY identअगरy routine to get the phy type */
	ixgbe_identअगरy_phy_generic(hw);

	mac->mcft_size = IXGBE_82598_MC_TBL_SIZE;
	mac->vft_size = IXGBE_82598_VFT_TBL_SIZE;
	mac->num_rar_entries = IXGBE_82598_RAR_ENTRIES;
	mac->rx_pb_size = IXGBE_82598_RX_PB_SIZE;
	mac->max_rx_queues = IXGBE_82598_MAX_RX_QUEUES;
	mac->max_tx_queues = IXGBE_82598_MAX_TX_QUEUES;
	mac->max_msix_vectors = ixgbe_get_pcie_msix_count_generic(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_phy_ops_82598 - PHY/SFP specअगरic init
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initialize any function poपूर्णांकers that were not able to be
 *  set during get_invariants because the PHY/SFP type was
 *  not known.  Perक्रमm the SFP init अगर necessary.
 *
 **/
अटल s32 ixgbe_init_phy_ops_82598(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	काष्ठा ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 list_offset, data_offset;

	/* Identअगरy the PHY */
	phy->ops.identअगरy(hw);

	/* Overग_लिखो the link function poपूर्णांकers अगर copper PHY */
	अगर (mac->ops.get_media_type(hw) == ixgbe_media_type_copper) अणु
		mac->ops.setup_link = &ixgbe_setup_copper_link_82598;
		mac->ops.get_link_capabilities =
			&ixgbe_get_copper_link_capabilities_generic;
	पूर्ण

	चयन (hw->phy.type) अणु
	हाल ixgbe_phy_tn:
		phy->ops.setup_link = &ixgbe_setup_phy_link_tnx;
		phy->ops.check_link = &ixgbe_check_phy_link_tnx;
		अवरोध;
	हाल ixgbe_phy_nl:
		phy->ops.reset = &ixgbe_reset_phy_nl;

		/* Call SFP+ identअगरy routine to get the SFP+ module type */
		ret_val = phy->ops.identअगरy_sfp(hw);
		अगर (ret_val)
			वापस ret_val;
		अगर (hw->phy.sfp_type == ixgbe_sfp_type_unknown)
			वापस IXGBE_ERR_SFP_NOT_SUPPORTED;

		/* Check to see अगर SFP+ module is supported */
		ret_val = ixgbe_get_sfp_init_sequence_offsets(hw,
							    &list_offset,
							    &data_offset);
		अगर (ret_val)
			वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_start_hw_82598 - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Starts the hardware using the generic start_hw function.
 *  Disables relaxed ordering क्रम archs other than SPARC
 *  Then set pcie completion समयout
 *
 **/
अटल s32 ixgbe_start_hw_82598(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val;

	ret_val = ixgbe_start_hw_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	/* set the completion समयout क्रम पूर्णांकerface */
	ixgbe_set_pcie_completion_समयout(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_link_capabilities_82598 - Determines link capabilities
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: poपूर्णांकer to link speed
 *  @स्वतःneg: boolean स्वतः-negotiation value
 *
 *  Determines the link capabilities by पढ़ोing the AUTOC रेजिस्टर.
 **/
अटल s32 ixgbe_get_link_capabilities_82598(काष्ठा ixgbe_hw *hw,
					     ixgbe_link_speed *speed,
					     bool *स्वतःneg)
अणु
	u32 स्वतःc = 0;

	/*
	 * Determine link capabilities based on the stored value of AUTOC,
	 * which represents EEPROM शेषs.  If AUTOC value has not been
	 * stored, use the current रेजिस्टर value.
	 */
	अगर (hw->mac.orig_link_settings_stored)
		स्वतःc = hw->mac.orig_स्वतःc;
	अन्यथा
		स्वतःc = IXGBE_READ_REG(hw, IXGBE_AUTOC);

	चयन (स्वतःc & IXGBE_AUTOC_LMS_MASK) अणु
	हाल IXGBE_AUTOC_LMS_1G_LINK_NO_AN:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = false;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_10G_LINK_NO_AN:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		*स्वतःneg = false;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_1G_AN:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = true;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_KX4_AN:
	हाल IXGBE_AUTOC_LMS_KX4_AN_1G_AN:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
		अगर (स्वतःc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = true;
		अवरोध;

	शेष:
		वापस IXGBE_ERR_LINK_SETUP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_media_type_82598 - Determines media type
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns the media type (fiber, copper, backplane)
 **/
अटल क्रमागत ixgbe_media_type ixgbe_get_media_type_82598(काष्ठा ixgbe_hw *hw)
अणु
	/* Detect अगर there is a copper PHY attached. */
	चयन (hw->phy.type) अणु
	हाल ixgbe_phy_cu_unknown:
	हाल ixgbe_phy_tn:
		वापस ixgbe_media_type_copper;

	शेष:
		अवरोध;
	पूर्ण

	/* Media type क्रम I82598 is based on device ID */
	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82598:
	हाल IXGBE_DEV_ID_82598_BX:
		/* Default device ID is mezzanine card KX/KX4 */
		वापस ixgbe_media_type_backplane;

	हाल IXGBE_DEV_ID_82598AF_DUAL_PORT:
	हाल IXGBE_DEV_ID_82598AF_SINGLE_PORT:
	हाल IXGBE_DEV_ID_82598_DA_DUAL_PORT:
	हाल IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM:
	हाल IXGBE_DEV_ID_82598EB_XF_LR:
	हाल IXGBE_DEV_ID_82598EB_SFP_LOM:
		वापस ixgbe_media_type_fiber;

	हाल IXGBE_DEV_ID_82598EB_CX4:
	हाल IXGBE_DEV_ID_82598_CX4_DUAL_PORT:
		वापस ixgbe_media_type_cx4;

	हाल IXGBE_DEV_ID_82598AT:
	हाल IXGBE_DEV_ID_82598AT2:
		वापस ixgbe_media_type_copper;

	शेष:
		वापस ixgbe_media_type_unknown;
	पूर्ण
पूर्ण

/**
 *  ixgbe_fc_enable_82598 - Enable flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enable flow control according to the current settings.
 **/
अटल s32 ixgbe_fc_enable_82598(काष्ठा ixgbe_hw *hw)
अणु
	u32 fctrl_reg;
	u32 rmcs_reg;
	u32 reg;
	u32 fcrtl, fcrth;
	u32 link_speed = 0;
	पूर्णांक i;
	bool link_up;

	/* Validate the water mark configuration */
	अगर (!hw->fc.छोड़ो_समय)
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;

	/* Low water mark of zero causes XOFF floods */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		अगर ((hw->fc.current_mode & ixgbe_fc_tx_छोड़ो) &&
		    hw->fc.high_water[i]) अणु
			अगर (!hw->fc.low_water[i] ||
			    hw->fc.low_water[i] >= hw->fc.high_water[i]) अणु
				hw_dbg(hw, "Invalid water mark configuration\n");
				वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * On 82598 having Rx FC on causes resets जबतक करोing 1G
	 * so अगर it's on turn it off once we know link_speed. For
	 * more details see 82598 Specअगरication update.
	 */
	hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
	अगर (link_up && link_speed == IXGBE_LINK_SPEED_1GB_FULL) अणु
		चयन (hw->fc.requested_mode) अणु
		हाल ixgbe_fc_full:
			hw->fc.requested_mode = ixgbe_fc_tx_छोड़ो;
			अवरोध;
		हाल ixgbe_fc_rx_छोड़ो:
			hw->fc.requested_mode = ixgbe_fc_none;
			अवरोध;
		शेष:
			/* no change */
			अवरोध;
		पूर्ण
	पूर्ण

	/* Negotiate the fc mode to use */
	hw->mac.ops.fc_स्वतःneg(hw);

	/* Disable any previous flow control settings */
	fctrl_reg = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	fctrl_reg &= ~(IXGBE_FCTRL_RFCE | IXGBE_FCTRL_RPFCE);

	rmcs_reg = IXGBE_READ_REG(hw, IXGBE_RMCS);
	rmcs_reg &= ~(IXGBE_RMCS_TFCE_PRIORITY | IXGBE_RMCS_TFCE_802_3X);

	/*
	 * The possible values of fc.current_mode are:
	 * 0: Flow control is completely disabled
	 * 1: Rx flow control is enabled (we can receive छोड़ो frames,
	 *    but not send छोड़ो frames).
	 * 2: Tx flow control is enabled (we can send छोड़ो frames but
	 *     we करो not support receiving छोड़ो frames).
	 * 3: Both Rx and Tx flow control (symmetric) are enabled.
	 * other: Invalid.
	 */
	चयन (hw->fc.current_mode) अणु
	हाल ixgbe_fc_none:
		/*
		 * Flow control is disabled by software override or स्वतःneg.
		 * The code below will actually disable it in the HW.
		 */
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		/*
		 * Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
		fctrl_reg |= IXGBE_FCTRL_RFCE;
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		/*
		 * Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		rmcs_reg |= IXGBE_RMCS_TFCE_802_3X;
		अवरोध;
	हाल ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		fctrl_reg |= IXGBE_FCTRL_RFCE;
		rmcs_reg |= IXGBE_RMCS_TFCE_802_3X;
		अवरोध;
	शेष:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	/* Set 802.3x based flow control settings. */
	fctrl_reg |= IXGBE_FCTRL_DPF;
	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl_reg);
	IXGBE_WRITE_REG(hw, IXGBE_RMCS, rmcs_reg);

	/* Set up and enable Rx high/low water mark thresholds, enable XON. */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		अगर ((hw->fc.current_mode & ixgbe_fc_tx_छोड़ो) &&
		    hw->fc.high_water[i]) अणु
			fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
			fcrth = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), fcrtl);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), fcrth);
		पूर्ण अन्यथा अणु
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), 0);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), 0);
		पूर्ण

	पूर्ण

	/* Configure छोड़ो समय (2 TCs per रेजिस्टर) */
	reg = hw->fc.छोड़ो_समय * 0x00010001;
	क्रम (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);

	/* Configure flow control refresh threshold value */
	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.छोड़ो_समय / 2);

	वापस 0;
पूर्ण

/**
 *  ixgbe_start_mac_link_82598 - Configures MAC link settings
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Configures link settings based on values in the ixgbe_hw काष्ठा.
 *  Restarts the link.  Perक्रमms स्वतःnegotiation अगर needed.
 **/
अटल s32 ixgbe_start_mac_link_82598(काष्ठा ixgbe_hw *hw,
				      bool स्वतःneg_रुको_to_complete)
अणु
	u32 स्वतःc_reg;
	u32 links_reg;
	u32 i;
	s32 status = 0;

	/* Restart link */
	स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	स्वतःc_reg |= IXGBE_AUTOC_AN_RESTART;
	IXGBE_WRITE_REG(hw, IXGBE_AUTOC, स्वतःc_reg);

	/* Only poll क्रम स्वतःneg to complete अगर specअगरied to करो so */
	अगर (स्वतःneg_रुको_to_complete) अणु
		अगर ((स्वतःc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_AN ||
		    (स्वतःc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_AN_1G_AN) अणु
			links_reg = 0; /* Just in हाल Autoneg समय = 0 */
			क्रम (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) अणु
				links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
				अगर (links_reg & IXGBE_LINKS_KX_AN_COMP)
					अवरोध;
				msleep(100);
			पूर्ण
			अगर (!(links_reg & IXGBE_LINKS_KX_AN_COMP)) अणु
				status = IXGBE_ERR_AUTONEG_NOT_COMPLETE;
				hw_dbg(hw, "Autonegotiation did not complete.\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* Add delay to filter out noises during initial link setup */
	msleep(50);

	वापस status;
पूर्ण

/**
 *  ixgbe_validate_link_पढ़ोy - Function looks क्रम phy link
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Function indicates success when phy link is available. If phy is not पढ़ोy
 *  within 5 seconds of MAC indicating link, the function वापसs error.
 **/
अटल s32 ixgbe_validate_link_पढ़ोy(काष्ठा ixgbe_hw *hw)
अणु
	u32 समयout;
	u16 an_reg;

	अगर (hw->device_id != IXGBE_DEV_ID_82598AT2)
		वापस 0;

	क्रम (समयout = 0;
	     समयout < IXGBE_VALIDATE_LINK_READY_TIMEOUT; समयout++) अणु
		hw->phy.ops.पढ़ो_reg(hw, MDIO_STAT1, MDIO_MMD_AN, &an_reg);

		अगर ((an_reg & MDIO_AN_STAT1_COMPLETE) &&
		    (an_reg & MDIO_STAT1_LSTATUS))
			अवरोध;

		msleep(100);
	पूर्ण

	अगर (समयout == IXGBE_VALIDATE_LINK_READY_TIMEOUT) अणु
		hw_dbg(hw, "Link was indicated but link is down\n");
		वापस IXGBE_ERR_LINK_SETUP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_check_mac_link_82598 - Get link/speed status
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: poपूर्णांकer to link speed
 *  @link_up: true is link is up, false otherwise
 *  @link_up_रुको_to_complete: bool used to रुको क्रम link up or not
 *
 *  Reads the links रेजिस्टर to determine अगर link is up and the current speed
 **/
अटल s32 ixgbe_check_mac_link_82598(काष्ठा ixgbe_hw *hw,
				      ixgbe_link_speed *speed, bool *link_up,
				      bool link_up_रुको_to_complete)
अणु
	u32 links_reg;
	u32 i;
	u16 link_reg, adapt_comp_reg;

	/*
	 * SERDES PHY requires us to पढ़ो link status from रेजिस्टर 0xC79F.
	 * Bit 0 set indicates link is up/पढ़ोy; clear indicates link करोwn.
	 * 0xC00C is पढ़ो to check that the XAUI lanes are active.  Bit 0
	 * clear indicates active; set indicates inactive.
	 */
	अगर (hw->phy.type == ixgbe_phy_nl) अणु
		hw->phy.ops.पढ़ो_reg(hw, 0xC79F, MDIO_MMD_PMAPMD, &link_reg);
		hw->phy.ops.पढ़ो_reg(hw, 0xC79F, MDIO_MMD_PMAPMD, &link_reg);
		hw->phy.ops.पढ़ो_reg(hw, 0xC00C, MDIO_MMD_PMAPMD,
				     &adapt_comp_reg);
		अगर (link_up_रुको_to_complete) अणु
			क्रम (i = 0; i < IXGBE_LINK_UP_TIME; i++) अणु
				अगर ((link_reg & 1) &&
				    ((adapt_comp_reg & 1) == 0)) अणु
					*link_up = true;
					अवरोध;
				पूर्ण अन्यथा अणु
					*link_up = false;
				पूर्ण
				msleep(100);
				hw->phy.ops.पढ़ो_reg(hw, 0xC79F,
						     MDIO_MMD_PMAPMD,
						     &link_reg);
				hw->phy.ops.पढ़ो_reg(hw, 0xC00C,
						     MDIO_MMD_PMAPMD,
						     &adapt_comp_reg);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((link_reg & 1) && ((adapt_comp_reg & 1) == 0))
				*link_up = true;
			अन्यथा
				*link_up = false;
		पूर्ण

		अगर (!*link_up)
			वापस 0;
	पूर्ण

	links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
	अगर (link_up_रुको_to_complete) अणु
		क्रम (i = 0; i < IXGBE_LINK_UP_TIME; i++) अणु
			अगर (links_reg & IXGBE_LINKS_UP) अणु
				*link_up = true;
				अवरोध;
			पूर्ण अन्यथा अणु
				*link_up = false;
			पूर्ण
			msleep(100);
			links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (links_reg & IXGBE_LINKS_UP)
			*link_up = true;
		अन्यथा
			*link_up = false;
	पूर्ण

	अगर (links_reg & IXGBE_LINKS_SPEED)
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
	अन्यथा
		*speed = IXGBE_LINK_SPEED_1GB_FULL;

	अगर ((hw->device_id == IXGBE_DEV_ID_82598AT2) && *link_up &&
	    (ixgbe_validate_link_पढ़ोy(hw) != 0))
		*link_up = false;

	वापस 0;
पूर्ण

/**
 *  ixgbe_setup_mac_link_82598 - Set MAC link speed
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Set the link speed in the AUTOC रेजिस्टर and restarts link.
 **/
अटल s32 ixgbe_setup_mac_link_82598(काष्ठा ixgbe_hw *hw,
				      ixgbe_link_speed speed,
				      bool स्वतःneg_रुको_to_complete)
अणु
	bool		 स्वतःneg	   = false;
	ixgbe_link_speed link_capabilities = IXGBE_LINK_SPEED_UNKNOWN;
	u32              curr_स्वतःc        = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32              स्वतःc             = curr_स्वतःc;
	u32              link_mode         = स्वतःc & IXGBE_AUTOC_LMS_MASK;

	/* Check to see अगर speed passed in is supported. */
	ixgbe_get_link_capabilities_82598(hw, &link_capabilities, &स्वतःneg);
	speed &= link_capabilities;

	अगर (speed == IXGBE_LINK_SPEED_UNKNOWN)
		वापस IXGBE_ERR_LINK_SETUP;

	/* Set KX4/KX support according to speed requested */
	अन्यथा अगर (link_mode == IXGBE_AUTOC_LMS_KX4_AN ||
		 link_mode == IXGBE_AUTOC_LMS_KX4_AN_1G_AN) अणु
		स्वतःc &= ~IXGBE_AUTOC_KX4_KX_SUPP_MASK;
		अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
			स्वतःc |= IXGBE_AUTOC_KX4_SUPP;
		अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
			स्वतःc |= IXGBE_AUTOC_KX_SUPP;
		अगर (स्वतःc != curr_स्वतःc)
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC, स्वतःc);
	पूर्ण

	/* Setup and restart the link based on the new values in
	 * ixgbe_hw This will ग_लिखो the AUTOC रेजिस्टर based on the new
	 * stored values
	 */
	वापस ixgbe_start_mac_link_82598(hw, स्वतःneg_रुको_to_complete);
पूर्ण


/**
 *  ixgbe_setup_copper_link_82598 - Set the PHY स्वतःneg advertised field
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true अगर रुकोing is needed to complete
 *
 *  Sets the link speed in the AUTOC रेजिस्टर in the MAC and restarts link.
 **/
अटल s32 ixgbe_setup_copper_link_82598(काष्ठा ixgbe_hw *hw,
					       ixgbe_link_speed speed,
					       bool स्वतःneg_रुको_to_complete)
अणु
	s32 status;

	/* Setup the PHY according to input speed */
	status = hw->phy.ops.setup_link_speed(hw, speed,
					      स्वतःneg_रुको_to_complete);
	/* Set up MAC */
	ixgbe_start_mac_link_82598(hw, स्वतःneg_रुको_to_complete);

	वापस status;
पूर्ण

/**
 *  ixgbe_reset_hw_82598 - Perक्रमms hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Resets the hardware by resetting the transmit and receive units, masks and
 *  clears all पूर्णांकerrupts, perक्रमming a PHY reset, and perक्रमming a link (MAC)
 *  reset.
 **/
अटल s32 ixgbe_reset_hw_82598(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	s32 phy_status = 0;
	u32 ctrl;
	u32 gheccr;
	u32 i;
	u32 स्वतःc;
	u8  analog_val;

	/* Call adapter stop to disable tx/rx and clear पूर्णांकerrupts */
	status = hw->mac.ops.stop_adapter(hw);
	अगर (status)
		वापस status;

	/*
	 * Power up the Atlas Tx lanes अगर they are currently घातered करोwn.
	 * Atlas Tx lanes are घातered करोwn क्रम MAC loopback tests, but
	 * they are not स्वतःmatically restored on reset.
	 */
	hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, &analog_val);
	अगर (analog_val & IXGBE_ATLAS_PDN_TX_REG_EN) अणु
		/* Enable Tx Atlas so packets can be transmitted again */
		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_REG_EN;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK,
					      analog_val);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_10G,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_10G_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_10G,
					      analog_val);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_1G,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_1G_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_1G,
					      analog_val);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_AN,
					     &analog_val);
		analog_val &= ~IXGBE_ATLAS_PDN_TX_AN_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_AN,
					      analog_val);
	पूर्ण

	/* Reset PHY */
	अगर (hw->phy.reset_disable == false) अणु
		/* PHY ops must be identअगरied and initialized prior to reset */

		/* Init PHY and function poपूर्णांकers, perक्रमm SFP setup */
		phy_status = hw->phy.ops.init(hw);
		अगर (phy_status == IXGBE_ERR_SFP_NOT_SUPPORTED)
			वापस phy_status;
		अगर (phy_status == IXGBE_ERR_SFP_NOT_PRESENT)
			जाओ mac_reset_top;

		hw->phy.ops.reset(hw);
	पूर्ण

mac_reset_top:
	/*
	 * Issue global reset to the MAC.  This needs to be a SW reset.
	 * If link reset is used, it might reset the MAC when mng is using it
	 */
	ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL) | IXGBE_CTRL_RST;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(1000, 1200);

	/* Poll क्रम reset bit to self-clear indicating reset is complete */
	क्रम (i = 0; i < 10; i++) अणु
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		अगर (!(ctrl & IXGBE_CTRL_RST))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (ctrl & IXGBE_CTRL_RST) अणु
		status = IXGBE_ERR_RESET_FAILED;
		hw_dbg(hw, "Reset polling failed to complete.\n");
	पूर्ण

	msleep(50);

	/*
	 * Double resets are required क्रम recovery from certain error
	 * conditions.  Between resets, it is necessary to stall to allow समय
	 * क्रम any pending HW events to complete.
	 */
	अगर (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) अणु
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		जाओ mac_reset_top;
	पूर्ण

	gheccr = IXGBE_READ_REG(hw, IXGBE_GHECCR);
	gheccr &= ~(BIT(21) | BIT(18) | BIT(9) | BIT(6));
	IXGBE_WRITE_REG(hw, IXGBE_GHECCR, gheccr);

	/*
	 * Store the original AUTOC value अगर it has not been
	 * stored off yet.  Otherwise restore the stored original
	 * AUTOC value since the reset operation sets back to deaults.
	 */
	स्वतःc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	अगर (hw->mac.orig_link_settings_stored == false) अणु
		hw->mac.orig_स्वतःc = स्वतःc;
		hw->mac.orig_link_settings_stored = true;
	पूर्ण अन्यथा अगर (स्वतःc != hw->mac.orig_स्वतःc) अणु
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC, hw->mac.orig_स्वतःc);
	पूर्ण

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address रेजिस्टरs, and
	 * clear the multicast table
	 */
	hw->mac.ops.init_rx_addrs(hw);

	अगर (phy_status)
		status = phy_status;

	वापस status;
पूर्ण

/**
 *  ixgbe_set_vmdq_82598 - Associate a VMDq set index with a rx address
 *  @hw: poपूर्णांकer to hardware काष्ठा
 *  @rar: receive address रेजिस्टर index to associate with a VMDq index
 *  @vmdq: VMDq set index
 **/
अटल s32 ixgbe_set_vmdq_82598(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq)
अणु
	u32 rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	अगर (rar >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", rar);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(rar));
	rar_high &= ~IXGBE_RAH_VIND_MASK;
	rar_high |= ((vmdq << IXGBE_RAH_VIND_SHIFT) & IXGBE_RAH_VIND_MASK);
	IXGBE_WRITE_REG(hw, IXGBE_RAH(rar), rar_high);
	वापस 0;
पूर्ण

/**
 *  ixgbe_clear_vmdq_82598 - Disassociate a VMDq set index from an rx address
 *  @hw: poपूर्णांकer to hardware काष्ठा
 *  @rar: receive address रेजिस्टर index to associate with a VMDq index
 *  @vmdq: VMDq clear index (not used in 82598, but अन्यथाwhere)
 **/
अटल s32 ixgbe_clear_vmdq_82598(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq)
अणु
	u32 rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;


	/* Make sure we are using a valid rar index range */
	अगर (rar >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", rar);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(rar));
	अगर (rar_high & IXGBE_RAH_VIND_MASK) अणु
		rar_high &= ~IXGBE_RAH_VIND_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_RAH(rar), rar_high);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_set_vfta_82598 - Set VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vlan: VLAN id to ग_लिखो to VLAN filter
 *  @vind: VMDq output index that maps queue to VLAN id in VFTA
 *  @vlan_on: boolean flag to turn on/off VLAN in VFTA
 *  @vlvf_bypass: boolean flag - unused
 *
 *  Turn on/off specअगरied VLAN in the VLAN filter table.
 **/
अटल s32 ixgbe_set_vfta_82598(काष्ठा ixgbe_hw *hw, u32 vlan, u32 vind,
				bool vlan_on, bool vlvf_bypass)
अणु
	u32 regindex;
	u32 bitindex;
	u32 bits;
	u32 vftabyte;

	अगर (vlan > 4095)
		वापस IXGBE_ERR_PARAM;

	/* Determine 32-bit word position in array */
	regindex = (vlan >> 5) & 0x7F;   /* upper seven bits */

	/* Determine the location of the (VMD) queue index */
	vftabyte =  ((vlan >> 3) & 0x03); /* bits (4:3) indicating byte array */
	bitindex = (vlan & 0x7) << 2;    /* lower 3 bits indicate nibble */

	/* Set the nibble क्रम VMD queue index */
	bits = IXGBE_READ_REG(hw, IXGBE_VFTAVIND(vftabyte, regindex));
	bits &= (~(0x0F << bitindex));
	bits |= (vind << bitindex);
	IXGBE_WRITE_REG(hw, IXGBE_VFTAVIND(vftabyte, regindex), bits);

	/* Determine the location of the bit क्रम this VLAN id */
	bitindex = vlan & 0x1F;   /* lower five bits */

	bits = IXGBE_READ_REG(hw, IXGBE_VFTA(regindex));
	अगर (vlan_on)
		/* Turn on this VLAN id */
		bits |= BIT(bitindex);
	अन्यथा
		/* Turn off this VLAN id */
		bits &= ~BIT(bitindex);
	IXGBE_WRITE_REG(hw, IXGBE_VFTA(regindex), bits);

	वापस 0;
पूर्ण

/**
 *  ixgbe_clear_vfta_82598 - Clear VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Clears the VLAN filer table, and the VMDq index associated with the filter
 **/
अटल s32 ixgbe_clear_vfta_82598(काष्ठा ixgbe_hw *hw)
अणु
	u32 offset;
	u32 vlanbyte;

	क्रम (offset = 0; offset < hw->mac.vft_size; offset++)
		IXGBE_WRITE_REG(hw, IXGBE_VFTA(offset), 0);

	क्रम (vlanbyte = 0; vlanbyte < 4; vlanbyte++)
		क्रम (offset = 0; offset < hw->mac.vft_size; offset++)
			IXGBE_WRITE_REG(hw, IXGBE_VFTAVIND(vlanbyte, offset),
					0);

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_analog_reg8_82598 - Reads 8 bit Atlas analog रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg: analog रेजिस्टर to पढ़ो
 *  @val: पढ़ो value
 *
 *  Perक्रमms पढ़ो operation to Atlas analog रेजिस्टर specअगरied.
 **/
अटल s32 ixgbe_पढ़ो_analog_reg8_82598(काष्ठा ixgbe_hw *hw, u32 reg, u8 *val)
अणु
	u32  atlas_ctl;

	IXGBE_WRITE_REG(hw, IXGBE_ATLASCTL,
			IXGBE_ATLASCTL_WRITE_CMD | (reg << 8));
	IXGBE_WRITE_FLUSH(hw);
	udelay(10);
	atlas_ctl = IXGBE_READ_REG(hw, IXGBE_ATLASCTL);
	*val = (u8)atlas_ctl;

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_analog_reg8_82598 - Writes 8 bit Atlas analog रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg: atlas रेजिस्टर to ग_लिखो
 *  @val: value to ग_लिखो
 *
 *  Perक्रमms ग_लिखो operation to Atlas analog रेजिस्टर specअगरied.
 **/
अटल s32 ixgbe_ग_लिखो_analog_reg8_82598(काष्ठा ixgbe_hw *hw, u32 reg, u8 val)
अणु
	u32  atlas_ctl;

	atlas_ctl = (reg << 8) | val;
	IXGBE_WRITE_REG(hw, IXGBE_ATLASCTL, atlas_ctl);
	IXGBE_WRITE_FLUSH(hw);
	udelay(10);

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_phy_82598 - Reads 8 bit word over I2C पूर्णांकerface.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @dev_addr: address to पढ़ो from
 *  @byte_offset: byte offset to पढ़ो from dev_addr
 *  @eeprom_data: value पढ़ो
 *
 *  Perक्रमms 8 byte पढ़ो operation to SFP module's data over I2C पूर्णांकerface.
 **/
अटल s32 ixgbe_पढ़ो_i2c_phy_82598(काष्ठा ixgbe_hw *hw, u8 dev_addr,
				    u8 byte_offset, u8 *eeprom_data)
अणु
	s32 status = 0;
	u16 sfp_addr = 0;
	u16 sfp_data = 0;
	u16 sfp_stat = 0;
	u16 gssr;
	u32 i;

	अगर (IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_LAN_ID_1)
		gssr = IXGBE_GSSR_PHY1_SM;
	अन्यथा
		gssr = IXGBE_GSSR_PHY0_SM;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, gssr) != 0)
		वापस IXGBE_ERR_SWFW_SYNC;

	अगर (hw->phy.type == ixgbe_phy_nl) अणु
		/*
		 * phy SDA/SCL रेजिस्टरs are at addresses 0xC30A to
		 * 0xC30D.  These रेजिस्टरs are used to talk to the SFP+
		 * module's EEPROM through the SDA/SCL (I2C) पूर्णांकerface.
		 */
		sfp_addr = (dev_addr << 8) + byte_offset;
		sfp_addr = (sfp_addr | IXGBE_I2C_EEPROM_READ_MASK);
		hw->phy.ops.ग_लिखो_reg_mdi(hw,
					  IXGBE_MDIO_PMA_PMD_SDA_SCL_ADDR,
					  MDIO_MMD_PMAPMD,
					  sfp_addr);

		/* Poll status */
		क्रम (i = 0; i < 100; i++) अणु
			hw->phy.ops.पढ़ो_reg_mdi(hw,
						IXGBE_MDIO_PMA_PMD_SDA_SCL_STAT,
						MDIO_MMD_PMAPMD,
						&sfp_stat);
			sfp_stat = sfp_stat & IXGBE_I2C_EEPROM_STATUS_MASK;
			अगर (sfp_stat != IXGBE_I2C_EEPROM_STATUS_IN_PROGRESS)
				अवरोध;
			usleep_range(10000, 20000);
		पूर्ण

		अगर (sfp_stat != IXGBE_I2C_EEPROM_STATUS_PASS) अणु
			hw_dbg(hw, "EEPROM read did not pass.\n");
			status = IXGBE_ERR_SFP_NOT_PRESENT;
			जाओ out;
		पूर्ण

		/* Read data */
		hw->phy.ops.पढ़ो_reg_mdi(hw, IXGBE_MDIO_PMA_PMD_SDA_SCL_DATA,
					MDIO_MMD_PMAPMD, &sfp_data);

		*eeprom_data = (u8)(sfp_data >> 8);
	पूर्ण अन्यथा अणु
		status = IXGBE_ERR_PHY;
	पूर्ण

out:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	वापस status;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_eeprom_82598 - Reads 8 bit word over I2C पूर्णांकerface.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: EEPROM byte offset to पढ़ो
 *  @eeprom_data: value पढ़ो
 *
 *  Perक्रमms 8 byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface.
 **/
अटल s32 ixgbe_पढ़ो_i2c_eeprom_82598(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				       u8 *eeprom_data)
अणु
	वापस ixgbe_पढ़ो_i2c_phy_82598(hw, IXGBE_I2C_EEPROM_DEV_ADDR,
					byte_offset, eeprom_data);
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_sff8472_82598 - Reads 8 bit word over I2C पूर्णांकerface.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset at address 0xA2
 *  @sff8472_data: value पढ़ो
 *
 *  Perक्रमms 8 byte पढ़ो operation to SFP module's SFF-8472 data over I2C
 **/
अटल s32 ixgbe_पढ़ो_i2c_sff8472_82598(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				       u8 *sff8472_data)
अणु
	वापस ixgbe_पढ़ो_i2c_phy_82598(hw, IXGBE_I2C_EEPROM_DEV_ADDR2,
					byte_offset, sff8472_data);
पूर्ण

/**
 *  ixgbe_set_lan_id_multi_port_pcie_82598 - Set LAN id क्रम PCIe multiple
 *  port devices.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls common function and corrects issue with some single port devices
 *  that enable LAN1 but not LAN0.
 **/
अटल व्योम ixgbe_set_lan_id_multi_port_pcie_82598(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_bus_info *bus = &hw->bus;
	u16 pci_gen = 0;
	u16 pci_ctrl2 = 0;

	ixgbe_set_lan_id_multi_port_pcie(hw);

	/* check अगर LAN0 is disabled */
	hw->eeprom.ops.पढ़ो(hw, IXGBE_PCIE_GENERAL_PTR, &pci_gen);
	अगर ((pci_gen != 0) && (pci_gen != 0xFFFF)) अणु

		hw->eeprom.ops.पढ़ो(hw, pci_gen + IXGBE_PCIE_CTRL2, &pci_ctrl2);

		/* अगर LAN0 is completely disabled क्रमce function to 0 */
		अगर ((pci_ctrl2 & IXGBE_PCIE_CTRL2_LAN_DISABLE) &&
		    !(pci_ctrl2 & IXGBE_PCIE_CTRL2_DISABLE_SELECT) &&
		    !(pci_ctrl2 & IXGBE_PCIE_CTRL2_DUMMY_ENABLE)) अणु

			bus->func = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ixgbe_set_rxpba_82598 - Initialize RX packet buffer
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @num_pb: number of packet buffers to allocate
 * @headroom: reserve n KB of headroom
 * @strategy: packet buffer allocation strategy
 **/
अटल व्योम ixgbe_set_rxpba_82598(काष्ठा ixgbe_hw *hw, पूर्णांक num_pb,
				  u32 headroom, पूर्णांक strategy)
अणु
	u32 rxpktsize = IXGBE_RXPBSIZE_64KB;
	u8  i = 0;

	अगर (!num_pb)
		वापस;

	/* Setup Rx packet buffer sizes */
	चयन (strategy) अणु
	हाल PBA_STRATEGY_WEIGHTED:
		/* Setup the first four at 80KB */
		rxpktsize = IXGBE_RXPBSIZE_80KB;
		क्रम (; i < 4; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		/* Setup the last four at 48KB...करोn't re-init i */
		rxpktsize = IXGBE_RXPBSIZE_48KB;
		fallthrough;
	हाल PBA_STRATEGY_EQUAL:
	शेष:
		/* Divide the reमुख्यing Rx packet buffer evenly among the TCs */
		क्रम (; i < IXGBE_MAX_PACKET_BUFFERS; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		अवरोध;
	पूर्ण

	/* Setup Tx packet buffer sizes */
	क्रम (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++)
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), IXGBE_TXPBSIZE_40KB);
पूर्ण

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_82598 = अणु
	.init_hw		= &ixgbe_init_hw_generic,
	.reset_hw		= &ixgbe_reset_hw_82598,
	.start_hw		= &ixgbe_start_hw_82598,
	.clear_hw_cntrs		= &ixgbe_clear_hw_cntrs_generic,
	.get_media_type		= &ixgbe_get_media_type_82598,
	.enable_rx_dma          = &ixgbe_enable_rx_dma_generic,
	.get_mac_addr		= &ixgbe_get_mac_addr_generic,
	.stop_adapter		= &ixgbe_stop_adapter_generic,
	.get_bus_info           = &ixgbe_get_bus_info_generic,
	.set_lan_id             = &ixgbe_set_lan_id_multi_port_pcie_82598,
	.पढ़ो_analog_reg8	= &ixgbe_पढ़ो_analog_reg8_82598,
	.ग_लिखो_analog_reg8	= &ixgbe_ग_लिखो_analog_reg8_82598,
	.setup_link		= &ixgbe_setup_mac_link_82598,
	.set_rxpba		= &ixgbe_set_rxpba_82598,
	.check_link		= &ixgbe_check_mac_link_82598,
	.get_link_capabilities	= &ixgbe_get_link_capabilities_82598,
	.led_on			= &ixgbe_led_on_generic,
	.led_off		= &ixgbe_led_off_generic,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.blink_led_start	= &ixgbe_blink_led_start_generic,
	.blink_led_stop		= &ixgbe_blink_led_stop_generic,
	.set_rar		= &ixgbe_set_rar_generic,
	.clear_rar		= &ixgbe_clear_rar_generic,
	.set_vmdq		= &ixgbe_set_vmdq_82598,
	.clear_vmdq		= &ixgbe_clear_vmdq_82598,
	.init_rx_addrs		= &ixgbe_init_rx_addrs_generic,
	.update_mc_addr_list	= &ixgbe_update_mc_addr_list_generic,
	.enable_mc		= &ixgbe_enable_mc_generic,
	.disable_mc		= &ixgbe_disable_mc_generic,
	.clear_vfta		= &ixgbe_clear_vfta_82598,
	.set_vfta		= &ixgbe_set_vfta_82598,
	.fc_enable		= &ixgbe_fc_enable_82598,
	.setup_fc		= ixgbe_setup_fc_generic,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.set_fw_drv_ver         = शून्य,
	.acquire_swfw_sync      = &ixgbe_acquire_swfw_sync,
	.release_swfw_sync      = &ixgbe_release_swfw_sync,
	.init_swfw_sync		= शून्य,
	.get_thermal_sensor_data = शून्य,
	.init_thermal_sensor_thresh = शून्य,
	.prot_स्वतःc_पढ़ो	= &prot_स्वतःc_पढ़ो_generic,
	.prot_स्वतःc_ग_लिखो	= &prot_स्वतःc_ग_लिखो_generic,
	.enable_rx		= &ixgbe_enable_rx_generic,
	.disable_rx		= &ixgbe_disable_rx_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_eeprom_operations eeprom_ops_82598 = अणु
	.init_params		= &ixgbe_init_eeprom_params_generic,
	.पढ़ो			= &ixgbe_पढ़ो_eerd_generic,
	.ग_लिखो			= &ixgbe_ग_लिखो_eeprom_generic,
	.ग_लिखो_buffer		= &ixgbe_ग_लिखो_eeprom_buffer_bit_bang_generic,
	.पढ़ो_buffer		= &ixgbe_पढ़ो_eerd_buffer_generic,
	.calc_checksum          = &ixgbe_calc_eeprom_checksum_generic,
	.validate_checksum	= &ixgbe_validate_eeprom_checksum_generic,
	.update_checksum	= &ixgbe_update_eeprom_checksum_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_82598 = अणु
	.identअगरy		= &ixgbe_identअगरy_phy_generic,
	.identअगरy_sfp		= &ixgbe_identअगरy_module_generic,
	.init			= &ixgbe_init_phy_ops_82598,
	.reset			= &ixgbe_reset_phy_generic,
	.पढ़ो_reg		= &ixgbe_पढ़ो_phy_reg_generic,
	.ग_लिखो_reg		= &ixgbe_ग_लिखो_phy_reg_generic,
	.पढ़ो_reg_mdi		= &ixgbe_पढ़ो_phy_reg_mdi,
	.ग_लिखो_reg_mdi		= &ixgbe_ग_लिखो_phy_reg_mdi,
	.setup_link		= &ixgbe_setup_phy_link_generic,
	.setup_link_speed	= &ixgbe_setup_phy_link_speed_generic,
	.पढ़ो_i2c_sff8472	= &ixgbe_पढ़ो_i2c_sff8472_82598,
	.पढ़ो_i2c_eeprom	= &ixgbe_पढ़ो_i2c_eeprom_82598,
	.check_overtemp		= &ixgbe_tn_check_overtemp,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_82598_info = अणु
	.mac			= ixgbe_mac_82598EB,
	.get_invariants		= &ixgbe_get_invariants_82598,
	.mac_ops		= &mac_ops_82598,
	.eeprom_ops		= &eeprom_ops_82598,
	.phy_ops		= &phy_ops_82598,
	.mvals			= ixgbe_mvals_8259X,
पूर्ण;

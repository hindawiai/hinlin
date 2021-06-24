<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/netdevice.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_common.h"
#समावेश "ixgbe_phy.h"

अटल s32 ixgbe_acquire_eeprom(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_get_eeprom_semaphore(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_release_eeprom_semaphore(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_पढ़ोy_eeprom(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_standby_eeprom(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_shअगरt_out_eeprom_bits(काष्ठा ixgbe_hw *hw, u16 data,
					u16 count);
अटल u16 ixgbe_shअगरt_in_eeprom_bits(काष्ठा ixgbe_hw *hw, u16 count);
अटल व्योम ixgbe_उठाओ_eeprom_clk(काष्ठा ixgbe_hw *hw, u32 *eec);
अटल व्योम ixgbe_lower_eeprom_clk(काष्ठा ixgbe_hw *hw, u32 *eec);
अटल व्योम ixgbe_release_eeprom(काष्ठा ixgbe_hw *hw);

अटल s32 ixgbe_mta_vector(काष्ठा ixgbe_hw *hw, u8 *mc_addr);
अटल s32 ixgbe_poll_eerd_eewr_करोne(काष्ठा ixgbe_hw *hw, u32 ee_reg);
अटल s32 ixgbe_पढ़ो_eeprom_buffer_bit_bang(काष्ठा ixgbe_hw *hw, u16 offset,
					     u16 words, u16 *data);
अटल s32 ixgbe_ग_लिखो_eeprom_buffer_bit_bang(काष्ठा ixgbe_hw *hw, u16 offset,
					     u16 words, u16 *data);
अटल s32 ixgbe_detect_eeprom_page_size_generic(काष्ठा ixgbe_hw *hw,
						 u16 offset);
अटल s32 ixgbe_disable_pcie_master(काष्ठा ixgbe_hw *hw);

/* Base table क्रम रेजिस्टरs values that change by MAC */
स्थिर u32 ixgbe_mvals_8259X[IXGBE_MVALS_IDX_LIMIT] = अणु
	IXGBE_MVALS_INIT(8259X)
पूर्ण;

/**
 *  ixgbe_device_supports_स्वतःneg_fc - Check अगर phy supports स्वतःneg flow
 *  control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  There are several phys that करो not support स्वतःneg flow control. This
 *  function check the device id to see अगर the associated phy supports
 *  स्वतःneg flow control.
 **/
bool ixgbe_device_supports_स्वतःneg_fc(काष्ठा ixgbe_hw *hw)
अणु
	bool supported = false;
	ixgbe_link_speed speed;
	bool link_up;

	चयन (hw->phy.media_type) अणु
	हाल ixgbe_media_type_fiber:
		/* flow control स्वतःneg black list */
		चयन (hw->device_id) अणु
		हाल IXGBE_DEV_ID_X550EM_A_SFP:
		हाल IXGBE_DEV_ID_X550EM_A_SFP_N:
			supported = false;
			अवरोध;
		शेष:
			hw->mac.ops.check_link(hw, &speed, &link_up, false);
			/* अगर link is करोwn, assume supported */
			अगर (link_up)
				supported = speed == IXGBE_LINK_SPEED_1GB_FULL;
			अन्यथा
				supported = true;
		पूर्ण

		अवरोध;
	हाल ixgbe_media_type_backplane:
		अगर (hw->device_id == IXGBE_DEV_ID_X550EM_X_XFI)
			supported = false;
		अन्यथा
			supported = true;
		अवरोध;
	हाल ixgbe_media_type_copper:
		/* only some copper devices support flow control स्वतःneg */
		चयन (hw->device_id) अणु
		हाल IXGBE_DEV_ID_82599_T3_LOM:
		हाल IXGBE_DEV_ID_X540T:
		हाल IXGBE_DEV_ID_X540T1:
		हाल IXGBE_DEV_ID_X550T:
		हाल IXGBE_DEV_ID_X550T1:
		हाल IXGBE_DEV_ID_X550EM_X_10G_T:
		हाल IXGBE_DEV_ID_X550EM_A_10G_T:
		हाल IXGBE_DEV_ID_X550EM_A_1G_T:
		हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
			supported = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!supported)
		hw_dbg(hw, "Device %x does not support flow control autoneg\n",
		       hw->device_id);

	वापस supported;
पूर्ण

/**
 *  ixgbe_setup_fc_generic - Set up flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Called at init समय to set up flow control.
 **/
s32 ixgbe_setup_fc_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = 0;
	u32 reg = 0, reg_bp = 0;
	u16 reg_cu = 0;
	bool locked = false;

	/*
	 * Validate the requested mode.  Strict IEEE mode करोes not allow
	 * ixgbe_fc_rx_छोड़ो because it will cause us to fail at UNH.
	 */
	अगर (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_छोड़ो) अणु
		hw_dbg(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
	पूर्ण

	/*
	 * 10gig parts करो not have a word in the EEPROM to determine the
	 * शेष flow control setting, so we explicitly set it to full.
	 */
	अगर (hw->fc.requested_mode == ixgbe_fc_शेष)
		hw->fc.requested_mode = ixgbe_fc_full;

	/*
	 * Set up the 1G and 10G flow control advertisement रेजिस्टरs so the
	 * HW will be able to करो fc स्वतःneg once the cable is plugged in.  If
	 * we link at 10G, the 1G advertisement is harmless and vice versa.
	 */
	चयन (hw->phy.media_type) अणु
	हाल ixgbe_media_type_backplane:
		/* some MAC's need RMW protection on AUTOC */
		ret_val = hw->mac.ops.prot_स्वतःc_पढ़ो(hw, &locked, &reg_bp);
		अगर (ret_val)
			वापस ret_val;

		fallthrough; /* only backplane uses स्वतःc */
	हाल ixgbe_media_type_fiber:
		reg = IXGBE_READ_REG(hw, IXGBE_PCS1GANA);

		अवरोध;
	हाल ixgbe_media_type_copper:
		hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_ADVERTISE,
					MDIO_MMD_AN, &reg_cu);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * The possible values of fc.requested_mode are:
	 * 0: Flow control is completely disabled
	 * 1: Rx flow control is enabled (we can receive छोड़ो frames,
	 *    but not send छोड़ो frames).
	 * 2: Tx flow control is enabled (we can send छोड़ो frames but
	 *    we करो not support receiving छोड़ो frames).
	 * 3: Both Rx and Tx flow control (symmetric) are enabled.
	 * other: Invalid.
	 */
	चयन (hw->fc.requested_mode) अणु
	हाल ixgbe_fc_none:
		/* Flow control completely disabled by software override. */
		reg &= ~(IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		अगर (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp &= ~(IXGBE_AUTOC_SYM_PAUSE |
				    IXGBE_AUTOC_ASM_PAUSE);
		अन्यथा अगर (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu &= ~(IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		/*
		 * Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		reg |= IXGBE_PCS1GANA_ASM_PAUSE;
		reg &= ~IXGBE_PCS1GANA_SYM_PAUSE;
		अगर (hw->phy.media_type == ixgbe_media_type_backplane) अणु
			reg_bp |= IXGBE_AUTOC_ASM_PAUSE;
			reg_bp &= ~IXGBE_AUTOC_SYM_PAUSE;
		पूर्ण अन्यथा अगर (hw->phy.media_type == ixgbe_media_type_copper) अणु
			reg_cu |= IXGBE_TAF_ASM_PAUSE;
			reg_cu &= ~IXGBE_TAF_SYM_PAUSE;
		पूर्ण
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		/*
		 * Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE, as such we fall
		 * through to the fc_full statement.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
	हाल ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		reg |= IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE;
		अगर (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp |= IXGBE_AUTOC_SYM_PAUSE |
				  IXGBE_AUTOC_ASM_PAUSE;
		अन्यथा अगर (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu |= IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE;
		अवरोध;
	शेष:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	अगर (hw->mac.type != ixgbe_mac_X540) अणु
		/*
		 * Enable स्वतः-negotiation between the MAC & PHY;
		 * the MAC will advertise clause 37 flow control.
		 */
		IXGBE_WRITE_REG(hw, IXGBE_PCS1GANA, reg);
		reg = IXGBE_READ_REG(hw, IXGBE_PCS1GLCTL);

		/* Disable AN समयout */
		अगर (hw->fc.strict_ieee)
			reg &= ~IXGBE_PCS1GLCTL_AN_1G_TIMEOUT_EN;

		IXGBE_WRITE_REG(hw, IXGBE_PCS1GLCTL, reg);
		hw_dbg(hw, "Set up FC; PCS1GLCTL = 0x%08X\n", reg);
	पूर्ण

	/*
	 * AUTOC restart handles negotiation of 1G and 10G on backplane
	 * and copper. There is no need to set the PCS1GCTL रेजिस्टर.
	 *
	 */
	अगर (hw->phy.media_type == ixgbe_media_type_backplane) अणु
		/* Need the SW/FW semaphore around AUTOC ग_लिखोs अगर 82599 and
		 * LESM is on, likewise reset_pipeline requries the lock as
		 * it also ग_लिखोs AUTOC.
		 */
		ret_val = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw, reg_bp, locked);
		अगर (ret_val)
			वापस ret_val;

	पूर्ण अन्यथा अगर ((hw->phy.media_type == ixgbe_media_type_copper) &&
		   ixgbe_device_supports_स्वतःneg_fc(hw)) अणु
		hw->phy.ops.ग_लिखो_reg(hw, MDIO_AN_ADVERTISE,
				      MDIO_MMD_AN, reg_cu);
	पूर्ण

	hw_dbg(hw, "Set up FC; IXGBE_AUTOC = 0x%08X\n", reg);
	वापस ret_val;
पूर्ण

/**
 *  ixgbe_start_hw_generic - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Starts the hardware by filling the bus info काष्ठाure and media type, clears
 *  all on chip counters, initializes receive address रेजिस्टरs, multicast
 *  table, VLAN filter table, calls routine to set up link and flow control
 *  settings, and leaves transmit and receive units disabled and uninitialized
 **/
s32 ixgbe_start_hw_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val;
	u32 ctrl_ext;
	u16 device_caps;

	/* Set the media type */
	hw->phy.media_type = hw->mac.ops.get_media_type(hw);

	/* Identअगरy the PHY */
	hw->phy.ops.identअगरy(hw);

	/* Clear the VLAN filter table */
	hw->mac.ops.clear_vfta(hw);

	/* Clear statistics रेजिस्टरs */
	hw->mac.ops.clear_hw_cntrs(hw);

	/* Set No Snoop Disable */
	ctrl_ext = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	ctrl_ext |= IXGBE_CTRL_EXT_NS_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_CTRL_EXT, ctrl_ext);
	IXGBE_WRITE_FLUSH(hw);

	/* Setup flow control अगर method क्रम करोing so */
	अगर (hw->mac.ops.setup_fc) अणु
		ret_val = hw->mac.ops.setup_fc(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Cashe bit indicating need क्रम crosstalk fix */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		hw->mac.ops.get_device_caps(hw, &device_caps);
		अगर (device_caps & IXGBE_DEVICE_CAPS_NO_CROSSTALK_WR)
			hw->need_crosstalk_fix = false;
		अन्यथा
			hw->need_crosstalk_fix = true;
		अवरोध;
	शेष:
		hw->need_crosstalk_fix = false;
		अवरोध;
	पूर्ण

	/* Clear adapter stopped flag */
	hw->adapter_stopped = false;

	वापस 0;
पूर्ण

/**
 *  ixgbe_start_hw_gen2 - Init sequence क्रम common device family
 *  @hw: poपूर्णांकer to hw काष्ठाure
 *
 * Perक्रमms the init sequence common to the second generation
 * of 10 GbE devices.
 * Devices in the second generation:
 *     82599
 *     X540
 **/
s32 ixgbe_start_hw_gen2(काष्ठा ixgbe_hw *hw)
अणु
	u32 i;

	/* Clear the rate limiters */
	क्रम (i = 0; i < hw->mac.max_tx_queues; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, i);
		IXGBE_WRITE_REG(hw, IXGBE_RTTBCNRC, 0);
	पूर्ण
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_hw_generic - Generic hardware initialization
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initialize the hardware by resetting the hardware, filling the bus info
 *  काष्ठाure and media type, clears all on chip counters, initializes receive
 *  address रेजिस्टरs, multicast table, VLAN filter table, calls routine to set
 *  up link and flow control settings, and leaves transmit and receive units
 *  disabled and uninitialized
 **/
s32 ixgbe_init_hw_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;

	/* Reset the hardware */
	status = hw->mac.ops.reset_hw(hw);

	अगर (status == 0) अणु
		/* Start the HW */
		status = hw->mac.ops.start_hw(hw);
	पूर्ण

	/* Initialize the LED link active क्रम LED blink support */
	अगर (hw->mac.ops.init_led_link_act)
		hw->mac.ops.init_led_link_act(hw);

	वापस status;
पूर्ण

/**
 *  ixgbe_clear_hw_cntrs_generic - Generic clear hardware counters
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Clears all hardware statistics counters by पढ़ोing them from the hardware
 *  Statistics counters are clear on पढ़ो.
 **/
s32 ixgbe_clear_hw_cntrs_generic(काष्ठा ixgbe_hw *hw)
अणु
	u16 i = 0;

	IXGBE_READ_REG(hw, IXGBE_CRCERRS);
	IXGBE_READ_REG(hw, IXGBE_ILLERRC);
	IXGBE_READ_REG(hw, IXGBE_ERRBC);
	IXGBE_READ_REG(hw, IXGBE_MSPDC);
	क्रम (i = 0; i < 8; i++)
		IXGBE_READ_REG(hw, IXGBE_MPC(i));

	IXGBE_READ_REG(hw, IXGBE_MLFC);
	IXGBE_READ_REG(hw, IXGBE_MRFC);
	IXGBE_READ_REG(hw, IXGBE_RLEC);
	IXGBE_READ_REG(hw, IXGBE_LXONTXC);
	IXGBE_READ_REG(hw, IXGBE_LXOFFTXC);
	अगर (hw->mac.type >= ixgbe_mac_82599EB) अणु
		IXGBE_READ_REG(hw, IXGBE_LXONRXCNT);
		IXGBE_READ_REG(hw, IXGBE_LXOFFRXCNT);
	पूर्ण अन्यथा अणु
		IXGBE_READ_REG(hw, IXGBE_LXONRXC);
		IXGBE_READ_REG(hw, IXGBE_LXOFFRXC);
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		IXGBE_READ_REG(hw, IXGBE_PXONTXC(i));
		IXGBE_READ_REG(hw, IXGBE_PXOFFTXC(i));
		अगर (hw->mac.type >= ixgbe_mac_82599EB) अणु
			IXGBE_READ_REG(hw, IXGBE_PXONRXCNT(i));
			IXGBE_READ_REG(hw, IXGBE_PXOFFRXCNT(i));
		पूर्ण अन्यथा अणु
			IXGBE_READ_REG(hw, IXGBE_PXONRXC(i));
			IXGBE_READ_REG(hw, IXGBE_PXOFFRXC(i));
		पूर्ण
	पूर्ण
	अगर (hw->mac.type >= ixgbe_mac_82599EB)
		क्रम (i = 0; i < 8; i++)
			IXGBE_READ_REG(hw, IXGBE_PXON2OFFCNT(i));
	IXGBE_READ_REG(hw, IXGBE_PRC64);
	IXGBE_READ_REG(hw, IXGBE_PRC127);
	IXGBE_READ_REG(hw, IXGBE_PRC255);
	IXGBE_READ_REG(hw, IXGBE_PRC511);
	IXGBE_READ_REG(hw, IXGBE_PRC1023);
	IXGBE_READ_REG(hw, IXGBE_PRC1522);
	IXGBE_READ_REG(hw, IXGBE_GPRC);
	IXGBE_READ_REG(hw, IXGBE_BPRC);
	IXGBE_READ_REG(hw, IXGBE_MPRC);
	IXGBE_READ_REG(hw, IXGBE_GPTC);
	IXGBE_READ_REG(hw, IXGBE_GORCL);
	IXGBE_READ_REG(hw, IXGBE_GORCH);
	IXGBE_READ_REG(hw, IXGBE_GOTCL);
	IXGBE_READ_REG(hw, IXGBE_GOTCH);
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		क्रम (i = 0; i < 8; i++)
			IXGBE_READ_REG(hw, IXGBE_RNBC(i));
	IXGBE_READ_REG(hw, IXGBE_RUC);
	IXGBE_READ_REG(hw, IXGBE_RFC);
	IXGBE_READ_REG(hw, IXGBE_ROC);
	IXGBE_READ_REG(hw, IXGBE_RJC);
	IXGBE_READ_REG(hw, IXGBE_MNGPRC);
	IXGBE_READ_REG(hw, IXGBE_MNGPDC);
	IXGBE_READ_REG(hw, IXGBE_MNGPTC);
	IXGBE_READ_REG(hw, IXGBE_TORL);
	IXGBE_READ_REG(hw, IXGBE_TORH);
	IXGBE_READ_REG(hw, IXGBE_TPR);
	IXGBE_READ_REG(hw, IXGBE_TPT);
	IXGBE_READ_REG(hw, IXGBE_PTC64);
	IXGBE_READ_REG(hw, IXGBE_PTC127);
	IXGBE_READ_REG(hw, IXGBE_PTC255);
	IXGBE_READ_REG(hw, IXGBE_PTC511);
	IXGBE_READ_REG(hw, IXGBE_PTC1023);
	IXGBE_READ_REG(hw, IXGBE_PTC1522);
	IXGBE_READ_REG(hw, IXGBE_MPTC);
	IXGBE_READ_REG(hw, IXGBE_BPTC);
	क्रम (i = 0; i < 16; i++) अणु
		IXGBE_READ_REG(hw, IXGBE_QPRC(i));
		IXGBE_READ_REG(hw, IXGBE_QPTC(i));
		अगर (hw->mac.type >= ixgbe_mac_82599EB) अणु
			IXGBE_READ_REG(hw, IXGBE_QBRC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBRC_H(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC_L(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC_H(i));
			IXGBE_READ_REG(hw, IXGBE_QPRDC(i));
		पूर्ण अन्यथा अणु
			IXGBE_READ_REG(hw, IXGBE_QBRC(i));
			IXGBE_READ_REG(hw, IXGBE_QBTC(i));
		पूर्ण
	पूर्ण

	अगर (hw->mac.type == ixgbe_mac_X550 || hw->mac.type == ixgbe_mac_X540) अणु
		अगर (hw->phy.id == 0)
			hw->phy.ops.identअगरy(hw);
		hw->phy.ops.पढ़ो_reg(hw, IXGBE_PCRC8ECL, MDIO_MMD_PCS, &i);
		hw->phy.ops.पढ़ो_reg(hw, IXGBE_PCRC8ECH, MDIO_MMD_PCS, &i);
		hw->phy.ops.पढ़ो_reg(hw, IXGBE_LDPCECL, MDIO_MMD_PCS, &i);
		hw->phy.ops.पढ़ो_reg(hw, IXGBE_LDPCECH, MDIO_MMD_PCS, &i);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_pba_string_generic - Reads part number string from EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @pba_num: stores the part number string from the EEPROM
 *  @pba_num_size: part number string buffer length
 *
 *  Reads the part number string from the EEPROM.
 **/
s32 ixgbe_पढ़ो_pba_string_generic(काष्ठा ixgbe_hw *hw, u8 *pba_num,
				  u32 pba_num_size)
अणु
	s32 ret_val;
	u16 data;
	u16 pba_ptr;
	u16 offset;
	u16 length;

	अगर (pba_num == शून्य) अणु
		hw_dbg(hw, "PBA string buffer was null\n");
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	ret_val = hw->eeprom.ops.पढ़ो(hw, IXGBE_PBANUM0_PTR, &data);
	अगर (ret_val) अणु
		hw_dbg(hw, "NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	ret_val = hw->eeprom.ops.पढ़ो(hw, IXGBE_PBANUM1_PTR, &pba_ptr);
	अगर (ret_val) अणु
		hw_dbg(hw, "NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	/*
	 * अगर data is not ptr guard the PBA must be in legacy क्रमmat which
	 * means pba_ptr is actually our second data word क्रम the PBA number
	 * and we can decode it पूर्णांकo an ascii string
	 */
	अगर (data != IXGBE_PBANUM_PTR_GUARD) अणु
		hw_dbg(hw, "NVM PBA number is not stored as string\n");

		/* we will need 11 अक्षरacters to store the PBA */
		अगर (pba_num_size < 11) अणु
			hw_dbg(hw, "PBA string buffer too small\n");
			वापस IXGBE_ERR_NO_SPACE;
		पूर्ण

		/* extract hex string from data and pba_ptr */
		pba_num[0] = (data >> 12) & 0xF;
		pba_num[1] = (data >> 8) & 0xF;
		pba_num[2] = (data >> 4) & 0xF;
		pba_num[3] = data & 0xF;
		pba_num[4] = (pba_ptr >> 12) & 0xF;
		pba_num[5] = (pba_ptr >> 8) & 0xF;
		pba_num[6] = '-';
		pba_num[7] = 0;
		pba_num[8] = (pba_ptr >> 4) & 0xF;
		pba_num[9] = pba_ptr & 0xF;

		/* put a null अक्षरacter on the end of our string */
		pba_num[10] = '\0';

		/* चयन all the data but the '-' to hex अक्षर */
		क्रम (offset = 0; offset < 10; offset++) अणु
			अगर (pba_num[offset] < 0xA)
				pba_num[offset] += '0';
			अन्यथा अगर (pba_num[offset] < 0x10)
				pba_num[offset] += 'A' - 0xA;
		पूर्ण

		वापस 0;
	पूर्ण

	ret_val = hw->eeprom.ops.पढ़ो(hw, pba_ptr, &length);
	अगर (ret_val) अणु
		hw_dbg(hw, "NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर (length == 0xFFFF || length == 0) अणु
		hw_dbg(hw, "NVM PBA number section invalid length\n");
		वापस IXGBE_ERR_PBA_SECTION;
	पूर्ण

	/* check अगर pba_num buffer is big enough */
	अगर (pba_num_size  < (((u32)length * 2) - 1)) अणु
		hw_dbg(hw, "PBA string buffer too small\n");
		वापस IXGBE_ERR_NO_SPACE;
	पूर्ण

	/* trim pba length from start of string */
	pba_ptr++;
	length--;

	क्रम (offset = 0; offset < length; offset++) अणु
		ret_val = hw->eeprom.ops.पढ़ो(hw, pba_ptr + offset, &data);
		अगर (ret_val) अणु
			hw_dbg(hw, "NVM Read Error\n");
			वापस ret_val;
		पूर्ण
		pba_num[offset * 2] = (u8)(data >> 8);
		pba_num[(offset * 2) + 1] = (u8)(data & 0xFF);
	पूर्ण
	pba_num[offset * 2] = '\0';

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_mac_addr_generic - Generic get MAC address
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mac_addr: Adapter MAC address
 *
 *  Reads the adapter's MAC address from first Receive Address Register (RAR0)
 *  A reset of the adapter must be perक्रमmed prior to calling this function
 *  in order क्रम the MAC address to have been loaded from the EEPROM पूर्णांकo RAR0
 **/
s32 ixgbe_get_mac_addr_generic(काष्ठा ixgbe_hw *hw, u8 *mac_addr)
अणु
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(0));
	rar_low = IXGBE_READ_REG(hw, IXGBE_RAL(0));

	क्रम (i = 0; i < 4; i++)
		mac_addr[i] = (u8)(rar_low >> (i*8));

	क्रम (i = 0; i < 2; i++)
		mac_addr[i+4] = (u8)(rar_high >> (i*8));

	वापस 0;
पूर्ण

क्रमागत ixgbe_bus_width ixgbe_convert_bus_width(u16 link_status)
अणु
	चयन (link_status & IXGBE_PCI_LINK_WIDTH) अणु
	हाल IXGBE_PCI_LINK_WIDTH_1:
		वापस ixgbe_bus_width_pcie_x1;
	हाल IXGBE_PCI_LINK_WIDTH_2:
		वापस ixgbe_bus_width_pcie_x2;
	हाल IXGBE_PCI_LINK_WIDTH_4:
		वापस ixgbe_bus_width_pcie_x4;
	हाल IXGBE_PCI_LINK_WIDTH_8:
		वापस ixgbe_bus_width_pcie_x8;
	शेष:
		वापस ixgbe_bus_width_unknown;
	पूर्ण
पूर्ण

क्रमागत ixgbe_bus_speed ixgbe_convert_bus_speed(u16 link_status)
अणु
	चयन (link_status & IXGBE_PCI_LINK_SPEED) अणु
	हाल IXGBE_PCI_LINK_SPEED_2500:
		वापस ixgbe_bus_speed_2500;
	हाल IXGBE_PCI_LINK_SPEED_5000:
		वापस ixgbe_bus_speed_5000;
	हाल IXGBE_PCI_LINK_SPEED_8000:
		वापस ixgbe_bus_speed_8000;
	शेष:
		वापस ixgbe_bus_speed_unknown;
	पूर्ण
पूर्ण

/**
 *  ixgbe_get_bus_info_generic - Generic set PCI bus info
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets the PCI bus info (speed, width, type) within the ixgbe_hw काष्ठाure
 **/
s32 ixgbe_get_bus_info_generic(काष्ठा ixgbe_hw *hw)
अणु
	u16 link_status;

	hw->bus.type = ixgbe_bus_type_pci_express;

	/* Get the negotiated link width and speed from PCI config space */
	link_status = ixgbe_पढ़ो_pci_cfg_word(hw, IXGBE_PCI_LINK_STATUS);

	hw->bus.width = ixgbe_convert_bus_width(link_status);
	hw->bus.speed = ixgbe_convert_bus_speed(link_status);

	hw->mac.ops.set_lan_id(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_set_lan_id_multi_port_pcie - Set LAN id क्रम PCIe multiple port devices
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines the LAN function id by पढ़ोing memory-mapped रेजिस्टरs
 *  and swaps the port value अगर requested.
 **/
व्योम ixgbe_set_lan_id_multi_port_pcie(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_bus_info *bus = &hw->bus;
	u16 ee_ctrl_4;
	u32 reg;

	reg = IXGBE_READ_REG(hw, IXGBE_STATUS);
	bus->func = (reg & IXGBE_STATUS_LAN_ID) >> IXGBE_STATUS_LAN_ID_SHIFT;
	bus->lan_id = bus->func;

	/* check क्रम a port swap */
	reg = IXGBE_READ_REG(hw, IXGBE_FACTPS(hw));
	अगर (reg & IXGBE_FACTPS_LFS)
		bus->func ^= 0x1;

	/* Get MAC instance from EEPROM क्रम configuring CS4227 */
	अगर (hw->device_id == IXGBE_DEV_ID_X550EM_A_SFP) अणु
		hw->eeprom.ops.पढ़ो(hw, IXGBE_EEPROM_CTRL_4, &ee_ctrl_4);
		bus->instance_id = (ee_ctrl_4 & IXGBE_EE_CTRL_4_INST_ID) >>
				   IXGBE_EE_CTRL_4_INST_ID_SHIFT;
	पूर्ण
पूर्ण

/**
 *  ixgbe_stop_adapter_generic - Generic stop Tx/Rx units
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets the adapter_stopped flag within ixgbe_hw काष्ठा. Clears पूर्णांकerrupts,
 *  disables transmit and receive units. The adapter_stopped flag is used by
 *  the shared code and drivers to determine अगर the adapter is in a stopped
 *  state and should not touch the hardware.
 **/
s32 ixgbe_stop_adapter_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 reg_val;
	u16 i;

	/*
	 * Set the adapter_stopped flag so other driver functions stop touching
	 * the hardware
	 */
	hw->adapter_stopped = true;

	/* Disable the receive unit */
	hw->mac.ops.disable_rx(hw);

	/* Clear पूर्णांकerrupt mask to stop पूर्णांकerrupts from being generated */
	IXGBE_WRITE_REG(hw, IXGBE_EIMC, IXGBE_IRQ_CLEAR_MASK);

	/* Clear any pending पूर्णांकerrupts, flush previous ग_लिखोs */
	IXGBE_READ_REG(hw, IXGBE_EICR);

	/* Disable the transmit unit.  Each queue must be disabled. */
	क्रम (i = 0; i < hw->mac.max_tx_queues; i++)
		IXGBE_WRITE_REG(hw, IXGBE_TXDCTL(i), IXGBE_TXDCTL_SWFLSH);

	/* Disable the receive unit by stopping each queue */
	क्रम (i = 0; i < hw->mac.max_rx_queues; i++) अणु
		reg_val = IXGBE_READ_REG(hw, IXGBE_RXDCTL(i));
		reg_val &= ~IXGBE_RXDCTL_ENABLE;
		reg_val |= IXGBE_RXDCTL_SWFLSH;
		IXGBE_WRITE_REG(hw, IXGBE_RXDCTL(i), reg_val);
	पूर्ण

	/* flush all queues disables */
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(1000, 2000);

	/*
	 * Prevent the PCI-E bus from from hanging by disabling PCI-E master
	 * access and verअगरy no pending requests
	 */
	वापस ixgbe_disable_pcie_master(hw);
पूर्ण

/**
 *  ixgbe_init_led_link_act_generic - Store the LED index link/activity.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Store the index क्रम the link active LED. This will be used to support
 *  blinking the LED.
 **/
s32 ixgbe_init_led_link_act_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	u32 led_reg, led_mode;
	u16 i;

	led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);

	/* Get LED link active from the LEDCTL रेजिस्टर */
	क्रम (i = 0; i < 4; i++) अणु
		led_mode = led_reg >> IXGBE_LED_MODE_SHIFT(i);

		अगर ((led_mode & IXGBE_LED_MODE_MASK_BASE) ==
		    IXGBE_LED_LINK_ACTIVE) अणु
			mac->led_link_act = i;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If LEDCTL रेजिस्टर करोes not have the LED link active set, then use
	 * known MAC शेषs.
	 */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_x550em_a:
		mac->led_link_act = 0;
		अवरोध;
	हाल ixgbe_mac_X550EM_x:
		mac->led_link_act = 1;
		अवरोध;
	शेष:
		mac->led_link_act = 2;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_led_on_generic - Turns on the software controllable LEDs.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: led number to turn on
 **/
s32 ixgbe_led_on_generic(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	/* To turn on the LED, set mode to ON. */
	led_reg &= ~IXGBE_LED_MODE_MASK(index);
	led_reg |= IXGBE_LED_ON << IXGBE_LED_MODE_SHIFT(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, led_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_led_off_generic - Turns off the software controllable LEDs.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: led number to turn off
 **/
s32 ixgbe_led_off_generic(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	/* To turn off the LED, set mode to OFF. */
	led_reg &= ~IXGBE_LED_MODE_MASK(index);
	led_reg |= IXGBE_LED_OFF << IXGBE_LED_MODE_SHIFT(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, led_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_eeprom_params_generic - Initialize EEPROM params
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initializes the EEPROM parameters ixgbe_eeprom_info within the
 *  ixgbe_hw काष्ठा in order to set up EEPROM access.
 **/
s32 ixgbe_init_eeprom_params_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_eeprom_info *eeprom = &hw->eeprom;
	u32 eec;
	u16 eeprom_size;

	अगर (eeprom->type == ixgbe_eeprom_uninitialized) अणु
		eeprom->type = ixgbe_eeprom_none;
		/* Set शेष semaphore delay to 10ms which is a well
		 * tested value */
		eeprom->semaphore_delay = 10;
		/* Clear EEPROM page size, it will be initialized as needed */
		eeprom->word_page_size = 0;

		/*
		 * Check क्रम EEPROM present first.
		 * If not present leave as none
		 */
		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		अगर (eec & IXGBE_EEC_PRES) अणु
			eeprom->type = ixgbe_eeprom_spi;

			/*
			 * SPI EEPROM is assumed here.  This code would need to
			 * change अगर a future EEPROM is not SPI.
			 */
			eeprom_size = (u16)((eec & IXGBE_EEC_SIZE) >>
					    IXGBE_EEC_SIZE_SHIFT);
			eeprom->word_size = BIT(eeprom_size +
						 IXGBE_EEPROM_WORD_SIZE_SHIFT);
		पूर्ण

		अगर (eec & IXGBE_EEC_ADDR_SIZE)
			eeprom->address_bits = 16;
		अन्यथा
			eeprom->address_bits = 8;
		hw_dbg(hw, "Eeprom params: type = %d, size = %d, address bits: %d\n",
		       eeprom->type, eeprom->word_size, eeprom->address_bits);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eeprom_buffer_bit_bang_generic - Write EEPROM using bit-bang
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to ग_लिखो
 *  @words: number of words
 *  @data: 16 bit word(s) to ग_लिखो to EEPROM
 *
 *  Reads 16 bit word(s) from EEPROM through bit-bang method
 **/
s32 ixgbe_ग_लिखो_eeprom_buffer_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
					       u16 words, u16 *data)
अणु
	s32 status;
	u16 i, count;

	hw->eeprom.ops.init_params(hw);

	अगर (words == 0)
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	अगर (offset + words > hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	/*
	 * The EEPROM page size cannot be queried from the chip. We करो lazy
	 * initialization. It is worth to करो that when we ग_लिखो large buffer.
	 */
	अगर ((hw->eeprom.word_page_size == 0) &&
	    (words > IXGBE_EEPROM_PAGE_SIZE_MAX))
		ixgbe_detect_eeprom_page_size_generic(hw, offset);

	/*
	 * We cannot hold synchronization semaphores क्रम too दीर्घ
	 * to aव्योम other entity starvation. However it is more efficient
	 * to पढ़ो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += IXGBE_EEPROM_RD_BUFFER_MAX_COUNT) अणु
		count = (words - i) / IXGBE_EEPROM_RD_BUFFER_MAX_COUNT > 0 ?
			 IXGBE_EEPROM_RD_BUFFER_MAX_COUNT : (words - i);
		status = ixgbe_ग_लिखो_eeprom_buffer_bit_bang(hw, offset + i,
							    count, &data[i]);

		अगर (status != 0)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eeprom_buffer_bit_bang - Writes 16 bit word(s) to EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @words: number of word(s)
 *  @data: 16 bit word(s) to be written to the EEPROM
 *
 *  If ixgbe_eeprom_update_checksum is not called after this function, the
 *  EEPROM will most likely contain an invalid checksum.
 **/
अटल s32 ixgbe_ग_लिखो_eeprom_buffer_bit_bang(काष्ठा ixgbe_hw *hw, u16 offset,
					      u16 words, u16 *data)
अणु
	s32 status;
	u16 word;
	u16 page_size;
	u16 i;
	u8 ग_लिखो_opcode = IXGBE_EEPROM_WRITE_OPCODE_SPI;

	/* Prepare the EEPROM क्रम writing  */
	status = ixgbe_acquire_eeprom(hw);
	अगर (status)
		वापस status;

	अगर (ixgbe_पढ़ोy_eeprom(hw) != 0) अणु
		ixgbe_release_eeprom(hw);
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		ixgbe_standby_eeprom(hw);

		/* Send the WRITE ENABLE command (8 bit opcode) */
		ixgbe_shअगरt_out_eeprom_bits(hw,
					    IXGBE_EEPROM_WREN_OPCODE_SPI,
					    IXGBE_EEPROM_OPCODE_BITS);

		ixgbe_standby_eeprom(hw);

		/* Some SPI eeproms use the 8th address bit embedded
		 * in the opcode
		 */
		अगर ((hw->eeprom.address_bits == 8) &&
		    ((offset + i) >= 128))
			ग_लिखो_opcode |= IXGBE_EEPROM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		ixgbe_shअगरt_out_eeprom_bits(hw, ग_लिखो_opcode,
					    IXGBE_EEPROM_OPCODE_BITS);
		ixgbe_shअगरt_out_eeprom_bits(hw, (u16)((offset + i) * 2),
					    hw->eeprom.address_bits);

		page_size = hw->eeprom.word_page_size;

		/* Send the data in burst via SPI */
		करो अणु
			word = data[i];
			word = (word >> 8) | (word << 8);
			ixgbe_shअगरt_out_eeprom_bits(hw, word, 16);

			अगर (page_size == 0)
				अवरोध;

			/* करो not wrap around page */
			अगर (((offset + i) & (page_size - 1)) ==
			    (page_size - 1))
				अवरोध;
		पूर्ण जबतक (++i < words);

		ixgbe_standby_eeprom(hw);
		usleep_range(10000, 20000);
	पूर्ण
	/* Done with writing - release the EEPROM */
	ixgbe_release_eeprom(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eeprom_generic - Writes 16 bit value to EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @data: 16 bit word to be written to the EEPROM
 *
 *  If ixgbe_eeprom_update_checksum is not called after this function, the
 *  EEPROM will most likely contain an invalid checksum.
 **/
s32 ixgbe_ग_लिखो_eeprom_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 data)
अणु
	hw->eeprom.ops.init_params(hw);

	अगर (offset >= hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	वापस ixgbe_ग_लिखो_eeprom_buffer_bit_bang(hw, offset, 1, &data);
पूर्ण

/**
 *  ixgbe_पढ़ो_eeprom_buffer_bit_bang_generic - Read EEPROM using bit-bang
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be पढ़ो
 *  @words: number of word(s)
 *  @data: पढ़ो 16 bit words(s) from EEPROM
 *
 *  Reads 16 bit word(s) from EEPROM through bit-bang method
 **/
s32 ixgbe_पढ़ो_eeprom_buffer_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
					      u16 words, u16 *data)
अणु
	s32 status;
	u16 i, count;

	hw->eeprom.ops.init_params(hw);

	अगर (words == 0)
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	अगर (offset + words > hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	/*
	 * We cannot hold synchronization semaphores क्रम too दीर्घ
	 * to aव्योम other entity starvation. However it is more efficient
	 * to पढ़ो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += IXGBE_EEPROM_RD_BUFFER_MAX_COUNT) अणु
		count = (words - i) / IXGBE_EEPROM_RD_BUFFER_MAX_COUNT > 0 ?
			 IXGBE_EEPROM_RD_BUFFER_MAX_COUNT : (words - i);

		status = ixgbe_पढ़ो_eeprom_buffer_bit_bang(hw, offset + i,
							   count, &data[i]);

		अगर (status)
			वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_eeprom_buffer_bit_bang - Read EEPROM using bit-bang
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be पढ़ो
 *  @words: number of word(s)
 *  @data: पढ़ो 16 bit word(s) from EEPROM
 *
 *  Reads 16 bit word(s) from EEPROM through bit-bang method
 **/
अटल s32 ixgbe_पढ़ो_eeprom_buffer_bit_bang(काष्ठा ixgbe_hw *hw, u16 offset,
					     u16 words, u16 *data)
अणु
	s32 status;
	u16 word_in;
	u8 पढ़ो_opcode = IXGBE_EEPROM_READ_OPCODE_SPI;
	u16 i;

	/* Prepare the EEPROM क्रम पढ़ोing  */
	status = ixgbe_acquire_eeprom(hw);
	अगर (status)
		वापस status;

	अगर (ixgbe_पढ़ोy_eeprom(hw) != 0) अणु
		ixgbe_release_eeprom(hw);
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		ixgbe_standby_eeprom(hw);
		/* Some SPI eeproms use the 8th address bit embedded
		 * in the opcode
		 */
		अगर ((hw->eeprom.address_bits == 8) &&
		    ((offset + i) >= 128))
			पढ़ो_opcode |= IXGBE_EEPROM_A8_OPCODE_SPI;

		/* Send the READ command (opcode + addr) */
		ixgbe_shअगरt_out_eeprom_bits(hw, पढ़ो_opcode,
					    IXGBE_EEPROM_OPCODE_BITS);
		ixgbe_shअगरt_out_eeprom_bits(hw, (u16)((offset + i) * 2),
					    hw->eeprom.address_bits);

		/* Read the data. */
		word_in = ixgbe_shअगरt_in_eeprom_bits(hw, 16);
		data[i] = (word_in >> 8) | (word_in << 8);
	पूर्ण

	/* End this पढ़ो operation */
	ixgbe_release_eeprom(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_eeprom_bit_bang_generic - Read EEPROM word using bit-bang
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be पढ़ो
 *  @data: पढ़ो 16 bit value from EEPROM
 *
 *  Reads 16 bit value from EEPROM through bit-bang method
 **/
s32 ixgbe_पढ़ो_eeprom_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				       u16 *data)
अणु
	hw->eeprom.ops.init_params(hw);

	अगर (offset >= hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	वापस ixgbe_पढ़ो_eeprom_buffer_bit_bang(hw, offset, 1, data);
पूर्ण

/**
 *  ixgbe_पढ़ो_eerd_buffer_generic - Read EEPROM word(s) using EERD
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of word in the EEPROM to पढ़ो
 *  @words: number of word(s)
 *  @data: 16 bit word(s) from the EEPROM
 *
 *  Reads a 16 bit word(s) from the EEPROM using the EERD रेजिस्टर.
 **/
s32 ixgbe_पढ़ो_eerd_buffer_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				   u16 words, u16 *data)
अणु
	u32 eerd;
	s32 status;
	u32 i;

	hw->eeprom.ops.init_params(hw);

	अगर (words == 0)
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	अगर (offset >= hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	क्रम (i = 0; i < words; i++) अणु
		eerd = ((offset + i) << IXGBE_EEPROM_RW_ADDR_SHIFT) |
		       IXGBE_EEPROM_RW_REG_START;

		IXGBE_WRITE_REG(hw, IXGBE_EERD, eerd);
		status = ixgbe_poll_eerd_eewr_करोne(hw, IXGBE_NVM_POLL_READ);

		अगर (status == 0) अणु
			data[i] = (IXGBE_READ_REG(hw, IXGBE_EERD) >>
				   IXGBE_EEPROM_RW_REG_DATA);
		पूर्ण अन्यथा अणु
			hw_dbg(hw, "Eeprom read timed out\n");
			वापस status;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_detect_eeprom_page_size_generic - Detect EEPROM page size
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset within the EEPROM to be used as a scratch pad
 *
 *  Discover EEPROM page size by writing marching data at given offset.
 *  This function is called only when we are writing a new large buffer
 *  at given offset so the data would be overwritten anyway.
 **/
अटल s32 ixgbe_detect_eeprom_page_size_generic(काष्ठा ixgbe_hw *hw,
						 u16 offset)
अणु
	u16 data[IXGBE_EEPROM_PAGE_SIZE_MAX];
	s32 status;
	u16 i;

	क्रम (i = 0; i < IXGBE_EEPROM_PAGE_SIZE_MAX; i++)
		data[i] = i;

	hw->eeprom.word_page_size = IXGBE_EEPROM_PAGE_SIZE_MAX;
	status = ixgbe_ग_लिखो_eeprom_buffer_bit_bang(hw, offset,
					     IXGBE_EEPROM_PAGE_SIZE_MAX, data);
	hw->eeprom.word_page_size = 0;
	अगर (status)
		वापस status;

	status = ixgbe_पढ़ो_eeprom_buffer_bit_bang(hw, offset, 1, data);
	अगर (status)
		वापस status;

	/*
	 * When writing in burst more than the actual page size
	 * EEPROM address wraps around current page.
	 */
	hw->eeprom.word_page_size = IXGBE_EEPROM_PAGE_SIZE_MAX - data[0];

	hw_dbg(hw, "Detected EEPROM page size = %d words.\n",
	       hw->eeprom.word_page_size);
	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_eerd_generic - Read EEPROM word using EERD
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM using the EERD रेजिस्टर.
 **/
s32 ixgbe_पढ़ो_eerd_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 *data)
अणु
	वापस ixgbe_पढ़ो_eerd_buffer_generic(hw, offset, 1, data);
पूर्ण

/**
 *  ixgbe_ग_लिखो_eewr_buffer_generic - Write EEPROM word(s) using EEWR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @words: number of words
 *  @data: word(s) ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word(s) to the EEPROM using the EEWR रेजिस्टर.
 **/
s32 ixgbe_ग_लिखो_eewr_buffer_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				    u16 words, u16 *data)
अणु
	u32 eewr;
	s32 status;
	u16 i;

	hw->eeprom.ops.init_params(hw);

	अगर (words == 0)
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	अगर (offset >= hw->eeprom.word_size)
		वापस IXGBE_ERR_EEPROM;

	क्रम (i = 0; i < words; i++) अणु
		eewr = ((offset + i) << IXGBE_EEPROM_RW_ADDR_SHIFT) |
		       (data[i] << IXGBE_EEPROM_RW_REG_DATA) |
		       IXGBE_EEPROM_RW_REG_START;

		status = ixgbe_poll_eerd_eewr_करोne(hw, IXGBE_NVM_POLL_WRITE);
		अगर (status) अणु
			hw_dbg(hw, "Eeprom write EEWR timed out\n");
			वापस status;
		पूर्ण

		IXGBE_WRITE_REG(hw, IXGBE_EEWR, eewr);

		status = ixgbe_poll_eerd_eewr_करोne(hw, IXGBE_NVM_POLL_WRITE);
		अगर (status) अणु
			hw_dbg(hw, "Eeprom write EEWR timed out\n");
			वापस status;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eewr_generic - Write EEPROM word using EEWR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @data: word ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word to the EEPROM using the EEWR रेजिस्टर.
 **/
s32 ixgbe_ग_लिखो_eewr_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 data)
अणु
	वापस ixgbe_ग_लिखो_eewr_buffer_generic(hw, offset, 1, &data);
पूर्ण

/**
 *  ixgbe_poll_eerd_eewr_करोne - Poll EERD पढ़ो or EEWR ग_लिखो status
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @ee_reg: EEPROM flag क्रम polling
 *
 *  Polls the status bit (bit 1) of the EERD or EEWR to determine when the
 *  पढ़ो or ग_लिखो is करोne respectively.
 **/
अटल s32 ixgbe_poll_eerd_eewr_करोne(काष्ठा ixgbe_hw *hw, u32 ee_reg)
अणु
	u32 i;
	u32 reg;

	क्रम (i = 0; i < IXGBE_EERD_EEWR_ATTEMPTS; i++) अणु
		अगर (ee_reg == IXGBE_NVM_POLL_READ)
			reg = IXGBE_READ_REG(hw, IXGBE_EERD);
		अन्यथा
			reg = IXGBE_READ_REG(hw, IXGBE_EEWR);

		अगर (reg & IXGBE_EEPROM_RW_REG_DONE) अणु
			वापस 0;
		पूर्ण
		udelay(5);
	पूर्ण
	वापस IXGBE_ERR_EEPROM;
पूर्ण

/**
 *  ixgbe_acquire_eeprom - Acquire EEPROM using bit-bang
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Prepares EEPROM क्रम access using bit-bang method. This function should
 *  be called beक्रमe issuing a command to the EEPROM.
 **/
अटल s32 ixgbe_acquire_eeprom(काष्ठा ixgbe_hw *hw)
अणु
	u32 eec;
	u32 i;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM) != 0)
		वापस IXGBE_ERR_SWFW_SYNC;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	/* Request EEPROM Access */
	eec |= IXGBE_EEC_REQ;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);

	क्रम (i = 0; i < IXGBE_EEPROM_GRANT_ATTEMPTS; i++) अणु
		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		अगर (eec & IXGBE_EEC_GNT)
			अवरोध;
		udelay(5);
	पूर्ण

	/* Release अगर grant not acquired */
	अगर (!(eec & IXGBE_EEC_GNT)) अणु
		eec &= ~IXGBE_EEC_REQ;
		IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
		hw_dbg(hw, "Could not acquire EEPROM grant\n");

		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	/* Setup EEPROM क्रम Read/Write */
	/* Clear CS and SK */
	eec &= ~(IXGBE_EEC_CS | IXGBE_EEC_SK);
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
	वापस 0;
पूर्ण

/**
 *  ixgbe_get_eeprom_semaphore - Get hardware semaphore
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets the hardware semaphores so EEPROM access can occur क्रम bit-bang method
 **/
अटल s32 ixgbe_get_eeprom_semaphore(काष्ठा ixgbe_hw *hw)
अणु
	u32 समयout = 2000;
	u32 i;
	u32 swsm;

	/* Get SMBI software semaphore between device drivers first */
	क्रम (i = 0; i < समयout; i++) अणु
		/*
		 * If the SMBI bit is 0 when we पढ़ो it, then the bit will be
		 * set and we have the semaphore
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		अगर (!(swsm & IXGBE_SWSM_SMBI))
			अवरोध;
		usleep_range(50, 100);
	पूर्ण

	अगर (i == समयout) अणु
		hw_dbg(hw, "Driver can't access the Eeprom - SMBI Semaphore not granted.\n");
		/* this release is particularly important because our attempts
		 * above to get the semaphore may have succeeded, and अगर there
		 * was a समयout, we should unconditionally clear the semaphore
		 * bits to मुक्त the driver to make progress
		 */
		ixgbe_release_eeprom_semaphore(hw);

		usleep_range(50, 100);
		/* one last try
		 * If the SMBI bit is 0 when we पढ़ो it, then the bit will be
		 * set and we have the semaphore
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		अगर (swsm & IXGBE_SWSM_SMBI) अणु
			hw_dbg(hw, "Software semaphore SMBI between device drivers not granted.\n");
			वापस IXGBE_ERR_EEPROM;
		पूर्ण
	पूर्ण

	/* Now get the semaphore between SW/FW through the SWESMBI bit */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));

		/* Set the SW EEPROM semaphore bit to request access */
		swsm |= IXGBE_SWSM_SWESMBI;
		IXGBE_WRITE_REG(hw, IXGBE_SWSM(hw), swsm);

		/* If we set the bit successfully then we got the
		 * semaphore.
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		अगर (swsm & IXGBE_SWSM_SWESMBI)
			अवरोध;

		usleep_range(50, 100);
	पूर्ण

	/* Release semaphores and वापस error अगर SW EEPROM semaphore
	 * was not granted because we करोn't have access to the EEPROM
	 */
	अगर (i >= समयout) अणु
		hw_dbg(hw, "SWESMBI Software EEPROM semaphore not granted.\n");
		ixgbe_release_eeprom_semaphore(hw);
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_release_eeprom_semaphore - Release hardware semaphore
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function clears hardware semaphore bits.
 **/
अटल व्योम ixgbe_release_eeprom_semaphore(काष्ठा ixgbe_hw *hw)
अणु
	u32 swsm;

	swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));

	/* Release both semaphores by writing 0 to the bits SWESMBI and SMBI */
	swsm &= ~(IXGBE_SWSM_SWESMBI | IXGBE_SWSM_SMBI);
	IXGBE_WRITE_REG(hw, IXGBE_SWSM(hw), swsm);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 *  ixgbe_पढ़ोy_eeprom - Polls क्रम EEPROM पढ़ोy
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_पढ़ोy_eeprom(काष्ठा ixgbe_hw *hw)
अणु
	u16 i;
	u8 spi_stat_reg;

	/*
	 * Read "Status Register" repeatedly until the LSB is cleared.  The
	 * EEPROM will संकेत that the command has been completed by clearing
	 * bit 0 of the पूर्णांकernal status रेजिस्टर.  If it's not cleared within
	 * 5 milliseconds, then error out.
	 */
	क्रम (i = 0; i < IXGBE_EEPROM_MAX_RETRY_SPI; i += 5) अणु
		ixgbe_shअगरt_out_eeprom_bits(hw, IXGBE_EEPROM_RDSR_OPCODE_SPI,
					    IXGBE_EEPROM_OPCODE_BITS);
		spi_stat_reg = (u8)ixgbe_shअगरt_in_eeprom_bits(hw, 8);
		अगर (!(spi_stat_reg & IXGBE_EEPROM_STATUS_RDY_SPI))
			अवरोध;

		udelay(5);
		ixgbe_standby_eeprom(hw);
	पूर्ण

	/*
	 * On some parts, SPI ग_लिखो समय could vary from 0-20mSec on 3.3V
	 * devices (and only 0-5mSec on 5V devices)
	 */
	अगर (i >= IXGBE_EEPROM_MAX_RETRY_SPI) अणु
		hw_dbg(hw, "SPI EEPROM Status error\n");
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_standby_eeprom - Returns EEPROM to a "standby" state
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_standby_eeprom(काष्ठा ixgbe_hw *hw)
अणु
	u32 eec;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	/* Toggle CS to flush commands */
	eec |= IXGBE_EEC_CS;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
	eec &= ~IXGBE_EEC_CS;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
पूर्ण

/**
 *  ixgbe_shअगरt_out_eeprom_bits - Shअगरt data bits out to the EEPROM.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @data: data to send to the EEPROM
 *  @count: number of bits to shअगरt out
 **/
अटल व्योम ixgbe_shअगरt_out_eeprom_bits(काष्ठा ixgbe_hw *hw, u16 data,
					u16 count)
अणु
	u32 eec;
	u32 mask;
	u32 i;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	/*
	 * Mask is used to shअगरt "count" bits of "data" out to the EEPROM
	 * one bit at a समय.  Determine the starting bit based on count
	 */
	mask = BIT(count - 1);

	क्रम (i = 0; i < count; i++) अणु
		/*
		 * A "1" is shअगरted out to the EEPROM by setting bit "DI" to a
		 * "1", and then raising and then lowering the घड़ी (the SK
		 * bit controls the घड़ी input to the EEPROM).  A "0" is
		 * shअगरted out to the EEPROM by setting "DI" to "0" and then
		 * raising and then lowering the घड़ी.
		 */
		अगर (data & mask)
			eec |= IXGBE_EEC_DI;
		अन्यथा
			eec &= ~IXGBE_EEC_DI;

		IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
		IXGBE_WRITE_FLUSH(hw);

		udelay(1);

		ixgbe_उठाओ_eeprom_clk(hw, &eec);
		ixgbe_lower_eeprom_clk(hw, &eec);

		/*
		 * Shअगरt mask to signअगरy next bit of data to shअगरt in to the
		 * EEPROM
		 */
		mask = mask >> 1;
	पूर्ण

	/* We leave the "DI" bit set to "0" when we leave this routine. */
	eec &= ~IXGBE_EEC_DI;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 *  ixgbe_shअगरt_in_eeprom_bits - Shअगरt data bits in from the EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @count: number of bits to shअगरt
 **/
अटल u16 ixgbe_shअगरt_in_eeprom_bits(काष्ठा ixgbe_hw *hw, u16 count)
अणु
	u32 eec;
	u32 i;
	u16 data = 0;

	/*
	 * In order to पढ़ो a रेजिस्टर from the EEPROM, we need to shअगरt
	 * 'count' bits in from the EEPROM. Bits are "shifted in" by raising
	 * the घड़ी input to the EEPROM (setting the SK bit), and then पढ़ोing
	 * the value of the "DO" bit.  During this "shifting in" process the
	 * "DI" bit should always be clear.
	 */
	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	eec &= ~(IXGBE_EEC_DO | IXGBE_EEC_DI);

	क्रम (i = 0; i < count; i++) अणु
		data = data << 1;
		ixgbe_उठाओ_eeprom_clk(hw, &eec);

		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

		eec &= ~(IXGBE_EEC_DI);
		अगर (eec & IXGBE_EEC_DO)
			data |= 1;

		ixgbe_lower_eeprom_clk(hw, &eec);
	पूर्ण

	वापस data;
पूर्ण

/**
 *  ixgbe_उठाओ_eeprom_clk - Raises the EEPROM's घड़ी input.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @eec: EEC रेजिस्टर's current value
 **/
अटल व्योम ixgbe_उठाओ_eeprom_clk(काष्ठा ixgbe_hw *hw, u32 *eec)
अणु
	/*
	 * Raise the घड़ी input to the EEPROM
	 * (setting the SK bit), then delay
	 */
	*eec = *eec | IXGBE_EEC_SK;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), *eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
पूर्ण

/**
 *  ixgbe_lower_eeprom_clk - Lowers the EEPROM's घड़ी input.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @eec: EEC's current value
 **/
अटल व्योम ixgbe_lower_eeprom_clk(काष्ठा ixgbe_hw *hw, u32 *eec)
अणु
	/*
	 * Lower the घड़ी input to the EEPROM (clearing the SK bit), then
	 * delay
	 */
	*eec = *eec & ~IXGBE_EEC_SK;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), *eec);
	IXGBE_WRITE_FLUSH(hw);
	udelay(1);
पूर्ण

/**
 *  ixgbe_release_eeprom - Release EEPROM, release semaphores
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_release_eeprom(काष्ठा ixgbe_hw *hw)
अणु
	u32 eec;

	eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

	eec |= IXGBE_EEC_CS;  /* Pull CS high */
	eec &= ~IXGBE_EEC_SK; /* Lower SCK */

	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);
	IXGBE_WRITE_FLUSH(hw);

	udelay(1);

	/* Stop requesting EEPROM access */
	eec &= ~IXGBE_EEC_REQ;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), eec);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);

	/*
	 * Delay beक्रमe attempt to obtain semaphore again to allow FW
	 * access. semaphore_delay is in ms we need us क्रम usleep_range
	 */
	usleep_range(hw->eeprom.semaphore_delay * 1000,
		     hw->eeprom.semaphore_delay * 2000);
पूर्ण

/**
 *  ixgbe_calc_eeprom_checksum_generic - Calculates and वापसs the checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_calc_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw)
अणु
	u16 i;
	u16 j;
	u16 checksum = 0;
	u16 length = 0;
	u16 poपूर्णांकer = 0;
	u16 word = 0;

	/* Include 0x0-0x3F in the checksum */
	क्रम (i = 0; i < IXGBE_EEPROM_CHECKSUM; i++) अणु
		अगर (hw->eeprom.ops.पढ़ो(hw, i, &word)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			अवरोध;
		पूर्ण
		checksum += word;
	पूर्ण

	/* Include all data from poपूर्णांकers except क्रम the fw poपूर्णांकer */
	क्रम (i = IXGBE_PCIE_ANALOG_PTR; i < IXGBE_FW_PTR; i++) अणु
		अगर (hw->eeprom.ops.पढ़ो(hw, i, &poपूर्णांकer)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			वापस IXGBE_ERR_EEPROM;
		पूर्ण

		/* If the poपूर्णांकer seems invalid */
		अगर (poपूर्णांकer == 0xFFFF || poपूर्णांकer == 0)
			जारी;

		अगर (hw->eeprom.ops.पढ़ो(hw, poपूर्णांकer, &length)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			वापस IXGBE_ERR_EEPROM;
		पूर्ण

		अगर (length == 0xFFFF || length == 0)
			जारी;

		क्रम (j = poपूर्णांकer + 1; j <= poपूर्णांकer + length; j++) अणु
			अगर (hw->eeprom.ops.पढ़ो(hw, j, &word)) अणु
				hw_dbg(hw, "EEPROM read failed\n");
				वापस IXGBE_ERR_EEPROM;
			पूर्ण
			checksum += word;
		पूर्ण
	पूर्ण

	checksum = (u16)IXGBE_EEPROM_SUM - checksum;

	वापस (s32)checksum;
पूर्ण

/**
 *  ixgbe_validate_eeprom_checksum_generic - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @checksum_val: calculated checksum
 *
 *  Perक्रमms checksum calculation and validates the EEPROM checksum.  If the
 *  caller करोes not need checksum_val, the value can be शून्य.
 **/
s32 ixgbe_validate_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw,
					   u16 *checksum_val)
अणु
	s32 status;
	u16 checksum;
	u16 पढ़ो_checksum = 0;

	/*
	 * Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = hw->eeprom.ops.पढ़ो(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	status = hw->eeprom.ops.calc_checksum(hw);
	अगर (status < 0)
		वापस status;

	checksum = (u16)(status & 0xffff);

	status = hw->eeprom.ops.पढ़ो(hw, IXGBE_EEPROM_CHECKSUM, &पढ़ो_checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	/* Verअगरy पढ़ो checksum from EEPROM is the same as
	 * calculated checksum
	 */
	अगर (पढ़ो_checksum != checksum)
		status = IXGBE_ERR_EEPROM_CHECKSUM;

	/* If the user cares, वापस the calculated checksum */
	अगर (checksum_val)
		*checksum_val = checksum;

	वापस status;
पूर्ण

/**
 *  ixgbe_update_eeprom_checksum_generic - Updates the EEPROM checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_update_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 checksum;

	/*
	 * Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = hw->eeprom.ops.पढ़ो(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	status = hw->eeprom.ops.calc_checksum(hw);
	अगर (status < 0)
		वापस status;

	checksum = (u16)(status & 0xffff);

	status = hw->eeprom.ops.ग_लिखो(hw, IXGBE_EEPROM_CHECKSUM, checksum);

	वापस status;
पूर्ण

/**
 *  ixgbe_set_rar_generic - Set Rx address रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: Receive address रेजिस्टर to ग_लिखो
 *  @addr: Address to put पूर्णांकo receive address रेजिस्टर
 *  @vmdq: VMDq "set" or "pool" index
 *  @enable_addr: set flag that address is active
 *
 *  Puts an ethernet address पूर्णांकo a receive address रेजिस्टर.
 **/
s32 ixgbe_set_rar_generic(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr, u32 vmdq,
			  u32 enable_addr)
अणु
	u32 rar_low, rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	अगर (index >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", index);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	/* setup VMDq pool selection beक्रमe this RAR माला_लो enabled */
	hw->mac.ops.set_vmdq(hw, index, vmdq);

	/*
	 * HW expects these in little endian so we reverse the byte
	 * order from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] |
		   ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) |
		   ((u32)addr[3] << 24));
	/*
	 * Some parts put the VMDq setting in the extra RAH bits,
	 * so save everything except the lower 16 bits that hold part
	 * of the address and the address valid bit.
	 */
	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(index));
	rar_high &= ~(0x0000FFFF | IXGBE_RAH_AV);
	rar_high |= ((u32)addr[4] | ((u32)addr[5] << 8));

	अगर (enable_addr != 0)
		rar_high |= IXGBE_RAH_AV;

	/* Record lower 32 bits of MAC address and then make
	 * sure that ग_लिखो is flushed to hardware beक्रमe writing
	 * the upper 16 bits and setting the valid bit.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_RAL(index), rar_low);
	IXGBE_WRITE_FLUSH(hw);
	IXGBE_WRITE_REG(hw, IXGBE_RAH(index), rar_high);

	वापस 0;
पूर्ण

/**
 *  ixgbe_clear_rar_generic - Remove Rx address रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: Receive address रेजिस्टर to ग_लिखो
 *
 *  Clears an ethernet address from a receive address रेजिस्टर.
 **/
s32 ixgbe_clear_rar_generic(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	अगर (index >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", index);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	/*
	 * Some parts put the VMDq setting in the extra RAH bits,
	 * so save everything except the lower 16 bits that hold part
	 * of the address and the address valid bit.
	 */
	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(index));
	rar_high &= ~(0x0000FFFF | IXGBE_RAH_AV);

	/* Clear the address valid bit and upper 16 bits of the address
	 * beक्रमe clearing the lower bits. This way we aren't updating
	 * a live filter.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_RAH(index), rar_high);
	IXGBE_WRITE_FLUSH(hw);
	IXGBE_WRITE_REG(hw, IXGBE_RAL(index), 0);

	/* clear VMDq pool/queue selection क्रम this RAR */
	hw->mac.ops.clear_vmdq(hw, index, IXGBE_CLEAR_VMDQ_ALL);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_rx_addrs_generic - Initializes receive address filters.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Places the MAC address in receive address रेजिस्टर 0 and clears the rest
 *  of the receive address रेजिस्टरs. Clears the multicast table. Assumes
 *  the receiver is in reset when the routine is called.
 **/
s32 ixgbe_init_rx_addrs_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 i;
	u32 rar_entries = hw->mac.num_rar_entries;

	/*
	 * If the current mac address is valid, assume it is a software override
	 * to the permanent address.
	 * Otherwise, use the permanent address from the eeprom.
	 */
	अगर (!is_valid_ether_addr(hw->mac.addr)) अणु
		/* Get the MAC address from the RAR0 क्रम later reference */
		hw->mac.ops.get_mac_addr(hw, hw->mac.addr);

		hw_dbg(hw, " Keeping Current RAR0 Addr =%pM\n", hw->mac.addr);
	पूर्ण अन्यथा अणु
		/* Setup the receive address. */
		hw_dbg(hw, "Overriding MAC Address in RAR[0]\n");
		hw_dbg(hw, " New MAC Addr =%pM\n", hw->mac.addr);

		hw->mac.ops.set_rar(hw, 0, hw->mac.addr, 0, IXGBE_RAH_AV);
	पूर्ण

	/*  clear VMDq pool/queue selection क्रम RAR 0 */
	hw->mac.ops.clear_vmdq(hw, 0, IXGBE_CLEAR_VMDQ_ALL);

	hw->addr_ctrl.overflow_promisc = 0;

	hw->addr_ctrl.rar_used_count = 1;

	/* Zero out the other receive addresses. */
	hw_dbg(hw, "Clearing RAR[1-%d]\n", rar_entries - 1);
	क्रम (i = 1; i < rar_entries; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_RAL(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_RAH(i), 0);
	पूर्ण

	/* Clear the MTA */
	hw->addr_ctrl.mta_in_use = 0;
	IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL, hw->mac.mc_filter_type);

	hw_dbg(hw, " Clearing MTA\n");
	क्रम (i = 0; i < hw->mac.mcft_size; i++)
		IXGBE_WRITE_REG(hw, IXGBE_MTA(i), 0);

	अगर (hw->mac.ops.init_uta_tables)
		hw->mac.ops.init_uta_tables(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_mta_vector - Determines bit-vector in multicast table to set
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mc_addr: the multicast address
 *
 *  Extracts the 12 bits, from a multicast address, to determine which
 *  bit-vector to set in the multicast table. The hardware uses 12 bits, from
 *  incoming rx multicast addresses, to determine the bit-vector to check in
 *  the MTA. Which of the 4 combination, of 12-bits, the hardware uses is set
 *  by the MO field of the MCSTCTRL. The MO field is set during initialization
 *  to mc_filter_type.
 **/
अटल s32 ixgbe_mta_vector(काष्ठा ixgbe_hw *hw, u8 *mc_addr)
अणु
	u32 vector = 0;

	चयन (hw->mac.mc_filter_type) अणु
	हाल 0:   /* use bits [47:36] of the address */
		vector = ((mc_addr[4] >> 4) | (((u16)mc_addr[5]) << 4));
		अवरोध;
	हाल 1:   /* use bits [46:35] of the address */
		vector = ((mc_addr[4] >> 3) | (((u16)mc_addr[5]) << 5));
		अवरोध;
	हाल 2:   /* use bits [45:34] of the address */
		vector = ((mc_addr[4] >> 2) | (((u16)mc_addr[5]) << 6));
		अवरोध;
	हाल 3:   /* use bits [43:32] of the address */
		vector = ((mc_addr[4]) | (((u16)mc_addr[5]) << 8));
		अवरोध;
	शेष:  /* Invalid mc_filter_type */
		hw_dbg(hw, "MC filter type param set incorrectly\n");
		अवरोध;
	पूर्ण

	/* vector can only be 12-bits or boundary will be exceeded */
	vector &= 0xFFF;
	वापस vector;
पूर्ण

/**
 *  ixgbe_set_mta - Set bit-vector in multicast table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mc_addr: Multicast address
 *
 *  Sets the bit-vector in the multicast table.
 **/
अटल व्योम ixgbe_set_mta(काष्ठा ixgbe_hw *hw, u8 *mc_addr)
अणु
	u32 vector;
	u32 vector_bit;
	u32 vector_reg;

	hw->addr_ctrl.mta_in_use++;

	vector = ixgbe_mta_vector(hw, mc_addr);
	hw_dbg(hw, " bit-vector = 0x%03X\n", vector);

	/*
	 * The MTA is a रेजिस्टर array of 128 32-bit रेजिस्टरs. It is treated
	 * like an array of 4096 bits.  We want to set bit
	 * BitArray[vector_value]. So we figure out what रेजिस्टर the bit is
	 * in, पढ़ो it, OR in the new bit, then ग_लिखो back the new value.  The
	 * रेजिस्टर is determined by the upper 7 bits of the vector value and
	 * the bit within that रेजिस्टर are determined by the lower 5 bits of
	 * the value.
	 */
	vector_reg = (vector >> 5) & 0x7F;
	vector_bit = vector & 0x1F;
	hw->mac.mta_shaकरोw[vector_reg] |= BIT(vector_bit);
पूर्ण

/**
 *  ixgbe_update_mc_addr_list_generic - Updates MAC list of multicast addresses
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @netdev: poपूर्णांकer to net device काष्ठाure
 *
 *  The given list replaces any existing list. Clears the MC addrs from receive
 *  address रेजिस्टरs and the multicast table. Uses unused receive address
 *  रेजिस्टरs क्रम the first multicast addresses, and hashes the rest पूर्णांकo the
 *  multicast table.
 **/
s32 ixgbe_update_mc_addr_list_generic(काष्ठा ixgbe_hw *hw,
				      काष्ठा net_device *netdev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u32 i;

	/*
	 * Set the new number of MC addresses that we are being requested to
	 * use.
	 */
	hw->addr_ctrl.num_mc_addrs = netdev_mc_count(netdev);
	hw->addr_ctrl.mta_in_use = 0;

	/* Clear mta_shaकरोw */
	hw_dbg(hw, " Clearing MTA\n");
	स_रखो(&hw->mac.mta_shaकरोw, 0, माप(hw->mac.mta_shaकरोw));

	/* Update mta shaकरोw */
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		hw_dbg(hw, " Adding the multicast addresses:\n");
		ixgbe_set_mta(hw, ha->addr);
	पूर्ण

	/* Enable mta */
	क्रम (i = 0; i < hw->mac.mcft_size; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_MTA(0), i,
				      hw->mac.mta_shaकरोw[i]);

	अगर (hw->addr_ctrl.mta_in_use > 0)
		IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL,
				IXGBE_MCSTCTRL_MFE | hw->mac.mc_filter_type);

	hw_dbg(hw, "ixgbe_update_mc_addr_list_generic Complete\n");
	वापस 0;
पूर्ण

/**
 *  ixgbe_enable_mc_generic - Enable multicast address in RAR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enables multicast address in RAR and the use of the multicast hash table.
 **/
s32 ixgbe_enable_mc_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_addr_filter_info *a = &hw->addr_ctrl;

	अगर (a->mta_in_use > 0)
		IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL, IXGBE_MCSTCTRL_MFE |
				hw->mac.mc_filter_type);

	वापस 0;
पूर्ण

/**
 *  ixgbe_disable_mc_generic - Disable multicast address in RAR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Disables multicast address in RAR and the use of the multicast hash table.
 **/
s32 ixgbe_disable_mc_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_addr_filter_info *a = &hw->addr_ctrl;

	अगर (a->mta_in_use > 0)
		IXGBE_WRITE_REG(hw, IXGBE_MCSTCTRL, hw->mac.mc_filter_type);

	वापस 0;
पूर्ण

/**
 *  ixgbe_fc_enable_generic - Enable flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enable flow control according to the current settings.
 **/
s32 ixgbe_fc_enable_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 mflcn_reg, fccfg_reg;
	u32 reg;
	u32 fcrtl, fcrth;
	पूर्णांक i;

	/* Validate the water mark configuration. */
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

	/* Negotiate the fc mode to use */
	hw->mac.ops.fc_स्वतःneg(hw);

	/* Disable any previous flow control settings */
	mflcn_reg = IXGBE_READ_REG(hw, IXGBE_MFLCN);
	mflcn_reg &= ~(IXGBE_MFLCN_RPFCE_MASK | IXGBE_MFLCN_RFCE);

	fccfg_reg = IXGBE_READ_REG(hw, IXGBE_FCCFG);
	fccfg_reg &= ~(IXGBE_FCCFG_TFCE_802_3X | IXGBE_FCCFG_TFCE_PRIORITY);

	/*
	 * The possible values of fc.current_mode are:
	 * 0: Flow control is completely disabled
	 * 1: Rx flow control is enabled (we can receive छोड़ो frames,
	 *    but not send छोड़ो frames).
	 * 2: Tx flow control is enabled (we can send छोड़ो frames but
	 *    we करो not support receiving छोड़ो frames).
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
		mflcn_reg |= IXGBE_MFLCN_RFCE;
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		/*
		 * Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		fccfg_reg |= IXGBE_FCCFG_TFCE_802_3X;
		अवरोध;
	हाल ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		mflcn_reg |= IXGBE_MFLCN_RFCE;
		fccfg_reg |= IXGBE_FCCFG_TFCE_802_3X;
		अवरोध;
	शेष:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	/* Set 802.3x based flow control settings. */
	mflcn_reg |= IXGBE_MFLCN_DPF;
	IXGBE_WRITE_REG(hw, IXGBE_MFLCN, mflcn_reg);
	IXGBE_WRITE_REG(hw, IXGBE_FCCFG, fccfg_reg);

	/* Set up and enable Rx high/low water mark thresholds, enable XON. */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		अगर ((hw->fc.current_mode & ixgbe_fc_tx_छोड़ो) &&
		    hw->fc.high_water[i]) अणु
			fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL_82599(i), fcrtl);
			fcrth = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
		पूर्ण अन्यथा अणु
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL_82599(i), 0);
			/*
			 * In order to prevent Tx hangs when the पूर्णांकernal Tx
			 * चयन is enabled we must set the high water mark
			 * to the Rx packet buffer size - 24KB.  This allows
			 * the Tx चयन to function even under heavy Rx
			 * workloads.
			 */
			fcrth = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(i)) - 24576;
		पूर्ण

		IXGBE_WRITE_REG(hw, IXGBE_FCRTH_82599(i), fcrth);
	पूर्ण

	/* Configure छोड़ो समय (2 TCs per रेजिस्टर) */
	reg = hw->fc.छोड़ो_समय * 0x00010001U;
	क्रम (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);

	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.छोड़ो_समय / 2);

	वापस 0;
पूर्ण

/**
 *  ixgbe_negotiate_fc - Negotiate flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @adv_reg: flow control advertised settings
 *  @lp_reg: link partner's flow control settings
 *  @adv_sym: symmetric छोड़ो bit in advertisement
 *  @adv_यंत्र: asymmetric छोड़ो bit in advertisement
 *  @lp_sym: symmetric छोड़ो bit in link partner advertisement
 *  @lp_यंत्र: asymmetric छोड़ो bit in link partner advertisement
 *
 *  Find the पूर्णांकersection between advertised settings and link partner's
 *  advertised settings
 **/
s32 ixgbe_negotiate_fc(काष्ठा ixgbe_hw *hw, u32 adv_reg, u32 lp_reg,
		       u32 adv_sym, u32 adv_यंत्र, u32 lp_sym, u32 lp_यंत्र)
अणु
	अगर ((!(adv_reg)) ||  (!(lp_reg)))
		वापस IXGBE_ERR_FC_NOT_NEGOTIATED;

	अगर ((adv_reg & adv_sym) && (lp_reg & lp_sym)) अणु
		/*
		 * Now we need to check अगर the user selected Rx ONLY
		 * of छोड़ो frames.  In this हाल, we had to advertise
		 * FULL flow control because we could not advertise RX
		 * ONLY. Hence, we must now check to see अगर we need to
		 * turn OFF the TRANSMISSION of PAUSE frames.
		 */
		अगर (hw->fc.requested_mode == ixgbe_fc_full) अणु
			hw->fc.current_mode = ixgbe_fc_full;
			hw_dbg(hw, "Flow Control = FULL.\n");
		पूर्ण अन्यथा अणु
			hw->fc.current_mode = ixgbe_fc_rx_छोड़ो;
			hw_dbg(hw, "Flow Control=RX PAUSE frames only\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(adv_reg & adv_sym) && (adv_reg & adv_यंत्र) &&
		   (lp_reg & lp_sym) && (lp_reg & lp_यंत्र)) अणु
		hw->fc.current_mode = ixgbe_fc_tx_छोड़ो;
		hw_dbg(hw, "Flow Control = TX PAUSE frames only.\n");
	पूर्ण अन्यथा अगर ((adv_reg & adv_sym) && (adv_reg & adv_यंत्र) &&
		   !(lp_reg & lp_sym) && (lp_reg & lp_यंत्र)) अणु
		hw->fc.current_mode = ixgbe_fc_rx_छोड़ो;
		hw_dbg(hw, "Flow Control = RX PAUSE frames only.\n");
	पूर्ण अन्यथा अणु
		hw->fc.current_mode = ixgbe_fc_none;
		hw_dbg(hw, "Flow Control = NONE.\n");
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg_fiber - Enable flow control on 1 gig fiber
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enable flow control according on 1 gig fiber.
 **/
अटल s32 ixgbe_fc_स्वतःneg_fiber(काष्ठा ixgbe_hw *hw)
अणु
	u32 pcs_anadv_reg, pcs_lpab_reg, linkstat;
	s32 ret_val;

	/*
	 * On multispeed fiber at 1g, bail out अगर
	 * - link is up but AN did not complete, or अगर
	 * - link is up and AN completed but समयd out
	 */

	linkstat = IXGBE_READ_REG(hw, IXGBE_PCS1GLSTA);
	अगर ((!!(linkstat & IXGBE_PCS1GLSTA_AN_COMPLETE) == 0) ||
	    (!!(linkstat & IXGBE_PCS1GLSTA_AN_TIMED_OUT) == 1))
		वापस IXGBE_ERR_FC_NOT_NEGOTIATED;

	pcs_anadv_reg = IXGBE_READ_REG(hw, IXGBE_PCS1GANA);
	pcs_lpab_reg = IXGBE_READ_REG(hw, IXGBE_PCS1GANLP);

	ret_val =  ixgbe_negotiate_fc(hw, pcs_anadv_reg,
			       pcs_lpab_reg, IXGBE_PCS1GANA_SYM_PAUSE,
			       IXGBE_PCS1GANA_ASM_PAUSE,
			       IXGBE_PCS1GANA_SYM_PAUSE,
			       IXGBE_PCS1GANA_ASM_PAUSE);

	वापस ret_val;
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg_backplane - Enable flow control IEEE clause 37
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enable flow control according to IEEE clause 37.
 **/
अटल s32 ixgbe_fc_स्वतःneg_backplane(काष्ठा ixgbe_hw *hw)
अणु
	u32 links2, anlp1_reg, स्वतःc_reg, links;
	s32 ret_val;

	/*
	 * On backplane, bail out अगर
	 * - backplane स्वतःneg was not completed, or अगर
	 * - we are 82599 and link partner is not AN enabled
	 */
	links = IXGBE_READ_REG(hw, IXGBE_LINKS);
	अगर ((links & IXGBE_LINKS_KX_AN_COMP) == 0)
		वापस IXGBE_ERR_FC_NOT_NEGOTIATED;

	अगर (hw->mac.type == ixgbe_mac_82599EB) अणु
		links2 = IXGBE_READ_REG(hw, IXGBE_LINKS2);
		अगर ((links2 & IXGBE_LINKS2_AN_SUPPORTED) == 0)
			वापस IXGBE_ERR_FC_NOT_NEGOTIATED;
	पूर्ण
	/*
	 * Read the 10g AN स्वतःc and LP ability रेजिस्टरs and resolve
	 * local flow control settings accordingly
	 */
	स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	anlp1_reg = IXGBE_READ_REG(hw, IXGBE_ANLP1);

	ret_val = ixgbe_negotiate_fc(hw, स्वतःc_reg,
		anlp1_reg, IXGBE_AUTOC_SYM_PAUSE, IXGBE_AUTOC_ASM_PAUSE,
		IXGBE_ANLP1_SYM_PAUSE, IXGBE_ANLP1_ASM_PAUSE);

	वापस ret_val;
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg_copper - Enable flow control IEEE clause 37
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enable flow control according to IEEE clause 37.
 **/
अटल s32 ixgbe_fc_स्वतःneg_copper(काष्ठा ixgbe_hw *hw)
अणु
	u16 technology_ability_reg = 0;
	u16 lp_technology_ability_reg = 0;

	hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_ADVERTISE,
			     MDIO_MMD_AN,
			     &technology_ability_reg);
	hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_LPA,
			     MDIO_MMD_AN,
			     &lp_technology_ability_reg);

	वापस ixgbe_negotiate_fc(hw, (u32)technology_ability_reg,
				  (u32)lp_technology_ability_reg,
				  IXGBE_TAF_SYM_PAUSE, IXGBE_TAF_ASM_PAUSE,
				  IXGBE_TAF_SYM_PAUSE, IXGBE_TAF_ASM_PAUSE);
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg - Configure flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Compares our advertised flow control capabilities to those advertised by
 *  our link partner, and determines the proper flow control mode to use.
 **/
व्योम ixgbe_fc_स्वतःneg(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = IXGBE_ERR_FC_NOT_NEGOTIATED;
	ixgbe_link_speed speed;
	bool link_up;

	/*
	 * AN should have completed when the cable was plugged in.
	 * Look क्रम reasons to bail out.  Bail out अगर:
	 * - FC स्वतःneg is disabled, or अगर
	 * - link is not up.
	 *
	 * Since we're being called from an LSC, link is alपढ़ोy known to be up.
	 * So use link_up_रुको_to_complete=false.
	 */
	अगर (hw->fc.disable_fc_स्वतःneg)
		जाओ out;

	hw->mac.ops.check_link(hw, &speed, &link_up, false);
	अगर (!link_up)
		जाओ out;

	चयन (hw->phy.media_type) अणु
	/* Autoneg flow control on fiber adapters */
	हाल ixgbe_media_type_fiber:
		अगर (speed == IXGBE_LINK_SPEED_1GB_FULL)
			ret_val = ixgbe_fc_स्वतःneg_fiber(hw);
		अवरोध;

	/* Autoneg flow control on backplane adapters */
	हाल ixgbe_media_type_backplane:
		ret_val = ixgbe_fc_स्वतःneg_backplane(hw);
		अवरोध;

	/* Autoneg flow control on copper adapters */
	हाल ixgbe_media_type_copper:
		अगर (ixgbe_device_supports_स्वतःneg_fc(hw))
			ret_val = ixgbe_fc_स्वतःneg_copper(hw);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

out:
	अगर (ret_val == 0) अणु
		hw->fc.fc_was_स्वतःnegged = true;
	पूर्ण अन्यथा अणु
		hw->fc.fc_was_स्वतःnegged = false;
		hw->fc.current_mode = hw->fc.requested_mode;
	पूर्ण
पूर्ण

/**
 * ixgbe_pcie_समयout_poll - Return number of बार to poll क्रम completion
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * System-wide समयout range is encoded in PCIe Device Control2 रेजिस्टर.
 *
 *  Add 10% to specअगरied maximum and वापस the number of बार to poll क्रम
 *  completion समयout, in units of 100 microsec.  Never वापस less than
 *  800 = 80 millisec.
 **/
अटल u32 ixgbe_pcie_समयout_poll(काष्ठा ixgbe_hw *hw)
अणु
	s16 devctl2;
	u32 pollcnt;

	devctl2 = ixgbe_पढ़ो_pci_cfg_word(hw, IXGBE_PCI_DEVICE_CONTROL2);
	devctl2 &= IXGBE_PCIDEVCTRL2_TIMEO_MASK;

	चयन (devctl2) अणु
	हाल IXGBE_PCIDEVCTRL2_65_130ms:
		 pollcnt = 1300;         /* 130 millisec */
		अवरोध;
	हाल IXGBE_PCIDEVCTRL2_260_520ms:
		pollcnt = 5200;         /* 520 millisec */
		अवरोध;
	हाल IXGBE_PCIDEVCTRL2_1_2s:
		pollcnt = 20000;        /* 2 sec */
		अवरोध;
	हाल IXGBE_PCIDEVCTRL2_4_8s:
		pollcnt = 80000;        /* 8 sec */
		अवरोध;
	हाल IXGBE_PCIDEVCTRL2_17_34s:
		pollcnt = 34000;        /* 34 sec */
		अवरोध;
	हाल IXGBE_PCIDEVCTRL2_50_100us:        /* 100 microsecs */
	हाल IXGBE_PCIDEVCTRL2_1_2ms:           /* 2 millisecs */
	हाल IXGBE_PCIDEVCTRL2_16_32ms:         /* 32 millisec */
	हाल IXGBE_PCIDEVCTRL2_16_32ms_def:     /* 32 millisec शेष */
	शेष:
		pollcnt = 800;          /* 80 millisec minimum */
		अवरोध;
	पूर्ण

	/* add 10% to spec maximum */
	वापस (pollcnt * 11) / 10;
पूर्ण

/**
 *  ixgbe_disable_pcie_master - Disable PCI-express master access
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Disables PCI-Express master access and verअगरies there are no pending
 *  requests. IXGBE_ERR_MASTER_REQUESTS_PENDING is वापसed अगर master disable
 *  bit hasn't caused the master requests to be disabled, अन्यथा 0
 *  is वापसed signअगरying master requests disabled.
 **/
अटल s32 ixgbe_disable_pcie_master(काष्ठा ixgbe_hw *hw)
अणु
	u32 i, poll;
	u16 value;

	/* Always set this bit to ensure any future transactions are blocked */
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, IXGBE_CTRL_GIO_DIS);

	/* Poll क्रम bit to पढ़ो as set */
	क्रम (i = 0; i < IXGBE_PCI_MASTER_DISABLE_TIMEOUT; i++) अणु
		अगर (IXGBE_READ_REG(hw, IXGBE_CTRL) & IXGBE_CTRL_GIO_DIS)
			अवरोध;
		usleep_range(100, 120);
	पूर्ण
	अगर (i >= IXGBE_PCI_MASTER_DISABLE_TIMEOUT) अणु
		hw_dbg(hw, "GIO disable did not set - requesting resets\n");
		जाओ gio_disable_fail;
	पूर्ण

	/* Exit अगर master requests are blocked */
	अगर (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO) ||
	    ixgbe_हटाओd(hw->hw_addr))
		वापस 0;

	/* Poll क्रम master request bit to clear */
	क्रम (i = 0; i < IXGBE_PCI_MASTER_DISABLE_TIMEOUT; i++) अणु
		udelay(100);
		अगर (!(IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_GIO))
			वापस 0;
	पूर्ण

	/*
	 * Two consecutive resets are required via CTRL.RST per datasheet
	 * 5.2.5.3.2 Master Disable.  We set a flag to inक्रमm the reset routine
	 * of this need.  The first reset prevents new master requests from
	 * being issued by our device.  We then must रुको 1usec or more क्रम any
	 * reमुख्यing completions from the PCIe bus to trickle in, and then reset
	 * again to clear out any effects they may have had on our device.
	 */
	hw_dbg(hw, "GIO Master Disable bit didn't clear - requesting resets\n");
gio_disable_fail:
	hw->mac.flags |= IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;

	अगर (hw->mac.type >= ixgbe_mac_X550)
		वापस 0;

	/*
	 * Beक्रमe proceeding, make sure that the PCIe block करोes not have
	 * transactions pending.
	 */
	poll = ixgbe_pcie_समयout_poll(hw);
	क्रम (i = 0; i < poll; i++) अणु
		udelay(100);
		value = ixgbe_पढ़ो_pci_cfg_word(hw, IXGBE_PCI_DEVICE_STATUS);
		अगर (ixgbe_हटाओd(hw->hw_addr))
			वापस 0;
		अगर (!(value & IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING))
			वापस 0;
	पूर्ण

	hw_dbg(hw, "PCIe transaction pending bit also did not clear.\n");
	वापस IXGBE_ERR_MASTER_REQUESTS_PENDING;
पूर्ण

/**
 *  ixgbe_acquire_swfw_sync - Acquire SWFW semaphore
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mask: Mask to specअगरy which semaphore to acquire
 *
 *  Acquires the SWFW semaphore through the GSSR रेजिस्टर क्रम the specअगरied
 *  function (CSR, PHY0, PHY1, EEPROM, Flash)
 **/
s32 ixgbe_acquire_swfw_sync(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 gssr = 0;
	u32 swmask = mask;
	u32 fwmask = mask << 5;
	u32 समयout = 200;
	u32 i;

	क्रम (i = 0; i < समयout; i++) अणु
		/*
		 * SW NVM semaphore bit is used क्रम access to all
		 * SW_FW_SYNC bits (not just NVM)
		 */
		अगर (ixgbe_get_eeprom_semaphore(hw))
			वापस IXGBE_ERR_SWFW_SYNC;

		gssr = IXGBE_READ_REG(hw, IXGBE_GSSR);
		अगर (!(gssr & (fwmask | swmask))) अणु
			gssr |= swmask;
			IXGBE_WRITE_REG(hw, IXGBE_GSSR, gssr);
			ixgbe_release_eeprom_semaphore(hw);
			वापस 0;
		पूर्ण अन्यथा अणु
			/* Resource is currently in use by FW or SW */
			ixgbe_release_eeprom_semaphore(hw);
			usleep_range(5000, 10000);
		पूर्ण
	पूर्ण

	/* If समय expired clear the bits holding the lock and retry */
	अगर (gssr & (fwmask | swmask))
		ixgbe_release_swfw_sync(hw, gssr & (fwmask | swmask));

	usleep_range(5000, 10000);
	वापस IXGBE_ERR_SWFW_SYNC;
पूर्ण

/**
 *  ixgbe_release_swfw_sync - Release SWFW semaphore
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @mask: Mask to specअगरy which semaphore to release
 *
 *  Releases the SWFW semaphore through the GSSR रेजिस्टर क्रम the specअगरied
 *  function (CSR, PHY0, PHY1, EEPROM, Flash)
 **/
व्योम ixgbe_release_swfw_sync(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 gssr;
	u32 swmask = mask;

	ixgbe_get_eeprom_semaphore(hw);

	gssr = IXGBE_READ_REG(hw, IXGBE_GSSR);
	gssr &= ~swmask;
	IXGBE_WRITE_REG(hw, IXGBE_GSSR, gssr);

	ixgbe_release_eeprom_semaphore(hw);
पूर्ण

/**
 * prot_स्वतःc_पढ़ो_generic - Hides MAC dअगरferences needed क्रम AUTOC पढ़ो
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg_val: Value we पढ़ो from AUTOC
 * @locked: bool to indicate whether the SW/FW lock should be taken.  Never
 *	    true in this the generic हाल.
 *
 * The शेष हाल requires no protection so just to the रेजिस्टर पढ़ो.
 **/
s32 prot_स्वतःc_पढ़ो_generic(काष्ठा ixgbe_hw *hw, bool *locked, u32 *reg_val)
अणु
	*locked = false;
	*reg_val = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	वापस 0;
पूर्ण

/**
 * prot_स्वतःc_ग_लिखो_generic - Hides MAC dअगरferences needed क्रम AUTOC ग_लिखो
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg_val: value to ग_लिखो to AUTOC
 * @locked: bool to indicate whether the SW/FW lock was alपढ़ोy taken by
 *	    previous पढ़ो.
 **/
s32 prot_स्वतःc_ग_लिखो_generic(काष्ठा ixgbe_hw *hw, u32 reg_val, bool locked)
अणु
	IXGBE_WRITE_REG(hw, IXGBE_AUTOC, reg_val);
	वापस 0;
पूर्ण

/**
 *  ixgbe_disable_rx_buff_generic - Stops the receive data path
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Stops the receive data path and रुकोs क्रम the HW to पूर्णांकernally
 *  empty the Rx security block.
 **/
s32 ixgbe_disable_rx_buff_generic(काष्ठा ixgbe_hw *hw)
अणु
#घोषणा IXGBE_MAX_SECRX_POLL 40
	पूर्णांक i;
	पूर्णांक secrxreg;

	secrxreg = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	secrxreg |= IXGBE_SECRXCTRL_RX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, secrxreg);
	क्रम (i = 0; i < IXGBE_MAX_SECRX_POLL; i++) अणु
		secrxreg = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT);
		अगर (secrxreg & IXGBE_SECRXSTAT_SECRX_RDY)
			अवरोध;
		अन्यथा
			/* Use पूर्णांकerrupt-safe sleep just in हाल */
			udelay(1000);
	पूर्ण

	/* For inक्रमmational purposes only */
	अगर (i >= IXGBE_MAX_SECRX_POLL)
		hw_dbg(hw, "Rx unit being enabled before security path fully disabled. Continuing with init.\n");

	वापस 0;

पूर्ण

/**
 *  ixgbe_enable_rx_buff_generic - Enables the receive data path
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Enables the receive data path
 **/
s32 ixgbe_enable_rx_buff_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 secrxreg;

	secrxreg = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	secrxreg &= ~IXGBE_SECRXCTRL_RX_DIS;
	IXGBE_WRITE_REG(hw, IXGBE_SECRXCTRL, secrxreg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_enable_rx_dma_generic - Enable the Rx DMA unit
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @regval: रेजिस्टर value to ग_लिखो to RXCTRL
 *
 *  Enables the Rx DMA unit
 **/
s32 ixgbe_enable_rx_dma_generic(काष्ठा ixgbe_hw *hw, u32 regval)
अणु
	अगर (regval & IXGBE_RXCTRL_RXEN)
		hw->mac.ops.enable_rx(hw);
	अन्यथा
		hw->mac.ops.disable_rx(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_blink_led_start_generic - Blink LED based on index.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: led number to blink
 **/
s32 ixgbe_blink_led_start_generic(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	ixgbe_link_speed speed = 0;
	bool link_up = false;
	u32 स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	u32 led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	bool locked = false;
	s32 ret_val;

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	/*
	 * Link must be up to स्वतः-blink the LEDs;
	 * Force it अगर link is करोwn.
	 */
	hw->mac.ops.check_link(hw, &speed, &link_up, false);

	अगर (!link_up) अणु
		ret_val = hw->mac.ops.prot_स्वतःc_पढ़ो(hw, &locked, &स्वतःc_reg);
		अगर (ret_val)
			वापस ret_val;

		स्वतःc_reg |= IXGBE_AUTOC_AN_RESTART;
		स्वतःc_reg |= IXGBE_AUTOC_FLU;

		ret_val = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw, स्वतःc_reg, locked);
		अगर (ret_val)
			वापस ret_val;

		IXGBE_WRITE_FLUSH(hw);

		usleep_range(10000, 20000);
	पूर्ण

	led_reg &= ~IXGBE_LED_MODE_MASK(index);
	led_reg |= IXGBE_LED_BLINK(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, led_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_blink_led_stop_generic - Stop blinking LED based on index.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @index: led number to stop blinking
 **/
s32 ixgbe_blink_led_stop_generic(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 स्वतःc_reg = 0;
	u32 led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	bool locked = false;
	s32 ret_val;

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	ret_val = hw->mac.ops.prot_स्वतःc_पढ़ो(hw, &locked, &स्वतःc_reg);
	अगर (ret_val)
		वापस ret_val;

	स्वतःc_reg &= ~IXGBE_AUTOC_FLU;
	स्वतःc_reg |= IXGBE_AUTOC_AN_RESTART;

	ret_val = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw, स्वतःc_reg, locked);
	अगर (ret_val)
		वापस ret_val;

	led_reg &= ~IXGBE_LED_MODE_MASK(index);
	led_reg &= ~IXGBE_LED_BLINK(index);
	led_reg |= IXGBE_LED_LINK_ACTIVE << IXGBE_LED_MODE_SHIFT(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, led_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_san_mac_addr_offset - Get SAN MAC address offset from the EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @san_mac_offset: SAN MAC address offset
 *
 *  This function will पढ़ो the EEPROM location क्रम the SAN MAC address
 *  poपूर्णांकer, and वापसs the value at that location.  This is used in both
 *  get and set mac_addr routines.
 **/
अटल s32 ixgbe_get_san_mac_addr_offset(काष्ठा ixgbe_hw *hw,
					u16 *san_mac_offset)
अणु
	s32 ret_val;

	/*
	 * First पढ़ो the EEPROM poपूर्णांकer to see अगर the MAC addresses are
	 * available.
	 */
	ret_val = hw->eeprom.ops.पढ़ो(hw, IXGBE_SAN_MAC_ADDR_PTR,
				      san_mac_offset);
	अगर (ret_val)
		hw_err(hw, "eeprom read at offset %d failed\n",
		       IXGBE_SAN_MAC_ADDR_PTR);

	वापस ret_val;
पूर्ण

/**
 *  ixgbe_get_san_mac_addr_generic - SAN MAC address retrieval from the EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @san_mac_addr: SAN MAC address
 *
 *  Reads the SAN MAC address from the EEPROM, अगर it's available.  This is
 *  per-port, so set_lan_id() must be called beक्रमe पढ़ोing the addresses.
 *  set_lan_id() is called by identअगरy_sfp(), but this cannot be relied
 *  upon क्रम non-SFP connections, so we must call it here.
 **/
s32 ixgbe_get_san_mac_addr_generic(काष्ठा ixgbe_hw *hw, u8 *san_mac_addr)
अणु
	u16 san_mac_data, san_mac_offset;
	u8 i;
	s32 ret_val;

	/*
	 * First पढ़ो the EEPROM poपूर्णांकer to see अगर the MAC addresses are
	 * available.  If they're not, no poपूर्णांक in calling set_lan_id() here.
	 */
	ret_val = ixgbe_get_san_mac_addr_offset(hw, &san_mac_offset);
	अगर (ret_val || san_mac_offset == 0 || san_mac_offset == 0xFFFF)

		जाओ san_mac_addr_clr;

	/* make sure we know which port we need to program */
	hw->mac.ops.set_lan_id(hw);
	/* apply the port offset to the address offset */
	(hw->bus.func) ? (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT1_OFFSET) :
			 (san_mac_offset += IXGBE_SAN_MAC_ADDR_PORT0_OFFSET);
	क्रम (i = 0; i < 3; i++) अणु
		ret_val = hw->eeprom.ops.पढ़ो(hw, san_mac_offset,
					      &san_mac_data);
		अगर (ret_val) अणु
			hw_err(hw, "eeprom read at offset %d failed\n",
			       san_mac_offset);
			जाओ san_mac_addr_clr;
		पूर्ण
		san_mac_addr[i * 2] = (u8)(san_mac_data);
		san_mac_addr[i * 2 + 1] = (u8)(san_mac_data >> 8);
		san_mac_offset++;
	पूर्ण
	वापस 0;

san_mac_addr_clr:
	/* No addresses available in this EEPROM.  It's not necessarily an
	 * error though, so just wipe the local address and वापस.
	 */
	क्रम (i = 0; i < 6; i++)
		san_mac_addr[i] = 0xFF;
	वापस ret_val;
पूर्ण

/**
 *  ixgbe_get_pcie_msix_count_generic - Gets MSI-X vector count
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Read PCIe configuration space, and get the MSI-X vector count from
 *  the capabilities table.
 **/
u16 ixgbe_get_pcie_msix_count_generic(काष्ठा ixgbe_hw *hw)
अणु
	u16 msix_count;
	u16 max_msix_count;
	u16 pcie_offset;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		pcie_offset = IXGBE_PCIE_MSIX_82598_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTORS_82598;
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		pcie_offset = IXGBE_PCIE_MSIX_82599_CAPS;
		max_msix_count = IXGBE_MAX_MSIX_VECTORS_82599;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	msix_count = ixgbe_पढ़ो_pci_cfg_word(hw, pcie_offset);
	अगर (ixgbe_हटाओd(hw->hw_addr))
		msix_count = 0;
	msix_count &= IXGBE_PCIE_MSIX_TBL_SZ_MASK;

	/* MSI-X count is zero-based in HW */
	msix_count++;

	अगर (msix_count > max_msix_count)
		msix_count = max_msix_count;

	वापस msix_count;
पूर्ण

/**
 *  ixgbe_clear_vmdq_generic - Disassociate a VMDq pool index from a rx address
 *  @hw: poपूर्णांकer to hardware काष्ठा
 *  @rar: receive address रेजिस्टर index to disassociate
 *  @vmdq: VMDq pool index to हटाओ from the rar
 **/
s32 ixgbe_clear_vmdq_generic(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq)
अणु
	u32 mpsar_lo, mpsar_hi;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	अगर (rar >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", rar);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	mpsar_lo = IXGBE_READ_REG(hw, IXGBE_MPSAR_LO(rar));
	mpsar_hi = IXGBE_READ_REG(hw, IXGBE_MPSAR_HI(rar));

	अगर (ixgbe_हटाओd(hw->hw_addr))
		वापस 0;

	अगर (!mpsar_lo && !mpsar_hi)
		वापस 0;

	अगर (vmdq == IXGBE_CLEAR_VMDQ_ALL) अणु
		अगर (mpsar_lo) अणु
			IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), 0);
			mpsar_lo = 0;
		पूर्ण
		अगर (mpsar_hi) अणु
			IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), 0);
			mpsar_hi = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (vmdq < 32) अणु
		mpsar_lo &= ~BIT(vmdq);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), mpsar_lo);
	पूर्ण अन्यथा अणु
		mpsar_hi &= ~BIT(vmdq - 32);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), mpsar_hi);
	पूर्ण

	/* was that the last pool using this rar? */
	अगर (mpsar_lo == 0 && mpsar_hi == 0 &&
	    rar != 0 && rar != hw->mac.san_mac_rar_index)
		hw->mac.ops.clear_rar(hw, rar);

	वापस 0;
पूर्ण

/**
 *  ixgbe_set_vmdq_generic - Associate a VMDq pool index with a rx address
 *  @hw: poपूर्णांकer to hardware काष्ठा
 *  @rar: receive address रेजिस्टर index to associate with a VMDq index
 *  @vmdq: VMDq pool index
 **/
s32 ixgbe_set_vmdq_generic(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq)
अणु
	u32 mpsar;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	अगर (rar >= rar_entries) अणु
		hw_dbg(hw, "RAR index %d is out of range.\n", rar);
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	अगर (vmdq < 32) अणु
		mpsar = IXGBE_READ_REG(hw, IXGBE_MPSAR_LO(rar));
		mpsar |= BIT(vmdq);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), mpsar);
	पूर्ण अन्यथा अणु
		mpsar = IXGBE_READ_REG(hw, IXGBE_MPSAR_HI(rar));
		mpsar |= BIT(vmdq - 32);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), mpsar);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  ixgbe_set_vmdq_san_mac_generic - Associate VMDq pool index with a rx address
 *  @hw: poपूर्णांकer to hardware काष्ठा
 *  @vmdq: VMDq pool index
 *
 *  This function should only be involved in the IOV mode.
 *  In IOV mode, Default pool is next pool after the number of
 *  VFs advertized and not 0.
 *  MPSAR table needs to be updated क्रम SAN_MAC RAR [hw->mac.san_mac_rar_index]
 **/
s32 ixgbe_set_vmdq_san_mac_generic(काष्ठा ixgbe_hw *hw, u32 vmdq)
अणु
	u32 rar = hw->mac.san_mac_rar_index;

	अगर (vmdq < 32) अणु
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), BIT(vmdq));
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), 0);
	पूर्ण अन्यथा अणु
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), 0);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), BIT(vmdq - 32));
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_uta_tables_generic - Initialize the Unicast Table Array
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_init_uta_tables_generic(काष्ठा ixgbe_hw *hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 128; i++)
		IXGBE_WRITE_REG(hw, IXGBE_UTA(i), 0);

	वापस 0;
पूर्ण

/**
 *  ixgbe_find_vlvf_slot - find the vlanid or the first empty slot
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vlan: VLAN id to ग_लिखो to VLAN filter
 *  @vlvf_bypass: true to find vlanid only, false वापसs first empty slot अगर
 *		  vlanid not found
 *
 *  वापस the VLVF index where this VLAN id should be placed
 *
 **/
अटल s32 ixgbe_find_vlvf_slot(काष्ठा ixgbe_hw *hw, u32 vlan, bool vlvf_bypass)
अणु
	s32 regindex, first_empty_slot;
	u32 bits;

	/* लघु cut the special हाल */
	अगर (vlan == 0)
		वापस 0;

	/* अगर vlvf_bypass is set we करोn't want to use an empty slot, we
	 * will simply bypass the VLVF अगर there are no entries present in the
	 * VLVF that contain our VLAN
	 */
	first_empty_slot = vlvf_bypass ? IXGBE_ERR_NO_SPACE : 0;

	/* add VLAN enable bit क्रम comparison */
	vlan |= IXGBE_VLVF_VIEN;

	/* Search क्रम the vlan id in the VLVF entries. Save off the first empty
	 * slot found aदीर्घ the way.
	 *
	 * pre-decrement loop covering (IXGBE_VLVF_ENTRIES - 1) .. 1
	 */
	क्रम (regindex = IXGBE_VLVF_ENTRIES; --regindex;) अणु
		bits = IXGBE_READ_REG(hw, IXGBE_VLVF(regindex));
		अगर (bits == vlan)
			वापस regindex;
		अगर (!first_empty_slot && !bits)
			first_empty_slot = regindex;
	पूर्ण

	/* If we are here then we didn't find the VLAN.  Return first empty
	 * slot we found during our search, अन्यथा error.
	 */
	अगर (!first_empty_slot)
		hw_dbg(hw, "No space in VLVF.\n");

	वापस first_empty_slot ? : IXGBE_ERR_NO_SPACE;
पूर्ण

/**
 *  ixgbe_set_vfta_generic - Set VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @vlan: VLAN id to ग_लिखो to VLAN filter
 *  @vind: VMDq output index that maps queue to VLAN id in VFVFB
 *  @vlan_on: boolean flag to turn on/off VLAN in VFVF
 *  @vlvf_bypass: boolean flag indicating updating शेष pool is okay
 *
 *  Turn on/off specअगरied VLAN in the VLAN filter table.
 **/
s32 ixgbe_set_vfta_generic(काष्ठा ixgbe_hw *hw, u32 vlan, u32 vind,
			   bool vlan_on, bool vlvf_bypass)
अणु
	u32 regidx, vfta_delta, vfta, bits;
	s32 vlvf_index;

	अगर ((vlan > 4095) || (vind > 63))
		वापस IXGBE_ERR_PARAM;

	/*
	 * this is a 2 part operation - first the VFTA, then the
	 * VLVF and VLVFB अगर VT Mode is set
	 * We करोn't ग_लिखो the VFTA until we know the VLVF part succeeded.
	 */

	/* Part 1
	 * The VFTA is a bitstring made up of 128 32-bit रेजिस्टरs
	 * that enable the particular VLAN id, much like the MTA:
	 *    bits[11-5]: which रेजिस्टर
	 *    bits[4-0]:  which bit in the रेजिस्टर
	 */
	regidx = vlan / 32;
	vfta_delta = BIT(vlan % 32);
	vfta = IXGBE_READ_REG(hw, IXGBE_VFTA(regidx));

	/* vfta_delta represents the dअगरference between the current value
	 * of vfta and the value we want in the रेजिस्टर.  Since the dअगरf
	 * is an XOR mask we can just update vfta using an XOR.
	 */
	vfta_delta &= vlan_on ? ~vfta : vfta;
	vfta ^= vfta_delta;

	/* Part 2
	 * If VT Mode is set
	 *   Either vlan_on
	 *     make sure the vlan is in VLVF
	 *     set the vind bit in the matching VLVFB
	 *   Or !vlan_on
	 *     clear the pool bit and possibly the vind
	 */
	अगर (!(IXGBE_READ_REG(hw, IXGBE_VT_CTL) & IXGBE_VT_CTL_VT_ENABLE))
		जाओ vfta_update;

	vlvf_index = ixgbe_find_vlvf_slot(hw, vlan, vlvf_bypass);
	अगर (vlvf_index < 0) अणु
		अगर (vlvf_bypass)
			जाओ vfta_update;
		वापस vlvf_index;
	पूर्ण

	bits = IXGBE_READ_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32));

	/* set the pool bit */
	bits |= BIT(vind % 32);
	अगर (vlan_on)
		जाओ vlvf_update;

	/* clear the pool bit */
	bits ^= BIT(vind % 32);

	अगर (!bits &&
	    !IXGBE_READ_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + 1 - vind / 32))) अणु
		/* Clear VFTA first, then disable VLVF.  Otherwise
		 * we run the risk of stray packets leaking पूर्णांकo
		 * the PF via the शेष pool
		 */
		अगर (vfta_delta)
			IXGBE_WRITE_REG(hw, IXGBE_VFTA(regidx), vfta);

		/* disable VLVF and clear reमुख्यing bit from pool */
		IXGBE_WRITE_REG(hw, IXGBE_VLVF(vlvf_index), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32), 0);

		वापस 0;
	पूर्ण

	/* If there are still bits set in the VLVFB रेजिस्टरs
	 * क्रम the VLAN ID indicated we need to see अगर the
	 * caller is requesting that we clear the VFTA entry bit.
	 * If the caller has requested that we clear the VFTA
	 * entry bit but there are still pools/VFs using this VLAN
	 * ID entry then ignore the request.  We're not worried
	 * about the हाल where we're turning the VFTA VLAN ID
	 * entry bit on, only when requested to turn it off as
	 * there may be multiple pools and/or VFs using the
	 * VLAN ID entry.  In that हाल we cannot clear the
	 * VFTA bit until all pools/VFs using that VLAN ID have also
	 * been cleared.  This will be indicated by "bits" being
	 * zero.
	 */
	vfta_delta = 0;

vlvf_update:
	/* record pool change and enable VLAN ID अगर not alपढ़ोy enabled */
	IXGBE_WRITE_REG(hw, IXGBE_VLVFB(vlvf_index * 2 + vind / 32), bits);
	IXGBE_WRITE_REG(hw, IXGBE_VLVF(vlvf_index), IXGBE_VLVF_VIEN | vlan);

vfta_update:
	/* Update VFTA now that we are पढ़ोy क्रम traffic */
	अगर (vfta_delta)
		IXGBE_WRITE_REG(hw, IXGBE_VFTA(regidx), vfta);

	वापस 0;
पूर्ण

/**
 *  ixgbe_clear_vfta_generic - Clear VLAN filter table
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Clears the VLAN filer table, and the VMDq index associated with the filter
 **/
s32 ixgbe_clear_vfta_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 offset;

	क्रम (offset = 0; offset < hw->mac.vft_size; offset++)
		IXGBE_WRITE_REG(hw, IXGBE_VFTA(offset), 0);

	क्रम (offset = 0; offset < IXGBE_VLVF_ENTRIES; offset++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_VLVF(offset), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(offset * 2), 0);
		IXGBE_WRITE_REG(hw, IXGBE_VLVFB(offset * 2 + 1), 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_need_crosstalk_fix - Determine अगर we need to करो cross talk fix
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Contains the logic to identअगरy अगर we need to verअगरy link क्रम the
 *  crosstalk fix
 **/
अटल bool ixgbe_need_crosstalk_fix(काष्ठा ixgbe_hw *hw)
अणु
	/* Does FW say we need the fix */
	अगर (!hw->need_crosstalk_fix)
		वापस false;

	/* Only consider SFP+ PHYs i.e. media type fiber */
	चयन (hw->mac.ops.get_media_type(hw)) अणु
	हाल ixgbe_media_type_fiber:
	हाल ixgbe_media_type_fiber_qsfp:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 *  ixgbe_check_mac_link_generic - Determine link and speed status
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: poपूर्णांकer to link speed
 *  @link_up: true when link is up
 *  @link_up_रुको_to_complete: bool used to रुको क्रम link up or not
 *
 *  Reads the links रेजिस्टर to determine अगर link is up and the current speed
 **/
s32 ixgbe_check_mac_link_generic(काष्ठा ixgbe_hw *hw, ixgbe_link_speed *speed,
				 bool *link_up, bool link_up_रुको_to_complete)
अणु
	u32 links_reg, links_orig;
	u32 i;

	/* If Crosstalk fix enabled करो the sanity check of making sure
	 * the SFP+ cage is full.
	 */
	अगर (ixgbe_need_crosstalk_fix(hw)) अणु
		u32 sfp_cage_full;

		चयन (hw->mac.type) अणु
		हाल ixgbe_mac_82599EB:
			sfp_cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP2;
			अवरोध;
		हाल ixgbe_mac_X550EM_x:
		हाल ixgbe_mac_x550em_a:
			sfp_cage_full = IXGBE_READ_REG(hw, IXGBE_ESDP) &
					IXGBE_ESDP_SDP0;
			अवरोध;
		शेष:
			/* sanity check - No SFP+ devices here */
			sfp_cage_full = false;
			अवरोध;
		पूर्ण

		अगर (!sfp_cage_full) अणु
			*link_up = false;
			*speed = IXGBE_LINK_SPEED_UNKNOWN;
			वापस 0;
		पूर्ण
	पूर्ण

	/* clear the old state */
	links_orig = IXGBE_READ_REG(hw, IXGBE_LINKS);

	links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);

	अगर (links_orig != links_reg) अणु
		hw_dbg(hw, "LINKS changed from %08X to %08X\n",
		       links_orig, links_reg);
	पूर्ण

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

	चयन (links_reg & IXGBE_LINKS_SPEED_82599) अणु
	हाल IXGBE_LINKS_SPEED_10G_82599:
		अगर ((hw->mac.type >= ixgbe_mac_X550) &&
		    (links_reg & IXGBE_LINKS_SPEED_NON_STD))
			*speed = IXGBE_LINK_SPEED_2_5GB_FULL;
		अन्यथा
			*speed = IXGBE_LINK_SPEED_10GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_1G_82599:
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_100_82599:
		अगर ((hw->mac.type >= ixgbe_mac_X550) &&
		    (links_reg & IXGBE_LINKS_SPEED_NON_STD))
			*speed = IXGBE_LINK_SPEED_5GB_FULL;
		अन्यथा
			*speed = IXGBE_LINK_SPEED_100_FULL;
		अवरोध;
	हाल IXGBE_LINKS_SPEED_10_X550EM_A:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
		अगर (hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_1G_T_L) अणु
			*speed = IXGBE_LINK_SPEED_10_FULL;
		पूर्ण
		अवरोध;
	शेष:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_wwn_prefix_generic - Get alternative WWNN/WWPN prefix from
 *  the EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @wwnn_prefix: the alternative WWNN prefix
 *  @wwpn_prefix: the alternative WWPN prefix
 *
 *  This function will पढ़ो the EEPROM from the alternative SAN MAC address
 *  block to check the support क्रम the alternative WWNN/WWPN prefix support.
 **/
s32 ixgbe_get_wwn_prefix_generic(काष्ठा ixgbe_hw *hw, u16 *wwnn_prefix,
					u16 *wwpn_prefix)
अणु
	u16 offset, caps;
	u16 alt_san_mac_blk_offset;

	/* clear output first */
	*wwnn_prefix = 0xFFFF;
	*wwpn_prefix = 0xFFFF;

	/* check अगर alternative SAN MAC is supported */
	offset = IXGBE_ALT_SAN_MAC_ADDR_BLK_PTR;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, &alt_san_mac_blk_offset))
		जाओ wwn_prefix_err;

	अगर ((alt_san_mac_blk_offset == 0) ||
	    (alt_san_mac_blk_offset == 0xFFFF))
		वापस 0;

	/* check capability in alternative san mac address block */
	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_CAPS_OFFSET;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, &caps))
		जाओ wwn_prefix_err;
	अगर (!(caps & IXGBE_ALT_SAN_MAC_ADDR_CAPS_ALTWWN))
		वापस 0;

	/* get the corresponding prefix क्रम WWNN/WWPN */
	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_WWNN_OFFSET;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, wwnn_prefix))
		hw_err(hw, "eeprom read at offset %d failed\n", offset);

	offset = alt_san_mac_blk_offset + IXGBE_ALT_SAN_MAC_ADDR_WWPN_OFFSET;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, wwpn_prefix))
		जाओ wwn_prefix_err;

	वापस 0;

wwn_prefix_err:
	hw_err(hw, "eeprom read at offset %d failed\n", offset);
	वापस 0;
पूर्ण

/**
 *  ixgbe_set_mac_anti_spoofing - Enable/Disable MAC anti-spoofing
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @enable: enable or disable चयन क्रम MAC anti-spoofing
 *  @vf: Virtual Function pool - VF Pool to set क्रम MAC anti-spoofing
 *
 **/
व्योम ixgbe_set_mac_anti_spoofing(काष्ठा ixgbe_hw *hw, bool enable, पूर्णांक vf)
अणु
	पूर्णांक vf_target_reg = vf >> 3;
	पूर्णांक vf_target_shअगरt = vf % 8;
	u32 pfvfspoof;

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	pfvfspoof = IXGBE_READ_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg));
	अगर (enable)
		pfvfspoof |= BIT(vf_target_shअगरt);
	अन्यथा
		pfvfspoof &= ~BIT(vf_target_shअगरt);
	IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg), pfvfspoof);
पूर्ण

/**
 *  ixgbe_set_vlan_anti_spoofing - Enable/Disable VLAN anti-spoofing
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @enable: enable or disable चयन क्रम VLAN anti-spoofing
 *  @vf: Virtual Function pool - VF Pool to set क्रम VLAN anti-spoofing
 *
 **/
व्योम ixgbe_set_vlan_anti_spoofing(काष्ठा ixgbe_hw *hw, bool enable, पूर्णांक vf)
अणु
	पूर्णांक vf_target_reg = vf >> 3;
	पूर्णांक vf_target_shअगरt = vf % 8 + IXGBE_SPOOF_VLANAS_SHIFT;
	u32 pfvfspoof;

	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस;

	pfvfspoof = IXGBE_READ_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg));
	अगर (enable)
		pfvfspoof |= BIT(vf_target_shअगरt);
	अन्यथा
		pfvfspoof &= ~BIT(vf_target_shअगरt);
	IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg), pfvfspoof);
पूर्ण

/**
 *  ixgbe_get_device_caps_generic - Get additional device capabilities
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @device_caps: the EEPROM word with the extra device capabilities
 *
 *  This function will पढ़ो the EEPROM location क्रम the device capabilities,
 *  and वापस the word through device_caps.
 **/
s32 ixgbe_get_device_caps_generic(काष्ठा ixgbe_hw *hw, u16 *device_caps)
अणु
	hw->eeprom.ops.पढ़ो(hw, IXGBE_DEVICE_CAPS, device_caps);

	वापस 0;
पूर्ण

/**
 * ixgbe_set_rxpba_generic - Initialize RX packet buffer
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @num_pb: number of packet buffers to allocate
 * @headroom: reserve n KB of headroom
 * @strategy: packet buffer allocation strategy
 **/
व्योम ixgbe_set_rxpba_generic(काष्ठा ixgbe_hw *hw,
			     पूर्णांक num_pb,
			     u32 headroom,
			     पूर्णांक strategy)
अणु
	u32 pbsize = hw->mac.rx_pb_size;
	पूर्णांक i = 0;
	u32 rxpktsize, txpktsize, txpbthresh;

	/* Reserve headroom */
	pbsize -= headroom;

	अगर (!num_pb)
		num_pb = 1;

	/* Divide reमुख्यing packet buffer space amongst the number
	 * of packet buffers requested using supplied strategy.
	 */
	चयन (strategy) अणु
	हाल (PBA_STRATEGY_WEIGHTED):
		/* pba_80_48 strategy weight first half of packet buffer with
		 * 5/8 of the packet buffer space.
		 */
		rxpktsize = ((pbsize * 5 * 2) / (num_pb * 8));
		pbsize -= rxpktsize * (num_pb / 2);
		rxpktsize <<= IXGBE_RXPBSIZE_SHIFT;
		क्रम (; i < (num_pb / 2); i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		fallthrough; /* configure reमुख्यing packet buffers */
	हाल (PBA_STRATEGY_EQUAL):
		/* Divide the reमुख्यing Rx packet buffer evenly among the TCs */
		rxpktsize = (pbsize / (num_pb - i)) << IXGBE_RXPBSIZE_SHIFT;
		क्रम (; i < num_pb; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Setup Tx packet buffer and threshold equally क्रम all TCs
	 * TXPBTHRESH रेजिस्टर is set in K so भागide by 1024 and subtract
	 * 10 since the largest packet we support is just over 9K.
	 */
	txpktsize = IXGBE_TXPBSIZE_MAX / num_pb;
	txpbthresh = (txpktsize / 1024) - IXGBE_TXPKT_SIZE_MAX;
	क्रम (i = 0; i < num_pb; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), txpktsize);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBTHRESH(i), txpbthresh);
	पूर्ण

	/* Clear unused TCs, अगर any, to zero buffer size*/
	क्रम (; i < IXGBE_MAX_PB; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBTHRESH(i), 0);
	पूर्ण
पूर्ण

/**
 *  ixgbe_calculate_checksum - Calculate checksum क्रम buffer
 *  @buffer: poपूर्णांकer to EEPROM
 *  @length: size of EEPROM to calculate a checksum क्रम
 *
 *  Calculates the checksum क्रम some buffer on a specअगरied length.  The
 *  checksum calculated is वापसed.
 **/
u8 ixgbe_calculate_checksum(u8 *buffer, u32 length)
अणु
	u32 i;
	u8 sum = 0;

	अगर (!buffer)
		वापस 0;

	क्रम (i = 0; i < length; i++)
		sum += buffer[i];

	वापस (u8) (0 - sum);
पूर्ण

/**
 *  ixgbe_hic_unlocked - Issue command to manageability block unlocked
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @buffer: command to ग_लिखो and where the वापस status will be placed
 *  @length: length of buffer, must be multiple of 4 bytes
 *  @समयout: समय in ms to रुको क्रम command completion
 *
 *  Communicates with the manageability block. On success वापस 0
 *  अन्यथा वापसs semaphore error when encountering an error acquiring
 *  semaphore or IXGBE_ERR_HOST_INTERFACE_COMMAND when command fails.
 *
 *  This function assumes that the IXGBE_GSSR_SW_MNG_SM semaphore is held
 *  by the caller.
 **/
s32 ixgbe_hic_unlocked(काष्ठा ixgbe_hw *hw, u32 *buffer, u32 length,
		       u32 समयout)
अणु
	u32 hicr, i, fwsts;
	u16 dword_len;

	अगर (!length || length > IXGBE_HI_MAX_BLOCK_BYTE_LENGTH) अणु
		hw_dbg(hw, "Buffer length failure buffersize-%d.\n", length);
		वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण

	/* Set bit 9 of FWSTS clearing FW reset indication */
	fwsts = IXGBE_READ_REG(hw, IXGBE_FWSTS);
	IXGBE_WRITE_REG(hw, IXGBE_FWSTS, fwsts | IXGBE_FWSTS_FWRI);

	/* Check that the host पूर्णांकerface is enabled. */
	hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
	अगर (!(hicr & IXGBE_HICR_EN)) अणु
		hw_dbg(hw, "IXGBE_HOST_EN bit disabled.\n");
		वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण

	/* Calculate length in DWORDs. We must be DWORD aligned */
	अगर (length % माप(u32)) अणु
		hw_dbg(hw, "Buffer length failure, not aligned to dword");
		वापस IXGBE_ERR_INVALID_ARGUMENT;
	पूर्ण

	dword_len = length >> 2;

	/* The device driver ग_लिखोs the relevant command block
	 * पूर्णांकo the ram area.
	 */
	क्रम (i = 0; i < dword_len; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_FLEX_MNG,
				      i, (__क्रमce u32)cpu_to_le32(buffer[i]));

	/* Setting this bit tells the ARC that a new command is pending. */
	IXGBE_WRITE_REG(hw, IXGBE_HICR, hicr | IXGBE_HICR_C);

	क्रम (i = 0; i < समयout; i++) अणु
		hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
		अगर (!(hicr & IXGBE_HICR_C))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	/* Check command successful completion. */
	अगर ((समयout && i == समयout) ||
	    !(IXGBE_READ_REG(hw, IXGBE_HICR) & IXGBE_HICR_SV))
		वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;

	वापस 0;
पूर्ण

/**
 *  ixgbe_host_पूर्णांकerface_command - Issue command to manageability block
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @buffer: contains the command to ग_लिखो and where the वापस status will
 *           be placed
 *  @length: length of buffer, must be multiple of 4 bytes
 *  @समयout: समय in ms to रुको क्रम command completion
 *  @वापस_data: पढ़ो and वापस data from the buffer (true) or not (false)
 *  Needed because FW काष्ठाures are big endian and decoding of
 *  these fields can be 8 bit or 16 bit based on command. Decoding
 *  is not easily understood without making a table of commands.
 *  So we will leave this up to the caller to पढ़ो back the data
 *  in these हालs.
 *
 *  Communicates with the manageability block.  On success वापस 0
 *  अन्यथा वापस IXGBE_ERR_HOST_INTERFACE_COMMAND.
 **/
s32 ixgbe_host_पूर्णांकerface_command(काष्ठा ixgbe_hw *hw, व्योम *buffer,
				 u32 length, u32 समयout,
				 bool वापस_data)
अणु
	u32 hdr_size = माप(काष्ठा ixgbe_hic_hdr);
	जोड़ अणु
		काष्ठा ixgbe_hic_hdr hdr;
		u32 u32arr[1];
	पूर्ण *bp = buffer;
	u16 buf_len, dword_len;
	s32 status;
	u32 bi;

	अगर (!length || length > IXGBE_HI_MAX_BLOCK_BYTE_LENGTH) अणु
		hw_dbg(hw, "Buffer length failure buffersize-%d.\n", length);
		वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण
	/* Take management host पूर्णांकerface semaphore */
	status = hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM);
	अगर (status)
		वापस status;

	status = ixgbe_hic_unlocked(hw, buffer, length, समयout);
	अगर (status)
		जाओ rel_out;

	अगर (!वापस_data)
		जाओ rel_out;

	/* Calculate length in DWORDs */
	dword_len = hdr_size >> 2;

	/* first pull in the header so we know the buffer length */
	क्रम (bi = 0; bi < dword_len; bi++) अणु
		bp->u32arr[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&bp->u32arr[bi]);
	पूर्ण

	/* If there is any thing in data position pull it in */
	buf_len = bp->hdr.buf_len;
	अगर (!buf_len)
		जाओ rel_out;

	अगर (length < round_up(buf_len, 4) + hdr_size) अणु
		hw_dbg(hw, "Buffer not large enough for reply message.\n");
		status = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		जाओ rel_out;
	पूर्ण

	/* Calculate length in DWORDs, add 3 क्रम odd lengths */
	dword_len = (buf_len + 3) >> 2;

	/* Pull in the rest of the buffer (bi is where we left off) */
	क्रम (; bi <= dword_len; bi++) अणु
		bp->u32arr[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&bp->u32arr[bi]);
	पूर्ण

rel_out:
	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM);

	वापस status;
पूर्ण

/**
 *  ixgbe_set_fw_drv_ver_generic - Sends driver version to firmware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @maj: driver version major number
 *  @min: driver version minor number
 *  @build: driver version build number
 *  @sub: driver version sub build number
 *  @len: length of driver_ver string
 *  @driver_ver: driver string
 *
 *  Sends driver version number to firmware through the manageability
 *  block.  On success वापस 0
 *  अन्यथा वापसs IXGBE_ERR_SWFW_SYNC when encountering an error acquiring
 *  semaphore or IXGBE_ERR_HOST_INTERFACE_COMMAND when command fails.
 **/
s32 ixgbe_set_fw_drv_ver_generic(काष्ठा ixgbe_hw *hw, u8 maj, u8 min,
				 u8 build, u8 sub, __always_unused u16 len,
				 __always_unused स्थिर अक्षर *driver_ver)
अणु
	काष्ठा ixgbe_hic_drv_info fw_cmd;
	पूर्णांक i;
	s32 ret_val;

	fw_cmd.hdr.cmd = FW_CEM_CMD_DRIVER_INFO;
	fw_cmd.hdr.buf_len = FW_CEM_CMD_DRIVER_INFO_LEN;
	fw_cmd.hdr.cmd_or_resp.cmd_resv = FW_CEM_CMD_RESERVED;
	fw_cmd.port_num = hw->bus.func;
	fw_cmd.ver_maj = maj;
	fw_cmd.ver_min = min;
	fw_cmd.ver_build = build;
	fw_cmd.ver_sub = sub;
	fw_cmd.hdr.checksum = 0;
	fw_cmd.pad = 0;
	fw_cmd.pad2 = 0;
	fw_cmd.hdr.checksum = ixgbe_calculate_checksum((u8 *)&fw_cmd,
				(FW_CEM_HDR_LEN + fw_cmd.hdr.buf_len));

	क्रम (i = 0; i <= FW_CEM_MAX_RETRIES; i++) अणु
		ret_val = ixgbe_host_पूर्णांकerface_command(hw, &fw_cmd,
						       माप(fw_cmd),
						       IXGBE_HI_COMMAND_TIMEOUT,
						       true);
		अगर (ret_val != 0)
			जारी;

		अगर (fw_cmd.hdr.cmd_or_resp.ret_status ==
		    FW_CEM_RESP_STATUS_SUCCESS)
			ret_val = 0;
		अन्यथा
			ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;

		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * ixgbe_clear_tx_pending - Clear pending TX work from the PCIe fअगरo
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * The 82599 and x540 MACs can experience issues अगर TX work is still pending
 * when a reset occurs.  This function prevents this by flushing the PCIe
 * buffers on the प्रणाली.
 **/
व्योम ixgbe_clear_tx_pending(काष्ठा ixgbe_hw *hw)
अणु
	u32 gcr_ext, hlreg0, i, poll;
	u16 value;

	/*
	 * If द्विगुन reset is not requested then all transactions should
	 * alपढ़ोy be clear and as such there is no work to करो
	 */
	अगर (!(hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED))
		वापस;

	/*
	 * Set loopback enable to prevent any transmits from being sent
	 * should the link come up.  This assumes that the RXCTRL.RXEN bit
	 * has alपढ़ोy been cleared.
	 */
	hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0 | IXGBE_HLREG0_LPBK);

	/* रुको क्रम a last completion beक्रमe clearing buffers */
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(3000, 6000);

	/* Beक्रमe proceeding, make sure that the PCIe block करोes not have
	 * transactions pending.
	 */
	poll = ixgbe_pcie_समयout_poll(hw);
	क्रम (i = 0; i < poll; i++) अणु
		usleep_range(100, 200);
		value = ixgbe_पढ़ो_pci_cfg_word(hw, IXGBE_PCI_DEVICE_STATUS);
		अगर (ixgbe_हटाओd(hw->hw_addr))
			अवरोध;
		अगर (!(value & IXGBE_PCI_DEVICE_STATUS_TRANSACTION_PENDING))
			अवरोध;
	पूर्ण

	/* initiate cleaning flow क्रम buffers in the PCIe transaction layer */
	gcr_ext = IXGBE_READ_REG(hw, IXGBE_GCR_EXT);
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT,
			gcr_ext | IXGBE_GCR_EXT_BUFFERS_CLEAR);

	/* Flush all ग_लिखोs and allow 20usec क्रम all transactions to clear */
	IXGBE_WRITE_FLUSH(hw);
	udelay(20);

	/* restore previous रेजिस्टर values */
	IXGBE_WRITE_REG(hw, IXGBE_GCR_EXT, gcr_ext);
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
पूर्ण

अटल स्थिर u8 ixgbe_emc_temp_data[4] = अणु
	IXGBE_EMC_INTERNAL_DATA,
	IXGBE_EMC_DIODE1_DATA,
	IXGBE_EMC_DIODE2_DATA,
	IXGBE_EMC_DIODE3_DATA
पूर्ण;
अटल स्थिर u8 ixgbe_emc_therm_limit[4] = अणु
	IXGBE_EMC_INTERNAL_THERM_LIMIT,
	IXGBE_EMC_DIODE1_THERM_LIMIT,
	IXGBE_EMC_DIODE2_THERM_LIMIT,
	IXGBE_EMC_DIODE3_THERM_LIMIT
पूर्ण;

/**
 *  ixgbe_get_ets_data - Extracts the ETS bit data
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @ets_cfg: extected ETS data
 *  @ets_offset: offset of ETS data
 *
 *  Returns error code.
 **/
अटल s32 ixgbe_get_ets_data(काष्ठा ixgbe_hw *hw, u16 *ets_cfg,
			      u16 *ets_offset)
अणु
	s32 status;

	status = hw->eeprom.ops.पढ़ो(hw, IXGBE_ETS_CFG, ets_offset);
	अगर (status)
		वापस status;

	अगर ((*ets_offset == 0x0000) || (*ets_offset == 0xFFFF))
		वापस IXGBE_NOT_IMPLEMENTED;

	status = hw->eeprom.ops.पढ़ो(hw, *ets_offset, ets_cfg);
	अगर (status)
		वापस status;

	अगर ((*ets_cfg & IXGBE_ETS_TYPE_MASK) != IXGBE_ETS_TYPE_EMC_SHIFTED)
		वापस IXGBE_NOT_IMPLEMENTED;

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_thermal_sensor_data_generic - Gathers thermal sensor data
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns the thermal sensor data काष्ठाure
 **/
s32 ixgbe_get_thermal_sensor_data_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  num_sensors;
	u8  i;
	काष्ठा ixgbe_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	/* Only support thermal sensors attached to physical port 0 */
	अगर ((IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_LAN_ID_1))
		वापस IXGBE_NOT_IMPLEMENTED;

	status = ixgbe_get_ets_data(hw, &ets_cfg, &ets_offset);
	अगर (status)
		वापस status;

	num_sensors = (ets_cfg & IXGBE_ETS_NUM_SENSORS_MASK);
	अगर (num_sensors > IXGBE_MAX_SENSORS)
		num_sensors = IXGBE_MAX_SENSORS;

	क्रम (i = 0; i < num_sensors; i++) अणु
		u8  sensor_index;
		u8  sensor_location;

		status = hw->eeprom.ops.पढ़ो(hw, (ets_offset + 1 + i),
					     &ets_sensor);
		अगर (status)
			वापस status;

		sensor_index = ((ets_sensor & IXGBE_ETS_DATA_INDEX_MASK) >>
				IXGBE_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & IXGBE_ETS_DATA_LOC_MASK) >>
				   IXGBE_ETS_DATA_LOC_SHIFT);

		अगर (sensor_location != 0) अणु
			status = hw->phy.ops.पढ़ो_i2c_byte(hw,
					ixgbe_emc_temp_data[sensor_index],
					IXGBE_I2C_THERMAL_SENSOR_ADDR,
					&data->sensor[i].temp);
			अगर (status)
				वापस status;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_init_thermal_sensor_thresh_generic - Inits thermal sensor thresholds
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Inits the thermal sensor thresholds according to the NVM map
 * and save off the threshold and location values पूर्णांकo mac.thermal_sensor_data
 **/
s32 ixgbe_init_thermal_sensor_thresh_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  low_thresh_delta;
	u8  num_sensors;
	u8  therm_limit;
	u8  i;
	काष्ठा ixgbe_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	स_रखो(data, 0, माप(काष्ठा ixgbe_thermal_sensor_data));

	/* Only support thermal sensors attached to physical port 0 */
	अगर ((IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_LAN_ID_1))
		वापस IXGBE_NOT_IMPLEMENTED;

	status = ixgbe_get_ets_data(hw, &ets_cfg, &ets_offset);
	अगर (status)
		वापस status;

	low_thresh_delta = ((ets_cfg & IXGBE_ETS_LTHRES_DELTA_MASK) >>
			     IXGBE_ETS_LTHRES_DELTA_SHIFT);
	num_sensors = (ets_cfg & IXGBE_ETS_NUM_SENSORS_MASK);
	अगर (num_sensors > IXGBE_MAX_SENSORS)
		num_sensors = IXGBE_MAX_SENSORS;

	क्रम (i = 0; i < num_sensors; i++) अणु
		u8  sensor_index;
		u8  sensor_location;

		अगर (hw->eeprom.ops.पढ़ो(hw, ets_offset + 1 + i, &ets_sensor)) अणु
			hw_err(hw, "eeprom read at offset %d failed\n",
			       ets_offset + 1 + i);
			जारी;
		पूर्ण
		sensor_index = ((ets_sensor & IXGBE_ETS_DATA_INDEX_MASK) >>
				IXGBE_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & IXGBE_ETS_DATA_LOC_MASK) >>
				   IXGBE_ETS_DATA_LOC_SHIFT);
		therm_limit = ets_sensor & IXGBE_ETS_DATA_HTHRESH_MASK;

		hw->phy.ops.ग_लिखो_i2c_byte(hw,
			ixgbe_emc_therm_limit[sensor_index],
			IXGBE_I2C_THERMAL_SENSOR_ADDR, therm_limit);

		अगर (sensor_location == 0)
			जारी;

		data->sensor[i].location = sensor_location;
		data->sensor[i].caution_thresh = therm_limit;
		data->sensor[i].max_op_thresh = therm_limit - low_thresh_delta;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_orom_version - Return option ROM from EEPROM
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @nvm_ver: poपूर्णांकer to output काष्ठाure
 *
 *  अगर valid option ROM version, nvm_ver->or_valid set to true
 *  अन्यथा nvm_ver->or_valid is false.
 **/
व्योम ixgbe_get_orom_version(काष्ठा ixgbe_hw *hw,
			    काष्ठा ixgbe_nvm_version *nvm_ver)
अणु
	u16 offset, eeprom_cfg_blkh, eeprom_cfg_blkl;

	nvm_ver->or_valid = false;
	/* Option Rom may or may not be present.  Start with poपूर्णांकer */
	hw->eeprom.ops.पढ़ो(hw, NVM_OROM_OFFSET, &offset);

	/* make sure offset is valid */
	अगर (offset == 0x0 || offset == NVM_INVALID_PTR)
		वापस;

	hw->eeprom.ops.पढ़ो(hw, offset + NVM_OROM_BLK_HI, &eeprom_cfg_blkh);
	hw->eeprom.ops.पढ़ो(hw, offset + NVM_OROM_BLK_LOW, &eeprom_cfg_blkl);

	/* option rom exists and is valid */
	अगर ((eeprom_cfg_blkl | eeprom_cfg_blkh) == 0x0 ||
	    eeprom_cfg_blkl == NVM_VER_INVALID ||
	    eeprom_cfg_blkh == NVM_VER_INVALID)
		वापस;

	nvm_ver->or_valid = true;
	nvm_ver->or_major = eeprom_cfg_blkl >> NVM_OROM_SHIFT;
	nvm_ver->or_build = (eeprom_cfg_blkl << NVM_OROM_SHIFT) |
			    (eeprom_cfg_blkh >> NVM_OROM_SHIFT);
	nvm_ver->or_patch = eeprom_cfg_blkh & NVM_OROM_PATCH_MASK;
पूर्ण

/**
 *  ixgbe_get_oem_prod_version - Etrack ID from EEPROM
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @nvm_ver: poपूर्णांकer to output काष्ठाure
 *
 *  अगर valid OEM product version, nvm_ver->oem_valid set to true
 *  अन्यथा nvm_ver->oem_valid is false.
 **/
व्योम ixgbe_get_oem_prod_version(काष्ठा ixgbe_hw *hw,
				काष्ठा ixgbe_nvm_version *nvm_ver)
अणु
	u16 rel_num, prod_ver, mod_len, cap, offset;

	nvm_ver->oem_valid = false;
	hw->eeprom.ops.पढ़ो(hw, NVM_OEM_PROD_VER_PTR, &offset);

	/* Return is offset to OEM Product Version block is invalid */
	अगर (offset == 0x0 || offset == NVM_INVALID_PTR)
		वापस;

	/* Read product version block */
	hw->eeprom.ops.पढ़ो(hw, offset, &mod_len);
	hw->eeprom.ops.पढ़ो(hw, offset + NVM_OEM_PROD_VER_CAP_OFF, &cap);

	/* Return अगर OEM product version block is invalid */
	अगर (mod_len != NVM_OEM_PROD_VER_MOD_LEN ||
	    (cap & NVM_OEM_PROD_VER_CAP_MASK) != 0x0)
		वापस;

	hw->eeprom.ops.पढ़ो(hw, offset + NVM_OEM_PROD_VER_OFF_L, &prod_ver);
	hw->eeprom.ops.पढ़ो(hw, offset + NVM_OEM_PROD_VER_OFF_H, &rel_num);

	/* Return अगर version is invalid */
	अगर ((rel_num | prod_ver) == 0x0 ||
	    rel_num == NVM_VER_INVALID || prod_ver == NVM_VER_INVALID)
		वापस;

	nvm_ver->oem_major = prod_ver >> NVM_VER_SHIFT;
	nvm_ver->oem_minor = prod_ver & NVM_VER_MASK;
	nvm_ver->oem_release = rel_num;
	nvm_ver->oem_valid = true;
पूर्ण

/**
 *  ixgbe_get_etk_id - Return Etrack ID from EEPROM
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @nvm_ver: poपूर्णांकer to output काष्ठाure
 *
 *  word पढ़ो errors will वापस 0xFFFF
 **/
व्योम ixgbe_get_etk_id(काष्ठा ixgbe_hw *hw,
		      काष्ठा ixgbe_nvm_version *nvm_ver)
अणु
	u16 etk_id_l, etk_id_h;

	अगर (hw->eeprom.ops.पढ़ो(hw, NVM_ETK_OFF_LOW, &etk_id_l))
		etk_id_l = NVM_VER_INVALID;
	अगर (hw->eeprom.ops.पढ़ो(hw, NVM_ETK_OFF_HI, &etk_id_h))
		etk_id_h = NVM_VER_INVALID;

	/* The word order क्रम the version क्रमmat is determined by high order
	 * word bit 15.
	 */
	अगर ((etk_id_h & NVM_ETK_VALID) == 0) अणु
		nvm_ver->etk_id = etk_id_h;
		nvm_ver->etk_id |= (etk_id_l << NVM_ETK_SHIFT);
	पूर्ण अन्यथा अणु
		nvm_ver->etk_id = etk_id_l;
		nvm_ver->etk_id |= (etk_id_h << NVM_ETK_SHIFT);
	पूर्ण
पूर्ण

व्योम ixgbe_disable_rx_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 rxctrl;

	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	अगर (rxctrl & IXGBE_RXCTRL_RXEN) अणु
		अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
			u32 pfdtxgswc;

			pfdtxgswc = IXGBE_READ_REG(hw, IXGBE_PFDTXGSWC);
			अगर (pfdtxgswc & IXGBE_PFDTXGSWC_VT_LBEN) अणु
				pfdtxgswc &= ~IXGBE_PFDTXGSWC_VT_LBEN;
				IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
				hw->mac.set_lben = true;
			पूर्ण अन्यथा अणु
				hw->mac.set_lben = false;
			पूर्ण
		पूर्ण
		rxctrl &= ~IXGBE_RXCTRL_RXEN;
		IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, rxctrl);
	पूर्ण
पूर्ण

व्योम ixgbe_enable_rx_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 rxctrl;

	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, (rxctrl | IXGBE_RXCTRL_RXEN));

	अगर (hw->mac.type != ixgbe_mac_82598EB) अणु
		अगर (hw->mac.set_lben) अणु
			u32 pfdtxgswc;

			pfdtxgswc = IXGBE_READ_REG(hw, IXGBE_PFDTXGSWC);
			pfdtxgswc |= IXGBE_PFDTXGSWC_VT_LBEN;
			IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
			hw->mac.set_lben = false;
		पूर्ण
	पूर्ण
पूर्ण

/** ixgbe_mng_present - वापसs true when management capability is present
 * @hw: poपूर्णांकer to hardware काष्ठाure
 **/
bool ixgbe_mng_present(काष्ठा ixgbe_hw *hw)
अणु
	u32 fwsm;

	अगर (hw->mac.type < ixgbe_mac_82599EB)
		वापस false;

	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));

	वापस !!(fwsm & IXGBE_FWSM_FW_MODE_PT);
पूर्ण

/**
 *  ixgbe_setup_mac_link_multispeed_fiber - Set MAC link speed
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Set the link speed in the MAC and/or PHY रेजिस्टर and restarts link.
 */
s32 ixgbe_setup_mac_link_multispeed_fiber(काष्ठा ixgbe_hw *hw,
					  ixgbe_link_speed speed,
					  bool स्वतःneg_रुको_to_complete)
अणु
	ixgbe_link_speed link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	ixgbe_link_speed highest_link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	s32 status = 0;
	u32 speedcnt = 0;
	u32 i = 0;
	bool स्वतःneg, link_up = false;

	/* Mask off requested but non-supported speeds */
	status = hw->mac.ops.get_link_capabilities(hw, &link_speed, &स्वतःneg);
	अगर (status)
		वापस status;

	speed &= link_speed;

	/* Try each speed one by one, highest priority first.  We करो this in
	 * software because 10Gb fiber करोesn't support speed स्वतःnegotiation.
	 */
	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL) अणु
		speedcnt++;
		highest_link_speed = IXGBE_LINK_SPEED_10GB_FULL;

		/* Set the module link speed */
		चयन (hw->phy.media_type) अणु
		हाल ixgbe_media_type_fiber:
			hw->mac.ops.set_rate_select_speed(hw,
						    IXGBE_LINK_SPEED_10GB_FULL);
			अवरोध;
		हाल ixgbe_media_type_fiber_qsfp:
			/* QSFP module स्वतःmatically detects MAC link speed */
			अवरोध;
		शेष:
			hw_dbg(hw, "Unexpected media type\n");
			अवरोध;
		पूर्ण

		/* Allow module to change analog अक्षरacteristics (1G->10G) */
		msleep(40);

		status = hw->mac.ops.setup_mac_link(hw,
						    IXGBE_LINK_SPEED_10GB_FULL,
						    स्वतःneg_रुको_to_complete);
		अगर (status)
			वापस status;

		/* Flap the Tx laser अगर it has not alपढ़ोy been करोne */
		अगर (hw->mac.ops.flap_tx_laser)
			hw->mac.ops.flap_tx_laser(hw);

		/* Wait क्रम the controller to acquire link.  Per IEEE 802.3ap,
		 * Section 73.10.2, we may have to रुको up to 500ms अगर KR is
		 * attempted.  82599 uses the same timing क्रम 10g SFI.
		 */
		क्रम (i = 0; i < 5; i++) अणु
			/* Wait क्रम the link partner to also set speed */
			msleep(100);

			/* If we have link, just jump out */
			status = hw->mac.ops.check_link(hw, &link_speed,
							&link_up, false);
			अगर (status)
				वापस status;

			अगर (link_up)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL) अणु
		speedcnt++;
		अगर (highest_link_speed == IXGBE_LINK_SPEED_UNKNOWN)
			highest_link_speed = IXGBE_LINK_SPEED_1GB_FULL;

		/* Set the module link speed */
		चयन (hw->phy.media_type) अणु
		हाल ixgbe_media_type_fiber:
			hw->mac.ops.set_rate_select_speed(hw,
						     IXGBE_LINK_SPEED_1GB_FULL);
			अवरोध;
		हाल ixgbe_media_type_fiber_qsfp:
			/* QSFP module स्वतःmatically detects link speed */
			अवरोध;
		शेष:
			hw_dbg(hw, "Unexpected media type\n");
			अवरोध;
		पूर्ण

		/* Allow module to change analog अक्षरacteristics (10G->1G) */
		msleep(40);

		status = hw->mac.ops.setup_mac_link(hw,
						    IXGBE_LINK_SPEED_1GB_FULL,
						    स्वतःneg_रुको_to_complete);
		अगर (status)
			वापस status;

		/* Flap the Tx laser अगर it has not alपढ़ोy been करोne */
		अगर (hw->mac.ops.flap_tx_laser)
			hw->mac.ops.flap_tx_laser(hw);

		/* Wait क्रम the link partner to also set speed */
		msleep(100);

		/* If we have link, just jump out */
		status = hw->mac.ops.check_link(hw, &link_speed, &link_up,
						false);
		अगर (status)
			वापस status;

		अगर (link_up)
			जाओ out;
	पूर्ण

	/* We didn't get link.  Configure back to the highest speed we tried,
	 * (अगर there was more than one).  We call ourselves back with just the
	 * single highest speed that the user requested.
	 */
	अगर (speedcnt > 1)
		status = ixgbe_setup_mac_link_multispeed_fiber(hw,
						      highest_link_speed,
						      स्वतःneg_रुको_to_complete);

out:
	/* Set स्वतःneg_advertised value based on input link speed */
	hw->phy.स्वतःneg_advertised = 0;

	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	वापस status;
पूर्ण

/**
 *  ixgbe_set_soft_rate_select_speed - Set module link speed
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: link speed to set
 *
 *  Set module link speed via the soft rate select.
 */
व्योम ixgbe_set_soft_rate_select_speed(काष्ठा ixgbe_hw *hw,
				      ixgbe_link_speed speed)
अणु
	s32 status;
	u8 rs, eeprom_data;

	चयन (speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		/* one bit mask same as setting on */
		rs = IXGBE_SFF_SOFT_RS_SELECT_10G;
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		rs = IXGBE_SFF_SOFT_RS_SELECT_1G;
		अवरोध;
	शेष:
		hw_dbg(hw, "Invalid fixed module speed\n");
		वापस;
	पूर्ण

	/* Set RS0 */
	status = hw->phy.ops.पढ़ो_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					   IXGBE_I2C_EEPROM_DEV_ADDR2,
					   &eeprom_data);
	अगर (status) अणु
		hw_dbg(hw, "Failed to read Rx Rate Select RS0\n");
		वापस;
	पूर्ण

	eeprom_data = (eeprom_data & ~IXGBE_SFF_SOFT_RS_SELECT_MASK) | rs;

	status = hw->phy.ops.ग_लिखो_i2c_byte(hw, IXGBE_SFF_SFF_8472_OSCB,
					    IXGBE_I2C_EEPROM_DEV_ADDR2,
					    eeprom_data);
	अगर (status) अणु
		hw_dbg(hw, "Failed to write Rx Rate Select RS0\n");
		वापस;
	पूर्ण

	/* Set RS1 */
	status = hw->phy.ops.पढ़ो_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					   IXGBE_I2C_EEPROM_DEV_ADDR2,
					   &eeprom_data);
	अगर (status) अणु
		hw_dbg(hw, "Failed to read Rx Rate Select RS1\n");
		वापस;
	पूर्ण

	eeprom_data = (eeprom_data & ~IXGBE_SFF_SOFT_RS_SELECT_MASK) | rs;

	status = hw->phy.ops.ग_लिखो_i2c_byte(hw, IXGBE_SFF_SFF_8472_ESCB,
					    IXGBE_I2C_EEPROM_DEV_ADDR2,
					    eeprom_data);
	अगर (status) अणु
		hw_dbg(hw, "Failed to write Rx Rate Select RS1\n");
		वापस;
	पूर्ण
पूर्ण

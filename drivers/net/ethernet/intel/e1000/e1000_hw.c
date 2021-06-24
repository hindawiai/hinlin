<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/* e1000_hw.c
 * Shared functions क्रम accessing and configuring the MAC
 */

#समावेश "e1000.h"

अटल s32 e1000_check_करोwnshअगरt(काष्ठा e1000_hw *hw);
अटल s32 e1000_check_polarity(काष्ठा e1000_hw *hw,
				e1000_rev_polarity *polarity);
अटल व्योम e1000_clear_hw_cntrs(काष्ठा e1000_hw *hw);
अटल व्योम e1000_clear_vfta(काष्ठा e1000_hw *hw);
अटल s32 e1000_config_dsp_after_link_change(काष्ठा e1000_hw *hw,
					      bool link_up);
अटल s32 e1000_config_fc_after_link_up(काष्ठा e1000_hw *hw);
अटल s32 e1000_detect_gig_phy(काष्ठा e1000_hw *hw);
अटल s32 e1000_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw);
अटल s32 e1000_get_cable_length(काष्ठा e1000_hw *hw, u16 *min_length,
				  u16 *max_length);
अटल s32 e1000_get_phy_cfg_करोne(काष्ठा e1000_hw *hw);
अटल s32 e1000_id_led_init(काष्ठा e1000_hw *hw);
अटल व्योम e1000_init_rx_addrs(काष्ठा e1000_hw *hw);
अटल s32 e1000_phy_igp_get_info(काष्ठा e1000_hw *hw,
				  काष्ठा e1000_phy_info *phy_info);
अटल s32 e1000_phy_m88_get_info(काष्ठा e1000_hw *hw,
				  काष्ठा e1000_phy_info *phy_info);
अटल s32 e1000_set_d3_lplu_state(काष्ठा e1000_hw *hw, bool active);
अटल s32 e1000_रुको_स्वतःneg(काष्ठा e1000_hw *hw);
अटल व्योम e1000_ग_लिखो_reg_io(काष्ठा e1000_hw *hw, u32 offset, u32 value);
अटल s32 e1000_set_phy_type(काष्ठा e1000_hw *hw);
अटल व्योम e1000_phy_init_script(काष्ठा e1000_hw *hw);
अटल s32 e1000_setup_copper_link(काष्ठा e1000_hw *hw);
अटल s32 e1000_setup_fiber_serdes_link(काष्ठा e1000_hw *hw);
अटल s32 e1000_adjust_serdes_amplitude(काष्ठा e1000_hw *hw);
अटल s32 e1000_phy_क्रमce_speed_duplex(काष्ठा e1000_hw *hw);
अटल s32 e1000_config_mac_to_phy(काष्ठा e1000_hw *hw);
अटल व्योम e1000_उठाओ_mdi_clk(काष्ठा e1000_hw *hw, u32 *ctrl);
अटल व्योम e1000_lower_mdi_clk(काष्ठा e1000_hw *hw, u32 *ctrl);
अटल व्योम e1000_shअगरt_out_mdi_bits(काष्ठा e1000_hw *hw, u32 data, u16 count);
अटल u16 e1000_shअगरt_in_mdi_bits(काष्ठा e1000_hw *hw);
अटल s32 e1000_phy_reset_dsp(काष्ठा e1000_hw *hw);
अटल s32 e1000_ग_लिखो_eeprom_spi(काष्ठा e1000_hw *hw, u16 offset,
				  u16 words, u16 *data);
अटल s32 e1000_ग_लिखो_eeprom_microwire(काष्ठा e1000_hw *hw, u16 offset,
					u16 words, u16 *data);
अटल s32 e1000_spi_eeprom_पढ़ोy(काष्ठा e1000_hw *hw);
अटल व्योम e1000_उठाओ_ee_clk(काष्ठा e1000_hw *hw, u32 *eecd);
अटल व्योम e1000_lower_ee_clk(काष्ठा e1000_hw *hw, u32 *eecd);
अटल व्योम e1000_shअगरt_out_ee_bits(काष्ठा e1000_hw *hw, u16 data, u16 count);
अटल s32 e1000_ग_लिखो_phy_reg_ex(काष्ठा e1000_hw *hw, u32 reg_addr,
				  u16 phy_data);
अटल s32 e1000_पढ़ो_phy_reg_ex(काष्ठा e1000_hw *hw, u32 reg_addr,
				 u16 *phy_data);
अटल u16 e1000_shअगरt_in_ee_bits(काष्ठा e1000_hw *hw, u16 count);
अटल s32 e1000_acquire_eeprom(काष्ठा e1000_hw *hw);
अटल व्योम e1000_release_eeprom(काष्ठा e1000_hw *hw);
अटल व्योम e1000_standby_eeprom(काष्ठा e1000_hw *hw);
अटल s32 e1000_set_vco_speed(काष्ठा e1000_hw *hw);
अटल s32 e1000_polarity_reversal_workaround(काष्ठा e1000_hw *hw);
अटल s32 e1000_set_phy_mode(काष्ठा e1000_hw *hw);
अटल s32 e1000_करो_पढ़ो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				u16 *data);
अटल s32 e1000_करो_ग_लिखो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				 u16 *data);

/* IGP cable length table */
अटल स्थिर
u16 e1000_igp_cable_length_table[IGP01E1000_AGC_LENGTH_TABLE_SIZE] = अणु
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 10, 10, 10, 10, 10, 10, 10, 20, 20, 20, 20, 20, 25, 25, 25,
	25, 25, 25, 25, 30, 30, 30, 30, 40, 40, 40, 40, 40, 40, 40, 40,
	40, 50, 50, 50, 50, 50, 50, 50, 60, 60, 60, 60, 60, 60, 60, 60,
	60, 70, 70, 70, 70, 70, 70, 80, 80, 80, 80, 80, 80, 90, 90, 90,
	90, 90, 90, 90, 90, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100,
	    100,
	100, 100, 100, 100, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
	    110, 110,
	110, 110, 110, 110, 110, 110, 120, 120, 120, 120, 120, 120, 120, 120,
	    120, 120
पूर्ण;

अटल DEFINE_MUTEX(e1000_eeprom_lock);
अटल DEFINE_SPINLOCK(e1000_phy_lock);

/**
 * e1000_set_phy_type - Set the phy type member in the hw काष्ठा.
 * @hw: Struct containing variables accessed by shared code
 */
अटल s32 e1000_set_phy_type(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->mac_type == e1000_undefined)
		वापस -E1000_ERR_PHY_TYPE;

	चयन (hw->phy_id) अणु
	हाल M88E1000_E_PHY_ID:
	हाल M88E1000_I_PHY_ID:
	हाल M88E1011_I_PHY_ID:
	हाल M88E1111_I_PHY_ID:
	हाल M88E1118_E_PHY_ID:
		hw->phy_type = e1000_phy_m88;
		अवरोध;
	हाल IGP01E1000_I_PHY_ID:
		अगर (hw->mac_type == e1000_82541 ||
		    hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547 ||
		    hw->mac_type == e1000_82547_rev_2)
			hw->phy_type = e1000_phy_igp;
		अवरोध;
	हाल RTL8211B_PHY_ID:
		hw->phy_type = e1000_phy_8211;
		अवरोध;
	हाल RTL8201N_PHY_ID:
		hw->phy_type = e1000_phy_8201;
		अवरोध;
	शेष:
		/* Should never have loaded on this device */
		hw->phy_type = e1000_phy_undefined;
		वापस -E1000_ERR_PHY_TYPE;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_init_script - IGP phy init script - initializes the GbE PHY
 * @hw: Struct containing variables accessed by shared code
 */
अटल व्योम e1000_phy_init_script(काष्ठा e1000_hw *hw)
अणु
	u16 phy_saved_data;

	अगर (hw->phy_init_script) अणु
		msleep(20);

		/* Save off the current value of रेजिस्टर 0x2F5B to be restored
		 * at the end of this routine.
		 */
		e1000_पढ़ो_phy_reg(hw, 0x2F5B, &phy_saved_data);

		/* Disabled the PHY transmitter */
		e1000_ग_लिखो_phy_reg(hw, 0x2F5B, 0x0003);
		msleep(20);

		e1000_ग_लिखो_phy_reg(hw, 0x0000, 0x0140);
		msleep(5);

		चयन (hw->mac_type) अणु
		हाल e1000_82541:
		हाल e1000_82547:
			e1000_ग_लिखो_phy_reg(hw, 0x1F95, 0x0001);
			e1000_ग_लिखो_phy_reg(hw, 0x1F71, 0xBD21);
			e1000_ग_लिखो_phy_reg(hw, 0x1F79, 0x0018);
			e1000_ग_लिखो_phy_reg(hw, 0x1F30, 0x1600);
			e1000_ग_लिखो_phy_reg(hw, 0x1F31, 0x0014);
			e1000_ग_लिखो_phy_reg(hw, 0x1F32, 0x161C);
			e1000_ग_लिखो_phy_reg(hw, 0x1F94, 0x0003);
			e1000_ग_लिखो_phy_reg(hw, 0x1F96, 0x003F);
			e1000_ग_लिखो_phy_reg(hw, 0x2010, 0x0008);
			अवरोध;

		हाल e1000_82541_rev_2:
		हाल e1000_82547_rev_2:
			e1000_ग_लिखो_phy_reg(hw, 0x1F73, 0x0099);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		e1000_ग_लिखो_phy_reg(hw, 0x0000, 0x3300);
		msleep(20);

		/* Now enable the transmitter */
		e1000_ग_लिखो_phy_reg(hw, 0x2F5B, phy_saved_data);

		अगर (hw->mac_type == e1000_82547) अणु
			u16 fused, fine, coarse;

			/* Move to analog रेजिस्टरs page */
			e1000_पढ़ो_phy_reg(hw,
					   IGP01E1000_ANALOG_SPARE_FUSE_STATUS,
					   &fused);

			अगर (!(fused & IGP01E1000_ANALOG_SPARE_FUSE_ENABLED)) अणु
				e1000_पढ़ो_phy_reg(hw,
						   IGP01E1000_ANALOG_FUSE_STATUS,
						   &fused);

				fine = fused & IGP01E1000_ANALOG_FUSE_FINE_MASK;
				coarse =
				    fused & IGP01E1000_ANALOG_FUSE_COARSE_MASK;

				अगर (coarse >
				    IGP01E1000_ANALOG_FUSE_COARSE_THRESH) अणु
					coarse -=
					    IGP01E1000_ANALOG_FUSE_COARSE_10;
					fine -= IGP01E1000_ANALOG_FUSE_FINE_1;
				पूर्ण अन्यथा अगर (coarse ==
					   IGP01E1000_ANALOG_FUSE_COARSE_THRESH)
					fine -= IGP01E1000_ANALOG_FUSE_FINE_10;

				fused =
				    (fused & IGP01E1000_ANALOG_FUSE_POLY_MASK) |
				    (fine & IGP01E1000_ANALOG_FUSE_FINE_MASK) |
				    (coarse &
				     IGP01E1000_ANALOG_FUSE_COARSE_MASK);

				e1000_ग_लिखो_phy_reg(hw,
						    IGP01E1000_ANALOG_FUSE_CONTROL,
						    fused);
				e1000_ग_लिखो_phy_reg(hw,
						    IGP01E1000_ANALOG_FUSE_BYPASS,
						    IGP01E1000_ANALOG_FUSE_ENABLE_SW_CONTROL);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * e1000_set_mac_type - Set the mac type member in the hw काष्ठा.
 * @hw: Struct containing variables accessed by shared code
 */
s32 e1000_set_mac_type(काष्ठा e1000_hw *hw)
अणु
	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82542:
		चयन (hw->revision_id) अणु
		हाल E1000_82542_2_0_REV_ID:
			hw->mac_type = e1000_82542_rev2_0;
			अवरोध;
		हाल E1000_82542_2_1_REV_ID:
			hw->mac_type = e1000_82542_rev2_1;
			अवरोध;
		शेष:
			/* Invalid 82542 revision ID */
			वापस -E1000_ERR_MAC_TYPE;
		पूर्ण
		अवरोध;
	हाल E1000_DEV_ID_82543GC_FIBER:
	हाल E1000_DEV_ID_82543GC_COPPER:
		hw->mac_type = e1000_82543;
		अवरोध;
	हाल E1000_DEV_ID_82544EI_COPPER:
	हाल E1000_DEV_ID_82544EI_FIBER:
	हाल E1000_DEV_ID_82544GC_COPPER:
	हाल E1000_DEV_ID_82544GC_LOM:
		hw->mac_type = e1000_82544;
		अवरोध;
	हाल E1000_DEV_ID_82540EM:
	हाल E1000_DEV_ID_82540EM_LOM:
	हाल E1000_DEV_ID_82540EP:
	हाल E1000_DEV_ID_82540EP_LOM:
	हाल E1000_DEV_ID_82540EP_LP:
		hw->mac_type = e1000_82540;
		अवरोध;
	हाल E1000_DEV_ID_82545EM_COPPER:
	हाल E1000_DEV_ID_82545EM_FIBER:
		hw->mac_type = e1000_82545;
		अवरोध;
	हाल E1000_DEV_ID_82545GM_COPPER:
	हाल E1000_DEV_ID_82545GM_FIBER:
	हाल E1000_DEV_ID_82545GM_SERDES:
		hw->mac_type = e1000_82545_rev_3;
		अवरोध;
	हाल E1000_DEV_ID_82546EB_COPPER:
	हाल E1000_DEV_ID_82546EB_FIBER:
	हाल E1000_DEV_ID_82546EB_QUAD_COPPER:
		hw->mac_type = e1000_82546;
		अवरोध;
	हाल E1000_DEV_ID_82546GB_COPPER:
	हाल E1000_DEV_ID_82546GB_FIBER:
	हाल E1000_DEV_ID_82546GB_SERDES:
	हाल E1000_DEV_ID_82546GB_PCIE:
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER:
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		hw->mac_type = e1000_82546_rev_3;
		अवरोध;
	हाल E1000_DEV_ID_82541EI:
	हाल E1000_DEV_ID_82541EI_MOBILE:
	हाल E1000_DEV_ID_82541ER_LOM:
		hw->mac_type = e1000_82541;
		अवरोध;
	हाल E1000_DEV_ID_82541ER:
	हाल E1000_DEV_ID_82541GI:
	हाल E1000_DEV_ID_82541GI_LF:
	हाल E1000_DEV_ID_82541GI_MOBILE:
		hw->mac_type = e1000_82541_rev_2;
		अवरोध;
	हाल E1000_DEV_ID_82547EI:
	हाल E1000_DEV_ID_82547EI_MOBILE:
		hw->mac_type = e1000_82547;
		अवरोध;
	हाल E1000_DEV_ID_82547GI:
		hw->mac_type = e1000_82547_rev_2;
		अवरोध;
	हाल E1000_DEV_ID_INTEL_CE4100_GBE:
		hw->mac_type = e1000_ce4100;
		अवरोध;
	शेष:
		/* Should never have loaded on this device */
		वापस -E1000_ERR_MAC_TYPE;
	पूर्ण

	चयन (hw->mac_type) अणु
	हाल e1000_82541:
	हाल e1000_82547:
	हाल e1000_82541_rev_2:
	हाल e1000_82547_rev_2:
		hw->asf_firmware_present = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* The 82543 chip करोes not count tx_carrier_errors properly in
	 * FD mode
	 */
	अगर (hw->mac_type == e1000_82543)
		hw->bad_tx_carr_stats_fd = true;

	अगर (hw->mac_type > e1000_82544)
		hw->has_smbus = true;

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_set_media_type - Set media type and TBI compatibility.
 * @hw: Struct containing variables accessed by shared code
 */
व्योम e1000_set_media_type(काष्ठा e1000_hw *hw)
अणु
	u32 status;

	अगर (hw->mac_type != e1000_82543) अणु
		/* tbi_compatibility is only valid on 82543 */
		hw->tbi_compatibility_en = false;
	पूर्ण

	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82545GM_SERDES:
	हाल E1000_DEV_ID_82546GB_SERDES:
		hw->media_type = e1000_media_type_पूर्णांकernal_serdes;
		अवरोध;
	शेष:
		चयन (hw->mac_type) अणु
		हाल e1000_82542_rev2_0:
		हाल e1000_82542_rev2_1:
			hw->media_type = e1000_media_type_fiber;
			अवरोध;
		हाल e1000_ce4100:
			hw->media_type = e1000_media_type_copper;
			अवरोध;
		शेष:
			status = er32(STATUS);
			अगर (status & E1000_STATUS_TBIMODE) अणु
				hw->media_type = e1000_media_type_fiber;
				/* tbi_compatibility not valid on fiber */
				hw->tbi_compatibility_en = false;
			पूर्ण अन्यथा अणु
				hw->media_type = e1000_media_type_copper;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * e1000_reset_hw - reset the hardware completely
 * @hw: Struct containing variables accessed by shared code
 *
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 */
s32 e1000_reset_hw(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	u32 ctrl_ext;
	u32 manc;
	u32 led_ctrl;
	s32 ret_val;

	/* For 82542 (rev 2.0), disable MWI beक्रमe issuing a device reset */
	अगर (hw->mac_type == e1000_82542_rev2_0) अणु
		e_dbg("Disabling MWI on 82542 rev 2.0\n");
		e1000_pci_clear_mwi(hw);
	पूर्ण

	/* Clear पूर्णांकerrupt mask to stop board from generating पूर्णांकerrupts */
	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete beक्रमe we hit the MAC with
	 * the global reset.
	 */
	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH();

	/* The tbi_compatibility_on Flag must be cleared when Rctl is cleared. */
	hw->tbi_compatibility_on = false;

	/* Delay to allow any outstanding PCI transactions to complete beक्रमe
	 * resetting the device
	 */
	msleep(10);

	ctrl = er32(CTRL);

	/* Must reset the PHY beक्रमe resetting the MAC */
	अगर ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) अणु
		ew32(CTRL, (ctrl | E1000_CTRL_PHY_RST));
		E1000_WRITE_FLUSH();
		msleep(5);
	पूर्ण

	/* Issue a global reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA, and link units.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	e_dbg("Issuing a global reset to MAC\n");

	चयन (hw->mac_type) अणु
	हाल e1000_82544:
	हाल e1000_82540:
	हाल e1000_82545:
	हाल e1000_82546:
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
		/* These controllers can't ack the 64-bit ग_लिखो when issuing the
		 * reset, so use IO-mapping as a workaround to issue the reset
		 */
		E1000_WRITE_REG_IO(hw, CTRL, (ctrl | E1000_CTRL_RST));
		अवरोध;
	हाल e1000_82545_rev_3:
	हाल e1000_82546_rev_3:
		/* Reset is perक्रमmed on a shaकरोw of the control रेजिस्टर */
		ew32(CTRL_DUP, (ctrl | E1000_CTRL_RST));
		अवरोध;
	हाल e1000_ce4100:
	शेष:
		ew32(CTRL, (ctrl | E1000_CTRL_RST));
		अवरोध;
	पूर्ण

	/* After MAC reset, क्रमce reload of EEPROM to restore घातer-on settings
	 * to device.  Later controllers reload the EEPROM स्वतःmatically, so
	 * just रुको क्रम reload to complete.
	 */
	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
	हाल e1000_82544:
		/* Wait क्रम reset to complete */
		udelay(10);
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_EE_RST;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
		/* Wait क्रम EEPROM reload */
		msleep(2);
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
	हाल e1000_82547:
	हाल e1000_82547_rev_2:
		/* Wait क्रम EEPROM reload */
		msleep(20);
		अवरोध;
	शेष:
		/* Auto पढ़ो करोne will delay 5ms or poll based on mac type */
		ret_val = e1000_get_स्वतः_rd_करोne(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	पूर्ण

	/* Disable HW ARPs on ASF enabled adapters */
	अगर (hw->mac_type >= e1000_82540) अणु
		manc = er32(MANC);
		manc &= ~(E1000_MANC_ARP_EN);
		ew32(MANC, manc);
	पूर्ण

	अगर ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) अणु
		e1000_phy_init_script(hw);

		/* Configure activity LED after PHY reset */
		led_ctrl = er32(LEDCTL);
		led_ctrl &= IGP_ACTIVITY_LED_MASK;
		led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		ew32(LEDCTL, led_ctrl);
	पूर्ण

	/* Clear पूर्णांकerrupt mask to stop board from generating पूर्णांकerrupts */
	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Clear any pending पूर्णांकerrupt events. */
	er32(ICR);

	/* If MWI was previously enabled, reenable it. */
	अगर (hw->mac_type == e1000_82542_rev2_0) अणु
		अगर (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
			e1000_pci_set_mwi(hw);
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_init_hw - Perक्रमms basic configuration of the adapter.
 * @hw: Struct containing variables accessed by shared code
 *
 * Assumes that the controller has previously been reset and is in a
 * post-reset uninitialized state. Initializes the receive address रेजिस्टरs,
 * multicast table, and VLAN filter table. Calls routines to setup link
 * configuration and flow control settings. Clears all on-chip counters. Leaves
 * the transmit and receive units disabled and uninitialized.
 */
s32 e1000_init_hw(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	u32 i;
	s32 ret_val;
	u32 mta_size;
	u32 ctrl_ext;

	/* Initialize Identअगरication LED */
	ret_val = e1000_id_led_init(hw);
	अगर (ret_val) अणु
		e_dbg("Error Initializing Identification LED\n");
		वापस ret_val;
	पूर्ण

	/* Set the media type and TBI compatibility */
	e1000_set_media_type(hw);

	/* Disabling VLAN filtering. */
	e_dbg("Initializing the IEEE VLAN\n");
	अगर (hw->mac_type < e1000_82545_rev_3)
		ew32(VET, 0);
	e1000_clear_vfta(hw);

	/* For 82542 (rev 2.0), disable MWI and put the receiver पूर्णांकo reset */
	अगर (hw->mac_type == e1000_82542_rev2_0) अणु
		e_dbg("Disabling MWI on 82542 rev 2.0\n");
		e1000_pci_clear_mwi(hw);
		ew32(RCTL, E1000_RCTL_RST);
		E1000_WRITE_FLUSH();
		msleep(5);
	पूर्ण

	/* Setup the receive address. This involves initializing all of the
	 * Receive Address Registers (RARs 0 - 15).
	 */
	e1000_init_rx_addrs(hw);

	/* For 82542 (rev 2.0), take the receiver out of reset and enable MWI */
	अगर (hw->mac_type == e1000_82542_rev2_0) अणु
		ew32(RCTL, 0);
		E1000_WRITE_FLUSH();
		msleep(1);
		अगर (hw->pci_cmd_word & PCI_COMMAND_INVALIDATE)
			e1000_pci_set_mwi(hw);
	पूर्ण

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	mta_size = E1000_MC_TBL_SIZE;
	क्रम (i = 0; i < mta_size; i++) अणु
		E1000_WRITE_REG_ARRAY(hw, MTA, i, 0);
		/* use ग_लिखो flush to prevent Memory Write Block (MWB) from
		 * occurring when accessing our रेजिस्टर space
		 */
		E1000_WRITE_FLUSH();
	पूर्ण

	/* Set the PCI priority bit correctly in the CTRL रेजिस्टर.  This
	 * determines अगर the adapter gives priority to receives, or अगर it
	 * gives equal priority to transmits and receives.  Valid only on
	 * 82542 and 82543 silicon.
	 */
	अगर (hw->dma_fairness && hw->mac_type <= e1000_82543) अणु
		ctrl = er32(CTRL);
		ew32(CTRL, ctrl | E1000_CTRL_PRIOR);
	पूर्ण

	चयन (hw->mac_type) अणु
	हाल e1000_82545_rev_3:
	हाल e1000_82546_rev_3:
		अवरोध;
	शेष:
		/* Workaround क्रम PCI-X problem when BIOS sets MMRBC
		 * incorrectly.
		 */
		अगर (hw->bus_type == e1000_bus_type_pcix &&
		    e1000_pcix_get_mmrbc(hw) > 2048)
			e1000_pcix_set_mmrbc(hw, 2048);
		अवरोध;
	पूर्ण

	/* Call a subroutine to configure the link and setup flow control. */
	ret_val = e1000_setup_link(hw);

	/* Set the transmit descriptor ग_लिखो-back policy */
	अगर (hw->mac_type > e1000_82544) अणु
		ctrl = er32(TXDCTL);
		ctrl =
		    (ctrl & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB;
		ew32(TXDCTL, ctrl);
	पूर्ण

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	e1000_clear_hw_cntrs(hw);

	अगर (hw->device_id == E1000_DEV_ID_82546GB_QUAD_COPPER ||
	    hw->device_id == E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3) अणु
		ctrl_ext = er32(CTRL_EXT);
		/* Relaxed ordering must be disabled to aव्योम a parity
		 * error crash in a PCI slot.
		 */
		ctrl_ext |= E1000_CTRL_EXT_RO_DIS;
		ew32(CTRL_EXT, ctrl_ext);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * e1000_adjust_serdes_amplitude - Adjust SERDES output amplitude based on EEPROM setting.
 * @hw: Struct containing variables accessed by shared code.
 */
अटल s32 e1000_adjust_serdes_amplitude(काष्ठा e1000_hw *hw)
अणु
	u16 eeprom_data;
	s32 ret_val;

	अगर (hw->media_type != e1000_media_type_पूर्णांकernal_serdes)
		वापस E1000_SUCCESS;

	चयन (hw->mac_type) अणु
	हाल e1000_82545_rev_3:
	हाल e1000_82546_rev_3:
		अवरोध;
	शेष:
		वापस E1000_SUCCESS;
	पूर्ण

	ret_val = e1000_पढ़ो_eeprom(hw, EEPROM_SERDES_AMPLITUDE, 1,
				    &eeprom_data);
	अगर (ret_val)
		वापस ret_val;

	अगर (eeprom_data != EEPROM_RESERVED_WORD) अणु
		/* Adjust SERDES output amplitude only. */
		eeprom_data &= EEPROM_SERDES_AMPLITUDE_MASK;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_EXT_CTRL, eeprom_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_setup_link - Configures flow control and link settings.
 * @hw: Struct containing variables accessed by shared code
 *
 * Determines which flow control settings to use. Calls the appropriate media-
 * specअगरic link configuration function. Configures the flow control settings.
 * Assuming the adapter has a valid link partner, a valid link should be
 * established. Assumes the hardware has previously been reset and the
 * transmitter and receiver are not enabled.
 */
s32 e1000_setup_link(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl_ext;
	s32 ret_val;
	u16 eeprom_data;

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's शेष PAUSE (flow control) mode,
	 * a bit that determines whether the HW शेषs to enabling or
	 * disabling स्वतः-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	अगर (hw->fc == E1000_FC_DEFAULT) अणु
		ret_val = e1000_पढ़ो_eeprom(hw, EEPROM_INIT_CONTROL2_REG,
					    1, &eeprom_data);
		अगर (ret_val) अणु
			e_dbg("EEPROM Read Error\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
		अगर ((eeprom_data & EEPROM_WORD0F_PAUSE_MASK) == 0)
			hw->fc = E1000_FC_NONE;
		अन्यथा अगर ((eeprom_data & EEPROM_WORD0F_PAUSE_MASK) ==
			 EEPROM_WORD0F_ASM_सूची)
			hw->fc = E1000_FC_TX_PAUSE;
		अन्यथा
			hw->fc = E1000_FC_FULL;
	पूर्ण

	/* We want to save off the original Flow Control configuration just
	 * in हाल we get disconnected and then reconnected पूर्णांकo a dअगरferent
	 * hub or चयन with dअगरferent Flow Control capabilities.
	 */
	अगर (hw->mac_type == e1000_82542_rev2_0)
		hw->fc &= (~E1000_FC_TX_PAUSE);

	अगर ((hw->mac_type < e1000_82543) && (hw->report_tx_early == 1))
		hw->fc &= (~E1000_FC_RX_PAUSE);

	hw->original_fc = hw->fc;

	e_dbg("After fix-ups FlowControl is now = %x\n", hw->fc);

	/* Take the 4 bits from EEPROM word 0x0F that determine the initial
	 * polarity value क्रम the SW controlled pins, and setup the
	 * Extended Device Control reg with that info.
	 * This is needed because one of the SW controlled pins is used क्रम
	 * संकेत detection.  So this should be करोne beक्रमe e1000_setup_pcs_link()
	 * or e1000_phy_setup() is called.
	 */
	अगर (hw->mac_type == e1000_82543) अणु
		ret_val = e1000_पढ़ो_eeprom(hw, EEPROM_INIT_CONTROL2_REG,
					    1, &eeprom_data);
		अगर (ret_val) अणु
			e_dbg("EEPROM Read Error\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
		ctrl_ext = ((eeprom_data & EEPROM_WORD0F_SWPDIO_EXT) <<
			    SWDPIO__EXT_SHIFT);
		ew32(CTRL_EXT, ctrl_ext);
	पूर्ण

	/* Call the necessary subroutine to configure the link. */
	ret_val = (hw->media_type == e1000_media_type_copper) ?
	    e1000_setup_copper_link(hw) : e1000_setup_fiber_serdes_link(hw);

	/* Initialize the flow control address, type, and PAUSE समयr
	 * रेजिस्टरs to their शेष values.  This is करोne even अगर flow
	 * control is disabled, because it करोes not hurt anything to
	 * initialize these रेजिस्टरs.
	 */
	e_dbg("Initializing the Flow Control address, type and timer regs\n");

	ew32(FCT, FLOW_CONTROL_TYPE);
	ew32(FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	ew32(FCAL, FLOW_CONTROL_ADDRESS_LOW);

	ew32(FCTTV, hw->fc_छोड़ो_समय);

	/* Set the flow control receive threshold रेजिस्टरs.  Normally,
	 * these रेजिस्टरs will be set to a शेष threshold that may be
	 * adjusted later by the driver's runसमय code.  However, अगर the
	 * ability to transmit छोड़ो frames in not enabled, then these
	 * रेजिस्टरs will be set to 0.
	 */
	अगर (!(hw->fc & E1000_FC_TX_PAUSE)) अणु
		ew32(FCRTL, 0);
		ew32(FCRTH, 0);
	पूर्ण अन्यथा अणु
		/* We need to set up the Receive Threshold high and low water
		 * marks as well as (optionally) enabling the transmission of
		 * XON frames.
		 */
		अगर (hw->fc_send_xon) अणु
			ew32(FCRTL, (hw->fc_low_water | E1000_FCRTL_XONE));
			ew32(FCRTH, hw->fc_high_water);
		पूर्ण अन्यथा अणु
			ew32(FCRTL, hw->fc_low_water);
			ew32(FCRTH, hw->fc_high_water);
		पूर्ण
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 * e1000_setup_fiber_serdes_link - prepare fiber or serdes link
 * @hw: Struct containing variables accessed by shared code
 *
 * Manipulates Physical Coding Sublayer functions in order to configure
 * link. Assumes the hardware has been previously reset and the transmitter
 * and receiver are not enabled.
 */
अटल s32 e1000_setup_fiber_serdes_link(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	u32 status;
	u32 txcw = 0;
	u32 i;
	u32 संकेत = 0;
	s32 ret_val;

	/* On adapters with a MAC newer than 82544, SWDP 1 will be
	 * set when the optics detect a संकेत. On older adapters, it will be
	 * cleared when there is a संकेत.  This applies to fiber media only.
	 * If we're on serdes media, adjust the output amplitude to value
	 * set in the EEPROM.
	 */
	ctrl = er32(CTRL);
	अगर (hw->media_type == e1000_media_type_fiber)
		संकेत = (hw->mac_type > e1000_82544) ? E1000_CTRL_SWDPIN1 : 0;

	ret_val = e1000_adjust_serdes_amplitude(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Take the link out of reset */
	ctrl &= ~(E1000_CTRL_LRST);

	/* Adjust VCO speed to improve BER perक्रमmance */
	ret_val = e1000_set_vco_speed(hw);
	अगर (ret_val)
		वापस ret_val;

	e1000_config_collision_dist(hw);

	/* Check क्रम a software override of the flow control settings, and setup
	 * the device accordingly.  If स्वतः-negotiation is enabled, then
	 * software will have to set the "PAUSE" bits to the correct value in
	 * the Tranmsit Config Word Register (TXCW) and re-start
	 * स्वतः-negotiation.  However, अगर स्वतः-negotiation is disabled, then
	 * software will have to manually configure the two flow control enable
	 * bits in the CTRL रेजिस्टर.
	 *
	 * The possible values of the "fc" parameter are:
	 *  0:  Flow control is completely disabled
	 *  1:  Rx flow control is enabled (we can receive छोड़ो frames, but
	 *      not send छोड़ो frames).
	 *  2:  Tx flow control is enabled (we can send छोड़ो frames but we करो
	 *      not support receiving छोड़ो frames).
	 *  3:  Both Rx and TX flow control (symmetric) are enabled.
	 */
	चयन (hw->fc) अणु
	हाल E1000_FC_NONE:
		/* Flow ctrl is completely disabled by a software over-ride */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD);
		अवरोध;
	हाल E1000_FC_RX_PAUSE:
		/* Rx Flow control is enabled and Tx Flow control is disabled by
		 * a software over-ride. Since there really isn't a way to
		 * advertise that we are capable of Rx Pause ONLY, we will
		 * advertise that we support both symmetric and asymmetric Rx
		 * PAUSE. Later, we will disable the adapter's ability to send
		 * PAUSE frames.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		अवरोध;
	हाल E1000_FC_TX_PAUSE:
		/* Tx Flow control is enabled, and Rx Flow control is disabled,
		 * by a software over-ride.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_ASM_सूची);
		अवरोध;
	हाल E1000_FC_FULL:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		txcw = (E1000_TXCW_ANE | E1000_TXCW_FD | E1000_TXCW_PAUSE_MASK);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	/* Since स्वतः-negotiation is enabled, take the link out of reset (the
	 * link will be in reset, because we previously reset the chip). This
	 * will restart स्वतः-negotiation.  If स्वतः-negotiation is successful
	 * then the link-up status bit will be set and the flow control enable
	 * bits (RFCE and TFCE) will be set according to their negotiated value.
	 */
	e_dbg("Auto-negotiation enabled\n");

	ew32(TXCW, txcw);
	ew32(CTRL, ctrl);
	E1000_WRITE_FLUSH();

	hw->txcw = txcw;
	msleep(1);

	/* If we have a संकेत (the cable is plugged in) then poll क्रम a
	 * "Link-Up" indication in the Device Status Register.  Time-out अगर a
	 * link isn't seen in 500 milliseconds seconds (Auto-negotiation should
	 * complete in less than 500 milliseconds even अगर the other end is करोing
	 * it in SW). For पूर्णांकernal serdes, we just assume a संकेत is present,
	 * then poll.
	 */
	अगर (hw->media_type == e1000_media_type_पूर्णांकernal_serdes ||
	    (er32(CTRL) & E1000_CTRL_SWDPIN1) == संकेत) अणु
		e_dbg("Looking for Link\n");
		क्रम (i = 0; i < (LINK_UP_TIMEOUT / 10); i++) अणु
			msleep(10);
			status = er32(STATUS);
			अगर (status & E1000_STATUS_LU)
				अवरोध;
		पूर्ण
		अगर (i == (LINK_UP_TIMEOUT / 10)) अणु
			e_dbg("Never got a valid link from auto-neg!!!\n");
			hw->स्वतःneg_failed = 1;
			/* AutoNeg failed to achieve a link, so we'll call
			 * e1000_check_क्रम_link. This routine will क्रमce the
			 * link up अगर we detect a संकेत. This will allow us to
			 * communicate with non-स्वतःnegotiating link partners.
			 */
			ret_val = e1000_check_क्रम_link(hw);
			अगर (ret_val) अणु
				e_dbg("Error while checking for link\n");
				वापस ret_val;
			पूर्ण
			hw->स्वतःneg_failed = 0;
		पूर्ण अन्यथा अणु
			hw->स्वतःneg_failed = 0;
			e_dbg("Valid Link Found\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		e_dbg("No Signal Detected\n");
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_rtl_setup - Copper link setup क्रम e1000_phy_rtl series.
 * @hw: Struct containing variables accessed by shared code
 *
 * Commits changes to PHY configuration by calling e1000_phy_reset().
 */
अटल s32 e1000_copper_link_rtl_setup(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	/* SW reset the PHY so all changes take effect */
	ret_val = e1000_phy_reset(hw);
	अगर (ret_val) अणु
		e_dbg("Error Resetting the PHY\n");
		वापस ret_val;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

अटल s32 gbe_dhg_phy_setup(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u32 ctrl_aux;

	चयन (hw->phy_type) अणु
	हाल e1000_phy_8211:
		ret_val = e1000_copper_link_rtl_setup(hw);
		अगर (ret_val) अणु
			e_dbg("e1000_copper_link_rtl_setup failed!\n");
			वापस ret_val;
		पूर्ण
		अवरोध;
	हाल e1000_phy_8201:
		/* Set RMII mode */
		ctrl_aux = er32(CTL_AUX);
		ctrl_aux |= E1000_CTL_AUX_RMII;
		ew32(CTL_AUX, ctrl_aux);
		E1000_WRITE_FLUSH();

		/* Disable the J/K bits required क्रम receive */
		ctrl_aux = er32(CTL_AUX);
		ctrl_aux |= 0x4;
		ctrl_aux &= ~0x2;
		ew32(CTL_AUX, ctrl_aux);
		E1000_WRITE_FLUSH();
		ret_val = e1000_copper_link_rtl_setup(hw);

		अगर (ret_val) अणु
			e_dbg("e1000_copper_link_rtl_setup failed!\n");
			वापस ret_val;
		पूर्ण
		अवरोध;
	शेष:
		e_dbg("Error Resetting the PHY\n");
		वापस E1000_ERR_PHY_TYPE;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_preconfig - early configuration क्रम copper
 * @hw: Struct containing variables accessed by shared code
 *
 * Make sure we have a valid PHY and change PHY mode beक्रमe link setup.
 */
अटल s32 e1000_copper_link_preconfig(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 phy_data;

	ctrl = er32(CTRL);
	/* With 82543, we need to क्रमce speed and duplex on the MAC equal to
	 * what the PHY speed and duplex configuration is. In addition, we need
	 * to perक्रमm a hardware reset on the PHY to take it out of reset.
	 */
	अगर (hw->mac_type > e1000_82543) अणु
		ctrl |= E1000_CTRL_SLU;
		ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
		ew32(CTRL, ctrl);
	पूर्ण अन्यथा अणु
		ctrl |=
		    (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX | E1000_CTRL_SLU);
		ew32(CTRL, ctrl);
		ret_val = e1000_phy_hw_reset(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Make sure we have a valid PHY */
	ret_val = e1000_detect_gig_phy(hw);
	अगर (ret_val) अणु
		e_dbg("Error, did not detect valid phy.\n");
		वापस ret_val;
	पूर्ण
	e_dbg("Phy ID = %x\n", hw->phy_id);

	/* Set PHY to class A mode (अगर necessary) */
	ret_val = e1000_set_phy_mode(hw);
	अगर (ret_val)
		वापस ret_val;

	अगर ((hw->mac_type == e1000_82545_rev_3) ||
	    (hw->mac_type == e1000_82546_rev_3)) अणु
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		phy_data |= 0x00000008;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	पूर्ण

	अगर (hw->mac_type <= e1000_82543 ||
	    hw->mac_type == e1000_82541 || hw->mac_type == e1000_82547 ||
	    hw->mac_type == e1000_82541_rev_2 ||
	    hw->mac_type == e1000_82547_rev_2)
		hw->phy_reset_disable = false;

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_igp_setup - Copper link setup क्रम e1000_phy_igp series.
 * @hw: Struct containing variables accessed by shared code
 */
अटल s32 e1000_copper_link_igp_setup(काष्ठा e1000_hw *hw)
अणु
	u32 led_ctrl;
	s32 ret_val;
	u16 phy_data;

	अगर (hw->phy_reset_disable)
		वापस E1000_SUCCESS;

	ret_val = e1000_phy_reset(hw);
	अगर (ret_val) अणु
		e_dbg("Error Resetting the PHY\n");
		वापस ret_val;
	पूर्ण

	/* Wait 15ms क्रम MAC to configure PHY from eeprom settings */
	msleep(15);
	/* Configure activity LED after PHY reset */
	led_ctrl = er32(LEDCTL);
	led_ctrl &= IGP_ACTIVITY_LED_MASK;
	led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
	ew32(LEDCTL, led_ctrl);

	/* The NVM settings will configure LPLU in D3 क्रम IGP2 and IGP3 PHYs */
	अगर (hw->phy_type == e1000_phy_igp) अणु
		/* disable lplu d3 during driver init */
		ret_val = e1000_set_d3_lplu_state(hw, false);
		अगर (ret_val) अणु
			e_dbg("Error Disabling LPLU D3\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Configure mdi-mdix settings */
	ret_val = e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) अणु
		hw->dsp_config_state = e1000_dsp_config_disabled;
		/* Force MDI क्रम earlier revs of the IGP PHY */
		phy_data &=
		    ~(IGP01E1000_PSCR_AUTO_MDIX |
		      IGP01E1000_PSCR_FORCE_MDI_MDIX);
		hw->mdix = 1;

	पूर्ण अन्यथा अणु
		hw->dsp_config_state = e1000_dsp_config_enabled;
		phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;

		चयन (hw->mdix) अणु
		हाल 1:
			phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;
			अवरोध;
		हाल 2:
			phy_data |= IGP01E1000_PSCR_FORCE_MDI_MDIX;
			अवरोध;
		हाल 0:
		शेष:
			phy_data |= IGP01E1000_PSCR_AUTO_MDIX;
			अवरोध;
		पूर्ण
	पूर्ण
	ret_val = e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* set स्वतः-master slave resolution settings */
	अगर (hw->स्वतःneg) अणु
		e1000_ms_type phy_ms_setting = hw->master_slave;

		अगर (hw->ffe_config_state == e1000_ffe_config_active)
			hw->ffe_config_state = e1000_ffe_config_enabled;

		अगर (hw->dsp_config_state == e1000_dsp_config_activated)
			hw->dsp_config_state = e1000_dsp_config_enabled;

		/* when स्वतःnegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware शेष.
		 */
		अगर (hw->स्वतःneg_advertised == ADVERTISE_1000_FULL) अणु
			/* Disable SmartSpeed */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			अगर (ret_val)
				वापस ret_val;
			phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			अगर (ret_val)
				वापस ret_val;
			/* Set स्वतः Master/Slave resolution process */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_1000T_CTRL, &phy_data);
			अगर (ret_val)
				वापस ret_val;
			phy_data &= ~CR_1000T_MS_ENABLE;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, PHY_1000T_CTRL, phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* load शेषs क्रम future use */
		hw->original_master_slave = (phy_data & CR_1000T_MS_ENABLE) ?
		    ((phy_data & CR_1000T_MS_VALUE) ?
		     e1000_ms_क्रमce_master :
		     e1000_ms_क्रमce_slave) : e1000_ms_स्वतः;

		चयन (phy_ms_setting) अणु
		हाल e1000_ms_क्रमce_master:
			phy_data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
			अवरोध;
		हाल e1000_ms_क्रमce_slave:
			phy_data |= CR_1000T_MS_ENABLE;
			phy_data &= ~(CR_1000T_MS_VALUE);
			अवरोध;
		हाल e1000_ms_स्वतः:
			phy_data &= ~CR_1000T_MS_ENABLE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_1000T_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_mgp_setup - Copper link setup क्रम e1000_phy_m88 series.
 * @hw: Struct containing variables accessed by shared code
 */
अटल s32 e1000_copper_link_mgp_setup(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	अगर (hw->phy_reset_disable)
		वापस E1000_SUCCESS;

	/* Enable CRS on TX. This must be set क्रम half-duplex operation. */
	ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;

	/* Options:
	 *   MDI/MDI-X = 0 (शेष)
	 *   0 - Auto क्रम all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto क्रम 1000Base-T only (MDI-X क्रम 10/100Base-T modes)
	 */
	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;

	चयन (hw->mdix) अणु
	हाल 1:
		phy_data |= M88E1000_PSCR_MDI_MANUAL_MODE;
		अवरोध;
	हाल 2:
		phy_data |= M88E1000_PSCR_MDIX_MANUAL_MODE;
		अवरोध;
	हाल 3:
		phy_data |= M88E1000_PSCR_AUTO_X_1000T;
		अवरोध;
	हाल 0:
	शेष:
		phy_data |= M88E1000_PSCR_AUTO_X_MODE;
		अवरोध;
	पूर्ण

	/* Options:
	 *   disable_polarity_correction = 0 (शेष)
	 *       Automatic Correction क्रम Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	phy_data &= ~M88E1000_PSCR_POLARITY_REVERSAL;
	अगर (hw->disable_polarity_correction == 1)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर (hw->phy_revision < M88E1011_I_REV_4) अणु
		/* Force TX_CLK in the Extended PHY Specअगरic Control Register
		 * to 25MHz घड़ी.
		 */
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
				       &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;

		अगर ((hw->phy_revision == E1000_REVISION_2) &&
		    (hw->phy_id == M88E1111_I_PHY_ID)) अणु
			/* Vidalia Phy, set the करोwnshअगरt counter to 5x */
			phy_data &= ~(M88EC018_EPSCR_DOWNSHIFT_COUNTER_MASK);
			phy_data |= M88EC018_EPSCR_DOWNSHIFT_COUNTER_5X;
			ret_val = e1000_ग_लिखो_phy_reg(hw,
						      M88E1000_EXT_PHY_SPEC_CTRL,
						      phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण अन्यथा अणु
			/* Configure Master and Slave करोwnshअगरt values */
			phy_data &= ~(M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK |
				      M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK);
			phy_data |= (M88E1000_EPSCR_MASTER_DOWNSHIFT_1X |
				     M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X);
			ret_val = e1000_ग_लिखो_phy_reg(hw,
						      M88E1000_EXT_PHY_SPEC_CTRL,
						      phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण

	/* SW Reset the PHY so all changes take effect */
	ret_val = e1000_phy_reset(hw);
	अगर (ret_val) अणु
		e_dbg("Error Resetting the PHY\n");
		वापस ret_val;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_स्वतःneg - setup स्वतः-neg
 * @hw: Struct containing variables accessed by shared code
 *
 * Setup स्वतः-negotiation and flow control advertisements,
 * and then perक्रमm स्वतः-negotiation.
 */
अटल s32 e1000_copper_link_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	/* Perक्रमm some bounds checking on the hw->स्वतःneg_advertised
	 * parameter.  If this variable is zero, then set it to the शेष.
	 */
	hw->स्वतःneg_advertised &= AUTONEG_ADVERTISE_SPEED_DEFAULT;

	/* If स्वतःneg_advertised is zero, we assume it was not शेषed
	 * by the calling code so we set to advertise full capability.
	 */
	अगर (hw->स्वतःneg_advertised == 0)
		hw->स्वतःneg_advertised = AUTONEG_ADVERTISE_SPEED_DEFAULT;

	/* IFE/RTL8201N PHY only supports 10/100 */
	अगर (hw->phy_type == e1000_phy_8201)
		hw->स्वतःneg_advertised &= AUTONEG_ADVERTISE_10_100_ALL;

	e_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = e1000_phy_setup_स्वतःneg(hw);
	अगर (ret_val) अणु
		e_dbg("Error Setting up Auto-Negotiation\n");
		वापस ret_val;
	पूर्ण
	e_dbg("Restarting Auto-Neg\n");

	/* Restart स्वतः-negotiation by setting the Auto Neg Enable bit and
	 * the Auto Neg Restart bit in the PHY control रेजिस्टर.
	 */
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data |= (MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG);
	ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Does the user want to रुको क्रम Auto-Neg to complete here, or
	 * check at a later समय (क्रम example, callback routine).
	 */
	अगर (hw->रुको_स्वतःneg_complete) अणु
		ret_val = e1000_रुको_स्वतःneg(hw);
		अगर (ret_val) अणु
			e_dbg
			    ("Error while waiting for autoneg to complete\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	hw->get_link_status = true;

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_copper_link_postconfig - post link setup
 * @hw: Struct containing variables accessed by shared code
 *
 * Config the MAC and the PHY after link is up.
 *   1) Set up the MAC to the current PHY speed/duplex
 *      अगर we are on 82543.  If we
 *      are on newer silicon, we only need to configure
 *      collision distance in the Transmit Control Register.
 *   2) Set up flow control on the MAC to that established with
 *      the link partner.
 *   3) Config DSP to improve Gigabit link quality क्रम some PHY revisions.
 */
अटल s32 e1000_copper_link_postconfig(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	अगर ((hw->mac_type >= e1000_82544) && (hw->mac_type != e1000_ce4100)) अणु
		e1000_config_collision_dist(hw);
	पूर्ण अन्यथा अणु
		ret_val = e1000_config_mac_to_phy(hw);
		अगर (ret_val) अणु
			e_dbg("Error configuring MAC to PHY settings\n");
			वापस ret_val;
		पूर्ण
	पूर्ण
	ret_val = e1000_config_fc_after_link_up(hw);
	अगर (ret_val) अणु
		e_dbg("Error Configuring Flow Control\n");
		वापस ret_val;
	पूर्ण

	/* Config DSP to improve Giga link quality */
	अगर (hw->phy_type == e1000_phy_igp) अणु
		ret_val = e1000_config_dsp_after_link_change(hw, true);
		अगर (ret_val) अणु
			e_dbg("Error Configuring DSP after link up\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_setup_copper_link - phy/speed/duplex setting
 * @hw: Struct containing variables accessed by shared code
 *
 * Detects which PHY is present and sets up the speed and duplex
 */
अटल s32 e1000_setup_copper_link(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 i;
	u16 phy_data;

	/* Check अगर it is a valid PHY and set PHY mode अगर necessary. */
	ret_val = e1000_copper_link_preconfig(hw);
	अगर (ret_val)
		वापस ret_val;

	अगर (hw->phy_type == e1000_phy_igp) अणु
		ret_val = e1000_copper_link_igp_setup(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अगर (hw->phy_type == e1000_phy_m88) अणु
		ret_val = e1000_copper_link_mgp_setup(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		ret_val = gbe_dhg_phy_setup(hw);
		अगर (ret_val) अणु
			e_dbg("gbe_dhg_phy_setup failed!\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	अगर (hw->स्वतःneg) अणु
		/* Setup स्वतःneg and flow control advertisement
		 * and perक्रमm स्वतःnegotiation
		 */
		ret_val = e1000_copper_link_स्वतःneg(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		/* PHY will be set to 10H, 10F, 100H,or 100F
		 * depending on value from क्रमced_speed_duplex.
		 */
		e_dbg("Forcing speed and duplex\n");
		ret_val = e1000_phy_क्रमce_speed_duplex(hw);
		अगर (ret_val) अणु
			e_dbg("Error Forcing Speed and Duplex\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Check link status. Wait up to 100 microseconds क्रम link to become
	 * valid.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर (phy_data & MII_SR_LINK_STATUS) अणु
			/* Config the MAC and PHY after link is up */
			ret_val = e1000_copper_link_postconfig(hw);
			अगर (ret_val)
				वापस ret_val;

			e_dbg("Valid link established!!!\n");
			वापस E1000_SUCCESS;
		पूर्ण
		udelay(10);
	पूर्ण

	e_dbg("Unable to establish link!!!\n");
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_setup_स्वतःneg - phy settings
 * @hw: Struct containing variables accessed by shared code
 *
 * Configures PHY स्वतःneg and flow control advertisement settings
 */
s32 e1000_phy_setup_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_AUTONEG_ADV, &mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	/* Read the MII 1000Base-T Control Register (Address 9). */
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_CTRL, &mii_1000t_ctrl_reg);
	अगर (ret_val)
		वापस ret_val;
	अन्यथा अगर (hw->phy_type == e1000_phy_8201)
		mii_1000t_ctrl_reg &= ~REG9_SPEED_MASK;

	/* Need to parse both स्वतःneg_advertised and fc and set up
	 * the appropriate PHY रेजिस्टरs.  First we will parse क्रम
	 * स्वतःneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * inभागidually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_स्वतःneg_adv_reg &= ~REG4_SPEED_MASK;
	mii_1000t_ctrl_reg &= ~REG9_SPEED_MASK;

	e_dbg("autoneg_advertised %x\n", hw->स्वतःneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_10_HALF) अणु
		e_dbg("Advertise 10mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 10 Mb Full Duplex? */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_10_FULL) अणु
		e_dbg("Advertise 10mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Half Duplex? */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_100_HALF) अणु
		e_dbg("Advertise 100mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Full Duplex? */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_100_FULL) अणु
		e_dbg("Advertise 100mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
	पूर्ण

	/* We करो not allow the Phy to advertise 1000 Mb Half Duplex */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_1000_HALF) अणु
		e_dbg
		    ("Advertise 1000mb Half duplex requested, request denied!\n");
	पूर्ण

	/* Do we want to advertise 1000 Mb Full Duplex? */
	अगर (hw->स्वतःneg_advertised & ADVERTISE_1000_FULL) अणु
		e_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
	पूर्ण

	/* Check क्रम a software override of the flow control settings, and
	 * setup the PHY advertisement रेजिस्टरs accordingly.  If
	 * स्वतः-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (PHY_AUTONEG_ADV) and re-start
	 * स्वतः-negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          but we करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	चयन (hw->fc) अणु
	हाल E1000_FC_NONE:	/* 0 */
		/* Flow control (RX & TX) is completely disabled by a
		 * software over-ride.
		 */
		mii_स्वतःneg_adv_reg &= ~(NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल E1000_FC_RX_PAUSE:	/* 1 */
		/* RX Flow control is enabled, and TX Flow control is
		 * disabled, by a software over-ride.
		 */
		/* Since there really isn't a way to advertise that we are
		 * capable of RX Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric RX PAUSE.  Later
		 * (in e1000_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल E1000_FC_TX_PAUSE:	/* 2 */
		/* TX Flow control is enabled, and RX Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_स्वतःneg_adv_reg |= NWAY_AR_ASM_सूची;
		mii_स्वतःneg_adv_reg &= ~NWAY_AR_PAUSE;
		अवरोध;
	हाल E1000_FC_FULL:	/* 3 */
		/* Flow control (both RX and TX) is enabled by a software
		 * over-ride.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_AUTONEG_ADV, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("Auto-Neg Advertising %x\n", mii_स्वतःneg_adv_reg);

	अगर (hw->phy_type == e1000_phy_8201) अणु
		mii_1000t_ctrl_reg = 0;
	पूर्ण अन्यथा अणु
		ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_1000T_CTRL,
					      mii_1000t_ctrl_reg);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_क्रमce_speed_duplex - क्रमce link settings
 * @hw: Struct containing variables accessed by shared code
 *
 * Force PHY speed and duplex settings to hw->क्रमced_speed_duplex
 */
अटल s32 e1000_phy_क्रमce_speed_duplex(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 mii_ctrl_reg;
	u16 mii_status_reg;
	u16 phy_data;
	u16 i;

	/* Turn off Flow control अगर we are क्रमcing speed and duplex. */
	hw->fc = E1000_FC_NONE;

	e_dbg("hw->fc = %d\n", hw->fc);

	/* Read the Device Control Register. */
	ctrl = er32(CTRL);

	/* Set the bits to Force Speed and Duplex in the Device Ctrl Reg. */
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~(DEVICE_SPEED_MASK);

	/* Clear the Auto Speed Detect Enable bit. */
	ctrl &= ~E1000_CTRL_ASDE;

	/* Read the MII Control Register. */
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &mii_ctrl_reg);
	अगर (ret_val)
		वापस ret_val;

	/* We need to disable स्वतःneg in order to क्रमce link and duplex. */

	mii_ctrl_reg &= ~MII_CR_AUTO_NEG_EN;

	/* Are we क्रमcing Full or Half Duplex? */
	अगर (hw->क्रमced_speed_duplex == e1000_100_full ||
	    hw->क्रमced_speed_duplex == e1000_10_full) अणु
		/* We want to क्रमce full duplex so we SET the full duplex bits
		 * in the Device and MII Control Registers.
		 */
		ctrl |= E1000_CTRL_FD;
		mii_ctrl_reg |= MII_CR_FULL_DUPLEX;
		e_dbg("Full Duplex\n");
	पूर्ण अन्यथा अणु
		/* We want to क्रमce half duplex so we CLEAR the full duplex bits
		 * in the Device and MII Control Registers.
		 */
		ctrl &= ~E1000_CTRL_FD;
		mii_ctrl_reg &= ~MII_CR_FULL_DUPLEX;
		e_dbg("Half Duplex\n");
	पूर्ण

	/* Are we क्रमcing 100Mbps??? */
	अगर (hw->क्रमced_speed_duplex == e1000_100_full ||
	    hw->क्रमced_speed_duplex == e1000_100_half) अणु
		/* Set the 100Mb bit and turn off the 1000Mb and 10Mb bits. */
		ctrl |= E1000_CTRL_SPD_100;
		mii_ctrl_reg |= MII_CR_SPEED_100;
		mii_ctrl_reg &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_10);
		e_dbg("Forcing 100mb ");
	पूर्ण अन्यथा अणु
		/* Set the 10Mb bit and turn off the 1000Mb and 100Mb bits. */
		ctrl &= ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
		mii_ctrl_reg |= MII_CR_SPEED_10;
		mii_ctrl_reg &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_100);
		e_dbg("Forcing 10mb ");
	पूर्ण

	e1000_config_collision_dist(hw);

	/* Write the configured values back to the Device Control Reg. */
	ew32(CTRL, ctrl);

	अगर (hw->phy_type == e1000_phy_m88) अणु
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* Clear Auto-Crossover to क्रमce MDI manually. M88E1000 requires
		 * MDI क्रमced whenever speed are duplex are क्रमced.
		 */
		phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;

		e_dbg("M88E1000 PSCR: %x\n", phy_data);

		/* Need to reset the PHY or these changes will be ignored */
		mii_ctrl_reg |= MII_CR_RESET;

		/* Disable MDI-X support क्रम 10/100 */
	पूर्ण अन्यथा अणु
		/* Clear Auto-Crossover to क्रमce MDI manually.  IGP requires MDI
		 * क्रमced whenever speed or duplex are क्रमced.
		 */
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;
		phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;

		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Write back the modअगरied PHY MII control रेजिस्टर. */
	ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, mii_ctrl_reg);
	अगर (ret_val)
		वापस ret_val;

	udelay(1);

	/* The रुको_स्वतःneg_complete flag may be a little misleading here.
	 * Since we are क्रमcing speed and duplex, Auto-Neg is not enabled.
	 * But we करो want to delay क्रम a period जबतक क्रमcing only so we
	 * करोn't generate false No Link messages.  So we will रुको here
	 * only अगर the user has set रुको_स्वतःneg_complete to 1, which is
	 * the शेष.
	 */
	अगर (hw->रुको_स्वतःneg_complete) अणु
		/* We will रुको क्रम स्वतःneg to complete. */
		e_dbg("Waiting for forced speed/duplex link.\n");
		mii_status_reg = 0;

		/* Wait क्रम स्वतःneg to complete or 4.5 seconds to expire */
		क्रम (i = PHY_FORCE_TIME; i > 0; i--) अणु
			/* Read the MII Status Register and रुको क्रम Auto-Neg
			 * Complete bit to be set.
			 */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			अगर (ret_val)
				वापस ret_val;

			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			अगर (ret_val)
				वापस ret_val;

			अगर (mii_status_reg & MII_SR_LINK_STATUS)
				अवरोध;
			msleep(100);
		पूर्ण
		अगर ((i == 0) && (hw->phy_type == e1000_phy_m88)) अणु
			/* We didn't get link.  Reset the DSP and रुको again
			 * क्रम link.
			 */
			ret_val = e1000_phy_reset_dsp(hw);
			अगर (ret_val) अणु
				e_dbg("Error Resetting PHY DSP\n");
				वापस ret_val;
			पूर्ण
		पूर्ण
		/* This loop will early-out अगर the link condition has been
		 * met
		 */
		क्रम (i = PHY_FORCE_TIME; i > 0; i--) अणु
			अगर (mii_status_reg & MII_SR_LINK_STATUS)
				अवरोध;
			msleep(100);
			/* Read the MII Status Register and रुको क्रम Auto-Neg
			 * Complete bit to be set.
			 */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			अगर (ret_val)
				वापस ret_val;

			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण

	अगर (hw->phy_type == e1000_phy_m88) अणु
		/* Because we reset the PHY above, we need to re-क्रमce TX_CLK in
		 * the Extended PHY Specअगरic Control Register to 25MHz घड़ी.
		 * This value शेषs back to a 2.5MHz घड़ी when the PHY is
		 * reset.
		 */
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
				       &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
					phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* In addition, because of the s/w reset above, we need to
		 * enable CRS on Tx.  This must be set क्रम both full and half
		 * duplex operation.
		 */
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर ((hw->mac_type == e1000_82544 ||
		     hw->mac_type == e1000_82543) &&
		    (!hw->स्वतःneg) &&
		    (hw->क्रमced_speed_duplex == e1000_10_full ||
		     hw->क्रमced_speed_duplex == e1000_10_half)) अणु
			ret_val = e1000_polarity_reversal_workaround(hw);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_config_collision_dist - set collision distance रेजिस्टर
 * @hw: Struct containing variables accessed by shared code
 *
 * Sets the collision distance in the Transmit Control रेजिस्टर.
 * Link should have been established previously. Reads the speed and duplex
 * inक्रमmation from the Device Status रेजिस्टर.
 */
व्योम e1000_config_collision_dist(काष्ठा e1000_hw *hw)
अणु
	u32 tctl, coll_dist;

	अगर (hw->mac_type < e1000_82543)
		coll_dist = E1000_COLLISION_DISTANCE_82542;
	अन्यथा
		coll_dist = E1000_COLLISION_DISTANCE;

	tctl = er32(TCTL);

	tctl &= ~E1000_TCTL_COLD;
	tctl |= coll_dist << E1000_COLD_SHIFT;

	ew32(TCTL, tctl);
	E1000_WRITE_FLUSH();
पूर्ण

/**
 * e1000_config_mac_to_phy - sync phy and mac settings
 * @hw: Struct containing variables accessed by shared code
 *
 * Sets MAC speed and duplex settings to reflect the those in the PHY
 * The contents of the PHY रेजिस्टर containing the needed inक्रमmation need to
 * be passed in.
 */
अटल s32 e1000_config_mac_to_phy(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 phy_data;

	/* 82544 or newer MAC, Auto Speed Detection takes care of
	 * MAC speed/duplex configuration.
	 */
	अगर ((hw->mac_type >= e1000_82544) && (hw->mac_type != e1000_ce4100))
		वापस E1000_SUCCESS;

	/* Read the Device Control Register and set the bits to Force Speed
	 * and Duplex.
	 */
	ctrl = er32(CTRL);
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~(E1000_CTRL_SPD_SEL | E1000_CTRL_ILOS);

	चयन (hw->phy_type) अणु
	हाल e1000_phy_8201:
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर (phy_data & RTL_PHY_CTRL_FD)
			ctrl |= E1000_CTRL_FD;
		अन्यथा
			ctrl &= ~E1000_CTRL_FD;

		अगर (phy_data & RTL_PHY_CTRL_SPD_100)
			ctrl |= E1000_CTRL_SPD_100;
		अन्यथा
			ctrl |= E1000_CTRL_SPD_10;

		e1000_config_collision_dist(hw);
		अवरोध;
	शेष:
		/* Set up duplex in the Device Control and Transmit Control
		 * रेजिस्टरs depending on negotiated values.
		 */
		ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर (phy_data & M88E1000_PSSR_DPLX)
			ctrl |= E1000_CTRL_FD;
		अन्यथा
			ctrl &= ~E1000_CTRL_FD;

		e1000_config_collision_dist(hw);

		/* Set up speed in the Device Control रेजिस्टर depending on
		 * negotiated values.
		 */
		अगर ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS)
			ctrl |= E1000_CTRL_SPD_1000;
		अन्यथा अगर ((phy_data & M88E1000_PSSR_SPEED) ==
			 M88E1000_PSSR_100MBS)
			ctrl |= E1000_CTRL_SPD_100;
	पूर्ण

	/* Write the configured values back to the Device Control Reg. */
	ew32(CTRL, ctrl);
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_क्रमce_mac_fc - क्रमce flow control settings
 * @hw: Struct containing variables accessed by shared code
 *
 * Forces the MAC's flow control settings.
 * Sets the TFCE and RFCE bits in the device control रेजिस्टर to reflect
 * the adapter settings. TFCE and RFCE need to be explicitly set by
 * software when a Copper PHY is used because स्वतःnegotiation is managed
 * by the PHY rather than the MAC. Software must also configure these
 * bits when link is क्रमced on a fiber connection.
 */
s32 e1000_क्रमce_mac_fc(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;

	/* Get the current configuration of the Device Control Register */
	ctrl = er32(CTRL);

	/* Because we didn't get link via the पूर्णांकernal स्वतः-negotiation
	 * mechanism (we either क्रमced link or we got link via PHY
	 * स्वतः-neg), we have to manually enable/disable transmit an
	 * receive flow control.
	 *
	 * The "Case" statement below enables/disable flow control
	 * according to the "hw->fc" parameter.
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

	चयन (hw->fc) अणु
	हाल E1000_FC_NONE:
		ctrl &= (~(E1000_CTRL_TFCE | E1000_CTRL_RFCE));
		अवरोध;
	हाल E1000_FC_RX_PAUSE:
		ctrl &= (~E1000_CTRL_TFCE);
		ctrl |= E1000_CTRL_RFCE;
		अवरोध;
	हाल E1000_FC_TX_PAUSE:
		ctrl &= (~E1000_CTRL_RFCE);
		ctrl |= E1000_CTRL_TFCE;
		अवरोध;
	हाल E1000_FC_FULL:
		ctrl |= (E1000_CTRL_TFCE | E1000_CTRL_RFCE);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	/* Disable TX Flow Control क्रम 82542 (rev 2.0) */
	अगर (hw->mac_type == e1000_82542_rev2_0)
		ctrl &= (~E1000_CTRL_TFCE);

	ew32(CTRL, ctrl);
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_config_fc_after_link_up - configure flow control after स्वतःneg
 * @hw: Struct containing variables accessed by shared code
 *
 * Configures flow control settings after link is established
 * Should be called immediately after a valid link has been established.
 * Forces MAC flow control settings अगर link was क्रमced. When in MII/GMII mode
 * and स्वतःnegotiation is enabled, the MAC flow control settings will be set
 * based on the flow control negotiated by the PHY. In TBI mode, the TFCE
 * and RFCE bits will be स्वतःmatically set to the negotiated flow control mode.
 */
अटल s32 e1000_config_fc_after_link_up(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 mii_status_reg;
	u16 mii_nway_adv_reg;
	u16 mii_nway_lp_ability_reg;
	u16 speed;
	u16 duplex;

	/* Check क्रम the हाल where we have fiber media and स्वतः-neg failed
	 * so we had to क्रमce link.  In this हाल, we need to क्रमce the
	 * configuration of the MAC to match the "fc" parameter.
	 */
	अगर (((hw->media_type == e1000_media_type_fiber) &&
	     (hw->स्वतःneg_failed)) ||
	    ((hw->media_type == e1000_media_type_पूर्णांकernal_serdes) &&
	     (hw->स्वतःneg_failed)) ||
	    ((hw->media_type == e1000_media_type_copper) &&
	     (!hw->स्वतःneg))) अणु
		ret_val = e1000_क्रमce_mac_fc(hw);
		अगर (ret_val) अणु
			e_dbg("Error forcing flow control settings\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Check क्रम the हाल where we have copper media and स्वतः-neg is
	 * enabled.  In this हाल, we need to check and see अगर Auto-Neg
	 * has completed, and अगर so, how the PHY and link partner has
	 * flow control configured.
	 */
	अगर ((hw->media_type == e1000_media_type_copper) && hw->स्वतःneg) अणु
		/* Read the MII Status Register and check to see अगर AutoNeg
		 * has completed.  We पढ़ो this twice because this reg has
		 * some "sticky" (latched) bits.
		 */
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		अगर (mii_status_reg & MII_SR_AUTONEG_COMPLETE) अणु
			/* The AutoNeg process has completed, so we now need to
			 * पढ़ो both the Auto Negotiation Advertisement Register
			 * (Address 4) and the Auto_Negotiation Base Page
			 * Ability Register (Address 5) to determine how flow
			 * control was negotiated.
			 */
			ret_val = e1000_पढ़ो_phy_reg(hw, PHY_AUTONEG_ADV,
						     &mii_nway_adv_reg);
			अगर (ret_val)
				वापस ret_val;
			ret_val = e1000_पढ़ो_phy_reg(hw, PHY_LP_ABILITY,
						     &mii_nway_lp_ability_reg);
			अगर (ret_val)
				वापस ret_val;

			/* Two bits in the Auto Negotiation Advertisement
			 * Register (Address 4) and two bits in the Auto
			 * Negotiation Base Page Ability Register (Address 5)
			 * determine flow control क्रम both the PHY and the link
			 * partner.  The following table, taken out of the IEEE
			 * 802.3ab/D6.0 dated March 25, 1999, describes these
			 * PAUSE resolution bits and how flow control is
			 * determined based upon these settings.
			 * NOTE:  DC = Don't Care
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | NIC Resolution
			 *-------|---------|-------|---------|------------------
			 *   0   |    0    |  DC   |   DC    | E1000_FC_NONE
			 *   0   |    1    |   0   |   DC    | E1000_FC_NONE
			 *   0   |    1    |   1   |    0    | E1000_FC_NONE
			 *   0   |    1    |   1   |    1    | E1000_FC_TX_PAUSE
			 *   1   |    0    |   0   |   DC    | E1000_FC_NONE
			 *   1   |   DC    |   1   |   DC    | E1000_FC_FULL
			 *   1   |    1    |   0   |    0    | E1000_FC_NONE
			 *   1   |    1    |   0   |    1    | E1000_FC_RX_PAUSE
			 *
			 */
			/* Are both PAUSE bits set to 1?  If so, this implies
			 * Symmetric Flow Control is enabled at both ends.  The
			 * ASM_सूची bits are irrelevant per the spec.
			 *
			 * For Symmetric Flow Control:
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
			 *-------|---------|-------|---------|------------------
			 *   1   |   DC    |   1   |   DC    | E1000_FC_FULL
			 *
			 */
			अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			    (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE)) अणु
				/* Now we need to check अगर the user selected Rx
				 * ONLY of छोड़ो frames.  In this हाल, we had
				 * to advertise FULL flow control because we
				 * could not advertise Rx ONLY. Hence, we must
				 * now check to see अगर we need to turn OFF the
				 * TRANSMISSION of PAUSE frames.
				 */
				अगर (hw->original_fc == E1000_FC_FULL) अणु
					hw->fc = E1000_FC_FULL;
					e_dbg("Flow Control = FULL.\n");
				पूर्ण अन्यथा अणु
					hw->fc = E1000_FC_RX_PAUSE;
					e_dbg
					    ("Flow Control = RX PAUSE frames only.\n");
				पूर्ण
			पूर्ण
			/* For receiving PAUSE frames ONLY.
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
			 *-------|---------|-------|---------|------------------
			 *   0   |    1    |   1   |    1    | E1000_FC_TX_PAUSE
			 *
			 */
			अन्यथा अगर (!(mii_nway_adv_reg & NWAY_AR_PAUSE) &&
				 (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
				hw->fc = E1000_FC_TX_PAUSE;
				e_dbg
				    ("Flow Control = TX PAUSE frames only.\n");
			पूर्ण
			/* For transmitting PAUSE frames ONLY.
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_सूची | PAUSE | ASM_सूची | Result
			 *-------|---------|-------|---------|------------------
			 *   1   |    1    |   0   |    1    | E1000_FC_RX_PAUSE
			 *
			 */
			अन्यथा अगर ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
				 (mii_nway_adv_reg & NWAY_AR_ASM_सूची) &&
				 !(mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_सूची)) अणु
				hw->fc = E1000_FC_RX_PAUSE;
				e_dbg
				    ("Flow Control = RX PAUSE frames only.\n");
			पूर्ण
			/* Per the IEEE spec, at this poपूर्णांक flow control should
			 * be disabled.  However, we want to consider that we
			 * could be connected to a legacy चयन that करोesn't
			 * advertise desired flow control, but can be क्रमced on
			 * the link partner.  So अगर we advertised no flow
			 * control, that is what we will resolve to.  If we
			 * advertised some kind of receive capability (Rx Pause
			 * Only or Full Flow Control) and the link partner
			 * advertised none, we will configure ourselves to
			 * enable Rx Flow Control only.  We can करो this safely
			 * क्रम two reasons:  If the link partner really
			 * didn't want flow control enabled, and we enable Rx,
			 * no harm करोne since we won't be receiving any PAUSE
			 * frames anyway.  If the पूर्णांकent on the link partner was
			 * to have flow control enabled, then by us enabling Rx
			 * only, we can at least receive छोड़ो frames and
			 * process them. This is a good idea because in most
			 * हालs, since we are preकरोminantly a server NIC, more
			 * बार than not we will be asked to delay transmission
			 * of packets than asking our link partner to छोड़ो
			 * transmission of frames.
			 */
			अन्यथा अगर ((hw->original_fc == E1000_FC_NONE ||
				  hw->original_fc == E1000_FC_TX_PAUSE) ||
				 hw->fc_strict_ieee) अणु
				hw->fc = E1000_FC_NONE;
				e_dbg("Flow Control = NONE.\n");
			पूर्ण अन्यथा अणु
				hw->fc = E1000_FC_RX_PAUSE;
				e_dbg
				    ("Flow Control = RX PAUSE frames only.\n");
			पूर्ण

			/* Now we need to करो one last check...  If we स्वतः-
			 * negotiated to HALF DUPLEX, flow control should not be
			 * enabled per IEEE 802.3 spec.
			 */
			ret_val =
			    e1000_get_speed_and_duplex(hw, &speed, &duplex);
			अगर (ret_val) अणु
				e_dbg
				    ("Error getting link speed and duplex\n");
				वापस ret_val;
			पूर्ण

			अगर (duplex == HALF_DUPLEX)
				hw->fc = E1000_FC_NONE;

			/* Now we call a subroutine to actually क्रमce the MAC
			 * controller to use the correct flow control settings.
			 */
			ret_val = e1000_क्रमce_mac_fc(hw);
			अगर (ret_val) अणु
				e_dbg
				    ("Error forcing flow control settings\n");
				वापस ret_val;
			पूर्ण
		पूर्ण अन्यथा अणु
			e_dbg
			    ("Copper PHY and Auto Neg has not completed.\n");
		पूर्ण
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_check_क्रम_serdes_link_generic - Check क्रम link (Serdes)
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Checks क्रम link up on the hardware.  If link is not up and we have
 * a संकेत, then we need to क्रमce link up.
 */
अटल s32 e1000_check_क्रम_serdes_link_generic(काष्ठा e1000_hw *hw)
अणु
	u32 rxcw;
	u32 ctrl;
	u32 status;
	s32 ret_val = E1000_SUCCESS;

	ctrl = er32(CTRL);
	status = er32(STATUS);
	rxcw = er32(RXCW);

	/* If we करोn't have link (स्वतः-negotiation failed or link partner
	 * cannot स्वतः-negotiate), and our link partner is not trying to
	 * स्वतः-negotiate with us (we are receiving idles or data),
	 * we need to क्रमce link up. We also need to give स्वतः-negotiation
	 * समय to complete.
	 */
	/* (ctrl & E1000_CTRL_SWDPIN1) == 1 == have संकेत */
	अगर ((!(status & E1000_STATUS_LU)) && (!(rxcw & E1000_RXCW_C))) अणु
		अगर (hw->स्वतःneg_failed == 0) अणु
			hw->स्वतःneg_failed = 1;
			जाओ out;
		पूर्ण
		e_dbg("NOT RXing /C/, disable AutoNeg and force link.\n");

		/* Disable स्वतः-negotiation in the TXCW रेजिस्टर */
		ew32(TXCW, (hw->txcw & ~E1000_TXCW_ANE));

		/* Force link-up and also क्रमce full-duplex. */
		ctrl = er32(CTRL);
		ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
		ew32(CTRL, ctrl);

		/* Configure Flow Control after क्रमcing link up. */
		ret_val = e1000_config_fc_after_link_up(hw);
		अगर (ret_val) अणु
			e_dbg("Error configuring flow control\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) अणु
		/* If we are क्रमcing link and we are receiving /C/ ordered
		 * sets, re-enable स्वतः-negotiation in the TXCW रेजिस्टर
		 * and disable क्रमced link in the Device Control रेजिस्टर
		 * in an attempt to स्वतः-negotiate with our link partner.
		 */
		e_dbg("RXing /C/, enable AutoNeg and stop forcing link.\n");
		ew32(TXCW, hw->txcw);
		ew32(CTRL, (ctrl & ~E1000_CTRL_SLU));

		hw->serdes_has_link = true;
	पूर्ण अन्यथा अगर (!(E1000_TXCW_ANE & er32(TXCW))) अणु
		/* If we क्रमce link क्रम non-स्वतः-negotiation चयन, check
		 * link status based on MAC synchronization क्रम पूर्णांकernal
		 * serdes media type.
		 */
		/* SYNCH bit and IV bit are sticky. */
		udelay(10);
		rxcw = er32(RXCW);
		अगर (rxcw & E1000_RXCW_SYNCH) अणु
			अगर (!(rxcw & E1000_RXCW_IV)) अणु
				hw->serdes_has_link = true;
				e_dbg("SERDES: Link up - forced.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			hw->serdes_has_link = false;
			e_dbg("SERDES: Link down - force failed.\n");
		पूर्ण
	पूर्ण

	अगर (E1000_TXCW_ANE & er32(TXCW)) अणु
		status = er32(STATUS);
		अगर (status & E1000_STATUS_LU) अणु
			/* SYNCH bit and IV bit are sticky, so reपढ़ो rxcw. */
			udelay(10);
			rxcw = er32(RXCW);
			अगर (rxcw & E1000_RXCW_SYNCH) अणु
				अगर (!(rxcw & E1000_RXCW_IV)) अणु
					hw->serdes_has_link = true;
					e_dbg("SERDES: Link up - autoneg "
						 "completed successfully.\n");
				पूर्ण अन्यथा अणु
					hw->serdes_has_link = false;
					e_dbg("SERDES: Link down - invalid"
						 "codewords detected in autoneg.\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				hw->serdes_has_link = false;
				e_dbg("SERDES: Link down - no sync.\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			hw->serdes_has_link = false;
			e_dbg("SERDES: Link down - autoneg failed\n");
		पूर्ण
	पूर्ण

      out:
	वापस ret_val;
पूर्ण

/**
 * e1000_check_क्रम_link
 * @hw: Struct containing variables accessed by shared code
 *
 * Checks to see अगर the link status of the hardware has changed.
 * Called by any function that needs to check the link status of the adapter.
 */
s32 e1000_check_क्रम_link(काष्ठा e1000_hw *hw)
अणु
	u32 status;
	u32 rctl;
	u32 icr;
	s32 ret_val;
	u16 phy_data;

	er32(CTRL);
	status = er32(STATUS);

	/* On adapters with a MAC newer than 82544, SW Definable pin 1 will be
	 * set when the optics detect a संकेत. On older adapters, it will be
	 * cleared when there is a संकेत.  This applies to fiber media only.
	 */
	अगर ((hw->media_type == e1000_media_type_fiber) ||
	    (hw->media_type == e1000_media_type_पूर्णांकernal_serdes)) अणु
		er32(RXCW);

		अगर (hw->media_type == e1000_media_type_fiber) अणु
			अगर (status & E1000_STATUS_LU)
				hw->get_link_status = false;
		पूर्ण
	पूर्ण

	/* If we have a copper PHY then we only want to go out to the PHY
	 * रेजिस्टरs to see अगर Auto-Neg has completed and/or अगर our link
	 * status has changed.  The get_link_status flag will be set अगर we
	 * receive a Link Status Change पूर्णांकerrupt or we have Rx Sequence
	 * Errors.
	 */
	अगर ((hw->media_type == e1000_media_type_copper) && hw->get_link_status) अणु
		/* First we want to see अगर the MII Status Register reports
		 * link.  If so, then we want to get the current speed/duplex
		 * of the PHY.
		 * Read the रेजिस्टर twice since the link bit is sticky.
		 */
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर (phy_data & MII_SR_LINK_STATUS) अणु
			hw->get_link_status = false;
			/* Check अगर there was DownShअगरt, must be checked
			 * immediately after link-up
			 */
			e1000_check_करोwnshअगरt(hw);

			/* If we are on 82544 or 82543 silicon and speed/duplex
			 * are क्रमced to 10H or 10F, then we will implement the
			 * polarity reversal workaround.  We disable पूर्णांकerrupts
			 * first, and upon वापसing, place the devices
			 * पूर्णांकerrupt state to its previous value except क्रम the
			 * link status change पूर्णांकerrupt which will
			 * happen due to the execution of this workaround.
			 */

			अगर ((hw->mac_type == e1000_82544 ||
			     hw->mac_type == e1000_82543) &&
			    (!hw->स्वतःneg) &&
			    (hw->क्रमced_speed_duplex == e1000_10_full ||
			     hw->क्रमced_speed_duplex == e1000_10_half)) अणु
				ew32(IMC, 0xffffffff);
				ret_val =
				    e1000_polarity_reversal_workaround(hw);
				icr = er32(ICR);
				ew32(ICS, (icr & ~E1000_ICS_LSC));
				ew32(IMS, IMS_ENABLE_MASK);
			पूर्ण

		पूर्ण अन्यथा अणु
			/* No link detected */
			e1000_config_dsp_after_link_change(hw, false);
			वापस 0;
		पूर्ण

		/* If we are क्रमcing speed/duplex, then we simply वापस since
		 * we have alपढ़ोy determined whether we have link or not.
		 */
		अगर (!hw->स्वतःneg)
			वापस -E1000_ERR_CONFIG;

		/* optimize the dsp settings क्रम the igp phy */
		e1000_config_dsp_after_link_change(hw, true);

		/* We have a M88E1000 PHY and Auto-Neg is enabled.  If we
		 * have Si on board that is 82544 or newer, Auto
		 * Speed Detection takes care of MAC speed/duplex
		 * configuration.  So we only need to configure Collision
		 * Distance in the MAC.  Otherwise, we need to क्रमce
		 * speed/duplex on the MAC to the current PHY speed/duplex
		 * settings.
		 */
		अगर ((hw->mac_type >= e1000_82544) &&
		    (hw->mac_type != e1000_ce4100))
			e1000_config_collision_dist(hw);
		अन्यथा अणु
			ret_val = e1000_config_mac_to_phy(hw);
			अगर (ret_val) अणु
				e_dbg
				    ("Error configuring MAC to PHY settings\n");
				वापस ret_val;
			पूर्ण
		पूर्ण

		/* Configure Flow Control now that Auto-Neg has completed.
		 * First, we need to restore the desired flow control settings
		 * because we may have had to re-स्वतःneg with a dअगरferent link
		 * partner.
		 */
		ret_val = e1000_config_fc_after_link_up(hw);
		अगर (ret_val) अणु
			e_dbg("Error configuring flow control\n");
			वापस ret_val;
		पूर्ण

		/* At this poपूर्णांक we know that we are on copper and we have
		 * स्वतः-negotiated link.  These are conditions क्रम checking the
		 * link partner capability रेजिस्टर.  We use the link speed to
		 * determine अगर TBI compatibility needs to be turned on or off.
		 * If the link is not at gigabit speed, then TBI compatibility
		 * is not needed.  If we are at gigabit speed, we turn on TBI
		 * compatibility.
		 */
		अगर (hw->tbi_compatibility_en) अणु
			u16 speed, duplex;

			ret_val =
			    e1000_get_speed_and_duplex(hw, &speed, &duplex);

			अगर (ret_val) अणु
				e_dbg
				    ("Error getting link speed and duplex\n");
				वापस ret_val;
			पूर्ण
			अगर (speed != SPEED_1000) अणु
				/* If link speed is not set to gigabit speed, we
				 * करो not need to enable TBI compatibility.
				 */
				अगर (hw->tbi_compatibility_on) अणु
					/* If we previously were in the mode,
					 * turn it off.
					 */
					rctl = er32(RCTL);
					rctl &= ~E1000_RCTL_SBP;
					ew32(RCTL, rctl);
					hw->tbi_compatibility_on = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* If TBI compatibility is was previously off,
				 * turn it on. For compatibility with a TBI link
				 * partner, we will store bad packets. Some
				 * frames have an additional byte on the end and
				 * will look like CRC errors to to the hardware.
				 */
				अगर (!hw->tbi_compatibility_on) अणु
					hw->tbi_compatibility_on = true;
					rctl = er32(RCTL);
					rctl |= E1000_RCTL_SBP;
					ew32(RCTL, rctl);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((hw->media_type == e1000_media_type_fiber) ||
	    (hw->media_type == e1000_media_type_पूर्णांकernal_serdes))
		e1000_check_क्रम_serdes_link_generic(hw);

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_get_speed_and_duplex
 * @hw: Struct containing variables accessed by shared code
 * @speed: Speed of the connection
 * @duplex: Duplex setting of the connection
 *
 * Detects the current speed and duplex settings of the hardware.
 */
s32 e1000_get_speed_and_duplex(काष्ठा e1000_hw *hw, u16 *speed, u16 *duplex)
अणु
	u32 status;
	s32 ret_val;
	u16 phy_data;

	अगर (hw->mac_type >= e1000_82543) अणु
		status = er32(STATUS);
		अगर (status & E1000_STATUS_SPEED_1000) अणु
			*speed = SPEED_1000;
			e_dbg("1000 Mbs, ");
		पूर्ण अन्यथा अगर (status & E1000_STATUS_SPEED_100) अणु
			*speed = SPEED_100;
			e_dbg("100 Mbs, ");
		पूर्ण अन्यथा अणु
			*speed = SPEED_10;
			e_dbg("10 Mbs, ");
		पूर्ण

		अगर (status & E1000_STATUS_FD) अणु
			*duplex = FULL_DUPLEX;
			e_dbg("Full Duplex\n");
		पूर्ण अन्यथा अणु
			*duplex = HALF_DUPLEX;
			e_dbg(" Half Duplex\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		e_dbg("1000 Mbs, Full Duplex\n");
		*speed = SPEED_1000;
		*duplex = FULL_DUPLEX;
	पूर्ण

	/* IGP01 PHY may advertise full duplex operation after speed करोwngrade
	 * even अगर it is operating at half duplex.  Here we set the duplex
	 * settings to match the duplex in the link partner's capabilities.
	 */
	अगर (hw->phy_type == e1000_phy_igp && hw->speed_करोwngraded) अणु
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_AUTONEG_EXP, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		अगर (!(phy_data & NWAY_ER_LP_NWAY_CAPS))
			*duplex = HALF_DUPLEX;
		अन्यथा अणु
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, PHY_LP_ABILITY, &phy_data);
			अगर (ret_val)
				वापस ret_val;
			अगर ((*speed == SPEED_100 &&
			     !(phy_data & NWAY_LPAR_100TX_FD_CAPS)) ||
			    (*speed == SPEED_10 &&
			     !(phy_data & NWAY_LPAR_10T_FD_CAPS)))
				*duplex = HALF_DUPLEX;
		पूर्ण
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_रुको_स्वतःneg
 * @hw: Struct containing variables accessed by shared code
 *
 * Blocks until स्वतःneg completes or बार out (~4.5 seconds)
 */
अटल s32 e1000_रुको_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 i;
	u16 phy_data;

	e_dbg("Waiting for Auto-Neg to complete.\n");

	/* We will रुको क्रम स्वतःneg to complete or 4.5 seconds to expire. */
	क्रम (i = PHY_AUTO_NEG_TIME; i > 0; i--) अणु
		/* Read the MII Status Register and रुको क्रम Auto-Neg
		 * Complete bit to be set.
		 */
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;
		अगर (phy_data & MII_SR_AUTONEG_COMPLETE)
			वापस E1000_SUCCESS;

		msleep(100);
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_उठाओ_mdi_clk - Raises the Management Data Clock
 * @hw: Struct containing variables accessed by shared code
 * @ctrl: Device control रेजिस्टर's current value
 */
अटल व्योम e1000_उठाओ_mdi_clk(काष्ठा e1000_hw *hw, u32 *ctrl)
अणु
	/* Raise the घड़ी input to the Management Data Clock (by setting the
	 * MDC bit), and then delay 10 microseconds.
	 */
	ew32(CTRL, (*ctrl | E1000_CTRL_MDC));
	E1000_WRITE_FLUSH();
	udelay(10);
पूर्ण

/**
 * e1000_lower_mdi_clk - Lowers the Management Data Clock
 * @hw: Struct containing variables accessed by shared code
 * @ctrl: Device control रेजिस्टर's current value
 */
अटल व्योम e1000_lower_mdi_clk(काष्ठा e1000_hw *hw, u32 *ctrl)
अणु
	/* Lower the घड़ी input to the Management Data Clock (by clearing the
	 * MDC bit), and then delay 10 microseconds.
	 */
	ew32(CTRL, (*ctrl & ~E1000_CTRL_MDC));
	E1000_WRITE_FLUSH();
	udelay(10);
पूर्ण

/**
 * e1000_shअगरt_out_mdi_bits - Shअगरts data bits out to the PHY
 * @hw: Struct containing variables accessed by shared code
 * @data: Data to send out to the PHY
 * @count: Number of bits to shअगरt out
 *
 * Bits are shअगरted out in MSB to LSB order.
 */
अटल व्योम e1000_shअगरt_out_mdi_bits(काष्ठा e1000_hw *hw, u32 data, u16 count)
अणु
	u32 ctrl;
	u32 mask;

	/* We need to shअगरt "count" number of bits out to the PHY. So, the value
	 * in the "data" parameter will be shअगरted out to the PHY one bit at a
	 * समय. In order to करो this, "data" must be broken करोwn पूर्णांकo bits.
	 */
	mask = 0x01;
	mask <<= (count - 1);

	ctrl = er32(CTRL);

	/* Set MDIO_सूची and MDC_सूची direction bits to be used as output pins. */
	ctrl |= (E1000_CTRL_MDIO_सूची | E1000_CTRL_MDC_सूची);

	जबतक (mask) अणु
		/* A "1" is shअगरted out to the PHY by setting the MDIO bit to
		 * "1" and then raising and lowering the Management Data Clock.
		 * A "0" is shअगरted out to the PHY by setting the MDIO bit to
		 * "0" and then raising and lowering the घड़ी.
		 */
		अगर (data & mask)
			ctrl |= E1000_CTRL_MDIO;
		अन्यथा
			ctrl &= ~E1000_CTRL_MDIO;

		ew32(CTRL, ctrl);
		E1000_WRITE_FLUSH();

		udelay(10);

		e1000_उठाओ_mdi_clk(hw, &ctrl);
		e1000_lower_mdi_clk(hw, &ctrl);

		mask = mask >> 1;
	पूर्ण
पूर्ण

/**
 * e1000_shअगरt_in_mdi_bits - Shअगरts data bits in from the PHY
 * @hw: Struct containing variables accessed by shared code
 *
 * Bits are shअगरted in in MSB to LSB order.
 */
अटल u16 e1000_shअगरt_in_mdi_bits(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	u16 data = 0;
	u8 i;

	/* In order to पढ़ो a रेजिस्टर from the PHY, we need to shअगरt in a total
	 * of 18 bits from the PHY. The first two bit (turnaround) बार are
	 * used to aव्योम contention on the MDIO pin when a पढ़ो operation is
	 * perक्रमmed. These two bits are ignored by us and thrown away. Bits are
	 * "shifted in" by raising the input to the Management Data Clock
	 * (setting the MDC bit), and then पढ़ोing the value of the MDIO bit.
	 */
	ctrl = er32(CTRL);

	/* Clear MDIO_सूची (SWDPIO1) to indicate this bit is to be used as
	 * input.
	 */
	ctrl &= ~E1000_CTRL_MDIO_सूची;
	ctrl &= ~E1000_CTRL_MDIO;

	ew32(CTRL, ctrl);
	E1000_WRITE_FLUSH();

	/* Raise and Lower the घड़ी beक्रमe पढ़ोing in the data. This accounts
	 * क्रम the turnaround bits. The first घड़ी occurred when we घड़ीed out
	 * the last bit of the Register Address.
	 */
	e1000_उठाओ_mdi_clk(hw, &ctrl);
	e1000_lower_mdi_clk(hw, &ctrl);

	क्रम (data = 0, i = 0; i < 16; i++) अणु
		data = data << 1;
		e1000_उठाओ_mdi_clk(hw, &ctrl);
		ctrl = er32(CTRL);
		/* Check to see अगर we shअगरted in a "1". */
		अगर (ctrl & E1000_CTRL_MDIO)
			data |= 1;
		e1000_lower_mdi_clk(hw, &ctrl);
	पूर्ण

	e1000_उठाओ_mdi_clk(hw, &ctrl);
	e1000_lower_mdi_clk(hw, &ctrl);

	वापस data;
पूर्ण

/**
 * e1000_पढ़ो_phy_reg - पढ़ो a phy रेजिस्टर
 * @hw: Struct containing variables accessed by shared code
 * @reg_addr: address of the PHY रेजिस्टर to पढ़ो
 * @phy_data: poपूर्णांकer to the value on the PHY रेजिस्टर
 *
 * Reads the value from a PHY रेजिस्टर, अगर the value is on a specअगरic non zero
 * page, sets the page first.
 */
s32 e1000_पढ़ो_phy_reg(काष्ठा e1000_hw *hw, u32 reg_addr, u16 *phy_data)
अणु
	u32 ret_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&e1000_phy_lock, flags);

	अगर ((hw->phy_type == e1000_phy_igp) &&
	    (reg_addr > MAX_PHY_MULTI_PAGE_REG)) अणु
		ret_val = e1000_ग_लिखो_phy_reg_ex(hw, IGP01E1000_PHY_PAGE_SELECT,
						 (u16) reg_addr);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	ret_val = e1000_पढ़ो_phy_reg_ex(hw, MAX_PHY_REG_ADDRESS & reg_addr,
					phy_data);
out:
	spin_unlock_irqrestore(&e1000_phy_lock, flags);

	वापस ret_val;
पूर्ण

अटल s32 e1000_पढ़ो_phy_reg_ex(काष्ठा e1000_hw *hw, u32 reg_addr,
				 u16 *phy_data)
अणु
	u32 i;
	u32 mdic = 0;
	स्थिर u32 phy_addr = (hw->mac_type == e1000_ce4100) ? hw->phy_addr : 1;

	अगर (reg_addr > MAX_PHY_REG_ADDRESS) अणु
		e_dbg("PHY Address %d is out of range\n", reg_addr);
		वापस -E1000_ERR_PARAM;
	पूर्ण

	अगर (hw->mac_type > e1000_82543) अणु
		/* Set up Op-code, Phy Address, and रेजिस्टर address in the MDI
		 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with
		 * the PHY to retrieve the desired data.
		 */
		अगर (hw->mac_type == e1000_ce4100) अणु
			mdic = ((reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(INTEL_CE_GBE_MDIC_OP_READ) |
				(INTEL_CE_GBE_MDIC_GO));

			ग_लिखोl(mdic, E1000_MDIO_CMD);

			/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो
			 * completed
			 */
			क्रम (i = 0; i < 64; i++) अणु
				udelay(50);
				mdic = पढ़ोl(E1000_MDIO_CMD);
				अगर (!(mdic & INTEL_CE_GBE_MDIC_GO))
					अवरोध;
			पूर्ण

			अगर (mdic & INTEL_CE_GBE_MDIC_GO) अणु
				e_dbg("MDI Read did not complete\n");
				वापस -E1000_ERR_PHY;
			पूर्ण

			mdic = पढ़ोl(E1000_MDIO_STS);
			अगर (mdic & INTEL_CE_GBE_MDIC_READ_ERROR) अणु
				e_dbg("MDI Read Error\n");
				वापस -E1000_ERR_PHY;
			पूर्ण
			*phy_data = (u16)mdic;
		पूर्ण अन्यथा अणु
			mdic = ((reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(E1000_MDIC_OP_READ));

			ew32(MDIC, mdic);

			/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो
			 * completed
			 */
			क्रम (i = 0; i < 64; i++) अणु
				udelay(50);
				mdic = er32(MDIC);
				अगर (mdic & E1000_MDIC_READY)
					अवरोध;
			पूर्ण
			अगर (!(mdic & E1000_MDIC_READY)) अणु
				e_dbg("MDI Read did not complete\n");
				वापस -E1000_ERR_PHY;
			पूर्ण
			अगर (mdic & E1000_MDIC_ERROR) अणु
				e_dbg("MDI Error\n");
				वापस -E1000_ERR_PHY;
			पूर्ण
			*phy_data = (u16)mdic;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We must first send a preamble through the MDIO pin to संकेत
		 * the beginning of an MII inकाष्ठाion.  This is करोne by sending
		 * 32 consecutive "1" bits.
		 */
		e1000_shअगरt_out_mdi_bits(hw, PHY_PREAMBLE, PHY_PREAMBLE_SIZE);

		/* Now combine the next few fields that are required क्रम a पढ़ो
		 * operation.  We use this method instead of calling the
		 * e1000_shअगरt_out_mdi_bits routine five dअगरferent बार. The
		 * क्रमmat of a MII पढ़ो inकाष्ठाion consists of a shअगरt out of
		 * 14 bits and is defined as follows:
		 *    <Preamble><SOF><Op Code><Phy Addr><Reg Addr>
		 * followed by a shअगरt in of 18 bits.  This first two bits
		 * shअगरted in are TurnAround bits used to aव्योम contention on
		 * the MDIO pin when a READ operation is perक्रमmed.  These two
		 * bits are thrown away followed by a shअगरt in of 16 bits which
		 * contains the desired data.
		 */
		mdic = ((reg_addr) | (phy_addr << 5) |
			(PHY_OP_READ << 10) | (PHY_SOF << 12));

		e1000_shअगरt_out_mdi_bits(hw, mdic, 14);

		/* Now that we've shअगरted out the पढ़ो command to the MII, we
		 * need to "shift in" the 16-bit value (18 total bits) of the
		 * requested PHY रेजिस्टर address.
		 */
		*phy_data = e1000_shअगरt_in_mdi_bits(hw);
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_ग_लिखो_phy_reg - ग_लिखो a phy रेजिस्टर
 *
 * @hw: Struct containing variables accessed by shared code
 * @reg_addr: address of the PHY रेजिस्टर to ग_लिखो
 * @phy_data: data to ग_लिखो to the PHY
 *
 * Writes a value to a PHY रेजिस्टर
 */
s32 e1000_ग_लिखो_phy_reg(काष्ठा e1000_hw *hw, u32 reg_addr, u16 phy_data)
अणु
	u32 ret_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&e1000_phy_lock, flags);

	अगर ((hw->phy_type == e1000_phy_igp) &&
	    (reg_addr > MAX_PHY_MULTI_PAGE_REG)) अणु
		ret_val = e1000_ग_लिखो_phy_reg_ex(hw, IGP01E1000_PHY_PAGE_SELECT,
						 (u16)reg_addr);
		अगर (ret_val) अणु
			spin_unlock_irqrestore(&e1000_phy_lock, flags);
			वापस ret_val;
		पूर्ण
	पूर्ण

	ret_val = e1000_ग_लिखो_phy_reg_ex(hw, MAX_PHY_REG_ADDRESS & reg_addr,
					 phy_data);
	spin_unlock_irqrestore(&e1000_phy_lock, flags);

	वापस ret_val;
पूर्ण

अटल s32 e1000_ग_लिखो_phy_reg_ex(काष्ठा e1000_hw *hw, u32 reg_addr,
				  u16 phy_data)
अणु
	u32 i;
	u32 mdic = 0;
	स्थिर u32 phy_addr = (hw->mac_type == e1000_ce4100) ? hw->phy_addr : 1;

	अगर (reg_addr > MAX_PHY_REG_ADDRESS) अणु
		e_dbg("PHY Address %d is out of range\n", reg_addr);
		वापस -E1000_ERR_PARAM;
	पूर्ण

	अगर (hw->mac_type > e1000_82543) अणु
		/* Set up Op-code, Phy Address, रेजिस्टर address, and data
		 * पूर्णांकended क्रम the PHY रेजिस्टर in the MDI Control रेजिस्टर.
		 * The MAC will take care of पूर्णांकerfacing with the PHY to send
		 * the desired data.
		 */
		अगर (hw->mac_type == e1000_ce4100) अणु
			mdic = (((u32)phy_data) |
				(reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(INTEL_CE_GBE_MDIC_OP_WRITE) |
				(INTEL_CE_GBE_MDIC_GO));

			ग_लिखोl(mdic, E1000_MDIO_CMD);

			/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो
			 * completed
			 */
			क्रम (i = 0; i < 640; i++) अणु
				udelay(5);
				mdic = पढ़ोl(E1000_MDIO_CMD);
				अगर (!(mdic & INTEL_CE_GBE_MDIC_GO))
					अवरोध;
			पूर्ण
			अगर (mdic & INTEL_CE_GBE_MDIC_GO) अणु
				e_dbg("MDI Write did not complete\n");
				वापस -E1000_ERR_PHY;
			पूर्ण
		पूर्ण अन्यथा अणु
			mdic = (((u32)phy_data) |
				(reg_addr << E1000_MDIC_REG_SHIFT) |
				(phy_addr << E1000_MDIC_PHY_SHIFT) |
				(E1000_MDIC_OP_WRITE));

			ew32(MDIC, mdic);

			/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो
			 * completed
			 */
			क्रम (i = 0; i < 641; i++) अणु
				udelay(5);
				mdic = er32(MDIC);
				अगर (mdic & E1000_MDIC_READY)
					अवरोध;
			पूर्ण
			अगर (!(mdic & E1000_MDIC_READY)) अणु
				e_dbg("MDI Write did not complete\n");
				वापस -E1000_ERR_PHY;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We'll need to use the SW defined pins to shअगरt the ग_लिखो
		 * command out to the PHY. We first send a preamble to the PHY
		 * to संकेत the beginning of the MII inकाष्ठाion.  This is करोne
		 * by sending 32 consecutive "1" bits.
		 */
		e1000_shअगरt_out_mdi_bits(hw, PHY_PREAMBLE, PHY_PREAMBLE_SIZE);

		/* Now combine the reमुख्यing required fields that will indicate
		 * a ग_लिखो operation. We use this method instead of calling the
		 * e1000_shअगरt_out_mdi_bits routine क्रम each field in the
		 * command. The क्रमmat of a MII ग_लिखो inकाष्ठाion is as follows:
		 * <Preamble><SOF><OpCode><PhyAddr><RegAddr><Turnaround><Data>.
		 */
		mdic = ((PHY_TURNAROUND) | (reg_addr << 2) | (phy_addr << 7) |
			(PHY_OP_WRITE << 12) | (PHY_SOF << 14));
		mdic <<= 16;
		mdic |= (u32)phy_data;

		e1000_shअगरt_out_mdi_bits(hw, mdic, 32);
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_hw_reset - reset the phy, hardware style
 * @hw: Struct containing variables accessed by shared code
 *
 * Returns the PHY to the घातer-on reset state
 */
s32 e1000_phy_hw_reset(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl, ctrl_ext;
	u32 led_ctrl;

	e_dbg("Resetting Phy...\n");

	अगर (hw->mac_type > e1000_82543) अणु
		/* Read the device control रेजिस्टर and निश्चित the
		 * E1000_CTRL_PHY_RST bit. Then, take it out of reset.
		 * For e1000 hardware, we delay क्रम 10ms between the निश्चित
		 * and de-निश्चित.
		 */
		ctrl = er32(CTRL);
		ew32(CTRL, ctrl | E1000_CTRL_PHY_RST);
		E1000_WRITE_FLUSH();

		msleep(10);

		ew32(CTRL, ctrl);
		E1000_WRITE_FLUSH();

	पूर्ण अन्यथा अणु
		/* Read the Extended Device Control Register, निश्चित the
		 * PHY_RESET_सूची bit to put the PHY पूर्णांकo reset. Then, take it
		 * out of reset.
		 */
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_SDP4_सूची;
		ctrl_ext &= ~E1000_CTRL_EXT_SDP4_DATA;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
		msleep(10);
		ctrl_ext |= E1000_CTRL_EXT_SDP4_DATA;
		ew32(CTRL_EXT, ctrl_ext);
		E1000_WRITE_FLUSH();
	पूर्ण
	udelay(150);

	अगर ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) अणु
		/* Configure activity LED after PHY reset */
		led_ctrl = er32(LEDCTL);
		led_ctrl &= IGP_ACTIVITY_LED_MASK;
		led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		ew32(LEDCTL, led_ctrl);
	पूर्ण

	/* Wait क्रम FW to finish PHY configuration. */
	वापस e1000_get_phy_cfg_करोne(hw);
पूर्ण

/**
 * e1000_phy_reset - reset the phy to commit settings
 * @hw: Struct containing variables accessed by shared code
 *
 * Resets the PHY
 * Sets bit 15 of the MII Control रेजिस्टर
 */
s32 e1000_phy_reset(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	चयन (hw->phy_type) अणु
	हाल e1000_phy_igp:
		ret_val = e1000_phy_hw_reset(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	शेष:
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data |= MII_CR_RESET;
		ret_val = e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;

		udelay(1);
		अवरोध;
	पूर्ण

	अगर (hw->phy_type == e1000_phy_igp)
		e1000_phy_init_script(hw);

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_detect_gig_phy - check the phy type
 * @hw: Struct containing variables accessed by shared code
 *
 * Probes the expected PHY address क्रम known PHY IDs
 */
अटल s32 e1000_detect_gig_phy(काष्ठा e1000_hw *hw)
अणु
	s32 phy_init_status, ret_val;
	u16 phy_id_high, phy_id_low;
	bool match = false;

	अगर (hw->phy_id != 0)
		वापस E1000_SUCCESS;

	/* Read the PHY ID Registers to identअगरy which PHY is onboard. */
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_ID1, &phy_id_high);
	अगर (ret_val)
		वापस ret_val;

	hw->phy_id = (u32)(phy_id_high << 16);
	udelay(20);
	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_ID2, &phy_id_low);
	अगर (ret_val)
		वापस ret_val;

	hw->phy_id |= (u32)(phy_id_low & PHY_REVISION_MASK);
	hw->phy_revision = (u32)phy_id_low & ~PHY_REVISION_MASK;

	चयन (hw->mac_type) अणु
	हाल e1000_82543:
		अगर (hw->phy_id == M88E1000_E_PHY_ID)
			match = true;
		अवरोध;
	हाल e1000_82544:
		अगर (hw->phy_id == M88E1000_I_PHY_ID)
			match = true;
		अवरोध;
	हाल e1000_82540:
	हाल e1000_82545:
	हाल e1000_82545_rev_3:
	हाल e1000_82546:
	हाल e1000_82546_rev_3:
		अगर (hw->phy_id == M88E1011_I_PHY_ID)
			match = true;
		अवरोध;
	हाल e1000_ce4100:
		अगर ((hw->phy_id == RTL8211B_PHY_ID) ||
		    (hw->phy_id == RTL8201N_PHY_ID) ||
		    (hw->phy_id == M88E1118_E_PHY_ID))
			match = true;
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
	हाल e1000_82547:
	हाल e1000_82547_rev_2:
		अगर (hw->phy_id == IGP01E1000_I_PHY_ID)
			match = true;
		अवरोध;
	शेष:
		e_dbg("Invalid MAC type %d\n", hw->mac_type);
		वापस -E1000_ERR_CONFIG;
	पूर्ण
	phy_init_status = e1000_set_phy_type(hw);

	अगर ((match) && (phy_init_status == E1000_SUCCESS)) अणु
		e_dbg("PHY ID 0x%X detected\n", hw->phy_id);
		वापस E1000_SUCCESS;
	पूर्ण
	e_dbg("Invalid PHY ID 0x%X\n", hw->phy_id);
	वापस -E1000_ERR_PHY;
पूर्ण

/**
 * e1000_phy_reset_dsp - reset DSP
 * @hw: Struct containing variables accessed by shared code
 *
 * Resets the PHY's DSP
 */
अटल s32 e1000_phy_reset_dsp(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	करो अणु
		ret_val = e1000_ग_लिखो_phy_reg(hw, 29, 0x001d);
		अगर (ret_val)
			अवरोध;
		ret_val = e1000_ग_लिखो_phy_reg(hw, 30, 0x00c1);
		अगर (ret_val)
			अवरोध;
		ret_val = e1000_ग_लिखो_phy_reg(hw, 30, 0x0000);
		अगर (ret_val)
			अवरोध;
		ret_val = E1000_SUCCESS;
	पूर्ण जबतक (0);

	वापस ret_val;
पूर्ण

/**
 * e1000_phy_igp_get_info - get igp specअगरic रेजिस्टरs
 * @hw: Struct containing variables accessed by shared code
 * @phy_info: PHY inक्रमmation काष्ठाure
 *
 * Get PHY inक्रमmation from various PHY रेजिस्टरs क्रम igp PHY only.
 */
अटल s32 e1000_phy_igp_get_info(काष्ठा e1000_hw *hw,
				  काष्ठा e1000_phy_info *phy_info)
अणु
	s32 ret_val;
	u16 phy_data, min_length, max_length, average;
	e1000_rev_polarity polarity;

	/* The करोwnshअगरt status is checked only once, after link is established,
	 * and it stored in the hw->speed_करोwngraded parameter.
	 */
	phy_info->करोwnshअगरt = (e1000_करोwnshअगरt) hw->speed_करोwngraded;

	/* IGP01E1000 करोes not need to support it. */
	phy_info->extended_10bt_distance = e1000_10bt_ext_dist_enable_normal;

	/* IGP01E1000 always correct polarity reversal */
	phy_info->polarity_correction = e1000_polarity_reversal_enabled;

	/* Check polarity status */
	ret_val = e1000_check_polarity(hw, &polarity);
	अगर (ret_val)
		वापस ret_val;

	phy_info->cable_polarity = polarity;

	ret_val = e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_info->mdix_mode =
	    (e1000_स्वतः_x_mode) ((phy_data & IGP01E1000_PSSR_MDIX) >>
				 IGP01E1000_PSSR_MDIX_SHIFT);

	अगर ((phy_data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
		/* Local/Remote Receiver Inक्रमmation are only valid @ 1000
		 * Mbps
		 */
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_info->local_rx = ((phy_data & SR_1000T_LOCAL_RX_STATUS) >>
				      SR_1000T_LOCAL_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
		phy_info->remote_rx = ((phy_data & SR_1000T_REMOTE_RX_STATUS) >>
				       SR_1000T_REMOTE_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

		/* Get cable length */
		ret_val = e1000_get_cable_length(hw, &min_length, &max_length);
		अगर (ret_val)
			वापस ret_val;

		/* Translate to old method */
		average = (max_length + min_length) / 2;

		अगर (average <= e1000_igp_cable_length_50)
			phy_info->cable_length = e1000_cable_length_50;
		अन्यथा अगर (average <= e1000_igp_cable_length_80)
			phy_info->cable_length = e1000_cable_length_50_80;
		अन्यथा अगर (average <= e1000_igp_cable_length_110)
			phy_info->cable_length = e1000_cable_length_80_110;
		अन्यथा अगर (average <= e1000_igp_cable_length_140)
			phy_info->cable_length = e1000_cable_length_110_140;
		अन्यथा
			phy_info->cable_length = e1000_cable_length_140;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_m88_get_info - get m88 specअगरic रेजिस्टरs
 * @hw: Struct containing variables accessed by shared code
 * @phy_info: PHY inक्रमmation काष्ठाure
 *
 * Get PHY inक्रमmation from various PHY रेजिस्टरs क्रम m88 PHY only.
 */
अटल s32 e1000_phy_m88_get_info(काष्ठा e1000_hw *hw,
				  काष्ठा e1000_phy_info *phy_info)
अणु
	s32 ret_val;
	u16 phy_data;
	e1000_rev_polarity polarity;

	/* The करोwnshअगरt status is checked only once, after link is established,
	 * and it stored in the hw->speed_करोwngraded parameter.
	 */
	phy_info->करोwnshअगरt = (e1000_करोwnshअगरt) hw->speed_करोwngraded;

	ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_info->extended_10bt_distance =
	    ((phy_data & M88E1000_PSCR_10BT_EXT_DIST_ENABLE) >>
	     M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT) ?
	    e1000_10bt_ext_dist_enable_lower :
	    e1000_10bt_ext_dist_enable_normal;

	phy_info->polarity_correction =
	    ((phy_data & M88E1000_PSCR_POLARITY_REVERSAL) >>
	     M88E1000_PSCR_POLARITY_REVERSAL_SHIFT) ?
	    e1000_polarity_reversal_disabled : e1000_polarity_reversal_enabled;

	/* Check polarity status */
	ret_val = e1000_check_polarity(hw, &polarity);
	अगर (ret_val)
		वापस ret_val;
	phy_info->cable_polarity = polarity;

	ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_info->mdix_mode =
	    (e1000_स्वतः_x_mode) ((phy_data & M88E1000_PSSR_MDIX) >>
				 M88E1000_PSSR_MDIX_SHIFT);

	अगर ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS) अणु
		/* Cable Length Estimation and Local/Remote Receiver Inक्रमmation
		 * are only valid at 1000 Mbps.
		 */
		phy_info->cable_length =
		    (e1000_cable_length) ((phy_data &
					   M88E1000_PSSR_CABLE_LENGTH) >>
					  M88E1000_PSSR_CABLE_LENGTH_SHIFT);

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_info->local_rx = ((phy_data & SR_1000T_LOCAL_RX_STATUS) >>
				      SR_1000T_LOCAL_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
		phy_info->remote_rx = ((phy_data & SR_1000T_REMOTE_RX_STATUS) >>
				       SR_1000T_REMOTE_RX_STATUS_SHIFT) ?
		    e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_phy_get_info - request phy info
 * @hw: Struct containing variables accessed by shared code
 * @phy_info: PHY inक्रमmation काष्ठाure
 *
 * Get PHY inक्रमmation from various PHY रेजिस्टरs
 */
s32 e1000_phy_get_info(काष्ठा e1000_hw *hw, काष्ठा e1000_phy_info *phy_info)
अणु
	s32 ret_val;
	u16 phy_data;

	phy_info->cable_length = e1000_cable_length_undefined;
	phy_info->extended_10bt_distance = e1000_10bt_ext_dist_enable_undefined;
	phy_info->cable_polarity = e1000_rev_polarity_undefined;
	phy_info->करोwnshअगरt = e1000_करोwnshअगरt_undefined;
	phy_info->polarity_correction = e1000_polarity_reversal_undefined;
	phy_info->mdix_mode = e1000_स्वतः_x_mode_undefined;
	phy_info->local_rx = e1000_1000t_rx_status_undefined;
	phy_info->remote_rx = e1000_1000t_rx_status_undefined;

	अगर (hw->media_type != e1000_media_type_copper) अणु
		e_dbg("PHY info is only valid for copper media\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर ((phy_data & MII_SR_LINK_STATUS) != MII_SR_LINK_STATUS) अणु
		e_dbg("PHY info is only valid if link is up\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	अगर (hw->phy_type == e1000_phy_igp)
		वापस e1000_phy_igp_get_info(hw, phy_info);
	अन्यथा अगर ((hw->phy_type == e1000_phy_8211) ||
		 (hw->phy_type == e1000_phy_8201))
		वापस E1000_SUCCESS;
	अन्यथा
		वापस e1000_phy_m88_get_info(hw, phy_info);
पूर्ण

s32 e1000_validate_mdi_setting(काष्ठा e1000_hw *hw)
अणु
	अगर (!hw->स्वतःneg && (hw->mdix == 0 || hw->mdix == 3)) अणु
		e_dbg("Invalid MDI setting detected\n");
		hw->mdix = 1;
		वापस -E1000_ERR_CONFIG;
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_init_eeprom_params - initialize sw eeprom vars
 * @hw: Struct containing variables accessed by shared code
 *
 * Sets up eeprom variables in the hw काष्ठा.  Must be called after mac_type
 * is configured.
 */
s32 e1000_init_eeprom_params(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd = er32(EECD);
	s32 ret_val = E1000_SUCCESS;
	u16 eeprom_size;

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
	हाल e1000_82544:
		eeprom->type = e1000_eeprom_microwire;
		eeprom->word_size = 64;
		eeprom->opcode_bits = 3;
		eeprom->address_bits = 6;
		eeprom->delay_usec = 50;
		अवरोध;
	हाल e1000_82540:
	हाल e1000_82545:
	हाल e1000_82545_rev_3:
	हाल e1000_82546:
	हाल e1000_82546_rev_3:
		eeprom->type = e1000_eeprom_microwire;
		eeprom->opcode_bits = 3;
		eeprom->delay_usec = 50;
		अगर (eecd & E1000_EECD_SIZE) अणु
			eeprom->word_size = 256;
			eeprom->address_bits = 8;
		पूर्ण अन्यथा अणु
			eeprom->word_size = 64;
			eeprom->address_bits = 6;
		पूर्ण
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
	हाल e1000_82547:
	हाल e1000_82547_rev_2:
		अगर (eecd & E1000_EECD_TYPE) अणु
			eeprom->type = e1000_eeprom_spi;
			eeprom->opcode_bits = 8;
			eeprom->delay_usec = 1;
			अगर (eecd & E1000_EECD_ADDR_BITS) अणु
				eeprom->page_size = 32;
				eeprom->address_bits = 16;
			पूर्ण अन्यथा अणु
				eeprom->page_size = 8;
				eeprom->address_bits = 8;
			पूर्ण
		पूर्ण अन्यथा अणु
			eeprom->type = e1000_eeprom_microwire;
			eeprom->opcode_bits = 3;
			eeprom->delay_usec = 50;
			अगर (eecd & E1000_EECD_ADDR_BITS) अणु
				eeprom->word_size = 256;
				eeprom->address_bits = 8;
			पूर्ण अन्यथा अणु
				eeprom->word_size = 64;
				eeprom->address_bits = 6;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (eeprom->type == e1000_eeprom_spi) अणु
		/* eeprom_size will be an क्रमागत [0..8] that maps to eeprom sizes
		 * 128B to 32KB (incremented by घातers of 2).
		 */
		/* Set to शेष value क्रम initial eeprom पढ़ो. */
		eeprom->word_size = 64;
		ret_val = e1000_पढ़ो_eeprom(hw, EEPROM_CFG, 1, &eeprom_size);
		अगर (ret_val)
			वापस ret_val;
		eeprom_size =
		    (eeprom_size & EEPROM_SIZE_MASK) >> EEPROM_SIZE_SHIFT;
		/* 256B eeprom size was not supported in earlier hardware, so we
		 * bump eeprom_size up one to ensure that "1" (which maps to
		 * 256B) is never the result used in the shअगरting logic below.
		 */
		अगर (eeprom_size)
			eeprom_size++;

		eeprom->word_size = 1 << (eeprom_size + EEPROM_WORD_SIZE_SHIFT);
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 * e1000_उठाओ_ee_clk - Raises the EEPROM's घड़ी input.
 * @hw: Struct containing variables accessed by shared code
 * @eecd: EECD's current value
 */
अटल व्योम e1000_उठाओ_ee_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	/* Raise the घड़ी input to the EEPROM (by setting the SK bit), and then
	 * रुको <delay> microseconds.
	 */
	*eecd = *eecd | E1000_EECD_SK;
	ew32(EECD, *eecd);
	E1000_WRITE_FLUSH();
	udelay(hw->eeprom.delay_usec);
पूर्ण

/**
 * e1000_lower_ee_clk - Lowers the EEPROM's घड़ी input.
 * @hw: Struct containing variables accessed by shared code
 * @eecd: EECD's current value
 */
अटल व्योम e1000_lower_ee_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	/* Lower the घड़ी input to the EEPROM (by clearing the SK bit), and
	 * then रुको 50 microseconds.
	 */
	*eecd = *eecd & ~E1000_EECD_SK;
	ew32(EECD, *eecd);
	E1000_WRITE_FLUSH();
	udelay(hw->eeprom.delay_usec);
पूर्ण

/**
 * e1000_shअगरt_out_ee_bits - Shअगरt data bits out to the EEPROM.
 * @hw: Struct containing variables accessed by shared code
 * @data: data to send to the EEPROM
 * @count: number of bits to shअगरt out
 */
अटल व्योम e1000_shअगरt_out_ee_bits(काष्ठा e1000_hw *hw, u16 data, u16 count)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd;
	u32 mask;

	/* We need to shअगरt "count" bits out to the EEPROM. So, value in the
	 * "data" parameter will be shअगरted out to the EEPROM one bit at a समय.
	 * In order to करो this, "data" must be broken करोwn पूर्णांकo bits.
	 */
	mask = 0x01 << (count - 1);
	eecd = er32(EECD);
	अगर (eeprom->type == e1000_eeprom_microwire)
		eecd &= ~E1000_EECD_DO;
	अन्यथा अगर (eeprom->type == e1000_eeprom_spi)
		eecd |= E1000_EECD_DO;

	करो अणु
		/* A "1" is shअगरted out to the EEPROM by setting bit "DI" to a
		 * "1", and then raising and then lowering the घड़ी (the SK bit
		 * controls the घड़ी input to the EEPROM).  A "0" is shअगरted
		 * out to the EEPROM by setting "DI" to "0" and then raising and
		 * then lowering the घड़ी.
		 */
		eecd &= ~E1000_EECD_DI;

		अगर (data & mask)
			eecd |= E1000_EECD_DI;

		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();

		udelay(eeprom->delay_usec);

		e1000_उठाओ_ee_clk(hw, &eecd);
		e1000_lower_ee_clk(hw, &eecd);

		mask = mask >> 1;

	पूर्ण जबतक (mask);

	/* We leave the "DI" bit set to "0" when we leave this routine. */
	eecd &= ~E1000_EECD_DI;
	ew32(EECD, eecd);
पूर्ण

/**
 * e1000_shअगरt_in_ee_bits - Shअगरt data bits in from the EEPROM
 * @hw: Struct containing variables accessed by shared code
 * @count: number of bits to shअगरt in
 */
अटल u16 e1000_shअगरt_in_ee_bits(काष्ठा e1000_hw *hw, u16 count)
अणु
	u32 eecd;
	u32 i;
	u16 data;

	/* In order to पढ़ो a रेजिस्टर from the EEPROM, we need to shअगरt 'count'
	 * bits in from the EEPROM. Bits are "shifted in" by raising the घड़ी
	 * input to the EEPROM (setting the SK bit), and then पढ़ोing the value
	 * of the "DO" bit.  During this "shifting in" process the "DI" bit
	 * should always be clear.
	 */

	eecd = er32(EECD);

	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	क्रम (i = 0; i < count; i++) अणु
		data = data << 1;
		e1000_उठाओ_ee_clk(hw, &eecd);

		eecd = er32(EECD);

		eecd &= ~(E1000_EECD_DI);
		अगर (eecd & E1000_EECD_DO)
			data |= 1;

		e1000_lower_ee_clk(hw, &eecd);
	पूर्ण

	वापस data;
पूर्ण

/**
 * e1000_acquire_eeprom - Prepares EEPROM क्रम access
 * @hw: Struct containing variables accessed by shared code
 *
 * Lowers EEPROM घड़ी. Clears input pin. Sets the chip select pin. This
 * function should be called beक्रमe issuing a command to the EEPROM.
 */
अटल s32 e1000_acquire_eeprom(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd, i = 0;

	eecd = er32(EECD);

	/* Request EEPROM Access */
	अगर (hw->mac_type > e1000_82544) अणु
		eecd |= E1000_EECD_REQ;
		ew32(EECD, eecd);
		eecd = er32(EECD);
		जबतक ((!(eecd & E1000_EECD_GNT)) &&
		       (i < E1000_EEPROM_GRANT_ATTEMPTS)) अणु
			i++;
			udelay(5);
			eecd = er32(EECD);
		पूर्ण
		अगर (!(eecd & E1000_EECD_GNT)) अणु
			eecd &= ~E1000_EECD_REQ;
			ew32(EECD, eecd);
			e_dbg("Could not acquire EEPROM grant\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
	पूर्ण

	/* Setup EEPROM क्रम Read/Write */

	अगर (eeprom->type == e1000_eeprom_microwire) अणु
		/* Clear SK and DI */
		eecd &= ~(E1000_EECD_DI | E1000_EECD_SK);
		ew32(EECD, eecd);

		/* Set CS */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
	पूर्ण अन्यथा अगर (eeprom->type == e1000_eeprom_spi) अणु
		/* Clear SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(1);
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_standby_eeprom - Returns EEPROM to a "standby" state
 * @hw: Struct containing variables accessed by shared code
 */
अटल व्योम e1000_standby_eeprom(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd;

	eecd = er32(EECD);

	अगर (eeprom->type == e1000_eeprom_microwire) अणु
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Clock high */
		eecd |= E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Select EEPROM */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);

		/* Clock low */
		eecd &= ~E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
	पूर्ण अन्यथा अगर (eeprom->type == e1000_eeprom_spi) अणु
		/* Toggle CS to flush commands */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
		eecd &= ~E1000_EECD_CS;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(eeprom->delay_usec);
	पूर्ण
पूर्ण

/**
 * e1000_release_eeprom - drop chip select
 * @hw: Struct containing variables accessed by shared code
 *
 * Terminates a command by inverting the EEPROM's chip select pin
 */
अटल व्योम e1000_release_eeprom(काष्ठा e1000_hw *hw)
अणु
	u32 eecd;

	eecd = er32(EECD);

	अगर (hw->eeprom.type == e1000_eeprom_spi) अणु
		eecd |= E1000_EECD_CS;	/* Pull CS high */
		eecd &= ~E1000_EECD_SK;	/* Lower SCK */

		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();

		udelay(hw->eeprom.delay_usec);
	पूर्ण अन्यथा अगर (hw->eeprom.type == e1000_eeprom_microwire) अणु
		/* cleanup eeprom */

		/* CS on Microwire is active-high */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_DI);

		ew32(EECD, eecd);

		/* Rising edge of घड़ी */
		eecd |= E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(hw->eeprom.delay_usec);

		/* Falling edge of घड़ी */
		eecd &= ~E1000_EECD_SK;
		ew32(EECD, eecd);
		E1000_WRITE_FLUSH();
		udelay(hw->eeprom.delay_usec);
	पूर्ण

	/* Stop requesting EEPROM access */
	अगर (hw->mac_type > e1000_82544) अणु
		eecd &= ~E1000_EECD_REQ;
		ew32(EECD, eecd);
	पूर्ण
पूर्ण

/**
 * e1000_spi_eeprom_पढ़ोy - Reads a 16 bit word from the EEPROM.
 * @hw: Struct containing variables accessed by shared code
 */
अटल s32 e1000_spi_eeprom_पढ़ोy(काष्ठा e1000_hw *hw)
अणु
	u16 retry_count = 0;
	u8 spi_stat_reg;

	/* Read "Status Register" repeatedly until the LSB is cleared.  The
	 * EEPROM will संकेत that the command has been completed by clearing
	 * bit 0 of the पूर्णांकernal status रेजिस्टर.  If it's not cleared within
	 * 5 milliseconds, then error out.
	 */
	retry_count = 0;
	करो अणु
		e1000_shअगरt_out_ee_bits(hw, EEPROM_RDSR_OPCODE_SPI,
					hw->eeprom.opcode_bits);
		spi_stat_reg = (u8)e1000_shअगरt_in_ee_bits(hw, 8);
		अगर (!(spi_stat_reg & EEPROM_STATUS_RDY_SPI))
			अवरोध;

		udelay(5);
		retry_count += 5;

		e1000_standby_eeprom(hw);
	पूर्ण जबतक (retry_count < EEPROM_MAX_RETRY_SPI);

	/* ATMEL SPI ग_लिखो समय could vary from 0-20mSec on 3.3V devices (and
	 * only 0-5mSec on 5V devices)
	 */
	अगर (retry_count >= EEPROM_MAX_RETRY_SPI) अणु
		e_dbg("SPI EEPROM Status error\n");
		वापस -E1000_ERR_EEPROM;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_पढ़ो_eeprom - Reads a 16 bit word from the EEPROM.
 * @hw: Struct containing variables accessed by shared code
 * @offset: offset of  word in the EEPROM to पढ़ो
 * @data: word पढ़ो from the EEPROM
 * @words: number of words to पढ़ो
 */
s32 e1000_पढ़ो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	s32 ret;

	mutex_lock(&e1000_eeprom_lock);
	ret = e1000_करो_पढ़ो_eeprom(hw, offset, words, data);
	mutex_unlock(&e1000_eeprom_lock);
	वापस ret;
पूर्ण

अटल s32 e1000_करो_पढ़ो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				u16 *data)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 i = 0;

	अगर (hw->mac_type == e1000_ce4100) अणु
		GBE_CONFIG_FLASH_READ(GBE_CONFIG_BASE_VIRT, offset, words,
				      data);
		वापस E1000_SUCCESS;
	पूर्ण

	/* A check क्रम invalid values:  offset too large, too many words, and
	 * not enough words.
	 */
	अगर ((offset >= eeprom->word_size) ||
	    (words > eeprom->word_size - offset) ||
	    (words == 0)) अणु
		e_dbg("\"words\" parameter out of bounds. Words = %d,"
		      "size = %d\n", offset, eeprom->word_size);
		वापस -E1000_ERR_EEPROM;
	पूर्ण

	/* EEPROM's that don't use EERD to पढ़ो require us to bit-bang the SPI
	 * directly. In this हाल, we need to acquire the EEPROM so that
	 * FW or other port software करोes not पूर्णांकerrupt.
	 */
	/* Prepare the EEPROM क्रम bit-bang पढ़ोing */
	अगर (e1000_acquire_eeprom(hw) != E1000_SUCCESS)
		वापस -E1000_ERR_EEPROM;

	/* Set up the SPI or Microwire EEPROM क्रम bit-bang पढ़ोing.  We have
	 * acquired the EEPROM at this poपूर्णांक, so any वापसs should release it
	 */
	अगर (eeprom->type == e1000_eeprom_spi) अणु
		u16 word_in;
		u8 पढ़ो_opcode = EEPROM_READ_OPCODE_SPI;

		अगर (e1000_spi_eeprom_पढ़ोy(hw)) अणु
			e1000_release_eeprom(hw);
			वापस -E1000_ERR_EEPROM;
		पूर्ण

		e1000_standby_eeprom(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		अगर ((eeprom->address_bits == 8) && (offset >= 128))
			पढ़ो_opcode |= EEPROM_A8_OPCODE_SPI;

		/* Send the READ command (opcode + addr)  */
		e1000_shअगरt_out_ee_bits(hw, पढ़ो_opcode, eeprom->opcode_bits);
		e1000_shअगरt_out_ee_bits(hw, (u16)(offset * 2),
					eeprom->address_bits);

		/* Read the data.  The address of the eeprom पूर्णांकernally
		 * increments with each byte (spi) being पढ़ो, saving on the
		 * overhead of eeprom setup and tear-करोwn.  The address counter
		 * will roll over अगर पढ़ोing beyond the size of the eeprom, thus
		 * allowing the entire memory to be पढ़ो starting from any
		 * offset.
		 */
		क्रम (i = 0; i < words; i++) अणु
			word_in = e1000_shअगरt_in_ee_bits(hw, 16);
			data[i] = (word_in >> 8) | (word_in << 8);
		पूर्ण
	पूर्ण अन्यथा अगर (eeprom->type == e1000_eeprom_microwire) अणु
		क्रम (i = 0; i < words; i++) अणु
			/* Send the READ command (opcode + addr)  */
			e1000_shअगरt_out_ee_bits(hw,
						EEPROM_READ_OPCODE_MICROWIRE,
						eeprom->opcode_bits);
			e1000_shअगरt_out_ee_bits(hw, (u16)(offset + i),
						eeprom->address_bits);

			/* Read the data.  For microwire, each word requires the
			 * overhead of eeprom setup and tear-करोwn.
			 */
			data[i] = e1000_shअगरt_in_ee_bits(hw, 16);
			e1000_standby_eeprom(hw);
			cond_resched();
		पूर्ण
	पूर्ण

	/* End this पढ़ो operation */
	e1000_release_eeprom(hw);

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_validate_eeprom_checksum - Verअगरies that the EEPROM has a valid checksum
 * @hw: Struct containing variables accessed by shared code
 *
 * Reads the first 64 16 bit words of the EEPROM and sums the values पढ़ो.
 * If the sum of the 64 16 bit words is 0xBABA, the EEPROM's checksum is
 * valid.
 */
s32 e1000_validate_eeprom_checksum(काष्ठा e1000_hw *hw)
अणु
	u16 checksum = 0;
	u16 i, eeprom_data;

	क्रम (i = 0; i < (EEPROM_CHECKSUM_REG + 1); i++) अणु
		अगर (e1000_पढ़ो_eeprom(hw, i, 1, &eeprom_data) < 0) अणु
			e_dbg("EEPROM Read Error\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
		checksum += eeprom_data;
	पूर्ण

#अगर_घोषित CONFIG_PARISC
	/* This is a signature and not a checksum on HP c8000 */
	अगर ((hw->subप्रणाली_venकरोr_id == 0x103C) && (eeprom_data == 0x16d6))
		वापस E1000_SUCCESS;

#पूर्ण_अगर
	अगर (checksum == (u16)EEPROM_SUM)
		वापस E1000_SUCCESS;
	अन्यथा अणु
		e_dbg("EEPROM Checksum Invalid\n");
		वापस -E1000_ERR_EEPROM;
	पूर्ण
पूर्ण

/**
 * e1000_update_eeprom_checksum - Calculates/ग_लिखोs the EEPROM checksum
 * @hw: Struct containing variables accessed by shared code
 *
 * Sums the first 63 16 bit words of the EEPROM. Subtracts the sum from 0xBABA.
 * Writes the dअगरference to word offset 63 of the EEPROM.
 */
s32 e1000_update_eeprom_checksum(काष्ठा e1000_hw *hw)
अणु
	u16 checksum = 0;
	u16 i, eeprom_data;

	क्रम (i = 0; i < EEPROM_CHECKSUM_REG; i++) अणु
		अगर (e1000_पढ़ो_eeprom(hw, i, 1, &eeprom_data) < 0) अणु
			e_dbg("EEPROM Read Error\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
		checksum += eeprom_data;
	पूर्ण
	checksum = (u16)EEPROM_SUM - checksum;
	अगर (e1000_ग_लिखो_eeprom(hw, EEPROM_CHECKSUM_REG, 1, &checksum) < 0) अणु
		e_dbg("EEPROM Write Error\n");
		वापस -E1000_ERR_EEPROM;
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_ग_लिखो_eeprom - ग_लिखो words to the dअगरferent EEPROM types.
 * @hw: Struct containing variables accessed by shared code
 * @offset: offset within the EEPROM to be written to
 * @words: number of words to ग_लिखो
 * @data: 16 bit word to be written to the EEPROM
 *
 * If e1000_update_eeprom_checksum is not called after this function, the
 * EEPROM will most likely contain an invalid checksum.
 */
s32 e1000_ग_लिखो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	s32 ret;

	mutex_lock(&e1000_eeprom_lock);
	ret = e1000_करो_ग_लिखो_eeprom(hw, offset, words, data);
	mutex_unlock(&e1000_eeprom_lock);
	वापस ret;
पूर्ण

अटल s32 e1000_करो_ग_लिखो_eeprom(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				 u16 *data)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	s32 status = 0;

	अगर (hw->mac_type == e1000_ce4100) अणु
		GBE_CONFIG_FLASH_WRITE(GBE_CONFIG_BASE_VIRT, offset, words,
				       data);
		वापस E1000_SUCCESS;
	पूर्ण

	/* A check क्रम invalid values:  offset too large, too many words, and
	 * not enough words.
	 */
	अगर ((offset >= eeprom->word_size) ||
	    (words > eeprom->word_size - offset) ||
	    (words == 0)) अणु
		e_dbg("\"words\" parameter out of bounds\n");
		वापस -E1000_ERR_EEPROM;
	पूर्ण

	/* Prepare the EEPROM क्रम writing  */
	अगर (e1000_acquire_eeprom(hw) != E1000_SUCCESS)
		वापस -E1000_ERR_EEPROM;

	अगर (eeprom->type == e1000_eeprom_microwire) अणु
		status = e1000_ग_लिखो_eeprom_microwire(hw, offset, words, data);
	पूर्ण अन्यथा अणु
		status = e1000_ग_लिखो_eeprom_spi(hw, offset, words, data);
		msleep(10);
	पूर्ण

	/* Done with writing */
	e1000_release_eeprom(hw);

	वापस status;
पूर्ण

/**
 * e1000_ग_लिखो_eeprom_spi - Writes a 16 bit word to a given offset in an SPI EEPROM.
 * @hw: Struct containing variables accessed by shared code
 * @offset: offset within the EEPROM to be written to
 * @words: number of words to ग_लिखो
 * @data: poपूर्णांकer to array of 8 bit words to be written to the EEPROM
 */
अटल s32 e1000_ग_लिखो_eeprom_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				  u16 *data)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u16 widx = 0;

	जबतक (widx < words) अणु
		u8 ग_लिखो_opcode = EEPROM_WRITE_OPCODE_SPI;

		अगर (e1000_spi_eeprom_पढ़ोy(hw))
			वापस -E1000_ERR_EEPROM;

		e1000_standby_eeprom(hw);
		cond_resched();

		/*  Send the WRITE ENABLE command (8 bit opcode )  */
		e1000_shअगरt_out_ee_bits(hw, EEPROM_WREN_OPCODE_SPI,
					eeprom->opcode_bits);

		e1000_standby_eeprom(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		अगर ((eeprom->address_bits == 8) && (offset >= 128))
			ग_लिखो_opcode |= EEPROM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		e1000_shअगरt_out_ee_bits(hw, ग_लिखो_opcode, eeprom->opcode_bits);

		e1000_shअगरt_out_ee_bits(hw, (u16)((offset + widx) * 2),
					eeprom->address_bits);

		/* Send the data */

		/* Loop to allow क्रम up to whole page ग_लिखो (32 bytes) of
		 * eeprom
		 */
		जबतक (widx < words) अणु
			u16 word_out = data[widx];

			word_out = (word_out >> 8) | (word_out << 8);
			e1000_shअगरt_out_ee_bits(hw, word_out, 16);
			widx++;

			/* Some larger eeprom sizes are capable of a 32-byte
			 * PAGE WRITE operation, जबतक the smaller eeproms are
			 * capable of an 8-byte PAGE WRITE operation.  Break the
			 * inner loop to pass new address
			 */
			अगर ((((offset + widx) * 2) % eeprom->page_size) == 0) अणु
				e1000_standby_eeprom(hw);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_ग_लिखो_eeprom_microwire - Writes a 16 bit word to a given offset in a Microwire EEPROM.
 * @hw: Struct containing variables accessed by shared code
 * @offset: offset within the EEPROM to be written to
 * @words: number of words to ग_लिखो
 * @data: poपूर्णांकer to array of 8 bit words to be written to the EEPROM
 */
अटल s32 e1000_ग_लिखो_eeprom_microwire(काष्ठा e1000_hw *hw, u16 offset,
					u16 words, u16 *data)
अणु
	काष्ठा e1000_eeprom_info *eeprom = &hw->eeprom;
	u32 eecd;
	u16 words_written = 0;
	u16 i = 0;

	/* Send the ग_लिखो enable command to the EEPROM (3-bit opcode plus
	 * 6/8-bit dummy address beginning with 11).  It's less work to include
	 * the 11 of the dummy address as part of the opcode than it is to shअगरt
	 * it over the correct number of bits क्रम the address.  This माला_दो the
	 * EEPROM पूर्णांकo ग_लिखो/erase mode.
	 */
	e1000_shअगरt_out_ee_bits(hw, EEPROM_EWEN_OPCODE_MICROWIRE,
				(u16)(eeprom->opcode_bits + 2));

	e1000_shअगरt_out_ee_bits(hw, 0, (u16)(eeprom->address_bits - 2));

	/* Prepare the EEPROM */
	e1000_standby_eeprom(hw);

	जबतक (words_written < words) अणु
		/* Send the Write command (3-bit opcode + addr) */
		e1000_shअगरt_out_ee_bits(hw, EEPROM_WRITE_OPCODE_MICROWIRE,
					eeprom->opcode_bits);

		e1000_shअगरt_out_ee_bits(hw, (u16)(offset + words_written),
					eeprom->address_bits);

		/* Send the data */
		e1000_shअगरt_out_ee_bits(hw, data[words_written], 16);

		/* Toggle the CS line.  This in effect tells the EEPROM to
		 * execute the previous command.
		 */
		e1000_standby_eeprom(hw);

		/* Read DO repeatedly until it is high (equal to '1').  The
		 * EEPROM will संकेत that the command has been completed by
		 * raising the DO संकेत. If DO करोes not go high in 10
		 * milliseconds, then error out.
		 */
		क्रम (i = 0; i < 200; i++) अणु
			eecd = er32(EECD);
			अगर (eecd & E1000_EECD_DO)
				अवरोध;
			udelay(50);
		पूर्ण
		अगर (i == 200) अणु
			e_dbg("EEPROM Write did not complete\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण

		/* Recover from ग_लिखो */
		e1000_standby_eeprom(hw);
		cond_resched();

		words_written++;
	पूर्ण

	/* Send the ग_लिखो disable command to the EEPROM (3-bit opcode plus
	 * 6/8-bit dummy address beginning with 10).  It's less work to include
	 * the 10 of the dummy address as part of the opcode than it is to shअगरt
	 * it over the correct number of bits क्रम the address.  This takes the
	 * EEPROM out of ग_लिखो/erase mode.
	 */
	e1000_shअगरt_out_ee_bits(hw, EEPROM_EWDS_OPCODE_MICROWIRE,
				(u16)(eeprom->opcode_bits + 2));

	e1000_shअगरt_out_ee_bits(hw, 0, (u16)(eeprom->address_bits - 2));

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_पढ़ो_mac_addr - पढ़ो the adapters MAC from eeprom
 * @hw: Struct containing variables accessed by shared code
 *
 * Reads the adapter's MAC address from the EEPROM and inverts the LSB क्रम the
 * second function of dual function devices
 */
s32 e1000_पढ़ो_mac_addr(काष्ठा e1000_hw *hw)
अणु
	u16 offset;
	u16 eeprom_data, i;

	क्रम (i = 0; i < NODE_ADDRESS_SIZE; i += 2) अणु
		offset = i >> 1;
		अगर (e1000_पढ़ो_eeprom(hw, offset, 1, &eeprom_data) < 0) अणु
			e_dbg("EEPROM Read Error\n");
			वापस -E1000_ERR_EEPROM;
		पूर्ण
		hw->perm_mac_addr[i] = (u8)(eeprom_data & 0x00FF);
		hw->perm_mac_addr[i + 1] = (u8)(eeprom_data >> 8);
	पूर्ण

	चयन (hw->mac_type) अणु
	शेष:
		अवरोध;
	हाल e1000_82546:
	हाल e1000_82546_rev_3:
		अगर (er32(STATUS) & E1000_STATUS_FUNC_1)
			hw->perm_mac_addr[5] ^= 0x01;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < NODE_ADDRESS_SIZE; i++)
		hw->mac_addr[i] = hw->perm_mac_addr[i];
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_init_rx_addrs - Initializes receive address filters.
 * @hw: Struct containing variables accessed by shared code
 *
 * Places the MAC address in receive address रेजिस्टर 0 and clears the rest
 * of the receive address रेजिस्टरs. Clears the multicast table. Assumes
 * the receiver is in reset when the routine is called.
 */
अटल व्योम e1000_init_rx_addrs(काष्ठा e1000_hw *hw)
अणु
	u32 i;
	u32 rar_num;

	/* Setup the receive address. */
	e_dbg("Programming MAC Address into RAR[0]\n");

	e1000_rar_set(hw, hw->mac_addr, 0);

	rar_num = E1000_RAR_ENTRIES;

	/* Zero out the following 14 receive addresses. RAR[15] is क्रम
	 * manageability
	 */
	e_dbg("Clearing RAR[1-14]\n");
	क्रम (i = 1; i < rar_num; i++) अणु
		E1000_WRITE_REG_ARRAY(hw, RA, (i << 1), 0);
		E1000_WRITE_FLUSH();
		E1000_WRITE_REG_ARRAY(hw, RA, ((i << 1) + 1), 0);
		E1000_WRITE_FLUSH();
	पूर्ण
पूर्ण

/**
 * e1000_hash_mc_addr - Hashes an address to determine its location in the multicast table
 * @hw: Struct containing variables accessed by shared code
 * @mc_addr: the multicast address to hash
 */
u32 e1000_hash_mc_addr(काष्ठा e1000_hw *hw, u8 *mc_addr)
अणु
	u32 hash_value = 0;

	/* The portion of the address that is used क्रम the hash table is
	 * determined by the mc_filter_type setting.
	 */
	चयन (hw->mc_filter_type) अणु
		/* [0] [1] [2] [3] [4] [5]
		 * 01  AA  00  12  34  56
		 * LSB                 MSB
		 */
	हाल 0:
		/* [47:36] i.e. 0x563 क्रम above example address */
		hash_value = ((mc_addr[4] >> 4) | (((u16)mc_addr[5]) << 4));
		अवरोध;
	हाल 1:
		/* [46:35] i.e. 0xAC6 क्रम above example address */
		hash_value = ((mc_addr[4] >> 3) | (((u16)mc_addr[5]) << 5));
		अवरोध;
	हाल 2:
		/* [45:34] i.e. 0x5D8 क्रम above example address */
		hash_value = ((mc_addr[4] >> 2) | (((u16)mc_addr[5]) << 6));
		अवरोध;
	हाल 3:
		/* [43:32] i.e. 0x634 क्रम above example address */
		hash_value = ((mc_addr[4]) | (((u16)mc_addr[5]) << 8));
		अवरोध;
	पूर्ण

	hash_value &= 0xFFF;
	वापस hash_value;
पूर्ण

/**
 * e1000_rar_set - Puts an ethernet address पूर्णांकo a receive address रेजिस्टर.
 * @hw: Struct containing variables accessed by shared code
 * @addr: Address to put पूर्णांकo receive address रेजिस्टर
 * @index: Receive address रेजिस्टर to ग_लिखो
 */
व्योम e1000_rar_set(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
अणु
	u32 rar_low, rar_high;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] | ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) | ((u32)addr[3] << 24));
	rar_high = ((u32)addr[4] | ((u32)addr[5] << 8));

	/* Disable Rx and flush all Rx frames beक्रमe enabling RSS to aव्योम Rx
	 * unit hang.
	 *
	 * Description:
	 * If there are any Rx frames queued up or otherwise present in the HW
	 * beक्रमe RSS is enabled, and then we enable RSS, the HW Rx unit will
	 * hang.  To work around this issue, we have to disable receives and
	 * flush out all Rx frames beक्रमe we enable RSS. To करो so, we modअगरy we
	 * redirect all Rx traffic to manageability and then reset the HW.
	 * This flushes away Rx frames, and (since the redirections to
	 * manageability persists across resets) keeps new ones from coming in
	 * जबतक we work.  Then, we clear the Address Valid AV bit क्रम all MAC
	 * addresses and unकरो the re-direction to manageability.
	 * Now, frames are coming in again, but the MAC won't accept them, so
	 * far so good.  We now proceed to initialize RSS (अगर necessary) and
	 * configure the Rx unit.  Last, we re-enable the AV bits and जारी
	 * on our merry way.
	 */
	चयन (hw->mac_type) अणु
	शेष:
		/* Indicate to hardware the Address is Valid. */
		rar_high |= E1000_RAH_AV;
		अवरोध;
	पूर्ण

	E1000_WRITE_REG_ARRAY(hw, RA, (index << 1), rar_low);
	E1000_WRITE_FLUSH();
	E1000_WRITE_REG_ARRAY(hw, RA, ((index << 1) + 1), rar_high);
	E1000_WRITE_FLUSH();
पूर्ण

/**
 * e1000_ग_लिखो_vfta - Writes a value to the specअगरied offset in the VLAN filter table.
 * @hw: Struct containing variables accessed by shared code
 * @offset: Offset in VLAN filer table to ग_लिखो
 * @value: Value to ग_लिखो पूर्णांकo VLAN filter table
 */
व्योम e1000_ग_लिखो_vfta(काष्ठा e1000_hw *hw, u32 offset, u32 value)
अणु
	u32 temp;

	अगर ((hw->mac_type == e1000_82544) && ((offset & 0x1) == 1)) अणु
		temp = E1000_READ_REG_ARRAY(hw, VFTA, (offset - 1));
		E1000_WRITE_REG_ARRAY(hw, VFTA, offset, value);
		E1000_WRITE_FLUSH();
		E1000_WRITE_REG_ARRAY(hw, VFTA, (offset - 1), temp);
		E1000_WRITE_FLUSH();
	पूर्ण अन्यथा अणु
		E1000_WRITE_REG_ARRAY(hw, VFTA, offset, value);
		E1000_WRITE_FLUSH();
	पूर्ण
पूर्ण

/**
 * e1000_clear_vfta - Clears the VLAN filer table
 * @hw: Struct containing variables accessed by shared code
 */
अटल व्योम e1000_clear_vfta(काष्ठा e1000_hw *hw)
अणु
	u32 offset;

	क्रम (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) अणु
		E1000_WRITE_REG_ARRAY(hw, VFTA, offset, 0);
		E1000_WRITE_FLUSH();
	पूर्ण
पूर्ण

अटल s32 e1000_id_led_init(काष्ठा e1000_hw *hw)
अणु
	u32 ledctl;
	स्थिर u32 ledctl_mask = 0x000000FF;
	स्थिर u32 ledctl_on = E1000_LEDCTL_MODE_LED_ON;
	स्थिर u32 ledctl_off = E1000_LEDCTL_MODE_LED_OFF;
	u16 eeprom_data, i, temp;
	स्थिर u16 led_mask = 0x0F;

	अगर (hw->mac_type < e1000_82540) अणु
		/* Nothing to करो */
		वापस E1000_SUCCESS;
	पूर्ण

	ledctl = er32(LEDCTL);
	hw->ledctl_शेष = ledctl;
	hw->ledctl_mode1 = hw->ledctl_शेष;
	hw->ledctl_mode2 = hw->ledctl_शेष;

	अगर (e1000_पढ़ो_eeprom(hw, EEPROM_ID_LED_SETTINGS, 1, &eeprom_data) < 0) अणु
		e_dbg("EEPROM Read Error\n");
		वापस -E1000_ERR_EEPROM;
	पूर्ण

	अगर ((eeprom_data == ID_LED_RESERVED_0000) ||
	    (eeprom_data == ID_LED_RESERVED_FFFF)) अणु
		eeprom_data = ID_LED_DEFAULT;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		temp = (eeprom_data >> (i << 2)) & led_mask;
		चयन (temp) अणु
		हाल ID_LED_ON1_DEF2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_ON1_OFF2:
			hw->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode1 |= ledctl_on << (i << 3);
			अवरोध;
		हाल ID_LED_OFF1_DEF2:
		हाल ID_LED_OFF1_ON2:
		हाल ID_LED_OFF1_OFF2:
			hw->ledctl_mode1 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode1 |= ledctl_off << (i << 3);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
		चयन (temp) अणु
		हाल ID_LED_DEF1_ON2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_OFF1_ON2:
			hw->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode2 |= ledctl_on << (i << 3);
			अवरोध;
		हाल ID_LED_DEF1_OFF2:
		हाल ID_LED_ON1_OFF2:
		हाल ID_LED_OFF1_OFF2:
			hw->ledctl_mode2 &= ~(ledctl_mask << (i << 3));
			hw->ledctl_mode2 |= ledctl_off << (i << 3);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_setup_led
 * @hw: Struct containing variables accessed by shared code
 *
 * Prepares SW controlable LED क्रम use and saves the current state of the LED.
 */
s32 e1000_setup_led(काष्ठा e1000_hw *hw)
अणु
	u32 ledctl;
	s32 ret_val = E1000_SUCCESS;

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
	हाल e1000_82544:
		/* No setup necessary */
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82547:
	हाल e1000_82541_rev_2:
	हाल e1000_82547_rev_2:
		/* Turn off PHY Smart Power Down (अगर enabled) */
		ret_val = e1000_पढ़ो_phy_reg(hw, IGP01E1000_GMII_FIFO,
					     &hw->phy_spd_शेष);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_ग_लिखो_phy_reg(hw, IGP01E1000_GMII_FIFO,
					      (u16)(hw->phy_spd_शेष &
						     ~IGP01E1000_GMII_SPD));
		अगर (ret_val)
			वापस ret_val;
		fallthrough;
	शेष:
		अगर (hw->media_type == e1000_media_type_fiber) अणु
			ledctl = er32(LEDCTL);
			/* Save current LEDCTL settings */
			hw->ledctl_शेष = ledctl;
			/* Turn off LED0 */
			ledctl &= ~(E1000_LEDCTL_LED0_IVRT |
				    E1000_LEDCTL_LED0_BLINK |
				    E1000_LEDCTL_LED0_MODE_MASK);
			ledctl |= (E1000_LEDCTL_MODE_LED_OFF <<
				   E1000_LEDCTL_LED0_MODE_SHIFT);
			ew32(LEDCTL, ledctl);
		पूर्ण अन्यथा अगर (hw->media_type == e1000_media_type_copper)
			ew32(LEDCTL, hw->ledctl_mode1);
		अवरोध;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_cleanup_led - Restores the saved state of the SW controlable LED.
 * @hw: Struct containing variables accessed by shared code
 */
s32 e1000_cleanup_led(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = E1000_SUCCESS;

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
	हाल e1000_82544:
		/* No cleanup necessary */
		अवरोध;
	हाल e1000_82541:
	हाल e1000_82547:
	हाल e1000_82541_rev_2:
	हाल e1000_82547_rev_2:
		/* Turn on PHY Smart Power Down (अगर previously enabled) */
		ret_val = e1000_ग_लिखो_phy_reg(hw, IGP01E1000_GMII_FIFO,
					      hw->phy_spd_शेष);
		अगर (ret_val)
			वापस ret_val;
		fallthrough;
	शेष:
		/* Restore LEDCTL settings */
		ew32(LEDCTL, hw->ledctl_शेष);
		अवरोध;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_led_on - Turns on the software controllable LED
 * @hw: Struct containing variables accessed by shared code
 */
s32 e1000_led_on(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl = er32(CTRL);

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
		/* Set SW Defineable Pin 0 to turn on the LED */
		ctrl |= E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		अवरोध;
	हाल e1000_82544:
		अगर (hw->media_type == e1000_media_type_fiber) अणु
			/* Set SW Defineable Pin 0 to turn on the LED */
			ctrl |= E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण अन्यथा अणु
			/* Clear SW Defineable Pin 0 to turn on the LED */
			ctrl &= ~E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण
		अवरोध;
	शेष:
		अगर (hw->media_type == e1000_media_type_fiber) अणु
			/* Clear SW Defineable Pin 0 to turn on the LED */
			ctrl &= ~E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण अन्यथा अगर (hw->media_type == e1000_media_type_copper) अणु
			ew32(LEDCTL, hw->ledctl_mode2);
			वापस E1000_SUCCESS;
		पूर्ण
		अवरोध;
	पूर्ण

	ew32(CTRL, ctrl);

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_led_off - Turns off the software controllable LED
 * @hw: Struct containing variables accessed by shared code
 */
s32 e1000_led_off(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl = er32(CTRL);

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
	हाल e1000_82543:
		/* Clear SW Defineable Pin 0 to turn off the LED */
		ctrl &= ~E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		अवरोध;
	हाल e1000_82544:
		अगर (hw->media_type == e1000_media_type_fiber) अणु
			/* Clear SW Defineable Pin 0 to turn off the LED */
			ctrl &= ~E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण अन्यथा अणु
			/* Set SW Defineable Pin 0 to turn off the LED */
			ctrl |= E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण
		अवरोध;
	शेष:
		अगर (hw->media_type == e1000_media_type_fiber) अणु
			/* Set SW Defineable Pin 0 to turn off the LED */
			ctrl |= E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		पूर्ण अन्यथा अगर (hw->media_type == e1000_media_type_copper) अणु
			ew32(LEDCTL, hw->ledctl_mode1);
			वापस E1000_SUCCESS;
		पूर्ण
		अवरोध;
	पूर्ण

	ew32(CTRL, ctrl);

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_clear_hw_cntrs - Clears all hardware statistics counters.
 * @hw: Struct containing variables accessed by shared code
 */
अटल व्योम e1000_clear_hw_cntrs(काष्ठा e1000_hw *hw)
अणु
	er32(CRCERRS);
	er32(SYMERRS);
	er32(MPC);
	er32(SCC);
	er32(ECOL);
	er32(MCC);
	er32(LATECOL);
	er32(COLC);
	er32(DC);
	er32(SEC);
	er32(RLEC);
	er32(XONRXC);
	er32(XONTXC);
	er32(XOFFRXC);
	er32(XOFFTXC);
	er32(FCRUC);

	er32(PRC64);
	er32(PRC127);
	er32(PRC255);
	er32(PRC511);
	er32(PRC1023);
	er32(PRC1522);

	er32(GPRC);
	er32(BPRC);
	er32(MPRC);
	er32(GPTC);
	er32(GORCL);
	er32(GORCH);
	er32(GOTCL);
	er32(GOTCH);
	er32(RNBC);
	er32(RUC);
	er32(RFC);
	er32(ROC);
	er32(RJC);
	er32(TORL);
	er32(TORH);
	er32(TOTL);
	er32(TOTH);
	er32(TPR);
	er32(TPT);

	er32(PTC64);
	er32(PTC127);
	er32(PTC255);
	er32(PTC511);
	er32(PTC1023);
	er32(PTC1522);

	er32(MPTC);
	er32(BPTC);

	अगर (hw->mac_type < e1000_82543)
		वापस;

	er32(ALGNERRC);
	er32(RXERRC);
	er32(TNCRS);
	er32(CEXTERR);
	er32(TSCTC);
	er32(TSCTFC);

	अगर (hw->mac_type <= e1000_82544)
		वापस;

	er32(MGTPRC);
	er32(MGTPDC);
	er32(MGTPTC);
पूर्ण

/**
 * e1000_reset_adaptive - Resets Adaptive IFS to its शेष state.
 * @hw: Struct containing variables accessed by shared code
 *
 * Call this after e1000_init_hw. You may override the IFS शेषs by setting
 * hw->अगरs_params_क्रमced to true. However, you must initialize hw->
 * current_अगरs_val, अगरs_min_val, अगरs_max_val, अगरs_step_size, and अगरs_ratio
 * beक्रमe calling this function.
 */
व्योम e1000_reset_adaptive(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->adaptive_अगरs) अणु
		अगर (!hw->अगरs_params_क्रमced) अणु
			hw->current_अगरs_val = 0;
			hw->अगरs_min_val = IFS_MIN;
			hw->अगरs_max_val = IFS_MAX;
			hw->अगरs_step_size = IFS_STEP;
			hw->अगरs_ratio = IFS_RATIO;
		पूर्ण
		hw->in_अगरs_mode = false;
		ew32(AIT, 0);
	पूर्ण अन्यथा अणु
		e_dbg("Not in Adaptive IFS mode!\n");
	पूर्ण
पूर्ण

/**
 * e1000_update_adaptive - update adaptive IFS
 * @hw: Struct containing variables accessed by shared code
 *
 * Called during the callback/watchकरोg routine to update IFS value based on
 * the ratio of transmits to collisions.
 */
व्योम e1000_update_adaptive(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->adaptive_अगरs) अणु
		अगर ((hw->collision_delta * hw->अगरs_ratio) > hw->tx_packet_delta) अणु
			अगर (hw->tx_packet_delta > MIN_NUM_XMITS) अणु
				hw->in_अगरs_mode = true;
				अगर (hw->current_अगरs_val < hw->अगरs_max_val) अणु
					अगर (hw->current_अगरs_val == 0)
						hw->current_अगरs_val =
						    hw->अगरs_min_val;
					अन्यथा
						hw->current_अगरs_val +=
						    hw->अगरs_step_size;
					ew32(AIT, hw->current_अगरs_val);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (hw->in_अगरs_mode &&
			    (hw->tx_packet_delta <= MIN_NUM_XMITS)) अणु
				hw->current_अगरs_val = 0;
				hw->in_अगरs_mode = false;
				ew32(AIT, 0);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		e_dbg("Not in Adaptive IFS mode!\n");
	पूर्ण
पूर्ण

/**
 * e1000_get_bus_info
 * @hw: Struct containing variables accessed by shared code
 *
 * Gets the current PCI bus type, speed, and width of the hardware
 */
व्योम e1000_get_bus_info(काष्ठा e1000_hw *hw)
अणु
	u32 status;

	चयन (hw->mac_type) अणु
	हाल e1000_82542_rev2_0:
	हाल e1000_82542_rev2_1:
		hw->bus_type = e1000_bus_type_pci;
		hw->bus_speed = e1000_bus_speed_unknown;
		hw->bus_width = e1000_bus_width_unknown;
		अवरोध;
	शेष:
		status = er32(STATUS);
		hw->bus_type = (status & E1000_STATUS_PCIX_MODE) ?
		    e1000_bus_type_pcix : e1000_bus_type_pci;

		अगर (hw->device_id == E1000_DEV_ID_82546EB_QUAD_COPPER) अणु
			hw->bus_speed = (hw->bus_type == e1000_bus_type_pci) ?
			    e1000_bus_speed_66 : e1000_bus_speed_120;
		पूर्ण अन्यथा अगर (hw->bus_type == e1000_bus_type_pci) अणु
			hw->bus_speed = (status & E1000_STATUS_PCI66) ?
			    e1000_bus_speed_66 : e1000_bus_speed_33;
		पूर्ण अन्यथा अणु
			चयन (status & E1000_STATUS_PCIX_SPEED) अणु
			हाल E1000_STATUS_PCIX_SPEED_66:
				hw->bus_speed = e1000_bus_speed_66;
				अवरोध;
			हाल E1000_STATUS_PCIX_SPEED_100:
				hw->bus_speed = e1000_bus_speed_100;
				अवरोध;
			हाल E1000_STATUS_PCIX_SPEED_133:
				hw->bus_speed = e1000_bus_speed_133;
				अवरोध;
			शेष:
				hw->bus_speed = e1000_bus_speed_reserved;
				अवरोध;
			पूर्ण
		पूर्ण
		hw->bus_width = (status & E1000_STATUS_BUS64) ?
		    e1000_bus_width_64 : e1000_bus_width_32;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * e1000_ग_लिखो_reg_io
 * @hw: Struct containing variables accessed by shared code
 * @offset: offset to ग_लिखो to
 * @value: value to ग_लिखो
 *
 * Writes a value to one of the devices रेजिस्टरs using port I/O (as opposed to
 * memory mapped I/O). Only 82544 and newer devices support port I/O.
 */
अटल व्योम e1000_ग_लिखो_reg_io(काष्ठा e1000_hw *hw, u32 offset, u32 value)
अणु
	अचिन्हित दीर्घ io_addr = hw->io_base;
	अचिन्हित दीर्घ io_data = hw->io_base + 4;

	e1000_io_ग_लिखो(hw, io_addr, offset);
	e1000_io_ग_लिखो(hw, io_data, value);
पूर्ण

/**
 * e1000_get_cable_length - Estimates the cable length.
 * @hw: Struct containing variables accessed by shared code
 * @min_length: The estimated minimum length
 * @max_length: The estimated maximum length
 *
 * वापसs: - E1000_ERR_XXX
 *            E1000_SUCCESS
 *
 * This function always वापसs a ranged length (minimum & maximum).
 * So क्रम M88 phy's, this function पूर्णांकerprets the one value वापसed from the
 * रेजिस्टर to the minimum and maximum range.
 * For IGP phy's, the function calculates the range by the AGC रेजिस्टरs.
 */
अटल s32 e1000_get_cable_length(काष्ठा e1000_hw *hw, u16 *min_length,
				  u16 *max_length)
अणु
	s32 ret_val;
	u16 agc_value = 0;
	u16 i, phy_data;
	u16 cable_length;

	*min_length = *max_length = 0;

	/* Use old method क्रम Phy older than IGP */
	अगर (hw->phy_type == e1000_phy_m88) अणु
		ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;
		cable_length = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
		    M88E1000_PSSR_CABLE_LENGTH_SHIFT;

		/* Convert the क्रमागत value to ranged values */
		चयन (cable_length) अणु
		हाल e1000_cable_length_50:
			*min_length = 0;
			*max_length = e1000_igp_cable_length_50;
			अवरोध;
		हाल e1000_cable_length_50_80:
			*min_length = e1000_igp_cable_length_50;
			*max_length = e1000_igp_cable_length_80;
			अवरोध;
		हाल e1000_cable_length_80_110:
			*min_length = e1000_igp_cable_length_80;
			*max_length = e1000_igp_cable_length_110;
			अवरोध;
		हाल e1000_cable_length_110_140:
			*min_length = e1000_igp_cable_length_110;
			*max_length = e1000_igp_cable_length_140;
			अवरोध;
		हाल e1000_cable_length_140:
			*min_length = e1000_igp_cable_length_140;
			*max_length = e1000_igp_cable_length_170;
			अवरोध;
		शेष:
			वापस -E1000_ERR_PHY;
		पूर्ण
	पूर्ण अन्यथा अगर (hw->phy_type == e1000_phy_igp) अणु	/* For IGP PHY */
		u16 cur_agc_value;
		u16 min_agc_value = IGP01E1000_AGC_LENGTH_TABLE_SIZE;
		अटल स्थिर u16 agc_reg_array[IGP01E1000_PHY_CHANNEL_NUM] = अणु
		       IGP01E1000_PHY_AGC_A,
		       IGP01E1000_PHY_AGC_B,
		       IGP01E1000_PHY_AGC_C,
		       IGP01E1000_PHY_AGC_D
		पूर्ण;
		/* Read the AGC रेजिस्टरs क्रम all channels */
		क्रम (i = 0; i < IGP01E1000_PHY_CHANNEL_NUM; i++) अणु
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, agc_reg_array[i], &phy_data);
			अगर (ret_val)
				वापस ret_val;

			cur_agc_value = phy_data >> IGP01E1000_AGC_LENGTH_SHIFT;

			/* Value bound check. */
			अगर ((cur_agc_value >=
			     IGP01E1000_AGC_LENGTH_TABLE_SIZE - 1) ||
			    (cur_agc_value == 0))
				वापस -E1000_ERR_PHY;

			agc_value += cur_agc_value;

			/* Update minimal AGC value. */
			अगर (min_agc_value > cur_agc_value)
				min_agc_value = cur_agc_value;
		पूर्ण

		/* Remove the minimal AGC result क्रम length < 50m */
		अगर (agc_value <
		    IGP01E1000_PHY_CHANNEL_NUM * e1000_igp_cable_length_50) अणु
			agc_value -= min_agc_value;

			/* Get the average length of the reमुख्यing 3 channels */
			agc_value /= (IGP01E1000_PHY_CHANNEL_NUM - 1);
		पूर्ण अन्यथा अणु
			/* Get the average length of all the 4 channels. */
			agc_value /= IGP01E1000_PHY_CHANNEL_NUM;
		पूर्ण

		/* Set the range of the calculated length. */
		*min_length = ((e1000_igp_cable_length_table[agc_value] -
				IGP01E1000_AGC_RANGE) > 0) ?
		    (e1000_igp_cable_length_table[agc_value] -
		     IGP01E1000_AGC_RANGE) : 0;
		*max_length = e1000_igp_cable_length_table[agc_value] +
		    IGP01E1000_AGC_RANGE;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_check_polarity - Check the cable polarity
 * @hw: Struct containing variables accessed by shared code
 * @polarity: output parameter : 0 - Polarity is not reversed
 *                               1 - Polarity is reversed.
 *
 * वापसs: - E1000_ERR_XXX
 *            E1000_SUCCESS
 *
 * For phy's older than IGP, this function simply पढ़ोs the polarity bit in the
 * Phy Status रेजिस्टर.  For IGP phy's, this bit is valid only अगर link speed is
 * 10 Mbps.  If the link speed is 100 Mbps there is no polarity so this bit will
 * वापस 0.  If the link speed is 1000 Mbps the polarity status is in the
 * IGP01E1000_PHY_PCS_INIT_REG.
 */
अटल s32 e1000_check_polarity(काष्ठा e1000_hw *hw,
				e1000_rev_polarity *polarity)
अणु
	s32 ret_val;
	u16 phy_data;

	अगर (hw->phy_type == e1000_phy_m88) अणु
		/* वापस the Polarity bit in the Status रेजिस्टर. */
		ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;
		*polarity = ((phy_data & M88E1000_PSSR_REV_POLARITY) >>
			     M88E1000_PSSR_REV_POLARITY_SHIFT) ?
		    e1000_rev_polarity_reversed : e1000_rev_polarity_normal;

	पूर्ण अन्यथा अगर (hw->phy_type == e1000_phy_igp) अणु
		/* Read the Status रेजिस्टर to check the speed */
		ret_val = e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_STATUS,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* If speed is 1000 Mbps, must पढ़ो the
		 * IGP01E1000_PHY_PCS_INIT_REG to find the polarity status
		 */
		अगर ((phy_data & IGP01E1000_PSSR_SPEED_MASK) ==
		    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
			/* Read the GIG initialization PCS रेजिस्टर (0x00B4) */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PCS_INIT_REG,
					       &phy_data);
			अगर (ret_val)
				वापस ret_val;

			/* Check the polarity bits */
			*polarity = (phy_data & IGP01E1000_PHY_POLARITY_MASK) ?
			    e1000_rev_polarity_reversed :
			    e1000_rev_polarity_normal;
		पूर्ण अन्यथा अणु
			/* For 10 Mbps, पढ़ो the polarity bit in the status
			 * रेजिस्टर. (क्रम 100 Mbps this bit is always 0)
			 */
			*polarity =
			    (phy_data & IGP01E1000_PSSR_POLARITY_REVERSED) ?
			    e1000_rev_polarity_reversed :
			    e1000_rev_polarity_normal;
		पूर्ण
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_check_करोwnshअगरt - Check अगर Downshअगरt occurred
 * @hw: Struct containing variables accessed by shared code
 *
 * वापसs: - E1000_ERR_XXX
 *            E1000_SUCCESS
 *
 * For phy's older than IGP, this function पढ़ोs the Downshअगरt bit in the Phy
 * Specअगरic Status रेजिस्टर.  For IGP phy's, it पढ़ोs the Downgrade bit in the
 * Link Health रेजिस्टर.  In IGP this bit is latched high, so the driver must
 * पढ़ो it immediately after link is established.
 */
अटल s32 e1000_check_करोwnshअगरt(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	अगर (hw->phy_type == e1000_phy_igp) अणु
		ret_val = e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_LINK_HEALTH,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;

		hw->speed_करोwngraded =
		    (phy_data & IGP01E1000_PLHR_SS_DOWNGRADE) ? 1 : 0;
	पूर्ण अन्यथा अगर (hw->phy_type == e1000_phy_m88) अणु
		ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		अगर (ret_val)
			वापस ret_val;

		hw->speed_करोwngraded = (phy_data & M88E1000_PSSR_DOWNSHIFT) >>
		    M88E1000_PSSR_DOWNSHIFT_SHIFT;
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

अटल स्थिर u16 dsp_reg_array[IGP01E1000_PHY_CHANNEL_NUM] = अणु
	IGP01E1000_PHY_AGC_PARAM_A,
	IGP01E1000_PHY_AGC_PARAM_B,
	IGP01E1000_PHY_AGC_PARAM_C,
	IGP01E1000_PHY_AGC_PARAM_D
पूर्ण;

अटल s32 e1000_1000Mb_check_cable_length(काष्ठा e1000_hw *hw)
अणु
	u16 min_length, max_length;
	u16 phy_data, i;
	s32 ret_val;

	ret_val = e1000_get_cable_length(hw, &min_length, &max_length);
	अगर (ret_val)
		वापस ret_val;

	अगर (hw->dsp_config_state != e1000_dsp_config_enabled)
		वापस 0;

	अगर (min_length >= e1000_igp_cable_length_50) अणु
		क्रम (i = 0; i < IGP01E1000_PHY_CHANNEL_NUM; i++) अणु
			ret_val = e1000_पढ़ो_phy_reg(hw, dsp_reg_array[i],
						     &phy_data);
			अगर (ret_val)
				वापस ret_val;

			phy_data &= ~IGP01E1000_PHY_EDAC_MU_INDEX;

			ret_val = e1000_ग_लिखो_phy_reg(hw, dsp_reg_array[i],
						      phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
		hw->dsp_config_state = e1000_dsp_config_activated;
	पूर्ण अन्यथा अणु
		u16 ffe_idle_err_समयout = FFE_IDLE_ERR_COUNT_TIMEOUT_20;
		u32 idle_errs = 0;

		/* clear previous idle error counts */
		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		क्रम (i = 0; i < ffe_idle_err_समयout; i++) अणु
			udelay(1000);
			ret_val = e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS,
						     &phy_data);
			अगर (ret_val)
				वापस ret_val;

			idle_errs += (phy_data & SR_1000T_IDLE_ERROR_CNT);
			अगर (idle_errs > SR_1000T_PHY_EXCESSIVE_IDLE_ERR_COUNT) अणु
				hw->ffe_config_state = e1000_ffe_config_active;

				ret_val = e1000_ग_लिखो_phy_reg(hw,
							      IGP01E1000_PHY_DSP_FFE,
							      IGP01E1000_PHY_DSP_FFE_CM_CP);
				अगर (ret_val)
					वापस ret_val;
				अवरोध;
			पूर्ण

			अगर (idle_errs)
				ffe_idle_err_समयout =
					    FFE_IDLE_ERR_COUNT_TIMEOUT_100;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * e1000_config_dsp_after_link_change
 * @hw: Struct containing variables accessed by shared code
 * @link_up: was link up at the समय this was called
 *
 * वापसs: - E1000_ERR_PHY अगर fail to पढ़ो/ग_लिखो the PHY
 *            E1000_SUCCESS at any other हाल.
 *
 * 82541_rev_2 & 82547_rev_2 have the capability to configure the DSP when a
 * gigabit link is achieved to improve link quality.
 */

अटल s32 e1000_config_dsp_after_link_change(काष्ठा e1000_hw *hw, bool link_up)
अणु
	s32 ret_val;
	u16 phy_data, phy_saved_data, speed, duplex, i;

	अगर (hw->phy_type != e1000_phy_igp)
		वापस E1000_SUCCESS;

	अगर (link_up) अणु
		ret_val = e1000_get_speed_and_duplex(hw, &speed, &duplex);
		अगर (ret_val) अणु
			e_dbg("Error getting link speed and duplex\n");
			वापस ret_val;
		पूर्ण

		अगर (speed == SPEED_1000) अणु
			ret_val = e1000_1000Mb_check_cable_length(hw);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hw->dsp_config_state == e1000_dsp_config_activated) अणु
			/* Save off the current value of रेजिस्टर 0x2F5B to be
			 * restored at the end of the routines.
			 */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, 0x2F5B, &phy_saved_data);

			अगर (ret_val)
				वापस ret_val;

			/* Disable the PHY transmitter */
			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x2F5B, 0x0003);

			अगर (ret_val)
				वापस ret_val;

			msleep(20);

			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_FORCE_GIGA);
			अगर (ret_val)
				वापस ret_val;
			क्रम (i = 0; i < IGP01E1000_PHY_CHANNEL_NUM; i++) अणु
				ret_val =
				    e1000_पढ़ो_phy_reg(hw, dsp_reg_array[i],
						       &phy_data);
				अगर (ret_val)
					वापस ret_val;

				phy_data &= ~IGP01E1000_PHY_EDAC_MU_INDEX;
				phy_data |= IGP01E1000_PHY_EDAC_SIGN_EXT_9_BITS;

				ret_val =
				    e1000_ग_लिखो_phy_reg(hw, dsp_reg_array[i],
							phy_data);
				अगर (ret_val)
					वापस ret_val;
			पूर्ण

			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_RESTART_AUTONEG);
			अगर (ret_val)
				वापस ret_val;

			msleep(20);

			/* Now enable the transmitter */
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, 0x2F5B, phy_saved_data);

			अगर (ret_val)
				वापस ret_val;

			hw->dsp_config_state = e1000_dsp_config_enabled;
		पूर्ण

		अगर (hw->ffe_config_state == e1000_ffe_config_active) अणु
			/* Save off the current value of रेजिस्टर 0x2F5B to be
			 * restored at the end of the routines.
			 */
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, 0x2F5B, &phy_saved_data);

			अगर (ret_val)
				वापस ret_val;

			/* Disable the PHY transmitter */
			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x2F5B, 0x0003);

			अगर (ret_val)
				वापस ret_val;

			msleep(20);

			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_FORCE_GIGA);
			अगर (ret_val)
				वापस ret_val;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_DSP_FFE,
						IGP01E1000_PHY_DSP_FFE_DEFAULT);
			अगर (ret_val)
				वापस ret_val;

			ret_val = e1000_ग_लिखो_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_RESTART_AUTONEG);
			अगर (ret_val)
				वापस ret_val;

			msleep(20);

			/* Now enable the transmitter */
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, 0x2F5B, phy_saved_data);

			अगर (ret_val)
				वापस ret_val;

			hw->ffe_config_state = e1000_ffe_config_enabled;
		पूर्ण
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_set_phy_mode - Set PHY to class A mode
 * @hw: Struct containing variables accessed by shared code
 *
 * Assumes the following operations will follow to enable the new class mode.
 *  1. Do a PHY soft reset
 *  2. Restart स्वतः-negotiation or क्रमce link.
 */
अटल s32 e1000_set_phy_mode(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 eeprom_data;

	अगर ((hw->mac_type == e1000_82545_rev_3) &&
	    (hw->media_type == e1000_media_type_copper)) अणु
		ret_val =
		    e1000_पढ़ो_eeprom(hw, EEPROM_PHY_CLASS_WORD, 1,
				      &eeprom_data);
		अगर (ret_val)
			वापस ret_val;

		अगर ((eeprom_data != EEPROM_RESERVED_WORD) &&
		    (eeprom_data & EEPROM_PHY_CLASS_A)) अणु
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT,
						0x000B);
			अगर (ret_val)
				वापस ret_val;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL,
						0x8104);
			अगर (ret_val)
				वापस ret_val;

			hw->phy_reset_disable = false;
		पूर्ण
	पूर्ण

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_set_d3_lplu_state - set d3 link घातer state
 * @hw: Struct containing variables accessed by shared code
 * @active: true to enable lplu false to disable lplu.
 *
 * This function sets the lplu state according to the active flag.  When
 * activating lplu this function also disables smart speed and vise versa.
 * lplu will not be activated unless the device स्वतःnegotiation advertisement
 * meets standards of either 10 or 10/100 or 10/100/1000 at all duplexes.
 *
 * वापसs: - E1000_ERR_PHY अगर fail to पढ़ो/ग_लिखो the PHY
 *            E1000_SUCCESS at any other हाल.
 */
अटल s32 e1000_set_d3_lplu_state(काष्ठा e1000_hw *hw, bool active)
अणु
	s32 ret_val;
	u16 phy_data;

	अगर (hw->phy_type != e1000_phy_igp)
		वापस E1000_SUCCESS;

	/* During driver activity LPLU should not be used or it will attain link
	 * from the lowest speeds starting from 10Mbps. The capability is used
	 * क्रम Dx transitions and states
	 */
	अगर (hw->mac_type == e1000_82541_rev_2 ||
	    hw->mac_type == e1000_82547_rev_2) अणु
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, IGP01E1000_GMII_FIFO, &phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (!active) अणु
		अगर (hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547_rev_2) अणु
			phy_data &= ~IGP01E1000_GMII_FLEX_SPD;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_GMII_FIFO,
						phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (hw->smart_speed == e1000_smart_speed_on) अणु
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			अगर (ret_val)
				वापस ret_val;

			phy_data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण अन्यथा अगर (hw->smart_speed == e1000_smart_speed_off) अणु
			ret_val =
			    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			अगर (ret_val)
				वापस ret_val;

			phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण अन्यथा अगर ((hw->स्वतःneg_advertised == AUTONEG_ADVERTISE_SPEED_DEFAULT) ||
		   (hw->स्वतःneg_advertised == AUTONEG_ADVERTISE_10_ALL) ||
		   (hw->स्वतःneg_advertised == AUTONEG_ADVERTISE_10_100_ALL)) अणु
		अगर (hw->mac_type == e1000_82541_rev_2 ||
		    hw->mac_type == e1000_82547_rev_2) अणु
			phy_data |= IGP01E1000_GMII_FLEX_SPD;
			ret_val =
			    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_GMII_FIFO,
						phy_data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		/* When LPLU is enabled we should disable SmartSpeed */
		ret_val =
		    e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
				       &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val =
		    e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_set_vco_speed
 * @hw: Struct containing variables accessed by shared code
 *
 * Change VCO speed रेजिस्टर to improve Bit Error Rate perक्रमmance of SERDES.
 */
अटल s32 e1000_set_vco_speed(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 शेष_page = 0;
	u16 phy_data;

	चयन (hw->mac_type) अणु
	हाल e1000_82545_rev_3:
	हाल e1000_82546_rev_3:
		अवरोध;
	शेष:
		वापस E1000_SUCCESS;
	पूर्ण

	/* Set PHY रेजिस्टर 30, page 5, bit 8 to 0 */

	ret_val =
	    e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, &शेष_page);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0005);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data &= ~M88E1000_PHY_VCO_REG_BIT8;
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Set PHY रेजिस्टर 30, page 4, bit 11 to 1 */

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0004);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data |= M88E1000_PHY_VCO_REG_BIT11;
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	ret_val =
	    e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, शेष_page);
	अगर (ret_val)
		वापस ret_val;

	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_enable_mng_pass_thru - check क्रम bmc pass through
 * @hw: Struct containing variables accessed by shared code
 *
 * Verअगरies the hardware needs to allow ARPs to be processed by the host
 * वापसs: - true/false
 */
u32 e1000_enable_mng_pass_thru(काष्ठा e1000_hw *hw)
अणु
	u32 manc;

	अगर (hw->asf_firmware_present) अणु
		manc = er32(MANC);

		अगर (!(manc & E1000_MANC_RCV_TCO_EN) ||
		    !(manc & E1000_MANC_EN_MAC_ADDR_FILTER))
			वापस false;
		अगर ((manc & E1000_MANC_SMBUS_EN) && !(manc & E1000_MANC_ASF_EN))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल s32 e1000_polarity_reversal_workaround(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 mii_status_reg;
	u16 i;

	/* Polarity reversal workaround क्रम क्रमced 10F/10H links. */

	/* Disable the transmitter on the PHY */

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0019);
	अगर (ret_val)
		वापस ret_val;
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFFFF);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0000);
	अगर (ret_val)
		वापस ret_val;

	/* This loop will early-out अगर the NO link condition has been met. */
	क्रम (i = PHY_FORCE_TIME; i > 0; i--) अणु
		/* Read the MII Status Register and रुको क्रम Link Status bit
		 * to be clear.
		 */

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		अगर ((mii_status_reg & ~MII_SR_LINK_STATUS) == 0)
			अवरोध;
		msleep(100);
	पूर्ण

	/* Recommended delay समय after link has been lost */
	msleep(1000);

	/* Now we will re-enable th transmitter on the PHY */

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0019);
	अगर (ret_val)
		वापस ret_val;
	msleep(50);
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFFF0);
	अगर (ret_val)
		वापस ret_val;
	msleep(50);
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xFF00);
	अगर (ret_val)
		वापस ret_val;
	msleep(50);
	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_GEN_CONTROL, 0x0000);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_PAGE_SELECT, 0x0000);
	अगर (ret_val)
		वापस ret_val;

	/* This loop will early-out अगर the link condition has been met. */
	क्रम (i = PHY_FORCE_TIME; i > 0; i--) अणु
		/* Read the MII Status Register and रुको क्रम Link Status bit
		 * to be set.
		 */

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1000_पढ़ो_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		अगर (ret_val)
			वापस ret_val;

		अगर (mii_status_reg & MII_SR_LINK_STATUS)
			अवरोध;
		msleep(100);
	पूर्ण
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_get_स्वतः_rd_करोne
 * @hw: Struct containing variables accessed by shared code
 *
 * Check क्रम EEPROM Auto Read bit करोne.
 * वापसs: - E1000_ERR_RESET अगर fail to reset MAC
 *            E1000_SUCCESS at any other हाल.
 */
अटल s32 e1000_get_स्वतः_rd_करोne(काष्ठा e1000_hw *hw)
अणु
	msleep(5);
	वापस E1000_SUCCESS;
पूर्ण

/**
 * e1000_get_phy_cfg_करोne
 * @hw: Struct containing variables accessed by shared code
 *
 * Checks अगर the PHY configuration is करोne
 * वापसs: - E1000_ERR_RESET अगर fail to reset MAC
 *            E1000_SUCCESS at any other हाल.
 */
अटल s32 e1000_get_phy_cfg_करोne(काष्ठा e1000_hw *hw)
अणु
	msleep(10);
	वापस E1000_SUCCESS;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_phy.h"
#समावेश "ixgbe_mbx.h"

#घोषणा IXGBE_82599_MAX_TX_QUEUES 128
#घोषणा IXGBE_82599_MAX_RX_QUEUES 128
#घोषणा IXGBE_82599_RAR_ENTRIES   128
#घोषणा IXGBE_82599_MC_TBL_SIZE   128
#घोषणा IXGBE_82599_VFT_TBL_SIZE  128
#घोषणा IXGBE_82599_RX_PB_SIZE	  512

अटल व्योम ixgbe_disable_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_enable_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_flap_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw);
अटल व्योम
ixgbe_set_hard_rate_select_speed(काष्ठा ixgbe_hw *, ixgbe_link_speed);
अटल s32 ixgbe_setup_mac_link_smartspeed(काष्ठा ixgbe_hw *hw,
					   ixgbe_link_speed speed,
					   bool स्वतःneg_रुको_to_complete);
अटल व्योम ixgbe_stop_mac_link_on_d3_82599(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_start_mac_link_82599(काष्ठा ixgbe_hw *hw,
				      bool स्वतःneg_रुको_to_complete);
अटल s32 ixgbe_setup_mac_link_82599(काष्ठा ixgbe_hw *hw,
			       ixgbe_link_speed speed,
			       bool स्वतःneg_रुको_to_complete);
अटल s32 ixgbe_setup_copper_link_82599(काष्ठा ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool स्वतःneg_रुको_to_complete);
अटल s32 ixgbe_verअगरy_fw_version_82599(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_पढ़ो_i2c_byte_82599(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				     u8 dev_addr, u8 *data);
अटल s32 ixgbe_ग_लिखो_i2c_byte_82599(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				      u8 dev_addr, u8 data);
अटल s32 ixgbe_reset_pipeline_82599(काष्ठा ixgbe_hw *hw);
अटल bool ixgbe_verअगरy_lesm_fw_enabled_82599(काष्ठा ixgbe_hw *hw);

bool ixgbe_mng_enabled(काष्ठा ixgbe_hw *hw)
अणु
	u32 fwsm, manc, factps;

	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));
	अगर ((fwsm & IXGBE_FWSM_MODE_MASK) != IXGBE_FWSM_FW_MODE_PT)
		वापस false;

	manc = IXGBE_READ_REG(hw, IXGBE_MANC);
	अगर (!(manc & IXGBE_MANC_RCV_TCO_EN))
		वापस false;

	factps = IXGBE_READ_REG(hw, IXGBE_FACTPS(hw));
	अगर (factps & IXGBE_FACTPS_MNGCG)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम ixgbe_init_mac_link_ops_82599(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;

	/* enable the laser control functions क्रम SFP+ fiber
	 * and MNG not enabled
	 */
	अगर ((mac->ops.get_media_type(hw) == ixgbe_media_type_fiber) &&
	    !ixgbe_mng_enabled(hw)) अणु
		mac->ops.disable_tx_laser =
				       &ixgbe_disable_tx_laser_multispeed_fiber;
		mac->ops.enable_tx_laser =
					&ixgbe_enable_tx_laser_multispeed_fiber;
		mac->ops.flap_tx_laser = &ixgbe_flap_tx_laser_multispeed_fiber;
	पूर्ण अन्यथा अणु
		mac->ops.disable_tx_laser = शून्य;
		mac->ops.enable_tx_laser = शून्य;
		mac->ops.flap_tx_laser = शून्य;
	पूर्ण

	अगर (hw->phy.multispeed_fiber) अणु
		/* Set up dual speed SFP+ support */
		mac->ops.setup_link = &ixgbe_setup_mac_link_multispeed_fiber;
		mac->ops.setup_mac_link = ixgbe_setup_mac_link_82599;
		mac->ops.set_rate_select_speed =
					       ixgbe_set_hard_rate_select_speed;
	पूर्ण अन्यथा अणु
		अगर ((mac->ops.get_media_type(hw) ==
		     ixgbe_media_type_backplane) &&
		    (hw->phy.smart_speed == ixgbe_smart_speed_स्वतः ||
		     hw->phy.smart_speed == ixgbe_smart_speed_on) &&
		     !ixgbe_verअगरy_lesm_fw_enabled_82599(hw))
			mac->ops.setup_link = &ixgbe_setup_mac_link_smartspeed;
		अन्यथा
			mac->ops.setup_link = &ixgbe_setup_mac_link_82599;
	पूर्ण
पूर्ण

अटल s32 ixgbe_setup_sfp_modules_82599(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val;
	u16 list_offset, data_offset, data_value;

	अगर (hw->phy.sfp_type != ixgbe_sfp_type_unknown) अणु
		ixgbe_init_mac_link_ops_82599(hw);

		hw->phy.ops.reset = शून्य;

		ret_val = ixgbe_get_sfp_init_sequence_offsets(hw, &list_offset,
							      &data_offset);
		अगर (ret_val)
			वापस ret_val;

		/* PHY config will finish beक्रमe releasing the semaphore */
		ret_val = hw->mac.ops.acquire_swfw_sync(hw,
							IXGBE_GSSR_MAC_CSR_SM);
		अगर (ret_val)
			वापस IXGBE_ERR_SWFW_SYNC;

		अगर (hw->eeprom.ops.पढ़ो(hw, ++data_offset, &data_value))
			जाओ setup_sfp_err;
		जबतक (data_value != 0xffff) अणु
			IXGBE_WRITE_REG(hw, IXGBE_CORECTL, data_value);
			IXGBE_WRITE_FLUSH(hw);
			अगर (hw->eeprom.ops.पढ़ो(hw, ++data_offset, &data_value))
				जाओ setup_sfp_err;
		पूर्ण

		/* Release the semaphore */
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);
		/*
		 * Delay obtaining semaphore again to allow FW access,
		 * semaphore_delay is in ms usleep_range needs us.
		 */
		usleep_range(hw->eeprom.semaphore_delay * 1000,
			     hw->eeprom.semaphore_delay * 2000);

		/* Restart DSP and set SFI mode */
		ret_val = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw,
			hw->mac.orig_स्वतःc | IXGBE_AUTOC_LMS_10G_SERIAL,
			false);

		अगर (ret_val) अणु
			hw_dbg(hw, " sfp module setup not complete\n");
			वापस IXGBE_ERR_SFP_SETUP_NOT_COMPLETE;
		पूर्ण
	पूर्ण

	वापस 0;

setup_sfp_err:
	/* Release the semaphore */
	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);
	/* Delay obtaining semaphore again to allow FW access,
	 * semaphore_delay is in ms usleep_range needs us.
	 */
	usleep_range(hw->eeprom.semaphore_delay * 1000,
		     hw->eeprom.semaphore_delay * 2000);
	hw_err(hw, "eeprom read at offset %d failed\n", data_offset);
	वापस IXGBE_ERR_SFP_SETUP_NOT_COMPLETE;
पूर्ण

/**
 *  prot_स्वतःc_पढ़ो_82599 - Hides MAC dअगरferences needed क्रम AUTOC पढ़ो
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @locked: Return the अगर we locked क्रम this पढ़ो.
 *  @reg_val: Value we पढ़ो from AUTOC
 *
 *  For this part (82599) we need to wrap पढ़ो-modअगरy-ग_लिखोs with a possible
 *  FW/SW lock.  It is assumed this lock will be मुक्तd with the next
 *  prot_स्वतःc_ग_लिखो_82599().  Note, that locked can only be true in हालs
 *  where this function करोesn't वापस an error.
 **/
अटल s32 prot_स्वतःc_पढ़ो_82599(काष्ठा ixgbe_hw *hw, bool *locked,
				 u32 *reg_val)
अणु
	s32 ret_val;

	*locked = false;
	/* If LESM is on then we need to hold the SW/FW semaphore. */
	अगर (ixgbe_verअगरy_lesm_fw_enabled_82599(hw)) अणु
		ret_val = hw->mac.ops.acquire_swfw_sync(hw,
					IXGBE_GSSR_MAC_CSR_SM);
		अगर (ret_val)
			वापस IXGBE_ERR_SWFW_SYNC;

		*locked = true;
	पूर्ण

	*reg_val = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	वापस 0;
पूर्ण

/**
 * prot_स्वतःc_ग_लिखो_82599 - Hides MAC dअगरferences needed क्रम AUTOC ग_लिखो
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @स्वतःc: value to ग_लिखो to AUTOC
 * @locked: bool to indicate whether the SW/FW lock was alपढ़ोy taken by
 *	     previous proc_स्वतःc_पढ़ो_82599.
 *
 * This part (82599) may need to hold a the SW/FW lock around all ग_लिखोs to
 * AUTOC. Likewise after a ग_लिखो we need to करो a pipeline reset.
 **/
अटल s32 prot_स्वतःc_ग_लिखो_82599(काष्ठा ixgbe_hw *hw, u32 स्वतःc, bool locked)
अणु
	s32 ret_val = 0;

	/* Blocked by MNG FW so bail */
	अगर (ixgbe_check_reset_blocked(hw))
		जाओ out;

	/* We only need to get the lock अगर:
	 *  - We didn't करो it alपढ़ोy (in the पढ़ो part of a पढ़ो-modअगरy-ग_लिखो)
	 *  - LESM is enabled.
	 */
	अगर (!locked && ixgbe_verअगरy_lesm_fw_enabled_82599(hw)) अणु
		ret_val = hw->mac.ops.acquire_swfw_sync(hw,
					IXGBE_GSSR_MAC_CSR_SM);
		अगर (ret_val)
			वापस IXGBE_ERR_SWFW_SYNC;

		locked = true;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_AUTOC, स्वतःc);
	ret_val = ixgbe_reset_pipeline_82599(hw);

out:
	/* Free the SW/FW semaphore as we either grabbed it here or
	 * alपढ़ोy had it when this function was called.
	 */
	अगर (locked)
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);

	वापस ret_val;
पूर्ण

अटल s32 ixgbe_get_invariants_82599(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;

	ixgbe_init_mac_link_ops_82599(hw);

	mac->mcft_size = IXGBE_82599_MC_TBL_SIZE;
	mac->vft_size = IXGBE_82599_VFT_TBL_SIZE;
	mac->num_rar_entries = IXGBE_82599_RAR_ENTRIES;
	mac->rx_pb_size = IXGBE_82599_RX_PB_SIZE;
	mac->max_rx_queues = IXGBE_82599_MAX_RX_QUEUES;
	mac->max_tx_queues = IXGBE_82599_MAX_TX_QUEUES;
	mac->max_msix_vectors = ixgbe_get_pcie_msix_count_generic(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_phy_ops_82599 - PHY/SFP specअगरic init
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initialize any function poपूर्णांकers that were not able to be
 *  set during get_invariants because the PHY/SFP type was
 *  not known.  Perक्रमm the SFP init अगर necessary.
 *
 **/
अटल s32 ixgbe_init_phy_ops_82599(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	काष्ठा ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;
	u32 esdp;

	अगर (hw->device_id == IXGBE_DEV_ID_82599_QSFP_SF_QP) अणु
		/* Store flag indicating I2C bus access control unit. */
		hw->phy.qsfp_shared_i2c_bus = true;

		/* Initialize access to QSFP+ I2C bus */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0_सूची;
		esdp &= ~IXGBE_ESDP_SDP1_सूची;
		esdp &= ~IXGBE_ESDP_SDP0;
		esdp &= ~IXGBE_ESDP_SDP0_NATIVE;
		esdp &= ~IXGBE_ESDP_SDP1_NATIVE;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);

		phy->ops.पढ़ो_i2c_byte = &ixgbe_पढ़ो_i2c_byte_82599;
		phy->ops.ग_लिखो_i2c_byte = &ixgbe_ग_लिखो_i2c_byte_82599;
	पूर्ण

	/* Identअगरy the PHY or SFP module */
	ret_val = phy->ops.identअगरy(hw);

	/* Setup function poपूर्णांकers based on detected SFP module and speeds */
	ixgbe_init_mac_link_ops_82599(hw);

	/* If copper media, overग_लिखो with copper function poपूर्णांकers */
	अगर (mac->ops.get_media_type(hw) == ixgbe_media_type_copper) अणु
		mac->ops.setup_link = &ixgbe_setup_copper_link_82599;
		mac->ops.get_link_capabilities =
			&ixgbe_get_copper_link_capabilities_generic;
	पूर्ण

	/* Set necessary function poपूर्णांकers based on phy type */
	चयन (hw->phy.type) अणु
	हाल ixgbe_phy_tn:
		phy->ops.check_link = &ixgbe_check_phy_link_tnx;
		phy->ops.setup_link = &ixgbe_setup_phy_link_tnx;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  ixgbe_get_link_capabilities_82599 - Determines link capabilities
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: poपूर्णांकer to link speed
 *  @स्वतःneg: true when स्वतःneg or स्वतःtry is enabled
 *
 *  Determines the link capabilities by पढ़ोing the AUTOC रेजिस्टर.
 **/
अटल s32 ixgbe_get_link_capabilities_82599(काष्ठा ixgbe_hw *hw,
					     ixgbe_link_speed *speed,
					     bool *स्वतःneg)
अणु
	u32 स्वतःc = 0;

	/* Determine 1G link capabilities off of SFP+ type */
	अगर (hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1) अणु
		*speed = IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = true;
		वापस 0;
	पूर्ण

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

	हाल IXGBE_AUTOC_LMS_10G_SERIAL:
		*speed = IXGBE_LINK_SPEED_10GB_FULL;
		*स्वतःneg = false;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_KX4_KX_KR:
	हाल IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN:
		*speed = IXGBE_LINK_SPEED_UNKNOWN;
		अगर (स्वतःc & IXGBE_AUTOC_KR_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = true;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII:
		*speed = IXGBE_LINK_SPEED_100_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KR_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (स्वतःc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_LINK_SPEED_1GB_FULL;
		*स्वतःneg = true;
		अवरोध;

	हाल IXGBE_AUTOC_LMS_SGMII_1G_100M:
		*speed = IXGBE_LINK_SPEED_1GB_FULL | IXGBE_LINK_SPEED_100_FULL;
		*स्वतःneg = false;
		अवरोध;

	शेष:
		वापस IXGBE_ERR_LINK_SETUP;
	पूर्ण

	अगर (hw->phy.multispeed_fiber) अणु
		*speed |= IXGBE_LINK_SPEED_10GB_FULL |
			  IXGBE_LINK_SPEED_1GB_FULL;

		/* QSFP must not enable स्वतः-negotiation */
		अगर (hw->phy.media_type == ixgbe_media_type_fiber_qsfp)
			*स्वतःneg = false;
		अन्यथा
			*स्वतःneg = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_media_type_82599 - Get media type
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns the media type (fiber, copper, backplane)
 **/
अटल क्रमागत ixgbe_media_type ixgbe_get_media_type_82599(काष्ठा ixgbe_hw *hw)
अणु
	/* Detect अगर there is a copper PHY attached. */
	चयन (hw->phy.type) अणु
	हाल ixgbe_phy_cu_unknown:
	हाल ixgbe_phy_tn:
		वापस ixgbe_media_type_copper;

	शेष:
		अवरोध;
	पूर्ण

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82599_KX4:
	हाल IXGBE_DEV_ID_82599_KX4_MEZZ:
	हाल IXGBE_DEV_ID_82599_COMBO_BACKPLANE:
	हाल IXGBE_DEV_ID_82599_KR:
	हाल IXGBE_DEV_ID_82599_BACKPLANE_FCOE:
	हाल IXGBE_DEV_ID_82599_XAUI_LOM:
		/* Default device ID is mezzanine card KX/KX4 */
		वापस ixgbe_media_type_backplane;

	हाल IXGBE_DEV_ID_82599_SFP:
	हाल IXGBE_DEV_ID_82599_SFP_FCOE:
	हाल IXGBE_DEV_ID_82599_SFP_EM:
	हाल IXGBE_DEV_ID_82599_SFP_SF2:
	हाल IXGBE_DEV_ID_82599_SFP_SF_QP:
	हाल IXGBE_DEV_ID_82599EN_SFP:
		वापस ixgbe_media_type_fiber;

	हाल IXGBE_DEV_ID_82599_CX4:
		वापस ixgbe_media_type_cx4;

	हाल IXGBE_DEV_ID_82599_T3_LOM:
		वापस ixgbe_media_type_copper;

	हाल IXGBE_DEV_ID_82599_LS:
		वापस ixgbe_media_type_fiber_lco;

	हाल IXGBE_DEV_ID_82599_QSFP_SF_QP:
		वापस ixgbe_media_type_fiber_qsfp;

	शेष:
		वापस ixgbe_media_type_unknown;
	पूर्ण
पूर्ण

/**
 * ixgbe_stop_mac_link_on_d3_82599 - Disables link on D3
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Disables link, should be called during D3 घातer करोwn sequence.
 *
 **/
अटल व्योम ixgbe_stop_mac_link_on_d3_82599(काष्ठा ixgbe_hw *hw)
अणु
	u32 स्वतःc2_reg;
	u16 ee_ctrl_2 = 0;

	hw->eeprom.ops.पढ़ो(hw, IXGBE_EEPROM_CTRL_2, &ee_ctrl_2);

	अगर (!ixgbe_mng_present(hw) && !hw->wol_enabled &&
	    ee_ctrl_2 & IXGBE_EEPROM_CCD_BIT) अणु
		स्वतःc2_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
		स्वतःc2_reg |= IXGBE_AUTOC2_LINK_DISABLE_ON_D3_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, स्वतःc2_reg);
	पूर्ण
पूर्ण

/**
 *  ixgbe_start_mac_link_82599 - Setup MAC link settings
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Configures link settings based on values in the ixgbe_hw काष्ठा.
 *  Restarts the link.  Perक्रमms स्वतःnegotiation अगर needed.
 **/
अटल s32 ixgbe_start_mac_link_82599(काष्ठा ixgbe_hw *hw,
			       bool स्वतःneg_रुको_to_complete)
अणु
	u32 स्वतःc_reg;
	u32 links_reg;
	u32 i;
	s32 status = 0;
	bool got_lock = false;

	अगर (ixgbe_verअगरy_lesm_fw_enabled_82599(hw)) अणु
		status = hw->mac.ops.acquire_swfw_sync(hw,
						IXGBE_GSSR_MAC_CSR_SM);
		अगर (status)
			वापस status;

		got_lock = true;
	पूर्ण

	/* Restart link */
	ixgbe_reset_pipeline_82599(hw);

	अगर (got_lock)
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);

	/* Only poll क्रम स्वतःneg to complete अगर specअगरied to करो so */
	अगर (स्वतःneg_रुको_to_complete) अणु
		स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
		अगर ((स्वतःc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR ||
		    (स्वतःc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
		    (स्वतःc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) अणु
			links_reg = 0; /* Just in हाल Autoneg समय = 0 */
			क्रम (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) अणु
				links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
				अगर (links_reg & IXGBE_LINKS_KX_AN_COMP)
					अवरोध;
				msleep(100);
			पूर्ण
			अगर (!(links_reg & IXGBE_LINKS_KX_AN_COMP)) अणु
				status = IXGBE_ERR_AUTONEG_NOT_COMPLETE;
				hw_dbg(hw, "Autoneg did not complete.\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* Add delay to filter out noises during initial link setup */
	msleep(50);

	वापस status;
पूर्ण

/**
 *  ixgbe_disable_tx_laser_multispeed_fiber - Disable Tx laser
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  The base drivers may require better control over SFP+ module
 *  PHY states.  This includes selectively shutting करोwn the Tx
 *  laser on the PHY, effectively halting physical link.
 **/
अटल व्योम ixgbe_disable_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw)
अणु
	u32 esdp_reg = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* Blocked by MNG FW so bail */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस;

	/* Disable tx laser; allow 100us to go dark per spec */
	esdp_reg |= IXGBE_ESDP_SDP3;
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp_reg);
	IXGBE_WRITE_FLUSH(hw);
	udelay(100);
पूर्ण

/**
 *  ixgbe_enable_tx_laser_multispeed_fiber - Enable Tx laser
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  The base drivers may require better control over SFP+ module
 *  PHY states.  This includes selectively turning on the Tx
 *  laser on the PHY, effectively starting physical link.
 **/
अटल व्योम ixgbe_enable_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw)
अणु
	u32 esdp_reg = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* Enable tx laser; allow 100ms to light up */
	esdp_reg &= ~IXGBE_ESDP_SDP3;
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp_reg);
	IXGBE_WRITE_FLUSH(hw);
	msleep(100);
पूर्ण

/**
 *  ixgbe_flap_tx_laser_multispeed_fiber - Flap Tx laser
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  When the driver changes the link speeds that it can support,
 *  it sets स्वतःtry_restart to true to indicate that we need to
 *  initiate a new स्वतःtry session with the link partner.  To करो
 *  so, we set the speed then disable and re-enable the tx laser, to
 *  alert the link partner that it also needs to restart स्वतःtry on its
 *  end.  This is consistent with true clause 37 स्वतःneg, which also
 *  involves a loss of संकेत.
 **/
अटल व्योम ixgbe_flap_tx_laser_multispeed_fiber(काष्ठा ixgbe_hw *hw)
अणु
	/* Blocked by MNG FW so bail */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस;

	अगर (hw->mac.स्वतःtry_restart) अणु
		ixgbe_disable_tx_laser_multispeed_fiber(hw);
		ixgbe_enable_tx_laser_multispeed_fiber(hw);
		hw->mac.स्वतःtry_restart = false;
	पूर्ण
पूर्ण

/**
 * ixgbe_set_hard_rate_select_speed - Set module link speed
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: link speed to set
 *
 * Set module link speed via RS0/RS1 rate select pins.
 */
अटल व्योम
ixgbe_set_hard_rate_select_speed(काष्ठा ixgbe_hw *hw, ixgbe_link_speed speed)
अणु
	u32 esdp_reg = IXGBE_READ_REG(hw, IXGBE_ESDP);

	चयन (speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		esdp_reg |= (IXGBE_ESDP_SDP5_सूची | IXGBE_ESDP_SDP5);
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		esdp_reg &= ~IXGBE_ESDP_SDP5;
		esdp_reg |= IXGBE_ESDP_SDP5_सूची;
		अवरोध;
	शेष:
		hw_dbg(hw, "Invalid fixed module speed\n");
		वापस;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp_reg);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 *  ixgbe_setup_mac_link_smartspeed - Set MAC link speed using SmartSpeed
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Implements the Intel SmartSpeed algorithm.
 **/
अटल s32 ixgbe_setup_mac_link_smartspeed(काष्ठा ixgbe_hw *hw,
				     ixgbe_link_speed speed,
				     bool स्वतःneg_रुको_to_complete)
अणु
	s32 status = 0;
	ixgbe_link_speed link_speed = IXGBE_LINK_SPEED_UNKNOWN;
	s32 i, j;
	bool link_up = false;
	u32 स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);

	 /* Set स्वतःneg_advertised value based on input link speed */
	hw->phy.स्वतःneg_advertised = 0;

	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_100_FULL;

	/*
	 * Implement Intel SmartSpeed algorithm.  SmartSpeed will reduce the
	 * स्वतःneg advertisement अगर link is unable to be established at the
	 * highest negotiated rate.  This can someबार happen due to पूर्णांकegrity
	 * issues with the physical media connection.
	 */

	/* First, try to get link with full advertisement */
	hw->phy.smart_speed_active = false;
	क्रम (j = 0; j < IXGBE_SMARTSPEED_MAX_RETRIES; j++) अणु
		status = ixgbe_setup_mac_link_82599(hw, speed,
						    स्वतःneg_रुको_to_complete);
		अगर (status != 0)
			जाओ out;

		/*
		 * Wait क्रम the controller to acquire link.  Per IEEE 802.3ap,
		 * Section 73.10.2, we may have to रुको up to 500ms अगर KR is
		 * attempted, or 200ms अगर KX/KX4/BX/BX4 is attempted, per
		 * Table 9 in the AN MAS.
		 */
		क्रम (i = 0; i < 5; i++) अणु
			mdelay(100);

			/* If we have link, just jump out */
			status = hw->mac.ops.check_link(hw, &link_speed,
							&link_up, false);
			अगर (status != 0)
				जाओ out;

			अगर (link_up)
				जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We didn't get link.  If we advertised KR plus one of KX4/KX
	 * (or BX4/BX), then disable KR and try again.
	 */
	अगर (((स्वतःc_reg & IXGBE_AUTOC_KR_SUPP) == 0) ||
	    ((स्वतःc_reg & IXGBE_AUTOC_KX4_KX_SUPP_MASK) == 0))
		जाओ out;

	/* Turn SmartSpeed on to disable KR support */
	hw->phy.smart_speed_active = true;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    स्वतःneg_रुको_to_complete);
	अगर (status != 0)
		जाओ out;

	/*
	 * Wait क्रम the controller to acquire link.  600ms will allow क्रम
	 * the AN link_fail_inhibit_समयr as well क्रम multiple cycles of
	 * parallel detect, both 10g and 1g. This allows क्रम the maximum
	 * connect attempts as defined in the AN MAS table 73-7.
	 */
	क्रम (i = 0; i < 6; i++) अणु
		mdelay(100);

		/* If we have link, just jump out */
		status = hw->mac.ops.check_link(hw, &link_speed,
						&link_up, false);
		अगर (status != 0)
			जाओ out;

		अगर (link_up)
			जाओ out;
	पूर्ण

	/* We didn't get link.  Turn SmartSpeed back off. */
	hw->phy.smart_speed_active = false;
	status = ixgbe_setup_mac_link_82599(hw, speed,
					    स्वतःneg_रुको_to_complete);

out:
	अगर (link_up && (link_speed == IXGBE_LINK_SPEED_1GB_FULL))
		hw_dbg(hw, "Smartspeed has downgraded the link speed from the maximum advertised\n");
	वापस status;
पूर्ण

/**
 *  ixgbe_setup_mac_link_82599 - Set MAC link speed
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 *
 *  Set the link speed in the AUTOC रेजिस्टर and restarts link.
 **/
अटल s32 ixgbe_setup_mac_link_82599(काष्ठा ixgbe_hw *hw,
				      ixgbe_link_speed speed,
				      bool स्वतःneg_रुको_to_complete)
अणु
	bool स्वतःneg = false;
	s32 status;
	u32 pma_pmd_1g, link_mode, links_reg, i;
	u32 स्वतःc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	u32 pma_pmd_10g_serial = स्वतःc2 & IXGBE_AUTOC2_10G_SERIAL_PMA_PMD_MASK;
	ixgbe_link_speed link_capabilities = IXGBE_LINK_SPEED_UNKNOWN;

	/* holds the value of AUTOC रेजिस्टर at this current poपूर्णांक in समय */
	u32 current_स्वतःc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	/* holds the cached value of AUTOC रेजिस्टर */
	u32 orig_स्वतःc = 0;
	/* temporary variable used क्रम comparison purposes */
	u32 स्वतःc = current_स्वतःc;

	/* Check to see अगर speed passed in is supported. */
	status = hw->mac.ops.get_link_capabilities(hw, &link_capabilities,
						   &स्वतःneg);
	अगर (status)
		वापस status;

	speed &= link_capabilities;

	अगर (speed == IXGBE_LINK_SPEED_UNKNOWN)
		वापस IXGBE_ERR_LINK_SETUP;

	/* Use stored value (EEPROM शेषs) of AUTOC to find KR/KX4 support*/
	अगर (hw->mac.orig_link_settings_stored)
		orig_स्वतःc = hw->mac.orig_स्वतःc;
	अन्यथा
		orig_स्वतःc = स्वतःc;

	link_mode = स्वतःc & IXGBE_AUTOC_LMS_MASK;
	pma_pmd_1g = स्वतःc & IXGBE_AUTOC_1G_PMA_PMD_MASK;

	अगर (link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR ||
	    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
	    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) अणु
		/* Set KX4/KX/KR support according to speed requested */
		स्वतःc &= ~(IXGBE_AUTOC_KX4_KX_SUPP_MASK | IXGBE_AUTOC_KR_SUPP);
		अगर (speed & IXGBE_LINK_SPEED_10GB_FULL) अणु
			अगर (orig_स्वतःc & IXGBE_AUTOC_KX4_SUPP)
				स्वतःc |= IXGBE_AUTOC_KX4_SUPP;
			अगर ((orig_स्वतःc & IXGBE_AUTOC_KR_SUPP) &&
			    (hw->phy.smart_speed_active == false))
				स्वतःc |= IXGBE_AUTOC_KR_SUPP;
		पूर्ण
		अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
			स्वतःc |= IXGBE_AUTOC_KX_SUPP;
	पूर्ण अन्यथा अगर ((pma_pmd_1g == IXGBE_AUTOC_1G_SFI) &&
		   (link_mode == IXGBE_AUTOC_LMS_1G_LINK_NO_AN ||
		    link_mode == IXGBE_AUTOC_LMS_1G_AN)) अणु
		/* Switch from 1G SFI to 10G SFI अगर requested */
		अगर ((speed == IXGBE_LINK_SPEED_10GB_FULL) &&
		    (pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI)) अणु
			स्वतःc &= ~IXGBE_AUTOC_LMS_MASK;
			स्वतःc |= IXGBE_AUTOC_LMS_10G_SERIAL;
		पूर्ण
	पूर्ण अन्यथा अगर ((pma_pmd_10g_serial == IXGBE_AUTOC2_10G_SFI) &&
		   (link_mode == IXGBE_AUTOC_LMS_10G_SERIAL)) अणु
		/* Switch from 10G SFI to 1G SFI अगर requested */
		अगर ((speed == IXGBE_LINK_SPEED_1GB_FULL) &&
		    (pma_pmd_1g == IXGBE_AUTOC_1G_SFI)) अणु
			स्वतःc &= ~IXGBE_AUTOC_LMS_MASK;
			अगर (स्वतःneg)
				स्वतःc |= IXGBE_AUTOC_LMS_1G_AN;
			अन्यथा
				स्वतःc |= IXGBE_AUTOC_LMS_1G_LINK_NO_AN;
		पूर्ण
	पूर्ण

	अगर (स्वतःc != current_स्वतःc) अणु
		/* Restart link */
		status = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw, स्वतःc, false);
		अगर (status)
			वापस status;

		/* Only poll क्रम स्वतःneg to complete अगर specअगरied to करो so */
		अगर (स्वतःneg_रुको_to_complete) अणु
			अगर (link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR ||
			    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
			    link_mode == IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) अणु
				links_reg = 0; /*Just in हाल Autoneg समय=0*/
				क्रम (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) अणु
					links_reg =
					       IXGBE_READ_REG(hw, IXGBE_LINKS);
					अगर (links_reg & IXGBE_LINKS_KX_AN_COMP)
						अवरोध;
					msleep(100);
				पूर्ण
				अगर (!(links_reg & IXGBE_LINKS_KX_AN_COMP)) अणु
					status =
						IXGBE_ERR_AUTONEG_NOT_COMPLETE;
					hw_dbg(hw, "Autoneg did not complete.\n");
				पूर्ण
			पूर्ण
		पूर्ण

		/* Add delay to filter out noises during initial link setup */
		msleep(50);
	पूर्ण

	वापस status;
पूर्ण

/**
 *  ixgbe_setup_copper_link_82599 - Set the PHY स्वतःneg advertised field
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true अगर रुकोing is needed to complete
 *
 *  Restarts link on PHY and MAC based on settings passed in.
 **/
अटल s32 ixgbe_setup_copper_link_82599(काष्ठा ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool स्वतःneg_रुको_to_complete)
अणु
	s32 status;

	/* Setup the PHY according to input speed */
	status = hw->phy.ops.setup_link_speed(hw, speed,
					      स्वतःneg_रुको_to_complete);
	/* Set up MAC */
	ixgbe_start_mac_link_82599(hw, स्वतःneg_रुको_to_complete);

	वापस status;
पूर्ण

/**
 *  ixgbe_reset_hw_82599 - Perक्रमm hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Resets the hardware by resetting the transmit and receive units, masks
 *  and clears all पूर्णांकerrupts, perक्रमm a PHY reset, and perक्रमm a link (MAC)
 *  reset.
 **/
अटल s32 ixgbe_reset_hw_82599(काष्ठा ixgbe_hw *hw)
अणु
	ixgbe_link_speed link_speed;
	s32 status;
	u32 ctrl, i, स्वतःc, स्वतःc2;
	u32 curr_lms;
	bool link_up = false;

	/* Call adapter stop to disable tx/rx and clear पूर्णांकerrupts */
	status = hw->mac.ops.stop_adapter(hw);
	अगर (status)
		वापस status;

	/* flush pending Tx transactions */
	ixgbe_clear_tx_pending(hw);

	/* PHY ops must be identअगरied and initialized prior to reset */

	/* Identअगरy PHY and related function poपूर्णांकers */
	status = hw->phy.ops.init(hw);

	अगर (status == IXGBE_ERR_SFP_NOT_SUPPORTED)
		वापस status;

	/* Setup SFP module अगर there is one present. */
	अगर (hw->phy.sfp_setup_needed) अणु
		status = hw->mac.ops.setup_sfp(hw);
		hw->phy.sfp_setup_needed = false;
	पूर्ण

	अगर (status == IXGBE_ERR_SFP_NOT_SUPPORTED)
		वापस status;

	/* Reset PHY */
	अगर (hw->phy.reset_disable == false && hw->phy.ops.reset != शून्य)
		hw->phy.ops.reset(hw);

	/* remember AUTOC from beक्रमe we reset */
	curr_lms = IXGBE_READ_REG(hw, IXGBE_AUTOC) & IXGBE_AUTOC_LMS_MASK;

mac_reset_top:
	/*
	 * Issue global reset to the MAC. Needs to be SW reset अगर link is up.
	 * If link reset is used when link is up, it might reset the PHY when
	 * mng is using it.  If link is करोwn or the flag to क्रमce full link
	 * reset is set, then perक्रमm link reset.
	 */
	ctrl = IXGBE_CTRL_LNK_RST;
	अगर (!hw->क्रमce_full_reset) अणु
		hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
		अगर (link_up)
			ctrl = IXGBE_CTRL_RST;
	पूर्ण

	ctrl |= IXGBE_READ_REG(hw, IXGBE_CTRL);
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(1000, 1200);

	/* Poll क्रम reset bit to self-clear indicating reset is complete */
	क्रम (i = 0; i < 10; i++) अणु
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		अगर (!(ctrl & IXGBE_CTRL_RST_MASK))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (ctrl & IXGBE_CTRL_RST_MASK) अणु
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

	/*
	 * Store the original AUTOC/AUTOC2 values अगर they have not been
	 * stored off yet.  Otherwise restore the stored original
	 * values since the reset operation sets back to शेषs.
	 */
	स्वतःc = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	स्वतःc2 = IXGBE_READ_REG(hw, IXGBE_AUTOC2);

	/* Enable link अगर disabled in NVM */
	अगर (स्वतःc2 & IXGBE_AUTOC2_LINK_DISABLE_MASK) अणु
		स्वतःc2 &= ~IXGBE_AUTOC2_LINK_DISABLE_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, स्वतःc2);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	अगर (hw->mac.orig_link_settings_stored == false) अणु
		hw->mac.orig_स्वतःc = स्वतःc;
		hw->mac.orig_स्वतःc2 = स्वतःc2;
		hw->mac.orig_link_settings_stored = true;
	पूर्ण अन्यथा अणु

		/* If MNG FW is running on a multi-speed device that
		 * करोesn't स्वतःneg with out driver support we need to
		 * leave LMS in the state it was beक्रमe we MAC reset.
		 * Likewise अगर we support WoL we करोn't want change the
		 * LMS state either.
		 */
		अगर ((hw->phy.multispeed_fiber && ixgbe_mng_enabled(hw)) ||
		    hw->wol_enabled)
			hw->mac.orig_स्वतःc =
				(hw->mac.orig_स्वतःc & ~IXGBE_AUTOC_LMS_MASK) |
				curr_lms;

		अगर (स्वतःc != hw->mac.orig_स्वतःc) अणु
			status = hw->mac.ops.prot_स्वतःc_ग_लिखो(hw,
							hw->mac.orig_स्वतःc,
							false);
			अगर (status)
				वापस status;
		पूर्ण

		अगर ((स्वतःc2 & IXGBE_AUTOC2_UPPER_MASK) !=
		    (hw->mac.orig_स्वतःc2 & IXGBE_AUTOC2_UPPER_MASK)) अणु
			स्वतःc2 &= ~IXGBE_AUTOC2_UPPER_MASK;
			स्वतःc2 |= (hw->mac.orig_स्वतःc2 &
				   IXGBE_AUTOC2_UPPER_MASK);
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, स्वतःc2);
		पूर्ण
	पूर्ण

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address रेजिस्टरs, and
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modअगरy this value when programming the SAN MAC address.
	 */
	hw->mac.num_rar_entries = IXGBE_82599_RAR_ENTRIES;
	hw->mac.ops.init_rx_addrs(hw);

	/* Store the permanent SAN mac address */
	hw->mac.ops.get_san_mac_addr(hw, hw->mac.san_addr);

	/* Add the SAN MAC address to the RAR only अगर it's a valid address */
	अगर (is_valid_ether_addr(hw->mac.san_addr)) अणु
		/* Save the SAN MAC RAR index */
		hw->mac.san_mac_rar_index = hw->mac.num_rar_entries - 1;

		hw->mac.ops.set_rar(hw, hw->mac.san_mac_rar_index,
				    hw->mac.san_addr, 0, IXGBE_RAH_AV);

		/* clear VMDq pool/queue selection क्रम this RAR */
		hw->mac.ops.clear_vmdq(hw, hw->mac.san_mac_rar_index,
				       IXGBE_CLEAR_VMDQ_ALL);

		/* Reserve the last RAR क्रम the SAN MAC address */
		hw->mac.num_rar_entries--;
	पूर्ण

	/* Store the alternative WWNN/WWPN prefix */
	hw->mac.ops.get_wwn_prefix(hw, &hw->mac.wwnn_prefix,
				       &hw->mac.wwpn_prefix);

	वापस status;
पूर्ण

/**
 * ixgbe_fdir_check_cmd_complete - poll to check whether FसूचीCMD is complete
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @fdircmd: current value of FसूचीCMD रेजिस्टर
 */
अटल s32 ixgbe_fdir_check_cmd_complete(काष्ठा ixgbe_hw *hw, u32 *fdircmd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IXGBE_FसूचीCMD_CMD_POLL; i++) अणु
		*fdircmd = IXGBE_READ_REG(hw, IXGBE_FसूचीCMD);
		अगर (!(*fdircmd & IXGBE_FसूचीCMD_CMD_MASK))
			वापस 0;
		udelay(10);
	पूर्ण

	वापस IXGBE_ERR_Fसूची_CMD_INCOMPLETE;
पूर्ण

/**
 *  ixgbe_reinit_fdir_tables_82599 - Reinitialize Flow Director tables.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_reinit_fdir_tables_82599(काष्ठा ixgbe_hw *hw)
अणु
	पूर्णांक i;
	u32 fdirctrl = IXGBE_READ_REG(hw, IXGBE_FसूचीCTRL);
	u32 fdircmd;
	s32 err;

	fdirctrl &= ~IXGBE_FसूचीCTRL_INIT_DONE;

	/*
	 * Beक्रमe starting reinitialization process,
	 * FसूचीCMD.CMD must be zero.
	 */
	err = ixgbe_fdir_check_cmd_complete(hw, &fdircmd);
	अगर (err) अणु
		hw_dbg(hw, "Flow Director previous command did not complete, aborting table re-initialization.\n");
		वापस err;
	पूर्ण

	IXGBE_WRITE_REG(hw, IXGBE_FसूचीFREE, 0);
	IXGBE_WRITE_FLUSH(hw);
	/*
	 * 82599 adapters flow director init flow cannot be restarted,
	 * Workaround 82599 silicon errata by perक्रमming the following steps
	 * beक्रमe re-writing the FसूचीCTRL control रेजिस्टर with the same value.
	 * - ग_लिखो 1 to bit 8 of FसूचीCMD रेजिस्टर &
	 * - ग_लिखो 0 to bit 8 of FसूचीCMD रेजिस्टर
	 */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCMD,
			(IXGBE_READ_REG(hw, IXGBE_FसूचीCMD) |
			 IXGBE_FसूचीCMD_CLEARHT));
	IXGBE_WRITE_FLUSH(hw);
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCMD,
			(IXGBE_READ_REG(hw, IXGBE_FसूचीCMD) &
			 ~IXGBE_FसूचीCMD_CLEARHT));
	IXGBE_WRITE_FLUSH(hw);
	/*
	 * Clear Fसूची Hash रेजिस्टर to clear any leftover hashes
	 * रुकोing to be programmed.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीHASH, 0x00);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCTRL, fdirctrl);
	IXGBE_WRITE_FLUSH(hw);

	/* Poll init-करोne after we ग_लिखो FसूचीCTRL रेजिस्टर */
	क्रम (i = 0; i < IXGBE_Fसूची_INIT_DONE_POLL; i++) अणु
		अगर (IXGBE_READ_REG(hw, IXGBE_FसूचीCTRL) &
				   IXGBE_FसूचीCTRL_INIT_DONE)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (i >= IXGBE_Fसूची_INIT_DONE_POLL) अणु
		hw_dbg(hw, "Flow Director Signature poll time exceeded!\n");
		वापस IXGBE_ERR_Fसूची_REINIT_FAILED;
	पूर्ण

	/* Clear Fसूची statistics रेजिस्टरs (पढ़ो to clear) */
	IXGBE_READ_REG(hw, IXGBE_FसूचीUSTAT);
	IXGBE_READ_REG(hw, IXGBE_FसूचीFSTAT);
	IXGBE_READ_REG(hw, IXGBE_FसूचीMATCH);
	IXGBE_READ_REG(hw, IXGBE_FसूचीMISS);
	IXGBE_READ_REG(hw, IXGBE_FसूचीLEN);

	वापस 0;
पूर्ण

/**
 *  ixgbe_fdir_enable_82599 - Initialize Flow Director control रेजिस्टरs
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @fdirctrl: value to ग_लिखो to flow director control रेजिस्टर
 **/
अटल व्योम ixgbe_fdir_enable_82599(काष्ठा ixgbe_hw *hw, u32 fdirctrl)
अणु
	पूर्णांक i;

	/* Prime the keys क्रम hashing */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीHKEY, IXGBE_ATR_BUCKET_HASH_KEY);
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीSKEY, IXGBE_ATR_SIGNATURE_HASH_KEY);

	/*
	 * Poll init-करोne after we ग_लिखो the रेजिस्टर.  Estimated बार:
	 *      10G: PBALLOC = 11b, timing is 60us
	 *       1G: PBALLOC = 11b, timing is 600us
	 *     100M: PBALLOC = 11b, timing is 6ms
	 *
	 *     Multiple these timings by 4 अगर under full Rx load
	 *
	 * So we'll poll क्रम IXGBE_Fसूची_INIT_DONE_POLL बार, sleeping क्रम
	 * 1 msec per poll समय.  If we're at line rate and drop to 100M, then
	 * this might not finish in our poll समय, but we can live with that
	 * क्रम now.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCTRL, fdirctrl);
	IXGBE_WRITE_FLUSH(hw);
	क्रम (i = 0; i < IXGBE_Fसूची_INIT_DONE_POLL; i++) अणु
		अगर (IXGBE_READ_REG(hw, IXGBE_FसूचीCTRL) &
				   IXGBE_FसूचीCTRL_INIT_DONE)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (i >= IXGBE_Fसूची_INIT_DONE_POLL)
		hw_dbg(hw, "Flow Director poll time exceeded!\n");
पूर्ण

/**
 *  ixgbe_init_fdir_signature_82599 - Initialize Flow Director signature filters
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @fdirctrl: value to ग_लिखो to flow director control रेजिस्टर, initially
 *             contains just the value of the Rx packet buffer allocation
 **/
s32 ixgbe_init_fdir_signature_82599(काष्ठा ixgbe_hw *hw, u32 fdirctrl)
अणु
	/*
	 * Continue setup of fdirctrl रेजिस्टर bits:
	 *  Move the flexible bytes to use the ethertype - shअगरt 6 words
	 *  Set the maximum length per hash bucket to 0xA filters
	 *  Send पूर्णांकerrupt when 64 filters are left
	 */
	fdirctrl |= (0x6 << IXGBE_FसूचीCTRL_FLEX_SHIFT) |
		    (0xA << IXGBE_FसूचीCTRL_MAX_LENGTH_SHIFT) |
		    (4 << IXGBE_FसूचीCTRL_FULL_THRESH_SHIFT);

	/* ग_लिखो hashes and fdirctrl रेजिस्टर, poll क्रम completion */
	ixgbe_fdir_enable_82599(hw, fdirctrl);

	वापस 0;
पूर्ण

/**
 *  ixgbe_init_fdir_perfect_82599 - Initialize Flow Director perfect filters
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @fdirctrl: value to ग_लिखो to flow director control रेजिस्टर, initially
 *             contains just the value of the Rx packet buffer allocation
 **/
s32 ixgbe_init_fdir_perfect_82599(काष्ठा ixgbe_hw *hw, u32 fdirctrl)
अणु
	/*
	 * Continue setup of fdirctrl रेजिस्टर bits:
	 *  Turn perfect match filtering on
	 *  Initialize the drop queue
	 *  Move the flexible bytes to use the ethertype - shअगरt 6 words
	 *  Set the maximum length per hash bucket to 0xA filters
	 *  Send पूर्णांकerrupt when 64 (0x4 * 16) filters are left
	 */
	fdirctrl |= IXGBE_FसूचीCTRL_PERFECT_MATCH |
		    (IXGBE_Fसूची_DROP_QUEUE << IXGBE_FसूचीCTRL_DROP_Q_SHIFT) |
		    (0x6 << IXGBE_FसूचीCTRL_FLEX_SHIFT) |
		    (0xA << IXGBE_FसूचीCTRL_MAX_LENGTH_SHIFT) |
		    (4 << IXGBE_FसूचीCTRL_FULL_THRESH_SHIFT);

	/* ग_लिखो hashes and fdirctrl रेजिस्टर, poll क्रम completion */
	ixgbe_fdir_enable_82599(hw, fdirctrl);

	वापस 0;
पूर्ण

/*
 * These defines allow us to quickly generate all of the necessary inकाष्ठाions
 * in the function below by simply calling out IXGBE_COMPUTE_SIG_HASH_ITERATION
 * क्रम values 0 through 15
 */
#घोषणा IXGBE_ATR_COMMON_HASH_KEY \
		(IXGBE_ATR_BUCKET_HASH_KEY & IXGBE_ATR_SIGNATURE_HASH_KEY)
#घोषणा IXGBE_COMPUTE_SIG_HASH_ITERATION(_n) \
करो अणु \
	u32 n = (_n); \
	अगर (IXGBE_ATR_COMMON_HASH_KEY & BIT(n)) \
		common_hash ^= lo_hash_dword >> n; \
	अन्यथा अगर (IXGBE_ATR_BUCKET_HASH_KEY & BIT(n)) \
		bucket_hash ^= lo_hash_dword >> n; \
	अन्यथा अगर (IXGBE_ATR_SIGNATURE_HASH_KEY & BIT(n)) \
		sig_hash ^= lo_hash_dword << (16 - n); \
	अगर (IXGBE_ATR_COMMON_HASH_KEY & BIT(n + 16)) \
		common_hash ^= hi_hash_dword >> n; \
	अन्यथा अगर (IXGBE_ATR_BUCKET_HASH_KEY & BIT(n + 16)) \
		bucket_hash ^= hi_hash_dword >> n; \
	अन्यथा अगर (IXGBE_ATR_SIGNATURE_HASH_KEY & BIT(n + 16)) \
		sig_hash ^= hi_hash_dword << (16 - n); \
पूर्ण जबतक (0)

/**
 *  ixgbe_atr_compute_sig_hash_82599 - Compute the signature hash
 *  @input: input bitstream to compute the hash on
 *  @common: compressed common input dword
 *
 *  This function is almost identical to the function above but contains
 *  several optimizations such as unwinding all of the loops, letting the
 *  compiler work out all of the conditional अगरs since the keys are अटल
 *  defines, and computing two keys at once since the hashed dword stream
 *  will be the same क्रम both keys.
 **/
अटल u32 ixgbe_atr_compute_sig_hash_82599(जोड़ ixgbe_atr_hash_dword input,
					    जोड़ ixgbe_atr_hash_dword common)
अणु
	u32 hi_hash_dword, lo_hash_dword, flow_vm_vlan;
	u32 sig_hash = 0, bucket_hash = 0, common_hash = 0;

	/* record the flow_vm_vlan bits as they are a key part to the hash */
	flow_vm_vlan = ntohl(input.dword);

	/* generate common hash dword */
	hi_hash_dword = ntohl(common.dword);

	/* low dword is word swapped version of common */
	lo_hash_dword = (hi_hash_dword >> 16) | (hi_hash_dword << 16);

	/* apply flow ID/VM pool/VLAN ID bits to hash words */
	hi_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan >> 16);

	/* Process bits 0 and 16 */
	IXGBE_COMPUTE_SIG_HASH_ITERATION(0);

	/*
	 * apply flow ID/VM pool/VLAN ID bits to lo hash dword, we had to
	 * delay this because bit 0 of the stream should not be processed
	 * so we करो not add the vlan until after bit 0 was processed
	 */
	lo_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan << 16);

	/* Process reमुख्यing 30 bit of the key */
	IXGBE_COMPUTE_SIG_HASH_ITERATION(1);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(2);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(3);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(4);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(5);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(6);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(7);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(8);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(9);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(10);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(11);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(12);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(13);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(14);
	IXGBE_COMPUTE_SIG_HASH_ITERATION(15);

	/* combine common_hash result with signature and bucket hashes */
	bucket_hash ^= common_hash;
	bucket_hash &= IXGBE_ATR_HASH_MASK;

	sig_hash ^= common_hash << 16;
	sig_hash &= IXGBE_ATR_HASH_MASK << 16;

	/* वापस completed signature hash */
	वापस sig_hash ^ bucket_hash;
पूर्ण

/**
 *  ixgbe_fdir_add_signature_filter_82599 - Adds a signature hash filter
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @input: unique input dword
 *  @common: compressed common input dword
 *  @queue: queue index to direct traffic to
 *
 * Note that the tunnel bit in input must not be set when the hardware
 * tunneling support करोes not exist.
 **/
s32 ixgbe_fdir_add_signature_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_hash_dword input,
					  जोड़ ixgbe_atr_hash_dword common,
					  u8 queue)
अणु
	u64 fdirhashcmd;
	u8 flow_type;
	bool tunnel;
	u32 fdircmd;

	/*
	 * Get the flow_type in order to program FसूचीCMD properly
	 * lowest 2 bits are FसूचीCMD.L4TYPE, third lowest bit is FसूचीCMD.IPV6
	 */
	tunnel = !!(input.क्रमmatted.flow_type & IXGBE_ATR_L4TYPE_TUNNEL_MASK);
	flow_type = input.क्रमmatted.flow_type &
		    (IXGBE_ATR_L4TYPE_TUNNEL_MASK - 1);
	चयन (flow_type) अणु
	हाल IXGBE_ATR_FLOW_TYPE_TCPV4:
	हाल IXGBE_ATR_FLOW_TYPE_UDPV4:
	हाल IXGBE_ATR_FLOW_TYPE_SCTPV4:
	हाल IXGBE_ATR_FLOW_TYPE_TCPV6:
	हाल IXGBE_ATR_FLOW_TYPE_UDPV6:
	हाल IXGBE_ATR_FLOW_TYPE_SCTPV6:
		अवरोध;
	शेष:
		hw_dbg(hw, " Error on flow type input\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	/* configure FसूचीCMD रेजिस्टर */
	fdircmd = IXGBE_FसूचीCMD_CMD_ADD_FLOW | IXGBE_FसूचीCMD_FILTER_UPDATE |
		  IXGBE_FसूचीCMD_LAST | IXGBE_FसूचीCMD_QUEUE_EN;
	fdircmd |= (u32)flow_type << IXGBE_FसूचीCMD_FLOW_TYPE_SHIFT;
	fdircmd |= (u32)queue << IXGBE_FसूचीCMD_RX_QUEUE_SHIFT;
	अगर (tunnel)
		fdircmd |= IXGBE_FसूचीCMD_TUNNEL_FILTER;

	/*
	 * The lower 32-bits of fdirhashcmd is क्रम FसूचीHASH, the upper 32-bits
	 * is क्रम FसूचीCMD.  Then करो a 64-bit रेजिस्टर ग_लिखो from FसूचीHASH.
	 */
	fdirhashcmd = (u64)fdircmd << 32;
	fdirhashcmd |= ixgbe_atr_compute_sig_hash_82599(input, common);
	IXGBE_WRITE_REG64(hw, IXGBE_FसूचीHASH, fdirhashcmd);

	hw_dbg(hw, "Tx Queue=%x hash=%x\n", queue, (u32)fdirhashcmd);

	वापस 0;
पूर्ण

#घोषणा IXGBE_COMPUTE_BKT_HASH_ITERATION(_n) \
करो अणु \
	u32 n = (_n); \
	अगर (IXGBE_ATR_BUCKET_HASH_KEY & BIT(n)) \
		bucket_hash ^= lo_hash_dword >> n; \
	अगर (IXGBE_ATR_BUCKET_HASH_KEY & BIT(n + 16)) \
		bucket_hash ^= hi_hash_dword >> n; \
पूर्ण जबतक (0)

/**
 *  ixgbe_atr_compute_perfect_hash_82599 - Compute the perfect filter hash
 *  @input: input bitstream to compute the hash on
 *  @input_mask: mask क्रम the input bitstream
 *
 *  This function serves two मुख्य purposes.  First it applies the input_mask
 *  to the atr_input resulting in a cleaned up atr_input data stream.
 *  Secondly it computes the hash and stores it in the bkt_hash field at
 *  the end of the input byte stream.  This way it will be available क्रम
 *  future use without needing to recompute the hash.
 **/
व्योम ixgbe_atr_compute_perfect_hash_82599(जोड़ ixgbe_atr_input *input,
					  जोड़ ixgbe_atr_input *input_mask)
अणु

	u32 hi_hash_dword, lo_hash_dword, flow_vm_vlan;
	u32 bucket_hash = 0;
	__be32 hi_dword = 0;
	पूर्णांक i;

	/* Apply masks to input data */
	क्रम (i = 0; i <= 10; i++)
		input->dword_stream[i] &= input_mask->dword_stream[i];

	/* record the flow_vm_vlan bits as they are a key part to the hash */
	flow_vm_vlan = ntohl(input->dword_stream[0]);

	/* generate common hash dword */
	क्रम (i = 1; i <= 10; i++)
		hi_dword ^= input->dword_stream[i];
	hi_hash_dword = ntohl(hi_dword);

	/* low dword is word swapped version of common */
	lo_hash_dword = (hi_hash_dword >> 16) | (hi_hash_dword << 16);

	/* apply flow ID/VM pool/VLAN ID bits to hash words */
	hi_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan >> 16);

	/* Process bits 0 and 16 */
	IXGBE_COMPUTE_BKT_HASH_ITERATION(0);

	/*
	 * apply flow ID/VM pool/VLAN ID bits to lo hash dword, we had to
	 * delay this because bit 0 of the stream should not be processed
	 * so we करो not add the vlan until after bit 0 was processed
	 */
	lo_hash_dword ^= flow_vm_vlan ^ (flow_vm_vlan << 16);

	/* Process reमुख्यing 30 bit of the key */
	क्रम (i = 1; i <= 15; i++)
		IXGBE_COMPUTE_BKT_HASH_ITERATION(i);

	/*
	 * Limit hash to 13 bits since max bucket count is 8K.
	 * Store result at the end of the input stream.
	 */
	input->क्रमmatted.bkt_hash = (__क्रमce __be16)(bucket_hash & 0x1FFF);
पूर्ण

/**
 *  ixgbe_get_fdirtcpm_82599 - generate a tcp port from atr_input_masks
 *  @input_mask: mask to be bit swapped
 *
 *  The source and destination port masks क्रम flow director are bit swapped
 *  in that bit 15 effects bit 0, 14 effects 1, 13, 2 etc.  In order to
 *  generate a correctly swapped value we need to bit swap the mask and that
 *  is what is accomplished by this function.
 **/
अटल u32 ixgbe_get_fdirtcpm_82599(जोड़ ixgbe_atr_input *input_mask)
अणु
	u32 mask = ntohs(input_mask->क्रमmatted.dst_port);

	mask <<= IXGBE_FसूचीTCPM_DPORTM_SHIFT;
	mask |= ntohs(input_mask->क्रमmatted.src_port);
	mask = ((mask & 0x55555555) << 1) | ((mask & 0xAAAAAAAA) >> 1);
	mask = ((mask & 0x33333333) << 2) | ((mask & 0xCCCCCCCC) >> 2);
	mask = ((mask & 0x0F0F0F0F) << 4) | ((mask & 0xF0F0F0F0) >> 4);
	वापस ((mask & 0x00FF00FF) << 8) | ((mask & 0xFF00FF00) >> 8);
पूर्ण

/*
 * These two macros are meant to address the fact that we have रेजिस्टरs
 * that are either all or in part big-endian.  As a result on big-endian
 * प्रणालीs we will end up byte swapping the value to little-endian beक्रमe
 * it is byte swapped again and written to the hardware in the original
 * big-endian क्रमmat.
 */
#घोषणा IXGBE_STORE_AS_BE32(_value) \
	(((u32)(_value) >> 24) | (((u32)(_value) & 0x00FF0000) >> 8) | \
	 (((u32)(_value) & 0x0000FF00) << 8) | ((u32)(_value) << 24))

#घोषणा IXGBE_WRITE_REG_BE32(a, reg, value) \
	IXGBE_WRITE_REG((a), (reg), IXGBE_STORE_AS_BE32(ntohl(value)))

#घोषणा IXGBE_STORE_AS_BE16(_value) \
	ntohs(((u16)(_value) >> 8) | ((u16)(_value) << 8))

s32 ixgbe_fdir_set_input_mask_82599(काष्ठा ixgbe_hw *hw,
				    जोड़ ixgbe_atr_input *input_mask)
अणु
	/* mask IPv6 since it is currently not supported */
	u32 fdirm = IXGBE_FसूचीM_DIPv6;
	u32 fdirtcpm;

	/*
	 * Program the relevant mask रेजिस्टरs.  If src/dst_port or src/dst_addr
	 * are zero, then assume a full mask क्रम that field.  Also assume that
	 * a VLAN of 0 is unspecअगरied, so mask that out as well.  L4type
	 * cannot be masked out in this implementation.
	 *
	 * This also assumes IPv4 only.  IPv6 masking isn't supported at this
	 * poपूर्णांक in समय.
	 */

	/* verअगरy bucket hash is cleared on hash generation */
	अगर (input_mask->क्रमmatted.bkt_hash)
		hw_dbg(hw, " bucket hash should always be 0 in mask\n");

	/* Program FसूचीM and verअगरy partial masks */
	चयन (input_mask->क्रमmatted.vm_pool & 0x7F) अणु
	हाल 0x0:
		fdirm |= IXGBE_FसूचीM_POOL;
		अवरोध;
	हाल 0x7F:
		अवरोध;
	शेष:
		hw_dbg(hw, " Error on vm pool mask\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	चयन (input_mask->क्रमmatted.flow_type & IXGBE_ATR_L4TYPE_MASK) अणु
	हाल 0x0:
		fdirm |= IXGBE_FसूचीM_L4P;
		अगर (input_mask->क्रमmatted.dst_port ||
		    input_mask->क्रमmatted.src_port) अणु
			hw_dbg(hw, " Error on src/dst port mask\n");
			वापस IXGBE_ERR_CONFIG;
		पूर्ण
		अवरोध;
	हाल IXGBE_ATR_L4TYPE_MASK:
		अवरोध;
	शेष:
		hw_dbg(hw, " Error on flow type mask\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	चयन (ntohs(input_mask->क्रमmatted.vlan_id) & 0xEFFF) अणु
	हाल 0x0000:
		/* mask VLAN ID */
		fdirm |= IXGBE_FसूचीM_VLANID;
		fallthrough;
	हाल 0x0FFF:
		/* mask VLAN priority */
		fdirm |= IXGBE_FसूचीM_VLANP;
		अवरोध;
	हाल 0xE000:
		/* mask VLAN ID only */
		fdirm |= IXGBE_FसूचीM_VLANID;
		fallthrough;
	हाल 0xEFFF:
		/* no VLAN fields masked */
		अवरोध;
	शेष:
		hw_dbg(hw, " Error on VLAN mask\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	चयन ((__क्रमce u16)input_mask->क्रमmatted.flex_bytes & 0xFFFF) अणु
	हाल 0x0000:
		/* Mask Flex Bytes */
		fdirm |= IXGBE_FसूचीM_FLEX;
		fallthrough;
	हाल 0xFFFF:
		अवरोध;
	शेष:
		hw_dbg(hw, " Error on flexible byte mask\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	/* Now mask VM pool and destination IPv6 - bits 5 and 2 */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीM, fdirm);

	/* store the TCP/UDP port masks, bit reversed from port layout */
	fdirtcpm = ixgbe_get_fdirtcpm_82599(input_mask);

	/* ग_लिखो both the same so that UDP and TCP use the same mask */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीTCPM, ~fdirtcpm);
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीUDPM, ~fdirtcpm);

	/* also use it क्रम SCTP */
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		IXGBE_WRITE_REG(hw, IXGBE_FसूचीSCTPM, ~fdirtcpm);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* store source and destination IP masks (big-enian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीSIP4M,
			     ~input_mask->क्रमmatted.src_ip[0]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीDIP4M,
			     ~input_mask->क्रमmatted.dst_ip[0]);

	वापस 0;
पूर्ण

s32 ixgbe_fdir_ग_लिखो_perfect_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_input *input,
					  u16 soft_id, u8 queue)
अणु
	u32 fdirport, fdirvlan, fdirhash, fdircmd;
	s32 err;

	/* currently IPv6 is not supported, must be programmed with 0 */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीSIPv6(0),
			     input->क्रमmatted.src_ip[0]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीSIPv6(1),
			     input->क्रमmatted.src_ip[1]);
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीSIPv6(2),
			     input->क्रमmatted.src_ip[2]);

	/* record the source address (big-endian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीIPSA, input->क्रमmatted.src_ip[0]);

	/* record the first 32 bits of the destination address (big-endian) */
	IXGBE_WRITE_REG_BE32(hw, IXGBE_FसूचीIPDA, input->क्रमmatted.dst_ip[0]);

	/* record source and destination port (little-endian)*/
	fdirport = ntohs(input->क्रमmatted.dst_port);
	fdirport <<= IXGBE_FसूचीPORT_DESTINATION_SHIFT;
	fdirport |= ntohs(input->क्रमmatted.src_port);
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीPORT, fdirport);

	/* record vlan (little-endian) and flex_bytes(big-endian) */
	fdirvlan = IXGBE_STORE_AS_BE16((__क्रमce u16)input->क्रमmatted.flex_bytes);
	fdirvlan <<= IXGBE_FसूचीVLAN_FLEX_SHIFT;
	fdirvlan |= ntohs(input->क्रमmatted.vlan_id);
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीVLAN, fdirvlan);

	/* configure FसूचीHASH रेजिस्टर */
	fdirhash = (__क्रमce u32)input->क्रमmatted.bkt_hash;
	fdirhash |= soft_id << IXGBE_FसूचीHASH_SIG_SW_INDEX_SHIFT;
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीHASH, fdirhash);

	/*
	 * flush all previous ग_लिखोs to make certain रेजिस्टरs are
	 * programmed prior to issuing the command
	 */
	IXGBE_WRITE_FLUSH(hw);

	/* configure FसूचीCMD रेजिस्टर */
	fdircmd = IXGBE_FसूचीCMD_CMD_ADD_FLOW | IXGBE_FसूचीCMD_FILTER_UPDATE |
		  IXGBE_FसूचीCMD_LAST | IXGBE_FसूचीCMD_QUEUE_EN;
	अगर (queue == IXGBE_Fसूची_DROP_QUEUE)
		fdircmd |= IXGBE_FसूचीCMD_DROP;
	fdircmd |= input->क्रमmatted.flow_type << IXGBE_FसूचीCMD_FLOW_TYPE_SHIFT;
	fdircmd |= (u32)queue << IXGBE_FसूचीCMD_RX_QUEUE_SHIFT;
	fdircmd |= (u32)input->क्रमmatted.vm_pool << IXGBE_FसूचीCMD_VT_POOL_SHIFT;

	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCMD, fdircmd);
	err = ixgbe_fdir_check_cmd_complete(hw, &fdircmd);
	अगर (err) अणु
		hw_dbg(hw, "Flow Director command did not complete!\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

s32 ixgbe_fdir_erase_perfect_filter_82599(काष्ठा ixgbe_hw *hw,
					  जोड़ ixgbe_atr_input *input,
					  u16 soft_id)
अणु
	u32 fdirhash;
	u32 fdircmd;
	s32 err;

	/* configure FसूचीHASH रेजिस्टर */
	fdirhash = (__क्रमce u32)input->क्रमmatted.bkt_hash;
	fdirhash |= soft_id << IXGBE_FसूचीHASH_SIG_SW_INDEX_SHIFT;
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीHASH, fdirhash);

	/* flush hash to HW */
	IXGBE_WRITE_FLUSH(hw);

	/* Query अगर filter is present */
	IXGBE_WRITE_REG(hw, IXGBE_FसूचीCMD, IXGBE_FसूचीCMD_CMD_QUERY_REM_FILT);

	err = ixgbe_fdir_check_cmd_complete(hw, &fdircmd);
	अगर (err) अणु
		hw_dbg(hw, "Flow Director command did not complete!\n");
		वापस err;
	पूर्ण

	/* अगर filter exists in hardware then हटाओ it */
	अगर (fdircmd & IXGBE_FसूचीCMD_FILTER_VALID) अणु
		IXGBE_WRITE_REG(hw, IXGBE_FसूचीHASH, fdirhash);
		IXGBE_WRITE_FLUSH(hw);
		IXGBE_WRITE_REG(hw, IXGBE_FसूचीCMD,
				IXGBE_FसूचीCMD_CMD_REMOVE_FLOW);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_analog_reg8_82599 - Reads 8 bit Omer analog रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg: analog रेजिस्टर to पढ़ो
 *  @val: पढ़ो value
 *
 *  Perक्रमms पढ़ो operation to Omer analog रेजिस्टर specअगरied.
 **/
अटल s32 ixgbe_पढ़ो_analog_reg8_82599(काष्ठा ixgbe_hw *hw, u32 reg, u8 *val)
अणु
	u32  core_ctl;

	IXGBE_WRITE_REG(hw, IXGBE_CORECTL, IXGBE_CORECTL_WRITE_CMD |
			(reg << 8));
	IXGBE_WRITE_FLUSH(hw);
	udelay(10);
	core_ctl = IXGBE_READ_REG(hw, IXGBE_CORECTL);
	*val = (u8)core_ctl;

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_analog_reg8_82599 - Writes 8 bit Omer analog रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg: atlas रेजिस्टर to ग_लिखो
 *  @val: value to ग_लिखो
 *
 *  Perक्रमms ग_लिखो operation to Omer analog रेजिस्टर specअगरied.
 **/
अटल s32 ixgbe_ग_लिखो_analog_reg8_82599(काष्ठा ixgbe_hw *hw, u32 reg, u8 val)
अणु
	u32  core_ctl;

	core_ctl = (reg << 8) | val;
	IXGBE_WRITE_REG(hw, IXGBE_CORECTL, core_ctl);
	IXGBE_WRITE_FLUSH(hw);
	udelay(10);

	वापस 0;
पूर्ण

/**
 *  ixgbe_start_hw_82599 - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Starts the hardware using the generic start_hw function
 *  and the generation start_hw function.
 *  Then perक्रमms revision-specअगरic operations, अगर any.
 **/
अटल s32 ixgbe_start_hw_82599(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val = 0;

	ret_val = ixgbe_start_hw_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = ixgbe_start_hw_gen2(hw);
	अगर (ret_val)
		वापस ret_val;

	/* We need to run link स्वतःtry after the driver loads */
	hw->mac.स्वतःtry_restart = true;

	वापस ixgbe_verअगरy_fw_version_82599(hw);
पूर्ण

/**
 *  ixgbe_identअगरy_phy_82599 - Get physical layer module
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Determines the physical layer module found on the current adapter.
 *  If PHY alपढ़ोy detected, मुख्यtains current PHY type in hw काष्ठा,
 *  otherwise executes the PHY detection routine.
 **/
अटल s32 ixgbe_identअगरy_phy_82599(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;

	/* Detect PHY अगर not unknown - वापसs success अगर alपढ़ोy detected. */
	status = ixgbe_identअगरy_phy_generic(hw);
	अगर (status) अणु
		/* 82599 10GBASE-T requires an बाह्यal PHY */
		अगर (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_copper)
			वापस status;
		status = ixgbe_identअगरy_module_generic(hw);
	पूर्ण

	/* Set PHY type none अगर no PHY detected */
	अगर (hw->phy.type == ixgbe_phy_unknown) अणु
		hw->phy.type = ixgbe_phy_none;
		status = 0;
	पूर्ण

	/* Return error अगर SFP module has been detected but is not supported */
	अगर (hw->phy.type == ixgbe_phy_sfp_unsupported)
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;

	वापस status;
पूर्ण

/**
 *  ixgbe_enable_rx_dma_82599 - Enable the Rx DMA unit on 82599
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @regval: रेजिस्टर value to ग_लिखो to RXCTRL
 *
 *  Enables the Rx DMA unit क्रम 82599
 **/
अटल s32 ixgbe_enable_rx_dma_82599(काष्ठा ixgbe_hw *hw, u32 regval)
अणु
	/*
	 * Workaround क्रम 82599 silicon errata when enabling the Rx datapath.
	 * If traffic is incoming beक्रमe we enable the Rx unit, it could hang
	 * the Rx DMA unit.  Thereक्रमe, make sure the security engine is
	 * completely disabled prior to enabling the Rx unit.
	 */
	hw->mac.ops.disable_rx_buff(hw);

	अगर (regval & IXGBE_RXCTRL_RXEN)
		hw->mac.ops.enable_rx(hw);
	अन्यथा
		hw->mac.ops.disable_rx(hw);

	hw->mac.ops.enable_rx_buff(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_verअगरy_fw_version_82599 - verअगरy fw version क्रम 82599
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Verअगरies that installed the firmware version is 0.6 or higher
 *  क्रम SFI devices. All 82599 SFI devices should have version 0.6 or higher.
 *
 *  Returns IXGBE_ERR_EEPROM_VERSION अगर the FW is not present or
 *  अगर the FW version is not supported.
 **/
अटल s32 ixgbe_verअगरy_fw_version_82599(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = IXGBE_ERR_EEPROM_VERSION;
	u16 fw_offset, fw_ptp_cfg_offset;
	u16 offset;
	u16 fw_version = 0;

	/* firmware check is only necessary क्रम SFI devices */
	अगर (hw->phy.media_type != ixgbe_media_type_fiber)
		वापस 0;

	/* get the offset to the Firmware Module block */
	offset = IXGBE_FW_PTR;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, &fw_offset))
		जाओ fw_version_err;

	अगर (fw_offset == 0 || fw_offset == 0xFFFF)
		वापस IXGBE_ERR_EEPROM_VERSION;

	/* get the offset to the Pass Through Patch Configuration block */
	offset = fw_offset + IXGBE_FW_PASSTHROUGH_PATCH_CONFIG_PTR;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, &fw_ptp_cfg_offset))
		जाओ fw_version_err;

	अगर (fw_ptp_cfg_offset == 0 || fw_ptp_cfg_offset == 0xFFFF)
		वापस IXGBE_ERR_EEPROM_VERSION;

	/* get the firmware version */
	offset = fw_ptp_cfg_offset + IXGBE_FW_PATCH_VERSION_4;
	अगर (hw->eeprom.ops.पढ़ो(hw, offset, &fw_version))
		जाओ fw_version_err;

	अगर (fw_version > 0x5)
		status = 0;

	वापस status;

fw_version_err:
	hw_err(hw, "eeprom read at offset %d failed\n", offset);
	वापस IXGBE_ERR_EEPROM_VERSION;
पूर्ण

/**
 *  ixgbe_verअगरy_lesm_fw_enabled_82599 - Checks LESM FW module state.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns true अगर the LESM FW module is present and enabled. Otherwise
 *  वापसs false. Smart Speed must be disabled अगर LESM FW module is enabled.
 **/
अटल bool ixgbe_verअगरy_lesm_fw_enabled_82599(काष्ठा ixgbe_hw *hw)
अणु
	u16 fw_offset, fw_lesm_param_offset, fw_lesm_state;
	s32 status;

	/* get the offset to the Firmware Module block */
	status = hw->eeprom.ops.पढ़ो(hw, IXGBE_FW_PTR, &fw_offset);

	अगर (status || fw_offset == 0 || fw_offset == 0xFFFF)
		वापस false;

	/* get the offset to the LESM Parameters block */
	status = hw->eeprom.ops.पढ़ो(hw, (fw_offset +
				     IXGBE_FW_LESM_PARAMETERS_PTR),
				     &fw_lesm_param_offset);

	अगर (status ||
	    fw_lesm_param_offset == 0 || fw_lesm_param_offset == 0xFFFF)
		वापस false;

	/* get the lesm state word */
	status = hw->eeprom.ops.पढ़ो(hw, (fw_lesm_param_offset +
				     IXGBE_FW_LESM_STATE_1),
				     &fw_lesm_state);

	अगर (!status && (fw_lesm_state & IXGBE_FW_LESM_STATE_ENABLED))
		वापस true;

	वापस false;
पूर्ण

/**
 *  ixgbe_पढ़ो_eeprom_buffer_82599 - Read EEPROM word(s) using
 *  fastest available method
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in EEPROM to पढ़ो
 *  @words: number of words
 *  @data: word(s) पढ़ो from the EEPROM
 *
 *  Retrieves 16 bit word(s) पढ़ो from EEPROM
 **/
अटल s32 ixgbe_पढ़ो_eeprom_buffer_82599(काष्ठा ixgbe_hw *hw, u16 offset,
					  u16 words, u16 *data)
अणु
	काष्ठा ixgbe_eeprom_info *eeprom = &hw->eeprom;

	/* If EEPROM is detected and can be addressed using 14 bits,
	 * use EERD otherwise use bit bang
	 */
	अगर (eeprom->type == ixgbe_eeprom_spi &&
	    offset + (words - 1) <= IXGBE_EERD_MAX_ADDR)
		वापस ixgbe_पढ़ो_eerd_buffer_generic(hw, offset, words, data);

	वापस ixgbe_पढ़ो_eeprom_buffer_bit_bang_generic(hw, offset, words,
							 data);
पूर्ण

/**
 *  ixgbe_पढ़ो_eeprom_82599 - Read EEPROM word using
 *  fastest available method
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM
 **/
अटल s32 ixgbe_पढ़ो_eeprom_82599(काष्ठा ixgbe_hw *hw,
				   u16 offset, u16 *data)
अणु
	काष्ठा ixgbe_eeprom_info *eeprom = &hw->eeprom;

	/*
	 * If EEPROM is detected and can be addressed using 14 bits,
	 * use EERD otherwise use bit bang
	 */
	अगर (eeprom->type == ixgbe_eeprom_spi && offset <= IXGBE_EERD_MAX_ADDR)
		वापस ixgbe_पढ़ो_eerd_generic(hw, offset, data);

	वापस ixgbe_पढ़ो_eeprom_bit_bang_generic(hw, offset, data);
पूर्ण

/**
 * ixgbe_reset_pipeline_82599 - perक्रमm pipeline reset
 *
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Reset pipeline by निश्चितing Restart_AN together with LMS change to ensure
 * full pipeline reset.  Note - We must hold the SW/FW semaphore beक्रमe writing
 * to AUTOC, so this function assumes the semaphore is held.
 **/
अटल s32 ixgbe_reset_pipeline_82599(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val;
	u32 anlp1_reg = 0;
	u32 i, स्वतःc_reg, स्वतःc2_reg;

	/* Enable link अगर disabled in NVM */
	स्वतःc2_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	अगर (स्वतःc2_reg & IXGBE_AUTOC2_LINK_DISABLE_MASK) अणु
		स्वतःc2_reg &= ~IXGBE_AUTOC2_LINK_DISABLE_MASK;
		IXGBE_WRITE_REG(hw, IXGBE_AUTOC2, स्वतःc2_reg);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	स्वतःc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	स्वतःc_reg |= IXGBE_AUTOC_AN_RESTART;

	/* Write AUTOC रेजिस्टर with toggled LMS[2] bit and Restart_AN */
	IXGBE_WRITE_REG(hw, IXGBE_AUTOC,
			स्वतःc_reg ^ (0x4 << IXGBE_AUTOC_LMS_SHIFT));

	/* Wait क्रम AN to leave state 0 */
	क्रम (i = 0; i < 10; i++) अणु
		usleep_range(4000, 8000);
		anlp1_reg = IXGBE_READ_REG(hw, IXGBE_ANLP1);
		अगर (anlp1_reg & IXGBE_ANLP1_AN_STATE_MASK)
			अवरोध;
	पूर्ण

	अगर (!(anlp1_reg & IXGBE_ANLP1_AN_STATE_MASK)) अणु
		hw_dbg(hw, "auto negotiation not completed\n");
		ret_val = IXGBE_ERR_RESET_FAILED;
		जाओ reset_pipeline_out;
	पूर्ण

	ret_val = 0;

reset_pipeline_out:
	/* Write AUTOC रेजिस्टर with original LMS field and Restart_AN */
	IXGBE_WRITE_REG(hw, IXGBE_AUTOC, स्वतःc_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस ret_val;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_byte_82599 - Reads 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to पढ़ो
 *  @dev_addr: address to पढ़ो from
 *  @data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 **/
अटल s32 ixgbe_पढ़ो_i2c_byte_82599(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				     u8 dev_addr, u8 *data)
अणु
	u32 esdp;
	s32 status;
	s32 समयout = 200;

	अगर (hw->phy.qsfp_shared_i2c_bus == true) अणु
		/* Acquire I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);

		जबतक (समयout) अणु
			esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
			अगर (esdp & IXGBE_ESDP_SDP1)
				अवरोध;

			usleep_range(5000, 10000);
			समयout--;
		पूर्ण

		अगर (!समयout) अणु
			hw_dbg(hw, "Driver can't access resource, acquiring I2C bus timeout.\n");
			status = IXGBE_ERR_I2C;
			जाओ release_i2c_access;
		पूर्ण
	पूर्ण

	status = ixgbe_पढ़ो_i2c_byte_generic(hw, byte_offset, dev_addr, data);

release_i2c_access:
	अगर (hw->phy.qsfp_shared_i2c_bus == true) अणु
		/* Release I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp &= ~IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_byte_82599 - Writes 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to ग_लिखो
 *  @dev_addr: address to ग_लिखो to
 *  @data: value to ग_लिखो
 *
 *  Perक्रमms byte ग_लिखो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 **/
अटल s32 ixgbe_ग_लिखो_i2c_byte_82599(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				      u8 dev_addr, u8 data)
अणु
	u32 esdp;
	s32 status;
	s32 समयout = 200;

	अगर (hw->phy.qsfp_shared_i2c_bus == true) अणु
		/* Acquire I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);

		जबतक (समयout) अणु
			esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
			अगर (esdp & IXGBE_ESDP_SDP1)
				अवरोध;

			usleep_range(5000, 10000);
			समयout--;
		पूर्ण

		अगर (!समयout) अणु
			hw_dbg(hw, "Driver can't access resource, acquiring I2C bus timeout.\n");
			status = IXGBE_ERR_I2C;
			जाओ release_i2c_access;
		पूर्ण
	पूर्ण

	status = ixgbe_ग_लिखो_i2c_byte_generic(hw, byte_offset, dev_addr, data);

release_i2c_access:
	अगर (hw->phy.qsfp_shared_i2c_bus == true) अणु
		/* Release I2C bus ownership. */
		esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
		esdp &= ~IXGBE_ESDP_SDP0;
		IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	वापस status;
पूर्ण

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_82599 = अणु
	.init_hw                = &ixgbe_init_hw_generic,
	.reset_hw               = &ixgbe_reset_hw_82599,
	.start_hw               = &ixgbe_start_hw_82599,
	.clear_hw_cntrs         = &ixgbe_clear_hw_cntrs_generic,
	.get_media_type         = &ixgbe_get_media_type_82599,
	.enable_rx_dma          = &ixgbe_enable_rx_dma_82599,
	.disable_rx_buff	= &ixgbe_disable_rx_buff_generic,
	.enable_rx_buff		= &ixgbe_enable_rx_buff_generic,
	.get_mac_addr           = &ixgbe_get_mac_addr_generic,
	.get_san_mac_addr       = &ixgbe_get_san_mac_addr_generic,
	.get_device_caps        = &ixgbe_get_device_caps_generic,
	.get_wwn_prefix         = &ixgbe_get_wwn_prefix_generic,
	.stop_adapter           = &ixgbe_stop_adapter_generic,
	.get_bus_info           = &ixgbe_get_bus_info_generic,
	.set_lan_id             = &ixgbe_set_lan_id_multi_port_pcie,
	.पढ़ो_analog_reg8       = &ixgbe_पढ़ो_analog_reg8_82599,
	.ग_लिखो_analog_reg8      = &ixgbe_ग_लिखो_analog_reg8_82599,
	.stop_link_on_d3	= &ixgbe_stop_mac_link_on_d3_82599,
	.setup_link             = &ixgbe_setup_mac_link_82599,
	.set_rxpba		= &ixgbe_set_rxpba_generic,
	.check_link             = &ixgbe_check_mac_link_generic,
	.get_link_capabilities  = &ixgbe_get_link_capabilities_82599,
	.led_on                 = &ixgbe_led_on_generic,
	.led_off                = &ixgbe_led_off_generic,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.blink_led_start        = &ixgbe_blink_led_start_generic,
	.blink_led_stop         = &ixgbe_blink_led_stop_generic,
	.set_rar                = &ixgbe_set_rar_generic,
	.clear_rar              = &ixgbe_clear_rar_generic,
	.set_vmdq               = &ixgbe_set_vmdq_generic,
	.set_vmdq_san_mac	= &ixgbe_set_vmdq_san_mac_generic,
	.clear_vmdq             = &ixgbe_clear_vmdq_generic,
	.init_rx_addrs          = &ixgbe_init_rx_addrs_generic,
	.update_mc_addr_list    = &ixgbe_update_mc_addr_list_generic,
	.enable_mc              = &ixgbe_enable_mc_generic,
	.disable_mc             = &ixgbe_disable_mc_generic,
	.clear_vfta             = &ixgbe_clear_vfta_generic,
	.set_vfta               = &ixgbe_set_vfta_generic,
	.fc_enable              = &ixgbe_fc_enable_generic,
	.setup_fc		= ixgbe_setup_fc_generic,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.set_fw_drv_ver         = &ixgbe_set_fw_drv_ver_generic,
	.init_uta_tables        = &ixgbe_init_uta_tables_generic,
	.setup_sfp              = &ixgbe_setup_sfp_modules_82599,
	.set_mac_anti_spoofing  = &ixgbe_set_mac_anti_spoofing,
	.set_vlan_anti_spoofing = &ixgbe_set_vlan_anti_spoofing,
	.acquire_swfw_sync      = &ixgbe_acquire_swfw_sync,
	.release_swfw_sync      = &ixgbe_release_swfw_sync,
	.init_swfw_sync		= शून्य,
	.get_thermal_sensor_data = &ixgbe_get_thermal_sensor_data_generic,
	.init_thermal_sensor_thresh = &ixgbe_init_thermal_sensor_thresh_generic,
	.prot_स्वतःc_पढ़ो	= &prot_स्वतःc_पढ़ो_82599,
	.prot_स्वतःc_ग_लिखो	= &prot_स्वतःc_ग_लिखो_82599,
	.enable_rx		= &ixgbe_enable_rx_generic,
	.disable_rx		= &ixgbe_disable_rx_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_eeprom_operations eeprom_ops_82599 = अणु
	.init_params		= &ixgbe_init_eeprom_params_generic,
	.पढ़ो			= &ixgbe_पढ़ो_eeprom_82599,
	.पढ़ो_buffer		= &ixgbe_पढ़ो_eeprom_buffer_82599,
	.ग_लिखो			= &ixgbe_ग_लिखो_eeprom_generic,
	.ग_लिखो_buffer		= &ixgbe_ग_लिखो_eeprom_buffer_bit_bang_generic,
	.calc_checksum		= &ixgbe_calc_eeprom_checksum_generic,
	.validate_checksum	= &ixgbe_validate_eeprom_checksum_generic,
	.update_checksum	= &ixgbe_update_eeprom_checksum_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_82599 = अणु
	.identअगरy		= &ixgbe_identअगरy_phy_82599,
	.identअगरy_sfp		= &ixgbe_identअगरy_module_generic,
	.init			= &ixgbe_init_phy_ops_82599,
	.reset			= &ixgbe_reset_phy_generic,
	.पढ़ो_reg		= &ixgbe_पढ़ो_phy_reg_generic,
	.ग_लिखो_reg		= &ixgbe_ग_लिखो_phy_reg_generic,
	.setup_link		= &ixgbe_setup_phy_link_generic,
	.setup_link_speed	= &ixgbe_setup_phy_link_speed_generic,
	.पढ़ो_i2c_byte		= &ixgbe_पढ़ो_i2c_byte_generic,
	.ग_लिखो_i2c_byte		= &ixgbe_ग_लिखो_i2c_byte_generic,
	.पढ़ो_i2c_sff8472	= &ixgbe_पढ़ो_i2c_sff8472_generic,
	.पढ़ो_i2c_eeprom	= &ixgbe_पढ़ो_i2c_eeprom_generic,
	.ग_लिखो_i2c_eeprom	= &ixgbe_ग_लिखो_i2c_eeprom_generic,
	.check_overtemp		= &ixgbe_tn_check_overtemp,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_82599_info = अणु
	.mac                    = ixgbe_mac_82599EB,
	.get_invariants         = &ixgbe_get_invariants_82599,
	.mac_ops                = &mac_ops_82599,
	.eeprom_ops             = &eeprom_ops_82599,
	.phy_ops                = &phy_ops_82599,
	.mbx_ops                = &mbx_ops_generic,
	.mvals			= ixgbe_mvals_8259X,
पूर्ण;

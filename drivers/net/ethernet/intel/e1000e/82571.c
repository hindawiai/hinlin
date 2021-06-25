<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* 82571EB Gigabit Ethernet Controller
 * 82571EB Gigabit Ethernet Controller (Copper)
 * 82571EB Gigabit Ethernet Controller (Fiber)
 * 82571EB Dual Port Gigabit Mezzanine Adapter
 * 82571EB Quad Port Gigabit Mezzanine Adapter
 * 82571PT Gigabit PT Quad Port Server ExpressModule
 * 82572EI Gigabit Ethernet Controller (Copper)
 * 82572EI Gigabit Ethernet Controller (Fiber)
 * 82572EI Gigabit Ethernet Controller
 * 82573V Gigabit Ethernet Controller (Copper)
 * 82573E Gigabit Ethernet Controller (Copper)
 * 82573L Gigabit Ethernet Controller
 * 82574L Gigabit Network Connection
 * 82583V Gigabit Network Connection
 */

#समावेश "e1000.h"

अटल s32 e1000_get_phy_id_82571(काष्ठा e1000_hw *hw);
अटल s32 e1000_setup_copper_link_82571(काष्ठा e1000_hw *hw);
अटल s32 e1000_setup_fiber_serdes_link_82571(काष्ठा e1000_hw *hw);
अटल s32 e1000_check_क्रम_serdes_link_82571(काष्ठा e1000_hw *hw);
अटल s32 e1000_ग_लिखो_nvm_eewr_82571(काष्ठा e1000_hw *hw, u16 offset,
				      u16 words, u16 *data);
अटल s32 e1000_fix_nvm_checksum_82571(काष्ठा e1000_hw *hw);
अटल व्योम e1000_initialize_hw_bits_82571(काष्ठा e1000_hw *hw);
अटल व्योम e1000_clear_hw_cntrs_82571(काष्ठा e1000_hw *hw);
अटल bool e1000_check_mng_mode_82574(काष्ठा e1000_hw *hw);
अटल s32 e1000_led_on_82574(काष्ठा e1000_hw *hw);
अटल व्योम e1000_put_hw_semaphore_82571(काष्ठा e1000_hw *hw);
अटल व्योम e1000_घातer_करोwn_phy_copper_82571(काष्ठा e1000_hw *hw);
अटल व्योम e1000_put_hw_semaphore_82573(काष्ठा e1000_hw *hw);
अटल s32 e1000_get_hw_semaphore_82574(काष्ठा e1000_hw *hw);
अटल व्योम e1000_put_hw_semaphore_82574(काष्ठा e1000_hw *hw);
अटल s32 e1000_set_d0_lplu_state_82574(काष्ठा e1000_hw *hw, bool active);
अटल s32 e1000_set_d3_lplu_state_82574(काष्ठा e1000_hw *hw, bool active);

/**
 *  e1000_init_phy_params_82571 - Init PHY func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_phy_params_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	अगर (hw->phy.media_type != e1000_media_type_copper) अणु
		phy->type = e1000_phy_none;
		वापस 0;
	पूर्ण

	phy->addr = 1;
	phy->स्वतःneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us = 100;

	phy->ops.घातer_up = e1000_घातer_up_phy_copper;
	phy->ops.घातer_करोwn = e1000_घातer_करोwn_phy_copper_82571;

	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		phy->type = e1000_phy_igp_2;
		अवरोध;
	हाल e1000_82573:
		phy->type = e1000_phy_m88;
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		phy->type = e1000_phy_bm;
		phy->ops.acquire = e1000_get_hw_semaphore_82574;
		phy->ops.release = e1000_put_hw_semaphore_82574;
		phy->ops.set_d0_lplu_state = e1000_set_d0_lplu_state_82574;
		phy->ops.set_d3_lplu_state = e1000_set_d3_lplu_state_82574;
		अवरोध;
	शेष:
		वापस -E1000_ERR_PHY;
	पूर्ण

	/* This can only be करोne after all function poपूर्णांकers are setup. */
	ret_val = e1000_get_phy_id_82571(hw);
	अगर (ret_val) अणु
		e_dbg("Error getting PHY ID\n");
		वापस ret_val;
	पूर्ण

	/* Verअगरy phy id */
	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		अगर (phy->id != IGP01E1000_I_PHY_ID)
			ret_val = -E1000_ERR_PHY;
		अवरोध;
	हाल e1000_82573:
		अगर (phy->id != M88E1111_I_PHY_ID)
			ret_val = -E1000_ERR_PHY;
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		अगर (phy->id != BME1000_E_PHY_ID_R2)
			ret_val = -E1000_ERR_PHY;
		अवरोध;
	शेष:
		ret_val = -E1000_ERR_PHY;
		अवरोध;
	पूर्ण

	अगर (ret_val)
		e_dbg("PHY ID unknown: type = 0x%08x\n", phy->id);

	वापस ret_val;
पूर्ण

/**
 *  e1000_init_nvm_params_82571 - Init NVM func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_nvm_params_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);
	u16 size;

	nvm->opcode_bits = 8;
	nvm->delay_usec = 1;
	चयन (nvm->override) अणु
	हाल e1000_nvm_override_spi_large:
		nvm->page_size = 32;
		nvm->address_bits = 16;
		अवरोध;
	हाल e1000_nvm_override_spi_small:
		nvm->page_size = 8;
		nvm->address_bits = 8;
		अवरोध;
	शेष:
		nvm->page_size = eecd & E1000_EECD_ADDR_BITS ? 32 : 8;
		nvm->address_bits = eecd & E1000_EECD_ADDR_BITS ? 16 : 8;
		अवरोध;
	पूर्ण

	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		अगर (((eecd >> 15) & 0x3) == 0x3) अणु
			nvm->type = e1000_nvm_flash_hw;
			nvm->word_size = 2048;
			/* Autonomous Flash update bit must be cleared due
			 * to Flash update issue.
			 */
			eecd &= ~E1000_EECD_AUPDEN;
			ew32(EECD, eecd);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		nvm->type = e1000_nvm_eeprom_spi;
		size = (u16)((eecd & E1000_EECD_SIZE_EX_MASK) >>
			     E1000_EECD_SIZE_EX_SHIFT);
		/* Added to a स्थिरant, "size" becomes the left-shअगरt value
		 * क्रम setting word_size.
		 */
		size += NVM_WORD_SIZE_BASE_SHIFT;

		/* EEPROM access above 16k is unsupported */
		अगर (size > 14)
			size = 14;
		nvm->word_size = BIT(size);
		अवरोध;
	पूर्ण

	/* Function Poपूर्णांकers */
	चयन (hw->mac.type) अणु
	हाल e1000_82574:
	हाल e1000_82583:
		nvm->ops.acquire = e1000_get_hw_semaphore_82574;
		nvm->ops.release = e1000_put_hw_semaphore_82574;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_init_mac_params_82571 - Init MAC func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_mac_params_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 swsm = 0;
	u32 swsm2 = 0;
	bool क्रमce_clear_smbi = false;

	/* Set media type and media-dependent function poपूर्णांकers */
	चयन (hw->adapter->pdev->device) अणु
	हाल E1000_DEV_ID_82571EB_FIBER:
	हाल E1000_DEV_ID_82572EI_FIBER:
	हाल E1000_DEV_ID_82571EB_QUAD_FIBER:
		hw->phy.media_type = e1000_media_type_fiber;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_क्रम_link = e1000e_check_क्रम_fiber_link;
		mac->ops.get_link_up_info =
		    e1000e_get_speed_and_duplex_fiber_serdes;
		अवरोध;
	हाल E1000_DEV_ID_82571EB_SERDES:
	हाल E1000_DEV_ID_82571EB_SERDES_DUAL:
	हाल E1000_DEV_ID_82571EB_SERDES_QUAD:
	हाल E1000_DEV_ID_82572EI_SERDES:
		hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000_setup_fiber_serdes_link_82571;
		mac->ops.check_क्रम_link = e1000_check_क्रम_serdes_link_82571;
		mac->ops.get_link_up_info =
		    e1000e_get_speed_and_duplex_fiber_serdes;
		अवरोध;
	शेष:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000_setup_copper_link_82571;
		mac->ops.check_क्रम_link = e1000e_check_क्रम_copper_link;
		mac->ops.get_link_up_info = e1000e_get_speed_and_duplex_copper;
		अवरोध;
	पूर्ण

	/* Set mta रेजिस्टर count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* Adaptive IFS supported */
	mac->adaptive_अगरs = true;

	/* MAC-specअगरic function poपूर्णांकers */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000e_check_mng_mode_generic;
		mac->ops.led_on = e1000e_led_on_generic;
		mac->ops.blink_led = e1000e_blink_led_generic;

		/* FWSM रेजिस्टर */
		mac->has_fwsm = true;
		/* ARC supported; valid only अगर manageability features are
		 * enabled.
		 */
		mac->arc_subप्रणाली_valid = !!(er32(FWSM) &
					      E1000_FWSM_MODE_MASK);
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		mac->ops.set_lan_id = e1000_set_lan_id_single_port;
		mac->ops.check_mng_mode = e1000_check_mng_mode_82574;
		mac->ops.led_on = e1000_led_on_82574;
		अवरोध;
	शेष:
		mac->ops.check_mng_mode = e1000e_check_mng_mode_generic;
		mac->ops.led_on = e1000e_led_on_generic;
		mac->ops.blink_led = e1000e_blink_led_generic;

		/* FWSM रेजिस्टर */
		mac->has_fwsm = true;
		अवरोध;
	पूर्ण

	/* Ensure that the पूर्णांकer-port SWSM.SMBI lock bit is clear beक्रमe
	 * first NVM or PHY access. This should be करोne क्रम single-port
	 * devices, and क्रम one port only on dual-port devices so that
	 * क्रम those devices we can still use the SMBI lock to synchronize
	 * पूर्णांकer-port accesses to the PHY & NVM.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		swsm2 = er32(SWSM2);

		अगर (!(swsm2 & E1000_SWSM2_LOCK)) अणु
			/* Only करो this क्रम the first पूर्णांकerface on this card */
			ew32(SWSM2, swsm2 | E1000_SWSM2_LOCK);
			क्रमce_clear_smbi = true;
		पूर्ण अन्यथा अणु
			क्रमce_clear_smbi = false;
		पूर्ण
		अवरोध;
	शेष:
		क्रमce_clear_smbi = true;
		अवरोध;
	पूर्ण

	अगर (क्रमce_clear_smbi) अणु
		/* Make sure SWSM.SMBI is clear */
		swsm = er32(SWSM);
		अगर (swsm & E1000_SWSM_SMBI) अणु
			/* This bit should not be set on a first पूर्णांकerface, and
			 * indicates that the bootagent or EFI code has
			 * improperly left this bit enabled
			 */
			e_dbg("Please update your 82571 Bootagent\n");
		पूर्ण
		ew32(SWSM, swsm & ~E1000_SWSM_SMBI);
	पूर्ण

	/* Initialize device specअगरic counter of SMBI acquisition समयouts. */
	hw->dev_spec.e82571.smb_counter = 0;

	वापस 0;
पूर्ण

अटल s32 e1000_get_variants_82571(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अटल पूर्णांक global_quad_port_a;	/* global port a indication */
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक is_port_b = er32(STATUS) & E1000_STATUS_FUNC_1;
	s32 rc;

	rc = e1000_init_mac_params_82571(hw);
	अगर (rc)
		वापस rc;

	rc = e1000_init_nvm_params_82571(hw);
	अगर (rc)
		वापस rc;

	rc = e1000_init_phy_params_82571(hw);
	अगर (rc)
		वापस rc;

	/* tag quad port adapters first, it's used below */
	चयन (pdev->device) अणु
	हाल E1000_DEV_ID_82571EB_QUAD_COPPER:
	हाल E1000_DEV_ID_82571EB_QUAD_FIBER:
	हाल E1000_DEV_ID_82571EB_QUAD_COPPER_LP:
	हाल E1000_DEV_ID_82571PT_QUAD_COPPER:
		adapter->flags |= FLAG_IS_QUAD_PORT;
		/* mark the first port */
		अगर (global_quad_port_a == 0)
			adapter->flags |= FLAG_IS_QUAD_PORT_A;
		/* Reset क्रम multiple quad port adapters */
		global_quad_port_a++;
		अगर (global_quad_port_a == 4)
			global_quad_port_a = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_82571:
		/* these dual ports करोn't have WoL on port B at all */
		अगर (((pdev->device == E1000_DEV_ID_82571EB_FIBER) ||
		     (pdev->device == E1000_DEV_ID_82571EB_SERDES) ||
		     (pdev->device == E1000_DEV_ID_82571EB_COPPER)) &&
		    (is_port_b))
			adapter->flags &= ~FLAG_HAS_WOL;
		/* quad ports only support WoL on port A */
		अगर (adapter->flags & FLAG_IS_QUAD_PORT &&
		    (!(adapter->flags & FLAG_IS_QUAD_PORT_A)))
			adapter->flags &= ~FLAG_HAS_WOL;
		/* Does not support WoL on any port */
		अगर (pdev->device == E1000_DEV_ID_82571EB_SERDES_QUAD)
			adapter->flags &= ~FLAG_HAS_WOL;
		अवरोध;
	हाल e1000_82573:
		अगर (pdev->device == E1000_DEV_ID_82573L) अणु
			adapter->flags |= FLAG_HAS_JUMBO_FRAMES;
			adapter->max_hw_frame_size = DEFAULT_JUMBO;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_get_phy_id_82571 - Retrieve the PHY ID and revision
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the PHY रेजिस्टरs and stores the PHY ID and possibly the PHY
 *  revision in the hardware काष्ठाure.
 **/
अटल s32 e1000_get_phy_id_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_id = 0;

	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		/* The 82571 firmware may still be configuring the PHY.
		 * In this हाल, we cannot access the PHY until the
		 * configuration is करोne.  So we explicitly set the
		 * PHY ID.
		 */
		phy->id = IGP01E1000_I_PHY_ID;
		अवरोध;
	हाल e1000_82573:
		वापस e1000e_get_phy_id(hw);
	हाल e1000_82574:
	हाल e1000_82583:
		ret_val = e1e_rphy(hw, MII_PHYSID1, &phy_id);
		अगर (ret_val)
			वापस ret_val;

		phy->id = (u32)(phy_id << 16);
		usleep_range(20, 40);
		ret_val = e1e_rphy(hw, MII_PHYSID2, &phy_id);
		अगर (ret_val)
			वापस ret_val;

		phy->id |= (u32)(phy_id);
		phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);
		अवरोध;
	शेष:
		वापस -E1000_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_get_hw_semaphore_82571 - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore to access the PHY or NVM
 **/
अटल s32 e1000_get_hw_semaphore_82571(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;
	s32 sw_समयout = hw->nvm.word_size + 1;
	s32 fw_समयout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* If we have समयकरोut 3 बार on trying to acquire
	 * the पूर्णांकer-port SMBI semaphore, there is old code
	 * operating on the other port, and it is not
	 * releasing SMBI. Modअगरy the number of बार that
	 * we try क्रम the semaphore to पूर्णांकerwork with this
	 * older code.
	 */
	अगर (hw->dev_spec.e82571.smb_counter > 2)
		sw_समयout = 1;

	/* Get the SW semaphore */
	जबतक (i < sw_समयout) अणु
		swsm = er32(SWSM);
		अगर (!(swsm & E1000_SWSM_SMBI))
			अवरोध;

		usleep_range(50, 100);
		i++;
	पूर्ण

	अगर (i == sw_समयout) अणु
		e_dbg("Driver can't access device - SMBI bit is set.\n");
		hw->dev_spec.e82571.smb_counter++;
	पूर्ण
	/* Get the FW semaphore. */
	क्रम (i = 0; i < fw_समयout; i++) अणु
		swsm = er32(SWSM);
		ew32(SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired अगर bit latched */
		अगर (er32(SWSM) & E1000_SWSM_SWESMBI)
			अवरोध;

		usleep_range(50, 100);
	पूर्ण

	अगर (i == fw_समयout) अणु
		/* Release semaphores */
		e1000_put_hw_semaphore_82571(hw);
		e_dbg("Driver can't access the NVM\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_put_hw_semaphore_82571 - Release hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release hardware semaphore used to access the PHY or NVM
 **/
अटल व्योम e1000_put_hw_semaphore_82571(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;

	swsm = er32(SWSM);
	swsm &= ~(E1000_SWSM_SMBI | E1000_SWSM_SWESMBI);
	ew32(SWSM, swsm);
पूर्ण

/**
 *  e1000_get_hw_semaphore_82573 - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore during reset.
 *
 **/
अटल s32 e1000_get_hw_semaphore_82573(काष्ठा e1000_hw *hw)
अणु
	u32 extcnf_ctrl;
	s32 i = 0;

	extcnf_ctrl = er32(EXTCNF_CTRL);
	करो अणु
		extcnf_ctrl |= E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP;
		ew32(EXTCNF_CTRL, extcnf_ctrl);
		extcnf_ctrl = er32(EXTCNF_CTRL);

		अगर (extcnf_ctrl & E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP)
			अवरोध;

		usleep_range(2000, 4000);
		i++;
	पूर्ण जबतक (i < MDIO_OWNERSHIP_TIMEOUT);

	अगर (i == MDIO_OWNERSHIP_TIMEOUT) अणु
		/* Release semaphores */
		e1000_put_hw_semaphore_82573(hw);
		e_dbg("Driver can't access the PHY\n");
		वापस -E1000_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_put_hw_semaphore_82573 - Release hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release hardware semaphore used during reset.
 *
 **/
अटल व्योम e1000_put_hw_semaphore_82573(काष्ठा e1000_hw *hw)
अणु
	u32 extcnf_ctrl;

	extcnf_ctrl = er32(EXTCNF_CTRL);
	extcnf_ctrl &= ~E1000_EXTCNF_CTRL_MDIO_SW_OWNERSHIP;
	ew32(EXTCNF_CTRL, extcnf_ctrl);
पूर्ण

अटल DEFINE_MUTEX(swflag_mutex);

/**
 *  e1000_get_hw_semaphore_82574 - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore to access the PHY or NVM.
 *
 **/
अटल s32 e1000_get_hw_semaphore_82574(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	mutex_lock(&swflag_mutex);
	ret_val = e1000_get_hw_semaphore_82573(hw);
	अगर (ret_val)
		mutex_unlock(&swflag_mutex);
	वापस ret_val;
पूर्ण

/**
 *  e1000_put_hw_semaphore_82574 - Release hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release hardware semaphore used to access the PHY or NVM
 *
 **/
अटल व्योम e1000_put_hw_semaphore_82574(काष्ठा e1000_hw *hw)
अणु
	e1000_put_hw_semaphore_82573(hw);
	mutex_unlock(&swflag_mutex);
पूर्ण

/**
 *  e1000_set_d0_lplu_state_82574 - Set Low Power Linkup D0 state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU D0 state according to the active flag.
 *  LPLU will not be activated unless the
 *  device स्वतःnegotiation advertisement meets standards of
 *  either 10 or 10/100 or 10/100/1000 at all duplexes.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  PHY setup routines.
 **/
अटल s32 e1000_set_d0_lplu_state_82574(काष्ठा e1000_hw *hw, bool active)
अणु
	u32 data = er32(POEMB);

	अगर (active)
		data |= E1000_PHY_CTRL_D0A_LPLU;
	अन्यथा
		data &= ~E1000_PHY_CTRL_D0A_LPLU;

	ew32(POEMB, data);
	वापस 0;
पूर्ण

/**
 *  e1000_set_d3_lplu_state_82574 - Sets low घातer link up state क्रम D3
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: boolean used to enable/disable lplu
 *
 *  The low घातer link up (lplu) state is set to the घातer management level D3
 *  when active is true, अन्यथा clear lplu क्रम D3. LPLU
 *  is used during Dx states where the घातer conservation is most important.
 *  During driver activity, SmartSpeed should be enabled so perक्रमmance is
 *  मुख्यtained.
 **/
अटल s32 e1000_set_d3_lplu_state_82574(काष्ठा e1000_hw *hw, bool active)
अणु
	u32 data = er32(POEMB);

	अगर (!active) अणु
		data &= ~E1000_PHY_CTRL_NOND0A_LPLU;
	पूर्ण अन्यथा अगर ((hw->phy.स्वतःneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (hw->phy.स्वतःneg_advertised == E1000_ALL_NOT_GIG) ||
		   (hw->phy.स्वतःneg_advertised == E1000_ALL_10_SPEED)) अणु
		data |= E1000_PHY_CTRL_NOND0A_LPLU;
	पूर्ण

	ew32(POEMB, data);
	वापस 0;
पूर्ण

/**
 *  e1000_acquire_nvm_82571 - Request क्रम access to the EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  To gain access to the EEPROM, first we must obtain a hardware semaphore.
 *  Then क्रम non-82573 hardware, set the EEPROM access request bit and रुको
 *  क्रम EEPROM access grant bit.  If the access grant bit is not set, release
 *  hardware semaphore.
 **/
अटल s32 e1000_acquire_nvm_82571(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	ret_val = e1000_get_hw_semaphore_82571(hw);
	अगर (ret_val)
		वापस ret_val;

	चयन (hw->mac.type) अणु
	हाल e1000_82573:
		अवरोध;
	शेष:
		ret_val = e1000e_acquire_nvm(hw);
		अवरोध;
	पूर्ण

	अगर (ret_val)
		e1000_put_hw_semaphore_82571(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_release_nvm_82571 - Release exclusive access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Stop any current commands to the EEPROM and clear the EEPROM request bit.
 **/
अटल व्योम e1000_release_nvm_82571(काष्ठा e1000_hw *hw)
अणु
	e1000e_release_nvm(hw);
	e1000_put_hw_semaphore_82571(hw);
पूर्ण

/**
 *  e1000_ग_लिखो_nvm_82571 - Write to EEPROM using appropriate पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the EEPROM
 *
 *  For non-82573 silicon, ग_लिखो data to EEPROM at offset using SPI पूर्णांकerface.
 *
 *  If e1000e_update_nvm_checksum is not called after this function, the
 *  EEPROM will most likely contain an invalid checksum.
 **/
अटल s32 e1000_ग_लिखो_nvm_82571(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				 u16 *data)
अणु
	s32 ret_val;

	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		ret_val = e1000_ग_लिखो_nvm_eewr_82571(hw, offset, words, data);
		अवरोध;
	हाल e1000_82571:
	हाल e1000_82572:
		ret_val = e1000e_ग_लिखो_nvm_spi(hw, offset, words, data);
		अवरोध;
	शेष:
		ret_val = -E1000_ERR_NVM;
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_update_nvm_checksum_82571 - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 *  value to the EEPROM.
 **/
अटल s32 e1000_update_nvm_checksum_82571(काष्ठा e1000_hw *hw)
अणु
	u32 eecd;
	s32 ret_val;
	u16 i;

	ret_val = e1000e_update_nvm_checksum_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	/* If our nvm is an EEPROM, then we're करोne
	 * otherwise, commit the checksum to the flash NVM.
	 */
	अगर (hw->nvm.type != e1000_nvm_flash_hw)
		वापस 0;

	/* Check क्रम pending operations. */
	क्रम (i = 0; i < E1000_FLASH_UPDATES; i++) अणु
		usleep_range(1000, 2000);
		अगर (!(er32(EECD) & E1000_EECD_FLUPD))
			अवरोध;
	पूर्ण

	अगर (i == E1000_FLASH_UPDATES)
		वापस -E1000_ERR_NVM;

	/* Reset the firmware अगर using STM opcode. */
	अगर ((er32(FLOP) & 0xFF00) == E1000_STM_OPCODE) अणु
		/* The enabling of and the actual reset must be करोne
		 * in two ग_लिखो cycles.
		 */
		ew32(HICR, E1000_HICR_FW_RESET_ENABLE);
		e1e_flush();
		ew32(HICR, E1000_HICR_FW_RESET);
	पूर्ण

	/* Commit the ग_लिखो to flash */
	eecd = er32(EECD) | E1000_EECD_FLUPD;
	ew32(EECD, eecd);

	क्रम (i = 0; i < E1000_FLASH_UPDATES; i++) अणु
		usleep_range(1000, 2000);
		अगर (!(er32(EECD) & E1000_EECD_FLUPD))
			अवरोध;
	पूर्ण

	अगर (i == E1000_FLASH_UPDATES)
		वापस -E1000_ERR_NVM;

	वापस 0;
पूर्ण

/**
 *  e1000_validate_nvm_checksum_82571 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 **/
अटल s32 e1000_validate_nvm_checksum_82571(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->nvm.type == e1000_nvm_flash_hw)
		e1000_fix_nvm_checksum_82571(hw);

	वापस e1000e_validate_nvm_checksum_generic(hw);
पूर्ण

/**
 *  e1000_ग_लिखो_nvm_eewr_82571 - Write to EEPROM क्रम 82573 silicon
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the EEPROM
 *
 *  After checking क्रम invalid values, poll the EEPROM to ensure the previous
 *  command has completed beक्रमe trying to ग_लिखो the next word.  After ग_लिखो
 *  poll क्रम completion.
 *
 *  If e1000e_update_nvm_checksum is not called after this function, the
 *  EEPROM will most likely contain an invalid checksum.
 **/
अटल s32 e1000_ग_लिखो_nvm_eewr_82571(काष्ठा e1000_hw *hw, u16 offset,
				      u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eewr = 0;
	s32 ret_val = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		eewr = ((data[i] << E1000_NVM_RW_REG_DATA) |
			((offset + i) << E1000_NVM_RW_ADDR_SHIFT) |
			E1000_NVM_RW_REG_START);

		ret_val = e1000e_poll_eerd_eewr_करोne(hw, E1000_NVM_POLL_WRITE);
		अगर (ret_val)
			अवरोध;

		ew32(EEWR, eewr);

		ret_val = e1000e_poll_eerd_eewr_करोne(hw, E1000_NVM_POLL_WRITE);
		अगर (ret_val)
			अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_get_cfg_करोne_82571 - Poll क्रम configuration करोne
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the management control रेजिस्टर क्रम the config करोne bit to be set.
 **/
अटल s32 e1000_get_cfg_करोne_82571(काष्ठा e1000_hw *hw)
अणु
	s32 समयout = PHY_CFG_TIMEOUT;

	जबतक (समयout) अणु
		अगर (er32(EEMNGCTL) & E1000_NVM_CFG_DONE_PORT_0)
			अवरोध;
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण
	अगर (!समयout) अणु
		e_dbg("MNG configuration cycle has not completed.\n");
		वापस -E1000_ERR_RESET;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_set_d0_lplu_state_82571 - Set Low Power Linkup D0 state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU D0 state according to the active flag.  When activating LPLU
 *  this function also disables smart speed and vice versa.  LPLU will not be
 *  activated unless the device स्वतःnegotiation advertisement meets standards
 *  of either 10 or 10/100 or 10/100/1000 at all duplexes.  This is a function
 *  poपूर्णांकer entry poपूर्णांक only called by PHY setup routines.
 **/
अटल s32 e1000_set_d0_lplu_state_82571(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर (active) अणु
		data |= IGP02E1000_PM_D0_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);
		अगर (ret_val)
			वापस ret_val;

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG, &data);
		अगर (ret_val)
			वापस ret_val;
		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG, data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		data &= ~IGP02E1000_PM_D0_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);
		अगर (ret_val)
			वापस ret_val;
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (phy->smart_speed == e1000_smart_speed_on) अणु
			ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   &data);
			अगर (ret_val)
				वापस ret_val;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण अन्यथा अगर (phy->smart_speed == e1000_smart_speed_off) अणु
			ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   &data);
			अगर (ret_val)
				वापस ret_val;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_reset_hw_82571 - Reset hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This resets the hardware पूर्णांकo a known state.
 **/
अटल s32 e1000_reset_hw_82571(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl, ctrl_ext, eecd, tctl;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	अगर (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	ew32(RCTL, 0);
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);
	e1e_flush();

	usleep_range(10000, 11000);

	/* Must acquire the MDIO ownership beक्रमe MAC reset.
	 * Ownership शेषs to firmware after a reset.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
		ret_val = e1000_get_hw_semaphore_82573(hw);
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		ret_val = e1000_get_hw_semaphore_82574(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ctrl = er32(CTRL);

	e_dbg("Issuing a global reset to MAC\n");
	ew32(CTRL, ctrl | E1000_CTRL_RST);

	/* Must release MDIO ownership and mutex after MAC reset. */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
		/* Release mutex only अगर the hw semaphore is acquired */
		अगर (!ret_val)
			e1000_put_hw_semaphore_82573(hw);
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		/* Release mutex only अगर the hw semaphore is acquired */
		अगर (!ret_val)
			e1000_put_hw_semaphore_82574(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (hw->nvm.type == e1000_nvm_flash_hw) अणु
		usleep_range(10, 20);
		ctrl_ext = er32(CTRL_EXT);
		ctrl_ext |= E1000_CTRL_EXT_EE_RST;
		ew32(CTRL_EXT, ctrl_ext);
		e1e_flush();
	पूर्ण

	ret_val = e1000e_get_स्वतः_rd_करोne(hw);
	अगर (ret_val)
		/* We करोn't want to जारी accessing MAC रेजिस्टरs. */
		वापस ret_val;

	/* Phy configuration from NVM just starts after EECD_AUTO_RD is set.
	 * Need to रुको क्रम Phy configuration completion beक्रमe accessing
	 * NVM and Phy.
	 */

	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		/* REQ and GNT bits need to be cleared when using AUTO_RD
		 * to access the EEPROM.
		 */
		eecd = er32(EECD);
		eecd &= ~(E1000_EECD_REQ | E1000_EECD_GNT);
		ew32(EECD, eecd);
		अवरोध;
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		msleep(25);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Clear any pending पूर्णांकerrupt events. */
	ew32(IMC, 0xffffffff);
	er32(ICR);

	अगर (hw->mac.type == e1000_82571) अणु
		/* Install any alternate MAC address पूर्णांकo RAR0 */
		ret_val = e1000_check_alt_mac_addr_generic(hw);
		अगर (ret_val)
			वापस ret_val;

		e1000e_set_laa_state_82571(hw, true);
	पूर्ण

	/* Reinitialize the 82571 serdes link state machine */
	अगर (hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes)
		hw->mac.serdes_link_state = e1000_serdes_link_करोwn;

	वापस 0;
पूर्ण

/**
 *  e1000_init_hw_82571 - Initialize hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This inits the hardware पढ़ोying it क्रम operation.
 **/
अटल s32 e1000_init_hw_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 reg_data;
	s32 ret_val;
	u16 i, rar_count = mac->rar_entry_count;

	e1000_initialize_hw_bits_82571(hw);

	/* Initialize identअगरication LED */
	ret_val = mac->ops.id_led_init(hw);
	/* An error is not fatal and we should not stop init due to this */
	अगर (ret_val)
		e_dbg("Error initializing identification LED\n");

	/* Disabling VLAN filtering */
	e_dbg("Initializing the IEEE VLAN\n");
	mac->ops.clear_vfta(hw);

	/* Setup the receive address.
	 * If, however, a locally administered address was asचिन्हित to the
	 * 82571, we must reserve a RAR क्रम it to work around an issue where
	 * resetting one port will reload the MAC on the other port.
	 */
	अगर (e1000e_get_laa_state_82571(hw))
		rar_count--;
	e1000e_init_rx_addrs(hw, rar_count);

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	क्रम (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);

	/* Set the transmit descriptor ग_लिखो-back policy */
	reg_data = er32(TXDCTL(0));
	reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC);
	ew32(TXDCTL(0), reg_data);

	/* ...क्रम both queues. */
	चयन (mac->type) अणु
	हाल e1000_82573:
		e1000e_enable_tx_pkt_filtering(hw);
		fallthrough;
	हाल e1000_82574:
	हाल e1000_82583:
		reg_data = er32(GCR);
		reg_data |= E1000_GCR_L1_ACT_WITHOUT_L0S_RX;
		ew32(GCR, reg_data);
		अवरोध;
	शेष:
		reg_data = er32(TXDCTL(1));
		reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
			    E1000_TXDCTL_FULL_TX_DESC_WB |
			    E1000_TXDCTL_COUNT_DESC);
		ew32(TXDCTL(1), reg_data);
		अवरोध;
	पूर्ण

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_82571(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_initialize_hw_bits_82571 - Initialize hardware-dependent bits
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes required hardware-dependent bits needed क्रम normal operation.
 **/
अटल व्योम e1000_initialize_hw_bits_82571(काष्ठा e1000_hw *hw)
अणु
	u32 reg;

	/* Transmit Descriptor Control 0 */
	reg = er32(TXDCTL(0));
	reg |= BIT(22);
	ew32(TXDCTL(0), reg);

	/* Transmit Descriptor Control 1 */
	reg = er32(TXDCTL(1));
	reg |= BIT(22);
	ew32(TXDCTL(1), reg);

	/* Transmit Arbitration Control 0 */
	reg = er32(TARC(0));
	reg &= ~(0xF << 27);	/* 30:27 */
	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		reg |= BIT(23) | BIT(24) | BIT(25) | BIT(26);
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		reg |= BIT(26);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ew32(TARC(0), reg);

	/* Transmit Arbitration Control 1 */
	reg = er32(TARC(1));
	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		reg &= ~(BIT(29) | BIT(30));
		reg |= BIT(22) | BIT(24) | BIT(25) | BIT(26);
		अगर (er32(TCTL) & E1000_TCTL_MULR)
			reg &= ~BIT(28);
		अन्यथा
			reg |= BIT(28);
		ew32(TARC(1), reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Device Control */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		reg = er32(CTRL);
		reg &= ~BIT(29);
		ew32(CTRL, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Extended Device Control */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		reg = er32(CTRL_EXT);
		reg &= ~BIT(23);
		reg |= BIT(22);
		ew32(CTRL_EXT, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (hw->mac.type == e1000_82571) अणु
		reg = er32(PBA_ECC);
		reg |= E1000_PBA_ECC_CORR_EN;
		ew32(PBA_ECC, reg);
	पूर्ण

	/* Workaround क्रम hardware errata.
	 * Ensure that DMA Dynamic Clock gating is disabled on 82571 and 82572
	 */
	अगर ((hw->mac.type == e1000_82571) || (hw->mac.type == e1000_82572)) अणु
		reg = er32(CTRL_EXT);
		reg &= ~E1000_CTRL_EXT_DMA_DYN_CLK_EN;
		ew32(CTRL_EXT, reg);
	पूर्ण

	/* Disable IPv6 extension header parsing because some malक्रमmed
	 * IPv6 headers can hang the Rx.
	 */
	अगर (hw->mac.type <= e1000_82573) अणु
		reg = er32(RFCTL);
		reg |= (E1000_RFCTL_IPV6_EX_DIS | E1000_RFCTL_NEW_IPV6_EXT_DIS);
		ew32(RFCTL, reg);
	पूर्ण

	/* PCI-Ex Control Registers */
	चयन (hw->mac.type) अणु
	हाल e1000_82574:
	हाल e1000_82583:
		reg = er32(GCR);
		reg |= BIT(22);
		ew32(GCR, reg);

		/* Workaround क्रम hardware errata.
		 * apply workaround क्रम hardware errata करोcumented in errata
		 * करोcs Fixes issue where some error prone or unreliable PCIe
		 * completions are occurring, particularly with ASPM enabled.
		 * Without fix, issue can cause Tx समयouts.
		 */
		reg = er32(GCR2);
		reg |= 1;
		ew32(GCR2, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 *  e1000_clear_vfta_82571 - Clear VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the रेजिस्टर array which contains the VLAN filter table by
 *  setting all the values to 0.
 **/
अटल व्योम e1000_clear_vfta_82571(काष्ठा e1000_hw *hw)
अणु
	u32 offset;
	u32 vfta_value = 0;
	u32 vfta_offset = 0;
	u32 vfta_bit_in_reg = 0;

	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		अगर (hw->mng_cookie.vlan_id != 0) अणु
			/* The VFTA is a 4096b bit-field, each identअगरying
			 * a single VLAN ID.  The following operations
			 * determine which 32b entry (i.e. offset) पूर्णांकo the
			 * array we want to set the VLAN ID (i.e. bit) of
			 * the manageability unit.
			 */
			vfta_offset = (hw->mng_cookie.vlan_id >>
				       E1000_VFTA_ENTRY_SHIFT) &
			    E1000_VFTA_ENTRY_MASK;
			vfta_bit_in_reg =
			    BIT(hw->mng_cookie.vlan_id &
				E1000_VFTA_ENTRY_BIT_SHIFT_MASK);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	क्रम (offset = 0; offset < E1000_VLAN_FILTER_TBL_SIZE; offset++) अणु
		/* If the offset we want to clear is the same offset of the
		 * manageability VLAN ID, then clear all bits except that of
		 * the manageability unit.
		 */
		vfta_value = (offset == vfta_offset) ? vfta_bit_in_reg : 0;
		E1000_WRITE_REG_ARRAY(hw, E1000_VFTA, offset, vfta_value);
		e1e_flush();
	पूर्ण
पूर्ण

/**
 *  e1000_check_mng_mode_82574 - Check manageability is enabled
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the NVM Initialization Control Word 2 and वापसs true
 *  (>0) अगर any manageability is enabled, अन्यथा false (0).
 **/
अटल bool e1000_check_mng_mode_82574(काष्ठा e1000_hw *hw)
अणु
	u16 data;

	e1000_पढ़ो_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &data);
	वापस (data & E1000_NVM_INIT_CTRL2_MNGM) != 0;
पूर्ण

/**
 *  e1000_led_on_82574 - Turn LED on
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn LED on.
 **/
अटल s32 e1000_led_on_82574(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	u32 i;

	ctrl = hw->mac.ledctl_mode2;
	अगर (!(E1000_STATUS_LU & er32(STATUS))) अणु
		/* If no link, then turn LED on by setting the invert bit
		 * क्रम each LED that's "on" (0x0E) in ledctl_mode2.
		 */
		क्रम (i = 0; i < 4; i++)
			अगर (((hw->mac.ledctl_mode2 >> (i * 8)) & 0xFF) ==
			    E1000_LEDCTL_MODE_LED_ON)
				ctrl |= (E1000_LEDCTL_LED0_IVRT << (i * 8));
	पूर्ण
	ew32(LEDCTL, ctrl);

	वापस 0;
पूर्ण

/**
 *  e1000_check_phy_82574 - check 82574 phy hung state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Returns whether phy is hung or not
 **/
bool e1000_check_phy_82574(काष्ठा e1000_hw *hw)
अणु
	u16 status_1kbt = 0;
	u16 receive_errors = 0;
	s32 ret_val;

	/* Read PHY Receive Error counter first, अगर its is max - all F's then
	 * पढ़ो the Base1000T status रेजिस्टर If both are max then PHY is hung.
	 */
	ret_val = e1e_rphy(hw, E1000_RECEIVE_ERROR_COUNTER, &receive_errors);
	अगर (ret_val)
		वापस false;
	अगर (receive_errors == E1000_RECEIVE_ERROR_MAX) अणु
		ret_val = e1e_rphy(hw, E1000_BASE1000T_STATUS, &status_1kbt);
		अगर (ret_val)
			वापस false;
		अगर ((status_1kbt & E1000_IDLE_ERROR_COUNT_MASK) ==
		    E1000_IDLE_ERROR_COUNT_MASK)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 *  e1000_setup_link_82571 - Setup flow control and link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines which flow control settings to use, then configures flow
 *  control.  Calls the appropriate media-specअगरic link configuration
 *  function.  Assuming the adapter has a valid link partner, a valid link
 *  should be established.  Assumes the hardware has previously been reset
 *  and the transmitter and receiver are not enabled.
 **/
अटल s32 e1000_setup_link_82571(काष्ठा e1000_hw *hw)
अणु
	/* 82573 करोes not have a word in the NVM to determine
	 * the शेष flow control setting, so we explicitly
	 * set it to full.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		अगर (hw->fc.requested_mode == e1000_fc_शेष)
			hw->fc.requested_mode = e1000_fc_full;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस e1000e_setup_link_generic(hw);
पूर्ण

/**
 *  e1000_setup_copper_link_82571 - Configure copper link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures the link क्रम स्वतः-neg or क्रमced speed and duplex.  Then we check
 *  क्रम link, once link is established calls to configure collision distance
 *  and flow control are called.
 **/
अटल s32 e1000_setup_copper_link_82571(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ew32(CTRL, ctrl);

	चयन (hw->phy.type) अणु
	हाल e1000_phy_m88:
	हाल e1000_phy_bm:
		ret_val = e1000e_copper_link_setup_m88(hw);
		अवरोध;
	हाल e1000_phy_igp_2:
		ret_val = e1000e_copper_link_setup_igp(hw);
		अवरोध;
	शेष:
		वापस -E1000_ERR_PHY;
	पूर्ण

	अगर (ret_val)
		वापस ret_val;

	वापस e1000e_setup_copper_link(hw);
पूर्ण

/**
 *  e1000_setup_fiber_serdes_link_82571 - Setup link क्रम fiber/serdes
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures collision distance and flow control क्रम fiber and serdes links.
 *  Upon successful setup, poll क्रम link.
 **/
अटल s32 e1000_setup_fiber_serdes_link_82571(काष्ठा e1000_hw *hw)
अणु
	चयन (hw->mac.type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
		/* If SerDes loopback mode is entered, there is no क्रमm
		 * of reset to take the adapter out of that mode.  So we
		 * have to explicitly take the adapter out of loopback
		 * mode.  This prevents drivers from twiddling their thumbs
		 * अगर another tool failed to take it out of loopback mode.
		 */
		ew32(SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस e1000e_setup_fiber_serdes_link(hw);
पूर्ण

/**
 *  e1000_check_क्रम_serdes_link_82571 - Check क्रम link (Serdes)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reports the link state as up or करोwn.
 *
 *  If स्वतःnegotiation is supported by the link partner, the link state is
 *  determined by the result of स्वतःnegotiation. This is the most likely हाल.
 *  If स्वतःnegotiation is not supported by the link partner, and the link
 *  has a valid संकेत, क्रमce the link up.
 *
 *  The link state is represented पूर्णांकernally here by 4 states:
 *
 *  1) करोwn
 *  2) स्वतःneg_progress
 *  3) स्वतःneg_complete (the link successfully स्वतःnegotiated)
 *  4) क्रमced_up (the link has been क्रमced up, it did not स्वतःnegotiate)
 *
 **/
अटल s32 e1000_check_क्रम_serdes_link_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	u32 txcw;
	u32 i;
	s32 ret_val = 0;

	ctrl = er32(CTRL);
	status = er32(STATUS);
	er32(RXCW);
	/* SYNCH bit and IV bit are sticky */
	usleep_range(10, 20);
	rxcw = er32(RXCW);

	अगर ((rxcw & E1000_RXCW_SYNCH) && !(rxcw & E1000_RXCW_IV)) अणु
		/* Receiver is synchronized with no invalid bits.  */
		चयन (mac->serdes_link_state) अणु
		हाल e1000_serdes_link_स्वतःneg_complete:
			अगर (!(status & E1000_STATUS_LU)) अणु
				/* We have lost link, retry स्वतःneg beक्रमe
				 * reporting link failure
				 */
				mac->serdes_link_state =
				    e1000_serdes_link_स्वतःneg_progress;
				mac->serdes_has_link = false;
				e_dbg("AN_UP     -> AN_PROG\n");
			पूर्ण अन्यथा अणु
				mac->serdes_has_link = true;
			पूर्ण
			अवरोध;

		हाल e1000_serdes_link_क्रमced_up:
			/* If we are receiving /C/ ordered sets, re-enable
			 * स्वतः-negotiation in the TXCW रेजिस्टर and disable
			 * क्रमced link in the Device Control रेजिस्टर in an
			 * attempt to स्वतः-negotiate with our link partner.
			 */
			अगर (rxcw & E1000_RXCW_C) अणु
				/* Enable स्वतःneg, and unक्रमce link up */
				ew32(TXCW, mac->txcw);
				ew32(CTRL, (ctrl & ~E1000_CTRL_SLU));
				mac->serdes_link_state =
				    e1000_serdes_link_स्वतःneg_progress;
				mac->serdes_has_link = false;
				e_dbg("FORCED_UP -> AN_PROG\n");
			पूर्ण अन्यथा अणु
				mac->serdes_has_link = true;
			पूर्ण
			अवरोध;

		हाल e1000_serdes_link_स्वतःneg_progress:
			अगर (rxcw & E1000_RXCW_C) अणु
				/* We received /C/ ordered sets, meaning the
				 * link partner has स्वतःnegotiated, and we can
				 * trust the Link Up (LU) status bit.
				 */
				अगर (status & E1000_STATUS_LU) अणु
					mac->serdes_link_state =
					    e1000_serdes_link_स्वतःneg_complete;
					e_dbg("AN_PROG   -> AN_UP\n");
					mac->serdes_has_link = true;
				पूर्ण अन्यथा अणु
					/* Autoneg completed, but failed. */
					mac->serdes_link_state =
					    e1000_serdes_link_करोwn;
					e_dbg("AN_PROG   -> DOWN\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				/* The link partner did not स्वतःneg.
				 * Force link up and full duplex, and change
				 * state to क्रमced.
				 */
				ew32(TXCW, (mac->txcw & ~E1000_TXCW_ANE));
				ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
				ew32(CTRL, ctrl);

				/* Configure Flow Control after link up. */
				ret_val = e1000e_config_fc_after_link_up(hw);
				अगर (ret_val) अणु
					e_dbg("Error config flow control\n");
					अवरोध;
				पूर्ण
				mac->serdes_link_state =
				    e1000_serdes_link_क्रमced_up;
				mac->serdes_has_link = true;
				e_dbg("AN_PROG   -> FORCED_UP\n");
			पूर्ण
			अवरोध;

		हाल e1000_serdes_link_करोwn:
		शेष:
			/* The link was करोwn but the receiver has now gained
			 * valid sync, so lets see अगर we can bring the link
			 * up.
			 */
			ew32(TXCW, mac->txcw);
			ew32(CTRL, (ctrl & ~E1000_CTRL_SLU));
			mac->serdes_link_state =
			    e1000_serdes_link_स्वतःneg_progress;
			mac->serdes_has_link = false;
			e_dbg("DOWN      -> AN_PROG\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(rxcw & E1000_RXCW_SYNCH)) अणु
			mac->serdes_has_link = false;
			mac->serdes_link_state = e1000_serdes_link_करोwn;
			e_dbg("ANYSTATE  -> DOWN\n");
		पूर्ण अन्यथा अणु
			/* Check several बार, अगर SYNCH bit and CONFIG
			 * bit both are consistently 1 then simply ignore
			 * the IV bit and restart Autoneg
			 */
			क्रम (i = 0; i < AN_RETRY_COUNT; i++) अणु
				usleep_range(10, 20);
				rxcw = er32(RXCW);
				अगर ((rxcw & E1000_RXCW_SYNCH) &&
				    (rxcw & E1000_RXCW_C))
					जारी;

				अगर (rxcw & E1000_RXCW_IV) अणु
					mac->serdes_has_link = false;
					mac->serdes_link_state =
					    e1000_serdes_link_करोwn;
					e_dbg("ANYSTATE  -> DOWN\n");
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (i == AN_RETRY_COUNT) अणु
				txcw = er32(TXCW);
				txcw |= E1000_TXCW_ANE;
				ew32(TXCW, txcw);
				mac->serdes_link_state =
				    e1000_serdes_link_स्वतःneg_progress;
				mac->serdes_has_link = false;
				e_dbg("ANYSTATE  -> AN_PROG\n");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_valid_led_शेष_82571 - Verअगरy a valid शेष LED config
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: poपूर्णांकer to the NVM (EEPROM)
 *
 *  Read the EEPROM क्रम the current शेष LED configuration.  If the
 *  LED configuration is not valid, set to a valid LED configuration.
 **/
अटल s32 e1000_valid_led_शेष_82571(काष्ठा e1000_hw *hw, u16 *data)
अणु
	s32 ret_val;

	ret_val = e1000_पढ़ो_nvm(hw, NVM_ID_LED_SETTINGS, 1, data);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	चयन (hw->mac.type) अणु
	हाल e1000_82573:
	हाल e1000_82574:
	हाल e1000_82583:
		अगर (*data == ID_LED_RESERVED_F746)
			*data = ID_LED_DEFAULT_82573;
		अवरोध;
	शेष:
		अगर (*data == ID_LED_RESERVED_0000 ||
		    *data == ID_LED_RESERVED_FFFF)
			*data = ID_LED_DEFAULT;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_get_laa_state_82571 - Get locally administered address state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Retrieve and वापस the current locally administered address state.
 **/
bool e1000e_get_laa_state_82571(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->mac.type != e1000_82571)
		वापस false;

	वापस hw->dev_spec.e82571.laa_is_present;
पूर्ण

/**
 *  e1000e_set_laa_state_82571 - Set locally administered address state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @state: enable/disable locally administered address
 *
 *  Enable/Disable the current locally administered address state.
 **/
व्योम e1000e_set_laa_state_82571(काष्ठा e1000_hw *hw, bool state)
अणु
	अगर (hw->mac.type != e1000_82571)
		वापस;

	hw->dev_spec.e82571.laa_is_present = state;

	/* If workaround is activated... */
	अगर (state)
		/* Hold a copy of the LAA in RAR[14] This is करोne so that
		 * between the समय RAR[0] माला_लो clobbered and the समय it
		 * माला_लो fixed, the actual LAA is in one of the RARs and no
		 * incoming packets directed to this port are dropped.
		 * Eventually the LAA will be in RAR[0] and RAR[14].
		 */
		hw->mac.ops.rar_set(hw, hw->mac.addr,
				    hw->mac.rar_entry_count - 1);
पूर्ण

/**
 *  e1000_fix_nvm_checksum_82571 - Fix EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरies that the EEPROM has completed the update.  After updating the
 *  EEPROM, we need to check bit 15 in work 0x23 क्रम the checksum fix.  If
 *  the checksum fix is not implemented, we need to set the bit and update
 *  the checksum.  Otherwise, अगर bit 15 is set and the checksum is incorrect,
 *  we need to वापस bad checksum.
 **/
अटल s32 e1000_fix_nvm_checksum_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	s32 ret_val;
	u16 data;

	अगर (nvm->type != e1000_nvm_flash_hw)
		वापस 0;

	/* Check bit 4 of word 10h.  If it is 0, firmware is करोne updating
	 * 10h-12h.  Checksum may need to be fixed.
	 */
	ret_val = e1000_पढ़ो_nvm(hw, 0x10, 1, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर (!(data & 0x10)) अणु
		/* Read 0x23 and check bit 15.  This bit is a 1
		 * when the checksum has alपढ़ोy been fixed.  If
		 * the checksum is still wrong and this bit is a
		 * 1, we need to वापस bad checksum.  Otherwise,
		 * we need to set this bit to a 1 and update the
		 * checksum.
		 */
		ret_val = e1000_पढ़ो_nvm(hw, 0x23, 1, &data);
		अगर (ret_val)
			वापस ret_val;

		अगर (!(data & 0x8000)) अणु
			data |= 0x8000;
			ret_val = e1000_ग_लिखो_nvm(hw, 0x23, 1, &data);
			अगर (ret_val)
				वापस ret_val;
			ret_val = e1000e_update_nvm_checksum(hw);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_पढ़ो_mac_addr_82571 - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_पढ़ो_mac_addr_82571(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->mac.type == e1000_82571) अणु
		s32 ret_val;

		/* If there's an alternate MAC address place it in RAR0
		 * so that it will override the Si installed शेष perm
		 * address.
		 */
		ret_val = e1000_check_alt_mac_addr_generic(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस e1000_पढ़ो_mac_addr_generic(hw);
पूर्ण

/**
 * e1000_घातer_करोwn_phy_copper_82571 - Remove link during PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, हटाओ the link.
 **/
अटल व्योम e1000_घातer_करोwn_phy_copper_82571(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	काष्ठा e1000_mac_info *mac = &hw->mac;

	अगर (!phy->ops.check_reset_block)
		वापस;

	/* If the management पूर्णांकerface is not enabled, then घातer करोwn */
	अगर (!(mac->ops.check_mng_mode(hw) || phy->ops.check_reset_block(hw)))
		e1000_घातer_करोwn_phy_copper(hw);
पूर्ण

/**
 *  e1000_clear_hw_cntrs_82571 - Clear device specअगरic hardware counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the hardware counters by पढ़ोing the counter रेजिस्टरs.
 **/
अटल व्योम e1000_clear_hw_cntrs_82571(काष्ठा e1000_hw *hw)
अणु
	e1000e_clear_hw_cntrs_base(hw);

	er32(PRC64);
	er32(PRC127);
	er32(PRC255);
	er32(PRC511);
	er32(PRC1023);
	er32(PRC1522);
	er32(PTC64);
	er32(PTC127);
	er32(PTC255);
	er32(PTC511);
	er32(PTC1023);
	er32(PTC1522);

	er32(ALGNERRC);
	er32(RXERRC);
	er32(TNCRS);
	er32(CEXTERR);
	er32(TSCTC);
	er32(TSCTFC);

	er32(MGTPRC);
	er32(MGTPDC);
	er32(MGTPTC);

	er32(IAC);
	er32(ICRXOC);

	er32(ICRXPTC);
	er32(ICRXATC);
	er32(ICTXPTC);
	er32(ICTXATC);
	er32(ICTXQEC);
	er32(ICTXQMTC);
	er32(ICRXDMTC);
पूर्ण

अटल स्थिर काष्ठा e1000_mac_operations e82571_mac_ops = अणु
	/* .check_mng_mode: mac type dependent */
	/* .check_क्रम_link: media type dependent */
	.id_led_init		= e1000e_id_led_init_generic,
	.cleanup_led		= e1000e_cleanup_led_generic,
	.clear_hw_cntrs		= e1000_clear_hw_cntrs_82571,
	.get_bus_info		= e1000e_get_bus_info_pcie,
	.set_lan_id		= e1000_set_lan_id_multi_port_pcie,
	/* .get_link_up_info: media type dependent */
	/* .led_on: mac type dependent */
	.led_off		= e1000e_led_off_generic,
	.update_mc_addr_list	= e1000e_update_mc_addr_list_generic,
	.ग_लिखो_vfta		= e1000_ग_लिखो_vfta_generic,
	.clear_vfta		= e1000_clear_vfta_82571,
	.reset_hw		= e1000_reset_hw_82571,
	.init_hw		= e1000_init_hw_82571,
	.setup_link		= e1000_setup_link_82571,
	/* .setup_physical_पूर्णांकerface: media type dependent */
	.setup_led		= e1000e_setup_led_generic,
	.config_collision_dist	= e1000e_config_collision_dist_generic,
	.पढ़ो_mac_addr		= e1000_पढ़ो_mac_addr_82571,
	.rar_set		= e1000e_rar_set_generic,
	.rar_get_count		= e1000e_rar_get_count_generic,
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations e82_phy_ops_igp = अणु
	.acquire		= e1000_get_hw_semaphore_82571,
	.check_polarity		= e1000_check_polarity_igp,
	.check_reset_block	= e1000e_check_reset_block_generic,
	.commit			= शून्य,
	.क्रमce_speed_duplex	= e1000e_phy_क्रमce_speed_duplex_igp,
	.get_cfg_करोne		= e1000_get_cfg_करोne_82571,
	.get_cable_length	= e1000e_get_cable_length_igp_2,
	.get_info		= e1000e_get_phy_info_igp,
	.पढ़ो_reg		= e1000e_पढ़ो_phy_reg_igp,
	.release		= e1000_put_hw_semaphore_82571,
	.reset			= e1000e_phy_hw_reset_generic,
	.set_d0_lplu_state	= e1000_set_d0_lplu_state_82571,
	.set_d3_lplu_state	= e1000e_set_d3_lplu_state,
	.ग_लिखो_reg		= e1000e_ग_लिखो_phy_reg_igp,
	.cfg_on_link_up		= शून्य,
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations e82_phy_ops_m88 = अणु
	.acquire		= e1000_get_hw_semaphore_82571,
	.check_polarity		= e1000_check_polarity_m88,
	.check_reset_block	= e1000e_check_reset_block_generic,
	.commit			= e1000e_phy_sw_reset,
	.क्रमce_speed_duplex	= e1000e_phy_क्रमce_speed_duplex_m88,
	.get_cfg_करोne		= e1000e_get_cfg_करोne_generic,
	.get_cable_length	= e1000e_get_cable_length_m88,
	.get_info		= e1000e_get_phy_info_m88,
	.पढ़ो_reg		= e1000e_पढ़ो_phy_reg_m88,
	.release		= e1000_put_hw_semaphore_82571,
	.reset			= e1000e_phy_hw_reset_generic,
	.set_d0_lplu_state	= e1000_set_d0_lplu_state_82571,
	.set_d3_lplu_state	= e1000e_set_d3_lplu_state,
	.ग_लिखो_reg		= e1000e_ग_लिखो_phy_reg_m88,
	.cfg_on_link_up		= शून्य,
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations e82_phy_ops_bm = अणु
	.acquire		= e1000_get_hw_semaphore_82571,
	.check_polarity		= e1000_check_polarity_m88,
	.check_reset_block	= e1000e_check_reset_block_generic,
	.commit			= e1000e_phy_sw_reset,
	.क्रमce_speed_duplex	= e1000e_phy_क्रमce_speed_duplex_m88,
	.get_cfg_करोne		= e1000e_get_cfg_करोne_generic,
	.get_cable_length	= e1000e_get_cable_length_m88,
	.get_info		= e1000e_get_phy_info_m88,
	.पढ़ो_reg		= e1000e_पढ़ो_phy_reg_bm2,
	.release		= e1000_put_hw_semaphore_82571,
	.reset			= e1000e_phy_hw_reset_generic,
	.set_d0_lplu_state	= e1000_set_d0_lplu_state_82571,
	.set_d3_lplu_state	= e1000e_set_d3_lplu_state,
	.ग_लिखो_reg		= e1000e_ग_लिखो_phy_reg_bm2,
	.cfg_on_link_up		= शून्य,
पूर्ण;

अटल स्थिर काष्ठा e1000_nvm_operations e82571_nvm_ops = अणु
	.acquire		= e1000_acquire_nvm_82571,
	.पढ़ो			= e1000e_पढ़ो_nvm_eerd,
	.release		= e1000_release_nvm_82571,
	.reload			= e1000e_reload_nvm_generic,
	.update			= e1000_update_nvm_checksum_82571,
	.valid_led_शेष	= e1000_valid_led_शेष_82571,
	.validate		= e1000_validate_nvm_checksum_82571,
	.ग_लिखो			= e1000_ग_लिखो_nvm_82571,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82571_info = अणु
	.mac			= e1000_82571,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_HAS_WOL
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_SMART_POWER_DOWN
				  | FLAG_RESET_OVERWRITES_LAA /* errata */
				  | FLAG_TARC_SPEED_MODE_BIT /* errata */
				  | FLAG_APME_CHECK_PORT_B,
	.flags2			= FLAG2_DISABLE_ASPM_L1 /* errata 13 */
				  | FLAG2_DMA_BURST,
	.pba			= 38,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_82571,
	.mac_ops		= &e82571_mac_ops,
	.phy_ops		= &e82_phy_ops_igp,
	.nvm_ops		= &e82571_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82572_info = अणु
	.mac			= e1000_82572,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_HAS_WOL
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_TARC_SPEED_MODE_BIT, /* errata */
	.flags2			= FLAG2_DISABLE_ASPM_L1 /* errata 13 */
				  | FLAG2_DMA_BURST,
	.pba			= 38,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_82571,
	.mac_ops		= &e82571_mac_ops,
	.phy_ops		= &e82_phy_ops_igp,
	.nvm_ops		= &e82571_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82573_info = अणु
	.mac			= e1000_82573,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_WOL
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_SMART_POWER_DOWN
				  | FLAG_HAS_AMT
				  | FLAG_HAS_SWSM_ON_LOAD,
	.flags2			= FLAG2_DISABLE_ASPM_L1
				  | FLAG2_DISABLE_ASPM_L0S,
	.pba			= 20,
	.max_hw_frame_size	= VLAN_ETH_FRAME_LEN + ETH_FCS_LEN,
	.get_variants		= e1000_get_variants_82571,
	.mac_ops		= &e82571_mac_ops,
	.phy_ops		= &e82_phy_ops_m88,
	.nvm_ops		= &e82571_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82574_info = अणु
	.mac			= e1000_82574,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_MSIX
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_SMART_POWER_DOWN
				  | FLAG_HAS_AMT
				  | FLAG_HAS_CTRLEXT_ON_LOAD,
	.flags2			 = FLAG2_CHECK_PHY_HANG
				  | FLAG2_DISABLE_ASPM_L0S
				  | FLAG2_DISABLE_ASPM_L1
				  | FLAG2_NO_DISABLE_RX
				  | FLAG2_DMA_BURST
				  | FLAG2_CHECK_SYSTIM_OVERFLOW,
	.pba			= 32,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_82571,
	.mac_ops		= &e82571_mac_ops,
	.phy_ops		= &e82_phy_ops_bm,
	.nvm_ops		= &e82571_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82583_info = अणु
	.mac			= e1000_82583,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_SMART_POWER_DOWN
				  | FLAG_HAS_AMT
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_HAS_CTRLEXT_ON_LOAD,
	.flags2			= FLAG2_DISABLE_ASPM_L0S
				  | FLAG2_DISABLE_ASPM_L1
				  | FLAG2_NO_DISABLE_RX
				  | FLAG2_CHECK_SYSTIM_OVERFLOW,
	.pba			= 32,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_82571,
	.mac_ops		= &e82571_mac_ops,
	.phy_ops		= &e82_phy_ops_bm,
	.nvm_ops		= &e82571_nvm_ops,
पूर्ण;

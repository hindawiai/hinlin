<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* 80003ES2LAN Gigabit Ethernet Controller (Copper)
 * 80003ES2LAN Gigabit Ethernet Controller (Serdes)
 */

#समावेश "e1000.h"

/* A table क्रम the GG82563 cable length where the range is defined
 * with a lower bound at "index" and the upper bound at
 * "index + 5".
 */
अटल स्थिर u16 e1000_gg82563_cable_length_table[] = अणु
	0, 60, 115, 150, 150, 60, 115, 150, 180, 180, 0xFF
पूर्ण;

#घोषणा GG82563_CABLE_LENGTH_TABLE_SIZE \
		ARRAY_SIZE(e1000_gg82563_cable_length_table)

अटल s32 e1000_setup_copper_link_80003es2lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_acquire_swfw_sync_80003es2lan(काष्ठा e1000_hw *hw, u16 mask);
अटल व्योम e1000_release_swfw_sync_80003es2lan(काष्ठा e1000_hw *hw, u16 mask);
अटल व्योम e1000_initialize_hw_bits_80003es2lan(काष्ठा e1000_hw *hw);
अटल व्योम e1000_clear_hw_cntrs_80003es2lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_cfg_kmrn_1000_80003es2lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_cfg_kmrn_10_100_80003es2lan(काष्ठा e1000_hw *hw, u16 duplex);
अटल s32 e1000_पढ़ो_kmrn_reg_80003es2lan(काष्ठा e1000_hw *hw, u32 offset,
					   u16 *data);
अटल s32 e1000_ग_लिखो_kmrn_reg_80003es2lan(काष्ठा e1000_hw *hw, u32 offset,
					    u16 data);
अटल व्योम e1000_घातer_करोwn_phy_copper_80003es2lan(काष्ठा e1000_hw *hw);

/**
 *  e1000_init_phy_params_80003es2lan - Init ESB2 PHY func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_phy_params_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	अगर (hw->phy.media_type != e1000_media_type_copper) अणु
		phy->type = e1000_phy_none;
		वापस 0;
	पूर्ण अन्यथा अणु
		phy->ops.घातer_up = e1000_घातer_up_phy_copper;
		phy->ops.घातer_करोwn = e1000_घातer_करोwn_phy_copper_80003es2lan;
	पूर्ण

	phy->addr = 1;
	phy->स्वतःneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us = 100;
	phy->type = e1000_phy_gg82563;

	/* This can only be करोne after all function poपूर्णांकers are setup. */
	ret_val = e1000e_get_phy_id(hw);

	/* Verअगरy phy id */
	अगर (phy->id != GG82563_E_PHY_ID)
		वापस -E1000_ERR_PHY;

	वापस ret_val;
पूर्ण

/**
 *  e1000_init_nvm_params_80003es2lan - Init ESB2 NVM func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_nvm_params_80003es2lan(काष्ठा e1000_hw *hw)
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

	वापस 0;
पूर्ण

/**
 *  e1000_init_mac_params_80003es2lan - Init ESB2 MAC func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_init_mac_params_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;

	/* Set media type and media-dependent function poपूर्णांकers */
	चयन (hw->adapter->pdev->device) अणु
	हाल E1000_DEV_ID_80003ES2LAN_SERDES_DPT:
		hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;
		mac->ops.check_क्रम_link = e1000e_check_क्रम_serdes_link;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000e_setup_fiber_serdes_link;
		अवरोध;
	शेष:
		hw->phy.media_type = e1000_media_type_copper;
		mac->ops.check_क्रम_link = e1000e_check_क्रम_copper_link;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000_setup_copper_link_80003es2lan;
		अवरोध;
	पूर्ण

	/* Set mta रेजिस्टर count */
	mac->mta_reg_count = 128;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_RAR_ENTRIES;
	/* FWSM रेजिस्टर */
	mac->has_fwsm = true;
	/* ARC supported; valid only अगर manageability features are enabled. */
	mac->arc_subप्रणाली_valid = !!(er32(FWSM) & E1000_FWSM_MODE_MASK);
	/* Adaptive IFS not supported */
	mac->adaptive_अगरs = false;

	/* set lan id क्रम port to determine which phy lock to use */
	hw->mac.ops.set_lan_id(hw);

	वापस 0;
पूर्ण

अटल s32 e1000_get_variants_80003es2lan(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 rc;

	rc = e1000_init_mac_params_80003es2lan(hw);
	अगर (rc)
		वापस rc;

	rc = e1000_init_nvm_params_80003es2lan(hw);
	अगर (rc)
		वापस rc;

	rc = e1000_init_phy_params_80003es2lan(hw);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

/**
 *  e1000_acquire_phy_80003es2lan - Acquire rights to access PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  A wrapper to acquire access rights to the correct PHY.
 **/
अटल s32 e1000_acquire_phy_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u16 mask;

	mask = hw->bus.func ? E1000_SWFW_PHY1_SM : E1000_SWFW_PHY0_SM;
	वापस e1000_acquire_swfw_sync_80003es2lan(hw, mask);
पूर्ण

/**
 *  e1000_release_phy_80003es2lan - Release rights to access PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  A wrapper to release access rights to the correct PHY.
 **/
अटल व्योम e1000_release_phy_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u16 mask;

	mask = hw->bus.func ? E1000_SWFW_PHY1_SM : E1000_SWFW_PHY0_SM;
	e1000_release_swfw_sync_80003es2lan(hw, mask);
पूर्ण

/**
 *  e1000_acquire_mac_csr_80003es2lan - Acquire right to access Kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the semaphore to access the Kumeran पूर्णांकerface.
 *
 **/
अटल s32 e1000_acquire_mac_csr_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u16 mask;

	mask = E1000_SWFW_CSR_SM;

	वापस e1000_acquire_swfw_sync_80003es2lan(hw, mask);
पूर्ण

/**
 *  e1000_release_mac_csr_80003es2lan - Release right to access Kumeran Register
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release the semaphore used to access the Kumeran पूर्णांकerface
 **/
अटल व्योम e1000_release_mac_csr_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u16 mask;

	mask = E1000_SWFW_CSR_SM;

	e1000_release_swfw_sync_80003es2lan(hw, mask);
पूर्ण

/**
 *  e1000_acquire_nvm_80003es2lan - Acquire rights to access NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the semaphore to access the EEPROM.
 **/
अटल s32 e1000_acquire_nvm_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	ret_val = e1000_acquire_swfw_sync_80003es2lan(hw, E1000_SWFW_EEP_SM);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000e_acquire_nvm(hw);

	अगर (ret_val)
		e1000_release_swfw_sync_80003es2lan(hw, E1000_SWFW_EEP_SM);

	वापस ret_val;
पूर्ण

/**
 *  e1000_release_nvm_80003es2lan - Relinquish rights to access NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Release the semaphore used to access the EEPROM.
 **/
अटल व्योम e1000_release_nvm_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	e1000e_release_nvm(hw);
	e1000_release_swfw_sync_80003es2lan(hw, E1000_SWFW_EEP_SM);
पूर्ण

/**
 *  e1000_acquire_swfw_sync_80003es2lan - Acquire SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Acquire the SW/FW semaphore to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're acquiring the lock क्रम.
 **/
अटल s32 e1000_acquire_swfw_sync_80003es2lan(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 i = 0;
	s32 समयout = 50;

	जबतक (i < समयout) अणु
		अगर (e1000e_get_hw_semaphore(hw))
			वापस -E1000_ERR_SWFW_SYNC;

		swfw_sync = er32(SW_FW_SYNC);
		अगर (!(swfw_sync & (fwmask | swmask)))
			अवरोध;

		/* Firmware currently using resource (fwmask)
		 * or other software thपढ़ो using resource (swmask)
		 */
		e1000e_put_hw_semaphore(hw);
		mdelay(5);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		e_dbg("Driver can't access resource, SW_FW_SYNC timeout.\n");
		वापस -E1000_ERR_SWFW_SYNC;
	पूर्ण

	swfw_sync |= swmask;
	ew32(SW_FW_SYNC, swfw_sync);

	e1000e_put_hw_semaphore(hw);

	वापस 0;
पूर्ण

/**
 *  e1000_release_swfw_sync_80003es2lan - Release SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Release the SW/FW semaphore used to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're releasing the lock क्रम.
 **/
अटल व्योम e1000_release_swfw_sync_80003es2lan(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;

	जबतक (e1000e_get_hw_semaphore(hw) != 0)
		; /* Empty */

	swfw_sync = er32(SW_FW_SYNC);
	swfw_sync &= ~mask;
	ew32(SW_FW_SYNC, swfw_sync);

	e1000e_put_hw_semaphore(hw);
पूर्ण

/**
 *  e1000_पढ़ो_phy_reg_gg82563_80003es2lan - Read GG82563 PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of the रेजिस्टर to पढ़ो
 *  @data: poपूर्णांकer to the data वापसed from the operation
 *
 *  Read the GG82563 PHY रेजिस्टर.
 **/
अटल s32 e1000_पढ़ो_phy_reg_gg82563_80003es2lan(काष्ठा e1000_hw *hw,
						  u32 offset, u16 *data)
अणु
	s32 ret_val;
	u32 page_select;
	u16 temp;

	ret_val = e1000_acquire_phy_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Select Configuration Page */
	अगर ((offset & MAX_PHY_REG_ADDRESS) < GG82563_MIN_ALT_REG) अणु
		page_select = GG82563_PHY_PAGE_SELECT;
	पूर्ण अन्यथा अणु
		/* Use Alternative Page Select रेजिस्टर to access
		 * रेजिस्टरs 30 and 31
		 */
		page_select = GG82563_PHY_PAGE_SELECT_ALT;
	पूर्ण

	temp = (u16)((u16)offset >> GG82563_PAGE_SHIFT);
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, page_select, temp);
	अगर (ret_val) अणु
		e1000_release_phy_80003es2lan(hw);
		वापस ret_val;
	पूर्ण

	अगर (hw->dev_spec.e80003es2lan.mdic_wa_enable) अणु
		/* The "ready" bit in the MDIC रेजिस्टर may be incorrectly set
		 * beक्रमe the device has completed the "Page Select" MDI
		 * transaction.  So we रुको 200us after each MDI command...
		 */
		usleep_range(200, 400);

		/* ...and verअगरy the command was successful. */
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, page_select, &temp);

		अगर (((u16)offset >> GG82563_PAGE_SHIFT) != temp) अणु
			e1000_release_phy_80003es2lan(hw);
			वापस -E1000_ERR_PHY;
		पूर्ण

		usleep_range(200, 400);

		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw,
						   MAX_PHY_REG_ADDRESS & offset,
						   data);

		usleep_range(200, 400);
	पूर्ण अन्यथा अणु
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw,
						   MAX_PHY_REG_ADDRESS & offset,
						   data);
	पूर्ण

	e1000_release_phy_80003es2lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_phy_reg_gg82563_80003es2lan - Write GG82563 PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of the रेजिस्टर to पढ़ो
 *  @data: value to ग_लिखो to the रेजिस्टर
 *
 *  Write to the GG82563 PHY रेजिस्टर.
 **/
अटल s32 e1000_ग_लिखो_phy_reg_gg82563_80003es2lan(काष्ठा e1000_hw *hw,
						   u32 offset, u16 data)
अणु
	s32 ret_val;
	u32 page_select;
	u16 temp;

	ret_val = e1000_acquire_phy_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Select Configuration Page */
	अगर ((offset & MAX_PHY_REG_ADDRESS) < GG82563_MIN_ALT_REG) अणु
		page_select = GG82563_PHY_PAGE_SELECT;
	पूर्ण अन्यथा अणु
		/* Use Alternative Page Select रेजिस्टर to access
		 * रेजिस्टरs 30 and 31
		 */
		page_select = GG82563_PHY_PAGE_SELECT_ALT;
	पूर्ण

	temp = (u16)((u16)offset >> GG82563_PAGE_SHIFT);
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, page_select, temp);
	अगर (ret_val) अणु
		e1000_release_phy_80003es2lan(hw);
		वापस ret_val;
	पूर्ण

	अगर (hw->dev_spec.e80003es2lan.mdic_wa_enable) अणु
		/* The "ready" bit in the MDIC रेजिस्टर may be incorrectly set
		 * beक्रमe the device has completed the "Page Select" MDI
		 * transaction.  So we रुको 200us after each MDI command...
		 */
		usleep_range(200, 400);

		/* ...and verअगरy the command was successful. */
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, page_select, &temp);

		अगर (((u16)offset >> GG82563_PAGE_SHIFT) != temp) अणु
			e1000_release_phy_80003es2lan(hw);
			वापस -E1000_ERR_PHY;
		पूर्ण

		usleep_range(200, 400);

		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw,
						    MAX_PHY_REG_ADDRESS &
						    offset, data);

		usleep_range(200, 400);
	पूर्ण अन्यथा अणु
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw,
						    MAX_PHY_REG_ADDRESS &
						    offset, data);
	पूर्ण

	e1000_release_phy_80003es2lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_nvm_80003es2lan - Write to ESB2 NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of the रेजिस्टर to पढ़ो
 *  @words: number of words to ग_लिखो
 *  @data: buffer of data to ग_लिखो to the NVM
 *
 *  Write "words" of data to the ESB2 NVM.
 **/
अटल s32 e1000_ग_लिखो_nvm_80003es2lan(काष्ठा e1000_hw *hw, u16 offset,
				       u16 words, u16 *data)
अणु
	वापस e1000e_ग_लिखो_nvm_spi(hw, offset, words, data);
पूर्ण

/**
 *  e1000_get_cfg_करोne_80003es2lan - Wait क्रम configuration to complete
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Wait a specअगरic amount of समय क्रम manageability processes to complete.
 *  This is a function poपूर्णांकer entry poपूर्णांक called by the phy module.
 **/
अटल s32 e1000_get_cfg_करोne_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 समयout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_PORT_0;

	अगर (hw->bus.func == 1)
		mask = E1000_NVM_CFG_DONE_PORT_1;

	जबतक (समयout) अणु
		अगर (er32(EEMNGCTL) & mask)
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
 *  e1000_phy_क्रमce_speed_duplex_80003es2lan - Force PHY speed and duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Force the speed and duplex settings onto the PHY.  This is a
 *  function poपूर्णांकer entry poपूर्णांक called by the phy module.
 **/
अटल s32 e1000_phy_क्रमce_speed_duplex_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;
	bool link;

	/* Clear Auto-Crossover to क्रमce MDI manually.  M88E1000 requires MDI
	 * क्रमced whenever speed and duplex are क्रमced.
	 */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data &= ~GG82563_PSCR_CROSSOVER_MODE_AUTO;
	ret_val = e1e_wphy(hw, GG82563_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("GG82563 PSCR: %X\n", phy_data);

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	e1000e_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	/* Reset the phy to commit changes. */
	phy_data |= BMCR_RESET;

	ret_val = e1e_wphy(hw, MII_BMCR, phy_data);
	अगर (ret_val)
		वापस ret_val;

	udelay(1);

	अगर (hw->phy.स्वतःneg_रुको_to_complete) अणु
		e_dbg("Waiting for forced speed/duplex link on GG82563 phy.\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;

		अगर (!link) अणु
			/* We didn't get link.
			 * Reset the DSP and cross our fingers.
			 */
			ret_val = e1000e_phy_reset_dsp(hw);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	ret_val = e1e_rphy(hw, GG82563_PHY_MAC_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Resetting the phy means we need to verअगरy the TX_CLK corresponds
	 * to the link speed.  10Mbps -> 2.5MHz, अन्यथा 25MHz.
	 */
	phy_data &= ~GG82563_MSCR_TX_CLK_MASK;
	अगर (hw->mac.क्रमced_speed_duplex & E1000_ALL_10_SPEED)
		phy_data |= GG82563_MSCR_TX_CLK_10MBPS_2_5;
	अन्यथा
		phy_data |= GG82563_MSCR_TX_CLK_100MBPS_25;

	/* In addition, we must re-enable CRS on Tx क्रम both half and full
	 * duplex.
	 */
	phy_data |= GG82563_MSCR_ASSERT_CRS_ON_TX;
	ret_val = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTRL, phy_data);

	वापस ret_val;
पूर्ण

/**
 *  e1000_get_cable_length_80003es2lan - Set approximate cable length
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Find the approximate cable length as measured by the GG82563 PHY.
 *  This is a function poपूर्णांकer entry poपूर्णांक called by the phy module.
 **/
अटल s32 e1000_get_cable_length_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, index;

	ret_val = e1e_rphy(hw, GG82563_PHY_DSP_DISTANCE, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	index = phy_data & GG82563_DSPD_CABLE_LENGTH;

	अगर (index >= GG82563_CABLE_LENGTH_TABLE_SIZE - 5)
		वापस -E1000_ERR_PHY;

	phy->min_cable_length = e1000_gg82563_cable_length_table[index];
	phy->max_cable_length = e1000_gg82563_cable_length_table[index + 5];

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

	वापस 0;
पूर्ण

/**
 *  e1000_get_link_up_info_80003es2lan - Report speed and duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: poपूर्णांकer to speed buffer
 *  @duplex: poपूर्णांकer to duplex buffer
 *
 *  Retrieve the current speed and duplex configuration.
 **/
अटल s32 e1000_get_link_up_info_80003es2lan(काष्ठा e1000_hw *hw, u16 *speed,
					      u16 *duplex)
अणु
	s32 ret_val;

	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		ret_val = e1000e_get_speed_and_duplex_copper(hw, speed, duplex);
		hw->phy.ops.cfg_on_link_up(hw);
	पूर्ण अन्यथा अणु
		ret_val = e1000e_get_speed_and_duplex_fiber_serdes(hw,
								   speed,
								   duplex);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_reset_hw_80003es2lan - Reset the ESB2 controller
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Perक्रमm a global reset to the ESB2 controller.
 **/
अटल s32 e1000_reset_hw_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 kum_reg_data;

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	अगर (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	e1e_flush();

	usleep_range(10000, 11000);

	ctrl = er32(CTRL);

	ret_val = e1000_acquire_phy_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("Issuing a global reset to MAC\n");
	ew32(CTRL, ctrl | E1000_CTRL_RST);
	e1000_release_phy_80003es2lan(hw);

	/* Disable IBIST slave mode (far-end loopback) */
	ret_val =
	    e1000_पढ़ो_kmrn_reg_80003es2lan(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
					    &kum_reg_data);
	अगर (!ret_val) अणु
		kum_reg_data |= E1000_KMRNCTRLSTA_IBIST_DISABLE;
		ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw,
						 E1000_KMRNCTRLSTA_INBAND_PARAM,
						 kum_reg_data);
		अगर (ret_val)
			e_dbg("Error disabling far-end loopback\n");
	पूर्ण अन्यथा अणु
		e_dbg("Error disabling far-end loopback\n");
	पूर्ण

	ret_val = e1000e_get_स्वतः_rd_करोne(hw);
	अगर (ret_val)
		/* We करोn't want to जारी accessing MAC रेजिस्टरs. */
		वापस ret_val;

	/* Clear any pending पूर्णांकerrupt events. */
	ew32(IMC, 0xffffffff);
	er32(ICR);

	वापस e1000_check_alt_mac_addr_generic(hw);
पूर्ण

/**
 *  e1000_init_hw_80003es2lan - Initialize the ESB2 controller
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize the hw bits, LED, VFTA, MTA, link and hw counters.
 **/
अटल s32 e1000_init_hw_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 reg_data;
	s32 ret_val;
	u16 kum_reg_data;
	u16 i;

	e1000_initialize_hw_bits_80003es2lan(hw);

	/* Initialize identअगरication LED */
	ret_val = mac->ops.id_led_init(hw);
	/* An error is not fatal and we should not stop init due to this */
	अगर (ret_val)
		e_dbg("Error initializing identification LED\n");

	/* Disabling VLAN filtering */
	e_dbg("Initializing the IEEE VLAN\n");
	mac->ops.clear_vfta(hw);

	/* Setup the receive address. */
	e1000e_init_rx_addrs(hw, mac->rar_entry_count);

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	क्रम (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Disable IBIST slave mode (far-end loopback) */
	ret_val =
	    e1000_पढ़ो_kmrn_reg_80003es2lan(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
					    &kum_reg_data);
	अगर (!ret_val) अणु
		kum_reg_data |= E1000_KMRNCTRLSTA_IBIST_DISABLE;
		ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw,
						 E1000_KMRNCTRLSTA_INBAND_PARAM,
						 kum_reg_data);
		अगर (ret_val)
			e_dbg("Error disabling far-end loopback\n");
	पूर्ण अन्यथा अणु
		e_dbg("Error disabling far-end loopback\n");
	पूर्ण

	/* Set the transmit descriptor ग_लिखो-back policy */
	reg_data = er32(TXDCTL(0));
	reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC);
	ew32(TXDCTL(0), reg_data);

	/* ...क्रम both queues. */
	reg_data = er32(TXDCTL(1));
	reg_data = ((reg_data & ~E1000_TXDCTL_WTHRESH) |
		    E1000_TXDCTL_FULL_TX_DESC_WB | E1000_TXDCTL_COUNT_DESC);
	ew32(TXDCTL(1), reg_data);

	/* Enable retransmit on late collisions */
	reg_data = er32(TCTL);
	reg_data |= E1000_TCTL_RTLC;
	ew32(TCTL, reg_data);

	/* Configure Gigabit Carry Extend Padding */
	reg_data = er32(TCTL_EXT);
	reg_data &= ~E1000_TCTL_EXT_GCEX_MASK;
	reg_data |= DEFAULT_TCTL_EXT_GCEX_80003ES2LAN;
	ew32(TCTL_EXT, reg_data);

	/* Configure Transmit Inter-Packet Gap */
	reg_data = er32(TIPG);
	reg_data &= ~E1000_TIPG_IPGT_MASK;
	reg_data |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	ew32(TIPG, reg_data);

	reg_data = E1000_READ_REG_ARRAY(hw, E1000_FFLT, 0x0001);
	reg_data &= ~0x00100000;
	E1000_WRITE_REG_ARRAY(hw, E1000_FFLT, 0x0001, reg_data);

	/* शेष to true to enable the MDIC W/A */
	hw->dev_spec.e80003es2lan.mdic_wa_enable = true;

	ret_val =
	    e1000_पढ़ो_kmrn_reg_80003es2lan(hw, E1000_KMRNCTRLSTA_OFFSET >>
					    E1000_KMRNCTRLSTA_OFFSET_SHIFT, &i);
	अगर (!ret_val) अणु
		अगर ((i & E1000_KMRNCTRLSTA_OPMODE_MASK) ==
		    E1000_KMRNCTRLSTA_OPMODE_INBAND_MDIO)
			hw->dev_spec.e80003es2lan.mdic_wa_enable = false;
	पूर्ण

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_80003es2lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_initialize_hw_bits_80003es2lan - Init hw bits of ESB2
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes required hardware-dependent bits needed क्रम normal operation.
 **/
अटल व्योम e1000_initialize_hw_bits_80003es2lan(काष्ठा e1000_hw *hw)
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
	अगर (hw->phy.media_type != e1000_media_type_copper)
		reg &= ~BIT(20);
	ew32(TARC(0), reg);

	/* Transmit Arbitration Control 1 */
	reg = er32(TARC(1));
	अगर (er32(TCTL) & E1000_TCTL_MULR)
		reg &= ~BIT(28);
	अन्यथा
		reg |= BIT(28);
	ew32(TARC(1), reg);

	/* Disable IPv6 extension header parsing because some malक्रमmed
	 * IPv6 headers can hang the Rx.
	 */
	reg = er32(RFCTL);
	reg |= (E1000_RFCTL_IPV6_EX_DIS | E1000_RFCTL_NEW_IPV6_EXT_DIS);
	ew32(RFCTL, reg);
पूर्ण

/**
 *  e1000_copper_link_setup_gg82563_80003es2lan - Configure GG82563 Link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Setup some GG82563 PHY रेजिस्टरs क्रम obtaining link
 **/
अटल s32 e1000_copper_link_setup_gg82563_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u32 reg;
	u16 data;

	ret_val = e1e_rphy(hw, GG82563_PHY_MAC_SPEC_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

	data |= GG82563_MSCR_ASSERT_CRS_ON_TX;
	/* Use 25MHz क्रम both link करोwn and 1000Base-T क्रम Tx घड़ी. */
	data |= GG82563_MSCR_TX_CLK_1000MBPS_25;

	ret_val = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTRL, data);
	अगर (ret_val)
		वापस ret_val;

	/* Options:
	 *   MDI/MDI-X = 0 (शेष)
	 *   0 - Auto क्रम all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto क्रम 1000Base-T only (MDI-X क्रम 10/100Base-T modes)
	 */
	ret_val = e1e_rphy(hw, GG82563_PHY_SPEC_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

	data &= ~GG82563_PSCR_CROSSOVER_MODE_MASK;

	चयन (phy->mdix) अणु
	हाल 1:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDI;
		अवरोध;
	हाल 2:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDIX;
		अवरोध;
	हाल 0:
	शेष:
		data |= GG82563_PSCR_CROSSOVER_MODE_AUTO;
		अवरोध;
	पूर्ण

	/* Options:
	 *   disable_polarity_correction = 0 (शेष)
	 *       Automatic Correction क्रम Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	data &= ~GG82563_PSCR_POLARITY_REVERSAL_DISABLE;
	अगर (phy->disable_polarity_correction)
		data |= GG82563_PSCR_POLARITY_REVERSAL_DISABLE;

	ret_val = e1e_wphy(hw, GG82563_PHY_SPEC_CTRL, data);
	अगर (ret_val)
		वापस ret_val;

	/* SW Reset the PHY so all changes take effect */
	ret_val = hw->phy.ops.commit(hw);
	अगर (ret_val) अणु
		e_dbg("Error Resetting the PHY\n");
		वापस ret_val;
	पूर्ण

	/* Bypass Rx and Tx FIFO's */
	reg = E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL;
	data = (E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS |
		E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS);
	ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw, reg, data);
	अगर (ret_val)
		वापस ret_val;

	reg = E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE;
	ret_val = e1000_पढ़ो_kmrn_reg_80003es2lan(hw, reg, &data);
	अगर (ret_val)
		वापस ret_val;
	data |= E1000_KMRNCTRLSTA_OPMODE_E_IDLE;
	ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw, reg, data);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1e_rphy(hw, GG82563_PHY_SPEC_CTRL_2, &data);
	अगर (ret_val)
		वापस ret_val;

	data &= ~GG82563_PSCR2_REVERSE_AUTO_NEG;
	ret_val = e1e_wphy(hw, GG82563_PHY_SPEC_CTRL_2, data);
	अगर (ret_val)
		वापस ret_val;

	reg = er32(CTRL_EXT);
	reg &= ~E1000_CTRL_EXT_LINK_MODE_MASK;
	ew32(CTRL_EXT, reg);

	ret_val = e1e_rphy(hw, GG82563_PHY_PWR_MGMT_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

	/* Do not init these रेजिस्टरs when the HW is in IAMT mode, since the
	 * firmware will have alपढ़ोy initialized them.  We only initialize
	 * them अगर the HW is not in IAMT mode.
	 */
	अगर (!hw->mac.ops.check_mng_mode(hw)) अणु
		/* Enable Electrical Idle on the PHY */
		data |= GG82563_PMCR_ENABLE_ELECTRICAL_IDLE;
		ret_val = e1e_wphy(hw, GG82563_PHY_PWR_MGMT_CTRL, data);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &data);
		अगर (ret_val)
			वापस ret_val;

		data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;
		ret_val = e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Workaround: Disable padding in Kumeran पूर्णांकerface in the MAC
	 * and in the PHY to aव्योम CRC errors.
	 */
	ret_val = e1e_rphy(hw, GG82563_PHY_INBAND_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

	data |= GG82563_ICR_DIS_PADDING;
	ret_val = e1e_wphy(hw, GG82563_PHY_INBAND_CTRL, data);
	अगर (ret_val)
		वापस ret_val;

	वापस 0;
पूर्ण

/**
 *  e1000_setup_copper_link_80003es2lan - Setup Copper Link क्रम ESB2
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Essentially a wrapper क्रम setting up all things "copper" related.
 *  This is a function poपूर्णांकer entry poपूर्णांक called by the mac module.
 **/
अटल s32 e1000_setup_copper_link_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 reg_data;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ew32(CTRL, ctrl);

	/* Set the mac to रुको the maximum समय between each
	 * iteration and increase the max iterations when
	 * polling the phy; this fixes erroneous समयouts at 10Mbps.
	 */
	ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw, GG82563_REG(0x34, 4),
						   0xFFFF);
	अगर (ret_val)
		वापस ret_val;
	ret_val = e1000_पढ़ो_kmrn_reg_80003es2lan(hw, GG82563_REG(0x34, 9),
						  &reg_data);
	अगर (ret_val)
		वापस ret_val;
	reg_data |= 0x3F;
	ret_val = e1000_ग_लिखो_kmrn_reg_80003es2lan(hw, GG82563_REG(0x34, 9),
						   reg_data);
	अगर (ret_val)
		वापस ret_val;
	ret_val =
	    e1000_पढ़ो_kmrn_reg_80003es2lan(hw,
					    E1000_KMRNCTRLSTA_OFFSET_INB_CTRL,
					    &reg_data);
	अगर (ret_val)
		वापस ret_val;
	reg_data |= E1000_KMRNCTRLSTA_INB_CTRL_DIS_PADDING;
	ret_val =
	    e1000_ग_लिखो_kmrn_reg_80003es2lan(hw,
					     E1000_KMRNCTRLSTA_OFFSET_INB_CTRL,
					     reg_data);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000_copper_link_setup_gg82563_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस e1000e_setup_copper_link(hw);
पूर्ण

/**
 *  e1000_cfg_on_link_up_80003es2lan - es2 link configuration after link-up
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configure the KMRN पूर्णांकerface by applying last minute quirks क्रम
 *  10/100 operation.
 **/
अटल s32 e1000_cfg_on_link_up_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 speed;
	u16 duplex;

	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		ret_val = e1000e_get_speed_and_duplex_copper(hw, &speed,
							     &duplex);
		अगर (ret_val)
			वापस ret_val;

		अगर (speed == SPEED_1000)
			ret_val = e1000_cfg_kmrn_1000_80003es2lan(hw);
		अन्यथा
			ret_val = e1000_cfg_kmrn_10_100_80003es2lan(hw, duplex);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_cfg_kmrn_10_100_80003es2lan - Apply "quirks" क्रम 10/100 operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @duplex: current duplex setting
 *
 *  Configure the KMRN पूर्णांकerface by applying last minute quirks क्रम
 *  10/100 operation.
 **/
अटल s32 e1000_cfg_kmrn_10_100_80003es2lan(काष्ठा e1000_hw *hw, u16 duplex)
अणु
	s32 ret_val;
	u32 tipg;
	u32 i = 0;
	u16 reg_data, reg_data2;

	reg_data = E1000_KMRNCTRLSTA_HD_CTRL_10_100_DEFAULT;
	ret_val =
	    e1000_ग_लिखो_kmrn_reg_80003es2lan(hw,
					     E1000_KMRNCTRLSTA_OFFSET_HD_CTRL,
					     reg_data);
	अगर (ret_val)
		वापस ret_val;

	/* Configure Transmit Inter-Packet Gap */
	tipg = er32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAULT_TIPG_IPGT_10_100_80003ES2LAN;
	ew32(TIPG, tipg);

	करो अणु
		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data2);
		अगर (ret_val)
			वापस ret_val;
		i++;
	पूर्ण जबतक ((reg_data != reg_data2) && (i < GG82563_MAX_KMRN_RETRY));

	अगर (duplex == HALF_DUPLEX)
		reg_data |= GG82563_KMCR_PASS_FALSE_CARRIER;
	अन्यथा
		reg_data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;

	वापस e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, reg_data);
पूर्ण

/**
 *  e1000_cfg_kmrn_1000_80003es2lan - Apply "quirks" क्रम gigabit operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configure the KMRN पूर्णांकerface by applying last minute quirks क्रम
 *  gigabit operation.
 **/
अटल s32 e1000_cfg_kmrn_1000_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 reg_data, reg_data2;
	u32 tipg;
	u32 i = 0;

	reg_data = E1000_KMRNCTRLSTA_HD_CTRL_1000_DEFAULT;
	ret_val =
	    e1000_ग_लिखो_kmrn_reg_80003es2lan(hw,
					     E1000_KMRNCTRLSTA_OFFSET_HD_CTRL,
					     reg_data);
	अगर (ret_val)
		वापस ret_val;

	/* Configure Transmit Inter-Packet Gap */
	tipg = er32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAULT_TIPG_IPGT_1000_80003ES2LAN;
	ew32(TIPG, tipg);

	करो अणु
		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, GG82563_PHY_KMRN_MODE_CTRL, &reg_data2);
		अगर (ret_val)
			वापस ret_val;
		i++;
	पूर्ण जबतक ((reg_data != reg_data2) && (i < GG82563_MAX_KMRN_RETRY));

	reg_data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;

	वापस e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, reg_data);
पूर्ण

/**
 *  e1000_पढ़ो_kmrn_reg_80003es2lan - Read kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquire semaphore, then पढ़ो the PHY रेजिस्टर at offset
 *  using the kumeran पूर्णांकerface.  The inक्रमmation retrieved is stored in data.
 *  Release the semaphore beक्रमe निकासing.
 **/
अटल s32 e1000_पढ़ो_kmrn_reg_80003es2lan(काष्ठा e1000_hw *hw, u32 offset,
					   u16 *data)
अणु
	u32 kmrnctrlsta;
	s32 ret_val;

	ret_val = e1000_acquire_mac_csr_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | E1000_KMRNCTRLSTA_REN;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	kmrnctrlsta = er32(KMRNCTRLSTA);
	*data = (u16)kmrnctrlsta;

	e1000_release_mac_csr_80003es2lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_kmrn_reg_80003es2lan - Write kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquire semaphore, then ग_लिखो the data to PHY रेजिस्टर
 *  at the offset using the kumeran पूर्णांकerface.  Release semaphore
 *  beक्रमe निकासing.
 **/
अटल s32 e1000_ग_लिखो_kmrn_reg_80003es2lan(काष्ठा e1000_hw *hw, u32 offset,
					    u16 data)
अणु
	u32 kmrnctrlsta;
	s32 ret_val;

	ret_val = e1000_acquire_mac_csr_80003es2lan(hw);
	अगर (ret_val)
		वापस ret_val;

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | data;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	e1000_release_mac_csr_80003es2lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_mac_addr_80003es2lan - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_पढ़ो_mac_addr_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	/* If there's an alternate MAC address place it in RAR0
	 * so that it will override the Si installed शेष perm
	 * address.
	 */
	ret_val = e1000_check_alt_mac_addr_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस e1000_पढ़ो_mac_addr_generic(hw);
पूर्ण

/**
 * e1000_घातer_करोwn_phy_copper_80003es2lan - Remove link during PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, हटाओ the link.
 **/
अटल व्योम e1000_घातer_करोwn_phy_copper_80003es2lan(काष्ठा e1000_hw *hw)
अणु
	/* If the management पूर्णांकerface is not enabled, then घातer करोwn */
	अगर (!(hw->mac.ops.check_mng_mode(hw) ||
	      hw->phy.ops.check_reset_block(hw)))
		e1000_घातer_करोwn_phy_copper(hw);
पूर्ण

/**
 *  e1000_clear_hw_cntrs_80003es2lan - Clear device specअगरic hardware counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the hardware counters by पढ़ोing the counter रेजिस्टरs.
 **/
अटल व्योम e1000_clear_hw_cntrs_80003es2lan(काष्ठा e1000_hw *hw)
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

अटल स्थिर काष्ठा e1000_mac_operations es2_mac_ops = अणु
	.पढ़ो_mac_addr		= e1000_पढ़ो_mac_addr_80003es2lan,
	.id_led_init		= e1000e_id_led_init_generic,
	.blink_led		= e1000e_blink_led_generic,
	.check_mng_mode		= e1000e_check_mng_mode_generic,
	/* check_क्रम_link dependent on media type */
	.cleanup_led		= e1000e_cleanup_led_generic,
	.clear_hw_cntrs		= e1000_clear_hw_cntrs_80003es2lan,
	.get_bus_info		= e1000e_get_bus_info_pcie,
	.set_lan_id		= e1000_set_lan_id_multi_port_pcie,
	.get_link_up_info	= e1000_get_link_up_info_80003es2lan,
	.led_on			= e1000e_led_on_generic,
	.led_off		= e1000e_led_off_generic,
	.update_mc_addr_list	= e1000e_update_mc_addr_list_generic,
	.ग_लिखो_vfta		= e1000_ग_लिखो_vfta_generic,
	.clear_vfta		= e1000_clear_vfta_generic,
	.reset_hw		= e1000_reset_hw_80003es2lan,
	.init_hw		= e1000_init_hw_80003es2lan,
	.setup_link		= e1000e_setup_link_generic,
	/* setup_physical_पूर्णांकerface dependent on media type */
	.setup_led		= e1000e_setup_led_generic,
	.config_collision_dist	= e1000e_config_collision_dist_generic,
	.rar_set		= e1000e_rar_set_generic,
	.rar_get_count		= e1000e_rar_get_count_generic,
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations es2_phy_ops = अणु
	.acquire		= e1000_acquire_phy_80003es2lan,
	.check_polarity		= e1000_check_polarity_m88,
	.check_reset_block	= e1000e_check_reset_block_generic,
	.commit			= e1000e_phy_sw_reset,
	.क्रमce_speed_duplex	= e1000_phy_क्रमce_speed_duplex_80003es2lan,
	.get_cfg_करोne		= e1000_get_cfg_करोne_80003es2lan,
	.get_cable_length	= e1000_get_cable_length_80003es2lan,
	.get_info		= e1000e_get_phy_info_m88,
	.पढ़ो_reg		= e1000_पढ़ो_phy_reg_gg82563_80003es2lan,
	.release		= e1000_release_phy_80003es2lan,
	.reset			= e1000e_phy_hw_reset_generic,
	.set_d0_lplu_state	= शून्य,
	.set_d3_lplu_state	= e1000e_set_d3_lplu_state,
	.ग_लिखो_reg		= e1000_ग_लिखो_phy_reg_gg82563_80003es2lan,
	.cfg_on_link_up		= e1000_cfg_on_link_up_80003es2lan,
पूर्ण;

अटल स्थिर काष्ठा e1000_nvm_operations es2_nvm_ops = अणु
	.acquire		= e1000_acquire_nvm_80003es2lan,
	.पढ़ो			= e1000e_पढ़ो_nvm_eerd,
	.release		= e1000_release_nvm_80003es2lan,
	.reload			= e1000e_reload_nvm_generic,
	.update			= e1000e_update_nvm_checksum_generic,
	.valid_led_शेष	= e1000e_valid_led_शेष,
	.validate		= e1000e_validate_nvm_checksum_generic,
	.ग_लिखो			= e1000_ग_लिखो_nvm_80003es2lan,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_es2_info = अणु
	.mac			= e1000_80003es2lan,
	.flags			= FLAG_HAS_HW_VLAN_FILTER
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_HAS_WOL
				  | FLAG_APME_IN_CTRL3
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_RX_NEEDS_RESTART /* errata */
				  | FLAG_TARC_SET_BIT_ZERO /* errata */
				  | FLAG_APME_CHECK_PORT_B
				  | FLAG_DISABLE_FC_PAUSE_TIME, /* errata */
	.flags2			= FLAG2_DMA_BURST,
	.pba			= 38,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_80003es2lan,
	.mac_ops		= &es2_mac_ops,
	.phy_ops		= &es2_phy_ops,
	.nvm_ops		= &es2_nvm_ops,
पूर्ण;

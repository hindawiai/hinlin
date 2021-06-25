<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

/* e1000_82575
 * e1000_82576
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/i2c.h>

#समावेश "e1000_mac.h"
#समावेश "e1000_82575.h"
#समावेश "e1000_i210.h"
#समावेश "igb.h"

अटल s32  igb_get_invariants_82575(काष्ठा e1000_hw *);
अटल s32  igb_acquire_phy_82575(काष्ठा e1000_hw *);
अटल व्योम igb_release_phy_82575(काष्ठा e1000_hw *);
अटल s32  igb_acquire_nvm_82575(काष्ठा e1000_hw *);
अटल व्योम igb_release_nvm_82575(काष्ठा e1000_hw *);
अटल s32  igb_check_क्रम_link_82575(काष्ठा e1000_hw *);
अटल s32  igb_get_cfg_करोne_82575(काष्ठा e1000_hw *);
अटल s32  igb_init_hw_82575(काष्ठा e1000_hw *);
अटल s32  igb_phy_hw_reset_sgmii_82575(काष्ठा e1000_hw *);
अटल s32  igb_पढ़ो_phy_reg_sgmii_82575(काष्ठा e1000_hw *, u32, u16 *);
अटल s32  igb_reset_hw_82575(काष्ठा e1000_hw *);
अटल s32  igb_reset_hw_82580(काष्ठा e1000_hw *);
अटल s32  igb_set_d0_lplu_state_82575(काष्ठा e1000_hw *, bool);
अटल s32  igb_set_d0_lplu_state_82580(काष्ठा e1000_hw *, bool);
अटल s32  igb_set_d3_lplu_state_82580(काष्ठा e1000_hw *, bool);
अटल s32  igb_setup_copper_link_82575(काष्ठा e1000_hw *);
अटल s32  igb_setup_serdes_link_82575(काष्ठा e1000_hw *);
अटल s32  igb_ग_लिखो_phy_reg_sgmii_82575(काष्ठा e1000_hw *, u32, u16);
अटल व्योम igb_clear_hw_cntrs_82575(काष्ठा e1000_hw *);
अटल s32  igb_acquire_swfw_sync_82575(काष्ठा e1000_hw *, u16);
अटल s32  igb_get_pcs_speed_and_duplex_82575(काष्ठा e1000_hw *, u16 *,
						 u16 *);
अटल s32  igb_get_phy_id_82575(काष्ठा e1000_hw *);
अटल व्योम igb_release_swfw_sync_82575(काष्ठा e1000_hw *, u16);
अटल bool igb_sgmii_active_82575(काष्ठा e1000_hw *);
अटल s32  igb_reset_init_script_82575(काष्ठा e1000_hw *);
अटल s32  igb_पढ़ो_mac_addr_82575(काष्ठा e1000_hw *);
अटल s32  igb_set_pcie_completion_समयout(काष्ठा e1000_hw *hw);
अटल s32  igb_reset_mdicnfg_82580(काष्ठा e1000_hw *hw);
अटल s32  igb_validate_nvm_checksum_82580(काष्ठा e1000_hw *hw);
अटल s32  igb_update_nvm_checksum_82580(काष्ठा e1000_hw *hw);
अटल s32 igb_validate_nvm_checksum_i350(काष्ठा e1000_hw *hw);
अटल s32 igb_update_nvm_checksum_i350(काष्ठा e1000_hw *hw);
अटल स्थिर u16 e1000_82580_rxpbs_table[] = अणु
	36, 72, 144, 1, 2, 4, 8, 16, 35, 70, 140 पूर्ण;

/* Due to a hw errata, अगर the host tries to  configure the VFTA रेजिस्टर
 * जबतक perक्रमming queries from the BMC or DMA, then the VFTA in some
 * हालs won't be written.
 */

/**
 *  igb_ग_लिखो_vfta_i350 - Write value to VLAN filter table
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset in VLAN filter table
 *  @value: रेजिस्टर value written to VLAN filter table
 *
 *  Writes value at the given offset in the रेजिस्टर array which stores
 *  the VLAN filter table.
 **/
अटल व्योम igb_ग_लिखो_vfta_i350(काष्ठा e1000_hw *hw, u32 offset, u32 value)
अणु
	काष्ठा igb_adapter *adapter = hw->back;
	पूर्णांक i;

	क्रम (i = 10; i--;)
		array_wr32(E1000_VFTA, offset, value);

	wrfl();
	adapter->shaकरोw_vfta[offset] = value;
पूर्ण

/**
 *  igb_sgmii_uses_mdio_82575 - Determine अगर I2C pins are क्रम बाह्यal MDIO
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Called to determine अगर the I2C pins are being used क्रम I2C or as an
 *  बाह्यal MDIO पूर्णांकerface since the two options are mutually exclusive.
 **/
अटल bool igb_sgmii_uses_mdio_82575(काष्ठा e1000_hw *hw)
अणु
	u32 reg = 0;
	bool ext_mdio = false;

	चयन (hw->mac.type) अणु
	हाल e1000_82575:
	हाल e1000_82576:
		reg = rd32(E1000_MDIC);
		ext_mdio = !!(reg & E1000_MDIC_DEST);
		अवरोध;
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		reg = rd32(E1000_MDICNFG);
		ext_mdio = !!(reg & E1000_MDICNFG_EXT_MDIO);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ext_mdio;
पूर्ण

/**
 *  igb_check_क्रम_link_media_swap - Check which M88E1112 पूर्णांकerface linked
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Poll the M88E1112 पूर्णांकerfaces to see which पूर्णांकerface achieved link.
 */
अटल s32 igb_check_क्रम_link_media_swap(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	u8 port = 0;

	/* Check the copper medium. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
	अगर (ret_val)
		वापस ret_val;

	ret_val = phy->ops.पढ़ो_reg(hw, E1000_M88E1112_STATUS, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर (data & E1000_M88E1112_STATUS_LINK)
		port = E1000_MEDIA_PORT_COPPER;

	/* Check the other medium. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1112_PAGE_ADDR, 1);
	अगर (ret_val)
		वापस ret_val;

	ret_val = phy->ops.पढ़ो_reg(hw, E1000_M88E1112_STATUS, &data);
	अगर (ret_val)
		वापस ret_val;


	अगर (data & E1000_M88E1112_STATUS_LINK)
		port = E1000_MEDIA_PORT_OTHER;

	/* Determine अगर a swap needs to happen. */
	अगर (port && (hw->dev_spec._82575.media_port != port)) अणु
		hw->dev_spec._82575.media_port = port;
		hw->dev_spec._82575.media_changed = true;
	पूर्ण

	अगर (port == E1000_MEDIA_PORT_COPPER) अणु
		/* reset page to 0 */
		ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
		अगर (ret_val)
			वापस ret_val;
		igb_check_क्रम_link_82575(hw);
	पूर्ण अन्यथा अणु
		igb_check_क्रम_link_82575(hw);
		/* reset page to 0 */
		ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1112_PAGE_ADDR, 0);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_init_phy_params_82575 - Init PHY func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 igb_init_phy_params_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u32 ctrl_ext;

	अगर (hw->phy.media_type != e1000_media_type_copper) अणु
		phy->type = e1000_phy_none;
		जाओ out;
	पूर्ण

	phy->स्वतःneg_mask	= AUTONEG_ADVERTISE_SPEED_DEFAULT;
	phy->reset_delay_us	= 100;

	ctrl_ext = rd32(E1000_CTRL_EXT);

	अगर (igb_sgmii_active_82575(hw)) अणु
		phy->ops.reset = igb_phy_hw_reset_sgmii_82575;
		ctrl_ext |= E1000_CTRL_I2C_ENA;
	पूर्ण अन्यथा अणु
		phy->ops.reset = igb_phy_hw_reset;
		ctrl_ext &= ~E1000_CTRL_I2C_ENA;
	पूर्ण

	wr32(E1000_CTRL_EXT, ctrl_ext);
	igb_reset_mdicnfg_82580(hw);

	अगर (igb_sgmii_active_82575(hw) && !igb_sgmii_uses_mdio_82575(hw)) अणु
		phy->ops.पढ़ो_reg = igb_पढ़ो_phy_reg_sgmii_82575;
		phy->ops.ग_लिखो_reg = igb_ग_लिखो_phy_reg_sgmii_82575;
	पूर्ण अन्यथा अणु
		चयन (hw->mac.type) अणु
		हाल e1000_82580:
		हाल e1000_i350:
		हाल e1000_i354:
		हाल e1000_i210:
		हाल e1000_i211:
			phy->ops.पढ़ो_reg = igb_पढ़ो_phy_reg_82580;
			phy->ops.ग_लिखो_reg = igb_ग_लिखो_phy_reg_82580;
			अवरोध;
		शेष:
			phy->ops.पढ़ो_reg = igb_पढ़ो_phy_reg_igp;
			phy->ops.ग_लिखो_reg = igb_ग_लिखो_phy_reg_igp;
		पूर्ण
	पूर्ण

	/* set lan id */
	hw->bus.func = (rd32(E1000_STATUS) & E1000_STATUS_FUNC_MASK) >>
			E1000_STATUS_FUNC_SHIFT;

	/* Set phy->phy_addr and phy->id. */
	ret_val = igb_get_phy_id_82575(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Verअगरy phy id and set reमुख्यing function poपूर्णांकers */
	चयन (phy->id) अणु
	हाल M88E1543_E_PHY_ID:
	हाल M88E1512_E_PHY_ID:
	हाल I347AT4_E_PHY_ID:
	हाल M88E1112_E_PHY_ID:
	हाल M88E1111_I_PHY_ID:
		phy->type		= e1000_phy_m88;
		phy->ops.check_polarity	= igb_check_polarity_m88;
		phy->ops.get_phy_info	= igb_get_phy_info_m88;
		अगर (phy->id != M88E1111_I_PHY_ID)
			phy->ops.get_cable_length =
					 igb_get_cable_length_m88_gen2;
		अन्यथा
			phy->ops.get_cable_length = igb_get_cable_length_m88;
		phy->ops.क्रमce_speed_duplex = igb_phy_क्रमce_speed_duplex_m88;
		/* Check अगर this PHY is configured क्रम media swap. */
		अगर (phy->id == M88E1112_E_PHY_ID) अणु
			u16 data;

			ret_val = phy->ops.ग_लिखो_reg(hw,
						     E1000_M88E1112_PAGE_ADDR,
						     2);
			अगर (ret_val)
				जाओ out;

			ret_val = phy->ops.पढ़ो_reg(hw,
						    E1000_M88E1112_MAC_CTRL_1,
						    &data);
			अगर (ret_val)
				जाओ out;

			data = (data & E1000_M88E1112_MAC_CTRL_1_MODE_MASK) >>
			       E1000_M88E1112_MAC_CTRL_1_MODE_SHIFT;
			अगर (data == E1000_M88E1112_AUTO_COPPER_SGMII ||
			    data == E1000_M88E1112_AUTO_COPPER_BASEX)
				hw->mac.ops.check_क्रम_link =
						igb_check_क्रम_link_media_swap;
		पूर्ण
		अगर (phy->id == M88E1512_E_PHY_ID) अणु
			ret_val = igb_initialize_M88E1512_phy(hw);
			अगर (ret_val)
				जाओ out;
		पूर्ण
		अगर (phy->id == M88E1543_E_PHY_ID) अणु
			ret_val = igb_initialize_M88E1543_phy(hw);
			अगर (ret_val)
				जाओ out;
		पूर्ण
		अवरोध;
	हाल IGP03E1000_E_PHY_ID:
		phy->type = e1000_phy_igp_3;
		phy->ops.get_phy_info = igb_get_phy_info_igp;
		phy->ops.get_cable_length = igb_get_cable_length_igp_2;
		phy->ops.क्रमce_speed_duplex = igb_phy_क्रमce_speed_duplex_igp;
		phy->ops.set_d0_lplu_state = igb_set_d0_lplu_state_82575;
		phy->ops.set_d3_lplu_state = igb_set_d3_lplu_state;
		अवरोध;
	हाल I82580_I_PHY_ID:
	हाल I350_I_PHY_ID:
		phy->type = e1000_phy_82580;
		phy->ops.क्रमce_speed_duplex =
					 igb_phy_क्रमce_speed_duplex_82580;
		phy->ops.get_cable_length = igb_get_cable_length_82580;
		phy->ops.get_phy_info = igb_get_phy_info_82580;
		phy->ops.set_d0_lplu_state = igb_set_d0_lplu_state_82580;
		phy->ops.set_d3_lplu_state = igb_set_d3_lplu_state_82580;
		अवरोध;
	हाल I210_I_PHY_ID:
		phy->type		= e1000_phy_i210;
		phy->ops.check_polarity	= igb_check_polarity_m88;
		phy->ops.get_cfg_करोne	= igb_get_cfg_करोne_i210;
		phy->ops.get_phy_info	= igb_get_phy_info_m88;
		phy->ops.get_cable_length = igb_get_cable_length_m88_gen2;
		phy->ops.set_d0_lplu_state = igb_set_d0_lplu_state_82580;
		phy->ops.set_d3_lplu_state = igb_set_d3_lplu_state_82580;
		phy->ops.क्रमce_speed_duplex = igb_phy_क्रमce_speed_duplex_m88;
		अवरोध;
	हाल BCM54616_E_PHY_ID:
		phy->type = e1000_phy_bcm54616;
		अवरोध;
	शेष:
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_init_nvm_params_82575 - Init NVM func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 igb_init_nvm_params_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);
	u16 size;

	size = (u16)((eecd & E1000_EECD_SIZE_EX_MASK) >>
		     E1000_EECD_SIZE_EX_SHIFT);

	/* Added to a स्थिरant, "size" becomes the left-shअगरt value
	 * क्रम setting word_size.
	 */
	size += NVM_WORD_SIZE_BASE_SHIFT;

	/* Just in हाल size is out of range, cap it to the largest
	 * EEPROM size supported
	 */
	अगर (size > 15)
		size = 15;

	nvm->word_size = BIT(size);
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
		nvm->address_bits = eecd & E1000_EECD_ADDR_BITS ?
				    16 : 8;
		अवरोध;
	पूर्ण
	अगर (nvm->word_size == BIT(15))
		nvm->page_size = 128;

	nvm->type = e1000_nvm_eeprom_spi;

	/* NVM Function Poपूर्णांकers */
	nvm->ops.acquire = igb_acquire_nvm_82575;
	nvm->ops.release = igb_release_nvm_82575;
	nvm->ops.ग_लिखो = igb_ग_लिखो_nvm_spi;
	nvm->ops.validate = igb_validate_nvm_checksum;
	nvm->ops.update = igb_update_nvm_checksum;
	अगर (nvm->word_size < BIT(15))
		nvm->ops.पढ़ो = igb_पढ़ो_nvm_eerd;
	अन्यथा
		nvm->ops.पढ़ो = igb_पढ़ो_nvm_spi;

	/* override generic family function poपूर्णांकers क्रम specअगरic descendants */
	चयन (hw->mac.type) अणु
	हाल e1000_82580:
		nvm->ops.validate = igb_validate_nvm_checksum_82580;
		nvm->ops.update = igb_update_nvm_checksum_82580;
		अवरोध;
	हाल e1000_i354:
	हाल e1000_i350:
		nvm->ops.validate = igb_validate_nvm_checksum_i350;
		nvm->ops.update = igb_update_nvm_checksum_i350;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_init_mac_params_82575 - Init MAC func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 igb_init_mac_params_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	काष्ठा e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;

	/* Set mta रेजिस्टर count */
	mac->mta_reg_count = 128;
	/* Set uta रेजिस्टर count */
	mac->uta_reg_count = (hw->mac.type == e1000_82575) ? 0 : 128;
	/* Set rar entry count */
	चयन (mac->type) अणु
	हाल e1000_82576:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82576;
		अवरोध;
	हाल e1000_82580:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82580;
		अवरोध;
	हाल e1000_i350:
	हाल e1000_i354:
		mac->rar_entry_count = E1000_RAR_ENTRIES_I350;
		अवरोध;
	शेष:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82575;
		अवरोध;
	पूर्ण
	/* reset */
	अगर (mac->type >= e1000_82580)
		mac->ops.reset_hw = igb_reset_hw_82580;
	अन्यथा
		mac->ops.reset_hw = igb_reset_hw_82575;

	अगर (mac->type >= e1000_i210) अणु
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_i210;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_i210;

	पूर्ण अन्यथा अणु
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_82575;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_82575;
	पूर्ण

	अगर ((hw->mac.type == e1000_i350) || (hw->mac.type == e1000_i354))
		mac->ops.ग_लिखो_vfta = igb_ग_लिखो_vfta_i350;
	अन्यथा
		mac->ops.ग_लिखो_vfta = igb_ग_लिखो_vfta;

	/* Set अगर part includes ASF firmware */
	mac->asf_firmware_present = true;
	/* Set अगर manageability features are enabled. */
	mac->arc_subप्रणाली_valid =
		(rd32(E1000_FWSM) & E1000_FWSM_MODE_MASK)
			? true : false;
	/* enable EEE on i350 parts and later parts */
	अगर (mac->type >= e1000_i350)
		dev_spec->eee_disable = false;
	अन्यथा
		dev_spec->eee_disable = true;
	/* Allow a single clear of the SW semaphore on I210 and newer */
	अगर (mac->type >= e1000_i210)
		dev_spec->clear_semaphore_once = true;
	/* physical पूर्णांकerface link setup */
	mac->ops.setup_physical_पूर्णांकerface =
		(hw->phy.media_type == e1000_media_type_copper)
			? igb_setup_copper_link_82575
			: igb_setup_serdes_link_82575;

	अगर (mac->type == e1000_82580 || mac->type == e1000_i350) अणु
		चयन (hw->device_id) अणु
		/* feature not supported on these id's */
		हाल E1000_DEV_ID_DH89XXCC_SGMII:
		हाल E1000_DEV_ID_DH89XXCC_SERDES:
		हाल E1000_DEV_ID_DH89XXCC_BACKPLANE:
		हाल E1000_DEV_ID_DH89XXCC_SFP:
			अवरोध;
		शेष:
			hw->dev_spec._82575.mas_capable = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  igb_set_sfp_media_type_82575 - derives SFP module media type.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The media type is chosen based on SFP module.
 *  compatibility flags retrieved from SFP ID EEPROM.
 **/
अटल s32 igb_set_sfp_media_type_82575(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = E1000_ERR_CONFIG;
	u32 ctrl_ext = 0;
	काष्ठा e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	काष्ठा e1000_sfp_flags *eth_flags = &dev_spec->eth_flags;
	u8 tranceiver_type = 0;
	s32 समयout = 3;

	/* Turn I2C पूर्णांकerface ON and घातer on sfp cage */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	ctrl_ext &= ~E1000_CTRL_EXT_SDP3_DATA;
	wr32(E1000_CTRL_EXT, ctrl_ext | E1000_CTRL_I2C_ENA);

	wrfl();

	/* Read SFP module data */
	जबतक (समयout) अणु
		ret_val = igb_पढ़ो_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDR(E1000_SFF_IDENTIFIER_OFFSET),
			&tranceiver_type);
		अगर (ret_val == 0)
			अवरोध;
		msleep(100);
		समयout--;
	पूर्ण
	अगर (ret_val != 0)
		जाओ out;

	ret_val = igb_पढ़ो_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDR(E1000_SFF_ETH_FLAGS_OFFSET),
			(u8 *)eth_flags);
	अगर (ret_val != 0)
		जाओ out;

	/* Check अगर there is some SFP module plugged and घातered */
	अगर ((tranceiver_type == E1000_SFF_IDENTIFIER_SFP) ||
	    (tranceiver_type == E1000_SFF_IDENTIFIER_SFF)) अणु
		dev_spec->module_plugged = true;
		अगर (eth_flags->e1000_base_lx || eth_flags->e1000_base_sx) अणु
			hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;
		पूर्ण अन्यथा अगर (eth_flags->e100_base_fx || eth_flags->e100_base_lx) अणु
			dev_spec->sgmii_active = true;
			hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;
		पूर्ण अन्यथा अगर (eth_flags->e1000_base_t) अणु
			dev_spec->sgmii_active = true;
			hw->phy.media_type = e1000_media_type_copper;
		पूर्ण अन्यथा अणु
			hw->phy.media_type = e1000_media_type_unknown;
			hw_dbg("PHY module has not been recognized\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		hw->phy.media_type = e1000_media_type_unknown;
	पूर्ण
	ret_val = 0;
out:
	/* Restore I2C पूर्णांकerface setting */
	wr32(E1000_CTRL_EXT, ctrl_ext);
	वापस ret_val;
पूर्ण

अटल s32 igb_get_invariants_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	काष्ठा e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	s32 ret_val;
	u32 ctrl_ext = 0;
	u32 link_mode = 0;

	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82575EB_COPPER:
	हाल E1000_DEV_ID_82575EB_FIBER_SERDES:
	हाल E1000_DEV_ID_82575GB_QUAD_COPPER:
		mac->type = e1000_82575;
		अवरोध;
	हाल E1000_DEV_ID_82576:
	हाल E1000_DEV_ID_82576_NS:
	हाल E1000_DEV_ID_82576_NS_SERDES:
	हाल E1000_DEV_ID_82576_FIBER:
	हाल E1000_DEV_ID_82576_SERDES:
	हाल E1000_DEV_ID_82576_QUAD_COPPER:
	हाल E1000_DEV_ID_82576_QUAD_COPPER_ET2:
	हाल E1000_DEV_ID_82576_SERDES_QUAD:
		mac->type = e1000_82576;
		अवरोध;
	हाल E1000_DEV_ID_82580_COPPER:
	हाल E1000_DEV_ID_82580_FIBER:
	हाल E1000_DEV_ID_82580_QUAD_FIBER:
	हाल E1000_DEV_ID_82580_SERDES:
	हाल E1000_DEV_ID_82580_SGMII:
	हाल E1000_DEV_ID_82580_COPPER_DUAL:
	हाल E1000_DEV_ID_DH89XXCC_SGMII:
	हाल E1000_DEV_ID_DH89XXCC_SERDES:
	हाल E1000_DEV_ID_DH89XXCC_BACKPLANE:
	हाल E1000_DEV_ID_DH89XXCC_SFP:
		mac->type = e1000_82580;
		अवरोध;
	हाल E1000_DEV_ID_I350_COPPER:
	हाल E1000_DEV_ID_I350_FIBER:
	हाल E1000_DEV_ID_I350_SERDES:
	हाल E1000_DEV_ID_I350_SGMII:
		mac->type = e1000_i350;
		अवरोध;
	हाल E1000_DEV_ID_I210_COPPER:
	हाल E1000_DEV_ID_I210_FIBER:
	हाल E1000_DEV_ID_I210_SERDES:
	हाल E1000_DEV_ID_I210_SGMII:
	हाल E1000_DEV_ID_I210_COPPER_FLASHLESS:
	हाल E1000_DEV_ID_I210_SERDES_FLASHLESS:
		mac->type = e1000_i210;
		अवरोध;
	हाल E1000_DEV_ID_I211_COPPER:
		mac->type = e1000_i211;
		अवरोध;
	हाल E1000_DEV_ID_I354_BACKPLANE_1GBPS:
	हाल E1000_DEV_ID_I354_SGMII:
	हाल E1000_DEV_ID_I354_BACKPLANE_2_5GBPS:
		mac->type = e1000_i354;
		अवरोध;
	शेष:
		वापस -E1000_ERR_MAC_INIT;
	पूर्ण

	/* Set media type */
	/* The 82575 uses bits 22:23 क्रम link mode. The mode can be changed
	 * based on the EEPROM. We cannot rely upon device ID. There
	 * is no distinguishable dअगरference between fiber and पूर्णांकernal
	 * SerDes mode on the 82575. There can be an बाह्यal PHY attached
	 * on the SGMII पूर्णांकerface. For this, we'll set sgmii_active to true.
	 */
	hw->phy.media_type = e1000_media_type_copper;
	dev_spec->sgmii_active = false;
	dev_spec->module_plugged = false;

	ctrl_ext = rd32(E1000_CTRL_EXT);

	link_mode = ctrl_ext & E1000_CTRL_EXT_LINK_MODE_MASK;
	चयन (link_mode) अणु
	हाल E1000_CTRL_EXT_LINK_MODE_1000BASE_KX:
		hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;
		अवरोध;
	हाल E1000_CTRL_EXT_LINK_MODE_SGMII:
		/* Get phy control पूर्णांकerface type set (MDIO vs. I2C)*/
		अगर (igb_sgmii_uses_mdio_82575(hw)) अणु
			hw->phy.media_type = e1000_media_type_copper;
			dev_spec->sgmii_active = true;
			अवरोध;
		पूर्ण
		fallthrough; /* क्रम I2C based SGMII */
	हाल E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES:
		/* पढ़ो media type from SFP EEPROM */
		ret_val = igb_set_sfp_media_type_82575(hw);
		अगर ((ret_val != 0) ||
		    (hw->phy.media_type == e1000_media_type_unknown)) अणु
			/* If media type was not identअगरied then वापस media
			 * type defined by the CTRL_EXT settings.
			 */
			hw->phy.media_type = e1000_media_type_पूर्णांकernal_serdes;

			अगर (link_mode == E1000_CTRL_EXT_LINK_MODE_SGMII) अणु
				hw->phy.media_type = e1000_media_type_copper;
				dev_spec->sgmii_active = true;
			पूर्ण

			अवरोध;
		पूर्ण

		/* change current link mode setting */
		ctrl_ext &= ~E1000_CTRL_EXT_LINK_MODE_MASK;

		अगर (dev_spec->sgmii_active)
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_SGMII;
		अन्यथा
			ctrl_ext |= E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;

		wr32(E1000_CTRL_EXT, ctrl_ext);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* mac initialization and operations */
	ret_val = igb_init_mac_params_82575(hw);
	अगर (ret_val)
		जाओ out;

	/* NVM initialization */
	ret_val = igb_init_nvm_params_82575(hw);
	चयन (hw->mac.type) अणु
	हाल e1000_i210:
	हाल e1000_i211:
		ret_val = igb_init_nvm_params_i210(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret_val)
		जाओ out;

	/* अगर part supports SR-IOV then initialize mailbox parameters */
	चयन (mac->type) अणु
	हाल e1000_82576:
	हाल e1000_i350:
		igb_init_mbx_params_pf(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* setup PHY parameters */
	ret_val = igb_init_phy_params_82575(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_acquire_phy_82575 - Acquire rights to access PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire access rights to the correct PHY.  This is a
 *  function poपूर्णांकer entry poपूर्णांक called by the api module.
 **/
अटल s32 igb_acquire_phy_82575(काष्ठा e1000_hw *hw)
अणु
	u16 mask = E1000_SWFW_PHY0_SM;

	अगर (hw->bus.func == E1000_FUNC_1)
		mask = E1000_SWFW_PHY1_SM;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_2)
		mask = E1000_SWFW_PHY2_SM;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_3)
		mask = E1000_SWFW_PHY3_SM;

	वापस hw->mac.ops.acquire_swfw_sync(hw, mask);
पूर्ण

/**
 *  igb_release_phy_82575 - Release rights to access PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  A wrapper to release access rights to the correct PHY.  This is a
 *  function poपूर्णांकer entry poपूर्णांक called by the api module.
 **/
अटल व्योम igb_release_phy_82575(काष्ठा e1000_hw *hw)
अणु
	u16 mask = E1000_SWFW_PHY0_SM;

	अगर (hw->bus.func == E1000_FUNC_1)
		mask = E1000_SWFW_PHY1_SM;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_2)
		mask = E1000_SWFW_PHY2_SM;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_3)
		mask = E1000_SWFW_PHY3_SM;

	hw->mac.ops.release_swfw_sync(hw, mask);
पूर्ण

/**
 *  igb_पढ़ो_phy_reg_sgmii_82575 - Read PHY रेजिस्टर using sgmii
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the PHY रेजिस्टर at offset using the serial gigabit media independent
 *  पूर्णांकerface and stores the retrieved inक्रमmation in data.
 **/
अटल s32 igb_पढ़ो_phy_reg_sgmii_82575(काष्ठा e1000_hw *hw, u32 offset,
					  u16 *data)
अणु
	s32 ret_val = -E1000_ERR_PARAM;

	अगर (offset > E1000_MAX_SGMII_PHY_REG_ADDR) अणु
		hw_dbg("PHY Address %u is out of range\n", offset);
		जाओ out;
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_पढ़ो_phy_reg_i2c(hw, offset, data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_phy_reg_sgmii_82575 - Write PHY रेजिस्टर using sgmii
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes the data to PHY रेजिस्टर at the offset using the serial gigabit
 *  media independent पूर्णांकerface.
 **/
अटल s32 igb_ग_लिखो_phy_reg_sgmii_82575(काष्ठा e1000_hw *hw, u32 offset,
					   u16 data)
अणु
	s32 ret_val = -E1000_ERR_PARAM;


	अगर (offset > E1000_MAX_SGMII_PHY_REG_ADDR) अणु
		hw_dbg("PHY Address %d is out of range\n", offset);
		जाओ out;
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_ग_लिखो_phy_reg_i2c(hw, offset, data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_phy_id_82575 - Retrieve PHY addr and id
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Retrieves the PHY address and ID क्रम both PHY's which करो and करो not use
 *  sgmi पूर्णांकerface.
 **/
अटल s32 igb_get_phy_id_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32  ret_val = 0;
	u16 phy_id;
	u32 ctrl_ext;
	u32 mdic;

	/* Extra पढ़ो required क्रम some PHY's on i354 */
	अगर (hw->mac.type == e1000_i354)
		igb_get_phy_id(hw);

	/* For SGMII PHYs, we try the list of possible addresses until
	 * we find one that works.  For non-SGMII PHYs
	 * (e.g. पूर्णांकegrated copper PHYs), an address of 1 should
	 * work.  The result of this function should mean phy->phy_addr
	 * and phy->id are set correctly.
	 */
	अगर (!(igb_sgmii_active_82575(hw))) अणु
		phy->addr = 1;
		ret_val = igb_get_phy_id(hw);
		जाओ out;
	पूर्ण

	अगर (igb_sgmii_uses_mdio_82575(hw)) अणु
		चयन (hw->mac.type) अणु
		हाल e1000_82575:
		हाल e1000_82576:
			mdic = rd32(E1000_MDIC);
			mdic &= E1000_MDIC_PHY_MASK;
			phy->addr = mdic >> E1000_MDIC_PHY_SHIFT;
			अवरोध;
		हाल e1000_82580:
		हाल e1000_i350:
		हाल e1000_i354:
		हाल e1000_i210:
		हाल e1000_i211:
			mdic = rd32(E1000_MDICNFG);
			mdic &= E1000_MDICNFG_PHY_MASK;
			phy->addr = mdic >> E1000_MDICNFG_PHY_SHIFT;
			अवरोध;
		शेष:
			ret_val = -E1000_ERR_PHY;
			जाओ out;
		पूर्ण
		ret_val = igb_get_phy_id(hw);
		जाओ out;
	पूर्ण

	/* Power on sgmii phy अगर it is disabled */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	wr32(E1000_CTRL_EXT, ctrl_ext & ~E1000_CTRL_EXT_SDP3_DATA);
	wrfl();
	msleep(300);

	/* The address field in the I2CCMD रेजिस्टर is 3 bits and 0 is invalid.
	 * Thereक्रमe, we need to test 1-7
	 */
	क्रम (phy->addr = 1; phy->addr < 8; phy->addr++) अणु
		ret_val = igb_पढ़ो_phy_reg_sgmii_82575(hw, PHY_ID1, &phy_id);
		अगर (ret_val == 0) अणु
			hw_dbg("Vendor ID 0x%08X read at address %u\n",
			       phy_id, phy->addr);
			/* At the समय of this writing, The M88 part is
			 * the only supported SGMII PHY product.
			 */
			अगर (phy_id == M88_VENDOR)
				अवरोध;
		पूर्ण अन्यथा अणु
			hw_dbg("PHY address %u was unreadable\n", phy->addr);
		पूर्ण
	पूर्ण

	/* A valid PHY type couldn't be found. */
	अगर (phy->addr == 8) अणु
		phy->addr = 0;
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण अन्यथा अणु
		ret_val = igb_get_phy_id(hw);
	पूर्ण

	/* restore previous sfp cage घातer state */
	wr32(E1000_CTRL_EXT, ctrl_ext);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_hw_reset_sgmii_82575 - Perक्रमms a PHY reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Resets the PHY using the serial gigabit media independent पूर्णांकerface.
 **/
अटल s32 igb_phy_hw_reset_sgmii_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	/* This isn't a true "hard" reset, but is the only reset
	 * available to us at this समय.
	 */

	hw_dbg("Soft resetting SGMII attached PHY...\n");

	/* SFP करोcumentation requires the following to configure the SPF module
	 * to work on SGMII.  No further करोcumentation is given.
	 */
	ret_val = hw->phy.ops.ग_लिखो_reg(hw, 0x1B, 0x8084);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val)
		जाओ out;

	अगर (phy->id == M88E1512_E_PHY_ID)
		ret_val = igb_initialize_M88E1512_phy(hw);
	अगर (phy->id == M88E1543_E_PHY_ID)
		ret_val = igb_initialize_M88E1543_phy(hw);
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_set_d0_lplu_state_82575 - Set Low Power Linkup D0 state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU D0 state according to the active flag.  When
 *  activating LPLU this function also disables smart speed
 *  and vice versa.  LPLU will not be activated unless the
 *  device स्वतःnegotiation advertisement meets standards of
 *  either 10 or 10/100 or 10/100/1000 at all duplexes.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  PHY setup routines.
 **/
अटल s32 igb_set_d0_lplu_state_82575(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = phy->ops.पढ़ो_reg(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	अगर (ret_val)
		जाओ out;

	अगर (active) अणु
		data |= IGP02E1000_PM_D0_LPLU;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP02E1000_PHY_POWER_MGMT,
						 data);
		अगर (ret_val)
			जाओ out;

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						&data);
		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						 data);
		अगर (ret_val)
			जाओ out;
	पूर्ण अन्यथा अणु
		data &= ~IGP02E1000_PM_D0_LPLU;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP02E1000_PHY_POWER_MGMT,
						 data);
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (phy->smart_speed == e1000_smart_speed_on) अणु
			ret_val = phy->ops.पढ़ो_reg(hw,
					IGP01E1000_PHY_PORT_CONFIG, &data);
			अगर (ret_val)
				जाओ out;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.ग_लिखो_reg(hw,
					IGP01E1000_PHY_PORT_CONFIG, data);
			अगर (ret_val)
				जाओ out;
		पूर्ण अन्यथा अगर (phy->smart_speed == e1000_smart_speed_off) अणु
			ret_val = phy->ops.पढ़ो_reg(hw,
					IGP01E1000_PHY_PORT_CONFIG, &data);
			अगर (ret_val)
				जाओ out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.ग_लिखो_reg(hw,
					IGP01E1000_PHY_PORT_CONFIG, data);
			अगर (ret_val)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_set_d0_lplu_state_82580 - Set Low Power Linkup D0 state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU D0 state according to the active flag.  When
 *  activating LPLU this function also disables smart speed
 *  and vice versa.  LPLU will not be activated unless the
 *  device स्वतःnegotiation advertisement meets standards of
 *  either 10 or 10/100 or 10/100/1000 at all duplexes.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  PHY setup routines.
 **/
अटल s32 igb_set_d0_lplu_state_82580(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u16 data;

	data = rd32(E1000_82580_PHY_POWER_MGMT);

	अगर (active) अणु
		data |= E1000_82580_PM_D0_LPLU;

		/* When LPLU is enabled, we should disable SmartSpeed */
		data &= ~E1000_82580_PM_SPD;
	पूर्ण अन्यथा अणु
		data &= ~E1000_82580_PM_D0_LPLU;

		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (phy->smart_speed == e1000_smart_speed_on)
			data |= E1000_82580_PM_SPD;
		अन्यथा अगर (phy->smart_speed == e1000_smart_speed_off)
			data &= ~E1000_82580_PM_SPD; पूर्ण

	wr32(E1000_82580_PHY_POWER_MGMT, data);
	वापस 0;
पूर्ण

/**
 *  igb_set_d3_lplu_state_82580 - Sets low घातer link up state क्रम D3
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: boolean used to enable/disable lplu
 *
 *  Success वापसs 0, Failure वापसs 1
 *
 *  The low घातer link up (lplu) state is set to the घातer management level D3
 *  and SmartSpeed is disabled when active is true, अन्यथा clear lplu क्रम D3
 *  and enable Smartspeed.  LPLU and Smartspeed are mutually exclusive.  LPLU
 *  is used during Dx states where the घातer conservation is most important.
 *  During driver activity, SmartSpeed should be enabled so perक्रमmance is
 *  मुख्यtained.
 **/
अटल s32 igb_set_d3_lplu_state_82580(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u16 data;

	data = rd32(E1000_82580_PHY_POWER_MGMT);

	अगर (!active) अणु
		data &= ~E1000_82580_PM_D3_LPLU;
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (phy->smart_speed == e1000_smart_speed_on)
			data |= E1000_82580_PM_SPD;
		अन्यथा अगर (phy->smart_speed == e1000_smart_speed_off)
			data &= ~E1000_82580_PM_SPD;
	पूर्ण अन्यथा अगर ((phy->स्वतःneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_NOT_GIG) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_10_SPEED)) अणु
		data |= E1000_82580_PM_D3_LPLU;
		/* When LPLU is enabled, we should disable SmartSpeed */
		data &= ~E1000_82580_PM_SPD;
	पूर्ण

	wr32(E1000_82580_PHY_POWER_MGMT, data);
	वापस 0;
पूर्ण

/**
 *  igb_acquire_nvm_82575 - Request क्रम access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the necessary semaphores क्रम exclusive access to the EEPROM.
 *  Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 *  Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 *  EEPROM access and वापस -E1000_ERR_NVM (-1).
 **/
अटल s32 igb_acquire_nvm_82575(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	ret_val = hw->mac.ops.acquire_swfw_sync(hw, E1000_SWFW_EEP_SM);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_acquire_nvm(hw);

	अगर (ret_val)
		hw->mac.ops.release_swfw_sync(hw, E1000_SWFW_EEP_SM);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_release_nvm_82575 - Release exclusive access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Stop any current commands to the EEPROM and clear the EEPROM request bit,
 *  then release the semaphores acquired.
 **/
अटल व्योम igb_release_nvm_82575(काष्ठा e1000_hw *hw)
अणु
	igb_release_nvm(hw);
	hw->mac.ops.release_swfw_sync(hw, E1000_SWFW_EEP_SM);
पूर्ण

/**
 *  igb_acquire_swfw_sync_82575 - Acquire SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Acquire the SW/FW semaphore to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're acquiring the lock क्रम.
 **/
अटल s32 igb_acquire_swfw_sync_82575(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 ret_val = 0;
	s32 i = 0, समयout = 200;

	जबतक (i < समयout) अणु
		अगर (igb_get_hw_semaphore(hw)) अणु
			ret_val = -E1000_ERR_SWFW_SYNC;
			जाओ out;
		पूर्ण

		swfw_sync = rd32(E1000_SW_FW_SYNC);
		अगर (!(swfw_sync & (fwmask | swmask)))
			अवरोध;

		/* Firmware currently using resource (fwmask)
		 * or other software thपढ़ो using resource (swmask)
		 */
		igb_put_hw_semaphore(hw);
		mdelay(5);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		hw_dbg("Driver can't access resource, SW_FW_SYNC timeout.\n");
		ret_val = -E1000_ERR_SWFW_SYNC;
		जाओ out;
	पूर्ण

	swfw_sync |= swmask;
	wr32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphore(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_release_swfw_sync_82575 - Release SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Release the SW/FW semaphore used to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're releasing the lock क्रम.
 **/
अटल व्योम igb_release_swfw_sync_82575(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;

	जबतक (igb_get_hw_semaphore(hw) != 0)
		; /* Empty */

	swfw_sync = rd32(E1000_SW_FW_SYNC);
	swfw_sync &= ~mask;
	wr32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphore(hw);
पूर्ण

/**
 *  igb_get_cfg_करोne_82575 - Read config करोne bit
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the management control रेजिस्टर क्रम the config करोne bit क्रम
 *  completion status.  NOTE: silicon which is EEPROM-less will fail trying
 *  to पढ़ो the config करोne bit, so an error is *ONLY* logged and वापसs
 *  0.  If we were to वापस with error, EEPROM-less silicon
 *  would not be able to be reset or change link.
 **/
अटल s32 igb_get_cfg_करोne_82575(काष्ठा e1000_hw *hw)
अणु
	s32 समयout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_PORT_0;

	अगर (hw->bus.func == 1)
		mask = E1000_NVM_CFG_DONE_PORT_1;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_2)
		mask = E1000_NVM_CFG_DONE_PORT_2;
	अन्यथा अगर (hw->bus.func == E1000_FUNC_3)
		mask = E1000_NVM_CFG_DONE_PORT_3;

	जबतक (समयout) अणु
		अगर (rd32(E1000_EEMNGCTL) & mask)
			अवरोध;
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण
	अगर (!समयout)
		hw_dbg("MNG configuration cycle has not completed.\n");

	/* If EEPROM is not marked present, init the PHY manually */
	अगर (((rd32(E1000_EECD) & E1000_EECD_PRES) == 0) &&
	    (hw->phy.type == e1000_phy_igp_3))
		igb_phy_init_script_igp3(hw);

	वापस 0;
पूर्ण

/**
 *  igb_get_link_up_info_82575 - Get link speed/duplex info
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: stores the current speed
 *  @duplex: stores the current duplex
 *
 *  This is a wrapper function, अगर using the serial gigabit media independent
 *  पूर्णांकerface, use PCS to retrieve the link speed and duplex inक्रमmation.
 *  Otherwise, use the generic function to get the link speed and duplex info.
 **/
अटल s32 igb_get_link_up_info_82575(काष्ठा e1000_hw *hw, u16 *speed,
					u16 *duplex)
अणु
	s32 ret_val;

	अगर (hw->phy.media_type != e1000_media_type_copper)
		ret_val = igb_get_pcs_speed_and_duplex_82575(hw, speed,
							       duplex);
	अन्यथा
		ret_val = igb_get_speed_and_duplex_copper(hw, speed,
								    duplex);

	वापस ret_val;
पूर्ण

/**
 *  igb_check_क्रम_link_82575 - Check क्रम link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  If sgmii is enabled, then use the pcs रेजिस्टर to determine link, otherwise
 *  use the generic पूर्णांकerface क्रम determining link.
 **/
अटल s32 igb_check_क्रम_link_82575(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 speed, duplex;

	अगर (hw->phy.media_type != e1000_media_type_copper) अणु
		ret_val = igb_get_pcs_speed_and_duplex_82575(hw, &speed,
							     &duplex);
		/* Use this flag to determine अगर link needs to be checked or
		 * not.  If  we have link clear the flag so that we करो not
		 * जारी to check क्रम link.
		 */
		hw->mac.get_link_status = !hw->mac.serdes_has_link;

		/* Configure Flow Control now that Auto-Neg has completed.
		 * First, we need to restore the desired flow control
		 * settings because we may have had to re-स्वतःneg with a
		 * dअगरferent link partner.
		 */
		ret_val = igb_config_fc_after_link_up(hw);
		अगर (ret_val)
			hw_dbg("Error configuring flow control\n");
	पूर्ण अन्यथा अणु
		ret_val = igb_check_क्रम_copper_link(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_घातer_up_serdes_link_82575 - Power up the serdes link after shutकरोwn
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
व्योम igb_घातer_up_serdes_link_82575(काष्ठा e1000_hw *hw)
अणु
	u32 reg;


	अगर ((hw->phy.media_type != e1000_media_type_पूर्णांकernal_serdes) &&
	    !igb_sgmii_active_82575(hw))
		वापस;

	/* Enable PCS to turn on link */
	reg = rd32(E1000_PCS_CFG0);
	reg |= E1000_PCS_CFG_PCS_EN;
	wr32(E1000_PCS_CFG0, reg);

	/* Power up the laser */
	reg = rd32(E1000_CTRL_EXT);
	reg &= ~E1000_CTRL_EXT_SDP3_DATA;
	wr32(E1000_CTRL_EXT, reg);

	/* flush the ग_लिखो to verअगरy completion */
	wrfl();
	usleep_range(1000, 2000);
पूर्ण

/**
 *  igb_get_pcs_speed_and_duplex_82575 - Retrieve current speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: stores the current speed
 *  @duplex: stores the current duplex
 *
 *  Using the physical coding sub-layer (PCS), retrieve the current speed and
 *  duplex, then store the values in the poपूर्णांकers provided.
 **/
अटल s32 igb_get_pcs_speed_and_duplex_82575(काष्ठा e1000_hw *hw, u16 *speed,
						u16 *duplex)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 pcs, status;

	/* Set up शेषs क्रम the वापस values of this function */
	mac->serdes_has_link = false;
	*speed = 0;
	*duplex = 0;

	/* Read the PCS Status रेजिस्टर क्रम link state. For non-copper mode,
	 * the status रेजिस्टर is not accurate. The PCS status रेजिस्टर is
	 * used instead.
	 */
	pcs = rd32(E1000_PCS_LSTAT);

	/* The link up bit determines when link is up on स्वतःneg. The sync ok
	 * माला_लो set once both sides sync up and agree upon link. Stable link
	 * can be determined by checking क्रम both link up and link sync ok
	 */
	अगर ((pcs & E1000_PCS_LSTS_LINK_OK) && (pcs & E1000_PCS_LSTS_SYNK_OK)) अणु
		mac->serdes_has_link = true;

		/* Detect and store PCS speed */
		अगर (pcs & E1000_PCS_LSTS_SPEED_1000)
			*speed = SPEED_1000;
		अन्यथा अगर (pcs & E1000_PCS_LSTS_SPEED_100)
			*speed = SPEED_100;
		अन्यथा
			*speed = SPEED_10;

		/* Detect and store PCS duplex */
		अगर (pcs & E1000_PCS_LSTS_DUPLEX_FULL)
			*duplex = FULL_DUPLEX;
		अन्यथा
			*duplex = HALF_DUPLEX;

	/* Check अगर it is an I354 2.5Gb backplane connection. */
		अगर (mac->type == e1000_i354) अणु
			status = rd32(E1000_STATUS);
			अगर ((status & E1000_STATUS_2P5_SKU) &&
			    !(status & E1000_STATUS_2P5_SKU_OVER)) अणु
				*speed = SPEED_2500;
				*duplex = FULL_DUPLEX;
				hw_dbg("2500 Mbs, ");
				hw_dbg("Full Duplex\n");
			पूर्ण
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_shutकरोwn_serdes_link_82575 - Remove link during घातer करोwn
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  In the हाल of fiber serdes, shut करोwn optics and PCS on driver unload
 *  when management pass thru is not enabled.
 **/
व्योम igb_shutकरोwn_serdes_link_82575(काष्ठा e1000_hw *hw)
अणु
	u32 reg;

	अगर (hw->phy.media_type != e1000_media_type_पूर्णांकernal_serdes &&
	    igb_sgmii_active_82575(hw))
		वापस;

	अगर (!igb_enable_mng_pass_thru(hw)) अणु
		/* Disable PCS to turn off link */
		reg = rd32(E1000_PCS_CFG0);
		reg &= ~E1000_PCS_CFG_PCS_EN;
		wr32(E1000_PCS_CFG0, reg);

		/* shutकरोwn the laser */
		reg = rd32(E1000_CTRL_EXT);
		reg |= E1000_CTRL_EXT_SDP3_DATA;
		wr32(E1000_CTRL_EXT, reg);

		/* flush the ग_लिखो to verअगरy completion */
		wrfl();
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

/**
 *  igb_reset_hw_82575 - Reset hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This resets the hardware पूर्णांकo a known state.  This is a
 *  function poपूर्णांकer entry poपूर्णांक called by the api module.
 **/
अटल s32 igb_reset_hw_82575(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = igb_disable_pcie_master(hw);
	अगर (ret_val)
		hw_dbg("PCI-E Master disable polling has failed.\n");

	/* set the completion समयout क्रम पूर्णांकerface */
	ret_val = igb_set_pcie_completion_समयout(hw);
	अगर (ret_val)
		hw_dbg("PCI-E Set completion timeout has failed.\n");

	hw_dbg("Masking off all interrupts\n");
	wr32(E1000_IMC, 0xffffffff);

	wr32(E1000_RCTL, 0);
	wr32(E1000_TCTL, E1000_TCTL_PSP);
	wrfl();

	usleep_range(10000, 20000);

	ctrl = rd32(E1000_CTRL);

	hw_dbg("Issuing a global reset to MAC\n");
	wr32(E1000_CTRL, ctrl | E1000_CTRL_RST);

	ret_val = igb_get_स्वतः_rd_करोne(hw);
	अगर (ret_val) अणु
		/* When स्वतः config पढ़ो करोes not complete, करो not
		 * वापस with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	पूर्ण

	/* If EEPROM is not present, run manual init scripts */
	अगर ((rd32(E1000_EECD) & E1000_EECD_PRES) == 0)
		igb_reset_init_script_82575(hw);

	/* Clear any pending पूर्णांकerrupt events. */
	wr32(E1000_IMC, 0xffffffff);
	rd32(E1000_ICR);

	/* Install any alternate MAC address पूर्णांकo RAR0 */
	ret_val = igb_check_alt_mac_addr(hw);

	वापस ret_val;
पूर्ण

/**
 *  igb_init_hw_82575 - Initialize hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This inits the hardware पढ़ोying it क्रम operation.
 **/
अटल s32 igb_init_hw_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	u16 i, rar_count = mac->rar_entry_count;

	अगर ((hw->mac.type >= e1000_i210) &&
	    !(igb_get_flash_presence_i210(hw))) अणु
		ret_val = igb_pll_workaround_i210(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Initialize identअगरication LED */
	ret_val = igb_id_led_init(hw);
	अगर (ret_val) अणु
		hw_dbg("Error initializing identification LED\n");
		/* This is not fatal and we should not stop init due to this */
	पूर्ण

	/* Disabling VLAN filtering */
	hw_dbg("Initializing the IEEE VLAN\n");
	igb_clear_vfta(hw);

	/* Setup the receive address */
	igb_init_rx_addrs(hw, rar_count);

	/* Zero out the Multicast HASH table */
	hw_dbg("Zeroing the MTA\n");
	क्रम (i = 0; i < mac->mta_reg_count; i++)
		array_wr32(E1000_MTA, i, 0);

	/* Zero out the Unicast HASH table */
	hw_dbg("Zeroing the UTA\n");
	क्रम (i = 0; i < mac->uta_reg_count; i++)
		array_wr32(E1000_UTA, i, 0);

	/* Setup link and flow control */
	ret_val = igb_setup_link(hw);

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	igb_clear_hw_cntrs_82575(hw);
	वापस ret_val;
पूर्ण

/**
 *  igb_setup_copper_link_82575 - Configure copper link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures the link क्रम स्वतः-neg or क्रमced speed and duplex.  Then we check
 *  क्रम link, once link is established calls to configure collision distance
 *  and flow control are called.
 **/
अटल s32 igb_setup_copper_link_82575(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32  ret_val;
	u32 phpm_reg;

	ctrl = rd32(E1000_CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	wr32(E1000_CTRL, ctrl);

	/* Clear Go Link Disconnect bit on supported devices */
	चयन (hw->mac.type) अणु
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i210:
	हाल e1000_i211:
		phpm_reg = rd32(E1000_82580_PHY_POWER_MGMT);
		phpm_reg &= ~E1000_82580_PM_GO_LINKD;
		wr32(E1000_82580_PHY_POWER_MGMT, phpm_reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret_val = igb_setup_serdes_link_82575(hw);
	अगर (ret_val)
		जाओ out;

	अगर (igb_sgmii_active_82575(hw) && !hw->phy.reset_disable) अणु
		/* allow समय क्रम SFP cage समय to घातer up phy */
		msleep(300);

		ret_val = hw->phy.ops.reset(hw);
		अगर (ret_val) अणु
			hw_dbg("Error resetting the PHY.\n");
			जाओ out;
		पूर्ण
	पूर्ण
	चयन (hw->phy.type) अणु
	हाल e1000_phy_i210:
	हाल e1000_phy_m88:
		चयन (hw->phy.id) अणु
		हाल I347AT4_E_PHY_ID:
		हाल M88E1112_E_PHY_ID:
		हाल M88E1543_E_PHY_ID:
		हाल M88E1512_E_PHY_ID:
		हाल I210_I_PHY_ID:
			ret_val = igb_copper_link_setup_m88_gen2(hw);
			अवरोध;
		शेष:
			ret_val = igb_copper_link_setup_m88(hw);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल e1000_phy_igp_3:
		ret_val = igb_copper_link_setup_igp(hw);
		अवरोध;
	हाल e1000_phy_82580:
		ret_val = igb_copper_link_setup_82580(hw);
		अवरोध;
	हाल e1000_phy_bcm54616:
		ret_val = 0;
		अवरोध;
	शेष:
		ret_val = -E1000_ERR_PHY;
		अवरोध;
	पूर्ण

	अगर (ret_val)
		जाओ out;

	ret_val = igb_setup_copper_link(hw);
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_setup_serdes_link_82575 - Setup link क्रम serdes
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configure the physical coding sub-layer (PCS) link.  The PCS link is
 *  used on copper connections where the serialized gigabit media independent
 *  पूर्णांकerface (sgmii), or serdes fiber is being used.  Configures the link
 *  क्रम स्वतः-negotiation or क्रमces speed/duplex.
 **/
अटल s32 igb_setup_serdes_link_82575(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl_ext, ctrl_reg, reg, anadv_reg;
	bool pcs_स्वतःneg;
	s32 ret_val = 0;
	u16 data;

	अगर ((hw->phy.media_type != e1000_media_type_पूर्णांकernal_serdes) &&
	    !igb_sgmii_active_82575(hw))
		वापस ret_val;


	/* On the 82575, SerDes loopback mode persists until it is
	 * explicitly turned off or a घातer cycle is perक्रमmed.  A पढ़ो to
	 * the रेजिस्टर करोes not indicate its status.  Thereक्रमe, we ensure
	 * loopback mode is disabled during initialization.
	 */
	wr32(E1000_SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);

	/* घातer on the sfp cage अगर present and turn on I2C */
	ctrl_ext = rd32(E1000_CTRL_EXT);
	ctrl_ext &= ~E1000_CTRL_EXT_SDP3_DATA;
	ctrl_ext |= E1000_CTRL_I2C_ENA;
	wr32(E1000_CTRL_EXT, ctrl_ext);

	ctrl_reg = rd32(E1000_CTRL);
	ctrl_reg |= E1000_CTRL_SLU;

	अगर (hw->mac.type == e1000_82575 || hw->mac.type == e1000_82576) अणु
		/* set both sw defined pins */
		ctrl_reg |= E1000_CTRL_SWDPIN0 | E1000_CTRL_SWDPIN1;

		/* Set चयन control to serdes energy detect */
		reg = rd32(E1000_CONNSW);
		reg |= E1000_CONNSW_ENRGSRC;
		wr32(E1000_CONNSW, reg);
	पूर्ण

	reg = rd32(E1000_PCS_LCTL);

	/* शेष pcs_स्वतःneg to the same setting as mac स्वतःneg */
	pcs_स्वतःneg = hw->mac.स्वतःneg;

	चयन (ctrl_ext & E1000_CTRL_EXT_LINK_MODE_MASK) अणु
	हाल E1000_CTRL_EXT_LINK_MODE_SGMII:
		/* sgmii mode lets the phy handle क्रमcing speed/duplex */
		pcs_स्वतःneg = true;
		/* स्वतःneg समय out should be disabled क्रम SGMII mode */
		reg &= ~(E1000_PCS_LCTL_AN_TIMEOUT);
		अवरोध;
	हाल E1000_CTRL_EXT_LINK_MODE_1000BASE_KX:
		/* disable PCS स्वतःneg and support parallel detect only */
		pcs_स्वतःneg = false;
		fallthrough;
	शेष:
		अगर (hw->mac.type == e1000_82575 ||
		    hw->mac.type == e1000_82576) अणु
			ret_val = hw->nvm.ops.पढ़ो(hw, NVM_COMPAT, 1, &data);
			अगर (ret_val) अणु
				hw_dbg(KERN_DEBUG "NVM Read Error\n\n");
				वापस ret_val;
			पूर्ण

			अगर (data & E1000_EEPROM_PCS_AUTONEG_DISABLE_BIT)
				pcs_स्वतःneg = false;
		पूर्ण

		/* non-SGMII modes only supports a speed of 1000/Full क्रम the
		 * link so it is best to just क्रमce the MAC and let the pcs
		 * link either स्वतःneg or be क्रमced to 1000/Full
		 */
		ctrl_reg |= E1000_CTRL_SPD_1000 | E1000_CTRL_FRCSPD |
				E1000_CTRL_FD | E1000_CTRL_FRCDPX;

		/* set speed of 1000/Full अगर speed/duplex is क्रमced */
		reg |= E1000_PCS_LCTL_FSV_1000 | E1000_PCS_LCTL_FDV_FULL;
		अवरोध;
	पूर्ण

	wr32(E1000_CTRL, ctrl_reg);

	/* New SerDes mode allows क्रम क्रमcing speed or स्वतःnegotiating speed
	 * at 1gb. Autoneg should be शेष set by most drivers. This is the
	 * mode that will be compatible with older link partners and चयनes.
	 * However, both are supported by the hardware and some drivers/tools.
	 */
	reg &= ~(E1000_PCS_LCTL_AN_ENABLE | E1000_PCS_LCTL_FLV_LINK_UP |
		E1000_PCS_LCTL_FSD | E1000_PCS_LCTL_FORCE_LINK);

	अगर (pcs_स्वतःneg) अणु
		/* Set PCS रेजिस्टर क्रम स्वतःneg */
		reg |= E1000_PCS_LCTL_AN_ENABLE | /* Enable Autoneg */
		       E1000_PCS_LCTL_AN_RESTART; /* Restart स्वतःneg */

		/* Disable क्रमce flow control क्रम स्वतःneg */
		reg &= ~E1000_PCS_LCTL_FORCE_FCTRL;

		/* Configure flow control advertisement क्रम स्वतःneg */
		anadv_reg = rd32(E1000_PCS_ANADV);
		anadv_reg &= ~(E1000_TXCW_ASM_सूची | E1000_TXCW_PAUSE);
		चयन (hw->fc.requested_mode) अणु
		हाल e1000_fc_full:
		हाल e1000_fc_rx_छोड़ो:
			anadv_reg |= E1000_TXCW_ASM_सूची;
			anadv_reg |= E1000_TXCW_PAUSE;
			अवरोध;
		हाल e1000_fc_tx_छोड़ो:
			anadv_reg |= E1000_TXCW_ASM_सूची;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		wr32(E1000_PCS_ANADV, anadv_reg);

		hw_dbg("Configuring Autoneg:PCS_LCTL=0x%08X\n", reg);
	पूर्ण अन्यथा अणु
		/* Set PCS रेजिस्टर क्रम क्रमced link */
		reg |= E1000_PCS_LCTL_FSD;        /* Force Speed */

		/* Force flow control क्रम क्रमced link */
		reg |= E1000_PCS_LCTL_FORCE_FCTRL;

		hw_dbg("Configuring Forced Link:PCS_LCTL=0x%08X\n", reg);
	पूर्ण

	wr32(E1000_PCS_LCTL, reg);

	अगर (!pcs_स्वतःneg && !igb_sgmii_active_82575(hw))
		igb_क्रमce_mac_fc(hw);

	वापस ret_val;
पूर्ण

/**
 *  igb_sgmii_active_82575 - Return sgmii state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  82575 silicon has a serialized gigabit media independent पूर्णांकerface (sgmii)
 *  which can be enabled क्रम use in the embedded applications.  Simply
 *  वापस the current state of the sgmii पूर्णांकerface.
 **/
अटल bool igb_sgmii_active_82575(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	वापस dev_spec->sgmii_active;
पूर्ण

/**
 *  igb_reset_init_script_82575 - Inits HW शेषs after reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Inits recommended HW शेषs after a reset when there is no EEPROM
 *  detected. This is only क्रम the 82575.
 **/
अटल s32 igb_reset_init_script_82575(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->mac.type == e1000_82575) अणु
		hw_dbg("Running reset init script for 82575\n");
		/* SerDes configuration via SERDESCTRL */
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCTL, 0x00, 0x0C);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCTL, 0x01, 0x78);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCTL, 0x1B, 0x23);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCTL, 0x23, 0x15);

		/* CCM configuration via CCMCTL रेजिस्टर */
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_CCMCTL, 0x14, 0x00);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_CCMCTL, 0x10, 0x00);

		/* PCIe lanes configuration */
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x00, 0xEC);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x61, 0xDF);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x34, 0x05);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_GIOCTL, 0x2F, 0x81);

		/* PCIe PLL Configuration */
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCCTL, 0x02, 0x47);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCCTL, 0x14, 0x00);
		igb_ग_लिखो_8bit_ctrl_reg(hw, E1000_SCCTL, 0x10, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_पढ़ो_mac_addr_82575 - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 igb_पढ़ो_mac_addr_82575(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	/* If there's an alternate MAC address place it in RAR0
	 * so that it will override the Si installed शेष perm
	 * address.
	 */
	ret_val = igb_check_alt_mac_addr(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_पढ़ो_mac_addr(hw);

out:
	वापस ret_val;
पूर्ण

/**
 * igb_घातer_करोwn_phy_copper_82575 - Remove link during PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, हटाओ the link.
 **/
व्योम igb_घातer_करोwn_phy_copper_82575(काष्ठा e1000_hw *hw)
अणु
	/* If the management पूर्णांकerface is not enabled, then घातer करोwn */
	अगर (!(igb_enable_mng_pass_thru(hw) || igb_check_reset_block(hw)))
		igb_घातer_करोwn_phy_copper(hw);
पूर्ण

/**
 *  igb_clear_hw_cntrs_82575 - Clear device specअगरic hardware counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears the hardware counters by पढ़ोing the counter रेजिस्टरs.
 **/
अटल व्योम igb_clear_hw_cntrs_82575(काष्ठा e1000_hw *hw)
अणु
	igb_clear_hw_cntrs_base(hw);

	rd32(E1000_PRC64);
	rd32(E1000_PRC127);
	rd32(E1000_PRC255);
	rd32(E1000_PRC511);
	rd32(E1000_PRC1023);
	rd32(E1000_PRC1522);
	rd32(E1000_PTC64);
	rd32(E1000_PTC127);
	rd32(E1000_PTC255);
	rd32(E1000_PTC511);
	rd32(E1000_PTC1023);
	rd32(E1000_PTC1522);

	rd32(E1000_ALGNERRC);
	rd32(E1000_RXERRC);
	rd32(E1000_TNCRS);
	rd32(E1000_CEXTERR);
	rd32(E1000_TSCTC);
	rd32(E1000_TSCTFC);

	rd32(E1000_MGTPRC);
	rd32(E1000_MGTPDC);
	rd32(E1000_MGTPTC);

	rd32(E1000_IAC);
	rd32(E1000_ICRXOC);

	rd32(E1000_ICRXPTC);
	rd32(E1000_ICRXATC);
	rd32(E1000_ICTXPTC);
	rd32(E1000_ICTXATC);
	rd32(E1000_ICTXQEC);
	rd32(E1000_ICTXQMTC);
	rd32(E1000_ICRXDMTC);

	rd32(E1000_CBTMPC);
	rd32(E1000_HTDPMC);
	rd32(E1000_CBRMPC);
	rd32(E1000_RPTHC);
	rd32(E1000_HGPTC);
	rd32(E1000_HTCBDPC);
	rd32(E1000_HGORCL);
	rd32(E1000_HGORCH);
	rd32(E1000_HGOTCL);
	rd32(E1000_HGOTCH);
	rd32(E1000_LENERRS);

	/* This रेजिस्टर should not be पढ़ो in copper configurations */
	अगर (hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes ||
	    igb_sgmii_active_82575(hw))
		rd32(E1000_SCVPC);
पूर्ण

/**
 *  igb_rx_fअगरo_flush_82575 - Clean rx fअगरo after RX enable
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  After rx enable अगर manageability is enabled then there is likely some
 *  bad data at the start of the fअगरo and possibly in the DMA fअगरo. This
 *  function clears the fअगरos and flushes any packets that came in as rx was
 *  being enabled.
 **/
व्योम igb_rx_fअगरo_flush_82575(काष्ठा e1000_hw *hw)
अणु
	u32 rctl, rlpml, rxdctl[4], rfctl, temp_rctl, rx_enabled;
	पूर्णांक i, ms_रुको;

	/* disable IPv6 options as per hardware errata */
	rfctl = rd32(E1000_RFCTL);
	rfctl |= E1000_RFCTL_IPV6_EX_DIS;
	wr32(E1000_RFCTL, rfctl);

	अगर (hw->mac.type != e1000_82575 ||
	    !(rd32(E1000_MANC) & E1000_MANC_RCV_TCO_EN))
		वापस;

	/* Disable all RX queues */
	क्रम (i = 0; i < 4; i++) अणु
		rxdctl[i] = rd32(E1000_RXDCTL(i));
		wr32(E1000_RXDCTL(i),
		     rxdctl[i] & ~E1000_RXDCTL_QUEUE_ENABLE);
	पूर्ण
	/* Poll all queues to verअगरy they have shut करोwn */
	क्रम (ms_रुको = 0; ms_रुको < 10; ms_रुको++) अणु
		usleep_range(1000, 2000);
		rx_enabled = 0;
		क्रम (i = 0; i < 4; i++)
			rx_enabled |= rd32(E1000_RXDCTL(i));
		अगर (!(rx_enabled & E1000_RXDCTL_QUEUE_ENABLE))
			अवरोध;
	पूर्ण

	अगर (ms_रुको == 10)
		hw_dbg("Queue disable timed out after 10ms\n");

	/* Clear RLPML, RCTL.SBP, RFCTL.LEF, and set RCTL.LPE so that all
	 * incoming packets are rejected.  Set enable and रुको 2ms so that
	 * any packet that was coming in as RCTL.EN was set is flushed
	 */
	wr32(E1000_RFCTL, rfctl & ~E1000_RFCTL_LEF);

	rlpml = rd32(E1000_RLPML);
	wr32(E1000_RLPML, 0);

	rctl = rd32(E1000_RCTL);
	temp_rctl = rctl & ~(E1000_RCTL_EN | E1000_RCTL_SBP);
	temp_rctl |= E1000_RCTL_LPE;

	wr32(E1000_RCTL, temp_rctl);
	wr32(E1000_RCTL, temp_rctl | E1000_RCTL_EN);
	wrfl();
	usleep_range(2000, 3000);

	/* Enable RX queues that were previously enabled and restore our
	 * previous state
	 */
	क्रम (i = 0; i < 4; i++)
		wr32(E1000_RXDCTL(i), rxdctl[i]);
	wr32(E1000_RCTL, rctl);
	wrfl();

	wr32(E1000_RLPML, rlpml);
	wr32(E1000_RFCTL, rfctl);

	/* Flush receive errors generated by workaround */
	rd32(E1000_ROC);
	rd32(E1000_RNBC);
	rd32(E1000_MPC);
पूर्ण

/**
 *  igb_set_pcie_completion_समयout - set pci-e completion समयout
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The शेषs क्रम 82575 and 82576 should be in the range of 50us to 50ms,
 *  however the hardware शेष क्रम these parts is 500us to 1ms which is less
 *  than the 10ms recommended by the pci-e spec.  To address this we need to
 *  increase the value to either 10ms to 200ms क्रम capability version 1 config,
 *  or 16ms to 55ms क्रम version 2.
 **/
अटल s32 igb_set_pcie_completion_समयout(काष्ठा e1000_hw *hw)
अणु
	u32 gcr = rd32(E1000_GCR);
	s32 ret_val = 0;
	u16 pcie_devctl2;

	/* only take action अगर समयout value is शेषed to 0 */
	अगर (gcr & E1000_GCR_CMPL_TMOUT_MASK)
		जाओ out;

	/* अगर capabilities version is type 1 we can ग_लिखो the
	 * समयout of 10ms to 200ms through the GCR रेजिस्टर
	 */
	अगर (!(gcr & E1000_GCR_CAP_VER2)) अणु
		gcr |= E1000_GCR_CMPL_TMOUT_10ms;
		जाओ out;
	पूर्ण

	/* क्रम version 2 capabilities we need to ग_लिखो the config space
	 * directly in order to set the completion समयout value क्रम
	 * 16ms to 55ms
	 */
	ret_val = igb_पढ़ो_pcie_cap_reg(hw, PCIE_DEVICE_CONTROL2,
					&pcie_devctl2);
	अगर (ret_val)
		जाओ out;

	pcie_devctl2 |= PCIE_DEVICE_CONTROL2_16ms;

	ret_val = igb_ग_लिखो_pcie_cap_reg(hw, PCIE_DEVICE_CONTROL2,
					 &pcie_devctl2);
out:
	/* disable completion समयout resend */
	gcr &= ~E1000_GCR_CMPL_TMOUT_RESEND;

	wr32(E1000_GCR, gcr);
	वापस ret_val;
पूर्ण

/**
 *  igb_vmdq_set_anti_spoofing_pf - enable or disable anti-spoofing
 *  @hw: poपूर्णांकer to the hardware काष्ठा
 *  @enable: state to enter, either enabled or disabled
 *  @pf: Physical Function pool - करो not set anti-spoofing क्रम the PF
 *
 *  enables/disables L2 चयन anti-spoofing functionality.
 **/
व्योम igb_vmdq_set_anti_spoofing_pf(काष्ठा e1000_hw *hw, bool enable, पूर्णांक pf)
अणु
	u32 reg_val, reg_offset;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
		reg_offset = E1000_DTXSWC;
		अवरोध;
	हाल e1000_i350:
	हाल e1000_i354:
		reg_offset = E1000_TXSWC;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	reg_val = rd32(reg_offset);
	अगर (enable) अणु
		reg_val |= (E1000_DTXSWC_MAC_SPOOF_MASK |
			     E1000_DTXSWC_VLAN_SPOOF_MASK);
		/* The PF can spoof - it has to in order to
		 * support emulation mode NICs
		 */
		reg_val ^= (BIT(pf) | BIT(pf + MAX_NUM_VFS));
	पूर्ण अन्यथा अणु
		reg_val &= ~(E1000_DTXSWC_MAC_SPOOF_MASK |
			     E1000_DTXSWC_VLAN_SPOOF_MASK);
	पूर्ण
	wr32(reg_offset, reg_val);
पूर्ण

/**
 *  igb_vmdq_set_loopback_pf - enable or disable vmdq loopback
 *  @hw: poपूर्णांकer to the hardware काष्ठा
 *  @enable: state to enter, either enabled or disabled
 *
 *  enables/disables L2 चयन loopback functionality.
 **/
व्योम igb_vmdq_set_loopback_pf(काष्ठा e1000_hw *hw, bool enable)
अणु
	u32 dtxswc;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
		dtxswc = rd32(E1000_DTXSWC);
		अगर (enable)
			dtxswc |= E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		अन्यथा
			dtxswc &= ~E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		wr32(E1000_DTXSWC, dtxswc);
		अवरोध;
	हाल e1000_i354:
	हाल e1000_i350:
		dtxswc = rd32(E1000_TXSWC);
		अगर (enable)
			dtxswc |= E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		अन्यथा
			dtxswc &= ~E1000_DTXSWC_VMDQ_LOOPBACK_EN;
		wr32(E1000_TXSWC, dtxswc);
		अवरोध;
	शेष:
		/* Currently no other hardware supports loopback */
		अवरोध;
	पूर्ण

पूर्ण

/**
 *  igb_vmdq_set_replication_pf - enable or disable vmdq replication
 *  @hw: poपूर्णांकer to the hardware काष्ठा
 *  @enable: state to enter, either enabled or disabled
 *
 *  enables/disables replication of packets across multiple pools.
 **/
व्योम igb_vmdq_set_replication_pf(काष्ठा e1000_hw *hw, bool enable)
अणु
	u32 vt_ctl = rd32(E1000_VT_CTL);

	अगर (enable)
		vt_ctl |= E1000_VT_CTL_VM_REPL_EN;
	अन्यथा
		vt_ctl &= ~E1000_VT_CTL_VM_REPL_EN;

	wr32(E1000_VT_CTL, vt_ctl);
पूर्ण

/**
 *  igb_पढ़ो_phy_reg_82580 - Read 82580 MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the MDI control रेजिस्टर in the PHY at offset and stores the
 *  inक्रमmation पढ़ो to data.
 **/
s32 igb_पढ़ो_phy_reg_82580(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	s32 ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_पढ़ो_phy_reg_mdic(hw, offset, data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_phy_reg_82580 - Write 82580 MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो to रेजिस्टर at offset
 *
 *  Writes data to MDI control रेजिस्टर in the PHY at offset.
 **/
s32 igb_ग_लिखो_phy_reg_82580(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	s32 ret_val;


	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_ग_लिखो_phy_reg_mdic(hw, offset, data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_reset_mdicnfg_82580 - Reset MDICNFG destination and com_mdio bits
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This resets the the MDICNFG.Destination and MDICNFG.Com_MDIO bits based on
 *  the values found in the EEPROM.  This addresses an issue in which these
 *  bits are not restored from EEPROM after reset.
 **/
अटल s32 igb_reset_mdicnfg_82580(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u32 mdicnfg;
	u16 nvm_data = 0;

	अगर (hw->mac.type != e1000_82580)
		जाओ out;
	अगर (!igb_sgmii_active_82575(hw))
		जाओ out;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_INIT_CONTROL3_PORT_A +
				   NVM_82580_LAN_FUNC_OFFSET(hw->bus.func), 1,
				   &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	mdicnfg = rd32(E1000_MDICNFG);
	अगर (nvm_data & NVM_WORD24_EXT_MDIO)
		mdicnfg |= E1000_MDICNFG_EXT_MDIO;
	अगर (nvm_data & NVM_WORD24_COM_MDIO)
		mdicnfg |= E1000_MDICNFG_COM_MDIO;
	wr32(E1000_MDICNFG, mdicnfg);
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_reset_hw_82580 - Reset hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This resets function or entire device (all ports, etc.)
 *  to a known state.
 **/
अटल s32 igb_reset_hw_82580(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	/* BH SW mailbox bit in SW_FW_SYNC */
	u16 swmbsw_mask = E1000_SW_SYNCH_MB;
	u32 ctrl;
	bool global_device_reset = hw->dev_spec._82575.global_device_reset;

	hw->dev_spec._82575.global_device_reset = false;

	/* due to hw errata, global device reset करोesn't always
	 * work on 82580
	 */
	अगर (hw->mac.type == e1000_82580)
		global_device_reset = false;

	/* Get current control state. */
	ctrl = rd32(E1000_CTRL);

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = igb_disable_pcie_master(hw);
	अगर (ret_val)
		hw_dbg("PCI-E Master disable polling has failed.\n");

	hw_dbg("Masking off all interrupts\n");
	wr32(E1000_IMC, 0xffffffff);
	wr32(E1000_RCTL, 0);
	wr32(E1000_TCTL, E1000_TCTL_PSP);
	wrfl();

	usleep_range(10000, 11000);

	/* Determine whether or not a global dev reset is requested */
	अगर (global_device_reset &&
		hw->mac.ops.acquire_swfw_sync(hw, swmbsw_mask))
			global_device_reset = false;

	अगर (global_device_reset &&
		!(rd32(E1000_STATUS) & E1000_STAT_DEV_RST_SET))
		ctrl |= E1000_CTRL_DEV_RST;
	अन्यथा
		ctrl |= E1000_CTRL_RST;

	wr32(E1000_CTRL, ctrl);
	wrfl();

	/* Add delay to insure DEV_RST has समय to complete */
	अगर (global_device_reset)
		usleep_range(5000, 6000);

	ret_val = igb_get_स्वतः_rd_करोne(hw);
	अगर (ret_val) अणु
		/* When स्वतः config पढ़ो करोes not complete, करो not
		 * वापस with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	पूर्ण

	/* clear global device reset status bit */
	wr32(E1000_STATUS, E1000_STAT_DEV_RST_SET);

	/* Clear any pending पूर्णांकerrupt events. */
	wr32(E1000_IMC, 0xffffffff);
	rd32(E1000_ICR);

	ret_val = igb_reset_mdicnfg_82580(hw);
	अगर (ret_val)
		hw_dbg("Could not reset MDICNFG based on EEPROM\n");

	/* Install any alternate MAC address पूर्णांकo RAR0 */
	ret_val = igb_check_alt_mac_addr(hw);

	/* Release semaphore */
	अगर (global_device_reset)
		hw->mac.ops.release_swfw_sync(hw, swmbsw_mask);

	वापस ret_val;
पूर्ण

/**
 *  igb_rxpbs_adjust_82580 - adjust RXPBS value to reflect actual RX PBA size
 *  @data: data received by पढ़ोing RXPBS रेजिस्टर
 *
 *  The 82580 uses a table based approach क्रम packet buffer allocation sizes.
 *  This function converts the retrieved value पूर्णांकo the correct table value
 *     0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7
 *  0x0 36  72 144   1   2   4   8  16
 *  0x8 35  70 140 rsv rsv rsv rsv rsv
 */
u16 igb_rxpbs_adjust_82580(u32 data)
अणु
	u16 ret_val = 0;

	अगर (data < ARRAY_SIZE(e1000_82580_rxpbs_table))
		ret_val = e1000_82580_rxpbs_table[data];

	वापस ret_val;
पूर्ण

/**
 *  igb_validate_nvm_checksum_with_offset - Validate EEPROM
 *  checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset in words of the checksum रक्षित region
 *
 *  Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 **/
अटल s32 igb_validate_nvm_checksum_with_offset(काष्ठा e1000_hw *hw,
						 u16 offset)
अणु
	s32 ret_val = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = offset; i < ((NVM_CHECKSUM_REG + offset) + 1); i++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण

	अगर (checksum != (u16) NVM_SUM) अणु
		hw_dbg("NVM Checksum Invalid\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_update_nvm_checksum_with_offset - Update EEPROM
 *  checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset in words of the checksum रक्षित region
 *
 *  Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 *  value to the EEPROM.
 **/
अटल s32 igb_update_nvm_checksum_with_offset(काष्ठा e1000_hw *hw, u16 offset)
अणु
	s32 ret_val;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = offset; i < (NVM_CHECKSUM_REG + offset); i++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error while updating checksum.\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण
	checksum = (u16) NVM_SUM - checksum;
	ret_val = hw->nvm.ops.ग_लिखो(hw, (NVM_CHECKSUM_REG + offset), 1,
				&checksum);
	अगर (ret_val)
		hw_dbg("NVM Write Error while updating checksum.\n");

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_validate_nvm_checksum_82580 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM section checksum by पढ़ोing/adding each word of
 *  the EEPROM and then verअगरies that the sum of the EEPROM is
 *  equal to 0xBABA.
 **/
अटल s32 igb_validate_nvm_checksum_82580(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 eeprom_regions_count = 1;
	u16 j, nvm_data;
	u16 nvm_offset;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_COMPATIBILITY_REG_3, 1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर (nvm_data & NVM_COMPATIBILITY_BIT_MASK) अणु
		/* अगर checksums compatibility bit is set validate checksums
		 * क्रम all 4 ports.
		 */
		eeprom_regions_count = 4;
	पूर्ण

	क्रम (j = 0; j < eeprom_regions_count; j++) अणु
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = igb_validate_nvm_checksum_with_offset(hw,
								nvm_offset);
		अगर (ret_val != 0)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_update_nvm_checksum_82580 - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM section checksums क्रम all 4 ports by पढ़ोing/adding
 *  each word of the EEPROM up to the checksum.  Then calculates the EEPROM
 *  checksum and ग_लिखोs the value to the EEPROM.
 **/
अटल s32 igb_update_nvm_checksum_82580(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 j, nvm_data;
	u16 nvm_offset;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_COMPATIBILITY_REG_3, 1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error while updating checksum compatibility bit.\n");
		जाओ out;
	पूर्ण

	अगर ((nvm_data & NVM_COMPATIBILITY_BIT_MASK) == 0) अणु
		/* set compatibility bit to validate checksums appropriately */
		nvm_data = nvm_data | NVM_COMPATIBILITY_BIT_MASK;
		ret_val = hw->nvm.ops.ग_लिखो(hw, NVM_COMPATIBILITY_REG_3, 1,
					&nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Write Error while updating checksum compatibility bit.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < 4; j++) अणु
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = igb_update_nvm_checksum_with_offset(hw, nvm_offset);
		अगर (ret_val)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_validate_nvm_checksum_i350 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM section checksum by पढ़ोing/adding each word of
 *  the EEPROM and then verअगरies that the sum of the EEPROM is
 *  equal to 0xBABA.
 **/
अटल s32 igb_validate_nvm_checksum_i350(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 j;
	u16 nvm_offset;

	क्रम (j = 0; j < 4; j++) अणु
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = igb_validate_nvm_checksum_with_offset(hw,
								nvm_offset);
		अगर (ret_val != 0)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_update_nvm_checksum_i350 - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM section checksums क्रम all 4 ports by पढ़ोing/adding
 *  each word of the EEPROM up to the checksum.  Then calculates the EEPROM
 *  checksum and ग_लिखोs the value to the EEPROM.
 **/
अटल s32 igb_update_nvm_checksum_i350(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 j;
	u16 nvm_offset;

	क्रम (j = 0; j < 4; j++) अणु
		nvm_offset = NVM_82580_LAN_FUNC_OFFSET(j);
		ret_val = igb_update_nvm_checksum_with_offset(hw, nvm_offset);
		अगर (ret_val != 0)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  __igb_access_emi_reg - Read/ग_लिखो EMI रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @address: EMI address to program
 *  @data: poपूर्णांकer to value to पढ़ो/ग_लिखो from/to the EMI address
 *  @पढ़ो: boolean flag to indicate पढ़ो or ग_लिखो
 **/
अटल s32 __igb_access_emi_reg(काष्ठा e1000_hw *hw, u16 address,
				  u16 *data, bool पढ़ो)
अणु
	s32 ret_val = 0;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_EMIADD, address);
	अगर (ret_val)
		वापस ret_val;

	अगर (पढ़ो)
		ret_val = hw->phy.ops.पढ़ो_reg(hw, E1000_EMIDATA, data);
	अन्यथा
		ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_EMIDATA, *data);

	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_emi_reg - Read Extended Management Interface रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: EMI address to program
 *  @data: value to be पढ़ो from the EMI address
 **/
s32 igb_पढ़ो_emi_reg(काष्ठा e1000_hw *hw, u16 addr, u16 *data)
अणु
	वापस __igb_access_emi_reg(hw, addr, data, true);
पूर्ण

/**
 *  igb_set_eee_i350 - Enable/disable EEE support
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @adv1G: boolean flag enabling 1G EEE advertisement
 *  @adv100M: boolean flag enabling 100M EEE advertisement
 *
 *  Enable/disable EEE based on setting in dev_spec काष्ठाure.
 *
 **/
s32 igb_set_eee_i350(काष्ठा e1000_hw *hw, bool adv1G, bool adv100M)
अणु
	u32 ipcnfg, eeer;

	अगर ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_copper))
		जाओ out;
	ipcnfg = rd32(E1000_IPCNFG);
	eeer = rd32(E1000_EEER);

	/* enable or disable per user setting */
	अगर (!(hw->dev_spec._82575.eee_disable)) अणु
		u32 eee_su = rd32(E1000_EEE_SU);

		अगर (adv100M)
			ipcnfg |= E1000_IPCNFG_EEE_100M_AN;
		अन्यथा
			ipcnfg &= ~E1000_IPCNFG_EEE_100M_AN;

		अगर (adv1G)
			ipcnfg |= E1000_IPCNFG_EEE_1G_AN;
		अन्यथा
			ipcnfg &= ~E1000_IPCNFG_EEE_1G_AN;

		eeer |= (E1000_EEER_TX_LPI_EN | E1000_EEER_RX_LPI_EN |
			E1000_EEER_LPI_FC);

		/* This bit should not be set in normal operation. */
		अगर (eee_su & E1000_EEE_SU_LPI_CLK_STP)
			hw_dbg("LPI Clock Stop Bit should not be set!\n");

	पूर्ण अन्यथा अणु
		ipcnfg &= ~(E1000_IPCNFG_EEE_1G_AN |
			E1000_IPCNFG_EEE_100M_AN);
		eeer &= ~(E1000_EEER_TX_LPI_EN |
			E1000_EEER_RX_LPI_EN |
			E1000_EEER_LPI_FC);
	पूर्ण
	wr32(E1000_IPCNFG, ipcnfg);
	wr32(E1000_EEER, eeer);
	rd32(E1000_IPCNFG);
	rd32(E1000_EEER);
out:

	वापस 0;
पूर्ण

/**
 *  igb_set_eee_i354 - Enable/disable EEE support
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @adv1G: boolean flag enabling 1G EEE advertisement
 *  @adv100M: boolean flag enabling 100M EEE advertisement
 *
 *  Enable/disable EEE legacy mode based on setting in dev_spec काष्ठाure.
 *
 **/
s32 igb_set_eee_i354(काष्ठा e1000_hw *hw, bool adv1G, bool adv100M)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_data;

	अगर ((hw->phy.media_type != e1000_media_type_copper) ||
	    ((phy->id != M88E1543_E_PHY_ID) &&
	     (phy->id != M88E1512_E_PHY_ID)))
		जाओ out;

	अगर (!hw->dev_spec._82575.eee_disable) अणु
		/* Switch to PHY page 18. */
		ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 18);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.पढ़ो_reg(hw, E1000_M88E1543_EEE_CTRL_1,
					    &phy_data);
		अगर (ret_val)
			जाओ out;

		phy_data |= E1000_M88E1543_EEE_CTRL_1_MS;
		ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_EEE_CTRL_1,
					     phy_data);
		अगर (ret_val)
			जाओ out;

		/* Return the PHY to page 0. */
		ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0);
		अगर (ret_val)
			जाओ out;

		/* Turn on EEE advertisement. */
		ret_val = igb_पढ़ो_xmdio_reg(hw, E1000_EEE_ADV_ADDR_I354,
					     E1000_EEE_ADV_DEV_I354,
					     &phy_data);
		अगर (ret_val)
			जाओ out;

		अगर (adv100M)
			phy_data |= E1000_EEE_ADV_100_SUPPORTED;
		अन्यथा
			phy_data &= ~E1000_EEE_ADV_100_SUPPORTED;

		अगर (adv1G)
			phy_data |= E1000_EEE_ADV_1000_SUPPORTED;
		अन्यथा
			phy_data &= ~E1000_EEE_ADV_1000_SUPPORTED;

		ret_val = igb_ग_लिखो_xmdio_reg(hw, E1000_EEE_ADV_ADDR_I354,
						E1000_EEE_ADV_DEV_I354,
						phy_data);
	पूर्ण अन्यथा अणु
		/* Turn off EEE advertisement. */
		ret_val = igb_पढ़ो_xmdio_reg(hw, E1000_EEE_ADV_ADDR_I354,
					     E1000_EEE_ADV_DEV_I354,
					     &phy_data);
		अगर (ret_val)
			जाओ out;

		phy_data &= ~(E1000_EEE_ADV_100_SUPPORTED |
			      E1000_EEE_ADV_1000_SUPPORTED);
		ret_val = igb_ग_लिखो_xmdio_reg(hw, E1000_EEE_ADV_ADDR_I354,
					      E1000_EEE_ADV_DEV_I354,
					      phy_data);
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_eee_status_i354 - Get EEE status
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @status: EEE status
 *
 *  Get EEE status by guessing based on whether Tx or Rx LPI indications have
 *  been received.
 **/
s32 igb_get_eee_status_i354(काष्ठा e1000_hw *hw, bool *status)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_data;

	/* Check अगर EEE is supported on this device. */
	अगर ((hw->phy.media_type != e1000_media_type_copper) ||
	    ((phy->id != M88E1543_E_PHY_ID) &&
	     (phy->id != M88E1512_E_PHY_ID)))
		जाओ out;

	ret_val = igb_पढ़ो_xmdio_reg(hw, E1000_PCS_STATUS_ADDR_I354,
				     E1000_PCS_STATUS_DEV_I354,
				     &phy_data);
	अगर (ret_val)
		जाओ out;

	*status = phy_data & (E1000_PCS_STATUS_TX_LPI_RCVD |
			      E1000_PCS_STATUS_RX_LPI_RCVD) ? true : false;

out:
	वापस ret_val;
पूर्ण

अटल स्थिर u8 e1000_emc_temp_data[4] = अणु
	E1000_EMC_INTERNAL_DATA,
	E1000_EMC_DIODE1_DATA,
	E1000_EMC_DIODE2_DATA,
	E1000_EMC_DIODE3_DATA
पूर्ण;
अटल स्थिर u8 e1000_emc_therm_limit[4] = अणु
	E1000_EMC_INTERNAL_THERM_LIMIT,
	E1000_EMC_DIODE1_THERM_LIMIT,
	E1000_EMC_DIODE2_THERM_LIMIT,
	E1000_EMC_DIODE3_THERM_LIMIT
पूर्ण;

#अगर_घोषित CONFIG_IGB_HWMON
/**
 *  igb_get_thermal_sensor_data_generic - Gathers thermal sensor data
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Updates the temperatures in mac.thermal_sensor_data
 **/
अटल s32 igb_get_thermal_sensor_data_generic(काष्ठा e1000_hw *hw)
अणु
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  num_sensors;
	u8  sensor_index;
	u8  sensor_location;
	u8  i;
	काष्ठा e1000_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	अगर ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		वापस E1000_NOT_IMPLEMENTED;

	data->sensor[0].temp = (rd32(E1000_THMJT) & 0xFF);

	/* Return the पूर्णांकernal sensor only अगर ETS is unsupported */
	hw->nvm.ops.पढ़ो(hw, NVM_ETS_CFG, 1, &ets_offset);
	अगर ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		वापस 0;

	hw->nvm.ops.पढ़ो(hw, ets_offset, 1, &ets_cfg);
	अगर (((ets_cfg & NVM_ETS_TYPE_MASK) >> NVM_ETS_TYPE_SHIFT)
	    != NVM_ETS_TYPE_EMC)
		वापस E1000_NOT_IMPLEMENTED;

	num_sensors = (ets_cfg & NVM_ETS_NUM_SENSORS_MASK);
	अगर (num_sensors > E1000_MAX_SENSORS)
		num_sensors = E1000_MAX_SENSORS;

	क्रम (i = 1; i < num_sensors; i++) अणु
		hw->nvm.ops.पढ़ो(hw, (ets_offset + i), 1, &ets_sensor);
		sensor_index = ((ets_sensor & NVM_ETS_DATA_INDEX_MASK) >>
				NVM_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & NVM_ETS_DATA_LOC_MASK) >>
				   NVM_ETS_DATA_LOC_SHIFT);

		अगर (sensor_location != 0)
			hw->phy.ops.पढ़ो_i2c_byte(hw,
					e1000_emc_temp_data[sensor_index],
					E1000_I2C_THERMAL_SENSOR_ADDR,
					&data->sensor[i].temp);
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  igb_init_thermal_sensor_thresh_generic - Sets thermal sensor thresholds
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets the thermal sensor thresholds according to the NVM map
 *  and save off the threshold and location values पूर्णांकo mac.thermal_sensor_data
 **/
अटल s32 igb_init_thermal_sensor_thresh_generic(काष्ठा e1000_hw *hw)
अणु
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  low_thresh_delta;
	u8  num_sensors;
	u8  sensor_index;
	u8  sensor_location;
	u8  therm_limit;
	u8  i;
	काष्ठा e1000_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	अगर ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		वापस E1000_NOT_IMPLEMENTED;

	स_रखो(data, 0, माप(काष्ठा e1000_thermal_sensor_data));

	data->sensor[0].location = 0x1;
	data->sensor[0].caution_thresh =
		(rd32(E1000_THHIGHTC) & 0xFF);
	data->sensor[0].max_op_thresh =
		(rd32(E1000_THLOWTC) & 0xFF);

	/* Return the पूर्णांकernal sensor only अगर ETS is unsupported */
	hw->nvm.ops.पढ़ो(hw, NVM_ETS_CFG, 1, &ets_offset);
	अगर ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		वापस 0;

	hw->nvm.ops.पढ़ो(hw, ets_offset, 1, &ets_cfg);
	अगर (((ets_cfg & NVM_ETS_TYPE_MASK) >> NVM_ETS_TYPE_SHIFT)
	    != NVM_ETS_TYPE_EMC)
		वापस E1000_NOT_IMPLEMENTED;

	low_thresh_delta = ((ets_cfg & NVM_ETS_LTHRES_DELTA_MASK) >>
			    NVM_ETS_LTHRES_DELTA_SHIFT);
	num_sensors = (ets_cfg & NVM_ETS_NUM_SENSORS_MASK);

	क्रम (i = 1; i <= num_sensors; i++) अणु
		hw->nvm.ops.पढ़ो(hw, (ets_offset + i), 1, &ets_sensor);
		sensor_index = ((ets_sensor & NVM_ETS_DATA_INDEX_MASK) >>
				NVM_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & NVM_ETS_DATA_LOC_MASK) >>
				   NVM_ETS_DATA_LOC_SHIFT);
		therm_limit = ets_sensor & NVM_ETS_DATA_HTHRESH_MASK;

		hw->phy.ops.ग_लिखो_i2c_byte(hw,
			e1000_emc_therm_limit[sensor_index],
			E1000_I2C_THERMAL_SENSOR_ADDR,
			therm_limit);

		अगर ((i < E1000_MAX_SENSORS) && (sensor_location != 0)) अणु
			data->sensor[i].location = sensor_location;
			data->sensor[i].caution_thresh = therm_limit;
			data->sensor[i].max_op_thresh = therm_limit -
							low_thresh_delta;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर
अटल काष्ठा e1000_mac_operations e1000_mac_ops_82575 = अणु
	.init_hw              = igb_init_hw_82575,
	.check_क्रम_link       = igb_check_क्रम_link_82575,
	.rar_set              = igb_rar_set,
	.पढ़ो_mac_addr        = igb_पढ़ो_mac_addr_82575,
	.get_speed_and_duplex = igb_get_link_up_info_82575,
#अगर_घोषित CONFIG_IGB_HWMON
	.get_thermal_sensor_data = igb_get_thermal_sensor_data_generic,
	.init_thermal_sensor_thresh = igb_init_thermal_sensor_thresh_generic,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations e1000_phy_ops_82575 = अणु
	.acquire              = igb_acquire_phy_82575,
	.get_cfg_करोne         = igb_get_cfg_करोne_82575,
	.release              = igb_release_phy_82575,
	.ग_लिखो_i2c_byte       = igb_ग_लिखो_i2c_byte,
	.पढ़ो_i2c_byte        = igb_पढ़ो_i2c_byte,
पूर्ण;

अटल काष्ठा e1000_nvm_operations e1000_nvm_ops_82575 = अणु
	.acquire              = igb_acquire_nvm_82575,
	.पढ़ो                 = igb_पढ़ो_nvm_eerd,
	.release              = igb_release_nvm_82575,
	.ग_लिखो                = igb_ग_लिखो_nvm_spi,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_82575_info = अणु
	.get_invariants = igb_get_invariants_82575,
	.mac_ops = &e1000_mac_ops_82575,
	.phy_ops = &e1000_phy_ops_82575,
	.nvm_ops = &e1000_nvm_ops_82575,
पूर्ण;


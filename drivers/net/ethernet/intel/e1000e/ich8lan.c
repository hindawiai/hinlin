<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* 82562G 10/100 Network Connection
 * 82562G-2 10/100 Network Connection
 * 82562GT 10/100 Network Connection
 * 82562GT-2 10/100 Network Connection
 * 82562V 10/100 Network Connection
 * 82562V-2 10/100 Network Connection
 * 82566DC-2 Gigabit Network Connection
 * 82566DC Gigabit Network Connection
 * 82566DM-2 Gigabit Network Connection
 * 82566DM Gigabit Network Connection
 * 82566MC Gigabit Network Connection
 * 82566MM Gigabit Network Connection
 * 82567LM Gigabit Network Connection
 * 82567LF Gigabit Network Connection
 * 82567V Gigabit Network Connection
 * 82567LM-2 Gigabit Network Connection
 * 82567LF-2 Gigabit Network Connection
 * 82567V-2 Gigabit Network Connection
 * 82567LF-3 Gigabit Network Connection
 * 82567LM-3 Gigabit Network Connection
 * 82567LM-4 Gigabit Network Connection
 * 82577LM Gigabit Network Connection
 * 82577LC Gigabit Network Connection
 * 82578DM Gigabit Network Connection
 * 82578DC Gigabit Network Connection
 * 82579LM Gigabit Network Connection
 * 82579V Gigabit Network Connection
 * Ethernet Connection I217-LM
 * Ethernet Connection I217-V
 * Ethernet Connection I218-V
 * Ethernet Connection I218-LM
 * Ethernet Connection (2) I218-LM
 * Ethernet Connection (2) I218-V
 * Ethernet Connection (3) I218-LM
 * Ethernet Connection (3) I218-V
 */

#समावेश "e1000.h"

/* ICH GbE Flash Hardware Sequencing Flash Status Register bit अवरोधकरोwn */
/* Offset 04h HSFSTS */
जोड़ ich8_hws_flash_status अणु
	काष्ठा ich8_hsfsts अणु
		u16 flcकरोne:1;	/* bit 0 Flash Cycle Done */
		u16 flcerr:1;	/* bit 1 Flash Cycle Error */
		u16 dael:1;	/* bit 2 Direct Access error Log */
		u16 berasesz:2;	/* bit 4:3 Sector Erase Size */
		u16 flcinprog:1;	/* bit 5 flash cycle in Progress */
		u16 reserved1:2;	/* bit 13:6 Reserved */
		u16 reserved2:6;	/* bit 13:6 Reserved */
		u16 fldesvalid:1;	/* bit 14 Flash Descriptor Valid */
		u16 flockdn:1;	/* bit 15 Flash Config Lock-Down */
	पूर्ण hsf_status;
	u16 regval;
पूर्ण;

/* ICH GbE Flash Hardware Sequencing Flash control Register bit अवरोधकरोwn */
/* Offset 06h FLCTL */
जोड़ ich8_hws_flash_ctrl अणु
	काष्ठा ich8_hsflctl अणु
		u16 flcgo:1;	/* 0 Flash Cycle Go */
		u16 flcycle:2;	/* 2:1 Flash Cycle */
		u16 reserved:5;	/* 7:3 Reserved  */
		u16 fldbcount:2;	/* 9:8 Flash Data Byte Count */
		u16 flockdn:6;	/* 15:10 Reserved */
	पूर्ण hsf_ctrl;
	u16 regval;
पूर्ण;

/* ICH Flash Region Access Permissions */
जोड़ ich8_hws_flash_regacc अणु
	काष्ठा ich8_flracc अणु
		u32 grra:8;	/* 0:7 GbE region Read Access */
		u32 grwa:8;	/* 8:15 GbE region Write Access */
		u32 gmrag:8;	/* 23:16 GbE Master Read Access Grant */
		u32 gmwag:8;	/* 31:24 GbE Master Write Access Grant */
	पूर्ण hsf_flregacc;
	u16 regval;
पूर्ण;

/* ICH Flash Protected Region */
जोड़ ich8_flash_रक्षित_range अणु
	काष्ठा ich8_pr अणु
		u32 base:13;	/* 0:12 Protected Range Base */
		u32 reserved1:2;	/* 13:14 Reserved */
		u32 rpe:1;	/* 15 Read Protection Enable */
		u32 limit:13;	/* 16:28 Protected Range Limit */
		u32 reserved2:2;	/* 29:30 Reserved */
		u32 wpe:1;	/* 31 Write Protection Enable */
	पूर्ण range;
	u32 regval;
पूर्ण;

अटल व्योम e1000_clear_hw_cntrs_ich8lan(काष्ठा e1000_hw *hw);
अटल व्योम e1000_initialize_hw_bits_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_erase_flash_bank_ich8lan(काष्ठा e1000_hw *hw, u32 bank);
अटल s32 e1000_retry_ग_लिखो_flash_byte_ich8lan(काष्ठा e1000_hw *hw,
						u32 offset, u8 byte);
अटल s32 e1000_पढ़ो_flash_byte_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u8 *data);
अटल s32 e1000_पढ़ो_flash_word_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u16 *data);
अटल s32 e1000_पढ़ो_flash_data_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u8 size, u16 *data);
अटल s32 e1000_पढ़ो_flash_data32_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					   u32 *data);
अटल s32 e1000_पढ़ो_flash_dword_ich8lan(काष्ठा e1000_hw *hw,
					  u32 offset, u32 *data);
अटल s32 e1000_ग_लिखो_flash_data32_ich8lan(काष्ठा e1000_hw *hw,
					    u32 offset, u32 data);
अटल s32 e1000_retry_ग_लिखो_flash_dword_ich8lan(काष्ठा e1000_hw *hw,
						 u32 offset, u32 dword);
अटल s32 e1000_kmrn_lock_loss_workaround_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_cleanup_led_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_led_on_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_led_off_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_id_led_init_pchlan(काष्ठा e1000_hw *hw);
अटल s32 e1000_setup_led_pchlan(काष्ठा e1000_hw *hw);
अटल s32 e1000_cleanup_led_pchlan(काष्ठा e1000_hw *hw);
अटल s32 e1000_led_on_pchlan(काष्ठा e1000_hw *hw);
अटल s32 e1000_led_off_pchlan(काष्ठा e1000_hw *hw);
अटल s32 e1000_set_lplu_state_pchlan(काष्ठा e1000_hw *hw, bool active);
अटल व्योम e1000_घातer_करोwn_phy_copper_ich8lan(काष्ठा e1000_hw *hw);
अटल व्योम e1000_lan_init_करोne_ich8lan(काष्ठा e1000_hw *hw);
अटल s32 e1000_k1_gig_workaround_hv(काष्ठा e1000_hw *hw, bool link);
अटल s32 e1000_set_mdio_slow_mode_hv(काष्ठा e1000_hw *hw);
अटल bool e1000_check_mng_mode_ich8lan(काष्ठा e1000_hw *hw);
अटल bool e1000_check_mng_mode_pchlan(काष्ठा e1000_hw *hw);
अटल पूर्णांक e1000_rar_set_pch2lan(काष्ठा e1000_hw *hw, u8 *addr, u32 index);
अटल पूर्णांक e1000_rar_set_pch_lpt(काष्ठा e1000_hw *hw, u8 *addr, u32 index);
अटल u32 e1000_rar_get_count_pch_lpt(काष्ठा e1000_hw *hw);
अटल s32 e1000_k1_workaround_lv(काष्ठा e1000_hw *hw);
अटल व्योम e1000_gate_hw_phy_config_ich8lan(काष्ठा e1000_hw *hw, bool gate);
अटल s32 e1000_disable_ulp_lpt_lp(काष्ठा e1000_hw *hw, bool क्रमce);
अटल s32 e1000_setup_copper_link_pch_lpt(काष्ठा e1000_hw *hw);
अटल s32 e1000_oem_bits_config_ich8lan(काष्ठा e1000_hw *hw, bool d0_state);

अटल अंतरभूत u16 __er16flash(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोw(hw->flash_address + reg);
पूर्ण

अटल अंतरभूत u32 __er32flash(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(hw->flash_address + reg);
पूर्ण

अटल अंतरभूत व्योम __ew16flash(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg, u16 val)
अणु
	ग_लिखोw(val, hw->flash_address + reg);
पूर्ण

अटल अंतरभूत व्योम __ew32flash(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg, u32 val)
अणु
	ग_लिखोl(val, hw->flash_address + reg);
पूर्ण

#घोषणा er16flash(reg)		__er16flash(hw, (reg))
#घोषणा er32flash(reg)		__er32flash(hw, (reg))
#घोषणा ew16flash(reg, val)	__ew16flash(hw, (reg), (val))
#घोषणा ew32flash(reg, val)	__ew32flash(hw, (reg), (val))

/**
 *  e1000_phy_is_accessible_pchlan - Check अगर able to access PHY रेजिस्टरs
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Test access to the PHY रेजिस्टरs by पढ़ोing the PHY ID रेजिस्टरs.  If
 *  the PHY ID is alपढ़ोy known (e.g. resume path) compare it with known ID,
 *  otherwise assume the पढ़ो PHY ID is correct अगर it is valid.
 *
 *  Assumes the sw/fw/hw semaphore is alपढ़ोy acquired.
 **/
अटल bool e1000_phy_is_accessible_pchlan(काष्ठा e1000_hw *hw)
अणु
	u16 phy_reg = 0;
	u32 phy_id = 0;
	s32 ret_val = 0;
	u16 retry_count;
	u32 mac_reg = 0;

	क्रम (retry_count = 0; retry_count < 2; retry_count++) अणु
		ret_val = e1e_rphy_locked(hw, MII_PHYSID1, &phy_reg);
		अगर (ret_val || (phy_reg == 0xFFFF))
			जारी;
		phy_id = (u32)(phy_reg << 16);

		ret_val = e1e_rphy_locked(hw, MII_PHYSID2, &phy_reg);
		अगर (ret_val || (phy_reg == 0xFFFF)) अणु
			phy_id = 0;
			जारी;
		पूर्ण
		phy_id |= (u32)(phy_reg & PHY_REVISION_MASK);
		अवरोध;
	पूर्ण

	अगर (hw->phy.id) अणु
		अगर (hw->phy.id == phy_id)
			जाओ out;
	पूर्ण अन्यथा अगर (phy_id) अणु
		hw->phy.id = phy_id;
		hw->phy.revision = (u32)(phy_reg & ~PHY_REVISION_MASK);
		जाओ out;
	पूर्ण

	/* In हाल the PHY needs to be in mdio slow mode,
	 * set slow mode and try to get the PHY id again.
	 */
	अगर (hw->mac.type < e1000_pch_lpt) अणु
		hw->phy.ops.release(hw);
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		अगर (!ret_val)
			ret_val = e1000e_get_phy_id(hw);
		hw->phy.ops.acquire(hw);
	पूर्ण

	अगर (ret_val)
		वापस false;
out:
	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		/* Only unक्रमce SMBus अगर ME is not active */
		अगर (!(er32(FWSM) & E1000_ICH_FWSM_FW_VALID)) अणु
			/* Unक्रमce SMBus mode in PHY */
			e1e_rphy_locked(hw, CV_SMB_CTRL, &phy_reg);
			phy_reg &= ~CV_SMB_CTRL_FORCE_SMBUS;
			e1e_wphy_locked(hw, CV_SMB_CTRL, phy_reg);

			/* Unक्रमce SMBus mode in MAC */
			mac_reg = er32(CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			ew32(CTRL_EXT, mac_reg);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 *  e1000_toggle_lanphypc_pch_lpt - toggle the LANPHYPC pin value
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Toggling the LANPHYPC pin value fully घातer-cycles the PHY and is
 *  used to reset the PHY to a quiescent state when necessary.
 **/
अटल व्योम e1000_toggle_lanphypc_pch_lpt(काष्ठा e1000_hw *hw)
अणु
	u32 mac_reg;

	/* Set Phy Config Counter to 50msec */
	mac_reg = er32(FEXTNVM3);
	mac_reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
	mac_reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
	ew32(FEXTNVM3, mac_reg);

	/* Toggle LANPHYPC Value bit */
	mac_reg = er32(CTRL);
	mac_reg |= E1000_CTRL_LANPHYPC_OVERRIDE;
	mac_reg &= ~E1000_CTRL_LANPHYPC_VALUE;
	ew32(CTRL, mac_reg);
	e1e_flush();
	usleep_range(10, 20);
	mac_reg &= ~E1000_CTRL_LANPHYPC_OVERRIDE;
	ew32(CTRL, mac_reg);
	e1e_flush();

	अगर (hw->mac.type < e1000_pch_lpt) अणु
		msleep(50);
	पूर्ण अन्यथा अणु
		u16 count = 20;

		करो अणु
			usleep_range(5000, 6000);
		पूर्ण जबतक (!(er32(CTRL_EXT) & E1000_CTRL_EXT_LPCD) && count--);

		msleep(30);
	पूर्ण
पूर्ण

/**
 *  e1000_init_phy_workarounds_pchlan - PHY initialization workarounds
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Workarounds/flow necessary क्रम PHY initialization during driver load
 *  and resume paths.
 **/
अटल s32 e1000_init_phy_workarounds_pchlan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_adapter *adapter = hw->adapter;
	u32 mac_reg, fwsm = er32(FWSM);
	s32 ret_val;

	/* Gate स्वतःmatic PHY configuration by hardware on managed and
	 * non-managed 82579 and newer adapters.
	 */
	e1000_gate_hw_phy_config_ich8lan(hw, true);

	/* It is not possible to be certain of the current state of ULP
	 * so क्रमcibly disable it.
	 */
	hw->dev_spec.ich8lan.ulp_state = e1000_ulp_state_unknown;
	ret_val = e1000_disable_ulp_lpt_lp(hw, true);
	अगर (ret_val)
		e_warn("Failed to disable ULP\n");

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val) अणु
		e_dbg("Failed to initialize PHY flow\n");
		जाओ out;
	पूर्ण

	/* The MAC-PHY पूर्णांकerconnect may be in SMBus mode.  If the PHY is
	 * inaccessible and resetting the PHY is not blocked, toggle the
	 * LANPHYPC Value bit to क्रमce the पूर्णांकerconnect to PCIe mode.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		अगर (e1000_phy_is_accessible_pchlan(hw))
			अवरोध;

		/* Beक्रमe toggling LANPHYPC, see अगर PHY is accessible by
		 * क्रमcing MAC to SMBus mode first.
		 */
		mac_reg = er32(CTRL_EXT);
		mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
		ew32(CTRL_EXT, mac_reg);

		/* Wait 50 milliseconds क्रम MAC to finish any retries
		 * that it might be trying to perक्रमm from previous
		 * attempts to acknowledge any phy पढ़ो requests.
		 */
		msleep(50);

		fallthrough;
	हाल e1000_pch2lan:
		अगर (e1000_phy_is_accessible_pchlan(hw))
			अवरोध;

		fallthrough;
	हाल e1000_pchlan:
		अगर ((hw->mac.type == e1000_pchlan) &&
		    (fwsm & E1000_ICH_FWSM_FW_VALID))
			अवरोध;

		अगर (hw->phy.ops.check_reset_block(hw)) अणु
			e_dbg("Required LANPHYPC toggle blocked by ME\n");
			ret_val = -E1000_ERR_PHY;
			अवरोध;
		पूर्ण

		/* Toggle LANPHYPC Value bit */
		e1000_toggle_lanphypc_pch_lpt(hw);
		अगर (hw->mac.type >= e1000_pch_lpt) अणु
			अगर (e1000_phy_is_accessible_pchlan(hw))
				अवरोध;

			/* Toggling LANPHYPC brings the PHY out of SMBus mode
			 * so ensure that the MAC is also out of SMBus mode
			 */
			mac_reg = er32(CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			ew32(CTRL_EXT, mac_reg);

			अगर (e1000_phy_is_accessible_pchlan(hw))
				अवरोध;

			ret_val = -E1000_ERR_PHY;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	hw->phy.ops.release(hw);
	अगर (!ret_val) अणु

		/* Check to see अगर able to reset PHY.  Prपूर्णांक error अगर not */
		अगर (hw->phy.ops.check_reset_block(hw)) अणु
			e_err("Reset blocked by ME\n");
			जाओ out;
		पूर्ण

		/* Reset the PHY beक्रमe any access to it.  Doing so, ensures
		 * that the PHY is in a known good state beक्रमe we पढ़ो/ग_लिखो
		 * PHY रेजिस्टरs.  The generic reset is sufficient here,
		 * because we haven't determined the PHY type yet.
		 */
		ret_val = e1000e_phy_hw_reset_generic(hw);
		अगर (ret_val)
			जाओ out;

		/* On a successful reset, possibly need to रुको क्रम the PHY
		 * to quiesce to an accessible state beक्रमe वापसing control
		 * to the calling function.  If the PHY करोes not quiesce, then
		 * वापस E1000E_BLK_PHY_RESET, as this is the condition that
		 *  the PHY is in.
		 */
		ret_val = hw->phy.ops.check_reset_block(hw);
		अगर (ret_val)
			e_err("ME blocked access to PHY after reset\n");
	पूर्ण

out:
	/* Ungate स्वतःmatic PHY configuration on non-managed 82579 */
	अगर ((hw->mac.type == e1000_pch2lan) &&
	    !(fwsm & E1000_ICH_FWSM_FW_VALID)) अणु
		usleep_range(10000, 11000);
		e1000_gate_hw_phy_config_ich8lan(hw, false);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_init_phy_params_pchlan - Initialize PHY function poपूर्णांकers
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize family-specअगरic PHY parameters and function poपूर्णांकers.
 **/
अटल s32 e1000_init_phy_params_pchlan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;

	phy->addr = 1;
	phy->reset_delay_us = 100;

	phy->ops.set_page = e1000_set_page_igp;
	phy->ops.पढ़ो_reg = e1000_पढ़ो_phy_reg_hv;
	phy->ops.पढ़ो_reg_locked = e1000_पढ़ो_phy_reg_hv_locked;
	phy->ops.पढ़ो_reg_page = e1000_पढ़ो_phy_reg_page_hv;
	phy->ops.set_d0_lplu_state = e1000_set_lplu_state_pchlan;
	phy->ops.set_d3_lplu_state = e1000_set_lplu_state_pchlan;
	phy->ops.ग_लिखो_reg = e1000_ग_लिखो_phy_reg_hv;
	phy->ops.ग_लिखो_reg_locked = e1000_ग_लिखो_phy_reg_hv_locked;
	phy->ops.ग_लिखो_reg_page = e1000_ग_लिखो_phy_reg_page_hv;
	phy->ops.घातer_up = e1000_घातer_up_phy_copper;
	phy->ops.घातer_करोwn = e1000_घातer_करोwn_phy_copper_ich8lan;
	phy->स्वतःneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;

	phy->id = e1000_phy_unknown;

	ret_val = e1000_init_phy_workarounds_pchlan(hw);
	अगर (ret_val)
		वापस ret_val;

	अगर (phy->id == e1000_phy_unknown)
		चयन (hw->mac.type) अणु
		शेष:
			ret_val = e1000e_get_phy_id(hw);
			अगर (ret_val)
				वापस ret_val;
			अगर ((phy->id != 0) && (phy->id != PHY_REVISION_MASK))
				अवरोध;
			fallthrough;
		हाल e1000_pch2lan:
		हाल e1000_pch_lpt:
		हाल e1000_pch_spt:
		हाल e1000_pch_cnp:
		हाल e1000_pch_tgp:
		हाल e1000_pch_adp:
		हाल e1000_pch_mtp:
			/* In हाल the PHY needs to be in mdio slow mode,
			 * set slow mode and try to get the PHY id again.
			 */
			ret_val = e1000_set_mdio_slow_mode_hv(hw);
			अगर (ret_val)
				वापस ret_val;
			ret_val = e1000e_get_phy_id(hw);
			अगर (ret_val)
				वापस ret_val;
			अवरोध;
		पूर्ण
	phy->type = e1000e_get_phy_type_from_id(phy->id);

	चयन (phy->type) अणु
	हाल e1000_phy_82577:
	हाल e1000_phy_82579:
	हाल e1000_phy_i217:
		phy->ops.check_polarity = e1000_check_polarity_82577;
		phy->ops.क्रमce_speed_duplex =
		    e1000_phy_क्रमce_speed_duplex_82577;
		phy->ops.get_cable_length = e1000_get_cable_length_82577;
		phy->ops.get_info = e1000_get_phy_info_82577;
		phy->ops.commit = e1000e_phy_sw_reset;
		अवरोध;
	हाल e1000_phy_82578:
		phy->ops.check_polarity = e1000_check_polarity_m88;
		phy->ops.क्रमce_speed_duplex = e1000e_phy_क्रमce_speed_duplex_m88;
		phy->ops.get_cable_length = e1000e_get_cable_length_m88;
		phy->ops.get_info = e1000e_get_phy_info_m88;
		अवरोध;
	शेष:
		ret_val = -E1000_ERR_PHY;
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_init_phy_params_ich8lan - Initialize PHY function poपूर्णांकers
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize family-specअगरic PHY parameters and function poपूर्णांकers.
 **/
अटल s32 e1000_init_phy_params_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 i = 0;

	phy->addr = 1;
	phy->reset_delay_us = 100;

	phy->ops.घातer_up = e1000_घातer_up_phy_copper;
	phy->ops.घातer_करोwn = e1000_घातer_करोwn_phy_copper_ich8lan;

	/* We may need to करो this twice - once क्रम IGP and अगर that fails,
	 * we'll set BM func poपूर्णांकers and try again
	 */
	ret_val = e1000e_determine_phy_address(hw);
	अगर (ret_val) अणु
		phy->ops.ग_लिखो_reg = e1000e_ग_लिखो_phy_reg_bm;
		phy->ops.पढ़ो_reg = e1000e_पढ़ो_phy_reg_bm;
		ret_val = e1000e_determine_phy_address(hw);
		अगर (ret_val) अणु
			e_dbg("Cannot determine PHY addr. Erroring out\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	phy->id = 0;
	जबतक ((e1000_phy_unknown == e1000e_get_phy_type_from_id(phy->id)) &&
	       (i++ < 100)) अणु
		usleep_range(1000, 1100);
		ret_val = e1000e_get_phy_id(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Verअगरy phy id */
	चयन (phy->id) अणु
	हाल IGP03E1000_E_PHY_ID:
		phy->type = e1000_phy_igp_3;
		phy->स्वतःneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
		phy->ops.पढ़ो_reg_locked = e1000e_पढ़ो_phy_reg_igp_locked;
		phy->ops.ग_लिखो_reg_locked = e1000e_ग_लिखो_phy_reg_igp_locked;
		phy->ops.get_info = e1000e_get_phy_info_igp;
		phy->ops.check_polarity = e1000_check_polarity_igp;
		phy->ops.क्रमce_speed_duplex = e1000e_phy_क्रमce_speed_duplex_igp;
		अवरोध;
	हाल IFE_E_PHY_ID:
	हाल IFE_PLUS_E_PHY_ID:
	हाल IFE_C_E_PHY_ID:
		phy->type = e1000_phy_अगरe;
		phy->स्वतःneg_mask = E1000_ALL_NOT_GIG;
		phy->ops.get_info = e1000_get_phy_info_अगरe;
		phy->ops.check_polarity = e1000_check_polarity_अगरe;
		phy->ops.क्रमce_speed_duplex = e1000_phy_क्रमce_speed_duplex_अगरe;
		अवरोध;
	हाल BME1000_E_PHY_ID:
		phy->type = e1000_phy_bm;
		phy->स्वतःneg_mask = AUTONEG_ADVERTISE_SPEED_DEFAULT;
		phy->ops.पढ़ो_reg = e1000e_पढ़ो_phy_reg_bm;
		phy->ops.ग_लिखो_reg = e1000e_ग_लिखो_phy_reg_bm;
		phy->ops.commit = e1000e_phy_sw_reset;
		phy->ops.get_info = e1000e_get_phy_info_m88;
		phy->ops.check_polarity = e1000_check_polarity_m88;
		phy->ops.क्रमce_speed_duplex = e1000e_phy_क्रमce_speed_duplex_m88;
		अवरोध;
	शेष:
		वापस -E1000_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_init_nvm_params_ich8lan - Initialize NVM function poपूर्णांकers
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize family-specअगरic NVM parameters and function
 *  poपूर्णांकers.
 **/
अटल s32 e1000_init_nvm_params_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 gfpreg, sector_base_addr, sector_end_addr;
	u16 i;
	u32 nvm_size;

	nvm->type = e1000_nvm_flash_sw;

	अगर (hw->mac.type >= e1000_pch_spt) अणु
		/* in SPT, gfpreg करोesn't exist. NVM size is taken from the
		 * STRAP रेजिस्टर. This is because in SPT the GbE Flash region
		 * is no दीर्घer accessed through the flash रेजिस्टरs. Instead,
		 * the mechanism has changed, and the Flash region access
		 * रेजिस्टरs are now implemented in GbE memory space.
		 */
		nvm->flash_base_addr = 0;
		nvm_size = (((er32(STRAP) >> 1) & 0x1F) + 1)
		    * NVM_SIZE_MULTIPLIER;
		nvm->flash_bank_size = nvm_size / 2;
		/* Adjust to word count */
		nvm->flash_bank_size /= माप(u16);
		/* Set the base address क्रम flash रेजिस्टर access */
		hw->flash_address = hw->hw_addr + E1000_FLASH_BASE_ADDR;
	पूर्ण अन्यथा अणु
		/* Can't read flash registers if register set isn't mapped. */
		अगर (!hw->flash_address) अणु
			e_dbg("ERROR: Flash registers not mapped\n");
			वापस -E1000_ERR_CONFIG;
		पूर्ण

		gfpreg = er32flash(ICH_FLASH_GFPREG);

		/* sector_X_addr is a "sector"-aligned address (4096 bytes)
		 * Add 1 to sector_end_addr since this sector is included in
		 * the overall size.
		 */
		sector_base_addr = gfpreg & FLASH_GFPREG_BASE_MASK;
		sector_end_addr = ((gfpreg >> 16) & FLASH_GFPREG_BASE_MASK) + 1;

		/* flash_base_addr is byte-aligned */
		nvm->flash_base_addr = sector_base_addr
		    << FLASH_SECTOR_ADDR_SHIFT;

		/* find total size of the NVM, then cut in half since the total
		 * size represents two separate NVM banks.
		 */
		nvm->flash_bank_size = ((sector_end_addr - sector_base_addr)
					<< FLASH_SECTOR_ADDR_SHIFT);
		nvm->flash_bank_size /= 2;
		/* Adjust to word count */
		nvm->flash_bank_size /= माप(u16);
	पूर्ण

	nvm->word_size = E1000_ICH8_SHADOW_RAM_WORDS;

	/* Clear shaकरोw ram */
	क्रम (i = 0; i < nvm->word_size; i++) अणु
		dev_spec->shaकरोw_ram[i].modअगरied = false;
		dev_spec->shaकरोw_ram[i].value = 0xFFFF;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_init_mac_params_ich8lan - Initialize MAC function poपूर्णांकers
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize family-specअगरic MAC parameters and function
 *  poपूर्णांकers.
 **/
अटल s32 e1000_init_mac_params_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;

	/* Set media type function poपूर्णांकer */
	hw->phy.media_type = e1000_media_type_copper;

	/* Set mta रेजिस्टर count */
	mac->mta_reg_count = 32;
	/* Set rar entry count */
	mac->rar_entry_count = E1000_ICH_RAR_ENTRIES;
	अगर (mac->type == e1000_ich8lan)
		mac->rar_entry_count--;
	/* FWSM रेजिस्टर */
	mac->has_fwsm = true;
	/* ARC subप्रणाली not supported */
	mac->arc_subप्रणाली_valid = false;
	/* Adaptive IFS supported */
	mac->adaptive_अगरs = true;

	/* LED and other operations */
	चयन (mac->type) अणु
	हाल e1000_ich8lan:
	हाल e1000_ich9lan:
	हाल e1000_ich10lan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_ich8lan;
		/* ID LED init */
		mac->ops.id_led_init = e1000e_id_led_init_generic;
		/* blink LED */
		mac->ops.blink_led = e1000e_blink_led_generic;
		/* setup LED */
		mac->ops.setup_led = e1000e_setup_led_generic;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_ich8lan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_ich8lan;
		mac->ops.led_off = e1000_led_off_ich8lan;
		अवरोध;
	हाल e1000_pch2lan:
		mac->rar_entry_count = E1000_PCH2_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch2lan;
		fallthrough;
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
	हाल e1000_pchlan:
		/* check management mode */
		mac->ops.check_mng_mode = e1000_check_mng_mode_pchlan;
		/* ID LED init */
		mac->ops.id_led_init = e1000_id_led_init_pchlan;
		/* setup LED */
		mac->ops.setup_led = e1000_setup_led_pchlan;
		/* cleanup LED */
		mac->ops.cleanup_led = e1000_cleanup_led_pchlan;
		/* turn on/off LED */
		mac->ops.led_on = e1000_led_on_pchlan;
		mac->ops.led_off = e1000_led_off_pchlan;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (mac->type >= e1000_pch_lpt) अणु
		mac->rar_entry_count = E1000_PCH_LPT_RAR_ENTRIES;
		mac->ops.rar_set = e1000_rar_set_pch_lpt;
		mac->ops.setup_physical_पूर्णांकerface =
		    e1000_setup_copper_link_pch_lpt;
		mac->ops.rar_get_count = e1000_rar_get_count_pch_lpt;
	पूर्ण

	/* Enable PCS Lock-loss workaround क्रम ICH8 */
	अगर (mac->type == e1000_ich8lan)
		e1000e_set_kmrn_lock_loss_workaround_ich8lan(hw, true);

	वापस 0;
पूर्ण

/**
 *  __e1000_access_emi_reg_locked - Read/ग_लिखो EMI रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @address: EMI address to program
 *  @data: poपूर्णांकer to value to पढ़ो/ग_लिखो from/to the EMI address
 *  @पढ़ो: boolean flag to indicate पढ़ो or ग_लिखो
 *
 *  This helper function assumes the SW/FW/HW Semaphore is alपढ़ोy acquired.
 **/
अटल s32 __e1000_access_emi_reg_locked(काष्ठा e1000_hw *hw, u16 address,
					 u16 *data, bool पढ़ो)
अणु
	s32 ret_val;

	ret_val = e1e_wphy_locked(hw, I82579_EMI_ADDR, address);
	अगर (ret_val)
		वापस ret_val;

	अगर (पढ़ो)
		ret_val = e1e_rphy_locked(hw, I82579_EMI_DATA, data);
	अन्यथा
		ret_val = e1e_wphy_locked(hw, I82579_EMI_DATA, *data);

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_emi_reg_locked - Read Extended Management Interface रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: EMI address to program
 *  @data: value to be पढ़ो from the EMI address
 *
 *  Assumes the SW/FW/HW Semaphore is alपढ़ोy acquired.
 **/
s32 e1000_पढ़ो_emi_reg_locked(काष्ठा e1000_hw *hw, u16 addr, u16 *data)
अणु
	वापस __e1000_access_emi_reg_locked(hw, addr, data, true);
पूर्ण

/**
 *  e1000_ग_लिखो_emi_reg_locked - Write Extended Management Interface रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: EMI address to program
 *  @data: value to be written to the EMI address
 *
 *  Assumes the SW/FW/HW Semaphore is alपढ़ोy acquired.
 **/
s32 e1000_ग_लिखो_emi_reg_locked(काष्ठा e1000_hw *hw, u16 addr, u16 data)
अणु
	वापस __e1000_access_emi_reg_locked(hw, addr, &data, false);
पूर्ण

/**
 *  e1000_set_eee_pchlan - Enable/disable EEE support
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Enable/disable EEE based on setting in dev_spec काष्ठाure, the duplex of
 *  the link and the EEE capabilities of the link partner.  The LPI Control
 *  रेजिस्टर bits will reमुख्य set only अगर/when link is up.
 *
 *  EEE LPI must not be निश्चितed earlier than one second after link is up.
 *  On 82579, EEE LPI should not be enabled until such समय otherwise there
 *  can be link issues with some चयनes.  Other devices can have EEE LPI
 *  enabled immediately upon link up since they have a समयr in hardware which
 *  prevents LPI from being निश्चितed too early.
 **/
s32 e1000_set_eee_pchlan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	s32 ret_val;
	u16 lpa, pcs_status, adv, adv_addr, lpi_ctrl, data;

	चयन (hw->phy.type) अणु
	हाल e1000_phy_82579:
		lpa = I82579_EEE_LP_ABILITY;
		pcs_status = I82579_EEE_PCS_STATUS;
		adv_addr = I82579_EEE_ADVERTISEMENT;
		अवरोध;
	हाल e1000_phy_i217:
		lpa = I217_EEE_LP_ABILITY;
		pcs_status = I217_EEE_PCS_STATUS;
		adv_addr = I217_EEE_ADVERTISEMENT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1e_rphy_locked(hw, I82579_LPI_CTRL, &lpi_ctrl);
	अगर (ret_val)
		जाओ release;

	/* Clear bits that enable EEE in various speeds */
	lpi_ctrl &= ~I82579_LPI_CTRL_ENABLE_MASK;

	/* Enable EEE अगर not disabled by user */
	अगर (!dev_spec->eee_disable) अणु
		/* Save off link partner's EEE ability */
		ret_val = e1000_पढ़ो_emi_reg_locked(hw, lpa,
						    &dev_spec->eee_lp_ability);
		अगर (ret_val)
			जाओ release;

		/* Read EEE advertisement */
		ret_val = e1000_पढ़ो_emi_reg_locked(hw, adv_addr, &adv);
		अगर (ret_val)
			जाओ release;

		/* Enable EEE only क्रम speeds in which the link partner is
		 * EEE capable and क्रम which we advertise EEE.
		 */
		अगर (adv & dev_spec->eee_lp_ability & I82579_EEE_1000_SUPPORTED)
			lpi_ctrl |= I82579_LPI_CTRL_1000_ENABLE;

		अगर (adv & dev_spec->eee_lp_ability & I82579_EEE_100_SUPPORTED) अणु
			e1e_rphy_locked(hw, MII_LPA, &data);
			अगर (data & LPA_100FULL)
				lpi_ctrl |= I82579_LPI_CTRL_100_ENABLE;
			अन्यथा
				/* EEE is not supported in 100Half, so ignore
				 * partner's EEE in 100 ability अगर full-duplex
				 * is not advertised.
				 */
				dev_spec->eee_lp_ability &=
				    ~I82579_EEE_100_SUPPORTED;
		पूर्ण
	पूर्ण

	अगर (hw->phy.type == e1000_phy_82579) अणु
		ret_val = e1000_पढ़ो_emi_reg_locked(hw, I82579_LPI_PLL_SHUT,
						    &data);
		अगर (ret_val)
			जाओ release;

		data &= ~I82579_LPI_100_PLL_SHUT;
		ret_val = e1000_ग_लिखो_emi_reg_locked(hw, I82579_LPI_PLL_SHUT,
						     data);
	पूर्ण

	/* R/Clr IEEE MMD 3.1 bits 11:10 - Tx/Rx LPI Received */
	ret_val = e1000_पढ़ो_emi_reg_locked(hw, pcs_status, &data);
	अगर (ret_val)
		जाओ release;

	ret_val = e1e_wphy_locked(hw, I82579_LPI_CTRL, lpi_ctrl);
release:
	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_k1_workaround_lpt_lp - K1 workaround on Lynxpoपूर्णांक-LP
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 *  @link: link up bool flag
 *
 *  When K1 is enabled क्रम 1Gbps, the MAC can miss 2 DMA completion indications
 *  preventing further DMA ग_लिखो requests.  Workaround the issue by disabling
 *  the de-निश्चितion of the घड़ी request when in 1Gpbs mode.
 *  Also, set appropriate Tx re-transmission समयouts क्रम 10 and 100Half link
 *  speeds in order to aव्योम Tx hangs.
 **/
अटल s32 e1000_k1_workaround_lpt_lp(काष्ठा e1000_hw *hw, bool link)
अणु
	u32 fextnvm6 = er32(FEXTNVM6);
	u32 status = er32(STATUS);
	s32 ret_val = 0;
	u16 reg;

	अगर (link && (status & E1000_STATUS_SPEED_1000)) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val =
		    e1000e_पढ़ो_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
						&reg);
		अगर (ret_val)
			जाओ release;

		ret_val =
		    e1000e_ग_लिखो_kmrn_reg_locked(hw,
						 E1000_KMRNCTRLSTA_K1_CONFIG,
						 reg &
						 ~E1000_KMRNCTRLSTA_K1_ENABLE);
		अगर (ret_val)
			जाओ release;

		usleep_range(10, 20);

		ew32(FEXTNVM6, fextnvm6 | E1000_FEXTNVM6_REQ_PLL_CLK);

		ret_val =
		    e1000e_ग_लिखो_kmrn_reg_locked(hw,
						 E1000_KMRNCTRLSTA_K1_CONFIG,
						 reg);
release:
		hw->phy.ops.release(hw);
	पूर्ण अन्यथा अणु
		/* clear FEXTNVM6 bit 8 on link करोwn or 10/100 */
		fextnvm6 &= ~E1000_FEXTNVM6_REQ_PLL_CLK;

		अगर ((hw->phy.revision > 5) || !link ||
		    ((status & E1000_STATUS_SPEED_100) &&
		     (status & E1000_STATUS_FD)))
			जाओ update_fextnvm6;

		ret_val = e1e_rphy(hw, I217_INBAND_CTRL, &reg);
		अगर (ret_val)
			वापस ret_val;

		/* Clear link status transmit समयout */
		reg &= ~I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_MASK;

		अगर (status & E1000_STATUS_SPEED_100) अणु
			/* Set inband Tx समयout to 5x10us क्रम 100Half */
			reg |= 5 << I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT;

			/* Do not extend the K1 entry latency क्रम 100Half */
			fextnvm6 &= ~E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION;
		पूर्ण अन्यथा अणु
			/* Set inband Tx समयout to 50x10us क्रम 10Full/Half */
			reg |= 50 <<
			    I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT;

			/* Extend the K1 entry latency क्रम 10 Mbps */
			fextnvm6 |= E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION;
		पूर्ण

		ret_val = e1e_wphy(hw, I217_INBAND_CTRL, reg);
		अगर (ret_val)
			वापस ret_val;

update_fextnvm6:
		ew32(FEXTNVM6, fextnvm6);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_platक्रमm_pm_pch_lpt - Set platक्रमm घातer management values
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @link: bool indicating link status
 *
 *  Set the Latency Tolerance Reporting (LTR) values क्रम the "PCIe-like"
 *  GbE MAC in the Lynx Poपूर्णांक PCH based on Rx buffer size and link speed
 *  when link is up (which must not exceed the maximum latency supported
 *  by the platक्रमm), otherwise specअगरy there is no LTR requirement.
 *  Unlike true-PCIe devices which set the LTR maximum snoop/no-snoop
 *  latencies in the LTR Extended Capability Structure in the PCIe Extended
 *  Capability रेजिस्टर set, on this device LTR is set by writing the
 *  equivalent snoop/no-snoop latencies in the LTRV रेजिस्टर in the MAC and
 *  set the SEND bit to send an Intel On-chip System Fabric sideband (IOSF-SB)
 *  message to the PMC.
 **/
अटल s32 e1000_platक्रमm_pm_pch_lpt(काष्ठा e1000_hw *hw, bool link)
अणु
	u32 reg = link << (E1000_LTRV_REQ_SHIFT + E1000_LTRV_NOSNOOP_SHIFT) |
	    link << E1000_LTRV_REQ_SHIFT | E1000_LTRV_SEND;
	u16 lat_enc = 0;	/* latency encoded */

	अगर (link) अणु
		u16 speed, duplex, scale = 0;
		u16 max_snoop, max_nosnoop;
		u16 max_ltr_enc;	/* max LTR latency encoded */
		u64 value;
		u32 rxa;

		अगर (!hw->adapter->max_frame_size) अणु
			e_dbg("max_frame_size not set.\n");
			वापस -E1000_ERR_CONFIG;
		पूर्ण

		hw->mac.ops.get_link_up_info(hw, &speed, &duplex);
		अगर (!speed) अणु
			e_dbg("Speed not set.\n");
			वापस -E1000_ERR_CONFIG;
		पूर्ण

		/* Rx Packet Buffer Allocation size (KB) */
		rxa = er32(PBA) & E1000_PBA_RXA_MASK;

		/* Determine the maximum latency tolerated by the device.
		 *
		 * Per the PCIe spec, the tolerated latencies are encoded as
		 * a 3-bit encoded scale (only 0-5 are valid) multiplied by
		 * a 10-bit value (0-1023) to provide a range from 1 ns to
		 * 2^25*(2^10-1) ns.  The scale is encoded as 0=2^0ns,
		 * 1=2^5ns, 2=2^10ns,...5=2^25ns.
		 */
		rxa *= 512;
		value = (rxa > hw->adapter->max_frame_size) ?
			(rxa - hw->adapter->max_frame_size) * (16000 / speed) :
			0;

		जबतक (value > PCI_LTR_VALUE_MASK) अणु
			scale++;
			value = DIV_ROUND_UP(value, BIT(5));
		पूर्ण
		अगर (scale > E1000_LTRV_SCALE_MAX) अणु
			e_dbg("Invalid LTR latency scale %d\n", scale);
			वापस -E1000_ERR_CONFIG;
		पूर्ण
		lat_enc = (u16)((scale << PCI_LTR_SCALE_SHIFT) | value);

		/* Determine the maximum latency tolerated by the platक्रमm */
		pci_पढ़ो_config_word(hw->adapter->pdev, E1000_PCI_LTR_CAP_LPT,
				     &max_snoop);
		pci_पढ़ो_config_word(hw->adapter->pdev,
				     E1000_PCI_LTR_CAP_LPT + 2, &max_nosnoop);
		max_ltr_enc = max_t(u16, max_snoop, max_nosnoop);

		अगर (lat_enc > max_ltr_enc)
			lat_enc = max_ltr_enc;
	पूर्ण

	/* Set Snoop and No-Snoop latencies the same */
	reg |= lat_enc | (lat_enc << E1000_LTRV_NOSNOOP_SHIFT);
	ew32(LTRV, reg);

	वापस 0;
पूर्ण

/**
 *  e1000_enable_ulp_lpt_lp - configure Ultra Low Power mode क्रम LynxPoपूर्णांक-LP
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @to_sx: boolean indicating a प्रणाली घातer state transition to Sx
 *
 *  When link is करोwn, configure ULP mode to signअगरicantly reduce the घातer
 *  to the PHY.  If on a Manageability Engine (ME) enabled प्रणाली, tell the
 *  ME firmware to start the ULP configuration.  If not on an ME enabled
 *  प्रणाली, configure the ULP mode by software.
 */
s32 e1000_enable_ulp_lpt_lp(काष्ठा e1000_hw *hw, bool to_sx)
अणु
	u32 mac_reg;
	s32 ret_val = 0;
	u16 phy_reg;
	u16 oem_reg = 0;

	अगर ((hw->mac.type < e1000_pch_lpt) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPT_I217_LM) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPT_I217_V) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_LM2) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_V2) ||
	    (hw->dev_spec.ich8lan.ulp_state == e1000_ulp_state_on))
		वापस 0;

	अगर (er32(FWSM) & E1000_ICH_FWSM_FW_VALID) अणु
		/* Request ME configure ULP mode in the PHY */
		mac_reg = er32(H2ME);
		mac_reg |= E1000_H2ME_ULP | E1000_H2ME_ENFORCE_SETTINGS;
		ew32(H2ME, mac_reg);

		जाओ out;
	पूर्ण

	अगर (!to_sx) अणु
		पूर्णांक i = 0;

		/* Poll up to 5 seconds क्रम Cable Disconnected indication */
		जबतक (!(er32(FEXT) & E1000_FEXT_PHY_CABLE_DISCONNECTED)) अणु
			/* Bail अगर link is re-acquired */
			अगर (er32(STATUS) & E1000_STATUS_LU)
				वापस -E1000_ERR_PHY;

			अगर (i++ == 100)
				अवरोध;

			msleep(50);
		पूर्ण
		e_dbg("CABLE_DISCONNECTED %s set after %dmsec\n",
		      (er32(FEXT) &
		       E1000_FEXT_PHY_CABLE_DISCONNECTED) ? "" : "not", i * 50);
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	/* Force SMBus mode in PHY */
	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, CV_SMB_CTRL, &phy_reg);
	अगर (ret_val)
		जाओ release;
	phy_reg |= CV_SMB_CTRL_FORCE_SMBUS;
	e1000_ग_लिखो_phy_reg_hv_locked(hw, CV_SMB_CTRL, phy_reg);

	/* Force SMBus mode in MAC */
	mac_reg = er32(CTRL_EXT);
	mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
	ew32(CTRL_EXT, mac_reg);

	/* Si workaround क्रम ULP entry flow on i127/rev6 h/w.  Enable
	 * LPLU and disable Gig speed when entering ULP
	 */
	अगर ((hw->phy.type == e1000_phy_i217) && (hw->phy.revision == 6)) अणु
		ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, HV_OEM_BITS,
						       &oem_reg);
		अगर (ret_val)
			जाओ release;

		phy_reg = oem_reg;
		phy_reg |= HV_OEM_BITS_LPLU | HV_OEM_BITS_GBE_DIS;

		ret_val = e1000_ग_लिखो_phy_reg_hv_locked(hw, HV_OEM_BITS,
							phy_reg);

		अगर (ret_val)
			जाओ release;
	पूर्ण

	/* Set Inband ULP Exit, Reset to SMBus mode and
	 * Disable SMBus Release on PERST# in PHY
	 */
	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, &phy_reg);
	अगर (ret_val)
		जाओ release;
	phy_reg |= (I218_ULP_CONFIG1_RESET_TO_SMBUS |
		    I218_ULP_CONFIG1_DISABLE_SMB_PERST);
	अगर (to_sx) अणु
		अगर (er32(WUFC) & E1000_WUFC_LNKC)
			phy_reg |= I218_ULP_CONFIG1_WOL_HOST;
		अन्यथा
			phy_reg &= ~I218_ULP_CONFIG1_WOL_HOST;

		phy_reg |= I218_ULP_CONFIG1_STICKY_ULP;
		phy_reg &= ~I218_ULP_CONFIG1_INBAND_EXIT;
	पूर्ण अन्यथा अणु
		phy_reg |= I218_ULP_CONFIG1_INBAND_EXIT;
		phy_reg &= ~I218_ULP_CONFIG1_STICKY_ULP;
		phy_reg &= ~I218_ULP_CONFIG1_WOL_HOST;
	पूर्ण
	e1000_ग_लिखो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	/* Set Disable SMBus Release on PERST# in MAC */
	mac_reg = er32(FEXTNVM7);
	mac_reg |= E1000_FEXTNVM7_DISABLE_SMB_PERST;
	ew32(FEXTNVM7, mac_reg);

	/* Commit ULP changes in PHY by starting स्वतः ULP configuration */
	phy_reg |= I218_ULP_CONFIG1_START;
	e1000_ग_लिखो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	अगर ((hw->phy.type == e1000_phy_i217) && (hw->phy.revision == 6) &&
	    to_sx && (er32(STATUS) & E1000_STATUS_LU)) अणु
		ret_val = e1000_ग_लिखो_phy_reg_hv_locked(hw, HV_OEM_BITS,
							oem_reg);
		अगर (ret_val)
			जाओ release;
	पूर्ण

release:
	hw->phy.ops.release(hw);
out:
	अगर (ret_val)
		e_dbg("Error in ULP enable flow: %d\n", ret_val);
	अन्यथा
		hw->dev_spec.ich8lan.ulp_state = e1000_ulp_state_on;

	वापस ret_val;
पूर्ण

/**
 *  e1000_disable_ulp_lpt_lp - unconfigure Ultra Low Power mode क्रम LynxPoपूर्णांक-LP
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @क्रमce: boolean indicating whether or not to क्रमce disabling ULP
 *
 *  Un-configure ULP mode when link is up, the प्रणाली is transitioned from
 *  Sx or the driver is unloaded.  If on a Manageability Engine (ME) enabled
 *  प्रणाली, poll क्रम an indication from ME that ULP has been un-configured.
 *  If not on an ME enabled प्रणाली, un-configure the ULP mode by software.
 *
 *  During nominal operation, this function is called when link is acquired
 *  to disable ULP mode (क्रमce=false); otherwise, क्रम example when unloading
 *  the driver or during Sx->S0 transitions, this is called with क्रमce=true
 *  to क्रमcibly disable ULP.
 */
अटल s32 e1000_disable_ulp_lpt_lp(काष्ठा e1000_hw *hw, bool क्रमce)
अणु
	s32 ret_val = 0;
	u32 mac_reg;
	u16 phy_reg;
	पूर्णांक i = 0;

	अगर ((hw->mac.type < e1000_pch_lpt) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPT_I217_LM) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPT_I217_V) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_LM2) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_V2) ||
	    (hw->dev_spec.ich8lan.ulp_state == e1000_ulp_state_off))
		वापस 0;

	अगर (er32(FWSM) & E1000_ICH_FWSM_FW_VALID) अणु
		काष्ठा e1000_adapter *adapter = hw->adapter;
		bool firmware_bug = false;

		अगर (क्रमce) अणु
			/* Request ME un-configure ULP mode in the PHY */
			mac_reg = er32(H2ME);
			mac_reg &= ~E1000_H2ME_ULP;
			mac_reg |= E1000_H2ME_ENFORCE_SETTINGS;
			ew32(H2ME, mac_reg);
		पूर्ण

		/* Poll up to 2.5 seconds क्रम ME to clear ULP_CFG_DONE.
		 * If this takes more than 1 second, show a warning indicating a
		 * firmware bug
		 */
		जबतक (er32(FWSM) & E1000_FWSM_ULP_CFG_DONE) अणु
			अगर (i++ == 250) अणु
				ret_val = -E1000_ERR_PHY;
				जाओ out;
			पूर्ण
			अगर (i > 100 && !firmware_bug)
				firmware_bug = true;

			usleep_range(10000, 11000);
		पूर्ण
		अगर (firmware_bug)
			e_warn("ULP_CONFIG_DONE took %dmsec.  This is a firmware bug\n", i * 10);
		अन्यथा
			e_dbg("ULP_CONFIG_DONE cleared after %dmsec\n", i * 10);

		अगर (क्रमce) अणु
			mac_reg = er32(H2ME);
			mac_reg &= ~E1000_H2ME_ENFORCE_SETTINGS;
			ew32(H2ME, mac_reg);
		पूर्ण अन्यथा अणु
			/* Clear H2ME.ULP after ME ULP configuration */
			mac_reg = er32(H2ME);
			mac_reg &= ~E1000_H2ME_ULP;
			ew32(H2ME, mac_reg);
		पूर्ण

		जाओ out;
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	अगर (क्रमce)
		/* Toggle LANPHYPC Value bit */
		e1000_toggle_lanphypc_pch_lpt(hw);

	/* Unक्रमce SMBus mode in PHY */
	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, CV_SMB_CTRL, &phy_reg);
	अगर (ret_val) अणु
		/* The MAC might be in PCIe mode, so temporarily क्रमce to
		 * SMBus mode in order to access the PHY.
		 */
		mac_reg = er32(CTRL_EXT);
		mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
		ew32(CTRL_EXT, mac_reg);

		msleep(50);

		ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, CV_SMB_CTRL,
						       &phy_reg);
		अगर (ret_val)
			जाओ release;
	पूर्ण
	phy_reg &= ~CV_SMB_CTRL_FORCE_SMBUS;
	e1000_ग_लिखो_phy_reg_hv_locked(hw, CV_SMB_CTRL, phy_reg);

	/* Unक्रमce SMBus mode in MAC */
	mac_reg = er32(CTRL_EXT);
	mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
	ew32(CTRL_EXT, mac_reg);

	/* When ULP mode was previously entered, K1 was disabled by the
	 * hardware.  Re-Enable K1 in the PHY when निकासing ULP.
	 */
	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, HV_PM_CTRL, &phy_reg);
	अगर (ret_val)
		जाओ release;
	phy_reg |= HV_PM_CTRL_K1_ENABLE;
	e1000_ग_लिखो_phy_reg_hv_locked(hw, HV_PM_CTRL, phy_reg);

	/* Clear ULP enabled configuration */
	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, &phy_reg);
	अगर (ret_val)
		जाओ release;
	phy_reg &= ~(I218_ULP_CONFIG1_IND |
		     I218_ULP_CONFIG1_STICKY_ULP |
		     I218_ULP_CONFIG1_RESET_TO_SMBUS |
		     I218_ULP_CONFIG1_WOL_HOST |
		     I218_ULP_CONFIG1_INBAND_EXIT |
		     I218_ULP_CONFIG1_EN_ULP_LANPHYPC |
		     I218_ULP_CONFIG1_DIS_CLR_STICKY_ON_PERST |
		     I218_ULP_CONFIG1_DISABLE_SMB_PERST);
	e1000_ग_लिखो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	/* Commit ULP changes by starting स्वतः ULP configuration */
	phy_reg |= I218_ULP_CONFIG1_START;
	e1000_ग_लिखो_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	/* Clear Disable SMBus Release on PERST# in MAC */
	mac_reg = er32(FEXTNVM7);
	mac_reg &= ~E1000_FEXTNVM7_DISABLE_SMB_PERST;
	ew32(FEXTNVM7, mac_reg);

release:
	hw->phy.ops.release(hw);
	अगर (क्रमce) अणु
		e1000_phy_hw_reset(hw);
		msleep(50);
	पूर्ण
out:
	अगर (ret_val)
		e_dbg("Error in ULP disable flow: %d\n", ret_val);
	अन्यथा
		hw->dev_spec.ich8lan.ulp_state = e1000_ulp_state_off;

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_क्रम_copper_link_ich8lan - Check क्रम link (Copper)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks to see of the link status of the hardware has changed.  If a
 *  change in link status has been detected, then we पढ़ो the PHY रेजिस्टरs
 *  to get the current speed/duplex अगर link exists.
 **/
अटल s32 e1000_check_क्रम_copper_link_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val, tipg_reg = 0;
	u16 emi_addr, emi_val = 0;
	bool link;
	u16 phy_reg;

	/* We only want to go out to the PHY रेजिस्टरs to see अगर Auto-Neg
	 * has completed and/or अगर our link status has changed.  The
	 * get_link_status flag is set upon receiving a Link Status
	 * Change or Rx Sequence Error पूर्णांकerrupt.
	 */
	अगर (!mac->get_link_status)
		वापस 0;
	mac->get_link_status = false;

	/* First we want to see अगर the MII Status Register reports
	 * link.  If so, then we want to get the current speed/duplex
	 * of the PHY.
	 */
	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (hw->mac.type == e1000_pchlan) अणु
		ret_val = e1000_k1_gig_workaround_hv(hw, link);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	/* When connected at 10Mbps half-duplex, some parts are excessively
	 * aggressive resulting in many collisions. To aव्योम this, increase
	 * the IPG and reduce Rx latency in the PHY.
	 */
	अगर ((hw->mac.type >= e1000_pch2lan) && link) अणु
		u16 speed, duplex;

		e1000e_get_speed_and_duplex_copper(hw, &speed, &duplex);
		tipg_reg = er32(TIPG);
		tipg_reg &= ~E1000_TIPG_IPGT_MASK;

		अगर (duplex == HALF_DUPLEX && speed == SPEED_10) अणु
			tipg_reg |= 0xFF;
			/* Reduce Rx latency in analog PHY */
			emi_val = 0;
		पूर्ण अन्यथा अगर (hw->mac.type >= e1000_pch_spt &&
			   duplex == FULL_DUPLEX && speed != SPEED_1000) अणु
			tipg_reg |= 0xC;
			emi_val = 1;
		पूर्ण अन्यथा अणु

			/* Roll back the शेष values */
			tipg_reg |= 0x08;
			emi_val = 1;
		पूर्ण

		ew32(TIPG, tipg_reg);

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			जाओ out;

		अगर (hw->mac.type == e1000_pch2lan)
			emi_addr = I82579_RX_CONFIG;
		अन्यथा
			emi_addr = I217_RX_CONFIG;
		ret_val = e1000_ग_लिखो_emi_reg_locked(hw, emi_addr, emi_val);

		अगर (hw->mac.type >= e1000_pch_lpt) अणु
			u16 phy_reg;

			e1e_rphy_locked(hw, I217_PLL_CLOCK_GATE_REG, &phy_reg);
			phy_reg &= ~I217_PLL_CLOCK_GATE_MASK;
			अगर (speed == SPEED_100 || speed == SPEED_10)
				phy_reg |= 0x3E8;
			अन्यथा
				phy_reg |= 0xFA;
			e1e_wphy_locked(hw, I217_PLL_CLOCK_GATE_REG, phy_reg);

			अगर (speed == SPEED_1000) अणु
				hw->phy.ops.पढ़ो_reg_locked(hw, HV_PM_CTRL,
							    &phy_reg);

				phy_reg |= HV_PM_CTRL_K1_CLK_REQ;

				hw->phy.ops.ग_लिखो_reg_locked(hw, HV_PM_CTRL,
							     phy_reg);
			पूर्ण
		पूर्ण
		hw->phy.ops.release(hw);

		अगर (ret_val)
			जाओ out;

		अगर (hw->mac.type >= e1000_pch_spt) अणु
			u16 data;
			u16 ptr_gap;

			अगर (speed == SPEED_1000) अणु
				ret_val = hw->phy.ops.acquire(hw);
				अगर (ret_val)
					जाओ out;

				ret_val = e1e_rphy_locked(hw,
							  PHY_REG(776, 20),
							  &data);
				अगर (ret_val) अणु
					hw->phy.ops.release(hw);
					जाओ out;
				पूर्ण

				ptr_gap = (data & (0x3FF << 2)) >> 2;
				अगर (ptr_gap < 0x18) अणु
					data &= ~(0x3FF << 2);
					data |= (0x18 << 2);
					ret_val =
					    e1e_wphy_locked(hw,
							    PHY_REG(776, 20),
							    data);
				पूर्ण
				hw->phy.ops.release(hw);
				अगर (ret_val)
					जाओ out;
			पूर्ण अन्यथा अणु
				ret_val = hw->phy.ops.acquire(hw);
				अगर (ret_val)
					जाओ out;

				ret_val = e1e_wphy_locked(hw,
							  PHY_REG(776, 20),
							  0xC023);
				hw->phy.ops.release(hw);
				अगर (ret_val)
					जाओ out;

			पूर्ण
		पूर्ण
	पूर्ण

	/* I217 Packet Loss issue:
	 * ensure that FEXTNVM4 Beacon Duration is set correctly
	 * on घातer up.
	 * Set the Beacon Duration क्रम I217 to 8 usec
	 */
	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		u32 mac_reg;

		mac_reg = er32(FEXTNVM4);
		mac_reg &= ~E1000_FEXTNVM4_BEACON_DURATION_MASK;
		mac_reg |= E1000_FEXTNVM4_BEACON_DURATION_8USEC;
		ew32(FEXTNVM4, mac_reg);
	पूर्ण

	/* Work-around I218 hang issue */
	अगर ((hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPTLP_I218_LM) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_LPTLP_I218_V) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_LM3) ||
	    (hw->adapter->pdev->device == E1000_DEV_ID_PCH_I218_V3)) अणु
		ret_val = e1000_k1_workaround_lpt_lp(hw, link);
		अगर (ret_val)
			जाओ out;
	पूर्ण
	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		/* Set platक्रमm घातer management values क्रम
		 * Latency Tolerance Reporting (LTR)
		 */
		ret_val = e1000_platक्रमm_pm_pch_lpt(hw, link);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	/* Clear link partner's EEE ability */
	hw->dev_spec.ich8lan.eee_lp_ability = 0;

	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		u32 fextnvm6 = er32(FEXTNVM6);

		अगर (hw->mac.type == e1000_pch_spt) अणु
			/* FEXTNVM6 K1-off workaround - क्रम SPT only */
			u32 pcieanacfg = er32(PCIEANACFG);

			अगर (pcieanacfg & E1000_FEXTNVM6_K1_OFF_ENABLE)
				fextnvm6 |= E1000_FEXTNVM6_K1_OFF_ENABLE;
			अन्यथा
				fextnvm6 &= ~E1000_FEXTNVM6_K1_OFF_ENABLE;
		पूर्ण

		ew32(FEXTNVM6, fextnvm6);
	पूर्ण

	अगर (!link)
		जाओ out;

	चयन (hw->mac.type) अणु
	हाल e1000_pch2lan:
		ret_val = e1000_k1_workaround_lv(hw);
		अगर (ret_val)
			वापस ret_val;
		fallthrough;
	हाल e1000_pchlan:
		अगर (hw->phy.type == e1000_phy_82578) अणु
			ret_val = e1000_link_stall_workaround_hv(hw);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		/* Workaround क्रम PCHx parts in half-duplex:
		 * Set the number of preambles हटाओd from the packet
		 * when it is passed from the PHY to the MAC to prevent
		 * the MAC from misपूर्णांकerpreting the packet type.
		 */
		e1e_rphy(hw, HV_KMRN_FIFO_CTRLSTA, &phy_reg);
		phy_reg &= ~HV_KMRN_FIFO_CTRLSTA_PREAMBLE_MASK;

		अगर ((er32(STATUS) & E1000_STATUS_FD) != E1000_STATUS_FD)
			phy_reg |= BIT(HV_KMRN_FIFO_CTRLSTA_PREAMBLE_SHIFT);

		e1e_wphy(hw, HV_KMRN_FIFO_CTRLSTA, phy_reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Check अगर there was DownShअगरt, must be checked
	 * immediately after link-up
	 */
	e1000e_check_करोwnshअगरt(hw);

	/* Enable/Disable EEE after link up */
	अगर (hw->phy.type > e1000_phy_82579) अणु
		ret_val = e1000_set_eee_pchlan(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* If we are क्रमcing speed/duplex, then we simply वापस since
	 * we have alपढ़ोy determined whether we have link or not.
	 */
	अगर (!mac->स्वतःneg)
		वापस -E1000_ERR_CONFIG;

	/* Auto-Neg is enabled.  Auto Speed Detection takes care
	 * of MAC speed/duplex configuration.  So we only need to
	 * configure Collision Distance in the MAC.
	 */
	mac->ops.config_collision_dist(hw);

	/* Configure Flow Control now that Auto-Neg has completed.
	 * First, we need to restore the desired flow control
	 * settings because we may have had to re-स्वतःneg with a
	 * dअगरferent link partner.
	 */
	ret_val = e1000e_config_fc_after_link_up(hw);
	अगर (ret_val)
		e_dbg("Error configuring flow control\n");

	वापस ret_val;

out:
	mac->get_link_status = true;
	वापस ret_val;
पूर्ण

अटल s32 e1000_get_variants_ich8lan(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 rc;

	rc = e1000_init_mac_params_ich8lan(hw);
	अगर (rc)
		वापस rc;

	rc = e1000_init_nvm_params_ich8lan(hw);
	अगर (rc)
		वापस rc;

	चयन (hw->mac.type) अणु
	हाल e1000_ich8lan:
	हाल e1000_ich9lan:
	हाल e1000_ich10lan:
		rc = e1000_init_phy_params_ich8lan(hw);
		अवरोध;
	हाल e1000_pchlan:
	हाल e1000_pch2lan:
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		rc = e1000_init_phy_params_pchlan(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (rc)
		वापस rc;

	/* Disable Jumbo Frame support on parts with Intel 10/100 PHY or
	 * on parts with MACsec enabled in NVM (reflected in CTRL_EXT).
	 */
	अगर ((adapter->hw.phy.type == e1000_phy_अगरe) ||
	    ((adapter->hw.mac.type >= e1000_pch2lan) &&
	     (!(er32(CTRL_EXT) & E1000_CTRL_EXT_LSECCK)))) अणु
		adapter->flags &= ~FLAG_HAS_JUMBO_FRAMES;
		adapter->max_hw_frame_size = VLAN_ETH_FRAME_LEN + ETH_FCS_LEN;

		hw->mac.ops.blink_led = शून्य;
	पूर्ण

	अगर ((adapter->hw.mac.type == e1000_ich8lan) &&
	    (adapter->hw.phy.type != e1000_phy_अगरe))
		adapter->flags |= FLAG_LSC_GIG_SPEED_DROP;

	/* Enable workaround क्रम 82579 w/ ME enabled */
	अगर ((adapter->hw.mac.type == e1000_pch2lan) &&
	    (er32(FWSM) & E1000_ICH_FWSM_FW_VALID))
		adapter->flags2 |= FLAG2_PCIM2PCI_ARBITER_WA;

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(nvm_mutex);

/**
 *  e1000_acquire_nvm_ich8lan - Acquire NVM mutex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquires the mutex क्रम perक्रमming NVM operations.
 **/
अटल s32 e1000_acquire_nvm_ich8lan(काष्ठा e1000_hw __always_unused *hw)
अणु
	mutex_lock(&nvm_mutex);

	वापस 0;
पूर्ण

/**
 *  e1000_release_nvm_ich8lan - Release NVM mutex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Releases the mutex used जबतक perक्रमming NVM operations.
 **/
अटल व्योम e1000_release_nvm_ich8lan(काष्ठा e1000_hw __always_unused *hw)
अणु
	mutex_unlock(&nvm_mutex);
पूर्ण

/**
 *  e1000_acquire_swflag_ich8lan - Acquire software control flag
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquires the software control flag क्रम perक्रमming PHY and select
 *  MAC CSR accesses.
 **/
अटल s32 e1000_acquire_swflag_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 extcnf_ctrl, समयout = PHY_CFG_TIMEOUT;
	s32 ret_val = 0;

	अगर (test_and_set_bit(__E1000_ACCESS_SHARED_RESOURCE,
			     &hw->adapter->state)) अणु
		e_dbg("contention for Phy access\n");
		वापस -E1000_ERR_PHY;
	पूर्ण

	जबतक (समयout) अणु
		extcnf_ctrl = er32(EXTCNF_CTRL);
		अगर (!(extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG))
			अवरोध;

		mdelay(1);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		e_dbg("SW has already locked the resource.\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	समयout = SW_FLAG_TIMEOUT;

	extcnf_ctrl |= E1000_EXTCNF_CTRL_SWFLAG;
	ew32(EXTCNF_CTRL, extcnf_ctrl);

	जबतक (समयout) अणु
		extcnf_ctrl = er32(EXTCNF_CTRL);
		अगर (extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG)
			अवरोध;

		mdelay(1);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		e_dbg("Failed to acquire the semaphore, FW or HW has it: FWSM=0x%8.8x EXTCNF_CTRL=0x%8.8x)\n",
		      er32(FWSM), extcnf_ctrl);
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_SWFLAG;
		ew32(EXTCNF_CTRL, extcnf_ctrl);
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

out:
	अगर (ret_val)
		clear_bit(__E1000_ACCESS_SHARED_RESOURCE, &hw->adapter->state);

	वापस ret_val;
पूर्ण

/**
 *  e1000_release_swflag_ich8lan - Release software control flag
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Releases the software control flag क्रम perक्रमming PHY and select
 *  MAC CSR accesses.
 **/
अटल व्योम e1000_release_swflag_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 extcnf_ctrl;

	extcnf_ctrl = er32(EXTCNF_CTRL);

	अगर (extcnf_ctrl & E1000_EXTCNF_CTRL_SWFLAG) अणु
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_SWFLAG;
		ew32(EXTCNF_CTRL, extcnf_ctrl);
	पूर्ण अन्यथा अणु
		e_dbg("Semaphore unexpectedly released by sw/fw/hw\n");
	पूर्ण

	clear_bit(__E1000_ACCESS_SHARED_RESOURCE, &hw->adapter->state);
पूर्ण

/**
 *  e1000_check_mng_mode_ich8lan - Checks management mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This checks अगर the adapter has any manageability enabled.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by पढ़ो/ग_लिखो
 *  routines क्रम the PHY and NVM parts.
 **/
अटल bool e1000_check_mng_mode_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 fwsm;

	fwsm = er32(FWSM);
	वापस (fwsm & E1000_ICH_FWSM_FW_VALID) &&
		((fwsm & E1000_FWSM_MODE_MASK) ==
		 (E1000_ICH_MNG_IAMT_MODE << E1000_FWSM_MODE_SHIFT));
पूर्ण

/**
 *  e1000_check_mng_mode_pchlan - Checks management mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This checks अगर the adapter has iAMT enabled.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by पढ़ो/ग_लिखो
 *  routines क्रम the PHY and NVM parts.
 **/
अटल bool e1000_check_mng_mode_pchlan(काष्ठा e1000_hw *hw)
अणु
	u32 fwsm;

	fwsm = er32(FWSM);
	वापस (fwsm & E1000_ICH_FWSM_FW_VALID) &&
	    (fwsm & (E1000_ICH_MNG_IAMT_MODE << E1000_FWSM_MODE_SHIFT));
पूर्ण

/**
 *  e1000_rar_set_pch2lan - Set receive address रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: poपूर्णांकer to the receive address
 *  @index: receive address array रेजिस्टर
 *
 *  Sets the receive address array रेजिस्टर at index to the address passed
 *  in by addr.  For 82579, RAR[0] is the base address रेजिस्टर that is to
 *  contain the MAC address but RAR[1-6] are reserved क्रम manageability (ME).
 *  Use SHRA[0-3] in place of those reserved क्रम ME.
 **/
अटल पूर्णांक e1000_rar_set_pch2lan(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
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
		rar_high |= E1000_RAH_AV;

	अगर (index == 0) अणु
		ew32(RAL(index), rar_low);
		e1e_flush();
		ew32(RAH(index), rar_high);
		e1e_flush();
		वापस 0;
	पूर्ण

	/* RAR[1-6] are owned by manageability.  Skip those and program the
	 * next address पूर्णांकo the SHRA रेजिस्टर array.
	 */
	अगर (index < (u32)(hw->mac.rar_entry_count)) अणु
		s32 ret_val;

		ret_val = e1000_acquire_swflag_ich8lan(hw);
		अगर (ret_val)
			जाओ out;

		ew32(SHRAL(index - 1), rar_low);
		e1e_flush();
		ew32(SHRAH(index - 1), rar_high);
		e1e_flush();

		e1000_release_swflag_ich8lan(hw);

		/* verअगरy the रेजिस्टर updates */
		अगर ((er32(SHRAL(index - 1)) == rar_low) &&
		    (er32(SHRAH(index - 1)) == rar_high))
			वापस 0;

		e_dbg("SHRA[%d] might be locked by ME - FWSM=0x%8.8x\n",
		      (index - 1), er32(FWSM));
	पूर्ण

out:
	e_dbg("Failed to write receive address at index %d\n", index);
	वापस -E1000_ERR_CONFIG;
पूर्ण

/**
 *  e1000_rar_get_count_pch_lpt - Get the number of available SHRA
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Get the number of available receive रेजिस्टरs that the Host can
 *  program. SHRA[0-10] are the shared receive address रेजिस्टरs
 *  that are shared between the Host and manageability engine (ME).
 *  ME can reserve any number of addresses and the host needs to be
 *  able to tell how many available रेजिस्टरs it has access to.
 **/
अटल u32 e1000_rar_get_count_pch_lpt(काष्ठा e1000_hw *hw)
अणु
	u32 wlock_mac;
	u32 num_entries;

	wlock_mac = er32(FWSM) & E1000_FWSM_WLOCK_MAC_MASK;
	wlock_mac >>= E1000_FWSM_WLOCK_MAC_SHIFT;

	चयन (wlock_mac) अणु
	हाल 0:
		/* All SHRA[0..10] and RAR[0] available */
		num_entries = hw->mac.rar_entry_count;
		अवरोध;
	हाल 1:
		/* Only RAR[0] available */
		num_entries = 1;
		अवरोध;
	शेष:
		/* SHRA[0..(wlock_mac - 1)] available + RAR[0] */
		num_entries = wlock_mac + 1;
		अवरोध;
	पूर्ण

	वापस num_entries;
पूर्ण

/**
 *  e1000_rar_set_pch_lpt - Set receive address रेजिस्टरs
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: poपूर्णांकer to the receive address
 *  @index: receive address array रेजिस्टर
 *
 *  Sets the receive address रेजिस्टर array at index to the address passed
 *  in by addr. For LPT, RAR[0] is the base address रेजिस्टर that is to
 *  contain the MAC address. SHRA[0-10] are the shared receive address
 *  रेजिस्टरs that are shared between the Host and manageability engine (ME).
 **/
अटल पूर्णांक e1000_rar_set_pch_lpt(काष्ठा e1000_hw *hw, u8 *addr, u32 index)
अणु
	u32 rar_low, rar_high;
	u32 wlock_mac;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] | ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) | ((u32)addr[3] << 24));

	rar_high = ((u32)addr[4] | ((u32)addr[5] << 8));

	/* If MAC address zero, no need to set the AV bit */
	अगर (rar_low || rar_high)
		rar_high |= E1000_RAH_AV;

	अगर (index == 0) अणु
		ew32(RAL(index), rar_low);
		e1e_flush();
		ew32(RAH(index), rar_high);
		e1e_flush();
		वापस 0;
	पूर्ण

	/* The manageability engine (ME) can lock certain SHRAR रेजिस्टरs that
	 * it is using - those रेजिस्टरs are unavailable क्रम use.
	 */
	अगर (index < hw->mac.rar_entry_count) अणु
		wlock_mac = er32(FWSM) & E1000_FWSM_WLOCK_MAC_MASK;
		wlock_mac >>= E1000_FWSM_WLOCK_MAC_SHIFT;

		/* Check अगर all SHRAR रेजिस्टरs are locked */
		अगर (wlock_mac == 1)
			जाओ out;

		अगर ((wlock_mac == 0) || (index <= wlock_mac)) अणु
			s32 ret_val;

			ret_val = e1000_acquire_swflag_ich8lan(hw);

			अगर (ret_val)
				जाओ out;

			ew32(SHRAL_PCH_LPT(index - 1), rar_low);
			e1e_flush();
			ew32(SHRAH_PCH_LPT(index - 1), rar_high);
			e1e_flush();

			e1000_release_swflag_ich8lan(hw);

			/* verअगरy the रेजिस्टर updates */
			अगर ((er32(SHRAL_PCH_LPT(index - 1)) == rar_low) &&
			    (er32(SHRAH_PCH_LPT(index - 1)) == rar_high))
				वापस 0;
		पूर्ण
	पूर्ण

out:
	e_dbg("Failed to write receive address at index %d\n", index);
	वापस -E1000_ERR_CONFIG;
पूर्ण

/**
 *  e1000_check_reset_block_ich8lan - Check अगर PHY reset is blocked
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Checks अगर firmware is blocking the reset of the PHY.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  reset routines.
 **/
अटल s32 e1000_check_reset_block_ich8lan(काष्ठा e1000_hw *hw)
अणु
	bool blocked = false;
	पूर्णांक i = 0;

	जबतक ((blocked = !(er32(FWSM) & E1000_ICH_FWSM_RSPCIPHY)) &&
	       (i++ < 30))
		usleep_range(10000, 11000);
	वापस blocked ? E1000_BLK_PHY_RESET : 0;
पूर्ण

/**
 *  e1000_ग_लिखो_smbus_addr - Write SMBus address to PHY needed during Sx states
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Assumes semaphore alपढ़ोy acquired.
 *
 **/
अटल s32 e1000_ग_लिखो_smbus_addr(काष्ठा e1000_hw *hw)
अणु
	u16 phy_data;
	u32 strap = er32(STRAP);
	u32 freq = (strap & E1000_STRAP_SMT_FREQ_MASK) >>
	    E1000_STRAP_SMT_FREQ_SHIFT;
	s32 ret_val;

	strap &= E1000_STRAP_SMBUS_ADDRESS_MASK;

	ret_val = e1000_पढ़ो_phy_reg_hv_locked(hw, HV_SMB_ADDR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data &= ~HV_SMB_ADDR_MASK;
	phy_data |= (strap >> E1000_STRAP_SMBUS_ADDRESS_SHIFT);
	phy_data |= HV_SMB_ADDR_PEC_EN | HV_SMB_ADDR_VALID;

	अगर (hw->phy.type == e1000_phy_i217) अणु
		/* Restore SMBus frequency */
		अगर (freq--) अणु
			phy_data &= ~HV_SMB_ADDR_FREQ_MASK;
			phy_data |= (freq & BIT(0)) <<
			    HV_SMB_ADDR_FREQ_LOW_SHIFT;
			phy_data |= (freq & BIT(1)) <<
			    (HV_SMB_ADDR_FREQ_HIGH_SHIFT - 1);
		पूर्ण अन्यथा अणु
			e_dbg("Unsupported SMB frequency in PHY\n");
		पूर्ण
	पूर्ण

	वापस e1000_ग_लिखो_phy_reg_hv_locked(hw, HV_SMB_ADDR, phy_data);
पूर्ण

/**
 *  e1000_sw_lcd_config_ich8lan - SW-based LCD Configuration
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 *
 *  SW should configure the LCD from the NVM extended configuration region
 *  as a workaround क्रम certain parts.
 **/
अटल s32 e1000_sw_lcd_config_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, data, cnf_size, cnf_base_addr, sw_cfg_mask;
	s32 ret_val = 0;
	u16 word_addr, reg_data, reg_addr, phy_page = 0;

	/* Initialize the PHY from the NVM on ICH platक्रमms.  This
	 * is needed due to an issue where the NVM configuration is
	 * not properly स्वतःloaded after घातer transitions.
	 * Thereक्रमe, after each PHY reset, we will load the
	 * configuration data out of the NVM manually.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_ich8lan:
		अगर (phy->type != e1000_phy_igp_3)
			वापस ret_val;

		अगर ((hw->adapter->pdev->device == E1000_DEV_ID_ICH8_IGP_AMT) ||
		    (hw->adapter->pdev->device == E1000_DEV_ID_ICH8_IGP_C)) अणु
			sw_cfg_mask = E1000_FEXTNVM_SW_CONFIG;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल e1000_pchlan:
	हाल e1000_pch2lan:
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		sw_cfg_mask = E1000_FEXTNVM_SW_CONFIG_ICH8M;
		अवरोध;
	शेष:
		वापस ret_val;
	पूर्ण

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	data = er32(FEXTNVM);
	अगर (!(data & sw_cfg_mask))
		जाओ release;

	/* Make sure HW करोes not configure LCD from PHY
	 * extended configuration beक्रमe SW configuration
	 */
	data = er32(EXTCNF_CTRL);
	अगर ((hw->mac.type < e1000_pch2lan) &&
	    (data & E1000_EXTCNF_CTRL_LCD_WRITE_ENABLE))
		जाओ release;

	cnf_size = er32(EXTCNF_SIZE);
	cnf_size &= E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_MASK;
	cnf_size >>= E1000_EXTCNF_SIZE_EXT_PCIE_LENGTH_SHIFT;
	अगर (!cnf_size)
		जाओ release;

	cnf_base_addr = data & E1000_EXTCNF_CTRL_EXT_CNF_POINTER_MASK;
	cnf_base_addr >>= E1000_EXTCNF_CTRL_EXT_CNF_POINTER_SHIFT;

	अगर (((hw->mac.type == e1000_pchlan) &&
	     !(data & E1000_EXTCNF_CTRL_OEM_WRITE_ENABLE)) ||
	    (hw->mac.type > e1000_pchlan)) अणु
		/* HW configures the SMBus address and LEDs when the
		 * OEM and LCD Write Enable bits are set in the NVM.
		 * When both NVM bits are cleared, SW will configure
		 * them instead.
		 */
		ret_val = e1000_ग_लिखो_smbus_addr(hw);
		अगर (ret_val)
			जाओ release;

		data = er32(LEDCTL);
		ret_val = e1000_ग_लिखो_phy_reg_hv_locked(hw, HV_LED_CONFIG,
							(u16)data);
		अगर (ret_val)
			जाओ release;
	पूर्ण

	/* Configure LCD from extended configuration region. */

	/* cnf_base_addr is in DWORD */
	word_addr = (u16)(cnf_base_addr << 1);

	क्रम (i = 0; i < cnf_size; i++) अणु
		ret_val = e1000_पढ़ो_nvm(hw, (word_addr + i * 2), 1, &reg_data);
		अगर (ret_val)
			जाओ release;

		ret_val = e1000_पढ़ो_nvm(hw, (word_addr + i * 2 + 1),
					 1, &reg_addr);
		अगर (ret_val)
			जाओ release;

		/* Save off the PHY page क्रम future ग_लिखोs. */
		अगर (reg_addr == IGP01E1000_PHY_PAGE_SELECT) अणु
			phy_page = reg_data;
			जारी;
		पूर्ण

		reg_addr &= PHY_REG_MASK;
		reg_addr |= phy_page;

		ret_val = e1e_wphy_locked(hw, (u32)reg_addr, reg_data);
		अगर (ret_val)
			जाओ release;
	पूर्ण

release:
	hw->phy.ops.release(hw);
	वापस ret_val;
पूर्ण

/**
 *  e1000_k1_gig_workaround_hv - K1 Si workaround
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 *  @link: link up bool flag
 *
 *  If K1 is enabled क्रम 1Gbps, the MAC might stall when transitioning
 *  from a lower speed.  This workaround disables K1 whenever link is at 1Gig
 *  If link is करोwn, the function will restore the शेष K1 setting located
 *  in the NVM.
 **/
अटल s32 e1000_k1_gig_workaround_hv(काष्ठा e1000_hw *hw, bool link)
अणु
	s32 ret_val = 0;
	u16 status_reg = 0;
	bool k1_enable = hw->dev_spec.ich8lan.nvm_k1_enabled;

	अगर (hw->mac.type != e1000_pchlan)
		वापस 0;

	/* Wrap the whole flow with the sw flag */
	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Disable K1 when link is 1Gbps, otherwise use the NVM setting */
	अगर (link) अणु
		अगर (hw->phy.type == e1000_phy_82578) अणु
			ret_val = e1e_rphy_locked(hw, BM_CS_STATUS,
						  &status_reg);
			अगर (ret_val)
				जाओ release;

			status_reg &= (BM_CS_STATUS_LINK_UP |
				       BM_CS_STATUS_RESOLVED |
				       BM_CS_STATUS_SPEED_MASK);

			अगर (status_reg == (BM_CS_STATUS_LINK_UP |
					   BM_CS_STATUS_RESOLVED |
					   BM_CS_STATUS_SPEED_1000))
				k1_enable = false;
		पूर्ण

		अगर (hw->phy.type == e1000_phy_82577) अणु
			ret_val = e1e_rphy_locked(hw, HV_M_STATUS, &status_reg);
			अगर (ret_val)
				जाओ release;

			status_reg &= (HV_M_STATUS_LINK_UP |
				       HV_M_STATUS_AUTONEG_COMPLETE |
				       HV_M_STATUS_SPEED_MASK);

			अगर (status_reg == (HV_M_STATUS_LINK_UP |
					   HV_M_STATUS_AUTONEG_COMPLETE |
					   HV_M_STATUS_SPEED_1000))
				k1_enable = false;
		पूर्ण

		/* Link stall fix क्रम link up */
		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x0100);
		अगर (ret_val)
			जाओ release;

	पूर्ण अन्यथा अणु
		/* Link stall fix क्रम link करोwn */
		ret_val = e1e_wphy_locked(hw, PHY_REG(770, 19), 0x4100);
		अगर (ret_val)
			जाओ release;
	पूर्ण

	ret_val = e1000_configure_k1_ich8lan(hw, k1_enable);

release:
	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_configure_k1_ich8lan - Configure K1 घातer state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @k1_enable: K1 state to configure
 *
 *  Configure the K1 घातer state based on the provided parameter.
 *  Assumes semaphore alपढ़ोy acquired.
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 **/
s32 e1000_configure_k1_ich8lan(काष्ठा e1000_hw *hw, bool k1_enable)
अणु
	s32 ret_val;
	u32 ctrl_reg = 0;
	u32 ctrl_ext = 0;
	u32 reg = 0;
	u16 kmrn_reg = 0;

	ret_val = e1000e_पढ़ो_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
					      &kmrn_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर (k1_enable)
		kmrn_reg |= E1000_KMRNCTRLSTA_K1_ENABLE;
	अन्यथा
		kmrn_reg &= ~E1000_KMRNCTRLSTA_K1_ENABLE;

	ret_val = e1000e_ग_लिखो_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
					       kmrn_reg);
	अगर (ret_val)
		वापस ret_val;

	usleep_range(20, 40);
	ctrl_ext = er32(CTRL_EXT);
	ctrl_reg = er32(CTRL);

	reg = ctrl_reg & ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
	reg |= E1000_CTRL_FRCSPD;
	ew32(CTRL, reg);

	ew32(CTRL_EXT, ctrl_ext | E1000_CTRL_EXT_SPD_BYPS);
	e1e_flush();
	usleep_range(20, 40);
	ew32(CTRL, ctrl_reg);
	ew32(CTRL_EXT, ctrl_ext);
	e1e_flush();
	usleep_range(20, 40);

	वापस 0;
पूर्ण

/**
 *  e1000_oem_bits_config_ich8lan - SW-based LCD Configuration
 *  @hw:       poपूर्णांकer to the HW काष्ठाure
 *  @d0_state: boolean अगर entering d0 or d3 device state
 *
 *  SW will configure Gbe Disable and LPLU based on the NVM. The four bits are
 *  collectively called OEM bits.  The OEM Write Enable bit and SW Config bit
 *  in NVM determines whether HW should configure LPLU and Gbe Disable.
 **/
अटल s32 e1000_oem_bits_config_ich8lan(काष्ठा e1000_hw *hw, bool d0_state)
अणु
	s32 ret_val = 0;
	u32 mac_reg;
	u16 oem_reg;

	अगर (hw->mac.type < e1000_pchlan)
		वापस ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	अगर (hw->mac.type == e1000_pchlan) अणु
		mac_reg = er32(EXTCNF_CTRL);
		अगर (mac_reg & E1000_EXTCNF_CTRL_OEM_WRITE_ENABLE)
			जाओ release;
	पूर्ण

	mac_reg = er32(FEXTNVM);
	अगर (!(mac_reg & E1000_FEXTNVM_SW_CONFIG_ICH8M))
		जाओ release;

	mac_reg = er32(PHY_CTRL);

	ret_val = e1e_rphy_locked(hw, HV_OEM_BITS, &oem_reg);
	अगर (ret_val)
		जाओ release;

	oem_reg &= ~(HV_OEM_BITS_GBE_DIS | HV_OEM_BITS_LPLU);

	अगर (d0_state) अणु
		अगर (mac_reg & E1000_PHY_CTRL_GBE_DISABLE)
			oem_reg |= HV_OEM_BITS_GBE_DIS;

		अगर (mac_reg & E1000_PHY_CTRL_D0A_LPLU)
			oem_reg |= HV_OEM_BITS_LPLU;
	पूर्ण अन्यथा अणु
		अगर (mac_reg & (E1000_PHY_CTRL_GBE_DISABLE |
			       E1000_PHY_CTRL_NOND0A_GBE_DISABLE))
			oem_reg |= HV_OEM_BITS_GBE_DIS;

		अगर (mac_reg & (E1000_PHY_CTRL_D0A_LPLU |
			       E1000_PHY_CTRL_NOND0A_LPLU))
			oem_reg |= HV_OEM_BITS_LPLU;
	पूर्ण

	/* Set Restart स्वतः-neg to activate the bits */
	अगर ((d0_state || (hw->mac.type != e1000_pchlan)) &&
	    !hw->phy.ops.check_reset_block(hw))
		oem_reg |= HV_OEM_BITS_RESTART_AN;

	ret_val = e1e_wphy_locked(hw, HV_OEM_BITS, oem_reg);

release:
	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_set_mdio_slow_mode_hv - Set slow MDIO access mode
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_set_mdio_slow_mode_hv(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, HV_KMRN_MODE_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

	data |= HV_KMRN_MDIO_SLOW;

	ret_val = e1e_wphy(hw, HV_KMRN_MODE_CTRL, data);

	वापस ret_val;
पूर्ण

/**
 *  e1000_hv_phy_workarounds_ich8lan - apply PHY workarounds
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  A series of PHY workarounds to be करोne after every PHY reset.
 **/
अटल s32 e1000_hv_phy_workarounds_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 phy_data;

	अगर (hw->mac.type != e1000_pchlan)
		वापस 0;

	/* Set MDIO slow mode beक्रमe any other MDIO access */
	अगर (hw->phy.type == e1000_phy_82577) अणु
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (((hw->phy.type == e1000_phy_82577) &&
	     ((hw->phy.revision == 1) || (hw->phy.revision == 2))) ||
	    ((hw->phy.type == e1000_phy_82578) && (hw->phy.revision == 1))) अणु
		/* Disable generation of early preamble */
		ret_val = e1e_wphy(hw, PHY_REG(769, 25), 0x4431);
		अगर (ret_val)
			वापस ret_val;

		/* Preamble tuning क्रम SSC */
		ret_val = e1e_wphy(hw, HV_KMRN_FIFO_CTRLSTA, 0xA204);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (hw->phy.type == e1000_phy_82578) अणु
		/* Return रेजिस्टरs to शेष by करोing a soft reset then
		 * writing 0x3140 to the control रेजिस्टर.
		 */
		अगर (hw->phy.revision < 2) अणु
			e1000e_phy_sw_reset(hw);
			ret_val = e1e_wphy(hw, MII_BMCR, 0x3140);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण
	पूर्ण

	/* Select page 0 */
	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	hw->phy.addr = 1;
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT, 0);
	hw->phy.ops.release(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Configure the K1 Si workaround during phy reset assuming there is
	 * link so that it disables K1 अगर link is in 1Gbps.
	 */
	ret_val = e1000_k1_gig_workaround_hv(hw, true);
	अगर (ret_val)
		वापस ret_val;

	/* Workaround क्रम link disconnects on a busy hub in half duplex */
	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;
	ret_val = e1e_rphy_locked(hw, BM_PORT_GEN_CFG, &phy_data);
	अगर (ret_val)
		जाओ release;
	ret_val = e1e_wphy_locked(hw, BM_PORT_GEN_CFG, phy_data & 0x00FF);
	अगर (ret_val)
		जाओ release;

	/* set MSE higher to enable link to stay up when noise is high */
	ret_val = e1000_ग_लिखो_emi_reg_locked(hw, I82577_MSE_THRESHOLD, 0x0034);
release:
	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_copy_rx_addrs_to_phy_ich8lan - Copy Rx addresses from MAC to PHY
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 **/
व्योम e1000_copy_rx_addrs_to_phy_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 mac_reg;
	u16 i, phy_reg = 0;
	s32 ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस;
	ret_val = e1000_enable_phy_wakeup_reg_access_bm(hw, &phy_reg);
	अगर (ret_val)
		जाओ release;

	/* Copy both RAL/H (rar_entry_count) and SHRAL/H to PHY */
	क्रम (i = 0; i < (hw->mac.rar_entry_count); i++) अणु
		mac_reg = er32(RAL(i));
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_RAR_L(i),
					   (u16)(mac_reg & 0xFFFF));
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_RAR_M(i),
					   (u16)((mac_reg >> 16) & 0xFFFF));

		mac_reg = er32(RAH(i));
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_RAR_H(i),
					   (u16)(mac_reg & 0xFFFF));
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_RAR_CTRL(i),
					   (u16)((mac_reg & E1000_RAH_AV)
						 >> 16));
	पूर्ण

	e1000_disable_phy_wakeup_reg_access_bm(hw, &phy_reg);

release:
	hw->phy.ops.release(hw);
पूर्ण

/**
 *  e1000_lv_jumbo_workaround_ich8lan - required क्रम jumbo frame operation
 *  with 82579 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @enable: flag to enable/disable workaround when enabling/disabling jumbos
 **/
s32 e1000_lv_jumbo_workaround_ich8lan(काष्ठा e1000_hw *hw, bool enable)
अणु
	s32 ret_val = 0;
	u16 phy_reg, data;
	u32 mac_reg;
	u16 i;

	अगर (hw->mac.type < e1000_pch2lan)
		वापस 0;

	/* disable Rx path जबतक enabling/disabling workaround */
	e1e_rphy(hw, PHY_REG(769, 20), &phy_reg);
	ret_val = e1e_wphy(hw, PHY_REG(769, 20), phy_reg | BIT(14));
	अगर (ret_val)
		वापस ret_val;

	अगर (enable) अणु
		/* Write Rx addresses (rar_entry_count क्रम RAL/H, and
		 * SHRAL/H) and initial CRC values to the MAC
		 */
		क्रम (i = 0; i < hw->mac.rar_entry_count; i++) अणु
			u8 mac_addr[ETH_ALEN] = अणु 0 पूर्ण;
			u32 addr_high, addr_low;

			addr_high = er32(RAH(i));
			अगर (!(addr_high & E1000_RAH_AV))
				जारी;
			addr_low = er32(RAL(i));
			mac_addr[0] = (addr_low & 0xFF);
			mac_addr[1] = ((addr_low >> 8) & 0xFF);
			mac_addr[2] = ((addr_low >> 16) & 0xFF);
			mac_addr[3] = ((addr_low >> 24) & 0xFF);
			mac_addr[4] = (addr_high & 0xFF);
			mac_addr[5] = ((addr_high >> 8) & 0xFF);

			ew32(PCH_RAICC(i), ~ether_crc_le(ETH_ALEN, mac_addr));
		पूर्ण

		/* Write Rx addresses to the PHY */
		e1000_copy_rx_addrs_to_phy_ich8lan(hw);

		/* Enable jumbo frame workaround in the MAC */
		mac_reg = er32(FFLT_DBG);
		mac_reg &= ~BIT(14);
		mac_reg |= (7 << 15);
		ew32(FFLT_DBG, mac_reg);

		mac_reg = er32(RCTL);
		mac_reg |= E1000_RCTL_SECRC;
		ew32(RCTL, mac_reg);

		ret_val = e1000e_पढ़ो_kmrn_reg(hw,
					       E1000_KMRNCTRLSTA_CTRL_OFFSET,
					       &data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000e_ग_लिखो_kmrn_reg(hw,
						E1000_KMRNCTRLSTA_CTRL_OFFSET,
						data | BIT(0));
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000e_पढ़ो_kmrn_reg(hw,
					       E1000_KMRNCTRLSTA_HD_CTRL,
					       &data);
		अगर (ret_val)
			वापस ret_val;
		data &= ~(0xF << 8);
		data |= (0xB << 8);
		ret_val = e1000e_ग_लिखो_kmrn_reg(hw,
						E1000_KMRNCTRLSTA_HD_CTRL,
						data);
		अगर (ret_val)
			वापस ret_val;

		/* Enable jumbo frame workaround in the PHY */
		e1e_rphy(hw, PHY_REG(769, 23), &data);
		data &= ~(0x7F << 5);
		data |= (0x37 << 5);
		ret_val = e1e_wphy(hw, PHY_REG(769, 23), data);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, PHY_REG(769, 16), &data);
		data &= ~BIT(13);
		ret_val = e1e_wphy(hw, PHY_REG(769, 16), data);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, PHY_REG(776, 20), &data);
		data &= ~(0x3FF << 2);
		data |= (E1000_TX_PTR_GAP << 2);
		ret_val = e1e_wphy(hw, PHY_REG(776, 20), data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1e_wphy(hw, PHY_REG(776, 23), 0xF100);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, HV_PM_CTRL, &data);
		ret_val = e1e_wphy(hw, HV_PM_CTRL, data | BIT(10));
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		/* Write MAC रेजिस्टर values back to h/w शेषs */
		mac_reg = er32(FFLT_DBG);
		mac_reg &= ~(0xF << 14);
		ew32(FFLT_DBG, mac_reg);

		mac_reg = er32(RCTL);
		mac_reg &= ~E1000_RCTL_SECRC;
		ew32(RCTL, mac_reg);

		ret_val = e1000e_पढ़ो_kmrn_reg(hw,
					       E1000_KMRNCTRLSTA_CTRL_OFFSET,
					       &data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000e_ग_लिखो_kmrn_reg(hw,
						E1000_KMRNCTRLSTA_CTRL_OFFSET,
						data & ~BIT(0));
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000e_पढ़ो_kmrn_reg(hw,
					       E1000_KMRNCTRLSTA_HD_CTRL,
					       &data);
		अगर (ret_val)
			वापस ret_val;
		data &= ~(0xF << 8);
		data |= (0xB << 8);
		ret_val = e1000e_ग_लिखो_kmrn_reg(hw,
						E1000_KMRNCTRLSTA_HD_CTRL,
						data);
		अगर (ret_val)
			वापस ret_val;

		/* Write PHY रेजिस्टर values back to h/w शेषs */
		e1e_rphy(hw, PHY_REG(769, 23), &data);
		data &= ~(0x7F << 5);
		ret_val = e1e_wphy(hw, PHY_REG(769, 23), data);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, PHY_REG(769, 16), &data);
		data |= BIT(13);
		ret_val = e1e_wphy(hw, PHY_REG(769, 16), data);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, PHY_REG(776, 20), &data);
		data &= ~(0x3FF << 2);
		data |= (0x8 << 2);
		ret_val = e1e_wphy(hw, PHY_REG(776, 20), data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1e_wphy(hw, PHY_REG(776, 23), 0x7E00);
		अगर (ret_val)
			वापस ret_val;
		e1e_rphy(hw, HV_PM_CTRL, &data);
		ret_val = e1e_wphy(hw, HV_PM_CTRL, data & ~BIT(10));
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* re-enable Rx path after enabling/disabling workaround */
	वापस e1e_wphy(hw, PHY_REG(769, 20), phy_reg & ~BIT(14));
पूर्ण

/**
 *  e1000_lv_phy_workarounds_ich8lan - apply ich8 specअगरic workarounds
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  A series of PHY workarounds to be करोne after every PHY reset.
 **/
अटल s32 e1000_lv_phy_workarounds_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	अगर (hw->mac.type != e1000_pch2lan)
		वापस 0;

	/* Set MDIO slow mode beक्रमe any other MDIO access */
	ret_val = e1000_set_mdio_slow_mode_hv(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;
	/* set MSE higher to enable link to stay up when noise is high */
	ret_val = e1000_ग_लिखो_emi_reg_locked(hw, I82579_MSE_THRESHOLD, 0x0034);
	अगर (ret_val)
		जाओ release;
	/* drop link after 5 बार MSE threshold was reached */
	ret_val = e1000_ग_लिखो_emi_reg_locked(hw, I82579_MSE_LINK_DOWN, 0x0005);
release:
	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_k1_workaround_lv - K1 Si workaround
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 *
 *  Workaround to set the K1 beacon duration क्रम 82579 parts in 10Mbps
 *  Disable K1 in 1000Mbps and 100Mbps
 **/
अटल s32 e1000_k1_workaround_lv(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 status_reg = 0;

	अगर (hw->mac.type != e1000_pch2lan)
		वापस 0;

	/* Set K1 beacon duration based on 10Mbs speed */
	ret_val = e1e_rphy(hw, HV_M_STATUS, &status_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर ((status_reg & (HV_M_STATUS_LINK_UP | HV_M_STATUS_AUTONEG_COMPLETE))
	    == (HV_M_STATUS_LINK_UP | HV_M_STATUS_AUTONEG_COMPLETE)) अणु
		अगर (status_reg &
		    (HV_M_STATUS_SPEED_1000 | HV_M_STATUS_SPEED_100)) अणु
			u16 pm_phy_reg;

			/* LV 1G/100 Packet drop issue wa  */
			ret_val = e1e_rphy(hw, HV_PM_CTRL, &pm_phy_reg);
			अगर (ret_val)
				वापस ret_val;
			pm_phy_reg &= ~HV_PM_CTRL_K1_ENABLE;
			ret_val = e1e_wphy(hw, HV_PM_CTRL, pm_phy_reg);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण अन्यथा अणु
			u32 mac_reg;

			mac_reg = er32(FEXTNVM4);
			mac_reg &= ~E1000_FEXTNVM4_BEACON_DURATION_MASK;
			mac_reg |= E1000_FEXTNVM4_BEACON_DURATION_16USEC;
			ew32(FEXTNVM4, mac_reg);
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_gate_hw_phy_config_ich8lan - disable PHY config via hardware
 *  @hw:   poपूर्णांकer to the HW काष्ठाure
 *  @gate: boolean set to true to gate, false to ungate
 *
 *  Gate/ungate the स्वतःmatic PHY configuration via hardware; perक्रमm
 *  the configuration via software instead.
 **/
अटल व्योम e1000_gate_hw_phy_config_ich8lan(काष्ठा e1000_hw *hw, bool gate)
अणु
	u32 extcnf_ctrl;

	अगर (hw->mac.type < e1000_pch2lan)
		वापस;

	extcnf_ctrl = er32(EXTCNF_CTRL);

	अगर (gate)
		extcnf_ctrl |= E1000_EXTCNF_CTRL_GATE_PHY_CFG;
	अन्यथा
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_GATE_PHY_CFG;

	ew32(EXTCNF_CTRL, extcnf_ctrl);
पूर्ण

/**
 *  e1000_lan_init_करोne_ich8lan - Check क्रम PHY config completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Check the appropriate indication the MAC has finished configuring the
 *  PHY after a software reset.
 **/
अटल व्योम e1000_lan_init_करोne_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 data, loop = E1000_ICH8_LAN_INIT_TIMEOUT;

	/* Wait क्रम basic configuration completes beक्रमe proceeding */
	करो अणु
		data = er32(STATUS);
		data &= E1000_STATUS_LAN_INIT_DONE;
		usleep_range(100, 200);
	पूर्ण जबतक ((!data) && --loop);

	/* If basic configuration is incomplete beक्रमe the above loop
	 * count reaches 0, loading the configuration from NVM will
	 * leave the PHY in a bad state possibly resulting in no link.
	 */
	अगर (loop == 0)
		e_dbg("LAN_INIT_DONE not set, increase timeout\n");

	/* Clear the Init Done bit क्रम the next init event */
	data = er32(STATUS);
	data &= ~E1000_STATUS_LAN_INIT_DONE;
	ew32(STATUS, data);
पूर्ण

/**
 *  e1000_post_phy_reset_ich8lan - Perक्रमm steps required after a PHY reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
अटल s32 e1000_post_phy_reset_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 reg;

	अगर (hw->phy.ops.check_reset_block(hw))
		वापस 0;

	/* Allow समय क्रम h/w to get to quiescent state after reset */
	usleep_range(10000, 11000);

	/* Perक्रमm any necessary post-reset workarounds */
	चयन (hw->mac.type) अणु
	हाल e1000_pchlan:
		ret_val = e1000_hv_phy_workarounds_ich8lan(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	हाल e1000_pch2lan:
		ret_val = e1000_lv_phy_workarounds_ich8lan(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Clear the host wakeup bit after lcd reset */
	अगर (hw->mac.type >= e1000_pchlan) अणु
		e1e_rphy(hw, BM_PORT_GEN_CFG, &reg);
		reg &= ~BM_WUC_HOST_WU_BIT;
		e1e_wphy(hw, BM_PORT_GEN_CFG, reg);
	पूर्ण

	/* Configure the LCD with the extended configuration region in NVM */
	ret_val = e1000_sw_lcd_config_ich8lan(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Configure the LCD with the OEM bits in NVM */
	ret_val = e1000_oem_bits_config_ich8lan(hw, true);

	अगर (hw->mac.type == e1000_pch2lan) अणु
		/* Ungate स्वतःmatic PHY configuration on non-managed 82579 */
		अगर (!(er32(FWSM) & E1000_ICH_FWSM_FW_VALID)) अणु
			usleep_range(10000, 11000);
			e1000_gate_hw_phy_config_ich8lan(hw, false);
		पूर्ण

		/* Set EEE LPI Update Timer to 200usec */
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000_ग_लिखो_emi_reg_locked(hw,
						     I82579_LPI_UPDATE_TIMER,
						     0x1387);
		hw->phy.ops.release(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_phy_hw_reset_ich8lan - Perक्रमms a PHY reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Resets the PHY
 *  This is a function poपूर्णांकer entry poपूर्णांक called by drivers
 *  or other shared routines.
 **/
अटल s32 e1000_phy_hw_reset_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	/* Gate स्वतःmatic PHY configuration by hardware on non-managed 82579 */
	अगर ((hw->mac.type == e1000_pch2lan) &&
	    !(er32(FWSM) & E1000_ICH_FWSM_FW_VALID))
		e1000_gate_hw_phy_config_ich8lan(hw, true);

	ret_val = e1000e_phy_hw_reset_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस e1000_post_phy_reset_ich8lan(hw);
पूर्ण

/**
 *  e1000_set_lplu_state_pchlan - Set Low Power Link Up state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU state according to the active flag.  For PCH, अगर OEM ग_लिखो
 *  bit are disabled in the NVM, writing the LPLU bits in the MAC will not set
 *  the phy speed. This function will manually set the LPLU bit and restart
 *  स्वतः-neg as hw would करो. D3 and D0 LPLU will call the same function
 *  since it configures the same bit.
 **/
अटल s32 e1000_set_lplu_state_pchlan(काष्ठा e1000_hw *hw, bool active)
अणु
	s32 ret_val;
	u16 oem_reg;

	ret_val = e1e_rphy(hw, HV_OEM_BITS, &oem_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर (active)
		oem_reg |= HV_OEM_BITS_LPLU;
	अन्यथा
		oem_reg &= ~HV_OEM_BITS_LPLU;

	अगर (!hw->phy.ops.check_reset_block(hw))
		oem_reg |= HV_OEM_BITS_RESTART_AN;

	वापस e1e_wphy(hw, HV_OEM_BITS, oem_reg);
पूर्ण

/**
 *  e1000_set_d0_lplu_state_ich8lan - Set Low Power Linkup D0 state
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
अटल s32 e1000_set_d0_lplu_state_ich8lan(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 phy_ctrl;
	s32 ret_val = 0;
	u16 data;

	अगर (phy->type == e1000_phy_अगरe)
		वापस 0;

	phy_ctrl = er32(PHY_CTRL);

	अगर (active) अणु
		phy_ctrl |= E1000_PHY_CTRL_D0A_LPLU;
		ew32(PHY_CTRL, phy_ctrl);

		अगर (phy->type != e1000_phy_igp_3)
			वापस 0;

		/* Call gig speed drop workaround on LPLU beक्रमe accessing
		 * any PHY रेजिस्टरs
		 */
		अगर (hw->mac.type == e1000_ich8lan)
			e1000e_gig_करोwnshअगरt_workaround_ich8lan(hw);

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG, &data);
		अगर (ret_val)
			वापस ret_val;
		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG, data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		phy_ctrl &= ~E1000_PHY_CTRL_D0A_LPLU;
		ew32(PHY_CTRL, phy_ctrl);

		अगर (phy->type != e1000_phy_igp_3)
			वापस 0;

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
 *  e1000_set_d3_lplu_state_ich8lan - Set Low Power Linkup D3 state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @active: true to enable LPLU, false to disable
 *
 *  Sets the LPLU D3 state according to the active flag.  When
 *  activating LPLU this function also disables smart speed
 *  and vice versa.  LPLU will not be activated unless the
 *  device स्वतःnegotiation advertisement meets standards of
 *  either 10 or 10/100 or 10/100/1000 at all duplexes.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  PHY setup routines.
 **/
अटल s32 e1000_set_d3_lplu_state_ich8lan(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 phy_ctrl;
	s32 ret_val = 0;
	u16 data;

	phy_ctrl = er32(PHY_CTRL);

	अगर (!active) अणु
		phy_ctrl &= ~E1000_PHY_CTRL_NOND0A_LPLU;
		ew32(PHY_CTRL, phy_ctrl);

		अगर (phy->type != e1000_phy_igp_3)
			वापस 0;

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
	पूर्ण अन्यथा अगर ((phy->स्वतःneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_NOT_GIG) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_10_SPEED)) अणु
		phy_ctrl |= E1000_PHY_CTRL_NOND0A_LPLU;
		ew32(PHY_CTRL, phy_ctrl);

		अगर (phy->type != e1000_phy_igp_3)
			वापस 0;

		/* Call gig speed drop workaround on LPLU beक्रमe accessing
		 * any PHY रेजिस्टरs
		 */
		अगर (hw->mac.type == e1000_ich8lan)
			e1000e_gig_करोwnshअगरt_workaround_ich8lan(hw);

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG, &data);
		अगर (ret_val)
			वापस ret_val;

		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG, data);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_valid_nvm_bank_detect_ich8lan - finds out the valid bank 0 or 1
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @bank:  poपूर्णांकer to the variable that वापसs the active bank
 *
 *  Reads signature byte from the NVM using the flash access रेजिस्टरs.
 *  Word 0x13 bits 15:14 = 10b indicate a valid signature क्रम that bank.
 **/
अटल s32 e1000_valid_nvm_bank_detect_ich8lan(काष्ठा e1000_hw *hw, u32 *bank)
अणु
	u32 eecd;
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 bank1_offset = nvm->flash_bank_size * माप(u16);
	u32 act_offset = E1000_ICH_NVM_SIG_WORD * 2 + 1;
	u32 nvm_dword = 0;
	u8 sig_byte = 0;
	s32 ret_val;

	चयन (hw->mac.type) अणु
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		bank1_offset = nvm->flash_bank_size;
		act_offset = E1000_ICH_NVM_SIG_WORD;

		/* set bank to 0 in हाल flash पढ़ो fails */
		*bank = 0;

		/* Check bank 0 */
		ret_val = e1000_पढ़ो_flash_dword_ich8lan(hw, act_offset,
							 &nvm_dword);
		अगर (ret_val)
			वापस ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		अगर ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) अणु
			*bank = 0;
			वापस 0;
		पूर्ण

		/* Check bank 1 */
		ret_val = e1000_पढ़ो_flash_dword_ich8lan(hw, act_offset +
							 bank1_offset,
							 &nvm_dword);
		अगर (ret_val)
			वापस ret_val;
		sig_byte = (u8)((nvm_dword & 0xFF00) >> 8);
		अगर ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) अणु
			*bank = 1;
			वापस 0;
		पूर्ण

		e_dbg("ERROR: No valid NVM bank present\n");
		वापस -E1000_ERR_NVM;
	हाल e1000_ich8lan:
	हाल e1000_ich9lan:
		eecd = er32(EECD);
		अगर ((eecd & E1000_EECD_SEC1VAL_VALID_MASK) ==
		    E1000_EECD_SEC1VAL_VALID_MASK) अणु
			अगर (eecd & E1000_EECD_SEC1VAL)
				*bank = 1;
			अन्यथा
				*bank = 0;

			वापस 0;
		पूर्ण
		e_dbg("Unable to determine valid NVM bank via EEC - reading flash signature\n");
		fallthrough;
	शेष:
		/* set bank to 0 in हाल flash पढ़ो fails */
		*bank = 0;

		/* Check bank 0 */
		ret_val = e1000_पढ़ो_flash_byte_ich8lan(hw, act_offset,
							&sig_byte);
		अगर (ret_val)
			वापस ret_val;
		अगर ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) अणु
			*bank = 0;
			वापस 0;
		पूर्ण

		/* Check bank 1 */
		ret_val = e1000_पढ़ो_flash_byte_ich8lan(hw, act_offset +
							bank1_offset,
							&sig_byte);
		अगर (ret_val)
			वापस ret_val;
		अगर ((sig_byte & E1000_ICH_NVM_VALID_SIG_MASK) ==
		    E1000_ICH_NVM_SIG_VALUE) अणु
			*bank = 1;
			वापस 0;
		पूर्ण

		e_dbg("ERROR: No valid NVM bank present\n");
		वापस -E1000_ERR_NVM;
	पूर्ण
पूर्ण

/**
 *  e1000_पढ़ो_nvm_spt - NVM access क्रम SPT
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the word(s) to पढ़ो.
 *  @words: Size of data to पढ़ो in words.
 *  @data: poपूर्णांकer to the word(s) to पढ़ो at offset.
 *
 *  Reads a word(s) from the NVM
 **/
अटल s32 e1000_पढ़ो_nvm_spt(काष्ठा e1000_hw *hw, u16 offset, u16 words,
			      u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 act_offset;
	s32 ret_val = 0;
	u32 bank = 0;
	u32 dword = 0;
	u16 offset_to_पढ़ो;
	u16 i;

	अगर ((offset >= nvm->word_size) || (words > nvm->word_size - offset) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	nvm->ops.acquire(hw);

	ret_val = e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	अगर (ret_val) अणु
		e_dbg("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	पूर्ण

	act_offset = (bank) ? nvm->flash_bank_size : 0;
	act_offset += offset;

	ret_val = 0;

	क्रम (i = 0; i < words; i += 2) अणु
		अगर (words - i == 1) अणु
			अगर (dev_spec->shaकरोw_ram[offset + i].modअगरied) अणु
				data[i] =
				    dev_spec->shaकरोw_ram[offset + i].value;
			पूर्ण अन्यथा अणु
				offset_to_पढ़ो = act_offset + i -
				    ((act_offset + i) % 2);
				ret_val =
				  e1000_पढ़ो_flash_dword_ich8lan(hw,
								 offset_to_पढ़ो,
								 &dword);
				अगर (ret_val)
					अवरोध;
				अगर ((act_offset + i) % 2 == 0)
					data[i] = (u16)(dword & 0xFFFF);
				अन्यथा
					data[i] = (u16)((dword >> 16) & 0xFFFF);
			पूर्ण
		पूर्ण अन्यथा अणु
			offset_to_पढ़ो = act_offset + i;
			अगर (!(dev_spec->shaकरोw_ram[offset + i].modअगरied) ||
			    !(dev_spec->shaकरोw_ram[offset + i + 1].modअगरied)) अणु
				ret_val =
				  e1000_पढ़ो_flash_dword_ich8lan(hw,
								 offset_to_पढ़ो,
								 &dword);
				अगर (ret_val)
					अवरोध;
			पूर्ण
			अगर (dev_spec->shaकरोw_ram[offset + i].modअगरied)
				data[i] =
				    dev_spec->shaकरोw_ram[offset + i].value;
			अन्यथा
				data[i] = (u16)(dword & 0xFFFF);
			अगर (dev_spec->shaकरोw_ram[offset + i].modअगरied)
				data[i + 1] =
				    dev_spec->shaकरोw_ram[offset + i + 1].value;
			अन्यथा
				data[i + 1] = (u16)(dword >> 16 & 0xFFFF);
		पूर्ण
	पूर्ण

	nvm->ops.release(hw);

out:
	अगर (ret_val)
		e_dbg("NVM read error: %d\n", ret_val);

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_nvm_ich8lan - Read word(s) from the NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the word(s) to पढ़ो.
 *  @words: Size of data to पढ़ो in words
 *  @data: Poपूर्णांकer to the word(s) to पढ़ो at offset.
 *
 *  Reads a word(s) from the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_पढ़ो_nvm_ich8lan(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				  u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 act_offset;
	s32 ret_val = 0;
	u32 bank = 0;
	u16 i, word;

	अगर ((offset >= nvm->word_size) || (words > nvm->word_size - offset) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	nvm->ops.acquire(hw);

	ret_val = e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	अगर (ret_val) अणु
		e_dbg("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	पूर्ण

	act_offset = (bank) ? nvm->flash_bank_size : 0;
	act_offset += offset;

	ret_val = 0;
	क्रम (i = 0; i < words; i++) अणु
		अगर (dev_spec->shaकरोw_ram[offset + i].modअगरied) अणु
			data[i] = dev_spec->shaकरोw_ram[offset + i].value;
		पूर्ण अन्यथा अणु
			ret_val = e1000_पढ़ो_flash_word_ich8lan(hw,
								act_offset + i,
								&word);
			अगर (ret_val)
				अवरोध;
			data[i] = word;
		पूर्ण
	पूर्ण

	nvm->ops.release(hw);

out:
	अगर (ret_val)
		e_dbg("NVM read error: %d\n", ret_val);

	वापस ret_val;
पूर्ण

/**
 *  e1000_flash_cycle_init_ich8lan - Initialize flash
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This function करोes initial flash setup so that a new पढ़ो/ग_लिखो/erase cycle
 *  can be started.
 **/
अटल s32 e1000_flash_cycle_init_ich8lan(काष्ठा e1000_hw *hw)
अणु
	जोड़ ich8_hws_flash_status hsfsts;
	s32 ret_val = -E1000_ERR_NVM;

	hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);

	/* Check अगर the flash descriptor is valid */
	अगर (!hsfsts.hsf_status.fldesvalid) अणु
		e_dbg("Flash descriptor invalid.  SW Sequencing must be used.\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	/* Clear FCERR and DAEL in hw status by writing 1 */
	hsfsts.hsf_status.flcerr = 1;
	hsfsts.hsf_status.dael = 1;
	अगर (hw->mac.type >= e1000_pch_spt)
		ew32flash(ICH_FLASH_HSFSTS, hsfsts.regval & 0xFFFF);
	अन्यथा
		ew16flash(ICH_FLASH_HSFSTS, hsfsts.regval);

	/* Either we should have a hardware SPI cycle in progress
	 * bit to check against, in order to start a new cycle or
	 * FDONE bit should be changed in the hardware so that it
	 * is 1 after hardware reset, which can then be used as an
	 * indication whether a cycle is in progress or has been
	 * completed.
	 */

	अगर (!hsfsts.hsf_status.flcinprog) अणु
		/* There is no cycle running at present,
		 * so we can start a cycle.
		 * Begin by setting Flash Cycle Done.
		 */
		hsfsts.hsf_status.flcकरोne = 1;
		अगर (hw->mac.type >= e1000_pch_spt)
			ew32flash(ICH_FLASH_HSFSTS, hsfsts.regval & 0xFFFF);
		अन्यथा
			ew16flash(ICH_FLASH_HSFSTS, hsfsts.regval);
		ret_val = 0;
	पूर्ण अन्यथा अणु
		s32 i;

		/* Otherwise poll क्रम someसमय so the current
		 * cycle has a chance to end beक्रमe giving up.
		 */
		क्रम (i = 0; i < ICH_FLASH_READ_COMMAND_TIMEOUT; i++) अणु
			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			अगर (!hsfsts.hsf_status.flcinprog) अणु
				ret_val = 0;
				अवरोध;
			पूर्ण
			udelay(1);
		पूर्ण
		अगर (!ret_val) अणु
			/* Successful in रुकोing क्रम previous cycle to समयout,
			 * now set the Flash Cycle Done.
			 */
			hsfsts.hsf_status.flcकरोne = 1;
			अगर (hw->mac.type >= e1000_pch_spt)
				ew32flash(ICH_FLASH_HSFSTS,
					  hsfsts.regval & 0xFFFF);
			अन्यथा
				ew16flash(ICH_FLASH_HSFSTS, hsfsts.regval);
		पूर्ण अन्यथा अणु
			e_dbg("Flash controller busy, cannot get access\n");
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_flash_cycle_ich8lan - Starts flash cycle (पढ़ो/ग_लिखो/erase)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @समयout: maximum समय to रुको क्रम completion
 *
 *  This function starts a flash cycle and रुकोs क्रम its completion.
 **/
अटल s32 e1000_flash_cycle_ich8lan(काष्ठा e1000_hw *hw, u32 समयout)
अणु
	जोड़ ich8_hws_flash_ctrl hsflctl;
	जोड़ ich8_hws_flash_status hsfsts;
	u32 i = 0;

	/* Start a cycle by writing 1 in Flash Cycle Go in Hw Flash Control */
	अगर (hw->mac.type >= e1000_pch_spt)
		hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;
	अन्यथा
		hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);
	hsflctl.hsf_ctrl.flcgo = 1;

	अगर (hw->mac.type >= e1000_pch_spt)
		ew32flash(ICH_FLASH_HSFSTS, hsflctl.regval << 16);
	अन्यथा
		ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

	/* रुको till FDONE bit is set to 1 */
	करो अणु
		hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
		अगर (hsfsts.hsf_status.flcकरोne)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (i++ < समयout);

	अगर (hsfsts.hsf_status.flcकरोne && !hsfsts.hsf_status.flcerr)
		वापस 0;

	वापस -E1000_ERR_NVM;
पूर्ण

/**
 *  e1000_पढ़ो_flash_dword_ich8lan - Read dword from flash
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset to data location
 *  @data: poपूर्णांकer to the location क्रम storing the data
 *
 *  Reads the flash dword at offset पूर्णांकo data.  Offset is converted
 *  to bytes beक्रमe पढ़ो.
 **/
अटल s32 e1000_पढ़ो_flash_dword_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					  u32 *data)
अणु
	/* Must convert word offset पूर्णांकo bytes. */
	offset <<= 1;
	वापस e1000_पढ़ो_flash_data32_ich8lan(hw, offset, data);
पूर्ण

/**
 *  e1000_पढ़ो_flash_word_ich8lan - Read word from flash
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset to data location
 *  @data: poपूर्णांकer to the location क्रम storing the data
 *
 *  Reads the flash word at offset पूर्णांकo data.  Offset is converted
 *  to bytes beक्रमe पढ़ो.
 **/
अटल s32 e1000_पढ़ो_flash_word_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u16 *data)
अणु
	/* Must convert offset पूर्णांकo bytes. */
	offset <<= 1;

	वापस e1000_पढ़ो_flash_data_ich8lan(hw, offset, 2, data);
पूर्ण

/**
 *  e1000_पढ़ो_flash_byte_ich8lan - Read byte from flash
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset of the byte to पढ़ो.
 *  @data: Poपूर्णांकer to a byte to store the value पढ़ो.
 *
 *  Reads a single byte from the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_पढ़ो_flash_byte_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u8 *data)
अणु
	s32 ret_val;
	u16 word = 0;

	/* In SPT, only 32 bits access is supported,
	 * so this function should not be called.
	 */
	अगर (hw->mac.type >= e1000_pch_spt)
		वापस -E1000_ERR_NVM;
	अन्यथा
		ret_val = e1000_पढ़ो_flash_data_ich8lan(hw, offset, 1, &word);

	अगर (ret_val)
		वापस ret_val;

	*data = (u8)word;

	वापस 0;
पूर्ण

/**
 *  e1000_पढ़ो_flash_data_ich8lan - Read byte or word from NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the byte or word to पढ़ो.
 *  @size: Size of data to पढ़ो, 1=byte 2=word
 *  @data: Poपूर्णांकer to the word to store the value पढ़ो.
 *
 *  Reads a byte or word from the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_पढ़ो_flash_data_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					 u8 size, u16 *data)
अणु
	जोड़ ich8_hws_flash_status hsfsts;
	जोड़ ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	u32 flash_data = 0;
	s32 ret_val = -E1000_ERR_NVM;
	u8 count = 0;

	अगर (size < 1 || size > 2 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
		वापस -E1000_ERR_NVM;

	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	करो अणु
		udelay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		अगर (ret_val)
			अवरोध;

		hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);
		/* 0b/1b corresponds to 1 or 2 byte size, respectively. */
		hsflctl.hsf_ctrl.fldbcount = size - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_READ;
		ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		ret_val =
		    e1000_flash_cycle_ich8lan(hw,
					      ICH_FLASH_READ_COMMAND_TIMEOUT);

		/* Check अगर FCERR is set to 1, अगर set to 1, clear it
		 * and try the whole sequence a few more बार, अन्यथा
		 * पढ़ो in (shअगरt in) the Flash Data0, the order is
		 * least signअगरicant byte first msb to lsb
		 */
		अगर (!ret_val) अणु
			flash_data = er32flash(ICH_FLASH_FDATA0);
			अगर (size == 1)
				*data = (u8)(flash_data & 0x000000FF);
			अन्यथा अगर (size == 2)
				*data = (u16)(flash_data & 0x0000FFFF);
			अवरोध;
		पूर्ण अन्यथा अणु
			/* If we've gotten here, then things are probably
			 * completely hosed, but अगर the error condition is
			 * detected, it won't hurt to give it another try...
			 * ICH_FLASH_CYCLE_REPEAT_COUNT बार.
			 */
			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			अगर (hsfsts.hsf_status.flcerr) अणु
				/* Repeat क्रम some समय beक्रमe giving up. */
				जारी;
			पूर्ण अन्यथा अगर (!hsfsts.hsf_status.flcकरोne) अणु
				e_dbg("Timeout error - flash cycle did not complete.\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_flash_data32_ich8lan - Read dword from NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the dword to पढ़ो.
 *  @data: Poपूर्णांकer to the dword to store the value पढ़ो.
 *
 *  Reads a byte or word from the NVM using the flash access रेजिस्टरs.
 **/

अटल s32 e1000_पढ़ो_flash_data32_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					   u32 *data)
अणु
	जोड़ ich8_hws_flash_status hsfsts;
	जोड़ ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	s32 ret_val = -E1000_ERR_NVM;
	u8 count = 0;

	अगर (offset > ICH_FLASH_LINEAR_ADDR_MASK || hw->mac.type < e1000_pch_spt)
		वापस -E1000_ERR_NVM;
	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	करो अणु
		udelay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		अगर (ret_val)
			अवरोध;
		/* In SPT, This रेजिस्टर is in Lan memory space, not flash.
		 * Thereक्रमe, only 32 bit access is supported
		 */
		hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;

		/* 0b/1b corresponds to 1 or 2 byte size, respectively. */
		hsflctl.hsf_ctrl.fldbcount = माप(u32) - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_READ;
		/* In SPT, This रेजिस्टर is in Lan memory space, not flash.
		 * Thereक्रमe, only 32 bit access is supported
		 */
		ew32flash(ICH_FLASH_HSFSTS, (u32)hsflctl.regval << 16);
		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		ret_val =
		   e1000_flash_cycle_ich8lan(hw,
					     ICH_FLASH_READ_COMMAND_TIMEOUT);

		/* Check अगर FCERR is set to 1, अगर set to 1, clear it
		 * and try the whole sequence a few more बार, अन्यथा
		 * पढ़ो in (shअगरt in) the Flash Data0, the order is
		 * least signअगरicant byte first msb to lsb
		 */
		अगर (!ret_val) अणु
			*data = er32flash(ICH_FLASH_FDATA0);
			अवरोध;
		पूर्ण अन्यथा अणु
			/* If we've gotten here, then things are probably
			 * completely hosed, but अगर the error condition is
			 * detected, it won't hurt to give it another try...
			 * ICH_FLASH_CYCLE_REPEAT_COUNT बार.
			 */
			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			अगर (hsfsts.hsf_status.flcerr) अणु
				/* Repeat क्रम some समय beक्रमe giving up. */
				जारी;
			पूर्ण अन्यथा अगर (!hsfsts.hsf_status.flcकरोne) अणु
				e_dbg("Timeout error - flash cycle did not complete.\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_nvm_ich8lan - Write word(s) to the NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the word(s) to ग_लिखो.
 *  @words: Size of data to ग_लिखो in words
 *  @data: Poपूर्णांकer to the word(s) to ग_लिखो at offset.
 *
 *  Writes a byte or word to the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_ग_लिखो_nvm_ich8lan(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				   u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u16 i;

	अगर ((offset >= nvm->word_size) || (words > nvm->word_size - offset) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	nvm->ops.acquire(hw);

	क्रम (i = 0; i < words; i++) अणु
		dev_spec->shaकरोw_ram[offset + i].modअगरied = true;
		dev_spec->shaकरोw_ram[offset + i].value = data[i];
	पूर्ण

	nvm->ops.release(hw);

	वापस 0;
पूर्ण

/**
 *  e1000_update_nvm_checksum_spt - Update the checksum क्रम NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The NVM checksum is updated by calling the generic update_nvm_checksum,
 *  which ग_लिखोs the checksum to the shaकरोw ram.  The changes in the shaकरोw
 *  ram are then committed to the EEPROM by processing each bank at a समय
 *  checking क्रम the modअगरied bit and writing only the pending changes.
 *  After a successful commit, the shaकरोw ram is cleared and is पढ़ोy क्रम
 *  future ग_लिखोs.
 **/
अटल s32 e1000_update_nvm_checksum_spt(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 i, act_offset, new_bank_offset, old_bank_offset, bank;
	s32 ret_val;
	u32 dword = 0;

	ret_val = e1000e_update_nvm_checksum_generic(hw);
	अगर (ret_val)
		जाओ out;

	अगर (nvm->type != e1000_nvm_flash_sw)
		जाओ out;

	nvm->ops.acquire(hw);

	/* We're writing to the opposite bank so if we're on bank 1,
	 * ग_लिखो to bank 0 etc.  We also need to erase the segment that
	 * is going to be written
	 */
	ret_val = e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	अगर (ret_val) अणु
		e_dbg("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	पूर्ण

	अगर (bank == 0) अणु
		new_bank_offset = nvm->flash_bank_size;
		old_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 1);
		अगर (ret_val)
			जाओ release;
	पूर्ण अन्यथा अणु
		old_bank_offset = nvm->flash_bank_size;
		new_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 0);
		अगर (ret_val)
			जाओ release;
	पूर्ण
	क्रम (i = 0; i < E1000_ICH8_SHADOW_RAM_WORDS; i += 2) अणु
		/* Determine whether to ग_लिखो the value stored
		 * in the other NVM bank or a modअगरied value stored
		 * in the shaकरोw RAM
		 */
		ret_val = e1000_पढ़ो_flash_dword_ich8lan(hw,
							 i + old_bank_offset,
							 &dword);

		अगर (dev_spec->shaकरोw_ram[i].modअगरied) अणु
			dword &= 0xffff0000;
			dword |= (dev_spec->shaकरोw_ram[i].value & 0xffff);
		पूर्ण
		अगर (dev_spec->shaकरोw_ram[i + 1].modअगरied) अणु
			dword &= 0x0000ffff;
			dword |= ((dev_spec->shaकरोw_ram[i + 1].value & 0xffff)
				  << 16);
		पूर्ण
		अगर (ret_val)
			अवरोध;

		/* If the word is 0x13, then make sure the signature bits
		 * (15:14) are 11b until the commit has completed.
		 * This will allow us to ग_लिखो 10b which indicates the
		 * signature is valid.  We want to करो this after the ग_लिखो
		 * has completed so that we करोn't mark the segment valid
		 * जबतक the ग_लिखो is still in progress
		 */
		अगर (i == E1000_ICH_NVM_SIG_WORD - 1)
			dword |= E1000_ICH_NVM_SIG_MASK << 16;

		/* Convert offset to bytes. */
		act_offset = (i + new_bank_offset) << 1;

		usleep_range(100, 200);

		/* Write the data to the new bank. Offset in words */
		act_offset = i + new_bank_offset;
		ret_val = e1000_retry_ग_लिखो_flash_dword_ich8lan(hw, act_offset,
								dword);
		अगर (ret_val)
			अवरोध;
	पूर्ण

	/* Don't bother writing the segment valid bits अगर sector
	 * programming failed.
	 */
	अगर (ret_val) अणु
		/* Possibly पढ़ो-only, see e1000e_ग_लिखो_protect_nvm_ich8lan() */
		e_dbg("Flash commit failed.\n");
		जाओ release;
	पूर्ण

	/* Finally validate the new segment by setting bit 15:14
	 * to 10b in word 0x13 , this can be करोne without an
	 * erase as well since these bits are 11 to start with
	 * and we need to change bit 14 to 0b
	 */
	act_offset = new_bank_offset + E1000_ICH_NVM_SIG_WORD;

	/*offset in words but we पढ़ो dword */
	--act_offset;
	ret_val = e1000_पढ़ो_flash_dword_ich8lan(hw, act_offset, &dword);

	अगर (ret_val)
		जाओ release;

	dword &= 0xBFFFFFFF;
	ret_val = e1000_retry_ग_लिखो_flash_dword_ich8lan(hw, act_offset, dword);

	अगर (ret_val)
		जाओ release;

	/* offset in words but we पढ़ो dword */
	act_offset = old_bank_offset + E1000_ICH_NVM_SIG_WORD - 1;
	ret_val = e1000_पढ़ो_flash_dword_ich8lan(hw, act_offset, &dword);

	अगर (ret_val)
		जाओ release;

	dword &= 0x00FFFFFF;
	ret_val = e1000_retry_ग_लिखो_flash_dword_ich8lan(hw, act_offset, dword);

	अगर (ret_val)
		जाओ release;

	/* Great!  Everything worked, we can now clear the cached entries. */
	क्रम (i = 0; i < E1000_ICH8_SHADOW_RAM_WORDS; i++) अणु
		dev_spec->shaकरोw_ram[i].modअगरied = false;
		dev_spec->shaकरोw_ram[i].value = 0xFFFF;
	पूर्ण

release:
	nvm->ops.release(hw);

	/* Reload the EEPROM, or अन्यथा modअगरications will not appear
	 * until after the next adapter reset.
	 */
	अगर (!ret_val) अणु
		nvm->ops.reload(hw);
		usleep_range(10000, 11000);
	पूर्ण

out:
	अगर (ret_val)
		e_dbg("NVM update error: %d\n", ret_val);

	वापस ret_val;
पूर्ण

/**
 *  e1000_update_nvm_checksum_ich8lan - Update the checksum क्रम NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The NVM checksum is updated by calling the generic update_nvm_checksum,
 *  which ग_लिखोs the checksum to the shaकरोw ram.  The changes in the shaकरोw
 *  ram are then committed to the EEPROM by processing each bank at a समय
 *  checking क्रम the modअगरied bit and writing only the pending changes.
 *  After a successful commit, the shaकरोw ram is cleared and is पढ़ोy क्रम
 *  future ग_लिखोs.
 **/
अटल s32 e1000_update_nvm_checksum_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 i, act_offset, new_bank_offset, old_bank_offset, bank;
	s32 ret_val;
	u16 data = 0;

	ret_val = e1000e_update_nvm_checksum_generic(hw);
	अगर (ret_val)
		जाओ out;

	अगर (nvm->type != e1000_nvm_flash_sw)
		जाओ out;

	nvm->ops.acquire(hw);

	/* We're writing to the opposite bank so if we're on bank 1,
	 * ग_लिखो to bank 0 etc.  We also need to erase the segment that
	 * is going to be written
	 */
	ret_val = e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	अगर (ret_val) अणु
		e_dbg("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	पूर्ण

	अगर (bank == 0) अणु
		new_bank_offset = nvm->flash_bank_size;
		old_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 1);
		अगर (ret_val)
			जाओ release;
	पूर्ण अन्यथा अणु
		old_bank_offset = nvm->flash_bank_size;
		new_bank_offset = 0;
		ret_val = e1000_erase_flash_bank_ich8lan(hw, 0);
		अगर (ret_val)
			जाओ release;
	पूर्ण
	क्रम (i = 0; i < E1000_ICH8_SHADOW_RAM_WORDS; i++) अणु
		अगर (dev_spec->shaकरोw_ram[i].modअगरied) अणु
			data = dev_spec->shaकरोw_ram[i].value;
		पूर्ण अन्यथा अणु
			ret_val = e1000_पढ़ो_flash_word_ich8lan(hw, i +
								old_bank_offset,
								&data);
			अगर (ret_val)
				अवरोध;
		पूर्ण

		/* If the word is 0x13, then make sure the signature bits
		 * (15:14) are 11b until the commit has completed.
		 * This will allow us to ग_लिखो 10b which indicates the
		 * signature is valid.  We want to करो this after the ग_लिखो
		 * has completed so that we करोn't mark the segment valid
		 * जबतक the ग_लिखो is still in progress
		 */
		अगर (i == E1000_ICH_NVM_SIG_WORD)
			data |= E1000_ICH_NVM_SIG_MASK;

		/* Convert offset to bytes. */
		act_offset = (i + new_bank_offset) << 1;

		usleep_range(100, 200);
		/* Write the bytes to the new bank. */
		ret_val = e1000_retry_ग_लिखो_flash_byte_ich8lan(hw,
							       act_offset,
							       (u8)data);
		अगर (ret_val)
			अवरोध;

		usleep_range(100, 200);
		ret_val = e1000_retry_ग_लिखो_flash_byte_ich8lan(hw,
							       act_offset + 1,
							       (u8)(data >> 8));
		अगर (ret_val)
			अवरोध;
	पूर्ण

	/* Don't bother writing the segment valid bits अगर sector
	 * programming failed.
	 */
	अगर (ret_val) अणु
		/* Possibly पढ़ो-only, see e1000e_ग_लिखो_protect_nvm_ich8lan() */
		e_dbg("Flash commit failed.\n");
		जाओ release;
	पूर्ण

	/* Finally validate the new segment by setting bit 15:14
	 * to 10b in word 0x13 , this can be करोne without an
	 * erase as well since these bits are 11 to start with
	 * and we need to change bit 14 to 0b
	 */
	act_offset = new_bank_offset + E1000_ICH_NVM_SIG_WORD;
	ret_val = e1000_पढ़ो_flash_word_ich8lan(hw, act_offset, &data);
	अगर (ret_val)
		जाओ release;

	data &= 0xBFFF;
	ret_val = e1000_retry_ग_लिखो_flash_byte_ich8lan(hw,
						       act_offset * 2 + 1,
						       (u8)(data >> 8));
	अगर (ret_val)
		जाओ release;

	/* And invalidate the previously valid segment by setting
	 * its signature word (0x13) high_byte to 0b. This can be
	 * करोne without an erase because flash erase sets all bits
	 * to 1's. We can write 1's to 0's without an erase
	 */
	act_offset = (old_bank_offset + E1000_ICH_NVM_SIG_WORD) * 2 + 1;
	ret_val = e1000_retry_ग_लिखो_flash_byte_ich8lan(hw, act_offset, 0);
	अगर (ret_val)
		जाओ release;

	/* Great!  Everything worked, we can now clear the cached entries. */
	क्रम (i = 0; i < E1000_ICH8_SHADOW_RAM_WORDS; i++) अणु
		dev_spec->shaकरोw_ram[i].modअगरied = false;
		dev_spec->shaकरोw_ram[i].value = 0xFFFF;
	पूर्ण

release:
	nvm->ops.release(hw);

	/* Reload the EEPROM, or अन्यथा modअगरications will not appear
	 * until after the next adapter reset.
	 */
	अगर (!ret_val) अणु
		nvm->ops.reload(hw);
		usleep_range(10000, 11000);
	पूर्ण

out:
	अगर (ret_val)
		e_dbg("NVM update error: %d\n", ret_val);

	वापस ret_val;
पूर्ण

/**
 *  e1000_validate_nvm_checksum_ich8lan - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Check to see अगर checksum needs to be fixed by पढ़ोing bit 6 in word 0x19.
 *  If the bit is 0, that the EEPROM had been modअगरied, but the checksum was not
 *  calculated, in which हाल we need to calculate the checksum and set bit 6.
 **/
अटल s32 e1000_validate_nvm_checksum_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 data;
	u16 word;
	u16 valid_csum_mask;

	/* Read NVM and check Invalid Image CSUM bit.  If this bit is 0,
	 * the checksum needs to be fixed.  This bit is an indication that
	 * the NVM was prepared by OEM software and did not calculate
	 * the checksum...a likely scenario.
	 */
	चयन (hw->mac.type) अणु
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		word = NVM_COMPAT;
		valid_csum_mask = NVM_COMPAT_VALID_CSUM;
		अवरोध;
	शेष:
		word = NVM_FUTURE_INIT_WORD1;
		valid_csum_mask = NVM_FUTURE_INIT_WORD1_VALID_CSUM;
		अवरोध;
	पूर्ण

	ret_val = e1000_पढ़ो_nvm(hw, word, 1, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर (!(data & valid_csum_mask)) अणु
		data |= valid_csum_mask;
		ret_val = e1000_ग_लिखो_nvm(hw, word, 1, &data);
		अगर (ret_val)
			वापस ret_val;
		ret_val = e1000e_update_nvm_checksum(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस e1000e_validate_nvm_checksum_generic(hw);
पूर्ण

/**
 *  e1000e_ग_लिखो_protect_nvm_ich8lan - Make the NVM पढ़ो-only
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  To prevent malicious ग_लिखो/erase of the NVM, set it to be पढ़ो-only
 *  so that the hardware ignores all ग_लिखो/erase cycles of the NVM via
 *  the flash control रेजिस्टरs.  The shaकरोw-ram copy of the NVM will
 *  still be updated, however any updates to this copy will not stick
 *  across driver reloads.
 **/
व्योम e1000e_ग_लिखो_protect_nvm_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	जोड़ ich8_flash_रक्षित_range pr0;
	जोड़ ich8_hws_flash_status hsfsts;
	u32 gfpreg;

	nvm->ops.acquire(hw);

	gfpreg = er32flash(ICH_FLASH_GFPREG);

	/* Write-protect GbE Sector of NVM */
	pr0.regval = er32flash(ICH_FLASH_PR0);
	pr0.range.base = gfpreg & FLASH_GFPREG_BASE_MASK;
	pr0.range.limit = ((gfpreg >> 16) & FLASH_GFPREG_BASE_MASK);
	pr0.range.wpe = true;
	ew32flash(ICH_FLASH_PR0, pr0.regval);

	/* Lock करोwn a subset of GbE Flash Control Registers, e.g.
	 * PR0 to prevent the ग_लिखो-protection from being lअगरted.
	 * Once FLOCKDN is set, the रेजिस्टरs रक्षित by it cannot
	 * be written until FLOCKDN is cleared by a hardware reset.
	 */
	hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
	hsfsts.hsf_status.flockdn = true;
	ew32flash(ICH_FLASH_HSFSTS, hsfsts.regval);

	nvm->ops.release(hw);
पूर्ण

/**
 *  e1000_ग_लिखो_flash_data_ich8lan - Writes bytes to the NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset (in bytes) of the byte/word to पढ़ो.
 *  @size: Size of data to पढ़ो, 1=byte 2=word
 *  @data: The byte(s) to ग_लिखो to the NVM.
 *
 *  Writes one/two bytes to the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_ग_लिखो_flash_data_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					  u8 size, u16 data)
अणु
	जोड़ ich8_hws_flash_status hsfsts;
	जोड़ ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	u32 flash_data = 0;
	s32 ret_val;
	u8 count = 0;

	अगर (hw->mac.type >= e1000_pch_spt) अणु
		अगर (size != 4 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			वापस -E1000_ERR_NVM;
	पूर्ण अन्यथा अणु
		अगर (size < 1 || size > 2 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			वापस -E1000_ERR_NVM;
	पूर्ण

	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	करो अणु
		udelay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		अगर (ret_val)
			अवरोध;
		/* In SPT, This रेजिस्टर is in Lan memory space, not
		 * flash.  Thereक्रमe, only 32 bit access is supported
		 */
		अगर (hw->mac.type >= e1000_pch_spt)
			hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;
		अन्यथा
			hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);

		/* 0b/1b corresponds to 1 or 2 byte size, respectively. */
		hsflctl.hsf_ctrl.fldbcount = size - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_WRITE;
		/* In SPT, This रेजिस्टर is in Lan memory space,
		 * not flash.  Thereक्रमe, only 32 bit access is
		 * supported
		 */
		अगर (hw->mac.type >= e1000_pch_spt)
			ew32flash(ICH_FLASH_HSFSTS, hsflctl.regval << 16);
		अन्यथा
			ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		अगर (size == 1)
			flash_data = (u32)data & 0x00FF;
		अन्यथा
			flash_data = (u32)data;

		ew32flash(ICH_FLASH_FDATA0, flash_data);

		/* check अगर FCERR is set to 1 , अगर set to 1, clear it
		 * and try the whole sequence a few more बार अन्यथा करोne
		 */
		ret_val =
		    e1000_flash_cycle_ich8lan(hw,
					      ICH_FLASH_WRITE_COMMAND_TIMEOUT);
		अगर (!ret_val)
			अवरोध;

		/* If we're here, then things are most likely
		 * completely hosed, but अगर the error condition
		 * is detected, it won't hurt to give it another
		 * try...ICH_FLASH_CYCLE_REPEAT_COUNT बार.
		 */
		hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
		अगर (hsfsts.hsf_status.flcerr)
			/* Repeat क्रम some समय beक्रमe giving up. */
			जारी;
		अगर (!hsfsts.hsf_status.flcकरोne) अणु
			e_dbg("Timeout error - flash cycle did not complete.\n");
			अवरोध;
		पूर्ण
	पूर्ण जबतक (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	वापस ret_val;
पूर्ण

/**
*  e1000_ग_लिखो_flash_data32_ich8lan - Writes 4 bytes to the NVM
*  @hw: poपूर्णांकer to the HW काष्ठाure
*  @offset: The offset (in bytes) of the dwords to पढ़ो.
*  @data: The 4 bytes to ग_लिखो to the NVM.
*
*  Writes one/two/four bytes to the NVM using the flash access रेजिस्टरs.
**/
अटल s32 e1000_ग_लिखो_flash_data32_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					    u32 data)
अणु
	जोड़ ich8_hws_flash_status hsfsts;
	जोड़ ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	s32 ret_val;
	u8 count = 0;

	अगर (hw->mac.type >= e1000_pch_spt) अणु
		अगर (offset > ICH_FLASH_LINEAR_ADDR_MASK)
			वापस -E1000_ERR_NVM;
	पूर्ण
	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);
	करो अणु
		udelay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		अगर (ret_val)
			अवरोध;

		/* In SPT, This रेजिस्टर is in Lan memory space, not
		 * flash.  Thereक्रमe, only 32 bit access is supported
		 */
		अगर (hw->mac.type >= e1000_pch_spt)
			hsflctl.regval = er32flash(ICH_FLASH_HSFSTS)
			    >> 16;
		अन्यथा
			hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);

		hsflctl.hsf_ctrl.fldbcount = माप(u32) - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_WRITE;

		/* In SPT, This रेजिस्टर is in Lan memory space,
		 * not flash.  Thereक्रमe, only 32 bit access is
		 * supported
		 */
		अगर (hw->mac.type >= e1000_pch_spt)
			ew32flash(ICH_FLASH_HSFSTS, hsflctl.regval << 16);
		अन्यथा
			ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		ew32flash(ICH_FLASH_FDATA0, data);

		/* check अगर FCERR is set to 1 , अगर set to 1, clear it
		 * and try the whole sequence a few more बार अन्यथा करोne
		 */
		ret_val =
		   e1000_flash_cycle_ich8lan(hw,
					     ICH_FLASH_WRITE_COMMAND_TIMEOUT);

		अगर (!ret_val)
			अवरोध;

		/* If we're here, then things are most likely
		 * completely hosed, but अगर the error condition
		 * is detected, it won't hurt to give it another
		 * try...ICH_FLASH_CYCLE_REPEAT_COUNT बार.
		 */
		hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);

		अगर (hsfsts.hsf_status.flcerr)
			/* Repeat क्रम some समय beक्रमe giving up. */
			जारी;
		अगर (!hsfsts.hsf_status.flcकरोne) अणु
			e_dbg("Timeout error - flash cycle did not complete.\n");
			अवरोध;
		पूर्ण
	पूर्ण जबतक (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_flash_byte_ich8lan - Write a single byte to NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The index of the byte to पढ़ो.
 *  @data: The byte to ग_लिखो to the NVM.
 *
 *  Writes a single byte to the NVM using the flash access रेजिस्टरs.
 **/
अटल s32 e1000_ग_लिखो_flash_byte_ich8lan(काष्ठा e1000_hw *hw, u32 offset,
					  u8 data)
अणु
	u16 word = (u16)data;

	वापस e1000_ग_लिखो_flash_data_ich8lan(hw, offset, 1, word);
पूर्ण

/**
*  e1000_retry_ग_लिखो_flash_dword_ich8lan - Writes a dword to NVM
*  @hw: poपूर्णांकer to the HW काष्ठाure
*  @offset: The offset of the word to ग_लिखो.
*  @dword: The dword to ग_लिखो to the NVM.
*
*  Writes a single dword to the NVM using the flash access रेजिस्टरs.
*  Goes through a retry algorithm beक्रमe giving up.
**/
अटल s32 e1000_retry_ग_लिखो_flash_dword_ich8lan(काष्ठा e1000_hw *hw,
						 u32 offset, u32 dword)
अणु
	s32 ret_val;
	u16 program_retries;

	/* Must convert word offset पूर्णांकo bytes. */
	offset <<= 1;
	ret_val = e1000_ग_लिखो_flash_data32_ich8lan(hw, offset, dword);

	अगर (!ret_val)
		वापस ret_val;
	क्रम (program_retries = 0; program_retries < 100; program_retries++) अणु
		e_dbg("Retrying Byte %8.8X at offset %u\n", dword, offset);
		usleep_range(100, 200);
		ret_val = e1000_ग_लिखो_flash_data32_ich8lan(hw, offset, dword);
		अगर (!ret_val)
			अवरोध;
	पूर्ण
	अगर (program_retries == 100)
		वापस -E1000_ERR_NVM;

	वापस 0;
पूर्ण

/**
 *  e1000_retry_ग_लिखो_flash_byte_ich8lan - Writes a single byte to NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: The offset of the byte to ग_लिखो.
 *  @byte: The byte to ग_लिखो to the NVM.
 *
 *  Writes a single byte to the NVM using the flash access रेजिस्टरs.
 *  Goes through a retry algorithm beक्रमe giving up.
 **/
अटल s32 e1000_retry_ग_लिखो_flash_byte_ich8lan(काष्ठा e1000_hw *hw,
						u32 offset, u8 byte)
अणु
	s32 ret_val;
	u16 program_retries;

	ret_val = e1000_ग_लिखो_flash_byte_ich8lan(hw, offset, byte);
	अगर (!ret_val)
		वापस ret_val;

	क्रम (program_retries = 0; program_retries < 100; program_retries++) अणु
		e_dbg("Retrying Byte %2.2X at offset %u\n", byte, offset);
		usleep_range(100, 200);
		ret_val = e1000_ग_लिखो_flash_byte_ich8lan(hw, offset, byte);
		अगर (!ret_val)
			अवरोध;
	पूर्ण
	अगर (program_retries == 100)
		वापस -E1000_ERR_NVM;

	वापस 0;
पूर्ण

/**
 *  e1000_erase_flash_bank_ich8lan - Erase a bank (4k) from NVM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @bank: 0 क्रम first bank, 1 क्रम second bank, etc.
 *
 *  Erases the bank specअगरied. Each bank is a 4k block. Banks are 0 based.
 *  bank N is 4096 * N + flash_reg_addr.
 **/
अटल s32 e1000_erase_flash_bank_ich8lan(काष्ठा e1000_hw *hw, u32 bank)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	जोड़ ich8_hws_flash_status hsfsts;
	जोड़ ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	/* bank size is in 16bit words - adjust to bytes */
	u32 flash_bank_size = nvm->flash_bank_size * 2;
	s32 ret_val;
	s32 count = 0;
	s32 j, iteration, sector_size;

	hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);

	/* Determine HW Sector size: Read BERASE bits of hw flash status
	 * रेजिस्टर
	 * 00: The Hw sector is 256 bytes, hence we need to erase 16
	 *     consecutive sectors.  The start index क्रम the nth Hw sector
	 *     can be calculated as = bank * 4096 + n * 256
	 * 01: The Hw sector is 4K bytes, hence we need to erase 1 sector.
	 *     The start index क्रम the nth Hw sector can be calculated
	 *     as = bank * 4096
	 * 10: The Hw sector is 8K bytes, nth sector = bank * 8192
	 *     (ich9 only, otherwise error condition)
	 * 11: The Hw sector is 64K bytes, nth sector = bank * 65536
	 */
	चयन (hsfsts.hsf_status.berasesz) अणु
	हाल 0:
		/* Hw sector size 256 */
		sector_size = ICH_FLASH_SEG_SIZE_256;
		iteration = flash_bank_size / ICH_FLASH_SEG_SIZE_256;
		अवरोध;
	हाल 1:
		sector_size = ICH_FLASH_SEG_SIZE_4K;
		iteration = 1;
		अवरोध;
	हाल 2:
		sector_size = ICH_FLASH_SEG_SIZE_8K;
		iteration = 1;
		अवरोध;
	हाल 3:
		sector_size = ICH_FLASH_SEG_SIZE_64K;
		iteration = 1;
		अवरोध;
	शेष:
		वापस -E1000_ERR_NVM;
	पूर्ण

	/* Start with the base address, then add the sector offset. */
	flash_linear_addr = hw->nvm.flash_base_addr;
	flash_linear_addr += (bank) ? flash_bank_size : 0;

	क्रम (j = 0; j < iteration; j++) अणु
		करो अणु
			u32 समयout = ICH_FLASH_ERASE_COMMAND_TIMEOUT;

			/* Steps */
			ret_val = e1000_flash_cycle_init_ich8lan(hw);
			अगर (ret_val)
				वापस ret_val;

			/* Write a value 11 (block Erase) in Flash
			 * Cycle field in hw flash control
			 */
			अगर (hw->mac.type >= e1000_pch_spt)
				hsflctl.regval =
				    er32flash(ICH_FLASH_HSFSTS) >> 16;
			अन्यथा
				hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);

			hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_ERASE;
			अगर (hw->mac.type >= e1000_pch_spt)
				ew32flash(ICH_FLASH_HSFSTS,
					  hsflctl.regval << 16);
			अन्यथा
				ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

			/* Write the last 24 bits of an index within the
			 * block पूर्णांकo Flash Linear address field in Flash
			 * Address.
			 */
			flash_linear_addr += (j * sector_size);
			ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

			ret_val = e1000_flash_cycle_ich8lan(hw, समयout);
			अगर (!ret_val)
				अवरोध;

			/* Check अगर FCERR is set to 1.  If 1,
			 * clear it and try the whole sequence
			 * a few more बार अन्यथा Done
			 */
			hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
			अगर (hsfsts.hsf_status.flcerr)
				/* repeat क्रम some समय beक्रमe giving up */
				जारी;
			अन्यथा अगर (!hsfsts.hsf_status.flcकरोne)
				वापस ret_val;
		पूर्ण जबतक (++count < ICH_FLASH_CYCLE_REPEAT_COUNT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_valid_led_शेष_ich8lan - Set the शेष LED settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: Poपूर्णांकer to the LED settings
 *
 *  Reads the LED शेष settings from the NVM to data.  If the NVM LED
 *  settings is all 0's or F's, set the LED शेष to a valid LED शेष
 *  setting.
 **/
अटल s32 e1000_valid_led_शेष_ich8lan(काष्ठा e1000_hw *hw, u16 *data)
अणु
	s32 ret_val;

	ret_val = e1000_पढ़ो_nvm(hw, NVM_ID_LED_SETTINGS, 1, data);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF)
		*data = ID_LED_DEFAULT_ICH8LAN;

	वापस 0;
पूर्ण

/**
 *  e1000_id_led_init_pchlan - store LED configurations
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  PCH करोes not control LEDs via the LEDCTL रेजिस्टर, rather it uses
 *  the PHY LED configuration रेजिस्टर.
 *
 *  PCH also करोes not have an "always on" or "always off" mode which
 *  complicates the ID feature.  Instead of using the "on" mode to indicate
 *  in ledctl_mode2 the LEDs to use क्रम ID (see e1000e_id_led_init_generic()),
 *  use "link_up" mode.  The LEDs will still ID on request अगर there is no
 *  link based on logic in e1000_led_[on|off]_pchlan().
 **/
अटल s32 e1000_id_led_init_pchlan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	स्थिर u32 ledctl_on = E1000_LEDCTL_MODE_LINK_UP;
	स्थिर u32 ledctl_off = E1000_LEDCTL_MODE_LINK_UP | E1000_PHY_LED0_IVRT;
	u16 data, i, temp, shअगरt;

	/* Get शेष ID LED modes */
	ret_val = hw->nvm.ops.valid_led_शेष(hw, &data);
	अगर (ret_val)
		वापस ret_val;

	mac->ledctl_शेष = er32(LEDCTL);
	mac->ledctl_mode1 = mac->ledctl_शेष;
	mac->ledctl_mode2 = mac->ledctl_शेष;

	क्रम (i = 0; i < 4; i++) अणु
		temp = (data >> (i << 2)) & E1000_LEDCTL_LED0_MODE_MASK;
		shअगरt = (i * 5);
		चयन (temp) अणु
		हाल ID_LED_ON1_DEF2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_ON1_OFF2:
			mac->ledctl_mode1 &= ~(E1000_PHY_LED0_MASK << shअगरt);
			mac->ledctl_mode1 |= (ledctl_on << shअगरt);
			अवरोध;
		हाल ID_LED_OFF1_DEF2:
		हाल ID_LED_OFF1_ON2:
		हाल ID_LED_OFF1_OFF2:
			mac->ledctl_mode1 &= ~(E1000_PHY_LED0_MASK << shअगरt);
			mac->ledctl_mode1 |= (ledctl_off << shअगरt);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
		चयन (temp) अणु
		हाल ID_LED_DEF1_ON2:
		हाल ID_LED_ON1_ON2:
		हाल ID_LED_OFF1_ON2:
			mac->ledctl_mode2 &= ~(E1000_PHY_LED0_MASK << shअगरt);
			mac->ledctl_mode2 |= (ledctl_on << shअगरt);
			अवरोध;
		हाल ID_LED_DEF1_OFF2:
		हाल ID_LED_ON1_OFF2:
		हाल ID_LED_OFF1_OFF2:
			mac->ledctl_mode2 &= ~(E1000_PHY_LED0_MASK << shअगरt);
			mac->ledctl_mode2 |= (ledctl_off << shअगरt);
			अवरोध;
		शेष:
			/* Do nothing */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_get_bus_info_ich8lan - Get/Set the bus type and width
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  ICH8 use the PCI Express bus, but करोes not contain a PCI Express Capability
 *  रेजिस्टर, so the the bus width is hard coded.
 **/
अटल s32 e1000_get_bus_info_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_bus_info *bus = &hw->bus;
	s32 ret_val;

	ret_val = e1000e_get_bus_info_pcie(hw);

	/* ICH devices are "PCI Express"-ish.  They have
	 * a configuration space, but करो not contain
	 * PCI Express Capability रेजिस्टरs, so bus width
	 * must be hardcoded.
	 */
	अगर (bus->width == e1000_bus_width_unknown)
		bus->width = e1000_bus_width_pcie_x1;

	वापस ret_val;
पूर्ण

/**
 *  e1000_reset_hw_ich8lan - Reset the hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Does a full reset of the hardware which includes a reset of the PHY and
 *  MAC.
 **/
अटल s32 e1000_reset_hw_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u16 kum_cfg;
	u32 ctrl, reg;
	s32 ret_val;

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = e1000e_disable_pcie_master(hw);
	अगर (ret_val)
		e_dbg("PCI-E Master disable polling has failed.\n");

	e_dbg("Masking off all interrupts\n");
	ew32(IMC, 0xffffffff);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete beक्रमe we hit the MAC
	 * with the global reset.
	 */
	ew32(RCTL, 0);
	ew32(TCTL, E1000_TCTL_PSP);
	e1e_flush();

	usleep_range(10000, 11000);

	/* Workaround क्रम ICH8 bit corruption issue in FIFO memory */
	अगर (hw->mac.type == e1000_ich8lan) अणु
		/* Set Tx and Rx buffer allocation to 8k apiece. */
		ew32(PBA, E1000_PBA_8K);
		/* Set Packet Buffer Size to 16k. */
		ew32(PBS, E1000_PBS_16K);
	पूर्ण

	अगर (hw->mac.type == e1000_pchlan) अणु
		/* Save the NVM K1 bit setting */
		ret_val = e1000_पढ़ो_nvm(hw, E1000_NVM_K1_CONFIG, 1, &kum_cfg);
		अगर (ret_val)
			वापस ret_val;

		अगर (kum_cfg & E1000_NVM_K1_ENABLE)
			dev_spec->nvm_k1_enabled = true;
		अन्यथा
			dev_spec->nvm_k1_enabled = false;
	पूर्ण

	ctrl = er32(CTRL);

	अगर (!hw->phy.ops.check_reset_block(hw)) अणु
		/* Full-chip reset requires MAC and PHY reset at the same
		 * समय to make sure the पूर्णांकerface between MAC and the
		 * बाह्यal PHY is reset.
		 */
		ctrl |= E1000_CTRL_PHY_RST;

		/* Gate स्वतःmatic PHY configuration by hardware on
		 * non-managed 82579
		 */
		अगर ((hw->mac.type == e1000_pch2lan) &&
		    !(er32(FWSM) & E1000_ICH_FWSM_FW_VALID))
			e1000_gate_hw_phy_config_ich8lan(hw, true);
	पूर्ण
	ret_val = e1000_acquire_swflag_ich8lan(hw);
	e_dbg("Issuing a global reset to ich8lan\n");
	ew32(CTRL, (ctrl | E1000_CTRL_RST));
	/* cannot issue a flush here because it hangs the hardware */
	msleep(20);

	/* Set Phy Config Counter to 50msec */
	अगर (hw->mac.type == e1000_pch2lan) अणु
		reg = er32(FEXTNVM3);
		reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
		reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
		ew32(FEXTNVM3, reg);
	पूर्ण

	अगर (!ret_val)
		clear_bit(__E1000_ACCESS_SHARED_RESOURCE, &hw->adapter->state);

	अगर (ctrl & E1000_CTRL_PHY_RST) अणु
		ret_val = hw->phy.ops.get_cfg_करोne(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1000_post_phy_reset_ich8lan(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* For PCH, this ग_लिखो will make sure that any noise
	 * will be detected as a CRC error and be dropped rather than show up
	 * as a bad packet to the DMA engine.
	 */
	अगर (hw->mac.type == e1000_pchlan)
		ew32(CRC_OFFSET, 0x65656565);

	ew32(IMC, 0xffffffff);
	er32(ICR);

	reg = er32(KABGTXD);
	reg |= E1000_KABGTXD_BGSQLBIAS;
	ew32(KABGTXD, reg);

	वापस 0;
पूर्ण

/**
 *  e1000_init_hw_ich8lan - Initialize the hardware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Prepares the hardware क्रम transmit and receive by करोing the following:
 *   - initialize hardware bits
 *   - initialize LED identअगरication
 *   - setup receive address रेजिस्टरs
 *   - setup flow control
 *   - setup transmit descriptors
 *   - clear statistics
 **/
अटल s32 e1000_init_hw_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 ctrl_ext, txdctl, snoop;
	s32 ret_val;
	u16 i;

	e1000_initialize_hw_bits_ich8lan(hw);

	/* Initialize identअगरication LED */
	ret_val = mac->ops.id_led_init(hw);
	/* An error is not fatal and we should not stop init due to this */
	अगर (ret_val)
		e_dbg("Error initializing identification LED\n");

	/* Setup the receive address. */
	e1000e_init_rx_addrs(hw, mac->rar_entry_count);

	/* Zero out the Multicast HASH table */
	e_dbg("Zeroing the MTA\n");
	क्रम (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/* The 82578 Rx buffer will stall अगर wakeup is enabled in host and
	 * the ME.  Disable wakeup by clearing the host wakeup bit.
	 * Reset the phy after disabling host wakeup to reset the Rx buffer.
	 */
	अगर (hw->phy.type == e1000_phy_82578) अणु
		e1e_rphy(hw, BM_PORT_GEN_CFG, &i);
		i &= ~BM_WUC_HOST_WU_BIT;
		e1e_wphy(hw, BM_PORT_GEN_CFG, i);
		ret_val = e1000_phy_hw_reset_ich8lan(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);

	/* Set the transmit descriptor ग_लिखो-back policy क्रम both queues */
	txdctl = er32(TXDCTL(0));
	txdctl = ((txdctl & ~E1000_TXDCTL_WTHRESH) |
		  E1000_TXDCTL_FULL_TX_DESC_WB);
	txdctl = ((txdctl & ~E1000_TXDCTL_PTHRESH) |
		  E1000_TXDCTL_MAX_TX_DESC_PREFETCH);
	ew32(TXDCTL(0), txdctl);
	txdctl = er32(TXDCTL(1));
	txdctl = ((txdctl & ~E1000_TXDCTL_WTHRESH) |
		  E1000_TXDCTL_FULL_TX_DESC_WB);
	txdctl = ((txdctl & ~E1000_TXDCTL_PTHRESH) |
		  E1000_TXDCTL_MAX_TX_DESC_PREFETCH);
	ew32(TXDCTL(1), txdctl);

	/* ICH8 has opposite polarity of no_snoop bits.
	 * By शेष, we should use snoop behavior.
	 */
	अगर (mac->type == e1000_ich8lan)
		snoop = PCIE_ICH8_SNOOP_ALL;
	अन्यथा
		snoop = (u32)~(PCIE_NO_SNOOP_ALL);
	e1000e_set_pcie_no_snoop(hw, snoop);

	ctrl_ext = er32(CTRL_EXT);
	ctrl_ext |= E1000_CTRL_EXT_RO_DIS;
	ew32(CTRL_EXT, ctrl_ext);

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_ich8lan(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_initialize_hw_bits_ich8lan - Initialize required hardware bits
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets/Clears required hardware bits necessary क्रम correctly setting up the
 *  hardware क्रम transmit and receive.
 **/
अटल व्योम e1000_initialize_hw_bits_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 reg;

	/* Extended Device Control */
	reg = er32(CTRL_EXT);
	reg |= BIT(22);
	/* Enable PHY low-घातer state when MAC is at D3 w/o WoL */
	अगर (hw->mac.type >= e1000_pchlan)
		reg |= E1000_CTRL_EXT_PHYPDEN;
	ew32(CTRL_EXT, reg);

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
	अगर (hw->mac.type == e1000_ich8lan)
		reg |= BIT(28) | BIT(29);
	reg |= BIT(23) | BIT(24) | BIT(26) | BIT(27);
	ew32(TARC(0), reg);

	/* Transmit Arbitration Control 1 */
	reg = er32(TARC(1));
	अगर (er32(TCTL) & E1000_TCTL_MULR)
		reg &= ~BIT(28);
	अन्यथा
		reg |= BIT(28);
	reg |= BIT(24) | BIT(26) | BIT(30);
	ew32(TARC(1), reg);

	/* Device Status */
	अगर (hw->mac.type == e1000_ich8lan) अणु
		reg = er32(STATUS);
		reg &= ~BIT(31);
		ew32(STATUS, reg);
	पूर्ण

	/* work-around descriptor data corruption issue during nfs v2 udp
	 * traffic, just disable the nfs filtering capability
	 */
	reg = er32(RFCTL);
	reg |= (E1000_RFCTL_NFSW_DIS | E1000_RFCTL_NFSR_DIS);

	/* Disable IPv6 extension header parsing because some malक्रमmed
	 * IPv6 headers can hang the Rx.
	 */
	अगर (hw->mac.type == e1000_ich8lan)
		reg |= (E1000_RFCTL_IPV6_EX_DIS | E1000_RFCTL_NEW_IPV6_EXT_DIS);
	ew32(RFCTL, reg);

	/* Enable ECC on Lynxpoपूर्णांक */
	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		reg = er32(PBECCSTS);
		reg |= E1000_PBECCSTS_ECC_ENABLE;
		ew32(PBECCSTS, reg);

		reg = er32(CTRL);
		reg |= E1000_CTRL_MEHE;
		ew32(CTRL, reg);
	पूर्ण
पूर्ण

/**
 *  e1000_setup_link_ich8lan - Setup flow control and link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Determines which flow control settings to use, then configures flow
 *  control.  Calls the appropriate media-specअगरic link configuration
 *  function.  Assuming the adapter has a valid link partner, a valid link
 *  should be established.  Assumes the hardware has previously been reset
 *  and the transmitter and receiver are not enabled.
 **/
अटल s32 e1000_setup_link_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	अगर (hw->phy.ops.check_reset_block(hw))
		वापस 0;

	/* ICH parts करो not have a word in the NVM to determine
	 * the शेष flow control setting, so we explicitly
	 * set it to full.
	 */
	अगर (hw->fc.requested_mode == e1000_fc_शेष) अणु
		/* Workaround h/w hang when Tx flow control enabled */
		अगर (hw->mac.type == e1000_pchlan)
			hw->fc.requested_mode = e1000_fc_rx_छोड़ो;
		अन्यथा
			hw->fc.requested_mode = e1000_fc_full;
	पूर्ण

	/* Save off the requested flow control mode क्रम use later.  Depending
	 * on the link partner's capabilities, we may or may not use this mode.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	e_dbg("After fix-ups FlowControl is now = %x\n", hw->fc.current_mode);

	/* Continue to configure the copper link. */
	ret_val = hw->mac.ops.setup_physical_पूर्णांकerface(hw);
	अगर (ret_val)
		वापस ret_val;

	ew32(FCTTV, hw->fc.छोड़ो_समय);
	अगर ((hw->phy.type == e1000_phy_82578) ||
	    (hw->phy.type == e1000_phy_82579) ||
	    (hw->phy.type == e1000_phy_i217) ||
	    (hw->phy.type == e1000_phy_82577)) अणु
		ew32(FCRTV_PCH, hw->fc.refresh_समय);

		ret_val = e1e_wphy(hw, PHY_REG(BM_PORT_CTRL_PAGE, 27),
				   hw->fc.छोड़ो_समय);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस e1000e_set_fc_watermarks(hw);
पूर्ण

/**
 *  e1000_setup_copper_link_ich8lan - Configure MAC/PHY पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Configures the kumeran पूर्णांकerface to the PHY to रुको the appropriate समय
 *  when polling the PHY, then call the generic setup_copper_link to finish
 *  configuring the copper link.
 **/
अटल s32 e1000_setup_copper_link_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;
	u16 reg_data;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ew32(CTRL, ctrl);

	/* Set the mac to रुको the maximum समय between each iteration
	 * and increase the max iterations when polling the phy;
	 * this fixes erroneous समयouts at 10Mbps.
	 */
	ret_val = e1000e_ग_लिखो_kmrn_reg(hw, E1000_KMRNCTRLSTA_TIMEOUTS, 0xFFFF);
	अगर (ret_val)
		वापस ret_val;
	ret_val = e1000e_पढ़ो_kmrn_reg(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
				       &reg_data);
	अगर (ret_val)
		वापस ret_val;
	reg_data |= 0x3F;
	ret_val = e1000e_ग_लिखो_kmrn_reg(hw, E1000_KMRNCTRLSTA_INBAND_PARAM,
					reg_data);
	अगर (ret_val)
		वापस ret_val;

	चयन (hw->phy.type) अणु
	हाल e1000_phy_igp_3:
		ret_val = e1000e_copper_link_setup_igp(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	हाल e1000_phy_bm:
	हाल e1000_phy_82578:
		ret_val = e1000e_copper_link_setup_m88(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	हाल e1000_phy_82577:
	हाल e1000_phy_82579:
		ret_val = e1000_copper_link_setup_82577(hw);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	हाल e1000_phy_अगरe:
		ret_val = e1e_rphy(hw, IFE_PHY_MDIX_CONTROL, &reg_data);
		अगर (ret_val)
			वापस ret_val;

		reg_data &= ~IFE_PMC_AUTO_MDIX;

		चयन (hw->phy.mdix) अणु
		हाल 1:
			reg_data &= ~IFE_PMC_FORCE_MDIX;
			अवरोध;
		हाल 2:
			reg_data |= IFE_PMC_FORCE_MDIX;
			अवरोध;
		हाल 0:
		शेष:
			reg_data |= IFE_PMC_AUTO_MDIX;
			अवरोध;
		पूर्ण
		ret_val = e1e_wphy(hw, IFE_PHY_MDIX_CONTROL, reg_data);
		अगर (ret_val)
			वापस ret_val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस e1000e_setup_copper_link(hw);
पूर्ण

/**
 *  e1000_setup_copper_link_pch_lpt - Configure MAC/PHY पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY specअगरic link setup function and then calls the
 *  generic setup_copper_link to finish configuring the link क्रम
 *  Lynxpoपूर्णांक PCH devices
 **/
अटल s32 e1000_setup_copper_link_pch_lpt(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl;
	s32 ret_val;

	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_SLU;
	ctrl &= ~(E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ew32(CTRL, ctrl);

	ret_val = e1000_copper_link_setup_82577(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस e1000e_setup_copper_link(hw);
पूर्ण

/**
 *  e1000_get_link_up_info_ich8lan - Get current link speed and duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @speed: poपूर्णांकer to store current link speed
 *  @duplex: poपूर्णांकer to store the current link duplex
 *
 *  Calls the generic get_speed_and_duplex to retrieve the current link
 *  inक्रमmation and then calls the Kumeran lock loss workaround क्रम links at
 *  gigabit speeds.
 **/
अटल s32 e1000_get_link_up_info_ich8lan(काष्ठा e1000_hw *hw, u16 *speed,
					  u16 *duplex)
अणु
	s32 ret_val;

	ret_val = e1000e_get_speed_and_duplex_copper(hw, speed, duplex);
	अगर (ret_val)
		वापस ret_val;

	अगर ((hw->mac.type == e1000_ich8lan) &&
	    (hw->phy.type == e1000_phy_igp_3) && (*speed == SPEED_1000)) अणु
		ret_val = e1000_kmrn_lock_loss_workaround_ich8lan(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_kmrn_lock_loss_workaround_ich8lan - Kumeran workaround
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Work-around क्रम 82566 Kumeran PCS lock loss:
 *  On link status change (i.e. PCI reset, speed change) and link is up and
 *  speed is gigabit-
 *    0) अगर workaround is optionally disabled करो nothing
 *    1) रुको 1ms क्रम Kumeran link to come up
 *    2) check Kumeran Diagnostic रेजिस्टर PCS lock loss bit
 *    3) अगर not set the link is locked (all is good), otherwise...
 *    4) reset the PHY
 *    5) repeat up to 10 बार
 *  Note: this is only called क्रम IGP3 copper when speed is 1gb.
 **/
अटल s32 e1000_kmrn_lock_loss_workaround_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 phy_ctrl;
	s32 ret_val;
	u16 i, data;
	bool link;

	अगर (!dev_spec->kmrn_lock_loss_workaround_enabled)
		वापस 0;

	/* Make sure link is up beक्रमe proceeding.  If not just वापस.
	 * Attempting this जबतक link is negotiating fouled up link
	 * stability
	 */
	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (!link)
		वापस 0;

	क्रम (i = 0; i < 10; i++) अणु
		/* पढ़ो once to clear */
		ret_val = e1e_rphy(hw, IGP3_KMRN_DIAG, &data);
		अगर (ret_val)
			वापस ret_val;
		/* and again to get new status */
		ret_val = e1e_rphy(hw, IGP3_KMRN_DIAG, &data);
		अगर (ret_val)
			वापस ret_val;

		/* check क्रम PCS lock */
		अगर (!(data & IGP3_KMRN_DIAG_PCS_LOCK_LOSS))
			वापस 0;

		/* Issue PHY reset */
		e1000_phy_hw_reset(hw);
		mdelay(5);
	पूर्ण
	/* Disable GigE link negotiation */
	phy_ctrl = er32(PHY_CTRL);
	phy_ctrl |= (E1000_PHY_CTRL_GBE_DISABLE |
		     E1000_PHY_CTRL_NOND0A_GBE_DISABLE);
	ew32(PHY_CTRL, phy_ctrl);

	/* Call gig speed drop workaround on Gig disable beक्रमe accessing
	 * any PHY रेजिस्टरs
	 */
	e1000e_gig_करोwnshअगरt_workaround_ich8lan(hw);

	/* unable to acquire PCS lock */
	वापस -E1000_ERR_PHY;
पूर्ण

/**
 *  e1000e_set_kmrn_lock_loss_workaround_ich8lan - Set Kumeran workaround state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @state: boolean value used to set the current Kumeran workaround state
 *
 *  If ICH8, set the current Kumeran workaround state (enabled - true
 *  /disabled - false).
 **/
व्योम e1000e_set_kmrn_lock_loss_workaround_ich8lan(काष्ठा e1000_hw *hw,
						  bool state)
अणु
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;

	अगर (hw->mac.type != e1000_ich8lan) अणु
		e_dbg("Workaround applies to ICH8 only.\n");
		वापस;
	पूर्ण

	dev_spec->kmrn_lock_loss_workaround_enabled = state;
पूर्ण

/**
 *  e1000e_igp3_phy_घातerकरोwn_workaround_ich8lan - Power करोwn workaround on D3
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Workaround क्रम 82566 घातer-करोwn on D3 entry:
 *    1) disable gigabit link
 *    2) ग_लिखो VR घातer-करोwn enable
 *    3) पढ़ो it back
 *  Continue अगर successful, अन्यथा issue LCD reset and repeat
 **/
व्योम e1000e_igp3_phy_घातerकरोwn_workaround_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u32 reg;
	u16 data;
	u8 retry = 0;

	अगर (hw->phy.type != e1000_phy_igp_3)
		वापस;

	/* Try the workaround twice (अगर needed) */
	करो अणु
		/* Disable link */
		reg = er32(PHY_CTRL);
		reg |= (E1000_PHY_CTRL_GBE_DISABLE |
			E1000_PHY_CTRL_NOND0A_GBE_DISABLE);
		ew32(PHY_CTRL, reg);

		/* Call gig speed drop workaround on Gig disable beक्रमe
		 * accessing any PHY रेजिस्टरs
		 */
		अगर (hw->mac.type == e1000_ich8lan)
			e1000e_gig_करोwnshअगरt_workaround_ich8lan(hw);

		/* Write VR घातer-करोwn enable */
		e1e_rphy(hw, IGP3_VR_CTRL, &data);
		data &= ~IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK;
		e1e_wphy(hw, IGP3_VR_CTRL, data | IGP3_VR_CTRL_MODE_SHUTDOWN);

		/* Read it back and test */
		e1e_rphy(hw, IGP3_VR_CTRL, &data);
		data &= IGP3_VR_CTRL_DEV_POWERDOWN_MODE_MASK;
		अगर ((data == IGP3_VR_CTRL_MODE_SHUTDOWN) || retry)
			अवरोध;

		/* Issue PHY reset and repeat at most one more समय */
		reg = er32(CTRL);
		ew32(CTRL, reg | E1000_CTRL_PHY_RST);
		retry++;
	पूर्ण जबतक (retry);
पूर्ण

/**
 *  e1000e_gig_करोwnshअगरt_workaround_ich8lan - WoL from S5 stops working
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Steps to take when dropping from 1Gb/s (eg. link cable removal (LSC),
 *  LPLU, Gig disable, MDIC PHY reset):
 *    1) Set Kumeran Near-end loopback
 *    2) Clear Kumeran Near-end loopback
 *  Should only be called क्रम ICH8[m] devices with any 1G Phy.
 **/
व्योम e1000e_gig_करोwnshअगरt_workaround_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 reg_data;

	अगर ((hw->mac.type != e1000_ich8lan) || (hw->phy.type == e1000_phy_अगरe))
		वापस;

	ret_val = e1000e_पढ़ो_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET,
				       &reg_data);
	अगर (ret_val)
		वापस;
	reg_data |= E1000_KMRNCTRLSTA_DIAG_NELPBK;
	ret_val = e1000e_ग_लिखो_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET,
					reg_data);
	अगर (ret_val)
		वापस;
	reg_data &= ~E1000_KMRNCTRLSTA_DIAG_NELPBK;
	e1000e_ग_लिखो_kmrn_reg(hw, E1000_KMRNCTRLSTA_DIAG_OFFSET, reg_data);
पूर्ण

/**
 *  e1000_suspend_workarounds_ich8lan - workarounds needed during S0->Sx
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  During S0 to Sx transition, it is possible the link reमुख्यs at gig
 *  instead of negotiating to a lower speed.  Beक्रमe going to Sx, set
 *  'Gig Disable' to क्रमce link speed negotiation to a lower speed based on
 *  the LPLU setting in the NVM or custom setting.  For PCH and newer parts,
 *  the OEM bits PHY रेजिस्टर (LED, GbE disable and LPLU configurations) also
 *  needs to be written.
 *  Parts that support (and are linked to a partner which support) EEE in
 *  100Mbps should disable LPLU since 100Mbps w/ EEE requires less घातer
 *  than 10Mbps w/o EEE.
 **/
व्योम e1000_suspend_workarounds_ich8lan(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 phy_ctrl;
	s32 ret_val;

	phy_ctrl = er32(PHY_CTRL);
	phy_ctrl |= E1000_PHY_CTRL_GBE_DISABLE;

	अगर (hw->phy.type == e1000_phy_i217) अणु
		u16 phy_reg, device_id = hw->adapter->pdev->device;

		अगर ((device_id == E1000_DEV_ID_PCH_LPTLP_I218_LM) ||
		    (device_id == E1000_DEV_ID_PCH_LPTLP_I218_V) ||
		    (device_id == E1000_DEV_ID_PCH_I218_LM3) ||
		    (device_id == E1000_DEV_ID_PCH_I218_V3) ||
		    (hw->mac.type >= e1000_pch_spt)) अणु
			u32 fextnvm6 = er32(FEXTNVM6);

			ew32(FEXTNVM6, fextnvm6 & ~E1000_FEXTNVM6_REQ_PLL_CLK);
		पूर्ण

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			जाओ out;

		अगर (!dev_spec->eee_disable) अणु
			u16 eee_advert;

			ret_val =
			    e1000_पढ़ो_emi_reg_locked(hw,
						      I217_EEE_ADVERTISEMENT,
						      &eee_advert);
			अगर (ret_val)
				जाओ release;

			/* Disable LPLU अगर both link partners support 100BaseT
			 * EEE and 100Full is advertised on both ends of the
			 * link, and enable Auto Enable LPI since there will
			 * be no driver to enable LPI जबतक in Sx.
			 */
			अगर ((eee_advert & I82579_EEE_100_SUPPORTED) &&
			    (dev_spec->eee_lp_ability &
			     I82579_EEE_100_SUPPORTED) &&
			    (hw->phy.स्वतःneg_advertised & ADVERTISE_100_FULL)) अणु
				phy_ctrl &= ~(E1000_PHY_CTRL_D0A_LPLU |
					      E1000_PHY_CTRL_NOND0A_LPLU);

				/* Set Auto Enable LPI after link up */
				e1e_rphy_locked(hw,
						I217_LPI_GPIO_CTRL, &phy_reg);
				phy_reg |= I217_LPI_GPIO_CTRL_AUTO_EN_LPI;
				e1e_wphy_locked(hw,
						I217_LPI_GPIO_CTRL, phy_reg);
			पूर्ण
		पूर्ण

		/* For i217 Intel Rapid Start Technology support,
		 * when the प्रणाली is going पूर्णांकo Sx and no manageability engine
		 * is present, the driver must configure proxy to reset only on
		 * घातer good.  LPI (Low Power Idle) state must also reset only
		 * on घातer good, as well as the MTA (Multicast table array).
		 * The SMBus release must also be disabled on LCD reset.
		 */
		अगर (!(er32(FWSM) & E1000_ICH_FWSM_FW_VALID)) अणु
			/* Enable proxy to reset only on घातer good. */
			e1e_rphy_locked(hw, I217_PROXY_CTRL, &phy_reg);
			phy_reg |= I217_PROXY_CTRL_AUTO_DISABLE;
			e1e_wphy_locked(hw, I217_PROXY_CTRL, phy_reg);

			/* Set bit enable LPI (EEE) to reset only on
			 * घातer good.
			 */
			e1e_rphy_locked(hw, I217_SxCTRL, &phy_reg);
			phy_reg |= I217_SxCTRL_ENABLE_LPI_RESET;
			e1e_wphy_locked(hw, I217_SxCTRL, phy_reg);

			/* Disable the SMB release on LCD reset. */
			e1e_rphy_locked(hw, I217_MEMPWR, &phy_reg);
			phy_reg &= ~I217_MEMPWR_DISABLE_SMB_RELEASE;
			e1e_wphy_locked(hw, I217_MEMPWR, phy_reg);
		पूर्ण

		/* Enable MTA to reset क्रम Intel Rapid Start Technology
		 * Support
		 */
		e1e_rphy_locked(hw, I217_CGFREG, &phy_reg);
		phy_reg |= I217_CGFREG_ENABLE_MTA_RESET;
		e1e_wphy_locked(hw, I217_CGFREG, phy_reg);

release:
		hw->phy.ops.release(hw);
	पूर्ण
out:
	ew32(PHY_CTRL, phy_ctrl);

	अगर (hw->mac.type == e1000_ich8lan)
		e1000e_gig_करोwnshअगरt_workaround_ich8lan(hw);

	अगर (hw->mac.type >= e1000_pchlan) अणु
		e1000_oem_bits_config_ich8lan(hw, false);

		/* Reset PHY to activate OEM bits on 82577/8 */
		अगर (hw->mac.type == e1000_pchlan)
			e1000e_phy_hw_reset_generic(hw);

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस;
		e1000_ग_लिखो_smbus_addr(hw);
		hw->phy.ops.release(hw);
	पूर्ण
पूर्ण

/**
 *  e1000_resume_workarounds_pchlan - workarounds needed during Sx->S0
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  During Sx to S0 transitions on non-managed devices or managed devices
 *  on which PHY resets are not blocked, अगर the PHY रेजिस्टरs cannot be
 *  accessed properly by the s/w toggle the LANPHYPC value to घातer cycle
 *  the PHY.
 *  On i217, setup Intel Rapid Start Technology.
 **/
व्योम e1000_resume_workarounds_pchlan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	अगर (hw->mac.type < e1000_pch2lan)
		वापस;

	ret_val = e1000_init_phy_workarounds_pchlan(hw);
	अगर (ret_val) अणु
		e_dbg("Failed to init PHY flow ret_val=%d\n", ret_val);
		वापस;
	पूर्ण

	/* For i217 Intel Rapid Start Technology support when the प्रणाली
	 * is transitioning from Sx and no manageability engine is present
	 * configure SMBus to restore on reset, disable proxy, and enable
	 * the reset on MTA (Multicast table array).
	 */
	अगर (hw->phy.type == e1000_phy_i217) अणु
		u16 phy_reg;

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val) अणु
			e_dbg("Failed to setup iRST\n");
			वापस;
		पूर्ण

		/* Clear Auto Enable LPI after link up */
		e1e_rphy_locked(hw, I217_LPI_GPIO_CTRL, &phy_reg);
		phy_reg &= ~I217_LPI_GPIO_CTRL_AUTO_EN_LPI;
		e1e_wphy_locked(hw, I217_LPI_GPIO_CTRL, phy_reg);

		अगर (!(er32(FWSM) & E1000_ICH_FWSM_FW_VALID)) अणु
			/* Restore clear on SMB अगर no manageability engine
			 * is present
			 */
			ret_val = e1e_rphy_locked(hw, I217_MEMPWR, &phy_reg);
			अगर (ret_val)
				जाओ release;
			phy_reg |= I217_MEMPWR_DISABLE_SMB_RELEASE;
			e1e_wphy_locked(hw, I217_MEMPWR, phy_reg);

			/* Disable Proxy */
			e1e_wphy_locked(hw, I217_PROXY_CTRL, 0);
		पूर्ण
		/* Enable reset on MTA */
		ret_val = e1e_rphy_locked(hw, I217_CGFREG, &phy_reg);
		अगर (ret_val)
			जाओ release;
		phy_reg &= ~I217_CGFREG_ENABLE_MTA_RESET;
		e1e_wphy_locked(hw, I217_CGFREG, phy_reg);
release:
		अगर (ret_val)
			e_dbg("Error %d in resume workarounds\n", ret_val);
		hw->phy.ops.release(hw);
	पूर्ण
पूर्ण

/**
 *  e1000_cleanup_led_ich8lan - Restore the शेष LED operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Return the LED back to the शेष configuration.
 **/
अटल s32 e1000_cleanup_led_ich8lan(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->phy.type == e1000_phy_अगरe)
		वापस e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED, 0);

	ew32(LEDCTL, hw->mac.ledctl_शेष);
	वापस 0;
पूर्ण

/**
 *  e1000_led_on_ich8lan - Turn LEDs on
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn on the LEDs.
 **/
अटल s32 e1000_led_on_ich8lan(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->phy.type == e1000_phy_अगरe)
		वापस e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED,
				(IFE_PSCL_PROBE_MODE | IFE_PSCL_PROBE_LEDS_ON));

	ew32(LEDCTL, hw->mac.ledctl_mode2);
	वापस 0;
पूर्ण

/**
 *  e1000_led_off_ich8lan - Turn LEDs off
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn off the LEDs.
 **/
अटल s32 e1000_led_off_ich8lan(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->phy.type == e1000_phy_अगरe)
		वापस e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED,
				(IFE_PSCL_PROBE_MODE |
				 IFE_PSCL_PROBE_LEDS_OFF));

	ew32(LEDCTL, hw->mac.ledctl_mode1);
	वापस 0;
पूर्ण

/**
 *  e1000_setup_led_pchlan - Configures SW controllable LED
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This prepares the SW controllable LED क्रम use.
 **/
अटल s32 e1000_setup_led_pchlan(काष्ठा e1000_hw *hw)
अणु
	वापस e1e_wphy(hw, HV_LED_CONFIG, (u16)hw->mac.ledctl_mode1);
पूर्ण

/**
 *  e1000_cleanup_led_pchlan - Restore the शेष LED operation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Return the LED back to the शेष configuration.
 **/
अटल s32 e1000_cleanup_led_pchlan(काष्ठा e1000_hw *hw)
अणु
	वापस e1e_wphy(hw, HV_LED_CONFIG, (u16)hw->mac.ledctl_शेष);
पूर्ण

/**
 *  e1000_led_on_pchlan - Turn LEDs on
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn on the LEDs.
 **/
अटल s32 e1000_led_on_pchlan(काष्ठा e1000_hw *hw)
अणु
	u16 data = (u16)hw->mac.ledctl_mode2;
	u32 i, led;

	/* If no link, then turn LED on by setting the invert bit
	 * क्रम each LED that's mode is "link_up" in ledctl_mode2.
	 */
	अगर (!(er32(STATUS) & E1000_STATUS_LU)) अणु
		क्रम (i = 0; i < 3; i++) अणु
			led = (data >> (i * 5)) & E1000_PHY_LED0_MASK;
			अगर ((led & E1000_PHY_LED0_MODE_MASK) !=
			    E1000_LEDCTL_MODE_LINK_UP)
				जारी;
			अगर (led & E1000_PHY_LED0_IVRT)
				data &= ~(E1000_PHY_LED0_IVRT << (i * 5));
			अन्यथा
				data |= (E1000_PHY_LED0_IVRT << (i * 5));
		पूर्ण
	पूर्ण

	वापस e1e_wphy(hw, HV_LED_CONFIG, data);
पूर्ण

/**
 *  e1000_led_off_pchlan - Turn LEDs off
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Turn off the LEDs.
 **/
अटल s32 e1000_led_off_pchlan(काष्ठा e1000_hw *hw)
अणु
	u16 data = (u16)hw->mac.ledctl_mode1;
	u32 i, led;

	/* If no link, then turn LED off by clearing the invert bit
	 * क्रम each LED that's mode is "link_up" in ledctl_mode1.
	 */
	अगर (!(er32(STATUS) & E1000_STATUS_LU)) अणु
		क्रम (i = 0; i < 3; i++) अणु
			led = (data >> (i * 5)) & E1000_PHY_LED0_MASK;
			अगर ((led & E1000_PHY_LED0_MODE_MASK) !=
			    E1000_LEDCTL_MODE_LINK_UP)
				जारी;
			अगर (led & E1000_PHY_LED0_IVRT)
				data &= ~(E1000_PHY_LED0_IVRT << (i * 5));
			अन्यथा
				data |= (E1000_PHY_LED0_IVRT << (i * 5));
		पूर्ण
	पूर्ण

	वापस e1e_wphy(hw, HV_LED_CONFIG, data);
पूर्ण

/**
 *  e1000_get_cfg_करोne_ich8lan - Read config करोne bit after Full or PHY reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read appropriate रेजिस्टर क्रम the config करोne bit क्रम completion status
 *  and configure the PHY through s/w क्रम EEPROM-less parts.
 *
 *  NOTE: some silicon which is EEPROM-less will fail trying to पढ़ो the
 *  config करोne bit, so only an error is logged and जारीs.  If we were
 *  to वापस with error, EEPROM-less silicon would not be able to be reset
 *  or change link.
 **/
अटल s32 e1000_get_cfg_करोne_ich8lan(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u32 bank = 0;
	u32 status;

	e1000e_get_cfg_करोne_generic(hw);

	/* Wait क्रम indication from h/w that it has completed basic config */
	अगर (hw->mac.type >= e1000_ich10lan) अणु
		e1000_lan_init_करोne_ich8lan(hw);
	पूर्ण अन्यथा अणु
		ret_val = e1000e_get_स्वतः_rd_करोne(hw);
		अगर (ret_val) अणु
			/* When स्वतः config पढ़ो करोes not complete, करो not
			 * वापस with an error. This can happen in situations
			 * where there is no eeprom and prevents getting link.
			 */
			e_dbg("Auto Read Done did not complete\n");
			ret_val = 0;
		पूर्ण
	पूर्ण

	/* Clear PHY Reset Asserted bit */
	status = er32(STATUS);
	अगर (status & E1000_STATUS_PHYRA)
		ew32(STATUS, status & ~E1000_STATUS_PHYRA);
	अन्यथा
		e_dbg("PHY Reset Asserted not set - needs delay\n");

	/* If EEPROM is not marked present, init the IGP 3 PHY manually */
	अगर (hw->mac.type <= e1000_ich9lan) अणु
		अगर (!(er32(EECD) & E1000_EECD_PRES) &&
		    (hw->phy.type == e1000_phy_igp_3)) अणु
			e1000e_phy_init_script_igp3(hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (e1000_valid_nvm_bank_detect_ich8lan(hw, &bank)) अणु
			/* Maybe we should करो a basic PHY config */
			e_dbg("EEPROM not present\n");
			ret_val = -E1000_ERR_CONFIG;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * e1000_घातer_करोwn_phy_copper_ich8lan - Remove link during PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, हटाओ the link.
 **/
अटल व्योम e1000_घातer_करोwn_phy_copper_ich8lan(काष्ठा e1000_hw *hw)
अणु
	/* If the management पूर्णांकerface is not enabled, then घातer करोwn */
	अगर (!(hw->mac.ops.check_mng_mode(hw) ||
	      hw->phy.ops.check_reset_block(hw)))
		e1000_घातer_करोwn_phy_copper(hw);
पूर्ण

/**
 *  e1000_clear_hw_cntrs_ich8lan - Clear statistical counters
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Clears hardware counters specअगरic to the silicon family and calls
 *  clear_hw_cntrs_generic to clear all general purpose counters.
 **/
अटल व्योम e1000_clear_hw_cntrs_ich8lan(काष्ठा e1000_hw *hw)
अणु
	u16 phy_data;
	s32 ret_val;

	e1000e_clear_hw_cntrs_base(hw);

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

	/* Clear PHY statistics रेजिस्टरs */
	अगर ((hw->phy.type == e1000_phy_82578) ||
	    (hw->phy.type == e1000_phy_82579) ||
	    (hw->phy.type == e1000_phy_i217) ||
	    (hw->phy.type == e1000_phy_82577)) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस;
		ret_val = hw->phy.ops.set_page(hw,
					       HV_STATS_PAGE << IGP_PAGE_SHIFT);
		अगर (ret_val)
			जाओ release;
		hw->phy.ops.पढ़ो_reg_page(hw, HV_SCC_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_SCC_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_ECOL_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_ECOL_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_MCC_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_MCC_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_LATECOL_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_LATECOL_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_COLC_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_COLC_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_DC_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_DC_LOWER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_TNCRS_UPPER, &phy_data);
		hw->phy.ops.पढ़ो_reg_page(hw, HV_TNCRS_LOWER, &phy_data);
release:
		hw->phy.ops.release(hw);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा e1000_mac_operations ich8_mac_ops = अणु
	/* check_mng_mode dependent on mac type */
	.check_क्रम_link		= e1000_check_क्रम_copper_link_ich8lan,
	/* cleanup_led dependent on mac type */
	.clear_hw_cntrs		= e1000_clear_hw_cntrs_ich8lan,
	.get_bus_info		= e1000_get_bus_info_ich8lan,
	.set_lan_id		= e1000_set_lan_id_single_port,
	.get_link_up_info	= e1000_get_link_up_info_ich8lan,
	/* led_on dependent on mac type */
	/* led_off dependent on mac type */
	.update_mc_addr_list	= e1000e_update_mc_addr_list_generic,
	.reset_hw		= e1000_reset_hw_ich8lan,
	.init_hw		= e1000_init_hw_ich8lan,
	.setup_link		= e1000_setup_link_ich8lan,
	.setup_physical_पूर्णांकerface = e1000_setup_copper_link_ich8lan,
	/* id_led_init dependent on mac type */
	.config_collision_dist	= e1000e_config_collision_dist_generic,
	.rar_set		= e1000e_rar_set_generic,
	.rar_get_count		= e1000e_rar_get_count_generic,
पूर्ण;

अटल स्थिर काष्ठा e1000_phy_operations ich8_phy_ops = अणु
	.acquire		= e1000_acquire_swflag_ich8lan,
	.check_reset_block	= e1000_check_reset_block_ich8lan,
	.commit			= शून्य,
	.get_cfg_करोne		= e1000_get_cfg_करोne_ich8lan,
	.get_cable_length	= e1000e_get_cable_length_igp_2,
	.पढ़ो_reg		= e1000e_पढ़ो_phy_reg_igp,
	.release		= e1000_release_swflag_ich8lan,
	.reset			= e1000_phy_hw_reset_ich8lan,
	.set_d0_lplu_state	= e1000_set_d0_lplu_state_ich8lan,
	.set_d3_lplu_state	= e1000_set_d3_lplu_state_ich8lan,
	.ग_लिखो_reg		= e1000e_ग_लिखो_phy_reg_igp,
पूर्ण;

अटल स्थिर काष्ठा e1000_nvm_operations ich8_nvm_ops = अणु
	.acquire		= e1000_acquire_nvm_ich8lan,
	.पढ़ो			= e1000_पढ़ो_nvm_ich8lan,
	.release		= e1000_release_nvm_ich8lan,
	.reload			= e1000e_reload_nvm_generic,
	.update			= e1000_update_nvm_checksum_ich8lan,
	.valid_led_शेष	= e1000_valid_led_शेष_ich8lan,
	.validate		= e1000_validate_nvm_checksum_ich8lan,
	.ग_लिखो			= e1000_ग_लिखो_nvm_ich8lan,
पूर्ण;

अटल स्थिर काष्ठा e1000_nvm_operations spt_nvm_ops = अणु
	.acquire		= e1000_acquire_nvm_ich8lan,
	.release		= e1000_release_nvm_ich8lan,
	.पढ़ो			= e1000_पढ़ो_nvm_spt,
	.update			= e1000_update_nvm_checksum_spt,
	.reload			= e1000e_reload_nvm_generic,
	.valid_led_शेष	= e1000_valid_led_शेष_ich8lan,
	.validate		= e1000_validate_nvm_checksum_ich8lan,
	.ग_लिखो			= e1000_ग_लिखो_nvm_ich8lan,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_ich8_info = अणु
	.mac			= e1000_ich8lan,
	.flags			= FLAG_HAS_WOL
				  | FLAG_IS_ICH
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_APME_IN_WUC,
	.pba			= 8,
	.max_hw_frame_size	= VLAN_ETH_FRAME_LEN + ETH_FCS_LEN,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_ich9_info = अणु
	.mac			= e1000_ich9lan,
	.flags			= FLAG_HAS_JUMBO_FRAMES
				  | FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_APME_IN_WUC,
	.pba			= 18,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_ich10_info = अणु
	.mac			= e1000_ich10lan,
	.flags			= FLAG_HAS_JUMBO_FRAMES
				  | FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_APME_IN_WUC,
	.pba			= 18,
	.max_hw_frame_size	= DEFAULT_JUMBO,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_pch_info = अणु
	.mac			= e1000_pchlan,
	.flags			= FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_DISABLE_FC_PAUSE_TIME /* errata */
				  | FLAG_APME_IN_WUC,
	.flags2			= FLAG2_HAS_PHY_STATS,
	.pba			= 26,
	.max_hw_frame_size	= 4096,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_pch2_info = अणु
	.mac			= e1000_pch2lan,
	.flags			= FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_APME_IN_WUC,
	.flags2			= FLAG2_HAS_PHY_STATS
				  | FLAG2_HAS_EEE
				  | FLAG2_CHECK_SYSTIM_OVERFLOW,
	.pba			= 26,
	.max_hw_frame_size	= 9022,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_pch_lpt_info = अणु
	.mac			= e1000_pch_lpt,
	.flags			= FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_APME_IN_WUC,
	.flags2			= FLAG2_HAS_PHY_STATS
				  | FLAG2_HAS_EEE
				  | FLAG2_CHECK_SYSTIM_OVERFLOW,
	.pba			= 26,
	.max_hw_frame_size	= 9022,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &ich8_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_pch_spt_info = अणु
	.mac			= e1000_pch_spt,
	.flags			= FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_APME_IN_WUC,
	.flags2			= FLAG2_HAS_PHY_STATS
				  | FLAG2_HAS_EEE,
	.pba			= 26,
	.max_hw_frame_size	= 9022,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &spt_nvm_ops,
पूर्ण;

स्थिर काष्ठा e1000_info e1000_pch_cnp_info = अणु
	.mac			= e1000_pch_cnp,
	.flags			= FLAG_IS_ICH
				  | FLAG_HAS_WOL
				  | FLAG_HAS_HW_TIMESTAMP
				  | FLAG_HAS_CTRLEXT_ON_LOAD
				  | FLAG_HAS_AMT
				  | FLAG_HAS_FLASH
				  | FLAG_HAS_JUMBO_FRAMES
				  | FLAG_APME_IN_WUC,
	.flags2			= FLAG2_HAS_PHY_STATS
				  | FLAG2_HAS_EEE,
	.pba			= 26,
	.max_hw_frame_size	= 9022,
	.get_variants		= e1000_get_variants_ich8lan,
	.mac_ops		= &ich8_mac_ops,
	.phy_ops		= &ich8_phy_ops,
	.nvm_ops		= &spt_nvm_ops,
पूर्ण;

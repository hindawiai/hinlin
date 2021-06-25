<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश <linux/delay.h>

#समावेश "igc_hw.h"
#समावेश "igc_i225.h"
#समावेश "igc_mac.h"
#समावेश "igc_base.h"
#समावेश "igc.h"

/**
 * igc_reset_hw_base - Reset hardware
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This resets the hardware पूर्णांकo a known state.  This is a
 * function poपूर्णांकer entry poपूर्णांक called by the api module.
 */
अटल s32 igc_reset_hw_base(काष्ठा igc_hw *hw)
अणु
	s32 ret_val;
	u32 ctrl;

	/* Prevent the PCI-E bus from sticking अगर there is no TLP connection
	 * on the last TLP पढ़ो/ग_लिखो transaction when MAC is reset.
	 */
	ret_val = igc_disable_pcie_master(hw);
	अगर (ret_val)
		hw_dbg("PCI-E Master disable polling has failed\n");

	hw_dbg("Masking off all interrupts\n");
	wr32(IGC_IMC, 0xffffffff);

	wr32(IGC_RCTL, 0);
	wr32(IGC_TCTL, IGC_TCTL_PSP);
	wrfl();

	usleep_range(10000, 20000);

	ctrl = rd32(IGC_CTRL);

	hw_dbg("Issuing a global reset to MAC\n");
	wr32(IGC_CTRL, ctrl | IGC_CTRL_DEV_RST);

	ret_val = igc_get_स्वतः_rd_करोne(hw);
	अगर (ret_val) अणु
		/* When स्वतः config पढ़ो करोes not complete, करो not
		 * वापस with an error. This can happen in situations
		 * where there is no eeprom and prevents getting link.
		 */
		hw_dbg("Auto Read Done did not complete\n");
	पूर्ण

	/* Clear any pending पूर्णांकerrupt events. */
	wr32(IGC_IMC, 0xffffffff);
	rd32(IGC_ICR);

	वापस ret_val;
पूर्ण

/**
 * igc_init_nvm_params_base - Init NVM func ptrs.
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
अटल s32 igc_init_nvm_params_base(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(IGC_EECD);
	u16 size;

	size = (u16)((eecd & IGC_EECD_SIZE_EX_MASK) >>
		     IGC_EECD_SIZE_EX_SHIFT);

	/* Added to a स्थिरant, "size" becomes the left-shअगरt value
	 * क्रम setting word_size.
	 */
	size += NVM_WORD_SIZE_BASE_SHIFT;

	/* Just in हाल size is out of range, cap it to the largest
	 * EEPROM size supported
	 */
	अगर (size > 15)
		size = 15;

	nvm->type = igc_nvm_eeprom_spi;
	nvm->word_size = BIT(size);
	nvm->opcode_bits = 8;
	nvm->delay_usec = 1;

	nvm->page_size = eecd & IGC_EECD_ADDR_BITS ? 32 : 8;
	nvm->address_bits = eecd & IGC_EECD_ADDR_BITS ?
			    16 : 8;

	अगर (nvm->word_size == BIT(15))
		nvm->page_size = 128;

	वापस 0;
पूर्ण

/**
 * igc_setup_copper_link_base - Configure copper link settings
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Configures the link क्रम स्वतः-neg or क्रमced speed and duplex.  Then we check
 * क्रम link, once link is established calls to configure collision distance
 * and flow control are called.
 */
अटल s32 igc_setup_copper_link_base(काष्ठा igc_hw *hw)
अणु
	s32  ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);
	ctrl |= IGC_CTRL_SLU;
	ctrl &= ~(IGC_CTRL_FRCSPD | IGC_CTRL_FRCDPX);
	wr32(IGC_CTRL, ctrl);

	ret_val = igc_setup_copper_link(hw);

	वापस ret_val;
पूर्ण

/**
 * igc_init_mac_params_base - Init MAC func ptrs.
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
अटल s32 igc_init_mac_params_base(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_dev_spec_base *dev_spec = &hw->dev_spec._base;
	काष्ठा igc_mac_info *mac = &hw->mac;

	/* Set mta रेजिस्टर count */
	mac->mta_reg_count = 128;
	mac->rar_entry_count = IGC_RAR_ENTRIES;

	/* reset */
	mac->ops.reset_hw = igc_reset_hw_base;

	mac->ops.acquire_swfw_sync = igc_acquire_swfw_sync_i225;
	mac->ops.release_swfw_sync = igc_release_swfw_sync_i225;

	/* Allow a single clear of the SW semaphore on I225 */
	अगर (mac->type == igc_i225)
		dev_spec->clear_semaphore_once = true;

	/* physical पूर्णांकerface link setup */
	mac->ops.setup_physical_पूर्णांकerface = igc_setup_copper_link_base;

	वापस 0;
पूर्ण

/**
 * igc_init_phy_params_base - Init PHY func ptrs.
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
अटल s32 igc_init_phy_params_base(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_phy_info *phy = &hw->phy;
	s32 ret_val = 0;

	अगर (hw->phy.media_type != igc_media_type_copper) अणु
		phy->type = igc_phy_none;
		जाओ out;
	पूर्ण

	phy->स्वतःneg_mask	= AUTONEG_ADVERTISE_SPEED_DEFAULT_2500;
	phy->reset_delay_us	= 100;

	/* set lan id */
	hw->bus.func = (rd32(IGC_STATUS) & IGC_STATUS_FUNC_MASK) >>
			IGC_STATUS_FUNC_SHIFT;

	/* Make sure the PHY is in a good state. Several people have reported
	 * firmware leaving the PHY's page select रेजिस्टर set to something
	 * other than the शेष of zero, which causes the PHY ID पढ़ो to
	 * access something other than the पूर्णांकended रेजिस्टर.
	 */
	ret_val = hw->phy.ops.reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error resetting the PHY\n");
		जाओ out;
	पूर्ण

	ret_val = igc_get_phy_id(hw);
	अगर (ret_val)
		वापस ret_val;

	igc_check_क्रम_copper_link(hw);

	/* Verअगरy phy id and set reमुख्यing function poपूर्णांकers */
	चयन (phy->id) अणु
	हाल I225_I_PHY_ID:
		phy->type	= igc_phy_i225;
		अवरोध;
	शेष:
		ret_val = -IGC_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

अटल s32 igc_get_invariants_base(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_mac_info *mac = &hw->mac;
	s32 ret_val = 0;

	चयन (hw->device_id) अणु
	हाल IGC_DEV_ID_I225_LM:
	हाल IGC_DEV_ID_I225_V:
	हाल IGC_DEV_ID_I225_I:
	हाल IGC_DEV_ID_I220_V:
	हाल IGC_DEV_ID_I225_K:
	हाल IGC_DEV_ID_I225_K2:
	हाल IGC_DEV_ID_I226_K:
	हाल IGC_DEV_ID_I225_LMVP:
	हाल IGC_DEV_ID_I225_IT:
	हाल IGC_DEV_ID_I226_LM:
	हाल IGC_DEV_ID_I226_V:
	हाल IGC_DEV_ID_I226_IT:
	हाल IGC_DEV_ID_I221_V:
	हाल IGC_DEV_ID_I226_BLANK_NVM:
	हाल IGC_DEV_ID_I225_BLANK_NVM:
		mac->type = igc_i225;
		अवरोध;
	शेष:
		वापस -IGC_ERR_MAC_INIT;
	पूर्ण

	hw->phy.media_type = igc_media_type_copper;

	/* mac initialization and operations */
	ret_val = igc_init_mac_params_base(hw);
	अगर (ret_val)
		जाओ out;

	/* NVM initialization */
	ret_val = igc_init_nvm_params_base(hw);
	चयन (hw->mac.type) अणु
	हाल igc_i225:
		ret_val = igc_init_nvm_params_i225(hw);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* setup PHY parameters */
	ret_val = igc_init_phy_params_base(hw);
	अगर (ret_val)
		जाओ out;

out:
	वापस ret_val;
पूर्ण

/**
 * igc_acquire_phy_base - Acquire rights to access PHY
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Acquire access rights to the correct PHY.  This is a
 * function poपूर्णांकer entry poपूर्णांक called by the api module.
 */
अटल s32 igc_acquire_phy_base(काष्ठा igc_hw *hw)
अणु
	u16 mask = IGC_SWFW_PHY0_SM;

	वापस hw->mac.ops.acquire_swfw_sync(hw, mask);
पूर्ण

/**
 * igc_release_phy_base - Release rights to access PHY
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * A wrapper to release access rights to the correct PHY.  This is a
 * function poपूर्णांकer entry poपूर्णांक called by the api module.
 */
अटल व्योम igc_release_phy_base(काष्ठा igc_hw *hw)
अणु
	u16 mask = IGC_SWFW_PHY0_SM;

	hw->mac.ops.release_swfw_sync(hw, mask);
पूर्ण

/**
 * igc_init_hw_base - Initialize hardware
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This inits the hardware पढ़ोying it क्रम operation.
 */
अटल s32 igc_init_hw_base(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_mac_info *mac = &hw->mac;
	u16 i, rar_count = mac->rar_entry_count;
	s32 ret_val = 0;

	/* Setup the receive address */
	igc_init_rx_addrs(hw, rar_count);

	/* Zero out the Multicast HASH table */
	hw_dbg("Zeroing the MTA\n");
	क्रम (i = 0; i < mac->mta_reg_count; i++)
		array_wr32(IGC_MTA, i, 0);

	/* Zero out the Unicast HASH table */
	hw_dbg("Zeroing the UTA\n");
	क्रम (i = 0; i < mac->uta_reg_count; i++)
		array_wr32(IGC_UTA, i, 0);

	/* Setup link and flow control */
	ret_val = igc_setup_link(hw);

	/* Clear all of the statistics रेजिस्टरs (clear on पढ़ो).  It is
	 * important that we करो this after we have tried to establish link
	 * because the symbol error count will increment wildly अगर there
	 * is no link.
	 */
	igc_clear_hw_cntrs_base(hw);

	वापस ret_val;
पूर्ण

/**
 * igc_घातer_करोwn_phy_copper_base - Remove link during PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, हटाओ the link.
 */
व्योम igc_घातer_करोwn_phy_copper_base(काष्ठा igc_hw *hw)
अणु
	/* If the management पूर्णांकerface is not enabled, then घातer करोwn */
	अगर (!(igc_enable_mng_pass_thru(hw) || igc_check_reset_block(hw)))
		igc_घातer_करोwn_phy_copper(hw);
पूर्ण

/**
 * igc_rx_fअगरo_flush_base - Clean rx fअगरo after Rx enable
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * After Rx enable, अगर manageability is enabled then there is likely some
 * bad data at the start of the fअगरo and possibly in the DMA fअगरo.  This
 * function clears the fअगरos and flushes any packets that came in as rx was
 * being enabled.
 */
व्योम igc_rx_fअगरo_flush_base(काष्ठा igc_hw *hw)
अणु
	u32 rctl, rlpml, rxdctl[4], rfctl, temp_rctl, rx_enabled;
	पूर्णांक i, ms_रुको;

	/* disable IPv6 options as per hardware errata */
	rfctl = rd32(IGC_RFCTL);
	rfctl |= IGC_RFCTL_IPV6_EX_DIS;
	wr32(IGC_RFCTL, rfctl);

	अगर (!(rd32(IGC_MANC) & IGC_MANC_RCV_TCO_EN))
		वापस;

	/* Disable all Rx queues */
	क्रम (i = 0; i < 4; i++) अणु
		rxdctl[i] = rd32(IGC_RXDCTL(i));
		wr32(IGC_RXDCTL(i),
		     rxdctl[i] & ~IGC_RXDCTL_QUEUE_ENABLE);
	पूर्ण
	/* Poll all queues to verअगरy they have shut करोwn */
	क्रम (ms_रुको = 0; ms_रुको < 10; ms_रुको++) अणु
		usleep_range(1000, 2000);
		rx_enabled = 0;
		क्रम (i = 0; i < 4; i++)
			rx_enabled |= rd32(IGC_RXDCTL(i));
		अगर (!(rx_enabled & IGC_RXDCTL_QUEUE_ENABLE))
			अवरोध;
	पूर्ण

	अगर (ms_रुको == 10)
		hw_dbg("Queue disable timed out after 10ms\n");

	/* Clear RLPML, RCTL.SBP, RFCTL.LEF, and set RCTL.LPE so that all
	 * incoming packets are rejected.  Set enable and रुको 2ms so that
	 * any packet that was coming in as RCTL.EN was set is flushed
	 */
	wr32(IGC_RFCTL, rfctl & ~IGC_RFCTL_LEF);

	rlpml = rd32(IGC_RLPML);
	wr32(IGC_RLPML, 0);

	rctl = rd32(IGC_RCTL);
	temp_rctl = rctl & ~(IGC_RCTL_EN | IGC_RCTL_SBP);
	temp_rctl |= IGC_RCTL_LPE;

	wr32(IGC_RCTL, temp_rctl);
	wr32(IGC_RCTL, temp_rctl | IGC_RCTL_EN);
	wrfl();
	usleep_range(2000, 3000);

	/* Enable Rx queues that were previously enabled and restore our
	 * previous state
	 */
	क्रम (i = 0; i < 4; i++)
		wr32(IGC_RXDCTL(i), rxdctl[i]);
	wr32(IGC_RCTL, rctl);
	wrfl();

	wr32(IGC_RLPML, rlpml);
	wr32(IGC_RFCTL, rfctl);

	/* Flush receive errors generated by workaround */
	rd32(IGC_ROC);
	rd32(IGC_RNBC);
	rd32(IGC_MPC);
पूर्ण

अटल काष्ठा igc_mac_operations igc_mac_ops_base = अणु
	.init_hw		= igc_init_hw_base,
	.check_क्रम_link		= igc_check_क्रम_copper_link,
	.rar_set		= igc_rar_set,
	.पढ़ो_mac_addr		= igc_पढ़ो_mac_addr,
	.get_speed_and_duplex	= igc_get_speed_and_duplex_copper,
पूर्ण;

अटल स्थिर काष्ठा igc_phy_operations igc_phy_ops_base = अणु
	.acquire		= igc_acquire_phy_base,
	.release		= igc_release_phy_base,
	.reset			= igc_phy_hw_reset,
	.पढ़ो_reg		= igc_पढ़ो_phy_reg_gpy,
	.ग_लिखो_reg		= igc_ग_लिखो_phy_reg_gpy,
पूर्ण;

स्थिर काष्ठा igc_info igc_base_info = अणु
	.get_invariants		= igc_get_invariants_base,
	.mac_ops		= &igc_mac_ops_base,
	.phy_ops		= &igc_phy_ops_base,
पूर्ण;

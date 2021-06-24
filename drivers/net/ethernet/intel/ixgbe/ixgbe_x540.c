<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_phy.h"
#समावेश "ixgbe_x540.h"

#घोषणा IXGBE_X540_MAX_TX_QUEUES	128
#घोषणा IXGBE_X540_MAX_RX_QUEUES	128
#घोषणा IXGBE_X540_RAR_ENTRIES		128
#घोषणा IXGBE_X540_MC_TBL_SIZE		128
#घोषणा IXGBE_X540_VFT_TBL_SIZE		128
#घोषणा IXGBE_X540_RX_PB_SIZE		384

अटल s32 ixgbe_update_flash_X540(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_poll_flash_update_करोne_X540(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_get_swfw_sync_semaphore(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_release_swfw_sync_semaphore(काष्ठा ixgbe_hw *hw);

क्रमागत ixgbe_media_type ixgbe_get_media_type_X540(काष्ठा ixgbe_hw *hw)
अणु
	वापस ixgbe_media_type_copper;
पूर्ण

s32 ixgbe_get_invariants_X540(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	काष्ठा ixgbe_phy_info *phy = &hw->phy;

	/* set_phy_घातer was set by शेष to शून्य */
	phy->ops.set_phy_घातer = ixgbe_set_copper_phy_घातer;

	mac->mcft_size = IXGBE_X540_MC_TBL_SIZE;
	mac->vft_size = IXGBE_X540_VFT_TBL_SIZE;
	mac->num_rar_entries = IXGBE_X540_RAR_ENTRIES;
	mac->rx_pb_size = IXGBE_X540_RX_PB_SIZE;
	mac->max_rx_queues = IXGBE_X540_MAX_RX_QUEUES;
	mac->max_tx_queues = IXGBE_X540_MAX_TX_QUEUES;
	mac->max_msix_vectors = ixgbe_get_pcie_msix_count_generic(hw);

	वापस 0;
पूर्ण

/**
 *  ixgbe_setup_mac_link_X540 - Set the स्वतः advertised capabilitires
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: true when रुकोing क्रम completion is needed
 **/
s32 ixgbe_setup_mac_link_X540(काष्ठा ixgbe_hw *hw, ixgbe_link_speed speed,
			      bool स्वतःneg_रुको_to_complete)
अणु
	वापस hw->phy.ops.setup_link_speed(hw, speed,
					    स्वतःneg_रुको_to_complete);
पूर्ण

/**
 *  ixgbe_reset_hw_X540 - Perक्रमm hardware reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Resets the hardware by resetting the transmit and receive units, masks
 *  and clears all पूर्णांकerrupts, perक्रमm a PHY reset, and perक्रमm a link (MAC)
 *  reset.
 **/
s32 ixgbe_reset_hw_X540(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u32 ctrl, i;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;

	/* Call adapter stop to disable tx/rx and clear पूर्णांकerrupts */
	status = hw->mac.ops.stop_adapter(hw);
	अगर (status)
		वापस status;

	/* flush pending Tx transactions */
	ixgbe_clear_tx_pending(hw);

mac_reset_top:
	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	अगर (status) अणु
		hw_dbg(hw, "semaphore failed with %d", status);
		वापस IXGBE_ERR_SWFW_SYNC;
	पूर्ण

	ctrl = IXGBE_CTRL_RST;
	ctrl |= IXGBE_READ_REG(hw, IXGBE_CTRL);
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
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
	msleep(100);

	/*
	 * Double resets are required क्रम recovery from certain error
	 * conditions.  Between resets, it is necessary to stall to allow समय
	 * क्रम any pending HW events to complete.
	 */
	अगर (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) अणु
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		जाओ mac_reset_top;
	पूर्ण

	/* Set the Rx packet buffer size. */
	IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(0), 384 << IXGBE_RXPBSIZE_SHIFT);

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/*
	 * Store MAC address from RAR0, clear receive address रेजिस्टरs, and
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modअगरy this value when programming the SAN MAC address.
	 */
	hw->mac.num_rar_entries = IXGBE_X540_MAX_TX_QUEUES;
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
 *  ixgbe_start_hw_X540 - Prepare hardware क्रम Tx/Rx
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Starts the hardware using the generic start_hw function
 *  and the generation start_hw function.
 *  Then perक्रमms revision-specअगरic operations, अगर any.
 **/
s32 ixgbe_start_hw_X540(काष्ठा ixgbe_hw *hw)
अणु
	s32 ret_val;

	ret_val = ixgbe_start_hw_generic(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस ixgbe_start_hw_gen2(hw);
पूर्ण

/**
 *  ixgbe_init_eeprom_params_X540 - Initialize EEPROM params
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initializes the EEPROM parameters ixgbe_eeprom_info within the
 *  ixgbe_hw काष्ठा in order to set up EEPROM access.
 **/
s32 ixgbe_init_eeprom_params_X540(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_eeprom_info *eeprom = &hw->eeprom;
	u32 eec;
	u16 eeprom_size;

	अगर (eeprom->type == ixgbe_eeprom_uninitialized) अणु
		eeprom->semaphore_delay = 10;
		eeprom->type = ixgbe_flash;

		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		eeprom_size = (u16)((eec & IXGBE_EEC_SIZE) >>
				    IXGBE_EEC_SIZE_SHIFT);
		eeprom->word_size = BIT(eeprom_size +
					IXGBE_EEPROM_WORD_SIZE_SHIFT);

		hw_dbg(hw, "Eeprom params: type = %d, size = %d\n",
		       eeprom->type, eeprom->word_size);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_eerd_X540- Read EEPROM word using EERD
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM using the EERD रेजिस्टर.
 **/
अटल s32 ixgbe_पढ़ो_eerd_X540(काष्ठा ixgbe_hw *hw, u16 offset, u16 *data)
अणु
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = ixgbe_पढ़ो_eerd_generic(hw, offset, data);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	वापस status;
पूर्ण

/**
 *  ixgbe_पढ़ो_eerd_buffer_X540 - Read EEPROM word(s) using EERD
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @words: number of words
 *  @data: word(s) पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word(s) from the EEPROM using the EERD रेजिस्टर.
 **/
अटल s32 ixgbe_पढ़ो_eerd_buffer_X540(काष्ठा ixgbe_hw *hw,
				       u16 offset, u16 words, u16 *data)
अणु
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = ixgbe_पढ़ो_eerd_buffer_generic(hw, offset, words, data);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eewr_X540 - Write EEPROM word using EEWR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @data: word ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word to the EEPROM using the EEWR रेजिस्टर.
 **/
अटल s32 ixgbe_ग_लिखो_eewr_X540(काष्ठा ixgbe_hw *hw, u16 offset, u16 data)
अणु
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = ixgbe_ग_लिखो_eewr_generic(hw, offset, data);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_eewr_buffer_X540 - Write EEPROM word(s) using EEWR
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @words: number of words
 *  @data: word(s) ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word(s) to the EEPROM using the EEWR रेजिस्टर.
 **/
अटल s32 ixgbe_ग_लिखो_eewr_buffer_X540(काष्ठा ixgbe_hw *hw,
					u16 offset, u16 words, u16 *data)
अणु
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = ixgbe_ग_लिखो_eewr_buffer_generic(hw, offset, words, data);

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	वापस status;
पूर्ण

/**
 *  ixgbe_calc_eeprom_checksum_X540 - Calculates and वापसs the checksum
 *
 *  This function करोes not use synchronization क्रम EERD and EEWR. It can
 *  be used पूर्णांकernally by function which utilize ixgbe_acquire_swfw_sync_X540.
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_calc_eeprom_checksum_X540(काष्ठा ixgbe_hw *hw)
अणु
	u16 i;
	u16 j;
	u16 checksum = 0;
	u16 length = 0;
	u16 poपूर्णांकer = 0;
	u16 word = 0;
	u16 checksum_last_word = IXGBE_EEPROM_CHECKSUM;
	u16 ptr_start = IXGBE_PCIE_ANALOG_PTR;

	/*
	 * Do not use hw->eeprom.ops.पढ़ो because we करो not want to take
	 * the synchronization semaphores here. Instead use
	 * ixgbe_पढ़ो_eerd_generic
	 */

	/* Include 0x0-0x3F in the checksum */
	क्रम (i = 0; i < checksum_last_word; i++) अणु
		अगर (ixgbe_पढ़ो_eerd_generic(hw, i, &word)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			वापस IXGBE_ERR_EEPROM;
		पूर्ण
		checksum += word;
	पूर्ण

	/*
	 * Include all data from poपूर्णांकers 0x3, 0x6-0xE.  This excludes the
	 * FW, PHY module, and PCIe Expansion/Option ROM poपूर्णांकers.
	 */
	क्रम (i = ptr_start; i < IXGBE_FW_PTR; i++) अणु
		अगर (i == IXGBE_PHY_PTR || i == IXGBE_OPTION_ROM_PTR)
			जारी;

		अगर (ixgbe_पढ़ो_eerd_generic(hw, i, &poपूर्णांकer)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			अवरोध;
		पूर्ण

		/* Skip poपूर्णांकer section अगर the poपूर्णांकer is invalid. */
		अगर (poपूर्णांकer == 0xFFFF || poपूर्णांकer == 0 ||
		    poपूर्णांकer >= hw->eeprom.word_size)
			जारी;

		अगर (ixgbe_पढ़ो_eerd_generic(hw, poपूर्णांकer, &length)) अणु
			hw_dbg(hw, "EEPROM read failed\n");
			वापस IXGBE_ERR_EEPROM;
		पूर्ण

		/* Skip poपूर्णांकer section अगर length is invalid. */
		अगर (length == 0xFFFF || length == 0 ||
		    (poपूर्णांकer + length) >= hw->eeprom.word_size)
			जारी;

		क्रम (j = poपूर्णांकer + 1; j <= poपूर्णांकer + length; j++) अणु
			अगर (ixgbe_पढ़ो_eerd_generic(hw, j, &word)) अणु
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
 *  ixgbe_validate_eeprom_checksum_X540 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @checksum_val: calculated checksum
 *
 *  Perक्रमms checksum calculation and validates the EEPROM checksum.  If the
 *  caller करोes not need checksum_val, the value can be शून्य.
 **/
अटल s32 ixgbe_validate_eeprom_checksum_X540(काष्ठा ixgbe_hw *hw,
					       u16 *checksum_val)
अणु
	s32 status;
	u16 checksum;
	u16 पढ़ो_checksum = 0;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = hw->eeprom.ops.पढ़ो(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = hw->eeprom.ops.calc_checksum(hw);
	अगर (status < 0)
		जाओ out;

	checksum = (u16)(status & 0xffff);

	/* Do not use hw->eeprom.ops.पढ़ो because we करो not want to take
	 * the synchronization semaphores twice here.
	 */
	status = ixgbe_पढ़ो_eerd_generic(hw, IXGBE_EEPROM_CHECKSUM,
					 &पढ़ो_checksum);
	अगर (status)
		जाओ out;

	/* Verअगरy पढ़ो checksum from EEPROM is the same as
	 * calculated checksum
	 */
	अगर (पढ़ो_checksum != checksum) अणु
		hw_dbg(hw, "Invalid EEPROM checksum");
		status = IXGBE_ERR_EEPROM_CHECKSUM;
	पूर्ण

	/* If the user cares, वापस the calculated checksum */
	अगर (checksum_val)
		*checksum_val = checksum;

out:
	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);

	वापस status;
पूर्ण

/**
 * ixgbe_update_eeprom_checksum_X540 - Updates the EEPROM checksum and flash
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * After writing EEPROM to shaकरोw RAM using EEWR रेजिस्टर, software calculates
 * checksum and updates the EEPROM and inकाष्ठाs the hardware to update
 * the flash.
 **/
अटल s32 ixgbe_update_eeprom_checksum_X540(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 checksum;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = hw->eeprom.ops.पढ़ो(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM))
		वापस  IXGBE_ERR_SWFW_SYNC;

	status = hw->eeprom.ops.calc_checksum(hw);
	अगर (status < 0)
		जाओ out;

	checksum = (u16)(status & 0xffff);

	/* Do not use hw->eeprom.ops.ग_लिखो because we करो not want to
	 * take the synchronization semaphores twice here.
	 */
	status = ixgbe_ग_लिखो_eewr_generic(hw, IXGBE_EEPROM_CHECKSUM, checksum);
	अगर (status)
		जाओ out;

	status = ixgbe_update_flash_X540(hw);

out:
	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	वापस status;
पूर्ण

/**
 * ixgbe_update_flash_X540 - Inकाष्ठा HW to copy EEPROM to Flash device
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Set FLUP (bit 23) of the EEC रेजिस्टर to inकाष्ठा Hardware to copy
 * EEPROM from shaकरोw RAM to the flash device.
 **/
अटल s32 ixgbe_update_flash_X540(काष्ठा ixgbe_hw *hw)
अणु
	u32 flup;
	s32 status;

	status = ixgbe_poll_flash_update_करोne_X540(hw);
	अगर (status == IXGBE_ERR_EEPROM) अणु
		hw_dbg(hw, "Flash update time out\n");
		वापस status;
	पूर्ण

	flup = IXGBE_READ_REG(hw, IXGBE_EEC(hw)) | IXGBE_EEC_FLUP;
	IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), flup);

	status = ixgbe_poll_flash_update_करोne_X540(hw);
	अगर (status == 0)
		hw_dbg(hw, "Flash update complete\n");
	अन्यथा
		hw_dbg(hw, "Flash update time out\n");

	अगर (hw->revision_id == 0) अणु
		flup = IXGBE_READ_REG(hw, IXGBE_EEC(hw));

		अगर (flup & IXGBE_EEC_SEC1VAL) अणु
			flup |= IXGBE_EEC_FLUP;
			IXGBE_WRITE_REG(hw, IXGBE_EEC(hw), flup);
		पूर्ण

		status = ixgbe_poll_flash_update_करोne_X540(hw);
		अगर (status == 0)
			hw_dbg(hw, "Flash update complete\n");
		अन्यथा
			hw_dbg(hw, "Flash update time out\n");
	पूर्ण

	वापस status;
पूर्ण

/**
 * ixgbe_poll_flash_update_करोne_X540 - Poll flash update status
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Polls the FLUDONE (bit 26) of the EEC Register to determine when the
 * flash update is करोne.
 **/
अटल s32 ixgbe_poll_flash_update_करोne_X540(काष्ठा ixgbe_hw *hw)
अणु
	u32 i;
	u32 reg;

	क्रम (i = 0; i < IXGBE_FLUDONE_ATTEMPTS; i++) अणु
		reg = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		अगर (reg & IXGBE_EEC_FLUDONE)
			वापस 0;
		udelay(5);
	पूर्ण
	वापस IXGBE_ERR_EEPROM;
पूर्ण

/**
 * ixgbe_acquire_swfw_sync_X540 - Acquire SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to acquire
 *
 * Acquires the SWFW semaphore thought the SW_FW_SYNC रेजिस्टर क्रम
 * the specअगरied function (CSR, PHY0, PHY1, NVM, Flash)
 **/
s32 ixgbe_acquire_swfw_sync_X540(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 swmask = mask & IXGBE_GSSR_NVM_PHY_MASK;
	u32 swi2c_mask = mask & IXGBE_GSSR_I2C_MASK;
	u32 fwmask = swmask << 5;
	u32 समयout = 200;
	u32 hwmask = 0;
	u32 swfw_sync;
	u32 i;

	अगर (swmask & IXGBE_GSSR_EEP_SM)
		hwmask = IXGBE_GSSR_FLASH_SM;

	/* SW only mask करोes not have FW bit pair */
	अगर (mask & IXGBE_GSSR_SW_MNG_SM)
		swmask |= IXGBE_GSSR_SW_MNG_SM;

	swmask |= swi2c_mask;
	fwmask |= swi2c_mask << 2;
	क्रम (i = 0; i < समयout; i++) अणु
		/* SW NVM semaphore bit is used क्रम access to all
		 * SW_FW_SYNC bits (not just NVM)
		 */
		अगर (ixgbe_get_swfw_sync_semaphore(hw))
			वापस IXGBE_ERR_SWFW_SYNC;

		swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
		अगर (!(swfw_sync & (fwmask | swmask | hwmask))) अणु
			swfw_sync |= swmask;
			IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);
			ixgbe_release_swfw_sync_semaphore(hw);
			usleep_range(5000, 6000);
			वापस 0;
		पूर्ण
		/* Firmware currently using resource (fwmask), hardware
		 * currently using resource (hwmask), or other software
		 * thपढ़ो currently using resource (swmask)
		 */
		ixgbe_release_swfw_sync_semaphore(hw);
		usleep_range(5000, 10000);
	पूर्ण

	/* If the resource is not released by the FW/HW the SW can assume that
	 * the FW/HW malfunctions. In that हाल the SW should set the SW bit(s)
	 * of the requested resource(s) जबतक ignoring the corresponding FW/HW
	 * bits in the SW_FW_SYNC रेजिस्टर.
	 */
	अगर (ixgbe_get_swfw_sync_semaphore(hw))
		वापस IXGBE_ERR_SWFW_SYNC;
	swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
	अगर (swfw_sync & (fwmask | hwmask)) अणु
		swfw_sync |= swmask;
		IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);
		ixgbe_release_swfw_sync_semaphore(hw);
		usleep_range(5000, 6000);
		वापस 0;
	पूर्ण
	/* If the resource is not released by other SW the SW can assume that
	 * the other SW malfunctions. In that हाल the SW should clear all SW
	 * flags that it करोes not own and then repeat the whole process once
	 * again.
	 */
	अगर (swfw_sync & swmask) अणु
		u32 rmask = IXGBE_GSSR_EEP_SM | IXGBE_GSSR_PHY0_SM |
			    IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_MAC_CSR_SM |
			    IXGBE_GSSR_SW_MNG_SM;

		अगर (swi2c_mask)
			rmask |= IXGBE_GSSR_I2C_MASK;
		ixgbe_release_swfw_sync_X540(hw, rmask);
		ixgbe_release_swfw_sync_semaphore(hw);
		वापस IXGBE_ERR_SWFW_SYNC;
	पूर्ण
	ixgbe_release_swfw_sync_semaphore(hw);

	वापस IXGBE_ERR_SWFW_SYNC;
पूर्ण

/**
 * ixgbe_release_swfw_sync_X540 - Release SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to release
 *
 * Releases the SWFW semaphore through the SW_FW_SYNC रेजिस्टर
 * क्रम the specअगरied function (CSR, PHY0, PHY1, EVM, Flash)
 **/
व्योम ixgbe_release_swfw_sync_X540(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 swmask = mask & (IXGBE_GSSR_NVM_PHY_MASK | IXGBE_GSSR_SW_MNG_SM);
	u32 swfw_sync;

	अगर (mask & IXGBE_GSSR_I2C_MASK)
		swmask |= mask & IXGBE_GSSR_I2C_MASK;
	ixgbe_get_swfw_sync_semaphore(hw);

	swfw_sync = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
	swfw_sync &= ~swmask;
	IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);

	ixgbe_release_swfw_sync_semaphore(hw);
	usleep_range(5000, 6000);
पूर्ण

/**
 * ixgbe_get_swfw_sync_semaphore - Get hardware semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Sets the hardware semaphores so SW/FW can gain control of shared resources
 */
अटल s32 ixgbe_get_swfw_sync_semaphore(काष्ठा ixgbe_hw *hw)
अणु
	u32 समयout = 2000;
	u32 i;
	u32 swsm;

	/* Get SMBI software semaphore between device drivers first */
	क्रम (i = 0; i < समयout; i++) अणु
		/* If the SMBI bit is 0 when we पढ़ो it, then the bit will be
		 * set and we have the semaphore
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		अगर (!(swsm & IXGBE_SWSM_SMBI))
			अवरोध;
		usleep_range(50, 100);
	पूर्ण

	अगर (i == समयout) अणु
		hw_dbg(hw,
		       "Software semaphore SMBI between device drivers not granted.\n");
		वापस IXGBE_ERR_EEPROM;
	पूर्ण

	/* Now get the semaphore between SW/FW through the REGSMP bit */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
		अगर (!(swsm & IXGBE_SWFW_REGSMP))
			वापस 0;

		usleep_range(50, 100);
	पूर्ण

	/* Release semaphores and वापस error अगर SW NVM semaphore
	 * was not granted because we करो not have access to the EEPROM
	 */
	hw_dbg(hw, "REGSMP Software NVM semaphore not granted\n");
	ixgbe_release_swfw_sync_semaphore(hw);
	वापस IXGBE_ERR_EEPROM;
पूर्ण

/**
 * ixgbe_release_swfw_sync_semaphore - Release hardware semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * This function clears hardware semaphore bits.
 **/
अटल व्योम ixgbe_release_swfw_sync_semaphore(काष्ठा ixgbe_hw *hw)
अणु
	 u32 swsm;

	/* Release both semaphores by writing 0 to the bits REGSMP and SMBI */

	swsm = IXGBE_READ_REG(hw, IXGBE_SWFW_SYNC(hw));
	swsm &= ~IXGBE_SWFW_REGSMP;
	IXGBE_WRITE_REG(hw, IXGBE_SWFW_SYNC(hw), swsm);

	swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
	swsm &= ~IXGBE_SWSM_SMBI;
	IXGBE_WRITE_REG(hw, IXGBE_SWSM(hw), swsm);

	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 *  ixgbe_init_swfw_sync_X540 - Release hardware semaphore
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  This function reset hardware semaphore bits क्रम a semaphore that may
 *  have be left locked due to a catastrophic failure.
 **/
व्योम ixgbe_init_swfw_sync_X540(काष्ठा ixgbe_hw *hw)
अणु
	u32 rmask;

	/* First try to grab the semaphore but we करोn't need to bother
	 * looking to see whether we got the lock or not since we करो
	 * the same thing regardless of whether we got the lock or not.
	 * We got the lock - we release it.
	 * We समयout trying to get the lock - we क्रमce its release.
	 */
	ixgbe_get_swfw_sync_semaphore(hw);
	ixgbe_release_swfw_sync_semaphore(hw);

	/* Acquire and release all software resources. */
	rmask = IXGBE_GSSR_EEP_SM | IXGBE_GSSR_PHY0_SM |
		IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_MAC_CSR_SM |
		IXGBE_GSSR_SW_MNG_SM | IXGBE_GSSR_I2C_MASK;

	ixgbe_acquire_swfw_sync_X540(hw, rmask);
	ixgbe_release_swfw_sync_X540(hw, rmask);
पूर्ण

/**
 * ixgbe_blink_led_start_X540 - Blink LED based on index.
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @index: led number to blink
 *
 * Devices that implement the version 2 पूर्णांकerface:
 *   X540
 **/
s32 ixgbe_blink_led_start_X540(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 macc_reg;
	u32 ledctl_reg;
	ixgbe_link_speed speed;
	bool link_up;

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	/* Link should be up in order क्रम the blink bit in the LED control
	 * रेजिस्टर to work. Force link and speed in the MAC अगर link is करोwn.
	 * This will be reversed when we stop the blinking.
	 */
	hw->mac.ops.check_link(hw, &speed, &link_up, false);
	अगर (!link_up) अणु
		macc_reg = IXGBE_READ_REG(hw, IXGBE_MACC);
		macc_reg |= IXGBE_MACC_FLU | IXGBE_MACC_FSV_10G | IXGBE_MACC_FS;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, macc_reg);
	पूर्ण
	/* Set the LED to LINK_UP + BLINK. */
	ledctl_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	ledctl_reg &= ~IXGBE_LED_MODE_MASK(index);
	ledctl_reg |= IXGBE_LED_BLINK(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, ledctl_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण

/**
 * ixgbe_blink_led_stop_X540 - Stop blinking LED based on index.
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @index: led number to stop blinking
 *
 * Devices that implement the version 2 पूर्णांकerface:
 *   X540
 **/
s32 ixgbe_blink_led_stop_X540(काष्ठा ixgbe_hw *hw, u32 index)
अणु
	u32 macc_reg;
	u32 ledctl_reg;

	अगर (index > 3)
		वापस IXGBE_ERR_PARAM;

	/* Restore the LED to its शेष value. */
	ledctl_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	ledctl_reg &= ~IXGBE_LED_MODE_MASK(index);
	ledctl_reg |= IXGBE_LED_LINK_ACTIVE << IXGBE_LED_MODE_SHIFT(index);
	ledctl_reg &= ~IXGBE_LED_BLINK(index);
	IXGBE_WRITE_REG(hw, IXGBE_LEDCTL, ledctl_reg);

	/* Unक्रमce link and speed in the MAC. */
	macc_reg = IXGBE_READ_REG(hw, IXGBE_MACC);
	macc_reg &= ~(IXGBE_MACC_FLU | IXGBE_MACC_FSV_10G | IXGBE_MACC_FS);
	IXGBE_WRITE_REG(hw, IXGBE_MACC, macc_reg);
	IXGBE_WRITE_FLUSH(hw);

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_X540 = अणु
	.init_hw                = &ixgbe_init_hw_generic,
	.reset_hw               = &ixgbe_reset_hw_X540,
	.start_hw               = &ixgbe_start_hw_X540,
	.clear_hw_cntrs         = &ixgbe_clear_hw_cntrs_generic,
	.get_media_type         = &ixgbe_get_media_type_X540,
	.enable_rx_dma          = &ixgbe_enable_rx_dma_generic,
	.get_mac_addr           = &ixgbe_get_mac_addr_generic,
	.get_san_mac_addr       = &ixgbe_get_san_mac_addr_generic,
	.get_device_caps        = &ixgbe_get_device_caps_generic,
	.get_wwn_prefix         = &ixgbe_get_wwn_prefix_generic,
	.stop_adapter           = &ixgbe_stop_adapter_generic,
	.get_bus_info           = &ixgbe_get_bus_info_generic,
	.set_lan_id             = &ixgbe_set_lan_id_multi_port_pcie,
	.पढ़ो_analog_reg8       = शून्य,
	.ग_लिखो_analog_reg8      = शून्य,
	.setup_link             = &ixgbe_setup_mac_link_X540,
	.set_rxpba		= &ixgbe_set_rxpba_generic,
	.check_link             = &ixgbe_check_mac_link_generic,
	.get_link_capabilities  = &ixgbe_get_copper_link_capabilities_generic,
	.led_on                 = &ixgbe_led_on_generic,
	.led_off                = &ixgbe_led_off_generic,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.blink_led_start        = &ixgbe_blink_led_start_X540,
	.blink_led_stop         = &ixgbe_blink_led_stop_X540,
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
	.setup_sfp              = शून्य,
	.set_mac_anti_spoofing  = &ixgbe_set_mac_anti_spoofing,
	.set_vlan_anti_spoofing = &ixgbe_set_vlan_anti_spoofing,
	.acquire_swfw_sync      = &ixgbe_acquire_swfw_sync_X540,
	.release_swfw_sync      = &ixgbe_release_swfw_sync_X540,
	.init_swfw_sync		= &ixgbe_init_swfw_sync_X540,
	.disable_rx_buff	= &ixgbe_disable_rx_buff_generic,
	.enable_rx_buff		= &ixgbe_enable_rx_buff_generic,
	.get_thermal_sensor_data = शून्य,
	.init_thermal_sensor_thresh = शून्य,
	.prot_स्वतःc_पढ़ो	= &prot_स्वतःc_पढ़ो_generic,
	.prot_स्वतःc_ग_लिखो	= &prot_स्वतःc_ग_लिखो_generic,
	.enable_rx		= &ixgbe_enable_rx_generic,
	.disable_rx		= &ixgbe_disable_rx_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_eeprom_operations eeprom_ops_X540 = अणु
	.init_params            = &ixgbe_init_eeprom_params_X540,
	.पढ़ो                   = &ixgbe_पढ़ो_eerd_X540,
	.पढ़ो_buffer		= &ixgbe_पढ़ो_eerd_buffer_X540,
	.ग_लिखो                  = &ixgbe_ग_लिखो_eewr_X540,
	.ग_लिखो_buffer		= &ixgbe_ग_लिखो_eewr_buffer_X540,
	.calc_checksum		= &ixgbe_calc_eeprom_checksum_X540,
	.validate_checksum      = &ixgbe_validate_eeprom_checksum_X540,
	.update_checksum        = &ixgbe_update_eeprom_checksum_X540,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_X540 = अणु
	.identअगरy               = &ixgbe_identअगरy_phy_generic,
	.identअगरy_sfp           = &ixgbe_identअगरy_sfp_module_generic,
	.init			= शून्य,
	.reset                  = शून्य,
	.पढ़ो_reg               = &ixgbe_पढ़ो_phy_reg_generic,
	.ग_लिखो_reg              = &ixgbe_ग_लिखो_phy_reg_generic,
	.setup_link             = &ixgbe_setup_phy_link_generic,
	.setup_link_speed       = &ixgbe_setup_phy_link_speed_generic,
	.पढ़ो_i2c_byte          = &ixgbe_पढ़ो_i2c_byte_generic,
	.ग_लिखो_i2c_byte         = &ixgbe_ग_लिखो_i2c_byte_generic,
	.पढ़ो_i2c_sff8472	= &ixgbe_पढ़ो_i2c_sff8472_generic,
	.पढ़ो_i2c_eeprom        = &ixgbe_पढ़ो_i2c_eeprom_generic,
	.ग_लिखो_i2c_eeprom       = &ixgbe_ग_लिखो_i2c_eeprom_generic,
	.check_overtemp         = &ixgbe_tn_check_overtemp,
	.set_phy_घातer          = &ixgbe_set_copper_phy_घातer,
पूर्ण;

अटल स्थिर u32 ixgbe_mvals_X540[IXGBE_MVALS_IDX_LIMIT] = अणु
	IXGBE_MVALS_INIT(X540)
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_X540_info = अणु
	.mac                    = ixgbe_mac_X540,
	.get_invariants         = &ixgbe_get_invariants_X540,
	.mac_ops                = &mac_ops_X540,
	.eeprom_ops             = &eeprom_ops_X540,
	.phy_ops                = &phy_ops_X540,
	.mbx_ops                = &mbx_ops_generic,
	.mvals			= ixgbe_mvals_X540,
पूर्ण;

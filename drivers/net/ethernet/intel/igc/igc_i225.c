<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश <linux/delay.h>

#समावेश "igc_hw.h"

/**
 * igc_acquire_nvm_i225 - Acquire exclusive access to EEPROM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Acquire the necessary semaphores क्रम exclusive access to the EEPROM.
 * Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 * Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 * EEPROM access and वापस -IGC_ERR_NVM (-1).
 */
अटल s32 igc_acquire_nvm_i225(काष्ठा igc_hw *hw)
अणु
	वापस igc_acquire_swfw_sync_i225(hw, IGC_SWFW_EEP_SM);
पूर्ण

/**
 * igc_release_nvm_i225 - Release exclusive access to EEPROM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Stop any current commands to the EEPROM and clear the EEPROM request bit,
 * then release the semaphores acquired.
 */
अटल व्योम igc_release_nvm_i225(काष्ठा igc_hw *hw)
अणु
	igc_release_swfw_sync_i225(hw, IGC_SWFW_EEP_SM);
पूर्ण

/**
 * igc_get_hw_semaphore_i225 - Acquire hardware semaphore
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Acquire the HW semaphore to access the PHY or NVM
 */
अटल s32 igc_get_hw_semaphore_i225(काष्ठा igc_hw *hw)
अणु
	s32 समयout = hw->nvm.word_size + 1;
	s32 i = 0;
	u32 swsm;

	/* Get the SW semaphore */
	जबतक (i < समयout) अणु
		swsm = rd32(IGC_SWSM);
		अगर (!(swsm & IGC_SWSM_SMBI))
			अवरोध;

		usleep_range(500, 600);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		/* In rare circumstances, the SW semaphore may alपढ़ोy be held
		 * unपूर्णांकentionally. Clear the semaphore once beक्रमe giving up.
		 */
		अगर (hw->dev_spec._base.clear_semaphore_once) अणु
			hw->dev_spec._base.clear_semaphore_once = false;
			igc_put_hw_semaphore(hw);
			क्रम (i = 0; i < समयout; i++) अणु
				swsm = rd32(IGC_SWSM);
				अगर (!(swsm & IGC_SWSM_SMBI))
					अवरोध;

				usleep_range(500, 600);
			पूर्ण
		पूर्ण

		/* If we करो not have the semaphore here, we have to give up. */
		अगर (i == समयout) अणु
			hw_dbg("Driver can't access device - SMBI bit is set.\n");
			वापस -IGC_ERR_NVM;
		पूर्ण
	पूर्ण

	/* Get the FW semaphore. */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = rd32(IGC_SWSM);
		wr32(IGC_SWSM, swsm | IGC_SWSM_SWESMBI);

		/* Semaphore acquired अगर bit latched */
		अगर (rd32(IGC_SWSM) & IGC_SWSM_SWESMBI)
			अवरोध;

		usleep_range(500, 600);
	पूर्ण

	अगर (i == समयout) अणु
		/* Release semaphores */
		igc_put_hw_semaphore(hw);
		hw_dbg("Driver can't access the NVM\n");
		वापस -IGC_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * igc_acquire_swfw_sync_i225 - Acquire SW/FW semaphore
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @mask: specअगरies which semaphore to acquire
 *
 * Acquire the SW/FW semaphore to access the PHY or NVM.  The mask
 * will also specअगरy which port we're acquiring the lock क्रम.
 */
s32 igc_acquire_swfw_sync_i225(काष्ठा igc_hw *hw, u16 mask)
अणु
	s32 i = 0, समयout = 200;
	u32 fwmask = mask << 16;
	u32 swmask = mask;
	s32 ret_val = 0;
	u32 swfw_sync;

	जबतक (i < समयout) अणु
		अगर (igc_get_hw_semaphore_i225(hw)) अणु
			ret_val = -IGC_ERR_SWFW_SYNC;
			जाओ out;
		पूर्ण

		swfw_sync = rd32(IGC_SW_FW_SYNC);
		अगर (!(swfw_sync & (fwmask | swmask)))
			अवरोध;

		/* Firmware currently using resource (fwmask) */
		igc_put_hw_semaphore(hw);
		mdelay(5);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		hw_dbg("Driver can't access resource, SW_FW_SYNC timeout.\n");
		ret_val = -IGC_ERR_SWFW_SYNC;
		जाओ out;
	पूर्ण

	swfw_sync |= swmask;
	wr32(IGC_SW_FW_SYNC, swfw_sync);

	igc_put_hw_semaphore(hw);
out:
	वापस ret_val;
पूर्ण

/**
 * igc_release_swfw_sync_i225 - Release SW/FW semaphore
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @mask: specअगरies which semaphore to acquire
 *
 * Release the SW/FW semaphore used to access the PHY or NVM.  The mask
 * will also specअगरy which port we're releasing the lock क्रम.
 */
व्योम igc_release_swfw_sync_i225(काष्ठा igc_hw *hw, u16 mask)
अणु
	u32 swfw_sync;

	जबतक (igc_get_hw_semaphore_i225(hw))
		; /* Empty */

	swfw_sync = rd32(IGC_SW_FW_SYNC);
	swfw_sync &= ~mask;
	wr32(IGC_SW_FW_SYNC, swfw_sync);

	igc_put_hw_semaphore(hw);
पूर्ण

/**
 * igc_पढ़ो_nvm_srrd_i225 - Reads Shaकरोw Ram using EERD रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of word in the Shaकरोw Ram to पढ़ो
 * @words: number of words to पढ़ो
 * @data: word पढ़ो from the Shaकरोw Ram
 *
 * Reads a 16 bit word from the Shaकरोw Ram using the EERD रेजिस्टर.
 * Uses necessary synchronization semaphores.
 */
अटल s32 igc_पढ़ो_nvm_srrd_i225(काष्ठा igc_hw *hw, u16 offset, u16 words,
				  u16 *data)
अणु
	s32 status = 0;
	u16 i, count;

	/* We cannot hold synchronization semaphores क्रम too दीर्घ,
	 * because of क्रमceful takeover procedure. However it is more efficient
	 * to पढ़ो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += IGC_EERD_EEWR_MAX_COUNT) अणु
		count = (words - i) / IGC_EERD_EEWR_MAX_COUNT > 0 ?
			IGC_EERD_EEWR_MAX_COUNT : (words - i);

		status = hw->nvm.ops.acquire(hw);
		अगर (status)
			अवरोध;

		status = igc_पढ़ो_nvm_eerd(hw, offset, count, data + i);
		hw->nvm.ops.release(hw);
		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * igc_ग_लिखो_nvm_srwr - Write to Shaकरोw Ram using EEWR
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset within the Shaकरोw Ram to be written to
 * @words: number of words to ग_लिखो
 * @data: 16 bit word(s) to be written to the Shaकरोw Ram
 *
 * Writes data to Shaकरोw Ram at offset using EEWR रेजिस्टर.
 *
 * If igc_update_nvm_checksum is not called after this function , the
 * Shaकरोw Ram will most likely contain an invalid checksum.
 */
अटल s32 igc_ग_लिखो_nvm_srwr(काष्ठा igc_hw *hw, u16 offset, u16 words,
			      u16 *data)
अणु
	काष्ठा igc_nvm_info *nvm = &hw->nvm;
	s32 ret_val = -IGC_ERR_NVM;
	u32 attempts = 100000;
	u32 i, k, eewr = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * too many words क्रम the offset, and not enough words.
	 */
	अगर (offset >= nvm->word_size || (words > (nvm->word_size - offset)) ||
	    words == 0) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		वापस ret_val;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		ret_val = -IGC_ERR_NVM;
		eewr = ((offset + i) << IGC_NVM_RW_ADDR_SHIFT) |
			(data[i] << IGC_NVM_RW_REG_DATA) |
			IGC_NVM_RW_REG_START;

		wr32(IGC_SRWR, eewr);

		क्रम (k = 0; k < attempts; k++) अणु
			अगर (IGC_NVM_RW_REG_DONE &
			    rd32(IGC_SRWR)) अणु
				ret_val = 0;
				अवरोध;
			पूर्ण
			udelay(5);
		पूर्ण

		अगर (ret_val) अणु
			hw_dbg("Shadow RAM write EEWR timed out\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_ग_लिखो_nvm_srwr_i225 - Write to Shaकरोw RAM using EEWR
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset within the Shaकरोw RAM to be written to
 * @words: number of words to ग_लिखो
 * @data: 16 bit word(s) to be written to the Shaकरोw RAM
 *
 * Writes data to Shaकरोw RAM at offset using EEWR रेजिस्टर.
 *
 * If igc_update_nvm_checksum is not called after this function , the
 * data will not be committed to FLASH and also Shaकरोw RAM will most likely
 * contain an invalid checksum.
 *
 * If error code is वापसed, data and Shaकरोw RAM may be inconsistent - buffer
 * partially written.
 */
अटल s32 igc_ग_लिखो_nvm_srwr_i225(काष्ठा igc_hw *hw, u16 offset, u16 words,
				   u16 *data)
अणु
	s32 status = 0;
	u16 i, count;

	/* We cannot hold synchronization semaphores क्रम too दीर्घ,
	 * because of क्रमceful takeover procedure. However it is more efficient
	 * to ग_लिखो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += IGC_EERD_EEWR_MAX_COUNT) अणु
		count = (words - i) / IGC_EERD_EEWR_MAX_COUNT > 0 ?
			IGC_EERD_EEWR_MAX_COUNT : (words - i);

		status = hw->nvm.ops.acquire(hw);
		अगर (status)
			अवरोध;

		status = igc_ग_लिखो_nvm_srwr(hw, offset, count, data + i);
		hw->nvm.ops.release(hw);
		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * igc_validate_nvm_checksum_i225 - Validate EEPROM checksum
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 * and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 */
अटल s32 igc_validate_nvm_checksum_i225(काष्ठा igc_hw *hw)
अणु
	s32 (*पढ़ो_op_ptr)(काष्ठा igc_hw *hw, u16 offset, u16 count,
			   u16 *data);
	s32 status = 0;

	status = hw->nvm.ops.acquire(hw);
	अगर (status)
		जाओ out;

	/* Replace the पढ़ो function with semaphore grabbing with
	 * the one that skips this क्रम a जबतक.
	 * We have semaphore taken alपढ़ोy here.
	 */
	पढ़ो_op_ptr = hw->nvm.ops.पढ़ो;
	hw->nvm.ops.पढ़ो = igc_पढ़ो_nvm_eerd;

	status = igc_validate_nvm_checksum(hw);

	/* Revert original पढ़ो operation. */
	hw->nvm.ops.पढ़ो = पढ़ो_op_ptr;

	hw->nvm.ops.release(hw);

out:
	वापस status;
पूर्ण

/**
 * igc_pool_flash_update_करोne_i225 - Pool FLUDONE status
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
अटल s32 igc_pool_flash_update_करोne_i225(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = -IGC_ERR_NVM;
	u32 i, reg;

	क्रम (i = 0; i < IGC_FLUDONE_ATTEMPTS; i++) अणु
		reg = rd32(IGC_EECD);
		अगर (reg & IGC_EECD_FLUDONE_I225) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_update_flash_i225 - Commit EEPROM to the flash
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
अटल s32 igc_update_flash_i225(काष्ठा igc_hw *hw)
अणु
	s32 ret_val = 0;
	u32 flup;

	ret_val = igc_pool_flash_update_करोne_i225(hw);
	अगर (ret_val == -IGC_ERR_NVM) अणु
		hw_dbg("Flash update time out\n");
		जाओ out;
	पूर्ण

	flup = rd32(IGC_EECD) | IGC_EECD_FLUPD_I225;
	wr32(IGC_EECD, flup);

	ret_val = igc_pool_flash_update_करोne_i225(hw);
	अगर (ret_val)
		hw_dbg("Flash update time out\n");
	अन्यथा
		hw_dbg("Flash update complete\n");

out:
	वापस ret_val;
पूर्ण

/**
 * igc_update_nvm_checksum_i225 - Update EEPROM checksum
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 * up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 * value to the EEPROM. Next commit EEPROM data onto the Flash.
 */
अटल s32 igc_update_nvm_checksum_i225(काष्ठा igc_hw *hw)
अणु
	u16 checksum = 0;
	s32 ret_val = 0;
	u16 i, nvm_data;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	ret_val = igc_पढ़ो_nvm_eerd(hw, 0, 1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("EEPROM read failed\n");
		जाओ out;
	पूर्ण

	ret_val = hw->nvm.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	/* Do not use hw->nvm.ops.ग_लिखो, hw->nvm.ops.पढ़ो
	 * because we करो not want to take the synchronization
	 * semaphores twice here.
	 */

	क्रम (i = 0; i < NVM_CHECKSUM_REG; i++) अणु
		ret_val = igc_पढ़ो_nvm_eerd(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw->nvm.ops.release(hw);
			hw_dbg("NVM Read Error while updating checksum.\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण
	checksum = (u16)NVM_SUM - checksum;
	ret_val = igc_ग_लिखो_nvm_srwr(hw, NVM_CHECKSUM_REG, 1,
				     &checksum);
	अगर (ret_val) अणु
		hw->nvm.ops.release(hw);
		hw_dbg("NVM Write Error while updating checksum.\n");
		जाओ out;
	पूर्ण

	hw->nvm.ops.release(hw);

	ret_val = igc_update_flash_i225(hw);

out:
	वापस ret_val;
पूर्ण

/**
 * igc_get_flash_presence_i225 - Check अगर flash device is detected
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
bool igc_get_flash_presence_i225(काष्ठा igc_hw *hw)
अणु
	bool ret_val = false;
	u32 eec = 0;

	eec = rd32(IGC_EECD);
	अगर (eec & IGC_EECD_FLASH_DETECTED_I225)
		ret_val = true;

	वापस ret_val;
पूर्ण

/**
 * igc_init_nvm_params_i225 - Init NVM func ptrs.
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
s32 igc_init_nvm_params_i225(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquire = igc_acquire_nvm_i225;
	nvm->ops.release = igc_release_nvm_i225;

	/* NVM Function Poपूर्णांकers */
	अगर (igc_get_flash_presence_i225(hw)) अणु
		hw->nvm.type = igc_nvm_flash_hw;
		nvm->ops.पढ़ो = igc_पढ़ो_nvm_srrd_i225;
		nvm->ops.ग_लिखो = igc_ग_लिखो_nvm_srwr_i225;
		nvm->ops.validate = igc_validate_nvm_checksum_i225;
		nvm->ops.update = igc_update_nvm_checksum_i225;
	पूर्ण अन्यथा अणु
		hw->nvm.type = igc_nvm_invm;
		nvm->ops.पढ़ो = igc_पढ़ो_nvm_eerd;
		nvm->ops.ग_लिखो = शून्य;
		nvm->ops.validate = शून्य;
		nvm->ops.update = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *  igc_set_eee_i225 - Enable/disable EEE support
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @adv2p5G: boolean flag enabling 2.5G EEE advertisement
 *  @adv1G: boolean flag enabling 1G EEE advertisement
 *  @adv100M: boolean flag enabling 100M EEE advertisement
 *
 *  Enable/disable EEE based on setting in dev_spec काष्ठाure.
 **/
s32 igc_set_eee_i225(काष्ठा igc_hw *hw, bool adv2p5G, bool adv1G,
		     bool adv100M)
अणु
	u32 ipcnfg, eeer;

	ipcnfg = rd32(IGC_IPCNFG);
	eeer = rd32(IGC_EEER);

	/* enable or disable per user setting */
	अगर (hw->dev_spec._base.eee_enable) अणु
		u32 eee_su = rd32(IGC_EEE_SU);

		अगर (adv100M)
			ipcnfg |= IGC_IPCNFG_EEE_100M_AN;
		अन्यथा
			ipcnfg &= ~IGC_IPCNFG_EEE_100M_AN;

		अगर (adv1G)
			ipcnfg |= IGC_IPCNFG_EEE_1G_AN;
		अन्यथा
			ipcnfg &= ~IGC_IPCNFG_EEE_1G_AN;

		अगर (adv2p5G)
			ipcnfg |= IGC_IPCNFG_EEE_2_5G_AN;
		अन्यथा
			ipcnfg &= ~IGC_IPCNFG_EEE_2_5G_AN;

		eeer |= (IGC_EEER_TX_LPI_EN | IGC_EEER_RX_LPI_EN |
			 IGC_EEER_LPI_FC);

		/* This bit should not be set in normal operation. */
		अगर (eee_su & IGC_EEE_SU_LPI_CLK_STP)
			hw_dbg("LPI Clock Stop Bit should not be set!\n");
	पूर्ण अन्यथा अणु
		ipcnfg &= ~(IGC_IPCNFG_EEE_2_5G_AN | IGC_IPCNFG_EEE_1G_AN |
			    IGC_IPCNFG_EEE_100M_AN);
		eeer &= ~(IGC_EEER_TX_LPI_EN | IGC_EEER_RX_LPI_EN |
			  IGC_EEER_LPI_FC);
	पूर्ण
	wr32(IGC_IPCNFG, ipcnfg);
	wr32(IGC_EEER, eeer);
	rd32(IGC_IPCNFG);
	rd32(IGC_EEER);

	वापस IGC_SUCCESS;
पूर्ण

/* igc_set_ltr_i225 - Set Latency Tolerance Reporting thresholds
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @link: bool indicating link status
 *
 * Set the LTR thresholds based on the link speed (Mbps), EEE, and DMAC
 * settings, otherwise specअगरy that there is no LTR requirement.
 */
s32 igc_set_ltr_i225(काष्ठा igc_hw *hw, bool link)
अणु
	u32 tw_प्रणाली, ltrc, ltrv, ltr_min, ltr_max, scale_min, scale_max;
	u16 speed, duplex;
	s32 size;

	/* If we करो not have link, LTR thresholds are zero. */
	अगर (link) अणु
		hw->mac.ops.get_speed_and_duplex(hw, &speed, &duplex);

		/* Check अगर using copper पूर्णांकerface with EEE enabled or अगर the
		 * link speed is 10 Mbps.
		 */
		अगर (hw->dev_spec._base.eee_enable &&
		    speed != SPEED_10) अणु
			/* EEE enabled, so send LTRMAX threshold. */
			ltrc = rd32(IGC_LTRC) |
			       IGC_LTRC_EEEMS_EN;
			wr32(IGC_LTRC, ltrc);

			/* Calculate tw_प्रणाली (nsec). */
			अगर (speed == SPEED_100) अणु
				tw_प्रणाली = ((rd32(IGC_EEE_SU) &
					     IGC_TW_SYSTEM_100_MASK) >>
					     IGC_TW_SYSTEM_100_SHIFT) * 500;
			पूर्ण अन्यथा अणु
				tw_प्रणाली = (rd32(IGC_EEE_SU) &
					     IGC_TW_SYSTEM_1000_MASK) * 500;
			पूर्ण
		पूर्ण अन्यथा अणु
			tw_प्रणाली = 0;
		पूर्ण

		/* Get the Rx packet buffer size. */
		size = rd32(IGC_RXPBS) &
		       IGC_RXPBS_SIZE_I225_MASK;

		/* Calculations vary based on DMAC settings. */
		अगर (rd32(IGC_DMACR) & IGC_DMACR_DMAC_EN) अणु
			size -= (rd32(IGC_DMACR) &
				 IGC_DMACR_DMACTHR_MASK) >>
				 IGC_DMACR_DMACTHR_SHIFT;
			/* Convert size to bits. */
			size *= 1024 * 8;
		पूर्ण अन्यथा अणु
			/* Convert size to bytes, subtract the MTU, and then
			 * convert the size to bits.
			 */
			size *= 1024;
			size *= 8;
		पूर्ण

		अगर (size < 0) अणु
			hw_dbg("Invalid effective Rx buffer size %d\n",
			       size);
			वापस -IGC_ERR_CONFIG;
		पूर्ण

		/* Calculate the thresholds. Since speed is in Mbps, simplअगरy
		 * the calculation by multiplying size/speed by 1000 क्रम result
		 * to be in nsec beक्रमe भागiding by the scale in nsec. Set the
		 * scale such that the LTR threshold fits in the रेजिस्टर.
		 */
		ltr_min = (1000 * size) / speed;
		ltr_max = ltr_min + tw_प्रणाली;
		scale_min = (ltr_min / 1024) < 1024 ? IGC_LTRMINV_SCALE_1024 :
			    IGC_LTRMINV_SCALE_32768;
		scale_max = (ltr_max / 1024) < 1024 ? IGC_LTRMAXV_SCALE_1024 :
			    IGC_LTRMAXV_SCALE_32768;
		ltr_min /= scale_min == IGC_LTRMINV_SCALE_1024 ? 1024 : 32768;
		ltr_min -= 1;
		ltr_max /= scale_max == IGC_LTRMAXV_SCALE_1024 ? 1024 : 32768;
		ltr_max -= 1;

		/* Only ग_लिखो the LTR thresholds अगर they dअगरfer from beक्रमe. */
		ltrv = rd32(IGC_LTRMINV);
		अगर (ltr_min != (ltrv & IGC_LTRMINV_LTRV_MASK)) अणु
			ltrv = IGC_LTRMINV_LSNP_REQ | ltr_min |
			       (scale_min << IGC_LTRMINV_SCALE_SHIFT);
			wr32(IGC_LTRMINV, ltrv);
		पूर्ण

		ltrv = rd32(IGC_LTRMAXV);
		अगर (ltr_max != (ltrv & IGC_LTRMAXV_LTRV_MASK)) अणु
			ltrv = IGC_LTRMAXV_LSNP_REQ | ltr_max |
			       (scale_min << IGC_LTRMAXV_SCALE_SHIFT);
			wr32(IGC_LTRMAXV, ltrv);
		पूर्ण
	पूर्ण

	वापस IGC_SUCCESS;
पूर्ण

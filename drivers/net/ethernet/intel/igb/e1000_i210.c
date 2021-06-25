<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

/* e1000_i210
 * e1000_i211
 */

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#समावेश "e1000_hw.h"
#समावेश "e1000_i210.h"

अटल s32 igb_update_flash_i210(काष्ठा e1000_hw *hw);

/**
 * igb_get_hw_semaphore_i210 - Acquire hardware semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the HW semaphore to access the PHY or NVM
 */
अटल s32 igb_get_hw_semaphore_i210(काष्ठा e1000_hw *hw)
अणु
	u32 swsm;
	s32 समयout = hw->nvm.word_size + 1;
	s32 i = 0;

	/* Get the SW semaphore */
	जबतक (i < समयout) अणु
		swsm = rd32(E1000_SWSM);
		अगर (!(swsm & E1000_SWSM_SMBI))
			अवरोध;

		udelay(50);
		i++;
	पूर्ण

	अगर (i == समयout) अणु
		/* In rare circumstances, the SW semaphore may alपढ़ोy be held
		 * unपूर्णांकentionally. Clear the semaphore once beक्रमe giving up.
		 */
		अगर (hw->dev_spec._82575.clear_semaphore_once) अणु
			hw->dev_spec._82575.clear_semaphore_once = false;
			igb_put_hw_semaphore(hw);
			क्रम (i = 0; i < समयout; i++) अणु
				swsm = rd32(E1000_SWSM);
				अगर (!(swsm & E1000_SWSM_SMBI))
					अवरोध;

				udelay(50);
			पूर्ण
		पूर्ण

		/* If we करो not have the semaphore here, we have to give up. */
		अगर (i == समयout) अणु
			hw_dbg("Driver can't access device - SMBI bit is set.\n");
			वापस -E1000_ERR_NVM;
		पूर्ण
	पूर्ण

	/* Get the FW semaphore. */
	क्रम (i = 0; i < समयout; i++) अणु
		swsm = rd32(E1000_SWSM);
		wr32(E1000_SWSM, swsm | E1000_SWSM_SWESMBI);

		/* Semaphore acquired अगर bit latched */
		अगर (rd32(E1000_SWSM) & E1000_SWSM_SWESMBI)
			अवरोध;

		udelay(50);
	पूर्ण

	अगर (i == समयout) अणु
		/* Release semaphores */
		igb_put_hw_semaphore(hw);
		hw_dbg("Driver can't access the NVM\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_acquire_nvm_i210 - Request क्रम access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Acquire the necessary semaphores क्रम exclusive access to the EEPROM.
 *  Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 *  Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 *  EEPROM access and वापस -E1000_ERR_NVM (-1).
 **/
अटल s32 igb_acquire_nvm_i210(काष्ठा e1000_hw *hw)
अणु
	वापस igb_acquire_swfw_sync_i210(hw, E1000_SWFW_EEP_SM);
पूर्ण

/**
 *  igb_release_nvm_i210 - Release exclusive access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Stop any current commands to the EEPROM and clear the EEPROM request bit,
 *  then release the semaphores acquired.
 **/
अटल व्योम igb_release_nvm_i210(काष्ठा e1000_hw *hw)
अणु
	igb_release_swfw_sync_i210(hw, E1000_SWFW_EEP_SM);
पूर्ण

/**
 *  igb_acquire_swfw_sync_i210 - Acquire SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Acquire the SW/FW semaphore to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're acquiring the lock क्रम.
 **/
s32 igb_acquire_swfw_sync_i210(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 ret_val = 0;
	s32 i = 0, समयout = 200; /* FIXME: find real value to use here */

	जबतक (i < समयout) अणु
		अगर (igb_get_hw_semaphore_i210(hw)) अणु
			ret_val = -E1000_ERR_SWFW_SYNC;
			जाओ out;
		पूर्ण

		swfw_sync = rd32(E1000_SW_FW_SYNC);
		अगर (!(swfw_sync & (fwmask | swmask)))
			अवरोध;

		/* Firmware currently using resource (fwmask) */
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
 *  igb_release_swfw_sync_i210 - Release SW/FW semaphore
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @mask: specअगरies which semaphore to acquire
 *
 *  Release the SW/FW semaphore used to access the PHY or NVM.  The mask
 *  will also specअगरy which port we're releasing the lock क्रम.
 **/
व्योम igb_release_swfw_sync_i210(काष्ठा e1000_hw *hw, u16 mask)
अणु
	u32 swfw_sync;

	जबतक (igb_get_hw_semaphore_i210(hw))
		; /* Empty */

	swfw_sync = rd32(E1000_SW_FW_SYNC);
	swfw_sync &= ~mask;
	wr32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphore(hw);
पूर्ण

/**
 *  igb_पढ़ो_nvm_srrd_i210 - Reads Shaकरोw Ram using EERD रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of word in the Shaकरोw Ram to पढ़ो
 *  @words: number of words to पढ़ो
 *  @data: word पढ़ो from the Shaकरोw Ram
 *
 *  Reads a 16 bit word from the Shaकरोw Ram using the EERD रेजिस्टर.
 *  Uses necessary synchronization semaphores.
 **/
अटल s32 igb_पढ़ो_nvm_srrd_i210(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				  u16 *data)
अणु
	s32 status = 0;
	u16 i, count;

	/* We cannot hold synchronization semaphores क्रम too दीर्घ,
	 * because of क्रमceful takeover procedure. However it is more efficient
	 * to पढ़ो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += E1000_EERD_EEWR_MAX_COUNT) अणु
		count = (words - i) / E1000_EERD_EEWR_MAX_COUNT > 0 ?
			E1000_EERD_EEWR_MAX_COUNT : (words - i);
		अगर (!(hw->nvm.ops.acquire(hw))) अणु
			status = igb_पढ़ो_nvm_eerd(hw, offset, count,
						     data + i);
			hw->nvm.ops.release(hw);
		पूर्ण अन्यथा अणु
			status = E1000_ERR_SWFW_SYNC;
		पूर्ण

		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 *  igb_ग_लिखो_nvm_srwr - Write to Shaकरोw Ram using EEWR
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the Shaकरोw Ram to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the Shaकरोw Ram
 *
 *  Writes data to Shaकरोw Ram at offset using EEWR रेजिस्टर.
 *
 *  If igb_update_nvm_checksum is not called after this function , the
 *  Shaकरोw Ram will most likely contain an invalid checksum.
 **/
अटल s32 igb_ग_लिखो_nvm_srwr(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 i, k, eewr = 0;
	u32 attempts = 100000;
	s32 ret_val = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * too many words क्रम the offset, and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		eewr = ((offset+i) << E1000_NVM_RW_ADDR_SHIFT) |
			(data[i] << E1000_NVM_RW_REG_DATA) |
			E1000_NVM_RW_REG_START;

		wr32(E1000_SRWR, eewr);

		क्रम (k = 0; k < attempts; k++) अणु
			अगर (E1000_NVM_RW_REG_DONE &
			    rd32(E1000_SRWR)) अणु
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

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_nvm_srwr_i210 - Write to Shaकरोw RAM using EEWR
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the Shaकरोw RAM to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the Shaकरोw RAM
 *
 *  Writes data to Shaकरोw RAM at offset using EEWR रेजिस्टर.
 *
 *  If e1000_update_nvm_checksum is not called after this function , the
 *  data will not be committed to FLASH and also Shaकरोw RAM will most likely
 *  contain an invalid checksum.
 *
 *  If error code is वापसed, data and Shaकरोw RAM may be inconsistent - buffer
 *  partially written.
 **/
अटल s32 igb_ग_लिखो_nvm_srwr_i210(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				   u16 *data)
अणु
	s32 status = 0;
	u16 i, count;

	/* We cannot hold synchronization semaphores क्रम too दीर्घ,
	 * because of क्रमceful takeover procedure. However it is more efficient
	 * to ग_लिखो in bursts than synchronizing access क्रम each word.
	 */
	क्रम (i = 0; i < words; i += E1000_EERD_EEWR_MAX_COUNT) अणु
		count = (words - i) / E1000_EERD_EEWR_MAX_COUNT > 0 ?
			E1000_EERD_EEWR_MAX_COUNT : (words - i);
		अगर (!(hw->nvm.ops.acquire(hw))) अणु
			status = igb_ग_लिखो_nvm_srwr(hw, offset, count,
						      data + i);
			hw->nvm.ops.release(hw);
		पूर्ण अन्यथा अणु
			status = E1000_ERR_SWFW_SYNC;
		पूर्ण

		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 *  igb_पढ़ो_invm_word_i210 - Reads OTP
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @address: the word address (aka eeprom offset) to पढ़ो
 *  @data: poपूर्णांकer to the data पढ़ो
 *
 *  Reads 16-bit words from the OTP. Return error when the word is not
 *  stored in OTP.
 **/
अटल s32 igb_पढ़ो_invm_word_i210(काष्ठा e1000_hw *hw, u8 address, u16 *data)
अणु
	s32 status = -E1000_ERR_INVM_VALUE_NOT_FOUND;
	u32 invm_dword;
	u16 i;
	u8 record_type, word_address;

	क्रम (i = 0; i < E1000_INVM_SIZE; i++) अणु
		invm_dword = rd32(E1000_INVM_DATA_REG(i));
		/* Get record type */
		record_type = INVM_DWORD_TO_RECORD_TYPE(invm_dword);
		अगर (record_type == E1000_INVM_UNINITIALIZED_STRUCTURE)
			अवरोध;
		अगर (record_type == E1000_INVM_CSR_AUTOLOAD_STRUCTURE)
			i += E1000_INVM_CSR_AUTOLOAD_DATA_SIZE_IN_DWORDS;
		अगर (record_type == E1000_INVM_RSA_KEY_SHA256_STRUCTURE)
			i += E1000_INVM_RSA_KEY_SHA256_DATA_SIZE_IN_DWORDS;
		अगर (record_type == E1000_INVM_WORD_AUTOLOAD_STRUCTURE) अणु
			word_address = INVM_DWORD_TO_WORD_ADDRESS(invm_dword);
			अगर (word_address == address) अणु
				*data = INVM_DWORD_TO_WORD_DATA(invm_dword);
				hw_dbg("Read INVM Word 0x%02x = %x\n",
					  address, *data);
				status = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (status)
		hw_dbg("Requested word 0x%02x not found in OTP\n", address);
	वापस status;
पूर्ण

/**
 * igb_पढ़ो_invm_i210 - Read invm wrapper function क्रम I210/I211
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset to पढ़ो from
 *  @words: number of words to पढ़ो (unused)
 *  @data: poपूर्णांकer to the data पढ़ो
 *
 *  Wrapper function to वापस data क्रमmerly found in the NVM.
 **/
अटल s32 igb_पढ़ो_invm_i210(काष्ठा e1000_hw *hw, u16 offset,
				u16 __always_unused words, u16 *data)
अणु
	s32 ret_val = 0;

	/* Only the MAC addr is required to be present in the iNVM */
	चयन (offset) अणु
	हाल NVM_MAC_ADDR:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, &data[0]);
		ret_val |= igb_पढ़ो_invm_word_i210(hw, (u8)offset+1,
						     &data[1]);
		ret_val |= igb_पढ़ो_invm_word_i210(hw, (u8)offset+2,
						     &data[2]);
		अगर (ret_val)
			hw_dbg("MAC Addr not found in iNVM\n");
		अवरोध;
	हाल NVM_INIT_CTRL_2:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, data);
		अगर (ret_val) अणु
			*data = NVM_INIT_CTRL_2_DEFAULT_I211;
			ret_val = 0;
		पूर्ण
		अवरोध;
	हाल NVM_INIT_CTRL_4:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, data);
		अगर (ret_val) अणु
			*data = NVM_INIT_CTRL_4_DEFAULT_I211;
			ret_val = 0;
		पूर्ण
		अवरोध;
	हाल NVM_LED_1_CFG:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, data);
		अगर (ret_val) अणु
			*data = NVM_LED_1_CFG_DEFAULT_I211;
			ret_val = 0;
		पूर्ण
		अवरोध;
	हाल NVM_LED_0_2_CFG:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, data);
		अगर (ret_val) अणु
			*data = NVM_LED_0_2_CFG_DEFAULT_I211;
			ret_val = 0;
		पूर्ण
		अवरोध;
	हाल NVM_ID_LED_SETTINGS:
		ret_val = igb_पढ़ो_invm_word_i210(hw, (u8)offset, data);
		अगर (ret_val) अणु
			*data = ID_LED_RESERVED_FFFF;
			ret_val = 0;
		पूर्ण
		अवरोध;
	हाल NVM_SUB_DEV_ID:
		*data = hw->subप्रणाली_device_id;
		अवरोध;
	हाल NVM_SUB_VEN_ID:
		*data = hw->subप्रणाली_venकरोr_id;
		अवरोध;
	हाल NVM_DEV_ID:
		*data = hw->device_id;
		अवरोध;
	हाल NVM_VEN_ID:
		*data = hw->venकरोr_id;
		अवरोध;
	शेष:
		hw_dbg("NVM word 0x%02x is not mapped.\n", offset);
		*data = NVM_RESERVED_WORD;
		अवरोध;
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_invm_version - Reads iNVM version and image type
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @invm_ver: version काष्ठाure क्रम the version पढ़ो
 *
 *  Reads iNVM version and image type.
 **/
s32 igb_पढ़ो_invm_version(काष्ठा e1000_hw *hw,
			  काष्ठा e1000_fw_version *invm_ver) अणु
	u32 *record = शून्य;
	u32 *next_record = शून्य;
	u32 i = 0;
	u32 invm_dword = 0;
	u32 invm_blocks = E1000_INVM_SIZE - (E1000_INVM_ULT_BYTES_SIZE /
					     E1000_INVM_RECORD_SIZE_IN_BYTES);
	u32 buffer[E1000_INVM_SIZE];
	s32 status = -E1000_ERR_INVM_VALUE_NOT_FOUND;
	u16 version = 0;

	/* Read iNVM memory */
	क्रम (i = 0; i < E1000_INVM_SIZE; i++) अणु
		invm_dword = rd32(E1000_INVM_DATA_REG(i));
		buffer[i] = invm_dword;
	पूर्ण

	/* Read version number */
	क्रम (i = 1; i < invm_blocks; i++) अणु
		record = &buffer[invm_blocks - i];
		next_record = &buffer[invm_blocks - i + 1];

		/* Check अगर we have first version location used */
		अगर ((i == 1) && ((*record & E1000_INVM_VER_FIELD_ONE) == 0)) अणु
			version = 0;
			status = 0;
			अवरोध;
		पूर्ण
		/* Check अगर we have second version location used */
		अन्यथा अगर ((i == 1) &&
			 ((*record & E1000_INVM_VER_FIELD_TWO) == 0)) अणु
			version = (*record & E1000_INVM_VER_FIELD_ONE) >> 3;
			status = 0;
			अवरोध;
		पूर्ण
		/* Check अगर we have odd version location
		 * used and it is the last one used
		 */
		अन्यथा अगर ((((*record & E1000_INVM_VER_FIELD_ONE) == 0) &&
			 ((*record & 0x3) == 0)) || (((*record & 0x3) != 0) &&
			 (i != 1))) अणु
			version = (*next_record & E1000_INVM_VER_FIELD_TWO)
				  >> 13;
			status = 0;
			अवरोध;
		पूर्ण
		/* Check अगर we have even version location
		 * used and it is the last one used
		 */
		अन्यथा अगर (((*record & E1000_INVM_VER_FIELD_TWO) == 0) &&
			 ((*record & 0x3) == 0)) अणु
			version = (*record & E1000_INVM_VER_FIELD_ONE) >> 3;
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!status) अणु
		invm_ver->invm_major = (version & E1000_INVM_MAJOR_MASK)
					>> E1000_INVM_MAJOR_SHIFT;
		invm_ver->invm_minor = version & E1000_INVM_MINOR_MASK;
	पूर्ण
	/* Read Image Type */
	क्रम (i = 1; i < invm_blocks; i++) अणु
		record = &buffer[invm_blocks - i];
		next_record = &buffer[invm_blocks - i + 1];

		/* Check अगर we have image type in first location used */
		अगर ((i == 1) && ((*record & E1000_INVM_IMGTYPE_FIELD) == 0)) अणु
			invm_ver->invm_img_type = 0;
			status = 0;
			अवरोध;
		पूर्ण
		/* Check अगर we have image type in first location used */
		अन्यथा अगर ((((*record & 0x3) == 0) &&
			 ((*record & E1000_INVM_IMGTYPE_FIELD) == 0)) ||
			 ((((*record & 0x3) != 0) && (i != 1)))) अणु
			invm_ver->invm_img_type =
				(*next_record & E1000_INVM_IMGTYPE_FIELD) >> 23;
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 *  igb_validate_nvm_checksum_i210 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 **/
अटल s32 igb_validate_nvm_checksum_i210(काष्ठा e1000_hw *hw)
अणु
	s32 status = 0;
	s32 (*पढ़ो_op_ptr)(काष्ठा e1000_hw *, u16, u16, u16 *);

	अगर (!(hw->nvm.ops.acquire(hw))) अणु

		/* Replace the पढ़ो function with semaphore grabbing with
		 * the one that skips this क्रम a जबतक.
		 * We have semaphore taken alपढ़ोy here.
		 */
		पढ़ो_op_ptr = hw->nvm.ops.पढ़ो;
		hw->nvm.ops.पढ़ो = igb_पढ़ो_nvm_eerd;

		status = igb_validate_nvm_checksum(hw);

		/* Revert original पढ़ो operation. */
		hw->nvm.ops.पढ़ो = पढ़ो_op_ptr;

		hw->nvm.ops.release(hw);
	पूर्ण अन्यथा अणु
		status = E1000_ERR_SWFW_SYNC;
	पूर्ण

	वापस status;
पूर्ण

/**
 *  igb_update_nvm_checksum_i210 - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 *  value to the EEPROM. Next commit EEPROM data onto the Flash.
 **/
अटल s32 igb_update_nvm_checksum_i210(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	ret_val = igb_पढ़ो_nvm_eerd(hw, 0, 1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("EEPROM read failed\n");
		जाओ out;
	पूर्ण

	अगर (!(hw->nvm.ops.acquire(hw))) अणु
		/* Do not use hw->nvm.ops.ग_लिखो, hw->nvm.ops.पढ़ो
		 * because we करो not want to take the synchronization
		 * semaphores twice here.
		 */

		क्रम (i = 0; i < NVM_CHECKSUM_REG; i++) अणु
			ret_val = igb_पढ़ो_nvm_eerd(hw, i, 1, &nvm_data);
			अगर (ret_val) अणु
				hw->nvm.ops.release(hw);
				hw_dbg("NVM Read Error while updating checksum.\n");
				जाओ out;
			पूर्ण
			checksum += nvm_data;
		पूर्ण
		checksum = (u16) NVM_SUM - checksum;
		ret_val = igb_ग_लिखो_nvm_srwr(hw, NVM_CHECKSUM_REG, 1,
						&checksum);
		अगर (ret_val) अणु
			hw->nvm.ops.release(hw);
			hw_dbg("NVM Write Error while updating checksum.\n");
			जाओ out;
		पूर्ण

		hw->nvm.ops.release(hw);

		ret_val = igb_update_flash_i210(hw);
	पूर्ण अन्यथा अणु
		ret_val = -E1000_ERR_SWFW_SYNC;
	पूर्ण
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_pool_flash_update_करोne_i210 - Pool FLUDONE status.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 **/
अटल s32 igb_pool_flash_update_करोne_i210(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = -E1000_ERR_NVM;
	u32 i, reg;

	क्रम (i = 0; i < E1000_FLUDONE_ATTEMPTS; i++) अणु
		reg = rd32(E1000_EECD);
		अगर (reg & E1000_EECD_FLUDONE_I210) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_get_flash_presence_i210 - Check अगर flash device is detected.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 **/
bool igb_get_flash_presence_i210(काष्ठा e1000_hw *hw)
अणु
	u32 eec = 0;
	bool ret_val = false;

	eec = rd32(E1000_EECD);
	अगर (eec & E1000_EECD_FLASH_DETECTED_I210)
		ret_val = true;

	वापस ret_val;
पूर्ण

/**
 *  igb_update_flash_i210 - Commit EEPROM to the flash
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 **/
अटल s32 igb_update_flash_i210(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u32 flup;

	ret_val = igb_pool_flash_update_करोne_i210(hw);
	अगर (ret_val == -E1000_ERR_NVM) अणु
		hw_dbg("Flash update time out\n");
		जाओ out;
	पूर्ण

	flup = rd32(E1000_EECD) | E1000_EECD_FLUPD_I210;
	wr32(E1000_EECD, flup);

	ret_val = igb_pool_flash_update_करोne_i210(hw);
	अगर (ret_val)
		hw_dbg("Flash update time out\n");
	अन्यथा
		hw_dbg("Flash update complete\n");

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_valid_led_शेष_i210 - Verअगरy a valid शेष LED config
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: poपूर्णांकer to the NVM (EEPROM)
 *
 *  Read the EEPROM क्रम the current शेष LED configuration.  If the
 *  LED configuration is not valid, set to a valid LED configuration.
 **/
s32 igb_valid_led_शेष_i210(काष्ठा e1000_hw *hw, u16 *data)
अणु
	s32 ret_val;

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_ID_LED_SETTINGS, 1, data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF) अणु
		चयन (hw->phy.media_type) अणु
		हाल e1000_media_type_पूर्णांकernal_serdes:
			*data = ID_LED_DEFAULT_I210_SERDES;
			अवरोध;
		हाल e1000_media_type_copper:
		शेष:
			*data = ID_LED_DEFAULT_I210;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस ret_val;
पूर्ण

/**
 *  __igb_access_xmdio_reg - Read/ग_लिखो XMDIO रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @address: XMDIO address to program
 *  @dev_addr: device address to program
 *  @data: poपूर्णांकer to value to पढ़ो/ग_लिखो from/to the XMDIO address
 *  @पढ़ो: boolean flag to indicate पढ़ो or ग_लिखो
 **/
अटल s32 __igb_access_xmdio_reg(काष्ठा e1000_hw *hw, u16 address,
				  u8 dev_addr, u16 *data, bool पढ़ो)
अणु
	s32 ret_val = 0;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_MMDAC, dev_addr);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_MMDAAD, address);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_MMDAC, E1000_MMDAC_FUNC_DATA |
							 dev_addr);
	अगर (ret_val)
		वापस ret_val;

	अगर (पढ़ो)
		ret_val = hw->phy.ops.पढ़ो_reg(hw, E1000_MMDAAD, data);
	अन्यथा
		ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_MMDAAD, *data);
	अगर (ret_val)
		वापस ret_val;

	/* Recalibrate the device back to 0 */
	ret_val = hw->phy.ops.ग_लिखो_reg(hw, E1000_MMDAC, 0);
	अगर (ret_val)
		वापस ret_val;

	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_xmdio_reg - Read XMDIO रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: XMDIO address to program
 *  @dev_addr: device address to program
 *  @data: value to be पढ़ो from the EMI address
 **/
s32 igb_पढ़ो_xmdio_reg(काष्ठा e1000_hw *hw, u16 addr, u8 dev_addr, u16 *data)
अणु
	वापस __igb_access_xmdio_reg(hw, addr, dev_addr, data, true);
पूर्ण

/**
 *  igb_ग_लिखो_xmdio_reg - Write XMDIO रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @addr: XMDIO address to program
 *  @dev_addr: device address to program
 *  @data: value to be written to the XMDIO address
 **/
s32 igb_ग_लिखो_xmdio_reg(काष्ठा e1000_hw *hw, u16 addr, u8 dev_addr, u16 data)
अणु
	वापस __igb_access_xmdio_reg(hw, addr, dev_addr, &data, false);
पूर्ण

/**
 *  igb_init_nvm_params_i210 - Init NVM func ptrs.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 **/
s32 igb_init_nvm_params_i210(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquire = igb_acquire_nvm_i210;
	nvm->ops.release = igb_release_nvm_i210;
	nvm->ops.valid_led_शेष = igb_valid_led_शेष_i210;

	/* NVM Function Poपूर्णांकers */
	अगर (igb_get_flash_presence_i210(hw)) अणु
		hw->nvm.type = e1000_nvm_flash_hw;
		nvm->ops.पढ़ो    = igb_पढ़ो_nvm_srrd_i210;
		nvm->ops.ग_लिखो   = igb_ग_लिखो_nvm_srwr_i210;
		nvm->ops.validate = igb_validate_nvm_checksum_i210;
		nvm->ops.update   = igb_update_nvm_checksum_i210;
	पूर्ण अन्यथा अणु
		hw->nvm.type = e1000_nvm_invm;
		nvm->ops.पढ़ो     = igb_पढ़ो_invm_i210;
		nvm->ops.ग_लिखो    = शून्य;
		nvm->ops.validate = शून्य;
		nvm->ops.update   = शून्य;
	पूर्ण
	वापस ret_val;
पूर्ण

/**
 * igb_pll_workaround_i210
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Works around an errata in the PLL circuit where it occasionally
 * provides the wrong घड़ी frequency after घातer up.
 **/
s32 igb_pll_workaround_i210(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u32 wuc, mdicnfg, ctrl, ctrl_ext, reg_val;
	u16 nvm_word, phy_word, pci_word, पंचांगp_nvm;
	पूर्णांक i;

	/* Get and set needed रेजिस्टर values */
	wuc = rd32(E1000_WUC);
	mdicnfg = rd32(E1000_MDICNFG);
	reg_val = mdicnfg & ~E1000_MDICNFG_EXT_MDIO;
	wr32(E1000_MDICNFG, reg_val);

	/* Get data from NVM, or set शेष */
	ret_val = igb_पढ़ो_invm_word_i210(hw, E1000_INVM_AUTOLOAD,
					  &nvm_word);
	अगर (ret_val)
		nvm_word = E1000_INVM_DEFAULT_AL;
	पंचांगp_nvm = nvm_word | E1000_INVM_PLL_WO_VAL;
	igb_ग_लिखो_phy_reg_82580(hw, I347AT4_PAGE_SELECT, E1000_PHY_PLL_FREQ_PAGE);
	phy_word = E1000_PHY_PLL_UNCONF;
	क्रम (i = 0; i < E1000_MAX_PLL_TRIES; i++) अणु
		/* check current state directly from पूर्णांकernal PHY */
		igb_पढ़ो_phy_reg_82580(hw, E1000_PHY_PLL_FREQ_REG, &phy_word);
		अगर ((phy_word & E1000_PHY_PLL_UNCONF)
		    != E1000_PHY_PLL_UNCONF) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण अन्यथा अणु
			ret_val = -E1000_ERR_PHY;
		पूर्ण
		/* directly reset the पूर्णांकernal PHY */
		ctrl = rd32(E1000_CTRL);
		wr32(E1000_CTRL, ctrl|E1000_CTRL_PHY_RST);

		ctrl_ext = rd32(E1000_CTRL_EXT);
		ctrl_ext |= (E1000_CTRL_EXT_PHYPDEN | E1000_CTRL_EXT_SDLPE);
		wr32(E1000_CTRL_EXT, ctrl_ext);

		wr32(E1000_WUC, 0);
		reg_val = (E1000_INVM_AUTOLOAD << 4) | (पंचांगp_nvm << 16);
		wr32(E1000_EEARBC_I210, reg_val);

		igb_पढ़ो_pci_cfg(hw, E1000_PCI_PMCSR, &pci_word);
		pci_word |= E1000_PCI_PMCSR_D3;
		igb_ग_लिखो_pci_cfg(hw, E1000_PCI_PMCSR, &pci_word);
		usleep_range(1000, 2000);
		pci_word &= ~E1000_PCI_PMCSR_D3;
		igb_ग_लिखो_pci_cfg(hw, E1000_PCI_PMCSR, &pci_word);
		reg_val = (E1000_INVM_AUTOLOAD << 4) | (nvm_word << 16);
		wr32(E1000_EEARBC_I210, reg_val);

		/* restore WUC रेजिस्टर */
		wr32(E1000_WUC, wuc);
	पूर्ण
	igb_ग_लिखो_phy_reg_82580(hw, I347AT4_PAGE_SELECT, 0);
	/* restore MDICNFG setting */
	wr32(E1000_MDICNFG, mdicnfg);
	वापस ret_val;
पूर्ण

/**
 *  igb_get_cfg_करोne_i210 - Read config करोne bit
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the management control रेजिस्टर क्रम the config करोne bit क्रम
 *  completion status.  NOTE: silicon which is EEPROM-less will fail trying
 *  to पढ़ो the config करोne bit, so an error is *ONLY* logged and वापसs
 *  0.  If we were to वापस with error, EEPROM-less silicon
 *  would not be able to be reset or change link.
 **/
s32 igb_get_cfg_करोne_i210(काष्ठा e1000_hw *hw)
अणु
	s32 समयout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_PORT_0;

	जबतक (समयout) अणु
		अगर (rd32(E1000_EEMNGCTL_I210) & mask)
			अवरोध;
		usleep_range(1000, 2000);
		समयout--;
	पूर्ण
	अगर (!समयout)
		hw_dbg("MNG configuration cycle has not completed.\n");

	वापस 0;
पूर्ण

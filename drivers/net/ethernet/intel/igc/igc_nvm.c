<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश "igc_mac.h"
#समावेश "igc_nvm.h"

/**
 * igc_poll_eerd_eewr_करोne - Poll क्रम EEPROM पढ़ो/ग_लिखो completion
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @ee_reg: EEPROM flag क्रम polling
 *
 * Polls the EEPROM status bit क्रम either पढ़ो or ग_लिखो completion based
 * upon the value of 'ee_reg'.
 */
अटल s32 igc_poll_eerd_eewr_करोne(काष्ठा igc_hw *hw, पूर्णांक ee_reg)
अणु
	s32 ret_val = -IGC_ERR_NVM;
	u32 attempts = 100000;
	u32 i, reg = 0;

	क्रम (i = 0; i < attempts; i++) अणु
		अगर (ee_reg == IGC_NVM_POLL_READ)
			reg = rd32(IGC_EERD);
		अन्यथा
			reg = rd32(IGC_EEWR);

		अगर (reg & IGC_NVM_RW_REG_DONE) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण

		udelay(5);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_acquire_nvm - Generic request क्रम access to EEPROM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 * Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 * EEPROM access and वापस -IGC_ERR_NVM (-1).
 */
s32 igc_acquire_nvm(काष्ठा igc_hw *hw)
अणु
	s32 समयout = IGC_NVM_GRANT_ATTEMPTS;
	u32 eecd = rd32(IGC_EECD);
	s32 ret_val = 0;

	wr32(IGC_EECD, eecd | IGC_EECD_REQ);
	eecd = rd32(IGC_EECD);

	जबतक (समयout) अणु
		अगर (eecd & IGC_EECD_GNT)
			अवरोध;
		udelay(5);
		eecd = rd32(IGC_EECD);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		eecd &= ~IGC_EECD_REQ;
		wr32(IGC_EECD, eecd);
		hw_dbg("Could not acquire NVM grant\n");
		ret_val = -IGC_ERR_NVM;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * igc_release_nvm - Release exclusive access to EEPROM
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Stop any current commands to the EEPROM and clear the EEPROM request bit.
 */
व्योम igc_release_nvm(काष्ठा igc_hw *hw)
अणु
	u32 eecd;

	eecd = rd32(IGC_EECD);
	eecd &= ~IGC_EECD_REQ;
	wr32(IGC_EECD, eecd);
पूर्ण

/**
 * igc_पढ़ो_nvm_eerd - Reads EEPROM using EERD रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of word in the EEPROM to पढ़ो
 * @words: number of words to पढ़ो
 * @data: word पढ़ो from the EEPROM
 *
 * Reads a 16 bit word from the EEPROM using the EERD रेजिस्टर.
 */
s32 igc_पढ़ो_nvm_eerd(काष्ठा igc_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा igc_nvm_info *nvm = &hw->nvm;
	u32 i, eerd = 0;
	s32 ret_val = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर (offset >= nvm->word_size || (words > (nvm->word_size - offset)) ||
	    words == 0) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -IGC_ERR_NVM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		eerd = ((offset + i) << IGC_NVM_RW_ADDR_SHIFT) +
			IGC_NVM_RW_REG_START;

		wr32(IGC_EERD, eerd);
		ret_val = igc_poll_eerd_eewr_करोne(hw, IGC_NVM_POLL_READ);
		अगर (ret_val)
			अवरोध;

		data[i] = (rd32(IGC_EERD) >> IGC_NVM_RW_REG_DATA);
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_पढ़ो_mac_addr - Read device MAC address
 * @hw: poपूर्णांकer to the HW काष्ठाure
 */
s32 igc_पढ़ो_mac_addr(काष्ठा igc_hw *hw)
अणु
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = rd32(IGC_RAH(0));
	rar_low = rd32(IGC_RAL(0));

	क्रम (i = 0; i < IGC_RAL_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i] = (u8)(rar_low >> (i * 8));

	क्रम (i = 0; i < IGC_RAH_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i + 4] = (u8)(rar_high >> (i * 8));

	क्रम (i = 0; i < ETH_ALEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	वापस 0;
पूर्ण

/**
 * igc_validate_nvm_checksum - Validate EEPROM checksum
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 * and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 */
s32 igc_validate_nvm_checksum(काष्ठा igc_hw *hw)
अणु
	u16 checksum = 0;
	u16 i, nvm_data;
	s32 ret_val = 0;

	क्रम (i = 0; i < (NVM_CHECKSUM_REG + 1); i++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण

	अगर (checksum != (u16)NVM_SUM) अणु
		hw_dbg("NVM Checksum Invalid\n");
		ret_val = -IGC_ERR_NVM;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 * igc_update_nvm_checksum - Update EEPROM checksum
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 * up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 * value to the EEPROM.
 */
s32 igc_update_nvm_checksum(काष्ठा igc_hw *hw)
अणु
	u16 checksum = 0;
	u16 i, nvm_data;
	s32  ret_val;

	क्रम (i = 0; i < NVM_CHECKSUM_REG; i++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error while updating checksum.\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण
	checksum = (u16)NVM_SUM - checksum;
	ret_val = hw->nvm.ops.ग_लिखो(hw, NVM_CHECKSUM_REG, 1, &checksum);
	अगर (ret_val)
		hw_dbg("NVM Write Error while updating checksum.\n");

out:
	वापस ret_val;
पूर्ण

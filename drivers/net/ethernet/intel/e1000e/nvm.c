<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "e1000.h"

/**
 *  e1000_उठाओ_eec_clk - Raise EEPROM घड़ी
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @eecd: poपूर्णांकer to the EEPROM
 *
 *  Enable/Raise the EEPROM घड़ी bit.
 **/
अटल व्योम e1000_उठाओ_eec_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	*eecd = *eecd | E1000_EECD_SK;
	ew32(EECD, *eecd);
	e1e_flush();
	udelay(hw->nvm.delay_usec);
पूर्ण

/**
 *  e1000_lower_eec_clk - Lower EEPROM घड़ी
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @eecd: poपूर्णांकer to the EEPROM
 *
 *  Clear/Lower the EEPROM घड़ी bit.
 **/
अटल व्योम e1000_lower_eec_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	*eecd = *eecd & ~E1000_EECD_SK;
	ew32(EECD, *eecd);
	e1e_flush();
	udelay(hw->nvm.delay_usec);
पूर्ण

/**
 *  e1000_shअगरt_out_eec_bits - Shअगरt data bits our to the EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: data to send to the EEPROM
 *  @count: number of bits to shअगरt out
 *
 *  We need to shअगरt 'count' bits out to the EEPROM.  So, the value in the
 *  "data" parameter will be shअगरted out to the EEPROM one bit at a समय.
 *  In order to करो this, "data" must be broken करोwn पूर्णांकo bits.
 **/
अटल व्योम e1000_shअगरt_out_eec_bits(काष्ठा e1000_hw *hw, u16 data, u16 count)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);
	u32 mask;

	mask = BIT(count - 1);
	अगर (nvm->type == e1000_nvm_eeprom_spi)
		eecd |= E1000_EECD_DO;

	करो अणु
		eecd &= ~E1000_EECD_DI;

		अगर (data & mask)
			eecd |= E1000_EECD_DI;

		ew32(EECD, eecd);
		e1e_flush();

		udelay(nvm->delay_usec);

		e1000_उठाओ_eec_clk(hw, &eecd);
		e1000_lower_eec_clk(hw, &eecd);

		mask >>= 1;
	पूर्ण जबतक (mask);

	eecd &= ~E1000_EECD_DI;
	ew32(EECD, eecd);
पूर्ण

/**
 *  e1000_shअगरt_in_eec_bits - Shअगरt data bits in from the EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @count: number of bits to shअगरt in
 *
 *  In order to पढ़ो a रेजिस्टर from the EEPROM, we need to shअगरt 'count' bits
 *  in from the EEPROM.  Bits are "shifted in" by raising the घड़ी input to
 *  the EEPROM (setting the SK bit), and then पढ़ोing the value of the data out
 *  "DO" bit.  During this "shifting in" process the data in "DI" bit should
 *  always be clear.
 **/
अटल u16 e1000_shअगरt_in_eec_bits(काष्ठा e1000_hw *hw, u16 count)
अणु
	u32 eecd;
	u32 i;
	u16 data;

	eecd = er32(EECD);
	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	क्रम (i = 0; i < count; i++) अणु
		data <<= 1;
		e1000_उठाओ_eec_clk(hw, &eecd);

		eecd = er32(EECD);

		eecd &= ~E1000_EECD_DI;
		अगर (eecd & E1000_EECD_DO)
			data |= 1;

		e1000_lower_eec_clk(hw, &eecd);
	पूर्ण

	वापस data;
पूर्ण

/**
 *  e1000e_poll_eerd_eewr_करोne - Poll क्रम EEPROM पढ़ो/ग_लिखो completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @ee_reg: EEPROM flag क्रम polling
 *
 *  Polls the EEPROM status bit क्रम either पढ़ो or ग_लिखो completion based
 *  upon the value of 'ee_reg'.
 **/
s32 e1000e_poll_eerd_eewr_करोne(काष्ठा e1000_hw *hw, पूर्णांक ee_reg)
अणु
	u32 attempts = 100000;
	u32 i, reg = 0;

	क्रम (i = 0; i < attempts; i++) अणु
		अगर (ee_reg == E1000_NVM_POLL_READ)
			reg = er32(EERD);
		अन्यथा
			reg = er32(EEWR);

		अगर (reg & E1000_NVM_RW_REG_DONE)
			वापस 0;

		udelay(5);
	पूर्ण

	वापस -E1000_ERR_NVM;
पूर्ण

/**
 *  e1000e_acquire_nvm - Generic request क्रम access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 *  Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 *  EEPROM access and वापस -E1000_ERR_NVM (-1).
 **/
s32 e1000e_acquire_nvm(काष्ठा e1000_hw *hw)
अणु
	u32 eecd = er32(EECD);
	s32 समयout = E1000_NVM_GRANT_ATTEMPTS;

	ew32(EECD, eecd | E1000_EECD_REQ);
	eecd = er32(EECD);

	जबतक (समयout) अणु
		अगर (eecd & E1000_EECD_GNT)
			अवरोध;
		udelay(5);
		eecd = er32(EECD);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		eecd &= ~E1000_EECD_REQ;
		ew32(EECD, eecd);
		e_dbg("Could not acquire NVM grant\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_standby_nvm - Return EEPROM to standby state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Return the EEPROM to a standby state.
 **/
अटल व्योम e1000_standby_nvm(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);

	अगर (nvm->type == e1000_nvm_eeprom_spi) अणु
		/* Toggle CS to flush commands */
		eecd |= E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_flush();
		udelay(nvm->delay_usec);
		eecd &= ~E1000_EECD_CS;
		ew32(EECD, eecd);
		e1e_flush();
		udelay(nvm->delay_usec);
	पूर्ण
पूर्ण

/**
 *  e1000_stop_nvm - Terminate EEPROM command
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Terminates the current command by inverting the EEPROM's chip select pin.
 **/
अटल व्योम e1000_stop_nvm(काष्ठा e1000_hw *hw)
अणु
	u32 eecd;

	eecd = er32(EECD);
	अगर (hw->nvm.type == e1000_nvm_eeprom_spi) अणु
		/* Pull CS high */
		eecd |= E1000_EECD_CS;
		e1000_lower_eec_clk(hw, &eecd);
	पूर्ण
पूर्ण

/**
 *  e1000e_release_nvm - Release exclusive access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Stop any current commands to the EEPROM and clear the EEPROM request bit.
 **/
व्योम e1000e_release_nvm(काष्ठा e1000_hw *hw)
अणु
	u32 eecd;

	e1000_stop_nvm(hw);

	eecd = er32(EECD);
	eecd &= ~E1000_EECD_REQ;
	ew32(EECD, eecd);
पूर्ण

/**
 *  e1000_पढ़ोy_nvm_eeprom - Prepares EEPROM क्रम पढ़ो/ग_लिखो
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Setups the EEPROM क्रम पढ़ोing and writing.
 **/
अटल s32 e1000_पढ़ोy_nvm_eeprom(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);
	u8 spi_stat_reg;

	अगर (nvm->type == e1000_nvm_eeprom_spi) अणु
		u16 समयout = NVM_MAX_RETRY_SPI;

		/* Clear SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		ew32(EECD, eecd);
		e1e_flush();
		udelay(1);

		/* Read "Status Register" repeatedly until the LSB is cleared.
		 * The EEPROM will संकेत that the command has been completed
		 * by clearing bit 0 of the पूर्णांकernal status रेजिस्टर.  If it's
		 * not cleared within 'timeout', then error out.
		 */
		जबतक (समयout) अणु
			e1000_shअगरt_out_eec_bits(hw, NVM_RDSR_OPCODE_SPI,
						 hw->nvm.opcode_bits);
			spi_stat_reg = (u8)e1000_shअगरt_in_eec_bits(hw, 8);
			अगर (!(spi_stat_reg & NVM_STATUS_RDY_SPI))
				अवरोध;

			udelay(5);
			e1000_standby_nvm(hw);
			समयout--;
		पूर्ण

		अगर (!समयout) अणु
			e_dbg("SPI NVM Status error\n");
			वापस -E1000_ERR_NVM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_पढ़ो_nvm_eerd - Reads EEPROM using EERD रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of word in the EEPROM to पढ़ो
 *  @words: number of words to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM using the EERD रेजिस्टर.
 **/
s32 e1000e_पढ़ो_nvm_eerd(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eerd = 0;
	s32 ret_val = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * too many words क्रम the offset, and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		eerd = ((offset + i) << E1000_NVM_RW_ADDR_SHIFT) +
		    E1000_NVM_RW_REG_START;

		ew32(EERD, eerd);
		ret_val = e1000e_poll_eerd_eewr_करोne(hw, E1000_NVM_POLL_READ);
		अगर (ret_val) अणु
			e_dbg("NVM read error: %d\n", ret_val);
			अवरोध;
		पूर्ण

		data[i] = (er32(EERD) >> E1000_NVM_RW_REG_DATA);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_ग_लिखो_nvm_spi - Write to EEPROM using SPI
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the EEPROM
 *
 *  Writes data to EEPROM at offset using SPI पूर्णांकerface.
 *
 *  If e1000e_update_nvm_checksum is not called after this function , the
 *  EEPROM will most likely contain an invalid checksum.
 **/
s32 e1000e_ग_लिखो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	s32 ret_val = -E1000_ERR_NVM;
	u16 widx = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		e_dbg("nvm parameter(s) out of bounds\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	जबतक (widx < words) अणु
		u8 ग_लिखो_opcode = NVM_WRITE_OPCODE_SPI;

		ret_val = nvm->ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1000_पढ़ोy_nvm_eeprom(hw);
		अगर (ret_val) अणु
			nvm->ops.release(hw);
			वापस ret_val;
		पूर्ण

		e1000_standby_nvm(hw);

		/* Send the WRITE ENABLE command (8 bit opcode) */
		e1000_shअगरt_out_eec_bits(hw, NVM_WREN_OPCODE_SPI,
					 nvm->opcode_bits);

		e1000_standby_nvm(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		अगर ((nvm->address_bits == 8) && (offset >= 128))
			ग_लिखो_opcode |= NVM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		e1000_shअगरt_out_eec_bits(hw, ग_लिखो_opcode, nvm->opcode_bits);
		e1000_shअगरt_out_eec_bits(hw, (u16)((offset + widx) * 2),
					 nvm->address_bits);

		/* Loop to allow क्रम up to whole page ग_लिखो of eeprom */
		जबतक (widx < words) अणु
			u16 word_out = data[widx];

			word_out = (word_out >> 8) | (word_out << 8);
			e1000_shअगरt_out_eec_bits(hw, word_out, 16);
			widx++;

			अगर ((((offset + widx) * 2) % nvm->page_size) == 0) अणु
				e1000_standby_nvm(hw);
				अवरोध;
			पूर्ण
		पूर्ण
		usleep_range(10000, 11000);
		nvm->ops.release(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_pba_string_generic - Read device part number
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @pba_num: poपूर्णांकer to device part number
 *  @pba_num_size: size of part number buffer
 *
 *  Reads the product board assembly (PBA) number from the EEPROM and stores
 *  the value in pba_num.
 **/
s32 e1000_पढ़ो_pba_string_generic(काष्ठा e1000_hw *hw, u8 *pba_num,
				  u32 pba_num_size)
अणु
	s32 ret_val;
	u16 nvm_data;
	u16 pba_ptr;
	u16 offset;
	u16 length;

	अगर (pba_num == शून्य) अणु
		e_dbg("PBA string buffer was null\n");
		वापस -E1000_ERR_INVALID_ARGUMENT;
	पूर्ण

	ret_val = e1000_पढ़ो_nvm(hw, NVM_PBA_OFFSET_0, 1, &nvm_data);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	ret_val = e1000_पढ़ो_nvm(hw, NVM_PBA_OFFSET_1, 1, &pba_ptr);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	/* अगर nvm_data is not ptr guard the PBA must be in legacy क्रमmat which
	 * means pba_ptr is actually our second data word क्रम the PBA number
	 * and we can decode it पूर्णांकo an ascii string
	 */
	अगर (nvm_data != NVM_PBA_PTR_GUARD) अणु
		e_dbg("NVM PBA number is not stored as string\n");

		/* make sure callers buffer is big enough to store the PBA */
		अगर (pba_num_size < E1000_PBANUM_LENGTH) अणु
			e_dbg("PBA string buffer too small\n");
			वापस E1000_ERR_NO_SPACE;
		पूर्ण

		/* extract hex string from data and pba_ptr */
		pba_num[0] = (nvm_data >> 12) & 0xF;
		pba_num[1] = (nvm_data >> 8) & 0xF;
		pba_num[2] = (nvm_data >> 4) & 0xF;
		pba_num[3] = nvm_data & 0xF;
		pba_num[4] = (pba_ptr >> 12) & 0xF;
		pba_num[5] = (pba_ptr >> 8) & 0xF;
		pba_num[6] = '-';
		pba_num[7] = 0;
		pba_num[8] = (pba_ptr >> 4) & 0xF;
		pba_num[9] = pba_ptr & 0xF;

		/* put a null अक्षरacter on the end of our string */
		pba_num[10] = '\0';

		/* चयन all the data but the '-' to hex अक्षर */
		क्रम (offset = 0; offset < 10; offset++) अणु
			अगर (pba_num[offset] < 0xA)
				pba_num[offset] += '0';
			अन्यथा अगर (pba_num[offset] < 0x10)
				pba_num[offset] += 'A' - 0xA;
		पूर्ण

		वापस 0;
	पूर्ण

	ret_val = e1000_पढ़ो_nvm(hw, pba_ptr, 1, &length);
	अगर (ret_val) अणु
		e_dbg("NVM Read Error\n");
		वापस ret_val;
	पूर्ण

	अगर (length == 0xFFFF || length == 0) अणु
		e_dbg("NVM PBA number section invalid length\n");
		वापस -E1000_ERR_NVM_PBA_SECTION;
	पूर्ण
	/* check अगर pba_num buffer is big enough */
	अगर (pba_num_size < (((u32)length * 2) - 1)) अणु
		e_dbg("PBA string buffer too small\n");
		वापस -E1000_ERR_NO_SPACE;
	पूर्ण

	/* trim pba length from start of string */
	pba_ptr++;
	length--;

	क्रम (offset = 0; offset < length; offset++) अणु
		ret_val = e1000_पढ़ो_nvm(hw, pba_ptr + offset, 1, &nvm_data);
		अगर (ret_val) अणु
			e_dbg("NVM Read Error\n");
			वापस ret_val;
		पूर्ण
		pba_num[offset * 2] = (u8)(nvm_data >> 8);
		pba_num[(offset * 2) + 1] = (u8)(nvm_data & 0xFF);
	पूर्ण
	pba_num[offset * 2] = '\0';

	वापस 0;
पूर्ण

/**
 *  e1000_पढ़ो_mac_addr_generic - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the device MAC address from the EEPROM and stores the value.
 *  Since devices with two ports use the same EEPROM, we increment the
 *  last bit in the MAC address क्रम the second port.
 **/
s32 e1000_पढ़ो_mac_addr_generic(काष्ठा e1000_hw *hw)
अणु
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = er32(RAH(0));
	rar_low = er32(RAL(0));

	क्रम (i = 0; i < E1000_RAL_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i] = (u8)(rar_low >> (i * 8));

	क्रम (i = 0; i < E1000_RAH_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i + 4] = (u8)(rar_high >> (i * 8));

	क्रम (i = 0; i < ETH_ALEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	वापस 0;
पूर्ण

/**
 *  e1000e_validate_nvm_checksum_generic - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 **/
s32 e1000e_validate_nvm_checksum_generic(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = 0; i < (NVM_CHECKSUM_REG + 1); i++) अणु
		ret_val = e1000_पढ़ो_nvm(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			e_dbg("NVM Read Error\n");
			वापस ret_val;
		पूर्ण
		checksum += nvm_data;
	पूर्ण

	अगर (checksum != (u16)NVM_SUM) अणु
		e_dbg("NVM Checksum Invalid\n");
		वापस -E1000_ERR_NVM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_update_nvm_checksum_generic - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 *  value to the EEPROM.
 **/
s32 e1000e_update_nvm_checksum_generic(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = 0; i < NVM_CHECKSUM_REG; i++) अणु
		ret_val = e1000_पढ़ो_nvm(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			e_dbg("NVM Read Error while updating checksum.\n");
			वापस ret_val;
		पूर्ण
		checksum += nvm_data;
	पूर्ण
	checksum = (u16)NVM_SUM - checksum;
	ret_val = e1000_ग_लिखो_nvm(hw, NVM_CHECKSUM_REG, 1, &checksum);
	अगर (ret_val)
		e_dbg("NVM Write Error while updating checksum.\n");

	वापस ret_val;
पूर्ण

/**
 *  e1000e_reload_nvm_generic - Reloads EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reloads the EEPROM by setting the "Reinitialize from EEPROM" bit in the
 *  extended control रेजिस्टर.
 **/
व्योम e1000e_reload_nvm_generic(काष्ठा e1000_hw *hw)
अणु
	u32 ctrl_ext;

	usleep_range(10, 20);
	ctrl_ext = er32(CTRL_EXT);
	ctrl_ext |= E1000_CTRL_EXT_EE_RST;
	ew32(CTRL_EXT, ctrl_ext);
	e1e_flush();
पूर्ण

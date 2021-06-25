<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/delay.h>

#समावेश "e1000_mac.h"
#समावेश "e1000_nvm.h"

/**
 *  igb_उठाओ_eec_clk - Raise EEPROM घड़ी
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @eecd: poपूर्णांकer to the EEPROM
 *
 *  Enable/Raise the EEPROM घड़ी bit.
 **/
अटल व्योम igb_उठाओ_eec_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	*eecd = *eecd | E1000_EECD_SK;
	wr32(E1000_EECD, *eecd);
	wrfl();
	udelay(hw->nvm.delay_usec);
पूर्ण

/**
 *  igb_lower_eec_clk - Lower EEPROM घड़ी
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @eecd: poपूर्णांकer to the EEPROM
 *
 *  Clear/Lower the EEPROM घड़ी bit.
 **/
अटल व्योम igb_lower_eec_clk(काष्ठा e1000_hw *hw, u32 *eecd)
अणु
	*eecd = *eecd & ~E1000_EECD_SK;
	wr32(E1000_EECD, *eecd);
	wrfl();
	udelay(hw->nvm.delay_usec);
पूर्ण

/**
 *  igb_shअगरt_out_eec_bits - Shअगरt data bits our to the EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @data: data to send to the EEPROM
 *  @count: number of bits to shअगरt out
 *
 *  We need to shअगरt 'count' bits out to the EEPROM.  So, the value in the
 *  "data" parameter will be shअगरted out to the EEPROM one bit at a समय.
 *  In order to करो this, "data" must be broken करोwn पूर्णांकo bits.
 **/
अटल व्योम igb_shअगरt_out_eec_bits(काष्ठा e1000_hw *hw, u16 data, u16 count)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);
	u32 mask;

	mask = 1u << (count - 1);
	अगर (nvm->type == e1000_nvm_eeprom_spi)
		eecd |= E1000_EECD_DO;

	करो अणु
		eecd &= ~E1000_EECD_DI;

		अगर (data & mask)
			eecd |= E1000_EECD_DI;

		wr32(E1000_EECD, eecd);
		wrfl();

		udelay(nvm->delay_usec);

		igb_उठाओ_eec_clk(hw, &eecd);
		igb_lower_eec_clk(hw, &eecd);

		mask >>= 1;
	पूर्ण जबतक (mask);

	eecd &= ~E1000_EECD_DI;
	wr32(E1000_EECD, eecd);
पूर्ण

/**
 *  igb_shअगरt_in_eec_bits - Shअगरt data bits in from the EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @count: number of bits to shअगरt in
 *
 *  In order to पढ़ो a रेजिस्टर from the EEPROM, we need to shअगरt 'count' bits
 *  in from the EEPROM.  Bits are "shifted in" by raising the घड़ी input to
 *  the EEPROM (setting the SK bit), and then पढ़ोing the value of the data out
 *  "DO" bit.  During this "shifting in" process the data in "DI" bit should
 *  always be clear.
 **/
अटल u16 igb_shअगरt_in_eec_bits(काष्ठा e1000_hw *hw, u16 count)
अणु
	u32 eecd;
	u32 i;
	u16 data;

	eecd = rd32(E1000_EECD);

	eecd &= ~(E1000_EECD_DO | E1000_EECD_DI);
	data = 0;

	क्रम (i = 0; i < count; i++) अणु
		data <<= 1;
		igb_उठाओ_eec_clk(hw, &eecd);

		eecd = rd32(E1000_EECD);

		eecd &= ~E1000_EECD_DI;
		अगर (eecd & E1000_EECD_DO)
			data |= 1;

		igb_lower_eec_clk(hw, &eecd);
	पूर्ण

	वापस data;
पूर्ण

/**
 *  igb_poll_eerd_eewr_करोne - Poll क्रम EEPROM पढ़ो/ग_लिखो completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @ee_reg: EEPROM flag क्रम polling
 *
 *  Polls the EEPROM status bit क्रम either पढ़ो or ग_लिखो completion based
 *  upon the value of 'ee_reg'.
 **/
अटल s32 igb_poll_eerd_eewr_करोne(काष्ठा e1000_hw *hw, पूर्णांक ee_reg)
अणु
	u32 attempts = 100000;
	u32 i, reg = 0;
	s32 ret_val = -E1000_ERR_NVM;

	क्रम (i = 0; i < attempts; i++) अणु
		अगर (ee_reg == E1000_NVM_POLL_READ)
			reg = rd32(E1000_EERD);
		अन्यथा
			reg = rd32(E1000_EEWR);

		अगर (reg & E1000_NVM_RW_REG_DONE) अणु
			ret_val = 0;
			अवरोध;
		पूर्ण

		udelay(5);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_acquire_nvm - Generic request क्रम access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Set the EEPROM access request bit and रुको क्रम EEPROM access grant bit.
 *  Return successful अगर access grant bit set, अन्यथा clear the request क्रम
 *  EEPROM access and वापस -E1000_ERR_NVM (-1).
 **/
s32 igb_acquire_nvm(काष्ठा e1000_hw *hw)
अणु
	u32 eecd = rd32(E1000_EECD);
	s32 समयout = E1000_NVM_GRANT_ATTEMPTS;
	s32 ret_val = 0;


	wr32(E1000_EECD, eecd | E1000_EECD_REQ);
	eecd = rd32(E1000_EECD);

	जबतक (समयout) अणु
		अगर (eecd & E1000_EECD_GNT)
			अवरोध;
		udelay(5);
		eecd = rd32(E1000_EECD);
		समयout--;
	पूर्ण

	अगर (!समयout) अणु
		eecd &= ~E1000_EECD_REQ;
		wr32(E1000_EECD, eecd);
		hw_dbg("Could not acquire NVM grant\n");
		ret_val = -E1000_ERR_NVM;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_standby_nvm - Return EEPROM to standby state
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Return the EEPROM to a standby state.
 **/
अटल व्योम igb_standby_nvm(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);

	अगर (nvm->type == e1000_nvm_eeprom_spi) अणु
		/* Toggle CS to flush commands */
		eecd |= E1000_EECD_CS;
		wr32(E1000_EECD, eecd);
		wrfl();
		udelay(nvm->delay_usec);
		eecd &= ~E1000_EECD_CS;
		wr32(E1000_EECD, eecd);
		wrfl();
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

	eecd = rd32(E1000_EECD);
	अगर (hw->nvm.type == e1000_nvm_eeprom_spi) अणु
		/* Pull CS high */
		eecd |= E1000_EECD_CS;
		igb_lower_eec_clk(hw, &eecd);
	पूर्ण
पूर्ण

/**
 *  igb_release_nvm - Release exclusive access to EEPROM
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Stop any current commands to the EEPROM and clear the EEPROM request bit.
 **/
व्योम igb_release_nvm(काष्ठा e1000_hw *hw)
अणु
	u32 eecd;

	e1000_stop_nvm(hw);

	eecd = rd32(E1000_EECD);
	eecd &= ~E1000_EECD_REQ;
	wr32(E1000_EECD, eecd);
पूर्ण

/**
 *  igb_पढ़ोy_nvm_eeprom - Prepares EEPROM क्रम पढ़ो/ग_लिखो
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Setups the EEPROM क्रम पढ़ोing and writing.
 **/
अटल s32 igb_पढ़ोy_nvm_eeprom(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = rd32(E1000_EECD);
	s32 ret_val = 0;
	u16 समयout = 0;
	u8 spi_stat_reg;


	अगर (nvm->type == e1000_nvm_eeprom_spi) अणु
		/* Clear SK and CS */
		eecd &= ~(E1000_EECD_CS | E1000_EECD_SK);
		wr32(E1000_EECD, eecd);
		wrfl();
		udelay(1);
		समयout = NVM_MAX_RETRY_SPI;

		/* Read "Status Register" repeatedly until the LSB is cleared.
		 * The EEPROM will संकेत that the command has been completed
		 * by clearing bit 0 of the पूर्णांकernal status रेजिस्टर.  If it's
		 * not cleared within 'timeout', then error out.
		 */
		जबतक (समयout) अणु
			igb_shअगरt_out_eec_bits(hw, NVM_RDSR_OPCODE_SPI,
					       hw->nvm.opcode_bits);
			spi_stat_reg = (u8)igb_shअगरt_in_eec_bits(hw, 8);
			अगर (!(spi_stat_reg & NVM_STATUS_RDY_SPI))
				अवरोध;

			udelay(5);
			igb_standby_nvm(hw);
			समयout--;
		पूर्ण

		अगर (!समयout) अणु
			hw_dbg("SPI NVM Status error\n");
			ret_val = -E1000_ERR_NVM;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_nvm_spi - Read EEPROM's using SPI
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of word in the EEPROM to पढ़ो
 *  @words: number of words to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM.
 **/
s32 igb_पढ़ो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 i = 0;
	s32 ret_val;
	u16 word_in;
	u8 पढ़ो_opcode = NVM_READ_OPCODE_SPI;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	ret_val = nvm->ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_पढ़ोy_nvm_eeprom(hw);
	अगर (ret_val)
		जाओ release;

	igb_standby_nvm(hw);

	अगर ((nvm->address_bits == 8) && (offset >= 128))
		पढ़ो_opcode |= NVM_A8_OPCODE_SPI;

	/* Send the READ command (opcode + addr) */
	igb_shअगरt_out_eec_bits(hw, पढ़ो_opcode, nvm->opcode_bits);
	igb_shअगरt_out_eec_bits(hw, (u16)(offset*2), nvm->address_bits);

	/* Read the data.  SPI NVMs increment the address with each byte
	 * पढ़ो and will roll over अगर पढ़ोing beyond the end.  This allows
	 * us to पढ़ो the whole NVM from any offset
	 */
	क्रम (i = 0; i < words; i++) अणु
		word_in = igb_shअगरt_in_eec_bits(hw, 16);
		data[i] = (word_in >> 8) | (word_in << 8);
	पूर्ण

release:
	nvm->ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_nvm_eerd - Reads EEPROM using EERD रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset of word in the EEPROM to पढ़ो
 *  @words: number of words to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word from the EEPROM using the EERD रेजिस्टर.
 **/
s32 igb_पढ़ो_nvm_eerd(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eerd = 0;
	s32 ret_val = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		eerd = ((offset+i) << E1000_NVM_RW_ADDR_SHIFT) +
			E1000_NVM_RW_REG_START;

		wr32(E1000_EERD, eerd);
		ret_val = igb_poll_eerd_eewr_करोne(hw, E1000_NVM_POLL_READ);
		अगर (ret_val)
			अवरोध;

		data[i] = (rd32(E1000_EERD) >>
			E1000_NVM_RW_REG_DATA);
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_nvm_spi - Write to EEPROM using SPI
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: offset within the EEPROM to be written to
 *  @words: number of words to ग_लिखो
 *  @data: 16 bit word(s) to be written to the EEPROM
 *
 *  Writes data to EEPROM at offset using SPI पूर्णांकerface.
 *
 *  If e1000_update_nvm_checksum is not called after this function , the
 *  EEPROM will most likley contain an invalid checksum.
 **/
s32 igb_ग_लिखो_nvm_spi(काष्ठा e1000_hw *hw, u16 offset, u16 words, u16 *data)
अणु
	काष्ठा e1000_nvm_info *nvm = &hw->nvm;
	s32 ret_val = -E1000_ERR_NVM;
	u16 widx = 0;

	/* A check क्रम invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	अगर ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) अणु
		hw_dbg("nvm parameter(s) out of bounds\n");
		वापस ret_val;
	पूर्ण

	जबतक (widx < words) अणु
		u8 ग_लिखो_opcode = NVM_WRITE_OPCODE_SPI;

		ret_val = nvm->ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = igb_पढ़ोy_nvm_eeprom(hw);
		अगर (ret_val) अणु
			nvm->ops.release(hw);
			वापस ret_val;
		पूर्ण

		igb_standby_nvm(hw);

		/* Send the WRITE ENABLE command (8 bit opcode) */
		igb_shअगरt_out_eec_bits(hw, NVM_WREN_OPCODE_SPI,
					 nvm->opcode_bits);

		igb_standby_nvm(hw);

		/* Some SPI eeproms use the 8th address bit embedded in the
		 * opcode
		 */
		अगर ((nvm->address_bits == 8) && (offset >= 128))
			ग_लिखो_opcode |= NVM_A8_OPCODE_SPI;

		/* Send the Write command (8-bit opcode + addr) */
		igb_shअगरt_out_eec_bits(hw, ग_लिखो_opcode, nvm->opcode_bits);
		igb_shअगरt_out_eec_bits(hw, (u16)((offset + widx) * 2),
					 nvm->address_bits);

		/* Loop to allow क्रम up to whole page ग_लिखो of eeprom */
		जबतक (widx < words) अणु
			u16 word_out = data[widx];

			word_out = (word_out >> 8) | (word_out << 8);
			igb_shअगरt_out_eec_bits(hw, word_out, 16);
			widx++;

			अगर ((((offset + widx) * 2) % nvm->page_size) == 0) अणु
				igb_standby_nvm(hw);
				अवरोध;
			पूर्ण
		पूर्ण
		usleep_range(1000, 2000);
		nvm->ops.release(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_part_string - Read device part number
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @part_num: poपूर्णांकer to device part number
 *  @part_num_size: size of part number buffer
 *
 *  Reads the product board assembly (PBA) number from the EEPROM and stores
 *  the value in part_num.
 **/
s32 igb_पढ़ो_part_string(काष्ठा e1000_hw *hw, u8 *part_num, u32 part_num_size)
अणु
	s32 ret_val;
	u16 nvm_data;
	u16 poपूर्णांकer;
	u16 offset;
	u16 length;

	अगर (part_num == शून्य) अणु
		hw_dbg("PBA string buffer was null\n");
		ret_val = E1000_ERR_INVALID_ARGUMENT;
		जाओ out;
	पूर्ण

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_PBA_OFFSET_0, 1, &nvm_data);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	ret_val = hw->nvm.ops.पढ़ो(hw, NVM_PBA_OFFSET_1, 1, &poपूर्णांकer);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	/* अगर nvm_data is not ptr guard the PBA must be in legacy क्रमmat which
	 * means poपूर्णांकer is actually our second data word क्रम the PBA number
	 * and we can decode it पूर्णांकo an ascii string
	 */
	अगर (nvm_data != NVM_PBA_PTR_GUARD) अणु
		hw_dbg("NVM PBA number is not stored as string\n");

		/* we will need 11 अक्षरacters to store the PBA */
		अगर (part_num_size < 11) अणु
			hw_dbg("PBA string buffer too small\n");
			वापस E1000_ERR_NO_SPACE;
		पूर्ण

		/* extract hex string from data and poपूर्णांकer */
		part_num[0] = (nvm_data >> 12) & 0xF;
		part_num[1] = (nvm_data >> 8) & 0xF;
		part_num[2] = (nvm_data >> 4) & 0xF;
		part_num[3] = nvm_data & 0xF;
		part_num[4] = (poपूर्णांकer >> 12) & 0xF;
		part_num[5] = (poपूर्णांकer >> 8) & 0xF;
		part_num[6] = '-';
		part_num[7] = 0;
		part_num[8] = (poपूर्णांकer >> 4) & 0xF;
		part_num[9] = poपूर्णांकer & 0xF;

		/* put a null अक्षरacter on the end of our string */
		part_num[10] = '\0';

		/* चयन all the data but the '-' to hex अक्षर */
		क्रम (offset = 0; offset < 10; offset++) अणु
			अगर (part_num[offset] < 0xA)
				part_num[offset] += '0';
			अन्यथा अगर (part_num[offset] < 0x10)
				part_num[offset] += 'A' - 0xA;
		पूर्ण

		जाओ out;
	पूर्ण

	ret_val = hw->nvm.ops.पढ़ो(hw, poपूर्णांकer, 1, &length);
	अगर (ret_val) अणु
		hw_dbg("NVM Read Error\n");
		जाओ out;
	पूर्ण

	अगर (length == 0xFFFF || length == 0) अणु
		hw_dbg("NVM PBA number section invalid length\n");
		ret_val = E1000_ERR_NVM_PBA_SECTION;
		जाओ out;
	पूर्ण
	/* check अगर part_num buffer is big enough */
	अगर (part_num_size < (((u32)length * 2) - 1)) अणु
		hw_dbg("PBA string buffer too small\n");
		ret_val = E1000_ERR_NO_SPACE;
		जाओ out;
	पूर्ण

	/* trim pba length from start of string */
	poपूर्णांकer++;
	length--;

	क्रम (offset = 0; offset < length; offset++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, poपूर्णांकer + offset, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error\n");
			जाओ out;
		पूर्ण
		part_num[offset * 2] = (u8)(nvm_data >> 8);
		part_num[(offset * 2) + 1] = (u8)(nvm_data & 0xFF);
	पूर्ण
	part_num[offset * 2] = '\0';

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_mac_addr - Read device MAC address
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the device MAC address from the EEPROM and stores the value.
 *  Since devices with two ports use the same EEPROM, we increment the
 *  last bit in the MAC address क्रम the second port.
 **/
s32 igb_पढ़ो_mac_addr(काष्ठा e1000_hw *hw)
अणु
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = rd32(E1000_RAH(0));
	rar_low = rd32(E1000_RAL(0));

	क्रम (i = 0; i < E1000_RAL_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i] = (u8)(rar_low >> (i*8));

	क्रम (i = 0; i < E1000_RAH_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i+4] = (u8)(rar_high >> (i*8));

	क्रम (i = 0; i < ETH_ALEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	वापस 0;
पूर्ण

/**
 *  igb_validate_nvm_checksum - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calculates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  and then verअगरies that the sum of the EEPROM is equal to 0xBABA.
 **/
s32 igb_validate_nvm_checksum(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = 0; i < (NVM_CHECKSUM_REG + 1); i++) अणु
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
 *  igb_update_nvm_checksum - Update EEPROM checksum
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Updates the EEPROM checksum by पढ़ोing/adding each word of the EEPROM
 *  up to the checksum.  Then calculates the EEPROM checksum and ग_लिखोs the
 *  value to the EEPROM.
 **/
s32 igb_update_nvm_checksum(काष्ठा e1000_hw *hw)
अणु
	s32  ret_val;
	u16 checksum = 0;
	u16 i, nvm_data;

	क्रम (i = 0; i < NVM_CHECKSUM_REG; i++) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, i, 1, &nvm_data);
		अगर (ret_val) अणु
			hw_dbg("NVM Read Error while updating checksum.\n");
			जाओ out;
		पूर्ण
		checksum += nvm_data;
	पूर्ण
	checksum = (u16) NVM_SUM - checksum;
	ret_val = hw->nvm.ops.ग_लिखो(hw, NVM_CHECKSUM_REG, 1, &checksum);
	अगर (ret_val)
		hw_dbg("NVM Write Error while updating checksum.\n");

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_fw_version - Get firmware version inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @fw_vers: poपूर्णांकer to output काष्ठाure
 *
 *  unsupported MAC types will वापस all 0 version काष्ठाure
 **/
व्योम igb_get_fw_version(काष्ठा e1000_hw *hw, काष्ठा e1000_fw_version *fw_vers)
अणु
	u16 eeprom_verh, eeprom_verl, etrack_test, fw_version;
	u8 q, hval, rem, result;
	u16 comb_verh, comb_verl, comb_offset;

	स_रखो(fw_vers, 0, माप(काष्ठा e1000_fw_version));

	/* basic eeprom version numbers and bits used vary by part and by tool
	 * used to create the nvm images. Check which data क्रमmat we have.
	 */
	hw->nvm.ops.पढ़ो(hw, NVM_ETRACK_HIWORD, 1, &etrack_test);
	चयन (hw->mac.type) अणु
	हाल e1000_i211:
		igb_पढ़ो_invm_version(hw, fw_vers);
		वापस;
	हाल e1000_82575:
	हाल e1000_82576:
	हाल e1000_82580:
		/* Use this क्रमmat, unless EETRACK ID exists,
		 * then use alternate क्रमmat
		 */
		अगर ((etrack_test &  NVM_MAJOR_MASK) != NVM_ETRACK_VALID) अणु
			hw->nvm.ops.पढ़ो(hw, NVM_VERSION, 1, &fw_version);
			fw_vers->eep_major = (fw_version & NVM_MAJOR_MASK)
					      >> NVM_MAJOR_SHIFT;
			fw_vers->eep_minor = (fw_version & NVM_MINOR_MASK)
					      >> NVM_MINOR_SHIFT;
			fw_vers->eep_build = (fw_version & NVM_IMAGE_ID_MASK);
			जाओ etrack_id;
		पूर्ण
		अवरोध;
	हाल e1000_i210:
		अगर (!(igb_get_flash_presence_i210(hw))) अणु
			igb_पढ़ो_invm_version(hw, fw_vers);
			वापस;
		पूर्ण
		fallthrough;
	हाल e1000_i350:
		/* find combo image version */
		hw->nvm.ops.पढ़ो(hw, NVM_COMB_VER_PTR, 1, &comb_offset);
		अगर ((comb_offset != 0x0) &&
		    (comb_offset != NVM_VER_INVALID)) अणु

			hw->nvm.ops.पढ़ो(hw, (NVM_COMB_VER_OFF + comb_offset
					 + 1), 1, &comb_verh);
			hw->nvm.ops.पढ़ो(hw, (NVM_COMB_VER_OFF + comb_offset),
					 1, &comb_verl);

			/* get Option Rom version अगर it exists and is valid */
			अगर ((comb_verh && comb_verl) &&
			    ((comb_verh != NVM_VER_INVALID) &&
			     (comb_verl != NVM_VER_INVALID))) अणु

				fw_vers->or_valid = true;
				fw_vers->or_major =
					comb_verl >> NVM_COMB_VER_SHFT;
				fw_vers->or_build =
					(comb_verl << NVM_COMB_VER_SHFT)
					| (comb_verh >> NVM_COMB_VER_SHFT);
				fw_vers->or_patch =
					comb_verh & NVM_COMB_VER_MASK;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	hw->nvm.ops.पढ़ो(hw, NVM_VERSION, 1, &fw_version);
	fw_vers->eep_major = (fw_version & NVM_MAJOR_MASK)
			      >> NVM_MAJOR_SHIFT;

	/* check क्रम old style version क्रमmat in newer images*/
	अगर ((fw_version & NVM_NEW_DEC_MASK) == 0x0) अणु
		eeprom_verl = (fw_version & NVM_COMB_VER_MASK);
	पूर्ण अन्यथा अणु
		eeprom_verl = (fw_version & NVM_MINOR_MASK)
				>> NVM_MINOR_SHIFT;
	पूर्ण
	/* Convert minor value to hex beक्रमe assigning to output काष्ठा
	 * Val to be converted will not be higher than 99, per tool output
	 */
	q = eeprom_verl / NVM_HEX_CONV;
	hval = q * NVM_HEX_TENS;
	rem = eeprom_verl % NVM_HEX_CONV;
	result = hval + rem;
	fw_vers->eep_minor = result;

etrack_id:
	अगर ((etrack_test &  NVM_MAJOR_MASK) == NVM_ETRACK_VALID) अणु
		hw->nvm.ops.पढ़ो(hw, NVM_ETRACK_WORD, 1, &eeprom_verl);
		hw->nvm.ops.पढ़ो(hw, (NVM_ETRACK_WORD + 1), 1, &eeprom_verh);
		fw_vers->etrack_id = (eeprom_verh << NVM_ETRACK_SHIFT)
			| eeprom_verl;
	पूर्ण
पूर्ण

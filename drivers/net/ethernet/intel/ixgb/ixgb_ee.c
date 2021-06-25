<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ixgb_hw.h"
#समावेश "ixgb_ee.h"
/* Local prototypes */
अटल u16 ixgb_shअगरt_in_bits(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_shअगरt_out_bits(काष्ठा ixgb_hw *hw,
				u16 data,
				u16 count);
अटल व्योम ixgb_standby_eeprom(काष्ठा ixgb_hw *hw);

अटल bool ixgb_रुको_eeprom_command(काष्ठा ixgb_hw *hw);

अटल व्योम ixgb_cleanup_eeprom(काष्ठा ixgb_hw *hw);

/******************************************************************************
 * Raises the EEPROM's घड़ी input.
 *
 * hw - Struct containing variables accessed by shared code
 * eecd_reg - EECD's current value
 *****************************************************************************/
अटल व्योम
ixgb_उठाओ_घड़ी(काष्ठा ixgb_hw *hw,
		  u32 *eecd_reg)
अणु
	/* Raise the घड़ी input to the EEPROM (by setting the SK bit), and then
	 *  रुको 50 microseconds.
	 */
	*eecd_reg = *eecd_reg | IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, *eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);
पूर्ण

/******************************************************************************
 * Lowers the EEPROM's घड़ी input.
 *
 * hw - Struct containing variables accessed by shared code
 * eecd_reg - EECD's current value
 *****************************************************************************/
अटल व्योम
ixgb_lower_घड़ी(काष्ठा ixgb_hw *hw,
		  u32 *eecd_reg)
अणु
	/* Lower the घड़ी input to the EEPROM (by clearing the SK bit), and then
	 * रुको 50 microseconds.
	 */
	*eecd_reg = *eecd_reg & ~IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, *eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);
पूर्ण

/******************************************************************************
 * Shअगरt data bits out to the EEPROM.
 *
 * hw - Struct containing variables accessed by shared code
 * data - data to send to the EEPROM
 * count - number of bits to shअगरt out
 *****************************************************************************/
अटल व्योम
ixgb_shअगरt_out_bits(काष्ठा ixgb_hw *hw,
					 u16 data,
					 u16 count)
अणु
	u32 eecd_reg;
	u32 mask;

	/* We need to shअगरt "count" bits out to the EEPROM. So, value in the
	 * "data" parameter will be shअगरted out to the EEPROM one bit at a समय.
	 * In order to करो this, "data" must be broken करोwn पूर्णांकo bits.
	 */
	mask = 0x01 << (count - 1);
	eecd_reg = IXGB_READ_REG(hw, EECD);
	eecd_reg &= ~(IXGB_EECD_DO | IXGB_EECD_DI);
	करो अणु
		/* A "1" is shअगरted out to the EEPROM by setting bit "DI" to a "1",
		 * and then raising and then lowering the घड़ी (the SK bit controls
		 * the घड़ी input to the EEPROM).  A "0" is shअगरted out to the EEPROM
		 * by setting "DI" to "0" and then raising and then lowering the घड़ी.
		 */
		eecd_reg &= ~IXGB_EECD_DI;

		अगर (data & mask)
			eecd_reg |= IXGB_EECD_DI;

		IXGB_WRITE_REG(hw, EECD, eecd_reg);
		IXGB_WRITE_FLUSH(hw);

		udelay(50);

		ixgb_उठाओ_घड़ी(hw, &eecd_reg);
		ixgb_lower_घड़ी(hw, &eecd_reg);

		mask = mask >> 1;

	पूर्ण जबतक (mask);

	/* We leave the "DI" bit set to "0" when we leave this routine. */
	eecd_reg &= ~IXGB_EECD_DI;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
पूर्ण

/******************************************************************************
 * Shअगरt data bits in from the EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल u16
ixgb_shअगरt_in_bits(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;
	u32 i;
	u16 data;

	/* In order to पढ़ो a रेजिस्टर from the EEPROM, we need to shअगरt 16 bits
	 * in from the EEPROM. Bits are "shifted in" by raising the घड़ी input to
	 * the EEPROM (setting the SK bit), and then पढ़ोing the value of the "DO"
	 * bit.  During this "shifting in" process the "DI" bit should always be
	 * clear..
	 */

	eecd_reg = IXGB_READ_REG(hw, EECD);

	eecd_reg &= ~(IXGB_EECD_DO | IXGB_EECD_DI);
	data = 0;

	क्रम (i = 0; i < 16; i++) अणु
		data = data << 1;
		ixgb_उठाओ_घड़ी(hw, &eecd_reg);

		eecd_reg = IXGB_READ_REG(hw, EECD);

		eecd_reg &= ~(IXGB_EECD_DI);
		अगर (eecd_reg & IXGB_EECD_DO)
			data |= 1;

		ixgb_lower_घड़ी(hw, &eecd_reg);
	पूर्ण

	वापस data;
पूर्ण

/******************************************************************************
 * Prepares EEPROM क्रम access
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Lowers EEPROM घड़ी. Clears input pin. Sets the chip select pin. This
 * function should be called beक्रमe issuing a command to the EEPROM.
 *****************************************************************************/
अटल व्योम
ixgb_setup_eeprom(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;

	eecd_reg = IXGB_READ_REG(hw, EECD);

	/*  Clear SK and DI  */
	eecd_reg &= ~(IXGB_EECD_SK | IXGB_EECD_DI);
	IXGB_WRITE_REG(hw, EECD, eecd_reg);

	/*  Set CS  */
	eecd_reg |= IXGB_EECD_CS;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
पूर्ण

/******************************************************************************
 * Returns EEPROM to a "standby" state
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_standby_eeprom(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;

	eecd_reg = IXGB_READ_REG(hw, EECD);

	/*  Deselect EEPROM  */
	eecd_reg &= ~(IXGB_EECD_CS | IXGB_EECD_SK);
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Clock high  */
	eecd_reg |= IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Select EEPROM  */
	eecd_reg |= IXGB_EECD_CS;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Clock low  */
	eecd_reg &= ~IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);
पूर्ण

/******************************************************************************
 * Raises then lowers the EEPROM's घड़ी pin
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_घड़ी_eeprom(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;

	eecd_reg = IXGB_READ_REG(hw, EECD);

	/*  Rising edge of घड़ी  */
	eecd_reg |= IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);

	/*  Falling edge of घड़ी  */
	eecd_reg &= ~IXGB_EECD_SK;
	IXGB_WRITE_REG(hw, EECD, eecd_reg);
	IXGB_WRITE_FLUSH(hw);
	udelay(50);
पूर्ण

/******************************************************************************
 * Terminates a command by lowering the EEPROM's chip select pin
 *
 * hw - Struct containing variables accessed by shared code
 *****************************************************************************/
अटल व्योम
ixgb_cleanup_eeprom(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;

	eecd_reg = IXGB_READ_REG(hw, EECD);

	eecd_reg &= ~(IXGB_EECD_CS | IXGB_EECD_DI);

	IXGB_WRITE_REG(hw, EECD, eecd_reg);

	ixgb_घड़ी_eeprom(hw);
पूर्ण

/******************************************************************************
 * Waits क्रम the EEPROM to finish the current command.
 *
 * hw - Struct containing variables accessed by shared code
 *
 * The command is करोne when the EEPROM's data out pin goes high.
 *
 * Returns:
 *      true: EEPROM data pin is high beक्रमe समयout.
 *      false:  Time expired.
 *****************************************************************************/
अटल bool
ixgb_रुको_eeprom_command(काष्ठा ixgb_hw *hw)
अणु
	u32 eecd_reg;
	u32 i;

	/* Toggle the CS line.  This in effect tells to EEPROM to actually execute
	 * the command in question.
	 */
	ixgb_standby_eeprom(hw);

	/* Now पढ़ो DO repeatedly until is high (equal to '1').  The EEPROM will
	 * संकेत that the command has been completed by raising the DO संकेत.
	 * If DO करोes not go high in 10 milliseconds, then error out.
	 */
	क्रम (i = 0; i < 200; i++) अणु
		eecd_reg = IXGB_READ_REG(hw, EECD);

		अगर (eecd_reg & IXGB_EECD_DO)
			वापस true;

		udelay(50);
	पूर्ण
	ASSERT(0);
	वापस false;
पूर्ण

/******************************************************************************
 * Verअगरies that the EEPROM has a valid checksum
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Reads the first 64 16 bit words of the EEPROM and sums the values पढ़ो.
 * If the sum of the 64 16 bit words is 0xBABA, the EEPROM's checksum is
 * valid.
 *
 * Returns:
 *  true: Checksum is valid
 *  false: Checksum is not valid.
 *****************************************************************************/
bool
ixgb_validate_eeprom_checksum(काष्ठा ixgb_hw *hw)
अणु
	u16 checksum = 0;
	u16 i;

	क्रम (i = 0; i < (EEPROM_CHECKSUM_REG + 1); i++)
		checksum += ixgb_पढ़ो_eeprom(hw, i);

	अगर (checksum == (u16) EEPROM_SUM)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/******************************************************************************
 * Calculates the EEPROM checksum and ग_लिखोs it to the EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Sums the first 63 16 bit words of the EEPROM. Subtracts the sum from 0xBABA.
 * Writes the dअगरference to word offset 63 of the EEPROM.
 *****************************************************************************/
व्योम
ixgb_update_eeprom_checksum(काष्ठा ixgb_hw *hw)
अणु
	u16 checksum = 0;
	u16 i;

	क्रम (i = 0; i < EEPROM_CHECKSUM_REG; i++)
		checksum += ixgb_पढ़ो_eeprom(hw, i);

	checksum = (u16) EEPROM_SUM - checksum;

	ixgb_ग_लिखो_eeprom(hw, EEPROM_CHECKSUM_REG, checksum);
पूर्ण

/******************************************************************************
 * Writes a 16 bit word to a given offset in the EEPROM.
 *
 * hw - Struct containing variables accessed by shared code
 * reg - offset within the EEPROM to be written to
 * data - 16 bit word to be written to the EEPROM
 *
 * If ixgb_update_eeprom_checksum is not called after this function, the
 * EEPROM will most likely contain an invalid checksum.
 *
 *****************************************************************************/
व्योम
ixgb_ग_लिखो_eeprom(काष्ठा ixgb_hw *hw, u16 offset, u16 data)
अणु
	काष्ठा ixgb_ee_map_type *ee_map = (काष्ठा ixgb_ee_map_type *)hw->eeprom;

	/* Prepare the EEPROM क्रम writing */
	ixgb_setup_eeprom(hw);

	/*  Send the 9-bit EWEN (ग_लिखो enable) command to the EEPROM (5-bit opcode
	 *  plus 4-bit dummy).  This माला_दो the EEPROM पूर्णांकo ग_लिखो/erase mode.
	 */
	ixgb_shअगरt_out_bits(hw, EEPROM_EWEN_OPCODE, 5);
	ixgb_shअगरt_out_bits(hw, 0, 4);

	/*  Prepare the EEPROM  */
	ixgb_standby_eeprom(hw);

	/*  Send the Write command (3-bit opcode + 6-bit addr)  */
	ixgb_shअगरt_out_bits(hw, EEPROM_WRITE_OPCODE, 3);
	ixgb_shअगरt_out_bits(hw, offset, 6);

	/*  Send the data  */
	ixgb_shअगरt_out_bits(hw, data, 16);

	ixgb_रुको_eeprom_command(hw);

	/*  Recover from ग_लिखो  */
	ixgb_standby_eeprom(hw);

	/* Send the 9-bit EWDS (ग_लिखो disable) command to the EEPROM (5-bit
	 * opcode plus 4-bit dummy).  This takes the EEPROM out of ग_लिखो/erase
	 * mode.
	 */
	ixgb_shअगरt_out_bits(hw, EEPROM_EWDS_OPCODE, 5);
	ixgb_shअगरt_out_bits(hw, 0, 4);

	/*  Done with writing  */
	ixgb_cleanup_eeprom(hw);

	/* clear the init_ctrl_reg_1 to signअगरy that the cache is invalidated */
	ee_map->init_ctrl_reg_1 = cpu_to_le16(EEPROM_ICW1_SIGNATURE_CLEAR);
पूर्ण

/******************************************************************************
 * Reads a 16 bit word from the EEPROM.
 *
 * hw - Struct containing variables accessed by shared code
 * offset - offset of 16 bit word in the EEPROM to पढ़ो
 *
 * Returns:
 *  The 16-bit value पढ़ो from the eeprom
 *****************************************************************************/
u16
ixgb_पढ़ो_eeprom(काष्ठा ixgb_hw *hw,
		  u16 offset)
अणु
	u16 data;

	/*  Prepare the EEPROM क्रम पढ़ोing  */
	ixgb_setup_eeprom(hw);

	/*  Send the READ command (opcode + addr)  */
	ixgb_shअगरt_out_bits(hw, EEPROM_READ_OPCODE, 3);
	/*
	 * We have a 64 word EEPROM, there are 6 address bits
	 */
	ixgb_shअगरt_out_bits(hw, offset, 6);

	/*  Read the data  */
	data = ixgb_shअगरt_in_bits(hw);

	/*  End this पढ़ो operation  */
	ixgb_standby_eeprom(hw);

	वापस data;
पूर्ण

/******************************************************************************
 * Reads eeprom and stores data in shared काष्ठाure.
 * Validates eeprom checksum and eeprom signature.
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Returns:
 *      true: अगर eeprom पढ़ो is successful
 *      false: otherwise.
 *****************************************************************************/
bool
ixgb_get_eeprom_data(काष्ठा ixgb_hw *hw)
अणु
	u16 i;
	u16 checksum = 0;
	काष्ठा ixgb_ee_map_type *ee_map;

	ENTER();

	ee_map = (काष्ठा ixgb_ee_map_type *)hw->eeprom;

	pr_debug("Reading eeprom data\n");
	क्रम (i = 0; i < IXGB_EEPROM_SIZE ; i++) अणु
		u16 ee_data;
		ee_data = ixgb_पढ़ो_eeprom(hw, i);
		checksum += ee_data;
		hw->eeprom[i] = cpu_to_le16(ee_data);
	पूर्ण

	अगर (checksum != (u16) EEPROM_SUM) अणु
		pr_debug("Checksum invalid\n");
		/* clear the init_ctrl_reg_1 to signअगरy that the cache is
		 * invalidated */
		ee_map->init_ctrl_reg_1 = cpu_to_le16(EEPROM_ICW1_SIGNATURE_CLEAR);
		वापस false;
	पूर्ण

	अगर ((ee_map->init_ctrl_reg_1 & cpu_to_le16(EEPROM_ICW1_SIGNATURE_MASK))
		 != cpu_to_le16(EEPROM_ICW1_SIGNATURE_VALID)) अणु
		pr_debug("Signature invalid\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/******************************************************************************
 * Local function to check अगर the eeprom signature is good
 * If the eeprom signature is good, calls ixgb)get_eeprom_data.
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Returns:
 *      true: eeprom signature was good and the eeprom पढ़ो was successful
 *      false: otherwise.
 ******************************************************************************/
अटल bool
ixgb_check_and_get_eeprom_data (काष्ठा ixgb_hw* hw)
अणु
	काष्ठा ixgb_ee_map_type *ee_map = (काष्ठा ixgb_ee_map_type *)hw->eeprom;

	अगर ((ee_map->init_ctrl_reg_1 & cpu_to_le16(EEPROM_ICW1_SIGNATURE_MASK))
	    == cpu_to_le16(EEPROM_ICW1_SIGNATURE_VALID)) अणु
		वापस true;
	पूर्ण अन्यथा अणु
		वापस ixgb_get_eeprom_data(hw);
	पूर्ण
पूर्ण

/******************************************************************************
 * वापस a word from the eeprom
 *
 * hw - Struct containing variables accessed by shared code
 * index - Offset of eeprom word
 *
 * Returns:
 *          Word at indexed offset in eeprom, अगर valid, 0 otherwise.
 ******************************************************************************/
__le16
ixgb_get_eeprom_word(काष्ठा ixgb_hw *hw, u16 index)
अणु

	अगर (index < IXGB_EEPROM_SIZE && ixgb_check_and_get_eeprom_data(hw))
		वापस hw->eeprom[index];

	वापस 0;
पूर्ण

/******************************************************************************
 * वापस the mac address from EEPROM
 *
 * hw       - Struct containing variables accessed by shared code
 * mac_addr - Ethernet Address अगर EEPROM contents are valid, 0 otherwise
 *
 * Returns: None.
 ******************************************************************************/
व्योम
ixgb_get_ee_mac_addr(काष्ठा ixgb_hw *hw,
			u8 *mac_addr)
अणु
	पूर्णांक i;
	काष्ठा ixgb_ee_map_type *ee_map = (काष्ठा ixgb_ee_map_type *)hw->eeprom;

	ENTER();

	अगर (ixgb_check_and_get_eeprom_data(hw)) अणु
		क्रम (i = 0; i < ETH_ALEN; i++) अणु
			mac_addr[i] = ee_map->mac_addr[i];
		पूर्ण
		pr_debug("eeprom mac address = %pM\n", mac_addr);
	पूर्ण
पूर्ण


/******************************************************************************
 * वापस the Prपूर्णांकed Board Assembly number from EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Returns:
 *          PBA number अगर EEPROM contents are valid, 0 otherwise
 ******************************************************************************/
u32
ixgb_get_ee_pba_number(काष्ठा ixgb_hw *hw)
अणु
	अगर (ixgb_check_and_get_eeprom_data(hw))
		वापस le16_to_cpu(hw->eeprom[EEPROM_PBA_1_2_REG])
			| (le16_to_cpu(hw->eeprom[EEPROM_PBA_3_4_REG])<<16);

	वापस 0;
पूर्ण


/******************************************************************************
 * वापस the Device Id from EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Returns:
 *          Device Id अगर EEPROM contents are valid, 0 otherwise
 ******************************************************************************/
u16
ixgb_get_ee_device_id(काष्ठा ixgb_hw *hw)
अणु
	काष्ठा ixgb_ee_map_type *ee_map = (काष्ठा ixgb_ee_map_type *)hw->eeprom;

	अगर (ixgb_check_and_get_eeprom_data(hw))
		वापस le16_to_cpu(ee_map->device_id);

	वापस 0;
पूर्ण


<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/delay.h>

#समावेश "e1000_mac.h"
#समावेश "e1000_phy.h"

अटल s32  igb_phy_setup_स्वतःneg(काष्ठा e1000_hw *hw);
अटल व्योम igb_phy_क्रमce_speed_duplex_setup(काष्ठा e1000_hw *hw,
					     u16 *phy_ctrl);
अटल s32  igb_रुको_स्वतःneg(काष्ठा e1000_hw *hw);
अटल s32  igb_set_master_slave_mode(काष्ठा e1000_hw *hw);

/* Cable length tables */
अटल स्थिर u16 e1000_m88_cable_length_table[] = अणु
	0, 50, 80, 110, 140, 140, E1000_CABLE_LENGTH_UNDEFINED पूर्ण;

अटल स्थिर u16 e1000_igp_2_cable_length_table[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 8, 11, 13, 16, 18, 21,
	0, 0, 0, 3, 6, 10, 13, 16, 19, 23, 26, 29, 32, 35, 38, 41,
	6, 10, 14, 18, 22, 26, 30, 33, 37, 41, 44, 48, 51, 54, 58, 61,
	21, 26, 31, 35, 40, 44, 49, 53, 57, 61, 65, 68, 72, 75, 79, 82,
	40, 45, 51, 56, 61, 66, 70, 75, 79, 83, 87, 91, 94, 98, 101, 104,
	60, 66, 72, 77, 82, 87, 92, 96, 100, 104, 108, 111, 114, 117, 119, 121,
	83, 89, 95, 100, 105, 109, 113, 116, 119, 122, 124,
	104, 109, 114, 118, 121, 124पूर्ण;

/**
 *  igb_check_reset_block - Check अगर PHY reset is blocked
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the PHY management control रेजिस्टर and check whether a PHY reset
 *  is blocked.  If a reset is not blocked वापस 0, otherwise
 *  वापस E1000_BLK_PHY_RESET (12).
 **/
s32 igb_check_reset_block(काष्ठा e1000_hw *hw)
अणु
	u32 manc;

	manc = rd32(E1000_MANC);

	वापस (manc & E1000_MANC_BLK_PHY_RST_ON_IDE) ? E1000_BLK_PHY_RESET : 0;
पूर्ण

/**
 *  igb_get_phy_id - Retrieve the PHY ID and revision
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the PHY रेजिस्टरs and stores the PHY ID and possibly the PHY
 *  revision in the hardware काष्ठाure.
 **/
s32 igb_get_phy_id(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_id;

	/* ensure PHY page selection to fix misconfigured i210 */
	अगर ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211))
		phy->ops.ग_लिखो_reg(hw, I347AT4_PAGE_SELECT, 0);

	ret_val = phy->ops.पढ़ो_reg(hw, PHY_ID1, &phy_id);
	अगर (ret_val)
		जाओ out;

	phy->id = (u32)(phy_id << 16);
	udelay(20);
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_ID2, &phy_id);
	अगर (ret_val)
		जाओ out;

	phy->id |= (u32)(phy_id & PHY_REVISION_MASK);
	phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_reset_dsp - Reset PHY DSP
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reset the digital संकेत processor.
 **/
अटल s32 igb_phy_reset_dsp(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;

	अगर (!(hw->phy.ops.ग_लिखो_reg))
		जाओ out;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, M88E1000_PHY_GEN_CONTROL, 0xC1);
	अगर (ret_val)
		जाओ out;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, M88E1000_PHY_GEN_CONTROL, 0);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_phy_reg_mdic - Read MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the MDI control रेजिस्टर in the PHY at offset and stores the
 *  inक्रमmation पढ़ो to data.
 **/
s32 igb_पढ़ो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		जाओ out;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = ((offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_READ));

	wr32(E1000_MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) अणु
		udelay(50);
		mdic = rd32(E1000_MDIC);
		अगर (mdic & E1000_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & E1000_MDIC_READY)) अणु
		hw_dbg("MDI Read did not complete\n");
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण
	अगर (mdic & E1000_MDIC_ERROR) अणु
		hw_dbg("MDI Error\n");
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण
	*data = (u16) mdic;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_phy_reg_mdic - Write MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो to रेजिस्टर at offset
 *
 *  Writes data to MDI control रेजिस्टर in the PHY at offset.
 **/
s32 igb_ग_लिखो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;
	s32 ret_val = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		hw_dbg("PHY Address %d is out of range\n", offset);
		ret_val = -E1000_ERR_PARAM;
		जाओ out;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = (((u32)data) |
		(offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_WRITE));

	wr32(E1000_MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) अणु
		udelay(50);
		mdic = rd32(E1000_MDIC);
		अगर (mdic & E1000_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & E1000_MDIC_READY)) अणु
		hw_dbg("MDI Write did not complete\n");
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण
	अगर (mdic & E1000_MDIC_ERROR) अणु
		hw_dbg("MDI Error\n");
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_पढ़ो_phy_reg_i2c - Read PHY रेजिस्टर using i2c
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the PHY रेजिस्टर at offset using the i2c पूर्णांकerface and stores the
 *  retrieved inक्रमmation in data.
 **/
s32 igb_पढ़ो_phy_reg_i2c(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, i2ccmd = 0;

	/* Set up Op-code, Phy Address, and रेजिस्टर address in the I2CCMD
	 * रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	i2ccmd = ((offset << E1000_I2CCMD_REG_ADDR_SHIFT) |
		  (phy->addr << E1000_I2CCMD_PHY_ADDR_SHIFT) |
		  (E1000_I2CCMD_OPCODE_READ));

	wr32(E1000_I2CCMD, i2ccmd);

	/* Poll the पढ़ोy bit to see अगर the I2C पढ़ो completed */
	क्रम (i = 0; i < E1000_I2CCMD_PHY_TIMEOUT; i++) अणु
		udelay(50);
		i2ccmd = rd32(E1000_I2CCMD);
		अगर (i2ccmd & E1000_I2CCMD_READY)
			अवरोध;
	पूर्ण
	अगर (!(i2ccmd & E1000_I2CCMD_READY)) अणु
		hw_dbg("I2CCMD Read did not complete\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (i2ccmd & E1000_I2CCMD_ERROR) अणु
		hw_dbg("I2CCMD Error bit set\n");
		वापस -E1000_ERR_PHY;
	पूर्ण

	/* Need to byte-swap the 16-bit value. */
	*data = ((i2ccmd >> 8) & 0x00FF) | ((i2ccmd << 8) & 0xFF00);

	वापस 0;
पूर्ण

/**
 *  igb_ग_लिखो_phy_reg_i2c - Write PHY रेजिस्टर using i2c
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes the data to PHY रेजिस्टर at the offset using the i2c पूर्णांकerface.
 **/
s32 igb_ग_लिखो_phy_reg_i2c(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, i2ccmd = 0;
	u16 phy_data_swapped;

	/* Prevent overwriting SFP I2C EEPROM which is at A0 address.*/
	अगर ((hw->phy.addr == 0) || (hw->phy.addr > 7)) अणु
		hw_dbg("PHY I2C Address %d is out of range.\n",
			  hw->phy.addr);
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	/* Swap the data bytes क्रम the I2C पूर्णांकerface */
	phy_data_swapped = ((data >> 8) & 0x00FF) | ((data << 8) & 0xFF00);

	/* Set up Op-code, Phy Address, and रेजिस्टर address in the I2CCMD
	 * रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	i2ccmd = ((offset << E1000_I2CCMD_REG_ADDR_SHIFT) |
		  (phy->addr << E1000_I2CCMD_PHY_ADDR_SHIFT) |
		  E1000_I2CCMD_OPCODE_WRITE |
		  phy_data_swapped);

	wr32(E1000_I2CCMD, i2ccmd);

	/* Poll the पढ़ोy bit to see अगर the I2C पढ़ो completed */
	क्रम (i = 0; i < E1000_I2CCMD_PHY_TIMEOUT; i++) अणु
		udelay(50);
		i2ccmd = rd32(E1000_I2CCMD);
		अगर (i2ccmd & E1000_I2CCMD_READY)
			अवरोध;
	पूर्ण
	अगर (!(i2ccmd & E1000_I2CCMD_READY)) अणु
		hw_dbg("I2CCMD Write did not complete\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (i2ccmd & E1000_I2CCMD_ERROR) अणु
		hw_dbg("I2CCMD Error bit set\n");
		वापस -E1000_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  igb_पढ़ो_sfp_data_byte - Reads SFP module data.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: byte location offset to be पढ़ो
 *  @data: पढ़ो data buffer poपूर्णांकer
 *
 *  Reads one byte from SFP module data stored
 *  in SFP resided EEPROM memory or SFP diagnostic area.
 *  Function should be called with
 *  E1000_I2CCMD_SFP_DATA_ADDR(<byte offset>) क्रम SFP module database access
 *  E1000_I2CCMD_SFP_DIAG_ADDR(<byte offset>) क्रम SFP diagnostics parameters
 *  access
 **/
s32 igb_पढ़ो_sfp_data_byte(काष्ठा e1000_hw *hw, u16 offset, u8 *data)
अणु
	u32 i = 0;
	u32 i2ccmd = 0;
	u32 data_local = 0;

	अगर (offset > E1000_I2CCMD_SFP_DIAG_ADDR(255)) अणु
		hw_dbg("I2CCMD command address exceeds upper limit\n");
		वापस -E1000_ERR_PHY;
	पूर्ण

	/* Set up Op-code, EEPROM Address,in the I2CCMD
	 * रेजिस्टर. The MAC will take care of पूर्णांकerfacing with the
	 * EEPROM to retrieve the desired data.
	 */
	i2ccmd = ((offset << E1000_I2CCMD_REG_ADDR_SHIFT) |
		  E1000_I2CCMD_OPCODE_READ);

	wr32(E1000_I2CCMD, i2ccmd);

	/* Poll the पढ़ोy bit to see अगर the I2C पढ़ो completed */
	क्रम (i = 0; i < E1000_I2CCMD_PHY_TIMEOUT; i++) अणु
		udelay(50);
		data_local = rd32(E1000_I2CCMD);
		अगर (data_local & E1000_I2CCMD_READY)
			अवरोध;
	पूर्ण
	अगर (!(data_local & E1000_I2CCMD_READY)) अणु
		hw_dbg("I2CCMD Read did not complete\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (data_local & E1000_I2CCMD_ERROR) अणु
		hw_dbg("I2CCMD Error bit set\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	*data = (u8) data_local & 0xFF;

	वापस 0;
पूर्ण

/**
 *  igb_पढ़ो_phy_reg_igp - Read igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and storing the retrieved inक्रमmation in data.  Release any acquired
 *  semaphores beक्रमe निकासing.
 **/
s32 igb_पढ़ो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	s32 ret_val = 0;

	अगर (!(hw->phy.ops.acquire))
		जाओ out;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		ret_val = igb_ग_लिखो_phy_reg_mdic(hw,
						 IGP01E1000_PHY_PAGE_SELECT,
						 (u16)offset);
		अगर (ret_val) अणु
			hw->phy.ops.release(hw);
			जाओ out;
		पूर्ण
	पूर्ण

	ret_val = igb_पढ़ो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_ग_लिखो_phy_reg_igp - Write igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
s32 igb_ग_लिखो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	s32 ret_val = 0;

	अगर (!(hw->phy.ops.acquire))
		जाओ out;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		ret_val = igb_ग_लिखो_phy_reg_mdic(hw,
						 IGP01E1000_PHY_PAGE_SELECT,
						 (u16)offset);
		अगर (ret_val) अणु
			hw->phy.ops.release(hw);
			जाओ out;
		पूर्ण
	पूर्ण

	ret_val = igb_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					 data);

	hw->phy.ops.release(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_copper_link_setup_82580 - Setup 82580 PHY क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up Carrier-sense on Transmit and करोwnshअगरt values.
 **/
s32 igb_copper_link_setup_82580(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	अगर (phy->reset_disable) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	अगर (phy->type == e1000_phy_82580) अणु
		ret_val = hw->phy.ops.reset(hw);
		अगर (ret_val) अणु
			hw_dbg("Error resetting the PHY.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Enable CRS on TX. This must be set क्रम half-duplex operation. */
	ret_val = phy->ops.पढ़ो_reg(hw, I82580_CFG_REG, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy_data |= I82580_CFG_ASSERT_CRS_ON_TX;

	/* Enable करोwnshअगरt */
	phy_data |= I82580_CFG_ENABLE_DOWNSHIFT;

	ret_val = phy->ops.ग_लिखो_reg(hw, I82580_CFG_REG, phy_data);
	अगर (ret_val)
		जाओ out;

	/* Set MDI/MDIX mode */
	ret_val = phy->ops.पढ़ो_reg(hw, I82580_PHY_CTRL_2, &phy_data);
	अगर (ret_val)
		जाओ out;
	phy_data &= ~I82580_PHY_CTRL2_MDIX_CFG_MASK;
	/* Options:
	 *   0 - Auto (शेष)
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 */
	चयन (hw->phy.mdix) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		phy_data |= I82580_PHY_CTRL2_MANUAL_MDIX;
		अवरोध;
	हाल 0:
	शेष:
		phy_data |= I82580_PHY_CTRL2_AUTO_MDI_MDIX;
		अवरोध;
	पूर्ण
	ret_val = hw->phy.ops.ग_लिखो_reg(hw, I82580_PHY_CTRL_2, phy_data);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_copper_link_setup_m88 - Setup m88 PHY's क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up MDI/MDI-X and polarity क्रम m88 PHY's.  If necessary, transmit घड़ी
 *  and करोwnshअगरt values are set also.
 **/
s32 igb_copper_link_setup_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	अगर (phy->reset_disable) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	/* Enable CRS on TX. This must be set क्रम half-duplex operation. */
	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;

	/* Options:
	 *   MDI/MDI-X = 0 (शेष)
	 *   0 - Auto क्रम all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto क्रम 1000Base-T only (MDI-X क्रम 10/100Base-T modes)
	 */
	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;

	चयन (phy->mdix) अणु
	हाल 1:
		phy_data |= M88E1000_PSCR_MDI_MANUAL_MODE;
		अवरोध;
	हाल 2:
		phy_data |= M88E1000_PSCR_MDIX_MANUAL_MODE;
		अवरोध;
	हाल 3:
		phy_data |= M88E1000_PSCR_AUTO_X_1000T;
		अवरोध;
	हाल 0:
	शेष:
		phy_data |= M88E1000_PSCR_AUTO_X_MODE;
		अवरोध;
	पूर्ण

	/* Options:
	 *   disable_polarity_correction = 0 (शेष)
	 *       Automatic Correction क्रम Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	phy_data &= ~M88E1000_PSCR_POLARITY_REVERSAL;
	अगर (phy->disable_polarity_correction == 1)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;

	ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		जाओ out;

	अगर (phy->revision < E1000_REVISION_4) अणु
		/* Force TX_CLK in the Extended PHY Specअगरic Control Register
		 * to 25MHz घड़ी.
		 */
		ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
					    &phy_data);
		अगर (ret_val)
			जाओ out;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;

		अगर ((phy->revision == E1000_REVISION_2) &&
		    (phy->id == M88E1111_I_PHY_ID)) अणु
			/* 82573L PHY - set the करोwnshअगरt counter to 5x. */
			phy_data &= ~M88EC018_EPSCR_DOWNSHIFT_COUNTER_MASK;
			phy_data |= M88EC018_EPSCR_DOWNSHIFT_COUNTER_5X;
		पूर्ण अन्यथा अणु
			/* Configure Master and Slave करोwnshअगरt values */
			phy_data &= ~(M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK |
				      M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK);
			phy_data |= (M88E1000_EPSCR_MASTER_DOWNSHIFT_1X |
				     M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X);
		पूर्ण
		ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
					     phy_data);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	/* Commit the changes. */
	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error committing the PHY changes\n");
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_copper_link_setup_m88_gen2 - Setup m88 PHY's क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up MDI/MDI-X and polarity क्रम i347-AT4, m88e1322 and m88e1112 PHY's.
 *  Also enables and sets the करोwnshअगरt parameters.
 **/
s32 igb_copper_link_setup_m88_gen2(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	अगर (phy->reset_disable)
		वापस 0;

	/* Enable CRS on Tx. This must be set क्रम half-duplex operation. */
	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Options:
	 *   MDI/MDI-X = 0 (शेष)
	 *   0 - Auto क्रम all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto क्रम 1000Base-T only (MDI-X क्रम 10/100Base-T modes)
	 */
	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;

	चयन (phy->mdix) अणु
	हाल 1:
		phy_data |= M88E1000_PSCR_MDI_MANUAL_MODE;
		अवरोध;
	हाल 2:
		phy_data |= M88E1000_PSCR_MDIX_MANUAL_MODE;
		अवरोध;
	हाल 3:
		/* M88E1112 करोes not support this mode) */
		अगर (phy->id != M88E1112_E_PHY_ID) अणु
			phy_data |= M88E1000_PSCR_AUTO_X_1000T;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0:
	शेष:
		phy_data |= M88E1000_PSCR_AUTO_X_MODE;
		अवरोध;
	पूर्ण

	/* Options:
	 *   disable_polarity_correction = 0 (शेष)
	 *       Automatic Correction क्रम Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	phy_data &= ~M88E1000_PSCR_POLARITY_REVERSAL;
	अगर (phy->disable_polarity_correction == 1)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;

	/* Enable करोwnshअगरt and setting it to X6 */
	अगर (phy->id == M88E1543_E_PHY_ID) अणु
		phy_data &= ~I347AT4_PSCR_DOWNSHIFT_ENABLE;
		ret_val =
		    phy->ops.ग_लिखो_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;

		ret_val = igb_phy_sw_reset(hw);
		अगर (ret_val) अणु
			hw_dbg("Error committing the PHY changes\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	phy_data &= ~I347AT4_PSCR_DOWNSHIFT_MASK;
	phy_data |= I347AT4_PSCR_DOWNSHIFT_6X;
	phy_data |= I347AT4_PSCR_DOWNSHIFT_ENABLE;

	ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Commit the changes. */
	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error committing the PHY changes\n");
		वापस ret_val;
	पूर्ण
	ret_val = igb_set_master_slave_mode(hw);
	अगर (ret_val)
		वापस ret_val;

	वापस 0;
पूर्ण

/**
 *  igb_copper_link_setup_igp - Setup igp PHY's क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up LPLU, MDI/MDI-X, polarity, Smartspeed and Master/Slave config क्रम
 *  igp PHY's.
 **/
s32 igb_copper_link_setup_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	अगर (phy->reset_disable) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error resetting the PHY.\n");
		जाओ out;
	पूर्ण

	/* Wait 100ms क्रम MAC to configure PHY from NVM settings, to aव्योम
	 * समयout issues when LFS is enabled.
	 */
	msleep(100);

	/* The NVM settings will configure LPLU in D3 क्रम
	 * non-IGP1 PHYs.
	 */
	अगर (phy->type == e1000_phy_igp) अणु
		/* disable lplu d3 during driver init */
		अगर (phy->ops.set_d3_lplu_state)
			ret_val = phy->ops.set_d3_lplu_state(hw, false);
		अगर (ret_val) अणु
			hw_dbg("Error Disabling LPLU D3\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* disable lplu d0 during driver init */
	ret_val = phy->ops.set_d0_lplu_state(hw, false);
	अगर (ret_val) अणु
		hw_dbg("Error Disabling LPLU D0\n");
		जाओ out;
	पूर्ण
	/* Configure mdi-mdix settings */
	ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_CTRL, &data);
	अगर (ret_val)
		जाओ out;

	data &= ~IGP01E1000_PSCR_AUTO_MDIX;

	चयन (phy->mdix) अणु
	हाल 1:
		data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;
		अवरोध;
	हाल 2:
		data |= IGP01E1000_PSCR_FORCE_MDI_MDIX;
		अवरोध;
	हाल 0:
	शेष:
		data |= IGP01E1000_PSCR_AUTO_MDIX;
		अवरोध;
	पूर्ण
	ret_val = phy->ops.ग_लिखो_reg(hw, IGP01E1000_PHY_PORT_CTRL, data);
	अगर (ret_val)
		जाओ out;

	/* set स्वतः-master slave resolution settings */
	अगर (hw->mac.स्वतःneg) अणु
		/* when स्वतःnegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware शेष.
		 */
		अगर (phy->स्वतःneg_advertised == ADVERTISE_1000_FULL) अणु
			/* Disable SmartSpeed */
			ret_val = phy->ops.पढ़ो_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			अगर (ret_val)
				जाओ out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.ग_लिखो_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			अगर (ret_val)
				जाओ out;

			/* Set स्वतः Master/Slave resolution process */
			ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_CTRL, &data);
			अगर (ret_val)
				जाओ out;

			data &= ~CR_1000T_MS_ENABLE;
			ret_val = phy->ops.ग_लिखो_reg(hw, PHY_1000T_CTRL, data);
			अगर (ret_val)
				जाओ out;
		पूर्ण

		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_CTRL, &data);
		अगर (ret_val)
			जाओ out;

		/* load शेषs क्रम future use */
		phy->original_ms_type = (data & CR_1000T_MS_ENABLE) ?
			((data & CR_1000T_MS_VALUE) ?
			e1000_ms_क्रमce_master :
			e1000_ms_क्रमce_slave) :
			e1000_ms_स्वतः;

		चयन (phy->ms_type) अणु
		हाल e1000_ms_क्रमce_master:
			data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
			अवरोध;
		हाल e1000_ms_क्रमce_slave:
			data |= CR_1000T_MS_ENABLE;
			data &= ~(CR_1000T_MS_VALUE);
			अवरोध;
		हाल e1000_ms_स्वतः:
			data &= ~CR_1000T_MS_ENABLE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		ret_val = phy->ops.ग_लिखो_reg(hw, PHY_1000T_CTRL, data);
		अगर (ret_val)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_copper_link_स्वतःneg - Setup/Enable स्वतःneg क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Perक्रमms initial bounds checking on स्वतःneg advertisement parameter, then
 *  configure to advertise the full capability.  Setup the PHY to स्वतःneg
 *  and restart the negotiation process between the link partner.  If
 *  स्वतःneg_रुको_to_complete, then रुको क्रम स्वतःneg to complete beक्रमe निकासing.
 **/
अटल s32 igb_copper_link_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_ctrl;

	/* Perक्रमm some bounds checking on the स्वतःneg advertisement
	 * parameter.
	 */
	phy->स्वतःneg_advertised &= phy->स्वतःneg_mask;

	/* If स्वतःneg_advertised is zero, we assume it was not शेषed
	 * by the calling code so we set to advertise full capability.
	 */
	अगर (phy->स्वतःneg_advertised == 0)
		phy->स्वतःneg_advertised = phy->स्वतःneg_mask;

	hw_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = igb_phy_setup_स्वतःneg(hw);
	अगर (ret_val) अणु
		hw_dbg("Error Setting up Auto-Negotiation\n");
		जाओ out;
	पूर्ण
	hw_dbg("Restarting Auto-Neg\n");

	/* Restart स्वतः-negotiation by setting the Auto Neg Enable bit and
	 * the Auto Neg Restart bit in the PHY control रेजिस्टर.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_ctrl);
	अगर (ret_val)
		जाओ out;

	phy_ctrl |= (MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG);
	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_ctrl);
	अगर (ret_val)
		जाओ out;

	/* Does the user want to रुको क्रम Auto-Neg to complete here, or
	 * check at a later समय (क्रम example, callback routine).
	 */
	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		ret_val = igb_रुको_स्वतःneg(hw);
		अगर (ret_val) अणु
			hw_dbg("Error while waiting for autoneg to complete\n");
			जाओ out;
		पूर्ण
	पूर्ण

	hw->mac.get_link_status = true;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_setup_स्वतःneg - Configure PHY क्रम स्वतः-negotiation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the MII स्वतः-neg advertisement रेजिस्टर and/or the 1000T control
 *  रेजिस्टर and अगर the PHY is alपढ़ोy setup क्रम स्वतः-negotiation, then
 *  वापस successful.  Otherwise, setup advertisement and flow control to
 *  the appropriate values क्रम the wanted स्वतः-negotiation.
 **/
अटल s32 igb_phy_setup_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg = 0;

	phy->स्वतःneg_advertised &= phy->स्वतःneg_mask;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = phy->ops.पढ़ो_reg(hw, PHY_AUTONEG_ADV, &mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		जाओ out;

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL) अणु
		/* Read the MII 1000Base-T Control Register (Address 9). */
		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_CTRL,
					    &mii_1000t_ctrl_reg);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	/* Need to parse both स्वतःneg_advertised and fc and set up
	 * the appropriate PHY रेजिस्टरs.  First we will parse क्रम
	 * स्वतःneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * inभागidually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_स्वतःneg_adv_reg &= ~(NWAY_AR_100TX_FD_CAPS |
				 NWAY_AR_100TX_HD_CAPS |
				 NWAY_AR_10T_FD_CAPS   |
				 NWAY_AR_10T_HD_CAPS);
	mii_1000t_ctrl_reg &= ~(CR_1000T_HD_CAPS | CR_1000T_FD_CAPS);

	hw_dbg("autoneg_advertised %x\n", phy->स्वतःneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_HALF) अणु
		hw_dbg("Advertise 10mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 10 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_FULL) अणु
		hw_dbg("Advertise 10mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_HALF) अणु
		hw_dbg("Advertise 100mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
	पूर्ण

	/* Do we want to advertise 100 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_FULL) अणु
		hw_dbg("Advertise 100mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
	पूर्ण

	/* We करो not allow the Phy to advertise 1000 Mb Half Duplex */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_HALF)
		hw_dbg("Advertise 1000mb Half duplex request denied!\n");

	/* Do we want to advertise 1000 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_FULL) अणु
		hw_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
	पूर्ण

	/* Check क्रम a software override of the flow control settings, and
	 * setup the PHY advertisement रेजिस्टरs accordingly.  If
	 * स्वतः-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (PHY_AUTONEG_ADV) and re-start स्वतः-
	 * negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          but we करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	चयन (hw->fc.current_mode) अणु
	हाल e1000_fc_none:
		/* Flow control (RX & TX) is completely disabled by a
		 * software over-ride.
		 */
		mii_स्वतःneg_adv_reg &= ~(NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल e1000_fc_rx_छोड़ो:
		/* RX Flow control is enabled, and TX Flow control is
		 * disabled, by a software over-ride.
		 *
		 * Since there really isn't a way to advertise that we are
		 * capable of RX Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric RX PAUSE.  Later
		 * (in e1000_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	हाल e1000_fc_tx_छोड़ो:
		/* TX Flow control is enabled, and RX Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_स्वतःneg_adv_reg |= NWAY_AR_ASM_सूची;
		mii_स्वतःneg_adv_reg &= ~NWAY_AR_PAUSE;
		अवरोध;
	हाल e1000_fc_full:
		/* Flow control (both RX and TX) is enabled by a software
		 * over-ride.
		 */
		mii_स्वतःneg_adv_reg |= (NWAY_AR_ASM_सूची | NWAY_AR_PAUSE);
		अवरोध;
	शेष:
		hw_dbg("Flow control param set incorrectly\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_AUTONEG_ADV, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		जाओ out;

	hw_dbg("Auto-Neg Advertising %x\n", mii_स्वतःneg_adv_reg);

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL) अणु
		ret_val = phy->ops.ग_लिखो_reg(hw,
					     PHY_1000T_CTRL,
					     mii_1000t_ctrl_reg);
		अगर (ret_val)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_setup_copper_link - Configure copper link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the appropriate function to configure the link क्रम स्वतः-neg or क्रमced
 *  speed and duplex.  Then we check क्रम link, once link is established calls
 *  to configure collision distance and flow control are called.  If link is
 *  not established, we वापस -E1000_ERR_PHY (-2).
 **/
s32 igb_setup_copper_link(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	bool link;

	अगर (hw->mac.स्वतःneg) अणु
		/* Setup स्वतःneg and flow control advertisement and perक्रमm
		 * स्वतःnegotiation.
		 */
		ret_val = igb_copper_link_स्वतःneg(hw);
		अगर (ret_val)
			जाओ out;
	पूर्ण अन्यथा अणु
		/* PHY will be set to 10H, 10F, 100H or 100F
		 * depending on user settings.
		 */
		hw_dbg("Forcing Speed and Duplex\n");
		ret_val = hw->phy.ops.क्रमce_speed_duplex(hw);
		अगर (ret_val) अणु
			hw_dbg("Error Forcing Speed and Duplex\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Check link status. Wait up to 100 microseconds क्रम link to become
	 * valid.
	 */
	ret_val = igb_phy_has_link(hw, COPPER_LINK_UP_LIMIT, 10, &link);
	अगर (ret_val)
		जाओ out;

	अगर (link) अणु
		hw_dbg("Valid link established!!!\n");
		igb_config_collision_dist(hw);
		ret_val = igb_config_fc_after_link_up(hw);
	पूर्ण अन्यथा अणु
		hw_dbg("Unable to establish link!!!\n");
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_क्रमce_speed_duplex_igp - Force speed/duplex क्रम igp PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.  Clears the
 *  स्वतः-crossover to क्रमce MDI manually.  Waits क्रम link and वापसs
 *  successful अगर link up is successful, अन्यथा -E1000_ERR_PHY (-2).
 **/
s32 igb_phy_क्रमce_speed_duplex_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	ret_val = phy->ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_data);
	अगर (ret_val)
		जाओ out;

	igb_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_data);
	अगर (ret_val)
		जाओ out;

	/* Clear Auto-Crossover to क्रमce MDI manually.  IGP requires MDI
	 * क्रमced whenever speed and duplex are क्रमced.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;
	phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;

	ret_val = phy->ops.ग_लिखो_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
	अगर (ret_val)
		जाओ out;

	hw_dbg("IGP PSCR: %X\n", phy_data);

	udelay(1);

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		hw_dbg("Waiting for forced speed/duplex link on IGP phy.\n");

		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 10000, &link);
		अगर (ret_val)
			जाओ out;

		अगर (!link)
			hw_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 10000, &link);
		अगर (ret_val)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_क्रमce_speed_duplex_m88 - Force speed/duplex क्रम m88 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.  Clears the
 *  स्वतः-crossover to क्रमce MDI manually.  Resets the PHY to commit the
 *  changes.  If समय expires जबतक रुकोing क्रम link up, we reset the DSP.
 *  After reset, TX_CLK and CRS on TX must be set.  Return successful upon
 *  successful completion, अन्यथा वापस corresponding error code.
 **/
s32 igb_phy_क्रमce_speed_duplex_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	/* I210 and I211 devices support Auto-Crossover in क्रमced operation. */
	अगर (phy->type != e1000_phy_i210) अणु
		/* Clear Auto-Crossover to क्रमce MDI manually.  M88E1000
		 * requires MDI क्रमced whenever speed and duplex are क्रमced.
		 */
		ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_CTRL,
					    &phy_data);
		अगर (ret_val)
			जाओ out;

		phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
		ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_PHY_SPEC_CTRL,
					     phy_data);
		अगर (ret_val)
			जाओ out;

		hw_dbg("M88E1000 PSCR: %X\n", phy_data);
	पूर्ण

	ret_val = phy->ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_data);
	अगर (ret_val)
		जाओ out;

	igb_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_data);
	अगर (ret_val)
		जाओ out;

	/* Reset the phy to commit changes. */
	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val)
		जाओ out;

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		hw_dbg("Waiting for forced speed/duplex link on M88 phy.\n");

		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 100000, &link);
		अगर (ret_val)
			जाओ out;

		अगर (!link) अणु
			bool reset_dsp = true;

			चयन (hw->phy.id) अणु
			हाल I347AT4_E_PHY_ID:
			हाल M88E1112_E_PHY_ID:
			हाल M88E1543_E_PHY_ID:
			हाल M88E1512_E_PHY_ID:
			हाल I210_I_PHY_ID:
				reset_dsp = false;
				अवरोध;
			शेष:
				अगर (hw->phy.type != e1000_phy_m88)
					reset_dsp = false;
				अवरोध;
			पूर्ण
			अगर (!reset_dsp) अणु
				hw_dbg("Link taking longer than expected.\n");
			पूर्ण अन्यथा अणु
				/* We didn't get link.
				 * Reset the DSP and cross our fingers.
				 */
				ret_val = phy->ops.ग_लिखो_reg(hw,
						M88E1000_PHY_PAGE_SELECT,
						0x001d);
				अगर (ret_val)
					जाओ out;
				ret_val = igb_phy_reset_dsp(hw);
				अगर (ret_val)
					जाओ out;
			पूर्ण
		पूर्ण

		/* Try once more */
		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT,
					   100000, &link);
		अगर (ret_val)
			जाओ out;
	पूर्ण

	अगर (hw->phy.type != e1000_phy_m88 ||
	    hw->phy.id == I347AT4_E_PHY_ID ||
	    hw->phy.id == M88E1112_E_PHY_ID ||
	    hw->phy.id == M88E1543_E_PHY_ID ||
	    hw->phy.id == M88E1512_E_PHY_ID ||
	    hw->phy.id == I210_I_PHY_ID)
		जाओ out;

	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		जाओ out;

	/* Resetting the phy means we need to re-क्रमce TX_CLK in the
	 * Extended PHY Specअगरic Control Register to 25MHz घड़ी from
	 * the reset value of 2.5MHz.
	 */
	phy_data |= M88E1000_EPSCR_TX_CLK_25;
	ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		जाओ out;

	/* In addition, we must re-enable CRS on Tx क्रम both half and full
	 * duplex.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	ret_val = phy->ops.ग_लिखो_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_क्रमce_speed_duplex_setup - Configure क्रमced PHY speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @phy_ctrl: poपूर्णांकer to current value of PHY_CONTROL
 *
 *  Forces speed and duplex on the PHY by करोing the following: disable flow
 *  control, क्रमce speed/duplex on the MAC, disable स्वतः speed detection,
 *  disable स्वतः-negotiation, configure duplex, configure speed, configure
 *  the collision distance, ग_लिखो configuration to CTRL रेजिस्टर.  The
 *  caller must ग_लिखो to the PHY_CONTROL रेजिस्टर क्रम these settings to
 *  take affect.
 **/
अटल व्योम igb_phy_क्रमce_speed_duplex_setup(काष्ठा e1000_hw *hw,
					     u16 *phy_ctrl)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 ctrl;

	/* Turn off flow control when क्रमcing speed/duplex */
	hw->fc.current_mode = e1000_fc_none;

	/* Force speed/duplex on the mac */
	ctrl = rd32(E1000_CTRL);
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~E1000_CTRL_SPD_SEL;

	/* Disable Auto Speed Detection */
	ctrl &= ~E1000_CTRL_ASDE;

	/* Disable स्वतःneg on the phy */
	*phy_ctrl &= ~MII_CR_AUTO_NEG_EN;

	/* Forcing Full or Half Duplex? */
	अगर (mac->क्रमced_speed_duplex & E1000_ALL_HALF_DUPLEX) अणु
		ctrl &= ~E1000_CTRL_FD;
		*phy_ctrl &= ~MII_CR_FULL_DUPLEX;
		hw_dbg("Half Duplex\n");
	पूर्ण अन्यथा अणु
		ctrl |= E1000_CTRL_FD;
		*phy_ctrl |= MII_CR_FULL_DUPLEX;
		hw_dbg("Full Duplex\n");
	पूर्ण

	/* Forcing 10mb or 100mb? */
	अगर (mac->क्रमced_speed_duplex & E1000_ALL_100_SPEED) अणु
		ctrl |= E1000_CTRL_SPD_100;
		*phy_ctrl |= MII_CR_SPEED_100;
		*phy_ctrl &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_10);
		hw_dbg("Forcing 100mb\n");
	पूर्ण अन्यथा अणु
		ctrl &= ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
		*phy_ctrl |= MII_CR_SPEED_10;
		*phy_ctrl &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_100);
		hw_dbg("Forcing 10mb\n");
	पूर्ण

	igb_config_collision_dist(hw);

	wr32(E1000_CTRL, ctrl);
पूर्ण

/**
 *  igb_set_d3_lplu_state - Sets low घातer link up state क्रम D3
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
s32 igb_set_d3_lplu_state(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 data;

	अगर (!(hw->phy.ops.पढ़ो_reg))
		जाओ out;

	ret_val = phy->ops.पढ़ो_reg(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	अगर (ret_val)
		जाओ out;

	अगर (!active) अणु
		data &= ~IGP02E1000_PM_D3_LPLU;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP02E1000_PHY_POWER_MGMT,
					     data);
		अगर (ret_val)
			जाओ out;
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the घातer conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so perक्रमmance is मुख्यtained.
		 */
		अगर (phy->smart_speed == e1000_smart_speed_on) अणु
			ret_val = phy->ops.पढ़ो_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			अगर (ret_val)
				जाओ out;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.ग_लिखो_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			अगर (ret_val)
				जाओ out;
		पूर्ण अन्यथा अगर (phy->smart_speed == e1000_smart_speed_off) अणु
			ret_val = phy->ops.पढ़ो_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     &data);
			अगर (ret_val)
				जाओ out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.ग_लिखो_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			अगर (ret_val)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((phy->स्वतःneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_NOT_GIG) ||
		   (phy->स्वतःneg_advertised == E1000_ALL_10_SPEED)) अणु
		data |= IGP02E1000_PM_D3_LPLU;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP02E1000_PHY_POWER_MGMT,
					      data);
		अगर (ret_val)
			जाओ out;

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					    &data);
		अगर (ret_val)
			जाओ out;

		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = phy->ops.ग_लिखो_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					     data);
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_check_करोwnshअगरt - Checks whether a करोwnshअगरt in speed occurred
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs 1
 *
 *  A करोwnshअगरt is detected by querying the PHY link health.
 **/
s32 igb_check_करोwnshअगरt(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, offset, mask;

	चयन (phy->type) अणु
	हाल e1000_phy_i210:
	हाल e1000_phy_m88:
	हाल e1000_phy_gg82563:
		offset	= M88E1000_PHY_SPEC_STATUS;
		mask	= M88E1000_PSSR_DOWNSHIFT;
		अवरोध;
	हाल e1000_phy_igp_2:
	हाल e1000_phy_igp:
	हाल e1000_phy_igp_3:
		offset	= IGP01E1000_PHY_LINK_HEALTH;
		mask	= IGP01E1000_PLHR_SS_DOWNGRADE;
		अवरोध;
	शेष:
		/* speed करोwnshअगरt not supported */
		phy->speed_करोwngraded = false;
		ret_val = 0;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.पढ़ो_reg(hw, offset, &phy_data);

	अगर (!ret_val)
		phy->speed_करोwngraded = (phy_data & mask) ? true : false;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_check_polarity_m88 - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY specअगरic status रेजिस्टर.
 **/
s32 igb_check_polarity_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_STATUS, &data);

	अगर (!ret_val)
		phy->cable_polarity = (data & M88E1000_PSSR_REV_POLARITY)
				      ? e1000_rev_polarity_reversed
				      : e1000_rev_polarity_normal;

	वापस ret_val;
पूर्ण

/**
 *  igb_check_polarity_igp - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY port status रेजिस्टर, and the
 *  current speed (since there is no polarity at 100Mbps).
 **/
अटल s32 igb_check_polarity_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data, offset, mask;

	/* Polarity is determined based on the speed of
	 * our connection.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	अगर (ret_val)
		जाओ out;

	अगर ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
		offset	= IGP01E1000_PHY_PCS_INIT_REG;
		mask	= IGP01E1000_PHY_POLARITY_MASK;
	पूर्ण अन्यथा अणु
		/* This really only applies to 10Mbps since
		 * there is no polarity क्रम 100Mbps (always 0).
		 */
		offset	= IGP01E1000_PHY_PORT_STATUS;
		mask	= IGP01E1000_PSSR_POLARITY_REVERSED;
	पूर्ण

	ret_val = phy->ops.पढ़ो_reg(hw, offset, &data);

	अगर (!ret_val)
		phy->cable_polarity = (data & mask)
				      ? e1000_rev_polarity_reversed
				      : e1000_rev_polarity_normal;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_रुको_स्वतःneg - Wait क्रम स्वतः-neg completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Waits क्रम स्वतः-negotiation to complete or क्रम the स्वतः-negotiation समय
 *  limit to expire, which ever happens first.
 **/
अटल s32 igb_रुको_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 i, phy_status;

	/* Break after स्वतःneg completes or PHY_AUTO_NEG_LIMIT expires. */
	क्रम (i = PHY_AUTO_NEG_LIMIT; i > 0; i--) अणु
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & MII_SR_AUTONEG_COMPLETE)
			अवरोध;
		msleep(100);
	पूर्ण

	/* PHY_AUTO_NEG_TIME expiration करोesn't guarantee स्वतः-negotiation
	 * has completed.
	 */
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_has_link - Polls PHY क्रम link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @iterations: number of बार to poll क्रम link
 *  @usec_पूर्णांकerval: delay between polling attempts
 *  @success: poपूर्णांकer to whether polling was successful or not
 *
 *  Polls the PHY status रेजिस्टर क्रम link, 'iterations' number of बार.
 **/
s32 igb_phy_has_link(काष्ठा e1000_hw *hw, u32 iterations,
		     u32 usec_पूर्णांकerval, bool *success)
अणु
	s32 ret_val = 0;
	u16 i, phy_status;

	क्रम (i = 0; i < iterations; i++) अणु
		/* Some PHYs require the PHY_STATUS रेजिस्टर to be पढ़ो
		 * twice due to the link bit being sticky.  No harm करोing
		 * it across the board.
		 */
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val && usec_पूर्णांकerval > 0) अणु
			/* If the first पढ़ो fails, another entity may have
			 * ownership of the resources, रुको and try again to
			 * see अगर they have relinquished the resources yet.
			 */
			अगर (usec_पूर्णांकerval >= 1000)
				mdelay(usec_पूर्णांकerval/1000);
			अन्यथा
				udelay(usec_पूर्णांकerval);
		पूर्ण
		ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_STATUS, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & MII_SR_LINK_STATUS)
			अवरोध;
		अगर (usec_पूर्णांकerval >= 1000)
			mdelay(usec_पूर्णांकerval/1000);
		अन्यथा
			udelay(usec_पूर्णांकerval);
	पूर्ण

	*success = (i < iterations) ? true : false;

	वापस ret_val;
पूर्ण

/**
 *  igb_get_cable_length_m88 - Determine cable length क्रम m88 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the PHY specअगरic status रेजिस्टर to retrieve the cable length
 *  inक्रमmation.  The cable length is determined by averaging the minimum and
 *  maximum values to get the "average" cable length.  The m88 PHY has four
 *  possible cable length values, which are:
 *	Register Value		Cable Length
 *	0			< 50 meters
 *	1			50 - 80 meters
 *	2			80 - 110 meters
 *	3			110 - 140 meters
 *	4			> 140 meters
 **/
s32 igb_get_cable_length_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, index;

	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	अगर (ret_val)
		जाओ out;

	index = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
		M88E1000_PSSR_CABLE_LENGTH_SHIFT;
	अगर (index >= ARRAY_SIZE(e1000_m88_cable_length_table) - 1) अणु
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण

	phy->min_cable_length = e1000_m88_cable_length_table[index];
	phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

out:
	वापस ret_val;
पूर्ण

s32 igb_get_cable_length_m88_gen2(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, phy_data2, index, शेष_page, is_cm;
	पूर्णांक len_tot = 0;
	u16 len_min;
	u16 len_max;

	चयन (hw->phy.id) अणु
	हाल M88E1543_E_PHY_ID:
	हाल M88E1512_E_PHY_ID:
	हाल I347AT4_E_PHY_ID:
	हाल I210_I_PHY_ID:
		/* Remember the original page select and set it to 7 */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PAGE_SELECT,
					    &शेष_page);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.ग_लिखो_reg(hw, I347AT4_PAGE_SELECT, 0x07);
		अगर (ret_val)
			जाओ out;

		/* Check अगर the unit of cable length is meters or cm */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PCDC, &phy_data2);
		अगर (ret_val)
			जाओ out;

		is_cm = !(phy_data2 & I347AT4_PCDC_CABLE_LENGTH_UNIT);

		/* Get cable length from Pair 0 length Regs */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PCDL0, &phy_data);
		अगर (ret_val)
			जाओ out;

		phy->pair_length[0] = phy_data / (is_cm ? 100 : 1);
		len_tot = phy->pair_length[0];
		len_min = phy->pair_length[0];
		len_max = phy->pair_length[0];

		/* Get cable length from Pair 1 length Regs */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PCDL1, &phy_data);
		अगर (ret_val)
			जाओ out;

		phy->pair_length[1] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[1];
		len_min = min(len_min, phy->pair_length[1]);
		len_max = max(len_max, phy->pair_length[1]);

		/* Get cable length from Pair 2 length Regs */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PCDL2, &phy_data);
		अगर (ret_val)
			जाओ out;

		phy->pair_length[2] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[2];
		len_min = min(len_min, phy->pair_length[2]);
		len_max = max(len_max, phy->pair_length[2]);

		/* Get cable length from Pair 3 length Regs */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PCDL3, &phy_data);
		अगर (ret_val)
			जाओ out;

		phy->pair_length[3] = phy_data / (is_cm ? 100 : 1);
		len_tot += phy->pair_length[3];
		len_min = min(len_min, phy->pair_length[3]);
		len_max = max(len_max, phy->pair_length[3]);

		/* Populate the phy काष्ठाure with cable length in meters */
		phy->min_cable_length = len_min;
		phy->max_cable_length = len_max;
		phy->cable_length = len_tot / 4;

		/* Reset the page selec to its original value */
		ret_val = phy->ops.ग_लिखो_reg(hw, I347AT4_PAGE_SELECT,
					     शेष_page);
		अगर (ret_val)
			जाओ out;
		अवरोध;
	हाल M88E1112_E_PHY_ID:
		/* Remember the original page select and set it to 5 */
		ret_val = phy->ops.पढ़ो_reg(hw, I347AT4_PAGE_SELECT,
					    &शेष_page);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.ग_लिखो_reg(hw, I347AT4_PAGE_SELECT, 0x05);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.पढ़ो_reg(hw, M88E1112_VCT_DSP_DISTANCE,
					    &phy_data);
		अगर (ret_val)
			जाओ out;

		index = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
			M88E1000_PSSR_CABLE_LENGTH_SHIFT;
		अगर (index >= ARRAY_SIZE(e1000_m88_cable_length_table) - 1) अणु
			ret_val = -E1000_ERR_PHY;
			जाओ out;
		पूर्ण

		phy->min_cable_length = e1000_m88_cable_length_table[index];
		phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

		phy->cable_length = (phy->min_cable_length +
				     phy->max_cable_length) / 2;

		/* Reset the page select to its original value */
		ret_val = phy->ops.ग_लिखो_reg(hw, I347AT4_PAGE_SELECT,
					     शेष_page);
		अगर (ret_val)
			जाओ out;

		अवरोध;
	शेष:
		ret_val = -E1000_ERR_PHY;
		जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_cable_length_igp_2 - Determine cable length क्रम igp2 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The स्वतःmatic gain control (agc) normalizes the amplitude of the
 *  received संकेत, adjusting क्रम the attenuation produced by the
 *  cable.  By पढ़ोing the AGC रेजिस्टरs, which represent the
 *  combination of coarse and fine gain value, the value can be put
 *  पूर्णांकo a lookup table to obtain the approximate cable length
 *  क्रम each channel.
 **/
s32 igb_get_cable_length_igp_2(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_data, i, agc_value = 0;
	u16 cur_agc_index, max_agc_index = 0;
	u16 min_agc_index = ARRAY_SIZE(e1000_igp_2_cable_length_table) - 1;
	अटल स्थिर u16 agc_reg_array[IGP02E1000_PHY_CHANNEL_NUM] = अणु
		IGP02E1000_PHY_AGC_A,
		IGP02E1000_PHY_AGC_B,
		IGP02E1000_PHY_AGC_C,
		IGP02E1000_PHY_AGC_D
	पूर्ण;

	/* Read the AGC रेजिस्टरs क्रम all channels */
	क्रम (i = 0; i < IGP02E1000_PHY_CHANNEL_NUM; i++) अणु
		ret_val = phy->ops.पढ़ो_reg(hw, agc_reg_array[i], &phy_data);
		अगर (ret_val)
			जाओ out;

		/* Getting bits 15:9, which represent the combination of
		 * coarse and fine gain values.  The result is a number
		 * that can be put पूर्णांकo the lookup table to obtain the
		 * approximate cable length.
		 */
		cur_agc_index = (phy_data >> IGP02E1000_AGC_LENGTH_SHIFT) &
				IGP02E1000_AGC_LENGTH_MASK;

		/* Array index bound check. */
		अगर ((cur_agc_index >= ARRAY_SIZE(e1000_igp_2_cable_length_table)) ||
		    (cur_agc_index == 0)) अणु
			ret_val = -E1000_ERR_PHY;
			जाओ out;
		पूर्ण

		/* Remove min & max AGC values from calculation. */
		अगर (e1000_igp_2_cable_length_table[min_agc_index] >
		    e1000_igp_2_cable_length_table[cur_agc_index])
			min_agc_index = cur_agc_index;
		अगर (e1000_igp_2_cable_length_table[max_agc_index] <
		    e1000_igp_2_cable_length_table[cur_agc_index])
			max_agc_index = cur_agc_index;

		agc_value += e1000_igp_2_cable_length_table[cur_agc_index];
	पूर्ण

	agc_value -= (e1000_igp_2_cable_length_table[min_agc_index] +
		      e1000_igp_2_cable_length_table[max_agc_index]);
	agc_value /= (IGP02E1000_PHY_CHANNEL_NUM - 2);

	/* Calculate cable length with the error range of +/- 10 meters. */
	phy->min_cable_length = ((agc_value - IGP02E1000_AGC_RANGE) > 0) ?
				 (agc_value - IGP02E1000_AGC_RANGE) : 0;
	phy->max_cable_length = agc_value + IGP02E1000_AGC_RANGE;

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_phy_info_m88 - Retrieve PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Valid क्रम only copper links.  Read the PHY status रेजिस्टर (sticky पढ़ो)
 *  to verअगरy that link is up.  Read the PHY special control रेजिस्टर to
 *  determine the polarity and 10base-T extended distance.  Read the PHY
 *  special status रेजिस्टर to determine MDI/MDIx and current speed.  If
 *  speed is 1000, then determine cable length, local and remote receiver.
 **/
s32 igb_get_phy_info_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32  ret_val;
	u16 phy_data;
	bool link;

	अगर (phy->media_type != e1000_media_type_copper) अणु
		hw_dbg("Phy info is only valid for copper media\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	ret_val = igb_phy_has_link(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (!link) अणु
		hw_dbg("Phy info is only valid if link is up\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy->polarity_correction = (phy_data & M88E1000_PSCR_POLARITY_REVERSAL)
				   ? true : false;

	ret_val = igb_check_polarity_m88(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.पढ़ो_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy->is_mdix = (phy_data & M88E1000_PSSR_MDIX) ? true : false;

	अगर ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS) अणु
		ret_val = phy->ops.get_cable_length(hw);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_STATUS, &phy_data);
		अगर (ret_val)
			जाओ out;

		phy->local_rx = (phy_data & SR_1000T_LOCAL_RX_STATUS)
				? e1000_1000t_rx_status_ok
				: e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (phy_data & SR_1000T_REMOTE_RX_STATUS)
				 ? e1000_1000t_rx_status_ok
				 : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		/* Set values to "undefined" */
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_phy_info_igp - Retrieve igp PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read PHY status to determine अगर link is up.  If link is up, then
 *  set/determine 10base-T extended distance and polarity correction.  Read
 *  PHY port status to determine MDI/MDIx and speed.  Based on the speed,
 *  determine on the cable length, local and remote receiver.
 **/
s32 igb_get_phy_info_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = igb_phy_has_link(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (!link) अणु
		hw_dbg("Phy info is only valid if link is up\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	phy->polarity_correction = true;

	ret_val = igb_check_polarity_igp(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.पढ़ो_reg(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	अगर (ret_val)
		जाओ out;

	phy->is_mdix = (data & IGP01E1000_PSSR_MDIX) ? true : false;

	अगर ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
		ret_val = phy->ops.get_cable_length(hw);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_STATUS, &data);
		अगर (ret_val)
			जाओ out;

		phy->local_rx = (data & SR_1000T_LOCAL_RX_STATUS)
				? e1000_1000t_rx_status_ok
				: e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & SR_1000T_REMOTE_RX_STATUS)
				 ? e1000_1000t_rx_status_ok
				 : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_sw_reset - PHY software reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Does a software reset of the PHY by पढ़ोing the PHY control रेजिस्टर and
 *  setting/ग_लिखो the control रेजिस्टर reset bit to the PHY.
 **/
s32 igb_phy_sw_reset(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 phy_ctrl;

	अगर (!(hw->phy.ops.पढ़ो_reg))
		जाओ out;

	ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_ctrl);
	अगर (ret_val)
		जाओ out;

	phy_ctrl |= MII_CR_RESET;
	ret_val = hw->phy.ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_ctrl);
	अगर (ret_val)
		जाओ out;

	udelay(1);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_hw_reset - PHY hardware reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरy the reset block is not blocking us from resetting.  Acquire
 *  semaphore (अगर necessary) and पढ़ो/set/ग_लिखो the device control reset
 *  bit in the PHY.  Wait the appropriate delay समय क्रम the device to
 *  reset and release the semaphore (अगर necessary).
 **/
s32 igb_phy_hw_reset(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32  ret_val;
	u32 ctrl;

	ret_val = igb_check_reset_block(hw);
	अगर (ret_val) अणु
		ret_val = 0;
		जाओ out;
	पूर्ण

	ret_val = phy->ops.acquire(hw);
	अगर (ret_val)
		जाओ out;

	ctrl = rd32(E1000_CTRL);
	wr32(E1000_CTRL, ctrl | E1000_CTRL_PHY_RST);
	wrfl();

	udelay(phy->reset_delay_us);

	wr32(E1000_CTRL, ctrl);
	wrfl();

	udelay(150);

	phy->ops.release(hw);

	ret_val = phy->ops.get_cfg_करोne(hw);

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_phy_init_script_igp3 - Inits the IGP3 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes a Intel Gigabit PHY3 when an EEPROM is not present.
 **/
s32 igb_phy_init_script_igp3(काष्ठा e1000_hw *hw)
अणु
	hw_dbg("Running IGP 3 PHY init script\n");

	/* PHY init IGP 3 */
	/* Enable rise/fall, 10-mode work in class-A */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2F5B, 0x9018);
	/* Remove all caps from Replica path filter */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2F52, 0x0000);
	/* Bias trimming क्रम ADC, AFE and Driver (Default) */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2FB1, 0x8B24);
	/* Increase Hybrid poly bias */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2FB2, 0xF8F0);
	/* Add 4% to TX amplitude in Giga mode */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2010, 0x10B0);
	/* Disable trimming (TTT) */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2011, 0x0000);
	/* Poly DC correction to 94.6% + 2% क्रम all channels */
	hw->phy.ops.ग_लिखो_reg(hw, 0x20DD, 0x249A);
	/* ABS DC correction to 95.9% */
	hw->phy.ops.ग_लिखो_reg(hw, 0x20DE, 0x00D3);
	/* BG temp curve trim */
	hw->phy.ops.ग_लिखो_reg(hw, 0x28B4, 0x04CE);
	/* Increasing ADC OPAMP stage 1 currents to max */
	hw->phy.ops.ग_लिखो_reg(hw, 0x2F70, 0x29E4);
	/* Force 1000 ( required क्रम enabling PHY regs configuration) */
	hw->phy.ops.ग_लिखो_reg(hw, 0x0000, 0x0140);
	/* Set upd_freq to 6 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F30, 0x1606);
	/* Disable NPDFE */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F31, 0xB814);
	/* Disable adaptive fixed FFE (Default) */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F35, 0x002A);
	/* Enable FFE hysteresis */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F3E, 0x0067);
	/* Fixed FFE क्रम लघु cable lengths */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F54, 0x0065);
	/* Fixed FFE क्रम medium cable lengths */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F55, 0x002A);
	/* Fixed FFE क्रम दीर्घ cable lengths */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F56, 0x002A);
	/* Enable Adaptive Clip Threshold */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F72, 0x3FB0);
	/* AHT reset limit to 1 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F76, 0xC0FF);
	/* Set AHT master delay to 127 msec */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F77, 0x1DEC);
	/* Set scan bits क्रम AHT */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F78, 0xF9EF);
	/* Set AHT Preset bits */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1F79, 0x0210);
	/* Change पूर्णांकeg_factor of channel A to 3 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1895, 0x0003);
	/* Change prop_factor of channels BCD to 8 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1796, 0x0008);
	/* Change cg_icount + enable पूर्णांकegbp क्रम channels BCD */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1798, 0xD008);
	/* Change cg_icount + enable पूर्णांकegbp + change prop_factor_master
	 * to 8 क्रम channel A
	 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x1898, 0xD918);
	/* Disable AHT in Slave mode on channel A */
	hw->phy.ops.ग_लिखो_reg(hw, 0x187A, 0x0800);
	/* Enable LPLU and disable AN to 1000 in non-D0a states,
	 * Enable SPD+B2B
	 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x0019, 0x008D);
	/* Enable restart AN on an1000_dis change */
	hw->phy.ops.ग_लिखो_reg(hw, 0x001B, 0x2080);
	/* Enable wh_fअगरo पढ़ो घड़ी in 10/100 modes */
	hw->phy.ops.ग_लिखो_reg(hw, 0x0014, 0x0045);
	/* Restart AN, Speed selection is 1000 */
	hw->phy.ops.ग_लिखो_reg(hw, 0x0000, 0x1340);

	वापस 0;
पूर्ण

/**
 *  igb_initialize_M88E1512_phy - Initialize M88E1512 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize Marvel 1512 to work correctly with Avoton.
 **/
s32 igb_initialize_M88E1512_phy(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;

	/* Switch to PHY page 0xFF. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x00FF);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0x214B);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2144);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0x0C28);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2146);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0xB233);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x214D);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0xCC0C);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2159);
	अगर (ret_val)
		जाओ out;

	/* Switch to PHY page 0xFB. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x00FB);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_3, 0x000D);
	अगर (ret_val)
		जाओ out;

	/* Switch to PHY page 0x12. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x12);
	अगर (ret_val)
		जाओ out;

	/* Change mode to SGMII-to-Copper */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_MODE, 0x8001);
	अगर (ret_val)
		जाओ out;

	/* Return the PHY to page 0. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error committing the PHY changes\n");
		वापस ret_val;
	पूर्ण

	/* msec_delay(1000); */
	usleep_range(1000, 2000);
out:
	वापस ret_val;
पूर्ण

/**
 *  igb_initialize_M88E1543_phy - Initialize M88E1512 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initialize Marvell 1543 to work correctly with Avoton.
 **/
s32 igb_initialize_M88E1543_phy(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;

	/* Switch to PHY page 0xFF. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x00FF);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0x214B);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2144);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0x0C28);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2146);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0xB233);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x214D);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_2, 0xDC0C);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_1, 0x2159);
	अगर (ret_val)
		जाओ out;

	/* Switch to PHY page 0xFB. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x00FB);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_CFG_REG_3, 0x0C0D);
	अगर (ret_val)
		जाओ out;

	/* Switch to PHY page 0x12. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x12);
	अगर (ret_val)
		जाओ out;

	/* Change mode to SGMII-to-Copper */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1512_MODE, 0x8001);
	अगर (ret_val)
		जाओ out;

	/* Switch to PHY page 1. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0x1);
	अगर (ret_val)
		जाओ out;

	/* Change mode to 1000BASE-X/SGMII and स्वतःneg enable */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_FIBER_CTRL, 0x9140);
	अगर (ret_val)
		जाओ out;

	/* Return the PHY to page 0. */
	ret_val = phy->ops.ग_लिखो_reg(hw, E1000_M88E1543_PAGE_ADDR, 0);
	अगर (ret_val)
		जाओ out;

	ret_val = igb_phy_sw_reset(hw);
	अगर (ret_val) अणु
		hw_dbg("Error committing the PHY changes\n");
		वापस ret_val;
	पूर्ण

	/* msec_delay(1000); */
	usleep_range(1000, 2000);
out:
	वापस ret_val;
पूर्ण

/**
 * igb_घातer_up_phy_copper - Restore copper link in हाल of PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, restore the link to previous settings.
 **/
व्योम igb_घातer_up_phy_copper(काष्ठा e1000_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	hw->phy.ops.पढ़ो_reg(hw, PHY_CONTROL, &mii_reg);
	mii_reg &= ~MII_CR_POWER_DOWN;
	hw->phy.ops.ग_लिखो_reg(hw, PHY_CONTROL, mii_reg);
पूर्ण

/**
 * igb_घातer_करोwn_phy_copper - Power करोwn copper PHY
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Power करोwn PHY to save घातer when पूर्णांकerface is करोwn and wake on lan
 * is not enabled.
 **/
व्योम igb_घातer_करोwn_phy_copper(काष्ठा e1000_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	hw->phy.ops.पढ़ो_reg(hw, PHY_CONTROL, &mii_reg);
	mii_reg |= MII_CR_POWER_DOWN;
	hw->phy.ops.ग_लिखो_reg(hw, PHY_CONTROL, mii_reg);
	usleep_range(1000, 2000);
पूर्ण

/**
 *  igb_check_polarity_82580 - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY specअगरic status रेजिस्टर.
 **/
अटल s32 igb_check_polarity_82580(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;


	ret_val = phy->ops.पढ़ो_reg(hw, I82580_PHY_STATUS_2, &data);

	अगर (!ret_val)
		phy->cable_polarity = (data & I82580_PHY_STATUS2_REV_POLARITY)
				      ? e1000_rev_polarity_reversed
				      : e1000_rev_polarity_normal;

	वापस ret_val;
पूर्ण

/**
 *  igb_phy_क्रमce_speed_duplex_82580 - Force speed/duplex क्रम I82580 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.  Clears the
 *  स्वतः-crossover to क्रमce MDI manually.  Waits क्रम link and वापसs
 *  successful अगर link up is successful, अन्यथा -E1000_ERR_PHY (-2).
 **/
s32 igb_phy_क्रमce_speed_duplex_82580(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	ret_val = phy->ops.पढ़ो_reg(hw, PHY_CONTROL, &phy_data);
	अगर (ret_val)
		जाओ out;

	igb_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = phy->ops.ग_लिखो_reg(hw, PHY_CONTROL, phy_data);
	अगर (ret_val)
		जाओ out;

	/* Clear Auto-Crossover to क्रमce MDI manually.  82580 requires MDI
	 * क्रमced whenever speed and duplex are क्रमced.
	 */
	ret_val = phy->ops.पढ़ो_reg(hw, I82580_PHY_CTRL_2, &phy_data);
	अगर (ret_val)
		जाओ out;

	phy_data &= ~I82580_PHY_CTRL2_MDIX_CFG_MASK;

	ret_val = phy->ops.ग_लिखो_reg(hw, I82580_PHY_CTRL_2, phy_data);
	अगर (ret_val)
		जाओ out;

	hw_dbg("I82580_PHY_CTRL_2: %X\n", phy_data);

	udelay(1);

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		hw_dbg("Waiting for forced speed/duplex link on 82580 phy\n");

		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 100000, &link);
		अगर (ret_val)
			जाओ out;

		अगर (!link)
			hw_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 100000, &link);
		अगर (ret_val)
			जाओ out;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_phy_info_82580 - Retrieve I82580 PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read PHY status to determine अगर link is up.  If link is up, then
 *  set/determine 10base-T extended distance and polarity correction.  Read
 *  PHY port status to determine MDI/MDIx and speed.  Based on the speed,
 *  determine on the cable length, local and remote receiver.
 **/
s32 igb_get_phy_info_82580(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = igb_phy_has_link(hw, 1, 0, &link);
	अगर (ret_val)
		जाओ out;

	अगर (!link) अणु
		hw_dbg("Phy info is only valid if link is up\n");
		ret_val = -E1000_ERR_CONFIG;
		जाओ out;
	पूर्ण

	phy->polarity_correction = true;

	ret_val = igb_check_polarity_82580(hw);
	अगर (ret_val)
		जाओ out;

	ret_val = phy->ops.पढ़ो_reg(hw, I82580_PHY_STATUS_2, &data);
	अगर (ret_val)
		जाओ out;

	phy->is_mdix = (data & I82580_PHY_STATUS2_MDIX) ? true : false;

	अगर ((data & I82580_PHY_STATUS2_SPEED_MASK) ==
	    I82580_PHY_STATUS2_SPEED_1000MBPS) अणु
		ret_val = hw->phy.ops.get_cable_length(hw);
		अगर (ret_val)
			जाओ out;

		ret_val = phy->ops.पढ़ो_reg(hw, PHY_1000T_STATUS, &data);
		अगर (ret_val)
			जाओ out;

		phy->local_rx = (data & SR_1000T_LOCAL_RX_STATUS)
				? e1000_1000t_rx_status_ok
				: e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & SR_1000T_REMOTE_RX_STATUS)
				 ? e1000_1000t_rx_status_ok
				 : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_get_cable_length_82580 - Determine cable length क्रम 82580 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Reads the diagnostic status रेजिस्टर and verअगरies result is valid beक्रमe
 * placing it in the phy_cable_length field.
 **/
s32 igb_get_cable_length_82580(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, length;

	ret_val = phy->ops.पढ़ो_reg(hw, I82580_PHY_DIAG_STATUS, &phy_data);
	अगर (ret_val)
		जाओ out;

	length = (phy_data & I82580_DSTATUS_CABLE_LENGTH) >>
		 I82580_DSTATUS_CABLE_LENGTH_SHIFT;

	अगर (length == E1000_CABLE_LENGTH_UNDEFINED)
		ret_val = -E1000_ERR_PHY;

	phy->cable_length = length;

out:
	वापस ret_val;
पूर्ण

/**
 *  igb_set_master_slave_mode - Setup PHY क्रम Master/slave mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up Master/slave mode
 **/
अटल s32 igb_set_master_slave_mode(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	/* Resolve Master/Slave mode */
	ret_val = hw->phy.ops.पढ़ो_reg(hw, PHY_1000T_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* load शेषs क्रम future use */
	hw->phy.original_ms_type = (phy_data & CR_1000T_MS_ENABLE) ?
				   ((phy_data & CR_1000T_MS_VALUE) ?
				    e1000_ms_क्रमce_master :
				    e1000_ms_क्रमce_slave) : e1000_ms_स्वतः;

	चयन (hw->phy.ms_type) अणु
	हाल e1000_ms_क्रमce_master:
		phy_data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
		अवरोध;
	हाल e1000_ms_क्रमce_slave:
		phy_data |= CR_1000T_MS_ENABLE;
		phy_data &= ~(CR_1000T_MS_VALUE);
		अवरोध;
	हाल e1000_ms_स्वतः:
		phy_data &= ~CR_1000T_MS_ENABLE;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	वापस hw->phy.ops.ग_लिखो_reg(hw, PHY_1000T_CTRL, phy_data);
पूर्ण

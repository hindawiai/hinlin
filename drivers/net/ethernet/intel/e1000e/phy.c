<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "e1000.h"

अटल s32 e1000_रुको_स्वतःneg(काष्ठा e1000_hw *hw);
अटल s32 e1000_access_phy_wakeup_reg_bm(काष्ठा e1000_hw *hw, u32 offset,
					  u16 *data, bool पढ़ो, bool page_set);
अटल u32 e1000_get_phy_addr_क्रम_hv_page(u32 page);
अटल s32 e1000_access_phy_debug_regs_hv(काष्ठा e1000_hw *hw, u32 offset,
					  u16 *data, bool पढ़ो);

/* Cable length tables */
अटल स्थिर u16 e1000_m88_cable_length_table[] = अणु
	0, 50, 80, 110, 140, 140, E1000_CABLE_LENGTH_UNDEFINED
पूर्ण;

#घोषणा M88E1000_CABLE_LENGTH_TABLE_SIZE \
		ARRAY_SIZE(e1000_m88_cable_length_table)

अटल स्थिर u16 e1000_igp_2_cable_length_table[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 8, 11, 13, 16, 18, 21, 0, 0, 0, 3,
	6, 10, 13, 16, 19, 23, 26, 29, 32, 35, 38, 41, 6, 10, 14, 18, 22,
	26, 30, 33, 37, 41, 44, 48, 51, 54, 58, 61, 21, 26, 31, 35, 40,
	44, 49, 53, 57, 61, 65, 68, 72, 75, 79, 82, 40, 45, 51, 56, 61,
	66, 70, 75, 79, 83, 87, 91, 94, 98, 101, 104, 60, 66, 72, 77, 82,
	87, 92, 96, 100, 104, 108, 111, 114, 117, 119, 121, 83, 89, 95,
	100, 105, 109, 113, 116, 119, 122, 124, 104, 109, 114, 118, 121,
	124
पूर्ण;

#घोषणा IGP02E1000_CABLE_LENGTH_TABLE_SIZE \
		ARRAY_SIZE(e1000_igp_2_cable_length_table)

/**
 *  e1000e_check_reset_block_generic - Check अगर PHY reset is blocked
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read the PHY management control रेजिस्टर and check whether a PHY reset
 *  is blocked.  If a reset is not blocked वापस 0, otherwise
 *  वापस E1000_BLK_PHY_RESET (12).
 **/
s32 e1000e_check_reset_block_generic(काष्ठा e1000_hw *hw)
अणु
	u32 manc;

	manc = er32(MANC);

	वापस (manc & E1000_MANC_BLK_PHY_RST_ON_IDE) ? E1000_BLK_PHY_RESET : 0;
पूर्ण

/**
 *  e1000e_get_phy_id - Retrieve the PHY ID and revision
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the PHY रेजिस्टरs and stores the PHY ID and possibly the PHY
 *  revision in the hardware काष्ठाure.
 **/
s32 e1000e_get_phy_id(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 phy_id;
	u16 retry_count = 0;

	अगर (!phy->ops.पढ़ो_reg)
		वापस 0;

	जबतक (retry_count < 2) अणु
		ret_val = e1e_rphy(hw, MII_PHYSID1, &phy_id);
		अगर (ret_val)
			वापस ret_val;

		phy->id = (u32)(phy_id << 16);
		usleep_range(20, 40);
		ret_val = e1e_rphy(hw, MII_PHYSID2, &phy_id);
		अगर (ret_val)
			वापस ret_val;

		phy->id |= (u32)(phy_id & PHY_REVISION_MASK);
		phy->revision = (u32)(phy_id & ~PHY_REVISION_MASK);

		अगर (phy->id != 0 && phy->id != PHY_REVISION_MASK)
			वापस 0;

		retry_count++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_phy_reset_dsp - Reset PHY DSP
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reset the digital संकेत processor.
 **/
s32 e1000e_phy_reset_dsp(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;

	ret_val = e1e_wphy(hw, M88E1000_PHY_GEN_CONTROL, 0xC1);
	अगर (ret_val)
		वापस ret_val;

	वापस e1e_wphy(hw, M88E1000_PHY_GEN_CONTROL, 0);
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_mdic - Read MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the MDI control रेजिस्टर in the PHY at offset and stores the
 *  inक्रमmation पढ़ो to data.
 **/
s32 e1000e_पढ़ो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		e_dbg("PHY Address %d is out of range\n", offset);
		वापस -E1000_ERR_PARAM;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = ((offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_READ));

	ew32(MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) अणु
		udelay(50);
		mdic = er32(MDIC);
		अगर (mdic & E1000_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & E1000_MDIC_READY)) अणु
		e_dbg("MDI Read did not complete\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (mdic & E1000_MDIC_ERROR) अणु
		e_dbg("MDI Error\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (((mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT) != offset) अणु
		e_dbg("MDI Read offset error - requested %d, returned %d\n",
		      offset,
		      (mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT);
		वापस -E1000_ERR_PHY;
	पूर्ण
	*data = (u16)mdic;

	/* Allow some समय after each MDIC transaction to aव्योम
	 * पढ़ोing duplicate data in the next MDIC transaction.
	 */
	अगर (hw->mac.type == e1000_pch2lan)
		udelay(100);

	वापस 0;
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_mdic - Write MDI control रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो to रेजिस्टर at offset
 *
 *  Writes data to MDI control रेजिस्टर in the PHY at offset.
 **/
s32 e1000e_ग_लिखो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	u32 i, mdic = 0;

	अगर (offset > MAX_PHY_REG_ADDRESS) अणु
		e_dbg("PHY Address %d is out of range\n", offset);
		वापस -E1000_ERR_PARAM;
	पूर्ण

	/* Set up Op-code, Phy Address, and रेजिस्टर offset in the MDI
	 * Control रेजिस्टर.  The MAC will take care of पूर्णांकerfacing with the
	 * PHY to retrieve the desired data.
	 */
	mdic = (((u32)data) |
		(offset << E1000_MDIC_REG_SHIFT) |
		(phy->addr << E1000_MDIC_PHY_SHIFT) |
		(E1000_MDIC_OP_WRITE));

	ew32(MDIC, mdic);

	/* Poll the पढ़ोy bit to see अगर the MDI पढ़ो completed
	 * Increasing the समय out as testing showed failures with
	 * the lower समय out
	 */
	क्रम (i = 0; i < (E1000_GEN_POLL_TIMEOUT * 3); i++) अणु
		udelay(50);
		mdic = er32(MDIC);
		अगर (mdic & E1000_MDIC_READY)
			अवरोध;
	पूर्ण
	अगर (!(mdic & E1000_MDIC_READY)) अणु
		e_dbg("MDI Write did not complete\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (mdic & E1000_MDIC_ERROR) अणु
		e_dbg("MDI Error\n");
		वापस -E1000_ERR_PHY;
	पूर्ण
	अगर (((mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT) != offset) अणु
		e_dbg("MDI Write offset error - requested %d, returned %d\n",
		      offset,
		      (mdic & E1000_MDIC_REG_MASK) >> E1000_MDIC_REG_SHIFT);
		वापस -E1000_ERR_PHY;
	पूर्ण

	/* Allow some समय after each MDIC transaction to aव्योम
	 * पढ़ोing duplicate data in the next MDIC transaction.
	 */
	अगर (hw->mac.type == e1000_pch2lan)
		udelay(100);

	वापस 0;
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_m88 - Read m88 PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and storing the retrieved inक्रमmation in data.  Release any acquired
 *  semaphores beक्रमe निकासing.
 **/
s32 e1000e_पढ़ो_phy_reg_m88(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	s32 ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					   data);

	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_m88 - Write m88 PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
s32 e1000e_ग_लिखो_phy_reg_m88(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	s32 ret_val;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					    data);

	hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_set_page_igp - Set page as on IGP-like PHY(s)
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @page: page to set (shअगरted left when necessary)
 *
 *  Sets PHY page required क्रम PHY रेजिस्टर access.  Assumes semaphore is
 *  alपढ़ोy acquired.  Note, this function sets phy.addr to 1 so the caller
 *  must set it appropriately (अगर necessary) after this function वापसs.
 **/
s32 e1000_set_page_igp(काष्ठा e1000_hw *hw, u16 page)
अणु
	e_dbg("Setting page 0x%x\n", page);

	hw->phy.addr = 1;

	वापस e1000e_ग_लिखो_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT, page);
पूर्ण

/**
 *  __e1000e_पढ़ो_phy_reg_igp - Read igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and stores the retrieved inक्रमmation in data.  Release any acquired
 *  semaphores beक्रमe निकासing.
 **/
अटल s32 __e1000e_पढ़ो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 *data,
				     bool locked)
अणु
	s32 ret_val = 0;

	अगर (!locked) अणु
		अगर (!hw->phy.ops.acquire)
			वापस 0;

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (offset > MAX_PHY_MULTI_PAGE_REG)
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw,
						    IGP01E1000_PHY_PAGE_SELECT,
						    (u16)offset);
	अगर (!ret_val)
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw,
						   MAX_PHY_REG_ADDRESS & offset,
						   data);
	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_igp - Read igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore then पढ़ोs the PHY रेजिस्टर at offset and stores the
 *  retrieved inक्रमmation in data.
 *  Release the acquired semaphore beक्रमe निकासing.
 **/
s32 e1000e_पढ़ो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000e_पढ़ो_phy_reg_igp(hw, offset, data, false);
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_igp_locked - Read igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the PHY रेजिस्टर at offset and stores the retrieved inक्रमmation
 *  in data.  Assumes semaphore alपढ़ोy acquired.
 **/
s32 e1000e_पढ़ो_phy_reg_igp_locked(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000e_पढ़ो_phy_reg_igp(hw, offset, data, true);
पूर्ण

/**
 *  __e1000e_ग_लिखो_phy_reg_igp - Write igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
अटल s32 __e1000e_ग_लिखो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 data,
				      bool locked)
अणु
	s32 ret_val = 0;

	अगर (!locked) अणु
		अगर (!hw->phy.ops.acquire)
			वापस 0;

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (offset > MAX_PHY_MULTI_PAGE_REG)
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw,
						    IGP01E1000_PHY_PAGE_SELECT,
						    (u16)offset);
	अगर (!ret_val)
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS &
						    offset, data);
	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_igp - Write igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
s32 e1000e_ग_लिखो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000e_ग_लिखो_phy_reg_igp(hw, offset, data, false);
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_igp_locked - Write igp PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes the data to PHY रेजिस्टर at the offset.
 *  Assumes semaphore alपढ़ोy acquired.
 **/
s32 e1000e_ग_लिखो_phy_reg_igp_locked(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000e_ग_लिखो_phy_reg_igp(hw, offset, data, true);
पूर्ण

/**
 *  __e1000_पढ़ो_kmrn_reg - Read kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *
 *  Acquires semaphore, अगर necessary.  Then पढ़ोs the PHY रेजिस्टर at offset
 *  using the kumeran पूर्णांकerface.  The inक्रमmation retrieved is stored in data.
 *  Release any acquired semaphores beक्रमe निकासing.
 **/
अटल s32 __e1000_पढ़ो_kmrn_reg(काष्ठा e1000_hw *hw, u32 offset, u16 *data,
				 bool locked)
अणु
	u32 kmrnctrlsta;

	अगर (!locked) अणु
		s32 ret_val = 0;

		अगर (!hw->phy.ops.acquire)
			वापस 0;

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | E1000_KMRNCTRLSTA_REN;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	kmrnctrlsta = er32(KMRNCTRLSTA);
	*data = (u16)kmrnctrlsta;

	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस 0;
पूर्ण

/**
 *  e1000e_पढ़ो_kmrn_reg -  Read kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore then पढ़ोs the PHY रेजिस्टर at offset using the
 *  kumeran पूर्णांकerface.  The inक्रमmation retrieved is stored in data.
 *  Release the acquired semaphore beक्रमe निकासing.
 **/
s32 e1000e_पढ़ो_kmrn_reg(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000_पढ़ो_kmrn_reg(hw, offset, data, false);
पूर्ण

/**
 *  e1000e_पढ़ो_kmrn_reg_locked -  Read kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the PHY रेजिस्टर at offset using the kumeran पूर्णांकerface.  The
 *  inक्रमmation retrieved is stored in data.
 *  Assumes semaphore alपढ़ोy acquired.
 **/
s32 e1000e_पढ़ो_kmrn_reg_locked(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000_पढ़ो_kmrn_reg(hw, offset, data, true);
पूर्ण

/**
 *  __e1000_ग_लिखो_kmrn_reg - Write kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *
 *  Acquires semaphore, अगर necessary.  Then ग_लिखो the data to PHY रेजिस्टर
 *  at the offset using the kumeran पूर्णांकerface.  Release any acquired semaphores
 *  beक्रमe निकासing.
 **/
अटल s32 __e1000_ग_लिखो_kmrn_reg(काष्ठा e1000_hw *hw, u32 offset, u16 data,
				  bool locked)
अणु
	u32 kmrnctrlsta;

	अगर (!locked) अणु
		s32 ret_val = 0;

		अगर (!hw->phy.ops.acquire)
			वापस 0;

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | data;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस 0;
पूर्ण

/**
 *  e1000e_ग_लिखो_kmrn_reg -  Write kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore then ग_लिखोs the data to the PHY रेजिस्टर at the offset
 *  using the kumeran पूर्णांकerface.  Release the acquired semaphore beक्रमe निकासing.
 **/
s32 e1000e_ग_लिखो_kmrn_reg(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000_ग_लिखो_kmrn_reg(hw, offset, data, false);
पूर्ण

/**
 *  e1000e_ग_लिखो_kmrn_reg_locked -  Write kumeran रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Write the data to PHY रेजिस्टर at the offset using the kumeran पूर्णांकerface.
 *  Assumes semaphore alपढ़ोy acquired.
 **/
s32 e1000e_ग_लिखो_kmrn_reg_locked(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000_ग_लिखो_kmrn_reg(hw, offset, data, true);
पूर्ण

/**
 *  e1000_set_master_slave_mode - Setup PHY क्रम Master/slave mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up Master/slave mode
 **/
अटल s32 e1000_set_master_slave_mode(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	/* Resolve Master/Slave mode */
	ret_val = e1e_rphy(hw, MII_CTRL1000, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* load शेषs क्रम future use */
	hw->phy.original_ms_type = (phy_data & CTL1000_ENABLE_MASTER) ?
	    ((phy_data & CTL1000_AS_MASTER) ?
	     e1000_ms_क्रमce_master : e1000_ms_क्रमce_slave) : e1000_ms_स्वतः;

	चयन (hw->phy.ms_type) अणु
	हाल e1000_ms_क्रमce_master:
		phy_data |= (CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER);
		अवरोध;
	हाल e1000_ms_क्रमce_slave:
		phy_data |= CTL1000_ENABLE_MASTER;
		phy_data &= ~(CTL1000_AS_MASTER);
		अवरोध;
	हाल e1000_ms_स्वतः:
		phy_data &= ~CTL1000_ENABLE_MASTER;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	वापस e1e_wphy(hw, MII_CTRL1000, phy_data);
पूर्ण

/**
 *  e1000_copper_link_setup_82577 - Setup 82577 PHY क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up Carrier-sense on Transmit and करोwnshअगरt values.
 **/
s32 e1000_copper_link_setup_82577(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_data;

	/* Enable CRS on Tx. This must be set क्रम half-duplex operation. */
	ret_val = e1e_rphy(hw, I82577_CFG_REG, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data |= I82577_CFG_ASSERT_CRS_ON_TX;

	/* Enable करोwnshअगरt */
	phy_data |= I82577_CFG_ENABLE_DOWNSHIFT;

	ret_val = e1e_wphy(hw, I82577_CFG_REG, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Set MDI/MDIX mode */
	ret_val = e1e_rphy(hw, I82577_PHY_CTRL_2, &phy_data);
	अगर (ret_val)
		वापस ret_val;
	phy_data &= ~I82577_PHY_CTRL2_MDIX_CFG_MASK;
	/* Options:
	 *   0 - Auto (शेष)
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 */
	चयन (hw->phy.mdix) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		phy_data |= I82577_PHY_CTRL2_MANUAL_MDIX;
		अवरोध;
	हाल 0:
	शेष:
		phy_data |= I82577_PHY_CTRL2_AUTO_MDI_MDIX;
		अवरोध;
	पूर्ण
	ret_val = e1e_wphy(hw, I82577_PHY_CTRL_2, phy_data);
	अगर (ret_val)
		वापस ret_val;

	वापस e1000_set_master_slave_mode(hw);
पूर्ण

/**
 *  e1000e_copper_link_setup_m88 - Setup m88 PHY's क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up MDI/MDI-X and polarity क्रम m88 PHY's.  If necessary, transmit घड़ी
 *  and करोwnshअगरt values are set also.
 **/
s32 e1000e_copper_link_setup_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;

	/* Enable CRS on Tx. This must be set क्रम half-duplex operation. */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* For BM PHY this bit is करोwnshअगरt enable */
	अगर (phy->type != e1000_phy_bm)
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
	अगर (phy->disable_polarity_correction)
		phy_data |= M88E1000_PSCR_POLARITY_REVERSAL;

	/* Enable करोwnshअगरt on BM (disabled by शेष) */
	अगर (phy->type == e1000_phy_bm) अणु
		/* For 82574/82583, first disable then enable करोwnshअगरt */
		अगर (phy->id == BME1000_E_PHY_ID_R2) अणु
			phy_data &= ~BME1000_PSCR_ENABLE_DOWNSHIFT;
			ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL,
					   phy_data);
			अगर (ret_val)
				वापस ret_val;
			/* Commit the changes. */
			ret_val = phy->ops.commit(hw);
			अगर (ret_val) अणु
				e_dbg("Error committing the PHY changes\n");
				वापस ret_val;
			पूर्ण
		पूर्ण

		phy_data |= BME1000_PSCR_ENABLE_DOWNSHIFT;
	पूर्ण

	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर ((phy->type == e1000_phy_m88) &&
	    (phy->revision < E1000_REVISION_4) &&
	    (phy->id != BME1000_E_PHY_ID_R2)) अणु
		/* Force TX_CLK in the Extended PHY Specअगरic Control Register
		 * to 25MHz घड़ी.
		 */
		ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;

		अगर ((phy->revision == 2) && (phy->id == M88E1111_I_PHY_ID)) अणु
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
		ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर ((phy->type == e1000_phy_bm) && (phy->id == BME1000_E_PHY_ID_R2)) अणु
		/* Set PHY page 0, रेजिस्टर 29 to 0x0003 */
		ret_val = e1e_wphy(hw, 29, 0x0003);
		अगर (ret_val)
			वापस ret_val;

		/* Set PHY page 0, रेजिस्टर 30 to 0x0000 */
		ret_val = e1e_wphy(hw, 30, 0x0000);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Commit the changes. */
	अगर (phy->ops.commit) अणु
		ret_val = phy->ops.commit(hw);
		अगर (ret_val) अणु
			e_dbg("Error committing the PHY changes\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	अगर (phy->type == e1000_phy_82578) अणु
		ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* 82578 PHY - set the करोwnshअगरt count to 1x. */
		phy_data |= I82578_EPSCR_DOWNSHIFT_ENABLE;
		phy_data &= ~I82578_EPSCR_DOWNSHIFT_COUNTER_MASK;
		ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_copper_link_setup_igp - Setup igp PHY's क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Sets up LPLU, MDI/MDI-X, polarity, Smartspeed and Master/Slave config क्रम
 *  igp PHY's.
 **/
s32 e1000e_copper_link_setup_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1000_phy_hw_reset(hw);
	अगर (ret_val) अणु
		e_dbg("Error resetting the PHY.\n");
		वापस ret_val;
	पूर्ण

	/* Wait 100ms क्रम MAC to configure PHY from NVM settings, to aव्योम
	 * समयout issues when LFS is enabled.
	 */
	msleep(100);

	/* disable lplu d0 during driver init */
	अगर (hw->phy.ops.set_d0_lplu_state) अणु
		ret_val = hw->phy.ops.set_d0_lplu_state(hw, false);
		अगर (ret_val) अणु
			e_dbg("Error Disabling LPLU D0\n");
			वापस ret_val;
		पूर्ण
	पूर्ण
	/* Configure mdi-mdix settings */
	ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CTRL, &data);
	अगर (ret_val)
		वापस ret_val;

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
	ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CTRL, data);
	अगर (ret_val)
		वापस ret_val;

	/* set स्वतः-master slave resolution settings */
	अगर (hw->mac.स्वतःneg) अणु
		/* when स्वतःnegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware शेष.
		 */
		अगर (phy->स्वतःneg_advertised == ADVERTISE_1000_FULL) अणु
			/* Disable SmartSpeed */
			ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   &data);
			अगर (ret_val)
				वापस ret_val;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CONFIG,
					   data);
			अगर (ret_val)
				वापस ret_val;

			/* Set स्वतः Master/Slave resolution process */
			ret_val = e1e_rphy(hw, MII_CTRL1000, &data);
			अगर (ret_val)
				वापस ret_val;

			data &= ~CTL1000_ENABLE_MASTER;
			ret_val = e1e_wphy(hw, MII_CTRL1000, data);
			अगर (ret_val)
				वापस ret_val;
		पूर्ण

		ret_val = e1000_set_master_slave_mode(hw);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_phy_setup_स्वतःneg - Configure PHY क्रम स्वतः-negotiation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the MII स्वतः-neg advertisement रेजिस्टर and/or the 1000T control
 *  रेजिस्टर and अगर the PHY is alपढ़ोy setup क्रम स्वतः-negotiation, then
 *  वापस successful.  Otherwise, setup advertisement and flow control to
 *  the appropriate values क्रम the wanted स्वतः-negotiation.
 **/
अटल s32 e1000_phy_setup_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg = 0;

	phy->स्वतःneg_advertised &= phy->स्वतःneg_mask;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = e1e_rphy(hw, MII_ADVERTISE, &mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL) अणु
		/* Read the MII 1000Base-T Control Register (Address 9). */
		ret_val = e1e_rphy(hw, MII_CTRL1000, &mii_1000t_ctrl_reg);
		अगर (ret_val)
			वापस ret_val;
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
	mii_स्वतःneg_adv_reg &= ~(ADVERTISE_100FULL |
				 ADVERTISE_100HALF |
				 ADVERTISE_10FULL | ADVERTISE_10HALF);
	mii_1000t_ctrl_reg &= ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);

	e_dbg("autoneg_advertised %x\n", phy->स्वतःneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_HALF) अणु
		e_dbg("Advertise 10mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= ADVERTISE_10HALF;
	पूर्ण

	/* Do we want to advertise 10 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_10_FULL) अणु
		e_dbg("Advertise 10mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= ADVERTISE_10FULL;
	पूर्ण

	/* Do we want to advertise 100 Mb Half Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_HALF) अणु
		e_dbg("Advertise 100mb Half duplex\n");
		mii_स्वतःneg_adv_reg |= ADVERTISE_100HALF;
	पूर्ण

	/* Do we want to advertise 100 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_100_FULL) अणु
		e_dbg("Advertise 100mb Full duplex\n");
		mii_स्वतःneg_adv_reg |= ADVERTISE_100FULL;
	पूर्ण

	/* We करो not allow the Phy to advertise 1000 Mb Half Duplex */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_HALF)
		e_dbg("Advertise 1000mb Half duplex request denied!\n");

	/* Do we want to advertise 1000 Mb Full Duplex? */
	अगर (phy->स्वतःneg_advertised & ADVERTISE_1000_FULL) अणु
		e_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= ADVERTISE_1000FULL;
	पूर्ण

	/* Check क्रम a software override of the flow control settings, and
	 * setup the PHY advertisement रेजिस्टरs accordingly.  If
	 * स्वतः-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (MII_ADVERTISE) and re-start स्वतः-
	 * negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive छोड़ो frames
	 *          but not send छोड़ो frames).
	 *      2:  Tx flow control is enabled (we can send छोड़ो frames
	 *          but we करो not support receiving छोड़ो frames).
	 *      3:  Both Rx and Tx flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	चयन (hw->fc.current_mode) अणु
	हाल e1000_fc_none:
		/* Flow control (Rx & Tx) is completely disabled by a
		 * software over-ride.
		 */
		mii_स्वतःneg_adv_reg &=
		    ~(ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		अवरोध;
	हाल e1000_fc_rx_छोड़ो:
		/* Rx Flow control is enabled, and Tx Flow control is
		 * disabled, by a software over-ride.
		 *
		 * Since there really isn't a way to advertise that we are
		 * capable of Rx Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric Rx PAUSE.  Later
		 * (in e1000e_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_स्वतःneg_adv_reg |=
		    (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		अवरोध;
	हाल e1000_fc_tx_छोड़ो:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_स्वतःneg_adv_reg |= ADVERTISE_PAUSE_ASYM;
		mii_स्वतःneg_adv_reg &= ~ADVERTISE_PAUSE_CAP;
		अवरोध;
	हाल e1000_fc_full:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		mii_स्वतःneg_adv_reg |=
		    (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		अवरोध;
	शेष:
		e_dbg("Flow control param set incorrectly\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1e_wphy(hw, MII_ADVERTISE, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("Auto-Neg Advertising %x\n", mii_स्वतःneg_adv_reg);

	अगर (phy->स्वतःneg_mask & ADVERTISE_1000_FULL)
		ret_val = e1e_wphy(hw, MII_CTRL1000, mii_1000t_ctrl_reg);

	वापस ret_val;
पूर्ण

/**
 *  e1000_copper_link_स्वतःneg - Setup/Enable स्वतःneg क्रम copper link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Perक्रमms initial bounds checking on स्वतःneg advertisement parameter, then
 *  configure to advertise the full capability.  Setup the PHY to स्वतःneg
 *  and restart the negotiation process between the link partner.  If
 *  स्वतःneg_रुको_to_complete, then रुको क्रम स्वतःneg to complete beक्रमe निकासing.
 **/
अटल s32 e1000_copper_link_स्वतःneg(काष्ठा e1000_hw *hw)
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
	अगर (!phy->स्वतःneg_advertised)
		phy->स्वतःneg_advertised = phy->स्वतःneg_mask;

	e_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = e1000_phy_setup_स्वतःneg(hw);
	अगर (ret_val) अणु
		e_dbg("Error Setting up Auto-Negotiation\n");
		वापस ret_val;
	पूर्ण
	e_dbg("Restarting Auto-Neg\n");

	/* Restart स्वतः-negotiation by setting the Auto Neg Enable bit and
	 * the Auto Neg Restart bit in the PHY control रेजिस्टर.
	 */
	ret_val = e1e_rphy(hw, MII_BMCR, &phy_ctrl);
	अगर (ret_val)
		वापस ret_val;

	phy_ctrl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	ret_val = e1e_wphy(hw, MII_BMCR, phy_ctrl);
	अगर (ret_val)
		वापस ret_val;

	/* Does the user want to रुको क्रम Auto-Neg to complete here, or
	 * check at a later समय (क्रम example, callback routine).
	 */
	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		ret_val = e1000_रुको_स्वतःneg(hw);
		अगर (ret_val) अणु
			e_dbg("Error while waiting for autoneg to complete\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	hw->mac.get_link_status = true;

	वापस ret_val;
पूर्ण

/**
 *  e1000e_setup_copper_link - Configure copper link settings
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the appropriate function to configure the link क्रम स्वतः-neg or क्रमced
 *  speed and duplex.  Then we check क्रम link, once link is established calls
 *  to configure collision distance and flow control are called.  If link is
 *  not established, we वापस -E1000_ERR_PHY (-2).
 **/
s32 e1000e_setup_copper_link(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	bool link;

	अगर (hw->mac.स्वतःneg) अणु
		/* Setup स्वतःneg and flow control advertisement and perक्रमm
		 * स्वतःnegotiation.
		 */
		ret_val = e1000_copper_link_स्वतःneg(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		/* PHY will be set to 10H, 10F, 100H or 100F
		 * depending on user settings.
		 */
		e_dbg("Forcing Speed and Duplex\n");
		ret_val = hw->phy.ops.क्रमce_speed_duplex(hw);
		अगर (ret_val) अणु
			e_dbg("Error Forcing Speed and Duplex\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Check link status. Wait up to 100 microseconds क्रम link to become
	 * valid.
	 */
	ret_val = e1000e_phy_has_link_generic(hw, COPPER_LINK_UP_LIMIT, 10,
					      &link);
	अगर (ret_val)
		वापस ret_val;

	अगर (link) अणु
		e_dbg("Valid link established!!!\n");
		hw->mac.ops.config_collision_dist(hw);
		ret_val = e1000e_config_fc_after_link_up(hw);
	पूर्ण अन्यथा अणु
		e_dbg("Unable to establish link!!!\n");
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_phy_क्रमce_speed_duplex_igp - Force speed/duplex क्रम igp PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.  Clears the
 *  स्वतः-crossover to क्रमce MDI manually.  Waits क्रम link and वापसs
 *  successful अगर link up is successful, अन्यथा -E1000_ERR_PHY (-2).
 **/
s32 e1000e_phy_क्रमce_speed_duplex_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	e1000e_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = e1e_wphy(hw, MII_BMCR, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Clear Auto-Crossover to क्रमce MDI manually.  IGP requires MDI
	 * क्रमced whenever speed and duplex are क्रमced.
	 */
	ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;
	phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;

	ret_val = e1e_wphy(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("IGP PSCR: %X\n", phy_data);

	udelay(1);

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		e_dbg("Waiting for forced speed/duplex link on IGP phy.\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;

		अगर (!link)
			e_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_phy_क्रमce_speed_duplex_m88 - Force speed/duplex क्रम m88 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.  Clears the
 *  स्वतः-crossover to क्रमce MDI manually.  Resets the PHY to commit the
 *  changes.  If समय expires जबतक रुकोing क्रम link up, we reset the DSP.
 *  After reset, TX_CLK and CRS on Tx must be set.  Return successful upon
 *  successful completion, अन्यथा वापस corresponding error code.
 **/
s32 e1000e_phy_क्रमce_speed_duplex_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	/* Clear Auto-Crossover to क्रमce MDI manually.  M88E1000 requires MDI
	 * क्रमced whenever speed and duplex are क्रमced.
	 */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("M88E1000 PSCR: %X\n", phy_data);

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	e1000e_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = e1e_wphy(hw, MII_BMCR, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Reset the phy to commit changes. */
	अगर (hw->phy.ops.commit) अणु
		ret_val = hw->phy.ops.commit(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		e_dbg("Waiting for forced speed/duplex link on M88 phy.\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;

		अगर (!link) अणु
			अगर (hw->phy.type != e1000_phy_m88) अणु
				e_dbg("Link taking longer than expected.\n");
			पूर्ण अन्यथा अणु
				/* We didn't get link.
				 * Reset the DSP and cross our fingers.
				 */
				ret_val = e1e_wphy(hw, M88E1000_PHY_PAGE_SELECT,
						   0x001d);
				अगर (ret_val)
					वापस ret_val;
				ret_val = e1000e_phy_reset_dsp(hw);
				अगर (ret_val)
					वापस ret_val;
			पूर्ण
		पूर्ण

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	अगर (hw->phy.type != e1000_phy_m88)
		वापस 0;

	ret_val = e1e_rphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* Resetting the phy means we need to re-क्रमce TX_CLK in the
	 * Extended PHY Specअगरic Control Register to 25MHz घड़ी from
	 * the reset value of 2.5MHz.
	 */
	phy_data |= M88E1000_EPSCR_TX_CLK_25;
	ret_val = e1e_wphy(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
	अगर (ret_val)
		वापस ret_val;

	/* In addition, we must re-enable CRS on Tx क्रम both half and full
	 * duplex.
	 */
	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	ret_val = e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, phy_data);

	वापस ret_val;
पूर्ण

/**
 *  e1000_phy_क्रमce_speed_duplex_अगरe - Force PHY speed & duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Forces the speed and duplex settings of the PHY.
 *  This is a function poपूर्णांकer entry poपूर्णांक only called by
 *  PHY setup routines.
 **/
s32 e1000_phy_क्रमce_speed_duplex_अगरe(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = e1e_rphy(hw, MII_BMCR, &data);
	अगर (ret_val)
		वापस ret_val;

	e1000e_phy_क्रमce_speed_duplex_setup(hw, &data);

	ret_val = e1e_wphy(hw, MII_BMCR, data);
	अगर (ret_val)
		वापस ret_val;

	/* Disable MDI-X support क्रम 10/100 */
	ret_val = e1e_rphy(hw, IFE_PHY_MDIX_CONTROL, &data);
	अगर (ret_val)
		वापस ret_val;

	data &= ~IFE_PMC_AUTO_MDIX;
	data &= ~IFE_PMC_FORCE_MDIX;

	ret_val = e1e_wphy(hw, IFE_PHY_MDIX_CONTROL, data);
	अगर (ret_val)
		वापस ret_val;

	e_dbg("IFE PMC: %X\n", data);

	udelay(1);

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		e_dbg("Waiting for forced speed/duplex link on IFE phy.\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;

		अगर (!link)
			e_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_phy_क्रमce_speed_duplex_setup - Configure क्रमced PHY speed/duplex
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @phy_ctrl: poपूर्णांकer to current value of MII_BMCR
 *
 *  Forces speed and duplex on the PHY by करोing the following: disable flow
 *  control, क्रमce speed/duplex on the MAC, disable स्वतः speed detection,
 *  disable स्वतः-negotiation, configure duplex, configure speed, configure
 *  the collision distance, ग_लिखो configuration to CTRL रेजिस्टर.  The
 *  caller must ग_लिखो to the MII_BMCR रेजिस्टर क्रम these settings to
 *  take affect.
 **/
व्योम e1000e_phy_क्रमce_speed_duplex_setup(काष्ठा e1000_hw *hw, u16 *phy_ctrl)
अणु
	काष्ठा e1000_mac_info *mac = &hw->mac;
	u32 ctrl;

	/* Turn off flow control when क्रमcing speed/duplex */
	hw->fc.current_mode = e1000_fc_none;

	/* Force speed/duplex on the mac */
	ctrl = er32(CTRL);
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~E1000_CTRL_SPD_SEL;

	/* Disable Auto Speed Detection */
	ctrl &= ~E1000_CTRL_ASDE;

	/* Disable स्वतःneg on the phy */
	*phy_ctrl &= ~BMCR_ANENABLE;

	/* Forcing Full or Half Duplex? */
	अगर (mac->क्रमced_speed_duplex & E1000_ALL_HALF_DUPLEX) अणु
		ctrl &= ~E1000_CTRL_FD;
		*phy_ctrl &= ~BMCR_FULLDPLX;
		e_dbg("Half Duplex\n");
	पूर्ण अन्यथा अणु
		ctrl |= E1000_CTRL_FD;
		*phy_ctrl |= BMCR_FULLDPLX;
		e_dbg("Full Duplex\n");
	पूर्ण

	/* Forcing 10mb or 100mb? */
	अगर (mac->क्रमced_speed_duplex & E1000_ALL_100_SPEED) अणु
		ctrl |= E1000_CTRL_SPD_100;
		*phy_ctrl |= BMCR_SPEED100;
		*phy_ctrl &= ~BMCR_SPEED1000;
		e_dbg("Forcing 100mb\n");
	पूर्ण अन्यथा अणु
		ctrl &= ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
		*phy_ctrl &= ~(BMCR_SPEED1000 | BMCR_SPEED100);
		e_dbg("Forcing 10mb\n");
	पूर्ण

	hw->mac.ops.config_collision_dist(hw);

	ew32(CTRL, ctrl);
पूर्ण

/**
 *  e1000e_set_d3_lplu_state - Sets low घातer link up state क्रम D3
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
s32 e1000e_set_d3_lplu_state(काष्ठा e1000_hw *hw, bool active)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर (!active) अणु
		data &= ~IGP02E1000_PM_D3_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);
		अगर (ret_val)
			वापस ret_val;
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
		data |= IGP02E1000_PM_D3_LPLU;
		ret_val = e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, data);
		अगर (ret_val)
			वापस ret_val;

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
 *  e1000e_check_करोwnshअगरt - Checks whether a करोwnshअगरt in speed occurred
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs 1
 *
 *  A करोwnshअगरt is detected by querying the PHY link health.
 **/
s32 e1000e_check_करोwnshअगरt(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, offset, mask;

	चयन (phy->type) अणु
	हाल e1000_phy_m88:
	हाल e1000_phy_gg82563:
	हाल e1000_phy_bm:
	हाल e1000_phy_82578:
		offset = M88E1000_PHY_SPEC_STATUS;
		mask = M88E1000_PSSR_DOWNSHIFT;
		अवरोध;
	हाल e1000_phy_igp_2:
	हाल e1000_phy_igp_3:
		offset = IGP01E1000_PHY_LINK_HEALTH;
		mask = IGP01E1000_PLHR_SS_DOWNGRADE;
		अवरोध;
	शेष:
		/* speed करोwnshअगरt not supported */
		phy->speed_करोwngraded = false;
		वापस 0;
	पूर्ण

	ret_val = e1e_rphy(hw, offset, &phy_data);

	अगर (!ret_val)
		phy->speed_करोwngraded = !!(phy_data & mask);

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_polarity_m88 - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY specअगरic status रेजिस्टर.
 **/
s32 e1000_check_polarity_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_STATUS, &data);

	अगर (!ret_val)
		phy->cable_polarity = ((data & M88E1000_PSSR_REV_POLARITY)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_polarity_igp - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY port status रेजिस्टर, and the
 *  current speed (since there is no polarity at 100Mbps).
 **/
s32 e1000_check_polarity_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data, offset, mask;

	/* Polarity is determined based on the speed of
	 * our connection.
	 */
	ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	अगर (ret_val)
		वापस ret_val;

	अगर ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
		offset = IGP01E1000_PHY_PCS_INIT_REG;
		mask = IGP01E1000_PHY_POLARITY_MASK;
	पूर्ण अन्यथा अणु
		/* This really only applies to 10Mbps since
		 * there is no polarity क्रम 100Mbps (always 0).
		 */
		offset = IGP01E1000_PHY_PORT_STATUS;
		mask = IGP01E1000_PSSR_POLARITY_REVERSED;
	पूर्ण

	ret_val = e1e_rphy(hw, offset, &data);

	अगर (!ret_val)
		phy->cable_polarity = ((data & mask)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);

	वापस ret_val;
पूर्ण

/**
 *  e1000_check_polarity_अगरe - Check cable polarity क्रम IFE PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Polarity is determined on the polarity reversal feature being enabled.
 **/
s32 e1000_check_polarity_अगरe(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, offset, mask;

	/* Polarity is determined based on the reversal feature being enabled.
	 */
	अगर (phy->polarity_correction) अणु
		offset = IFE_PHY_EXTENDED_STATUS_CONTROL;
		mask = IFE_PESC_POLARITY_REVERSED;
	पूर्ण अन्यथा अणु
		offset = IFE_PHY_SPECIAL_CONTROL;
		mask = IFE_PSC_FORCE_POLARITY;
	पूर्ण

	ret_val = e1e_rphy(hw, offset, &phy_data);

	अगर (!ret_val)
		phy->cable_polarity = ((phy_data & mask)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);

	वापस ret_val;
पूर्ण

/**
 *  e1000_रुको_स्वतःneg - Wait क्रम स्वतः-neg completion
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Waits क्रम स्वतः-negotiation to complete or क्रम the स्वतः-negotiation समय
 *  limit to expire, which ever happens first.
 **/
अटल s32 e1000_रुको_स्वतःneg(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 i, phy_status;

	/* Break after स्वतःneg completes or PHY_AUTO_NEG_LIMIT expires. */
	क्रम (i = PHY_AUTO_NEG_LIMIT; i > 0; i--) अणु
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		अगर (ret_val)
			अवरोध;
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & BMSR_ANEGCOMPLETE)
			अवरोध;
		msleep(100);
	पूर्ण

	/* PHY_AUTO_NEG_TIME expiration करोesn't guarantee स्वतः-negotiation
	 * has completed.
	 */
	वापस ret_val;
पूर्ण

/**
 *  e1000e_phy_has_link_generic - Polls PHY क्रम link
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @iterations: number of बार to poll क्रम link
 *  @usec_पूर्णांकerval: delay between polling attempts
 *  @success: poपूर्णांकer to whether polling was successful or not
 *
 *  Polls the PHY status रेजिस्टर क्रम link, 'iterations' number of बार.
 **/
s32 e1000e_phy_has_link_generic(काष्ठा e1000_hw *hw, u32 iterations,
				u32 usec_पूर्णांकerval, bool *success)
अणु
	s32 ret_val = 0;
	u16 i, phy_status;

	*success = false;
	क्रम (i = 0; i < iterations; i++) अणु
		/* Some PHYs require the MII_BMSR रेजिस्टर to be पढ़ो
		 * twice due to the link bit being sticky.  No harm करोing
		 * it across the board.
		 */
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		अगर (ret_val) अणु
			/* If the first पढ़ो fails, another entity may have
			 * ownership of the resources, रुको and try again to
			 * see अगर they have relinquished the resources yet.
			 */
			अगर (usec_पूर्णांकerval >= 1000)
				msleep(usec_पूर्णांकerval / 1000);
			अन्यथा
				udelay(usec_पूर्णांकerval);
		पूर्ण
		ret_val = e1e_rphy(hw, MII_BMSR, &phy_status);
		अगर (ret_val)
			अवरोध;
		अगर (phy_status & BMSR_LSTATUS) अणु
			*success = true;
			अवरोध;
		पूर्ण
		अगर (usec_पूर्णांकerval >= 1000)
			msleep(usec_पूर्णांकerval / 1000);
		अन्यथा
			udelay(usec_पूर्णांकerval);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_get_cable_length_m88 - Determine cable length क्रम m88 PHY
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
s32 e1000e_get_cable_length_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, index;

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	index = ((phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
		 M88E1000_PSSR_CABLE_LENGTH_SHIFT);

	अगर (index >= M88E1000_CABLE_LENGTH_TABLE_SIZE - 1)
		वापस -E1000_ERR_PHY;

	phy->min_cable_length = e1000_m88_cable_length_table[index];
	phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

	वापस 0;
पूर्ण

/**
 *  e1000e_get_cable_length_igp_2 - Determine cable length क्रम igp2 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  The स्वतःmatic gain control (agc) normalizes the amplitude of the
 *  received संकेत, adjusting क्रम the attenuation produced by the
 *  cable.  By पढ़ोing the AGC रेजिस्टरs, which represent the
 *  combination of coarse and fine gain value, the value can be put
 *  पूर्णांकo a lookup table to obtain the approximate cable length
 *  क्रम each channel.
 **/
s32 e1000e_get_cable_length_igp_2(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, i, agc_value = 0;
	u16 cur_agc_index, max_agc_index = 0;
	u16 min_agc_index = IGP02E1000_CABLE_LENGTH_TABLE_SIZE - 1;
	अटल स्थिर u16 agc_reg_array[IGP02E1000_PHY_CHANNEL_NUM] = अणु
		IGP02E1000_PHY_AGC_A,
		IGP02E1000_PHY_AGC_B,
		IGP02E1000_PHY_AGC_C,
		IGP02E1000_PHY_AGC_D
	पूर्ण;

	/* Read the AGC रेजिस्टरs क्रम all channels */
	क्रम (i = 0; i < IGP02E1000_PHY_CHANNEL_NUM; i++) अणु
		ret_val = e1e_rphy(hw, agc_reg_array[i], &phy_data);
		अगर (ret_val)
			वापस ret_val;

		/* Getting bits 15:9, which represent the combination of
		 * coarse and fine gain values.  The result is a number
		 * that can be put पूर्णांकo the lookup table to obtain the
		 * approximate cable length.
		 */
		cur_agc_index = ((phy_data >> IGP02E1000_AGC_LENGTH_SHIFT) &
				 IGP02E1000_AGC_LENGTH_MASK);

		/* Array index bound check. */
		अगर ((cur_agc_index >= IGP02E1000_CABLE_LENGTH_TABLE_SIZE) ||
		    (cur_agc_index == 0))
			वापस -E1000_ERR_PHY;

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
	phy->min_cable_length = (((agc_value - IGP02E1000_AGC_RANGE) > 0) ?
				 (agc_value - IGP02E1000_AGC_RANGE) : 0);
	phy->max_cable_length = agc_value + IGP02E1000_AGC_RANGE;

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

	वापस 0;
पूर्ण

/**
 *  e1000e_get_phy_info_m88 - Retrieve PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Valid क्रम only copper links.  Read the PHY status रेजिस्टर (sticky पढ़ो)
 *  to verअगरy that link is up.  Read the PHY special control रेजिस्टर to
 *  determine the polarity and 10base-T extended distance.  Read the PHY
 *  special status रेजिस्टर to determine MDI/MDIx and current speed.  If
 *  speed is 1000, then determine cable length, local and remote receiver.
 **/
s32 e1000e_get_phy_info_m88(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	अगर (phy->media_type != e1000_media_type_copper) अणु
		e_dbg("Phy info is only valid for copper media\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val)
		वापस ret_val;

	अगर (!link) अणु
		e_dbg("Phy info is only valid if link is up\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy->polarity_correction = !!(phy_data &
				      M88E1000_PSCR_POLARITY_REVERSAL);

	ret_val = e1000_check_polarity_m88(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1e_rphy(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	phy->is_mdix = !!(phy_data & M88E1000_PSSR_MDIX);

	अगर ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS) अणु
		ret_val = hw->phy.ops.get_cable_length(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, MII_STAT1000, &phy_data);
		अगर (ret_val)
			वापस ret_val;

		phy->local_rx = (phy_data & LPA_1000LOCALRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (phy_data & LPA_1000REMRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		/* Set values to "undefined" */
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000e_get_phy_info_igp - Retrieve igp PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read PHY status to determine अगर link is up.  If link is up, then
 *  set/determine 10base-T extended distance and polarity correction.  Read
 *  PHY port status to determine MDI/MDIx and speed.  Based on the speed,
 *  determine on the cable length, local and remote receiver.
 **/
s32 e1000e_get_phy_info_igp(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val)
		वापस ret_val;

	अगर (!link) अणु
		e_dbg("Phy info is only valid if link is up\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	phy->polarity_correction = true;

	ret_val = e1000_check_polarity_igp(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1e_rphy(hw, IGP01E1000_PHY_PORT_STATUS, &data);
	अगर (ret_val)
		वापस ret_val;

	phy->is_mdix = !!(data & IGP01E1000_PSSR_MDIX);

	अगर ((data & IGP01E1000_PSSR_SPEED_MASK) ==
	    IGP01E1000_PSSR_SPEED_1000MBPS) अणु
		ret_val = phy->ops.get_cable_length(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, MII_STAT1000, &data);
		अगर (ret_val)
			वापस ret_val;

		phy->local_rx = (data & LPA_1000LOCALRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & LPA_1000REMRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_get_phy_info_अगरe - Retrieves various IFE PHY states
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Populates "phy" काष्ठाure with various feature states.
 **/
s32 e1000_get_phy_info_अगरe(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val)
		वापस ret_val;

	अगर (!link) अणु
		e_dbg("Phy info is only valid if link is up\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	ret_val = e1e_rphy(hw, IFE_PHY_SPECIAL_CONTROL, &data);
	अगर (ret_val)
		वापस ret_val;
	phy->polarity_correction = !(data & IFE_PSC_AUTO_POLARITY_DISABLE);

	अगर (phy->polarity_correction) अणु
		ret_val = e1000_check_polarity_अगरe(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण अन्यथा अणु
		/* Polarity is क्रमced */
		phy->cable_polarity = ((data & IFE_PSC_FORCE_POLARITY)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);
	पूर्ण

	ret_val = e1e_rphy(hw, IFE_PHY_MDIX_CONTROL, &data);
	अगर (ret_val)
		वापस ret_val;

	phy->is_mdix = !!(data & IFE_PMC_MDIX_STATUS);

	/* The following parameters are undefined क्रम 10/100 operation. */
	phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
	phy->local_rx = e1000_1000t_rx_status_undefined;
	phy->remote_rx = e1000_1000t_rx_status_undefined;

	वापस 0;
पूर्ण

/**
 *  e1000e_phy_sw_reset - PHY software reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Does a software reset of the PHY by पढ़ोing the PHY control रेजिस्टर and
 *  setting/ग_लिखो the control रेजिस्टर reset bit to the PHY.
 **/
s32 e1000e_phy_sw_reset(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val;
	u16 phy_ctrl;

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_ctrl);
	अगर (ret_val)
		वापस ret_val;

	phy_ctrl |= BMCR_RESET;
	ret_val = e1e_wphy(hw, MII_BMCR, phy_ctrl);
	अगर (ret_val)
		वापस ret_val;

	udelay(1);

	वापस ret_val;
पूर्ण

/**
 *  e1000e_phy_hw_reset_generic - PHY hardware reset
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरy the reset block is not blocking us from resetting.  Acquire
 *  semaphore (अगर necessary) and पढ़ो/set/ग_लिखो the device control reset
 *  bit in the PHY.  Wait the appropriate delay समय क्रम the device to
 *  reset and release the semaphore (अगर necessary).
 **/
s32 e1000e_phy_hw_reset_generic(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u32 ctrl;

	अगर (phy->ops.check_reset_block) अणु
		ret_val = phy->ops.check_reset_block(hw);
		अगर (ret_val)
			वापस 0;
	पूर्ण

	ret_val = phy->ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	ctrl = er32(CTRL);
	ew32(CTRL, ctrl | E1000_CTRL_PHY_RST);
	e1e_flush();

	udelay(phy->reset_delay_us);

	ew32(CTRL, ctrl);
	e1e_flush();

	usleep_range(150, 300);

	phy->ops.release(hw);

	वापस phy->ops.get_cfg_करोne(hw);
पूर्ण

/**
 *  e1000e_get_cfg_करोne_generic - Generic configuration करोne
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Generic function to रुको 10 milli-seconds क्रम configuration to complete
 *  and वापस success.
 **/
s32 e1000e_get_cfg_करोne_generic(काष्ठा e1000_hw __always_unused *hw)
अणु
	mdelay(10);

	वापस 0;
पूर्ण

/**
 *  e1000e_phy_init_script_igp3 - Inits the IGP3 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Initializes a Intel Gigabit PHY3 when an EEPROM is not present.
 **/
s32 e1000e_phy_init_script_igp3(काष्ठा e1000_hw *hw)
अणु
	e_dbg("Running IGP 3 PHY init script\n");

	/* PHY init IGP 3 */
	/* Enable rise/fall, 10-mode work in class-A */
	e1e_wphy(hw, 0x2F5B, 0x9018);
	/* Remove all caps from Replica path filter */
	e1e_wphy(hw, 0x2F52, 0x0000);
	/* Bias trimming क्रम ADC, AFE and Driver (Default) */
	e1e_wphy(hw, 0x2FB1, 0x8B24);
	/* Increase Hybrid poly bias */
	e1e_wphy(hw, 0x2FB2, 0xF8F0);
	/* Add 4% to Tx amplitude in Gig mode */
	e1e_wphy(hw, 0x2010, 0x10B0);
	/* Disable trimming (TTT) */
	e1e_wphy(hw, 0x2011, 0x0000);
	/* Poly DC correction to 94.6% + 2% क्रम all channels */
	e1e_wphy(hw, 0x20DD, 0x249A);
	/* ABS DC correction to 95.9% */
	e1e_wphy(hw, 0x20DE, 0x00D3);
	/* BG temp curve trim */
	e1e_wphy(hw, 0x28B4, 0x04CE);
	/* Increasing ADC OPAMP stage 1 currents to max */
	e1e_wphy(hw, 0x2F70, 0x29E4);
	/* Force 1000 ( required क्रम enabling PHY regs configuration) */
	e1e_wphy(hw, 0x0000, 0x0140);
	/* Set upd_freq to 6 */
	e1e_wphy(hw, 0x1F30, 0x1606);
	/* Disable NPDFE */
	e1e_wphy(hw, 0x1F31, 0xB814);
	/* Disable adaptive fixed FFE (Default) */
	e1e_wphy(hw, 0x1F35, 0x002A);
	/* Enable FFE hysteresis */
	e1e_wphy(hw, 0x1F3E, 0x0067);
	/* Fixed FFE क्रम लघु cable lengths */
	e1e_wphy(hw, 0x1F54, 0x0065);
	/* Fixed FFE क्रम medium cable lengths */
	e1e_wphy(hw, 0x1F55, 0x002A);
	/* Fixed FFE क्रम दीर्घ cable lengths */
	e1e_wphy(hw, 0x1F56, 0x002A);
	/* Enable Adaptive Clip Threshold */
	e1e_wphy(hw, 0x1F72, 0x3FB0);
	/* AHT reset limit to 1 */
	e1e_wphy(hw, 0x1F76, 0xC0FF);
	/* Set AHT master delay to 127 msec */
	e1e_wphy(hw, 0x1F77, 0x1DEC);
	/* Set scan bits क्रम AHT */
	e1e_wphy(hw, 0x1F78, 0xF9EF);
	/* Set AHT Preset bits */
	e1e_wphy(hw, 0x1F79, 0x0210);
	/* Change पूर्णांकeg_factor of channel A to 3 */
	e1e_wphy(hw, 0x1895, 0x0003);
	/* Change prop_factor of channels BCD to 8 */
	e1e_wphy(hw, 0x1796, 0x0008);
	/* Change cg_icount + enable पूर्णांकegbp क्रम channels BCD */
	e1e_wphy(hw, 0x1798, 0xD008);
	/* Change cg_icount + enable पूर्णांकegbp + change prop_factor_master
	 * to 8 क्रम channel A
	 */
	e1e_wphy(hw, 0x1898, 0xD918);
	/* Disable AHT in Slave mode on channel A */
	e1e_wphy(hw, 0x187A, 0x0800);
	/* Enable LPLU and disable AN to 1000 in non-D0a states,
	 * Enable SPD+B2B
	 */
	e1e_wphy(hw, 0x0019, 0x008D);
	/* Enable restart AN on an1000_dis change */
	e1e_wphy(hw, 0x001B, 0x2080);
	/* Enable wh_fअगरo पढ़ो घड़ी in 10/100 modes */
	e1e_wphy(hw, 0x0014, 0x0045);
	/* Restart AN, Speed selection is 1000 */
	e1e_wphy(hw, 0x0000, 0x1340);

	वापस 0;
पूर्ण

/**
 *  e1000e_get_phy_type_from_id - Get PHY type from id
 *  @phy_id: phy_id पढ़ो from the phy
 *
 *  Returns the phy type from the id.
 **/
क्रमागत e1000_phy_type e1000e_get_phy_type_from_id(u32 phy_id)
अणु
	क्रमागत e1000_phy_type phy_type = e1000_phy_unknown;

	चयन (phy_id) अणु
	हाल M88E1000_I_PHY_ID:
	हाल M88E1000_E_PHY_ID:
	हाल M88E1111_I_PHY_ID:
	हाल M88E1011_I_PHY_ID:
		phy_type = e1000_phy_m88;
		अवरोध;
	हाल IGP01E1000_I_PHY_ID:	/* IGP 1 & 2 share this */
		phy_type = e1000_phy_igp_2;
		अवरोध;
	हाल GG82563_E_PHY_ID:
		phy_type = e1000_phy_gg82563;
		अवरोध;
	हाल IGP03E1000_E_PHY_ID:
		phy_type = e1000_phy_igp_3;
		अवरोध;
	हाल IFE_E_PHY_ID:
	हाल IFE_PLUS_E_PHY_ID:
	हाल IFE_C_E_PHY_ID:
		phy_type = e1000_phy_अगरe;
		अवरोध;
	हाल BME1000_E_PHY_ID:
	हाल BME1000_E_PHY_ID_R2:
		phy_type = e1000_phy_bm;
		अवरोध;
	हाल I82578_E_PHY_ID:
		phy_type = e1000_phy_82578;
		अवरोध;
	हाल I82577_E_PHY_ID:
		phy_type = e1000_phy_82577;
		अवरोध;
	हाल I82579_E_PHY_ID:
		phy_type = e1000_phy_82579;
		अवरोध;
	हाल I217_E_PHY_ID:
		phy_type = e1000_phy_i217;
		अवरोध;
	शेष:
		phy_type = e1000_phy_unknown;
		अवरोध;
	पूर्ण
	वापस phy_type;
पूर्ण

/**
 *  e1000e_determine_phy_address - Determines PHY address.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This uses a trial and error method to loop through possible PHY
 *  addresses. It tests each by पढ़ोing the PHY ID रेजिस्टरs and
 *  checking क्रम a match.
 **/
s32 e1000e_determine_phy_address(काष्ठा e1000_hw *hw)
अणु
	u32 phy_addr = 0;
	u32 i;
	क्रमागत e1000_phy_type phy_type = e1000_phy_unknown;

	hw->phy.id = phy_type;

	क्रम (phy_addr = 0; phy_addr < E1000_MAX_PHY_ADDR; phy_addr++) अणु
		hw->phy.addr = phy_addr;
		i = 0;

		करो अणु
			e1000e_get_phy_id(hw);
			phy_type = e1000e_get_phy_type_from_id(hw->phy.id);

			/* If phy_type is valid, अवरोध - we found our
			 * PHY address
			 */
			अगर (phy_type != e1000_phy_unknown)
				वापस 0;

			usleep_range(1000, 2000);
			i++;
		पूर्ण जबतक (i < 10);
	पूर्ण

	वापस -E1000_ERR_PHY_TYPE;
पूर्ण

/**
 *  e1000_get_phy_addr_क्रम_bm_page - Retrieve PHY page address
 *  @page: page to access
 *  @reg: रेजिस्टर to check
 *
 *  Returns the phy address क्रम the page requested.
 **/
अटल u32 e1000_get_phy_addr_क्रम_bm_page(u32 page, u32 reg)
अणु
	u32 phy_addr = 2;

	अगर ((page >= 768) || (page == 0 && reg == 25) || (reg == 31))
		phy_addr = 1;

	वापस phy_addr;
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_bm - Write BM PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
s32 e1000e_ग_लिखो_phy_reg_bm(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	s32 ret_val;
	u32 page = offset >> IGP_PAGE_SHIFT;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, &data,
							 false, false);
		जाओ release;
	पूर्ण

	hw->phy.addr = e1000_get_phy_addr_क्रम_bm_page(page, offset);

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		u32 page_shअगरt, page_select;

		/* Page select is रेजिस्टर 31 क्रम phy address 1 and 22 क्रम
		 * phy address 2 and 3. Page select is shअगरted only क्रम
		 * phy address 1.
		 */
		अगर (hw->phy.addr == 1) अणु
			page_shअगरt = IGP_PAGE_SHIFT;
			page_select = IGP01E1000_PHY_PAGE_SELECT;
		पूर्ण अन्यथा अणु
			page_shअगरt = 0;
			page_select = BM_PHY_PAGE_SELECT;
		पूर्ण

		/* Page is shअगरted left, PHY expects (page x 32) */
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, page_select,
						    (page << page_shअगरt));
		अगर (ret_val)
			जाओ release;
	पूर्ण

	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					    data);

release:
	hw->phy.ops.release(hw);
	वापस ret_val;
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_bm - Read BM PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and storing the retrieved inक्रमmation in data.  Release any acquired
 *  semaphores beक्रमe निकासing.
 **/
s32 e1000e_पढ़ो_phy_reg_bm(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	s32 ret_val;
	u32 page = offset >> IGP_PAGE_SHIFT;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, data,
							 true, false);
		जाओ release;
	पूर्ण

	hw->phy.addr = e1000_get_phy_addr_क्रम_bm_page(page, offset);

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		u32 page_shअगरt, page_select;

		/* Page select is रेजिस्टर 31 क्रम phy address 1 and 22 क्रम
		 * phy address 2 and 3. Page select is shअगरted only क्रम
		 * phy address 1.
		 */
		अगर (hw->phy.addr == 1) अणु
			page_shअगरt = IGP_PAGE_SHIFT;
			page_select = IGP01E1000_PHY_PAGE_SELECT;
		पूर्ण अन्यथा अणु
			page_shअगरt = 0;
			page_select = BM_PHY_PAGE_SELECT;
		पूर्ण

		/* Page is shअगरted left, PHY expects (page x 32) */
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, page_select,
						    (page << page_shअगरt));
		अगर (ret_val)
			जाओ release;
	पूर्ण

	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					   data);
release:
	hw->phy.ops.release(hw);
	वापस ret_val;
पूर्ण

/**
 *  e1000e_पढ़ो_phy_reg_bm2 - Read BM PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and storing the retrieved inक्रमmation in data.  Release any acquired
 *  semaphores beक्रमe निकासing.
 **/
s32 e1000e_पढ़ो_phy_reg_bm2(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	s32 ret_val;
	u16 page = (u16)(offset >> IGP_PAGE_SHIFT);

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, data,
							 true, false);
		जाओ release;
	पूर्ण

	hw->phy.addr = 1;

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		/* Page is shअगरted left, PHY expects (page x 32) */
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_PHY_PAGE_SELECT,
						    page);

		अगर (ret_val)
			जाओ release;
	पूर्ण

	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					   data);
release:
	hw->phy.ops.release(hw);
	वापस ret_val;
पूर्ण

/**
 *  e1000e_ग_लिखो_phy_reg_bm2 - Write BM PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
s32 e1000e_ग_लिखो_phy_reg_bm2(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	s32 ret_val;
	u16 page = (u16)(offset >> IGP_PAGE_SHIFT);

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, &data,
							 false, false);
		जाओ release;
	पूर्ण

	hw->phy.addr = 1;

	अगर (offset > MAX_PHY_MULTI_PAGE_REG) अणु
		/* Page is shअगरted left, PHY expects (page x 32) */
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_PHY_PAGE_SELECT,
						    page);

		अगर (ret_val)
			जाओ release;
	पूर्ण

	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & offset,
					    data);

release:
	hw->phy.ops.release(hw);
	वापस ret_val;
पूर्ण

/**
 *  e1000_enable_phy_wakeup_reg_access_bm - enable access to BM wakeup रेजिस्टरs
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @phy_reg: poपूर्णांकer to store original contents of BM_WUC_ENABLE_REG
 *
 *  Assumes semaphore alपढ़ोy acquired and phy_reg poपूर्णांकs to a valid memory
 *  address to store contents of the BM_WUC_ENABLE_REG रेजिस्टर.
 **/
s32 e1000_enable_phy_wakeup_reg_access_bm(काष्ठा e1000_hw *hw, u16 *phy_reg)
अणु
	s32 ret_val;
	u16 temp;

	/* All page select, port ctrl and wakeup रेजिस्टरs use phy address 1 */
	hw->phy.addr = 1;

	/* Select Port Control Registers page */
	ret_val = e1000_set_page_igp(hw, (BM_PORT_CTRL_PAGE << IGP_PAGE_SHIFT));
	अगर (ret_val) अणु
		e_dbg("Could not set Port Control page\n");
		वापस ret_val;
	पूर्ण

	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, phy_reg);
	अगर (ret_val) अणु
		e_dbg("Could not read PHY register %d.%d\n",
		      BM_PORT_CTRL_PAGE, BM_WUC_ENABLE_REG);
		वापस ret_val;
	पूर्ण

	/* Enable both PHY wakeup mode and Wakeup रेजिस्टर page ग_लिखोs.
	 * Prevent a घातer state change by disabling ME and Host PHY wakeup.
	 */
	temp = *phy_reg;
	temp |= BM_WUC_ENABLE_BIT;
	temp &= ~(BM_WUC_ME_WU_BIT | BM_WUC_HOST_WU_BIT);

	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, temp);
	अगर (ret_val) अणु
		e_dbg("Could not write PHY register %d.%d\n",
		      BM_PORT_CTRL_PAGE, BM_WUC_ENABLE_REG);
		वापस ret_val;
	पूर्ण

	/* Select Host Wakeup Registers page - caller now able to ग_लिखो
	 * रेजिस्टरs on the Wakeup रेजिस्टरs page
	 */
	वापस e1000_set_page_igp(hw, (BM_WUC_PAGE << IGP_PAGE_SHIFT));
पूर्ण

/**
 *  e1000_disable_phy_wakeup_reg_access_bm - disable access to BM wakeup regs
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @phy_reg: poपूर्णांकer to original contents of BM_WUC_ENABLE_REG
 *
 *  Restore BM_WUC_ENABLE_REG to its original value.
 *
 *  Assumes semaphore alपढ़ोy acquired and *phy_reg is the contents of the
 *  BM_WUC_ENABLE_REG beक्रमe रेजिस्टर(s) on BM_WUC_PAGE were accessed by
 *  caller.
 **/
s32 e1000_disable_phy_wakeup_reg_access_bm(काष्ठा e1000_hw *hw, u16 *phy_reg)
अणु
	s32 ret_val;

	/* Select Port Control Registers page */
	ret_val = e1000_set_page_igp(hw, (BM_PORT_CTRL_PAGE << IGP_PAGE_SHIFT));
	अगर (ret_val) अणु
		e_dbg("Could not set Port Control page\n");
		वापस ret_val;
	पूर्ण

	/* Restore 769.17 to its original value */
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_WUC_ENABLE_REG, *phy_reg);
	अगर (ret_val)
		e_dbg("Could not restore PHY register %d.%d\n",
		      BM_PORT_CTRL_PAGE, BM_WUC_ENABLE_REG);

	वापस ret_val;
पूर्ण

/**
 *  e1000_access_phy_wakeup_reg_bm - Read/ग_लिखो BM PHY wakeup रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो or written
 *  @data: poपूर्णांकer to the data to पढ़ो or ग_लिखो
 *  @पढ़ो: determines अगर operation is पढ़ो or ग_लिखो
 *  @page_set: BM_WUC_PAGE alपढ़ोy set and access enabled
 *
 *  Read the PHY रेजिस्टर at offset and store the retrieved inक्रमmation in
 *  data, or ग_लिखो data to PHY रेजिस्टर at offset.  Note the procedure to
 *  access the PHY wakeup रेजिस्टरs is dअगरferent than पढ़ोing the other PHY
 *  रेजिस्टरs. It works as such:
 *  1) Set 769.17.2 (page 769, रेजिस्टर 17, bit 2) = 1
 *  2) Set page to 800 क्रम host (801 अगर we were manageability)
 *  3) Write the address using the address opcode (0x11)
 *  4) Read or ग_लिखो the data using the data opcode (0x12)
 *  5) Restore 769.17.2 to its original value
 *
 *  Steps 1 and 2 are करोne by e1000_enable_phy_wakeup_reg_access_bm() and
 *  step 5 is करोne by e1000_disable_phy_wakeup_reg_access_bm().
 *
 *  Assumes semaphore is alपढ़ोy acquired.  When page_set==true, assumes
 *  the PHY page is set to BM_WUC_PAGE (i.e. a function in the call stack
 *  is responsible क्रम calls to e1000_[enable|disable]_phy_wakeup_reg_bm()).
 **/
अटल s32 e1000_access_phy_wakeup_reg_bm(काष्ठा e1000_hw *hw, u32 offset,
					  u16 *data, bool पढ़ो, bool page_set)
अणु
	s32 ret_val;
	u16 reg = BM_PHY_REG_NUM(offset);
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 phy_reg = 0;

	/* Gig must be disabled क्रम MDIO accesses to Host Wakeup reg page */
	अगर ((hw->mac.type == e1000_pchlan) &&
	    (!(er32(PHY_CTRL) & E1000_PHY_CTRL_GBE_DISABLE)))
		e_dbg("Attempting to access page %d while gig enabled.\n",
		      page);

	अगर (!page_set) अणु
		/* Enable access to PHY wakeup रेजिस्टरs */
		ret_val = e1000_enable_phy_wakeup_reg_access_bm(hw, &phy_reg);
		अगर (ret_val) अणु
			e_dbg("Could not enable PHY wakeup reg access\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	e_dbg("Accessing PHY page %d reg 0x%x\n", page, reg);

	/* Write the Wakeup रेजिस्टर page offset value using opcode 0x11 */
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_WUC_ADDRESS_OPCODE, reg);
	अगर (ret_val) अणु
		e_dbg("Could not write address opcode to page %d\n", page);
		वापस ret_val;
	पूर्ण

	अगर (पढ़ो) अणु
		/* Read the Wakeup रेजिस्टर page value using opcode 0x12 */
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, BM_WUC_DATA_OPCODE,
						   data);
	पूर्ण अन्यथा अणु
		/* Write the Wakeup रेजिस्टर page value using opcode 0x12 */
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, BM_WUC_DATA_OPCODE,
						    *data);
	पूर्ण

	अगर (ret_val) अणु
		e_dbg("Could not access PHY reg %d.%d\n", page, reg);
		वापस ret_val;
	पूर्ण

	अगर (!page_set)
		ret_val = e1000_disable_phy_wakeup_reg_access_bm(hw, &phy_reg);

	वापस ret_val;
पूर्ण

/**
 * e1000_घातer_up_phy_copper - Restore copper link in हाल of PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, restore the link to previous
 * settings.
 **/
व्योम e1000_घातer_up_phy_copper(काष्ठा e1000_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	e1e_rphy(hw, MII_BMCR, &mii_reg);
	mii_reg &= ~BMCR_PDOWN;
	e1e_wphy(hw, MII_BMCR, mii_reg);
पूर्ण

/**
 * e1000_घातer_करोwn_phy_copper - Restore copper link in हाल of PHY घातer करोwn
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * In the हाल of a PHY घातer करोwn to save घातer, or to turn off link during a
 * driver unload, or wake on lan is not enabled, restore the link to previous
 * settings.
 **/
व्योम e1000_घातer_करोwn_phy_copper(काष्ठा e1000_hw *hw)
अणु
	u16 mii_reg = 0;

	/* The PHY will retain its settings across a घातer करोwn/up cycle */
	e1e_rphy(hw, MII_BMCR, &mii_reg);
	mii_reg |= BMCR_PDOWN;
	e1e_wphy(hw, MII_BMCR, mii_reg);
	usleep_range(1000, 2000);
पूर्ण

/**
 *  __e1000_पढ़ो_phy_reg_hv -  Read HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *  @page_set: BM_WUC_PAGE alपढ़ोy set and access enabled
 *
 *  Acquires semaphore, अगर necessary, then पढ़ोs the PHY रेजिस्टर at offset
 *  and stores the retrieved inक्रमmation in data.  Release any acquired
 *  semaphore beक्रमe निकासing.
 **/
अटल s32 __e1000_पढ़ो_phy_reg_hv(काष्ठा e1000_hw *hw, u32 offset, u16 *data,
				   bool locked, bool page_set)
अणु
	s32 ret_val;
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 reg = BM_PHY_REG_NUM(offset);
	u32 phy_addr = hw->phy.addr = e1000_get_phy_addr_क्रम_hv_page(page);

	अगर (!locked) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, data,
							 true, page_set);
		जाओ out;
	पूर्ण

	अगर (page > 0 && page < HV_INTC_FC_PAGE_START) अणु
		ret_val = e1000_access_phy_debug_regs_hv(hw, offset,
							 data, true);
		जाओ out;
	पूर्ण

	अगर (!page_set) अणु
		अगर (page == HV_INTC_FC_PAGE_START)
			page = 0;

		अगर (reg > MAX_PHY_MULTI_PAGE_REG) अणु
			/* Page is shअगरted left, PHY expects (page x 32) */
			ret_val = e1000_set_page_igp(hw,
						     (page << IGP_PAGE_SHIFT));

			hw->phy.addr = phy_addr;

			अगर (ret_val)
				जाओ out;
		पूर्ण
	पूर्ण

	e_dbg("reading PHY page %d (or 0x%x shifted) reg 0x%x\n", page,
	      page << IGP_PAGE_SHIFT, reg);

	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & reg, data);
out:
	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_पढ़ो_phy_reg_hv -  Read HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Acquires semaphore then पढ़ोs the PHY रेजिस्टर at offset and stores
 *  the retrieved inक्रमmation in data.  Release the acquired semaphore
 *  beक्रमe निकासing.
 **/
s32 e1000_पढ़ो_phy_reg_hv(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000_पढ़ो_phy_reg_hv(hw, offset, data, false, false);
पूर्ण

/**
 *  e1000_पढ़ो_phy_reg_hv_locked -  Read HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो
 *  @data: poपूर्णांकer to the पढ़ो data
 *
 *  Reads the PHY रेजिस्टर at offset and stores the retrieved inक्रमmation
 *  in data.  Assumes semaphore alपढ़ोy acquired.
 **/
s32 e1000_पढ़ो_phy_reg_hv_locked(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000_पढ़ो_phy_reg_hv(hw, offset, data, true, false);
पूर्ण

/**
 *  e1000_पढ़ो_phy_reg_page_hv - Read HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Reads the PHY रेजिस्टर at offset and stores the retrieved inक्रमmation
 *  in data.  Assumes semaphore alपढ़ोy acquired and page alपढ़ोy set.
 **/
s32 e1000_पढ़ो_phy_reg_page_hv(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस __e1000_पढ़ो_phy_reg_hv(hw, offset, data, true, true);
पूर्ण

/**
 *  __e1000_ग_लिखो_phy_reg_hv - Write HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *  @locked: semaphore has alपढ़ोy been acquired or not
 *  @page_set: BM_WUC_PAGE alपढ़ोy set and access enabled
 *
 *  Acquires semaphore, अगर necessary, then ग_लिखोs the data to PHY रेजिस्टर
 *  at the offset.  Release any acquired semaphores beक्रमe निकासing.
 **/
अटल s32 __e1000_ग_लिखो_phy_reg_hv(काष्ठा e1000_hw *hw, u32 offset, u16 data,
				    bool locked, bool page_set)
अणु
	s32 ret_val;
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 reg = BM_PHY_REG_NUM(offset);
	u32 phy_addr = hw->phy.addr = e1000_get_phy_addr_क्रम_hv_page(page);

	अगर (!locked) अणु
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	/* Page 800 works dअगरferently than the rest so it has its own func */
	अगर (page == BM_WUC_PAGE) अणु
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, &data,
							 false, page_set);
		जाओ out;
	पूर्ण

	अगर (page > 0 && page < HV_INTC_FC_PAGE_START) अणु
		ret_val = e1000_access_phy_debug_regs_hv(hw, offset,
							 &data, false);
		जाओ out;
	पूर्ण

	अगर (!page_set) अणु
		अगर (page == HV_INTC_FC_PAGE_START)
			page = 0;

		/* Workaround MDIO accesses being disabled after entering IEEE
		 * Power Down (when bit 11 of the PHY Control रेजिस्टर is set)
		 */
		अगर ((hw->phy.type == e1000_phy_82578) &&
		    (hw->phy.revision >= 1) &&
		    (hw->phy.addr == 2) &&
		    !(MAX_PHY_REG_ADDRESS & reg) && (data & BIT(11))) अणु
			u16 data2 = 0x7EFF;

			ret_val = e1000_access_phy_debug_regs_hv(hw,
								 BIT(6) | 0x3,
								 &data2, false);
			अगर (ret_val)
				जाओ out;
		पूर्ण

		अगर (reg > MAX_PHY_MULTI_PAGE_REG) अणु
			/* Page is shअगरted left, PHY expects (page x 32) */
			ret_val = e1000_set_page_igp(hw,
						     (page << IGP_PAGE_SHIFT));

			hw->phy.addr = phy_addr;

			अगर (ret_val)
				जाओ out;
		पूर्ण
	पूर्ण

	e_dbg("writing PHY page %d (or 0x%x shifted) reg 0x%x\n", page,
	      page << IGP_PAGE_SHIFT, reg);

	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & reg,
					    data);

out:
	अगर (!locked)
		hw->phy.ops.release(hw);

	वापस ret_val;
पूर्ण

/**
 *  e1000_ग_लिखो_phy_reg_hv - Write HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Acquires semaphore then ग_लिखोs the data to PHY रेजिस्टर at the offset.
 *  Release the acquired semaphores beक्रमe निकासing.
 **/
s32 e1000_ग_लिखो_phy_reg_hv(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000_ग_लिखो_phy_reg_hv(hw, offset, data, false, false);
पूर्ण

/**
 *  e1000_ग_लिखो_phy_reg_hv_locked - Write HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes the data to PHY रेजिस्टर at the offset.  Assumes semaphore
 *  alपढ़ोy acquired.
 **/
s32 e1000_ग_लिखो_phy_reg_hv_locked(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000_ग_लिखो_phy_reg_hv(hw, offset, data, true, false);
पूर्ण

/**
 *  e1000_ग_लिखो_phy_reg_page_hv - Write HV PHY रेजिस्टर
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to ग_लिखो to
 *  @data: data to ग_लिखो at रेजिस्टर offset
 *
 *  Writes the data to PHY रेजिस्टर at the offset.  Assumes semaphore
 *  alपढ़ोy acquired and page alपढ़ोy set.
 **/
s32 e1000_ग_लिखो_phy_reg_page_hv(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस __e1000_ग_लिखो_phy_reg_hv(hw, offset, data, true, true);
पूर्ण

/**
 *  e1000_get_phy_addr_क्रम_hv_page - Get PHY address based on page
 *  @page: page to be accessed
 **/
अटल u32 e1000_get_phy_addr_क्रम_hv_page(u32 page)
अणु
	u32 phy_addr = 2;

	अगर (page >= HV_INTC_FC_PAGE_START)
		phy_addr = 1;

	वापस phy_addr;
पूर्ण

/**
 *  e1000_access_phy_debug_regs_hv - Read HV PHY venकरोr specअगरic high रेजिस्टरs
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @offset: रेजिस्टर offset to be पढ़ो or written
 *  @data: poपूर्णांकer to the data to be पढ़ो or written
 *  @पढ़ो: determines अगर operation is पढ़ो or ग_लिखो
 *
 *  Reads the PHY रेजिस्टर at offset and stores the retreived inक्रमmation
 *  in data.  Assumes semaphore alपढ़ोy acquired.  Note that the procedure
 *  to access these regs uses the address port and data port to पढ़ो/ग_लिखो.
 *  These accesses करोne with PHY address 2 and without using pages.
 **/
अटल s32 e1000_access_phy_debug_regs_hv(काष्ठा e1000_hw *hw, u32 offset,
					  u16 *data, bool पढ़ो)
अणु
	s32 ret_val;
	u32 addr_reg;
	u32 data_reg;

	/* This takes care of the dअगरference with desktop vs mobile phy */
	addr_reg = ((hw->phy.type == e1000_phy_82578) ?
		    I82578_ADDR_REG : I82577_ADDR_REG);
	data_reg = addr_reg + 1;

	/* All operations in this function are phy address 2 */
	hw->phy.addr = 2;

	/* masking with 0x3F to हटाओ the page from offset */
	ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, addr_reg, (u16)offset & 0x3F);
	अगर (ret_val) अणु
		e_dbg("Could not write the Address Offset port register\n");
		वापस ret_val;
	पूर्ण

	/* Read or ग_लिखो the data value next */
	अगर (पढ़ो)
		ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, data_reg, data);
	अन्यथा
		ret_val = e1000e_ग_लिखो_phy_reg_mdic(hw, data_reg, *data);

	अगर (ret_val)
		e_dbg("Could not access the Data port register\n");

	वापस ret_val;
पूर्ण

/**
 *  e1000_link_stall_workaround_hv - Si workaround
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  This function works around a Si bug where the link partner can get
 *  a link up indication beक्रमe the PHY करोes.  If small packets are sent
 *  by the link partner they can be placed in the packet buffer without
 *  being properly accounted क्रम by the PHY and will stall preventing
 *  further packets from being received.  The workaround is to clear the
 *  packet buffer after the PHY detects link up.
 **/
s32 e1000_link_stall_workaround_hv(काष्ठा e1000_hw *hw)
अणु
	s32 ret_val = 0;
	u16 data;

	अगर (hw->phy.type != e1000_phy_82578)
		वापस 0;

	/* Do not apply workaround अगर in PHY loopback bit 14 set */
	e1e_rphy(hw, MII_BMCR, &data);
	अगर (data & BMCR_LOOPBACK)
		वापस 0;

	/* check अगर link is up and at 1Gbps */
	ret_val = e1e_rphy(hw, BM_CS_STATUS, &data);
	अगर (ret_val)
		वापस ret_val;

	data &= (BM_CS_STATUS_LINK_UP | BM_CS_STATUS_RESOLVED |
		 BM_CS_STATUS_SPEED_MASK);

	अगर (data != (BM_CS_STATUS_LINK_UP | BM_CS_STATUS_RESOLVED |
		     BM_CS_STATUS_SPEED_1000))
		वापस 0;

	msleep(200);

	/* flush the packets in the fअगरo buffer */
	ret_val = e1e_wphy(hw, HV_MUX_DATA_CTRL,
			   (HV_MUX_DATA_CTRL_GEN_TO_MAC |
			    HV_MUX_DATA_CTRL_FORCE_SPEED));
	अगर (ret_val)
		वापस ret_val;

	वापस e1e_wphy(hw, HV_MUX_DATA_CTRL, HV_MUX_DATA_CTRL_GEN_TO_MAC);
पूर्ण

/**
 *  e1000_check_polarity_82577 - Checks the polarity.
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Success वापसs 0, Failure वापसs -E1000_ERR_PHY (-2)
 *
 *  Polarity is determined based on the PHY specअगरic status रेजिस्टर.
 **/
s32 e1000_check_polarity_82577(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	ret_val = e1e_rphy(hw, I82577_PHY_STATUS_2, &data);

	अगर (!ret_val)
		phy->cable_polarity = ((data & I82577_PHY_STATUS2_REV_POLARITY)
				       ? e1000_rev_polarity_reversed
				       : e1000_rev_polarity_normal);

	वापस ret_val;
पूर्ण

/**
 *  e1000_phy_क्रमce_speed_duplex_82577 - Force speed/duplex क्रम I82577 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Calls the PHY setup function to क्रमce speed and duplex.
 **/
s32 e1000_phy_क्रमce_speed_duplex_82577(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	ret_val = e1e_rphy(hw, MII_BMCR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	e1000e_phy_क्रमce_speed_duplex_setup(hw, &phy_data);

	ret_val = e1e_wphy(hw, MII_BMCR, phy_data);
	अगर (ret_val)
		वापस ret_val;

	udelay(1);

	अगर (phy->स्वतःneg_रुको_to_complete) अणु
		e_dbg("Waiting for forced speed/duplex link on 82577 phy\n");

		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
		अगर (ret_val)
			वापस ret_val;

		अगर (!link)
			e_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = e1000e_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						      100000, &link);
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 *  e1000_get_phy_info_82577 - Retrieve I82577 PHY inक्रमmation
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Read PHY status to determine अगर link is up.  If link is up, then
 *  set/determine 10base-T extended distance and polarity correction.  Read
 *  PHY port status to determine MDI/MDIx and speed.  Based on the speed,
 *  determine on the cable length, local and remote receiver.
 **/
s32 e1000_get_phy_info_82577(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;
	bool link;

	ret_val = e1000e_phy_has_link_generic(hw, 1, 0, &link);
	अगर (ret_val)
		वापस ret_val;

	अगर (!link) अणु
		e_dbg("Phy info is only valid if link is up\n");
		वापस -E1000_ERR_CONFIG;
	पूर्ण

	phy->polarity_correction = true;

	ret_val = e1000_check_polarity_82577(hw);
	अगर (ret_val)
		वापस ret_val;

	ret_val = e1e_rphy(hw, I82577_PHY_STATUS_2, &data);
	अगर (ret_val)
		वापस ret_val;

	phy->is_mdix = !!(data & I82577_PHY_STATUS2_MDIX);

	अगर ((data & I82577_PHY_STATUS2_SPEED_MASK) ==
	    I82577_PHY_STATUS2_SPEED_1000MBPS) अणु
		ret_val = hw->phy.ops.get_cable_length(hw);
		अगर (ret_val)
			वापस ret_val;

		ret_val = e1e_rphy(hw, MII_STAT1000, &data);
		अगर (ret_val)
			वापस ret_val;

		phy->local_rx = (data & LPA_1000LOCALRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;

		phy->remote_rx = (data & LPA_1000REMRXOK)
		    ? e1000_1000t_rx_status_ok : e1000_1000t_rx_status_not_ok;
	पूर्ण अन्यथा अणु
		phy->cable_length = E1000_CABLE_LENGTH_UNDEFINED;
		phy->local_rx = e1000_1000t_rx_status_undefined;
		phy->remote_rx = e1000_1000t_rx_status_undefined;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_get_cable_length_82577 - Determine cable length क्रम 82577 PHY
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Reads the diagnostic status रेजिस्टर and verअगरies result is valid beक्रमe
 * placing it in the phy_cable_length field.
 **/
s32 e1000_get_cable_length_82577(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, length;

	ret_val = e1e_rphy(hw, I82577_PHY_DIAG_STATUS, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	length = ((phy_data & I82577_DSTATUS_CABLE_LENGTH) >>
		  I82577_DSTATUS_CABLE_LENGTH_SHIFT);

	अगर (length == E1000_CABLE_LENGTH_UNDEFINED)
		वापस -E1000_ERR_PHY;

	phy->cable_length = length;

	वापस 0;
पूर्ण

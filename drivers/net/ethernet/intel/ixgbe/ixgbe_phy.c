<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/sched.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_phy.h"

अटल व्योम ixgbe_i2c_start(काष्ठा ixgbe_hw *hw);
अटल व्योम ixgbe_i2c_stop(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_घड़ी_in_i2c_byte(काष्ठा ixgbe_hw *hw, u8 *data);
अटल s32 ixgbe_घड़ी_out_i2c_byte(काष्ठा ixgbe_hw *hw, u8 data);
अटल s32 ixgbe_get_i2c_ack(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_घड़ी_in_i2c_bit(काष्ठा ixgbe_hw *hw, bool *data);
अटल s32 ixgbe_घड़ी_out_i2c_bit(काष्ठा ixgbe_hw *hw, bool data);
अटल व्योम ixgbe_उठाओ_i2c_clk(काष्ठा ixgbe_hw *hw, u32 *i2cctl);
अटल व्योम ixgbe_lower_i2c_clk(काष्ठा ixgbe_hw *hw, u32 *i2cctl);
अटल s32 ixgbe_set_i2c_data(काष्ठा ixgbe_hw *hw, u32 *i2cctl, bool data);
अटल bool ixgbe_get_i2c_data(काष्ठा ixgbe_hw *hw, u32 *i2cctl);
अटल व्योम ixgbe_i2c_bus_clear(काष्ठा ixgbe_hw *hw);
अटल क्रमागत ixgbe_phy_type ixgbe_get_phy_type_from_id(u32 phy_id);
अटल s32 ixgbe_get_phy_id(काष्ठा ixgbe_hw *hw);
अटल s32 ixgbe_identअगरy_qsfp_module_generic(काष्ठा ixgbe_hw *hw);

/**
 *  ixgbe_out_i2c_byte_ack - Send I2C byte with ack
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @byte: byte to send
 *
 *  Returns an error code on error.
 **/
अटल s32 ixgbe_out_i2c_byte_ack(काष्ठा ixgbe_hw *hw, u8 byte)
अणु
	s32 status;

	status = ixgbe_घड़ी_out_i2c_byte(hw, byte);
	अगर (status)
		वापस status;
	वापस ixgbe_get_i2c_ack(hw);
पूर्ण

/**
 *  ixgbe_in_i2c_byte_ack - Receive an I2C byte and send ack
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @byte: poपूर्णांकer to a u8 to receive the byte
 *
 *  Returns an error code on error.
 **/
अटल s32 ixgbe_in_i2c_byte_ack(काष्ठा ixgbe_hw *hw, u8 *byte)
अणु
	s32 status;

	status = ixgbe_घड़ी_in_i2c_byte(hw, byte);
	अगर (status)
		वापस status;
	/* ACK */
	वापस ixgbe_घड़ी_out_i2c_bit(hw, false);
पूर्ण

/**
 *  ixgbe_ones_comp_byte_add - Perक्रमm one's complement addition
 *  @add1: addend 1
 *  @add2: addend 2
 *
 *  Returns one's complement 8-bit sum.
 **/
अटल u8 ixgbe_ones_comp_byte_add(u8 add1, u8 add2)
अणु
	u16 sum = add1 + add2;

	sum = (sum & 0xFF) + (sum >> 8);
	वापस sum & 0xFF;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_combined_generic_पूर्णांक - Perक्रमm I2C पढ़ो combined operation
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @addr: I2C bus address to पढ़ो from
 *  @reg: I2C device रेजिस्टर to पढ़ो from
 *  @val: poपूर्णांकer to location to receive पढ़ो value
 *  @lock: true अगर to take and release semaphore
 *
 *  Returns an error code on error.
 */
s32 ixgbe_पढ़ो_i2c_combined_generic_पूर्णांक(काष्ठा ixgbe_hw *hw, u8 addr,
					u16 reg, u16 *val, bool lock)
अणु
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	पूर्णांक max_retry = 3;
	पूर्णांक retry = 0;
	u8 csum_byte;
	u8 high_bits;
	u8 low_bits;
	u8 reg_high;
	u8 csum;

	reg_high = ((reg >> 7) & 0xFE) | 1;     /* Indicate पढ़ो combined */
	csum = ixgbe_ones_comp_byte_add(reg_high, reg & 0xFF);
	csum = ~csum;
	करो अणु
		अगर (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
			वापस IXGBE_ERR_SWFW_SYNC;
		ixgbe_i2c_start(hw);
		/* Device Address and ग_लिखो indication */
		अगर (ixgbe_out_i2c_byte_ack(hw, addr))
			जाओ fail;
		/* Write bits 14:8 */
		अगर (ixgbe_out_i2c_byte_ack(hw, reg_high))
			जाओ fail;
		/* Write bits 7:0 */
		अगर (ixgbe_out_i2c_byte_ack(hw, reg & 0xFF))
			जाओ fail;
		/* Write csum */
		अगर (ixgbe_out_i2c_byte_ack(hw, csum))
			जाओ fail;
		/* Re-start condition */
		ixgbe_i2c_start(hw);
		/* Device Address and पढ़ो indication */
		अगर (ixgbe_out_i2c_byte_ack(hw, addr | 1))
			जाओ fail;
		/* Get upper bits */
		अगर (ixgbe_in_i2c_byte_ack(hw, &high_bits))
			जाओ fail;
		/* Get low bits */
		अगर (ixgbe_in_i2c_byte_ack(hw, &low_bits))
			जाओ fail;
		/* Get csum */
		अगर (ixgbe_घड़ी_in_i2c_byte(hw, &csum_byte))
			जाओ fail;
		/* NACK */
		अगर (ixgbe_घड़ी_out_i2c_bit(hw, false))
			जाओ fail;
		ixgbe_i2c_stop(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		*val = (high_bits << 8) | low_bits;
		वापस 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		retry++;
		अगर (retry < max_retry)
			hw_dbg(hw, "I2C byte read combined error - Retry.\n");
		अन्यथा
			hw_dbg(hw, "I2C byte read combined error.\n");
	पूर्ण जबतक (retry < max_retry);

	वापस IXGBE_ERR_I2C;
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_combined_generic_पूर्णांक - Perक्रमm I2C ग_लिखो combined operation
 *  @hw: poपूर्णांकer to the hardware काष्ठाure
 *  @addr: I2C bus address to ग_लिखो to
 *  @reg: I2C device रेजिस्टर to ग_लिखो to
 *  @val: value to ग_लिखो
 *  @lock: true अगर to take and release semaphore
 *
 *  Returns an error code on error.
 */
s32 ixgbe_ग_लिखो_i2c_combined_generic_पूर्णांक(काष्ठा ixgbe_hw *hw, u8 addr,
					 u16 reg, u16 val, bool lock)
अणु
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	पूर्णांक max_retry = 1;
	पूर्णांक retry = 0;
	u8 reg_high;
	u8 csum;

	reg_high = (reg >> 7) & 0xFE;   /* Indicate ग_लिखो combined */
	csum = ixgbe_ones_comp_byte_add(reg_high, reg & 0xFF);
	csum = ixgbe_ones_comp_byte_add(csum, val >> 8);
	csum = ixgbe_ones_comp_byte_add(csum, val & 0xFF);
	csum = ~csum;
	करो अणु
		अगर (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
			वापस IXGBE_ERR_SWFW_SYNC;
		ixgbe_i2c_start(hw);
		/* Device Address and ग_लिखो indication */
		अगर (ixgbe_out_i2c_byte_ack(hw, addr))
			जाओ fail;
		/* Write bits 14:8 */
		अगर (ixgbe_out_i2c_byte_ack(hw, reg_high))
			जाओ fail;
		/* Write bits 7:0 */
		अगर (ixgbe_out_i2c_byte_ack(hw, reg & 0xFF))
			जाओ fail;
		/* Write data 15:8 */
		अगर (ixgbe_out_i2c_byte_ack(hw, val >> 8))
			जाओ fail;
		/* Write data 7:0 */
		अगर (ixgbe_out_i2c_byte_ack(hw, val & 0xFF))
			जाओ fail;
		/* Write csum */
		अगर (ixgbe_out_i2c_byte_ack(hw, csum))
			जाओ fail;
		ixgbe_i2c_stop(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		वापस 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		retry++;
		अगर (retry < max_retry)
			hw_dbg(hw, "I2C byte write combined error - Retry.\n");
		अन्यथा
			hw_dbg(hw, "I2C byte write combined error.\n");
	पूर्ण जबतक (retry < max_retry);

	वापस IXGBE_ERR_I2C;
पूर्ण

/**
 *  ixgbe_probe_phy - Probe a single address क्रम a PHY
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @phy_addr: PHY address to probe
 *
 *  Returns true अगर PHY found
 **/
अटल bool ixgbe_probe_phy(काष्ठा ixgbe_hw *hw, u16 phy_addr)
अणु
	u16 ext_ability = 0;

	hw->phy.mdio.prtad = phy_addr;
	अगर (mdio45_probe(&hw->phy.mdio, phy_addr) != 0)
		वापस false;

	अगर (ixgbe_get_phy_id(hw))
		वापस false;

	hw->phy.type = ixgbe_get_phy_type_from_id(hw->phy.id);

	अगर (hw->phy.type == ixgbe_phy_unknown) अणु
		hw->phy.ops.पढ़ो_reg(hw,
				     MDIO_PMA_EXTABLE,
				     MDIO_MMD_PMAPMD,
				     &ext_ability);
		अगर (ext_ability &
		    (MDIO_PMA_EXTABLE_10GBT |
		     MDIO_PMA_EXTABLE_1000BT))
			hw->phy.type = ixgbe_phy_cu_unknown;
		अन्यथा
			hw->phy.type = ixgbe_phy_generic;
	पूर्ण

	वापस true;
पूर्ण

/**
 *  ixgbe_identअगरy_phy_generic - Get physical layer module
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Determines the physical layer module found on the current adapter.
 **/
s32 ixgbe_identअगरy_phy_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 phy_addr;
	u32 status = IXGBE_ERR_PHY_ADDR_INVALID;

	अगर (!hw->phy.phy_semaphore_mask) अणु
		अगर (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
		अन्यथा
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;
	पूर्ण

	अगर (hw->phy.type != ixgbe_phy_unknown)
		वापस 0;

	अगर (hw->phy.nw_mng_अगर_sel) अणु
		phy_addr = (hw->phy.nw_mng_अगर_sel &
			    IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD) >>
			   IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT;
		अगर (ixgbe_probe_phy(hw, phy_addr))
			वापस 0;
		अन्यथा
			वापस IXGBE_ERR_PHY_ADDR_INVALID;
	पूर्ण

	क्रम (phy_addr = 0; phy_addr < IXGBE_MAX_PHY_ADDR; phy_addr++) अणु
		अगर (ixgbe_probe_phy(hw, phy_addr)) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Certain media types करो not have a phy so an address will not
	 * be found and the code will take this path.  Caller has to
	 * decide अगर it is an error or not.
	 */
	अगर (status)
		hw->phy.mdio.prtad = MDIO_PRTAD_NONE;

	वापस status;
पूर्ण

/**
 * ixgbe_check_reset_blocked - check status of MNG FW veto bit
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This function checks the MMNGC.MNG_VETO bit to see अगर there are
 * any स्थिरraपूर्णांकs on link from manageability.  For MAC's that don't
 * have this bit just वापस false since the link can not be blocked
 * via this method.
 **/
bool ixgbe_check_reset_blocked(काष्ठा ixgbe_hw *hw)
अणु
	u32 mmngc;

	/* If we करोn't have this bit, it can't be blocking */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस false;

	mmngc = IXGBE_READ_REG(hw, IXGBE_MMNGC);
	अगर (mmngc & IXGBE_MMNGC_MNG_VETO) अणु
		hw_dbg(hw, "MNG_VETO bit detected.\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 *  ixgbe_get_phy_id - Get the phy type
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 **/
अटल s32 ixgbe_get_phy_id(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 phy_id_high = 0;
	u16 phy_id_low = 0;

	status = hw->phy.ops.पढ़ो_reg(hw, MDIO_DEVID1, MDIO_MMD_PMAPMD,
				      &phy_id_high);

	अगर (!status) अणु
		hw->phy.id = (u32)(phy_id_high << 16);
		status = hw->phy.ops.पढ़ो_reg(hw, MDIO_DEVID2, MDIO_MMD_PMAPMD,
					      &phy_id_low);
		hw->phy.id |= (u32)(phy_id_low & IXGBE_PHY_REVISION_MASK);
		hw->phy.revision = (u32)(phy_id_low & ~IXGBE_PHY_REVISION_MASK);
	पूर्ण
	वापस status;
पूर्ण

/**
 *  ixgbe_get_phy_type_from_id - Get the phy type
 *  @phy_id: hardware phy id
 *
 **/
अटल क्रमागत ixgbe_phy_type ixgbe_get_phy_type_from_id(u32 phy_id)
अणु
	क्रमागत ixgbe_phy_type phy_type;

	चयन (phy_id) अणु
	हाल TN1010_PHY_ID:
		phy_type = ixgbe_phy_tn;
		अवरोध;
	हाल X550_PHY_ID2:
	हाल X550_PHY_ID3:
	हाल X540_PHY_ID:
		phy_type = ixgbe_phy_aq;
		अवरोध;
	हाल QT2022_PHY_ID:
		phy_type = ixgbe_phy_qt;
		अवरोध;
	हाल ATH_PHY_ID:
		phy_type = ixgbe_phy_nl;
		अवरोध;
	हाल X557_PHY_ID:
	हाल X557_PHY_ID2:
		phy_type = ixgbe_phy_x550em_ext_t;
		अवरोध;
	हाल BCM54616S_E_PHY_ID:
		phy_type = ixgbe_phy_ext_1g_t;
		अवरोध;
	शेष:
		phy_type = ixgbe_phy_unknown;
		अवरोध;
	पूर्ण

	वापस phy_type;
पूर्ण

/**
 *  ixgbe_reset_phy_generic - Perक्रमms a PHY reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_reset_phy_generic(काष्ठा ixgbe_hw *hw)
अणु
	u32 i;
	u16 ctrl = 0;
	s32 status = 0;

	अगर (hw->phy.type == ixgbe_phy_unknown)
		status = ixgbe_identअगरy_phy_generic(hw);

	अगर (status != 0 || hw->phy.type == ixgbe_phy_none)
		वापस status;

	/* Don't reset PHY if it's shut करोwn due to overtemp. */
	अगर (!hw->phy.reset_अगर_overtemp &&
	    (IXGBE_ERR_OVERTEMP == hw->phy.ops.check_overtemp(hw)))
		वापस 0;

	/* Blocked by MNG FW so bail */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	/*
	 * Perक्रमm soft PHY reset to the PHY_XS.
	 * This will cause a soft reset to the PHY
	 */
	hw->phy.ops.ग_लिखो_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_PHYXS,
			      MDIO_CTRL1_RESET);

	/*
	 * Poll क्रम reset bit to self-clear indicating reset is complete.
	 * Some PHYs could take up to 3 seconds to complete and need about
	 * 1.7 usec delay after the reset is complete.
	 */
	क्रम (i = 0; i < 30; i++) अणु
		msleep(100);
		अगर (hw->phy.type == ixgbe_phy_x550em_ext_t) अणु
			status = hw->phy.ops.पढ़ो_reg(hw,
						  IXGBE_MDIO_TX_VENDOR_ALARMS_3,
						  MDIO_MMD_PMAPMD, &ctrl);
			अगर (status)
				वापस status;

			अगर (ctrl & IXGBE_MDIO_TX_VENDOR_ALARMS_3_RST_MASK) अणु
				udelay(2);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			status = hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1,
						      MDIO_MMD_PHYXS, &ctrl);
			अगर (status)
				वापस status;

			अगर (!(ctrl & MDIO_CTRL1_RESET)) अणु
				udelay(2);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ctrl & MDIO_CTRL1_RESET) अणु
		hw_dbg(hw, "PHY reset polling failed to complete.\n");
		वापस IXGBE_ERR_RESET_FAILED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_phy_reg_mdi - पढ़ो PHY रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit address of PHY रेजिस्टर to पढ़ो
 *  @device_type: 5 bit device type
 *  @phy_data: Poपूर्णांकer to पढ़ो data from PHY रेजिस्टर
 *
 *  Reads a value from a specअगरied PHY रेजिस्टर without the SWFW lock
 **/
s32 ixgbe_पढ़ो_phy_reg_mdi(काष्ठा ixgbe_hw *hw, u32 reg_addr, u32 device_type,
		       u16 *phy_data)
अणु
	u32 i, data, command;

	/* Setup and ग_लिखो the address cycle command */
	command = ((reg_addr << IXGBE_MSCA_NP_ADDR_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.prtad << IXGBE_MSCA_PHY_ADDR_SHIFT) |
		   (IXGBE_MSCA_ADDR_CYCLE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WRITE_REG(hw, IXGBE_MSCA, command);

	/* Check every 10 usec to see अगर the address cycle completed.
	 * The MDI Command bit will clear when the operation is
	 * complete
	 */
	क्रम (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) अणु
		udelay(10);

		command = IXGBE_READ_REG(hw, IXGBE_MSCA);
		अगर ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
				अवरोध;
	पूर्ण


	अगर ((command & IXGBE_MSCA_MDI_COMMAND) != 0) अणु
		hw_dbg(hw, "PHY address command did not complete.\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	/* Address cycle complete, setup and ग_लिखो the पढ़ो
	 * command
	 */
	command = ((reg_addr << IXGBE_MSCA_NP_ADDR_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.prtad << IXGBE_MSCA_PHY_ADDR_SHIFT) |
		   (IXGBE_MSCA_READ | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WRITE_REG(hw, IXGBE_MSCA, command);

	/* Check every 10 usec to see अगर the address cycle
	 * completed. The MDI Command bit will clear when the
	 * operation is complete
	 */
	क्रम (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) अणु
		udelay(10);

		command = IXGBE_READ_REG(hw, IXGBE_MSCA);
		अगर ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	अगर ((command & IXGBE_MSCA_MDI_COMMAND) != 0) अणु
		hw_dbg(hw, "PHY read command didn't complete\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	/* Read operation is complete.  Get the data
	 * from MSRWD
	 */
	data = IXGBE_READ_REG(hw, IXGBE_MSRWD);
	data >>= IXGBE_MSRWD_READ_DATA_SHIFT;
	*phy_data = (u16)(data);

	वापस 0;
पूर्ण

/**
 *  ixgbe_पढ़ो_phy_reg_generic - Reads a value from a specअगरied PHY रेजिस्टर
 *  using the SWFW lock - this function is needed in most हालs
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit address of PHY रेजिस्टर to पढ़ो
 *  @device_type: 5 bit device type
 *  @phy_data: Poपूर्णांकer to पढ़ो data from PHY रेजिस्टर
 **/
s32 ixgbe_पढ़ो_phy_reg_generic(काष्ठा ixgbe_hw *hw, u32 reg_addr,
			       u32 device_type, u16 *phy_data)
अणु
	s32 status;
	u32 gssr = hw->phy.phy_semaphore_mask;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, gssr) == 0) अणु
		status = ixgbe_पढ़ो_phy_reg_mdi(hw, reg_addr, device_type,
						phy_data);
		hw->mac.ops.release_swfw_sync(hw, gssr);
	पूर्ण अन्यथा अणु
		वापस IXGBE_ERR_SWFW_SYNC;
	पूर्ण

	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_phy_reg_mdi - Writes a value to specअगरied PHY रेजिस्टर
 *  without SWFW lock
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 5 bit device type
 *  @phy_data: Data to ग_लिखो to the PHY रेजिस्टर
 **/
s32 ixgbe_ग_लिखो_phy_reg_mdi(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				u32 device_type, u16 phy_data)
अणु
	u32 i, command;

	/* Put the data in the MDI single पढ़ो and ग_लिखो data रेजिस्टर*/
	IXGBE_WRITE_REG(hw, IXGBE_MSRWD, (u32)phy_data);

	/* Setup and ग_लिखो the address cycle command */
	command = ((reg_addr << IXGBE_MSCA_NP_ADDR_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.prtad << IXGBE_MSCA_PHY_ADDR_SHIFT) |
		   (IXGBE_MSCA_ADDR_CYCLE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WRITE_REG(hw, IXGBE_MSCA, command);

	/*
	 * Check every 10 usec to see अगर the address cycle completed.
	 * The MDI Command bit will clear when the operation is
	 * complete
	 */
	क्रम (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) अणु
		udelay(10);

		command = IXGBE_READ_REG(hw, IXGBE_MSCA);
		अगर ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	अगर ((command & IXGBE_MSCA_MDI_COMMAND) != 0) अणु
		hw_dbg(hw, "PHY address cmd didn't complete\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	/*
	 * Address cycle complete, setup and ग_लिखो the ग_लिखो
	 * command
	 */
	command = ((reg_addr << IXGBE_MSCA_NP_ADDR_SHIFT)  |
		   (device_type << IXGBE_MSCA_DEV_TYPE_SHIFT) |
		   (hw->phy.mdio.prtad << IXGBE_MSCA_PHY_ADDR_SHIFT) |
		   (IXGBE_MSCA_WRITE | IXGBE_MSCA_MDI_COMMAND));

	IXGBE_WRITE_REG(hw, IXGBE_MSCA, command);

	/* Check every 10 usec to see अगर the address cycle
	 * completed. The MDI Command bit will clear when the
	 * operation is complete
	 */
	क्रम (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) अणु
		udelay(10);

		command = IXGBE_READ_REG(hw, IXGBE_MSCA);
		अगर ((command & IXGBE_MSCA_MDI_COMMAND) == 0)
			अवरोध;
	पूर्ण

	अगर ((command & IXGBE_MSCA_MDI_COMMAND) != 0) अणु
		hw_dbg(hw, "PHY write cmd didn't complete\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_ग_लिखो_phy_reg_generic - Writes a value to specअगरied PHY रेजिस्टर
 *  using SWFW lock- this function is needed in most हालs
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 5 bit device type
 *  @phy_data: Data to ग_लिखो to the PHY रेजिस्टर
 **/
s32 ixgbe_ग_लिखो_phy_reg_generic(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				u32 device_type, u16 phy_data)
अणु
	s32 status;
	u32 gssr = hw->phy.phy_semaphore_mask;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, gssr) == 0) अणु
		status = ixgbe_ग_लिखो_phy_reg_mdi(hw, reg_addr, device_type,
						 phy_data);
		hw->mac.ops.release_swfw_sync(hw, gssr);
	पूर्ण अन्यथा अणु
		वापस IXGBE_ERR_SWFW_SYNC;
	पूर्ण

	वापस status;
पूर्ण

#घोषणा IXGBE_HW_READ_REG(addr) IXGBE_READ_REG(hw, addr)

/**
 *  ixgbe_msca_cmd - Write the command रेजिस्टर and poll क्रम completion/समयout
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @cmd: command रेजिस्टर value to ग_लिखो
 **/
अटल s32 ixgbe_msca_cmd(काष्ठा ixgbe_hw *hw, u32 cmd)
अणु
	IXGBE_WRITE_REG(hw, IXGBE_MSCA, cmd);

	वापस पढ़ोx_poll_समयout(IXGBE_HW_READ_REG, IXGBE_MSCA, cmd,
				  !(cmd & IXGBE_MSCA_MDI_COMMAND), 10,
				  10 * IXGBE_MDIO_COMMAND_TIMEOUT);
पूर्ण

/**
 *  ixgbe_mii_bus_पढ़ो_generic - Read a clause 22/45 रेजिस्टर with gssr flags
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @addr: address
 *  @regnum: रेजिस्टर number
 *  @gssr: semaphore flags to acquire
 **/
अटल s32 ixgbe_mii_bus_पढ़ो_generic(काष्ठा ixgbe_hw *hw, पूर्णांक addr,
				      पूर्णांक regnum, u32 gssr)
अणु
	u32 hwaddr, cmd;
	s32 data;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, gssr))
		वापस -EBUSY;

	hwaddr = addr << IXGBE_MSCA_PHY_ADDR_SHIFT;
	अगर (regnum & MII_ADDR_C45) अणु
		hwaddr |= regnum & GENMASK(21, 0);
		cmd = hwaddr | IXGBE_MSCA_ADDR_CYCLE | IXGBE_MSCA_MDI_COMMAND;
	पूर्ण अन्यथा अणु
		hwaddr |= (regnum & GENMASK(5, 0)) << IXGBE_MSCA_DEV_TYPE_SHIFT;
		cmd = hwaddr | IXGBE_MSCA_OLD_PROTOCOL |
			IXGBE_MSCA_READ_AUTOINC | IXGBE_MSCA_MDI_COMMAND;
	पूर्ण

	data = ixgbe_msca_cmd(hw, cmd);
	अगर (data < 0)
		जाओ mii_bus_पढ़ो_करोne;

	/* For a clause 45 access the address cycle just completed, we still
	 * need to करो the पढ़ो command, otherwise just get the data
	 */
	अगर (!(regnum & MII_ADDR_C45))
		जाओ करो_mii_bus_पढ़ो;

	cmd = hwaddr | IXGBE_MSCA_READ | IXGBE_MSCA_MDI_COMMAND;
	data = ixgbe_msca_cmd(hw, cmd);
	अगर (data < 0)
		जाओ mii_bus_पढ़ो_करोne;

करो_mii_bus_पढ़ो:
	data = IXGBE_READ_REG(hw, IXGBE_MSRWD);
	data = (data >> IXGBE_MSRWD_READ_DATA_SHIFT) & GENMASK(16, 0);

mii_bus_पढ़ो_करोne:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	वापस data;
पूर्ण

/**
 *  ixgbe_mii_bus_ग_लिखो_generic - Write a clause 22/45 रेजिस्टर with gssr flags
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @addr: address
 *  @regnum: रेजिस्टर number
 *  @val: value to ग_लिखो
 *  @gssr: semaphore flags to acquire
 **/
अटल s32 ixgbe_mii_bus_ग_लिखो_generic(काष्ठा ixgbe_hw *hw, पूर्णांक addr,
				       पूर्णांक regnum, u16 val, u32 gssr)
अणु
	u32 hwaddr, cmd;
	s32 err;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, gssr))
		वापस -EBUSY;

	IXGBE_WRITE_REG(hw, IXGBE_MSRWD, (u32)val);

	hwaddr = addr << IXGBE_MSCA_PHY_ADDR_SHIFT;
	अगर (regnum & MII_ADDR_C45) अणु
		hwaddr |= regnum & GENMASK(21, 0);
		cmd = hwaddr | IXGBE_MSCA_ADDR_CYCLE | IXGBE_MSCA_MDI_COMMAND;
	पूर्ण अन्यथा अणु
		hwaddr |= (regnum & GENMASK(5, 0)) << IXGBE_MSCA_DEV_TYPE_SHIFT;
		cmd = hwaddr | IXGBE_MSCA_OLD_PROTOCOL | IXGBE_MSCA_WRITE |
			IXGBE_MSCA_MDI_COMMAND;
	पूर्ण

	/* For clause 45 this is an address cycle, क्रम clause 22 this is the
	 * entire transaction
	 */
	err = ixgbe_msca_cmd(hw, cmd);
	अगर (err < 0 || !(regnum & MII_ADDR_C45))
		जाओ mii_bus_ग_लिखो_करोne;

	cmd = hwaddr | IXGBE_MSCA_WRITE | IXGBE_MSCA_MDI_COMMAND;
	err = ixgbe_msca_cmd(hw, cmd);

mii_bus_ग_लिखो_करोne:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	वापस err;
पूर्ण

/**
 *  ixgbe_mii_bus_पढ़ो - Read a clause 22/45 रेजिस्टर
 *  @bus: poपूर्णांकer to mii_bus काष्ठाure which poपूर्णांकs to our driver निजी
 *  @addr: address
 *  @regnum: रेजिस्टर number
 **/
अटल s32 ixgbe_mii_bus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा ixgbe_adapter *adapter = bus->priv;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 gssr = hw->phy.phy_semaphore_mask;

	वापस ixgbe_mii_bus_पढ़ो_generic(hw, addr, regnum, gssr);
पूर्ण

/**
 *  ixgbe_mii_bus_ग_लिखो - Write a clause 22/45 रेजिस्टर
 *  @bus: poपूर्णांकer to mii_bus काष्ठाure which poपूर्णांकs to our driver निजी
 *  @addr: address
 *  @regnum: रेजिस्टर number
 *  @val: value to ग_लिखो
 **/
अटल s32 ixgbe_mii_bus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum,
			       u16 val)
अणु
	काष्ठा ixgbe_adapter *adapter = bus->priv;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 gssr = hw->phy.phy_semaphore_mask;

	वापस ixgbe_mii_bus_ग_लिखो_generic(hw, addr, regnum, val, gssr);
पूर्ण

/**
 *  ixgbe_x550em_a_mii_bus_पढ़ो - Read a clause 22/45 रेजिस्टर on x550em_a
 *  @bus: poपूर्णांकer to mii_bus काष्ठाure which poपूर्णांकs to our driver निजी
 *  @addr: address
 *  @regnum: रेजिस्टर number
 **/
अटल s32 ixgbe_x550em_a_mii_bus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr,
				       पूर्णांक regnum)
अणु
	काष्ठा ixgbe_adapter *adapter = bus->priv;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 gssr = hw->phy.phy_semaphore_mask;

	gssr |= IXGBE_GSSR_TOKEN_SM | IXGBE_GSSR_PHY0_SM;
	वापस ixgbe_mii_bus_पढ़ो_generic(hw, addr, regnum, gssr);
पूर्ण

/**
 *  ixgbe_x550em_a_mii_bus_ग_लिखो - Write a clause 22/45 रेजिस्टर on x550em_a
 *  @bus: poपूर्णांकer to mii_bus काष्ठाure which poपूर्णांकs to our driver निजी
 *  @addr: address
 *  @regnum: रेजिस्टर number
 *  @val: value to ग_लिखो
 **/
अटल s32 ixgbe_x550em_a_mii_bus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr,
					पूर्णांक regnum, u16 val)
अणु
	काष्ठा ixgbe_adapter *adapter = bus->priv;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 gssr = hw->phy.phy_semaphore_mask;

	gssr |= IXGBE_GSSR_TOKEN_SM | IXGBE_GSSR_PHY0_SM;
	वापस ixgbe_mii_bus_ग_लिखो_generic(hw, addr, regnum, val, gssr);
पूर्ण

/**
 * ixgbe_get_first_secondary_devfn - get first device करोwnstream of root port
 * @devfn: PCI_DEVFN of root port on करोमुख्य 0, bus 0
 *
 * Returns pci_dev poपूर्णांकer to PCI_DEVFN(0, 0) on subordinate side of root
 * on करोमुख्य 0, bus 0, devfn = 'devfn'
 **/
अटल काष्ठा pci_dev *ixgbe_get_first_secondary_devfn(अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_dev *rp_pdev;
	पूर्णांक bus;

	rp_pdev = pci_get_करोमुख्य_bus_and_slot(0, 0, devfn);
	अगर (rp_pdev && rp_pdev->subordinate) अणु
		bus = rp_pdev->subordinate->number;
		वापस pci_get_करोमुख्य_bus_and_slot(0, bus, 0);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ixgbe_x550em_a_has_mii - is this the first ixgbe x550em_a PCI function?
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Returns true अगर hw poपूर्णांकs to lowest numbered PCI B:D.F x550_em_a device in
 * the SoC.  There are up to 4 MACs sharing a single MDIO bus on the x550em_a,
 * but we only want to रेजिस्टर one MDIO bus.
 **/
अटल bool ixgbe_x550em_a_has_mii(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा pci_dev *func0_pdev;

	/* For the C3000 family of SoCs (x550em_a) the पूर्णांकernal ixgbe devices
	 * are always करोwnstream of root ports @ 0000:00:16.0 & 0000:00:17.0
	 * It's not valid क्रम function 0 to be disabled and function 1 is up,
	 * so the lowest numbered ixgbe dev will be device 0 function 0 on one
	 * of those two root ports
	 */
	func0_pdev = ixgbe_get_first_secondary_devfn(PCI_DEVFN(0x16, 0));
	अगर (func0_pdev) अणु
		अगर (func0_pdev == pdev)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
	func0_pdev = ixgbe_get_first_secondary_devfn(PCI_DEVFN(0x17, 0));
	अगर (func0_pdev == pdev)
		वापस true;

	वापस false;
पूर्ण

/**
 * ixgbe_mii_bus_init - mii_bus काष्ठाure setup
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Returns 0 on success, negative on failure
 *
 * ixgbe_mii_bus_init initializes a mii_bus काष्ठाure in adapter
 **/
s32 ixgbe_mii_bus_init(काष्ठा ixgbe_hw *hw)
अणु
	s32 (*ग_लिखो)(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum, u16 val);
	s32 (*पढ़ो)(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum);
	काष्ठा ixgbe_adapter *adapter = hw->back;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा device *dev = &adapter->netdev->dev;
	काष्ठा mii_bus *bus;

	चयन (hw->device_id) अणु
	/* C3000 SoCs */
	हाल IXGBE_DEV_ID_X550EM_A_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR_L:
	हाल IXGBE_DEV_ID_X550EM_A_SFP_N:
	हाल IXGBE_DEV_ID_X550EM_A_SGMII:
	हाल IXGBE_DEV_ID_X550EM_A_SGMII_L:
	हाल IXGBE_DEV_ID_X550EM_A_10G_T:
	हाल IXGBE_DEV_ID_X550EM_A_SFP:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		अगर (!ixgbe_x550em_a_has_mii(hw))
			वापस 0;
		पढ़ो = &ixgbe_x550em_a_mii_bus_पढ़ो;
		ग_लिखो = &ixgbe_x550em_a_mii_bus_ग_लिखो;
		अवरोध;
	शेष:
		पढ़ो = &ixgbe_mii_bus_पढ़ो;
		ग_लिखो = &ixgbe_mii_bus_ग_लिखो;
		अवरोध;
	पूर्ण

	bus = devm_mdiobus_alloc(dev);
	अगर (!bus)
		वापस -ENOMEM;

	bus->पढ़ो = पढ़ो;
	bus->ग_लिखो = ग_लिखो;

	/* Use the position of the device in the PCI hierarchy as the id */
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mdio-%s", ixgbe_driver_name,
		 pci_name(pdev));

	bus->name = "ixgbe-mdio";
	bus->priv = adapter;
	bus->parent = dev;
	bus->phy_mask = GENMASK(31, 0);

	/* Support clause 22/45 natively.  ixgbe_probe() sets MDIO_EMULATE_C22
	 * unक्रमtunately that causes some clause 22 frames to be sent with
	 * clause 45 addressing.  We करोn't want that.
	 */
	hw->phy.mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_SUPPORTS_C22;

	adapter->mii_bus = bus;
	वापस mdiobus_रेजिस्टर(bus);
पूर्ण

/**
 *  ixgbe_setup_phy_link_generic - Set and restart स्वतःneg
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Restart स्वतःnegotiation and PHY and रुकोs क्रम completion.
 **/
s32 ixgbe_setup_phy_link_generic(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = 0;
	u16 स्वतःneg_reg = IXGBE_MII_AUTONEG_REG;
	bool स्वतःneg = false;
	ixgbe_link_speed speed;

	ixgbe_get_copper_link_capabilities_generic(hw, &speed, &स्वतःneg);

	/* Set or unset स्वतः-negotiation 10G advertisement */
	hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_10GBT_CTRL, MDIO_MMD_AN, &स्वतःneg_reg);

	स्वतःneg_reg &= ~MDIO_AN_10GBT_CTRL_ADV10G;
	अगर ((hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_10GB_FULL) &&
	    (speed & IXGBE_LINK_SPEED_10GB_FULL))
		स्वतःneg_reg |= MDIO_AN_10GBT_CTRL_ADV10G;

	hw->phy.ops.ग_लिखो_reg(hw, MDIO_AN_10GBT_CTRL, MDIO_MMD_AN, स्वतःneg_reg);

	hw->phy.ops.पढ़ो_reg(hw, IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG,
			     MDIO_MMD_AN, &स्वतःneg_reg);

	अगर (hw->mac.type == ixgbe_mac_X550) अणु
		/* Set or unset स्वतः-negotiation 5G advertisement */
		स्वतःneg_reg &= ~IXGBE_MII_5GBASE_T_ADVERTISE;
		अगर ((hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_5GB_FULL) &&
		    (speed & IXGBE_LINK_SPEED_5GB_FULL))
			स्वतःneg_reg |= IXGBE_MII_5GBASE_T_ADVERTISE;

		/* Set or unset स्वतः-negotiation 2.5G advertisement */
		स्वतःneg_reg &= ~IXGBE_MII_2_5GBASE_T_ADVERTISE;
		अगर ((hw->phy.स्वतःneg_advertised &
		     IXGBE_LINK_SPEED_2_5GB_FULL) &&
		    (speed & IXGBE_LINK_SPEED_2_5GB_FULL))
			स्वतःneg_reg |= IXGBE_MII_2_5GBASE_T_ADVERTISE;
	पूर्ण

	/* Set or unset स्वतः-negotiation 1G advertisement */
	स्वतःneg_reg &= ~IXGBE_MII_1GBASE_T_ADVERTISE;
	अगर ((hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_1GB_FULL) &&
	    (speed & IXGBE_LINK_SPEED_1GB_FULL))
		स्वतःneg_reg |= IXGBE_MII_1GBASE_T_ADVERTISE;

	hw->phy.ops.ग_लिखो_reg(hw, IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG,
			      MDIO_MMD_AN, स्वतःneg_reg);

	/* Set or unset स्वतः-negotiation 100M advertisement */
	hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_ADVERTISE, MDIO_MMD_AN, &स्वतःneg_reg);

	स्वतःneg_reg &= ~(ADVERTISE_100FULL | ADVERTISE_100HALF);
	अगर ((hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_100_FULL) &&
	    (speed & IXGBE_LINK_SPEED_100_FULL))
		स्वतःneg_reg |= ADVERTISE_100FULL;

	hw->phy.ops.ग_लिखो_reg(hw, MDIO_AN_ADVERTISE, MDIO_MMD_AN, स्वतःneg_reg);

	/* Blocked by MNG FW so करोn't reset PHY */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	/* Restart PHY स्वतःnegotiation and रुको क्रम completion */
	hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1,
			     MDIO_MMD_AN, &स्वतःneg_reg);

	स्वतःneg_reg |= MDIO_AN_CTRL1_RESTART;

	hw->phy.ops.ग_लिखो_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_AN, स्वतःneg_reg);

	वापस status;
पूर्ण

/**
 *  ixgbe_setup_phy_link_speed_generic - Sets the स्वतः advertised capabilities
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: new link speed
 *  @स्वतःneg_रुको_to_complete: unused
 **/
s32 ixgbe_setup_phy_link_speed_generic(काष्ठा ixgbe_hw *hw,
				       ixgbe_link_speed speed,
				       bool स्वतःneg_रुको_to_complete)
अणु
	/* Clear स्वतःneg_advertised and set new values based on input link
	 * speed.
	 */
	hw->phy.स्वतःneg_advertised = 0;

	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_5GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_5GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_2_5GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_2_5GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	अगर (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_100_FULL;

	अगर (speed & IXGBE_LINK_SPEED_10_FULL)
		hw->phy.स्वतःneg_advertised |= IXGBE_LINK_SPEED_10_FULL;

	/* Setup link based on the new speed settings */
	अगर (hw->phy.ops.setup_link)
		hw->phy.ops.setup_link(hw);

	वापस 0;
पूर्ण

/**
 * ixgbe_get_copper_speeds_supported - Get copper link speed from phy
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Determines the supported link capabilities by पढ़ोing the PHY स्वतः
 * negotiation रेजिस्टर.
 */
अटल s32 ixgbe_get_copper_speeds_supported(काष्ठा ixgbe_hw *hw)
अणु
	u16 speed_ability;
	s32 status;

	status = hw->phy.ops.पढ़ो_reg(hw, MDIO_SPEED, MDIO_MMD_PMAPMD,
				      &speed_ability);
	अगर (status)
		वापस status;

	अगर (speed_ability & MDIO_SPEED_10G)
		hw->phy.speeds_supported |= IXGBE_LINK_SPEED_10GB_FULL;
	अगर (speed_ability & MDIO_PMA_SPEED_1000)
		hw->phy.speeds_supported |= IXGBE_LINK_SPEED_1GB_FULL;
	अगर (speed_ability & MDIO_PMA_SPEED_100)
		hw->phy.speeds_supported |= IXGBE_LINK_SPEED_100_FULL;

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X550:
		hw->phy.speeds_supported |= IXGBE_LINK_SPEED_2_5GB_FULL;
		hw->phy.speeds_supported |= IXGBE_LINK_SPEED_5GB_FULL;
		अवरोध;
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		hw->phy.speeds_supported &= ~IXGBE_LINK_SPEED_100_FULL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_get_copper_link_capabilities_generic - Determines link capabilities
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: poपूर्णांकer to link speed
 * @स्वतःneg: boolean स्वतः-negotiation value
 */
s32 ixgbe_get_copper_link_capabilities_generic(काष्ठा ixgbe_hw *hw,
					       ixgbe_link_speed *speed,
					       bool *स्वतःneg)
अणु
	s32 status = 0;

	*स्वतःneg = true;
	अगर (!hw->phy.speeds_supported)
		status = ixgbe_get_copper_speeds_supported(hw);

	*speed = hw->phy.speeds_supported;
	वापस status;
पूर्ण

/**
 *  ixgbe_check_phy_link_tnx - Determine link and speed status
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: link speed
 *  @link_up: status of link
 *
 *  Reads the VS1 रेजिस्टर to determine अगर link is up and the current speed क्रम
 *  the PHY.
 **/
s32 ixgbe_check_phy_link_tnx(काष्ठा ixgbe_hw *hw, ixgbe_link_speed *speed,
			     bool *link_up)
अणु
	s32 status;
	u32 समय_out;
	u32 max_समय_out = 10;
	u16 phy_link = 0;
	u16 phy_speed = 0;
	u16 phy_data = 0;

	/* Initialize speed and link to शेष हाल */
	*link_up = false;
	*speed = IXGBE_LINK_SPEED_10GB_FULL;

	/*
	 * Check current speed and link status of the PHY रेजिस्टर.
	 * This is a venकरोr specअगरic रेजिस्टर and may have to
	 * be changed क्रम other copper PHYs.
	 */
	क्रम (समय_out = 0; समय_out < max_समय_out; समय_out++) अणु
		udelay(10);
		status = hw->phy.ops.पढ़ो_reg(hw,
					      MDIO_STAT1,
					      MDIO_MMD_VEND1,
					      &phy_data);
		phy_link = phy_data &
			    IXGBE_MDIO_VENDOR_SPECIFIC_1_LINK_STATUS;
		phy_speed = phy_data &
			    IXGBE_MDIO_VENDOR_SPECIFIC_1_SPEED_STATUS;
		अगर (phy_link == IXGBE_MDIO_VENDOR_SPECIFIC_1_LINK_STATUS) अणु
			*link_up = true;
			अगर (phy_speed ==
			    IXGBE_MDIO_VENDOR_SPECIFIC_1_SPEED_STATUS)
				*speed = IXGBE_LINK_SPEED_1GB_FULL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 *	ixgbe_setup_phy_link_tnx - Set and restart स्वतःneg
 *	@hw: poपूर्णांकer to hardware काष्ठाure
 *
 *	Restart स्वतःnegotiation and PHY and रुकोs क्रम completion.
 *      This function always वापसs success, this is nessary since
 *	it is called via a function poपूर्णांकer that could call other
 *	functions that could वापस an error.
 **/
s32 ixgbe_setup_phy_link_tnx(काष्ठा ixgbe_hw *hw)
अणु
	u16 स्वतःneg_reg = IXGBE_MII_AUTONEG_REG;
	bool स्वतःneg = false;
	ixgbe_link_speed speed;

	ixgbe_get_copper_link_capabilities_generic(hw, &speed, &स्वतःneg);

	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL) अणु
		/* Set or unset स्वतः-negotiation 10G advertisement */
		hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_10GBT_CTRL,
				     MDIO_MMD_AN,
				     &स्वतःneg_reg);

		स्वतःneg_reg &= ~MDIO_AN_10GBT_CTRL_ADV10G;
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			स्वतःneg_reg |= MDIO_AN_10GBT_CTRL_ADV10G;

		hw->phy.ops.ग_लिखो_reg(hw, MDIO_AN_10GBT_CTRL,
				      MDIO_MMD_AN,
				      स्वतःneg_reg);
	पूर्ण

	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL) अणु
		/* Set or unset स्वतः-negotiation 1G advertisement */
		hw->phy.ops.पढ़ो_reg(hw, IXGBE_MII_AUTONEG_XNP_TX_REG,
				     MDIO_MMD_AN,
				     &स्वतःneg_reg);

		स्वतःneg_reg &= ~IXGBE_MII_1GBASE_T_ADVERTISE_XNP_TX;
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_1GB_FULL)
			स्वतःneg_reg |= IXGBE_MII_1GBASE_T_ADVERTISE_XNP_TX;

		hw->phy.ops.ग_लिखो_reg(hw, IXGBE_MII_AUTONEG_XNP_TX_REG,
				      MDIO_MMD_AN,
				      स्वतःneg_reg);
	पूर्ण

	अगर (speed & IXGBE_LINK_SPEED_100_FULL) अणु
		/* Set or unset स्वतः-negotiation 100M advertisement */
		hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_ADVERTISE,
				     MDIO_MMD_AN,
				     &स्वतःneg_reg);

		स्वतःneg_reg &= ~(ADVERTISE_100FULL |
				 ADVERTISE_100HALF);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			स्वतःneg_reg |= ADVERTISE_100FULL;

		hw->phy.ops.ग_लिखो_reg(hw, MDIO_AN_ADVERTISE,
				      MDIO_MMD_AN,
				      स्वतःneg_reg);
	पूर्ण

	/* Blocked by MNG FW so करोn't reset PHY */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	/* Restart PHY स्वतःnegotiation and रुको क्रम completion */
	hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1,
			     MDIO_MMD_AN, &स्वतःneg_reg);

	स्वतःneg_reg |= MDIO_AN_CTRL1_RESTART;

	hw->phy.ops.ग_लिखो_reg(hw, MDIO_CTRL1,
			      MDIO_MMD_AN, स्वतःneg_reg);
	वापस 0;
पूर्ण

/**
 *  ixgbe_reset_phy_nl - Perक्रमms a PHY reset
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
s32 ixgbe_reset_phy_nl(काष्ठा ixgbe_hw *hw)
अणु
	u16 phy_offset, control, eword, edata, block_crc;
	bool end_data = false;
	u16 list_offset, data_offset;
	u16 phy_data = 0;
	s32 ret_val;
	u32 i;

	/* Blocked by MNG FW so bail */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS, &phy_data);

	/* reset the PHY and poll क्रम completion */
	hw->phy.ops.ग_लिखो_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS,
			      (phy_data | MDIO_CTRL1_RESET));

	क्रम (i = 0; i < 100; i++) अणु
		hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1, MDIO_MMD_PHYXS,
				     &phy_data);
		अगर ((phy_data & MDIO_CTRL1_RESET) == 0)
			अवरोध;
		usleep_range(10000, 20000);
	पूर्ण

	अगर ((phy_data & MDIO_CTRL1_RESET) != 0) अणु
		hw_dbg(hw, "PHY reset did not complete.\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	/* Get init offsets */
	ret_val = ixgbe_get_sfp_init_sequence_offsets(hw, &list_offset,
						      &data_offset);
	अगर (ret_val)
		वापस ret_val;

	ret_val = hw->eeprom.ops.पढ़ो(hw, data_offset, &block_crc);
	data_offset++;
	जबतक (!end_data) अणु
		/*
		 * Read control word from PHY init contents offset
		 */
		ret_val = hw->eeprom.ops.पढ़ो(hw, data_offset, &eword);
		अगर (ret_val)
			जाओ err_eeprom;
		control = (eword & IXGBE_CONTROL_MASK_NL) >>
			   IXGBE_CONTROL_SHIFT_NL;
		edata = eword & IXGBE_DATA_MASK_NL;
		चयन (control) अणु
		हाल IXGBE_DELAY_NL:
			data_offset++;
			hw_dbg(hw, "DELAY: %d MS\n", edata);
			usleep_range(edata * 1000, edata * 2000);
			अवरोध;
		हाल IXGBE_DATA_NL:
			hw_dbg(hw, "DATA:\n");
			data_offset++;
			ret_val = hw->eeprom.ops.पढ़ो(hw, data_offset++,
						      &phy_offset);
			अगर (ret_val)
				जाओ err_eeprom;
			क्रम (i = 0; i < edata; i++) अणु
				ret_val = hw->eeprom.ops.पढ़ो(hw, data_offset,
							      &eword);
				अगर (ret_val)
					जाओ err_eeprom;
				hw->phy.ops.ग_लिखो_reg(hw, phy_offset,
						      MDIO_MMD_PMAPMD, eword);
				hw_dbg(hw, "Wrote %4.4x to %4.4x\n", eword,
				       phy_offset);
				data_offset++;
				phy_offset++;
			पूर्ण
			अवरोध;
		हाल IXGBE_CONTROL_NL:
			data_offset++;
			hw_dbg(hw, "CONTROL:\n");
			अगर (edata == IXGBE_CONTROL_EOL_NL) अणु
				hw_dbg(hw, "EOL\n");
				end_data = true;
			पूर्ण अन्यथा अगर (edata == IXGBE_CONTROL_SOL_NL) अणु
				hw_dbg(hw, "SOL\n");
			पूर्ण अन्यथा अणु
				hw_dbg(hw, "Bad control value\n");
				वापस IXGBE_ERR_PHY;
			पूर्ण
			अवरोध;
		शेष:
			hw_dbg(hw, "Bad control type\n");
			वापस IXGBE_ERR_PHY;
		पूर्ण
	पूर्ण

	वापस ret_val;

err_eeprom:
	hw_err(hw, "eeprom read at offset %d failed\n", data_offset);
	वापस IXGBE_ERR_PHY;
पूर्ण

/**
 *  ixgbe_identअगरy_module_generic - Identअगरies module type
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Determines HW type and calls appropriate function.
 **/
s32 ixgbe_identअगरy_module_generic(काष्ठा ixgbe_hw *hw)
अणु
	चयन (hw->mac.ops.get_media_type(hw)) अणु
	हाल ixgbe_media_type_fiber:
		वापस ixgbe_identअगरy_sfp_module_generic(hw);
	हाल ixgbe_media_type_fiber_qsfp:
		वापस ixgbe_identअगरy_qsfp_module_generic(hw);
	शेष:
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		वापस IXGBE_ERR_SFP_NOT_PRESENT;
	पूर्ण

	वापस IXGBE_ERR_SFP_NOT_PRESENT;
पूर्ण

/**
 *  ixgbe_identअगरy_sfp_module_generic - Identअगरies SFP modules
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Searches क्रम and identअगरies the SFP module and assigns appropriate PHY type.
 **/
s32 ixgbe_identअगरy_sfp_module_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;
	s32 status;
	u32 venकरोr_oui = 0;
	क्रमागत ixgbe_sfp_type stored_sfp_type = hw->phy.sfp_type;
	u8 identअगरier = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = अणु0, 0, 0पूर्ण;
	u8 cable_tech = 0;
	u8 cable_spec = 0;
	u16 enक्रमce_sfp = 0;

	अगर (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fiber) अणु
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		वापस IXGBE_ERR_SFP_NOT_PRESENT;
	पूर्ण

	/* LAN ID is needed क्रम sfp_type determination */
	hw->mac.ops.set_lan_id(hw);

	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_IDENTIFIER,
					     &identअगरier);

	अगर (status)
		जाओ err_पढ़ो_i2c_eeprom;

	अगर (identअगरier != IXGBE_SFF_IDENTIFIER_SFP) अणु
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण
	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_1GBE_COMP_CODES,
					     &comp_codes_1g);

	अगर (status)
		जाओ err_पढ़ो_i2c_eeprom;

	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_10GBE_COMP_CODES,
					     &comp_codes_10g);

	अगर (status)
		जाओ err_पढ़ो_i2c_eeprom;
	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_CABLE_TECHNOLOGY,
					     &cable_tech);

	अगर (status)
		जाओ err_पढ़ो_i2c_eeprom;

	 /* ID Module
	  * =========
	  * 0   SFP_DA_CU
	  * 1   SFP_SR
	  * 2   SFP_LR
	  * 3   SFP_DA_CORE0 - 82599-specअगरic
	  * 4   SFP_DA_CORE1 - 82599-specअगरic
	  * 5   SFP_SR/LR_CORE0 - 82599-specअगरic
	  * 6   SFP_SR/LR_CORE1 - 82599-specअगरic
	  * 7   SFP_act_lmt_DA_CORE0 - 82599-specअगरic
	  * 8   SFP_act_lmt_DA_CORE1 - 82599-specअगरic
	  * 9   SFP_1g_cu_CORE0 - 82599-specअगरic
	  * 10  SFP_1g_cu_CORE1 - 82599-specअगरic
	  * 11  SFP_1g_sx_CORE0 - 82599-specअगरic
	  * 12  SFP_1g_sx_CORE1 - 82599-specअगरic
	  */
	अगर (hw->mac.type == ixgbe_mac_82598EB) अणु
		अगर (cable_tech & IXGBE_SFF_DA_PASSIVE_CABLE)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu;
		अन्यथा अगर (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)
			hw->phy.sfp_type = ixgbe_sfp_type_sr;
		अन्यथा अगर (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)
			hw->phy.sfp_type = ixgbe_sfp_type_lr;
		अन्यथा
			hw->phy.sfp_type = ixgbe_sfp_type_unknown;
	पूर्ण अन्यथा अणु
		अगर (cable_tech & IXGBE_SFF_DA_PASSIVE_CABLE) अणु
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
					     ixgbe_sfp_type_da_cu_core0;
			अन्यथा
				hw->phy.sfp_type =
					     ixgbe_sfp_type_da_cu_core1;
		पूर्ण अन्यथा अगर (cable_tech & IXGBE_SFF_DA_ACTIVE_CABLE) अणु
			hw->phy.ops.पढ़ो_i2c_eeprom(
					hw, IXGBE_SFF_CABLE_SPEC_COMP,
					&cable_spec);
			अगर (cable_spec &
			    IXGBE_SFF_DA_SPEC_ACTIVE_LIMITING) अणु
				अगर (hw->bus.lan_id == 0)
					hw->phy.sfp_type =
					ixgbe_sfp_type_da_act_lmt_core0;
				अन्यथा
					hw->phy.sfp_type =
					ixgbe_sfp_type_da_act_lmt_core1;
			पूर्ण अन्यथा अणु
				hw->phy.sfp_type =
						ixgbe_sfp_type_unknown;
			पूर्ण
		पूर्ण अन्यथा अगर (comp_codes_10g &
			   (IXGBE_SFF_10GBASESR_CAPABLE |
			    IXGBE_SFF_10GBASELR_CAPABLE)) अणु
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
					      ixgbe_sfp_type_srlr_core0;
			अन्यथा
				hw->phy.sfp_type =
					      ixgbe_sfp_type_srlr_core1;
		पूर्ण अन्यथा अगर (comp_codes_1g & IXGBE_SFF_1GBASET_CAPABLE) अणु
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_cu_core0;
			अन्यथा
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_cu_core1;
		पूर्ण अन्यथा अगर (comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE) अणु
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_sx_core0;
			अन्यथा
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_sx_core1;
		पूर्ण अन्यथा अगर (comp_codes_1g & IXGBE_SFF_1GBASELX_CAPABLE) अणु
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_lx_core0;
			अन्यथा
				hw->phy.sfp_type =
					ixgbe_sfp_type_1g_lx_core1;
		पूर्ण अन्यथा अणु
			hw->phy.sfp_type = ixgbe_sfp_type_unknown;
		पूर्ण
	पूर्ण

	अगर (hw->phy.sfp_type != stored_sfp_type)
		hw->phy.sfp_setup_needed = true;

	/* Determine अगर the SFP+ PHY is dual speed or not. */
	hw->phy.multispeed_fiber = false;
	अगर (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASELX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)))
		hw->phy.multispeed_fiber = true;

	/* Determine PHY venकरोr */
	अगर (hw->phy.type != ixgbe_phy_nl) अणु
		hw->phy.id = identअगरier;
		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					    IXGBE_SFF_VENDOR_OUI_BYTE0,
					    &oui_bytes[0]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					    IXGBE_SFF_VENDOR_OUI_BYTE1,
					    &oui_bytes[1]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					    IXGBE_SFF_VENDOR_OUI_BYTE2,
					    &oui_bytes[2]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		venकरोr_oui =
		  ((oui_bytes[0] << IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT) |
		   (oui_bytes[1] << IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT) |
		   (oui_bytes[2] << IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT));

		चयन (venकरोr_oui) अणु
		हाल IXGBE_SFF_VENDOR_OUI_TYCO:
			अगर (cable_tech & IXGBE_SFF_DA_PASSIVE_CABLE)
				hw->phy.type =
					    ixgbe_phy_sfp_passive_tyco;
			अवरोध;
		हाल IXGBE_SFF_VENDOR_OUI_FTL:
			अगर (cable_tech & IXGBE_SFF_DA_ACTIVE_CABLE)
				hw->phy.type = ixgbe_phy_sfp_ftl_active;
			अन्यथा
				hw->phy.type = ixgbe_phy_sfp_ftl;
			अवरोध;
		हाल IXGBE_SFF_VENDOR_OUI_AVAGO:
			hw->phy.type = ixgbe_phy_sfp_avago;
			अवरोध;
		हाल IXGBE_SFF_VENDOR_OUI_INTEL:
			hw->phy.type = ixgbe_phy_sfp_पूर्णांकel;
			अवरोध;
		शेष:
			अगर (cable_tech & IXGBE_SFF_DA_PASSIVE_CABLE)
				hw->phy.type =
					 ixgbe_phy_sfp_passive_unknown;
			अन्यथा अगर (cable_tech & IXGBE_SFF_DA_ACTIVE_CABLE)
				hw->phy.type =
					ixgbe_phy_sfp_active_unknown;
			अन्यथा
				hw->phy.type = ixgbe_phy_sfp_unknown;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Allow any DA cable venकरोr */
	अगर (cable_tech & (IXGBE_SFF_DA_PASSIVE_CABLE |
	    IXGBE_SFF_DA_ACTIVE_CABLE))
		वापस 0;

	/* Verअगरy supported 1G SFP modules */
	अगर (comp_codes_10g == 0 &&
	    !(hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1)) अणु
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण

	/* Anything अन्यथा 82598-based is supported */
	अगर (hw->mac.type == ixgbe_mac_82598EB)
		वापस 0;

	hw->mac.ops.get_device_caps(hw, &enक्रमce_sfp);
	अगर (!(enक्रमce_sfp & IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP) &&
	    !(hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_core1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
	      hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1)) अणु
		/* Make sure we're a supported PHY type */
		अगर (hw->phy.type == ixgbe_phy_sfp_पूर्णांकel)
			वापस 0;
		अगर (hw->allow_unsupported_sfp) अणु
			e_warn(drv, "WARNING: Intel (R) Network Connections are quality tested using Intel (R) Ethernet Optics.  Using untested modules is not supported and may cause unstable operation or damage to the module or the adapter.  Intel Corporation is not responsible for any harm caused by using untested modules.\n");
			वापस 0;
		पूर्ण
		hw_dbg(hw, "SFP+ module not supported\n");
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण
	वापस 0;

err_पढ़ो_i2c_eeprom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_present;
	अगर (hw->phy.type != ixgbe_phy_nl) अणु
		hw->phy.id = 0;
		hw->phy.type = ixgbe_phy_unknown;
	पूर्ण
	वापस IXGBE_ERR_SFP_NOT_PRESENT;
पूर्ण

/**
 * ixgbe_identअगरy_qsfp_module_generic - Identअगरies QSFP modules
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Searches क्रम and identअगरies the QSFP module and assigns appropriate PHY type
 **/
अटल s32 ixgbe_identअगरy_qsfp_module_generic(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_adapter *adapter = hw->back;
	s32 status;
	u32 venकरोr_oui = 0;
	क्रमागत ixgbe_sfp_type stored_sfp_type = hw->phy.sfp_type;
	u8 identअगरier = 0;
	u8 comp_codes_1g = 0;
	u8 comp_codes_10g = 0;
	u8 oui_bytes[3] = अणु0, 0, 0पूर्ण;
	u16 enक्रमce_sfp = 0;
	u8 connector = 0;
	u8 cable_length = 0;
	u8 device_tech = 0;
	bool active_cable = false;

	अगर (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_fiber_qsfp) अणु
		hw->phy.sfp_type = ixgbe_sfp_type_not_present;
		वापस IXGBE_ERR_SFP_NOT_PRESENT;
	पूर्ण

	/* LAN ID is needed क्रम sfp_type determination */
	hw->mac.ops.set_lan_id(hw);

	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw, IXGBE_SFF_IDENTIFIER,
					     &identअगरier);

	अगर (status != 0)
		जाओ err_पढ़ो_i2c_eeprom;

	अगर (identअगरier != IXGBE_SFF_IDENTIFIER_QSFP_PLUS) अणु
		hw->phy.type = ixgbe_phy_sfp_unsupported;
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण

	hw->phy.id = identअगरier;

	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw, IXGBE_SFF_QSFP_10GBE_COMP,
					     &comp_codes_10g);

	अगर (status != 0)
		जाओ err_पढ़ो_i2c_eeprom;

	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw, IXGBE_SFF_QSFP_1GBE_COMP,
					     &comp_codes_1g);

	अगर (status != 0)
		जाओ err_पढ़ो_i2c_eeprom;

	अगर (comp_codes_10g & IXGBE_SFF_QSFP_DA_PASSIVE_CABLE) अणु
		hw->phy.type = ixgbe_phy_qsfp_passive_unknown;
		अगर (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core0;
		अन्यथा
			hw->phy.sfp_type = ixgbe_sfp_type_da_cu_core1;
	पूर्ण अन्यथा अगर (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
				     IXGBE_SFF_10GBASELR_CAPABLE)) अणु
		अगर (hw->bus.lan_id == 0)
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core0;
		अन्यथा
			hw->phy.sfp_type = ixgbe_sfp_type_srlr_core1;
	पूर्ण अन्यथा अणु
		अगर (comp_codes_10g & IXGBE_SFF_QSFP_DA_ACTIVE_CABLE)
			active_cable = true;

		अगर (!active_cable) अणु
			/* check क्रम active DA cables that pre-date
			 * SFF-8436 v3.6
			 */
			hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_CONNECTOR,
					&connector);

			hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_CABLE_LENGTH,
					&cable_length);

			hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_DEVICE_TECH,
					&device_tech);

			अगर ((connector ==
				     IXGBE_SFF_QSFP_CONNECTOR_NOT_SEPARABLE) &&
			    (cable_length > 0) &&
			    ((device_tech >> 4) ==
				     IXGBE_SFF_QSFP_TRANSMITER_850NM_VCSEL))
				active_cable = true;
		पूर्ण

		अगर (active_cable) अणु
			hw->phy.type = ixgbe_phy_qsfp_active_unknown;
			अगर (hw->bus.lan_id == 0)
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_lmt_core0;
			अन्यथा
				hw->phy.sfp_type =
						ixgbe_sfp_type_da_act_lmt_core1;
		पूर्ण अन्यथा अणु
			/* unsupported module type */
			hw->phy.type = ixgbe_phy_sfp_unsupported;
			वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
		पूर्ण
	पूर्ण

	अगर (hw->phy.sfp_type != stored_sfp_type)
		hw->phy.sfp_setup_needed = true;

	/* Determine अगर the QSFP+ PHY is dual speed or not. */
	hw->phy.multispeed_fiber = false;
	अगर (((comp_codes_1g & IXGBE_SFF_1GBASESX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASESR_CAPABLE)) ||
	    ((comp_codes_1g & IXGBE_SFF_1GBASELX_CAPABLE) &&
	     (comp_codes_10g & IXGBE_SFF_10GBASELR_CAPABLE)))
		hw->phy.multispeed_fiber = true;

	/* Determine PHY venकरोr क्रम optical modules */
	अगर (comp_codes_10g & (IXGBE_SFF_10GBASESR_CAPABLE |
			      IXGBE_SFF_10GBASELR_CAPABLE)) अणु
		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0,
					&oui_bytes[0]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1,
					&oui_bytes[1]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2,
					&oui_bytes[2]);

		अगर (status != 0)
			जाओ err_पढ़ो_i2c_eeprom;

		venकरोr_oui =
			((oui_bytes[0] << IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT) |
			 (oui_bytes[1] << IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT) |
			 (oui_bytes[2] << IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT));

		अगर (venकरोr_oui == IXGBE_SFF_VENDOR_OUI_INTEL)
			hw->phy.type = ixgbe_phy_qsfp_पूर्णांकel;
		अन्यथा
			hw->phy.type = ixgbe_phy_qsfp_unknown;

		hw->mac.ops.get_device_caps(hw, &enक्रमce_sfp);
		अगर (!(enक्रमce_sfp & IXGBE_DEVICE_CAPS_ALLOW_ANY_SFP)) अणु
			/* Make sure we're a supported PHY type */
			अगर (hw->phy.type == ixgbe_phy_qsfp_पूर्णांकel)
				वापस 0;
			अगर (hw->allow_unsupported_sfp) अणु
				e_warn(drv, "WARNING: Intel (R) Network Connections are quality tested using Intel (R) Ethernet Optics. Using untested modules is not supported and may cause unstable operation or damage to the module or the adapter. Intel Corporation is not responsible for any harm caused by using untested modules.\n");
				वापस 0;
			पूर्ण
			hw_dbg(hw, "QSFP module not supported\n");
			hw->phy.type = ixgbe_phy_sfp_unsupported;
			वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस 0;

err_पढ़ो_i2c_eeprom:
	hw->phy.sfp_type = ixgbe_sfp_type_not_present;
	hw->phy.id = 0;
	hw->phy.type = ixgbe_phy_unknown;

	वापस IXGBE_ERR_SFP_NOT_PRESENT;
पूर्ण

/**
 *  ixgbe_get_sfp_init_sequence_offsets - Provides offset of PHY init sequence
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @list_offset: offset to the SFP ID list
 *  @data_offset: offset to the SFP data block
 *
 *  Checks the MAC's EEPROM to see अगर it supports a given SFP+ module type, अगर
 *  so it वापसs the offsets to the phy init sequence block.
 **/
s32 ixgbe_get_sfp_init_sequence_offsets(काष्ठा ixgbe_hw *hw,
					u16 *list_offset,
					u16 *data_offset)
अणु
	u16 sfp_id;
	u16 sfp_type = hw->phy.sfp_type;

	अगर (hw->phy.sfp_type == ixgbe_sfp_type_unknown)
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;

	अगर (hw->phy.sfp_type == ixgbe_sfp_type_not_present)
		वापस IXGBE_ERR_SFP_NOT_PRESENT;

	अगर ((hw->device_id == IXGBE_DEV_ID_82598_SR_DUAL_PORT_EM) &&
	    (hw->phy.sfp_type == ixgbe_sfp_type_da_cu))
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;

	/*
	 * Limiting active cables and 1G Phys must be initialized as
	 * SR modules
	 */
	अगर (sfp_type == ixgbe_sfp_type_da_act_lmt_core0 ||
	    sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
	    sfp_type == ixgbe_sfp_type_1g_cu_core0 ||
	    sfp_type == ixgbe_sfp_type_1g_sx_core0)
		sfp_type = ixgbe_sfp_type_srlr_core0;
	अन्यथा अगर (sfp_type == ixgbe_sfp_type_da_act_lmt_core1 ||
		 sfp_type == ixgbe_sfp_type_1g_lx_core1 ||
		 sfp_type == ixgbe_sfp_type_1g_cu_core1 ||
		 sfp_type == ixgbe_sfp_type_1g_sx_core1)
		sfp_type = ixgbe_sfp_type_srlr_core1;

	/* Read offset to PHY init contents */
	अगर (hw->eeprom.ops.पढ़ो(hw, IXGBE_PHY_INIT_OFFSET_NL, list_offset)) अणु
		hw_err(hw, "eeprom read at %d failed\n",
		       IXGBE_PHY_INIT_OFFSET_NL);
		वापस IXGBE_ERR_SFP_NO_INIT_SEQ_PRESENT;
	पूर्ण

	अगर ((!*list_offset) || (*list_offset == 0xFFFF))
		वापस IXGBE_ERR_SFP_NO_INIT_SEQ_PRESENT;

	/* Shअगरt offset to first ID word */
	(*list_offset)++;

	/*
	 * Find the matching SFP ID in the EEPROM
	 * and program the init sequence
	 */
	अगर (hw->eeprom.ops.पढ़ो(hw, *list_offset, &sfp_id))
		जाओ err_phy;

	जबतक (sfp_id != IXGBE_PHY_INIT_END_NL) अणु
		अगर (sfp_id == sfp_type) अणु
			(*list_offset)++;
			अगर (hw->eeprom.ops.पढ़ो(hw, *list_offset, data_offset))
				जाओ err_phy;
			अगर ((!*data_offset) || (*data_offset == 0xFFFF)) अणु
				hw_dbg(hw, "SFP+ module not supported\n");
				वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			(*list_offset) += 2;
			अगर (hw->eeprom.ops.पढ़ो(hw, *list_offset, &sfp_id))
				जाओ err_phy;
		पूर्ण
	पूर्ण

	अगर (sfp_id == IXGBE_PHY_INIT_END_NL) अणु
		hw_dbg(hw, "No matching SFP+ module found\n");
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण

	वापस 0;

err_phy:
	hw_err(hw, "eeprom read at offset %d failed\n", *list_offset);
	वापस IXGBE_ERR_PHY;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_eeprom_generic - Reads 8 bit EEPROM word over I2C पूर्णांकerface
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: EEPROM byte offset to पढ़ो
 *  @eeprom_data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface.
 **/
s32 ixgbe_पढ़ो_i2c_eeprom_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				  u8 *eeprom_data)
अणु
	वापस hw->phy.ops.पढ़ो_i2c_byte(hw, byte_offset,
					 IXGBE_I2C_EEPROM_DEV_ADDR,
					 eeprom_data);
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_sff8472_generic - Reads 8 bit word over I2C पूर्णांकerface
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset at address 0xA2
 *  @sff8472_data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's SFF-8472 data over I2C
 **/
s32 ixgbe_पढ़ो_i2c_sff8472_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				   u8 *sff8472_data)
अणु
	वापस hw->phy.ops.पढ़ो_i2c_byte(hw, byte_offset,
					 IXGBE_I2C_EEPROM_DEV_ADDR2,
					 sff8472_data);
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_eeprom_generic - Writes 8 bit EEPROM word over I2C पूर्णांकerface
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: EEPROM byte offset to ग_लिखो
 *  @eeprom_data: value to ग_लिखो
 *
 *  Perक्रमms byte ग_लिखो operation to SFP module's EEPROM over I2C पूर्णांकerface.
 **/
s32 ixgbe_ग_लिखो_i2c_eeprom_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				   u8 eeprom_data)
अणु
	वापस hw->phy.ops.ग_लिखो_i2c_byte(hw, byte_offset,
					  IXGBE_I2C_EEPROM_DEV_ADDR,
					  eeprom_data);
पूर्ण

/**
 * ixgbe_is_sfp_probe - Returns true अगर SFP is being detected
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @offset: eeprom offset to be पढ़ो
 * @addr: I2C address to be पढ़ो
 */
अटल bool ixgbe_is_sfp_probe(काष्ठा ixgbe_hw *hw, u8 offset, u8 addr)
अणु
	अगर (addr == IXGBE_I2C_EEPROM_DEV_ADDR &&
	    offset == IXGBE_SFF_IDENTIFIER &&
	    hw->phy.sfp_type == ixgbe_sfp_type_not_present)
		वापस true;
	वापस false;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_byte_generic_पूर्णांक - Reads 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to पढ़ो
 *  @dev_addr: device address
 *  @data: value पढ़ो
 *  @lock: true अगर to take and release semaphore
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
अटल s32 ixgbe_पढ़ो_i2c_byte_generic_पूर्णांक(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					   u8 dev_addr, u8 *data, bool lock)
अणु
	s32 status;
	u32 max_retry = 10;
	u32 retry = 0;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	bool nack = true;

	अगर (hw->mac.type >= ixgbe_mac_X550)
		max_retry = 3;
	अगर (ixgbe_is_sfp_probe(hw, byte_offset, dev_addr))
		max_retry = IXGBE_SFP_DETECT_RETRIES;

	*data = 0;

	करो अणु
		अगर (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
			वापस IXGBE_ERR_SWFW_SYNC;

		ixgbe_i2c_start(hw);

		/* Device Address and ग_लिखो indication */
		status = ixgbe_घड़ी_out_i2c_byte(hw, dev_addr);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_घड़ी_out_i2c_byte(hw, byte_offset);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		ixgbe_i2c_start(hw);

		/* Device Address and पढ़ो indication */
		status = ixgbe_घड़ी_out_i2c_byte(hw, (dev_addr | 0x1));
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_घड़ी_in_i2c_byte(hw, data);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_घड़ी_out_i2c_bit(hw, nack);
		अगर (status != 0)
			जाओ fail;

		ixgbe_i2c_stop(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		वापस 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		अगर (lock) अणु
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
			msleep(100);
		पूर्ण
		retry++;
		अगर (retry < max_retry)
			hw_dbg(hw, "I2C byte read error - Retrying.\n");
		अन्यथा
			hw_dbg(hw, "I2C byte read error.\n");

	पूर्ण जबतक (retry < max_retry);

	वापस status;
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_byte_generic - Reads 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to पढ़ो
 *  @dev_addr: device address
 *  @data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
s32 ixgbe_पढ़ो_i2c_byte_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				u8 dev_addr, u8 *data)
अणु
	वापस ixgbe_पढ़ो_i2c_byte_generic_पूर्णांक(hw, byte_offset, dev_addr,
					       data, true);
पूर्ण

/**
 *  ixgbe_पढ़ो_i2c_byte_generic_unlocked - Reads 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to पढ़ो
 *  @dev_addr: device address
 *  @data: value पढ़ो
 *
 *  Perक्रमms byte पढ़ो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
s32 ixgbe_पढ़ो_i2c_byte_generic_unlocked(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					 u8 dev_addr, u8 *data)
अणु
	वापस ixgbe_पढ़ो_i2c_byte_generic_पूर्णांक(hw, byte_offset, dev_addr,
					       data, false);
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_byte_generic_पूर्णांक - Writes 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to ग_लिखो
 *  @dev_addr: device address
 *  @data: value to ग_लिखो
 *  @lock: true अगर to take and release semaphore
 *
 *  Perक्रमms byte ग_लिखो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
अटल s32 ixgbe_ग_लिखो_i2c_byte_generic_पूर्णांक(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					    u8 dev_addr, u8 data, bool lock)
अणु
	s32 status;
	u32 max_retry = 1;
	u32 retry = 0;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;

	अगर (lock && hw->mac.ops.acquire_swfw_sync(hw, swfw_mask))
		वापस IXGBE_ERR_SWFW_SYNC;

	करो अणु
		ixgbe_i2c_start(hw);

		status = ixgbe_घड़ी_out_i2c_byte(hw, dev_addr);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_घड़ी_out_i2c_byte(hw, byte_offset);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_घड़ी_out_i2c_byte(hw, data);
		अगर (status != 0)
			जाओ fail;

		status = ixgbe_get_i2c_ack(hw);
		अगर (status != 0)
			जाओ fail;

		ixgbe_i2c_stop(hw);
		अगर (lock)
			hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		वापस 0;

fail:
		ixgbe_i2c_bus_clear(hw);
		retry++;
		अगर (retry < max_retry)
			hw_dbg(hw, "I2C byte write error - Retrying.\n");
		अन्यथा
			hw_dbg(hw, "I2C byte write error.\n");
	पूर्ण जबतक (retry < max_retry);

	अगर (lock)
		hw->mac.ops.release_swfw_sync(hw, swfw_mask);

	वापस status;
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_byte_generic - Writes 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to ग_लिखो
 *  @dev_addr: device address
 *  @data: value to ग_लिखो
 *
 *  Perक्रमms byte ग_लिखो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
s32 ixgbe_ग_लिखो_i2c_byte_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				 u8 dev_addr, u8 data)
अणु
	वापस ixgbe_ग_लिखो_i2c_byte_generic_पूर्णांक(hw, byte_offset, dev_addr,
						data, true);
पूर्ण

/**
 *  ixgbe_ग_लिखो_i2c_byte_generic_unlocked - Writes 8 bit word over I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @byte_offset: byte offset to ग_लिखो
 *  @dev_addr: device address
 *  @data: value to ग_लिखो
 *
 *  Perक्रमms byte ग_लिखो operation to SFP module's EEPROM over I2C पूर्णांकerface at
 *  a specअगरied device address.
 */
s32 ixgbe_ग_लिखो_i2c_byte_generic_unlocked(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					  u8 dev_addr, u8 data)
अणु
	वापस ixgbe_ग_लिखो_i2c_byte_generic_पूर्णांक(hw, byte_offset, dev_addr,
						data, false);
पूर्ण

/**
 *  ixgbe_i2c_start - Sets I2C start condition
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets I2C start condition (High -> Low on SDA जबतक SCL is High)
 *  Set bit-bang mode on X550 hardware.
 **/
अटल व्योम ixgbe_i2c_start(काष्ठा ixgbe_hw *hw)
अणु
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));

	i2cctl |= IXGBE_I2C_BB_EN(hw);

	/* Start condition must begin with data and घड़ी high */
	ixgbe_set_i2c_data(hw, &i2cctl, 1);
	ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

	/* Setup समय क्रम start condition (4.7us) */
	udelay(IXGBE_I2C_T_SU_STA);

	ixgbe_set_i2c_data(hw, &i2cctl, 0);

	/* Hold समय क्रम start condition (4us) */
	udelay(IXGBE_I2C_T_HD_STA);

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of घड़ी is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

पूर्ण

/**
 *  ixgbe_i2c_stop - Sets I2C stop condition
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Sets I2C stop condition (Low -> High on SDA जबतक SCL is High)
 *  Disables bit-bang mode and negates data output enable on X550
 *  hardware.
 **/
अटल व्योम ixgbe_i2c_stop(काष्ठा ixgbe_hw *hw)
अणु
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	u32 clk_oe_bit = IXGBE_I2C_CLK_OE_N_EN(hw);
	u32 bb_en_bit = IXGBE_I2C_BB_EN(hw);

	/* Stop condition must begin with data low and घड़ी high */
	ixgbe_set_i2c_data(hw, &i2cctl, 0);
	ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

	/* Setup समय क्रम stop condition (4us) */
	udelay(IXGBE_I2C_T_SU_STO);

	ixgbe_set_i2c_data(hw, &i2cctl, 1);

	/* bus मुक्त समय between stop and start (4.7us)*/
	udelay(IXGBE_I2C_T_BUF);

	अगर (bb_en_bit || data_oe_bit || clk_oe_bit) अणु
		i2cctl &= ~bb_en_bit;
		i2cctl |= data_oe_bit | clk_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण
पूर्ण

/**
 *  ixgbe_घड़ी_in_i2c_byte - Clocks in one byte via I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @data: data byte to घड़ी in
 *
 *  Clocks in one byte data via I2C data/घड़ी
 **/
अटल s32 ixgbe_घड़ी_in_i2c_byte(काष्ठा ixgbe_hw *hw, u8 *data)
अणु
	s32 i;
	bool bit = false;

	*data = 0;
	क्रम (i = 7; i >= 0; i--) अणु
		ixgbe_घड़ी_in_i2c_bit(hw, &bit);
		*data |= bit << i;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_घड़ी_out_i2c_byte - Clocks out one byte via I2C
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @data: data byte घड़ीed out
 *
 *  Clocks out one byte data via I2C data/घड़ी
 **/
अटल s32 ixgbe_घड़ी_out_i2c_byte(काष्ठा ixgbe_hw *hw, u8 data)
अणु
	s32 status;
	s32 i;
	u32 i2cctl;
	bool bit = false;

	क्रम (i = 7; i >= 0; i--) अणु
		bit = (data >> i) & 0x1;
		status = ixgbe_घड़ी_out_i2c_bit(hw, bit);

		अगर (status != 0)
			अवरोध;
	पूर्ण

	/* Release SDA line (set high) */
	i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	i2cctl |= IXGBE_I2C_DATA_OUT(hw);
	i2cctl |= IXGBE_I2C_DATA_OE_N_EN(hw);
	IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
	IXGBE_WRITE_FLUSH(hw);

	वापस status;
पूर्ण

/**
 *  ixgbe_get_i2c_ack - Polls क्रम I2C ACK
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Clocks in/out one bit via I2C data/घड़ी
 **/
अटल s32 ixgbe_get_i2c_ack(काष्ठा ixgbe_hw *hw)
अणु
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);
	s32 status = 0;
	u32 i = 0;
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 समयout = 10;
	bool ack = true;

	अगर (data_oe_bit) अणु
		i2cctl |= IXGBE_I2C_DATA_OUT(hw);
		i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण
	ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

	/* Minimum high period of घड़ी is 4us */
	udelay(IXGBE_I2C_T_HIGH);

	/* Poll क्रम ACK.  Note that ACK in I2C spec is
	 * transition from 1 to 0 */
	क्रम (i = 0; i < समयout; i++) अणु
		i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
		ack = ixgbe_get_i2c_data(hw, &i2cctl);

		udelay(1);
		अगर (ack == 0)
			अवरोध;
	पूर्ण

	अगर (ack == 1) अणु
		hw_dbg(hw, "I2C ack was not received.\n");
		status = IXGBE_ERR_I2C;
	पूर्ण

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of घड़ी is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

	वापस status;
पूर्ण

/**
 *  ixgbe_घड़ी_in_i2c_bit - Clocks in one bit via I2C data/घड़ी
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @data: पढ़ो data value
 *
 *  Clocks in one bit via I2C data/घड़ी
 **/
अटल s32 ixgbe_घड़ी_in_i2c_bit(काष्ठा ixgbe_hw *hw, bool *data)
अणु
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	अगर (data_oe_bit) अणु
		i2cctl |= IXGBE_I2C_DATA_OUT(hw);
		i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण
	ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

	/* Minimum high period of घड़ी is 4us */
	udelay(IXGBE_I2C_T_HIGH);

	i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	*data = ixgbe_get_i2c_data(hw, &i2cctl);

	ixgbe_lower_i2c_clk(hw, &i2cctl);

	/* Minimum low period of घड़ी is 4.7 us */
	udelay(IXGBE_I2C_T_LOW);

	वापस 0;
पूर्ण

/**
 *  ixgbe_घड़ी_out_i2c_bit - Clocks in/out one bit via I2C data/घड़ी
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @data: data value to ग_लिखो
 *
 *  Clocks out one bit via I2C data/घड़ी
 **/
अटल s32 ixgbe_घड़ी_out_i2c_bit(काष्ठा ixgbe_hw *hw, bool data)
अणु
	s32 status;
	u32 i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));

	status = ixgbe_set_i2c_data(hw, &i2cctl, data);
	अगर (status == 0) अणु
		ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

		/* Minimum high period of घड़ी is 4us */
		udelay(IXGBE_I2C_T_HIGH);

		ixgbe_lower_i2c_clk(hw, &i2cctl);

		/* Minimum low period of घड़ी is 4.7 us.
		 * This also takes care of the data hold समय.
		 */
		udelay(IXGBE_I2C_T_LOW);
	पूर्ण अन्यथा अणु
		hw_dbg(hw, "I2C data was not set to %X\n", data);
		वापस IXGBE_ERR_I2C;
	पूर्ण

	वापस 0;
पूर्ण
/**
 *  ixgbe_उठाओ_i2c_clk - Raises the I2C SCL घड़ी
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @i2cctl: Current value of I2CCTL रेजिस्टर
 *
 *  Raises the I2C घड़ी line '0'->'1'
 *  Negates the I2C घड़ी output enable on X550 hardware.
 **/
अटल व्योम ixgbe_उठाओ_i2c_clk(काष्ठा ixgbe_hw *hw, u32 *i2cctl)
अणु
	u32 clk_oe_bit = IXGBE_I2C_CLK_OE_N_EN(hw);
	u32 i = 0;
	u32 समयout = IXGBE_I2C_CLOCK_STRETCHING_TIMEOUT;
	u32 i2cctl_r = 0;

	अगर (clk_oe_bit) अणु
		*i2cctl |= clk_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
	पूर्ण

	क्रम (i = 0; i < समयout; i++) अणु
		*i2cctl |= IXGBE_I2C_CLK_OUT(hw);
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
		/* SCL rise समय (1000ns) */
		udelay(IXGBE_I2C_T_RISE);

		i2cctl_r = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
		अगर (i2cctl_r & IXGBE_I2C_CLK_IN(hw))
			अवरोध;
	पूर्ण
पूर्ण

/**
 *  ixgbe_lower_i2c_clk - Lowers the I2C SCL घड़ी
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @i2cctl: Current value of I2CCTL रेजिस्टर
 *
 *  Lowers the I2C घड़ी line '1'->'0'
 *  Asserts the I2C घड़ी output enable on X550 hardware.
 **/
अटल व्योम ixgbe_lower_i2c_clk(काष्ठा ixgbe_hw *hw, u32 *i2cctl)
अणु

	*i2cctl &= ~IXGBE_I2C_CLK_OUT(hw);
	*i2cctl &= ~IXGBE_I2C_CLK_OE_N_EN(hw);

	IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
	IXGBE_WRITE_FLUSH(hw);

	/* SCL fall समय (300ns) */
	udelay(IXGBE_I2C_T_FALL);
पूर्ण

/**
 *  ixgbe_set_i2c_data - Sets the I2C data bit
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @i2cctl: Current value of I2CCTL रेजिस्टर
 *  @data: I2C data value (0 or 1) to set
 *
 *  Sets the I2C data bit
 *  Asserts the I2C data output enable on X550 hardware.
 **/
अटल s32 ixgbe_set_i2c_data(काष्ठा ixgbe_hw *hw, u32 *i2cctl, bool data)
अणु
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	अगर (data)
		*i2cctl |= IXGBE_I2C_DATA_OUT(hw);
	अन्यथा
		*i2cctl &= ~IXGBE_I2C_DATA_OUT(hw);
	*i2cctl &= ~data_oe_bit;

	IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
	IXGBE_WRITE_FLUSH(hw);

	/* Data rise/fall (1000ns/300ns) and set-up समय (250ns) */
	udelay(IXGBE_I2C_T_RISE + IXGBE_I2C_T_FALL + IXGBE_I2C_T_SU_DATA);

	अगर (!data)	/* Can't verअगरy data in this हाल */
		वापस 0;
	अगर (data_oe_bit) अणु
		*i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
	पूर्ण

	/* Verअगरy data was set correctly */
	*i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));
	अगर (data != ixgbe_get_i2c_data(hw, i2cctl)) अणु
		hw_dbg(hw, "Error - I2C data was not set to %X.\n", data);
		वापस IXGBE_ERR_I2C;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  ixgbe_get_i2c_data - Reads the I2C SDA data bit
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @i2cctl: Current value of I2CCTL रेजिस्टर
 *
 *  Returns the I2C data bit value
 *  Negates the I2C data output enable on X550 hardware.
 **/
अटल bool ixgbe_get_i2c_data(काष्ठा ixgbe_hw *hw, u32 *i2cctl)
अणु
	u32 data_oe_bit = IXGBE_I2C_DATA_OE_N_EN(hw);

	अगर (data_oe_bit) अणु
		*i2cctl |= data_oe_bit;
		IXGBE_WRITE_REG(hw, IXGBE_I2CCTL(hw), *i2cctl);
		IXGBE_WRITE_FLUSH(hw);
		udelay(IXGBE_I2C_T_FALL);
	पूर्ण

	अगर (*i2cctl & IXGBE_I2C_DATA_IN(hw))
		वापस true;
	वापस false;
पूर्ण

/**
 *  ixgbe_i2c_bus_clear - Clears the I2C bus
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Clears the I2C bus by sending nine घड़ी pulses.
 *  Used when data line is stuck low.
 **/
अटल व्योम ixgbe_i2c_bus_clear(काष्ठा ixgbe_hw *hw)
अणु
	u32 i2cctl;
	u32 i;

	ixgbe_i2c_start(hw);
	i2cctl = IXGBE_READ_REG(hw, IXGBE_I2CCTL(hw));

	ixgbe_set_i2c_data(hw, &i2cctl, 1);

	क्रम (i = 0; i < 9; i++) अणु
		ixgbe_उठाओ_i2c_clk(hw, &i2cctl);

		/* Min high period of घड़ी is 4us */
		udelay(IXGBE_I2C_T_HIGH);

		ixgbe_lower_i2c_clk(hw, &i2cctl);

		/* Min low period of घड़ी is 4.7us*/
		udelay(IXGBE_I2C_T_LOW);
	पूर्ण

	ixgbe_i2c_start(hw);

	/* Put the i2c bus back to शेष state */
	ixgbe_i2c_stop(hw);
पूर्ण

/**
 *  ixgbe_tn_check_overtemp - Checks अगर an overtemp occurred.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Checks अगर the LASI temp alarm status was triggered due to overtemp
 **/
s32 ixgbe_tn_check_overtemp(काष्ठा ixgbe_hw *hw)
अणु
	u16 phy_data = 0;

	अगर (hw->device_id != IXGBE_DEV_ID_82599_T3_LOM)
		वापस 0;

	/* Check that the LASI temp alarm status was triggered */
	hw->phy.ops.पढ़ो_reg(hw, IXGBE_TN_LASI_STATUS_REG,
			     MDIO_MMD_PMAPMD, &phy_data);

	अगर (!(phy_data & IXGBE_TN_LASI_STATUS_TEMP_ALARM))
		वापस 0;

	वापस IXGBE_ERR_OVERTEMP;
पूर्ण

/** ixgbe_set_copper_phy_घातer - Control घातer क्रम copper phy
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @on: true क्रम on, false क्रम off
 **/
s32 ixgbe_set_copper_phy_घातer(काष्ठा ixgbe_hw *hw, bool on)
अणु
	u32 status;
	u16 reg;

	/* Bail अगर we करोn't have copper phy */
	अगर (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		वापस 0;

	अगर (!on && ixgbe_mng_present(hw))
		वापस 0;

	status = hw->phy.ops.पढ़ो_reg(hw, MDIO_CTRL1, MDIO_MMD_VEND1, &reg);
	अगर (status)
		वापस status;

	अगर (on) अणु
		reg &= ~IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	पूर्ण अन्यथा अणु
		अगर (ixgbe_check_reset_blocked(hw))
			वापस 0;
		reg |= IXGBE_MDIO_PHY_SET_LOW_POWER_MODE;
	पूर्ण

	status = hw->phy.ops.ग_लिखो_reg(hw, MDIO_CTRL1, MDIO_MMD_VEND1, reg);
	वापस status;
पूर्ण

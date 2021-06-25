<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>

#समावेश "atl1e.h"

/*
 * check_eeprom_exist
 * वापस 0 अगर eeprom exist
 */
पूर्णांक atl1e_check_eeprom_exist(काष्ठा atl1e_hw *hw)
अणु
	u32 value;

	value = AT_READ_REG(hw, REG_SPI_FLASH_CTRL);
	अगर (value & SPI_FLASH_CTRL_EN_VPD) अणु
		value &= ~SPI_FLASH_CTRL_EN_VPD;
		AT_WRITE_REG(hw, REG_SPI_FLASH_CTRL, value);
	पूर्ण
	value = AT_READ_REGW(hw, REG_PCIE_CAP_LIST);
	वापस ((value & 0xFF00) == 0x6C00) ? 0 : 1;
पूर्ण

व्योम atl1e_hw_set_mac_addr(काष्ठा atl1e_hw *hw)
अणु
	u32 value;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC 1: 000B
	 * low dword
	 */
	value = (((u32)hw->mac_addr[2]) << 24) |
		(((u32)hw->mac_addr[3]) << 16) |
		(((u32)hw->mac_addr[4]) << 8)  |
		(((u32)hw->mac_addr[5])) ;
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 0, value);
	/* hight dword */
	value = (((u32)hw->mac_addr[0]) << 8) |
		(((u32)hw->mac_addr[1])) ;
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 1, value);
पूर्ण

/*
 * atl1e_get_permanent_address
 * वापस 0 अगर get valid mac address,
 */
अटल पूर्णांक atl1e_get_permanent_address(काष्ठा atl1e_hw *hw)
अणु
	u32 addr[2];
	u32 i;
	u32 twsi_ctrl_data;
	u8  eth_addr[ETH_ALEN];

	अगर (is_valid_ether_addr(hw->perm_mac_addr))
		वापस 0;

	/* init */
	addr[0] = addr[1] = 0;

	अगर (!atl1e_check_eeprom_exist(hw)) अणु
		/* eeprom exist */
		twsi_ctrl_data = AT_READ_REG(hw, REG_TWSI_CTRL);
		twsi_ctrl_data |= TWSI_CTRL_SW_LDSTART;
		AT_WRITE_REG(hw, REG_TWSI_CTRL, twsi_ctrl_data);
		क्रम (i = 0; i < AT_TWSI_EEPROM_TIMEOUT; i++) अणु
			msleep(10);
			twsi_ctrl_data = AT_READ_REG(hw, REG_TWSI_CTRL);
			अगर ((twsi_ctrl_data & TWSI_CTRL_SW_LDSTART) == 0)
				अवरोध;
		पूर्ण
		अगर (i >= AT_TWSI_EEPROM_TIMEOUT)
			वापस AT_ERR_TIMEOUT;
	पूर्ण

	/* maybe MAC-address is from BIOS */
	addr[0] = AT_READ_REG(hw, REG_MAC_STA_ADDR);
	addr[1] = AT_READ_REG(hw, REG_MAC_STA_ADDR + 4);
	*(u32 *) &eth_addr[2] = swab32(addr[0]);
	*(u16 *) &eth_addr[0] = swab16(*(u16 *)&addr[1]);

	अगर (is_valid_ether_addr(eth_addr)) अणु
		स_नकल(hw->perm_mac_addr, eth_addr, ETH_ALEN);
		वापस 0;
	पूर्ण

	वापस AT_ERR_EEPROM;
पूर्ण

bool atl1e_ग_लिखो_eeprom(काष्ठा atl1e_hw *hw, u32 offset, u32 value)
अणु
	वापस true;
पूर्ण

bool atl1e_पढ़ो_eeprom(काष्ठा atl1e_hw *hw, u32 offset, u32 *p_value)
अणु
	पूर्णांक i;
	u32 control;

	अगर (offset & 3)
		वापस false; /* address करो not align */

	AT_WRITE_REG(hw, REG_VPD_DATA, 0);
	control = (offset & VPD_CAP_VPD_ADDR_MASK) << VPD_CAP_VPD_ADDR_SHIFT;
	AT_WRITE_REG(hw, REG_VPD_CAP, control);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(2);
		control = AT_READ_REG(hw, REG_VPD_CAP);
		अगर (control & VPD_CAP_VPD_FLAG)
			अवरोध;
	पूर्ण
	अगर (control & VPD_CAP_VPD_FLAG) अणु
		*p_value = AT_READ_REG(hw, REG_VPD_DATA);
		वापस true;
	पूर्ण
	वापस false; /* समयout */
पूर्ण

व्योम atl1e_क्रमce_ps(काष्ठा atl1e_hw *hw)
अणु
	AT_WRITE_REGW(hw, REG_GPHY_CTRL,
			GPHY_CTRL_PW_WOL_DIS | GPHY_CTRL_EXT_RESET);
पूर्ण

/*
 * Reads the adapter's MAC address from the EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 */
पूर्णांक atl1e_पढ़ो_mac_addr(काष्ठा atl1e_hw *hw)
अणु
	पूर्णांक err = 0;

	err = atl1e_get_permanent_address(hw);
	अगर (err)
		वापस AT_ERR_EEPROM;
	स_नकल(hw->mac_addr, hw->perm_mac_addr, माप(hw->perm_mac_addr));
	वापस 0;
पूर्ण

/*
 * atl1e_hash_mc_addr
 *  purpose
 *      set hash value क्रम a multicast address
 */
u32 atl1e_hash_mc_addr(काष्ठा atl1e_hw *hw, u8 *mc_addr)
अणु
	u32 crc32;
	u32 value = 0;
	पूर्णांक i;

	crc32 = ether_crc_le(6, mc_addr);
	क्रम (i = 0; i < 32; i++)
		value |= (((crc32 >> i) & 1) << (31 - i));

	वापस value;
पूर्ण

/*
 * Sets the bit in the multicast table corresponding to the hash value.
 * hw - Struct containing variables accessed by shared code
 * hash_value - Multicast address hash value
 */
व्योम atl1e_hash_set(काष्ठा atl1e_hw *hw, u32 hash_value)
अणु
	u32 hash_bit, hash_reg;
	u32 mta;

	/*
	 * The HASH Table  is a रेजिस्टर array of 2 32-bit रेजिस्टरs.
	 * It is treated like an array of 64 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what रेजिस्टर
	 * the bit is in, पढ़ो it, OR in the new bit, then ग_लिखो
	 * back the new value.  The रेजिस्टर is determined by the
	 * upper 7 bits of the hash value and the bit within that
	 * रेजिस्टर are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 31) & 0x1;
	hash_bit = (hash_value >> 26) & 0x1F;

	mta = AT_READ_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg);

	mta |= (1 << hash_bit);

	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg, mta);
पूर्ण
/*
 * Reads the value from a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to पढ़ो
 */
पूर्णांक atl1e_पढ़ो_phy_reg(काष्ठा atl1e_hw *hw, u16 reg_addr, u16 *phy_data)
अणु
	u32 val;
	पूर्णांक i;

	val = ((u32)(reg_addr & MDIO_REG_ADDR_MASK)) << MDIO_REG_ADDR_SHIFT |
		MDIO_START | MDIO_SUP_PREAMBLE | MDIO_RW |
		MDIO_CLK_25_4 << MDIO_CLK_SEL_SHIFT;

	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);

	wmb();

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = AT_READ_REG(hw, REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;
		wmb();
	पूर्ण
	अगर (!(val & (MDIO_START | MDIO_BUSY))) अणु
		*phy_data = (u16)val;
		वापस 0;
	पूर्ण

	वापस AT_ERR_PHY;
पूर्ण

/*
 * Writes a value to a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to ग_लिखो
 * data - data to ग_लिखो to the PHY
 */
पूर्णांक atl1e_ग_लिखो_phy_reg(काष्ठा atl1e_hw *hw, u32 reg_addr, u16 phy_data)
अणु
	पूर्णांक i;
	u32 val;

	val = ((u32)(phy_data & MDIO_DATA_MASK)) << MDIO_DATA_SHIFT |
	       (reg_addr&MDIO_REG_ADDR_MASK) << MDIO_REG_ADDR_SHIFT |
	       MDIO_SUP_PREAMBLE |
	       MDIO_START |
	       MDIO_CLK_25_4 << MDIO_CLK_SEL_SHIFT;

	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);
	wmb();

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = AT_READ_REG(hw, REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;
		wmb();
	पूर्ण

	अगर (!(val & (MDIO_START | MDIO_BUSY)))
		वापस 0;

	वापस AT_ERR_PHY;
पूर्ण

/*
 * atl1e_init_pcie - init PCIE module
 */
अटल व्योम atl1e_init_pcie(काष्ठा atl1e_hw *hw)
अणु
	u32 value;
	/* comment 2lines below to save more घातer when sususpend
	   value = LTSSM_TEST_MODE_DEF;
	   AT_WRITE_REG(hw, REG_LTSSM_TEST_MODE, value);
	 */

	/* pcie flow control mode change */
	value = AT_READ_REG(hw, 0x1008);
	value |= 0x8000;
	AT_WRITE_REG(hw, 0x1008, value);
पूर्ण
/*
 * Configures PHY स्वतःneg and flow control advertisement settings
 *
 * hw - Struct containing variables accessed by shared code
 */
अटल पूर्णांक atl1e_phy_setup_स्वतःneg_adv(काष्ठा atl1e_hw *hw)
अणु
	s32 ret_val;
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg;

	अगर (0 != hw->mii_स्वतःneg_adv_reg)
		वापस 0;
	/* Read the MII Auto-Neg Advertisement Register (Address 4/9). */
	mii_स्वतःneg_adv_reg = MII_AR_DEFAULT_CAP_MASK;
	mii_1000t_ctrl_reg  = MII_AT001_CR_1000T_DEFAULT_CAP_MASK;

	/*
	 * Need to parse स्वतःneg_advertised  and set up
	 * the appropriate PHY रेजिस्टरs.  First we will parse क्रम
	 * स्वतःneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * inभागidually.
	 */

	/*
	 * First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T control Register (Address 9).
	 */
	mii_स्वतःneg_adv_reg &= ~ADVERTISE_ALL;
	mii_1000t_ctrl_reg  &= ~MII_AT001_CR_1000T_SPEED_MASK;

	/*
	 * Need to parse MediaType and setup the
	 * appropriate PHY रेजिस्टरs.
	 */
	चयन (hw->media_type) अणु
	हाल MEDIA_TYPE_AUTO_SENSOR:
		mii_स्वतःneg_adv_reg |= ADVERTISE_ALL;
		hw->स्वतःneg_advertised = ADVERTISE_ALL;
		अगर (hw->nic_type == athr_l1e) अणु
			mii_1000t_ctrl_reg |= ADVERTISE_1000FULL;
			hw->स्वतःneg_advertised |= ADVERTISE_1000_FULL;
		पूर्ण
		अवरोध;

	हाल MEDIA_TYPE_100M_FULL:
		mii_स्वतःneg_adv_reg   |= ADVERTISE_100FULL;
		hw->स्वतःneg_advertised = ADVERTISE_100_FULL;
		अवरोध;

	हाल MEDIA_TYPE_100M_HALF:
		mii_स्वतःneg_adv_reg   |= ADVERTISE_100_HALF;
		hw->स्वतःneg_advertised = ADVERTISE_100_HALF;
		अवरोध;

	हाल MEDIA_TYPE_10M_FULL:
		mii_स्वतःneg_adv_reg   |= ADVERTISE_10_FULL;
		hw->स्वतःneg_advertised = ADVERTISE_10_FULL;
		अवरोध;

	शेष:
		mii_स्वतःneg_adv_reg   |= ADVERTISE_10_HALF;
		hw->स्वतःneg_advertised = ADVERTISE_10_HALF;
		अवरोध;
	पूर्ण

	/* flow control fixed to enable all */
	mii_स्वतःneg_adv_reg |= (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);

	hw->mii_स्वतःneg_adv_reg = mii_स्वतःneg_adv_reg;
	hw->mii_1000t_ctrl_reg  = mii_1000t_ctrl_reg;

	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_ADVERTISE, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	अगर (hw->nic_type == athr_l1e || hw->nic_type == athr_l2e_revA) अणु
		ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_CTRL1000,
					   mii_1000t_ctrl_reg);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Resets the PHY and make all config validate
 *
 * hw - Struct containing variables accessed by shared code
 *
 * Sets bit 15 and 12 of the MII control regiser (क्रम F001 bug)
 */
पूर्णांक atl1e_phy_commit(काष्ठा atl1e_hw *hw)
अणु
	काष्ठा atl1e_adapter *adapter = hw->adapter;
	पूर्णांक ret_val;
	u16 phy_data;

	phy_data = BMCR_RESET | BMCR_ANENABLE | BMCR_ANRESTART;

	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
	अगर (ret_val) अणु
		u32 val;
		पूर्णांक i;
		/**************************************
		 * pcie serdes link may be करोwn !
		 **************************************/
		क्रम (i = 0; i < 25; i++) अणु
			msleep(1);
			val = AT_READ_REG(hw, REG_MDIO_CTRL);
			अगर (!(val & (MDIO_START | MDIO_BUSY)))
				अवरोध;
		पूर्ण

		अगर (0 != (val & (MDIO_START | MDIO_BUSY))) अणु
			netdev_err(adapter->netdev,
				   "pcie linkdown at least for 25ms\n");
			वापस ret_val;
		पूर्ण

		netdev_err(adapter->netdev, "pcie linkup after %d ms\n", i);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक atl1e_phy_init(काष्ठा atl1e_hw *hw)
अणु
	काष्ठा atl1e_adapter *adapter = hw->adapter;
	s32 ret_val;
	u16 phy_val;

	अगर (hw->phy_configured) अणु
		अगर (hw->re_स्वतःneg) अणु
			hw->re_स्वतःneg = false;
			वापस atl1e_restart_स्वतःneg(hw);
		पूर्ण
		वापस 0;
	पूर्ण

	/* RESET GPHY Core */
	AT_WRITE_REGW(hw, REG_GPHY_CTRL, GPHY_CTRL_DEFAULT);
	msleep(2);
	AT_WRITE_REGW(hw, REG_GPHY_CTRL, GPHY_CTRL_DEFAULT |
		      GPHY_CTRL_EXT_RESET);
	msleep(2);

	/* patches */
	/* p1. eable hibernation mode */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0xB);
	अगर (ret_val)
		वापस ret_val;
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0xBC00);
	अगर (ret_val)
		वापस ret_val;
	/* p2. set Class A/B क्रम all modes */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0);
	अगर (ret_val)
		वापस ret_val;
	phy_val = 0x02ef;
	/* हटाओ Class AB */
	/* phy_val = hw->emi_ca ? 0x02ef : 0x02df; */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_DATA, phy_val);
	अगर (ret_val)
		वापस ret_val;
	/* p3. 10B ??? */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0x12);
	अगर (ret_val)
		वापस ret_val;
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0x4C04);
	अगर (ret_val)
		वापस ret_val;
	/* p4. 1000T घातer */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0x4);
	अगर (ret_val)
		वापस ret_val;
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0x8BBB);
	अगर (ret_val)
		वापस ret_val;

	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, 0x5);
	अगर (ret_val)
		वापस ret_val;
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_DBG_DATA, 0x2C46);
	अगर (ret_val)
		वापस ret_val;

	msleep(1);

	/*Enable PHY LinkChange Interrupt */
	ret_val = atl1e_ग_लिखो_phy_reg(hw, MII_INT_CTRL, 0xC00);
	अगर (ret_val) अणु
		netdev_err(adapter->netdev,
			   "Error enable PHY linkChange Interrupt\n");
		वापस ret_val;
	पूर्ण
	/* setup AutoNeg parameters */
	ret_val = atl1e_phy_setup_स्वतःneg_adv(hw);
	अगर (ret_val) अणु
		netdev_err(adapter->netdev,
			   "Error Setting up Auto-Negotiation\n");
		वापस ret_val;
	पूर्ण
	/* SW.Reset & En-Auto-Neg to restart Auto-Neg*/
	netdev_dbg(adapter->netdev, "Restarting Auto-Negotiation\n");
	ret_val = atl1e_phy_commit(hw);
	अगर (ret_val) अणु
		netdev_err(adapter->netdev, "Error resetting the phy\n");
		वापस ret_val;
	पूर्ण

	hw->phy_configured = true;

	वापस 0;
पूर्ण

/*
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 * hw - Struct containing variables accessed by shared code
 * वापस : 0  or  idle status (अगर error)
 */
पूर्णांक atl1e_reset_hw(काष्ठा atl1e_hw *hw)
अणु
	काष्ठा atl1e_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;

	u32 idle_status_data = 0;
	u16 pci_cfg_cmd_word = 0;
	पूर्णांक समयout = 0;

	/* Workaround क्रम PCI problem when BIOS sets MMRBC incorrectly. */
	pci_पढ़ो_config_word(pdev, PCI_REG_COMMAND, &pci_cfg_cmd_word);
	अगर ((pci_cfg_cmd_word & (CMD_IO_SPACE |
				CMD_MEMORY_SPACE | CMD_BUS_MASTER))
			!= (CMD_IO_SPACE | CMD_MEMORY_SPACE | CMD_BUS_MASTER)) अणु
		pci_cfg_cmd_word |= (CMD_IO_SPACE |
				     CMD_MEMORY_SPACE | CMD_BUS_MASTER);
		pci_ग_लिखो_config_word(pdev, PCI_REG_COMMAND, pci_cfg_cmd_word);
	पूर्ण

	/*
	 * Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	AT_WRITE_REG(hw, REG_MASTER_CTRL,
			MASTER_CTRL_LED_MODE | MASTER_CTRL_SOFT_RST);
	wmb();
	msleep(1);

	/* Wait at least 10ms क्रम All module to be Idle */
	क्रम (समयout = 0; समयout < AT_HW_MAX_IDLE_DELAY; समयout++) अणु
		idle_status_data = AT_READ_REG(hw, REG_IDLE_STATUS);
		अगर (idle_status_data == 0)
			अवरोध;
		msleep(1);
		cpu_relax();
	पूर्ण

	अगर (समयout >= AT_HW_MAX_IDLE_DELAY) अणु
		netdev_err(adapter->netdev,
			   "MAC state machine can't be idle since disabled for 10ms second\n");
		वापस AT_ERR_TIMEOUT;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Perक्रमms basic configuration of the adapter.
 *
 * hw - Struct containing variables accessed by shared code
 * Assumes that the controller has previously been reset and is in a
 * post-reset uninitialized state. Initializes multicast table,
 * and  Calls routines to setup link
 * Leaves the transmit and receive units disabled and uninitialized.
 */
पूर्णांक atl1e_init_hw(काष्ठा atl1e_hw *hw)
अणु
	s32 ret_val = 0;

	atl1e_init_pcie(hw);

	/* Zero out the Multicast HASH table */
	/* clear the old settings from the multicast hash table */
	AT_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	ret_val = atl1e_phy_init(hw);

	वापस ret_val;
पूर्ण

/*
 * Detects the current speed and duplex settings of the hardware.
 *
 * hw - Struct containing variables accessed by shared code
 * speed - Speed of the connection
 * duplex - Duplex setting of the connection
 */
पूर्णांक atl1e_get_speed_and_duplex(काष्ठा atl1e_hw *hw, u16 *speed, u16 *duplex)
अणु
	पूर्णांक err;
	u16 phy_data;

	/* Read   PHY Specअगरic Status Register (17) */
	err = atl1e_पढ़ो_phy_reg(hw, MII_AT001_PSSR, &phy_data);
	अगर (err)
		वापस err;

	अगर (!(phy_data & MII_AT001_PSSR_SPD_DPLX_RESOLVED))
		वापस AT_ERR_PHY_RES;

	चयन (phy_data & MII_AT001_PSSR_SPEED) अणु
	हाल MII_AT001_PSSR_1000MBS:
		*speed = SPEED_1000;
		अवरोध;
	हाल MII_AT001_PSSR_100MBS:
		*speed = SPEED_100;
		अवरोध;
	हाल MII_AT001_PSSR_10MBS:
		*speed = SPEED_10;
		अवरोध;
	शेष:
		वापस AT_ERR_PHY_SPEED;
	पूर्ण

	अगर (phy_data & MII_AT001_PSSR_DPLX)
		*duplex = FULL_DUPLEX;
	अन्यथा
		*duplex = HALF_DUPLEX;

	वापस 0;
पूर्ण

पूर्णांक atl1e_restart_स्वतःneg(काष्ठा atl1e_hw *hw)
अणु
	पूर्णांक err = 0;

	err = atl1e_ग_लिखो_phy_reg(hw, MII_ADVERTISE, hw->mii_स्वतःneg_adv_reg);
	अगर (err)
		वापस err;

	अगर (hw->nic_type == athr_l1e || hw->nic_type == athr_l2e_revA) अणु
		err = atl1e_ग_लिखो_phy_reg(hw, MII_CTRL1000,
				       hw->mii_1000t_ctrl_reg);
		अगर (err)
			वापस err;
	पूर्ण

	err = atl1e_ग_लिखो_phy_reg(hw, MII_BMCR,
			BMCR_RESET | BMCR_ANENABLE | BMCR_ANRESTART);
	वापस err;
पूर्ण


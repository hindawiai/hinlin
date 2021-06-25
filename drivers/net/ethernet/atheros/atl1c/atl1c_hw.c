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

#समावेश "atl1c.h"

/*
 * check_eeprom_exist
 * वापस 1 अगर eeprom exist
 */
पूर्णांक atl1c_check_eeprom_exist(काष्ठा atl1c_hw *hw)
अणु
	u32 data;

	AT_READ_REG(hw, REG_TWSI_DEBUG, &data);
	अगर (data & TWSI_DEBUG_DEV_EXIST)
		वापस 1;

	AT_READ_REG(hw, REG_MASTER_CTRL, &data);
	अगर (data & MASTER_CTRL_OTP_SEL)
		वापस 1;
	वापस 0;
पूर्ण

व्योम atl1c_hw_set_mac_addr(काष्ठा atl1c_hw *hw, u8 *mac_addr)
अणु
	u32 value;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC 1: 000B
	 * low dword
	 */
	value = mac_addr[2] << 24 |
		mac_addr[3] << 16 |
		mac_addr[4] << 8  |
		mac_addr[5];
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 0, value);
	/* hight dword */
	value = mac_addr[0] << 8 |
		mac_addr[1];
	AT_WRITE_REG_ARRAY(hw, REG_MAC_STA_ADDR, 1, value);
पूर्ण

/* पढ़ो mac address from hardware रेजिस्टर */
अटल bool atl1c_पढ़ो_current_addr(काष्ठा atl1c_hw *hw, u8 *eth_addr)
अणु
	u32 addr[2];

	AT_READ_REG(hw, REG_MAC_STA_ADDR, &addr[0]);
	AT_READ_REG(hw, REG_MAC_STA_ADDR + 4, &addr[1]);

	*(u32 *) &eth_addr[2] = htonl(addr[0]);
	*(u16 *) &eth_addr[0] = htons((u16)addr[1]);

	वापस is_valid_ether_addr(eth_addr);
पूर्ण

/*
 * atl1c_get_permanent_address
 * वापस 0 अगर get valid mac address,
 */
अटल पूर्णांक atl1c_get_permanent_address(काष्ठा atl1c_hw *hw)
अणु
	u32 i;
	u32 otp_ctrl_data;
	u32 twsi_ctrl_data;
	u16 phy_data;
	bool उठाओ_vol = false;

	/* MAC-address from BIOS is the 1st priority */
	अगर (atl1c_पढ़ो_current_addr(hw, hw->perm_mac_addr))
		वापस 0;

	/* init */
	AT_READ_REG(hw, REG_OTP_CTRL, &otp_ctrl_data);
	अगर (atl1c_check_eeprom_exist(hw)) अणु
		अगर (hw->nic_type == athr_l1c || hw->nic_type == athr_l2c) अणु
			/* Enable OTP CLK */
			अगर (!(otp_ctrl_data & OTP_CTRL_CLK_EN)) अणु
				otp_ctrl_data |= OTP_CTRL_CLK_EN;
				AT_WRITE_REG(hw, REG_OTP_CTRL, otp_ctrl_data);
				AT_WRITE_FLUSH(hw);
				msleep(1);
			पूर्ण
		पूर्ण
		/* उठाओ voltage temporally क्रम l2cb */
		अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2) अणु
			atl1c_पढ़ो_phy_dbg(hw, MIIDBG_ANACTRL, &phy_data);
			phy_data &= ~ANACTRL_HB_EN;
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_ANACTRL, phy_data);
			atl1c_पढ़ो_phy_dbg(hw, MIIDBG_VOLT_CTRL, &phy_data);
			phy_data |= VOLT_CTRL_SWLOWEST;
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_VOLT_CTRL, phy_data);
			udelay(20);
			उठाओ_vol = true;
		पूर्ण

		AT_READ_REG(hw, REG_TWSI_CTRL, &twsi_ctrl_data);
		twsi_ctrl_data |= TWSI_CTRL_SW_LDSTART;
		AT_WRITE_REG(hw, REG_TWSI_CTRL, twsi_ctrl_data);
		क्रम (i = 0; i < AT_TWSI_EEPROM_TIMEOUT; i++) अणु
			msleep(10);
			AT_READ_REG(hw, REG_TWSI_CTRL, &twsi_ctrl_data);
			अगर ((twsi_ctrl_data & TWSI_CTRL_SW_LDSTART) == 0)
				अवरोध;
		पूर्ण
		अगर (i >= AT_TWSI_EEPROM_TIMEOUT)
			वापस -1;
	पूर्ण
	/* Disable OTP_CLK */
	अगर ((hw->nic_type == athr_l1c || hw->nic_type == athr_l2c)) अणु
		otp_ctrl_data &= ~OTP_CTRL_CLK_EN;
		AT_WRITE_REG(hw, REG_OTP_CTRL, otp_ctrl_data);
		msleep(1);
	पूर्ण
	अगर (उठाओ_vol) अणु
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_ANACTRL, &phy_data);
		phy_data |= ANACTRL_HB_EN;
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_ANACTRL, phy_data);
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_VOLT_CTRL, &phy_data);
		phy_data &= ~VOLT_CTRL_SWLOWEST;
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_VOLT_CTRL, phy_data);
		udelay(20);
	पूर्ण

	अगर (atl1c_पढ़ो_current_addr(hw, hw->perm_mac_addr))
		वापस 0;

	वापस -1;
पूर्ण

bool atl1c_पढ़ो_eeprom(काष्ठा atl1c_hw *hw, u32 offset, u32 *p_value)
अणु
	पूर्णांक i;
	bool ret = false;
	u32 otp_ctrl_data;
	u32 control;
	u32 data;

	अगर (offset & 3)
		वापस ret; /* address करो not align */

	AT_READ_REG(hw, REG_OTP_CTRL, &otp_ctrl_data);
	अगर (!(otp_ctrl_data & OTP_CTRL_CLK_EN))
		AT_WRITE_REG(hw, REG_OTP_CTRL,
				(otp_ctrl_data | OTP_CTRL_CLK_EN));

	AT_WRITE_REG(hw, REG_EEPROM_DATA_LO, 0);
	control = (offset & EEPROM_CTRL_ADDR_MASK) << EEPROM_CTRL_ADDR_SHIFT;
	AT_WRITE_REG(hw, REG_EEPROM_CTRL, control);

	क्रम (i = 0; i < 10; i++) अणु
		udelay(100);
		AT_READ_REG(hw, REG_EEPROM_CTRL, &control);
		अगर (control & EEPROM_CTRL_RW)
			अवरोध;
	पूर्ण
	अगर (control & EEPROM_CTRL_RW) अणु
		AT_READ_REG(hw, REG_EEPROM_CTRL, &data);
		AT_READ_REG(hw, REG_EEPROM_DATA_LO, p_value);
		data = data & 0xFFFF;
		*p_value = swab32((data << 16) | (*p_value >> 16));
		ret = true;
	पूर्ण
	अगर (!(otp_ctrl_data & OTP_CTRL_CLK_EN))
		AT_WRITE_REG(hw, REG_OTP_CTRL, otp_ctrl_data);

	वापस ret;
पूर्ण
/*
 * Reads the adapter's MAC address from the EEPROM
 *
 * hw - Struct containing variables accessed by shared code
 */
पूर्णांक atl1c_पढ़ो_mac_addr(काष्ठा atl1c_hw *hw)
अणु
	पूर्णांक err = 0;

	err = atl1c_get_permanent_address(hw);
	अगर (err)
		eth_अक्रमom_addr(hw->perm_mac_addr);

	स_नकल(hw->mac_addr, hw->perm_mac_addr, माप(hw->perm_mac_addr));
	वापस err;
पूर्ण

/*
 * atl1c_hash_mc_addr
 *  purpose
 *      set hash value क्रम a multicast address
 *      hash calcu processing :
 *          1. calcu 32bit CRC क्रम multicast address
 *          2. reverse crc with MSB to LSB
 */
u32 atl1c_hash_mc_addr(काष्ठा atl1c_hw *hw, u8 *mc_addr)
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
व्योम atl1c_hash_set(काष्ठा atl1c_hw *hw, u32 hash_value)
अणु
	u32 hash_bit, hash_reg;
	u32 mta;

	/*
	 * The HASH Table  is a रेजिस्टर array of 2 32-bit रेजिस्टरs.
	 * It is treated like an array of 64 bits.  We want to set
	 * bit BitArray[hash_value]. So we figure out what रेजिस्टर
	 * the bit is in, पढ़ो it, OR in the new bit, then ग_लिखो
	 * back the new value.  The रेजिस्टर is determined by the
	 * upper bit of the hash value and the bit within that
	 * रेजिस्टर are determined by the lower 5 bits of the value.
	 */
	hash_reg = (hash_value >> 31) & 0x1;
	hash_bit = (hash_value >> 26) & 0x1F;

	mta = AT_READ_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg);

	mta |= (1 << hash_bit);

	AT_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, hash_reg, mta);
पूर्ण

/*
 * रुको mdio module be idle
 * वापस true: idle
 *        false: still busy
 */
bool atl1c_रुको_mdio_idle(काष्ठा atl1c_hw *hw)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < MDIO_MAX_AC_TO; i++) अणु
		AT_READ_REG(hw, REG_MDIO_CTRL, &val);
		अगर (!(val & (MDIO_CTRL_BUSY | MDIO_CTRL_START)))
			अवरोध;
		udelay(10);
	पूर्ण

	वापस i != MDIO_MAX_AC_TO;
पूर्ण

व्योम atl1c_stop_phy_polling(काष्ठा atl1c_hw *hw)
अणु
	अगर (!(hw->ctrl_flags & ATL1C_FPGA_VERSION))
		वापस;

	AT_WRITE_REG(hw, REG_MDIO_CTRL, 0);
	atl1c_रुको_mdio_idle(hw);
पूर्ण

व्योम atl1c_start_phy_polling(काष्ठा atl1c_hw *hw, u16 clk_sel)
अणु
	u32 val;

	अगर (!(hw->ctrl_flags & ATL1C_FPGA_VERSION))
		वापस;

	val = MDIO_CTRL_SPRES_PRMBL |
		FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
		FIELDX(MDIO_CTRL_REG, 1) |
		MDIO_CTRL_START |
		MDIO_CTRL_OP_READ;
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);
	atl1c_रुको_mdio_idle(hw);
	val |= MDIO_CTRL_AP_EN;
	val &= ~MDIO_CTRL_START;
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);
	udelay(30);
पूर्ण


/*
 * atl1c_पढ़ो_phy_core
 * core function to पढ़ो रेजिस्टर in PHY via MDIO control रेजिस्टर.
 * ext: extension रेजिस्टर (see IEEE 802.3)
 * dev: device address (see IEEE 802.3 DEVAD, PRTAD is fixed to 0)
 * reg: reg to पढ़ो
 */
पूर्णांक atl1c_पढ़ो_phy_core(काष्ठा atl1c_hw *hw, bool ext, u8 dev,
			u16 reg, u16 *phy_data)
अणु
	u32 val;
	u16 clk_sel = MDIO_CTRL_CLK_25_4;

	atl1c_stop_phy_polling(hw);

	*phy_data = 0;

	/* only l2c_b2 & l1d_2 could use slow घड़ी */
	अगर ((hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) &&
		hw->hibernate)
		clk_sel = MDIO_CTRL_CLK_25_128;
	अगर (ext) अणु
		val = FIELDX(MDIO_EXTN_DEVAD, dev) | FIELDX(MDIO_EXTN_REG, reg);
		AT_WRITE_REG(hw, REG_MDIO_EXTN, val);
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			MDIO_CTRL_START |
			MDIO_CTRL_MODE_EXT |
			MDIO_CTRL_OP_READ;
	पूर्ण अन्यथा अणु
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			FIELDX(MDIO_CTRL_REG, reg) |
			MDIO_CTRL_START |
			MDIO_CTRL_OP_READ;
	पूर्ण
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);

	अगर (!atl1c_रुको_mdio_idle(hw))
		वापस -1;

	AT_READ_REG(hw, REG_MDIO_CTRL, &val);
	*phy_data = (u16)FIELD_GETX(val, MDIO_CTRL_DATA);

	atl1c_start_phy_polling(hw, clk_sel);

	वापस 0;
पूर्ण

/*
 * atl1c_ग_लिखो_phy_core
 * core function to ग_लिखो to रेजिस्टर in PHY via MDIO control रेजिस्टर.
 * ext: extension रेजिस्टर (see IEEE 802.3)
 * dev: device address (see IEEE 802.3 DEVAD, PRTAD is fixed to 0)
 * reg: reg to ग_लिखो
 */
पूर्णांक atl1c_ग_लिखो_phy_core(काष्ठा atl1c_hw *hw, bool ext, u8 dev,
			u16 reg, u16 phy_data)
अणु
	u32 val;
	u16 clk_sel = MDIO_CTRL_CLK_25_4;

	atl1c_stop_phy_polling(hw);


	/* only l2c_b2 & l1d_2 could use slow घड़ी */
	अगर ((hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) &&
		hw->hibernate)
		clk_sel = MDIO_CTRL_CLK_25_128;

	अगर (ext) अणु
		val = FIELDX(MDIO_EXTN_DEVAD, dev) | FIELDX(MDIO_EXTN_REG, reg);
		AT_WRITE_REG(hw, REG_MDIO_EXTN, val);
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			FIELDX(MDIO_CTRL_DATA, phy_data) |
			MDIO_CTRL_START |
			MDIO_CTRL_MODE_EXT;
	पूर्ण अन्यथा अणु
		val = MDIO_CTRL_SPRES_PRMBL |
			FIELDX(MDIO_CTRL_CLK_SEL, clk_sel) |
			FIELDX(MDIO_CTRL_DATA, phy_data) |
			FIELDX(MDIO_CTRL_REG, reg) |
			MDIO_CTRL_START;
	पूर्ण
	AT_WRITE_REG(hw, REG_MDIO_CTRL, val);

	अगर (!atl1c_रुको_mdio_idle(hw))
		वापस -1;

	atl1c_start_phy_polling(hw, clk_sel);

	वापस 0;
पूर्ण

/*
 * Reads the value from a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to पढ़ो
 */
पूर्णांक atl1c_पढ़ो_phy_reg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 *phy_data)
अणु
	वापस atl1c_पढ़ो_phy_core(hw, false, 0, reg_addr, phy_data);
पूर्ण

/*
 * Writes a value to a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to ग_लिखो
 * data - data to ग_लिखो to the PHY
 */
पूर्णांक atl1c_ग_लिखो_phy_reg(काष्ठा atl1c_hw *hw, u32 reg_addr, u16 phy_data)
अणु
	वापस atl1c_ग_लिखो_phy_core(hw, false, 0, reg_addr, phy_data);
पूर्ण

/* पढ़ो from PHY extension रेजिस्टर */
पूर्णांक atl1c_पढ़ो_phy_ext(काष्ठा atl1c_hw *hw, u8 dev_addr,
			u16 reg_addr, u16 *phy_data)
अणु
	वापस atl1c_पढ़ो_phy_core(hw, true, dev_addr, reg_addr, phy_data);
पूर्ण

/* ग_लिखो to PHY extension रेजिस्टर */
पूर्णांक atl1c_ग_लिखो_phy_ext(काष्ठा atl1c_hw *hw, u8 dev_addr,
			u16 reg_addr, u16 phy_data)
अणु
	वापस atl1c_ग_लिखो_phy_core(hw, true, dev_addr, reg_addr, phy_data);
पूर्ण

पूर्णांक atl1c_पढ़ो_phy_dbg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 *phy_data)
अणु
	पूर्णांक err;

	err = atl1c_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, reg_addr);
	अगर (unlikely(err))
		वापस err;
	अन्यथा
		err = atl1c_पढ़ो_phy_reg(hw, MII_DBG_DATA, phy_data);

	वापस err;
पूर्ण

पूर्णांक atl1c_ग_लिखो_phy_dbg(काष्ठा atl1c_hw *hw, u16 reg_addr, u16 phy_data)
अणु
	पूर्णांक err;

	err = atl1c_ग_लिखो_phy_reg(hw, MII_DBG_ADDR, reg_addr);
	अगर (unlikely(err))
		वापस err;
	अन्यथा
		err = atl1c_ग_लिखो_phy_reg(hw, MII_DBG_DATA, phy_data);

	वापस err;
पूर्ण

/*
 * Configures PHY स्वतःneg and flow control advertisement settings
 *
 * hw - Struct containing variables accessed by shared code
 */
अटल पूर्णांक atl1c_phy_setup_adv(काष्ठा atl1c_hw *hw)
अणु
	u16 mii_adv_data = ADVERTISE_DEFAULT_CAP & ~ADVERTISE_ALL;
	u16 mii_giga_ctrl_data = GIGA_CR_1000T_DEFAULT_CAP &
				~GIGA_CR_1000T_SPEED_MASK;

	अगर (hw->स्वतःneg_advertised & ADVERTISED_10baseT_Half)
		mii_adv_data |= ADVERTISE_10HALF;
	अगर (hw->स्वतःneg_advertised & ADVERTISED_10baseT_Full)
		mii_adv_data |= ADVERTISE_10FULL;
	अगर (hw->स्वतःneg_advertised & ADVERTISED_100baseT_Half)
		mii_adv_data |= ADVERTISE_100HALF;
	अगर (hw->स्वतःneg_advertised & ADVERTISED_100baseT_Full)
		mii_adv_data |= ADVERTISE_100FULL;

	अगर (hw->स्वतःneg_advertised & ADVERTISED_Autoneg)
		mii_adv_data |= ADVERTISE_10HALF  | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL;

	अगर (hw->link_cap_flags & ATL1C_LINK_CAP_1000M) अणु
		अगर (hw->स्वतःneg_advertised & ADVERTISED_1000baseT_Half)
			mii_giga_ctrl_data |= ADVERTISE_1000HALF;
		अगर (hw->स्वतःneg_advertised & ADVERTISED_1000baseT_Full)
			mii_giga_ctrl_data |= ADVERTISE_1000FULL;
		अगर (hw->स्वतःneg_advertised & ADVERTISED_Autoneg)
			mii_giga_ctrl_data |= ADVERTISE_1000HALF |
					ADVERTISE_1000FULL;
	पूर्ण

	अगर (atl1c_ग_लिखो_phy_reg(hw, MII_ADVERTISE, mii_adv_data) != 0 ||
	    atl1c_ग_लिखो_phy_reg(hw, MII_CTRL1000, mii_giga_ctrl_data) != 0)
		वापस -1;
	वापस 0;
पूर्ण

व्योम atl1c_phy_disable(काष्ठा atl1c_hw *hw)
अणु
	atl1c_घातer_saving(hw, 0);
पूर्ण


पूर्णांक atl1c_phy_reset(काष्ठा atl1c_hw *hw)
अणु
	काष्ठा atl1c_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u16 phy_data;
	u32 phy_ctrl_data, lpi_ctrl;
	पूर्णांक err;

	/* reset PHY core */
	AT_READ_REG(hw, REG_GPHY_CTRL, &phy_ctrl_data);
	phy_ctrl_data &= ~(GPHY_CTRL_EXT_RESET | GPHY_CTRL_PHY_IDDQ |
		GPHY_CTRL_GATE_25M_EN | GPHY_CTRL_PWDOWN_HW | GPHY_CTRL_CLS);
	phy_ctrl_data |= GPHY_CTRL_SEL_ANA_RST;
	अगर (!(hw->ctrl_flags & ATL1C_HIB_DISABLE))
		phy_ctrl_data |= (GPHY_CTRL_HIB_EN | GPHY_CTRL_HIB_PULSE);
	अन्यथा
		phy_ctrl_data &= ~(GPHY_CTRL_HIB_EN | GPHY_CTRL_HIB_PULSE);
	AT_WRITE_REG(hw, REG_GPHY_CTRL, phy_ctrl_data);
	AT_WRITE_FLUSH(hw);
	udelay(10);
	AT_WRITE_REG(hw, REG_GPHY_CTRL, phy_ctrl_data | GPHY_CTRL_EXT_RESET);
	AT_WRITE_FLUSH(hw);
	udelay(10 * GPHY_CTRL_EXT_RST_TO);	/* delay 800us */

	/* चयन घड़ी */
	अगर (hw->nic_type == athr_l2c_b) अणु
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_CFGLPSPD, &phy_data);
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_CFGLPSPD,
			phy_data & ~CFGLPSPD_RSTCNT_CLK125SW);
	पूर्ण

	/* tx-half amplitude issue fix */
	अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2) अणु
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_CABLE1TH_DET, &phy_data);
		phy_data |= CABLE1TH_DET_EN;
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_CABLE1TH_DET, phy_data);
	पूर्ण

	/* clear bit3 of dbgport 3B to lower voltage */
	अगर (!(hw->ctrl_flags & ATL1C_HIB_DISABLE)) अणु
		अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2) अणु
			atl1c_पढ़ो_phy_dbg(hw, MIIDBG_VOLT_CTRL, &phy_data);
			phy_data &= ~VOLT_CTRL_SWLOWEST;
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_VOLT_CTRL, phy_data);
		पूर्ण
		/* घातer saving config */
		phy_data =
			hw->nic_type == athr_l1d || hw->nic_type == athr_l1d_2 ?
			L1D_LEGCYPS_DEF : L1C_LEGCYPS_DEF;
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_LEGCYPS, phy_data);
		/* hib */
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_SYSMODCTRL,
			SYSMODCTRL_IECHOADJ_DEF);
	पूर्ण अन्यथा अणु
		/* disable pws */
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_LEGCYPS, &phy_data);
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_LEGCYPS,
			phy_data & ~LEGCYPS_EN);
		/* disable hibernate */
		atl1c_पढ़ो_phy_dbg(hw, MIIDBG_HIBNEG, &phy_data);
		atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_HIBNEG,
			phy_data & HIBNEG_PSHIB_EN);
	पूर्ण
	/* disable AZ(EEE) by शेष */
	अगर (hw->nic_type == athr_l1d || hw->nic_type == athr_l1d_2 ||
	    hw->nic_type == athr_l2c_b2) अणु
		AT_READ_REG(hw, REG_LPI_CTRL, &lpi_ctrl);
		AT_WRITE_REG(hw, REG_LPI_CTRL, lpi_ctrl & ~LPI_CTRL_EN);
		atl1c_ग_लिखो_phy_ext(hw, MIIEXT_ANEG, MIIEXT_LOCAL_EEEADV, 0);
		atl1c_ग_लिखो_phy_ext(hw, MIIEXT_PCS, MIIEXT_CLDCTRL3,
			L2CB_CLDCTRL3);
	पूर्ण

	/* other debug port to set */
	atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_ANACTRL, ANACTRL_DEF);
	atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_SRDSYSMOD, SRDSYSMOD_DEF);
	atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_TST10BTCFG, TST10BTCFG_DEF);
	/* UNH-IOL test issue, set bit7 */
	atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_TST100BTCFG,
		TST100BTCFG_DEF | TST100BTCFG_LITCH_EN);

	/* set phy पूर्णांकerrupt mask */
	phy_data = IER_LINK_UP | IER_LINK_DOWN;
	err = atl1c_ग_लिखो_phy_reg(hw, MII_IER, phy_data);
	अगर (err) अणु
		अगर (netअगर_msg_hw(adapter))
			dev_err(&pdev->dev,
				"Error enable PHY linkChange Interrupt\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक atl1c_phy_init(काष्ठा atl1c_hw *hw)
अणु
	काष्ठा atl1c_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक ret_val;
	u16 mii_bmcr_data = BMCR_RESET;

	अगर ((atl1c_पढ़ो_phy_reg(hw, MII_PHYSID1, &hw->phy_id1) != 0) ||
		(atl1c_पढ़ो_phy_reg(hw, MII_PHYSID2, &hw->phy_id2) != 0)) अणु
		dev_err(&pdev->dev, "Error get phy ID\n");
		वापस -1;
	पूर्ण
	चयन (hw->media_type) अणु
	हाल MEDIA_TYPE_AUTO_SENSOR:
		ret_val = atl1c_phy_setup_adv(hw);
		अगर (ret_val) अणु
			अगर (netअगर_msg_link(adapter))
				dev_err(&pdev->dev,
					"Error Setting up Auto-Negotiation\n");
			वापस ret_val;
		पूर्ण
		mii_bmcr_data |= BMCR_ANENABLE | BMCR_ANRESTART;
		अवरोध;
	हाल MEDIA_TYPE_100M_FULL:
		mii_bmcr_data |= BMCR_SPEED100 | BMCR_FULLDPLX;
		अवरोध;
	हाल MEDIA_TYPE_100M_HALF:
		mii_bmcr_data |= BMCR_SPEED100;
		अवरोध;
	हाल MEDIA_TYPE_10M_FULL:
		mii_bmcr_data |= BMCR_FULLDPLX;
		अवरोध;
	हाल MEDIA_TYPE_10M_HALF:
		अवरोध;
	शेष:
		अगर (netअगर_msg_link(adapter))
			dev_err(&pdev->dev, "Wrong Media type %d\n",
				hw->media_type);
		वापस -1;
	पूर्ण

	ret_val = atl1c_ग_लिखो_phy_reg(hw, MII_BMCR, mii_bmcr_data);
	अगर (ret_val)
		वापस ret_val;
	hw->phy_configured = true;

	वापस 0;
पूर्ण

/*
 * Detects the current speed and duplex settings of the hardware.
 *
 * hw - Struct containing variables accessed by shared code
 * speed - Speed of the connection
 * duplex - Duplex setting of the connection
 */
पूर्णांक atl1c_get_speed_and_duplex(काष्ठा atl1c_hw *hw, u16 *speed, u16 *duplex)
अणु
	पूर्णांक err;
	u16 phy_data;

	/* Read   PHY Specअगरic Status Register (17) */
	err = atl1c_पढ़ो_phy_reg(hw, MII_GIGA_PSSR, &phy_data);
	अगर (err)
		वापस err;

	अगर (!(phy_data & GIGA_PSSR_SPD_DPLX_RESOLVED))
		वापस -1;

	चयन (phy_data & GIGA_PSSR_SPEED) अणु
	हाल GIGA_PSSR_1000MBS:
		*speed = SPEED_1000;
		अवरोध;
	हाल GIGA_PSSR_100MBS:
		*speed = SPEED_100;
		अवरोध;
	हाल  GIGA_PSSR_10MBS:
		*speed = SPEED_10;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (phy_data & GIGA_PSSR_DPLX)
		*duplex = FULL_DUPLEX;
	अन्यथा
		*duplex = HALF_DUPLEX;

	वापस 0;
पूर्ण

/* select one link mode to get lower घातer consumption */
पूर्णांक atl1c_phy_to_ps_link(काष्ठा atl1c_hw *hw)
अणु
	काष्ठा atl1c_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक ret = 0;
	u16 स्वतःneg_advertised = ADVERTISED_10baseT_Half;
	u16 save_स्वतःneg_advertised;
	u16 phy_data;
	u16 mii_lpa_data;
	u16 speed = SPEED_0;
	u16 duplex = FULL_DUPLEX;
	पूर्णांक i;

	atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	अगर (phy_data & BMSR_LSTATUS) अणु
		atl1c_पढ़ो_phy_reg(hw, MII_LPA, &mii_lpa_data);
		अगर (mii_lpa_data & LPA_10FULL)
			स्वतःneg_advertised = ADVERTISED_10baseT_Full;
		अन्यथा अगर (mii_lpa_data & LPA_10HALF)
			स्वतःneg_advertised = ADVERTISED_10baseT_Half;
		अन्यथा अगर (mii_lpa_data & LPA_100HALF)
			स्वतःneg_advertised = ADVERTISED_100baseT_Half;
		अन्यथा अगर (mii_lpa_data & LPA_100FULL)
			स्वतःneg_advertised = ADVERTISED_100baseT_Full;

		save_स्वतःneg_advertised = hw->स्वतःneg_advertised;
		hw->phy_configured = false;
		hw->स्वतःneg_advertised = स्वतःneg_advertised;
		अगर (atl1c_restart_स्वतःneg(hw) != 0) अणु
			dev_dbg(&pdev->dev, "phy autoneg failed\n");
			ret = -1;
		पूर्ण
		hw->स्वतःneg_advertised = save_स्वतःneg_advertised;

		अगर (mii_lpa_data) अणु
			क्रम (i = 0; i < AT_SUSPEND_LINK_TIMEOUT; i++) अणु
				mdelay(100);
				atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
				atl1c_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
				अगर (phy_data & BMSR_LSTATUS) अणु
					अगर (atl1c_get_speed_and_duplex(hw, &speed,
									&duplex) != 0)
						dev_dbg(&pdev->dev,
							"get speed and duplex failed\n");
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		speed = SPEED_10;
		duplex = HALF_DUPLEX;
	पूर्ण
	adapter->link_speed = speed;
	adapter->link_duplex = duplex;

	वापस ret;
पूर्ण

पूर्णांक atl1c_restart_स्वतःneg(काष्ठा atl1c_hw *hw)
अणु
	पूर्णांक err = 0;
	u16 mii_bmcr_data = BMCR_RESET;

	err = atl1c_phy_setup_adv(hw);
	अगर (err)
		वापस err;
	mii_bmcr_data |= BMCR_ANENABLE | BMCR_ANRESTART;

	वापस atl1c_ग_लिखो_phy_reg(hw, MII_BMCR, mii_bmcr_data);
पूर्ण

पूर्णांक atl1c_घातer_saving(काष्ठा atl1c_hw *hw, u32 wufc)
अणु
	काष्ठा atl1c_adapter *adapter = hw->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 master_ctrl, mac_ctrl, phy_ctrl;
	u32 wol_ctrl, speed;
	u16 phy_data;

	wol_ctrl = 0;
	speed = adapter->link_speed == SPEED_1000 ?
		MAC_CTRL_SPEED_1000 : MAC_CTRL_SPEED_10_100;

	AT_READ_REG(hw, REG_MASTER_CTRL, &master_ctrl);
	AT_READ_REG(hw, REG_MAC_CTRL, &mac_ctrl);
	AT_READ_REG(hw, REG_GPHY_CTRL, &phy_ctrl);

	master_ctrl &= ~MASTER_CTRL_CLK_SEL_DIS;
	mac_ctrl = FIELD_SETX(mac_ctrl, MAC_CTRL_SPEED, speed);
	mac_ctrl &= ~(MAC_CTRL_DUPLX | MAC_CTRL_RX_EN | MAC_CTRL_TX_EN);
	अगर (adapter->link_duplex == FULL_DUPLEX)
		mac_ctrl |= MAC_CTRL_DUPLX;
	phy_ctrl &= ~(GPHY_CTRL_EXT_RESET | GPHY_CTRL_CLS);
	phy_ctrl |= GPHY_CTRL_SEL_ANA_RST | GPHY_CTRL_HIB_PULSE |
		GPHY_CTRL_HIB_EN;
	अगर (!wufc) अणु /* without WoL */
		master_ctrl |= MASTER_CTRL_CLK_SEL_DIS;
		phy_ctrl |= GPHY_CTRL_PHY_IDDQ | GPHY_CTRL_PWDOWN_HW;
		AT_WRITE_REG(hw, REG_MASTER_CTRL, master_ctrl);
		AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl);
		AT_WRITE_REG(hw, REG_GPHY_CTRL, phy_ctrl);
		AT_WRITE_REG(hw, REG_WOL_CTRL, 0);
		hw->phy_configured = false; /* re-init PHY when resume */
		वापस 0;
	पूर्ण
	phy_ctrl |= GPHY_CTRL_EXT_RESET;
	अगर (wufc & AT_WUFC_MAG) अणु
		mac_ctrl |= MAC_CTRL_RX_EN | MAC_CTRL_BC_EN;
		wol_ctrl |= WOL_MAGIC_EN | WOL_MAGIC_PME_EN;
		अगर (hw->nic_type == athr_l2c_b && hw->revision_id == L2CB_V11)
			wol_ctrl |= WOL_PATTERN_EN | WOL_PATTERN_PME_EN;
	पूर्ण
	अगर (wufc & AT_WUFC_LNKC) अणु
		wol_ctrl |= WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN;
		अगर (atl1c_ग_लिखो_phy_reg(hw, MII_IER, IER_LINK_UP) != 0) अणु
			dev_dbg(&pdev->dev, "%s: write phy MII_IER failed.\n",
				atl1c_driver_name);
		पूर्ण
	पूर्ण
	/* clear PHY पूर्णांकerrupt */
	atl1c_पढ़ो_phy_reg(hw, MII_ISR, &phy_data);

	dev_dbg(&pdev->dev, "%s: suspend MAC=%x,MASTER=%x,PHY=0x%x,WOL=%x\n",
		atl1c_driver_name, mac_ctrl, master_ctrl, phy_ctrl, wol_ctrl);
	AT_WRITE_REG(hw, REG_MASTER_CTRL, master_ctrl);
	AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl);
	AT_WRITE_REG(hw, REG_GPHY_CTRL, phy_ctrl);
	AT_WRITE_REG(hw, REG_WOL_CTRL, wol_ctrl);

	वापस 0;
पूर्ण


/* configure phy after Link change Event */
व्योम atl1c_post_phy_linkchg(काष्ठा atl1c_hw *hw, u16 link_speed)
अणु
	u16 phy_val;
	bool adj_thresh = false;

	अगर (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l2c_b2 ||
	    hw->nic_type == athr_l1d || hw->nic_type == athr_l1d_2)
		adj_thresh = true;

	अगर (link_speed != SPEED_0) अणु /* link up */
		/* az with brcm, half-amp */
		अगर (hw->nic_type == athr_l1d_2) अणु
			atl1c_पढ़ो_phy_ext(hw, MIIEXT_PCS, MIIEXT_CLDCTRL6,
				&phy_val);
			phy_val = FIELD_GETX(phy_val, CLDCTRL6_CAB_LEN);
			phy_val = phy_val > CLDCTRL6_CAB_LEN_SHORT ?
				AZ_ANADECT_LONG : AZ_ANADECT_DEF;
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_AZ_ANADECT, phy_val);
		पूर्ण
		/* threshold adjust */
		अगर (adj_thresh && link_speed == SPEED_100 && hw->msi_lnkpatch) अणु
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_MSE16DB, L1D_MSE16DB_UP);
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_SYSMODCTRL,
				L1D_SYSMODCTRL_IECHOADJ_DEF);
		पूर्ण
	पूर्ण अन्यथा अणु /* link करोwn */
		अगर (adj_thresh && hw->msi_lnkpatch) अणु
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_SYSMODCTRL,
				SYSMODCTRL_IECHOADJ_DEF);
			atl1c_ग_लिखो_phy_dbg(hw, MIIDBG_MSE16DB,
				L1D_MSE16DB_DOWN);
		पूर्ण
	पूर्ण
पूर्ण

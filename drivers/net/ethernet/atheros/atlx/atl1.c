<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2005 - 2006 Attansic Corporation. All rights reserved.
 * Copyright(c) 2006 - 2007 Chris Snook <csnook@redhat.com>
 * Copyright(c) 2006 - 2008 Jay Cliburn <jcliburn@gmail.com>
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * Xiong Huang <xiong.huang@atheros.com>
 * Jie Yang <jie.yang@atheros.com>
 * Chris Snook <csnook@redhat.com>
 * Jay Cliburn <jcliburn@gmail.com>
 *
 * This version is adapted from the Attansic reference driver.
 *
 * TODO:
 * Add more ethtool functions.
 * Fix असलtruse irq enable/disable condition described here:
 *	http://marc.theaimsgroup.com/?l=linux-netdev&m=116398508500553&w=2
 *
 * NEEDS TESTING:
 * VLAN
 * multicast
 * promiscuous mode
 * पूर्णांकerrupt coalescing
 * SMP torture testing
 */

#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/compiler.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pm.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/tcp.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <net/checksum.h>

#समावेश "atl1.h"

MODULE_AUTHOR("Xiong Huang <xiong.huang@atheros.com>, "
	      "Chris Snook <csnook@redhat.com>, "
	      "Jay Cliburn <jcliburn@gmail.com>");
MODULE_LICENSE("GPL");

/* Temporary hack क्रम merging atl1 and atl2 */
#समावेश "atlx.c"

अटल स्थिर काष्ठा ethtool_ops atl1_ethtool_ops;

/*
 * This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */
#घोषणा ATL1_MAX_NIC 4

#घोषणा OPTION_UNSET    -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

#घोषणा ATL1_PARAM_INIT अणु [0 ... ATL1_MAX_NIC] = OPTION_UNSET पूर्ण

/*
 * Interrupt Moderate Timer in units of 2 us
 *
 * Valid Range: 10-65535
 *
 * Default Value: 100 (200us)
 */
अटल पूर्णांक पूर्णांक_mod_समयr[ATL1_MAX_NIC+1] = ATL1_PARAM_INIT;
अटल अचिन्हित पूर्णांक num_पूर्णांक_mod_समयr;
module_param_array_named(पूर्णांक_mod_समयr, पूर्णांक_mod_समयr, पूर्णांक,
	&num_पूर्णांक_mod_समयr, 0);
MODULE_PARM_DESC(पूर्णांक_mod_समयr, "Interrupt moderator timer");

#घोषणा DEFAULT_INT_MOD_CNT	100	/* 200us */
#घोषणा MAX_INT_MOD_CNT		65000
#घोषणा MIN_INT_MOD_CNT		50

काष्ठा atl1_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	अक्षर *name;
	अक्षर *err;
	पूर्णांक def;
	जोड़ अणु
		काष्ठा अणु	/* range_option info */
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		काष्ठा अणु	/* list_option info */
			पूर्णांक nr;
			काष्ठा atl1_opt_list अणु
				पूर्णांक i;
				अक्षर *str;
			पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल पूर्णांक atl1_validate_option(पूर्णांक *value, काष्ठा atl1_option *opt,
				काष्ठा pci_dev *pdev)
अणु
	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			dev_info(&pdev->dev, "%s enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			dev_info(&pdev->dev, "%s disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			dev_info(&pdev->dev, "%s set to %i\n", opt->name,
				*value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option:अणु
			पूर्णांक i;
			काष्ठा atl1_opt_list *ent;

			क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
				ent = &opt->arg.l.p[i];
				अगर (*value == ent->i) अणु
					अगर (ent->str[0] != '\0')
						dev_info(&pdev->dev, "%s\n",
							ent->str);
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	dev_info(&pdev->dev, "invalid %s specified (%i) %s\n",
		opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * atl1_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 */
अटल व्योम atl1_check_options(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक bd = adapter->bd_number;
	अगर (bd >= ATL1_MAX_NIC) अणु
		dev_notice(&pdev->dev, "no configuration for board#%i\n", bd);
		dev_notice(&pdev->dev, "using defaults for all values\n");
	पूर्ण
	अणु			/* Interrupt Moderate Timer */
		काष्ठा atl1_option opt = अणु
			.type = range_option,
			.name = "Interrupt Moderator Timer",
			.err = "using default of "
				__MODULE_STRING(DEFAULT_INT_MOD_CNT),
			.def = DEFAULT_INT_MOD_CNT,
			.arg = अणु.r = अणु.min = MIN_INT_MOD_CNT,
					.max = MAX_INT_MOD_CNTपूर्ण पूर्ण
		पूर्ण;
		पूर्णांक val;
		अगर (num_पूर्णांक_mod_समयr > bd) अणु
			val = पूर्णांक_mod_समयr[bd];
			atl1_validate_option(&val, &opt, pdev);
			adapter->imt = (u16) val;
		पूर्ण अन्यथा
			adapter->imt = (u16) (opt.def);
	पूर्ण
पूर्ण

/*
 * atl1_pci_tbl - PCI Device ID Table
 */
अटल स्थिर काष्ठा pci_device_id atl1_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_ATTANSIC, PCI_DEVICE_ID_ATTANSIC_L1)पूर्ण,
	/* required last entry */
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, atl1_pci_tbl);

अटल स्थिर u32 atl1_शेष_msg = NETIF_MSG_DRV | NETIF_MSG_PROBE |
	NETIF_MSG_LINK | NETIF_MSG_TIMER | NETIF_MSG_IFDOWN | NETIF_MSG_IFUP;

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Message level (0=none,...,16=all)");

/*
 * Reset the transmit and receive units; mask and clear all पूर्णांकerrupts.
 * hw - Struct containing variables accessed by shared code
 * वापस : 0  or  idle status (अगर error)
 */
अटल s32 atl1_reset_hw(काष्ठा atl1_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->back->pdev;
	काष्ठा atl1_adapter *adapter = hw->back;
	u32 icr;
	पूर्णांक i;

	/*
	 * Clear Interrupt mask to stop board from generating
	 * पूर्णांकerrupts & Clear any pending पूर्णांकerrupt events
	 */
	/*
	 * atlx_irq_disable(adapter);
	 * ioग_लिखो32(0xffffffff, hw->hw_addr + REG_ISR);
	 */

	/*
	 * Issue Soft Reset to the MAC.  This will reset the chip's
	 * transmit, receive, DMA.  It will not effect
	 * the current PCI configuration.  The global reset bit is self-
	 * clearing, and should clear within a microsecond.
	 */
	ioग_लिखो32(MASTER_CTRL_SOFT_RST, hw->hw_addr + REG_MASTER_CTRL);
	ioपढ़ो32(hw->hw_addr + REG_MASTER_CTRL);

	ioग_लिखो16(1, hw->hw_addr + REG_PHY_ENABLE);
	ioपढ़ो16(hw->hw_addr + REG_PHY_ENABLE);

	/* delay about 1ms */
	msleep(1);

	/* Wait at least 10ms क्रम All module to be Idle */
	क्रम (i = 0; i < 10; i++) अणु
		icr = ioपढ़ो32(hw->hw_addr + REG_IDLE_STATUS);
		अगर (!icr)
			अवरोध;
		/* delay 1 ms */
		msleep(1);
		/* FIXME: still the right way to करो this? */
		cpu_relax();
	पूर्ण

	अगर (icr) अणु
		अगर (netअगर_msg_hw(adapter))
			dev_dbg(&pdev->dev, "ICR = 0x%x\n", icr);
		वापस icr;
	पूर्ण

	वापस 0;
पूर्ण

/* function about EEPROM
 *
 * check_eeprom_exist
 * वापस 0 अगर eeprom exist
 */
अटल पूर्णांक atl1_check_eeprom_exist(काष्ठा atl1_hw *hw)
अणु
	u32 value;
	value = ioपढ़ो32(hw->hw_addr + REG_SPI_FLASH_CTRL);
	अगर (value & SPI_FLASH_CTRL_EN_VPD) अणु
		value &= ~SPI_FLASH_CTRL_EN_VPD;
		ioग_लिखो32(value, hw->hw_addr + REG_SPI_FLASH_CTRL);
	पूर्ण

	value = ioपढ़ो16(hw->hw_addr + REG_PCIE_CAP_LIST);
	वापस ((value & 0xFF00) == 0x6C00) ? 0 : 1;
पूर्ण

अटल bool atl1_पढ़ो_eeprom(काष्ठा atl1_hw *hw, u32 offset, u32 *p_value)
अणु
	पूर्णांक i;
	u32 control;

	अगर (offset & 3)
		/* address करो not align */
		वापस false;

	ioग_लिखो32(0, hw->hw_addr + REG_VPD_DATA);
	control = (offset & VPD_CAP_VPD_ADDR_MASK) << VPD_CAP_VPD_ADDR_SHIFT;
	ioग_लिखो32(control, hw->hw_addr + REG_VPD_CAP);
	ioपढ़ो32(hw->hw_addr + REG_VPD_CAP);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(2);
		control = ioपढ़ो32(hw->hw_addr + REG_VPD_CAP);
		अगर (control & VPD_CAP_VPD_FLAG)
			अवरोध;
	पूर्ण
	अगर (control & VPD_CAP_VPD_FLAG) अणु
		*p_value = ioपढ़ो32(hw->hw_addr + REG_VPD_DATA);
		वापस true;
	पूर्ण
	/* समयout */
	वापस false;
पूर्ण

/*
 * Reads the value from a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to पढ़ो
 */
अटल s32 atl1_पढ़ो_phy_reg(काष्ठा atl1_hw *hw, u16 reg_addr, u16 *phy_data)
अणु
	u32 val;
	पूर्णांक i;

	val = ((u32) (reg_addr & MDIO_REG_ADDR_MASK)) << MDIO_REG_ADDR_SHIFT |
		MDIO_START | MDIO_SUP_PREAMBLE | MDIO_RW | MDIO_CLK_25_4 <<
		MDIO_CLK_SEL_SHIFT;
	ioग_लिखो32(val, hw->hw_addr + REG_MDIO_CTRL);
	ioपढ़ो32(hw->hw_addr + REG_MDIO_CTRL);

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = ioपढ़ो32(hw->hw_addr + REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;
	पूर्ण
	अगर (!(val & (MDIO_START | MDIO_BUSY))) अणु
		*phy_data = (u16) val;
		वापस 0;
	पूर्ण
	वापस ATLX_ERR_PHY;
पूर्ण

#घोषणा CUSTOM_SPI_CS_SETUP	2
#घोषणा CUSTOM_SPI_CLK_HI	2
#घोषणा CUSTOM_SPI_CLK_LO	2
#घोषणा CUSTOM_SPI_CS_HOLD	2
#घोषणा CUSTOM_SPI_CS_HI	3

अटल bool atl1_spi_पढ़ो(काष्ठा atl1_hw *hw, u32 addr, u32 *buf)
अणु
	पूर्णांक i;
	u32 value;

	ioग_लिखो32(0, hw->hw_addr + REG_SPI_DATA);
	ioग_लिखो32(addr, hw->hw_addr + REG_SPI_ADDR);

	value = SPI_FLASH_CTRL_WAIT_READY |
	    (CUSTOM_SPI_CS_SETUP & SPI_FLASH_CTRL_CS_SETUP_MASK) <<
	    SPI_FLASH_CTRL_CS_SETUP_SHIFT | (CUSTOM_SPI_CLK_HI &
					     SPI_FLASH_CTRL_CLK_HI_MASK) <<
	    SPI_FLASH_CTRL_CLK_HI_SHIFT | (CUSTOM_SPI_CLK_LO &
					   SPI_FLASH_CTRL_CLK_LO_MASK) <<
	    SPI_FLASH_CTRL_CLK_LO_SHIFT | (CUSTOM_SPI_CS_HOLD &
					   SPI_FLASH_CTRL_CS_HOLD_MASK) <<
	    SPI_FLASH_CTRL_CS_HOLD_SHIFT | (CUSTOM_SPI_CS_HI &
					    SPI_FLASH_CTRL_CS_HI_MASK) <<
	    SPI_FLASH_CTRL_CS_HI_SHIFT | (1 & SPI_FLASH_CTRL_INS_MASK) <<
	    SPI_FLASH_CTRL_INS_SHIFT;

	ioग_लिखो32(value, hw->hw_addr + REG_SPI_FLASH_CTRL);

	value |= SPI_FLASH_CTRL_START;
	ioग_लिखो32(value, hw->hw_addr + REG_SPI_FLASH_CTRL);
	ioपढ़ो32(hw->hw_addr + REG_SPI_FLASH_CTRL);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(1);
		value = ioपढ़ो32(hw->hw_addr + REG_SPI_FLASH_CTRL);
		अगर (!(value & SPI_FLASH_CTRL_START))
			अवरोध;
	पूर्ण

	अगर (value & SPI_FLASH_CTRL_START)
		वापस false;

	*buf = ioपढ़ो32(hw->hw_addr + REG_SPI_DATA);

	वापस true;
पूर्ण

/*
 * get_permanent_address
 * वापस 0 अगर get valid mac address,
 */
अटल पूर्णांक atl1_get_permanent_address(काष्ठा atl1_hw *hw)
अणु
	u32 addr[2];
	u32 i, control;
	u16 reg;
	u8 eth_addr[ETH_ALEN];
	bool key_valid;

	अगर (is_valid_ether_addr(hw->perm_mac_addr))
		वापस 0;

	/* init */
	addr[0] = addr[1] = 0;

	अगर (!atl1_check_eeprom_exist(hw)) अणु
		reg = 0;
		key_valid = false;
		/* Read out all EEPROM content */
		i = 0;
		जबतक (1) अणु
			अगर (atl1_पढ़ो_eeprom(hw, i + 0x100, &control)) अणु
				अगर (key_valid) अणु
					अगर (reg == REG_MAC_STA_ADDR)
						addr[0] = control;
					अन्यथा अगर (reg == (REG_MAC_STA_ADDR + 4))
						addr[1] = control;
					key_valid = false;
				पूर्ण अन्यथा अगर ((control & 0xff) == 0x5A) अणु
					key_valid = true;
					reg = (u16) (control >> 16);
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण अन्यथा
				/* पढ़ो error */
				अवरोध;
			i += 4;
		पूर्ण

		*(u32 *) &eth_addr[2] = swab32(addr[0]);
		*(u16 *) &eth_addr[0] = swab16(*(u16 *) &addr[1]);
		अगर (is_valid_ether_addr(eth_addr)) अणु
			स_नकल(hw->perm_mac_addr, eth_addr, ETH_ALEN);
			वापस 0;
		पूर्ण
	पूर्ण

	/* see अगर SPI FLAGS exist ? */
	addr[0] = addr[1] = 0;
	reg = 0;
	key_valid = false;
	i = 0;
	जबतक (1) अणु
		अगर (atl1_spi_पढ़ो(hw, i + 0x1f000, &control)) अणु
			अगर (key_valid) अणु
				अगर (reg == REG_MAC_STA_ADDR)
					addr[0] = control;
				अन्यथा अगर (reg == (REG_MAC_STA_ADDR + 4))
					addr[1] = control;
				key_valid = false;
			पूर्ण अन्यथा अगर ((control & 0xff) == 0x5A) अणु
				key_valid = true;
				reg = (u16) (control >> 16);
			पूर्ण अन्यथा
				/* data end */
				अवरोध;
		पूर्ण अन्यथा
			/* पढ़ो error */
			अवरोध;
		i += 4;
	पूर्ण

	*(u32 *) &eth_addr[2] = swab32(addr[0]);
	*(u16 *) &eth_addr[0] = swab16(*(u16 *) &addr[1]);
	अगर (is_valid_ether_addr(eth_addr)) अणु
		स_नकल(hw->perm_mac_addr, eth_addr, ETH_ALEN);
		वापस 0;
	पूर्ण

	/*
	 * On some motherboards, the MAC address is written by the
	 * BIOS directly to the MAC रेजिस्टर during POST, and is
	 * not stored in eeprom.  If all अन्यथा thus far has failed
	 * to fetch the permanent MAC address, try पढ़ोing it directly.
	 */
	addr[0] = ioपढ़ो32(hw->hw_addr + REG_MAC_STA_ADDR);
	addr[1] = ioपढ़ो16(hw->hw_addr + (REG_MAC_STA_ADDR + 4));
	*(u32 *) &eth_addr[2] = swab32(addr[0]);
	*(u16 *) &eth_addr[0] = swab16(*(u16 *) &addr[1]);
	अगर (is_valid_ether_addr(eth_addr)) अणु
		स_नकल(hw->perm_mac_addr, eth_addr, ETH_ALEN);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Reads the adapter's MAC address from the EEPROM
 * hw - Struct containing variables accessed by shared code
 */
अटल s32 atl1_पढ़ो_mac_addr(काष्ठा atl1_hw *hw)
अणु
	s32 ret = 0;
	u16 i;

	अगर (atl1_get_permanent_address(hw)) अणु
		eth_अक्रमom_addr(hw->perm_mac_addr);
		ret = 1;
	पूर्ण

	क्रम (i = 0; i < ETH_ALEN; i++)
		hw->mac_addr[i] = hw->perm_mac_addr[i];
	वापस ret;
पूर्ण

/*
 * Hashes an address to determine its location in the multicast table
 * hw - Struct containing variables accessed by shared code
 * mc_addr - the multicast address to hash
 *
 * atl1_hash_mc_addr
 *  purpose
 *      set hash value क्रम a multicast address
 *      hash calcu processing :
 *          1. calcu 32bit CRC क्रम multicast address
 *          2. reverse crc with MSB to LSB
 */
अटल u32 atl1_hash_mc_addr(काष्ठा atl1_hw *hw, u8 *mc_addr)
अणु
	u32 crc32, value = 0;
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
अटल व्योम atl1_hash_set(काष्ठा atl1_hw *hw, u32 hash_value)
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
	mta = ioपढ़ो32((hw->hw_addr + REG_RX_HASH_TABLE) + (hash_reg << 2));
	mta |= (1 << hash_bit);
	ioग_लिखो32(mta, (hw->hw_addr + REG_RX_HASH_TABLE) + (hash_reg << 2));
पूर्ण

/*
 * Writes a value to a PHY रेजिस्टर
 * hw - Struct containing variables accessed by shared code
 * reg_addr - address of the PHY रेजिस्टर to ग_लिखो
 * data - data to ग_लिखो to the PHY
 */
अटल s32 atl1_ग_लिखो_phy_reg(काष्ठा atl1_hw *hw, u32 reg_addr, u16 phy_data)
अणु
	पूर्णांक i;
	u32 val;

	val = ((u32) (phy_data & MDIO_DATA_MASK)) << MDIO_DATA_SHIFT |
	    (reg_addr & MDIO_REG_ADDR_MASK) << MDIO_REG_ADDR_SHIFT |
	    MDIO_SUP_PREAMBLE |
	    MDIO_START | MDIO_CLK_25_4 << MDIO_CLK_SEL_SHIFT;
	ioग_लिखो32(val, hw->hw_addr + REG_MDIO_CTRL);
	ioपढ़ो32(hw->hw_addr + REG_MDIO_CTRL);

	क्रम (i = 0; i < MDIO_WAIT_TIMES; i++) अणु
		udelay(2);
		val = ioपढ़ो32(hw->hw_addr + REG_MDIO_CTRL);
		अगर (!(val & (MDIO_START | MDIO_BUSY)))
			अवरोध;
	पूर्ण

	अगर (!(val & (MDIO_START | MDIO_BUSY)))
		वापस 0;

	वापस ATLX_ERR_PHY;
पूर्ण

/*
 * Make L001's PHY out of Power Saving State (bug)
 * hw - Struct containing variables accessed by shared code
 * when घातer on, L001's PHY always on Power saving State
 * (Gigabit Link क्रमbidden)
 */
अटल s32 atl1_phy_leave_घातer_saving(काष्ठा atl1_hw *hw)
अणु
	s32 ret;
	ret = atl1_ग_लिखो_phy_reg(hw, 29, 0x0029);
	अगर (ret)
		वापस ret;
	वापस atl1_ग_लिखो_phy_reg(hw, 30, 0);
पूर्ण

/*
 * Resets the PHY and make all config validate
 * hw - Struct containing variables accessed by shared code
 *
 * Sets bit 15 and 12 of the MII Control regiser (क्रम F001 bug)
 */
अटल s32 atl1_phy_reset(काष्ठा atl1_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->back->pdev;
	काष्ठा atl1_adapter *adapter = hw->back;
	s32 ret_val;
	u16 phy_data;

	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL)
		phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN;
	अन्यथा अणु
		चयन (hw->media_type) अणु
		हाल MEDIA_TYPE_100M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_100 |
			    MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_100M_HALF:
			phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_10M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		शेष:
			/* MEDIA_TYPE_10M_HALF: */
			phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		पूर्ण
	पूर्ण

	ret_val = atl1_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
	अगर (ret_val) अणु
		u32 val;
		पूर्णांक i;
		/* pcie serdes link may be करोwn! */
		अगर (netअगर_msg_hw(adapter))
			dev_dbg(&pdev->dev, "pcie phy link down\n");

		क्रम (i = 0; i < 25; i++) अणु
			msleep(1);
			val = ioपढ़ो32(hw->hw_addr + REG_MDIO_CTRL);
			अगर (!(val & (MDIO_START | MDIO_BUSY)))
				अवरोध;
		पूर्ण

		अगर ((val & (MDIO_START | MDIO_BUSY)) != 0) अणु
			अगर (netअगर_msg_hw(adapter))
				dev_warn(&pdev->dev,
					"pcie link down at least 25ms\n");
			वापस ret_val;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Configures PHY स्वतःneg and flow control advertisement settings
 * hw - Struct containing variables accessed by shared code
 */
अटल s32 atl1_phy_setup_स्वतःneg_adv(काष्ठा atl1_hw *hw)
अणु
	s32 ret_val;
	s16 mii_स्वतःneg_adv_reg;
	s16 mii_1000t_ctrl_reg;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	mii_स्वतःneg_adv_reg = MII_AR_DEFAULT_CAP_MASK;

	/* Read the MII 1000Base-T Control Register (Address 9). */
	mii_1000t_ctrl_reg = MII_ATLX_CR_1000T_DEFAULT_CAP_MASK;

	/*
	 * First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_स्वतःneg_adv_reg &= ~MII_AR_SPEED_MASK;
	mii_1000t_ctrl_reg &= ~MII_ATLX_CR_1000T_SPEED_MASK;

	/*
	 * Need to parse media_type  and set up
	 * the appropriate PHY रेजिस्टरs.
	 */
	चयन (hw->media_type) अणु
	हाल MEDIA_TYPE_AUTO_SENSOR:
		mii_स्वतःneg_adv_reg |= (MII_AR_10T_HD_CAPS |
					MII_AR_10T_FD_CAPS |
					MII_AR_100TX_HD_CAPS |
					MII_AR_100TX_FD_CAPS);
		mii_1000t_ctrl_reg |= MII_ATLX_CR_1000T_FD_CAPS;
		अवरोध;

	हाल MEDIA_TYPE_1000M_FULL:
		mii_1000t_ctrl_reg |= MII_ATLX_CR_1000T_FD_CAPS;
		अवरोध;

	हाल MEDIA_TYPE_100M_FULL:
		mii_स्वतःneg_adv_reg |= MII_AR_100TX_FD_CAPS;
		अवरोध;

	हाल MEDIA_TYPE_100M_HALF:
		mii_स्वतःneg_adv_reg |= MII_AR_100TX_HD_CAPS;
		अवरोध;

	हाल MEDIA_TYPE_10M_FULL:
		mii_स्वतःneg_adv_reg |= MII_AR_10T_FD_CAPS;
		अवरोध;

	शेष:
		mii_स्वतःneg_adv_reg |= MII_AR_10T_HD_CAPS;
		अवरोध;
	पूर्ण

	/* flow control fixed to enable all */
	mii_स्वतःneg_adv_reg |= (MII_AR_ASM_सूची | MII_AR_PAUSE);

	hw->mii_स्वतःneg_adv_reg = mii_स्वतःneg_adv_reg;
	hw->mii_1000t_ctrl_reg = mii_1000t_ctrl_reg;

	ret_val = atl1_ग_लिखो_phy_reg(hw, MII_ADVERTISE, mii_स्वतःneg_adv_reg);
	अगर (ret_val)
		वापस ret_val;

	ret_val = atl1_ग_लिखो_phy_reg(hw, MII_ATLX_CR, mii_1000t_ctrl_reg);
	अगर (ret_val)
		वापस ret_val;

	वापस 0;
पूर्ण

/*
 * Configures link settings.
 * hw - Struct containing variables accessed by shared code
 * Assumes the hardware has previously been reset and the
 * transmitter and receiver are not enabled.
 */
अटल s32 atl1_setup_link(काष्ठा atl1_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->back->pdev;
	काष्ठा atl1_adapter *adapter = hw->back;
	s32 ret_val;

	/*
	 * Options:
	 *  PHY will advertise value(s) parsed from
	 *  स्वतःneg_advertised and fc
	 *  no matter what स्वतःneg is , We will not रुको link result.
	 */
	ret_val = atl1_phy_setup_स्वतःneg_adv(hw);
	अगर (ret_val) अणु
		अगर (netअगर_msg_link(adapter))
			dev_dbg(&pdev->dev,
				"error setting up autonegotiation\n");
		वापस ret_val;
	पूर्ण
	/* SW.Reset , En-Auto-Neg अगर needed */
	ret_val = atl1_phy_reset(hw);
	अगर (ret_val) अणु
		अगर (netअगर_msg_link(adapter))
			dev_dbg(&pdev->dev, "error resetting phy\n");
		वापस ret_val;
	पूर्ण
	hw->phy_configured = true;
	वापस ret_val;
पूर्ण

अटल व्योम atl1_init_flash_opcode(काष्ठा atl1_hw *hw)
अणु
	अगर (hw->flash_venकरोr >= ARRAY_SIZE(flash_table))
		/* Aपंचांगel */
		hw->flash_venकरोr = 0;

	/* Init OP table */
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_program,
		hw->hw_addr + REG_SPI_FLASH_OP_PROGRAM);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_sector_erase,
		hw->hw_addr + REG_SPI_FLASH_OP_SC_ERASE);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_chip_erase,
		hw->hw_addr + REG_SPI_FLASH_OP_CHIP_ERASE);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_rdid,
		hw->hw_addr + REG_SPI_FLASH_OP_RDID);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_wren,
		hw->hw_addr + REG_SPI_FLASH_OP_WREN);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_rdsr,
		hw->hw_addr + REG_SPI_FLASH_OP_RDSR);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_wrsr,
		hw->hw_addr + REG_SPI_FLASH_OP_WRSR);
	ioग_लिखो8(flash_table[hw->flash_venकरोr].cmd_पढ़ो,
		hw->hw_addr + REG_SPI_FLASH_OP_READ);
पूर्ण

/*
 * Perक्रमms basic configuration of the adapter.
 * hw - Struct containing variables accessed by shared code
 * Assumes that the controller has previously been reset and is in a
 * post-reset uninitialized state. Initializes multicast table,
 * and  Calls routines to setup link
 * Leaves the transmit and receive units disabled and uninitialized.
 */
अटल s32 atl1_init_hw(काष्ठा atl1_hw *hw)
अणु
	u32 ret_val = 0;

	/* Zero out the Multicast HASH table */
	ioग_लिखो32(0, hw->hw_addr + REG_RX_HASH_TABLE);
	/* clear the old settings from the multicast hash table */
	ioग_लिखो32(0, (hw->hw_addr + REG_RX_HASH_TABLE) + (1 << 2));

	atl1_init_flash_opcode(hw);

	अगर (!hw->phy_configured) अणु
		/* enable GPHY LinkChange Interrupt */
		ret_val = atl1_ग_लिखो_phy_reg(hw, 18, 0xC00);
		अगर (ret_val)
			वापस ret_val;
		/* make PHY out of घातer-saving state */
		ret_val = atl1_phy_leave_घातer_saving(hw);
		अगर (ret_val)
			वापस ret_val;
		/* Call a subroutine to configure the link */
		ret_val = atl1_setup_link(hw);
	पूर्ण
	वापस ret_val;
पूर्ण

/*
 * Detects the current speed and duplex settings of the hardware.
 * hw - Struct containing variables accessed by shared code
 * speed - Speed of the connection
 * duplex - Duplex setting of the connection
 */
अटल s32 atl1_get_speed_and_duplex(काष्ठा atl1_hw *hw, u16 *speed, u16 *duplex)
अणु
	काष्ठा pci_dev *pdev = hw->back->pdev;
	काष्ठा atl1_adapter *adapter = hw->back;
	s32 ret_val;
	u16 phy_data;

	/* ; --- Read   PHY Specअगरic Status Register (17) */
	ret_val = atl1_पढ़ो_phy_reg(hw, MII_ATLX_PSSR, &phy_data);
	अगर (ret_val)
		वापस ret_val;

	अगर (!(phy_data & MII_ATLX_PSSR_SPD_DPLX_RESOLVED))
		वापस ATLX_ERR_PHY_RES;

	चयन (phy_data & MII_ATLX_PSSR_SPEED) अणु
	हाल MII_ATLX_PSSR_1000MBS:
		*speed = SPEED_1000;
		अवरोध;
	हाल MII_ATLX_PSSR_100MBS:
		*speed = SPEED_100;
		अवरोध;
	हाल MII_ATLX_PSSR_10MBS:
		*speed = SPEED_10;
		अवरोध;
	शेष:
		अगर (netअगर_msg_hw(adapter))
			dev_dbg(&pdev->dev, "error getting speed\n");
		वापस ATLX_ERR_PHY_SPEED;
	पूर्ण
	अगर (phy_data & MII_ATLX_PSSR_DPLX)
		*duplex = FULL_DUPLEX;
	अन्यथा
		*duplex = HALF_DUPLEX;

	वापस 0;
पूर्ण

अटल व्योम atl1_set_mac_addr(काष्ठा atl1_hw *hw)
अणु
	u32 value;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC   1: 000B
	 * low dword
	 */
	value = (((u32) hw->mac_addr[2]) << 24) |
	    (((u32) hw->mac_addr[3]) << 16) |
	    (((u32) hw->mac_addr[4]) << 8) | (((u32) hw->mac_addr[5]));
	ioग_लिखो32(value, hw->hw_addr + REG_MAC_STA_ADDR);
	/* high dword */
	value = (((u32) hw->mac_addr[0]) << 8) | (((u32) hw->mac_addr[1]));
	ioग_लिखो32(value, (hw->hw_addr + REG_MAC_STA_ADDR) + (1 << 2));
पूर्ण

/**
 * atl1_sw_init - Initialize general software काष्ठाures (काष्ठा atl1_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * atl1_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 */
अटल पूर्णांक atl1_sw_init(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;

	hw->max_frame_size = netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	hw->min_frame_size = ETH_ZLEN + ETH_FCS_LEN;

	adapter->wol = 0;
	device_set_wakeup_enable(&adapter->pdev->dev, false);
	adapter->rx_buffer_len = (hw->max_frame_size + 7) & ~7;
	adapter->ict = 50000;		/* 100ms */
	adapter->link_speed = SPEED_0;	/* hardware init */
	adapter->link_duplex = FULL_DUPLEX;

	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->ipgt = 0x60;
	hw->min_अगरg = 0x50;
	hw->ipgr1 = 0x40;
	hw->ipgr2 = 0x60;
	hw->max_retry = 0xf;
	hw->lcol = 0x37;
	hw->jam_ipg = 7;
	hw->rfd_burst = 8;
	hw->rrd_burst = 8;
	hw->rfd_fetch_gap = 1;
	hw->rx_jumbo_th = adapter->rx_buffer_len / 8;
	hw->rx_jumbo_lkah = 1;
	hw->rrd_ret_समयr = 16;
	hw->tpd_burst = 4;
	hw->tpd_fetch_th = 16;
	hw->txf_burst = 0x100;
	hw->tx_jumbo_task_th = (hw->max_frame_size + 7) >> 3;
	hw->tpd_fetch_gap = 1;
	hw->rcb_value = atl1_rcb_64;
	hw->dma_ord = atl1_dma_ord_enh;
	hw->dmar_block = atl1_dma_req_256;
	hw->dmaw_block = atl1_dma_req_256;
	hw->cmb_rrd = 4;
	hw->cmb_tpd = 4;
	hw->cmb_rx_समयr = 1;	/* about 2us */
	hw->cmb_tx_समयr = 1;	/* about 2us */
	hw->smb_समयr = 100000;	/* about 200ms */

	spin_lock_init(&adapter->lock);
	spin_lock_init(&adapter->mb_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	u16 result;

	atl1_पढ़ो_phy_reg(&adapter->hw, reg_num & 0x1f, &result);

	वापस result;
पूर्ण

अटल व्योम mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक reg_num,
	पूर्णांक val)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

	atl1_ग_लिखो_phy_reg(&adapter->hw, reg_num, val);
पूर्ण

अटल पूर्णांक atl1_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	spin_lock_irqsave(&adapter->lock, flags);
	retval = generic_mii_ioctl(&adapter->mii, अगर_mii(अगरr), cmd, शून्य);
	spin_unlock_irqrestore(&adapter->lock, flags);

	वापस retval;
पूर्ण

/**
 * atl1_setup_mem_resources - allocate Tx / RX descriptor resources
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल s32 atl1_setup_ring_resources(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1_ring_header *ring_header = &adapter->ring_header;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;
	u8 offset = 0;

	size = माप(काष्ठा atl1_buffer) * (tpd_ring->count + rfd_ring->count);
	tpd_ring->buffer_info = kzalloc(size, GFP_KERNEL);
	अगर (unlikely(!tpd_ring->buffer_info)) अणु
		अगर (netअगर_msg_drv(adapter))
			dev_err(&pdev->dev, "kzalloc failed , size = D%d\n",
				size);
		जाओ err_nomem;
	पूर्ण
	rfd_ring->buffer_info =
		(tpd_ring->buffer_info + tpd_ring->count);

	/*
	 * real ring DMA buffer
	 * each ring/block may need up to 8 bytes क्रम alignment, hence the
	 * additional 40 bytes tacked onto the end.
	 */
	ring_header->size =
		माप(काष्ठा tx_packet_desc) * tpd_ring->count
		+ माप(काष्ठा rx_मुक्त_desc) * rfd_ring->count
		+ माप(काष्ठा rx_वापस_desc) * rrd_ring->count
		+ माप(काष्ठा coals_msg_block)
		+ माप(काष्ठा stats_msg_block)
		+ 40;

	ring_header->desc = dma_alloc_coherent(&pdev->dev, ring_header->size,
					       &ring_header->dma, GFP_KERNEL);
	अगर (unlikely(!ring_header->desc)) अणु
		अगर (netअगर_msg_drv(adapter))
			dev_err(&pdev->dev, "dma_alloc_coherent failed\n");
		जाओ err_nomem;
	पूर्ण

	/* init TPD ring */
	tpd_ring->dma = ring_header->dma;
	offset = (tpd_ring->dma & 0x7) ? (8 - (ring_header->dma & 0x7)) : 0;
	tpd_ring->dma += offset;
	tpd_ring->desc = (u8 *) ring_header->desc + offset;
	tpd_ring->size = माप(काष्ठा tx_packet_desc) * tpd_ring->count;

	/* init RFD ring */
	rfd_ring->dma = tpd_ring->dma + tpd_ring->size;
	offset = (rfd_ring->dma & 0x7) ? (8 - (rfd_ring->dma & 0x7)) : 0;
	rfd_ring->dma += offset;
	rfd_ring->desc = (u8 *) tpd_ring->desc + (tpd_ring->size + offset);
	rfd_ring->size = माप(काष्ठा rx_मुक्त_desc) * rfd_ring->count;


	/* init RRD ring */
	rrd_ring->dma = rfd_ring->dma + rfd_ring->size;
	offset = (rrd_ring->dma & 0x7) ? (8 - (rrd_ring->dma & 0x7)) : 0;
	rrd_ring->dma += offset;
	rrd_ring->desc = (u8 *) rfd_ring->desc + (rfd_ring->size + offset);
	rrd_ring->size = माप(काष्ठा rx_वापस_desc) * rrd_ring->count;


	/* init CMB */
	adapter->cmb.dma = rrd_ring->dma + rrd_ring->size;
	offset = (adapter->cmb.dma & 0x7) ? (8 - (adapter->cmb.dma & 0x7)) : 0;
	adapter->cmb.dma += offset;
	adapter->cmb.cmb = (काष्ठा coals_msg_block *)
		((u8 *) rrd_ring->desc + (rrd_ring->size + offset));

	/* init SMB */
	adapter->smb.dma = adapter->cmb.dma + माप(काष्ठा coals_msg_block);
	offset = (adapter->smb.dma & 0x7) ? (8 - (adapter->smb.dma & 0x7)) : 0;
	adapter->smb.dma += offset;
	adapter->smb.smb = (काष्ठा stats_msg_block *)
		((u8 *) adapter->cmb.cmb +
		(माप(काष्ठा coals_msg_block) + offset));

	वापस 0;

err_nomem:
	kमुक्त(tpd_ring->buffer_info);
	वापस -ENOMEM;
पूर्ण

अटल व्योम atl1_init_ring_ptrs(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;

	atomic_set(&tpd_ring->next_to_use, 0);
	atomic_set(&tpd_ring->next_to_clean, 0);

	rfd_ring->next_to_clean = 0;
	atomic_set(&rfd_ring->next_to_use, 0);

	rrd_ring->next_to_use = 0;
	atomic_set(&rrd_ring->next_to_clean, 0);
पूर्ण

/**
 * atl1_clean_rx_ring - Free RFD Buffers
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atl1_clean_rx_ring(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rfd_ring->count; i++) अणु
		buffer_info = &rfd_ring->buffer_info[i];
		अगर (buffer_info->dma) अणु
			dma_unmap_page(&pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_FROM_DEVICE);
			buffer_info->dma = 0;
		पूर्ण
		अगर (buffer_info->skb) अणु
			dev_kमुक्त_skb(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा atl1_buffer) * rfd_ring->count;
	स_रखो(rfd_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(rfd_ring->desc, 0, rfd_ring->size);

	rfd_ring->next_to_clean = 0;
	atomic_set(&rfd_ring->next_to_use, 0);

	rrd_ring->next_to_use = 0;
	atomic_set(&rrd_ring->next_to_clean, 0);
पूर्ण

/**
 * atl1_clean_tx_ring - Free Tx Buffers
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम atl1_clean_tx_ring(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tpd_ring->count; i++) अणु
		buffer_info = &tpd_ring->buffer_info[i];
		अगर (buffer_info->dma) अणु
			dma_unmap_page(&pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
			buffer_info->dma = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < tpd_ring->count; i++) अणु
		buffer_info = &tpd_ring->buffer_info[i];
		अगर (buffer_info->skb) अणु
			dev_kमुक्त_skb_any(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा atl1_buffer) * tpd_ring->count;
	स_रखो(tpd_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(tpd_ring->desc, 0, tpd_ring->size);

	atomic_set(&tpd_ring->next_to_use, 0);
	atomic_set(&tpd_ring->next_to_clean, 0);
पूर्ण

/**
 * atl1_मुक्त_ring_resources - Free Tx / RX descriptor Resources
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम atl1_मुक्त_ring_resources(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1_ring_header *ring_header = &adapter->ring_header;

	atl1_clean_tx_ring(adapter);
	atl1_clean_rx_ring(adapter);

	kमुक्त(tpd_ring->buffer_info);
	dma_मुक्त_coherent(&pdev->dev, ring_header->size, ring_header->desc,
			  ring_header->dma);

	tpd_ring->buffer_info = शून्य;
	tpd_ring->desc = शून्य;
	tpd_ring->dma = 0;

	rfd_ring->buffer_info = शून्य;
	rfd_ring->desc = शून्य;
	rfd_ring->dma = 0;

	rrd_ring->desc = शून्य;
	rrd_ring->dma = 0;

	adapter->cmb.dma = 0;
	adapter->cmb.cmb = शून्य;

	adapter->smb.dma = 0;
	adapter->smb.smb = शून्य;
पूर्ण

अटल व्योम atl1_setup_mac_ctrl(काष्ठा atl1_adapter *adapter)
अणु
	u32 value;
	काष्ठा atl1_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	/* Config MAC CTRL Register */
	value = MAC_CTRL_TX_EN | MAC_CTRL_RX_EN;
	/* duplex */
	अगर (FULL_DUPLEX == adapter->link_duplex)
		value |= MAC_CTRL_DUPLX;
	/* speed */
	value |= ((u32) ((SPEED_1000 == adapter->link_speed) ?
			 MAC_CTRL_SPEED_1000 : MAC_CTRL_SPEED_10_100) <<
		  MAC_CTRL_SPEED_SHIFT);
	/* flow control */
	value |= (MAC_CTRL_TX_FLOW | MAC_CTRL_RX_FLOW);
	/* PAD & CRC */
	value |= (MAC_CTRL_ADD_CRC | MAC_CTRL_PAD);
	/* preamble length */
	value |= (((u32) adapter->hw.preamble_len
		   & MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);
	/* vlan */
	__atlx_vlan_mode(netdev->features, &value);
	/* rx checksum
	   अगर (adapter->rx_csum)
	   value |= MAC_CTRL_RX_CHKSUM_EN;
	 */
	/* filter mode */
	value |= MAC_CTRL_BC_EN;
	अगर (netdev->flags & IFF_PROMISC)
		value |= MAC_CTRL_PROMIS_EN;
	अन्यथा अगर (netdev->flags & IFF_ALLMULTI)
		value |= MAC_CTRL_MC_ALL_EN;
	/* value |= MAC_CTRL_LOOPBACK; */
	ioग_लिखो32(value, hw->hw_addr + REG_MAC_CTRL);
पूर्ण

अटल u32 atl1_check_link(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 ret_val;
	u16 speed, duplex, phy_data;
	पूर्णांक reconfig = 0;

	/* MII_BMSR must पढ़ो twice */
	atl1_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	atl1_पढ़ो_phy_reg(hw, MII_BMSR, &phy_data);
	अगर (!(phy_data & BMSR_LSTATUS)) अणु
		/* link करोwn */
		अगर (netअगर_carrier_ok(netdev)) अणु
			/* old link state: Up */
			अगर (netअगर_msg_link(adapter))
				dev_info(&adapter->pdev->dev, "link is down\n");
			adapter->link_speed = SPEED_0;
			netअगर_carrier_off(netdev);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Link Up */
	ret_val = atl1_get_speed_and_duplex(hw, &speed, &duplex);
	अगर (ret_val)
		वापस ret_val;

	चयन (hw->media_type) अणु
	हाल MEDIA_TYPE_1000M_FULL:
		अगर (speed != SPEED_1000 || duplex != FULL_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_100M_FULL:
		अगर (speed != SPEED_100 || duplex != FULL_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_100M_HALF:
		अगर (speed != SPEED_100 || duplex != HALF_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_10M_FULL:
		अगर (speed != SPEED_10 || duplex != FULL_DUPLEX)
			reconfig = 1;
		अवरोध;
	हाल MEDIA_TYPE_10M_HALF:
		अगर (speed != SPEED_10 || duplex != HALF_DUPLEX)
			reconfig = 1;
		अवरोध;
	पूर्ण

	/* link result is our setting */
	अगर (!reconfig) अणु
		अगर (adapter->link_speed != speed ||
		    adapter->link_duplex != duplex) अणु
			adapter->link_speed = speed;
			adapter->link_duplex = duplex;
			atl1_setup_mac_ctrl(adapter);
			अगर (netअगर_msg_link(adapter))
				dev_info(&adapter->pdev->dev,
					"%s link is up %d Mbps %s\n",
					netdev->name, adapter->link_speed,
					adapter->link_duplex == FULL_DUPLEX ?
					"full duplex" : "half duplex");
		पूर्ण
		अगर (!netअगर_carrier_ok(netdev)) अणु
			/* Link करोwn -> Up */
			netअगर_carrier_on(netdev);
		पूर्ण
		वापस 0;
	पूर्ण

	/* change original link status */
	अगर (netअगर_carrier_ok(netdev)) अणु
		adapter->link_speed = SPEED_0;
		netअगर_carrier_off(netdev);
		netअगर_stop_queue(netdev);
	पूर्ण

	अगर (hw->media_type != MEDIA_TYPE_AUTO_SENSOR &&
	    hw->media_type != MEDIA_TYPE_1000M_FULL) अणु
		चयन (hw->media_type) अणु
		हाल MEDIA_TYPE_100M_FULL:
			phy_data = MII_CR_FULL_DUPLEX | MII_CR_SPEED_100 |
			           MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_100M_HALF:
			phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_10M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		शेष:
			/* MEDIA_TYPE_10M_HALF: */
			phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		पूर्ण
		atl1_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
		वापस 0;
	पूर्ण

	/* स्वतः-neg, insert समयr to re-config phy */
	अगर (!adapter->phy_समयr_pending) अणु
		adapter->phy_समयr_pending = true;
		mod_समयr(&adapter->phy_config_समयr,
			  round_jअगरfies(jअगरfies + 3 * HZ));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_flow_ctrl_old(काष्ठा atl1_adapter *adapter)
अणु
	u32 hi, lo, value;

	/* RFD Flow Control */
	value = adapter->rfd_ring.count;
	hi = value / 16;
	अगर (hi < 2)
		hi = 2;
	lo = value * 7 / 8;

	value = ((hi & RXQ_RXF_PAUSE_TH_HI_MASK) << RXQ_RXF_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RXF_PAUSE_TH_LO_MASK) << RXQ_RXF_PAUSE_TH_LO_SHIFT);
	ioग_लिखो32(value, adapter->hw.hw_addr + REG_RXQ_RXF_PAUSE_THRESH);

	/* RRD Flow Control */
	value = adapter->rrd_ring.count;
	lo = value / 16;
	hi = value * 7 / 8;
	अगर (lo < 2)
		lo = 2;
	value = ((hi & RXQ_RRD_PAUSE_TH_HI_MASK) << RXQ_RRD_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RRD_PAUSE_TH_LO_MASK) << RXQ_RRD_PAUSE_TH_LO_SHIFT);
	ioग_लिखो32(value, adapter->hw.hw_addr + REG_RXQ_RRD_PAUSE_THRESH);
पूर्ण

अटल व्योम set_flow_ctrl_new(काष्ठा atl1_hw *hw)
अणु
	u32 hi, lo, value;

	/* RXF Flow Control */
	value = ioपढ़ो32(hw->hw_addr + REG_SRAM_RXF_LEN);
	lo = value / 16;
	अगर (lo < 192)
		lo = 192;
	hi = value * 7 / 8;
	अगर (hi < lo)
		hi = lo + 16;
	value = ((hi & RXQ_RXF_PAUSE_TH_HI_MASK) << RXQ_RXF_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RXF_PAUSE_TH_LO_MASK) << RXQ_RXF_PAUSE_TH_LO_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_RXQ_RXF_PAUSE_THRESH);

	/* RRD Flow Control */
	value = ioपढ़ो32(hw->hw_addr + REG_SRAM_RRD_LEN);
	lo = value / 8;
	hi = value * 7 / 8;
	अगर (lo < 2)
		lo = 2;
	अगर (hi < lo)
		hi = lo + 3;
	value = ((hi & RXQ_RRD_PAUSE_TH_HI_MASK) << RXQ_RRD_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RRD_PAUSE_TH_LO_MASK) << RXQ_RRD_PAUSE_TH_LO_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_RXQ_RRD_PAUSE_THRESH);
पूर्ण

/**
 * atl1_configure - Configure Transmit&Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx /Rx unit of the MAC after a reset.
 */
अटल u32 atl1_configure(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_hw *hw = &adapter->hw;
	u32 value;

	/* clear पूर्णांकerrupt status */
	ioग_लिखो32(0xffffffff, adapter->hw.hw_addr + REG_ISR);

	/* set MAC Address */
	value = (((u32) hw->mac_addr[2]) << 24) |
		(((u32) hw->mac_addr[3]) << 16) |
		(((u32) hw->mac_addr[4]) << 8) |
		(((u32) hw->mac_addr[5]));
	ioग_लिखो32(value, hw->hw_addr + REG_MAC_STA_ADDR);
	value = (((u32) hw->mac_addr[0]) << 8) | (((u32) hw->mac_addr[1]));
	ioग_लिखो32(value, hw->hw_addr + (REG_MAC_STA_ADDR + 4));

	/* tx / rx ring */

	/* HI base address */
	ioग_लिखो32((u32) ((adapter->tpd_ring.dma & 0xffffffff00000000ULL) >> 32),
		hw->hw_addr + REG_DESC_BASE_ADDR_HI);
	/* LO base address */
	ioग_लिखो32((u32) (adapter->rfd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_RFD_ADDR_LO);
	ioग_लिखो32((u32) (adapter->rrd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_RRD_ADDR_LO);
	ioग_लिखो32((u32) (adapter->tpd_ring.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_TPD_ADDR_LO);
	ioग_लिखो32((u32) (adapter->cmb.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_CMB_ADDR_LO);
	ioग_लिखो32((u32) (adapter->smb.dma & 0x00000000ffffffffULL),
		hw->hw_addr + REG_DESC_SMB_ADDR_LO);

	/* element count */
	value = adapter->rrd_ring.count;
	value <<= 16;
	value += adapter->rfd_ring.count;
	ioग_लिखो32(value, hw->hw_addr + REG_DESC_RFD_RRD_RING_SIZE);
	ioग_लिखो32(adapter->tpd_ring.count, hw->hw_addr +
		REG_DESC_TPD_RING_SIZE);

	/* Load Ptr */
	ioग_लिखो32(1, hw->hw_addr + REG_LOAD_PTR);

	/* config Mailbox */
	value = ((atomic_पढ़ो(&adapter->tpd_ring.next_to_use)
		  & MB_TPD_PROD_INDX_MASK) << MB_TPD_PROD_INDX_SHIFT) |
		((atomic_पढ़ो(&adapter->rrd_ring.next_to_clean)
		& MB_RRD_CONS_INDX_MASK) << MB_RRD_CONS_INDX_SHIFT) |
		((atomic_पढ़ो(&adapter->rfd_ring.next_to_use)
		& MB_RFD_PROD_INDX_MASK) << MB_RFD_PROD_INDX_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_MAILBOX);

	/* config IPG/IFG */
	value = (((u32) hw->ipgt & MAC_IPG_IFG_IPGT_MASK)
		 << MAC_IPG_IFG_IPGT_SHIFT) |
		(((u32) hw->min_अगरg & MAC_IPG_IFG_MIFG_MASK)
		<< MAC_IPG_IFG_MIFG_SHIFT) |
		(((u32) hw->ipgr1 & MAC_IPG_IFG_IPGR1_MASK)
		<< MAC_IPG_IFG_IPGR1_SHIFT) |
		(((u32) hw->ipgr2 & MAC_IPG_IFG_IPGR2_MASK)
		<< MAC_IPG_IFG_IPGR2_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_MAC_IPG_IFG);

	/* config  Half-Duplex Control */
	value = ((u32) hw->lcol & MAC_HALF_DUPLX_CTRL_LCOL_MASK) |
		(((u32) hw->max_retry & MAC_HALF_DUPLX_CTRL_RETRY_MASK)
		<< MAC_HALF_DUPLX_CTRL_RETRY_SHIFT) |
		MAC_HALF_DUPLX_CTRL_EXC_DEF_EN |
		(0xa << MAC_HALF_DUPLX_CTRL_ABEBT_SHIFT) |
		(((u32) hw->jam_ipg & MAC_HALF_DUPLX_CTRL_JAMIPG_MASK)
		<< MAC_HALF_DUPLX_CTRL_JAMIPG_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_MAC_HALF_DUPLX_CTRL);

	/* set Interrupt Moderator Timer */
	ioग_लिखो16(adapter->imt, hw->hw_addr + REG_IRQ_MODU_TIMER_INIT);
	ioग_लिखो32(MASTER_CTRL_ITIMER_EN, hw->hw_addr + REG_MASTER_CTRL);

	/* set Interrupt Clear Timer */
	ioग_लिखो16(adapter->ict, hw->hw_addr + REG_CMBDISDMA_TIMER);

	/* set max frame size hw will accept */
	ioग_लिखो32(hw->max_frame_size, hw->hw_addr + REG_MTU);

	/* jumbo size & rrd retirement समयr */
	value = (((u32) hw->rx_jumbo_th & RXQ_JMBOSZ_TH_MASK)
		 << RXQ_JMBOSZ_TH_SHIFT) |
		(((u32) hw->rx_jumbo_lkah & RXQ_JMBO_LKAH_MASK)
		<< RXQ_JMBO_LKAH_SHIFT) |
		(((u32) hw->rrd_ret_समयr & RXQ_RRD_TIMER_MASK)
		<< RXQ_RRD_TIMER_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_RXQ_JMBOSZ_RRDTIM);

	/* Flow Control */
	चयन (hw->dev_rev) अणु
	हाल 0x8001:
	हाल 0x9001:
	हाल 0x9002:
	हाल 0x9003:
		set_flow_ctrl_old(adapter);
		अवरोध;
	शेष:
		set_flow_ctrl_new(hw);
		अवरोध;
	पूर्ण

	/* config TXQ */
	value = (((u32) hw->tpd_burst & TXQ_CTRL_TPD_BURST_NUM_MASK)
		 << TXQ_CTRL_TPD_BURST_NUM_SHIFT) |
		(((u32) hw->txf_burst & TXQ_CTRL_TXF_BURST_NUM_MASK)
		<< TXQ_CTRL_TXF_BURST_NUM_SHIFT) |
		(((u32) hw->tpd_fetch_th & TXQ_CTRL_TPD_FETCH_TH_MASK)
		<< TXQ_CTRL_TPD_FETCH_TH_SHIFT) | TXQ_CTRL_ENH_MODE |
		TXQ_CTRL_EN;
	ioग_लिखो32(value, hw->hw_addr + REG_TXQ_CTRL);

	/* min tpd fetch gap & tx jumbo packet size threshold क्रम taskoffload */
	value = (((u32) hw->tx_jumbo_task_th & TX_JUMBO_TASK_TH_MASK)
		<< TX_JUMBO_TASK_TH_SHIFT) |
		(((u32) hw->tpd_fetch_gap & TX_TPD_MIN_IPG_MASK)
		<< TX_TPD_MIN_IPG_SHIFT);
	ioग_लिखो32(value, hw->hw_addr + REG_TX_JUMBO_TASK_TH_TPD_IPG);

	/* config RXQ */
	value = (((u32) hw->rfd_burst & RXQ_CTRL_RFD_BURST_NUM_MASK)
		<< RXQ_CTRL_RFD_BURST_NUM_SHIFT) |
		(((u32) hw->rrd_burst & RXQ_CTRL_RRD_BURST_THRESH_MASK)
		<< RXQ_CTRL_RRD_BURST_THRESH_SHIFT) |
		(((u32) hw->rfd_fetch_gap & RXQ_CTRL_RFD_PREF_MIN_IPG_MASK)
		<< RXQ_CTRL_RFD_PREF_MIN_IPG_SHIFT) | RXQ_CTRL_CUT_THRU_EN |
		RXQ_CTRL_EN;
	ioग_लिखो32(value, hw->hw_addr + REG_RXQ_CTRL);

	/* config DMA Engine */
	value = ((((u32) hw->dmar_block) & DMA_CTRL_DMAR_BURST_LEN_MASK)
		<< DMA_CTRL_DMAR_BURST_LEN_SHIFT) |
		((((u32) hw->dmaw_block) & DMA_CTRL_DMAW_BURST_LEN_MASK)
		<< DMA_CTRL_DMAW_BURST_LEN_SHIFT) | DMA_CTRL_DMAR_EN |
		DMA_CTRL_DMAW_EN;
	value |= (u32) hw->dma_ord;
	अगर (atl1_rcb_128 == hw->rcb_value)
		value |= DMA_CTRL_RCB_VALUE;
	ioग_लिखो32(value, hw->hw_addr + REG_DMA_CTRL);

	/* config CMB / SMB */
	value = (hw->cmb_tpd > adapter->tpd_ring.count) ?
		hw->cmb_tpd : adapter->tpd_ring.count;
	value <<= 16;
	value |= hw->cmb_rrd;
	ioग_लिखो32(value, hw->hw_addr + REG_CMB_WRITE_TH);
	value = hw->cmb_rx_समयr | ((u32) hw->cmb_tx_समयr << 16);
	ioग_लिखो32(value, hw->hw_addr + REG_CMB_WRITE_TIMER);
	ioग_लिखो32(hw->smb_समयr, hw->hw_addr + REG_SMB_TIMER);

	/* --- enable CMB / SMB */
	value = CSMB_CTRL_CMB_EN | CSMB_CTRL_SMB_EN;
	ioग_लिखो32(value, hw->hw_addr + REG_CSMB_CTRL);

	value = ioपढ़ो32(adapter->hw.hw_addr + REG_ISR);
	अगर (unlikely((value & ISR_PHY_LINKDOWN) != 0))
		value = 1;	/* config failed */
	अन्यथा
		value = 0;

	/* clear all पूर्णांकerrupt status */
	ioग_लिखो32(0x3fffffff, adapter->hw.hw_addr + REG_ISR);
	ioग_लिखो32(0, adapter->hw.hw_addr + REG_ISR);
	वापस value;
पूर्ण

/*
 * atl1_pcie_patch - Patch क्रम PCIE module
 */
अटल व्योम atl1_pcie_patch(काष्ठा atl1_adapter *adapter)
अणु
	u32 value;

	/* much venकरोr magic here */
	value = 0x6500;
	ioग_लिखो32(value, adapter->hw.hw_addr + 0x12FC);
	/* pcie flow control mode change */
	value = ioपढ़ो32(adapter->hw.hw_addr + 0x1008);
	value |= 0x8000;
	ioग_लिखो32(value, adapter->hw.hw_addr + 0x1008);
पूर्ण

/*
 * When ACPI resume on some VIA MotherBoard, the Interrupt Disable bit/0x400
 * on PCI Command रेजिस्टर is disable.
 * The function enable this bit.
 * Brackett, 2006/03/15
 */
अटल व्योम atl1_via_workaround(काष्ठा atl1_adapter *adapter)
अणु
	अचिन्हित दीर्घ value;

	value = ioपढ़ो16(adapter->hw.hw_addr + PCI_COMMAND);
	अगर (value & PCI_COMMAND_INTX_DISABLE)
		value &= ~PCI_COMMAND_INTX_DISABLE;
	ioग_लिखो32(value, adapter->hw.hw_addr + PCI_COMMAND);
पूर्ण

अटल व्योम atl1_inc_smb(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा stats_msg_block *smb = adapter->smb.smb;

	u64 new_rx_errors = smb->rx_frag +
			    smb->rx_fcs_err +
			    smb->rx_len_err +
			    smb->rx_sz_ov +
			    smb->rx_rxf_ov +
			    smb->rx_rrd_ov +
			    smb->rx_align_err;
	u64 new_tx_errors = smb->tx_late_col +
			    smb->tx_पात_col +
			    smb->tx_underrun +
			    smb->tx_trunc;

	/* Fill out the OS statistics काष्ठाure */
	adapter->soft_stats.rx_packets += smb->rx_ok + new_rx_errors;
	adapter->soft_stats.tx_packets += smb->tx_ok + new_tx_errors;
	adapter->soft_stats.rx_bytes += smb->rx_byte_cnt;
	adapter->soft_stats.tx_bytes += smb->tx_byte_cnt;
	adapter->soft_stats.multicast += smb->rx_mcast;
	adapter->soft_stats.collisions += smb->tx_1_col +
					  smb->tx_2_col +
					  smb->tx_late_col +
					  smb->tx_पात_col;

	/* Rx Errors */
	adapter->soft_stats.rx_errors += new_rx_errors;
	adapter->soft_stats.rx_fअगरo_errors += smb->rx_rxf_ov;
	adapter->soft_stats.rx_length_errors += smb->rx_len_err;
	adapter->soft_stats.rx_crc_errors += smb->rx_fcs_err;
	adapter->soft_stats.rx_frame_errors += smb->rx_align_err;

	adapter->soft_stats.rx_छोड़ो += smb->rx_छोड़ो;
	adapter->soft_stats.rx_rrd_ov += smb->rx_rrd_ov;
	adapter->soft_stats.rx_trunc += smb->rx_sz_ov;

	/* Tx Errors */
	adapter->soft_stats.tx_errors += new_tx_errors;
	adapter->soft_stats.tx_fअगरo_errors += smb->tx_underrun;
	adapter->soft_stats.tx_पातed_errors += smb->tx_पात_col;
	adapter->soft_stats.tx_winकरोw_errors += smb->tx_late_col;

	adapter->soft_stats.excecol += smb->tx_पात_col;
	adapter->soft_stats.deffer += smb->tx_defer;
	adapter->soft_stats.scc += smb->tx_1_col;
	adapter->soft_stats.mcc += smb->tx_2_col;
	adapter->soft_stats.latecol += smb->tx_late_col;
	adapter->soft_stats.tx_underrun += smb->tx_underrun;
	adapter->soft_stats.tx_trunc += smb->tx_trunc;
	adapter->soft_stats.tx_छोड़ो += smb->tx_छोड़ो;

	netdev->stats.rx_bytes = adapter->soft_stats.rx_bytes;
	netdev->stats.tx_bytes = adapter->soft_stats.tx_bytes;
	netdev->stats.multicast = adapter->soft_stats.multicast;
	netdev->stats.collisions = adapter->soft_stats.collisions;
	netdev->stats.rx_errors = adapter->soft_stats.rx_errors;
	netdev->stats.rx_length_errors =
		adapter->soft_stats.rx_length_errors;
	netdev->stats.rx_crc_errors = adapter->soft_stats.rx_crc_errors;
	netdev->stats.rx_frame_errors =
		adapter->soft_stats.rx_frame_errors;
	netdev->stats.rx_fअगरo_errors = adapter->soft_stats.rx_fअगरo_errors;
	netdev->stats.rx_dropped = adapter->soft_stats.rx_rrd_ov;
	netdev->stats.tx_errors = adapter->soft_stats.tx_errors;
	netdev->stats.tx_fअगरo_errors = adapter->soft_stats.tx_fअगरo_errors;
	netdev->stats.tx_पातed_errors =
		adapter->soft_stats.tx_पातed_errors;
	netdev->stats.tx_winकरोw_errors =
		adapter->soft_stats.tx_winकरोw_errors;
	netdev->stats.tx_carrier_errors =
		adapter->soft_stats.tx_carrier_errors;

	netdev->stats.rx_packets = adapter->soft_stats.rx_packets;
	netdev->stats.tx_packets = adapter->soft_stats.tx_packets;
पूर्ण

अटल व्योम atl1_update_mailbox(काष्ठा atl1_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;
	u32 tpd_next_to_use;
	u32 rfd_next_to_use;
	u32 rrd_next_to_clean;
	u32 value;

	spin_lock_irqsave(&adapter->mb_lock, flags);

	tpd_next_to_use = atomic_पढ़ो(&adapter->tpd_ring.next_to_use);
	rfd_next_to_use = atomic_पढ़ो(&adapter->rfd_ring.next_to_use);
	rrd_next_to_clean = atomic_पढ़ो(&adapter->rrd_ring.next_to_clean);

	value = ((rfd_next_to_use & MB_RFD_PROD_INDX_MASK) <<
		MB_RFD_PROD_INDX_SHIFT) |
		((rrd_next_to_clean & MB_RRD_CONS_INDX_MASK) <<
		MB_RRD_CONS_INDX_SHIFT) |
		((tpd_next_to_use & MB_TPD_PROD_INDX_MASK) <<
		MB_TPD_PROD_INDX_SHIFT);
	ioग_लिखो32(value, adapter->hw.hw_addr + REG_MAILBOX);

	spin_unlock_irqrestore(&adapter->mb_lock, flags);
पूर्ण

अटल व्योम atl1_clean_alloc_flag(काष्ठा atl1_adapter *adapter,
	काष्ठा rx_वापस_desc *rrd, u16 offset)
अणु
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;

	जबतक (rfd_ring->next_to_clean != (rrd->buf_indx + offset)) अणु
		rfd_ring->buffer_info[rfd_ring->next_to_clean].alloced = 0;
		अगर (++rfd_ring->next_to_clean == rfd_ring->count) अणु
			rfd_ring->next_to_clean = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम atl1_update_rfd_index(काष्ठा atl1_adapter *adapter,
	काष्ठा rx_वापस_desc *rrd)
अणु
	u16 num_buf;

	num_buf = (rrd->xsz.xsum_sz.pkt_size + adapter->rx_buffer_len - 1) /
		adapter->rx_buffer_len;
	अगर (rrd->num_buf == num_buf)
		/* clean alloc flag क्रम bad rrd */
		atl1_clean_alloc_flag(adapter, rrd, num_buf);
पूर्ण

अटल व्योम atl1_rx_checksum(काष्ठा atl1_adapter *adapter,
	काष्ठा rx_वापस_desc *rrd, काष्ठा sk_buff *skb)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	/*
	 * The L1 hardware contains a bug that erroneously sets the
	 * PACKET_FLAG_ERR and ERR_FLAG_L4_CHKSUM bits whenever a
	 * fragmented IP packet is received, even though the packet
	 * is perfectly valid and its checksum is correct. There's
	 * no way to distinguish between one of these good packets
	 * and a packet that actually contains a TCP/UDP checksum
	 * error, so all we can करो is allow it to be handed up to
	 * the higher layers and let it be sorted out there.
	 */

	skb_checksum_none_निश्चित(skb);

	अगर (unlikely(rrd->pkt_flg & PACKET_FLAG_ERR)) अणु
		अगर (rrd->err_flg & (ERR_FLAG_CRC | ERR_FLAG_TRUNC |
					ERR_FLAG_CODE | ERR_FLAG_OV)) अणु
			adapter->hw_csum_err++;
			अगर (netअगर_msg_rx_err(adapter))
				dev_prपूर्णांकk(KERN_DEBUG, &pdev->dev,
					"rx checksum error\n");
			वापस;
		पूर्ण
	पूर्ण

	/* not IPv4 */
	अगर (!(rrd->pkt_flg & PACKET_FLAG_IPV4))
		/* checksum is invalid, but it's not an IPv4 pkt, so ok */
		वापस;

	/* IPv4 packet */
	अगर (likely(!(rrd->err_flg &
		(ERR_FLAG_IP_CHKSUM | ERR_FLAG_L4_CHKSUM)))) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		adapter->hw_csum_good++;
		वापस;
	पूर्ण
पूर्ण

/**
 * atl1_alloc_rx_buffers - Replace used receive buffers
 * @adapter: address of board निजी काष्ठाure
 */
अटल u16 atl1_alloc_rx_buffers(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा page *page;
	अचिन्हित दीर्घ offset;
	काष्ठा atl1_buffer *buffer_info, *next_info;
	काष्ठा sk_buff *skb;
	u16 num_alloc = 0;
	u16 rfd_next_to_use, next_next;
	काष्ठा rx_मुक्त_desc *rfd_desc;

	next_next = rfd_next_to_use = atomic_पढ़ो(&rfd_ring->next_to_use);
	अगर (++next_next == rfd_ring->count)
		next_next = 0;
	buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
	next_info = &rfd_ring->buffer_info[next_next];

	जबतक (!buffer_info->alloced && !next_info->alloced) अणु
		अगर (buffer_info->skb) अणु
			buffer_info->alloced = 1;
			जाओ next;
		पूर्ण

		rfd_desc = ATL1_RFD_DESC(rfd_ring, rfd_next_to_use);

		skb = netdev_alloc_skb_ip_align(adapter->netdev,
						adapter->rx_buffer_len);
		अगर (unlikely(!skb)) अणु
			/* Better luck next round */
			adapter->soft_stats.rx_dropped++;
			अवरोध;
		पूर्ण

		buffer_info->alloced = 1;
		buffer_info->skb = skb;
		buffer_info->length = (u16) adapter->rx_buffer_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = dma_map_page(&pdev->dev, page, offset,
						adapter->rx_buffer_len,
						DMA_FROM_DEVICE);
		rfd_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		rfd_desc->buf_len = cpu_to_le16(adapter->rx_buffer_len);
		rfd_desc->coalese = 0;

next:
		rfd_next_to_use = next_next;
		अगर (unlikely(++next_next == rfd_ring->count))
			next_next = 0;

		buffer_info = &rfd_ring->buffer_info[rfd_next_to_use];
		next_info = &rfd_ring->buffer_info[next_next];
		num_alloc++;
	पूर्ण

	अगर (num_alloc) अणु
		/*
		 * Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		atomic_set(&rfd_ring->next_to_use, (पूर्णांक)rfd_next_to_use);
	पूर्ण
	वापस num_alloc;
पूर्ण

अटल पूर्णांक atl1_पूर्णांकr_rx(काष्ठा atl1_adapter *adapter, पूर्णांक budget)
अणु
	पूर्णांक i, count;
	u16 length;
	u16 rrd_next_to_clean;
	u32 value;
	काष्ठा atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	काष्ठा atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	काष्ठा atl1_buffer *buffer_info;
	काष्ठा rx_वापस_desc *rrd;
	काष्ठा sk_buff *skb;

	count = 0;

	rrd_next_to_clean = atomic_पढ़ो(&rrd_ring->next_to_clean);

	जबतक (count < budget) अणु
		rrd = ATL1_RRD_DESC(rrd_ring, rrd_next_to_clean);
		i = 1;
		अगर (likely(rrd->xsz.valid)) अणु	/* packet valid */
chk_rrd:
			/* check rrd status */
			अगर (likely(rrd->num_buf == 1))
				जाओ rrd_ok;
			अन्यथा अगर (netअगर_msg_rx_err(adapter)) अणु
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"unexpected RRD buffer count\n");
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"rx_buf_len = %d\n",
					adapter->rx_buffer_len);
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD num_buf = %d\n",
					rrd->num_buf);
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD pkt_len = %d\n",
					rrd->xsz.xsum_sz.pkt_size);
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD pkt_flg = 0x%08X\n",
					rrd->pkt_flg);
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD err_flg = 0x%08X\n",
					rrd->err_flg);
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD vlan_tag = 0x%08X\n",
					rrd->vlan_tag);
			पूर्ण

			/* rrd seems to be bad */
			अगर (unlikely(i-- > 0)) अणु
				/* rrd may not be DMAed completely */
				udelay(1);
				जाओ chk_rrd;
			पूर्ण
			/* bad rrd */
			अगर (netअगर_msg_rx_err(adapter))
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"bad RRD\n");
			/* see अगर update RFD index */
			अगर (rrd->num_buf > 1)
				atl1_update_rfd_index(adapter, rrd);

			/* update rrd */
			rrd->xsz.valid = 0;
			अगर (++rrd_next_to_clean == rrd_ring->count)
				rrd_next_to_clean = 0;
			count++;
			जारी;
		पूर्ण अन्यथा अणु	/* current rrd still not be updated */

			अवरोध;
		पूर्ण
rrd_ok:
		/* clean alloc flag क्रम bad rrd */
		atl1_clean_alloc_flag(adapter, rrd, 0);

		buffer_info = &rfd_ring->buffer_info[rrd->buf_indx];
		अगर (++rfd_ring->next_to_clean == rfd_ring->count)
			rfd_ring->next_to_clean = 0;

		/* update rrd next to clean */
		अगर (++rrd_next_to_clean == rrd_ring->count)
			rrd_next_to_clean = 0;
		count++;

		अगर (unlikely(rrd->pkt_flg & PACKET_FLAG_ERR)) अणु
			अगर (!(rrd->err_flg &
				(ERR_FLAG_IP_CHKSUM | ERR_FLAG_L4_CHKSUM
				| ERR_FLAG_LEN))) अणु
				/* packet error, करोn't need upstream */
				buffer_info->alloced = 0;
				rrd->xsz.valid = 0;
				जारी;
			पूर्ण
		पूर्ण

		/* Good Receive */
		dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
			       buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->dma = 0;
		skb = buffer_info->skb;
		length = le16_to_cpu(rrd->xsz.xsum_sz.pkt_size);

		skb_put(skb, length - ETH_FCS_LEN);

		/* Receive Checksum Offload */
		atl1_rx_checksum(adapter, rrd, skb);
		skb->protocol = eth_type_trans(skb, adapter->netdev);

		अगर (rrd->pkt_flg & PACKET_FLAG_VLAN_INS) अणु
			u16 vlan_tag = (rrd->vlan_tag >> 4) |
					((rrd->vlan_tag & 7) << 13) |
					((rrd->vlan_tag & 8) << 9);

			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
		पूर्ण
		netअगर_receive_skb(skb);

		/* let protocol layer मुक्त skb */
		buffer_info->skb = शून्य;
		buffer_info->alloced = 0;
		rrd->xsz.valid = 0;
	पूर्ण

	atomic_set(&rrd_ring->next_to_clean, rrd_next_to_clean);

	atl1_alloc_rx_buffers(adapter);

	/* update mailbox ? */
	अगर (count) अणु
		u32 tpd_next_to_use;
		u32 rfd_next_to_use;

		spin_lock(&adapter->mb_lock);

		tpd_next_to_use = atomic_पढ़ो(&adapter->tpd_ring.next_to_use);
		rfd_next_to_use =
		    atomic_पढ़ो(&adapter->rfd_ring.next_to_use);
		rrd_next_to_clean =
		    atomic_पढ़ो(&adapter->rrd_ring.next_to_clean);
		value = ((rfd_next_to_use & MB_RFD_PROD_INDX_MASK) <<
			MB_RFD_PROD_INDX_SHIFT) |
                        ((rrd_next_to_clean & MB_RRD_CONS_INDX_MASK) <<
			MB_RRD_CONS_INDX_SHIFT) |
                        ((tpd_next_to_use & MB_TPD_PROD_INDX_MASK) <<
			MB_TPD_PROD_INDX_SHIFT);
		ioग_लिखो32(value, adapter->hw.hw_addr + REG_MAILBOX);
		spin_unlock(&adapter->mb_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक atl1_पूर्णांकr_tx(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_buffer *buffer_info;
	u16 sw_tpd_next_to_clean;
	u16 cmb_tpd_next_to_clean;
	पूर्णांक count = 0;

	sw_tpd_next_to_clean = atomic_पढ़ो(&tpd_ring->next_to_clean);
	cmb_tpd_next_to_clean = le16_to_cpu(adapter->cmb.cmb->tpd_cons_idx);

	जबतक (cmb_tpd_next_to_clean != sw_tpd_next_to_clean) अणु
		buffer_info = &tpd_ring->buffer_info[sw_tpd_next_to_clean];
		अगर (buffer_info->dma) अणु
			dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
			buffer_info->dma = 0;
		पूर्ण

		अगर (buffer_info->skb) अणु
			dev_consume_skb_irq(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण

		अगर (++sw_tpd_next_to_clean == tpd_ring->count)
			sw_tpd_next_to_clean = 0;

		count++;
	पूर्ण
	atomic_set(&tpd_ring->next_to_clean, sw_tpd_next_to_clean);

	अगर (netअगर_queue_stopped(adapter->netdev) &&
	    netअगर_carrier_ok(adapter->netdev))
		netअगर_wake_queue(adapter->netdev);

	वापस count;
पूर्ण

अटल u16 atl1_tpd_avail(काष्ठा atl1_tpd_ring *tpd_ring)
अणु
	u16 next_to_clean = atomic_पढ़ो(&tpd_ring->next_to_clean);
	u16 next_to_use = atomic_पढ़ो(&tpd_ring->next_to_use);
	वापस (next_to_clean > next_to_use) ?
		next_to_clean - next_to_use - 1 :
		tpd_ring->count + next_to_clean - next_to_use - 1;
पूर्ण

अटल पूर्णांक atl1_tso(काष्ठा atl1_adapter *adapter, काष्ठा sk_buff *skb,
		    काष्ठा tx_packet_desc *ptpd)
अणु
	u8 hdr_len, ip_off;
	u32 real_len;

	अगर (skb_shinfo(skb)->gso_size) अणु
		पूर्णांक err;

		err = skb_cow_head(skb, 0);
		अगर (err < 0)
			वापस err;

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);

			real_len = (((अचिन्हित अक्षर *)iph - skb->data) +
				ntohs(iph->tot_len));
			अगर (real_len < skb->len)
				pskb_trim(skb, real_len);
			hdr_len = (skb_transport_offset(skb) + tcp_hdrlen(skb));
			अगर (skb->len == hdr_len) अणु
				iph->check = 0;
				tcp_hdr(skb)->check =
					~csum_tcpudp_magic(iph->saddr,
					iph->daddr, tcp_hdrlen(skb),
					IPPROTO_TCP, 0);
				ptpd->word3 |= (iph->ihl & TPD_IPHL_MASK) <<
					TPD_IPHL_SHIFT;
				ptpd->word3 |= ((tcp_hdrlen(skb) >> 2) &
					TPD_TCPHDRLEN_MASK) <<
					TPD_TCPHDRLEN_SHIFT;
				ptpd->word3 |= 1 << TPD_IP_CSUM_SHIFT;
				ptpd->word3 |= 1 << TPD_TCP_CSUM_SHIFT;
				वापस 1;
			पूर्ण

			iph->check = 0;
			tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
					iph->daddr, 0, IPPROTO_TCP, 0);
			ip_off = (अचिन्हित अक्षर *)iph -
				(अचिन्हित अक्षर *) skb_network_header(skb);
			अगर (ip_off == 8) /* 802.3-SNAP frame */
				ptpd->word3 |= 1 << TPD_ETHTYPE_SHIFT;
			अन्यथा अगर (ip_off != 0)
				वापस -2;

			ptpd->word3 |= (iph->ihl & TPD_IPHL_MASK) <<
				TPD_IPHL_SHIFT;
			ptpd->word3 |= ((tcp_hdrlen(skb) >> 2) &
				TPD_TCPHDRLEN_MASK) << TPD_TCPHDRLEN_SHIFT;
			ptpd->word3 |= (skb_shinfo(skb)->gso_size &
				TPD_MSS_MASK) << TPD_MSS_SHIFT;
			ptpd->word3 |= 1 << TPD_SEGMENT_EN_SHIFT;
			वापस 3;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक atl1_tx_csum(काष्ठा atl1_adapter *adapter, काष्ठा sk_buff *skb,
	काष्ठा tx_packet_desc *ptpd)
अणु
	u8 css, cso;

	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		css = skb_checksum_start_offset(skb);
		cso = css + (u8) skb->csum_offset;
		अगर (unlikely(css & 0x1)) अणु
			/* L1 hardware requires an even number here */
			अगर (netअगर_msg_tx_err(adapter))
				dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
					"payload offset not an even number\n");
			वापस -1;
		पूर्ण
		ptpd->word3 |= (css & TPD_PLOADOFFSET_MASK) <<
			TPD_PLOADOFFSET_SHIFT;
		ptpd->word3 |= (cso & TPD_CCSUMOFFSET_MASK) <<
			TPD_CCSUMOFFSET_SHIFT;
		ptpd->word3 |= 1 << TPD_CUST_CSUM_EN_SHIFT;
		वापस true;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम atl1_tx_map(काष्ठा atl1_adapter *adapter, काष्ठा sk_buff *skb,
	काष्ठा tx_packet_desc *ptpd)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_buffer *buffer_info;
	u16 buf_len = skb->len;
	काष्ठा page *page;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक nr_frags;
	अचिन्हित पूर्णांक f;
	पूर्णांक retval;
	u16 next_to_use;
	u16 data_len;
	u8 hdr_len;

	buf_len -= skb->data_len;
	nr_frags = skb_shinfo(skb)->nr_frags;
	next_to_use = atomic_पढ़ो(&tpd_ring->next_to_use);
	buffer_info = &tpd_ring->buffer_info[next_to_use];
	BUG_ON(buffer_info->skb);
	/* put skb in last TPD */
	buffer_info->skb = शून्य;

	retval = (ptpd->word3 >> TPD_SEGMENT_EN_SHIFT) & TPD_SEGMENT_EN_MASK;
	अगर (retval) अणु
		/* TSO */
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		buffer_info->length = hdr_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = dma_map_page(&adapter->pdev->dev, page,
						offset, hdr_len,
						DMA_TO_DEVICE);

		अगर (++next_to_use == tpd_ring->count)
			next_to_use = 0;

		अगर (buf_len > hdr_len) अणु
			पूर्णांक i, nseg;

			data_len = buf_len - hdr_len;
			nseg = (data_len + ATL1_MAX_TX_BUF_LEN - 1) /
				ATL1_MAX_TX_BUF_LEN;
			क्रम (i = 0; i < nseg; i++) अणु
				buffer_info =
				    &tpd_ring->buffer_info[next_to_use];
				buffer_info->skb = शून्य;
				buffer_info->length =
				    (ATL1_MAX_TX_BUF_LEN >=
				     data_len) ? ATL1_MAX_TX_BUF_LEN : data_len;
				data_len -= buffer_info->length;
				page = virt_to_page(skb->data +
					(hdr_len + i * ATL1_MAX_TX_BUF_LEN));
				offset = offset_in_page(skb->data +
					(hdr_len + i * ATL1_MAX_TX_BUF_LEN));
				buffer_info->dma = dma_map_page(&adapter->pdev->dev,
								page, offset,
								buffer_info->length,
								DMA_TO_DEVICE);
				अगर (++next_to_use == tpd_ring->count)
					next_to_use = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* not TSO */
		buffer_info->length = buf_len;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
		buffer_info->dma = dma_map_page(&adapter->pdev->dev, page,
						offset, buf_len,
						DMA_TO_DEVICE);
		अगर (++next_to_use == tpd_ring->count)
			next_to_use = 0;
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		u16 i, nseg;

		buf_len = skb_frag_size(frag);

		nseg = (buf_len + ATL1_MAX_TX_BUF_LEN - 1) /
			ATL1_MAX_TX_BUF_LEN;
		क्रम (i = 0; i < nseg; i++) अणु
			buffer_info = &tpd_ring->buffer_info[next_to_use];
			BUG_ON(buffer_info->skb);

			buffer_info->skb = शून्य;
			buffer_info->length = (buf_len > ATL1_MAX_TX_BUF_LEN) ?
				ATL1_MAX_TX_BUF_LEN : buf_len;
			buf_len -= buffer_info->length;
			buffer_info->dma = skb_frag_dma_map(&adapter->pdev->dev,
				frag, i * ATL1_MAX_TX_BUF_LEN,
				buffer_info->length, DMA_TO_DEVICE);

			अगर (++next_to_use == tpd_ring->count)
				next_to_use = 0;
		पूर्ण
	पूर्ण

	/* last tpd's buffer-info */
	buffer_info->skb = skb;
पूर्ण

अटल व्योम atl1_tx_queue(काष्ठा atl1_adapter *adapter, u16 count,
       काष्ठा tx_packet_desc *ptpd)
अणु
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	काष्ठा atl1_buffer *buffer_info;
	काष्ठा tx_packet_desc *tpd;
	u16 j;
	u32 val;
	u16 next_to_use = (u16) atomic_पढ़ो(&tpd_ring->next_to_use);

	क्रम (j = 0; j < count; j++) अणु
		buffer_info = &tpd_ring->buffer_info[next_to_use];
		tpd = ATL1_TPD_DESC(&adapter->tpd_ring, next_to_use);
		अगर (tpd != ptpd)
			स_नकल(tpd, ptpd, माप(काष्ठा tx_packet_desc));
		tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		tpd->word2 &= ~(TPD_BUFLEN_MASK << TPD_BUFLEN_SHIFT);
		tpd->word2 |= (cpu_to_le16(buffer_info->length) &
			TPD_BUFLEN_MASK) << TPD_BUFLEN_SHIFT;

		/*
		 * अगर this is the first packet in a TSO chain, set
		 * TPD_HDRFLAG, otherwise, clear it.
		 */
		val = (tpd->word3 >> TPD_SEGMENT_EN_SHIFT) &
			TPD_SEGMENT_EN_MASK;
		अगर (val) अणु
			अगर (!j)
				tpd->word3 |= 1 << TPD_HDRFLAG_SHIFT;
			अन्यथा
				tpd->word3 &= ~(1 << TPD_HDRFLAG_SHIFT);
		पूर्ण

		अगर (j == (count - 1))
			tpd->word3 |= 1 << TPD_EOP_SHIFT;

		अगर (++next_to_use == tpd_ring->count)
			next_to_use = 0;
	पूर्ण
	/*
	 * Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();

	atomic_set(&tpd_ring->next_to_use, next_to_use);
पूर्ण

अटल netdev_tx_t atl1_xmit_frame(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	पूर्णांक len;
	पूर्णांक tso;
	पूर्णांक count = 1;
	पूर्णांक ret_val;
	काष्ठा tx_packet_desc *ptpd;
	u16 vlan_tag;
	अचिन्हित पूर्णांक nr_frags = 0;
	अचिन्हित पूर्णांक mss = 0;
	अचिन्हित पूर्णांक f;
	अचिन्हित पूर्णांक proto_hdr_len;

	len = skb_headlen(skb);

	अगर (unlikely(skb->len <= 0)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	nr_frags = skb_shinfo(skb)->nr_frags;
	क्रम (f = 0; f < nr_frags; f++) अणु
		अचिन्हित पूर्णांक f_size = skb_frag_size(&skb_shinfo(skb)->frags[f]);
		count += (f_size + ATL1_MAX_TX_BUF_LEN - 1) /
			 ATL1_MAX_TX_BUF_LEN;
	पूर्ण

	mss = skb_shinfo(skb)->gso_size;
	अगर (mss) अणु
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			proto_hdr_len = (skb_transport_offset(skb) +
					 tcp_hdrlen(skb));
			अगर (unlikely(proto_hdr_len > len)) अणु
				dev_kमुक्त_skb_any(skb);
				वापस NETDEV_TX_OK;
			पूर्ण
			/* need additional TPD ? */
			अगर (proto_hdr_len != len)
				count += (len - proto_hdr_len +
					ATL1_MAX_TX_BUF_LEN - 1) /
					ATL1_MAX_TX_BUF_LEN;
		पूर्ण
	पूर्ण

	अगर (atl1_tpd_avail(&adapter->tpd_ring) < count) अणु
		/* not enough descriptors */
		netअगर_stop_queue(netdev);
		अगर (netअगर_msg_tx_queued(adapter))
			dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
				"tx busy\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	ptpd = ATL1_TPD_DESC(tpd_ring,
		(u16) atomic_पढ़ो(&tpd_ring->next_to_use));
	स_रखो(ptpd, 0, माप(काष्ठा tx_packet_desc));

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_tag = skb_vlan_tag_get(skb);
		vlan_tag = (vlan_tag << 4) | (vlan_tag >> 13) |
			((vlan_tag >> 9) & 0x8);
		ptpd->word3 |= 1 << TPD_INS_VL_TAG_SHIFT;
		ptpd->word2 |= (vlan_tag & TPD_VLANTAG_MASK) <<
			TPD_VLANTAG_SHIFT;
	पूर्ण

	tso = atl1_tso(adapter, skb, ptpd);
	अगर (tso < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (!tso) अणु
		ret_val = atl1_tx_csum(adapter, skb, ptpd);
		अगर (ret_val < 0) अणु
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	atl1_tx_map(adapter, skb, ptpd);
	atl1_tx_queue(adapter, count, ptpd);
	atl1_update_mailbox(adapter);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक atl1_rings_clean(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा atl1_adapter *adapter = container_of(napi, काष्ठा atl1_adapter, napi);
	पूर्णांक work_करोne = atl1_पूर्णांकr_rx(adapter, budget);

	अगर (atl1_पूर्णांकr_tx(adapter))
		work_करोne = budget;

	/* Let's come again to process some more packets */
	अगर (work_करोne >= budget)
		वापस work_करोne;

	napi_complete_करोne(napi, work_करोne);
	/* re-enable Interrupt */
	अगर (likely(adapter->पूर्णांक_enabled))
		atlx_imr_set(adapter, IMR_NORMAL_MASK);
	वापस work_करोne;
पूर्ण

अटल अंतरभूत पूर्णांक atl1_sched_rings_clean(काष्ठा atl1_adapter* adapter)
अणु
	अगर (!napi_schedule_prep(&adapter->napi))
		/* It is possible in हाल even the RX/TX पूर्णांकs are disabled via IMR
		 * रेजिस्टर the ISR bits are set anyway (but करो not produce IRQ).
		 * To handle such situation the napi functions used to check is
		 * something scheduled or not.
		 */
		वापस 0;

	__napi_schedule(&adapter->napi);

	/*
	 * Disable RX/TX पूर्णांकs via IMR रेजिस्टर अगर it is
	 * allowed. NAPI handler must reenable them in same
	 * way.
	 */
	अगर (!adapter->पूर्णांक_enabled)
		वापस 1;

	atlx_imr_set(adapter, IMR_NORXTX_MASK);
	वापस 1;
पूर्ण

/**
 * atl1_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t atl1_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(data);
	u32 status;

	status = adapter->cmb.cmb->पूर्णांक_stats;
	अगर (!status)
		वापस IRQ_NONE;

	/* clear CMB पूर्णांकerrupt status at once,
	 * but leave rx/tx पूर्णांकerrupt status in हाल it should be dropped
	 * only अगर rx/tx processing queued. In other हाल पूर्णांकerrupt
	 * can be lost.
	 */
	adapter->cmb.cmb->पूर्णांक_stats = status & (ISR_CMB_TX | ISR_CMB_RX);

	अगर (status & ISR_GPHY)	/* clear phy status */
		atlx_clear_phy_पूर्णांक(adapter);

	/* clear ISR status, and Enable CMB DMA/Disable Interrupt */
	ioग_लिखो32(status | ISR_DIS_INT, adapter->hw.hw_addr + REG_ISR);

	/* check अगर SMB पूर्णांकr */
	अगर (status & ISR_SMB)
		atl1_inc_smb(adapter);

	/* check अगर PCIE PHY Link करोwn */
	अगर (status & ISR_PHY_LINKDOWN) अणु
		अगर (netअगर_msg_पूर्णांकr(adapter))
			dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
				"pcie phy link down %x\n", status);
		अगर (netअगर_running(adapter->netdev)) अणु	/* reset MAC */
			atlx_irq_disable(adapter);
			schedule_work(&adapter->reset_dev_task);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	/* check अगर DMA पढ़ो/ग_लिखो error ? */
	अगर (status & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) अणु
		अगर (netअगर_msg_पूर्णांकr(adapter))
			dev_prपूर्णांकk(KERN_DEBUG, &adapter->pdev->dev,
				"pcie DMA r/w error (status = 0x%x)\n",
				status);
		atlx_irq_disable(adapter);
		schedule_work(&adapter->reset_dev_task);
		वापस IRQ_HANDLED;
	पूर्ण

	/* link event */
	अगर (status & ISR_GPHY) अणु
		adapter->soft_stats.tx_carrier_errors++;
		atl1_check_क्रम_link(adapter);
	पूर्ण

	/* transmit or receive event */
	अगर (status & (ISR_CMB_TX | ISR_CMB_RX) &&
	    atl1_sched_rings_clean(adapter))
		adapter->cmb.cmb->पूर्णांक_stats = adapter->cmb.cmb->पूर्णांक_stats &
					      ~(ISR_CMB_TX | ISR_CMB_RX);

	/* rx exception */
	अगर (unlikely(status & (ISR_RXF_OV | ISR_RFD_UNRUN |
		ISR_RRD_OV | ISR_HOST_RFD_UNRUN |
		ISR_HOST_RRD_OV))) अणु
		अगर (netअगर_msg_पूर्णांकr(adapter))
			dev_prपूर्णांकk(KERN_DEBUG,
				&adapter->pdev->dev,
				"rx exception, ISR = 0x%x\n",
				status);
		atl1_sched_rings_clean(adapter);
	पूर्ण

	/* re-enable Interrupt */
	ioग_लिखो32(ISR_DIS_SMB | ISR_DIS_DMA, adapter->hw.hw_addr + REG_ISR);
	वापस IRQ_HANDLED;
पूर्ण


/**
 * atl1_phy_config - Timer Call-back
 * @t: समयr_list containing poपूर्णांकer to netdev cast पूर्णांकo an अचिन्हित दीर्घ
 */
अटल व्योम atl1_phy_config(काष्ठा समयr_list *t)
अणु
	काष्ठा atl1_adapter *adapter = from_समयr(adapter, t,
						  phy_config_समयr);
	काष्ठा atl1_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->lock, flags);
	adapter->phy_समयr_pending = false;
	atl1_ग_लिखो_phy_reg(hw, MII_ADVERTISE, hw->mii_स्वतःneg_adv_reg);
	atl1_ग_लिखो_phy_reg(hw, MII_ATLX_CR, hw->mii_1000t_ctrl_reg);
	atl1_ग_लिखो_phy_reg(hw, MII_BMCR, MII_CR_RESET | MII_CR_AUTO_NEG_EN);
	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

/*
 * Orphaned venकरोr comment left पूर्णांकact here:
 * <venकरोr comment>
 * If TPD Buffer size equal to 0, PCIE DMAR_TO_INT
 * will निश्चित. We करो soft reset <0x1400=1> according
 * with the SPEC. BUT, it seemes that PCIE or DMA
 * state-machine will not be reset. DMAR_TO_INT will
 * निश्चित again and again.
 * </venकरोr comment>
 */

अटल पूर्णांक atl1_reset(काष्ठा atl1_adapter *adapter)
अणु
	पूर्णांक ret;
	ret = atl1_reset_hw(&adapter->hw);
	अगर (ret)
		वापस ret;
	वापस atl1_init_hw(&adapter->hw);
पूर्ण

अटल s32 atl1_up(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;
	पूर्णांक irq_flags = 0;

	/* hardware has been reset, we need to reload some things */
	atlx_set_multi(netdev);
	atl1_init_ring_ptrs(adapter);
	atlx_restore_vlan(adapter);
	err = atl1_alloc_rx_buffers(adapter);
	अगर (unlikely(!err))
		/* no RX BUFFER allocated */
		वापस -ENOMEM;

	अगर (unlikely(atl1_configure(adapter))) अणु
		err = -EIO;
		जाओ err_up;
	पूर्ण

	err = pci_enable_msi(adapter->pdev);
	अगर (err) अणु
		अगर (netअगर_msg_अगरup(adapter))
			dev_info(&adapter->pdev->dev,
				"Unable to enable MSI: %d\n", err);
		irq_flags |= IRQF_SHARED;
	पूर्ण

	err = request_irq(adapter->pdev->irq, atl1_पूर्णांकr, irq_flags,
			netdev->name, netdev);
	अगर (unlikely(err))
		जाओ err_up;

	napi_enable(&adapter->napi);
	atlx_irq_enable(adapter);
	atl1_check_link(adapter);
	netअगर_start_queue(netdev);
	वापस 0;

err_up:
	pci_disable_msi(adapter->pdev);
	/* मुक्त rx_buffers */
	atl1_clean_rx_ring(adapter);
	वापस err;
पूर्ण

अटल व्योम atl1_करोwn(काष्ठा atl1_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	napi_disable(&adapter->napi);
	netअगर_stop_queue(netdev);
	del_समयr_sync(&adapter->phy_config_समयr);
	adapter->phy_समयr_pending = false;

	atlx_irq_disable(adapter);
	मुक्त_irq(adapter->pdev->irq, netdev);
	pci_disable_msi(adapter->pdev);
	atl1_reset_hw(&adapter->hw);
	adapter->cmb.cmb->पूर्णांक_stats = 0;

	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	netअगर_carrier_off(netdev);

	atl1_clean_tx_ring(adapter);
	atl1_clean_rx_ring(adapter);
पूर्ण

अटल व्योम atl1_reset_dev_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atl1_adapter *adapter =
		container_of(work, काष्ठा atl1_adapter, reset_dev_task);
	काष्ठा net_device *netdev = adapter->netdev;

	netअगर_device_detach(netdev);
	atl1_करोwn(adapter);
	atl1_up(adapter);
	netअगर_device_attach(netdev);
पूर्ण

/**
 * atl1_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक atl1_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;

	adapter->hw.max_frame_size = max_frame;
	adapter->hw.tx_jumbo_task_th = (max_frame + 7) >> 3;
	adapter->rx_buffer_len = (max_frame + 7) & ~7;
	adapter->hw.rx_jumbo_th = adapter->rx_buffer_len / 8;

	netdev->mtu = new_mtu;
	अगर (netअगर_running(netdev)) अणु
		atl1_करोwn(adapter);
		atl1_up(adapter);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * atl1_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 */
अटल पूर्णांक atl1_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = atl1_setup_ring_resources(adapter);
	अगर (err)
		वापस err;

	err = atl1_up(adapter);
	अगर (err)
		जाओ err_up;

	वापस 0;

err_up:
	atl1_reset(adapter);
	वापस err;
पूर्ण

/**
 * atl1_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक atl1_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	atl1_करोwn(adapter);
	atl1_मुक्त_ring_resources(adapter);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक atl1_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;
	u32 ctrl = 0;
	u32 wufc = adapter->wol;
	u32 val;
	u16 speed;
	u16 duplex;

	netअगर_device_detach(netdev);
	अगर (netअगर_running(netdev))
		atl1_करोwn(adapter);

	atl1_पढ़ो_phy_reg(hw, MII_BMSR, (u16 *) & ctrl);
	atl1_पढ़ो_phy_reg(hw, MII_BMSR, (u16 *) & ctrl);
	val = ctrl & BMSR_LSTATUS;
	अगर (val)
		wufc &= ~ATLX_WUFC_LNKC;
	अगर (!wufc)
		जाओ disable_wol;

	अगर (val) अणु
		val = atl1_get_speed_and_duplex(hw, &speed, &duplex);
		अगर (val) अणु
			अगर (netअगर_msg_अगरकरोwn(adapter))
				dev_prपूर्णांकk(KERN_DEBUG, dev,
					"error getting speed/duplex\n");
			जाओ disable_wol;
		पूर्ण

		ctrl = 0;

		/* enable magic packet WOL */
		अगर (wufc & ATLX_WUFC_MAG)
			ctrl |= (WOL_MAGIC_EN | WOL_MAGIC_PME_EN);
		ioग_लिखो32(ctrl, hw->hw_addr + REG_WOL_CTRL);
		ioपढ़ो32(hw->hw_addr + REG_WOL_CTRL);

		/* configure the mac */
		ctrl = MAC_CTRL_RX_EN;
		ctrl |= ((u32)((speed == SPEED_1000) ? MAC_CTRL_SPEED_1000 :
			MAC_CTRL_SPEED_10_100) << MAC_CTRL_SPEED_SHIFT);
		अगर (duplex == FULL_DUPLEX)
			ctrl |= MAC_CTRL_DUPLX;
		ctrl |= (((u32)adapter->hw.preamble_len &
			MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);
		__atlx_vlan_mode(netdev->features, &ctrl);
		अगर (wufc & ATLX_WUFC_MAG)
			ctrl |= MAC_CTRL_BC_EN;
		ioग_लिखो32(ctrl, hw->hw_addr + REG_MAC_CTRL);
		ioपढ़ो32(hw->hw_addr + REG_MAC_CTRL);

		/* poke the PHY */
		ctrl = ioपढ़ो32(hw->hw_addr + REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		ioग_लिखो32(ctrl, hw->hw_addr + REG_PCIE_PHYMISC);
		ioपढ़ो32(hw->hw_addr + REG_PCIE_PHYMISC);
	पूर्ण अन्यथा अणु
		ctrl |= (WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN);
		ioग_लिखो32(ctrl, hw->hw_addr + REG_WOL_CTRL);
		ioपढ़ो32(hw->hw_addr + REG_WOL_CTRL);
		ioग_लिखो32(0, hw->hw_addr + REG_MAC_CTRL);
		ioपढ़ो32(hw->hw_addr + REG_MAC_CTRL);
		hw->phy_configured = false;
	पूर्ण

	वापस 0;

 disable_wol:
	ioग_लिखो32(0, hw->hw_addr + REG_WOL_CTRL);
	ioपढ़ो32(hw->hw_addr + REG_WOL_CTRL);
	ctrl = ioपढ़ो32(hw->hw_addr + REG_PCIE_PHYMISC);
	ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
	ioग_लिखो32(ctrl, hw->hw_addr + REG_PCIE_PHYMISC);
	ioपढ़ो32(hw->hw_addr + REG_PCIE_PHYMISC);
	hw->phy_configured = false;

	वापस 0;
पूर्ण

अटल पूर्णांक atl1_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

	ioग_लिखो32(0, adapter->hw.hw_addr + REG_WOL_CTRL);

	atl1_reset_hw(&adapter->hw);

	अगर (netअगर_running(netdev)) अणु
		adapter->cmb.cmb->पूर्णांक_stats = 0;
		atl1_up(adapter);
	पूर्ण
	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(atl1_pm_ops, atl1_suspend, atl1_resume);

अटल व्योम atl1_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

#अगर_घोषित CONFIG_PM_SLEEP
	atl1_suspend(&pdev->dev);
#पूर्ण_अगर
	pci_wake_from_d3(pdev, adapter->wol);
	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम atl1_poll_controller(काष्ठा net_device *netdev)
अणु
	disable_irq(netdev->irq);
	atl1_पूर्णांकr(netdev->irq, netdev);
	enable_irq(netdev->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops atl1_netdev_ops = अणु
	.nकरो_खोलो		= atl1_खोलो,
	.nकरो_stop		= atl1_बंद,
	.nकरो_start_xmit		= atl1_xmit_frame,
	.nकरो_set_rx_mode	= atlx_set_multi,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= atl1_set_mac,
	.nकरो_change_mtu		= atl1_change_mtu,
	.nकरो_fix_features	= atlx_fix_features,
	.nकरो_set_features	= atlx_set_features,
	.nकरो_करो_ioctl		= atlx_ioctl,
	.nकरो_tx_समयout		= atlx_tx_समयout,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= atl1_poll_controller,
#पूर्ण_अगर
पूर्ण;

/**
 * atl1_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in atl1_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * atl1_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक atl1_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा atl1_adapter *adapter;
	अटल पूर्णांक cards_found = 0;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	/*
	 * The atl1 chip can DMA to 64-bit addresses, but it uses a single
	 * shared रेजिस्टर क्रम the high 32 bits, so only a single, aligned,
	 * 4 GB physical address range can be used at a समय.
	 *
	 * Supporting 64-bit DMA on this hardware is more trouble than it's
	 * worth.  It is far easier to limit to 32-bit DMA than update
	 * various kernel subप्रणालीs to support the mechanics required by a
	 * fixed-high-32-bit प्रणाली.
	 */
	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "no usable DMA configuration\n");
		जाओ err_dma;
	पूर्ण
	/*
	 * Mark all PCI regions associated with PCI device
	 * pdev as being reserved by owner atl1_driver_name
	 */
	err = pci_request_regions(pdev, ATLX_DRIVER_NAME);
	अगर (err)
		जाओ err_request_regions;

	/*
	 * Enables bus-mastering on the device and calls
	 * pcibios_set_master to करो the needed arch specअगरic settings
	 */
	pci_set_master(pdev);

	netdev = alloc_etherdev(माप(काष्ठा atl1_adapter));
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण
	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->hw.back = adapter;
	adapter->msg_enable = netअगर_msg_init(debug, atl1_शेष_msg);

	adapter->hw.hw_addr = pci_iomap(pdev, 0, 0);
	अगर (!adapter->hw.hw_addr) अणु
		err = -EIO;
		जाओ err_pci_iomap;
	पूर्ण
	/* get device revision number */
	adapter->hw.dev_rev = ioपढ़ो16(adapter->hw.hw_addr +
		(REG_MASTER_CTRL + 2));

	/* set शेष ring resource counts */
	adapter->rfd_ring.count = adapter->rrd_ring.count = ATL1_DEFAULT_RFD;
	adapter->tpd_ring.count = ATL1_DEFAULT_TPD;

	adapter->mii.dev = netdev;
	adapter->mii.mdio_पढ़ो = mdio_पढ़ो;
	adapter->mii.mdio_ग_लिखो = mdio_ग_लिखो;
	adapter->mii.phy_id_mask = 0x1f;
	adapter->mii.reg_num_mask = 0x1f;

	netdev->netdev_ops = &atl1_netdev_ops;
	netdev->watchकरोg_समयo = 5 * HZ;
	netअगर_napi_add(netdev, &adapter->napi, atl1_rings_clean, 64);

	netdev->ethtool_ops = &atl1_ethtool_ops;
	adapter->bd_number = cards_found;

	/* setup the निजी काष्ठाure */
	err = atl1_sw_init(adapter);
	अगर (err)
		जाओ err_common;

	netdev->features = NETIF_F_HW_CSUM;
	netdev->features |= NETIF_F_SG;
	netdev->features |= (NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX);

	netdev->hw_features = NETIF_F_HW_CSUM | NETIF_F_SG | NETIF_F_TSO |
			      NETIF_F_HW_VLAN_CTAG_RX;

	/* is this valid? see atl1_setup_mac_ctrl() */
	netdev->features |= NETIF_F_RXCSUM;

	/* MTU range: 42 - 10218 */
	netdev->min_mtu = ETH_ZLEN - (ETH_HLEN + VLAN_HLEN);
	netdev->max_mtu = MAX_JUMBO_FRAME_SIZE -
			  (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

	/*
	 * patch क्रम some L1 of old version,
	 * the final version of L1 may not need these
	 * patches
	 */
	/* atl1_pcie_patch(adapter); */

	/* really reset GPHY core */
	ioग_लिखो16(0, adapter->hw.hw_addr + REG_PHY_ENABLE);

	/*
	 * reset the controller to
	 * put the device in a known good starting state
	 */
	अगर (atl1_reset_hw(&adapter->hw)) अणु
		err = -EIO;
		जाओ err_common;
	पूर्ण

	/* copy the MAC address out of the EEPROM */
	अगर (atl1_पढ़ो_mac_addr(&adapter->hw)) अणु
		/* mark अक्रमom mac */
		netdev->addr_assign_type = NET_ADDR_RANDOM;
	पूर्ण
	स_नकल(netdev->dev_addr, adapter->hw.mac_addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		err = -EIO;
		जाओ err_common;
	पूर्ण

	atl1_check_options(adapter);

	/* pre-init the MAC, and setup link */
	err = atl1_init_hw(&adapter->hw);
	अगर (err) अणु
		err = -EIO;
		जाओ err_common;
	पूर्ण

	atl1_pcie_patch(adapter);
	/* assume we have no link क्रम now */
	netअगर_carrier_off(netdev);

	समयr_setup(&adapter->phy_config_समयr, atl1_phy_config, 0);
	adapter->phy_समयr_pending = false;

	INIT_WORK(&adapter->reset_dev_task, atl1_reset_dev_task);

	INIT_WORK(&adapter->link_chg_task, atlx_link_chg_task);

	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_common;

	cards_found++;
	atl1_via_workaround(adapter);
	वापस 0;

err_common:
	pci_iounmap(pdev, adapter->hw.hw_addr);
err_pci_iomap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_dma:
err_request_regions:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * atl1_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * atl1_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 */
अटल व्योम atl1_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा atl1_adapter *adapter;
	/* Device not available. Return. */
	अगर (!netdev)
		वापस;

	adapter = netdev_priv(netdev);

	/*
	 * Some atl1 boards lack persistent storage क्रम their MAC, and get it
	 * from the BIOS during POST.  If we've been messing with the MAC
	 * address, we need to save the permanent one.
	 */
	अगर (!ether_addr_equal_unaligned(adapter->hw.mac_addr,
					adapter->hw.perm_mac_addr)) अणु
		स_नकल(adapter->hw.mac_addr, adapter->hw.perm_mac_addr,
			ETH_ALEN);
		atl1_set_mac_addr(&adapter->hw);
	पूर्ण

	ioग_लिखो16(0, adapter->hw.hw_addr + REG_PHY_ENABLE);
	unरेजिस्टर_netdev(netdev);
	pci_iounmap(pdev, adapter->hw.hw_addr);
	pci_release_regions(pdev);
	मुक्त_netdev(netdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver atl1_driver = अणु
	.name = ATLX_DRIVER_NAME,
	.id_table = atl1_pci_tbl,
	.probe = atl1_probe,
	.हटाओ = atl1_हटाओ,
	.shutकरोwn = atl1_shutकरोwn,
	.driver.pm = &atl1_pm_ops,
पूर्ण;

काष्ठा atl1_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा ATL1_STAT(m) \
	माप(((काष्ठा atl1_adapter *)0)->m), दुरत्व(काष्ठा atl1_adapter, m)

अटल काष्ठा atl1_stats atl1_gstrings_stats[] = अणु
	अणु"rx_packets", ATL1_STAT(soft_stats.rx_packets)पूर्ण,
	अणु"tx_packets", ATL1_STAT(soft_stats.tx_packets)पूर्ण,
	अणु"rx_bytes", ATL1_STAT(soft_stats.rx_bytes)पूर्ण,
	अणु"tx_bytes", ATL1_STAT(soft_stats.tx_bytes)पूर्ण,
	अणु"rx_errors", ATL1_STAT(soft_stats.rx_errors)पूर्ण,
	अणु"tx_errors", ATL1_STAT(soft_stats.tx_errors)पूर्ण,
	अणु"multicast", ATL1_STAT(soft_stats.multicast)पूर्ण,
	अणु"collisions", ATL1_STAT(soft_stats.collisions)पूर्ण,
	अणु"rx_length_errors", ATL1_STAT(soft_stats.rx_length_errors)पूर्ण,
	अणु"rx_over_errors", ATL1_STAT(soft_stats.rx_missed_errors)पूर्ण,
	अणु"rx_crc_errors", ATL1_STAT(soft_stats.rx_crc_errors)पूर्ण,
	अणु"rx_frame_errors", ATL1_STAT(soft_stats.rx_frame_errors)पूर्ण,
	अणु"rx_fifo_errors", ATL1_STAT(soft_stats.rx_fअगरo_errors)पूर्ण,
	अणु"rx_missed_errors", ATL1_STAT(soft_stats.rx_missed_errors)पूर्ण,
	अणु"tx_aborted_errors", ATL1_STAT(soft_stats.tx_पातed_errors)पूर्ण,
	अणु"tx_carrier_errors", ATL1_STAT(soft_stats.tx_carrier_errors)पूर्ण,
	अणु"tx_fifo_errors", ATL1_STAT(soft_stats.tx_fअगरo_errors)पूर्ण,
	अणु"tx_window_errors", ATL1_STAT(soft_stats.tx_winकरोw_errors)पूर्ण,
	अणु"tx_abort_exce_coll", ATL1_STAT(soft_stats.excecol)पूर्ण,
	अणु"tx_abort_late_coll", ATL1_STAT(soft_stats.latecol)पूर्ण,
	अणु"tx_deferred_ok", ATL1_STAT(soft_stats.deffer)पूर्ण,
	अणु"tx_single_coll_ok", ATL1_STAT(soft_stats.scc)पूर्ण,
	अणु"tx_multi_coll_ok", ATL1_STAT(soft_stats.mcc)पूर्ण,
	अणु"tx_underrun", ATL1_STAT(soft_stats.tx_underrun)पूर्ण,
	अणु"tx_trunc", ATL1_STAT(soft_stats.tx_trunc)पूर्ण,
	अणु"tx_pause", ATL1_STAT(soft_stats.tx_छोड़ो)पूर्ण,
	अणु"rx_pause", ATL1_STAT(soft_stats.rx_छोड़ो)पूर्ण,
	अणु"rx_rrd_ov", ATL1_STAT(soft_stats.rx_rrd_ov)पूर्ण,
	अणु"rx_trunc", ATL1_STAT(soft_stats.rx_trunc)पूर्ण
पूर्ण;

अटल व्योम atl1_get_ethtool_stats(काष्ठा net_device *netdev,
	काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	अक्षर *p;

	क्रम (i = 0; i < ARRAY_SIZE(atl1_gstrings_stats); i++) अणु
		p = (अक्षर *)adapter+atl1_gstrings_stats[i].stat_offset;
		data[i] = (atl1_gstrings_stats[i].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

पूर्ण

अटल पूर्णांक atl1_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(atl1_gstrings_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक atl1_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_Autoneg | SUPPORTED_TP);
	advertising = ADVERTISED_TP;
	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL) अणु
		advertising |= ADVERTISED_Autoneg;
		अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR) अणु
			advertising |= ADVERTISED_Autoneg;
			advertising |=
			    (ADVERTISED_10baseT_Half |
			     ADVERTISED_10baseT_Full |
			     ADVERTISED_100baseT_Half |
			     ADVERTISED_100baseT_Full |
			     ADVERTISED_1000baseT_Full);
		पूर्ण अन्यथा
			advertising |= (ADVERTISED_1000baseT_Full);
	पूर्ण
	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;

	अगर (netअगर_carrier_ok(adapter->netdev)) अणु
		u16 link_speed, link_duplex;
		atl1_get_speed_and_duplex(hw, &link_speed, &link_duplex);
		cmd->base.speed = link_speed;
		अगर (link_duplex == FULL_DUPLEX)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक atl1_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;
	u16 phy_data;
	पूर्णांक ret_val = 0;
	u16 old_media_type = hw->media_type;

	अगर (netअगर_running(adapter->netdev)) अणु
		अगर (netअगर_msg_link(adapter))
			dev_dbg(&adapter->pdev->dev,
				"ethtool shutting down adapter\n");
		atl1_करोwn(adapter);
	पूर्ण

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE)
		hw->media_type = MEDIA_TYPE_AUTO_SENSOR;
	अन्यथा अणु
		u32 speed = cmd->base.speed;
		अगर (speed == SPEED_1000) अणु
			अगर (cmd->base.duplex != DUPLEX_FULL) अणु
				अगर (netअगर_msg_link(adapter))
					dev_warn(&adapter->pdev->dev,
						"1000M half is invalid\n");
				ret_val = -EINVAL;
				जाओ निकास_sset;
			पूर्ण
			hw->media_type = MEDIA_TYPE_1000M_FULL;
		पूर्ण अन्यथा अगर (speed == SPEED_100) अणु
			अगर (cmd->base.duplex == DUPLEX_FULL)
				hw->media_type = MEDIA_TYPE_100M_FULL;
			अन्यथा
				hw->media_type = MEDIA_TYPE_100M_HALF;
		पूर्ण अन्यथा अणु
			अगर (cmd->base.duplex == DUPLEX_FULL)
				hw->media_type = MEDIA_TYPE_10M_FULL;
			अन्यथा
				hw->media_type = MEDIA_TYPE_10M_HALF;
		पूर्ण
	पूर्ण

	अगर (atl1_phy_setup_स्वतःneg_adv(hw)) अणु
		ret_val = -EINVAL;
		अगर (netअगर_msg_link(adapter))
			dev_warn(&adapter->pdev->dev,
				"invalid ethtool speed/duplex setting\n");
		जाओ निकास_sset;
	पूर्ण
	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL)
		phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN;
	अन्यथा अणु
		चयन (hw->media_type) अणु
		हाल MEDIA_TYPE_100M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_100 |
			    MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_100M_HALF:
			phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
			अवरोध;
		हाल MEDIA_TYPE_10M_FULL:
			phy_data =
			    MII_CR_FULL_DUPLEX | MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		शेष:
			/* MEDIA_TYPE_10M_HALF: */
			phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			अवरोध;
		पूर्ण
	पूर्ण
	atl1_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
निकास_sset:
	अगर (ret_val)
		hw->media_type = old_media_type;

	अगर (netअगर_running(adapter->netdev)) अणु
		अगर (netअगर_msg_link(adapter))
			dev_dbg(&adapter->pdev->dev,
				"ethtool starting adapter\n");
		atl1_up(adapter);
	पूर्ण अन्यथा अगर (!ret_val) अणु
		अगर (netअगर_msg_link(adapter))
			dev_dbg(&adapter->pdev->dev,
				"ethtool resetting adapter\n");
		atl1_reset(adapter);
	पूर्ण
	वापस ret_val;
पूर्ण

अटल व्योम atl1_get_drvinfo(काष्ठा net_device *netdev,
	काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, ATLX_DRIVER_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम atl1_get_wol(काष्ठा net_device *netdev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;
	अगर (adapter->wol & ATLX_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक atl1_set_wol(काष्ठा net_device *netdev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_PHY | WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
		WAKE_ARP | WAKE_MAGICSECURE))
		वापस -EOPNOTSUPP;
	adapter->wol = 0;
	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= ATLX_WUFC_MAG;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण

अटल u32 atl1_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम atl1_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = value;
पूर्ण

अटल पूर्णांक atl1_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस ATL1_REG_COUNT * माप(u32);
पूर्ण

अटल व्योम atl1_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
	व्योम *p)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक i;
	u32 *regbuf = p;

	क्रम (i = 0; i < ATL1_REG_COUNT; i++) अणु
		/*
		 * This चयन statement aव्योमs reserved regions
		 * of रेजिस्टर space.
		 */
		चयन (i) अणु
		हाल 6 ... 9:
		हाल 14:
		हाल 29 ... 31:
		हाल 34 ... 63:
		हाल 75 ... 127:
		हाल 136 ... 1023:
		हाल 1027 ... 1087:
		हाल 1091 ... 1151:
		हाल 1194 ... 1195:
		हाल 1200 ... 1201:
		हाल 1206 ... 1213:
		हाल 1216 ... 1279:
		हाल 1290 ... 1311:
		हाल 1323 ... 1343:
		हाल 1358 ... 1359:
		हाल 1368 ... 1375:
		हाल 1378 ... 1383:
		हाल 1388 ... 1391:
		हाल 1393 ... 1395:
		हाल 1402 ... 1403:
		हाल 1410 ... 1471:
		हाल 1522 ... 1535:
			/* reserved region; करोn't पढ़ो it */
			regbuf[i] = 0;
			अवरोध;
		शेष:
			/* unreserved region */
			regbuf[i] = ioपढ़ो32(hw->hw_addr + (i * माप(u32)));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम atl1_get_ringparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_tpd_ring *txdr = &adapter->tpd_ring;
	काष्ठा atl1_rfd_ring *rxdr = &adapter->rfd_ring;

	ring->rx_max_pending = ATL1_MAX_RFD;
	ring->tx_max_pending = ATL1_MAX_TPD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
पूर्ण

अटल पूर्णांक atl1_set_ringparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_tpd_ring *tpdr = &adapter->tpd_ring;
	काष्ठा atl1_rrd_ring *rrdr = &adapter->rrd_ring;
	काष्ठा atl1_rfd_ring *rfdr = &adapter->rfd_ring;

	काष्ठा atl1_tpd_ring tpd_old, tpd_new;
	काष्ठा atl1_rfd_ring rfd_old, rfd_new;
	काष्ठा atl1_rrd_ring rrd_old, rrd_new;
	काष्ठा atl1_ring_header rhdr_old, rhdr_new;
	काष्ठा atl1_smb smb;
	काष्ठा atl1_cmb cmb;
	पूर्णांक err;

	tpd_old = adapter->tpd_ring;
	rfd_old = adapter->rfd_ring;
	rrd_old = adapter->rrd_ring;
	rhdr_old = adapter->ring_header;

	अगर (netअगर_running(adapter->netdev))
		atl1_करोwn(adapter);

	rfdr->count = (u16) max(ring->rx_pending, (u32) ATL1_MIN_RFD);
	rfdr->count = rfdr->count > ATL1_MAX_RFD ? ATL1_MAX_RFD :
			rfdr->count;
	rfdr->count = (rfdr->count + 3) & ~3;
	rrdr->count = rfdr->count;

	tpdr->count = (u16) max(ring->tx_pending, (u32) ATL1_MIN_TPD);
	tpdr->count = tpdr->count > ATL1_MAX_TPD ? ATL1_MAX_TPD :
			tpdr->count;
	tpdr->count = (tpdr->count + 3) & ~3;

	अगर (netअगर_running(adapter->netdev)) अणु
		/* try to get new resources beक्रमe deleting old */
		err = atl1_setup_ring_resources(adapter);
		अगर (err)
			जाओ err_setup_ring;

		/*
		 * save the new, restore the old in order to मुक्त it,
		 * then restore the new back again
		 */

		rfd_new = adapter->rfd_ring;
		rrd_new = adapter->rrd_ring;
		tpd_new = adapter->tpd_ring;
		rhdr_new = adapter->ring_header;
		adapter->rfd_ring = rfd_old;
		adapter->rrd_ring = rrd_old;
		adapter->tpd_ring = tpd_old;
		adapter->ring_header = rhdr_old;
		/*
		 * Save SMB and CMB, since atl1_मुक्त_ring_resources
		 * will clear them.
		 */
		smb = adapter->smb;
		cmb = adapter->cmb;
		atl1_मुक्त_ring_resources(adapter);
		adapter->rfd_ring = rfd_new;
		adapter->rrd_ring = rrd_new;
		adapter->tpd_ring = tpd_new;
		adapter->ring_header = rhdr_new;
		adapter->smb = smb;
		adapter->cmb = cmb;

		err = atl1_up(adapter);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;

err_setup_ring:
	adapter->rfd_ring = rfd_old;
	adapter->rrd_ring = rrd_old;
	adapter->tpd_ring = tpd_old;
	adapter->ring_header = rhdr_old;
	atl1_up(adapter);
	वापस err;
पूर्ण

अटल व्योम atl1_get_छोड़ोparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;

	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL) अणु
		eछोड़ो->स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		eछोड़ो->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण
	eछोड़ो->rx_छोड़ो = 1;
	eछोड़ो->tx_छोड़ो = 1;
पूर्ण

अटल पूर्णांक atl1_set_छोड़ोparam(काष्ठा net_device *netdev,
	काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;

	अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL) अणु
		eछोड़ो->स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा अणु
		eछोड़ो->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	eछोड़ो->rx_छोड़ो = 1;
	eछोड़ो->tx_छोड़ो = 1;

	वापस 0;
पूर्ण

अटल व्योम atl1_get_strings(काष्ठा net_device *netdev, u32 stringset,
	u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(atl1_gstrings_stats); i++) अणु
			स_नकल(p, atl1_gstrings_stats[i].stat_string,
				ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक atl1_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा atl1_adapter *adapter = netdev_priv(netdev);
	काष्ठा atl1_hw *hw = &adapter->hw;

	अगर (netअगर_running(netdev)) अणु
		u16 phy_data;
		atl1_करोwn(adapter);

		अगर (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
			hw->media_type == MEDIA_TYPE_1000M_FULL) अणु
			phy_data = MII_CR_RESET | MII_CR_AUTO_NEG_EN;
		पूर्ण अन्यथा अणु
			चयन (hw->media_type) अणु
			हाल MEDIA_TYPE_100M_FULL:
				phy_data = MII_CR_FULL_DUPLEX |
					MII_CR_SPEED_100 | MII_CR_RESET;
				अवरोध;
			हाल MEDIA_TYPE_100M_HALF:
				phy_data = MII_CR_SPEED_100 | MII_CR_RESET;
				अवरोध;
			हाल MEDIA_TYPE_10M_FULL:
				phy_data = MII_CR_FULL_DUPLEX |
					MII_CR_SPEED_10 | MII_CR_RESET;
				अवरोध;
			शेष:
				/* MEDIA_TYPE_10M_HALF */
				phy_data = MII_CR_SPEED_10 | MII_CR_RESET;
			पूर्ण
		पूर्ण
		atl1_ग_लिखो_phy_reg(hw, MII_BMCR, phy_data);
		atl1_up(adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops atl1_ethtool_ops = अणु
	.get_drvinfo		= atl1_get_drvinfo,
	.get_wol		= atl1_get_wol,
	.set_wol		= atl1_set_wol,
	.get_msglevel		= atl1_get_msglevel,
	.set_msglevel		= atl1_set_msglevel,
	.get_regs_len		= atl1_get_regs_len,
	.get_regs		= atl1_get_regs,
	.get_ringparam		= atl1_get_ringparam,
	.set_ringparam		= atl1_set_ringparam,
	.get_छोड़ोparam		= atl1_get_छोड़ोparam,
	.set_छोड़ोparam		= atl1_set_छोड़ोparam,
	.get_link		= ethtool_op_get_link,
	.get_strings		= atl1_get_strings,
	.nway_reset		= atl1_nway_reset,
	.get_ethtool_stats	= atl1_get_ethtool_stats,
	.get_sset_count		= atl1_get_sset_count,
	.get_link_ksettings	= atl1_get_link_ksettings,
	.set_link_ksettings	= atl1_set_link_ksettings,
पूर्ण;

module_pci_driver(atl1_driver);

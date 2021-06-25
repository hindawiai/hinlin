<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2010 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2009 Bartlomiej Zolnierkiewicz <bzolnier@gmail.com>
	Copyright (C) 2009 Gertjan van Wingerde <gwingerde@gmail.com>

	Based on the original rt2800pci.c and rt2800usb.c.
	  Copyright (C) 2009 Alban Browaeys <prahal@yahoo.com>
	  Copyright (C) 2009 Felix Fietkau <nbd@खोलोwrt.org>
	  Copyright (C) 2009 Luis Correia <luis.f.correia@gmail.com>
	  Copyright (C) 2009 Mattias Nissler <mattias.nissler@gmx.de>
	  Copyright (C) 2009 Mark Asselstine <asselsm@gmail.com>
	  Copyright (C) 2009 Xose Vazquez Perez <xose.vazquez@gmail.com>
	  <http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2800lib
	Abstract: rt2800 generic device routines.
 */

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "rt2x00.h"
#समावेश "rt2800lib.h"
#समावेश "rt2800.h"

अटल bool modparam_watchकरोg;
module_param_named(watchकरोg, modparam_watchकरोg, bool, S_IRUGO);
MODULE_PARM_DESC(watchकरोg, "Enable watchdog to detect tx/rx hangs and reset hardware if detected");

/*
 * Register access.
 * All access to the CSR रेजिस्टरs will go through the methods
 * rt2800_रेजिस्टर_पढ़ो and rt2800_रेजिस्टर_ग_लिखो.
 * BBP and RF रेजिस्टर require indirect रेजिस्टर access,
 * and use the CSR रेजिस्टरs BBPCSR and RFCSR to achieve this.
 * These indirect रेजिस्टरs work with busy bits,
 * and we will try maximal REGISTER_BUSY_COUNT बार to access
 * the रेजिस्टर जबतक taking a REGISTER_BUSY_DELAY us delay
 * between each attampt. When the busy bit is still set at that समय,
 * the access attempt is considered to have failed,
 * and we will prपूर्णांक an error.
 * The _lock versions must be used अगर you alपढ़ोy hold the csr_mutex
 */
#घोषणा WAIT_FOR_BBP(__dev, __reg) \
	rt2800_regbusy_पढ़ो((__dev), BBP_CSR_CFG, BBP_CSR_CFG_BUSY, (__reg))
#घोषणा WAIT_FOR_RFCSR(__dev, __reg) \
	rt2800_regbusy_पढ़ो((__dev), RF_CSR_CFG, RF_CSR_CFG_BUSY, (__reg))
#घोषणा WAIT_FOR_RFCSR_MT7620(__dev, __reg) \
	rt2800_regbusy_पढ़ो((__dev), RF_CSR_CFG, RF_CSR_CFG_BUSY_MT7620, \
			    (__reg))
#घोषणा WAIT_FOR_RF(__dev, __reg) \
	rt2800_regbusy_पढ़ो((__dev), RF_CSR_CFG0, RF_CSR_CFG0_BUSY, (__reg))
#घोषणा WAIT_FOR_MCU(__dev, __reg) \
	rt2800_regbusy_पढ़ो((__dev), H2M_MAILBOX_CSR, \
			    H2M_MAILBOX_CSR_OWNER, (__reg))

अटल अंतरभूत bool rt2800_is_305x_soc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/* check क्रम rt2872 on SoC */
	अगर (!rt2x00_is_soc(rt2x00dev) ||
	    !rt2x00_rt(rt2x00dev, RT2872))
		वापस false;

	/* we know क्रम sure that these rf chipsets are used on rt305x boards */
	अगर (rt2x00_rf(rt2x00dev, RF3020) ||
	    rt2x00_rf(rt2x00dev, RF3021) ||
	    rt2x00_rf(rt2x00dev, RF3022))
		वापस true;

	rt2x00_warn(rt2x00dev, "Unknown RF chipset on rt305x\n");
	वापस false;
पूर्ण

अटल व्योम rt2800_bbp_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
			     स्थिर अचिन्हित पूर्णांक word, स्थिर u8 value)
अणु
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the BBP becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	अगर (WAIT_FOR_BBP(rt2x00dev, &reg)) अणु
		reg = 0;
		rt2x00_set_field32(&reg, BBP_CSR_CFG_VALUE, value);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_REGNUM, word);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_BUSY, 1);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_READ_CONTROL, 0);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_BBP_RW_MODE, 1);

		rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, BBP_CSR_CFG, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल u8 rt2800_bbp_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev, स्थिर अचिन्हित पूर्णांक word)
अणु
	u32 reg;
	u8 value;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the BBP becomes available, afterwards we
	 * can safely ग_लिखो the पढ़ो request पूर्णांकo the रेजिस्टर.
	 * After the data has been written, we रुको until hardware
	 * वापसs the correct value, अगर at any समय the रेजिस्टर
	 * करोesn't become available in समय, reg will be 0xffffffff
	 * which means we वापस 0xff to the caller.
	 */
	अगर (WAIT_FOR_BBP(rt2x00dev, &reg)) अणु
		reg = 0;
		rt2x00_set_field32(&reg, BBP_CSR_CFG_REGNUM, word);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_BUSY, 1);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_READ_CONTROL, 1);
		rt2x00_set_field32(&reg, BBP_CSR_CFG_BBP_RW_MODE, 1);

		rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, BBP_CSR_CFG, reg);

		WAIT_FOR_BBP(rt2x00dev, &reg);
	पूर्ण

	value = rt2x00_get_field32(reg, BBP_CSR_CFG_VALUE);

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल व्योम rt2800_rfcsr_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर अचिन्हित पूर्णांक word, स्थिर u8 value)
अणु
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RFCSR becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	चयन (rt2x00dev->chip.rt) अणु
	हाल RT6352:
		अगर (WAIT_FOR_RFCSR_MT7620(rt2x00dev, &reg)) अणु
			reg = 0;
			rt2x00_set_field32(&reg, RF_CSR_CFG_DATA_MT7620, value);
			rt2x00_set_field32(&reg, RF_CSR_CFG_REGNUM_MT7620,
					   word);
			rt2x00_set_field32(&reg, RF_CSR_CFG_WRITE_MT7620, 1);
			rt2x00_set_field32(&reg, RF_CSR_CFG_BUSY_MT7620, 1);

			rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, RF_CSR_CFG, reg);
		पूर्ण
		अवरोध;

	शेष:
		अगर (WAIT_FOR_RFCSR(rt2x00dev, &reg)) अणु
			reg = 0;
			rt2x00_set_field32(&reg, RF_CSR_CFG_DATA, value);
			rt2x00_set_field32(&reg, RF_CSR_CFG_REGNUM, word);
			rt2x00_set_field32(&reg, RF_CSR_CFG_WRITE, 1);
			rt2x00_set_field32(&reg, RF_CSR_CFG_BUSY, 1);

			rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, RF_CSR_CFG, reg);
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल व्योम rt2800_rfcsr_ग_लिखो_bank(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u8 bank,
				    स्थिर अचिन्हित पूर्णांक reg, स्थिर u8 value)
अणु
	rt2800_rfcsr_ग_लिखो(rt2x00dev, (reg | (bank << 6)), value);
पूर्ण

अटल व्योम rt2800_rfcsr_ग_लिखो_chanreg(काष्ठा rt2x00_dev *rt2x00dev,
				       स्थिर अचिन्हित पूर्णांक reg, स्थिर u8 value)
अणु
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 4, reg, value);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 6, reg, value);
पूर्ण

अटल व्योम rt2800_rfcsr_ग_लिखो_dccal(काष्ठा rt2x00_dev *rt2x00dev,
				     स्थिर अचिन्हित पूर्णांक reg, स्थिर u8 value)
अणु
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, reg, value);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 7, reg, value);
पूर्ण

अटल u8 rt2800_rfcsr_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			    स्थिर अचिन्हित पूर्णांक word)
अणु
	u32 reg;
	u8 value;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RFCSR becomes available, afterwards we
	 * can safely ग_लिखो the पढ़ो request पूर्णांकo the रेजिस्टर.
	 * After the data has been written, we रुको until hardware
	 * वापसs the correct value, अगर at any समय the रेजिस्टर
	 * करोesn't become available in समय, reg will be 0xffffffff
	 * which means we वापस 0xff to the caller.
	 */
	चयन (rt2x00dev->chip.rt) अणु
	हाल RT6352:
		अगर (WAIT_FOR_RFCSR_MT7620(rt2x00dev, &reg)) अणु
			reg = 0;
			rt2x00_set_field32(&reg, RF_CSR_CFG_REGNUM_MT7620,
					   word);
			rt2x00_set_field32(&reg, RF_CSR_CFG_WRITE_MT7620, 0);
			rt2x00_set_field32(&reg, RF_CSR_CFG_BUSY_MT7620, 1);

			rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, RF_CSR_CFG, reg);

			WAIT_FOR_RFCSR_MT7620(rt2x00dev, &reg);
		पूर्ण

		value = rt2x00_get_field32(reg, RF_CSR_CFG_DATA_MT7620);
		अवरोध;

	शेष:
		अगर (WAIT_FOR_RFCSR(rt2x00dev, &reg)) अणु
			reg = 0;
			rt2x00_set_field32(&reg, RF_CSR_CFG_REGNUM, word);
			rt2x00_set_field32(&reg, RF_CSR_CFG_WRITE, 0);
			rt2x00_set_field32(&reg, RF_CSR_CFG_BUSY, 1);

			rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, RF_CSR_CFG, reg);

			WAIT_FOR_RFCSR(rt2x00dev, &reg);
		पूर्ण

		value = rt2x00_get_field32(reg, RF_CSR_CFG_DATA);
		अवरोध;
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल u8 rt2800_rfcsr_पढ़ो_bank(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u8 bank,
				 स्थिर अचिन्हित पूर्णांक reg)
अणु
	वापस rt2800_rfcsr_पढ़ो(rt2x00dev, (reg | (bank << 6)));
पूर्ण

अटल व्योम rt2800_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
			    स्थिर अचिन्हित पूर्णांक word, स्थिर u32 value)
अणु
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RF becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	अगर (WAIT_FOR_RF(rt2x00dev, &reg)) अणु
		reg = 0;
		rt2x00_set_field32(&reg, RF_CSR_CFG0_REG_VALUE_BW, value);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_STANDBYMODE, 0);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_SEL, 0);
		rt2x00_set_field32(&reg, RF_CSR_CFG0_BUSY, 1);

		rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, RF_CSR_CFG0, reg);
		rt2x00_rf_ग_लिखो(rt2x00dev, word, value);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rt2800_eeprom_map[EEPROM_WORD_COUNT] = अणु
	[EEPROM_CHIP_ID]		= 0x0000,
	[EEPROM_VERSION]		= 0x0001,
	[EEPROM_MAC_ADDR_0]		= 0x0002,
	[EEPROM_MAC_ADDR_1]		= 0x0003,
	[EEPROM_MAC_ADDR_2]		= 0x0004,
	[EEPROM_NIC_CONF0]		= 0x001a,
	[EEPROM_NIC_CONF1]		= 0x001b,
	[EEPROM_FREQ]			= 0x001d,
	[EEPROM_LED_AG_CONF]		= 0x001e,
	[EEPROM_LED_ACT_CONF]		= 0x001f,
	[EEPROM_LED_POLARITY]		= 0x0020,
	[EEPROM_NIC_CONF2]		= 0x0021,
	[EEPROM_LNA]			= 0x0022,
	[EEPROM_RSSI_BG]		= 0x0023,
	[EEPROM_RSSI_BG2]		= 0x0024,
	[EEPROM_TXMIXER_GAIN_BG]	= 0x0024, /* overlaps with RSSI_BG2 */
	[EEPROM_RSSI_A]			= 0x0025,
	[EEPROM_RSSI_A2]		= 0x0026,
	[EEPROM_TXMIXER_GAIN_A]		= 0x0026, /* overlaps with RSSI_A2 */
	[EEPROM_EIRP_MAX_TX_POWER]	= 0x0027,
	[EEPROM_TXPOWER_DELTA]		= 0x0028,
	[EEPROM_TXPOWER_BG1]		= 0x0029,
	[EEPROM_TXPOWER_BG2]		= 0x0030,
	[EEPROM_TSSI_BOUND_BG1]		= 0x0037,
	[EEPROM_TSSI_BOUND_BG2]		= 0x0038,
	[EEPROM_TSSI_BOUND_BG3]		= 0x0039,
	[EEPROM_TSSI_BOUND_BG4]		= 0x003a,
	[EEPROM_TSSI_BOUND_BG5]		= 0x003b,
	[EEPROM_TXPOWER_A1]		= 0x003c,
	[EEPROM_TXPOWER_A2]		= 0x0053,
	[EEPROM_TXPOWER_INIT]		= 0x0068,
	[EEPROM_TSSI_BOUND_A1]		= 0x006a,
	[EEPROM_TSSI_BOUND_A2]		= 0x006b,
	[EEPROM_TSSI_BOUND_A3]		= 0x006c,
	[EEPROM_TSSI_BOUND_A4]		= 0x006d,
	[EEPROM_TSSI_BOUND_A5]		= 0x006e,
	[EEPROM_TXPOWER_BYRATE]		= 0x006f,
	[EEPROM_BBP_START]		= 0x0078,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rt2800_eeprom_map_ext[EEPROM_WORD_COUNT] = अणु
	[EEPROM_CHIP_ID]		= 0x0000,
	[EEPROM_VERSION]		= 0x0001,
	[EEPROM_MAC_ADDR_0]		= 0x0002,
	[EEPROM_MAC_ADDR_1]		= 0x0003,
	[EEPROM_MAC_ADDR_2]		= 0x0004,
	[EEPROM_NIC_CONF0]		= 0x001a,
	[EEPROM_NIC_CONF1]		= 0x001b,
	[EEPROM_NIC_CONF2]		= 0x001c,
	[EEPROM_EIRP_MAX_TX_POWER]	= 0x0020,
	[EEPROM_FREQ]			= 0x0022,
	[EEPROM_LED_AG_CONF]		= 0x0023,
	[EEPROM_LED_ACT_CONF]		= 0x0024,
	[EEPROM_LED_POLARITY]		= 0x0025,
	[EEPROM_LNA]			= 0x0026,
	[EEPROM_EXT_LNA2]		= 0x0027,
	[EEPROM_RSSI_BG]		= 0x0028,
	[EEPROM_RSSI_BG2]		= 0x0029,
	[EEPROM_RSSI_A]			= 0x002a,
	[EEPROM_RSSI_A2]		= 0x002b,
	[EEPROM_TXPOWER_BG1]		= 0x0030,
	[EEPROM_TXPOWER_BG2]		= 0x0037,
	[EEPROM_EXT_TXPOWER_BG3]	= 0x003e,
	[EEPROM_TSSI_BOUND_BG1]		= 0x0045,
	[EEPROM_TSSI_BOUND_BG2]		= 0x0046,
	[EEPROM_TSSI_BOUND_BG3]		= 0x0047,
	[EEPROM_TSSI_BOUND_BG4]		= 0x0048,
	[EEPROM_TSSI_BOUND_BG5]		= 0x0049,
	[EEPROM_TXPOWER_A1]		= 0x004b,
	[EEPROM_TXPOWER_A2]		= 0x0065,
	[EEPROM_EXT_TXPOWER_A3]		= 0x007f,
	[EEPROM_TSSI_BOUND_A1]		= 0x009a,
	[EEPROM_TSSI_BOUND_A2]		= 0x009b,
	[EEPROM_TSSI_BOUND_A3]		= 0x009c,
	[EEPROM_TSSI_BOUND_A4]		= 0x009d,
	[EEPROM_TSSI_BOUND_A5]		= 0x009e,
	[EEPROM_TXPOWER_BYRATE]		= 0x00a0,
पूर्ण;

अटल अचिन्हित पूर्णांक rt2800_eeprom_word_index(काष्ठा rt2x00_dev *rt2x00dev,
					     स्थिर क्रमागत rt2800_eeprom_word word)
अणु
	स्थिर अचिन्हित पूर्णांक *map;
	अचिन्हित पूर्णांक index;

	अगर (WARN_ONCE(word >= EEPROM_WORD_COUNT,
		      "%s: invalid EEPROM word %d\n",
		      wiphy_name(rt2x00dev->hw->wiphy), word))
		वापस 0;

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		map = rt2800_eeprom_map_ext;
	अन्यथा
		map = rt2800_eeprom_map;

	index = map[word];

	/* Index 0 is valid only क्रम EEPROM_CHIP_ID.
	 * Otherwise it means that the offset of the
	 * given word is not initialized in the map,
	 * or that the field is not usable on the
	 * actual chipset.
	 */
	WARN_ONCE(word != EEPROM_CHIP_ID && index == 0,
		  "%s: invalid access of EEPROM word %d\n",
		  wiphy_name(rt2x00dev->hw->wiphy), word);

	वापस index;
पूर्ण

अटल व्योम *rt2800_eeprom_addr(काष्ठा rt2x00_dev *rt2x00dev,
				स्थिर क्रमागत rt2800_eeprom_word word)
अणु
	अचिन्हित पूर्णांक index;

	index = rt2800_eeprom_word_index(rt2x00dev, word);
	वापस rt2x00_eeprom_addr(rt2x00dev, index);
पूर्ण

अटल u16 rt2800_eeprom_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			      स्थिर क्रमागत rt2800_eeprom_word word)
अणु
	अचिन्हित पूर्णांक index;

	index = rt2800_eeprom_word_index(rt2x00dev, word);
	वापस rt2x00_eeprom_पढ़ो(rt2x00dev, index);
पूर्ण

अटल व्योम rt2800_eeprom_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				स्थिर क्रमागत rt2800_eeprom_word word, u16 data)
अणु
	अचिन्हित पूर्णांक index;

	index = rt2800_eeprom_word_index(rt2x00dev, word);
	rt2x00_eeprom_ग_लिखो(rt2x00dev, index, data);
पूर्ण

अटल u16 rt2800_eeprom_पढ़ो_from_array(काष्ठा rt2x00_dev *rt2x00dev,
					 स्थिर क्रमागत rt2800_eeprom_word array,
					 अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक index;

	index = rt2800_eeprom_word_index(rt2x00dev, array);
	वापस rt2x00_eeprom_पढ़ो(rt2x00dev, index + offset);
पूर्ण

अटल पूर्णांक rt2800_enable_wlan_rt3290(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	पूर्णांक i, count;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WLAN_FUN_CTRL);
	rt2x00_set_field32(&reg, WLAN_GPIO_OUT_OE_BIT_ALL, 0xff);
	rt2x00_set_field32(&reg, FRC_WL_ANT_SET, 1);
	rt2x00_set_field32(&reg, WLAN_CLK_EN, 0);
	rt2x00_set_field32(&reg, WLAN_EN, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WLAN_FUN_CTRL, reg);

	udelay(REGISTER_BUSY_DELAY);

	count = 0;
	करो अणु
		/*
		 * Check PLL_LD & XTAL_RDY.
		 */
		क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
			reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CMB_CTRL);
			अगर (rt2x00_get_field32(reg, PLL_LD) &&
			    rt2x00_get_field32(reg, XTAL_RDY))
				अवरोध;
			udelay(REGISTER_BUSY_DELAY);
		पूर्ण

		अगर (i >= REGISTER_BUSY_COUNT) अणु

			अगर (count >= 10)
				वापस -EIO;

			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, 0x58, 0x018);
			udelay(REGISTER_BUSY_DELAY);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, 0x58, 0x418);
			udelay(REGISTER_BUSY_DELAY);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, 0x58, 0x618);
			udelay(REGISTER_BUSY_DELAY);
			count++;
		पूर्ण अन्यथा अणु
			count = 0;
		पूर्ण

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WLAN_FUN_CTRL);
		rt2x00_set_field32(&reg, PCIE_APP0_CLK_REQ, 0);
		rt2x00_set_field32(&reg, WLAN_CLK_EN, 1);
		rt2x00_set_field32(&reg, WLAN_RESET, 1);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WLAN_FUN_CTRL, reg);
		udelay(10);
		rt2x00_set_field32(&reg, WLAN_RESET, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WLAN_FUN_CTRL, reg);
		udelay(10);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, INT_SOURCE_CSR, 0x7fffffff);
	पूर्ण जबतक (count != 0);

	वापस 0;
पूर्ण

व्योम rt2800_mcu_request(काष्ठा rt2x00_dev *rt2x00dev,
			स्थिर u8 command, स्थिर u8 token,
			स्थिर u8 arg0, स्थिर u8 arg1)
अणु
	u32 reg;

	/*
	 * SOC devices करोn't support MCU requests.
	 */
	अगर (rt2x00_is_soc(rt2x00dev))
		वापस;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the MCU becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	अगर (WAIT_FOR_MCU(rt2x00dev, &reg)) अणु
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_OWNER, 1);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_CMD_TOKEN, token);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_ARG0, arg0);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_ARG1, arg1);
		rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, H2M_MAILBOX_CSR, reg);

		reg = 0;
		rt2x00_set_field32(&reg, HOST_CMD_CSR_HOST_COMMAND, command);
		rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, HOST_CMD_CSR, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_mcu_request);

पूर्णांक rt2800_रुको_csr_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i = 0;
	u32 reg;

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
		अगर (reg && reg != ~0)
			वापस 0;
		msleep(1);
	पूर्ण

	rt2x00_err(rt2x00dev, "Unstable hardware\n");
	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_रुको_csr_पढ़ोy);

पूर्णांक rt2800_रुको_wpdma_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	/*
	 * Some devices are really slow to respond here. Wait a whole second
	 * beक्रमe timing out.
	 */
	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WPDMA_GLO_CFG);
		अगर (!rt2x00_get_field32(reg, WPDMA_GLO_CFG_TX_DMA_BUSY) &&
		    !rt2x00_get_field32(reg, WPDMA_GLO_CFG_RX_DMA_BUSY))
			वापस 0;

		msleep(10);
	पूर्ण

	rt2x00_err(rt2x00dev, "WPDMA TX/RX busy [0x%08x]\n", reg);
	वापस -EACCES;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_रुको_wpdma_पढ़ोy);

व्योम rt2800_disable_wpdma(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WPDMA_GLO_CFG);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 0);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_DMA_BUSY, 0);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 0);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_RX_DMA_BUSY, 0);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WPDMA_GLO_CFG, reg);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_disable_wpdma);

व्योम rt2800_get_txwi_rxwi_size(काष्ठा rt2x00_dev *rt2x00dev,
			       अचिन्हित लघु *txwi_size,
			       अचिन्हित लघु *rxwi_size)
अणु
	चयन (rt2x00dev->chip.rt) अणु
	हाल RT3593:
	हाल RT3883:
		*txwi_size = TXWI_DESC_SIZE_4WORDS;
		*rxwi_size = RXWI_DESC_SIZE_5WORDS;
		अवरोध;

	हाल RT5592:
	हाल RT6352:
		*txwi_size = TXWI_DESC_SIZE_5WORDS;
		*rxwi_size = RXWI_DESC_SIZE_6WORDS;
		अवरोध;

	शेष:
		*txwi_size = TXWI_DESC_SIZE_4WORDS;
		*rxwi_size = RXWI_DESC_SIZE_4WORDS;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_get_txwi_rxwi_size);

अटल bool rt2800_check_firmware_crc(स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	u16 fw_crc;
	u16 crc;

	/*
	 * The last 2 bytes in the firmware array are the crc checksum itself,
	 * this means that we should never pass those 2 bytes to the crc
	 * algorithm.
	 */
	fw_crc = (data[len - 2] << 8 | data[len - 1]);

	/*
	 * Use the crc ccitt algorithm.
	 * This will वापस the same value as the legacy driver which
	 * used bit ordering reversion on the both the firmware bytes
	 * beक्रमe input input as well as on the final output.
	 * Obviously using crc ccitt directly is much more efficient.
	 */
	crc = crc_ccitt(~0, data, len - 2);

	/*
	 * There is a small dअगरference between the crc-itu-t + bitrev and
	 * the crc-ccitt crc calculation. In the latter method the 2 bytes
	 * will be swapped, use swab16 to convert the crc to the correct
	 * value.
	 */
	crc = swab16(crc);

	वापस fw_crc == crc;
पूर्ण

पूर्णांक rt2800_check_firmware(काष्ठा rt2x00_dev *rt2x00dev,
			  स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	माप_प्रकार offset = 0;
	माप_प्रकार fw_len;
	bool multiple;

	/*
	 * PCI(e) & SOC devices require firmware with a length
	 * of 8kb. USB devices require firmware files with a length
	 * of 4kb. Certain USB chipsets however require dअगरferent firmware,
	 * which Ralink only provides attached to the original firmware
	 * file. Thus क्रम USB devices, firmware files have a length
	 * which is a multiple of 4kb. The firmware क्रम rt3290 chip also
	 * have a length which is a multiple of 4kb.
	 */
	अगर (rt2x00_is_usb(rt2x00dev) || rt2x00_rt(rt2x00dev, RT3290))
		fw_len = 4096;
	अन्यथा
		fw_len = 8192;

	multiple = true;
	/*
	 * Validate the firmware length
	 */
	अगर (len != fw_len && (!multiple || (len % fw_len) != 0))
		वापस FW_BAD_LENGTH;

	/*
	 * Check अगर the chipset requires one of the upper parts
	 * of the firmware.
	 */
	अगर (rt2x00_is_usb(rt2x00dev) &&
	    !rt2x00_rt(rt2x00dev, RT2860) &&
	    !rt2x00_rt(rt2x00dev, RT2872) &&
	    !rt2x00_rt(rt2x00dev, RT3070) &&
	    ((len / fw_len) == 1))
		वापस FW_BAD_VERSION;

	/*
	 * 8kb firmware files must be checked as अगर it were
	 * 2 separate firmware files.
	 */
	जबतक (offset < len) अणु
		अगर (!rt2800_check_firmware_crc(data + offset, fw_len))
			वापस FW_BAD_CRC;

		offset += fw_len;
	पूर्ण

	वापस FW_OK;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_check_firmware);

पूर्णांक rt2800_load_firmware(काष्ठा rt2x00_dev *rt2x00dev,
			 स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;
	पूर्णांक retval;

	अगर (rt2x00_rt(rt2x00dev, RT3290)) अणु
		retval = rt2800_enable_wlan_rt3290(rt2x00dev);
		अगर (retval)
			वापस -EBUSY;
	पूर्ण

	/*
	 * If driver करोesn't wake up firmware here,
	 * rt2800_load_firmware will hang क्रमever when पूर्णांकerface is up again.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTOWAKEUP_CFG, 0x00000000);

	/*
	 * Wait क्रम stable hardware.
	 */
	अगर (rt2800_रुको_csr_पढ़ोy(rt2x00dev))
		वापस -EBUSY;

	अगर (rt2x00_is_pci(rt2x00dev)) अणु
		अगर (rt2x00_rt(rt2x00dev, RT3290) ||
		    rt2x00_rt(rt2x00dev, RT3572) ||
		    rt2x00_rt(rt2x00dev, RT5390) ||
		    rt2x00_rt(rt2x00dev, RT5392)) अणु
			reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AUX_CTRL);
			rt2x00_set_field32(&reg, AUX_CTRL_FORCE_PCIE_CLK, 1);
			rt2x00_set_field32(&reg, AUX_CTRL_WAKE_PCIE_EN, 1);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUX_CTRL, reg);
		पूर्ण
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, PWR_PIN_CFG, 0x00000002);
	पूर्ण

	rt2800_disable_wpdma(rt2x00dev);

	/*
	 * Write firmware to the device.
	 */
	rt2800_drv_ग_लिखो_firmware(rt2x00dev, data, len);

	/*
	 * Wait क्रम device to stabilize.
	 */
	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, PBF_SYS_CTRL);
		अगर (rt2x00_get_field32(reg, PBF_SYS_CTRL_READY))
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == REGISTER_BUSY_COUNT) अणु
		rt2x00_err(rt2x00dev, "PBF system register not ready\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Disable DMA, will be reenabled later when enabling
	 * the radio.
	 */
	rt2800_disable_wpdma(rt2x00dev);

	/*
	 * Initialize firmware.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);
	अगर (rt2x00_is_usb(rt2x00dev)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_INT_SRC, 0);
		rt2800_mcu_request(rt2x00dev, MCU_BOOT_SIGNAL, 0, 0, 0);
	पूर्ण
	msleep(1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_load_firmware);

व्योम rt2800_ग_लिखो_tx_data(काष्ठा queue_entry *entry,
			  काष्ठा txentry_desc *txdesc)
अणु
	__le32 *txwi = rt2800_drv_get_txwi(entry);
	u32 word;
	पूर्णांक i;

	/*
	 * Initialize TX Info descriptor
	 */
	word = rt2x00_desc_पढ़ो(txwi, 0);
	rt2x00_set_field32(&word, TXWI_W0_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_MIMO_PS,
			   test_bit(ENTRY_TXD_HT_MIMO_PS, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_CF_ACK, 0);
	rt2x00_set_field32(&word, TXWI_W0_TS,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_AMPDU,
			   test_bit(ENTRY_TXD_HT_AMPDU, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_MPDU_DENSITY,
			   txdesc->u.ht.mpdu_density);
	rt2x00_set_field32(&word, TXWI_W0_TX_OP, txdesc->u.ht.txop);
	rt2x00_set_field32(&word, TXWI_W0_MCS, txdesc->u.ht.mcs);
	rt2x00_set_field32(&word, TXWI_W0_BW,
			   test_bit(ENTRY_TXD_HT_BW_40, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_SHORT_GI,
			   test_bit(ENTRY_TXD_HT_SHORT_GI, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W0_STBC, txdesc->u.ht.stbc);
	rt2x00_set_field32(&word, TXWI_W0_PHYMODE, txdesc->rate_mode);
	rt2x00_desc_ग_लिखो(txwi, 0, word);

	word = rt2x00_desc_पढ़ो(txwi, 1);
	rt2x00_set_field32(&word, TXWI_W1_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W1_NSEQ,
			   test_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags));
	rt2x00_set_field32(&word, TXWI_W1_BW_WIN_SIZE, txdesc->u.ht.ba_size);
	rt2x00_set_field32(&word, TXWI_W1_WIRELESS_CLI_ID,
			   test_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags) ?
			   txdesc->key_idx : txdesc->u.ht.wcid);
	rt2x00_set_field32(&word, TXWI_W1_MPDU_TOTAL_BYTE_COUNT,
			   txdesc->length);
	rt2x00_set_field32(&word, TXWI_W1_PACKETID_QUEUE, entry->queue->qid);
	rt2x00_set_field32(&word, TXWI_W1_PACKETID_ENTRY, (entry->entry_idx % 3) + 1);
	rt2x00_desc_ग_लिखो(txwi, 1, word);

	/*
	 * Always ग_लिखो 0 to IV/EIV fields (word 2 and 3), hardware will insert
	 * the IV from the IVEIV रेजिस्टर when TXD_W3_WIV is set to 0.
	 * When TXD_W3_WIV is set to 1 it will use the IV data
	 * from the descriptor. The TXWI_W1_WIRELESS_CLI_ID indicates which
	 * crypto entry in the रेजिस्टरs should be used to encrypt the frame.
	 *
	 * Nulअगरy all reमुख्यing words as well, we करोn't know how to program them.
	 */
	क्रम (i = 2; i < entry->queue->winfo_size / माप(__le32); i++)
		_rt2x00_desc_ग_लिखो(txwi, i, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_ग_लिखो_tx_data);

अटल पूर्णांक rt2800_agc_to_rssi(काष्ठा rt2x00_dev *rt2x00dev, u32 rxwi_w2)
अणु
	s8 rssi0 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI0);
	s8 rssi1 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI1);
	s8 rssi2 = rt2x00_get_field32(rxwi_w2, RXWI_W2_RSSI2);
	u16 eeprom;
	u8 offset0;
	u8 offset1;
	u8 offset2;

	अगर (rt2x00dev->curr_band == NL80211_BAND_2GHZ) अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_BG);
		offset0 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG_OFFSET0);
		offset1 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG_OFFSET1);
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_BG2);
		offset2 = rt2x00_get_field16(eeprom, EEPROM_RSSI_BG2_OFFSET2);
	पूर्ण अन्यथा अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_A);
		offset0 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A_OFFSET0);
		offset1 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A_OFFSET1);
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_A2);
		offset2 = rt2x00_get_field16(eeprom, EEPROM_RSSI_A2_OFFSET2);
	पूर्ण

	/*
	 * Convert the value from the descriptor पूर्णांकo the RSSI value
	 * If the value in the descriptor is 0, it is considered invalid
	 * and the शेष (extremely low) rssi value is assumed
	 */
	rssi0 = (rssi0) ? (-12 - offset0 - rt2x00dev->lna_gain - rssi0) : -128;
	rssi1 = (rssi1) ? (-12 - offset1 - rt2x00dev->lna_gain - rssi1) : -128;
	rssi2 = (rssi2) ? (-12 - offset2 - rt2x00dev->lna_gain - rssi2) : -128;

	/*
	 * mac80211 only accepts a single RSSI value. Calculating the
	 * average करोesn't deliver a fair answer either since -60:-60 would
	 * be considered equally good as -50:-70 जबतक the second is the one
	 * which gives less energy...
	 */
	rssi0 = max(rssi0, rssi1);
	वापस (पूर्णांक)max(rssi0, rssi2);
पूर्ण

व्योम rt2800_process_rxwi(काष्ठा queue_entry *entry,
			 काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	__le32 *rxwi = (__le32 *) entry->skb->data;
	u32 word;

	word = rt2x00_desc_पढ़ो(rxwi, 0);

	rxdesc->cipher = rt2x00_get_field32(word, RXWI_W0_UDF);
	rxdesc->size = rt2x00_get_field32(word, RXWI_W0_MPDU_TOTAL_BYTE_COUNT);

	word = rt2x00_desc_पढ़ो(rxwi, 1);

	अगर (rt2x00_get_field32(word, RXWI_W1_SHORT_GI))
		rxdesc->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (rt2x00_get_field32(word, RXWI_W1_BW))
		rxdesc->bw = RATE_INFO_BW_40;

	/*
	 * Detect RX rate, always use MCS as संकेत type.
	 */
	rxdesc->dev_flags |= RXDONE_SIGNAL_MCS;
	rxdesc->संकेत = rt2x00_get_field32(word, RXWI_W1_MCS);
	rxdesc->rate_mode = rt2x00_get_field32(word, RXWI_W1_PHYMODE);

	/*
	 * Mask of 0x8 bit to हटाओ the लघु preamble flag.
	 */
	अगर (rxdesc->rate_mode == RATE_MODE_CCK)
		rxdesc->संकेत &= ~0x8;

	word = rt2x00_desc_पढ़ो(rxwi, 2);

	/*
	 * Convert descriptor AGC value to RSSI value.
	 */
	rxdesc->rssi = rt2800_agc_to_rssi(entry->queue->rt2x00dev, word);
	/*
	 * Remove RXWI descriptor from start of the buffer.
	 */
	skb_pull(entry->skb, entry->queue->winfo_size);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_process_rxwi);

अटल व्योम rt2800_rate_from_status(काष्ठा skb_frame_desc *skbdesc,
				    u32 status, क्रमागत nl80211_band band)
अणु
	u8 flags = 0;
	u8 idx = rt2x00_get_field32(status, TX_STA_FIFO_MCS);

	चयन (rt2x00_get_field32(status, TX_STA_FIFO_PHYMODE)) अणु
	हाल RATE_MODE_HT_GREENFIELD:
		flags |= IEEE80211_TX_RC_GREEN_FIELD;
		fallthrough;
	हाल RATE_MODE_HT_MIX:
		flags |= IEEE80211_TX_RC_MCS;
		अवरोध;
	हाल RATE_MODE_OFDM:
		अगर (band == NL80211_BAND_2GHZ)
			idx += 4;
		अवरोध;
	हाल RATE_MODE_CCK:
		अगर (idx >= 8)
			idx -= 8;
		अवरोध;
	पूर्ण

	अगर (rt2x00_get_field32(status, TX_STA_FIFO_BW))
		flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

	अगर (rt2x00_get_field32(status, TX_STA_FIFO_SGI))
		flags |= IEEE80211_TX_RC_SHORT_GI;

	skbdesc->tx_rate_idx = idx;
	skbdesc->tx_rate_flags = flags;
पूर्ण

अटल bool rt2800_txकरोne_entry_check(काष्ठा queue_entry *entry, u32 reg)
अणु
	__le32 *txwi;
	u32 word;
	पूर्णांक wcid, ack, pid;
	पूर्णांक tx_wcid, tx_ack, tx_pid, is_agg;

	/*
	 * This frames has वापसed with an IO error,
	 * so the status report is not पूर्णांकended क्रम this
	 * frame.
	 */
	अगर (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		वापस false;

	wcid	= rt2x00_get_field32(reg, TX_STA_FIFO_WCID);
	ack	= rt2x00_get_field32(reg, TX_STA_FIFO_TX_ACK_REQUIRED);
	pid	= rt2x00_get_field32(reg, TX_STA_FIFO_PID_TYPE);
	is_agg	= rt2x00_get_field32(reg, TX_STA_FIFO_TX_AGGRE);

	/*
	 * Validate अगर this TX status report is पूर्णांकended क्रम
	 * this entry by comparing the WCID/ACK/PID fields.
	 */
	txwi = rt2800_drv_get_txwi(entry);

	word = rt2x00_desc_पढ़ो(txwi, 1);
	tx_wcid = rt2x00_get_field32(word, TXWI_W1_WIRELESS_CLI_ID);
	tx_ack  = rt2x00_get_field32(word, TXWI_W1_ACK);
	tx_pid  = rt2x00_get_field32(word, TXWI_W1_PACKETID);

	अगर (wcid != tx_wcid || ack != tx_ack || (!is_agg && pid != tx_pid)) अणु
		rt2x00_dbg(entry->queue->rt2x00dev,
			   "TX status report missed for queue %d entry %d\n",
			   entry->queue->qid, entry->entry_idx);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम rt2800_txकरोne_entry(काष्ठा queue_entry *entry, u32 status, __le32 *txwi,
			 bool match)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	काष्ठा txकरोne_entry_desc txdesc;
	u32 word;
	u16 mcs, real_mcs;
	पूर्णांक aggr, ampdu, wcid, ack_req;

	/*
	 * Obtain the status about this packet.
	 */
	txdesc.flags = 0;
	word = rt2x00_desc_पढ़ो(txwi, 0);

	mcs = rt2x00_get_field32(word, TXWI_W0_MCS);
	ampdu = rt2x00_get_field32(word, TXWI_W0_AMPDU);

	real_mcs = rt2x00_get_field32(status, TX_STA_FIFO_MCS);
	aggr = rt2x00_get_field32(status, TX_STA_FIFO_TX_AGGRE);
	wcid = rt2x00_get_field32(status, TX_STA_FIFO_WCID);
	ack_req	= rt2x00_get_field32(status, TX_STA_FIFO_TX_ACK_REQUIRED);

	/*
	 * If a frame was meant to be sent as a single non-aggregated MPDU
	 * but ended up in an aggregate the used tx rate करोesn't correlate
	 * with the one specअगरied in the TXWI as the whole aggregate is sent
	 * with the same rate.
	 *
	 * For example: two frames are sent to rt2x00, the first one sets
	 * AMPDU=1 and requests MCS7 whereas the second frame sets AMDPU=0
	 * and requests MCS15. If the hw aggregates both frames पूर्णांकo one
	 * AMDPU the tx status क्रम both frames will contain MCS7 although
	 * the frame was sent successfully.
	 *
	 * Hence, replace the requested rate with the real tx rate to not
	 * confuse the rate control algortihm by providing clearly wrong
	 * data.
	 *
	 * FIXME: अगर we करो not find matching entry, we tell that frame was
	 * posted without any retries. We need to find a way to fix that
	 * and provide retry count.
 	 */
	अगर (unlikely((aggr == 1 && ampdu == 0 && real_mcs != mcs)) || !match) अणु
		rt2800_rate_from_status(skbdesc, status, rt2x00dev->curr_band);
		mcs = real_mcs;
	पूर्ण

	अगर (aggr == 1 || ampdu == 1)
		__set_bit(TXDONE_AMPDU, &txdesc.flags);

	अगर (!ack_req)
		__set_bit(TXDONE_NO_ACK_REQ, &txdesc.flags);

	/*
	 * Ralink has a retry mechanism using a global fallback
	 * table. We setup this fallback table to try the immediate
	 * lower rate क्रम all rates. In the TX_STA_FIFO, the MCS field
	 * always contains the MCS used क्रम the last transmission, be
	 * it successful or not.
	 */
	अगर (rt2x00_get_field32(status, TX_STA_FIFO_TX_SUCCESS)) अणु
		/*
		 * Transmission succeeded. The number of retries is
		 * mcs - real_mcs
		 */
		__set_bit(TXDONE_SUCCESS, &txdesc.flags);
		txdesc.retry = ((mcs > real_mcs) ? mcs - real_mcs : 0);
	पूर्ण अन्यथा अणु
		/*
		 * Transmission failed. The number of retries is
		 * always 7 in this हाल (क्रम a total number of 8
		 * frames sent).
		 */
		__set_bit(TXDONE_FAILURE, &txdesc.flags);
		txdesc.retry = rt2x00dev->दीर्घ_retry;
	पूर्ण

	/*
	 * the frame was retried at least once
	 * -> hw used fallback rates
	 */
	अगर (txdesc.retry)
		__set_bit(TXDONE_FALLBACK, &txdesc.flags);

	अगर (!match) अणु
		/* RCU assures non-null sta will not be मुक्तd by mac80211. */
		rcu_पढ़ो_lock();
		अगर (likely(wcid >= WCID_START && wcid <= WCID_END))
			skbdesc->sta = drv_data->wcid_to_sta[wcid - WCID_START];
		अन्यथा
			skbdesc->sta = शून्य;
		rt2x00lib_txकरोne_nomatch(entry, &txdesc);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		rt2x00lib_txकरोne(entry, &txdesc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_txकरोne_entry);

व्योम rt2800_txकरोne(काष्ठा rt2x00_dev *rt2x00dev, अचिन्हित पूर्णांक quota)
अणु
	काष्ठा data_queue *queue;
	काष्ठा queue_entry *entry;
	u32 reg;
	u8 qid;
	bool match;

	जबतक (quota-- > 0 && kfअगरo_get(&rt2x00dev->txstatus_fअगरo, &reg)) अणु
		/*
		 * TX_STA_FIFO_PID_QUEUE is a 2-bit field, thus qid is
		 * guaranteed to be one of the TX QIDs .
		 */
		qid = rt2x00_get_field32(reg, TX_STA_FIFO_PID_QUEUE);
		queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);

		अगर (unlikely(rt2x00queue_empty(queue))) अणु
			rt2x00_dbg(rt2x00dev, "Got TX status for an empty queue %u, dropping\n",
				   qid);
			अवरोध;
		पूर्ण

		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);

		अगर (unlikely(test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
			     !test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))) अणु
			rt2x00_warn(rt2x00dev, "Data pending for entry %u in queue %u\n",
				    entry->entry_idx, qid);
			अवरोध;
		पूर्ण

		match = rt2800_txकरोne_entry_check(entry, reg);
		rt2800_txकरोne_entry(entry, reg, rt2800_drv_get_txwi(entry), match);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_txकरोne);

अटल अंतरभूत bool rt2800_entry_txstatus_समयout(काष्ठा rt2x00_dev *rt2x00dev,
						 काष्ठा queue_entry *entry)
अणु
	bool ret;
	अचिन्हित दीर्घ tout;

	अगर (!test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
		वापस false;

	अगर (test_bit(DEVICE_STATE_FLUSHING, &rt2x00dev->flags))
		tout = msecs_to_jअगरfies(50);
	अन्यथा
		tout = msecs_to_jअगरfies(2000);

	ret = समय_after(jअगरfies, entry->last_action + tout);
	अगर (unlikely(ret))
		rt2x00_dbg(entry->queue->rt2x00dev,
			   "TX status timeout for entry %d in queue %d\n",
			   entry->entry_idx, entry->queue->qid);
	वापस ret;
पूर्ण

bool rt2800_txstatus_समयout(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	काष्ठा queue_entry *entry;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		अगर (rt2800_entry_txstatus_समयout(rt2x00dev, entry))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_txstatus_समयout);

/*
 * test अगर there is an entry in any TX queue क्रम which DMA is करोne
 * but the TX status has not been वापसed yet
 */
bool rt2800_txstatus_pending(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		अगर (rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE) !=
		    rt2x00queue_get_entry(queue, Q_INDEX_DONE))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_txstatus_pending);

व्योम rt2800_txकरोne_nostatus(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	काष्ठा queue_entry *entry;

	/*
	 * Process any trailing TX status reports क्रम IO failures,
	 * we loop until we find the first non-IO error entry. This
	 * can either be a frame which is मुक्त, is being uploaded,
	 * or has completed the upload but didn't have an entry
	 * in the TX_STAT_FIFO रेजिस्टर yet.
	 */
	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		जबतक (!rt2x00queue_empty(queue)) अणु
			entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);

			अगर (test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
			    !test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
				अवरोध;

			अगर (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags) ||
			    rt2800_entry_txstatus_समयout(rt2x00dev, entry))
				rt2x00lib_txकरोne_noinfo(entry, TXDONE_FAILURE);
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_txकरोne_nostatus);

अटल पूर्णांक rt2800_check_hung(काष्ठा data_queue *queue)
अणु
	अचिन्हित पूर्णांक cur_idx = rt2800_drv_get_dma_करोne(queue);

	अगर (queue->wd_idx != cur_idx)
		queue->wd_count = 0;
	अन्यथा
		queue->wd_count++;

	वापस queue->wd_count > 16;
पूर्ण

अटल व्योम rt2800_update_survey(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा ieee80211_channel *chan = rt2x00dev->hw->conf.chandef.chan;
	काष्ठा rt2x00_chan_survey *chan_survey =
		   &rt2x00dev->chan_survey[chan->hw_value];

	chan_survey->समय_idle += rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_IDLE_STA);
	chan_survey->समय_busy += rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_BUSY_STA);
	chan_survey->समय_ext_busy += rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_BUSY_STA_SEC);
पूर्ण

व्योम rt2800_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	bool hung_tx = false;
	bool hung_rx = false;

	अगर (test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags))
		वापस;

	rt2800_update_survey(rt2x00dev);

	queue_क्रम_each(rt2x00dev, queue) अणु
		चयन (queue->qid) अणु
		हाल QID_AC_VO:
		हाल QID_AC_VI:
		हाल QID_AC_BE:
		हाल QID_AC_BK:
		हाल QID_MGMT:
			अगर (rt2x00queue_empty(queue))
				जारी;
			hung_tx = rt2800_check_hung(queue);
			अवरोध;
		हाल QID_RX:
			/* For station mode we should reactive at least
			 * beacons. TODO: need to find good way detect
			 * RX hung क्रम AP mode.
			 */
			अगर (rt2x00dev->पूर्णांकf_sta_count == 0)
				जारी;
			hung_rx = rt2800_check_hung(queue);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (hung_tx)
		rt2x00_warn(rt2x00dev, "Watchdog TX hung detected\n");

	अगर (hung_rx)
		rt2x00_warn(rt2x00dev, "Watchdog RX hung detected\n");

	अगर (hung_tx || hung_rx)
		ieee80211_restart_hw(rt2x00dev->hw);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_watchकरोg);

अटल अचिन्हित पूर्णांक rt2800_hw_beacon_base(काष्ठा rt2x00_dev *rt2x00dev,
					  अचिन्हित पूर्णांक index)
अणु
	वापस HW_BEACON_BASE(index);
पूर्ण

अटल अंतरभूत u8 rt2800_get_beacon_offset(काष्ठा rt2x00_dev *rt2x00dev,
					  अचिन्हित पूर्णांक index)
अणु
	वापस BEACON_BASE_TO_OFFSET(rt2800_hw_beacon_base(rt2x00dev, index));
पूर्ण

अटल व्योम rt2800_update_beacons_setup(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue = rt2x00dev->bcn;
	काष्ठा queue_entry *entry;
	पूर्णांक i, bcn_num = 0;
	u64 off, reg = 0;
	u32 bssid_dw1;

	/*
	 * Setup offsets of all active beacons in BCN_OFFSETअणु0,1पूर्ण रेजिस्टरs.
	 */
	क्रम (i = 0; i < queue->limit; i++) अणु
		entry = &queue->entries[i];
		अगर (!test_bit(ENTRY_BCN_ENABLED, &entry->flags))
			जारी;
		off = rt2800_get_beacon_offset(rt2x00dev, entry->entry_idx);
		reg |= off << (8 * bcn_num);
		bcn_num++;
	पूर्ण

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_OFFSET0, (u32) reg);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_OFFSET1, (u32) (reg >> 32));

	/*
	 * H/W sends up to MAC_BSSID_DW1_BSS_BCN_NUM + 1 consecutive beacons.
	 */
	bssid_dw1 = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_BSSID_DW1);
	rt2x00_set_field32(&bssid_dw1, MAC_BSSID_DW1_BSS_BCN_NUM,
			   bcn_num > 0 ? bcn_num - 1 : 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_BSSID_DW1, bssid_dw1);
पूर्ण

व्योम rt2800_ग_लिखो_beacon(काष्ठा queue_entry *entry, काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	अचिन्हित पूर्णांक beacon_base;
	अचिन्हित पूर्णांक padding_len;
	u32 orig_reg, reg;
	स्थिर पूर्णांक txwi_desc_size = entry->queue->winfo_size;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
	orig_reg = reg;
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

	/*
	 * Add space क्रम the TXWI in front of the skb.
	 */
	स_रखो(skb_push(entry->skb, txwi_desc_size), 0, txwi_desc_size);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->flags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = entry->skb->data;
	skbdesc->desc_len = txwi_desc_size;

	/*
	 * Add the TXWI क्रम the beacon to the skb.
	 */
	rt2800_ग_लिखो_tx_data(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry);

	/*
	 * Write entire beacon with TXWI and padding to रेजिस्टर.
	 */
	padding_len = roundup(entry->skb->len, 4) - entry->skb->len;
	अगर (padding_len && skb_pad(entry->skb, padding_len)) अणु
		rt2x00_err(rt2x00dev, "Failure padding beacon, aborting\n");
		/* skb मुक्तd by skb_pad() on failure */
		entry->skb = शून्य;
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, orig_reg);
		वापस;
	पूर्ण

	beacon_base = rt2800_hw_beacon_base(rt2x00dev, entry->entry_idx);

	rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, beacon_base, entry->skb->data,
				   entry->skb->len + padding_len);
	__set_bit(ENTRY_BCN_ENABLED, &entry->flags);

	/*
	 * Change global beacons settings.
	 */
	rt2800_update_beacons_setup(rt2x00dev);

	/*
	 * Restore beaconing state.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, orig_reg);

	/*
	 * Clean up beacon skb.
	 */
	dev_kमुक्त_skb_any(entry->skb);
	entry->skb = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_ग_लिखो_beacon);

अटल अंतरभूत व्योम rt2800_clear_beacon_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev,
						अचिन्हित पूर्णांक index)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक txwi_desc_size = rt2x00dev->bcn->winfo_size;
	अचिन्हित पूर्णांक beacon_base;

	beacon_base = rt2800_hw_beacon_base(rt2x00dev, index);

	/*
	 * For the Beacon base रेजिस्टरs we only need to clear
	 * the whole TXWI which (when set to 0) will invalidate
	 * the entire beacon.
	 */
	क्रम (i = 0; i < txwi_desc_size; i += माप(__le32))
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, beacon_base + i, 0);
पूर्ण

व्योम rt2800_clear_beacon(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	orig_reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
	reg = orig_reg;
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

	/*
	 * Clear beacon.
	 */
	rt2800_clear_beacon_रेजिस्टर(rt2x00dev, entry->entry_idx);
	__clear_bit(ENTRY_BCN_ENABLED, &entry->flags);

	/*
	 * Change global beacons settings.
	 */
	rt2800_update_beacons_setup(rt2x00dev);
	/*
	 * Restore beaconing state.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, orig_reg);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_clear_beacon);

#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
स्थिर काष्ठा rt2x00debug rt2800_rt2x00debug = अणु
	.owner	= THIS_MODULE,
	.csr	= अणु
		.पढ़ो		= rt2800_रेजिस्टर_पढ़ो,
		.ग_लिखो		= rt2800_रेजिस्टर_ग_लिखो,
		.flags		= RT2X00DEBUGFS_OFFSET,
		.word_base	= CSR_REG_BASE,
		.word_size	= माप(u32),
		.word_count	= CSR_REG_SIZE / माप(u32),
	पूर्ण,
	.eeprom	= अणु
		/* NOTE: The local EEPROM access functions can't
		 * be used here, use the generic versions instead.
		 */
		.पढ़ो		= rt2x00_eeprom_पढ़ो,
		.ग_लिखो		= rt2x00_eeprom_ग_लिखो,
		.word_base	= EEPROM_BASE,
		.word_size	= माप(u16),
		.word_count	= EEPROM_SIZE / माप(u16),
	पूर्ण,
	.bbp	= अणु
		.पढ़ो		= rt2800_bbp_पढ़ो,
		.ग_लिखो		= rt2800_bbp_ग_लिखो,
		.word_base	= BBP_BASE,
		.word_size	= माप(u8),
		.word_count	= BBP_SIZE / माप(u8),
	पूर्ण,
	.rf	= अणु
		.पढ़ो		= rt2x00_rf_पढ़ो,
		.ग_लिखो		= rt2800_rf_ग_लिखो,
		.word_base	= RF_BASE,
		.word_size	= माप(u32),
		.word_count	= RF_SIZE / माप(u32),
	पूर्ण,
	.rfcsr	= अणु
		.पढ़ो		= rt2800_rfcsr_पढ़ो,
		.ग_लिखो		= rt2800_rfcsr_ग_लिखो,
		.word_base	= RFCSR_BASE,
		.word_size	= माप(u8),
		.word_count	= RFCSR_SIZE / माप(u8),
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(rt2800_rt2x00debug);
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

पूर्णांक rt2800_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	अगर (rt2x00_rt(rt2x00dev, RT3290)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WLAN_FUN_CTRL);
		वापस rt2x00_get_field32(reg, WLAN_GPIO_IN_BIT0);
	पूर्ण अन्यथा अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);
		वापस rt2x00_get_field32(reg, GPIO_CTRL_VAL2);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_rfसमाप्त_poll);

#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
अटल व्योम rt2800_brightness_set(काष्ठा led_classdev *led_cdev,
				  क्रमागत led_brightness brightness)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	अचिन्हित पूर्णांक enabled = brightness != LED_OFF;
	अचिन्हित पूर्णांक bg_mode =
	    (enabled && led->rt2x00dev->curr_band == NL80211_BAND_2GHZ);
	अचिन्हित पूर्णांक polarity =
		rt2x00_get_field16(led->rt2x00dev->led_mcu_reg,
				   EEPROM_FREQ_LED_POLARITY);
	अचिन्हित पूर्णांक ledmode =
		rt2x00_get_field16(led->rt2x00dev->led_mcu_reg,
				   EEPROM_FREQ_LED_MODE);
	u32 reg;

	/* Check क्रम SoC (SOC devices करोn't support MCU requests) */
	अगर (rt2x00_is_soc(led->rt2x00dev)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(led->rt2x00dev, LED_CFG);

		/* Set LED Polarity */
		rt2x00_set_field32(&reg, LED_CFG_LED_POLAR, polarity);

		/* Set LED Mode */
		अगर (led->type == LED_TYPE_RADIO) अणु
			rt2x00_set_field32(&reg, LED_CFG_G_LED_MODE,
					   enabled ? 3 : 0);
		पूर्ण अन्यथा अगर (led->type == LED_TYPE_ASSOC) अणु
			rt2x00_set_field32(&reg, LED_CFG_Y_LED_MODE,
					   enabled ? 3 : 0);
		पूर्ण अन्यथा अगर (led->type == LED_TYPE_QUALITY) अणु
			rt2x00_set_field32(&reg, LED_CFG_R_LED_MODE,
					   enabled ? 3 : 0);
		पूर्ण

		rt2800_रेजिस्टर_ग_लिखो(led->rt2x00dev, LED_CFG, reg);

	पूर्ण अन्यथा अणु
		अगर (led->type == LED_TYPE_RADIO) अणु
			rt2800_mcu_request(led->rt2x00dev, MCU_LED, 0xff, ledmode,
					      enabled ? 0x20 : 0);
		पूर्ण अन्यथा अगर (led->type == LED_TYPE_ASSOC) अणु
			rt2800_mcu_request(led->rt2x00dev, MCU_LED, 0xff, ledmode,
					      enabled ? (bg_mode ? 0x60 : 0xa0) : 0x20);
		पूर्ण अन्यथा अगर (led->type == LED_TYPE_QUALITY) अणु
			/*
			 * The brightness is भागided पूर्णांकo 6 levels (0 - 5),
			 * The specs tell us the following levels:
			 *	0, 1 ,3, 7, 15, 31
			 * to determine the level in a simple way we can simply
			 * work with bitshअगरting:
			 *	(1 << level) - 1
			 */
			rt2800_mcu_request(led->rt2x00dev, MCU_LED_STRENGTH, 0xff,
					      (1 << brightness / (LED_FULL / 6)) - 1,
					      polarity);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rt2800_init_led(काष्ठा rt2x00_dev *rt2x00dev,
		     काष्ठा rt2x00_led *led, क्रमागत led_type type)
अणु
	led->rt2x00dev = rt2x00dev;
	led->type = type;
	led->led_dev.brightness_set = rt2800_brightness_set;
	led->flags = LED_INITIALIZED;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

/*
 * Configuration handlers.
 */
अटल व्योम rt2800_config_wcid(काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर u8 *address,
			       पूर्णांक wcid)
अणु
	काष्ठा mac_wcid_entry wcid_entry;
	u32 offset;

	offset = MAC_WCID_ENTRY(wcid);

	स_रखो(&wcid_entry, 0xff, माप(wcid_entry));
	अगर (address)
		स_नकल(wcid_entry.mac, address, ETH_ALEN);

	rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, offset,
				      &wcid_entry, माप(wcid_entry));
पूर्ण

अटल व्योम rt2800_delete_wcid_attr(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक wcid)
अणु
	u32 offset;
	offset = MAC_WCID_ATTR_ENTRY(wcid);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, 0);
पूर्ण

अटल व्योम rt2800_config_wcid_attr_bssidx(काष्ठा rt2x00_dev *rt2x00dev,
					   पूर्णांक wcid, u32 bssidx)
अणु
	u32 offset = MAC_WCID_ATTR_ENTRY(wcid);
	u32 reg;

	/*
	 * The BSS Idx numbers is split in a मुख्य value of 3 bits,
	 * and a extended field क्रम adding one additional bit to the value.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_BSS_IDX, (bssidx & 0x7));
	rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_BSS_IDX_EXT,
			   (bssidx & 0x8) >> 3);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);
पूर्ण

अटल व्योम rt2800_config_wcid_attr_cipher(काष्ठा rt2x00_dev *rt2x00dev,
					   काष्ठा rt2x00lib_crypto *crypto,
					   काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा mac_iveiv_entry iveiv_entry;
	u32 offset;
	u32 reg;

	offset = MAC_WCID_ATTR_ENTRY(key->hw_key_idx);

	अगर (crypto->cmd == SET_KEY) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_KEYTAB,
				   !!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE));
		/*
		 * Both the cipher as the BSS Idx numbers are split in a मुख्य
		 * value of 3 bits, and a extended field क्रम adding one additional
		 * bit to the value.
		 */
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER,
				   (crypto->cipher & 0x7));
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER_EXT,
				   (crypto->cipher & 0x8) >> 3);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_RX_WIUDF, crypto->cipher);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);
	पूर्ण अन्यथा अणु
		/* Delete the cipher without touching the bssidx */
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_KEYTAB, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER_EXT, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_RX_WIUDF, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);
	पूर्ण

	अगर (test_bit(DEVICE_STATE_RESET, &rt2x00dev->flags))
		वापस;

	offset = MAC_IVEIV_ENTRY(key->hw_key_idx);

	स_रखो(&iveiv_entry, 0, माप(iveiv_entry));
	अगर ((crypto->cipher == CIPHER_TKIP) ||
	    (crypto->cipher == CIPHER_TKIP_NO_MIC) ||
	    (crypto->cipher == CIPHER_AES))
		iveiv_entry.iv[3] |= 0x20;
	iveiv_entry.iv[3] |= key->keyidx << 6;
	rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, offset,
				   &iveiv_entry, माप(iveiv_entry));
पूर्ण

पूर्णांक rt2800_config_shared_key(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00lib_crypto *crypto,
			     काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा hw_key_entry key_entry;
	काष्ठा rt2x00_field32 field;
	u32 offset;
	u32 reg;

	अगर (crypto->cmd == SET_KEY) अणु
		key->hw_key_idx = (4 * crypto->bssidx) + key->keyidx;

		स_नकल(key_entry.key, crypto->key,
		       माप(key_entry.key));
		स_नकल(key_entry.tx_mic, crypto->tx_mic,
		       माप(key_entry.tx_mic));
		स_नकल(key_entry.rx_mic, crypto->rx_mic,
		       माप(key_entry.rx_mic));

		offset = SHARED_KEY_ENTRY(key->hw_key_idx);
		rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, offset,
					      &key_entry, माप(key_entry));
	पूर्ण

	/*
	 * The cipher types are stored over multiple रेजिस्टरs
	 * starting with SHARED_KEY_MODE_BASE each word will have
	 * 32 bits and contains the cipher types क्रम 2 bssidx each.
	 * Using the correct defines correctly will cause overhead,
	 * so just calculate the correct offset.
	 */
	field.bit_offset = 4 * (key->hw_key_idx % 8);
	field.bit_mask = 0x7 << field.bit_offset;

	offset = SHARED_KEY_MODE_ENTRY(key->hw_key_idx / 8);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, field,
			   (crypto->cmd == SET_KEY) * crypto->cipher);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

	/*
	 * Update WCID inक्रमmation
	 */
	rt2800_config_wcid(rt2x00dev, crypto->address, key->hw_key_idx);
	rt2800_config_wcid_attr_bssidx(rt2x00dev, key->hw_key_idx,
				       crypto->bssidx);
	rt2800_config_wcid_attr_cipher(rt2x00dev, crypto, key);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_shared_key);

पूर्णांक rt2800_config_pairwise_key(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00lib_crypto *crypto,
			       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा hw_key_entry key_entry;
	u32 offset;

	अगर (crypto->cmd == SET_KEY) अणु
		/*
		 * Allow key configuration only क्रम STAs that are
		 * known by the hw.
		 */
		अगर (crypto->wcid > WCID_END)
			वापस -ENOSPC;
		key->hw_key_idx = crypto->wcid;

		स_नकल(key_entry.key, crypto->key,
		       माप(key_entry.key));
		स_नकल(key_entry.tx_mic, crypto->tx_mic,
		       माप(key_entry.tx_mic));
		स_नकल(key_entry.rx_mic, crypto->rx_mic,
		       माप(key_entry.rx_mic));

		offset = PAIRWISE_KEY_ENTRY(key->hw_key_idx);
		rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, offset,
					      &key_entry, माप(key_entry));
	पूर्ण

	/*
	 * Update WCID inक्रमmation
	 */
	rt2800_config_wcid_attr_cipher(rt2x00dev, crypto, key);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_pairwise_key);

अटल व्योम rt2800_set_max_psdu_len(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 i, max_psdu;
	u32 reg;
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;

	क्रम (i = 0; i < 3; i++)
		अगर (drv_data->ampdu_factor_cnt[i] > 0)
			अवरोध;

	max_psdu = min(drv_data->max_psdu, i);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAX_LEN_CFG);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_PSDU, max_psdu);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAX_LEN_CFG, reg);
पूर्ण

पूर्णांक rt2800_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	काष्ठा rt2x00_sta *sta_priv = sta_to_rt2x00_sta(sta);
	पूर्णांक wcid;

	/*
	 * Limit global maximum TX AMPDU length to smallest value of all
	 * connected stations. In AP mode this can be suboptimal, but we
	 * करो not have a choice अगर some connected STA is not capable to
	 * receive the same amount of data like the others.
	 */
	अगर (sta->ht_cap.ht_supported) अणु
		drv_data->ampdu_factor_cnt[sta->ht_cap.ampdu_factor & 3]++;
		rt2800_set_max_psdu_len(rt2x00dev);
	पूर्ण

	/*
	 * Search क्रम the first मुक्त WCID entry and वापस the corresponding
	 * index.
	 */
	wcid = find_first_zero_bit(drv_data->sta_ids, STA_IDS_SIZE) + WCID_START;

	/*
	 * Store selected wcid even अगर it is invalid so that we can
	 * later decide अगर the STA is uploaded पूर्णांकo the hw.
	 */
	sta_priv->wcid = wcid;

	/*
	 * No space left in the device, however, we can still communicate
	 * with the STA -> No error.
	 */
	अगर (wcid > WCID_END)
		वापस 0;

	__set_bit(wcid - WCID_START, drv_data->sta_ids);
	drv_data->wcid_to_sta[wcid - WCID_START] = sta;

	/*
	 * Clean up WCID attributes and ग_लिखो STA address to the device.
	 */
	rt2800_delete_wcid_attr(rt2x00dev, wcid);
	rt2800_config_wcid(rt2x00dev, sta->addr, wcid);
	rt2800_config_wcid_attr_bssidx(rt2x00dev, wcid,
				       rt2x00lib_get_bssidx(rt2x00dev, vअगर));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_sta_add);

पूर्णांक rt2800_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	काष्ठा rt2x00_sta *sta_priv = sta_to_rt2x00_sta(sta);
	पूर्णांक wcid = sta_priv->wcid;

	अगर (sta->ht_cap.ht_supported) अणु
		drv_data->ampdu_factor_cnt[sta->ht_cap.ampdu_factor & 3]--;
		rt2800_set_max_psdu_len(rt2x00dev);
	पूर्ण

	अगर (wcid > WCID_END)
		वापस 0;
	/*
	 * Remove WCID entry, no need to clean the attributes as they will
	 * get renewed when the WCID is reused.
	 */
	rt2800_config_wcid(rt2x00dev, शून्य, wcid);
	drv_data->wcid_to_sta[wcid - WCID_START] = शून्य;
	__clear_bit(wcid - WCID_START, drv_data->sta_ids);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_sta_हटाओ);

व्योम rt2800_pre_reset_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	काष्ठा data_queue *queue = rt2x00dev->bcn;
	काष्ठा queue_entry *entry;
	पूर्णांक i, wcid;

	क्रम (wcid = WCID_START; wcid < WCID_END; wcid++) अणु
		drv_data->wcid_to_sta[wcid - WCID_START] = शून्य;
		__clear_bit(wcid - WCID_START, drv_data->sta_ids);
	पूर्ण

	क्रम (i = 0; i < queue->limit; i++) अणु
		entry = &queue->entries[i];
		clear_bit(ENTRY_BCN_ASSIGNED, &entry->flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_pre_reset_hw);

व्योम rt2800_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
			  स्थिर अचिन्हित पूर्णांक filter_flags)
अणु
	u32 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * and broadcast frames will always be accepted since
	 * there is no filter क्रम it at this समय.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RX_FILTER_CFG);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_CRC_ERROR,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_PHY_ERROR,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_NOT_MY_BSSD, 0);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_VER_ERROR, 1);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_MULTICAST,
			   !(filter_flags & FIF_ALLMULTI));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_BROADCAST, 0);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_DUPLICATE, 1);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_CF_END_ACK,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_CF_END,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_ACK,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_CTS,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_RTS,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_PSPOLL,
			   !(filter_flags & FIF_PSPOLL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_BA, 0);
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_BAR,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RX_FILTER_CFG_DROP_CNTL,
			   !(filter_flags & FIF_CONTROL));
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RX_FILTER_CFG, reg);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_filter);

व्योम rt2800_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
			काष्ठा rt2x00पूर्णांकf_conf *conf, स्थिर अचिन्हित पूर्णांक flags)
अणु
	u32 reg;
	bool update_bssid = false;

	अगर (flags & CONFIG_UPDATE_TYPE) अणु
		/*
		 * Enable synchronisation.
		 */
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_SYNC, conf->sync);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

		अगर (conf->sync == TSF_SYNC_AP_NONE) अणु
			/*
			 * Tune beacon queue transmit parameters क्रम AP mode
			 */
			reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TBTT_SYNC_CFG);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_CWMIN, 0);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_AIFSN, 1);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_TBTT_ADJUST, 0);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TBTT_SYNC_CFG, reg);
		पूर्ण अन्यथा अणु
			reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TBTT_SYNC_CFG);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_CWMIN, 4);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_AIFSN, 2);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_BCN_EXP_WIN, 32);
			rt2x00_set_field32(&reg, TBTT_SYNC_CFG_TBTT_ADJUST, 16);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TBTT_SYNC_CFG, reg);
		पूर्ण
	पूर्ण

	अगर (flags & CONFIG_UPDATE_MAC) अणु
		अगर (flags & CONFIG_UPDATE_TYPE &&
		    conf->sync == TSF_SYNC_AP_NONE) अणु
			/*
			 * The BSSID रेजिस्टर has to be set to our own mac
			 * address in AP mode.
			 */
			स_नकल(conf->bssid, conf->mac, माप(conf->mac));
			update_bssid = true;
		पूर्ण

		अगर (!is_zero_ether_addr((स्थिर u8 *)conf->mac)) अणु
			reg = le32_to_cpu(conf->mac[1]);
			rt2x00_set_field32(&reg, MAC_ADDR_DW1_UNICAST_TO_ME_MASK, 0xff);
			conf->mac[1] = cpu_to_le32(reg);
		पूर्ण

		rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_ADDR_DW0,
					      conf->mac, माप(conf->mac));
	पूर्ण

	अगर ((flags & CONFIG_UPDATE_BSSID) || update_bssid) अणु
		अगर (!is_zero_ether_addr((स्थिर u8 *)conf->bssid)) अणु
			reg = le32_to_cpu(conf->bssid[1]);
			rt2x00_set_field32(&reg, MAC_BSSID_DW1_BSS_ID_MASK, 3);
			rt2x00_set_field32(&reg, MAC_BSSID_DW1_BSS_BCN_NUM, 0);
			conf->bssid[1] = cpu_to_le32(reg);
		पूर्ण

		rt2800_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_BSSID_DW0,
					      conf->bssid, माप(conf->bssid));
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_पूर्णांकf);

अटल व्योम rt2800_config_ht_opmode(काष्ठा rt2x00_dev *rt2x00dev,
				    काष्ठा rt2x00lib_erp *erp)
अणु
	bool any_sta_nongf = !!(erp->ht_opmode &
				IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u8 protection = erp->ht_opmode & IEEE80211_HT_OP_MODE_PROTECTION;
	u8 mm20_mode, mm40_mode, gf20_mode, gf40_mode;
	u16 mm20_rate, mm40_rate, gf20_rate, gf40_rate;
	u32 reg;

	/* शेष protection rate क्रम HT20: OFDM 24M */
	mm20_rate = gf20_rate = 0x4004;

	/* शेष protection rate क्रम HT40: duplicate OFDM 24M */
	mm40_rate = gf40_rate = 0x4084;

	चयन (protection) अणु
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		/*
		 * All STAs in this BSS are HT20/40 but there might be
		 * STAs not supporting greenfield mode.
		 * => Disable protection क्रम HT transmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 0;

		अवरोध;
	हाल IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		/*
		 * All STAs in this BSS are HT20 or HT20/40 but there
		 * might be STAs not supporting greenfield mode.
		 * => Protect all HT40 transmissions.
		 */
		mm20_mode = gf20_mode = 0;
		mm40_mode = gf40_mode = 1;

		अवरोध;
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
		/*
		 * Nonmember protection:
		 * According to 802.11n we _should_ protect all
		 * HT transmissions (but we करोn't have to).
		 *
		 * But अगर cts_protection is enabled we _shall_ protect
		 * all HT transmissions using a CCK rate.
		 *
		 * And अगर any station is non GF we _shall_ protect
		 * GF transmissions.
		 *
		 * We decide to protect everything
		 * -> fall through to mixed mode.
		 */
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		/*
		 * Legacy STAs are present
		 * => Protect all HT transmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 1;

		/*
		 * If erp protection is needed we have to protect HT
		 * transmissions with CCK 11M दीर्घ preamble.
		 */
		अगर (erp->cts_protection) अणु
			/* करोn't duplicate RTS/CTS in CCK mode */
			mm20_rate = mm40_rate = 0x0003;
			gf20_rate = gf40_rate = 0x0003;
		पूर्ण
		अवरोध;
	पूर्ण

	/* check क्रम STAs not supporting greenfield mode */
	अगर (any_sta_nongf)
		gf20_mode = gf40_mode = 1;

	/* Update HT protection config */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_RATE, mm20_rate);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_CTRL, mm20_mode);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_RATE, mm40_rate);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_CTRL, mm40_mode);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_RATE, gf20_rate);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_CTRL, gf20_mode);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_RATE, gf40_rate);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_CTRL, gf40_mode);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF40_PROT_CFG, reg);
पूर्ण

व्योम rt2800_config_erp(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा rt2x00lib_erp *erp,
		       u32 changed)
अणु
	u32 reg;

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AUTO_RSP_CFG);
		rt2x00_set_field32(&reg, AUTO_RSP_CFG_AR_PREAMBLE,
				   !!erp->लघु_preamble);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTO_RSP_CFG, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, OFDM_PROT_CFG);
		rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_CTRL,
				   erp->cts_protection ? 2 : 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, OFDM_PROT_CFG, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LEGACY_BASIC_RATE,
				      0xff0 | erp->basic_rates);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, HT_BASIC_RATE, 0x00008003);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BKOFF_SLOT_CFG);
		rt2x00_set_field32(&reg, BKOFF_SLOT_CFG_SLOT_TIME,
				   erp->slot_समय);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BKOFF_SLOT_CFG, reg);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, XIFS_TIME_CFG);
		rt2x00_set_field32(&reg, XIFS_TIME_CFG_EIFS, erp->eअगरs);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, XIFS_TIME_CFG, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
		rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL,
				   erp->beacon_पूर्णांक * 16);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_HT)
		rt2800_config_ht_opmode(rt2x00dev, erp);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_erp);

अटल व्योम rt2800_config_3572bt_ant(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	u16 eeprom;
	u8 led_ctrl, led_g_mode, led_r_mode;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_SWITCH);
	अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ) अणु
		rt2x00_set_field32(&reg, GPIO_SWITCH_0, 1);
		rt2x00_set_field32(&reg, GPIO_SWITCH_1, 1);
	पूर्ण अन्यथा अणु
		rt2x00_set_field32(&reg, GPIO_SWITCH_0, 0);
		rt2x00_set_field32(&reg, GPIO_SWITCH_1, 0);
	पूर्ण
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_SWITCH, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LED_CFG);
	led_g_mode = rt2x00_get_field32(reg, LED_CFG_LED_POLAR) ? 3 : 0;
	led_r_mode = rt2x00_get_field32(reg, LED_CFG_LED_POLAR) ? 0 : 3;
	अगर (led_g_mode != rt2x00_get_field32(reg, LED_CFG_G_LED_MODE) ||
	    led_r_mode != rt2x00_get_field32(reg, LED_CFG_R_LED_MODE)) अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
		led_ctrl = rt2x00_get_field16(eeprom, EEPROM_FREQ_LED_MODE);
		अगर (led_ctrl == 0 || led_ctrl > 0x40) अणु
			rt2x00_set_field32(&reg, LED_CFG_G_LED_MODE, led_g_mode);
			rt2x00_set_field32(&reg, LED_CFG_R_LED_MODE, led_r_mode);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LED_CFG, reg);
		पूर्ण अन्यथा अणु
			rt2800_mcu_request(rt2x00dev, MCU_BAND_SELECT, 0xff,
					   (led_g_mode << 2) | led_r_mode, 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rt2800_set_ant_भागersity(काष्ठा rt2x00_dev *rt2x00dev,
				     क्रमागत antenna ant)
अणु
	u32 reg;
	u8 eesk_pin = (ant == ANTENNA_A) ? 1 : 0;
	u8 gpio_bit3 = (ant == ANTENNA_A) ? 0 : 1;

	अगर (rt2x00_is_pci(rt2x00dev)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, E2PROM_CSR);
		rt2x00_set_field32(&reg, E2PROM_CSR_DATA_CLOCK, eesk_pin);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, E2PROM_CSR, reg);
	पूर्ण अन्यथा अगर (rt2x00_is_usb(rt2x00dev))
		rt2800_mcu_request(rt2x00dev, MCU_ANT_SELECT, 0xff,
				   eesk_pin, 0);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);
	rt2x00_set_field32(&reg, GPIO_CTRL_सूची3, 0);
	rt2x00_set_field32(&reg, GPIO_CTRL_VAL3, gpio_bit3);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_CTRL, reg);
पूर्ण

व्योम rt2800_config_ant(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा antenna_setup *ant)
अणु
	u8 r1;
	u8 r3;
	u16 eeprom;

	r1 = rt2800_bbp_पढ़ो(rt2x00dev, 1);
	r3 = rt2800_bbp_पढ़ो(rt2x00dev, 3);

	अगर (rt2x00_rt(rt2x00dev, RT3572) &&
	    rt2x00_has_cap_bt_coexist(rt2x00dev))
		rt2800_config_3572bt_ant(rt2x00dev);

	/*
	 * Configure the TX antenna.
	 */
	चयन (ant->tx_chain_num) अणु
	हाल 1:
		rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 0);
		अवरोध;
	हाल 2:
		अगर (rt2x00_rt(rt2x00dev, RT3572) &&
		    rt2x00_has_cap_bt_coexist(rt2x00dev))
			rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 1);
		अन्यथा
			rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 2);
		अवरोध;
	हाल 3:
		rt2x00_set_field8(&r1, BBP1_TX_ANTENNA, 2);
		अवरोध;
	पूर्ण

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx_chain_num) अणु
	हाल 1:
		अगर (rt2x00_rt(rt2x00dev, RT3070) ||
		    rt2x00_rt(rt2x00dev, RT3090) ||
		    rt2x00_rt(rt2x00dev, RT3352) ||
		    rt2x00_rt(rt2x00dev, RT3390)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev,
						    EEPROM_NIC_CONF1);
			अगर (rt2x00_get_field16(eeprom,
						EEPROM_NIC_CONF1_ANT_DIVERSITY))
				rt2800_set_ant_भागersity(rt2x00dev,
						rt2x00dev->शेष_ant.rx);
		पूर्ण
		rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 0);
		अवरोध;
	हाल 2:
		अगर (rt2x00_rt(rt2x00dev, RT3572) &&
		    rt2x00_has_cap_bt_coexist(rt2x00dev)) अणु
			rt2x00_set_field8(&r3, BBP3_RX_ADC, 1);
			rt2x00_set_field8(&r3, BBP3_RX_ANTENNA,
				rt2x00dev->curr_band == NL80211_BAND_5GHZ);
			rt2800_set_ant_भागersity(rt2x00dev, ANTENNA_B);
		पूर्ण अन्यथा अणु
			rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 1);
		पूर्ण
		अवरोध;
	हाल 3:
		rt2x00_set_field8(&r3, BBP3_RX_ANTENNA, 2);
		अवरोध;
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt2800_bbp_ग_लिखो(rt2x00dev, 1, r1);

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883)) अणु
		अगर (ant->rx_chain_num == 1)
			rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x46);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config_ant);

अटल व्योम rt2800_config_lna_gain(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा rt2x00lib_conf *libconf)
अणु
	u16 eeprom;
	लघु lna_gain;

	अगर (libconf->rf.channel <= 14) अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LNA);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_LNA_BG);
	पूर्ण अन्यथा अगर (libconf->rf.channel <= 64) अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LNA);
		lna_gain = rt2x00_get_field16(eeprom, EEPROM_LNA_A0);
	पूर्ण अन्यथा अगर (libconf->rf.channel <= 128) अणु
		अगर (rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT3883)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_EXT_LNA2);
			lna_gain = rt2x00_get_field16(eeprom,
						      EEPROM_EXT_LNA2_A1);
		पूर्ण अन्यथा अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_BG2);
			lna_gain = rt2x00_get_field16(eeprom,
						      EEPROM_RSSI_BG2_LNA_A1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT3883)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_EXT_LNA2);
			lna_gain = rt2x00_get_field16(eeprom,
						      EEPROM_EXT_LNA2_A2);
		पूर्ण अन्यथा अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_A2);
			lna_gain = rt2x00_get_field16(eeprom,
						      EEPROM_RSSI_A2_LNA_A2);
		पूर्ण
	पूर्ण

	rt2x00dev->lna_gain = lna_gain;
पूर्ण

अटल अंतरभूत bool rt2800_clk_is_20mhz(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस clk_get_rate(rt2x00dev->clk) == 20000000;
पूर्ण

#घोषणा FREQ_OFFSET_BOUND	0x5f

अटल व्योम rt2800_freq_cal_mode1(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 freq_offset, prev_freq_offset;
	u8 rfcsr, prev_rfcsr;

	freq_offset = rt2x00_get_field8(rt2x00dev->freq_offset, RFCSR17_CODE);
	freq_offset = min_t(u8, freq_offset, FREQ_OFFSET_BOUND);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 17);
	prev_rfcsr = rfcsr;

	rt2x00_set_field8(&rfcsr, RFCSR17_CODE, freq_offset);
	अगर (rfcsr == prev_rfcsr)
		वापस;

	अगर (rt2x00_is_usb(rt2x00dev)) अणु
		rt2800_mcu_request(rt2x00dev, MCU_FREQ_OFFSET, 0xff,
				   freq_offset, prev_rfcsr);
		वापस;
	पूर्ण

	prev_freq_offset = rt2x00_get_field8(prev_rfcsr, RFCSR17_CODE);
	जबतक (prev_freq_offset != freq_offset) अणु
		अगर (prev_freq_offset < freq_offset)
			prev_freq_offset++;
		अन्यथा
			prev_freq_offset--;

		rt2x00_set_field8(&rfcsr, RFCSR17_CODE, prev_freq_offset);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, rfcsr);

		usleep_range(1000, 1500);
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_channel_rf2xxx(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	rt2x00_set_field32(&rf->rf4, RF4_FREQ_OFFSET, rt2x00dev->freq_offset);

	अगर (rt2x00dev->शेष_ant.tx_chain_num == 1)
		rt2x00_set_field32(&rf->rf2, RF2_ANTENNA_TX1, 1);

	अगर (rt2x00dev->शेष_ant.rx_chain_num == 1) अणु
		rt2x00_set_field32(&rf->rf2, RF2_ANTENNA_RX1, 1);
		rt2x00_set_field32(&rf->rf2, RF2_ANTENNA_RX2, 1);
	पूर्ण अन्यथा अगर (rt2x00dev->शेष_ant.rx_chain_num == 2)
		rt2x00_set_field32(&rf->rf2, RF2_ANTENNA_RX2, 1);

	अगर (rf->channel > 14) अणु
		/*
		 * When TX घातer is below 0, we should increase it by 7 to
		 * make it a positive value (Minimum value is -7).
		 * However this means that values between 0 and 7 have
		 * द्विगुन meaning, and we should set a 7DBm boost flag.
		 */
		rt2x00_set_field32(&rf->rf3, RF3_TXPOWER_A_7DBM_BOOST,
				   (info->शेष_घातer1 >= 0));

		अगर (info->शेष_घातer1 < 0)
			info->शेष_घातer1 += 7;

		rt2x00_set_field32(&rf->rf3, RF3_TXPOWER_A, info->शेष_घातer1);

		rt2x00_set_field32(&rf->rf4, RF4_TXPOWER_A_7DBM_BOOST,
				   (info->शेष_घातer2 >= 0));

		अगर (info->शेष_घातer2 < 0)
			info->शेष_घातer2 += 7;

		rt2x00_set_field32(&rf->rf4, RF4_TXPOWER_A, info->शेष_घातer2);
	पूर्ण अन्यथा अणु
		rt2x00_set_field32(&rf->rf3, RF3_TXPOWER_G, info->शेष_घातer1);
		rt2x00_set_field32(&rf->rf4, RF4_TXPOWER_G, info->शेष_घातer2);
	पूर्ण

	rt2x00_set_field32(&rf->rf4, RF4_HT40, conf_is_ht40(conf));

	rt2800_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2800_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2800_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt2800_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	udelay(200);

	rt2800_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2800_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2800_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 | 0x00000004);
	rt2800_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	udelay(200);

	rt2800_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2800_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2800_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt2800_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);
पूर्ण

अटल व्योम rt2800_config_channel_rf3xxx(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rfcsr, calib_tx, calib_rx;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rf->rf1);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&rfcsr, RFCSR3_K, rf->rf3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
	rt2x00_set_field8(&rfcsr, RFCSR6_R1, rf->rf2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 12);
	rt2x00_set_field8(&rfcsr, RFCSR12_TX_POWER, info->शेष_घातer1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 13);
	rt2x00_set_field8(&rfcsr, RFCSR13_TX_POWER, info->शेष_घातer2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD,
			  rt2x00dev->शेष_ant.rx_chain_num <= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD,
			  rt2x00dev->शेष_ant.rx_chain_num <= 2);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD,
			  rt2x00dev->शेष_ant.tx_chain_num <= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD,
			  rt2x00dev->शेष_ant.tx_chain_num <= 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 23);
	rt2x00_set_field8(&rfcsr, RFCSR23_FREQ_OFFSET, rt2x00dev->freq_offset);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, rfcsr);

	अगर (rt2x00_rt(rt2x00dev, RT3390)) अणु
		calib_tx = conf_is_ht40(conf) ? 0x68 : 0x4f;
		calib_rx = conf_is_ht40(conf) ? 0x6f : 0x4f;
	पूर्ण अन्यथा अणु
		अगर (conf_is_ht40(conf)) अणु
			calib_tx = drv_data->calibration_bw40;
			calib_rx = drv_data->calibration_bw40;
		पूर्ण अन्यथा अणु
			calib_tx = drv_data->calibration_bw20;
			calib_rx = drv_data->calibration_bw20;
		पूर्ण
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 24);
	rt2x00_set_field8(&rfcsr, RFCSR24_TX_CALIB, calib_tx);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 31);
	rt2x00_set_field8(&rfcsr, RFCSR31_RX_CALIB, calib_rx);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 7);
	rt2x00_set_field8(&rfcsr, RFCSR7_RF_TUNING, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	rt2x00_set_field8(&rfcsr, RFCSR30_RF_CALIBRATION, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

	usleep_range(1000, 1500);

	rt2x00_set_field8(&rfcsr, RFCSR30_RF_CALIBRATION, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);
पूर्ण

अटल व्योम rt2800_config_channel_rf3052(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rfcsr;
	u32 reg;

	अगर (rf->channel <= 14) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, drv_data->bbp25);
		rt2800_bbp_ग_लिखो(rt2x00dev, 26, drv_data->bbp26);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, 0x09);
		rt2800_bbp_ग_लिखो(rt2x00dev, 26, 0xff);
	पूर्ण

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rf->rf3);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
	rt2x00_set_field8(&rfcsr, RFCSR6_R1, rf->rf2);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR6_TXDIV, 2);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR6_TXDIV, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 5);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR5_R1, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR5_R1, 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 12);
	अगर (rf->channel <= 14) अणु
		rt2x00_set_field8(&rfcsr, RFCSR12_DR0, 3);
		rt2x00_set_field8(&rfcsr, RFCSR12_TX_POWER,
				  info->शेष_घातer1);
	पूर्ण अन्यथा अणु
		rt2x00_set_field8(&rfcsr, RFCSR12_DR0, 7);
		rt2x00_set_field8(&rfcsr, RFCSR12_TX_POWER,
				(info->शेष_घातer1 & 0x3) |
				((info->शेष_घातer1 & 0xC) << 1));
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 13);
	अगर (rf->channel <= 14) अणु
		rt2x00_set_field8(&rfcsr, RFCSR13_DR0, 3);
		rt2x00_set_field8(&rfcsr, RFCSR13_TX_POWER,
				  info->शेष_घातer2);
	पूर्ण अन्यथा अणु
		rt2x00_set_field8(&rfcsr, RFCSR13_DR0, 7);
		rt2x00_set_field8(&rfcsr, RFCSR13_TX_POWER,
				(info->शेष_घातer2 & 0x3) |
				((info->शेष_घातer2 & 0xC) << 1));
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);
	अगर (rt2x00_has_cap_bt_coexist(rt2x00dev)) अणु
		अगर (rf->channel <= 14) अणु
			rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
			rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);
		पूर्ण
		rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 1);
	पूर्ण अन्यथा अणु
		चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
		हाल 1:
			rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
			fallthrough;
		हाल 2:
			rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 1);
			अवरोध;
		पूर्ण

		चयन (rt2x00dev->शेष_ant.rx_chain_num) अणु
		हाल 1:
			rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
			fallthrough;
		हाल 2:
			rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 23);
	rt2x00_set_field8(&rfcsr, RFCSR23_FREQ_OFFSET, rt2x00dev->freq_offset);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, rfcsr);

	अगर (conf_is_ht40(conf)) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, drv_data->calibration_bw40);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, drv_data->calibration_bw40);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, drv_data->calibration_bw20);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, drv_data->calibration_bw20);
	पूर्ण

	अगर (rf->channel <= 14) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0xd8);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0xc3);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xf1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0xb9);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x53);
		rfcsr = 0x4c;
		rt2x00_set_field8(&rfcsr, RFCSR16_TXMIXER_GAIN,
				  drv_data->txmixer_gain_24g);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, rfcsr);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x23);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x93);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xb3);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x15);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x85);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x9b);
	पूर्ण अन्यथा अणु
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 7);
		rt2x00_set_field8(&rfcsr, RFCSR7_BIT2, 1);
		rt2x00_set_field8(&rfcsr, RFCSR7_BIT3, 0);
		rt2x00_set_field8(&rfcsr, RFCSR7_BIT4, 1);
		rt2x00_set_field8(&rfcsr, RFCSR7_BITS67, 0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, rfcsr);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0xc0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xf1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x00);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x43);
		rfcsr = 0x7a;
		rt2x00_set_field8(&rfcsr, RFCSR16_TXMIXER_GAIN,
				  drv_data->txmixer_gain_5g);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, rfcsr);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x23);
		अगर (rf->channel <= 64) अणु
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0xb7);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xf6);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x3d);
		पूर्ण अन्यथा अगर (rf->channel <= 128) अणु
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x74);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xf4);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x01);
		पूर्ण अन्यथा अणु
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x72);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xf3);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x01);
		पूर्ण
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x87);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x01);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x9f);
	पूर्ण

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);
	rt2x00_set_field32(&reg, GPIO_CTRL_सूची7, 0);
	अगर (rf->channel <= 14)
		rt2x00_set_field32(&reg, GPIO_CTRL_VAL7, 1);
	अन्यथा
		rt2x00_set_field32(&reg, GPIO_CTRL_VAL7, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_CTRL, reg);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 7);
	rt2x00_set_field8(&rfcsr, RFCSR7_RF_TUNING, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, rfcsr);
पूर्ण

अटल व्योम rt2800_config_channel_rf3053(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 txrx_agc_fc;
	u8 txrx_h20m;
	u8 rfcsr;
	u8 bbp;
	स्थिर bool txbf_enabled = false; /* TODO */

	/* TODO: use TXअणु0,1,2पूर्णFinePowerControl values from EEPROM */
	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 109);
	rt2x00_set_field8(&bbp, BBP109_TX0_POWER, 0);
	rt2x00_set_field8(&bbp, BBP109_TX1_POWER, 0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 109, bbp);

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 110);
	rt2x00_set_field8(&bbp, BBP110_TX2_POWER, 0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 110, bbp);

	अगर (rf->channel <= 14) अणु
		/* Restore BBP 25 & 26 क्रम 2.4 GHz */
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, drv_data->bbp25);
		rt2800_bbp_ग_लिखो(rt2x00dev, 26, drv_data->bbp26);
	पूर्ण अन्यथा अणु
		/* Hard code BBP 25 & 26 क्रम 5GHz */

		/* Enable IQ Phase correction */
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, 0x09);
		/* Setup IQ Phase correction value */
		rt2800_bbp_ग_लिखो(rt2x00dev, 26, 0xff);
	पूर्ण

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rf->rf3 & 0xf);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 11);
	rt2x00_set_field8(&rfcsr, RFCSR11_R, (rf->rf2 & 0x3));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 11);
	rt2x00_set_field8(&rfcsr, RFCSR11_PLL_IDOH, 1);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR11_PLL_MOD, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR11_PLL_MOD, 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 53);
	अगर (rf->channel <= 14) अणु
		rfcsr = 0;
		rt2x00_set_field8(&rfcsr, RFCSR53_TX_POWER,
				  info->शेष_घातer1 & 0x1f);
	पूर्ण अन्यथा अणु
		अगर (rt2x00_is_usb(rt2x00dev))
			rfcsr = 0x40;

		rt2x00_set_field8(&rfcsr, RFCSR53_TX_POWER,
				  ((info->शेष_घातer1 & 0x18) << 1) |
				  (info->शेष_घातer1 & 7));
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 55);
	अगर (rf->channel <= 14) अणु
		rfcsr = 0;
		rt2x00_set_field8(&rfcsr, RFCSR55_TX_POWER,
				  info->शेष_घातer2 & 0x1f);
	पूर्ण अन्यथा अणु
		अगर (rt2x00_is_usb(rt2x00dev))
			rfcsr = 0x40;

		rt2x00_set_field8(&rfcsr, RFCSR55_TX_POWER,
				  ((info->शेष_घातer2 & 0x18) << 1) |
				  (info->शेष_घातer2 & 7));
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 54);
	अगर (rf->channel <= 14) अणु
		rfcsr = 0;
		rt2x00_set_field8(&rfcsr, RFCSR54_TX_POWER,
				  info->शेष_घातer3 & 0x1f);
	पूर्ण अन्यथा अणु
		अगर (rt2x00_is_usb(rt2x00dev))
			rfcsr = 0x40;

		rt2x00_set_field8(&rfcsr, RFCSR54_TX_POWER,
				  ((info->शेष_घातer3 & 0x18) << 1) |
				  (info->शेष_घातer3 & 7));
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_PLL_PD, 1);

	चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
	हाल 3:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 1);
		fallthrough;
	हाल 2:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
		fallthrough;
	हाल 1:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);
		अवरोध;
	पूर्ण

	चयन (rt2x00dev->शेष_ant.rx_chain_num) अणु
	हाल 3:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 1);
		fallthrough;
	हाल 2:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
		fallthrough;
	हाल 1:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
		अवरोध;
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	अगर (conf_is_ht40(conf)) अणु
		txrx_agc_fc = rt2x00_get_field8(drv_data->calibration_bw40,
						RFCSR24_TX_AGC_FC);
		txrx_h20m = rt2x00_get_field8(drv_data->calibration_bw40,
					      RFCSR24_TX_H20M);
	पूर्ण अन्यथा अणु
		txrx_agc_fc = rt2x00_get_field8(drv_data->calibration_bw20,
						RFCSR24_TX_AGC_FC);
		txrx_h20m = rt2x00_get_field8(drv_data->calibration_bw20,
					      RFCSR24_TX_H20M);
	पूर्ण

	/* NOTE: the reference driver करोes not ग_लिखोs the new value
	 * back to RFCSR 32
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 32);
	rt2x00_set_field8(&rfcsr, RFCSR32_TX_AGC_FC, txrx_agc_fc);

	अगर (rf->channel <= 14)
		rfcsr = 0xa0;
	अन्यथा
		rfcsr = 0x80;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	rt2x00_set_field8(&rfcsr, RFCSR30_TX_H20M, txrx_h20m);
	rt2x00_set_field8(&rfcsr, RFCSR30_RX_H20M, txrx_h20m);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

	/* Band selection */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 36);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR36_RF_BS, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR36_RF_BS, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 34);
	अगर (rf->channel <= 14)
		rfcsr = 0x3c;
	अन्यथा
		rfcsr = 0x20;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 12);
	अगर (rf->channel <= 14)
		rfcsr = 0x1a;
	अन्यथा
		rfcsr = 0x12;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
	अगर (rf->channel >= 1 && rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR6_VCO_IC, 1);
	अन्यथा अगर (rf->channel >= 36 && rf->channel <= 64)
		rt2x00_set_field8(&rfcsr, RFCSR6_VCO_IC, 2);
	अन्यथा अगर (rf->channel >= 100 && rf->channel <= 128)
		rt2x00_set_field8(&rfcsr, RFCSR6_VCO_IC, 2);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR6_VCO_IC, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	rt2x00_set_field8(&rfcsr, RFCSR30_RX_VCM, 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x60);

	अगर (rf->channel <= 14) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xd3);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x12);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xd8);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x23);
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 51);
	rt2x00_set_field8(&rfcsr, RFCSR51_BITS01, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 51);
	अगर (rf->channel <= 14) अणु
		rt2x00_set_field8(&rfcsr, RFCSR51_BITS24, 5);
		rt2x00_set_field8(&rfcsr, RFCSR51_BITS57, 3);
	पूर्ण अन्यथा अणु
		rt2x00_set_field8(&rfcsr, RFCSR51_BITS24, 4);
		rt2x00_set_field8(&rfcsr, RFCSR51_BITS57, 2);
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 49);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX_LO1_IC, 3);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR49_TX_LO1_IC, 2);

	अगर (txbf_enabled)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX_DIV, 1);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 50);
	rt2x00_set_field8(&rfcsr, RFCSR50_TX_LO1_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 57);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR57_DRV_CC, 0x1b);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR57_DRV_CC, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, rfcsr);

	अगर (rf->channel <= 14) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x93);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x45);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x9b);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x05);
	पूर्ण

	/* Initiate VCO calibration */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
	अगर (rf->channel <= 14) अणु
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
	पूर्ण अन्यथा अणु
		rt2x00_set_field8(&rfcsr, RFCSR3_BIT1, 1);
		rt2x00_set_field8(&rfcsr, RFCSR3_BIT2, 1);
		rt2x00_set_field8(&rfcsr, RFCSR3_BIT3, 1);
		rt2x00_set_field8(&rfcsr, RFCSR3_BIT4, 1);
		rt2x00_set_field8(&rfcsr, RFCSR3_BIT5, 1);
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);

	अगर (rf->channel >= 1 && rf->channel <= 14) अणु
		rfcsr = 0x23;
		अगर (txbf_enabled)
			rt2x00_set_field8(&rfcsr, RFCSR39_RX_DIV, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, rfcsr);

		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xbb);
	पूर्ण अन्यथा अगर (rf->channel >= 36 && rf->channel <= 64) अणु
		rfcsr = 0x36;
		अगर (txbf_enabled)
			rt2x00_set_field8(&rfcsr, RFCSR39_RX_DIV, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x36);

		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xeb);
	पूर्ण अन्यथा अगर (rf->channel >= 100 && rf->channel <= 128) अणु
		rfcsr = 0x32;
		अगर (txbf_enabled)
			rt2x00_set_field8(&rfcsr, RFCSR39_RX_DIV, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, rfcsr);

		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xb3);
	पूर्ण अन्यथा अणु
		rfcsr = 0x30;
		अगर (txbf_enabled)
			rt2x00_set_field8(&rfcsr, RFCSR39_RX_DIV, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, rfcsr);

		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0x9b);
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_channel_rf3853(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	u8 rfcsr;
	u8 bbp;
	u8 pwr1, pwr2, pwr3;

	स्थिर bool txbf_enabled = false; /* TODO */

	/* TODO: add band selection */

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x40);
	अन्यथा अगर (rf->channel < 132)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x80);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x40);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rf->rf3);

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x46);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x48);

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x1a);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x52);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x12);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_PLL_PD, 1);

	चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
	हाल 3:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 1);
		fallthrough;
	हाल 2:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
		fallthrough;
	हाल 1:
		rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);
		अवरोध;
	पूर्ण

	चयन (rt2x00dev->शेष_ant.rx_chain_num) अणु
	हाल 3:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 1);
		fallthrough;
	हाल 2:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
		fallthrough;
	हाल 1:
		rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
		अवरोध;
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	अगर (!conf_is_ht40(conf))
		rfcsr &= ~(0x06);
	अन्यथा
		rfcsr |= 0x06;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0xa0);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);

	अगर (conf_is_ht40(conf))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0xd8);

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x3c);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x20);

	/* loopback RF_BS */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 36);
	अगर (rf->channel <= 14)
		rt2x00_set_field8(&rfcsr, RFCSR36_RF_BS, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR36_RF_BS, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, rfcsr);

	अगर (rf->channel <= 14)
		rfcsr = 0x23;
	अन्यथा अगर (rf->channel < 100)
		rfcsr = 0x36;
	अन्यथा अगर (rf->channel < 132)
		rfcsr = 0x32;
	अन्यथा
		rfcsr = 0x30;

	अगर (txbf_enabled)
		rfcsr |= 0x40;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, rfcsr);

	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x93);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x9b);

	अगर (rf->channel <= 14)
		rfcsr = 0xbb;
	अन्यथा अगर (rf->channel < 100)
		rfcsr = 0xeb;
	अन्यथा अगर (rf->channel < 132)
		rfcsr = 0xb3;
	अन्यथा
		rfcsr = 0x9b;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, rfcsr);

	अगर (rf->channel <= 14)
		rfcsr = 0x8e;
	अन्यथा
		rfcsr = 0x8a;

	अगर (txbf_enabled)
		rfcsr |= 0x20;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, rfcsr);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, 0x86);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 51);
	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x75);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x51);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 52);
	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x45);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x05);

	अगर (rf->channel <= 14) अणु
		pwr1 = info->शेष_घातer1 & 0x1f;
		pwr2 = info->शेष_घातer2 & 0x1f;
		pwr3 = info->शेष_घातer3 & 0x1f;
	पूर्ण अन्यथा अणु
		pwr1 = 0x48 | ((info->शेष_घातer1 & 0x18) << 1) |
			(info->शेष_घातer1 & 0x7);
		pwr2 = 0x48 | ((info->शेष_घातer2 & 0x18) << 1) |
			(info->शेष_घातer2 & 0x7);
		pwr3 = 0x48 | ((info->शेष_घातer3 & 0x18) << 1) |
			(info->शेष_घातer3 & 0x7);
	पूर्ण

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, pwr1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, pwr2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, pwr3);

	rt2x00_dbg(rt2x00dev, "Channel:%d, pwr1:%02x, pwr2:%02x, pwr3:%02x\n",
		   rf->channel, pwr1, pwr2, pwr3);

	bbp = (info->शेष_घातer1 >> 5) |
	      ((info->शेष_घातer2 & 0xe0) >> 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 109, bbp);

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 110);
	bbp &= 0x0f;
	bbp |= (info->शेष_घातer3 & 0xe0) >> 1;
	rt2800_bbp_ग_लिखो(rt2x00dev, 110, bbp);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 57);
	अगर (rf->channel <= 14)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x6e);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x3e);

	/* Enable RF tuning */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);

	udelay(2000);

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 49);
	/* clear update flag */
	rt2800_bbp_ग_लिखो(rt2x00dev, 49, bbp & 0xfe);
	rt2800_bbp_ग_लिखो(rt2x00dev, 49, bbp);

	/* TODO: add calibration क्रम TxBF */
पूर्ण

#घोषणा POWER_BOUND		0x27
#घोषणा POWER_BOUND_5G		0x2b

अटल व्योम rt2800_config_channel_rf3290(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	u8 rfcsr;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rf->rf3);
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 11);
	rt2x00_set_field8(&rfcsr, RFCSR11_R, rf->rf2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 49);
	अगर (info->शेष_घातer1 > POWER_BOUND)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, POWER_BOUND);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, info->शेष_घातer1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	अगर (rf->channel <= 14) अणु
		अगर (rf->channel == 6)
			rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0c);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0b);

		अगर (rf->channel >= 1 && rf->channel <= 6)
			rt2800_bbp_ग_लिखो(rt2x00dev, 59, 0x0f);
		अन्यथा अगर (rf->channel >= 7 && rf->channel <= 11)
			rt2800_bbp_ग_लिखो(rt2x00dev, 59, 0x0e);
		अन्यथा अगर (rf->channel >= 12 && rf->channel <= 14)
			rt2800_bbp_ग_लिखो(rt2x00dev, 59, 0x0d);
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_channel_rf3322(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	u8 rfcsr;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rf->rf3);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x42);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x1c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x00);

	अगर (info->शेष_घातer1 > POWER_BOUND)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, POWER_BOUND);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, info->शेष_घातer1);

	अगर (info->शेष_घातer2 > POWER_BOUND)
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, POWER_BOUND);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, info->शेष_घातer2);

	rt2800_freq_cal_mode1(rt2x00dev);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);

	अगर ( rt2x00dev->शेष_ant.tx_chain_num == 2 )
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 0);

	अगर ( rt2x00dev->शेष_ant.rx_chain_num == 2 )
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 0);

	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 80);
पूर्ण

अटल व्योम rt2800_config_channel_rf53xx(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	u8 rfcsr;
	पूर्णांक idx = rf->channel-1;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rf->rf3);
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 11);
	rt2x00_set_field8(&rfcsr, RFCSR11_R, rf->rf2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 49);
	अगर (info->शेष_घातer1 > POWER_BOUND)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, POWER_BOUND);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, info->शेष_घातer1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, rfcsr);

	अगर (rt2x00_rt(rt2x00dev, RT5392)) अणु
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 50);
		अगर (info->शेष_घातer2 > POWER_BOUND)
			rt2x00_set_field8(&rfcsr, RFCSR50_TX, POWER_BOUND);
		अन्यथा
			rt2x00_set_field8(&rfcsr, RFCSR50_TX,
					  info->शेष_घातer2);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, rfcsr);
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	अगर (rt2x00_rt(rt2x00dev, RT5392)) अणु
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
	पूर्ण
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_PLL_PD, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	अगर (rt2x00_has_cap_bt_coexist(rt2x00dev)) अणु
		अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F)) अणु
			/* r55/r59 value array of channel 1~14 */
			अटल स्थिर अक्षर r55_bt_rev[] = अणु0x83, 0x83,
				0x83, 0x73, 0x73, 0x63, 0x53, 0x53,
				0x53, 0x43, 0x43, 0x43, 0x43, 0x43पूर्ण;
			अटल स्थिर अक्षर r59_bt_rev[] = अणु0x0e, 0x0e,
				0x0e, 0x0e, 0x0e, 0x0b, 0x0a, 0x09,
				0x07, 0x07, 0x07, 0x07, 0x07, 0x07पूर्ण;

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 55,
					   r55_bt_rev[idx]);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59,
					   r59_bt_rev[idx]);
		पूर्ण अन्यथा अणु
			अटल स्थिर अक्षर r59_bt[] = अणु0x8b, 0x8b, 0x8b,
				0x8b, 0x8b, 0x8b, 0x8b, 0x8a, 0x89,
				0x88, 0x88, 0x86, 0x85, 0x84पूर्ण;

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, r59_bt[idx]);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F)) अणु
			अटल स्थिर अक्षर r55_nonbt_rev[] = अणु0x23, 0x23,
				0x23, 0x23, 0x13, 0x13, 0x03, 0x03,
				0x03, 0x03, 0x03, 0x03, 0x03, 0x03पूर्ण;
			अटल स्थिर अक्षर r59_nonbt_rev[] = अणु0x07, 0x07,
				0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
				0x07, 0x07, 0x06, 0x05, 0x04, 0x04पूर्ण;

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 55,
					   r55_nonbt_rev[idx]);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59,
					   r59_nonbt_rev[idx]);
		पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5390) ||
			   rt2x00_rt(rt2x00dev, RT5392) ||
			   rt2x00_rt(rt2x00dev, RT6352)) अणु
			अटल स्थिर अक्षर r59_non_bt[] = अणु0x8f, 0x8f,
				0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8d,
				0x8a, 0x88, 0x88, 0x87, 0x87, 0x86पूर्ण;

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59,
					   r59_non_bt[idx]);
		पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5350)) अणु
			अटल स्थिर अक्षर r59_non_bt[] = अणु0x0b, 0x0b,
				0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a,
				0x0a, 0x09, 0x08, 0x07, 0x07, 0x06पूर्ण;

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59,
					   r59_non_bt[idx]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_channel_rf55xx(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	u8 rfcsr, ep_reg;
	u32 reg;
	पूर्णांक घातer_bound;

	/* TODO */
	स्थिर bool is_11b = false;
	स्थिर bool is_type_ep = false;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL,
			   (rf->channel > 14 || conf_is_ht40(conf)) ? 5 : 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);

	/* Order of values on rf_channel entry: N, K, mod, R */
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, rf->rf1 & 0xff);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev,  9);
	rt2x00_set_field8(&rfcsr, RFCSR9_K, rf->rf2 & 0xf);
	rt2x00_set_field8(&rfcsr, RFCSR9_N, (rf->rf1 & 0x100) >> 8);
	rt2x00_set_field8(&rfcsr, RFCSR9_MOD, ((rf->rf3 - 8) & 0x4) >> 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 11);
	rt2x00_set_field8(&rfcsr, RFCSR11_R, rf->rf4 - 1);
	rt2x00_set_field8(&rfcsr, RFCSR11_MOD, (rf->rf3 - 8) & 0x3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, rfcsr);

	अगर (rf->channel <= 14) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x90);
		/* FIXME: RF11 owerग_लिखो ? */
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x4A);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x52);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x42);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x40);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x4A);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x80);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x42);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x80);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x08);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x89);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1B);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x0D);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0x9B);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xD5);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x72);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x0E);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xA2);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x6B);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x10);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x3E);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x48);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x38);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xA1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x00);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x39);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x45);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0x91);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x39);

		/* TODO RF27 <- tssi */

		rfcsr = rf->channel <= 10 ? 0x07 : 0x06;
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, rfcsr);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, rfcsr);

		अगर (is_11b) अणु
			/* CCK */
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0xF8);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0xC0);
			अगर (is_type_ep)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x06);
			अन्यथा
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x47);
		पूर्ण अन्यथा अणु
			/* OFDM */
			अगर (is_type_ep)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x03);
			अन्यथा
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x43);
		पूर्ण

		घातer_bound = POWER_BOUND;
		ep_reg = 0x2;
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x97);
		/* FIMXE: RF11 overग_लिखो */
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x40);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0xBF);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x42);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x04);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x85);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x42);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xBB);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xD7);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0x41);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x00);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x77);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x05);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0x01);

		/* TODO RF27 <- tssi */

		अगर (rf->channel >= 36 && rf->channel <= 64) अणु

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x2E);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x22);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x60);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x7F);
			अगर (rf->channel <= 50)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x09);
			अन्यथा अगर (rf->channel >= 52)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x07);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1C);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x5B);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0X40);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0X00);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0xFE);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x0C);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0xF8);
			अगर (rf->channel <= 50) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x06),
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xD3);
			पूर्ण अन्यथा अगर (rf->channel >= 52) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x04);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xBB);
			पूर्ण

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x15);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x7F);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x15);

		पूर्ण अन्यथा अगर (rf->channel >= 100 && rf->channel <= 165) अणु

			rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x0E);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x42);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x40);
			अगर (rf->channel <= 153) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x3C);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x06);
			पूर्ण अन्यथा अगर (rf->channel >= 155) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x38);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x05);
			पूर्ण
			अगर (rf->channel <= 138) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1A);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x3B);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x20);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x18);
			पूर्ण अन्यथा अगर (rf->channel >= 140) अणु
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x18);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x1B);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x10);
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0X08);
			पूर्ण
			अगर (rf->channel <= 124)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0xFC);
			अन्यथा अगर (rf->channel >= 126)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0xEC);
			अगर (rf->channel <= 138)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x06);
			अन्यथा अगर (rf->channel >= 140)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x06);
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0xEB);
			अगर (rf->channel <= 138)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x01);
			अन्यथा अगर (rf->channel >= 140)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x00);
			अगर (rf->channel <= 128)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xBB);
			अन्यथा अगर (rf->channel >= 130)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xAB);
			अगर (rf->channel <= 116)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x1D);
			अन्यथा अगर (rf->channel >= 118)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x15);
			अगर (rf->channel <= 138)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x3F);
			अन्यथा अगर (rf->channel >= 140)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x7C);
			अगर (rf->channel <= 116)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x1D);
			अन्यथा अगर (rf->channel >= 118)
				rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x15);
		पूर्ण

		घातer_bound = POWER_BOUND_5G;
		ep_reg = 0x3;
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 49);
	अगर (info->शेष_घातer1 > घातer_bound)
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, घातer_bound);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR49_TX, info->शेष_घातer1);
	अगर (is_type_ep)
		rt2x00_set_field8(&rfcsr, RFCSR49_EP, ep_reg);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 50);
	अगर (info->शेष_घातer2 > घातer_bound)
		rt2x00_set_field8(&rfcsr, RFCSR50_TX, घातer_bound);
	अन्यथा
		rt2x00_set_field8(&rfcsr, RFCSR50_TX, info->शेष_घातer2);
	अगर (is_type_ep)
		rt2x00_set_field8(&rfcsr, RFCSR50_EP, ep_reg);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_PLL_PD, 1);

	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD,
			  rt2x00dev->शेष_ant.tx_chain_num >= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD,
			  rt2x00dev->शेष_ant.tx_chain_num == 2);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);

	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD,
			  rt2x00dev->शेष_ant.rx_chain_num >= 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD,
			  rt2x00dev->शेष_ant.rx_chain_num == 2);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xe4);

	अगर (conf_is_ht40(conf))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x16);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);

	अगर (!is_11b) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	पूर्ण

	/* TODO proper frequency adjusपंचांगent */
	rt2800_freq_cal_mode1(rt2x00dev);

	/* TODO merge with others */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);

	/* BBP settings */
	rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
	rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
	rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, (rf->channel <= 14) ? 0x1C : 0x18);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, (rf->channel <= 14) ? 0x0E : 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, (rf->channel <= 14) ? 0x3A : 0x38);
	rt2800_bbp_ग_लिखो(rt2x00dev, 82, (rf->channel <= 14) ? 0x62 : 0x92);

	/* GLRT band configuration */
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 128);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0xE0 : 0xF0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 129);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0x1F : 0x1E);
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 130);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0x38 : 0x28);
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 131);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0x32 : 0x20);
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 133);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0x28 : 0x7F);
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, 124);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, (rf->channel <= 14) ? 0x19 : 0x7F);
पूर्ण

अटल व्योम rt2800_config_channel_rf7620(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_conf *conf,
					 काष्ठा rf_channel *rf,
					 काष्ठा channel_info *info)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rx_agc_fc, tx_agc_fc;
	u8 rfcsr;

	/* Frequeny plan setting */
	/* Rभाग setting (set 0x03 अगर Xtal==20)
	 * R13[1:0]
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 13);
	rt2x00_set_field8(&rfcsr, RFCSR13_RDIV_MT7620,
			  rt2800_clk_is_20mhz(rt2x00dev) ? 3 : 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, rfcsr);

	/* N setting
	 * R20[7:0] in rf->rf1
	 * R21[0] always 0
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 20);
	rfcsr = (rf->rf1 & 0x00ff);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 21);
	rt2x00_set_field8(&rfcsr, RFCSR21_BIT1, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, rfcsr);

	/* K setting (always 0)
	 * R16[3:0] (RF PLL freq selection)
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 16);
	rt2x00_set_field8(&rfcsr, RFCSR16_RF_PLL_FREQ_SEL_MT7620, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, rfcsr);

	/* D setting (always 0)
	 * R22[2:0] (D=15, R22[2:0]=<111>)
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 22);
	rt2x00_set_field8(&rfcsr, RFCSR22_FREQPLAN_D_MT7620, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, rfcsr);

	/* Ksd setting
	 * Ksd: R17<7:0> in rf->rf2
	 *      R18<7:0> in rf->rf3
	 *      R19<1:0> in rf->rf4
	 */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 17);
	rfcsr = rf->rf2;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 18);
	rfcsr = rf->rf3;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 19);
	rt2x00_set_field8(&rfcsr, RFCSR19_K, rf->rf4);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, rfcsr);

	/* Default: XO=20MHz , SDM mode */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 16);
	rt2x00_set_field8(&rfcsr, RFCSR16_SDM_MODE_MT7620, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 21);
	rt2x00_set_field8(&rfcsr, RFCSR21_BIT8, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_EN_MT7620,
			  rt2x00dev->शेष_ant.tx_chain_num != 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_TX2_EN_MT7620,
			  rt2x00dev->शेष_ant.tx_chain_num != 1);
	rt2x00_set_field8(&rfcsr, RFCSR2_RX2_EN_MT7620,
			  rt2x00dev->शेष_ant.rx_chain_num != 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 42);
	rt2x00_set_field8(&rfcsr, RFCSR42_TX2_EN_MT7620,
			  rt2x00dev->शेष_ant.tx_chain_num != 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, rfcsr);

	/* RF क्रम DC Cal BW */
	अगर (conf_is_ht40(conf)) अणु
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 6, 0x10);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 7, 0x10);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 8, 0x04);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 58, 0x10);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 59, 0x10);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 6, 0x20);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 7, 0x20);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 8, 0x00);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 58, 0x20);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 59, 0x20);
	पूर्ण

	अगर (conf_is_ht40(conf)) अणु
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 58, 0x08);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 59, 0x08);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 58, 0x28);
		rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 59, 0x28);
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 28);
	rt2x00_set_field8(&rfcsr, RFCSR28_CH11_HT40,
			  conf_is_ht40(conf) && (rf->channel == 11));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, rfcsr);

	अगर (!test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags)) अणु
		अगर (conf_is_ht40(conf)) अणु
			rx_agc_fc = drv_data->rx_calibration_bw40;
			tx_agc_fc = drv_data->tx_calibration_bw40;
		पूर्ण अन्यथा अणु
			rx_agc_fc = drv_data->rx_calibration_bw20;
			tx_agc_fc = drv_data->tx_calibration_bw20;
		पूर्ण
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 6);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 6, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 7);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 7, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 7, 6);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 7, 6, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 7, 7);
		rfcsr &= (~0x3F);
		rfcsr |= rx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 7, 7, rfcsr);

		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 58);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 58, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 59);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 59, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 7, 58);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 7, 58, rfcsr);
		rfcsr = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 7, 59);
		rfcsr &= (~0x3F);
		rfcsr |= tx_agc_fc;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 7, 59, rfcsr);
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_alc(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा ieee80211_channel *chan,
			      पूर्णांक घातer_level) अणु
	u16 eeprom, target_घातer, max_घातer;
	u32 mac_sys_ctrl, mac_status;
	u32 reg;
	u8 bbp;
	पूर्णांक i;

	/* hardware unit is 0.5dBm, limited to 23.5dBm */
	घातer_level *= 2;
	अगर (घातer_level > 0x2f)
		घातer_level = 0x2f;

	max_घातer = chan->max_घातer * 2;
	अगर (max_घातer > 0x2f)
		max_घातer = 0x2f;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_ALC_CFG_0);
	rt2x00_set_field32(&reg, TX_ALC_CFG_0_CH_INIT_0, घातer_level);
	rt2x00_set_field32(&reg, TX_ALC_CFG_0_CH_INIT_1, घातer_level);
	rt2x00_set_field32(&reg, TX_ALC_CFG_0_LIMIT_0, max_घातer);
	rt2x00_set_field32(&reg, TX_ALC_CFG_0_LIMIT_1, max_घातer);

	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_INTERNAL_TX_ALC)) अणु
		/* init base घातer by eeprom target घातer */
		target_घातer = rt2800_eeprom_पढ़ो(rt2x00dev,
						  EEPROM_TXPOWER_INIT);
		rt2x00_set_field32(&reg, TX_ALC_CFG_0_CH_INIT_0, target_घातer);
		rt2x00_set_field32(&reg, TX_ALC_CFG_0_CH_INIT_1, target_घातer);
	पूर्ण
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_ALC_CFG_0, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_ALC_CFG_1);
	rt2x00_set_field32(&reg, TX_ALC_CFG_1_TX_TEMP_COMP, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_ALC_CFG_1, reg);

	/* Save MAC SYS CTRL रेजिस्टरs */
	mac_sys_ctrl = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
	/* Disable Tx/Rx */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, 0);
	/* Check MAC Tx/Rx idle */
	क्रम (i = 0; i < 10000; i++) अणु
		mac_status = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_STATUS_CFG);
		अगर (mac_status & 0x3)
			usleep_range(50, 200);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (i == 10000)
		rt2x00_warn(rt2x00dev, "Wait MAC Status to MAX !!!\n");

	अगर (chan->center_freq > 2457) अणु
		bbp = rt2800_bbp_पढ़ो(rt2x00dev, 30);
		bbp = 0x40;
		rt2800_bbp_ग_लिखो(rt2x00dev, 30, bbp);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0);
		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev))
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xfb);
		अन्यथा
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0x7b);
	पूर्ण अन्यथा अणु
		bbp = rt2800_bbp_पढ़ो(rt2x00dev, 30);
		bbp = 0x1f;
		rt2800_bbp_ग_लिखो(rt2x00dev, 30, bbp);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x80);
		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev))
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xdb);
		अन्यथा
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0x5b);
	पूर्ण
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, mac_sys_ctrl);

	rt2800_vco_calibration(rt2x00dev);
पूर्ण

अटल व्योम rt2800_bbp_ग_लिखो_with_rx_chain(काष्ठा rt2x00_dev *rt2x00dev,
					   स्थिर अचिन्हित पूर्णांक word,
					   स्थिर u8 value)
अणु
	u8 chain, reg;

	क्रम (chain = 0; chain < rt2x00dev->शेष_ant.rx_chain_num; chain++) अणु
		reg = rt2800_bbp_पढ़ो(rt2x00dev, 27);
		rt2x00_set_field8(&reg,  BBP27_RX_CHAIN_SEL, chain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 27, reg);

		rt2800_bbp_ग_लिखो(rt2x00dev, word, value);
	पूर्ण
पूर्ण

अटल व्योम rt2800_iq_calibrate(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक channel)
अणु
	u8 cal;

	/* TX0 IQ Gain */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x2c);
	अगर (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_GAIN_CAL_TX0_2G);
	अन्यथा अगर (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5G);
	अन्यथा अगर (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5G);
	अन्यथा अगर (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5G);
	अन्यथा
		cal = 0;
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal);

	/* TX0 IQ Phase */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x2d);
	अगर (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_PHASE_CAL_TX0_2G);
	अन्यथा अगर (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5G);
	अन्यथा अगर (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5G);
	अन्यथा अगर (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5G);
	अन्यथा
		cal = 0;
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal);

	/* TX1 IQ Gain */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x4a);
	अगर (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_GAIN_CAL_TX1_2G);
	अन्यथा अगर (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5G);
	अन्यथा अगर (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5G);
	अन्यथा अगर (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5G);
	अन्यथा
		cal = 0;
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal);

	/* TX1 IQ Phase */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x4b);
	अगर (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_PHASE_CAL_TX1_2G);
	अन्यथा अगर (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5G);
	अन्यथा अगर (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5G);
	अन्यथा अगर (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5G);
	अन्यथा
		cal = 0;
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal);

	/* FIXME: possible RX0, RX1 callibration ? */

	/* RF IQ compensation control */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x04);
	cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_RF_IQ_COMPENSATION_CONTROL);
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal != 0xff ? cal : 0);

	/* RF IQ imbalance compensation control */
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, 0x03);
	cal = rt2x00_eeprom_byte(rt2x00dev,
				 EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CONTROL);
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, cal != 0xff ? cal : 0);
पूर्ण

अटल अक्षर rt2800_txघातer_to_dev(काष्ठा rt2x00_dev *rt2x00dev,
				  अचिन्हित पूर्णांक channel,
				  अक्षर txघातer)
अणु
	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		txघातer = rt2x00_get_field8(txघातer, EEPROM_TXPOWER_ALC);

	अगर (channel <= 14)
		वापस clamp_t(अक्षर, txघातer, MIN_G_TXPOWER, MAX_G_TXPOWER);

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		वापस clamp_t(अक्षर, txघातer, MIN_A_TXPOWER_3593,
			       MAX_A_TXPOWER_3593);
	अन्यथा
		वापस clamp_t(अक्षर, txघातer, MIN_A_TXPOWER, MAX_A_TXPOWER);
पूर्ण

अटल व्योम rt3883_bbp_adjust(काष्ठा rt2x00_dev *rt2x00dev,
			      काष्ठा rf_channel *rf)
अणु
	u8 bbp;

	bbp = (rf->channel > 14) ? 0x48 : 0x38;
	rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, bbp);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);

	अगर (rf->channel <= 14) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);
	पूर्ण अन्यथा अणु
		/* Disable CCK packet detection */
		rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x00);
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);

	अगर (rf->channel > 14) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x1d);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x1d);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x1d);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x2d);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x2d);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x2d);
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_channel(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा ieee80211_conf *conf,
				  काष्ठा rf_channel *rf,
				  काष्ठा channel_info *info)
अणु
	u32 reg;
	u32 tx_pin;
	u8 bbp, rfcsr;

	info->शेष_घातer1 = rt2800_txघातer_to_dev(rt2x00dev, rf->channel,
						     info->शेष_घातer1);
	info->शेष_घातer2 = rt2800_txघातer_to_dev(rt2x00dev, rf->channel,
						     info->शेष_घातer2);
	अगर (rt2x00dev->शेष_ant.tx_chain_num > 2)
		info->शेष_घातer3 =
			rt2800_txघातer_to_dev(rt2x00dev, rf->channel,
					      info->शेष_घातer3);

	चयन (rt2x00dev->chip.rt) अणु
	हाल RT3883:
		rt3883_bbp_adjust(rt2x00dev, rf);
		अवरोध;
	पूर्ण

	चयन (rt2x00dev->chip.rf) अणु
	हाल RF2020:
	हाल RF3020:
	हाल RF3021:
	हाल RF3022:
	हाल RF3320:
		rt2800_config_channel_rf3xxx(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3052:
		rt2800_config_channel_rf3052(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3053:
		rt2800_config_channel_rf3053(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3290:
		rt2800_config_channel_rf3290(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3322:
		rt2800_config_channel_rf3322(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3853:
		rt2800_config_channel_rf3853(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF3070:
	हाल RF5350:
	हाल RF5360:
	हाल RF5362:
	हाल RF5370:
	हाल RF5372:
	हाल RF5390:
	हाल RF5392:
		rt2800_config_channel_rf53xx(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF5592:
		rt2800_config_channel_rf55xx(rt2x00dev, conf, rf, info);
		अवरोध;
	हाल RF7620:
		rt2800_config_channel_rf7620(rt2x00dev, conf, rf, info);
		अवरोध;
	शेष:
		rt2800_config_channel_rf2xxx(rt2x00dev, conf, rf, info);
	पूर्ण

	अगर (rt2x00_rf(rt2x00dev, RF3070) ||
	    rt2x00_rf(rt2x00dev, RF3290) ||
	    rt2x00_rf(rt2x00dev, RF3322) ||
	    rt2x00_rf(rt2x00dev, RF5350) ||
	    rt2x00_rf(rt2x00dev, RF5360) ||
	    rt2x00_rf(rt2x00dev, RF5362) ||
	    rt2x00_rf(rt2x00dev, RF5370) ||
	    rt2x00_rf(rt2x00dev, RF5372) ||
	    rt2x00_rf(rt2x00dev, RF5390) ||
	    rt2x00_rf(rt2x00dev, RF5392)) अणु
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
		अगर (rt2x00_rf(rt2x00dev, RF3322)) अणु
			rt2x00_set_field8(&rfcsr, RF3322_RFCSR30_TX_H20M,
					  conf_is_ht40(conf));
			rt2x00_set_field8(&rfcsr, RF3322_RFCSR30_RX_H20M,
					  conf_is_ht40(conf));
		पूर्ण अन्यथा अणु
			rt2x00_set_field8(&rfcsr, RFCSR30_TX_H20M,
					  conf_is_ht40(conf));
			rt2x00_set_field8(&rfcsr, RFCSR30_RX_H20M,
					  conf_is_ht40(conf));
		पूर्ण
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);
	पूर्ण

	/*
	 * Change BBP settings
	 */

	अगर (rt2x00_rt(rt2x00dev, RT3352)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);

		rt2800_bbp_ग_लिखो(rt2x00dev, 27, 0x0);
		rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x26 + rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 27, 0x20);
		rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x26 + rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);
		rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3593)) अणु
		अगर (rf->channel > 14) अणु
			/* Disable CCK Packet detection on 5GHz */
			rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x00);
		पूर्ण अन्यथा अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);
		पूर्ण

		अगर (conf_is_ht40(conf))
			rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x04);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x34);

		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x98);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3883)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);

		अगर (rt2x00dev->शेष_ant.rx_chain_num > 1)
			rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x46);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x37 - rt2x00dev->lna_gain);
		rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0);
	पूर्ण

	अगर (rf->channel <= 14) अणु
		अगर (!rt2x00_rt(rt2x00dev, RT5390) &&
		    !rt2x00_rt(rt2x00dev, RT5392) &&
		    !rt2x00_rt(rt2x00dev, RT6352)) अणु
			अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev)) अणु
				rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);
				rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);
				rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x46);
			पूर्ण अन्यथा अणु
				अगर (rt2x00_rt(rt2x00dev, RT3593))
					rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);
				अन्यथा
					rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x84);
				rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x50);
			पूर्ण
			अगर (rt2x00_rt(rt2x00dev, RT3593) ||
			    rt2x00_rt(rt2x00dev, RT3883))
				rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x8a);
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (rt2x00_rt(rt2x00dev, RT3572))
			rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x94);
		अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3593) ||
			 rt2x00_rt(rt2x00dev, RT3883))
			rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x82);
		अन्यथा अगर (!rt2x00_rt(rt2x00dev, RT6352))
			rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0xf2);

		अगर (rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT3883))
			rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x9a);

		अगर (rt2x00_has_cap_बाह्यal_lna_a(rt2x00dev))
			rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x46);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x50);
	पूर्ण

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_BAND_CFG);
	rt2x00_set_field32(&reg, TX_BAND_CFG_HT40_MINUS, conf_is_ht40_minus(conf));
	rt2x00_set_field32(&reg, TX_BAND_CFG_A, rf->channel > 14);
	rt2x00_set_field32(&reg, TX_BAND_CFG_BG, rf->channel <= 14);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_BAND_CFG, reg);

	अगर (rt2x00_rt(rt2x00dev, RT3572))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0);

	अगर (rt2x00_rt(rt2x00dev, RT6352)) अणु
		tx_pin = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PIN_CFG);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_RFRX_EN, 1);
	पूर्ण अन्यथा अणु
		tx_pin = 0;
	पूर्ण

	चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
	हाल 3:
		/* Turn on tertiary PAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A2_EN,
				   rf->channel > 14);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G2_EN,
				   rf->channel <= 14);
		fallthrough;
	हाल 2:
		/* Turn on secondary PAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN,
				   rf->channel > 14);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN,
				   rf->channel <= 14);
		fallthrough;
	हाल 1:
		/* Turn on primary PAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN,
				   rf->channel > 14);
		अगर (rt2x00_has_cap_bt_coexist(rt2x00dev))
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
		अन्यथा
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN,
					   rf->channel <= 14);
		अवरोध;
	पूर्ण

	चयन (rt2x00dev->शेष_ant.rx_chain_num) अणु
	हाल 3:
		/* Turn on tertiary LNAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_A2_EN, 1);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_G2_EN, 1);
		fallthrough;
	हाल 2:
		/* Turn on secondary LNAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_A1_EN, 1);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_G1_EN, 1);
		fallthrough;
	हाल 1:
		/* Turn on primary LNAs */
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_A0_EN, 1);
		rt2x00_set_field32(&tx_pin, TX_PIN_CFG_LNA_PE_G0_EN, 1);
		अवरोध;
	पूर्ण

	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_RFTR_EN, 1);
	rt2x00_set_field32(&tx_pin, TX_PIN_CFG_TRSW_EN, 1);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PIN_CFG, tx_pin);

	अगर (rt2x00_rt(rt2x00dev, RT3572)) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0x80);

		/* AGC init */
		अगर (rf->channel <= 14)
			reg = 0x1c + (2 * rt2x00dev->lna_gain);
		अन्यथा
			reg = 0x22 + ((rt2x00dev->lna_gain * 5) / 3);

		rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, reg);
	पूर्ण

	अगर (rt2x00_rt(rt2x00dev, RT3593)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);

		/* Band selection */
		अगर (rt2x00_is_usb(rt2x00dev) ||
		    rt2x00_is_pcie(rt2x00dev)) अणु
			/* GPIO #8 controls all paths */
			rt2x00_set_field32(&reg, GPIO_CTRL_सूची8, 0);
			अगर (rf->channel <= 14)
				rt2x00_set_field32(&reg, GPIO_CTRL_VAL8, 1);
			अन्यथा
				rt2x00_set_field32(&reg, GPIO_CTRL_VAL8, 0);
		पूर्ण

		/* LNA PE control. */
		अगर (rt2x00_is_usb(rt2x00dev)) अणु
			/* GPIO #4 controls PE0 and PE1,
			 * GPIO #7 controls PE2
			 */
			rt2x00_set_field32(&reg, GPIO_CTRL_सूची4, 0);
			rt2x00_set_field32(&reg, GPIO_CTRL_सूची7, 0);

			rt2x00_set_field32(&reg, GPIO_CTRL_VAL4, 1);
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL7, 1);
		पूर्ण अन्यथा अगर (rt2x00_is_pcie(rt2x00dev)) अणु
			/* GPIO #4 controls PE0, PE1 and PE2 */
			rt2x00_set_field32(&reg, GPIO_CTRL_सूची4, 0);
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL4, 1);
		पूर्ण

		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_CTRL, reg);

		/* AGC init */
		अगर (rf->channel <= 14)
			reg = 0x1c + 2 * rt2x00dev->lna_gain;
		अन्यथा
			reg = 0x22 + ((rt2x00dev->lna_gain * 5) / 3);

		rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, reg);

		usleep_range(1000, 1500);
	पूर्ण

	अगर (rt2x00_rt(rt2x00dev, RT3883)) अणु
		अगर (!conf_is_ht40(conf))
			rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x34);
		अन्यथा
			rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x04);

		/* AGC init */
		अगर (rf->channel <= 14)
			reg = 0x2e + rt2x00dev->lna_gain;
		अन्यथा
			reg = 0x20 + ((rt2x00dev->lna_gain * 5) / 3);

		rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, reg);

		usleep_range(1000, 1500);
	पूर्ण

	अगर (rt2x00_rt(rt2x00dev, RT5592) || rt2x00_rt(rt2x00dev, RT6352)) अणु
		reg = 0x10;
		अगर (!conf_is_ht40(conf)) अणु
			अगर (rt2x00_rt(rt2x00dev, RT6352) &&
			    rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev)) अणु
				reg |= 0x5;
			पूर्ण अन्यथा अणु
				reg |= 0xa;
			पूर्ण
		पूर्ण
		rt2800_bbp_ग_लिखो(rt2x00dev, 195, 141);
		rt2800_bbp_ग_लिखो(rt2x00dev, 196, reg);

		/* AGC init.
		 * Despite the venकरोr driver using dअगरferent values here क्रम
		 * RT6352 chip, we use 0x1c क्रम now. This may have to be changed
		 * once TSSI got implemented.
		 */
		reg = (rf->channel <= 14 ? 0x1c : 0x24) + 2*rt2x00dev->lna_gain;
		rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, reg);

		rt2800_iq_calibrate(rt2x00dev, rf->channel);
	पूर्ण

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 4);
	rt2x00_set_field8(&bbp, BBP4_BANDWIDTH, 2 * conf_is_ht40(conf));
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, bbp);

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&bbp, BBP3_HT40_MINUS, conf_is_ht40_minus(conf));
	rt2800_bbp_ग_लिखो(rt2x00dev, 3, bbp);

	अगर (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C)) अणु
		अगर (conf_is_ht40(conf)) अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x1a);
			rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);
			rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x16);
		पूर्ण अन्यथा अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x16);
			rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x08);
			rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x11);
		पूर्ण
	पूर्ण

	usleep_range(1000, 1500);

	/*
	 * Clear channel statistic counters
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_IDLE_STA);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_BUSY_STA);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_BUSY_STA_SEC);

	/*
	 * Clear update flag
	 */
	अगर (rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT5350)) अणु
		bbp = rt2800_bbp_पढ़ो(rt2x00dev, 49);
		rt2x00_set_field8(&bbp, BBP49_UPDATE_FLAG, 0);
		rt2800_bbp_ग_लिखो(rt2x00dev, 49, bbp);
	पूर्ण
पूर्ण

अटल पूर्णांक rt2800_get_gain_calibration_delta(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 tssi_bounds[9];
	u8 current_tssi;
	u16 eeprom;
	u8 step;
	पूर्णांक i;

	/*
	 * First check अगर temperature compensation is supported.
	 */
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
	अगर (!rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_EXTERNAL_TX_ALC))
		वापस 0;

	/*
	 * Read TSSI boundaries क्रम temperature compensation from
	 * the EEPROM.
	 *
	 * Array idx               0    1    2    3    4    5    6    7    8
	 * Matching Delta value   -4   -3   -2   -1    0   +1   +2   +3   +4
	 * Example TSSI bounds  0xF0 0xD0 0xB5 0xA0 0x88 0x45 0x25 0x15 0x00
	 */
	अगर (rt2x00dev->curr_band == NL80211_BAND_2GHZ) अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_BG1);
		tssi_bounds[0] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG1_MINUS4);
		tssi_bounds[1] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG1_MINUS3);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_BG2);
		tssi_bounds[2] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG2_MINUS2);
		tssi_bounds[3] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG2_MINUS1);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_BG3);
		tssi_bounds[4] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG3_REF);
		tssi_bounds[5] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG3_PLUS1);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_BG4);
		tssi_bounds[6] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG4_PLUS2);
		tssi_bounds[7] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG4_PLUS3);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_BG5);
		tssi_bounds[8] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_BG5_PLUS4);

		step = rt2x00_get_field16(eeprom,
					  EEPROM_TSSI_BOUND_BG5_AGC_STEP);
	पूर्ण अन्यथा अणु
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_A1);
		tssi_bounds[0] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A1_MINUS4);
		tssi_bounds[1] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A1_MINUS3);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_A2);
		tssi_bounds[2] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A2_MINUS2);
		tssi_bounds[3] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A2_MINUS1);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_A3);
		tssi_bounds[4] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A3_REF);
		tssi_bounds[5] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A3_PLUS1);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_A4);
		tssi_bounds[6] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A4_PLUS2);
		tssi_bounds[7] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A4_PLUS3);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TSSI_BOUND_A5);
		tssi_bounds[8] = rt2x00_get_field16(eeprom,
					EEPROM_TSSI_BOUND_A5_PLUS4);

		step = rt2x00_get_field16(eeprom,
					  EEPROM_TSSI_BOUND_A5_AGC_STEP);
	पूर्ण

	/*
	 * Check अगर temperature compensation is supported.
	 */
	अगर (tssi_bounds[4] == 0xff || step == 0xff)
		वापस 0;

	/*
	 * Read current TSSI (BBP 49).
	 */
	current_tssi = rt2800_bbp_पढ़ो(rt2x00dev, 49);

	/*
	 * Compare TSSI value (BBP49) with the compensation boundaries
	 * from the EEPROM and increase or decrease tx घातer.
	 */
	क्रम (i = 0; i <= 3; i++) अणु
		अगर (current_tssi > tssi_bounds[i])
			अवरोध;
	पूर्ण

	अगर (i == 4) अणु
		क्रम (i = 8; i >= 5; i--) अणु
			अगर (current_tssi < tssi_bounds[i])
				अवरोध;
		पूर्ण
	पूर्ण

	वापस (i - 4) * step;
पूर्ण

अटल पूर्णांक rt2800_get_txघातer_bw_comp(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत nl80211_band band)
अणु
	u16 eeprom;
	u8 comp_en;
	u8 comp_type;
	पूर्णांक comp_value = 0;

	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TXPOWER_DELTA);

	/*
	 * HT40 compensation not required.
	 */
	अगर (eeprom == 0xffff ||
	    !test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags))
		वापस 0;

	अगर (band == NL80211_BAND_2GHZ) अणु
		comp_en = rt2x00_get_field16(eeprom,
				 EEPROM_TXPOWER_DELTA_ENABLE_2G);
		अगर (comp_en) अणु
			comp_type = rt2x00_get_field16(eeprom,
					   EEPROM_TXPOWER_DELTA_TYPE_2G);
			comp_value = rt2x00_get_field16(eeprom,
					    EEPROM_TXPOWER_DELTA_VALUE_2G);
			अगर (!comp_type)
				comp_value = -comp_value;
		पूर्ण
	पूर्ण अन्यथा अणु
		comp_en = rt2x00_get_field16(eeprom,
				 EEPROM_TXPOWER_DELTA_ENABLE_5G);
		अगर (comp_en) अणु
			comp_type = rt2x00_get_field16(eeprom,
					   EEPROM_TXPOWER_DELTA_TYPE_5G);
			comp_value = rt2x00_get_field16(eeprom,
					    EEPROM_TXPOWER_DELTA_VALUE_5G);
			अगर (!comp_type)
				comp_value = -comp_value;
		पूर्ण
	पूर्ण

	वापस comp_value;
पूर्ण

अटल पूर्णांक rt2800_get_txघातer_reg_delta(काष्ठा rt2x00_dev *rt2x00dev,
					पूर्णांक घातer_level, पूर्णांक max_घातer)
अणु
	पूर्णांक delta;

	अगर (rt2x00_has_cap_घातer_limit(rt2x00dev))
		वापस 0;

	/*
	 * XXX: We करोn't know the maximum transmit घातer of our hardware since
	 * the EEPROM करोesn't expose it. We only know that we are calibrated
	 * to 100% tx घातer.
	 *
	 * Hence, we assume the regulatory limit that cfg80211 calulated क्रम
	 * the current channel is our maximum and अगर we are requested to lower
	 * the value we just reduce our tx घातer accordingly.
	 */
	delta = घातer_level - max_घातer;
	वापस min(delta, 0);
पूर्ण

अटल u8 rt2800_compensate_txघातer(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक is_rate_b,
				   क्रमागत nl80211_band band, पूर्णांक घातer_level,
				   u8 txघातer, पूर्णांक delta)
अणु
	u16 eeprom;
	u8 criterion;
	u8 eirp_txघातer;
	u8 eirp_txघातer_criterion;
	u8 reg_limit;

	अगर (rt2x00_rt(rt2x00dev, RT3593))
		वापस min_t(u8, txघातer, 0xc);

	अगर (rt2x00_rt(rt2x00dev, RT3883))
		वापस min_t(u8, txघातer, 0xf);

	अगर (rt2x00_has_cap_घातer_limit(rt2x00dev)) अणु
		/*
		 * Check अगर eirp txघातer exceed txघातer_limit.
		 * We use OFDM 6M as criterion and its eirp txघातer
		 * is stored at EEPROM_EIRP_MAX_TX_POWER.
		 * .11b data rate need add additional 4dbm
		 * when calculating eirp txघातer.
		 */
		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       1);
		criterion = rt2x00_get_field16(eeprom,
					       EEPROM_TXPOWER_BYRATE_RATE0);

		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_EIRP_MAX_TX_POWER);

		अगर (band == NL80211_BAND_2GHZ)
			eirp_txघातer_criterion = rt2x00_get_field16(eeprom,
						 EEPROM_EIRP_MAX_TX_POWER_2GHZ);
		अन्यथा
			eirp_txघातer_criterion = rt2x00_get_field16(eeprom,
						 EEPROM_EIRP_MAX_TX_POWER_5GHZ);

		eirp_txघातer = eirp_txघातer_criterion + (txघातer - criterion) +
			       (is_rate_b ? 4 : 0) + delta;

		reg_limit = (eirp_txघातer > घातer_level) ?
					(eirp_txघातer - घातer_level) : 0;
	पूर्ण अन्यथा
		reg_limit = 0;

	txघातer = max(0, txघातer + delta - reg_limit);
	वापस min_t(u8, txघातer, 0xc);
पूर्ण


क्रमागत अणु
	TX_PWR_CFG_0_IDX,
	TX_PWR_CFG_1_IDX,
	TX_PWR_CFG_2_IDX,
	TX_PWR_CFG_3_IDX,
	TX_PWR_CFG_4_IDX,
	TX_PWR_CFG_5_IDX,
	TX_PWR_CFG_6_IDX,
	TX_PWR_CFG_7_IDX,
	TX_PWR_CFG_8_IDX,
	TX_PWR_CFG_9_IDX,
	TX_PWR_CFG_0_EXT_IDX,
	TX_PWR_CFG_1_EXT_IDX,
	TX_PWR_CFG_2_EXT_IDX,
	TX_PWR_CFG_3_EXT_IDX,
	TX_PWR_CFG_4_EXT_IDX,
	TX_PWR_CFG_IDX_COUNT,
पूर्ण;

अटल व्योम rt2800_config_txघातer_rt3593(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_channel *chan,
					 पूर्णांक घातer_level)
अणु
	u8 txघातer;
	u16 eeprom;
	u32 regs[TX_PWR_CFG_IDX_COUNT];
	अचिन्हित पूर्णांक offset;
	क्रमागत nl80211_band band = chan->band;
	पूर्णांक delta;
	पूर्णांक i;

	स_रखो(regs, '\0', माप(regs));

	/* TODO: adapt TX घातer reduction from the rt28xx code */

	/* calculate temperature compensation delta */
	delta = rt2800_get_gain_calibration_delta(rt2x00dev);

	अगर (band == NL80211_BAND_5GHZ)
		offset = 16;
	अन्यथा
		offset = 0;

	अगर (test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags))
		offset += 8;

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset);

	/* CCK 1MBS,2MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 1, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_CCK1_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_CCK1_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_EXT_IDX],
			   TX_PWR_CFG_0_EXT_CCK1_CH2, txघातer);

	/* CCK 5.5MBS,11MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 1, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_CCK5_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_CCK5_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_EXT_IDX],
			   TX_PWR_CFG_0_EXT_CCK5_CH2, txघातer);

	/* OFDM 6MBS,9MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_OFDM6_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_OFDM6_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_EXT_IDX],
			   TX_PWR_CFG_0_EXT_OFDM6_CH2, txघातer);

	/* OFDM 12MBS,18MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE3);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_OFDM12_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_IDX],
			   TX_PWR_CFG_0_OFDM12_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_0_EXT_IDX],
			   TX_PWR_CFG_0_EXT_OFDM12_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 1);

	/* OFDM 24MBS,36MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_OFDM24_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_OFDM24_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_EXT_IDX],
			   TX_PWR_CFG_1_EXT_OFDM24_CH2, txघातer);

	/* OFDM 48MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_OFDM48_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_OFDM48_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_EXT_IDX],
			   TX_PWR_CFG_1_EXT_OFDM48_CH2, txघातer);

	/* OFDM 54MBS */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_OFDM54_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_OFDM54_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_OFDM54_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 2);

	/* MCS 0,1 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_MCS0_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_MCS0_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_EXT_IDX],
			   TX_PWR_CFG_1_EXT_MCS0_CH2, txघातer);

	/* MCS 2,3 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_MCS2_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_IDX],
			   TX_PWR_CFG_1_MCS2_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_1_EXT_IDX],
			   TX_PWR_CFG_1_EXT_MCS2_CH2, txघातer);

	/* MCS 4,5 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS4_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS4_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_EXT_IDX],
			   TX_PWR_CFG_2_EXT_MCS4_CH2, txघातer);

	/* MCS 6 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE3);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS6_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS6_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_EXT_IDX],
			   TX_PWR_CFG_2_EXT_MCS6_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 3);

	/* MCS 7 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_MCS7_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_MCS7_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_7_IDX],
			   TX_PWR_CFG_7_MCS7_CH2, txघातer);

	/* MCS 8,9 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS8_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS8_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_EXT_IDX],
			   TX_PWR_CFG_2_EXT_MCS8_CH2, txघातer);

	/* MCS 10,11 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS10_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_IDX],
			   TX_PWR_CFG_2_MCS10_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_2_EXT_IDX],
			   TX_PWR_CFG_2_EXT_MCS10_CH2, txघातer);

	/* MCS 12,13 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE3);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_MCS12_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_MCS12_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_EXT_IDX],
			   TX_PWR_CFG_3_EXT_MCS12_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 4);

	/* MCS 14 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_MCS14_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_MCS14_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_EXT_IDX],
			   TX_PWR_CFG_3_EXT_MCS14_CH2, txघातer);

	/* MCS 15 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS15_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS15_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS15_CH2, txघातer);

	/* MCS 16,17 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS16_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS16_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS16_CH2, txघातer);

	/* MCS 18,19 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE3);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS18_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS18_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_5_IDX],
			   TX_PWR_CFG_5_MCS18_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 5);

	/* MCS 20,21 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS20_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS20_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS20_CH2, txघातer);

	/* MCS 22 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS22_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS22_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_6_IDX],
			   TX_PWR_CFG_6_MCS22_CH2, txघातer);

	/* MCS 23 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS23_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS23_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_8_IDX],
			   TX_PWR_CFG_8_MCS23_CH2, txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 6);

	/* STBC, MCS 0,1 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_STBC0_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_STBC0_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_EXT_IDX],
			   TX_PWR_CFG_3_EXT_STBC0_CH2, txघातer);

	/* STBC, MCS 2,3 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE1);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_STBC2_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_IDX],
			   TX_PWR_CFG_3_STBC2_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_3_EXT_IDX],
			   TX_PWR_CFG_3_EXT_STBC2_CH2, txघातer);

	/* STBC, MCS 4,5 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE2);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_IDX], TX_PWR_CFG_RATE0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_IDX], TX_PWR_CFG_RATE1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_EXT_IDX], TX_PWR_CFG_RATE0,
			   txघातer);

	/* STBC, MCS 6 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE3);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_IDX], TX_PWR_CFG_RATE2, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_IDX], TX_PWR_CFG_RATE3, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_4_EXT_IDX], TX_PWR_CFG_RATE2,
			   txघातer);

	/* पढ़ो the next four txघातer values */
	eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev, EEPROM_TXPOWER_BYRATE,
					       offset + 7);

	/* STBC, MCS 7 */
	txघातer = rt2x00_get_field16(eeprom, EEPROM_TXPOWER_BYRATE_RATE0);
	txघातer = rt2800_compensate_txघातer(rt2x00dev, 0, band, घातer_level,
					    txघातer, delta);
	rt2x00_set_field32(&regs[TX_PWR_CFG_9_IDX],
			   TX_PWR_CFG_9_STBC7_CH0, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_9_IDX],
			   TX_PWR_CFG_9_STBC7_CH1, txघातer);
	rt2x00_set_field32(&regs[TX_PWR_CFG_9_IDX],
			   TX_PWR_CFG_9_STBC7_CH2, txघातer);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_0, regs[TX_PWR_CFG_0_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_1, regs[TX_PWR_CFG_1_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_2, regs[TX_PWR_CFG_2_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_3, regs[TX_PWR_CFG_3_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_4, regs[TX_PWR_CFG_4_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_5, regs[TX_PWR_CFG_5_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_6, regs[TX_PWR_CFG_6_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_7, regs[TX_PWR_CFG_7_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_8, regs[TX_PWR_CFG_8_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_9, regs[TX_PWR_CFG_9_IDX]);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_0_EXT,
			      regs[TX_PWR_CFG_0_EXT_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_1_EXT,
			      regs[TX_PWR_CFG_1_EXT_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_2_EXT,
			      regs[TX_PWR_CFG_2_EXT_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_3_EXT,
			      regs[TX_PWR_CFG_3_EXT_IDX]);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_4_EXT,
			      regs[TX_PWR_CFG_4_EXT_IDX]);

	क्रम (i = 0; i < TX_PWR_CFG_IDX_COUNT; i++)
		rt2x00_dbg(rt2x00dev,
			   "band:%cGHz, BW:%c0MHz, TX_PWR_CFG_%d%s = %08lx\n",
			   (band == NL80211_BAND_5GHZ) ? '5' : '2',
			   (test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags)) ?
								'4' : '2',
			   (i > TX_PWR_CFG_9_IDX) ?
					(i - TX_PWR_CFG_9_IDX - 1) : i,
			   (i > TX_PWR_CFG_9_IDX) ? "_EXT" : "",
			   (अचिन्हित दीर्घ) regs[i]);
पूर्ण

अटल व्योम rt2800_config_txघातer_rt6352(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_channel *chan,
					 पूर्णांक घातer_level)
अणु
	u32 reg, pwreg;
	u16 eeprom;
	u32 data, gdata;
	u8 t, i;
	क्रमागत nl80211_band band = chan->band;
	पूर्णांक delta;

	/* Warn user अगर bw_comp is set in EEPROM */
	delta = rt2800_get_txघातer_bw_comp(rt2x00dev, band);

	अगर (delta)
		rt2x00_warn(rt2x00dev, "ignoring EEPROM HT40 power delta: %d\n",
			    delta);

	/* populate TX_PWR_CFG_0 up to TX_PWR_CFG_4 from EEPROM क्रम HT20, limit
	 * value to 0x3f and replace 0x20 by 0x21 as this is what the venकरोr
	 * driver करोes as well, though it looks kinda wrong.
	 * Maybe some misunderstanding of what a चिन्हित 8-bit value is? Maybe
	 * the hardware has a problem handling 0x20, and as the code initially
	 * used a fixed offset between HT20 and HT40 rates they had to work-
	 * around that issue and most likely just क्रमgot about it later on.
	 * Maybe we should use rt2800_get_txघातer_bw_comp() here as well,
	 * however, the corresponding EEPROM value is not respected by the
	 * venकरोr driver, so maybe this is rather being taken care of the
	 * TXALC and the driver करोesn't need to handle it...?
	 * Though this is all very awkward, just करो as they did, as that's what
	 * board venकरोrs expected when they populated the EEPROM...
	 */
	क्रम (i = 0; i < 5; i++) अणु
		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       i * 2);

		data = eeprom;

		t = eeprom & 0x3f;
		अगर (t == 32)
			t++;

		gdata = t;

		t = (eeprom & 0x3f00) >> 8;
		अगर (t == 32)
			t++;

		gdata |= (t << 8);

		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       (i * 2) + 1);

		t = eeprom & 0x3f;
		अगर (t == 32)
			t++;

		gdata |= (t << 16);

		t = (eeprom & 0x3f00) >> 8;
		अगर (t == 32)
			t++;

		gdata |= (t << 24);
		data |= (eeprom << 16);

		अगर (!test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags)) अणु
			/* HT20 */
			अगर (data != 0xffffffff)
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev,
						      TX_PWR_CFG_0 + (i * 4),
						      data);
		पूर्ण अन्यथा अणु
			/* HT40 */
			अगर (gdata != 0xffffffff)
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev,
						      TX_PWR_CFG_0 + (i * 4),
						      gdata);
		पूर्ण
	पूर्ण

	/* Aparently Ralink ran out of space in the BYRATE calibration section
	 * of the EERPOM which is copied to the corresponding TX_PWR_CFG_x
	 * रेजिस्टरs. As recent 2T chips use 8-bit instead of 4-bit values क्रम
	 * घातer-offsets more space would be needed. Ralink decided to keep the
	 * EEPROM layout untouched and rather have some shared values covering
	 * multiple bitrates.
	 * Populate the रेजिस्टरs not covered by the EEPROM in the same way the
	 * venकरोr driver करोes.
	 */

	/* For OFDM 54MBS use value from OFDM 48MBS */
	pwreg = 0;
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PWR_CFG_1);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_1B_48MBS);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_7B_54MBS, t);

	/* For MCS 7 use value from MCS 6 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PWR_CFG_2);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_2B_MCS6_MCS7);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_7B_MCS7, t);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_7, pwreg);

	/* For MCS 15 use value from MCS 14 */
	pwreg = 0;
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PWR_CFG_3);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_3B_MCS14);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_8B_MCS15, t);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_8, pwreg);

	/* For STBC MCS 7 use value from STBC MCS 6 */
	pwreg = 0;
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PWR_CFG_4);
	t = rt2x00_get_field32(reg, TX_PWR_CFG_4B_STBC_MCS6);
	rt2x00_set_field32(&pwreg, TX_PWR_CFG_9B_STBC_MCS7, t);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PWR_CFG_9, pwreg);

	rt2800_config_alc(rt2x00dev, chan, घातer_level);

	/* TODO: temperature compensation code! */
पूर्ण

/*
 * We configure transmit घातer using MAC TX_PWR_CFG_अणु0,...,Nपूर्ण रेजिस्टरs and
 * BBP R1 रेजिस्टर. TX_PWR_CFG_X allow to configure per rate TX घातer values,
 * 4 bits क्रम each rate (tune from 0 to 15 dBm). BBP_R1 controls transmit घातer
 * क्रम all rates, but allow to set only 4 discrete values: -12, -6, 0 and 6 dBm.
 * Reference per rate transmit घातer values are located in the EEPROM at
 * EEPROM_TXPOWER_BYRATE offset. We adjust them and BBP R1 settings according to
 * current conditions (i.e. band, bandwidth, temperature, user settings).
 */
अटल व्योम rt2800_config_txघातer_rt28xx(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा ieee80211_channel *chan,
					 पूर्णांक घातer_level)
अणु
	u8 txघातer, r1;
	u16 eeprom;
	u32 reg, offset;
	पूर्णांक i, is_rate_b, delta, घातer_ctrl;
	क्रमागत nl80211_band band = chan->band;

	/*
	 * Calculate HT40 compensation. For 40MHz we need to add or subtract
	 * value पढ़ो from EEPROM (dअगरferent क्रम 2GHz and क्रम 5GHz).
	 */
	delta = rt2800_get_txघातer_bw_comp(rt2x00dev, band);

	/*
	 * Calculate temperature compensation. Depends on measurement of current
	 * TSSI (Transmitter Signal Strength Indication) we know TX घातer (due
	 * to temperature or maybe other factors) is smaller or bigger than
	 * expected. We adjust it, based on TSSI reference and boundaries values
	 * provided in EEPROM.
	 */
	चयन (rt2x00dev->chip.rt) अणु
	हाल RT2860:
	हाल RT2872:
	हाल RT2883:
	हाल RT3070:
	हाल RT3071:
	हाल RT3090:
	हाल RT3572:
		delta += rt2800_get_gain_calibration_delta(rt2x00dev);
		अवरोध;
	शेष:
		/* TODO: temperature compensation code क्रम other chips. */
		अवरोध;
	पूर्ण

	/*
	 * Decrease घातer according to user settings, on devices with unknown
	 * maximum tx घातer. For other devices we take user घातer_level पूर्णांकo
	 * consideration on rt2800_compensate_txघातer().
	 */
	delta += rt2800_get_txघातer_reg_delta(rt2x00dev, घातer_level,
					      chan->max_घातer);

	/*
	 * BBP_R1 controls TX घातer क्रम all rates, it allow to set the following
	 * gains -12, -6, 0, +6 dBm by setting values 2, 1, 0, 3 respectively.
	 *
	 * TODO: we करो not use +6 dBm option to करो not increase घातer beyond
	 * regulatory limit, however this could be utilized क्रम devices with
	 * CAPABILITY_POWER_LIMIT.
	 */
	अगर (delta <= -12) अणु
		घातer_ctrl = 2;
		delta += 12;
	पूर्ण अन्यथा अगर (delta <= -6) अणु
		घातer_ctrl = 1;
		delta += 6;
	पूर्ण अन्यथा अणु
		घातer_ctrl = 0;
	पूर्ण
	r1 = rt2800_bbp_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&r1, BBP1_TX_POWER_CTRL, घातer_ctrl);
	rt2800_bbp_ग_लिखो(rt2x00dev, 1, r1);

	offset = TX_PWR_CFG_0;

	क्रम (i = 0; i < EEPROM_TXPOWER_BYRATE_SIZE; i += 2) अणु
		/* just to be safe */
		अगर (offset > TX_PWR_CFG_4)
			अवरोध;

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);

		/* पढ़ो the next four txघातer values */
		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       i);

		is_rate_b = i ? 0 : 1;
		/*
		 * TX_PWR_CFG_0: 1MBS, TX_PWR_CFG_1: 24MBS,
		 * TX_PWR_CFG_2: MCS4, TX_PWR_CFG_3: MCS12,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE0);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE0, txघातer);

		/*
		 * TX_PWR_CFG_0: 2MBS, TX_PWR_CFG_1: 36MBS,
		 * TX_PWR_CFG_2: MCS5, TX_PWR_CFG_3: MCS13,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE1);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE1, txघातer);

		/*
		 * TX_PWR_CFG_0: 5.5MBS, TX_PWR_CFG_1: 48MBS,
		 * TX_PWR_CFG_2: MCS6,  TX_PWR_CFG_3: MCS14,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE2);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE2, txघातer);

		/*
		 * TX_PWR_CFG_0: 11MBS, TX_PWR_CFG_1: 54MBS,
		 * TX_PWR_CFG_2: MCS7,  TX_PWR_CFG_3: MCS15,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE3);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE3, txघातer);

		/* पढ़ो the next four txघातer values */
		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_TXPOWER_BYRATE,
						       i + 1);

		is_rate_b = 0;
		/*
		 * TX_PWR_CFG_0: 6MBS, TX_PWR_CFG_1: MCS0,
		 * TX_PWR_CFG_2: MCS8, TX_PWR_CFG_3: unknown,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE0);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE4, txघातer);

		/*
		 * TX_PWR_CFG_0: 9MBS, TX_PWR_CFG_1: MCS1,
		 * TX_PWR_CFG_2: MCS9, TX_PWR_CFG_3: unknown,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE1);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE5, txघातer);

		/*
		 * TX_PWR_CFG_0: 12MBS, TX_PWR_CFG_1: MCS2,
		 * TX_PWR_CFG_2: MCS10, TX_PWR_CFG_3: unknown,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE2);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE6, txघातer);

		/*
		 * TX_PWR_CFG_0: 18MBS, TX_PWR_CFG_1: MCS3,
		 * TX_PWR_CFG_2: MCS11, TX_PWR_CFG_3: unknown,
		 * TX_PWR_CFG_4: unknown
		 */
		txघातer = rt2x00_get_field16(eeprom,
					     EEPROM_TXPOWER_BYRATE_RATE3);
		txघातer = rt2800_compensate_txघातer(rt2x00dev, is_rate_b, band,
					     घातer_level, txघातer, delta);
		rt2x00_set_field32(&reg, TX_PWR_CFG_RATE7, txघातer);

		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

		/* next TX_PWR_CFG रेजिस्टर */
		offset += 4;
	पूर्ण
पूर्ण

अटल व्योम rt2800_config_txघातer(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा ieee80211_channel *chan,
				  पूर्णांक घातer_level)
अणु
	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		rt2800_config_txघातer_rt3593(rt2x00dev, chan, घातer_level);
	अन्यथा अगर (rt2x00_rt(rt2x00dev, RT6352))
		rt2800_config_txघातer_rt6352(rt2x00dev, chan, घातer_level);
	अन्यथा
		rt2800_config_txघातer_rt28xx(rt2x00dev, chan, घातer_level);
पूर्ण

व्योम rt2800_gain_calibration(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_config_txघातer(rt2x00dev, rt2x00dev->hw->conf.chandef.chan,
			      rt2x00dev->tx_घातer);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_gain_calibration);

व्योम rt2800_vco_calibration(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32	tx_pin;
	u8	rfcsr;
	अचिन्हित दीर्घ min_sleep = 0;

	/*
	 * A voltage-controlled oscillator(VCO) is an electronic oscillator
	 * deचिन्हित to be controlled in oscillation frequency by a voltage
	 * input. Maybe the temperature will affect the frequency of
	 * oscillation to be shअगरted. The VCO calibration will be called
	 * periodically to adjust the frequency to be precision.
	*/

	tx_pin = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PIN_CFG);
	tx_pin &= TX_PIN_CFG_PA_PE_DISABLE;
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PIN_CFG, tx_pin);

	चयन (rt2x00dev->chip.rf) अणु
	हाल RF2020:
	हाल RF3020:
	हाल RF3021:
	हाल RF3022:
	हाल RF3320:
	हाल RF3052:
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 7);
		rt2x00_set_field8(&rfcsr, RFCSR7_RF_TUNING, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, rfcsr);
		अवरोध;
	हाल RF3053:
	हाल RF3070:
	हाल RF3290:
	हाल RF3853:
	हाल RF5350:
	हाल RF5360:
	हाल RF5362:
	हाल RF5370:
	हाल RF5372:
	हाल RF5390:
	हाल RF5392:
	हाल RF5592:
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 3);
		rt2x00_set_field8(&rfcsr, RFCSR3_VCOCAL_EN, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, rfcsr);
		min_sleep = 1000;
		अवरोध;
	हाल RF7620:
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x40);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x0C);
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 4);
		rt2x00_set_field8(&rfcsr, RFCSR4_VCOCAL_EN, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, rfcsr);
		min_sleep = 2000;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Not supported RF chipset %x for VCO recalibration",
			  rt2x00dev->chip.rf);
		वापस;
	पूर्ण

	अगर (min_sleep > 0)
		usleep_range(min_sleep, min_sleep * 2);

	tx_pin = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_PIN_CFG);
	अगर (rt2x00dev->rf_channel <= 14) अणु
		चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
		हाल 3:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G2_EN, 1);
			fallthrough;
		हाल 2:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G1_EN, 1);
			fallthrough;
		हाल 1:
		शेष:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_G0_EN, 1);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rt2x00dev->शेष_ant.tx_chain_num) अणु
		हाल 3:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A2_EN, 1);
			fallthrough;
		हाल 2:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A1_EN, 1);
			fallthrough;
		हाल 1:
		शेष:
			rt2x00_set_field32(&tx_pin, TX_PIN_CFG_PA_PE_A0_EN, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_PIN_CFG, tx_pin);

	अगर (rt2x00_rt(rt2x00dev, RT6352)) अणु
		अगर (rt2x00dev->शेष_ant.rx_chain_num == 1) अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x07);
			rt2800_bbp_ग_लिखो(rt2x00dev, 95, 0x1A);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 128);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0xA0);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 170);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0x12);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 171);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0x10);
		पूर्ण अन्यथा अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x06);
			rt2800_bbp_ग_लिखो(rt2x00dev, 95, 0x9A);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 128);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0xE0);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 170);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0x30);
			rt2800_bbp_ग_लिखो(rt2x00dev, 195, 171);
			rt2800_bbp_ग_लिखो(rt2x00dev, 196, 0x30);
		पूर्ण

		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev)) अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x68);
			rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x4C);
			rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x1C);
			rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x0C);
			rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0xB6);
		पूर्ण

		/* On 11A, We should delay and रुको RF/BBP to be stable
		 * and the appropriate समय should be 1000 micro seconds
		 * 2005/06/05 - On 11G, we also need this delay समय.
		 * Otherwise it's dअगरficult to pass the WHQL.
		 */
		usleep_range(1000, 1500);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_vco_calibration);

अटल व्योम rt2800_config_retry_limit(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा rt2x00lib_conf *libconf)
अणु
	u32 reg;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_RTY_CFG);
	rt2x00_set_field32(&reg, TX_RTY_CFG_SHORT_RTY_LIMIT,
			   libconf->conf->लघु_frame_max_tx_count);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_LIMIT,
			   libconf->conf->दीर्घ_frame_max_tx_count);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RTY_CFG, reg);
पूर्ण

अटल व्योम rt2800_config_ps(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00lib_conf *libconf)
अणु
	क्रमागत dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	अगर (state == STATE_SLEEP) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTOWAKEUP_CFG, 0);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AUTOWAKEUP_CFG);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_AUTO_LEAD_TIME, 5);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_TBCN_BEFORE_WAKE,
				   libconf->conf->listen_पूर्णांकerval - 1);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_AUTOWAKE, 1);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTOWAKEUP_CFG, reg);

		rt2x00dev->ops->lib->set_device_state(rt2x00dev, state);
	पूर्ण अन्यथा अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AUTOWAKEUP_CFG);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_AUTO_LEAD_TIME, 0);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_TBCN_BEFORE_WAKE, 0);
		rt2x00_set_field32(&reg, AUTOWAKEUP_CFG_AUTOWAKE, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTOWAKEUP_CFG, reg);

		rt2x00dev->ops->lib->set_device_state(rt2x00dev, state);
	पूर्ण
पूर्ण

व्योम rt2800_config(काष्ठा rt2x00_dev *rt2x00dev,
		   काष्ठा rt2x00lib_conf *libconf,
		   स्थिर अचिन्हित पूर्णांक flags)
अणु
	/* Always recalculate LNA gain beक्रमe changing configuration */
	rt2800_config_lna_gain(rt2x00dev, libconf);

	अगर (flags & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		/*
		 * To provide correct survey data क्रम survey-based ACS algorithm
		 * we have to save survey data क्रम current channel beक्रमe चयनing.
		 */
		rt2800_update_survey(rt2x00dev);

		rt2800_config_channel(rt2x00dev, libconf->conf,
				      &libconf->rf, &libconf->channel);
		rt2800_config_txघातer(rt2x00dev, libconf->conf->chandef.chan,
				      libconf->conf->घातer_level);
	पूर्ण
	अगर (flags & IEEE80211_CONF_CHANGE_POWER)
		rt2800_config_txघातer(rt2x00dev, libconf->conf->chandef.chan,
				      libconf->conf->घातer_level);
	अगर (flags & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		rt2800_config_retry_limit(rt2x00dev, libconf);
	अगर (flags & IEEE80211_CONF_CHANGE_PS)
		rt2800_config_ps(rt2x00dev, libconf);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_config);

/*
 * Link tuning
 */
व्योम rt2800_link_stats(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual)
अणु
	u32 reg;

	/*
	 * Update FCS error count from रेजिस्टर.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RX_STA_CNT0);
	qual->rx_failed = rt2x00_get_field32(reg, RX_STA_CNT0_CRC_ERR);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_link_stats);

अटल u8 rt2800_get_शेष_vgc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 vgc;

	अगर (rt2x00dev->curr_band == NL80211_BAND_2GHZ) अणु
		अगर (rt2x00_rt(rt2x00dev, RT3070) ||
		    rt2x00_rt(rt2x00dev, RT3071) ||
		    rt2x00_rt(rt2x00dev, RT3090) ||
		    rt2x00_rt(rt2x00dev, RT3290) ||
		    rt2x00_rt(rt2x00dev, RT3390) ||
		    rt2x00_rt(rt2x00dev, RT3572) ||
		    rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT5390) ||
		    rt2x00_rt(rt2x00dev, RT5392) ||
		    rt2x00_rt(rt2x00dev, RT5592) ||
		    rt2x00_rt(rt2x00dev, RT6352))
			vgc = 0x1c + (2 * rt2x00dev->lna_gain);
		अन्यथा
			vgc = 0x2e + rt2x00dev->lna_gain;
	पूर्ण अन्यथा अणु /* 5GHZ band */
		अगर (rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT3883))
			vgc = 0x20 + (rt2x00dev->lna_gain * 5) / 3;
		अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5592))
			vgc = 0x24 + (2 * rt2x00dev->lna_gain);
		अन्यथा अणु
			अगर (!test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags))
				vgc = 0x32 + (rt2x00dev->lna_gain * 5) / 3;
			अन्यथा
				vgc = 0x3a + (rt2x00dev->lna_gain * 5) / 3;
		पूर्ण
	पूर्ण

	वापस vgc;
पूर्ण

अटल अंतरभूत व्योम rt2800_set_vgc(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा link_qual *qual, u8 vgc_level)
अणु
	अगर (qual->vgc_level != vgc_level) अणु
		अगर (rt2x00_rt(rt2x00dev, RT3572) ||
		    rt2x00_rt(rt2x00dev, RT3593) ||
		    rt2x00_rt(rt2x00dev, RT3883)) अणु
			rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66,
						       vgc_level);
		पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5592)) अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 83, qual->rssi > -65 ? 0x4a : 0x7a);
			rt2800_bbp_ग_लिखो_with_rx_chain(rt2x00dev, 66, vgc_level);
		पूर्ण अन्यथा अणु
			rt2800_bbp_ग_लिखो(rt2x00dev, 66, vgc_level);
		पूर्ण

		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	पूर्ण
पूर्ण

व्योम rt2800_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual)
अणु
	rt2800_set_vgc(rt2x00dev, qual, rt2800_get_शेष_vgc(rt2x00dev));
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_reset_tuner);

व्योम rt2800_link_tuner(काष्ठा rt2x00_dev *rt2x00dev, काष्ठा link_qual *qual,
		       स्थिर u32 count)
अणु
	u8 vgc;

	अगर (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C))
		वापस;

	/* When RSSI is better than a certain threshold, increase VGC
	 * with a chip specअगरic value in order to improve the balance
	 * between sensibility and noise isolation.
	 */

	vgc = rt2800_get_शेष_vgc(rt2x00dev);

	चयन (rt2x00dev->chip.rt) अणु
	हाल RT3572:
	हाल RT3593:
		अगर (qual->rssi > -65) अणु
			अगर (rt2x00dev->curr_band == NL80211_BAND_2GHZ)
				vgc += 0x20;
			अन्यथा
				vgc += 0x10;
		पूर्ण
		अवरोध;

	हाल RT3883:
		अगर (qual->rssi > -65)
			vgc += 0x10;
		अवरोध;

	हाल RT5592:
		अगर (qual->rssi > -65)
			vgc += 0x20;
		अवरोध;

	शेष:
		अगर (qual->rssi > -80)
			vgc += 0x10;
		अवरोध;
	पूर्ण

	rt2800_set_vgc(rt2x00dev, qual, vgc);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_link_tuner);

/*
 * Initialization functions.
 */
अटल पूर्णांक rt2800_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;
	u16 eeprom;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	rt2800_disable_wpdma(rt2x00dev);

	ret = rt2800_drv_init_रेजिस्टरs(rt2x00dev);
	अगर (ret)
		वापस ret;

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LEGACY_BASIC_RATE, 0x0000013f);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, HT_BASIC_RATE, 0x00008003);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BCN_TIME_CFG);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL, 1600);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_TICKING, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TBTT_ENABLE, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, BCN_TIME_CFG_TX_TIME_COMPENSATE, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BCN_TIME_CFG, reg);

	rt2800_config_filter(rt2x00dev, FIF_ALLMULTI);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, BKOFF_SLOT_CFG);
	rt2x00_set_field32(&reg, BKOFF_SLOT_CFG_SLOT_TIME, 9);
	rt2x00_set_field32(&reg, BKOFF_SLOT_CFG_CC_DELAY_TIME, 2);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, BKOFF_SLOT_CFG, reg);

	अगर (rt2x00_rt(rt2x00dev, RT3290)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WLAN_FUN_CTRL);
		अगर (rt2x00_get_field32(reg, WLAN_EN) == 1) अणु
			rt2x00_set_field32(&reg, PCIE_APP0_CLK_REQ, 1);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WLAN_FUN_CTRL, reg);
		पूर्ण

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CMB_CTRL);
		अगर (!(rt2x00_get_field32(reg, LDO0_EN) == 1)) अणु
			rt2x00_set_field32(&reg, LDO0_EN, 1);
			rt2x00_set_field32(&reg, LDO_BGSEL, 3);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, CMB_CTRL, reg);
		पूर्ण

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, OSC_CTRL);
		rt2x00_set_field32(&reg, OSC_ROSC_EN, 1);
		rt2x00_set_field32(&reg, OSC_CAL_REQ, 1);
		rt2x00_set_field32(&reg, OSC_REF_CYCLE, 0x27);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, OSC_CTRL, reg);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, COEX_CFG0);
		rt2x00_set_field32(&reg, COEX_CFG_ANT, 0x5e);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, COEX_CFG0, reg);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, COEX_CFG2);
		rt2x00_set_field32(&reg, BT_COEX_CFG1, 0x00);
		rt2x00_set_field32(&reg, BT_COEX_CFG0, 0x17);
		rt2x00_set_field32(&reg, WL_COEX_CFG1, 0x93);
		rt2x00_set_field32(&reg, WL_COEX_CFG0, 0x7f);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, COEX_CFG2, reg);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, PLL_CTRL);
		rt2x00_set_field32(&reg, PLL_CONTROL, 1);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, PLL_CTRL, reg);
	पूर्ण

	अगर (rt2x00_rt(rt2x00dev, RT3071) ||
	    rt2x00_rt(rt2x00dev, RT3090) ||
	    rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT3390)) अणु

		अगर (rt2x00_rt(rt2x00dev, RT3290))
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0,
					      0x00000404);
		अन्यथा
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0,
					      0x00000400);

		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
		अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
			अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_DAC_TEST))
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2,
						      0x0000002c);
			अन्यथा
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		पूर्ण अन्यथा अणु
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
		पूर्ण
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3070)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000400);

		अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F)) अणु
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x0000002c);
		पूर्ण अन्यथा अणु
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00080606);
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
		पूर्ण
	पूर्ण अन्यथा अगर (rt2800_is_305x_soc(rt2x00dev)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000400);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000030);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3352)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000402);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00080606);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3572)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000400);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00080606);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3593)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000402);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
		अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3593, REV_RT3593E)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
			अगर (rt2x00_get_field16(eeprom,
					       EEPROM_NIC_CONF1_DAC_TEST))
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2,
						      0x0000001f);
			अन्यथा
				rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2,
						      0x0000000f);
		पूर्ण अन्यथा अणु
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2,
					      0x00000000);
		पूर्ण
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3883)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000402);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00040000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_TXBF_CFG_0, 0x8000fc21);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_TXBF_CFG_3, 0x00009c40);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5390) ||
		   rt2x00_rt(rt2x00dev, RT5392)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000404);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00080606);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5592)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000404);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5350)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000404);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT6352)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000401);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x000C0000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG2, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_ALC_VGA3, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX0_BB_GAIN_ATTEN, 0x0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX1_BB_GAIN_ATTEN, 0x0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX0_RF_GAIN_ATTEN, 0x6C6C666C);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX1_RF_GAIN_ATTEN, 0x6C6C666C);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX0_RF_GAIN_CORRECT,
				      0x3630363A);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX1_RF_GAIN_CORRECT,
				      0x3630363A);
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_ALC_CFG_1);
		rt2x00_set_field32(&reg, TX_ALC_CFG_1_ROS_BUSY_EN, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_ALC_CFG_1, reg);
	पूर्ण अन्यथा अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG0, 0x00000000);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_SW_CFG1, 0x00080606);
	पूर्ण

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_LINK_CFG);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFB_LIFETIME, 32);
	rt2x00_set_field32(&reg, TX_LINK_CFG_MFB_ENABLE, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_UMFS_ENABLE, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_MRQ_EN, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_RDG_EN, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_TX_CF_ACK_EN, 1);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFB, 0);
	rt2x00_set_field32(&reg, TX_LINK_CFG_REMOTE_MFS, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_LINK_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_TIMEOUT_CFG);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_MPDU_LIFETIME, 9);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_RX_ACK_TIMEOUT, 32);
	rt2x00_set_field32(&reg, TX_TIMEOUT_CFG_TX_OP_TIMEOUT, 10);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_TIMEOUT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAX_LEN_CFG);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_MPDU, AGGREGATION_SIZE);
	अगर (rt2x00_is_usb(rt2x00dev)) अणु
		drv_data->max_psdu = 3;
	पूर्ण अन्यथा अगर (rt2x00_rt_rev_gte(rt2x00dev, RT2872, REV_RT2872E) ||
		   rt2x00_rt(rt2x00dev, RT2883) ||
		   rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070E)) अणु
		drv_data->max_psdu = 2;
	पूर्ण अन्यथा अणु
		drv_data->max_psdu = 1;
	पूर्ण
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MAX_PSDU, drv_data->max_psdu);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MIN_PSDU, 10);
	rt2x00_set_field32(&reg, MAX_LEN_CFG_MIN_MPDU, 10);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAX_LEN_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LED_CFG);
	rt2x00_set_field32(&reg, LED_CFG_ON_PERIOD, 70);
	rt2x00_set_field32(&reg, LED_CFG_OFF_PERIOD, 30);
	rt2x00_set_field32(&reg, LED_CFG_SLOW_BLINK_PERIOD, 3);
	rt2x00_set_field32(&reg, LED_CFG_R_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_G_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_Y_LED_MODE, 3);
	rt2x00_set_field32(&reg, LED_CFG_LED_POLAR, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LED_CFG, reg);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_MAX_PCNT, 0x1f3fbf9f);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_RTY_CFG);
	rt2x00_set_field32(&reg, TX_RTY_CFG_SHORT_RTY_LIMIT, 2);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_LIMIT, 2);
	rt2x00_set_field32(&reg, TX_RTY_CFG_LONG_RTY_THRE, 2000);
	rt2x00_set_field32(&reg, TX_RTY_CFG_NON_AGG_RTY_MODE, 0);
	rt2x00_set_field32(&reg, TX_RTY_CFG_AGG_RTY_MODE, 0);
	rt2x00_set_field32(&reg, TX_RTY_CFG_TX_AUTO_FB_ENABLE, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RTY_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AUTO_RSP_CFG);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_AUTORESPONDER, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_BAC_ACK_POLICY, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_CTS_40_MMODE, 1);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_CTS_40_MREF, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_AR_PREAMBLE, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_DUAL_CTS_EN, 0);
	rt2x00_set_field32(&reg, AUTO_RSP_CFG_ACK_CTS_PSM_BIT, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AUTO_RSP_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CCK_PROT_CFG);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_RATE, 3);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_CTRL, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_CCK, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_RTS_TH_EN, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, CCK_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, OFDM_PROT_CFG);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_RATE, 3);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_CTRL, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_CCK, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_RTS_TH_EN, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, OFDM_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_RATE, 0x4004);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_RTS_TH_EN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_RATE, 0x4084);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_MM40, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_TX_OP_ALLOW_GF40, 1);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_RTS_TH_EN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_RATE, 0x4004);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_MM40, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_TX_OP_ALLOW_GF40, 0);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_RTS_TH_EN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_RATE, 0x4084);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_CTRL, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_NAV_SHORT, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_CCK, 0);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_OFDM, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_MM20, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_MM40, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_GF20, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_TX_OP_ALLOW_GF40, 1);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_RTS_TH_EN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF40_PROT_CFG, reg);

	अगर (rt2x00_is_usb(rt2x00dev)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, PBF_CFG, 0xf40006);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WPDMA_GLO_CFG);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_DMA_BUSY, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_RX_DMA_BUSY, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_WP_DMA_BURST_SIZE, 3);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_BIG_ENDIAN, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_RX_HDR_SCATTER, 0);
		rt2x00_set_field32(&reg, WPDMA_GLO_CFG_HDR_SEG_LEN, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WPDMA_GLO_CFG, reg);
	पूर्ण

	/*
	 * The legacy driver also sets TXOP_CTRL_CFG_RESERVED_TRUN_EN to 1
	 * although it is reserved.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TXOP_CTRL_CFG);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_TIMEOUT_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_AC_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_TXRATEGRP_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_USER_MODE_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_MIMO_PS_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_RESERVED_TRUN_EN, 1);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_LSIG_TXOP_EN, 0);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CCA_EN, 0);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CCA_DLY, 88);
	rt2x00_set_field32(&reg, TXOP_CTRL_CFG_EXT_CWMIN, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TXOP_CTRL_CFG, reg);

	reg = rt2x00_rt(rt2x00dev, RT5592) ? 0x00000082 : 0x00000002;
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TXOP_HLDR_ET, reg);

	अगर (rt2x00_rt(rt2x00dev, RT3883)) अणु
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_FBK_CFG_3S_0, 0x12111008);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_FBK_CFG_3S_1, 0x16151413);
	पूर्ण

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_RTS_CFG);
	rt2x00_set_field32(&reg, TX_RTS_CFG_AUTO_RTS_RETRY_LIMIT, 7);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_THRES,
			   IEEE80211_MAX_RTS_THRESHOLD);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_FBK_EN, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RTS_CFG, reg);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, EXP_ACK_TIME, 0x002400ca);

	/*
	 * Usually the CCK SIFS समय should be set to 10 and the OFDM SIFS
	 * समय should be set to 16. However, the original Ralink driver uses
	 * 16 क्रम both and indeed using a value of 10 क्रम CCK SIFS results in
	 * connection problems with 11g + CTS protection. Hence, use the same
	 * शेषs as the Ralink driver: 16 क्रम both, CCK and OFDM SIFS.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, XIFS_TIME_CFG);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_CCKM_SIFS_TIME, 16);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_OFDM_SIFS_TIME, 16);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_OFDM_XIFS_TIME, 4);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_EIFS, 314);
	rt2x00_set_field32(&reg, XIFS_TIME_CFG_BB_RXEND_ENABLE, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, XIFS_TIME_CFG, reg);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, PWR_PIN_CFG, 0x00000003);

	/*
	 * ASIC will keep garbage value after boot, clear encryption keys.
	 */
	क्रम (i = 0; i < 4; i++)
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, SHARED_KEY_MODE_ENTRY(i), 0);

	क्रम (i = 0; i < 256; i++) अणु
		rt2800_config_wcid(rt2x00dev, शून्य, i);
		rt2800_delete_wcid_attr(rt2x00dev, i);
	पूर्ण

	/*
	 * Clear encryption initialization vectors on start, but keep them
	 * क्रम watchकरोg reset. Otherwise we will have wrong IVs and not be
	 * able to keep connections after reset.
	 */
	अगर (!test_bit(DEVICE_STATE_RESET, &rt2x00dev->flags))
		क्रम (i = 0; i < 256; i++)
			rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_IVEIV_ENTRY(i), 0);

	/*
	 * Clear all beacons
	 */
	क्रम (i = 0; i < 8; i++)
		rt2800_clear_beacon_रेजिस्टर(rt2x00dev, i);

	अगर (rt2x00_is_usb(rt2x00dev)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, US_CYC_CNT);
		rt2x00_set_field32(&reg, US_CYC_CNT_CLOCK_CYCLE, 30);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, US_CYC_CNT, reg);
	पूर्ण अन्यथा अगर (rt2x00_is_pcie(rt2x00dev)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, US_CYC_CNT);
		rt2x00_set_field32(&reg, US_CYC_CNT_CLOCK_CYCLE, 125);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, US_CYC_CNT, reg);
	पूर्ण

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, HT_FBK_CFG0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS0FBK, 0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS1FBK, 0);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS2FBK, 1);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS3FBK, 2);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS4FBK, 3);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS5FBK, 4);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS6FBK, 5);
	rt2x00_set_field32(&reg, HT_FBK_CFG0_HTMCS7FBK, 6);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, HT_FBK_CFG0, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, HT_FBK_CFG1);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS8FBK, 8);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS9FBK, 8);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS10FBK, 9);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS11FBK, 10);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS12FBK, 11);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS13FBK, 12);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS14FBK, 13);
	rt2x00_set_field32(&reg, HT_FBK_CFG1_HTMCS15FBK, 14);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, HT_FBK_CFG1, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LG_FBK_CFG0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS0FBK, 8);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS1FBK, 8);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS2FBK, 9);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS3FBK, 10);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS4FBK, 11);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS5FBK, 12);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS6FBK, 13);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_OFDMMCS7FBK, 14);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LG_FBK_CFG0, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LG_FBK_CFG1);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS0FBK, 0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS1FBK, 0);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS2FBK, 1);
	rt2x00_set_field32(&reg, LG_FBK_CFG0_CCKMCS3FBK, 2);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LG_FBK_CFG1, reg);

	/*
	 * Do not क्रमce the BA winकरोw size, we use the TXWI to set it
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, AMPDU_BA_WINSIZE);
	rt2x00_set_field32(&reg, AMPDU_BA_WINSIZE_FORCE_WINSIZE_ENABLE, 0);
	rt2x00_set_field32(&reg, AMPDU_BA_WINSIZE_FORCE_WINSIZE, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, AMPDU_BA_WINSIZE, reg);

	/*
	 * We must clear the error counters.
	 * These रेजिस्टरs are cleared on पढ़ो,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RX_STA_CNT0);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RX_STA_CNT1);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RX_STA_CNT2);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_STA_CNT0);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_STA_CNT1);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_STA_CNT2);

	/*
	 * Setup leadसमय क्रम pre tbtt पूर्णांकerrupt to 6ms
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, INT_TIMER_CFG);
	rt2x00_set_field32(&reg, INT_TIMER_CFG_PRE_TBTT_TIMER, 6 << 4);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, INT_TIMER_CFG, reg);

	/*
	 * Set up channel statistics समयr
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CH_TIME_CFG);
	rt2x00_set_field32(&reg, CH_TIME_CFG_EIFS_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_NAV_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_RX_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_TX_BUSY, 1);
	rt2x00_set_field32(&reg, CH_TIME_CFG_TMR_EN, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, CH_TIME_CFG, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800_रुको_bbp_rf_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_STATUS_CFG);
		अगर (!rt2x00_get_field32(reg, MAC_STATUS_CFG_BBP_RF_BUSY))
			वापस 0;

		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP/RF register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल पूर्णांक rt2800_रुको_bbp_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u8 value;

	/*
	 * BBP was enabled after firmware was loaded,
	 * but we need to reactivate it now.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);
	msleep(1);

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		value = rt2800_bbp_पढ़ो(rt2x00dev, 0);
		अगर ((value != 0xff) && (value != 0x00))
			वापस 0;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल व्योम rt2800_bbp4_mac_अगर_ctrl(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 value;

	value = rt2800_bbp_पढ़ो(rt2x00dev, 4);
	rt2x00_set_field8(&value, BBP4_MAC_IF_CTRL, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, value);
पूर्ण

अटल व्योम rt2800_init_freq_calibration(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 57);
पूर्ण

अटल व्योम rt2800_init_bbp_5592_glrt(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अटल स्थिर u8 glrt_table[] = अणु
		0xE0, 0x1F, 0X38, 0x32, 0x08, 0x28, 0x19, 0x0A, 0xFF, 0x00, /* 128 ~ 137 */
		0x16, 0x10, 0x10, 0x0B, 0x36, 0x2C, 0x26, 0x24, 0x42, 0x36, /* 138 ~ 147 */
		0x30, 0x2D, 0x4C, 0x46, 0x3D, 0x40, 0x3E, 0x42, 0x3D, 0x40, /* 148 ~ 157 */
		0X3C, 0x34, 0x2C, 0x2F, 0x3C, 0x35, 0x2E, 0x2A, 0x49, 0x41, /* 158 ~ 167 */
		0x36, 0x31, 0x30, 0x30, 0x0E, 0x0D, 0x28, 0x21, 0x1C, 0x16, /* 168 ~ 177 */
		0x50, 0x4A, 0x43, 0x40, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, /* 178 ~ 187 */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 188 ~ 197 */
		0x00, 0x00, 0x7D, 0x14, 0x32, 0x2C, 0x36, 0x4C, 0x43, 0x2C, /* 198 ~ 207 */
		0x2E, 0x36, 0x30, 0x6E,					    /* 208 ~ 211 */
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(glrt_table); i++) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 195, 128 + i);
		rt2800_bbp_ग_लिखो(rt2x00dev, 196, glrt_table[i]);
	पूर्ण
पूर्ण;

अटल व्योम rt2800_init_bbp_early(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);
	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0B);
	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x37);
	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);
	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);
	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);
पूर्ण

अटल व्योम rt2800_disable_unused_dac_adc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 eeprom;
	u8 value;

	value = rt2800_bbp_पढ़ो(rt2x00dev, 138);
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF0);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) == 1)
		value |= 0x20;
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) == 1)
		value &= ~0x02;
	rt2800_bbp_ग_लिखो(rt2x00dev, 138, value);
पूर्ण

अटल व्योम rt2800_init_bbp_305x_soc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 78, 0x0e);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x01);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);
पूर्ण

अटल व्योम rt2800_init_bbp_28xx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	अगर (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860C)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x16);
		rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x12);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
		rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x37);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);

	अगर (rt2x00_rt_rev(rt2x00dev, RT2860, REV_RT2860D))
		rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x19);
	अन्यथा
		rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);
पूर्ण

अटल व्योम rt2800_init_bbp_30xx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);

	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT3070, REV_RT3070F) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT3090, REV_RT3090E))
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);
	अन्यथा
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);

	अगर (rt2x00_rt(rt2x00dev, RT3071) ||
	    rt2x00_rt(rt2x00dev, RT3090))
		rt2800_disable_unused_dac_adc(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_bbp_3290(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 value;

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0b);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x46);
	rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x28);

	rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x58);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 74, 0x0b);
	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x18);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x09);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x7a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x9a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x1c);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x03);

	rt2800_bbp_ग_लिखो(rt2x00dev, 128, 0x12);

	rt2800_bbp_ग_लिखो(rt2x00dev, 67, 0x24);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x99);
	rt2800_bbp_ग_लिखो(rt2x00dev, 150, 0x30);
	rt2800_bbp_ग_लिखो(rt2x00dev, 151, 0x2e);
	rt2800_bbp_ग_लिखो(rt2x00dev, 152, 0x20);
	rt2800_bbp_ग_लिखो(rt2x00dev, 153, 0x34);
	rt2800_bbp_ग_लिखो(rt2x00dev, 154, 0x40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 155, 0x3b);
	rt2800_bbp_ग_लिखो(rt2x00dev, 253, 0x04);

	value = rt2800_bbp_पढ़ो(rt2x00dev, 47);
	rt2x00_set_field8(&value, BBP47_TSSI_ADC6, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 47, value);

	/* Use 5-bit ADC क्रम Acquisition and 8-bit ADC क्रम data */
	value = rt2800_bbp_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&value, BBP3_ADC_MODE_SWITCH, 1);
	rt2x00_set_field8(&value, BBP3_ADC_INIT_MODE, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 3, value);
पूर्ण

अटल व्योम rt2800_init_bbp_3352(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 3, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, 0x50);

	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 47, 0x48);

	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0b);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x46);
	rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x28);

	rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x59);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 78, 0x0e);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x37);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	अगर (rt2x00_rt(rt2x00dev, RT5350)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x7a);
		rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x9a);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);
		rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);

	अगर (rt2x00_rt(rt2x00dev, RT5350)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x3c);
		rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x03);
	पूर्ण अन्यथा अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x34);
		rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x05);
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 120, 0x50);

	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x0f);

	rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0xbd);
	/* Set ITxBF समयout to 0x9c40=1000msec */
	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x01);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x9c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x00);
	/* Reprogram the inband पूर्णांकerface to put right values in RXWI */
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0x3b);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x07);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa2);

	rt2800_bbp_ग_लिखो(rt2x00dev, 148, 0xc8);

	अगर (rt2x00_rt(rt2x00dev, RT5350)) अणु
		/* Antenna Software OFDM */
		rt2800_bbp_ग_लिखो(rt2x00dev, 150, 0x40);
		/* Antenna Software CCK */
		rt2800_bbp_ग_लिखो(rt2x00dev, 151, 0x30);
		rt2800_bbp_ग_लिखो(rt2x00dev, 152, 0xa3);
		/* Clear previously selected antenna */
		rt2800_bbp_ग_लिखो(rt2x00dev, 154, 0);
	पूर्ण
पूर्ण

अटल व्योम rt2800_init_bbp_3390(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);

	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT3390, REV_RT3390E))
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);
	अन्यथा
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);

	rt2800_disable_unused_dac_adc(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_bbp_3572(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x10);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x6a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x99);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);

	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);

	rt2800_disable_unused_dac_adc(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_bbp_3593(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_init_bbp_early(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);
	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x0f);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x19);

	/* Enable DC filter */
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT3593, REV_RT3593E))
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);
पूर्ण

अटल व्योम rt2800_init_bbp_3883(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_init_bbp_early(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 4, 0x50);
	rt2800_bbp_ग_लिखो(rt2x00dev, 47, 0x48);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x46);
	rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x34);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 120, 0x50);
	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x0f);
	rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0x9d);

	/* Set ITxBF समयout to 0x9C40=1000msec */
	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x01);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x9c);

	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x00);

	/* Reprogram the inband पूर्णांकerface to put right values in RXWI */
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0x3b);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x07);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa2);
	rt2800_bbp_ग_लिखो(rt2x00dev, 148, 0xc8);
पूर्ण

अटल व्योम rt2800_init_bbp_53xx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक ant, भाग_mode;
	u16 eeprom;
	u8 value;

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2c);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x38);

	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0b);

	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x46);
	rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x28);

	rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x59);

	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x0a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x33);

	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x62);

	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x7a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x9a);

	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);

	अगर (rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);

	अगर (rt2x00_rt(rt2x00dev, RT5392)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 95, 0x9a);
		rt2800_bbp_ग_लिखो(rt2x00dev, 98, 0x12);
	पूर्ण

	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x3c);

	अगर (rt2x00_rt(rt2x00dev, RT5390))
		rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x03);
	अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5392))
		rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x12);
	अन्यथा
		WARN_ON(1);

	rt2800_bbp_ग_लिखो(rt2x00dev, 128, 0x12);

	अगर (rt2x00_rt(rt2x00dev, RT5392)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 134, 0xd0);
		rt2800_bbp_ग_लिखो(rt2x00dev, 135, 0xf6);
	पूर्ण

	rt2800_disable_unused_dac_adc(rt2x00dev);

	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
	भाग_mode = rt2x00_get_field16(eeprom,
				      EEPROM_NIC_CONF1_ANT_DIVERSITY);
	ant = (भाग_mode == 3) ? 1 : 0;

	/* check अगर this is a Bluetooth combo card */
	अगर (rt2x00_has_cap_bt_coexist(rt2x00dev)) अणु
		u32 reg;

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);
		rt2x00_set_field32(&reg, GPIO_CTRL_सूची3, 0);
		rt2x00_set_field32(&reg, GPIO_CTRL_सूची6, 0);
		rt2x00_set_field32(&reg, GPIO_CTRL_VAL3, 0);
		rt2x00_set_field32(&reg, GPIO_CTRL_VAL6, 0);
		अगर (ant == 0)
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL3, 1);
		अन्यथा अगर (ant == 1)
			rt2x00_set_field32(&reg, GPIO_CTRL_VAL6, 1);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_CTRL, reg);
	पूर्ण

	/* These chips have hardware RX antenna भागersity */
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390R) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5370G)) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 150, 0); /* Disable Antenna Software OFDM */
		rt2800_bbp_ग_लिखो(rt2x00dev, 151, 0); /* Disable Antenna Software CCK */
		rt2800_bbp_ग_लिखो(rt2x00dev, 154, 0); /* Clear previously selected antenna */
	पूर्ण

	value = rt2800_bbp_पढ़ो(rt2x00dev, 152);
	अगर (ant == 0)
		rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 1);
	अन्यथा
		rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 152, value);

	rt2800_init_freq_calibration(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_bbp_5592(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक ant, भाग_mode;
	u16 eeprom;
	u8 value;

	rt2800_init_bbp_early(rt2x00dev);

	value = rt2800_bbp_पढ़ो(rt2x00dev, 105);
	rt2x00_set_field8(&value, BBP105_MLD,
			  rt2x00dev->शेष_ant.rx_chain_num == 2);
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, value);

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 20, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0xDD);
	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x1A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x13);
	rt2800_bbp_ग_लिखो(rt2x00dev, 74, 0x0F);
	rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x4F);
	rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x28);
	rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x59);
	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x9A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);
	rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);
	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 95, 0x9a);
	rt2800_bbp_ग_लिखो(rt2x00dev, 98, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xC0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);
	/* FIXME BBP105 owerग_लिखो */
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x3C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x35);
	rt2800_bbp_ग_लिखो(rt2x00dev, 128, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 134, 0xD0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 135, 0xF6);
	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x0F);

	/* Initialize GLRT (Generalized Likehood Radio Test) */
	rt2800_init_bbp_5592_glrt(rt2x00dev);

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
	भाग_mode = rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_ANT_DIVERSITY);
	ant = (भाग_mode == 3) ? 1 : 0;
	value = rt2800_bbp_पढ़ो(rt2x00dev, 152);
	अगर (ant == 0) अणु
		/* Main antenna */
		rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 1);
	पूर्ण अन्यथा अणु
		/* Auxiliary antenna */
		rt2x00_set_field8(&value, BBP152_RX_DEFAULT_ANT, 0);
	पूर्ण
	rt2800_bbp_ग_लिखो(rt2x00dev, 152, value);

	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5592, REV_RT5592C)) अणु
		value = rt2800_bbp_पढ़ो(rt2x00dev, 254);
		rt2x00_set_field8(&value, BBP254_BIT7, 1);
		rt2800_bbp_ग_लिखो(rt2x00dev, 254, value);
	पूर्ण

	rt2800_init_freq_calibration(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x19);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5592, REV_RT5592C))
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);
पूर्ण

अटल व्योम rt2800_bbp_glrt_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 reg, स्थिर u8 value)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 195, reg);
	rt2800_bbp_ग_लिखो(rt2x00dev, 196, value);
पूर्ण

अटल व्योम rt2800_bbp_dcoc_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 reg, स्थिर u8 value)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, reg);
	rt2800_bbp_ग_लिखो(rt2x00dev, 159, value);
पूर्ण

अटल u8 rt2800_bbp_dcoc_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev, स्थिर u8 reg)
अणु
	rt2800_bbp_ग_लिखो(rt2x00dev, 158, reg);
	वापस rt2800_bbp_पढ़ो(rt2x00dev, 159);
पूर्ण

अटल व्योम rt2800_init_bbp_6352(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 bbp;

	/* Apply Maximum Likelihood Detection (MLD) क्रम 2 stream हाल */
	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 105);
	rt2x00_set_field8(&bbp, BBP105_MLD,
			  rt2x00dev->शेष_ant.rx_chain_num == 2);
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, bbp);

	/* Aव्योम data loss and CRC errors */
	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	/* Fix I/Q swap issue */
	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 1);
	bbp |= 0x04;
	rt2800_bbp_ग_लिखो(rt2x00dev, 1, bbp);

	/* BBP क्रम G band */
	rt2800_bbp_ग_लिखो(rt2x00dev, 3, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, 0x00); /* rt2800_bbp4_mac_अगर_ctrl? */
	rt2800_bbp_ग_लिखो(rt2x00dev, 6, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 14, 0x09);
	rt2800_bbp_ग_लिखो(rt2x00dev, 15, 0xFF);
	rt2800_bbp_ग_लिखो(rt2x00dev, 16, 0x01);
	rt2800_bbp_ग_लिखो(rt2x00dev, 20, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 21, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 30, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x48);
	rt2800_bbp_ग_लिखो(rt2x00dev, 47, 0x40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 62, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 63, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 64, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 65, 0x2C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 66, 0x1C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 67, 0x20);
	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0xDD);
	rt2800_bbp_ग_लिखो(rt2x00dev, 69, 0x10);
	rt2800_bbp_ग_लिखो(rt2x00dev, 70, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 73, 0x18);
	rt2800_bbp_ग_लिखो(rt2x00dev, 74, 0x0F);
	rt2800_bbp_ग_लिखो(rt2x00dev, 75, 0x60);
	rt2800_bbp_ग_लिखो(rt2x00dev, 76, 0x44);
	rt2800_bbp_ग_लिखो(rt2x00dev, 77, 0x59);
	rt2800_bbp_ग_लिखो(rt2x00dev, 78, 0x1E);
	rt2800_bbp_ग_लिखो(rt2x00dev, 79, 0x1C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 80, 0x0C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 81, 0x3A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0xB6);
	rt2800_bbp_ग_लिखो(rt2x00dev, 83, 0x9A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 84, 0x9A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 86, 0x38);
	rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);
	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 95, 0x9A);
	rt2800_bbp_ग_लिखो(rt2x00dev, 96, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xC0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);
	/* FIXME BBP105 owerग_लिखो */
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x3C);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x12);
	rt2800_bbp_ग_लिखो(rt2x00dev, 109, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 134, 0x10);
	rt2800_bbp_ग_लिखो(rt2x00dev, 135, 0xA6);
	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x30);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xF7);
	rt2800_bbp_ग_लिखो(rt2x00dev, 160, 0xEC);
	rt2800_bbp_ग_लिखो(rt2x00dev, 161, 0xC4);
	rt2800_bbp_ग_लिखो(rt2x00dev, 162, 0x77);
	rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0xF9);
	rt2800_bbp_ग_लिखो(rt2x00dev, 164, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 165, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 186, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 187, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 188, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 186, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 187, 0x01);
	rt2800_bbp_ग_लिखो(rt2x00dev, 188, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 189, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 91, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 93, 0x54);
	rt2800_bbp_ग_लिखो(rt2x00dev, 99, 0x50);
	rt2800_bbp_ग_लिखो(rt2x00dev, 148, 0x84);
	rt2800_bbp_ग_लिखो(rt2x00dev, 167, 0x80);
	rt2800_bbp_ग_लिखो(rt2x00dev, 178, 0xFF);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x13);

	/* BBP क्रम G band GLRT function (BBP_128 ~ BBP_221) */
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 0, 0x00);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 1, 0x14);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 2, 0x20);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 3, 0x0A);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 10, 0x16);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 11, 0x06);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 12, 0x02);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 13, 0x07);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 14, 0x05);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 15, 0x09);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 16, 0x20);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 17, 0x08);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 18, 0x4A);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 19, 0x00);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 128, 0xE0);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 129, 0x1F);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 130, 0x4F);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 131, 0x32);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 132, 0x08);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 133, 0x28);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 134, 0x19);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 135, 0x0A);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 138, 0x16);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 139, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 140, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 141, 0x1A);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 142, 0x36);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 143, 0x2C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 144, 0x26);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 145, 0x24);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 146, 0x42);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 147, 0x40);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 148, 0x30);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 149, 0x29);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 150, 0x4C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 151, 0x46);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 152, 0x3D);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 153, 0x40);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 154, 0x3E);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 155, 0x38);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 156, 0x3D);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 157, 0x2F);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 158, 0x3C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 159, 0x34);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 160, 0x2C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 161, 0x2F);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 162, 0x3C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 163, 0x35);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 164, 0x2E);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 165, 0x2F);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 166, 0x49);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 167, 0x41);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 168, 0x36);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 169, 0x39);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 170, 0x30);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 171, 0x30);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 172, 0x0E);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 173, 0x0D);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 174, 0x28);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 175, 0x21);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 176, 0x1C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 177, 0x16);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 178, 0x50);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 179, 0x4A);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 180, 0x43);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 181, 0x50);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 182, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 183, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 184, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 185, 0x10);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 200, 0x7D);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 201, 0x14);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 202, 0x32);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 203, 0x2C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 204, 0x36);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 205, 0x4C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 206, 0x43);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 207, 0x2C);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 208, 0x2E);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 209, 0x36);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 210, 0x30);
	rt2800_bbp_glrt_ग_लिखो(rt2x00dev, 211, 0x6E);

	/* BBP क्रम G band DCOC function */
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 140, 0x0C);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 141, 0x00);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 142, 0x10);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 143, 0x10);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 144, 0x10);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 145, 0x10);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 146, 0x08);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 147, 0x40);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 148, 0x04);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 149, 0x04);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 150, 0x08);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 151, 0x08);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 152, 0x03);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 153, 0x03);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 154, 0x03);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 155, 0x02);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 156, 0x40);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 157, 0x40);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 158, 0x64);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 159, 0x64);

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_bbp(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	अगर (rt2800_is_305x_soc(rt2x00dev))
		rt2800_init_bbp_305x_soc(rt2x00dev);

	चयन (rt2x00dev->chip.rt) अणु
	हाल RT2860:
	हाल RT2872:
	हाल RT2883:
		rt2800_init_bbp_28xx(rt2x00dev);
		अवरोध;
	हाल RT3070:
	हाल RT3071:
	हाल RT3090:
		rt2800_init_bbp_30xx(rt2x00dev);
		अवरोध;
	हाल RT3290:
		rt2800_init_bbp_3290(rt2x00dev);
		अवरोध;
	हाल RT3352:
	हाल RT5350:
		rt2800_init_bbp_3352(rt2x00dev);
		अवरोध;
	हाल RT3390:
		rt2800_init_bbp_3390(rt2x00dev);
		अवरोध;
	हाल RT3572:
		rt2800_init_bbp_3572(rt2x00dev);
		अवरोध;
	हाल RT3593:
		rt2800_init_bbp_3593(rt2x00dev);
		वापस;
	हाल RT3883:
		rt2800_init_bbp_3883(rt2x00dev);
		वापस;
	हाल RT5390:
	हाल RT5392:
		rt2800_init_bbp_53xx(rt2x00dev);
		अवरोध;
	हाल RT5592:
		rt2800_init_bbp_5592(rt2x00dev);
		वापस;
	हाल RT6352:
		rt2800_init_bbp_6352(rt2x00dev);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < EEPROM_BBP_SIZE; i++) अणु
		eeprom = rt2800_eeprom_पढ़ो_from_array(rt2x00dev,
						       EEPROM_BBP_START, i);

		अगर (eeprom != 0xffff && eeprom != 0x0000) अणु
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2800_bbp_ग_लिखो(rt2x00dev, reg_id, value);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rt2800_led_खोलो_drain_enable(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, OPT_14_CSR);
	rt2x00_set_field32(&reg, OPT_14_CSR_BIT0, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, OPT_14_CSR, reg);
पूर्ण

अटल u8 rt2800_init_rx_filter(काष्ठा rt2x00_dev *rt2x00dev, bool bw40,
				u8 filter_target)
अणु
	अचिन्हित पूर्णांक i;
	u8 bbp;
	u8 rfcsr;
	u8 passband;
	u8 stopband;
	u8 overtuned = 0;
	u8 rfcsr24 = (bw40) ? 0x27 : 0x07;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, rfcsr24);

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 4);
	rt2x00_set_field8(&bbp, BBP4_BANDWIDTH, 2 * bw40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, bbp);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 31);
	rt2x00_set_field8(&rfcsr, RFCSR31_RX_H20M, bw40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 22);
	rt2x00_set_field8(&rfcsr, RFCSR22_BASEBAND_LOOPBACK, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, rfcsr);

	/*
	 * Set घातer & frequency of passband test tone
	 */
	rt2800_bbp_ग_लिखो(rt2x00dev, 24, 0);

	क्रम (i = 0; i < 100; i++) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, 0x90);
		msleep(1);

		passband = rt2800_bbp_पढ़ो(rt2x00dev, 55);
		अगर (passband)
			अवरोध;
	पूर्ण

	/*
	 * Set घातer & frequency of stopband test tone
	 */
	rt2800_bbp_ग_लिखो(rt2x00dev, 24, 0x06);

	क्रम (i = 0; i < 100; i++) अणु
		rt2800_bbp_ग_लिखो(rt2x00dev, 25, 0x90);
		msleep(1);

		stopband = rt2800_bbp_पढ़ो(rt2x00dev, 55);

		अगर ((passband - stopband) <= filter_target) अणु
			rfcsr24++;
			overtuned += ((passband - stopband) == filter_target);
		पूर्ण अन्यथा
			अवरोध;

		rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, rfcsr24);
	पूर्ण

	rfcsr24 -= !!overtuned;

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, rfcsr24);
	वापस rfcsr24;
पूर्ण

अटल व्योम rt2800_rf_init_calibration(काष्ठा rt2x00_dev *rt2x00dev,
				       स्थिर अचिन्हित पूर्णांक rf_reg)
अणु
	u8 rfcsr;

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, rf_reg);
	rt2x00_set_field8(&rfcsr, FIELD8(0x80), 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, rf_reg, rfcsr);
	msleep(1);
	rt2x00_set_field8(&rfcsr, FIELD8(0x80), 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, rf_reg, rfcsr);
पूर्ण

अटल व्योम rt2800_rx_filter_calibration(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 filter_tgt_bw20;
	u8 filter_tgt_bw40;
	u8 rfcsr, bbp;

	/*
	 * TODO: sync filter_tgt values with venकरोr driver
	 */
	अगर (rt2x00_rt(rt2x00dev, RT3070)) अणु
		filter_tgt_bw20 = 0x16;
		filter_tgt_bw40 = 0x19;
	पूर्ण अन्यथा अणु
		filter_tgt_bw20 = 0x13;
		filter_tgt_bw40 = 0x15;
	पूर्ण

	drv_data->calibration_bw20 =
		rt2800_init_rx_filter(rt2x00dev, false, filter_tgt_bw20);
	drv_data->calibration_bw40 =
		rt2800_init_rx_filter(rt2x00dev, true, filter_tgt_bw40);

	/*
	 * Save BBP 25 & 26 values क्रम later use in channel चयनing (क्रम 3052)
	 */
	drv_data->bbp25 = rt2800_bbp_पढ़ो(rt2x00dev, 25);
	drv_data->bbp26 = rt2800_bbp_पढ़ो(rt2x00dev, 26);

	/*
	 * Set back to initial state
	 */
	rt2800_bbp_ग_लिखो(rt2x00dev, 24, 0);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 22);
	rt2x00_set_field8(&rfcsr, RFCSR22_BASEBAND_LOOPBACK, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, rfcsr);

	/*
	 * Set BBP back to BW20
	 */
	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 4);
	rt2x00_set_field8(&bbp, BBP4_BANDWIDTH, 0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, bbp);
पूर्ण

अटल व्योम rt2800_normal_mode_setup_3xxx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 min_gain, rfcsr, bbp;
	u16 eeprom;

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 17);

	rt2x00_set_field8(&rfcsr, RFCSR17_TX_LO1_EN, 0);
	अगर (rt2x00_rt(rt2x00dev, RT3070) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E)) अणु
		अगर (!rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev))
			rt2x00_set_field8(&rfcsr, RFCSR17_R, 1);
	पूर्ण

	min_gain = rt2x00_rt(rt2x00dev, RT3070) ? 1 : 2;
	अगर (drv_data->txmixer_gain_24g >= min_gain) अणु
		rt2x00_set_field8(&rfcsr, RFCSR17_TXMIXER_GAIN,
				  drv_data->txmixer_gain_24g);
	पूर्ण

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, rfcsr);

	अगर (rt2x00_rt(rt2x00dev, RT3090)) अणु
		/*  Turn off unused DAC1 and ADC1 to reduce घातer consumption */
		bbp = rt2800_bbp_पढ़ो(rt2x00dev, 138);
		eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF0);
		अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) == 1)
			rt2x00_set_field8(&bbp, BBP138_RX_ADC1, 0);
		अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) == 1)
			rt2x00_set_field8(&bbp, BBP138_TX_DAC1, 1);
		rt2800_bbp_ग_लिखो(rt2x00dev, 138, bbp);
	पूर्ण

	अगर (rt2x00_rt(rt2x00dev, RT3070)) अणु
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 27);
		अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F))
			rt2x00_set_field8(&rfcsr, RFCSR27_R1, 3);
		अन्यथा
			rt2x00_set_field8(&rfcsr, RFCSR27_R1, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R2, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R3, 0);
		rt2x00_set_field8(&rfcsr, RFCSR27_R4, 0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, rfcsr);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3071) ||
		   rt2x00_rt(rt2x00dev, RT3090) ||
		   rt2x00_rt(rt2x00dev, RT3390)) अणु
		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 0);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 0);
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 15);
		rt2x00_set_field8(&rfcsr, RFCSR15_TX_LO2_EN, 0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, rfcsr);

		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 20);
		rt2x00_set_field8(&rfcsr, RFCSR20_RX_LO1_EN, 0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, rfcsr);

		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 21);
		rt2x00_set_field8(&rfcsr, RFCSR21_RX_LO2_EN, 0);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, rfcsr);
	पूर्ण
पूर्ण

अटल व्योम rt2800_normal_mode_setup_3593(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 rfcsr;
	u8 tx_gain;

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 50);
	rt2x00_set_field8(&rfcsr, RFCSR50_TX_LO2_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 51);
	tx_gain = rt2x00_get_field8(drv_data->txmixer_gain_24g,
				    RFCSR17_TXMIXER_GAIN);
	rt2x00_set_field8(&rfcsr, RFCSR51_BITS24, tx_gain);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 38);
	rt2x00_set_field8(&rfcsr, RFCSR38_RX_LO1_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 39);
	rt2x00_set_field8(&rfcsr, RFCSR39_RX_LO2_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_PLL_PD, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	rt2x00_set_field8(&rfcsr, RFCSR30_RX_VCM, 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, rfcsr);

	/* TODO: enable stream mode */
पूर्ण

अटल व्योम rt2800_normal_mode_setup_5xxx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 reg;
	u16 eeprom;

	/*  Turn off unused DAC1 and ADC1 to reduce घातer consumption */
	reg = rt2800_bbp_पढ़ो(rt2x00dev, 138);
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF0);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH) == 1)
		rt2x00_set_field8(&reg, BBP138_RX_ADC1, 0);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH) == 1)
		rt2x00_set_field8(&reg, BBP138_TX_DAC1, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 138, reg);

	reg = rt2800_rfcsr_पढ़ो(rt2x00dev, 38);
	rt2x00_set_field8(&reg, RFCSR38_RX_LO1_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, reg);

	reg = rt2800_rfcsr_पढ़ो(rt2x00dev, 39);
	rt2x00_set_field8(&reg, RFCSR39_RX_LO2_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, reg);

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	reg = rt2800_rfcsr_पढ़ो(rt2x00dev, 30);
	rt2x00_set_field8(&reg, RFCSR30_RX_VCM, 2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, reg);
पूर्ण

अटल व्योम rt2800_init_rfcsr_305x_soc(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x01);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0xf7);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x75);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0x39);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x60);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x75);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x75);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x58);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0xb3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x92);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x2c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xba);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x31);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x01);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x25);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x13);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x83);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x00);
पूर्ण

अटल व्योम rt2800_init_rfcsr_30xx(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 rfcsr;
	u16 eeprom;
	u32 reg;

	/* XXX venकरोr driver करो this only क्रम 3070 */
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x60);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x41);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x7b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x58);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0xb3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x92);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x2c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xba);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x16);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x1f);

	अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F)) अणु
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
		rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
		rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3071) ||
		   rt2x00_rt(rt2x00dev, RT3090)) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x14);

		rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
		rt2x00_set_field8(&rfcsr, RFCSR6_R2, 1);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
		rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
		अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
		    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E)) अणु
			eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
			अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_DAC_TEST))
				rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
			अन्यथा
				rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
		पूर्ण
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);

		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_SWITCH);
		rt2x00_set_field32(&reg, GPIO_SWITCH_5, 0);
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_SWITCH, reg);
	पूर्ण

	rt2800_rx_filter_calibration(rt2x00dev);

	अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3070, REV_RT3070F) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3071, REV_RT3071E) ||
	    rt2x00_rt_rev_lt(rt2x00dev, RT3090, REV_RT3090E))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x03);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_3290(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 rfcsr;

	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xa0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0xf3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x46);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x83);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x05);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x85);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x0b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xd5);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x7b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x0e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xa2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x73);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x98);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x38);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x78);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x43);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x7f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x45);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xc1);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 29);
	rt2x00_set_field8(&rfcsr, RFCSR29_RSSI_GAIN, 3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, rfcsr);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_3352(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक tx0_ext_pa = test_bit(CAPABILITY_EXTERNAL_PA_TX0,
				  &rt2x00dev->cap_flags);
	पूर्णांक tx1_ext_pa = test_bit(CAPABILITY_EXTERNAL_PA_TX1,
				  &rt2x00dev->cap_flags);
	u8 rfcsr;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0xf0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x18);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x33);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xd2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x42);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x1c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x5a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x01);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x45);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rfcsr = 0x01;
	अगर (tx0_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR34_TX0_EXT_PA, 1);
	अगर (tx1_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR34_TX1_EXT_PA, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, rfcsr);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0xbd);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x3c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x5f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0xc5);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x33);
	rfcsr = 0x52;
	अगर (!tx0_ext_pa) अणु
		rt2x00_set_field8(&rfcsr, RFCSR41_BIT1, 1);
		rt2x00_set_field8(&rfcsr, RFCSR41_BIT4, 1);
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, rfcsr);
	rfcsr = 0x52;
	अगर (!tx1_ext_pa) अणु
		rt2x00_set_field8(&rfcsr, RFCSR42_BIT1, 1);
		rt2x00_set_field8(&rfcsr, RFCSR42_BIT4, 1);
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, rfcsr);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0xdd);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x0d);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x14);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x00);
	rfcsr = 0x2d;
	अगर (tx0_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR50_TX0_EXT_PA, 1);
	अगर (tx1_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR50_TX1_EXT_PA, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, rfcsr);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, (tx0_ext_pa ? 0x52 : 0x7f));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, (tx0_ext_pa ? 0xc0 : 0x00));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, (tx0_ext_pa ? 0xd2 : 0x52));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, (tx0_ext_pa ? 0xc0 : 0x1b));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, (tx1_ext_pa ? 0x52 : 0x7f));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, (tx1_ext_pa ? 0xc0 : 0x00));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, (tx0_ext_pa ? 0x49 : 0x52));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, (tx1_ext_pa ? 0xc0 : 0x1b));
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x00);

	rt2800_rx_filter_calibration(rt2x00dev);
	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_3390(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0xa0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0xe1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x62);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x8b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x42);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x34);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0xc0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x61);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x21);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x3b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x90);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x94);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x5c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xb2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0xf6);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x14);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x3d);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x85);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x41);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x8f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x0f);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_SWITCH);
	rt2x00_set_field32(&reg, GPIO_SWITCH_5, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_SWITCH, reg);

	rt2800_rx_filter_calibration(rt2x00dev);

	अगर (rt2x00_rt_rev_lt(rt2x00dev, RT3390, REV_RT3390E))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x03);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_3572(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 rfcsr;
	u32 reg;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0x70);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x81);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x4c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x05);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0xd8);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0xc3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0xb9);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x70);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x65);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0xa0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x4c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0xac);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x93);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xb3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0xd0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x3c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x16);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x15);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x85);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x9b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x10);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
	rt2x00_set_field8(&rfcsr, RFCSR6_R2, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);
	msleep(1);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);

	rt2800_rx_filter_calibration(rt2x00dev);
	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
पूर्ण

अटल व्योम rt3593_post_bbp_init(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 bbp;
	bool txbf_enabled = false; /* FIXME */

	bbp = rt2800_bbp_पढ़ो(rt2x00dev, 105);
	अगर (rt2x00dev->शेष_ant.rx_chain_num == 1)
		rt2x00_set_field8(&bbp, BBP105_MLD, 0);
	अन्यथा
		rt2x00_set_field8(&bbp, BBP105_MLD, 1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, bbp);

	rt2800_bbp4_mac_अगर_ctrl(rt2x00dev);

	rt2800_bbp_ग_लिखो(rt2x00dev, 92, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 82, 0x82);
	rt2800_bbp_ग_लिखो(rt2x00dev, 106, 0x05);
	rt2800_bbp_ग_लिखो(rt2x00dev, 104, 0x92);
	rt2800_bbp_ग_लिखो(rt2x00dev, 88, 0x90);
	rt2800_bbp_ग_लिखो(rt2x00dev, 148, 0xc8);
	rt2800_bbp_ग_लिखो(rt2x00dev, 47, 0x48);
	rt2800_bbp_ग_लिखो(rt2x00dev, 120, 0x50);

	अगर (txbf_enabled)
		rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0xbd);
	अन्यथा
		rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0x9d);

	/* SNR mapping */
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 6);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 160);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 7);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 161);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 8);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 162);

	/* ADC/DAC control */
	rt2800_bbp_ग_लिखो(rt2x00dev, 31, 0x08);

	/* RX AGC energy lower bound in log2 */
	rt2800_bbp_ग_लिखो(rt2x00dev, 68, 0x0b);

	/* FIXME: BBP 105 owerग_लिखो? */
	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x04);

पूर्ण

अटल व्योम rt2800_init_rfcsr_3593(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;
	u8 rfcsr;

	/* Disable GPIO #4 and #7 function क्रम LAN PE control */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_SWITCH);
	rt2x00_set_field32(&reg, GPIO_SWITCH_4, 0);
	rt2x00_set_field32(&reg, GPIO_SWITCH_7, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_SWITCH, reg);

	/* Initialize शेष रेजिस्टर values */
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xd3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x4e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x78);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x3b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x3c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x86);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0xd3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x60);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x8e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, 0x86);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x75);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x45);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x18);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x18);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x18);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x6e);

	/* Initiate calibration */
	/* TODO: use rt2800_rf_init_calibration ? */
	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rfcsr);

	rt2800_freq_cal_mode1(rt2x00dev);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 18);
	rt2x00_set_field8(&rfcsr, RFCSR18_XO_TUNE_BYPASS, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, rfcsr);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 3);
	rt2x00_set_field32(&reg, LDO_CFG0_BGSEL, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);
	usleep_range(1000, 1500);
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, LDO_CFG0);
	rt2x00_set_field32(&reg, LDO_CFG0_LDO_CORE_VLEVEL, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, LDO_CFG0, reg);

	/* Set initial values क्रम RX filter calibration */
	drv_data->calibration_bw20 = 0x1f;
	drv_data->calibration_bw40 = 0x2f;

	/* Save BBP 25 & 26 values क्रम later use in channel चयनing */
	drv_data->bbp25 = rt2800_bbp_पढ़ो(rt2x00dev, 25);
	drv_data->bbp26 = rt2800_bbp_पढ़ो(rt2x00dev, 26);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3593(rt2x00dev);

	rt3593_post_bbp_init(rt2x00dev);

	/* TODO: enable stream mode support */
पूर्ण

अटल व्योम rt2800_init_rfcsr_5350(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0xf0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x49);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0xf1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x46);
	अगर (rt2800_clk_is_20mhz(rt2x00dev))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x1f);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0xc0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0xd0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x85);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x0b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xd5);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x9b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x0c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xa6);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x73);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x38);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x38);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x43);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0x82);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x39);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x0b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x45);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xd1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x00);
पूर्ण

अटल व्योम rt2800_init_rfcsr_3883(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u8 rfcsr;

	/* TODO: get the actual ECO value from the SoC */
	स्थिर अचिन्हित पूर्णांक eco = 5;

	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0x5b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0xd3);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x48);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x1a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x00);

	/* RFCSR 17 will be initialized later based on the
	 * frequency offset stored in the EEPROM
	 */

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0xc0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x86);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x23);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x93);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x60);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x8e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, 0x86);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x51);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x05);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x76);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x76);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x76);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xdb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x3e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x00);

	/* TODO: rx filter calibration? */

	rt2800_bbp_ग_लिखो(rt2x00dev, 137, 0x0f);

	rt2800_bbp_ग_लिखो(rt2x00dev, 163, 0x9d);

	rt2800_bbp_ग_लिखो(rt2x00dev, 105, 0x05);

	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x02);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x00);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x40);
	rt2800_bbp_ग_लिखो(rt2x00dev, 180, 0x01);
	rt2800_bbp_ग_लिखो(rt2x00dev, 182, 0x9c);

	rt2800_bbp_ग_लिखो(rt2x00dev, 179, 0x00);

	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x04);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0x3b);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x06);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa0);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x07);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 142, 0x08);
	rt2800_bbp_ग_लिखो(rt2x00dev, 143, 0xa2);
	rt2800_bbp_ग_लिखो(rt2x00dev, 148, 0xc8);

	अगर (eco == 5) अणु
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0xd8);
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x32);
	पूर्ण

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 2);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_BP, 0);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rfcsr);
	msleep(1);
	rt2x00_set_field8(&rfcsr, RFCSR2_RESCAL_EN, 0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_RF_BLOCK_EN, 1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 6);
	rfcsr |= 0xc0;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 22);
	rfcsr |= 0x20;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 46);
	rfcsr |= 0x20;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, rfcsr);

	rfcsr = rt2800_rfcsr_पढ़ो(rt2x00dev, 20);
	rfcsr &= ~0xee;
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, rfcsr);
पूर्ण

अटल व्योम rt2800_init_rfcsr_5390(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x88);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x10);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xe0);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xa0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x46);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x00);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x00);
	अगर (rt2x00_is_usb(rt2x00dev) &&
	    rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x80);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0xc0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x10);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x85);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1b);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x0b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xd2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x9a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x0e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xa2);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x73);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x7b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x94);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x38);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x00);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x84);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x78);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x44);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0x42);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0x22);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x7f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x8f);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x45);
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390F)) अणु
		अगर (rt2x00_is_usb(rt2x00dev))
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xd1);
		अन्यथा
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xd5);
	पूर्ण अन्यथा अणु
		अगर (rt2x00_is_usb(rt2x00dev))
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xdd);
		अन्यथा
			rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0xb5);
	पूर्ण
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x00);

	rt2800_normal_mode_setup_5xxx(rt2x00dev);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_5392(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_rf_init_calibration(rt2x00dev, 2);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x17);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x88);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xe0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x53);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x4a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, 0x46);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x9f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x4d);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x8d);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x0b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x44);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x20);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0xC0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x89);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x1b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x0f);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xbb);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0xd5);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x9b);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 44, 0x0e);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 45, 0xa2);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 46, 0x73);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x0c);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 48, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 49, 0x94);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 50, 0x94);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 51, 0x3a);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 52, 0x48);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x44);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 54, 0x38);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 55, 0x43);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 56, 0xa1);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 57, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 58, 0x39);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 59, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 60, 0x45);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 61, 0x91);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 62, 0x39);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x07);

	rt2800_normal_mode_setup_5xxx(rt2x00dev);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
पूर्ण

अटल व्योम rt2800_init_rfcsr_5592(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x3F);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0xE4);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x4D);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x8D);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x82);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x10);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0xC0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 47, 0x0C);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 53, 0x22);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 63, 0x07);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x80);
	msleep(1);

	rt2800_freq_cal_mode1(rt2x00dev);

	/* Enable DC filter */
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5592, REV_RT5592C))
		rt2800_bbp_ग_लिखो(rt2x00dev, 103, 0xc0);

	rt2800_normal_mode_setup_5xxx(rt2x00dev);

	अगर (rt2x00_rt_rev_lt(rt2x00dev, RT5592, REV_RT5592C))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x03);

	rt2800_led_खोलो_drain_enable(rt2x00dev);
पूर्ण

अटल व्योम rt2800_bbp_core_soft_reset(काष्ठा rt2x00_dev *rt2x00dev,
				       bool set_bw, bool is_ht40)
अणु
	u8 bbp_val;

	bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 21);
	bbp_val |= 0x1;
	rt2800_bbp_ग_लिखो(rt2x00dev, 21, bbp_val);
	usleep_range(100, 200);

	अगर (set_bw) अणु
		bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 4);
		rt2x00_set_field8(&bbp_val, BBP4_BANDWIDTH, 2 * is_ht40);
		rt2800_bbp_ग_लिखो(rt2x00dev, 4, bbp_val);
		usleep_range(100, 200);
	पूर्ण

	bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 21);
	bbp_val &= (~0x1);
	rt2800_bbp_ग_लिखो(rt2x00dev, 21, bbp_val);
	usleep_range(100, 200);
पूर्ण

अटल पूर्णांक rt2800_rf_lp_config(काष्ठा rt2x00_dev *rt2x00dev, bool btxcal)
अणु
	u8 rf_val;

	अगर (btxcal)
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RF_CONTROL0, 0x04);
	अन्यथा
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RF_CONTROL0, 0x02);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RF_BYPASS0, 0x06);

	rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 17);
	rf_val |= 0x80;
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 17, rf_val);

	अगर (btxcal) अणु
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 18, 0xC1);
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 19, 0x20);
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 20, 0x02);
		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 3);
		rf_val &= (~0x3F);
		rf_val |= 0x3F;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 3, rf_val);
		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 4);
		rf_val &= (~0x3F);
		rf_val |= 0x3F;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 4, rf_val);
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 5, 0x31);
	पूर्ण अन्यथा अणु
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 18, 0xF1);
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 19, 0x18);
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 20, 0x02);
		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 3);
		rf_val &= (~0x3F);
		rf_val |= 0x34;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 3, rf_val);
		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 4);
		rf_val &= (~0x3F);
		rf_val |= 0x34;
		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 4, rf_val);
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर rt2800_lp_tx_filter_bw_cal(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक cnt;
	u8 bbp_val;
	अक्षर cal_val;

	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 0, 0x82);

	cnt = 0;
	करो अणु
		usleep_range(500, 2000);
		bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 159);
		अगर (bbp_val == 0x02 || cnt == 20)
			अवरोध;

		cnt++;
	पूर्ण जबतक (cnt < 20);

	bbp_val = rt2800_bbp_dcoc_पढ़ो(rt2x00dev, 0x39);
	cal_val = bbp_val & 0x7F;
	अगर (cal_val >= 0x40)
		cal_val -= 128;

	वापस cal_val;
पूर्ण

अटल व्योम rt2800_bw_filter_calibration(काष्ठा rt2x00_dev *rt2x00dev,
					 bool btxcal)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 tx_agc_fc = 0, rx_agc_fc = 0, cmm_agc_fc;
	u8 filter_target;
	u8 tx_filter_target_20m = 0x09, tx_filter_target_40m = 0x02;
	u8 rx_filter_target_20m = 0x27, rx_filter_target_40m = 0x31;
	पूर्णांक loop = 0, is_ht40, cnt;
	u8 bbp_val, rf_val;
	अक्षर cal_r32_init, cal_r32_val, cal_dअगरf;
	u8 saverfb5r00, saverfb5r01, saverfb5r03, saverfb5r04, saverfb5r05;
	u8 saverfb5r06, saverfb5r07;
	u8 saverfb5r08, saverfb5r17, saverfb5r18, saverfb5r19, saverfb5r20;
	u8 saverfb5r37, saverfb5r38, saverfb5r39, saverfb5r40, saverfb5r41;
	u8 saverfb5r42, saverfb5r43, saverfb5r44, saverfb5r45, saverfb5r46;
	u8 saverfb5r58, saverfb5r59;
	u8 savebbp159r0, savebbp159r2, savebbpr23;
	u32 MAC_RF_CONTROL0, MAC_RF_BYPASS0;

	/* Save MAC रेजिस्टरs */
	MAC_RF_CONTROL0 = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RF_CONTROL0);
	MAC_RF_BYPASS0 = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, RF_BYPASS0);

	/* save BBP रेजिस्टरs */
	savebbpr23 = rt2800_bbp_पढ़ो(rt2x00dev, 23);

	savebbp159r0 = rt2800_bbp_dcoc_पढ़ो(rt2x00dev, 0);
	savebbp159r2 = rt2800_bbp_dcoc_पढ़ो(rt2x00dev, 2);

	/* Save RF रेजिस्टरs */
	saverfb5r00 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 0);
	saverfb5r01 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 1);
	saverfb5r03 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 3);
	saverfb5r04 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 4);
	saverfb5r05 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 5);
	saverfb5r06 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 6);
	saverfb5r07 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 7);
	saverfb5r08 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 8);
	saverfb5r17 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 17);
	saverfb5r18 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 18);
	saverfb5r19 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 19);
	saverfb5r20 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 20);

	saverfb5r37 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 37);
	saverfb5r38 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 38);
	saverfb5r39 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 39);
	saverfb5r40 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 40);
	saverfb5r41 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 41);
	saverfb5r42 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 42);
	saverfb5r43 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 43);
	saverfb5r44 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 44);
	saverfb5r45 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 45);
	saverfb5r46 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 46);

	saverfb5r58 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 58);
	saverfb5r59 = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 59);

	rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 0);
	rf_val |= 0x3;
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 0, rf_val);

	rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 1);
	rf_val |= 0x1;
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 1, rf_val);

	cnt = 0;
	करो अणु
		usleep_range(500, 2000);
		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 1);
		अगर (((rf_val & 0x1) == 0x00) || (cnt == 40))
			अवरोध;
		cnt++;
	पूर्ण जबतक (cnt < 40);

	rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 0);
	rf_val &= (~0x3);
	rf_val |= 0x1;
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 0, rf_val);

	/* I-3 */
	bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 23);
	bbp_val &= (~0x1F);
	bbp_val |= 0x10;
	rt2800_bbp_ग_लिखो(rt2x00dev, 23, bbp_val);

	करो अणु
		/* I-4,5,6,7,8,9 */
		अगर (loop == 0) अणु
			is_ht40 = false;

			अगर (btxcal)
				filter_target = tx_filter_target_20m;
			अन्यथा
				filter_target = rx_filter_target_20m;
		पूर्ण अन्यथा अणु
			is_ht40 = true;

			अगर (btxcal)
				filter_target = tx_filter_target_40m;
			अन्यथा
				filter_target = rx_filter_target_40m;
		पूर्ण

		rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 8);
		rf_val &= (~0x04);
		अगर (loop == 1)
			rf_val |= 0x4;

		rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 8, rf_val);

		rt2800_bbp_core_soft_reset(rt2x00dev, true, is_ht40);

		rt2800_rf_lp_config(rt2x00dev, btxcal);
		अगर (btxcal) अणु
			tx_agc_fc = 0;
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 58);
			rf_val &= (~0x7F);
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 58, rf_val);
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 59);
			rf_val &= (~0x7F);
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 59, rf_val);
		पूर्ण अन्यथा अणु
			rx_agc_fc = 0;
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 6);
			rf_val &= (~0x7F);
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 6, rf_val);
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 7);
			rf_val &= (~0x7F);
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 7, rf_val);
		पूर्ण

		usleep_range(1000, 2000);

		bbp_val = rt2800_bbp_dcoc_पढ़ो(rt2x00dev, 2);
		bbp_val &= (~0x6);
		rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 2, bbp_val);

		rt2800_bbp_core_soft_reset(rt2x00dev, false, is_ht40);

		cal_r32_init = rt2800_lp_tx_filter_bw_cal(rt2x00dev);

		bbp_val = rt2800_bbp_dcoc_पढ़ो(rt2x00dev, 2);
		bbp_val |= 0x6;
		rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 2, bbp_val);
करो_cal:
		अगर (btxcal) अणु
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 58);
			rf_val &= (~0x7F);
			rf_val |= tx_agc_fc;
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 58, rf_val);
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 59);
			rf_val &= (~0x7F);
			rf_val |= tx_agc_fc;
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 59, rf_val);
		पूर्ण अन्यथा अणु
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 6);
			rf_val &= (~0x7F);
			rf_val |= rx_agc_fc;
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 6, rf_val);
			rf_val = rt2800_rfcsr_पढ़ो_bank(rt2x00dev, 5, 7);
			rf_val &= (~0x7F);
			rf_val |= rx_agc_fc;
			rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 7, rf_val);
		पूर्ण

		usleep_range(500, 1000);

		rt2800_bbp_core_soft_reset(rt2x00dev, false, is_ht40);

		cal_r32_val = rt2800_lp_tx_filter_bw_cal(rt2x00dev);

		cal_dअगरf = cal_r32_init - cal_r32_val;

		अगर (btxcal)
			cmm_agc_fc = tx_agc_fc;
		अन्यथा
			cmm_agc_fc = rx_agc_fc;

		अगर (((cal_dअगरf > filter_target) && (cmm_agc_fc == 0)) ||
		    ((cal_dअगरf < filter_target) && (cmm_agc_fc == 0x3f))) अणु
			अगर (btxcal)
				tx_agc_fc = 0;
			अन्यथा
				rx_agc_fc = 0;
		पूर्ण अन्यथा अगर ((cal_dअगरf <= filter_target) && (cmm_agc_fc < 0x3f)) अणु
			अगर (btxcal)
				tx_agc_fc++;
			अन्यथा
				rx_agc_fc++;
			जाओ करो_cal;
		पूर्ण

		अगर (btxcal) अणु
			अगर (loop == 0)
				drv_data->tx_calibration_bw20 = tx_agc_fc;
			अन्यथा
				drv_data->tx_calibration_bw40 = tx_agc_fc;
		पूर्ण अन्यथा अणु
			अगर (loop == 0)
				drv_data->rx_calibration_bw20 = rx_agc_fc;
			अन्यथा
				drv_data->rx_calibration_bw40 = rx_agc_fc;
		पूर्ण

		loop++;
	पूर्ण जबतक (loop <= 1);

	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 0, saverfb5r00);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 1, saverfb5r01);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 3, saverfb5r03);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 4, saverfb5r04);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 5, saverfb5r05);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 6, saverfb5r06);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 7, saverfb5r07);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 8, saverfb5r08);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 17, saverfb5r17);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 18, saverfb5r18);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 19, saverfb5r19);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 20, saverfb5r20);

	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 37, saverfb5r37);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 38, saverfb5r38);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 39, saverfb5r39);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 40, saverfb5r40);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 41, saverfb5r41);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 42, saverfb5r42);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 43, saverfb5r43);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 44, saverfb5r44);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 45, saverfb5r45);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 46, saverfb5r46);

	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 58, saverfb5r58);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 5, 59, saverfb5r59);

	rt2800_bbp_ग_लिखो(rt2x00dev, 23, savebbpr23);

	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 0, savebbp159r0);
	rt2800_bbp_dcoc_ग_लिखो(rt2x00dev, 2, savebbp159r2);

	bbp_val = rt2800_bbp_पढ़ो(rt2x00dev, 4);
	rt2x00_set_field8(&bbp_val, BBP4_BANDWIDTH,
			  2 * test_bit(CONFIG_CHANNEL_HT40, &rt2x00dev->flags));
	rt2800_bbp_ग_लिखो(rt2x00dev, 4, bbp_val);

	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RF_CONTROL0, MAC_RF_CONTROL0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, RF_BYPASS0, MAC_RF_BYPASS0);
पूर्ण

अटल व्योम rt2800_init_rfcsr_6352(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/* Initialize RF central रेजिस्टर to शेष value */
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 0, 0x02);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 2, 0x33);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 3, 0xFF);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 4, 0x0C);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 5, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 6, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 8, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 9, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 10, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 12, rt2x00dev->freq_offset);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x40);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 15, 0x22);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x4C);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0xA0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0x12);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x07);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x13);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0xFE);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x24);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x7A);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0x05);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 30, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 31, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 32, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 34, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 35, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 37, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 38, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 40, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 41, 0xD0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 42, 0x5B);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x00);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 11, 0x21);
	अगर (rt2800_clk_is_20mhz(rt2x00dev))
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x03);
	अन्यथा
		rt2800_rfcsr_ग_लिखो(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 14, 0x7C);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 16, 0x80);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 17, 0x99);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 18, 0x99);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 19, 0x09);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 20, 0x50);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 21, 0xB0);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 23, 0x06);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 26, 0x5D);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x61);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0xB5);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 43, 0x02);

	rt2800_rfcsr_ग_लिखो(rt2x00dev, 28, 0x62);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 29, 0xAD);
	rt2800_rfcsr_ग_लिखो(rt2x00dev, 39, 0x80);

	/* Initialize RF channel रेजिस्टर to शेष value */
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 0, 0x03);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 1, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 2, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 3, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 5, 0x08);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 6, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 7, 0x51);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 8, 0x53);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 9, 0x16);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 10, 0x61);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 11, 0x53);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 12, 0x22);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 13, 0x3D);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 14, 0x06);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 15, 0x13);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 16, 0x22);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 17, 0x27);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 18, 0x02);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 19, 0xA7);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 20, 0x01);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 21, 0x52);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 22, 0x80);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 23, 0xB3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 28, 0x5C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 29, 0x6B);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 30, 0x6B);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 31, 0x31);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 32, 0x5D);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 34, 0xE6);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 35, 0x55);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 37, 0xBB);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 38, 0xB3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 39, 0xB3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 40, 0x03);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 43, 0xB3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 44, 0xD3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 45, 0xD5);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 46, 0x07);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 47, 0x68);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 48, 0xEF);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 49, 0x1C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 54, 0x07);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 55, 0xA8);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 56, 0x85);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 57, 0x10);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 58, 0x07);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 59, 0x6A);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 60, 0x85);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 61, 0x10);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 62, 0x1C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 63, 0x00);

	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 6, 45, 0xC5);

	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 9, 0x47);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 10, 0x71);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 11, 0x33);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 14, 0x0E);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 17, 0x23);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 19, 0xA4);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 20, 0x02);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 21, 0x12);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 28, 0x1C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 29, 0xEB);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 32, 0x7D);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 34, 0xD6);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 36, 0x08);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 38, 0xB4);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 43, 0xD3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 44, 0xB3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 45, 0xD5);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 46, 0x27);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 4, 47, 0x67);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 6, 47, 0x69);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 48, 0xFF);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 4, 54, 0x27);
	rt2800_rfcsr_ग_लिखो_bank(rt2x00dev, 6, 54, 0x20);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 55, 0x66);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 56, 0xFF);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 57, 0x1C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 58, 0x20);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 59, 0x6B);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 60, 0xF7);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 61, 0x09);

	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 10, 0x51);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 14, 0x06);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 19, 0xA7);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 28, 0x2C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 55, 0x64);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 8, 0x51);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 9, 0x36);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 11, 0x53);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 14, 0x16);

	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 47, 0x6C);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 48, 0xFC);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 49, 0x1F);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 54, 0x27);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 55, 0x66);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 59, 0x6B);

	/* Initialize RF channel रेजिस्टर क्रम DRQFN */
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 43, 0xD3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 44, 0xE3);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 45, 0xE5);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 47, 0x28);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 55, 0x68);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 56, 0xF7);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 58, 0x02);
	rt2800_rfcsr_ग_लिखो_chanreg(rt2x00dev, 60, 0xC7);

	/* Initialize RF DC calibration रेजिस्टर to शेष value */
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 0, 0x47);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 1, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 2, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 3, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 6, 0x10);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 7, 0x10);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 8, 0x04);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 9, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 10, 0x07);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 11, 0x01);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 12, 0x07);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 13, 0x07);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 14, 0x07);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 15, 0x20);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 16, 0x22);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 17, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 18, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 21, 0xF1);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 22, 0x11);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 23, 0x02);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 24, 0x41);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 25, 0x20);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 27, 0xD7);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 28, 0xA2);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 29, 0x20);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 30, 0x49);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 31, 0x20);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 32, 0x04);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 33, 0xF1);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 34, 0xA1);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 35, 0x01);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 43, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 44, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 45, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 46, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 47, 0x3E);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 48, 0x3D);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 49, 0x3E);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 50, 0x3D);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 51, 0x3E);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 52, 0x3D);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 53, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 54, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 55, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 56, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 57, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 58, 0x10);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 59, 0x10);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 60, 0x0A);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 63, 0x00);

	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 4, 0x04);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 5, 0x20);

	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_ग_लिखो_dccal(rt2x00dev, 17, 0x7C);

	rt2800_bw_filter_calibration(rt2x00dev, true);
	rt2800_bw_filter_calibration(rt2x00dev, false);
पूर्ण

अटल व्योम rt2800_init_rfcsr(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (rt2800_is_305x_soc(rt2x00dev)) अणु
		rt2800_init_rfcsr_305x_soc(rt2x00dev);
		वापस;
	पूर्ण

	चयन (rt2x00dev->chip.rt) अणु
	हाल RT3070:
	हाल RT3071:
	हाल RT3090:
		rt2800_init_rfcsr_30xx(rt2x00dev);
		अवरोध;
	हाल RT3290:
		rt2800_init_rfcsr_3290(rt2x00dev);
		अवरोध;
	हाल RT3352:
		rt2800_init_rfcsr_3352(rt2x00dev);
		अवरोध;
	हाल RT3390:
		rt2800_init_rfcsr_3390(rt2x00dev);
		अवरोध;
	हाल RT3883:
		rt2800_init_rfcsr_3883(rt2x00dev);
		अवरोध;
	हाल RT3572:
		rt2800_init_rfcsr_3572(rt2x00dev);
		अवरोध;
	हाल RT3593:
		rt2800_init_rfcsr_3593(rt2x00dev);
		अवरोध;
	हाल RT5350:
		rt2800_init_rfcsr_5350(rt2x00dev);
		अवरोध;
	हाल RT5390:
		rt2800_init_rfcsr_5390(rt2x00dev);
		अवरोध;
	हाल RT5392:
		rt2800_init_rfcsr_5392(rt2x00dev);
		अवरोध;
	हाल RT5592:
		rt2800_init_rfcsr_5592(rt2x00dev);
		अवरोध;
	हाल RT6352:
		rt2800_init_rfcsr_6352(rt2x00dev);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक rt2800_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	u16 word;

	/*
	 * Initialize MAC रेजिस्टरs.
	 */
	अगर (unlikely(rt2800_रुको_wpdma_पढ़ोy(rt2x00dev) ||
		     rt2800_init_रेजिस्टरs(rt2x00dev)))
		वापस -EIO;

	/*
	 * Wait BBP/RF to wake up.
	 */
	अगर (unlikely(rt2800_रुको_bbp_rf_पढ़ोy(rt2x00dev)))
		वापस -EIO;

	/*
	 * Send संकेत during boot समय to initialize firmware.
	 */
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_BBP_AGENT, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);
	अगर (rt2x00_is_usb(rt2x00dev))
		rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_INT_SRC, 0);
	rt2800_mcu_request(rt2x00dev, MCU_BOOT_SIGNAL, 0, 0, 0);
	msleep(1);

	/*
	 * Make sure BBP is up and running.
	 */
	अगर (unlikely(rt2800_रुको_bbp_पढ़ोy(rt2x00dev)))
		वापस -EIO;

	/*
	 * Initialize BBP/RF रेजिस्टरs.
	 */
	rt2800_init_bbp(rt2x00dev);
	rt2800_init_rfcsr(rt2x00dev);

	अगर (rt2x00_is_usb(rt2x00dev) &&
	    (rt2x00_rt(rt2x00dev, RT3070) ||
	     rt2x00_rt(rt2x00dev, RT3071) ||
	     rt2x00_rt(rt2x00dev, RT3572))) अणु
		udelay(200);
		rt2800_mcu_request(rt2x00dev, MCU_CURRENT, 0, 0, 0);
		udelay(10);
	पूर्ण

	/*
	 * Enable RX.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);

	udelay(50);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WPDMA_GLO_CFG);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_TX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_ENABLE_RX_DMA, 1);
	rt2x00_set_field32(&reg, WPDMA_GLO_CFG_TX_WRITEBACK_DONE, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WPDMA_GLO_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);

	/*
	 * Initialize LED control
	 */
	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LED_AG_CONF);
	rt2800_mcu_request(rt2x00dev, MCU_LED_AG_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LED_ACT_CONF);
	rt2800_mcu_request(rt2x00dev, MCU_LED_ACT_CONF, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LED_POLARITY);
	rt2800_mcu_request(rt2x00dev, MCU_LED_LED_POLARITY, 0xff,
			   word & 0xff, (word >> 8) & 0xff);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_enable_radio);

व्योम rt2800_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	rt2800_disable_wpdma(rt2x00dev);

	/* Wait क्रम DMA, ignore error */
	rt2800_रुको_wpdma_पढ़ोy(rt2x00dev);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 0);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_SYS_CTRL, reg);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_disable_radio);

पूर्णांक rt2800_efuse_detect(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	u16 efuse_ctrl_reg;

	अगर (rt2x00_rt(rt2x00dev, RT3290))
		efuse_ctrl_reg = EFUSE_CTRL_3290;
	अन्यथा
		efuse_ctrl_reg = EFUSE_CTRL;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, efuse_ctrl_reg);
	वापस rt2x00_get_field32(reg, EFUSE_CTRL_PRESENT);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_efuse_detect);

अटल व्योम rt2800_efuse_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev, अचिन्हित पूर्णांक i)
अणु
	u32 reg;
	u16 efuse_ctrl_reg;
	u16 efuse_data0_reg;
	u16 efuse_data1_reg;
	u16 efuse_data2_reg;
	u16 efuse_data3_reg;

	अगर (rt2x00_rt(rt2x00dev, RT3290)) अणु
		efuse_ctrl_reg = EFUSE_CTRL_3290;
		efuse_data0_reg = EFUSE_DATA0_3290;
		efuse_data1_reg = EFUSE_DATA1_3290;
		efuse_data2_reg = EFUSE_DATA2_3290;
		efuse_data3_reg = EFUSE_DATA3_3290;
	पूर्ण अन्यथा अणु
		efuse_ctrl_reg = EFUSE_CTRL;
		efuse_data0_reg = EFUSE_DATA0;
		efuse_data1_reg = EFUSE_DATA1;
		efuse_data2_reg = EFUSE_DATA2;
		efuse_data3_reg = EFUSE_DATA3;
	पूर्ण
	mutex_lock(&rt2x00dev->csr_mutex);

	reg = rt2800_रेजिस्टर_पढ़ो_lock(rt2x00dev, efuse_ctrl_reg);
	rt2x00_set_field32(&reg, EFUSE_CTRL_ADDRESS_IN, i);
	rt2x00_set_field32(&reg, EFUSE_CTRL_MODE, 0);
	rt2x00_set_field32(&reg, EFUSE_CTRL_KICK, 1);
	rt2800_रेजिस्टर_ग_लिखो_lock(rt2x00dev, efuse_ctrl_reg, reg);

	/* Wait until the EEPROM has been loaded */
	rt2800_regbusy_पढ़ो(rt2x00dev, efuse_ctrl_reg, EFUSE_CTRL_KICK, &reg);
	/* Apparently the data is पढ़ो from end to start */
	reg = rt2800_रेजिस्टर_पढ़ो_lock(rt2x00dev, efuse_data3_reg);
	/* The वापसed value is in CPU order, but eeprom is le */
	*(u32 *)&rt2x00dev->eeprom[i] = cpu_to_le32(reg);
	reg = rt2800_रेजिस्टर_पढ़ो_lock(rt2x00dev, efuse_data2_reg);
	*(u32 *)&rt2x00dev->eeprom[i + 2] = cpu_to_le32(reg);
	reg = rt2800_रेजिस्टर_पढ़ो_lock(rt2x00dev, efuse_data1_reg);
	*(u32 *)&rt2x00dev->eeprom[i + 4] = cpu_to_le32(reg);
	reg = rt2800_रेजिस्टर_पढ़ो_lock(rt2x00dev, efuse_data0_reg);
	*(u32 *)&rt2x00dev->eeprom[i + 6] = cpu_to_le32(reg);

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

पूर्णांक rt2800_पढ़ो_eeprom_efuse(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EEPROM_SIZE / माप(u16); i += 8)
		rt2800_efuse_पढ़ो(rt2x00dev, i);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_पढ़ो_eeprom_efuse);

अटल u8 rt2800_get_txmixer_gain_24g(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 word;

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		वापस 0;

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TXMIXER_GAIN_BG);
	अगर ((word & 0x00ff) != 0x00ff)
		वापस rt2x00_get_field16(word, EEPROM_TXMIXER_GAIN_BG_VAL);

	वापस 0;
पूर्ण

अटल u8 rt2800_get_txmixer_gain_5g(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 word;

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		वापस 0;

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_TXMIXER_GAIN_A);
	अगर ((word & 0x00ff) != 0x00ff)
		वापस rt2x00_get_field16(word, EEPROM_TXMIXER_GAIN_A_VAL);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800_validate_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u16 word;
	u8 *mac;
	u8 शेष_lna_gain;
	पूर्णांक retval;

	/*
	 * Read the EEPROM.
	 */
	retval = rt2800_पढ़ो_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Start validation of the data that has been पढ़ो.
	 */
	mac = rt2800_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	rt2x00lib_set_mac_address(rt2x00dev, mac);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF0);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RXPATH, 2);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_TXPATH, 1);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RF_TYPE, RF2820);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC_CONF0, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	पूर्ण अन्यथा अगर (rt2x00_rt(rt2x00dev, RT2860) ||
		   rt2x00_rt(rt2x00dev, RT2872)) अणु
		/*
		 * There is a max of 2 RX streams क्रम RT28x0 series
		 */
		अगर (rt2x00_get_field16(word, EEPROM_NIC_CONF0_RXPATH) > 2)
			rt2x00_set_field16(&word, EEPROM_NIC_CONF0_RXPATH, 2);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC_CONF0, word);
	पूर्ण

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_HW_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_TX_ALC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_LNA_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_EXTERNAL_LNA_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_SB_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_SB_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_WPS_PBC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_2G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BW40M_5G, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BROADBAND_EXT_LNA, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_ANT_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_INTERNAL_TX_ALC, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_BT_COEXIST, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CONF1_DAC_TEST, 0);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC_CONF1, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	पूर्ण

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
	अगर ((word & 0x00ff) == 0x00ff) अणु
		rt2x00_set_field16(&word, EEPROM_FREQ_OFFSET, 0);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_FREQ, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Freq: 0x%04x\n", word);
	पूर्ण
	अगर ((word & 0xff00) == 0xff00) अणु
		rt2x00_set_field16(&word, EEPROM_FREQ_LED_MODE,
				   LED_MODE_TXRX_ACTIVITY);
		rt2x00_set_field16(&word, EEPROM_FREQ_LED_POLARITY, 0);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_FREQ, word);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_LED_AG_CONF, 0x5555);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_LED_ACT_CONF, 0x2221);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_LED_POLARITY, 0xa9f8);
		rt2x00_eeprom_dbg(rt2x00dev, "Led Mode: 0x%04x\n", word);
	पूर्ण

	/*
	 * During the LNA validation we are going to use
	 * lna0 as correct value. Note that EEPROM_LNA
	 * is never validated.
	 */
	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_LNA);
	शेष_lna_gain = rt2x00_get_field16(word, EEPROM_LNA_A0);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_BG);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_BG_OFFSET0)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG_OFFSET0, 0);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_BG_OFFSET1)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG_OFFSET1, 0);
	rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_BG, word);

	drv_data->txmixer_gain_24g = rt2800_get_txmixer_gain_24g(rt2x00dev);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_BG2);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_BG2_OFFSET2)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_BG2_OFFSET2, 0);
	अगर (!rt2x00_rt(rt2x00dev, RT3593) &&
	    !rt2x00_rt(rt2x00dev, RT3883)) अणु
		अगर (rt2x00_get_field16(word, EEPROM_RSSI_BG2_LNA_A1) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_RSSI_BG2_LNA_A1) == 0xff)
			rt2x00_set_field16(&word, EEPROM_RSSI_BG2_LNA_A1,
					   शेष_lna_gain);
	पूर्ण
	rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_BG2, word);

	drv_data->txmixer_gain_5g = rt2800_get_txmixer_gain_5g(rt2x00dev);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_A);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_A_OFFSET0)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A_OFFSET0, 0);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_A_OFFSET1)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A_OFFSET1, 0);
	rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_A, word);

	word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_A2);
	अगर (असल(rt2x00_get_field16(word, EEPROM_RSSI_A2_OFFSET2)) > 10)
		rt2x00_set_field16(&word, EEPROM_RSSI_A2_OFFSET2, 0);
	अगर (!rt2x00_rt(rt2x00dev, RT3593) &&
	    !rt2x00_rt(rt2x00dev, RT3883)) अणु
		अगर (rt2x00_get_field16(word, EEPROM_RSSI_A2_LNA_A2) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_RSSI_A2_LNA_A2) == 0xff)
			rt2x00_set_field16(&word, EEPROM_RSSI_A2_LNA_A2,
					   शेष_lna_gain);
	पूर्ण
	rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_A2, word);

	अगर (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883)) अणु
		word = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_EXT_LNA2);
		अगर (rt2x00_get_field16(word, EEPROM_EXT_LNA2_A1) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_EXT_LNA2_A1) == 0xff)
			rt2x00_set_field16(&word, EEPROM_EXT_LNA2_A1,
					   शेष_lna_gain);
		अगर (rt2x00_get_field16(word, EEPROM_EXT_LNA2_A2) == 0x00 ||
		    rt2x00_get_field16(word, EEPROM_EXT_LNA2_A2) == 0xff)
			rt2x00_set_field16(&word, EEPROM_EXT_LNA2_A1,
					   शेष_lna_gain);
		rt2800_eeprom_ग_लिखो(rt2x00dev, EEPROM_EXT_LNA2, word);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800_init_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 value;
	u16 eeprom;
	u16 rf;

	/*
	 * Read EEPROM word क्रम configuration.
	 */
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF0);

	/*
	 * Identअगरy RF chipset by EEPROM value
	 * RT28xx/RT30xx: defined in "EEPROM_NIC_CONF0_RF_TYPE" field
	 * RT53xx: defined in "EEPROM_CHIP_ID" field
	 */
	अगर (rt2x00_rt(rt2x00dev, RT3290) ||
	    rt2x00_rt(rt2x00dev, RT5390) ||
	    rt2x00_rt(rt2x00dev, RT5392) ||
	    rt2x00_rt(rt2x00dev, RT6352))
		rf = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_CHIP_ID);
	अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3352))
		rf = RF3322;
	अन्यथा अगर (rt2x00_rt(rt2x00dev, RT3883))
		rf = RF3853;
	अन्यथा अगर (rt2x00_rt(rt2x00dev, RT5350))
		rf = RF5350;
	अन्यथा
		rf = rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RF_TYPE);

	चयन (rf) अणु
	हाल RF2820:
	हाल RF2850:
	हाल RF2720:
	हाल RF2750:
	हाल RF3020:
	हाल RF2020:
	हाल RF3021:
	हाल RF3022:
	हाल RF3052:
	हाल RF3053:
	हाल RF3070:
	हाल RF3290:
	हाल RF3320:
	हाल RF3322:
	हाल RF3853:
	हाल RF5350:
	हाल RF5360:
	हाल RF5362:
	हाल RF5370:
	हाल RF5372:
	हाल RF5390:
	हाल RF5392:
	हाल RF5592:
	हाल RF7620:
		अवरोध;
	शेष:
		rt2x00_err(rt2x00dev, "Invalid RF chipset 0x%04x detected\n",
			   rf);
		वापस -ENODEV;
	पूर्ण

	rt2x00_set_rf(rt2x00dev, rf);

	/*
	 * Identअगरy शेष antenna configuration.
	 */
	rt2x00dev->शेष_ant.tx_chain_num =
	    rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_TXPATH);
	rt2x00dev->शेष_ant.rx_chain_num =
	    rt2x00_get_field16(eeprom, EEPROM_NIC_CONF0_RXPATH);

	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);

	अगर (rt2x00_rt(rt2x00dev, RT3070) ||
	    rt2x00_rt(rt2x00dev, RT3090) ||
	    rt2x00_rt(rt2x00dev, RT3352) ||
	    rt2x00_rt(rt2x00dev, RT3390)) अणु
		value = rt2x00_get_field16(eeprom,
				EEPROM_NIC_CONF1_ANT_DIVERSITY);
		चयन (value) अणु
		हाल 0:
		हाल 1:
		हाल 2:
			rt2x00dev->शेष_ant.tx = ANTENNA_A;
			rt2x00dev->शेष_ant.rx = ANTENNA_A;
			अवरोध;
		हाल 3:
			rt2x00dev->शेष_ant.tx = ANTENNA_A;
			rt2x00dev->शेष_ant.rx = ANTENNA_B;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rt2x00dev->शेष_ant.tx = ANTENNA_A;
		rt2x00dev->शेष_ant.rx = ANTENNA_A;
	पूर्ण

	/* These chips have hardware RX antenna भागersity */
	अगर (rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5390R) ||
	    rt2x00_rt_rev_gte(rt2x00dev, RT5390, REV_RT5370G)) अणु
		rt2x00dev->शेष_ant.tx = ANTENNA_HW_DIVERSITY; /* Unused */
		rt2x00dev->शेष_ant.rx = ANTENNA_HW_DIVERSITY; /* Unused */
	पूर्ण

	/*
	 * Determine बाह्यal LNA inक्रमmations.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_EXTERNAL_LNA_5G))
		__set_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_EXTERNAL_LNA_2G))
		__set_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags);

	/*
	 * Detect अगर this device has an hardware controlled radio.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_HW_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Detect अगर this device has Bluetooth co-existence.
	 */
	अगर (!rt2x00_rt(rt2x00dev, RT3352) &&
	    rt2x00_get_field16(eeprom, EEPROM_NIC_CONF1_BT_COEXIST))
		__set_bit(CAPABILITY_BT_COEXIST, &rt2x00dev->cap_flags);

	/*
	 * Read frequency offset and RF programming sequence.
	 */
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
	rt2x00dev->freq_offset = rt2x00_get_field16(eeprom, EEPROM_FREQ_OFFSET);

	/*
	 * Store led settings, क्रम correct led behaviour.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
	rt2800_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	rt2800_init_led(rt2x00dev, &rt2x00dev->led_assoc, LED_TYPE_ASSOC);
	rt2800_init_led(rt2x00dev, &rt2x00dev->led_qual, LED_TYPE_QUALITY);

	rt2x00dev->led_mcu_reg = eeprom;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Check अगर support EIRP tx घातer limit feature.
	 */
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_EIRP_MAX_TX_POWER);

	अगर (rt2x00_get_field16(eeprom, EEPROM_EIRP_MAX_TX_POWER_2GHZ) <
					EIRP_MAX_TX_POWER_LIMIT)
		__set_bit(CAPABILITY_POWER_LIMIT, &rt2x00dev->cap_flags);

	/*
	 * Detect अगर device uses पूर्णांकernal or बाह्यal PA
	 */
	eeprom = rt2800_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC_CONF1);

	अगर (rt2x00_rt(rt2x00dev, RT3352)) अणु
		अगर (rt2x00_get_field16(eeprom,
		    EEPROM_NIC_CONF1_EXTERNAL_TX0_PA_3352))
		    __set_bit(CAPABILITY_EXTERNAL_PA_TX0,
			      &rt2x00dev->cap_flags);
		अगर (rt2x00_get_field16(eeprom,
		    EEPROM_NIC_CONF1_EXTERNAL_TX1_PA_3352))
		    __set_bit(CAPABILITY_EXTERNAL_PA_TX1,
			      &rt2x00dev->cap_flags);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * RF value list क्रम rt28xx
 * Supports: 2.4 GHz (all) & 5.2 GHz (RF2850 & RF2750)
 */
अटल स्थिर काष्ठा rf_channel rf_vals[] = अणु
	अणु 1,  0x18402ecc, 0x184c0786, 0x1816b455, 0x1800510b पूर्ण,
	अणु 2,  0x18402ecc, 0x184c0786, 0x18168a55, 0x1800519f पूर्ण,
	अणु 3,  0x18402ecc, 0x184c078a, 0x18168a55, 0x1800518b पूर्ण,
	अणु 4,  0x18402ecc, 0x184c078a, 0x18168a55, 0x1800519f पूर्ण,
	अणु 5,  0x18402ecc, 0x184c078e, 0x18168a55, 0x1800518b पूर्ण,
	अणु 6,  0x18402ecc, 0x184c078e, 0x18168a55, 0x1800519f पूर्ण,
	अणु 7,  0x18402ecc, 0x184c0792, 0x18168a55, 0x1800518b पूर्ण,
	अणु 8,  0x18402ecc, 0x184c0792, 0x18168a55, 0x1800519f पूर्ण,
	अणु 9,  0x18402ecc, 0x184c0796, 0x18168a55, 0x1800518b पूर्ण,
	अणु 10, 0x18402ecc, 0x184c0796, 0x18168a55, 0x1800519f पूर्ण,
	अणु 11, 0x18402ecc, 0x184c079a, 0x18168a55, 0x1800518b पूर्ण,
	अणु 12, 0x18402ecc, 0x184c079a, 0x18168a55, 0x1800519f पूर्ण,
	अणु 13, 0x18402ecc, 0x184c079e, 0x18168a55, 0x1800518b पूर्ण,
	अणु 14, 0x18402ecc, 0x184c07a2, 0x18168a55, 0x18005193 पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु 36, 0x18402ecc, 0x184c099a, 0x18158a55, 0x180ed1a3 पूर्ण,
	अणु 38, 0x18402ecc, 0x184c099e, 0x18158a55, 0x180ed193 पूर्ण,
	अणु 40, 0x18402ec8, 0x184c0682, 0x18158a55, 0x180ed183 पूर्ण,
	अणु 44, 0x18402ec8, 0x184c0682, 0x18158a55, 0x180ed1a3 पूर्ण,
	अणु 46, 0x18402ec8, 0x184c0686, 0x18158a55, 0x180ed18b पूर्ण,
	अणु 48, 0x18402ec8, 0x184c0686, 0x18158a55, 0x180ed19b पूर्ण,
	अणु 52, 0x18402ec8, 0x184c068a, 0x18158a55, 0x180ed193 पूर्ण,
	अणु 54, 0x18402ec8, 0x184c068a, 0x18158a55, 0x180ed1a3 पूर्ण,
	अणु 56, 0x18402ec8, 0x184c068e, 0x18158a55, 0x180ed18b पूर्ण,
	अणु 60, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed183 पूर्ण,
	अणु 62, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed193 पूर्ण,
	अणु 64, 0x18402ec8, 0x184c0692, 0x18158a55, 0x180ed1a3 पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु 100, 0x18402ec8, 0x184c06b2, 0x18178a55, 0x180ed783 पूर्ण,
	अणु 102, 0x18402ec8, 0x184c06b2, 0x18578a55, 0x180ed793 पूर्ण,
	अणु 104, 0x18402ec8, 0x185c06b2, 0x18578a55, 0x180ed1a3 पूर्ण,
	अणु 108, 0x18402ecc, 0x185c0a32, 0x18578a55, 0x180ed193 पूर्ण,
	अणु 110, 0x18402ecc, 0x184c0a36, 0x18178a55, 0x180ed183 पूर्ण,
	अणु 112, 0x18402ecc, 0x184c0a36, 0x18178a55, 0x180ed19b पूर्ण,
	अणु 116, 0x18402ecc, 0x184c0a3a, 0x18178a55, 0x180ed1a3 पूर्ण,
	अणु 118, 0x18402ecc, 0x184c0a3e, 0x18178a55, 0x180ed193 पूर्ण,
	अणु 120, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed183 पूर्ण,
	अणु 124, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed193 पूर्ण,
	अणु 126, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed15b पूर्ण,
	अणु 128, 0x18402ec4, 0x184c0382, 0x18178a55, 0x180ed1a3 पूर्ण,
	अणु 132, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed18b पूर्ण,
	अणु 134, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed193 पूर्ण,
	अणु 136, 0x18402ec4, 0x184c0386, 0x18178a55, 0x180ed19b पूर्ण,
	अणु 140, 0x18402ec4, 0x184c038a, 0x18178a55, 0x180ed183 पूर्ण,

	/* 802.11 UNII */
	अणु 149, 0x18402ec4, 0x184c038a, 0x18178a55, 0x180ed1a7 पूर्ण,
	अणु 151, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed187 पूर्ण,
	अणु 153, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed18f पूर्ण,
	अणु 157, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed19f पूर्ण,
	अणु 159, 0x18402ec4, 0x184c038e, 0x18178a55, 0x180ed1a7 पूर्ण,
	अणु 161, 0x18402ec4, 0x184c0392, 0x18178a55, 0x180ed187 पूर्ण,
	अणु 165, 0x18402ec4, 0x184c0392, 0x18178a55, 0x180ed197 पूर्ण,
	अणु 167, 0x18402ec4, 0x184c03d2, 0x18179855, 0x1815531f पूर्ण,
	अणु 169, 0x18402ec4, 0x184c03d2, 0x18179855, 0x18155327 पूर्ण,
	अणु 171, 0x18402ec4, 0x184c03d6, 0x18179855, 0x18155307 पूर्ण,
	अणु 173, 0x18402ec4, 0x184c03d6, 0x18179855, 0x1815530f पूर्ण,

	/* 802.11 Japan */
	अणु 184, 0x15002ccc, 0x1500491e, 0x1509be55, 0x150c0a0b पूर्ण,
	अणु 188, 0x15002ccc, 0x15004922, 0x1509be55, 0x150c0a13 पूर्ण,
	अणु 192, 0x15002ccc, 0x15004926, 0x1509be55, 0x150c0a1b पूर्ण,
	अणु 196, 0x15002ccc, 0x1500492a, 0x1509be55, 0x150c0a23 पूर्ण,
	अणु 208, 0x15002ccc, 0x1500493a, 0x1509be55, 0x150c0a13 पूर्ण,
	अणु 212, 0x15002ccc, 0x1500493e, 0x1509be55, 0x150c0a1b पूर्ण,
	अणु 216, 0x15002ccc, 0x15004982, 0x1509be55, 0x150c0a23 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम rt3xxx
 * Supports: 2.4 GHz (all) & 5.2 GHz (RF3052 & RF3053)
 */
अटल स्थिर काष्ठा rf_channel rf_vals_3x[] = अणु
	अणु1,  241, 2, 2 पूर्ण,
	अणु2,  241, 2, 7 पूर्ण,
	अणु3,  242, 2, 2 पूर्ण,
	अणु4,  242, 2, 7 पूर्ण,
	अणु5,  243, 2, 2 पूर्ण,
	अणु6,  243, 2, 7 पूर्ण,
	अणु7,  244, 2, 2 पूर्ण,
	अणु8,  244, 2, 7 पूर्ण,
	अणु9,  245, 2, 2 पूर्ण,
	अणु10, 245, 2, 7 पूर्ण,
	अणु11, 246, 2, 2 पूर्ण,
	अणु12, 246, 2, 7 पूर्ण,
	अणु13, 247, 2, 2 पूर्ण,
	अणु14, 248, 2, 4 पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु36, 0x56, 0, 4पूर्ण,
	अणु38, 0x56, 0, 6पूर्ण,
	अणु40, 0x56, 0, 8पूर्ण,
	अणु44, 0x57, 0, 0पूर्ण,
	अणु46, 0x57, 0, 2पूर्ण,
	अणु48, 0x57, 0, 4पूर्ण,
	अणु52, 0x57, 0, 8पूर्ण,
	अणु54, 0x57, 0, 10पूर्ण,
	अणु56, 0x58, 0, 0पूर्ण,
	अणु60, 0x58, 0, 4पूर्ण,
	अणु62, 0x58, 0, 6पूर्ण,
	अणु64, 0x58, 0, 8पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु100, 0x5b, 0, 8पूर्ण,
	अणु102, 0x5b, 0, 10पूर्ण,
	अणु104, 0x5c, 0, 0पूर्ण,
	अणु108, 0x5c, 0, 4पूर्ण,
	अणु110, 0x5c, 0, 6पूर्ण,
	अणु112, 0x5c, 0, 8पूर्ण,
	अणु116, 0x5d, 0, 0पूर्ण,
	अणु118, 0x5d, 0, 2पूर्ण,
	अणु120, 0x5d, 0, 4पूर्ण,
	अणु124, 0x5d, 0, 8पूर्ण,
	अणु126, 0x5d, 0, 10पूर्ण,
	अणु128, 0x5e, 0, 0पूर्ण,
	अणु132, 0x5e, 0, 4पूर्ण,
	अणु134, 0x5e, 0, 6पूर्ण,
	अणु136, 0x5e, 0, 8पूर्ण,
	अणु140, 0x5f, 0, 0पूर्ण,

	/* 802.11 UNII */
	अणु149, 0x5f, 0, 9पूर्ण,
	अणु151, 0x5f, 0, 11पूर्ण,
	अणु153, 0x60, 0, 1पूर्ण,
	अणु157, 0x60, 0, 5पूर्ण,
	अणु159, 0x60, 0, 7पूर्ण,
	अणु161, 0x60, 0, 9पूर्ण,
	अणु165, 0x61, 0, 1पूर्ण,
	अणु167, 0x61, 0, 3पूर्ण,
	अणु169, 0x61, 0, 5पूर्ण,
	अणु171, 0x61, 0, 7पूर्ण,
	अणु173, 0x61, 0, 9पूर्ण,
पूर्ण;

/*
 * RF value list क्रम rt3xxx with Xtal20MHz
 * Supports: 2.4 GHz (all) (RF3322)
 */
अटल स्थिर काष्ठा rf_channel rf_vals_3x_xtal20[] = अणु
	अणु1,    0xE2,	 2,  0x14पूर्ण,
	अणु2,    0xE3,	 2,  0x14पूर्ण,
	अणु3,    0xE4,	 2,  0x14पूर्ण,
	अणु4,    0xE5,	 2,  0x14पूर्ण,
	अणु5,    0xE6,	 2,  0x14पूर्ण,
	अणु6,    0xE7,	 2,  0x14पूर्ण,
	अणु7,    0xE8,	 2,  0x14पूर्ण,
	अणु8,    0xE9,	 2,  0x14पूर्ण,
	अणु9,    0xEA,	 2,  0x14पूर्ण,
	अणु10,   0xEB,	 2,  0x14पूर्ण,
	अणु11,   0xEC,	 2,  0x14पूर्ण,
	अणु12,   0xED,	 2,  0x14पूर्ण,
	अणु13,   0xEE,	 2,  0x14पूर्ण,
	अणु14,   0xF0,	 2,  0x18पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rf_channel rf_vals_3853[] = अणु
	अणु1,  241, 6, 2पूर्ण,
	अणु2,  241, 6, 7पूर्ण,
	अणु3,  242, 6, 2पूर्ण,
	अणु4,  242, 6, 7पूर्ण,
	अणु5,  243, 6, 2पूर्ण,
	अणु6,  243, 6, 7पूर्ण,
	अणु7,  244, 6, 2पूर्ण,
	अणु8,  244, 6, 7पूर्ण,
	अणु9,  245, 6, 2पूर्ण,
	अणु10, 245, 6, 7पूर्ण,
	अणु11, 246, 6, 2पूर्ण,
	अणु12, 246, 6, 7पूर्ण,
	अणु13, 247, 6, 2पूर्ण,
	अणु14, 248, 6, 4पूर्ण,

	अणु36, 0x56, 8, 4पूर्ण,
	अणु38, 0x56, 8, 6पूर्ण,
	अणु40, 0x56, 8, 8पूर्ण,
	अणु44, 0x57, 8, 0पूर्ण,
	अणु46, 0x57, 8, 2पूर्ण,
	अणु48, 0x57, 8, 4पूर्ण,
	अणु52, 0x57, 8, 8पूर्ण,
	अणु54, 0x57, 8, 10पूर्ण,
	अणु56, 0x58, 8, 0पूर्ण,
	अणु60, 0x58, 8, 4पूर्ण,
	अणु62, 0x58, 8, 6पूर्ण,
	अणु64, 0x58, 8, 8पूर्ण,

	अणु100, 0x5b, 8, 8पूर्ण,
	अणु102, 0x5b, 8, 10पूर्ण,
	अणु104, 0x5c, 8, 0पूर्ण,
	अणु108, 0x5c, 8, 4पूर्ण,
	अणु110, 0x5c, 8, 6पूर्ण,
	अणु112, 0x5c, 8, 8पूर्ण,
	अणु114, 0x5c, 8, 10पूर्ण,
	अणु116, 0x5d, 8, 0पूर्ण,
	अणु118, 0x5d, 8, 2पूर्ण,
	अणु120, 0x5d, 8, 4पूर्ण,
	अणु124, 0x5d, 8, 8पूर्ण,
	अणु126, 0x5d, 8, 10पूर्ण,
	अणु128, 0x5e, 8, 0पूर्ण,
	अणु132, 0x5e, 8, 4पूर्ण,
	अणु134, 0x5e, 8, 6पूर्ण,
	अणु136, 0x5e, 8, 8पूर्ण,
	अणु140, 0x5f, 8, 0पूर्ण,

	अणु149, 0x5f, 8, 9पूर्ण,
	अणु151, 0x5f, 8, 11पूर्ण,
	अणु153, 0x60, 8, 1पूर्ण,
	अणु157, 0x60, 8, 5पूर्ण,
	अणु159, 0x60, 8, 7पूर्ण,
	अणु161, 0x60, 8, 9पूर्ण,
	अणु165, 0x61, 8, 1पूर्ण,
	अणु167, 0x61, 8, 3पूर्ण,
	अणु169, 0x61, 8, 5पूर्ण,
	अणु171, 0x61, 8, 7पूर्ण,
	अणु173, 0x61, 8, 9पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rf_channel rf_vals_5592_xtal20[] = अणु
	/* Channel, N, K, mod, R */
	अणु1, 482, 4, 10, 3पूर्ण,
	अणु2, 483, 4, 10, 3पूर्ण,
	अणु3, 484, 4, 10, 3पूर्ण,
	अणु4, 485, 4, 10, 3पूर्ण,
	अणु5, 486, 4, 10, 3पूर्ण,
	अणु6, 487, 4, 10, 3पूर्ण,
	अणु7, 488, 4, 10, 3पूर्ण,
	अणु8, 489, 4, 10, 3पूर्ण,
	अणु9, 490, 4, 10, 3पूर्ण,
	अणु10, 491, 4, 10, 3पूर्ण,
	अणु11, 492, 4, 10, 3पूर्ण,
	अणु12, 493, 4, 10, 3पूर्ण,
	अणु13, 494, 4, 10, 3पूर्ण,
	अणु14, 496, 8, 10, 3पूर्ण,
	अणु36, 172, 8, 12, 1पूर्ण,
	अणु38, 173, 0, 12, 1पूर्ण,
	अणु40, 173, 4, 12, 1पूर्ण,
	अणु42, 173, 8, 12, 1पूर्ण,
	अणु44, 174, 0, 12, 1पूर्ण,
	अणु46, 174, 4, 12, 1पूर्ण,
	अणु48, 174, 8, 12, 1पूर्ण,
	अणु50, 175, 0, 12, 1पूर्ण,
	अणु52, 175, 4, 12, 1पूर्ण,
	अणु54, 175, 8, 12, 1पूर्ण,
	अणु56, 176, 0, 12, 1पूर्ण,
	अणु58, 176, 4, 12, 1पूर्ण,
	अणु60, 176, 8, 12, 1पूर्ण,
	अणु62, 177, 0, 12, 1पूर्ण,
	अणु64, 177, 4, 12, 1पूर्ण,
	अणु100, 183, 4, 12, 1पूर्ण,
	अणु102, 183, 8, 12, 1पूर्ण,
	अणु104, 184, 0, 12, 1पूर्ण,
	अणु106, 184, 4, 12, 1पूर्ण,
	अणु108, 184, 8, 12, 1पूर्ण,
	अणु110, 185, 0, 12, 1पूर्ण,
	अणु112, 185, 4, 12, 1पूर्ण,
	अणु114, 185, 8, 12, 1पूर्ण,
	अणु116, 186, 0, 12, 1पूर्ण,
	अणु118, 186, 4, 12, 1पूर्ण,
	अणु120, 186, 8, 12, 1पूर्ण,
	अणु122, 187, 0, 12, 1पूर्ण,
	अणु124, 187, 4, 12, 1पूर्ण,
	अणु126, 187, 8, 12, 1पूर्ण,
	अणु128, 188, 0, 12, 1पूर्ण,
	अणु130, 188, 4, 12, 1पूर्ण,
	अणु132, 188, 8, 12, 1पूर्ण,
	अणु134, 189, 0, 12, 1पूर्ण,
	अणु136, 189, 4, 12, 1पूर्ण,
	अणु138, 189, 8, 12, 1पूर्ण,
	अणु140, 190, 0, 12, 1पूर्ण,
	अणु149, 191, 6, 12, 1पूर्ण,
	अणु151, 191, 10, 12, 1पूर्ण,
	अणु153, 192, 2, 12, 1पूर्ण,
	अणु155, 192, 6, 12, 1पूर्ण,
	अणु157, 192, 10, 12, 1पूर्ण,
	अणु159, 193, 2, 12, 1पूर्ण,
	अणु161, 193, 6, 12, 1पूर्ण,
	अणु165, 194, 2, 12, 1पूर्ण,
	अणु184, 164, 0, 12, 1पूर्ण,
	अणु188, 164, 4, 12, 1पूर्ण,
	अणु192, 165, 8, 12, 1पूर्ण,
	अणु196, 166, 0, 12, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rf_channel rf_vals_5592_xtal40[] = अणु
	/* Channel, N, K, mod, R */
	अणु1, 241, 2, 10, 3पूर्ण,
	अणु2, 241, 7, 10, 3पूर्ण,
	अणु3, 242, 2, 10, 3पूर्ण,
	अणु4, 242, 7, 10, 3पूर्ण,
	अणु5, 243, 2, 10, 3पूर्ण,
	अणु6, 243, 7, 10, 3पूर्ण,
	अणु7, 244, 2, 10, 3पूर्ण,
	अणु8, 244, 7, 10, 3पूर्ण,
	अणु9, 245, 2, 10, 3पूर्ण,
	अणु10, 245, 7, 10, 3पूर्ण,
	अणु11, 246, 2, 10, 3पूर्ण,
	अणु12, 246, 7, 10, 3पूर्ण,
	अणु13, 247, 2, 10, 3पूर्ण,
	अणु14, 248, 4, 10, 3पूर्ण,
	अणु36, 86, 4, 12, 1पूर्ण,
	अणु38, 86, 6, 12, 1पूर्ण,
	अणु40, 86, 8, 12, 1पूर्ण,
	अणु42, 86, 10, 12, 1पूर्ण,
	अणु44, 87, 0, 12, 1पूर्ण,
	अणु46, 87, 2, 12, 1पूर्ण,
	अणु48, 87, 4, 12, 1पूर्ण,
	अणु50, 87, 6, 12, 1पूर्ण,
	अणु52, 87, 8, 12, 1पूर्ण,
	अणु54, 87, 10, 12, 1पूर्ण,
	अणु56, 88, 0, 12, 1पूर्ण,
	अणु58, 88, 2, 12, 1पूर्ण,
	अणु60, 88, 4, 12, 1पूर्ण,
	अणु62, 88, 6, 12, 1पूर्ण,
	अणु64, 88, 8, 12, 1पूर्ण,
	अणु100, 91, 8, 12, 1पूर्ण,
	अणु102, 91, 10, 12, 1पूर्ण,
	अणु104, 92, 0, 12, 1पूर्ण,
	अणु106, 92, 2, 12, 1पूर्ण,
	अणु108, 92, 4, 12, 1पूर्ण,
	अणु110, 92, 6, 12, 1पूर्ण,
	अणु112, 92, 8, 12, 1पूर्ण,
	अणु114, 92, 10, 12, 1पूर्ण,
	अणु116, 93, 0, 12, 1पूर्ण,
	अणु118, 93, 2, 12, 1पूर्ण,
	अणु120, 93, 4, 12, 1पूर्ण,
	अणु122, 93, 6, 12, 1पूर्ण,
	अणु124, 93, 8, 12, 1पूर्ण,
	अणु126, 93, 10, 12, 1पूर्ण,
	अणु128, 94, 0, 12, 1पूर्ण,
	अणु130, 94, 2, 12, 1पूर्ण,
	अणु132, 94, 4, 12, 1पूर्ण,
	अणु134, 94, 6, 12, 1पूर्ण,
	अणु136, 94, 8, 12, 1पूर्ण,
	अणु138, 94, 10, 12, 1पूर्ण,
	अणु140, 95, 0, 12, 1पूर्ण,
	अणु149, 95, 9, 12, 1पूर्ण,
	अणु151, 95, 11, 12, 1पूर्ण,
	अणु153, 96, 1, 12, 1पूर्ण,
	अणु155, 96, 3, 12, 1पूर्ण,
	अणु157, 96, 5, 12, 1पूर्ण,
	अणु159, 96, 7, 12, 1पूर्ण,
	अणु161, 96, 9, 12, 1पूर्ण,
	अणु165, 97, 1, 12, 1पूर्ण,
	अणु184, 82, 0, 12, 1पूर्ण,
	अणु188, 82, 4, 12, 1पूर्ण,
	अणु192, 82, 8, 12, 1पूर्ण,
	अणु196, 83, 0, 12, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rf_channel rf_vals_7620[] = अणु
	अणु1, 0x50, 0x99, 0x99, 1पूर्ण,
	अणु2, 0x50, 0x44, 0x44, 2पूर्ण,
	अणु3, 0x50, 0xEE, 0xEE, 2पूर्ण,
	अणु4, 0x50, 0x99, 0x99, 3पूर्ण,
	अणु5, 0x51, 0x44, 0x44, 0पूर्ण,
	अणु6, 0x51, 0xEE, 0xEE, 0पूर्ण,
	अणु7, 0x51, 0x99, 0x99, 1पूर्ण,
	अणु8, 0x51, 0x44, 0x44, 2पूर्ण,
	अणु9, 0x51, 0xEE, 0xEE, 2पूर्ण,
	अणु10, 0x51, 0x99, 0x99, 3पूर्ण,
	अणु11, 0x52, 0x44, 0x44, 0पूर्ण,
	अणु12, 0x52, 0xEE, 0xEE, 0पूर्ण,
	अणु13, 0x52, 0x99, 0x99, 1पूर्ण,
	अणु14, 0x52, 0x33, 0x33, 3पूर्ण,
पूर्ण;

अटल पूर्णांक rt2800_probe_hw_mode(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	काष्ठा channel_info *info;
	अक्षर *शेष_घातer1;
	अक्षर *शेष_घातer2;
	अक्षर *शेष_घातer3;
	अचिन्हित पूर्णांक i, tx_chains, rx_chains;
	u32 reg;

	/*
	 * Disable घातersaving as शेष.
	 */
	rt2x00dev->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	/*
	 * Change शेष retry settings to values corresponding more बंदly
	 * to rate[0].count setting of minstrel rate control algorithm.
	 */
	rt2x00dev->hw->wiphy->retry_लघु = 2;
	rt2x00dev->hw->wiphy->retry_दीर्घ = 2;

	/*
	 * Initialize all hw fields.
	 */
	ieee80211_hw_set(rt2x00dev->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(rt2x00dev->hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(rt2x00dev->hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);

	/*
	 * Don't set IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING क्रम USB devices
	 * unless we are capable of sending the buffered frames out after the
	 * DTIM transmission using rt2x00lib_beaconकरोne. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some समय.
	 */
	अगर (!rt2x00_is_usb(rt2x00dev))
		ieee80211_hw_set(rt2x00dev->hw, HOST_BROADCAST_PS_BUFFERING);

	ieee80211_hw_set(rt2x00dev->hw, MFP_CAPABLE);

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2800_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * As rt2800 has a global fallback table we cannot specअगरy
	 * more then one tx rate per frame but since the hw will
	 * try several rates (based on the fallback table) we should
	 * initialize max_report_rates to the maximum number of rates
	 * we are going to try. Otherwise mac80211 will truncate our
	 * reported tx rates and the rc algortihm will end up with
	 * incorrect data.
	 */
	rt2x00dev->hw->max_rates = 1;
	rt2x00dev->hw->max_report_rates = 7;
	rt2x00dev->hw->max_rate_tries = 1;

	/*
	 * Initialize hw_mode inक्रमmation.
	 */
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	चयन (rt2x00dev->chip.rf) अणु
	हाल RF2720:
	हाल RF2820:
		spec->num_channels = 14;
		spec->channels = rf_vals;
		अवरोध;

	हाल RF2750:
	हाल RF2850:
		spec->num_channels = ARRAY_SIZE(rf_vals);
		spec->channels = rf_vals;
		अवरोध;

	हाल RF2020:
	हाल RF3020:
	हाल RF3021:
	हाल RF3022:
	हाल RF3070:
	हाल RF3290:
	हाल RF3320:
	हाल RF3322:
	हाल RF5350:
	हाल RF5360:
	हाल RF5362:
	हाल RF5370:
	हाल RF5372:
	हाल RF5390:
	हाल RF5392:
		spec->num_channels = 14;
		अगर (rt2800_clk_is_20mhz(rt2x00dev))
			spec->channels = rf_vals_3x_xtal20;
		अन्यथा
			spec->channels = rf_vals_3x;
		अवरोध;

	हाल RF7620:
		spec->num_channels = ARRAY_SIZE(rf_vals_7620);
		spec->channels = rf_vals_7620;
		अवरोध;

	हाल RF3052:
	हाल RF3053:
		spec->num_channels = ARRAY_SIZE(rf_vals_3x);
		spec->channels = rf_vals_3x;
		अवरोध;

	हाल RF3853:
		spec->num_channels = ARRAY_SIZE(rf_vals_3853);
		spec->channels = rf_vals_3853;
		अवरोध;

	हाल RF5592:
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_DEBUG_INDEX);
		अगर (rt2x00_get_field32(reg, MAC_DEBUG_INDEX_XTAL)) अणु
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal40);
			spec->channels = rf_vals_5592_xtal40;
		पूर्ण अन्यथा अणु
			spec->num_channels = ARRAY_SIZE(rf_vals_5592_xtal20);
			spec->channels = rf_vals_5592_xtal20;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (WARN_ON_ONCE(!spec->channels))
		वापस -ENODEV;

	spec->supported_bands = SUPPORT_BAND_2GHZ;
	अगर (spec->num_channels > 14)
		spec->supported_bands |= SUPPORT_BAND_5GHZ;

	/*
	 * Initialize HT inक्रमmation.
	 */
	अगर (!rt2x00_rf(rt2x00dev, RF2020))
		spec->ht.ht_supported = true;
	अन्यथा
		spec->ht.ht_supported = false;

	spec->ht.cap =
	    IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	    IEEE80211_HT_CAP_GRN_FLD |
	    IEEE80211_HT_CAP_SGI_20 |
	    IEEE80211_HT_CAP_SGI_40;

	tx_chains = rt2x00dev->शेष_ant.tx_chain_num;
	rx_chains = rt2x00dev->शेष_ant.rx_chain_num;

	अगर (tx_chains >= 2)
		spec->ht.cap |= IEEE80211_HT_CAP_TX_STBC;

	spec->ht.cap |= rx_chains << IEEE80211_HT_CAP_RX_STBC_SHIFT;

	spec->ht.ampdu_factor = (rx_chains > 1) ? 3 : 2;
	spec->ht.ampdu_density = 4;
	spec->ht.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	अगर (tx_chains != rx_chains) अणु
		spec->ht.mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		spec->ht.mcs.tx_params |=
		    (tx_chains - 1) << IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
	पूर्ण

	चयन (rx_chains) अणु
	हाल 3:
		spec->ht.mcs.rx_mask[2] = 0xff;
		fallthrough;
	हाल 2:
		spec->ht.mcs.rx_mask[1] = 0xff;
		fallthrough;
	हाल 1:
		spec->ht.mcs.rx_mask[0] = 0xff;
		spec->ht.mcs.rx_mask[4] = 0x1; /* MCS32 */
		अवरोध;
	पूर्ण

	/*
	 * Create channel inक्रमmation and survey arrays
	 */
	info = kसुस्मृति(spec->num_channels, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	rt2x00dev->chan_survey =
		kसुस्मृति(spec->num_channels, माप(काष्ठा rt2x00_chan_survey),
			GFP_KERNEL);
	अगर (!rt2x00dev->chan_survey) अणु
		kमुक्त(info);
		वापस -ENOMEM;
	पूर्ण

	spec->channels_info = info;

	शेष_घातer1 = rt2800_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG1);
	शेष_घातer2 = rt2800_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_BG2);

	अगर (rt2x00dev->शेष_ant.tx_chain_num > 2)
		शेष_घातer3 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_EXT_TXPOWER_BG3);
	अन्यथा
		शेष_घातer3 = शून्य;

	क्रम (i = 0; i < 14; i++) अणु
		info[i].शेष_घातer1 = शेष_घातer1[i];
		info[i].शेष_घातer2 = शेष_घातer2[i];
		अगर (शेष_घातer3)
			info[i].शेष_घातer3 = शेष_घातer3[i];
	पूर्ण

	अगर (spec->num_channels > 14) अणु
		शेष_घातer1 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_TXPOWER_A1);
		शेष_घातer2 = rt2800_eeprom_addr(rt2x00dev,
						    EEPROM_TXPOWER_A2);

		अगर (rt2x00dev->शेष_ant.tx_chain_num > 2)
			शेष_घातer3 =
				rt2800_eeprom_addr(rt2x00dev,
						   EEPROM_EXT_TXPOWER_A3);
		अन्यथा
			शेष_घातer3 = शून्य;

		क्रम (i = 14; i < spec->num_channels; i++) अणु
			info[i].शेष_घातer1 = शेष_घातer1[i - 14];
			info[i].शेष_घातer2 = शेष_घातer2[i - 14];
			अगर (शेष_घातer3)
				info[i].शेष_घातer3 = शेष_घातer3[i - 14];
		पूर्ण
	पूर्ण

	चयन (rt2x00dev->chip.rf) अणु
	हाल RF2020:
	हाल RF3020:
	हाल RF3021:
	हाल RF3022:
	हाल RF3320:
	हाल RF3052:
	हाल RF3053:
	हाल RF3070:
	हाल RF3290:
	हाल RF3853:
	हाल RF5350:
	हाल RF5360:
	हाल RF5362:
	हाल RF5370:
	हाल RF5372:
	हाल RF5390:
	हाल RF5392:
	हाल RF5592:
	हाल RF7620:
		__set_bit(CAPABILITY_VCO_RECALIBRATION, &rt2x00dev->cap_flags);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2800_probe_rt(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	u32 rt;
	u32 rev;

	अगर (rt2x00_rt(rt2x00dev, RT3290))
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0_3290);
	अन्यथा
		reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);

	rt = rt2x00_get_field32(reg, MAC_CSR0_CHIPSET);
	rev = rt2x00_get_field32(reg, MAC_CSR0_REVISION);

	चयन (rt) अणु
	हाल RT2860:
	हाल RT2872:
	हाल RT2883:
	हाल RT3070:
	हाल RT3071:
	हाल RT3090:
	हाल RT3290:
	हाल RT3352:
	हाल RT3390:
	हाल RT3572:
	हाल RT3593:
	हाल RT3883:
	हाल RT5350:
	हाल RT5390:
	हाल RT5392:
	हाल RT5592:
		अवरोध;
	शेष:
		rt2x00_err(rt2x00dev, "Invalid RT chipset 0x%04x, rev %04x detected\n",
			   rt, rev);
		वापस -ENODEV;
	पूर्ण

	अगर (rt == RT5390 && rt2x00_is_soc(rt2x00dev))
		rt = RT6352;

	rt2x00_set_rt(rt2x00dev, rt, rev);

	वापस 0;
पूर्ण

पूर्णांक rt2800_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;
	u32 reg;

	retval = rt2800_probe_rt(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2800_validate_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	retval = rt2800_init_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Enable rfसमाप्त polling by setting GPIO direction of the
	 * rfसमाप्त चयन GPIO pin correctly.
	 */
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GPIO_CTRL);
	rt2x00_set_field32(&reg, GPIO_CTRL_सूची2, 1);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GPIO_CTRL, reg);

	/*
	 * Initialize hw specअगरications.
	 */
	retval = rt2800_probe_hw_mode(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Set device capabilities.
	 */
	__set_bit(CAPABILITY_CONTROL_FILTERS, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_CONTROL_FILTER_PSPOLL, &rt2x00dev->cap_flags);
	अगर (!rt2x00_is_usb(rt2x00dev))
		__set_bit(CAPABILITY_PRE_TBTT_INTERRUPT, &rt2x00dev->cap_flags);

	/*
	 * Set device requirements.
	 */
	अगर (!rt2x00_is_soc(rt2x00dev))
		__set_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_L2PAD, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_TXSTATUS_FIFO, &rt2x00dev->cap_flags);
	अगर (!rt2800_hwcrypt_disabled(rt2x00dev))
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_HT_TX_DESC, &rt2x00dev->cap_flags);
	अगर (rt2x00_is_usb(rt2x00dev))
		__set_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags);
	अन्यथा अणु
		__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
		__set_bit(REQUIRE_TASKLET_CONTEXT, &rt2x00dev->cap_flags);
	पूर्ण

	अगर (modparam_watchकरोg) अणु
		__set_bit(CAPABILITY_RESTART_HW, &rt2x00dev->cap_flags);
		rt2x00dev->link.watchकरोg_पूर्णांकerval = msecs_to_jअगरfies(100);
	पूर्ण अन्यथा अणु
		rt2x00dev->link.watchकरोg_disabled = true;
	पूर्ण

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_probe_hw);

/*
 * IEEE80211 stack callback functions.
 */
व्योम rt2800_get_key_seq(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_key_conf *key,
			काष्ठा ieee80211_key_seq *seq)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा mac_iveiv_entry iveiv_entry;
	u32 offset;

	अगर (key->cipher != WLAN_CIPHER_SUITE_TKIP)
		वापस;

	offset = MAC_IVEIV_ENTRY(key->hw_key_idx);
	rt2800_रेजिस्टर_multiपढ़ो(rt2x00dev, offset,
				      &iveiv_entry, माप(iveiv_entry));

	स_नकल(&seq->tkip.iv16, &iveiv_entry.iv[0], 2);
	स_नकल(&seq->tkip.iv32, &iveiv_entry.iv[4], 4);
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_get_key_seq);

पूर्णांक rt2800_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u32 reg;
	bool enabled = (value < IEEE80211_MAX_RTS_THRESHOLD);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TX_RTS_CFG);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_THRES, value);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RTS_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, CCK_PROT_CFG);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, CCK_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, OFDM_PROT_CFG);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, OFDM_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, GF40_PROT_CFG, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_set_rts_threshold);

पूर्णांक rt2800_conf_tx(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_vअगर *vअगर, u16 queue_idx,
		   स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा data_queue *queue;
	काष्ठा rt2x00_field32 field;
	पूर्णांक retval;
	u32 reg;
	u32 offset;

	/*
	 * First pass the configuration through rt2x00lib, that will
	 * update the queue settings and validate the input. After that
	 * we are मुक्त to update the रेजिस्टरs based on the value
	 * in the queue parameter.
	 */
	retval = rt2x00mac_conf_tx(hw, vअगर, queue_idx, params);
	अगर (retval)
		वापस retval;

	/*
	 * We only need to perक्रमm additional रेजिस्टर initialization
	 * क्रम WMM queues/
	 */
	अगर (queue_idx >= 4)
		वापस 0;

	queue = rt2x00queue_get_tx_queue(rt2x00dev, queue_idx);

	/* Update WMM TXOP रेजिस्टर */
	offset = WMM_TXOP0_CFG + (माप(u32) * (!!(queue_idx & 2)));
	field.bit_offset = (queue_idx & 1) * 16;
	field.bit_mask = 0xffff << field.bit_offset;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, field, queue->txop);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

	/* Update WMM रेजिस्टरs */
	field.bit_offset = queue_idx * 4;
	field.bit_mask = 0xf << field.bit_offset;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WMM_AIFSN_CFG);
	rt2x00_set_field32(&reg, field, queue->aअगरs);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WMM_AIFSN_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WMM_CWMIN_CFG);
	rt2x00_set_field32(&reg, field, queue->cw_min);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WMM_CWMIN_CFG, reg);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, WMM_CWMAX_CFG);
	rt2x00_set_field32(&reg, field, queue->cw_max);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, WMM_CWMAX_CFG, reg);

	/* Update EDCA रेजिस्टरs */
	offset = EDCA_AC0_CFG + (माप(u32) * queue_idx);

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, EDCA_AC0_CFG_TX_OP, queue->txop);
	rt2x00_set_field32(&reg, EDCA_AC0_CFG_AIFSN, queue->aअगरs);
	rt2x00_set_field32(&reg, EDCA_AC0_CFG_CWMIN, queue->cw_min);
	rt2x00_set_field32(&reg, EDCA_AC0_CFG_CWMAX, queue->cw_max);
	rt2800_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_conf_tx);

u64 rt2800_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u64 tsf;
	u32 reg;

	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TSF_TIMER_DW1);
	tsf = (u64) rt2x00_get_field32(reg, TSF_TIMER_DW1_HIGH_WORD) << 32;
	reg = rt2800_रेजिस्टर_पढ़ो(rt2x00dev, TSF_TIMER_DW0);
	tsf |= rt2x00_get_field32(reg, TSF_TIMER_DW0_LOW_WORD);

	वापस tsf;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_get_tsf);

पूर्णांक rt2800_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	काष्ठा rt2x00_sta *sta_priv = (काष्ठा rt2x00_sta *)sta->drv_priv;
	पूर्णांक ret = 0;

	/*
	 * Don't allow aggregation for stations the hardware isn't aware
	 * of because tx status reports क्रम frames to an unknown station
	 * always contain wcid=WCID_END+1 and thus we can't distinguish
	 * between multiple stations which leads to unwanted situations
	 * when the hw reorders frames due to aggregation.
	 */
	अगर (sta_priv->wcid > WCID_END)
		वापस -ENOSPC;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		/*
		 * The hw itself takes care of setting up BlockAck mechanisms.
		 * So, we only have to allow mac80211 to nagotiate a BlockAck
		 * agreement. Once that is करोne, the hw will BlockAck incoming
		 * AMPDUs without further setup.
		 */
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		अवरोध;
	शेष:
		rt2x00_warn((काष्ठा rt2x00_dev *)hw->priv,
			    "Unknown AMPDU action\n");
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rt2800_ampdu_action);

पूर्णांक rt2800_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
		      काष्ठा survey_info *survey)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	काष्ठा rt2x00_chan_survey *chan_survey =
		   &rt2x00dev->chan_survey[idx];
	क्रमागत nl80211_band band = NL80211_BAND_2GHZ;

	अगर (idx >= rt2x00dev->bands[band].n_channels) अणु
		idx -= rt2x00dev->bands[band].n_channels;
		band = NL80211_BAND_5GHZ;
	पूर्ण

	अगर (idx >= rt2x00dev->bands[band].n_channels)
		वापस -ENOENT;

	अगर (idx == 0)
		rt2800_update_survey(rt2x00dev);

	survey->channel = &rt2x00dev->bands[band].channels[idx];

	survey->filled = SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_BUSY |
			 SURVEY_INFO_TIME_EXT_BUSY;

	survey->समय = भाग_u64(chan_survey->समय_idle + chan_survey->समय_busy, 1000);
	survey->समय_busy = भाग_u64(chan_survey->समय_busy, 1000);
	survey->समय_ext_busy = भाग_u64(chan_survey->समय_ext_busy, 1000);

	अगर (!(hw->conf.flags & IEEE80211_CONF_OFFCHANNEL))
		survey->filled |= SURVEY_INFO_IN_USE;

	वापस 0;

पूर्ण
EXPORT_SYMBOL_GPL(rt2800_get_survey);

MODULE_AUTHOR(DRV_PROJECT ", Bartlomiej Zolnierkiewicz");
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2800 library");
MODULE_LICENSE("GPL");

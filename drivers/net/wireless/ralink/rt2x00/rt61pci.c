<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt61pci
	Abstract: rt61pci device specअगरic routines.
	Supported chipsets: RT2561, RT2561s, RT2661.
 */

#समावेश <linux/crc-itu-t.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/eeprom_93cx6.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"
#समावेश "rt2x00pci.h"
#समावेश "rt61pci.h"

/*
 * Allow hardware encryption to be disabled.
 */
अटल bool modparam_nohwcrypt = false;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

/*
 * Register access.
 * BBP and RF रेजिस्टर require indirect रेजिस्टर access,
 * and use the CSR रेजिस्टरs PHY_CSR3 and PHY_CSR4 to achieve this.
 * These indirect रेजिस्टरs work with busy bits,
 * and we will try maximal REGISTER_BUSY_COUNT बार to access
 * the रेजिस्टर जबतक taking a REGISTER_BUSY_DELAY us delay
 * between each attempt. When the busy bit is still set at that समय,
 * the access attempt is considered to have failed,
 * and we will prपूर्णांक an error.
 */
#घोषणा WAIT_FOR_BBP(__dev, __reg) \
	rt2x00mmio_regbusy_पढ़ो((__dev), PHY_CSR3, PHY_CSR3_BUSY, (__reg))
#घोषणा WAIT_FOR_RF(__dev, __reg) \
	rt2x00mmio_regbusy_पढ़ो((__dev), PHY_CSR4, PHY_CSR4_BUSY, (__reg))
#घोषणा WAIT_FOR_MCU(__dev, __reg) \
	rt2x00mmio_regbusy_पढ़ो((__dev), H2M_MAILBOX_CSR, \
				H2M_MAILBOX_CSR_OWNER, (__reg))

अटल व्योम rt61pci_bbp_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt2x00_set_field32(&reg, PHY_CSR3_VALUE, value);
		rt2x00_set_field32(&reg, PHY_CSR3_REGNUM, word);
		rt2x00_set_field32(&reg, PHY_CSR3_BUSY, 1);
		rt2x00_set_field32(&reg, PHY_CSR3_READ_CONTROL, 0);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR3, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल u8 rt61pci_bbp_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			   स्थिर अचिन्हित पूर्णांक word)
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
		rt2x00_set_field32(&reg, PHY_CSR3_REGNUM, word);
		rt2x00_set_field32(&reg, PHY_CSR3_BUSY, 1);
		rt2x00_set_field32(&reg, PHY_CSR3_READ_CONTROL, 1);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR3, reg);

		WAIT_FOR_BBP(rt2x00dev, &reg);
	पूर्ण

	value = rt2x00_get_field32(reg, PHY_CSR3_VALUE);

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल व्योम rt61pci_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt2x00_set_field32(&reg, PHY_CSR4_VALUE, value);
		rt2x00_set_field32(&reg, PHY_CSR4_NUMBER_OF_BITS, 21);
		rt2x00_set_field32(&reg, PHY_CSR4_IF_SELECT, 0);
		rt2x00_set_field32(&reg, PHY_CSR4_BUSY, 1);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR4, reg);
		rt2x00_rf_ग_लिखो(rt2x00dev, word, value);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल व्योम rt61pci_mcu_request(काष्ठा rt2x00_dev *rt2x00dev,
				स्थिर u8 command, स्थिर u8 token,
				स्थिर u8 arg0, स्थिर u8 arg1)
अणु
	u32 reg;

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
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, HOST_CMD_CSR);
		rt2x00_set_field32(&reg, HOST_CMD_CSR_HOST_COMMAND, command);
		rt2x00_set_field32(&reg, HOST_CMD_CSR_INTERRUPT_MCU, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HOST_CMD_CSR, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);

पूर्ण

अटल व्योम rt61pci_eepromरेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, E2PROM_CSR);

	eeprom->reg_data_in = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_IN);
	eeprom->reg_data_out = !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_OUT);
	eeprom->reg_data_घड़ी =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_DATA_CLOCK);
	eeprom->reg_chip_select =
	    !!rt2x00_get_field32(reg, E2PROM_CSR_CHIP_SELECT);
पूर्ण

अटल व्योम rt61pci_eepromरेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg = 0;

	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_IN, !!eeprom->reg_data_in);
	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_OUT, !!eeprom->reg_data_out);
	rt2x00_set_field32(&reg, E2PROM_CSR_DATA_CLOCK,
			   !!eeprom->reg_data_घड़ी);
	rt2x00_set_field32(&reg, E2PROM_CSR_CHIP_SELECT,
			   !!eeprom->reg_chip_select);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, E2PROM_CSR, reg);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
अटल स्थिर काष्ठा rt2x00debug rt61pci_rt2x00debug = अणु
	.owner	= THIS_MODULE,
	.csr	= अणु
		.पढ़ो		= rt2x00mmio_रेजिस्टर_पढ़ो,
		.ग_लिखो		= rt2x00mmio_रेजिस्टर_ग_लिखो,
		.flags		= RT2X00DEBUGFS_OFFSET,
		.word_base	= CSR_REG_BASE,
		.word_size	= माप(u32),
		.word_count	= CSR_REG_SIZE / माप(u32),
	पूर्ण,
	.eeprom	= अणु
		.पढ़ो		= rt2x00_eeprom_पढ़ो,
		.ग_लिखो		= rt2x00_eeprom_ग_लिखो,
		.word_base	= EEPROM_BASE,
		.word_size	= माप(u16),
		.word_count	= EEPROM_SIZE / माप(u16),
	पूर्ण,
	.bbp	= अणु
		.पढ़ो		= rt61pci_bbp_पढ़ो,
		.ग_लिखो		= rt61pci_bbp_ग_लिखो,
		.word_base	= BBP_BASE,
		.word_size	= माप(u8),
		.word_count	= BBP_SIZE / माप(u8),
	पूर्ण,
	.rf	= अणु
		.पढ़ो		= rt2x00_rf_पढ़ो,
		.ग_लिखो		= rt61pci_rf_ग_लिखो,
		.word_base	= RF_BASE,
		.word_size	= माप(u32),
		.word_count	= RF_SIZE / माप(u32),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

अटल पूर्णांक rt61pci_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR13);
	वापस rt2x00_get_field32(reg, MAC_CSR13_VAL5);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
अटल व्योम rt61pci_brightness_set(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	अचिन्हित पूर्णांक enabled = brightness != LED_OFF;
	अचिन्हित पूर्णांक a_mode =
	    (enabled && led->rt2x00dev->curr_band == NL80211_BAND_5GHZ);
	अचिन्हित पूर्णांक bg_mode =
	    (enabled && led->rt2x00dev->curr_band == NL80211_BAND_2GHZ);

	अगर (led->type == LED_TYPE_RADIO) अणु
		rt2x00_set_field16(&led->rt2x00dev->led_mcu_reg,
				   MCU_LEDCS_RADIO_STATUS, enabled);

		rt61pci_mcu_request(led->rt2x00dev, MCU_LED, 0xff,
				    (led->rt2x00dev->led_mcu_reg & 0xff),
				    ((led->rt2x00dev->led_mcu_reg >> 8)));
	पूर्ण अन्यथा अगर (led->type == LED_TYPE_ASSOC) अणु
		rt2x00_set_field16(&led->rt2x00dev->led_mcu_reg,
				   MCU_LEDCS_LINK_BG_STATUS, bg_mode);
		rt2x00_set_field16(&led->rt2x00dev->led_mcu_reg,
				   MCU_LEDCS_LINK_A_STATUS, a_mode);

		rt61pci_mcu_request(led->rt2x00dev, MCU_LED, 0xff,
				    (led->rt2x00dev->led_mcu_reg & 0xff),
				    ((led->rt2x00dev->led_mcu_reg >> 8)));
	पूर्ण अन्यथा अगर (led->type == LED_TYPE_QUALITY) अणु
		/*
		 * The brightness is भागided पूर्णांकo 6 levels (0 - 5),
		 * this means we need to convert the brightness
		 * argument पूर्णांकo the matching level within that range.
		 */
		rt61pci_mcu_request(led->rt2x00dev, MCU_LED_STRENGTH, 0xff,
				    brightness / (LED_FULL / 6), 0);
	पूर्ण
पूर्ण

अटल पूर्णांक rt61pci_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on,
			     अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(led->rt2x00dev, MAC_CSR14);
	rt2x00_set_field32(&reg, MAC_CSR14_ON_PERIOD, *delay_on);
	rt2x00_set_field32(&reg, MAC_CSR14_OFF_PERIOD, *delay_off);
	rt2x00mmio_रेजिस्टर_ग_लिखो(led->rt2x00dev, MAC_CSR14, reg);

	वापस 0;
पूर्ण

अटल व्योम rt61pci_init_led(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00_led *led,
			     क्रमागत led_type type)
अणु
	led->rt2x00dev = rt2x00dev;
	led->type = type;
	led->led_dev.brightness_set = rt61pci_brightness_set;
	led->led_dev.blink_set = rt61pci_blink_set;
	led->flags = LED_INITIALIZED;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

/*
 * Configuration handlers.
 */
अटल पूर्णांक rt61pci_config_shared_key(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा rt2x00lib_crypto *crypto,
				     काष्ठा ieee80211_key_conf *key)
अणु
	/*
	 * Let the software handle the shared keys,
	 * since the hardware decryption करोes not work reliably,
	 * because the firmware करोes not know the key's keyidx.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक rt61pci_config_pairwise_key(काष्ठा rt2x00_dev *rt2x00dev,
				       काष्ठा rt2x00lib_crypto *crypto,
				       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा hw_pairwise_ta_entry addr_entry;
	काष्ठा hw_key_entry key_entry;
	u32 mask;
	u32 reg;

	अगर (crypto->cmd == SET_KEY) अणु
		/*
		 * rt2x00lib can't determine the correct मुक्त
		 * key_idx क्रम pairwise keys. We have 2 रेजिस्टरs
		 * with key valid bits. The goal is simple: पढ़ो
		 * the first रेजिस्टर. If that is full, move to
		 * the next रेजिस्टर.
		 * When both रेजिस्टरs are full, we drop the key.
		 * Otherwise, we use the first invalid entry.
		 */
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR2);
		अगर (reg && reg == ~0) अणु
			key->hw_key_idx = 32;
			reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR3);
			अगर (reg && reg == ~0)
				वापस -ENOSPC;
		पूर्ण

		key->hw_key_idx += reg ? ffz(reg) : 0;

		/*
		 * Upload key to hardware
		 */
		स_नकल(key_entry.key, crypto->key,
		       माप(key_entry.key));
		स_नकल(key_entry.tx_mic, crypto->tx_mic,
		       माप(key_entry.tx_mic));
		स_नकल(key_entry.rx_mic, crypto->rx_mic,
		       माप(key_entry.rx_mic));

		स_रखो(&addr_entry, 0, माप(addr_entry));
		स_नकल(&addr_entry, crypto->address, ETH_ALEN);
		addr_entry.cipher = crypto->cipher;

		reg = PAIRWISE_KEY_ENTRY(key->hw_key_idx);
		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, reg,
					       &key_entry, माप(key_entry));

		reg = PAIRWISE_TA_ENTRY(key->hw_key_idx);
		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, reg,
					       &addr_entry, माप(addr_entry));

		/*
		 * Enable pairwise lookup table क्रम given BSS idx.
		 * Without this, received frames will not be decrypted
		 * by the hardware.
		 */
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR4);
		reg |= (1 << crypto->bssidx);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR4, reg);

		/*
		 * The driver करोes not support the IV/EIV generation
		 * in hardware. However it करोesn't support the IV/EIV
		 * inside the ieee80211 frame either, but requires it
		 * to be provided separately क्रम the descriptor.
		 * rt2x00lib will cut the IV/EIV data out of all frames
		 * given to us by mac80211, but we must tell mac80211
		 * to generate the IV/EIV data.
		 */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	पूर्ण

	/*
	 * SEC_CSR2 and SEC_CSR3 contain only single-bit fields to indicate
	 * a particular key is valid. Because using the FIELD32()
	 * defines directly will cause a lot of overhead, we use
	 * a calculation to determine the correct bit directly.
	 */
	अगर (key->hw_key_idx < 32) अणु
		mask = 1 << key->hw_key_idx;

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR2);
		अगर (crypto->cmd == SET_KEY)
			reg |= mask;
		अन्यथा अगर (crypto->cmd == DISABLE_KEY)
			reg &= ~mask;
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR2, reg);
	पूर्ण अन्यथा अणु
		mask = 1 << (key->hw_key_idx - 32);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR3);
		अगर (crypto->cmd == SET_KEY)
			reg |= mask;
		अन्यथा अगर (crypto->cmd == DISABLE_KEY)
			reg &= ~mask;
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR3, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt61pci_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर अचिन्हित पूर्णांक filter_flags)
अणु
	u32 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * and broadcast frames will always be accepted since
	 * there is no filter क्रम it at this समय.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_CRC,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_PHYSICAL,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_CONTROL,
			   !(filter_flags & (FIF_CONTROL | FIF_PSPOLL)));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_TO_DS,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags) &&
			   !rt2x00dev->पूर्णांकf_ap_count);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_VERSION_ERROR, 1);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_MULTICAST,
			   !(filter_flags & FIF_ALLMULTI));
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_BROADCAST, 0);
	rt2x00_set_field32(&reg, TXRX_CSR0_DROP_ACK_CTS,
			   !(filter_flags & FIF_CONTROL));
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
पूर्ण

अटल व्योम rt61pci_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
				काष्ठा rt2x00पूर्णांकf_conf *conf,
				स्थिर अचिन्हित पूर्णांक flags)
अणु
	u32 reg;

	अगर (flags & CONFIG_UPDATE_TYPE) अणु
		/*
		 * Enable synchronisation.
		 */
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_SYNC, conf->sync);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
	पूर्ण

	अगर (flags & CONFIG_UPDATE_MAC) अणु
		reg = le32_to_cpu(conf->mac[1]);
		rt2x00_set_field32(&reg, MAC_CSR3_UNICAST_TO_ME_MASK, 0xff);
		conf->mac[1] = cpu_to_le32(reg);

		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR2,
					       conf->mac, माप(conf->mac));
	पूर्ण

	अगर (flags & CONFIG_UPDATE_BSSID) अणु
		reg = le32_to_cpu(conf->bssid[1]);
		rt2x00_set_field32(&reg, MAC_CSR5_BSS_ID_MASK, 3);
		conf->bssid[1] = cpu_to_le32(reg);

		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR4,
					       conf->bssid,
					       माप(conf->bssid));
	पूर्ण
पूर्ण

अटल व्योम rt61pci_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00lib_erp *erp,
			       u32 changed)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field32(&reg, TXRX_CSR0_RX_ACK_TIMEOUT, 0x32);
	rt2x00_set_field32(&reg, TXRX_CSR0_TSF_OFFSET, IEEE80211_HEADER);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR4);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_PREAMBLE,
				   !!erp->लघु_preamble);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR4, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR5,
					  erp->basic_rates);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_INTERVAL,
				   erp->beacon_पूर्णांक * 16);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR9);
		rt2x00_set_field32(&reg, MAC_CSR9_SLOT_TIME, erp->slot_समय);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR9, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR8);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS, erp->sअगरs);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS_AFTER_RX_OFDM, 3);
		rt2x00_set_field32(&reg, MAC_CSR8_EIFS, erp->eअगरs);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR8, reg);
	पूर्ण
पूर्ण

अटल व्योम rt61pci_config_antenna_5x(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा antenna_setup *ant)
अणु
	u8 r3;
	u8 r4;
	u8 r77;

	r3 = rt61pci_bbp_पढ़ो(rt2x00dev, 3);
	r4 = rt61pci_bbp_पढ़ो(rt2x00dev, 4);
	r77 = rt61pci_bbp_पढ़ो(rt2x00dev, 77);

	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, rt2x00_rf(rt2x00dev, RF5325));

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 2);
		rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END,
				  (rt2x00dev->curr_band != NL80211_BAND_5GHZ));
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END, 0);
		अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ)
			rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		अन्यथा
			rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END, 0);
		अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ)
			rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		अन्यथा
			rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		अवरोध;
	पूर्ण

	rt61pci_bbp_ग_लिखो(rt2x00dev, 77, r77);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 4, r4);
पूर्ण

अटल व्योम rt61pci_config_antenna_2x(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा antenna_setup *ant)
अणु
	u8 r3;
	u8 r4;
	u8 r77;

	r3 = rt61pci_bbp_पढ़ो(rt2x00dev, 3);
	r4 = rt61pci_bbp_पढ़ो(rt2x00dev, 4);
	r77 = rt61pci_bbp_पढ़ो(rt2x00dev, 77);

	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, rt2x00_rf(rt2x00dev, RF2529));
	rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END,
			  !rt2x00_has_cap_frame_type(rt2x00dev));

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 2);
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		अवरोध;
	पूर्ण

	rt61pci_bbp_ग_लिखो(rt2x00dev, 77, r77);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 4, r4);
पूर्ण

अटल व्योम rt61pci_config_antenna_2529_rx(काष्ठा rt2x00_dev *rt2x00dev,
					   स्थिर पूर्णांक p1, स्थिर पूर्णांक p2)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR13);

	rt2x00_set_field32(&reg, MAC_CSR13_सूची4, 0);
	rt2x00_set_field32(&reg, MAC_CSR13_VAL4, p1);

	rt2x00_set_field32(&reg, MAC_CSR13_सूची3, 0);
	rt2x00_set_field32(&reg, MAC_CSR13_VAL3, !p2);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, reg);
पूर्ण

अटल व्योम rt61pci_config_antenna_2529(काष्ठा rt2x00_dev *rt2x00dev,
					काष्ठा antenna_setup *ant)
अणु
	u8 r3;
	u8 r4;
	u8 r77;

	r3 = rt61pci_bbp_पढ़ो(rt2x00dev, 3);
	r4 = rt61pci_bbp_पढ़ो(rt2x00dev, 4);
	r77 = rt61pci_bbp_पढ़ो(rt2x00dev, 77);

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_A:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		rt61pci_config_antenna_2529_rx(rt2x00dev, 0, 0);
		अवरोध;
	हाल ANTENNA_HW_DIVERSITY:
		/*
		 * FIXME: Antenna selection क्रम the rf 2529 is very confusing
		 * in the legacy driver. Just शेष to antenna B until the
		 * legacy code can be properly translated पूर्णांकo rt2x00 code.
		 */
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		rt61pci_config_antenna_2529_rx(rt2x00dev, 1, 1);
		अवरोध;
	पूर्ण

	rt61pci_bbp_ग_लिखो(rt2x00dev, 77, r77);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 4, r4);
पूर्ण

काष्ठा antenna_sel अणु
	u8 word;
	/*
	 * value[0] -> non-LNA
	 * value[1] -> LNA
	 */
	u8 value[2];
पूर्ण;

अटल स्थिर काष्ठा antenna_sel antenna_sel_a[] = अणु
	अणु 96,  अणु 0x58, 0x78 पूर्ण पूर्ण,
	अणु 104, अणु 0x38, 0x48 पूर्ण पूर्ण,
	अणु 75,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 86,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 88,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 35,  अणु 0x60, 0x60 पूर्ण पूर्ण,
	अणु 97,  अणु 0x58, 0x58 पूर्ण पूर्ण,
	अणु 98,  अणु 0x58, 0x58 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा antenna_sel antenna_sel_bg[] = अणु
	अणु 96,  अणु 0x48, 0x68 पूर्ण पूर्ण,
	अणु 104, अणु 0x2c, 0x3c पूर्ण पूर्ण,
	अणु 75,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 86,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 88,  अणु 0xfe, 0x80 पूर्ण पूर्ण,
	अणु 35,  अणु 0x50, 0x50 पूर्ण पूर्ण,
	अणु 97,  अणु 0x48, 0x48 पूर्ण पूर्ण,
	अणु 98,  अणु 0x48, 0x48 पूर्ण पूर्ण,
पूर्ण;

अटल व्योम rt61pci_config_ant(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा antenna_setup *ant)
अणु
	स्थिर काष्ठा antenna_sel *sel;
	अचिन्हित पूर्णांक lna;
	अचिन्हित पूर्णांक i;
	u32 reg;

	/*
	 * We should never come here because rt2x00lib is supposed
	 * to catch this and send us the correct antenna explicitely.
	 */
	BUG_ON(ant->rx == ANTENNA_SW_DIVERSITY ||
	       ant->tx == ANTENNA_SW_DIVERSITY);

	अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ) अणु
		sel = antenna_sel_a;
		lna = rt2x00_has_cap_बाह्यal_lna_a(rt2x00dev);
	पूर्ण अन्यथा अणु
		sel = antenna_sel_bg;
		lna = rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(antenna_sel_a); i++)
		rt61pci_bbp_ग_लिखो(rt2x00dev, sel[i].word, sel[i].value[lna]);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR0);

	rt2x00_set_field32(&reg, PHY_CSR0_PA_PE_BG,
			   rt2x00dev->curr_band == NL80211_BAND_2GHZ);
	rt2x00_set_field32(&reg, PHY_CSR0_PA_PE_A,
			   rt2x00dev->curr_band == NL80211_BAND_5GHZ);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR0, reg);

	अगर (rt2x00_rf(rt2x00dev, RF5225) || rt2x00_rf(rt2x00dev, RF5325))
		rt61pci_config_antenna_5x(rt2x00dev, ant);
	अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2527))
		rt61pci_config_antenna_2x(rt2x00dev, ant);
	अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2529)) अणु
		अगर (rt2x00_has_cap_द्विगुन_antenna(rt2x00dev))
			rt61pci_config_antenna_2x(rt2x00dev, ant);
		अन्यथा
			rt61pci_config_antenna_2529(rt2x00dev, ant);
	पूर्ण
पूर्ण

अटल व्योम rt61pci_config_lna_gain(काष्ठा rt2x00_dev *rt2x00dev,
				    काष्ठा rt2x00lib_conf *libconf)
अणु
	u16 eeprom;
	लघु lna_gain = 0;

	अगर (libconf->conf->chandef.chan->band == NL80211_BAND_2GHZ) अणु
		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev))
			lna_gain += 14;

		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_OFFSET_BG);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_BG_1);
	पूर्ण अन्यथा अणु
		अगर (rt2x00_has_cap_बाह्यal_lna_a(rt2x00dev))
			lna_gain += 14;

		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_OFFSET_A);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_A_1);
	पूर्ण

	rt2x00dev->lna_gain = lna_gain;
पूर्ण

अटल व्योम rt61pci_config_channel(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा rf_channel *rf, स्थिर पूर्णांक txघातer)
अणु
	u8 r3;
	u8 r94;
	u8 smart;

	rt2x00_set_field32(&rf->rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txघातer));
	rt2x00_set_field32(&rf->rf4, RF4_FREQ_OFFSET, rt2x00dev->freq_offset);

	smart = !(rt2x00_rf(rt2x00dev, RF5225) || rt2x00_rf(rt2x00dev, RF2527));

	r3 = rt61pci_bbp_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, smart);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 3, r3);

	r94 = 6;
	अगर (txघातer > MAX_TXPOWER && txघातer <= (MAX_TXPOWER + r94))
		r94 += txघातer - MAX_TXPOWER;
	अन्यथा अगर (txघातer < MIN_TXPOWER && txघातer >= (MIN_TXPOWER - r94))
		r94 += txघातer;
	rt61pci_bbp_ग_लिखो(rt2x00dev, 94, r94);

	rt61pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt61pci_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt61pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt61pci_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	udelay(200);

	rt61pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt61pci_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt61pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 | 0x00000004);
	rt61pci_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	udelay(200);

	rt61pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt61pci_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt61pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt61pci_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	msleep(1);
पूर्ण

अटल व्योम rt61pci_config_txघातer(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर पूर्णांक txघातer)
अणु
	काष्ठा rf_channel rf;

	rf.rf1 = rt2x00_rf_पढ़ो(rt2x00dev, 1);
	rf.rf2 = rt2x00_rf_पढ़ो(rt2x00dev, 2);
	rf.rf3 = rt2x00_rf_पढ़ो(rt2x00dev, 3);
	rf.rf4 = rt2x00_rf_पढ़ो(rt2x00dev, 4);

	rt61pci_config_channel(rt2x00dev, &rf, txघातer);
पूर्ण

अटल व्योम rt61pci_config_retry_limit(काष्ठा rt2x00_dev *rt2x00dev,
				    काष्ठा rt2x00lib_conf *libconf)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR4);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_RATE_DOWN, 1);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_RATE_STEP, 0);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_FALLBACK_CCK, 0);
	rt2x00_set_field32(&reg, TXRX_CSR4_LONG_RETRY_LIMIT,
			   libconf->conf->दीर्घ_frame_max_tx_count);
	rt2x00_set_field32(&reg, TXRX_CSR4_SHORT_RETRY_LIMIT,
			   libconf->conf->लघु_frame_max_tx_count);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR4, reg);
पूर्ण

अटल व्योम rt61pci_config_ps(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00lib_conf *libconf)
अणु
	क्रमागत dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	अगर (state == STATE_SLEEP) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR11);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN,
				   rt2x00dev->beacon_पूर्णांक - 10);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_पूर्णांकerval - 1);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 5);

		/* We must first disable स्वतःwake beक्रमe it can be enabled */
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SOFT_RESET_CSR,
					  0x00000005);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, IO_CNTL_CSR, 0x0000001c);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PCI_USEC_CSR, 0x00000060);

		rt61pci_mcu_request(rt2x00dev, MCU_SLEEP, 0xff, 0, 0);
	पूर्ण अन्यथा अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR11);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SOFT_RESET_CSR,
					  0x00000007);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, IO_CNTL_CSR, 0x00000018);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PCI_USEC_CSR, 0x00000020);

		rt61pci_mcu_request(rt2x00dev, MCU_WAKEUP, 0xff, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम rt61pci_config(काष्ठा rt2x00_dev *rt2x00dev,
			   काष्ठा rt2x00lib_conf *libconf,
			   स्थिर अचिन्हित पूर्णांक flags)
अणु
	/* Always recalculate LNA gain beक्रमe changing configuration */
	rt61pci_config_lna_gain(rt2x00dev, libconf);

	अगर (flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt61pci_config_channel(rt2x00dev, &libconf->rf,
				       libconf->conf->घातer_level);
	अगर ((flags & IEEE80211_CONF_CHANGE_POWER) &&
	    !(flags & IEEE80211_CONF_CHANGE_CHANNEL))
		rt61pci_config_txघातer(rt2x00dev, libconf->conf->घातer_level);
	अगर (flags & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		rt61pci_config_retry_limit(rt2x00dev, libconf);
	अगर (flags & IEEE80211_CONF_CHANGE_PS)
		rt61pci_config_ps(rt2x00dev, libconf);
पूर्ण

/*
 * Link tuning
 */
अटल व्योम rt61pci_link_stats(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा link_qual *qual)
अणु
	u32 reg;

	/*
	 * Update FCS error count from रेजिस्टर.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR0);
	qual->rx_failed = rt2x00_get_field32(reg, STA_CSR0_FCS_ERROR);

	/*
	 * Update False CCA count from रेजिस्टर.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR1);
	qual->false_cca = rt2x00_get_field32(reg, STA_CSR1_FALSE_CCA_ERROR);
पूर्ण

अटल अंतरभूत व्योम rt61pci_set_vgc(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा link_qual *qual, u8 vgc_level)
अणु
	अगर (qual->vgc_level != vgc_level) अणु
		rt61pci_bbp_ग_लिखो(rt2x00dev, 17, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	पूर्ण
पूर्ण

अटल व्योम rt61pci_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा link_qual *qual)
अणु
	rt61pci_set_vgc(rt2x00dev, qual, 0x20);
पूर्ण

अटल व्योम rt61pci_link_tuner(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा link_qual *qual, स्थिर u32 count)
अणु
	u8 up_bound;
	u8 low_bound;

	/*
	 * Determine r17 bounds.
	 */
	अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ) अणु
		low_bound = 0x28;
		up_bound = 0x48;
		अगर (rt2x00_has_cap_बाह्यal_lna_a(rt2x00dev)) अणु
			low_bound += 0x10;
			up_bound += 0x10;
		पूर्ण
	पूर्ण अन्यथा अणु
		low_bound = 0x20;
		up_bound = 0x40;
		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev)) अणु
			low_bound += 0x10;
			up_bound += 0x10;
		पूर्ण
	पूर्ण

	/*
	 * If we are not associated, we should go straight to the
	 * dynamic CCA tuning.
	 */
	अगर (!rt2x00dev->पूर्णांकf_associated)
		जाओ dynamic_cca_tune;

	/*
	 * Special big-R17 क्रम very लघु distance
	 */
	अगर (qual->rssi >= -35) अणु
		rt61pci_set_vgc(rt2x00dev, qual, 0x60);
		वापस;
	पूर्ण

	/*
	 * Special big-R17 क्रम लघु distance
	 */
	अगर (qual->rssi >= -58) अणु
		rt61pci_set_vgc(rt2x00dev, qual, up_bound);
		वापस;
	पूर्ण

	/*
	 * Special big-R17 क्रम middle-लघु distance
	 */
	अगर (qual->rssi >= -66) अणु
		rt61pci_set_vgc(rt2x00dev, qual, low_bound + 0x10);
		वापस;
	पूर्ण

	/*
	 * Special mid-R17 क्रम middle distance
	 */
	अगर (qual->rssi >= -74) अणु
		rt61pci_set_vgc(rt2x00dev, qual, low_bound + 0x08);
		वापस;
	पूर्ण

	/*
	 * Special हाल: Change up_bound based on the rssi.
	 * Lower up_bound when rssi is weaker then -74 dBm.
	 */
	up_bound -= 2 * (-74 - qual->rssi);
	अगर (low_bound > up_bound)
		up_bound = low_bound;

	अगर (qual->vgc_level > up_bound) अणु
		rt61pci_set_vgc(rt2x00dev, qual, up_bound);
		वापस;
	पूर्ण

dynamic_cca_tune:

	/*
	 * r17 करोes not yet exceed upper limit, जारी and base
	 * the r17 tuning on the false CCA count.
	 */
	अगर ((qual->false_cca > 512) && (qual->vgc_level < up_bound))
		rt61pci_set_vgc(rt2x00dev, qual, ++qual->vgc_level);
	अन्यथा अगर ((qual->false_cca < 100) && (qual->vgc_level > low_bound))
		rt61pci_set_vgc(rt2x00dev, qual, --qual->vgc_level);
पूर्ण

/*
 * Queue handlers.
 */
अटल व्योम rt61pci_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt61pci_kick_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_KICK_TX_AC0, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_VI:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_KICK_TX_AC1, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_BE:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_KICK_TX_AC2, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_BK:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_KICK_TX_AC3, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt61pci_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_ABORT_TX_AC0, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_VI:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_ABORT_TX_AC1, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_BE:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_ABORT_TX_AC2, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_AC_BK:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_CNTL_CSR);
		rt2x00_set_field32(&reg, TX_CNTL_CSR_ABORT_TX_AC3, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_CNTL_CSR, reg);
		अवरोध;
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 0);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 0);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

		/*
		 * Wait क्रम possibly running tbtt tasklets.
		 */
		tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Firmware functions
 */
अटल अक्षर *rt61pci_get_firmware_name(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 chip;
	अक्षर *fw_name;

	pci_पढ़ो_config_word(to_pci_dev(rt2x00dev->dev), PCI_DEVICE_ID, &chip);
	चयन (chip) अणु
	हाल RT2561_PCI_ID:
		fw_name = FIRMWARE_RT2561;
		अवरोध;
	हाल RT2561s_PCI_ID:
		fw_name = FIRMWARE_RT2561s;
		अवरोध;
	हाल RT2661_PCI_ID:
		fw_name = FIRMWARE_RT2661;
		अवरोध;
	शेष:
		fw_name = शून्य;
		अवरोध;
	पूर्ण

	वापस fw_name;
पूर्ण

अटल पूर्णांक rt61pci_check_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	u16 fw_crc;
	u16 crc;

	/*
	 * Only support 8kb firmware files.
	 */
	अगर (len != 8192)
		वापस FW_BAD_LENGTH;

	/*
	 * The last 2 bytes in the firmware array are the crc checksum itself.
	 * This means that we should never pass those 2 bytes to the crc
	 * algorithm.
	 */
	fw_crc = (data[len - 2] << 8 | data[len - 1]);

	/*
	 * Use the crc itu-t algorithm.
	 */
	crc = crc_itu_t(0, data, len - 2);
	crc = crc_itu_t_byte(crc, 0);
	crc = crc_itu_t_byte(crc, 0);

	वापस (fw_crc == crc) ? FW_OK : FW_BAD_CRC;
पूर्ण

अटल पूर्णांक rt61pci_load_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				 स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	पूर्णांक i;
	u32 reg;

	/*
	 * Wait क्रम stable hardware.
	 */
	क्रम (i = 0; i < 100; i++) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
		अगर (reg)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (!reg) अणु
		rt2x00_err(rt2x00dev, "Unstable hardware\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Prepare MCU and mailbox क्रम firmware loading.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_CNTL_CSR, reg);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, M2H_CMD_DONE_CSR, 0xffffffff);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, H2M_MAILBOX_CSR, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HOST_CMD_CSR, 0);

	/*
	 * Write firmware to device.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 1);
	rt2x00_set_field32(&reg, MCU_CNTL_CSR_SELECT_BANK, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_CNTL_CSR, reg);

	rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, FIRMWARE_IMAGE_BASE,
				       data, len);

	rt2x00_set_field32(&reg, MCU_CNTL_CSR_SELECT_BANK, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_CNTL_CSR, reg);

	rt2x00_set_field32(&reg, MCU_CNTL_CSR_RESET, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_CNTL_CSR, reg);

	क्रम (i = 0; i < 100; i++) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_CNTL_CSR);
		अगर (rt2x00_get_field32(reg, MCU_CNTL_CSR_READY))
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 100) अणु
		rt2x00_err(rt2x00dev, "MCU Control register not ready\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Hardware needs another millisecond beक्रमe it is पढ़ोy.
	 */
	msleep(1);

	/*
	 * Reset MAC and BBP रेजिस्टरs.
	 */
	reg = 0;
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_HOST_READY, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	वापस 0;
पूर्ण

/*
 * Initialization functions.
 */
अटल bool rt61pci_get_entry_state(काष्ठा queue_entry *entry)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word;

	अगर (entry->queue->qid == QID_RX) अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);

		वापस rt2x00_get_field32(word, RXD_W0_OWNER_NIC);
	पूर्ण अन्यथा अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);

		वापस (rt2x00_get_field32(word, TXD_W0_OWNER_NIC) ||
		        rt2x00_get_field32(word, TXD_W0_VALID));
	पूर्ण
पूर्ण

अटल व्योम rt61pci_clear_entry(काष्ठा queue_entry *entry)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	u32 word;

	अगर (entry->queue->qid == QID_RX) अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 5);
		rt2x00_set_field32(&word, RXD_W5_BUFFER_PHYSICAL_ADDRESS,
				   skbdesc->skb_dma);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 5, word);

		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);
		rt2x00_set_field32(&word, RXD_W0_OWNER_NIC, 1);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 0, word);
	पूर्ण अन्यथा अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);
		rt2x00_set_field32(&word, TXD_W0_VALID, 0);
		rt2x00_set_field32(&word, TXD_W0_OWNER_NIC, 0);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 0, word);
	पूर्ण
पूर्ण

अटल पूर्णांक rt61pci_init_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv;
	u32 reg;

	/*
	 * Initialize रेजिस्टरs.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_RING_CSR0);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC0_RING_SIZE,
			   rt2x00dev->tx[0].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC1_RING_SIZE,
			   rt2x00dev->tx[1].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC2_RING_SIZE,
			   rt2x00dev->tx[2].limit);
	rt2x00_set_field32(&reg, TX_RING_CSR0_AC3_RING_SIZE,
			   rt2x00dev->tx[3].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RING_CSR0, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_RING_CSR1);
	rt2x00_set_field32(&reg, TX_RING_CSR1_TXD_SIZE,
			   rt2x00dev->tx[0].desc_size / 4);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_RING_CSR1, reg);

	entry_priv = rt2x00dev->tx[0].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AC0_BASE_CSR);
	rt2x00_set_field32(&reg, AC0_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AC0_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[1].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AC1_BASE_CSR);
	rt2x00_set_field32(&reg, AC1_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AC1_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[2].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AC2_BASE_CSR);
	rt2x00_set_field32(&reg, AC2_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AC2_BASE_CSR, reg);

	entry_priv = rt2x00dev->tx[3].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AC3_BASE_CSR);
	rt2x00_set_field32(&reg, AC3_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AC3_BASE_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RX_RING_CSR);
	rt2x00_set_field32(&reg, RX_RING_CSR_RING_SIZE, rt2x00dev->rx->limit);
	rt2x00_set_field32(&reg, RX_RING_CSR_RXD_SIZE,
			   rt2x00dev->rx->desc_size / 4);
	rt2x00_set_field32(&reg, RX_RING_CSR_RXD_WRITEBACK_SIZE, 4);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_RING_CSR, reg);

	entry_priv = rt2x00dev->rx->entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RX_BASE_CSR);
	rt2x00_set_field32(&reg, RX_BASE_CSR_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_BASE_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TX_DMA_DST_CSR);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC0, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC1, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC2, 2);
	rt2x00_set_field32(&reg, TX_DMA_DST_CSR_DEST_AC3, 2);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TX_DMA_DST_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, LOAD_TX_RING_CSR);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC0, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC1, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC2, 1);
	rt2x00_set_field32(&reg, LOAD_TX_RING_CSR_LOAD_TXD_AC3, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, LOAD_TX_RING_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RX_CNTL_CSR);
	rt2x00_set_field32(&reg, RX_CNTL_CSR_LOAD_RXD, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_CNTL_CSR, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt61pci_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field32(&reg, TXRX_CSR0_AUTO_TX_SEQ, 1);
	rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
	rt2x00_set_field32(&reg, TXRX_CSR0_TX_WITHOUT_WAITING, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID0, 47); /* CCK Signal */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID1, 30); /* Rssi */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID2, 42); /* OFDM Rate */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID2_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID3, 30); /* Rssi */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID3_VALID, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR1, reg);

	/*
	 * CCK TXD BBP रेजिस्टरs
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID0, 13);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID1, 12);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID2, 11);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID2_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID3, 10);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID3_VALID, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);

	/*
	 * OFDM TXD BBP रेजिस्टरs
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR3);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID0, 7);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID1, 6);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID2, 5);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID2_VALID, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR3, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR7);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_6MBS, 59);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_9MBS, 53);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_12MBS, 49);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_18MBS, 46);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR7, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR8);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_24MBS, 44);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_36MBS, 42);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_48MBS, 42);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_54MBS, 42);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR8, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_INTERVAL, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TIMESTAMP_COMPENSATE, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR15, 0x0000000f);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR6, 0x00000fff);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR9);
	rt2x00_set_field32(&reg, MAC_CSR9_CW_SELECT, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR9, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR10, 0x0000071c);

	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		वापस -EBUSY;

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, 0x0000e000);

	/*
	 * Invalidate all Shared Keys (SEC_CSR0),
	 * and clear the Shared key Cipher algorithms (SEC_CSR1 & SEC_CSR5)
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR0, 0x00000000);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR1, 0x00000000);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR5, 0x00000000);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR1, 0x000023b0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR5, 0x060a100c);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR6, 0x00080606);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR7, 0x00000a08);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PCI_CFG_CSR, 0x28ca4404);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TEST_MODE_CSR, 0x00000200);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, M2H_CMD_DONE_CSR, 0xffffffff);

	/*
	 * Clear all beacons
	 * For the Beacon base रेजिस्टरs we only need to clear
	 * the first byte since that byte contains the VALID and OWNER
	 * bits which (when set to 0) will invalidate the entire beacon.
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE0, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE1, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE2, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE3, 0);

	/*
	 * We must clear the error counters.
	 * These रेजिस्टरs are cleared on पढ़ो,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR0);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR1);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR2);

	/*
	 * Reset MAC and BBP रेजिस्टरs.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_HOST_READY, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt61pci_रुको_bbp_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u8 value;

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		value = rt61pci_bbp_पढ़ो(rt2x00dev, 0);
		अगर ((value != 0xff) && (value != 0x00))
			वापस 0;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल पूर्णांक rt61pci_init_bbp(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	अगर (unlikely(rt61pci_रुको_bbp_पढ़ोy(rt2x00dev)))
		वापस -EACCES;

	rt61pci_bbp_ग_लिखो(rt2x00dev, 3, 0x00);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 15, 0x30);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 21, 0xc8);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 22, 0x38);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 23, 0x06);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 24, 0xfe);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 25, 0x0a);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 26, 0x0d);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 34, 0x12);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 37, 0x07);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 39, 0xf8);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 41, 0x60);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 53, 0x10);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 54, 0x18);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 60, 0x10);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 61, 0x04);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 62, 0x04);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 75, 0xfe);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 86, 0xfe);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 88, 0xfe);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 90, 0x0f);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 99, 0x00);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 102, 0x16);
	rt61pci_bbp_ग_लिखो(rt2x00dev, 107, 0x04);

	क्रम (i = 0; i < EEPROM_BBP_SIZE; i++) अणु
		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBP_START + i);

		अगर (eeprom != 0xffff && eeprom != 0x0000) अणु
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt61pci_bbp_ग_लिखो(rt2x00dev, reg_id, value);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल व्योम rt61pci_toggle_irq(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत dev_state state)
अणु
	पूर्णांक mask = (state == STATE_RADIO_IRQ_OFF);
	u32 reg;
	अचिन्हित दीर्घ flags;

	/*
	 * When पूर्णांकerrupts are being enabled, the पूर्णांकerrupt रेजिस्टरs
	 * should clear the रेजिस्टर to assure a clean state.
	 */
	अगर (state == STATE_RADIO_IRQ_ON) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_SOURCE_CSR);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_SOURCE_CSR, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_INT_SOURCE_CSR);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_INT_SOURCE_CSR, reg);
	पूर्ण

	/*
	 * Only toggle the पूर्णांकerrupts bits we are going to use.
	 * Non-checked पूर्णांकerrupt bits are disabled by शेष.
	 */
	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_MASK_CSR);
	rt2x00_set_field32(&reg, INT_MASK_CSR_TXDONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_RXDONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_BEACON_DONE, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_ENABLE_MITIGATION, mask);
	rt2x00_set_field32(&reg, INT_MASK_CSR_MITIGATION_PERIOD, 0xff);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_INT_MASK_CSR);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_0, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_1, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_2, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_3, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_4, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_5, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_6, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_7, mask);
	rt2x00_set_field32(&reg, MCU_INT_MASK_CSR_TWAKEUP, mask);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_INT_MASK_CSR, reg);

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	अगर (state == STATE_RADIO_IRQ_OFF) अणु
		/*
		 * Ensure that all tasklets are finished.
		 */
		tasklet_समाप्त(&rt2x00dev->txstatus_tasklet);
		tasklet_समाप्त(&rt2x00dev->rxकरोne_tasklet);
		tasklet_समाप्त(&rt2x00dev->स्वतःwake_tasklet);
		tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
	पूर्ण
पूर्ण

अटल पूर्णांक rt61pci_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	/*
	 * Initialize all रेजिस्टरs.
	 */
	अगर (unlikely(rt61pci_init_queues(rt2x00dev) ||
		     rt61pci_init_रेजिस्टरs(rt2x00dev) ||
		     rt61pci_init_bbp(rt2x00dev)))
		वापस -EIO;

	/*
	 * Enable RX.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RX_CNTL_CSR);
	rt2x00_set_field32(&reg, RX_CNTL_CSR_ENABLE_RX_DMA, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RX_CNTL_CSR, reg);

	वापस 0;
पूर्ण

अटल व्योम rt61pci_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Disable घातer
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR10, 0x00001818);
पूर्ण

अटल पूर्णांक rt61pci_set_state(काष्ठा rt2x00_dev *rt2x00dev, क्रमागत dev_state state)
अणु
	u32 reg, reg2;
	अचिन्हित पूर्णांक i;
	अक्षर put_to_sleep;

	put_to_sleep = (state != STATE_AWAKE);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR12);
	rt2x00_set_field32(&reg, MAC_CSR12_FORCE_WAKEUP, !put_to_sleep);
	rt2x00_set_field32(&reg, MAC_CSR12_PUT_TO_SLEEP, put_to_sleep);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR12, reg);

	/*
	 * Device is not guaranteed to be in the requested state yet.
	 * We must रुको until the रेजिस्टर indicates that the
	 * device has entered the correct state.
	 */
	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg2 = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR12);
		state = rt2x00_get_field32(reg2, MAC_CSR12_BBP_CURRENT_STATE);
		अगर (state == !put_to_sleep)
			वापस 0;
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR12, reg);
		msleep(10);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rt61pci_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				    क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt61pci_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		rt61pci_disable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		rt61pci_toggle_irq(rt2x00dev, state);
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt61pci_set_state(rt2x00dev, state);
		अवरोध;
	शेष:
		retval = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (unlikely(retval))
		rt2x00_err(rt2x00dev, "Device failed to enter state %d (%d)\n",
			   state, retval);

	वापस retval;
पूर्ण

/*
 * TX descriptor initialization
 */
अटल व्योम rt61pci_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
				  काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	__le32 *txd = entry_priv->desc;
	u32 word;

	/*
	 * Start writing the descriptor words.
	 */
	word = rt2x00_desc_पढ़ो(txd, 1);
	rt2x00_set_field32(&word, TXD_W1_HOST_Q_ID, entry->queue->qid);
	rt2x00_set_field32(&word, TXD_W1_AIFSN, entry->queue->aअगरs);
	rt2x00_set_field32(&word, TXD_W1_CWMIN, entry->queue->cw_min);
	rt2x00_set_field32(&word, TXD_W1_CWMAX, entry->queue->cw_max);
	rt2x00_set_field32(&word, TXD_W1_IV_OFFSET, txdesc->iv_offset);
	rt2x00_set_field32(&word, TXD_W1_HW_SEQUENCE,
			   test_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W1_BUFFER_COUNT, 1);
	rt2x00_desc_ग_लिखो(txd, 1, word);

	word = rt2x00_desc_पढ़ो(txd, 2);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SIGNAL, txdesc->u.plcp.संकेत);
	rt2x00_set_field32(&word, TXD_W2_PLCP_SERVICE, txdesc->u.plcp.service);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_LOW,
			   txdesc->u.plcp.length_low);
	rt2x00_set_field32(&word, TXD_W2_PLCP_LENGTH_HIGH,
			   txdesc->u.plcp.length_high);
	rt2x00_desc_ग_लिखो(txd, 2, word);

	अगर (test_bit(ENTRY_TXD_ENCRYPT, &txdesc->flags)) अणु
		_rt2x00_desc_ग_लिखो(txd, 3, skbdesc->iv[0]);
		_rt2x00_desc_ग_लिखो(txd, 4, skbdesc->iv[1]);
	पूर्ण

	word = rt2x00_desc_पढ़ो(txd, 5);
	rt2x00_set_field32(&word, TXD_W5_PID_TYPE, entry->queue->qid);
	rt2x00_set_field32(&word, TXD_W5_PID_SUBTYPE, entry->entry_idx);
	rt2x00_set_field32(&word, TXD_W5_TX_POWER,
			   TXPOWER_TO_DEV(entry->queue->rt2x00dev->tx_घातer));
	rt2x00_set_field32(&word, TXD_W5_WAITING_DMA_DONE_INT, 1);
	rt2x00_desc_ग_लिखो(txd, 5, word);

	अगर (entry->queue->qid != QID_BEACON) अणु
		word = rt2x00_desc_पढ़ो(txd, 6);
		rt2x00_set_field32(&word, TXD_W6_BUFFER_PHYSICAL_ADDRESS,
				   skbdesc->skb_dma);
		rt2x00_desc_ग_लिखो(txd, 6, word);

		word = rt2x00_desc_पढ़ो(txd, 11);
		rt2x00_set_field32(&word, TXD_W11_BUFFER_LENGTH0,
				   txdesc->length);
		rt2x00_desc_ग_लिखो(txd, 11, word);
	पूर्ण

	/*
	 * Writing TXD word 0 must the last to prevent a race condition with
	 * the device, whereby the device may take hold of the TXD beक्रमe we
	 * finished updating it.
	 */
	word = rt2x00_desc_पढ़ो(txd, 0);
	rt2x00_set_field32(&word, TXD_W0_OWNER_NIC, 1);
	rt2x00_set_field32(&word, TXD_W0_VALID, 1);
	rt2x00_set_field32(&word, TXD_W0_MORE_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TIMESTAMP,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_OFDM,
			   (txdesc->rate_mode == RATE_MODE_OFDM));
	rt2x00_set_field32(&word, TXD_W0_IFS, txdesc->u.plcp.अगरs);
	rt2x00_set_field32(&word, TXD_W0_RETRY_MODE,
			   test_bit(ENTRY_TXD_RETRY_MODE, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TKIP_MIC,
			   test_bit(ENTRY_TXD_ENCRYPT_MMIC, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_KEY_TABLE,
			   test_bit(ENTRY_TXD_ENCRYPT_PAIRWISE, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_KEY_INDEX, txdesc->key_idx);
	rt2x00_set_field32(&word, TXD_W0_DATABYTE_COUNT, txdesc->length);
	rt2x00_set_field32(&word, TXD_W0_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_CIPHER_ALG, txdesc->cipher);
	rt2x00_desc_ग_लिखो(txd, 0, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_len = (entry->queue->qid == QID_BEACON) ? TXINFO_SIZE :
			    TXD_DESC_SIZE;
पूर्ण

/*
 * TX data initialization
 */
अटल व्योम rt61pci_ग_लिखो_beacon(काष्ठा queue_entry *entry,
				 काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	अचिन्हित पूर्णांक beacon_base;
	अचिन्हित पूर्णांक padding_len;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	orig_reg = reg;
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Write the TX descriptor क्रम the beacon.
	 */
	rt61pci_ग_लिखो_tx_desc(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry);

	/*
	 * Write entire beacon with descriptor and padding to रेजिस्टर.
	 */
	padding_len = roundup(entry->skb->len, 4) - entry->skb->len;
	अगर (padding_len && skb_pad(entry->skb, padding_len)) अणु
		rt2x00_err(rt2x00dev, "Failure padding beacon, aborting\n");
		/* skb मुक्तd by skb_pad() on failure */
		entry->skb = शून्य;
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, orig_reg);
		वापस;
	पूर्ण

	beacon_base = HW_BEACON_OFFSET(entry->entry_idx);
	rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, beacon_base,
				       entry_priv->desc, TXINFO_SIZE);
	rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, beacon_base + TXINFO_SIZE,
				       entry->skb->data,
				       entry->skb->len + padding_len);

	/*
	 * Enable beaconing again.
	 *
	 * For Wi-Fi faily generated beacons between participating
	 * stations. Set TBTT phase adaptive adjusपंचांगent step to 8us.
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR10, 0x00001008);

	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Clean up beacon skb.
	 */
	dev_kमुक्त_skb_any(entry->skb);
	entry->skb = शून्य;
पूर्ण

अटल व्योम rt61pci_clear_beacon(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	orig_reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	reg = orig_reg;
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Clear beacon.
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev,
				  HW_BEACON_OFFSET(entry->entry_idx), 0);

	/*
	 * Restore global beaconing state.
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, orig_reg);
पूर्ण

/*
 * RX control handlers
 */
अटल पूर्णांक rt61pci_agc_to_rssi(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक rxd_w1)
अणु
	u8 offset = rt2x00dev->lna_gain;
	u8 lna;

	lna = rt2x00_get_field32(rxd_w1, RXD_W1_RSSI_LNA);
	चयन (lna) अणु
	हाल 3:
		offset += 90;
		अवरोध;
	हाल 2:
		offset += 74;
		अवरोध;
	हाल 1:
		offset += 64;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (rt2x00dev->curr_band == NL80211_BAND_5GHZ) अणु
		अगर (lna == 3 || lna == 2)
			offset += 10;
	पूर्ण

	वापस rt2x00_get_field32(rxd_w1, RXD_W1_RSSI_AGC) * 2 - offset;
पूर्ण

अटल व्योम rt61pci_fill_rxकरोne(काष्ठा queue_entry *entry,
				काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word0;
	u32 word1;

	word0 = rt2x00_desc_पढ़ो(entry_priv->desc, 0);
	word1 = rt2x00_desc_पढ़ो(entry_priv->desc, 1);

	अगर (rt2x00_get_field32(word0, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	rxdesc->cipher = rt2x00_get_field32(word0, RXD_W0_CIPHER_ALG);
	rxdesc->cipher_status = rt2x00_get_field32(word0, RXD_W0_CIPHER_ERROR);

	अगर (rxdesc->cipher != CIPHER_NONE) अणु
		rxdesc->iv[0] = _rt2x00_desc_पढ़ो(entry_priv->desc, 2);
		rxdesc->iv[1] = _rt2x00_desc_पढ़ो(entry_priv->desc, 3);
		rxdesc->dev_flags |= RXDONE_CRYPTO_IV;

		rxdesc->icv = _rt2x00_desc_पढ़ो(entry_priv->desc, 4);
		rxdesc->dev_flags |= RXDONE_CRYPTO_ICV;

		/*
		 * Hardware has stripped IV/EIV data from 802.11 frame during
		 * decryption. It has provided the data separately but rt2x00lib
		 * should decide अगर it should be reinserted.
		 */
		rxdesc->flags |= RX_FLAG_IV_STRIPPED;

		/*
		 * The hardware has alपढ़ोy checked the Michael Mic and has
		 * stripped it from the frame. Signal this to mac80211.
		 */
		rxdesc->flags |= RX_FLAG_MMIC_STRIPPED;

		अगर (rxdesc->cipher_status == RX_CRYPTO_SUCCESS)
			rxdesc->flags |= RX_FLAG_DECRYPTED;
		अन्यथा अगर (rxdesc->cipher_status == RX_CRYPTO_FAIL_MIC)
			rxdesc->flags |= RX_FLAG_MMIC_ERROR;
	पूर्ण

	/*
	 * Obtain the status about this packet.
	 * When frame was received with an OFDM bitrate,
	 * the संकेत is the PLCP value. If it was received with
	 * a CCK bitrate the संकेत is the rate in 100kbit/s.
	 */
	rxdesc->संकेत = rt2x00_get_field32(word1, RXD_W1_SIGNAL);
	rxdesc->rssi = rt61pci_agc_to_rssi(rt2x00dev, word1);
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	अगर (rt2x00_get_field32(word0, RXD_W0_OFDM))
		rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	अन्यथा
		rxdesc->dev_flags |= RXDONE_SIGNAL_BITRATE;
	अगर (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;
पूर्ण

/*
 * Interrupt functions.
 */
अटल व्योम rt61pci_txकरोne(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	काष्ठा queue_entry *entry;
	काष्ठा queue_entry *entry_करोne;
	काष्ठा queue_entry_priv_mmio *entry_priv;
	काष्ठा txकरोne_entry_desc txdesc;
	u32 word;
	u32 reg;
	पूर्णांक type;
	पूर्णांक index;
	पूर्णांक i;

	/*
	 * TX_STA_FIFO is a stack of X entries, hence पढ़ो TX_STA_FIFO
	 * at most X बार and also stop processing once the TX_STA_FIFO_VALID
	 * flag is not set anymore.
	 *
	 * The legacy drivers use X=TX_RING_SIZE but state in a comment
	 * that the TX_STA_FIFO stack has a size of 16. We stick to our
	 * tx ring size क्रम now.
	 */
	क्रम (i = 0; i < rt2x00dev->tx->limit; i++) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR4);
		अगर (!rt2x00_get_field32(reg, STA_CSR4_VALID))
			अवरोध;

		/*
		 * Skip this entry when it contains an invalid
		 * queue identication number.
		 */
		type = rt2x00_get_field32(reg, STA_CSR4_PID_TYPE);
		queue = rt2x00queue_get_tx_queue(rt2x00dev, type);
		अगर (unlikely(!queue))
			जारी;

		/*
		 * Skip this entry when it contains an invalid
		 * index number.
		 */
		index = rt2x00_get_field32(reg, STA_CSR4_PID_SUBTYPE);
		अगर (unlikely(index >= queue->limit))
			जारी;

		entry = &queue->entries[index];
		entry_priv = entry->priv_data;
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);

		अगर (rt2x00_get_field32(word, TXD_W0_OWNER_NIC) ||
		    !rt2x00_get_field32(word, TXD_W0_VALID))
			वापस;

		entry_करोne = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		जबतक (entry != entry_करोne) अणु
			/* Catch up.
			 * Just report any entries we missed as failed.
			 */
			rt2x00_warn(rt2x00dev, "TX status report missed for entry %d\n",
				    entry_करोne->entry_idx);

			rt2x00lib_txकरोne_noinfo(entry_करोne, TXDONE_UNKNOWN);
			entry_करोne = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		पूर्ण

		/*
		 * Obtain the status about this packet.
		 */
		txdesc.flags = 0;
		चयन (rt2x00_get_field32(reg, STA_CSR4_TX_RESULT)) अणु
		हाल 0: /* Success, maybe with retry */
			__set_bit(TXDONE_SUCCESS, &txdesc.flags);
			अवरोध;
		हाल 6: /* Failure, excessive retries */
			__set_bit(TXDONE_EXCESSIVE_RETRY, &txdesc.flags);
			fallthrough;	/* this is a failed frame! */
		शेष: /* Failure */
			__set_bit(TXDONE_FAILURE, &txdesc.flags);
		पूर्ण
		txdesc.retry = rt2x00_get_field32(reg, STA_CSR4_RETRY_COUNT);

		/*
		 * the frame was retried at least once
		 * -> hw used fallback rates
		 */
		अगर (txdesc.retry)
			__set_bit(TXDONE_FALLBACK, &txdesc.flags);

		rt2x00lib_txकरोne(entry, &txdesc);
	पूर्ण
पूर्ण

अटल व्योम rt61pci_wakeup(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा rt2x00lib_conf libconf = अणु .conf = &rt2x00dev->hw->conf पूर्ण;

	rt61pci_config(rt2x00dev, &libconf, IEEE80211_CONF_CHANGE_PS);
पूर्ण

अटल अंतरभूत व्योम rt61pci_enable_पूर्णांकerrupt(काष्ठा rt2x00_dev *rt2x00dev,
					    काष्ठा rt2x00_field32 irq_field)
अणु
	u32 reg;

	/*
	 * Enable a single पूर्णांकerrupt. The पूर्णांकerrupt mask रेजिस्टर
	 * access needs locking.
	 */
	spin_lock_irq(&rt2x00dev->irqmask_lock);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_MASK_CSR);
	rt2x00_set_field32(&reg, irq_field, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);

	spin_unlock_irq(&rt2x00dev->irqmask_lock);
पूर्ण

अटल व्योम rt61pci_enable_mcu_पूर्णांकerrupt(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा rt2x00_field32 irq_field)
अणु
	u32 reg;

	/*
	 * Enable a single MCU पूर्णांकerrupt. The पूर्णांकerrupt mask रेजिस्टर
	 * access needs locking.
	 */
	spin_lock_irq(&rt2x00dev->irqmask_lock);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_INT_MASK_CSR);
	rt2x00_set_field32(&reg, irq_field, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_INT_MASK_CSR, reg);

	spin_unlock_irq(&rt2x00dev->irqmask_lock);
पूर्ण

अटल व्योम rt61pci_txstatus_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    txstatus_tasklet);

	rt61pci_txकरोne(rt2x00dev);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt61pci_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_TXDONE);
पूर्ण

अटल व्योम rt61pci_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t, tbtt_tasklet);
	rt2x00lib_beaconकरोne(rt2x00dev);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt61pci_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_BEACON_DONE);
पूर्ण

अटल व्योम rt61pci_rxकरोne_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    rxकरोne_tasklet);
	अगर (rt2x00mmio_rxकरोne(rt2x00dev))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);
	अन्यथा अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt61pci_enable_पूर्णांकerrupt(rt2x00dev, INT_MASK_CSR_RXDONE);
पूर्ण

अटल व्योम rt61pci_स्वतःwake_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    स्वतःwake_tasklet);
	rt61pci_wakeup(rt2x00dev);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev,
				  M2H_CMD_DONE_CSR, 0xffffffff);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt61pci_enable_mcu_पूर्णांकerrupt(rt2x00dev, MCU_INT_MASK_CSR_TWAKEUP);
पूर्ण

अटल irqवापस_t rt61pci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg_mcu, mask_mcu;
	u32 reg, mask;

	/*
	 * Get the पूर्णांकerrupt sources & saved to local variable.
	 * Write रेजिस्टर value back to clear pending पूर्णांकerrupts.
	 */
	reg_mcu = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_INT_SOURCE_CSR);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_INT_SOURCE_CSR, reg_mcu);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_SOURCE_CSR);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_SOURCE_CSR, reg);

	अगर (!reg && !reg_mcu)
		वापस IRQ_NONE;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस IRQ_HANDLED;

	/*
	 * Schedule tasklets क्रम पूर्णांकerrupt handling.
	 */
	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_RXDONE))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_TXDONE))
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);

	अगर (rt2x00_get_field32(reg, INT_SOURCE_CSR_BEACON_DONE))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	अगर (rt2x00_get_field32(reg_mcu, MCU_INT_SOURCE_CSR_TWAKEUP))
		tasklet_schedule(&rt2x00dev->स्वतःwake_tasklet);

	/*
	 * Since INT_MASK_CSR and INT_SOURCE_CSR use the same bits
	 * क्रम पूर्णांकerrupts and पूर्णांकerrupt masks we can just use the value of
	 * INT_SOURCE_CSR to create the पूर्णांकerrupt mask.
	 */
	mask = reg;
	mask_mcu = reg_mcu;

	/*
	 * Disable all पूर्णांकerrupts क्रम which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate पूर्णांकerrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, INT_MASK_CSR);
	reg |= mask;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, INT_MASK_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MCU_INT_MASK_CSR);
	reg |= mask_mcu;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MCU_INT_MASK_CSR, reg);

	spin_unlock(&rt2x00dev->irqmask_lock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Device probe functions.
 */
अटल पूर्णांक rt61pci_validate_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा eeprom_93cx6 eeprom;
	u32 reg;
	u16 word;
	u8 *mac;
	s8 value;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, E2PROM_CSR);

	eeprom.data = rt2x00dev;
	eeprom.रेजिस्टर_पढ़ो = rt61pci_eepromरेजिस्टर_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = rt61pci_eepromरेजिस्टर_ग_लिखो;
	eeprom.width = rt2x00_get_field32(reg, E2PROM_CSR_TYPE_93C46) ?
	    PCI_EEPROM_WIDTH_93C46 : PCI_EEPROM_WIDTH_93C66;
	eeprom.reg_data_in = 0;
	eeprom.reg_data_out = 0;
	eeprom.reg_data_घड़ी = 0;
	eeprom.reg_chip_select = 0;

	eeprom_93cx6_multiपढ़ो(&eeprom, EEPROM_BASE, rt2x00dev->eeprom,
			       EEPROM_SIZE / माप(u16));

	/*
	 * Start validation of the data that has been पढ़ो.
	 */
	mac = rt2x00_eeprom_addr(rt2x00dev, EEPROM_MAC_ADDR_0);
	rt2x00lib_set_mac_address(rt2x00dev, mac);

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_ANTENNA);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_ANTENNA_NUM, 2);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_TX_DEFAULT,
				   ANTENNA_B);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RX_DEFAULT,
				   ANTENNA_B);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_FRAME_TYPE, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_DYN_TXAGC, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_HARDWARE_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RF_TYPE, RF5225);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_ANTENNA, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_NIC_ENABLE_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_TX_DIVERSITY, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_RX_FIXED, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_TX_FIXED, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_EXTERNAL_LNA_BG, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_EXTERNAL_LNA_A, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_LED);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_LED_LED_MODE,
				   LED_MODE_DEFAULT);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_LED, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Led: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_FREQ_OFFSET, 0);
		rt2x00_set_field16(&word, EEPROM_FREQ_SEQ, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_FREQ, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Freq: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_OFFSET_BG);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_1, 0);
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_2, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_OFFSET_BG, word);
		rt2x00_eeprom_dbg(rt2x00dev, "RSSI OFFSET BG: 0x%04x\n", word);
	पूर्ण अन्यथा अणु
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_BG_1);
		अगर (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_1, 0);
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_BG_2);
		अगर (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_BG_2, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_OFFSET_BG, word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_OFFSET_A);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_1, 0);
		rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_2, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_OFFSET_A, word);
		rt2x00_eeprom_dbg(rt2x00dev, "RSSI OFFSET A: 0x%04x\n", word);
	पूर्ण अन्यथा अणु
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_A_1);
		अगर (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_1, 0);
		value = rt2x00_get_field16(word, EEPROM_RSSI_OFFSET_A_2);
		अगर (value < -10 || value > 10)
			rt2x00_set_field16(&word, EEPROM_RSSI_OFFSET_A_2, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_RSSI_OFFSET_A, word);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt61pci_init_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;
	u16 value;
	u16 eeprom;

	/*
	 * Read EEPROM word क्रम configuration.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_ANTENNA);

	/*
	 * Identअगरy RF chipset.
	 */
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RF_TYPE);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
	rt2x00_set_chip(rt2x00dev, rt2x00_get_field32(reg, MAC_CSR0_CHIPSET),
			value, rt2x00_get_field32(reg, MAC_CSR0_REVISION));

	अगर (!rt2x00_rf(rt2x00dev, RF5225) &&
	    !rt2x00_rf(rt2x00dev, RF5325) &&
	    !rt2x00_rf(rt2x00dev, RF2527) &&
	    !rt2x00_rf(rt2x00dev, RF2529)) अणु
		rt2x00_err(rt2x00dev, "Invalid RF chipset detected\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Determine number of antennas.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_NUM) == 2)
		__set_bit(CAPABILITY_DOUBLE_ANTENNA, &rt2x00dev->cap_flags);

	/*
	 * Identअगरy शेष antenna configuration.
	 */
	rt2x00dev->शेष_ant.tx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_TX_DEFAULT);
	rt2x00dev->शेष_ant.rx =
	    rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_DEFAULT);

	/*
	 * Read the Frame type.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_FRAME_TYPE))
		__set_bit(CAPABILITY_FRAME_TYPE, &rt2x00dev->cap_flags);

	/*
	 * Detect अगर this device has a hardware controlled radio.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Read frequency offset and RF programming sequence.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
	अगर (rt2x00_get_field16(eeprom, EEPROM_FREQ_SEQ))
		__set_bit(CAPABILITY_RF_SEQUENCE, &rt2x00dev->cap_flags);

	rt2x00dev->freq_offset = rt2x00_get_field16(eeprom, EEPROM_FREQ_OFFSET);

	/*
	 * Read बाह्यal LNA inक्रमmations.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC);

	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_EXTERNAL_LNA_A))
		__set_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags);
	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_EXTERNAL_LNA_BG))
		__set_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags);

	/*
	 * When working with a RF2529 chip without द्विगुन antenna,
	 * the antenna settings should be gathered from the NIC
	 * eeprom word.
	 */
	अगर (rt2x00_rf(rt2x00dev, RF2529) &&
	    !rt2x00_has_cap_द्विगुन_antenna(rt2x00dev)) अणु
		rt2x00dev->शेष_ant.rx =
		    ANTENNA_A + rt2x00_get_field16(eeprom, EEPROM_NIC_RX_FIXED);
		rt2x00dev->शेष_ant.tx =
		    ANTENNA_B - rt2x00_get_field16(eeprom, EEPROM_NIC_TX_FIXED);

		अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_TX_DIVERSITY))
			rt2x00dev->शेष_ant.tx = ANTENNA_SW_DIVERSITY;
		अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_ENABLE_DIVERSITY))
			rt2x00dev->शेष_ant.rx = ANTENNA_SW_DIVERSITY;
	पूर्ण

	/*
	 * Store led settings, क्रम correct led behaviour.
	 * If the eeprom value is invalid,
	 * चयन to शेष led mode.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_LED);
	value = rt2x00_get_field16(eeprom, EEPROM_LED_LED_MODE);

	rt61pci_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	rt61pci_init_led(rt2x00dev, &rt2x00dev->led_assoc, LED_TYPE_ASSOC);
	अगर (value == LED_MODE_SIGNAL_STRENGTH)
		rt61pci_init_led(rt2x00dev, &rt2x00dev->led_qual,
				 LED_TYPE_QUALITY);

	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_LED_MODE, value);
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_0,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_0));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_1,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_1));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_2,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_2));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_3,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_3));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_GPIO_4,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_GPIO_4));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_ACT,
			   rt2x00_get_field16(eeprom, EEPROM_LED_POLARITY_ACT));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_READY_BG,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_RDY_G));
	rt2x00_set_field16(&rt2x00dev->led_mcu_reg, MCU_LEDCS_POLARITY_READY_A,
			   rt2x00_get_field16(eeprom,
					      EEPROM_LED_POLARITY_RDY_A));
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

	वापस 0;
पूर्ण

/*
 * RF value list क्रम RF5225 & RF5325
 * Supports: 2.4 GHz & 5.2 GHz, rf_sequence disabled
 */
अटल स्थिर काष्ठा rf_channel rf_vals_noseq[] = अणु
	अणु 1,  0x00002ccc, 0x00004786, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 2,  0x00002ccc, 0x00004786, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 3,  0x00002ccc, 0x0000478a, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 4,  0x00002ccc, 0x0000478a, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 5,  0x00002ccc, 0x0000478e, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 6,  0x00002ccc, 0x0000478e, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 7,  0x00002ccc, 0x00004792, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 8,  0x00002ccc, 0x00004792, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 9,  0x00002ccc, 0x00004796, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 10, 0x00002ccc, 0x00004796, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 11, 0x00002ccc, 0x0000479a, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 12, 0x00002ccc, 0x0000479a, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 13, 0x00002ccc, 0x0000479e, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 14, 0x00002ccc, 0x000047a2, 0x00068455, 0x000ffa13 पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु 36, 0x00002ccc, 0x0000499a, 0x0009be55, 0x000ffa23 पूर्ण,
	अणु 40, 0x00002ccc, 0x000049a2, 0x0009be55, 0x000ffa03 पूर्ण,
	अणु 44, 0x00002ccc, 0x000049a6, 0x0009be55, 0x000ffa0b पूर्ण,
	अणु 48, 0x00002ccc, 0x000049aa, 0x0009be55, 0x000ffa13 पूर्ण,
	अणु 52, 0x00002ccc, 0x000049ae, 0x0009ae55, 0x000ffa1b पूर्ण,
	अणु 56, 0x00002ccc, 0x000049b2, 0x0009ae55, 0x000ffa23 पूर्ण,
	अणु 60, 0x00002ccc, 0x000049ba, 0x0009ae55, 0x000ffa03 पूर्ण,
	अणु 64, 0x00002ccc, 0x000049be, 0x0009ae55, 0x000ffa0b पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु 100, 0x00002ccc, 0x00004a2a, 0x000bae55, 0x000ffa03 पूर्ण,
	अणु 104, 0x00002ccc, 0x00004a2e, 0x000bae55, 0x000ffa0b पूर्ण,
	अणु 108, 0x00002ccc, 0x00004a32, 0x000bae55, 0x000ffa13 पूर्ण,
	अणु 112, 0x00002ccc, 0x00004a36, 0x000bae55, 0x000ffa1b पूर्ण,
	अणु 116, 0x00002ccc, 0x00004a3a, 0x000bbe55, 0x000ffa23 पूर्ण,
	अणु 120, 0x00002ccc, 0x00004a82, 0x000bbe55, 0x000ffa03 पूर्ण,
	अणु 124, 0x00002ccc, 0x00004a86, 0x000bbe55, 0x000ffa0b पूर्ण,
	अणु 128, 0x00002ccc, 0x00004a8a, 0x000bbe55, 0x000ffa13 पूर्ण,
	अणु 132, 0x00002ccc, 0x00004a8e, 0x000bbe55, 0x000ffa1b पूर्ण,
	अणु 136, 0x00002ccc, 0x00004a92, 0x000bbe55, 0x000ffa23 पूर्ण,

	/* 802.11 UNII */
	अणु 140, 0x00002ccc, 0x00004a9a, 0x000bbe55, 0x000ffa03 पूर्ण,
	अणु 149, 0x00002ccc, 0x00004aa2, 0x000bbe55, 0x000ffa1f पूर्ण,
	अणु 153, 0x00002ccc, 0x00004aa6, 0x000bbe55, 0x000ffa27 पूर्ण,
	अणु 157, 0x00002ccc, 0x00004aae, 0x000bbe55, 0x000ffa07 पूर्ण,
	अणु 161, 0x00002ccc, 0x00004ab2, 0x000bbe55, 0x000ffa0f पूर्ण,
	अणु 165, 0x00002ccc, 0x00004ab6, 0x000bbe55, 0x000ffa17 पूर्ण,

	/* MMAC(Japan)J52 ch 34,38,42,46 */
	अणु 34, 0x00002ccc, 0x0000499a, 0x0009be55, 0x000ffa0b पूर्ण,
	अणु 38, 0x00002ccc, 0x0000499e, 0x0009be55, 0x000ffa13 पूर्ण,
	अणु 42, 0x00002ccc, 0x000049a2, 0x0009be55, 0x000ffa1b पूर्ण,
	अणु 46, 0x00002ccc, 0x000049a6, 0x0009be55, 0x000ffa23 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF5225 & RF5325
 * Supports: 2.4 GHz & 5.2 GHz, rf_sequence enabled
 */
अटल स्थिर काष्ठा rf_channel rf_vals_seq[] = अणु
	अणु 1,  0x00002ccc, 0x00004786, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 2,  0x00002ccc, 0x00004786, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 3,  0x00002ccc, 0x0000478a, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 4,  0x00002ccc, 0x0000478a, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 5,  0x00002ccc, 0x0000478e, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 6,  0x00002ccc, 0x0000478e, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 7,  0x00002ccc, 0x00004792, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 8,  0x00002ccc, 0x00004792, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 9,  0x00002ccc, 0x00004796, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 10, 0x00002ccc, 0x00004796, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 11, 0x00002ccc, 0x0000479a, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 12, 0x00002ccc, 0x0000479a, 0x00068455, 0x000ffa1f पूर्ण,
	अणु 13, 0x00002ccc, 0x0000479e, 0x00068455, 0x000ffa0b पूर्ण,
	अणु 14, 0x00002ccc, 0x000047a2, 0x00068455, 0x000ffa13 पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु 36, 0x00002cd4, 0x0004481a, 0x00098455, 0x000c0a03 पूर्ण,
	अणु 40, 0x00002cd0, 0x00044682, 0x00098455, 0x000c0a03 पूर्ण,
	अणु 44, 0x00002cd0, 0x00044686, 0x00098455, 0x000c0a1b पूर्ण,
	अणु 48, 0x00002cd0, 0x0004468e, 0x00098655, 0x000c0a0b पूर्ण,
	अणु 52, 0x00002cd0, 0x00044692, 0x00098855, 0x000c0a23 पूर्ण,
	अणु 56, 0x00002cd0, 0x0004469a, 0x00098c55, 0x000c0a13 पूर्ण,
	अणु 60, 0x00002cd0, 0x000446a2, 0x00098e55, 0x000c0a03 पूर्ण,
	अणु 64, 0x00002cd0, 0x000446a6, 0x00099255, 0x000c0a1b पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु 100, 0x00002cd4, 0x0004489a, 0x000b9855, 0x000c0a03 पूर्ण,
	अणु 104, 0x00002cd4, 0x000448a2, 0x000b9855, 0x000c0a03 पूर्ण,
	अणु 108, 0x00002cd4, 0x000448aa, 0x000b9855, 0x000c0a03 पूर्ण,
	अणु 112, 0x00002cd4, 0x000448b2, 0x000b9a55, 0x000c0a03 पूर्ण,
	अणु 116, 0x00002cd4, 0x000448ba, 0x000b9a55, 0x000c0a03 पूर्ण,
	अणु 120, 0x00002cd0, 0x00044702, 0x000b9a55, 0x000c0a03 पूर्ण,
	अणु 124, 0x00002cd0, 0x00044706, 0x000b9a55, 0x000c0a1b पूर्ण,
	अणु 128, 0x00002cd0, 0x0004470e, 0x000b9c55, 0x000c0a0b पूर्ण,
	अणु 132, 0x00002cd0, 0x00044712, 0x000b9c55, 0x000c0a23 पूर्ण,
	अणु 136, 0x00002cd0, 0x0004471a, 0x000b9e55, 0x000c0a13 पूर्ण,

	/* 802.11 UNII */
	अणु 140, 0x00002cd0, 0x00044722, 0x000b9e55, 0x000c0a03 पूर्ण,
	अणु 149, 0x00002cd0, 0x0004472e, 0x000ba255, 0x000c0a1b पूर्ण,
	अणु 153, 0x00002cd0, 0x00044736, 0x000ba255, 0x000c0a0b पूर्ण,
	अणु 157, 0x00002cd4, 0x0004490a, 0x000ba255, 0x000c0a17 पूर्ण,
	अणु 161, 0x00002cd4, 0x00044912, 0x000ba255, 0x000c0a17 पूर्ण,
	अणु 165, 0x00002cd4, 0x0004491a, 0x000ba255, 0x000c0a17 पूर्ण,

	/* MMAC(Japan)J52 ch 34,38,42,46 */
	अणु 34, 0x00002ccc, 0x0000499a, 0x0009be55, 0x000c0a0b पूर्ण,
	अणु 38, 0x00002ccc, 0x0000499e, 0x0009be55, 0x000c0a13 पूर्ण,
	अणु 42, 0x00002ccc, 0x000049a2, 0x0009be55, 0x000c0a1b पूर्ण,
	अणु 46, 0x00002ccc, 0x000049a6, 0x0009be55, 0x000c0a23 पूर्ण,
पूर्ण;

अटल पूर्णांक rt61pci_probe_hw_mode(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	काष्ठा channel_info *info;
	अक्षर *tx_घातer;
	अचिन्हित पूर्णांक i;

	/*
	 * Disable घातersaving as शेष.
	 */
	rt2x00dev->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	/*
	 * Initialize all hw fields.
	 */
	ieee80211_hw_set(rt2x00dev->hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);
	ieee80211_hw_set(rt2x00dev->hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2x00_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * As rt61 has a global fallback table we cannot specअगरy
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
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	अगर (!rt2x00_has_cap_rf_sequence(rt2x00dev)) अणु
		spec->num_channels = 14;
		spec->channels = rf_vals_noseq;
	पूर्ण अन्यथा अणु
		spec->num_channels = 14;
		spec->channels = rf_vals_seq;
	पूर्ण

	अगर (rt2x00_rf(rt2x00dev, RF5225) || rt2x00_rf(rt2x00dev, RF5325)) अणु
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_seq);
	पूर्ण

	/*
	 * Create channel inक्रमmation array
	 */
	info = kसुस्मृति(spec->num_channels, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	spec->channels_info = info;

	tx_घातer = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_G_START);
	क्रम (i = 0; i < 14; i++) अणु
		info[i].max_घातer = MAX_TXPOWER;
		info[i].शेष_घातer1 = TXPOWER_FROM_DEV(tx_घातer[i]);
	पूर्ण

	अगर (spec->num_channels > 14) अणु
		tx_घातer = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_A_START);
		क्रम (i = 14; i < spec->num_channels; i++) अणु
			info[i].max_घातer = MAX_TXPOWER;
			info[i].शेष_घातer1 =
					TXPOWER_FROM_DEV(tx_घातer[i - 14]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt61pci_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;
	u32 reg;

	/*
	 * Disable घातer saving.
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, SOFT_RESET_CSR, 0x00000007);

	/*
	 * Allocate eeprom data.
	 */
	retval = rt61pci_validate_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	retval = rt61pci_init_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Enable rfसमाप्त polling by setting GPIO direction of the
	 * rfसमाप्त चयन GPIO pin correctly.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR13);
	rt2x00_set_field32(&reg, MAC_CSR13_सूची5, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, reg);

	/*
	 * Initialize hw specअगरications.
	 */
	retval = rt61pci_probe_hw_mode(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * This device has multiple filters क्रम control frames,
	 * but has no a separate filter क्रम PS Poll frames.
	 */
	__set_bit(CAPABILITY_CONTROL_FILTERS, &rt2x00dev->cap_flags);

	/*
	 * This device requires firmware and DMA mapped skbs.
	 */
	__set_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
	अगर (!modparam_nohwcrypt)
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	वापस 0;
पूर्ण

/*
 * IEEE80211 stack callback functions.
 */
अटल पूर्णांक rt61pci_conf_tx(काष्ठा ieee80211_hw *hw,
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
	 * क्रम WMM queues.
	 */
	अगर (queue_idx >= 4)
		वापस 0;

	queue = rt2x00queue_get_tx_queue(rt2x00dev, queue_idx);

	/* Update WMM TXOP रेजिस्टर */
	offset = AC_TXOP_CSR0 + (माप(u32) * (!!(queue_idx & 2)));
	field.bit_offset = (queue_idx & 1) * 16;
	field.bit_mask = 0xffff << field.bit_offset;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, field, queue->txop);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

	/* Update WMM रेजिस्टरs */
	field.bit_offset = queue_idx * 4;
	field.bit_mask = 0xf << field.bit_offset;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, AIFSN_CSR);
	rt2x00_set_field32(&reg, field, queue->aअगरs);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, AIFSN_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CWMIN_CSR);
	rt2x00_set_field32(&reg, field, queue->cw_min);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CWMIN_CSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CWMAX_CSR);
	rt2x00_set_field32(&reg, field, queue->cw_max);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CWMAX_CSR, reg);

	वापस 0;
पूर्ण

अटल u64 rt61pci_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u64 tsf;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR13);
	tsf = (u64) rt2x00_get_field32(reg, TXRX_CSR13_HIGH_TSFTIMER) << 32;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR12);
	tsf |= rt2x00_get_field32(reg, TXRX_CSR12_LOW_TSFTIMER);

	वापस tsf;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt61pci_mac80211_ops = अणु
	.tx			= rt2x00mac_tx,
	.start			= rt2x00mac_start,
	.stop			= rt2x00mac_stop,
	.add_पूर्णांकerface		= rt2x00mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rt2x00mac_हटाओ_पूर्णांकerface,
	.config			= rt2x00mac_config,
	.configure_filter	= rt2x00mac_configure_filter,
	.set_key		= rt2x00mac_set_key,
	.sw_scan_start		= rt2x00mac_sw_scan_start,
	.sw_scan_complete	= rt2x00mac_sw_scan_complete,
	.get_stats		= rt2x00mac_get_stats,
	.bss_info_changed	= rt2x00mac_bss_info_changed,
	.conf_tx		= rt61pci_conf_tx,
	.get_tsf		= rt61pci_get_tsf,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.flush			= rt2x00mac_flush,
	.set_antenna		= rt2x00mac_set_antenna,
	.get_antenna		= rt2x00mac_get_antenna,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt61pci_rt2x00_ops = अणु
	.irq_handler		= rt61pci_पूर्णांकerrupt,
	.txstatus_tasklet	= rt61pci_txstatus_tasklet,
	.tbtt_tasklet		= rt61pci_tbtt_tasklet,
	.rxकरोne_tasklet		= rt61pci_rxकरोne_tasklet,
	.स्वतःwake_tasklet	= rt61pci_स्वतःwake_tasklet,
	.probe_hw		= rt61pci_probe_hw,
	.get_firmware_name	= rt61pci_get_firmware_name,
	.check_firmware		= rt61pci_check_firmware,
	.load_firmware		= rt61pci_load_firmware,
	.initialize		= rt2x00mmio_initialize,
	.uninitialize		= rt2x00mmio_uninitialize,
	.get_entry_state	= rt61pci_get_entry_state,
	.clear_entry		= rt61pci_clear_entry,
	.set_device_state	= rt61pci_set_device_state,
	.rfसमाप्त_poll		= rt61pci_rfसमाप्त_poll,
	.link_stats		= rt61pci_link_stats,
	.reset_tuner		= rt61pci_reset_tuner,
	.link_tuner		= rt61pci_link_tuner,
	.start_queue		= rt61pci_start_queue,
	.kick_queue		= rt61pci_kick_queue,
	.stop_queue		= rt61pci_stop_queue,
	.flush_queue		= rt2x00mmio_flush_queue,
	.ग_लिखो_tx_desc		= rt61pci_ग_लिखो_tx_desc,
	.ग_लिखो_beacon		= rt61pci_ग_लिखो_beacon,
	.clear_beacon		= rt61pci_clear_beacon,
	.fill_rxकरोne		= rt61pci_fill_rxकरोne,
	.config_shared_key	= rt61pci_config_shared_key,
	.config_pairwise_key	= rt61pci_config_pairwise_key,
	.config_filter		= rt61pci_config_filter,
	.config_पूर्णांकf		= rt61pci_config_पूर्णांकf,
	.config_erp		= rt61pci_config_erp,
	.config_ant		= rt61pci_config_ant,
	.config			= rt61pci_config,
पूर्ण;

अटल व्योम rt61pci_queue_init(काष्ठा data_queue *queue)
अणु
	चयन (queue->qid) अणु
	हाल QID_RX:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_BEACON:
		queue->limit = 4;
		queue->data_size = 0; /* No DMA required क्रम beacons */
		queue->desc_size = TXINFO_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_ATIM:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rt2x00_ops rt61pci_ops = अणु
	.name			= KBUILD_MODNAME,
	.max_ap_पूर्णांकf		= 4,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt61pci_queue_init,
	.lib			= &rt61pci_rt2x00_ops,
	.hw			= &rt61pci_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt61pci_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * RT61pci module inक्रमmation.
 */
अटल स्थिर काष्ठा pci_device_id rt61pci_device_table[] = अणु
	/* RT2561s */
	अणु PCI_DEVICE(0x1814, 0x0301) पूर्ण,
	/* RT2561 v2 */
	अणु PCI_DEVICE(0x1814, 0x0302) पूर्ण,
	/* RT2661 */
	अणु PCI_DEVICE(0x1814, 0x0401) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT61 PCI & PCMCIA Wireless LAN driver.");
MODULE_DEVICE_TABLE(pci, rt61pci_device_table);
MODULE_FIRMWARE(FIRMWARE_RT2561);
MODULE_FIRMWARE(FIRMWARE_RT2561s);
MODULE_FIRMWARE(FIRMWARE_RT2661);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt61pci_probe(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस rt2x00pci_probe(pci_dev, &rt61pci_ops);
पूर्ण

अटल काष्ठा pci_driver rt61pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt61pci_device_table,
	.probe		= rt61pci_probe,
	.हटाओ		= rt2x00pci_हटाओ,
	.driver.pm	= &rt2x00pci_pm_ops,
पूर्ण;

module_pci_driver(rt61pci_driver);

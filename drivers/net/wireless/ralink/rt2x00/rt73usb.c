<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt73usb
	Abstract: rt73usb device specअगरic routines.
	Supported chipsets: rt2571W & rt2671.
 */

#समावेश <linux/crc-itu-t.h>
#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00usb.h"
#समावेश "rt73usb.h"

/*
 * Allow hardware encryption to be disabled.
 */
अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

/*
 * Register access.
 * All access to the CSR रेजिस्टरs will go through the methods
 * rt2x00usb_रेजिस्टर_पढ़ो and rt2x00usb_रेजिस्टर_ग_लिखो.
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
	rt2x00usb_regbusy_पढ़ो((__dev), PHY_CSR3, PHY_CSR3_BUSY, (__reg))
#घोषणा WAIT_FOR_RF(__dev, __reg) \
	rt2x00usb_regbusy_पढ़ो((__dev), PHY_CSR4, PHY_CSR4_BUSY, (__reg))

अटल व्योम rt73usb_bbp_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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

		rt2x00usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR3, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल u8 rt73usb_bbp_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
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

		rt2x00usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR3, reg);

		WAIT_FOR_BBP(rt2x00dev, &reg);
	पूर्ण

	value = rt2x00_get_field32(reg, PHY_CSR3_VALUE);

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल व्योम rt73usb_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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
		/*
		 * RF5225 and RF2527 contain 21 bits per RF रेजिस्टर value,
		 * all others contain 20 bits.
		 */
		rt2x00_set_field32(&reg, PHY_CSR4_NUMBER_OF_BITS,
				   20 + (rt2x00_rf(rt2x00dev, RF5225) ||
					 rt2x00_rf(rt2x00dev, RF2527)));
		rt2x00_set_field32(&reg, PHY_CSR4_IF_SELECT, 0);
		rt2x00_set_field32(&reg, PHY_CSR4_BUSY, 1);

		rt2x00usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR4, reg);
		rt2x00_rf_ग_लिखो(rt2x00dev, word, value);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
अटल स्थिर काष्ठा rt2x00debug rt73usb_rt2x00debug = अणु
	.owner	= THIS_MODULE,
	.csr	= अणु
		.पढ़ो		= rt2x00usb_रेजिस्टर_पढ़ो,
		.ग_लिखो		= rt2x00usb_रेजिस्टर_ग_लिखो,
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
		.पढ़ो		= rt73usb_bbp_पढ़ो,
		.ग_लिखो		= rt73usb_bbp_ग_लिखो,
		.word_base	= BBP_BASE,
		.word_size	= माप(u8),
		.word_count	= BBP_SIZE / माप(u8),
	पूर्ण,
	.rf	= अणु
		.पढ़ो		= rt2x00_rf_पढ़ो,
		.ग_लिखो		= rt73usb_rf_ग_लिखो,
		.word_base	= RF_BASE,
		.word_size	= माप(u32),
		.word_count	= RF_SIZE / माप(u32),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

अटल पूर्णांक rt73usb_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR13);
	वापस rt2x00_get_field32(reg, MAC_CSR13_VAL7);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
अटल व्योम rt73usb_brightness_set(काष्ठा led_classdev *led_cdev,
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

		rt2x00usb_venकरोr_request_sw(led->rt2x00dev, USB_LED_CONTROL,
					    0, led->rt2x00dev->led_mcu_reg,
					    REGISTER_TIMEOUT);
	पूर्ण अन्यथा अगर (led->type == LED_TYPE_ASSOC) अणु
		rt2x00_set_field16(&led->rt2x00dev->led_mcu_reg,
				   MCU_LEDCS_LINK_BG_STATUS, bg_mode);
		rt2x00_set_field16(&led->rt2x00dev->led_mcu_reg,
				   MCU_LEDCS_LINK_A_STATUS, a_mode);

		rt2x00usb_venकरोr_request_sw(led->rt2x00dev, USB_LED_CONTROL,
					    0, led->rt2x00dev->led_mcu_reg,
					    REGISTER_TIMEOUT);
	पूर्ण अन्यथा अगर (led->type == LED_TYPE_QUALITY) अणु
		/*
		 * The brightness is भागided पूर्णांकo 6 levels (0 - 5),
		 * this means we need to convert the brightness
		 * argument पूर्णांकo the matching level within that range.
		 */
		rt2x00usb_venकरोr_request_sw(led->rt2x00dev, USB_LED_CONTROL,
					    brightness / (LED_FULL / 6),
					    led->rt2x00dev->led_mcu_reg,
					    REGISTER_TIMEOUT);
	पूर्ण
पूर्ण

अटल पूर्णांक rt73usb_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on,
			     अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(led->rt2x00dev, MAC_CSR14);
	rt2x00_set_field32(&reg, MAC_CSR14_ON_PERIOD, *delay_on);
	rt2x00_set_field32(&reg, MAC_CSR14_OFF_PERIOD, *delay_off);
	rt2x00usb_रेजिस्टर_ग_लिखो(led->rt2x00dev, MAC_CSR14, reg);

	वापस 0;
पूर्ण

अटल व्योम rt73usb_init_led(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00_led *led,
			     क्रमागत led_type type)
अणु
	led->rt2x00dev = rt2x00dev;
	led->type = type;
	led->led_dev.brightness_set = rt73usb_brightness_set;
	led->led_dev.blink_set = rt73usb_blink_set;
	led->flags = LED_INITIALIZED;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

/*
 * Configuration handlers.
 */
अटल पूर्णांक rt73usb_config_shared_key(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा rt2x00lib_crypto *crypto,
				     काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा hw_key_entry key_entry;
	काष्ठा rt2x00_field32 field;
	u32 mask;
	u32 reg;

	अगर (crypto->cmd == SET_KEY) अणु
		/*
		 * rt2x00lib can't determine the correct मुक्त
		 * key_idx क्रम shared keys. We have 1 रेजिस्टर
		 * with key valid bits. The goal is simple, पढ़ो
		 * the रेजिस्टर, अगर that is full we have no slots
		 * left.
		 * Note that each BSS is allowed to have up to 4
		 * shared keys, so put a mask over the allowed
		 * entries.
		 */
		mask = (0xf << crypto->bssidx);

		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR0);
		reg &= mask;

		अगर (reg && reg == mask)
			वापस -ENOSPC;

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

		reg = SHARED_KEY_ENTRY(key->hw_key_idx);
		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, reg,
					      &key_entry, माप(key_entry));

		/*
		 * The cipher types are stored over 2 रेजिस्टरs.
		 * bssidx 0 and 1 keys are stored in SEC_CSR1 and
		 * bssidx 1 and 2 keys are stored in SEC_CSR5.
		 * Using the correct defines correctly will cause overhead,
		 * so just calculate the correct offset.
		 */
		अगर (key->hw_key_idx < 8) अणु
			field.bit_offset = (3 * key->hw_key_idx);
			field.bit_mask = 0x7 << field.bit_offset;

			reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR1);
			rt2x00_set_field32(&reg, field, crypto->cipher);
			rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR1, reg);
		पूर्ण अन्यथा अणु
			field.bit_offset = (3 * (key->hw_key_idx - 8));
			field.bit_mask = 0x7 << field.bit_offset;

			reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR5);
			rt2x00_set_field32(&reg, field, crypto->cipher);
			rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR5, reg);
		पूर्ण

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
	 * SEC_CSR0 contains only single-bit fields to indicate
	 * a particular key is valid. Because using the FIELD32()
	 * defines directly will cause a lot of overhead we use
	 * a calculation to determine the correct bit directly.
	 */
	mask = 1 << key->hw_key_idx;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR0);
	अगर (crypto->cmd == SET_KEY)
		reg |= mask;
	अन्यथा अगर (crypto->cmd == DISABLE_KEY)
		reg &= ~mask;
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR0, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt73usb_config_pairwise_key(काष्ठा rt2x00_dev *rt2x00dev,
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
		 * with key valid bits. The goal is simple, पढ़ो
		 * the first रेजिस्टर, अगर that is full move to
		 * the next रेजिस्टर.
		 * When both रेजिस्टरs are full, we drop the key,
		 * otherwise we use the first invalid entry.
		 */
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR2);
		अगर (reg && reg == ~0) अणु
			key->hw_key_idx = 32;
			reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR3);
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

		reg = PAIRWISE_KEY_ENTRY(key->hw_key_idx);
		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, reg,
					      &key_entry, माप(key_entry));

		/*
		 * Send the address and cipher type to the hardware रेजिस्टर.
		 */
		स_रखो(&addr_entry, 0, माप(addr_entry));
		स_नकल(&addr_entry, crypto->address, ETH_ALEN);
		addr_entry.cipher = crypto->cipher;

		reg = PAIRWISE_TA_ENTRY(key->hw_key_idx);
		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, reg,
					    &addr_entry, माप(addr_entry));

		/*
		 * Enable pairwise lookup table क्रम given BSS idx,
		 * without this received frames will not be decrypted
		 * by the hardware.
		 */
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR4);
		reg |= (1 << crypto->bssidx);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR4, reg);

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
	 * defines directly will cause a lot of overhead we use
	 * a calculation to determine the correct bit directly.
	 */
	अगर (key->hw_key_idx < 32) अणु
		mask = 1 << key->hw_key_idx;

		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR2);
		अगर (crypto->cmd == SET_KEY)
			reg |= mask;
		अन्यथा अगर (crypto->cmd == DISABLE_KEY)
			reg &= ~mask;
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR2, reg);
	पूर्ण अन्यथा अणु
		mask = 1 << (key->hw_key_idx - 32);

		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, SEC_CSR3);
		अगर (crypto->cmd == SET_KEY)
			reg |= mask;
		अन्यथा अगर (crypto->cmd == DISABLE_KEY)
			reg &= ~mask;
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR3, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt73usb_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर अचिन्हित पूर्णांक filter_flags)
अणु
	u32 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * and broadcast frames will always be accepted since
	 * there is no filter क्रम it at this समय.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
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
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
पूर्ण

अटल व्योम rt73usb_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
				काष्ठा rt2x00पूर्णांकf_conf *conf,
				स्थिर अचिन्हित पूर्णांक flags)
अणु
	u32 reg;

	अगर (flags & CONFIG_UPDATE_TYPE) अणु
		/*
		 * Enable synchronisation.
		 */
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_SYNC, conf->sync);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
	पूर्ण

	अगर (flags & CONFIG_UPDATE_MAC) अणु
		reg = le32_to_cpu(conf->mac[1]);
		rt2x00_set_field32(&reg, MAC_CSR3_UNICAST_TO_ME_MASK, 0xff);
		conf->mac[1] = cpu_to_le32(reg);

		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR2,
					    conf->mac, माप(conf->mac));
	पूर्ण

	अगर (flags & CONFIG_UPDATE_BSSID) अणु
		reg = le32_to_cpu(conf->bssid[1]);
		rt2x00_set_field32(&reg, MAC_CSR5_BSS_ID_MASK, 3);
		conf->bssid[1] = cpu_to_le32(reg);

		rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR4,
					    conf->bssid, माप(conf->bssid));
	पूर्ण
पूर्ण

अटल व्योम rt73usb_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00lib_erp *erp,
			       u32 changed)
अणु
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field32(&reg, TXRX_CSR0_RX_ACK_TIMEOUT, 0x32);
	rt2x00_set_field32(&reg, TXRX_CSR0_TSF_OFFSET, IEEE80211_HEADER);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR4);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR4_AUTORESPOND_PREAMBLE,
				   !!erp->लघु_preamble);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR4, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR5,
					 erp->basic_rates);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_INTERVAL,
				   erp->beacon_पूर्णांक * 16);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR9);
		rt2x00_set_field32(&reg, MAC_CSR9_SLOT_TIME, erp->slot_समय);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR9, reg);

		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR8);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS, erp->sअगरs);
		rt2x00_set_field32(&reg, MAC_CSR8_SIFS_AFTER_RX_OFDM, 3);
		rt2x00_set_field32(&reg, MAC_CSR8_EIFS, erp->eअगरs);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR8, reg);
	पूर्ण
पूर्ण

अटल व्योम rt73usb_config_antenna_5x(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा antenna_setup *ant)
अणु
	u8 r3;
	u8 r4;
	u8 r77;
	u8 temp;

	r3 = rt73usb_bbp_पढ़ो(rt2x00dev, 3);
	r4 = rt73usb_bbp_पढ़ो(rt2x00dev, 4);
	r77 = rt73usb_bbp_पढ़ो(rt2x00dev, 77);

	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, 0);

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 2);
		temp = !rt2x00_has_cap_frame_type(rt2x00dev) &&
		       (rt2x00dev->curr_band != NL80211_BAND_5GHZ);
		rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END, temp);
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

	rt73usb_bbp_ग_लिखो(rt2x00dev, 77, r77);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 4, r4);
पूर्ण

अटल व्योम rt73usb_config_antenna_2x(काष्ठा rt2x00_dev *rt2x00dev,
				      काष्ठा antenna_setup *ant)
अणु
	u8 r3;
	u8 r4;
	u8 r77;

	r3 = rt73usb_bbp_पढ़ो(rt2x00dev, 3);
	r4 = rt73usb_bbp_पढ़ो(rt2x00dev, 4);
	r77 = rt73usb_bbp_पढ़ो(rt2x00dev, 77);

	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, 0);
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
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		अवरोध;
	पूर्ण

	rt73usb_bbp_ग_लिखो(rt2x00dev, 77, r77);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 3, r3);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 4, r4);
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

अटल व्योम rt73usb_config_ant(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt73usb_bbp_ग_लिखो(rt2x00dev, sel[i].word, sel[i].value[lna]);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR0);

	rt2x00_set_field32(&reg, PHY_CSR0_PA_PE_BG,
			   (rt2x00dev->curr_band == NL80211_BAND_2GHZ));
	rt2x00_set_field32(&reg, PHY_CSR0_PA_PE_A,
			   (rt2x00dev->curr_band == NL80211_BAND_5GHZ));

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR0, reg);

	अगर (rt2x00_rf(rt2x00dev, RF5226) || rt2x00_rf(rt2x00dev, RF5225))
		rt73usb_config_antenna_5x(rt2x00dev, ant);
	अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2528) || rt2x00_rf(rt2x00dev, RF2527))
		rt73usb_config_antenna_2x(rt2x00dev, ant);
पूर्ण

अटल व्योम rt73usb_config_lna_gain(काष्ठा rt2x00_dev *rt2x00dev,
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
		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_RSSI_OFFSET_A);
		lna_gain -= rt2x00_get_field16(eeprom, EEPROM_RSSI_OFFSET_A_1);
	पूर्ण

	rt2x00dev->lna_gain = lna_gain;
पूर्ण

अटल व्योम rt73usb_config_channel(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा rf_channel *rf, स्थिर पूर्णांक txघातer)
अणु
	u8 r3;
	u8 r94;
	u8 smart;

	rt2x00_set_field32(&rf->rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txघातer));
	rt2x00_set_field32(&rf->rf4, RF4_FREQ_OFFSET, rt2x00dev->freq_offset);

	smart = !(rt2x00_rf(rt2x00dev, RF5225) || rt2x00_rf(rt2x00dev, RF2527));

	r3 = rt73usb_bbp_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, smart);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 3, r3);

	r94 = 6;
	अगर (txघातer > MAX_TXPOWER && txघातer <= (MAX_TXPOWER + r94))
		r94 += txघातer - MAX_TXPOWER;
	अन्यथा अगर (txघातer < MIN_TXPOWER && txघातer >= (MIN_TXPOWER - r94))
		r94 += txघातer;
	rt73usb_bbp_ग_लिखो(rt2x00dev, 94, r94);

	rt73usb_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt73usb_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt73usb_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt73usb_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	rt73usb_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt73usb_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt73usb_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 | 0x00000004);
	rt73usb_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	rt73usb_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt73usb_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt73usb_rf_ग_लिखो(rt2x00dev, 3, rf->rf3 & ~0x00000004);
	rt73usb_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);

	udelay(10);
पूर्ण

अटल व्योम rt73usb_config_txघातer(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर पूर्णांक txघातer)
अणु
	काष्ठा rf_channel rf;

	rf.rf1 = rt2x00_rf_पढ़ो(rt2x00dev, 1);
	rf.rf2 = rt2x00_rf_पढ़ो(rt2x00dev, 2);
	rf.rf3 = rt2x00_rf_पढ़ो(rt2x00dev, 3);
	rf.rf4 = rt2x00_rf_पढ़ो(rt2x00dev, 4);

	rt73usb_config_channel(rt2x00dev, &rf, txघातer);
पूर्ण

अटल व्योम rt73usb_config_retry_limit(काष्ठा rt2x00_dev *rt2x00dev,
				       काष्ठा rt2x00lib_conf *libconf)
अणु
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR4);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_RATE_DOWN, 1);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_RATE_STEP, 0);
	rt2x00_set_field32(&reg, TXRX_CSR4_OFDM_TX_FALLBACK_CCK, 0);
	rt2x00_set_field32(&reg, TXRX_CSR4_LONG_RETRY_LIMIT,
			   libconf->conf->दीर्घ_frame_max_tx_count);
	rt2x00_set_field32(&reg, TXRX_CSR4_SHORT_RETRY_LIMIT,
			   libconf->conf->लघु_frame_max_tx_count);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR4, reg);
पूर्ण

अटल व्योम rt73usb_config_ps(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00lib_conf *libconf)
अणु
	क्रमागत dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	अगर (state == STATE_SLEEP) अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR11);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN,
				   rt2x00dev->beacon_पूर्णांक - 10);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_पूर्णांकerval - 1);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 5);

		/* We must first disable स्वतःwake beक्रमe it can be enabled */
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 1);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
					    USB_MODE_SLEEP, REGISTER_TIMEOUT);
	पूर्ण अन्यथा अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR11);
		rt2x00_set_field32(&reg, MAC_CSR11_DELAY_AFTER_TBCN, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_TBCN_BEFORE_WAKEUP, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_AUTOWAKE, 0);
		rt2x00_set_field32(&reg, MAC_CSR11_WAKEUP_LATENCY, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, reg);

		rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE, 0,
					    USB_MODE_WAKEUP, REGISTER_TIMEOUT);
	पूर्ण
पूर्ण

अटल व्योम rt73usb_config(काष्ठा rt2x00_dev *rt2x00dev,
			   काष्ठा rt2x00lib_conf *libconf,
			   स्थिर अचिन्हित पूर्णांक flags)
अणु
	/* Always recalculate LNA gain beक्रमe changing configuration */
	rt73usb_config_lna_gain(rt2x00dev, libconf);

	अगर (flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt73usb_config_channel(rt2x00dev, &libconf->rf,
				       libconf->conf->घातer_level);
	अगर ((flags & IEEE80211_CONF_CHANGE_POWER) &&
	    !(flags & IEEE80211_CONF_CHANGE_CHANNEL))
		rt73usb_config_txघातer(rt2x00dev, libconf->conf->घातer_level);
	अगर (flags & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		rt73usb_config_retry_limit(rt2x00dev, libconf);
	अगर (flags & IEEE80211_CONF_CHANGE_PS)
		rt73usb_config_ps(rt2x00dev, libconf);
पूर्ण

/*
 * Link tuning
 */
अटल व्योम rt73usb_link_stats(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा link_qual *qual)
अणु
	u32 reg;

	/*
	 * Update FCS error count from रेजिस्टर.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR0);
	qual->rx_failed = rt2x00_get_field32(reg, STA_CSR0_FCS_ERROR);

	/*
	 * Update False CCA count from रेजिस्टर.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR1);
	qual->false_cca = rt2x00_get_field32(reg, STA_CSR1_FALSE_CCA_ERROR);
पूर्ण

अटल अंतरभूत व्योम rt73usb_set_vgc(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा link_qual *qual, u8 vgc_level)
अणु
	अगर (qual->vgc_level != vgc_level) अणु
		rt73usb_bbp_ग_लिखो(rt2x00dev, 17, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	पूर्ण
पूर्ण

अटल व्योम rt73usb_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा link_qual *qual)
अणु
	rt73usb_set_vgc(rt2x00dev, qual, 0x20);
पूर्ण

अटल व्योम rt73usb_link_tuner(काष्ठा rt2x00_dev *rt2x00dev,
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
		अगर (qual->rssi > -82) अणु
			low_bound = 0x1c;
			up_bound = 0x40;
		पूर्ण अन्यथा अगर (qual->rssi > -84) अणु
			low_bound = 0x1c;
			up_bound = 0x20;
		पूर्ण अन्यथा अणु
			low_bound = 0x1c;
			up_bound = 0x1c;
		पूर्ण

		अगर (rt2x00_has_cap_बाह्यal_lna_bg(rt2x00dev)) अणु
			low_bound += 0x14;
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
	अगर (qual->rssi > -35) अणु
		rt73usb_set_vgc(rt2x00dev, qual, 0x60);
		वापस;
	पूर्ण

	/*
	 * Special big-R17 क्रम लघु distance
	 */
	अगर (qual->rssi >= -58) अणु
		rt73usb_set_vgc(rt2x00dev, qual, up_bound);
		वापस;
	पूर्ण

	/*
	 * Special big-R17 क्रम middle-लघु distance
	 */
	अगर (qual->rssi >= -66) अणु
		rt73usb_set_vgc(rt2x00dev, qual, low_bound + 0x10);
		वापस;
	पूर्ण

	/*
	 * Special mid-R17 क्रम middle distance
	 */
	अगर (qual->rssi >= -74) अणु
		rt73usb_set_vgc(rt2x00dev, qual, low_bound + 0x08);
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
		rt73usb_set_vgc(rt2x00dev, qual, up_bound);
		वापस;
	पूर्ण

dynamic_cca_tune:

	/*
	 * r17 करोes not yet exceed upper limit, जारी and base
	 * the r17 tuning on the false CCA count.
	 */
	अगर ((qual->false_cca > 512) && (qual->vgc_level < up_bound))
		rt73usb_set_vgc(rt2x00dev, qual,
				min_t(u8, qual->vgc_level + 4, up_bound));
	अन्यथा अगर ((qual->false_cca < 100) && (qual->vgc_level > low_bound))
		rt73usb_set_vgc(rt2x00dev, qual,
				max_t(u8, qual->vgc_level - 4, low_bound));
पूर्ण

/*
 * Queue handlers.
 */
अटल व्योम rt73usb_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt73usb_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 1);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 0);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 0);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Firmware functions
 */
अटल अक्षर *rt73usb_get_firmware_name(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	वापस FIRMWARE_RT2571;
पूर्ण

अटल पूर्णांक rt73usb_check_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	u16 fw_crc;
	u16 crc;

	/*
	 * Only support 2kb firmware files.
	 */
	अगर (len != 2048)
		वापस FW_BAD_LENGTH;

	/*
	 * The last 2 bytes in the firmware array are the crc checksum itself,
	 * this means that we should never pass those 2 bytes to the crc
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

अटल पूर्णांक rt73usb_load_firmware(काष्ठा rt2x00_dev *rt2x00dev,
				 स्थिर u8 *data, स्थिर माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक status;
	u32 reg;

	/*
	 * Wait क्रम stable hardware.
	 */
	क्रम (i = 0; i < 100; i++) अणु
		reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
		अगर (reg)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (!reg) अणु
		rt2x00_err(rt2x00dev, "Unstable hardware\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Write firmware to device.
	 */
	rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, FIRMWARE_IMAGE_BASE, data, len);

	/*
	 * Send firmware request to device to load firmware,
	 * we need to specअगरy a दीर्घ समयout समय.
	 */
	status = rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE,
					     0, USB_MODE_FIRMWARE,
					     REGISTER_TIMEOUT_FIRMWARE);
	अगर (status < 0) अणु
		rt2x00_err(rt2x00dev, "Failed to write Firmware to device\n");
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialization functions.
 */
अटल पूर्णांक rt73usb_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field32(&reg, TXRX_CSR0_AUTO_TX_SEQ, 1);
	rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
	rt2x00_set_field32(&reg, TXRX_CSR0_TX_WITHOUT_WAITING, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID0, 47); /* CCK Signal */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID1, 30); /* Rssi */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID2, 42); /* OFDM Rate */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID2_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID3, 30); /* Rssi */
	rt2x00_set_field32(&reg, TXRX_CSR1_BBP_ID3_VALID, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR1, reg);

	/*
	 * CCK TXD BBP रेजिस्टरs
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID0, 13);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID1, 12);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID2, 11);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID2_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID3, 10);
	rt2x00_set_field32(&reg, TXRX_CSR2_BBP_ID3_VALID, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);

	/*
	 * OFDM TXD BBP रेजिस्टरs
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR3);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID0, 7);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID1, 6);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID2, 5);
	rt2x00_set_field32(&reg, TXRX_CSR3_BBP_ID2_VALID, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR3, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR7);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_6MBS, 59);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_9MBS, 53);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_12MBS, 49);
	rt2x00_set_field32(&reg, TXRX_CSR7_ACK_CTS_18MBS, 46);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR7, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR8);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_24MBS, 44);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_36MBS, 42);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_48MBS, 42);
	rt2x00_set_field32(&reg, TXRX_CSR8_ACK_CTS_54MBS, 42);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR8, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_INTERVAL, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, TXRX_CSR9_TIMESTAMP_COMPENSATE, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR15, 0x0000000f);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR6);
	rt2x00_set_field32(&reg, MAC_CSR6_MAX_FRAME_UNIT, 0xfff);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR6, reg);

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR10, 0x00000718);

	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		वापस -EBUSY;

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, 0x00007f00);

	/*
	 * Invalidate all Shared Keys (SEC_CSR0),
	 * and clear the Shared key Cipher algorithms (SEC_CSR1 & SEC_CSR5)
	 */
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR0, 0x00000000);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR1, 0x00000000);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, SEC_CSR5, 0x00000000);

	reg = 0x000023b0;
	अगर (rt2x00_rf(rt2x00dev, RF5225) || rt2x00_rf(rt2x00dev, RF2527))
		rt2x00_set_field32(&reg, PHY_CSR1_RF_RPI, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR1, reg);

	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR5, 0x00040a06);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR6, 0x00080606);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR7, 0x00000408);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR9);
	rt2x00_set_field32(&reg, MAC_CSR9_CW_SELECT, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR9, reg);

	/*
	 * Clear all beacons
	 * For the Beacon base रेजिस्टरs we only need to clear
	 * the first byte since that byte contains the VALID and OWNER
	 * bits which (when set to 0) will invalidate the entire beacon.
	 */
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE0, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE1, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE2, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, HW_BEACON_BASE3, 0);

	/*
	 * We must clear the error counters.
	 * These रेजिस्टरs are cleared on पढ़ो,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR0);
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR1);
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR2);

	/*
	 * Reset MAC and BBP रेजिस्टरs.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field32(&reg, MAC_CSR1_HOST_READY, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt73usb_रुको_bbp_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u8 value;

	क्रम (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) अणु
		value = rt73usb_bbp_पढ़ो(rt2x00dev, 0);
		अगर ((value != 0xff) && (value != 0x00))
			वापस 0;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल पूर्णांक rt73usb_init_bbp(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	अगर (unlikely(rt73usb_रुको_bbp_पढ़ोy(rt2x00dev)))
		वापस -EACCES;

	rt73usb_bbp_ग_लिखो(rt2x00dev, 3, 0x80);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 15, 0x30);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 21, 0xc8);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 22, 0x38);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 23, 0x06);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 24, 0xfe);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 25, 0x0a);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 26, 0x0d);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 32, 0x0b);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 34, 0x12);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 37, 0x07);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 39, 0xf8);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 41, 0x60);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 53, 0x10);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 54, 0x18);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 60, 0x10);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 61, 0x04);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 62, 0x04);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 75, 0xfe);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 86, 0xfe);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 88, 0xfe);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 90, 0x0f);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 99, 0x00);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 102, 0x16);
	rt73usb_bbp_ग_लिखो(rt2x00dev, 107, 0x04);

	क्रम (i = 0; i < EEPROM_BBP_SIZE; i++) अणु
		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBP_START + i);

		अगर (eeprom != 0xffff && eeprom != 0x0000) अणु
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt73usb_bbp_ग_लिखो(rt2x00dev, reg_id, value);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल पूर्णांक rt73usb_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Initialize all रेजिस्टरs.
	 */
	अगर (unlikely(rt73usb_init_रेजिस्टरs(rt2x00dev) ||
		     rt73usb_init_bbp(rt2x00dev)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम rt73usb_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR10, 0x00001818);

	/*
	 * Disable synchronisation.
	 */
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, 0);

	rt2x00usb_disable_radio(rt2x00dev);
पूर्ण

अटल पूर्णांक rt73usb_set_state(काष्ठा rt2x00_dev *rt2x00dev, क्रमागत dev_state state)
अणु
	u32 reg, reg2;
	अचिन्हित पूर्णांक i;
	अक्षर put_to_sleep;

	put_to_sleep = (state != STATE_AWAKE);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR12);
	rt2x00_set_field32(&reg, MAC_CSR12_FORCE_WAKEUP, !put_to_sleep);
	rt2x00_set_field32(&reg, MAC_CSR12_PUT_TO_SLEEP, put_to_sleep);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR12, reg);

	/*
	 * Device is not guaranteed to be in the requested state yet.
	 * We must रुको until the रेजिस्टर indicates that the
	 * device has entered the correct state.
	 */
	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg2 = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR12);
		state = rt2x00_get_field32(reg2, MAC_CSR12_BBP_CURRENT_STATE);
		अगर (state == !put_to_sleep)
			वापस 0;
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR12, reg);
		msleep(10);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rt73usb_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				    क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt73usb_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		rt73usb_disable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		/* No support, but no error either */
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt73usb_set_state(rt2x00dev, state);
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
अटल व्योम rt73usb_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
				  काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *txd = (__le32 *) entry->skb->data;
	u32 word;

	/*
	 * Start writing the descriptor words.
	 */
	word = rt2x00_desc_पढ़ो(txd, 0);
	rt2x00_set_field32(&word, TXD_W0_BURST,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
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
	rt2x00_set_field32(&word, TXD_W0_BURST2,
			   test_bit(ENTRY_TXD_BURST, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_CIPHER_ALG, txdesc->cipher);
	rt2x00_desc_ग_लिखो(txd, 0, word);

	word = rt2x00_desc_पढ़ो(txd, 1);
	rt2x00_set_field32(&word, TXD_W1_HOST_Q_ID, entry->queue->qid);
	rt2x00_set_field32(&word, TXD_W1_AIFSN, entry->queue->aअगरs);
	rt2x00_set_field32(&word, TXD_W1_CWMIN, entry->queue->cw_min);
	rt2x00_set_field32(&word, TXD_W1_CWMAX, entry->queue->cw_max);
	rt2x00_set_field32(&word, TXD_W1_IV_OFFSET, txdesc->iv_offset);
	rt2x00_set_field32(&word, TXD_W1_HW_SEQUENCE,
			   test_bit(ENTRY_TXD_GENERATE_SEQ, &txdesc->flags));
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
	rt2x00_set_field32(&word, TXD_W5_TX_POWER,
			   TXPOWER_TO_DEV(entry->queue->rt2x00dev->tx_घातer));
	rt2x00_set_field32(&word, TXD_W5_WAITING_DMA_DONE_INT, 1);
	rt2x00_desc_ग_लिखो(txd, 5, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->flags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = txd;
	skbdesc->desc_len = TXD_DESC_SIZE;
पूर्ण

/*
 * TX data initialization
 */
अटल व्योम rt73usb_ग_लिखो_beacon(काष्ठा queue_entry *entry,
				 काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	अचिन्हित पूर्णांक beacon_base;
	अचिन्हित पूर्णांक padding_len;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	orig_reg = reg;
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Add space क्रम the descriptor in front of the skb.
	 */
	skb_push(entry->skb, TXD_DESC_SIZE);
	स_रखो(entry->skb->data, 0, TXD_DESC_SIZE);

	/*
	 * Write the TX descriptor क्रम the beacon.
	 */
	rt73usb_ग_लिखो_tx_desc(entry, txdesc);

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
		rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, orig_reg);
		वापस;
	पूर्ण

	beacon_base = HW_BEACON_OFFSET(entry->entry_idx);
	rt2x00usb_रेजिस्टर_multiग_लिखो(rt2x00dev, beacon_base, entry->skb->data,
				      entry->skb->len + padding_len);

	/*
	 * Enable beaconing again.
	 *
	 * For Wi-Fi faily generated beacons between participating stations.
	 * Set TBTT phase adaptive adjusपंचांगent step to 8us (शेष 16us)
	 */
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR10, 0x00001008);

	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Clean up the beacon skb.
	 */
	dev_kमुक्त_skb(entry->skb);
	entry->skb = शून्य;
पूर्ण

अटल व्योम rt73usb_clear_beacon(काष्ठा queue_entry *entry)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	अचिन्हित पूर्णांक beacon_base;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	orig_reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR9);
	reg = orig_reg;
	rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, reg);

	/*
	 * Clear beacon.
	 */
	beacon_base = HW_BEACON_OFFSET(entry->entry_idx);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, beacon_base, 0);

	/*
	 * Restore beaconing state.
	 */
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR9, orig_reg);
पूर्ण

अटल पूर्णांक rt73usb_get_tx_data_len(काष्ठा queue_entry *entry)
अणु
	पूर्णांक length;

	/*
	 * The length _must_ be a multiple of 4,
	 * but it must _not_ be a multiple of the USB packet size.
	 */
	length = roundup(entry->skb->len, 4);
	length += (4 * !(length % entry->queue->usb_maxpacket));

	वापस length;
पूर्ण

/*
 * RX control handlers
 */
अटल पूर्णांक rt73usb_agc_to_rssi(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक rxd_w1)
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
		अगर (rt2x00_has_cap_बाह्यal_lna_a(rt2x00dev)) अणु
			अगर (lna == 3 || lna == 2)
				offset += 10;
		पूर्ण अन्यथा अणु
			अगर (lna == 3)
				offset += 6;
			अन्यथा अगर (lna == 2)
				offset += 8;
		पूर्ण
	पूर्ण

	वापस rt2x00_get_field32(rxd_w1, RXD_W1_RSSI_AGC) * 2 - offset;
पूर्ण

अटल व्योम rt73usb_fill_rxकरोne(काष्ठा queue_entry *entry,
				काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *rxd = (__le32 *)entry->skb->data;
	u32 word0;
	u32 word1;

	/*
	 * Copy descriptor to the skbdesc->desc buffer, making it safe from moving of
	 * frame data in rt2x00usb.
	 */
	स_नकल(skbdesc->desc, rxd, skbdesc->desc_len);
	rxd = (__le32 *)skbdesc->desc;

	/*
	 * It is now safe to पढ़ो the descriptor on all architectures.
	 */
	word0 = rt2x00_desc_पढ़ो(rxd, 0);
	word1 = rt2x00_desc_पढ़ो(rxd, 1);

	अगर (rt2x00_get_field32(word0, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;

	rxdesc->cipher = rt2x00_get_field32(word0, RXD_W0_CIPHER_ALG);
	rxdesc->cipher_status = rt2x00_get_field32(word0, RXD_W0_CIPHER_ERROR);

	अगर (rxdesc->cipher != CIPHER_NONE) अणु
		rxdesc->iv[0] = _rt2x00_desc_पढ़ो(rxd, 2);
		rxdesc->iv[1] = _rt2x00_desc_पढ़ो(rxd, 3);
		rxdesc->dev_flags |= RXDONE_CRYPTO_IV;

		rxdesc->icv = _rt2x00_desc_पढ़ो(rxd, 4);
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
	rxdesc->rssi = rt73usb_agc_to_rssi(rt2x00dev, word1);
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	अगर (rt2x00_get_field32(word0, RXD_W0_OFDM))
		rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	अन्यथा
		rxdesc->dev_flags |= RXDONE_SIGNAL_BITRATE;
	अगर (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	/*
	 * Set skb poपूर्णांकers, and update frame inक्रमmation.
	 */
	skb_pull(entry->skb, entry->queue->desc_size);
	skb_trim(entry->skb, rxdesc->size);
पूर्ण

/*
 * Device probe functions.
 */
अटल पूर्णांक rt73usb_validate_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 word;
	u8 *mac;
	s8 value;

	rt2x00usb_eeprom_पढ़ो(rt2x00dev, rt2x00dev->eeprom, EEPROM_SIZE);

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
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RF_TYPE, RF5226);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_ANTENNA, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_NIC_EXTERNAL_LNA, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_LED);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_RDY_G, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_RDY_A, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_ACT, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_GPIO_0, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_GPIO_1, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_GPIO_2, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_GPIO_3, 0);
		rt2x00_set_field16(&word, EEPROM_LED_POLARITY_GPIO_4, 0);
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

अटल पूर्णांक rt73usb_init_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
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
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
	rt2x00_set_chip(rt2x00dev, rt2x00_get_field32(reg, MAC_CSR0_CHIPSET),
			value, rt2x00_get_field32(reg, MAC_CSR0_REVISION));

	अगर (!rt2x00_rt(rt2x00dev, RT2573) || (rt2x00_rev(rt2x00dev) == 0)) अणु
		rt2x00_err(rt2x00dev, "Invalid RT chipset detected\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!rt2x00_rf(rt2x00dev, RF5226) &&
	    !rt2x00_rf(rt2x00dev, RF2528) &&
	    !rt2x00_rf(rt2x00dev, RF5225) &&
	    !rt2x00_rf(rt2x00dev, RF2527)) अणु
		rt2x00_err(rt2x00dev, "Invalid RF chipset detected\n");
		वापस -ENODEV;
	पूर्ण

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
	 * Detect अगर this device has an hardware controlled radio.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Read frequency offset.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_FREQ);
	rt2x00dev->freq_offset = rt2x00_get_field16(eeprom, EEPROM_FREQ_OFFSET);

	/*
	 * Read बाह्यal LNA inक्रमmations.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC);

	अगर (rt2x00_get_field16(eeprom, EEPROM_NIC_EXTERNAL_LNA)) अणु
		__set_bit(CAPABILITY_EXTERNAL_LNA_A, &rt2x00dev->cap_flags);
		__set_bit(CAPABILITY_EXTERNAL_LNA_BG, &rt2x00dev->cap_flags);
	पूर्ण

	/*
	 * Store led settings, क्रम correct led behaviour.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_LED);

	rt73usb_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	rt73usb_init_led(rt2x00dev, &rt2x00dev->led_assoc, LED_TYPE_ASSOC);
	अगर (value == LED_MODE_SIGNAL_STRENGTH)
		rt73usb_init_led(rt2x00dev, &rt2x00dev->led_qual,
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
 * RF value list क्रम RF2528
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2528[] = अणु
	अणु 1,  0x00002c0c, 0x00000786, 0x00068255, 0x000fea0b पूर्ण,
	अणु 2,  0x00002c0c, 0x00000786, 0x00068255, 0x000fea1f पूर्ण,
	अणु 3,  0x00002c0c, 0x0000078a, 0x00068255, 0x000fea0b पूर्ण,
	अणु 4,  0x00002c0c, 0x0000078a, 0x00068255, 0x000fea1f पूर्ण,
	अणु 5,  0x00002c0c, 0x0000078e, 0x00068255, 0x000fea0b पूर्ण,
	अणु 6,  0x00002c0c, 0x0000078e, 0x00068255, 0x000fea1f पूर्ण,
	अणु 7,  0x00002c0c, 0x00000792, 0x00068255, 0x000fea0b पूर्ण,
	अणु 8,  0x00002c0c, 0x00000792, 0x00068255, 0x000fea1f पूर्ण,
	अणु 9,  0x00002c0c, 0x00000796, 0x00068255, 0x000fea0b पूर्ण,
	अणु 10, 0x00002c0c, 0x00000796, 0x00068255, 0x000fea1f पूर्ण,
	अणु 11, 0x00002c0c, 0x0000079a, 0x00068255, 0x000fea0b पूर्ण,
	अणु 12, 0x00002c0c, 0x0000079a, 0x00068255, 0x000fea1f पूर्ण,
	अणु 13, 0x00002c0c, 0x0000079e, 0x00068255, 0x000fea0b पूर्ण,
	अणु 14, 0x00002c0c, 0x000007a2, 0x00068255, 0x000fea13 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF5226
 * Supports: 2.4 GHz & 5.2 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_5226[] = अणु
	अणु 1,  0x00002c0c, 0x00000786, 0x00068255, 0x000fea0b पूर्ण,
	अणु 2,  0x00002c0c, 0x00000786, 0x00068255, 0x000fea1f पूर्ण,
	अणु 3,  0x00002c0c, 0x0000078a, 0x00068255, 0x000fea0b पूर्ण,
	अणु 4,  0x00002c0c, 0x0000078a, 0x00068255, 0x000fea1f पूर्ण,
	अणु 5,  0x00002c0c, 0x0000078e, 0x00068255, 0x000fea0b पूर्ण,
	अणु 6,  0x00002c0c, 0x0000078e, 0x00068255, 0x000fea1f पूर्ण,
	अणु 7,  0x00002c0c, 0x00000792, 0x00068255, 0x000fea0b पूर्ण,
	अणु 8,  0x00002c0c, 0x00000792, 0x00068255, 0x000fea1f पूर्ण,
	अणु 9,  0x00002c0c, 0x00000796, 0x00068255, 0x000fea0b पूर्ण,
	अणु 10, 0x00002c0c, 0x00000796, 0x00068255, 0x000fea1f पूर्ण,
	अणु 11, 0x00002c0c, 0x0000079a, 0x00068255, 0x000fea0b पूर्ण,
	अणु 12, 0x00002c0c, 0x0000079a, 0x00068255, 0x000fea1f पूर्ण,
	अणु 13, 0x00002c0c, 0x0000079e, 0x00068255, 0x000fea0b पूर्ण,
	अणु 14, 0x00002c0c, 0x000007a2, 0x00068255, 0x000fea13 पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु 36, 0x00002c0c, 0x0000099a, 0x00098255, 0x000fea23 पूर्ण,
	अणु 40, 0x00002c0c, 0x000009a2, 0x00098255, 0x000fea03 पूर्ण,
	अणु 44, 0x00002c0c, 0x000009a6, 0x00098255, 0x000fea0b पूर्ण,
	अणु 48, 0x00002c0c, 0x000009aa, 0x00098255, 0x000fea13 पूर्ण,
	अणु 52, 0x00002c0c, 0x000009ae, 0x00098255, 0x000fea1b पूर्ण,
	अणु 56, 0x00002c0c, 0x000009b2, 0x00098255, 0x000fea23 पूर्ण,
	अणु 60, 0x00002c0c, 0x000009ba, 0x00098255, 0x000fea03 पूर्ण,
	अणु 64, 0x00002c0c, 0x000009be, 0x00098255, 0x000fea0b पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु 100, 0x00002c0c, 0x00000a2a, 0x000b8255, 0x000fea03 पूर्ण,
	अणु 104, 0x00002c0c, 0x00000a2e, 0x000b8255, 0x000fea0b पूर्ण,
	अणु 108, 0x00002c0c, 0x00000a32, 0x000b8255, 0x000fea13 पूर्ण,
	अणु 112, 0x00002c0c, 0x00000a36, 0x000b8255, 0x000fea1b पूर्ण,
	अणु 116, 0x00002c0c, 0x00000a3a, 0x000b8255, 0x000fea23 पूर्ण,
	अणु 120, 0x00002c0c, 0x00000a82, 0x000b8255, 0x000fea03 पूर्ण,
	अणु 124, 0x00002c0c, 0x00000a86, 0x000b8255, 0x000fea0b पूर्ण,
	अणु 128, 0x00002c0c, 0x00000a8a, 0x000b8255, 0x000fea13 पूर्ण,
	अणु 132, 0x00002c0c, 0x00000a8e, 0x000b8255, 0x000fea1b पूर्ण,
	अणु 136, 0x00002c0c, 0x00000a92, 0x000b8255, 0x000fea23 पूर्ण,

	/* 802.11 UNII */
	अणु 140, 0x00002c0c, 0x00000a9a, 0x000b8255, 0x000fea03 पूर्ण,
	अणु 149, 0x00002c0c, 0x00000aa2, 0x000b8255, 0x000fea1f पूर्ण,
	अणु 153, 0x00002c0c, 0x00000aa6, 0x000b8255, 0x000fea27 पूर्ण,
	अणु 157, 0x00002c0c, 0x00000aae, 0x000b8255, 0x000fea07 पूर्ण,
	अणु 161, 0x00002c0c, 0x00000ab2, 0x000b8255, 0x000fea0f पूर्ण,
	अणु 165, 0x00002c0c, 0x00000ab6, 0x000b8255, 0x000fea17 पूर्ण,

	/* MMAC(Japan)J52 ch 34,38,42,46 */
	अणु 34, 0x00002c0c, 0x0008099a, 0x000da255, 0x000d3a0b पूर्ण,
	अणु 38, 0x00002c0c, 0x0008099e, 0x000da255, 0x000d3a13 पूर्ण,
	अणु 42, 0x00002c0c, 0x000809a2, 0x000da255, 0x000d3a1b पूर्ण,
	अणु 46, 0x00002c0c, 0x000809a6, 0x000da255, 0x000d3a23 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF5225 & RF2527
 * Supports: 2.4 GHz & 5.2 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_5225_2527[] = अणु
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


अटल पूर्णांक rt73usb_probe_hw_mode(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	काष्ठा channel_info *info;
	अक्षर *tx_घातer;
	अचिन्हित पूर्णांक i;

	/*
	 * Initialize all hw fields.
	 *
	 * Don't set IEEE80211_HOST_BROADCAST_PS_BUFFERING unless we are
	 * capable of sending the buffered frames out after the DTIM
	 * transmission using rt2x00lib_beaconकरोne. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some समय.
	 */
	ieee80211_hw_set(rt2x00dev->hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2x00_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * Initialize hw_mode inक्रमmation.
	 */
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	अगर (rt2x00_rf(rt2x00dev, RF2528)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2528);
		spec->channels = rf_vals_bg_2528;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF5226)) अणु
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_5226);
		spec->channels = rf_vals_5226;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2527)) अणु
		spec->num_channels = 14;
		spec->channels = rf_vals_5225_2527;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF5225)) अणु
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_5225_2527);
		spec->channels = rf_vals_5225_2527;
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

अटल पूर्णांक rt73usb_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;
	u32 reg;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt73usb_validate_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	retval = rt73usb_init_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Enable rfसमाप्त polling by setting GPIO direction of the
	 * rfसमाप्त चयन GPIO pin correctly.
	 */
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR13);
	rt2x00_set_field32(&reg, MAC_CSR13_सूची7, 0);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, reg);

	/*
	 * Initialize hw specअगरications.
	 */
	retval = rt73usb_probe_hw_mode(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * This device has multiple filters क्रम control frames,
	 * but has no a separate filter क्रम PS Poll frames.
	 */
	__set_bit(CAPABILITY_CONTROL_FILTERS, &rt2x00dev->cap_flags);

	/*
	 * This device requires firmware.
	 */
	__set_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	अगर (!modparam_nohwcrypt)
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	वापस 0;
पूर्ण

/*
 * IEEE80211 stack callback functions.
 */
अटल पूर्णांक rt73usb_conf_tx(काष्ठा ieee80211_hw *hw,
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
	offset = AC_TXOP_CSR0 + (माप(u32) * (!!(queue_idx & 2)));
	field.bit_offset = (queue_idx & 1) * 16;
	field.bit_mask = 0xffff << field.bit_offset;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, offset);
	rt2x00_set_field32(&reg, field, queue->txop);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, offset, reg);

	/* Update WMM रेजिस्टरs */
	field.bit_offset = queue_idx * 4;
	field.bit_mask = 0xf << field.bit_offset;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, AIFSN_CSR);
	rt2x00_set_field32(&reg, field, queue->aअगरs);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, AIFSN_CSR, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, CWMIN_CSR);
	rt2x00_set_field32(&reg, field, queue->cw_min);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, CWMIN_CSR, reg);

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, CWMAX_CSR);
	rt2x00_set_field32(&reg, field, queue->cw_max);
	rt2x00usb_रेजिस्टर_ग_लिखो(rt2x00dev, CWMAX_CSR, reg);

	वापस 0;
पूर्ण

अटल u64 rt73usb_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u64 tsf;
	u32 reg;

	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR13);
	tsf = (u64) rt2x00_get_field32(reg, TXRX_CSR13_HIGH_TSFTIMER) << 32;
	reg = rt2x00usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR12);
	tsf |= rt2x00_get_field32(reg, TXRX_CSR12_LOW_TSFTIMER);

	वापस tsf;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt73usb_mac80211_ops = अणु
	.tx			= rt2x00mac_tx,
	.start			= rt2x00mac_start,
	.stop			= rt2x00mac_stop,
	.add_पूर्णांकerface		= rt2x00mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rt2x00mac_हटाओ_पूर्णांकerface,
	.config			= rt2x00mac_config,
	.configure_filter	= rt2x00mac_configure_filter,
	.set_tim		= rt2x00mac_set_tim,
	.set_key		= rt2x00mac_set_key,
	.sw_scan_start		= rt2x00mac_sw_scan_start,
	.sw_scan_complete	= rt2x00mac_sw_scan_complete,
	.get_stats		= rt2x00mac_get_stats,
	.bss_info_changed	= rt2x00mac_bss_info_changed,
	.conf_tx		= rt73usb_conf_tx,
	.get_tsf		= rt73usb_get_tsf,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.flush			= rt2x00mac_flush,
	.set_antenna		= rt2x00mac_set_antenna,
	.get_antenna		= rt2x00mac_get_antenna,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt73usb_rt2x00_ops = अणु
	.probe_hw		= rt73usb_probe_hw,
	.get_firmware_name	= rt73usb_get_firmware_name,
	.check_firmware		= rt73usb_check_firmware,
	.load_firmware		= rt73usb_load_firmware,
	.initialize		= rt2x00usb_initialize,
	.uninitialize		= rt2x00usb_uninitialize,
	.clear_entry		= rt2x00usb_clear_entry,
	.set_device_state	= rt73usb_set_device_state,
	.rfसमाप्त_poll		= rt73usb_rfसमाप्त_poll,
	.link_stats		= rt73usb_link_stats,
	.reset_tuner		= rt73usb_reset_tuner,
	.link_tuner		= rt73usb_link_tuner,
	.watchकरोg		= rt2x00usb_watchकरोg,
	.start_queue		= rt73usb_start_queue,
	.kick_queue		= rt2x00usb_kick_queue,
	.stop_queue		= rt73usb_stop_queue,
	.flush_queue		= rt2x00usb_flush_queue,
	.ग_लिखो_tx_desc		= rt73usb_ग_लिखो_tx_desc,
	.ग_लिखो_beacon		= rt73usb_ग_लिखो_beacon,
	.clear_beacon		= rt73usb_clear_beacon,
	.get_tx_data_len	= rt73usb_get_tx_data_len,
	.fill_rxकरोne		= rt73usb_fill_rxकरोne,
	.config_shared_key	= rt73usb_config_shared_key,
	.config_pairwise_key	= rt73usb_config_pairwise_key,
	.config_filter		= rt73usb_config_filter,
	.config_पूर्णांकf		= rt73usb_config_पूर्णांकf,
	.config_erp		= rt73usb_config_erp,
	.config_ant		= rt73usb_config_ant,
	.config			= rt73usb_config,
पूर्ण;

अटल व्योम rt73usb_queue_init(काष्ठा data_queue *queue)
अणु
	चयन (queue->qid) अणु
	हाल QID_RX:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_BEACON:
		queue->limit = 4;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXINFO_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	हाल QID_ATIM:
	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rt2x00_ops rt73usb_ops = अणु
	.name			= KBUILD_MODNAME,
	.max_ap_पूर्णांकf		= 4,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt73usb_queue_init,
	.lib			= &rt73usb_rt2x00_ops,
	.hw			= &rt73usb_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt73usb_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * rt73usb module inक्रमmation.
 */
अटल स्थिर काष्ठा usb_device_id rt73usb_device_table[] = अणु
	/* AboCom */
	अणु USB_DEVICE(0x07b8, 0xb21b) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0xb21c) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0xb21d) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0xb21e) पूर्ण,
	अणु USB_DEVICE(0x07b8, 0xb21f) पूर्ण,
	/* AL */
	अणु USB_DEVICE(0x14b2, 0x3c10) पूर्ण,
	/* Amigo */
	अणु USB_DEVICE(0x148f, 0x9021) पूर्ण,
	अणु USB_DEVICE(0x0eb0, 0x9021) पूर्ण,
	/* AMIT  */
	अणु USB_DEVICE(0x18c5, 0x0002) पूर्ण,
	/* Askey */
	अणु USB_DEVICE(0x1690, 0x0722) पूर्ण,
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x1723) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1724) पूर्ण,
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x7050) पूर्ण,	/* FCC ID: K7SF5D7050B ver. 3.x */
	अणु USB_DEVICE(0x050d, 0x705a) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x905b) पूर्ण,
	अणु USB_DEVICE(0x050d, 0x905c) पूर्ण,
	/* Billionton */
	अणु USB_DEVICE(0x1631, 0xc019) पूर्ण,
	अणु USB_DEVICE(0x08dd, 0x0120) पूर्ण,
	/* Buffalo */
	अणु USB_DEVICE(0x0411, 0x00d8) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x00d9) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x00e6) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x00f4) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0116) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0119) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0137) पूर्ण,
	/* CEIVA */
	अणु USB_DEVICE(0x178d, 0x02be) पूर्ण,
	/* CNet */
	अणु USB_DEVICE(0x1371, 0x9022) पूर्ण,
	अणु USB_DEVICE(0x1371, 0x9032) पूर्ण,
	/* Conceptronic */
	अणु USB_DEVICE(0x14b2, 0x3c22) पूर्ण,
	/* Corega */
	अणु USB_DEVICE(0x07aa, 0x002e) पूर्ण,
	/* D-Link */
	अणु USB_DEVICE(0x07d1, 0x3c03) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c04) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c06) पूर्ण,
	अणु USB_DEVICE(0x07d1, 0x3c07) पूर्ण,
	/* Edimax */
	अणु USB_DEVICE(0x7392, 0x7318) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7618) पूर्ण,
	/* EnGenius */
	अणु USB_DEVICE(0x1740, 0x3701) पूर्ण,
	/* Gemtek */
	अणु USB_DEVICE(0x15a9, 0x0004) पूर्ण,
	/* Gigabyte */
	अणु USB_DEVICE(0x1044, 0x8008) पूर्ण,
	अणु USB_DEVICE(0x1044, 0x800a) पूर्ण,
	/* Huawei-3Com */
	अणु USB_DEVICE(0x1472, 0x0009) पूर्ण,
	/* Hercules */
	अणु USB_DEVICE(0x06f8, 0xe002) पूर्ण,
	अणु USB_DEVICE(0x06f8, 0xe010) पूर्ण,
	अणु USB_DEVICE(0x06f8, 0xe020) पूर्ण,
	/* Linksys */
	अणु USB_DEVICE(0x13b1, 0x0020) पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x0023) पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x0028) पूर्ण,
	/* MSI */
	अणु USB_DEVICE(0x0db0, 0x4600) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x6877) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x6874) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0xa861) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0xa874) पूर्ण,
	/* Ovislink */
	अणु USB_DEVICE(0x1b75, 0x7318) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x04bb, 0x093d) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x2573) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x2671) पूर्ण,
	अणु USB_DEVICE(0x0812, 0x3101) पूर्ण,
	/* Qcom */
	अणु USB_DEVICE(0x18e8, 0x6196) पूर्ण,
	अणु USB_DEVICE(0x18e8, 0x6229) पूर्ण,
	अणु USB_DEVICE(0x18e8, 0x6238) पूर्ण,
	/* Samsung */
	अणु USB_DEVICE(0x04e8, 0x4471) पूर्ण,
	/* Senao */
	अणु USB_DEVICE(0x1740, 0x7100) पूर्ण,
	/* Sitecom */
	अणु USB_DEVICE(0x0df6, 0x0024) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x0027) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x002f) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x90ac) पूर्ण,
	अणु USB_DEVICE(0x0df6, 0x9712) पूर्ण,
	/* Surecom */
	अणु USB_DEVICE(0x0769, 0x31f3) पूर्ण,
	/* Tilgin */
	अणु USB_DEVICE(0x6933, 0x5001) पूर्ण,
	/* Philips */
	अणु USB_DEVICE(0x0471, 0x200a) पूर्ण,
	/* Planex */
	अणु USB_DEVICE(0x2019, 0xab01) पूर्ण,
	अणु USB_DEVICE(0x2019, 0xab50) पूर्ण,
	/* WideTell */
	अणु USB_DEVICE(0x7167, 0x3840) पूर्ण,
	/* Zcom */
	अणु USB_DEVICE(0x0cde, 0x001c) पूर्ण,
	/* ZyXEL */
	अणु USB_DEVICE(0x0586, 0x3415) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT73 USB Wireless LAN driver.");
MODULE_DEVICE_TABLE(usb, rt73usb_device_table);
MODULE_FIRMWARE(FIRMWARE_RT2571);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt73usb_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	वापस rt2x00usb_probe(usb_पूर्णांकf, &rt73usb_ops);
पूर्ण

अटल काष्ठा usb_driver rt73usb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt73usb_device_table,
	.probe		= rt73usb_probe,
	.disconnect	= rt2x00usb_disconnect,
	.suspend	= rt2x00usb_suspend,
	.resume		= rt2x00usb_resume,
	.reset_resume	= rt2x00usb_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rt73usb_driver);

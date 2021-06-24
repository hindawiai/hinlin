<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2500usb
	Abstract: rt2500usb device specअगरic routines.
	Supported chipsets: RT2570.
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00usb.h"
#समावेश "rt2500usb.h"

/*
 * Allow hardware encryption to be disabled.
 */
अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

/*
 * Register access.
 * All access to the CSR रेजिस्टरs will go through the methods
 * rt2500usb_रेजिस्टर_पढ़ो and rt2500usb_रेजिस्टर_ग_लिखो.
 * BBP and RF रेजिस्टर require indirect रेजिस्टर access,
 * and use the CSR रेजिस्टरs BBPCSR and RFCSR to achieve this.
 * These indirect रेजिस्टरs work with busy bits,
 * and we will try maximal REGISTER_USB_BUSY_COUNT बार to access
 * the रेजिस्टर जबतक taking a REGISTER_BUSY_DELAY us delay
 * between each attampt. When the busy bit is still set at that समय,
 * the access attempt is considered to have failed,
 * and we will prपूर्णांक an error.
 * If the csr_mutex is alपढ़ोy held then the _lock variants must
 * be used instead.
 */
अटल u16 rt2500usb_रेजिस्टर_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक offset)
अणु
	__le16 reg;
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_READ,
				      USB_VENDOR_REQUEST_IN, offset,
				      &reg, माप(reg));
	वापस le16_to_cpu(reg);
पूर्ण

अटल u16 rt2500usb_रेजिस्टर_पढ़ो_lock(काष्ठा rt2x00_dev *rt2x00dev,
					स्थिर अचिन्हित पूर्णांक offset)
अणु
	__le16 reg;
	rt2x00usb_venकरोr_req_buff_lock(rt2x00dev, USB_MULTI_READ,
				       USB_VENDOR_REQUEST_IN, offset,
				       &reg, माप(reg), REGISTER_TIMEOUT);
	वापस le16_to_cpu(reg);
पूर्ण

अटल व्योम rt2500usb_रेजिस्टर_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
					    स्थिर अचिन्हित पूर्णांक offset,
					    u16 value)
अणु
	__le16 reg = cpu_to_le16(value);
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_WRITE,
				      USB_VENDOR_REQUEST_OUT, offset,
				      &reg, माप(reg));
पूर्ण

अटल व्योम rt2500usb_रेजिस्टर_ग_लिखो_lock(काष्ठा rt2x00_dev *rt2x00dev,
						 स्थिर अचिन्हित पूर्णांक offset,
						 u16 value)
अणु
	__le16 reg = cpu_to_le16(value);
	rt2x00usb_venकरोr_req_buff_lock(rt2x00dev, USB_MULTI_WRITE,
				       USB_VENDOR_REQUEST_OUT, offset,
				       &reg, माप(reg), REGISTER_TIMEOUT);
पूर्ण

अटल व्योम rt2500usb_रेजिस्टर_multiग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
						 स्थिर अचिन्हित पूर्णांक offset,
						 व्योम *value, स्थिर u16 length)
अणु
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_WRITE,
				      USB_VENDOR_REQUEST_OUT, offset,
				      value, length);
पूर्ण

अटल पूर्णांक rt2500usb_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर अचिन्हित पूर्णांक offset,
				  काष्ठा rt2x00_field16 field,
				  u16 *reg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) अणु
		*reg = rt2500usb_रेजिस्टर_पढ़ो_lock(rt2x00dev, offset);
		अगर (!rt2x00_get_field16(*reg, field))
			वापस 1;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "Indirect register access failed: offset=0x%.08x, value=0x%.08x\n",
		   offset, *reg);
	*reg = ~0;

	वापस 0;
पूर्ण

#घोषणा WAIT_FOR_BBP(__dev, __reg) \
	rt2500usb_regbusy_पढ़ो((__dev), PHY_CSR8, PHY_CSR8_BUSY, (__reg))
#घोषणा WAIT_FOR_RF(__dev, __reg) \
	rt2500usb_regbusy_पढ़ो((__dev), PHY_CSR10, PHY_CSR10_RF_BUSY, (__reg))

अटल व्योम rt2500usb_bbp_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				स्थिर अचिन्हित पूर्णांक word, स्थिर u8 value)
अणु
	u16 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the BBP becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	अगर (WAIT_FOR_BBP(rt2x00dev, &reg)) अणु
		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR7_DATA, value);
		rt2x00_set_field16(&reg, PHY_CSR7_REG_ID, word);
		rt2x00_set_field16(&reg, PHY_CSR7_READ_CONTROL, 0);

		rt2500usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR7, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल u8 rt2500usb_bbp_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			     स्थिर अचिन्हित पूर्णांक word)
अणु
	u16 reg;
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
		rt2x00_set_field16(&reg, PHY_CSR7_REG_ID, word);
		rt2x00_set_field16(&reg, PHY_CSR7_READ_CONTROL, 1);

		rt2500usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR7, reg);

		अगर (WAIT_FOR_BBP(rt2x00dev, &reg))
			reg = rt2500usb_रेजिस्टर_पढ़ो_lock(rt2x00dev, PHY_CSR7);
	पूर्ण

	value = rt2x00_get_field16(reg, PHY_CSR7_DATA);

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल व्योम rt2500usb_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
			       स्थिर अचिन्हित पूर्णांक word, स्थिर u32 value)
अणु
	u16 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the RF becomes available, afterwards we
	 * can safely ग_लिखो the new data पूर्णांकo the रेजिस्टर.
	 */
	अगर (WAIT_FOR_RF(rt2x00dev, &reg)) अणु
		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR9_RF_VALUE, value);
		rt2500usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR9, reg);

		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR10_RF_VALUE, value >> 16);
		rt2x00_set_field16(&reg, PHY_CSR10_RF_NUMBER_OF_BITS, 20);
		rt2x00_set_field16(&reg, PHY_CSR10_RF_IF_SELECT, 0);
		rt2x00_set_field16(&reg, PHY_CSR10_RF_BUSY, 1);

		rt2500usb_रेजिस्टर_ग_लिखो_lock(rt2x00dev, PHY_CSR10, reg);
		rt2x00_rf_ग_लिखो(rt2x00dev, word, value);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
अटल u32 _rt2500usb_रेजिस्टर_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
				     स्थिर अचिन्हित पूर्णांक offset)
अणु
	वापस rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, offset);
पूर्ण

अटल व्योम _rt2500usb_रेजिस्टर_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
				      स्थिर अचिन्हित पूर्णांक offset,
				      u32 value)
अणु
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, offset, value);
पूर्ण

अटल स्थिर काष्ठा rt2x00debug rt2500usb_rt2x00debug = अणु
	.owner	= THIS_MODULE,
	.csr	= अणु
		.पढ़ो		= _rt2500usb_रेजिस्टर_पढ़ो,
		.ग_लिखो		= _rt2500usb_रेजिस्टर_ग_लिखो,
		.flags		= RT2X00DEBUGFS_OFFSET,
		.word_base	= CSR_REG_BASE,
		.word_size	= माप(u16),
		.word_count	= CSR_REG_SIZE / माप(u16),
	पूर्ण,
	.eeprom	= अणु
		.पढ़ो		= rt2x00_eeprom_पढ़ो,
		.ग_लिखो		= rt2x00_eeprom_ग_लिखो,
		.word_base	= EEPROM_BASE,
		.word_size	= माप(u16),
		.word_count	= EEPROM_SIZE / माप(u16),
	पूर्ण,
	.bbp	= अणु
		.पढ़ो		= rt2500usb_bbp_पढ़ो,
		.ग_लिखो		= rt2500usb_bbp_ग_लिखो,
		.word_base	= BBP_BASE,
		.word_size	= माप(u8),
		.word_count	= BBP_SIZE / माप(u8),
	पूर्ण,
	.rf	= अणु
		.पढ़ो		= rt2x00_rf_पढ़ो,
		.ग_लिखो		= rt2500usb_rf_ग_लिखो,
		.word_base	= RF_BASE,
		.word_size	= माप(u32),
		.word_count	= RF_SIZE / माप(u32),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

अटल पूर्णांक rt2500usb_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 reg;

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR19);
	वापस rt2x00_get_field16(reg, MAC_CSR19_VAL7);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
अटल व्योम rt2500usb_brightness_set(काष्ठा led_classdev *led_cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	अचिन्हित पूर्णांक enabled = brightness != LED_OFF;
	u16 reg;

	reg = rt2500usb_रेजिस्टर_पढ़ो(led->rt2x00dev, MAC_CSR20);

	अगर (led->type == LED_TYPE_RADIO || led->type == LED_TYPE_ASSOC)
		rt2x00_set_field16(&reg, MAC_CSR20_LINK, enabled);
	अन्यथा अगर (led->type == LED_TYPE_ACTIVITY)
		rt2x00_set_field16(&reg, MAC_CSR20_ACTIVITY, enabled);

	rt2500usb_रेजिस्टर_ग_लिखो(led->rt2x00dev, MAC_CSR20, reg);
पूर्ण

अटल पूर्णांक rt2500usb_blink_set(काष्ठा led_classdev *led_cdev,
			       अचिन्हित दीर्घ *delay_on,
			       अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	u16 reg;

	reg = rt2500usb_रेजिस्टर_पढ़ो(led->rt2x00dev, MAC_CSR21);
	rt2x00_set_field16(&reg, MAC_CSR21_ON_PERIOD, *delay_on);
	rt2x00_set_field16(&reg, MAC_CSR21_OFF_PERIOD, *delay_off);
	rt2500usb_रेजिस्टर_ग_लिखो(led->rt2x00dev, MAC_CSR21, reg);

	वापस 0;
पूर्ण

अटल व्योम rt2500usb_init_led(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00_led *led,
			       क्रमागत led_type type)
अणु
	led->rt2x00dev = rt2x00dev;
	led->type = type;
	led->led_dev.brightness_set = rt2500usb_brightness_set;
	led->led_dev.blink_set = rt2500usb_blink_set;
	led->flags = LED_INITIALIZED;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

/*
 * Configuration handlers.
 */

/*
 * rt2500usb करोes not dअगरferentiate between shared and pairwise
 * keys, so we should use the same function क्रम both key types.
 */
अटल पूर्णांक rt2500usb_config_key(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00lib_crypto *crypto,
				काष्ठा ieee80211_key_conf *key)
अणु
	u32 mask;
	u16 reg;
	क्रमागत cipher curr_cipher;

	अगर (crypto->cmd == SET_KEY) अणु
		/*
		 * Disallow to set WEP key other than with index 0,
		 * it is known that not work at least on some hardware.
		 * SW crypto will be used in that हाल.
		 */
		अगर ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
		     key->cipher == WLAN_CIPHER_SUITE_WEP104) &&
		    key->keyidx != 0)
			वापस -EOPNOTSUPP;

		/*
		 * Pairwise key will always be entry 0, but this
		 * could collide with a shared key on the same
		 * position...
		 */
		mask = TXRX_CSR0_KEY_ID.bit_mask;

		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
		curr_cipher = rt2x00_get_field16(reg, TXRX_CSR0_ALGORITHM);
		reg &= mask;

		अगर (reg && reg == mask)
			वापस -ENOSPC;

		reg = rt2x00_get_field16(reg, TXRX_CSR0_KEY_ID);

		key->hw_key_idx += reg ? ffz(reg) : 0;
		/*
		 * Hardware requires that all keys use the same cipher
		 * (e.g. TKIP-only, AES-only, but not TKIP+AES).
		 * If this is not the first key, compare the cipher with the
		 * first one and fall back to SW crypto अगर not the same.
		 */
		अगर (key->hw_key_idx > 0 && crypto->cipher != curr_cipher)
			वापस -EOPNOTSUPP;

		rt2500usb_रेजिस्टर_multiग_लिखो(rt2x00dev, KEY_ENTRY(key->hw_key_idx),
					      crypto->key, माप(crypto->key));

		/*
		 * The driver करोes not support the IV/EIV generation
		 * in hardware. However it demands the data to be provided
		 * both separately as well as inside the frame.
		 * We alपढ़ोy provided the CONFIG_CRYPTO_COPY_IV to rt2x00lib
		 * to ensure rt2x00lib will not strip the data from the
		 * frame after the copy, now we must tell mac80211
		 * to generate the IV/EIV data.
		 */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
	पूर्ण

	/*
	 * TXRX_CSR0_KEY_ID contains only single-bit fields to indicate
	 * a particular key is valid.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field16(&reg, TXRX_CSR0_ALGORITHM, crypto->cipher);
	rt2x00_set_field16(&reg, TXRX_CSR0_IV_OFFSET, IEEE80211_HEADER);

	mask = rt2x00_get_field16(reg, TXRX_CSR0_KEY_ID);
	अगर (crypto->cmd == SET_KEY)
		mask |= 1 << key->hw_key_idx;
	अन्यथा अगर (crypto->cmd == DISABLE_KEY)
		mask &= ~(1 << key->hw_key_idx);
	rt2x00_set_field16(&reg, TXRX_CSR0_KEY_ID, mask);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	वापस 0;
पूर्ण

अटल व्योम rt2500usb_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर अचिन्हित पूर्णांक filter_flags)
अणु
	u16 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * and broadcast frames will always be accepted since
	 * there is no filter क्रम it at this समय.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_CRC,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_PHYSICAL,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_CONTROL,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags));
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_TODS,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags) &&
			   !rt2x00dev->पूर्णांकf_ap_count);
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_VERSION_ERROR, 1);
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_MULTICAST,
			   !(filter_flags & FIF_ALLMULTI));
	rt2x00_set_field16(&reg, TXRX_CSR2_DROP_BROADCAST, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);
पूर्ण

अटल व्योम rt2500usb_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
				  काष्ठा rt2x00पूर्णांकf_conf *conf,
				  स्थिर अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक bcn_preload;
	u16 reg;

	अगर (flags & CONFIG_UPDATE_TYPE) अणु
		/*
		 * Enable beacon config
		 */
		bcn_preload = PREAMBLE + GET_DURATION(IEEE80211_HEADER, 20);
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR20);
		rt2x00_set_field16(&reg, TXRX_CSR20_OFFSET, bcn_preload >> 6);
		rt2x00_set_field16(&reg, TXRX_CSR20_BCN_EXPECT_WINDOW,
				   2 * (conf->type != NL80211_IFTYPE_STATION));
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR20, reg);

		/*
		 * Enable synchronisation.
		 */
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR18);
		rt2x00_set_field16(&reg, TXRX_CSR18_OFFSET, 0);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR18, reg);

		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR19);
		rt2x00_set_field16(&reg, TXRX_CSR19_TSF_SYNC, conf->sync);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
	पूर्ण

	अगर (flags & CONFIG_UPDATE_MAC)
		rt2500usb_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR2, conf->mac,
					      (3 * माप(__le16)));

	अगर (flags & CONFIG_UPDATE_BSSID)
		rt2500usb_रेजिस्टर_multiग_लिखो(rt2x00dev, MAC_CSR5, conf->bssid,
					      (3 * माप(__le16)));
पूर्ण

अटल व्योम rt2500usb_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा rt2x00lib_erp *erp,
				 u32 changed)
अणु
	u16 reg;

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR10);
		rt2x00_set_field16(&reg, TXRX_CSR10_AUTORESPOND_PREAMBLE,
				   !!erp->लघु_preamble);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR10, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR11,
					 erp->basic_rates);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR18);
		rt2x00_set_field16(&reg, TXRX_CSR18_INTERVAL,
				   erp->beacon_पूर्णांक * 4);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR18, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR10, erp->slot_समय);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, erp->sअगरs);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR12, erp->eअगरs);
	पूर्ण
पूर्ण

अटल व्योम rt2500usb_config_ant(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा antenna_setup *ant)
अणु
	u8 r2;
	u8 r14;
	u16 csr5;
	u16 csr6;

	/*
	 * We should never come here because rt2x00lib is supposed
	 * to catch this and send us the correct antenna explicitely.
	 */
	BUG_ON(ant->rx == ANTENNA_SW_DIVERSITY ||
	       ant->tx == ANTENNA_SW_DIVERSITY);

	r2 = rt2500usb_bbp_पढ़ो(rt2x00dev, 2);
	r14 = rt2500usb_bbp_पढ़ो(rt2x00dev, 14);
	csr5 = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR5);
	csr6 = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR6);

	/*
	 * Configure the TX antenna.
	 */
	चयन (ant->tx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 1);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 1);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 1);
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 0);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 0);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 0);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r2, BBP_R2_TX_ANTENNA, 2);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK, 2);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM, 2);
		अवरोध;
	पूर्ण

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 1);
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 0);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r14, BBP_R14_RX_ANTENNA, 2);
		अवरोध;
	पूर्ण

	/*
	 * RT2525E and RT5222 need to flip TX I/Q
	 */
	अगर (rt2x00_rf(rt2x00dev, RF2525E) || rt2x00_rf(rt2x00dev, RF5222)) अणु
		rt2x00_set_field8(&r2, BBP_R2_TX_IQ_FLIP, 1);
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK_FLIP, 1);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM_FLIP, 1);

		/*
		 * RT2525E करोes not need RX I/Q Flip.
		 */
		अगर (rt2x00_rf(rt2x00dev, RF2525E))
			rt2x00_set_field8(&r14, BBP_R14_RX_IQ_FLIP, 0);
	पूर्ण अन्यथा अणु
		rt2x00_set_field16(&csr5, PHY_CSR5_CCK_FLIP, 0);
		rt2x00_set_field16(&csr6, PHY_CSR6_OFDM_FLIP, 0);
	पूर्ण

	rt2500usb_bbp_ग_लिखो(rt2x00dev, 2, r2);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 14, r14);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR5, csr5);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR6, csr6);
पूर्ण

अटल व्योम rt2500usb_config_channel(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा rf_channel *rf, स्थिर पूर्णांक txघातer)
अणु
	/*
	 * Set TXघातer.
	 */
	rt2x00_set_field32(&rf->rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txघातer));

	/*
	 * For RT2525E we should first set the channel to half band higher.
	 */
	अगर (rt2x00_rf(rt2x00dev, RF2525E)) अणु
		अटल स्थिर u32 vals[] = अणु
			0x000008aa, 0x000008ae, 0x000008ae, 0x000008b2,
			0x000008b2, 0x000008b6, 0x000008b6, 0x000008ba,
			0x000008ba, 0x000008be, 0x000008b7, 0x00000902,
			0x00000902, 0x00000906
		पूर्ण;

		rt2500usb_rf_ग_लिखो(rt2x00dev, 2, vals[rf->channel - 1]);
		अगर (rf->rf4)
			rt2500usb_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);
	पूर्ण

	rt2500usb_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2500usb_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2500usb_rf_ग_लिखो(rt2x00dev, 3, rf->rf3);
	अगर (rf->rf4)
		rt2500usb_rf_ग_लिखो(rt2x00dev, 4, rf->rf4);
पूर्ण

अटल व्योम rt2500usb_config_txघातer(काष्ठा rt2x00_dev *rt2x00dev,
				     स्थिर पूर्णांक txघातer)
अणु
	u32 rf3;

	rf3 = rt2x00_rf_पढ़ो(rt2x00dev, 3);
	rt2x00_set_field32(&rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txघातer));
	rt2500usb_rf_ग_लिखो(rt2x00dev, 3, rf3);
पूर्ण

अटल व्योम rt2500usb_config_ps(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00lib_conf *libconf)
अणु
	क्रमागत dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u16 reg;

	अगर (state == STATE_SLEEP) अणु
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR18);
		rt2x00_set_field16(&reg, MAC_CSR18_DELAY_AFTER_BEACON,
				   rt2x00dev->beacon_पूर्णांक - 20);
		rt2x00_set_field16(&reg, MAC_CSR18_BEACONS_BEFORE_WAKEUP,
				   libconf->conf->listen_पूर्णांकerval - 1);

		/* We must first disable स्वतःwake beक्रमe it can be enabled */
		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 0);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR18, reg);

		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 1);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR18, reg);
	पूर्ण अन्यथा अणु
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR18);
		rt2x00_set_field16(&reg, MAC_CSR18_AUTO_WAKE, 0);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR18, reg);
	पूर्ण

	rt2x00dev->ops->lib->set_device_state(rt2x00dev, state);
पूर्ण

अटल व्योम rt2500usb_config(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00lib_conf *libconf,
			     स्थिर अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt2500usb_config_channel(rt2x00dev, &libconf->rf,
					 libconf->conf->घातer_level);
	अगर ((flags & IEEE80211_CONF_CHANGE_POWER) &&
	    !(flags & IEEE80211_CONF_CHANGE_CHANNEL))
		rt2500usb_config_txघातer(rt2x00dev,
					 libconf->conf->घातer_level);
	अगर (flags & IEEE80211_CONF_CHANGE_PS)
		rt2500usb_config_ps(rt2x00dev, libconf);
पूर्ण

/*
 * Link tuning
 */
अटल व्योम rt2500usb_link_stats(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा link_qual *qual)
अणु
	u16 reg;

	/*
	 * Update FCS error count from रेजिस्टर.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR0);
	qual->rx_failed = rt2x00_get_field16(reg, STA_CSR0_FCS_ERROR);

	/*
	 * Update False CCA count from रेजिस्टर.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, STA_CSR3);
	qual->false_cca = rt2x00_get_field16(reg, STA_CSR3_FALSE_CCA_ERROR);
पूर्ण

अटल व्योम rt2500usb_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा link_qual *qual)
अणु
	u16 eeprom;
	u16 value;

	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R24);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R24_LOW);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 24, value);

	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R25);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R25_LOW);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 25, value);

	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R61);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R61_LOW);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 61, value);

	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_VGC);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_VGCUPPER);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 17, value);

	qual->vgc_level = value;
पूर्ण

/*
 * Queue handlers.
 */
अटल व्योम rt2500usb_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u16 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
		rt2x00_set_field16(&reg, TXRX_CSR2_DISABLE_RX, 0);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR19);
		rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 1);
		rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 1);
		rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 1);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt2500usb_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u16 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
		rt2x00_set_field16(&reg, TXRX_CSR2_DISABLE_RX, 1);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR19);
		rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 0);
		rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 0);
		rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Initialization functions.
 */
अटल पूर्णांक rt2500usb_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 reg;

	rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_DEVICE_MODE, 0x0001,
				    USB_MODE_TEST, REGISTER_TIMEOUT);
	rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_SINGLE_WRITE, 0x0308,
				    0x00f0, REGISTER_TIMEOUT);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR2);
	rt2x00_set_field16(&reg, TXRX_CSR2_DISABLE_RX, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR2, reg);

	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, 0x1111);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR14, 0x1e11);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 1);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 1);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR5);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID0, 13);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID1, 12);
	rt2x00_set_field16(&reg, TXRX_CSR5_BBP_ID1_VALID, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR5, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR6);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID0, 10);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID1, 11);
	rt2x00_set_field16(&reg, TXRX_CSR6_BBP_ID1_VALID, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR6, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR7);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID0, 7);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID1, 6);
	rt2x00_set_field16(&reg, TXRX_CSR7_BBP_ID1_VALID, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR7, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR8);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID0, 5);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID0_VALID, 1);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID1, 0);
	rt2x00_set_field16(&reg, TXRX_CSR8_BBP_ID1_VALID, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR8, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR19);
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_SYNC, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 0);
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);

	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR21, 0xe78f);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR9, 0xff1d);

	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		वापस -EBUSY;

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR1);
	rt2x00_set_field16(&reg, MAC_CSR1_SOFT_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_BBP_RESET, 0);
	rt2x00_set_field16(&reg, MAC_CSR1_HOST_READY, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR1, reg);

	अगर (rt2x00_rev(rt2x00dev) >= RT2570_VERSION_C) अणु
		reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR2);
		rt2x00_set_field16(&reg, PHY_CSR2_LNA, 0);
	पूर्ण अन्यथा अणु
		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR2_LNA, 1);
		rt2x00_set_field16(&reg, PHY_CSR2_LNA_MODE, 3);
	पूर्ण
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR2, reg);

	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR11, 0x0002);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR22, 0x0053);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR15, 0x01ee);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR16, 0x0000);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR8);
	rt2x00_set_field16(&reg, MAC_CSR8_MAX_FRAME_UNIT,
			   rt2x00dev->rx->data_size);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR8, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR0);
	rt2x00_set_field16(&reg, TXRX_CSR0_ALGORITHM, CIPHER_NONE);
	rt2x00_set_field16(&reg, TXRX_CSR0_IV_OFFSET, IEEE80211_HEADER);
	rt2x00_set_field16(&reg, TXRX_CSR0_KEY_ID, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR0, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR18);
	rt2x00_set_field16(&reg, MAC_CSR18_DELAY_AFTER_BEACON, 90);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR18, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, PHY_CSR4);
	rt2x00_set_field16(&reg, PHY_CSR4_LOW_RF_LE, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, PHY_CSR4, reg);

	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR1);
	rt2x00_set_field16(&reg, TXRX_CSR1_AUTO_SEQUENCE, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR1, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2500usb_रुको_bbp_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u8 value;

	क्रम (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) अणु
		value = rt2500usb_bbp_पढ़ो(rt2x00dev, 0);
		अगर ((value != 0xff) && (value != 0x00))
			वापस 0;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल पूर्णांक rt2500usb_init_bbp(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 eeprom;
	u8 value;
	u8 reg_id;

	अगर (unlikely(rt2500usb_रुको_bbp_पढ़ोy(rt2x00dev)))
		वापस -EACCES;

	rt2500usb_bbp_ग_लिखो(rt2x00dev, 3, 0x02);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 4, 0x19);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 14, 0x1c);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 15, 0x30);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 16, 0xac);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 18, 0x18);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 19, 0xff);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 20, 0x1e);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 21, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 22, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 23, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 24, 0x80);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 25, 0x50);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 26, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 27, 0x23);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 30, 0x10);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 31, 0x2b);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 32, 0xb9);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 34, 0x12);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 35, 0x50);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 39, 0xc4);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 40, 0x02);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 41, 0x60);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 53, 0x10);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 54, 0x18);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 56, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 57, 0x10);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 58, 0x08);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 61, 0x60);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 62, 0x10);
	rt2500usb_bbp_ग_लिखो(rt2x00dev, 75, 0xff);

	क्रम (i = 0; i < EEPROM_BBP_SIZE; i++) अणु
		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBP_START + i);

		अगर (eeprom != 0xffff && eeprom != 0x0000) अणु
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2500usb_bbp_ग_लिखो(rt2x00dev, reg_id, value);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल पूर्णांक rt2500usb_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Initialize all रेजिस्टरs.
	 */
	अगर (unlikely(rt2500usb_init_रेजिस्टरs(rt2x00dev) ||
		     rt2500usb_init_bbp(rt2x00dev)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम rt2500usb_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR13, 0x2121);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR14, 0x2121);

	/*
	 * Disable synchronisation.
	 */
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, 0);

	rt2x00usb_disable_radio(rt2x00dev);
पूर्ण

अटल पूर्णांक rt2500usb_set_state(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत dev_state state)
अणु
	u16 reg;
	u16 reg2;
	अचिन्हित पूर्णांक i;
	अक्षर put_to_sleep;
	अक्षर bbp_state;
	अक्षर rf_state;

	put_to_sleep = (state != STATE_AWAKE);

	reg = 0;
	rt2x00_set_field16(&reg, MAC_CSR17_BBP_DESIRE_STATE, state);
	rt2x00_set_field16(&reg, MAC_CSR17_RF_DESIRE_STATE, state);
	rt2x00_set_field16(&reg, MAC_CSR17_PUT_TO_SLEEP, put_to_sleep);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR17, reg);
	rt2x00_set_field16(&reg, MAC_CSR17_SET_STATE, 1);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR17, reg);

	/*
	 * Device is not guaranteed to be in the requested state yet.
	 * We must रुको until the रेजिस्टर indicates that the
	 * device has entered the correct state.
	 */
	क्रम (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) अणु
		reg2 = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR17);
		bbp_state = rt2x00_get_field16(reg2, MAC_CSR17_BBP_CURR_STATE);
		rf_state = rt2x00_get_field16(reg2, MAC_CSR17_RF_CURR_STATE);
		अगर (bbp_state == state && rf_state == state)
			वापस 0;
		rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR17, reg);
		msleep(30);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rt2500usb_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt2500usb_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		rt2500usb_disable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		/* No support, but no error either */
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt2500usb_set_state(rt2x00dev, state);
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
अटल व्योम rt2500usb_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
				    काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *txd = (__le32 *) entry->skb->data;
	u32 word;

	/*
	 * Start writing the descriptor words.
	 */
	word = rt2x00_desc_पढ़ो(txd, 0);
	rt2x00_set_field32(&word, TXD_W0_RETRY_LIMIT, txdesc->retry_limit);
	rt2x00_set_field32(&word, TXD_W0_MORE_FRAG,
			   test_bit(ENTRY_TXD_MORE_FRAG, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_ACK,
			   test_bit(ENTRY_TXD_ACK, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_TIMESTAMP,
			   test_bit(ENTRY_TXD_REQ_TIMESTAMP, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_OFDM,
			   (txdesc->rate_mode == RATE_MODE_OFDM));
	rt2x00_set_field32(&word, TXD_W0_NEW_SEQ,
			   test_bit(ENTRY_TXD_FIRST_FRAGMENT, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_IFS, txdesc->u.plcp.अगरs);
	rt2x00_set_field32(&word, TXD_W0_DATABYTE_COUNT, txdesc->length);
	rt2x00_set_field32(&word, TXD_W0_CIPHER, !!txdesc->cipher);
	rt2x00_set_field32(&word, TXD_W0_KEY_ID, txdesc->key_idx);
	rt2x00_desc_ग_लिखो(txd, 0, word);

	word = rt2x00_desc_पढ़ो(txd, 1);
	rt2x00_set_field32(&word, TXD_W1_IV_OFFSET, txdesc->iv_offset);
	rt2x00_set_field32(&word, TXD_W1_AIFS, entry->queue->aअगरs);
	rt2x00_set_field32(&word, TXD_W1_CWMIN, entry->queue->cw_min);
	rt2x00_set_field32(&word, TXD_W1_CWMAX, entry->queue->cw_max);
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
अटल व्योम rt2500usb_beaconकरोne(काष्ठा urb *urb);

अटल व्योम rt2500usb_ग_लिखो_beacon(काष्ठा queue_entry *entry,
				   काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(rt2x00dev->dev);
	काष्ठा queue_entry_priv_usb_bcn *bcn_priv = entry->priv_data;
	पूर्णांक pipe = usb_sndbulkpipe(usb_dev, entry->queue->usb_endpoपूर्णांक);
	पूर्णांक length;
	u16 reg, reg0;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, TXRX_CSR19);
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);

	/*
	 * Add space क्रम the descriptor in front of the skb.
	 */
	skb_push(entry->skb, TXD_DESC_SIZE);
	स_रखो(entry->skb->data, 0, TXD_DESC_SIZE);

	/*
	 * Write the TX descriptor क्रम the beacon.
	 */
	rt2500usb_ग_लिखो_tx_desc(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry);

	/*
	 * USB devices cannot blindly pass the skb->len as the
	 * length of the data to usb_fill_bulk_urb. Pass the skb
	 * to the driver to determine what the length should be.
	 */
	length = rt2x00dev->ops->lib->get_tx_data_len(entry);

	usb_fill_bulk_urb(bcn_priv->urb, usb_dev, pipe,
			  entry->skb->data, length, rt2500usb_beaconकरोne,
			  entry);

	/*
	 * Second we need to create the guardian byte.
	 * We only need a single byte, so lets recycle
	 * the 'flags' field we are not using क्रम beacons.
	 */
	bcn_priv->guardian_data = 0;
	usb_fill_bulk_urb(bcn_priv->guardian_urb, usb_dev, pipe,
			  &bcn_priv->guardian_data, 1, rt2500usb_beaconकरोne,
			  entry);

	/*
	 * Send out the guardian byte.
	 */
	usb_submit_urb(bcn_priv->guardian_urb, GFP_ATOMIC);

	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field16(&reg, TXRX_CSR19_TSF_COUNT, 1);
	rt2x00_set_field16(&reg, TXRX_CSR19_TBCN, 1);
	reg0 = reg;
	rt2x00_set_field16(&reg, TXRX_CSR19_BEACON_GEN, 1);
	/*
	 * Beacon generation will fail initially.
	 * To prevent this we need to change the TXRX_CSR19
	 * रेजिस्टर several बार (reg0 is the same as reg
	 * except क्रम TXRX_CSR19_BEACON_GEN, which is 0 in reg0
	 * and 1 in reg).
	 */
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, TXRX_CSR19, reg);
पूर्ण

अटल पूर्णांक rt2500usb_get_tx_data_len(काष्ठा queue_entry *entry)
अणु
	पूर्णांक length;

	/*
	 * The length _must_ be a multiple of 2,
	 * but it must _not_ be a multiple of the USB packet size.
	 */
	length = roundup(entry->skb->len, 2);
	length += (2 * !(length % entry->queue->usb_maxpacket));

	वापस length;
पूर्ण

/*
 * RX control handlers
 */
अटल व्योम rt2500usb_fill_rxकरोne(काष्ठा queue_entry *entry,
				  काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा queue_entry_priv_usb *entry_priv = entry->priv_data;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	__le32 *rxd =
	    (__le32 *)(entry->skb->data +
		       (entry_priv->urb->actual_length -
			entry->queue->desc_size));
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
	अगर (rt2x00_get_field32(word0, RXD_W0_PHYSICAL_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_PLCP_CRC;

	rxdesc->cipher = rt2x00_get_field32(word0, RXD_W0_CIPHER);
	अगर (rt2x00_get_field32(word0, RXD_W0_CIPHER_ERROR))
		rxdesc->cipher_status = RX_CRYPTO_FAIL_KEY;

	अगर (rxdesc->cipher != CIPHER_NONE) अणु
		rxdesc->iv[0] = _rt2x00_desc_पढ़ो(rxd, 2);
		rxdesc->iv[1] = _rt2x00_desc_पढ़ो(rxd, 3);
		rxdesc->dev_flags |= RXDONE_CRYPTO_IV;

		/* ICV is located at the end of frame */

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
	rxdesc->rssi =
	    rt2x00_get_field32(word1, RXD_W1_RSSI) - rt2x00dev->rssi_offset;
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	अगर (rt2x00_get_field32(word0, RXD_W0_OFDM))
		rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	अन्यथा
		rxdesc->dev_flags |= RXDONE_SIGNAL_BITRATE;
	अगर (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;

	/*
	 * Adjust the skb memory winकरोw to the frame boundaries.
	 */
	skb_trim(entry->skb, rxdesc->size);
पूर्ण

/*
 * Interrupt functions.
 */
अटल व्योम rt2500usb_beaconकरोne(काष्ठा urb *urb)
अणु
	काष्ठा queue_entry *entry = (काष्ठा queue_entry *)urb->context;
	काष्ठा queue_entry_priv_usb_bcn *bcn_priv = entry->priv_data;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &entry->queue->rt2x00dev->flags))
		वापस;

	/*
	 * Check अगर this was the guardian beacon,
	 * अगर that was the हाल we need to send the real beacon now.
	 * Otherwise we should मुक्त the sk_buffer, the device
	 * should be करोing the rest of the work now.
	 */
	अगर (bcn_priv->guardian_urb == urb) अणु
		usb_submit_urb(bcn_priv->urb, GFP_ATOMIC);
	पूर्ण अन्यथा अगर (bcn_priv->urb == urb) अणु
		dev_kमुक्त_skb(entry->skb);
		entry->skb = शून्य;
	पूर्ण
पूर्ण

/*
 * Device probe functions.
 */
अटल पूर्णांक rt2500usb_validate_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 word;
	u8 *mac;
	u8 bbp;

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
				   ANTENNA_SW_DIVERSITY);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RX_DEFAULT,
				   ANTENNA_SW_DIVERSITY);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_LED_MODE,
				   LED_MODE_DEFAULT);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_DYN_TXAGC, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_HARDWARE_RADIO, 0);
		rt2x00_set_field16(&word, EEPROM_ANTENNA_RF_TYPE, RF2522);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_ANTENNA, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Antenna: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_NIC);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_NIC_CARDBUS_ACCEL, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_DYN_BBP_TUNE, 0);
		rt2x00_set_field16(&word, EEPROM_NIC_CCK_TX_POWER, 0);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_NIC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "NIC: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_CALIBRATE_OFFSET);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_CALIBRATE_OFFSET_RSSI,
				   DEFAULT_RSSI_OFFSET);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_CALIBRATE_OFFSET, word);
		rt2x00_eeprom_dbg(rt2x00dev, "Calibrate offset: 0x%04x\n",
				  word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_THRESHOLD, 45);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune: 0x%04x\n", word);
	पूर्ण

	/*
	 * Switch lower vgc bound to current BBP R17 value,
	 * lower the value a bit क्रम better quality.
	 */
	bbp = rt2500usb_bbp_पढ़ो(rt2x00dev, 17);
	bbp -= 6;

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_VGC);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCUPPER, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCLOWER, bbp);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_VGC, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune vgc: 0x%04x\n", word);
	पूर्ण अन्यथा अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_VGCLOWER, bbp);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_VGC, word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R17);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R17_LOW, 0x48);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R17_HIGH, 0x41);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_R17, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r17: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R24);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R24_LOW, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R24_HIGH, 0x80);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_R24, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r24: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R25);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R25_LOW, 0x40);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R25_HIGH, 0x50);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_R25, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r25: 0x%04x\n", word);
	पूर्ण

	word = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBPTUNE_R61);
	अगर (word == 0xffff) अणु
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R61_LOW, 0x60);
		rt2x00_set_field16(&word, EEPROM_BBPTUNE_R61_HIGH, 0x6d);
		rt2x00_eeprom_ग_लिखो(rt2x00dev, EEPROM_BBPTUNE_R61, word);
		rt2x00_eeprom_dbg(rt2x00dev, "BBPtune r61: 0x%04x\n", word);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2500usb_init_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u16 reg;
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
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR0);
	rt2x00_set_chip(rt2x00dev, RT2570, value, reg);

	अगर (((reg & 0xfff0) != 0) || ((reg & 0x0000000f) == 0)) अणु
		rt2x00_err(rt2x00dev, "Invalid RT chipset detected\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!rt2x00_rf(rt2x00dev, RF2522) &&
	    !rt2x00_rf(rt2x00dev, RF2523) &&
	    !rt2x00_rf(rt2x00dev, RF2524) &&
	    !rt2x00_rf(rt2x00dev, RF2525) &&
	    !rt2x00_rf(rt2x00dev, RF2525E) &&
	    !rt2x00_rf(rt2x00dev, RF5222)) अणु
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
	 * When the eeprom indicates SW_DIVERSITY use HW_DIVERSITY instead.
	 * I am not 100% sure about this, but the legacy drivers करो not
	 * indicate antenna swapping in software is required when
	 * भागersity is enabled.
	 */
	अगर (rt2x00dev->शेष_ant.tx == ANTENNA_SW_DIVERSITY)
		rt2x00dev->शेष_ant.tx = ANTENNA_HW_DIVERSITY;
	अगर (rt2x00dev->शेष_ant.rx == ANTENNA_SW_DIVERSITY)
		rt2x00dev->शेष_ant.rx = ANTENNA_HW_DIVERSITY;

	/*
	 * Store led mode, क्रम correct led behaviour.
	 */
#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
	value = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_LED_MODE);

	rt2500usb_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	अगर (value == LED_MODE_TXRX_ACTIVITY ||
	    value == LED_MODE_DEFAULT ||
	    value == LED_MODE_ASUS)
		rt2500usb_init_led(rt2x00dev, &rt2x00dev->led_qual,
				   LED_TYPE_ACTIVITY);
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Detect अगर this device has an hardware controlled radio.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Read the RSSI <-> dBm offset inक्रमmation.
	 */
	eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_CALIBRATE_OFFSET);
	rt2x00dev->rssi_offset =
	    rt2x00_get_field16(eeprom, EEPROM_CALIBRATE_OFFSET_RSSI);

	वापस 0;
पूर्ण

/*
 * RF value list क्रम RF2522
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2522[] = अणु
	अणु 1,  0x00002050, 0x000c1fda, 0x00000101, 0 पूर्ण,
	अणु 2,  0x00002050, 0x000c1fee, 0x00000101, 0 पूर्ण,
	अणु 3,  0x00002050, 0x000c2002, 0x00000101, 0 पूर्ण,
	अणु 4,  0x00002050, 0x000c2016, 0x00000101, 0 पूर्ण,
	अणु 5,  0x00002050, 0x000c202a, 0x00000101, 0 पूर्ण,
	अणु 6,  0x00002050, 0x000c203e, 0x00000101, 0 पूर्ण,
	अणु 7,  0x00002050, 0x000c2052, 0x00000101, 0 पूर्ण,
	अणु 8,  0x00002050, 0x000c2066, 0x00000101, 0 पूर्ण,
	अणु 9,  0x00002050, 0x000c207a, 0x00000101, 0 पूर्ण,
	अणु 10, 0x00002050, 0x000c208e, 0x00000101, 0 पूर्ण,
	अणु 11, 0x00002050, 0x000c20a2, 0x00000101, 0 पूर्ण,
	अणु 12, 0x00002050, 0x000c20b6, 0x00000101, 0 पूर्ण,
	अणु 13, 0x00002050, 0x000c20ca, 0x00000101, 0 पूर्ण,
	अणु 14, 0x00002050, 0x000c20fa, 0x00000101, 0 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF2523
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2523[] = अणु
	अणु 1,  0x00022010, 0x00000c9e, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 2,  0x00022010, 0x00000ca2, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 3,  0x00022010, 0x00000ca6, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 4,  0x00022010, 0x00000caa, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 5,  0x00022010, 0x00000cae, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 6,  0x00022010, 0x00000cb2, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 7,  0x00022010, 0x00000cb6, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 8,  0x00022010, 0x00000cba, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 9,  0x00022010, 0x00000cbe, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 10, 0x00022010, 0x00000d02, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 11, 0x00022010, 0x00000d06, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 12, 0x00022010, 0x00000d0a, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 13, 0x00022010, 0x00000d0e, 0x000e0111, 0x00000a1b पूर्ण,
	अणु 14, 0x00022010, 0x00000d1a, 0x000e0111, 0x00000a03 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF2524
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2524[] = अणु
	अणु 1,  0x00032020, 0x00000c9e, 0x00000101, 0x00000a1b पूर्ण,
	अणु 2,  0x00032020, 0x00000ca2, 0x00000101, 0x00000a1b पूर्ण,
	अणु 3,  0x00032020, 0x00000ca6, 0x00000101, 0x00000a1b पूर्ण,
	अणु 4,  0x00032020, 0x00000caa, 0x00000101, 0x00000a1b पूर्ण,
	अणु 5,  0x00032020, 0x00000cae, 0x00000101, 0x00000a1b पूर्ण,
	अणु 6,  0x00032020, 0x00000cb2, 0x00000101, 0x00000a1b पूर्ण,
	अणु 7,  0x00032020, 0x00000cb6, 0x00000101, 0x00000a1b पूर्ण,
	अणु 8,  0x00032020, 0x00000cba, 0x00000101, 0x00000a1b पूर्ण,
	अणु 9,  0x00032020, 0x00000cbe, 0x00000101, 0x00000a1b पूर्ण,
	अणु 10, 0x00032020, 0x00000d02, 0x00000101, 0x00000a1b पूर्ण,
	अणु 11, 0x00032020, 0x00000d06, 0x00000101, 0x00000a1b पूर्ण,
	अणु 12, 0x00032020, 0x00000d0a, 0x00000101, 0x00000a1b पूर्ण,
	अणु 13, 0x00032020, 0x00000d0e, 0x00000101, 0x00000a1b पूर्ण,
	अणु 14, 0x00032020, 0x00000d1a, 0x00000101, 0x00000a03 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF2525
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2525[] = अणु
	अणु 1,  0x00022020, 0x00080c9e, 0x00060111, 0x00000a1b पूर्ण,
	अणु 2,  0x00022020, 0x00080ca2, 0x00060111, 0x00000a1b पूर्ण,
	अणु 3,  0x00022020, 0x00080ca6, 0x00060111, 0x00000a1b पूर्ण,
	अणु 4,  0x00022020, 0x00080caa, 0x00060111, 0x00000a1b पूर्ण,
	अणु 5,  0x00022020, 0x00080cae, 0x00060111, 0x00000a1b पूर्ण,
	अणु 6,  0x00022020, 0x00080cb2, 0x00060111, 0x00000a1b पूर्ण,
	अणु 7,  0x00022020, 0x00080cb6, 0x00060111, 0x00000a1b पूर्ण,
	अणु 8,  0x00022020, 0x00080cba, 0x00060111, 0x00000a1b पूर्ण,
	अणु 9,  0x00022020, 0x00080cbe, 0x00060111, 0x00000a1b पूर्ण,
	अणु 10, 0x00022020, 0x00080d02, 0x00060111, 0x00000a1b पूर्ण,
	अणु 11, 0x00022020, 0x00080d06, 0x00060111, 0x00000a1b पूर्ण,
	अणु 12, 0x00022020, 0x00080d0a, 0x00060111, 0x00000a1b पूर्ण,
	अणु 13, 0x00022020, 0x00080d0e, 0x00060111, 0x00000a1b पूर्ण,
	अणु 14, 0x00022020, 0x00080d1a, 0x00060111, 0x00000a03 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF2525e
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_bg_2525e[] = अणु
	अणु 1,  0x00022010, 0x0000089a, 0x00060111, 0x00000e1b पूर्ण,
	अणु 2,  0x00022010, 0x0000089e, 0x00060111, 0x00000e07 पूर्ण,
	अणु 3,  0x00022010, 0x0000089e, 0x00060111, 0x00000e1b पूर्ण,
	अणु 4,  0x00022010, 0x000008a2, 0x00060111, 0x00000e07 पूर्ण,
	अणु 5,  0x00022010, 0x000008a2, 0x00060111, 0x00000e1b पूर्ण,
	अणु 6,  0x00022010, 0x000008a6, 0x00060111, 0x00000e07 पूर्ण,
	अणु 7,  0x00022010, 0x000008a6, 0x00060111, 0x00000e1b पूर्ण,
	अणु 8,  0x00022010, 0x000008aa, 0x00060111, 0x00000e07 पूर्ण,
	अणु 9,  0x00022010, 0x000008aa, 0x00060111, 0x00000e1b पूर्ण,
	अणु 10, 0x00022010, 0x000008ae, 0x00060111, 0x00000e07 पूर्ण,
	अणु 11, 0x00022010, 0x000008ae, 0x00060111, 0x00000e1b पूर्ण,
	अणु 12, 0x00022010, 0x000008b2, 0x00060111, 0x00000e07 पूर्ण,
	अणु 13, 0x00022010, 0x000008b2, 0x00060111, 0x00000e1b पूर्ण,
	अणु 14, 0x00022010, 0x000008b6, 0x00060111, 0x00000e23 पूर्ण,
पूर्ण;

/*
 * RF value list क्रम RF5222
 * Supports: 2.4 GHz & 5.2 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_5222[] = अणु
	अणु 1,  0x00022020, 0x00001136, 0x00000101, 0x00000a0b पूर्ण,
	अणु 2,  0x00022020, 0x0000113a, 0x00000101, 0x00000a0b पूर्ण,
	अणु 3,  0x00022020, 0x0000113e, 0x00000101, 0x00000a0b पूर्ण,
	अणु 4,  0x00022020, 0x00001182, 0x00000101, 0x00000a0b पूर्ण,
	अणु 5,  0x00022020, 0x00001186, 0x00000101, 0x00000a0b पूर्ण,
	अणु 6,  0x00022020, 0x0000118a, 0x00000101, 0x00000a0b पूर्ण,
	अणु 7,  0x00022020, 0x0000118e, 0x00000101, 0x00000a0b पूर्ण,
	अणु 8,  0x00022020, 0x00001192, 0x00000101, 0x00000a0b पूर्ण,
	अणु 9,  0x00022020, 0x00001196, 0x00000101, 0x00000a0b पूर्ण,
	अणु 10, 0x00022020, 0x0000119a, 0x00000101, 0x00000a0b पूर्ण,
	अणु 11, 0x00022020, 0x0000119e, 0x00000101, 0x00000a0b पूर्ण,
	अणु 12, 0x00022020, 0x000011a2, 0x00000101, 0x00000a0b पूर्ण,
	अणु 13, 0x00022020, 0x000011a6, 0x00000101, 0x00000a0b पूर्ण,
	अणु 14, 0x00022020, 0x000011ae, 0x00000101, 0x00000a1b पूर्ण,

	/* 802.11 UNI / HyperLan 2 */
	अणु 36, 0x00022010, 0x00018896, 0x00000101, 0x00000a1f पूर्ण,
	अणु 40, 0x00022010, 0x0001889a, 0x00000101, 0x00000a1f पूर्ण,
	अणु 44, 0x00022010, 0x0001889e, 0x00000101, 0x00000a1f पूर्ण,
	अणु 48, 0x00022010, 0x000188a2, 0x00000101, 0x00000a1f पूर्ण,
	अणु 52, 0x00022010, 0x000188a6, 0x00000101, 0x00000a1f पूर्ण,
	अणु 66, 0x00022010, 0x000188aa, 0x00000101, 0x00000a1f पूर्ण,
	अणु 60, 0x00022010, 0x000188ae, 0x00000101, 0x00000a1f पूर्ण,
	अणु 64, 0x00022010, 0x000188b2, 0x00000101, 0x00000a1f पूर्ण,

	/* 802.11 HyperLan 2 */
	अणु 100, 0x00022010, 0x00008802, 0x00000101, 0x00000a0f पूर्ण,
	अणु 104, 0x00022010, 0x00008806, 0x00000101, 0x00000a0f पूर्ण,
	अणु 108, 0x00022010, 0x0000880a, 0x00000101, 0x00000a0f पूर्ण,
	अणु 112, 0x00022010, 0x0000880e, 0x00000101, 0x00000a0f पूर्ण,
	अणु 116, 0x00022010, 0x00008812, 0x00000101, 0x00000a0f पूर्ण,
	अणु 120, 0x00022010, 0x00008816, 0x00000101, 0x00000a0f पूर्ण,
	अणु 124, 0x00022010, 0x0000881a, 0x00000101, 0x00000a0f पूर्ण,
	अणु 128, 0x00022010, 0x0000881e, 0x00000101, 0x00000a0f पूर्ण,
	अणु 132, 0x00022010, 0x00008822, 0x00000101, 0x00000a0f पूर्ण,
	अणु 136, 0x00022010, 0x00008826, 0x00000101, 0x00000a0f पूर्ण,

	/* 802.11 UNII */
	अणु 140, 0x00022010, 0x0000882a, 0x00000101, 0x00000a0f पूर्ण,
	अणु 149, 0x00022020, 0x000090a6, 0x00000101, 0x00000a07 पूर्ण,
	अणु 153, 0x00022020, 0x000090ae, 0x00000101, 0x00000a07 पूर्ण,
	अणु 157, 0x00022020, 0x000090b6, 0x00000101, 0x00000a07 पूर्ण,
	अणु 161, 0x00022020, 0x000090be, 0x00000101, 0x00000a07 पूर्ण,
पूर्ण;

अटल पूर्णांक rt2500usb_probe_hw_mode(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	काष्ठा channel_info *info;
	अक्षर *tx_घातer;
	अचिन्हित पूर्णांक i;

	/*
	 * Initialize all hw fields.
	 *
	 * Don't set IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING unless we are
	 * capable of sending the buffered frames out after the DTIM
	 * transmission using rt2x00lib_beaconकरोne. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some समय.
	 */
	ieee80211_hw_set(rt2x00dev->hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);
	ieee80211_hw_set(rt2x00dev->hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);

	/*
	 * Disable घातersaving as शेष.
	 */
	rt2x00dev->hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2x00_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * Initialize hw_mode inक्रमmation.
	 */
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	अगर (rt2x00_rf(rt2x00dev, RF2522)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2522);
		spec->channels = rf_vals_bg_2522;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2523)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2523);
		spec->channels = rf_vals_bg_2523;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2524)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2524);
		spec->channels = rf_vals_bg_2524;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2525)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2525);
		spec->channels = rf_vals_bg_2525;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF2525E)) अणु
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2525e);
		spec->channels = rf_vals_bg_2525e;
	पूर्ण अन्यथा अगर (rt2x00_rf(rt2x00dev, RF5222)) अणु
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_5222);
		spec->channels = rf_vals_5222;
	पूर्ण

	/*
	 * Create channel inक्रमmation array
	 */
	info = kसुस्मृति(spec->num_channels, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	spec->channels_info = info;

	tx_घातer = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_START);
	क्रम (i = 0; i < 14; i++) अणु
		info[i].max_घातer = MAX_TXPOWER;
		info[i].शेष_घातer1 = TXPOWER_FROM_DEV(tx_घातer[i]);
	पूर्ण

	अगर (spec->num_channels > 14) अणु
		क्रम (i = 14; i < spec->num_channels; i++) अणु
			info[i].max_घातer = MAX_TXPOWER;
			info[i].शेष_घातer1 = DEFAULT_TXPOWER;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2500usb_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;
	u16 reg;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2500usb_validate_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	retval = rt2500usb_init_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Enable rfसमाप्त polling by setting GPIO direction of the
	 * rfसमाप्त चयन GPIO pin correctly.
	 */
	reg = rt2500usb_रेजिस्टर_पढ़ो(rt2x00dev, MAC_CSR19);
	rt2x00_set_field16(&reg, MAC_CSR19_सूची0, 0);
	rt2500usb_रेजिस्टर_ग_लिखो(rt2x00dev, MAC_CSR19, reg);

	/*
	 * Initialize hw specअगरications.
	 */
	retval = rt2500usb_probe_hw_mode(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * This device requires the atim queue
	 */
	__set_bit(REQUIRE_ATIM_QUEUE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_BEACON_GUARD, &rt2x00dev->cap_flags);
	अगर (!modparam_nohwcrypt) अणु
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
		__set_bit(REQUIRE_COPY_IV, &rt2x00dev->cap_flags);
	पूर्ण
	__set_bit(REQUIRE_SW_SEQNO, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt2500usb_mac80211_ops = अणु
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
	.conf_tx		= rt2x00mac_conf_tx,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.flush			= rt2x00mac_flush,
	.set_antenna		= rt2x00mac_set_antenna,
	.get_antenna		= rt2x00mac_get_antenna,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt2500usb_rt2x00_ops = अणु
	.probe_hw		= rt2500usb_probe_hw,
	.initialize		= rt2x00usb_initialize,
	.uninitialize		= rt2x00usb_uninitialize,
	.clear_entry		= rt2x00usb_clear_entry,
	.set_device_state	= rt2500usb_set_device_state,
	.rfसमाप्त_poll		= rt2500usb_rfसमाप्त_poll,
	.link_stats		= rt2500usb_link_stats,
	.reset_tuner		= rt2500usb_reset_tuner,
	.watchकरोg		= rt2x00usb_watchकरोg,
	.start_queue		= rt2500usb_start_queue,
	.kick_queue		= rt2x00usb_kick_queue,
	.stop_queue		= rt2500usb_stop_queue,
	.flush_queue		= rt2x00usb_flush_queue,
	.ग_लिखो_tx_desc		= rt2500usb_ग_लिखो_tx_desc,
	.ग_लिखो_beacon		= rt2500usb_ग_लिखो_beacon,
	.get_tx_data_len	= rt2500usb_get_tx_data_len,
	.fill_rxकरोne		= rt2500usb_fill_rxकरोne,
	.config_shared_key	= rt2500usb_config_key,
	.config_pairwise_key	= rt2500usb_config_key,
	.config_filter		= rt2500usb_config_filter,
	.config_पूर्णांकf		= rt2500usb_config_पूर्णांकf,
	.config_erp		= rt2500usb_config_erp,
	.config_ant		= rt2500usb_config_ant,
	.config			= rt2500usb_config,
पूर्ण;

अटल व्योम rt2500usb_queue_init(काष्ठा data_queue *queue)
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
		queue->limit = 1;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb_bcn);
		अवरोध;

	हाल QID_ATIM:
		queue->limit = 8;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_usb);
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rt2x00_ops rt2500usb_ops = अणु
	.name			= KBUILD_MODNAME,
	.max_ap_पूर्णांकf		= 1,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt2500usb_queue_init,
	.lib			= &rt2500usb_rt2x00_ops,
	.hw			= &rt2500usb_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt2500usb_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * rt2500usb module inक्रमmation.
 */
अटल स्थिर काष्ठा usb_device_id rt2500usb_device_table[] = अणु
	/* ASUS */
	अणु USB_DEVICE(0x0b05, 0x1706) पूर्ण,
	अणु USB_DEVICE(0x0b05, 0x1707) पूर्ण,
	/* Belkin */
	अणु USB_DEVICE(0x050d, 0x7050) पूर्ण,	/* FCC ID: K7SF5D7050A ver. 2.x */
	अणु USB_DEVICE(0x050d, 0x7051) पूर्ण,
	/* Cisco Systems */
	अणु USB_DEVICE(0x13b1, 0x000d) पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x0011) पूर्ण,
	अणु USB_DEVICE(0x13b1, 0x001a) पूर्ण,
	/* Conceptronic */
	अणु USB_DEVICE(0x14b2, 0x3c02) पूर्ण,
	/* D-LINK */
	अणु USB_DEVICE(0x2001, 0x3c00) पूर्ण,
	/* Gigabyte */
	अणु USB_DEVICE(0x1044, 0x8001) पूर्ण,
	अणु USB_DEVICE(0x1044, 0x8007) पूर्ण,
	/* Hercules */
	अणु USB_DEVICE(0x06f8, 0xe000) पूर्ण,
	/* Melco */
	अणु USB_DEVICE(0x0411, 0x005e) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0066) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0067) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x008b) पूर्ण,
	अणु USB_DEVICE(0x0411, 0x0097) पूर्ण,
	/* MSI */
	अणु USB_DEVICE(0x0db0, 0x6861) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x6865) पूर्ण,
	अणु USB_DEVICE(0x0db0, 0x6869) पूर्ण,
	/* Ralink */
	अणु USB_DEVICE(0x148f, 0x1706) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x2570) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x9020) पूर्ण,
	/* Sagem */
	अणु USB_DEVICE(0x079b, 0x004b) पूर्ण,
	/* Siemens */
	अणु USB_DEVICE(0x0681, 0x3c06) पूर्ण,
	/* SMC */
	अणु USB_DEVICE(0x0707, 0xee13) पूर्ण,
	/* Spairon */
	अणु USB_DEVICE(0x114b, 0x0110) पूर्ण,
	/* SURECOM */
	अणु USB_DEVICE(0x0769, 0x11f3) पूर्ण,
	/* Trust */
	अणु USB_DEVICE(0x0eb0, 0x9020) पूर्ण,
	/* VTech */
	अणु USB_DEVICE(0x0f88, 0x3012) पूर्ण,
	/* Zinwell */
	अणु USB_DEVICE(0x5a57, 0x0260) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2500 USB Wireless LAN driver.");
MODULE_DEVICE_TABLE(usb, rt2500usb_device_table);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt2500usb_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	वापस rt2x00usb_probe(usb_पूर्णांकf, &rt2500usb_ops);
पूर्ण

अटल काष्ठा usb_driver rt2500usb_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt2500usb_device_table,
	.probe		= rt2500usb_probe,
	.disconnect	= rt2x00usb_disconnect,
	.suspend	= rt2x00usb_suspend,
	.resume		= rt2x00usb_resume,
	.reset_resume	= rt2x00usb_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rt2500usb_driver);

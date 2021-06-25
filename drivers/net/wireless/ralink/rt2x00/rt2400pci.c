<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2400pci
	Abstract: rt2400pci device specअगरic routines.
	Supported chipsets: RT2460.
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/eeprom_93cx6.h>
#समावेश <linux/slab.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00mmio.h"
#समावेश "rt2x00pci.h"
#समावेश "rt2400pci.h"

/*
 * Register access.
 * All access to the CSR रेजिस्टरs will go through the methods
 * rt2x00mmio_रेजिस्टर_पढ़ो and rt2x00mmio_रेजिस्टर_ग_लिखो.
 * BBP and RF रेजिस्टर require indirect रेजिस्टर access,
 * and use the CSR रेजिस्टरs BBPCSR and RFCSR to achieve this.
 * These indirect रेजिस्टरs work with busy bits,
 * and we will try maximal REGISTER_BUSY_COUNT बार to access
 * the रेजिस्टर जबतक taking a REGISTER_BUSY_DELAY us delay
 * between each attempt. When the busy bit is still set at that समय,
 * the access attempt is considered to have failed,
 * and we will prपूर्णांक an error.
 */
#घोषणा WAIT_FOR_BBP(__dev, __reg) \
	rt2x00mmio_regbusy_पढ़ो((__dev), BBPCSR, BBPCSR_BUSY, (__reg))
#घोषणा WAIT_FOR_RF(__dev, __reg) \
	rt2x00mmio_regbusy_पढ़ो((__dev), RFCSR, RFCSR_BUSY, (__reg))

अटल व्योम rt2400pci_bbp_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt2x00_set_field32(&reg, BBPCSR_VALUE, value);
		rt2x00_set_field32(&reg, BBPCSR_REGNUM, word);
		rt2x00_set_field32(&reg, BBPCSR_BUSY, 1);
		rt2x00_set_field32(&reg, BBPCSR_WRITE_CONTROL, 1);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BBPCSR, reg);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल u8 rt2400pci_bbp_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt2x00_set_field32(&reg, BBPCSR_REGNUM, word);
		rt2x00_set_field32(&reg, BBPCSR_BUSY, 1);
		rt2x00_set_field32(&reg, BBPCSR_WRITE_CONTROL, 0);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BBPCSR, reg);

		WAIT_FOR_BBP(rt2x00dev, &reg);
	पूर्ण

	value = rt2x00_get_field32(reg, BBPCSR_VALUE);

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस value;
पूर्ण

अटल व्योम rt2400pci_rf_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
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
		rt2x00_set_field32(&reg, RFCSR_VALUE, value);
		rt2x00_set_field32(&reg, RFCSR_NUMBER_OF_BITS, 20);
		rt2x00_set_field32(&reg, RFCSR_IF_SELECT, 0);
		rt2x00_set_field32(&reg, RFCSR_BUSY, 1);

		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RFCSR, reg);
		rt2x00_rf_ग_लिखो(rt2x00dev, word, value);
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);
पूर्ण

अटल व्योम rt2400pci_eepromरेजिस्टर_पढ़ो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR21);

	eeprom->reg_data_in = !!rt2x00_get_field32(reg, CSR21_EEPROM_DATA_IN);
	eeprom->reg_data_out = !!rt2x00_get_field32(reg, CSR21_EEPROM_DATA_OUT);
	eeprom->reg_data_घड़ी =
	    !!rt2x00_get_field32(reg, CSR21_EEPROM_DATA_CLOCK);
	eeprom->reg_chip_select =
	    !!rt2x00_get_field32(reg, CSR21_EEPROM_CHIP_SELECT);
पूर्ण

अटल व्योम rt2400pci_eepromरेजिस्टर_ग_लिखो(काष्ठा eeprom_93cx6 *eeprom)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = eeprom->data;
	u32 reg = 0;

	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_IN, !!eeprom->reg_data_in);
	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_OUT, !!eeprom->reg_data_out);
	rt2x00_set_field32(&reg, CSR21_EEPROM_DATA_CLOCK,
			   !!eeprom->reg_data_घड़ी);
	rt2x00_set_field32(&reg, CSR21_EEPROM_CHIP_SELECT,
			   !!eeprom->reg_chip_select);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR21, reg);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
अटल स्थिर काष्ठा rt2x00debug rt2400pci_rt2x00debug = अणु
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
		.पढ़ो		= rt2400pci_bbp_पढ़ो,
		.ग_लिखो		= rt2400pci_bbp_ग_लिखो,
		.word_base	= BBP_BASE,
		.word_size	= माप(u8),
		.word_count	= BBP_SIZE / माप(u8),
	पूर्ण,
	.rf	= अणु
		.पढ़ो		= rt2x00_rf_पढ़ो,
		.ग_लिखो		= rt2400pci_rf_ग_लिखो,
		.word_base	= RF_BASE,
		.word_size	= माप(u32),
		.word_count	= RF_SIZE / माप(u32),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */

अटल पूर्णांक rt2400pci_rfसमाप्त_poll(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, GPIOCSR);
	वापस rt2x00_get_field32(reg, GPIOCSR_VAL0);
पूर्ण

#अगर_घोषित CONFIG_RT2X00_LIB_LEDS
अटल व्योम rt2400pci_brightness_set(काष्ठा led_classdev *led_cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	अचिन्हित पूर्णांक enabled = brightness != LED_OFF;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(led->rt2x00dev, LEDCSR);

	अगर (led->type == LED_TYPE_RADIO || led->type == LED_TYPE_ASSOC)
		rt2x00_set_field32(&reg, LEDCSR_LINK, enabled);
	अन्यथा अगर (led->type == LED_TYPE_ACTIVITY)
		rt2x00_set_field32(&reg, LEDCSR_ACTIVITY, enabled);

	rt2x00mmio_रेजिस्टर_ग_लिखो(led->rt2x00dev, LEDCSR, reg);
पूर्ण

अटल पूर्णांक rt2400pci_blink_set(काष्ठा led_classdev *led_cdev,
			       अचिन्हित दीर्घ *delay_on,
			       अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा rt2x00_led *led =
	    container_of(led_cdev, काष्ठा rt2x00_led, led_dev);
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(led->rt2x00dev, LEDCSR);
	rt2x00_set_field32(&reg, LEDCSR_ON_PERIOD, *delay_on);
	rt2x00_set_field32(&reg, LEDCSR_OFF_PERIOD, *delay_off);
	rt2x00mmio_रेजिस्टर_ग_लिखो(led->rt2x00dev, LEDCSR, reg);

	वापस 0;
पूर्ण

अटल व्योम rt2400pci_init_led(काष्ठा rt2x00_dev *rt2x00dev,
			       काष्ठा rt2x00_led *led,
			       क्रमागत led_type type)
अणु
	led->rt2x00dev = rt2x00dev;
	led->type = type;
	led->led_dev.brightness_set = rt2400pci_brightness_set;
	led->led_dev.blink_set = rt2400pci_blink_set;
	led->flags = LED_INITIALIZED;
पूर्ण
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

/*
 * Configuration handlers.
 */
अटल व्योम rt2400pci_config_filter(काष्ठा rt2x00_dev *rt2x00dev,
				    स्थिर अचिन्हित पूर्णांक filter_flags)
अणु
	u32 reg;

	/*
	 * Start configuration steps.
	 * Note that the version error will always be dropped
	 * since there is no filter क्रम it at this समय.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR0);
	rt2x00_set_field32(&reg, RXCSR0_DROP_CRC,
			   !(filter_flags & FIF_FCSFAIL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_PHYSICAL,
			   !(filter_flags & FIF_PLCPFAIL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_CONTROL,
			   !(filter_flags & FIF_CONTROL));
	rt2x00_set_field32(&reg, RXCSR0_DROP_NOT_TO_ME,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags));
	rt2x00_set_field32(&reg, RXCSR0_DROP_TODS,
			   !test_bit(CONFIG_MONITORING, &rt2x00dev->flags) &&
			   !rt2x00dev->पूर्णांकf_ap_count);
	rt2x00_set_field32(&reg, RXCSR0_DROP_VERSION_ERROR, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR0, reg);
पूर्ण

अटल व्योम rt2400pci_config_पूर्णांकf(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा rt2x00_पूर्णांकf *पूर्णांकf,
				  काष्ठा rt2x00पूर्णांकf_conf *conf,
				  स्थिर अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक bcn_preload;
	u32 reg;

	अगर (flags & CONFIG_UPDATE_TYPE) अणु
		/*
		 * Enable beacon config
		 */
		bcn_preload = PREAMBLE + GET_DURATION(IEEE80211_HEADER, 20);
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, BCNCSR1);
		rt2x00_set_field32(&reg, BCNCSR1_PRELOAD, bcn_preload);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, BCNCSR1, reg);

		/*
		 * Enable synchronisation.
		 */
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR14);
		rt2x00_set_field32(&reg, CSR14_TSF_SYNC, conf->sync);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);
	पूर्ण

	अगर (flags & CONFIG_UPDATE_MAC)
		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, CSR3,
					       conf->mac, माप(conf->mac));

	अगर (flags & CONFIG_UPDATE_BSSID)
		rt2x00mmio_रेजिस्टर_multiग_लिखो(rt2x00dev, CSR5,
					       conf->bssid,
					       माप(conf->bssid));
पूर्ण

अटल व्योम rt2400pci_config_erp(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा rt2x00lib_erp *erp,
				 u32 changed)
अणु
	पूर्णांक preamble_mask;
	u32 reg;

	/*
	 * When लघु preamble is enabled, we should set bit 0x08
	 */
	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		preamble_mask = erp->लघु_preamble << 3;

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR1);
		rt2x00_set_field32(&reg, TXCSR1_ACK_TIMEOUT, 0x1ff);
		rt2x00_set_field32(&reg, TXCSR1_ACK_CONSUME_TIME, 0x13a);
		rt2x00_set_field32(&reg, TXCSR1_TSF_OFFSET, IEEE80211_HEADER);
		rt2x00_set_field32(&reg, TXCSR1_AUTORESPONDER, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR1, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, ARCSR2);
		rt2x00_set_field32(&reg, ARCSR2_SIGNAL, 0x00);
		rt2x00_set_field32(&reg, ARCSR2_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 10));
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR2, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, ARCSR3);
		rt2x00_set_field32(&reg, ARCSR3_SIGNAL, 0x01 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR3_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 20));
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR3, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, ARCSR4);
		rt2x00_set_field32(&reg, ARCSR4_SIGNAL, 0x02 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR4_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 55));
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR4, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, ARCSR5);
		rt2x00_set_field32(&reg, ARCSR5_SIGNAL, 0x03 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR5_SERVICE, 0x84);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 110));
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR5, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES)
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR1, erp->basic_rates);

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR11);
		rt2x00_set_field32(&reg, CSR11_SLOT_TIME, erp->slot_समय);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR11, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR18);
		rt2x00_set_field32(&reg, CSR18_SIFS, erp->sअगरs);
		rt2x00_set_field32(&reg, CSR18_PIFS, erp->pअगरs);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR18, reg);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR19);
		rt2x00_set_field32(&reg, CSR19_DIFS, erp->dअगरs);
		rt2x00_set_field32(&reg, CSR19_EIFS, erp->eअगरs);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR19, reg);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR12);
		rt2x00_set_field32(&reg, CSR12_BEACON_INTERVAL,
				   erp->beacon_पूर्णांक * 16);
		rt2x00_set_field32(&reg, CSR12_CFP_MAX_DURATION,
				   erp->beacon_पूर्णांक * 16);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR12, reg);
	पूर्ण
पूर्ण

अटल व्योम rt2400pci_config_ant(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा antenna_setup *ant)
अणु
	u8 r1;
	u8 r4;

	/*
	 * We should never come here because rt2x00lib is supposed
	 * to catch this and send us the correct antenna explicitely.
	 */
	BUG_ON(ant->rx == ANTENNA_SW_DIVERSITY ||
	       ant->tx == ANTENNA_SW_DIVERSITY);

	r4 = rt2400pci_bbp_पढ़ो(rt2x00dev, 4);
	r1 = rt2400pci_bbp_पढ़ो(rt2x00dev, 1);

	/*
	 * Configure the TX antenna.
	 */
	चयन (ant->tx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 1);
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 0);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 2);
		अवरोध;
	पूर्ण

	/*
	 * Configure the RX antenna.
	 */
	चयन (ant->rx) अणु
	हाल ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 1);
		अवरोध;
	हाल ANTENNA_A:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 0);
		अवरोध;
	हाल ANTENNA_B:
	शेष:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 2);
		अवरोध;
	पूर्ण

	rt2400pci_bbp_ग_लिखो(rt2x00dev, 4, r4);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 1, r1);
पूर्ण

अटल व्योम rt2400pci_config_channel(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा rf_channel *rf)
अणु
	/*
	 * Switch on tuning bits.
	 */
	rt2x00_set_field32(&rf->rf1, RF1_TUNER, 1);
	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 1);

	rt2400pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3);

	/*
	 * RF2420 chipset करोn't need any additional actions.
	 */
	अगर (rt2x00_rf(rt2x00dev, RF2420))
		वापस;

	/*
	 * For the RT2421 chipsets we need to ग_लिखो an invalid
	 * reference घड़ी rate to activate स्वतः_tune.
	 * After that we set the value back to the correct channel.
	 */
	rt2400pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 2, 0x000c2a32);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3);

	msleep(1);

	rt2400pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 2, rf->rf2);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3);

	msleep(1);

	/*
	 * Switch off tuning bits.
	 */
	rt2x00_set_field32(&rf->rf1, RF1_TUNER, 0);
	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 0);

	rt2400pci_rf_ग_लिखो(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_ग_लिखो(rt2x00dev, 3, rf->rf3);

	/*
	 * Clear false CRC during channel चयन.
	 */
	rf->rf1 = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CNT0);
पूर्ण

अटल व्योम rt2400pci_config_txघातer(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक txघातer)
अणु
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 3, TXPOWER_TO_DEV(txघातer));
पूर्ण

अटल व्योम rt2400pci_config_retry_limit(काष्ठा rt2x00_dev *rt2x00dev,
					 काष्ठा rt2x00lib_conf *libconf)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR11);
	rt2x00_set_field32(&reg, CSR11_LONG_RETRY,
			   libconf->conf->दीर्घ_frame_max_tx_count);
	rt2x00_set_field32(&reg, CSR11_SHORT_RETRY,
			   libconf->conf->लघु_frame_max_tx_count);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR11, reg);
पूर्ण

अटल व्योम rt2400pci_config_ps(काष्ठा rt2x00_dev *rt2x00dev,
				काष्ठा rt2x00lib_conf *libconf)
अणु
	क्रमागत dev_state state =
	    (libconf->conf->flags & IEEE80211_CONF_PS) ?
		STATE_SLEEP : STATE_AWAKE;
	u32 reg;

	अगर (state == STATE_SLEEP) अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR20);
		rt2x00_set_field32(&reg, CSR20_DELAY_AFTER_TBCN,
				   (rt2x00dev->beacon_पूर्णांक - 20) * 16);
		rt2x00_set_field32(&reg, CSR20_TBCN_BEFORE_WAKEUP,
				   libconf->conf->listen_पूर्णांकerval - 1);

		/* We must first disable स्वतःwake beक्रमe it can be enabled */
		rt2x00_set_field32(&reg, CSR20_AUTOWAKE, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR20, reg);

		rt2x00_set_field32(&reg, CSR20_AUTOWAKE, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR20, reg);
	पूर्ण अन्यथा अणु
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR20);
		rt2x00_set_field32(&reg, CSR20_AUTOWAKE, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR20, reg);
	पूर्ण

	rt2x00dev->ops->lib->set_device_state(rt2x00dev, state);
पूर्ण

अटल व्योम rt2400pci_config(काष्ठा rt2x00_dev *rt2x00dev,
			     काष्ठा rt2x00lib_conf *libconf,
			     स्थिर अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & IEEE80211_CONF_CHANGE_CHANNEL)
		rt2400pci_config_channel(rt2x00dev, &libconf->rf);
	अगर (flags & IEEE80211_CONF_CHANGE_POWER)
		rt2400pci_config_txघातer(rt2x00dev,
					 libconf->conf->घातer_level);
	अगर (flags & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		rt2400pci_config_retry_limit(rt2x00dev, libconf);
	अगर (flags & IEEE80211_CONF_CHANGE_PS)
		rt2400pci_config_ps(rt2x00dev, libconf);
पूर्ण

अटल व्योम rt2400pci_config_cw(काष्ठा rt2x00_dev *rt2x00dev,
				स्थिर पूर्णांक cw_min, स्थिर पूर्णांक cw_max)
अणु
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR11);
	rt2x00_set_field32(&reg, CSR11_CWMIN, cw_min);
	rt2x00_set_field32(&reg, CSR11_CWMAX, cw_max);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR11, reg);
पूर्ण

/*
 * Link tuning
 */
अटल व्योम rt2400pci_link_stats(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा link_qual *qual)
अणु
	u32 reg;
	u8 bbp;

	/*
	 * Update FCS error count from रेजिस्टर.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CNT0);
	qual->rx_failed = rt2x00_get_field32(reg, CNT0_FCS_ERROR);

	/*
	 * Update False CCA count from रेजिस्टर.
	 */
	bbp = rt2400pci_bbp_पढ़ो(rt2x00dev, 39);
	qual->false_cca = bbp;
पूर्ण

अटल अंतरभूत व्योम rt2400pci_set_vgc(काष्ठा rt2x00_dev *rt2x00dev,
				     काष्ठा link_qual *qual, u8 vgc_level)
अणु
	अगर (qual->vgc_level_reg != vgc_level) अणु
		rt2400pci_bbp_ग_लिखो(rt2x00dev, 13, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	पूर्ण
पूर्ण

अटल व्योम rt2400pci_reset_tuner(काष्ठा rt2x00_dev *rt2x00dev,
				  काष्ठा link_qual *qual)
अणु
	rt2400pci_set_vgc(rt2x00dev, qual, 0x08);
पूर्ण

अटल व्योम rt2400pci_link_tuner(काष्ठा rt2x00_dev *rt2x00dev,
				 काष्ठा link_qual *qual, स्थिर u32 count)
अणु
	/*
	 * The link tuner should not run दीर्घer then 60 seconds,
	 * and should run once every 2 seconds.
	 */
	अगर (count > 60 || !(count & 1))
		वापस;

	/*
	 * Base r13 link tuning on the false cca count.
	 */
	अगर ((qual->false_cca > 512) && (qual->vgc_level < 0x20))
		rt2400pci_set_vgc(rt2x00dev, qual, ++qual->vgc_level);
	अन्यथा अगर ((qual->false_cca < 100) && (qual->vgc_level > 0x08))
		rt2400pci_set_vgc(rt2x00dev, qual, --qual->vgc_level);
पूर्ण

/*
 * Queue handlers.
 */
अटल व्योम rt2400pci_start_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR0);
		rt2x00_set_field32(&reg, RXCSR0_DISABLE_RX, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR14);
		rt2x00_set_field32(&reg, CSR14_TSF_COUNT, 1);
		rt2x00_set_field32(&reg, CSR14_TBCN, 1);
		rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt2400pci_kick_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_PRIO, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR0, reg);
		अवरोध;
	हाल QID_AC_VI:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_TX, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR0, reg);
		अवरोध;
	हाल QID_ATIM:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_KICK_ATIM, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR0, reg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rt2400pci_stop_queue(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_ATIM:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR0);
		rt2x00_set_field32(&reg, TXCSR0_ABORT, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR0, reg);
		अवरोध;
	हाल QID_RX:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR0);
		rt2x00_set_field32(&reg, RXCSR0_DISABLE_RX, 1);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR0, reg);
		अवरोध;
	हाल QID_BEACON:
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR14);
		rt2x00_set_field32(&reg, CSR14_TSF_COUNT, 0);
		rt2x00_set_field32(&reg, CSR14_TBCN, 0);
		rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);

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
 * Initialization functions.
 */
अटल bool rt2400pci_get_entry_state(काष्ठा queue_entry *entry)
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

अटल व्योम rt2400pci_clear_entry(काष्ठा queue_entry *entry)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	काष्ठा skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	u32 word;

	अगर (entry->queue->qid == QID_RX) अणु
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 2);
		rt2x00_set_field32(&word, RXD_W2_BUFFER_LENGTH, entry->skb->len);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 2, word);

		word = rt2x00_desc_पढ़ो(entry_priv->desc, 1);
		rt2x00_set_field32(&word, RXD_W1_BUFFER_ADDRESS, skbdesc->skb_dma);
		rt2x00_desc_ग_लिखो(entry_priv->desc, 1, word);

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

अटल पूर्णांक rt2400pci_init_queues(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा queue_entry_priv_mmio *entry_priv;
	u32 reg;

	/*
	 * Initialize रेजिस्टरs.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR2);
	rt2x00_set_field32(&reg, TXCSR2_TXD_SIZE, rt2x00dev->tx[0].desc_size);
	rt2x00_set_field32(&reg, TXCSR2_NUM_TXD, rt2x00dev->tx[1].limit);
	rt2x00_set_field32(&reg, TXCSR2_NUM_ATIM, rt2x00dev->atim->limit);
	rt2x00_set_field32(&reg, TXCSR2_NUM_PRIO, rt2x00dev->tx[0].limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR2, reg);

	entry_priv = rt2x00dev->tx[1].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR3);
	rt2x00_set_field32(&reg, TXCSR3_TX_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR3, reg);

	entry_priv = rt2x00dev->tx[0].entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR5);
	rt2x00_set_field32(&reg, TXCSR5_PRIO_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR5, reg);

	entry_priv = rt2x00dev->atim->entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR4);
	rt2x00_set_field32(&reg, TXCSR4_ATIM_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR4, reg);

	entry_priv = rt2x00dev->bcn->entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TXCSR6);
	rt2x00_set_field32(&reg, TXCSR6_BEACON_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TXCSR6, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR1);
	rt2x00_set_field32(&reg, RXCSR1_RXD_SIZE, rt2x00dev->rx->desc_size);
	rt2x00_set_field32(&reg, RXCSR1_NUM_RXD, rt2x00dev->rx->limit);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR1, reg);

	entry_priv = rt2x00dev->rx->entries[0].priv_data;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR2);
	rt2x00_set_field32(&reg, RXCSR2_RX_RING_REGISTER,
			   entry_priv->desc_dma);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR2, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2400pci_init_रेजिस्टरs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	u32 reg;

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PSCSR0, 0x00020002);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PSCSR1, 0x00000002);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PSCSR2, 0x00023f20);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PSCSR3, 0x00000002);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, TIMECSR);
	rt2x00_set_field32(&reg, TIMECSR_US_COUNT, 33);
	rt2x00_set_field32(&reg, TIMECSR_US_64_COUNT, 63);
	rt2x00_set_field32(&reg, TIMECSR_BEACON_EXPECT, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, TIMECSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR9);
	rt2x00_set_field32(&reg, CSR9_MAX_FRAME_UNIT,
			   (rt2x00dev->rx->data_size / 128));
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR9, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR14);
	rt2x00_set_field32(&reg, CSR14_TSF_COUNT, 0);
	rt2x00_set_field32(&reg, CSR14_TSF_SYNC, 0);
	rt2x00_set_field32(&reg, CSR14_TBCN, 0);
	rt2x00_set_field32(&reg, CSR14_TCFP, 0);
	rt2x00_set_field32(&reg, CSR14_TATIMW, 0);
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 0);
	rt2x00_set_field32(&reg, CSR14_CFP_COUNT_PRELOAD, 0);
	rt2x00_set_field32(&reg, CSR14_TBCM_PRELOAD, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CNT3, 0x3f080000);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, ARCSR0);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_DATA0, 133);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_ID0, 134);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_DATA1, 136);
	rt2x00_set_field32(&reg, ARCSR0_AR_BBP_ID1, 135);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, ARCSR0, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RXCSR3);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0, 3); /* Tx घातer.*/
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1, 32); /* Signal */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2, 36); /* Rssi */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2_VALID, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RXCSR3, reg);

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWRCSR0, 0x3f3b3100);

	अगर (rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_AWAKE))
		वापस -EBUSY;

	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MACCSR0, 0x00217223);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MACCSR1, 0x00235518);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, MACCSR2);
	rt2x00_set_field32(&reg, MACCSR2_DELAY, 64);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, MACCSR2, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, RALINKCSR);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA0, 17);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID0, 154);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA1, 0);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID1, 154);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, RALINKCSR, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR1);
	rt2x00_set_field32(&reg, CSR1_SOFT_RESET, 1);
	rt2x00_set_field32(&reg, CSR1_BBP_RESET, 0);
	rt2x00_set_field32(&reg, CSR1_HOST_READY, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR1, reg);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR1);
	rt2x00_set_field32(&reg, CSR1_SOFT_RESET, 0);
	rt2x00_set_field32(&reg, CSR1_HOST_READY, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR1, reg);

	/*
	 * We must clear the FCS and FIFO error count.
	 * These रेजिस्टरs are cleared on पढ़ो,
	 * so we may pass a useless variable to store the value.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CNT0);
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CNT4);

	वापस 0;
पूर्ण

अटल पूर्णांक rt2400pci_रुको_bbp_पढ़ोy(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u8 value;

	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		value = rt2400pci_bbp_पढ़ो(rt2x00dev, 0);
		अगर ((value != 0xff) && (value != 0x00))
			वापस 0;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "BBP register access failed, aborting\n");
	वापस -EACCES;
पूर्ण

अटल पूर्णांक rt2400pci_init_bbp(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अचिन्हित पूर्णांक i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	अगर (unlikely(rt2400pci_रुको_bbp_पढ़ोy(rt2x00dev)))
		वापस -EACCES;

	rt2400pci_bbp_ग_लिखो(rt2x00dev, 1, 0x00);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 3, 0x27);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 4, 0x08);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 10, 0x0f);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 15, 0x72);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 16, 0x74);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 17, 0x20);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 18, 0x72);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 19, 0x0b);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 20, 0x00);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 28, 0x11);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 29, 0x04);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 30, 0x21);
	rt2400pci_bbp_ग_लिखो(rt2x00dev, 31, 0x00);

	क्रम (i = 0; i < EEPROM_BBP_SIZE; i++) अणु
		eeprom = rt2x00_eeprom_पढ़ो(rt2x00dev, EEPROM_BBP_START + i);

		अगर (eeprom != 0xffff && eeprom != 0x0000) अणु
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2400pci_bbp_ग_लिखो(rt2x00dev, reg_id, value);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Device state चयन handlers.
 */
अटल व्योम rt2400pci_toggle_irq(काष्ठा rt2x00_dev *rt2x00dev,
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
		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR7);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR7, reg);
	पूर्ण

	/*
	 * Only toggle the पूर्णांकerrupts bits we are going to use.
	 * Non-checked पूर्णांकerrupt bits are disabled by शेष.
	 */
	spin_lock_irqsave(&rt2x00dev->irqmask_lock, flags);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR8);
	rt2x00_set_field32(&reg, CSR8_TBCN_EXPIRE, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, mask);
	rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, mask);
	rt2x00_set_field32(&reg, CSR8_RXDONE, mask);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR8, reg);

	spin_unlock_irqrestore(&rt2x00dev->irqmask_lock, flags);

	अगर (state == STATE_RADIO_IRQ_OFF) अणु
		/*
		 * Ensure that all tasklets are finished beक्रमe
		 * disabling the पूर्णांकerrupts.
		 */
		tasklet_समाप्त(&rt2x00dev->txstatus_tasklet);
		tasklet_समाप्त(&rt2x00dev->rxकरोne_tasklet);
		tasklet_समाप्त(&rt2x00dev->tbtt_tasklet);
	पूर्ण
पूर्ण

अटल पूर्णांक rt2400pci_enable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Initialize all रेजिस्टरs.
	 */
	अगर (unlikely(rt2400pci_init_queues(rt2x00dev) ||
		     rt2400pci_init_रेजिस्टरs(rt2x00dev) ||
		     rt2400pci_init_bbp(rt2x00dev)))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम rt2400pci_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	/*
	 * Disable घातer
	 */
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWRCSR0, 0);
पूर्ण

अटल पूर्णांक rt2400pci_set_state(काष्ठा rt2x00_dev *rt2x00dev,
			       क्रमागत dev_state state)
अणु
	u32 reg, reg2;
	अचिन्हित पूर्णांक i;
	अक्षर put_to_sleep;
	अक्षर bbp_state;
	अक्षर rf_state;

	put_to_sleep = (state != STATE_AWAKE);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, PWRCSR1);
	rt2x00_set_field32(&reg, PWRCSR1_SET_STATE, 1);
	rt2x00_set_field32(&reg, PWRCSR1_BBP_DESIRE_STATE, state);
	rt2x00_set_field32(&reg, PWRCSR1_RF_DESIRE_STATE, state);
	rt2x00_set_field32(&reg, PWRCSR1_PUT_TO_SLEEP, put_to_sleep);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWRCSR1, reg);

	/*
	 * Device is not guaranteed to be in the requested state yet.
	 * We must रुको until the रेजिस्टर indicates that the
	 * device has entered the correct state.
	 */
	क्रम (i = 0; i < REGISTER_BUSY_COUNT; i++) अणु
		reg2 = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, PWRCSR1);
		bbp_state = rt2x00_get_field32(reg2, PWRCSR1_BBP_CURR_STATE);
		rf_state = rt2x00_get_field32(reg2, PWRCSR1_RF_CURR_STATE);
		अगर (bbp_state == state && rf_state == state)
			वापस 0;
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, PWRCSR1, reg);
		msleep(10);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rt2400pci_set_device_state(काष्ठा rt2x00_dev *rt2x00dev,
				      क्रमागत dev_state state)
अणु
	पूर्णांक retval = 0;

	चयन (state) अणु
	हाल STATE_RADIO_ON:
		retval = rt2400pci_enable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_OFF:
		rt2400pci_disable_radio(rt2x00dev);
		अवरोध;
	हाल STATE_RADIO_IRQ_ON:
	हाल STATE_RADIO_IRQ_OFF:
		rt2400pci_toggle_irq(rt2x00dev, state);
		अवरोध;
	हाल STATE_DEEP_SLEEP:
	हाल STATE_SLEEP:
	हाल STATE_STANDBY:
	हाल STATE_AWAKE:
		retval = rt2400pci_set_state(rt2x00dev, state);
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
अटल व्योम rt2400pci_ग_लिखो_tx_desc(काष्ठा queue_entry *entry,
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
	rt2x00_set_field32(&word, TXD_W1_BUFFER_ADDRESS, skbdesc->skb_dma);
	rt2x00_desc_ग_लिखो(txd, 1, word);

	word = rt2x00_desc_पढ़ो(txd, 2);
	rt2x00_set_field32(&word, TXD_W2_BUFFER_LENGTH, txdesc->length);
	rt2x00_set_field32(&word, TXD_W2_DATABYTE_COUNT, txdesc->length);
	rt2x00_desc_ग_लिखो(txd, 2, word);

	word = rt2x00_desc_पढ़ो(txd, 3);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SIGNAL, txdesc->u.plcp.संकेत);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SIGNAL_REGNUM, 5);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SIGNAL_BUSY, 1);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SERVICE, txdesc->u.plcp.service);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SERVICE_REGNUM, 6);
	rt2x00_set_field32(&word, TXD_W3_PLCP_SERVICE_BUSY, 1);
	rt2x00_desc_ग_लिखो(txd, 3, word);

	word = rt2x00_desc_पढ़ो(txd, 4);
	rt2x00_set_field32(&word, TXD_W4_PLCP_LENGTH_LOW,
			   txdesc->u.plcp.length_low);
	rt2x00_set_field32(&word, TXD_W3_PLCP_LENGTH_LOW_REGNUM, 8);
	rt2x00_set_field32(&word, TXD_W3_PLCP_LENGTH_LOW_BUSY, 1);
	rt2x00_set_field32(&word, TXD_W4_PLCP_LENGTH_HIGH,
			   txdesc->u.plcp.length_high);
	rt2x00_set_field32(&word, TXD_W3_PLCP_LENGTH_HIGH_REGNUM, 7);
	rt2x00_set_field32(&word, TXD_W3_PLCP_LENGTH_HIGH_BUSY, 1);
	rt2x00_desc_ग_लिखो(txd, 4, word);

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
	rt2x00_set_field32(&word, TXD_W0_RTS,
			   test_bit(ENTRY_TXD_RTS_FRAME, &txdesc->flags));
	rt2x00_set_field32(&word, TXD_W0_IFS, txdesc->u.plcp.अगरs);
	rt2x00_set_field32(&word, TXD_W0_RETRY_MODE,
			   test_bit(ENTRY_TXD_RETRY_MODE, &txdesc->flags));
	rt2x00_desc_ग_लिखो(txd, 0, word);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_len = TXD_DESC_SIZE;
पूर्ण

/*
 * TX data initialization
 */
अटल व्योम rt2400pci_ग_लिखो_beacon(काष्ठा queue_entry *entry,
				   काष्ठा txentry_desc *txdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 reg;

	/*
	 * Disable beaconing जबतक we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR14);
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);

	अगर (rt2x00queue_map_txskb(entry)) अणु
		rt2x00_err(rt2x00dev, "Fail to map beacon, aborting\n");
		जाओ out;
	पूर्ण
	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 1);
	/*
	 * Write the TX descriptor क्रम the beacon.
	 */
	rt2400pci_ग_लिखो_tx_desc(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry);
out:
	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR14, reg);
पूर्ण

/*
 * RX control handlers
 */
अटल व्योम rt2400pci_fill_rxकरोne(काष्ठा queue_entry *entry,
				  काष्ठा rxकरोne_entry_desc *rxdesc)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा queue_entry_priv_mmio *entry_priv = entry->priv_data;
	u32 word0;
	u32 word2;
	u32 word3;
	u32 word4;
	u64 tsf;
	u32 rx_low;
	u32 rx_high;

	word0 = rt2x00_desc_पढ़ो(entry_priv->desc, 0);
	word2 = rt2x00_desc_पढ़ो(entry_priv->desc, 2);
	word3 = rt2x00_desc_पढ़ो(entry_priv->desc, 3);
	word4 = rt2x00_desc_पढ़ो(entry_priv->desc, 4);

	अगर (rt2x00_get_field32(word0, RXD_W0_CRC_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_FCS_CRC;
	अगर (rt2x00_get_field32(word0, RXD_W0_PHYSICAL_ERROR))
		rxdesc->flags |= RX_FLAG_FAILED_PLCP_CRC;

	/*
	 * We only get the lower 32bits from the बारtamp,
	 * to get the full 64bits we must complement it with
	 * the बारtamp from get_tsf().
	 * Note that when a wraparound of the lower 32bits
	 * has occurred between the frame arrival and the get_tsf()
	 * call, we must decrease the higher 32bits with 1 to get
	 * to correct value.
	 */
	tsf = rt2x00dev->ops->hw->get_tsf(rt2x00dev->hw, शून्य);
	rx_low = rt2x00_get_field32(word4, RXD_W4_RX_END_TIME);
	rx_high = upper_32_bits(tsf);

	अगर ((u32)tsf <= rx_low)
		rx_high--;

	/*
	 * Obtain the status about this packet.
	 * The संकेत is the PLCP value, and needs to be stripped
	 * of the preamble bit (0x08).
	 */
	rxdesc->बारtamp = ((u64)rx_high << 32) | rx_low;
	rxdesc->संकेत = rt2x00_get_field32(word2, RXD_W2_SIGNAL) & ~0x08;
	rxdesc->rssi = rt2x00_get_field32(word3, RXD_W3_RSSI) -
	    entry->queue->rt2x00dev->rssi_offset;
	rxdesc->size = rt2x00_get_field32(word0, RXD_W0_DATABYTE_COUNT);

	rxdesc->dev_flags |= RXDONE_SIGNAL_PLCP;
	अगर (rt2x00_get_field32(word0, RXD_W0_MY_BSS))
		rxdesc->dev_flags |= RXDONE_MY_BSS;
पूर्ण

/*
 * Interrupt functions.
 */
अटल व्योम rt2400pci_txकरोne(काष्ठा rt2x00_dev *rt2x00dev,
			     स्थिर क्रमागत data_queue_qid queue_idx)
अणु
	काष्ठा data_queue *queue = rt2x00queue_get_tx_queue(rt2x00dev, queue_idx);
	काष्ठा queue_entry_priv_mmio *entry_priv;
	काष्ठा queue_entry *entry;
	काष्ठा txकरोne_entry_desc txdesc;
	u32 word;

	जबतक (!rt2x00queue_empty(queue)) अणु
		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);
		entry_priv = entry->priv_data;
		word = rt2x00_desc_पढ़ो(entry_priv->desc, 0);

		अगर (rt2x00_get_field32(word, TXD_W0_OWNER_NIC) ||
		    !rt2x00_get_field32(word, TXD_W0_VALID))
			अवरोध;

		/*
		 * Obtain the status about this packet.
		 */
		txdesc.flags = 0;
		चयन (rt2x00_get_field32(word, TXD_W0_RESULT)) अणु
		हाल 0: /* Success */
		हाल 1: /* Success with retry */
			__set_bit(TXDONE_SUCCESS, &txdesc.flags);
			अवरोध;
		हाल 2: /* Failure, excessive retries */
			__set_bit(TXDONE_EXCESSIVE_RETRY, &txdesc.flags);
			fallthrough;	/* this is a failed frame! */
		शेष: /* Failure */
			__set_bit(TXDONE_FAILURE, &txdesc.flags);
		पूर्ण
		txdesc.retry = rt2x00_get_field32(word, TXD_W0_RETRY_COUNT);

		rt2x00lib_txकरोne(entry, &txdesc);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rt2400pci_enable_पूर्णांकerrupt(काष्ठा rt2x00_dev *rt2x00dev,
					      काष्ठा rt2x00_field32 irq_field)
अणु
	u32 reg;

	/*
	 * Enable a single पूर्णांकerrupt. The पूर्णांकerrupt mask रेजिस्टर
	 * access needs locking.
	 */
	spin_lock_irq(&rt2x00dev->irqmask_lock);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR8);
	rt2x00_set_field32(&reg, irq_field, 0);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR8, reg);

	spin_unlock_irq(&rt2x00dev->irqmask_lock);
पूर्ण

अटल व्योम rt2400pci_txstatus_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    txstatus_tasklet);
	u32 reg;

	/*
	 * Handle all tx queues.
	 */
	rt2400pci_txकरोne(rt2x00dev, QID_ATIM);
	rt2400pci_txकरोne(rt2x00dev, QID_AC_VO);
	rt2400pci_txकरोne(rt2x00dev, QID_AC_VI);

	/*
	 * Enable all TXDONE पूर्णांकerrupts again.
	 */
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags)) अणु
		spin_lock_irq(&rt2x00dev->irqmask_lock);

		reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR8);
		rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, 0);
		rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, 0);
		rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, 0);
		rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR8, reg);

		spin_unlock_irq(&rt2x00dev->irqmask_lock);
	पूर्ण
पूर्ण

अटल व्योम rt2400pci_tbtt_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t, tbtt_tasklet);
	rt2x00lib_beaconकरोne(rt2x00dev);
	अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2400pci_enable_पूर्णांकerrupt(rt2x00dev, CSR8_TBCN_EXPIRE);
पूर्ण

अटल व्योम rt2400pci_rxकरोne_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = from_tasklet(rt2x00dev, t,
						    rxकरोne_tasklet);
	अगर (rt2x00mmio_rxकरोne(rt2x00dev))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);
	अन्यथा अगर (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2400pci_enable_पूर्णांकerrupt(rt2x00dev, CSR8_RXDONE);
पूर्ण

अटल irqवापस_t rt2400pci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = dev_instance;
	u32 reg, mask;

	/*
	 * Get the पूर्णांकerrupt sources & saved to local variable.
	 * Write रेजिस्टर value back to clear pending पूर्णांकerrupts.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR7);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR7, reg);

	अगर (!reg)
		वापस IRQ_NONE;

	अगर (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		वापस IRQ_HANDLED;

	mask = reg;

	/*
	 * Schedule tasklets क्रम पूर्णांकerrupt handling.
	 */
	अगर (rt2x00_get_field32(reg, CSR7_TBCN_EXPIRE))
		tasklet_hi_schedule(&rt2x00dev->tbtt_tasklet);

	अगर (rt2x00_get_field32(reg, CSR7_RXDONE))
		tasklet_schedule(&rt2x00dev->rxकरोne_tasklet);

	अगर (rt2x00_get_field32(reg, CSR7_TXDONE_ATIMRING) ||
	    rt2x00_get_field32(reg, CSR7_TXDONE_PRIORING) ||
	    rt2x00_get_field32(reg, CSR7_TXDONE_TXRING)) अणु
		tasklet_schedule(&rt2x00dev->txstatus_tasklet);
		/*
		 * Mask out all txकरोne पूर्णांकerrupts.
		 */
		rt2x00_set_field32(&mask, CSR8_TXDONE_TXRING, 1);
		rt2x00_set_field32(&mask, CSR8_TXDONE_ATIMRING, 1);
		rt2x00_set_field32(&mask, CSR8_TXDONE_PRIORING, 1);
	पूर्ण

	/*
	 * Disable all पूर्णांकerrupts क्रम which a tasklet was scheduled right now,
	 * the tasklet will reenable the appropriate पूर्णांकerrupts.
	 */
	spin_lock(&rt2x00dev->irqmask_lock);

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR8);
	reg |= mask;
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, CSR8, reg);

	spin_unlock(&rt2x00dev->irqmask_lock);



	वापस IRQ_HANDLED;
पूर्ण

/*
 * Device probe functions.
 */
अटल पूर्णांक rt2400pci_validate_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा eeprom_93cx6 eeprom;
	u32 reg;
	u16 word;
	u8 *mac;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR21);

	eeprom.data = rt2x00dev;
	eeprom.रेजिस्टर_पढ़ो = rt2400pci_eepromरेजिस्टर_पढ़ो;
	eeprom.रेजिस्टर_ग_लिखो = rt2400pci_eepromरेजिस्टर_ग_लिखो;
	eeprom.width = rt2x00_get_field32(reg, CSR21_TYPE_93C46) ?
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
		rt2x00_err(rt2x00dev, "Invalid EEPROM data detected\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2400pci_init_eeprom(काष्ठा rt2x00_dev *rt2x00dev)
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
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR0);
	rt2x00_set_chip(rt2x00dev, RT2460, value,
			rt2x00_get_field32(reg, CSR0_REVISION));

	अगर (!rt2x00_rf(rt2x00dev, RF2420) && !rt2x00_rf(rt2x00dev, RF2421)) अणु
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

	rt2400pci_init_led(rt2x00dev, &rt2x00dev->led_radio, LED_TYPE_RADIO);
	अगर (value == LED_MODE_TXRX_ACTIVITY ||
	    value == LED_MODE_DEFAULT ||
	    value == LED_MODE_ASUS)
		rt2400pci_init_led(rt2x00dev, &rt2x00dev->led_qual,
				   LED_TYPE_ACTIVITY);
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_LEDS */

	/*
	 * Detect अगर this device has an hardware controlled radio.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_HARDWARE_RADIO))
		__set_bit(CAPABILITY_HW_BUTTON, &rt2x00dev->cap_flags);

	/*
	 * Check अगर the BBP tuning should be enabled.
	 */
	अगर (rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_AGCVGC_TUNING))
		__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);

	वापस 0;
पूर्ण

/*
 * RF value list क्रम RF2420 & RF2421
 * Supports: 2.4 GHz
 */
अटल स्थिर काष्ठा rf_channel rf_vals_b[] = अणु
	अणु 1,  0x00022058, 0x000c1fda, 0x00000101, 0 पूर्ण,
	अणु 2,  0x00022058, 0x000c1fee, 0x00000101, 0 पूर्ण,
	अणु 3,  0x00022058, 0x000c2002, 0x00000101, 0 पूर्ण,
	अणु 4,  0x00022058, 0x000c2016, 0x00000101, 0 पूर्ण,
	अणु 5,  0x00022058, 0x000c202a, 0x00000101, 0 पूर्ण,
	अणु 6,  0x00022058, 0x000c203e, 0x00000101, 0 पूर्ण,
	अणु 7,  0x00022058, 0x000c2052, 0x00000101, 0 पूर्ण,
	अणु 8,  0x00022058, 0x000c2066, 0x00000101, 0 पूर्ण,
	अणु 9,  0x00022058, 0x000c207a, 0x00000101, 0 पूर्ण,
	अणु 10, 0x00022058, 0x000c208e, 0x00000101, 0 पूर्ण,
	अणु 11, 0x00022058, 0x000c20a2, 0x00000101, 0 पूर्ण,
	अणु 12, 0x00022058, 0x000c20b6, 0x00000101, 0 पूर्ण,
	अणु 13, 0x00022058, 0x000c20ca, 0x00000101, 0 पूर्ण,
	अणु 14, 0x00022058, 0x000c20fa, 0x00000101, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक rt2400pci_probe_hw_mode(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा hw_mode_spec *spec = &rt2x00dev->spec;
	काष्ठा channel_info *info;
	अक्षर *tx_घातer;
	अचिन्हित पूर्णांक i;

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
	 * Initialize hw_mode inक्रमmation.
	 */
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK;

	spec->num_channels = ARRAY_SIZE(rf_vals_b);
	spec->channels = rf_vals_b;

	/*
	 * Create channel inक्रमmation array
	 */
	info = kसुस्मृति(spec->num_channels, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	spec->channels_info = info;

	tx_घातer = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_START);
	क्रम (i = 0; i < 14; i++) अणु
		info[i].max_घातer = TXPOWER_FROM_DEV(MAX_TXPOWER);
		info[i].शेष_घातer1 = TXPOWER_FROM_DEV(tx_घातer[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2400pci_probe_hw(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	पूर्णांक retval;
	u32 reg;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2400pci_validate_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	retval = rt2400pci_init_eeprom(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * Enable rfसमाप्त polling by setting GPIO direction of the
	 * rfसमाप्त चयन GPIO pin correctly.
	 */
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, GPIOCSR);
	rt2x00_set_field32(&reg, GPIOCSR_सूची0, 1);
	rt2x00mmio_रेजिस्टर_ग_लिखो(rt2x00dev, GPIOCSR, reg);

	/*
	 * Initialize hw specअगरications.
	 */
	retval = rt2400pci_probe_hw_mode(rt2x00dev);
	अगर (retval)
		वापस retval;

	/*
	 * This device requires the atim queue and DMA-mapped skbs.
	 */
	__set_bit(REQUIRE_ATIM_QUEUE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_SW_SEQNO, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	वापस 0;
पूर्ण

/*
 * IEEE80211 stack callback functions.
 */
अटल पूर्णांक rt2400pci_conf_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			     स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * We करोn't support variating cw_min and cw_max variables
	 * per queue. So by शेष we only configure the TX queue,
	 * and ignore all other configurations.
	 */
	अगर (queue != 0)
		वापस -EINVAL;

	अगर (rt2x00mac_conf_tx(hw, vअगर, queue, params))
		वापस -EINVAL;

	/*
	 * Write configuration to रेजिस्टर.
	 */
	rt2400pci_config_cw(rt2x00dev,
			    rt2x00dev->tx->cw_min, rt2x00dev->tx->cw_max);

	वापस 0;
पूर्ण

अटल u64 rt2400pci_get_tsf(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u64 tsf;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR17);
	tsf = (u64) rt2x00_get_field32(reg, CSR17_HIGH_TSFTIMER) << 32;
	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR16);
	tsf |= rt2x00_get_field32(reg, CSR16_LOW_TSFTIMER);

	वापस tsf;
पूर्ण

अटल पूर्णांक rt2400pci_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;
	u32 reg;

	reg = rt2x00mmio_रेजिस्टर_पढ़ो(rt2x00dev, CSR15);
	वापस rt2x00_get_field32(reg, CSR15_BEACON_SENT);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops rt2400pci_mac80211_ops = अणु
	.tx			= rt2x00mac_tx,
	.start			= rt2x00mac_start,
	.stop			= rt2x00mac_stop,
	.add_पूर्णांकerface		= rt2x00mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rt2x00mac_हटाओ_पूर्णांकerface,
	.config			= rt2x00mac_config,
	.configure_filter	= rt2x00mac_configure_filter,
	.sw_scan_start		= rt2x00mac_sw_scan_start,
	.sw_scan_complete	= rt2x00mac_sw_scan_complete,
	.get_stats		= rt2x00mac_get_stats,
	.bss_info_changed	= rt2x00mac_bss_info_changed,
	.conf_tx		= rt2400pci_conf_tx,
	.get_tsf		= rt2400pci_get_tsf,
	.tx_last_beacon		= rt2400pci_tx_last_beacon,
	.rfसमाप्त_poll		= rt2x00mac_rfसमाप्त_poll,
	.flush			= rt2x00mac_flush,
	.set_antenna		= rt2x00mac_set_antenna,
	.get_antenna		= rt2x00mac_get_antenna,
	.get_ringparam		= rt2x00mac_get_ringparam,
	.tx_frames_pending	= rt2x00mac_tx_frames_pending,
पूर्ण;

अटल स्थिर काष्ठा rt2x00lib_ops rt2400pci_rt2x00_ops = अणु
	.irq_handler		= rt2400pci_पूर्णांकerrupt,
	.txstatus_tasklet	= rt2400pci_txstatus_tasklet,
	.tbtt_tasklet		= rt2400pci_tbtt_tasklet,
	.rxकरोne_tasklet		= rt2400pci_rxकरोne_tasklet,
	.probe_hw		= rt2400pci_probe_hw,
	.initialize		= rt2x00mmio_initialize,
	.uninitialize		= rt2x00mmio_uninitialize,
	.get_entry_state	= rt2400pci_get_entry_state,
	.clear_entry		= rt2400pci_clear_entry,
	.set_device_state	= rt2400pci_set_device_state,
	.rfसमाप्त_poll		= rt2400pci_rfसमाप्त_poll,
	.link_stats		= rt2400pci_link_stats,
	.reset_tuner		= rt2400pci_reset_tuner,
	.link_tuner		= rt2400pci_link_tuner,
	.start_queue		= rt2400pci_start_queue,
	.kick_queue		= rt2400pci_kick_queue,
	.stop_queue		= rt2400pci_stop_queue,
	.flush_queue		= rt2x00mmio_flush_queue,
	.ग_लिखो_tx_desc		= rt2400pci_ग_लिखो_tx_desc,
	.ग_लिखो_beacon		= rt2400pci_ग_लिखो_beacon,
	.fill_rxकरोne		= rt2400pci_fill_rxकरोne,
	.config_filter		= rt2400pci_config_filter,
	.config_पूर्णांकf		= rt2400pci_config_पूर्णांकf,
	.config_erp		= rt2400pci_config_erp,
	.config_ant		= rt2400pci_config_ant,
	.config			= rt2400pci_config,
पूर्ण;

अटल व्योम rt2400pci_queue_init(काष्ठा data_queue *queue)
अणु
	चयन (queue->qid) अणु
	हाल QID_RX:
		queue->limit = 24;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		queue->limit = 24;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_BEACON:
		queue->limit = 1;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	हाल QID_ATIM:
		queue->limit = 8;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = माप(काष्ठा queue_entry_priv_mmio);
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rt2x00_ops rt2400pci_ops = अणु
	.name			= KBUILD_MODNAME,
	.max_ap_पूर्णांकf		= 1,
	.eeprom_size		= EEPROM_SIZE,
	.rf_size		= RF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= rt2400pci_queue_init,
	.lib			= &rt2400pci_rt2x00_ops,
	.hw			= &rt2400pci_mac80211_ops,
#अगर_घोषित CONFIG_RT2X00_LIB_DEBUGFS
	.debugfs		= &rt2400pci_rt2x00debug,
#पूर्ण_अगर /* CONFIG_RT2X00_LIB_DEBUGFS */
पूर्ण;

/*
 * RT2400pci module inक्रमmation.
 */
अटल स्थिर काष्ठा pci_device_id rt2400pci_device_table[] = अणु
	अणु PCI_DEVICE(0x1814, 0x0101) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;


MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2400 PCI & PCMCIA Wireless LAN driver.");
MODULE_DEVICE_TABLE(pci, rt2400pci_device_table);
MODULE_LICENSE("GPL");

अटल पूर्णांक rt2400pci_probe(काष्ठा pci_dev *pci_dev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	वापस rt2x00pci_probe(pci_dev, &rt2400pci_ops);
पूर्ण

अटल काष्ठा pci_driver rt2400pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= rt2400pci_device_table,
	.probe		= rt2400pci_probe,
	.हटाओ		= rt2x00pci_हटाओ,
	.driver.pm	= &rt2x00pci_pm_ops,
पूर्ण;

module_pci_driver(rt2400pci_driver);

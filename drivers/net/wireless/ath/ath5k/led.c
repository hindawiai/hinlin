<शैली गुरु>
/*
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * Copyright (c) 2004-2005 Atheros Communications, Inc.
 * Copyright (c) 2007 Jiri Slaby <jirislaby@gmail.com>
 * Copyright (c) 2009 Bob Copeland <me@bobcopeland.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश "ath5k.h"

#घोषणा ATH_SDEVICE(subv, subd) \
	.venकरोr = PCI_ANY_ID, .device = PCI_ANY_ID, \
	.subvenकरोr = (subv), .subdevice = (subd)

#घोषणा ATH_LED(pin, polarity) .driver_data = (((pin) << 8) | (polarity))
#घोषणा ATH_PIN(data) ((data) >> 8)
#घोषणा ATH_POLARITY(data) ((data) & 0xff)

/* Devices we match on क्रम LED config info (typically laptops) */
अटल स्थिर काष्ठा pci_device_id ath5k_led_devices[] = अणु
	/* AR5211 */
	अणु PCI_VDEVICE(ATHEROS, PCI_DEVICE_ID_ATHEROS_AR5211), ATH_LED(0, 0) पूर्ण,
	/* HP Compaq nc6xx, nc4000, nx6000 */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_COMPAQ, PCI_ANY_ID), ATH_LED(1, 1) पूर्ण,
	/* Acer Aspire One A150 (maximlevitsky@gmail.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_FOXCONN, 0xe008), ATH_LED(3, 0) पूर्ण,
	/* Acer Aspire One AO531h AO751h (keng-yu.lin@canonical.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_FOXCONN, 0xe00d), ATH_LED(3, 0) पूर्ण,
	/* Acer Ferrari 5000 (russ.dill@gmail.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_AMBIT, 0x0422), ATH_LED(1, 1) पूर्ण,
	/* E-machines E510 (tuliom@gmail.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_AMBIT, 0x0428), ATH_LED(3, 0) पूर्ण,
	/* BenQ Joybook R55v (nowymarluk@wp.pl) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0100), ATH_LED(1, 0) पूर्ण,
	/* Acer Extensa 5620z (nekoreeve@gmail.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0105), ATH_LED(3, 0) पूर्ण,
	/* Fukato Datacask Jupiter 1014a (mrb74@gmx.at) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_AZWAVE, 0x1026), ATH_LED(3, 0) पूर्ण,
	/* IBM ThinkPad AR5BXB6 (legovini@spiro.fisica.unipd.it) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_IBM, 0x058a), ATH_LED(1, 0) पूर्ण,
	/* HP Compaq CQ60-206US (ddreggors@jumptv.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_HP, 0x0137a), ATH_LED(3, 1) पूर्ण,
	/* HP Compaq C700 (nitrousnrg@gmail.com) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_HP, 0x0137b), ATH_LED(3, 0) पूर्ण,
	/* LiteOn AR5BXB63 (magooz@salug.it) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_ATHEROS, 0x3067), ATH_LED(3, 0) पूर्ण,
	/* IBM-specअगरic AR5212 (all others) */
	अणु PCI_VDEVICE(ATHEROS, PCI_DEVICE_ID_ATHEROS_AR5212_IBM), ATH_LED(0, 0) पूर्ण,
	/* Dell Vostro A860 (shahar@shahar-or.co.il) */
	अणु ATH_SDEVICE(PCI_VENDOR_ID_QMI, 0x0112), ATH_LED(3, 0) पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम ath5k_led_enable(काष्ठा ath5k_hw *ah)
अणु
	अगर (test_bit(ATH_STAT_LEDSOFT, ah->status)) अणु
		ath5k_hw_set_gpio_output(ah, ah->led_pin);
		ath5k_led_off(ah);
	पूर्ण
पूर्ण

अटल व्योम ath5k_led_on(काष्ठा ath5k_hw *ah)
अणु
	अगर (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		वापस;
	ath5k_hw_set_gpio(ah, ah->led_pin, ah->led_on);
पूर्ण

व्योम ath5k_led_off(काष्ठा ath5k_hw *ah)
अणु
	अगर (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		वापस;
	ath5k_hw_set_gpio(ah, ah->led_pin, !ah->led_on);
पूर्ण

अटल व्योम
ath5k_led_brightness_set(काष्ठा led_classdev *led_dev,
	क्रमागत led_brightness brightness)
अणु
	काष्ठा ath5k_led *led = container_of(led_dev, काष्ठा ath5k_led,
		led_dev);

	अगर (brightness == LED_OFF)
		ath5k_led_off(led->ah);
	अन्यथा
		ath5k_led_on(led->ah);
पूर्ण

अटल पूर्णांक
ath5k_रेजिस्टर_led(काष्ठा ath5k_hw *ah, काष्ठा ath5k_led *led,
		   स्थिर अक्षर *name, स्थिर अक्षर *trigger)
अणु
	पूर्णांक err;

	led->ah = ah;
	म_नकलन(led->name, name, माप(led->name));
	led->name[माप(led->name)-1] = 0;
	led->led_dev.name = led->name;
	led->led_dev.शेष_trigger = trigger;
	led->led_dev.brightness_set = ath5k_led_brightness_set;

	err = led_classdev_रेजिस्टर(ah->dev, &led->led_dev);
	अगर (err) अणु
		ATH5K_WARN(ah, "could not register LED %s\n", name);
		led->ah = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम
ath5k_unरेजिस्टर_led(काष्ठा ath5k_led *led)
अणु
	अगर (!led->ah)
		वापस;
	led_classdev_unरेजिस्टर(&led->led_dev);
	ath5k_led_off(led->ah);
	led->ah = शून्य;
पूर्ण

व्योम ath5k_unरेजिस्टर_leds(काष्ठा ath5k_hw *ah)
अणु
	ath5k_unरेजिस्टर_led(&ah->rx_led);
	ath5k_unरेजिस्टर_led(&ah->tx_led);
पूर्ण

पूर्णांक ath5k_init_leds(काष्ठा ath5k_hw *ah)
अणु
	पूर्णांक ret = 0;
	काष्ठा ieee80211_hw *hw = ah->hw;
#अगर_अघोषित CONFIG_ATH5K_AHB
	काष्ठा pci_dev *pdev = ah->pdev;
#पूर्ण_अगर
	अक्षर name[ATH5K_LED_MAX_NAME_LEN + 1];
	स्थिर काष्ठा pci_device_id *match;

	अगर (!ah->pdev)
		वापस 0;

#अगर_घोषित CONFIG_ATH5K_AHB
	match = शून्य;
#अन्यथा
	match = pci_match_id(&ath5k_led_devices[0], pdev);
#पूर्ण_अगर
	अगर (match) अणु
		__set_bit(ATH_STAT_LEDSOFT, ah->status);
		ah->led_pin = ATH_PIN(match->driver_data);
		ah->led_on = ATH_POLARITY(match->driver_data);
	पूर्ण

	अगर (!test_bit(ATH_STAT_LEDSOFT, ah->status))
		जाओ out;

	ath5k_led_enable(ah);

	snम_लिखो(name, माप(name), "ath5k-%s::rx", wiphy_name(hw->wiphy));
	ret = ath5k_रेजिस्टर_led(ah, &ah->rx_led, name,
		ieee80211_get_rx_led_name(hw));
	अगर (ret)
		जाओ out;

	snम_लिखो(name, माप(name), "ath5k-%s::tx", wiphy_name(hw->wiphy));
	ret = ath5k_रेजिस्टर_led(ah, &ah->tx_led, name,
		ieee80211_get_tx_led_name(hw));
out:
	वापस ret;
पूर्ण


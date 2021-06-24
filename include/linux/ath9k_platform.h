<शैली गुरु>
/*
 * Copyright (c) 2008 Atheros Communications Inc.
 * Copyright (c) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (c) 2009 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _LINUX_ATH9K_PLATFORM_H
#घोषणा _LINUX_ATH9K_PLATFORM_H

#घोषणा ATH9K_PLAT_EEP_MAX_WORDS	2048

काष्ठा ath9k_platक्रमm_data अणु
	स्थिर अक्षर *eeprom_name;

	u16 eeprom_data[ATH9K_PLAT_EEP_MAX_WORDS];
	u8 *macaddr;

	पूर्णांक led_pin;
	u32 gpio_mask;
	u32 gpio_val;

	u32 bt_active_pin;
	u32 bt_priority_pin;
	u32 wlan_active_pin;

	bool endian_check;
	bool is_clk_25mhz;
	bool tx_gain_buffalo;
	bool disable_2ghz;
	bool disable_5ghz;
	bool led_active_high;

	पूर्णांक (*get_mac_revision)(व्योम);
	पूर्णांक (*बाह्यal_reset)(व्योम);

	bool use_eeprom;
पूर्ण;

#पूर्ण_अगर /* _LINUX_ATH9K_PLATFORM_H */

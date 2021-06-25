<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Jiri Slaby <jirislaby@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
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
 *
 */

/**************\
* Capabilities *
\**************/

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "../regd.h"

/*
 * Fill the capabilities काष्ठा
 * TODO: Merge this with EEPROM code when we are करोne with it
 */
पूर्णांक ath5k_hw_set_capabilities(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_capabilities *caps = &ah->ah_capabilities;
	u16 ee_header;

	/* Capabilities stored in the EEPROM */
	ee_header = caps->cap_eeprom.ee_header;

	अगर (ah->ah_version == AR5K_AR5210) अणु
		/*
		 * Set radio capabilities
		 * (The AR5110 only supports the middle 5GHz band)
		 */
		caps->cap_range.range_5ghz_min = 5120;
		caps->cap_range.range_5ghz_max = 5430;
		caps->cap_range.range_2ghz_min = 0;
		caps->cap_range.range_2ghz_max = 0;

		/* Set supported modes */
		__set_bit(AR5K_MODE_11A, caps->cap_mode);
	पूर्ण अन्यथा अणु
		/*
		 * XXX The transceiver supports frequencies from 4920 to 6100MHz
		 * XXX and from 2312 to 2732MHz. There are problems with the
		 * XXX current ieee80211 implementation because the IEEE
		 * XXX channel mapping करोes not support negative channel
		 * XXX numbers (2312MHz is channel -19). Of course, this
		 * XXX करोesn't matter because these channels are out of the
		 * XXX legal range.
		 */

		/*
		 * Set radio capabilities
		 */

		अगर (AR5K_EEPROM_HDR_11A(ee_header)) अणु
			अगर (ath_is_49ghz_allowed(caps->cap_eeprom.ee_regकरोमुख्य))
				caps->cap_range.range_5ghz_min = 4920;
			अन्यथा
				caps->cap_range.range_5ghz_min = 5005;
			caps->cap_range.range_5ghz_max = 6100;

			/* Set supported modes */
			__set_bit(AR5K_MODE_11A, caps->cap_mode);
		पूर्ण

		/* Enable  802.11b अगर a 2GHz capable radio (2111/5112) is
		 * connected */
		अगर (AR5K_EEPROM_HDR_11B(ee_header) ||
		    (AR5K_EEPROM_HDR_11G(ee_header) &&
		     ah->ah_version != AR5K_AR5211)) अणु
			/* 2312 */
			caps->cap_range.range_2ghz_min = 2412;
			caps->cap_range.range_2ghz_max = 2732;

			/* Override 2GHz modes on SoCs that need it
			 * NOTE: cap_needs_2GHz_ovr माला_लो set from
			 * ath_ahb_probe */
			अगर (!caps->cap_needs_2GHz_ovr) अणु
				अगर (AR5K_EEPROM_HDR_11B(ee_header))
					__set_bit(AR5K_MODE_11B,
							caps->cap_mode);

				अगर (AR5K_EEPROM_HDR_11G(ee_header) &&
				ah->ah_version != AR5K_AR5211)
					__set_bit(AR5K_MODE_11G,
							caps->cap_mode);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ah->ah_radio_5ghz_revision & 0xf0) == AR5K_SREV_RAD_2112)
		__clear_bit(AR5K_MODE_11A, caps->cap_mode);

	/* Set number of supported TX queues */
	अगर (ah->ah_version == AR5K_AR5210)
		caps->cap_queues.q_tx_num = AR5K_NUM_TX_QUEUES_NOQCU;
	अन्यथा
		caps->cap_queues.q_tx_num = AR5K_NUM_TX_QUEUES;

	/* Newer hardware has PHY error counters */
	अगर (ah->ah_mac_srev >= AR5K_SREV_AR5213A)
		caps->cap_has_phyerr_counters = true;
	अन्यथा
		caps->cap_has_phyerr_counters = false;

	/* MACs since AR5212 have MRR support */
	अगर (ah->ah_version == AR5K_AR5212)
		caps->cap_has_mrr_support = true;
	अन्यथा
		caps->cap_has_mrr_support = false;

	वापस 0;
पूर्ण

/*
 * TODO: Following functions should be part of a new function
 * set_capability
 */

पूर्णांक ath5k_hw_enable_pspoll(काष्ठा ath5k_hw *ah, u8 *bssid,
		u16 assoc_id)
अणु
	अगर (ah->ah_version == AR5K_AR5210) अणु
		AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1,
			AR5K_STA_ID1_NO_PSPOLL | AR5K_STA_ID1_DEFAULT_ANTENNA);
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

पूर्णांक ath5k_hw_disable_pspoll(काष्ठा ath5k_hw *ah)
अणु
	अगर (ah->ah_version == AR5K_AR5210) अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1,
			AR5K_STA_ID1_NO_PSPOLL | AR5K_STA_ID1_DEFAULT_ANTENNA);
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

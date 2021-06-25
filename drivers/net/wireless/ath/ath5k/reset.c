<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Luis Rodriguez <mcgrof@winlab.rutgers.edu>
 * Copyright (c) 2007-2008 Pavel Roskin <proski@gnu.org>
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

/****************************\
  Reset function and helpers
\****************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/pci.h>		/* To determine अगर a card is pci-e */
#समावेश <linux/log2.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"


/**
 * DOC: Reset function and helpers
 *
 * Here we implement the मुख्य reset routine, used to bring the card
 * to a working state and पढ़ोy to receive. We also handle routines
 * that करोn't fit on other places such as घड़ी, sleep and घातer control
 */


/******************\
* Helper functions *
\******************/

/**
 * ath5k_hw_रेजिस्टर_समयout() - Poll a रेजिस्टर क्रम a flag/field change
 * @ah: The &काष्ठा ath5k_hw
 * @reg: The रेजिस्टर to पढ़ो
 * @flag: The flag/field to check on the रेजिस्टर
 * @val: The field value we expect (अगर we check a field)
 * @is_set: Instead of checking अगर the flag got cleared, check अगर it got set
 *
 * Some रेजिस्टरs contain flags that indicate that an operation is
 * running. We use this function to poll these रेजिस्टरs and check
 * अगर these flags get cleared. We also use it to poll a रेजिस्टर
 * field (containing multiple flags) until it माला_लो a specअगरic value.
 *
 * Returns -EAGAIN अगर we exceeded AR5K_TUNE_REGISTER_TIMEOUT * 15us or 0
 */
पूर्णांक
ath5k_hw_रेजिस्टर_समयout(काष्ठा ath5k_hw *ah, u32 reg, u32 flag, u32 val,
			      bool is_set)
अणु
	पूर्णांक i;
	u32 data;

	क्रम (i = AR5K_TUNE_REGISTER_TIMEOUT; i > 0; i--) अणु
		data = ath5k_hw_reg_पढ़ो(ah, reg);
		अगर (is_set && (data & flag))
			अवरोध;
		अन्यथा अगर ((data & flag) == val)
			अवरोध;
		udelay(15);
	पूर्ण

	वापस (i <= 0) ? -EAGAIN : 0;
पूर्ण


/*************************\
* Clock related functions *
\*************************/

/**
 * ath5k_hw_htoघड़ी() - Translate usec to hw घड़ी units
 * @ah: The &काष्ठा ath5k_hw
 * @usec: value in microseconds
 *
 * Translate usecs to hw घड़ी units based on the current
 * hw घड़ी rate.
 *
 * Returns number of घड़ी units
 */
अचिन्हित पूर्णांक
ath5k_hw_htoघड़ी(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक usec)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	वापस usec * common->घड़ीrate;
पूर्ण

/**
 * ath5k_hw_घड़ीtoh() - Translate hw घड़ी units to usec
 * @ah: The &काष्ठा ath5k_hw
 * @घड़ी: value in hw घड़ी units
 *
 * Translate hw घड़ी units to usecs based on the current
 * hw घड़ी rate.
 *
 * Returns number of usecs
 */
अचिन्हित पूर्णांक
ath5k_hw_घड़ीtoh(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	वापस घड़ी / common->घड़ीrate;
पूर्ण

/**
 * ath5k_hw_init_core_घड़ी() - Initialize core घड़ी
 * @ah: The &काष्ठा ath5k_hw
 *
 * Initialize core घड़ी parameters (usec, usec32, latencies etc),
 * based on current bwmode and chipset properties.
 */
अटल व्योम
ath5k_hw_init_core_घड़ी(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_channel *channel = ah->ah_current_channel;
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	u32 usec_reg, txlat, rxlat, usec, घड़ी, sघड़ी, txf2txs;

	/*
	 * Set core घड़ी frequency
	 */
	चयन (channel->hw_value) अणु
	हाल AR5K_MODE_11A:
		घड़ी = 40;
		अवरोध;
	हाल AR5K_MODE_11B:
		घड़ी = 22;
		अवरोध;
	हाल AR5K_MODE_11G:
	शेष:
		घड़ी = 44;
		अवरोध;
	पूर्ण

	/* Use घड़ी multiplier क्रम non-शेष
	 * bwmode */
	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_40MHZ:
		घड़ी *= 2;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		घड़ी /= 2;
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		घड़ी /= 4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	common->घड़ीrate = घड़ी;

	/*
	 * Set USEC parameters
	 */
	/* Set USEC counter on PCU*/
	usec = घड़ी - 1;
	usec = AR5K_REG_SM(usec, AR5K_USEC_1);

	/* Set usec duration on DCU */
	अगर (ah->ah_version != AR5K_AR5210)
		AR5K_REG_WRITE_BITS(ah, AR5K_DCU_GBL_IFS_MISC,
					AR5K_DCU_GBL_IFS_MISC_USEC_DUR,
					घड़ी);

	/* Set 32MHz USEC counter */
	अगर ((ah->ah_radio == AR5K_RF5112) ||
	    (ah->ah_radio == AR5K_RF2413) ||
	    (ah->ah_radio == AR5K_RF5413) ||
	    (ah->ah_radio == AR5K_RF2316) ||
	    (ah->ah_radio == AR5K_RF2317))
		/* Reमुख्य on 40MHz घड़ी ? */
		sघड़ी = 40 - 1;
	अन्यथा
		sघड़ी = 32 - 1;
	sघड़ी = AR5K_REG_SM(sघड़ी, AR5K_USEC_32);

	/*
	 * Set tx/rx latencies
	 */
	usec_reg = ath5k_hw_reg_पढ़ो(ah, AR5K_USEC_5211);
	txlat = AR5K_REG_MS(usec_reg, AR5K_USEC_TX_LATENCY_5211);
	rxlat = AR5K_REG_MS(usec_reg, AR5K_USEC_RX_LATENCY_5211);

	/*
	 * Set शेष Tx frame to Tx data start delay
	 */
	txf2txs = AR5K_INIT_TXF2TXD_START_DEFAULT;

	/*
	 * 5210 initvals करोn't include usec settings
	 * so we need to use magic values here क्रम
	 * tx/rx latencies
	 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		/* same क्रम turbo */
		txlat = AR5K_INIT_TX_LATENCY_5210;
		rxlat = AR5K_INIT_RX_LATENCY_5210;
	पूर्ण

	अगर (ah->ah_mac_srev < AR5K_SREV_AR5211) अणु
		/* 5311 has dअगरferent tx/rx latency masks
		 * from 5211, since we deal 5311 the same
		 * as 5211 when setting initvals, shअगरt
		 * values here to their proper locations
		 *
		 * Note: Initvals indicate tx/rx/ latencies
		 * are the same क्रम turbo mode */
		txlat = AR5K_REG_SM(txlat, AR5K_USEC_TX_LATENCY_5210);
		rxlat = AR5K_REG_SM(rxlat, AR5K_USEC_RX_LATENCY_5210);
	पूर्ण अन्यथा
	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_10MHZ:
		txlat = AR5K_REG_SM(txlat * 2,
				AR5K_USEC_TX_LATENCY_5211);
		rxlat = AR5K_REG_SM(AR5K_INIT_RX_LAT_MAX,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DELAY_10MHZ;
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		txlat = AR5K_REG_SM(txlat * 4,
				AR5K_USEC_TX_LATENCY_5211);
		rxlat = AR5K_REG_SM(AR5K_INIT_RX_LAT_MAX,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DELAY_5MHZ;
		अवरोध;
	हाल AR5K_BWMODE_40MHZ:
		txlat = AR5K_INIT_TX_LAT_MIN;
		rxlat = AR5K_REG_SM(rxlat / 2,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DEFAULT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	usec_reg = (usec | sघड़ी | txlat | rxlat);
	ath5k_hw_reg_ग_लिखो(ah, usec_reg, AR5K_USEC);

	/* On 5112 set tx frame to tx data start delay */
	अगर (ah->ah_radio == AR5K_RF5112) अणु
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_RF_CTL2,
					AR5K_PHY_RF_CTL2_TXF2TXD_START,
					txf2txs);
	पूर्ण
पूर्ण

/**
 * ath5k_hw_set_sleep_घड़ी() - Setup sleep घड़ी operation
 * @ah: The &काष्ठा ath5k_hw
 * @enable: Enable sleep घड़ी operation (false to disable)
 *
 * If there is an बाह्यal 32KHz crystal available, use it
 * as ref. घड़ी instead of 32/40MHz घड़ी and baseband घड़ीs
 * to save घातer during sleep or restore normal 32/40MHz
 * operation.
 *
 * NOTE: When operating on 32KHz certain PHY रेजिस्टरs (27 - 31,
 * 123 - 127) require delay on access.
 */
अटल व्योम
ath5k_hw_set_sleep_घड़ी(काष्ठा ath5k_hw *ah, bool enable)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 scal, spending, sघड़ी;

	/* Only set 32KHz settings अगर we have an बाह्यal
	 * 32KHz crystal present */
	अगर ((AR5K_EEPROM_HAS32KHZCRYSTAL(ee->ee_misc1) ||
	AR5K_EEPROM_HAS32KHZCRYSTAL_OLD(ee->ee_misc1)) &&
	enable) अणु

		/* 1 usec/cycle */
		AR5K_REG_WRITE_BITS(ah, AR5K_USEC_5211, AR5K_USEC_32, 1);
		/* Set up tsf increment on each cycle */
		AR5K_REG_WRITE_BITS(ah, AR5K_TSF_PARM, AR5K_TSF_PARM_INC, 61);

		/* Set baseband sleep control रेजिस्टरs
		 * and sleep control rate */
		ath5k_hw_reg_ग_लिखो(ah, 0x1f, AR5K_PHY_SCR);

		अगर ((ah->ah_radio == AR5K_RF5112) ||
		(ah->ah_radio == AR5K_RF5413) ||
		(ah->ah_radio == AR5K_RF2316) ||
		(ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4)))
			spending = 0x14;
		अन्यथा
			spending = 0x18;
		ath5k_hw_reg_ग_लिखो(ah, spending, AR5K_PHY_SPENDING);

		अगर ((ah->ah_radio == AR5K_RF5112) ||
		(ah->ah_radio == AR5K_RF5413) ||
		(ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4))) अणु
			ath5k_hw_reg_ग_लिखो(ah, 0x26, AR5K_PHY_SLMT);
			ath5k_hw_reg_ग_लिखो(ah, 0x0d, AR5K_PHY_SCAL);
			ath5k_hw_reg_ग_लिखो(ah, 0x07, AR5K_PHY_SCLOCK);
			ath5k_hw_reg_ग_लिखो(ah, 0x3f, AR5K_PHY_SDELAY);
			AR5K_REG_WRITE_BITS(ah, AR5K_PCICFG,
				AR5K_PCICFG_SLEEP_CLOCK_RATE, 0x02);
		पूर्ण अन्यथा अणु
			ath5k_hw_reg_ग_लिखो(ah, 0x0a, AR5K_PHY_SLMT);
			ath5k_hw_reg_ग_लिखो(ah, 0x0c, AR5K_PHY_SCAL);
			ath5k_hw_reg_ग_लिखो(ah, 0x03, AR5K_PHY_SCLOCK);
			ath5k_hw_reg_ग_लिखो(ah, 0x20, AR5K_PHY_SDELAY);
			AR5K_REG_WRITE_BITS(ah, AR5K_PCICFG,
				AR5K_PCICFG_SLEEP_CLOCK_RATE, 0x03);
		पूर्ण

		/* Enable sleep घड़ी operation */
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG,
				AR5K_PCICFG_SLEEP_CLOCK_EN);

	पूर्ण अन्यथा अणु

		/* Disable sleep घड़ी operation and
		 * restore शेष parameters */
		AR5K_REG_DISABLE_BITS(ah, AR5K_PCICFG,
				AR5K_PCICFG_SLEEP_CLOCK_EN);

		AR5K_REG_WRITE_BITS(ah, AR5K_PCICFG,
				AR5K_PCICFG_SLEEP_CLOCK_RATE, 0);

		/* Set DAC/ADC delays */
		ath5k_hw_reg_ग_लिखो(ah, 0x1f, AR5K_PHY_SCR);
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SLMT_32MHZ, AR5K_PHY_SLMT);

		अगर (ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4))
			scal = AR5K_PHY_SCAL_32MHZ_2417;
		अन्यथा अगर (ee->ee_is_hb63)
			scal = AR5K_PHY_SCAL_32MHZ_HB63;
		अन्यथा
			scal = AR5K_PHY_SCAL_32MHZ;
		ath5k_hw_reg_ग_लिखो(ah, scal, AR5K_PHY_SCAL);

		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SCLOCK_32MHZ, AR5K_PHY_SCLOCK);
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SDELAY_32MHZ, AR5K_PHY_SDELAY);

		अगर ((ah->ah_radio == AR5K_RF5112) ||
		(ah->ah_radio == AR5K_RF5413) ||
		(ah->ah_radio == AR5K_RF2316) ||
		(ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4)))
			spending = 0x14;
		अन्यथा
			spending = 0x18;
		ath5k_hw_reg_ग_लिखो(ah, spending, AR5K_PHY_SPENDING);

		/* Set up tsf increment on each cycle */
		AR5K_REG_WRITE_BITS(ah, AR5K_TSF_PARM, AR5K_TSF_PARM_INC, 1);

		अगर ((ah->ah_radio == AR5K_RF5112) ||
			(ah->ah_radio == AR5K_RF5413) ||
			(ah->ah_radio == AR5K_RF2316) ||
			(ah->ah_radio == AR5K_RF2317))
			sघड़ी = 40 - 1;
		अन्यथा
			sघड़ी = 32 - 1;
		AR5K_REG_WRITE_BITS(ah, AR5K_USEC_5211, AR5K_USEC_32, sघड़ी);
	पूर्ण
पूर्ण


/*********************\
* Reset/Sleep control *
\*********************/

/**
 * ath5k_hw_nic_reset() - Reset the various chipset units
 * @ah: The &काष्ठा ath5k_hw
 * @val: Mask to indicate what units to reset
 *
 * To reset the various chipset units we need to ग_लिखो
 * the mask to AR5K_RESET_CTL and poll the रेजिस्टर until
 * all flags are cleared.
 *
 * Returns 0 अगर we are O.K. or -EAGAIN (from athk5_hw_रेजिस्टर_समयout)
 */
अटल पूर्णांक
ath5k_hw_nic_reset(काष्ठा ath5k_hw *ah, u32 val)
अणु
	पूर्णांक ret;
	u32 mask = val ? val : ~0U;

	/* Read-and-clear RX Descriptor Poपूर्णांकer*/
	ath5k_hw_reg_पढ़ो(ah, AR5K_RXDP);

	/*
	 * Reset the device and रुको until success
	 */
	ath5k_hw_reg_ग_लिखो(ah, val, AR5K_RESET_CTL);

	/* Wait at least 128 PCI घड़ीs */
	usleep_range(15, 20);

	अगर (ah->ah_version == AR5K_AR5210) अणु
		val &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_DMA
			| AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_PHY;
		mask &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_DMA
			| AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_PHY;
	पूर्ण अन्यथा अणु
		val &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_BASEBAND;
		mask &= AR5K_RESET_CTL_PCU | AR5K_RESET_CTL_BASEBAND;
	पूर्ण

	ret = ath5k_hw_रेजिस्टर_समयout(ah, AR5K_RESET_CTL, mask, val, false);

	/*
	 * Reset configuration रेजिस्टर (क्रम hw byte-swap). Note that this
	 * is only set क्रम big endian. We करो the necessary magic in
	 * AR5K_INIT_CFG.
	 */
	अगर ((val & AR5K_RESET_CTL_PCU) == 0)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_INIT_CFG, AR5K_CFG);

	वापस ret;
पूर्ण

/**
 * ath5k_hw_wisoc_reset() -  Reset AHB chipset
 * @ah: The &काष्ठा ath5k_hw
 * @flags: Mask to indicate what units to reset
 *
 * Same as ath5k_hw_nic_reset but क्रम AHB based devices
 *
 * Returns 0 अगर we are O.K. or -EAGAIN (from athk5_hw_रेजिस्टर_समयout)
 */
अटल पूर्णांक
ath5k_hw_wisoc_reset(काष्ठा ath5k_hw *ah, u32 flags)
अणु
	u32 mask = flags ? flags : ~0U;
	u32 __iomem *reg;
	u32 regval;
	u32 val = 0;

	/* ah->ah_mac_srev is not available at this poपूर्णांक yet */
	अगर (ah->devid >= AR5K_SREV_AR2315_R6) अणु
		reg = (u32 __iomem *) AR5K_AR2315_RESET;
		अगर (mask & AR5K_RESET_CTL_PCU)
			val |= AR5K_AR2315_RESET_WMAC;
		अगर (mask & AR5K_RESET_CTL_BASEBAND)
			val |= AR5K_AR2315_RESET_BB_WARM;
	पूर्ण अन्यथा अणु
		reg = (u32 __iomem *) AR5K_AR5312_RESET;
		अगर (to_platक्रमm_device(ah->dev)->id == 0) अणु
			अगर (mask & AR5K_RESET_CTL_PCU)
				val |= AR5K_AR5312_RESET_WMAC0;
			अगर (mask & AR5K_RESET_CTL_BASEBAND)
				val |= AR5K_AR5312_RESET_BB0_COLD |
				       AR5K_AR5312_RESET_BB0_WARM;
		पूर्ण अन्यथा अणु
			अगर (mask & AR5K_RESET_CTL_PCU)
				val |= AR5K_AR5312_RESET_WMAC1;
			अगर (mask & AR5K_RESET_CTL_BASEBAND)
				val |= AR5K_AR5312_RESET_BB1_COLD |
				       AR5K_AR5312_RESET_BB1_WARM;
		पूर्ण
	पूर्ण

	/* Put BB/MAC पूर्णांकo reset */
	regval = ioपढ़ो32(reg);
	ioग_लिखो32(regval | val, reg);
	regval = ioपढ़ो32(reg);
	udelay(100);	/* NB: should be atomic */

	/* Bring BB/MAC out of reset */
	ioग_लिखो32(regval & ~val, reg);
	regval = ioपढ़ो32(reg);

	/*
	 * Reset configuration रेजिस्टर (क्रम hw byte-swap). Note that this
	 * is only set क्रम big endian. We करो the necessary magic in
	 * AR5K_INIT_CFG.
	 */
	अगर ((flags & AR5K_RESET_CTL_PCU) == 0)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_INIT_CFG, AR5K_CFG);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_घातer_mode() - Set घातer mode
 * @ah: The &काष्ठा ath5k_hw
 * @mode: One of क्रमागत ath5k_घातer_mode
 * @set_chip: Set to true to ग_लिखो sleep control रेजिस्टर
 * @sleep_duration: How much समय the device is allowed to sleep
 * when sleep logic is enabled (in 128 microsecond increments).
 *
 * This function is used to configure sleep policy and allowed
 * sleep modes. For more inक्रमmation check out the sleep control
 * रेजिस्टर on reg.h and STA_ID1.
 *
 * Returns 0 on success, -EIO अगर chip didn't wake up or -EINVAL अगर an invalid
 * mode is requested.
 */
अटल पूर्णांक
ath5k_hw_set_घातer_mode(काष्ठा ath5k_hw *ah, क्रमागत ath5k_घातer_mode mode,
			      bool set_chip, u16 sleep_duration)
अणु
	अचिन्हित पूर्णांक i;
	u32 staid, data;

	staid = ath5k_hw_reg_पढ़ो(ah, AR5K_STA_ID1);

	चयन (mode) अणु
	हाल AR5K_PM_AUTO:
		staid &= ~AR5K_STA_ID1_DEFAULT_ANTENNA;
		fallthrough;
	हाल AR5K_PM_NETWORK_SLEEP:
		अगर (set_chip)
			ath5k_hw_reg_ग_लिखो(ah,
				AR5K_SLEEP_CTL_SLE_ALLOW |
				sleep_duration,
				AR5K_SLEEP_CTL);

		staid |= AR5K_STA_ID1_PWR_SV;
		अवरोध;

	हाल AR5K_PM_FULL_SLEEP:
		अगर (set_chip)
			ath5k_hw_reg_ग_लिखो(ah, AR5K_SLEEP_CTL_SLE_SLP,
				AR5K_SLEEP_CTL);

		staid |= AR5K_STA_ID1_PWR_SV;
		अवरोध;

	हाल AR5K_PM_AWAKE:

		staid &= ~AR5K_STA_ID1_PWR_SV;

		अगर (!set_chip)
			जाओ commit;

		data = ath5k_hw_reg_पढ़ो(ah, AR5K_SLEEP_CTL);

		/* If card is करोwn we 'll get 0xffff... so we
		 * need to clean this up beक्रमe we ग_लिखो the रेजिस्टर
		 */
		अगर (data & 0xffc00000)
			data = 0;
		अन्यथा
			/* Preserve sleep duration etc */
			data = data & ~AR5K_SLEEP_CTL_SLE;

		ath5k_hw_reg_ग_लिखो(ah, data | AR5K_SLEEP_CTL_SLE_WAKE,
							AR5K_SLEEP_CTL);
		usleep_range(15, 20);

		क्रम (i = 200; i > 0; i--) अणु
			/* Check अगर the chip did wake up */
			अगर ((ath5k_hw_reg_पढ़ो(ah, AR5K_PCICFG) &
					AR5K_PCICFG_SPWR_DN) == 0)
				अवरोध;

			/* Wait a bit and retry */
			usleep_range(50, 75);
			ath5k_hw_reg_ग_लिखो(ah, data | AR5K_SLEEP_CTL_SLE_WAKE,
							AR5K_SLEEP_CTL);
		पूर्ण

		/* Fail अगर the chip didn't wake up */
		अगर (i == 0)
			वापस -EIO;

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

commit:
	ath5k_hw_reg_ग_लिखो(ah, staid, AR5K_STA_ID1);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_on_hold() - Put device on hold
 * @ah: The &काष्ठा ath5k_hw
 *
 * Put MAC and Baseband on warm reset and keep that state
 * (करोn't clean sleep control रेजिस्टर). After this MAC
 * and Baseband are disabled and a full reset is needed
 * to come back. This way we save as much घातer as possible
 * without putting the card on full sleep.
 *
 * Returns 0 on success or -EIO on error
 */
पूर्णांक
ath5k_hw_on_hold(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा pci_dev *pdev = ah->pdev;
	u32 bus_flags;
	पूर्णांक ret;

	अगर (ath5k_get_bus_type(ah) == ATH_AHB)
		वापस 0;

	/* Make sure device is awake */
	ret = ath5k_hw_set_घातer_mode(ah, AR5K_PM_AWAKE, true, 0);
	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to wakeup the MAC Chip\n");
		वापस ret;
	पूर्ण

	/*
	 * Put chipset on warm reset...
	 *
	 * Note: putting PCI core on warm reset on PCI-E cards
	 * results card to hang and always वापस 0xffff... so
	 * we ignore that flag क्रम PCI-E cards. On PCI cards
	 * this flag माला_लो cleared after 64 PCI घड़ीs.
	 */
	bus_flags = (pdev && pci_is_pcie(pdev)) ? 0 : AR5K_RESET_CTL_PCI;

	अगर (ah->ah_version == AR5K_AR5210) अणु
		ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
			AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_DMA |
			AR5K_RESET_CTL_PHY | AR5K_RESET_CTL_PCI);
		usleep_range(2000, 2500);
	पूर्ण अन्यथा अणु
		ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
			AR5K_RESET_CTL_BASEBAND | bus_flags);
	पूर्ण

	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to put device on warm reset\n");
		वापस -EIO;
	पूर्ण

	/* ...wakeup again!*/
	ret = ath5k_hw_set_घातer_mode(ah, AR5K_PM_AWAKE, true, 0);
	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to put device on hold\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ath5k_hw_nic_wakeup() - Force card out of sleep
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Bring up MAC + PHY Chips and program PLL
 * NOTE: Channel is शून्य क्रम the initial wakeup.
 *
 * Returns 0 on success, -EIO on hw failure or -EINVAL क्रम false channel infos
 */
पूर्णांक
ath5k_hw_nic_wakeup(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा pci_dev *pdev = ah->pdev;
	u32 turbo, mode, घड़ी, bus_flags;
	पूर्णांक ret;

	turbo = 0;
	mode = 0;
	घड़ी = 0;

	अगर ((ath5k_get_bus_type(ah) != ATH_AHB) || channel) अणु
		/* Wakeup the device */
		ret = ath5k_hw_set_घातer_mode(ah, AR5K_PM_AWAKE, true, 0);
		अगर (ret) अणु
			ATH5K_ERR(ah, "failed to wakeup the MAC Chip\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Put chipset on warm reset...
	 *
	 * Note: putting PCI core on warm reset on PCI-E cards
	 * results card to hang and always वापस 0xffff... so
	 * we ignore that flag क्रम PCI-E cards. On PCI cards
	 * this flag माला_लो cleared after 64 PCI घड़ीs.
	 */
	bus_flags = (pdev && pci_is_pcie(pdev)) ? 0 : AR5K_RESET_CTL_PCI;

	अगर (ah->ah_version == AR5K_AR5210) अणु
		ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
			AR5K_RESET_CTL_MAC | AR5K_RESET_CTL_DMA |
			AR5K_RESET_CTL_PHY | AR5K_RESET_CTL_PCI);
		usleep_range(2000, 2500);
	पूर्ण अन्यथा अणु
		अगर (ath5k_get_bus_type(ah) == ATH_AHB)
			ret = ath5k_hw_wisoc_reset(ah, AR5K_RESET_CTL_PCU |
				AR5K_RESET_CTL_BASEBAND);
		अन्यथा
			ret = ath5k_hw_nic_reset(ah, AR5K_RESET_CTL_PCU |
				AR5K_RESET_CTL_BASEBAND | bus_flags);
	पूर्ण

	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to reset the MAC Chip\n");
		वापस -EIO;
	पूर्ण

	/* ...wakeup again!...*/
	ret = ath5k_hw_set_घातer_mode(ah, AR5K_PM_AWAKE, true, 0);
	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to resume the MAC Chip\n");
		वापस ret;
	पूर्ण

	/* ...reset configuration रेजिस्टर on Wisoc ...
	 * ...clear reset control रेजिस्टर and pull device out of
	 * warm reset on others */
	अगर (ath5k_get_bus_type(ah) == ATH_AHB)
		ret = ath5k_hw_wisoc_reset(ah, 0);
	अन्यथा
		ret = ath5k_hw_nic_reset(ah, 0);

	अगर (ret) अणु
		ATH5K_ERR(ah, "failed to warm reset the MAC Chip\n");
		वापस -EIO;
	पूर्ण

	/* On initialization skip PLL programming since we करोn't have
	 * a channel / mode set yet */
	अगर (!channel)
		वापस 0;

	अगर (ah->ah_version != AR5K_AR5210) अणु
		/*
		 * Get channel mode flags
		 */

		अगर (ah->ah_radio >= AR5K_RF5112) अणु
			mode = AR5K_PHY_MODE_RAD_RF5112;
			घड़ी = AR5K_PHY_PLL_RF5112;
		पूर्ण अन्यथा अणु
			mode = AR5K_PHY_MODE_RAD_RF5111;	/*Zero*/
			घड़ी = AR5K_PHY_PLL_RF5111;		/*Zero*/
		पूर्ण

		अगर (channel->band == NL80211_BAND_2GHZ) अणु
			mode |= AR5K_PHY_MODE_FREQ_2GHZ;
			घड़ी |= AR5K_PHY_PLL_44MHZ;

			अगर (channel->hw_value == AR5K_MODE_11B) अणु
				mode |= AR5K_PHY_MODE_MOD_CCK;
			पूर्ण अन्यथा अणु
				/* XXX Dynamic OFDM/CCK is not supported by the
				 * AR5211 so we set MOD_OFDM क्रम plain g (no
				 * CCK headers) operation. We need to test
				 * this, 5211 might support ofdm-only g after
				 * all, there are also initial रेजिस्टर values
				 * in the code क्रम g mode (see initvals.c).
				 */
				अगर (ah->ah_version == AR5K_AR5211)
					mode |= AR5K_PHY_MODE_MOD_OFDM;
				अन्यथा
					mode |= AR5K_PHY_MODE_MOD_DYN;
			पूर्ण
		पूर्ण अन्यथा अगर (channel->band == NL80211_BAND_5GHZ) अणु
			mode |= (AR5K_PHY_MODE_FREQ_5GHZ |
				 AR5K_PHY_MODE_MOD_OFDM);

			/* Dअगरferent PLL setting क्रम 5413 */
			अगर (ah->ah_radio == AR5K_RF5413)
				घड़ी = AR5K_PHY_PLL_40MHZ_5413;
			अन्यथा
				घड़ी |= AR5K_PHY_PLL_40MHZ;
		पूर्ण अन्यथा अणु
			ATH5K_ERR(ah, "invalid radio frequency mode\n");
			वापस -EINVAL;
		पूर्ण

		/*XXX: Can bwmode be used with dynamic mode ?
		 * (I करोn't think it supports 44MHz) */
		/* On 2425 initvals TURBO_SHORT is not present */
		अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ) अणु
			turbo = AR5K_PHY_TURBO_MODE;
			अगर (ah->ah_radio != AR5K_RF2425)
				turbo |= AR5K_PHY_TURBO_SHORT;
		पूर्ण अन्यथा अगर (ah->ah_bwmode != AR5K_BWMODE_DEFAULT) अणु
			अगर (ah->ah_radio == AR5K_RF5413) अणु
				mode |= (ah->ah_bwmode == AR5K_BWMODE_10MHZ) ?
					AR5K_PHY_MODE_HALF_RATE :
					AR5K_PHY_MODE_QUARTER_RATE;
			पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5212) अणु
				घड़ी |= (ah->ah_bwmode == AR5K_BWMODE_10MHZ) ?
					AR5K_PHY_PLL_HALF_RATE :
					AR5K_PHY_PLL_QUARTER_RATE;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु /* Reset the device */

		/* ...enable Atheros turbo mode अगर requested */
		अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
			ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_TURBO_MODE,
					AR5K_PHY_TURBO);
	पूर्ण

	अगर (ah->ah_version != AR5K_AR5210) अणु

		/* ...update PLL अगर needed */
		अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_PLL) != घड़ी) अणु
			ath5k_hw_reg_ग_लिखो(ah, घड़ी, AR5K_PHY_PLL);
			usleep_range(300, 350);
		पूर्ण

		/* ...set the PHY operating mode */
		ath5k_hw_reg_ग_लिखो(ah, mode, AR5K_PHY_MODE);
		ath5k_hw_reg_ग_लिखो(ah, turbo, AR5K_PHY_TURBO);
	पूर्ण

	वापस 0;
पूर्ण


/**************************************\
* Post-initvals रेजिस्टर modअगरications *
\**************************************/

/**
 * ath5k_hw_tweak_initval_settings() - Tweak initial settings
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Some settings are not handled on initvals, e.g. bwmode
 * settings, some phy settings, workarounds etc that in general
 * करोn't fit anywhere अन्यथा or are too small to पूर्णांकroduce a separate
 * function क्रम each one. So we have this function to handle
 * them all during reset and complete card's initialization.
 */
अटल व्योम
ath5k_hw_tweak_initval_settings(काष्ठा ath5k_hw *ah,
				काष्ठा ieee80211_channel *channel)
अणु
	अगर (ah->ah_version == AR5K_AR5212 &&
	    ah->ah_phy_revision >= AR5K_SREV_PHY_5212A) अणु

		/* Setup ADC control */
		ath5k_hw_reg_ग_लिखो(ah,
				(AR5K_REG_SM(2,
				AR5K_PHY_ADC_CTL_INBUFGAIN_OFF) |
				AR5K_REG_SM(2,
				AR5K_PHY_ADC_CTL_INBUFGAIN_ON) |
				AR5K_PHY_ADC_CTL_PWD_DAC_OFF |
				AR5K_PHY_ADC_CTL_PWD_ADC_OFF),
				AR5K_PHY_ADC_CTL);



		/* Disable barker RSSI threshold */
		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_DAG_CCK_CTL,
				AR5K_PHY_DAG_CCK_CTL_EN_RSSI_THR);

		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DAG_CCK_CTL,
			AR5K_PHY_DAG_CCK_CTL_RSSI_THR, 2);

		/* Set the mute mask */
		ath5k_hw_reg_ग_लिखो(ah, 0x0000000f, AR5K_SEQ_MASK);
	पूर्ण

	/* Clear PHY_BLUETOOTH to allow RX_CLEAR line debug */
	अगर (ah->ah_phy_revision >= AR5K_SREV_PHY_5212B)
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BLUETOOTH);

	/* Enable DCU द्विगुन buffering */
	अगर (ah->ah_phy_revision > AR5K_SREV_PHY_5212B)
		AR5K_REG_DISABLE_BITS(ah, AR5K_TXCFG,
				AR5K_TXCFG_DCU_DBL_BUF_DIS);

	/* Set fast ADC */
	अगर ((ah->ah_radio == AR5K_RF5413) ||
		(ah->ah_radio == AR5K_RF2317) ||
		(ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4))) अणु
		u32 fast_adc = true;

		अगर (channel->center_freq == 2462 ||
		channel->center_freq == 2467)
			fast_adc = 0;

		/* Only update अगर needed */
		अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_FAST_ADC) != fast_adc)
				ath5k_hw_reg_ग_लिखो(ah, fast_adc,
						AR5K_PHY_FAST_ADC);
	पूर्ण

	/* Fix क्रम first revision of the RF5112 RF chipset */
	अगर (ah->ah_radio == AR5K_RF5112 &&
			ah->ah_radio_5ghz_revision <
			AR5K_SREV_RAD_5112A) अणु
		u32 data;
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_CCKTXCTL_WORLD,
				AR5K_PHY_CCKTXCTL);
		अगर (channel->band == NL80211_BAND_5GHZ)
			data = 0xffb81020;
		अन्यथा
			data = 0xffb80d20;
		ath5k_hw_reg_ग_लिखो(ah, data, AR5K_PHY_FRAME_CTL);
	पूर्ण

	अगर (ah->ah_mac_srev < AR5K_SREV_AR5211) अणु
		/* Clear QCU/DCU घड़ी gating रेजिस्टर */
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_QCUDCU_CLKGT);
		/* Set DAC/ADC delays */
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SCAL_32MHZ_5311,
						AR5K_PHY_SCAL);
		/* Enable PCU FIFO corruption ECO */
		AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW_5211,
					AR5K_DIAG_SW_ECO_ENABLE);
	पूर्ण

	अगर (ah->ah_bwmode) अणु
		/* Increase PHY चयन and AGC settling समय
		 * on turbo mode (ath5k_hw_commit_eeprom_settings
		 * will override settling समय अगर available) */
		अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ) अणु

			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SETTLING,
						AR5K_PHY_SETTLING_AGC,
						AR5K_AGC_SETTLING_TURBO);

			/* XXX: Initvals indicate we only increase
			 * चयन समय on AR5212, 5211 and 5210
			 * only change agc समय (bug?) */
			अगर (ah->ah_version == AR5K_AR5212)
				AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SETTLING,
						AR5K_PHY_SETTLING_SWITCH,
						AR5K_SWITCH_SETTLING_TURBO);

			अगर (ah->ah_version == AR5K_AR5210) अणु
				/* Set Frame Control Register */
				ath5k_hw_reg_ग_लिखो(ah,
					(AR5K_PHY_FRAME_CTL_INI |
					AR5K_PHY_TURBO_MODE |
					AR5K_PHY_TURBO_SHORT | 0x2020),
					AR5K_PHY_FRAME_CTL_5210);
			पूर्ण
		/* On 5413 PHY क्रमce winकरोw length क्रम half/quarter rate*/
		पूर्ण अन्यथा अगर ((ah->ah_mac_srev >= AR5K_SREV_AR5424) &&
		(ah->ah_mac_srev <= AR5K_SREV_AR5414)) अणु
			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_FRAME_CTL_5211,
						AR5K_PHY_FRAME_CTL_WIN_LEN,
						3);
		पूर्ण
	पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5210) अणु
		/* Set Frame Control Register क्रम normal operation */
		ath5k_hw_reg_ग_लिखो(ah, (AR5K_PHY_FRAME_CTL_INI | 0x1020),
						AR5K_PHY_FRAME_CTL_5210);
	पूर्ण
पूर्ण

/**
 * ath5k_hw_commit_eeprom_settings() - Commit settings from EEPROM
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Use settings stored on EEPROM to properly initialize the card
 * based on various infos and per-mode calibration data.
 */
अटल व्योम
ath5k_hw_commit_eeprom_settings(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	s16 cck_ofdm_pwr_delta;
	u8 ee_mode;

	/* TODO: Add support क्रम AR5210 EEPROM */
	अगर (ah->ah_version == AR5K_AR5210)
		वापस;

	ee_mode = ath5k_eeprom_mode_from_channel(ah, channel);

	/* Adjust घातer delta क्रम channel 14 */
	अगर (channel->center_freq == 2484)
		cck_ofdm_pwr_delta =
			((ee->ee_cck_ofdm_घातer_delta -
			ee->ee_scaled_cck_delta) * 2) / 10;
	अन्यथा
		cck_ofdm_pwr_delta =
			(ee->ee_cck_ofdm_घातer_delta * 2) / 10;

	/* Set CCK to OFDM घातer delta on tx घातer
	 * adjusपंचांगent रेजिस्टर */
	अगर (ah->ah_phy_revision >= AR5K_SREV_PHY_5212A) अणु
		अगर (channel->hw_value == AR5K_MODE_11G)
			ath5k_hw_reg_ग_लिखो(ah,
			AR5K_REG_SM((ee->ee_cck_ofdm_gain_delta * -1),
				AR5K_PHY_TX_PWR_ADJ_CCK_GAIN_DELTA) |
			AR5K_REG_SM((cck_ofdm_pwr_delta * -1),
				AR5K_PHY_TX_PWR_ADJ_CCK_PCDAC_INDEX),
				AR5K_PHY_TX_PWR_ADJ);
		अन्यथा
			ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_TX_PWR_ADJ);
	पूर्ण अन्यथा अणु
		/* For older revs we scale घातer on sw during tx घातer
		 * setup */
		ah->ah_txघातer.txp_cck_ofdm_pwr_delta = cck_ofdm_pwr_delta;
		ah->ah_txघातer.txp_cck_ofdm_gainf_delta =
						ee->ee_cck_ofdm_gain_delta;
	पूर्ण

	/* XXX: necessary here? is called from ath5k_hw_set_antenna_mode()
	 * too */
	ath5k_hw_set_antenna_चयन(ah, ee_mode);

	/* Noise न्यूनमान threshold */
	ath5k_hw_reg_ग_लिखो(ah,
		AR5K_PHY_NF_SVAL(ee->ee_noise_न्यूनमान_thr[ee_mode]),
		AR5K_PHY_NFTHRES);

	अगर ((ah->ah_bwmode == AR5K_BWMODE_40MHZ) &&
	(ah->ah_ee_version >= AR5K_EEPROM_VERSION_5_0)) अणु
		/* Switch settling समय (Turbo) */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SETTLING,
				AR5K_PHY_SETTLING_SWITCH,
				ee->ee_चयन_settling_turbo[ee_mode]);

		/* Tx/Rx attenuation (Turbo) */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_GAIN,
				AR5K_PHY_GAIN_TXRX_ATTEN,
				ee->ee_atn_tx_rx_turbo[ee_mode]);

		/* ADC/PGA desired size (Turbo) */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_ADC,
				ee->ee_adc_desired_माप_प्रकारurbo[ee_mode]);

		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_PGA,
				ee->ee_pga_desired_माप_प्रकारurbo[ee_mode]);

		/* Tx/Rx margin (Turbo) */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_GAIN_2GHZ,
				AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX,
				ee->ee_margin_tx_rx_turbo[ee_mode]);

	पूर्ण अन्यथा अणु
		/* Switch settling समय */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SETTLING,
				AR5K_PHY_SETTLING_SWITCH,
				ee->ee_चयन_settling[ee_mode]);

		/* Tx/Rx attenuation */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_GAIN,
				AR5K_PHY_GAIN_TXRX_ATTEN,
				ee->ee_atn_tx_rx[ee_mode]);

		/* ADC/PGA desired size */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_ADC,
				ee->ee_adc_desired_size[ee_mode]);

		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_PGA,
				ee->ee_pga_desired_size[ee_mode]);

		/* Tx/Rx margin */
		अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_1)
			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_GAIN_2GHZ,
				AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX,
				ee->ee_margin_tx_rx[ee_mode]);
	पूर्ण

	/* XPA delays */
	ath5k_hw_reg_ग_लिखो(ah,
		(ee->ee_tx_end2xpa_disable[ee_mode] << 24) |
		(ee->ee_tx_end2xpa_disable[ee_mode] << 16) |
		(ee->ee_tx_frm2xpa_enable[ee_mode] << 8) |
		(ee->ee_tx_frm2xpa_enable[ee_mode]), AR5K_PHY_RF_CTL4);

	/* XLNA delay */
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_RF_CTL3,
			AR5K_PHY_RF_CTL3_TXE2XLNA_ON,
			ee->ee_tx_end2xlna_enable[ee_mode]);

	/* Thresh64 (ANI) */
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_NF,
			AR5K_PHY_NF_THRESH62,
			ee->ee_thr_62[ee_mode]);

	/* False detect backoff क्रम channels
	 * that have spur noise. Write the new
	 * cyclic घातer RSSI threshold. */
	अगर (ath5k_hw_chan_has_spur_noise(ah, channel))
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_OFDM_SELFCORR,
				AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1,
				AR5K_INIT_CYCRSSI_THR1 +
				ee->ee_false_detect[ee_mode]);
	अन्यथा
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_OFDM_SELFCORR,
				AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1,
				AR5K_INIT_CYCRSSI_THR1);

	/* I/Q correction (set enable bit last to match HAL sources) */
	/* TODO: Per channel i/q infos ? */
	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0) अणु
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_Q_I_COFF,
			    ee->ee_i_cal[ee_mode]);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_Q_Q_COFF,
			    ee->ee_q_cal[ee_mode]);
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_ENABLE);
	पूर्ण

	/* Heavy clipping -disable क्रम now */
	अगर (ah->ah_ee_version >= AR5K_EEPROM_VERSION_5_1)
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_HEAVY_CLIP_ENABLE);
पूर्ण


/*********************\
* Main reset function *
\*********************/

/**
 * ath5k_hw_reset() - The मुख्य reset function
 * @ah: The &काष्ठा ath5k_hw
 * @op_mode: One of क्रमागत nl80211_अगरtype
 * @channel: The &काष्ठा ieee80211_channel
 * @fast: Enable fast channel चयनing
 * @skip_pcu: Skip pcu initialization
 *
 * This is the function we call each समय we want to (re)initialize the
 * card and pass new settings to hw. We also call it when hw runs पूर्णांकo
 * trouble to make it come back to a working state.
 *
 * Returns 0 on success, -EINVAL on false op_mode or channel infos, or -EIO
 * on failure.
 */
पूर्णांक
ath5k_hw_reset(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype op_mode,
		काष्ठा ieee80211_channel *channel, bool fast, bool skip_pcu)
अणु
	u32 s_seq[10], s_led[3], tsf_up, tsf_lo;
	u8 mode;
	पूर्णांक i, ret;

	tsf_up = 0;
	tsf_lo = 0;
	mode = 0;

	/*
	 * Sanity check क्रम fast flag
	 * Fast channel change only available
	 * on AR2413/AR5413.
	 */
	अगर (fast && (ah->ah_radio != AR5K_RF2413) &&
	(ah->ah_radio != AR5K_RF5413))
		fast = false;

	/* Disable sleep घड़ी operation
	 * to aव्योम रेजिस्टर access delay on certain
	 * PHY रेजिस्टरs */
	अगर (ah->ah_version == AR5K_AR5212)
		ath5k_hw_set_sleep_घड़ी(ah, false);

	mode = channel->hw_value;
	चयन (mode) अणु
	हाल AR5K_MODE_11A:
		अवरोध;
	हाल AR5K_MODE_11G:
		अगर (ah->ah_version <= AR5K_AR5211) अणु
			ATH5K_ERR(ah,
				"G mode not available on 5210/5211");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AR5K_MODE_11B:
		अगर (ah->ah_version < AR5K_AR5211) अणु
			ATH5K_ERR(ah,
				"B mode not available on 5210");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ATH5K_ERR(ah,
			"invalid channel: %d\n", channel->center_freq);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If driver requested fast channel change and DMA has stopped
	 * go on. If it fails जारी with a normal reset.
	 */
	अगर (fast) अणु
		ret = ath5k_hw_phy_init(ah, channel, mode, true);
		अगर (ret) अणु
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"fast chan change failed, falling back to normal reset\n");
			/* Non fatal, can happen eg.
			 * on mode change */
			ret = 0;
		पूर्ण अन्यथा अणु
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"fast chan change successful\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Save some रेजिस्टरs beक्रमe a reset
	 */
	अगर (ah->ah_version != AR5K_AR5210) अणु
		/*
		 * Save frame sequence count
		 * For revs. after Oahu, only save
		 * seq num क्रम DCU 0 (Global seq num)
		 */
		अगर (ah->ah_mac_srev < AR5K_SREV_AR5211) अणु

			क्रम (i = 0; i < 10; i++)
				s_seq[i] = ath5k_hw_reg_पढ़ो(ah,
					AR5K_QUEUE_DCU_SEQNUM(i));

		पूर्ण अन्यथा अणु
			s_seq[0] = ath5k_hw_reg_पढ़ो(ah,
					AR5K_QUEUE_DCU_SEQNUM(0));
		पूर्ण

		/* TSF accelerates on AR5211 during reset
		 * As a workaround save it here and restore
		 * it later so that it's back in समय after
		 * reset. This way it'll get re-synced on the
		 * next beacon without अवरोधing ad-hoc.
		 *
		 * On AR5212 TSF is almost preserved across a
		 * reset so it stays back in समय anyway and
		 * we करोn't have to save/restore it.
		 *
		 * XXX: Since this अवरोधs घातer saving we have
		 * to disable घातer saving until we receive the
		 * next beacon, so we can resync beacon समयrs */
		अगर (ah->ah_version == AR5K_AR5211) अणु
			tsf_up = ath5k_hw_reg_पढ़ो(ah, AR5K_TSF_U32);
			tsf_lo = ath5k_hw_reg_पढ़ो(ah, AR5K_TSF_L32);
		पूर्ण
	पूर्ण


	/*GPIOs*/
	s_led[0] = ath5k_hw_reg_पढ़ो(ah, AR5K_PCICFG) &
					AR5K_PCICFG_LEDSTATE;
	s_led[1] = ath5k_hw_reg_पढ़ो(ah, AR5K_GPIOCR);
	s_led[2] = ath5k_hw_reg_पढ़ो(ah, AR5K_GPIODO);


	/*
	 * Since we are going to ग_लिखो rf buffer
	 * check अगर we have any pending gain_F
	 * optimization settings
	 */
	अगर (ah->ah_version == AR5K_AR5212 &&
	(ah->ah_radio <= AR5K_RF5112)) अणु
		अगर (!fast && ah->ah_rf_banks != शून्य)
				ath5k_hw_gainf_calibrate(ah);
	पूर्ण

	/* Wakeup the device */
	ret = ath5k_hw_nic_wakeup(ah, channel);
	अगर (ret)
		वापस ret;

	/* PHY access enable */
	अगर (ah->ah_mac_srev >= AR5K_SREV_AR5211)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));
	अन्यथा
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SHIFT_5GHZ | 0x40,
							AR5K_PHY(0));

	/* Write initial settings */
	ret = ath5k_hw_ग_लिखो_initvals(ah, mode, skip_pcu);
	अगर (ret)
		वापस ret;

	/* Initialize core घड़ी settings */
	ath5k_hw_init_core_घड़ी(ah);

	/*
	 * Tweak initval settings क्रम revised
	 * chipsets and add some more config
	 * bits
	 */
	ath5k_hw_tweak_initval_settings(ah, channel);

	/* Commit values from EEPROM */
	ath5k_hw_commit_eeprom_settings(ah, channel);


	/*
	 * Restore saved values
	 */

	/* Seqnum, TSF */
	अगर (ah->ah_version != AR5K_AR5210) अणु
		अगर (ah->ah_mac_srev < AR5K_SREV_AR5211) अणु
			क्रम (i = 0; i < 10; i++)
				ath5k_hw_reg_ग_लिखो(ah, s_seq[i],
					AR5K_QUEUE_DCU_SEQNUM(i));
		पूर्ण अन्यथा अणु
			ath5k_hw_reg_ग_लिखो(ah, s_seq[0],
				AR5K_QUEUE_DCU_SEQNUM(0));
		पूर्ण

		अगर (ah->ah_version == AR5K_AR5211) अणु
			ath5k_hw_reg_ग_लिखो(ah, tsf_up, AR5K_TSF_U32);
			ath5k_hw_reg_ग_लिखो(ah, tsf_lo, AR5K_TSF_L32);
		पूर्ण
	पूर्ण

	/* Ledstate */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, s_led[0]);

	/* Gpio settings */
	ath5k_hw_reg_ग_लिखो(ah, s_led[1], AR5K_GPIOCR);
	ath5k_hw_reg_ग_लिखो(ah, s_led[2], AR5K_GPIODO);

	/*
	 * Initialize PCU
	 */
	ath5k_hw_pcu_init(ah, op_mode);

	/*
	 * Initialize PHY
	 */
	ret = ath5k_hw_phy_init(ah, channel, mode, false);
	अगर (ret) अणु
		ATH5K_ERR(ah,
			"failed to initialize PHY (%i) !\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Configure QCUs/DCUs
	 */
	ret = ath5k_hw_init_queues(ah);
	अगर (ret)
		वापस ret;


	/*
	 * Initialize DMA/Interrupts
	 */
	ath5k_hw_dma_init(ah);


	/*
	 * Enable 32KHz घड़ी function क्रम AR5212+ chips
	 * Set घड़ीs to 32KHz operation and use an
	 * बाह्यal 32KHz crystal when sleeping अगर one
	 * exists.
	 * Disabled by शेष because it is also disabled in
	 * other drivers and it is known to cause stability
	 * issues on some devices
	 */
	अगर (ah->ah_use_32khz_घड़ी && ah->ah_version == AR5K_AR5212 &&
	    op_mode != NL80211_IFTYPE_AP)
		ath5k_hw_set_sleep_घड़ी(ah, true);

	/*
	 * Disable beacons and reset the TSF
	 */
	AR5K_REG_DISABLE_BITS(ah, AR5K_BEACON, AR5K_BEACON_ENABLE);
	ath5k_hw_reset_tsf(ah);
	वापस 0;
पूर्ण

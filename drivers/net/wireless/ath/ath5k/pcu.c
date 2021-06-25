<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Matthew W. S. Bell  <mentor@madwअगरi.org>
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

/*********************************\
* Protocol Control Unit Functions *
\*********************************/

#समावेश <यंत्र/unaligned.h>

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"

/**
 * DOC: Protocol Control Unit (PCU) functions
 *
 * Protocol control unit is responsible to मुख्यtain various protocol
 * properties beक्रमe a frame is send and after a frame is received to/from
 * baseband. To be more specअगरic, PCU handles:
 *
 * - Buffering of RX and TX frames (after QCU/DCUs)
 *
 * - Encrypting and decrypting (using the built-in engine)
 *
 * - Generating ACKs, RTS/CTS frames
 *
 * - Maपूर्णांकaining TSF
 *
 * - FCS
 *
 * - Updating beacon data (with TSF etc)
 *
 * - Generating भव CCA
 *
 * - RX/Multicast filtering
 *
 * - BSSID filtering
 *
 * - Various statistics
 *
 * -Dअगरferent operating modes: AP, STA, IBSS
 *
 * Note: Most of these functions can be tweaked/bypassed so you can करो
 * them on sw above क्रम debugging or research. For more infos check out PCU
 * रेजिस्टरs on reg.h.
 */

/**
 * DOC: ACK rates
 *
 * AR5212+ can use higher rates क्रम ack transmission
 * based on current tx rate instead of the base rate.
 * It करोes this to better utilize channel usage.
 * There is a mapping between G rates (that cover both
 * CCK and OFDM) and ack rates that we use when setting
 * rate -> duration table. This mapping is hw-based so
 * करोn't change anything.
 *
 * To enable this functionality we must set
 * ah->ah_ack_bitrate_high to true अन्यथा base rate is
 * used (1Mb क्रम CCK, 6Mb क्रम OFDM).
 */
अटल स्थिर अचिन्हित पूर्णांक ack_rates_high[] =
/* Tx	-> ACK	*/
/* 1Mb	-> 1Mb	*/	अणु 0,
/* 2MB	-> 2Mb	*/	1,
/* 5.5Mb -> 2Mb	*/	1,
/* 11Mb	-> 2Mb	*/	1,
/* 6Mb	-> 6Mb	*/	4,
/* 9Mb	-> 6Mb	*/	4,
/* 12Mb	-> 12Mb	*/	6,
/* 18Mb	-> 12Mb	*/	6,
/* 24Mb	-> 24Mb	*/	8,
/* 36Mb	-> 24Mb	*/	8,
/* 48Mb	-> 24Mb	*/	8,
/* 54Mb	-> 24Mb	*/	8 पूर्ण;

/*******************\
* Helper functions *
\*******************/

/**
 * ath5k_hw_get_frame_duration() - Get tx समय of a frame
 * @ah: The &काष्ठा ath5k_hw
 * @band: One of क्रमागत nl80211_band
 * @len: Frame's length in bytes
 * @rate: The @काष्ठा ieee80211_rate
 * @लघुpre: Indicate लघु preample
 *
 * Calculate tx duration of a frame given it's rate and length
 * It extends ieee80211_generic_frame_duration क्रम non standard
 * bwmodes.
 */
पूर्णांक
ath5k_hw_get_frame_duration(काष्ठा ath5k_hw *ah, क्रमागत nl80211_band band,
		पूर्णांक len, काष्ठा ieee80211_rate *rate, bool लघुpre)
अणु
	पूर्णांक sअगरs, preamble, plcp_bits, sym_समय;
	पूर्णांक bitrate, bits, symbols, symbol_bits;
	पूर्णांक dur;

	/* Fallback */
	अगर (!ah->ah_bwmode) अणु
		__le16 raw_dur = ieee80211_generic_frame_duration(ah->hw,
					शून्य, band, len, rate);

		/* subtract dअगरference between दीर्घ and लघु preamble */
		dur = le16_to_cpu(raw_dur);
		अगर (लघुpre)
			dur -= 96;

		वापस dur;
	पूर्ण

	bitrate = rate->bitrate;
	preamble = AR5K_INIT_OFDM_PREAMPLE_TIME;
	plcp_bits = AR5K_INIT_OFDM_PLCP_BITS;
	sym_समय = AR5K_INIT_OFDM_SYMBOL_TIME;

	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_40MHZ:
		sअगरs = AR5K_INIT_SIFS_TURBO;
		preamble = AR5K_INIT_OFDM_PREAMBLE_TIME_MIN;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		sअगरs = AR5K_INIT_SIFS_HALF_RATE;
		preamble *= 2;
		sym_समय *= 2;
		bitrate = DIV_ROUND_UP(bitrate, 2);
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		sअगरs = AR5K_INIT_SIFS_QUARTER_RATE;
		preamble *= 4;
		sym_समय *= 4;
		bitrate = DIV_ROUND_UP(bitrate, 4);
		अवरोध;
	शेष:
		sअगरs = AR5K_INIT_SIFS_DEFAULT_BG;
		अवरोध;
	पूर्ण

	bits = plcp_bits + (len << 3);
	/* Bit rate is in 100Kbits */
	symbol_bits = bitrate * sym_समय;
	symbols = DIV_ROUND_UP(bits * 10, symbol_bits);

	dur = sअगरs + preamble + (sym_समय * symbols);

	वापस dur;
पूर्ण

/**
 * ath5k_hw_get_शेष_slotसमय() - Get the शेष slot समय क्रम current mode
 * @ah: The &काष्ठा ath5k_hw
 */
अचिन्हित पूर्णांक
ath5k_hw_get_शेष_slotसमय(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_channel *channel = ah->ah_current_channel;
	अचिन्हित पूर्णांक slot_समय;

	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_40MHZ:
		slot_समय = AR5K_INIT_SLOT_TIME_TURBO;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		slot_समय = AR5K_INIT_SLOT_TIME_HALF_RATE;
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		slot_समय = AR5K_INIT_SLOT_TIME_QUARTER_RATE;
		अवरोध;
	हाल AR5K_BWMODE_DEFAULT:
	शेष:
		slot_समय = AR5K_INIT_SLOT_TIME_DEFAULT;
		अगर ((channel->hw_value == AR5K_MODE_11B) && !ah->ah_लघु_slot)
			slot_समय = AR5K_INIT_SLOT_TIME_B;
		अवरोध;
	पूर्ण

	वापस slot_समय;
पूर्ण

/**
 * ath5k_hw_get_शेष_sअगरs() - Get the शेष SIFS क्रम current mode
 * @ah: The &काष्ठा ath5k_hw
 */
अचिन्हित पूर्णांक
ath5k_hw_get_शेष_sअगरs(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_channel *channel = ah->ah_current_channel;
	अचिन्हित पूर्णांक sअगरs;

	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_40MHZ:
		sअगरs = AR5K_INIT_SIFS_TURBO;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		sअगरs = AR5K_INIT_SIFS_HALF_RATE;
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		sअगरs = AR5K_INIT_SIFS_QUARTER_RATE;
		अवरोध;
	हाल AR5K_BWMODE_DEFAULT:
	शेष:
		sअगरs = AR5K_INIT_SIFS_DEFAULT_BG;
		अगर (channel->band == NL80211_BAND_5GHZ)
			sअगरs = AR5K_INIT_SIFS_DEFAULT_A;
		अवरोध;
	पूर्ण

	वापस sअगरs;
पूर्ण

/**
 * ath5k_hw_update_mib_counters() - Update MIB counters (mac layer statistics)
 * @ah: The &काष्ठा ath5k_hw
 *
 * Reads MIB counters from PCU and updates sw statistics. Is called after a
 * MIB पूर्णांकerrupt, because one of these counters might have reached their maximum
 * and triggered the MIB पूर्णांकerrupt, to let us पढ़ो and clear the counter.
 *
 * NOTE: Is called in पूर्णांकerrupt context!
 */
व्योम
ath5k_hw_update_mib_counters(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_statistics *stats = &ah->stats;

	/* Read-And-Clear */
	stats->ack_fail += ath5k_hw_reg_पढ़ो(ah, AR5K_ACK_FAIL);
	stats->rts_fail += ath5k_hw_reg_पढ़ो(ah, AR5K_RTS_FAIL);
	stats->rts_ok += ath5k_hw_reg_पढ़ो(ah, AR5K_RTS_OK);
	stats->fcs_error += ath5k_hw_reg_पढ़ो(ah, AR5K_FCS_FAIL);
	stats->beacons += ath5k_hw_reg_पढ़ो(ah, AR5K_BEACON_CNT);
पूर्ण


/******************\
* ACK/CTS Timeouts *
\******************/

/**
 * ath5k_hw_ग_लिखो_rate_duration() - Fill rate code to duration table
 * @ah: The &काष्ठा ath5k_hw
 *
 * Write the rate code to duration table upon hw reset. This is a helper क्रम
 * ath5k_hw_pcu_init(). It seems all this is करोing is setting an ACK समयout on
 * the hardware, based on current mode, क्रम each rate. The rates which are
 * capable of लघु preamble (802.11b rates 2Mbps, 5.5Mbps, and 11Mbps) have
 * dअगरferent rate code so we ग_लिखो their value twice (one क्रम दीर्घ preamble
 * and one क्रम लघु).
 *
 * Note: Band करोesn't matter here, अगर we set the values क्रम OFDM it works
 * on both a and g modes. So all we have to करो is set values क्रम all g rates
 * that include all OFDM and CCK rates.
 *
 */
अटल अंतरभूत व्योम
ath5k_hw_ग_लिखो_rate_duration(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_rate *rate;
	अचिन्हित पूर्णांक i;
	/* 802.11g covers both OFDM and CCK */
	u8 band = NL80211_BAND_2GHZ;

	/* Write rate duration table */
	क्रम (i = 0; i < ah->sbands[band].n_bitrates; i++) अणु
		u32 reg;
		u16 tx_समय;

		अगर (ah->ah_ack_bitrate_high)
			rate = &ah->sbands[band].bitrates[ack_rates_high[i]];
		/* CCK -> 1Mb */
		अन्यथा अगर (i < 4)
			rate = &ah->sbands[band].bitrates[0];
		/* OFDM -> 6Mb */
		अन्यथा
			rate = &ah->sbands[band].bitrates[4];

		/* Set ACK समयout */
		reg = AR5K_RATE_DUR(rate->hw_value);

		/* An ACK frame consists of 10 bytes. If you add the FCS,
		 * which ieee80211_generic_frame_duration() adds,
		 * its 14 bytes. Note we use the control rate and not the
		 * actual rate क्रम this rate. See mac80211 tx.c
		 * ieee80211_duration() क्रम a brief description of
		 * what rate we should choose to TX ACKs. */
		tx_समय = ath5k_hw_get_frame_duration(ah, band, 10,
					rate, false);

		ath5k_hw_reg_ग_लिखो(ah, tx_समय, reg);

		अगर (!(rate->flags & IEEE80211_RATE_SHORT_PREAMBLE))
			जारी;

		tx_समय = ath5k_hw_get_frame_duration(ah, band, 10, rate, true);
		ath5k_hw_reg_ग_लिखो(ah, tx_समय,
			reg + (AR5K_SET_SHORT_PREAMBLE << 2));
	पूर्ण
पूर्ण

/**
 * ath5k_hw_set_ack_समयout() - Set ACK समयout on PCU
 * @ah: The &काष्ठा ath5k_hw
 * @समयout: Timeout in usec
 */
अटल पूर्णांक
ath5k_hw_set_ack_समयout(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक समयout)
अणु
	अगर (ath5k_hw_घड़ीtoh(ah, AR5K_REG_MS(0xffffffff, AR5K_TIME_OUT_ACK))
			<= समयout)
		वापस -EINVAL;

	AR5K_REG_WRITE_BITS(ah, AR5K_TIME_OUT, AR5K_TIME_OUT_ACK,
		ath5k_hw_htoघड़ी(ah, समयout));

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_cts_समयout() - Set CTS समयout on PCU
 * @ah: The &काष्ठा ath5k_hw
 * @समयout: Timeout in usec
 */
अटल पूर्णांक
ath5k_hw_set_cts_समयout(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक समयout)
अणु
	अगर (ath5k_hw_घड़ीtoh(ah, AR5K_REG_MS(0xffffffff, AR5K_TIME_OUT_CTS))
			<= समयout)
		वापस -EINVAL;

	AR5K_REG_WRITE_BITS(ah, AR5K_TIME_OUT, AR5K_TIME_OUT_CTS,
			ath5k_hw_htoघड़ी(ah, समयout));

	वापस 0;
पूर्ण


/*******************\
* RX filter Control *
\*******************/

/**
 * ath5k_hw_set_lladdr() - Set station id
 * @ah: The &काष्ठा ath5k_hw
 * @mac: The card's mac address (array of octets)
 *
 * Set station id on hw using the provided mac address
 */
पूर्णांक
ath5k_hw_set_lladdr(काष्ठा ath5k_hw *ah, स्थिर u8 *mac)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	u32 low_id, high_id;
	u32 pcu_reg;

	/* Set new station ID */
	स_नकल(common->macaddr, mac, ETH_ALEN);

	pcu_reg = ath5k_hw_reg_पढ़ो(ah, AR5K_STA_ID1) & 0xffff0000;

	low_id = get_unaligned_le32(mac);
	high_id = get_unaligned_le16(mac + 4);

	ath5k_hw_reg_ग_लिखो(ah, low_id, AR5K_STA_ID0);
	ath5k_hw_reg_ग_लिखो(ah, pcu_reg | high_id, AR5K_STA_ID1);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_bssid() - Set current BSSID on hw
 * @ah: The &काष्ठा ath5k_hw
 *
 * Sets the current BSSID and BSSID mask we have from the
 * common काष्ठा पूर्णांकo the hardware
 */
व्योम
ath5k_hw_set_bssid(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	u16 tim_offset = 0;

	/*
	 * Set BSSID mask on 5212
	 */
	अगर (ah->ah_version == AR5K_AR5212)
		ath_hw_setbssidmask(common);

	/*
	 * Set BSSID
	 */
	ath5k_hw_reg_ग_लिखो(ah,
			   get_unaligned_le32(common->curbssid),
			   AR5K_BSS_ID0);
	ath5k_hw_reg_ग_लिखो(ah,
			   get_unaligned_le16(common->curbssid + 4) |
			   ((common->curaid & 0x3fff) << AR5K_BSS_ID1_AID_S),
			   AR5K_BSS_ID1);

	अगर (common->curaid == 0) अणु
		ath5k_hw_disable_pspoll(ah);
		वापस;
	पूर्ण

	AR5K_REG_WRITE_BITS(ah, AR5K_BEACON, AR5K_BEACON_TIM,
			    tim_offset ? tim_offset + 4 : 0);

	ath5k_hw_enable_pspoll(ah, शून्य, 0);
पूर्ण

/**
 * ath5k_hw_set_bssid_mask() - Filter out bssids we listen
 * @ah: The &काष्ठा ath5k_hw
 * @mask: The BSSID mask to set (array of octets)
 *
 * BSSID masking is a method used by AR5212 and newer hardware to inक्रमm PCU
 * which bits of the पूर्णांकerface's MAC address should be looked at when trying
 * to decide which packets to ACK. In station mode and AP mode with a single
 * BSS every bit matters since we lock to only one BSS. In AP mode with
 * multiple BSSes (भव पूर्णांकerfaces) not every bit matters because hw must
 * accept frames क्रम all BSSes and so we tweak some bits of our mac address
 * in order to have multiple BSSes.
 *
 * For more inक्रमmation check out ../hw.c of the common ath module.
 */
व्योम
ath5k_hw_set_bssid_mask(काष्ठा ath5k_hw *ah, स्थिर u8 *mask)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);

	/* Cache bssid mask so that we can restore it
	 * on reset */
	स_नकल(common->bssidmask, mask, ETH_ALEN);
	अगर (ah->ah_version == AR5K_AR5212)
		ath_hw_setbssidmask(common);
पूर्ण

/**
 * ath5k_hw_set_mcast_filter() - Set multicast filter
 * @ah: The &काष्ठा ath5k_hw
 * @filter0: Lower 32bits of muticast filter
 * @filter1: Higher 16bits of multicast filter
 */
व्योम
ath5k_hw_set_mcast_filter(काष्ठा ath5k_hw *ah, u32 filter0, u32 filter1)
अणु
	ath5k_hw_reg_ग_लिखो(ah, filter0, AR5K_MCAST_FILTER0);
	ath5k_hw_reg_ग_लिखो(ah, filter1, AR5K_MCAST_FILTER1);
पूर्ण

/**
 * ath5k_hw_get_rx_filter() - Get current rx filter
 * @ah: The &काष्ठा ath5k_hw
 *
 * Returns the RX filter by पढ़ोing rx filter and
 * phy error filter रेजिस्टरs. RX filter is used
 * to set the allowed frame types that PCU will accept
 * and pass to the driver. For a list of frame types
 * check out reg.h.
 */
u32
ath5k_hw_get_rx_filter(काष्ठा ath5k_hw *ah)
अणु
	u32 data, filter = 0;

	filter = ath5k_hw_reg_पढ़ो(ah, AR5K_RX_FILTER);

	/*Radar detection क्रम 5212*/
	अगर (ah->ah_version == AR5K_AR5212) अणु
		data = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_ERR_FIL);

		अगर (data & AR5K_PHY_ERR_FIL_RADAR)
			filter |= AR5K_RX_FILTER_RADARERR;
		अगर (data & (AR5K_PHY_ERR_FIL_OFDM | AR5K_PHY_ERR_FIL_CCK))
			filter |= AR5K_RX_FILTER_PHYERR;
	पूर्ण

	वापस filter;
पूर्ण

/**
 * ath5k_hw_set_rx_filter() - Set rx filter
 * @ah: The &काष्ठा ath5k_hw
 * @filter: RX filter mask (see reg.h)
 *
 * Sets RX filter रेजिस्टर and also handles PHY error filter
 * रेजिस्टर on 5212 and newer chips so that we have proper PHY
 * error reporting.
 */
व्योम
ath5k_hw_set_rx_filter(काष्ठा ath5k_hw *ah, u32 filter)
अणु
	u32 data = 0;

	/* Set PHY error filter रेजिस्टर on 5212*/
	अगर (ah->ah_version == AR5K_AR5212) अणु
		अगर (filter & AR5K_RX_FILTER_RADARERR)
			data |= AR5K_PHY_ERR_FIL_RADAR;
		अगर (filter & AR5K_RX_FILTER_PHYERR)
			data |= AR5K_PHY_ERR_FIL_OFDM | AR5K_PHY_ERR_FIL_CCK;
	पूर्ण

	/*
	 * The AR5210 uses promiscuous mode to detect radar activity
	 */
	अगर (ah->ah_version == AR5K_AR5210 &&
			(filter & AR5K_RX_FILTER_RADARERR)) अणु
		filter &= ~AR5K_RX_FILTER_RADARERR;
		filter |= AR5K_RX_FILTER_PROM;
	पूर्ण

	/*Zero length DMA (phy error reporting) */
	अगर (data)
		AR5K_REG_ENABLE_BITS(ah, AR5K_RXCFG, AR5K_RXCFG_ZLFDMA);
	अन्यथा
		AR5K_REG_DISABLE_BITS(ah, AR5K_RXCFG, AR5K_RXCFG_ZLFDMA);

	/*Write RX Filter रेजिस्टर*/
	ath5k_hw_reg_ग_लिखो(ah, filter & 0xff, AR5K_RX_FILTER);

	/*Write PHY error filter रेजिस्टर on 5212*/
	अगर (ah->ah_version == AR5K_AR5212)
		ath5k_hw_reg_ग_लिखो(ah, data, AR5K_PHY_ERR_FIL);

पूर्ण


/****************\
* Beacon control *
\****************/

#घोषणा ATH5K_MAX_TSF_READ 10

/**
 * ath5k_hw_get_tsf64() - Get the full 64bit TSF
 * @ah: The &काष्ठा ath5k_hw
 *
 * Returns the current TSF
 */
u64
ath5k_hw_get_tsf64(काष्ठा ath5k_hw *ah)
अणु
	u32 tsf_lower, tsf_upper1, tsf_upper2;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* This code is समय critical - we करोn't want to be पूर्णांकerrupted here */
	local_irq_save(flags);

	/*
	 * While पढ़ोing TSF upper and then lower part, the घड़ी is still
	 * counting (or jumping in हाल of IBSS merge) so we might get
	 * inconsistent values. To aव्योम this, we पढ़ो the upper part again
	 * and check it has not been changed. We make the hypothesis that a
	 * maximum of 3 changes can happens in a row (we use 10 as a safe
	 * value).
	 *
	 * Impact on perक्रमmance is pretty small, since in most हालs, only
	 * 3 रेजिस्टर पढ़ोs are needed.
	 */

	tsf_upper1 = ath5k_hw_reg_पढ़ो(ah, AR5K_TSF_U32);
	क्रम (i = 0; i < ATH5K_MAX_TSF_READ; i++) अणु
		tsf_lower = ath5k_hw_reg_पढ़ो(ah, AR5K_TSF_L32);
		tsf_upper2 = ath5k_hw_reg_पढ़ो(ah, AR5K_TSF_U32);
		अगर (tsf_upper2 == tsf_upper1)
			अवरोध;
		tsf_upper1 = tsf_upper2;
	पूर्ण

	local_irq_restore(flags);

	WARN_ON(i == ATH5K_MAX_TSF_READ);

	वापस ((u64)tsf_upper1 << 32) | tsf_lower;
पूर्ण

#अघोषित ATH5K_MAX_TSF_READ

/**
 * ath5k_hw_set_tsf64() - Set a new 64bit TSF
 * @ah: The &काष्ठा ath5k_hw
 * @tsf64: The new 64bit TSF
 *
 * Sets the new TSF
 */
व्योम
ath5k_hw_set_tsf64(काष्ठा ath5k_hw *ah, u64 tsf64)
अणु
	ath5k_hw_reg_ग_लिखो(ah, tsf64 & 0xffffffff, AR5K_TSF_L32);
	ath5k_hw_reg_ग_लिखो(ah, (tsf64 >> 32) & 0xffffffff, AR5K_TSF_U32);
पूर्ण

/**
 * ath5k_hw_reset_tsf() - Force a TSF reset
 * @ah: The &काष्ठा ath5k_hw
 *
 * Forces a TSF reset on PCU
 */
व्योम
ath5k_hw_reset_tsf(काष्ठा ath5k_hw *ah)
अणु
	u32 val;

	val = ath5k_hw_reg_पढ़ो(ah, AR5K_BEACON) | AR5K_BEACON_RESET_TSF;

	/*
	 * Each ग_लिखो to the RESET_TSF bit toggles a hardware पूर्णांकernal
	 * संकेत to reset TSF, but अगर left high it will cause a TSF reset
	 * on the next chip reset as well.  Thus we always ग_लिखो the value
	 * twice to clear the संकेत.
	 */
	ath5k_hw_reg_ग_लिखो(ah, val, AR5K_BEACON);
	ath5k_hw_reg_ग_लिखो(ah, val, AR5K_BEACON);
पूर्ण

/**
 * ath5k_hw_init_beacon_समयrs() - Initialize beacon समयrs
 * @ah: The &काष्ठा ath5k_hw
 * @next_beacon: Next TBTT
 * @पूर्णांकerval: Current beacon पूर्णांकerval
 *
 * This function is used to initialize beacon समयrs based on current
 * operation mode and settings.
 */
व्योम
ath5k_hw_init_beacon_समयrs(काष्ठा ath5k_hw *ah, u32 next_beacon, u32 पूर्णांकerval)
अणु
	u32 समयr1, समयr2, समयr3;

	/*
	 * Set the additional समयrs by mode
	 */
	चयन (ah->opmode) अणु
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_STATION:
		/* In STA mode समयr1 is used as next wakeup
		 * समयr and समयr2 as next CFP duration start
		 * समयr. Both in 1/8TUs. */
		/* TODO: PCF handling */
		अगर (ah->ah_version == AR5K_AR5210) अणु
			समयr1 = 0xffffffff;
			समयr2 = 0xffffffff;
		पूर्ण अन्यथा अणु
			समयr1 = 0x0000ffff;
			समयr2 = 0x0007ffff;
		पूर्ण
		/* Mark associated AP as PCF incapable क्रम now */
		AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1, AR5K_STA_ID1_PCF);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		AR5K_REG_ENABLE_BITS(ah, AR5K_TXCFG, AR5K_TXCFG_ADHOC_BCN_ATIM);
		fallthrough;
	शेष:
		/* On non-STA modes समयr1 is used as next DMA
		 * beacon alert (DBA) समयr and समयr2 as next
		 * software beacon alert. Both in 1/8TUs. */
		समयr1 = (next_beacon - AR5K_TUNE_DMA_BEACON_RESP) << 3;
		समयr2 = (next_beacon - AR5K_TUNE_SW_BEACON_RESP) << 3;
		अवरोध;
	पूर्ण

	/* Timer3 marks the end of our ATIM winकरोw
	 * a zero length winकरोw is not allowed because
	 * we 'll get no beacons */
	समयr3 = next_beacon + 1;

	/*
	 * Set the beacon रेजिस्टर and enable all समयrs.
	 */
	/* When in AP or Mesh Poपूर्णांक mode zero समयr0 to start TSF */
	अगर (ah->opmode == NL80211_IFTYPE_AP ||
	    ah->opmode == NL80211_IFTYPE_MESH_POINT)
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_TIMER0);

	ath5k_hw_reg_ग_लिखो(ah, next_beacon, AR5K_TIMER0);
	ath5k_hw_reg_ग_लिखो(ah, समयr1, AR5K_TIMER1);
	ath5k_hw_reg_ग_लिखो(ah, समयr2, AR5K_TIMER2);
	ath5k_hw_reg_ग_लिखो(ah, समयr3, AR5K_TIMER3);

	/* Force a TSF reset अगर requested and enable beacons */
	अगर (पूर्णांकerval & AR5K_BEACON_RESET_TSF)
		ath5k_hw_reset_tsf(ah);

	ath5k_hw_reg_ग_लिखो(ah, पूर्णांकerval & (AR5K_BEACON_PERIOD |
					AR5K_BEACON_ENABLE),
						AR5K_BEACON);

	/* Flush any pending BMISS पूर्णांकerrupts on ISR by
	 * perक्रमming a clear-on-ग_लिखो operation on PISR
	 * रेजिस्टर क्रम the BMISS bit (writing a bit on
	 * ISR toggles a reset क्रम that bit and leaves
	 * the reमुख्यing bits पूर्णांकact) */
	अगर (ah->ah_version == AR5K_AR5210)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_ISR_BMISS, AR5K_ISR);
	अन्यथा
		ath5k_hw_reg_ग_लिखो(ah, AR5K_ISR_BMISS, AR5K_PISR);

	/* TODO: Set enhanced sleep रेजिस्टरs on AR5212
	 * based on vअगर->bss_conf params, until then
	 * disable घातer save reporting.*/
	AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1, AR5K_STA_ID1_PWR_SV);

पूर्ण

/**
 * ath5k_check_समयr_win() - Check अगर समयr B is समयr A + winकरोw
 * @a: समयr a (beक्रमe b)
 * @b: समयr b (after a)
 * @winकरोw: dअगरference between a and b
 * @पूर्णांकval: समयrs are increased by this पूर्णांकerval
 *
 * This helper function checks अगर समयr B is समयr A + winकरोw and covers
 * हालs where समयr A or B might have alपढ़ोy been updated or wrapped
 * around (Timers are 16 bit).
 *
 * Returns true अगर O.K.
 */
अटल अंतरभूत bool
ath5k_check_समयr_win(पूर्णांक a, पूर्णांक b, पूर्णांक winकरोw, पूर्णांक पूर्णांकval)
अणु
	/*
	 * 1.) usually B should be A + winकरोw
	 * 2.) A alपढ़ोy updated, B not updated yet
	 * 3.) A alपढ़ोy updated and has wrapped around
	 * 4.) B has wrapped around
	 */
	अगर ((b - a == winकरोw) ||				/* 1.) */
	    (a - b == पूर्णांकval - winकरोw) ||			/* 2.) */
	    ((a | 0x10000) - b == पूर्णांकval - winकरोw) ||		/* 3.) */
	    ((b | 0x10000) - a == winकरोw))			/* 4.) */
		वापस true; /* O.K. */
	वापस false;
पूर्ण

/**
 * ath5k_hw_check_beacon_समयrs() - Check अगर the beacon समयrs are correct
 * @ah: The &काष्ठा ath5k_hw
 * @पूर्णांकval: beacon पूर्णांकerval
 *
 * This is a workaround क्रम IBSS mode
 *
 * The need क्रम this function arises from the fact that we have 4 separate
 * HW समयr रेजिस्टरs (TIMER0 - TIMER3), which are बंदly related to the
 * next beacon target समय (NBTT), and that the HW updates these समयrs
 * separately based on the current TSF value. The hardware increments each
 * समयr by the beacon पूर्णांकerval, when the local TSF converted to TU is equal
 * to the value stored in the समयr.
 *
 * The reception of a beacon with the same BSSID can update the local HW TSF
 * at any समय - this is something we can't aव्योम. If the TSF jumps to a
 * समय which is later than the समय stored in a समयr, this समयr will not
 * be updated until the TSF in TU wraps around at 16 bit (the size of the
 * समयrs) and reaches the समय which is stored in the समयr.
 *
 * The problem is that these समयrs are बंदly related to TIMER0 (NBTT) and
 * that they define a समय "window". When the TSF jumps between two समयrs
 * (e.g. ATIM and NBTT), the one in the past will be left behind (not
 * updated), जबतक the one in the future will be updated every beacon
 * पूर्णांकerval. This causes the winकरोw to get larger, until the TSF wraps
 * around as described above and the समयr which was left behind माला_लो
 * updated again. But - because the beacon पूर्णांकerval is usually not an exact
 * भागisor of the size of the समयrs (16 bit), an unwanted "window" between
 * these समयrs has developed!
 *
 * This is especially important with the ATIM winकरोw, because during
 * the ATIM winकरोw only ATIM frames and no data frames are allowed to be
 * sent, which creates transmission छोड़ोs after each beacon. This symptom
 * has been described as "ramping ping" because ping बार increase linearly
 * क्रम some समय and then drop करोwn again. A wrong winकरोw on the DMA beacon
 * समयr has the same effect, so we check क्रम these two conditions.
 *
 * Returns true अगर O.K.
 */
bool
ath5k_hw_check_beacon_समयrs(काष्ठा ath5k_hw *ah, पूर्णांक पूर्णांकval)
अणु
	अचिन्हित पूर्णांक nbtt, atim, dma;

	nbtt = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER0);
	atim = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER3);
	dma = ath5k_hw_reg_पढ़ो(ah, AR5K_TIMER1) >> 3;

	/* NOTE: SWBA is dअगरferent. Having a wrong winकरोw there करोes not
	 * stop us from sending data and this condition is caught by
	 * other means (SWBA पूर्णांकerrupt) */

	अगर (ath5k_check_समयr_win(nbtt, atim, 1, पूर्णांकval) &&
	    ath5k_check_समयr_win(dma, nbtt, AR5K_TUNE_DMA_BEACON_RESP,
				  पूर्णांकval))
		वापस true; /* O.K. */
	वापस false;
पूर्ण

/**
 * ath5k_hw_set_coverage_class() - Set IEEE 802.11 coverage class
 * @ah: The &काष्ठा ath5k_hw
 * @coverage_class: IEEE 802.11 coverage class number
 *
 * Sets IFS पूर्णांकervals and ACK/CTS समयouts क्रम given coverage class.
 */
व्योम
ath5k_hw_set_coverage_class(काष्ठा ath5k_hw *ah, u8 coverage_class)
अणु
	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	पूर्णांक slot_समय = ath5k_hw_get_शेष_slotसमय(ah) + 3 * coverage_class;
	पूर्णांक ack_समयout = ath5k_hw_get_शेष_sअगरs(ah) + slot_समय;
	पूर्णांक cts_समयout = ack_समयout;

	ath5k_hw_set_अगरs_पूर्णांकervals(ah, slot_समय);
	ath5k_hw_set_ack_समयout(ah, ack_समयout);
	ath5k_hw_set_cts_समयout(ah, cts_समयout);

	ah->ah_coverage_class = coverage_class;
पूर्ण

/***************************\
* Init/Start/Stop functions *
\***************************/

/**
 * ath5k_hw_start_rx_pcu() - Start RX engine
 * @ah: The &काष्ठा ath5k_hw
 *
 * Starts RX engine on PCU so that hw can process RXed frames
 * (ACK etc).
 *
 * NOTE: RX DMA should be alपढ़ोy enabled using ath5k_hw_start_rx_dma
 */
व्योम
ath5k_hw_start_rx_pcu(काष्ठा ath5k_hw *ah)
अणु
	AR5K_REG_DISABLE_BITS(ah, AR5K_DIAG_SW, AR5K_DIAG_SW_DIS_RX);
पूर्ण

/**
 * at5k_hw_stop_rx_pcu() - Stop RX engine
 * @ah: The &काष्ठा ath5k_hw
 *
 * Stops RX engine on PCU
 */
व्योम
ath5k_hw_stop_rx_pcu(काष्ठा ath5k_hw *ah)
अणु
	AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW, AR5K_DIAG_SW_DIS_RX);
पूर्ण

/**
 * ath5k_hw_set_opmode() - Set PCU operating mode
 * @ah: The &काष्ठा ath5k_hw
 * @op_mode: One of क्रमागत nl80211_अगरtype
 *
 * Configure PCU क्रम the various operating modes (AP/STA etc)
 */
पूर्णांक
ath5k_hw_set_opmode(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype op_mode)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	u32 pcu_reg, beacon_reg, low_id, high_id;

	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "mode %d\n", op_mode);

	/* Preserve rest settings */
	pcu_reg = ath5k_hw_reg_पढ़ो(ah, AR5K_STA_ID1) & 0xffff0000;
	pcu_reg &= ~(AR5K_STA_ID1_ADHOC | AR5K_STA_ID1_AP
			| AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
			(AR5K_STA_ID1_PWR_SV | AR5K_STA_ID1_NO_PSPOLL) : 0));

	beacon_reg = 0;

	चयन (op_mode) अणु
	हाल NL80211_IFTYPE_ADHOC:
		pcu_reg |= AR5K_STA_ID1_ADHOC | AR5K_STA_ID1_KEYSRCH_MODE;
		beacon_reg |= AR5K_BCR_ADHOC;
		अगर (ah->ah_version == AR5K_AR5210)
			pcu_reg |= AR5K_STA_ID1_NO_PSPOLL;
		अन्यथा
			AR5K_REG_ENABLE_BITS(ah, AR5K_CFG, AR5K_CFG_IBSS);
		अवरोध;

	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		pcu_reg |= AR5K_STA_ID1_AP | AR5K_STA_ID1_KEYSRCH_MODE;
		beacon_reg |= AR5K_BCR_AP;
		अगर (ah->ah_version == AR5K_AR5210)
			pcu_reg |= AR5K_STA_ID1_NO_PSPOLL;
		अन्यथा
			AR5K_REG_DISABLE_BITS(ah, AR5K_CFG, AR5K_CFG_IBSS);
		अवरोध;

	हाल NL80211_IFTYPE_STATION:
		pcu_reg |= AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
				AR5K_STA_ID1_PWR_SV : 0);
		fallthrough;
	हाल NL80211_IFTYPE_MONITOR:
		pcu_reg |= AR5K_STA_ID1_KEYSRCH_MODE
			| (ah->ah_version == AR5K_AR5210 ?
				AR5K_STA_ID1_NO_PSPOLL : 0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set PCU रेजिस्टरs
	 */
	low_id = get_unaligned_le32(common->macaddr);
	high_id = get_unaligned_le16(common->macaddr + 4);
	ath5k_hw_reg_ग_लिखो(ah, low_id, AR5K_STA_ID0);
	ath5k_hw_reg_ग_लिखो(ah, pcu_reg | high_id, AR5K_STA_ID1);

	/*
	 * Set Beacon Control Register on 5210
	 */
	अगर (ah->ah_version == AR5K_AR5210)
		ath5k_hw_reg_ग_लिखो(ah, beacon_reg, AR5K_BCR);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_pcu_init() - Initialize PCU
 * @ah: The &काष्ठा ath5k_hw
 * @op_mode: One of क्रमागत nl80211_अगरtype
 *
 * This function is used to initialize PCU by setting current
 * operation mode and various other settings.
 */
व्योम
ath5k_hw_pcu_init(काष्ठा ath5k_hw *ah, क्रमागत nl80211_अगरtype op_mode)
अणु
	/* Set bssid and bssid mask */
	ath5k_hw_set_bssid(ah);

	/* Set PCU config */
	ath5k_hw_set_opmode(ah, op_mode);

	/* Write rate duration table only on AR5212 and अगर
	 * भव पूर्णांकerface has alपढ़ोy been brought up
	 * XXX: rethink this after new mode changes to
	 * mac80211 are पूर्णांकegrated */
	अगर (ah->ah_version == AR5K_AR5212 &&
		ah->nvअगरs)
		ath5k_hw_ग_लिखो_rate_duration(ah);

	/* Set RSSI/BRSSI thresholds
	 *
	 * Note: If we decide to set this value
	 * dynamically, have in mind that when AR5K_RSSI_THR
	 * रेजिस्टर is पढ़ो it might वापस 0x40 अगर we haven't
	 * wrote anything to it plus BMISS RSSI threshold is zeroed.
	 * So करोing a save/restore procedure here isn't the right
	 * choice. Instead store it on ath5k_hw */
	ath5k_hw_reg_ग_लिखो(ah, (AR5K_TUNE_RSSI_THRES |
				AR5K_TUNE_BMISS_THRES <<
				AR5K_RSSI_THR_BMISS_S),
				AR5K_RSSI_THR);

	/* MIC QoS support */
	अगर (ah->ah_mac_srev >= AR5K_SREV_AR2413) अणु
		ath5k_hw_reg_ग_लिखो(ah, 0x000100aa, AR5K_MIC_QOS_CTL);
		ath5k_hw_reg_ग_लिखो(ah, 0x00003210, AR5K_MIC_QOS_SEL);
	पूर्ण

	/* QoS NOACK Policy */
	अगर (ah->ah_version == AR5K_AR5212) अणु
		ath5k_hw_reg_ग_लिखो(ah,
			AR5K_REG_SM(2, AR5K_QOS_NOACK_2BIT_VALUES) |
			AR5K_REG_SM(5, AR5K_QOS_NOACK_BIT_OFFSET)  |
			AR5K_REG_SM(0, AR5K_QOS_NOACK_BYTE_OFFSET),
			AR5K_QOS_NOACK);
	पूर्ण

	/* Restore slot समय and ACK समयouts */
	अगर (ah->ah_coverage_class > 0)
		ath5k_hw_set_coverage_class(ah, ah->ah_coverage_class);

	/* Set ACK bitrate mode (see ack_rates_high) */
	अगर (ah->ah_version == AR5K_AR5212) अणु
		u32 val = AR5K_STA_ID1_BASE_RATE_11B | AR5K_STA_ID1_ACKCTS_6MB;
		अगर (ah->ah_ack_bitrate_high)
			AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1, val);
		अन्यथा
			AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1, val);
	पूर्ण
	वापस;
पूर्ण

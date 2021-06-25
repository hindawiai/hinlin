<शैली गुरु>
/*
 * Copyright (c) 2004-2007 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2009 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2007-2008 Jiri Slaby <jirislaby@gmail.com>
 * Copyright (c) 2008-2009 Felix Fietkau <nbd@खोलोwrt.org>
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

/***********************\
* PHY related functions *
\***********************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "rfbuffer.h"
#समावेश "rfgain.h"
#समावेश "../regd.h"


/**
 * DOC: PHY related functions
 *
 * Here we handle the low-level functions related to baseband
 * and analog frontend (RF) parts. This is by far the most complex
 * part of the hw code so make sure you know what you are करोing.
 *
 * Here is a list of what this is all about:
 *
 * - Channel setting/चयनing
 *
 * - Automatic Gain Control (AGC) calibration
 *
 * - Noise Floor calibration
 *
 * - I/Q imbalance calibration (QAM correction)
 *
 * - Calibration due to thermal changes (gain_F)
 *
 * - Spur noise mitigation
 *
 * - RF/PHY initialization क्रम the various operating modes and bwmodes
 *
 * - Antenna control
 *
 * - TX घातer control per channel/rate/packet type
 *
 * Also have in mind we never got करोcumentation क्रम most of these
 * functions, what we have comes mostly from Atheros's code, reverse
 * engineering and patent करोcs/presentations etc.
 */


/******************\
* Helper functions *
\******************/

/**
 * ath5k_hw_radio_revision() - Get the PHY Chip revision
 * @ah: The &काष्ठा ath5k_hw
 * @band: One of क्रमागत nl80211_band
 *
 * Returns the revision number of a 2GHz, 5GHz or single chip
 * radio.
 */
u16
ath5k_hw_radio_revision(काष्ठा ath5k_hw *ah, क्रमागत nl80211_band band)
अणु
	अचिन्हित पूर्णांक i;
	u32 srev;
	u16 ret;

	/*
	 * Set the radio chip access रेजिस्टर
	 */
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SHIFT_2GHZ, AR5K_PHY(0));
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	usleep_range(2000, 2500);

	/* ...रुको until PHY is पढ़ोy and पढ़ो the selected radio revision */
	ath5k_hw_reg_ग_लिखो(ah, 0x00001c16, AR5K_PHY(0x34));

	क्रम (i = 0; i < 8; i++)
		ath5k_hw_reg_ग_लिखो(ah, 0x00010000, AR5K_PHY(0x20));

	अगर (ah->ah_version == AR5K_AR5210) अणु
		srev = (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY(256)) >> 28) & 0xf;
		ret = (u16)ath5k_hw_bitswap(srev, 4) + 1;
	पूर्ण अन्यथा अणु
		srev = (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY(0x100)) >> 24) & 0xff;
		ret = (u16)ath5k_hw_bitswap(((srev & 0xf0) >> 4) |
				((srev & 0x0f) << 4), 8);
	पूर्ण

	/* Reset to the 5GHz mode */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_SHIFT_5GHZ, AR5K_PHY(0));

	वापस ret;
पूर्ण

/**
 * ath5k_channel_ok() - Check अगर a channel is supported by the hw
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Note: We करोn't do any regulatory domain checks here, it's just
 * a sanity check.
 */
bool
ath5k_channel_ok(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel)
अणु
	u16 freq = channel->center_freq;

	/* Check अगर the channel is in our supported range */
	अगर (channel->band == NL80211_BAND_2GHZ) अणु
		अगर ((freq >= ah->ah_capabilities.cap_range.range_2ghz_min) &&
		    (freq <= ah->ah_capabilities.cap_range.range_2ghz_max))
			वापस true;
	पूर्ण अन्यथा अगर (channel->band == NL80211_BAND_5GHZ)
		अगर ((freq >= ah->ah_capabilities.cap_range.range_5ghz_min) &&
		    (freq <= ah->ah_capabilities.cap_range.range_5ghz_max))
			वापस true;

	वापस false;
पूर्ण

/**
 * ath5k_hw_chan_has_spur_noise() - Check अगर channel is sensitive to spur noise
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 */
bool
ath5k_hw_chan_has_spur_noise(काष्ठा ath5k_hw *ah,
				काष्ठा ieee80211_channel *channel)
अणु
	u8 refclk_freq;

	अगर ((ah->ah_radio == AR5K_RF5112) ||
	(ah->ah_radio == AR5K_RF5413) ||
	(ah->ah_radio == AR5K_RF2413) ||
	(ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4)))
		refclk_freq = 40;
	अन्यथा
		refclk_freq = 32;

	अगर ((channel->center_freq % refclk_freq != 0) &&
	((channel->center_freq % refclk_freq < 10) ||
	(channel->center_freq % refclk_freq > 22)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/**
 * ath5k_hw_rfb_op() - Perक्रमm an operation on the given RF Buffer
 * @ah: The &काष्ठा ath5k_hw
 * @rf_regs: The काष्ठा ath5k_rf_reg
 * @val: New value
 * @reg_id: RF रेजिस्टर ID
 * @set: Indicate we need to swap data
 *
 * This is an पूर्णांकernal function used to modअगरy RF Banks beक्रमe
 * writing them to AR5K_RF_BUFFER. Check out rfbuffer.h क्रम more
 * infos.
 */
अटल अचिन्हित पूर्णांक
ath5k_hw_rfb_op(काष्ठा ath5k_hw *ah, स्थिर काष्ठा ath5k_rf_reg *rf_regs,
					u32 val, u8 reg_id, bool set)
अणु
	स्थिर काष्ठा ath5k_rf_reg *rfreg = शून्य;
	u8 offset, bank, num_bits, col, position;
	u16 entry;
	u32 mask, data, last_bit, bits_shअगरted, first_bit;
	u32 *rfb;
	s32 bits_left;
	पूर्णांक i;

	data = 0;
	rfb = ah->ah_rf_banks;

	क्रम (i = 0; i < ah->ah_rf_regs_count; i++) अणु
		अगर (rf_regs[i].index == reg_id) अणु
			rfreg = &rf_regs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rfb == शून्य || rfreg == शून्य) अणु
		ATH5K_PRINTF("Rf register not found!\n");
		/* should not happen */
		वापस 0;
	पूर्ण

	bank = rfreg->bank;
	num_bits = rfreg->field.len;
	first_bit = rfreg->field.pos;
	col = rfreg->field.col;

	/* first_bit is an offset from bank's
	 * start. Since we have all banks on
	 * the same array, we use this offset
	 * to mark each bank's start */
	offset = ah->ah_offset[bank];

	/* Boundary check */
	अगर (!(col <= 3 && num_bits <= 32 && first_bit + num_bits <= 319)) अणु
		ATH5K_PRINTF("invalid values at offset %u\n", offset);
		वापस 0;
	पूर्ण

	entry = ((first_bit - 1) / 8) + offset;
	position = (first_bit - 1) % 8;

	अगर (set)
		data = ath5k_hw_bitswap(val, num_bits);

	क्रम (bits_shअगरted = 0, bits_left = num_bits; bits_left > 0;
	     position = 0, entry++) अणु

		last_bit = (position + bits_left > 8) ? 8 :
					position + bits_left;

		mask = (((1 << last_bit) - 1) ^ ((1 << position) - 1)) <<
								(col * 8);

		अगर (set) अणु
			rfb[entry] &= ~mask;
			rfb[entry] |= ((data << position) << (col * 8)) & mask;
			data >>= (8 - position);
		पूर्ण अन्यथा अणु
			data |= (((rfb[entry] & mask) >> (col * 8)) >> position)
				<< bits_shअगरted;
			bits_shअगरted += last_bit - position;
		पूर्ण

		bits_left -= 8 - position;
	पूर्ण

	data = set ? 1 : ath5k_hw_bitswap(data, num_bits);

	वापस data;
पूर्ण

/**
 * ath5k_hw_ग_लिखो_ofdm_timings() - set OFDM timings on AR5212
 * @ah: the &काष्ठा ath5k_hw
 * @channel: the currently set channel upon reset
 *
 * Write the delta slope coefficient (used on pilot tracking ?) क्रम OFDM
 * operation on the AR5212 upon reset. This is a helper क्रम ath5k_hw_phy_init.
 *
 * Since delta slope is भग्नing poपूर्णांक we split it on its exponent and
 * mantissa and provide these values on hw.
 *
 * For more infos i think this patent is related
 * "http://www.freepatentsonline.com/7184495.html"
 */
अटल अंतरभूत पूर्णांक
ath5k_hw_ग_लिखो_ofdm_timings(काष्ठा ath5k_hw *ah,
				काष्ठा ieee80211_channel *channel)
अणु
	/* Get exponent and mantissa and set it */
	u32 coef_scaled, coef_exp, coef_man,
		ds_coef_exp, ds_coef_man, घड़ी;

	BUG_ON(!(ah->ah_version == AR5K_AR5212) ||
		(channel->hw_value == AR5K_MODE_11B));

	/* Get coefficient
	 * ALGO: coef = (5 * घड़ी / carrier_freq) / 2
	 * we scale coef by shअगरting घड़ी value by 24 क्रम
	 * better precision since we use पूर्णांकegers */
	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_40MHZ:
		घड़ी = 40 * 2;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		घड़ी = 40 / 2;
		अवरोध;
	हाल AR5K_BWMODE_5MHZ:
		घड़ी = 40 / 4;
		अवरोध;
	शेष:
		घड़ी = 40;
		अवरोध;
	पूर्ण
	coef_scaled = ((5 * (घड़ी << 24)) / 2) / channel->center_freq;

	/* Get exponent
	 * ALGO: coef_exp = 14 - highest set bit position */
	coef_exp = ilog2(coef_scaled);

	/* Doesn't make sense if it's zero*/
	अगर (!coef_scaled || !coef_exp)
		वापस -EINVAL;

	/* Note: we've shअगरted coef_scaled by 24 */
	coef_exp = 14 - (coef_exp - 24);


	/* Get mantissa (signअगरicant digits)
	 * ALGO: coef_mant = न्यूनमान(coef_scaled* 2^coef_exp+0.5) */
	coef_man = coef_scaled +
		(1 << (24 - coef_exp - 1));

	/* Calculate delta slope coefficient exponent
	 * and mantissa (हटाओ scaling) and set them on hw */
	ds_coef_man = coef_man >> (24 - coef_exp);
	ds_coef_exp = coef_exp - 16;

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_3,
		AR5K_PHY_TIMING_3_DSC_MAN, ds_coef_man);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_3,
		AR5K_PHY_TIMING_3_DSC_EXP, ds_coef_exp);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_phy_disable() - Disable PHY
 * @ah: The &काष्ठा ath5k_hw
 */
पूर्णांक ath5k_hw_phy_disable(काष्ठा ath5k_hw *ah)
अणु
	/*Just a try M.F.*/
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ACT_DISABLE, AR5K_PHY_ACT);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_रुको_क्रम_synth() - Wait क्रम synth to settle
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 */
अटल व्योम
ath5k_hw_रुको_क्रम_synth(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel)
अणु
	/*
	 * On 5211+ पढ़ो activation -> rx delay
	 * and use it (100ns steps).
	 */
	अगर (ah->ah_version != AR5K_AR5210) अणु
		u32 delay;
		delay = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_RX_DELAY) &
			AR5K_PHY_RX_DELAY_M;
		delay = (channel->hw_value == AR5K_MODE_11B) ?
			((delay << 2) / 22) : (delay / 10);
		अगर (ah->ah_bwmode == AR5K_BWMODE_10MHZ)
			delay = delay << 1;
		अगर (ah->ah_bwmode == AR5K_BWMODE_5MHZ)
			delay = delay << 2;
		/* XXX: /2 on turbo ? Let's be safe
		 * क्रम now */
		usleep_range(100 + delay, 100 + (2 * delay));
	पूर्ण अन्यथा अणु
		usleep_range(1000, 1500);
	पूर्ण
पूर्ण


/**********************\
* RF Gain optimization *
\**********************/

/**
 * DOC: RF Gain optimization
 *
 * This code is used to optimize RF gain on dअगरferent environments
 * (temperature mostly) based on feedback from a घातer detector.
 *
 * It's only used on RF5111 and RF5112, later RF chips seem to have
 * स्वतः adjusपंचांगent on hw -notice they have a much smaller BANK 7 and
 * no gain optimization ladder-.
 *
 * For more infos check out this patent करोc
 * "http://www.freepatentsonline.com/7400691.html"
 *
 * This paper describes घातer drops as seen on the receiver due to
 * probe packets
 * "http://www.cnri.dit.ie/खुलाations/ICT08%20-%20Practical%20Issues
 * %20of%20Power%20Control.pdf"
 *
 * And this is the MadWiFi bug entry related to the above
 * "http://madwifi-project.org/ticket/1659"
 * with various measurements and diagrams
 */

/**
 * ath5k_hw_rfgain_opt_init() - Initialize ah_gain during attach
 * @ah: The &काष्ठा ath5k_hw
 */
पूर्णांक ath5k_hw_rfgain_opt_init(काष्ठा ath5k_hw *ah)
अणु
	/* Initialize the gain optimization values */
	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5111:
		ah->ah_gain.g_step_idx = rfgain_opt_5111.go_शेष;
		ah->ah_gain.g_low = 20;
		ah->ah_gain.g_high = 35;
		ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		अवरोध;
	हाल AR5K_RF5112:
		ah->ah_gain.g_step_idx = rfgain_opt_5112.go_शेष;
		ah->ah_gain.g_low = 20;
		ah->ah_gain.g_high = 85;
		ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ath5k_hw_request_rfgain_probe() - Request a PAPD probe packet
 * @ah: The &काष्ठा ath5k_hw
 *
 * Schedules a gain probe check on the next transmitted packet.
 * That means our next packet is going to be sent with lower
 * tx घातer and a Peak to Average Power Detector (PAPD) will try
 * to measure the gain.
 *
 * TODO: Force a tx packet (bypassing PCU arbitrator etc)
 * just after we enable the probe so that we करोn't mess with
 * standard traffic.
 */
अटल व्योम
ath5k_hw_request_rfgain_probe(काष्ठा ath5k_hw *ah)
अणु

	/* Skip अगर gain calibration is inactive or
	 * we alपढ़ोy handle a probe request */
	अगर (ah->ah_gain.g_state != AR5K_RFGAIN_ACTIVE)
		वापस;

	/* Send the packet with 2dB below max घातer as
	 * patent करोc suggest */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txघातer.txp_ofdm - 4,
			AR5K_PHY_PAPD_PROBE_TXPOWER) |
			AR5K_PHY_PAPD_PROBE_TX_NEXT, AR5K_PHY_PAPD_PROBE);

	ah->ah_gain.g_state = AR5K_RFGAIN_READ_REQUESTED;

पूर्ण

/**
 * ath5k_hw_rf_gainf_corr() - Calculate Gain_F measurement correction
 * @ah: The &काष्ठा ath5k_hw
 *
 * Calculate Gain_F measurement correction
 * based on the current step क्रम RF5112 rev. 2
 */
अटल u32
ath5k_hw_rf_gainf_corr(काष्ठा ath5k_hw *ah)
अणु
	u32 mix, step;
	स्थिर काष्ठा ath5k_gain_opt *go;
	स्थिर काष्ठा ath5k_gain_opt_step *g_step;
	स्थिर काष्ठा ath5k_rf_reg *rf_regs;

	/* Only RF5112 Rev. 2 supports it */
	अगर ((ah->ah_radio != AR5K_RF5112) ||
	(ah->ah_radio_5ghz_revision <= AR5K_SREV_RAD_5112A))
		वापस 0;

	go = &rfgain_opt_5112;
	rf_regs = rf_regs_5112a;
	ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112a);

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	अगर (ah->ah_rf_banks == शून्य)
		वापस 0;

	ah->ah_gain.g_f_corr = 0;

	/* No VGA (Variable Gain Amplअगरier) override, skip */
	अगर (ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXVGA_OVR, false) != 1)
		वापस 0;

	/* Mix gain stepping */
	step = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXGAIN_STEP, false);

	/* Mix gain override */
	mix = g_step->gos_param[0];

	चयन (mix) अणु
	हाल 3:
		ah->ah_gain.g_f_corr = step * 2;
		अवरोध;
	हाल 2:
		ah->ah_gain.g_f_corr = (step - 5) * 2;
		अवरोध;
	हाल 1:
		ah->ah_gain.g_f_corr = step;
		अवरोध;
	शेष:
		ah->ah_gain.g_f_corr = 0;
		अवरोध;
	पूर्ण

	वापस ah->ah_gain.g_f_corr;
पूर्ण

/**
 * ath5k_hw_rf_check_gainf_पढ़ोback() - Validate Gain_F feedback from detector
 * @ah: The &काष्ठा ath5k_hw
 *
 * Check अगर current gain_F measurement is in the range of our
 * घातer detector winकरोws. If we get a measurement outside range
 * we know it's not accurate (detectors can't measure anything outside
 * their detection winकरोw) so we must ignore it.
 *
 * Returns true अगर पढ़ोback was O.K. or false on failure
 */
अटल bool
ath5k_hw_rf_check_gainf_पढ़ोback(काष्ठा ath5k_hw *ah)
अणु
	स्थिर काष्ठा ath5k_rf_reg *rf_regs;
	u32 step, mix_ovr, level[4];

	अगर (ah->ah_rf_banks == शून्य)
		वापस false;

	अगर (ah->ah_radio == AR5K_RF5111) अणु

		rf_regs = rf_regs_5111;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5111);

		step = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_RFGAIN_STEP,
			false);

		level[0] = 0;
		level[1] = (step == 63) ? 50 : step + 4;
		level[2] = (step != 63) ? 64 : level[0];
		level[3] = level[2] + 50;

		ah->ah_gain.g_high = level[3] -
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_HI_MARGIN : -5);
		ah->ah_gain.g_low = level[0] +
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_LO_MARGIN : 0);
	पूर्ण अन्यथा अणु

		rf_regs = rf_regs_5112;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112);

		mix_ovr = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXVGA_OVR,
			false);

		level[0] = level[2] = 0;

		अगर (mix_ovr == 1) अणु
			level[1] = level[3] = 83;
		पूर्ण अन्यथा अणु
			level[1] = level[3] = 107;
			ah->ah_gain.g_high = 55;
		पूर्ण
	पूर्ण

	वापस (ah->ah_gain.g_current >= level[0] &&
			ah->ah_gain.g_current <= level[1]) ||
		(ah->ah_gain.g_current >= level[2] &&
			ah->ah_gain.g_current <= level[3]);
पूर्ण

/**
 * ath5k_hw_rf_gainf_adjust() - Perक्रमm Gain_F adjusपंचांगent
 * @ah: The &काष्ठा ath5k_hw
 *
 * Choose the right target gain based on current gain
 * and RF gain optimization ladder
 */
अटल s8
ath5k_hw_rf_gainf_adjust(काष्ठा ath5k_hw *ah)
अणु
	स्थिर काष्ठा ath5k_gain_opt *go;
	स्थिर काष्ठा ath5k_gain_opt_step *g_step;
	पूर्णांक ret = 0;

	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5111:
		go = &rfgain_opt_5111;
		अवरोध;
	हाल AR5K_RF5112:
		go = &rfgain_opt_5112;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	अगर (ah->ah_gain.g_current >= ah->ah_gain.g_high) अणु

		/* Reached maximum */
		अगर (ah->ah_gain.g_step_idx == 0)
			वापस -1;

		क्रम (ah->ah_gain.g_target = ah->ah_gain.g_current;
				ah->ah_gain.g_target >=  ah->ah_gain.g_high &&
				ah->ah_gain.g_step_idx > 0;
				g_step = &go->go_step[ah->ah_gain.g_step_idx])
			ah->ah_gain.g_target -= 2 *
			    (go->go_step[--(ah->ah_gain.g_step_idx)].gos_gain -
			    g_step->gos_gain);

		ret = 1;
		जाओ करोne;
	पूर्ण

	अगर (ah->ah_gain.g_current <= ah->ah_gain.g_low) अणु

		/* Reached minimum */
		अगर (ah->ah_gain.g_step_idx == (go->go_steps_count - 1))
			वापस -2;

		क्रम (ah->ah_gain.g_target = ah->ah_gain.g_current;
				ah->ah_gain.g_target <= ah->ah_gain.g_low &&
				ah->ah_gain.g_step_idx < go->go_steps_count - 1;
				g_step = &go->go_step[ah->ah_gain.g_step_idx])
			ah->ah_gain.g_target -= 2 *
			    (go->go_step[++ah->ah_gain.g_step_idx].gos_gain -
			    g_step->gos_gain);

		ret = 2;
		जाओ करोne;
	पूर्ण

करोne:
	ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
		"ret %d, gain step %u, current gain %u, target gain %u\n",
		ret, ah->ah_gain.g_step_idx, ah->ah_gain.g_current,
		ah->ah_gain.g_target);

	वापस ret;
पूर्ण

/**
 * ath5k_hw_gainf_calibrate() - Do a gain_F calibration
 * @ah: The &काष्ठा ath5k_hw
 *
 * Main callback क्रम thermal RF gain calibration engine
 * Check क्रम a new gain पढ़ोing and schedule an adjusपंचांगent
 * अगर needed.
 *
 * Returns one of क्रमागत ath5k_rfgain codes
 */
क्रमागत ath5k_rfgain
ath5k_hw_gainf_calibrate(काष्ठा ath5k_hw *ah)
अणु
	u32 data, type;
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;

	अगर (ah->ah_rf_banks == शून्य ||
	ah->ah_gain.g_state == AR5K_RFGAIN_INACTIVE)
		वापस AR5K_RFGAIN_INACTIVE;

	/* No check requested, either engine is inactive
	 * or an adjusपंचांगent is alपढ़ोy requested */
	अगर (ah->ah_gain.g_state != AR5K_RFGAIN_READ_REQUESTED)
		जाओ करोne;

	/* Read the PAPD (Peak to Average Power Detector)
	 * रेजिस्टर */
	data = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_PAPD_PROBE);

	/* No probe is scheduled, पढ़ो gain_F measurement */
	अगर (!(data & AR5K_PHY_PAPD_PROBE_TX_NEXT)) अणु
		ah->ah_gain.g_current = data >> AR5K_PHY_PAPD_PROBE_GAINF_S;
		type = AR5K_REG_MS(data, AR5K_PHY_PAPD_PROBE_TYPE);

		/* If tx packet is CCK correct the gain_F measurement
		 * by cck ofdm gain delta */
		अगर (type == AR5K_PHY_PAPD_PROBE_TYPE_CCK) अणु
			अगर (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A)
				ah->ah_gain.g_current +=
					ee->ee_cck_ofdm_gain_delta;
			अन्यथा
				ah->ah_gain.g_current +=
					AR5K_GAIN_CCK_PROBE_CORR;
		पूर्ण

		/* Further correct gain_F measurement क्रम
		 * RF5112A radios */
		अगर (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A) अणु
			ath5k_hw_rf_gainf_corr(ah);
			ah->ah_gain.g_current =
				ah->ah_gain.g_current >= ah->ah_gain.g_f_corr ?
				(ah->ah_gain.g_current - ah->ah_gain.g_f_corr) :
				0;
		पूर्ण

		/* Check अगर measurement is ok and अगर we need
		 * to adjust gain, schedule a gain adjusपंचांगent,
		 * अन्यथा चयन back to the active state */
		अगर (ath5k_hw_rf_check_gainf_पढ़ोback(ah) &&
		AR5K_GAIN_CHECK_ADJUST(&ah->ah_gain) &&
		ath5k_hw_rf_gainf_adjust(ah)) अणु
			ah->ah_gain.g_state = AR5K_RFGAIN_NEED_CHANGE;
		पूर्ण अन्यथा अणु
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		पूर्ण
	पूर्ण

करोne:
	वापस ah->ah_gain.g_state;
पूर्ण

/**
 * ath5k_hw_rfgain_init() - Write initial RF gain settings to hw
 * @ah: The &काष्ठा ath5k_hw
 * @band: One of क्रमागत nl80211_band
 *
 * Write initial RF gain table to set the RF sensitivity.
 *
 * NOTE: This one works on all RF chips and has nothing to करो
 * with Gain_F calibration
 */
अटल पूर्णांक
ath5k_hw_rfgain_init(काष्ठा ath5k_hw *ah, क्रमागत nl80211_band band)
अणु
	स्थिर काष्ठा ath5k_ini_rfgain *ath5k_rfg;
	अचिन्हित पूर्णांक i, size, index;

	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5111:
		ath5k_rfg = rfgain_5111;
		size = ARRAY_SIZE(rfgain_5111);
		अवरोध;
	हाल AR5K_RF5112:
		ath5k_rfg = rfgain_5112;
		size = ARRAY_SIZE(rfgain_5112);
		अवरोध;
	हाल AR5K_RF2413:
		ath5k_rfg = rfgain_2413;
		size = ARRAY_SIZE(rfgain_2413);
		अवरोध;
	हाल AR5K_RF2316:
		ath5k_rfg = rfgain_2316;
		size = ARRAY_SIZE(rfgain_2316);
		अवरोध;
	हाल AR5K_RF5413:
		ath5k_rfg = rfgain_5413;
		size = ARRAY_SIZE(rfgain_5413);
		अवरोध;
	हाल AR5K_RF2317:
	हाल AR5K_RF2425:
		ath5k_rfg = rfgain_2425;
		size = ARRAY_SIZE(rfgain_2425);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	index = (band == NL80211_BAND_2GHZ) ? 1 : 0;

	क्रम (i = 0; i < size; i++) अणु
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_ग_लिखो(ah, ath5k_rfg[i].rfg_value[index],
			(u32)ath5k_rfg[i].rfg_रेजिस्टर);
	पूर्ण

	वापस 0;
पूर्ण


/********************\
* RF Registers setup *
\********************/

/**
 * ath5k_hw_rfregs_init() - Initialize RF रेजिस्टर settings
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 * @mode: One of क्रमागत ath5k_driver_mode
 *
 * Setup RF रेजिस्टरs by writing RF buffer on hw. For
 * more infos on this, check out rfbuffer.h
 */
अटल पूर्णांक
ath5k_hw_rfregs_init(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel,
			अचिन्हित पूर्णांक mode)
अणु
	स्थिर काष्ठा ath5k_rf_reg *rf_regs;
	स्थिर काष्ठा ath5k_ini_rfbuffer *ini_rfb;
	स्थिर काष्ठा ath5k_gain_opt *go = शून्य;
	स्थिर काष्ठा ath5k_gain_opt_step *g_step;
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 ee_mode = 0;
	u32 *rfb;
	पूर्णांक i, obdb = -1, bank = -1;

	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5111:
		rf_regs = rf_regs_5111;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5111);
		ini_rfb = rfb_5111;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5111);
		go = &rfgain_opt_5111;
		अवरोध;
	हाल AR5K_RF5112:
		अगर (ah->ah_radio_5ghz_revision >= AR5K_SREV_RAD_5112A) अणु
			rf_regs = rf_regs_5112a;
			ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112a);
			ini_rfb = rfb_5112a;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5112a);
		पूर्ण अन्यथा अणु
			rf_regs = rf_regs_5112;
			ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112);
			ini_rfb = rfb_5112;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5112);
		पूर्ण
		go = &rfgain_opt_5112;
		अवरोध;
	हाल AR5K_RF2413:
		rf_regs = rf_regs_2413;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2413);
		ini_rfb = rfb_2413;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2413);
		अवरोध;
	हाल AR5K_RF2316:
		rf_regs = rf_regs_2316;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2316);
		ini_rfb = rfb_2316;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2316);
		अवरोध;
	हाल AR5K_RF5413:
		rf_regs = rf_regs_5413;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5413);
		ini_rfb = rfb_5413;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_5413);
		अवरोध;
	हाल AR5K_RF2317:
		rf_regs = rf_regs_2425;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2425);
		ini_rfb = rfb_2317;
		ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2317);
		अवरोध;
	हाल AR5K_RF2425:
		rf_regs = rf_regs_2425;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_2425);
		अगर (ah->ah_mac_srev < AR5K_SREV_AR2417) अणु
			ini_rfb = rfb_2425;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2425);
		पूर्ण अन्यथा अणु
			ini_rfb = rfb_2417;
			ah->ah_rf_banks_size = ARRAY_SIZE(rfb_2417);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* If it's the first समय we set RF buffer, allocate
	 * ah->ah_rf_banks based on ah->ah_rf_banks_size
	 * we set above */
	अगर (ah->ah_rf_banks == शून्य) अणु
		ah->ah_rf_banks = kदो_स्मृति_array(ah->ah_rf_banks_size,
								माप(u32),
								GFP_KERNEL);
		अगर (ah->ah_rf_banks == शून्य) अणु
			ATH5K_ERR(ah, "out of memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Copy values to modअगरy them */
	rfb = ah->ah_rf_banks;

	क्रम (i = 0; i < ah->ah_rf_banks_size; i++) अणु
		अगर (ini_rfb[i].rfb_bank >= AR5K_MAX_RF_BANKS) अणु
			ATH5K_ERR(ah, "invalid bank\n");
			वापस -EINVAL;
		पूर्ण

		/* Bank changed, ग_लिखो करोwn the offset */
		अगर (bank != ini_rfb[i].rfb_bank) अणु
			bank = ini_rfb[i].rfb_bank;
			ah->ah_offset[bank] = i;
		पूर्ण

		rfb[i] = ini_rfb[i].rfb_mode_data[mode];
	पूर्ण

	/* Set Output and Driver bias current (OB/DB) */
	अगर (channel->band == NL80211_BAND_2GHZ) अणु

		अगर (channel->hw_value == AR5K_MODE_11B)
			ee_mode = AR5K_EEPROM_MODE_11B;
		अन्यथा
			ee_mode = AR5K_EEPROM_MODE_11G;

		/* For RF511X/RF211X combination we
		 * use b_OB and b_DB parameters stored
		 * in eeprom on ee->ee_ob[ee_mode][0]
		 *
		 * For all other chips we use OB/DB क्रम 2GHz
		 * stored in the b/g modal section just like
		 * 802.11a on ee->ee_ob[ee_mode][1] */
		अगर ((ah->ah_radio == AR5K_RF5111) ||
		(ah->ah_radio == AR5K_RF5112))
			obdb = 0;
		अन्यथा
			obdb = 1;

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_ob[ee_mode][obdb],
						AR5K_RF_OB_2GHZ, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_db[ee_mode][obdb],
						AR5K_RF_DB_2GHZ, true);

	/* RF5111 always needs OB/DB क्रम 5GHz, even अगर we use 2GHz */
	पूर्ण अन्यथा अगर ((channel->band == NL80211_BAND_5GHZ) ||
			(ah->ah_radio == AR5K_RF5111)) अणु

		/* For 11a, Turbo and XR we need to choose
		 * OB/DB based on frequency range */
		ee_mode = AR5K_EEPROM_MODE_11A;
		obdb =	 channel->center_freq >= 5725 ? 3 :
			(channel->center_freq >= 5500 ? 2 :
			(channel->center_freq >= 5260 ? 1 :
			 (channel->center_freq > 4000 ? 0 : -1)));

		अगर (obdb < 0)
			वापस -EINVAL;

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_ob[ee_mode][obdb],
						AR5K_RF_OB_5GHZ, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_db[ee_mode][obdb],
						AR5K_RF_DB_5GHZ, true);
	पूर्ण

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	/* Set turbo mode (N/A on RF5413) */
	अगर ((ah->ah_bwmode == AR5K_BWMODE_40MHZ) &&
	(ah->ah_radio != AR5K_RF5413))
		ath5k_hw_rfb_op(ah, rf_regs, 1, AR5K_RF_TURBO, false);

	/* Bank Modअगरications (chip-specअगरic) */
	अगर (ah->ah_radio == AR5K_RF5111) अणु

		/* Set gain_F settings according to current step */
		अगर (channel->hw_value != AR5K_MODE_11B) अणु

			AR5K_REG_WRITE_BITS(ah, AR5K_PHY_FRAME_CTL,
					AR5K_PHY_FRAME_CTL_TX_CLIP,
					g_step->gos_param[0]);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[1],
							AR5K_RF_PWD_90, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[2],
							AR5K_RF_PWD_84, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[3],
						AR5K_RF_RFGAIN_SEL, true);

			/* We programmed gain_F parameters, चयन back
			 * to active state */
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;

		पूर्ण

		/* Bank 6/7 setup */

		ath5k_hw_rfb_op(ah, rf_regs, !ee->ee_xpd[ee_mode],
						AR5K_RF_PWD_XPD, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_x_gain[ee_mode],
						AR5K_RF_XPD_GAIN, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_i_gain[ee_mode],
						AR5K_RF_GAIN_I, true);

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_xpd[ee_mode],
						AR5K_RF_PLO_SEL, true);

		/* Tweak घातer detectors क्रम half/quarter rate support */
		अगर (ah->ah_bwmode == AR5K_BWMODE_5MHZ ||
		ah->ah_bwmode == AR5K_BWMODE_10MHZ) अणु
			u8 रुको_i;

			ath5k_hw_rfb_op(ah, rf_regs, 0x1f,
						AR5K_RF_WAIT_S, true);

			रुको_i = (ah->ah_bwmode == AR5K_BWMODE_5MHZ) ?
							0x1f : 0x10;

			ath5k_hw_rfb_op(ah, rf_regs, रुको_i,
						AR5K_RF_WAIT_I, true);
			ath5k_hw_rfb_op(ah, rf_regs, 3,
						AR5K_RF_MAX_TIME, true);

		पूर्ण
	पूर्ण

	अगर (ah->ah_radio == AR5K_RF5112) अणु

		/* Set gain_F settings according to current step */
		अगर (channel->hw_value != AR5K_MODE_11B) अणु

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[0],
						AR5K_RF_MIXGAIN_OVR, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[1],
						AR5K_RF_PWD_138, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[2],
						AR5K_RF_PWD_137, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[3],
						AR5K_RF_PWD_136, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[4],
						AR5K_RF_PWD_132, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[5],
						AR5K_RF_PWD_131, true);

			ath5k_hw_rfb_op(ah, rf_regs, g_step->gos_param[6],
						AR5K_RF_PWD_130, true);

			/* We programmed gain_F parameters, चयन back
			 * to active state */
			ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		पूर्ण

		/* Bank 6/7 setup */

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_xpd[ee_mode],
						AR5K_RF_XPD_SEL, true);

		अगर (ah->ah_radio_5ghz_revision < AR5K_SREV_RAD_5112A) अणु
			/* Rev. 1 supports only one xpd */
			ath5k_hw_rfb_op(ah, rf_regs,
						ee->ee_x_gain[ee_mode],
						AR5K_RF_XPD_GAIN, true);

		पूर्ण अन्यथा अणु
			u8 *pdg_curve_to_idx = ee->ee_pdc_to_idx[ee_mode];
			अगर (ee->ee_pd_gains[ee_mode] > 1) अणु
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_LO, true);
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[1],
						AR5K_RF_PD_GAIN_HI, true);
			पूर्ण अन्यथा अणु
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_LO, true);
				ath5k_hw_rfb_op(ah, rf_regs,
						pdg_curve_to_idx[0],
						AR5K_RF_PD_GAIN_HI, true);
			पूर्ण

			/* Lower synth voltage on Rev 2 */
			अगर (ah->ah_radio == AR5K_RF5112 &&
			    (ah->ah_radio_5ghz_revision & AR5K_SREV_REV) > 0) अणु
				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_HIGH_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_MID_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_LOW_VC_CP, true);

				ath5k_hw_rfb_op(ah, rf_regs, 2,
						AR5K_RF_PUSH_UP, true);
			पूर्ण

			/* Decrease घातer consumption on 5213+ BaseBand */
			अगर (ah->ah_phy_revision >= AR5K_SREV_PHY_5212A) अणु
				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PAD2GND, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_XB2_LVL, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_XB5_LVL, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PWD_167, true);

				ath5k_hw_rfb_op(ah, rf_regs, 1,
						AR5K_RF_PWD_166, true);
			पूर्ण
		पूर्ण

		ath5k_hw_rfb_op(ah, rf_regs, ee->ee_i_gain[ee_mode],
						AR5K_RF_GAIN_I, true);

		/* Tweak घातer detector क्रम half/quarter rates */
		अगर (ah->ah_bwmode == AR5K_BWMODE_5MHZ ||
		ah->ah_bwmode == AR5K_BWMODE_10MHZ) अणु
			u8 pd_delay;

			pd_delay = (ah->ah_bwmode == AR5K_BWMODE_5MHZ) ?
							0xf : 0x8;

			ath5k_hw_rfb_op(ah, rf_regs, pd_delay,
						AR5K_RF_PD_PERIOD_A, true);
			ath5k_hw_rfb_op(ah, rf_regs, 0xf,
						AR5K_RF_PD_DELAY_A, true);

		पूर्ण
	पूर्ण

	अगर (ah->ah_radio == AR5K_RF5413 &&
	channel->band == NL80211_BAND_2GHZ) अणु

		ath5k_hw_rfb_op(ah, rf_regs, 1, AR5K_RF_DERBY_CHAN_SEL_MODE,
									true);

		/* Set optimum value क्रम early revisions (on pci-e chips) */
		अगर (ah->ah_mac_srev >= AR5K_SREV_AR5424 &&
		ah->ah_mac_srev < AR5K_SREV_AR5413)
			ath5k_hw_rfb_op(ah, rf_regs, ath5k_hw_bitswap(6, 3),
						AR5K_RF_PWD_ICLOBUF_2G, true);

	पूर्ण

	/* Write RF banks on hw */
	क्रम (i = 0; i < ah->ah_rf_banks_size; i++) अणु
		AR5K_REG_WAIT(i);
		ath5k_hw_reg_ग_लिखो(ah, rfb[i], ini_rfb[i].rfb_ctrl_रेजिस्टर);
	पूर्ण

	वापस 0;
पूर्ण


/**************************\
  PHY/RF channel functions
\**************************/

/**
 * ath5k_hw_rf5110_chan2athchan() - Convert channel freq on RF5110
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Map channel frequency to IEEE channel number and convert it
 * to an पूर्णांकernal channel value used by the RF5110 chipset.
 */
अटल u32
ath5k_hw_rf5110_chan2athchan(काष्ठा ieee80211_channel *channel)
अणु
	u32 athchan;

	athchan = (ath5k_hw_bitswap(
			(ieee80211_frequency_to_channel(
				channel->center_freq) - 24) / 2, 5)
				<< 1) | (1 << 6) | 0x1;
	वापस athchan;
पूर्ण

/**
 * ath5k_hw_rf5110_channel() - Set channel frequency on RF5110
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 */
अटल पूर्णांक
ath5k_hw_rf5110_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	u32 data;

	/*
	 * Set the channel and रुको
	 */
	data = ath5k_hw_rf5110_chan2athchan(channel);
	ath5k_hw_reg_ग_लिखो(ah, data, AR5K_RF_BUFFER);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_RF_BUFFER_CONTROL_0);
	usleep_range(1000, 1500);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_rf5111_chan2athchan() - Handle 2GHz channels on RF5111/2111
 * @ieee: IEEE channel number
 * @athchan: The &काष्ठा ath5k_athchan_2ghz
 *
 * In order to enable the RF2111 frequency converter on RF5111/2111 setups
 * we need to add some offsets and extra flags to the data values we pass
 * on to the PHY. So क्रम every 2GHz channel this function माला_लो called
 * to करो the conversion.
 */
अटल पूर्णांक
ath5k_hw_rf5111_chan2athchan(अचिन्हित पूर्णांक ieee,
		काष्ठा ath5k_athchan_2ghz *athchan)
अणु
	पूर्णांक channel;

	/* Cast this value to catch negative channel numbers (>= -19) */
	channel = (पूर्णांक)ieee;

	/*
	 * Map 2GHz IEEE channel to 5GHz Atheros channel
	 */
	अगर (channel <= 13) अणु
		athchan->a2_athchan = 115 + channel;
		athchan->a2_flags = 0x46;
	पूर्ण अन्यथा अगर (channel == 14) अणु
		athchan->a2_athchan = 124;
		athchan->a2_flags = 0x44;
	पूर्ण अन्यथा अगर (channel >= 15 && channel <= 26) अणु
		athchan->a2_athchan = ((channel - 14) * 4) + 132;
		athchan->a2_flags = 0x46;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * ath5k_hw_rf5111_channel() - Set channel frequency on RF5111/2111
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 */
अटल पूर्णांक
ath5k_hw_rf5111_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा ath5k_athchan_2ghz ath5k_channel_2ghz;
	अचिन्हित पूर्णांक ath5k_channel =
		ieee80211_frequency_to_channel(channel->center_freq);
	u32 data0, data1, घड़ी;
	पूर्णांक ret;

	/*
	 * Set the channel on the RF5111 radio
	 */
	data0 = data1 = 0;

	अगर (channel->band == NL80211_BAND_2GHZ) अणु
		/* Map 2GHz channel to 5GHz Atheros channel ID */
		ret = ath5k_hw_rf5111_chan2athchan(
			ieee80211_frequency_to_channel(channel->center_freq),
			&ath5k_channel_2ghz);
		अगर (ret)
			वापस ret;

		ath5k_channel = ath5k_channel_2ghz.a2_athchan;
		data0 = ((ath5k_hw_bitswap(ath5k_channel_2ghz.a2_flags, 8) & 0xff)
		    << 5) | (1 << 4);
	पूर्ण

	अगर (ath5k_channel < 145 || !(ath5k_channel & 1)) अणु
		घड़ी = 1;
		data1 = ((ath5k_hw_bitswap(ath5k_channel - 24, 8) & 0xff) << 2) |
			(घड़ी << 1) | (1 << 10) | 1;
	पूर्ण अन्यथा अणु
		घड़ी = 0;
		data1 = ((ath5k_hw_bitswap((ath5k_channel - 24) / 2, 8) & 0xff)
			<< 2) | (घड़ी << 1) | (1 << 10) | 1;
	पूर्ण

	ath5k_hw_reg_ग_लिखो(ah, (data1 & 0xff) | ((data0 & 0xff) << 8),
			AR5K_RF_BUFFER);
	ath5k_hw_reg_ग_लिखो(ah, ((data1 >> 8) & 0xff) | (data0 & 0xff00),
			AR5K_RF_BUFFER_CONTROL_3);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_rf5112_channel() - Set channel frequency on 5112 and newer
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * On RF5112/2112 and newer we करोn't need to करो any conversion.
 * We pass the frequency value after a few modअगरications to the
 * chip directly.
 *
 * NOTE: Make sure channel frequency given is within our range or अन्यथा
 * we might damage the chip ! Use ath5k_channel_ok beक्रमe calling this one.
 */
अटल पूर्णांक
ath5k_hw_rf5112_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	u32 data, data0, data1, data2;
	u16 c;

	data = data0 = data1 = data2 = 0;
	c = channel->center_freq;

	/* My guess based on code:
	 * 2GHz RF has 2 synth modes, one with a Local Oscillator
	 * at 2224Hz and one with a LO at 2192Hz. IF is 1520Hz
	 * (3040/2). data0 is used to set the PLL भागider and data1
	 * selects synth mode. */
	अगर (c < 4800) अणु
		/* Channel 14 and all frequencies with 2Hz spacing
		 * below/above (non-standard channels) */
		अगर (!((c - 2224) % 5)) अणु
			/* Same as (c - 2224) / 5 */
			data0 = ((2 * (c - 704)) - 3040) / 10;
			data1 = 1;
		/* Channel 1 and all frequencies with 5Hz spacing
		 * below/above (standard channels without channel 14) */
		पूर्ण अन्यथा अगर (!((c - 2192) % 5)) अणु
			/* Same as (c - 2192) / 5 */
			data0 = ((2 * (c - 672)) - 3040) / 10;
			data1 = 0;
		पूर्ण अन्यथा
			वापस -EINVAL;

		data0 = ath5k_hw_bitswap((data0 << 2) & 0xff, 8);
	/* This is more complex, we have a single synthesizer with
	 * 4 reference घड़ी settings (?) based on frequency spacing
	 * and set using data2. LO is at 4800Hz and data0 is again used
	 * to set some भागider.
	 *
	 * NOTE: There is an old atheros presentation at Stanक्रमd
	 * that mentions a method called dual direct conversion
	 * with 1GHz sliding IF क्रम RF5110. Maybe that's what we
	 * have here, or an updated version. */
	पूर्ण अन्यथा अगर ((c % 5) != 2 || c > 5435) अणु
		अगर (!(c % 20) && c >= 5120) अणु
			data0 = ath5k_hw_bitswap(((c - 4800) / 20 << 2), 8);
			data2 = ath5k_hw_bitswap(3, 2);
		पूर्ण अन्यथा अगर (!(c % 10)) अणु
			data0 = ath5k_hw_bitswap(((c - 4800) / 10 << 1), 8);
			data2 = ath5k_hw_bitswap(2, 2);
		पूर्ण अन्यथा अगर (!(c % 5)) अणु
			data0 = ath5k_hw_bitswap((c - 4800) / 5, 8);
			data2 = ath5k_hw_bitswap(1, 2);
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		data0 = ath5k_hw_bitswap((10 * (c - 2 - 4800)) / 25 + 1, 8);
		data2 = ath5k_hw_bitswap(0, 2);
	पूर्ण

	data = (data0 << 4) | (data1 << 1) | (data2 << 2) | 0x1001;

	ath5k_hw_reg_ग_लिखो(ah, data & 0xff, AR5K_RF_BUFFER);
	ath5k_hw_reg_ग_लिखो(ah, (data >> 8) & 0x7f, AR5K_RF_BUFFER_CONTROL_5);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_rf2425_channel() - Set channel frequency on RF2425
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * AR2425/2417 have a dअगरferent 2GHz RF so code changes
 * a little bit from RF5112.
 */
अटल पूर्णांक
ath5k_hw_rf2425_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	u32 data, data0, data2;
	u16 c;

	data = data0 = data2 = 0;
	c = channel->center_freq;

	अगर (c < 4800) अणु
		data0 = ath5k_hw_bitswap((c - 2272), 8);
		data2 = 0;
	/* ? 5GHz ? */
	पूर्ण अन्यथा अगर ((c % 5) != 2 || c > 5435) अणु
		अगर (!(c % 20) && c < 5120)
			data0 = ath5k_hw_bitswap(((c - 4800) / 20 << 2), 8);
		अन्यथा अगर (!(c % 10))
			data0 = ath5k_hw_bitswap(((c - 4800) / 10 << 1), 8);
		अन्यथा अगर (!(c % 5))
			data0 = ath5k_hw_bitswap((c - 4800) / 5, 8);
		अन्यथा
			वापस -EINVAL;
		data2 = ath5k_hw_bitswap(1, 2);
	पूर्ण अन्यथा अणु
		data0 = ath5k_hw_bitswap((10 * (c - 2 - 4800)) / 25 + 1, 8);
		data2 = ath5k_hw_bitswap(0, 2);
	पूर्ण

	data = (data0 << 4) | data2 << 2 | 0x1001;

	ath5k_hw_reg_ग_लिखो(ah, data & 0xff, AR5K_RF_BUFFER);
	ath5k_hw_reg_ग_लिखो(ah, (data >> 8) & 0x7f, AR5K_RF_BUFFER_CONTROL_5);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_channel() - Set a channel on the radio chip
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * This is the मुख्य function called to set a channel on the
 * radio chip based on the radio chip version.
 */
अटल पूर्णांक
ath5k_hw_channel(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	पूर्णांक ret;
	/*
	 * Check bounds supported by the PHY (we करोn't care about regulatory
	 * restrictions at this poपूर्णांक).
	 */
	अगर (!ath5k_channel_ok(ah, channel)) अणु
		ATH5K_ERR(ah,
			"channel frequency (%u MHz) out of supported "
			"band range\n",
			channel->center_freq);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set the channel and रुको
	 */
	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5110:
		ret = ath5k_hw_rf5110_channel(ah, channel);
		अवरोध;
	हाल AR5K_RF5111:
		ret = ath5k_hw_rf5111_channel(ah, channel);
		अवरोध;
	हाल AR5K_RF2317:
	हाल AR5K_RF2425:
		ret = ath5k_hw_rf2425_channel(ah, channel);
		अवरोध;
	शेष:
		ret = ath5k_hw_rf5112_channel(ah, channel);
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Set JAPAN setting क्रम channel 14 */
	अगर (channel->center_freq == 2484) अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_CCKTXCTL,
				AR5K_PHY_CCKTXCTL_JAPAN);
	पूर्ण अन्यथा अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_CCKTXCTL,
				AR5K_PHY_CCKTXCTL_WORLD);
	पूर्ण

	ah->ah_current_channel = channel;

	वापस 0;
पूर्ण


/*****************\
  PHY calibration
\*****************/

/**
 * DOC: PHY Calibration routines
 *
 * Noise न्यूनमान calibration: When we tell the hardware to
 * perक्रमm a noise न्यूनमान calibration by setting the
 * AR5K_PHY_AGCCTL_NF bit on AR5K_PHY_AGCCTL, it will periodically
 * sample-and-hold the minimum noise level seen at the antennas.
 * This value is then stored in a ring buffer of recently measured
 * noise न्यूनमान values so we have a moving winकरोw of the last few
 * samples. The median of the values in the history is then loaded
 * पूर्णांकo the hardware क्रम its own use क्रम RSSI and CCA measurements.
 * This type of calibration करोesn't पूर्णांकerfere with traffic.
 *
 * AGC calibration: When we tell the hardware to perक्रमm
 * an AGC (Automatic Gain Control) calibration by setting the
 * AR5K_PHY_AGCCTL_CAL, hw disconnects the antennas and करोes
 * a calibration on the DC offsets of ADCs. During this period
 * rx/tx माला_लो disabled so we have to deal with it on the driver
 * part.
 *
 * I/Q calibration: When we tell the hardware to perक्रमm
 * an I/Q calibration, it tries to correct I/Q imbalance and
 * fix QAM स्थिरellation by sampling data from rxed frames.
 * It करोesn't पूर्णांकerfere with traffic.
 *
 * For more infos on AGC and I/Q calibration check out patent करोc
 * #03/094463.
 */

/**
 * ath5k_hw_पढ़ो_measured_noise_न्यूनमान() - Read measured NF from hw
 * @ah: The &काष्ठा ath5k_hw
 */
अटल s32
ath5k_hw_पढ़ो_measured_noise_न्यूनमान(काष्ठा ath5k_hw *ah)
अणु
	s32 val;

	val = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_NF);
	वापस sign_extend32(AR5K_REG_MS(val, AR5K_PHY_NF_MINCCA_PWR), 8);
पूर्ण

/**
 * ath5k_hw_init_nfcal_hist() - Initialize NF calibration history buffer
 * @ah: The &काष्ठा ath5k_hw
 */
व्योम
ath5k_hw_init_nfcal_hist(काष्ठा ath5k_hw *ah)
अणु
	पूर्णांक i;

	ah->ah_nfcal_hist.index = 0;
	क्रम (i = 0; i < ATH5K_NF_CAL_HIST_MAX; i++)
		ah->ah_nfcal_hist.nfval[i] = AR5K_TUNE_CCA_MAX_GOOD_VALUE;
पूर्ण

/**
 * ath5k_hw_update_nfcal_hist() - Update NF calibration history buffer
 * @ah: The &काष्ठा ath5k_hw
 * @noise_न्यूनमान: The NF we got from hw
 */
अटल व्योम ath5k_hw_update_nfcal_hist(काष्ठा ath5k_hw *ah, s16 noise_न्यूनमान)
अणु
	काष्ठा ath5k_nfcal_hist *hist = &ah->ah_nfcal_hist;
	hist->index = (hist->index + 1) & (ATH5K_NF_CAL_HIST_MAX - 1);
	hist->nfval[hist->index] = noise_न्यूनमान;
पूर्ण

/**
 * ath5k_hw_get_median_noise_न्यूनमान() - Get median NF from history buffer
 * @ah: The &काष्ठा ath5k_hw
 */
अटल s16
ath5k_hw_get_median_noise_न्यूनमान(काष्ठा ath5k_hw *ah)
अणु
	s16 sort[ATH5K_NF_CAL_HIST_MAX];
	s16 पंचांगp;
	पूर्णांक i, j;

	स_नकल(sort, ah->ah_nfcal_hist.nfval, माप(sort));
	क्रम (i = 0; i < ATH5K_NF_CAL_HIST_MAX - 1; i++) अणु
		क्रम (j = 1; j < ATH5K_NF_CAL_HIST_MAX - i; j++) अणु
			अगर (sort[j] > sort[j - 1]) अणु
				पंचांगp = sort[j];
				sort[j] = sort[j - 1];
				sort[j - 1] = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ATH5K_NF_CAL_HIST_MAX; i++) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"cal %d:%d\n", i, sort[i]);
	पूर्ण
	वापस sort[(ATH5K_NF_CAL_HIST_MAX - 1) / 2];
पूर्ण

/**
 * ath5k_hw_update_noise_न्यूनमान() - Update NF on hardware
 * @ah: The &काष्ठा ath5k_hw
 *
 * This is the मुख्य function we call to perक्रमm a NF calibration,
 * it पढ़ोs NF from hardware, calculates the median and updates
 * NF on hw.
 */
व्योम
ath5k_hw_update_noise_न्यूनमान(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 val;
	s16 nf, threshold;
	u8 ee_mode;

	/* keep last value अगर calibration hasn't completed */
	अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_AGCCTL) & AR5K_PHY_AGCCTL_NF) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"NF did not complete in calibration window\n");

		वापस;
	पूर्ण

	ah->ah_cal_mask |= AR5K_CALIBRATION_NF;

	ee_mode = ath5k_eeprom_mode_from_channel(ah, ah->ah_current_channel);

	/* completed NF calibration, test threshold */
	nf = ath5k_hw_पढ़ो_measured_noise_न्यूनमान(ah);
	threshold = ee->ee_noise_न्यूनमान_thr[ee_mode];

	अगर (nf > threshold) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"noise floor failure detected; "
			"read %d, threshold %d\n",
			nf, threshold);

		nf = AR5K_TUNE_CCA_MAX_GOOD_VALUE;
	पूर्ण

	ath5k_hw_update_nfcal_hist(ah, nf);
	nf = ath5k_hw_get_median_noise_न्यूनमान(ah);

	/* load noise न्यूनमान (in .5 dBm) so the hardware will use it */
	val = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_NF) & ~AR5K_PHY_NF_M;
	val |= (nf * 2) & AR5K_PHY_NF_M;
	ath5k_hw_reg_ग_लिखो(ah, val, AR5K_PHY_NF);

	AR5K_REG_MASKED_BITS(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_NF,
		~(AR5K_PHY_AGCCTL_NF_EN | AR5K_PHY_AGCCTL_NF_NOUPDATE));

	ath5k_hw_रेजिस्टर_समयout(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_NF,
		0, false);

	/*
	 * Load a high max CCA Power value (-50 dBm in .5 dBm units)
	 * so that we're not capped by the median we just loaded.
	 * This will be used as the initial value क्रम the next noise
	 * न्यूनमान calibration.
	 */
	val = (val & ~AR5K_PHY_NF_M) | ((-50 * 2) & AR5K_PHY_NF_M);
	ath5k_hw_reg_ग_लिखो(ah, val, AR5K_PHY_NF);
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
		AR5K_PHY_AGCCTL_NF_EN |
		AR5K_PHY_AGCCTL_NF_NOUPDATE |
		AR5K_PHY_AGCCTL_NF);

	ah->ah_noise_न्यूनमान = nf;

	ah->ah_cal_mask &= ~AR5K_CALIBRATION_NF;

	ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
		"noise floor calibrated: %d\n", nf);
पूर्ण

/**
 * ath5k_hw_rf5110_calibrate() - Perक्रमm a PHY calibration on RF5110
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Do a complete PHY calibration (AGC + NF + I/Q) on RF5110
 */
अटल पूर्णांक
ath5k_hw_rf5110_calibrate(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	u32 phy_sig, phy_agc, phy_sat, beacon;
	पूर्णांक ret;

	अगर (!(ah->ah_cal_mask & AR5K_CALIBRATION_FULL))
		वापस 0;

	/*
	 * Disable beacons and RX/TX queues, रुको
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_DIAG_SW_5210,
		AR5K_DIAG_SW_DIS_TX_5210 | AR5K_DIAG_SW_DIS_RX_5210);
	beacon = ath5k_hw_reg_पढ़ो(ah, AR5K_BEACON_5210);
	ath5k_hw_reg_ग_लिखो(ah, beacon & ~AR5K_BEACON_ENABLE, AR5K_BEACON_5210);

	usleep_range(2000, 2500);

	/*
	 * Set the channel (with AGC turned off)
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);
	udelay(10);
	ret = ath5k_hw_channel(ah, channel);

	/*
	 * Activate PHY and रुको
	 */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ACT_ENABLE, AR5K_PHY_ACT);
	usleep_range(1000, 1500);

	AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);

	अगर (ret)
		वापस ret;

	/*
	 * Calibrate the radio chip
	 */

	/* Remember normal state */
	phy_sig = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_SIG);
	phy_agc = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_AGCCOARSE);
	phy_sat = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_ADCSAT);

	/* Update radio रेजिस्टरs */
	ath5k_hw_reg_ग_लिखो(ah, (phy_sig & ~(AR5K_PHY_SIG_FIRPWR)) |
		AR5K_REG_SM(-1, AR5K_PHY_SIG_FIRPWR), AR5K_PHY_SIG);

	ath5k_hw_reg_ग_लिखो(ah, (phy_agc & ~(AR5K_PHY_AGCCOARSE_HI |
			AR5K_PHY_AGCCOARSE_LO)) |
		AR5K_REG_SM(-1, AR5K_PHY_AGCCOARSE_HI) |
		AR5K_REG_SM(-127, AR5K_PHY_AGCCOARSE_LO), AR5K_PHY_AGCCOARSE);

	ath5k_hw_reg_ग_लिखो(ah, (phy_sat & ~(AR5K_PHY_ADCSAT_ICNT |
			AR5K_PHY_ADCSAT_THR)) |
		AR5K_REG_SM(2, AR5K_PHY_ADCSAT_ICNT) |
		AR5K_REG_SM(12, AR5K_PHY_ADCSAT_THR), AR5K_PHY_ADCSAT);

	udelay(20);

	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);
	udelay(10);
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_RFSTG_DISABLE, AR5K_PHY_RFSTG);
	AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_AGC, AR5K_PHY_AGC_DISABLE);

	usleep_range(1000, 1500);

	/*
	 * Enable calibration and रुको until completion
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_CAL);

	ret = ath5k_hw_रेजिस्टर_समयout(ah, AR5K_PHY_AGCCTL,
			AR5K_PHY_AGCCTL_CAL, 0, false);

	/* Reset to normal state */
	ath5k_hw_reg_ग_लिखो(ah, phy_sig, AR5K_PHY_SIG);
	ath5k_hw_reg_ग_लिखो(ah, phy_agc, AR5K_PHY_AGCCOARSE);
	ath5k_hw_reg_ग_लिखो(ah, phy_sat, AR5K_PHY_ADCSAT);

	अगर (ret) अणु
		ATH5K_ERR(ah, "calibration timeout (%uMHz)\n",
				channel->center_freq);
		वापस ret;
	पूर्ण

	/*
	 * Re-enable RX/TX and beacons
	 */
	AR5K_REG_DISABLE_BITS(ah, AR5K_DIAG_SW_5210,
		AR5K_DIAG_SW_DIS_TX_5210 | AR5K_DIAG_SW_DIS_RX_5210);
	ath5k_hw_reg_ग_लिखो(ah, beacon, AR5K_BEACON_5210);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_rf511x_iq_calibrate() - Perक्रमm I/Q calibration on RF5111 and newer
 * @ah: The &काष्ठा ath5k_hw
 */
अटल पूर्णांक
ath5k_hw_rf511x_iq_calibrate(काष्ठा ath5k_hw *ah)
अणु
	u32 i_pwr, q_pwr;
	s32 iq_corr, i_coff, i_coffd, q_coff, q_coffd;
	पूर्णांक i;

	/* Skip अगर I/Q calibration is not needed or अगर it's still running */
	अगर (!ah->ah_iq_cal_needed)
		वापस -EINVAL;
	अन्यथा अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_IQ) & AR5K_PHY_IQ_RUN) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_CALIBRATE,
				"I/Q calibration still running");
		वापस -EBUSY;
	पूर्ण

	/* Calibration has finished, get the results and re-run */

	/* Work around क्रम empty results which can apparently happen on 5212:
	 * Read रेजिस्टरs up to 10 बार until we get both i_pr and q_pwr */
	क्रम (i = 0; i <= 10; i++) अणु
		iq_corr = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_IQRES_CAL_CORR);
		i_pwr = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_IQRES_CAL_PWR_I);
		q_pwr = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_IQRES_CAL_PWR_Q);
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_CALIBRATE,
			"iq_corr:%x i_pwr:%x q_pwr:%x", iq_corr, i_pwr, q_pwr);
		अगर (i_pwr && q_pwr)
			अवरोध;
	पूर्ण

	i_coffd = ((i_pwr >> 1) + (q_pwr >> 1)) >> 7;

	अगर (ah->ah_version == AR5K_AR5211)
		q_coffd = q_pwr >> 6;
	अन्यथा
		q_coffd = q_pwr >> 7;

	/* In हाल i_coffd became zero, cancel calibration
	 * not only it's too small, it'll also result a भागide
	 * by zero later on. */
	अगर (i_coffd == 0 || q_coffd < 2)
		वापस -ECANCELED;

	/* Protect against loss of sign bits */

	i_coff = (-iq_corr) / i_coffd;
	i_coff = clamp(i_coff, -32, 31); /* चिन्हित 6 bit */

	अगर (ah->ah_version == AR5K_AR5211)
		q_coff = (i_pwr / q_coffd) - 64;
	अन्यथा
		q_coff = (i_pwr / q_coffd) - 128;
	q_coff = clamp(q_coff, -16, 15); /* चिन्हित 5 bit */

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_CALIBRATE,
			"new I:%d Q:%d (i_coffd:%x q_coffd:%x)",
			i_coff, q_coff, i_coffd, q_coffd);

	/* Commit new I/Q values (set enable bit last to match HAL sources) */
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_Q_I_COFF, i_coff);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_Q_Q_COFF, q_coff);
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_CORR_ENABLE);

	/* Re-enable calibration -अगर we करोn't we'll commit
	 * the same values again and again */
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ,
			AR5K_PHY_IQ_CAL_NUM_LOG_MAX, 15);
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ, AR5K_PHY_IQ_RUN);

	वापस 0;
पूर्ण

/**
 * ath5k_hw_phy_calibrate() - Perक्रमm a PHY calibration
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * The मुख्य function we call from above to perक्रमm
 * a लघु or full PHY calibration based on RF chip
 * and current channel
 */
पूर्णांक
ath5k_hw_phy_calibrate(काष्ठा ath5k_hw *ah,
		काष्ठा ieee80211_channel *channel)
अणु
	पूर्णांक ret;

	अगर (ah->ah_radio == AR5K_RF5110)
		वापस ath5k_hw_rf5110_calibrate(ah, channel);

	ret = ath5k_hw_rf511x_iq_calibrate(ah);
	अगर (ret) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_CALIBRATE,
			"No I/Q correction performed (%uMHz)\n",
			channel->center_freq);

		/* Happens all the समय अगर there is not much
		 * traffic, consider it normal behaviour. */
		ret = 0;
	पूर्ण

	/* On full calibration request a PAPD probe क्रम
	 * gainf calibration अगर needed */
	अगर ((ah->ah_cal_mask & AR5K_CALIBRATION_FULL) &&
	    (ah->ah_radio == AR5K_RF5111 ||
	     ah->ah_radio == AR5K_RF5112) &&
	    channel->hw_value != AR5K_MODE_11B)
		ath5k_hw_request_rfgain_probe(ah);

	/* Update noise न्यूनमान */
	अगर (!(ah->ah_cal_mask & AR5K_CALIBRATION_NF))
		ath5k_hw_update_noise_न्यूनमान(ah);

	वापस ret;
पूर्ण


/***************************\
* Spur mitigation functions *
\***************************/

/**
 * ath5k_hw_set_spur_mitigation_filter() - Configure SPUR filter
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * This function माला_लो called during PHY initialization to
 * configure the spur filter क्रम the given channel. Spur is noise
 * generated due to "reflection" effects, क्रम more inक्रमmation on this
 * method check out patent US7643810
 */
अटल व्योम
ath5k_hw_set_spur_mitigation_filter(काष्ठा ath5k_hw *ah,
				काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 mag_mask[4] = अणु0, 0, 0, 0पूर्ण;
	u32 pilot_mask[2] = अणु0, 0पूर्ण;
	/* Note: fbin values are scaled up by 2 */
	u16 spur_chan_fbin, chan_fbin, symbol_width, spur_detection_winकरोw;
	s32 spur_delta_phase, spur_freq_sigma_delta;
	s32 spur_offset, num_symbols_x16;
	u8 num_symbol_offsets, i, freq_band;

	/* Convert current frequency to fbin value (the same way channels
	 * are stored on EEPROM, check out ath5k_eeprom_bin2freq) and scale
	 * up by 2 so we can compare it later */
	अगर (channel->band == NL80211_BAND_2GHZ) अणु
		chan_fbin = (channel->center_freq - 2300) * 10;
		freq_band = AR5K_EEPROM_BAND_2GHZ;
	पूर्ण अन्यथा अणु
		chan_fbin = (channel->center_freq - 4900) * 10;
		freq_band = AR5K_EEPROM_BAND_5GHZ;
	पूर्ण

	/* Check अगर any spur_chan_fbin from EEPROM is
	 * within our current channel's spur detection range */
	spur_chan_fbin = AR5K_EEPROM_NO_SPUR;
	spur_detection_winकरोw = AR5K_SPUR_CHAN_WIDTH;
	/* XXX: Half/Quarter channels ?*/
	अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
		spur_detection_winकरोw *= 2;

	क्रम (i = 0; i < AR5K_EEPROM_N_SPUR_CHANS; i++) अणु
		spur_chan_fbin = ee->ee_spur_chans[i][freq_band];

		/* Note: mask cleans AR5K_EEPROM_NO_SPUR flag
		 * so it's zero अगर we got nothing from EEPROM */
		अगर (spur_chan_fbin == AR5K_EEPROM_NO_SPUR) अणु
			spur_chan_fbin &= AR5K_EEPROM_SPUR_CHAN_MASK;
			अवरोध;
		पूर्ण

		अगर ((chan_fbin - spur_detection_winकरोw <=
		(spur_chan_fbin & AR5K_EEPROM_SPUR_CHAN_MASK)) &&
		(chan_fbin + spur_detection_winकरोw >=
		(spur_chan_fbin & AR5K_EEPROM_SPUR_CHAN_MASK))) अणु
			spur_chan_fbin &= AR5K_EEPROM_SPUR_CHAN_MASK;
			अवरोध;
		पूर्ण
	पूर्ण

	/* We need to enable spur filter क्रम this channel */
	अगर (spur_chan_fbin) अणु
		spur_offset = spur_chan_fbin - chan_fbin;
		/*
		 * Calculate deltas:
		 * spur_freq_sigma_delta -> spur_offset / sample_freq << 21
		 * spur_delta_phase -> spur_offset / chip_freq << 11
		 * Note: Both values have 100Hz resolution
		 */
		चयन (ah->ah_bwmode) अणु
		हाल AR5K_BWMODE_40MHZ:
			/* Both sample_freq and chip_freq are 80MHz */
			spur_delta_phase = (spur_offset << 16) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz * 2;
			अवरोध;
		हाल AR5K_BWMODE_10MHZ:
			/* Both sample_freq and chip_freq are 20MHz (?) */
			spur_delta_phase = (spur_offset << 18) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz / 2;
			अवरोध;
		हाल AR5K_BWMODE_5MHZ:
			/* Both sample_freq and chip_freq are 10MHz (?) */
			spur_delta_phase = (spur_offset << 19) / 25;
			spur_freq_sigma_delta = (spur_delta_phase >> 10);
			symbol_width = AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz / 4;
			अवरोध;
		शेष:
			अगर (channel->band == NL80211_BAND_5GHZ) अणु
				/* Both sample_freq and chip_freq are 40MHz */
				spur_delta_phase = (spur_offset << 17) / 25;
				spur_freq_sigma_delta =
						(spur_delta_phase >> 10);
				symbol_width =
					AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz;
			पूर्ण अन्यथा अणु
				/* sample_freq -> 40MHz chip_freq -> 44MHz
				 * (क्रम b compatibility) */
				spur_delta_phase = (spur_offset << 17) / 25;
				spur_freq_sigma_delta =
						(spur_offset << 8) / 55;
				symbol_width =
					AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Calculate pilot and magnitude masks */

		/* Scale up spur_offset by 1000 to चयन to 100HZ resolution
		 * and भागide by symbol_width to find how many symbols we have
		 * Note: number of symbols is scaled up by 16 */
		num_symbols_x16 = ((spur_offset * 1000) << 4) / symbol_width;

		/* Spur is on a symbol अगर num_symbols_x16 % 16 is zero */
		अगर (!(num_symbols_x16 & 0xF))
			/* _X_ */
			num_symbol_offsets = 3;
		अन्यथा
			/* _xx_ */
			num_symbol_offsets = 4;

		क्रम (i = 0; i < num_symbol_offsets; i++) अणु

			/* Calculate pilot mask */
			s32 curr_sym_off =
				(num_symbols_x16 / 16) + i + 25;

			/* Pilot magnitude mask seems to be a way to
			 * declare the boundaries क्रम our detection
			 * winकरोw or something, it's 2 क्रम the middle
			 * value(s) where the symbol is expected to be
			 * and 1 on the boundary values */
			u8 plt_mag_map =
				(i == 0 || i == (num_symbol_offsets - 1))
								? 1 : 2;

			अगर (curr_sym_off >= 0 && curr_sym_off <= 32) अणु
				अगर (curr_sym_off <= 25)
					pilot_mask[0] |= 1 << curr_sym_off;
				अन्यथा अगर (curr_sym_off >= 27)
					pilot_mask[0] |= 1 << (curr_sym_off - 1);
			पूर्ण अन्यथा अगर (curr_sym_off >= 33 && curr_sym_off <= 52)
				pilot_mask[1] |= 1 << (curr_sym_off - 33);

			/* Calculate magnitude mask (क्रम viterbi decoder) */
			अगर (curr_sym_off >= -1 && curr_sym_off <= 14)
				mag_mask[0] |=
					plt_mag_map << (curr_sym_off + 1) * 2;
			अन्यथा अगर (curr_sym_off >= 15 && curr_sym_off <= 30)
				mag_mask[1] |=
					plt_mag_map << (curr_sym_off - 15) * 2;
			अन्यथा अगर (curr_sym_off >= 31 && curr_sym_off <= 46)
				mag_mask[2] |=
					plt_mag_map << (curr_sym_off - 31) * 2;
			अन्यथा अगर (curr_sym_off >= 47 && curr_sym_off <= 53)
				mag_mask[3] |=
					plt_mag_map << (curr_sym_off - 47) * 2;

		पूर्ण

		/* Write settings on hw to enable spur filter */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_RATE, 0xff);
		/* XXX: Self correlator also ? */
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ,
					AR5K_PHY_IQ_PILOT_MASK_EN |
					AR5K_PHY_IQ_CHAN_MASK_EN |
					AR5K_PHY_IQ_SPUR_FILT_EN);

		/* Set delta phase and freq sigma delta */
		ath5k_hw_reg_ग_लिखो(ah,
				AR5K_REG_SM(spur_delta_phase,
					AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE) |
				AR5K_REG_SM(spur_freq_sigma_delta,
				AR5K_PHY_TIMING_11_SPUR_FREQ_SD) |
				AR5K_PHY_TIMING_11_USE_SPUR_IN_AGC,
				AR5K_PHY_TIMING_11);

		/* Write pilot masks */
		ath5k_hw_reg_ग_लिखो(ah, pilot_mask[0], AR5K_PHY_TIMING_7);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_8,
					AR5K_PHY_TIMING_8_PILOT_MASK_2,
					pilot_mask[1]);

		ath5k_hw_reg_ग_लिखो(ah, pilot_mask[0], AR5K_PHY_TIMING_9);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_10,
					AR5K_PHY_TIMING_10_PILOT_MASK_2,
					pilot_mask[1]);

		/* Write magnitude masks */
		ath5k_hw_reg_ग_लिखो(ah, mag_mask[0], AR5K_PHY_BIN_MASK_1);
		ath5k_hw_reg_ग_लिखो(ah, mag_mask[1], AR5K_PHY_BIN_MASK_2);
		ath5k_hw_reg_ग_लिखो(ah, mag_mask[2], AR5K_PHY_BIN_MASK_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_MASK_4,
					mag_mask[3]);

		ath5k_hw_reg_ग_लिखो(ah, mag_mask[0], AR5K_PHY_BIN_MASK2_1);
		ath5k_hw_reg_ग_लिखो(ah, mag_mask[1], AR5K_PHY_BIN_MASK2_2);
		ath5k_hw_reg_ग_लिखो(ah, mag_mask[2], AR5K_PHY_BIN_MASK2_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK2_4,
					AR5K_PHY_BIN_MASK2_4_MASK_4,
					mag_mask[3]);

	पूर्ण अन्यथा अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_IQ) &
	AR5K_PHY_IQ_SPUR_FILT_EN) अणु
		/* Clean up spur mitigation settings and disable filter */
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_RATE, 0);
		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_IQ,
					AR5K_PHY_IQ_PILOT_MASK_EN |
					AR5K_PHY_IQ_CHAN_MASK_EN |
					AR5K_PHY_IQ_SPUR_FILT_EN);
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_TIMING_11);

		/* Clear pilot masks */
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_TIMING_7);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_8,
					AR5K_PHY_TIMING_8_PILOT_MASK_2,
					0);

		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_TIMING_9);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_TIMING_10,
					AR5K_PHY_TIMING_10_PILOT_MASK_2,
					0);

		/* Clear magnitude masks */
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK_1);
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK_2);
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK_CTL,
					AR5K_PHY_BIN_MASK_CTL_MASK_4,
					0);

		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK2_1);
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK2_2);
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHY_BIN_MASK2_3);
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_BIN_MASK2_4,
					AR5K_PHY_BIN_MASK2_4_MASK_4,
					0);
	पूर्ण
पूर्ण


/*****************\
* Antenna control *
\*****************/

/**
 * DOC: Antenna control
 *
 * Hw supports up to 14 antennas ! I haven't found any card that implements
 * that. The maximum number of antennas I've seen is up to 4 (2 क्रम 2GHz and 2
 * क्रम 5GHz). Antenna 1 (MAIN) should be omnidirectional, 2 (AUX)
 * omnidirectional or sectorial and antennas 3-14 sectorial (or directional).
 *
 * We can have a single antenna क्रम RX and multiple antennas क्रम TX.
 * RX antenna is our "default" antenna (usually antenna 1) set on
 * DEFAULT_ANTENNA रेजिस्टर and TX antenna is set on each TX control descriptor
 * (0 क्रम स्वतःmatic selection, 1 - 14 antenna number).
 *
 * We can let hw करो all the work करोing fast antenna भागersity क्रम both
 * tx and rx or we can करो things manually. Here are the options we have
 * (all are bits of STA_ID1 रेजिस्टर):
 *
 * AR5K_STA_ID1_DEFAULT_ANTENNA -> When 0 is set as the TX antenna on TX
 * control descriptor, use the शेष antenna to transmit or अन्यथा use the last
 * antenna on which we received an ACK.
 *
 * AR5K_STA_ID1_DESC_ANTENNA -> Update शेष antenna after each TX frame to
 * the antenna on which we got the ACK क्रम that frame.
 *
 * AR5K_STA_ID1_RTS_DEF_ANTENNA -> Use शेष antenna क्रम RTS or अन्यथा use the
 * one on the TX descriptor.
 *
 * AR5K_STA_ID1_SELFGEN_DEF_ANT -> Use शेष antenna क्रम self generated frames
 * (ACKs etc), or अन्यथा use current antenna (the one we just used क्रम TX).
 *
 * Using the above we support the following scenarios:
 *
 * AR5K_ANTMODE_DEFAULT -> Hw handles antenna भागersity etc स्वतःmatically
 *
 * AR5K_ANTMODE_FIXED_A	-> Only antenna A (MAIN) is present
 *
 * AR5K_ANTMODE_FIXED_B	-> Only antenna B (AUX) is present
 *
 * AR5K_ANTMODE_SINGLE_AP -> Sta locked on a single ap
 *
 * AR5K_ANTMODE_SECTOR_AP -> AP with tx antenna set on tx desc
 *
 * AR5K_ANTMODE_SECTOR_STA -> STA with tx antenna set on tx desc
 *
 * AR5K_ANTMODE_DEBUG Debug mode -A -> Rx, B-> Tx-
 *
 * Also note that when setting antenna to F on tx descriptor card inverts
 * current tx antenna.
 */

/**
 * ath5k_hw_set_def_antenna() - Set शेष rx antenna on AR5211/5212 and newer
 * @ah: The &काष्ठा ath5k_hw
 * @ant: Antenna number
 */
अटल व्योम
ath5k_hw_set_def_antenna(काष्ठा ath5k_hw *ah, u8 ant)
अणु
	अगर (ah->ah_version != AR5K_AR5210)
		ath5k_hw_reg_ग_लिखो(ah, ant & 0x7, AR5K_DEFAULT_ANTENNA);
पूर्ण

/**
 * ath5k_hw_set_fast_भाग() -  Enable/disable fast rx antenna भागersity
 * @ah: The &काष्ठा ath5k_hw
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 * @enable: True to enable, false to disable
 */
अटल व्योम
ath5k_hw_set_fast_भाग(काष्ठा ath5k_hw *ah, u8 ee_mode, bool enable)
अणु
	चयन (ee_mode) अणु
	हाल AR5K_EEPROM_MODE_11G:
		/* XXX: This is set to
		 * disabled on initvals !!! */
	हाल AR5K_EEPROM_MODE_11A:
		अगर (enable)
			AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_AGCCTL,
					AR5K_PHY_AGCCTL_OFDM_DIV_DIS);
		अन्यथा
			AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
					AR5K_PHY_AGCCTL_OFDM_DIV_DIS);
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
					AR5K_PHY_AGCCTL_OFDM_DIV_DIS);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (enable) अणु
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_RESTART,
				AR5K_PHY_RESTART_DIV_GC, 4);

		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_FAST_ANT_DIV,
					AR5K_PHY_FAST_ANT_DIV_EN);
	पूर्ण अन्यथा अणु
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_RESTART,
				AR5K_PHY_RESTART_DIV_GC, 0);

		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_FAST_ANT_DIV,
					AR5K_PHY_FAST_ANT_DIV_EN);
	पूर्ण
पूर्ण

/**
 * ath5k_hw_set_antenna_चयन() - Set up antenna चयन table
 * @ah: The &काष्ठा ath5k_hw
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 *
 * Switch table comes from EEPROM and includes inक्रमmation on controlling
 * the 2 antenna RX attenuators
 */
व्योम
ath5k_hw_set_antenna_चयन(काष्ठा ath5k_hw *ah, u8 ee_mode)
अणु
	u8 ant0, ant1;

	/*
	 * In हाल a fixed antenna was set as शेष
	 * use the same चयन table twice.
	 */
	अगर (ah->ah_ant_mode == AR5K_ANTMODE_FIXED_A)
		ant0 = ant1 = AR5K_ANT_SWTABLE_A;
	अन्यथा अगर (ah->ah_ant_mode == AR5K_ANTMODE_FIXED_B)
		ant0 = ant1 = AR5K_ANT_SWTABLE_B;
	अन्यथा अणु
		ant0 = AR5K_ANT_SWTABLE_A;
		ant1 = AR5K_ANT_SWTABLE_B;
	पूर्ण

	/* Set antenna idle चयन table */
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_ANT_CTL,
			AR5K_PHY_ANT_CTL_SWTABLE_IDLE,
			(ah->ah_ant_ctl[ee_mode][AR5K_ANT_CTL] |
			AR5K_PHY_ANT_CTL_TXRX_EN));

	/* Set antenna चयन tables */
	ath5k_hw_reg_ग_लिखो(ah, ah->ah_ant_ctl[ee_mode][ant0],
		AR5K_PHY_ANT_SWITCH_TABLE_0);
	ath5k_hw_reg_ग_लिखो(ah, ah->ah_ant_ctl[ee_mode][ant1],
		AR5K_PHY_ANT_SWITCH_TABLE_1);
पूर्ण

/**
 * ath5k_hw_set_antenna_mode() -  Set antenna operating mode
 * @ah: The &काष्ठा ath5k_hw
 * @ant_mode: One of क्रमागत ath5k_ant_mode
 */
व्योम
ath5k_hw_set_antenna_mode(काष्ठा ath5k_hw *ah, u8 ant_mode)
अणु
	काष्ठा ieee80211_channel *channel = ah->ah_current_channel;
	bool use_def_क्रम_tx, update_def_on_tx, use_def_क्रम_rts, fast_भाग;
	bool use_def_क्रम_sg;
	पूर्णांक ee_mode;
	u8 def_ant, tx_ant;
	u32 sta_id1 = 0;

	/* अगर channel is not initialized yet we can't set the antennas
	 * so just store the mode. it will be set on the next reset */
	अगर (channel == शून्य) अणु
		ah->ah_ant_mode = ant_mode;
		वापस;
	पूर्ण

	def_ant = ah->ah_def_ant;

	ee_mode = ath5k_eeprom_mode_from_channel(ah, channel);

	चयन (ant_mode) अणु
	हाल AR5K_ANTMODE_DEFAULT:
		tx_ant = 0;
		use_def_क्रम_tx = false;
		update_def_on_tx = false;
		use_def_क्रम_rts = false;
		use_def_क्रम_sg = false;
		fast_भाग = true;
		अवरोध;
	हाल AR5K_ANTMODE_FIXED_A:
		def_ant = 1;
		tx_ant = 1;
		use_def_क्रम_tx = true;
		update_def_on_tx = false;
		use_def_क्रम_rts = true;
		use_def_क्रम_sg = true;
		fast_भाग = false;
		अवरोध;
	हाल AR5K_ANTMODE_FIXED_B:
		def_ant = 2;
		tx_ant = 2;
		use_def_क्रम_tx = true;
		update_def_on_tx = false;
		use_def_क्रम_rts = true;
		use_def_क्रम_sg = true;
		fast_भाग = false;
		अवरोध;
	हाल AR5K_ANTMODE_SINGLE_AP:
		def_ant = 1;	/* updated on tx */
		tx_ant = 0;
		use_def_क्रम_tx = true;
		update_def_on_tx = true;
		use_def_क्रम_rts = true;
		use_def_क्रम_sg = true;
		fast_भाग = true;
		अवरोध;
	हाल AR5K_ANTMODE_SECTOR_AP:
		tx_ant = 1;	/* variable */
		use_def_क्रम_tx = false;
		update_def_on_tx = false;
		use_def_क्रम_rts = true;
		use_def_क्रम_sg = false;
		fast_भाग = false;
		अवरोध;
	हाल AR5K_ANTMODE_SECTOR_STA:
		tx_ant = 1;	/* variable */
		use_def_क्रम_tx = true;
		update_def_on_tx = false;
		use_def_क्रम_rts = true;
		use_def_क्रम_sg = false;
		fast_भाग = true;
		अवरोध;
	हाल AR5K_ANTMODE_DEBUG:
		def_ant = 1;
		tx_ant = 2;
		use_def_क्रम_tx = false;
		update_def_on_tx = false;
		use_def_क्रम_rts = false;
		use_def_क्रम_sg = false;
		fast_भाग = false;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ah->ah_tx_ant = tx_ant;
	ah->ah_ant_mode = ant_mode;
	ah->ah_def_ant = def_ant;

	sta_id1 |= use_def_क्रम_tx ? AR5K_STA_ID1_DEFAULT_ANTENNA : 0;
	sta_id1 |= update_def_on_tx ? AR5K_STA_ID1_DESC_ANTENNA : 0;
	sta_id1 |= use_def_क्रम_rts ? AR5K_STA_ID1_RTS_DEF_ANTENNA : 0;
	sta_id1 |= use_def_क्रम_sg ? AR5K_STA_ID1_SELFGEN_DEF_ANT : 0;

	AR5K_REG_DISABLE_BITS(ah, AR5K_STA_ID1, AR5K_STA_ID1_ANTENNA_SETTINGS);

	अगर (sta_id1)
		AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1, sta_id1);

	ath5k_hw_set_antenna_चयन(ah, ee_mode);
	/* Note: set भागersity beक्रमe शेष antenna
	 * because it won't work correctly */
	ath5k_hw_set_fast_भाग(ah, ee_mode, fast_भाग);
	ath5k_hw_set_def_antenna(ah, def_ant);
पूर्ण


/****************\
* TX घातer setup *
\****************/

/*
 * Helper functions
 */

/**
 * ath5k_get_पूर्णांकerpolated_value() - Get पूर्णांकerpolated Y val between two poपूर्णांकs
 * @target: X value of the middle poपूर्णांक
 * @x_left: X value of the left poपूर्णांक
 * @x_right: X value of the right poपूर्णांक
 * @y_left: Y value of the left poपूर्णांक
 * @y_right: Y value of the right poपूर्णांक
 */
अटल s16
ath5k_get_पूर्णांकerpolated_value(s16 target, s16 x_left, s16 x_right,
					s16 y_left, s16 y_right)
अणु
	s16 ratio, result;

	/* Aव्योम भागide by zero and skip पूर्णांकerpolation
	 * अगर we have the same poपूर्णांक */
	अगर ((x_left == x_right) || (y_left == y_right))
		वापस y_left;

	/*
	 * Since we use पूर्णांकs and not fps, we need to scale up in
	 * order to get a sane ratio value (or अन्यथा we 'll eg. get
	 * always 1 instead of 1.25, 1.75 etc). We scale up by 100
	 * to have some accuracy both क्रम 0.5 and 0.25 steps.
	 */
	ratio = ((100 * y_right - 100 * y_left) / (x_right - x_left));

	/* Now scale करोwn to be in range */
	result = y_left + (ratio * (target - x_left) / 100);

	वापस result;
पूर्ण

/**
 * ath5k_get_linear_pcdac_min() - Find vertical boundary (min pwr) क्रम the
 * linear PCDAC curve
 * @stepL: Left array with y values (pcdac steps)
 * @stepR: Right array with y values (pcdac steps)
 * @pwrL: Left array with x values (घातer steps)
 * @pwrR: Right array with x values (घातer steps)
 *
 * Since we have the top of the curve and we draw the line below
 * until we reach 1 (1 pcdac step) we need to know which poपूर्णांक
 * (x value) that is so that we करोn't go below x axis and have negative
 * pcdac values when creating the curve, or fill the table with zeros.
 */
अटल s16
ath5k_get_linear_pcdac_min(स्थिर u8 *stepL, स्थिर u8 *stepR,
				स्थिर s16 *pwrL, स्थिर s16 *pwrR)
अणु
	s8 पंचांगp;
	s16 min_pwrL, min_pwrR;
	s16 pwr_i;

	/* Some venकरोrs ग_लिखो the same pcdac value twice !!! */
	अगर (stepL[0] == stepL[1] || stepR[0] == stepR[1])
		वापस max(pwrL[0], pwrR[0]);

	अगर (pwrL[0] == pwrL[1])
		min_pwrL = pwrL[0];
	अन्यथा अणु
		pwr_i = pwrL[0];
		करो अणु
			pwr_i--;
			पंचांगp = (s8) ath5k_get_पूर्णांकerpolated_value(pwr_i,
							pwrL[0], pwrL[1],
							stepL[0], stepL[1]);
		पूर्ण जबतक (पंचांगp > 1);

		min_pwrL = pwr_i;
	पूर्ण

	अगर (pwrR[0] == pwrR[1])
		min_pwrR = pwrR[0];
	अन्यथा अणु
		pwr_i = pwrR[0];
		करो अणु
			pwr_i--;
			पंचांगp = (s8) ath5k_get_पूर्णांकerpolated_value(pwr_i,
							pwrR[0], pwrR[1],
							stepR[0], stepR[1]);
		पूर्ण जबतक (पंचांगp > 1);

		min_pwrR = pwr_i;
	पूर्ण

	/* Keep the right boundary so that it works क्रम both curves */
	वापस max(min_pwrL, min_pwrR);
पूर्ण

/**
 * ath5k_create_घातer_curve() - Create a Power to PDADC or PCDAC curve
 * @pmin: Minimum घातer value (xmin)
 * @pmax: Maximum घातer value (xmax)
 * @pwr: Array of घातer steps (x values)
 * @vpd: Array of matching PCDAC/PDADC steps (y values)
 * @num_poपूर्णांकs: Number of provided poपूर्णांकs
 * @vpd_table: Array to fill with the full PCDAC/PDADC values (y values)
 * @type: One of क्रमागत ath5k_घातertable_type (eeprom.h)
 *
 * Interpolate (pwr,vpd) poपूर्णांकs to create a Power to PDADC or a
 * Power to PCDAC curve.
 *
 * Each curve has घातer on x axis (in 0.5dB units) and PCDAC/PDADC
 * steps (offsets) on y axis. Power can go up to 31.5dB and max
 * PCDAC/PDADC step क्रम each curve is 64 but we can ग_लिखो more than
 * one curves on hw so we can go up to 128 (which is the max step we
 * can ग_लिखो on the final table).
 *
 * We ग_लिखो y values (PCDAC/PDADC steps) on hw.
 */
अटल व्योम
ath5k_create_घातer_curve(s16 pmin, s16 pmax,
			स्थिर s16 *pwr, स्थिर u8 *vpd,
			u8 num_poपूर्णांकs,
			u8 *vpd_table, u8 type)
अणु
	u8 idx[2] = अणु 0, 1 पूर्ण;
	s16 pwr_i = 2 * pmin;
	पूर्णांक i;

	अगर (num_poपूर्णांकs < 2)
		वापस;

	/* We want the whole line, so adjust boundaries
	 * to cover the entire घातer range. Note that
	 * घातer values are alपढ़ोy 0.25dB so no need
	 * to multiply pwr_i by 2 */
	अगर (type == AR5K_PWRTABLE_LINEAR_PCDAC) अणु
		pwr_i = pmin;
		pmin = 0;
		pmax = 63;
	पूर्ण

	/* Find surrounding turning poपूर्णांकs (TPs)
	 * and पूर्णांकerpolate between them */
	क्रम (i = 0; (i <= (u16) (pmax - pmin)) &&
	(i < AR5K_EEPROM_POWER_TABLE_SIZE); i++) अणु

		/* We passed the right TP, move to the next set of TPs
		 * अगर we pass the last TP, extrapolate above using the last
		 * two TPs क्रम ratio */
		अगर ((pwr_i > pwr[idx[1]]) && (idx[1] < num_poपूर्णांकs - 1)) अणु
			idx[0]++;
			idx[1]++;
		पूर्ण

		vpd_table[i] = (u8) ath5k_get_पूर्णांकerpolated_value(pwr_i,
						pwr[idx[0]], pwr[idx[1]],
						vpd[idx[0]], vpd[idx[1]]);

		/* Increase by 0.5dB
		 * (0.25 dB units) */
		pwr_i += 2;
	पूर्ण
पूर्ण

/**
 * ath5k_get_chan_pcal_surrounding_piers() - Get surrounding calibration piers
 * क्रम a given channel.
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 * @pcinfo_l: The &काष्ठा ath5k_chan_pcal_info to put the left cal. pier
 * @pcinfo_r: The &काष्ठा ath5k_chan_pcal_info to put the right cal. pier
 *
 * Get the surrounding per-channel घातer calibration piers
 * क्रम a given frequency so that we can पूर्णांकerpolate between
 * them and come up with an appropriate dataset क्रम our current
 * channel.
 */
अटल व्योम
ath5k_get_chan_pcal_surrounding_piers(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel,
			काष्ठा ath5k_chan_pcal_info **pcinfo_l,
			काष्ठा ath5k_chan_pcal_info **pcinfo_r)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_chan_pcal_info *pcinfo;
	u8 idx_l, idx_r;
	u8 mode, max, i;
	u32 target = channel->center_freq;

	idx_l = 0;
	idx_r = 0;

	चयन (channel->hw_value) अणु
	हाल AR5K_EEPROM_MODE_11A:
		pcinfo = ee->ee_pwr_cal_a;
		mode = AR5K_EEPROM_MODE_11A;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11B:
		pcinfo = ee->ee_pwr_cal_b;
		mode = AR5K_EEPROM_MODE_11B;
		अवरोध;
	हाल AR5K_EEPROM_MODE_11G:
	शेष:
		pcinfo = ee->ee_pwr_cal_g;
		mode = AR5K_EEPROM_MODE_11G;
		अवरोध;
	पूर्ण
	max = ee->ee_n_piers[mode] - 1;

	/* Frequency is below our calibrated
	 * range. Use the lowest घातer curve
	 * we have */
	अगर (target < pcinfo[0].freq) अणु
		idx_l = idx_r = 0;
		जाओ करोne;
	पूर्ण

	/* Frequency is above our calibrated
	 * range. Use the highest घातer curve
	 * we have */
	अगर (target > pcinfo[max].freq) अणु
		idx_l = idx_r = max;
		जाओ करोne;
	पूर्ण

	/* Frequency is inside our calibrated
	 * channel range. Pick the surrounding
	 * calibration piers so that we can
	 * पूर्णांकerpolate */
	क्रम (i = 0; i <= max; i++) अणु

		/* Frequency matches one of our calibration
		 * piers, no need to पूर्णांकerpolate, just use
		 * that calibration pier */
		अगर (pcinfo[i].freq == target) अणु
			idx_l = idx_r = i;
			जाओ करोne;
		पूर्ण

		/* We found a calibration pier that's above
		 * frequency, use this pier and the previous
		 * one to पूर्णांकerpolate */
		अगर (target < pcinfo[i].freq) अणु
			idx_r = i;
			idx_l = idx_r - 1;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	*pcinfo_l = &pcinfo[idx_l];
	*pcinfo_r = &pcinfo[idx_r];
पूर्ण

/**
 * ath5k_get_rate_pcal_data() - Get the पूर्णांकerpolated per-rate घातer
 * calibration data
 * @ah: The &काष्ठा ath5k_hw *ah,
 * @channel: The &काष्ठा ieee80211_channel
 * @rates: The &काष्ठा ath5k_rate_pcal_info to fill
 *
 * Get the surrounding per-rate घातer calibration data
 * क्रम a given frequency and पूर्णांकerpolate between घातer
 * values to set max target घातer supported by hw क्रम
 * each rate on this frequency.
 */
अटल व्योम
ath5k_get_rate_pcal_data(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel,
			काष्ठा ath5k_rate_pcal_info *rates)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_rate_pcal_info *rpinfo;
	u8 idx_l, idx_r;
	u8 mode, max, i;
	u32 target = channel->center_freq;

	idx_l = 0;
	idx_r = 0;

	चयन (channel->hw_value) अणु
	हाल AR5K_MODE_11A:
		rpinfo = ee->ee_rate_tpwr_a;
		mode = AR5K_EEPROM_MODE_11A;
		अवरोध;
	हाल AR5K_MODE_11B:
		rpinfo = ee->ee_rate_tpwr_b;
		mode = AR5K_EEPROM_MODE_11B;
		अवरोध;
	हाल AR5K_MODE_11G:
	शेष:
		rpinfo = ee->ee_rate_tpwr_g;
		mode = AR5K_EEPROM_MODE_11G;
		अवरोध;
	पूर्ण
	max = ee->ee_rate_target_pwr_num[mode] - 1;

	/* Get the surrounding calibration
	 * piers - same as above */
	अगर (target < rpinfo[0].freq) अणु
		idx_l = idx_r = 0;
		जाओ करोne;
	पूर्ण

	अगर (target > rpinfo[max].freq) अणु
		idx_l = idx_r = max;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i <= max; i++) अणु

		अगर (rpinfo[i].freq == target) अणु
			idx_l = idx_r = i;
			जाओ करोne;
		पूर्ण

		अगर (target < rpinfo[i].freq) अणु
			idx_r = i;
			idx_l = idx_r - 1;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	/* Now पूर्णांकerpolate घातer value, based on the frequency */
	rates->freq = target;

	rates->target_घातer_6to24 =
		ath5k_get_पूर्णांकerpolated_value(target, rpinfo[idx_l].freq,
					rpinfo[idx_r].freq,
					rpinfo[idx_l].target_घातer_6to24,
					rpinfo[idx_r].target_घातer_6to24);

	rates->target_घातer_36 =
		ath5k_get_पूर्णांकerpolated_value(target, rpinfo[idx_l].freq,
					rpinfo[idx_r].freq,
					rpinfo[idx_l].target_घातer_36,
					rpinfo[idx_r].target_घातer_36);

	rates->target_घातer_48 =
		ath5k_get_पूर्णांकerpolated_value(target, rpinfo[idx_l].freq,
					rpinfo[idx_r].freq,
					rpinfo[idx_l].target_घातer_48,
					rpinfo[idx_r].target_घातer_48);

	rates->target_घातer_54 =
		ath5k_get_पूर्णांकerpolated_value(target, rpinfo[idx_l].freq,
					rpinfo[idx_r].freq,
					rpinfo[idx_l].target_घातer_54,
					rpinfo[idx_r].target_घातer_54);
पूर्ण

/**
 * ath5k_get_max_ctl_घातer() - Get max edge घातer क्रम a given frequency
 * @ah: the &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 *
 * Get the max edge घातer क्रम this channel अगर
 * we have such data from EEPROM's Conक्रमmance Test
 * Limits (CTL), and limit max घातer अगर needed.
 */
अटल व्योम
ath5k_get_max_ctl_घातer(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा ath_regulatory *regulatory = ath5k_hw_regulatory(ah);
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	काष्ठा ath5k_edge_घातer *rep = ee->ee_ctl_pwr;
	u8 *ctl_val = ee->ee_ctl;
	s16 max_chan_pwr = ah->ah_txघातer.txp_max_pwr / 4;
	s16 edge_pwr = 0;
	u8 rep_idx;
	u8 i, ctl_mode;
	u8 ctl_idx = 0xFF;
	u32 target = channel->center_freq;

	ctl_mode = ath_regd_get_band_ctl(regulatory, channel->band);

	चयन (channel->hw_value) अणु
	हाल AR5K_MODE_11A:
		अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
			ctl_mode |= AR5K_CTL_TURBO;
		अन्यथा
			ctl_mode |= AR5K_CTL_11A;
		अवरोध;
	हाल AR5K_MODE_11G:
		अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
			ctl_mode |= AR5K_CTL_TURBOG;
		अन्यथा
			ctl_mode |= AR5K_CTL_11G;
		अवरोध;
	हाल AR5K_MODE_11B:
		ctl_mode |= AR5K_CTL_11B;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < ee->ee_ctls; i++) अणु
		अगर (ctl_val[i] == ctl_mode) अणु
			ctl_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If we have a CTL dataset available grab it and find the
	 * edge घातer क्रम our frequency */
	अगर (ctl_idx == 0xFF)
		वापस;

	/* Edge घातers are sorted by frequency from lower
	 * to higher. Each CTL corresponds to 8 edge घातer
	 * measurements. */
	rep_idx = ctl_idx * AR5K_EEPROM_N_EDGES;

	/* Don't करो boundaries check because we
	 * might have more that one bands defined
	 * क्रम this mode */

	/* Get the edge घातer that's बंदr to our
	 * frequency */
	क्रम (i = 0; i < AR5K_EEPROM_N_EDGES; i++) अणु
		rep_idx += i;
		अगर (target <= rep[rep_idx].freq)
			edge_pwr = (s16) rep[rep_idx].edge;
	पूर्ण

	अगर (edge_pwr)
		ah->ah_txघातer.txp_max_pwr = 4 * min(edge_pwr, max_chan_pwr);
पूर्ण


/*
 * Power to PCDAC table functions
 */

/**
 * DOC: Power to PCDAC table functions
 *
 * For RF5111 we have an XPD -eXternal Power Detector- curve
 * क्रम each calibrated channel. Each curve has 0,5dB Power steps
 * on x axis and PCDAC steps (offsets) on y axis and looks like an
 * exponential function. To recreate the curve we पढ़ो 11 poपूर्णांकs
 * from eeprom (eeprom.c) and पूर्णांकerpolate here.
 *
 * For RF5112 we have 4 XPD -eXternal Power Detector- curves
 * क्रम each calibrated channel on 0, -6, -12 and -18dBm but we only
 * use the higher (3) and the lower (0) curves. Each curve again has 0.5dB
 * घातer steps on x axis and PCDAC steps on y axis and looks like a
 * linear function. To recreate the curve and pass the घातer values
 * on hw, we get 4 poपूर्णांकs क्रम xpd 0 (lower gain -> max घातer)
 * and 3 poपूर्णांकs क्रम xpd 3 (higher gain -> lower घातer) from eeprom (eeprom.c)
 * and पूर्णांकerpolate here.
 *
 * For a given channel we get the calibrated poपूर्णांकs (piers) क्रम it or
 * -अगर we करोn't have calibration data क्रम this specअगरic channel- from the
 * available surrounding channels we have calibration data क्रम, after we करो a
 * linear पूर्णांकerpolation between them. Then since we have our calibrated poपूर्णांकs
 * क्रम this channel, we करो again a linear पूर्णांकerpolation between them to get the
 * whole curve.
 *
 * We finally ग_लिखो the Y values of the curve(s) (the PCDAC values) on hw
 */

/**
 * ath5k_fill_pwr_to_pcdac_table() - Fill Power to PCDAC table on RF5111
 * @ah: The &काष्ठा ath5k_hw
 * @table_min: Minimum घातer (x min)
 * @table_max: Maximum घातer (x max)
 *
 * No further processing is needed क्रम RF5111, the only thing we have to
 * करो is fill the values below and above calibration range since eeprom data
 * may not cover the entire PCDAC table.
 */
अटल व्योम
ath5k_fill_pwr_to_pcdac_table(काष्ठा ath5k_hw *ah, s16* table_min,
							s16 *table_max)
अणु
	u8	*pcdac_out = ah->ah_txघातer.txp_pd_table;
	u8	*pcdac_पंचांगp = ah->ah_txघातer.पंचांगpL[0];
	u8	pcdac_0, pcdac_n, pcdac_i, pwr_idx, i;
	s16	min_pwr, max_pwr;

	/* Get table boundaries */
	min_pwr = table_min[0];
	pcdac_0 = pcdac_पंचांगp[0];

	max_pwr = table_max[0];
	pcdac_n = pcdac_पंचांगp[table_max[0] - table_min[0]];

	/* Extrapolate below minimum using pcdac_0 */
	pcdac_i = 0;
	क्रम (i = 0; i < min_pwr; i++)
		pcdac_out[pcdac_i++] = pcdac_0;

	/* Copy values from pcdac_पंचांगp */
	pwr_idx = min_pwr;
	क्रम (i = 0; pwr_idx <= max_pwr &&
		    pcdac_i < AR5K_EEPROM_POWER_TABLE_SIZE; i++) अणु
		pcdac_out[pcdac_i++] = pcdac_पंचांगp[i];
		pwr_idx++;
	पूर्ण

	/* Extrapolate above maximum */
	जबतक (pcdac_i < AR5K_EEPROM_POWER_TABLE_SIZE)
		pcdac_out[pcdac_i++] = pcdac_n;

पूर्ण

/**
 * ath5k_combine_linear_pcdac_curves() - Combine available PCDAC Curves
 * @ah: The &काष्ठा ath5k_hw
 * @table_min: Minimum घातer (x min)
 * @table_max: Maximum घातer (x max)
 * @pdcurves: Number of pd curves
 *
 * Combine available XPD Curves and fill Linear Power to PCDAC table on RF5112
 * RFX112 can have up to 2 curves (one क्रम low txघातer range and one क्रम
 * higher txघातer range). We need to put them both on pcdac_out and place
 * them in the correct location. In हाल we only have one curve available
 * just fit it on pcdac_out (it's supposed to cover the entire range of
 * available pwr levels since it's always the higher घातer curve). Extrapolate
 * below and above final table अगर needed.
 */
अटल व्योम
ath5k_combine_linear_pcdac_curves(काष्ठा ath5k_hw *ah, s16* table_min,
						s16 *table_max, u8 pdcurves)
अणु
	u8	*pcdac_out = ah->ah_txघातer.txp_pd_table;
	u8	*pcdac_low_pwr;
	u8	*pcdac_high_pwr;
	u8	*pcdac_पंचांगp;
	u8	pwr;
	s16	max_pwr_idx;
	s16	min_pwr_idx;
	s16	mid_pwr_idx = 0;
	/* Edge flag turns on the 7nth bit on the PCDAC
	 * to declare the higher घातer curve (क्रमce values
	 * to be greater than 64). If we only have one curve
	 * we करोn't need to set this, अगर we have 2 curves and
	 * fill the table backwards this can also be used to
	 * चयन from higher घातer curve to lower घातer curve */
	u8	edge_flag;
	पूर्णांक	i;

	/* When we have only one curve available
	 * that's the higher घातer curve. If we have
	 * two curves the first is the high घातer curve
	 * and the next is the low घातer curve. */
	अगर (pdcurves > 1) अणु
		pcdac_low_pwr = ah->ah_txघातer.पंचांगpL[1];
		pcdac_high_pwr = ah->ah_txघातer.पंचांगpL[0];
		mid_pwr_idx = table_max[1] - table_min[1] - 1;
		max_pwr_idx = (table_max[0] - table_min[0]) / 2;

		/* If table size goes beyond 31.5dB, keep the
		 * upper 31.5dB range when setting tx घातer.
		 * Note: 126 = 31.5 dB in quarter dB steps */
		अगर (table_max[0] - table_min[1] > 126)
			min_pwr_idx = table_max[0] - 126;
		अन्यथा
			min_pwr_idx = table_min[1];

		/* Since we fill table backwards
		 * start from high घातer curve */
		pcdac_पंचांगp = pcdac_high_pwr;

		edge_flag = 0x40;
	पूर्ण अन्यथा अणु
		pcdac_low_pwr = ah->ah_txघातer.पंचांगpL[1]; /* Zeroed */
		pcdac_high_pwr = ah->ah_txघातer.पंचांगpL[0];
		min_pwr_idx = table_min[0];
		max_pwr_idx = (table_max[0] - table_min[0]) / 2;
		pcdac_पंचांगp = pcdac_high_pwr;
		edge_flag = 0;
	पूर्ण

	/* This is used when setting tx घातer*/
	ah->ah_txघातer.txp_min_idx = min_pwr_idx / 2;

	/* Fill Power to PCDAC table backwards */
	pwr = max_pwr_idx;
	क्रम (i = 63; i >= 0; i--) अणु
		/* Entering lower घातer range, reset
		 * edge flag and set pcdac_पंचांगp to lower
		 * घातer curve.*/
		अगर (edge_flag == 0x40 &&
		(2 * pwr <= (table_max[1] - table_min[0]) || pwr == 0)) अणु
			edge_flag = 0x00;
			pcdac_पंचांगp = pcdac_low_pwr;
			pwr = mid_pwr_idx / 2;
		पूर्ण

		/* Don't go below 1, extrapolate below अगर we have
		 * alपढ़ोy चयनed to the lower घातer curve -or
		 * we only have one curve and edge_flag is zero
		 * anyway */
		अगर (pcdac_पंचांगp[pwr] < 1 && (edge_flag == 0x00)) अणु
			जबतक (i >= 0) अणु
				pcdac_out[i] = pcdac_out[i + 1];
				i--;
			पूर्ण
			अवरोध;
		पूर्ण

		pcdac_out[i] = pcdac_पंचांगp[pwr] | edge_flag;

		/* Extrapolate above अगर pcdac is greater than
		 * 126 -this can happen because we OR pcdac_out
		 * value with edge_flag on high घातer curve */
		अगर (pcdac_out[i] > 126)
			pcdac_out[i] = 126;

		/* Decrease by a 0.5dB step */
		pwr--;
	पूर्ण
पूर्ण

/**
 * ath5k_ग_लिखो_pcdac_table() - Write the PCDAC values on hw
 * @ah: The &काष्ठा ath5k_hw
 */
अटल व्योम
ath5k_ग_लिखो_pcdac_table(काष्ठा ath5k_hw *ah)
अणु
	u8	*pcdac_out = ah->ah_txघातer.txp_pd_table;
	पूर्णांक	i;

	/*
	 * Write TX घातer values
	 */
	क्रम (i = 0; i < (AR5K_EEPROM_POWER_TABLE_SIZE / 2); i++) अणु
		ath5k_hw_reg_ग_लिखो(ah,
			(((pcdac_out[2 * i + 0] << 8 | 0xff) & 0xffff) << 0) |
			(((pcdac_out[2 * i + 1] << 8 | 0xff) & 0xffff) << 16),
			AR5K_PHY_PCDAC_TXPOWER(i));
	पूर्ण
पूर्ण


/*
 * Power to PDADC table functions
 */

/**
 * DOC: Power to PDADC table functions
 *
 * For RF2413 and later we have a Power to PDADC table (Power Detector)
 * instead of a PCDAC (Power Control) and 4 pd gain curves क्रम each
 * calibrated channel. Each curve has घातer on x axis in 0.5 db steps and
 * PDADC steps on y axis and looks like an exponential function like the
 * RF5111 curve.
 *
 * To recreate the curves we पढ़ो the poपूर्णांकs from eeprom (eeprom.c)
 * and पूर्णांकerpolate here. Note that in most हालs only 2 (higher and lower)
 * curves are used (like RF5112) but venकरोrs have the opportunity to include
 * all 4 curves on eeprom. The final curve (higher घातer) has an extra
 * poपूर्णांक क्रम better accuracy like RF5112.
 *
 * The process is similar to what we करो above क्रम RF5111/5112
 */

/**
 * ath5k_combine_pwr_to_pdadc_curves() - Combine the various PDADC curves
 * @ah: The &काष्ठा ath5k_hw
 * @pwr_min: Minimum घातer (x min)
 * @pwr_max: Maximum घातer (x max)
 * @pdcurves: Number of available curves
 *
 * Combine the various pd curves and create the final Power to PDADC table
 * We can have up to 4 pd curves, we need to करो a similar process
 * as we करो क्रम RF5112. This समय we करोn't have an edge_flag but we
 * set the gain boundaries on a separate रेजिस्टर.
 */
अटल व्योम
ath5k_combine_pwr_to_pdadc_curves(काष्ठा ath5k_hw *ah,
			s16 *pwr_min, s16 *pwr_max, u8 pdcurves)
अणु
	u8 gain_boundaries[AR5K_EEPROM_N_PD_GAINS];
	u8 *pdadc_out = ah->ah_txघातer.txp_pd_table;
	u8 *pdadc_पंचांगp;
	s16 pdadc_0;
	u8 pdadc_i, pdadc_n, pwr_step, pdg, max_idx, table_size;
	u8 pd_gain_overlap;

	/* Note: Register value is initialized on initvals
	 * there is no feedback from hw.
	 * XXX: What about pd_gain_overlap from EEPROM ? */
	pd_gain_overlap = (u8) ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_TPC_RG5) &
		AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP;

	/* Create final PDADC table */
	क्रम (pdg = 0, pdadc_i = 0; pdg < pdcurves; pdg++) अणु
		pdadc_पंचांगp = ah->ah_txघातer.पंचांगpL[pdg];

		अगर (pdg == pdcurves - 1)
			/* 2 dB boundary stretch क्रम last
			 * (higher घातer) curve */
			gain_boundaries[pdg] = pwr_max[pdg] + 4;
		अन्यथा
			/* Set gain boundary in the middle
			 * between this curve and the next one */
			gain_boundaries[pdg] =
				(pwr_max[pdg] + pwr_min[pdg + 1]) / 2;

		/* Sanity check in हाल our 2 db stretch got out of
		 * range. */
		अगर (gain_boundaries[pdg] > AR5K_TUNE_MAX_TXPOWER)
			gain_boundaries[pdg] = AR5K_TUNE_MAX_TXPOWER;

		/* For the first curve (lower घातer)
		 * start from 0 dB */
		अगर (pdg == 0)
			pdadc_0 = 0;
		अन्यथा
			/* For the other curves use the gain overlap */
			pdadc_0 = (gain_boundaries[pdg - 1] - pwr_min[pdg]) -
							pd_gain_overlap;

		/* Force each घातer step to be at least 0.5 dB */
		अगर ((pdadc_पंचांगp[1] - pdadc_पंचांगp[0]) > 1)
			pwr_step = pdadc_पंचांगp[1] - pdadc_पंचांगp[0];
		अन्यथा
			pwr_step = 1;

		/* If pdadc_0 is negative, we need to extrapolate
		 * below this pdgain by a number of pwr_steps */
		जबतक ((pdadc_0 < 0) && (pdadc_i < 128)) अणु
			s16 पंचांगp = pdadc_पंचांगp[0] + pdadc_0 * pwr_step;
			pdadc_out[pdadc_i++] = (पंचांगp < 0) ? 0 : (u8) पंचांगp;
			pdadc_0++;
		पूर्ण

		/* Set last pwr level, using gain boundaries */
		pdadc_n = gain_boundaries[pdg] + pd_gain_overlap - pwr_min[pdg];
		/* Limit it to be inside pwr range */
		table_size = pwr_max[pdg] - pwr_min[pdg];
		max_idx = (pdadc_n < table_size) ? pdadc_n : table_size;

		/* Fill pdadc_out table */
		जबतक (pdadc_0 < max_idx && pdadc_i < 128)
			pdadc_out[pdadc_i++] = pdadc_पंचांगp[pdadc_0++];

		/* Need to extrapolate above this pdgain? */
		अगर (pdadc_n <= max_idx)
			जारी;

		/* Force each घातer step to be at least 0.5 dB */
		अगर ((pdadc_पंचांगp[table_size - 1] - pdadc_पंचांगp[table_size - 2]) > 1)
			pwr_step = pdadc_पंचांगp[table_size - 1] -
						pdadc_पंचांगp[table_size - 2];
		अन्यथा
			pwr_step = 1;

		/* Extrapolate above */
		जबतक ((pdadc_0 < (s16) pdadc_n) &&
		(pdadc_i < AR5K_EEPROM_POWER_TABLE_SIZE * 2)) अणु
			s16 पंचांगp = pdadc_पंचांगp[table_size - 1] +
					(pdadc_0 - max_idx) * pwr_step;
			pdadc_out[pdadc_i++] = (पंचांगp > 127) ? 127 : (u8) पंचांगp;
			pdadc_0++;
		पूर्ण
	पूर्ण

	जबतक (pdg < AR5K_EEPROM_N_PD_GAINS) अणु
		gain_boundaries[pdg] = gain_boundaries[pdg - 1];
		pdg++;
	पूर्ण

	जबतक (pdadc_i < AR5K_EEPROM_POWER_TABLE_SIZE * 2) अणु
		pdadc_out[pdadc_i] = pdadc_out[pdadc_i - 1];
		pdadc_i++;
	पूर्ण

	/* Set gain boundaries */
	ath5k_hw_reg_ग_लिखो(ah,
		AR5K_REG_SM(pd_gain_overlap,
			AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP) |
		AR5K_REG_SM(gain_boundaries[0],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1) |
		AR5K_REG_SM(gain_boundaries[1],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2) |
		AR5K_REG_SM(gain_boundaries[2],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3) |
		AR5K_REG_SM(gain_boundaries[3],
			AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4),
		AR5K_PHY_TPC_RG5);

	/* Used क्रम setting rate घातer table */
	ah->ah_txघातer.txp_min_idx = pwr_min[0];

पूर्ण

/**
 * ath5k_ग_लिखो_pwr_to_pdadc_table() - Write the PDADC values on hw
 * @ah: The &काष्ठा ath5k_hw
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 */
अटल व्योम
ath5k_ग_लिखो_pwr_to_pdadc_table(काष्ठा ath5k_hw *ah, u8 ee_mode)
अणु
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 *pdadc_out = ah->ah_txघातer.txp_pd_table;
	u8 *pdg_to_idx = ee->ee_pdc_to_idx[ee_mode];
	u8 pdcurves = ee->ee_pd_gains[ee_mode];
	u32 reg;
	u8 i;

	/* Select the right pdgain curves */

	/* Clear current settings */
	reg = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_TPC_RG1);
	reg &= ~(AR5K_PHY_TPC_RG1_PDGAIN_1 |
		AR5K_PHY_TPC_RG1_PDGAIN_2 |
		AR5K_PHY_TPC_RG1_PDGAIN_3 |
		AR5K_PHY_TPC_RG1_NUM_PD_GAIN);

	/*
	 * Use pd_gains curve from eeprom
	 *
	 * This overrides the शेष setting from initvals
	 * in हाल some venकरोrs (e.g. Zcomax) करोn't use the शेष
	 * curves. If we करोn't honor their settings we 'll get a
	 * 5dB (1 * gain overlap ?) drop.
	 */
	reg |= AR5K_REG_SM(pdcurves, AR5K_PHY_TPC_RG1_NUM_PD_GAIN);

	चयन (pdcurves) अणु
	हाल 3:
		reg |= AR5K_REG_SM(pdg_to_idx[2], AR5K_PHY_TPC_RG1_PDGAIN_3);
		fallthrough;
	हाल 2:
		reg |= AR5K_REG_SM(pdg_to_idx[1], AR5K_PHY_TPC_RG1_PDGAIN_2);
		fallthrough;
	हाल 1:
		reg |= AR5K_REG_SM(pdg_to_idx[0], AR5K_PHY_TPC_RG1_PDGAIN_1);
		अवरोध;
	पूर्ण
	ath5k_hw_reg_ग_लिखो(ah, reg, AR5K_PHY_TPC_RG1);

	/*
	 * Write TX घातer values
	 */
	क्रम (i = 0; i < (AR5K_EEPROM_POWER_TABLE_SIZE / 2); i++) अणु
		u32 val = get_unaligned_le32(&pdadc_out[4 * i]);
		ath5k_hw_reg_ग_लिखो(ah, val, AR5K_PHY_PDADC_TXPOWER(i));
	पूर्ण
पूर्ण


/*
 * Common code क्रम PCDAC/PDADC tables
 */

/**
 * ath5k_setup_channel_घातertable() - Set up घातer table क्रम this channel
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 * @type: One of क्रमागत ath5k_घातertable_type (eeprom.h)
 *
 * This is the मुख्य function that uses all of the above
 * to set PCDAC/PDADC table on hw क्रम the current channel.
 * This table is used क्रम tx घातer calibration on the baseband,
 * without it we get weird tx घातer levels and in some हालs
 * distorted spectral mask
 */
अटल पूर्णांक
ath5k_setup_channel_घातertable(काष्ठा ath5k_hw *ah,
			काष्ठा ieee80211_channel *channel,
			u8 ee_mode, u8 type)
अणु
	काष्ठा ath5k_pdgain_info *pdg_L, *pdg_R;
	काष्ठा ath5k_chan_pcal_info *pcinfo_L;
	काष्ठा ath5k_chan_pcal_info *pcinfo_R;
	काष्ठा ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 *pdg_curve_to_idx = ee->ee_pdc_to_idx[ee_mode];
	s16 table_min[AR5K_EEPROM_N_PD_GAINS];
	s16 table_max[AR5K_EEPROM_N_PD_GAINS];
	u8 *पंचांगpL;
	u8 *पंचांगpR;
	u32 target = channel->center_freq;
	पूर्णांक pdg, i;

	/* Get surrounding freq piers क्रम this channel */
	ath5k_get_chan_pcal_surrounding_piers(ah, channel,
						&pcinfo_L,
						&pcinfo_R);

	/* Loop over pd gain curves on
	 * surrounding freq piers by index */
	क्रम (pdg = 0; pdg < ee->ee_pd_gains[ee_mode]; pdg++) अणु

		/* Fill curves in reverse order
		 * from lower घातer (max gain)
		 * to higher घातer. Use curve -> idx
		 * backmapping we did on eeprom init */
		u8 idx = pdg_curve_to_idx[pdg];

		/* Grab the needed curves by index */
		pdg_L = &pcinfo_L->pd_curves[idx];
		pdg_R = &pcinfo_R->pd_curves[idx];

		/* Initialize the temp tables */
		पंचांगpL = ah->ah_txघातer.पंचांगpL[pdg];
		पंचांगpR = ah->ah_txघातer.पंचांगpR[pdg];

		/* Set curve's x boundaries and create
		 * curves so that they cover the same
		 * range (अगर we करोn't करो that one table
		 * will have values on some range and the
		 * other one won't have any so पूर्णांकerpolation
		 * will fail) */
		table_min[pdg] = min(pdg_L->pd_pwr[0],
					pdg_R->pd_pwr[0]) / 2;

		table_max[pdg] = max(pdg_L->pd_pwr[pdg_L->pd_poपूर्णांकs - 1],
				pdg_R->pd_pwr[pdg_R->pd_poपूर्णांकs - 1]) / 2;

		/* Now create the curves on surrounding channels
		 * and पूर्णांकerpolate अगर needed to get the final
		 * curve क्रम this gain on this channel */
		चयन (type) अणु
		हाल AR5K_PWRTABLE_LINEAR_PCDAC:
			/* Override min/max so that we करोn't loose
			 * accuracy (करोn't भागide by 2) */
			table_min[pdg] = min(pdg_L->pd_pwr[0],
						pdg_R->pd_pwr[0]);

			table_max[pdg] =
				max(pdg_L->pd_pwr[pdg_L->pd_poपूर्णांकs - 1],
					pdg_R->pd_pwr[pdg_R->pd_poपूर्णांकs - 1]);

			/* Override minimum so that we करोn't get
			 * out of bounds जबतक extrapolating
			 * below. Don't करो this when we have 2
			 * curves and we are on the high घातer curve
			 * because table_min is ok in this हाल */
			अगर (!(ee->ee_pd_gains[ee_mode] > 1 && pdg == 0)) अणु

				table_min[pdg] =
					ath5k_get_linear_pcdac_min(pdg_L->pd_step,
								pdg_R->pd_step,
								pdg_L->pd_pwr,
								pdg_R->pd_pwr);

				/* Don't go too low because we will
				 * miss the upper part of the curve.
				 * Note: 126 = 31.5dB (max घातer supported)
				 * in 0.25dB units */
				अगर (table_max[pdg] - table_min[pdg] > 126)
					table_min[pdg] = table_max[pdg] - 126;
			पूर्ण

			fallthrough;
		हाल AR5K_PWRTABLE_PWR_TO_PCDAC:
		हाल AR5K_PWRTABLE_PWR_TO_PDADC:

			ath5k_create_घातer_curve(table_min[pdg],
						table_max[pdg],
						pdg_L->pd_pwr,
						pdg_L->pd_step,
						pdg_L->pd_poपूर्णांकs, पंचांगpL, type);

			/* We are in a calibration
			 * pier, no need to पूर्णांकerpolate
			 * between freq piers */
			अगर (pcinfo_L == pcinfo_R)
				जारी;

			ath5k_create_घातer_curve(table_min[pdg],
						table_max[pdg],
						pdg_R->pd_pwr,
						pdg_R->pd_step,
						pdg_R->pd_poपूर्णांकs, पंचांगpR, type);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* Interpolate between curves
		 * of surrounding freq piers to
		 * get the final curve क्रम this
		 * pd gain. Re-use पंचांगpL क्रम पूर्णांकerpolation
		 * output */
		क्रम (i = 0; (i < (u16) (table_max[pdg] - table_min[pdg])) &&
		(i < AR5K_EEPROM_POWER_TABLE_SIZE); i++) अणु
			पंचांगpL[i] = (u8) ath5k_get_पूर्णांकerpolated_value(target,
							(s16) pcinfo_L->freq,
							(s16) pcinfo_R->freq,
							(s16) पंचांगpL[i],
							(s16) पंचांगpR[i]);
		पूर्ण
	पूर्ण

	/* Now we have a set of curves क्रम this
	 * channel on पंचांगpL (x range is table_max - table_min
	 * and y values are पंचांगpL[pdg][]) sorted in the same
	 * order as EEPROM (because we've used the backmapping).
	 * So क्रम RF5112 it's from higher घातer to lower घातer
	 * and क्रम RF2413 it's from lower घातer to higher घातer.
	 * For RF5111 we only have one curve. */

	/* Fill min and max घातer levels क्रम this
	 * channel by पूर्णांकerpolating the values on
	 * surrounding channels to complete the dataset */
	ah->ah_txघातer.txp_min_pwr = ath5k_get_पूर्णांकerpolated_value(target,
					(s16) pcinfo_L->freq,
					(s16) pcinfo_R->freq,
					pcinfo_L->min_pwr, pcinfo_R->min_pwr);

	ah->ah_txघातer.txp_max_pwr = ath5k_get_पूर्णांकerpolated_value(target,
					(s16) pcinfo_L->freq,
					(s16) pcinfo_R->freq,
					pcinfo_L->max_pwr, pcinfo_R->max_pwr);

	/* Fill PCDAC/PDADC table */
	चयन (type) अणु
	हाल AR5K_PWRTABLE_LINEAR_PCDAC:
		/* For RF5112 we can have one or two curves
		 * and each curve covers a certain घातer lvl
		 * range so we need to करो some more processing */
		ath5k_combine_linear_pcdac_curves(ah, table_min, table_max,
						ee->ee_pd_gains[ee_mode]);

		/* Set txp.offset so that we can
		 * match max घातer value with max
		 * table index */
		ah->ah_txघातer.txp_offset = 64 - (table_max[0] / 2);
		अवरोध;
	हाल AR5K_PWRTABLE_PWR_TO_PCDAC:
		/* We are करोne क्रम RF5111 since it has only
		 * one curve, just fit the curve on the table */
		ath5k_fill_pwr_to_pcdac_table(ah, table_min, table_max);

		/* No rate घातertable adjusपंचांगent क्रम RF5111 */
		ah->ah_txघातer.txp_min_idx = 0;
		ah->ah_txघातer.txp_offset = 0;
		अवरोध;
	हाल AR5K_PWRTABLE_PWR_TO_PDADC:
		/* Set PDADC boundaries and fill
		 * final PDADC table */
		ath5k_combine_pwr_to_pdadc_curves(ah, table_min, table_max,
						ee->ee_pd_gains[ee_mode]);

		/* Set txp.offset, note that table_min
		 * can be negative */
		ah->ah_txघातer.txp_offset = table_min[0];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ah->ah_txघातer.txp_setup = true;

	वापस 0;
पूर्ण

/**
 * ath5k_ग_लिखो_channel_घातertable() - Set घातer table क्रम current channel on hw
 * @ah: The &काष्ठा ath5k_hw
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 * @type: One of क्रमागत ath5k_घातertable_type (eeprom.h)
 */
अटल व्योम
ath5k_ग_लिखो_channel_घातertable(काष्ठा ath5k_hw *ah, u8 ee_mode, u8 type)
अणु
	अगर (type == AR5K_PWRTABLE_PWR_TO_PDADC)
		ath5k_ग_लिखो_pwr_to_pdadc_table(ah, ee_mode);
	अन्यथा
		ath5k_ग_लिखो_pcdac_table(ah);
पूर्ण


/**
 * DOC: Per-rate tx घातer setting
 *
 * This is the code that sets the desired tx घातer limit (below
 * maximum) on hw क्रम each rate (we also have TPC that sets
 * घातer per packet type). We करो that by providing an index on the
 * PCDAC/PDADC table we set up above, क्रम each rate.
 *
 * For now we only limit txघातer based on maximum tx घातer
 * supported by hw (what's inside rate_info) + conक्रमmance test
 * limits. We need to limit this even more, based on regulatory करोमुख्य
 * etc to be safe. Normally this is करोne from above so we करोn't care
 * here, all we care is that the tx घातer we set will be O.K.
 * क्रम the hw (e.g. won't create noise on PA etc).
 *
 * Rate घातer table contains indices to PCDAC/PDADC table (0.5dB steps -
 * x values) and is indexed as follows:
 * rates[0] - rates[7] -> OFDM rates
 * rates[8] - rates[14] -> CCK rates
 * rates[15] -> XR rates (they all have the same घातer)
 */

/**
 * ath5k_setup_rate_घातertable() - Set up rate घातer table क्रम a given tx घातer
 * @ah: The &काष्ठा ath5k_hw
 * @max_pwr: The maximum tx घातer requested in 0.5dB steps
 * @rate_info: The &काष्ठा ath5k_rate_pcal_info to fill
 * @ee_mode: One of क्रमागत ath5k_driver_mode
 */
अटल व्योम
ath5k_setup_rate_घातertable(काष्ठा ath5k_hw *ah, u16 max_pwr,
			काष्ठा ath5k_rate_pcal_info *rate_info,
			u8 ee_mode)
अणु
	अचिन्हित पूर्णांक i;
	u16 *rates;
	s16 rate_idx_scaled = 0;

	/* max_pwr is घातer level we got from driver/user in 0.5dB
	 * units, चयन to 0.25dB units so we can compare */
	max_pwr *= 2;
	max_pwr = min(max_pwr, (u16) ah->ah_txघातer.txp_max_pwr) / 2;

	/* apply rate limits */
	rates = ah->ah_txघातer.txp_rates_घातer_table;

	/* OFDM rates 6 to 24Mb/s */
	क्रम (i = 0; i < 5; i++)
		rates[i] = min(max_pwr, rate_info->target_घातer_6to24);

	/* Rest OFDM rates */
	rates[5] = min(rates[0], rate_info->target_घातer_36);
	rates[6] = min(rates[0], rate_info->target_घातer_48);
	rates[7] = min(rates[0], rate_info->target_घातer_54);

	/* CCK rates */
	/* 1L */
	rates[8] = min(rates[0], rate_info->target_घातer_6to24);
	/* 2L */
	rates[9] = min(rates[0], rate_info->target_घातer_36);
	/* 2S */
	rates[10] = min(rates[0], rate_info->target_घातer_36);
	/* 5L */
	rates[11] = min(rates[0], rate_info->target_घातer_48);
	/* 5S */
	rates[12] = min(rates[0], rate_info->target_घातer_48);
	/* 11L */
	rates[13] = min(rates[0], rate_info->target_घातer_54);
	/* 11S */
	rates[14] = min(rates[0], rate_info->target_घातer_54);

	/* XR rates */
	rates[15] = min(rates[0], rate_info->target_घातer_6to24);

	/* CCK rates have dअगरferent peak to average ratio
	 * so we have to tweak their घातer so that gainf
	 * correction works ok. For this we use OFDM to
	 * CCK delta from eeprom */
	अगर ((ee_mode == AR5K_EEPROM_MODE_11G) &&
	(ah->ah_phy_revision < AR5K_SREV_PHY_5212A))
		क्रम (i = 8; i <= 15; i++)
			rates[i] -= ah->ah_txघातer.txp_cck_ofdm_gainf_delta;

	/* Save min/max and current tx घातer क्रम this channel
	 * in 0.25dB units.
	 *
	 * Note: We use rates[0] क्रम current tx घातer because
	 * it covers most of the rates, in most हालs. It's our
	 * tx घातer limit and what the user expects to see. */
	ah->ah_txघातer.txp_min_pwr = 2 * rates[7];
	ah->ah_txघातer.txp_cur_pwr = 2 * rates[0];

	/* Set max txघातer क्रम correct OFDM operation on all rates
	 * -that is the txघातer क्रम 54Mbit-, it's used क्रम the PAPD
	 * gain probe and it's in 0.5dB units */
	ah->ah_txघातer.txp_ofdm = rates[7];

	/* Now that we have all rates setup use table offset to
	 * match the घातer range set by user with the घातer indices
	 * on PCDAC/PDADC table */
	क्रम (i = 0; i < 16; i++) अणु
		rate_idx_scaled = rates[i] + ah->ah_txघातer.txp_offset;
		/* Don't get out of bounds */
		अगर (rate_idx_scaled > 63)
			rate_idx_scaled = 63;
		अगर (rate_idx_scaled < 0)
			rate_idx_scaled = 0;
		rates[i] = rate_idx_scaled;
	पूर्ण
पूर्ण


/**
 * ath5k_hw_txघातer() - Set transmission घातer limit क्रम a given channel
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The &काष्ठा ieee80211_channel
 * @txघातer: Requested tx घातer in 0.5dB steps
 *
 * Combines all of the above to set the requested tx घातer limit
 * on hw.
 */
अटल पूर्णांक
ath5k_hw_txघातer(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel,
		 u8 txघातer)
अणु
	काष्ठा ath5k_rate_pcal_info rate_info;
	काष्ठा ieee80211_channel *curr_channel = ah->ah_current_channel;
	पूर्णांक ee_mode;
	u8 type;
	पूर्णांक ret;

	अगर (txघातer > AR5K_TUNE_MAX_TXPOWER) अणु
		ATH5K_ERR(ah, "invalid tx power: %u\n", txघातer);
		वापस -EINVAL;
	पूर्ण

	ee_mode = ath5k_eeprom_mode_from_channel(ah, channel);

	/* Initialize TX घातer table */
	चयन (ah->ah_radio) अणु
	हाल AR5K_RF5110:
		/* TODO */
		वापस 0;
	हाल AR5K_RF5111:
		type = AR5K_PWRTABLE_PWR_TO_PCDAC;
		अवरोध;
	हाल AR5K_RF5112:
		type = AR5K_PWRTABLE_LINEAR_PCDAC;
		अवरोध;
	हाल AR5K_RF2413:
	हाल AR5K_RF5413:
	हाल AR5K_RF2316:
	हाल AR5K_RF2317:
	हाल AR5K_RF2425:
		type = AR5K_PWRTABLE_PWR_TO_PDADC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * If we करोn't change channel/mode skip tx घातertable calculation
	 * and use the cached one.
	 */
	अगर (!ah->ah_txघातer.txp_setup ||
	    (channel->hw_value != curr_channel->hw_value) ||
	    (channel->center_freq != curr_channel->center_freq)) अणु
		/* Reset TX घातer values but preserve requested
		 * tx घातer from above */
		पूर्णांक requested_txघातer = ah->ah_txघातer.txp_requested;

		स_रखो(&ah->ah_txघातer, 0, माप(ah->ah_txघातer));

		/* Restore TPC setting and requested tx घातer */
		ah->ah_txघातer.txp_tpc = AR5K_TUNE_TPC_TXPOWER;

		ah->ah_txघातer.txp_requested = requested_txघातer;

		/* Calculate the घातertable */
		ret = ath5k_setup_channel_घातertable(ah, channel,
							ee_mode, type);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Write table on hw */
	ath5k_ग_लिखो_channel_घातertable(ah, ee_mode, type);

	/* Limit max घातer अगर we have a CTL available */
	ath5k_get_max_ctl_घातer(ah, channel);

	/* FIXME: Antenna reduction stuff */

	/* FIXME: Limit घातer on turbo modes */

	/* FIXME: TPC scale reduction */

	/* Get surrounding channels क्रम per-rate घातer table
	 * calibration */
	ath5k_get_rate_pcal_data(ah, channel, &rate_info);

	/* Setup rate घातer table */
	ath5k_setup_rate_घातertable(ah, txघातer, &rate_info, ee_mode);

	/* Write rate घातer table on hw */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_TXPOWER_OFDM(3, 24) |
		AR5K_TXPOWER_OFDM(2, 16) | AR5K_TXPOWER_OFDM(1, 8) |
		AR5K_TXPOWER_OFDM(0, 0), AR5K_PHY_TXPOWER_RATE1);

	ath5k_hw_reg_ग_लिखो(ah, AR5K_TXPOWER_OFDM(7, 24) |
		AR5K_TXPOWER_OFDM(6, 16) | AR5K_TXPOWER_OFDM(5, 8) |
		AR5K_TXPOWER_OFDM(4, 0), AR5K_PHY_TXPOWER_RATE2);

	ath5k_hw_reg_ग_लिखो(ah, AR5K_TXPOWER_CCK(10, 24) |
		AR5K_TXPOWER_CCK(9, 16) | AR5K_TXPOWER_CCK(15, 8) |
		AR5K_TXPOWER_CCK(8, 0), AR5K_PHY_TXPOWER_RATE3);

	ath5k_hw_reg_ग_लिखो(ah, AR5K_TXPOWER_CCK(14, 24) |
		AR5K_TXPOWER_CCK(13, 16) | AR5K_TXPOWER_CCK(12, 8) |
		AR5K_TXPOWER_CCK(11, 0), AR5K_PHY_TXPOWER_RATE4);

	/* FIXME: TPC support */
	अगर (ah->ah_txघातer.txp_tpc) अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_TXPOWER_RATE_MAX_TPC_ENABLE |
			AR5K_TUNE_MAX_TXPOWER, AR5K_PHY_TXPOWER_RATE_MAX);

		ath5k_hw_reg_ग_लिखो(ah,
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_ACK) |
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_CTS) |
			AR5K_REG_MS(AR5K_TUNE_MAX_TXPOWER, AR5K_TPC_CHIRP),
			AR5K_TPC);
	पूर्ण अन्यथा अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_TUNE_MAX_TXPOWER,
			AR5K_PHY_TXPOWER_RATE_MAX);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_txघातer_limit() - Set txघातer limit क्रम the current channel
 * @ah: The &काष्ठा ath5k_hw
 * @txघातer: The requested tx घातer limit in 0.5dB steps
 *
 * This function provides access to ath5k_hw_txघातer to the driver in
 * हाल user or an application changes it जबतक PHY is running.
 */
पूर्णांक
ath5k_hw_set_txघातer_limit(काष्ठा ath5k_hw *ah, u8 txघातer)
अणु
	ATH5K_DBG(ah, ATH5K_DEBUG_TXPOWER,
		"changing txpower to %d\n", txघातer);

	वापस ath5k_hw_txघातer(ah, ah->ah_current_channel, txघातer);
पूर्ण


/*************\
 Init function
\*************/

/**
 * ath5k_hw_phy_init() - Initialize PHY
 * @ah: The &काष्ठा ath5k_hw
 * @channel: The @काष्ठा ieee80211_channel
 * @mode: One of क्रमागत ath5k_driver_mode
 * @fast: Try a fast channel चयन instead
 *
 * This is the मुख्य function used during reset to initialize PHY
 * or करो a fast channel change अगर possible.
 *
 * NOTE: Do not call this one from the driver, it assumes PHY is in a
 * warm reset state !
 */
पूर्णांक
ath5k_hw_phy_init(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channel,
		      u8 mode, bool fast)
अणु
	काष्ठा ieee80211_channel *curr_channel;
	पूर्णांक ret, i;
	u32 phy_tst1;
	ret = 0;

	/*
	 * Sanity check क्रम fast flag
	 * Don't try fast channel change when changing modulation
	 * mode/band. We check क्रम chip compatibility on
	 * ath5k_hw_reset.
	 */
	curr_channel = ah->ah_current_channel;
	अगर (fast && (channel->hw_value != curr_channel->hw_value))
		वापस -EINVAL;

	/*
	 * On fast channel change we only set the synth parameters
	 * जबतक PHY is running, enable calibration and skip the rest.
	 */
	अगर (fast) अणु
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_RFBUS_REQ,
				    AR5K_PHY_RFBUS_REQ_REQUEST);
		क्रम (i = 0; i < 100; i++) अणु
			अगर (ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_RFBUS_GRANT))
				अवरोध;
			udelay(5);
		पूर्ण
		/* Failed */
		अगर (i >= 100)
			वापस -EIO;

		/* Set channel and रुको क्रम synth */
		ret = ath5k_hw_channel(ah, channel);
		अगर (ret)
			वापस ret;

		ath5k_hw_रुको_क्रम_synth(ah, channel);
	पूर्ण

	/*
	 * Set TX घातer
	 *
	 * Note: We need to करो that beक्रमe we set
	 * RF buffer settings on 5211/5212+ so that we
	 * properly set curve indices.
	 */
	ret = ath5k_hw_txघातer(ah, channel, ah->ah_txघातer.txp_requested ?
					ah->ah_txघातer.txp_requested * 2 :
					AR5K_TUNE_MAX_TXPOWER);
	अगर (ret)
		वापस ret;

	/* Write OFDM timings on 5212*/
	अगर (ah->ah_version == AR5K_AR5212 &&
		channel->hw_value != AR5K_MODE_11B) अणु

		ret = ath5k_hw_ग_लिखो_ofdm_timings(ah, channel);
		अगर (ret)
			वापस ret;

		/* Spur info is available only from EEPROM versions
		 * greater than 5.3, but the EEPROM routines will use
		 * अटल values क्रम older versions */
		अगर (ah->ah_mac_srev >= AR5K_SREV_AR5424)
			ath5k_hw_set_spur_mitigation_filter(ah,
							    channel);
	पूर्ण

	/* If we used fast channel चयनing
	 * we are करोne, release RF bus and
	 * fire up NF calibration.
	 *
	 * Note: Only NF calibration due to
	 * channel change, not AGC calibration
	 * since AGC is still running !
	 */
	अगर (fast) अणु
		/*
		 * Release RF Bus grant
		 */
		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_RFBUS_REQ,
				    AR5K_PHY_RFBUS_REQ_REQUEST);

		/*
		 * Start NF calibration
		 */
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
					AR5K_PHY_AGCCTL_NF);

		वापस ret;
	पूर्ण

	/*
	 * For 5210 we करो all initialization using
	 * initvals, so we करोn't have to modअगरy
	 * any settings (5210 also only supports
	 * a/aturbo modes)
	 */
	अगर (ah->ah_version != AR5K_AR5210) अणु

		/*
		 * Write initial RF gain settings
		 * This should work क्रम both 5111/5112
		 */
		ret = ath5k_hw_rfgain_init(ah, channel->band);
		अगर (ret)
			वापस ret;

		usleep_range(1000, 1500);

		/*
		 * Write RF buffer
		 */
		ret = ath5k_hw_rfregs_init(ah, channel, mode);
		अगर (ret)
			वापस ret;

		/*Enable/disable 802.11b mode on 5111
		(enable 2111 frequency converter + CCK)*/
		अगर (ah->ah_radio == AR5K_RF5111) अणु
			अगर (mode == AR5K_MODE_11B)
				AR5K_REG_ENABLE_BITS(ah, AR5K_TXCFG,
				    AR5K_TXCFG_B_MODE);
			अन्यथा
				AR5K_REG_DISABLE_BITS(ah, AR5K_TXCFG,
				    AR5K_TXCFG_B_MODE);
		पूर्ण

	पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5210) अणु
		usleep_range(1000, 1500);
		/* Disable phy and रुको */
		ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ACT_DISABLE, AR5K_PHY_ACT);
		usleep_range(1000, 1500);
	पूर्ण

	/* Set channel on PHY */
	ret = ath5k_hw_channel(ah, channel);
	अगर (ret)
		वापस ret;

	/*
	 * Enable the PHY and रुको until completion
	 * This includes BaseBand and Synthesizer
	 * activation.
	 */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ACT_ENABLE, AR5K_PHY_ACT);

	ath5k_hw_रुको_क्रम_synth(ah, channel);

	/*
	 * Perक्रमm ADC test to see अगर baseband is पढ़ोy
	 * Set tx hold and check adc test रेजिस्टर
	 */
	phy_tst1 = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_TST1);
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_TST1_TXHOLD, AR5K_PHY_TST1);
	क्रम (i = 0; i <= 20; i++) अणु
		अगर (!(ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_ADC_TEST) & 0x10))
			अवरोध;
		usleep_range(200, 250);
	पूर्ण
	ath5k_hw_reg_ग_लिखो(ah, phy_tst1, AR5K_PHY_TST1);

	/*
	 * Start स्वतःmatic gain control calibration
	 *
	 * During AGC calibration RX path is re-routed to
	 * a घातer detector so we करोn't receive anything.
	 *
	 * This method is used to calibrate some अटल offsets
	 * used together with on-the fly I/Q calibration (the
	 * one perक्रमmed via ath5k_hw_phy_calibrate), which करोesn't
	 * पूर्णांकerrupt rx path.
	 *
	 * While rx path is re-routed to the घातer detector we also
	 * start a noise न्यूनमान calibration to measure the
	 * card's noise न्यूनमान (the noise we measure when we are not
	 * transmitting or receiving anything).
	 *
	 * If we are in a noisy environment, AGC calibration may समय
	 * out and/or noise न्यूनमान calibration might समयout.
	 */
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
				AR5K_PHY_AGCCTL_CAL | AR5K_PHY_AGCCTL_NF);

	/* At the same समय start I/Q calibration क्रम QAM स्थिरellation
	 * -no need क्रम CCK- */
	ah->ah_iq_cal_needed = false;
	अगर (!(mode == AR5K_MODE_11B)) अणु
		ah->ah_iq_cal_needed = true;
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_IQ,
				AR5K_PHY_IQ_CAL_NUM_LOG_MAX, 15);
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_IQ,
				AR5K_PHY_IQ_RUN);
	पूर्ण

	/* Wait क्रम gain calibration to finish (we check क्रम I/Q calibration
	 * during ath5k_phy_calibrate) */
	अगर (ath5k_hw_रेजिस्टर_समयout(ah, AR5K_PHY_AGCCTL,
			AR5K_PHY_AGCCTL_CAL, 0, false)) अणु
		ATH5K_ERR(ah, "gain calibration timeout (%uMHz)\n",
			channel->center_freq);
	पूर्ण

	/* Restore antenna mode */
	ath5k_hw_set_antenna_mode(ah, ah->ah_ant_mode);

	वापस ret;
पूर्ण

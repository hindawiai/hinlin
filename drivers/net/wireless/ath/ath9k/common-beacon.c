<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश "common.h"

#घोषणा FUDGE 2

अटल u32 ath9k_get_next_tbtt(काष्ठा ath_hw *ah, u64 tsf,
			       अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक offset, भागisor;

	tsf += TU_TO_USEC(FUDGE + ah->config.sw_beacon_response_समय);
	भागisor = TU_TO_USEC(पूर्णांकerval);
	भाग_u64_rem(tsf, भागisor, &offset);

	वापस (u32) tsf + भागisor - offset;
पूर्ण

/*
 * This sets up the beacon समयrs according to the बारtamp of the last
 * received beacon and the current TSF, configures PCF and DTIM
 * handling, programs the sleep रेजिस्टरs so the hardware will wakeup in
 * समय to receive beacons, and configures the beacon miss handling so
 * we'll receive a BMISS पूर्णांकerrupt when we stop seeing beacons from the AP
 * we've associated with.
 */
पूर्णांक ath9k_cmn_beacon_config_sta(काष्ठा ath_hw *ah,
				 काष्ठा ath_beacon_config *conf,
				 काष्ठा ath9k_beacon_state *bs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक dtim_पूर्णांकval;
	u64 tsf;

	/* No need to configure beacon अगर we are not associated */
	अगर (!test_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags)) अणु
		ath_dbg(common, BEACON,
			"STA is not yet associated..skipping beacon config\n");
		वापस -EPERM;
	पूर्ण

	स_रखो(bs, 0, माप(*bs));
	conf->पूर्णांकval = conf->beacon_पूर्णांकerval;

	/*
	 * Setup dtim parameters according to
	 * last beacon we received (which may be none).
	 */
	dtim_पूर्णांकval = conf->पूर्णांकval * conf->dtim_period;

	/*
	 * Pull nexttbtt क्रमward to reflect the current
	 * TSF and calculate dtim state क्रम the result.
	 */
	tsf = ath9k_hw_gettsf64(ah);
	conf->nexttbtt = ath9k_get_next_tbtt(ah, tsf, conf->पूर्णांकval);

	bs->bs_पूर्णांकval = TU_TO_USEC(conf->पूर्णांकval);
	bs->bs_dtimperiod = conf->dtim_period * bs->bs_पूर्णांकval;
	bs->bs_nexttbtt = conf->nexttbtt;
	bs->bs_nextdtim = conf->nexttbtt;
	अगर (conf->dtim_period > 1)
		bs->bs_nextdtim = ath9k_get_next_tbtt(ah, tsf, dtim_पूर्णांकval);

	/*
	 * Calculate the number of consecutive beacons to miss* beक्रमe taking
	 * a BMISS पूर्णांकerrupt. The configuration is specअगरied in TU so we only
	 * need calculate based	on the beacon पूर्णांकerval.  Note that we clamp the
	 * result to at most 15 beacons.
	 */
	bs->bs_bmissthreshold = DIV_ROUND_UP(conf->bmiss_समयout, conf->पूर्णांकval);
	अगर (bs->bs_bmissthreshold > 15)
		bs->bs_bmissthreshold = 15;
	अन्यथा अगर (bs->bs_bmissthreshold <= 0)
		bs->bs_bmissthreshold = 1;

	/*
	 * Calculate sleep duration. The configuration is given in ms.
	 * We ensure a multiple of the beacon period is used. Also, अगर the sleep
	 * duration is greater than the DTIM period then it makes senses
	 * to make it a multiple of that.
	 *
	 * XXX fixed at 100ms
	 */

	bs->bs_sleepduration = TU_TO_USEC(roundup(IEEE80211_MS_TO_TU(100),
						  conf->पूर्णांकval));
	अगर (bs->bs_sleepduration > bs->bs_dtimperiod)
		bs->bs_sleepduration = bs->bs_dtimperiod;

	/* TSF out of range threshold fixed at 1 second */
	bs->bs_tsfoor_threshold = ATH9K_TSFOOR_THRESHOLD;

	ath_dbg(common, BEACON, "bmiss: %u sleep: %u\n",
		bs->bs_bmissthreshold, bs->bs_sleepduration);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_beacon_config_sta);

व्योम ath9k_cmn_beacon_config_adhoc(काष्ठा ath_hw *ah,
				   काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	conf->पूर्णांकval = TU_TO_USEC(conf->beacon_पूर्णांकerval);

	अगर (conf->ibss_creator)
		conf->nexttbtt = conf->पूर्णांकval;
	अन्यथा
		conf->nexttbtt = ath9k_get_next_tbtt(ah, ath9k_hw_gettsf64(ah),
					       conf->beacon_पूर्णांकerval);

	अगर (conf->enable_beacon)
		ah->imask |= ATH9K_INT_SWBA;
	अन्यथा
		ah->imask &= ~ATH9K_INT_SWBA;

	ath_dbg(common, BEACON,
		"IBSS (%s) nexttbtt: %u intval: %u conf_intval: %u\n",
		(conf->enable_beacon) ? "Enable" : "Disable",
		conf->nexttbtt, conf->पूर्णांकval, conf->beacon_पूर्णांकerval);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_beacon_config_adhoc);

/*
 * For multi-bss ap support beacons are either staggered evenly over N slots or
 * burst together.  For the क्रमmer arrange क्रम the SWBA to be delivered क्रम each
 * slot. Slots that are not occupied will generate nothing.
 */
व्योम ath9k_cmn_beacon_config_ap(काष्ठा ath_hw *ah,
				काष्ठा ath_beacon_config *conf,
				अचिन्हित पूर्णांक bc_buf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	/* NB: the beacon पूर्णांकerval is kept पूर्णांकernally in TU's */
	conf->पूर्णांकval = TU_TO_USEC(conf->beacon_पूर्णांकerval);
	conf->पूर्णांकval /= bc_buf;
	conf->nexttbtt = ath9k_get_next_tbtt(ah, ath9k_hw_gettsf64(ah),
				       conf->beacon_पूर्णांकerval);

	अगर (conf->enable_beacon)
		ah->imask |= ATH9K_INT_SWBA;
	अन्यथा
		ah->imask &= ~ATH9K_INT_SWBA;

	ath_dbg(common, BEACON,
		"AP (%s) nexttbtt: %u intval: %u conf_intval: %u\n",
		(conf->enable_beacon) ? "Enable" : "Disable",
		conf->nexttbtt, conf->पूर्णांकval, conf->beacon_पूर्णांकerval);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_beacon_config_ap);

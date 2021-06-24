<शैली गुरु>
/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
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

#समावेश "ath9k.h"

/*
 * AR9285
 * ======
 *
 * EEPROM has 2 4-bit fields containing the card configuration.
 *
 * antभाग_ctl1:
 * ------------
 * bb_enable_ant_भाग_lnaभाग : 1
 * bb_ant_भाग_alt_gaपूर्णांकb    : 1
 * bb_ant_भाग_मुख्य_gaपूर्णांकb   : 1
 * bb_enable_ant_fast_भाग   : 1
 *
 * antभाग_ctl2:
 * -----------
 * bb_ant_भाग_alt_lnaconf  : 2
 * bb_ant_भाग_मुख्य_lnaconf : 2
 *
 * The EEPROM bits are used as follows:
 * ------------------------------------
 *
 * bb_enable_ant_भाग_lnaभाग      - Enable LNA path rx antenna भागersity/combining.
 *                                 Set in AR_PHY_MULTICHAIN_GAIN_CTL.
 *
 * bb_ant_भाग_[alt/मुख्य]_gaपूर्णांकb  - 0 -> Antenna config Alt/Main uses gaपूर्णांकable 0
 *                                 1 -> Antenna config Alt/Main uses gaपूर्णांकable 1
 *                                 Set in AR_PHY_MULTICHAIN_GAIN_CTL.
 *
 * bb_enable_ant_fast_भाग        - Enable fast antenna भागersity.
 *                                 Set in AR_PHY_CCK_DETECT.
 *
 * bb_ant_भाग_[alt/मुख्य]_lnaconf - Alt/Main LNA भागersity/combining input config.
 *                                 Set in AR_PHY_MULTICHAIN_GAIN_CTL.
 *                                 10=LNA1
 *                                 01=LNA2
 *                                 11=LNA1+LNA2
 *                                 00=LNA1-LNA2
 *
 * AR9485 / AR9565 / AR9331
 * ========================
 *
 * The same bits are present in the EEPROM, but the location in the
 * EEPROM is dअगरferent (ant_भाग_control in ar9300_BaseExtension_1).
 *
 * ant_भाग_alt_lnaconf      ==> bit 0~1
 * ant_भाग_मुख्य_lnaconf     ==> bit 2~3
 * ant_भाग_alt_gaपूर्णांकb       ==> bit 4
 * ant_भाग_मुख्य_gaपूर्णांकb      ==> bit 5
 * enable_ant_भाग_lnaभाग    ==> bit 6
 * enable_ant_fast_भाग      ==> bit 7
 */

अटल अंतरभूत bool ath_is_alt_ant_ratio_better(काष्ठा ath_ant_comb *antcomb,
					       पूर्णांक alt_ratio, पूर्णांक maxdelta,
					       पूर्णांक mindelta, पूर्णांक मुख्य_rssi_avg,
					       पूर्णांक alt_rssi_avg, पूर्णांक pkt_count)
अणु
	अगर (pkt_count <= 50)
		वापस false;

	अगर (alt_rssi_avg > मुख्य_rssi_avg + mindelta)
		वापस true;

	अगर (alt_ratio >= antcomb->ant_ratio2 &&
	    alt_rssi_avg >= antcomb->low_rssi_thresh &&
	    (alt_rssi_avg > मुख्य_rssi_avg + maxdelta))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool ath_ant_भाग_comb_alt_check(काष्ठा ath_hw_antcomb_conf *conf,
					      काष्ठा ath_ant_comb *antcomb,
					      पूर्णांक alt_ratio, पूर्णांक alt_rssi_avg,
					      पूर्णांक मुख्य_rssi_avg)
अणु
	bool result, set1, set2;

	result = set1 = set2 = false;

	अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2 &&
	    conf->alt_lna_conf == ATH_ANT_DIV_COMB_LNA1)
		set1 = true;

	अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA1 &&
	    conf->alt_lna_conf == ATH_ANT_DIV_COMB_LNA2)
		set2 = true;

	चयन (conf->भाग_group) अणु
	हाल 0:
		अगर (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO)
			result = true;
		अवरोध;
	हाल 1:
	हाल 2:
		अगर (alt_rssi_avg < 4 || alt_rssi_avg < antcomb->low_rssi_thresh)
			अवरोध;

		अगर ((set1 && (alt_rssi_avg >= (मुख्य_rssi_avg - 5))) ||
		    (set2 && (alt_rssi_avg >= (मुख्य_rssi_avg - 2))) ||
		    (alt_ratio > antcomb->ant_ratio))
			result = true;

		अवरोध;
	हाल 3:
		अगर (alt_rssi_avg < 4 || alt_rssi_avg < antcomb->low_rssi_thresh)
			अवरोध;

		अगर ((set1 && (alt_rssi_avg >= (मुख्य_rssi_avg - 3))) ||
		    (set2 && (alt_rssi_avg >= (मुख्य_rssi_avg + 3))) ||
		    (alt_ratio > antcomb->ant_ratio))
			result = true;

		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ath_lnaconf_alt_good_scan(काष्ठा ath_ant_comb *antcomb,
				      काष्ठा ath_hw_antcomb_conf ant_conf,
				      पूर्णांक मुख्य_rssi_avg)
अणु
	antcomb->quick_scan_cnt = 0;

	अगर (ant_conf.मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
		antcomb->rssi_lna2 = मुख्य_rssi_avg;
	अन्यथा अगर (ant_conf.मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA1)
		antcomb->rssi_lna1 = मुख्य_rssi_avg;

	चयन ((ant_conf.मुख्य_lna_conf << 4) | ant_conf.alt_lna_conf) अणु
	हाल 0x10: /* LNA2 A-B */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_LNA1;
		अवरोध;
	हाल 0x20: /* LNA1 A-B */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_LNA2;
		अवरोध;
	हाल 0x21: /* LNA1 LNA2 */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA2;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->second_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		अवरोध;
	हाल 0x12: /* LNA2 LNA1 */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA1;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->second_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		अवरोध;
	हाल 0x13: /* LNA2 A+B */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_LNA1;
		अवरोध;
	हाल 0x23: /* LNA1 A+B */
		antcomb->मुख्य_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		antcomb->first_quick_scan_conf =
			ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_LNA2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath_ant_set_alt_ratio(काष्ठा ath_ant_comb *antcomb,
				  काष्ठा ath_hw_antcomb_conf *conf)
अणु
	/* set alt to the conf with maximun ratio */
	अगर (antcomb->first_ratio && antcomb->second_ratio) अणु
		अगर (antcomb->rssi_second > antcomb->rssi_third) अणु
			/* first alt*/
			अगर ((antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
			    (antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
				/* Set alt LNA1 or LNA2*/
				अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
					conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				अन्यथा
					conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			अन्यथा
				/* Set alt to A+B or A-B */
				conf->alt_lna_conf =
					antcomb->first_quick_scan_conf;
		पूर्ण अन्यथा अगर ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
			   (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2)) अणु
			/* Set alt LNA1 or LNA2 */
			अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			अन्यथा
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		पूर्ण अन्यथा अणु
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->second_quick_scan_conf;
		पूर्ण
	पूर्ण अन्यथा अगर (antcomb->first_ratio) अणु
		/* first alt */
		अगर ((antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->first_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			अन्यथा
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		अन्यथा
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->first_quick_scan_conf;
	पूर्ण अन्यथा अगर (antcomb->second_ratio) अणु
		/* second alt */
		अगर ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			अन्यथा
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		अन्यथा
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->second_quick_scan_conf;
	पूर्ण अन्यथा अणु
		/* मुख्य is largest */
		अगर ((antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA1) ||
		    (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA2))
			/* Set alt LNA1 or LNA2 */
			अगर (conf->मुख्य_lna_conf == ATH_ANT_DIV_COMB_LNA2)
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			अन्यथा
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		अन्यथा
			/* Set alt to A+B or A-B */
			conf->alt_lna_conf = antcomb->मुख्य_conf;
	पूर्ण
पूर्ण

अटल व्योम ath_select_ant_भाग_from_quick_scan(काष्ठा ath_ant_comb *antcomb,
				       काष्ठा ath_hw_antcomb_conf *भाग_ant_conf,
				       पूर्णांक मुख्य_rssi_avg, पूर्णांक alt_rssi_avg,
				       पूर्णांक alt_ratio)
अणु
	/* alt_good */
	चयन (antcomb->quick_scan_cnt) अणु
	हाल 0:
		/* set alt to मुख्य, and alt to first conf */
		भाग_ant_conf->मुख्य_lna_conf = antcomb->मुख्य_conf;
		भाग_ant_conf->alt_lna_conf = antcomb->first_quick_scan_conf;
		अवरोध;
	हाल 1:
		/* set alt to मुख्य, and alt to first conf */
		भाग_ant_conf->मुख्य_lna_conf = antcomb->मुख्य_conf;
		भाग_ant_conf->alt_lna_conf = antcomb->second_quick_scan_conf;
		antcomb->rssi_first = मुख्य_rssi_avg;
		antcomb->rssi_second = alt_rssi_avg;

		अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA1) अणु
			/* मुख्य is LNA1 */
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			अन्यथा
				antcomb->first_ratio = false;
		पूर्ण अन्यथा अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA2) अणु
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			अन्यथा
				antcomb->first_ratio = false;
		पूर्ण अन्यथा अणु
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						0,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->first_ratio = true;
			अन्यथा
				antcomb->first_ratio = false;
		पूर्ण
		अवरोध;
	हाल 2:
		antcomb->alt_good = false;
		antcomb->scan_not_start = false;
		antcomb->scan = false;
		antcomb->rssi_first = मुख्य_rssi_avg;
		antcomb->rssi_third = alt_rssi_avg;

		चयन(antcomb->second_quick_scan_conf) अणु
		हाल ATH_ANT_DIV_COMB_LNA1:
			antcomb->rssi_lna1 = alt_rssi_avg;
			अवरोध;
		हाल ATH_ANT_DIV_COMB_LNA2:
			antcomb->rssi_lna2 = alt_rssi_avg;
			अवरोध;
		हाल ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2:
			अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA2)
				antcomb->rssi_lna2 = मुख्य_rssi_avg;
			अन्यथा अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA1)
				antcomb->rssi_lna1 = मुख्य_rssi_avg;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (antcomb->rssi_lna2 > antcomb->rssi_lna1 +
		    भाग_ant_conf->lna1_lna2_चयन_delta)
			भाग_ant_conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		अन्यथा
			भाग_ant_conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;

		अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA1) अणु
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			अन्यथा
				antcomb->second_ratio = false;
		पूर्ण अन्यथा अगर (antcomb->मुख्य_conf == ATH_ANT_DIV_COMB_LNA2) अणु
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_MID,
						ATH_ANT_DIV_COMB_LNA1_DELTA_LOW,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			अन्यथा
				antcomb->second_ratio = false;
		पूर्ण अन्यथा अणु
			अगर (ath_is_alt_ant_ratio_better(antcomb, alt_ratio,
						ATH_ANT_DIV_COMB_LNA1_DELTA_HI,
						0,
						मुख्य_rssi_avg, alt_rssi_avg,
						antcomb->total_pkt_count))
				antcomb->second_ratio = true;
			अन्यथा
				antcomb->second_ratio = false;
		पूर्ण

		ath_ant_set_alt_ratio(antcomb, भाग_ant_conf);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath_ant_भाग_conf_fast_भागbias(काष्ठा ath_hw_antcomb_conf *ant_conf,
					  काष्ठा ath_ant_comb *antcomb,
					  पूर्णांक alt_ratio)
अणु
	ant_conf->मुख्य_gaपूर्णांकb = 0;
	ant_conf->alt_gaपूर्णांकb = 0;

	अगर (ant_conf->भाग_group == 0) अणु
		/* Adjust the fast_भाग_bias based on मुख्य and alt lna conf */
		चयन ((ant_conf->मुख्य_lna_conf << 4) |
				ant_conf->alt_lna_conf) अणु
		हाल 0x01: /* A-B LNA2 */
			ant_conf->fast_भाग_bias = 0x3b;
			अवरोध;
		हाल 0x02: /* A-B LNA1 */
			ant_conf->fast_भाग_bias = 0x3d;
			अवरोध;
		हाल 0x03: /* A-B A+B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x10: /* LNA2 A-B */
			ant_conf->fast_भाग_bias = 0x7;
			अवरोध;
		हाल 0x12: /* LNA2 LNA1 */
			ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x13: /* LNA2 A+B */
			ant_conf->fast_भाग_bias = 0x7;
			अवरोध;
		हाल 0x20: /* LNA1 A-B */
			ant_conf->fast_भाग_bias = 0x6;
			अवरोध;
		हाल 0x21: /* LNA1 LNA2 */
			ant_conf->fast_भाग_bias = 0x0;
			अवरोध;
		हाल 0x23: /* LNA1 A+B */
			ant_conf->fast_भाग_bias = 0x6;
			अवरोध;
		हाल 0x30: /* A+B A-B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x31: /* A+B LNA2 */
			ant_conf->fast_भाग_bias = 0x3b;
			अवरोध;
		हाल 0x32: /* A+B LNA1 */
			ant_conf->fast_भाग_bias = 0x3d;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ant_conf->भाग_group == 1) अणु
		/* Adjust the fast_भाग_bias based on मुख्य and alt_lna_conf */
		चयन ((ant_conf->मुख्य_lna_conf << 4) |
			ant_conf->alt_lna_conf) अणु
		हाल 0x01: /* A-B LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x02: /* A-B LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x03: /* A-B A+B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x10: /* LNA2 A-B */
			अगर (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_भाग_bias = 0x3f;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x12: /* LNA2 LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x13: /* LNA2 A+B */
			अगर (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_भाग_bias = 0x3f;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x20: /* LNA1 A-B */
			अगर (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_भाग_bias = 0x3f;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x21: /* LNA1 LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x23: /* LNA1 A+B */
			अगर (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_भाग_bias = 0x3f;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x30: /* A+B A-B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x31: /* A+B LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x32: /* A+B LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ant_conf->भाग_group == 2) अणु
		/* Adjust the fast_भाग_bias based on मुख्य and alt_lna_conf */
		चयन ((ant_conf->मुख्य_lna_conf << 4) |
				ant_conf->alt_lna_conf) अणु
		हाल 0x01: /* A-B LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x02: /* A-B LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x03: /* A-B A+B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x10: /* LNA2 A-B */
			अगर (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_भाग_bias = 0x1;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x12: /* LNA2 LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x13: /* LNA2 A+B */
			अगर (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_भाग_bias = 0x1;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x20: /* LNA1 A-B */
			अगर (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_भाग_bias = 0x1;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x21: /* LNA1 LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x23: /* LNA1 A+B */
			अगर (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_भाग_bias = 0x1;
			अन्यथा
				ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x30: /* A+B A-B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x31: /* A+B LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x32: /* A+B LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (antcomb->fast_भाग_bias)
			ant_conf->fast_भाग_bias = antcomb->fast_भाग_bias;
	पूर्ण अन्यथा अगर (ant_conf->भाग_group == 3) अणु
		चयन ((ant_conf->मुख्य_lna_conf << 4) |
			ant_conf->alt_lna_conf) अणु
		हाल 0x01: /* A-B LNA2 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x02: /* A-B LNA1 */
			ant_conf->fast_भाग_bias = 0x39;
			अवरोध;
		हाल 0x03: /* A-B A+B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x10: /* LNA2 A-B */
			ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x12: /* LNA2 LNA1 */
			ant_conf->fast_भाग_bias = 0x3f;
			अवरोध;
		हाल 0x13: /* LNA2 A+B */
			ant_conf->fast_भाग_bias = 0x2;
			अवरोध;
		हाल 0x20: /* LNA1 A-B */
			ant_conf->fast_भाग_bias = 0x3;
			अवरोध;
		हाल 0x21: /* LNA1 LNA2 */
			ant_conf->fast_भाग_bias = 0x3;
			अवरोध;
		हाल 0x23: /* LNA1 A+B */
			ant_conf->fast_भाग_bias = 0x3;
			अवरोध;
		हाल 0x30: /* A+B A-B */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		हाल 0x31: /* A+B LNA2 */
			ant_conf->fast_भाग_bias = 0x6;
			अवरोध;
		हाल 0x32: /* A+B LNA1 */
			ant_conf->fast_भाग_bias = 0x1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath_ant_try_scan(काष्ठा ath_ant_comb *antcomb,
			     काष्ठा ath_hw_antcomb_conf *conf,
			     पूर्णांक curr_alt_set, पूर्णांक alt_rssi_avg,
			     पूर्णांक मुख्य_rssi_avg)
अणु
	चयन (curr_alt_set) अणु
	हाल ATH_ANT_DIV_COMB_LNA2:
		antcomb->rssi_lna2 = alt_rssi_avg;
		antcomb->rssi_lna1 = मुख्य_rssi_avg;
		antcomb->scan = true;
		/* set to A+B */
		conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		अवरोध;
	हाल ATH_ANT_DIV_COMB_LNA1:
		antcomb->rssi_lna1 = alt_rssi_avg;
		antcomb->rssi_lna2 = मुख्य_rssi_avg;
		antcomb->scan = true;
		/* set to A+B */
		conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
		अवरोध;
	हाल ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2:
		antcomb->rssi_add = alt_rssi_avg;
		antcomb->scan = true;
		/* set to A-B */
		conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
		अवरोध;
	हाल ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2:
		antcomb->rssi_sub = alt_rssi_avg;
		antcomb->scan = false;
		अगर (antcomb->rssi_lna2 >
		    (antcomb->rssi_lna1 + conf->lna1_lna2_चयन_delta)) अणु
			/* use LNA2 as मुख्य LNA */
			अगर ((antcomb->rssi_add > antcomb->rssi_lna1) &&
			    (antcomb->rssi_add > antcomb->rssi_sub)) अणु
				/* set to A+B */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			पूर्ण अन्यथा अगर (antcomb->rssi_sub >
				   antcomb->rssi_lna1) अणु
				/* set to A-B */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
			पूर्ण अन्यथा अणु
				/* set to LNA1 */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* use LNA1 as मुख्य LNA */
			अगर ((antcomb->rssi_add > antcomb->rssi_lna2) &&
			    (antcomb->rssi_add > antcomb->rssi_sub)) अणु
				/* set to A+B */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_PLUS_LNA2;
			पूर्ण अन्यथा अगर (antcomb->rssi_sub >
				   antcomb->rssi_lna1) अणु
				/* set to A-B */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1_MINUS_LNA2;
			पूर्ण अन्यथा अणु
				/* set to LNA2 */
				conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;
				conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool ath_ant_try_चयन(काष्ठा ath_hw_antcomb_conf *भाग_ant_conf,
			       काष्ठा ath_ant_comb *antcomb,
			       पूर्णांक alt_ratio, पूर्णांक alt_rssi_avg,
			       पूर्णांक मुख्य_rssi_avg, पूर्णांक curr_मुख्य_set,
			       पूर्णांक curr_alt_set)
अणु
	bool ret = false;

	अगर (ath_ant_भाग_comb_alt_check(भाग_ant_conf, antcomb, alt_ratio,
				       alt_rssi_avg, मुख्य_rssi_avg)) अणु
		अगर (curr_alt_set == ATH_ANT_DIV_COMB_LNA2) अणु
			/*
			 * Switch मुख्य and alt LNA.
			 */
			भाग_ant_conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA2;
			भाग_ant_conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
		पूर्ण अन्यथा अगर (curr_alt_set == ATH_ANT_DIV_COMB_LNA1) अणु
			भाग_ant_conf->मुख्य_lna_conf = ATH_ANT_DIV_COMB_LNA1;
			भाग_ant_conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;
		पूर्ण

		ret = true;
	पूर्ण अन्यथा अगर ((curr_alt_set != ATH_ANT_DIV_COMB_LNA1) &&
		   (curr_alt_set != ATH_ANT_DIV_COMB_LNA2)) अणु
		/*
		  Set alt to another LNA.
		*/
		अगर (curr_मुख्य_set == ATH_ANT_DIV_COMB_LNA2)
			भाग_ant_conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA1;
		अन्यथा अगर (curr_मुख्य_set == ATH_ANT_DIV_COMB_LNA1)
			भाग_ant_conf->alt_lna_conf = ATH_ANT_DIV_COMB_LNA2;

		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ath_ant_लघु_scan_check(काष्ठा ath_ant_comb *antcomb)
अणु
	पूर्णांक alt_ratio;

	अगर (!antcomb->scan || !antcomb->alt_good)
		वापस false;

	अगर (समय_after(jअगरfies, antcomb->scan_start_समय +
		       msecs_to_jअगरfies(ATH_ANT_DIV_COMB_SHORT_SCAN_INTR)))
		वापस true;

	अगर (antcomb->total_pkt_count == ATH_ANT_DIV_COMB_SHORT_SCAN_PKTCOUNT) अणु
		alt_ratio = ((antcomb->alt_recv_cnt * 100) /
			     antcomb->total_pkt_count);
		अगर (alt_ratio < antcomb->ant_ratio)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम ath_ant_comb_scan(काष्ठा ath_softc *sc, काष्ठा ath_rx_status *rs)
अणु
	काष्ठा ath_hw_antcomb_conf भाग_ant_conf;
	काष्ठा ath_ant_comb *antcomb = &sc->ant_comb;
	पूर्णांक alt_ratio = 0, alt_rssi_avg = 0, मुख्य_rssi_avg = 0, curr_alt_set;
	पूर्णांक curr_मुख्य_set;
	पूर्णांक मुख्य_rssi = rs->rs_rssi_ctl[0];
	पूर्णांक alt_rssi = rs->rs_rssi_ctl[1];
	पूर्णांक rx_ant_conf,  मुख्य_ant_conf;
	bool लघु_scan = false, ret;

	rx_ant_conf = (rs->rs_rssi_ctl[2] >> ATH_ANT_RX_CURRENT_SHIFT) &
		       ATH_ANT_RX_MASK;
	मुख्य_ant_conf = (rs->rs_rssi_ctl[2] >> ATH_ANT_RX_MAIN_SHIFT) &
			 ATH_ANT_RX_MASK;

	अगर (alt_rssi >= antcomb->low_rssi_thresh) अणु
		antcomb->ant_ratio = ATH_ANT_DIV_COMB_ALT_ANT_RATIO;
		antcomb->ant_ratio2 = ATH_ANT_DIV_COMB_ALT_ANT_RATIO2;
	पूर्ण अन्यथा अणु
		antcomb->ant_ratio = ATH_ANT_DIV_COMB_ALT_ANT_RATIO_LOW_RSSI;
		antcomb->ant_ratio2 = ATH_ANT_DIV_COMB_ALT_ANT_RATIO2_LOW_RSSI;
	पूर्ण

	/* Record packet only when both मुख्य_rssi and  alt_rssi is positive */
	अगर (मुख्य_rssi > 0 && alt_rssi > 0) अणु
		antcomb->total_pkt_count++;
		antcomb->मुख्य_total_rssi += मुख्य_rssi;
		antcomb->alt_total_rssi  += alt_rssi;

		अगर (मुख्य_ant_conf == rx_ant_conf)
			antcomb->मुख्य_recv_cnt++;
		अन्यथा
			antcomb->alt_recv_cnt++;
	पूर्ण

	अगर (मुख्य_ant_conf == rx_ant_conf) अणु
		ANT_STAT_INC(sc, ANT_MAIN, recv_cnt);
		ANT_LNA_INC(sc, ANT_MAIN, rx_ant_conf);
	पूर्ण अन्यथा अणु
		ANT_STAT_INC(sc, ANT_ALT, recv_cnt);
		ANT_LNA_INC(sc, ANT_ALT, rx_ant_conf);
	पूर्ण

	/* Short scan check */
	लघु_scan = ath_ant_लघु_scan_check(antcomb);

	अगर (((antcomb->total_pkt_count < ATH_ANT_DIV_COMB_MAX_PKTCOUNT) ||
	     rs->rs_moreaggr) && !लघु_scan)
		वापस;

	अगर (antcomb->total_pkt_count) अणु
		alt_ratio = ((antcomb->alt_recv_cnt * 100) /
			     antcomb->total_pkt_count);
		मुख्य_rssi_avg = (antcomb->मुख्य_total_rssi /
				 antcomb->total_pkt_count);
		alt_rssi_avg = (antcomb->alt_total_rssi /
				 antcomb->total_pkt_count);
	पूर्ण

	ath9k_hw_antभाग_comb_conf_get(sc->sc_ah, &भाग_ant_conf);
	curr_alt_set = भाग_ant_conf.alt_lna_conf;
	curr_मुख्य_set = भाग_ant_conf.मुख्य_lna_conf;
	antcomb->count++;

	अगर (antcomb->count == ATH_ANT_DIV_COMB_MAX_COUNT) अणु
		अगर (alt_ratio > antcomb->ant_ratio) अणु
			ath_lnaconf_alt_good_scan(antcomb, भाग_ant_conf,
						  मुख्य_rssi_avg);
			antcomb->alt_good = true;
		पूर्ण अन्यथा अणु
			antcomb->alt_good = false;
		पूर्ण

		antcomb->count = 0;
		antcomb->scan = true;
		antcomb->scan_not_start = true;
	पूर्ण

	अगर (!antcomb->scan) अणु
		ret = ath_ant_try_चयन(&भाग_ant_conf, antcomb, alt_ratio,
					 alt_rssi_avg, मुख्य_rssi_avg,
					 curr_मुख्य_set, curr_alt_set);
		अगर (ret)
			जाओ भाग_comb_करोne;
	पूर्ण

	अगर (!antcomb->scan &&
	    (alt_rssi_avg < (मुख्य_rssi_avg + भाग_ant_conf.lna1_lna2_delta)))
		जाओ भाग_comb_करोne;

	अगर (!antcomb->scan_not_start) अणु
		ath_ant_try_scan(antcomb, &भाग_ant_conf, curr_alt_set,
				 alt_rssi_avg, मुख्य_rssi_avg);
	पूर्ण अन्यथा अणु
		अगर (!antcomb->alt_good) अणु
			antcomb->scan_not_start = false;
			/* Set alt to another LNA */
			अगर (curr_मुख्य_set == ATH_ANT_DIV_COMB_LNA2) अणु
				भाग_ant_conf.मुख्य_lna_conf =
					ATH_ANT_DIV_COMB_LNA2;
				भाग_ant_conf.alt_lna_conf =
					ATH_ANT_DIV_COMB_LNA1;
			पूर्ण अन्यथा अगर (curr_मुख्य_set == ATH_ANT_DIV_COMB_LNA1) अणु
				भाग_ant_conf.मुख्य_lna_conf =
					ATH_ANT_DIV_COMB_LNA1;
				भाग_ant_conf.alt_lna_conf =
					ATH_ANT_DIV_COMB_LNA2;
			पूर्ण
			जाओ भाग_comb_करोne;
		पूर्ण
		ath_select_ant_भाग_from_quick_scan(antcomb, &भाग_ant_conf,
						   मुख्य_rssi_avg, alt_rssi_avg,
						   alt_ratio);
		antcomb->quick_scan_cnt++;
	पूर्ण

भाग_comb_करोne:
	ath_ant_भाग_conf_fast_भागbias(&भाग_ant_conf, antcomb, alt_ratio);
	ath9k_hw_antभाग_comb_conf_set(sc->sc_ah, &भाग_ant_conf);
	ath9k_debug_stat_ant(sc, &भाग_ant_conf, मुख्य_rssi_avg, alt_rssi_avg);

	antcomb->scan_start_समय = jअगरfies;
	antcomb->total_pkt_count = 0;
	antcomb->मुख्य_total_rssi = 0;
	antcomb->alt_total_rssi = 0;
	antcomb->मुख्य_recv_cnt = 0;
	antcomb->alt_recv_cnt = 0;
पूर्ण

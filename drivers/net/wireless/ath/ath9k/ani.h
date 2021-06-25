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

#अगर_अघोषित ANI_H
#घोषणा ANI_H

#घोषणा BEACON_RSSI(ahp) (ahp->stats.avgbrssi)

/* units are errors per second */
#घोषणा ATH9K_ANI_OFDM_TRIG_HIGH           3500
#घोषणा ATH9K_ANI_OFDM_TRIG_HIGH_BELOW_INI 1000
#घोषणा ATH9K_ANI_OFDM_TRIG_HIGH_OLD       500

#घोषणा ATH9K_ANI_OFDM_TRIG_LOW           400
#घोषणा ATH9K_ANI_OFDM_TRIG_LOW_ABOVE_INI 900
#घोषणा ATH9K_ANI_OFDM_TRIG_LOW_OLD       200

#घोषणा ATH9K_ANI_CCK_TRIG_HIGH           600
#घोषणा ATH9K_ANI_CCK_TRIG_HIGH_OLD       200
#घोषणा ATH9K_ANI_CCK_TRIG_LOW            300
#घोषणा ATH9K_ANI_CCK_TRIG_LOW_OLD        100

#घोषणा ATH9K_ANI_SPUR_IMMUNE_LVL         3
#घोषणा ATH9K_ANI_FIRSTEP_LVL             2

#घोषणा ATH9K_ANI_RSSI_THR_HIGH           40
#घोषणा ATH9K_ANI_RSSI_THR_LOW            7

#घोषणा ATH9K_ANI_PERIOD                  300

/* in ms */
#घोषणा ATH9K_ANI_POLLINTERVAL            1000

#घोषणा ATH9K_SIG_FIRSTEP_SETTING_MIN     0
#घोषणा ATH9K_SIG_FIRSTEP_SETTING_MAX     20
#घोषणा ATH9K_SIG_SPUR_IMM_SETTING_MIN    0
#घोषणा ATH9K_SIG_SPUR_IMM_SETTING_MAX    22

/* values here are relative to the INI */

क्रमागत ath9k_ani_cmd अणु
	ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION = 0x1,
	ATH9K_ANI_FIRSTEP_LEVEL = 0x2,
	ATH9K_ANI_SPUR_IMMUNITY_LEVEL = 0x4,
	ATH9K_ANI_MRC_CCK = 0x8,
	ATH9K_ANI_ALL = 0xfff
पूर्ण;

काष्ठा ath9k_mib_stats अणु
	u32 ackrcv_bad;
	u32 rts_bad;
	u32 rts_good;
	u32 fcs_bad;
	u32 beacons;
पूर्ण;

/* INI शेष values क्रम ANI रेजिस्टरs */
काष्ठा ath9k_ani_शेष अणु
	u16 m1ThreshLow;
	u16 m2ThreshLow;
	u16 m1Thresh;
	u16 m2Thresh;
	u16 m2CountThr;
	u16 m2CountThrLow;
	u16 m1ThreshLowExt;
	u16 m2ThreshLowExt;
	u16 m1ThreshExt;
	u16 m2ThreshExt;
	u16 firstep;
	u16 firstepLow;
	u16 cycpwrThr1;
	u16 cycpwrThr1Ext;
पूर्ण;

काष्ठा ar5416AniState अणु
	u8 noiseImmunityLevel;
	u8 ofdmNoiseImmunityLevel;
	u8 cckNoiseImmunityLevel;
	bool ofdmsTurn;
	u8 mrcCCK;
	u8 spurImmunityLevel;
	u8 firstepLevel;
	bool ofdmWeakSigDetect;
	u32 listenTime;
	u32 ofdmPhyErrCount;
	u32 cckPhyErrCount;
	काष्ठा ath9k_ani_शेष iniDef;
पूर्ण;

काष्ठा ar5416Stats अणु
	u32 ast_ani_spurup;
	u32 ast_ani_spurकरोwn;
	u32 ast_ani_ofdmon;
	u32 ast_ani_ofdmoff;
	u32 ast_ani_cckhigh;
	u32 ast_ani_ccklow;
	u32 ast_ani_stepup;
	u32 ast_ani_stepकरोwn;
	u32 ast_ani_ofdmerrs;
	u32 ast_ani_cckerrs;
	u32 ast_ani_reset;
	u32 ast_ani_lneg_or_lzero;
	u32 avgbrssi;
	काष्ठा ath9k_mib_stats ast_mibstats;
पूर्ण;
#घोषणा ah_mibStats stats.ast_mibstats

व्योम ath9k_enable_mib_counters(काष्ठा ath_hw *ah);
व्योम ath9k_hw_disable_mib_counters(काष्ठा ath_hw *ah);
व्योम ath9k_hw_ani_init(काष्ठा ath_hw *ah);

#पूर्ण_अगर /* ANI_H */

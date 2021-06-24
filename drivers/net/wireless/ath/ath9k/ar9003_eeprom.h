<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#अगर_अघोषित AR9003_EEPROM_H
#घोषणा AR9003_EEPROM_H

#समावेश <linux/types.h>

#घोषणा AR9300_EEP_VER               0xD000
#घोषणा AR9300_EEP_VER_MINOR_MASK    0xFFF
#घोषणा AR9300_EEP_MINOR_VER_1       0x1
#घोषणा AR9300_EEP_MINOR_VER         AR9300_EEP_MINOR_VER_1

/* 16-bit offset location start of calibration काष्ठा */
#घोषणा AR9300_EEP_START_LOC         256
#घोषणा AR9300_NUM_5G_CAL_PIERS      8
#घोषणा AR9300_NUM_2G_CAL_PIERS      3
#घोषणा AR9300_NUM_5G_20_TARGET_POWERS  8
#घोषणा AR9300_NUM_5G_40_TARGET_POWERS  8
#घोषणा AR9300_NUM_2G_CCK_TARGET_POWERS 2
#घोषणा AR9300_NUM_2G_20_TARGET_POWERS  3
#घोषणा AR9300_NUM_2G_40_TARGET_POWERS  3
/* #घोषणा AR9300_NUM_CTLS              21 */
#घोषणा AR9300_NUM_CTLS_5G           9
#घोषणा AR9300_NUM_CTLS_2G           12
#घोषणा AR9300_NUM_BAND_EDGES_5G     8
#घोषणा AR9300_NUM_BAND_EDGES_2G     4
#घोषणा AR9300_EEPMISC_WOW           0x02
#घोषणा AR9300_CUSTOMER_DATA_SIZE    20

#घोषणा AR9300_MAX_CHAINS            3
#घोषणा AR9300_ANT_16S               25
#घोषणा AR9300_FUTURE_MODAL_SZ       6

#घोषणा AR9300_PAPRD_RATE_MASK		0x01ffffff
#घोषणा AR9300_PAPRD_SCALE_1		0x0e000000
#घोषणा AR9300_PAPRD_SCALE_1_S		25
#घोषणा AR9300_PAPRD_SCALE_2		0x70000000
#घोषणा AR9300_PAPRD_SCALE_2_S		28

#घोषणा AR9300_EEP_ANTDIV_CONTROL_DEFAULT_VALUE 0xc9

/* Delta from which to start घातer to pdadc table */
/* This offset is used in both खोलो loop and बंदd loop घातer control
 * schemes. In खोलो loop घातer control, it is not really needed, but क्रम
 * the "sake of consistency" it was kept. For certain AP designs, this
 * value is overwritten by the value in the flag "pwrTableOffset" just
 * beक्रमe writing the pdadc vs pwr पूर्णांकo the chip रेजिस्टरs.
 */
#घोषणा AR9300_PWR_TABLE_OFFSET  0

/* Noise घातer data definitions
 * units are: 4 x dBm - NOISE_PWR_DATA_OFFSET
 * (e.g. -25 = (-25/4 - 90) = -96.25 dBm)
 * range (क्रम 6 चिन्हित bits) is (-32 to 31) + offset => -122dBm to -59dBm
 * resolution (2 bits) is 0.25dBm
 */
#घोषणा NOISE_PWR_DATA_OFFSET	-90
#घोषणा NOISE_PWR_DBM_2_INT(_p)	((((_p) + 3) >> 2) + NOISE_PWR_DATA_OFFSET)
#घोषणा N2DBM(_p)		NOISE_PWR_DBM_2_INT(_p)

/* byte addressable */
#घोषणा AR9300_EEPROM_SIZE (16*1024)

#घोषणा AR9300_BASE_ADDR_4K 0xfff
#घोषणा AR9300_BASE_ADDR 0x3ff
#घोषणा AR9300_BASE_ADDR_512 0x1ff

/* AR5416_EEPMISC_BIG_ENDIAN not set indicates little endian */
#घोषणा AR9300_EEPMISC_LITTLE_ENDIAN 0

#घोषणा AR9300_OTP_BASE \
		((AR_SREV_9340(ah) || AR_SREV_9550(ah)) ? 0x30000 : 0x14000)
#घोषणा AR9300_OTP_STATUS \
		((AR_SREV_9340(ah) || AR_SREV_9550(ah)) ? 0x31018 : 0x15f18)
#घोषणा AR9300_OTP_STATUS_TYPE		0x7
#घोषणा AR9300_OTP_STATUS_VALID		0x4
#घोषणा AR9300_OTP_STATUS_ACCESS_BUSY	0x2
#घोषणा AR9300_OTP_STATUS_SM_BUSY	0x1
#घोषणा AR9300_OTP_READ_DATA \
		((AR_SREV_9340(ah) || AR_SREV_9550(ah)) ? 0x3101c : 0x15f1c)

क्रमागत targetPowerHTRates अणु
	HT_TARGET_RATE_0_8_16,
	HT_TARGET_RATE_1_3_9_11_17_19,
	HT_TARGET_RATE_4,
	HT_TARGET_RATE_5,
	HT_TARGET_RATE_6,
	HT_TARGET_RATE_7,
	HT_TARGET_RATE_12,
	HT_TARGET_RATE_13,
	HT_TARGET_RATE_14,
	HT_TARGET_RATE_15,
	HT_TARGET_RATE_20,
	HT_TARGET_RATE_21,
	HT_TARGET_RATE_22,
	HT_TARGET_RATE_23
पूर्ण;

क्रमागत targetPowerLegacyRates अणु
	LEGACY_TARGET_RATE_6_24,
	LEGACY_TARGET_RATE_36,
	LEGACY_TARGET_RATE_48,
	LEGACY_TARGET_RATE_54
पूर्ण;

क्रमागत targetPowerCckRates अणु
	LEGACY_TARGET_RATE_1L_5L,
	LEGACY_TARGET_RATE_5S,
	LEGACY_TARGET_RATE_11L,
	LEGACY_TARGET_RATE_11S
पूर्ण;

क्रमागत ar9300_Rates अणु
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_36,
	ALL_TARGET_LEGACY_48,
	ALL_TARGET_LEGACY_54,
	ALL_TARGET_LEGACY_1L_5L,
	ALL_TARGET_LEGACY_5S,
	ALL_TARGET_LEGACY_11L,
	ALL_TARGET_LEGACY_11S,
	ALL_TARGET_HT20_0_8_16,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_4,
	ALL_TARGET_HT20_5,
	ALL_TARGET_HT20_6,
	ALL_TARGET_HT20_7,
	ALL_TARGET_HT20_12,
	ALL_TARGET_HT20_13,
	ALL_TARGET_HT20_14,
	ALL_TARGET_HT20_15,
	ALL_TARGET_HT20_20,
	ALL_TARGET_HT20_21,
	ALL_TARGET_HT20_22,
	ALL_TARGET_HT20_23,
	ALL_TARGET_HT40_0_8_16,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_4,
	ALL_TARGET_HT40_5,
	ALL_TARGET_HT40_6,
	ALL_TARGET_HT40_7,
	ALL_TARGET_HT40_12,
	ALL_TARGET_HT40_13,
	ALL_TARGET_HT40_14,
	ALL_TARGET_HT40_15,
	ALL_TARGET_HT40_20,
	ALL_TARGET_HT40_21,
	ALL_TARGET_HT40_22,
	ALL_TARGET_HT40_23,
	ar9300RateSize,
पूर्ण;


काष्ठा eepFlags अणु
	u8 opFlags;
	u8 eepMisc;
पूर्ण __packed;

क्रमागत CompressAlgorithm अणु
	_CompressNone = 0,
	_CompressLzma,
	_CompressPairs,
	_CompressBlock,
	_Compress4,
	_Compress5,
	_Compress6,
	_Compress7,
पूर्ण;

काष्ठा ar9300_base_eep_hdr अणु
	__le16 regDmn[2];
	/* 4 bits tx and 4 bits rx */
	u8 txrxMask;
	काष्ठा eepFlags opCapFlags;
	u8 rfSilent;
	u8 blueToothOptions;
	u8 deviceCap;
	/* takes lower byte in eeprom location */
	u8 deviceType;
	/* offset in dB to be added to beginning
	 * of pdadc table in calibration
	 */
	पूर्णांक8_t pwrTableOffset;
	u8 params_क्रम_tuning_caps[2];
	/*
	 * bit0 - enable tx temp comp
	 * bit1 - enable tx volt comp
	 * bit2 - enable fastClock - शेष to 1
	 * bit3 - enable करोubling - शेष to 1
	 * bit4 - enable पूर्णांकernal regulator - शेष to 1
	 */
	u8 featureEnable;
	/* misc flags: bit0 - turn करोwn drivestrength */
	u8 miscConfiguration;
	u8 eepromWriteEnableGpio;
	u8 wlanDisableGpio;
	u8 wlanLedGpio;
	u8 rxBandSelectGpio;
	u8 txrxgain;
	/* SW controlled पूर्णांकernal regulator fields */
	__le32 swreg;
पूर्ण __packed;

काष्ठा ar9300_modal_eep_header अणु
	/* 4 idle, t1, t2, b (4 bits per setting) */
	__le32 antCtrlCommon;
	/* 4 ra1l1, ra2l1, ra1l2, ra2l2, ra12 */
	__le32 antCtrlCommon2;
	/* 6 idle, t, r, rx1, rx12, b (2 bits each) */
	__le16 antCtrlChain[AR9300_MAX_CHAINS];
	/* 3 xatten1_db क्रम AR9280 (0xa20c/b20c 5:0) */
	u8 xatten1DB[AR9300_MAX_CHAINS];
	/* 3  xatten1_margin क्रम merlin (0xa20c/b20c 16:12 */
	u8 xatten1Margin[AR9300_MAX_CHAINS];
	पूर्णांक8_t tempSlope;
	पूर्णांक8_t voltSlope;
	/* spur channels in usual fbin coding क्रमmat */
	u8 spurChans[AR_EEPROM_MODAL_SPURS];
	/* 3  Check अगर the रेजिस्टर is per chain */
	पूर्णांक8_t noiseFloorThreshCh[AR9300_MAX_CHAINS];
	u8 reserved[11];
	पूर्णांक8_t quick_drop;
	u8 xpaBiasLvl;
	u8 txFrameToDataStart;
	u8 txFrameToPaOn;
	u8 txClip;
	पूर्णांक8_t antennaGain;
	u8 चयनSettling;
	पूर्णांक8_t adcDesiredSize;
	u8 txEndToXpaOff;
	u8 txEndToRxOn;
	u8 txFrameToXpaOn;
	u8 thresh62;
	__le32 papdRateMaskHt20;
	__le32 papdRateMaskHt40;
	__le16 चयनcomspdt;
	u8 xlna_bias_strength;
	u8 futureModal[7];
पूर्ण __packed;

काष्ठा ar9300_cal_data_per_freq_op_loop अणु
	पूर्णांक8_t refPower;
	/* pdadc voltage at घातer measurement */
	u8 voltMeas;
	/* pcdac used क्रम घातer measurement   */
	u8 tempMeas;
	/* range is -60 to -127 create a mapping equation 1db resolution */
	पूर्णांक8_t rxNoiseन्यूनमानCal;
	/*range is same as noiseन्यूनमान */
	पूर्णांक8_t rxNoiseन्यूनमानPower;
	/* temp measured when noiseन्यूनमान cal was perक्रमmed */
	u8 rxTempMeas;
पूर्ण __packed;

काष्ठा cal_tgt_घात_legacy अणु
	u8 tPow2x[4];
पूर्ण __packed;

काष्ठा cal_tgt_घात_ht अणु
	u8 tPow2x[14];
पूर्ण __packed;

काष्ठा cal_ctl_data_2g अणु
	u8 ctlEdges[AR9300_NUM_BAND_EDGES_2G];
पूर्ण __packed;

काष्ठा cal_ctl_data_5g अणु
	u8 ctlEdges[AR9300_NUM_BAND_EDGES_5G];
पूर्ण __packed;

#घोषणा MAX_BASE_EXTENSION_FUTURE 2

काष्ठा ar9300_BaseExtension_1 अणु
	u8 ant_भाग_control;
	u8 future[MAX_BASE_EXTENSION_FUTURE];
	/*
	 * misc_enable:
	 *
	 * BIT 0   - TX Gain Cap enable.
	 * BIT 1   - Uncompressed Checksum enable.
	 * BIT 2/3 - MinCCApwr enable 2g/5g.
	 */
	u8 misc_enable;
	पूर्णांक8_t tempslopextension[8];
	पूर्णांक8_t quick_drop_low;
	पूर्णांक8_t quick_drop_high;
पूर्ण __packed;

काष्ठा ar9300_BaseExtension_2 अणु
	पूर्णांक8_t    tempSlopeLow;
	पूर्णांक8_t    tempSlopeHigh;
	u8   xatten1DBLow[AR9300_MAX_CHAINS];
	u8   xatten1MarginLow[AR9300_MAX_CHAINS];
	u8   xatten1DBHigh[AR9300_MAX_CHAINS];
	u8   xatten1MarginHigh[AR9300_MAX_CHAINS];
पूर्ण __packed;

काष्ठा ar9300_eeprom अणु
	u8 eepromVersion;
	u8 ढाँचाVersion;
	u8 macAddr[6];
	u8 custData[AR9300_CUSTOMER_DATA_SIZE];

	काष्ठा ar9300_base_eep_hdr baseEepHeader;

	काष्ठा ar9300_modal_eep_header modalHeader2G;
	काष्ठा ar9300_BaseExtension_1 base_ext1;
	u8 calFreqPier2G[AR9300_NUM_2G_CAL_PIERS];
	काष्ठा ar9300_cal_data_per_freq_op_loop
	 calPierData2G[AR9300_MAX_CHAINS][AR9300_NUM_2G_CAL_PIERS];
	u8 calTarget_freqbin_Cck[AR9300_NUM_2G_CCK_TARGET_POWERS];
	u8 calTarget_freqbin_2G[AR9300_NUM_2G_20_TARGET_POWERS];
	u8 calTarget_freqbin_2GHT20[AR9300_NUM_2G_20_TARGET_POWERS];
	u8 calTarget_freqbin_2GHT40[AR9300_NUM_2G_40_TARGET_POWERS];
	काष्ठा cal_tgt_घात_legacy
	 calTargetPowerCck[AR9300_NUM_2G_CCK_TARGET_POWERS];
	काष्ठा cal_tgt_घात_legacy
	 calTargetPower2G[AR9300_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_tgt_घात_ht
	 calTargetPower2GHT20[AR9300_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_tgt_घात_ht
	 calTargetPower2GHT40[AR9300_NUM_2G_40_TARGET_POWERS];
	u8 ctlIndex_2G[AR9300_NUM_CTLS_2G];
	u8 ctl_freqbin_2G[AR9300_NUM_CTLS_2G][AR9300_NUM_BAND_EDGES_2G];
	काष्ठा cal_ctl_data_2g ctlPowerData_2G[AR9300_NUM_CTLS_2G];
	काष्ठा ar9300_modal_eep_header modalHeader5G;
	काष्ठा ar9300_BaseExtension_2 base_ext2;
	u8 calFreqPier5G[AR9300_NUM_5G_CAL_PIERS];
	काष्ठा ar9300_cal_data_per_freq_op_loop
	 calPierData5G[AR9300_MAX_CHAINS][AR9300_NUM_5G_CAL_PIERS];
	u8 calTarget_freqbin_5G[AR9300_NUM_5G_20_TARGET_POWERS];
	u8 calTarget_freqbin_5GHT20[AR9300_NUM_5G_20_TARGET_POWERS];
	u8 calTarget_freqbin_5GHT40[AR9300_NUM_5G_40_TARGET_POWERS];
	काष्ठा cal_tgt_घात_legacy
	 calTargetPower5G[AR9300_NUM_5G_20_TARGET_POWERS];
	काष्ठा cal_tgt_घात_ht
	 calTargetPower5GHT20[AR9300_NUM_5G_20_TARGET_POWERS];
	काष्ठा cal_tgt_घात_ht
	 calTargetPower5GHT40[AR9300_NUM_5G_40_TARGET_POWERS];
	u8 ctlIndex_5G[AR9300_NUM_CTLS_5G];
	u8 ctl_freqbin_5G[AR9300_NUM_CTLS_5G][AR9300_NUM_BAND_EDGES_5G];
	काष्ठा cal_ctl_data_5g ctlPowerData_5G[AR9300_NUM_CTLS_5G];
पूर्ण __packed;

s32 ar9003_hw_get_tx_gain_idx(काष्ठा ath_hw *ah);
s32 ar9003_hw_get_rx_gain_idx(काष्ठा ath_hw *ah);
u32 ar9003_hw_ant_ctrl_common_get(काष्ठा ath_hw *ah, bool is2ghz);
u32 ar9003_hw_ant_ctrl_common_2_get(काष्ठा ath_hw *ah, bool is2ghz);

u8 *ar9003_get_spur_chan_ptr(काष्ठा ath_hw *ah, bool is_2ghz);

अचिन्हित पूर्णांक ar9003_get_paprd_scale_factor(काष्ठा ath_hw *ah,
					   काष्ठा ath9k_channel *chan);

व्योम ar9003_hw_पूर्णांकernal_regulator_apply(काष्ठा ath_hw *ah);
पूर्णांक ar9003_hw_tx_घातer_regग_लिखो(काष्ठा ath_hw *ah, u8 * pPwrArray);

#पूर्ण_अगर

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

#अगर_अघोषित EEPROM_H
#घोषणा EEPROM_H

#घोषणा AR_EEPROM_MODAL_SPURS   5

#समावेश "../ath.h"
#समावेश <net/cfg80211.h>
#समावेश "ar9003_eeprom.h"

/* helpers to swap EEPROM fields, which are stored as __le16 or __le32. Since
 * we are 100% sure about it we __क्रमce these to u16/u32 क्रम the swab calls to
 * silence the sparse checks. These macros are used when we have a Big Endian
 * EEPROM (according to AR5416_EEPMISC_BIG_ENDIAN) and need to convert the
 * fields to __le16/__le32.
 */
#घोषणा EEPROM_FIELD_SWAB16(field) \
	(field = (__क्रमce __le16)swab16((__क्रमce u16)field))
#घोषणा EEPROM_FIELD_SWAB32(field) \
	(field = (__क्रमce __le32)swab32((__क्रमce u32)field))

#अगर_घोषित __BIG_ENDIAN
#घोषणा AR5416_EEPROM_MAGIC 0x5aa5
#अन्यथा
#घोषणा AR5416_EEPROM_MAGIC 0xa55a
#पूर्ण_अगर

#घोषणा CTRY_DEBUG   0x1ff
#घोषणा	CTRY_DEFAULT 0

#घोषणा AR_EEPROM_EEPCAP_COMPRESS_DIS   0x0001
#घोषणा AR_EEPROM_EEPCAP_AES_DIS        0x0002
#घोषणा AR_EEPROM_EEPCAP_FASTFRAME_DIS  0x0004
#घोषणा AR_EEPROM_EEPCAP_BURST_DIS      0x0008
#घोषणा AR_EEPROM_EEPCAP_MAXQCU         0x01F0
#घोषणा AR_EEPROM_EEPCAP_MAXQCU_S       4
#घोषणा AR_EEPROM_EEPCAP_HEAVY_CLIP_EN  0x0200
#घोषणा AR_EEPROM_EEPCAP_KC_ENTRIES     0xF000
#घोषणा AR_EEPROM_EEPCAP_KC_ENTRIES_S   12

#घोषणा AR_EEPROM_EEREGCAP_EN_FCC_MIDBAND   0x0040
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_U1_EVEN    0x0080
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_U2         0x0100
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_MIDBAND    0x0200
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_U1_ODD     0x0400
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_NEW_11A    0x0800

#घोषणा AR_EEPROM_EEREGCAP_EN_KK_U1_ODD_PRE4_0  0x4000
#घोषणा AR_EEPROM_EEREGCAP_EN_KK_NEW_11A_PRE4_0 0x8000

#घोषणा AR5416_EEPROM_MAGIC_OFFSET  0x0
#घोषणा AR5416_EEPROM_S             2
#घोषणा AR5416_EEPROM_OFFSET        0x2000
#घोषणा AR5416_EEPROM_MAX           0xae0

#घोषणा AR5416_EEPROM_START_ADDR \
	(AR_SREV_9100(ah)) ? 0x1fff1000 : 0x503f1200

#घोषणा SD_NO_CTL               0xE0
#घोषणा NO_CTL                  0xff
#घोषणा CTL_MODE_M              0xf
#घोषणा CTL_11A                 0
#घोषणा CTL_11B                 1
#घोषणा CTL_11G                 2
#घोषणा CTL_2GHT20              5
#घोषणा CTL_5GHT20              6
#घोषणा CTL_2GHT40              7
#घोषणा CTL_5GHT40              8

#घोषणा EXT_ADDITIVE (0x8000)
#घोषणा CTL_11A_EXT (CTL_11A | EXT_ADDITIVE)
#घोषणा CTL_11G_EXT (CTL_11G | EXT_ADDITIVE)
#घोषणा CTL_11B_EXT (CTL_11B | EXT_ADDITIVE)

#घोषणा SUB_NUM_CTL_MODES_AT_5G_40 2
#घोषणा SUB_NUM_CTL_MODES_AT_2G_40 3

#घोषणा POWER_CORRECTION_FOR_TWO_CHAIN		6  /* 10*log10(2)*2 */
#घोषणा POWER_CORRECTION_FOR_THREE_CHAIN	10 /* 10*log10(3)*2 */

/*
 * For AR9285 and later chipsets, the following bits are not being programmed
 * in EEPROM and so need to be enabled always.
 *
 * Bit 0: en_fcc_mid
 * Bit 1: en_jap_mid
 * Bit 2: en_fcc_dfs_ht40
 * Bit 3: en_jap_ht40
 * Bit 4: en_jap_dfs_ht40
 */
#घोषणा AR9285_RDEXT_DEFAULT    0x1F

#घोषणा ATH9K_POW_SM(_r, _s)	(((_r) & 0x3f) << (_s))
#घोषणा FREQ2FBIN(x, y)		(u8)((y) ? ((x) - 2300) : (((x) - 4800) / 5))
#घोषणा FBIN2FREQ(x, y)		((y) ? (2300 + x) : (4800 + 5 * x))
#घोषणा ath9k_hw_use_flash(_ah)	(!(_ah->ah_flags & AH_USE_EEPROM))

#घोषणा OLC_FOR_AR9280_20_LATER (AR_SREV_9280_20_OR_LATER(ah) && \
				 ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL))
#घोषणा OLC_FOR_AR9287_10_LATER (AR_SREV_9287_11_OR_LATER(ah) && \
				 ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL))

#घोषणा EEP_RFSILENT_ENABLED        0x0001
#घोषणा EEP_RFSILENT_ENABLED_S      0
#घोषणा EEP_RFSILENT_POLARITY       0x0002
#घोषणा EEP_RFSILENT_POLARITY_S     1
#घोषणा EEP_RFSILENT_GPIO_SEL       ((AR_SREV_9462(ah) || AR_SREV_9565(ah)) ? 0x00fc : 0x001c)
#घोषणा EEP_RFSILENT_GPIO_SEL_S     2

#घोषणा AR5416_OPFLAGS_11A           0x01
#घोषणा AR5416_OPFLAGS_11G           0x02
#घोषणा AR5416_OPFLAGS_N_5G_HT40     0x04
#घोषणा AR5416_OPFLAGS_N_2G_HT40     0x08
#घोषणा AR5416_OPFLAGS_N_5G_HT20     0x10
#घोषणा AR5416_OPFLAGS_N_2G_HT20     0x20

#घोषणा AR5416_EEP_NO_BACK_VER       0x1
#घोषणा AR5416_EEP_VER               0xE
#घोषणा AR5416_EEP_VER_MAJOR_SHIFT   12
#घोषणा AR5416_EEP_VER_MAJOR_MASK    0xF000
#घोषणा AR5416_EEP_VER_MINOR_MASK    0x0FFF
#घोषणा AR5416_EEP_MINOR_VER_2       0x2
#घोषणा AR5416_EEP_MINOR_VER_3       0x3
#घोषणा AR5416_EEP_MINOR_VER_7       0x7
#घोषणा AR5416_EEP_MINOR_VER_9       0x9
#घोषणा AR5416_EEP_MINOR_VER_16      0x10
#घोषणा AR5416_EEP_MINOR_VER_17      0x11
#घोषणा AR5416_EEP_MINOR_VER_19      0x13
#घोषणा AR5416_EEP_MINOR_VER_20      0x14
#घोषणा AR5416_EEP_MINOR_VER_21      0x15
#घोषणा AR5416_EEP_MINOR_VER_22      0x16

#घोषणा AR5416_NUM_5G_CAL_PIERS         8
#घोषणा AR5416_NUM_2G_CAL_PIERS         4
#घोषणा AR5416_NUM_5G_20_TARGET_POWERS  8
#घोषणा AR5416_NUM_5G_40_TARGET_POWERS  8
#घोषणा AR5416_NUM_2G_CCK_TARGET_POWERS 3
#घोषणा AR5416_NUM_2G_20_TARGET_POWERS  4
#घोषणा AR5416_NUM_2G_40_TARGET_POWERS  4
#घोषणा AR5416_NUM_CTLS                 24
#घोषणा AR5416_NUM_BAND_EDGES           8
#घोषणा AR5416_NUM_PD_GAINS             4
#घोषणा AR5416_PD_GAINS_IN_MASK         4
#घोषणा AR5416_PD_GAIN_ICEPTS           5
#घोषणा AR5416_NUM_PDADC_VALUES         128
#घोषणा AR5416_BCHAN_UNUSED             0xFF
#घोषणा AR5416_MAX_PWR_RANGE_IN_HALF_DB 64
#घोषणा AR5416_MAX_CHAINS               3
#घोषणा AR9300_MAX_CHAINS		3
#घोषणा AR5416_PWR_TABLE_OFFSET_DB     -5

/* Rx gain type values */
#घोषणा AR5416_EEP_RXGAIN_23DB_BACKOFF     0
#घोषणा AR5416_EEP_RXGAIN_13DB_BACKOFF     1
#घोषणा AR5416_EEP_RXGAIN_ORIG             2

/* Tx gain type values */
#घोषणा AR5416_EEP_TXGAIN_ORIGINAL         0
#घोषणा AR5416_EEP_TXGAIN_HIGH_POWER       1

/* Endianness of EEPROM content */
#घोषणा AR5416_EEPMISC_BIG_ENDIAN          0x01

#घोषणा AR5416_EEP4K_START_LOC                64
#घोषणा AR5416_EEP4K_NUM_2G_CAL_PIERS         3
#घोषणा AR5416_EEP4K_NUM_2G_CCK_TARGET_POWERS 3
#घोषणा AR5416_EEP4K_NUM_2G_20_TARGET_POWERS  3
#घोषणा AR5416_EEP4K_NUM_2G_40_TARGET_POWERS  3
#घोषणा AR5416_EEP4K_NUM_CTLS                 12
#घोषणा AR5416_EEP4K_NUM_BAND_EDGES           4
#घोषणा AR5416_EEP4K_NUM_PD_GAINS             2
#घोषणा AR5416_EEP4K_MAX_CHAINS               1

#घोषणा AR9280_TX_GAIN_TABLE_SIZE 22

#घोषणा AR9287_EEP_VER               0xE
#घोषणा AR9287_EEP_MINOR_VER_1       0x1
#घोषणा AR9287_EEP_MINOR_VER_2       0x2
#घोषणा AR9287_EEP_MINOR_VER_3       0x3
#घोषणा AR9287_EEP_MINOR_VER         AR9287_EEP_MINOR_VER_3
#घोषणा AR9287_EEP_MINOR_VER_b       AR9287_EEP_MINOR_VER
#घोषणा AR9287_EEP_NO_BACK_VER       AR9287_EEP_MINOR_VER_1

#घोषणा AR9287_EEP_START_LOC            128
#घोषणा AR9287_HTC_EEP_START_LOC        256
#घोषणा AR9287_NUM_2G_CAL_PIERS         3
#घोषणा AR9287_NUM_2G_CCK_TARGET_POWERS 3
#घोषणा AR9287_NUM_2G_20_TARGET_POWERS  3
#घोषणा AR9287_NUM_2G_40_TARGET_POWERS  3
#घोषणा AR9287_NUM_CTLS              	12
#घोषणा AR9287_NUM_BAND_EDGES        	4
#घोषणा AR9287_PD_GAIN_ICEPTS           1
#घोषणा AR9287_EEPMISC_WOW              0x02
#घोषणा AR9287_MAX_CHAINS               2
#घोषणा AR9287_ANT_16S                  32

#घोषणा AR9287_DATA_SZ                  32

#घोषणा AR9287_PWR_TABLE_OFFSET_DB  -5

#घोषणा AR9287_CHECKSUM_LOCATION (AR9287_EEP_START_LOC + 1)

#घोषणा CTL_EDGE_TPOWER(_ctl) ((_ctl) & 0x3f)
#घोषणा CTL_EDGE_FLAGS(_ctl) (((_ctl) >> 6) & 0x03)

#घोषणा LNA_CTL_BUF_MODE	BIT(0)
#घोषणा LNA_CTL_ISEL_LO		BIT(1)
#घोषणा LNA_CTL_ISEL_HI		BIT(2)
#घोषणा LNA_CTL_BUF_IN		BIT(3)
#घोषणा LNA_CTL_FEM_BAND	BIT(4)
#घोषणा LNA_CTL_LOCAL_BIAS	BIT(5)
#घोषणा LNA_CTL_FORCE_XPA	BIT(6)
#घोषणा LNA_CTL_USE_ANT1	BIT(7)

क्रमागत eeprom_param अणु
	EEP_NFTHRESH_5,
	EEP_NFTHRESH_2,
	EEP_MAC_MSW,
	EEP_MAC_MID,
	EEP_MAC_LSW,
	EEP_REG_0,
	EEP_OP_CAP,
	EEP_OP_MODE,
	EEP_RF_SILENT,
	EEP_OB_5,
	EEP_DB_5,
	EEP_OB_2,
	EEP_DB_2,
	EEP_TX_MASK,
	EEP_RX_MASK,
	EEP_FSTCLK_5G,
	EEP_RXGAIN_TYPE,
	EEP_OL_PWRCTRL,
	EEP_TXGAIN_TYPE,
	EEP_RC_CHAIN_MASK,
	EEP_DAC_HPWR_5G,
	EEP_FRAC_N_5G,
	EEP_DEV_TYPE,
	EEP_TEMPSENSE_SLOPE,
	EEP_TEMPSENSE_SLOPE_PAL_ON,
	EEP_PWR_TABLE_OFFSET,
	EEP_PAPRD,
	EEP_MODAL_VER,
	EEP_ANT_DIV_CTL1,
	EEP_CHAIN_MASK_REDUCE,
	EEP_ANTENNA_GAIN_2G,
	EEP_ANTENNA_GAIN_5G,
पूर्ण;

क्रमागत ar5416_rates अणु
	rate6mb, rate9mb, rate12mb, rate18mb,
	rate24mb, rate36mb, rate48mb, rate54mb,
	rate1l, rate2l, rate2s, rate5_5l,
	rate5_5s, rate11l, rate11s, rateXr,
	rateHt20_0, rateHt20_1, rateHt20_2, rateHt20_3,
	rateHt20_4, rateHt20_5, rateHt20_6, rateHt20_7,
	rateHt40_0, rateHt40_1, rateHt40_2, rateHt40_3,
	rateHt40_4, rateHt40_5, rateHt40_6, rateHt40_7,
	rateDupCck, rateDupOfdm, rateExtCck, rateExtOfdm,
	Ar5416RateSize
पूर्ण;

क्रमागत ath9k_hal_freq_band अणु
	ATH9K_HAL_FREQ_BAND_5GHZ = 0,
	ATH9K_HAL_FREQ_BAND_2GHZ = 1
पूर्ण;

काष्ठा base_eep_header अणु
	__le16 length;
	__le16 checksum;
	__le16 version;
	u8 opCapFlags;
	u8 eepMisc;
	__le16 regDmn[2];
	u8 macAddr[6];
	u8 rxMask;
	u8 txMask;
	__le16 rfSilent;
	__le16 blueToothOptions;
	__le16 deviceCap;
	__le32 binBuildNumber;
	u8 deviceType;
	u8 pwdclkind;
	u8 fastClk5g;
	u8 भागChain;
	u8 rxGainType;
	u8 dacHiPwrMode_5G;
	u8 खोलोLoopPwrCntl;
	u8 dacLpMode;
	u8 txGainType;
	u8 rcChainMask;
	u8 desiredScaleCCK;
	u8 pwr_table_offset;
	u8 frac_n_5g;
	u8 futureBase_3[21];
पूर्ण __packed;

काष्ठा base_eep_header_4k अणु
	__le16 length;
	__le16 checksum;
	__le16 version;
	u8 opCapFlags;
	u8 eepMisc;
	__le16 regDmn[2];
	u8 macAddr[6];
	u8 rxMask;
	u8 txMask;
	__le16 rfSilent;
	__le16 blueToothOptions;
	__le16 deviceCap;
	__le32 binBuildNumber;
	u8 deviceType;
	u8 txGainType;
पूर्ण __packed;


काष्ठा spur_chan अणु
	__le16 spurChan;
	u8 spurRangeLow;
	u8 spurRangeHigh;
पूर्ण __packed;

काष्ठा modal_eep_header अणु
	__le32 antCtrlChain[AR5416_MAX_CHAINS];
	__le32 antCtrlCommon;
	u8 antennaGainCh[AR5416_MAX_CHAINS];
	u8 चयनSettling;
	u8 txRxAttenCh[AR5416_MAX_CHAINS];
	u8 rxTxMarginCh[AR5416_MAX_CHAINS];
	u8 adcDesiredSize;
	u8 pgaDesiredSize;
	u8 xlnaGainCh[AR5416_MAX_CHAINS];
	u8 txEndToXpaOff;
	u8 txEndToRxOn;
	u8 txFrameToXpaOn;
	u8 thresh62;
	u8 noiseFloorThreshCh[AR5416_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	u8 iqCalICh[AR5416_MAX_CHAINS];
	u8 iqCalQCh[AR5416_MAX_CHAINS];
	u8 pdGainOverlap;
	u8 ob;
	u8 db;
	u8 xpaBiasLvl;
	u8 pwrDecreaseFor2Chain;
	u8 pwrDecreaseFor3Chain;
	u8 txFrameToDataStart;
	u8 txFrameToPaOn;
	u8 ht40PowerIncForPdadc;
	u8 bswAtten[AR5416_MAX_CHAINS];
	u8 bswMargin[AR5416_MAX_CHAINS];
	u8 swSettleHt40;
	u8 xatten2Db[AR5416_MAX_CHAINS];
	u8 xatten2Margin[AR5416_MAX_CHAINS];
	u8 ob_ch1;
	u8 db_ch1;
	u8 lna_ctl;
	u8 miscBits;
	__le16 xpaBiasLvlFreq[3];
	u8 futureModal[6];

	काष्ठा spur_chan spurChans[AR_EEPROM_MODAL_SPURS];
पूर्ण __packed;

काष्ठा calDataPerFreqOpLoop अणु
	u8 pwrPdg[2][5];
	u8 vpdPdg[2][5];
	u8 pcdac[2][5];
	u8 empty[2][5];
पूर्ण __packed;

काष्ठा modal_eep_4k_header अणु
	__le32 antCtrlChain[AR5416_EEP4K_MAX_CHAINS];
	__le32 antCtrlCommon;
	u8 antennaGainCh[AR5416_EEP4K_MAX_CHAINS];
	u8 चयनSettling;
	u8 txRxAttenCh[AR5416_EEP4K_MAX_CHAINS];
	u8 rxTxMarginCh[AR5416_EEP4K_MAX_CHAINS];
	u8 adcDesiredSize;
	u8 pgaDesiredSize;
	u8 xlnaGainCh[AR5416_EEP4K_MAX_CHAINS];
	u8 txEndToXpaOff;
	u8 txEndToRxOn;
	u8 txFrameToXpaOn;
	u8 thresh62;
	u8 noiseFloorThreshCh[AR5416_EEP4K_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	u8 iqCalICh[AR5416_EEP4K_MAX_CHAINS];
	u8 iqCalQCh[AR5416_EEP4K_MAX_CHAINS];
	u8 pdGainOverlap;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u8 ob_1:4, ob_0:4;
	u8 db1_1:4, db1_0:4;
#अन्यथा
	u8 ob_0:4, ob_1:4;
	u8 db1_0:4, db1_1:4;
#पूर्ण_अगर
	u8 xpaBiasLvl;
	u8 txFrameToDataStart;
	u8 txFrameToPaOn;
	u8 ht40PowerIncForPdadc;
	u8 bswAtten[AR5416_EEP4K_MAX_CHAINS];
	u8 bswMargin[AR5416_EEP4K_MAX_CHAINS];
	u8 swSettleHt40;
	u8 xatten2Db[AR5416_EEP4K_MAX_CHAINS];
	u8 xatten2Margin[AR5416_EEP4K_MAX_CHAINS];
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u8 db2_1:4, db2_0:4;
#अन्यथा
	u8 db2_0:4, db2_1:4;
#पूर्ण_अगर
	u8 version;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u8 ob_3:4, ob_2:4;
	u8 antभाग_ctl1:4, ob_4:4;
	u8 db1_3:4, db1_2:4;
	u8 antभाग_ctl2:4, db1_4:4;
	u8 db2_2:4, db2_3:4;
	u8 reserved:4, db2_4:4;
#अन्यथा
	u8 ob_2:4, ob_3:4;
	u8 ob_4:4, antभाग_ctl1:4;
	u8 db1_2:4, db1_3:4;
	u8 db1_4:4, antभाग_ctl2:4;
	u8 db2_2:4, db2_3:4;
	u8 db2_4:4, reserved:4;
#पूर्ण_अगर
	u8 tx_भागersity;
	u8 flc_pwr_thresh;
	u8 bb_scale_smrt_antenna;
#घोषणा EEP_4K_BB_DESIRED_SCALE_MASK	0x1f
	u8 futureModal[1];
	काष्ठा spur_chan spurChans[AR_EEPROM_MODAL_SPURS];
पूर्ण __packed;

काष्ठा base_eep_ar9287_header अणु
	__le16 length;
	__le16 checksum;
	__le16 version;
	u8 opCapFlags;
	u8 eepMisc;
	__le16 regDmn[2];
	u8 macAddr[6];
	u8 rxMask;
	u8 txMask;
	__le16 rfSilent;
	__le16 blueToothOptions;
	__le16 deviceCap;
	__le32 binBuildNumber;
	u8 deviceType;
	u8 खोलोLoopPwrCntl;
	पूर्णांक8_t pwrTableOffset;
	पूर्णांक8_t tempSensSlope;
	पूर्णांक8_t tempSensSlopePalOn;
	u8 futureBase[29];
पूर्ण __packed;

काष्ठा modal_eep_ar9287_header अणु
	__le32 antCtrlChain[AR9287_MAX_CHAINS];
	__le32 antCtrlCommon;
	पूर्णांक8_t antennaGainCh[AR9287_MAX_CHAINS];
	u8 चयनSettling;
	u8 txRxAttenCh[AR9287_MAX_CHAINS];
	u8 rxTxMarginCh[AR9287_MAX_CHAINS];
	पूर्णांक8_t adcDesiredSize;
	u8 txEndToXpaOff;
	u8 txEndToRxOn;
	u8 txFrameToXpaOn;
	u8 thresh62;
	पूर्णांक8_t noiseFloorThreshCh[AR9287_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	पूर्णांक8_t iqCalICh[AR9287_MAX_CHAINS];
	पूर्णांक8_t iqCalQCh[AR9287_MAX_CHAINS];
	u8 pdGainOverlap;
	u8 xpaBiasLvl;
	u8 txFrameToDataStart;
	u8 txFrameToPaOn;
	u8 ht40PowerIncForPdadc;
	u8 bswAtten[AR9287_MAX_CHAINS];
	u8 bswMargin[AR9287_MAX_CHAINS];
	u8 swSettleHt40;
	u8 version;
	u8 db1;
	u8 db2;
	u8 ob_cck;
	u8 ob_psk;
	u8 ob_qam;
	u8 ob_pal_off;
	u8 futureModal[30];
	काष्ठा spur_chan spurChans[AR_EEPROM_MODAL_SPURS];
पूर्ण __packed;

काष्ठा cal_data_per_freq अणु
	u8 pwrPdg[AR5416_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
	u8 vpdPdg[AR5416_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
पूर्ण __packed;

काष्ठा cal_data_per_freq_4k अणु
	u8 pwrPdg[AR5416_EEP4K_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
	u8 vpdPdg[AR5416_EEP4K_NUM_PD_GAINS][AR5416_PD_GAIN_ICEPTS];
पूर्ण __packed;

काष्ठा cal_target_घातer_leg अणु
	u8 bChannel;
	u8 tPow2x[4];
पूर्ण __packed;

काष्ठा cal_target_घातer_ht अणु
	u8 bChannel;
	u8 tPow2x[8];
पूर्ण __packed;

काष्ठा cal_ctl_edges अणु
	u8 bChannel;
	u8 ctl;
पूर्ण __packed;

काष्ठा cal_data_op_loop_ar9287 अणु
	u8 pwrPdg[2][5];
	u8 vpdPdg[2][5];
	u8 pcdac[2][5];
	u8 empty[2][5];
पूर्ण __packed;

काष्ठा cal_data_per_freq_ar9287 अणु
	u8 pwrPdg[AR5416_NUM_PD_GAINS][AR9287_PD_GAIN_ICEPTS];
	u8 vpdPdg[AR5416_NUM_PD_GAINS][AR9287_PD_GAIN_ICEPTS];
पूर्ण __packed;

जोड़ cal_data_per_freq_ar9287_u अणु
	काष्ठा cal_data_op_loop_ar9287 calDataOpen;
	काष्ठा cal_data_per_freq_ar9287 calDataClose;
पूर्ण __packed;

काष्ठा cal_ctl_data_ar9287 अणु
	काष्ठा cal_ctl_edges
	ctlEdges[AR9287_MAX_CHAINS][AR9287_NUM_BAND_EDGES];
पूर्ण __packed;

काष्ठा cal_ctl_data अणु
	काष्ठा cal_ctl_edges
	ctlEdges[AR5416_MAX_CHAINS][AR5416_NUM_BAND_EDGES];
पूर्ण __packed;

काष्ठा cal_ctl_data_4k अणु
	काष्ठा cal_ctl_edges
	ctlEdges[AR5416_EEP4K_MAX_CHAINS][AR5416_EEP4K_NUM_BAND_EDGES];
पूर्ण __packed;

काष्ठा ar5416_eeprom_def अणु
	काष्ठा base_eep_header baseEepHeader;
	u8 custData[64];
	काष्ठा modal_eep_header modalHeader[2];
	u8 calFreqPier5G[AR5416_NUM_5G_CAL_PIERS];
	u8 calFreqPier2G[AR5416_NUM_2G_CAL_PIERS];
	काष्ठा cal_data_per_freq
	 calPierData5G[AR5416_MAX_CHAINS][AR5416_NUM_5G_CAL_PIERS];
	काष्ठा cal_data_per_freq
	 calPierData2G[AR5416_MAX_CHAINS][AR5416_NUM_2G_CAL_PIERS];
	काष्ठा cal_target_घातer_leg
	 calTargetPower5G[AR5416_NUM_5G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	 calTargetPower5GHT20[AR5416_NUM_5G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	 calTargetPower5GHT40[AR5416_NUM_5G_40_TARGET_POWERS];
	काष्ठा cal_target_घातer_leg
	 calTargetPowerCck[AR5416_NUM_2G_CCK_TARGET_POWERS];
	काष्ठा cal_target_घातer_leg
	 calTargetPower2G[AR5416_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	 calTargetPower2GHT20[AR5416_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	 calTargetPower2GHT40[AR5416_NUM_2G_40_TARGET_POWERS];
	u8 ctlIndex[AR5416_NUM_CTLS];
	काष्ठा cal_ctl_data ctlData[AR5416_NUM_CTLS];
	u8 padding;
पूर्ण __packed;

काष्ठा ar5416_eeprom_4k अणु
	काष्ठा base_eep_header_4k baseEepHeader;
	u8 custData[20];
	काष्ठा modal_eep_4k_header modalHeader;
	u8 calFreqPier2G[AR5416_EEP4K_NUM_2G_CAL_PIERS];
	काष्ठा cal_data_per_freq_4k
	calPierData2G[AR5416_EEP4K_MAX_CHAINS][AR5416_EEP4K_NUM_2G_CAL_PIERS];
	काष्ठा cal_target_घातer_leg
	calTargetPowerCck[AR5416_EEP4K_NUM_2G_CCK_TARGET_POWERS];
	काष्ठा cal_target_घातer_leg
	calTargetPower2G[AR5416_EEP4K_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	calTargetPower2GHT20[AR5416_EEP4K_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	calTargetPower2GHT40[AR5416_EEP4K_NUM_2G_40_TARGET_POWERS];
	u8 ctlIndex[AR5416_EEP4K_NUM_CTLS];
	काष्ठा cal_ctl_data_4k ctlData[AR5416_EEP4K_NUM_CTLS];
	u8 padding;
पूर्ण __packed;

काष्ठा ar9287_eeprom अणु
	काष्ठा base_eep_ar9287_header baseEepHeader;
	u8 custData[AR9287_DATA_SZ];
	काष्ठा modal_eep_ar9287_header modalHeader;
	u8 calFreqPier2G[AR9287_NUM_2G_CAL_PIERS];
	जोड़ cal_data_per_freq_ar9287_u
	calPierData2G[AR9287_MAX_CHAINS][AR9287_NUM_2G_CAL_PIERS];
	काष्ठा cal_target_घातer_leg
	calTargetPowerCck[AR9287_NUM_2G_CCK_TARGET_POWERS];
	काष्ठा cal_target_घातer_leg
	calTargetPower2G[AR9287_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	calTargetPower2GHT20[AR9287_NUM_2G_20_TARGET_POWERS];
	काष्ठा cal_target_घातer_ht
	calTargetPower2GHT40[AR9287_NUM_2G_40_TARGET_POWERS];
	u8 ctlIndex[AR9287_NUM_CTLS];
	काष्ठा cal_ctl_data_ar9287 ctlData[AR9287_NUM_CTLS];
	u8 padding;
पूर्ण __packed;

क्रमागत reg_ext_biपंचांगap अणु
	REG_EXT_FCC_MIDBAND = 0,
	REG_EXT_JAPAN_MIDBAND = 1,
	REG_EXT_FCC_DFS_HT40 = 2,
	REG_EXT_JAPAN_NONDFS_HT40 = 3,
	REG_EXT_JAPAN_DFS_HT40 = 4
पूर्ण;

काष्ठा ath9k_country_entry अणु
	u16 countryCode;
	u16 regDmnEnum;
	u16 regDmn5G;
	u16 regDmn2G;
	u8 isMultiकरोमुख्य;
	u8 iso[3];
पूर्ण;

काष्ठा eeprom_ops अणु
	पूर्णांक (*check_eeprom)(काष्ठा ath_hw *hw);
	u32 (*get_eeprom)(काष्ठा ath_hw *hw, क्रमागत eeprom_param param);
	bool (*fill_eeprom)(काष्ठा ath_hw *hw);
	u32 (*dump_eeprom)(काष्ठा ath_hw *hw, bool dump_base_hdr, u8 *buf,
			   u32 len, u32 size);
	पूर्णांक (*get_eeprom_ver)(काष्ठा ath_hw *hw);
	पूर्णांक (*get_eeprom_rev)(काष्ठा ath_hw *hw);
	व्योम (*set_board_values)(काष्ठा ath_hw *hw, काष्ठा ath9k_channel *chan);
	व्योम (*set_addac)(काष्ठा ath_hw *hw, काष्ठा ath9k_channel *chan);
	व्योम (*set_txघातer)(काष्ठा ath_hw *hw, काष्ठा ath9k_channel *chan,
			   u16 cfgCtl, u8 twiceAntennaReduction,
			   u8 घातerLimit, bool test);
	u16 (*get_spur_channel)(काष्ठा ath_hw *ah, u16 i, bool is2GHz);
	u8 (*get_eepmisc)(काष्ठा ath_hw *ah);
पूर्ण;

व्योम ath9k_hw_analog_shअगरt_regग_लिखो(काष्ठा ath_hw *ah, u32 reg, u32 val);
व्योम ath9k_hw_analog_shअगरt_rmw(काष्ठा ath_hw *ah, u32 reg, u32 mask,
			       u32 shअगरt, u32 val);
पूर्णांक16_t ath9k_hw_पूर्णांकerpolate(u16 target, u16 srcLeft, u16 srcRight,
			     पूर्णांक16_t targetLeft,
			     पूर्णांक16_t targetRight);
bool ath9k_hw_get_lower_upper_index(u8 target, u8 *pList, u16 listSize,
				    u16 *indexL, u16 *indexR);
bool ath9k_hw_nvram_पढ़ो(काष्ठा ath_hw *ah, u32 off, u16 *data);
पूर्णांक ath9k_hw_nvram_swap_data(काष्ठा ath_hw *ah, bool *swap_needed, पूर्णांक size);
bool ath9k_hw_nvram_validate_checksum(काष्ठा ath_hw *ah, पूर्णांक size);
bool ath9k_hw_nvram_check_version(काष्ठा ath_hw *ah, पूर्णांक version, पूर्णांक minrev);
व्योम ath9k_hw_usb_gen_fill_eeprom(काष्ठा ath_hw *ah, u16 *eep_data,
				  पूर्णांक eep_start_loc, पूर्णांक size);
व्योम ath9k_hw_fill_vpd_table(u8 pwrMin, u8 pwrMax, u8 *pPwrList,
			     u8 *pVpdList, u16 numIntercepts,
			     u8 *pRetVpdList);
व्योम ath9k_hw_get_legacy_target_घातers(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan,
				       काष्ठा cal_target_घातer_leg *घातInfo,
				       u16 numChannels,
				       काष्ठा cal_target_घातer_leg *pNewPower,
				       u16 numRates, bool isExtTarget);
व्योम ath9k_hw_get_target_घातers(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan,
				काष्ठा cal_target_घातer_ht *घातInfo,
				u16 numChannels,
				काष्ठा cal_target_घातer_ht *pNewPower,
				u16 numRates, bool isHt40Target);
u16 ath9k_hw_get_max_edge_घातer(u16 freq, काष्ठा cal_ctl_edges *pRdEdgesPower,
				bool is2GHz, पूर्णांक num_band_edges);
u16 ath9k_hw_get_scaled_घातer(काष्ठा ath_hw *ah, u16 घातer_limit,
			      u8 antenna_reduction);
व्योम ath9k_hw_update_regulatory_maxघातer(काष्ठा ath_hw *ah);
पूर्णांक ath9k_hw_eeprom_init(काष्ठा ath_hw *ah);

व्योम ath9k_hw_get_gain_boundaries_pdadcs(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan,
				व्योम *pRawDataSet,
				u8 *bChans, u16 availPiers,
				u16 tPdGainOverlap,
				u16 *pPdGainBoundaries, u8 *pPDADCValues,
				u16 numXpdGains);

अटल अंतरभूत u16 ath9k_hw_fbin2freq(u8 fbin, bool is2GHz)
अणु
	अगर (fbin == AR5416_BCHAN_UNUSED)
		वापस fbin;

	वापस (u16) ((is2GHz) ? (2300 + fbin) : (4800 + 5 * fbin));
पूर्ण

#घोषणा ar5416_get_ntxchains(_txchainmask)			\
	(((_txchainmask >> 2) & 1) +                            \
	 ((_txchainmask >> 1) & 1) + (_txchainmask & 1))

बाह्य स्थिर काष्ठा eeprom_ops eep_def_ops;
बाह्य स्थिर काष्ठा eeprom_ops eep_4k_ops;
बाह्य स्थिर काष्ठा eeprom_ops eep_ar9287_ops;
बाह्य स्थिर काष्ठा eeprom_ops eep_ar9287_ops;
बाह्य स्थिर काष्ठा eeprom_ops eep_ar9300_ops;

#पूर्ण_अगर /* EEPROM_H */

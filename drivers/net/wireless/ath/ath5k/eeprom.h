<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
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

/*
 * Common ar5xxx EEPROM data offsets (set these on AR5K_EEPROM_BASE)
 */
#घोषणा	AR5K_EEPROM_PCIE_OFFSET		0x02	/* Contains offset to PCI-E infos */
#घोषणा	AR5K_EEPROM_PCIE_SERDES_SECTION	0x40	/* PCIE_OFFSET poपूर्णांकs here when
						 * SERDES infos are present */
#घोषणा AR5K_EEPROM_MAGIC		0x003d	/* EEPROM Magic number */
#घोषणा AR5K_EEPROM_MAGIC_VALUE		0x5aa5	/* Default - found on EEPROM */

#घोषणा	AR5K_EEPROM_IS_HB63		0x000b	/* Talon detect */

#घोषणा AR5K_EEPROM_RFKILL		0x0f
#घोषणा AR5K_EEPROM_RFKILL_GPIO_SEL	0x0000001c
#घोषणा AR5K_EEPROM_RFKILL_GPIO_SEL_S	2
#घोषणा AR5K_EEPROM_RFKILL_POLARITY	0x00000002
#घोषणा AR5K_EEPROM_RFKILL_POLARITY_S	1

#घोषणा AR5K_EEPROM_REG_DOMAIN		0x00bf	/* EEPROM regकरोm */

/* FLASH(EEPROM) Defines क्रम AR531X chips */
#घोषणा AR5K_EEPROM_SIZE_LOWER		0x1b /* size info -- lower */
#घोषणा AR5K_EEPROM_SIZE_UPPER		0x1c /* size info -- upper */
#घोषणा AR5K_EEPROM_SIZE_UPPER_MASK	0xfff0
#घोषणा AR5K_EEPROM_SIZE_UPPER_SHIFT	4
#घोषणा AR5K_EEPROM_SIZE_ENDLOC_SHIFT	12

#घोषणा AR5K_EEPROM_CHECKSUM		0x00c0	/* EEPROM checksum */
#घोषणा AR5K_EEPROM_INFO_BASE		0x00c0	/* EEPROM header */
#घोषणा AR5K_EEPROM_INFO_MAX		(0x400 - AR5K_EEPROM_INFO_BASE)
#घोषणा AR5K_EEPROM_INFO_CKSUM		0xffff
#घोषणा AR5K_EEPROM_INFO(_n)		(AR5K_EEPROM_INFO_BASE + (_n))

#घोषणा AR5K_EEPROM_VERSION		AR5K_EEPROM_INFO(1)	/* EEPROM Version */
#घोषणा AR5K_EEPROM_VERSION_3_0		0x3000	/* No idea what's going on beक्रमe this version */
#घोषणा AR5K_EEPROM_VERSION_3_1		0x3001	/* ob/db values क्रम 2GHz (ar5211_rfregs) */
#घोषणा AR5K_EEPROM_VERSION_3_2		0x3002	/* dअगरferent frequency representation (eeprom_bin2freq) */
#घोषणा AR5K_EEPROM_VERSION_3_3		0x3003	/* offsets changed, has 32 CTLs (see below) and ee_false_detect (eeprom_पढ़ो_modes) */
#घोषणा AR5K_EEPROM_VERSION_3_4		0x3004	/* has ee_i_gain, ee_cck_ofdm_घातer_delta (eeprom_पढ़ो_modes) */
#घोषणा AR5K_EEPROM_VERSION_4_0		0x4000	/* has ee_misc, ee_cal_pier, ee_turbo_max_घातer and ee_xr_घातer (eeprom_init) */
#घोषणा AR5K_EEPROM_VERSION_4_1		0x4001	/* has ee_margin_tx_rx (eeprom_init) */
#घोषणा AR5K_EEPROM_VERSION_4_2		0x4002	/* has ee_cck_ofdm_gain_delta (eeprom_init) */
#घोषणा AR5K_EEPROM_VERSION_4_3		0x4003	/* घातer calibration changes */
#घोषणा AR5K_EEPROM_VERSION_4_4		0x4004
#घोषणा AR5K_EEPROM_VERSION_4_5		0x4005
#घोषणा AR5K_EEPROM_VERSION_4_6		0x4006	/* has ee_scaled_cck_delta */
#घोषणा AR5K_EEPROM_VERSION_4_7		0x3007	/* 4007 ? */
#घोषणा AR5K_EEPROM_VERSION_4_9		0x4009	/* EAR futureproofing */
#घोषणा AR5K_EEPROM_VERSION_5_0		0x5000	/* Has 2413 PDADC calibration etc */
#घोषणा AR5K_EEPROM_VERSION_5_1		0x5001	/* Has capability values */
#घोषणा AR5K_EEPROM_VERSION_5_3		0x5003	/* Has spur mitigation tables */

#घोषणा AR5K_EEPROM_MODE_11A		0
#घोषणा AR5K_EEPROM_MODE_11B		1
#घोषणा AR5K_EEPROM_MODE_11G		2

#घोषणा AR5K_EEPROM_HDR			AR5K_EEPROM_INFO(2)	/* Header that contains the device caps */
#घोषणा AR5K_EEPROM_HDR_11A(_v)		(((_v) >> AR5K_EEPROM_MODE_11A) & 0x1)
#घोषणा AR5K_EEPROM_HDR_11B(_v)		(((_v) >> AR5K_EEPROM_MODE_11B) & 0x1)
#घोषणा AR5K_EEPROM_HDR_11G(_v)		(((_v) >> AR5K_EEPROM_MODE_11G) & 0x1)
#घोषणा AR5K_EEPROM_HDR_T_2GHZ_DIS(_v)	(((_v) >> 3) & 0x1)	/* Disable turbo क्रम 2GHz */
#घोषणा AR5K_EEPROM_HDR_T_5GHZ_DBM(_v)	(((_v) >> 4) & 0x7f)	/* Max turbo घातer क्रम < 2W घातer consumption */
#घोषणा AR5K_EEPROM_HDR_DEVICE(_v)	(((_v) >> 11) & 0x7)	/* Device type (1 Cardbus, 2 PCI, 3 MiniPCI, 4 AP) */
#घोषणा AR5K_EEPROM_HDR_RFKILL(_v)	(((_v) >> 14) & 0x1)	/* Device has RFKill support */
#घोषणा AR5K_EEPROM_HDR_T_5GHZ_DIS(_v)	(((_v) >> 15) & 0x1)	/* Disable turbo क्रम 5GHz */

/* Newer EEPROMs are using a dअगरferent offset */
#घोषणा AR5K_EEPROM_OFF(_v, _v3_0, _v3_3) \
	(((_v) >= AR5K_EEPROM_VERSION_3_3) ? _v3_3 : _v3_0)

#घोषणा AR5K_EEPROM_ANT_GAIN(_v)	AR5K_EEPROM_OFF(_v, 0x00c4, 0x00c3)
#घोषणा AR5K_EEPROM_ANT_GAIN_5GHZ(_v)	((s8)(((_v) >> 8) & 0xff))
#घोषणा AR5K_EEPROM_ANT_GAIN_2GHZ(_v)	((s8)((_v) & 0xff))

/* Misc values available since EEPROM 4.0 */
#घोषणा AR5K_EEPROM_MISC0		AR5K_EEPROM_INFO(4)
#घोषणा AR5K_EEPROM_EARSTART(_v)	((_v) & 0xfff)
#घोषणा AR5K_EEPROM_HDR_XR2_DIS(_v)	(((_v) >> 12) & 0x1)
#घोषणा AR5K_EEPROM_HDR_XR5_DIS(_v)	(((_v) >> 13) & 0x1)
#घोषणा AR5K_EEPROM_EEMAP(_v)		(((_v) >> 14) & 0x3)

#घोषणा AR5K_EEPROM_MISC1			AR5K_EEPROM_INFO(5)
#घोषणा AR5K_EEPROM_TARGET_PWRSTART(_v)		((_v) & 0xfff)
#घोषणा AR5K_EEPROM_HAS32KHZCRYSTAL(_v)		(((_v) >> 14) & 0x1)	/* has 32KHz crystal क्रम sleep mode */
#घोषणा AR5K_EEPROM_HAS32KHZCRYSTAL_OLD(_v)	(((_v) >> 15) & 0x1)

#घोषणा AR5K_EEPROM_MISC2			AR5K_EEPROM_INFO(6)
#घोषणा AR5K_EEPROM_EEP_खाता_VERSION(_v)	(((_v) >> 8) & 0xff)
#घोषणा AR5K_EEPROM_EAR_खाता_VERSION(_v)	((_v) & 0xff)

#घोषणा AR5K_EEPROM_MISC3		AR5K_EEPROM_INFO(7)
#घोषणा AR5K_EEPROM_ART_BUILD_NUM(_v)	(((_v) >> 10) & 0x3f)
#घोषणा AR5K_EEPROM_EAR_खाता_ID(_v)	((_v) & 0xff)

#घोषणा AR5K_EEPROM_MISC4		AR5K_EEPROM_INFO(8)
#घोषणा AR5K_EEPROM_CAL_DATA_START(_v)	(((_v) >> 4) & 0xfff)
#घोषणा AR5K_EEPROM_MASK_R0(_v)		(((_v) >> 2) & 0x3)	/* modes supported by radio 0 (bit 1: G, bit 2: A) */
#घोषणा AR5K_EEPROM_MASK_R1(_v)		((_v) & 0x3)		/* modes supported by radio 1 (bit 1: G, bit 2: A) */

#घोषणा AR5K_EEPROM_MISC5		AR5K_EEPROM_INFO(9)
#घोषणा AR5K_EEPROM_COMP_DIS(_v)	((_v) & 0x1)		/* disable compression */
#घोषणा AR5K_EEPROM_AES_DIS(_v)		(((_v) >> 1) & 0x1)	/* disable AES */
#घोषणा AR5K_EEPROM_FF_DIS(_v)		(((_v) >> 2) & 0x1)	/* disable fast frames */
#घोषणा AR5K_EEPROM_BURST_DIS(_v)	(((_v) >> 3) & 0x1)	/* disable bursting */
#घोषणा AR5K_EEPROM_MAX_QCU(_v)		(((_v) >> 4) & 0xf)	/* max number of QCUs. शेषs to 10 */
#घोषणा AR5K_EEPROM_HEAVY_CLIP_EN(_v)	(((_v) >> 8) & 0x1)	/* enable heavy clipping */
#घोषणा AR5K_EEPROM_KEY_CACHE_SIZE(_v)	(((_v) >> 12) & 0xf)	/* key cache size. शेषs to 128 */

#घोषणा AR5K_EEPROM_MISC6		AR5K_EEPROM_INFO(10)
#घोषणा AR5K_EEPROM_TX_CHAIN_DIS	((_v) & 0x7)		/* MIMO chains disabled क्रम TX biपंचांगask */
#घोषणा AR5K_EEPROM_RX_CHAIN_DIS	(((_v) >> 3) & 0x7)	/* MIMO chains disabled क्रम RX biपंचांगask */
#घोषणा AR5K_EEPROM_FCC_MID_EN		(((_v) >> 6) & 0x1)	/* 5.47-5.7GHz supported */
#घोषणा AR5K_EEPROM_JAP_U1EVEN_EN	(((_v) >> 7) & 0x1)	/* Japan UNII1 band (5.15-5.25GHz) on even channels (5180, 5200, 5220, 5240) supported */
#घोषणा AR5K_EEPROM_JAP_U2_EN		(((_v) >> 8) & 0x1)	/* Japan UNII2 band (5.25-5.35GHz) supported */
#घोषणा AR5K_EEPROM_JAP_MID_EN		(((_v) >> 9) & 0x1)	/* Japan band from 5.47-5.7GHz supported */
#घोषणा AR5K_EEPROM_JAP_U1ODD_EN	(((_v) >> 10) & 0x1)	/* Japan UNII2 band (5.15-5.25GHz) on odd channels (5170, 5190, 5210, 5230) supported */
#घोषणा AR5K_EEPROM_JAP_11A_NEW_EN	(((_v) >> 11) & 0x1)	/* Japan A mode enabled (using even channels) */

/* calibration settings */
#घोषणा AR5K_EEPROM_MODES_11A(_v)	AR5K_EEPROM_OFF(_v, 0x00c5, 0x00d4)
#घोषणा AR5K_EEPROM_MODES_11B(_v)	AR5K_EEPROM_OFF(_v, 0x00d0, 0x00f2)
#घोषणा AR5K_EEPROM_MODES_11G(_v)	AR5K_EEPROM_OFF(_v, 0x00da, 0x010d)
#घोषणा AR5K_EEPROM_CTL(_v)		AR5K_EEPROM_OFF(_v, 0x00e4, 0x0128)	/* Conक्रमmance test limits */
#घोषणा AR5K_EEPROM_GROUPS_START(_v)	AR5K_EEPROM_OFF(_v, 0x0100, 0x0150)	/* Start of Groups */
#घोषणा AR5K_EEPROM_GROUP1_OFFSET	0x0
#घोषणा AR5K_EEPROM_GROUP2_OFFSET	0x5
#घोषणा AR5K_EEPROM_GROUP3_OFFSET	0x37
#घोषणा AR5K_EEPROM_GROUP4_OFFSET	0x46
#घोषणा AR5K_EEPROM_GROUP5_OFFSET	0x55
#घोषणा AR5K_EEPROM_GROUP6_OFFSET	0x65
#घोषणा AR5K_EEPROM_GROUP7_OFFSET	0x69
#घोषणा AR5K_EEPROM_GROUP8_OFFSET	0x6f

#घोषणा AR5K_EEPROM_TARGET_PWR_OFF_11A(_v)	AR5K_EEPROM_OFF(_v, AR5K_EEPROM_GROUPS_START(_v) + \
								AR5K_EEPROM_GROUP5_OFFSET, 0x0000)
#घोषणा AR5K_EEPROM_TARGET_PWR_OFF_11B(_v)	AR5K_EEPROM_OFF(_v, AR5K_EEPROM_GROUPS_START(_v) + \
								AR5K_EEPROM_GROUP6_OFFSET, 0x0010)
#घोषणा AR5K_EEPROM_TARGET_PWR_OFF_11G(_v)	AR5K_EEPROM_OFF(_v, AR5K_EEPROM_GROUPS_START(_v) + \
								AR5K_EEPROM_GROUP7_OFFSET, 0x0014)

/* [3.1 - 3.3] */
#घोषणा AR5K_EEPROM_OBDB0_2GHZ		0x00ec
#घोषणा AR5K_EEPROM_OBDB1_2GHZ		0x00ed

#घोषणा AR5K_EEPROM_PROTECT		0x003f	/* EEPROM protect status */
#घोषणा AR5K_EEPROM_PROTECT_RD_0_31	0x0001	/* Read protection bit क्रम offsets 0x0 - 0x1f */
#घोषणा AR5K_EEPROM_PROTECT_WR_0_31	0x0002	/* Write protection bit क्रम offsets 0x0 - 0x1f */
#घोषणा AR5K_EEPROM_PROTECT_RD_32_63	0x0004	/* 0x20 - 0x3f */
#घोषणा AR5K_EEPROM_PROTECT_WR_32_63	0x0008
#घोषणा AR5K_EEPROM_PROTECT_RD_64_127	0x0010	/* 0x40 - 0x7f */
#घोषणा AR5K_EEPROM_PROTECT_WR_64_127	0x0020
#घोषणा AR5K_EEPROM_PROTECT_RD_128_191	0x0040	/* 0x80 - 0xbf (regकरोm) */
#घोषणा AR5K_EEPROM_PROTECT_WR_128_191	0x0080
#घोषणा AR5K_EEPROM_PROTECT_RD_192_207	0x0100	/* 0xc0 - 0xcf */
#घोषणा AR5K_EEPROM_PROTECT_WR_192_207	0x0200
#घोषणा AR5K_EEPROM_PROTECT_RD_208_223	0x0400	/* 0xd0 - 0xdf */
#घोषणा AR5K_EEPROM_PROTECT_WR_208_223	0x0800
#घोषणा AR5K_EEPROM_PROTECT_RD_224_239	0x1000	/* 0xe0 - 0xef */
#घोषणा AR5K_EEPROM_PROTECT_WR_224_239	0x2000
#घोषणा AR5K_EEPROM_PROTECT_RD_240_255	0x4000	/* 0xf0 - 0xff */
#घोषणा AR5K_EEPROM_PROTECT_WR_240_255	0x8000

/* Some EEPROM defines */
#घोषणा AR5K_EEPROM_EEP_SCALE		100
#घोषणा AR5K_EEPROM_EEP_DELTA		10
#घोषणा AR5K_EEPROM_N_MODES		3
#घोषणा AR5K_EEPROM_N_5GHZ_CHAN		10
#घोषणा AR5K_EEPROM_N_5GHZ_RATE_CHAN	8
#घोषणा AR5K_EEPROM_N_2GHZ_CHAN		3
#घोषणा AR5K_EEPROM_N_2GHZ_CHAN_2413	4
#घोषणा	AR5K_EEPROM_N_2GHZ_CHAN_MAX	4
#घोषणा AR5K_EEPROM_MAX_CHAN		10
#घोषणा AR5K_EEPROM_N_PWR_POINTS_5111	11
#घोषणा AR5K_EEPROM_N_PCDAC		11
#घोषणा AR5K_EEPROM_N_PHASE_CAL		5
#घोषणा AR5K_EEPROM_N_TEST_FREQ		8
#घोषणा AR5K_EEPROM_N_EDGES		8
#घोषणा AR5K_EEPROM_N_INTERCEPTS	11
#घोषणा AR5K_EEPROM_FREQ_M(_v)		AR5K_EEPROM_OFF(_v, 0x7f, 0xff)
#घोषणा AR5K_EEPROM_PCDAC_M		0x3f
#घोषणा AR5K_EEPROM_PCDAC_START		1
#घोषणा AR5K_EEPROM_PCDAC_STOP		63
#घोषणा AR5K_EEPROM_PCDAC_STEP		1
#घोषणा AR5K_EEPROM_NON_EDGE_M		0x40
#घोषणा AR5K_EEPROM_CHANNEL_POWER	8
#घोषणा AR5K_EEPROM_N_OBDB		4
#घोषणा AR5K_EEPROM_OBDB_DIS		0xffff
#घोषणा AR5K_EEPROM_CHANNEL_DIS		0xff
#घोषणा AR5K_EEPROM_SCALE_OC_DELTA(_x)	(((_x) * 2) / 10)
#घोषणा AR5K_EEPROM_N_CTLS(_v)		AR5K_EEPROM_OFF(_v, 16, 32)
#घोषणा AR5K_EEPROM_MAX_CTLS		32
#घोषणा AR5K_EEPROM_N_PD_CURVES		4
#घोषणा AR5K_EEPROM_N_XPD0_POINTS	4
#घोषणा AR5K_EEPROM_N_XPD3_POINTS	3
#घोषणा AR5K_EEPROM_N_PD_GAINS		4
#घोषणा AR5K_EEPROM_N_PD_POINTS		5
#घोषणा AR5K_EEPROM_N_INTERCEPT_10_2GHZ	35
#घोषणा AR5K_EEPROM_N_INTERCEPT_10_5GHZ	55
#घोषणा AR5K_EEPROM_POWER_M		0x3f
#घोषणा AR5K_EEPROM_POWER_MIN		0
#घोषणा AR5K_EEPROM_POWER_MAX		3150
#घोषणा AR5K_EEPROM_POWER_STEP		50
#घोषणा AR5K_EEPROM_POWER_TABLE_SIZE	64
#घोषणा AR5K_EEPROM_N_POWER_LOC_11B	4
#घोषणा AR5K_EEPROM_N_POWER_LOC_11G	6
#घोषणा AR5K_EEPROM_I_GAIN		10
#घोषणा AR5K_EEPROM_CCK_OFDM_DELTA	15
#घोषणा AR5K_EEPROM_N_IQ_CAL		2
/* 5GHz/2GHz */
क्रमागत ath5k_eeprom_freq_bands अणु
	AR5K_EEPROM_BAND_5GHZ = 0,
	AR5K_EEPROM_BAND_2GHZ = 1,
	AR5K_EEPROM_N_FREQ_BANDS,
पूर्ण;
/* Spur chans per freq band */
#घोषणा	AR5K_EEPROM_N_SPUR_CHANS	5
/* fbin value क्रम chan 2464 x2 */
#घोषणा	AR5K_EEPROM_5413_SPUR_CHAN_1	1640
/* fbin value क्रम chan 2420 x2 */
#घोषणा	AR5K_EEPROM_5413_SPUR_CHAN_2	1200
#घोषणा	AR5K_EEPROM_SPUR_CHAN_MASK	0x3FFF
#घोषणा	AR5K_EEPROM_NO_SPUR		0x8000
#घोषणा	AR5K_SPUR_CHAN_WIDTH			87
#घोषणा	AR5K_SPUR_SYMBOL_WIDTH_BASE_100Hz	3125
#घोषणा	AR5K_SPUR_SYMBOL_WIDTH_TURBO_100Hz	6250

#घोषणा AR5K_EEPROM_READ(_o, _v) करो अणु			\
	अगर (!ath5k_hw_nvram_पढ़ो(ah, (_o), &(_v)))	\
		वापस -EIO;				\
पूर्ण जबतक (0)

#घोषणा AR5K_EEPROM_READ_HDR(_o, _v)					\
	AR5K_EEPROM_READ(_o, ah->ah_capabilities.cap_eeprom._v);	\

क्रमागत ath5k_ant_table अणु
	AR5K_ANT_CTL		= 0,	/* Idle चयन table settings */
	AR5K_ANT_SWTABLE_A	= 1,	/* Switch table क्रम antenna A */
	AR5K_ANT_SWTABLE_B	= 2,	/* Switch table क्रम antenna B */
	AR5K_ANT_MAX,
पूर्ण;

क्रमागत ath5k_ctl_mode अणु
	AR5K_CTL_11A = 0,
	AR5K_CTL_11B = 1,
	AR5K_CTL_11G = 2,
	AR5K_CTL_TURBO = 3,
	AR5K_CTL_TURBOG = 4,
	AR5K_CTL_2GHT20 = 5,
	AR5K_CTL_5GHT20 = 6,
	AR5K_CTL_2GHT40 = 7,
	AR5K_CTL_5GHT40 = 8,
	AR5K_CTL_MODE_M = 15,
पूर्ण;

/* Per channel calibration data, used क्रम घातer table setup */
काष्ठा ath5k_chan_pcal_info_rf5111 अणु
	/* Power levels in half dBm units
	 * क्रम one घातer curve. */
	u8 pwr[AR5K_EEPROM_N_PWR_POINTS_5111];
	/* PCDAC table steps
	 * क्रम the above values */
	u8 pcdac[AR5K_EEPROM_N_PWR_POINTS_5111];
	/* Starting PCDAC step */
	u8 pcdac_min;
	/* Final PCDAC step */
	u8 pcdac_max;
पूर्ण;

काष्ठा ath5k_chan_pcal_info_rf5112 अणु
	/* Power levels in quarter dBm units
	 * क्रम lower (0) and higher (3)
	 * level curves in 0.25dB units */
	s8 pwr_x0[AR5K_EEPROM_N_XPD0_POINTS];
	s8 pwr_x3[AR5K_EEPROM_N_XPD3_POINTS];
	/* PCDAC table steps
	 * क्रम the above values */
	u8 pcdac_x0[AR5K_EEPROM_N_XPD0_POINTS];
	u8 pcdac_x3[AR5K_EEPROM_N_XPD3_POINTS];
पूर्ण;

काष्ठा ath5k_chan_pcal_info_rf2413 अणु
	/* Starting pwr/pddac values */
	s8 pwr_i[AR5K_EEPROM_N_PD_GAINS];
	u8 pddac_i[AR5K_EEPROM_N_PD_GAINS];
	/* (pwr,pddac) poपूर्णांकs
	 * घातer levels in 0.5dB units */
	s8 pwr[AR5K_EEPROM_N_PD_GAINS]
		[AR5K_EEPROM_N_PD_POINTS];
	u8 pddac[AR5K_EEPROM_N_PD_GAINS]
		[AR5K_EEPROM_N_PD_POINTS];
पूर्ण;

क्रमागत ath5k_घातertable_type अणु
	AR5K_PWRTABLE_PWR_TO_PCDAC = 0,
	AR5K_PWRTABLE_LINEAR_PCDAC = 1,
	AR5K_PWRTABLE_PWR_TO_PDADC = 2,
पूर्ण;

काष्ठा ath5k_pdgain_info अणु
	u8 pd_poपूर्णांकs;
	u8 *pd_step;
	/* Power values are in
	 * 0.25dB units */
	s16 *pd_pwr;
पूर्ण;

काष्ठा ath5k_chan_pcal_info अणु
	/* Frequency */
	u16	freq;
	/* Tx घातer boundaries */
	s16	max_pwr;
	s16	min_pwr;
	जोड़ अणु
		काष्ठा ath5k_chan_pcal_info_rf5111 rf5111_info;
		काष्ठा ath5k_chan_pcal_info_rf5112 rf5112_info;
		काष्ठा ath5k_chan_pcal_info_rf2413 rf2413_info;
	पूर्ण;
	/* Raw values used by phy code
	 * Curves are stored in order from lower
	 * gain to higher gain (max txघातer -> min txघातer) */
	काष्ठा ath5k_pdgain_info *pd_curves;
पूर्ण;

/* Per rate calibration data क्रम each mode,
 * used क्रम rate घातer table setup.
 * Note: Values in 0.5dB units */
काष्ठा ath5k_rate_pcal_info अणु
	u16	freq; /* Frequency */
	/* Power level क्रम 6-24Mbit/s rates or
	 * 1Mb rate */
	u16	target_घातer_6to24;
	/* Power level क्रम 36Mbit rate or
	 * 2Mb rate */
	u16	target_घातer_36;
	/* Power level क्रम 48Mbit rate or
	 * 5.5Mbit rate */
	u16	target_घातer_48;
	/* Power level क्रम 54Mbit rate or
	 * 11Mbit rate */
	u16	target_घातer_54;
पूर्ण;

/* Power edges क्रम conक्रमmance test limits */
काष्ठा ath5k_edge_घातer अणु
	u16 freq;
	u16 edge; /* in half dBm */
	bool flag;
पूर्ण;

/**
 * काष्ठा ath5k_eeprom_info - EEPROM calibration data
 *
 * @ee_regकरोमुख्य: ath/regd.c takes care of COUNTRY_ERD and WORLDWIDE_ROAMING
 *	flags
 * @ee_ant_gain: Antenna gain in 0.5dB steps चिन्हित [5211 only?]
 * @ee_cck_ofdm_gain_delta: dअगरference in gainF to output the same घातer क्रम
 *	OFDM and CCK packets
 * @ee_cck_ofdm_घातer_delta: घातer dअगरference between OFDM (6Mbps) and CCK
 *	(11Mbps) rate in G mode. 0.1dB steps
 * @ee_scaled_cck_delta: क्रम Japan Channel 14: 0.1dB resolution
 *
 * @ee_i_cal: Initial I coefficient to correct I/Q mismatch in the receive path
 * @ee_q_cal: Initial Q coefficient to correct I/Q mismatch in the receive path
 * @ee_fixed_bias: use ee_ob and ee_db settings or use स्वतःmatic control
 * @ee_चयन_settling: RX/TX Switch settling समय
 * @ee_atn_tx_rx: Dअगरference in attenuation between TX and RX in 1dB steps
 * @ee_ant_control: Antenna Control Settings
 * @ee_ob: Bias current क्रम Output stage of PA
 *	B/G mode: Index [0] is used क्रम AR2112/5112, otherwise [1]
 *	A mode: [0] 5.15-5.25 [1] 5.25-5.50 [2] 5.50-5.70 [3] 5.70-5.85 GHz
 * @ee_db: Bias current क्रम Output stage of PA. see @ee_ob
 * @ee_tx_end2xlna_enable: Time dअगरference from when BB finishes sending a frame
 *	to when the बाह्यal LNA is activated
 * @ee_tx_end2xpa_disable: Time dअगरference from when BB finishes sending a frame
 *	to when the बाह्यal PA चयन is deactivated
 * @ee_tx_frm2xpa_enable: Time dअगरference from when MAC sends frame to when
 *	बाह्यal PA चयन is activated
 * @ee_thr_62: Clear Channel Assessment (CCA) sensitivity
 *	(IEEE802.11a section 17.3.10.5 )
 * @ee_xlna_gain: Total gain of the LNA (inक्रमmation only)
 * @ee_xpd: Use बाह्यal (1) or पूर्णांकernal घातer detector
 * @ee_x_gain: Gain क्रम बाह्यal घातer detector output (dअगरferences in EEMAP
 *	versions!)
 * @ee_i_gain: Initial gain value after reset
 * @ee_margin_tx_rx: Margin in dB when final attenuation stage should be used
 *
 * @ee_false_detect: Backoff in Sensitivity (dB) on channels with spur संकेतs
 * @ee_noise_न्यूनमान_thr: Noise न्यूनमान threshold in 1dB steps
 * @ee_adc_desired_size: Desired amplitude क्रम ADC, used by AGC; in 0.5 dB steps
 * @ee_pga_desired_size: Desired output of PGA (क्रम BB gain) in 0.5 dB steps
 * @ee_pd_gain_overlap: PD ADC curves need to overlap in 0.5dB steps (ee_map>=2)
 */
काष्ठा ath5k_eeprom_info अणु

	/* Header inक्रमmation */
	u16	ee_magic;
	u16	ee_protect;
	u16	ee_regकरोमुख्य;
	u16	ee_version;
	u16	ee_header;
	u16	ee_ant_gain;
	u8	ee_rfसमाप्त_pin;
	bool	ee_rfसमाप्त_pol;
	bool	ee_is_hb63;
	bool	ee_serdes;
	u16	ee_misc0;
	u16	ee_misc1;
	u16	ee_misc2;
	u16	ee_misc3;
	u16	ee_misc4;
	u16	ee_misc5;
	u16	ee_misc6;
	u16	ee_cck_ofdm_gain_delta;
	u16	ee_cck_ofdm_घातer_delta;
	u16	ee_scaled_cck_delta;

	/* RF Calibration settings (reset, rfregs) */
	u16	ee_i_cal[AR5K_EEPROM_N_MODES];
	u16	ee_q_cal[AR5K_EEPROM_N_MODES];
	u16	ee_fixed_bias[AR5K_EEPROM_N_MODES];
	u16	ee_turbo_max_घातer[AR5K_EEPROM_N_MODES];
	u16	ee_xr_घातer[AR5K_EEPROM_N_MODES];
	u16	ee_चयन_settling[AR5K_EEPROM_N_MODES];
	u16	ee_atn_tx_rx[AR5K_EEPROM_N_MODES];
	u16	ee_ant_control[AR5K_EEPROM_N_MODES][AR5K_EEPROM_N_PCDAC];
	u16	ee_ob[AR5K_EEPROM_N_MODES][AR5K_EEPROM_N_OBDB];
	u16	ee_db[AR5K_EEPROM_N_MODES][AR5K_EEPROM_N_OBDB];
	u16	ee_tx_end2xlna_enable[AR5K_EEPROM_N_MODES];
	u16	ee_tx_end2xpa_disable[AR5K_EEPROM_N_MODES];
	u16	ee_tx_frm2xpa_enable[AR5K_EEPROM_N_MODES];
	u16	ee_thr_62[AR5K_EEPROM_N_MODES];
	u16	ee_xlna_gain[AR5K_EEPROM_N_MODES];
	u16	ee_xpd[AR5K_EEPROM_N_MODES];
	u16	ee_x_gain[AR5K_EEPROM_N_MODES];
	u16	ee_i_gain[AR5K_EEPROM_N_MODES];
	u16	ee_margin_tx_rx[AR5K_EEPROM_N_MODES];
	u16	ee_चयन_settling_turbo[AR5K_EEPROM_N_MODES];
	u16	ee_margin_tx_rx_turbo[AR5K_EEPROM_N_MODES];
	u16	ee_atn_tx_rx_turbo[AR5K_EEPROM_N_MODES];

	/* Power calibration data */
	u16	ee_false_detect[AR5K_EEPROM_N_MODES];

	/* Number of pd gain curves per mode */
	u8	ee_pd_gains[AR5K_EEPROM_N_MODES];
	/* Back mapping pdcurve number -> pdcurve index in pd->pd_curves */
	u8	ee_pdc_to_idx[AR5K_EEPROM_N_MODES][AR5K_EEPROM_N_PD_GAINS];

	u8	ee_n_piers[AR5K_EEPROM_N_MODES];
	काष्ठा ath5k_chan_pcal_info	ee_pwr_cal_a[AR5K_EEPROM_N_5GHZ_CHAN];
	काष्ठा ath5k_chan_pcal_info	ee_pwr_cal_b[AR5K_EEPROM_N_2GHZ_CHAN_MAX];
	काष्ठा ath5k_chan_pcal_info	ee_pwr_cal_g[AR5K_EEPROM_N_2GHZ_CHAN_MAX];

	/* Per rate target घातer levels */
	u8	ee_rate_target_pwr_num[AR5K_EEPROM_N_MODES];
	काष्ठा ath5k_rate_pcal_info	ee_rate_tpwr_a[AR5K_EEPROM_N_5GHZ_CHAN];
	काष्ठा ath5k_rate_pcal_info	ee_rate_tpwr_b[AR5K_EEPROM_N_2GHZ_CHAN_MAX];
	काष्ठा ath5k_rate_pcal_info	ee_rate_tpwr_g[AR5K_EEPROM_N_2GHZ_CHAN_MAX];

	/* Conक्रमmance test limits (Unused) */
	u8	ee_ctls;
	u8	ee_ctl[AR5K_EEPROM_MAX_CTLS];
	काष्ठा ath5k_edge_घातer ee_ctl_pwr[AR5K_EEPROM_N_EDGES * AR5K_EEPROM_MAX_CTLS];

	/* Noise Floor Calibration settings */
	s16	ee_noise_न्यूनमान_thr[AR5K_EEPROM_N_MODES];
	s8	ee_adc_desired_size[AR5K_EEPROM_N_MODES];
	s8	ee_pga_desired_size[AR5K_EEPROM_N_MODES];
	s8	ee_adc_desired_माप_प्रकारurbo[AR5K_EEPROM_N_MODES];
	s8	ee_pga_desired_माप_प्रकारurbo[AR5K_EEPROM_N_MODES];
	s8	ee_pd_gain_overlap;

	/* Spur mitigation data (fbin values क्रम spur channels) */
	u16	ee_spur_chans[AR5K_EEPROM_N_SPUR_CHANS][AR5K_EEPROM_N_FREQ_BANDS];

	/* Antenna raw चयन tables */
	u32	ee_antenna[AR5K_EEPROM_N_MODES][AR5K_ANT_MAX];
पूर्ण;

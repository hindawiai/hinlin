<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW8822C_H__
#घोषणा __RTW8822C_H__

#समावेश <यंत्र/byteorder.h>

काष्ठा rtw8822cu_efuse अणु
	u8 res0[0x30];			/* 0x120 */
	u8 vid[2];			/* 0x150 */
	u8 pid[2];
	u8 res1[3];
	u8 mac_addr[ETH_ALEN];		/* 0x157 */
	u8 res2[0x3d];
पूर्ण;

काष्ठा rtw8822ce_efuse अणु
	u8 mac_addr[ETH_ALEN];		/* 0x120 */
	u8 vender_id[2];
	u8 device_id[2];
	u8 sub_vender_id[2];
	u8 sub_device_id[2];
	u8 pmc[2];
	u8 exp_device_cap[2];
	u8 msi_cap;
	u8 ltr_cap;			/* 0x133 */
	u8 exp_link_control[2];
	u8 link_cap[4];
	u8 link_control[2];
	u8 serial_number[8];
	u8 res0:2;			/* 0x144 */
	u8 ltr_en:1;
	u8 res1:2;
	u8 obff:2;
	u8 res2:3;
	u8 obff_cap:2;
	u8 res3:4;
	u8 class_code[3];
	u8 res4;
	u8 pci_pm_L1_2_supp:1;
	u8 pci_pm_L1_1_supp:1;
	u8 aspm_pm_L1_2_supp:1;
	u8 aspm_pm_L1_1_supp:1;
	u8 L1_pm_substates_supp:1;
	u8 res5:3;
	u8 port_common_mode_restore_समय;
	u8 port_t_घातer_on_scale:2;
	u8 res6:1;
	u8 port_t_घातer_on_value:5;
	u8 res7;
पूर्ण;

काष्ठा rtw8822c_efuse अणु
	__le16 rtl_id;
	u8 res0[0x0e];

	/* घातer index क्रम four RF paths */
	काष्ठा rtw_txpwr_idx txpwr_idx_table[4];

	u8 channel_plan;		/* 0xb8 */
	u8 xtal_k;
	u8 res1;
	u8 iqk_lck;
	u8 res2[5];			/* 0xbc */
	u8 rf_board_option;
	u8 rf_feature_option;
	u8 rf_bt_setting;
	u8 eeprom_version;
	u8 eeprom_customer_id;
	u8 tx_bb_swing_setting_2g;
	u8 tx_bb_swing_setting_5g;
	u8 tx_pwr_calibrate_rate;
	u8 rf_antenna_option;		/* 0xc9 */
	u8 rfe_option;
	u8 country_code[2];
	u8 res3[3];
	u8 path_a_thermal;		/* 0xd0 */
	u8 path_b_thermal;
	u8 res4[2];
	u8 rx_gain_gap_2g_ofdm;
	u8 res5;
	u8 rx_gain_gap_2g_cck;
	u8 res6;
	u8 rx_gain_gap_5gl;
	u8 res7;
	u8 rx_gain_gap_5gm;
	u8 res8;
	u8 rx_gain_gap_5gh;
	u8 res9;
	u8 res10[0x42];
	जोड़ अणु
		काष्ठा rtw8822cu_efuse u;
		काष्ठा rtw8822ce_efuse e;
	पूर्ण;
पूर्ण;

क्रमागत rtw8822c_dpk_agc_phase अणु
	RTW_DPK_GAIN_CHECK,
	RTW_DPK_GAIN_LARGE,
	RTW_DPK_GAIN_LESS,
	RTW_DPK_GL_LARGE,
	RTW_DPK_GL_LESS,
	RTW_DPK_LOSS_CHECK,
	RTW_DPK_AGC_OUT,
पूर्ण;

क्रमागत rtw8822c_dpk_one_shot_action अणु
	RTW_DPK_CAL_PWR,
	RTW_DPK_GAIN_LOSS,
	RTW_DPK_DO_DPK,
	RTW_DPK_DPK_ON,
	RTW_DPK_DAGC,
	RTW_DPK_ACTION_MAX
पूर्ण;

व्योम rtw8822c_parse_tbl_dpk(काष्ठा rtw_dev *rtwdev,
			    स्थिर काष्ठा rtw_table *tbl);

#घोषणा RTW_DECL_TABLE_DPK(name)			\
स्थिर काष्ठा rtw_table name ## _tbl = अणु			\
	.data = name,					\
	.size = ARRAY_SIZE(name),			\
	.parse = rtw8822c_parse_tbl_dpk,		\
पूर्ण

#घोषणा DACK_PATH_8822C		2
#घोषणा DACK_REG_8822C		16
#घोषणा DACK_RF_8822C		1
#घोषणा DACK_SN_8822C		100

/* phy status page0 */
#घोषणा GET_PHY_STAT_P0_PWDB_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#घोषणा GET_PHY_STAT_P0_PWDB_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(7, 0))
#घोषणा GET_PHY_STAT_P0_GAIN_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(21, 16))
#घोषणा GET_PHY_STAT_P0_GAIN_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(29, 24))

/* phy status page1 */
#घोषणा GET_PHY_STAT_P1_PWDB_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#घोषणा GET_PHY_STAT_P1_PWDB_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(23, 16))
#घोषणा GET_PHY_STAT_P1_L_RXSC(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x01), GENMASK(11, 8))
#घोषणा GET_PHY_STAT_P1_HT_RXSC(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x01), GENMASK(15, 12))
#घोषणा GET_PHY_STAT_P1_RXEVM_A(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(7, 0))
#घोषणा GET_PHY_STAT_P1_RXEVM_B(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x04), GENMASK(15, 8))
#घोषणा GET_PHY_STAT_P1_CFO_TAIL_A(phy_stat)                                 \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x05), GENMASK(7, 0))
#घोषणा GET_PHY_STAT_P1_CFO_TAIL_B(phy_stat)                                 \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x05), GENMASK(15, 8))
#घोषणा GET_PHY_STAT_P1_RXSNR_A(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x06), GENMASK(7, 0))
#घोषणा GET_PHY_STAT_P1_RXSNR_B(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x06), GENMASK(15, 8))

#घोषणा REG_ANAPARLDO_POW_MAC	0x0029
#घोषणा BIT_LDOE25_PON		BIT(0)
#घोषणा XCAP_MASK		GENMASK(6, 0)
#घोषणा CFO_TRK_ENABLE_TH	20
#घोषणा CFO_TRK_STOP_TH		10
#घोषणा CFO_TRK_ADJ_TH		10

#घोषणा REG_TXDFIR0		0x808
#घोषणा REG_DFIRBW		0x810
#घोषणा REG_ANTMAP0		0x820
#घोषणा BIT_ANT_PATH		GENMASK(1, 0)
#घोषणा REG_ANTMAP		0x824
#घोषणा REG_DYMPRITH		0x86c
#घोषणा REG_DYMENTH0		0x870
#घोषणा REG_DYMENTH		0x874
#घोषणा REG_SBD			0x88c
#घोषणा BITS_SUBTUNE		GENMASK(15, 12)
#घोषणा REG_DYMTHMIN		0x8a4

#घोषणा REG_TXBWCTL		0x9b0
#घोषणा REG_TXCLK		0x9b4

#घोषणा REG_SCOTRK		0xc30
#घोषणा REG_MRCM		0xc38
#घोषणा REG_AGCSWSH		0xc44
#घोषणा REG_ANTWTPD		0xc54
#घोषणा REG_PT_CHSMO		0xcbc
#घोषणा BIT_PT_OPT		BIT(21)

#घोषणा REG_ORITXCODE		0x1800
#घोषणा BIT_PATH_EN		BIT(31)
#घोषणा REG_3WIRE		0x180c
#घोषणा BIT_DIS_SHARERX_TXGAT	BIT(27)
#घोषणा BIT_3WIRE_TX_EN		BIT(0)
#घोषणा BIT_3WIRE_RX_EN		BIT(1)
#घोषणा BIT_3WIRE_EN		GENMASK(1, 0)
#घोषणा BIT_3WIRE_PI_ON		BIT(28)
#घोषणा REG_ANAPAR_A		0x1830
#घोषणा BIT_ANAPAR_UPDATE	BIT(29)
#घोषणा REG_RFTXEN_GCK_A	0x1864
#घोषणा BIT_RFTXEN_GCK_FORCE_ON	BIT(31)
#घोषणा REG_DIS_SHARE_RX_A	0x186c
#घोषणा BIT_TX_SCALE_0DB	BIT(7)
#घोषणा REG_RXAGCCTL0		0x18ac
#घोषणा BITS_RXAGC_CCK		GENMASK(15, 12)
#घोषणा BITS_RXAGC_OFDM		GENMASK(8, 4)
#घोषणा REG_DCKA_I_0		0x18bc
#घोषणा REG_DCKA_I_1		0x18c0
#घोषणा REG_DCKA_Q_0		0x18d8
#घोषणा REG_DCKA_Q_1		0x18dc

#घोषणा REG_CCKSB		0x1a00
#घोषणा BIT_BBMODE		GENMASK(2, 1)
#घोषणा REG_RXCCKSEL		0x1a04
#घोषणा REG_BGCTRL		0x1a14
#घोषणा BITS_RX_IQ_WEIGHT	(BIT(8) | BIT(9))
#घोषणा REG_TXF0		0x1a20
#घोषणा REG_TXF1		0x1a24
#घोषणा REG_TXF2		0x1a28
#घोषणा REG_CCANRX		0x1a2c
#घोषणा BIT_CCK_FA_RST		(BIT(14) | BIT(15))
#घोषणा BIT_OFDM_FA_RST		(BIT(12) | BIT(13))
#घोषणा REG_CCK_FACNT		0x1a5c
#घोषणा REG_CCKTXONLY		0x1a80
#घोषणा BIT_BB_CCK_CHECK_EN	BIT(18)
#घोषणा REG_TXF3		0x1a98
#घोषणा REG_TXF4		0x1a9c
#घोषणा REG_TXF5		0x1aa0
#घोषणा REG_TXF6		0x1aac
#घोषणा REG_TXF7		0x1ab0
#घोषणा REG_CCK_SOURCE		0x1abc
#घोषणा BIT_NBI_EN		BIT(30)

#घोषणा REG_NCTL0		0x1b00
#घोषणा BIT_SEL_PATH		GENMASK(2, 1)
#घोषणा BIT_SUBPAGE		GENMASK(3, 0)
#घोषणा REG_DPD_CTL0_S0		0x1b04
#घोषणा BIT_GS_PWSF		GENMASK(27, 0)
#घोषणा REG_DPD_CTL1_S0		0x1b08
#घोषणा BIT_DPD_EN		BIT(31)
#घोषणा BIT_PS_EN		BIT(7)
#घोषणा REG_IQKSTAT		0x1b10
#घोषणा REG_IQK_CTL1		0x1b20
#घोषणा BIT_TX_CFIR		GENMASK(31, 30)
#घोषणा BIT_CFIR_EN		GENMASK(26, 24)
#घोषणा BIT_BYPASS_DPD		BIT(25)

#घोषणा REG_TX_TONE_IDX		0x1b2c
#घोषणा REG_DPD_LUT0		0x1b44
#घोषणा BIT_GLOSS_DB		GENMASK(14, 12)
#घोषणा REG_DPD_CTL0_S1		0x1b5c
#घोषणा REG_DPD_CTL1_S1		0x1b60
#घोषणा REG_DPD_AGC		0x1b67
#घोषणा REG_TABLE_SEL		0x1b98
#घोषणा BIT_I_GAIN		GENMASK(19, 16)
#घोषणा BIT_GAIN_RST		BIT(15)
#घोषणा BIT_Q_GAIN_SEL		GENMASK(14, 12)
#घोषणा BIT_Q_GAIN		GENMASK(11, 0)
#घोषणा REG_TX_GAIN_SET		0x1b9c
#घोषणा BIT_GAPK_RPT_IDX	GENMASK(11, 8)
#घोषणा REG_DPD_CTL0		0x1bb4
#घोषणा REG_SINGLE_TONE_SW	0x1bb8
#घोषणा BIT_IRQ_TEST_MODE	BIT(20)
#घोषणा REG_R_CONFIG		0x1bcc
#घोषणा BIT_INNER_LB		BIT(21)
#घोषणा BIT_IQ_SWITCH		GENMASK(5, 0)
#घोषणा BIT_2G_SWING		0x2d
#घोषणा BIT_5G_SWING		0x36
#घोषणा REG_RXSRAM_CTL		0x1bd4
#घोषणा BIT_RPT_EN		BIT(21)
#घोषणा BIT_RPT_SEL		GENMASK(20, 16)
#घोषणा BIT_DPD_CLK		GENMASK(7, 4)
#घोषणा REG_DPD_CTL11		0x1be4
#घोषणा REG_DPD_CTL12		0x1be8
#घोषणा REG_DPD_CTL15		0x1bf4
#घोषणा REG_DPD_CTL16		0x1bf8
#घोषणा REG_STAT_RPT		0x1bfc
#घोषणा BIT_RPT_DGAIN		GENMASK(27, 16)
#घोषणा BIT_GAPK_RPT0		GENMASK(3, 0)
#घोषणा BIT_GAPK_RPT1		GENMASK(7, 4)
#घोषणा BIT_GAPK_RPT2		GENMASK(11, 8)
#घोषणा BIT_GAPK_RPT3		GENMASK(15, 12)
#घोषणा BIT_GAPK_RPT4		GENMASK(19, 16)
#घोषणा BIT_GAPK_RPT5		GENMASK(23, 20)
#घोषणा BIT_GAPK_RPT6		GENMASK(27, 24)
#घोषणा BIT_GAPK_RPT7		GENMASK(31, 28)

#घोषणा REG_TXANT		0x1c28
#घोषणा REG_IQK_CTRL		0x1c38
#घोषणा REG_ENCCK		0x1c3c
#घोषणा BIT_CCK_BLK_EN		BIT(1)
#घोषणा BIT_CCK_OFDM_BLK_EN	(BIT(0) | BIT(1))
#घोषणा REG_CCAMSK		0x1c80
#घोषणा REG_RSTB		0x1c90
#घोषणा BIT_RSTB_3WIRE		BIT(8)
#घोषणा REG_CH_DELAY_EXTR2	0x1cd0
#घोषणा BIT_TST_IQK2SET_SRC	BIT(31)
#घोषणा BIT_EN_IOQ_IQK_DPK	BIT(30)
#घोषणा BIT_IQK_DPK_RESET_SRC	BIT(29)
#घोषणा BIT_IQK_DPK_CLOCK_SRC	BIT(28)

#घोषणा REG_RX_BREAK		0x1d2c
#घोषणा BIT_COM_RX_GCK_EN	BIT(31)
#घोषणा REG_RXFNCTL		0x1d30
#घोषणा REG_CCA_OFF		0x1d58
#घोषणा BIT_CCA_ON_BY_PW	GENMASK(11, 3)
#घोषणा REG_RXIGI		0x1d70

#घोषणा REG_ENFN		0x1e24
#घोषणा BIT_IQK_DPK_EN		BIT(17)
#घोषणा REG_TXANTSEG		0x1e28
#घोषणा BIT_ANTSEG		GENMASK(3, 0)
#घोषणा REG_TXLGMAP		0x1e2c
#घोषणा REG_CCKPATH		0x1e5c
#घोषणा REG_TX_FIFO		0x1e70
#घोषणा BIT_STOP_TX		GENMASK(3, 0)
#घोषणा REG_CNT_CTRL		0x1eb4
#घोषणा BIT_ALL_CNT_RST		BIT(25)

#घोषणा REG_OFDM_FACNT		0x2d00
#घोषणा REG_OFDM_FACNT1		0x2d04
#घोषणा REG_OFDM_FACNT2		0x2d08
#घोषणा REG_OFDM_FACNT3		0x2d0c
#घोषणा REG_OFDM_FACNT4		0x2d10
#घोषणा REG_OFDM_FACNT5		0x2d20
#घोषणा REG_RPT_CIP		0x2d9c
#घोषणा BIT_RPT_CIP_STATUS	GENMASK(7, 0)
#घोषणा REG_OFDM_TXCNT		0x2de0

#घोषणा REG_ORITXCODE2		0x4100
#घोषणा REG_3WIRE2		0x410c
#घोषणा REG_ANAPAR_B		0x4130
#घोषणा REG_RFTXEN_GCK_B	0x4164
#घोषणा REG_DIS_SHARE_RX_B	0x416c
#घोषणा BIT_EXT_TIA_BW		BIT(1)
#घोषणा REG_RXAGCCTL		0x41ac
#घोषणा REG_DCKB_I_0		0x41bc
#घोषणा REG_DCKB_I_1		0x41c0
#घोषणा REG_DCKB_Q_0		0x41d8
#घोषणा REG_DCKB_Q_1		0x41dc

#घोषणा RF_MODE_TRXAGC		0x00
#घोषणा BIT_RF_MODE		GENMASK(19, 16)
#घोषणा BIT_RXAGC		GENMASK(9, 5)
#घोषणा BIT_TXAGC		GENMASK(4, 0)
#घोषणा RF_RXAGC_OFFSET		0x19
#घोषणा RF_BW_TRXBB		0x1a
#घोषणा BIT_TX_CCK_IND		BIT(16)
#घोषणा BIT_BW_TXBB		GENMASK(14, 12)
#घोषणा BIT_BW_RXBB		GENMASK(11, 10)
#घोषणा BIT_DBG_CCK_CCA		BIT(1)
#घोषणा RF_TX_GAIN_OFFSET	0x55
#घोषणा BIT_BB_GAIN		GENMASK(18, 14)
#घोषणा BIT_RF_GAIN		GENMASK(4, 2)
#घोषणा RF_TX_GAIN		0x56
#घोषणा BIT_GAIN_TXBB		GENMASK(4, 0)
#घोषणा RF_IDAC			0x58
#घोषणा BIT_TX_MODE		GENMASK(19, 8)
#घोषणा RF_TX_RESULT		0x5f
#घोषणा BIT_GAIN_TX_PAD_H	GENMASK(11, 8)
#घोषणा BIT_GAIN_TX_PAD_L	GENMASK(7, 4)
#घोषणा RF_PA			0x60
#घोषणा RF_PABIAS_2G_MASK	GENMASK(15, 12)
#घोषणा RF_PABIAS_5G_MASK	GENMASK(19, 16)
#घोषणा RF_TXA_LB_SW		0x63
#घोषणा BIT_TXA_LB_ATT		GENMASK(15, 14)
#घोषणा BIT_LB_SW		GENMASK(13, 12)
#घोषणा BIT_LB_ATT		GENMASK(4, 2)
#घोषणा RF_RXG_GAIN		0x87
#घोषणा BIT_RXG_GAIN		BIT(18)
#घोषणा RF_RXA_MIX_GAIN		0x8a
#घोषणा BIT_RXA_MIX_GAIN	GENMASK(4, 3)
#घोषणा RF_EXT_TIA_BW		0x8f
#घोषणा BIT_PW_EXT_TIA		BIT(1)
#घोषणा RF_DIS_BYPASS_TXBB	0x9e
#घोषणा BIT_TXBB		BIT(10)
#घोषणा BIT_TIA_BYPASS		BIT(5)
#घोषणा RF_DEBUG		0xde
#घोषणा BIT_DE_PWR_TRIM		BIT(19)
#घोषणा BIT_DE_TX_GAIN		BIT(16)
#घोषणा BIT_DE_TRXBW		BIT(2)

#घोषणा PPG_THERMAL_B		0x1b0
#घोषणा RF_THEMAL_MASK		GENMASK(19, 16)
#घोषणा PPG_2GH_TXAB		0x1d2
#घोषणा PPG_2G_A_MASK		GENMASK(3, 0)
#घोषणा PPG_2G_B_MASK		GENMASK(7, 4)
#घोषणा PPG_2GL_TXAB		0x1d4
#घोषणा PPG_PABIAS_2GB		0x1d5
#घोषणा PPG_PABIAS_2GA		0x1d6
#घोषणा PPG_PABIAS_MASK		GENMASK(3, 0)
#घोषणा PPG_PABIAS_5GB		0x1d7
#घोषणा PPG_PABIAS_5GA		0x1d8
#घोषणा PPG_5G_MASK		GENMASK(4, 0)
#घोषणा PPG_5GH1_TXB		0x1db
#घोषणा PPG_5GH1_TXA		0x1dc
#घोषणा PPG_5GM2_TXB		0x1df
#घोषणा PPG_5GM2_TXA		0x1e0
#घोषणा PPG_5GM1_TXB		0x1e3
#घोषणा PPG_5GM1_TXA		0x1e4
#घोषणा PPG_5GL2_TXB		0x1e7
#घोषणा PPG_5GL2_TXA		0x1e8
#घोषणा PPG_5GL1_TXB		0x1eb
#घोषणा PPG_5GL1_TXA		0x1ec
#घोषणा PPG_2GM_TXAB		0x1ee
#घोषणा PPG_THERMAL_A		0x1ef
#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW8822B_H__
#घोषणा __RTW8822B_H__

#समावेश <यंत्र/byteorder.h>

#घोषणा RCR_VHT_ACK		BIT(26)

काष्ठा rtw8822bu_efuse अणु
	u8 res4[4];			/* 0xd0 */
	u8 usb_optional_function;
	u8 res5[0x1e];
	u8 res6[2];
	u8 serial[0x0b];		/* 0xf5 */
	u8 vid;				/* 0x100 */
	u8 res7;
	u8 pid;
	u8 res8[4];
	u8 mac_addr[ETH_ALEN];		/* 0x107 */
	u8 res9[2];
	u8 venकरोr_name[0x07];
	u8 res10[2];
	u8 device_name[0x14];
	u8 res11[0xcf];
	u8 package_type;		/* 0x1fb */
	u8 res12[0x4];
पूर्ण;

काष्ठा rtw8822be_efuse अणु
	u8 mac_addr[ETH_ALEN];		/* 0xd0 */
	u8 vender_id[2];
	u8 device_id[2];
	u8 sub_vender_id[2];
	u8 sub_device_id[2];
	u8 pmc[2];
	u8 exp_device_cap[2];
	u8 msi_cap;
	u8 ltr_cap;			/* 0xe3 */
	u8 exp_link_control[2];
	u8 link_cap[4];
	u8 link_control[2];
	u8 serial_number[8];
	u8 res0:2;			/* 0xf4 */
	u8 ltr_en:1;
	u8 res1:2;
	u8 obff:2;
	u8 res2:3;
	u8 obff_cap:2;
	u8 res3:4;
	u8 res4[3];
	u8 class_code[3];
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

काष्ठा rtw8822b_efuse अणु
	__le16 rtl_id;
	u8 res0[0x0e];

	/* घातer index क्रम four RF paths */
	काष्ठा rtw_txpwr_idx txpwr_idx_table[4];

	u8 channel_plan;		/* 0xb8 */
	u8 xtal_k;
	u8 thermal_meter;
	u8 iqk_lck;
	u8 pa_type;			/* 0xbc */
	u8 lna_type_2g[2];		/* 0xbd */
	u8 lna_type_5g[2];
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
	u8 res[3];
	जोड़ अणु
		काष्ठा rtw8822bu_efuse u;
		काष्ठा rtw8822be_efuse e;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम
_rtw_ग_लिखो32s_mask(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u32 data)
अणु
	/* 0xC00-0xCFF and 0xE00-0xEFF have the same layout */
	rtw_ग_लिखो32_mask(rtwdev, addr, mask, data);
	rtw_ग_लिखो32_mask(rtwdev, addr + 0x200, mask, data);
पूर्ण

#घोषणा rtw_ग_लिखो32s_mask(rtwdev, addr, mask, data)			       \
	करो अणु								       \
		BUILD_BUG_ON((addr) < 0xC00 || (addr) >= 0xD00);	       \
									       \
		_rtw_ग_लिखो32s_mask(rtwdev, addr, mask, data);		       \
	पूर्ण जबतक (0)

/* phy status page0 */
#घोषणा GET_PHY_STAT_P0_PWDB(phy_stat)                                         \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))

/* phy status page1 */
#घोषणा GET_PHY_STAT_P1_PWDB_A(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(15, 8))
#घोषणा GET_PHY_STAT_P1_PWDB_B(phy_stat)                                       \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x00), GENMASK(23, 16))
#घोषणा GET_PHY_STAT_P1_RF_MODE(phy_stat)                                      \
	le32_get_bits(*((__le32 *)(phy_stat) + 0x03), GENMASK(29, 28))
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

#घोषणा REG_HTSTFWT	0x800
#घोषणा REG_RXPSEL	0x808
#घोषणा BIT_RX_PSEL_RST		(BIT(28) | BIT(29))
#घोषणा REG_TXPSEL	0x80c
#घोषणा REG_RXCCAMSK	0x814
#घोषणा REG_CCASEL	0x82c
#घोषणा REG_PDMFTH	0x830
#घोषणा REG_CCA2ND	0x838
#घोषणा REG_L1WT	0x83c
#घोषणा REG_L1PKWT	0x840
#घोषणा REG_MRC		0x850
#घोषणा REG_CLKTRK	0x860
#घोषणा REG_ADCCLK	0x8ac
#घोषणा REG_ADC160	0x8c4
#घोषणा REG_ADC40	0x8c8
#घोषणा REG_CDDTXP	0x93c
#घोषणा REG_TXPSEL1	0x940
#घोषणा REG_ACBB0	0x948
#घोषणा REG_ACBBRXFIR	0x94c
#घोषणा REG_ACGG2TBL	0x958
#घोषणा REG_RXSB	0xa00
#घोषणा REG_ADCINI	0xa04
#घोषणा REG_TXSF2	0xa24
#घोषणा REG_TXSF6	0xa28
#घोषणा REG_RXDESC	0xa2c
#घोषणा REG_ENTXCCK	0xa80
#घोषणा REG_AGCTR_A	0xc08
#घोषणा REG_TXDFIR	0xc20
#घोषणा REG_RXIGI_A	0xc50
#घोषणा REG_TRSW	0xca0
#घोषणा REG_RFESEL0	0xcb0
#घोषणा REG_RFESEL8	0xcb4
#घोषणा REG_RFECTL	0xcb8
#घोषणा REG_RFEINV	0xcbc
#घोषणा REG_AGCTR_B	0xe08
#घोषणा REG_RXIGI_B	0xe50
#घोषणा REG_ANTWT	0x1904
#घोषणा REG_IQKFAILMSK	0x1bf0

#पूर्ण_अगर

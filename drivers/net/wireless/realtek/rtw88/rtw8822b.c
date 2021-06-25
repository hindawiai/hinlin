<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/module.h>
#समावेश "main.h"
#समावेश "coex.h"
#समावेश "fw.h"
#समावेश "tx.h"
#समावेश "rx.h"
#समावेश "phy.h"
#समावेश "rtw8822b.h"
#समावेश "rtw8822b_table.h"
#समावेश "mac.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "bf.h"

अटल व्योम rtw8822b_config_trx_mode(काष्ठा rtw_dev *rtwdev, u8 tx_path,
				     u8 rx_path, bool is_tx2_path);

अटल व्योम rtw8822be_efuse_parsing(काष्ठा rtw_efuse *efuse,
				    काष्ठा rtw8822b_efuse *map)
अणु
	ether_addr_copy(efuse->addr, map->e.mac_addr);
पूर्ण

अटल पूर्णांक rtw8822b_पढ़ो_efuse(काष्ठा rtw_dev *rtwdev, u8 *log_map)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw8822b_efuse *map;
	पूर्णांक i;

	map = (काष्ठा rtw8822b_efuse *)log_map;

	efuse->rfe_option = map->rfe_option;
	efuse->rf_board_option = map->rf_board_option;
	efuse->crystal_cap = map->xtal_k;
	efuse->pa_type_2g = map->pa_type;
	efuse->pa_type_5g = map->pa_type;
	efuse->lna_type_2g = map->lna_type_2g[0];
	efuse->lna_type_5g = map->lna_type_5g[0];
	efuse->channel_plan = map->channel_plan;
	efuse->country_code[0] = map->country_code[0];
	efuse->country_code[1] = map->country_code[1];
	efuse->bt_setting = map->rf_bt_setting;
	efuse->regd = map->rf_board_option & 0x7;
	efuse->thermal_meter[RF_PATH_A] = map->thermal_meter;
	efuse->thermal_meter_k = map->thermal_meter;

	क्रम (i = 0; i < 4; i++)
		efuse->txpwr_idx_table[i] = map->txpwr_idx_table[i];

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtw8822be_efuse_parsing(efuse, map);
		अवरोध;
	शेष:
		/* unsupported now */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtw8822b_phy_rfe_init(काष्ठा rtw_dev *rtwdev)
अणु
	/* chip top mux */
	rtw_ग_लिखो32_mask(rtwdev, 0x64, BIT(29) | BIT(28), 0x3);
	rtw_ग_लिखो32_mask(rtwdev, 0x4c, BIT(26) | BIT(25), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x40, BIT(2), 0x1);

	/* from s0 or s1 */
	rtw_ग_लिखो32_mask(rtwdev, 0x1990, 0x3f, 0x30);
	rtw_ग_लिखो32_mask(rtwdev, 0x1990, (BIT(11) | BIT(10)), 0x3);

	/* input or output */
	rtw_ग_लिखो32_mask(rtwdev, 0x974, 0x3f, 0x3f);
	rtw_ग_लिखो32_mask(rtwdev, 0x974, (BIT(11) | BIT(10)), 0x3);
पूर्ण

#घोषणा RTW_TXSCALE_SIZE 37
अटल स्थिर u32 rtw8822b_txscale_tbl[RTW_TXSCALE_SIZE] = अणु
	0x081, 0x088, 0x090, 0x099, 0x0a2, 0x0ac, 0x0b6, 0x0c0, 0x0cc, 0x0d8,
	0x0e5, 0x0f2, 0x101, 0x110, 0x120, 0x131, 0x143, 0x156, 0x16a, 0x180,
	0x197, 0x1af, 0x1c8, 0x1e3, 0x200, 0x21e, 0x23e, 0x261, 0x285, 0x2ab,
	0x2d3, 0x2fe, 0x32b, 0x35c, 0x38e, 0x3c4, 0x3fe
पूर्ण;

अटल u8 rtw8822b_get_swing_index(काष्ठा rtw_dev *rtwdev)
अणु
	u8 i = 0;
	u32 swing, table_value;

	swing = rtw_पढ़ो32_mask(rtwdev, 0xc1c, 0xffe00000);
	क्रम (i = 0; i < RTW_TXSCALE_SIZE; i++) अणु
		table_value = rtw8822b_txscale_tbl[i];
		अगर (swing == table_value)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम rtw8822b_pwrtrack_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 swing_idx = rtw8822b_get_swing_index(rtwdev);
	u8 path;

	अगर (swing_idx >= RTW_TXSCALE_SIZE)
		dm_info->शेष_ofdm_index = 24;
	अन्यथा
		dm_info->शेष_ofdm_index = swing_idx;

	क्रम (path = RF_PATH_A; path < rtwdev->hal.rf_path_num; path++) अणु
		ewma_thermal_init(&dm_info->avg_thermal[path]);
		dm_info->delta_घातer_index[path] = 0;
	पूर्ण
	dm_info->pwr_trk_triggered = false;
	dm_info->pwr_trk_init_trigger = true;
	dm_info->thermal_meter_k = rtwdev->efuse.thermal_meter_k;
पूर्ण

अटल व्योम rtw8822b_phy_bf_init(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_bf_phy_init(rtwdev);
	/* Grouping biपंचांगap parameters */
	rtw_ग_लिखो32(rtwdev, 0x1C94, 0xAFFFAFFF);
पूर्ण

अटल व्योम rtw8822b_phy_set_param(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 crystal_cap;
	bool is_tx2_path;

	/* घातer on BB/RF करोमुख्य */
	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN,
		       BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST);
	rtw_ग_लिखो8_set(rtwdev, REG_RF_CTRL,
		       BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	rtw_ग_लिखो32_set(rtwdev, REG_WLRF1, BIT_WLRF1_BBRF_EN);

	/* pre init beक्रमe header files config */
	rtw_ग_लिखो32_clr(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);

	rtw_phy_load_tables(rtwdev);

	crystal_cap = rtwdev->efuse.crystal_cap & 0x3F;
	rtw_ग_लिखो32_mask(rtwdev, 0x24, 0x7e000000, crystal_cap);
	rtw_ग_लिखो32_mask(rtwdev, 0x28, 0x7e, crystal_cap);

	/* post init after header files config */
	rtw_ग_लिखो32_set(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);

	is_tx2_path = false;
	rtw8822b_config_trx_mode(rtwdev, hal->antenna_tx, hal->antenna_rx,
				 is_tx2_path);
	rtw_phy_init(rtwdev);

	rtw8822b_phy_rfe_init(rtwdev);
	rtw8822b_pwrtrack_init(rtwdev);

	rtw8822b_phy_bf_init(rtwdev);
पूर्ण

#घोषणा WLAN_SLOT_TIME		0x09
#घोषणा WLAN_PIFS_TIME		0x19
#घोषणा WLAN_SIFS_CCK_CONT_TX	0xA
#घोषणा WLAN_SIFS_OFDM_CONT_TX	0xE
#घोषणा WLAN_SIFS_CCK_TRX	0x10
#घोषणा WLAN_SIFS_OFDM_TRX	0x10
#घोषणा WLAN_VO_TXOP_LIMIT	0x186 /* unit : 32us */
#घोषणा WLAN_VI_TXOP_LIMIT	0x3BC /* unit : 32us */
#घोषणा WLAN_RDG_NAV		0x05
#घोषणा WLAN_TXOP_NAV		0x1B
#घोषणा WLAN_CCK_RX_TSF		0x30
#घोषणा WLAN_OFDM_RX_TSF	0x30
#घोषणा WLAN_TBTT_PROHIBIT	0x04 /* unit : 32us */
#घोषणा WLAN_TBTT_HOLD_TIME	0x064 /* unit : 32us */
#घोषणा WLAN_DRV_EARLY_INT	0x04
#घोषणा WLAN_BCN_DMA_TIME	0x02

#घोषणा WLAN_RX_FILTER0		0x0FFFFFFF
#घोषणा WLAN_RX_FILTER2		0xFFFF
#घोषणा WLAN_RCR_CFG		0xE400220E
#घोषणा WLAN_RXPKT_MAX_SZ	12288
#घोषणा WLAN_RXPKT_MAX_SZ_512	(WLAN_RXPKT_MAX_SZ >> 9)

#घोषणा WLAN_AMPDU_MAX_TIME		0x70
#घोषणा WLAN_RTS_LEN_TH			0xFF
#घोषणा WLAN_RTS_TX_TIME_TH		0x08
#घोषणा WLAN_MAX_AGG_PKT_LIMIT		0x20
#घोषणा WLAN_RTS_MAX_AGG_PKT_LIMIT	0x20
#घोषणा FAST_EDCA_VO_TH		0x06
#घोषणा FAST_EDCA_VI_TH		0x06
#घोषणा FAST_EDCA_BE_TH		0x06
#घोषणा FAST_EDCA_BK_TH		0x06
#घोषणा WLAN_BAR_RETRY_LIMIT		0x01
#घोषणा WLAN_RA_TRY_RATE_AGG_LIMIT	0x08

#घोषणा WLAN_TX_FUNC_CFG1		0x30
#घोषणा WLAN_TX_FUNC_CFG2		0x30
#घोषणा WLAN_MAC_OPT_NORM_FUNC1		0x98
#घोषणा WLAN_MAC_OPT_LB_FUNC1		0x80
#घोषणा WLAN_MAC_OPT_FUNC2		0x30810041

#घोषणा WLAN_SIFS_CFG	(WLAN_SIFS_CCK_CONT_TX | \
			(WLAN_SIFS_OFDM_CONT_TX << BIT_SHIFT_SIFS_OFDM_CTX) | \
			(WLAN_SIFS_CCK_TRX << BIT_SHIFT_SIFS_CCK_TRX) | \
			(WLAN_SIFS_OFDM_TRX << BIT_SHIFT_SIFS_OFDM_TRX))

#घोषणा WLAN_TBTT_TIME	(WLAN_TBTT_PROHIBIT |\
			(WLAN_TBTT_HOLD_TIME << BIT_SHIFT_TBTT_HOLD_TIME_AP))

#घोषणा WLAN_NAV_CFG		(WLAN_RDG_NAV | (WLAN_TXOP_NAV << 16))
#घोषणा WLAN_RX_TSF_CFG		(WLAN_CCK_RX_TSF | (WLAN_OFDM_RX_TSF) << 8)

अटल पूर्णांक rtw8822b_mac_init(काष्ठा rtw_dev *rtwdev)
अणु
	u32 value32;

	/* protocol configuration */
	rtw_ग_लिखो8_clr(rtwdev, REG_SW_AMPDU_BURST_MODE_CTRL, BIT_PRE_TX_CMD);
	rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME_V1, WLAN_AMPDU_MAX_TIME);
	rtw_ग_लिखो8_set(rtwdev, REG_TX_HANG_CTRL, BIT_EN_खातापूर्ण_V1);
	value32 = WLAN_RTS_LEN_TH | (WLAN_RTS_TX_TIME_TH << 8) |
		  (WLAN_MAX_AGG_PKT_LIMIT << 16) |
		  (WLAN_RTS_MAX_AGG_PKT_LIMIT << 24);
	rtw_ग_लिखो32(rtwdev, REG_PROT_MODE_CTRL, value32);
	rtw_ग_लिखो16(rtwdev, REG_BAR_MODE_CTRL + 2,
		    WLAN_BAR_RETRY_LIMIT | WLAN_RA_TRY_RATE_AGG_LIMIT << 8);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_VOVI_SETTING, FAST_EDCA_VO_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_VOVI_SETTING + 2, FAST_EDCA_VI_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_BEBK_SETTING, FAST_EDCA_BE_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_BEBK_SETTING + 2, FAST_EDCA_BK_TH);
	/* EDCA configuration */
	rtw_ग_लिखो8_clr(rtwdev, REG_TIMER0_SRC_SEL, BIT_TSFT_SEL_TIMER0);
	rtw_ग_लिखो16(rtwdev, REG_TXPAUSE, 0x0000);
	rtw_ग_लिखो8(rtwdev, REG_SLOT, WLAN_SLOT_TIME);
	rtw_ग_लिखो8(rtwdev, REG_PIFS, WLAN_PIFS_TIME);
	rtw_ग_लिखो32(rtwdev, REG_SIFS, WLAN_SIFS_CFG);
	rtw_ग_लिखो16(rtwdev, REG_EDCA_VO_PARAM + 2, WLAN_VO_TXOP_LIMIT);
	rtw_ग_लिखो16(rtwdev, REG_EDCA_VI_PARAM + 2, WLAN_VI_TXOP_LIMIT);
	rtw_ग_लिखो32(rtwdev, REG_RD_NAV_NXT, WLAN_NAV_CFG);
	rtw_ग_लिखो16(rtwdev, REG_RXTSF_OFFSET_CCK, WLAN_RX_TSF_CFG);
	/* Set beacon cotnrol - enable TSF and other related functions */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);
	/* Set send beacon related रेजिस्टरs */
	rtw_ग_लिखो32(rtwdev, REG_TBTT_PROHIBIT, WLAN_TBTT_TIME);
	rtw_ग_लिखो8(rtwdev, REG_DRVERLYINT, WLAN_DRV_EARLY_INT);
	rtw_ग_लिखो8(rtwdev, REG_BCNDMATIM, WLAN_BCN_DMA_TIME);
	rtw_ग_लिखो8_clr(rtwdev, REG_TX_PTCL_CTRL + 1, BIT_SIFS_BK_EN >> 8);
	/* WMAC configuration */
	rtw_ग_लिखो32(rtwdev, REG_RXFLTMAP0, WLAN_RX_FILTER0);
	rtw_ग_लिखो16(rtwdev, REG_RXFLTMAP2, WLAN_RX_FILTER2);
	rtw_ग_लिखो32(rtwdev, REG_RCR, WLAN_RCR_CFG);
	rtw_ग_लिखो8(rtwdev, REG_RX_PKT_LIMIT, WLAN_RXPKT_MAX_SZ_512);
	rtw_ग_लिखो8(rtwdev, REG_TCR + 2, WLAN_TX_FUNC_CFG2);
	rtw_ग_लिखो8(rtwdev, REG_TCR + 1, WLAN_TX_FUNC_CFG1);
	rtw_ग_लिखो32(rtwdev, REG_WMAC_OPTION_FUNCTION + 8, WLAN_MAC_OPT_FUNC2);
	rtw_ग_लिखो8(rtwdev, REG_WMAC_OPTION_FUNCTION + 4, WLAN_MAC_OPT_NORM_FUNC1);

	वापस 0;
पूर्ण

अटल व्योम rtw8822b_set_channel_rfe_efem(काष्ठा rtw_dev *rtwdev, u8 channel)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	अगर (IS_CH_2G_BAND(channel)) अणु
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x705770);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x57);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFECTL, BIT(4), 0);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x177517);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x75);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFECTL, BIT(5), 0);
	पूर्ण

	rtw_ग_लिखो32s_mask(rtwdev, REG_RFEINV, BIT(11) | BIT(10) | 0x3f, 0x0);

	अगर (hal->antenna_rx == BB_PATH_AB ||
	    hal->antenna_tx == BB_PATH_AB) अणु
		/* 2TX or 2RX */
		rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa501);
	पूर्ण अन्यथा अगर (hal->antenna_rx == hal->antenna_tx) अणु
		/* TXA+RXA or TXB+RXB */
		rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa500);
	पूर्ण अन्यथा अणु
		/* TXB+RXA or TXA+RXB */
		rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa005);
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_set_channel_rfe_अगरem(काष्ठा rtw_dev *rtwdev, u8 channel)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	अगर (IS_CH_2G_BAND(channel)) अणु
		/* संकेत source */
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x745774);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x57);
	पूर्ण अन्यथा अणु
		/* संकेत source */
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL0, 0xffffff, 0x477547);
		rtw_ग_लिखो32s_mask(rtwdev, REG_RFESEL8, MASKBYTE1, 0x75);
	पूर्ण

	rtw_ग_लिखो32s_mask(rtwdev, REG_RFEINV, BIT(11) | BIT(10) | 0x3f, 0x0);

	अगर (IS_CH_2G_BAND(channel)) अणु
		अगर (hal->antenna_rx == BB_PATH_AB ||
		    hal->antenna_tx == BB_PATH_AB) अणु
			/* 2TX or 2RX */
			rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa501);
		पूर्ण अन्यथा अगर (hal->antenna_rx == hal->antenna_tx) अणु
			/* TXA+RXA or TXB+RXB */
			rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa500);
		पूर्ण अन्यथा अणु
			/* TXB+RXA or TXA+RXB */
			rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa005);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32s_mask(rtwdev, REG_TRSW, MASKLWORD, 0xa5a5);
	पूर्ण
पूर्ण

क्रमागत अणु
	CCUT_IDX_1R_2G,
	CCUT_IDX_2R_2G,
	CCUT_IDX_1R_5G,
	CCUT_IDX_2R_5G,
	CCUT_IDX_NR,
पूर्ण;

काष्ठा cca_ccut अणु
	u32 reg82c[CCUT_IDX_NR];
	u32 reg830[CCUT_IDX_NR];
	u32 reg838[CCUT_IDX_NR];
पूर्ण;

अटल स्थिर काष्ठा cca_ccut cca_अगरem_ccut = अणु
	अणु0x75C97010, 0x75C97010, 0x75C97010, 0x75C97010पूर्ण, /*Reg82C*/
	अणु0x79a0eaaa, 0x79A0EAAC, 0x79a0eaaa, 0x79a0eaaaपूर्ण, /*Reg830*/
	अणु0x87765541, 0x87746341, 0x87765541, 0x87746341पूर्ण, /*Reg838*/
पूर्ण;

अटल स्थिर काष्ठा cca_ccut cca_efem_ccut = अणु
	अणु0x75B86010, 0x75B76010, 0x75B86010, 0x75B76010पूर्ण, /*Reg82C*/
	अणु0x79A0EAA8, 0x79A0EAAC, 0x79A0EAA8, 0x79a0eaaaपूर्ण, /*Reg830*/
	अणु0x87766451, 0x87766431, 0x87766451, 0x87766431पूर्ण, /*Reg838*/
पूर्ण;

अटल स्थिर काष्ठा cca_ccut cca_अगरem_ccut_ext = अणु
	अणु0x75da8010, 0x75da8010, 0x75da8010, 0x75da8010पूर्ण, /*Reg82C*/
	अणु0x79a0eaaa, 0x97A0EAAC, 0x79a0eaaa, 0x79a0eaaaपूर्ण, /*Reg830*/
	अणु0x87765541, 0x86666341, 0x87765561, 0x86666361पूर्ण, /*Reg838*/
पूर्ण;

अटल व्योम rtw8822b_get_cca_val(स्थिर काष्ठा cca_ccut *cca_ccut, u8 col,
				 u32 *reg82c, u32 *reg830, u32 *reg838)
अणु
	*reg82c = cca_ccut->reg82c[col];
	*reg830 = cca_ccut->reg830[col];
	*reg838 = cca_ccut->reg838[col];
पूर्ण

काष्ठा rtw8822b_rfe_info अणु
	स्थिर काष्ठा cca_ccut *cca_ccut_2g;
	स्थिर काष्ठा cca_ccut *cca_ccut_5g;
	क्रमागत rtw_rfe_fem fem;
	bool अगरem_ext;
	व्योम (*rtw_set_channel_rfe)(काष्ठा rtw_dev *rtwdev, u8 channel);
पूर्ण;

#घोषणा I2GE5G_CCUT(set_ch) अणु						\
	.cca_ccut_2g = &cca_अगरem_ccut,					\
	.cca_ccut_5g = &cca_efem_ccut,					\
	.fem = RTW_RFE_IFEM2G_EFEM5G,					\
	.अगरem_ext = false,						\
	.rtw_set_channel_rfe = &rtw8822b_set_channel_rfe_ ## set_ch,	\
	पूर्ण
#घोषणा IFEM_EXT_CCUT(set_ch) अणु						\
	.cca_ccut_2g = &cca_अगरem_ccut_ext,				\
	.cca_ccut_5g = &cca_अगरem_ccut_ext,				\
	.fem = RTW_RFE_IFEM,						\
	.अगरem_ext = true,						\
	.rtw_set_channel_rfe = &rtw8822b_set_channel_rfe_ ## set_ch,	\
	पूर्ण

अटल स्थिर काष्ठा rtw8822b_rfe_info rtw8822b_rfe_info[] = अणु
	[2] = I2GE5G_CCUT(efem),
	[3] = IFEM_EXT_CCUT(अगरem),
	[5] = IFEM_EXT_CCUT(अगरem),
पूर्ण;

अटल व्योम rtw8822b_set_channel_cca(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				     स्थिर काष्ठा rtw8822b_rfe_info *rfe_info)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	स्थिर काष्ठा cca_ccut *cca_ccut;
	u8 col;
	u32 reg82c, reg830, reg838;
	bool is_efem_cca = false, is_अगरem_cca = false, is_rfe_type = false;

	अगर (IS_CH_2G_BAND(channel)) अणु
		cca_ccut = rfe_info->cca_ccut_2g;

		अगर (hal->antenna_rx == BB_PATH_A ||
		    hal->antenna_rx == BB_PATH_B)
			col = CCUT_IDX_1R_2G;
		अन्यथा
			col = CCUT_IDX_2R_2G;
	पूर्ण अन्यथा अणु
		cca_ccut = rfe_info->cca_ccut_5g;

		अगर (hal->antenna_rx == BB_PATH_A ||
		    hal->antenna_rx == BB_PATH_B)
			col = CCUT_IDX_1R_5G;
		अन्यथा
			col = CCUT_IDX_2R_5G;
	पूर्ण

	rtw8822b_get_cca_val(cca_ccut, col, &reg82c, &reg830, &reg838);

	चयन (rfe_info->fem) अणु
	हाल RTW_RFE_IFEM:
	शेष:
		is_अगरem_cca = true;
		अगर (rfe_info->अगरem_ext)
			is_rfe_type = true;
		अवरोध;
	हाल RTW_RFE_EFEM:
		is_efem_cca = true;
		अवरोध;
	हाल RTW_RFE_IFEM2G_EFEM5G:
		अगर (IS_CH_2G_BAND(channel))
			is_अगरem_cca = true;
		अन्यथा
			is_efem_cca = true;
		अवरोध;
	पूर्ण

	अगर (is_अगरem_cca) अणु
		अगर ((hal->cut_version == RTW_CHIP_VER_CUT_B &&
		     (col == CCUT_IDX_2R_2G || col == CCUT_IDX_2R_5G) &&
		     bw == RTW_CHANNEL_WIDTH_40) ||
		    (!is_rfe_type && col == CCUT_IDX_2R_5G &&
		     bw == RTW_CHANNEL_WIDTH_40) ||
		    (efuse->rfe_option == 5 && col == CCUT_IDX_2R_5G))
			reg830 = 0x79a0ea28;
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_CCASEL, MASKDWORD, reg82c);
	rtw_ग_लिखो32_mask(rtwdev, REG_PDMFTH, MASKDWORD, reg830);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCA2ND, MASKDWORD, reg838);

	अगर (is_efem_cca && !(hal->cut_version == RTW_CHIP_VER_CUT_B))
		rtw_ग_लिखो32_mask(rtwdev, REG_L1WT, MASKDWORD, 0x9194b2b9);

	अगर (bw == RTW_CHANNEL_WIDTH_20 && IS_CH_5G_BAND_MID(channel))
		rtw_ग_लिखो32_mask(rtwdev, REG_CCA2ND, 0xf0, 0x4);
पूर्ण

अटल स्थिर u8 low_band[15] = अणु0x7, 0x6, 0x6, 0x5, 0x0, 0x0, 0x7, 0xff, 0x6,
				0x5, 0x0, 0x0, 0x7, 0x6, 0x6पूर्ण;
अटल स्थिर u8 middle_band[23] = अणु0x6, 0x5, 0x0, 0x0, 0x7, 0x6, 0x6, 0xff, 0x0,
				   0x0, 0x7, 0x6, 0x6, 0x5, 0x0, 0xff, 0x7, 0x6,
				   0x6, 0x5, 0x0, 0x0, 0x7पूर्ण;
अटल स्थिर u8 high_band[15] = अणु0x5, 0x5, 0x0, 0x7, 0x7, 0x6, 0x5, 0xff, 0x0,
				 0x7, 0x7, 0x6, 0x5, 0x5, 0x0पूर्ण;

अटल व्योम rtw8822b_set_channel_rf(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw)
अणु
#घोषणा RF18_BAND_MASK		(BIT(16) | BIT(9) | BIT(8))
#घोषणा RF18_BAND_2G		(0)
#घोषणा RF18_BAND_5G		(BIT(16) | BIT(8))
#घोषणा RF18_CHANNEL_MASK	(MASKBYTE0)
#घोषणा RF18_RFSI_MASK		(BIT(18) | BIT(17))
#घोषणा RF18_RFSI_GE_CH80	(BIT(17))
#घोषणा RF18_RFSI_GT_CH144	(BIT(18))
#घोषणा RF18_BW_MASK		(BIT(11) | BIT(10))
#घोषणा RF18_BW_20M		(BIT(11) | BIT(10))
#घोषणा RF18_BW_40M		(BIT(11))
#घोषणा RF18_BW_80M		(BIT(10))
#घोषणा RFBE_MASK		(BIT(17) | BIT(16) | BIT(15))

	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u32 rf_reg18, rf_reg_be;

	rf_reg18 = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK);

	rf_reg18 &= ~(RF18_BAND_MASK | RF18_CHANNEL_MASK | RF18_RFSI_MASK |
		      RF18_BW_MASK);

	rf_reg18 |= (IS_CH_2G_BAND(channel) ? RF18_BAND_2G : RF18_BAND_5G);
	rf_reg18 |= (channel & RF18_CHANNEL_MASK);
	अगर (channel > 144)
		rf_reg18 |= RF18_RFSI_GT_CH144;
	अन्यथा अगर (channel >= 80)
		rf_reg18 |= RF18_RFSI_GE_CH80;

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_5:
	हाल RTW_CHANNEL_WIDTH_10:
	हाल RTW_CHANNEL_WIDTH_20:
	शेष:
		rf_reg18 |= RF18_BW_20M;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		rf_reg18 |= RF18_BW_40M;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		rf_reg18 |= RF18_BW_80M;
		अवरोध;
	पूर्ण

	अगर (IS_CH_2G_BAND(channel))
		rf_reg_be = 0x0;
	अन्यथा अगर (IS_CH_5G_BAND_1(channel) || IS_CH_5G_BAND_2(channel))
		rf_reg_be = low_band[(channel - 36) >> 1];
	अन्यथा अगर (IS_CH_5G_BAND_3(channel))
		rf_reg_be = middle_band[(channel - 100) >> 1];
	अन्यथा अगर (IS_CH_5G_BAND_4(channel))
		rf_reg_be = high_band[(channel - 149) >> 1];
	अन्यथा
		जाओ err;

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_MALSEL, RFBE_MASK, rf_reg_be);

	/* need to set 0xdf[18]=1 beक्रमe writing RF18 when channel 144 */
	अगर (channel == 144)
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTDBG, BIT(18), 0x1);
	अन्यथा
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTDBG, BIT(18), 0x0);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK, rf_reg18);
	अगर (hal->rf_type > RF_1T1R)
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, 0x18, RFREG_MASK, rf_reg18);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_XTALX2, BIT(19), 0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_XTALX2, BIT(19), 1);

	वापस;

err:
	WARN_ON(1);
पूर्ण

अटल व्योम rtw8822b_toggle_igi(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u32 igi;

	igi = rtw_पढ़ो32_mask(rtwdev, REG_RXIGI_A, 0x7f);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI_A, 0x7f, igi - 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI_A, 0x7f, igi);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI_B, 0x7f, igi - 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI_B, 0x7f, igi);

	rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, MASKBYTE0, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, MASKBYTE0,
			 hal->antenna_rx | (hal->antenna_rx << 4));
पूर्ण

अटल व्योम rtw8822b_set_channel_rxdfir(काष्ठा rtw_dev *rtwdev, u8 bw)
अणु
	अगर (bw == RTW_CHANNEL_WIDTH_40) अणु
		/* RX DFIR क्रम BW40 */
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x0);
		rtw_ग_लिखो32s_mask(rtwdev, REG_TXDFIR, BIT(31), 0x0);
	पूर्ण अन्यथा अगर (bw == RTW_CHANNEL_WIDTH_80) अणु
		/* RX DFIR क्रम BW80 */
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x1);
		rtw_ग_लिखो32s_mask(rtwdev, REG_TXDFIR, BIT(31), 0x0);
	पूर्ण अन्यथा अणु
		/* RX DFIR क्रम BW20, BW10 and BW5*/
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32s_mask(rtwdev, REG_TXDFIR, BIT(31), 0x1);
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_set_channel_bb(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				    u8 primary_ch_idx)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 rfe_option = efuse->rfe_option;
	u32 val32;

	अगर (IS_CH_2G_BAND(channel)) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 15);

		rtw_ग_लिखो32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x96a);
		अगर (channel == 14) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF2, MASKDWORD, 0x00006577);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF6, MASKLWORD, 0x0000);
		पूर्ण अन्यथा अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF2, MASKDWORD, 0x384f6577);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF6, MASKLWORD, 0x1525);
		पूर्ण

		rtw_ग_लिखो32_mask(rtwdev, REG_RFEINV, 0x300, 0x2);
	पूर्ण अन्यथा अगर (IS_CH_5G_BAND(channel)) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 34);

		अगर (IS_CH_5G_BAND_1(channel) || IS_CH_5G_BAND_2(channel))
			rtw_ग_लिखो32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x1);
		अन्यथा अगर (IS_CH_5G_BAND_3(channel))
			rtw_ग_लिखो32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x2);
		अन्यथा अगर (IS_CH_5G_BAND_4(channel))
			rtw_ग_लिखो32_mask(rtwdev, REG_ACGG2TBL, 0x1f, 0x3);

		अगर (IS_CH_5G_BAND_1(channel))
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x494);
		अन्यथा अगर (IS_CH_5G_BAND_2(channel))
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x453);
		अन्यथा अगर (channel >= 100 && channel <= 116)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x452);
		अन्यथा अगर (channel >= 118 && channel <= 177)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x412);

		rtw_ग_लिखो32_mask(rtwdev, 0xcbc, 0x300, 0x1);
	पूर्ण

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_20:
	शेष:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFFCFFC00;
		val32 |= (RTW_CHANNEL_WIDTH_20);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		अगर (primary_ch_idx == RTW_SC_20_UPPER)
			rtw_ग_लिखो32_set(rtwdev, REG_RXSB, BIT(4));
		अन्यथा
			rtw_ग_लिखो32_clr(rtwdev, REG_RXSB, BIT(4));

		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFF3FF300;
		val32 |= (((primary_ch_idx & 0xf) << 2) | RTW_CHANNEL_WIDTH_40);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xFCEFCF00;
		val32 |= (((primary_ch_idx & 0xf) << 2) | RTW_CHANNEL_WIDTH_80);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);

		अगर (rfe_option == 2 || rfe_option == 3) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_L1PKWT, 0x0000f000, 0x6);
			rtw_ग_लिखो32_mask(rtwdev, REG_ADC40, BIT(10), 0x1);
		पूर्ण
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_5:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xEFEEFE00;
		val32 |= ((BIT(6) | RTW_CHANNEL_WIDTH_20));
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_10:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xEFFEFF00;
		val32 |= ((BIT(7) | RTW_CHANNEL_WIDTH_20));
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_set_channel(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				 u8 primary_chan_idx)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	स्थिर काष्ठा rtw8822b_rfe_info *rfe_info;

	अगर (WARN(efuse->rfe_option >= ARRAY_SIZE(rtw8822b_rfe_info),
		 "rfe_option %d is out of boundary\n", efuse->rfe_option))
		वापस;

	rfe_info = &rtw8822b_rfe_info[efuse->rfe_option];

	rtw8822b_set_channel_bb(rtwdev, channel, bw, primary_chan_idx);
	rtw_set_channel_mac(rtwdev, channel, bw, primary_chan_idx);
	rtw8822b_set_channel_rf(rtwdev, channel, bw);
	rtw8822b_set_channel_rxdfir(rtwdev, bw);
	rtw8822b_toggle_igi(rtwdev);
	rtw8822b_set_channel_cca(rtwdev, channel, bw, rfe_info);
	(*rfe_info->rtw_set_channel_rfe)(rtwdev, channel);
पूर्ण

अटल व्योम rtw8822b_config_trx_mode(काष्ठा rtw_dev *rtwdev, u8 tx_path,
				     u8 rx_path, bool is_tx2_path)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	स्थिर काष्ठा rtw8822b_rfe_info *rfe_info;
	u8 ch = rtwdev->hal.current_channel;
	u8 tx_path_sel, rx_path_sel;
	पूर्णांक counter;

	अगर (WARN(efuse->rfe_option >= ARRAY_SIZE(rtw8822b_rfe_info),
		 "rfe_option %d is out of boundary\n", efuse->rfe_option))
		वापस;

	rfe_info = &rtw8822b_rfe_info[efuse->rfe_option];

	अगर ((tx_path | rx_path) & BB_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCTR_A, MASKLWORD, 0x3231);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCTR_A, MASKLWORD, 0x1111);

	अगर ((tx_path | rx_path) & BB_PATH_B)
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCTR_B, MASKLWORD, 0x3231);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCTR_B, MASKLWORD, 0x1111);

	rtw_ग_लिखो32_mask(rtwdev, REG_CDDTXP, (BIT(19) | BIT(18)), 0x3);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXPSEL, (BIT(29) | BIT(28)), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXPSEL, BIT(30), 0x1);

	अगर (tx_path & BB_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_CDDTXP, 0xfff00000, 0x001);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCINI, 0xf0000000, 0x8);
	पूर्ण अन्यथा अगर (tx_path & BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_CDDTXP, 0xfff00000, 0x002);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCINI, 0xf0000000, 0x4);
	पूर्ण

	अगर (tx_path == BB_PATH_A || tx_path == BB_PATH_B)
		rtw_ग_लिखो32_mask(rtwdev, REG_TXPSEL1, 0xfff0, 0x01);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_TXPSEL1, 0xfff0, 0x43);

	tx_path_sel = (tx_path << 4) | tx_path;
	rtw_ग_लिखो32_mask(rtwdev, REG_TXPSEL, MASKBYTE0, tx_path_sel);

	अगर (tx_path != BB_PATH_A && tx_path != BB_PATH_B) अणु
		अगर (is_tx2_path || rtwdev->mp_mode) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_CDDTXP, 0xfff00000, 0x043);
			rtw_ग_लिखो32_mask(rtwdev, REG_ADCINI, 0xf0000000, 0xc);
		पूर्ण
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_RXDESC, BIT(22), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXDESC, BIT(18), 0x0);

	अगर (rx_path & BB_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCINI, 0x0f000000, 0x0);
	अन्यथा अगर (rx_path & BB_PATH_B)
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCINI, 0x0f000000, 0x5);

	rx_path_sel = (rx_path << 4) | rx_path;
	rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, MASKBYTE0, rx_path_sel);

	अगर (rx_path == BB_PATH_A || rx_path == BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTWT, BIT(16), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_HTSTFWT, BIT(28), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_MRC, BIT(23), 0x0);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTWT, BIT(16), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_HTSTFWT, BIT(28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_MRC, BIT(23), 0x1);
	पूर्ण

	क्रम (counter = 100; counter > 0; counter--) अणु
		u32 rf_reg33;

		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE, RFREG_MASK, 0x80000);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, RFREG_MASK, 0x00001);

		udelay(2);
		rf_reg33 = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x33, RFREG_MASK);

		अगर (rf_reg33 == 0x00001)
			अवरोध;
	पूर्ण

	अगर (WARN(counter <= 0, "write RF mode table fail\n"))
		वापस;

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE, RFREG_MASK, 0x80000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, RFREG_MASK, 0x00001);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD1, RFREG_MASK, 0x00034);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD0, RFREG_MASK, 0x4080c);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE, RFREG_MASK, 0x00000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE, RFREG_MASK, 0x00000);

	rtw8822b_toggle_igi(rtwdev);
	rtw8822b_set_channel_cca(rtwdev, 1, RTW_CHANNEL_WIDTH_20, rfe_info);
	(*rfe_info->rtw_set_channel_rfe)(rtwdev, ch);
पूर्ण

अटल व्योम query_phy_status_page0(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 min_rx_घातer = -120;
	u8 pwdb = GET_PHY_STAT_P0_PWDB(phy_status);

	/* 8822B uses only 1 antenna to RX CCK rates */
	pkt_stat->rx_घातer[RF_PATH_A] = pwdb - 110;
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 1);
	pkt_stat->bw = RTW_CHANNEL_WIDTH_20;
	pkt_stat->संकेत_घातer = max(pkt_stat->rx_घातer[RF_PATH_A],
				     min_rx_घातer);
	dm_info->rssi[RF_PATH_A] = pkt_stat->rssi;
पूर्ण

अटल व्योम query_phy_status_page1(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 rxsc, bw;
	s8 min_rx_घातer = -120;
	s8 rx_evm;
	u8 evm_dbm = 0;
	u8 rssi;
	पूर्णांक path;

	अगर (pkt_stat->rate > DESC_RATE11M && pkt_stat->rate < DESC_RATEMCS0)
		rxsc = GET_PHY_STAT_P1_L_RXSC(phy_status);
	अन्यथा
		rxsc = GET_PHY_STAT_P1_HT_RXSC(phy_status);

	अगर (rxsc >= 1 && rxsc <= 8)
		bw = RTW_CHANNEL_WIDTH_20;
	अन्यथा अगर (rxsc >= 9 && rxsc <= 12)
		bw = RTW_CHANNEL_WIDTH_40;
	अन्यथा अगर (rxsc >= 13)
		bw = RTW_CHANNEL_WIDTH_80;
	अन्यथा
		bw = GET_PHY_STAT_P1_RF_MODE(phy_status);

	pkt_stat->rx_घातer[RF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->rx_घातer[RF_PATH_B] = GET_PHY_STAT_P1_PWDB_B(phy_status) - 110;
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 2);
	pkt_stat->bw = bw;
	pkt_stat->संकेत_घातer = max3(pkt_stat->rx_घातer[RF_PATH_A],
				      pkt_stat->rx_घातer[RF_PATH_B],
				      min_rx_घातer);

	dm_info->curr_rx_rate = pkt_stat->rate;

	pkt_stat->rx_evm[RF_PATH_A] = GET_PHY_STAT_P1_RXEVM_A(phy_status);
	pkt_stat->rx_evm[RF_PATH_B] = GET_PHY_STAT_P1_RXEVM_B(phy_status);

	pkt_stat->rx_snr[RF_PATH_A] = GET_PHY_STAT_P1_RXSNR_A(phy_status);
	pkt_stat->rx_snr[RF_PATH_B] = GET_PHY_STAT_P1_RXSNR_B(phy_status);

	pkt_stat->cfo_tail[RF_PATH_A] = GET_PHY_STAT_P1_CFO_TAIL_A(phy_status);
	pkt_stat->cfo_tail[RF_PATH_B] = GET_PHY_STAT_P1_CFO_TAIL_B(phy_status);

	क्रम (path = 0; path <= rtwdev->hal.rf_path_num; path++) अणु
		rssi = rtw_phy_rf_घातer_2_rssi(&pkt_stat->rx_घातer[path], 1);
		dm_info->rssi[path] = rssi;
		dm_info->rx_snr[path] = pkt_stat->rx_snr[path] >> 1;
		dm_info->cfo_tail[path] = (pkt_stat->cfo_tail[path] * 5) >> 1;

		rx_evm = pkt_stat->rx_evm[path];

		अगर (rx_evm < 0) अणु
			अगर (rx_evm == S8_MIN)
				evm_dbm = 0;
			अन्यथा
				evm_dbm = ((u8)-rx_evm >> 1);
		पूर्ण
		dm_info->rx_evm_dbm[path] = evm_dbm;
	पूर्ण
पूर्ण

अटल व्योम query_phy_status(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
			     काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	u8 page;

	page = *phy_status & 0xf;

	चयन (page) अणु
	हाल 0:
		query_phy_status_page0(rtwdev, phy_status, pkt_stat);
		अवरोध;
	हाल 1:
		query_phy_status_page1(rtwdev, phy_status, pkt_stat);
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "unused phy status page (%d)\n", page);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_query_rx_desc(काष्ठा rtw_dev *rtwdev, u8 *rx_desc,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat,
				   काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u32 desc_sz = rtwdev->chip->rx_pkt_desc_sz;
	u8 *phy_status = शून्य;

	स_रखो(pkt_stat, 0, माप(*pkt_stat));

	pkt_stat->phy_status = GET_RX_DESC_PHYST(rx_desc);
	pkt_stat->icv_err = GET_RX_DESC_ICV_ERR(rx_desc);
	pkt_stat->crc_err = GET_RX_DESC_CRC32(rx_desc);
	pkt_stat->decrypted = !GET_RX_DESC_SWDEC(rx_desc) &&
			      GET_RX_DESC_ENC_TYPE(rx_desc) != RX_DESC_ENC_NONE;
	pkt_stat->is_c2h = GET_RX_DESC_C2H(rx_desc);
	pkt_stat->pkt_len = GET_RX_DESC_PKT_LEN(rx_desc);
	pkt_stat->drv_info_sz = GET_RX_DESC_DRV_INFO_SIZE(rx_desc);
	pkt_stat->shअगरt = GET_RX_DESC_SHIFT(rx_desc);
	pkt_stat->rate = GET_RX_DESC_RX_RATE(rx_desc);
	pkt_stat->cam_id = GET_RX_DESC_MACID(rx_desc);
	pkt_stat->ppdu_cnt = GET_RX_DESC_PPDU_CNT(rx_desc);
	pkt_stat->tsf_low = GET_RX_DESC_TSFL(rx_desc);

	/* drv_info_sz is in unit of 8-bytes */
	pkt_stat->drv_info_sz *= 8;

	/* c2h cmd pkt's rx/phy status is not पूर्णांकerested */
	अगर (pkt_stat->is_c2h)
		वापस;

	hdr = (काष्ठा ieee80211_hdr *)(rx_desc + desc_sz + pkt_stat->shअगरt +
				       pkt_stat->drv_info_sz);
	अगर (pkt_stat->phy_status) अणु
		phy_status = rx_desc + desc_sz + pkt_stat->shअगरt;
		query_phy_status(rtwdev, phy_status, pkt_stat);
	पूर्ण

	rtw_rx_fill_rx_status(rtwdev, pkt_stat, hdr, rx_status, phy_status);
पूर्ण

अटल व्योम
rtw8822b_set_tx_घातer_index_by_rate(काष्ठा rtw_dev *rtwdev, u8 path, u8 rs)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	अटल स्थिर u32 offset_txagc[2] = अणु0x1d00, 0x1d80पूर्ण;
	अटल u32 phy_pwr_idx;
	u8 rate, rate_idx, pwr_index, shअगरt;
	पूर्णांक j;

	क्रम (j = 0; j < rtw_rate_size[rs]; j++) अणु
		rate = rtw_rate_section[rs][j];
		pwr_index = hal->tx_pwr_tbl[path][rate];
		shअगरt = rate & 0x3;
		phy_pwr_idx |= ((u32)pwr_index << (shअगरt * 8));
		अगर (shअगरt == 0x3) अणु
			rate_idx = rate & 0xfc;
			rtw_ग_लिखो32(rtwdev, offset_txagc[path] + rate_idx,
				    phy_pwr_idx);
			phy_pwr_idx = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_set_tx_घातer_index(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	पूर्णांक rs, path;

	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		क्रम (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++)
			rtw8822b_set_tx_घातer_index_by_rate(rtwdev, path, rs);
	पूर्ण
पूर्ण

अटल bool rtw8822b_check_rf_path(u8 antenna)
अणु
	चयन (antenna) अणु
	हाल BB_PATH_A:
	हाल BB_PATH_B:
	हाल BB_PATH_AB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक rtw8822b_set_antenna(काष्ठा rtw_dev *rtwdev,
				u32 antenna_tx,
				u32 antenna_rx)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	rtw_dbg(rtwdev, RTW_DBG_PHY, "config RF path, tx=0x%x rx=0x%x\n",
		antenna_tx, antenna_rx);

	अगर (!rtw8822b_check_rf_path(antenna_tx)) अणु
		rtw_info(rtwdev, "unsupported tx path 0x%x\n", antenna_tx);
		वापस -EINVAL;
	पूर्ण

	अगर (!rtw8822b_check_rf_path(antenna_rx)) अणु
		rtw_info(rtwdev, "unsupported rx path 0x%x\n", antenna_rx);
		वापस -EINVAL;
	पूर्ण

	hal->antenna_tx = antenna_tx;
	hal->antenna_rx = antenna_rx;

	rtw8822b_config_trx_mode(rtwdev, antenna_tx, antenna_rx, false);

	वापस 0;
पूर्ण

अटल व्योम rtw8822b_cfg_lकरो25(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 lकरो_pwr;

	lकरो_pwr = rtw_पढ़ो8(rtwdev, REG_LDO_EFUSE_CTRL + 3);
	lकरो_pwr = enable ? lकरो_pwr | BIT_LDO25_EN : lकरो_pwr & ~BIT_LDO25_EN;
	rtw_ग_लिखो8(rtwdev, REG_LDO_EFUSE_CTRL + 3, lकरो_pwr);
पूर्ण

अटल व्योम rtw8822b_false_alarm_statistics(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_enable;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 crc32_cnt;
	u32 cca32_cnt;

	cck_enable = rtw_पढ़ो32(rtwdev, 0x808) & BIT(28);
	cck_fa_cnt = rtw_पढ़ो16(rtwdev, 0xa5c);
	ofdm_fa_cnt = rtw_पढ़ो16(rtwdev, 0xf48);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt += cck_enable ? cck_fa_cnt : 0;

	crc32_cnt = rtw_पढ़ो32(rtwdev, 0xf04);
	dm_info->cck_ok_cnt = crc32_cnt & 0xffff;
	dm_info->cck_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0xf14);
	dm_info->ofdm_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ofdm_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0xf10);
	dm_info->ht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0xf0c);
	dm_info->vht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->vht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;

	cca32_cnt = rtw_पढ़ो32(rtwdev, 0xf08);
	dm_info->ofdm_cca_cnt = ((cca32_cnt & 0xffff0000) >> 16);
	dm_info->total_cca_cnt = dm_info->ofdm_cca_cnt;
	अगर (cck_enable) अणु
		cca32_cnt = rtw_पढ़ो32(rtwdev, 0xfcc);
		dm_info->cck_cca_cnt = cca32_cnt & 0xffff;
		dm_info->total_cca_cnt += dm_info->cck_cca_cnt;
	पूर्ण

	rtw_ग_लिखो32_set(rtwdev, 0x9a4, BIT(17));
	rtw_ग_लिखो32_clr(rtwdev, 0x9a4, BIT(17));
	rtw_ग_लिखो32_clr(rtwdev, 0xa2c, BIT(15));
	rtw_ग_लिखो32_set(rtwdev, 0xa2c, BIT(15));
	rtw_ग_लिखो32_set(rtwdev, 0xb58, BIT(0));
	rtw_ग_लिखो32_clr(rtwdev, 0xb58, BIT(0));
पूर्ण

अटल व्योम rtw8822b_करो_iqk(काष्ठा rtw_dev *rtwdev)
अणु
	अटल पूर्णांक करो_iqk_cnt;
	काष्ठा rtw_iqk_para para = अणु.clear = 0, .segment_iqk = 0पूर्ण;
	u32 rf_reg, iqk_fail_mask;
	पूर्णांक counter;
	bool reload;

	rtw_fw_करो_iqk(rtwdev, &para);

	क्रम (counter = 0; counter < 300; counter++) अणु
		rf_reg = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_DTXLOK, RFREG_MASK);
		अगर (rf_reg == 0xabcde)
			अवरोध;
		msleep(20);
	पूर्ण
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_DTXLOK, RFREG_MASK, 0x0);

	reload = !!rtw_पढ़ो32_mask(rtwdev, REG_IQKFAILMSK, BIT(16));
	iqk_fail_mask = rtw_पढ़ो32_mask(rtwdev, REG_IQKFAILMSK, GENMASK(7, 0));
	rtw_dbg(rtwdev, RTW_DBG_PHY,
		"iqk counter=%d reload=%d do_iqk_cnt=%d n_iqk_fail(mask)=0x%02x\n",
		counter, reload, ++करो_iqk_cnt, iqk_fail_mask);
पूर्ण

अटल व्योम rtw8822b_phy_calibration(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8822b_करो_iqk(rtwdev);
पूर्ण

अटल व्योम rtw8822b_coex_cfg_init(काष्ठा rtw_dev *rtwdev)
अणु
	/* enable TBTT nterrupt */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	/* BT report packet sample rate */
	/* 0x790[5:0]=0x5 */
	rtw_ग_लिखो8_mask(rtwdev, REG_BT_TDMA_TIME, BIT_MASK_SAMPLE_RATE, 0x5);

	/* enable BT counter statistics */
	rtw_ग_लिखो8(rtwdev, REG_BT_STAT_CTRL, 0x1);

	/* enable PTA (3-wire function क्रमm BT side) */
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enable PTA (tx/rx संकेत क्रमm WiFi side) */
	rtw_ग_लिखो8_set(rtwdev, REG_QUEUE_CTRL, BIT_PTA_WL_TX_EN);
	/* wl tx संकेत to PTA not हाल EDCCA */
	rtw_ग_लिखो8_clr(rtwdev, REG_QUEUE_CTRL, BIT_PTA_EDCCA_EN);
	/* GNT_BT=1 जबतक select both */
	rtw_ग_लिखो16_set(rtwdev, REG_BT_COEX_V2, BIT_GNT_BT_POLARITY);
पूर्ण

अटल व्योम rtw8822b_coex_cfg_ant_चयन(काष्ठा rtw_dev *rtwdev,
					 u8 ctrl_type, u8 pos_type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	bool polarity_inverse;
	u8 regval = 0;

	अगर (((ctrl_type << 8) + pos_type) == coex_dm->cur_चयन_status)
		वापस;

	coex_dm->cur_चयन_status = (ctrl_type << 8) + pos_type;

	अगर (coex_rfe->ant_चयन_भागersity &&
	    ctrl_type == COEX_SWITCH_CTRL_BY_BBSW)
		ctrl_type = COEX_SWITCH_CTRL_BY_ANTDIV;

	polarity_inverse = (coex_rfe->ant_चयन_polarity == 1);

	चयन (ctrl_type) अणु
	शेष:
	हाल COEX_SWITCH_CTRL_BY_BBSW:
		/* 0x4c[23] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		/* BB SW, DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x77);

		अगर (pos_type == COEX_SWITCH_TO_WLG_BT) अणु
			अगर (coex_rfe->rfe_module_type != 0x4 &&
			    coex_rfe->rfe_module_type != 0x2)
				regval = 0x3;
			अन्यथा
				regval = (!polarity_inverse ? 0x2 : 0x1);
		पूर्ण अन्यथा अगर (pos_type == COEX_SWITCH_TO_WLG) अणु
			regval = (!polarity_inverse ? 0x2 : 0x1);
		पूर्ण अन्यथा अणु
			regval = (!polarity_inverse ? 0x1 : 0x2);
		पूर्ण

		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_INV8, BIT_MASK_RFE_INV89, regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_PTA:
		/* 0x4c[23] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		/* PTA,  DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x66);

		regval = (!polarity_inverse ? 0x2 : 0x1);
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_INV8, BIT_MASK_RFE_INV89, regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_ANTDIV:
		/* 0x4c[23] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89, 0x88);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_MAC:
		/* 0x4c[23] = 1 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x1);

		regval = (!polarity_inverse ? 0x0 : 0x1);
		rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1, BIT_SW_DPDT_SEL_DATA, regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_FW:
		/* 0x4c[23] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 1 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x1);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_BT:
		/* 0x4c[23] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 2, BIT_DPDT_SEL_EN >> 16, 0x0);
		/* 0x4c[24] = 0 */
		rtw_ग_लिखो8_mask(rtwdev, REG_LED_CFG + 3, BIT_DPDT_WL_SEL >> 24, 0x0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_coex_cfg_gnt_fix(काष्ठा rtw_dev *rtwdev)
अणु
पूर्ण

अटल व्योम rtw8822b_coex_cfg_gnt_debug(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 2, BIT_BTGP_SPI_EN >> 16, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 3, BIT_BTGP_JTAG_EN >> 24, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_GPIO_MUXCFG + 2, BIT_FSPI_EN >> 16, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 1, BIT_LED1DIS >> 8, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_SYS_SDIO_CTRL + 3, BIT_DBG_GNT_WL_BT >> 24, 0);
पूर्ण

अटल व्योम rtw8822b_coex_cfg_rfe_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	bool is_ext_fem = false;

	coex_rfe->rfe_module_type = rtwdev->efuse.rfe_option;
	coex_rfe->ant_चयन_polarity = 0;
	coex_rfe->ant_चयन_भागersity = false;
	अगर (coex_rfe->rfe_module_type == 0x12 ||
	    coex_rfe->rfe_module_type == 0x15 ||
	    coex_rfe->rfe_module_type == 0x16)
		coex_rfe->ant_चयन_exist = false;
	अन्यथा
		coex_rfe->ant_चयन_exist = true;

	अगर (coex_rfe->rfe_module_type == 2 ||
	    coex_rfe->rfe_module_type == 4) अणु
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_EXTFEM, true);
		is_ext_fem = true;
	पूर्ण अन्यथा अणु
		rtw_coex_ग_लिखो_scbd(rtwdev, COEX_SCBD_EXTFEM, false);
	पूर्ण

	coex_rfe->wlg_at_btg = false;

	अगर (efuse->share_ant &&
	    coex_rfe->ant_चयन_exist && !is_ext_fem)
		coex_rfe->ant_चयन_with_bt = true;
	अन्यथा
		coex_rfe->ant_चयन_with_bt = false;

	/* Ext चयन buffer mux */
	rtw_ग_लिखो8(rtwdev, REG_RFE_CTRL_E, 0xff);
	rtw_ग_लिखो8_mask(rtwdev, REG_RFESEL_CTRL + 1, 0x3, 0x0);
	rtw_ग_लिखो8_mask(rtwdev, REG_RFE_INV16, BIT_RFE_BUF_EN, 0x0);

	/* Disable LTE Coex Function in WiFi side */
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, BIT_LTE_COEX_EN, 0);

	/* BTC_CTT_WL_VS_LTE */
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_WL_TRX_CTRL, MASKLWORD, 0xffff);

	/* BTC_CTT_BT_VS_LTE */
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_BT_TRX_CTRL, MASKLWORD, 0xffff);
पूर्ण

अटल व्योम rtw8822b_coex_cfg_wl_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 wl_pwr)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	अटल स्थिर u16 reg_addr[] = अणु0xc58, 0xe58पूर्ण;
	अटल स्थिर u8	wl_tx_घातer[] = अणु0xd8, 0xd4, 0xd0, 0xcc, 0xc8पूर्ण;
	u8 i, pwr;

	अगर (wl_pwr == coex_dm->cur_wl_pwr_lvl)
		वापस;

	coex_dm->cur_wl_pwr_lvl = wl_pwr;

	अगर (coex_dm->cur_wl_pwr_lvl >= ARRAY_SIZE(wl_tx_घातer))
		coex_dm->cur_wl_pwr_lvl = ARRAY_SIZE(wl_tx_घातer) - 1;

	pwr = wl_tx_घातer[coex_dm->cur_wl_pwr_lvl];

	क्रम (i = 0; i < ARRAY_SIZE(reg_addr); i++)
		rtw_ग_लिखो8_mask(rtwdev, reg_addr[i], 0xff, pwr);
पूर्ण

अटल व्योम rtw8822b_coex_cfg_wl_rx_gain(काष्ठा rtw_dev *rtwdev, bool low_gain)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	/* WL Rx Low gain on */
	अटल स्थिर u32 wl_rx_low_gain_on[] = अणु
		0xff000003, 0xbd120003, 0xbe100003, 0xbf080003, 0xbf060003,
		0xbf050003, 0xbc140003, 0xbb160003, 0xba180003, 0xb91a0003,
		0xb81c0003, 0xb71e0003, 0xb4200003, 0xb5220003, 0xb4240003,
		0xb3260003, 0xb2280003, 0xb12a0003, 0xb02c0003, 0xaf2e0003,
		0xae300003, 0xad320003, 0xac340003, 0xab360003, 0x8d380003,
		0x8c3a0003, 0x8b3c0003, 0x8a3e0003, 0x6e400003, 0x6d420003,
		0x6c440003, 0x6b460003, 0x6a480003, 0x694a0003, 0x684c0003,
		0x674e0003, 0x66500003, 0x65520003, 0x64540003, 0x64560003,
		0x007e0403
	पूर्ण;

	/* WL Rx Low gain off */
	अटल स्थिर u32 wl_rx_low_gain_off[] = अणु
		0xff000003, 0xf4120003, 0xf5100003, 0xf60e0003, 0xf70c0003,
		0xf80a0003, 0xf3140003, 0xf2160003, 0xf1180003, 0xf01a0003,
		0xef1c0003, 0xee1e0003, 0xed200003, 0xec220003, 0xeb240003,
		0xea260003, 0xe9280003, 0xe82a0003, 0xe72c0003, 0xe62e0003,
		0xe5300003, 0xc8320003, 0xc7340003, 0xc6360003, 0xc5380003,
		0xc43a0003, 0xc33c0003, 0xc23e0003, 0xc1400003, 0xc0420003,
		0xa5440003, 0xa4460003, 0xa3480003, 0xa24a0003, 0xa14c0003,
		0x834e0003, 0x82500003, 0x81520003, 0x80540003, 0x65560003,
		0x007e0403
	पूर्ण;
	u8 i;

	अगर (low_gain == coex_dm->cur_wl_rx_low_gain_en)
		वापस;

	coex_dm->cur_wl_rx_low_gain_en = low_gain;

	अगर (coex_dm->cur_wl_rx_low_gain_en) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], Hi-Li Table On!\n");
		क्रम (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_on); i++)
			rtw_ग_लिखो32(rtwdev, REG_RX_GAIN_EN, wl_rx_low_gain_on[i]);

		/* set Rx filter corner RCK offset */
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCKD, 0x2, 0x1);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCK, 0x3f, 0x3f);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCKD, 0x2, 0x1);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCK, 0x3f, 0x3f);
	पूर्ण अन्यथा अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], Hi-Li Table Off!\n");
		क्रम (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_off); i++)
			rtw_ग_लिखो32(rtwdev, 0x81c, wl_rx_low_gain_off[i]);

		/* set Rx filter corner RCK offset */
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCK, 0x3f, 0x4);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCKD, 0x2, 0x0);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCK, 0x3f, 0x4);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCKD, 0x2, 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8822b_txagc_swing_offset(काष्ठा rtw_dev *rtwdev, u8 path,
					u8 tx_pwr_idx_offset,
					s8 *txagc_idx, u8 *swing_idx)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 delta_pwr_idx = dm_info->delta_घातer_index[path];
	u8 swing_upper_bound = dm_info->शेष_ofdm_index + 10;
	u8 swing_lower_bound = 0;
	u8 max_tx_pwr_idx_offset = 0xf;
	s8 agc_index = 0;
	u8 swing_index = dm_info->शेष_ofdm_index;

	tx_pwr_idx_offset = min_t(u8, tx_pwr_idx_offset, max_tx_pwr_idx_offset);

	अगर (delta_pwr_idx >= 0) अणु
		अगर (delta_pwr_idx <= tx_pwr_idx_offset) अणु
			agc_index = delta_pwr_idx;
			swing_index = dm_info->शेष_ofdm_index;
		पूर्ण अन्यथा अगर (delta_pwr_idx > tx_pwr_idx_offset) अणु
			agc_index = tx_pwr_idx_offset;
			swing_index = dm_info->शेष_ofdm_index +
					delta_pwr_idx - tx_pwr_idx_offset;
			swing_index = min_t(u8, swing_index, swing_upper_bound);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dm_info->शेष_ofdm_index > असल(delta_pwr_idx))
			swing_index =
				dm_info->शेष_ofdm_index + delta_pwr_idx;
		अन्यथा
			swing_index = swing_lower_bound;
		swing_index = max_t(u8, swing_index, swing_lower_bound);

		agc_index = 0;
	पूर्ण

	अगर (swing_index >= RTW_TXSCALE_SIZE) अणु
		rtw_warn(rtwdev, "swing index overflow\n");
		swing_index = RTW_TXSCALE_SIZE - 1;
	पूर्ण
	*txagc_idx = agc_index;
	*swing_idx = swing_index;
पूर्ण

अटल व्योम rtw8822b_pwrtrack_set_pwr(काष्ठा rtw_dev *rtwdev, u8 path,
				      u8 pwr_idx_offset)
अणु
	s8 txagc_idx;
	u8 swing_idx;
	u32 reg1, reg2;

	अगर (path == RF_PATH_A) अणु
		reg1 = 0xc94;
		reg2 = 0xc1c;
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		reg1 = 0xe94;
		reg2 = 0xe1c;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	rtw8822b_txagc_swing_offset(rtwdev, path, pwr_idx_offset,
				    &txagc_idx, &swing_idx);
	rtw_ग_लिखो32_mask(rtwdev, reg1, GENMASK(29, 25), txagc_idx);
	rtw_ग_लिखो32_mask(rtwdev, reg2, GENMASK(31, 21),
			 rtw8822b_txscale_tbl[swing_idx]);
पूर्ण

अटल व्योम rtw8822b_pwrtrack_set(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 pwr_idx_offset, tx_pwr_idx;
	u8 channel = rtwdev->hal.current_channel;
	u8 band_width = rtwdev->hal.current_band_width;
	u8 regd = rtwdev->regd.txpwr_regd;
	u8 tx_rate = dm_info->tx_rate;
	u8 max_pwr_idx = rtwdev->chip->max_घातer_index;

	tx_pwr_idx = rtw_phy_get_tx_घातer_index(rtwdev, path, tx_rate,
						band_width, channel, regd);

	tx_pwr_idx = min_t(u8, tx_pwr_idx, max_pwr_idx);

	pwr_idx_offset = max_pwr_idx - tx_pwr_idx;

	rtw8822b_pwrtrack_set_pwr(rtwdev, path, pwr_idx_offset);
पूर्ण

अटल व्योम rtw8822b_phy_pwrtrack_path(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_swing_table *swing_table,
				       u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 घातer_idx_cur, घातer_idx_last;
	u8 delta;

	/* 8822B only has one thermal meter at PATH A */
	delta = rtw_phy_pwrtrack_get_delta(rtwdev, RF_PATH_A);

	घातer_idx_last = dm_info->delta_घातer_index[path];
	घातer_idx_cur = rtw_phy_pwrtrack_get_pwridx(rtwdev, swing_table,
						    path, RF_PATH_A, delta);

	/* अगर delta of घातer indexes are the same, just skip */
	अगर (घातer_idx_cur == घातer_idx_last)
		वापस;

	dm_info->delta_घातer_index[path] = घातer_idx_cur;
	rtw8822b_pwrtrack_set(rtwdev, path);
पूर्ण

अटल व्योम rtw8822b_phy_pwrtrack(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_swing_table swing_table;
	u8 thermal_value, path;

	rtw_phy_config_swing_table(rtwdev, &swing_table);

	अगर (rtwdev->efuse.thermal_meter[RF_PATH_A] == 0xff)
		वापस;

	thermal_value = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_T_METER, 0xfc00);

	rtw_phy_pwrtrack_avg(rtwdev, thermal_value, RF_PATH_A);

	अगर (dm_info->pwr_trk_init_trigger)
		dm_info->pwr_trk_init_trigger = false;
	अन्यथा अगर (!rtw_phy_pwrtrack_thermal_changed(rtwdev, thermal_value,
						   RF_PATH_A))
		जाओ iqk;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++)
		rtw8822b_phy_pwrtrack_path(rtwdev, &swing_table, path);

iqk:
	अगर (rtw_phy_pwrtrack_need_iqk(rtwdev))
		rtw8822b_करो_iqk(rtwdev);
पूर्ण

अटल व्योम rtw8822b_pwr_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	अगर (efuse->घातer_track_type != 0)
		वापस;

	अगर (!dm_info->pwr_trk_triggered) अणु
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_T_METER,
			     GENMASK(17, 16), 0x03);
		dm_info->pwr_trk_triggered = true;
		वापस;
	पूर्ण

	rtw8822b_phy_pwrtrack(rtwdev);
	dm_info->pwr_trk_triggered = false;
पूर्ण

अटल व्योम rtw8822b_bf_config_bfee_su(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw_bf_enable_bfee_su(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_su(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8822b_bf_config_bfee_mu(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw_bf_enable_bfee_mu(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_mu(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8822b_bf_config_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
				    काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (bfee->role == RTW_BFEE_SU)
		rtw8822b_bf_config_bfee_su(rtwdev, vअगर, bfee, enable);
	अन्यथा अगर (bfee->role == RTW_BFEE_MU)
		rtw8822b_bf_config_bfee_mu(rtwdev, vअगर, bfee, enable);
	अन्यथा
		rtw_warn(rtwdev, "wrong bfee role\n");
पूर्ण

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_carddis_to_cardemu_8822b[] = अणु
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,
	अणु0x004A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4) | BIT(7), 0पूर्ण,
	अणु0x0300,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x0301,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_act_8822b[] = अणु
	अणु0x0012,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0012,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0020,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0001,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_DELAY, 1, RTW_PWR_DELAY_MSपूर्ण,
	अणु0x0000,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(4) | BIT(3) | BIT(2)), 0पूर्ण,
	अणु0x0075,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,
	अणु0x0075,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0xFF1A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(4) | BIT(3)), 0पूर्ण,
	अणु0x10C3,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(0), 0पूर्ण,
	अणु0x0020,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), BIT(3)पूर्ण,
	अणु0x10A8,
	 RTW_PWR_CUT_C_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x10A9,
	 RTW_PWR_CUT_C_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0xefपूर्ण,
	अणु0x10AA,
	 RTW_PWR_CUT_C_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x0cपूर्ण,
	अणु0x0068,
	 RTW_PWR_CUT_C_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,
	अणु0x0029,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0xF9पूर्ण,
	अणु0x0024,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), 0पूर्ण,
	अणु0x0074,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0x00AF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_cardemu_8822b[] = अणु
	अणु0x0003,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), 0पूर्ण,
	अणु0x0093,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), 0पूर्ण,
	अणु0x001F,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x00EF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0xFF1A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x30पूर्ण,
	अणु0x0049,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x10C3,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(1), 0पूर्ण,
	अणु0x0020,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), 0पूर्ण,
	अणु0x0000,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_carddis_8822b[] = अणु
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7), BIT(7)पूर्ण,
	अणु0x0007,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x004A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), 0पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), 0पूर्ण,
	अणु0x004F,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0046,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(6), BIT(6)पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), 0पूर्ण,
	अणु0x0046,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7), BIT(7)पूर्ण,
	अणु0x0062,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,
	अणु0x0081,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7) | BIT(6), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)पूर्ण,
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_POLLING, BIT(1), 0पूर्ण,
	अणु0x0090,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0044,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x0040,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x90पूर्ण,
	अणु0x0041,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,
	अणु0x0042,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x04पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_enable_flow_8822b[] = अणु
	trans_carddis_to_cardemu_8822b,
	trans_cardemu_to_act_8822b,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_disable_flow_8822b[] = अणु
	trans_act_to_cardemu_8822b,
	trans_cardemu_to_carddis_8822b,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb2_param_8822b[] = अणु
	अणु0xFFFF, 0x00,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb3_param_8822b[] = अणु
	अणु0x0001, 0xA841,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_D,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen1_param_8822b[] = अणु
	अणु0x0001, 0xA841,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0002, 0x60C6,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0008, 0x3596,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0009, 0x321C,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x000A, 0x9623,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0020, 0x94FF,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0021, 0xFFCF,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0026, 0xC006,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0029, 0xFF0E,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x002A, 0x1840,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen2_param_8822b[] = अणु
	अणु0x0001, 0xA841,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0002, 0x60C6,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0008, 0x3597,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0009, 0x321C,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x000A, 0x9623,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0020, 0x94FF,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0021, 0xFFCF,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0026, 0xC006,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0029, 0xFF0E,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x002A, 0x3040,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_C,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para_table phy_para_table_8822b = अणु
	.usb2_para	= usb2_param_8822b,
	.usb3_para	= usb3_param_8822b,
	.gen1_para	= pcie_gen1_param_8822b,
	.gen2_para	= pcie_gen2_param_8822b,
	.n_usb2_para	= ARRAY_SIZE(usb2_param_8822b),
	.n_usb3_para	= ARRAY_SIZE(usb2_param_8822b),
	.n_gen1_para	= ARRAY_SIZE(pcie_gen1_param_8822b),
	.n_gen2_para	= ARRAY_SIZE(pcie_gen2_param_8822b),
पूर्ण;

अटल स्थिर काष्ठा rtw_rfe_def rtw8822b_rfe_defs[] = अणु
	[2] = RTW_DEF_RFE(8822b, 2, 2),
	[3] = RTW_DEF_RFE(8822b, 3, 0),
	[5] = RTW_DEF_RFE(8822b, 5, 5),
पूर्ण;

अटल स्थिर काष्ठा rtw_hw_reg rtw8822b_dig[] = अणु
	[0] = अणु .addr = 0xc50, .mask = 0x7f पूर्ण,
	[1] = अणु .addr = 0xe50, .mask = 0x7f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_ltecoex_addr rtw8822b_ltecoex_addr = अणु
	.ctrl = LTECOEX_ACCESS_CTRL,
	.wdata = LTECOEX_WRITE_DATA,
	.rdata = LTECOEX_READ_DATA,
पूर्ण;

अटल स्थिर काष्ठा rtw_page_table page_table_8822b[] = अणु
	अणु64, 64, 64, 64, 1पूर्ण,
	अणु64, 64, 64, 64, 1पूर्ण,
	अणु64, 64, 0, 0, 1पूर्ण,
	अणु64, 64, 64, 0, 1पूर्ण,
	अणु64, 64, 64, 64, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_rqpn rqpn_table_8822b[] = अणु
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_HIGH,
	 RTW_DMA_MAPPING_HIGH, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_HIGH, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
पूर्ण;

अटल काष्ठा rtw_prioq_addrs prioq_addrs_8822b = अणु
	.prio[RTW_DMA_MAPPING_EXTRA] = अणु
		.rsvd = REG_FIFOPAGE_INFO_4, .avail = REG_FIFOPAGE_INFO_4 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_LOW] = अणु
		.rsvd = REG_FIFOPAGE_INFO_2, .avail = REG_FIFOPAGE_INFO_2 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_NORMAL] = अणु
		.rsvd = REG_FIFOPAGE_INFO_3, .avail = REG_FIFOPAGE_INFO_3 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_HIGH] = अणु
		.rsvd = REG_FIFOPAGE_INFO_1, .avail = REG_FIFOPAGE_INFO_1 + 2,
	पूर्ण,
	.wsize = true,
पूर्ण;

अटल काष्ठा rtw_chip_ops rtw8822b_ops = अणु
	.phy_set_param		= rtw8822b_phy_set_param,
	.पढ़ो_efuse		= rtw8822b_पढ़ो_efuse,
	.query_rx_desc		= rtw8822b_query_rx_desc,
	.set_channel		= rtw8822b_set_channel,
	.mac_init		= rtw8822b_mac_init,
	.पढ़ो_rf		= rtw_phy_पढ़ो_rf,
	.ग_लिखो_rf		= rtw_phy_ग_लिखो_rf_reg_sipi,
	.set_tx_घातer_index	= rtw8822b_set_tx_घातer_index,
	.set_antenna		= rtw8822b_set_antenna,
	.cfg_lकरो25		= rtw8822b_cfg_lकरो25,
	.false_alarm_statistics	= rtw8822b_false_alarm_statistics,
	.phy_calibration	= rtw8822b_phy_calibration,
	.pwr_track		= rtw8822b_pwr_track,
	.config_bfee		= rtw8822b_bf_config_bfee,
	.set_gid_table		= rtw_bf_set_gid_table,
	.cfg_csi_rate		= rtw_bf_cfg_csi_rate,

	.coex_set_init		= rtw8822b_coex_cfg_init,
	.coex_set_ant_चयन	= rtw8822b_coex_cfg_ant_चयन,
	.coex_set_gnt_fix	= rtw8822b_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= rtw8822b_coex_cfg_gnt_debug,
	.coex_set_rfe_type	= rtw8822b_coex_cfg_rfe_type,
	.coex_set_wl_tx_घातer	= rtw8822b_coex_cfg_wl_tx_घातer,
	.coex_set_wl_rx_gain	= rtw8822b_coex_cfg_wl_rx_gain,
पूर्ण;

/* Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_sant_8822b[] = अणु
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-0 */
	अणु0x55555555, 0x55555555पूर्ण,
	अणु0x66555555, 0x66555555पूर्ण,
	अणु0xaaaaaaaa, 0xaaaaaaaaपूर्ण,
	अणु0x5a5a5a5a, 0x5a5a5a5aपूर्ण,
	अणु0xfafafafa, 0xfafafafaपूर्ण, /* हाल-5 */
	अणु0x6a5a5555, 0xaaaaaaaaपूर्ण,
	अणु0x6a5a56aa, 0x6a5a56aaपूर्ण,
	अणु0x6a5a5a5a, 0x6a5a5a5aपूर्ण,
	अणु0x66555555, 0x5a5a5a5aपूर्ण,
	अणु0x66555555, 0x6a5a5a5aपूर्ण, /* हाल-10 */
	अणु0x66555555, 0xfafafafaपूर्ण,
	अणु0x66555555, 0x5a5a5aaaपूर्ण,
	अणु0x66555555, 0x6aaa5aaaपूर्ण,
	अणु0x66555555, 0xaaaa5aaaपूर्ण,
	अणु0x66555555, 0xaaaaaaaaपूर्ण, /* हाल-15 */
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffff55ff, 0x6afa5afaपूर्ण,
	अणु0xaaffffaa, 0xfafafafaपूर्ण,
	अणु0xaa5555aa, 0x5a5a5a5aपूर्ण,
	अणु0xaa5555aa, 0x6a5a5a5aपूर्ण, /* हाल-20 */
	अणु0xaa5555aa, 0xaaaaaaaaपूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x55555555पूर्ण,
	अणु0xffffffff, 0x6a5a5aaaपूर्ण, /* हाल-25 */
	अणु0x55555555, 0x5a5a5a5aपूर्ण,
	अणु0x55555555, 0xaaaaaaaaपूर्ण,
	अणु0x55555555, 0x6a5a6a5aपूर्ण,
	अणु0x66556655, 0x66556655पूर्ण,
	अणु0x66556aaa, 0x6a5a6aaaपूर्ण, /* हाल-30 */
	अणु0xffffffff, 0x5aaa5aaaपूर्ण,
	अणु0x56555555, 0x5a5a5aaaपूर्ण,
पूर्ण;

/* Non-Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_nsant_8822b[] = अणु
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-100 */
	अणु0x55555555, 0x55555555पूर्ण,
	अणु0x66555555, 0x66555555पूर्ण,
	अणु0xaaaaaaaa, 0xaaaaaaaaपूर्ण,
	अणु0x5a5a5a5a, 0x5a5a5a5aपूर्ण,
	अणु0xfafafafa, 0xfafafafaपूर्ण, /* हाल-105 */
	अणु0x5afa5afa, 0x5afa5afaपूर्ण,
	अणु0x55555555, 0xfafafafaपूर्ण,
	अणु0x66555555, 0xfafafafaपूर्ण,
	अणु0x66555555, 0x5a5a5a5aपूर्ण,
	अणु0x66555555, 0x6a5a5a5aपूर्ण, /* हाल-110 */
	अणु0x66555555, 0xaaaaaaaaपूर्ण,
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffff55ff, 0x5afa5afaपूर्ण,
	अणु0xffff55ff, 0xaaaaaaaaपूर्ण,
	अणु0xffff55ff, 0xffff55ffपूर्ण, /* हाल-115 */
	अणु0xaaffffaa, 0x5afa5afaपूर्ण,
	अणु0xaaffffaa, 0xaaaaaaaaपूर्ण,
	अणु0xffffffff, 0xfafafafaपूर्ण,
	अणु0xffffffff, 0x5afa5afaपूर्ण,
	अणु0xffffffff, 0xaaaaaaaaपूर्ण, /* हाल-120 */
	अणु0x55ff55ff, 0x5afa5afaपूर्ण,
	अणु0x55ff55ff, 0xaaaaaaaaपूर्ण,
	अणु0x55ff55ff, 0x55ff55ffपूर्ण
पूर्ण;

/* Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_sant_8822b[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-0 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-5 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-10 */
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x14पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-15 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x20, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-20 */
	अणु अणु0x51, 0x4a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x0c, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x55, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x65, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x51पूर्ण पूर्ण, /* हाल-25 */
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x11पूर्ण पूर्ण
पूर्ण;

/* Non-Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_nsant_8822b[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-100 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-101 */
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-105 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-110 */
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x14पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-115 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x20, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-120 */
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x50पूर्ण पूर्ण
पूर्ण;

/* rssi in percentage % (dbm = % - 100) */
अटल स्थिर u8 wl_rssi_step_8822b[] = अणु60, 50, 44, 30पूर्ण;
अटल स्थिर u8 bt_rssi_step_8822b[] = अणु30, 30, 30, 30पूर्ण;

/* wl_tx_dec_घातer, bt_tx_dec_घातer, wl_rx_gain, bt_rx_lna_स्थिरrain */
अटल स्थिर काष्ठा coex_rf_para rf_para_tx_8822b[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 16, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु4, 0, true, 1पूर्ण,
	अणु3, 6, true, 1पूर्ण,
	अणु2, 9, true, 1पूर्ण,
	अणु1, 13, true, 1पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_rf_para rf_para_rx_8822b[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 16, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु4, 0, true, 1पूर्ण,
	अणु3, 6, true, 1पूर्ण,
	अणु2, 9, true, 1पूर्ण,
	अणु1, 13, true, 1पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_5g_afh_map afh_5g_8822b[] = अणु
	अणु120, 2, 4पूर्ण,
	अणु124, 8, 8पूर्ण,
	अणु128, 17, 8पूर्ण,
	अणु132, 26, 10पूर्ण,
	अणु136, 34, 8पूर्ण,
	अणु140, 42, 10पूर्ण,
	अणु144, 51, 8पूर्ण,
	अणु149, 62, 8पूर्ण,
	अणु153, 71, 10पूर्ण,
	अणु157, 77, 4पूर्ण,
	अणु118, 2, 4पूर्ण,
	अणु126, 12, 16पूर्ण,
	अणु134, 29, 16पूर्ण,
	अणु142, 46, 16पूर्ण,
	अणु151, 66, 16पूर्ण,
	अणु159, 76, 4पूर्ण,
	अणु122, 10, 20पूर्ण,
	अणु138, 37, 34पूर्ण,
	अणु155, 68, 20पूर्ण
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(rf_para_tx_8822b) == ARRAY_SIZE(rf_para_rx_8822b));

अटल स्थिर u8
rtw8822b_pwrtrk_5gb_n[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822b_pwrtrk_5gb_p[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822b_pwrtrk_5ga_n[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  8,  9, 10, 11, 11, 12, 13, 14, 14,
	 15, 16, 17, 17, 18, 19, 20, 20, 21, 22 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822b_pwrtrk_5ga_p[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23पूर्ण,
	अणु 0,  1,  2,  2,  3,  4,  5,  5,  6,  7,
	  8,  9,  9, 10, 11, 12, 13, 14, 14, 15,
	 16, 17, 18, 19, 19, 20, 21, 22, 22, 23पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2gb_n[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  1,  1,  1,  2,  2,  3,  3,  3,  4,
	4,  5,  5,  5,  6,  6,  7,  7,  7,  8,
	8,  9,  9,  9, 10, 10, 11, 11, 11, 12
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2gb_p[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  0,  1,  1,  2,  2,  3,  3,  4,  4,
	5,  5,  6,  6,  6,  7,  7,  8,  8,  9,
	9, 10, 10, 11, 11, 12, 12, 12, 13, 13
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2ga_n[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  1,  1,  1,  2,  2,  3,  3,  3,  4,
	4,  5,  5,  5,  6,  6,  7,  7,  7,  8,
	8,  9,  9,  9, 10, 10, 11, 11, 11, 12
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2ga_p[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  1,  1,  2,  2,  3,  3,  4,  4,  5,
	5,  6,  6,  7,  7,  8,  8,  9,  9, 10,
	10, 11, 11, 12, 12, 13, 13, 14, 14, 15
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2g_cck_b_n[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  1,  1,  1,  2,  2,  3,  3,  3,  4,
	4,  5,  5,  5,  6,  6,  7,  7,  7,  8,
	8,  9,  9,  9, 10, 10, 11, 11, 11, 12
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2g_cck_b_p[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  0,  1,  1,  2,  2,  3,  3,  4,  4,
	5,  5,  6,  6,  6,  7,  7,  8,  8,  9,
	9, 10, 10, 11, 11, 12, 12, 12, 13, 13
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2g_cck_a_n[RTW_PWR_TRK_TBL_SZ] = अणु
	0,  1,  1,  1,  2,  2,  3,  3,  3,  4,
	4,  5,  5,  5,  6,  6,  7,  7,  7,  8,
	8,  9,  9,  9, 10, 10, 11, 11, 11, 12
पूर्ण;

अटल स्थिर u8 rtw8822b_pwrtrk_2g_cck_a_p[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  1,  2,  2,  3,  3,  4,  4,  5,
	 5,  6,  6,  7,  7,  8,  8,  9,  9, 10,
	10, 11, 11, 12, 12, 13, 13, 14, 14, 15
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_track_tbl rtw8822b_rtw_pwr_track_tbl = अणु
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_1] = rtw8822b_pwrtrk_5gb_n[RTW_PWR_TRK_5G_1],
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_2] = rtw8822b_pwrtrk_5gb_n[RTW_PWR_TRK_5G_2],
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_3] = rtw8822b_pwrtrk_5gb_n[RTW_PWR_TRK_5G_3],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_1] = rtw8822b_pwrtrk_5gb_p[RTW_PWR_TRK_5G_1],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_2] = rtw8822b_pwrtrk_5gb_p[RTW_PWR_TRK_5G_2],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_3] = rtw8822b_pwrtrk_5gb_p[RTW_PWR_TRK_5G_3],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_1] = rtw8822b_pwrtrk_5ga_n[RTW_PWR_TRK_5G_1],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_2] = rtw8822b_pwrtrk_5ga_n[RTW_PWR_TRK_5G_2],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_3] = rtw8822b_pwrtrk_5ga_n[RTW_PWR_TRK_5G_3],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_1] = rtw8822b_pwrtrk_5ga_p[RTW_PWR_TRK_5G_1],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_2] = rtw8822b_pwrtrk_5ga_p[RTW_PWR_TRK_5G_2],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_3] = rtw8822b_pwrtrk_5ga_p[RTW_PWR_TRK_5G_3],
	.pwrtrk_2gb_n = rtw8822b_pwrtrk_2gb_n,
	.pwrtrk_2gb_p = rtw8822b_pwrtrk_2gb_p,
	.pwrtrk_2ga_n = rtw8822b_pwrtrk_2ga_n,
	.pwrtrk_2ga_p = rtw8822b_pwrtrk_2ga_p,
	.pwrtrk_2g_cckb_n = rtw8822b_pwrtrk_2g_cck_b_n,
	.pwrtrk_2g_cckb_p = rtw8822b_pwrtrk_2g_cck_b_p,
	.pwrtrk_2g_ccka_n = rtw8822b_pwrtrk_2g_cck_a_n,
	.pwrtrk_2g_ccka_p = rtw8822b_pwrtrk_2g_cck_a_p,
पूर्ण;

अटल स्थिर काष्ठा rtw_reg_करोमुख्य coex_info_hw_regs_8822b[] = अणु
	अणु0xcb0, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0xcb4, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0xcba, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xcbd, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xc58, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xcbd, BIT(0), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x430, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x434, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x42a, MASKLWORD, RTW_REG_DOMAIN_MAC16पूर्ण,
	अणु0x426, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x45e, BIT(3), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x454, MASKLWORD, RTW_REG_DOMAIN_MAC16पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x4c, BIT(24) | BIT(23), RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x64, BIT(0), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x4c6, BIT(4), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x40, BIT(5), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x1, RFREG_MASK, RTW_REG_DOMAIN_RF_Bपूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x550, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x522, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x953, BIT(1), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xc50,  MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
पूर्ण;

काष्ठा rtw_chip_info rtw8822b_hw_spec = अणु
	.ops = &rtw8822b_ops,
	.id = RTW_CHIP_TYPE_8822B,
	.fw_name = "rtw88/rtw8822b_fw.bin",
	.wlan_cpu = RTW_WCPU_11AC,
	.tx_pkt_desc_sz = 48,
	.tx_buf_desc_sz = 16,
	.rx_pkt_desc_sz = 24,
	.rx_buf_desc_sz = 8,
	.phy_efuse_size = 1024,
	.log_efuse_size = 768,
	.ptct_efuse_size = 96,
	.txff_size = 262144,
	.rxff_size = 24576,
	.fw_rxff_size = 12288,
	.txgi_factor = 1,
	.is_pwr_by_rate_dec = true,
	.max_घातer_index = 0x3f,
	.csi_buf_pg_num = 0,
	.band = RTW_BAND_2G | RTW_BAND_5G,
	.page_size = 128,
	.dig_min = 0x1c,
	.ht_supported = true,
	.vht_supported = true,
	.lps_deep_mode_supported = BIT(LPS_DEEP_MODE_LCLK),
	.sys_func_en = 0xDC,
	.pwr_on_seq = card_enable_flow_8822b,
	.pwr_off_seq = card_disable_flow_8822b,
	.page_table = page_table_8822b,
	.rqpn_table = rqpn_table_8822b,
	.prioq_addrs = &prioq_addrs_8822b,
	.पूर्णांकf_table = &phy_para_table_8822b,
	.dig = rtw8822b_dig,
	.dig_cck = शून्य,
	.rf_base_addr = अणु0x2800, 0x2c00पूर्ण,
	.rf_sipi_addr = अणु0xc90, 0xe90पूर्ण,
	.ltecoex_addr = &rtw8822b_ltecoex_addr,
	.mac_tbl = &rtw8822b_mac_tbl,
	.agc_tbl = &rtw8822b_agc_tbl,
	.bb_tbl = &rtw8822b_bb_tbl,
	.rf_tbl = अणु&rtw8822b_rf_a_tbl, &rtw8822b_rf_b_tblपूर्ण,
	.rfe_defs = rtw8822b_rfe_defs,
	.rfe_defs_size = ARRAY_SIZE(rtw8822b_rfe_defs),
	.pwr_track_tbl = &rtw8822b_rtw_pwr_track_tbl,
	.iqk_threshold = 8,
	.bfer_su_max_num = 2,
	.bfer_mu_max_num = 1,
	.rx_ldpc = true,

	.coex_para_ver = 0x20070206,
	.bt_desired_ver = 0x6,
	.scbd_support = true,
	.new_scbd10_def = false,
	.ble_hid_profile_support = false,
	.pstdma_type = COEX_PSTDMA_FORCE_LPSOFF,
	.bt_rssi_type = COEX_BTRSSI_RATIO,
	.ant_isolation = 15,
	.rssi_tolerance = 2,
	.wl_rssi_step = wl_rssi_step_8822b,
	.bt_rssi_step = bt_rssi_step_8822b,
	.table_sant_num = ARRAY_SIZE(table_sant_8822b),
	.table_sant = table_sant_8822b,
	.table_nsant_num = ARRAY_SIZE(table_nsant_8822b),
	.table_nsant = table_nsant_8822b,
	.tdma_sant_num = ARRAY_SIZE(tdma_sant_8822b),
	.tdma_sant = tdma_sant_8822b,
	.tdma_nsant_num = ARRAY_SIZE(tdma_nsant_8822b),
	.tdma_nsant = tdma_nsant_8822b,
	.wl_rf_para_num = ARRAY_SIZE(rf_para_tx_8822b),
	.wl_rf_para_tx = rf_para_tx_8822b,
	.wl_rf_para_rx = rf_para_rx_8822b,
	.bt_afh_span_bw20 = 0x24,
	.bt_afh_span_bw40 = 0x36,
	.afh_5g_num = ARRAY_SIZE(afh_5g_8822b),
	.afh_5g = afh_5g_8822b,

	.coex_info_hw_regs_num = ARRAY_SIZE(coex_info_hw_regs_8822b),
	.coex_info_hw_regs = coex_info_hw_regs_8822b,

	.fw_fअगरo_addr = अणु0x780, 0x700, 0x780, 0x660, 0x650, 0x680पूर्ण,
पूर्ण;
EXPORT_SYMBOL(rtw8822b_hw_spec);

MODULE_FIRMWARE("rtw88/rtw8822b_fw.bin");

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless 8822b driver");
MODULE_LICENSE("Dual BSD/GPL");

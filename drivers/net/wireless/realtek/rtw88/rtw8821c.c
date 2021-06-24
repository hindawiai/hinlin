<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "coex.h"
#समावेश "fw.h"
#समावेश "tx.h"
#समावेश "rx.h"
#समावेश "phy.h"
#समावेश "rtw8821c.h"
#समावेश "rtw8821c_table.h"
#समावेश "mac.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "bf.h"

अटल स्थिर s8 lna_gain_table_0[8] = अणु22, 8, -6, -22, -31, -40, -46, -52पूर्ण;
अटल स्थिर s8 lna_gain_table_1[16] = अणु10, 6, 2, -2, -6, -10, -14, -17,
					-20, -24, -28, -31, -34, -37, -40, -44पूर्ण;

अटल व्योम rtw8821ce_efuse_parsing(काष्ठा rtw_efuse *efuse,
				    काष्ठा rtw8821c_efuse *map)
अणु
	ether_addr_copy(efuse->addr, map->e.mac_addr);
पूर्ण

क्रमागत rtw8821ce_rf_set अणु
	SWITCH_TO_BTG,
	SWITCH_TO_WLG,
	SWITCH_TO_WLA,
	SWITCH_TO_BT,
पूर्ण;

अटल पूर्णांक rtw8821c_पढ़ो_efuse(काष्ठा rtw_dev *rtwdev, u8 *log_map)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw8821c_efuse *map;
	पूर्णांक i;

	map = (काष्ठा rtw8821c_efuse *)log_map;

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
	efuse->thermal_meter[0] = map->thermal_meter;
	efuse->thermal_meter_k = map->thermal_meter;
	efuse->tx_bb_swing_setting_2g = map->tx_bb_swing_setting_2g;
	efuse->tx_bb_swing_setting_5g = map->tx_bb_swing_setting_5g;

	क्रम (i = 0; i < 4; i++)
		efuse->txpwr_idx_table[i] = map->txpwr_idx_table[i];

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtw8821ce_efuse_parsing(efuse, map);
		अवरोध;
	शेष:
		/* unsupported now */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u32 rtw8821c_txscale_tbl[] = अणु
	0x081, 0x088, 0x090, 0x099, 0x0a2, 0x0ac, 0x0b6, 0x0c0, 0x0cc, 0x0d8,
	0x0e5, 0x0f2, 0x101, 0x110, 0x120, 0x131, 0x143, 0x156, 0x16a, 0x180,
	0x197, 0x1af, 0x1c8, 0x1e3, 0x200, 0x21e, 0x23e, 0x261, 0x285, 0x2ab,
	0x2d3, 0x2fe, 0x32b, 0x35c, 0x38e, 0x3c4, 0x3fe
पूर्ण;

अटल u8 rtw8821c_get_swing_index(काष्ठा rtw_dev *rtwdev)
अणु
	u8 i = 0;
	u32 swing, table_value;

	swing = rtw_पढ़ो32_mask(rtwdev, REG_TXSCALE_A, 0xffe00000);
	क्रम (i = 0; i < ARRAY_SIZE(rtw8821c_txscale_tbl); i++) अणु
		table_value = rtw8821c_txscale_tbl[i];
		अगर (swing == table_value)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम rtw8821c_pwrtrack_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 swing_idx = rtw8821c_get_swing_index(rtwdev);

	अगर (swing_idx >= ARRAY_SIZE(rtw8821c_txscale_tbl))
		dm_info->शेष_ofdm_index = 24;
	अन्यथा
		dm_info->शेष_ofdm_index = swing_idx;

	ewma_thermal_init(&dm_info->avg_thermal[RF_PATH_A]);
	dm_info->delta_घातer_index[RF_PATH_A] = 0;
	dm_info->delta_घातer_index_last[RF_PATH_A] = 0;
	dm_info->pwr_trk_triggered = false;
	dm_info->pwr_trk_init_trigger = true;
	dm_info->thermal_meter_k = rtwdev->efuse.thermal_meter_k;
पूर्ण

अटल व्योम rtw8821c_phy_bf_init(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_bf_phy_init(rtwdev);
	/* Grouping biपंचांगap parameters */
	rtw_ग_लिखो32(rtwdev, 0x1C94, 0xAFFFAFFF);
पूर्ण

अटल व्योम rtw8821c_phy_set_param(काष्ठा rtw_dev *rtwdev)
अणु
	u8 crystal_cap, val;

	/* घातer on BB/RF करोमुख्य */
	val = rtw_पढ़ो8(rtwdev, REG_SYS_FUNC_EN);
	val |= BIT_FEN_PCIEA;
	rtw_ग_लिखो8(rtwdev, REG_SYS_FUNC_EN, val);

	/* toggle BB reset */
	val |= BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST;
	rtw_ग_लिखो8(rtwdev, REG_SYS_FUNC_EN, val);
	val &= ~(BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST);
	rtw_ग_लिखो8(rtwdev, REG_SYS_FUNC_EN, val);
	val |= BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST;
	rtw_ग_लिखो8(rtwdev, REG_SYS_FUNC_EN, val);

	rtw_ग_लिखो8(rtwdev, REG_RF_CTRL,
		   BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	usleep_range(10, 11);
	rtw_ग_लिखो8(rtwdev, REG_WLRF1 + 3,
		   BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	usleep_range(10, 11);

	/* pre init beक्रमe header files config */
	rtw_ग_लिखो32_clr(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);

	rtw_phy_load_tables(rtwdev);

	crystal_cap = rtwdev->efuse.crystal_cap & 0x3F;
	rtw_ग_लिखो32_mask(rtwdev, REG_AFE_XTAL_CTRL, 0x7e000000, crystal_cap);
	rtw_ग_लिखो32_mask(rtwdev, REG_AFE_PLL_CTRL, 0x7e, crystal_cap);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK0_FAREPORT, BIT(18) | BIT(22), 0);

	/* post init after header files config */
	rtw_ग_लिखो32_set(rtwdev, REG_RXPSEL, BIT_RX_PSEL_RST);
	rtwdev->chip->ch_param[0] = rtw_पढ़ो32_mask(rtwdev, REG_TXSF2, MASKDWORD);
	rtwdev->chip->ch_param[1] = rtw_पढ़ो32_mask(rtwdev, REG_TXSF6, MASKDWORD);
	rtwdev->chip->ch_param[2] = rtw_पढ़ो32_mask(rtwdev, REG_TXFILTER, MASKDWORD);

	rtw_phy_init(rtwdev);
	rtwdev->dm_info.cck_pd_शेष = rtw_पढ़ो8(rtwdev, REG_CSRATIO) & 0x1f;

	rtw8821c_pwrtrack_init(rtwdev);

	rtw8821c_phy_bf_init(rtwdev);
पूर्ण

अटल पूर्णांक rtw8821c_mac_init(काष्ठा rtw_dev *rtwdev)
अणु
	u32 value32;
	u16 pre_txcnt;

	/* protocol configuration */
	rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME_V1, WLAN_AMPDU_MAX_TIME);
	rtw_ग_लिखो8_set(rtwdev, REG_TX_HANG_CTRL, BIT_EN_खातापूर्ण_V1);
	pre_txcnt = WLAN_PRE_TXCNT_TIME_TH | BIT_EN_PRECNT;
	rtw_ग_लिखो8(rtwdev, REG_PRECNT_CTRL, (u8)(pre_txcnt & 0xFF));
	rtw_ग_लिखो8(rtwdev, REG_PRECNT_CTRL + 1, (u8)(pre_txcnt >> 8));
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
	rtw_ग_लिखो8_set(rtwdev, REG_INIRTS_RATE_SEL, BIT(5));

	/* EDCA configuration */
	rtw_ग_लिखो8_clr(rtwdev, REG_TIMER0_SRC_SEL, BIT_TSFT_SEL_TIMER0);
	rtw_ग_लिखो16(rtwdev, REG_TXPAUSE, 0);
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
	rtw_ग_लिखो8(rtwdev, REG_ACKTO_CCK, 0x40);
	rtw_ग_लिखो8_set(rtwdev, REG_WMAC_TRXPTCL_CTL_H, BIT(1));
	rtw_ग_लिखो8_set(rtwdev, REG_SND_PTCL_CTRL, BIT(6));
	rtw_ग_लिखो32(rtwdev, REG_WMAC_OPTION_FUNCTION + 8, WLAN_MAC_OPT_FUNC2);
	rtw_ग_लिखो8(rtwdev, REG_WMAC_OPTION_FUNCTION + 4, WLAN_MAC_OPT_NORM_FUNC1);

	वापस 0;
पूर्ण

अटल व्योम rtw8821c_cfg_lकरो25(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 lकरो_pwr;

	lकरो_pwr = rtw_पढ़ो8(rtwdev, REG_LDO_EFUSE_CTRL + 3);
	lकरो_pwr = enable ? lकरो_pwr | BIT(7) : lकरो_pwr & ~BIT(7);
	rtw_ग_लिखो8(rtwdev, REG_LDO_EFUSE_CTRL + 3, lकरो_pwr);
पूर्ण

अटल व्योम rtw8821c_चयन_rf_set(काष्ठा rtw_dev *rtwdev, u8 rf_set)
अणु
	u32 reg;

	rtw_ग_लिखो32_set(rtwdev, REG_DMEM_CTRL, BIT_WL_RST);
	rtw_ग_लिखो32_set(rtwdev, REG_SYS_CTRL, BIT_FEN_EN);

	reg = rtw_पढ़ो32(rtwdev, REG_RFECTL);
	चयन (rf_set) अणु
	हाल SWITCH_TO_BTG:
		reg |= B_BTG_SWITCH;
		reg &= ~(B_CTRL_SWITCH | B_WL_SWITCH | B_WLG_SWITCH |
			 B_WLA_SWITCH);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENRXCCA, MASKBYTE2, BTG_CCA);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, MASKLWORD, BTG_LNA);
		अवरोध;
	हाल SWITCH_TO_WLG:
		reg |= B_WL_SWITCH | B_WLG_SWITCH;
		reg &= ~(B_BTG_SWITCH | B_CTRL_SWITCH | B_WLA_SWITCH);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENRXCCA, MASKBYTE2, WLG_CCA);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, MASKLWORD, WLG_LNA);
		अवरोध;
	हाल SWITCH_TO_WLA:
		reg |= B_WL_SWITCH | B_WLA_SWITCH;
		reg &= ~(B_BTG_SWITCH | B_CTRL_SWITCH | B_WLG_SWITCH);
		अवरोध;
	हाल SWITCH_TO_BT:
	शेष:
		अवरोध;
	पूर्ण

	rtw_ग_लिखो32(rtwdev, REG_RFECTL, reg);
पूर्ण

अटल व्योम rtw8821c_set_channel_rf(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw)
अणु
	u32 rf_reg18;

	rf_reg18 = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK);

	rf_reg18 &= ~(RF18_BAND_MASK | RF18_CHANNEL_MASK | RF18_RFSI_MASK |
		      RF18_BW_MASK);

	rf_reg18 |= (channel <= 14 ? RF18_BAND_2G : RF18_BAND_5G);
	rf_reg18 |= (channel & RF18_CHANNEL_MASK);

	अगर (channel >= 100 && channel <= 140)
		rf_reg18 |= RF18_RFSI_GE;
	अन्यथा अगर (channel > 140)
		rf_reg18 |= RF18_RFSI_GT;

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

	अगर (channel <= 14) अणु
		अगर (rtwdev->efuse.rfe_option == 0)
			rtw8821c_चयन_rf_set(rtwdev, SWITCH_TO_WLG);
		अन्यथा अगर (rtwdev->efuse.rfe_option == 2)
			rtw8821c_चयन_rf_set(rtwdev, SWITCH_TO_BTG);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTDBG, BIT(6), 0x1);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0x64, 0xf, 0xf);
	पूर्ण अन्यथा अणु
		rtw8821c_चयन_rf_set(rtwdev, SWITCH_TO_WLA);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTDBG, BIT(6), 0x0);
	पूर्ण

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK, rf_reg18);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_XTALX2, BIT(19), 0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_XTALX2, BIT(19), 1);
पूर्ण

अटल व्योम rtw8821c_set_channel_rxdfir(काष्ठा rtw_dev *rtwdev, u8 bw)
अणु
	अगर (bw == RTW_CHANNEL_WIDTH_40) अणु
		/* RX DFIR क्रम BW40 */
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR, BIT(31), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CHFIR, BIT(31), 0x0);
	पूर्ण अन्यथा अगर (bw == RTW_CHANNEL_WIDTH_80) अणु
		/* RX DFIR क्रम BW80 */
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR, BIT(31), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CHFIR, BIT(31), 0x1);
	पूर्ण अन्यथा अणु
		/* RX DFIR क्रम BW20, BW10 and BW5 */
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBB0, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_ACBBRXFIR, BIT(29) | BIT(28), 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR, BIT(31), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CHFIR, BIT(31), 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8821c_set_channel_bb(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				    u8 primary_ch_idx)
अणु
	u32 val32;

	अगर (channel <= 14) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 15);

		rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, 0xf00, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x96a);
		अगर (channel == 14) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF2, MASKDWORD, 0x0000b81c);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF6, MASKLWORD, 0x0000);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXFILTER, MASKDWORD, 0x00003667);
		पूर्ण अन्यथा अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF2, MASKDWORD,
					 rtwdev->chip->ch_param[0]);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSF6, MASKLWORD,
					 rtwdev->chip->ch_param[1] & MASKLWORD);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXFILTER, MASKDWORD,
					 rtwdev->chip->ch_param[2]);
		पूर्ण
	पूर्ण अन्यथा अगर (channel > 35) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ENTXCCK, BIT(18), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_CHECK, BIT(7), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXPSEL, BIT(28), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCAMSK, 0x0000FC00, 15);

		अगर (channel >= 36 && channel <= 64)
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, 0xf00, 0x1);
		अन्यथा अगर (channel >= 100 && channel <= 144)
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, 0xf00, 0x2);
		अन्यथा अगर (channel >= 149)
			rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, 0xf00, 0x3);

		अगर (channel >= 36 && channel <= 48)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x494);
		अन्यथा अगर (channel >= 52 && channel <= 64)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x453);
		अन्यथा अगर (channel >= 100 && channel <= 116)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x452);
		अन्यथा अगर (channel >= 118 && channel <= 177)
			rtw_ग_लिखो32_mask(rtwdev, REG_CLKTRK, 0x1ffe0000, 0x412);
	पूर्ण

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_20:
	शेष:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xffcffc00;
		val32 |= 0x10010000;
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		अगर (primary_ch_idx == 1)
			rtw_ग_लिखो32_set(rtwdev, REG_RXSB, BIT(4));
		अन्यथा
			rtw_ग_लिखो32_clr(rtwdev, REG_RXSB, BIT(4));

		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xff3ff300;
		val32 |= 0x20020000 | ((primary_ch_idx & 0xf) << 2) |
			 RTW_CHANNEL_WIDTH_40;
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xfcffcf00;
		val32 |= 0x40040000 | ((primary_ch_idx & 0xf) << 2) |
			 RTW_CHANNEL_WIDTH_80;
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_5:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xefcefc00;
		val32 |= 0x200240;
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_10:
		val32 = rtw_पढ़ो32_mask(rtwdev, REG_ADCCLK, MASKDWORD);
		val32 &= 0xefcefc00;
		val32 |= 0x300380;
		rtw_ग_लिखो32_mask(rtwdev, REG_ADCCLK, MASKDWORD, val32);

		rtw_ग_लिखो32_mask(rtwdev, REG_ADC160, BIT(30), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ADC40, BIT(31), 0x1);
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 rtw8821c_get_bb_swing(काष्ठा rtw_dev *rtwdev, u8 channel)
अणु
	काष्ठा rtw_efuse efuse = rtwdev->efuse;
	u8 tx_bb_swing;
	u32 swing2setting[4] = अणु0x200, 0x16a, 0x101, 0x0b6पूर्ण;

	tx_bb_swing = channel <= 14 ? efuse.tx_bb_swing_setting_2g :
				      efuse.tx_bb_swing_setting_5g;
	अगर (tx_bb_swing > 9)
		tx_bb_swing = 0;

	वापस swing2setting[(tx_bb_swing / 3)];
पूर्ण

अटल व्योम rtw8821c_set_channel_bb_swing(काष्ठा rtw_dev *rtwdev, u8 channel,
					  u8 bw, u8 primary_ch_idx)
अणु
	rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, GENMASK(31, 21),
			 rtw8821c_get_bb_swing(rtwdev, channel));
	rtw8821c_pwrtrack_init(rtwdev);
पूर्ण

अटल व्योम rtw8821c_set_channel(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				 u8 primary_chan_idx)
अणु
	rtw8821c_set_channel_bb(rtwdev, channel, bw, primary_chan_idx);
	rtw8821c_set_channel_bb_swing(rtwdev, channel, bw, primary_chan_idx);
	rtw_set_channel_mac(rtwdev, channel, bw, primary_chan_idx);
	rtw8821c_set_channel_rf(rtwdev, channel, bw);
	rtw8821c_set_channel_rxdfir(rtwdev, bw);
पूर्ण

अटल s8 get_cck_rx_pwr(काष्ठा rtw_dev *rtwdev, u8 lna_idx, u8 vga_idx)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	स्थिर s8 *lna_gain_table;
	पूर्णांक lna_gain_table_size;
	s8 rx_pwr_all = 0;
	s8 lna_gain = 0;

	अगर (efuse->rfe_option == 0) अणु
		lna_gain_table = lna_gain_table_0;
		lna_gain_table_size = ARRAY_SIZE(lna_gain_table_0);
	पूर्ण अन्यथा अणु
		lna_gain_table = lna_gain_table_1;
		lna_gain_table_size = ARRAY_SIZE(lna_gain_table_1);
	पूर्ण

	अगर (lna_idx >= lna_gain_table_size) अणु
		rtw_info(rtwdev, "incorrect lna index (%d)\n", lna_idx);
		वापस -120;
	पूर्ण

	lna_gain = lna_gain_table[lna_idx];
	rx_pwr_all = lna_gain - 2 * vga_idx;

	वापस rx_pwr_all;
पूर्ण

अटल व्योम query_phy_status_page0(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	s8 rx_घातer;
	u8 lna_idx = 0;
	u8 vga_idx = 0;

	vga_idx = GET_PHY_STAT_P0_VGA(phy_status);
	lna_idx = FIELD_PREP(BIT_LNA_H_MASK, GET_PHY_STAT_P0_LNA_H(phy_status)) |
		  FIELD_PREP(BIT_LNA_L_MASK, GET_PHY_STAT_P0_LNA_L(phy_status));
	rx_घातer = get_cck_rx_pwr(rtwdev, lna_idx, vga_idx);

	pkt_stat->rx_घातer[RF_PATH_A] = rx_घातer;
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 1);
	pkt_stat->bw = RTW_CHANNEL_WIDTH_20;
	pkt_stat->संकेत_घातer = rx_घातer;
पूर्ण

अटल व्योम query_phy_status_page1(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	u8 rxsc, bw;
	s8 min_rx_घातer = -120;

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
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 1);
	pkt_stat->bw = bw;
	pkt_stat->संकेत_घातer = max(pkt_stat->rx_घातer[RF_PATH_A],
				     min_rx_घातer);
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

अटल व्योम rtw8821c_query_rx_desc(काष्ठा rtw_dev *rtwdev, u8 *rx_desc,
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
rtw8821c_set_tx_घातer_index_by_rate(काष्ठा rtw_dev *rtwdev, u8 path, u8 rs)
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
		अगर (shअगरt == 0x3 || rate == DESC_RATEVHT1SS_MCS9) अणु
			rate_idx = rate & 0xfc;
			rtw_ग_लिखो32(rtwdev, offset_txagc[path] + rate_idx,
				    phy_pwr_idx);
			phy_pwr_idx = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8821c_set_tx_घातer_index(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	पूर्णांक rs, path;

	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		क्रम (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++) अणु
			अगर (rs == RTW_RATE_SECTION_HT_2S ||
			    rs == RTW_RATE_SECTION_VHT_2S)
				जारी;
			rtw8821c_set_tx_घातer_index_by_rate(rtwdev, path, rs);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8821c_false_alarm_statistics(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_enable;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 crc32_cnt;
	u32 cca32_cnt;

	cck_enable = rtw_पढ़ो32(rtwdev, REG_RXPSEL) & BIT(28);
	cck_fa_cnt = rtw_पढ़ो16(rtwdev, REG_FA_CCK);
	ofdm_fa_cnt = rtw_पढ़ो16(rtwdev, REG_FA_OFDM);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	अगर (cck_enable)
		dm_info->total_fa_cnt += cck_fa_cnt;
	dm_info->total_fa_cnt = ofdm_fa_cnt;

	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_CRC_CCK);
	dm_info->cck_ok_cnt = FIELD_GET(GENMASK(15, 0), crc32_cnt);
	dm_info->cck_err_cnt = FIELD_GET(GENMASK(31, 16), crc32_cnt);

	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_CRC_OFDM);
	dm_info->ofdm_ok_cnt = FIELD_GET(GENMASK(15, 0), crc32_cnt);
	dm_info->ofdm_err_cnt = FIELD_GET(GENMASK(31, 16), crc32_cnt);

	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_CRC_HT);
	dm_info->ht_ok_cnt = FIELD_GET(GENMASK(15, 0), crc32_cnt);
	dm_info->ht_err_cnt = FIELD_GET(GENMASK(31, 16), crc32_cnt);

	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_CRC_VHT);
	dm_info->vht_ok_cnt = FIELD_GET(GENMASK(15, 0), crc32_cnt);
	dm_info->vht_err_cnt = FIELD_GET(GENMASK(31, 16), crc32_cnt);

	cca32_cnt = rtw_पढ़ो32(rtwdev, REG_CCA_OFDM);
	dm_info->ofdm_cca_cnt = FIELD_GET(GENMASK(31, 16), cca32_cnt);
	dm_info->total_cca_cnt = dm_info->ofdm_cca_cnt;
	अगर (cck_enable) अणु
		cca32_cnt = rtw_पढ़ो32(rtwdev, REG_CCA_CCK);
		dm_info->cck_cca_cnt = FIELD_GET(GENMASK(15, 0), cca32_cnt);
		dm_info->total_cca_cnt += dm_info->cck_cca_cnt;
	पूर्ण

	rtw_ग_लिखो32_set(rtwdev, REG_FAS, BIT(17));
	rtw_ग_लिखो32_clr(rtwdev, REG_FAS, BIT(17));
	rtw_ग_लिखो32_clr(rtwdev, REG_RXDESC, BIT(15));
	rtw_ग_लिखो32_set(rtwdev, REG_RXDESC, BIT(15));
	rtw_ग_लिखो32_set(rtwdev, REG_CNTRST, BIT(0));
	rtw_ग_लिखो32_clr(rtwdev, REG_CNTRST, BIT(0));
पूर्ण

अटल व्योम rtw8821c_करो_iqk(काष्ठा rtw_dev *rtwdev)
अणु
	अटल पूर्णांक करो_iqk_cnt;
	काष्ठा rtw_iqk_para para = अणु.clear = 0, .segment_iqk = 0पूर्ण;
	u32 rf_reg, iqk_fail_mask;
	पूर्णांक counter;
	bool reload;

	अगर (rtw_is_assoc(rtwdev))
		para.segment_iqk = 1;

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

अटल व्योम rtw8821c_phy_calibration(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8821c_करो_iqk(rtwdev);
पूर्ण

/* क्रम coex */
अटल व्योम rtw8821c_coex_cfg_init(काष्ठा rtw_dev *rtwdev)
अणु
	/* enable TBTT nterrupt */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	/* BT report packet sample rate */
	rtw_ग_लिखो8_mask(rtwdev, REG_BT_TDMA_TIME, BIT_MASK_SAMPLE_RATE, 0x5);

	/* enable BT counter statistics */
	rtw_ग_लिखो8(rtwdev, REG_BT_STAT_CTRL, BT_CNT_ENABLE);

	/* enable PTA (3-wire function क्रमm BT side) */
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enable PTA (tx/rx संकेत क्रमm WiFi side) */
	rtw_ग_लिखो8_set(rtwdev, REG_QUEUE_CTRL, BIT_PTA_WL_TX_EN);
	/* wl tx संकेत to PTA not हाल EDCCA */
	rtw_ग_लिखो8_clr(rtwdev, REG_QUEUE_CTRL, BIT_PTA_EDCCA_EN);
	/* GNT_BT=1 जबतक select both */
	rtw_ग_लिखो16_set(rtwdev, REG_BT_COEX_V2, BIT_GNT_BT_POLARITY);

	/* beacon queue always hi-pri  */
	rtw_ग_लिखो8_mask(rtwdev, REG_BT_COEX_TABLE_H + 3, BIT_BCN_QUEUE,
			BCN_PRI_EN);
पूर्ण

अटल व्योम rtw8821c_coex_cfg_ant_चयन(काष्ठा rtw_dev *rtwdev, u8 ctrl_type,
					 u8 pos_type)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	u32 चयन_status = FIELD_PREP(CTRL_TYPE_MASK, ctrl_type) | pos_type;
	bool polarity_inverse;
	u8 regval = 0;

	अगर (चयन_status == coex_dm->cur_चयन_status)
		वापस;

	coex_dm->cur_चयन_status = चयन_status;

	अगर (coex_rfe->ant_चयन_भागersity &&
	    ctrl_type == COEX_SWITCH_CTRL_BY_BBSW)
		ctrl_type = COEX_SWITCH_CTRL_BY_ANTDIV;

	polarity_inverse = (coex_rfe->ant_चयन_polarity == 1);

	चयन (ctrl_type) अणु
	शेष:
	हाल COEX_SWITCH_CTRL_BY_BBSW:
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_LED_CFG, BIT_DPDT_WL_SEL);
		/* BB SW, DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89,
				DPDT_CTRL_PIN);

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

		rtw_ग_लिखो32_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_R_RFE_SEL_15,
				 regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_PTA:
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_LED_CFG, BIT_DPDT_WL_SEL);
		/* PTA,  DPDT use RFE_ctrl8 and RFE_ctrl9 as ctrl pin */
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89,
				PTA_CTRL_PIN);

		regval = (!polarity_inverse ? 0x2 : 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_R_RFE_SEL_15,
				 regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_ANTDIV:
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_LED_CFG, BIT_DPDT_WL_SEL);
		rtw_ग_लिखो8_mask(rtwdev, REG_RFE_CTRL8, BIT_MASK_RFE_SEL89,
				ANTDIC_CTRL_PIN);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_MAC:
		rtw_ग_लिखो32_set(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);

		regval = (!polarity_inverse ? 0x0 : 0x1);
		rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1, BIT_SW_DPDT_SEL_DATA,
				regval);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_FW:
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_LED_CFG, BIT_DPDT_WL_SEL);
		अवरोध;
	हाल COEX_SWITCH_CTRL_BY_BT:
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_SEL_EN);
		rtw_ग_लिखो32_clr(rtwdev, REG_LED_CFG, BIT_DPDT_WL_SEL);
		अवरोध;
	पूर्ण

	अगर (ctrl_type == COEX_SWITCH_CTRL_BY_BT) अणु
		rtw_ग_लिखो8_clr(rtwdev, REG_CTRL_TYPE, BIT_CTRL_TYPE1);
		rtw_ग_लिखो8_clr(rtwdev, REG_CTRL_TYPE, BIT_CTRL_TYPE2);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8_set(rtwdev, REG_CTRL_TYPE, BIT_CTRL_TYPE1);
		rtw_ग_लिखो8_set(rtwdev, REG_CTRL_TYPE, BIT_CTRL_TYPE2);
	पूर्ण
पूर्ण

अटल व्योम rtw8821c_coex_cfg_gnt_fix(काष्ठा rtw_dev *rtwdev)
अणुपूर्ण

अटल व्योम rtw8821c_coex_cfg_gnt_debug(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32_clr(rtwdev, REG_PAD_CTRL1, BIT_BTGP_SPI_EN);
	rtw_ग_लिखो32_clr(rtwdev, REG_PAD_CTRL1, BIT_BTGP_JTAG_EN);
	rtw_ग_लिखो32_clr(rtwdev, REG_GPIO_MUXCFG, BIT_FSPI_EN);
	rtw_ग_लिखो32_clr(rtwdev, REG_PAD_CTRL1, BIT_LED1DIS);
	rtw_ग_लिखो32_clr(rtwdev, REG_SYS_SDIO_CTRL, BIT_SDIO_INT);
	rtw_ग_लिखो32_clr(rtwdev, REG_SYS_SDIO_CTRL, BIT_DBG_GNT_WL_BT);
पूर्ण

अटल व्योम rtw8821c_coex_cfg_rfe_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;

	coex_rfe->rfe_module_type = efuse->rfe_option;
	coex_rfe->ant_चयन_polarity = 0;
	coex_rfe->ant_चयन_exist = true;
	coex_rfe->wlg_at_btg = false;

	चयन (coex_rfe->rfe_module_type) अणु
	हाल 0:
	हाल 8:
	हाल 1:
	हाल 9:  /* 1-Ant, Main, WLG */
	शेष: /* 2-Ant, DPDT, WLG */
		अवरोध;
	हाल 2:
	हाल 10: /* 1-Ant, Main, BTG */
	हाल 7:
	हाल 15: /* 2-Ant, DPDT, BTG */
		coex_rfe->wlg_at_btg = true;
		अवरोध;
	हाल 3:
	हाल 11: /* 1-Ant, Aux, WLG */
		coex_rfe->ant_चयन_polarity = 1;
		अवरोध;
	हाल 4:
	हाल 12: /* 1-Ant, Aux, BTG */
		coex_rfe->wlg_at_btg = true;
		coex_rfe->ant_चयन_polarity = 1;
		अवरोध;
	हाल 5:
	हाल 13: /* 2-Ant, no चयन, WLG */
	हाल 6:
	हाल 14: /* 2-Ant, no antenna चयन, WLG */
		coex_rfe->ant_चयन_exist = false;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8821c_coex_cfg_wl_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 wl_pwr)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	bool share_ant = efuse->share_ant;

	अगर (share_ant)
		वापस;

	अगर (wl_pwr == coex_dm->cur_wl_pwr_lvl)
		वापस;

	coex_dm->cur_wl_pwr_lvl = wl_pwr;
पूर्ण

अटल व्योम rtw8821c_coex_cfg_wl_rx_gain(काष्ठा rtw_dev *rtwdev, bool low_gain)
अणुपूर्ण

अटल व्योम
rtw8821c_txagc_swing_offset(काष्ठा rtw_dev *rtwdev, u8 pwr_idx_offset,
			    s8 pwr_idx_offset_lower,
			    s8 *txagc_idx, u8 *swing_idx)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 delta_pwr_idx = dm_info->delta_घातer_index[RF_PATH_A];
	u8 swing_upper_bound = dm_info->शेष_ofdm_index + 10;
	u8 swing_lower_bound = 0;
	u8 max_pwr_idx_offset = 0xf;
	s8 agc_index = 0;
	u8 swing_index = dm_info->शेष_ofdm_index;

	pwr_idx_offset = min_t(u8, pwr_idx_offset, max_pwr_idx_offset);
	pwr_idx_offset_lower = max_t(s8, pwr_idx_offset_lower, -15);

	अगर (delta_pwr_idx >= 0) अणु
		अगर (delta_pwr_idx <= pwr_idx_offset) अणु
			agc_index = delta_pwr_idx;
			swing_index = dm_info->शेष_ofdm_index;
		पूर्ण अन्यथा अगर (delta_pwr_idx > pwr_idx_offset) अणु
			agc_index = pwr_idx_offset;
			swing_index = dm_info->शेष_ofdm_index +
					delta_pwr_idx - pwr_idx_offset;
			swing_index = min_t(u8, swing_index, swing_upper_bound);
		पूर्ण
	पूर्ण अन्यथा अगर (delta_pwr_idx < 0) अणु
		अगर (delta_pwr_idx >= pwr_idx_offset_lower) अणु
			agc_index = delta_pwr_idx;
			swing_index = dm_info->शेष_ofdm_index;
		पूर्ण अन्यथा अगर (delta_pwr_idx < pwr_idx_offset_lower) अणु
			अगर (dm_info->शेष_ofdm_index >
				(pwr_idx_offset_lower - delta_pwr_idx))
				swing_index = dm_info->शेष_ofdm_index +
					delta_pwr_idx - pwr_idx_offset_lower;
			अन्यथा
				swing_index = swing_lower_bound;

			agc_index = pwr_idx_offset_lower;
		पूर्ण
	पूर्ण

	अगर (swing_index >= ARRAY_SIZE(rtw8821c_txscale_tbl)) अणु
		rtw_warn(rtwdev, "swing index overflow\n");
		swing_index = ARRAY_SIZE(rtw8821c_txscale_tbl) - 1;
	पूर्ण

	*txagc_idx = agc_index;
	*swing_idx = swing_index;
पूर्ण

अटल व्योम rtw8821c_pwrtrack_set_pwr(काष्ठा rtw_dev *rtwdev, u8 pwr_idx_offset,
				      s8 pwr_idx_offset_lower)
अणु
	s8 txagc_idx;
	u8 swing_idx;

	rtw8821c_txagc_swing_offset(rtwdev, pwr_idx_offset, pwr_idx_offset_lower,
				    &txagc_idx, &swing_idx);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXAGCIDX, GENMASK(6, 1), txagc_idx);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXSCALE_A, GENMASK(31, 21),
			 rtw8821c_txscale_tbl[swing_idx]);
पूर्ण

अटल व्योम rtw8821c_pwrtrack_set(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 pwr_idx_offset, tx_pwr_idx;
	s8 pwr_idx_offset_lower;
	u8 channel = rtwdev->hal.current_channel;
	u8 band_width = rtwdev->hal.current_band_width;
	u8 regd = rtwdev->regd.txpwr_regd;
	u8 tx_rate = dm_info->tx_rate;
	u8 max_pwr_idx = rtwdev->chip->max_घातer_index;

	tx_pwr_idx = rtw_phy_get_tx_घातer_index(rtwdev, RF_PATH_A, tx_rate,
						band_width, channel, regd);

	tx_pwr_idx = min_t(u8, tx_pwr_idx, max_pwr_idx);

	pwr_idx_offset = max_pwr_idx - tx_pwr_idx;
	pwr_idx_offset_lower = 0 - tx_pwr_idx;

	rtw8821c_pwrtrack_set_pwr(rtwdev, pwr_idx_offset, pwr_idx_offset_lower);
पूर्ण

अटल व्योम rtw8821c_phy_pwrtrack(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_swing_table swing_table;
	u8 thermal_value, delta;

	rtw_phy_config_swing_table(rtwdev, &swing_table);

	अगर (rtwdev->efuse.thermal_meter[0] == 0xff)
		वापस;

	thermal_value = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_T_METER, 0xfc00);

	rtw_phy_pwrtrack_avg(rtwdev, thermal_value, RF_PATH_A);

	अगर (dm_info->pwr_trk_init_trigger)
		dm_info->pwr_trk_init_trigger = false;
	अन्यथा अगर (!rtw_phy_pwrtrack_thermal_changed(rtwdev, thermal_value,
						   RF_PATH_A))
		जाओ iqk;

	delta = rtw_phy_pwrtrack_get_delta(rtwdev, RF_PATH_A);

	delta = min_t(u8, delta, RTW_PWR_TRK_TBL_SZ - 1);

	dm_info->delta_घातer_index[RF_PATH_A] =
		rtw_phy_pwrtrack_get_pwridx(rtwdev, &swing_table, RF_PATH_A,
					    RF_PATH_A, delta);
	अगर (dm_info->delta_घातer_index[RF_PATH_A] ==
			dm_info->delta_घातer_index_last[RF_PATH_A])
		जाओ iqk;
	अन्यथा
		dm_info->delta_घातer_index_last[RF_PATH_A] =
			dm_info->delta_घातer_index[RF_PATH_A];
	rtw8821c_pwrtrack_set(rtwdev);

iqk:
	अगर (rtw_phy_pwrtrack_need_iqk(rtwdev))
		rtw8821c_करो_iqk(rtwdev);
पूर्ण

अटल व्योम rtw8821c_pwr_track(काष्ठा rtw_dev *rtwdev)
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

	rtw8821c_phy_pwrtrack(rtwdev);
	dm_info->pwr_trk_triggered = false;
पूर्ण

अटल व्योम rtw8821c_bf_config_bfee_su(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw_bf_enable_bfee_su(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_su(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8821c_bf_config_bfee_mu(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw_bf_enable_bfee_mu(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_mu(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8821c_bf_config_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
				    काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (bfee->role == RTW_BFEE_SU)
		rtw8821c_bf_config_bfee_su(rtwdev, vअगर, bfee, enable);
	अन्यथा अगर (bfee->role == RTW_BFEE_MU)
		rtw8821c_bf_config_bfee_mu(rtwdev, vअगर, bfee, enable);
	अन्यथा
		rtw_warn(rtwdev, "wrong bfee role\n");
पूर्ण

अटल व्योम rtw8821c_phy_cck_pd_set(काष्ठा rtw_dev *rtwdev, u8 new_lvl)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 pd[CCK_PD_LV_MAX] = अणु3, 7, 13, 13, 13पूर्ण;
	u8 cck_n_rx;

	rtw_dbg(rtwdev, RTW_DBG_PHY, "lv: (%d) -> (%d)\n",
		dm_info->cck_pd_lv[RTW_CHANNEL_WIDTH_20][RF_PATH_A], new_lvl);

	अगर (dm_info->cck_pd_lv[RTW_CHANNEL_WIDTH_20][RF_PATH_A] == new_lvl)
		वापस;

	cck_n_rx = (rtw_पढ़ो8_mask(rtwdev, REG_CCK0_FAREPORT, BIT_CCK0_2RX) &&
		    rtw_पढ़ो8_mask(rtwdev, REG_CCK0_FAREPORT, BIT_CCK0_MRC)) ? 2 : 1;
	rtw_dbg(rtwdev, RTW_DBG_PHY,
		"is_linked=%d, lv=%d, n_rx=%d, cs_ratio=0x%x, pd_th=0x%x, cck_fa_avg=%d\n",
		rtw_is_assoc(rtwdev), new_lvl, cck_n_rx,
		dm_info->cck_pd_शेष + new_lvl * 2,
		pd[new_lvl], dm_info->cck_fa_avg);

	dm_info->cck_fa_avg = CCK_FA_AVG_RESET;

	dm_info->cck_pd_lv[RTW_CHANNEL_WIDTH_20][RF_PATH_A] = new_lvl;
	rtw_ग_लिखो32_mask(rtwdev, REG_PWRTH, 0x3f0000, pd[new_lvl]);
	rtw_ग_लिखो32_mask(rtwdev, REG_PWRTH2, 0x1f0000,
			 dm_info->cck_pd_शेष + new_lvl * 2);
पूर्ण

अटल काष्ठा rtw_pwr_seq_cmd trans_carddis_to_cardemu_8821c[] = अणु
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

अटल काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_act_8821c[] = अणु
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
	अणु0x0074,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0x0022,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0062,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6) | BIT(5)),
	 (BIT(7) | BIT(6) | BIT(5))पूर्ण,
	अणु0x0061,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6) | BIT(5)), 0पूर्ण,
	अणु0x007C,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल काष्ठा rtw_pwr_seq_cmd trans_act_to_cardemu_8821c[] = अणु
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

अटल काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_carddis_8821c[] = अणु
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

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_enable_flow_8821c[] = अणु
	trans_carddis_to_cardemu_8821c,
	trans_cardemu_to_act_8821c,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_disable_flow_8821c[] = अणु
	trans_act_to_cardemu_8821c,
	trans_cardemu_to_carddis_8821c,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb2_param_8821c[] = अणु
	अणु0xFFFF, 0x00,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb3_param_8821c[] = अणु
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen1_param_8821c[] = अणु
	अणु0x0009, 0x6380,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen2_param_8821c[] = अणु
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para_table phy_para_table_8821c = अणु
	.usb2_para	= usb2_param_8821c,
	.usb3_para	= usb3_param_8821c,
	.gen1_para	= pcie_gen1_param_8821c,
	.gen2_para	= pcie_gen2_param_8821c,
	.n_usb2_para	= ARRAY_SIZE(usb2_param_8821c),
	.n_usb3_para	= ARRAY_SIZE(usb2_param_8821c),
	.n_gen1_para	= ARRAY_SIZE(pcie_gen1_param_8821c),
	.n_gen2_para	= ARRAY_SIZE(pcie_gen2_param_8821c),
पूर्ण;

अटल स्थिर काष्ठा rtw_rfe_def rtw8821c_rfe_defs[] = अणु
	[0] = RTW_DEF_RFE(8821c, 0, 0),
	[2] = RTW_DEF_RFE_EXT(8821c, 0, 0, 2),
पूर्ण;

अटल काष्ठा rtw_hw_reg rtw8821c_dig[] = अणु
	[0] = अणु .addr = 0xc50, .mask = 0x7f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_ltecoex_addr rtw8821c_ltecoex_addr = अणु
	.ctrl = LTECOEX_ACCESS_CTRL,
	.wdata = LTECOEX_WRITE_DATA,
	.rdata = LTECOEX_READ_DATA,
पूर्ण;

अटल काष्ठा rtw_page_table page_table_8821c[] = अणु
	/* not sure what [0] stands क्रम */
	अणु16, 16, 16, 14, 1पूर्ण,
	अणु16, 16, 16, 14, 1पूर्ण,
	अणु16, 16, 0, 0, 1पूर्ण,
	अणु16, 16, 16, 0, 1पूर्ण,
	अणु16, 16, 16, 14, 1पूर्ण,
पूर्ण;

अटल काष्ठा rtw_rqpn rqpn_table_8821c[] = अणु
	/* not sure what [0] stands क्रम */
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

अटल काष्ठा rtw_prioq_addrs prioq_addrs_8821c = अणु
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

अटल काष्ठा rtw_chip_ops rtw8821c_ops = अणु
	.phy_set_param		= rtw8821c_phy_set_param,
	.पढ़ो_efuse		= rtw8821c_पढ़ो_efuse,
	.query_rx_desc		= rtw8821c_query_rx_desc,
	.set_channel		= rtw8821c_set_channel,
	.mac_init		= rtw8821c_mac_init,
	.पढ़ो_rf		= rtw_phy_पढ़ो_rf,
	.ग_लिखो_rf		= rtw_phy_ग_लिखो_rf_reg_sipi,
	.set_antenna		= शून्य,
	.set_tx_घातer_index	= rtw8821c_set_tx_घातer_index,
	.cfg_lकरो25		= rtw8821c_cfg_lकरो25,
	.false_alarm_statistics	= rtw8821c_false_alarm_statistics,
	.phy_calibration	= rtw8821c_phy_calibration,
	.cck_pd_set		= rtw8821c_phy_cck_pd_set,
	.pwr_track		= rtw8821c_pwr_track,
	.config_bfee		= rtw8821c_bf_config_bfee,
	.set_gid_table		= rtw_bf_set_gid_table,
	.cfg_csi_rate		= rtw_bf_cfg_csi_rate,

	.coex_set_init		= rtw8821c_coex_cfg_init,
	.coex_set_ant_चयन	= rtw8821c_coex_cfg_ant_चयन,
	.coex_set_gnt_fix	= rtw8821c_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= rtw8821c_coex_cfg_gnt_debug,
	.coex_set_rfe_type	= rtw8821c_coex_cfg_rfe_type,
	.coex_set_wl_tx_घातer	= rtw8821c_coex_cfg_wl_tx_घातer,
	.coex_set_wl_rx_gain	= rtw8821c_coex_cfg_wl_rx_gain,
पूर्ण;

/* rssi in percentage % (dbm = % - 100) */
अटल स्थिर u8 wl_rssi_step_8821c[] = अणु101, 45, 101, 40पूर्ण;
अटल स्थिर u8 bt_rssi_step_8821c[] = अणु101, 101, 101, 101पूर्ण;

/* Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_sant_8821c[] = अणु
	अणु0x55555555, 0x55555555पूर्ण, /* हाल-0 */
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
	अणु0x66555555, 0xaaaaaaaaपूर्ण,
	अणु0x66555555, 0x6a5a5aaaपूर्ण,
	अणु0x66555555, 0x6aaa6aaaपूर्ण,
	अणु0x66555555, 0x6a5a5aaaपूर्ण,
	अणु0x66555555, 0xaaaaaaaaपूर्ण, /* हाल-15 */
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffff55ff, 0x6afa5afaपूर्ण,
	अणु0xaaffffaa, 0xfafafafaपूर्ण,
	अणु0xaa5555aa, 0x5a5a5a5aपूर्ण,
	अणु0xaa5555aa, 0x6a5a5a5aपूर्ण, /* हाल-20 */
	अणु0xaa5555aa, 0xaaaaaaaaपूर्ण,
	अणु0xffffffff, 0x55555555पूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x5a5a5aaaपूर्ण, /* हाल-25 */
	अणु0x55555555, 0x5a5a5a5aपूर्ण,
	अणु0x55555555, 0xaaaaaaaaपूर्ण,
	अणु0x66555555, 0x6a5a6a5aपूर्ण,
	अणु0x66556655, 0x66556655पूर्ण,
	अणु0x66556aaa, 0x6a5a6aaaपूर्ण, /* हाल-30 */
	अणु0xffffffff, 0x5aaa5aaaपूर्ण,
	अणु0x56555555, 0x5a5a5aaaपूर्ण
पूर्ण;

/* Non-Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_nsant_8821c[] = अणु
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-100 */
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0x66555555, 0x66555555पूर्ण,
	अणु0xaaaaaaaa, 0xaaaaaaaaपूर्ण,
	अणु0x5a5a5a5a, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-105 */
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
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffffffff, 0xaaaaaaaaपूर्ण, /* हाल-120 */
	अणु0xffff55ff, 0x5afa5afaपूर्ण,
	अणु0xffff55ff, 0x5afa5afaपूर्ण,
	अणु0x55ff55ff, 0x55ff55ffपूर्ण
पूर्ण;

/* Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_sant_8821c[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-0 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-1 */
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x35, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-5 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x35, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-10 */
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x15पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-15 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x11, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x21, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-20 */
	अणु अणु0x51, 0x4a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x30, 0x54पूर्ण पूर्ण,
	अणु अणु0x55, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x65, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x51पूर्ण पूर्ण, /* हाल-25 */
	अणु अणु0x51, 0x21, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x11पूर्ण पूर्ण
पूर्ण;

/* Non-Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_nsant_8821c[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x40, 0x00पूर्ण पूर्ण, /* हाल-100 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x25, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x35, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-105 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-110 */
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-115 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x21, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x21, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-120 */
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_5g_afh_map afh_5g_8821c[] = अणु अणु0, 0, 0पूर्ण पूर्ण;

/* wl_tx_dec_घातer, bt_tx_dec_घातer, wl_rx_gain, bt_rx_lna_स्थिरrain */
अटल स्थिर काष्ठा coex_rf_para rf_para_tx_8821c[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 20, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु8, 17, true, 4पूर्ण,
	अणु7, 18, true, 4पूर्ण,
	अणु6, 19, true, 4पूर्ण,
	अणु5, 20, true, 4पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_rf_para rf_para_rx_8821c[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 20, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु3, 24, true, 5पूर्ण,
	अणु2, 26, true, 5पूर्ण,
	अणु1, 27, true, 5पूर्ण,
	अणु0, 28, true, 5पूर्ण
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(rf_para_tx_8821c) == ARRAY_SIZE(rf_para_rx_8821c));

अटल स्थिर u8 rtw8821c_pwrtrk_5gb_n[][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु0, 1, 1, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 9, 9, 9, 10, 10,
	 11, 11, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_5gb_p[][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 8, 9, 10, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_5ga_n[][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु0, 1, 1, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 9, 9, 9, 10, 10,
	 11, 11, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_5ga_p[][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 7, 7, 8, 8, 9, 10, 10, 11, 11,
	 12, 12, 12, 12, 12, 12, 12, 12पूर्ण,
	अणु0, 1, 1, 1, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 10, 10, 11,
	 11, 12, 12, 12, 12, 12, 12, 12पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2gb_n[] = अणु
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
	4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2gb_p[] = अणु
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5,
	5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2ga_n[] = अणु
	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4,
	4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 8, 8, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2ga_p[] = अणु
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5,
	5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2g_cck_b_n[] = अणु
	0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
	4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2g_cck_b_p[] = अणु
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5,
	5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2g_cck_a_n[] = अणु
	0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
	4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9
पूर्ण;

अटल स्थिर u8 rtw8821c_pwrtrk_2g_cck_a_p[] = अणु
	0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5,
	5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_track_tbl rtw8821c_rtw_pwr_track_tbl = अणु
	.pwrtrk_5gb_n[0] = rtw8821c_pwrtrk_5gb_n[0],
	.pwrtrk_5gb_n[1] = rtw8821c_pwrtrk_5gb_n[1],
	.pwrtrk_5gb_n[2] = rtw8821c_pwrtrk_5gb_n[2],
	.pwrtrk_5gb_p[0] = rtw8821c_pwrtrk_5gb_p[0],
	.pwrtrk_5gb_p[1] = rtw8821c_pwrtrk_5gb_p[1],
	.pwrtrk_5gb_p[2] = rtw8821c_pwrtrk_5gb_p[2],
	.pwrtrk_5ga_n[0] = rtw8821c_pwrtrk_5ga_n[0],
	.pwrtrk_5ga_n[1] = rtw8821c_pwrtrk_5ga_n[1],
	.pwrtrk_5ga_n[2] = rtw8821c_pwrtrk_5ga_n[2],
	.pwrtrk_5ga_p[0] = rtw8821c_pwrtrk_5ga_p[0],
	.pwrtrk_5ga_p[1] = rtw8821c_pwrtrk_5ga_p[1],
	.pwrtrk_5ga_p[2] = rtw8821c_pwrtrk_5ga_p[2],
	.pwrtrk_2gb_n = rtw8821c_pwrtrk_2gb_n,
	.pwrtrk_2gb_p = rtw8821c_pwrtrk_2gb_p,
	.pwrtrk_2ga_n = rtw8821c_pwrtrk_2ga_n,
	.pwrtrk_2ga_p = rtw8821c_pwrtrk_2ga_p,
	.pwrtrk_2g_cckb_n = rtw8821c_pwrtrk_2g_cck_b_n,
	.pwrtrk_2g_cckb_p = rtw8821c_pwrtrk_2g_cck_b_p,
	.pwrtrk_2g_ccka_n = rtw8821c_pwrtrk_2g_cck_a_n,
	.pwrtrk_2g_ccka_p = rtw8821c_pwrtrk_2g_cck_a_p,
पूर्ण;

अटल स्थिर काष्ठा rtw_reg_करोमुख्य coex_info_hw_regs_8821c[] = अणु
	अणु0xCB0, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0xCB4, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0xCBA, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
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
	अणु0x1, RFREG_MASK, RTW_REG_DOMAIN_RF_Aपूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x550, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x522, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x953, BIT(1), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xc50,  MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x60A, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
पूर्ण;

काष्ठा rtw_chip_info rtw8821c_hw_spec = अणु
	.ops = &rtw8821c_ops,
	.id = RTW_CHIP_TYPE_8821C,
	.fw_name = "rtw88/rtw8821c_fw.bin",
	.wlan_cpu = RTW_WCPU_11AC,
	.tx_pkt_desc_sz = 48,
	.tx_buf_desc_sz = 16,
	.rx_pkt_desc_sz = 24,
	.rx_buf_desc_sz = 8,
	.phy_efuse_size = 512,
	.log_efuse_size = 512,
	.ptct_efuse_size = 96,
	.txff_size = 65536,
	.rxff_size = 16384,
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
	.sys_func_en = 0xD8,
	.pwr_on_seq = card_enable_flow_8821c,
	.pwr_off_seq = card_disable_flow_8821c,
	.page_table = page_table_8821c,
	.rqpn_table = rqpn_table_8821c,
	.prioq_addrs = &prioq_addrs_8821c,
	.पूर्णांकf_table = &phy_para_table_8821c,
	.dig = rtw8821c_dig,
	.rf_base_addr = अणु0x2800, 0x2c00पूर्ण,
	.rf_sipi_addr = अणु0xc90, 0xe90पूर्ण,
	.ltecoex_addr = &rtw8821c_ltecoex_addr,
	.mac_tbl = &rtw8821c_mac_tbl,
	.agc_tbl = &rtw8821c_agc_tbl,
	.bb_tbl = &rtw8821c_bb_tbl,
	.rf_tbl = अणु&rtw8821c_rf_a_tblपूर्ण,
	.rfe_defs = rtw8821c_rfe_defs,
	.rfe_defs_size = ARRAY_SIZE(rtw8821c_rfe_defs),
	.rx_ldpc = false,
	.pwr_track_tbl = &rtw8821c_rtw_pwr_track_tbl,
	.iqk_threshold = 8,
	.bfer_su_max_num = 2,
	.bfer_mu_max_num = 1,

	.coex_para_ver = 0x19092746,
	.bt_desired_ver = 0x46,
	.scbd_support = true,
	.new_scbd10_def = false,
	.ble_hid_profile_support = false,
	.pstdma_type = COEX_PSTDMA_FORCE_LPSOFF,
	.bt_rssi_type = COEX_BTRSSI_RATIO,
	.ant_isolation = 15,
	.rssi_tolerance = 2,
	.wl_rssi_step = wl_rssi_step_8821c,
	.bt_rssi_step = bt_rssi_step_8821c,
	.table_sant_num = ARRAY_SIZE(table_sant_8821c),
	.table_sant = table_sant_8821c,
	.table_nsant_num = ARRAY_SIZE(table_nsant_8821c),
	.table_nsant = table_nsant_8821c,
	.tdma_sant_num = ARRAY_SIZE(tdma_sant_8821c),
	.tdma_sant = tdma_sant_8821c,
	.tdma_nsant_num = ARRAY_SIZE(tdma_nsant_8821c),
	.tdma_nsant = tdma_nsant_8821c,
	.wl_rf_para_num = ARRAY_SIZE(rf_para_tx_8821c),
	.wl_rf_para_tx = rf_para_tx_8821c,
	.wl_rf_para_rx = rf_para_rx_8821c,
	.bt_afh_span_bw20 = 0x24,
	.bt_afh_span_bw40 = 0x36,
	.afh_5g_num = ARRAY_SIZE(afh_5g_8821c),
	.afh_5g = afh_5g_8821c,

	.coex_info_hw_regs_num = ARRAY_SIZE(coex_info_hw_regs_8821c),
	.coex_info_hw_regs = coex_info_hw_regs_8821c,
पूर्ण;
EXPORT_SYMBOL(rtw8821c_hw_spec);

MODULE_FIRMWARE("rtw88/rtw8821c_fw.bin");

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless 8821c driver");
MODULE_LICENSE("Dual BSD/GPL");

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
#समावेश "rtw8723d.h"
#समावेश "rtw8723d_table.h"
#समावेश "mac.h"
#समावेश "reg.h"
#समावेश "debug.h"

अटल स्थिर काष्ठा rtw_hw_reg rtw8723d_txagc[] = अणु
	[DESC_RATE1M]	= अणु .addr = 0xe08, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATE2M]	= अणु .addr = 0x86c, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATE5_5M]	= अणु .addr = 0x86c, .mask = 0x00ff0000 पूर्ण,
	[DESC_RATE11M]	= अणु .addr = 0x86c, .mask = 0xff000000 पूर्ण,
	[DESC_RATE6M]	= अणु .addr = 0xe00, .mask = 0x000000ff पूर्ण,
	[DESC_RATE9M]	= अणु .addr = 0xe00, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATE12M]	= अणु .addr = 0xe00, .mask = 0x00ff0000 पूर्ण,
	[DESC_RATE18M]	= अणु .addr = 0xe00, .mask = 0xff000000 पूर्ण,
	[DESC_RATE24M]	= अणु .addr = 0xe04, .mask = 0x000000ff पूर्ण,
	[DESC_RATE36M]	= अणु .addr = 0xe04, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATE48M]	= अणु .addr = 0xe04, .mask = 0x00ff0000 पूर्ण,
	[DESC_RATE54M]	= अणु .addr = 0xe04, .mask = 0xff000000 पूर्ण,
	[DESC_RATEMCS0]	= अणु .addr = 0xe10, .mask = 0x000000ff पूर्ण,
	[DESC_RATEMCS1]	= अणु .addr = 0xe10, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATEMCS2]	= अणु .addr = 0xe10, .mask = 0x00ff0000 पूर्ण,
	[DESC_RATEMCS3]	= अणु .addr = 0xe10, .mask = 0xff000000 पूर्ण,
	[DESC_RATEMCS4]	= अणु .addr = 0xe14, .mask = 0x000000ff पूर्ण,
	[DESC_RATEMCS5]	= अणु .addr = 0xe14, .mask = 0x0000ff00 पूर्ण,
	[DESC_RATEMCS6]	= अणु .addr = 0xe14, .mask = 0x00ff0000 पूर्ण,
	[DESC_RATEMCS7]	= अणु .addr = 0xe14, .mask = 0xff000000 पूर्ण,
पूर्ण;

#घोषणा WLAN_TXQ_RPT_EN		0x1F
#घोषणा WLAN_SLOT_TIME		0x09
#घोषणा WLAN_RL_VAL		0x3030
#घोषणा WLAN_BAR_VAL		0x0201ffff
#घोषणा BIT_MASK_TBTT_HOLD	0x00000fff
#घोषणा BIT_SHIFT_TBTT_HOLD	8
#घोषणा BIT_MASK_TBTT_SETUP	0x000000ff
#घोषणा BIT_SHIFT_TBTT_SETUP	0
#घोषणा BIT_MASK_TBTT_MASK	((BIT_MASK_TBTT_HOLD << BIT_SHIFT_TBTT_HOLD) | \
				 (BIT_MASK_TBTT_SETUP << BIT_SHIFT_TBTT_SETUP))
#घोषणा TBTT_TIME(s, h)((((s) & BIT_MASK_TBTT_SETUP) << BIT_SHIFT_TBTT_SETUP) |\
			(((h) & BIT_MASK_TBTT_HOLD) << BIT_SHIFT_TBTT_HOLD))
#घोषणा WLAN_TBTT_TIME_NORMAL	TBTT_TIME(0x04, 0x80)
#घोषणा WLAN_TBTT_TIME_STOP_BCN	TBTT_TIME(0x04, 0x64)
#घोषणा WLAN_PIFS_VAL		0
#घोषणा WLAN_AGG_BRK_TIME	0x16
#घोषणा WLAN_NAV_PROT_LEN	0x0040
#घोषणा WLAN_SPEC_SIFS		0x100a
#घोषणा WLAN_RX_PKT_LIMIT	0x17
#घोषणा WLAN_MAX_AGG_NR		0x0A
#घोषणा WLAN_AMPDU_MAX_TIME	0x1C
#घोषणा WLAN_ANT_SEL		0x82
#घोषणा WLAN_LTR_IDLE_LAT	0x90039003
#घोषणा WLAN_LTR_ACT_LAT	0x883c883c
#घोषणा WLAN_LTR_CTRL1		0xCB004010
#घोषणा WLAN_LTR_CTRL2		0x01233425

अटल व्योम rtw8723d_lck(काष्ठा rtw_dev *rtwdev)
अणु
	u32 lc_cal;
	u8 val_ctx, rf_val;
	पूर्णांक ret;

	val_ctx = rtw_पढ़ो8(rtwdev, REG_CTX);
	अगर ((val_ctx & BIT_MASK_CTX_TYPE) != 0)
		rtw_ग_लिखो8(rtwdev, REG_CTX, val_ctx & ~BIT_MASK_CTX_TYPE);
	अन्यथा
		rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, 0xFF);
	lc_cal = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK, lc_cal | BIT_LCK);

	ret = पढ़ो_poll_समयout(rtw_पढ़ो_rf, rf_val, rf_val != 0x1,
				10000, 1000000, false,
				rtwdev, RF_PATH_A, RF_CFGCH, BIT_LCK);
	अगर (ret)
		rtw_warn(rtwdev, "failed to poll LCK status bit\n");

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK, lc_cal);
	अगर ((val_ctx & BIT_MASK_CTX_TYPE) != 0)
		rtw_ग_लिखो8(rtwdev, REG_CTX, val_ctx);
	अन्यथा
		rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, 0x00);
पूर्ण

अटल स्थिर u32 rtw8723d_ofdm_swing_table[] = अणु
	0x0b40002d, 0x0c000030, 0x0cc00033, 0x0d800036, 0x0e400039, 0x0f00003c,
	0x10000040, 0x11000044, 0x12000048, 0x1300004c, 0x14400051, 0x15800056,
	0x16c0005b, 0x18000060, 0x19800066, 0x1b00006c, 0x1c800072, 0x1e400079,
	0x20000080, 0x22000088, 0x24000090, 0x26000098, 0x288000a2, 0x2ac000ab,
	0x2d4000b5, 0x300000c0, 0x32c000cb, 0x35c000d7, 0x390000e4, 0x3c8000f2,
	0x40000100, 0x43c0010f, 0x47c0011f, 0x4c000130, 0x50800142, 0x55400155,
	0x5a400169, 0x5fc0017f, 0x65400195, 0x6b8001ae, 0x71c001c7, 0x788001e2,
	0x7f8001fe,
पूर्ण;

अटल स्थिर u32 rtw8723d_cck_swing_table[] = अणु
	0x0CD, 0x0D9, 0x0E6, 0x0F3, 0x102, 0x111, 0x121, 0x132, 0x144, 0x158,
	0x16C, 0x182, 0x198, 0x1B1, 0x1CA, 0x1E5, 0x202, 0x221, 0x241, 0x263,
	0x287, 0x2AE, 0x2D6, 0x301, 0x32F, 0x35F, 0x392, 0x3C9, 0x402, 0x43F,
	0x47F, 0x4C3, 0x50C, 0x558, 0x5A9, 0x5FF, 0x65A, 0x6BA, 0x720, 0x78C,
	0x7FF,
पूर्ण;

#घोषणा RTW_OFDM_SWING_TABLE_SIZE	ARRAY_SIZE(rtw8723d_ofdm_swing_table)
#घोषणा RTW_CCK_SWING_TABLE_SIZE	ARRAY_SIZE(rtw8723d_cck_swing_table)

अटल व्योम rtw8723d_pwrtrack_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 path;

	dm_info->शेष_ofdm_index = RTW_DEF_OFDM_SWING_INDEX;

	क्रम (path = RF_PATH_A; path < rtwdev->hal.rf_path_num; path++) अणु
		ewma_thermal_init(&dm_info->avg_thermal[path]);
		dm_info->delta_घातer_index[path] = 0;
	पूर्ण
	dm_info->pwr_trk_triggered = false;
	dm_info->pwr_trk_init_trigger = true;
	dm_info->thermal_meter_k = rtwdev->efuse.thermal_meter_k;
	dm_info->txagc_remnant_cck = 0;
	dm_info->txagc_remnant_ofdm = 0;
पूर्ण

अटल व्योम rtw8723d_phy_set_param(काष्ठा rtw_dev *rtwdev)
अणु
	u8 xtal_cap;
	u32 val32;

	/* घातer on BB/RF करोमुख्य */
	rtw_ग_लिखो16_set(rtwdev, REG_SYS_FUNC_EN,
			BIT_FEN_EN_25_1 | BIT_FEN_BB_GLB_RST | BIT_FEN_BB_RSTB);
	rtw_ग_लिखो8_set(rtwdev, REG_RF_CTRL,
		       BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	rtw_ग_लिखो8(rtwdev, REG_AFE_CTRL1 + 1, 0x80);

	rtw_phy_load_tables(rtwdev);

	/* post init after header files config */
	rtw_ग_लिखो32_clr(rtwdev, REG_RCR, BIT_RCR_ADF);
	rtw_ग_लिखो8_set(rtwdev, REG_HIQ_NO_LMT_EN, BIT_HIQ_NO_LMT_EN_ROOT);
	rtw_ग_लिखो16_set(rtwdev, REG_AFE_CTRL_4, BIT_CK320M_AFE_EN | BIT_EN_SYN);

	xtal_cap = rtwdev->efuse.crystal_cap & 0x3F;
	rtw_ग_लिखो32_mask(rtwdev, REG_AFE_CTRL3, BIT_MASK_XTAL,
			 xtal_cap | (xtal_cap << 6));
	rtw_ग_लिखो32_set(rtwdev, REG_FPGA0_RFMOD, BIT_CCKEN | BIT_OFDMEN);
	अगर ((rtwdev->efuse.afe >> 4) == 14) अणु
		rtw_ग_लिखो32_set(rtwdev, REG_AFE_CTRL3, BIT_XTAL_GMP_BIT4);
		rtw_ग_लिखो32_clr(rtwdev, REG_AFE_CTRL1, BITS_PLL);
		rtw_ग_लिखो32_set(rtwdev, REG_LDO_SWR_CTRL, BIT_XTA1);
		rtw_ग_लिखो32_clr(rtwdev, REG_LDO_SWR_CTRL, BIT_XTA0);
	पूर्ण

	rtw_ग_लिखो8(rtwdev, REG_SLOT, WLAN_SLOT_TIME);
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL + 1, WLAN_TXQ_RPT_EN);
	rtw_ग_लिखो16(rtwdev, REG_RETRY_LIMIT, WLAN_RL_VAL);
	rtw_ग_लिखो32(rtwdev, REG_BAR_MODE_CTRL, WLAN_BAR_VAL);
	rtw_ग_लिखो8(rtwdev, REG_ATIMWND, 0x2);
	rtw_ग_लिखो8(rtwdev, REG_BCN_CTRL,
		   BIT_DIS_TSF_UDT | BIT_EN_BCN_FUNCTION | BIT_EN_TXBCN_RPT);
	val32 = rtw_पढ़ो32(rtwdev, REG_TBTT_PROHIBIT);
	val32 &= ~BIT_MASK_TBTT_MASK;
	val32 |= WLAN_TBTT_TIME_STOP_BCN;
	rtw_ग_लिखो8(rtwdev, REG_TBTT_PROHIBIT, val32);
	rtw_ग_लिखो8(rtwdev, REG_PIFS, WLAN_PIFS_VAL);
	rtw_ग_लिखो8(rtwdev, REG_AGGR_BREAK_TIME, WLAN_AGG_BRK_TIME);
	rtw_ग_लिखो16(rtwdev, REG_NAV_PROT_LEN, WLAN_NAV_PROT_LEN);
	rtw_ग_लिखो16(rtwdev, REG_MAC_SPEC_SIFS, WLAN_SPEC_SIFS);
	rtw_ग_लिखो16(rtwdev, REG_SIFS, WLAN_SPEC_SIFS);
	rtw_ग_लिखो16(rtwdev, REG_SIFS + 2, WLAN_SPEC_SIFS);
	rtw_ग_लिखो8(rtwdev, REG_SINGLE_AMPDU_CTRL, BIT_EN_SINGLE_APMDU);
	rtw_ग_लिखो8(rtwdev, REG_RX_PKT_LIMIT, WLAN_RX_PKT_LIMIT);
	rtw_ग_लिखो8(rtwdev, REG_MAX_AGGR_NUM, WLAN_MAX_AGG_NR);
	rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME, WLAN_AMPDU_MAX_TIME);
	rtw_ग_लिखो8(rtwdev, REG_LEDCFG2, WLAN_ANT_SEL);

	rtw_ग_लिखो32(rtwdev, REG_LTR_IDLE_LATENCY, WLAN_LTR_IDLE_LAT);
	rtw_ग_लिखो32(rtwdev, REG_LTR_ACTIVE_LATENCY, WLAN_LTR_ACT_LAT);
	rtw_ग_लिखो32(rtwdev, REG_LTR_CTRL_BASIC, WLAN_LTR_CTRL1);
	rtw_ग_लिखो32(rtwdev, REG_LTR_CTRL_BASIC + 4, WLAN_LTR_CTRL2);

	rtw_phy_init(rtwdev);
	rtwdev->dm_info.cck_pd_शेष = rtw_पढ़ो8(rtwdev, REG_CSRATIO) & 0x1f;

	rtw_ग_लिखो16_set(rtwdev, REG_TXDMA_OFFSET_CHK, BIT_DROP_DATA_EN);

	rtw8723d_lck(rtwdev);

	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XAAGC1, MASKBYTE0, 0x50);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XAAGC1, MASKBYTE0, 0x20);

	rtw8723d_pwrtrack_init(rtwdev);
पूर्ण

अटल व्योम rtw8723de_efuse_parsing(काष्ठा rtw_efuse *efuse,
				    काष्ठा rtw8723d_efuse *map)
अणु
	ether_addr_copy(efuse->addr, map->e.mac_addr);
पूर्ण

अटल पूर्णांक rtw8723d_पढ़ो_efuse(काष्ठा rtw_dev *rtwdev, u8 *log_map)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw8723d_efuse *map;
	पूर्णांक i;

	map = (काष्ठा rtw8723d_efuse *)log_map;

	efuse->rfe_option = 0;
	efuse->rf_board_option = map->rf_board_option;
	efuse->crystal_cap = map->xtal_k;
	efuse->pa_type_2g = map->pa_type;
	efuse->lna_type_2g = map->lna_type_2g[0];
	efuse->channel_plan = map->channel_plan;
	efuse->country_code[0] = map->country_code[0];
	efuse->country_code[1] = map->country_code[1];
	efuse->bt_setting = map->rf_bt_setting;
	efuse->regd = map->rf_board_option & 0x7;
	efuse->thermal_meter[0] = map->thermal_meter;
	efuse->thermal_meter_k = map->thermal_meter;
	efuse->afe = map->afe;

	क्रम (i = 0; i < 4; i++)
		efuse->txpwr_idx_table[i] = map->txpwr_idx_table[i];

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtw8723de_efuse_parsing(efuse, map);
		अवरोध;
	शेष:
		/* unsupported now */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम query_phy_status_page0(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 min_rx_घातer = -120;
	u8 pwdb = GET_PHY_STAT_P0_PWDB(phy_status);

	pkt_stat->rx_घातer[RF_PATH_A] = pwdb - 97;
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

	अगर (pkt_stat->rate > DESC_RATE11M && pkt_stat->rate < DESC_RATEMCS0)
		rxsc = GET_PHY_STAT_P1_L_RXSC(phy_status);
	अन्यथा
		rxsc = GET_PHY_STAT_P1_HT_RXSC(phy_status);

	अगर (GET_PHY_STAT_P1_RF_MODE(phy_status) == 0)
		bw = RTW_CHANNEL_WIDTH_20;
	अन्यथा अगर ((rxsc == 1) || (rxsc == 2))
		bw = RTW_CHANNEL_WIDTH_20;
	अन्यथा
		bw = RTW_CHANNEL_WIDTH_40;

	pkt_stat->rx_घातer[RF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 1);
	pkt_stat->bw = bw;
	pkt_stat->संकेत_घातer = max(pkt_stat->rx_घातer[RF_PATH_A],
				     min_rx_घातer);
	pkt_stat->rx_evm[RF_PATH_A] = GET_PHY_STAT_P1_RXEVM_A(phy_status);
	pkt_stat->rx_snr[RF_PATH_A] = GET_PHY_STAT_P1_RXSNR_A(phy_status);
	pkt_stat->cfo_tail[RF_PATH_A] = GET_PHY_STAT_P1_CFO_TAIL_A(phy_status);

	dm_info->curr_rx_rate = pkt_stat->rate;
	dm_info->rssi[RF_PATH_A] = pkt_stat->rssi;
	dm_info->rx_snr[RF_PATH_A] = pkt_stat->rx_snr[RF_PATH_A] >> 1;
	dm_info->cfo_tail[RF_PATH_A] = (pkt_stat->cfo_tail[RF_PATH_A] * 5) >> 1;

	rx_evm = clamp_t(s8, -pkt_stat->rx_evm[RF_PATH_A] >> 1, 0, 64);
	rx_evm &= 0x3F;	/* 64->0: second path of 1SS rate is 64 */
	dm_info->rx_evm_dbm[RF_PATH_A] = rx_evm;
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

अटल व्योम rtw8723d_query_rx_desc(काष्ठा rtw_dev *rtwdev, u8 *rx_desc,
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
	pkt_stat->ppdu_cnt = 0;
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

अटल bool rtw8723d_check_spur_ov_thres(काष्ठा rtw_dev *rtwdev,
					 u8 channel, u32 thres)
अणु
	u32 freq;
	bool ret = false;

	अगर (channel == 13)
		freq = FREQ_CH13;
	अन्यथा अगर (channel == 14)
		freq = FREQ_CH14;
	अन्यथा
		वापस false;

	rtw_ग_लिखो32(rtwdev, REG_ANALOG_P4, DIS_3WIRE);
	rtw_ग_लिखो32(rtwdev, REG_PSDFN, freq);
	rtw_ग_लिखो32(rtwdev, REG_PSDFN, START_PSD | freq);

	msleep(30);
	अगर (rtw_पढ़ो32(rtwdev, REG_PSDRPT) >= thres)
		ret = true;

	rtw_ग_लिखो32(rtwdev, REG_PSDFN, freq);
	rtw_ग_लिखो32(rtwdev, REG_ANALOG_P4, EN_3WIRE);

	वापस ret;
पूर्ण

अटल व्योम rtw8723d_cfg_notch(काष्ठा rtw_dev *rtwdev, u8 channel, bool notch)
अणु
	अगर (!notch) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_MASK_RXDSP, 0x1f);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_EN_RXDSP, 0x0);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI1, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI2, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI3, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI4, 0x00000000);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM1_CFOTRK, BIT_EN_CFOTRK, 0x0);
		वापस;
	पूर्ण

	चयन (channel) अणु
	हाल 13:
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_MASK_RXDSP, 0xb);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_EN_RXDSP, 0x1);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI1, 0x04000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI2, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI3, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI4, 0x00000000);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM1_CFOTRK, BIT_EN_CFOTRK, 0x1);
		अवरोध;
	हाल 14:
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_MASK_RXDSP, 0x5);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_EN_RXDSP, 0x1);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI1, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI2, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI3, 0x00000000);
		rtw_ग_लिखो32(rtwdev, REG_OFDM1_CSI4, 0x00080000);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM1_CFOTRK, BIT_EN_CFOTRK, 0x1);
		अवरोध;
	शेष:
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_RXDSP, BIT_EN_RXDSP, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_OFDM1_CFOTRK, BIT_EN_CFOTRK, 0x0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_spur_cal(काष्ठा rtw_dev *rtwdev, u8 channel)
अणु
	bool notch;

	अगर (channel < 13) अणु
		rtw8723d_cfg_notch(rtwdev, channel, false);
		वापस;
	पूर्ण

	notch = rtw8723d_check_spur_ov_thres(rtwdev, channel, SPUR_THRES);
	rtw8723d_cfg_notch(rtwdev, channel, notch);
पूर्ण

अटल व्योम rtw8723d_set_channel_rf(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw)
अणु
	u32 rf_cfgch_a, rf_cfgch_b;

	rf_cfgch_a = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK);
	rf_cfgch_b = rtw_पढ़ो_rf(rtwdev, RF_PATH_B, RF_CFGCH, RFREG_MASK);

	rf_cfgch_a &= ~RFCFGCH_CHANNEL_MASK;
	rf_cfgch_b &= ~RFCFGCH_CHANNEL_MASK;
	rf_cfgch_a |= (channel & RFCFGCH_CHANNEL_MASK);
	rf_cfgch_b |= (channel & RFCFGCH_CHANNEL_MASK);

	rf_cfgch_a &= ~RFCFGCH_BW_MASK;
	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_20:
		rf_cfgch_a |= RFCFGCH_BW_20M;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		rf_cfgch_a |= RFCFGCH_BW_40M;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK, rf_cfgch_a);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_CFGCH, RFREG_MASK, rf_cfgch_b);

	rtw8723d_spur_cal(rtwdev, channel);
पूर्ण

अटल स्थिर काष्ठा rtw_backup_info cck_dfir_cfg[][CCK_DFIR_NR] = अणु
	[0] = अणु
		अणु .len = 4, .reg = 0xA24, .val = 0x64B80C1C पूर्ण,
		अणु .len = 4, .reg = 0xA28, .val = 0x00008810 पूर्ण,
		अणु .len = 4, .reg = 0xAAC, .val = 0x01235667 पूर्ण,
	पूर्ण,
	[1] = अणु
		अणु .len = 4, .reg = 0xA24, .val = 0x0000B81C पूर्ण,
		अणु .len = 4, .reg = 0xA28, .val = 0x00000000 पूर्ण,
		अणु .len = 4, .reg = 0xAAC, .val = 0x00003667 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम rtw8723d_set_channel_bb(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				    u8 primary_ch_idx)
अणु
	स्थिर काष्ठा rtw_backup_info *cck_dfir;
	पूर्णांक i;

	cck_dfir = channel <= 13 ? cck_dfir_cfg[0] : cck_dfir_cfg[1];

	क्रम (i = 0; i < CCK_DFIR_NR; i++, cck_dfir++)
		rtw_ग_लिखो32(rtwdev, cck_dfir->reg, cck_dfir->val);

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_20:
		rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_RFMOD, BIT_MASK_RFMOD, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_FPGA1_RFMOD, BIT_MASK_RFMOD, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_BBRX_DFIR, BIT_RXBB_DFIR_EN, 1);
		rtw_ग_लिखो32_mask(rtwdev, REG_BBRX_DFIR, BIT_MASK_RXBB_DFIR, 0xa);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_RFMOD, BIT_MASK_RFMOD, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_FPGA1_RFMOD, BIT_MASK_RFMOD, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_BBRX_DFIR, BIT_RXBB_DFIR_EN, 0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK0_SYS, BIT_CCK_SIDE_BAND,
				 (primary_ch_idx == RTW_SC_20_UPPER ? 1 : 0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_set_channel(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				 u8 primary_chan_idx)
अणु
	rtw8723d_set_channel_rf(rtwdev, channel, bw);
	rtw_set_channel_mac(rtwdev, channel, bw, primary_chan_idx);
	rtw8723d_set_channel_bb(rtwdev, channel, bw, primary_chan_idx);
पूर्ण

#घोषणा BIT_CFENDFORM		BIT(9)
#घोषणा BIT_WMAC_TCR_ERR0	BIT(12)
#घोषणा BIT_WMAC_TCR_ERR1	BIT(13)
#घोषणा BIT_TCR_CFG		(BIT_CFENDFORM | BIT_WMAC_TCR_ERR0 |	       \
				 BIT_WMAC_TCR_ERR1)
#घोषणा WLAN_RX_FILTER0		0xFFFF
#घोषणा WLAN_RX_FILTER1		0x400
#घोषणा WLAN_RX_FILTER2		0xFFFF
#घोषणा WLAN_RCR_CFG		0x700060CE

अटल पूर्णांक rtw8723d_mac_init(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL + 1, WLAN_TXQ_RPT_EN);
	rtw_ग_लिखो32(rtwdev, REG_TCR, BIT_TCR_CFG);

	rtw_ग_लिखो16(rtwdev, REG_RXFLTMAP0, WLAN_RX_FILTER0);
	rtw_ग_लिखो16(rtwdev, REG_RXFLTMAP1, WLAN_RX_FILTER1);
	rtw_ग_लिखो16(rtwdev, REG_RXFLTMAP2, WLAN_RX_FILTER2);
	rtw_ग_लिखो32(rtwdev, REG_RCR, WLAN_RCR_CFG);

	rtw_ग_लिखो32(rtwdev, REG_INT_MIG, 0);
	rtw_ग_लिखो32(rtwdev, REG_MCUTST_1, 0x0);

	rtw_ग_लिखो8(rtwdev, REG_MISC_CTRL, BIT_DIS_SECOND_CCA);
	rtw_ग_लिखो8(rtwdev, REG_2ND_CCA_CTRL, 0);

	वापस 0;
पूर्ण

अटल व्योम rtw8723d_shutकरोwn(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो16_set(rtwdev, REG_HCI_OPT_CTRL, BIT_USB_SUS_DIS);
पूर्ण

अटल व्योम rtw8723d_cfg_lकरो25(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 lकरो_pwr;

	lकरो_pwr = rtw_पढ़ो8(rtwdev, REG_LDO_EFUSE_CTRL + 3);
	अगर (enable) अणु
		lकरो_pwr &= ~BIT_MASK_LDO25_VOLTAGE;
		lकरो_pwr |= (BIT_LDO25_VOLTAGE_V25 << 4) | BIT_LDO25_EN;
	पूर्ण अन्यथा अणु
		lकरो_pwr &= ~BIT_LDO25_EN;
	पूर्ण
	rtw_ग_लिखो8(rtwdev, REG_LDO_EFUSE_CTRL + 3, lकरो_pwr);
पूर्ण

अटल व्योम
rtw8723d_set_tx_घातer_index_by_rate(काष्ठा rtw_dev *rtwdev, u8 path, u8 rs)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	स्थिर काष्ठा rtw_hw_reg *txagc;
	u8 rate, pwr_index;
	पूर्णांक j;

	क्रम (j = 0; j < rtw_rate_size[rs]; j++) अणु
		rate = rtw_rate_section[rs][j];
		pwr_index = hal->tx_pwr_tbl[path][rate];

		अगर (rate >= ARRAY_SIZE(rtw8723d_txagc)) अणु
			rtw_warn(rtwdev, "rate 0x%x isn't supported\n", rate);
			जारी;
		पूर्ण
		txagc = &rtw8723d_txagc[rate];
		अगर (!txagc->addr) अणु
			rtw_warn(rtwdev, "rate 0x%x isn't defined\n", rate);
			जारी;
		पूर्ण

		rtw_ग_लिखो32_mask(rtwdev, txagc->addr, txagc->mask, pwr_index);
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_set_tx_घातer_index(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	पूर्णांक rs, path;

	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		क्रम (rs = 0; rs <= RTW_RATE_SECTION_HT_1S; rs++)
			rtw8723d_set_tx_घातer_index_by_rate(rtwdev, path, rs);
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_efuse_grant(काष्ठा rtw_dev *rtwdev, bool on)
अणु
	अगर (on) अणु
		rtw_ग_लिखो8(rtwdev, REG_EFUSE_ACCESS, EFUSE_ACCESS_ON);

		rtw_ग_लिखो16_set(rtwdev, REG_SYS_FUNC_EN, BIT_FEN_ELDR);
		rtw_ग_लिखो16_set(rtwdev, REG_SYS_CLKR, BIT_LOADER_CLK_EN | BIT_ANA8M);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8(rtwdev, REG_EFUSE_ACCESS, EFUSE_ACCESS_OFF);
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_false_alarm_statistics(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 crc32_cnt;
	u32 val32;

	/* hold counter */
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_HOLDC_11N, BIT_MASK_OFDM_FA_KEEP, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTD_11N, BIT_MASK_OFDM_FA_KEEP1, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_CNT_KEEP, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_FA_KEEP, 1);

	cck_fa_cnt = rtw_पढ़ो32_mask(rtwdev, REG_CCK_FA_LSB_11N, MASKBYTE0);
	cck_fa_cnt += rtw_पढ़ो32_mask(rtwdev, REG_CCK_FA_MSB_11N, MASKBYTE3) << 8;

	val32 = rtw_पढ़ो32(rtwdev, REG_OFDM_FA_TYPE1_11N);
	ofdm_fa_cnt = u32_get_bits(val32, BIT_MASK_OFDM_FF_CNT);
	ofdm_fa_cnt += u32_get_bits(val32, BIT_MASK_OFDM_SF_CNT);
	val32 = rtw_पढ़ो32(rtwdev, REG_OFDM_FA_TYPE2_11N);
	dm_info->ofdm_cca_cnt = u32_get_bits(val32, BIT_MASK_OFDM_CCA_CNT);
	ofdm_fa_cnt += u32_get_bits(val32, BIT_MASK_OFDM_PF_CNT);
	val32 = rtw_पढ़ो32(rtwdev, REG_OFDM_FA_TYPE3_11N);
	ofdm_fa_cnt += u32_get_bits(val32, BIT_MASK_OFDM_RI_CNT);
	ofdm_fa_cnt += u32_get_bits(val32, BIT_MASK_OFDM_CRC_CNT);
	val32 = rtw_पढ़ो32(rtwdev, REG_OFDM_FA_TYPE4_11N);
	ofdm_fa_cnt += u32_get_bits(val32, BIT_MASK_OFDM_MNS_CNT);

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt = cck_fa_cnt + ofdm_fa_cnt;

	dm_info->cck_err_cnt = rtw_पढ़ो32(rtwdev, REG_IGI_C_11N);
	dm_info->cck_ok_cnt = rtw_पढ़ो32(rtwdev, REG_IGI_D_11N);
	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_OFDM_CRC32_CNT_11N);
	dm_info->ofdm_err_cnt = u32_get_bits(crc32_cnt, BIT_MASK_OFDM_LCRC_ERR);
	dm_info->ofdm_ok_cnt = u32_get_bits(crc32_cnt, BIT_MASK_OFDM_LCRC_OK);
	crc32_cnt = rtw_पढ़ो32(rtwdev, REG_HT_CRC32_CNT_11N);
	dm_info->ht_err_cnt = u32_get_bits(crc32_cnt, BIT_MASK_HT_CRC_ERR);
	dm_info->ht_ok_cnt = u32_get_bits(crc32_cnt, BIT_MASK_HT_CRC_OK);
	dm_info->vht_err_cnt = 0;
	dm_info->vht_ok_cnt = 0;

	val32 = rtw_पढ़ो32(rtwdev, REG_CCK_CCA_CNT_11N);
	dm_info->cck_cca_cnt = (u32_get_bits(val32, BIT_MASK_CCK_FA_MSB) << 8) |
			       u32_get_bits(val32, BIT_MASK_CCK_FA_LSB);
	dm_info->total_cca_cnt = dm_info->cck_cca_cnt + dm_info->ofdm_cca_cnt;

	/* reset counter */
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTC_11N, BIT_MASK_OFDM_FA_RST, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTC_11N, BIT_MASK_OFDM_FA_RST, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTD_11N, BIT_MASK_OFDM_FA_RST1, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTD_11N, BIT_MASK_OFDM_FA_RST1, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_HOLDC_11N, BIT_MASK_OFDM_FA_KEEP, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_FA_RSTD_11N, BIT_MASK_OFDM_FA_KEEP1, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_CNT_KPEN, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_CNT_KPEN, 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_FA_KPEN, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_FA_RST_11N, BIT_MASK_CCK_FA_KPEN, 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_PAGE_F_RST_11N, BIT_MASK_F_RST_ALL, 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_PAGE_F_RST_11N, BIT_MASK_F_RST_ALL, 0);
पूर्ण

अटल स्थिर u32 iqk_adda_regs[] = अणु
	0x85c, 0xe6c, 0xe70, 0xe74, 0xe78, 0xe7c, 0xe80, 0xe84, 0xe88, 0xe8c,
	0xed0, 0xed4, 0xed8, 0xedc, 0xee0, 0xeec
पूर्ण;

अटल स्थिर u32 iqk_mac8_regs[] = अणु0x522, 0x550, 0x551पूर्ण;
अटल स्थिर u32 iqk_mac32_regs[] = अणु0x40पूर्ण;

अटल स्थिर u32 iqk_bb_regs[] = अणु
	0xc04, 0xc08, 0x874, 0xb68, 0xb6c, 0x870, 0x860, 0x864, 0xa04
पूर्ण;

#घोषणा IQK_ADDA_REG_NUM	ARRAY_SIZE(iqk_adda_regs)
#घोषणा IQK_MAC8_REG_NUM	ARRAY_SIZE(iqk_mac8_regs)
#घोषणा IQK_MAC32_REG_NUM	ARRAY_SIZE(iqk_mac32_regs)
#घोषणा IQK_BB_REG_NUM		ARRAY_SIZE(iqk_bb_regs)

काष्ठा iqk_backup_regs अणु
	u32 adda[IQK_ADDA_REG_NUM];
	u8 mac8[IQK_MAC8_REG_NUM];
	u32 mac32[IQK_MAC32_REG_NUM];
	u32 bb[IQK_BB_REG_NUM];

	u32 lte_path;
	u32 lte_gnt;

	u32 bb_sel_btg;
	u8 btg_sel;

	u8 igia;
	u8 igib;
पूर्ण;

अटल व्योम rtw8723d_iqk_backup_regs(काष्ठा rtw_dev *rtwdev,
				     काष्ठा iqk_backup_regs *backup)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IQK_ADDA_REG_NUM; i++)
		backup->adda[i] = rtw_पढ़ो32(rtwdev, iqk_adda_regs[i]);

	क्रम (i = 0; i < IQK_MAC8_REG_NUM; i++)
		backup->mac8[i] = rtw_पढ़ो8(rtwdev, iqk_mac8_regs[i]);
	क्रम (i = 0; i < IQK_MAC32_REG_NUM; i++)
		backup->mac32[i] = rtw_पढ़ो32(rtwdev, iqk_mac32_regs[i]);

	क्रम (i = 0; i < IQK_BB_REG_NUM; i++)
		backup->bb[i] = rtw_पढ़ो32(rtwdev, iqk_bb_regs[i]);

	backup->igia = rtw_पढ़ो32_mask(rtwdev, REG_OFDM0_XAAGC1, MASKBYTE0);
	backup->igib = rtw_पढ़ो32_mask(rtwdev, REG_OFDM0_XBAGC1, MASKBYTE0);

	backup->bb_sel_btg = rtw_पढ़ो32(rtwdev, REG_BB_SEL_BTG);
पूर्ण

अटल व्योम rtw8723d_iqk_restore_regs(काष्ठा rtw_dev *rtwdev,
				      स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtw_ग_लिखो32(rtwdev, iqk_adda_regs[i], backup->adda[i]);

	क्रम (i = 0; i < IQK_MAC8_REG_NUM; i++)
		rtw_ग_लिखो8(rtwdev, iqk_mac8_regs[i], backup->mac8[i]);
	क्रम (i = 0; i < IQK_MAC32_REG_NUM; i++)
		rtw_ग_लिखो32(rtwdev, iqk_mac32_regs[i], backup->mac32[i]);

	क्रम (i = 0; i < IQK_BB_REG_NUM; i++)
		rtw_ग_लिखो32(rtwdev, iqk_bb_regs[i], backup->bb[i]);

	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XAAGC1, MASKBYTE0, 0x50);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XAAGC1, MASKBYTE0, backup->igia);

	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XBAGC1, MASKBYTE0, 0x50);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM0_XBAGC1, MASKBYTE0, backup->igib);

	rtw_ग_लिखो32(rtwdev, REG_TXIQK_TONE_A_11N, 0x01008c00);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_TONE_A_11N, 0x01008c00);
पूर्ण

अटल व्योम rtw8723d_iqk_backup_path_ctrl(काष्ठा rtw_dev *rtwdev,
					  काष्ठा iqk_backup_regs *backup)
अणु
	backup->btg_sel = rtw_पढ़ो8(rtwdev, REG_BTG_SEL);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] original 0x67 = 0x%x\n",
		backup->btg_sel);
पूर्ण

अटल व्योम rtw8723d_iqk_config_path_ctrl(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32_mask(rtwdev, REG_PAD_CTRL1, BIT_BT_BTG_SEL, 0x1);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] set 0x67 = 0x%x\n",
		rtw_पढ़ो32_mask(rtwdev, REG_PAD_CTRL1, MASKBYTE3));
पूर्ण

अटल व्योम rtw8723d_iqk_restore_path_ctrl(काष्ठा rtw_dev *rtwdev,
					   स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	rtw_ग_लिखो8(rtwdev, REG_BTG_SEL, backup->btg_sel);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] restore 0x67 = 0x%x\n",
		rtw_पढ़ो32_mask(rtwdev, REG_PAD_CTRL1, MASKBYTE3));
पूर्ण

अटल व्योम rtw8723d_iqk_backup_lte_path_gnt(काष्ठा rtw_dev *rtwdev,
					     काष्ठा iqk_backup_regs *backup)
अणु
	backup->lte_path = rtw_पढ़ो32(rtwdev, REG_LTECOEX_PATH_CONTROL);
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_CTRL, 0x800f0038);
	mdelay(1);
	backup->lte_gnt = rtw_पढ़ो32(rtwdev, REG_LTECOEX_READ_DATA);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] OriginalGNT = 0x%x\n",
		backup->lte_gnt);
पूर्ण

अटल व्योम rtw8723d_iqk_config_lte_path_gnt(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_WRITE_DATA, 0x0000ff00);
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_CTRL, 0xc0020038);
	rtw_ग_लिखो32_mask(rtwdev, REG_LTECOEX_PATH_CONTROL, BIT_LTE_MUX_CTRL_PATH, 0x1);
पूर्ण

अटल व्योम rtw8723d_iqk_restore_lte_path_gnt(काष्ठा rtw_dev *rtwdev,
					      स्थिर काष्ठा iqk_backup_regs *bak)
अणु
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_WRITE_DATA, bak->lte_gnt);
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_CTRL, 0xc00f0038);
	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_PATH_CONTROL, bak->lte_path);
पूर्ण

काष्ठा rtw_8723d_iqk_cfg अणु
	स्थिर अक्षर *name;
	u32 val_bb_sel_btg;
	u32 reg_lutwe;
	u32 val_txiqk_pi;
	u32 reg_padlut;
	u32 reg_gaपूर्णांकx;
	u32 reg_bspad;
	u32 val_wlपूर्णांक;
	u32 val_wlsel;
	u32 val_iqkpts;
पूर्ण;

अटल स्थिर काष्ठा rtw_8723d_iqk_cfg iqk_tx_cfg[PATH_NR] = अणु
	[PATH_S1] = अणु
		.name = "S1",
		.val_bb_sel_btg = 0x99000000,
		.reg_lutwe = RF_LUTWE,
		.val_txiqk_pi = 0x8214019f,
		.reg_padlut = RF_LUTDBG,
		.reg_gaपूर्णांकx = RF_GAINTX,
		.reg_bspad = RF_BSPAD,
		.val_wlपूर्णांक = 0xe0d,
		.val_wlsel = 0x60d,
		.val_iqkpts = 0xfa000000,
	पूर्ण,
	[PATH_S0] = अणु
		.name = "S0",
		.val_bb_sel_btg = 0x99000280,
		.reg_lutwe = RF_LUTWE2,
		.val_txiqk_pi = 0x8214018a,
		.reg_padlut = RF_TXADBG,
		.reg_gaपूर्णांकx = RF_TRXIQ,
		.reg_bspad = RF_TXATANK,
		.val_wlपूर्णांक = 0xe6d,
		.val_wlsel = 0x66d,
		.val_iqkpts = 0xf9000000,
	पूर्ण,
पूर्ण;

अटल u8 rtw8723d_iqk_check_tx_failed(काष्ठा rtw_dev *rtwdev,
				       स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg)
अणु
	s32 tx_x, tx_y;
	u32 tx_fail;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0xeac = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_IQK_RES_RY));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0xe94 = 0x%x, 0xe9c = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_IQK_RES_TX),
		rtw_पढ़ो32(rtwdev, REG_IQK_RES_TY));
	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] 0xe90(before IQK)= 0x%x, 0xe98(afer IQK) = 0x%x\n",
		rtw_पढ़ो32(rtwdev, 0xe90),
		rtw_पढ़ो32(rtwdev, 0xe98));

	tx_fail = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RY, BIT_IQK_TX_FAIL);
	tx_x = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TX, BIT_MASK_RES_TX);
	tx_y = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TY, BIT_MASK_RES_TY);

	अगर (!tx_fail && tx_x != IQK_TX_X_ERR && tx_y != IQK_TX_Y_ERR)
		वापस IQK_TX_OK;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] %s TXIQK is failed\n",
		iqk_cfg->name);

	वापस 0;
पूर्ण

अटल u8 rtw8723d_iqk_check_rx_failed(काष्ठा rtw_dev *rtwdev,
				       स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg)
अणु
	s32 rx_x, rx_y;
	u32 rx_fail;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0xea4 = 0x%x, 0xeac = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_IQK_RES_RX),
		rtw_पढ़ो32(rtwdev, REG_IQK_RES_RY));

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] 0xea0(before IQK)= 0x%x, 0xea8(afer IQK) = 0x%x\n",
		rtw_पढ़ो32(rtwdev, 0xea0),
		rtw_पढ़ो32(rtwdev, 0xea8));

	rx_fail = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RY, BIT_IQK_RX_FAIL);
	rx_x = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RX, BIT_MASK_RES_RX);
	rx_y = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RY, BIT_MASK_RES_RY);
	rx_y = असल(iqkxy_to_s32(rx_y));

	अगर (!rx_fail && rx_x < IQK_RX_X_UPPER && rx_x > IQK_RX_X_LOWER &&
	    rx_y < IQK_RX_Y_LMT)
		वापस IQK_RX_OK;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] %s RXIQK STEP2 is failed\n",
		iqk_cfg->name);

	वापस 0;
पूर्ण

अटल व्योम rtw8723d_iqk_one_shot(काष्ठा rtw_dev *rtwdev, bool tx,
				  स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg)
अणु
	u32 pts = (tx ? iqk_cfg->val_iqkpts : 0xf9000000);

	/* enter IQK mode */
	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
	rtw8723d_iqk_config_lte_path_gnt(rtwdev);

	rtw_ग_लिखो32(rtwdev, REG_LTECOEX_CTRL, 0x800f0054);
	mdelay(1);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] GNT_BT @%s %sIQK1 = 0x%x\n",
		iqk_cfg->name, tx ? "TX" : "RX",
		rtw_पढ़ो32(rtwdev, REG_LTECOEX_READ_DATA));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0x948 @%s %sIQK1 = 0x%x\n",
		iqk_cfg->name, tx ? "TX" : "RX",
		rtw_पढ़ो32(rtwdev, REG_BB_SEL_BTG));

	/* One shot, LOK & IQK */
	rtw_ग_लिखो32(rtwdev, REG_IQK_AGC_PTS_11N, pts);
	rtw_ग_लिखो32(rtwdev, REG_IQK_AGC_PTS_11N, 0xf8000000);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_IQK_RES_RY, BIT_IQK_DONE, 1))
		rtw_warn(rtwdev, "%s %s IQK isn't done\n", iqk_cfg->name,
			 tx ? "TX" : "RX");
पूर्ण

अटल व्योम rtw8723d_iqk_txrx_path_post(काष्ठा rtw_dev *rtwdev,
					स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg,
					स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	rtw8723d_iqk_restore_lte_path_gnt(rtwdev, backup);
	rtw_ग_लिखो32(rtwdev, REG_BB_SEL_BTG, backup->bb_sel_btg);

	/* leave IQK mode */
	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);
	mdelay(1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_padlut, 0x800, 0x0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLINT, BIT(0), 0x0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLSEL, BIT(0), 0x0);
पूर्ण

अटल u8 rtw8723d_iqk_tx_path(काष्ठा rtw_dev *rtwdev,
			       स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg,
			       स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	u8 status;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path %s TXIQK!!\n", iqk_cfg->name);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0x67 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो32_mask(rtwdev, REG_PAD_CTRL1, MASKBYTE3));

	rtw_ग_लिखो32(rtwdev, REG_BB_SEL_BTG, iqk_cfg->val_bb_sel_btg);
	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);
	mdelay(1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, RFREG_MASK, 0x80000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, RFREG_MASK, 0x00004);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD1, RFREG_MASK, 0x0005d);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD0, RFREG_MASK, 0xBFFE0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, RFREG_MASK, 0x00000);

	/* IQK setting */
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_TONE_A_11N, 0x08008c0c);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_TONE_A_11N, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_PI_A_11N, iqk_cfg->val_txiqk_pi);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_PI_A_11N, 0x28160200);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_11N, 0x01007c00);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_11N, 0x01004800);

	/* LOK setting */
	rtw_ग_लिखो32(rtwdev, REG_IQK_AGC_RSP_11N, 0x00462911);

	/* PA, PAD setting */
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_padlut, 0x800, 0x1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_gaपूर्णांकx, 0x600, 0x0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_gaपूर्णांकx, 0x1E0, 0x3);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RXIQGEN, 0x1F, 0xf);

	/* LOK setting क्रम 8723D */
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, 0x10, 0x1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_bspad, 0x1, 0x1);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLINT, RFREG_MASK, iqk_cfg->val_wlपूर्णांक);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLSEL, RFREG_MASK, iqk_cfg->val_wlsel);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x1 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLINT, RFREG_MASK));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x2 @%s TXIQK = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLSEL, RFREG_MASK));

	rtw8723d_iqk_one_shot(rtwdev, true, iqk_cfg);
	status = rtw8723d_iqk_check_tx_failed(rtwdev, iqk_cfg);

	rtw8723d_iqk_txrx_path_post(rtwdev, iqk_cfg, backup);

	वापस status;
पूर्ण

अटल u8 rtw8723d_iqk_rx_path(काष्ठा rtw_dev *rtwdev,
			       स्थिर काष्ठा rtw_8723d_iqk_cfg *iqk_cfg,
			       स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	u32 tx_x, tx_y;
	u8 status;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path %s RXIQK Step1!!\n",
		iqk_cfg->name);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0x67 @%s RXIQK1 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो32_mask(rtwdev, REG_PAD_CTRL1, MASKBYTE3));
	rtw_ग_लिखो32(rtwdev, REG_BB_SEL_BTG, iqk_cfg->val_bb_sel_btg);

	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);

	/* IQK setting */
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_11N, 0x01007c00);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_11N, 0x01004800);

	/* path IQK setting */
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_TONE_A_11N, 0x18008c1c);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_TONE_A_11N, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_RX_IQK_TONE_B, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_PI_A_11N, 0x82160000);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_PI_A_11N, 0x28160000);

	/* LOK setting */
	rtw_ग_लिखो32(rtwdev, REG_IQK_AGC_RSP_11N, 0x0046a911);

	/* RXIQK mode */
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, RFREG_MASK, 0x80000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, RFREG_MASK, 0x00006);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD1, RFREG_MASK, 0x0005f);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD0, RFREG_MASK, 0xa7ffb);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, RFREG_MASK, 0x00000);

	/* PA/PAD=0 */
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_padlut, 0x800, 0x1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_gaपूर्णांकx, 0x600, 0x0);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLINT, RFREG_MASK, iqk_cfg->val_wlपूर्णांक);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_WLSEL, RFREG_MASK, iqk_cfg->val_wlsel);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x1@ path %s RXIQK1 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLINT, RFREG_MASK));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x2@ path %s RXIQK1 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLSEL, RFREG_MASK));

	rtw8723d_iqk_one_shot(rtwdev, false, iqk_cfg);
	status = rtw8723d_iqk_check_tx_failed(rtwdev, iqk_cfg);

	अगर (!status)
		जाओ restore;

	/* second round */
	tx_x = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TX, BIT_MASK_RES_TX);
	tx_y = rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TY, BIT_MASK_RES_TY);

	rtw_ग_लिखो32(rtwdev, REG_TXIQK_11N, BIT_SET_TXIQK_11N(tx_x, tx_y));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0xe40 = 0x%x u4tmp = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_TXIQK_11N),
		BIT_SET_TXIQK_11N(tx_x, tx_y));

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path %s RXIQK STEP2!!\n",
		iqk_cfg->name);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] 0x67 @%s RXIQK2 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो32_mask(rtwdev, REG_PAD_CTRL1, MASKBYTE3));

	rtw_ग_लिखो32(rtwdev, REG_RXIQK_11N, 0x01004800);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_TONE_A_11N, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_TONE_A_11N, 0x18008c1c);
	rtw_ग_लिखो32(rtwdev, REG_TX_IQK_TONE_B, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_RX_IQK_TONE_B, 0x38008c1c);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_PI_A_11N, 0x82170000);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_PI_A_11N, 0x28171400);

	/* LOK setting */
	rtw_ग_लिखो32(rtwdev, REG_IQK_AGC_RSP_11N, 0x0046a8d1);

	/* RXIQK mode */
	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);
	mdelay(1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, 0x80000, 0x1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, RFREG_MASK, 0x00007);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD1, RFREG_MASK, 0x0005f);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD0, RFREG_MASK, 0xb3fdb);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, iqk_cfg->reg_lutwe, RFREG_MASK, 0x00000);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x1 @%s RXIQK2 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLINT, RFREG_MASK));
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] RF0x2 @%s RXIQK2 = 0x%x\n",
		iqk_cfg->name,
		rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_WLSEL, RFREG_MASK));

	rtw8723d_iqk_one_shot(rtwdev, false, iqk_cfg);
	status |= rtw8723d_iqk_check_rx_failed(rtwdev, iqk_cfg);

restore:
	rtw8723d_iqk_txrx_path_post(rtwdev, iqk_cfg, backup);

	वापस status;
पूर्ण

अटल
व्योम rtw8723d_iqk_fill_s1_matrix(काष्ठा rtw_dev *rtwdev, स्थिर s32 result[])
अणु
	s32 oldval_1;
	s32 x, y;
	s32 tx1_a, tx1_a_ext;
	s32 tx1_c, tx1_c_ext;

	अगर (result[IQK_S1_TX_X] == 0)
		वापस;

	oldval_1 = rtw_पढ़ो32_mask(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE,
				   BIT_MASK_TXIQ_ELM_D);

	x = iqkxy_to_s32(result[IQK_S1_TX_X]);
	tx1_a = iqk_mult(x, oldval_1, &tx1_a_ext);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE,
			 BIT_MASK_TXIQ_ELM_A, tx1_a);
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_0_ECCA_THRESHOLD,
			 BIT_MASK_OFDM0_EXT_A, tx1_a_ext);

	y = iqkxy_to_s32(result[IQK_S1_TX_Y]);
	tx1_c = iqk_mult(y, oldval_1, &tx1_c_ext);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXIQK_MATRIXA_LSB2_11N, MASKH4BITS,
			 BIT_SET_TXIQ_ELM_C1(tx1_c));
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE,
			 BIT_MASK_TXIQ_ELM_C, BIT_SET_TXIQ_ELM_C2(tx1_c));
	rtw_ग_लिखो32_mask(rtwdev, REG_OFDM_0_ECCA_THRESHOLD,
			 BIT_MASK_OFDM0_EXT_C, tx1_c_ext);

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] X = 0x%x, TX1_A = 0x%x, oldval_1 0x%x\n",
		x, tx1_a, oldval_1);
	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] Y = 0x%x, TX1_C = 0x%x\n", y, tx1_c);

	अगर (result[IQK_S1_RX_X] == 0)
		वापस;

	rtw_ग_लिखो32_mask(rtwdev, REG_A_RXIQI, BIT_MASK_RXIQ_S1_X,
			 result[IQK_S1_RX_X]);
	rtw_ग_लिखो32_mask(rtwdev, REG_A_RXIQI, BIT_MASK_RXIQ_S1_Y1,
			 BIT_SET_RXIQ_S1_Y1(result[IQK_S1_RX_Y]));
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIQK_MATRIX_LSB_11N, BIT_MASK_RXIQ_S1_Y2,
			 BIT_SET_RXIQ_S1_Y2(result[IQK_S1_RX_Y]));
पूर्ण

अटल
व्योम rtw8723d_iqk_fill_s0_matrix(काष्ठा rtw_dev *rtwdev, स्थिर s32 result[])
अणु
	s32 oldval_0;
	s32 x, y;
	s32 tx0_a, tx0_a_ext;
	s32 tx0_c, tx0_c_ext;

	अगर (result[IQK_S0_TX_X] == 0)
		वापस;

	oldval_0 = rtw_पढ़ो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0);

	x = iqkxy_to_s32(result[IQK_S0_TX_X]);
	tx0_a = iqk_mult(x, oldval_0, &tx0_a_ext);

	rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0, tx0_a);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0, tx0_a_ext);

	y = iqkxy_to_s32(result[IQK_S0_TX_Y]);
	tx0_c = iqk_mult(y, oldval_0, &tx0_c_ext);

	rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0, tx0_c);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0, tx0_c_ext);

	अगर (result[IQK_S0_RX_X] == 0)
		वापस;

	rtw_ग_लिखो32_mask(rtwdev, REG_RXIQ_AB_S0, BIT_MASK_RXIQ_X_S0,
			 result[IQK_S0_RX_X]);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIQ_AB_S0, BIT_MASK_RXIQ_Y_S0,
			 result[IQK_S0_RX_Y]);
पूर्ण

अटल व्योम rtw8723d_iqk_path_adda_on(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtw_ग_लिखो32(rtwdev, iqk_adda_regs[i], 0x03c00016);
पूर्ण

अटल व्योम rtw8723d_iqk_config_mac(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, 0xff);
पूर्ण

अटल
व्योम rtw8723d_iqk_rf_standby(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path path)
अणु
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path-%s standby mode!\n",
		path == RF_PATH_A ? "S1" : "S0");

	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);
	mdelay(1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_MODE, RFREG_MASK, 0x10000);
	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
पूर्ण

अटल
bool rtw8723d_iqk_similarity_cmp(काष्ठा rtw_dev *rtwdev, s32 result[][IQK_NR],
				 u8 c1, u8 c2)
अणु
	u32 i, j, dअगरf;
	u32 biपंचांगap = 0;
	u8 candidate[PATH_NR] = अणुIQK_ROUND_INVALID, IQK_ROUND_INVALIDपूर्ण;
	bool ret = true;

	s32 पंचांगp1, पंचांगp2;

	क्रम (i = 0; i < IQK_NR; i++) अणु
		पंचांगp1 = iqkxy_to_s32(result[c1][i]);
		पंचांगp2 = iqkxy_to_s32(result[c2][i]);

		dअगरf = असल(पंचांगp1 - पंचांगp2);

		अगर (dअगरf <= MAX_TOLERANCE)
			जारी;

		अगर ((i == IQK_S1_RX_X || i == IQK_S0_RX_X) && !biपंचांगap) अणु
			अगर (result[c1][i] + result[c1][i + 1] == 0)
				candidate[i / IQK_SX_NR] = c2;
			अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
				candidate[i / IQK_SX_NR] = c1;
			अन्यथा
				biपंचांगap |= BIT(i);
		पूर्ण अन्यथा अणु
			biपंचांगap |= BIT(i);
		पूर्ण
	पूर्ण

	अगर (biपंचांगap != 0)
		जाओ check_sim;

	क्रम (i = 0; i < PATH_NR; i++) अणु
		अगर (candidate[i] == IQK_ROUND_INVALID)
			जारी;

		क्रम (j = i * IQK_SX_NR; j < i * IQK_SX_NR + 2; j++)
			result[IQK_ROUND_HYBRID][j] = result[candidate[i]][j];
		ret = false;
	पूर्ण

	वापस ret;

check_sim:
	क्रम (i = 0; i < IQK_NR; i++) अणु
		j = i & ~1;	/* 2 bits are a pair क्रम IQ[X, Y] */
		अगर (biपंचांगap & GENMASK(j + 1, j))
			जारी;

		result[IQK_ROUND_HYBRID][i] = result[c1][i];
	पूर्ण

	वापस false;
पूर्ण

अटल
व्योम rtw8723d_iqk_precfg_path(काष्ठा rtw_dev *rtwdev, क्रमागत rtw8723d_path path)
अणु
	अगर (path == PATH_S0) अणु
		rtw8723d_iqk_rf_standby(rtwdev, RF_PATH_A);
		rtw8723d_iqk_path_adda_on(rtwdev);
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, EN_IQK);
	rtw_ग_लिखो32(rtwdev, REG_TXIQK_11N, 0x01007c00);
	rtw_ग_लिखो32(rtwdev, REG_RXIQK_11N, 0x01004800);

	अगर (path == PATH_S1) अणु
		rtw8723d_iqk_rf_standby(rtwdev, RF_PATH_B);
		rtw8723d_iqk_path_adda_on(rtwdev);
	पूर्ण
पूर्ण

अटल
व्योम rtw8723d_iqk_one_round(काष्ठा rtw_dev *rtwdev, s32 result[][IQK_NR], u8 t,
			    स्थिर काष्ठा iqk_backup_regs *backup)
अणु
	u32 i;
	u8 s1_ok, s0_ok;

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] IQ Calibration for 1T1R_S0/S1 for %d times\n", t);

	rtw8723d_iqk_path_adda_on(rtwdev);
	rtw8723d_iqk_config_mac(rtwdev);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCK_ANT_SEL_11N, 0x0f000000, 0xf);
	rtw_ग_लिखो32(rtwdev, REG_BB_RX_PATH_11N, 0x03a05611);
	rtw_ग_लिखो32(rtwdev, REG_TRMUX_11N, 0x000800e4);
	rtw_ग_लिखो32(rtwdev, REG_BB_PWR_SAV1_11N, 0x25204200);
	rtw8723d_iqk_precfg_path(rtwdev, PATH_S1);

	क्रम (i = 0; i < PATH_IQK_RETRY; i++) अणु
		s1_ok = rtw8723d_iqk_tx_path(rtwdev, &iqk_tx_cfg[PATH_S1], backup);
		अगर (s1_ok == IQK_TX_OK) अणु
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[IQK] path S1 Tx IQK Success!!\n");
			result[t][IQK_S1_TX_X] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TX, BIT_MASK_RES_TX);
			result[t][IQK_S1_TX_Y] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TY, BIT_MASK_RES_TY);
			अवरोध;
		पूर्ण

		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S1 Tx IQK Fail!!\n");
		result[t][IQK_S1_TX_X] = 0x100;
		result[t][IQK_S1_TX_Y] = 0x0;
	पूर्ण

	क्रम (i = 0; i < PATH_IQK_RETRY; i++) अणु
		s1_ok = rtw8723d_iqk_rx_path(rtwdev, &iqk_tx_cfg[PATH_S1], backup);
		अगर (s1_ok == (IQK_TX_OK | IQK_RX_OK)) अणु
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[IQK] path S1 Rx IQK Success!!\n");
			result[t][IQK_S1_RX_X] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RX, BIT_MASK_RES_RX);
			result[t][IQK_S1_RX_Y] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RY, BIT_MASK_RES_RY);
			अवरोध;
		पूर्ण

		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S1 Rx IQK Fail!!\n");
		result[t][IQK_S1_RX_X] = 0x100;
		result[t][IQK_S1_RX_Y] = 0x0;
	पूर्ण

	अगर (s1_ok == 0x0)
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S1 IQK is failed!!\n");

	rtw8723d_iqk_precfg_path(rtwdev, PATH_S0);

	क्रम (i = 0; i < PATH_IQK_RETRY; i++) अणु
		s0_ok = rtw8723d_iqk_tx_path(rtwdev, &iqk_tx_cfg[PATH_S0], backup);
		अगर (s0_ok == IQK_TX_OK) अणु
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[IQK] path S0 Tx IQK Success!!\n");
			result[t][IQK_S0_TX_X] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TX, BIT_MASK_RES_TX);
			result[t][IQK_S0_TX_Y] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_TY, BIT_MASK_RES_TY);
			अवरोध;
		पूर्ण

		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S0 Tx IQK Fail!!\n");
		result[t][IQK_S0_TX_X] = 0x100;
		result[t][IQK_S0_TX_Y] = 0x0;
	पूर्ण

	क्रम (i = 0; i < PATH_IQK_RETRY; i++) अणु
		s0_ok = rtw8723d_iqk_rx_path(rtwdev, &iqk_tx_cfg[PATH_S0], backup);
		अगर (s0_ok == (IQK_TX_OK | IQK_RX_OK)) अणु
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[IQK] path S0 Rx IQK Success!!\n");

			result[t][IQK_S0_RX_X] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RX, BIT_MASK_RES_RX);
			result[t][IQK_S0_RX_Y] =
			  rtw_पढ़ो32_mask(rtwdev, REG_IQK_RES_RY, BIT_MASK_RES_RY);
			अवरोध;
		पूर्ण

		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S0 Rx IQK Fail!!\n");
		result[t][IQK_S0_RX_X] = 0x100;
		result[t][IQK_S0_RX_Y] = 0x0;
	पूर्ण

	अगर (s0_ok == 0x0)
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] path S0 IQK is failed!!\n");

	rtw_ग_लिखो32_mask(rtwdev, REG_FPGA0_IQK_11N, BIT_MASK_IQK_MOD, RST_IQK);
	mdelay(1);

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK] back to BB mode, load original value!\n");
पूर्ण

अटल व्योम rtw8723d_phy_calibration(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s32 result[IQK_ROUND_SIZE][IQK_NR];
	काष्ठा iqk_backup_regs backup;
	u8 i, j;
	u8 final_candidate = IQK_ROUND_INVALID;
	bool good;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] Start!!!\n");

	स_रखो(result, 0, माप(result));

	rtw8723d_iqk_backup_path_ctrl(rtwdev, &backup);
	rtw8723d_iqk_backup_lte_path_gnt(rtwdev, &backup);
	rtw8723d_iqk_backup_regs(rtwdev, &backup);

	क्रम (i = IQK_ROUND_0; i <= IQK_ROUND_2; i++) अणु
		rtw8723d_iqk_config_path_ctrl(rtwdev);
		rtw8723d_iqk_config_lte_path_gnt(rtwdev);

		rtw8723d_iqk_one_round(rtwdev, result, i, &backup);

		अगर (i > IQK_ROUND_0)
			rtw8723d_iqk_restore_regs(rtwdev, &backup);
		rtw8723d_iqk_restore_lte_path_gnt(rtwdev, &backup);
		rtw8723d_iqk_restore_path_ctrl(rtwdev, &backup);

		क्रम (j = IQK_ROUND_0; j < i; j++) अणु
			good = rtw8723d_iqk_similarity_cmp(rtwdev, result, j, i);

			अगर (good) अणु
				final_candidate = j;
				rtw_dbg(rtwdev, RTW_DBG_RFK,
					"[IQK] cmp %d:%d final_candidate is %x\n",
					j, i, final_candidate);
				जाओ iqk_करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (final_candidate == IQK_ROUND_INVALID) अणु
		s32 reg_पंचांगp = 0;

		क्रम (i = 0; i < IQK_NR; i++)
			reg_पंचांगp += result[IQK_ROUND_HYBRID][i];

		अगर (reg_पंचांगp != 0) अणु
			final_candidate = IQK_ROUND_HYBRID;
		पूर्ण अन्यथा अणु
			WARN(1, "IQK is failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

iqk_करोne:
	rtw8723d_iqk_fill_s1_matrix(rtwdev, result[final_candidate]);
	rtw8723d_iqk_fill_s0_matrix(rtwdev, result[final_candidate]);

	dm_info->iqk.result.s1_x = result[final_candidate][IQK_S1_TX_X];
	dm_info->iqk.result.s1_y = result[final_candidate][IQK_S1_TX_Y];
	dm_info->iqk.result.s0_x = result[final_candidate][IQK_S0_TX_X];
	dm_info->iqk.result.s0_y = result[final_candidate][IQK_S0_TX_Y];
	dm_info->iqk.करोne = true;

out:
	rtw_ग_लिखो32(rtwdev, REG_BB_SEL_BTG, backup.bb_sel_btg);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] final_candidate is %x\n",
		final_candidate);

	क्रम (i = IQK_ROUND_0; i < IQK_ROUND_SIZE; i++)
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[IQK] Result %u: rege94_s1=%x rege9c_s1=%x regea4_s1=%x regeac_s1=%x rege94_s0=%x rege9c_s0=%x regea4_s0=%x regeac_s0=%x %s\n",
			i,
			result[i][0], result[i][1], result[i][2], result[i][3],
			result[i][4], result[i][5], result[i][6], result[i][7],
			final_candidate == i ? "(final candidate)" : "");

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK]0xc80 = 0x%x 0xc94 = 0x%x 0xc14 = 0x%x 0xca0 = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE),
		rtw_पढ़ो32(rtwdev, REG_TXIQK_MATRIXA_LSB2_11N),
		rtw_पढ़ो32(rtwdev, REG_A_RXIQI),
		rtw_पढ़ो32(rtwdev, REG_RXIQK_MATRIX_LSB_11N));
	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[IQK]0xcd0 = 0x%x 0xcd4 = 0x%x 0xcd8 = 0x%x\n",
		rtw_पढ़ो32(rtwdev, REG_TXIQ_AB_S0),
		rtw_पढ़ो32(rtwdev, REG_TXIQ_CD_S0),
		rtw_पढ़ो32(rtwdev, REG_RXIQ_AB_S0));

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[IQK] finished\n");
पूर्ण

अटल व्योम rtw8723d_phy_cck_pd_set(काष्ठा rtw_dev *rtwdev, u8 new_lvl)
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

/* क्रम coex */
अटल व्योम rtw8723d_coex_cfg_init(काष्ठा rtw_dev *rtwdev)
अणु
	/* enable TBTT nterrupt */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	/* BT report packet sample rate	 */
	/* 0x790[5:0]=0x5 */
	rtw_ग_लिखो8_mask(rtwdev, REG_BT_TDMA_TIME, BIT_MASK_SAMPLE_RATE, 0x5);

	/* enable BT counter statistics */
	rtw_ग_लिखो8(rtwdev, REG_BT_STAT_CTRL, 0x1);

	/* enable PTA (3-wire function क्रमm BT side) */
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enable PTA (tx/rx संकेत क्रमm WiFi side) */
	rtw_ग_लिखो8_set(rtwdev, REG_QUEUE_CTRL, BIT_PTA_WL_TX_EN);
पूर्ण

अटल व्योम rtw8723d_coex_cfg_gnt_fix(काष्ठा rtw_dev *rtwdev)
अणु
पूर्ण

अटल व्योम rtw8723d_coex_cfg_gnt_debug(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8_mask(rtwdev, REG_LEDCFG2, BIT(6), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 3, BIT(0), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_GPIO_INTM + 2, BIT(4), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_GPIO_MUXCFG + 2, BIT(1), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 3, BIT(1), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 2, BIT(7), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_SYS_CLKR + 1, BIT(1), 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_SYS_SDIO_CTRL + 3, BIT(3), 0);
पूर्ण

अटल व्योम rtw8723d_coex_cfg_rfe_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	bool aux = efuse->bt_setting & BIT(6);

	coex_rfe->rfe_module_type = rtwdev->efuse.rfe_option;
	coex_rfe->ant_चयन_polarity = 0;
	coex_rfe->ant_चयन_exist = false;
	coex_rfe->ant_चयन_with_bt = false;
	coex_rfe->ant_चयन_भागersity = false;
	coex_rfe->wlg_at_btg = true;

	/* decide antenna at मुख्य or aux */
	अगर (efuse->share_ant) अणु
		अगर (aux)
			rtw_ग_लिखो16(rtwdev, REG_BB_SEL_BTG, 0x80);
		अन्यथा
			rtw_ग_लिखो16(rtwdev, REG_BB_SEL_BTG, 0x200);
	पूर्ण अन्यथा अणु
		अगर (aux)
			rtw_ग_लिखो16(rtwdev, REG_BB_SEL_BTG, 0x280);
		अन्यथा
			rtw_ग_लिखो16(rtwdev, REG_BB_SEL_BTG, 0x0);
	पूर्ण

	/* disable LTE coex in wअगरi side */
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, BIT_LTE_COEX_EN, 0x0);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_WL_TRX_CTRL, MASKLWORD, 0xffff);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_BT_TRX_CTRL, MASKLWORD, 0xffff);
पूर्ण

अटल व्योम rtw8723d_coex_cfg_wl_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 wl_pwr)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	अटल स्थिर u8	wl_tx_घातer[] = अणु0xb2, 0x90पूर्ण;
	u8 pwr;

	अगर (wl_pwr == coex_dm->cur_wl_pwr_lvl)
		वापस;

	coex_dm->cur_wl_pwr_lvl = wl_pwr;

	अगर (coex_dm->cur_wl_pwr_lvl >= ARRAY_SIZE(wl_tx_घातer))
		coex_dm->cur_wl_pwr_lvl = ARRAY_SIZE(wl_tx_घातer) - 1;

	pwr = wl_tx_घातer[coex_dm->cur_wl_pwr_lvl];

	rtw_ग_लिखो8(rtwdev, REG_ANA_PARAM1 + 3, pwr);
पूर्ण

अटल व्योम rtw8723d_coex_cfg_wl_rx_gain(काष्ठा rtw_dev *rtwdev, bool low_gain)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;
	/* WL Rx Low gain on */
	अटल स्थिर u32 wl_rx_low_gain_on[] = अणु
		0xec120101, 0xeb130101, 0xce140101, 0xcd150101, 0xcc160101,
		0xcb170101, 0xca180101, 0x8d190101, 0x8c1a0101, 0x8b1b0101,
		0x4f1c0101, 0x4e1d0101, 0x4d1e0101, 0x4c1f0101, 0x0e200101,
		0x0d210101, 0x0c220101, 0x0b230101, 0xcf240001, 0xce250001,
		0xcd260001, 0xcc270001, 0x8f280001
	पूर्ण;
	/* WL Rx Low gain off */
	अटल स्थिर u32 wl_rx_low_gain_off[] = अणु
		0xec120101, 0xeb130101, 0xea140101, 0xe9150101, 0xe8160101,
		0xe7170101, 0xe6180101, 0xe5190101, 0xe41a0101, 0xe31b0101,
		0xe21c0101, 0xe11d0101, 0xe01e0101, 0x861f0101, 0x85200101,
		0x84210101, 0x83220101, 0x82230101, 0x81240101, 0x80250101,
		0x44260101, 0x43270101, 0x42280101
	पूर्ण;
	u8 i;

	अगर (low_gain == coex_dm->cur_wl_rx_low_gain_en)
		वापस;

	coex_dm->cur_wl_rx_low_gain_en = low_gain;

	अगर (coex_dm->cur_wl_rx_low_gain_en) अणु
		क्रम (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_on); i++)
			rtw_ग_लिखो32(rtwdev, REG_AGCRSSI, wl_rx_low_gain_on[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(wl_rx_low_gain_off); i++)
			rtw_ग_लिखो32(rtwdev, REG_AGCRSSI, wl_rx_low_gain_off[i]);
	पूर्ण
पूर्ण

अटल u8 rtw8723d_pwrtrack_get_limit_ofdm(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 tx_rate = dm_info->tx_rate;
	u8 limit_ofdm = 30;

	चयन (tx_rate) अणु
	हाल DESC_RATE1M...DESC_RATE5_5M:
	हाल DESC_RATE11M:
		अवरोध;
	हाल DESC_RATE6M...DESC_RATE48M:
		limit_ofdm = 36;
		अवरोध;
	हाल DESC_RATE54M:
		limit_ofdm = 34;
		अवरोध;
	हाल DESC_RATEMCS0...DESC_RATEMCS2:
		limit_ofdm = 38;
		अवरोध;
	हाल DESC_RATEMCS3...DESC_RATEMCS4:
		limit_ofdm = 36;
		अवरोध;
	हाल DESC_RATEMCS5...DESC_RATEMCS7:
		limit_ofdm = 34;
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "pwrtrack unhandled tx_rate 0x%x\n", tx_rate);
		अवरोध;
	पूर्ण

	वापस limit_ofdm;
पूर्ण

अटल व्योम rtw8723d_set_iqk_matrix_by_result(काष्ठा rtw_dev *rtwdev,
					      u32 ofdm_swing, u8 rf_path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s32 ele_A, ele_D, ele_C;
	s32 ele_A_ext, ele_C_ext, ele_D_ext;
	s32 iqk_result_x;
	s32 iqk_result_y;
	s32 value32;

	चयन (rf_path) अणु
	शेष:
	हाल RF_PATH_A:
		iqk_result_x = dm_info->iqk.result.s1_x;
		iqk_result_y = dm_info->iqk.result.s1_y;
		अवरोध;
	हाल RF_PATH_B:
		iqk_result_x = dm_info->iqk.result.s0_x;
		iqk_result_y = dm_info->iqk.result.s0_y;
		अवरोध;
	पूर्ण

	/* new element D */
	ele_D = OFDM_SWING_D(ofdm_swing);
	iqk_mult(iqk_result_x, ele_D, &ele_D_ext);
	/* new element A */
	iqk_result_x = iqkxy_to_s32(iqk_result_x);
	ele_A = iqk_mult(iqk_result_x, ele_D, &ele_A_ext);
	/* new element C */
	iqk_result_y = iqkxy_to_s32(iqk_result_y);
	ele_C = iqk_mult(iqk_result_y, ele_D, &ele_C_ext);

	चयन (rf_path) अणु
	हाल RF_PATH_A:
	शेष:
		/* ग_लिखो new elements A, C, D, and element B is always 0 */
		value32 = BIT_SET_TXIQ_ELM_ACD(ele_A, ele_C, ele_D);
		rtw_ग_लिखो32(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE, value32);
		value32 = BIT_SET_TXIQ_ELM_C1(ele_C);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQK_MATRIXA_LSB2_11N, MASKH4BITS,
				 value32);
		value32 = rtw_पढ़ो32(rtwdev, REG_OFDM_0_ECCA_THRESHOLD);
		value32 &= ~BIT_MASK_OFDM0_EXTS;
		value32 |= BIT_SET_OFDM0_EXTS(ele_A_ext, ele_C_ext, ele_D_ext);
		rtw_ग_लिखो32(rtwdev, REG_OFDM_0_ECCA_THRESHOLD, value32);
		अवरोध;

	हाल RF_PATH_B:
		/* ग_लिखो new elements A, C, D, and element B is always 0 */
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0, ele_D);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0, ele_C);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0, ele_A);

		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_EXT_S0,
				 ele_D_ext);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0,
				 ele_A_ext);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0,
				 ele_C_ext);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_set_iqk_matrix(काष्ठा rtw_dev *rtwdev, s8 ofdm_index,
				    u8 rf_path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s32 value32;
	u32 ofdm_swing;

	अगर (ofdm_index >= RTW_OFDM_SWING_TABLE_SIZE)
		ofdm_index = RTW_OFDM_SWING_TABLE_SIZE - 1;
	अन्यथा अगर (ofdm_index < 0)
		ofdm_index = 0;

	ofdm_swing = rtw8723d_ofdm_swing_table[ofdm_index];

	अगर (dm_info->iqk.करोne) अणु
		rtw8723d_set_iqk_matrix_by_result(rtwdev, ofdm_swing, rf_path);
		वापस;
	पूर्ण

	चयन (rf_path) अणु
	हाल RF_PATH_A:
	शेष:
		rtw_ग_लिखो32(rtwdev, REG_OFDM_0_XA_TX_IQ_IMBALANCE, ofdm_swing);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQK_MATRIXA_LSB2_11N, MASKH4BITS,
				 0x00);
		value32 = rtw_पढ़ो32(rtwdev, REG_OFDM_0_ECCA_THRESHOLD);
		value32 &= ~BIT_MASK_OFDM0_EXTS;
		rtw_ग_लिखो32(rtwdev, REG_OFDM_0_ECCA_THRESHOLD, value32);
		अवरोध;

	हाल RF_PATH_B:
		/* image S1:c80 to S0:Cd0 and Cd4 */
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_S0,
				 OFDM_SWING_A(ofdm_swing));
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_B_S0,
				 OFDM_SWING_B(ofdm_swing));
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_S0,
				 OFDM_SWING_C(ofdm_swing));
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_S0,
				 OFDM_SWING_D(ofdm_swing));
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_D_EXT_S0, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_CD_S0, BIT_MASK_TXIQ_C_EXT_S0, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXIQ_AB_S0, BIT_MASK_TXIQ_A_EXT_S0, 0x0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8723d_pwrtrack_set_ofdm_pwr(काष्ठा rtw_dev *rtwdev, s8 swing_idx,
					   s8 txagc_idx)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	dm_info->txagc_remnant_ofdm = txagc_idx;

	rtw8723d_set_iqk_matrix(rtwdev, swing_idx, RF_PATH_A);
	rtw8723d_set_iqk_matrix(rtwdev, swing_idx, RF_PATH_B);
पूर्ण

अटल व्योम rtw8723d_pwrtrack_set_cck_pwr(काष्ठा rtw_dev *rtwdev, s8 swing_idx,
					  s8 txagc_idx)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	dm_info->txagc_remnant_cck = txagc_idx;

	rtw_ग_लिखो32_mask(rtwdev, 0xab4, 0x000007FF,
			 rtw8723d_cck_swing_table[swing_idx]);
पूर्ण

अटल व्योम rtw8723d_pwrtrack_set(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 limit_ofdm;
	u8 limit_cck = 40;
	s8 final_ofdm_swing_index;
	s8 final_cck_swing_index;

	limit_ofdm = rtw8723d_pwrtrack_get_limit_ofdm(rtwdev);

	final_ofdm_swing_index = RTW_DEF_OFDM_SWING_INDEX +
				 dm_info->delta_घातer_index[path];
	final_cck_swing_index = RTW_DEF_CCK_SWING_INDEX +
				dm_info->delta_घातer_index[path];

	अगर (final_ofdm_swing_index > limit_ofdm)
		rtw8723d_pwrtrack_set_ofdm_pwr(rtwdev, limit_ofdm,
					       final_ofdm_swing_index - limit_ofdm);
	अन्यथा अगर (final_ofdm_swing_index < 0)
		rtw8723d_pwrtrack_set_ofdm_pwr(rtwdev, 0,
					       final_ofdm_swing_index);
	अन्यथा
		rtw8723d_pwrtrack_set_ofdm_pwr(rtwdev, final_ofdm_swing_index, 0);

	अगर (final_cck_swing_index > limit_cck)
		rtw8723d_pwrtrack_set_cck_pwr(rtwdev, limit_cck,
					      final_cck_swing_index - limit_cck);
	अन्यथा अगर (final_cck_swing_index < 0)
		rtw8723d_pwrtrack_set_cck_pwr(rtwdev, 0,
					      final_cck_swing_index);
	अन्यथा
		rtw8723d_pwrtrack_set_cck_pwr(rtwdev, final_cck_swing_index, 0);

	rtw_phy_set_tx_घातer_level(rtwdev, hal->current_channel);
पूर्ण

अटल व्योम rtw8723d_pwrtrack_set_xtal(काष्ठा rtw_dev *rtwdev, u8 therm_path,
				       u8 delta)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	स्थिर काष्ठा rtw_pwr_track_tbl *tbl = rtwdev->chip->pwr_track_tbl;
	स्थिर s8 *pwrtrk_xtal;
	s8 xtal_cap;

	अगर (dm_info->thermal_avg[therm_path] >
	    rtwdev->efuse.thermal_meter[therm_path])
		pwrtrk_xtal = tbl->pwrtrk_xtal_p;
	अन्यथा
		pwrtrk_xtal = tbl->pwrtrk_xtal_n;

	xtal_cap = rtwdev->efuse.crystal_cap & 0x3F;
	xtal_cap = clamp_t(s8, xtal_cap + pwrtrk_xtal[delta], 0, 0x3F);
	rtw_ग_लिखो32_mask(rtwdev, REG_AFE_CTRL3, BIT_MASK_XTAL,
			 xtal_cap | (xtal_cap << 6));
पूर्ण

अटल व्योम rtw8723d_phy_pwrtrack(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_swing_table swing_table;
	u8 thermal_value, delta, path;
	bool करो_iqk = false;

	rtw_phy_config_swing_table(rtwdev, &swing_table);

	अगर (rtwdev->efuse.thermal_meter[0] == 0xff)
		वापस;

	thermal_value = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, RF_T_METER, 0xfc00);

	rtw_phy_pwrtrack_avg(rtwdev, thermal_value, RF_PATH_A);

	करो_iqk = rtw_phy_pwrtrack_need_iqk(rtwdev);

	अगर (करो_iqk)
		rtw8723d_lck(rtwdev);

	अगर (dm_info->pwr_trk_init_trigger)
		dm_info->pwr_trk_init_trigger = false;
	अन्यथा अगर (!rtw_phy_pwrtrack_thermal_changed(rtwdev, thermal_value,
						   RF_PATH_A))
		जाओ iqk;

	delta = rtw_phy_pwrtrack_get_delta(rtwdev, RF_PATH_A);

	delta = min_t(u8, delta, RTW_PWR_TRK_TBL_SZ - 1);

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		s8 delta_cur, delta_last;

		delta_last = dm_info->delta_घातer_index[path];
		delta_cur = rtw_phy_pwrtrack_get_pwridx(rtwdev, &swing_table,
							path, RF_PATH_A, delta);
		अगर (delta_last == delta_cur)
			जारी;

		dm_info->delta_घातer_index[path] = delta_cur;
		rtw8723d_pwrtrack_set(rtwdev, path);
	पूर्ण

	rtw8723d_pwrtrack_set_xtal(rtwdev, RF_PATH_A, delta);

iqk:
	अगर (करो_iqk)
		rtw8723d_phy_calibration(rtwdev);
पूर्ण

अटल व्योम rtw8723d_pwr_track(काष्ठा rtw_dev *rtwdev)
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

	rtw8723d_phy_pwrtrack(rtwdev);
	dm_info->pwr_trk_triggered = false;
पूर्ण

अटल काष्ठा rtw_chip_ops rtw8723d_ops = अणु
	.phy_set_param		= rtw8723d_phy_set_param,
	.पढ़ो_efuse		= rtw8723d_पढ़ो_efuse,
	.query_rx_desc		= rtw8723d_query_rx_desc,
	.set_channel		= rtw8723d_set_channel,
	.mac_init		= rtw8723d_mac_init,
	.shutकरोwn		= rtw8723d_shutकरोwn,
	.पढ़ो_rf		= rtw_phy_पढ़ो_rf_sipi,
	.ग_लिखो_rf		= rtw_phy_ग_लिखो_rf_reg_sipi,
	.set_tx_घातer_index	= rtw8723d_set_tx_घातer_index,
	.set_antenna		= शून्य,
	.cfg_lकरो25		= rtw8723d_cfg_lकरो25,
	.efuse_grant		= rtw8723d_efuse_grant,
	.false_alarm_statistics	= rtw8723d_false_alarm_statistics,
	.phy_calibration	= rtw8723d_phy_calibration,
	.cck_pd_set		= rtw8723d_phy_cck_pd_set,
	.pwr_track		= rtw8723d_pwr_track,
	.config_bfee		= शून्य,
	.set_gid_table		= शून्य,
	.cfg_csi_rate		= शून्य,

	.coex_set_init		= rtw8723d_coex_cfg_init,
	.coex_set_ant_चयन	= शून्य,
	.coex_set_gnt_fix	= rtw8723d_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= rtw8723d_coex_cfg_gnt_debug,
	.coex_set_rfe_type	= rtw8723d_coex_cfg_rfe_type,
	.coex_set_wl_tx_घातer	= rtw8723d_coex_cfg_wl_tx_घातer,
	.coex_set_wl_rx_gain	= rtw8723d_coex_cfg_wl_rx_gain,
पूर्ण;

/* Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_sant_8723d[] = अणु
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
	अणु0x66555555, 0x6a5a5aaaपूर्ण,
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
	अणु0xffffffff, 0x5a5a5aaaपूर्ण, /* हाल-25 */
	अणु0x55555555, 0x5a5a5a5aपूर्ण,
	अणु0x55555555, 0xaaaaaaaaपूर्ण,
	अणु0x55555555, 0x6a5a6a5aपूर्ण,
	अणु0x66556655, 0x66556655पूर्ण,
	अणु0x66556aaa, 0x6a5a6aaaपूर्ण, /* हाल-30 */
	अणु0xffffffff, 0x5aaa5aaaपूर्ण,
	अणु0x56555555, 0x5a5a5aaaपूर्ण,
पूर्ण;

/* Non-Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_nsant_8723d[] = अणु
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
अटल स्थिर काष्ठा coex_tdma_para tdma_sant_8723d[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-0 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-1 */
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
अटल स्थिर काष्ठा coex_tdma_para tdma_nsant_8723d[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x01पूर्ण पूर्ण, /* हाल-100 */
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
अटल स्थिर u8 wl_rssi_step_8723d[] = अणु60, 50, 44, 30पूर्ण;
अटल स्थिर u8 bt_rssi_step_8723d[] = अणु30, 30, 30, 30पूर्ण;
अटल स्थिर काष्ठा coex_5g_afh_map afh_5g_8723d[] = अणु अणु0, 0, 0पूर्ण पूर्ण;

अटल स्थिर काष्ठा rtw_hw_reg btg_reg_8723d = अणु
	.addr = REG_BTG_SEL, .mask = BIT_MASK_BTG_WL,
पूर्ण;

/* wl_tx_dec_घातer, bt_tx_dec_घातer, wl_rx_gain, bt_rx_lna_स्थिरrain */
अटल स्थिर काष्ठा coex_rf_para rf_para_tx_8723d[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 10, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु1, 0, true, 4पूर्ण,
	अणु1, 2, true, 4पूर्ण,
	अणु1, 10, true, 4पूर्ण,
	अणु1, 15, true, 4पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_rf_para rf_para_rx_8723d[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 10, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु1, 0, true, 5पूर्ण,
	अणु1, 2, true, 5पूर्ण,
	अणु1, 10, true, 5पूर्ण,
	अणु1, 15, true, 5पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_carddis_to_cardemu_8723d[] = अणु
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(7), 0पूर्ण,
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
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4), 0पूर्ण,
	अणु0x0023,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), 0पूर्ण,
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

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_act_8723d[] = अणु
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
	 RTW_PWR_CMD_POLLING, (BIT(1) | BIT(0)), 0पूर्ण,
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
	अणु0x0010,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(6), BIT(6)पूर्ण,
	अणु0x0049,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0x0063,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0x0062,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0058,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x005A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0x0068,
	 RTW_PWR_CUT_TEST_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), BIT(3)पूर्ण,
	अणु0x0069,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(6), BIT(6)पूर्ण,
	अणु0x001f,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,
	अणु0x0077,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,
	अणु0x001f,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x07पूर्ण,
	अणु0x0077,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x07पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_enable_flow_8723d[] = अणु
	trans_carddis_to_cardemu_8723d,
	trans_cardemu_to_act_8723d,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_lps_8723d[] = अणु
	अणु0x0301,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,
	अणु0x0522,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0xFFपूर्ण,
	अणु0x05F8,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, 0xFF, 0पूर्ण,
	अणु0x05F9,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, 0xFF, 0पूर्ण,
	अणु0x05FA,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, 0xFF, 0पूर्ण,
	अणु0x05FB,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, 0xFF, 0पूर्ण,
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_DELAY, 0, RTW_PWR_DELAY_USपूर्ण,
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0100,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x03पूर्ण,
	अणु0x0101,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0093,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,
	अणु0x0553,
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

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_pre_carddis_8723d[] = अणु
	अणु0x0003,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), 0पूर्ण,
	अणु0x0080,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_cardemu_8723d[] = अणु
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
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
	अणु0x0010,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(6), 0पूर्ण,
	अणु0x0000,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0x0020,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_carddis_8723d[] = अणु
	अणु0x0007,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3) | BIT(4)पूर्ण,
	अणु0x004A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 1पूर्ण,
	अणु0x0023,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,
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
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_post_carddis_8723d[] = अणु
	अणु0x001D,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x001D,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x001C,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x0Eपूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_disable_flow_8723d[] = अणु
	trans_act_to_lps_8723d,
	trans_act_to_pre_carddis_8723d,
	trans_act_to_cardemu_8723d,
	trans_cardemu_to_carddis_8723d,
	trans_act_to_post_carddis_8723d,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_page_table page_table_8723d[] = अणु
	अणु12, 2, 2, 0, 1पूर्ण,
	अणु12, 2, 2, 0, 1पूर्ण,
	अणु12, 2, 2, 0, 1पूर्ण,
	अणु12, 2, 2, 0, 1पूर्ण,
	अणु12, 2, 2, 0, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_rqpn rqpn_table_8723d[] = अणु
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

अटल स्थिर काष्ठा rtw_prioq_addrs prioq_addrs_8723d = अणु
	.prio[RTW_DMA_MAPPING_EXTRA] = अणु
		.rsvd = REG_RQPN_NPQ + 2, .avail = REG_RQPN_NPQ + 3,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_LOW] = अणु
		.rsvd = REG_RQPN + 1, .avail = REG_FIFOPAGE_CTRL_2 + 1,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_NORMAL] = अणु
		.rsvd = REG_RQPN_NPQ, .avail = REG_RQPN_NPQ + 1,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_HIGH] = अणु
		.rsvd = REG_RQPN, .avail = REG_FIFOPAGE_CTRL_2,
	पूर्ण,
	.wsize = false,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen1_param_8723d[] = अणु
	अणु0x0008, 0x4a22,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0x0009, 0x1000,
	 RTW_IP_SEL_PHY,
	 ~(RTW_INTF_PHY_CUT_A | RTW_INTF_PHY_CUT_B),
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para_table phy_para_table_8723d = अणु
	.gen1_para	= pcie_gen1_param_8723d,
	.n_gen1_para	= ARRAY_SIZE(pcie_gen1_param_8723d),
पूर्ण;

अटल स्थिर काष्ठा rtw_hw_reg rtw8723d_dig[] = अणु
	[0] = अणु .addr = 0xc50, .mask = 0x7f पूर्ण,
	[1] = अणु .addr = 0xc50, .mask = 0x7f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_hw_reg rtw8723d_dig_cck[] = अणु
	[0] = अणु .addr = 0xa0c, .mask = 0x3f00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_rf_sipi_addr rtw8723d_rf_sipi_addr[] = अणु
	[RF_PATH_A] = अणु .hssi_1 = 0x820, .lssi_पढ़ो    = 0x8a0,
			.hssi_2 = 0x824, .lssi_पढ़ो_pi = 0x8b8पूर्ण,
	[RF_PATH_B] = अणु .hssi_1 = 0x828, .lssi_पढ़ो    = 0x8a4,
			.hssi_2 = 0x82c, .lssi_पढ़ो_pi = 0x8bcपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_ltecoex_addr rtw8723d_ltecoex_addr = अणु
	.ctrl = REG_LTECOEX_CTRL,
	.wdata = REG_LTECOEX_WRITE_DATA,
	.rdata = REG_LTECOEX_READ_DATA,
पूर्ण;

अटल स्थिर काष्ठा rtw_rfe_def rtw8723d_rfe_defs[] = अणु
	[0] = अणु .phy_pg_tbl	= &rtw8723d_bb_pg_tbl,
		.txpwr_lmt_tbl	= &rtw8723d_txpwr_lmt_tbl,पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2gb_n[] = अणु
	0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 5,
	6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2gb_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7,
	7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2ga_n[] = अणु
	0, 0, 1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5, 5, 5,
	6, 6, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 10
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2ga_p[] = अणु
	0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7,
	7, 8, 8, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2g_cck_b_n[] = अणु
	0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2g_cck_b_p[] = अणु
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2g_cck_a_n[] = अणु
	0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
	6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11
पूर्ण;

अटल स्थिर u8 rtw8723d_pwrtrk_2g_cck_a_p[] = अणु
	0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7,
	7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11
पूर्ण;

अटल स्थिर s8 rtw8723d_pwrtrk_xtal_n[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल स्थिर s8 rtw8723d_pwrtrk_xtal_p[] = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, -10, -12, -14, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_track_tbl rtw8723d_rtw_pwr_track_tbl = अणु
	.pwrtrk_2gb_n = rtw8723d_pwrtrk_2gb_n,
	.pwrtrk_2gb_p = rtw8723d_pwrtrk_2gb_p,
	.pwrtrk_2ga_n = rtw8723d_pwrtrk_2ga_n,
	.pwrtrk_2ga_p = rtw8723d_pwrtrk_2ga_p,
	.pwrtrk_2g_cckb_n = rtw8723d_pwrtrk_2g_cck_b_n,
	.pwrtrk_2g_cckb_p = rtw8723d_pwrtrk_2g_cck_b_p,
	.pwrtrk_2g_ccka_n = rtw8723d_pwrtrk_2g_cck_a_n,
	.pwrtrk_2g_ccka_p = rtw8723d_pwrtrk_2g_cck_a_p,
	.pwrtrk_xtal_p = rtw8723d_pwrtrk_xtal_p,
	.pwrtrk_xtal_n = rtw8723d_pwrtrk_xtal_n,
पूर्ण;

अटल स्थिर काष्ठा rtw_reg_करोमुख्य coex_info_hw_regs_8723d[] = अणु
	अणु0x948, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x67, BIT(7), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x964, BIT(1), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x864, BIT(0), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xab7, BIT(5), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xa01, BIT(7), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x430, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x434, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x42a, MASKLWORD, RTW_REG_DOMAIN_MAC16पूर्ण,
	अणु0x426, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x45e, BIT(3), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x4c6, BIT(4), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x40, BIT(5), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x550, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x522, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x953, BIT(1), RTW_REG_DOMAIN_MAC8पूर्ण,
पूर्ण;

काष्ठा rtw_chip_info rtw8723d_hw_spec = अणु
	.ops = &rtw8723d_ops,
	.id = RTW_CHIP_TYPE_8723D,
	.fw_name = "rtw88/rtw8723d_fw.bin",
	.wlan_cpu = RTW_WCPU_11N,
	.tx_pkt_desc_sz = 40,
	.tx_buf_desc_sz = 16,
	.rx_pkt_desc_sz = 24,
	.rx_buf_desc_sz = 8,
	.phy_efuse_size = 512,
	.log_efuse_size = 512,
	.ptct_efuse_size = 96 + 1,
	.txff_size = 32768,
	.rxff_size = 16384,
	.txgi_factor = 1,
	.is_pwr_by_rate_dec = true,
	.max_घातer_index = 0x3f,
	.csi_buf_pg_num = 0,
	.band = RTW_BAND_2G,
	.page_size = 128,
	.dig_min = 0x20,
	.ht_supported = true,
	.vht_supported = false,
	.lps_deep_mode_supported = 0,
	.sys_func_en = 0xFD,
	.pwr_on_seq = card_enable_flow_8723d,
	.pwr_off_seq = card_disable_flow_8723d,
	.page_table = page_table_8723d,
	.rqpn_table = rqpn_table_8723d,
	.prioq_addrs = &prioq_addrs_8723d,
	.पूर्णांकf_table = &phy_para_table_8723d,
	.dig = rtw8723d_dig,
	.dig_cck = rtw8723d_dig_cck,
	.rf_sipi_addr = अणु0x840, 0x844पूर्ण,
	.rf_sipi_पढ़ो_addr = rtw8723d_rf_sipi_addr,
	.fix_rf_phy_num = 2,
	.ltecoex_addr = &rtw8723d_ltecoex_addr,
	.mac_tbl = &rtw8723d_mac_tbl,
	.agc_tbl = &rtw8723d_agc_tbl,
	.bb_tbl = &rtw8723d_bb_tbl,
	.rf_tbl = अणु&rtw8723d_rf_a_tblपूर्ण,
	.rfe_defs = rtw8723d_rfe_defs,
	.rfe_defs_size = ARRAY_SIZE(rtw8723d_rfe_defs),
	.rx_ldpc = false,
	.pwr_track_tbl = &rtw8723d_rtw_pwr_track_tbl,
	.iqk_threshold = 8,

	.coex_para_ver = 0x2007022f,
	.bt_desired_ver = 0x2f,
	.scbd_support = true,
	.new_scbd10_def = true,
	.ble_hid_profile_support = false,
	.pstdma_type = COEX_PSTDMA_FORCE_LPSOFF,
	.bt_rssi_type = COEX_BTRSSI_RATIO,
	.ant_isolation = 15,
	.rssi_tolerance = 2,
	.wl_rssi_step = wl_rssi_step_8723d,
	.bt_rssi_step = bt_rssi_step_8723d,
	.table_sant_num = ARRAY_SIZE(table_sant_8723d),
	.table_sant = table_sant_8723d,
	.table_nsant_num = ARRAY_SIZE(table_nsant_8723d),
	.table_nsant = table_nsant_8723d,
	.tdma_sant_num = ARRAY_SIZE(tdma_sant_8723d),
	.tdma_sant = tdma_sant_8723d,
	.tdma_nsant_num = ARRAY_SIZE(tdma_nsant_8723d),
	.tdma_nsant = tdma_nsant_8723d,
	.wl_rf_para_num = ARRAY_SIZE(rf_para_tx_8723d),
	.wl_rf_para_tx = rf_para_tx_8723d,
	.wl_rf_para_rx = rf_para_rx_8723d,
	.bt_afh_span_bw20 = 0x20,
	.bt_afh_span_bw40 = 0x30,
	.afh_5g_num = ARRAY_SIZE(afh_5g_8723d),
	.afh_5g = afh_5g_8723d,
	.btg_reg = &btg_reg_8723d,

	.coex_info_hw_regs_num = ARRAY_SIZE(coex_info_hw_regs_8723d),
	.coex_info_hw_regs = coex_info_hw_regs_8723d,
पूर्ण;
EXPORT_SYMBOL(rtw8723d_hw_spec);

MODULE_FIRMWARE("rtw88/rtw8723d_fw.bin");

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11n wireless 8723d driver");
MODULE_LICENSE("Dual BSD/GPL");

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C_PHY_H__
#घोषणा __RTL92C_PHY_H__

#घोषणा MAX_PRECMD_CNT				16
#घोषणा MAX_RFDEPENDCMD_CNT			16
#घोषणा MAX_POSTCMD_CNT				16

#घोषणा MAX_DOZE_WAITING_TIMES_9x		64

#घोषणा RT_CANNOT_IO(hw)			false
#घोषणा HIGHPOWER_RADIOA_ARRAYLEN		22

#घोषणा IQK_ADDA_REG_NUM			16
#घोषणा MAX_TOLERANCE				5
#घोषणा	IQK_DELAY_TIME				1

#घोषणा	APK_BB_REG_NUM				5
#घोषणा	APK_AFE_REG_NUM				16
#घोषणा	APK_CURVE_REG_NUM			4
#घोषणा	PATH_NUM				2

#घोषणा LOOP_LIMIT				5
#घोषणा MAX_STALL_TIME				50
#घोषणा ANTENNADIVERSITYVALUE			0x80
#घोषणा MAX_TXPWR_IDX_NMODE_92S			63
#घोषणा reset_cnt_limit				3

#घोषणा IQK_ADDA_REG_NUM			16
#घोषणा IQK_MAC_REG_NUM				4

#घोषणा IQK_DELAY_TIME				1

#घोषणा RF6052_MAX_PATH				2

#घोषणा CT_OFFSET_MAC_ADDR			0X16

#घोषणा CT_OFFSET_CCK_TX_PWR_IDX		0x5A
#घोषणा CT_OFFSET_HT401S_TX_PWR_IDX		0x60
#घोषणा CT_OFFSET_HT402S_TX_PWR_IDX_DIFF	0x66
#घोषणा CT_OFFSET_HT20_TX_PWR_IDX_DIFF		0x69
#घोषणा CT_OFFSET_OFDM_TX_PWR_IDX_DIFF		0x6C

#घोषणा CT_OFFSET_HT40_MAX_PWR_OFFSET		0x6F
#घोषणा CT_OFFSET_HT20_MAX_PWR_OFFSET		0x72

#घोषणा CT_OFFSET_CHANNEL_PLAH			0x75
#घोषणा CT_OFFSET_THERMAL_METER			0x78
#घोषणा CT_OFFSET_RF_OPTION			0x79
#घोषणा CT_OFFSET_VERSION			0x7E
#घोषणा CT_OFFSET_CUSTOMER_ID			0x7F

#घोषणा RTL92C_MAX_PATH_NUM			2

क्रमागत hw90_block_e अणु
	HW90_BLOCK_MAC = 0,
	HW90_BLOCK_PHY0 = 1,
	HW90_BLOCK_PHY1 = 2,
	HW90_BLOCK_RF = 3,
	HW90_BLOCK_MAXIMUM = 4,
पूर्ण;

क्रमागत baseband_config_type अणु
	BASEBAND_CONFIG_PHY_REG = 0,
	BASEBAND_CONFIG_AGC_TAB = 1,
पूर्ण;

क्रमागत ra_offset_area अणु
	RA_OFFSET_LEGACY_OFDM1,
	RA_OFFSET_LEGACY_OFDM2,
	RA_OFFSET_HT_OFDM1,
	RA_OFFSET_HT_OFDM2,
	RA_OFFSET_HT_OFDM3,
	RA_OFFSET_HT_OFDM4,
	RA_OFFSET_HT_CCK,
पूर्ण;

क्रमागत antenna_path अणु
	ANTENNA_NONE,
	ANTENNA_D,
	ANTENNA_C,
	ANTENNA_CD,
	ANTENNA_B,
	ANTENNA_BD,
	ANTENNA_BC,
	ANTENNA_BCD,
	ANTENNA_A,
	ANTENNA_AD,
	ANTENNA_AC,
	ANTENNA_ACD,
	ANTENNA_AB,
	ANTENNA_ABD,
	ANTENNA_ABC,
	ANTENNA_ABCD
पूर्ण;

काष्ठा r_antenna_select_ofdm अणु
	u32 r_tx_antenna:4;
	u32 r_ant_l:4;
	u32 r_ant_non_ht:4;
	u32 r_ant_ht1:4;
	u32 r_ant_ht2:4;
	u32 r_ant_ht_s1:4;
	u32 r_ant_non_ht_s1:4;
	u32 ofdm_txsc:2;
	u32 reserved:2;
पूर्ण;

काष्ठा r_antenna_select_cck अणु
	u8 r_cckrx_enable_2:2;
	u8 r_cckrx_enable:2;
	u8 r_ccktx_enable:4;
पूर्ण;

काष्ठा efuse_contents अणु
	u8 mac_addr[ETH_ALEN];
	u8 cck_tx_घातer_idx[6];
	u8 ht40_1s_tx_घातer_idx[6];
	u8 ht40_2s_tx_घातer_idx_dअगरf[3];
	u8 ht20_tx_घातer_idx_dअगरf[3];
	u8 ofdm_tx_घातer_idx_dअगरf[3];
	u8 ht40_max_घातer_offset[3];
	u8 ht20_max_घातer_offset[3];
	u8 channel_plan;
	u8 thermal_meter;
	u8 rf_option[5];
	u8 version;
	u8 oem_id;
	u8 regulatory;
पूर्ण;

काष्ठा tx_घातer_काष्ठा अणु
	u8 cck[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 ht40_1s[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 ht40_2s[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 ht20_dअगरf[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 legacy_ht_dअगरf[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 legacy_ht_txघातerdअगरf;
	u8 groupht20[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 groupht40[RTL92C_MAX_PATH_NUM][CHANNEL_MAX_NUMBER];
	u8 pwrgroup_cnt;
	u32 mcs_original_offset[4][16];
पूर्ण;

u32 rtl8723e_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			      क्रमागत radio_path rfpath, u32 regaddr,
			      u32 biपंचांगask);
व्योम rtl8723e_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			     क्रमागत radio_path rfpath, u32 regaddr,
			     u32 biपंचांगask, u32 data);
bool rtl8723e_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool rtl8723e_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl8723e_phy_rf_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_config_rf_with_feaderfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath);
व्योम rtl8723e_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw,
				    दीर्घ *घातerlevel);
व्योम rtl8723e_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel);
bool rtl8723e_phy_update_txघातer_dbm(काष्ठा ieee80211_hw *hw,
				     दीर्घ घातer_indbm);
व्योम rtl8723e_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw,
					u8 operation);
व्योम rtl8723e_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			      क्रमागत nl80211_channel_type ch_type);
व्योम rtl8723e_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw);
u8 rtl8723e_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery);
व्योम rtl8723e_phy_lc_calibrate(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य);
bool rtl8723e_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					    क्रमागत radio_path rfpath);
bool rtl8723e_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype);
bool rtl8723e_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				     क्रमागत rf_pwrstate rfpwr_state);

#पूर्ण_अगर

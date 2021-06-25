<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C_PHY_COMMON_H__
#घोषणा __RTL92C_PHY_COMMON_H__

#घोषणा MAX_PRECMD_CNT			16
#घोषणा MAX_RFDEPENDCMD_CNT		16
#घोषणा MAX_POSTCMD_CNT			16

#घोषणा MAX_DOZE_WAITING_TIMES_9x	64

#घोषणा RT_CANNOT_IO(hw)		false
#घोषणा HIGHPOWER_RADIOA_ARRAYLEN	22

#घोषणा MAX_TOLERANCE			5

#घोषणा	APK_BB_REG_NUM			5
#घोषणा	APK_AFE_REG_NUM			16
#घोषणा	APK_CURVE_REG_NUM		4
#घोषणा	PATH_NUM			2

#घोषणा LOOP_LIMIT			5
#घोषणा MAX_STALL_TIME			50
#घोषणा ANTENNADIVERSITYVALUE		0x80
#घोषणा MAX_TXPWR_IDX_NMODE_92S		63
#घोषणा RESET_CNT_LIMIT			3

#घोषणा IQK_ADDA_REG_NUM		16
#घोषणा IQK_MAC_REG_NUM			4

#घोषणा IQK_DELAY_TIME			1
#घोषणा RF90_PATH_MAX			2

#घोषणा CT_OFFSET_MAC_ADDR		0X16

#घोषणा CT_OFFSET_CCK_TX_PWR_IDX	0x5A
#घोषणा CT_OFFSET_HT401S_TX_PWR_IDX	0x60
#घोषणा CT_OFFSET_HT402S_TX_PWR_IDX_DIF	0x66
#घोषणा CT_OFFSET_HT20_TX_PWR_IDX_DIFF	0x69
#घोषणा CT_OFFSET_OFDM_TX_PWR_IDX_DIFF	0x6C

#घोषणा CT_OFFSET_HT40_MAX_PWR_OFFSET	0x6F
#घोषणा CT_OFFSET_HT20_MAX_PWR_OFFSET	0x72

#घोषणा CT_OFFSET_CHANNEL_PLAH		0x75
#घोषणा CT_OFFSET_THERMAL_METER		0x78
#घोषणा CT_OFFSET_RF_OPTION		0x79
#घोषणा CT_OFFSET_VERSION		0x7E
#घोषणा CT_OFFSET_CUSTOMER_ID		0x7F

#घोषणा RTL92C_MAX_PATH_NUM		2
#घोषणा LLT_LAST_ENTRY_OF_TX_PKT_BUFFER	255

क्रमागत swchnlcmd_id अणु
	CMDID_END,
	CMDID_SET_TXPOWEROWER_LEVEL,
	CMDID_BBREGWRITE10,
	CMDID_WRITEPORT_ULONG,
	CMDID_WRITEPORT_USHORT,
	CMDID_WRITEPORT_UCHAR,
	CMDID_RF_WRITEREG,
पूर्ण;

काष्ठा swchnlcmd अणु
	क्रमागत swchnlcmd_id cmdid;
	u32 para1;
	u32 para2;
	u32 msdelay;
पूर्ण;

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

u32 rtl92c_phy_query_bb_reg(काष्ठा ieee80211_hw *hw,
				   u32 regaddr, u32 biपंचांगask);
व्योम rtl92c_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
				  u32 regaddr, u32 biपंचांगask, u32 data);
u32 rtl92c_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
				   क्रमागत radio_path rfpath, u32 regaddr,
				   u32 biपंचांगask);
bool rtl92c_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_rf_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_config_rf_with_feaderfile(काष्ठा ieee80211_hw *hw,
						 क्रमागत radio_path rfpath);
व्योम rtl92c_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw,
					 दीर्घ *घातerlevel);
व्योम rtl92c_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel);
bool rtl92c_phy_update_txघातer_dbm(काष्ठा ieee80211_hw *hw,
					  दीर्घ घातer_indbm);
व्योम rtl92c_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
				   क्रमागत nl80211_channel_type ch_type);
व्योम rtl92c_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw);
u8 rtl92c_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery);
व्योम rtl92c_phy_set_beacon_hw_reg(काष्ठा ieee80211_hw *hw,
					 u16 beaconपूर्णांकerval);
व्योम rtl92c_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta);
व्योम rtl92c_phy_lc_calibrate(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य);
bool rtl92c_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath);
bool rtl8192_phy_check_is_legal_rfpath(काष्ठा ieee80211_hw *hw,
					      u32 rfpath);
bool rtl92c_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
					  क्रमागत rf_pwrstate rfpwr_state);
व्योम rtl92ce_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_set_io(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_bb_block_on(काष्ठा ieee80211_hw *hw);
u32 _rtl92c_phy_calculate_bit_shअगरt(u32 biपंचांगask);
दीर्घ _rtl92c_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
				  क्रमागत wireless_mode wirelessmode,
				  u8 txpwridx);
u8 _rtl92c_phy_dbm_to_txpwr_idx(काष्ठा ieee80211_hw *hw,
				क्रमागत wireless_mode wirelessmode,
				दीर्घ घातer_indbm);
व्योम _rtl92c_phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw);
व्योम _rtl92c_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw);
bool _rtl92c_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
				      u8 channel, u8 *stage, u8 *step,
				      u32 *delay);
u8 rtl92c_bt_rssi_state_change(काष्ठा ieee80211_hw *hw);
u32 _rtl92c_phy_fw_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				  क्रमागत radio_path rfpath, u32 offset);
व्योम _rtl92c_phy_fw_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				    क्रमागत radio_path rfpath, u32 offset,
				    u32 data);
u32 _rtl92c_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
			       क्रमागत radio_path rfpath, u32 offset);
व्योम _rtl92c_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				 क्रमागत radio_path rfpath, u32 offset,
				 u32 data);
bool _rtl92c_phy_bb8192c_config_parafile(काष्ठा ieee80211_hw *hw);
व्योम _rtl92c_store_pwrindex_dअगरfrate_offset(काष्ठा ieee80211_hw *hw,
					    u32 regaddr, u32 biपंचांगask,
					    u32 data);
bool rtl92c_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype);

#पूर्ण_अगर

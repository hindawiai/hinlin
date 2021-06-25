<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C_PHY_H__
#घोषणा __RTL92C_PHY_H__

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

bool rtl92c_phy_bb_config(काष्ठा ieee80211_hw *hw);
u32 rtl92c_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask);
व्योम rtl92c_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask,
			   u32 data);
u32 rtl92c_phy_query_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask);
व्योम rtl92ce_phy_set_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask, u32 data);
bool rtl92c_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool rtl92ce_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_rf_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_config_rf_with_feaderfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath);
व्योम rtl92c_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw, दीर्घ *घातerlevel);
व्योम rtl92c_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel);
bool rtl92c_phy_update_txघातer_dbm(काष्ठा ieee80211_hw *hw,
					  दीर्घ घातer_indbm);
व्योम rtl92c_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type);
व्योम rtl92c_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw);
u8 rtl92c_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery);
व्योम rtl92c_phy_set_beacon_hw_reg(काष्ठा ieee80211_hw *hw, u16 beaconपूर्णांकerval);
व्योम rtl92c_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta);
व्योम rtl92c_phy_lc_calibrate(काष्ठा ieee80211_hw *hw);
व्योम _rtl92ce_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t);
व्योम rtl92c_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य);
bool rtl92c_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath);
bool rtl8192_phy_check_is_legal_rfpath(काष्ठा ieee80211_hw *hw,
				       u32 rfpath);
bool rtl92ce_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				    क्रमागत rf_pwrstate rfpwr_state);
व्योम rtl92ce_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype);
व्योम rtl92c_phy_set_io(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_bb_block_on(काष्ठा ieee80211_hw *hw);
u32 _rtl92c_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			       u32 offset);
u32 _rtl92c_phy_fw_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				  क्रमागत radio_path rfpath, u32 offset);
u32 _rtl92c_phy_calculate_bit_shअगरt(u32 biपंचांगask);
व्योम _rtl92c_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				 क्रमागत radio_path rfpath, u32 offset, u32 data);
व्योम _rtl92c_phy_fw_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				    क्रमागत radio_path rfpath, u32 offset,
				    u32 data);
व्योम _rtl92c_store_pwrindex_dअगरfrate_offset(काष्ठा ieee80211_hw *hw,
					    u32 regaddr, u32 biपंचांगask, u32 data);
bool _rtl92ce_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
व्योम _rtl92c_phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw);
bool _rtl92c_phy_bb8192c_config_parafile(काष्ठा ieee80211_hw *hw);
व्योम _rtl92c_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state);
bool _rtl92ce_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
					    u8 configtype);
bool _rtl92ce_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
					      u8 configtype);
व्योम rtl92ce_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL92E_PHY_H__
#घोषणा __RTL92E_PHY_H__

/* MAX_TX_COUNT must always set to 4, otherwise पढ़ो efuse table sequence
 * will be wrong.
 */
#घोषणा MAX_TX_COUNT				4
#घोषणा TX_1S					0
#घोषणा TX_2S					1
#घोषणा TX_3S					2
#घोषणा TX_4S					3

#घोषणा MAX_POWER_INDEX				0x3f

#घोषणा MAX_PRECMD_CNT				16
#घोषणा MAX_RFDEPENDCMD_CNT			16
#घोषणा MAX_POSTCMD_CNT				16

#घोषणा MAX_DOZE_WAITING_TIMES_9x		64

#घोषणा RT_CANNOT_IO(hw)			false
#घोषणा HIGHPOWER_RADIOA_ARRAYLEN		22

#घोषणा IQK_ADDA_REG_NUM			16
#घोषणा IQK_MAC_REG_NUM				4
#घोषणा IQK_BB_REG_NUM				9
#घोषणा MAX_TOLERANCE				5
#घोषणा	IQK_DELAY_TIME				10
#घोषणा	index_mapping_NUM			15

#घोषणा	APK_BB_REG_NUM				5
#घोषणा	APK_AFE_REG_NUM				16
#घोषणा	APK_CURVE_REG_NUM			4
#घोषणा	PATH_NUM				2

#घोषणा LOOP_LIMIT				5
#घोषणा MAX_STALL_TIME				50
#घोषणा ANTENNADIVERSITYVALUE			0x80
#घोषणा MAX_TXPWR_IDX_NMODE_92S			63
#घोषणा RESET_CNT_LIMIT				3

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

क्रमागत baseband_config_type अणु
	BASEBAND_CONFIG_PHY_REG = 0,
	BASEBAND_CONFIG_AGC_TAB = 1,
पूर्ण;

क्रमागत ant_भाग_प्रकारype अणु
	NO_ANTDIV = 0xFF,
	CG_TRX_HW_ANTDIV = 0x01,
	CGCS_RX_HW_ANTDIV = 0x02,
	FIXED_HW_ANTDIV = 0x03,
	CG_TRX_SMART_ANTDIV = 0x04,
	CGCS_RX_SW_ANTDIV = 0x05,
पूर्ण;

u32 rtl92ee_phy_query_bb_reg(काष्ठा ieee80211_hw *hw,
			     u32 regaddr, u32 biपंचांगask);
व्योम rtl92ee_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
			    u32 regaddr, u32 biपंचांगask, u32 data);
u32 rtl92ee_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			     क्रमागत radio_path rfpath, u32 regaddr,
			     u32 biपंचांगask);
व्योम rtl92ee_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath, u32 regaddr,
			    u32 biपंचांगask, u32 data);
bool rtl92ee_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool rtl92ee_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl92ee_phy_rf_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw,
				   दीर्घ *घातerlevel);
व्योम rtl92ee_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel);
व्योम rtl92ee_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw,
				       u8 operation);
व्योम rtl92ee_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			     क्रमागत nl80211_channel_type ch_type);
व्योम rtl92ee_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw);
u8 rtl92ee_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery);
व्योम rtl92ee_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta);
व्योम rtl92ee_phy_lc_calibrate(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य);
bool rtl92ee_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					   क्रमागत radio_path rfpath);
bool rtl92ee_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype);
bool rtl92ee_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				    क्रमागत rf_pwrstate rfpwr_state);

#पूर्ण_अगर

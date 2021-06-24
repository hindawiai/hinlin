<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92D_PHY_H__
#घोषणा __RTL92D_PHY_H__

#घोषणा MAX_PRECMD_CNT				16
#घोषणा MAX_RFDEPENDCMD_CNT			16
#घोषणा MAX_POSTCMD_CNT				16

#घोषणा MAX_DOZE_WAITING_TIMES_9x		64

#घोषणा RT_CANNOT_IO(hw)			false
#घोषणा HIGHPOWER_RADIOA_ARRAYLEN		22

#घोषणा MAX_TOLERANCE				5

#घोषणा	APK_BB_REG_NUM				5
#घोषणा	APK_AFE_REG_NUM				16
#घोषणा	APK_CURVE_REG_NUM			4
#घोषणा	PATH_NUM				2

#घोषणा LOOP_LIMIT				5
#घोषणा MAX_STALL_TIME				50
#घोषणा ANTENNA_DIVERSITY_VALUE			0x80
#घोषणा MAX_TXPWR_IDX_NMODE_92S			63
#घोषणा RESET_CNT_LIMIT				3

#घोषणा IQK_ADDA_REG_NUM			16
#घोषणा IQK_BB_REG_NUM				10
#घोषणा IQK_BB_REG_NUM_test			6
#घोषणा IQK_MAC_REG_NUM				4
#घोषणा RX_INDEX_MAPPING_NUM			15

#घोषणा IQK_DELAY_TIME				1

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

क्रमागत rf_content अणु
	radioa_txt = 0,
	radiob_txt = 1,
	radioc_txt = 2,
	radiod_txt = 3
पूर्ण;

अटल अंतरभूत व्योम rtl92d_acquire_cckandrw_pagea_ctl(काष्ठा ieee80211_hw *hw,
						     अचिन्हित दीर्घ *flag)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->rtlhal.पूर्णांकerfaceindex == 1)
		spin_lock_irqsave(&rtlpriv->locks.cck_and_rw_pagea_lock, *flag);
पूर्ण

अटल अंतरभूत व्योम rtl92d_release_cckandrw_pagea_ctl(काष्ठा ieee80211_hw *hw,
						     अचिन्हित दीर्घ *flag)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->rtlhal.पूर्णांकerfaceindex == 1)
		spin_unlock_irqrestore(&rtlpriv->locks.cck_and_rw_pagea_lock,
			*flag);
पूर्ण

u32 rtl92d_phy_query_bb_reg(काष्ठा ieee80211_hw *hw,
			    u32 regaddr, u32 biपंचांगask);
व्योम rtl92d_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
			   u32 regaddr, u32 biपंचांगask, u32 data);
u32 rtl92d_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath, u32 regaddr,
			    u32 biपंचांगask);
व्योम rtl92d_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			   क्रमागत radio_path rfpath, u32 regaddr,
			   u32 biपंचांगask, u32 data);
bool rtl92d_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool rtl92d_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl92d_phy_rf_config(काष्ठा ieee80211_hw *hw);
bool rtl92c_phy_config_rf_with_feaderfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath);
व्योम rtl92d_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel);
व्योम rtl92d_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type);
u8 rtl92d_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
bool rtl92d_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत rf_content content,
					  क्रमागत radio_path rfpath);
bool rtl92d_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype);
bool rtl92d_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state);

व्योम rtl92d_phy_config_macphymode(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_config_macphymode_info(काष्ठा ieee80211_hw *hw);
u8 rtl92d_get_chnlgroup_fromarray(u8 chnl);
व्योम rtl92d_phy_set_घातeron(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_config_maccoexist_rfpage(काष्ठा ieee80211_hw *hw);
bool rtl92d_phy_check_घातeroff(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_lc_calibrate(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_update_bbrf_configuration(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta);
व्योम rtl92d_phy_iq_calibrate(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_phy_reset_iqk_result(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_release_cckandrw_pagea_ctl(काष्ठा ieee80211_hw *hw,
				       अचिन्हित दीर्घ *flag);
व्योम rtl92d_acquire_cckandrw_pagea_ctl(काष्ठा ieee80211_hw *hw,
				       अचिन्हित दीर्घ *flag);
u8 rtl92d_get_rightchnlplace_क्रम_iqk(u8 chnl);
व्योम rtl92d_phy_reload_iqk_setting(काष्ठा ieee80211_hw *hw, u8 channel);

#पूर्ण_अगर

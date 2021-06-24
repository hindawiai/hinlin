<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92S_PHY_H__
#घोषणा __RTL92S_PHY_H__

#घोषणा MAX_TXPWR_IDX_NMODE_92S		63
#घोषणा MAX_DOZE_WAITING_TIMES_9x	64

/* Channel चयन:The size of
 * command tables क्रम चयन channel */
#घोषणा MAX_PRECMD_CNT			16
#घोषणा MAX_RFDEPENDCMD_CNT		16
#घोषणा MAX_POSTCMD_CNT			16

#घोषणा RF90_PATH_MAX			4
#घोषणा RF6052_MAX_PATH			2

क्रमागत version_8192s अणु
	VERSION_8192S_ACUT,
	VERSION_8192S_BCUT,
	VERSION_8192S_CCUT
पूर्ण;

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
	/* Radio Path A */
	BASEBAND_CONFIG_PHY_REG = 0,
	/* Radio Path B */
	BASEBAND_CONFIG_AGC_TAB = 1,
पूर्ण;

#घोषणा hal_get_firmwareversion(rtlpriv) \
	(((काष्ठा rt_firmware *)(rtlpriv->rtlhal.pfirmware))->firmwareversion)

u32 rtl92s_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask);
व्योम rtl92s_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask,
			   u32 data);
व्योम rtl92s_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation);
u32 rtl92s_phy_query_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask);
व्योम rtl92s_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,	क्रमागत radio_path rfpath,
			   u32 regaddr, u32 biपंचांगask, u32 data);
व्योम rtl92s_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type);
u8 rtl92s_phy_sw_chnl(काष्ठा ieee80211_hw *hw);
bool rtl92s_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfघातer_state);
bool rtl92s_phy_mac_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_phy_चयन_ephy_parameter(काष्ठा ieee80211_hw *hw);
bool rtl92s_phy_bb_config(काष्ठा ieee80211_hw *hw);
bool rtl92s_phy_rf_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_phy_set_txघातer(काष्ठा ieee80211_hw *hw, u8	channel);
bool rtl92s_phy_set_fw_cmd(काष्ठा ieee80211_hw *hw, क्रमागत fwcmd_iotype fwcmd_io);
व्योम rtl92s_phy_chk_fwcmd_ioकरोne(काष्ठा ieee80211_hw *hw);
व्योम rtl92s_phy_set_beacon_hwreg(काष्ठा ieee80211_hw *hw, u16 beaconपूर्णांकerval);
u8 rtl92s_phy_config_rf(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath) ;

#पूर्ण_अगर


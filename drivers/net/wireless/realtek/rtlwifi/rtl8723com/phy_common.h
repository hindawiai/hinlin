<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __PHY_COMMON__
#घोषणा __PHY_COMMON__

#घोषणा RT_CANNOT_IO(hw)			false

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

u32 rtl8723_phy_query_bb_reg(काष्ठा ieee80211_hw *hw,
			     u32 regaddr, u32 biपंचांगask);
व्योम rtl8723_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr,
			      u32 biपंचांगask, u32 data);
u32 rtl8723_phy_calculate_bit_shअगरt(u32 biपंचांगask);
u32 rtl8723_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
			       क्रमागत radio_path rfpath, u32 offset);
व्योम rtl8723_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				 क्रमागत radio_path rfpath,
				 u32 offset, u32 data);
दीर्घ rtl8723_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
				  क्रमागत wireless_mode wirelessmode,
				  u8 txpwridx);
व्योम rtl8723_phy_init_bb_rf_reg_def(काष्ठा ieee80211_hw *hw);
bool rtl8723_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
				      u32 cmdtableidx,
				      u32 cmdtablesz,
				      क्रमागत swchnlcmd_id cmdid,
				      u32 para1, u32 para2,
				      u32 msdelay);
व्योम rtl8723_phy_path_a_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
					bool iqk_ok,
					दीर्घ result[][8],
					u8 final_candidate,
					bool btxonly);
व्योम rtl8723_save_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw, u32 *addareg,
				 u32 *addabackup, u32 रेजिस्टरnum);
व्योम rtl8723_phy_save_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				    u32 *macreg, u32 *macbackup);
व्योम rtl8723_phy_reload_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				       u32 *addareg, u32 *addabackup,
				       u32 regiesternum);
व्योम rtl8723_phy_reload_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				      u32 *macreg, u32 *macbackup);
व्योम rtl8723_phy_path_adda_on(काष्ठा ieee80211_hw *hw, u32 *addareg,
			      bool is_patha_on, bool is2t);
व्योम rtl8723_phy_mac_setting_calibration(काष्ठा ieee80211_hw *hw,
					 u32 *macreg, u32 *macbackup);
व्योम rtl8723_phy_path_a_standby(काष्ठा ieee80211_hw *hw);
व्योम rtl8723_phy_pi_mode_चयन(काष्ठा ieee80211_hw *hw, bool pi_mode);

#पूर्ण_अगर

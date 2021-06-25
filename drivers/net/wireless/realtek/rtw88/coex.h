<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_COEX_H__
#घोषणा __RTW_COEX_H__

#घोषणा COEX_CCK_2	0x1
#घोषणा COEX_RESP_ACK_BY_WL_FW	0x1
#घोषणा COEX_REQUEST_TIMEOUT	msecs_to_jअगरfies(10)

#घोषणा COEX_MIN_DELAY		10 /* delay unit in ms */
#घोषणा COEX_RFK_TIMEOUT	600 /* RFK समयout in ms */

#घोषणा COEX_RF_OFF	0x0
#घोषणा COEX_RF_ON	0x1

#घोषणा COEX_H2C69_WL_LEAKAP	0xc
#घोषणा PARA1_H2C69_DIS_5MS	0x1
#घोषणा PARA1_H2C69_EN_5MS	0x0

#घोषणा COEX_H2C69_TDMA_SLOT	0xb
#घोषणा PARA1_H2C69_TDMA_4SLOT	0xc1
#घोषणा PARA1_H2C69_TDMA_2SLOT	0x1
#घोषणा PARA1_H2C69_TBTT_TIMES	GENMASK(5, 0)
#घोषणा PARA1_H2C69_TBTT_DIV100	BIT(7)

#घोषणा COEX_H2C69_TOGGLE_TABLE_A 0xd
#घोषणा COEX_H2C69_TOGGLE_TABLE_B 0x7

#घोषणा TDMA_4SLOT	BIT(8)

#घोषणा TDMA_TIMER_TYPE_2SLOT 0
#घोषणा TDMA_TIMER_TYPE_4SLOT 3

#घोषणा COEX_RSSI_STEP		4

#घोषणा COEX_RSSI_HIGH(rssi) \
	(अणु typeof(rssi) __rssi__ = rssi; \
	   (__rssi__ == COEX_RSSI_STATE_HIGH || \
	    __rssi__ == COEX_RSSI_STATE_STAY_HIGH ? true : false); पूर्ण)

#घोषणा COEX_RSSI_MEDIUM(rssi) \
	(अणु typeof(rssi) __rssi__ = rssi; \
	   (__rssi__ == COEX_RSSI_STATE_MEDIUM || \
	    __rssi__ == COEX_RSSI_STATE_STAY_MEDIUM ? true : false); पूर्ण)

#घोषणा COEX_RSSI_LOW(rssi) \
	(अणु typeof(rssi) __rssi__ = rssi; \
	   (__rssi__ == COEX_RSSI_STATE_LOW || \
	    __rssi__ == COEX_RSSI_STATE_STAY_LOW ? true : false); पूर्ण)

#घोषणा GET_COEX_RESP_BT_SUPP_VER(payload)				\
	le64_get_bits(*((__le64 *)(payload)), GENMASK_ULL(39, 32))
#घोषणा GET_COEX_RESP_BT_SUPP_FEAT(payload)				\
	le64_get_bits(*((__le64 *)(payload)), GENMASK_ULL(39, 24))
#घोषणा GET_COEX_RESP_BT_PATCH_VER(payload)				\
	le64_get_bits(*((__le64 *)(payload)), GENMASK_ULL(55, 24))
#घोषणा GET_COEX_RESP_BT_REG_VAL(payload)				\
	le64_get_bits(*((__le64 *)(payload)), GENMASK_ULL(39, 24))
#घोषणा GET_COEX_RESP_BT_SCAN_TYPE(payload)				\
	le64_get_bits(*((__le64 *)(payload)), GENMASK(31, 24))

क्रमागत coex_mp_info_op अणु
	BT_MP_INFO_OP_PATCH_VER	= 0x00,
	BT_MP_INFO_OP_READ_REG	= 0x11,
	BT_MP_INFO_OP_SUPP_FEAT	= 0x2a,
	BT_MP_INFO_OP_SUPP_VER	= 0x2b,
	BT_MP_INFO_OP_SCAN_TYPE	= 0x2d,
	BT_MP_INFO_OP_LNA_CONSTRAINT	= 0x32,
पूर्ण;

क्रमागत coex_set_ant_phase अणु
	COEX_SET_ANT_INIT,
	COEX_SET_ANT_WONLY,
	COEX_SET_ANT_WOFF,
	COEX_SET_ANT_2G,
	COEX_SET_ANT_5G,
	COEX_SET_ANT_POWERON,
	COEX_SET_ANT_2G_WLBT,
	COEX_SET_ANT_2G_FREERUN,

	COEX_SET_ANT_MAX
पूर्ण;

क्रमागत coex_runreason अणु
	COEX_RSN_2GSCANSTART	= 0,
	COEX_RSN_5GSCANSTART	= 1,
	COEX_RSN_SCANFINISH	= 2,
	COEX_RSN_2GSWITCHBAND	= 3,
	COEX_RSN_5GSWITCHBAND	= 4,
	COEX_RSN_2GCONSTART	= 5,
	COEX_RSN_5GCONSTART	= 6,
	COEX_RSN_2GCONFINISH	= 7,
	COEX_RSN_5GCONFINISH	= 8,
	COEX_RSN_2GMEDIA	= 9,
	COEX_RSN_5GMEDIA	= 10,
	COEX_RSN_MEDIADISCON	= 11,
	COEX_RSN_BTINFO		= 12,
	COEX_RSN_LPS		= 13,
	COEX_RSN_WLSTATUS	= 14,
	COEX_RSN_BTSTATUS	= 15,

	COEX_RSN_MAX
पूर्ण;

क्रमागत coex_lte_coex_table_type अणु
	COEX_CTT_WL_VS_LTE,
	COEX_CTT_BT_VS_LTE,
पूर्ण;

क्रमागत coex_gnt_setup_state अणु
	COEX_GNT_SET_HW_PTA	= 0x0,
	COEX_GNT_SET_SW_LOW	= 0x1,
	COEX_GNT_SET_SW_HIGH	= 0x3,
पूर्ण;

क्रमागत coex_ext_ant_चयन_pos_type अणु
	COEX_SWITCH_TO_BT,
	COEX_SWITCH_TO_WLG,
	COEX_SWITCH_TO_WLA,
	COEX_SWITCH_TO_NOCARE,
	COEX_SWITCH_TO_WLG_BT,

	COEX_SWITCH_TO_MAX
पूर्ण;

क्रमागत coex_ext_ant_चयन_ctrl_type अणु
	COEX_SWITCH_CTRL_BY_BBSW,
	COEX_SWITCH_CTRL_BY_PTA,
	COEX_SWITCH_CTRL_BY_ANTDIV,
	COEX_SWITCH_CTRL_BY_MAC,
	COEX_SWITCH_CTRL_BY_BT,
	COEX_SWITCH_CTRL_BY_FW,

	COEX_SWITCH_CTRL_MAX
पूर्ण;

क्रमागत coex_algorithm अणु
	COEX_ALGO_NOPROखाता	= 0,
	COEX_ALGO_HFP		= 1,
	COEX_ALGO_HID		= 2,
	COEX_ALGO_A2DP		= 3,
	COEX_ALGO_PAN		= 4,
	COEX_ALGO_A2DP_HID	= 5,
	COEX_ALGO_A2DP_PAN	= 6,
	COEX_ALGO_PAN_HID	= 7,
	COEX_ALGO_A2DP_PAN_HID	= 8,

	COEX_ALGO_MAX
पूर्ण;

क्रमागत coex_bt_profile अणु
	BPM_NOPROखाता		= 0,
	BPM_HFP			= BIT(0),
	BPM_HID			= BIT(1),
	BPM_A2DP		= BIT(2),
	BPM_PAN			= BIT(3),
	BPM_HID_HFP		= BPM_HID | BPM_HFP,
	BPM_A2DP_HFP		= BPM_A2DP | BPM_HFP,
	BPM_A2DP_HID		= BPM_A2DP | BPM_HID,
	BPM_A2DP_HID_HFP	= BPM_A2DP | BPM_HID | BPM_HFP,
	BPM_PAN_HFP		= BPM_PAN | BPM_HFP,
	BPM_PAN_HID		= BPM_PAN | BPM_HID,
	BPM_PAN_HID_HFP		= BPM_PAN | BPM_HID | BPM_HFP,
	BPM_PAN_A2DP		= BPM_PAN | BPM_A2DP,
	BPM_PAN_A2DP_HFP	= BPM_PAN | BPM_A2DP | BPM_HFP,
	BPM_PAN_A2DP_HID	= BPM_PAN | BPM_A2DP | BPM_HID,
	BPM_PAN_A2DP_HID_HFP	= BPM_PAN | BPM_A2DP | BPM_HID | BPM_HFP,
पूर्ण;

क्रमागत coex_wl_link_mode अणु
	COEX_WLINK_2G1PORT	= 0x0,
	COEX_WLINK_5G		= 0x3,
	COEX_WLINK_MAX
पूर्ण;

क्रमागत coex_wl2bt_scoreboard अणु
	COEX_SCBD_ACTIVE	= BIT(0),
	COEX_SCBD_ONOFF		= BIT(1),
	COEX_SCBD_SCAN		= BIT(2),
	COEX_SCBD_UNDERTEST	= BIT(3),
	COEX_SCBD_RXGAIN	= BIT(4),
	COEX_SCBD_BT_RFK	= BIT(5),
	COEX_SCBD_WLBUSY	= BIT(6),
	COEX_SCBD_EXTFEM	= BIT(8),
	COEX_SCBD_TDMA		= BIT(9),
	COEX_SCBD_FIX2M		= BIT(10),
	COEX_SCBD_ALL		= GENMASK(15, 0),
पूर्ण;

क्रमागत coex_घातer_save_type अणु
	COEX_PS_WIFI_NATIVE	= 0,
	COEX_PS_LPS_ON		= 1,
	COEX_PS_LPS_OFF		= 2,
पूर्ण;

क्रमागत coex_rssi_state अणु
	COEX_RSSI_STATE_HIGH,
	COEX_RSSI_STATE_MEDIUM,
	COEX_RSSI_STATE_LOW,
	COEX_RSSI_STATE_STAY_HIGH,
	COEX_RSSI_STATE_STAY_MEDIUM,
	COEX_RSSI_STATE_STAY_LOW,
पूर्ण;

क्रमागत coex_notअगरy_type_ips अणु
	COEX_IPS_LEAVE		= 0x0,
	COEX_IPS_ENTER		= 0x1,
पूर्ण;

क्रमागत coex_notअगरy_type_lps अणु
	COEX_LPS_DISABLE	= 0x0,
	COEX_LPS_ENABLE		= 0x1,
पूर्ण;

क्रमागत coex_notअगरy_type_scan अणु
	COEX_SCAN_FINISH,
	COEX_SCAN_START,
	COEX_SCAN_START_2G,
	COEX_SCAN_START_5G,
पूर्ण;

क्रमागत coex_notअगरy_type_चयनband अणु
	COEX_NOT_SWITCH,
	COEX_SWITCH_TO_24G,
	COEX_SWITCH_TO_5G,
	COEX_SWITCH_TO_24G_NOFORSCAN,
पूर्ण;

क्रमागत coex_notअगरy_type_associate अणु
	COEX_ASSOCIATE_FINISH,
	COEX_ASSOCIATE_START,
	COEX_ASSOCIATE_5G_FINISH,
	COEX_ASSOCIATE_5G_START,
पूर्ण;

क्रमागत coex_notअगरy_type_media_status अणु
	COEX_MEDIA_DISCONNECT,
	COEX_MEDIA_CONNECT,
	COEX_MEDIA_CONNECT_5G,
पूर्ण;

क्रमागत coex_bt_status अणु
	COEX_BTSTATUS_NCON_IDLE		= 0,
	COEX_BTSTATUS_CON_IDLE		= 1,
	COEX_BTSTATUS_INQ_PAGE		= 2,
	COEX_BTSTATUS_ACL_BUSY		= 3,
	COEX_BTSTATUS_SCO_BUSY		= 4,
	COEX_BTSTATUS_ACL_SCO_BUSY	= 5,

	COEX_BTSTATUS_MAX
पूर्ण;

क्रमागत coex_wl_tput_dir अणु
	COEX_WL_TPUT_TX			= 0x0,
	COEX_WL_TPUT_RX			= 0x1,
	COEX_WL_TPUT_MAX
पूर्ण;

क्रमागत coex_wl_priority_mask अणु
	COEX_WLPRI_RX_RSP	= 2,
	COEX_WLPRI_TX_RSP	= 3,
	COEX_WLPRI_TX_BEACON	= 4,
	COEX_WLPRI_TX_OFDM	= 11,
	COEX_WLPRI_TX_CCK	= 12,
	COEX_WLPRI_TX_BEACONQ	= 27,
	COEX_WLPRI_RX_CCK	= 28,
	COEX_WLPRI_RX_OFDM	= 29,
	COEX_WLPRI_MAX
पूर्ण;

क्रमागत coex_commom_chip_setup अणु
	COEX_CSETUP_INIT_HW		= 0x0,
	COEX_CSETUP_ANT_SWITCH		= 0x1,
	COEX_CSETUP_GNT_FIX		= 0x2,
	COEX_CSETUP_GNT_DEBUG		= 0x3,
	COEX_CSETUP_RFE_TYPE		= 0x4,
	COEX_CSETUP_COEXINFO_HW		= 0x5,
	COEX_CSETUP_WL_TX_POWER		= 0x6,
	COEX_CSETUP_WL_RX_GAIN		= 0x7,
	COEX_CSETUP_WLAN_ACT_IPS	= 0x8,
	COEX_CSETUP_MAX
पूर्ण;

क्रमागत coex_indirect_reg_type अणु
	COEX_INसूचीECT_1700		= 0x0,
	COEX_INसूचीECT_7C0		= 0x1,
	COEX_INसूचीECT_MAX
पूर्ण;

क्रमागत coex_pstdma_type अणु
	COEX_PSTDMA_FORCE_LPSOFF	= 0x0,
	COEX_PSTDMA_FORCE_LPSON		= 0x1,
	COEX_PSTDMA_MAX
पूर्ण;

क्रमागत coex_btrssi_type अणु
	COEX_BTRSSI_RATIO		= 0x0,
	COEX_BTRSSI_DBM			= 0x1,
	COEX_BTRSSI_MAX
पूर्ण;

काष्ठा coex_table_para अणु
	u32 bt;
	u32 wl;
पूर्ण;

काष्ठा coex_tdma_para अणु
	u8 para[5];
पूर्ण;

काष्ठा coex_5g_afh_map अणु
	u32 wl_5g_ch;
	u8 bt_skip_ch;
	u8 bt_skip_span;
पूर्ण;

काष्ठा coex_rf_para अणु
	u8 wl_pwr_dec_lvl;
	u8 bt_pwr_dec_lvl;
	bool wl_low_gain_en;
	u8 bt_lna_lvl;
पूर्ण;

अटल अंतरभूत व्योम rtw_coex_set_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_init(rtwdev);
पूर्ण

अटल अंतरभूत
व्योम rtw_coex_set_ant_चयन(काष्ठा rtw_dev *rtwdev, u8 ctrl_type, u8 pos_type)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	अगर (!chip->ops->coex_set_ant_चयन)
		वापस;

	chip->ops->coex_set_ant_चयन(rtwdev, ctrl_type, pos_type);
पूर्ण

अटल अंतरभूत व्योम rtw_coex_set_gnt_fix(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_gnt_fix(rtwdev);
पूर्ण

अटल अंतरभूत व्योम rtw_coex_set_gnt_debug(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_gnt_debug(rtwdev);
पूर्ण

अटल अंतरभूत  व्योम rtw_coex_set_rfe_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_rfe_type(rtwdev);
पूर्ण

अटल अंतरभूत व्योम rtw_coex_set_wl_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 wl_pwr)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_wl_tx_घातer(rtwdev, wl_pwr);
पूर्ण

अटल अंतरभूत
व्योम rtw_coex_set_wl_rx_gain(काष्ठा rtw_dev *rtwdev, bool low_gain)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	chip->ops->coex_set_wl_rx_gain(rtwdev, low_gain);
पूर्ण

व्योम rtw_coex_info_response(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb);
u32 rtw_coex_पढ़ो_indirect_reg(काष्ठा rtw_dev *rtwdev, u16 addr);
व्योम rtw_coex_ग_लिखो_indirect_reg(काष्ठा rtw_dev *rtwdev, u16 addr,
				 u32 mask, u32 val);
व्योम rtw_coex_ग_लिखो_scbd(काष्ठा rtw_dev *rtwdev, u16 bitpos, bool set);

व्योम rtw_coex_bt_relink_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_bt_reenable_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_deमुक्तze_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_wl_reमुख्य_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_bt_reमुख्य_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_wl_connecting_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_bt_multi_link_reमुख्य_work(काष्ठा work_काष्ठा *work);
व्योम rtw_coex_wl_ccklock_work(काष्ठा work_काष्ठा *work);

व्योम rtw_coex_घातer_on_setting(काष्ठा rtw_dev *rtwdev);
व्योम rtw_coex_घातer_off_setting(काष्ठा rtw_dev *rtwdev);
व्योम rtw_coex_init_hw_config(काष्ठा rtw_dev *rtwdev, bool wअगरi_only);
व्योम rtw_coex_ips_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_lps_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_scan_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_connect_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_media_status_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_bt_info_notअगरy(काष्ठा rtw_dev *rtwdev, u8 *buf, u8 length);
व्योम rtw_coex_wl_fwdbginfo_notअगरy(काष्ठा rtw_dev *rtwdev, u8 *buf, u8 length);
व्योम rtw_coex_चयनband_notअगरy(काष्ठा rtw_dev *rtwdev, u8 type);
व्योम rtw_coex_wl_status_change_notअगरy(काष्ठा rtw_dev *rtwdev, u32 type);
व्योम rtw_coex_display_coex_info(काष्ठा rtw_dev *rtwdev, काष्ठा seq_file *m);

अटल अंतरभूत bool rtw_coex_disabled(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;

	वापस coex_stat->bt_disabled;
पूर्ण

#पूर्ण_अगर

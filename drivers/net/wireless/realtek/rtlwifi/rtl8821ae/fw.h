<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#अगर_अघोषित __RTL8821AE__FW__H__
#घोषणा __RTL8821AE__FW__H__
#समावेश "def.h"

#घोषणा FW_8821AE_SIZE					0x8000
#घोषणा FW_8821AE_START_ADDRESS			0x1000
#घोषणा FW_8821AE_END_ADDRESS			0x5FFF
#घोषणा FW_8821AE_PAGE_SIZE				4096
#घोषणा FW_8821AE_POLLING_DELAY			5
#घोषणा FW_8821AE_POLLING_TIMEOUT_COUNT	6000

#घोषणा IS_FW_HEADER_EXIST_8812(_pfwhdr)	\
	((le16_to_cpu(_pfwhdr->signature) & 0xFFF0) == 0x9500)

#घोषणा IS_FW_HEADER_EXIST_8821(_pfwhdr)	\
	((le16_to_cpu(_pfwhdr->signature) & 0xFFF0) == 0x2100)

#घोषणा USE_OLD_WOWLAN_DEBUG_FW 0

#घोषणा H2C_8821AE_RSVDPAGE_LOC_LEN		5
#घोषणा H2C_8821AE_PWEMODE_LENGTH			7
#घोषणा H2C_8821AE_JOINBSSRPT_LENGTH		1
#घोषणा H2C_8821AE_AP_OFFLOAD_LENGTH		3
#घोषणा H2C_8821AE_WOWLAN_LENGTH			3
#घोषणा H2C_8821AE_KEEP_ALIVE_CTRL_LENGTH	3
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 0)
#घोषणा H2C_8821AE_REMOTE_WAKE_CTRL_LEN	1
#अन्यथा
#घोषणा H2C_8821AE_REMOTE_WAKE_CTRL_LEN	3
#पूर्ण_अगर
#घोषणा H2C_8821AE_AOAC_GLOBAL_INFO_LEN	2
#घोषणा H2C_8821AE_AOAC_RSVDPAGE_LOC_LEN	7
#घोषणा H2C_8821AE_DISCONNECT_DECISION_CTRL_LEN	3

/* Fw PS state क्रम RPWM.
*BIT[2:0] = HW state

*BIT[3] = Protocol PS state,
1: रेजिस्टर active state ,
0: रेजिस्टर sleep state

*BIT[4] = sub-state
*/
#घोषणा	FW_PS_GO_ON			BIT(0)
#घोषणा	FW_PS_TX_शून्य			BIT(1)
#घोषणा	FW_PS_RF_ON			BIT(2)
#घोषणा	FW_PS_REGISTER_ACTIVE	BIT(3)

#घोषणा	FW_PS_DPS		BIT(0)
#घोषणा	FW_PS_LCLK		(FW_PS_DPS)
#घोषणा	FW_PS_RF_OFF		BIT(1)
#घोषणा	FW_PS_ALL_ON		BIT(2)
#घोषणा	FW_PS_ST_ACTIVE		BIT(3)
#घोषणा	FW_PS_ISR_ENABLE	BIT(4)
#घोषणा	FW_PS_IMR_ENABLE	BIT(5)

#घोषणा	FW_PS_ACK		BIT(6)
#घोषणा	FW_PS_TOGGLE		BIT(7)

 /* 8821AE RPWM value*/
 /* BIT[0] = 1: 32k, 0: 40M*/
 /* 32k*/
#घोषणा	FW_PS_CLOCK_OFF		BIT(0)
/*40M*/
#घोषणा	FW_PS_CLOCK_ON		0

#घोषणा	FW_PS_STATE_MASK		(0x0F)
#घोषणा	FW_PS_STATE_HW_MASK	(0x07)
/*ISR_ENABLE, IMR_ENABLE, and PS mode should be inherited.*/
#घोषणा	FW_PS_STATE_INT_MASK	(0x3F)

#घोषणा	FW_PS_STATE(x)			(FW_PS_STATE_MASK & (x))
#घोषणा	FW_PS_STATE_HW(x)		(FW_PS_STATE_HW_MASK & (x))
#घोषणा	FW_PS_STATE_INT(x)	(FW_PS_STATE_INT_MASK & (x))
#घोषणा	FW_PS_ISR_VAL(x)		((x) & 0x70)
#घोषणा	FW_PS_IMR_MASK(x)	((x) & 0xDF)
#घोषणा	FW_PS_KEEP_IMR(x)		((x) & 0x20)

#घोषणा	FW_PS_STATE_S0		(FW_PS_DPS)
#घोषणा	FW_PS_STATE_S1		(FW_PS_LCLK)
#घोषणा	FW_PS_STATE_S2		(FW_PS_RF_OFF)
#घोषणा	FW_PS_STATE_S3		(FW_PS_ALL_ON)
#घोषणा	FW_PS_STATE_S4		((FW_PS_ST_ACTIVE) | (FW_PS_ALL_ON))
 /* ((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))*/
#घोषणा	FW_PS_STATE_ALL_ON_8821AE	(FW_PS_CLOCK_ON)
 /* (FW_PS_RF_ON)*/
#घोषणा	FW_PS_STATE_RF_ON_8821AE	(FW_PS_CLOCK_ON)
 /* 0x0*/
#घोषणा	FW_PS_STATE_RF_OFF_8821AE	(FW_PS_CLOCK_ON)
 /* (FW_PS_STATE_RF_OFF)*/
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR_8821AE	(FW_PS_CLOCK_OFF)

#घोषणा	FW_PS_STATE_ALL_ON_92C	(FW_PS_STATE_S4)
#घोषणा	FW_PS_STATE_RF_ON_92C		(FW_PS_STATE_S3)
#घोषणा	FW_PS_STATE_RF_OFF_92C	(FW_PS_STATE_S2)
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR_92C	(FW_PS_STATE_S1)

/* For 8821AE H2C PwrMode Cmd ID 5.*/
#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

#घोषणा	FW_PS_IS_ACK(x)		((x) & FW_PS_ACK)
#घोषणा	FW_PS_IS_CLK_ON(x)	((x) & (FW_PS_RF_OFF | FW_PS_ALL_ON))
#घोषणा	FW_PS_IS_RF_ON(x)	((x) & (FW_PS_ALL_ON))
#घोषणा	FW_PS_IS_ACTIVE(x)	((x) & (FW_PS_ST_ACTIVE))
#घोषणा	FW_PS_IS_CPWM_INT(x)	((x) & 0x40)

#घोषणा	FW_CLR_PS_STATE(x)	((x) = ((x) & (0xF0)))

#घोषणा	IS_IN_LOW_POWER_STATE_8821AE(__state)		\
			(FW_PS_STATE(__state) == FW_PS_CLOCK_OFF)

#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

क्रमागत rtl8821a_h2c_cmd अणु
	H2C_8821AE_RSVDPAGE = 0,
	H2C_8821AE_MSRRPT = 1,
	H2C_8821AE_SCAN = 2,
	H2C_8821AE_KEEP_ALIVE_CTRL = 3,
	H2C_8821AE_DISCONNECT_DECISION = 4,
	H2C_8821AE_INIT_OFFLOAD = 6,
	H2C_8821AE_AP_OFFLOAD = 8,
	H2C_8821AE_BCN_RSVDPAGE = 9,
	H2C_8821AE_PROBERSP_RSVDPAGE = 10,

	H2C_8821AE_SETPWRMODE = 0x20,
	H2C_8821AE_PS_TUNING_PARA = 0x21,
	H2C_8821AE_PS_TUNING_PARA2 = 0x22,
	H2C_8821AE_PS_LPS_PARA = 0x23,
	H2C_8821AE_P2P_PS_OFFLOAD = 024,

	H2C_8821AE_WO_WLAN = 0x80,
	H2C_8821AE_REMOTE_WAKE_CTRL = 0x81,
	H2C_8821AE_AOAC_GLOBAL_INFO = 0x82,
	H2C_8821AE_AOAC_RSVDPAGE = 0x83,

	H2C_RSSI_21AE_REPORT = 0x42,
	H2C_8821AE_RA_MASK = 0x40,
	H2C_8821AE_SELECTIVE_SUSPEND_ROF_CMD,
	H2C_8821AE_P2P_PS_MODE,
	H2C_8821AE_PSD_RESULT,
	/*Not defined CTW CMD क्रम P2P yet*/
	H2C_8821AE_P2P_PS_CTW_CMD,
	MAX_8821AE_H2CCMD
पूर्ण;

#घोषणा pagक्रमागत_128(_len)	(u32)(((_len)>>7) + ((_len)&0x7F ? 1 : 0))

#घोषणा SET_8812_H2CCMD_WOWLAN_FUNC_ENABLE(__cmd, __value)		\
	u8p_replace_bits(__cmd, __value, BIT(0))
#घोषणा SET_8812_H2CCMD_WOWLAN_PATTERN_MATCH_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(1))
#घोषणा SET_8812_H2CCMD_WOWLAN_MAGIC_PKT_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(2))
#घोषणा SET_8812_H2CCMD_WOWLAN_UNICAST_PKT_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(3))
#घोषणा SET_8812_H2CCMD_WOWLAN_ALL_PKT_DROP(__cmd, __value)		\
	u8p_replace_bits(__cmd, __value, BIT(4))
#घोषणा SET_8812_H2CCMD_WOWLAN_GPIO_ACTIVE(__cmd, __value)		\
	u8p_replace_bits(__cmd, __value, BIT(5))
#घोषणा SET_8812_H2CCMD_WOWLAN_REKEY_WAKE_UP(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(6))
#घोषणा SET_8812_H2CCMD_WOWLAN_DISCONNECT_WAKE_UP(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(7))
#घोषणा SET_8812_H2CCMD_WOWLAN_GPIONUM(__cmd, __value)		\
	*(u8 *)(__cmd + 1) = __value
#घोषणा SET_8812_H2CCMD_WOWLAN_GPIO_DURATION(__cmd, __value)	\
	*(u8 *)(__cmd + 2) = __value

#घोषणा SET_H2CCMD_PWRMODE_PARM_MODE(__ph2ccmd, __val)			\
	*(u8 *)__ph2ccmd = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_RLBM(__cmd, __value)		\
	u8p_replace_bits(__cmd + 1, __value, GENMASK(3, 0))
#घोषणा SET_H2CCMD_PWRMODE_PARM_SMART_PS(__cmd, __value)	\
	u8p_replace_bits(__cmd + 1, __value, GENMASK(7, 4))
#घोषणा SET_H2CCMD_PWRMODE_PARM_AWAKE_INTERVAL(__cmd, __value)	\
	*(u8 *)(__cmd + 2) = __value
#घोषणा SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(__cmd, __value)		\
	*(u8 *)(__cmd + 3) = __value
#घोषणा SET_H2CCMD_PWRMODE_PARM_PWR_STATE(__cmd, __value)	\
	*(u8 *)(__cmd + 4) = __value
#घोषणा SET_H2CCMD_PWRMODE_PARM_BYTE5(__cmd, __value)		\
	*(u8 *)(__cmd + 5) = __value

#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_QOS_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 3) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_शून्य_DATA(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 4) = __val

/* _MEDIA_STATUS_RPT_PARM_CMD1 */
#घोषणा SET_H2CCMD_MSRRPT_PARM_OPMODE(__cmd, __value)	\
	u8p_replace_bits(__cmd + 1, __value, BIT(0))
#घोषणा SET_H2CCMD_MSRRPT_PARM_MACID_IND(__cmd, __value)	\
	u8p_replace_bits(__cmd + 1, __value, BIT(1))

/* AP_OFFLOAD */
#घोषणा SET_H2CCMD_AP_OFFLOAD_ON(__cmd, __value)	\
	*(u8 *)__cmd = __value
#घोषणा SET_H2CCMD_AP_OFFLOAD_HIDDEN(__cmd, __value)	\
	*(u8 *)(__cmd + 1) = __value
#घोषणा SET_H2CCMD_AP_OFFLOAD_DENYANY(__cmd, __value)	\
	*(u8 *)(__cmd + 2) = __value
#घोषणा SET_H2CCMD_AP_OFFLOAD_WAKEUP_EVT_RPT(__cmd, __value) \
	*(u8 *)(__cmd + 3) = __value

/* Keep Alive Control*/
#घोषणा SET_8812_H2CCMD_KEEP_ALIVE_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(0))
#घोषणा SET_8812_H2CCMD_KEEP_ALIVE_ACCPEPT_USER_DEFINED(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(1))
#घोषणा SET_8812_H2CCMD_KEEP_ALIVE_PERIOD(__cmd, __value)	\
	*(u8 *)(__cmd + 1) = __value

/*REMOTE_WAKE_CTRL */
#घोषणा SET_8812_H2CCMD_REMOTE_WAKECTRL_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(0))
#घोषणा SET_8812_H2CCMD_REMOTE_WAKE_CTRL_ARP_OFFLOAD_EN(__cmd, __value)\
	u8p_replace_bits(__cmd, __value, BIT(1))
#घोषणा SET_8812_H2CCMD_REMOTE_WAKE_CTRL_NDP_OFFLOAD_EN(__cmd, __value)\
	u8p_replace_bits(__cmd, __value, BIT(2))
#घोषणा SET_8812_H2CCMD_REMOTE_WAKE_CTRL_GTK_OFFLOAD_EN(__cmd, __value)\
	u8p_replace_bits(__cmd, __value, BIT(3))
#घोषणा SET_8812_H2CCMD_REMOTE_WAKE_CTRL_REALWOWV2_EN(__cmd, __value)\
	u8p_replace_bits(__cmd, __value, BIT(6))

/* GTK_OFFLOAD */
#घोषणा SET_8812_H2CCMD_AOAC_GLOBAL_INFO_PAIRWISE_ENC_ALG(__cmd, __value)\
	*(u8 *)__cmd = __value
#घोषणा SET_8812_H2CCMD_AOAC_GLOBAL_INFO_GROUP_ENC_ALG(__cmd, __value)	\
	*(u8 *)(__cmd + 1) = __value

/* AOAC_RSVDPAGE_LOC */
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_REMOTE_WAKE_CTRL_INFO(__cmd, __value)	\
	*(u8 *)__cmd = __value
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_ARP_RSP(__cmd, __value)	\
	*(u8 *)(__cmd + 1) = __value
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_NEIGHBOR_ADV(__cmd, __value)\
	*(u8 *)(__cmd + 2) = __value
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_RSP(__cmd, __value)	\
	*(u8 *)(__cmd + 3) = __value
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_INFO(__cmd, __value)	\
	*(u8 *)(__cmd + 4) = __value
#घोषणा SET_8821AE_H2CCMD_AOAC_RSVDPAGE_LOC_GTK_EXT_MEM(__cmd, __value)	\
	*(u8 *)(__cmd + 5) = __value

/* Disconnect_Decision_Control */
#घोषणा SET_8812_H2CCMD_DISCONNECT_DECISION_CTRL_ENABLE(__cmd, __value)	\
	u8p_replace_bits(__cmd, __value, BIT(0))
#घोषणा SET_8812_H2CCMD_DISCONNECT_DECISION_CTRL_USER_SETTING(__cmd, __value)\
	u8p_replace_bits(__cmd, __value, BIT(1))
#घोषणा SET_8812_H2CCMD_DISCONNECT_DECISION_CTRL_CHECK_PERIOD(__cmd, __value)\
	*(u8 *)(__cmd + 1) = __value
#घोषणा SET_8812_H2CCMD_DISCONNECT_DECISION_CTRL_TRYPKT_NUM(__cmd, __value)\
	*(u8 *)(__cmd + 2) = __value

पूर्णांक rtl8821ae_करोwnload_fw(काष्ठा ieee80211_hw *hw, bool buse_wake_on_wlan_fw);
#अगर (USE_SPECIFIC_FW_TO_SUPPORT_WOWLAN == 1)
व्योम rtl8821ae_set_fw_related_क्रम_wowlan(काष्ठा ieee80211_hw *hw,
					 bool used_wowlan_fw);

#पूर्ण_अगर
व्योम rtl8821ae_fill_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 element_id,
			    u32 cmd_len, u8 *cmdbuffer);
व्योम rtl8821ae_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl8821ae_set_fw_media_status_rpt_cmd(काष्ठा ieee80211_hw *hw,
					   u8 mstatus);
व्योम rtl8821ae_set_fw_ap_off_load_cmd(काष्ठा ieee80211_hw *hw,
				      u8 ap_offload_enable);
व्योम rtl8821ae_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw,
				  bool b_dl_finished, bool dl_whole_packet);
व्योम rtl8812ae_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw,
				  bool b_dl_finished, bool dl_whole_packet);
व्योम rtl8821ae_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw,
				      u8 p2p_ps_state);
व्योम rtl8821ae_set_fw_wowlan_mode(काष्ठा ieee80211_hw *hw, bool func_en);
व्योम rtl8821ae_set_fw_remote_wake_ctrl_cmd(काष्ठा ieee80211_hw *hw,
					   u8 enable);
व्योम rtl8821ae_set_fw_keep_alive_cmd(काष्ठा ieee80211_hw *hw, bool func_en);
व्योम rtl8821ae_set_fw_disconnect_decision_ctrl_cmd(काष्ठा ieee80211_hw *hw,
						   bool enabled);
व्योम rtl8821ae_set_fw_global_info_cmd(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_c2h_ra_report_handler(काष्ठा ieee80211_hw *hw,
				     u8 *cmd_buf, u8 cmd_len);
#पूर्ण_अगर

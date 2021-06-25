<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL92E__FW__H__
#घोषणा __RTL92E__FW__H__

#घोषणा FW_8192C_SIZE				0x8000
#घोषणा FW_8192C_START_ADDRESS			0x1000
#घोषणा FW_8192C_END_ADDRESS			0x5FFF
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8192C_POLLING_DELAY			5
#घोषणा FW_8192C_POLLING_TIMEOUT_COUNT		3000

#घोषणा IS_FW_HEADER_EXIST(_pfwhdr)	\
	((le16_to_cpu(_pfwhdr->signature) & 0xFFF0) == 0x92E0)
#घोषणा USE_OLD_WOWLAN_DEBUG_FW 0

#घोषणा H2C_92E_RSVDPAGE_LOC_LEN		5
#घोषणा H2C_92E_PWEMODE_LENGTH			7
#घोषणा H2C_92E_JOINBSSRPT_LENGTH		1
#घोषणा H2C_92E_AP_OFFLOAD_LENGTH		3
#घोषणा H2C_92E_WOWLAN_LENGTH			3
#घोषणा H2C_92E_KEEP_ALIVE_CTRL_LENGTH		3
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 0)
#घोषणा H2C_92E_REMOTE_WAKE_CTRL_LEN		1
#अन्यथा
#घोषणा H2C_92E_REMOTE_WAKE_CTRL_LEN		3
#पूर्ण_अगर
#घोषणा H2C_92E_AOAC_GLOBAL_INFO_LEN		2
#घोषणा H2C_92E_AOAC_RSVDPAGE_LOC_LEN		7

/* Fw PS state क्रम RPWM.
*BIT[2:0] = HW state
*BIT[3] = Protocol PS state,  1: रेजिस्टर active state, 0: रेजिस्टर sleep state
*BIT[4] = sub-state
*/
#घोषणा	FW_PS_RF_ON		BIT(2)
#घोषणा	FW_PS_REGISTER_ACTIVE	BIT(3)

#घोषणा	FW_PS_ACK		BIT(6)
#घोषणा	FW_PS_TOGGLE		BIT(7)

 /* 92E RPWM value*/
 /* BIT[0] = 1: 32k, 0: 40M*/
#घोषणा	FW_PS_CLOCK_OFF		BIT(0)		/* 32k */
#घोषणा	FW_PS_CLOCK_ON		0		/* 40M */

#घोषणा	FW_PS_STATE_MASK		(0x0F)
#घोषणा	FW_PS_STATE_HW_MASK		(0x07)
#घोषणा	FW_PS_STATE_INT_MASK		(0x3F)

#घोषणा	FW_PS_STATE(x)			(FW_PS_STATE_MASK & (x))

#घोषणा	FW_PS_STATE_ALL_ON_92E		(FW_PS_CLOCK_ON)
#घोषणा	FW_PS_STATE_RF_ON_92E		(FW_PS_CLOCK_ON)
#घोषणा	FW_PS_STATE_RF_OFF_92E		(FW_PS_CLOCK_ON)
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR	(FW_PS_CLOCK_OFF)

/* For 92E H2C PwrMode Cmd ID 5.*/
#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

#घोषणा	FW_PS_IS_ACK(x)		((x) & FW_PS_ACK)

#घोषणा	IS_IN_LOW_POWER_STATE_92E(__state)		\
	(FW_PS_STATE(__state) == FW_PS_CLOCK_OFF)

#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

क्रमागत rtl8192e_h2c_cmd अणु
	H2C_92E_RSVDPAGE = 0,
	H2C_92E_MSRRPT = 1,
	H2C_92E_SCAN = 2,
	H2C_92E_KEEP_ALIVE_CTRL = 3,
	H2C_92E_DISCONNECT_DECISION = 4,
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 1)
	H2C_92E_WO_WLAN = 5,
#पूर्ण_अगर
	H2C_92E_INIT_OFFLOAD = 6,
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 1)
	H2C_92E_REMOTE_WAKE_CTRL = 7,
#पूर्ण_अगर
	H2C_92E_AP_OFFLOAD = 8,
	H2C_92E_BCN_RSVDPAGE = 9,
	H2C_92E_PROBERSP_RSVDPAGE = 10,

	H2C_92E_SETPWRMODE = 0x20,
	H2C_92E_PS_TUNING_PARA = 0x21,
	H2C_92E_PS_TUNING_PARA2 = 0x22,
	H2C_92E_PS_LPS_PARA = 0x23,
	H2C_92E_P2P_PS_OFFLOAD = 024,

#अगर (USE_OLD_WOWLAN_DEBUG_FW == 0)
	H2C_92E_WO_WLAN = 0x80,
	H2C_92E_REMOTE_WAKE_CTRL = 0x81,
	H2C_92E_AOAC_GLOBAL_INFO = 0x82,
	H2C_92E_AOAC_RSVDPAGE = 0x83,
#पूर्ण_अगर
	H2C_92E_RA_MASK = 0x40,
	H2C_92E_RSSI_REPORT = 0x42,
	H2C_92E_SELECTIVE_SUSPEND_ROF_CMD,
	H2C_92E_P2P_PS_MODE,
	H2C_92E_PSD_RESULT,
	/*Not defined CTW CMD क्रम P2P yet*/
	H2C_92E_P2P_PS_CTW_CMD,
	MAX_92E_H2CCMD
पूर्ण;

#घोषणा pagक्रमागत_128(_len)	\
	(u32)(((_len) >> 7) + ((_len) & 0x7F ? 1 : 0))

#घोषणा SET_H2CCMD_PWRMODE_PARM_MODE(__ph2ccmd, __val)			\
	*(u8 *)__ph2ccmd = __val;
#घोषणा SET_H2CCMD_PWRMODE_PARM_RLBM(__cmd, __val)			\
	u8p_replace_bits(__cmd + 1, __val, GENMASK(3, 0))
#घोषणा SET_H2CCMD_PWRMODE_PARM_SMART_PS(__cmd, __val)		\
	u8p_replace_bits(__cmd + 1, __val, GENMASK(7, 4))
#घोषणा SET_H2CCMD_PWRMODE_PARM_AWAKE_INTERVAL(__cmd, __val)	\
	*(u8 *)(__cmd + 2) = __val;
#घोषणा SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(__cmd, __val)	\
	*(u8 *)(__cmd + 3) = __val;
#घोषणा SET_H2CCMD_PWRMODE_PARM_PWR_STATE(__cmd, __val)		\
	*(u8 *)(__cmd + 4) = __val;
#घोषणा SET_H2CCMD_PWRMODE_PARM_BYTE5(__cmd, __val)		\
	*(u8 *)(__cmd + 5) = __val;

#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(__ph2ccmd, __val)		\
	*(u8 *)__ph2ccmd = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_QOS_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 3) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_शून्य_DATA(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 4) = __val;

/* _MEDIA_STATUS_RPT_PARM_CMD1 */
#घोषणा SET_H2CCMD_MSRRPT_PARM_OPMODE(__cmd, __val)		\
	u8p_replace_bits(__cmd, __val, BIT(0))
#घोषणा SET_H2CCMD_MSRRPT_PARM_MACID_IND(__cmd, __val)		\
	u8p_replace_bits(__cmd, __val, BIT(1))
#घोषणा SET_H2CCMD_MSRRPT_PARM_MACID(__cmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val;
#घोषणा SET_H2CCMD_MSRRPT_PARM_MACID_END(__cmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val;

पूर्णांक rtl92ee_करोwnload_fw(काष्ठा ieee80211_hw *hw, bool buse_wake_on_wlan_fw);
व्योम rtl92ee_fill_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 element_id,
			  u32 cmd_len, u8 *cmdbuffer);
व्योम rtl92ee_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl92ee_set_fw_media_status_rpt_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus);
व्योम rtl92ee_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw, bool b_dl_finished);
व्योम rtl92ee_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state);
व्योम rtl92ee_c2h_ra_report_handler(काष्ठा ieee80211_hw *hw,
				   u8 *cmd_buf, u8 cmd_len);
#पूर्ण_अगर

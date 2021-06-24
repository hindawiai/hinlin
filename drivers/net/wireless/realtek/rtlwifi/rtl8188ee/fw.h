<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#अगर_अघोषित __RTL92C__FW__H__
#घोषणा __RTL92C__FW__H__

#घोषणा FW_8192C_SIZE				0x8000
#घोषणा FW_8192C_START_ADDRESS			0x1000
#घोषणा FW_8192C_END_ADDRESS			0x5FFF
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8192C_POLLING_DELAY			5
#घोषणा FW_8192C_POLLING_TIMEOUT_COUNT		3000

#घोषणा IS_FW_HEADER_EXIST(_pfwhdr)		\
	((le16_to_cpu(_pfwhdr->signature) & 0xFFFF) == 0x88E1)
#घोषणा USE_OLD_WOWLAN_DEBUG_FW			0

#घोषणा H2C_88E_RSVDPAGE_LOC_LEN		5
#घोषणा H2C_88E_PWEMODE_LENGTH			5
#घोषणा H2C_88E_JOINBSSRPT_LENGTH		1
#घोषणा H2C_88E_AP_OFFLOAD_LENGTH		3
#घोषणा H2C_88E_WOWLAN_LENGTH			3
#घोषणा H2C_88E_KEEP_ALIVE_CTRL_LENGTH		3
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 0)
#घोषणा H2C_88E_REMOTE_WAKE_CTRL_LEN		1
#अन्यथा
#घोषणा H2C_88E_REMOTE_WAKE_CTRL_LEN		3
#पूर्ण_अगर
#घोषणा H2C_88E_AOAC_GLOBAL_INFO_LEN		2
#घोषणा H2C_88E_AOAC_RSVDPAGE_LOC_LEN		7

/* Fw PS state क्रम RPWM.
*BIT[2:0] = HW state
*BIT[3] = Protocol PS state,
*1: रेजिस्टर active state , 0: रेजिस्टर sleep state
*BIT[4] = sub-state
*/
#घोषणा	FW_PS_GO_ON			BIT(0)
#घोषणा	FW_PS_TX_शून्य			BIT(1)
#घोषणा	FW_PS_RF_ON			BIT(2)
#घोषणा	FW_PS_REGISTER_ACTIVE		BIT(3)

#घोषणा	FW_PS_DPS			BIT(0)
#घोषणा	FW_PS_LCLK			(FW_PS_DPS)
#घोषणा	FW_PS_RF_OFF			BIT(1)
#घोषणा	FW_PS_ALL_ON			BIT(2)
#घोषणा	FW_PS_ST_ACTIVE			BIT(3)
#घोषणा	FW_PS_ISR_ENABLE		BIT(4)
#घोषणा	FW_PS_IMR_ENABLE		BIT(5)


#घोषणा	FW_PS_ACK			BIT(6)
#घोषणा	FW_PS_TOGGLE			BIT(7)

 /* 88E RPWM value*/
 /* BIT[0] = 1: 32k, 0: 40M*/
#घोषणा	FW_PS_CLOCK_OFF			BIT(0)		/* 32k*/
#घोषणा	FW_PS_CLOCK_ON			0		/*40M*/

#घोषणा	FW_PS_STATE_MASK		(0x0F)
#घोषणा	FW_PS_STATE_HW_MASK		(0x07)
/*ISR_ENABLE, IMR_ENABLE, and PS mode should be inherited.*/
#घोषणा	FW_PS_STATE_INT_MASK		(0x3F)

#घोषणा	FW_PS_STATE(x)			(FW_PS_STATE_MASK & (x))
#घोषणा	FW_PS_STATE_HW(x)		(FW_PS_STATE_HW_MASK & (x))
#घोषणा	FW_PS_STATE_INT(x)		(FW_PS_STATE_INT_MASK & (x))
#घोषणा	FW_PS_ISR_VAL(x)		((x) & 0x70)
#घोषणा	FW_PS_IMR_MASK(x)		((x) & 0xDF)
#घोषणा	FW_PS_KEEP_IMR(x)		((x) & 0x20)

#घोषणा	FW_PS_STATE_S0			(FW_PS_DPS)
#घोषणा	FW_PS_STATE_S1			(FW_PS_LCLK)
#घोषणा	FW_PS_STATE_S2			(FW_PS_RF_OFF)
#घोषणा	FW_PS_STATE_S3			(FW_PS_ALL_ON)
#घोषणा	FW_PS_STATE_S4			((FW_PS_ST_ACTIVE) | (FW_PS_ALL_ON))
/* ((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))*/
#घोषणा	FW_PS_STATE_ALL_ON_88E		(FW_PS_CLOCK_ON)
/* (FW_PS_RF_ON)*/
#घोषणा	FW_PS_STATE_RF_ON_88E		(FW_PS_CLOCK_ON)
/* 0x0*/
#घोषणा	FW_PS_STATE_RF_OFF_88E	(FW_PS_CLOCK_ON)
/* (FW_PS_STATE_RF_OFF)*/
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR_88E	(FW_PS_CLOCK_OFF)

#घोषणा	FW_PS_STATE_ALL_ON_92C		(FW_PS_STATE_S4)
#घोषणा	FW_PS_STATE_RF_ON_92C		(FW_PS_STATE_S3)
#घोषणा	FW_PS_STATE_RF_OFF_92C		(FW_PS_STATE_S2)
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR_92C	(FW_PS_STATE_S1)

/* For 88E H2C PwrMode Cmd ID 5.*/
#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF		0

#घोषणा	FW_PS_IS_ACK(x)			((x) & FW_PS_ACK)
#घोषणा	FW_PS_IS_CLK_ON(x)		((x) & (FW_PS_RF_OFF | FW_PS_ALL_ON))
#घोषणा	FW_PS_IS_RF_ON(x)		((x) & (FW_PS_ALL_ON))
#घोषणा	FW_PS_IS_ACTIVE(x)		((x) & (FW_PS_ST_ACTIVE))
#घोषणा	FW_PS_IS_CPWM_INT(x)		((x) & 0x40)

#घोषणा	FW_CLR_PS_STATE(x)		((x) = ((x) & (0xF0)))

#घोषणा	IS_IN_LOW_POWER_STATE_88E(fwpsstate)		\
	(FW_PS_STATE(fwpsstate) == FW_PS_CLOCK_OFF)

#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF		0

क्रमागत rtl8188e_h2c_cmd अणु
	H2C_88E_RSVDPAGE = 0,
	H2C_88E_JOINBSSRPT = 1,
	H2C_88E_SCAN = 2,
	H2C_88E_KEEP_ALIVE_CTRL = 3,
	H2C_88E_DISCONNECT_DECISION = 4,
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 1)
	H2C_88E_WO_WLAN = 5,
#पूर्ण_अगर
	H2C_88E_INIT_OFFLOAD = 6,
#अगर (USE_OLD_WOWLAN_DEBUG_FW == 1)
	H2C_88E_REMOTE_WAKE_CTRL = 7,
#पूर्ण_अगर
	H2C_88E_AP_OFFLOAD = 8,
	H2C_88E_BCN_RSVDPAGE = 9,
	H2C_88E_PROBERSP_RSVDPAGE = 10,

	H2C_88E_SETPWRMODE = 0x20,
	H2C_88E_PS_TUNING_PARA = 0x21,
	H2C_88E_PS_TUNING_PARA2 = 0x22,
	H2C_88E_PS_LPS_PARA = 0x23,
	H2C_88E_P2P_PS_OFFLOAD = 024,

#अगर (USE_OLD_WOWLAN_DEBUG_FW == 0)
	H2C_88E_WO_WLAN = 0x80,
	H2C_88E_REMOTE_WAKE_CTRL = 0x81,
	H2C_88E_AOAC_GLOBAL_INFO = 0x82,
	H2C_88E_AOAC_RSVDPAGE = 0x83,
#पूर्ण_अगर
	/*Not defined in new 88E H2C CMD Format*/
	H2C_88E_RA_MASK,
	H2C_88E_SELECTIVE_SUSPEND_ROF_CMD,
	H2C_88E_P2P_PS_MODE,
	H2C_88E_PSD_RESULT,
	/*Not defined CTW CMD क्रम P2P yet*/
	H2C_88E_P2P_PS_CTW_CMD,
	MAX_88E_H2CCMD
पूर्ण;

#घोषणा pagक्रमागत_128(_len)	(u32)(((_len)>>7) + ((_len)&0x7F ? 1 : 0))

#घोषणा SET_88E_H2CCMD_WOWLAN_FUNC_ENABLE(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE(__cmd, 0, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_PATTERN_MATCH_ENABLE(__cmd, __value)	\
	SET_BITS_TO_LE_1BYTE(__cmd, 1, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_MAGIC_PKT_ENABLE(__cmd, __value)	\
	SET_BITS_TO_LE_1BYTE(__cmd, 2, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_UNICAST_PKT_ENABLE(__cmd, __value)	\
	SET_BITS_TO_LE_1BYTE(__cmd, 3, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_ALL_PKT_DROP(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE(__cmd, 4, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_GPIO_ACTIVE(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE(__cmd, 5, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_REKEY_WAKE_UP(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE(__cmd, 6, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_DISCONNECT_WAKE_UP(__cmd, __value)	\
	SET_BITS_TO_LE_1BYTE(__cmd, 7, 1, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_GPIONUM(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE((__cmd)+1, 0, 8, __value)
#घोषणा SET_88E_H2CCMD_WOWLAN_GPIO_DURATION(__cmd, __value)		\
	SET_BITS_TO_LE_1BYTE((__cmd)+2, 0, 8, __value)


अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_mode(u8 *__ph2ccmd, u8 __val)
अणु
	*(u8 *)(__ph2ccmd) = __val;
पूर्ण

अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_rlbm(u8 *__cmd, u8 __value)
अणु
	u8p_replace_bits(__cmd + 1, __value, GENMASK(3, 0));
पूर्ण

अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_smart_ps(u8 *__cmd, u8 __value)
अणु
	u8p_replace_bits(__cmd + 1, __value, GENMASK(7, 4));
पूर्ण

अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_awake_पूर्णांकerval(u8 *__cmd, u8 __value)
अणु
	*(u8 *)(__cmd + 2) = __value;
पूर्ण

अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_all_queue_uapsd(u8 *__cmd,
							   u8 __value)
अणु
	*(u8 *)(__cmd + 3) = __value;
पूर्ण

अटल अंतरभूत व्योम set_h2ccmd_pwrmode_parm_pwr_state(u8 *__cmd, u8 __value)
अणु
	*(u8 *)(__cmd + 4) = __value;
पूर्ण

#घोषणा SET_H2CCMD_JOINBSSRPT_PARM_OPMODE(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val;
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val;

/* AP_OFFLOAD */
#घोषणा SET_H2CCMD_AP_OFFLOAD_ON(__cmd, __value)			\
	*(u8 *)__cmd = __value;
#घोषणा SET_H2CCMD_AP_OFFLOAD_HIDDEN(__cmd, __value)		\
	*(u8 *)(__cmd + 1) = __value;
#घोषणा SET_H2CCMD_AP_OFFLOAD_DENYANY(__cmd, __value)		\
	*(u8 *)(__cmd + 2) = __value;
#घोषणा SET_H2CCMD_AP_OFFLOAD_WAKEUP_EVT_RPT(__cmd, __value)	\
	*(u8 *)(__cmd + 3) = __value;

पूर्णांक rtl88e_करोwnload_fw(काष्ठा ieee80211_hw *hw,
		       bool buse_wake_on_wlan_fw);
व्योम rtl88e_fill_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 element_id,
			 u32 cmd_len, u8 *cmdbuffer);
व्योम rtl88e_firmware_selfreset(काष्ठा ieee80211_hw *hw);
व्योम rtl88e_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl88e_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus);
व्योम rtl88e_set_fw_ap_off_load_cmd(काष्ठा ieee80211_hw *hw,
				   u8 ap_offload_enable);
व्योम rtl88e_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw, bool b_dl_finished);
व्योम rtl88e_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state);
#पूर्ण_अगर

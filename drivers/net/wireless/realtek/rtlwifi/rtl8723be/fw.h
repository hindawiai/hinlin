<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL8723BE__FW__H__
#घोषणा __RTL8723BE__FW__H__

#घोषणा FW_8192C_SIZE				0x8000
#घोषणा FW_8192C_START_ADDRESS			0x1000
#घोषणा FW_8192C_END_ADDRESS			0x5FFF
#घोषणा FW_8192C_PAGE_SIZE			4096
#घोषणा FW_8192C_POLLING_DELAY			5

#घोषणा USE_OLD_WOWLAN_DEBUG_FW			0

#घोषणा H2C_PWEMODE_LENGTH			7

/* Fw PS state क्रम RPWM.
*BIT[2:0] = HW state
*BIT[3] = Protocol PS state, 1: रेजिस्टर active state , 0: रेजिस्टर sleep state
*BIT[4] = sub-state
*/
#घोषणा	FW_PS_RF_ON		BIT(2)
#घोषणा	FW_PS_REGISTER_ACTIVE	BIT(3)

#घोषणा	FW_PS_ACK		BIT(6)
#घोषणा	FW_PS_TOGGLE		BIT(7)

 /* 8723BE RPWM value*/
 /* BIT[0] = 1: 32k, 0: 40M*/
#घोषणा	FW_PS_CLOCK_OFF		BIT(0)		/* 32k*/
#घोषणा	FW_PS_CLOCK_ON		0		/*40M*/

#घोषणा	FW_PS_STATE_MASK	(0x0F)
#घोषणा	FW_PS_STATE_HW_MASK	(0x07)
/*ISR_ENABLE, IMR_ENABLE, and PS mode should be inherited.*/
#घोषणा	FW_PS_STATE_INT_MASK	(0x3F)

#घोषणा	FW_PS_STATE(x)		(FW_PS_STATE_MASK & (x))

/* ((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))*/
#घोषणा	FW_PS_STATE_ALL_ON	(FW_PS_CLOCK_ON)
/* (FW_PS_RF_ON)*/
#घोषणा	FW_PS_STATE_RF_ON	(FW_PS_CLOCK_ON)
/* 0x0*/
#घोषणा	FW_PS_STATE_RF_OFF	(FW_PS_CLOCK_ON)
/* (FW_PS_STATE_RF_OFF)*/
#घोषणा	FW_PS_STATE_RF_OFF_LOW_PWR	(FW_PS_CLOCK_OFF)


/* For 8723BE H2C PwrMode Cmd ID 5.*/
#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

#घोषणा	FW_PS_IS_ACK(x)		((x) & FW_PS_ACK)

#घोषणा	IS_IN_LOW_POWER_STATE(__fwpsstate)	\
	(FW_PS_STATE(__fwpsstate) == FW_PS_CLOCK_OFF)

#घोषणा	FW_PWR_STATE_ACTIVE	((FW_PS_RF_ON) | (FW_PS_REGISTER_ACTIVE))
#घोषणा	FW_PWR_STATE_RF_OFF	0

क्रमागत rtl8723b_h2c_cmd अणु
	H2C_8723B_RSVDPAGE = 0,
	H2C_8723B_MSRRPT = 1,
	H2C_8723B_SCAN = 2,
	H2C_8723B_KEEP_ALIVE_CTRL = 3,
	H2C_8723B_DISCONNECT_DECISION = 4,
	H2C_8723B_BCN_RSVDPAGE = 9,
	H2C_8723B_PROBERSP_RSVDPAGE = 10,

	H2C_8723B_SETPWRMODE = 0x20,
	H2C_8723B_PS_LPS_PARA = 0x23,
	H2C_8723B_P2P_PS_OFFLOAD = 0x24,

	H2C_8723B_RA_MASK = 0x40,
	H2C_RSSIBE_REPORT = 0x42,
	/*Not defined CTW CMD क्रम P2P yet*/
	H2C_8723B_P2P_PS_CTW_CMD,
	MAX_8723B_H2CCMD
पूर्ण;

#घोषणा pagक्रमागत_128(_len) (u32)(((_len)>>7) + ((_len)&0x7F ? 1 : 0))


#घोषणा SET_H2CCMD_PWRMODE_PARM_MODE(__ph2ccmd, __val)			\
	*(u8 *)__ph2ccmd = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_RLBM(__ph2ccmd, __val)			\
	u8p_replace_bits(__ph2ccmd + 1, __val, GENMASK(3, 0))
#घोषणा SET_H2CCMD_PWRMODE_PARM_SMART_PS(__ph2ccmd, __val)		\
	u8p_replace_bits(__ph2ccmd + 1, __val, GENMASK(7, 4))
#घोषणा SET_H2CCMD_PWRMODE_PARM_AWAKE_INTERVAL(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 2) = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_ALL_QUEUE_UAPSD(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 3) = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_PWR_STATE(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 4) = __val
#घोषणा SET_H2CCMD_PWRMODE_PARM_BYTE5(__ph2ccmd, __val)			\
	*(u8 *)(__ph2ccmd + 5) = __val

#घोषणा SET_H2CCMD_MSRRPT_PARM_OPMODE(__ph2ccmd, __val)		\
	u8p_replace_bits(__ph2ccmd, __val, BIT(0))
#घोषणा SET_H2CCMD_MSRRPT_PARM_MACID_IND(__ph2ccmd, __val)	\
	u8p_replace_bits(__ph2ccmd, __val, BIT(1))

#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 1) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_शून्य_DATA(__ph2ccmd, __val)		\
	*(u8 *)(__ph2ccmd + 2) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_QOS_शून्य_DATA(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 3) = __val
#घोषणा SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_शून्य_DATA(__ph2ccmd, __val)	\
	*(u8 *)(__ph2ccmd + 4) = __val


व्योम rtl8723be_fill_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 element_id,
			    u32 cmd_len, u8 *p_cmdbuffer);
व्योम rtl8723be_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode);
व्योम rtl8723be_set_fw_media_status_rpt_cmd(काष्ठा ieee80211_hw *hw, u8 mstatus);
व्योम rtl8723be_set_fw_rsvdpagepkt(काष्ठा ieee80211_hw *hw, bool b_dl_finished);
व्योम rtl8723be_set_p2p_ps_offload_cmd(काष्ठा ieee80211_hw *hw, u8 p2p_ps_state);
#पूर्ण_अगर

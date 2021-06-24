<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8188E_CMD_H__
#घोषणा __RTL8188E_CMD_H__

क्रमागत RTL8188E_H2C_CMD_ID अणु
	/* Class Common */
	H2C_COM_RSVD_PAGE		= 0x00,
	H2C_COM_MEDIA_STATUS_RPT	= 0x01,
	H2C_COM_SCAN			= 0x02,
	H2C_COM_KEEP_ALIVE		= 0x03,
	H2C_COM_DISCNT_DECISION		= 0x04,
	H2C_COM_INIT_OFFLOAD		= 0x06,
	H2C_COM_REMOTE_WAKE_CTL		= 0x07,
	H2C_COM_AP_OFFLOAD		= 0x08,
	H2C_COM_BCN_RSVD_PAGE		= 0x09,
	H2C_COM_PROB_RSP_RSVD_PAGE	= 0x0A,

	/* Class PS */
	H2C_PS_PWR_MODE			= 0x20,
	H2C_PS_TUNE_PARA		= 0x21,
	H2C_PS_TUNE_PARA_2		= 0x22,
	H2C_PS_LPS_PARA			= 0x23,
	H2C_PS_P2P_OFFLOAD		= 0x24,

	/* Class DM */
	H2C_DM_MACID_CFG		= 0x40,
	H2C_DM_TXBF			= 0x41,

	/* Class BT */
	H2C_BT_COEX_MASK		= 0x60,
	H2C_BT_COEX_GPIO_MODE		= 0x61,
	H2C_BT_DAC_SWING_VAL		= 0x62,
	H2C_BT_PSD_RST			= 0x63,

	/* Class */
	 H2C_RESET_TSF			= 0xc0,
पूर्ण;

क्रमागत अणु
	PWRS
पूर्ण;

काष्ठा setpwrmode_parm अणु
	u8 Mode;/* 0:Active,1:LPS,2:WMMPS */
	u8 SmartPS_RLBM;/* LPS= 0:PS_Poll,1:PS_Poll,2:NullData,WMM= 0:PS_Poll,1:NullData */
	u8 AwakeInterval;	/*  unit: beacon पूर्णांकerval */
	u8 bAllQueueUAPSD;
	u8 PwrState;/* AllON(0x0c),RFON(0x04),RFOFF(0x00) */
पूर्ण;

काष्ठा rsvdpage_loc अणु
	u8 LocProbeRsp;
	u8 LocPsPoll;
	u8 LocNullData;
	u8 LocQosNull;
	u8 LocBTQosNull;
पूर्ण;

/*  host message to firmware cmd */
व्योम rtl8188e_set_FwPwrMode_cmd(काष्ठा adapter *padapter, u8 Mode);
व्योम rtl8188e_set_FwJoinBssReport_cmd(काष्ठा adapter *padapter, u8 mstatus);

व्योम rtl8188e_set_FwMediaStatus_cmd(काष्ठा adapter *adapt, __le16 mstatus_rpt);

#पूर्ण_अगर/* __RTL8188E_CMD_H__ */

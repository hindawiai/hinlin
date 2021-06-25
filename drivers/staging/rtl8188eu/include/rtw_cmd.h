<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_CMD_H_
#घोषणा __RTW_CMD_H_

#समावेश <wlan_bssdef.h>
#समावेश <rtw_rf.h>
#समावेश <rtw_led.h>

#समावेश <osdep_service.h>
#समावेश <ieee80211.h> /*  <ieee80211/ieee80211.h> */

#घोषणा MAX_CMDSZ	1024
#घोषणा MAX_RSPSZ	512

#घोषणा CMDBUFF_ALIGN_SZ 512

काष्ठा cmd_obj अणु
	काष्ठा adapter *padapter;
	u16	cmdcode;
	u8	res;
	u8	*parmbuf;
	u32	cmdsz;
	u8	*rsp;
	u32	rspsz;
	काष्ठा list_head list;
पूर्ण;

काष्ठा cmd_priv अणु
	काष्ठा completion cmd_queue_comp;
	काष्ठा completion terminate_cmdthपढ़ो_comp;
	काष्ठा __queue cmd_queue;
	u8 cmdthd_running;
	काष्ठा adapter *padapter;
पूर्ण;

#घोषणा init_h2fwcmd_w_parm_no_rsp(pcmd, pparm, code) \
करो अणु\
	INIT_LIST_HEAD(&pcmd->list);\
	pcmd->cmdcode = code;\
	pcmd->parmbuf = (u8 *)(pparm);\
	pcmd->cmdsz = माप(*pparm);\
	pcmd->rsp = शून्य;\
	pcmd->rspsz = 0;\
पूर्ण जबतक (0)

u32 rtw_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj);
काष्ठा cmd_obj *rtw_dequeue_cmd(काष्ठा __queue *queue);
व्योम rtw_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd);

पूर्णांक rtw_cmd_thपढ़ो(व्योम *context);

पूर्णांक rtw_init_cmd_priv(काष्ठा cmd_priv *pcmdpriv);

क्रमागत rtw_drvextra_cmd_id अणु
	NONE_WK_CID,
	DYNAMIC_CHK_WK_CID,
	DM_CTRL_WK_CID,
	PBC_POLLING_WK_CID,
	POWER_SAVING_CTRL_WK_CID,/* IPS,AUTOSuspend */
	LPS_CTRL_WK_CID,
	ANT_SELECT_WK_CID,
	P2P_PS_WK_CID,
	P2P_PROTO_WK_CID,
	CHECK_HIQ_WK_CID,/* क्रम softap mode, check hi queue अगर empty */
	INTEl_WIDI_WK_CID,
	C2H_WK_CID,
	RTP_TIMER_CFG_WK_CID,
	MAX_WK_CID
पूर्ण;

क्रमागत LPS_CTRL_TYPE अणु
	LPS_CTRL_SCAN = 0,
	LPS_CTRL_JOINBSS = 1,
	LPS_CTRL_CONNECT = 2,
	LPS_CTRL_DISCONNECT = 3,
	LPS_CTRL_SPECIAL_PACKET = 4,
	LPS_CTRL_LEAVE = 5,
पूर्ण;

क्रमागत RFINTFS अणु
	SWSI,
	HWSI,
	HWPI,
पूर्ण;

/*
 * Caller Mode: Infra, Ad-HoC(C)
 *
 * Notes: To disconnect the current associated BSS
 *
 * Command Mode
 *
 */
काष्ठा disconnect_parm अणु
	u32 deauth_समयout_ms;
पूर्ण;

काष्ठा	setopmode_parm अणु
	u8	mode;
	u8	rsvd[3];
पूर्ण;

/*
 * Caller Mode: AP, Ad-HoC, Infra
 *
 * Notes: To ask RTL8711 perक्रमming site-survey
 *
 * Command-Event Mode
 *
 */

#घोषणा RTW_SSID_SCAN_AMOUNT 9 /*  क्रम WEXT_CSCAN_AMOUNT 9 */
#घोषणा RTW_CHANNEL_SCAN_AMOUNT (14 + 37)
काष्ठा sitesurvey_parm अणु
	पूर्णांक scan_mode;	/* active: 1, passive: 0 */
	u8 ssid_num;
	u8 ch_num;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];
	काष्ठा rtw_ieee80211_channel ch[RTW_CHANNEL_SCAN_AMOUNT];
पूर्ण;

/*
 * Caller Mode: Any
 *
 * Notes: To set the auth type of RTL8711. खोलो/shared/802.1x
 *
 * Command Mode
 *
 */
काष्ठा setauth_parm अणु
	u8 mode;  /* 0: legacy खोलो, 1: legacy shared 2: 802.1x */
	u8 _1x;   /* 0: PSK, 1: TLS */
	u8 rsvd[2];
पूर्ण;

/*
 * Caller Mode: Infra
 *
 * a. algorithm: wep40, wep104, tkip & aes
 * b. keytype: grp key/unicast key
 * c. key contents
 *
 * when shared key ==> keyid is the camid
 * when 802.1x ==> keyid [0:1] ==> grp key
 * when 802.1x ==> keyid > 2 ==> unicast key
 *
 */
काष्ठा setkey_parm अणु
	u8	algorithm;	/* could be none, wep40, TKIP, CCMP, wep104 */
	u8	keyid;
	u8	grpkey;		/* 1: this is the grpkey क्रम 802.1x.
				 * 0: this is the unicast key क्रम 802.1x
				 */
	u8	set_tx;		/* 1: मुख्य tx key क्रम wep. 0: other key. */
	u8	key[16];	/* this could be 40 or 104 */
पूर्ण;

/*
 * When in AP or Ad-Hoc mode, this is used to
 * allocate an sw/hw entry क्रम a newly associated sta.
 *
 * Command
 *
 * when shared key ==> algorithm/keyid
 *
 */
काष्ठा set_stakey_parm अणु
	u8	addr[ETH_ALEN];
	u8	algorithm;
	u8	id;/* currently क्रम erasing cam entry अगर
		    * algorithm == _NO_PRIVACY_
		    */
	u8	key[16];
पूर्ण;

काष्ठा set_stakey_rsp अणु
	u8	addr[ETH_ALEN];
	u8	keyid;
	u8	rsvd;
पूर्ण;

/*
 * Caller Ad-Hoc/AP
 *
 * Command -Rsp(AID == CAMID) mode
 *
 * This is to क्रमce fw to add an sta_data entry per driver's request.
 *
 * FW will ग_लिखो an cam entry associated with it.
 *
 */
काष्ठा set_assocsta_parm अणु
	u8	addr[ETH_ALEN];
पूर्ण;

काष्ठा set_assocsta_rsp अणु
	u8	cam_id;
	u8	rsvd[3];
पूर्ण;

/*
 *	Notes: This command is used क्रम H2C/C2H loopback testing
 *
 *	mac[0] == 0
 *	==> CMD mode, वापस H2C_SUCCESS.
 *	The following condition must be true under CMD mode
 *		mac[1] == mac[4], mac[2] == mac[3], mac[0]=mac[5]= 0;
 *		s0 == 0x1234, s1 == 0xabcd, w0 == 0x78563412, w1 == 0x5aa5def7;
 *		s2 == (b1 << 8 | b0);
 *
 *	mac[0] == 1
 *	==> CMD_RSP mode, वापस H2C_SUCCESS_RSP
 *
 *	The rsp layout shall be:
 *	rsp:			parm:
 *		mac[0]  =   mac[5];
 *		mac[1]  =   mac[4];
 *		mac[2]  =   mac[3];
 *		mac[3]  =   mac[2];
 *		mac[4]  =   mac[1];
 *		mac[5]  =   mac[0];
 *		s0		=   s1;
 *		s1		=   swap16(s0);
 *		w0		=	swap32(w1);
 *		b0		=	b1
 *		s2		=	s0 + s1
 *		b1		=	b0
 *		w1		=	w0
 *
 *	mac[0] ==	2
 *	==> CMD_EVENT mode, वापस	H2C_SUCCESS
 *	The event layout shall be:
 *	event:			parm:
 *		mac[0]  =   mac[5];
 *		mac[1]  =   mac[4];
 *		mac[2]  =   event's seq no, starting from 1 to parm's marc[3]
 *		mac[2]  =   event's seq no, starting from 1 to parm's marc[3]
 *		mac[2]  =   event's seq no, starting from 1 to parm's marc[3]
 *		mac[3]  =   mac[2];
 *		mac[4]  =   mac[1];
 *		mac[5]  =   mac[0];
 *		s0		=   swap16(s0) - event.mac[2];
 *		s1		=   s1 + event.mac[2];
 *		w0		=	swap32(w0);
 *		b0		=	b1
 *		s2		=	s0 + event.mac[2]
 *		b1		=	b0
 *		w1		=	swap32(w1) - event.mac[2];
 *
 *		parm->mac[3] is the total event counts that host requested.
 *	event will be the same with the cmd's param.
 */

/*  CMD param Format क्रम driver extra cmd handler */
काष्ठा drvextra_cmd_parm अणु
	पूर्णांक ec_id; /* extra cmd id */
	पूर्णांक type_size; /*  Can use this field as the type id or command size */
	अचिन्हित अक्षर *pbuf;
पूर्ण;

काष्ठा addBaReq_parm अणु
	अचिन्हित पूर्णांक tid;
	u8	addr[ETH_ALEN];
पूर्ण;

/*H2C Handler index: 46 */
काष्ठा set_ch_parm अणु
	u8 ch;
	u8 bw;
	u8 ch_offset;
पूर्ण;

/*H2C Handler index: 59 */
काष्ठा SetChannelPlan_param अणु
	u8 channel_plan;
पूर्ण;

/*
 *
 * Result:
 * 0x00: success
 * 0x01: success, and check Response.
 * 0x02: cmd ignored due to duplicated sequcne number
 * 0x03: cmd dropped due to invalid cmd code
 * 0x04: reserved.
 *
 */

#घोषणा H2C_SUCCESS		0x00
#घोषणा H2C_SUCCESS_RSP		0x01
#घोषणा H2C_DROPPED		0x03
#घोषणा H2C_PARAMETERS_ERROR	0x04
#घोषणा H2C_REJECTED		0x05

u8 rtw_sitesurvey_cmd(काष्ठा adapter *padapter, काष्ठा ndis_802_11_ssid *ssid,
		      पूर्णांक ssid_num, काष्ठा rtw_ieee80211_channel *ch,
		      पूर्णांक ch_num);
u8 rtw_createbss_cmd(काष्ठा adapter *padapter);
u8 rtw_setstakey_cmd(काष्ठा adapter *padapter, u8 *psta, u8 unicast_key);
u8 rtw_clearstakey_cmd(काष्ठा adapter *padapter, u8 *psta, u8 entry,
		       u8 enqueue);
u8 rtw_joinbss_cmd(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork);
u8 rtw_disassoc_cmd(काष्ठा adapter *padapter, u32 deauth_समयout_ms,
		    bool enqueue);
u8 rtw_setopmode_cmd(काष्ठा adapter *padapter,
		     क्रमागत ndis_802_11_network_infra networktype);
u8 rtw_addbareq_cmd(काष्ठा adapter *padapter, u8 tid, u8 *addr);

u8 rtw_dynamic_chk_wk_cmd(काष्ठा adapter *adapter);

u8 rtw_lps_ctrl_wk_cmd(काष्ठा adapter *padapter, u8 lps_ctrl_type, u8 enqueue);
u8 rtw_rpt_समयr_cfg_cmd(काष्ठा adapter *padapter, u16 minRptTime);

u8 rtw_antenna_select_cmd(काष्ठा adapter *padapter, u8 antenna, u8 enqueue);
u8 rtw_ps_cmd(काष्ठा adapter *padapter);

#अगर_घोषित CONFIG_88EU_AP_MODE
u8 rtw_chk_hi_queue_cmd(काष्ठा adapter *padapter);
#पूर्ण_अगर

u8 rtw_set_chplan_cmd(काष्ठा adapter *padapter, u8 chplan, u8 enqueue);
u8 rtw_drvextra_cmd_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);

व्योम rtw_survey_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd);
व्योम rtw_disassoc_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd);
व्योम rtw_joinbss_cmd_callback(काष्ठा adapter *padapter, काष्ठा cmd_obj *pcmd);
व्योम rtw_createbss_cmd_callback(काष्ठा adapter *adapt, काष्ठा cmd_obj *pcmd);
व्योम rtw_पढ़ोtssi_cmdrsp_callback(काष्ठा adapter *adapt, काष्ठा cmd_obj *cmd);

व्योम rtw_setstaKey_cmdrsp_callback(काष्ठा adapter *adapt, काष्ठा cmd_obj *cmd);
व्योम rtw_setassocsta_cmdrsp_callback(काष्ठा adapter *adapt, काष्ठा cmd_obj *cm);
व्योम rtw_getrttbl_cmdrsp_callback(काष्ठा adapter *adapt, काष्ठा cmd_obj *cmd);

काष्ठा _cmd_callback अणु
	u32	cmd_code;
	व्योम (*callback)(काष्ठा adapter  *padapter, काष्ठा cmd_obj *cmd);
पूर्ण;

क्रमागत rtw_h2c_cmd अणु
	_JoinBss_CMD_,
	_DisConnect_CMD_,
	_CreateBss_CMD_,
	_SetOpMode_CMD_,
	_SiteSurvey_CMD_,
	_SetAuth_CMD_,
	_SetKey_CMD_,
	_SetStaKey_CMD_,
	_SetAssocSta_CMD_,
	_AddBAReq_CMD_,
	_SetChannel_CMD_,
	_TX_Beacon_CMD_,
	_Set_MLME_EVT_CMD_,
	_Set_Drv_Extra_CMD_,
	_SetChannelPlan_CMD_,

	MAX_H2CCMD
पूर्ण;

#पूर्ण_अगर /*  _CMD_H_ */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_CMD_H_
#घोषणा __RTL871X_CMD_H_

#समावेश "wlan_bssdef.h"
#समावेश "rtl871x_rf.h"
#घोषणा C2H_MEM_SZ (16*1024)

#समावेश "osdep_service.h"
#समावेश "ieee80211.h"

#घोषणा FREE_CMDOBJ_SZ	128
#घोषणा MAX_CMDSZ	512
#घोषणा MAX_RSPSZ	512
#घोषणा MAX_EVTSZ	1024
#घोषणा CMDBUFF_ALIGN_SZ 512

काष्ठा cmd_obj अणु
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
	काष्ठा  __queue	cmd_queue;
	u8 cmd_seq;
	u8 *cmd_buf;	/*shall be non-paged, and 4 bytes aligned*/
	u8 *cmd_allocated_buf;
	u8 *rsp_buf;	/*shall be non-paged, and 4 bytes aligned*/
	u8 *rsp_allocated_buf;
	u32 cmd_issued_cnt;
	u32 cmd_करोne_cnt;
	u32 rsp_cnt;
	काष्ठा _adapter *padapter;
पूर्ण;

काष्ठा evt_obj अणु
	u16 evtcode;
	u8 res;
	u8 *parmbuf;
	u32 evtsz;
	काष्ठा list_head list;
पूर्ण;

काष्ठा	evt_priv अणु
	काष्ठा  __queue	evt_queue;
	u8	event_seq;
	u8	*evt_buf;	/*shall be non-paged, and 4 bytes aligned*/
	u8	*evt_allocated_buf;
	u32	evt_करोne_cnt;
	काष्ठा tasklet_काष्ठा event_tasklet;
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

व्योम r8712_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj);
व्योम r8712_enqueue_cmd_ex(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj);
काष्ठा cmd_obj *r8712_dequeue_cmd(काष्ठा  __queue *queue);
व्योम r8712_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd);
पूर्णांक r8712_cmd_thपढ़ो(व्योम *context);
पूर्णांक r8712_init_cmd_priv(काष्ठा cmd_priv *pcmdpriv);
व्योम r8712_मुक्त_cmd_priv(काष्ठा cmd_priv *pcmdpriv);
पूर्णांक r8712_init_evt_priv(काष्ठा evt_priv *pevtpriv);
व्योम r8712_मुक्त_evt_priv(काष्ठा evt_priv *pevtpriv);

क्रमागत rtl871x_drvपूर्णांक_cid अणु
	NONE_WK_CID,
	WDG_WK_CID,
	MAX_WK_CID
पूर्ण;

क्रमागत RFINTFS अणु
	SWSI,
	HWSI,
	HWPI,
पूर्ण;

/*
 * Caller Mode: Infra, Ad-HoC(C)
 * Notes: To enter USB suspend mode
 * Command Mode
 */
काष्ठा usb_suspend_parm अणु
	u32 action; /* 1: sleep, 0:resume */
पूर्ण;

/*
 * Caller Mode: Infra, Ad-HoC(C)
 * Notes: To disconnect the current associated BSS
 * Command Mode
 */
काष्ठा disconnect_parm अणु
	u32 rsvd;
पूर्ण;

/*
 * Caller Mode: AP, Ad-HoC, Infra
 * Notes: To set the NIC mode of RTL8711
 * Command Mode
 * The definition of mode:
 *
 * #घोषणा IW_MODE_AUTO	0	// Let the driver decides which AP to join
 * #घोषणा IW_MODE_ADHOC	1	// Single cell network (Ad-Hoc Clients)
 * #घोषणा IW_MODE_INFRA	2	// Multi cell network, roaming, ..
 * #घोषणा IW_MODE_MASTER	3	// Synchronisation master or AP
 * #घोषणा IW_MODE_REPEAT	4	// Wireless Repeater (क्रमwarder)
 * #घोषणा IW_MODE_SECOND	5	// Secondary master/repeater (backup)
 * #घोषणा IW_MODE_MONITOR	6	// Passive monitor (listen only)
 */
काष्ठा	setopmode_parm अणु
	u8	mode;
	u8	rsvd[3];
पूर्ण;

/*
 * Caller Mode: AP, Ad-HoC, Infra
 * Notes: To ask RTL8711 perक्रमming site-survey
 * Command-Event Mode
 */
काष्ठा sitesurvey_parm अणु
	__le32	passive_mode;	/*active: 1, passive: 0 */
	__le32	bsslimit;	/* 1 ~ 48 */
	__le32	ss_ssidlen;
	u8	ss_ssid[IW_ESSID_MAX_SIZE + 1];
पूर्ण;

/*
 * Caller Mode: Any
 * Notes: To set the auth type of RTL8711. खोलो/shared/802.1x
 * Command Mode
 */
काष्ठा setauth_parm अणु
	u8 mode;  /*0: legacy खोलो, 1: legacy shared 2: 802.1x*/
	u8 _1x;   /*0: PSK, 1: TLS*/
	u8 rsvd[2];
पूर्ण;

/*
 * Caller Mode: Infra
 * a. algorithm: wep40, wep104, tkip & aes
 * b. keytype: grp key/unicast key
 * c. key contents
 *
 * when shared key ==> keyid is the camid
 * when 802.1x ==> keyid [0:1] ==> grp key
 * when 802.1x ==> keyid > 2 ==> unicast key
 */
काष्ठा setkey_parm अणु
	u8	algorithm;	/* encryption algorithm, could be none, wep40,
				 * TKIP, CCMP, wep104
				 */
	u8	keyid;
	u8	grpkey;		/* 1: this is the grpkey क्रम 802.1x.
				 * 0: this is the unicast key क्रम 802.1x
				 */
	u8	key[16];	/* this could be 40 or 104 */
पूर्ण;

/*
 * When in AP or Ad-Hoc mode, this is used to
 * allocate an sw/hw entry क्रम a newly associated sta.
 * Command
 * when shared key ==> algorithm/keyid
 */
काष्ठा set_stakey_parm अणु
	u8	addr[ETH_ALEN];
	u8	algorithm;
	u8	key[16];
पूर्ण;

काष्ठा set_stakey_rsp अणु
	u8	addr[ETH_ALEN];
	u8	keyid;
	u8	rsvd;
पूर्ण;

काष्ठा SetMacAddr_param अणु
	u8	MacAddr[ETH_ALEN];
पूर्ण;

/*
 *	Caller Ad-Hoc/AP
 *
 *	Command -Rsp(AID == CAMID) mode
 *
 *	This is to क्रमce fw to add an sta_data entry per driver's request.
 *
 *	FW will ग_लिखो an cam entry associated with it.
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
 *	Caller Ad-Hoc/AP
 *
 *	Command mode
 *
 *	This is to क्रमce fw to del an sta_data entry per driver's request
 *
 *	FW will invalidate the cam entry associated with it.
 *
 */
काष्ठा del_assocsta_parm अणु
	u8	addr[ETH_ALEN];
पूर्ण;

/*
 *	Caller Mode: AP/Ad-HoC(M)
 *
 *	Notes: To notअगरy fw that given staid has changed its घातer state
 *
 *	Command Mode
 *
 */
काष्ठा setstapwrstate_parm अणु
	u8	staid;
	u8	status;
	u8	hwaddr[6];
पूर्ण;

/*
 *	Caller Mode: Any
 *
 *	Notes: To setup the basic rate of RTL8711
 *
 *	Command Mode
 *
 */
काष्ठा	setbasicrate_parm अणु
	u8	basicrates[NumRates];
पूर्ण;

/*
 *	Caller Mode: Any
 *
 *	Notes: To पढ़ो the current basic rate
 *
 *	Command-Rsp Mode
 *
 */
काष्ठा getbasicrate_parm अणु
	u32 rsvd;
पूर्ण;

काष्ठा getbasicrate_rsp अणु
	u8 basicrates[NumRates];
पूर्ण;

/*
 *	Caller Mode: Any
 *
 *	Notes: To setup the data rate of RTL8711
 *
 *	Command Mode
 *
 */
काष्ठा setdatarate_parm अणु
	u8	mac_id;
	u8	datarates[NumRates];
पूर्ण;

क्रमागत _RT_CHANNEL_DOMAIN अणु
	RT_CHANNEL_DOMAIN_FCC = 0,
	RT_CHANNEL_DOMAIN_IC = 1,
	RT_CHANNEL_DOMAIN_ETSI = 2,
	RT_CHANNEL_DOMAIN_SPAIN = 3,
	RT_CHANNEL_DOMAIN_FRANCE = 4,
	RT_CHANNEL_DOMAIN_MKK = 5,
	RT_CHANNEL_DOMAIN_MKK1 = 6,
	RT_CHANNEL_DOMAIN_ISRAEL = 7,
	RT_CHANNEL_DOMAIN_TELEC = 8,

	/* Be compatible with old channel plan. No good! */
	RT_CHANNEL_DOMAIN_MIC = 9,
	RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN = 10,
	RT_CHANNEL_DOMAIN_WORLD_WIDE_13 = 11,
	RT_CHANNEL_DOMAIN_TELEC_NETGEAR = 12,

	RT_CHANNEL_DOMAIN_NCC = 13,
	RT_CHANNEL_DOMAIN_5G = 14,
	RT_CHANNEL_DOMAIN_5G_40M = 15,
 /*===== Add new channel plan above this line===============*/
	RT_CHANNEL_DOMAIN_MAX,
पूर्ण;


काष्ठा SetChannelPlan_param अणु
	क्रमागत _RT_CHANNEL_DOMAIN ChannelPlan;
पूर्ण;

/*
 *	Caller Mode: Any
 *
 *	Notes: To पढ़ो the current data rate
 *
 *	Command-Rsp Mode
 *
 */
काष्ठा getdatarate_parm अणु
	u32 rsvd;

पूर्ण;

काष्ठा getdatarate_rsp अणु
	u8 datarates[NumRates];
पूर्ण;


/*
 *	Caller Mode: Any
 *	AP: AP can use the info क्रम the contents of beacon frame
 *	Infra: STA can use the info when sitesurveying
 *	Ad-HoC(M): Like AP
 *	Ad-HoC(C): Like STA
 *
 *
 *	Notes: To set the phy capability of the NIC
 *
 *	Command Mode
 *
 */

/*
 *	Caller Mode: Any
 *
 *	Notes: To set the channel/modem/band
 *	This command will be used when channel/modem/band is changed.
 *
 *	Command Mode
 *
 */
/*
 *	Caller Mode: Any
 *
 *	Notes: To get the current setting of channel/modem/band
 *
 *	Command-Rsp Mode
 *
 */
काष्ठा	getphy_rsp अणु
	u8	rfchannel;
	u8	modem;
पूर्ण;

काष्ठा पढ़ोBB_parm अणु
	u8	offset;
पूर्ण;

काष्ठा पढ़ोBB_rsp अणु
	u8	value;
पूर्ण;

काष्ठा पढ़ोTSSI_parm अणु
	u8	offset;
पूर्ण;

काष्ठा पढ़ोTSSI_rsp अणु
	u8	value;
पूर्ण;

काष्ठा ग_लिखोBB_parm अणु
	u8	offset;
	u8	value;
पूर्ण;

काष्ठा ग_लिखोPTM_parm अणु
	u8	type;
पूर्ण;

काष्ठा पढ़ोRF_parm अणु
	u8	offset;
पूर्ण;

काष्ठा पढ़ोRF_rsp अणु
	u32	value;
पूर्ण;

काष्ठा ग_लिखोRF_parm अणु
	u32	offset;
	u32	value;
पूर्ण;

काष्ठा setrfपूर्णांकfs_parm अणु
	u8	rfपूर्णांकfs;
पूर्ण;

काष्ठा getrfपूर्णांकfs_parm अणु
	u8	rfपूर्णांकfs;
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
 *	event:	     parm:
 *	mac[0]  =   mac[5];
 *	mac[1]  =   mac[4];
 *	mac[2]  =   event's sequence number, starting from 1 to parm's marc[3]
 *	mac[3]  =   mac[2];
 *	mac[4]  =   mac[1];
 *	mac[5]  =   mac[0];
 *	s0		=   swap16(s0) - event.mac[2];
 *	s1		=   s1 + event.mac[2];
 *	w0		=	swap32(w0);
 *	b0		=	b1
 *	s2		=	s0 + event.mac[2]
 *	b1		=	b0
 *	w1		=	swap32(w1) - event.mac[2];
 *
 *	parm->mac[3] is the total event counts that host requested.
 *
 *
 *	event will be the same with the cmd's param.
 *
 */

/* CMD param Formart क्रम DRV INTERNAL CMD HDL*/
काष्ठा drvपूर्णांक_cmd_parm अणु
	पूर्णांक i_cid; /*पूर्णांकernal cmd id*/
	पूर्णांक sz; /* buf sz*/
	अचिन्हित अक्षर *pbuf;
पूर्ण;

/*------------------- Below are used क्रम RF/BB tuning ---------------------*/

काष्ठा	setantenna_parm अणु
	u8	tx_antset;
	u8	rx_antset;
	u8	tx_antenna;
	u8	rx_antenna;
पूर्ण;

काष्ठा	enrateadaptive_parm अणु
	u32	en;
पूर्ण;

काष्ठा settxagctbl_parm अणु
	u32	txagc[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा gettxagctbl_parm अणु
	u32 rsvd;
पूर्ण;

काष्ठा gettxagctbl_rsp अणु
	u32	txagc[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा setagcctrl_parm अणु
	u32	agcctrl;	/* 0: pure hw, 1: fw */
पूर्ण;

काष्ठा setssup_parm	अणु
	u32	ss_ForceUp[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा माला_लोsup_parm	अणु
	u32 rsvd;
पूर्ण;

काष्ठा माला_लोsup_rsp	अणु
	u8	ss_ForceUp[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा setssdlevel_parm	अणु
	u8	ss_DLevel[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा माला_लोsdlevel_parm	अणु
	u32 rsvd;
पूर्ण;

काष्ठा माला_लोsdlevel_rsp	अणु
	u8	ss_DLevel[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा setssulevel_parm	अणु
	u8	ss_ULevel[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा माला_लोsulevel_parm	अणु
	u32 rsvd;
पूर्ण;

काष्ठा माला_लोsulevel_rsp	अणु
	u8	ss_ULevel[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा	setcountjudge_parm अणु
	u8	count_judge[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा	अ_लोountjudge_parm अणु
	u32 rsvd;
पूर्ण;

काष्ठा	अ_लोountjudge_rsp अणु
	u8	count_judge[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा setpwrmode_parm  अणु
	u8	mode;
	u8	flag_low_traffic_en;
	u8	flag_lpnav_en;
	u8	flag_rf_low_snr_en;
	u8	flag_dps_en; /* 1: dps, 0: 32k */
	u8	bcn_rx_en;
	u8	bcn_pass_cnt;	  /* fw report one beacon inक्रमmation to
				   * driver  when it receives bcn_pass_cnt
				   * beacons.
				   */
	u8	bcn_to;		  /* beacon TO (ms). तँतई=0तँतउ no limit.*/
	u16	bcn_itv;
	u8	app_itv; /* only क्रम VOIP mode. */
	u8	awake_bcn_itv;
	u8	smart_ps;
	u8	bcn_pass_समय;	/* unit: 100ms */
पूर्ण;

काष्ठा setatim_parm अणु
	u8 op;   /*0: add, 1:del*/
	u8 txid; /* id of dest station.*/
पूर्ण;

काष्ठा setratable_parm अणु
	u8 ss_ForceUp[NumRates];
	u8 ss_ULevel[NumRates];
	u8 ss_DLevel[NumRates];
	u8 count_judge[NumRates];
पूर्ण;

काष्ठा getratable_parm अणु
	uपूर्णांक rsvd;
पूर्ण;

काष्ठा getratable_rsp अणु
	u8 ss_ForceUp[NumRates];
	u8 ss_ULevel[NumRates];
	u8 ss_DLevel[NumRates];
	u8 count_judge[NumRates];
पूर्ण;

/*to get TX,RX retry count*/
काष्ठा gettxretrycnt_parm अणु
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

काष्ठा gettxretrycnt_rsp अणु
	अचिन्हित दीर्घ tx_retrycnt;
पूर्ण;

काष्ठा getrxretrycnt_parm अणु
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

काष्ठा getrxretrycnt_rsp अणु
	अचिन्हित दीर्घ rx_retrycnt;
पूर्ण;

/*to get BCNOK,BCNERR count*/
काष्ठा getbcnokcnt_parm अणु
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

काष्ठा getbcnokcnt_rsp अणु
	अचिन्हित दीर्घ bcnokcnt;
पूर्ण;

काष्ठा getbcnerrcnt_parm अणु
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

काष्ठा getbcnerrcnt_rsp अणु
	अचिन्हित दीर्घ bcnerrcnt;
पूर्ण;

/* to get current TX घातer level*/
काष्ठा अ_लोurtxpwrlevel_parm अणु
	अचिन्हित पूर्णांक rsvd;
पूर्ण;

काष्ठा अ_लोurtxpwrlevel_rsp अणु
	अचिन्हित लघु tx_घातer;
पूर्ण;

/*dynamic on/off DIG*/
काष्ठा setdig_parm अणु
	अचिन्हित अक्षर dig_on;	/* 1:on , 0:off */
पूर्ण;

/*dynamic on/off RA*/
काष्ठा setra_parm अणु
	अचिन्हित अक्षर ra_on;	/* 1:on , 0:off */
पूर्ण;

काष्ठा setprobereqextraie_parm अणु
	अचिन्हित अक्षर e_id;
	अचिन्हित अक्षर ie_len;
	अचिन्हित अक्षर ie[0];
पूर्ण;

काष्ठा setassocreqextraie_parm अणु
	अचिन्हित अक्षर e_id;
	अचिन्हित अक्षर ie_len;
	अचिन्हित अक्षर ie[0];
पूर्ण;

काष्ठा setproberspextraie_parm अणु
	अचिन्हित अक्षर e_id;
	अचिन्हित अक्षर ie_len;
	अचिन्हित अक्षर ie[0];
पूर्ण;

काष्ठा setassocrspextraie_parm अणु
	अचिन्हित अक्षर e_id;
	अचिन्हित अक्षर ie_len;
	अचिन्हित अक्षर ie[0];
पूर्ण;

काष्ठा addBaReq_parm अणु
	अचिन्हित पूर्णांक tid;
पूर्ण;

/*H2C Handler index: 46 */
काष्ठा SetChannel_parm अणु
	u32 curr_ch;
पूर्ण;

/*H2C Handler index: 61 */
काष्ठा DisconnectCtrlEx_param अणु
	/* MAXTIME = (2 * FirstStageTO) + (TryPktCnt * TryPktInterval) */
	अचिन्हित अक्षर EnableDrvCtrl;
	अचिन्हित अक्षर TryPktCnt;
	अचिन्हित अक्षर TryPktInterval; /* Unit: ms */
	अचिन्हित अक्षर rsvd;
	अचिन्हित पूर्णांक  FirstStageTO; /* Unit: ms */
पूर्ण;

#घोषणा GEN_CMD_CODE(cmd)	cmd ## _CMD_

/*
 * Result:
 * 0x00: success
 * 0x01: success, and check Response.
 * 0x02: cmd ignored due to duplicated sequence number
 * 0x03: cmd dropped due to invalid cmd code
 * 0x04: reserved.
 */

#घोषणा H2C_RSP_OFFSET			512
#घोषणा H2C_SUCCESS			0x00
#घोषणा H2C_SUCCESS_RSP			0x01
#घोषणा H2C_DUPLICATED			0x02
#घोषणा H2C_DROPPED			0x03
#घोषणा H2C_PARAMETERS_ERROR		0x04
#घोषणा H2C_REJECTED			0x05
#घोषणा H2C_CMD_OVERFLOW		0x06
#घोषणा H2C_RESERVED			0x07

व्योम r8712_setMacAddr_cmd(काष्ठा _adapter *padapter, u8 *mac_addr);
u8 r8712_sitesurvey_cmd(काष्ठा _adapter *padapter,
			काष्ठा ndis_802_11_ssid *pssid);
पूर्णांक r8712_createbss_cmd(काष्ठा _adapter *padapter);
व्योम r8712_setstakey_cmd(काष्ठा _adapter *padapter, u8 *psta, u8 unicast_key);
पूर्णांक r8712_joinbss_cmd(काष्ठा _adapter *padapter,
		      काष्ठा wlan_network *pnetwork);
व्योम r8712_disassoc_cmd(काष्ठा _adapter *padapter);
व्योम r8712_setopmode_cmd(काष्ठा _adapter *padapter,
		 क्रमागत NDIS_802_11_NETWORK_INFRASTRUCTURE networktype);
पूर्णांक r8712_setdatarate_cmd(काष्ठा _adapter *padapter, u8 *rateset);
व्योम r8712_set_chplan_cmd(काष्ठा _adapter  *padapter, पूर्णांक chplan);
पूर्णांक r8712_getrfreg_cmd(काष्ठा _adapter *padapter, u8 offset, u8 *pval);
पूर्णांक r8712_setrfreg_cmd(काष्ठा _adapter  *padapter, u8 offset, u32 val);
व्योम r8712_addbareq_cmd(काष्ठा _adapter *padapter, u8 tid);
व्योम r8712_wdg_wk_cmd(काष्ठा _adapter *padapter);
व्योम r8712_survey_cmd_callback(काष्ठा _adapter  *padapter,
			       काष्ठा cmd_obj *pcmd);
व्योम r8712_disassoc_cmd_callback(काष्ठा _adapter  *padapter,
				 काष्ठा cmd_obj *pcmd);
व्योम r8712_joinbss_cmd_callback(काष्ठा _adapter  *padapter,
				काष्ठा cmd_obj *pcmd);
व्योम r8712_createbss_cmd_callback(काष्ठा _adapter *padapter,
				  काष्ठा cmd_obj *pcmd);
व्योम r8712_getbbrfreg_cmdrsp_callback(काष्ठा _adapter *padapter,
				      काष्ठा cmd_obj *pcmd);
व्योम r8712_पढ़ोtssi_cmdrsp_callback(काष्ठा _adapter *padapter,
				काष्ठा cmd_obj *pcmd);
व्योम r8712_setstaKey_cmdrsp_callback(काष्ठा _adapter  *padapter,
				     काष्ठा cmd_obj *pcmd);
व्योम r8712_setassocsta_cmdrsp_callback(काष्ठा _adapter  *padapter,
				       काष्ठा cmd_obj *pcmd);
व्योम r8712_disconnectCtrlEx_cmd(काष्ठा _adapter *adapter, u32 enableDrvCtrl,
			u32 tryPktCnt, u32 tryPktInterval, u32 firstStageTO);

काष्ठा _cmd_callback अणु
	u32	cmd_code;
	व्योम (*callback)(काष्ठा _adapter  *padapter, काष्ठा cmd_obj *cmd);
पूर्ण;

#समावेश "rtl8712_cmd.h"

#पूर्ण_अगर /* _CMD_H_ */


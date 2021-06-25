<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_CMD_H_
#घोषणा __RTW_CMD_H_

#समावेश <linux/completion.h>

#घोषणा C2H_MEM_SZ (16*1024)

	#घोषणा FREE_CMDOBJ_SZ	128

	#घोषणा MAX_CMDSZ	1024
	#घोषणा MAX_RSPSZ	512
	#घोषणा MAX_EVTSZ	1024

	#घोषणा CMDBUFF_ALIGN_SZ 512

	काष्ठा cmd_obj अणु
		काष्ठा adapter *padapter;
		u16 cmdcode;
		u8 res;
		u8 *parmbuf;
		u32 cmdsz;
		u8 *rsp;
		u32 rspsz;
		काष्ठा submit_ctx *sctx;
		काष्ठा list_head	list;
	पूर्ण;

	/* cmd flags */
	क्रमागत अणु
		RTW_CMDF_सूचीECTLY = BIT0,
		RTW_CMDF_WAIT_ACK = BIT1,
	पूर्ण;

	काष्ठा cmd_priv अणु
		काष्ठा completion cmd_queue_comp;
		काष्ठा completion terminate_cmdthपढ़ो_comp;
		काष्ठा __queue	cmd_queue;
		u8 cmd_seq;
		u8 *cmd_buf;	/* shall be non-paged, and 4 bytes aligned */
		u8 *cmd_allocated_buf;
		u8 *rsp_buf;	/* shall be non-paged, and 4 bytes aligned */
		u8 *rsp_allocated_buf;
		u32 cmd_issued_cnt;
		u32 cmd_करोne_cnt;
		u32 rsp_cnt;
		atomic_t cmdthd_running;
		/* u8 cmdthd_running; */
		u8 stop_req;
		काष्ठा adapter *padapter;
		काष्ठा mutex sctx_mutex;
	पूर्ण;

	काष्ठा	evt_priv अणु
		काष्ठा work_काष्ठा c2h_wk;
		bool c2h_wk_alive;
		काष्ठा rtw_cbuf *c2h_queue;
		#घोषणा C2H_QUEUE_MAX_LEN 10

		atomic_t event_seq;
		u8 *evt_buf;	/* shall be non-paged, and 4 bytes aligned */
		u8 *evt_allocated_buf;
		u32 evt_करोne_cnt;
		u8 *c2h_mem;
		u8 *allocated_c2h_mem;
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

#घोषणा init_h2fwcmd_w_parm_no_parm_rsp(pcmd, code) \
करो अणु\
	INIT_LIST_HEAD(&pcmd->list);\
	pcmd->cmdcode = code;\
	pcmd->parmbuf = शून्य;\
	pcmd->cmdsz = 0;\
	pcmd->rsp = शून्य;\
	pcmd->rspsz = 0;\
पूर्ण जबतक (0)

काष्ठा c2h_evt_hdr अणु
	u8 id:4;
	u8 plen:4;
	u8 seq;
	u8 payload[0];
पूर्ण;

काष्ठा c2h_evt_hdr_88xx अणु
	u8 id;
	u8 seq;
	u8 payload[12];
	u8 plen;
	u8 trigger;
पूर्ण;

#घोषणा c2h_evt_valid(c2h_evt) ((c2h_evt)->id || (c2h_evt)->plen)

पूर्णांक rtw_enqueue_cmd(काष्ठा cmd_priv *pcmdpriv, काष्ठा cmd_obj *obj);
बाह्य काष्ठा cmd_obj *rtw_dequeue_cmd(काष्ठा cmd_priv *pcmdpriv);
बाह्य व्योम rtw_मुक्त_cmd_obj(काष्ठा cmd_obj *pcmd);

व्योम rtw_stop_cmd_thपढ़ो(काष्ठा adapter *adapter);
पूर्णांक rtw_cmd_thपढ़ो(व्योम *context);

बाह्य व्योम rtw_मुक्त_cmd_priv(काष्ठा cmd_priv *pcmdpriv);

बाह्य व्योम rtw_मुक्त_evt_priv(काष्ठा evt_priv *pevtpriv);
बाह्य व्योम rtw_evt_notअगरy_isr(काष्ठा evt_priv *pevtpriv);

क्रमागत अणु
	NONE_WK_CID,
	DYNAMIC_CHK_WK_CID,
	DM_CTRL_WK_CID,
	PBC_POLLING_WK_CID,
	POWER_SAVING_CTRL_WK_CID,/* IPS, AUTOSuspend */
	LPS_CTRL_WK_CID,
	ANT_SELECT_WK_CID,
	P2P_PS_WK_CID,
	P2P_PROTO_WK_CID,
	CHECK_HIQ_WK_CID,/* क्रम softap mode, check hi queue अगर empty */
	INTEl_WIDI_WK_CID,
	C2H_WK_CID,
	RTP_TIMER_CFG_WK_CID,
	RESET_SECURITYPRIV, /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	FREE_ASSOC_RESOURCES, /*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
	DM_IN_LPS_WK_CID,
	DM_RA_MSK_WK_CID, /* add क्रम STA update RAMask when bandwidth change. */
	BEAMFORMING_WK_CID,
	LPS_CHANGE_DTIM_CID,
	BTINFO_WK_CID,
	MAX_WK_CID
पूर्ण;

क्रमागत अणु
	LPS_CTRL_SCAN = 0,
	LPS_CTRL_JOINBSS = 1,
	LPS_CTRL_CONNECT = 2,
	LPS_CTRL_DISCONNECT = 3,
	LPS_CTRL_SPECIAL_PACKET = 4,
	LPS_CTRL_LEAVE = 5,
	LPS_CTRL_TRAFFIC_BUSY = 6,
पूर्ण;

क्रमागत अणु
	SWSI,
	HWSI,
	HWPI,
पूर्ण;

/*
Caller Mode: Infra, Ad-HoC

Notes: To join a known BSS.

Command-Event Mode

*/

/*
Caller Mode: Infra, Ad-Hoc

Notes: To join the specअगरied bss

Command Event Mode

*/
काष्ठा joinbss_parm अणु
	काष्ठा wlan_bssid_ex network;
पूर्ण;

/*
Caller Mode: Infra, Ad-HoC(C)

Notes: To disconnect the current associated BSS

Command Mode

*/
काष्ठा disconnect_parm अणु
	u32 deauth_समयout_ms;
पूर्ण;

/*
Caller Mode: AP, Ad-HoC(M)

Notes: To create a BSS

Command Mode
*/
काष्ठा createbss_parm अणु
	काष्ठा wlan_bssid_ex network;
पूर्ण;

/*
Caller Mode: AP, Ad-HoC, Infra

Notes: To set the NIC mode of RTL8711

Command Mode

The definition of mode:

#घोषणा IW_MODE_AUTO	0	 Let the driver decides which AP to join
#घोषणा IW_MODE_ADHOC	1	 Single cell network (Ad-Hoc Clients)
#घोषणा IW_MODE_INFRA	2	 Multi cell network, roaming, ..
#घोषणा IW_MODE_MASTER	3	 Synchronisation master or Access Poपूर्णांक
#घोषणा IW_MODE_REPEAT	4	 Wireless Repeater (क्रमwarder)
#घोषणा IW_MODE_SECOND	5	 Secondary master/repeater (backup)
#घोषणा IW_MODE_MONITOR	6	 Passive monitor (listen only)

*/
काष्ठा	setopmode_parm अणु
	u8 mode;
	u8 rsvd[3];
पूर्ण;

/*
Caller Mode: AP, Ad-HoC, Infra

Notes: To ask RTL8711 perक्रमming site-survey

Command-Event Mode

*/

#घोषणा RTW_SSID_SCAN_AMOUNT 9 /*  क्रम WEXT_CSCAN_AMOUNT 9 */
#घोषणा RTW_CHANNEL_SCAN_AMOUNT (14+37)
काष्ठा sitesurvey_parm अणु
	चिन्हित पूर्णांक scan_mode;	/* active: 1, passive: 0 */
	u8 ssid_num;
	u8 ch_num;
	काष्ठा ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];
	काष्ठा rtw_ieee80211_channel ch[RTW_CHANNEL_SCAN_AMOUNT];
पूर्ण;

/*
Caller Mode: Any

Notes: To set the auth type of RTL8711. खोलो/shared/802.1x

Command Mode

*/
काष्ठा setauth_parm अणु
	u8 mode;  /* 0: legacy खोलो, 1: legacy shared 2: 802.1x */
	u8 _1x;   /* 0: PSK, 1: TLS */
	u8 rsvd[2];
पूर्ण;

/*
Caller Mode: Infra

a. algorithm: wep40, wep104, tkip & aes
b. keytype: grp key/unicast key
c. key contents

when shared key ==> keyid is the camid
when 802.1x ==> keyid [0:1] ==> grp key
when 802.1x ==> keyid > 2 ==> unicast key

*/
काष्ठा setkey_parm अणु
	u8 algorithm;	/*  encryption algorithm, could be none, wep40, TKIP, CCMP, wep104 */
	u8 keyid;
	u8 grpkey;		/*  1: this is the grpkey क्रम 802.1x. 0: this is the unicast key क्रम 802.1x */
	u8 set_tx;		/*  1: मुख्य tx key क्रम wep. 0: other key. */
	u8 key[16];	/*  this could be 40 or 104 */
पूर्ण;

/*
When in AP or Ad-Hoc mode, this is used to
allocate an sw/hw entry क्रम a newly associated sta.

Command

when shared key ==> algorithm/keyid

*/
काष्ठा set_stakey_parm अणु
	u8 addr[ETH_ALEN];
	u8 algorithm;
	u8 keyid;
	u8 key[16];
पूर्ण;

काष्ठा set_stakey_rsp अणु
	u8 addr[ETH_ALEN];
	u8 keyid;
	u8 rsvd;
पूर्ण;

/*
Caller Ad-Hoc/AP

Command -Rsp(AID == CAMID) mode

This is to क्रमce fw to add an sta_data entry per driver's request.

FW will ग_लिखो an cam entry associated with it.

*/
काष्ठा set_assocsta_parm अणु
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा set_assocsta_rsp अणु
	u8 cam_id;
	u8 rsvd[3];
पूर्ण;

/*
	Caller Ad-Hoc/AP

	Command mode

	This is to क्रमce fw to del an sta_data entry per driver's request

	FW will invalidate the cam entry associated with it.

*/
काष्ठा del_assocsta_parm अणु
	u8 addr[ETH_ALEN];
पूर्ण;

/*
Caller Mode: AP/Ad-HoC(M)

Notes: To notअगरy fw that given staid has changed its घातer state

Command Mode

*/
काष्ठा setstapwrstate_parm अणु
	u8 staid;
	u8 status;
	u8 hwaddr[6];
पूर्ण;

/*
Caller Mode: Any

Notes: To setup the basic rate of RTL8711

Command Mode

*/
काष्ठा	setbasicrate_parm अणु
	u8 basicrates[NumRates];
पूर्ण;

/*
Caller Mode: Any

Notes: To पढ़ो the current basic rate

Command-Rsp Mode

*/
काष्ठा getbasicrate_parm अणु
	u32 rsvd;
पूर्ण;

/*
Caller Mode: Any

Notes: To setup the data rate of RTL8711

Command Mode

*/
काष्ठा setdatarate_parm अणु
	u8 mac_id;
	u8 datarates[NumRates];
पूर्ण;

/*
Caller Mode: Any

Notes: To पढ़ो the current data rate

Command-Rsp Mode

*/
काष्ठा getdatarate_parm अणु
	u32 rsvd;

पूर्ण;

/*
Caller Mode: Any
AP: AP can use the info क्रम the contents of beacon frame
Infra: STA can use the info when sitesurveying
Ad-HoC(M): Like AP
Ad-HoC(C): Like STA


Notes: To set the phy capability of the NIC

Command Mode

*/

काष्ठा	setphyinfo_parm अणु
	काष्ठा regulatory_class class_sets[NUM_REGULATORYS];
	u8 status;
पूर्ण;

काष्ठा	getphyinfo_parm अणु
	u32 rsvd;
पूर्ण;

/*
Caller Mode: Any

Notes: To set the channel/modem/band
This command will be used when channel/modem/band is changed.

Command Mode

*/
काष्ठा	setphy_parm अणु
	u8 rfchannel;
	u8 modem;
पूर्ण;

/*
Caller Mode: Any

Notes: To get the current setting of channel/modem/band

Command-Rsp Mode

*/
काष्ठा	getphy_parm अणु
	u32 rsvd;

पूर्ण;

काष्ठा Tx_Beacon_param अणु
	काष्ठा wlan_bssid_ex network;
पूर्ण;

/*
	Notes: This command is used क्रम H2C/C2H loopback testing

	mac[0] == 0
	==> CMD mode, वापस H2C_SUCCESS.
	The following condition must be true under CMD mode
		mac[1] == mac[4], mac[2] == mac[3], mac[0]=mac[5]= 0;
		s0 == 0x1234, s1 == 0xabcd, w0 == 0x78563412, w1 == 0x5aa5def7;
		s2 == (b1 << 8 | b0);

	mac[0] == 1
	==> CMD_RSP mode, वापस H2C_SUCCESS_RSP

	The rsp layout shall be:
	rsp:			parm:
		mac[0]  =   mac[5];
		mac[1]  =   mac[4];
		mac[2]  =   mac[3];
		mac[3]  =   mac[2];
		mac[4]  =   mac[1];
		mac[5]  =   mac[0];
		s0		=   s1;
		s1		=   swap16(s0);
		w0		=	swap32(w1);
		b0		=	b1
		s2		=	s0 + s1
		b1		=	b0
		w1		=	w0

	mac[0] ==	2
	==> CMD_EVENT mode, वापस	H2C_SUCCESS
	The event layout shall be:
	event:			parm:
		mac[0]  =   mac[5];
		mac[1]  =   mac[4];
		mac[2]  =   event's sequence number, starting from 1 to parm's marc[3]
		mac[3]  =   mac[2];
		mac[4]  =   mac[1];
		mac[5]  =   mac[0];
		s0		=   swap16(s0) - event.mac[2];
		s1		=   s1 + event.mac[2];
		w0		=	swap32(w0);
		b0		=	b1
		s2		=	s0 + event.mac[2]
		b1		=	b0
		w1		=	swap32(w1) - event.mac[2];

		parm->mac[3] is the total event counts that host requested.


	event will be the same with the cmd's param.

*/

/*  CMD param Formart क्रम driver extra cmd handler */
काष्ठा drvextra_cmd_parm अणु
	पूर्णांक ec_id; /* extra cmd id */
	पूर्णांक type; /*  Can use this field as the type id or command size */
	पूर्णांक size; /* buffer size */
	अचिन्हित अक्षर *pbuf;
पूर्ण;

/*------------------- Below are used क्रम RF/BB tuning ---------------------*/

काष्ठा	अ_लोountjudge_rsp अणु
	u8 count_judge[MAX_RATES_LENGTH];
पूर्ण;

काष्ठा addBaReq_parm अणु
	अचिन्हित पूर्णांक tid;
	u8 addr[ETH_ALEN];
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

/*H2C Handler index: 61 */
काष्ठा SetChannelSwitch_param अणु
	u8 new_ch_no;
पूर्ण;

/*H2C Handler index: 62 */
काष्ठा TDLSoption_param अणु
	u8 addr[ETH_ALEN];
	u8 option;
पूर्ण;

/*H2C Handler index: 64 */
काष्ठा RunInThपढ़ो_param अणु
	व्योम (*func)(व्योम *);
	व्योम *context;
पूर्ण;


#घोषणा GEN_CMD_CODE(cmd)	cmd ## _CMD_


/*

Result:
0x00: success
0x01: success, and check Response.
0x02: cmd ignored due to duplicated sequcne number
0x03: cmd dropped due to invalid cmd code
0x04: reserved.

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

u8 rtw_sitesurvey_cmd(काष्ठा adapter  *padapter, काष्ठा ndis_802_11_ssid *ssid, पूर्णांक ssid_num, काष्ठा rtw_ieee80211_channel *ch, पूर्णांक ch_num);
बाह्य u8 rtw_createbss_cmd(काष्ठा adapter  *padapter);
पूर्णांक rtw_startbss_cmd(काष्ठा adapter  *padapter, पूर्णांक flags);

काष्ठा sta_info;
बाह्य u8 rtw_setstakey_cmd(काष्ठा adapter  *padapter, काष्ठा sta_info *sta, u8 unicast_key, bool enqueue);
बाह्य u8 rtw_clearstakey_cmd(काष्ठा adapter *padapter, काष्ठा sta_info *sta, u8 enqueue);

बाह्य u8 rtw_joinbss_cmd(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork);
u8 rtw_disassoc_cmd(काष्ठा adapter *padapter, u32 deauth_समयout_ms, bool enqueue);
बाह्य u8 rtw_setopmode_cmd(काष्ठा adapter  *padapter, क्रमागत ndis_802_11_network_infraकाष्ठाure networktype, bool enqueue);
बाह्य u8 rtw_setdatarate_cmd(काष्ठा adapter  *padapter, u8 *rateset);
बाह्य u8 rtw_setrfपूर्णांकfs_cmd(काष्ठा adapter  *padapter, u8 mode);

बाह्य u8 rtw_gettssi_cmd(काष्ठा adapter  *padapter, u8 offset, u8 *pval);
बाह्य u8 rtw_setfwdig_cmd(काष्ठा adapter *padapter, u8 type);
बाह्य u8 rtw_setfwra_cmd(काष्ठा adapter *padapter, u8 type);

बाह्य u8 rtw_addbareq_cmd(काष्ठा adapter *padapter, u8 tid, u8 *addr);
/*  add क्रम CONFIG_IEEE80211W, none 11w also can use */
बाह्य u8 rtw_reset_securitypriv_cmd(काष्ठा adapter *padapter);
बाह्य u8 rtw_मुक्त_assoc_resources_cmd(काष्ठा adapter *padapter);
बाह्य u8 rtw_dynamic_chk_wk_cmd(काष्ठा adapter *adapter);

u8 rtw_lps_ctrl_wk_cmd(काष्ठा adapter *padapter, u8 lps_ctrl_type, u8 enqueue);
u8 rtw_dm_in_lps_wk_cmd(काष्ठा adapter *padapter);

u8 rtw_dm_ra_mask_wk_cmd(काष्ठा adapter *padapter, u8 *psta);

बाह्य u8 rtw_ps_cmd(काष्ठा adapter *padapter);

u8 rtw_chk_hi_queue_cmd(काष्ठा adapter *padapter);

बाह्य u8 rtw_set_chplan_cmd(काष्ठा adapter *padapter, u8 chplan, u8 enqueue, u8 swconfig);

बाह्य u8 rtw_c2h_packet_wk_cmd(काष्ठा adapter *padapter, u8 *pbuf, u16 length);
बाह्य u8 rtw_c2h_wk_cmd(काष्ठा adapter *padapter, u8 *c2h_evt);

u8 rtw_drvextra_cmd_hdl(काष्ठा adapter *padapter, अचिन्हित अक्षर *pbuf);

बाह्य व्योम rtw_survey_cmd_callback(काष्ठा adapter  *padapter, काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_disassoc_cmd_callback(काष्ठा adapter  *padapter, काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_joinbss_cmd_callback(काष्ठा adapter  *padapter, काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_createbss_cmd_callback(काष्ठा adapter  *padapter, काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_getbbrfreg_cmdrsp_callback(काष्ठा adapter  *padapter, काष्ठा cmd_obj *pcmd);

बाह्य व्योम rtw_setstaKey_cmdrsp_callback(काष्ठा adapter  *padapter,  काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_setassocsta_cmdrsp_callback(काष्ठा adapter  *padapter,  काष्ठा cmd_obj *pcmd);
बाह्य व्योम rtw_getrttbl_cmdrsp_callback(काष्ठा adapter  *padapter,  काष्ठा cmd_obj *pcmd);


काष्ठा _cmd_callback अणु
	u32 cmd_code;
	व्योम (*callback)(काष्ठा adapter  *padapter, काष्ठा cmd_obj *cmd);
पूर्ण;

क्रमागत अणु
	GEN_CMD_CODE(_Read_MACREG),	/*0*/
	GEN_CMD_CODE(_Write_MACREG),
	GEN_CMD_CODE(_Read_BBREG),
	GEN_CMD_CODE(_Write_BBREG),
	GEN_CMD_CODE(_Read_RFREG),
	GEN_CMD_CODE(_Write_RFREG), /*5*/
	GEN_CMD_CODE(_Read_EEPROM),
	GEN_CMD_CODE(_Write_EEPROM),
	GEN_CMD_CODE(_Read_EFUSE),
	GEN_CMD_CODE(_Write_EFUSE),

	GEN_CMD_CODE(_Read_CAM),	/*10*/
	GEN_CMD_CODE(_Write_CAM),
	GEN_CMD_CODE(_setBCNITV),
	GEN_CMD_CODE(_setMBIDCFG),
	GEN_CMD_CODE(_JoinBss),   /*14*/
	GEN_CMD_CODE(_DisConnect), /*15*/
	GEN_CMD_CODE(_CreateBss),
	GEN_CMD_CODE(_SetOpMode),
	GEN_CMD_CODE(_SiteSurvey),  /*18*/
	GEN_CMD_CODE(_SetAuth),

	GEN_CMD_CODE(_SetKey),	/*20*/
	GEN_CMD_CODE(_SetStaKey),
	GEN_CMD_CODE(_SetAssocSta),
	GEN_CMD_CODE(_DelAssocSta),
	GEN_CMD_CODE(_SetStaPwrState),
	GEN_CMD_CODE(_SetBasicRate), /*25*/
	GEN_CMD_CODE(_GetBasicRate),
	GEN_CMD_CODE(_SetDataRate),
	GEN_CMD_CODE(_GetDataRate),
	GEN_CMD_CODE(_SetPhyInfo),

	GEN_CMD_CODE(_GetPhyInfo),	/*30*/
	GEN_CMD_CODE(_SetPhy),
	GEN_CMD_CODE(_GetPhy),
	GEN_CMD_CODE(_पढ़ोRssi),
	GEN_CMD_CODE(_पढ़ोGain),
	GEN_CMD_CODE(_SetAtim), /*35*/
	GEN_CMD_CODE(_SetPwrMode),
	GEN_CMD_CODE(_JoinbssRpt),
	GEN_CMD_CODE(_SetRaTable),
	GEN_CMD_CODE(_GetRaTable),

	GEN_CMD_CODE(_GetCCXReport), /*40*/
	GEN_CMD_CODE(_GetDTMReport),
	GEN_CMD_CODE(_GetTXRateStatistics),
	GEN_CMD_CODE(_SetUsbSuspend),
	GEN_CMD_CODE(_SetH2cLbk),
	GEN_CMD_CODE(_AddBAReq), /*45*/
	GEN_CMD_CODE(_SetChannel), /*46*/
	GEN_CMD_CODE(_SetTxPower),
	GEN_CMD_CODE(_SwitchAntenna),
	GEN_CMD_CODE(_SetCrystalCap),
	GEN_CMD_CODE(_SetSingleCarrierTx), /*50*/

	GEN_CMD_CODE(_SetSingleToneTx),/*51*/
	GEN_CMD_CODE(_SetCarrierSuppressionTx),
	GEN_CMD_CODE(_SetContinuousTx),
	GEN_CMD_CODE(_SwitchBandwidth), /*54*/
	GEN_CMD_CODE(_TX_Beacon), /*55*/

	GEN_CMD_CODE(_Set_MLME_EVT), /*56*/
	GEN_CMD_CODE(_Set_Drv_Extra), /*57*/
	GEN_CMD_CODE(_Set_H2C_MSG), /*58*/

	GEN_CMD_CODE(_SetChannelPlan), /*59*/

	GEN_CMD_CODE(_SetChannelSwitch), /*60*/
	GEN_CMD_CODE(_TDLS), /*61*/
	GEN_CMD_CODE(_ChkBMCSleepq), /*62*/

	GEN_CMD_CODE(_RunInThपढ़ोCMD), /*63*/

	MAX_H2CCMD
पूर्ण;

#घोषणा _GetBBReg_CMD_		_Read_BBREG_CMD_
#घोषणा _SetBBReg_CMD_		_Write_BBREG_CMD_
#घोषणा _GetRFReg_CMD_		_Read_RFREG_CMD_
#घोषणा _SetRFReg_CMD_		_Write_RFREG_CMD_

#पूर्ण_अगर /*  _CMD_H_ */

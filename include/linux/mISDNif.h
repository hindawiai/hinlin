<शैली गुरु>
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 *
 * This code is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE
 * version 2.1 as published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU LESSER GENERAL PUBLIC LICENSE क्रम more details.
 *
 */

#अगर_अघोषित mISDNIF_H
#घोषणा mISDNIF_H

#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>

/*
 * ABI Version 32 bit
 *
 * <8 bit> Major version
 *		- changed अगर any पूर्णांकerface become backwards incompatible
 *
 * <8 bit> Minor version
 *              - changed अगर any पूर्णांकerface is extended but backwards compatible
 *
 * <16 bit> Release number
 *              - should be incremented on every checkin
 */
#घोषणा	MISDN_MAJOR_VERSION	1
#घोषणा	MISDN_MINOR_VERSION	1
#घोषणा MISDN_RELEASE		29

/* primitives क्रम inक्रमmation exchange
 * generell क्रमmat
 * <16  bit  0 >
 * <8  bit command>
 *    BIT 8 = 1 LAYER निजी
 *    BIT 7 = 1 answer
 *    BIT 6 = 1 DATA
 * <8  bit target layer mask>
 *
 * Layer = 00 is reserved क्रम general commands
   Layer = 01  L2 -> HW
   Layer = 02  HW -> L2
   Layer = 04  L3 -> L2
   Layer = 08  L2 -> L3
 * Layer = FF is reserved क्रम broadcast commands
 */

#घोषणा MISDN_CMDMASK		0xff00
#घोषणा MISDN_LAYERMASK		0x00ff

/* generell commands */
#घोषणा OPEN_CHANNEL		0x0100
#घोषणा CLOSE_CHANNEL		0x0200
#घोषणा CONTROL_CHANNEL		0x0300
#घोषणा CHECK_DATA		0x0400

/* layer 2 -> layer 1 */
#घोषणा PH_ACTIVATE_REQ		0x0101
#घोषणा PH_DEACTIVATE_REQ	0x0201
#घोषणा PH_DATA_REQ		0x2001
#घोषणा MPH_ACTIVATE_REQ	0x0501
#घोषणा MPH_DEACTIVATE_REQ	0x0601
#घोषणा MPH_INFORMATION_REQ	0x0701
#घोषणा PH_CONTROL_REQ		0x0801

/* layer 1 -> layer 2 */
#घोषणा PH_ACTIVATE_IND		0x0102
#घोषणा PH_ACTIVATE_CNF		0x4102
#घोषणा PH_DEACTIVATE_IND	0x0202
#घोषणा PH_DEACTIVATE_CNF	0x4202
#घोषणा PH_DATA_IND		0x2002
#घोषणा PH_DATA_E_IND		0x3002
#घोषणा MPH_ACTIVATE_IND	0x0502
#घोषणा MPH_DEACTIVATE_IND	0x0602
#घोषणा MPH_INFORMATION_IND	0x0702
#घोषणा PH_DATA_CNF		0x6002
#घोषणा PH_CONTROL_IND		0x0802
#घोषणा PH_CONTROL_CNF		0x4802

/* layer 3 -> layer 2 */
#घोषणा DL_ESTABLISH_REQ	0x1004
#घोषणा DL_RELEASE_REQ		0x1104
#घोषणा DL_DATA_REQ		0x3004
#घोषणा DL_UNITDATA_REQ		0x3104
#घोषणा DL_INFORMATION_REQ	0x0004

/* layer 2 -> layer 3 */
#घोषणा DL_ESTABLISH_IND	0x1008
#घोषणा DL_ESTABLISH_CNF	0x5008
#घोषणा DL_RELEASE_IND		0x1108
#घोषणा DL_RELEASE_CNF		0x5108
#घोषणा DL_DATA_IND		0x3008
#घोषणा DL_UNITDATA_IND		0x3108
#घोषणा DL_INFORMATION_IND	0x0008

/* पूर्णांकern layer 2 management */
#घोषणा MDL_ASSIGN_REQ		0x1804
#घोषणा MDL_ASSIGN_IND		0x1904
#घोषणा MDL_REMOVE_REQ		0x1A04
#घोषणा MDL_REMOVE_IND		0x1B04
#घोषणा MDL_STATUS_UP_IND	0x1C04
#घोषणा MDL_STATUS_DOWN_IND	0x1D04
#घोषणा MDL_STATUS_UI_IND	0x1E04
#घोषणा MDL_ERROR_IND		0x1F04
#घोषणा MDL_ERROR_RSP		0x5F04

/* पूर्णांकern layer 2 */
#घोषणा DL_TIMER200_IND		0x7004
#घोषणा DL_TIMER203_IND		0x7304
#घोषणा DL_INTERN_MSG		0x7804

/* DL_INFORMATION_IND types */
#घोषणा DL_INFO_L2_CONNECT	0x0001
#घोषणा DL_INFO_L2_REMOVED	0x0002

/* PH_CONTROL types */
/* TOUCH TONE IS 0x20XX  XX "0"..."9", "A","B","C","D","*","#" */
#घोषणा DTMF_TONE_VAL		0x2000
#घोषणा DTMF_TONE_MASK		0x007F
#घोषणा DTMF_TONE_START		0x2100
#घोषणा DTMF_TONE_STOP		0x2200
#घोषणा DTMF_HFC_COEF		0x4000
#घोषणा DSP_CONF_JOIN		0x2403
#घोषणा DSP_CONF_SPLIT		0x2404
#घोषणा DSP_RECEIVE_OFF		0x2405
#घोषणा DSP_RECEIVE_ON		0x2406
#घोषणा DSP_ECHO_ON		0x2407
#घोषणा DSP_ECHO_OFF		0x2408
#घोषणा DSP_MIX_ON		0x2409
#घोषणा DSP_MIX_OFF		0x240a
#घोषणा DSP_DELAY		0x240b
#घोषणा DSP_JITTER		0x240c
#घोषणा DSP_TXDATA_ON		0x240d
#घोषणा DSP_TXDATA_OFF		0x240e
#घोषणा DSP_TX_DEJITTER		0x240f
#घोषणा DSP_TX_DEJ_OFF		0x2410
#घोषणा DSP_TONE_PATT_ON	0x2411
#घोषणा DSP_TONE_PATT_OFF	0x2412
#घोषणा DSP_VOL_CHANGE_TX	0x2413
#घोषणा DSP_VOL_CHANGE_RX	0x2414
#घोषणा DSP_BF_ENABLE_KEY	0x2415
#घोषणा DSP_BF_DISABLE		0x2416
#घोषणा DSP_BF_ACCEPT		0x2416
#घोषणा DSP_BF_REJECT		0x2417
#घोषणा DSP_PIPELINE_CFG	0x2418
#घोषणा HFC_VOL_CHANGE_TX	0x2601
#घोषणा HFC_VOL_CHANGE_RX	0x2602
#घोषणा HFC_SPL_LOOP_ON		0x2603
#घोषणा HFC_SPL_LOOP_OFF	0x2604
/* क्रम T30 FAX and analog modem */
#घोषणा HW_MOD_FRM		0x4000
#घोषणा HW_MOD_FRH		0x4001
#घोषणा HW_MOD_FTM		0x4002
#घोषणा HW_MOD_FTH		0x4003
#घोषणा HW_MOD_FTS		0x4004
#घोषणा HW_MOD_CONNECT		0x4010
#घोषणा HW_MOD_OK		0x4011
#घोषणा HW_MOD_NOCARR		0x4012
#घोषणा HW_MOD_FCERROR		0x4013
#घोषणा HW_MOD_READY		0x4014
#घोषणा HW_MOD_LASTDATA		0x4015

/* DSP_TONE_PATT_ON parameter */
#घोषणा TONE_OFF			0x0000
#घोषणा TONE_GERMAN_DIALTONE		0x0001
#घोषणा TONE_GERMAN_OLDDIALTONE		0x0002
#घोषणा TONE_AMERICAN_DIALTONE		0x0003
#घोषणा TONE_GERMAN_DIALPBX		0x0004
#घोषणा TONE_GERMAN_OLDDIALPBX		0x0005
#घोषणा TONE_AMERICAN_DIALPBX		0x0006
#घोषणा TONE_GERMAN_RINGING		0x0007
#घोषणा TONE_GERMAN_OLDRINGING		0x0008
#घोषणा TONE_AMERICAN_RINGPBX		0x000b
#घोषणा TONE_GERMAN_RINGPBX		0x000c
#घोषणा TONE_GERMAN_OLDRINGPBX		0x000d
#घोषणा TONE_AMERICAN_RINGING		0x000e
#घोषणा TONE_GERMAN_BUSY		0x000f
#घोषणा TONE_GERMAN_OLDBUSY		0x0010
#घोषणा TONE_AMERICAN_BUSY		0x0011
#घोषणा TONE_GERMAN_HANGUP		0x0012
#घोषणा TONE_GERMAN_OLDHANGUP		0x0013
#घोषणा TONE_AMERICAN_HANGUP		0x0014
#घोषणा TONE_SPECIAL_INFO		0x0015
#घोषणा TONE_GERMAN_GASSENBESETZT	0x0016
#घोषणा TONE_GERMAN_AUFSCHALTTON	0x0016

/* MPH_INFORMATION_IND */
#घोषणा L1_SIGNAL_LOS_OFF	0x0010
#घोषणा L1_SIGNAL_LOS_ON	0x0011
#घोषणा L1_SIGNAL_AIS_OFF	0x0012
#घोषणा L1_SIGNAL_AIS_ON	0x0013
#घोषणा L1_SIGNAL_RDI_OFF	0x0014
#घोषणा L1_SIGNAL_RDI_ON	0x0015
#घोषणा L1_SIGNAL_SLIP_RX	0x0020
#घोषणा L1_SIGNAL_SLIP_TX	0x0021

/*
 * protocol ids
 * D channel 1-31
 * B channel 33 - 63
 */

#घोषणा ISDN_P_NONE		0
#घोषणा ISDN_P_BASE		0
#घोषणा ISDN_P_TE_S0		0x01
#घोषणा ISDN_P_NT_S0  		0x02
#घोषणा ISDN_P_TE_E1		0x03
#घोषणा ISDN_P_NT_E1  		0x04
#घोषणा ISDN_P_TE_UP0		0x05
#घोषणा ISDN_P_NT_UP0		0x06

#घोषणा IS_ISDN_P_TE(p) ((p == ISDN_P_TE_S0) || (p == ISDN_P_TE_E1) || \
				(p == ISDN_P_TE_UP0) || (p == ISDN_P_LAPD_TE))
#घोषणा IS_ISDN_P_NT(p) ((p == ISDN_P_NT_S0) || (p == ISDN_P_NT_E1) || \
				(p == ISDN_P_NT_UP0) || (p == ISDN_P_LAPD_NT))
#घोषणा IS_ISDN_P_S0(p) ((p == ISDN_P_TE_S0) || (p == ISDN_P_NT_S0))
#घोषणा IS_ISDN_P_E1(p) ((p == ISDN_P_TE_E1) || (p == ISDN_P_NT_E1))
#घोषणा IS_ISDN_P_UP0(p) ((p == ISDN_P_TE_UP0) || (p == ISDN_P_NT_UP0))


#घोषणा ISDN_P_LAPD_TE		0x10
#घोषणा	ISDN_P_LAPD_NT		0x11

#घोषणा ISDN_P_B_MASK		0x1f
#घोषणा ISDN_P_B_START		0x20

#घोषणा ISDN_P_B_RAW		0x21
#घोषणा ISDN_P_B_HDLC		0x22
#घोषणा ISDN_P_B_X75SLP		0x23
#घोषणा ISDN_P_B_L2DTMF		0x24
#घोषणा ISDN_P_B_L2DSP		0x25
#घोषणा ISDN_P_B_L2DSPHDLC	0x26
#घोषणा ISDN_P_B_T30_FAX	0x27
#घोषणा ISDN_P_B_MODEM_ASYNC	0x28

#घोषणा OPTION_L2_PMX		1
#घोषणा OPTION_L2_PTP		2
#घोषणा OPTION_L2_FIXEDTEI	3
#घोषणा OPTION_L2_CLEANUP	4
#घोषणा OPTION_L1_HOLD		5

/* should be in sync with linux/kobject.h:KOBJ_NAME_LEN */
#घोषणा MISDN_MAX_IDLEN		20

काष्ठा mISDNhead अणु
	अचिन्हित पूर्णांक	prim;
	अचिन्हित पूर्णांक	id;
पूर्ण  __packed;

#घोषणा MISDN_HEADER_LEN	माप(काष्ठा mISDNhead)
#घोषणा MAX_DATA_SIZE		2048
#घोषणा MAX_DATA_MEM		(MAX_DATA_SIZE + MISDN_HEADER_LEN)
#घोषणा MAX_DFRAME_LEN		260

#घोषणा MISDN_ID_ADDR_MASK	0xFFFF
#घोषणा MISDN_ID_TEI_MASK	0xFF00
#घोषणा MISDN_ID_SAPI_MASK	0x00FF
#घोषणा MISDN_ID_TEI_ANY	0x7F00

#घोषणा MISDN_ID_ANY		0xFFFF
#घोषणा MISDN_ID_NONE		0xFFFE

#घोषणा GROUP_TEI		127
#घोषणा TEI_SAPI		63
#घोषणा CTRL_SAPI		0

#घोषणा MISDN_MAX_CHANNEL	127
#घोषणा MISDN_CHMAP_SIZE	((MISDN_MAX_CHANNEL + 1) >> 3)

#घोषणा SOL_MISDN	0

काष्ठा sockaddr_mISDN अणु
	sa_family_t    family;
	अचिन्हित अक्षर	dev;
	अचिन्हित अक्षर	channel;
	अचिन्हित अक्षर	sapi;
	अचिन्हित अक्षर	tei;
पूर्ण;

काष्ठा mISDNversion अणु
	अचिन्हित अक्षर	major;
	अचिन्हित अक्षर	minor;
	अचिन्हित लघु	release;
पूर्ण;

काष्ठा mISDN_devinfo अणु
	u_पूर्णांक			id;
	u_पूर्णांक			Dprotocols;
	u_पूर्णांक			Bprotocols;
	u_पूर्णांक			protocol;
	u_अक्षर			channelmap[MISDN_CHMAP_SIZE];
	u_पूर्णांक			nrbchan;
	अक्षर			name[MISDN_MAX_IDLEN];
पूर्ण;

काष्ठा mISDN_devनाम अणु
	u_पूर्णांक			id;
	अक्षर			name[MISDN_MAX_IDLEN]; /* new name */
पूर्ण;

/* MPH_INFORMATION_REQ payload */
काष्ठा ph_info_ch अणु
	__u32 protocol;
	__u64 Flags;
पूर्ण;

काष्ठा ph_info_dch अणु
	काष्ठा ph_info_ch ch;
	__u16 state;
	__u16 num_bch;
पूर्ण;

काष्ठा ph_info अणु
	काष्ठा ph_info_dch dch;
	काष्ठा ph_info_ch  bch[];
पूर्ण;

/* समयr device ioctl */
#घोषणा IMADDTIMER	_IOR('I', 64, पूर्णांक)
#घोषणा IMDELTIMER	_IOR('I', 65, पूर्णांक)

/* socket ioctls */
#घोषणा	IMGETVERSION	_IOR('I', 66, पूर्णांक)
#घोषणा	IMGETCOUNT	_IOR('I', 67, पूर्णांक)
#घोषणा IMGETDEVINFO	_IOR('I', 68, पूर्णांक)
#घोषणा IMCTRLREQ	_IOR('I', 69, पूर्णांक)
#घोषणा IMCLEAR_L2	_IOR('I', 70, पूर्णांक)
#घोषणा IMSETDEVNAME	_IOR('I', 71, काष्ठा mISDN_devनाम)
#घोषणा IMHOLD_L1	_IOR('I', 72, पूर्णांक)

अटल अंतरभूत पूर्णांक
test_channelmap(u_पूर्णांक nr, u_अक्षर *map)
अणु
	अगर (nr <= MISDN_MAX_CHANNEL)
		वापस map[nr >> 3] & (1 << (nr & 7));
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम
set_channelmap(u_पूर्णांक nr, u_अक्षर *map)
अणु
	map[nr >> 3] |= (1 << (nr & 7));
पूर्ण

अटल अंतरभूत व्योम
clear_channelmap(u_पूर्णांक nr, u_अक्षर *map)
अणु
	map[nr >> 3] &= ~(1 << (nr & 7));
पूर्ण

/* CONTROL_CHANNEL parameters */
#घोषणा MISDN_CTRL_GETOP		0x0000
#घोषणा MISDN_CTRL_LOOP			0x0001
#घोषणा MISDN_CTRL_CONNECT		0x0002
#घोषणा MISDN_CTRL_DISCONNECT		0x0004
#घोषणा MISDN_CTRL_RX_BUFFER		0x0008
#घोषणा MISDN_CTRL_PCMCONNECT		0x0010
#घोषणा MISDN_CTRL_PCMDISCONNECT	0x0020
#घोषणा MISDN_CTRL_SETPEER		0x0040
#घोषणा MISDN_CTRL_UNSETPEER		0x0080
#घोषणा MISDN_CTRL_RX_OFF		0x0100
#घोषणा MISDN_CTRL_FILL_EMPTY		0x0200
#घोषणा MISDN_CTRL_GETPEER		0x0400
#घोषणा MISDN_CTRL_L1_TIMER3		0x0800
#घोषणा MISDN_CTRL_HW_FEATURES_OP	0x2000
#घोषणा MISDN_CTRL_HW_FEATURES		0x2001
#घोषणा MISDN_CTRL_HFC_OP		0x4000
#घोषणा MISDN_CTRL_HFC_PCM_CONN		0x4001
#घोषणा MISDN_CTRL_HFC_PCM_DISC		0x4002
#घोषणा MISDN_CTRL_HFC_CONF_JOIN	0x4003
#घोषणा MISDN_CTRL_HFC_CONF_SPLIT	0x4004
#घोषणा MISDN_CTRL_HFC_RECEIVE_OFF	0x4005
#घोषणा MISDN_CTRL_HFC_RECEIVE_ON	0x4006
#घोषणा MISDN_CTRL_HFC_ECHOCAN_ON 	0x4007
#घोषणा MISDN_CTRL_HFC_ECHOCAN_OFF 	0x4008
#घोषणा MISDN_CTRL_HFC_WD_INIT		0x4009
#घोषणा MISDN_CTRL_HFC_WD_RESET		0x400A

/* special RX buffer value क्रम MISDN_CTRL_RX_BUFFER request.p1 is the minimum
 * buffer size request.p2 the maximum. Using  MISDN_CTRL_RX_SIZE_IGNORE will
 * not change the value, but still पढ़ो back the actual stetting.
 */
#घोषणा MISDN_CTRL_RX_SIZE_IGNORE	-1

/* socket options */
#घोषणा MISDN_TIME_STAMP		0x0001

काष्ठा mISDN_ctrl_req अणु
	पूर्णांक		op;
	पूर्णांक		channel;
	पूर्णांक		p1;
	पूर्णांक		p2;
पूर्ण;

/* muxer options */
#घोषणा MISDN_OPT_ALL		1
#घोषणा MISDN_OPT_TEIMGR	2

#अगर_घोषित __KERNEL__
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <net/sock.h>
#समावेश <linux/completion.h>

#घोषणा DEBUG_CORE		0x000000ff
#घोषणा DEBUG_CORE_FUNC		0x00000002
#घोषणा DEBUG_SOCKET		0x00000004
#घोषणा DEBUG_MANAGER		0x00000008
#घोषणा DEBUG_SEND_ERR		0x00000010
#घोषणा DEBUG_MSG_THREAD	0x00000020
#घोषणा DEBUG_QUEUE_FUNC	0x00000040
#घोषणा DEBUG_L1		0x0000ff00
#घोषणा DEBUG_L1_FSM		0x00000200
#घोषणा DEBUG_L2		0x00ff0000
#घोषणा DEBUG_L2_FSM		0x00020000
#घोषणा DEBUG_L2_CTRL		0x00040000
#घोषणा DEBUG_L2_RECV		0x00080000
#घोषणा DEBUG_L2_TEI		0x00100000
#घोषणा DEBUG_L2_TEIFSM		0x00200000
#घोषणा DEBUG_TIMER		0x01000000
#घोषणा DEBUG_CLOCK		0x02000000

#घोषणा mISDN_HEAD_P(s)		((काष्ठा mISDNhead *)&s->cb[0])
#घोषणा mISDN_HEAD_PRIM(s)	(((काष्ठा mISDNhead *)&s->cb[0])->prim)
#घोषणा mISDN_HEAD_ID(s)	(((काष्ठा mISDNhead *)&s->cb[0])->id)

/* socket states */
#घोषणा MISDN_OPEN	1
#घोषणा MISDN_BOUND	2
#घोषणा MISDN_CLOSED	3

काष्ठा mISDNchannel;
काष्ठा mISDNdevice;
काष्ठा mISDNstack;
काष्ठा mISDNघड़ी;

काष्ठा channel_req अणु
	u_पूर्णांक			protocol;
	काष्ठा sockaddr_mISDN	adr;
	काष्ठा mISDNchannel	*ch;
पूर्ण;

प्रकार	पूर्णांक	(ctrl_func_t)(काष्ठा mISDNchannel *, u_पूर्णांक, व्योम *);
प्रकार	पूर्णांक	(send_func_t)(काष्ठा mISDNchannel *, काष्ठा sk_buff *);
प्रकार पूर्णांक	(create_func_t)(काष्ठा channel_req *);

काष्ठा Bprotocol अणु
	काष्ठा list_head	list;
	अक्षर			*name;
	u_पूर्णांक			Bprotocols;
	create_func_t		*create;
पूर्ण;

काष्ठा mISDNchannel अणु
	काष्ठा list_head	list;
	u_पूर्णांक			protocol;
	u_पूर्णांक			nr;
	u_दीर्घ			opt;
	u_पूर्णांक			addr;
	काष्ठा mISDNstack	*st;
	काष्ठा mISDNchannel	*peer;
	send_func_t		*send;
	send_func_t		*recv;
	ctrl_func_t		*ctrl;
पूर्ण;

काष्ठा mISDN_sock_list अणु
	काष्ठा hlist_head	head;
	rwlock_t		lock;
पूर्ण;

काष्ठा mISDN_sock अणु
	काष्ठा sock		sk;
	काष्ठा mISDNchannel	ch;
	u_पूर्णांक			cmask;
	काष्ठा mISDNdevice	*dev;
पूर्ण;



काष्ठा mISDNdevice अणु
	काष्ठा mISDNchannel	D;
	u_पूर्णांक			id;
	u_पूर्णांक			Dprotocols;
	u_पूर्णांक			Bprotocols;
	u_पूर्णांक			nrbchan;
	u_अक्षर			channelmap[MISDN_CHMAP_SIZE];
	काष्ठा list_head	bchannels;
	काष्ठा mISDNchannel	*teimgr;
	काष्ठा device		dev;
पूर्ण;

काष्ठा mISDNstack अणु
	u_दीर्घ			status;
	काष्ठा mISDNdevice	*dev;
	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा completion	*notअगरy;
	रुको_queue_head_t	workq;
	काष्ठा sk_buff_head	msgq;
	काष्ठा list_head	layer2;
	काष्ठा mISDNchannel	*layer1;
	काष्ठा mISDNchannel	own;
	काष्ठा mutex		lmutex; /* protect lists */
	काष्ठा mISDN_sock_list	l1sock;
#अगर_घोषित MISDN_MSG_STATS
	u_पूर्णांक			msg_cnt;
	u_पूर्णांक			sleep_cnt;
	u_पूर्णांक			stopped_cnt;
#पूर्ण_अगर
पूर्ण;

प्रकार	पूर्णांक	(घड़ीctl_func_t)(व्योम *, पूर्णांक);

काष्ठा	mISDNघड़ी अणु
	काष्ठा list_head	list;
	अक्षर			name[64];
	पूर्णांक			pri;
	घड़ीctl_func_t		*ctl;
	व्योम			*priv;
पूर्ण;

/* global alloc/queue functions */

अटल अंतरभूत काष्ठा sk_buff *
mI_alloc_skb(अचिन्हित पूर्णांक len, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff	*skb;

	skb = alloc_skb(len + MISDN_HEADER_LEN, gfp_mask);
	अगर (likely(skb))
		skb_reserve(skb, MISDN_HEADER_LEN);
	वापस skb;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
_alloc_mISDN_skb(u_पूर्णांक prim, u_पूर्णांक id, u_पूर्णांक len, व्योम *dp, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff	*skb = mI_alloc_skb(len, gfp_mask);
	काष्ठा mISDNhead *hh;

	अगर (!skb)
		वापस शून्य;
	अगर (len)
		skb_put_data(skb, dp, len);
	hh = mISDN_HEAD_P(skb);
	hh->prim = prim;
	hh->id = id;
	वापस skb;
पूर्ण

अटल अंतरभूत व्योम
_queue_data(काष्ठा mISDNchannel *ch, u_पूर्णांक prim,
    u_पूर्णांक id, u_पूर्णांक len, व्योम *dp, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff		*skb;

	अगर (!ch->peer)
		वापस;
	skb = _alloc_mISDN_skb(prim, id, len, dp, gfp_mask);
	अगर (!skb)
		वापस;
	अगर (ch->recv(ch->peer, skb))
		dev_kमुक्त_skb(skb);
पूर्ण

/* global रेजिस्टर/unरेजिस्टर functions */

बाह्य पूर्णांक	mISDN_रेजिस्टर_device(काष्ठा mISDNdevice *,
					काष्ठा device *parent, अक्षर *name);
बाह्य व्योम	mISDN_unरेजिस्टर_device(काष्ठा mISDNdevice *);
बाह्य पूर्णांक	mISDN_रेजिस्टर_Bprotocol(काष्ठा Bprotocol *);
बाह्य व्योम	mISDN_unरेजिस्टर_Bprotocol(काष्ठा Bprotocol *);
बाह्य काष्ठा mISDNघड़ी *mISDN_रेजिस्टर_घड़ी(अक्षर *, पूर्णांक, घड़ीctl_func_t *,
						व्योम *);
बाह्य व्योम	mISDN_unरेजिस्टर_घड़ी(काष्ठा mISDNघड़ी *);

अटल अंतरभूत काष्ठा mISDNdevice *dev_to_mISDN(काष्ठा device *dev)
अणु
	अगर (dev)
		वापस dev_get_drvdata(dev);
	अन्यथा
		वापस शून्य;
पूर्ण

बाह्य व्योम	set_channel_address(काष्ठा mISDNchannel *, u_पूर्णांक, u_पूर्णांक);
बाह्य व्योम	mISDN_घड़ी_update(काष्ठा mISDNघड़ी *, पूर्णांक, kसमय_प्रकार *);
बाह्य अचिन्हित लघु mISDN_घड़ी_get(व्योम);
बाह्य स्थिर अक्षर *mISDNDevName4ch(काष्ठा mISDNchannel *);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* mISDNIF_H */

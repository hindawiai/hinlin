<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* PPTP स्थिरants and काष्ठाs */
#अगर_अघोषित _NF_CONNTRACK_PPTP_H
#घोषणा _NF_CONNTRACK_PPTP_H

#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <uapi/linux/netfilter/nf_conntrack_tuple_common.h>

स्थिर अक्षर *pptp_msg_name(u_पूर्णांक16_t msg);

/* state of the control session */
क्रमागत pptp_ctrlsess_state अणु
	PPTP_SESSION_NONE,			/* no session present */
	PPTP_SESSION_ERROR,			/* some session error */
	PPTP_SESSION_STOPREQ,			/* stop_sess request seen */
	PPTP_SESSION_REQUESTED,			/* start_sess request seen */
	PPTP_SESSION_CONFIRMED,			/* session established */
पूर्ण;

/* state of the call inside the control session */
क्रमागत pptp_ctrlcall_state अणु
	PPTP_CALL_NONE,
	PPTP_CALL_ERROR,
	PPTP_CALL_OUT_REQ,
	PPTP_CALL_OUT_CONF,
	PPTP_CALL_IN_REQ,
	PPTP_CALL_IN_REP,
	PPTP_CALL_IN_CONF,
	PPTP_CALL_CLEAR_REQ,
पूर्ण;

/* conntrack निजी data */
काष्ठा nf_ct_pptp_master अणु
	क्रमागत pptp_ctrlsess_state sstate;	/* session state */
	क्रमागत pptp_ctrlcall_state cstate;	/* call state */
	__be16 pac_call_id;			/* call id of PAC */
	__be16 pns_call_id;			/* call id of PNS */

	/* in pre-2.6.11 this used to be per-expect. Now it is per-conntrack
	 * and thereक्रमe imposes a fixed limit on the number of maps */
	काष्ठा nf_ct_gre_keymap *keymap[IP_CT_सूची_MAX];
पूर्ण;

काष्ठा nf_nat_pptp अणु
	__be16 pns_call_id;			/* NAT'ed PNS call id */
	__be16 pac_call_id;			/* NAT'ed PAC call id */
पूर्ण;

#घोषणा PPTP_CONTROL_PORT	1723

#घोषणा PPTP_PACKET_CONTROL	1
#घोषणा PPTP_PACKET_MGMT	2

#घोषणा PPTP_MAGIC_COOKIE	0x1a2b3c4d

काष्ठा pptp_pkt_hdr अणु
	__u16	packetLength;
	__be16	packetType;
	__be32	magicCookie;
पूर्ण;

/* PptpControlMessageType values */
#घोषणा PPTP_START_SESSION_REQUEST	1
#घोषणा PPTP_START_SESSION_REPLY	2
#घोषणा PPTP_STOP_SESSION_REQUEST	3
#घोषणा PPTP_STOP_SESSION_REPLY		4
#घोषणा PPTP_ECHO_REQUEST		5
#घोषणा PPTP_ECHO_REPLY			6
#घोषणा PPTP_OUT_CALL_REQUEST		7
#घोषणा PPTP_OUT_CALL_REPLY		8
#घोषणा PPTP_IN_CALL_REQUEST		9
#घोषणा PPTP_IN_CALL_REPLY		10
#घोषणा PPTP_IN_CALL_CONNECT		11
#घोषणा PPTP_CALL_CLEAR_REQUEST		12
#घोषणा PPTP_CALL_DISCONNECT_NOTIFY	13
#घोषणा PPTP_WAN_ERROR_NOTIFY		14
#घोषणा PPTP_SET_LINK_INFO		15

#घोषणा PPTP_MSG_MAX			15

/* PptpGeneralError values */
#घोषणा PPTP_ERROR_CODE_NONE		0
#घोषणा PPTP_NOT_CONNECTED		1
#घोषणा PPTP_BAD_FORMAT			2
#घोषणा PPTP_BAD_VALUE			3
#घोषणा PPTP_NO_RESOURCE		4
#घोषणा PPTP_BAD_CALLID			5
#घोषणा PPTP_REMOVE_DEVICE_ERROR	6

काष्ठा PptpControlHeader अणु
	__be16	messageType;
	__u16	reserved;
पूर्ण;

/* FramingCapability Biपंचांगap Values */
#घोषणा PPTP_FRAME_CAP_ASYNC		0x1
#घोषणा PPTP_FRAME_CAP_SYNC		0x2

/* BearerCapability Biपंचांगap Values */
#घोषणा PPTP_BEARER_CAP_ANALOG		0x1
#घोषणा PPTP_BEARER_CAP_DIGITAL		0x2

काष्ठा PptpStartSessionRequest अणु
	__be16	protocolVersion;
	__u16	reserved1;
	__be32	framingCapability;
	__be32	bearerCapability;
	__be16	maxChannels;
	__be16	firmwareRevision;
	__u8	hostName[64];
	__u8	venकरोrString[64];
पूर्ण;

/* PptpStartSessionResultCode Values */
#घोषणा PPTP_START_OK			1
#घोषणा PPTP_START_GENERAL_ERROR	2
#घोषणा PPTP_START_ALREADY_CONNECTED	3
#घोषणा PPTP_START_NOT_AUTHORIZED	4
#घोषणा PPTP_START_UNKNOWN_PROTOCOL	5

काष्ठा PptpStartSessionReply अणु
	__be16	protocolVersion;
	__u8	resultCode;
	__u8	generalErrorCode;
	__be32	framingCapability;
	__be32	bearerCapability;
	__be16	maxChannels;
	__be16	firmwareRevision;
	__u8	hostName[64];
	__u8	venकरोrString[64];
पूर्ण;

/* PptpStopReasons */
#घोषणा PPTP_STOP_NONE			1
#घोषणा PPTP_STOP_PROTOCOL		2
#घोषणा PPTP_STOP_LOCAL_SHUTDOWN	3

काष्ठा PptpStopSessionRequest अणु
	__u8	reason;
	__u8	reserved1;
	__u16	reserved2;
पूर्ण;

/* PptpStopSessionResultCode */
#घोषणा PPTP_STOP_OK			1
#घोषणा PPTP_STOP_GENERAL_ERROR		2

काष्ठा PptpStopSessionReply अणु
	__u8	resultCode;
	__u8	generalErrorCode;
	__u16	reserved1;
पूर्ण;

काष्ठा PptpEchoRequest अणु
	__be32 identNumber;
पूर्ण;

/* PptpEchoReplyResultCode */
#घोषणा PPTP_ECHO_OK			1
#घोषणा PPTP_ECHO_GENERAL_ERROR		2

काष्ठा PptpEchoReply अणु
	__be32	identNumber;
	__u8	resultCode;
	__u8	generalErrorCode;
	__u16	reserved;
पूर्ण;

/* PptpFramingType */
#घोषणा PPTP_ASYNC_FRAMING		1
#घोषणा PPTP_SYNC_FRAMING		2
#घोषणा PPTP_DONT_CARE_FRAMING		3

/* PptpCallBearerType */
#घोषणा PPTP_ANALOG_TYPE		1
#घोषणा PPTP_DIGITAL_TYPE		2
#घोषणा PPTP_DONT_CARE_BEARER_TYPE	3

काष्ठा PptpOutCallRequest अणु
	__be16	callID;
	__be16	callSerialNumber;
	__be32	minBPS;
	__be32	maxBPS;
	__be32	bearerType;
	__be32	framingType;
	__be16	packetWinकरोw;
	__be16	packetProcDelay;
	__be16	phoneNumberLength;
	__u16	reserved1;
	__u8	phoneNumber[64];
	__u8	subAddress[64];
पूर्ण;

/* PptpCallResultCode */
#घोषणा PPTP_OUTCALL_CONNECT		1
#घोषणा PPTP_OUTCALL_GENERAL_ERROR	2
#घोषणा PPTP_OUTCALL_NO_CARRIER		3
#घोषणा PPTP_OUTCALL_BUSY		4
#घोषणा PPTP_OUTCALL_NO_DIAL_TONE	5
#घोषणा PPTP_OUTCALL_TIMEOUT		6
#घोषणा PPTP_OUTCALL_DONT_ACCEPT	7

काष्ठा PptpOutCallReply अणु
	__be16	callID;
	__be16	peersCallID;
	__u8	resultCode;
	__u8	generalErrorCode;
	__be16	causeCode;
	__be32	connectSpeed;
	__be16	packetWinकरोw;
	__be16	packetProcDelay;
	__be32	physChannelID;
पूर्ण;

काष्ठा PptpInCallRequest अणु
	__be16	callID;
	__be16	callSerialNumber;
	__be32	callBearerType;
	__be32	physChannelID;
	__be16	dialedNumberLength;
	__be16	dialingNumberLength;
	__u8	dialedNumber[64];
	__u8	dialingNumber[64];
	__u8	subAddress[64];
पूर्ण;

/* PptpInCallResultCode */
#घोषणा PPTP_INCALL_ACCEPT		1
#घोषणा PPTP_INCALL_GENERAL_ERROR	2
#घोषणा PPTP_INCALL_DONT_ACCEPT		3

काष्ठा PptpInCallReply अणु
	__be16	callID;
	__be16	peersCallID;
	__u8	resultCode;
	__u8	generalErrorCode;
	__be16	packetWinकरोw;
	__be16	packetProcDelay;
	__u16	reserved;
पूर्ण;

काष्ठा PptpInCallConnected अणु
	__be16	peersCallID;
	__u16	reserved;
	__be32	connectSpeed;
	__be16	packetWinकरोw;
	__be16	packetProcDelay;
	__be32	callFramingType;
पूर्ण;

काष्ठा PptpClearCallRequest अणु
	__be16	callID;
	__u16	reserved;
पूर्ण;

काष्ठा PptpCallDisconnectNotअगरy अणु
	__be16	callID;
	__u8	resultCode;
	__u8	generalErrorCode;
	__be16	causeCode;
	__u16	reserved;
	__u8	callStatistics[128];
पूर्ण;

काष्ठा PptpWanErrorNotअगरy अणु
	__be16	peersCallID;
	__u16	reserved;
	__be32	crcErrors;
	__be32	framingErrors;
	__be32	hardwareOverRuns;
	__be32	bufferOverRuns;
	__be32	समयoutErrors;
	__be32	alignmentErrors;
पूर्ण;

काष्ठा PptpSetLinkInfo अणु
	__be16	peersCallID;
	__u16	reserved;
	__be32	sendAccm;
	__be32	recvAccm;
पूर्ण;

जोड़ pptp_ctrl_जोड़ अणु
	काष्ठा PptpStartSessionRequest	sreq;
	काष्ठा PptpStartSessionReply	srep;
	काष्ठा PptpStopSessionRequest	streq;
	काष्ठा PptpStopSessionReply	strep;
	काष्ठा PptpOutCallRequest	ocreq;
	काष्ठा PptpOutCallReply		ocack;
	काष्ठा PptpInCallRequest	icreq;
	काष्ठा PptpInCallReply		icack;
	काष्ठा PptpInCallConnected	iccon;
	काष्ठा PptpClearCallRequest	clrreq;
	काष्ठा PptpCallDisconnectNotअगरy disc;
	काष्ठा PptpWanErrorNotअगरy	wanerr;
	काष्ठा PptpSetLinkInfo		setlink;
पूर्ण;

बाह्य पूर्णांक
(*nf_nat_pptp_hook_outbound)(काष्ठा sk_buff *skb,
			     काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			     अचिन्हित पूर्णांक protoff,
			     काष्ठा PptpControlHeader *ctlh,
			     जोड़ pptp_ctrl_जोड़ *pptpReq);

बाह्य पूर्णांक
(*nf_nat_pptp_hook_inbound)(काष्ठा sk_buff *skb,
			    काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			    अचिन्हित पूर्णांक protoff,
			    काष्ठा PptpControlHeader *ctlh,
			    जोड़ pptp_ctrl_जोड़ *pptpReq);

बाह्य व्योम
(*nf_nat_pptp_hook_exp_gre)(काष्ठा nf_conntrack_expect *exp_orig,
			    काष्ठा nf_conntrack_expect *exp_reply);

बाह्य व्योम
(*nf_nat_pptp_hook_expectfn)(काष्ठा nf_conn *ct,
			     काष्ठा nf_conntrack_expect *exp);

#पूर्ण_अगर /* _NF_CONNTRACK_PPTP_H */

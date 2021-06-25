<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_PARAMETERS_H
#घोषणा ISCSI_PARAMETERS_H

#समावेश <linux/types.h>
#समावेश <scsi/iscsi_proto.h>

काष्ठा iscsi_extra_response अणु
	अक्षर key[KEY_MAXLEN];
	अक्षर value[32];
	काष्ठा list_head er_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_param अणु
	अक्षर *name;
	अक्षर *value;
	u8 set_param;
	u8 phase;
	u8 scope;
	u8 sender;
	u8 type;
	u8 use;
	u16 type_range;
	u32 state;
	काष्ठा list_head p_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_conn;
काष्ठा iscsi_conn_ops;
काष्ठा iscsi_param_list;
काष्ठा iscsi_sess_ops;

बाह्य पूर्णांक iscsi_login_rx_data(काष्ठा iscsi_conn *, अक्षर *, पूर्णांक);
बाह्य पूर्णांक iscsi_login_tx_data(काष्ठा iscsi_conn *, अक्षर *, अक्षर *, पूर्णांक);
बाह्य व्योम iscsi_dump_conn_ops(काष्ठा iscsi_conn_ops *);
बाह्य व्योम iscsi_dump_sess_ops(काष्ठा iscsi_sess_ops *);
बाह्य व्योम iscsi_prपूर्णांक_params(काष्ठा iscsi_param_list *);
बाह्य पूर्णांक iscsi_create_शेष_params(काष्ठा iscsi_param_list **);
बाह्य पूर्णांक iscsi_set_keys_to_negotiate(काष्ठा iscsi_param_list *, bool);
बाह्य पूर्णांक iscsi_set_keys_irrelevant_क्रम_discovery(काष्ठा iscsi_param_list *);
बाह्य पूर्णांक iscsi_copy_param_list(काष्ठा iscsi_param_list **,
			काष्ठा iscsi_param_list *, पूर्णांक);
बाह्य पूर्णांक iscsi_change_param_value(अक्षर *, काष्ठा iscsi_param_list *, पूर्णांक);
बाह्य व्योम iscsi_release_param_list(काष्ठा iscsi_param_list *);
बाह्य काष्ठा iscsi_param *iscsi_find_param_from_key(अक्षर *, काष्ठा iscsi_param_list *);
बाह्य पूर्णांक iscsi_extract_key_value(अक्षर *, अक्षर **, अक्षर **);
बाह्य पूर्णांक iscsi_update_param_value(काष्ठा iscsi_param *, अक्षर *);
बाह्य पूर्णांक iscsi_decode_text_input(u8, u8, अक्षर *, u32, काष्ठा iscsi_conn *);
बाह्य पूर्णांक iscsi_encode_text_output(u8, u8, अक्षर *, u32 *,
			काष्ठा iscsi_param_list *, bool);
बाह्य पूर्णांक iscsi_check_negotiated_keys(काष्ठा iscsi_param_list *);
बाह्य व्योम iscsi_set_connection_parameters(काष्ठा iscsi_conn_ops *,
			काष्ठा iscsi_param_list *);
बाह्य व्योम iscsi_set_session_parameters(काष्ठा iscsi_sess_ops *,
			काष्ठा iscsi_param_list *, पूर्णांक);

#घोषणा YES				"Yes"
#घोषणा NO				"No"
#घोषणा ALL				"All"
#घोषणा IRRELEVANT			"Irrelevant"
#घोषणा NONE				"None"
#घोषणा NOTUNDERSTOOD			"NotUnderstood"
#घोषणा REJECT				"Reject"

/*
 * The Parameter Names.
 */
#घोषणा AUTHMETHOD			"AuthMethod"
#घोषणा HEADERDIGEST			"HeaderDigest"
#घोषणा DATADIGEST			"DataDigest"
#घोषणा MAXCONNECTIONS			"MaxConnections"
#घोषणा SENDTARGETS			"SendTargets"
#घोषणा TARGETNAME			"TargetName"
#घोषणा INITIATORNAME			"InitiatorName"
#घोषणा TARGETALIAS			"TargetAlias"
#घोषणा INITIATORALIAS			"InitiatorAlias"
#घोषणा TARGETADDRESS			"TargetAddress"
#घोषणा TARGETPORTALGROUPTAG		"TargetPortalGroupTag"
#घोषणा INITIALR2T			"InitialR2T"
#घोषणा IMMEDIATEDATA			"ImmediateData"
#घोषणा MAXRECVDATASEGMENTLENGTH	"MaxRecvDataSegmentLength"
#घोषणा MAXXMITDATASEGMENTLENGTH	"MaxXmitDataSegmentLength"
#घोषणा MAXBURSTLENGTH			"MaxBurstLength"
#घोषणा FIRSTBURSTLENGTH		"FirstBurstLength"
#घोषणा DEFAULTTIME2WAIT		"DefaultTime2Wait"
#घोषणा DEFAULTTIME2RETAIN		"DefaultTime2Retain"
#घोषणा MAXOUTSTANDINGR2T		"MaxOutstandingR2T"
#घोषणा DATAPDUINORDER			"DataPDUInOrder"
#घोषणा DATASEQUENCEINORDER		"DataSequenceInOrder"
#घोषणा ERRORRECOVERYLEVEL		"ErrorRecoveryLevel"
#घोषणा SESSIONTYPE			"SessionType"
#घोषणा IFMARKER			"IFMarker"
#घोषणा OFMARKER			"OFMarker"
#घोषणा IFMARKINT			"IFMarkInt"
#घोषणा OFMARKINT			"OFMarkInt"

/*
 * Parameter names of iSCSI Extentions क्रम RDMA (iSER).  See RFC-5046
 */
#घोषणा RDMAEXTENSIONS			"RDMAExtensions"
#घोषणा INITIATORRECVDATASEGMENTLENGTH	"InitiatorRecvDataSegmentLength"
#घोषणा TARGETRECVDATASEGMENTLENGTH	"TargetRecvDataSegmentLength"

/*
 * For AuthMethod.
 */
#घोषणा KRB5				"KRB5"
#घोषणा SPKM1				"SPKM1"
#घोषणा SPKM2				"SPKM2"
#घोषणा SRP				"SRP"
#घोषणा CHAP				"CHAP"

/*
 * Initial values क्रम Parameter Negotiation.
 */
#घोषणा INITIAL_AUTHMETHOD			CHAP
#घोषणा INITIAL_HEADERDIGEST			"CRC32C,None"
#घोषणा INITIAL_DATADIGEST			"CRC32C,None"
#घोषणा INITIAL_MAXCONNECTIONS			"1"
#घोषणा INITIAL_SENDTARGETS			ALL
#घोषणा INITIAL_TARGETNAME			"LIO.Target"
#घोषणा INITIAL_INITIATORNAME			"LIO.Initiator"
#घोषणा INITIAL_TARGETALIAS			"LIO Target"
#घोषणा INITIAL_INITIATORALIAS			"LIO Initiator"
#घोषणा INITIAL_TARGETADDRESS			"0.0.0.0:0000,0"
#घोषणा INITIAL_TARGETPORTALGROUPTAG		"1"
#घोषणा INITIAL_INITIALR2T			YES
#घोषणा INITIAL_IMMEDIATEDATA			YES
#घोषणा INITIAL_MAXRECVDATASEGMENTLENGTH	"8192"
/*
 * Match outgoing MXDSL शेष to incoming Open-iSCSI शेष
 */
#घोषणा INITIAL_MAXXMITDATASEGMENTLENGTH	"262144"
#घोषणा INITIAL_MAXBURSTLENGTH			"262144"
#घोषणा INITIAL_FIRSTBURSTLENGTH		"65536"
#घोषणा INITIAL_DEFAULTTIME2WAIT		"2"
#घोषणा INITIAL_DEFAULTTIME2RETAIN		"20"
#घोषणा INITIAL_MAXOUTSTANDINGR2T		"1"
#घोषणा INITIAL_DATAPDUINORDER			YES
#घोषणा INITIAL_DATASEQUENCEINORDER		YES
#घोषणा INITIAL_ERRORRECOVERYLEVEL		"0"
#घोषणा INITIAL_SESSIONTYPE			NORMAL
#घोषणा INITIAL_IFMARKER			NO
#घोषणा INITIAL_OFMARKER			NO
#घोषणा INITIAL_IFMARKINT			REJECT
#घोषणा INITIAL_OFMARKINT			REJECT

/*
 * Initial values क्रम iSER parameters following RFC-5046 Section 6
 */
#घोषणा INITIAL_RDMAEXTENSIONS			NO
#घोषणा INITIAL_INITIATORRECVDATASEGMENTLENGTH	"262144"
#घोषणा INITIAL_TARGETRECVDATASEGMENTLENGTH	"8192"

/*
 * For [Header,Data]Digests.
 */
#घोषणा CRC32C				"CRC32C"

/*
 * For SessionType.
 */
#घोषणा DISCOVERY			"Discovery"
#घोषणा NORMAL				"Normal"

/*
 * काष्ठा iscsi_param->use
 */
#घोषणा USE_LEADING_ONLY		0x01
#घोषणा USE_INITIAL_ONLY		0x02
#घोषणा USE_ALL				0x04

#घोषणा IS_USE_LEADING_ONLY(p)		((p)->use & USE_LEADING_ONLY)
#घोषणा IS_USE_INITIAL_ONLY(p)		((p)->use & USE_INITIAL_ONLY)
#घोषणा IS_USE_ALL(p)			((p)->use & USE_ALL)

#घोषणा SET_USE_INITIAL_ONLY(p)		((p)->use |= USE_INITIAL_ONLY)

/*
 * काष्ठा iscsi_param->sender
 */
#घोषणा	SENDER_INITIATOR		0x01
#घोषणा SENDER_TARGET			0x02
#घोषणा SENDER_BOTH			0x03
/* Used in iscsi_check_key() */
#घोषणा SENDER_RECEIVER			0x04

#घोषणा IS_SENDER_INITIATOR(p)		((p)->sender & SENDER_INITIATOR)
#घोषणा IS_SENDER_TARGET(p)		((p)->sender & SENDER_TARGET)
#घोषणा IS_SENDER_BOTH(p)		((p)->sender & SENDER_BOTH)

/*
 * काष्ठा iscsi_param->scope
 */
#घोषणा SCOPE_CONNECTION_ONLY		0x01
#घोषणा SCOPE_SESSION_WIDE		0x02

#घोषणा IS_SCOPE_CONNECTION_ONLY(p)	((p)->scope & SCOPE_CONNECTION_ONLY)
#घोषणा IS_SCOPE_SESSION_WIDE(p)	((p)->scope & SCOPE_SESSION_WIDE)

/*
 * काष्ठा iscsi_param->phase
 */
#घोषणा PHASE_SECURITY			0x01
#घोषणा PHASE_OPERATIONAL		0x02
#घोषणा PHASE_DECLARATIVE		0x04
#घोषणा PHASE_FFP0			0x08

#घोषणा IS_PHASE_SECURITY(p)		((p)->phase & PHASE_SECURITY)
#घोषणा IS_PHASE_OPERATIONAL(p)		((p)->phase & PHASE_OPERATIONAL)
#घोषणा IS_PHASE_DECLARATIVE(p)		((p)->phase & PHASE_DECLARATIVE)
#घोषणा IS_PHASE_FFP0(p)		((p)->phase & PHASE_FFP0)

/*
 * काष्ठा iscsi_param->type
 */
#घोषणा TYPE_BOOL_AND			0x01
#घोषणा TYPE_BOOL_OR			0x02
#घोषणा TYPE_NUMBER			0x04
#घोषणा TYPE_NUMBER_RANGE		0x08
#घोषणा TYPE_STRING			0x10
#घोषणा TYPE_VALUE_LIST			0x20

#घोषणा IS_TYPE_BOOL_AND(p)		((p)->type & TYPE_BOOL_AND)
#घोषणा IS_TYPE_BOOL_OR(p)		((p)->type & TYPE_BOOL_OR)
#घोषणा IS_TYPE_NUMBER(p)		((p)->type & TYPE_NUMBER)
#घोषणा IS_TYPE_NUMBER_RANGE(p)		((p)->type & TYPE_NUMBER_RANGE)
#घोषणा IS_TYPE_STRING(p)		((p)->type & TYPE_STRING)
#घोषणा IS_TYPE_VALUE_LIST(p)		((p)->type & TYPE_VALUE_LIST)

/*
 * काष्ठा iscsi_param->type_range
 */
#घोषणा TYPदुस्फल_BOOL_AND		0x0001
#घोषणा TYPदुस्फल_BOOL_OR		0x0002
#घोषणा TYPदुस्फल_0_TO_2		0x0004
#घोषणा TYPदुस्फल_0_TO_3600		0x0008
#घोषणा TYPदुस्फल_0_TO_32767		0x0010
#घोषणा TYPदुस्फल_0_TO_65535		0x0020
#घोषणा TYPदुस्फल_1_TO_65535		0x0040
#घोषणा TYPदुस्फल_2_TO_3600		0x0080
#घोषणा TYPदुस्फल_512_TO_16777215	0x0100
#घोषणा TYPदुस्फल_AUTH			0x0200
#घोषणा TYPदुस्फल_DIGEST		0x0400
#घोषणा TYPदुस्फल_ISCSINAME		0x0800
#घोषणा TYPदुस्फल_SESSIONTYPE		0x1000
#घोषणा TYPदुस्फल_TARGETADDRESS		0x2000
#घोषणा TYPदुस्फल_UTF8			0x4000

#घोषणा IS_TYPदुस्फल_0_TO_2(p)		((p)->type_range & TYPदुस्फल_0_TO_2)
#घोषणा IS_TYPदुस्फल_0_TO_3600(p)	((p)->type_range & TYPदुस्फल_0_TO_3600)
#घोषणा IS_TYPदुस्फल_0_TO_32767(p)	((p)->type_range & TYPदुस्फल_0_TO_32767)
#घोषणा IS_TYPदुस्फल_0_TO_65535(p)	((p)->type_range & TYPदुस्फल_0_TO_65535)
#घोषणा IS_TYPदुस्फल_1_TO_65535(p)	((p)->type_range & TYPदुस्फल_1_TO_65535)
#घोषणा IS_TYPदुस्फल_2_TO_3600(p)	((p)->type_range & TYPदुस्फल_2_TO_3600)
#घोषणा IS_TYPदुस्फल_512_TO_16777215(p)	((p)->type_range & \
						TYPदुस्फल_512_TO_16777215)
#घोषणा IS_TYPदुस्फल_AUTH_PARAM(p)	((p)->type_range & TYPदुस्फल_AUTH)
#घोषणा IS_TYPदुस्फल_DIGEST_PARAM(p)	((p)->type_range & TYPदुस्फल_DIGEST)
#घोषणा IS_TYPदुस्फल_SESSIONTYPE(p)	((p)->type_range & \
						TYPदुस्फल_SESSIONTYPE)

/*
 * काष्ठा iscsi_param->state
 */
#घोषणा PSTATE_ACCEPTOR			0x01
#घोषणा PSTATE_NEGOTIATE		0x02
#घोषणा PSTATE_PROPOSER			0x04
#घोषणा PSTATE_IRRELEVANT		0x08
#घोषणा PSTATE_REJECT			0x10
#घोषणा PSTATE_REPLY_OPTIONAL		0x20
#घोषणा PSTATE_RESPONSE_GOT		0x40
#घोषणा PSTATE_RESPONSE_SENT		0x80

#घोषणा IS_PSTATE_ACCEPTOR(p)		((p)->state & PSTATE_ACCEPTOR)
#घोषणा IS_PSTATE_NEGOTIATE(p)		((p)->state & PSTATE_NEGOTIATE)
#घोषणा IS_PSTATE_PROPOSER(p)		((p)->state & PSTATE_PROPOSER)
#घोषणा IS_PSTATE_IRRELEVANT(p)		((p)->state & PSTATE_IRRELEVANT)
#घोषणा IS_PSTATE_REJECT(p)		((p)->state & PSTATE_REJECT)
#घोषणा IS_PSTATE_REPLY_OPTIONAL(p)	((p)->state & PSTATE_REPLY_OPTIONAL)
#घोषणा IS_PSTATE_RESPONSE_GOT(p)	((p)->state & PSTATE_RESPONSE_GOT)
#घोषणा IS_PSTATE_RESPONSE_SENT(p)	((p)->state & PSTATE_RESPONSE_SENT)

#घोषणा SET_PSTATE_ACCEPTOR(p)		((p)->state |= PSTATE_ACCEPTOR)
#घोषणा SET_PSTATE_NEGOTIATE(p)		((p)->state |= PSTATE_NEGOTIATE)
#घोषणा SET_PSTATE_PROPOSER(p)		((p)->state |= PSTATE_PROPOSER)
#घोषणा SET_PSTATE_IRRELEVANT(p)	((p)->state |= PSTATE_IRRELEVANT)
#घोषणा SET_PSTATE_REJECT(p)		((p)->state |= PSTATE_REJECT)
#घोषणा SET_PSTATE_REPLY_OPTIONAL(p)	((p)->state |= PSTATE_REPLY_OPTIONAL)
#घोषणा SET_PSTATE_RESPONSE_GOT(p)	((p)->state |= PSTATE_RESPONSE_GOT)
#घोषणा SET_PSTATE_RESPONSE_SENT(p)	((p)->state |= PSTATE_RESPONSE_SENT)

#पूर्ण_अगर /* ISCSI_PARAMETERS_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RFC 3720 (iSCSI) protocol data types
 *
 * Copyright (C) 2005 Dmitry Yusupov
 * Copyright (C) 2005 Alex Aizman
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 */

#अगर_अघोषित ISCSI_PROTO_H
#घोषणा ISCSI_PROTO_H

#समावेश <linux/types.h>
#समावेश <scsi/scsi.h>

#घोषणा ISCSI_DRAFT20_VERSION	0x00

/* शेष iSCSI listen port क्रम incoming connections */
#घोषणा ISCSI_LISTEN_PORT	3260

/* iSCSI header length */
#घोषणा ISCSI_HDR_LEN		48

/* iSCSI CRC32C length */
#घोषणा ISCSI_CRC_LEN		4

/* Padding word length */
#घोषणा ISCSI_PAD_LEN		4

/*
 * Serial Number Arithmetic, 32 bits, RFC1982
 */

अटल अंतरभूत पूर्णांक iscsi_sna_lt(u32 n1, u32 n2)
अणु
	वापस (s32)(n1 - n2) < 0;
पूर्ण

अटल अंतरभूत पूर्णांक iscsi_sna_lte(u32 n1, u32 n2)
अणु
	वापस (s32)(n1 - n2) <= 0;
पूर्ण

अटल अंतरभूत पूर्णांक iscsi_sna_gt(u32 n1, u32 n2)
अणु
	वापस (s32)(n1 - n2) > 0;
पूर्ण

अटल अंतरभूत पूर्णांक iscsi_sna_gte(u32 n1, u32 n2)
अणु
	वापस (s32)(n1 - n2) >= 0;
पूर्ण

/*
 * useful common(control and data pathes) macro
 */
#घोषणा ntoh24(p) (((p)[0] << 16) | ((p)[1] << 8) | ((p)[2]))
#घोषणा hton24(p, v) अणु \
        p[0] = (((v) >> 16) & 0xFF); \
        p[1] = (((v) >> 8) & 0xFF); \
        p[2] = ((v) & 0xFF); \
पूर्ण
#घोषणा zero_data(p) अणुp[0]=0;p[1]=0;p[2]=0;पूर्ण

/* initiator tags; opaque क्रम target */
प्रकार uपूर्णांक32_t __bitwise itt_t;
/* below makes sense only क्रम initiator that created this tag */
#घोषणा build_itt(itt, age) ((__क्रमce itt_t)\
	((itt) | ((age) << ISCSI_AGE_SHIFT)))
#घोषणा get_itt(itt) ((__क्रमce uपूर्णांक32_t)(itt_t)(itt) & ISCSI_ITT_MASK)
#घोषणा RESERVED_ITT ((__क्रमce itt_t)0xffffffff)

/*
 * iSCSI Template Message Header
 */
काष्ठा iscsi_hdr अणु
	uपूर्णांक8_t		opcode;
	uपूर्णांक8_t		flags;		/* Final bit */
	uपूर्णांक8_t		rsvd2[2];
	uपूर्णांक8_t		hlength;	/* AHSs total length */
	uपूर्णांक8_t		dlength[3];	/* Data length */
	काष्ठा scsi_lun	lun;
	itt_t		itt;		/* Initiator Task Tag, opaque क्रम target */
	__be32		ttt;		/* Target Task Tag */
	__be32		statsn;
	__be32		exp_statsn;
	__be32		max_statsn;
	uपूर्णांक8_t		other[12];
पूर्ण;

/************************* RFC 3720 Begin *****************************/

#घोषणा ISCSI_RESERVED_TAG		0xffffffff

/* Opcode encoding bits */
#घोषणा ISCSI_OP_RETRY			0x80
#घोषणा ISCSI_OP_IMMEDIATE		0x40
#घोषणा ISCSI_OPCODE_MASK		0x3F

/* Initiator Opcode values */
#घोषणा ISCSI_OP_NOOP_OUT		0x00
#घोषणा ISCSI_OP_SCSI_CMD		0x01
#घोषणा ISCSI_OP_SCSI_TMFUNC		0x02
#घोषणा ISCSI_OP_LOGIN			0x03
#घोषणा ISCSI_OP_TEXT			0x04
#घोषणा ISCSI_OP_SCSI_DATA_OUT		0x05
#घोषणा ISCSI_OP_LOGOUT			0x06
#घोषणा ISCSI_OP_SNACK			0x10

#घोषणा ISCSI_OP_VENDOR1_CMD		0x1c
#घोषणा ISCSI_OP_VENDOR2_CMD		0x1d
#घोषणा ISCSI_OP_VENDOR3_CMD		0x1e
#घोषणा ISCSI_OP_VENDOR4_CMD		0x1f

/* Target Opcode values */
#घोषणा ISCSI_OP_NOOP_IN		0x20
#घोषणा ISCSI_OP_SCSI_CMD_RSP		0x21
#घोषणा ISCSI_OP_SCSI_TMFUNC_RSP	0x22
#घोषणा ISCSI_OP_LOGIN_RSP		0x23
#घोषणा ISCSI_OP_TEXT_RSP		0x24
#घोषणा ISCSI_OP_SCSI_DATA_IN		0x25
#घोषणा ISCSI_OP_LOGOUT_RSP		0x26
#घोषणा ISCSI_OP_R2T			0x31
#घोषणा ISCSI_OP_ASYNC_EVENT		0x32
#घोषणा ISCSI_OP_REJECT			0x3f

काष्ठा iscsi_ahs_hdr अणु
	__be16 ahslength;
	uपूर्णांक8_t ahstype;
	uपूर्णांक8_t ahspec[5];
पूर्ण;

#घोषणा ISCSI_AHSTYPE_CDB		1
#घोषणा ISCSI_AHSTYPE_RLENGTH		2
#घोषणा ISCSI_CDB_SIZE			16

/* iSCSI PDU Header */
काष्ठा iscsi_scsi_req अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	__be16 rsvd2;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun lun;
	itt_t	 itt;	/* Initiator Task Tag */
	__be32 data_length;
	__be32 cmdsn;
	__be32 exp_statsn;
	uपूर्णांक8_t cdb[ISCSI_CDB_SIZE];	/* SCSI Command Block */
	/* Additional Data (Command Dependent) */
पूर्ण;

/* Command PDU flags */
#घोषणा ISCSI_FLAG_CMD_FINAL		0x80
#घोषणा ISCSI_FLAG_CMD_READ		0x40
#घोषणा ISCSI_FLAG_CMD_WRITE		0x20
#घोषणा ISCSI_FLAG_CMD_ATTR_MASK	0x07	/* 3 bits */

/* SCSI Command Attribute values */
#घोषणा ISCSI_ATTR_UNTAGGED		0
#घोषणा ISCSI_ATTR_SIMPLE		1
#घोषणा ISCSI_ATTR_ORDERED		2
#घोषणा ISCSI_ATTR_HEAD_OF_QUEUE	3
#घोषणा ISCSI_ATTR_ACA			4

काष्ठा iscsi_rlength_ahdr अणु
	__be16 ahslength;
	uपूर्णांक8_t ahstype;
	uपूर्णांक8_t reserved;
	__be32 पढ़ो_length;
पूर्ण;

/* Extended CDB AHS */
काष्ठा iscsi_ecdb_ahdr अणु
	__be16 ahslength;	/* CDB length - 15, including reserved byte */
	uपूर्णांक8_t ahstype;
	uपूर्णांक8_t reserved;
	/* 4-byte aligned extended CDB spillover */
	uपूर्णांक8_t ecdb[SCSI_MAX_VARLEN_CDB_SIZE - ISCSI_CDB_SIZE];
पूर्ण;

/* SCSI Response Header */
काष्ठा iscsi_scsi_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t response;
	uपूर्णांक8_t cmd_status;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd[8];
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	rsvd1;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	exp_datasn;
	__be32	bi_residual_count;
	__be32	residual_count;
	/* Response or Sense Data (optional) */
पूर्ण;

/* Command Response PDU flags */
#घोषणा ISCSI_FLAG_CMD_BIDI_OVERFLOW	0x10
#घोषणा ISCSI_FLAG_CMD_BIDI_UNDERFLOW	0x08
#घोषणा ISCSI_FLAG_CMD_OVERFLOW		0x04
#घोषणा ISCSI_FLAG_CMD_UNDERFLOW	0x02

/* iSCSI Status values. Valid अगर Rsp Selector bit is not set */
#घोषणा ISCSI_STATUS_CMD_COMPLETED	0
#घोषणा ISCSI_STATUS_TARGET_FAILURE	1
#घोषणा ISCSI_STATUS_SUBSYS_FAILURE	2

/* Asynchronous Event Header */
काष्ठा iscsi_async अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t rsvd3;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun	lun;
	uपूर्णांक8_t rsvd4[8];
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uपूर्णांक8_t async_event;
	uपूर्णांक8_t async_vcode;
	__be16	param1;
	__be16	param2;
	__be16	param3;
	uपूर्णांक8_t rsvd5[4];
पूर्ण;

/* iSCSI Event Codes */
#घोषणा ISCSI_ASYNC_MSG_SCSI_EVENT			0
#घोषणा ISCSI_ASYNC_MSG_REQUEST_LOGOUT			1
#घोषणा ISCSI_ASYNC_MSG_DROPPING_CONNECTION		2
#घोषणा ISCSI_ASYNC_MSG_DROPPING_ALL_CONNECTIONS	3
#घोषणा ISCSI_ASYNC_MSG_PARAM_NEGOTIATION		4
#घोषणा ISCSI_ASYNC_MSG_VENDOR_SPECIFIC			255

/* NOP-Out Message */
काष्ठा iscsi_nopout अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	__be16	rsvd2;
	uपूर्णांक8_t rsvd3;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun	lun;
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	ttt;	/* Target Transfer Tag */
	__be32	cmdsn;
	__be32	exp_statsn;
	uपूर्णांक8_t rsvd4[16];
पूर्ण;

/* NOP-In Message */
काष्ठा iscsi_nopin अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	__be16	rsvd2;
	uपूर्णांक8_t rsvd3;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun	lun;
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	ttt;	/* Target Transfer Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uपूर्णांक8_t rsvd4[12];
पूर्ण;

/* SCSI Task Management Message Header */
काष्ठा iscsi_पंचांग अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd1[2];
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun lun;
	itt_t	 itt;	/* Initiator Task Tag */
	itt_t	 rtt;	/* Reference Task Tag */
	__be32	cmdsn;
	__be32	exp_statsn;
	__be32	refcmdsn;
	__be32	exp_datasn;
	uपूर्णांक8_t rsvd2[8];
पूर्ण;

#घोषणा ISCSI_FLAG_TM_FUNC_MASK			0x7F

/* Function values */
#घोषणा ISCSI_TM_FUNC_ABORT_TASK		1
#घोषणा ISCSI_TM_FUNC_ABORT_TASK_SET		2
#घोषणा ISCSI_TM_FUNC_CLEAR_ACA			3
#घोषणा ISCSI_TM_FUNC_CLEAR_TASK_SET		4
#घोषणा ISCSI_TM_FUNC_LOGICAL_UNIT_RESET	5
#घोषणा ISCSI_TM_FUNC_TARGET_WARM_RESET		6
#घोषणा ISCSI_TM_FUNC_TARGET_COLD_RESET		7
#घोषणा ISCSI_TM_FUNC_TASK_REASSIGN		8

#घोषणा ISCSI_TM_FUNC_VALUE(hdr) ((hdr)->flags & ISCSI_FLAG_TM_FUNC_MASK)

/* SCSI Task Management Response Header */
काष्ठा iscsi_पंचांग_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t response;	/* see Response values below */
	uपूर्णांक8_t qualअगरier;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd2[8];
	itt_t	 itt;	/* Initiator Task Tag */
	itt_t	 rtt;	/* Reference Task Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uपूर्णांक8_t rsvd3[12];
पूर्ण;

/* Response values */
#घोषणा ISCSI_TMF_RSP_COMPLETE		0x00
#घोषणा ISCSI_TMF_RSP_NO_TASK		0x01
#घोषणा ISCSI_TMF_RSP_NO_LUN		0x02
#घोषणा ISCSI_TMF_RSP_TASK_ALLEGIANT	0x03
#घोषणा ISCSI_TMF_RSP_NO_FAILOVER	0x04
#घोषणा ISCSI_TMF_RSP_NOT_SUPPORTED	0x05
#घोषणा ISCSI_TMF_RSP_AUTH_FAILED	0x06
#घोषणा ISCSI_TMF_RSP_REJECTED		0xff

/* Ready To Transfer Header */
काष्ठा iscsi_r2t_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t	hlength;
	uपूर्णांक8_t	dlength[3];
	काष्ठा scsi_lun	lun;
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	ttt;	/* Target Transfer Tag */
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	r2tsn;
	__be32	data_offset;
	__be32	data_length;
पूर्ण;

/* SCSI Data Hdr */
काष्ठा iscsi_data अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t rsvd3;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun lun;
	itt_t	 itt;
	__be32	ttt;
	__be32	rsvd4;
	__be32	exp_statsn;
	__be32	rsvd5;
	__be32	datasn;
	__be32	offset;
	__be32	rsvd6;
	/* Payload */
पूर्ण;

/* SCSI Data Response Hdr */
काष्ठा iscsi_data_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2;
	uपूर्णांक8_t cmd_status;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	काष्ठा scsi_lun	lun;
	itt_t	 itt;
	__be32	ttt;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	datasn;
	__be32	offset;
	__be32	residual_count;
पूर्ण;

/* Data Response PDU flags */
#घोषणा ISCSI_FLAG_DATA_ACK		0x40
#घोषणा ISCSI_FLAG_DATA_OVERFLOW	0x04
#घोषणा ISCSI_FLAG_DATA_UNDERFLOW	0x02
#घोषणा ISCSI_FLAG_DATA_STATUS		0x01

/* Text Header */
काष्ठा iscsi_text अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd4[8];
	itt_t	 itt;
	__be32	ttt;
	__be32	cmdsn;
	__be32	exp_statsn;
	uपूर्णांक8_t rsvd5[16];
	/* Text - key=value pairs */
पूर्ण;

#घोषणा ISCSI_FLAG_TEXT_CONTINUE	0x40

/* Text Response Header */
काष्ठा iscsi_text_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd4[8];
	itt_t	 itt;
	__be32	ttt;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uपूर्णांक8_t rsvd5[12];
	/* Text Response - key:value pairs */
पूर्ण;

/* Login Header */
काष्ठा iscsi_login_req अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t max_version;	/* Max. version supported */
	uपूर्णांक8_t min_version;	/* Min. version supported */
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t isid[6];	/* Initiator Session ID */
	__be16	tsih;	/* Target Session Handle */
	itt_t	 itt;	/* Initiator Task Tag */
	__be16	cid;
	__be16	rsvd3;
	__be32	cmdsn;
	__be32	exp_statsn;
	uपूर्णांक8_t rsvd5[16];
पूर्ण;

/* Login PDU flags */
#घोषणा ISCSI_FLAG_LOGIN_TRANSIT		0x80
#घोषणा ISCSI_FLAG_LOGIN_CONTINUE		0x40
#घोषणा ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK	0x0C	/* 2 bits */
#घोषणा ISCSI_FLAG_LOGIN_CURRENT_STAGE1		0x04
#घोषणा ISCSI_FLAG_LOGIN_CURRENT_STAGE2		0x08
#घोषणा ISCSI_FLAG_LOGIN_CURRENT_STAGE3		0x0C
#घोषणा ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK	0x03	/* 2 bits */
#घोषणा ISCSI_FLAG_LOGIN_NEXT_STAGE1		0x01
#घोषणा ISCSI_FLAG_LOGIN_NEXT_STAGE2		0x02
#घोषणा ISCSI_FLAG_LOGIN_NEXT_STAGE3		0x03

#घोषणा ISCSI_LOGIN_CURRENT_STAGE(flags) \
	((flags & ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK) >> 2)
#घोषणा ISCSI_LOGIN_NEXT_STAGE(flags) \
	(flags & ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK)

/* Login Response Header */
काष्ठा iscsi_login_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t max_version;	/* Max. version supported */
	uपूर्णांक8_t active_version;	/* Active version */
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t isid[6];	/* Initiator Session ID */
	__be16	tsih;	/* Target Session Handle */
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	rsvd3;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	uपूर्णांक8_t status_class;	/* see Login RSP ststus classes below */
	uपूर्णांक8_t status_detail;	/* see Login RSP Status details below */
	uपूर्णांक8_t rsvd4[10];
पूर्ण;

/* Login stage (phase) codes क्रम CSG, NSG */
#घोषणा ISCSI_INITIAL_LOGIN_STAGE		-1
#घोषणा ISCSI_SECURITY_NEGOTIATION_STAGE	0
#घोषणा ISCSI_OP_PARMS_NEGOTIATION_STAGE	1
#घोषणा ISCSI_FULL_FEATURE_PHASE		3

/* Login Status response classes */
#घोषणा ISCSI_STATUS_CLS_SUCCESS		0x00
#घोषणा ISCSI_STATUS_CLS_REसूचीECT		0x01
#घोषणा ISCSI_STATUS_CLS_INITIATOR_ERR		0x02
#घोषणा ISCSI_STATUS_CLS_TARGET_ERR		0x03

/* Login Status response detail codes */
/* Class-0 (Success) */
#घोषणा ISCSI_LOGIN_STATUS_ACCEPT		0x00

/* Class-1 (Redirection) */
#घोषणा ISCSI_LOGIN_STATUS_TGT_MOVED_TEMP	0x01
#घोषणा ISCSI_LOGIN_STATUS_TGT_MOVED_PERM	0x02

/* Class-2 (Initiator Error) */
#घोषणा ISCSI_LOGIN_STATUS_INIT_ERR		0x00
#घोषणा ISCSI_LOGIN_STATUS_AUTH_FAILED		0x01
#घोषणा ISCSI_LOGIN_STATUS_TGT_FORBIDDEN	0x02
#घोषणा ISCSI_LOGIN_STATUS_TGT_NOT_FOUND	0x03
#घोषणा ISCSI_LOGIN_STATUS_TGT_REMOVED		0x04
#घोषणा ISCSI_LOGIN_STATUS_NO_VERSION		0x05
#घोषणा ISCSI_LOGIN_STATUS_ISID_ERROR		0x06
#घोषणा ISCSI_LOGIN_STATUS_MISSING_FIELDS	0x07
#घोषणा ISCSI_LOGIN_STATUS_CONN_ADD_FAILED	0x08
#घोषणा ISCSI_LOGIN_STATUS_NO_SESSION_TYPE	0x09
#घोषणा ISCSI_LOGIN_STATUS_NO_SESSION		0x0a
#घोषणा ISCSI_LOGIN_STATUS_INVALID_REQUEST	0x0b

/* Class-3 (Target Error) */
#घोषणा ISCSI_LOGIN_STATUS_TARGET_ERROR		0x00
#घोषणा ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE	0x01
#घोषणा ISCSI_LOGIN_STATUS_NO_RESOURCES		0x02

/* Logout Header */
काष्ठा iscsi_logout अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd1[2];
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd2[8];
	itt_t	 itt;	/* Initiator Task Tag */
	__be16	cid;
	uपूर्णांक8_t rsvd3[2];
	__be32	cmdsn;
	__be32	exp_statsn;
	uपूर्णांक8_t rsvd4[16];
पूर्ण;

/* Logout PDU flags */
#घोषणा ISCSI_FLAG_LOGOUT_REASON_MASK	0x7F

/* logout reason_code values */

#घोषणा ISCSI_LOGOUT_REASON_CLOSE_SESSION	0
#घोषणा ISCSI_LOGOUT_REASON_CLOSE_CONNECTION	1
#घोषणा ISCSI_LOGOUT_REASON_RECOVERY		2
#घोषणा ISCSI_LOGOUT_REASON_AEN_REQUEST		3

/* Logout Response Header */
काष्ठा iscsi_logout_rsp अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t response;	/* see Logout response values below */
	uपूर्णांक8_t rsvd2;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd3[8];
	itt_t	 itt;	/* Initiator Task Tag */
	__be32	rsvd4;
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	rsvd5;
	__be16	t2रुको;
	__be16	t2retain;
	__be32	rsvd6;
पूर्ण;

/* logout response status values */

#घोषणा ISCSI_LOGOUT_SUCCESS			0
#घोषणा ISCSI_LOGOUT_CID_NOT_FOUND		1
#घोषणा ISCSI_LOGOUT_RECOVERY_UNSUPPORTED	2
#घोषणा ISCSI_LOGOUT_CLEANUP_FAILED		3

/* SNACK Header */
काष्ठा iscsi_snack अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t rsvd2[2];
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t lun[8];
	itt_t	 itt;
	__be32  ttt;
	uपूर्णांक8_t rsvd3[4];
	__be32  exp_statsn;
	uपूर्णांक8_t rsvd4[8];
	__be32	begrun;
	__be32	runlength;
पूर्ण;

/* SNACK PDU flags */
#घोषणा ISCSI_FLAG_SNACK_TYPE_DATA		0
#घोषणा ISCSI_FLAG_SNACK_TYPE_R2T		0
#घोषणा ISCSI_FLAG_SNACK_TYPE_STATUS		1
#घोषणा ISCSI_FLAG_SNACK_TYPE_DATA_ACK		2
#घोषणा ISCSI_FLAG_SNACK_TYPE_RDATA		3
#घोषणा ISCSI_FLAG_SNACK_TYPE_MASK	0x0F	/* 4 bits */

/* Reject Message Header */
काष्ठा iscsi_reject अणु
	uपूर्णांक8_t opcode;
	uपूर्णांक8_t flags;
	uपूर्णांक8_t reason;
	uपूर्णांक8_t rsvd2;
	uपूर्णांक8_t hlength;
	uपूर्णांक8_t dlength[3];
	uपूर्णांक8_t rsvd3[8];
	__be32  ffffffff;
	uपूर्णांक8_t rsvd4[4];
	__be32	statsn;
	__be32	exp_cmdsn;
	__be32	max_cmdsn;
	__be32	datasn;
	uपूर्णांक8_t rsvd5[8];
	/* Text - Rejected hdr */
पूर्ण;

/* Reason क्रम Reject */
#घोषणा ISCSI_REASON_CMD_BEFORE_LOGIN	1
#घोषणा ISCSI_REASON_DATA_DIGEST_ERROR	2
#घोषणा ISCSI_REASON_DATA_SNACK_REJECT	3
#घोषणा ISCSI_REASON_PROTOCOL_ERROR	4
#घोषणा ISCSI_REASON_CMD_NOT_SUPPORTED	5
#घोषणा ISCSI_REASON_IMM_CMD_REJECT		6
#घोषणा ISCSI_REASON_TASK_IN_PROGRESS	7
#घोषणा ISCSI_REASON_INVALID_SNACK		8
#घोषणा ISCSI_REASON_BOOKMARK_INVALID	9
#घोषणा ISCSI_REASON_BOOKMARK_NO_RESOURCES	10
#घोषणा ISCSI_REASON_NEGOTIATION_RESET	11

/* Max. number of Key=Value pairs in a text message */
#घोषणा MAX_KEY_VALUE_PAIRS	8192

/* maximum length क्रम text keys/values */
#घोषणा KEY_MAXLEN		64
#घोषणा VALUE_MAXLEN		255
#घोषणा TARGET_NAME_MAXLEN	VALUE_MAXLEN

#घोषणा ISCSI_DEF_MAX_RECV_SEG_LEN		8192
#घोषणा ISCSI_MIN_MAX_RECV_SEG_LEN		512
#घोषणा ISCSI_MAX_MAX_RECV_SEG_LEN		16777215

#घोषणा ISCSI_DEF_FIRST_BURST_LEN		65536
#घोषणा ISCSI_MIN_FIRST_BURST_LEN		512
#घोषणा ISCSI_MAX_FIRST_BURST_LEN		16777215

#घोषणा ISCSI_DEF_MAX_BURST_LEN			262144
#घोषणा ISCSI_MIN_MAX_BURST_LEN			512
#घोषणा ISCSI_MAX_MAX_BURST_LEN			16777215

#घोषणा ISCSI_DEF_TIME2WAIT			2

#घोषणा ISCSI_NAME_LEN				224

/************************* RFC 3720 End *****************************/

#पूर्ण_अगर /* ISCSI_PROTO_H */

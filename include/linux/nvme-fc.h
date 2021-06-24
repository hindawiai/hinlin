<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 Avago Technologies.  All rights reserved.
 */

/*
 * This file contains definitions relative to FC-NVME-2 r1.08
 * (T11-2019-00210-v004).
 */

#अगर_अघोषित _NVME_FC_H
#घोषणा _NVME_FC_H 1

#समावेश <uapi/scsi/fc/fc_fs.h>

#घोषणा NVME_CMD_FORMAT_ID		0xFD
#घोषणा NVME_CMD_FC_ID			FC_TYPE_NVME

/* FC-NVME Cmd IU Flags */
क्रमागत अणु
	FCNVME_CMD_FLAGS_सूचीMASK	= 0x03,
	FCNVME_CMD_FLAGS_WRITE		= (1 << 0),
	FCNVME_CMD_FLAGS_READ		= (1 << 1),

	FCNVME_CMD_FLAGS_PICWP		= (1 << 2),
पूर्ण;

क्रमागत अणु
	FCNVME_CMD_CAT_MASK		= 0x0F,
	FCNVME_CMD_CAT_ADMINQ		= 0x01,
	FCNVME_CMD_CAT_CSSMASK		= 0x07,
	FCNVME_CMD_CAT_CSSFLAG		= 0x08,
पूर्ण;

अटल अंतरभूत __u8 fccmnd_set_cat_admin(__u8 rsv_cat)
अणु
	वापस (rsv_cat & ~FCNVME_CMD_CAT_MASK) | FCNVME_CMD_CAT_ADMINQ;
पूर्ण

अटल अंतरभूत __u8 fccmnd_set_cat_css(__u8 rsv_cat, __u8 css)
अणु
	वापस (rsv_cat & ~FCNVME_CMD_CAT_MASK) | FCNVME_CMD_CAT_CSSFLAG |
		(css & FCNVME_CMD_CAT_CSSMASK);
पूर्ण

काष्ठा nvme_fc_cmd_iu अणु
	__u8			क्रमmat_id;
	__u8			fc_id;
	__be16			iu_len;
	__u8			rsvd4[2];
	__u8			rsv_cat;
	__u8			flags;
	__be64			connection_id;
	__be32			csn;
	__be32			data_len;
	काष्ठा nvme_command	sqe;
	__u8			dps;
	__u8			lbads;
	__be16			ms;
	__be32			rsvd92;
पूर्ण;

#घोषणा NVME_FC_SIZखातापूर्ण_ZEROS_RSP	12

क्रमागत अणु
	FCNVME_SC_SUCCESS		= 0,
	FCNVME_SC_INVALID_FIELD		= 1,
	/* reserved			  2 */
	FCNVME_SC_ILL_CONN_PARAMS	= 3,
पूर्ण;

काष्ठा nvme_fc_ersp_iu अणु
	__u8			ersp_result;
	__u8			rsvd1;
	__be16			iu_len;
	__be32			rsn;
	__be32			xfrd_len;
	__be32			rsvd12;
	काष्ठा nvme_completion	cqe;
	/* क्रम now - no additional payload */
पूर्ण;


#घोषणा FCNVME_NVME_SR_OPCODE		0x01
#घोषणा FCNVME_NVME_SR_RSP_OPCODE	0x02

काष्ठा nvme_fc_nvme_sr_iu अणु
	__u8			fc_id;
	__u8			opcode;
	__u8			rsvd2;
	__u8			retry_rctl;
	__be32			rsvd4;
पूर्ण;


क्रमागत अणु
	FCNVME_SRSTAT_ACC		= 0x0,
	/* reserved			  0x1 */
	/* reserved			  0x2 */
	FCNVME_SRSTAT_LOGICAL_ERR	= 0x3,
	FCNVME_SRSTAT_INV_QUALIF	= 0x4,
	FCNVME_SRSTAT_UNABL2PERFORM	= 0x9,
पूर्ण;

काष्ठा nvme_fc_nvme_sr_rsp_iu अणु
	__u8			fc_id;
	__u8			opcode;
	__u8			rsvd2;
	__u8			status;
	__be32			rsvd4;
पूर्ण;


/* FC-NVME Link Services - LS cmd values (w0 bits 31:24) */
क्रमागत अणु
	FCNVME_LS_RSVD			= 0,
	FCNVME_LS_RJT			= 1,
	FCNVME_LS_ACC			= 2,
	FCNVME_LS_CREATE_ASSOCIATION	= 3,	/* Create Association */
	FCNVME_LS_CREATE_CONNECTION	= 4,	/* Create I/O Connection */
	FCNVME_LS_DISCONNECT_ASSOC	= 5,	/* Disconnect Association */
	FCNVME_LS_DISCONNECT_CONN	= 6,	/* Disconnect Connection */
पूर्ण;

/* FC-NVME Link Service Descriptors */
क्रमागत अणु
	FCNVME_LSDESC_RSVD		= 0x0,
	FCNVME_LSDESC_RQST		= 0x1,
	FCNVME_LSDESC_RJT		= 0x2,
	FCNVME_LSDESC_CREATE_ASSOC_CMD	= 0x3,
	FCNVME_LSDESC_CREATE_CONN_CMD	= 0x4,
	FCNVME_LSDESC_DISCONN_CMD	= 0x5,
	FCNVME_LSDESC_CONN_ID		= 0x6,
	FCNVME_LSDESC_ASSOC_ID		= 0x7,
पूर्ण;


/* ********** start of Link Service Descriptors ********** */


/*
 * fills in length of a descriptor. Struture minus descriptor header
 */
अटल अंतरभूत __be32 fcnvme_lsdesc_len(माप_प्रकार sz)
अणु
	वापस cpu_to_be32(sz - (2 * माप(u32)));
पूर्ण

काष्ठा fcnvme_ls_rqst_w0 अणु
	u8	ls_cmd;			/* FCNVME_LS_xxx */
	u8	zeros[3];
पूर्ण;

/* FCNVME_LSDESC_RQST */
काष्ठा fcnvme_lsdesc_rqst अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	काष्ठा fcnvme_ls_rqst_w0	w0;
	__be32	rsvd12;
पूर्ण;

/* FC-NVME LS RJT reason_code values */
क्रमागत fcnvme_ls_rjt_reason अणु
	FCNVME_RJT_RC_NONE		= 0,
	/* no reason - not to be sent */

	FCNVME_RJT_RC_INVAL		= 0x01,
	/* invalid NVMe_LS command code */

	FCNVME_RJT_RC_LOGIC		= 0x03,
	/* logical error */

	FCNVME_RJT_RC_UNAB		= 0x09,
	/* unable to perक्रमm command request */

	FCNVME_RJT_RC_UNSUP		= 0x0b,
	/* command not supported */

	FCNVME_RJT_RC_INV_ASSOC		= 0x40,
	/* Invalid Association ID */

	FCNVME_RJT_RC_INV_CONN		= 0x41,
	/* Invalid Connection ID */

	FCNVME_RJT_RC_INV_PARAM		= 0x42,
	/* Invalid Parameters */

	FCNVME_RJT_RC_INSUF_RES		= 0x43,
	/* Insufficient Resources */

	FCNVME_RJT_RC_VENDOR		= 0xff,
	/* venकरोr specअगरic error */
पूर्ण;

/* FC-NVME LS RJT reason_explanation values */
क्रमागत fcnvme_ls_rjt_explan अणु
	FCNVME_RJT_EXP_NONE		= 0x00,
	/* No additional explanation */

	FCNVME_RJT_EXP_OXID_RXID	= 0x17,
	/* invalid OX_ID-RX_ID combination */

	FCNVME_RJT_EXP_UNAB_DATA	= 0x2a,
	/* unable to supply requested data */

	FCNVME_RJT_EXP_INV_LEN		= 0x2d,
	/* Invalid payload length */

	FCNVME_RJT_EXP_INV_ERSP_RAT	= 0x40,
	/* Invalid NVMe_ERSP Ratio */

	FCNVME_RJT_EXP_INV_CTLR_ID	= 0x41,
	/* Invalid Controller ID */

	FCNVME_RJT_EXP_INV_QUEUE_ID	= 0x42,
	/* Invalid Queue ID */

	FCNVME_RJT_EXP_INV_SQSIZE	= 0x43,
	/* Invalid Submission Queue Size */

	FCNVME_RJT_EXP_INV_HOSTID	= 0x44,
	/* Invalid HOST ID */

	FCNVME_RJT_EXP_INV_HOSTNQN	= 0x45,
	/* Invalid HOSTNQN */

	FCNVME_RJT_EXP_INV_SUBNQN	= 0x46,
	/* Invalid SUBNQN */
पूर्ण;

/* FCNVME_LSDESC_RJT */
काष्ठा fcnvme_lsdesc_rjt अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	u8	rsvd8;

	/*
	 * Reject reason and explanaction codes are generic
	 * to ELs's from LS-3.
	 */
	u8	reason_code;		/* fcnvme_ls_rjt_reason */
	u8	reason_explanation;	/* fcnvme_ls_rjt_explan */

	u8	venकरोr;
	__be32	rsvd12;
पूर्ण;


#घोषणा FCNVME_ASSOC_HOSTNQN_LEN	256
#घोषणा FCNVME_ASSOC_SUBNQN_LEN		256

/* FCNVME_LSDESC_CREATE_ASSOC_CMD */
काष्ठा fcnvme_lsdesc_cr_assoc_cmd अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	__be16	ersp_ratio;
	__be16	rsvd10;
	__be32	rsvd12[9];
	__be16	cntlid;
	__be16	sqsize;
	__be32	rsvd52;
	uuid_t	hostid;
	u8	hostnqn[FCNVME_ASSOC_HOSTNQN_LEN];
	u8	subnqn[FCNVME_ASSOC_SUBNQN_LEN];
	__be32	rsvd584[108];		/* pad to 1016 bytes,
					 * which makes overall LS rqst
					 * payload 1024 bytes
					 */
पूर्ण;

#घोषणा FCNVME_LSDESC_CRA_CMD_DESC_MINLEN	\
		दुरत्व(काष्ठा fcnvme_lsdesc_cr_assoc_cmd, rsvd584)

#घोषणा FCNVME_LSDESC_CRA_CMD_DESC_MIN_DESCLEN	\
		(FCNVME_LSDESC_CRA_CMD_DESC_MINLEN - \
		 दुरत्व(काष्ठा fcnvme_lsdesc_cr_assoc_cmd, ersp_ratio))



/* FCNVME_LSDESC_CREATE_CONN_CMD */
काष्ठा fcnvme_lsdesc_cr_conn_cmd अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	__be16	ersp_ratio;
	__be16	rsvd10;
	__be32	rsvd12[9];
	__be16	qid;
	__be16	sqsize;
	__be32  rsvd52;
पूर्ण;

/* FCNVME_LSDESC_DISCONN_CMD */
काष्ठा fcnvme_lsdesc_disconn_cmd अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	__be32	rsvd8[4];
पूर्ण;

/* FCNVME_LSDESC_CONN_ID */
काष्ठा fcnvme_lsdesc_conn_id अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	__be64	connection_id;
पूर्ण;

/* FCNVME_LSDESC_ASSOC_ID */
काष्ठा fcnvme_lsdesc_assoc_id अणु
	__be32	desc_tag;		/* FCNVME_LSDESC_xxx */
	__be32	desc_len;
	__be64	association_id;
पूर्ण;

/* r_ctl values */
क्रमागत अणु
	FCNVME_RS_RCTL_CMND		= 0x6,
	FCNVME_RS_RCTL_DATA		= 0x1,
	FCNVME_RS_RCTL_CONF		= 0x3,
	FCNVME_RS_RCTL_SR		= 0x9,
	FCNVME_RS_RCTL_XFER_RDY		= 0x5,
	FCNVME_RS_RCTL_RSP		= 0x7,
	FCNVME_RS_RCTL_ERSP		= 0x8,
	FCNVME_RS_RCTL_SR_RSP		= 0xA,
पूर्ण;


/* ********** start of Link Services ********** */


/* FCNVME_LS_RJT */
काष्ठा fcnvme_ls_rjt अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_rqst		rqst;
	काष्ठा fcnvme_lsdesc_rjt		rjt;
पूर्ण;

/* FCNVME_LS_ACC */
काष्ठा fcnvme_ls_acc_hdr अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_rqst		rqst;
	/*
	 * Followed by cmd-specअगरic ACCEPT descriptors, see xxx_acc
	 * definitions below
	 */
पूर्ण;

/* FCNVME_LS_CREATE_ASSOCIATION */
काष्ठा fcnvme_ls_cr_assoc_rqst अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_cr_assoc_cmd	assoc_cmd;
पूर्ण;

#घोषणा FCNVME_LSDESC_CRA_RQST_MINLEN	\
		(दुरत्व(काष्ठा fcnvme_ls_cr_assoc_rqst, assoc_cmd) + \
			FCNVME_LSDESC_CRA_CMD_DESC_MINLEN)

#घोषणा FCNVME_LSDESC_CRA_RQST_MIN_LISTLEN	\
		FCNVME_LSDESC_CRA_CMD_DESC_MINLEN


काष्ठा fcnvme_ls_cr_assoc_acc अणु
	काष्ठा fcnvme_ls_acc_hdr		hdr;
	काष्ठा fcnvme_lsdesc_assoc_id		associd;
	काष्ठा fcnvme_lsdesc_conn_id		connectid;
पूर्ण;


/* FCNVME_LS_CREATE_CONNECTION */
काष्ठा fcnvme_ls_cr_conn_rqst अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_assoc_id		associd;
	काष्ठा fcnvme_lsdesc_cr_conn_cmd	connect_cmd;
पूर्ण;

काष्ठा fcnvme_ls_cr_conn_acc अणु
	काष्ठा fcnvme_ls_acc_hdr		hdr;
	काष्ठा fcnvme_lsdesc_conn_id		connectid;
पूर्ण;

/* FCNVME_LS_DISCONNECT_ASSOC */
काष्ठा fcnvme_ls_disconnect_assoc_rqst अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_assoc_id		associd;
	काष्ठा fcnvme_lsdesc_disconn_cmd	discon_cmd;
पूर्ण;

काष्ठा fcnvme_ls_disconnect_assoc_acc अणु
	काष्ठा fcnvme_ls_acc_hdr		hdr;
पूर्ण;


/* FCNVME_LS_DISCONNECT_CONN */
काष्ठा fcnvme_ls_disconnect_conn_rqst अणु
	काष्ठा fcnvme_ls_rqst_w0		w0;
	__be32					desc_list_len;
	काष्ठा fcnvme_lsdesc_assoc_id		associd;
	काष्ठा fcnvme_lsdesc_conn_id		connectid;
पूर्ण;

काष्ठा fcnvme_ls_disconnect_conn_acc अणु
	काष्ठा fcnvme_ls_acc_hdr		hdr;
पूर्ण;


/*
 * Default R_A_TOV is pulled in from fc_fs.h but needs conversion
 * from ms to seconds क्रम our use.
 */
#घोषणा FC_TWO_TIMES_R_A_TOV		(2 * (FC_DEF_R_A_TOV / 1000))
#घोषणा NVME_FC_LS_TIMEOUT_SEC		FC_TWO_TIMES_R_A_TOV
#घोषणा NVME_FC_TGTOP_TIMEOUT_SEC	FC_TWO_TIMES_R_A_TOV

/*
 * TRADDR string must be of क्रमm "nn-<16hexdigits>:pn-<16hexdigits>"
 * the string is allowed to be specअगरied with or without a "0x" prefix
 * infront of the <16hexdigits>.  Without is considered the "min" string
 * and with is considered the "max" string. The hexdigits may be upper
 * or lower हाल.
 * Note: FC-NVME-2 standard requires a "0x" prefix.
 */
#घोषणा NVME_FC_TRADDR_NNLEN		3	/* "?n-" */
#घोषणा NVME_FC_TRADDR_OXNNLEN		5	/* "?n-0x" */
#घोषणा NVME_FC_TRADDR_HEXNAMELEN	16
#घोषणा NVME_FC_TRADDR_MINLENGTH	\
		(2 * (NVME_FC_TRADDR_NNLEN + NVME_FC_TRADDR_HEXNAMELEN) + 1)
#घोषणा NVME_FC_TRADDR_MAXLENGTH	\
		(2 * (NVME_FC_TRADDR_OXNNLEN + NVME_FC_TRADDR_HEXNAMELEN) + 1)
#घोषणा NVME_FC_TRADDR_MIN_PN_OFFSET	\
		(NVME_FC_TRADDR_NNLEN + NVME_FC_TRADDR_HEXNAMELEN + 1)
#घोषणा NVME_FC_TRADDR_MAX_PN_OFFSET	\
		(NVME_FC_TRADDR_OXNNLEN + NVME_FC_TRADDR_HEXNAMELEN + 1)


#पूर्ण_अगर /* _NVME_FC_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 2004 - 2010 Vladislav Bolkhovitin <vst@vlnb.net>
 *  Copyright (C) 2004 - 2005 Leonid Stoljar
 *  Copyright (C) 2006 Nathaniel Clark <nate@misrule.us>
 *  Copyright (C) 2007 - 2010 ID7 Ltd.
 *
 *  Forward port and refactoring to modern qla2xxx and target/configfs
 *
 *  Copyright (C) 2010-2011 Nicholas A. Bellinger <nab@kernel.org>
 *
 *  Additional file क्रम the target driver support.
 */
/*
 * This is the global def file that is useful क्रम including from the
 * target portion.
 */

#अगर_अघोषित __QLA_TARGET_H
#घोषणा __QLA_TARGET_H

#समावेश "qla_def.h"
#समावेश "qla_dsd.h"

/*
 * Must be changed on any change in any initiator visible पूर्णांकerfaces or
 * data in the target add-on
 */
#घोषणा QLA2XXX_TARGET_MAGIC	269

/*
 * Must be changed on any change in any target visible पूर्णांकerfaces or
 * data in the initiator
 */
#घोषणा QLA2XXX_INITIATOR_MAGIC   57222

#घोषणा QLA2XXX_INI_MODE_STR_EXCLUSIVE	"exclusive"
#घोषणा QLA2XXX_INI_MODE_STR_DISABLED	"disabled"
#घोषणा QLA2XXX_INI_MODE_STR_ENABLED	"enabled"
#घोषणा QLA2XXX_INI_MODE_STR_DUAL		"dual"

#घोषणा QLA2XXX_INI_MODE_EXCLUSIVE	0
#घोषणा QLA2XXX_INI_MODE_DISABLED	1
#घोषणा QLA2XXX_INI_MODE_ENABLED	2
#घोषणा QLA2XXX_INI_MODE_DUAL	3

#घोषणा QLA2XXX_COMMAND_COUNT_INIT	250
#घोषणा QLA2XXX_IMMED_NOTIFY_COUNT_INIT 250

/*
 * Used to mark which completion handles (क्रम RIO Status's) are for CTIO's
 * vs. regular (non-target) info. This is checked क्रम in
 * qla2x00_process_response_queue() to see अगर a handle coming back in a
 * multi-complete should come to the tgt driver or be handled there by qla2xxx
 */
#घोषणा CTIO_COMPLETION_HANDLE_MARK	BIT_29
#अगर (CTIO_COMPLETION_HANDLE_MARK <= DEFAULT_OUTSTANDING_COMMANDS)
#त्रुटि "CTIO_COMPLETION_HANDLE_MARK not larger than "
	"DEFAULT_OUTSTANDING_COMMANDS"
#पूर्ण_अगर
#घोषणा HANDLE_IS_CTIO_COMP(h) (h & CTIO_COMPLETION_HANDLE_MARK)

/* Used to mark CTIO as पूर्णांकermediate */
#घोषणा CTIO_INTERMEDIATE_HANDLE_MARK	BIT_30
#घोषणा QLA_TGT_शून्य_HANDLE	0

#घोषणा QLA_TGT_HANDLE_MASK  0xF0000000
#घोषणा QLA_QPID_HANDLE_MASK 0x00FF0000 /* qpair id mask */
#घोषणा QLA_CMD_HANDLE_MASK  0x0000FFFF
#घोषणा QLA_TGT_SKIP_HANDLE	(0xFFFFFFFF & ~QLA_TGT_HANDLE_MASK)

#घोषणा QLA_QPID_HANDLE_SHIFT 16
#घोषणा GET_QID(_h) ((_h & QLA_QPID_HANDLE_MASK) >> QLA_QPID_HANDLE_SHIFT)


#अगर_अघोषित OF_SS_MODE_0
/*
 * ISP target entries - Flags bit definitions.
 */
#घोषणा OF_SS_MODE_0        0
#घोषणा OF_SS_MODE_1        1
#घोषणा OF_SS_MODE_2        2
#घोषणा OF_SS_MODE_3        3

#घोषणा OF_EXPL_CONF        BIT_5       /* Explicit Confirmation Requested */
#घोषणा OF_DATA_IN          BIT_6       /* Data in to initiator */
					/*  (data from target to initiator) */
#घोषणा OF_DATA_OUT         BIT_7       /* Data out from initiator */
					/*  (data from initiator to target) */
#घोषणा OF_NO_DATA          (BIT_7 | BIT_6)
#घोषणा OF_INC_RC           BIT_8       /* Increment command resource count */
#घोषणा OF_FAST_POST        BIT_9       /* Enable mailbox fast posting. */
#घोषणा OF_CONF_REQ         BIT_13      /* Confirmation Requested */
#घोषणा OF_TERM_EXCH        BIT_14      /* Terminate exchange */
#घोषणा OF_SSTS             BIT_15      /* Send SCSI status */
#पूर्ण_अगर

#अगर_अघोषित QLA_TGT_DATASEGS_PER_CMD32
#घोषणा QLA_TGT_DATASEGS_PER_CMD32	3
#घोषणा QLA_TGT_DATASEGS_PER_CONT32	7
#घोषणा QLA_TGT_MAX_SG32(ql) \
	(((ql) > 0) ? (QLA_TGT_DATASEGS_PER_CMD32 + \
		QLA_TGT_DATASEGS_PER_CONT32*((ql) - 1)) : 0)

#घोषणा QLA_TGT_DATASEGS_PER_CMD64	2
#घोषणा QLA_TGT_DATASEGS_PER_CONT64	5
#घोषणा QLA_TGT_MAX_SG64(ql) \
	(((ql) > 0) ? (QLA_TGT_DATASEGS_PER_CMD64 + \
		QLA_TGT_DATASEGS_PER_CONT64*((ql) - 1)) : 0)
#पूर्ण_अगर

#अगर_अघोषित QLA_TGT_DATASEGS_PER_CMD_24XX
#घोषणा QLA_TGT_DATASEGS_PER_CMD_24XX	1
#घोषणा QLA_TGT_DATASEGS_PER_CONT_24XX	5
#घोषणा QLA_TGT_MAX_SG_24XX(ql) \
	(min(1270, ((ql) > 0) ? (QLA_TGT_DATASEGS_PER_CMD_24XX + \
		QLA_TGT_DATASEGS_PER_CONT_24XX*((ql) - 1)) : 0))
#पूर्ण_अगर

#घोषणा GET_TARGET_ID(ha, iocb) ((HAS_EXTENDED_IDS(ha))			\
			 ? le16_to_cpu((iocb)->u.isp2x.target.extended)	\
			 : (uपूर्णांक16_t)(iocb)->u.isp2x.target.id.standard)

#अगर_अघोषित NOTIFY_ACK_TYPE
#घोषणा NOTIFY_ACK_TYPE 0x0E	  /* Notअगरy acknowledge entry. */
/*
 * ISP queue -	notअगरy acknowledge entry काष्ठाure definition.
 *		This is sent to the ISP from the target driver.
 */
काष्ठा nack_to_isp अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	जोड़ अणु
		काष्ठा अणु
			__le32	sys_define_2; /* System defined. */
			target_id_t target;
			uपूर्णांक8_t	 target_id;
			uपूर्णांक8_t	 reserved_1;
			__le16	flags;
			__le16	resp_code;
			__le16	status;
			__le16	task_flags;
			__le16	seq_id;
			__le16	srr_rx_id;
			__le32	srr_rel_offs;
			__le16	srr_ui;
			__le16	srr_flags;
			__le16	srr_reject_code;
			uपूर्णांक8_t  srr_reject_venकरोr_uniq;
			uपूर्णांक8_t  srr_reject_code_expl;
			uपूर्णांक8_t  reserved_2[24];
		पूर्ण isp2x;
		काष्ठा अणु
			uपूर्णांक32_t handle;
			__le16	nport_handle;
			uपूर्णांक16_t reserved_1;
			__le16	flags;
			__le16	srr_rx_id;
			__le16	status;
			uपूर्णांक8_t  status_subcode;
			uपूर्णांक8_t  fw_handle;
			__le32	exchange_address;
			__le32	srr_rel_offs;
			__le16	srr_ui;
			__le16	srr_flags;
			uपूर्णांक8_t  reserved_4[19];
			uपूर्णांक8_t  vp_index;
			uपूर्णांक8_t  srr_reject_venकरोr_uniq;
			uपूर्णांक8_t  srr_reject_code_expl;
			uपूर्णांक8_t  srr_reject_code;
			uपूर्णांक8_t  reserved_5[5];
		पूर्ण isp24;
	पूर्ण u;
	uपूर्णांक8_t  reserved[2];
	__le16	ox_id;
पूर्ण __packed;
#घोषणा NOTIFY_ACK_FLAGS_TERMINATE	BIT_3
#घोषणा NOTIFY_ACK_SRR_FLAGS_ACCEPT	0
#घोषणा NOTIFY_ACK_SRR_FLAGS_REJECT	1

#घोषणा NOTIFY_ACK_SRR_REJECT_REASON_UNABLE_TO_PERFORM	0x9

#घोषणा NOTIFY_ACK_SRR_FLAGS_REJECT_EXPL_NO_EXPL		0
#घोषणा NOTIFY_ACK_SRR_FLAGS_REJECT_EXPL_UNABLE_TO_SUPPLY_DATA	0x2a

#घोषणा NOTIFY_ACK_SUCCESS      0x01
#पूर्ण_अगर

#अगर_अघोषित ACCEPT_TGT_IO_TYPE
#घोषणा ACCEPT_TGT_IO_TYPE 0x16 /* Accept target I/O entry. */
#पूर्ण_अगर

#अगर_अघोषित CONTINUE_TGT_IO_TYPE
#घोषणा CONTINUE_TGT_IO_TYPE 0x17
/*
 * ISP queue -	Continue Target I/O (CTIO) entry क्रम status mode 0 काष्ठाure.
 *		This काष्ठाure is sent to the ISP 2xxx from target driver.
 */
काष्ठा ctio_to_2xxx अणु
	uपूर्णांक8_t	 entry_type;		/* Entry type. */
	uपूर्णांक8_t	 entry_count;		/* Entry count. */
	uपूर्णांक8_t	 sys_define;		/* System defined. */
	uपूर्णांक8_t	 entry_status;		/* Entry Status. */
	uपूर्णांक32_t handle;		/* System defined handle */
	target_id_t target;
	__le16	rx_id;
	__le16	flags;
	__le16	status;
	__le16	समयout;		/* 0 = 30 seconds, 0xFFFF = disable */
	__le16	dseg_count;		/* Data segment count. */
	__le32	relative_offset;
	__le32	residual;
	__le16	reserved_1[3];
	__le16	scsi_status;
	__le32	transfer_length;
	काष्ठा dsd32 dsd[3];
पूर्ण __packed;
#घोषणा ATIO_PATH_INVALID       0x07
#घोषणा ATIO_CANT_PROV_CAP      0x16
#घोषणा ATIO_CDB_VALID          0x3D

#घोषणा ATIO_EXEC_READ          BIT_1
#घोषणा ATIO_EXEC_WRITE         BIT_0
#पूर्ण_अगर

#अगर_अघोषित CTIO_A64_TYPE
#घोषणा CTIO_A64_TYPE 0x1F
#घोषणा CTIO_SUCCESS			0x01
#घोषणा CTIO_ABORTED			0x02
#घोषणा CTIO_INVALID_RX_ID		0x08
#घोषणा CTIO_TIMEOUT			0x0B
#घोषणा CTIO_DIF_ERROR			0x0C     /* DIF error detected  */
#घोषणा CTIO_LIP_RESET			0x0E
#घोषणा CTIO_TARGET_RESET		0x17
#घोषणा CTIO_PORT_UNAVAILABLE		0x28
#घोषणा CTIO_PORT_LOGGED_OUT		0x29
#घोषणा CTIO_PORT_CONF_CHANGED		0x2A
#घोषणा CTIO_SRR_RECEIVED		0x45
#पूर्ण_अगर

#अगर_अघोषित CTIO_RET_TYPE
#घोषणा CTIO_RET_TYPE	0x17		/* CTIO वापस entry */
#घोषणा ATIO_TYPE7 0x06 /* Accept target I/O entry क्रम 24xx */
#पूर्ण_अगर

काष्ठा fcp_hdr अणु
	uपूर्णांक8_t  r_ctl;
	be_id_t  d_id;
	uपूर्णांक8_t  cs_ctl;
	be_id_t  s_id;
	uपूर्णांक8_t  type;
	uपूर्णांक8_t  f_ctl[3];
	uपूर्णांक8_t  seq_id;
	uपूर्णांक8_t  df_ctl;
	uपूर्णांक16_t seq_cnt;
	__be16   ox_id;
	uपूर्णांक16_t rx_id;
	__le32	parameter;
पूर्ण;

काष्ठा fcp_hdr_le अणु
	le_id_t  d_id;
	uपूर्णांक8_t  r_ctl;
	le_id_t  s_id;
	uपूर्णांक8_t  cs_ctl;
	uपूर्णांक8_t  f_ctl[3];
	uपूर्णांक8_t  type;
	__le16	seq_cnt;
	uपूर्णांक8_t  df_ctl;
	uपूर्णांक8_t  seq_id;
	__le16	rx_id;
	__le16	ox_id;
	__le32	parameter;
पूर्ण;

#घोषणा F_CTL_EXCH_CONTEXT_RESP	BIT_23
#घोषणा F_CTL_SEQ_CONTEXT_RESIP	BIT_22
#घोषणा F_CTL_LAST_SEQ		BIT_20
#घोषणा F_CTL_END_SEQ		BIT_19
#घोषणा F_CTL_SEQ_INITIATIVE	BIT_16

#घोषणा R_CTL_BASIC_LINK_SERV	0x80
#घोषणा R_CTL_B_ACC		0x4
#घोषणा R_CTL_B_RJT		0x5

काष्ठा atio7_fcp_cmnd अणु
	uपूर्णांक64_t lun;
	uपूर्णांक8_t  cmnd_ref;
	uपूर्णांक8_t  task_attr:3;
	uपूर्णांक8_t  reserved:5;
	uपूर्णांक8_t  task_mgmt_flags;
#घोषणा FCP_CMND_TASK_MGMT_CLEAR_ACA		6
#घोषणा FCP_CMND_TASK_MGMT_TARGET_RESET		5
#घोषणा FCP_CMND_TASK_MGMT_LU_RESET		4
#घोषणा FCP_CMND_TASK_MGMT_CLEAR_TASK_SET	2
#घोषणा FCP_CMND_TASK_MGMT_ABORT_TASK_SET	1
	uपूर्णांक8_t  wrdata:1;
	uपूर्णांक8_t  rddata:1;
	uपूर्णांक8_t  add_cdb_len:6;
	uपूर्णांक8_t  cdb[16];
	/*
	 * add_cdb is optional and can असलent from काष्ठा atio7_fcp_cmnd. Size 4
	 * only to make माप(काष्ठा atio7_fcp_cmnd) be as expected by
	 * BUILD_BUG_ON in qlt_init().
	 */
	uपूर्णांक8_t  add_cdb[4];
	/* __le32	data_length; */
पूर्ण __packed;

/*
 * ISP queue -	Accept Target I/O (ATIO) type entry IOCB काष्ठाure.
 *		This is sent from the ISP to the target driver.
 */
काष्ठा atio_from_isp अणु
	जोड़ अणु
		काष्ठा अणु
			__le16	entry_hdr;
			uपूर्णांक8_t  sys_define;   /* System defined. */
			uपूर्णांक8_t  entry_status; /* Entry Status.   */
			__le32	sys_define_2; /* System defined. */
			target_id_t target;
			__le16	rx_id;
			__le16	flags;
			__le16	status;
			uपूर्णांक8_t  command_ref;
			uपूर्णांक8_t  task_codes;
			uपूर्णांक8_t  task_flags;
			uपूर्णांक8_t  execution_codes;
			uपूर्णांक8_t  cdb[MAX_CMDSZ];
			__le32	data_length;
			__le16	lun;
			uपूर्णांक8_t  initiator_port_name[WWN_SIZE]; /* on qla23xx */
			__le16	reserved_32[6];
			__le16	ox_id;
		पूर्ण isp2x;
		काष्ठा अणु
			__le16	entry_hdr;
			uपूर्णांक8_t  fcp_cmnd_len_low;
			uपूर्णांक8_t  fcp_cmnd_len_high:4;
			uपूर्णांक8_t  attr:4;
			__le32	exchange_addr;
#घोषणा ATIO_EXCHANGE_ADDRESS_UNKNOWN	0xFFFFFFFF
			काष्ठा fcp_hdr fcp_hdr;
			काष्ठा atio7_fcp_cmnd fcp_cmnd;
		पूर्ण isp24;
		काष्ठा अणु
			uपूर्णांक8_t  entry_type;	/* Entry type. */
			uपूर्णांक8_t  entry_count;	/* Entry count. */
			__le16	 attr_n_length;
#घोषणा FCP_CMD_LENGTH_MASK 0x0fff
#घोषणा FCP_CMD_LENGTH_MIN  0x38
			uपूर्णांक8_t  data[56];
			__le32	signature;
#घोषणा ATIO_PROCESSED 0xDEADDEAD		/* Signature */
		पूर्ण raw;
	पूर्ण u;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक fcpcmd_is_corrupted(काष्ठा atio *atio)
अणु
	अगर (atio->entry_type == ATIO_TYPE7 &&
	    ((le16_to_cpu(atio->attr_n_length) & FCP_CMD_LENGTH_MASK) <
	     FCP_CMD_LENGTH_MIN))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* adjust corrupted atio so we won't trip over the same entry again. */
अटल अंतरभूत व्योम adjust_corrupted_atio(काष्ठा atio_from_isp *atio)
अणु
	atio->u.raw.attr_n_length = cpu_to_le16(FCP_CMD_LENGTH_MIN);
	atio->u.isp24.fcp_cmnd.add_cdb_len = 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_datalen_क्रम_atio(काष्ठा atio_from_isp *atio)
अणु
	पूर्णांक len = atio->u.isp24.fcp_cmnd.add_cdb_len;

	वापस get_unaligned_be32(&atio->u.isp24.fcp_cmnd.add_cdb[len * 4]);
पूर्ण

#घोषणा CTIO_TYPE7 0x12 /* Continue target I/O entry (क्रम 24xx) */

/*
 * ISP queue -	Continue Target I/O (ATIO) type 7 entry (क्रम 24xx) काष्ठाure.
 *		This काष्ठाure is sent to the ISP 24xx from the target driver.
 */

काष्ठा ctio7_to_24xx अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	uपूर्णांक32_t handle;		    /* System defined handle */
	__le16	nport_handle;
#घोषणा CTIO7_NHANDLE_UNRECOGNIZED	0xFFFF
	__le16	समयout;
	__le16	dseg_count;		    /* Data segment count. */
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  add_flags;
	le_id_t  initiator_id;
	uपूर्णांक8_t  reserved;
	__le32	exchange_addr;
	जोड़ अणु
		काष्ठा अणु
			__le16	reserved1;
			__le16 flags;
			__le32	residual;
			__le16 ox_id;
			__le16	scsi_status;
			__le32	relative_offset;
			__le32	reserved2;
			__le32	transfer_length;
			__le32	reserved3;
			काष्ठा dsd64 dsd;
		पूर्ण status0;
		काष्ठा अणु
			__le16	sense_length;
			__le16 flags;
			__le32	residual;
			__le16 ox_id;
			__le16	scsi_status;
			__le16	response_len;
			__le16	reserved;
			uपूर्णांक8_t sense_data[24];
		पूर्ण status1;
	पूर्ण u;
पूर्ण __packed;

/*
 * ISP queue - CTIO type 7 from ISP 24xx to target driver
 * वापसed entry काष्ठाure.
 */
काष्ठा ctio7_from_24xx अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	uपूर्णांक32_t handle;		    /* System defined handle */
	__le16	status;
	__le16	समयout;
	__le16	dseg_count;		    /* Data segment count. */
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  reserved1[5];
	__le32	exchange_address;
	__le16	reserved2;
	__le16	flags;
	__le32	residual;
	__le16	ox_id;
	__le16	reserved3;
	__le32	relative_offset;
	uपूर्णांक8_t  reserved4[24];
पूर्ण __packed;

/* CTIO7 flags values */
#घोषणा CTIO7_FLAGS_SEND_STATUS		BIT_15
#घोषणा CTIO7_FLAGS_TERMINATE		BIT_14
#घोषणा CTIO7_FLAGS_CONFORM_REQ		BIT_13
#घोषणा CTIO7_FLAGS_DONT_RET_CTIO	BIT_8
#घोषणा CTIO7_FLAGS_STATUS_MODE_0	0
#घोषणा CTIO7_FLAGS_STATUS_MODE_1	BIT_6
#घोषणा CTIO7_FLAGS_STATUS_MODE_2	BIT_7
#घोषणा CTIO7_FLAGS_EXPLICIT_CONFORM	BIT_5
#घोषणा CTIO7_FLAGS_CONFIRM_SATISF	BIT_4
#घोषणा CTIO7_FLAGS_DSD_PTR		BIT_2
#घोषणा CTIO7_FLAGS_DATA_IN		BIT_1 /* data to initiator */
#घोषणा CTIO7_FLAGS_DATA_OUT		BIT_0 /* data from initiator */

#घोषणा ELS_PLOGI			0x3
#घोषणा ELS_FLOGI			0x4
#घोषणा ELS_LOGO			0x5
#घोषणा ELS_PRLI			0x20
#घोषणा ELS_PRLO			0x21
#घोषणा ELS_TPRLO			0x24
#घोषणा ELS_PDISC			0x50
#घोषणा ELS_ADISC			0x52

/*
 *CTIO Type CRC_2 IOCB
 */
काष्ठा ctio_crc2_to_fw अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
#घोषणा CTIO_CRC2 0x7A
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	__le16	nport_handle;		/* N_PORT handle. */
	__le16 समयout;		/* Command समयout. */

	__le16	dseg_count;		/* Data segment count. */
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  add_flags;		/* additional flags */
#घोषणा CTIO_CRC2_AF_DIF_DSD_ENA BIT_3

	le_id_t  initiator_id;		/* initiator ID */
	uपूर्णांक8_t  reserved1;
	__le32	exchange_addr;		/* rcv exchange address */
	__le16	reserved2;
	__le16 flags;			/* refer to CTIO7 flags values */
	__le32	residual;
	__le16 ox_id;
	__le16	scsi_status;
	__le32 relative_offset;
	__le32	reserved5;
	__le32 transfer_length;		/* total fc transfer length */
	__le32	reserved6;
	__le64	 crc_context_address __packed; /* Data segment address. */
	__le16	crc_context_len;	/* Data segment length. */
	__le16	reserved_1;		/* MUST be set to 0. */
पूर्ण;

/* CTIO Type CRC_x Status IOCB */
काष्ठा ctio_crc_from_fw अणु
	uपूर्णांक8_t entry_type;		/* Entry type. */
	uपूर्णांक8_t entry_count;		/* Entry count. */
	uपूर्णांक8_t sys_define;		/* System defined. */
	uपूर्णांक8_t entry_status;		/* Entry Status. */

	uपूर्णांक32_t handle;		/* System handle. */
	__le16	status;
	__le16	समयout;		/* Command समयout. */
	__le16	dseg_count;		/* Data segment count. */
	__le32	reserved1;
	__le16	state_flags;
#घोषणा CTIO_CRC_SF_DIF_CHOPPED BIT_4

	__le32	exchange_address;	/* rcv exchange address */
	__le16	reserved2;
	__le16	flags;
	__le32	resid_xfer_length;
	__le16	ox_id;
	uपूर्णांक8_t  reserved3[12];
	__le16	runt_guard;		/* reported runt blk guard */
	uपूर्णांक8_t  actual_dअगर[8];
	uपूर्णांक8_t  expected_dअगर[8];
पूर्ण __packed;

/*
 * ISP queue - ABTS received/response entries काष्ठाure definition क्रम 24xx.
 */
#घोषणा ABTS_RECV_24XX		0x54 /* ABTS received (क्रम 24xx) */
#घोषणा ABTS_RESP_24XX		0x55 /* ABTS responce (क्रम 24xx) */

/*
 * ISP queue -	ABTS received IOCB entry काष्ठाure definition क्रम 24xx.
 *		The ABTS BLS received from the wire is sent to the
 *		target driver by the ISP 24xx.
 *		The IOCB is placed on the response queue.
 */
काष्ठा abts_recv_from_24xx अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	uपूर्णांक8_t  reserved_1[6];
	__le16	nport_handle;
	uपूर्णांक8_t  reserved_2[2];
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  reserved_3:4;
	uपूर्णांक8_t  sof_type:4;
	__le32	exchange_address;
	काष्ठा fcp_hdr_le fcp_hdr_le;
	uपूर्णांक8_t  reserved_4[16];
	__le32	exchange_addr_to_पात;
पूर्ण __packed;

#घोषणा ABTS_PARAM_ABORT_SEQ		BIT_0

काष्ठा ba_acc_le अणु
	__le16	reserved;
	uपूर्णांक8_t  seq_id_last;
	uपूर्णांक8_t  seq_id_valid;
#घोषणा SEQ_ID_VALID	0x80
#घोषणा SEQ_ID_INVALID	0x00
	__le16	rx_id;
	__le16	ox_id;
	__le16	high_seq_cnt;
	__le16	low_seq_cnt;
पूर्ण __packed;

काष्ठा ba_rjt_le अणु
	uपूर्णांक8_t venकरोr_uniq;
	uपूर्णांक8_t reason_expl;
	uपूर्णांक8_t reason_code;
#घोषणा BA_RJT_REASON_CODE_INVALID_COMMAND	0x1
#घोषणा BA_RJT_REASON_CODE_UNABLE_TO_PERFORM	0x9
	uपूर्णांक8_t reserved;
पूर्ण __packed;

/*
 * ISP queue -	ABTS Response IOCB entry काष्ठाure definition क्रम 24xx.
 *		The ABTS response to the ABTS received is sent by the
 *		target driver to the ISP 24xx.
 *		The IOCB is placed on the request queue.
 */
काष्ठा abts_resp_to_24xx अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	uपूर्णांक32_t handle;
	__le16	reserved_1;
	__le16	nport_handle;
	__le16	control_flags;
#घोषणा ABTS_CONTR_FLG_TERM_EXCHG	BIT_0
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  reserved_3:4;
	uपूर्णांक8_t  sof_type:4;
	__le32	exchange_address;
	काष्ठा fcp_hdr_le fcp_hdr_le;
	जोड़ अणु
		काष्ठा ba_acc_le ba_acct;
		काष्ठा ba_rjt_le ba_rjt;
	पूर्ण __packed payload;
	__le32	reserved_4;
	__le32	exchange_addr_to_पात;
पूर्ण __packed;

/*
 * ISP queue -	ABTS Response IOCB from ISP24xx Firmware entry काष्ठाure.
 *		The ABTS response with completion status to the ABTS response
 *		(sent by the target driver to the ISP 24xx) is sent by the
 *		ISP24xx firmware to the target driver.
 *		The IOCB is placed on the response queue.
 */
काष्ठा abts_resp_from_24xx_fw अणु
	uपूर्णांक8_t	 entry_type;		    /* Entry type. */
	uपूर्णांक8_t	 entry_count;		    /* Entry count. */
	uपूर्णांक8_t	 sys_define;		    /* System defined. */
	uपूर्णांक8_t	 entry_status;		    /* Entry Status. */
	uपूर्णांक32_t handle;
	__le16	compl_status;
#घोषणा ABTS_RESP_COMPL_SUCCESS		0
#घोषणा ABTS_RESP_COMPL_SUBCODE_ERROR	0x31
	__le16	nport_handle;
	__le16	reserved_1;
	uपूर्णांक8_t  reserved_2;
	uपूर्णांक8_t  reserved_3:4;
	uपूर्णांक8_t  sof_type:4;
	__le32	exchange_address;
	काष्ठा fcp_hdr_le fcp_hdr_le;
	uपूर्णांक8_t reserved_4[8];
	__le32	error_subcode1;
#घोषणा ABTS_RESP_SUBCODE_ERR_ABORTED_EXCH_NOT_TERM	0x1E
	__le32	error_subcode2;
	__le32	exchange_addr_to_पात;
पूर्ण __packed;

/********************************************************************\
 * Type Definitions used by initiator & target halves
\********************************************************************/

काष्ठा qla_tgt_mgmt_cmd;
काष्ठा fc_port;
काष्ठा qla_tgt_cmd;

/*
 * This काष्ठाure provides a ढाँचा of function calls that the
 * target driver (from within qla_target.c) can issue to the
 * target module (tcm_qla2xxx).
 */
काष्ठा qla_tgt_func_पंचांगpl अणु
	काष्ठा qla_tgt_cmd *(*find_cmd_by_tag)(काष्ठा fc_port *, uपूर्णांक64_t);
	पूर्णांक (*handle_cmd)(काष्ठा scsi_qla_host *, काष्ठा qla_tgt_cmd *,
			अचिन्हित अक्षर *, uपूर्णांक32_t, पूर्णांक, पूर्णांक, पूर्णांक);
	व्योम (*handle_data)(काष्ठा qla_tgt_cmd *);
	पूर्णांक (*handle_पंचांगr)(काष्ठा qla_tgt_mgmt_cmd *, u64, uपूर्णांक16_t,
			uपूर्णांक32_t);
	काष्ठा qla_tgt_cmd *(*get_cmd)(काष्ठा fc_port *);
	व्योम (*rel_cmd)(काष्ठा qla_tgt_cmd *);
	व्योम (*मुक्त_cmd)(काष्ठा qla_tgt_cmd *);
	व्योम (*मुक्त_mcmd)(काष्ठा qla_tgt_mgmt_cmd *);
	व्योम (*मुक्त_session)(काष्ठा fc_port *);

	पूर्णांक (*check_initiator_node_acl)(काष्ठा scsi_qla_host *, अचिन्हित अक्षर *,
					काष्ठा fc_port *);
	व्योम (*update_sess)(काष्ठा fc_port *, port_id_t, uपूर्णांक16_t, bool);
	काष्ठा fc_port *(*find_sess_by_loop_id)(काष्ठा scsi_qla_host *,
						स्थिर uपूर्णांक16_t);
	काष्ठा fc_port *(*find_sess_by_s_id)(काष्ठा scsi_qla_host *,
					     स्थिर be_id_t);
	व्योम (*clear_nacl_from_fcport_map)(काष्ठा fc_port *);
	व्योम (*put_sess)(काष्ठा fc_port *);
	व्योम (*shutकरोwn_sess)(काष्ठा fc_port *);
	पूर्णांक (*get_dअगर_tags)(काष्ठा qla_tgt_cmd *cmd, uपूर्णांक16_t *pfw_prot_opts);
	पूर्णांक (*chk_dअगर_tags)(uपूर्णांक32_t tag);
	व्योम (*add_target)(काष्ठा scsi_qla_host *);
	व्योम (*हटाओ_target)(काष्ठा scsi_qla_host *);
पूर्ण;

पूर्णांक qla2x00_रुको_क्रम_hba_online(काष्ठा scsi_qla_host *);

#समावेश <target/target_core_base.h>

#घोषणा QLA_TGT_TIMEOUT			10	/* in seconds */

#घोषणा QLA_TGT_MAX_HW_PENDING_TIME	60 /* in seconds */

/* Immediate notअगरy status स्थिरants */
#घोषणा IMM_NTFY_LIP_RESET          0x000E
#घोषणा IMM_NTFY_LIP_LINK_REINIT    0x000F
#घोषणा IMM_NTFY_IOCB_OVERFLOW      0x0016
#घोषणा IMM_NTFY_ABORT_TASK         0x0020
#घोषणा IMM_NTFY_PORT_LOGOUT        0x0029
#घोषणा IMM_NTFY_PORT_CONFIG        0x002A
#घोषणा IMM_NTFY_GLBL_TPRLO         0x002D
#घोषणा IMM_NTFY_GLBL_LOGO          0x002E
#घोषणा IMM_NTFY_RESOURCE           0x0034
#घोषणा IMM_NTFY_MSG_RX             0x0036
#घोषणा IMM_NTFY_SRR                0x0045
#घोषणा IMM_NTFY_ELS                0x0046

/* Immediate notअगरy task flags */
#घोषणा IMM_NTFY_TASK_MGMT_SHIFT    8

#घोषणा QLA_TGT_CLEAR_ACA               0x40
#घोषणा QLA_TGT_TARGET_RESET            0x20
#घोषणा QLA_TGT_LUN_RESET               0x10
#घोषणा QLA_TGT_CLEAR_TS                0x04
#घोषणा QLA_TGT_ABORT_TS                0x02
#घोषणा QLA_TGT_ABORT_ALL_SESS          0xFFFF
#घोषणा QLA_TGT_ABORT_ALL               0xFFFE
#घोषणा QLA_TGT_NEXUS_LOSS_SESS         0xFFFD
#घोषणा QLA_TGT_NEXUS_LOSS              0xFFFC
#घोषणा QLA_TGT_ABTS			0xFFFB
#घोषणा QLA_TGT_2G_ABORT_TASK		0xFFFA

/* Notअगरy Acknowledge flags */
#घोषणा NOTIFY_ACK_RES_COUNT        BIT_8
#घोषणा NOTIFY_ACK_CLEAR_LIP_RESET  BIT_5
#घोषणा NOTIFY_ACK_TM_RESP_CODE_VALID BIT_4

/* Command's states */
#घोषणा QLA_TGT_STATE_NEW		0 /* New command + target processing */
#घोषणा QLA_TGT_STATE_NEED_DATA		1 /* target needs data to जारी */
#घोषणा QLA_TGT_STATE_DATA_IN		2 /* Data arrived + target processing */
#घोषणा QLA_TGT_STATE_PROCESSED		3 /* target करोne processing */

/* ATIO task_codes field */
#घोषणा ATIO_SIMPLE_QUEUE           0
#घोषणा ATIO_HEAD_OF_QUEUE          1
#घोषणा ATIO_ORDERED_QUEUE          2
#घोषणा ATIO_ACA_QUEUE              4
#घोषणा ATIO_UNTAGGED               5

/* TM failed response codes, see FCP (9.4.11 FCP_RSP_INFO) */
#घोषणा	FC_TM_SUCCESS               0
#घोषणा	FC_TM_BAD_FCP_DATA          1
#घोषणा	FC_TM_BAD_CMD               2
#घोषणा	FC_TM_FCP_DATA_MISMATCH     3
#घोषणा	FC_TM_REJECT                4
#घोषणा FC_TM_FAILED                5

#घोषणा QLA_TGT_SENSE_VALID(sense)  ((sense != शून्य) && \
				(((स्थिर uपूर्णांक8_t *)(sense))[0] & 0x70) == 0x70)

काष्ठा qla_port_24xx_data अणु
	uपूर्णांक8_t port_name[WWN_SIZE];
	uपूर्णांक16_t loop_id;
	uपूर्णांक16_t reserved;
पूर्ण;

काष्ठा qla_qpair_hपूर्णांक अणु
	काष्ठा list_head hपूर्णांक_elem;
	काष्ठा qla_qpair *qpair;
	u16 cpuid;
	uपूर्णांक8_t cmd_cnt;
पूर्ण;

काष्ठा qla_tgt अणु
	काष्ठा scsi_qla_host *vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा btree_head64 lun_qpair_map;
	काष्ठा qla_qpair_hपूर्णांक *qphपूर्णांकs;
	/*
	 * To sync between IRQ handlers and qlt_target_release(). Needed,
	 * because req_pkt() can drop/reaquire HW lock inside. Protected by
	 * HW lock.
	 */
	पूर्णांक atio_irq_cmd_count;

	पूर्णांक sg_tablesize;

	/* Target's flags, serialized by pha->hardware_lock */
	अचिन्हित पूर्णांक link_reinit_iocb_pending:1;

	/*
	 * Protected by tgt_mutex AND hardware_lock क्रम writing and tgt_mutex
	 * OR hardware_lock क्रम पढ़ोing.
	 */
	पूर्णांक tgt_stop; /* the target mode driver is being stopped */
	पूर्णांक tgt_stopped; /* the target mode driver has been stopped */

	/* Count of sessions refering qla_tgt. Protected by hardware_lock. */
	पूर्णांक sess_count;

	/* Protected by hardware_lock */
	काष्ठा list_head del_sess_list;

	spinlock_t sess_work_lock;
	काष्ठा list_head sess_works_list;
	काष्ठा work_काष्ठा sess_work;

	काष्ठा imm_ntfy_from_isp link_reinit_iocb;
	रुको_queue_head_t रुकोQ;
	पूर्णांक notअगरy_ack_expected;
	पूर्णांक abts_resp_expected;
	पूर्णांक modअगरy_lun_expected;
	atomic_t tgt_global_resets_count;
	काष्ठा list_head tgt_list_entry;
पूर्ण;

काष्ठा qla_tgt_sess_op अणु
	काष्ठा scsi_qla_host *vha;
	uपूर्णांक32_t chip_reset;
	काष्ठा atio_from_isp atio;
	काष्ठा work_काष्ठा work;
	काष्ठा list_head cmd_list;
	bool पातed;
	काष्ठा rsp_que *rsp;
पूर्ण;

क्रमागत trace_flags अणु
	TRC_NEW_CMD = BIT_0,
	TRC_DO_WORK = BIT_1,
	TRC_DO_WORK_ERR = BIT_2,
	TRC_XFR_RDY = BIT_3,
	TRC_XMIT_DATA = BIT_4,
	TRC_XMIT_STATUS = BIT_5,
	TRC_SRR_RSP =  BIT_6,
	TRC_SRR_XRDY = BIT_7,
	TRC_SRR_TERM = BIT_8,
	TRC_SRR_CTIO = BIT_9,
	TRC_FLUSH = BIT_10,
	TRC_CTIO_ERR = BIT_11,
	TRC_CTIO_DONE = BIT_12,
	TRC_CTIO_ABORTED =  BIT_13,
	TRC_CTIO_STRANGE = BIT_14,
	TRC_CMD_DONE = BIT_15,
	TRC_CMD_CHK_STOP = BIT_16,
	TRC_CMD_FREE = BIT_17,
	TRC_DATA_IN = BIT_18,
	TRC_ABORT = BIT_19,
	TRC_DIF_ERR = BIT_20,
पूर्ण;

काष्ठा qla_tgt_cmd अणु
	/*
	 * Do not move cmd_type field. it needs to line up with srb->cmd_type
	 */
	uपूर्णांक8_t cmd_type;
	uपूर्णांक8_t pad[7];
	काष्ठा se_cmd se_cmd;
	काष्ठा list_head sess_cmd_list;
	काष्ठा fc_port *sess;
	काष्ठा qla_qpair *qpair;
	uपूर्णांक32_t reset_count;
	पूर्णांक state;
	काष्ठा work_काष्ठा work;
	/* Sense buffer that will be mapped पूर्णांकo outgoing status */
	अचिन्हित अक्षर sense_buffer[TRANSPORT_SENSE_BUFFER];

	spinlock_t cmd_lock;
	/* to save extra sess dereferences */
	अचिन्हित पूर्णांक conf_compl_supported:1;
	अचिन्हित पूर्णांक sg_mapped:1;
	अचिन्हित पूर्णांक मुक्त_sg:1;
	अचिन्हित पूर्णांक ग_लिखो_data_transferred:1;
	अचिन्हित पूर्णांक q_full:1;
	अचिन्हित पूर्णांक term_exchg:1;
	अचिन्हित पूर्णांक cmd_sent_to_fw:1;
	अचिन्हित पूर्णांक cmd_in_wq:1;

	/*
	 * This variable may be set from outside the LIO and I/O completion
	 * callback functions. Do not declare this member variable as a
	 * bitfield to aव्योम a पढ़ो-modअगरy-ग_लिखो operation when this variable
	 * is set.
	 */
	अचिन्हित पूर्णांक पातed;

	काष्ठा scatterlist *sg;	/* cmd data buffer SG vector */
	पूर्णांक sg_cnt;		/* SG segments count */
	पूर्णांक bufflen;		/* cmd buffer length */
	पूर्णांक offset;
	u64 unpacked_lun;
	क्रमागत dma_data_direction dma_data_direction;

	uपूर्णांक16_t ctio_flags;
	uपूर्णांक16_t vp_idx;
	uपूर्णांक16_t loop_id;	/* to save extra sess dereferences */
	काष्ठा qla_tgt *tgt;	/* to save extra sess dereferences */
	काष्ठा scsi_qla_host *vha;
	काष्ठा list_head cmd_list;

	काष्ठा atio_from_isp atio;

	uपूर्णांक8_t ctx_dsd_alloced;

	/* T10-DIF */
#घोषणा DIF_ERR_NONE 0
#घोषणा DIF_ERR_GRD 1
#घोषणा DIF_ERR_REF 2
#घोषणा DIF_ERR_APP 3
	पूर्णांक8_t dअगर_err_code;
	काष्ठा scatterlist *prot_sg;
	uपूर्णांक32_t prot_sg_cnt;
	uपूर्णांक32_t blk_sz, num_blks;
	uपूर्णांक8_t scsi_status, sense_key, asc, ascq;

	काष्ठा crc_context *ctx;
	स्थिर uपूर्णांक8_t	*cdb;
	uपूर्णांक64_t	lba;
	uपूर्णांक16_t	a_guard, e_guard, a_app_tag, e_app_tag;
	uपूर्णांक32_t	a_ref_tag, e_ref_tag;
#घोषणा DIF_BUNDL_DMA_VALID 1
	uपूर्णांक16_t prot_flags;

	uपूर्णांक64_t jअगरfies_at_alloc;
	uपूर्णांक64_t jअगरfies_at_मुक्त;

	क्रमागत trace_flags trc_flags;
पूर्ण;

काष्ठा qla_tgt_sess_work_param अणु
	काष्ठा list_head sess_works_list_entry;

#घोषणा QLA_TGT_SESS_WORK_ABORT	1
#घोषणा QLA_TGT_SESS_WORK_TM	2
	पूर्णांक type;

	जोड़ अणु
		काष्ठा abts_recv_from_24xx abts;
		काष्ठा imm_ntfy_from_isp पंचांग_iocb;
		काष्ठा atio_from_isp पंचांग_iocb2;
	पूर्ण;
पूर्ण;

काष्ठा qla_tgt_mgmt_cmd अणु
	uपूर्णांक8_t cmd_type;
	uपूर्णांक8_t pad[3];
	uपूर्णांक16_t पंचांगr_func;
	uपूर्णांक8_t fc_पंचांग_rsp;
	uपूर्णांक8_t पात_io_attr;
	काष्ठा fc_port *sess;
	काष्ठा qla_qpair *qpair;
	काष्ठा scsi_qla_host *vha;
	काष्ठा se_cmd se_cmd;
	काष्ठा work_काष्ठा मुक्त_work;
	अचिन्हित पूर्णांक flags;
#घोषणा QLA24XX_MGMT_SEND_NACK	BIT_0
#घोषणा QLA24XX_MGMT_ABORT_IO_ATTR_VALID BIT_1
	uपूर्णांक32_t reset_count;
	काष्ठा work_काष्ठा work;
	uपूर्णांक64_t unpacked_lun;
	जोड़ अणु
		काष्ठा atio_from_isp atio;
		काष्ठा imm_ntfy_from_isp imm_ntfy;
		काष्ठा abts_recv_from_24xx abts;
	पूर्ण __packed orig_iocb;
पूर्ण;

काष्ठा qla_tgt_prm अणु
	काष्ठा qla_tgt_cmd *cmd;
	काष्ठा qla_tgt *tgt;
	व्योम *pkt;
	काष्ठा scatterlist *sg;	/* cmd data buffer SG vector */
	अचिन्हित अक्षर *sense_buffer;
	पूर्णांक seg_cnt;
	पूर्णांक req_cnt;
	uपूर्णांक16_t rq_result;
	पूर्णांक sense_buffer_len;
	पूर्णांक residual;
	पूर्णांक add_status_pkt;
	/* dअगर */
	काष्ठा scatterlist *prot_sg;
	uपूर्णांक16_t prot_seg_cnt;
	uपूर्णांक16_t tot_dsds;
पूर्ण;

/* Check क्रम Switch reserved address */
#घोषणा IS_SW_RESV_ADDR(_s_id) \
	((_s_id.b.करोमुख्य == 0xff) && ((_s_id.b.area & 0xf0) == 0xf0))

#घोषणा QLA_TGT_XMIT_DATA		1
#घोषणा QLA_TGT_XMIT_STATUS		2
#घोषणा QLA_TGT_XMIT_ALL		(QLA_TGT_XMIT_STATUS|QLA_TGT_XMIT_DATA)


बाह्य काष्ठा qla_tgt_data qla_target;

/*
 * Function prototypes क्रम qla_target.c logic used by qla2xxx LLD code.
 */
बाह्य पूर्णांक qlt_add_target(काष्ठा qla_hw_data *, काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qlt_हटाओ_target(काष्ठा qla_hw_data *, काष्ठा scsi_qla_host *);
बाह्य पूर्णांक qlt_lport_रेजिस्टर(व्योम *, u64, u64, u64,
			पूर्णांक (*callback)(काष्ठा scsi_qla_host *, व्योम *, u64, u64));
बाह्य व्योम qlt_lport_deरेजिस्टर(काष्ठा scsi_qla_host *);
बाह्य व्योम qlt_unreg_sess(काष्ठा fc_port *);
बाह्य व्योम qlt_fc_port_added(काष्ठा scsi_qla_host *, fc_port_t *);
बाह्य व्योम qlt_fc_port_deleted(काष्ठा scsi_qla_host *, fc_port_t *, पूर्णांक);
बाह्य पूर्णांक __init qlt_init(व्योम);
बाह्य व्योम qlt_निकास(व्योम);
बाह्य व्योम qlt_update_vp_map(काष्ठा scsi_qla_host *, पूर्णांक);
बाह्य व्योम qlt_मुक्त_session_करोne(काष्ठा work_काष्ठा *);
/*
 * This macro is used during early initializations when host->active_mode
 * is not set. Right now, ha value is ignored.
 */
#घोषणा QLA_TGT_MODE_ENABLED() (ql2x_ini_mode != QLA2XXX_INI_MODE_ENABLED)

बाह्य पूर्णांक ql2x_ini_mode;

अटल अंतरभूत bool qla_tgt_mode_enabled(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->host->active_mode == MODE_TARGET;
पूर्ण

अटल अंतरभूत bool qla_ini_mode_enabled(काष्ठा scsi_qla_host *ha)
अणु
	वापस ha->host->active_mode == MODE_INITIATOR;
पूर्ण

अटल अंतरभूत bool qla_dual_mode_enabled(काष्ठा scsi_qla_host *ha)
अणु
	वापस (ha->host->active_mode == MODE_DUAL);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t sid_to_key(स्थिर be_id_t s_id)
अणु
	वापस s_id.करोमुख्य << 16 |
		s_id.area << 8 |
		s_id.al_pa;
पूर्ण

/*
 * Exported symbols from qla_target.c LLD logic used by qla2xxx code..
 */
बाह्य व्योम qlt_response_pkt_all_vps(काष्ठा scsi_qla_host *, काष्ठा rsp_que *,
	response_t *);
बाह्य पूर्णांक qlt_rdy_to_xfer(काष्ठा qla_tgt_cmd *);
बाह्य पूर्णांक qlt_xmit_response(काष्ठा qla_tgt_cmd *, पूर्णांक, uपूर्णांक8_t);
बाह्य पूर्णांक qlt_पात_cmd(काष्ठा qla_tgt_cmd *);
बाह्य व्योम qlt_xmit_पंचांग_rsp(काष्ठा qla_tgt_mgmt_cmd *);
बाह्य व्योम qlt_मुक्त_mcmd(काष्ठा qla_tgt_mgmt_cmd *);
बाह्य व्योम qlt_मुक्त_cmd(काष्ठा qla_tgt_cmd *cmd);
बाह्य व्योम qlt_async_event(uपूर्णांक16_t, काष्ठा scsi_qla_host *, uपूर्णांक16_t *);
बाह्य व्योम qlt_enable_vha(काष्ठा scsi_qla_host *);
बाह्य व्योम qlt_vport_create(काष्ठा scsi_qla_host *, काष्ठा qla_hw_data *);
बाह्य u8 qlt_rff_id(काष्ठा scsi_qla_host *);
बाह्य व्योम qlt_init_atio_q_entries(काष्ठा scsi_qla_host *);
बाह्य व्योम qlt_24xx_process_atio_queue(काष्ठा scsi_qla_host *, uपूर्णांक8_t);
बाह्य व्योम qlt_24xx_config_rings(काष्ठा scsi_qla_host *);
बाह्य व्योम qlt_24xx_config_nvram_stage1(काष्ठा scsi_qla_host *,
	काष्ठा nvram_24xx *);
बाह्य व्योम qlt_24xx_config_nvram_stage2(काष्ठा scsi_qla_host *,
	काष्ठा init_cb_24xx *);
बाह्य व्योम qlt_81xx_config_nvram_stage2(काष्ठा scsi_qla_host *,
	काष्ठा init_cb_81xx *);
बाह्य व्योम qlt_81xx_config_nvram_stage1(काष्ठा scsi_qla_host *,
	काष्ठा nvram_81xx *);
बाह्य पूर्णांक qlt_24xx_process_response_error(काष्ठा scsi_qla_host *,
	काष्ठा sts_entry_24xx *);
बाह्य व्योम qlt_modअगरy_vp_config(काष्ठा scsi_qla_host *,
	काष्ठा vp_config_entry_24xx *);
बाह्य व्योम qlt_probe_one_stage1(काष्ठा scsi_qla_host *, काष्ठा qla_hw_data *);
बाह्य पूर्णांक qlt_mem_alloc(काष्ठा qla_hw_data *);
बाह्य व्योम qlt_mem_मुक्त(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qlt_stop_phase1(काष्ठा qla_tgt *);
बाह्य व्योम qlt_stop_phase2(काष्ठा qla_tgt *);
बाह्य irqवापस_t qla83xx_msix_atio_q(पूर्णांक, व्योम *);
बाह्य व्योम qlt_83xx_iospace_config(काष्ठा qla_hw_data *);
बाह्य पूर्णांक qlt_मुक्त_qfull_cmds(काष्ठा qla_qpair *);
बाह्य व्योम qlt_logo_completion_handler(fc_port_t *, पूर्णांक);
बाह्य व्योम qlt_करो_generation_tick(काष्ठा scsi_qla_host *, पूर्णांक *);

व्योम qlt_send_resp_ctio(काष्ठा qla_qpair *, काष्ठा qla_tgt_cmd *, uपूर्णांक8_t,
    uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t);

#पूर्ण_अगर /* __QLA_TARGET_H */

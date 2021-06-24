<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_CORE_H
#घोषणा ISCSI_TARGET_CORE_H

#समावेश <linux/dma-direction.h>     /* क्रमागत dma_data_direction */
#समावेश <linux/list.h>              /* काष्ठा list_head */
#समावेश <linux/sched.h>
#समावेश <linux/socket.h>            /* काष्ठा sockaddr_storage */
#समावेश <linux/types.h>             /* u8 */
#समावेश <scsi/iscsi_proto.h>        /* itt_t */
#समावेश <target/target_core_base.h> /* काष्ठा se_cmd */

काष्ठा sock;

#घोषणा ISCSIT_VERSION			"v4.1.0"
#घोषणा ISCSI_MAX_DATASN_MISSING_COUNT	16
#घोषणा ISCSI_TX_THREAD_TCP_TIMEOUT	2
#घोषणा ISCSI_RX_THREAD_TCP_TIMEOUT	2
#घोषणा SECONDS_FOR_ASYNC_LOGOUT	10
#घोषणा SECONDS_FOR_ASYNC_TEXT		10
#घोषणा SECONDS_FOR_LOGOUT_COMP		15
#घोषणा WHITE_SPACE			" \t\v\f\n\r"
#घोषणा ISCSIT_MIN_TAGS			16
#घोषणा ISCSIT_EXTRA_TAGS		8
#घोषणा ISCSIT_TCP_BACKLOG		256
#घोषणा ISCSI_RX_THREAD_NAME		"iscsi_trx"
#घोषणा ISCSI_TX_THREAD_NAME		"iscsi_ttx"
#घोषणा ISCSI_IQN_LEN			224

/* काष्ठा iscsi_node_attrib sanity values */
#घोषणा NA_DATAOUT_TIMEOUT		3
#घोषणा NA_DATAOUT_TIMEOUT_MAX		60
#घोषणा NA_DATAOUT_TIMEOUT_MIX		2
#घोषणा NA_DATAOUT_TIMEOUT_RETRIES	5
#घोषणा NA_DATAOUT_TIMEOUT_RETRIES_MAX	15
#घोषणा NA_DATAOUT_TIMEOUT_RETRIES_MIN	1
#घोषणा NA_NOPIN_TIMEOUT		15
#घोषणा NA_NOPIN_TIMEOUT_MAX		60
#घोषणा NA_NOPIN_TIMEOUT_MIN		3
#घोषणा NA_NOPIN_RESPONSE_TIMEOUT	30
#घोषणा NA_NOPIN_RESPONSE_TIMEOUT_MAX	60
#घोषणा NA_NOPIN_RESPONSE_TIMEOUT_MIN	3
#घोषणा NA_RANDOM_DATAIN_PDU_OFFSETS	0
#घोषणा NA_RANDOM_DATAIN_SEQ_OFFSETS	0
#घोषणा NA_RANDOM_R2T_OFFSETS		0

/* काष्ठा iscsi_tpg_attrib sanity values */
#घोषणा TA_AUTHENTICATION		1
#घोषणा TA_LOGIN_TIMEOUT		15
#घोषणा TA_LOGIN_TIMEOUT_MAX		30
#घोषणा TA_LOGIN_TIMEOUT_MIN		5
#घोषणा TA_NETIF_TIMEOUT		2
#घोषणा TA_NETIF_TIMEOUT_MAX		15
#घोषणा TA_NETIF_TIMEOUT_MIN		2
#घोषणा TA_GENERATE_NODE_ACLS		0
#घोषणा TA_DEFAULT_CMDSN_DEPTH		64
#घोषणा TA_DEFAULT_CMDSN_DEPTH_MAX	512
#घोषणा TA_DEFAULT_CMDSN_DEPTH_MIN	1
#घोषणा TA_CACHE_DYNAMIC_ACLS		0
/* Enabled by शेष in demo mode (generic_node_acls=1) */
#घोषणा TA_DEMO_MODE_WRITE_PROTECT	1
/* Disabled by शेष in production mode w/ explict ACLs */
#घोषणा TA_PROD_MODE_WRITE_PROTECT	0
#घोषणा TA_DEMO_MODE_DISCOVERY		1
#घोषणा TA_DEFAULT_ERL			0
#घोषणा TA_CACHE_CORE_NPS		0
/* T10 protection inक्रमmation disabled by शेष */
#घोषणा TA_DEFAULT_T10_PI		0
#घोषणा TA_DEFAULT_FABRIC_PROT_TYPE	0
/* TPG status needs to be enabled to वापस sendtarमाला_लो discovery endpoपूर्णांक info */
#घोषणा TA_DEFAULT_TPG_ENABLED_SENDTARGETS 1
/*
 * Used to control the sending of keys with optional to respond state bit,
 * as a workaround क्रम non RFC compliant initiators,that करो not propose,
 * nor respond to specअगरic keys required क्रम login to complete.
 *
 * See iscsi_check_proposer_क्रम_optional_reply() क्रम more details.
 */
#घोषणा TA_DEFAULT_LOGIN_KEYS_WORKAROUND 1

#घोषणा ISCSI_IOV_DATA_BUFFER		5

क्रमागत iscsit_transport_type अणु
	ISCSI_TCP				= 0,
	ISCSI_SCTP_TCP				= 1,
	ISCSI_SCTP_UDP				= 2,
	ISCSI_IWARP_TCP				= 3,
	ISCSI_IWARP_SCTP			= 4,
	ISCSI_INFINIBAND			= 5,
	ISCSI_CXGBIT				= 6,
पूर्ण;

/* RFC-3720 7.1.4  Standard Connection State Diagram क्रम a Target */
क्रमागत target_conn_state_table अणु
	TARG_CONN_STATE_FREE			= 0x1,
	TARG_CONN_STATE_XPT_UP			= 0x3,
	TARG_CONN_STATE_IN_LOGIN		= 0x4,
	TARG_CONN_STATE_LOGGED_IN		= 0x5,
	TARG_CONN_STATE_IN_LOGOUT		= 0x6,
	TARG_CONN_STATE_LOGOUT_REQUESTED	= 0x7,
	TARG_CONN_STATE_CLEANUP_WAIT		= 0x8,
पूर्ण;

/* RFC-3720 7.3.2  Session State Diagram क्रम a Target */
क्रमागत target_sess_state_table अणु
	TARG_SESS_STATE_FREE			= 0x1,
	TARG_SESS_STATE_ACTIVE			= 0x2,
	TARG_SESS_STATE_LOGGED_IN		= 0x3,
	TARG_SESS_STATE_FAILED			= 0x4,
	TARG_SESS_STATE_IN_CONTINUE		= 0x5,
पूर्ण;

/* काष्ठा iscsi_data_count->type */
क्रमागत data_count_type अणु
	ISCSI_RX_DATA	= 1,
	ISCSI_TX_DATA	= 2,
पूर्ण;

/* काष्ठा iscsi_datain_req->dr_complete */
क्रमागत datain_req_comp_table अणु
	DATAIN_COMPLETE_NORMAL			= 1,
	DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY = 2,
	DATAIN_COMPLETE_CONNECTION_RECOVERY	= 3,
पूर्ण;

/* काष्ठा iscsi_datain_req->recovery */
क्रमागत datain_req_rec_table अणु
	DATAIN_WITHIN_COMMAND_RECOVERY		= 1,
	DATAIN_CONNECTION_RECOVERY		= 2,
पूर्ण;

/* काष्ठा iscsi_portal_group->state */
क्रमागत tpg_state_table अणु
	TPG_STATE_FREE				= 0,
	TPG_STATE_ACTIVE			= 1,
	TPG_STATE_INACTIVE			= 2,
	TPG_STATE_COLD_RESET			= 3,
पूर्ण;

/* काष्ठा iscsi_tiqn->tiqn_state */
क्रमागत tiqn_state_table अणु
	TIQN_STATE_ACTIVE			= 1,
	TIQN_STATE_SHUTDOWN			= 2,
पूर्ण;

/* काष्ठा iscsi_cmd->cmd_flags */
क्रमागत cmd_flags_table अणु
	ICF_GOT_LAST_DATAOUT			= 0x00000001,
	ICF_GOT_DATACK_SNACK			= 0x00000002,
	ICF_NON_IMMEDIATE_UNSOLICITED_DATA	= 0x00000004,
	ICF_SENT_LAST_R2T			= 0x00000008,
	ICF_WITHIN_COMMAND_RECOVERY		= 0x00000010,
	ICF_CONTIG_MEMORY			= 0x00000020,
	ICF_ATTACHED_TO_RQUEUE			= 0x00000040,
	ICF_OOO_CMDSN				= 0x00000080,
	ICF_SENDTARGETS_ALL			= 0x00000100,
	ICF_SENDTARGETS_SINGLE			= 0x00000200,
पूर्ण;

/* काष्ठा iscsi_cmd->i_state */
क्रमागत cmd_i_state_table अणु
	ISTATE_NO_STATE			= 0,
	ISTATE_NEW_CMD			= 1,
	ISTATE_DEFERRED_CMD		= 2,
	ISTATE_UNSOLICITED_DATA		= 3,
	ISTATE_RECEIVE_DATAOUT		= 4,
	ISTATE_RECEIVE_DATAOUT_RECOVERY	= 5,
	ISTATE_RECEIVED_LAST_DATAOUT	= 6,
	ISTATE_WITHIN_DATAOUT_RECOVERY	= 7,
	ISTATE_IN_CONNECTION_RECOVERY	= 8,
	ISTATE_RECEIVED_TASKMGT		= 9,
	ISTATE_SEND_ASYNCMSG		= 10,
	ISTATE_SENT_ASYNCMSG		= 11,
	ISTATE_SEND_DATAIN		= 12,
	ISTATE_SEND_LAST_DATAIN		= 13,
	ISTATE_SENT_LAST_DATAIN		= 14,
	ISTATE_SEND_LOGOUTRSP		= 15,
	ISTATE_SENT_LOGOUTRSP		= 16,
	ISTATE_SEND_NOPIN		= 17,
	ISTATE_SENT_NOPIN		= 18,
	ISTATE_SEND_REJECT		= 19,
	ISTATE_SENT_REJECT		= 20,
	ISTATE_SEND_R2T			= 21,
	ISTATE_SENT_R2T			= 22,
	ISTATE_SEND_R2T_RECOVERY	= 23,
	ISTATE_SENT_R2T_RECOVERY	= 24,
	ISTATE_SEND_LAST_R2T		= 25,
	ISTATE_SENT_LAST_R2T		= 26,
	ISTATE_SEND_LAST_R2T_RECOVERY	= 27,
	ISTATE_SENT_LAST_R2T_RECOVERY	= 28,
	ISTATE_SEND_STATUS		= 29,
	ISTATE_SEND_STATUS_BROKEN_PC	= 30,
	ISTATE_SENT_STATUS		= 31,
	ISTATE_SEND_STATUS_RECOVERY	= 32,
	ISTATE_SENT_STATUS_RECOVERY	= 33,
	ISTATE_SEND_TASKMGTRSP		= 34,
	ISTATE_SENT_TASKMGTRSP		= 35,
	ISTATE_SEND_TEXTRSP		= 36,
	ISTATE_SENT_TEXTRSP		= 37,
	ISTATE_SEND_NOPIN_WANT_RESPONSE	= 38,
	ISTATE_SENT_NOPIN_WANT_RESPONSE	= 39,
	ISTATE_SEND_NOPIN_NO_RESPONSE	= 40,
	ISTATE_REMOVE			= 41,
	ISTATE_FREE			= 42,
पूर्ण;

/* Used क्रम iscsi_recover_cmdsn() वापस values */
क्रमागत recover_cmdsn_ret_table अणु
	CMDSN_ERROR_CANNOT_RECOVER	= -1,
	CMDSN_NORMAL_OPERATION		= 0,
	CMDSN_LOWER_THAN_EXP		= 1,
	CMDSN_HIGHER_THAN_EXP		= 2,
	CMDSN_MAXCMDSN_OVERRUN		= 3,
पूर्ण;

/* Used क्रम iscsi_handle_immediate_data() वापस values */
क्रमागत immedate_data_ret_table अणु
	IMMEDIATE_DATA_CANNOT_RECOVER	= -1,
	IMMEDIATE_DATA_NORMAL_OPERATION = 0,
	IMMEDIATE_DATA_ERL1_CRC_FAILURE = 1,
पूर्ण;

/* Used क्रम iscsi_decide_dataout_action() वापस values */
क्रमागत dataout_action_ret_table अणु
	DATAOUT_CANNOT_RECOVER		= -1,
	DATAOUT_NORMAL			= 0,
	DATAOUT_SEND_R2T		= 1,
	DATAOUT_SEND_TO_TRANSPORT	= 2,
	DATAOUT_WITHIN_COMMAND_RECOVERY = 3,
पूर्ण;

/* Used क्रम काष्ठा iscsi_node_auth->naf_flags */
क्रमागत naf_flags_table अणु
	NAF_USERID_SET			= 0x01,
	NAF_PASSWORD_SET		= 0x02,
	NAF_USERID_IN_SET		= 0x04,
	NAF_PASSWORD_IN_SET		= 0x08,
पूर्ण;

/* Used by various काष्ठा समयr_list to manage iSCSI specअगरic state */
क्रमागत iscsi_समयr_flags_table अणु
	ISCSI_TF_RUNNING		= 0x01,
	ISCSI_TF_STOP			= 0x02,
	ISCSI_TF_EXPIRED		= 0x04,
पूर्ण;

/* Used क्रम काष्ठा iscsi_np->np_flags */
क्रमागत np_flags_table अणु
	NPF_IP_NETWORK		= 0x00,
पूर्ण;

/* Used क्रम काष्ठा iscsi_np->np_thपढ़ो_state */
क्रमागत np_thपढ़ो_state_table अणु
	ISCSI_NP_THREAD_ACTIVE		= 1,
	ISCSI_NP_THREAD_INACTIVE	= 2,
	ISCSI_NP_THREAD_RESET		= 3,
	ISCSI_NP_THREAD_SHUTDOWN	= 4,
	ISCSI_NP_THREAD_EXIT		= 5,
पूर्ण;

काष्ठा iscsi_conn_ops अणु
	u8	HeaderDigest;			/* [0,1] == [None,CRC32C] */
	u8	DataDigest;			/* [0,1] == [None,CRC32C] */
	u32	MaxRecvDataSegmentLength;	/* [512..2**24-1] */
	u32	MaxXmitDataSegmentLength;	/* [512..2**24-1] */
	/*
	 * iSER specअगरic connection parameters
	 */
	u32	InitiatorRecvDataSegmentLength;	/* [512..2**24-1] */
	u32	TargetRecvDataSegmentLength;	/* [512..2**24-1] */
पूर्ण;

काष्ठा iscsi_sess_ops अणु
	अक्षर	InitiatorName[ISCSI_IQN_LEN];
	अक्षर	InitiatorAlias[256];
	अक्षर	TargetName[ISCSI_IQN_LEN];
	अक्षर	TargetAlias[256];
	अक्षर	TargetAddress[256];
	u16	TargetPortalGroupTag;		/* [0..65535] */
	u16	MaxConnections;			/* [1..65535] */
	u8	InitialR2T;			/* [0,1] == [No,Yes] */
	u8	ImmediateData;			/* [0,1] == [No,Yes] */
	u32	MaxBurstLength;			/* [512..2**24-1] */
	u32	FirstBurstLength;		/* [512..2**24-1] */
	u16	DefaultTime2Wait;		/* [0..3600] */
	u16	DefaultTime2Retain;		/* [0..3600] */
	u16	MaxOutstandingR2T;		/* [1..65535] */
	u8	DataPDUInOrder;			/* [0,1] == [No,Yes] */
	u8	DataSequenceInOrder;		/* [0,1] == [No,Yes] */
	u8	ErrorRecoveryLevel;		/* [0..2] */
	u8	SessionType;			/* [0,1] == [Normal,Discovery]*/
	/*
	 * iSER specअगरic session parameters
	 */
	u8	RDMAExtensions;			/* [0,1] == [No,Yes] */
पूर्ण;

काष्ठा iscsi_queue_req अणु
	पूर्णांक			state;
	काष्ठा iscsi_cmd	*cmd;
	काष्ठा list_head	qr_list;
पूर्ण;

काष्ठा iscsi_param_list अणु
	bool			iser;
	काष्ठा list_head	param_list;
	काष्ठा list_head	extra_response_list;
पूर्ण;

काष्ठा iscsi_datain_req अणु
	क्रमागत datain_req_comp_table dr_complete;
	पूर्णांक			generate_recovery_values;
	क्रमागत datain_req_rec_table recovery;
	u32			begrun;
	u32			runlength;
	u32			data_length;
	u32			data_offset;
	u32			data_sn;
	u32			next_burst_len;
	u32			पढ़ो_data_करोne;
	u32			seq_send_order;
	काष्ठा list_head	cmd_datain_node;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_ooo_cmdsn अणु
	u16			cid;
	u32			batch_count;
	u32			cmdsn;
	u32			exp_cmdsn;
	काष्ठा iscsi_cmd	*cmd;
	काष्ठा list_head	ooo_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_datain अणु
	u8			flags;
	u32			data_sn;
	u32			length;
	u32			offset;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_r2t अणु
	पूर्णांक			seq_complete;
	पूर्णांक			recovery_r2t;
	पूर्णांक			sent_r2t;
	u32			r2t_sn;
	u32			offset;
	u32			targ_xfer_tag;
	u32			xfer_len;
	काष्ठा list_head	r2t_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_cmd अणु
	क्रमागत iscsi_समयr_flags_table dataout_समयr_flags;
	/* DataOUT समयout retries */
	u8			dataout_समयout_retries;
	/* Within command recovery count */
	u8			error_recovery_count;
	/* iSCSI dependent state क्रम out or order CmdSNs */
	क्रमागत cmd_i_state_table	deferred_i_state;
	/* iSCSI dependent state */
	क्रमागत cmd_i_state_table	i_state;
	/* Command is an immediate command (ISCSI_OP_IMMEDIATE set) */
	u8			immediate_cmd;
	/* Immediate data present */
	u8			immediate_data;
	/* iSCSI Opcode */
	u8			iscsi_opcode;
	/* iSCSI Response Code */
	u8			iscsi_response;
	/* Logout reason when iscsi_opcode == ISCSI_INIT_LOGOUT_CMND */
	u8			logout_reason;
	/* Logout response code when iscsi_opcode == ISCSI_INIT_LOGOUT_CMND */
	u8			logout_response;
	/* MaxCmdSN has been incremented */
	u8			maxcmdsn_inc;
	/* Immediate Unsolicited Dataout */
	u8			unsolicited_data;
	/* Reject reason code */
	u8			reject_reason;
	/* CID contained in logout PDU when opcode == ISCSI_INIT_LOGOUT_CMND */
	u16			logout_cid;
	/* Command flags */
	क्रमागत cmd_flags_table	cmd_flags;
	/* Initiator Task Tag asचिन्हित from Initiator */
	itt_t			init_task_tag;
	/* Target Transfer Tag asचिन्हित from Target */
	u32			targ_xfer_tag;
	/* CmdSN asचिन्हित from Initiator */
	u32			cmd_sn;
	/* ExpStatSN asचिन्हित from Initiator */
	u32			exp_stat_sn;
	/* StatSN asचिन्हित to this ITT */
	u32			stat_sn;
	/* DataSN Counter */
	u32			data_sn;
	/* R2TSN Counter */
	u32			r2t_sn;
	/* Last DataSN acknowledged via DataAck SNACK */
	u32			acked_data_sn;
	/* Used क्रम echoing NOPOUT ping data */
	u32			buf_ptr_size;
	/* Used to store DataDigest */
	u32			data_crc;
	/* Counter क्रम MaxOutstandingR2T */
	u32			outstanding_r2ts;
	/* Next R2T Offset when DataSequenceInOrder=Yes */
	u32			r2t_offset;
	/* Iovec current and orig count क्रम iscsi_cmd->iov_data */
	u32			iov_data_count;
	u32			orig_iov_data_count;
	/* Number of miscellaneous iovecs used क्रम IP stack calls */
	u32			iov_misc_count;
	/* Number of काष्ठा iscsi_pdu in काष्ठा iscsi_cmd->pdu_list */
	u32			pdu_count;
	/* Next काष्ठा iscsi_pdu to send in काष्ठा iscsi_cmd->pdu_list */
	u32			pdu_send_order;
	/* Current काष्ठा iscsi_pdu in काष्ठा iscsi_cmd->pdu_list */
	u32			pdu_start;
	/* Next काष्ठा iscsi_seq to send in काष्ठा iscsi_cmd->seq_list */
	u32			seq_send_order;
	/* Number of काष्ठा iscsi_seq in काष्ठा iscsi_cmd->seq_list */
	u32			seq_count;
	/* Current काष्ठा iscsi_seq in काष्ठा iscsi_cmd->seq_list */
	u32			seq_no;
	/* Lowest offset in current DataOUT sequence */
	u32			seq_start_offset;
	/* Highest offset in current DataOUT sequence */
	u32			seq_end_offset;
	/* Total size in bytes received so far of READ data */
	u32			पढ़ो_data_करोne;
	/* Total size in bytes received so far of WRITE data */
	u32			ग_लिखो_data_करोne;
	/* Counter क्रम FirstBurstLength key */
	u32			first_burst_len;
	/* Counter क्रम MaxBurstLength key */
	u32			next_burst_len;
	/* Transfer size used क्रम IP stack calls */
	u32			tx_size;
	/* Buffer used क्रम various purposes */
	व्योम			*buf_ptr;
	/* Used by SendTarमाला_लो=[iqn.,eui.] discovery */
	व्योम			*text_in_ptr;
	/* See include/linux/dma-mapping.h */
	क्रमागत dma_data_direction	data_direction;
	/* iSCSI PDU Header + CRC */
	अचिन्हित अक्षर		pdu[ISCSI_HDR_LEN + ISCSI_CRC_LEN];
	/* Number of बार काष्ठा iscsi_cmd is present in immediate queue */
	atomic_t		immed_queue_count;
	atomic_t		response_queue_count;
	spinlock_t		datain_lock;
	spinlock_t		dataout_समयout_lock;
	/* spinlock क्रम protecting काष्ठा iscsi_cmd->i_state */
	spinlock_t		istate_lock;
	/* spinlock क्रम adding within command recovery entries */
	spinlock_t		error_lock;
	/* spinlock क्रम adding R2Ts */
	spinlock_t		r2t_lock;
	/* DataIN List */
	काष्ठा list_head	datain_list;
	/* R2T List */
	काष्ठा list_head	cmd_r2t_list;
	/* Timer क्रम DataOUT */
	काष्ठा समयr_list	dataout_समयr;
	/* Iovecs क्रम SCSI data payload RX/TX w/ kernel level sockets */
	काष्ठा kvec		*iov_data;
	व्योम			*overflow_buf;
	/* Iovecs क्रम miscellaneous purposes */
#घोषणा ISCSI_MISC_IOVECS			5
	काष्ठा kvec		iov_misc[ISCSI_MISC_IOVECS];
	/* Array of काष्ठा iscsi_pdu used क्रम DataPDUInOrder=No */
	काष्ठा iscsi_pdu	*pdu_list;
	/* Current काष्ठा iscsi_pdu used क्रम DataPDUInOrder=No */
	काष्ठा iscsi_pdu	*pdu_ptr;
	/* Array of काष्ठा iscsi_seq used क्रम DataSequenceInOrder=No */
	काष्ठा iscsi_seq	*seq_list;
	/* Current काष्ठा iscsi_seq used क्रम DataSequenceInOrder=No */
	काष्ठा iscsi_seq	*seq_ptr;
	/* TMR Request when iscsi_opcode == ISCSI_OP_SCSI_TMFUNC */
	काष्ठा iscsi_पंचांगr_req	*पंचांगr_req;
	/* Connection this command is alligient to */
	काष्ठा iscsi_conn	*conn;
	/* Poपूर्णांकer to connection recovery entry */
	काष्ठा iscsi_conn_recovery *cr;
	/* Session the command is part of,  used क्रम connection recovery */
	काष्ठा iscsi_session	*sess;
	/* list_head क्रम connection list */
	काष्ठा list_head	i_conn_node;
	/* The TCM I/O descriptor that is accessed via container_of() */
	काष्ठा se_cmd		se_cmd;
	/* Sense buffer that will be mapped पूर्णांकo outgoing status */
#घोषणा ISCSI_SENSE_BUFFER_LEN          (TRANSPORT_SENSE_BUFFER + 2)
	अचिन्हित अक्षर		sense_buffer[ISCSI_SENSE_BUFFER_LEN];

	u32			padding;
	u8			pad_bytes[4];

	काष्ठा scatterlist	*first_data_sg;
	u32			first_data_sg_off;
	u32			kmapped_nents;
	sense_reason_t		sense_reason;
पूर्ण  ____cacheline_aligned;

काष्ठा iscsi_पंचांगr_req अणु
	bool			task_reassign:1;
	u32			exp_data_sn;
	काष्ठा iscsi_cmd	*ref_cmd;
	काष्ठा iscsi_conn_recovery *conn_recovery;
	काष्ठा se_पंचांगr_req	*se_पंचांगr_req;
पूर्ण;

काष्ठा iscsi_conn अणु
	रुको_queue_head_t	queues_wq;
	/* Authentication Successful क्रम this connection */
	u8			auth_complete;
	/* State connection is currently in */
	u8			conn_state;
	u8			conn_logout_reason;
	u8			network_transport;
	क्रमागत iscsi_समयr_flags_table nopin_समयr_flags;
	क्रमागत iscsi_समयr_flags_table nopin_response_समयr_flags;
	/* Used to know what thपढ़ो encountered a transport failure */
	u8			which_thपढ़ो;
	/* connection id asचिन्हित by the Initiator */
	u16			cid;
	/* Remote TCP Port */
	u16			login_port;
	पूर्णांक			net_size;
	पूर्णांक			login_family;
	u32			auth_id;
	u32			conn_flags;
	/* Used क्रम iscsi_tx_login_rsp() */
	itt_t			login_itt;
	u32			exp_statsn;
	/* Per connection status sequence number */
	u32			stat_sn;
	काष्ठा sockaddr_storage login_sockaddr;
	काष्ठा sockaddr_storage local_sockaddr;
	पूर्णांक			conn_usage_count;
	पूर्णांक			conn_रुकोing_on_uc;
	atomic_t		check_immediate_queue;
	atomic_t		conn_logout_हटाओ;
	atomic_t		connection_निकास;
	atomic_t		connection_recovery;
	atomic_t		connection_reinstatement;
	atomic_t		connection_रुको_rcfr;
	atomic_t		sleep_on_conn_रुको_comp;
	atomic_t		transport_failed;
	काष्ठा completion	conn_post_रुको_comp;
	काष्ठा completion	conn_रुको_comp;
	काष्ठा completion	conn_रुको_rcfr_comp;
	काष्ठा completion	conn_रुकोing_on_uc_comp;
	काष्ठा completion	conn_logout_comp;
	काष्ठा completion	tx_half_बंद_comp;
	काष्ठा completion	rx_half_बंद_comp;
	/* socket used by this connection */
	काष्ठा socket		*sock;
	व्योम			(*orig_data_पढ़ोy)(काष्ठा sock *);
	व्योम			(*orig_state_change)(काष्ठा sock *);
#घोषणा LOGIN_FLAGS_READY		0
#घोषणा LOGIN_FLAGS_INITIAL_PDU		1
#घोषणा LOGIN_FLAGS_READ_ACTIVE		2
#घोषणा LOGIN_FLAGS_WRITE_ACTIVE	3
#घोषणा LOGIN_FLAGS_CLOSED		4
	अचिन्हित दीर्घ		login_flags;
	काष्ठा delayed_work	login_work;
	काष्ठा iscsi_login	*login;
	काष्ठा समयr_list	nopin_समयr;
	काष्ठा समयr_list	nopin_response_समयr;
	काष्ठा समयr_list	transport_समयr;
	काष्ठा task_काष्ठा	*login_kworker;
	/* Spinlock used क्रम add/deleting cmd's from conn_cmd_list */
	spinlock_t		cmd_lock;
	spinlock_t		conn_usage_lock;
	spinlock_t		immed_queue_lock;
	spinlock_t		nopin_समयr_lock;
	spinlock_t		response_queue_lock;
	spinlock_t		state_lock;
	/* libcrypto RX and TX contexts क्रम crc32c */
	काष्ठा ahash_request	*conn_rx_hash;
	काष्ठा ahash_request	*conn_tx_hash;
	/* Used क्रम scheduling TX and RX connection kthपढ़ोs */
	cpumask_var_t		conn_cpumask;
	अचिन्हित पूर्णांक		conn_rx_reset_cpumask:1;
	अचिन्हित पूर्णांक		conn_tx_reset_cpumask:1;
	/* list_head of काष्ठा iscsi_cmd क्रम this connection */
	काष्ठा list_head	conn_cmd_list;
	काष्ठा list_head	immed_queue_list;
	काष्ठा list_head	response_queue_list;
	काष्ठा iscsi_conn_ops	*conn_ops;
	काष्ठा iscsi_login	*conn_login;
	काष्ठा iscsit_transport *conn_transport;
	काष्ठा iscsi_param_list	*param_list;
	/* Used क्रम per connection auth state machine */
	व्योम			*auth_protocol;
	व्योम			*context;
	काष्ठा iscsi_login_thपढ़ो_s *login_thपढ़ो;
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np	*tpg_np;
	/* Poपूर्णांकer to parent session */
	काष्ठा iscsi_session	*sess;
	पूर्णांक			biपंचांगap_id;
	पूर्णांक			rx_thपढ़ो_active;
	काष्ठा task_काष्ठा	*rx_thपढ़ो;
	काष्ठा completion	rx_login_comp;
	पूर्णांक			tx_thपढ़ो_active;
	काष्ठा task_काष्ठा	*tx_thपढ़ो;
	/* list_head क्रम session connection list */
	काष्ठा list_head	conn_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_conn_recovery अणु
	u16			cid;
	u32			cmd_count;
	u32			maxrecvdatasegmentlength;
	u32			maxxmitdatasegmentlength;
	पूर्णांक			पढ़ोy_क्रम_reallegiance;
	काष्ठा list_head	conn_recovery_cmd_list;
	spinlock_t		conn_recovery_cmd_lock;
	काष्ठा समयr_list	समय2retain_समयr;
	काष्ठा iscsi_session	*sess;
	काष्ठा list_head	cr_list;
पूर्ण  ____cacheline_aligned;

काष्ठा iscsi_session अणु
	u8			initiator_venकरोr;
	u8			isid[6];
	क्रमागत iscsi_समयr_flags_table समय2retain_समयr_flags;
	u8			version_active;
	u16			cid_called;
	u16			conn_recovery_count;
	u16			tsih;
	/* state session is currently in */
	u32			session_state;
	/* session wide counter: initiator asचिन्हित task tag */
	itt_t			init_task_tag;
	/* session wide counter: target asचिन्हित task tag */
	u32			targ_xfer_tag;
	u32			cmdsn_winकरोw;

	/* protects cmdsn values */
	काष्ठा mutex		cmdsn_mutex;
	/* session wide counter: expected command sequence number */
	u32			exp_cmd_sn;
	/* session wide counter: maximum allowed command sequence number */
	atomic_t		max_cmd_sn;
	काष्ठा list_head	sess_ooo_cmdsn_list;

	/* LIO specअगरic session ID */
	u32			sid;
	अक्षर			auth_type[8];
	/* unique within the target */
	पूर्णांक			session_index;
	/* Used क्रम session reference counting */
	पूर्णांक			session_usage_count;
	पूर्णांक			session_रुकोing_on_uc;
	atomic_दीर्घ_t		cmd_pdus;
	atomic_दीर्घ_t		rsp_pdus;
	atomic_दीर्घ_t		tx_data_octets;
	atomic_दीर्घ_t		rx_data_octets;
	atomic_दीर्घ_t		conn_digest_errors;
	atomic_दीर्घ_t		conn_समयout_errors;
	u64			creation_समय;
	/* Number of active connections */
	atomic_t		nconn;
	atomic_t		session_continuation;
	atomic_t		session_fall_back_to_erl0;
	atomic_t		session_logout;
	atomic_t		session_reinstatement;
	atomic_t		session_stop_active;
	atomic_t		session_बंद;
	/* connection list */
	काष्ठा list_head	sess_conn_list;
	काष्ठा list_head	cr_active_list;
	काष्ठा list_head	cr_inactive_list;
	spinlock_t		conn_lock;
	spinlock_t		cr_a_lock;
	spinlock_t		cr_i_lock;
	spinlock_t		session_usage_lock;
	spinlock_t		ttt_lock;
	काष्ठा completion	async_msg_comp;
	काष्ठा completion	reinstatement_comp;
	काष्ठा completion	session_रुको_comp;
	काष्ठा completion	session_रुकोing_on_uc_comp;
	काष्ठा समयr_list	समय2retain_समयr;
	काष्ठा iscsi_sess_ops	*sess_ops;
	काष्ठा se_session	*se_sess;
	काष्ठा iscsi_portal_group *tpg;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_login अणु
	u8 auth_complete;
	u8 checked_क्रम_existing;
	u8 current_stage;
	u8 leading_connection;
	u8 first_request;
	u8 version_min;
	u8 version_max;
	u8 login_complete;
	u8 login_failed;
	bool zero_tsih;
	अक्षर isid[6];
	u32 cmd_sn;
	itt_t init_task_tag;
	u32 initial_exp_statsn;
	u32 rsp_length;
	u16 cid;
	u16 tsih;
	अक्षर req[ISCSI_HDR_LEN];
	अक्षर rsp[ISCSI_HDR_LEN];
	अक्षर *req_buf;
	अक्षर *rsp_buf;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_np *np;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_node_attrib अणु
	u32			dataout_समयout;
	u32			dataout_समयout_retries;
	u32			शेष_erl;
	u32			nopin_समयout;
	u32			nopin_response_समयout;
	u32			अक्रमom_datain_pdu_offsets;
	u32			अक्रमom_datain_seq_offsets;
	u32			अक्रमom_r2t_offsets;
	u32			पंचांगr_cold_reset;
	u32			पंचांगr_warm_reset;
	काष्ठा iscsi_node_acl *nacl;
पूर्ण;

काष्ठा se_dev_entry_s;

काष्ठा iscsi_node_auth अणु
	क्रमागत naf_flags_table	naf_flags;
	पूर्णांक			authenticate_target;
	/* Used क्रम iscsit_global->discovery_auth,
	 * set to zero (auth disabled) by शेष */
	पूर्णांक			enक्रमce_discovery_auth;
#घोषणा MAX_USER_LEN				256
#घोषणा MAX_PASS_LEN				256
	अक्षर			userid[MAX_USER_LEN];
	अक्षर			password[MAX_PASS_LEN];
	अक्षर			userid_mutual[MAX_USER_LEN];
	अक्षर			password_mutual[MAX_PASS_LEN];
पूर्ण;

#समावेश "iscsi_target_stat.h"

काष्ठा iscsi_node_stat_grps अणु
	काष्ठा config_group	iscsi_sess_stats_group;
	काष्ठा config_group	iscsi_conn_stats_group;
पूर्ण;

काष्ठा iscsi_node_acl अणु
	काष्ठा se_node_acl	se_node_acl;
	काष्ठा iscsi_node_attrib node_attrib;
	काष्ठा iscsi_node_auth	node_auth;
	काष्ठा iscsi_node_stat_grps node_stat_grps;
पूर्ण;

काष्ठा iscsi_tpg_attrib अणु
	u32			authentication;
	u32			login_समयout;
	u32			netअगर_समयout;
	u32			generate_node_acls;
	u32			cache_dynamic_acls;
	u32			शेष_cmdsn_depth;
	u32			demo_mode_ग_लिखो_protect;
	u32			prod_mode_ग_लिखो_protect;
	u32			demo_mode_discovery;
	u32			शेष_erl;
	u8			t10_pi;
	u32			fabric_prot_type;
	u32			tpg_enabled_sendtarमाला_लो;
	u32			login_keys_workaround;
	काष्ठा iscsi_portal_group *tpg;
पूर्ण;

काष्ठा iscsi_np अणु
	पूर्णांक			np_network_transport;
	पूर्णांक			np_ip_proto;
	पूर्णांक			np_sock_type;
	क्रमागत np_thपढ़ो_state_table np_thपढ़ो_state;
	bool                    enabled;
	atomic_t		np_reset_count;
	क्रमागत iscsi_समयr_flags_table np_login_समयr_flags;
	u32			np_exports;
	क्रमागत np_flags_table	np_flags;
	spinlock_t		np_thपढ़ो_lock;
	काष्ठा completion	np_restart_comp;
	काष्ठा socket		*np_socket;
	काष्ठा sockaddr_storage np_sockaddr;
	काष्ठा task_काष्ठा	*np_thपढ़ो;
	काष्ठा समयr_list	np_login_समयr;
	व्योम			*np_context;
	काष्ठा iscsit_transport *np_transport;
	काष्ठा list_head	np_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_tpg_np अणु
	काष्ठा iscsi_np		*tpg_np;
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np	*tpg_np_parent;
	काष्ठा list_head	tpg_np_list;
	काष्ठा list_head	tpg_np_child_list;
	काष्ठा list_head	tpg_np_parent_list;
	काष्ठा se_tpg_np	se_tpg_np;
	spinlock_t		tpg_np_parent_lock;
	काष्ठा completion	tpg_np_comp;
	काष्ठा kref		tpg_np_kref;
पूर्ण;

काष्ठा iscsi_portal_group अणु
	अचिन्हित अक्षर		tpg_chap_id;
	/* TPG State */
	क्रमागत tpg_state_table	tpg_state;
	/* Target Portal Group Tag */
	u16			tpgt;
	/* Id asचिन्हित to target sessions */
	u16			ntsih;
	/* Number of active sessions */
	u32			nsessions;
	/* Number of Network Portals available क्रम this TPG */
	u32			num_tpg_nps;
	/* Per TPG LIO specअगरic session ID. */
	u32			sid;
	/* Spinlock क्रम adding/removing Network Portals */
	spinlock_t		tpg_np_lock;
	spinlock_t		tpg_state_lock;
	काष्ठा se_portal_group tpg_se_tpg;
	काष्ठा mutex		tpg_access_lock;
	काष्ठा semaphore	np_login_sem;
	काष्ठा iscsi_tpg_attrib	tpg_attrib;
	काष्ठा iscsi_node_auth	tpg_demo_auth;
	/* Poपूर्णांकer to शेष list of iSCSI parameters क्रम TPG */
	काष्ठा iscsi_param_list	*param_list;
	काष्ठा iscsi_tiqn	*tpg_tiqn;
	काष्ठा list_head	tpg_gnp_list;
	काष्ठा list_head	tpg_list;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_wwn_stat_grps अणु
	काष्ठा config_group	iscsi_stat_group;
	काष्ठा config_group	iscsi_instance_group;
	काष्ठा config_group	iscsi_sess_err_group;
	काष्ठा config_group	iscsi_tgt_attr_group;
	काष्ठा config_group	iscsi_login_stats_group;
	काष्ठा config_group	iscsi_logout_stats_group;
पूर्ण;

काष्ठा iscsi_tiqn अणु
	अचिन्हित अक्षर		tiqn[ISCSI_IQN_LEN];
	क्रमागत tiqn_state_table	tiqn_state;
	पूर्णांक			tiqn_access_count;
	u32			tiqn_active_tpgs;
	u32			tiqn_ntpgs;
	u32			tiqn_num_tpg_nps;
	u32			tiqn_nsessions;
	काष्ठा list_head	tiqn_list;
	काष्ठा list_head	tiqn_tpg_list;
	spinlock_t		tiqn_state_lock;
	spinlock_t		tiqn_tpg_lock;
	काष्ठा se_wwn		tiqn_wwn;
	काष्ठा iscsi_wwn_stat_grps tiqn_stat_grps;
	पूर्णांक			tiqn_index;
	काष्ठा iscsi_sess_err_stats  sess_err_stats;
	काष्ठा iscsi_login_stats     login_stats;
	काष्ठा iscsi_logout_stats    logout_stats;
पूर्ण ____cacheline_aligned;

काष्ठा iscsit_global अणु
	/* In core shutकरोwn */
	u32			in_shutकरोwn;
	u32			active_ts;
	/* Unique identअगरier used क्रम the authentication daemon */
	u32			auth_id;
	u32			inactive_ts;
#घोषणा ISCSIT_BITMAP_BITS	262144
	/* Thपढ़ो Set biपंचांगap poपूर्णांकer */
	अचिन्हित दीर्घ		*ts_biपंचांगap;
	spinlock_t		ts_biपंचांगap_lock;
	/* Used क्रम iSCSI discovery session authentication */
	काष्ठा iscsi_node_acl	discovery_acl;
	काष्ठा iscsi_portal_group	*discovery_tpg;
पूर्ण;

अटल अंतरभूत u32 session_get_next_ttt(काष्ठा iscsi_session *session)
अणु
	u32 ttt;

	spin_lock_bh(&session->ttt_lock);
	ttt = session->targ_xfer_tag++;
	अगर (ttt == 0xFFFFFFFF)
		ttt = session->targ_xfer_tag++;
	spin_unlock_bh(&session->ttt_lock);

	वापस ttt;
पूर्ण

बाह्य काष्ठा iscsi_cmd *iscsit_find_cmd_from_itt(काष्ठा iscsi_conn *, itt_t);

अटल अंतरभूत व्योम iscsit_thपढ़ो_check_cpumask(
	काष्ठा iscsi_conn *conn,
	काष्ठा task_काष्ठा *p,
	पूर्णांक mode)
अणु
	/*
	 * mode == 1 संकेतs iscsi_target_tx_thपढ़ो() usage.
	 * mode == 0 संकेतs iscsi_target_rx_thपढ़ो() usage.
	 */
	अगर (mode == 1) अणु
		अगर (!conn->conn_tx_reset_cpumask)
			वापस;
		conn->conn_tx_reset_cpumask = 0;
	पूर्ण अन्यथा अणु
		अगर (!conn->conn_rx_reset_cpumask)
			वापस;
		conn->conn_rx_reset_cpumask = 0;
	पूर्ण
	/*
	 * Update the CPU mask क्रम this single kthपढ़ो so that
	 * both TX and RX kthपढ़ोs are scheduled to run on the
	 * same CPU.
	 */
	set_cpus_allowed_ptr(p, conn->conn_cpumask);
पूर्ण
#पूर्ण_अगर /* ISCSI_TARGET_CORE_H */

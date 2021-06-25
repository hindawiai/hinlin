<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_BASE_H
#घोषणा TARGET_CORE_BASE_H

#समावेश <linux/configfs.h>      /* काष्ठा config_group */
#समावेश <linux/dma-direction.h> /* क्रमागत dma_data_direction */
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/semaphore.h>     /* काष्ठा semaphore */
#समावेश <linux/completion.h>

#घोषणा TARGET_CORE_VERSION		"v5.0"

/*
 * Maximum size of a CDB that can be stored in se_cmd without allocating
 * memory dynamically क्रम the CDB.
 */
#घोषणा TCM_MAX_COMMAND_SIZE			32
/*
 * From include/scsi/scsi_cmnd.h:SCSI_SENSE_BUFFERSIZE, currently
 * defined 96, but the real limit is 252 (or 260 including the header)
 */
#घोषणा TRANSPORT_SENSE_BUFFER			96
/* Used by transport_send_check_condition_and_sense() */
#घोषणा SPC_SENSE_KEY_OFFSET			2
#घोषणा SPC_ADD_SENSE_LEN_OFFSET		7
#घोषणा SPC_DESC_TYPE_OFFSET			8
#घोषणा SPC_ADDITIONAL_DESC_LEN_OFFSET		9
#घोषणा SPC_VALIDITY_OFFSET			10
#घोषणा SPC_ASC_KEY_OFFSET			12
#घोषणा SPC_ASCQ_KEY_OFFSET			13
#घोषणा TRANSPORT_IQN_LEN			224
/* Used by target_core_store_alua_lu_gp() and target_core_alua_lu_gp_show_attr_members() */
#घोषणा LU_GROUP_NAME_BUF			256
/* Used by core_alua_store_tg_pt_gp_info() and target_core_alua_tg_pt_gp_show_attr_members() */
#घोषणा TG_PT_GROUP_NAME_BUF			256
/* Used to parse VPD पूर्णांकo काष्ठा t10_vpd */
#घोषणा VPD_TMP_BUF_SIZE			254
/* Used by transport_generic_cmd_sequencer() */
#घोषणा READ_BLOCK_LEN          		6
#घोषणा READ_CAP_LEN            		8
#घोषणा READ_POSITION_LEN       		20
#घोषणा INQUIRY_LEN				36
/* Used by transport_get_inquiry_vpd_serial() */
#घोषणा INQUIRY_VPD_SERIAL_LEN			254
/* Used by transport_get_inquiry_vpd_device_ident() */
#घोषणा INQUIRY_VPD_DEVICE_IDENTIFIER_LEN	254

#घोषणा INQUIRY_VENDOR_LEN			8
#घोषणा INQUIRY_MODEL_LEN			16
#घोषणा INQUIRY_REVISION_LEN			4

/* Attempts beक्रमe moving from SHORT to LONG */
#घोषणा PYX_TRANSPORT_WINDOW_CLOSED_THRESHOLD	3
#घोषणा PYX_TRANSPORT_WINDOW_CLOSED_WAIT_SHORT	3  /* In milliseconds */
#घोषणा PYX_TRANSPORT_WINDOW_CLOSED_WAIT_LONG	10 /* In milliseconds */

#घोषणा PYX_TRANSPORT_STATUS_INTERVAL		5 /* In seconds */

/* काष्ठा se_dev_attrib sanity values */
/* Default max_unmap_lba_count */
#घोषणा DA_MAX_UNMAP_LBA_COUNT			0
/* Default max_unmap_block_desc_count */
#घोषणा DA_MAX_UNMAP_BLOCK_DESC_COUNT		0
/* Default unmap_granularity */
#घोषणा DA_UNMAP_GRANULARITY_DEFAULT		0
/* Default unmap_granularity_alignment */
#घोषणा DA_UNMAP_GRANULARITY_ALIGNMENT_DEFAULT	0
/* Default unmap_zeroes_data */
#घोषणा DA_UNMAP_ZEROES_DATA_DEFAULT		0
/* Default max_ग_लिखो_same_len, disabled by शेष */
#घोषणा DA_MAX_WRITE_SAME_LEN			0
/* Use a model alias based on the configfs backend device name */
#घोषणा DA_EMULATE_MODEL_ALIAS			0
/* Emulation क्रम WriteCache and SYNCHRONIZE_CACHE */
#घोषणा DA_EMULATE_WRITE_CACHE			0
/* Emulation क्रम TASK_ABORTED status (TAS) by शेष */
#घोषणा DA_EMULATE_TAS				1
/* Emulation क्रम Thin Provisioning UNMAP using block/blk-lib.c:blkdev_issue_discard() */
#घोषणा DA_EMULATE_TPU				0
/*
 * Emulation क्रम Thin Provisioning WRITE_SAME w/ UNMAP=1 bit using
 * block/blk-lib.c:blkdev_issue_discard()
 */
#घोषणा DA_EMULATE_TPWS				0
/* Emulation क्रम CompareAndWrite (AtomicTestandSet) by शेष */
#घोषणा DA_EMULATE_CAW				1
/* Emulation क्रम 3rd Party Copy (ExtendedCopy) by शेष */
#घोषणा DA_EMULATE_3PC				1
/* No Emulation क्रम PSCSI by शेष */
#घोषणा DA_EMULATE_ALUA				0
/* Emulate SCSI2 RESERVE/RELEASE and Persistent Reservations by शेष */
#घोषणा DA_EMULATE_PR				1
/* Enक्रमce SCSI Initiator Port TransportID with 'ISID' क्रम PR */
#घोषणा DA_ENFORCE_PR_ISIDS			1
/* Force SPC-3 PR Activate Persistence across Target Power Loss */
#घोषणा DA_FORCE_PR_APTPL			0
#घोषणा DA_STATUS_MAX_SECTORS_MIN		16
#घोषणा DA_STATUS_MAX_SECTORS_MAX		8192
/* By शेष करोn't report non-rotating (solid state) medium */
#घोषणा DA_IS_NONROT				0
/* Queue Algorithm Modअगरier शेष क्रम restricted reordering in control mode page */
#घोषणा DA_EMULATE_REST_REORD			0

#घोषणा SE_INQUIRY_BUF				1024
#घोषणा SE_MODE_PAGE_BUF			512
#घोषणा SE_SENSE_BUF				96

/* काष्ठा se_hba->hba_flags */
क्रमागत hba_flags_table अणु
	HBA_FLAGS_INTERNAL_USE	= 0x01,
	HBA_FLAGS_PSCSI_MODE	= 0x02,
पूर्ण;

/* Special transport agnostic काष्ठा se_cmd->t_states */
क्रमागत transport_state_table अणु
	TRANSPORT_NO_STATE	= 0,
	TRANSPORT_NEW_CMD	= 1,
	TRANSPORT_WRITE_PENDING	= 3,
	TRANSPORT_PROCESSING	= 5,
	TRANSPORT_COMPLETE	= 6,
	TRANSPORT_ISTATE_PROCESSING = 11,
	TRANSPORT_COMPLETE_QF_WP = 18,
	TRANSPORT_COMPLETE_QF_OK = 19,
	TRANSPORT_COMPLETE_QF_ERR = 20,
पूर्ण;

/* Used क्रम काष्ठा se_cmd->se_cmd_flags */
क्रमागत se_cmd_flags_table अणु
	SCF_SUPPORTED_SAM_OPCODE		= (1 << 0),
	SCF_TRANSPORT_TASK_SENSE		= (1 << 1),
	SCF_EMULATED_TASK_SENSE			= (1 << 2),
	SCF_SCSI_DATA_CDB			= (1 << 3),
	SCF_SCSI_TMR_CDB			= (1 << 4),
	SCF_FUA					= (1 << 5),
	SCF_SE_LUN_CMD				= (1 << 6),
	SCF_BIDI				= (1 << 7),
	SCF_SENT_CHECK_CONDITION		= (1 << 8),
	SCF_OVERFLOW_BIT			= (1 << 9),
	SCF_UNDERFLOW_BIT			= (1 << 10),
	SCF_ALUA_NON_OPTIMIZED			= (1 << 11),
	SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC	= (1 << 12),
	SCF_COMPARE_AND_WRITE			= (1 << 13),
	SCF_PASSTHROUGH_PROT_SG_TO_MEM_NOALLOC	= (1 << 14),
	SCF_ACK_KREF				= (1 << 15),
	SCF_USE_CPUID				= (1 << 16),
	SCF_TASK_ATTR_SET			= (1 << 17),
	SCF_TREAT_READ_AS_NORMAL		= (1 << 18),
पूर्ण;

/*
 * Used by transport_send_check_condition_and_sense()
 * to संकेत which ASC/ASCQ sense payload should be built.
 */
प्रकार अचिन्हित __bitwise sense_reason_t;

क्रमागत tcm_sense_reason_table अणु
#घोषणा R(x)	(__क्रमce sense_reason_t )(x)
	TCM_NO_SENSE				= R(0x00),
	TCM_NON_EXISTENT_LUN			= R(0x01),
	TCM_UNSUPPORTED_SCSI_OPCODE		= R(0x02),
	TCM_INCORRECT_AMOUNT_OF_DATA		= R(0x03),
	TCM_UNEXPECTED_UNSOLICITED_DATA		= R(0x04),
	TCM_SERVICE_CRC_ERROR			= R(0x05),
	TCM_SNACK_REJECTED			= R(0x06),
	TCM_SECTOR_COUNT_TOO_MANY		= R(0x07),
	TCM_INVALID_CDB_FIELD			= R(0x08),
	TCM_INVALID_PARAMETER_LIST		= R(0x09),
	TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE	= R(0x0a),
	TCM_UNKNOWN_MODE_PAGE			= R(0x0b),
	TCM_WRITE_PROTECTED			= R(0x0c),
	TCM_CHECK_CONDITION_ABORT_CMD		= R(0x0d),
	TCM_CHECK_CONDITION_UNIT_ATTENTION	= R(0x0e),
	TCM_CHECK_CONDITION_NOT_READY		= R(0x0f),
	TCM_RESERVATION_CONFLICT		= R(0x10),
	TCM_ADDRESS_OUT_OF_RANGE		= R(0x11),
	TCM_OUT_OF_RESOURCES			= R(0x12),
	TCM_PARAMETER_LIST_LENGTH_ERROR		= R(0x13),
	TCM_MISCOMPARE_VERIFY			= R(0x14),
	TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED	= R(0x15),
	TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED	= R(0x16),
	TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED	= R(0x17),
	TCM_COPY_TARGET_DEVICE_NOT_REACHABLE	= R(0x18),
	TCM_TOO_MANY_TARGET_DESCS		= R(0x19),
	TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE	= R(0x1a),
	TCM_TOO_MANY_SEGMENT_DESCS		= R(0x1b),
	TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE	= R(0x1c),
	TCM_INSUFFICIENT_REGISTRATION_RESOURCES	= R(0x1d),
	TCM_LUN_BUSY				= R(0x1e),
	TCM_INVALID_FIELD_IN_COMMAND_IU         = R(0x1f),
#अघोषित R
पूर्ण;

क्रमागत target_sc_flags_table अणु
	TARGET_SCF_BIDI_OP		= 0x01,
	TARGET_SCF_ACK_KREF		= 0x02,
	TARGET_SCF_UNKNOWN_SIZE		= 0x04,
	TARGET_SCF_USE_CPUID		= 0x08,
पूर्ण;

/* fabric independent task management function values */
क्रमागत tcm_पंचांगreq_table अणु
	TMR_ABORT_TASK		= 1,
	TMR_ABORT_TASK_SET	= 2,
	TMR_CLEAR_ACA		= 3,
	TMR_CLEAR_TASK_SET	= 4,
	TMR_LUN_RESET		= 5,
	TMR_TARGET_WARM_RESET	= 6,
	TMR_TARGET_COLD_RESET	= 7,
	TMR_LUN_RESET_PRO	= 0x80,
	TMR_UNKNOWN		= 0xff,
पूर्ण;

/* fabric independent task management response values */
क्रमागत tcm_पंचांगrsp_table अणु
	TMR_FUNCTION_FAILED		= 0,
	TMR_FUNCTION_COMPLETE		= 1,
	TMR_TASK_DOES_NOT_EXIST		= 2,
	TMR_LUN_DOES_NOT_EXIST		= 3,
	TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED	= 4,
	TMR_FUNCTION_REJECTED		= 5,
पूर्ण;

/*
 * Used क्रम target SCSI statistics
 */
प्रकार क्रमागत अणु
	SCSI_INST_INDEX,
	SCSI_AUTH_INTR_INDEX,
	SCSI_INDEX_TYPE_MAX
पूर्ण scsi_index_t;

काष्ठा se_cmd;

काष्ठा t10_alua_lba_map_member अणु
	काष्ठा list_head lba_map_mem_list;
	पूर्णांक lba_map_mem_alua_state;
	पूर्णांक lba_map_mem_alua_pg_id;
पूर्ण;

काष्ठा t10_alua_lba_map अणु
	u64 lba_map_first_lba;
	u64 lba_map_last_lba;
	काष्ठा list_head lba_map_list;
	काष्ठा list_head lba_map_mem_list;
पूर्ण;

काष्ठा t10_alua अणु
	/* ALUA Target Port Group ID */
	u16	alua_tg_pt_gps_counter;
	u32	alua_tg_pt_gps_count;
	/* Referrals support */
	spinlock_t lba_map_lock;
	u32     lba_map_segment_size;
	u32     lba_map_segment_multiplier;
	काष्ठा list_head lba_map_list;
	spinlock_t tg_pt_gps_lock;
	काष्ठा se_device *t10_dev;
	/* Used क्रम शेष ALUA Target Port Group */
	काष्ठा t10_alua_tg_pt_gp *शेष_tg_pt_gp;
	/* Used क्रम शेष ALUA Target Port Group ConfigFS group */
	काष्ठा config_group alua_tg_pt_gps_group;
	काष्ठा list_head tg_pt_gps_list;
पूर्ण;

काष्ठा t10_alua_lu_gp अणु
	u16	lu_gp_id;
	पूर्णांक	lu_gp_valid_id;
	u32	lu_gp_members;
	atomic_t lu_gp_ref_cnt;
	spinlock_t lu_gp_lock;
	काष्ठा config_group lu_gp_group;
	काष्ठा list_head lu_gp_node;
	काष्ठा list_head lu_gp_mem_list;
पूर्ण;

काष्ठा t10_alua_lu_gp_member अणु
	bool lu_gp_assoc;
	atomic_t lu_gp_mem_ref_cnt;
	spinlock_t lu_gp_mem_lock;
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा se_device *lu_gp_mem_dev;
	काष्ठा list_head lu_gp_mem_list;
पूर्ण;

काष्ठा t10_alua_tg_pt_gp अणु
	u16	tg_pt_gp_id;
	पूर्णांक	tg_pt_gp_valid_id;
	पूर्णांक	tg_pt_gp_alua_supported_states;
	पूर्णांक	tg_pt_gp_alua_access_status;
	पूर्णांक	tg_pt_gp_alua_access_type;
	पूर्णांक	tg_pt_gp_nonop_delay_msecs;
	पूर्णांक	tg_pt_gp_trans_delay_msecs;
	पूर्णांक	tg_pt_gp_implicit_trans_secs;
	पूर्णांक	tg_pt_gp_pref;
	पूर्णांक	tg_pt_gp_ग_लिखो_metadata;
	u32	tg_pt_gp_members;
	पूर्णांक	tg_pt_gp_alua_access_state;
	atomic_t tg_pt_gp_ref_cnt;
	spinlock_t tg_pt_gp_lock;
	काष्ठा mutex tg_pt_gp_transition_mutex;
	काष्ठा se_device *tg_pt_gp_dev;
	काष्ठा config_group tg_pt_gp_group;
	काष्ठा list_head tg_pt_gp_list;
	काष्ठा list_head tg_pt_gp_lun_list;
	काष्ठा se_lun *tg_pt_gp_alua_lun;
	काष्ठा se_node_acl *tg_pt_gp_alua_nacl;
पूर्ण;

काष्ठा t10_vpd अणु
	अचिन्हित अक्षर device_identअगरier[INQUIRY_VPD_DEVICE_IDENTIFIER_LEN];
	पूर्णांक protocol_identअगरier_set;
	u32 protocol_identअगरier;
	u32 device_identअगरier_code_set;
	u32 association;
	u32 device_identअगरier_type;
	काष्ठा list_head vpd_list;
पूर्ण;

काष्ठा t10_wwn अणु
	/*
	 * SCSI left aligned strings may not be null terminated. +1 to ensure a
	 * null terminator is always present.
	 */
	अक्षर venकरोr[INQUIRY_VENDOR_LEN + 1];
	अक्षर model[INQUIRY_MODEL_LEN + 1];
	अक्षर revision[INQUIRY_REVISION_LEN + 1];
	अक्षर unit_serial[INQUIRY_VPD_SERIAL_LEN];
	spinlock_t t10_vpd_lock;
	काष्ठा se_device *t10_dev;
	काष्ठा config_group t10_wwn_group;
	काष्ठा list_head t10_vpd_list;
पूर्ण;

काष्ठा t10_pr_registration अणु
	/* Used क्रम fabrics that contain WWN+ISID */
#घोषणा PR_REG_ISID_LEN				16
	/* PR_REG_ISID_LEN + ',i,0x' */
#घोषणा PR_REG_ISID_ID_LEN			(PR_REG_ISID_LEN + 5)
	अक्षर pr_reg_isid[PR_REG_ISID_LEN];
	/* Used during APTPL metadata पढ़ोing */
#घोषणा PR_APTPL_MAX_IPORT_LEN			256
	अचिन्हित अक्षर pr_iport[PR_APTPL_MAX_IPORT_LEN];
	/* Used during APTPL metadata पढ़ोing */
#घोषणा PR_APTPL_MAX_TPORT_LEN			256
	अचिन्हित अक्षर pr_tport[PR_APTPL_MAX_TPORT_LEN];
	u16 pr_aptpl_rpti;
	u16 pr_reg_tpgt;
	/* Reservation effects all target ports */
	पूर्णांक pr_reg_all_tg_pt;
	/* Activate Persistence across Target Power Loss */
	पूर्णांक pr_reg_aptpl;
	पूर्णांक pr_res_holder;
	पूर्णांक pr_res_type;
	पूर्णांक pr_res_scope;
	/* Used क्रम fabric initiator WWPNs using a ISID */
	bool isid_present_at_reg;
	u64 pr_res_mapped_lun;
	u64 pr_aptpl_target_lun;
	u16 tg_pt_sep_rtpi;
	u32 pr_res_generation;
	u64 pr_reg_bin_isid;
	u64 pr_res_key;
	atomic_t pr_res_holders;
	काष्ठा se_node_acl *pr_reg_nacl;
	/* Used by ALL_TG_PT=1 registration with deve->pr_ref taken */
	काष्ठा se_dev_entry *pr_reg_deve;
	काष्ठा list_head pr_reg_list;
	काष्ठा list_head pr_reg_पात_list;
	काष्ठा list_head pr_reg_aptpl_list;
	काष्ठा list_head pr_reg_atp_list;
	काष्ठा list_head pr_reg_atp_mem_list;
पूर्ण;

काष्ठा t10_reservation अणु
	/* Reservation effects all target ports */
	पूर्णांक pr_all_tg_pt;
	/* Activate Persistence across Target Power Loss enabled
	 * क्रम SCSI device */
	पूर्णांक pr_aptpl_active;
#घोषणा PR_APTPL_BUF_LEN			262144
	u32 pr_generation;
	spinlock_t registration_lock;
	spinlock_t aptpl_reg_lock;
	/*
	 * This will always be set by one inभागidual I_T Nexus.
	 * However with all_tg_pt=1, other I_T Nexus from the
	 * same initiator can access PR reg/res info on a dअगरferent
	 * target port.
	 *
	 * There is also the 'All Registrants' हाल, where there is
	 * a single *pr_res_holder of the reservation, but all
	 * registrations are considered reservation holders.
	 */
	काष्ठा se_node_acl *pr_res_holder;
	काष्ठा list_head registration_list;
	काष्ठा list_head aptpl_reg_list;
पूर्ण;

काष्ठा se_पंचांगr_req अणु
	/* Task Management function to be perक्रमmed */
	u8			function;
	/* Task Management response to send */
	u8			response;
	पूर्णांक			call_transport;
	/* Reference to ITT that Task Mgmt should be perक्रमmed */
	u64			ref_task_tag;
	व्योम 			*fabric_पंचांगr_ptr;
	काष्ठा se_cmd		*task_cmd;
	काष्ठा se_device	*पंचांगr_dev;
	काष्ठा list_head	पंचांगr_list;
पूर्ण;

क्रमागत target_prot_op अणु
	TARGET_PROT_NORMAL	= 0,
	TARGET_PROT_DIN_INSERT	= (1 << 0),
	TARGET_PROT_DOUT_INSERT	= (1 << 1),
	TARGET_PROT_DIN_STRIP	= (1 << 2),
	TARGET_PROT_DOUT_STRIP	= (1 << 3),
	TARGET_PROT_DIN_PASS	= (1 << 4),
	TARGET_PROT_DOUT_PASS	= (1 << 5),
पूर्ण;

#घोषणा TARGET_PROT_ALL	TARGET_PROT_DIN_INSERT | TARGET_PROT_DOUT_INSERT | \
			TARGET_PROT_DIN_STRIP | TARGET_PROT_DOUT_STRIP | \
			TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS

क्रमागत target_prot_type अणु
	TARGET_DIF_TYPE0_PROT,
	TARGET_DIF_TYPE1_PROT,
	TARGET_DIF_TYPE2_PROT,
	TARGET_DIF_TYPE3_PROT,
पूर्ण;

/* Emulation क्रम UNIT ATTENTION Interlock Control */
क्रमागत target_ua_पूर्णांकlck_ctrl अणु
	TARGET_UA_INTLCK_CTRL_CLEAR = 0,
	TARGET_UA_INTLCK_CTRL_NO_CLEAR = 1,
	TARGET_UA_INTLCK_CTRL_ESTABLISH_UA = 2,
पूर्ण;

क्रमागत target_core_dअगर_check अणु
	TARGET_DIF_CHECK_GUARD  = 0x1 << 0,
	TARGET_DIF_CHECK_APPTAG = 0x1 << 1,
	TARGET_DIF_CHECK_REFTAG = 0x1 << 2,
पूर्ण;

/* क्रम sam_task_attr */
#घोषणा TCM_SIMPLE_TAG	0x20
#घोषणा TCM_HEAD_TAG	0x21
#घोषणा TCM_ORDERED_TAG	0x22
#घोषणा TCM_ACA_TAG	0x24

काष्ठा se_cmd अणु
	/* SAM response code being sent to initiator */
	u8			scsi_status;
	u8			scsi_asc;
	u8			scsi_ascq;
	u16			scsi_sense_length;
	अचिन्हित		unknown_data_length:1;
	bool			state_active:1;
	u64			tag; /* SAM command identअगरier aka task tag */
	/* Delay क्रम ALUA Active/NonOptimized state access in milliseconds */
	पूर्णांक			alua_nonop_delay;
	/* See include/linux/dma-mapping.h */
	क्रमागत dma_data_direction	data_direction;
	/* For SAM Task Attribute */
	पूर्णांक			sam_task_attr;
	/* Used क्रम se_sess->sess_tag_pool */
	अचिन्हित पूर्णांक		map_tag;
	पूर्णांक			map_cpu;
	/* Transport protocol dependent state, see transport_state_table */
	क्रमागत transport_state_table t_state;
	/* See se_cmd_flags_table */
	u32			se_cmd_flags;
	/* Total size in bytes associated with command */
	u32			data_length;
	u32			residual_count;
	u64			orig_fe_lun;
	/* Persistent Reservation key */
	u64			pr_res_key;
	/* Used क्रम sense data */
	व्योम			*sense_buffer;
	काष्ठा list_head	se_delayed_node;
	काष्ठा list_head	se_qf_node;
	काष्ठा se_device      *se_dev;
	काष्ठा se_lun		*se_lun;
	/* Only used क्रम पूर्णांकernal passthrough and legacy TCM fabric modules */
	काष्ठा se_session	*se_sess;
	काष्ठा se_पंचांगr_req	*se_पंचांगr_req;
	काष्ठा llist_node	se_cmd_list;
	काष्ठा completion	*मुक्त_compl;
	काष्ठा completion	*abrt_compl;
	स्थिर काष्ठा target_core_fabric_ops *se_tfo;
	sense_reason_t		(*execute_cmd)(काष्ठा se_cmd *);
	sense_reason_t (*transport_complete_callback)(काष्ठा se_cmd *, bool, पूर्णांक *);
	व्योम			*protocol_data;

	अचिन्हित अक्षर		*t_task_cdb;
	अचिन्हित अक्षर		__t_task_cdb[TCM_MAX_COMMAND_SIZE];
	अचिन्हित दीर्घ दीर्घ	t_task_lba;
	अचिन्हित पूर्णांक		t_task_nolb;
	अचिन्हित पूर्णांक		transport_state;
#घोषणा CMD_T_ABORTED		(1 << 0)
#घोषणा CMD_T_ACTIVE		(1 << 1)
#घोषणा CMD_T_COMPLETE		(1 << 2)
#घोषणा CMD_T_SENT		(1 << 4)
#घोषणा CMD_T_STOP		(1 << 5)
#घोषणा CMD_T_TAS		(1 << 10)
#घोषणा CMD_T_FABRIC_STOP	(1 << 11)
	spinlock_t		t_state_lock;
	काष्ठा kref		cmd_kref;
	काष्ठा completion	t_transport_stop_comp;

	काष्ठा work_काष्ठा	work;

	काष्ठा scatterlist	*t_data_sg;
	काष्ठा scatterlist	*t_data_sg_orig;
	अचिन्हित पूर्णांक		t_data_nents;
	अचिन्हित पूर्णांक		t_data_nents_orig;
	व्योम			*t_data_vmap;
	काष्ठा scatterlist	*t_bidi_data_sg;
	अचिन्हित पूर्णांक		t_bidi_data_nents;

	/* Used क्रम lun->lun_ref counting */
	पूर्णांक			lun_ref_active;

	काष्ठा list_head	state_list;

	/* backend निजी data */
	व्योम			*priv;

	/* DIF related members */
	क्रमागत target_prot_op	prot_op;
	क्रमागत target_prot_type	prot_type;
	u8			prot_checks;
	bool			prot_pto;
	u32			prot_length;
	u32			reftag_seed;
	काष्ठा scatterlist	*t_prot_sg;
	अचिन्हित पूर्णांक		t_prot_nents;
	sense_reason_t		pi_err;
	u64			sense_info;
	/*
	 * CPU LIO will execute the cmd on. Defaults to the CPU the cmd is
	 * initialized on. Drivers can override.
	 */
	पूर्णांक			cpuid;
पूर्ण;

काष्ठा se_ua अणु
	u8			ua_asc;
	u8			ua_ascq;
	काष्ठा list_head	ua_nacl_list;
पूर्ण;

काष्ठा se_node_acl अणु
	अक्षर			initiatorname[TRANSPORT_IQN_LEN];
	/* Used to संकेत demo mode created ACL, disabled by शेष */
	bool			dynamic_node_acl;
	bool			dynamic_stop;
	u32			queue_depth;
	u32			acl_index;
	क्रमागत target_prot_type	saved_prot_type;
#घोषणा MAX_ACL_TAG_SIZE 64
	अक्षर			acl_tag[MAX_ACL_TAG_SIZE];
	/* Used क्रम PR SPEC_I_PT=1 and REGISTER_AND_MOVE */
	atomic_t		acl_pr_ref_count;
	काष्ठा hlist_head	lun_entry_hlist;
	काष्ठा se_session	*nacl_sess;
	काष्ठा se_portal_group *se_tpg;
	काष्ठा mutex		lun_entry_mutex;
	spinlock_t		nacl_sess_lock;
	काष्ठा config_group	acl_group;
	काष्ठा config_group	acl_attrib_group;
	काष्ठा config_group	acl_auth_group;
	काष्ठा config_group	acl_param_group;
	काष्ठा config_group	acl_fabric_stat_group;
	काष्ठा list_head	acl_list;
	काष्ठा list_head	acl_sess_list;
	काष्ठा completion	acl_मुक्त_comp;
	काष्ठा kref		acl_kref;
पूर्ण;

अटल अंतरभूत काष्ठा se_node_acl *acl_to_nacl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_node_acl,
			acl_group);
पूर्ण

अटल अंतरभूत काष्ठा se_node_acl *attrib_to_nacl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_node_acl,
			acl_attrib_group);
पूर्ण

अटल अंतरभूत काष्ठा se_node_acl *auth_to_nacl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_node_acl,
			acl_auth_group);
पूर्ण

अटल अंतरभूत काष्ठा se_node_acl *param_to_nacl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_node_acl,
			acl_param_group);
पूर्ण

अटल अंतरभूत काष्ठा se_node_acl *fabric_stat_to_nacl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_node_acl,
			acl_fabric_stat_group);
पूर्ण

काष्ठा se_session अणु
	atomic_t		stopped;
	u64			sess_bin_isid;
	क्रमागत target_prot_op	sup_prot_ops;
	क्रमागत target_prot_type	sess_prot_type;
	काष्ठा se_node_acl	*se_node_acl;
	काष्ठा se_portal_group *se_tpg;
	व्योम			*fabric_sess_ptr;
	काष्ठा percpu_ref	cmd_count;
	काष्ठा list_head	sess_list;
	काष्ठा list_head	sess_acl_list;
	spinlock_t		sess_cmd_lock;
	रुको_queue_head_t	cmd_count_wq;
	काष्ठा completion	stop_करोne;
	व्योम			*sess_cmd_map;
	काष्ठा sbiपंचांगap_queue	sess_tag_pool;
पूर्ण;

काष्ठा se_device;
काष्ठा se_transक्रमm_info;
काष्ठा scatterlist;

काष्ठा se_ml_stat_grps अणु
	काष्ठा config_group	stat_group;
	काष्ठा config_group	scsi_auth_पूर्णांकr_group;
	काष्ठा config_group	scsi_att_पूर्णांकr_port_group;
पूर्ण;

काष्ठा se_lun_acl अणु
	u64			mapped_lun;
	काष्ठा se_node_acl	*se_lun_nacl;
	काष्ठा se_lun		*se_lun;
	काष्ठा config_group	se_lun_group;
	काष्ठा se_ml_stat_grps	ml_stat_grps;
पूर्ण;

काष्ठा se_dev_entry अणु
	u64			mapped_lun;
	u64			pr_res_key;
	u64			creation_समय;
	bool			lun_access_ro;
	u32			attach_count;
	atomic_दीर्घ_t		total_cmds;
	atomic_दीर्घ_t		पढ़ो_bytes;
	atomic_दीर्घ_t		ग_लिखो_bytes;
	/* Used क्रम PR SPEC_I_PT=1 and REGISTER_AND_MOVE */
	काष्ठा kref		pr_kref;
	काष्ठा completion	pr_comp;
	काष्ठा se_lun_acl __rcu	*se_lun_acl;
	spinlock_t		ua_lock;
	काष्ठा se_lun __rcu	*se_lun;
#घोषणा DEF_PR_REG_ACTIVE		1
	अचिन्हित दीर्घ		deve_flags;
	काष्ठा list_head	alua_port_list;
	काष्ठा list_head	lun_link;
	काष्ठा list_head	ua_list;
	काष्ठा hlist_node	link;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

काष्ठा se_dev_attrib अणु
	bool		emulate_model_alias;
	bool		emulate_dpo;		/* deprecated */
	bool		emulate_fua_ग_लिखो;
	bool		emulate_fua_पढ़ो;	/* deprecated */
	bool		emulate_ग_लिखो_cache;
	क्रमागत target_ua_पूर्णांकlck_ctrl emulate_ua_पूर्णांकlck_ctrl;
	bool		emulate_tas;
	bool		emulate_tpu;
	bool		emulate_tpws;
	bool		emulate_caw;
	bool		emulate_3pc;
	bool		emulate_pr;
	क्रमागत target_prot_type pi_prot_type;
	क्रमागत target_prot_type hw_pi_prot_type;
	bool		pi_prot_verअगरy;
	bool		enक्रमce_pr_isids;
	bool		क्रमce_pr_aptpl;
	bool		is_nonrot;
	bool		emulate_rest_reord;
	bool		unmap_zeroes_data;
	u32		hw_block_size;
	u32		block_size;
	u32		hw_max_sectors;
	u32		optimal_sectors;
	u32		hw_queue_depth;
	u32		queue_depth;
	u32		max_unmap_lba_count;
	u32		max_unmap_block_desc_count;
	u32		unmap_granularity;
	u32		unmap_granularity_alignment;
	u32		max_ग_लिखो_same_len;
	u32		max_bytes_per_io;
	काष्ठा se_device *da_dev;
	काष्ठा config_group da_group;
पूर्ण;

काष्ठा se_port_stat_grps अणु
	काष्ठा config_group stat_group;
	काष्ठा config_group scsi_port_group;
	काष्ठा config_group scsi_tgt_port_group;
	काष्ठा config_group scsi_transport_group;
पूर्ण;

काष्ठा scsi_port_stats अणु
	atomic_दीर्घ_t	cmd_pdus;
	atomic_दीर्घ_t	tx_data_octets;
	atomic_दीर्घ_t	rx_data_octets;
पूर्ण;

काष्ठा se_lun अणु
	u64			unpacked_lun;
	bool			lun_shutकरोwn;
	bool			lun_access_ro;
	u32			lun_index;

	/* RELATIVE TARGET PORT IDENTIFER */
	u16			lun_rtpi;
	atomic_t		lun_acl_count;
	काष्ठा se_device __rcu	*lun_se_dev;

	काष्ठा list_head	lun_deve_list;
	spinlock_t		lun_deve_lock;

	/* ALUA state */
	पूर्णांक			lun_tg_pt_secondary_stat;
	पूर्णांक			lun_tg_pt_secondary_ग_लिखो_md;
	atomic_t		lun_tg_pt_secondary_offline;
	काष्ठा mutex		lun_tg_pt_md_mutex;

	/* ALUA target port group linkage */
	काष्ठा list_head	lun_tg_pt_gp_link;
	काष्ठा t10_alua_tg_pt_gp *lun_tg_pt_gp;
	spinlock_t		lun_tg_pt_gp_lock;

	काष्ठा se_portal_group	*lun_tpg;
	काष्ठा scsi_port_stats	lun_stats;
	काष्ठा config_group	lun_group;
	काष्ठा se_port_stat_grps port_stat_grps;
	काष्ठा completion	lun_shutकरोwn_comp;
	काष्ठा percpu_ref	lun_ref;
	काष्ठा list_head	lun_dev_link;
	काष्ठा hlist_node	link;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

काष्ठा se_dev_stat_grps अणु
	काष्ठा config_group stat_group;
	काष्ठा config_group scsi_dev_group;
	काष्ठा config_group scsi_tgt_dev_group;
	काष्ठा config_group scsi_lu_group;
पूर्ण;

काष्ठा se_cmd_queue अणु
	काष्ठा llist_head	cmd_list;
	काष्ठा work_काष्ठा	work;
पूर्ण;

काष्ठा se_dev_plug अणु
	काष्ठा se_device	*se_dev;
पूर्ण;

काष्ठा se_device_queue अणु
	काष्ठा list_head	state_list;
	spinlock_t		lock;
	काष्ठा se_cmd_queue	sq;
पूर्ण;

काष्ठा se_device अणु
	/* RELATIVE TARGET PORT IDENTIFER Counter */
	u16			dev_rpti_counter;
	/* Used क्रम SAM Task Attribute ordering */
	u32			dev_cur_ordered_id;
	u32			dev_flags;
#घोषणा DF_CONFIGURED				0x00000001
#घोषणा DF_FIRMWARE_VPD_UNIT_SERIAL		0x00000002
#घोषणा DF_EMULATED_VPD_UNIT_SERIAL		0x00000004
#घोषणा DF_USING_UDEV_PATH			0x00000008
#घोषणा DF_USING_ALIAS				0x00000010
#घोषणा DF_READ_ONLY				0x00000020
	u8			transport_flags;
	/* Physical device queue depth */
	u32			queue_depth;
	/* Used क्रम SPC-2 reservations enक्रमce of ISIDs */
	u64			dev_res_bin_isid;
	/* Poपूर्णांकer to transport specअगरic device काष्ठाure */
	u32			dev_index;
	u64			creation_समय;
	atomic_दीर्घ_t		num_resets;
	atomic_दीर्घ_t		पातs_complete;
	atomic_दीर्घ_t		पातs_no_task;
	atomic_दीर्घ_t		num_cmds;
	atomic_दीर्घ_t		पढ़ो_bytes;
	atomic_दीर्घ_t		ग_लिखो_bytes;
	/* Active commands on this भव SE device */
	atomic_t		simple_cmds;
	atomic_t		dev_ordered_sync;
	atomic_t		dev_qf_count;
	u32			export_count;
	spinlock_t		delayed_cmd_lock;
	spinlock_t		dev_reservation_lock;
	अचिन्हित पूर्णांक		dev_reservation_flags;
#घोषणा DRF_SPC2_RESERVATIONS			0x00000001
#घोषणा DRF_SPC2_RESERVATIONS_WITH_ISID		0x00000002
	spinlock_t		se_port_lock;
	spinlock_t		se_पंचांगr_lock;
	spinlock_t		qf_cmd_lock;
	काष्ठा semaphore	caw_sem;
	/* Used क्रम legacy SPC-2 reservations */
	काष्ठा se_session	*reservation_holder;
	/* Used क्रम ALUA Logical Unit Group membership */
	काष्ठा t10_alua_lu_gp_member *dev_alua_lu_gp_mem;
	/* Used क्रम SPC-3 Persistent Reservations */
	काष्ठा t10_pr_registration *dev_pr_res_holder;
	काष्ठा list_head	dev_sep_list;
	काष्ठा list_head	dev_पंचांगr_list;
	काष्ठा work_काष्ठा	qf_work_queue;
	काष्ठा list_head	delayed_cmd_list;
	काष्ठा list_head	qf_cmd_list;
	/* Poपूर्णांकer to associated SE HBA */
	काष्ठा se_hba		*se_hba;
	/* T10 Inquiry and VPD WWN Inक्रमmation */
	काष्ठा t10_wwn		t10_wwn;
	/* T10 Asymmetric Logical Unit Assignment क्रम Target Ports */
	काष्ठा t10_alua		t10_alua;
	/* T10 SPC-2 + SPC-3 Reservations */
	काष्ठा t10_reservation	t10_pr;
	काष्ठा se_dev_attrib	dev_attrib;
	काष्ठा config_group	dev_action_group;
	काष्ठा config_group	dev_group;
	काष्ठा config_group	dev_pr_group;
	काष्ठा se_dev_stat_grps dev_stat_grps;
#घोषणा SE_DEV_ALIAS_LEN 512		/* must be less than PAGE_SIZE */
	अचिन्हित अक्षर		dev_alias[SE_DEV_ALIAS_LEN];
#घोषणा SE_UDEV_PATH_LEN 512		/* must be less than PAGE_SIZE */
	अचिन्हित अक्षर		udev_path[SE_UDEV_PATH_LEN];
	/* Poपूर्णांकer to ढाँचा of function poपूर्णांकers क्रम transport */
	स्थिर काष्ठा target_backend_ops *transport;
	काष्ठा se_lun		xcopy_lun;
	/* Protection Inक्रमmation */
	पूर्णांक			prot_length;
	/* For se_lun->lun_se_dev RCU पढ़ो-side critical access */
	u32			hba_index;
	काष्ठा rcu_head		rcu_head;
	पूर्णांक			queue_cnt;
	काष्ठा se_device_queue	*queues;
पूर्ण;

काष्ठा se_hba अणु
	u16			hba_tpgt;
	u32			hba_id;
	/* See hba_flags_table */
	u32			hba_flags;
	/* Virtual iSCSI devices attached. */
	u32			dev_count;
	u32			hba_index;
	/* Poपूर्णांकer to transport specअगरic host काष्ठाure. */
	व्योम			*hba_ptr;
	काष्ठा list_head	hba_node;
	spinlock_t		device_lock;
	काष्ठा config_group	hba_group;
	काष्ठा mutex		hba_access_mutex;
	काष्ठा target_backend	*backend;
पूर्ण;

काष्ठा se_tpg_np अणु
	काष्ठा se_portal_group *tpg_np_parent;
	काष्ठा config_group	tpg_np_group;
पूर्ण;

अटल अंतरभूत काष्ठा se_tpg_np *to_tpg_np(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_tpg_np,
			tpg_np_group);
पूर्ण

काष्ठा se_portal_group अणु
	/*
	 * PROTOCOL IDENTIFIER value per SPC4, 7.5.1.
	 *
	 * Negative values can be used by fabric drivers क्रम पूर्णांकernal use TPGs.
	 */
	पूर्णांक			proto_id;
	/* Used क्रम PR SPEC_I_PT=1 and REGISTER_AND_MOVE */
	atomic_t		tpg_pr_ref_count;
	/* Spinlock क्रम adding/removing ACLed Nodes */
	काष्ठा mutex		acl_node_mutex;
	/* Spinlock क्रम adding/removing sessions */
	spinlock_t		session_lock;
	काष्ठा mutex		tpg_lun_mutex;
	/* linked list क्रम initiator ACL list */
	काष्ठा list_head	acl_node_list;
	काष्ठा hlist_head	tpg_lun_hlist;
	काष्ठा se_lun		*tpg_virt_lun0;
	/* List of TCM sessions associated wth this TPG */
	काष्ठा list_head	tpg_sess_list;
	/* Poपूर्णांकer to $FABRIC_MOD dependent code */
	स्थिर काष्ठा target_core_fabric_ops *se_tpg_tfo;
	काष्ठा se_wwn		*se_tpg_wwn;
	काष्ठा config_group	tpg_group;
	काष्ठा config_group	tpg_lun_group;
	काष्ठा config_group	tpg_np_group;
	काष्ठा config_group	tpg_acl_group;
	काष्ठा config_group	tpg_attrib_group;
	काष्ठा config_group	tpg_auth_group;
	काष्ठा config_group	tpg_param_group;
पूर्ण;

अटल अंतरभूत काष्ठा se_portal_group *to_tpg(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_portal_group,
			tpg_group);
पूर्ण

अटल अंतरभूत काष्ठा se_portal_group *attrib_to_tpg(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_portal_group,
			tpg_attrib_group);
पूर्ण

अटल अंतरभूत काष्ठा se_portal_group *auth_to_tpg(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_portal_group,
			tpg_auth_group);
पूर्ण

अटल अंतरभूत काष्ठा se_portal_group *param_to_tpg(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_portal_group,
			tpg_param_group);
पूर्ण

क्रमागत अणु
	/* Use se_cmd's cpuid क्रम completion */
	SE_COMPL_AFFINITY_CPUID		= -1,
	/* Complete on current CPU */
	SE_COMPL_AFFINITY_CURR_CPU	= -2,
पूर्ण;

काष्ठा se_wwn अणु
	काष्ठा target_fabric_configfs *wwn_tf;
	व्योम			*priv;
	काष्ठा config_group	wwn_group;
	काष्ठा config_group	fabric_stat_group;
	काष्ठा config_group	param_group;
	पूर्णांक			cmd_compl_affinity;
पूर्ण;

अटल अंतरभूत व्योम atomic_inc_mb(atomic_t *v)
अणु
	smp_mb__beक्रमe_atomic();
	atomic_inc(v);
	smp_mb__after_atomic();
पूर्ण

अटल अंतरभूत व्योम atomic_dec_mb(atomic_t *v)
अणु
	smp_mb__beक्रमe_atomic();
	atomic_dec(v);
	smp_mb__after_atomic();
पूर्ण

अटल अंतरभूत व्योम target_मुक्त_tag(काष्ठा se_session *sess, काष्ठा se_cmd *cmd)
अणु
	sbiपंचांगap_queue_clear(&sess->sess_tag_pool, cmd->map_tag, cmd->map_cpu);
पूर्ण

#पूर्ण_अगर /* TARGET_CORE_BASE_H */

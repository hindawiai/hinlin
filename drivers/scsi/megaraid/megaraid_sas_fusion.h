<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Linux MegaRAID driver क्रम SAS based RAID controllers
 *
 *  Copyright (c) 2009-2013  LSI Corporation
 *  Copyright (c) 2013-2016  Avago Technologies
 *  Copyright (c) 2016-2018  Broadcom Inc.
 *
 *  खाता: megaraid_sas_fusion.h
 *
 *  Authors: Broadcom Inc.
 *           Manoj Jose
 *           Sumant Patro
 *           Kashyap Desai <kashyap.desai@broadcom.com>
 *           Sumit Saxena <sumit.saxena@broadcom.com>
 *
 *  Send feedback to: megaraidlinux.pdl@broadcom.com
 */

#अगर_अघोषित _MEGARAID_SAS_FUSION_H_
#घोषणा _MEGARAID_SAS_FUSION_H_

/* Fusion defines */
#घोषणा MEGASAS_CHAIN_FRAME_SZ_MIN 1024
#घोषणा MFI_FUSION_ENABLE_INTERRUPT_MASK (0x00000009)
#घोषणा MEGASAS_MAX_CHAIN_SHIFT			5
#घोषणा MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK	0x400000
#घोषणा MEGASAS_MAX_CHAIN_SIZE_MASK		0x3E0
#घोषणा MEGASAS_256K_IO				128
#घोषणा MEGASAS_1MB_IO				(MEGASAS_256K_IO * 4)
#घोषणा MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE 256
#घोषणा MEGASAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST   0xF0
#घोषणा MEGASAS_MPI2_FUNCTION_LD_IO_REQUEST         0xF1
#घोषणा MEGASAS_LOAD_BALANCE_FLAG		    0x1
#घोषणा MEGASAS_DCMD_MBOX_PEND_FLAG		    0x1
#घोषणा HOST_DIAG_WRITE_ENABLE			    0x80
#घोषणा HOST_DIAG_RESET_ADAPTER			    0x4
#घोषणा MEGASAS_FUSION_MAX_RESET_TRIES		    3
#घोषणा MAX_MSIX_QUEUES_FUSION			    128
#घोषणा RDPQ_MAX_INDEX_IN_ONE_CHUNK		    16
#घोषणा RDPQ_MAX_CHUNK_COUNT (MAX_MSIX_QUEUES_FUSION / RDPQ_MAX_INDEX_IN_ONE_CHUNK)

/* Invader defines */
#घोषणा MPI2_TYPE_CUDA				    0x2
#घोषणा MPI25_SAS_DEVICE0_FLAGS_ENABLED_FAST_PATH   0x4000
#घोषणा	MR_RL_FLAGS_GRANT_DESTINATION_CPU0	    0x00
#घोषणा	MR_RL_FLAGS_GRANT_DESTINATION_CPU1	    0x10
#घोषणा	MR_RL_FLAGS_GRANT_DESTINATION_CUDA	    0x80
#घोषणा MR_RL_FLAGS_SEQ_NUM_ENABLE		    0x8
#घोषणा MR_RL_WRITE_THROUGH_MODE		    0x00
#घोषणा MR_RL_WRITE_BACK_MODE			    0x01

/* T10 PI defines */
#घोषणा MR_PROT_INFO_TYPE_CONTROLLER                0x8
#घोषणा MEGASAS_SCSI_VARIABLE_LENGTH_CMD            0x7f
#घोषणा MEGASAS_SCSI_SERVICE_ACTION_READ32          0x9
#घोषणा MEGASAS_SCSI_SERVICE_ACTION_WRITE32         0xB
#घोषणा MEGASAS_SCSI_ADDL_CDB_LEN                   0x18
#घोषणा MEGASAS_RD_WR_PROTECT_CHECK_ALL		    0x20
#घोषणा MEGASAS_RD_WR_PROTECT_CHECK_NONE	    0x60

#घोषणा MPI2_SUP_REPLY_POST_HOST_INDEX_OFFSET   (0x0000030C)
#घोषणा MPI2_REPLY_POST_HOST_INDEX_OFFSET	(0x0000006C)

/*
 * Raid context flags
 */

#घोषणा MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT   0x4
#घोषणा MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_MASK    0x30
क्रमागत MR_RAID_FLAGS_IO_SUB_TYPE अणु
	MR_RAID_FLAGS_IO_SUB_TYPE_NONE = 0,
	MR_RAID_FLAGS_IO_SUB_TYPE_SYSTEM_PD = 1,
	MR_RAID_FLAGS_IO_SUB_TYPE_RMW_DATA     = 2,
	MR_RAID_FLAGS_IO_SUB_TYPE_RMW_P        = 3,
	MR_RAID_FLAGS_IO_SUB_TYPE_RMW_Q        = 4,
	MR_RAID_FLAGS_IO_SUB_TYPE_CACHE_BYPASS = 6,
	MR_RAID_FLAGS_IO_SUB_TYPE_LDIO_BW_LIMIT = 7,
	MR_RAID_FLAGS_IO_SUB_TYPE_R56_DIV_OFFLOAD = 8
पूर्ण;

/*
 * Request descriptor types
 */
#घोषणा MEGASAS_REQ_DESCRIPT_FLAGS_LD_IO           0x7
#घोषणा MEGASAS_REQ_DESCRIPT_FLAGS_MFA             0x1
#घोषणा MEGASAS_REQ_DESCRIPT_FLAGS_NO_LOCK	   0x2
#घोषणा MEGASAS_REQ_DESCRIPT_FLAGS_TYPE_SHIFT      1

#घोषणा MEGASAS_FP_CMD_LEN	16
#घोषणा MEGASAS_FUSION_IN_RESET 0
#घोषणा MEGASAS_FUSION_OCR_NOT_POSSIBLE 1
#घोषणा RAID_1_PEER_CMDS 2
#घोषणा JBOD_MAPS_COUNT	2
#घोषणा MEGASAS_REDUCE_QD_COUNT 64
#घोषणा IOC_INIT_FRAME_SIZE 4096

/*
 * Raid Context काष्ठाure which describes MegaRAID specअगरic IO Parameters
 * This resides at offset 0x60 where the SGL normally starts in MPT IO Frames
 */

काष्ठा RAID_CONTEXT अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
	u8 nseg:4;
	u8 type:4;
#अन्यथा
	u8 type:4;
	u8 nseg:4;
#पूर्ण_अगर
	u8 resvd0;
	__le16 समयout_value;
	u8 reg_lock_flags;
	u8 resvd1;
	__le16 भव_disk_tgt_id;
	__le64 reg_lock_row_lba;
	__le32 reg_lock_length;
	__le16 next_lmid;
	u8 ex_status;
	u8 status;
	u8 raid_flags;
	u8 num_sge;
	__le16 config_seq_num;
	u8 span_arm;
	u8 priority;
	u8 num_sge_ext;
	u8 resvd2;
पूर्ण;

/*
 * Raid Context काष्ठाure which describes ventura MegaRAID specअगरic
 * IO Paramenters ,This resides at offset 0x60 where the SGL normally
 * starts in MPT IO Frames
 */
काष्ठा RAID_CONTEXT_G35 अणु
	#घोषणा RAID_CONTEXT_NSEG_MASK	0x00F0
	#घोषणा RAID_CONTEXT_NSEG_SHIFT	4
	#घोषणा RAID_CONTEXT_TYPE_MASK	0x000F
	#घोषणा RAID_CONTEXT_TYPE_SHIFT	0
	u16		nseg_type;
	u16 समयout_value; /* 0x02 -0x03 */
	u16		routing_flags;	// 0x04 -0x05 routing flags
	u16 भव_disk_tgt_id;   /* 0x06 -0x07 */
	__le64 reg_lock_row_lba;      /* 0x08 - 0x0F */
	u32 reg_lock_length;      /* 0x10 - 0x13 */
	जोड़ अणु                     // flow specअगरic
		u16 rmw_op_index;   /* 0x14 - 0x15, R5/6 RMW: rmw operation index*/
		u16 peer_smid;      /* 0x14 - 0x15, R1 Write: peer smid*/
		u16 r56_arm_map;    /* 0x14 - 0x15, Unused [15], LogArm[14:10], P-Arm[9:5], Q-Arm[4:0] */

	पूर्ण flow_specअगरic;

	u8 ex_status;       /* 0x16 : OUT */
	u8 status;          /* 0x17 status */
	u8 raid_flags;		/* 0x18 resvd[7:6], ioSubType[5:4],
				 * resvd[3:1], preferredCpu[0]
				 */
	u8 span_arm;            /* 0x1C span[7:5], arm[4:0] */
	u16	config_seq_num;           /* 0x1A -0x1B */
	जोड़ अणु
		/*
		 * Bit क्रमmat:
		 *	 ---------------------------------
		 *	 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
		 *	 ---------------------------------
		 * Byte0 |    numSGE[7]- numSGE[0]	 |
		 *	 ---------------------------------
		 * Byte1 |SD | resvd     | numSGE 8-11   |
		 *        --------------------------------
		 */
		#घोषणा NUM_SGE_MASK_LOWER	0xFF
		#घोषणा NUM_SGE_MASK_UPPER	0x0F
		#घोषणा NUM_SGE_SHIFT_UPPER	8
		#घोषणा STREAM_DETECT_SHIFT	7
		#घोषणा STREAM_DETECT_MASK	0x80
		काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD) /* 0x1C - 0x1D */
			u16 stream_detected:1;
			u16 reserved:3;
			u16 num_sge:12;
#अन्यथा
			u16 num_sge:12;
			u16 reserved:3;
			u16 stream_detected:1;
#पूर्ण_अगर
		पूर्ण bits;
		u8 bytes[2];
	पूर्ण u;
	u8 resvd2[2];          /* 0x1E-0x1F */
पूर्ण;

#घोषणा MR_RAID_CTX_ROUTINGFLAGS_SLD_SHIFT	1
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_C2D_SHIFT	2
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_FWD_SHIFT	3
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_SQN_SHIFT	4
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_SBS_SHIFT	5
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_RW_SHIFT	6
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_LOG_SHIFT	7
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_CPUSEL_SHIFT	8
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_CPUSEL_MASK	0x0F00
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_SETDIVERT_SHIFT	12
#घोषणा MR_RAID_CTX_ROUTINGFLAGS_SETDIVERT_MASK	0xF000

अटल अंतरभूत व्योम set_num_sge(काष्ठा RAID_CONTEXT_G35 *rctx_g35,
			       u16 sge_count)
अणु
	rctx_g35->u.bytes[0] = (u8)(sge_count & NUM_SGE_MASK_LOWER);
	rctx_g35->u.bytes[1] |= (u8)((sge_count >> NUM_SGE_SHIFT_UPPER)
							& NUM_SGE_MASK_UPPER);
पूर्ण

अटल अंतरभूत u16 get_num_sge(काष्ठा RAID_CONTEXT_G35 *rctx_g35)
अणु
	u16 sge_count;

	sge_count = (u16)(((rctx_g35->u.bytes[1] & NUM_SGE_MASK_UPPER)
			<< NUM_SGE_SHIFT_UPPER) | (rctx_g35->u.bytes[0]));
	वापस sge_count;
पूर्ण

#घोषणा SET_STREAM_DETECTED(rctx_g35) \
	(rctx_g35.u.bytes[1] |= STREAM_DETECT_MASK)

#घोषणा CLEAR_STREAM_DETECTED(rctx_g35) \
	(rctx_g35.u.bytes[1] &= ~(STREAM_DETECT_MASK))

अटल अंतरभूत bool is_stream_detected(काष्ठा RAID_CONTEXT_G35 *rctx_g35)
अणु
	वापस ((rctx_g35->u.bytes[1] & STREAM_DETECT_MASK));
पूर्ण

जोड़ RAID_CONTEXT_UNION अणु
	काष्ठा RAID_CONTEXT raid_context;
	काष्ठा RAID_CONTEXT_G35 raid_context_g35;
पूर्ण;

#घोषणा RAID_CTX_SPANARM_ARM_SHIFT	(0)
#घोषणा RAID_CTX_SPANARM_ARM_MASK	(0x1f)

#घोषणा RAID_CTX_SPANARM_SPAN_SHIFT	(5)
#घोषणा RAID_CTX_SPANARM_SPAN_MASK	(0xE0)

/* LogArm[14:10], P-Arm[9:5], Q-Arm[4:0] */
#घोषणा RAID_CTX_R56_Q_ARM_MASK		(0x1F)
#घोषणा RAID_CTX_R56_P_ARM_SHIFT	(5)
#घोषणा RAID_CTX_R56_P_ARM_MASK		(0x3E0)
#घोषणा RAID_CTX_R56_LOG_ARM_SHIFT	(10)
#घोषणा RAID_CTX_R56_LOG_ARM_MASK	(0x7C00)

/* number of bits per index in U32 TrackStream */
#घोषणा BITS_PER_INDEX_STREAM		4
#घोषणा INVALID_STREAM_NUM              16
#घोषणा MR_STREAM_BITMAP		0x76543210
#घोषणा STREAM_MASK			((1 << BITS_PER_INDEX_STREAM) - 1)
#घोषणा ZERO_LAST_STREAM		0x0fffffff
#घोषणा MAX_STREAMS_TRACKED		8

/*
 * define region lock types
 */
क्रमागत REGION_TYPE अणु
	REGION_TYPE_UNUSED       = 0,
	REGION_TYPE_SHARED_READ  = 1,
	REGION_TYPE_SHARED_WRITE = 2,
	REGION_TYPE_EXCLUSIVE    = 3,
पूर्ण;

/* MPI2 defines */
#घोषणा MPI2_FUNCTION_IOC_INIT              (0x02) /* IOC Init */
#घोषणा MPI2_WHOINIT_HOST_DRIVER            (0x04)
#घोषणा MPI2_VERSION_MAJOR                  (0x02)
#घोषणा MPI2_VERSION_MINOR                  (0x00)
#घोषणा MPI2_VERSION_MAJOR_MASK             (0xFF00)
#घोषणा MPI2_VERSION_MAJOR_SHIFT            (8)
#घोषणा MPI2_VERSION_MINOR_MASK             (0x00FF)
#घोषणा MPI2_VERSION_MINOR_SHIFT            (0)
#घोषणा MPI2_VERSION ((MPI2_VERSION_MAJOR << MPI2_VERSION_MAJOR_SHIFT) | \
		      MPI2_VERSION_MINOR)
#घोषणा MPI2_HEADER_VERSION_UNIT            (0x10)
#घोषणा MPI2_HEADER_VERSION_DEV             (0x00)
#घोषणा MPI2_HEADER_VERSION_UNIT_MASK       (0xFF00)
#घोषणा MPI2_HEADER_VERSION_UNIT_SHIFT      (8)
#घोषणा MPI2_HEADER_VERSION_DEV_MASK        (0x00FF)
#घोषणा MPI2_HEADER_VERSION_DEV_SHIFT       (0)
#घोषणा MPI2_HEADER_VERSION ((MPI2_HEADER_VERSION_UNIT << 8) | \
			     MPI2_HEADER_VERSION_DEV)
#घोषणा MPI2_IEEE_SGE_FLAGS_IOCPLBNTA_ADDR      (0x03)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG        (0x8000)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_CHECK_REFTAG          (0x0400)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_CHECK_REMOVE_OP       (0x0003)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_CHECK_APPTAG          (0x0200)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD           (0x0100)
#घोषणा MPI2_SCSIIO_EEDPFLAGS_INSERT_OP             (0x0004)
/* EEDP escape mode */
#घोषणा MPI25_SCSIIO_EEDPFLAGS_DO_NOT_DISABLE_MODE  (0x0040)
#घोषणा MPI2_FUNCTION_SCSI_IO_REQUEST               (0x00) /* SCSI IO */
#घोषणा MPI2_FUNCTION_SCSI_TASK_MGMT                (0x01)
#घोषणा MPI2_REQ_DESCRIPT_FLAGS_HIGH_PRIORITY       (0x03)
#घोषणा MPI2_REQ_DESCRIPT_FLAGS_FP_IO               (0x06)
#घोषणा MPI2_REQ_DESCRIPT_FLAGS_SCSI_IO                 (0x00)
#घोषणा MPI2_SGE_FLAGS_64_BIT_ADDRESSING        (0x02)
#घोषणा MPI2_SCSIIO_CONTROL_WRITE               (0x01000000)
#घोषणा MPI2_SCSIIO_CONTROL_READ                (0x02000000)
#घोषणा MPI2_REQ_DESCRIPT_FLAGS_TYPE_MASK       (0x0E)
#घोषणा MPI2_RPY_DESCRIPT_FLAGS_UNUSED          (0x0F)
#घोषणा MPI2_RPY_DESCRIPT_FLAGS_SCSI_IO_SUCCESS (0x00)
#घोषणा MPI2_RPY_DESCRIPT_FLAGS_TYPE_MASK       (0x0F)
#घोषणा MPI2_WRSEQ_FLUSH_KEY_VALUE              (0x0)
#घोषणा MPI2_WRITE_SEQUENCE_OFFSET              (0x00000004)
#घोषणा MPI2_WRSEQ_1ST_KEY_VALUE                (0xF)
#घोषणा MPI2_WRSEQ_2ND_KEY_VALUE                (0x4)
#घोषणा MPI2_WRSEQ_3RD_KEY_VALUE                (0xB)
#घोषणा MPI2_WRSEQ_4TH_KEY_VALUE                (0x2)
#घोषणा MPI2_WRSEQ_5TH_KEY_VALUE                (0x7)
#घोषणा MPI2_WRSEQ_6TH_KEY_VALUE                (0xD)

काष्ठा MPI25_IEEE_SGE_CHAIN64 अणु
	__le64			Address;
	__le32			Length;
	__le16			Reserved1;
	u8                      NextChainOffset;
	u8                      Flags;
पूर्ण;

काष्ठा MPI2_SGE_SIMPLE_UNION अणु
	__le32                     FlagsLength;
	जोड़ अणु
		__le32                 Address32;
		__le64                 Address64;
	पूर्ण u;
पूर्ण;

काष्ठा MPI2_SCSI_IO_CDB_EEDP32 अणु
	u8                      CDB[20];                    /* 0x00 */
	__be32			PrimaryReferenceTag;        /* 0x14 */
	__be16			PrimaryApplicationTag;      /* 0x18 */
	__be16			PrimaryApplicationTagMask;  /* 0x1A */
	__le32			TransferLength;             /* 0x1C */
पूर्ण;

काष्ठा MPI2_SGE_CHAIN_UNION अणु
	__le16			Length;
	u8                      NextChainOffset;
	u8                      Flags;
	जोड़ अणु
		__le32		Address32;
		__le64		Address64;
	पूर्ण u;
पूर्ण;

काष्ठा MPI2_IEEE_SGE_SIMPLE32 अणु
	__le32			Address;
	__le32			FlagsLength;
पूर्ण;

काष्ठा MPI2_IEEE_SGE_CHAIN32 अणु
	__le32			Address;
	__le32			FlagsLength;
पूर्ण;

काष्ठा MPI2_IEEE_SGE_SIMPLE64 अणु
	__le64			Address;
	__le32			Length;
	__le16			Reserved1;
	u8                      Reserved2;
	u8                      Flags;
पूर्ण;

काष्ठा MPI2_IEEE_SGE_CHAIN64 अणु
	__le64			Address;
	__le32			Length;
	__le16			Reserved1;
	u8                      Reserved2;
	u8                      Flags;
पूर्ण;

जोड़ MPI2_IEEE_SGE_SIMPLE_UNION अणु
	काष्ठा MPI2_IEEE_SGE_SIMPLE32  Simple32;
	काष्ठा MPI2_IEEE_SGE_SIMPLE64  Simple64;
पूर्ण;

जोड़ MPI2_IEEE_SGE_CHAIN_UNION अणु
	काष्ठा MPI2_IEEE_SGE_CHAIN32   Chain32;
	काष्ठा MPI2_IEEE_SGE_CHAIN64   Chain64;
पूर्ण;

जोड़ MPI2_SGE_IO_UNION अणु
	काष्ठा MPI2_SGE_SIMPLE_UNION       MpiSimple;
	काष्ठा MPI2_SGE_CHAIN_UNION        MpiChain;
	जोड़ MPI2_IEEE_SGE_SIMPLE_UNION  IeeeSimple;
	जोड़ MPI2_IEEE_SGE_CHAIN_UNION   IeeeChain;
पूर्ण;

जोड़ MPI2_SCSI_IO_CDB_UNION अणु
	u8                      CDB32[32];
	काष्ठा MPI2_SCSI_IO_CDB_EEDP32 EEDP32;
	काष्ठा MPI2_SGE_SIMPLE_UNION SGE;
पूर्ण;

/****************************************************************************
*  SCSI Task Management messages
****************************************************************************/

/*SCSI Task Management Request Message */
काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST अणु
	u16 DevHandle;		/*0x00 */
	u8 ChainOffset;		/*0x02 */
	u8 Function;		/*0x03 */
	u8 Reserved1;		/*0x04 */
	u8 TaskType;		/*0x05 */
	u8 Reserved2;		/*0x06 */
	u8 MsgFlags;		/*0x07 */
	u8 VP_ID;		/*0x08 */
	u8 VF_ID;		/*0x09 */
	u16 Reserved3;		/*0x0A */
	u8 LUN[8];		/*0x0C */
	u32 Reserved4[7];	/*0x14 */
	u16 TaskMID;		/*0x30 */
	u16 Reserved5;		/*0x32 */
पूर्ण;


/*SCSI Task Management Reply Message */
काष्ठा MPI2_SCSI_TASK_MANAGE_REPLY अणु
	u16 DevHandle;		/*0x00 */
	u8 MsgLength;		/*0x02 */
	u8 Function;		/*0x03 */
	u8 ResponseCode;	/*0x04 */
	u8 TaskType;		/*0x05 */
	u8 Reserved1;		/*0x06 */
	u8 MsgFlags;		/*0x07 */
	u8 VP_ID;		/*0x08 */
	u8 VF_ID;		/*0x09 */
	u16 Reserved2;		/*0x0A */
	u16 Reserved3;		/*0x0C */
	u16 IOCStatus;		/*0x0E */
	u32 IOCLogInfo;		/*0x10 */
	u32 TerminationCount;	/*0x14 */
	u32 ResponseInfo;	/*0x18 */
पूर्ण;

काष्ठा MR_TM_REQUEST अणु
	अक्षर request[128];
पूर्ण;

काष्ठा MR_TM_REPLY अणु
	अक्षर reply[128];
पूर्ण;

/* SCSI Task Management Request Message */
काष्ठा MR_TASK_MANAGE_REQUEST अणु
	/*To be type casted to काष्ठा MPI2_SCSI_TASK_MANAGE_REQUEST */
	काष्ठा MR_TM_REQUEST         TmRequest;
	जोड़ अणु
		काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
			u32 reserved1:30;
			u32 isTMForPD:1;
			u32 isTMForLD:1;
#अन्यथा
			u32 isTMForLD:1;
			u32 isTMForPD:1;
			u32 reserved1:30;
#पूर्ण_अगर
			u32 reserved2;
		पूर्ण पंचांगReqFlags;
		काष्ठा MR_TM_REPLY   TMReply;
	पूर्ण;
पूर्ण;

/* TaskType values */

#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK           (0x01)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET        (0x02)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET         (0x03)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET   (0x05)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_CLEAR_TASK_SET       (0x06)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK           (0x07)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_CLR_ACA              (0x08)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_QRY_TASK_SET         (0x09)
#घोषणा MPI2_SCSITASKMGMT_TASKTYPE_QRY_ASYNC_EVENT      (0x0A)

/* ResponseCode values */

#घोषणा MPI2_SCSITASKMGMT_RSP_TM_COMPLETE               (0x00)
#घोषणा MPI2_SCSITASKMGMT_RSP_INVALID_FRAME             (0x02)
#घोषणा MPI2_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED          (0x04)
#घोषणा MPI2_SCSITASKMGMT_RSP_TM_FAILED                 (0x05)
#घोषणा MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED              (0x08)
#घोषणा MPI2_SCSITASKMGMT_RSP_TM_INVALID_LUN            (0x09)
#घोषणा MPI2_SCSITASKMGMT_RSP_TM_OVERLAPPED_TAG         (0x0A)
#घोषणा MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC          (0x80)

/*
 * RAID SCSI IO Request Message
 * Total SGE count will be one less than  _MPI2_SCSI_IO_REQUEST
 */
काष्ठा MPI2_RAID_SCSI_IO_REQUEST अणु
	__le16			DevHandle;                      /* 0x00 */
	u8                      ChainOffset;                    /* 0x02 */
	u8                      Function;                       /* 0x03 */
	__le16			Reserved1;                      /* 0x04 */
	u8                      Reserved2;                      /* 0x06 */
	u8                      MsgFlags;                       /* 0x07 */
	u8                      VP_ID;                          /* 0x08 */
	u8                      VF_ID;                          /* 0x09 */
	__le16			Reserved3;                      /* 0x0A */
	__le32			SenseBufferLowAddress;          /* 0x0C */
	__le16			SGLFlags;                       /* 0x10 */
	u8                      SenseBufferLength;              /* 0x12 */
	u8                      Reserved4;                      /* 0x13 */
	u8                      SGLOffset0;                     /* 0x14 */
	u8                      SGLOffset1;                     /* 0x15 */
	u8                      SGLOffset2;                     /* 0x16 */
	u8                      SGLOffset3;                     /* 0x17 */
	__le32			SkipCount;                      /* 0x18 */
	__le32			DataLength;                     /* 0x1C */
	__le32			BidirectionalDataLength;        /* 0x20 */
	__le16			IoFlags;                        /* 0x24 */
	__le16			EEDPFlags;                      /* 0x26 */
	__le32			EEDPBlockSize;                  /* 0x28 */
	__le32			SecondaryReferenceTag;          /* 0x2C */
	__le16			SecondaryApplicationTag;        /* 0x30 */
	__le16			ApplicationTagTranslationMask;  /* 0x32 */
	u8                      LUN[8];                         /* 0x34 */
	__le32			Control;                        /* 0x3C */
	जोड़ MPI2_SCSI_IO_CDB_UNION  CDB;			/* 0x40 */
	जोड़ RAID_CONTEXT_UNION RaidContext;  /* 0x60 */
	जोड़ MPI2_SGE_IO_UNION       SGL;			/* 0x80 */
पूर्ण;

/*
 * MPT RAID MFA IO Descriptor.
 */
काष्ठा MEGASAS_RAID_MFA_IO_REQUEST_DESCRIPTOR अणु
	u32     RequestFlags:8;
	u32     MessageAddress1:24;
	u32     MessageAddress2;
पूर्ण;

/* Default Request Descriptor */
काष्ठा MPI2_DEFAULT_REQUEST_DESCRIPTOR अणु
	u8              RequestFlags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		LMID;                       /* 0x04 */
	__le16		DescriptorTypeDependent;    /* 0x06 */
पूर्ण;

/* High Priority Request Descriptor */
काष्ठा MPI2_HIGH_PRIORITY_REQUEST_DESCRIPTOR अणु
	u8              RequestFlags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		LMID;                       /* 0x04 */
	__le16		Reserved1;                  /* 0x06 */
पूर्ण;

/* SCSI IO Request Descriptor */
काष्ठा MPI2_SCSI_IO_REQUEST_DESCRIPTOR अणु
	u8              RequestFlags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		LMID;                       /* 0x04 */
	__le16		DevHandle;                  /* 0x06 */
पूर्ण;

/* SCSI Target Request Descriptor */
काष्ठा MPI2_SCSI_TARGET_REQUEST_DESCRIPTOR अणु
	u8              RequestFlags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		LMID;                       /* 0x04 */
	__le16		IoIndex;                    /* 0x06 */
पूर्ण;

/* RAID Accelerator Request Descriptor */
काष्ठा MPI2_RAID_ACCEL_REQUEST_DESCRIPTOR अणु
	u8              RequestFlags;               /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		LMID;                       /* 0x04 */
	__le16		Reserved;                   /* 0x06 */
पूर्ण;

/* जोड़ of Request Descriptors */
जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION अणु
	काष्ठा MPI2_DEFAULT_REQUEST_DESCRIPTOR             Default;
	काष्ठा MPI2_HIGH_PRIORITY_REQUEST_DESCRIPTOR       HighPriority;
	काष्ठा MPI2_SCSI_IO_REQUEST_DESCRIPTOR             SCSIIO;
	काष्ठा MPI2_SCSI_TARGET_REQUEST_DESCRIPTOR         SCSITarget;
	काष्ठा MPI2_RAID_ACCEL_REQUEST_DESCRIPTOR          RAIDAccelerator;
	काष्ठा MEGASAS_RAID_MFA_IO_REQUEST_DESCRIPTOR      MFAIo;
	जोड़ अणु
		काष्ठा अणु
			__le32 low;
			__le32 high;
		पूर्ण u;
		__le64 Words;
	पूर्ण;
पूर्ण;

/* Default Reply Descriptor */
काष्ठा MPI2_DEFAULT_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		DescriptorTypeDependent1;   /* 0x02 */
	__le32		DescriptorTypeDependent2;   /* 0x04 */
पूर्ण;

/* Address Reply Descriptor */
काष्ठा MPI2_ADDRESS_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le32		ReplyFrameAddress;          /* 0x04 */
पूर्ण;

/* SCSI IO Success Reply Descriptor */
काष्ठा MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le16		TaskTag;                    /* 0x04 */
	__le16		Reserved1;                  /* 0x06 */
पूर्ण;

/* TargetAssist Success Reply Descriptor */
काष्ठा MPI2_TARGETASSIST_SUCCESS_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	u8              SequenceNumber;             /* 0x04 */
	u8              Reserved1;                  /* 0x05 */
	__le16		IoIndex;                    /* 0x06 */
पूर्ण;

/* Target Command Buffer Reply Descriptor */
काष्ठा MPI2_TARGET_COMMAND_BUFFER_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	u8              VP_ID;                      /* 0x02 */
	u8              Flags;                      /* 0x03 */
	__le16		InitiatorDevHandle;         /* 0x04 */
	__le16		IoIndex;                    /* 0x06 */
पूर्ण;

/* RAID Accelerator Success Reply Descriptor */
काष्ठा MPI2_RAID_ACCELERATOR_SUCCESS_REPLY_DESCRIPTOR अणु
	u8              ReplyFlags;                 /* 0x00 */
	u8              MSIxIndex;                  /* 0x01 */
	__le16		SMID;                       /* 0x02 */
	__le32		Reserved;                   /* 0x04 */
पूर्ण;

/* जोड़ of Reply Descriptors */
जोड़ MPI2_REPLY_DESCRIPTORS_UNION अणु
	काष्ठा MPI2_DEFAULT_REPLY_DESCRIPTOR                   Default;
	काष्ठा MPI2_ADDRESS_REPLY_DESCRIPTOR                   AddressReply;
	काष्ठा MPI2_SCSI_IO_SUCCESS_REPLY_DESCRIPTOR           SCSIIOSuccess;
	काष्ठा MPI2_TARGETASSIST_SUCCESS_REPLY_DESCRIPTOR TargetAssistSuccess;
	काष्ठा MPI2_TARGET_COMMAND_BUFFER_REPLY_DESCRIPTOR TargetCommandBuffer;
	काष्ठा MPI2_RAID_ACCELERATOR_SUCCESS_REPLY_DESCRIPTOR
	RAIDAcceleratorSuccess;
	__le64                                             Words;
पूर्ण;

/* IOCInit Request message */
काष्ठा MPI2_IOC_INIT_REQUEST अणु
	u8                      WhoInit;                        /* 0x00 */
	u8                      Reserved1;                      /* 0x01 */
	u8                      ChainOffset;                    /* 0x02 */
	u8                      Function;                       /* 0x03 */
	__le16			Reserved2;                      /* 0x04 */
	u8                      Reserved3;                      /* 0x06 */
	u8                      MsgFlags;                       /* 0x07 */
	u8                      VP_ID;                          /* 0x08 */
	u8                      VF_ID;                          /* 0x09 */
	__le16			Reserved4;                      /* 0x0A */
	__le16			MsgVersion;                     /* 0x0C */
	__le16			HeaderVersion;                  /* 0x0E */
	u32                     Reserved5;                      /* 0x10 */
	__le16			Reserved6;                      /* 0x14 */
	u8                      HostPageSize;                   /* 0x16 */
	u8                      HostMSIxVectors;                /* 0x17 */
	__le16			Reserved8;                      /* 0x18 */
	__le16			SystemRequestFrameSize;         /* 0x1A */
	__le16			ReplyDescriptorPostQueueDepth;  /* 0x1C */
	__le16			ReplyFreeQueueDepth;            /* 0x1E */
	__le32			SenseBufferAddressHigh;         /* 0x20 */
	__le32			SystemReplyAddressHigh;         /* 0x24 */
	__le64			SystemRequestFrameBaseAddress;  /* 0x28 */
	__le64			ReplyDescriptorPostQueueAddress;/* 0x30 */
	__le64			ReplyFreeQueueAddress;          /* 0x38 */
	__le64			TimeStamp;                      /* 0x40 */
पूर्ण;

/* mrpriv defines */
#घोषणा MR_PD_INVALID 0xFFFF
#घोषणा MR_DEVHANDLE_INVALID 0xFFFF
#घोषणा MAX_SPAN_DEPTH 8
#घोषणा MAX_QUAD_DEPTH	MAX_SPAN_DEPTH
#घोषणा MAX_RAIDMAP_SPAN_DEPTH (MAX_SPAN_DEPTH)
#घोषणा MAX_ROW_SIZE 32
#घोषणा MAX_RAIDMAP_ROW_SIZE (MAX_ROW_SIZE)
#घोषणा MAX_LOGICAL_DRIVES 64
#घोषणा MAX_LOGICAL_DRIVES_EXT 256
#घोषणा MAX_LOGICAL_DRIVES_DYN 512
#घोषणा MAX_RAIDMAP_LOGICAL_DRIVES (MAX_LOGICAL_DRIVES)
#घोषणा MAX_RAIDMAP_VIEWS (MAX_LOGICAL_DRIVES)
#घोषणा MAX_ARRAYS 128
#घोषणा MAX_RAIDMAP_ARRAYS (MAX_ARRAYS)
#घोषणा MAX_ARRAYS_EXT	256
#घोषणा MAX_API_ARRAYS_EXT (MAX_ARRAYS_EXT)
#घोषणा MAX_API_ARRAYS_DYN 512
#घोषणा MAX_PHYSICAL_DEVICES 256
#घोषणा MAX_RAIDMAP_PHYSICAL_DEVICES (MAX_PHYSICAL_DEVICES)
#घोषणा MAX_RAIDMAP_PHYSICAL_DEVICES_DYN 512
#घोषणा MR_DCMD_LD_MAP_GET_INFO             0x0300e101
#घोषणा MR_DCMD_SYSTEM_PD_MAP_GET_INFO      0x0200e102
#घोषणा MR_DCMD_DRV_GET_TARGET_PROP         0x0200e103
#घोषणा MR_DCMD_CTRL_SHARED_HOST_MEM_ALLOC  0x010e8485   /* SR-IOV HB alloc*/
#घोषणा MR_DCMD_LD_VF_MAP_GET_ALL_LDS_111   0x03200200
#घोषणा MR_DCMD_LD_VF_MAP_GET_ALL_LDS       0x03150200
#घोषणा MR_DCMD_CTRL_SNAPDUMP_GET_PROPERTIES	0x01200100
#घोषणा MR_DCMD_CTRL_DEVICE_LIST_GET		0x01190600

काष्ठा MR_DEV_HANDLE_INFO अणु
	__le16	curDevHdl;
	u8      validHandles;
	u8      पूर्णांकerfaceType;
	__le16	devHandle[2];
पूर्ण;

काष्ठा MR_ARRAY_INFO अणु
	__le16	pd[MAX_RAIDMAP_ROW_SIZE];
पूर्ण;

काष्ठा MR_QUAD_ELEMENT अणु
	__le64     logStart;
	__le64     logEnd;
	__le64     offsetInSpan;
	__le32     dअगरf;
	__le32     reserved1;
पूर्ण;

काष्ठा MR_SPAN_INFO अणु
	__le32             noElements;
	__le32             reserved1;
	काष्ठा MR_QUAD_ELEMENT quad[MAX_RAIDMAP_SPAN_DEPTH];
पूर्ण;

काष्ठा MR_LD_SPAN अणु
	__le64	 startBlk;
	__le64	 numBlks;
	__le16	 arrayRef;
	u8       spanRowSize;
	u8       spanRowDataSize;
	u8       reserved[4];
पूर्ण;

काष्ठा MR_SPAN_BLOCK_INFO अणु
	__le64          num_rows;
	काष्ठा MR_LD_SPAN   span;
	काष्ठा MR_SPAN_INFO block_span_info;
पूर्ण;

#घोषणा MR_RAID_CTX_CPUSEL_0		0
#घोषणा MR_RAID_CTX_CPUSEL_1		1
#घोषणा MR_RAID_CTX_CPUSEL_2		2
#घोषणा MR_RAID_CTX_CPUSEL_3		3
#घोषणा MR_RAID_CTX_CPUSEL_FCFS		0xF

काष्ठा MR_CPU_AFFINITY_MASK अणु
	जोड़ अणु
		काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		u8 hw_path:1;
		u8 cpu0:1;
		u8 cpu1:1;
		u8 cpu2:1;
		u8 cpu3:1;
		u8 reserved:3;
#अन्यथा
		u8 reserved:3;
		u8 cpu3:1;
		u8 cpu2:1;
		u8 cpu1:1;
		u8 cpu0:1;
		u8 hw_path:1;
#पूर्ण_अगर
		पूर्ण;
		u8 core_mask;
	पूर्ण;
पूर्ण;

काष्ठा MR_IO_AFFINITY अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा MR_CPU_AFFINITY_MASK pdRead;
			काष्ठा MR_CPU_AFFINITY_MASK pdWrite;
			काष्ठा MR_CPU_AFFINITY_MASK ldRead;
			काष्ठा MR_CPU_AFFINITY_MASK ldWrite;
			पूर्ण;
		u32 word;
		पूर्ण;
	u8 maxCores;    /* Total cores + HW Path in ROC */
	u8 reserved[3];
पूर्ण;

काष्ठा MR_LD_RAID अणु
	काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
		u32 reserved4:2;
		u32 fp_cache_bypass_capable:1;
		u32 fp_rmw_capable:1;
		u32 disable_coalescing:1;
		u32     fpBypassRegionLock:1;
		u32     पंचांगCapable:1;
		u32	fpNonRWCapable:1;
		u32     fpReadAcrossStripe:1;
		u32     fpWriteAcrossStripe:1;
		u32     fpReadCapable:1;
		u32     fpWriteCapable:1;
		u32     encryptionType:8;
		u32     pdPiMode:4;
		u32     ldPiMode:4;
		u32 reserved5:2;
		u32 ra_capable:1;
		u32     fpCapable:1;
#अन्यथा
		u32     fpCapable:1;
		u32 ra_capable:1;
		u32 reserved5:2;
		u32     ldPiMode:4;
		u32     pdPiMode:4;
		u32     encryptionType:8;
		u32     fpWriteCapable:1;
		u32     fpReadCapable:1;
		u32     fpWriteAcrossStripe:1;
		u32     fpReadAcrossStripe:1;
		u32	fpNonRWCapable:1;
		u32     पंचांगCapable:1;
		u32     fpBypassRegionLock:1;
		u32 disable_coalescing:1;
		u32 fp_rmw_capable:1;
		u32 fp_cache_bypass_capable:1;
		u32 reserved4:2;
#पूर्ण_अगर
	पूर्ण capability;
	__le32     reserved6;
	__le64     size;
	u8      spanDepth;
	u8      level;
	u8      stripeShअगरt;
	u8      rowSize;
	u8      rowDataSize;
	u8      ग_लिखोMode;
	u8      PRL;
	u8      SRL;
	__le16     targetId;
	u8      ldState;
	u8      regTypeReqOnWrite;
	u8      modFactor;
	u8	regTypeReqOnRead;
	__le16     seqNum;

काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
	u32 ldSyncRequired:1;
	u32 regTypeReqOnReadIsValid:1;
	u32 isEPD:1;
	u32 enableSLDOnAllRWIOs:1;
	u32 reserved:28;
#अन्यथा
	u32 reserved:28;
	u32 enableSLDOnAllRWIOs:1;
	u32 isEPD:1;
	u32 regTypeReqOnReadIsValid:1;
	u32 ldSyncRequired:1;
#पूर्ण_अगर
	पूर्ण flags;

	u8	LUN[8]; /* 0x24 8 byte LUN field used क्रम SCSI IO's */
	u8	fpIoTimeoutForLd;/*0x2C समयout value used by driver in FP IO*/
	/* Ox2D This LD accept priority boost of this type */
	u8 ld_accept_priority_type;
	u8 reserved2[2];	        /* 0x2E - 0x2F */
	/* 0x30 - 0x33, Logical block size क्रम the LD */
	u32 logical_block_length;
	काष्ठा अणु
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
	/* 0x34, P_I_EXPONENT from READ CAPACITY 16 */
	u32 ld_pi_exp:4;
	/* 0x34, LOGICAL BLOCKS PER PHYSICAL
	 *  BLOCK EXPONENT from READ CAPACITY 16
	 */
	u32 ld_logical_block_exp:4;
	u32 reserved1:24;           /* 0x34 */
#अन्यथा
	u32 reserved1:24;           /* 0x34 */
	/* 0x34, LOGICAL BLOCKS PER PHYSICAL
	 *  BLOCK EXPONENT from READ CAPACITY 16
	 */
	u32 ld_logical_block_exp:4;
	/* 0x34, P_I_EXPONENT from READ CAPACITY 16 */
	u32 ld_pi_exp:4;
#पूर्ण_अगर
	पूर्ण;                               /* 0x34 - 0x37 */
	 /* 0x38 - 0x3f, This will determine which
	  *  core will process LD IO and PD IO.
	  */
	काष्ठा MR_IO_AFFINITY cpuAffinity;
     /* Bit definiations are specअगरied by MR_IO_AFFINITY */
	u8 reserved3[0x80 - 0x40];    /* 0x40 - 0x7f */
पूर्ण;

काष्ठा MR_LD_SPAN_MAP अणु
	काष्ठा MR_LD_RAID          ldRaid;
	u8                  dataArmMap[MAX_RAIDMAP_ROW_SIZE];
	काष्ठा MR_SPAN_BLOCK_INFO  spanBlock[MAX_RAIDMAP_SPAN_DEPTH];
पूर्ण;

काष्ठा MR_FW_RAID_MAP अणु
	__le32                 totalSize;
	जोड़ अणु
		काष्ठा अणु
			__le32         maxLd;
			__le32         maxSpanDepth;
			__le32         maxRowSize;
			__le32         maxPdCount;
			__le32         maxArrays;
		पूर्ण validationInfo;
		__le32             version[5];
	पूर्ण;

	__le32                 ldCount;
	__le32                 Reserved1;
	u8                  ldTgtIdToLd[MAX_RAIDMAP_LOGICAL_DRIVES+
					MAX_RAIDMAP_VIEWS];
	u8                  fpPdIoTimeoutSec;
	u8                  reserved2[7];
	काष्ठा MR_ARRAY_INFO       arMapInfo[MAX_RAIDMAP_ARRAYS];
	काष्ठा MR_DEV_HANDLE_INFO  devHndlInfo[MAX_RAIDMAP_PHYSICAL_DEVICES];
	काष्ठा MR_LD_SPAN_MAP      ldSpanMap[1];
पूर्ण;

काष्ठा IO_REQUEST_INFO अणु
	u64 ldStartBlock;
	u32 numBlocks;
	u16 ldTgtId;
	u8 isRead;
	__le16 devHandle;
	u8 pd_पूर्णांकerface;
	u64 pdBlock;
	u8 fpOkForIo;
	u8 Ioक्रमUnevenSpan;
	u8 start_span;
	u8 करो_fp_rlbypass;
	u64 start_row;
	u8  span_arm;	/* span[7:5], arm[4:0] */
	u8  pd_after_lb;
	u16 r1_alt_dev_handle; /* raid 1/10 only */
	bool ra_capable;
	u8 data_arms;
पूर्ण;

काष्ठा MR_LD_TARGET_SYNC अणु
	u8  targetId;
	u8  reserved;
	__le16 seqNum;
पूर्ण;

/*
 * RAID Map descriptor Types.
 * Each element should uniquely idetअगरy one data काष्ठाure in the RAID map
 */
क्रमागत MR_RAID_MAP_DESC_TYPE अणु
	/* MR_DEV_HANDLE_INFO data */
	RAID_MAP_DESC_TYPE_DEVHDL_INFO    = 0x0,
	/* target to Ld num Index map */
	RAID_MAP_DESC_TYPE_TGTID_INFO     = 0x1,
	/* MR_ARRAY_INFO data */
	RAID_MAP_DESC_TYPE_ARRAY_INFO     = 0x2,
	/* MR_LD_SPAN_MAP data */
	RAID_MAP_DESC_TYPE_SPAN_INFO      = 0x3,
	RAID_MAP_DESC_TYPE_COUNT,
पूर्ण;

/*
 * This table defines the offset, size and num elements  of each descriptor
 * type in the RAID Map buffer
 */
काष्ठा MR_RAID_MAP_DESC_TABLE अणु
	/* Raid map descriptor type */
	u32 raid_map_desc_type;
	/* Offset पूर्णांकo the RAID map buffer where
	 *  descriptor data is saved
	 */
	u32 raid_map_desc_offset;
	/* total size of the
	 * descriptor buffer
	 */
	u32 raid_map_desc_buffer_size;
	/* Number of elements contained in the
	 *  descriptor buffer
	 */
	u32 raid_map_desc_elements;
पूर्ण;

/*
 * Dynamic Raid Map Structure.
 */
काष्ठा MR_FW_RAID_MAP_DYNAMIC अणु
	u32 raid_map_size;   /* total size of RAID Map काष्ठाure */
	u32 desc_table_offset;/* Offset of desc table पूर्णांकo RAID map*/
	u32 desc_table_size;  /* Total Size of desc table */
	/* Total Number of elements in the desc table */
	u32 desc_table_num_elements;
	u64	reserved1;
	u32	reserved2[3];	/*future use */
	/* समयout value used by driver in FP IOs */
	u8 fp_pd_io_समयout_sec;
	u8 reserved3[3];
	/* when this seqNum increments, driver needs to
	 *  release RMW buffers asap
	 */
	u32 rmw_fp_seq_num;
	u16 ld_count;	/* count of lds. */
	u16 ar_count;   /* count of arrays */
	u16 span_count; /* count of spans */
	u16 reserved4[3];
/*
 * The below काष्ठाure of poपूर्णांकers is only to be used by the driver.
 * This is added in the ,API to reduce the amount of code changes
 * needed in the driver to support dynamic RAID map Firmware should
 * not update these poपूर्णांकers जबतक preparing the raid map
 */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा MR_DEV_HANDLE_INFO  *dev_hndl_info;
			u16 *ld_tgt_id_to_ld;
			काष्ठा MR_ARRAY_INFO *ar_map_info;
			काष्ठा MR_LD_SPAN_MAP *ld_span_map;
			पूर्ण;
		u64 ptr_काष्ठाure_size[RAID_MAP_DESC_TYPE_COUNT];
		पूर्ण;
/*
 * RAID Map descriptor table defines the layout of data in the RAID Map.
 * The size of the descriptor table itself could change.
 */
	/* Variable Size descriptor Table. */
	काष्ठा MR_RAID_MAP_DESC_TABLE
			raid_map_desc_table[RAID_MAP_DESC_TYPE_COUNT];
	/* Variable Size buffer containing all data */
	u32 raid_map_desc_data[1];
पूर्ण; /* Dynamicaly sized RAID MAp काष्ठाure */

#घोषणा IEEE_SGE_FLAGS_ADDR_MASK            (0x03)
#घोषणा IEEE_SGE_FLAGS_SYSTEM_ADDR          (0x00)
#घोषणा IEEE_SGE_FLAGS_IOCDDR_ADDR          (0x01)
#घोषणा IEEE_SGE_FLAGS_IOCPLB_ADDR          (0x02)
#घोषणा IEEE_SGE_FLAGS_IOCPLBNTA_ADDR       (0x03)
#घोषणा IEEE_SGE_FLAGS_CHAIN_ELEMENT        (0x80)
#घोषणा IEEE_SGE_FLAGS_END_OF_LIST          (0x40)

#घोषणा MPI2_SGE_FLAGS_SHIFT                (0x02)
#घोषणा IEEE_SGE_FLAGS_FORMAT_MASK          (0xC0)
#घोषणा IEEE_SGE_FLAGS_FORMAT_IEEE          (0x00)
#घोषणा IEEE_SGE_FLAGS_FORMAT_NVME          (0x02)

#घोषणा MPI26_IEEE_SGE_FLAGS_NSF_MASK           (0x1C)
#घोषणा MPI26_IEEE_SGE_FLAGS_NSF_MPI_IEEE       (0x00)
#घोषणा MPI26_IEEE_SGE_FLAGS_NSF_NVME_PRP       (0x08)
#घोषणा MPI26_IEEE_SGE_FLAGS_NSF_NVME_SGL       (0x10)

#घोषणा MEGASAS_DEFAULT_SNAP_DUMP_WAIT_TIME 15
#घोषणा MEGASAS_MAX_SNAP_DUMP_WAIT_TIME 60

काष्ठा megasas_रेजिस्टर_set;
काष्ठा megasas_instance;

जोड़ desc_word अणु
	u64 word;
	काष्ठा अणु
		u32 low;
		u32 high;
	पूर्ण u;
पूर्ण;

काष्ठा megasas_cmd_fusion अणु
	काष्ठा MPI2_RAID_SCSI_IO_REQUEST	*io_request;
	dma_addr_t			io_request_phys_addr;

	जोड़ MPI2_SGE_IO_UNION	*sg_frame;
	dma_addr_t		sg_frame_phys_addr;

	u8 *sense;
	dma_addr_t sense_phys_addr;

	काष्ठा list_head list;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा megasas_instance *instance;

	u8 retry_क्रम_fw_reset;
	जोड़ MEGASAS_REQUEST_DESCRIPTOR_UNION  *request_desc;

	/*
	 * Context क्रम a MFI frame.
	 * Used to get the mfi cmd from list when a MFI cmd is completed
	 */
	u32 sync_cmd_idx;
	u32 index;
	u8 pd_r1_lb;
	काष्ठा completion करोne;
	u8 pd_पूर्णांकerface;
	u16 r1_alt_dev_handle; /* raid 1/10 only*/
	bool cmd_completed;  /* raid 1/10 fp ग_लिखोs status holder */

पूर्ण;

काष्ठा LD_LOAD_BALANCE_INFO अणु
	u8	loadBalanceFlag;
	u8	reserved1;
	atomic_t     scsi_pending_cmds[MAX_PHYSICAL_DEVICES];
	u64     last_accessed_block[MAX_PHYSICAL_DEVICES];
पूर्ण;

/* SPAN_SET is info caclulated from span info from Raid map per LD */
प्रकार काष्ठा _LD_SPAN_SET अणु
	u64  log_start_lba;
	u64  log_end_lba;
	u64  span_row_start;
	u64  span_row_end;
	u64  data_strip_start;
	u64  data_strip_end;
	u64  data_row_start;
	u64  data_row_end;
	u8   strip_offset[MAX_SPAN_DEPTH];
	u32    span_row_data_width;
	u32    dअगरf;
	u32    reserved[2];
पूर्ण LD_SPAN_SET, *PLD_SPAN_SET;

प्रकार काष्ठा LOG_BLOCK_SPAN_INFO अणु
	LD_SPAN_SET  span_set[MAX_SPAN_DEPTH];
पूर्ण LD_SPAN_INFO, *PLD_SPAN_INFO;

काष्ठा MR_FW_RAID_MAP_ALL अणु
	काष्ठा MR_FW_RAID_MAP raidMap;
	काष्ठा MR_LD_SPAN_MAP ldSpanMap[MAX_LOGICAL_DRIVES - 1];
पूर्ण __attribute__ ((packed));

काष्ठा MR_DRV_RAID_MAP अणु
	/* total size of this काष्ठाure, including this field.
	 * This feild will be manupulated by driver क्रम ext raid map,
	 * अन्यथा pick the value from firmware raid map.
	 */
	__le32                 totalSize;

	जोड़ अणु
	काष्ठा अणु
		__le32         maxLd;
		__le32         maxSpanDepth;
		__le32         maxRowSize;
		__le32         maxPdCount;
		__le32         maxArrays;
	पूर्ण validationInfo;
	__le32             version[5];
	पूर्ण;

	/* समयout value used by driver in FP IOs*/
	u8                  fpPdIoTimeoutSec;
	u8                  reserved2[7];

	__le16                 ldCount;
	__le16                 arCount;
	__le16                 spanCount;
	__le16                 reserve3;

	काष्ठा MR_DEV_HANDLE_INFO
		devHndlInfo[MAX_RAIDMAP_PHYSICAL_DEVICES_DYN];
	u16 ldTgtIdToLd[MAX_LOGICAL_DRIVES_DYN];
	काष्ठा MR_ARRAY_INFO arMapInfo[MAX_API_ARRAYS_DYN];
	काष्ठा MR_LD_SPAN_MAP      ldSpanMap[1];

पूर्ण;

/* Driver raid map size is same as raid map ext
 * MR_DRV_RAID_MAP_ALL is created to sync with old raid.
 * And it is मुख्यly क्रम code re-use purpose.
 */
काष्ठा MR_DRV_RAID_MAP_ALL अणु

	काष्ठा MR_DRV_RAID_MAP raidMap;
	काष्ठा MR_LD_SPAN_MAP ldSpanMap[MAX_LOGICAL_DRIVES_DYN - 1];
पूर्ण __packed;



काष्ठा MR_FW_RAID_MAP_EXT अणु
	/* Not usred in new map */
	u32                 reserved;

	जोड़ अणु
	काष्ठा अणु
		u32         maxLd;
		u32         maxSpanDepth;
		u32         maxRowSize;
		u32         maxPdCount;
		u32         maxArrays;
	पूर्ण validationInfo;
	u32             version[5];
	पूर्ण;

	u8                  fpPdIoTimeoutSec;
	u8                  reserved2[7];

	__le16                 ldCount;
	__le16                 arCount;
	__le16                 spanCount;
	__le16                 reserve3;

	काष्ठा MR_DEV_HANDLE_INFO  devHndlInfo[MAX_RAIDMAP_PHYSICAL_DEVICES];
	u8                  ldTgtIdToLd[MAX_LOGICAL_DRIVES_EXT];
	काष्ठा MR_ARRAY_INFO       arMapInfo[MAX_API_ARRAYS_EXT];
	काष्ठा MR_LD_SPAN_MAP      ldSpanMap[MAX_LOGICAL_DRIVES_EXT];
पूर्ण;

/*
 *  * define MR_PD_CFG_SEQ काष्ठाure क्रम प्रणाली PDs
 *   */
काष्ठा MR_PD_CFG_SEQ अणु
	u16 seqNum;
	u16 devHandle;
	काष्ठा अणु
#अगर   defined(__BIG_ENDIAN_BITFIELD)
		u8     reserved:7;
		u8     पंचांगCapable:1;
#अन्यथा
		u8     पंचांगCapable:1;
		u8     reserved:7;
#पूर्ण_अगर
	पूर्ण capability;
	u8  reserved;
	u16 pd_target_id;
पूर्ण __packed;

काष्ठा MR_PD_CFG_SEQ_NUM_SYNC अणु
	__le32 size;
	__le32 count;
	काष्ठा MR_PD_CFG_SEQ seq[1];
पूर्ण __packed;

/* stream detection */
काष्ठा STREAM_DETECT अणु
	u64 next_seq_lba; /* next LBA to match sequential access */
	काष्ठा megasas_cmd_fusion *first_cmd_fusion; /* first cmd in group */
	काष्ठा megasas_cmd_fusion *last_cmd_fusion; /* last cmd in group */
	u32 count_cmds_in_stream; /* count of host commands in this stream */
	u16 num_sges_in_group; /* total number of SGEs in grouped IOs */
	u8 is_पढ़ो; /* SCSI OpCode क्रम this stream */
	u8 group_depth; /* total number of host commands in group */
	/* TRUE अगर cannot add any more commands to this group */
	bool group_flush;
	u8 reserved[7]; /* pad to 64-bit alignment */
पूर्ण;

काष्ठा LD_STREAM_DETECT अणु
	bool ग_लिखो_back; /* TRUE अगर WB, FALSE अगर WT */
	bool fp_ग_लिखो_enabled;
	bool members_ssds;
	bool fp_cache_bypass_capable;
	u32 mru_bit_map; /* biपंचांगap used to track MRU and LRU stream indicies */
	/* this is the array of stream detect काष्ठाures (one per stream) */
	काष्ठा STREAM_DETECT stream_track[MAX_STREAMS_TRACKED];
पूर्ण;

काष्ठा MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY अणु
	u64 RDPQBaseAddress;
	u32 Reserved1;
	u32 Reserved2;
पूर्ण;

काष्ठा rdpq_alloc_detail अणु
	काष्ठा dma_pool *dma_pool_ptr;
	dma_addr_t	pool_entry_phys;
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *pool_entry_virt;
पूर्ण;

काष्ठा fusion_context अणु
	काष्ठा megasas_cmd_fusion **cmd_list;
	dma_addr_t req_frames_desc_phys;
	u8 *req_frames_desc;

	काष्ठा dma_pool *io_request_frames_pool;
	dma_addr_t io_request_frames_phys;
	u8 *io_request_frames;

	काष्ठा dma_pool *sg_dma_pool;
	काष्ठा dma_pool *sense_dma_pool;

	u8 *sense;
	dma_addr_t sense_phys_addr;

	atomic_t   busy_mq_poll[MAX_MSIX_QUEUES_FUSION];

	dma_addr_t reply_frames_desc_phys[MAX_MSIX_QUEUES_FUSION];
	जोड़ MPI2_REPLY_DESCRIPTORS_UNION *reply_frames_desc[MAX_MSIX_QUEUES_FUSION];
	काष्ठा rdpq_alloc_detail rdpq_tracker[RDPQ_MAX_CHUNK_COUNT];
	काष्ठा dma_pool *reply_frames_desc_pool;
	काष्ठा dma_pool *reply_frames_desc_pool_align;

	u16 last_reply_idx[MAX_MSIX_QUEUES_FUSION];

	u32 reply_q_depth;
	u32 request_alloc_sz;
	u32 reply_alloc_sz;
	u32 io_frames_alloc_sz;

	काष्ठा MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY *rdpq_virt;
	dma_addr_t rdpq_phys;
	u16	max_sge_in_मुख्य_msg;
	u16	max_sge_in_chain;

	u8	chain_offset_io_request;
	u8	chain_offset_mfi_pthru;

	काष्ठा MR_FW_RAID_MAP_DYNAMIC *ld_map[2];
	dma_addr_t ld_map_phys[2];

	/*Non dma-able memory. Driver local copy.*/
	काष्ठा MR_DRV_RAID_MAP_ALL *ld_drv_map[2];

	u32 max_map_sz;
	u32 current_map_sz;
	u32 old_map_sz;
	u32 new_map_sz;
	u32 drv_map_sz;
	u32 drv_map_pages;
	काष्ठा MR_PD_CFG_SEQ_NUM_SYNC	*pd_seq_sync[JBOD_MAPS_COUNT];
	dma_addr_t pd_seq_phys[JBOD_MAPS_COUNT];
	u8 fast_path_io;
	काष्ठा LD_LOAD_BALANCE_INFO *load_balance_info;
	u32 load_balance_info_pages;
	LD_SPAN_INFO *log_to_span;
	u32 log_to_span_pages;
	काष्ठा LD_STREAM_DETECT **stream_detect_by_ld;
	dma_addr_t ioc_init_request_phys;
	काष्ठा MPI2_IOC_INIT_REQUEST *ioc_init_request;
	काष्ठा megasas_cmd *ioc_init_cmd;
	bool pcie_bw_limitation;
	bool r56_भाग_offload;
पूर्ण;

जोड़ desc_value अणु
	__le64 word;
	काष्ठा अणु
		__le32 low;
		__le32 high;
	पूर्ण u;
पूर्ण;

क्रमागत CMD_RET_VALUES अणु
	REFIRE_CMD = 1,
	COMPLETE_CMD = 2,
	RETURN_CMD = 3,
पूर्ण;

काष्ठा  MR_SNAPDUMP_PROPERTIES अणु
	u8       offload_num;
	u8       max_num_supported;
	u8       cur_num_supported;
	u8       trigger_min_num_sec_beक्रमe_ocr;
	u8       reserved[12];
पूर्ण;

काष्ठा megasas_debugfs_buffer अणु
	व्योम *buf;
	u32 len;
पूर्ण;

व्योम megasas_मुक्त_cmds_fusion(काष्ठा megasas_instance *instance);
पूर्णांक megasas_ioc_init_fusion(काष्ठा megasas_instance *instance);
u8 megasas_get_map_info(काष्ठा megasas_instance *instance);
पूर्णांक megasas_sync_map_info(काष्ठा megasas_instance *instance);
व्योम megasas_release_fusion(काष्ठा megasas_instance *instance);
व्योम megasas_reset_reply_desc(काष्ठा megasas_instance *instance);
पूर्णांक megasas_check_mpio_paths(काष्ठा megasas_instance *instance,
			      काष्ठा scsi_cmnd *scmd);
व्योम megasas_fusion_ocr_wq(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* _MEGARAID_SAS_FUSION_H_ */

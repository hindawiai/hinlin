<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_FWIF_H
#घोषणा _INTEL_GUC_FWIF_H

#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#घोषणा GUC_CLIENT_PRIORITY_KMD_HIGH	0
#घोषणा GUC_CLIENT_PRIORITY_HIGH	1
#घोषणा GUC_CLIENT_PRIORITY_KMD_NORMAL	2
#घोषणा GUC_CLIENT_PRIORITY_NORMAL	3
#घोषणा GUC_CLIENT_PRIORITY_NUM		4

#घोषणा GUC_MAX_STAGE_DESCRIPTORS	1024
#घोषणा	GUC_INVALID_STAGE_ID		GUC_MAX_STAGE_DESCRIPTORS

#घोषणा GUC_RENDER_ENGINE		0
#घोषणा GUC_VIDEO_ENGINE		1
#घोषणा GUC_BLITTER_ENGINE		2
#घोषणा GUC_VIDEOENHANCE_ENGINE		3
#घोषणा GUC_VIDEO_ENGINE2		4
#घोषणा GUC_MAX_ENGINES_NUM		(GUC_VIDEO_ENGINE2 + 1)

#घोषणा GUC_MAX_ENGINE_CLASSES		16
#घोषणा GUC_MAX_INSTANCES_PER_CLASS	32

#घोषणा GUC_DOORBELL_INVALID		256

#घोषणा GUC_WQ_SIZE			(PAGE_SIZE * 2)

/* Work queue item header definitions */
#घोषणा WQ_STATUS_ACTIVE		1
#घोषणा WQ_STATUS_SUSPENDED		2
#घोषणा WQ_STATUS_CMD_ERROR		3
#घोषणा WQ_STATUS_ENGINE_ID_NOT_USED	4
#घोषणा WQ_STATUS_SUSPENDED_FROM_RESET	5
#घोषणा WQ_TYPE_SHIFT			0
#घोषणा   WQ_TYPE_BATCH_BUF		(0x1 << WQ_TYPE_SHIFT)
#घोषणा   WQ_TYPE_PSEUDO		(0x2 << WQ_TYPE_SHIFT)
#घोषणा   WQ_TYPE_INORDER		(0x3 << WQ_TYPE_SHIFT)
#घोषणा   WQ_TYPE_NOOP			(0x4 << WQ_TYPE_SHIFT)
#घोषणा WQ_TARGET_SHIFT			10
#घोषणा WQ_LEN_SHIFT			16
#घोषणा WQ_NO_WCFLUSH_WAIT		(1 << 27)
#घोषणा WQ_PRESENT_WORKLOAD		(1 << 28)

#घोषणा WQ_RING_TAIL_SHIFT		20
#घोषणा WQ_RING_TAIL_MAX		0x7FF	/* 2^11 QWords */
#घोषणा WQ_RING_TAIL_MASK		(WQ_RING_TAIL_MAX << WQ_RING_TAIL_SHIFT)

#घोषणा GUC_STAGE_DESC_ATTR_ACTIVE	BIT(0)
#घोषणा GUC_STAGE_DESC_ATTR_PENDING_DB	BIT(1)
#घोषणा GUC_STAGE_DESC_ATTR_KERNEL	BIT(2)
#घोषणा GUC_STAGE_DESC_ATTR_PREEMPT	BIT(3)
#घोषणा GUC_STAGE_DESC_ATTR_RESET	BIT(4)
#घोषणा GUC_STAGE_DESC_ATTR_WQLOCKED	BIT(5)
#घोषणा GUC_STAGE_DESC_ATTR_PCH		BIT(6)
#घोषणा GUC_STAGE_DESC_ATTR_TERMINATED	BIT(7)

#घोषणा GUC_CTL_LOG_PARAMS		0
#घोषणा   GUC_LOG_VALID			(1 << 0)
#घोषणा   GUC_LOG_NOTIFY_ON_HALF_FULL	(1 << 1)
#घोषणा   GUC_LOG_ALLOC_IN_MEGABYTE	(1 << 3)
#घोषणा   GUC_LOG_CRASH_SHIFT		4
#घोषणा   GUC_LOG_CRASH_MASK		(0x3 << GUC_LOG_CRASH_SHIFT)
#घोषणा   GUC_LOG_DPC_SHIFT		6
#घोषणा   GUC_LOG_DPC_MASK	        (0x7 << GUC_LOG_DPC_SHIFT)
#घोषणा   GUC_LOG_ISR_SHIFT		9
#घोषणा   GUC_LOG_ISR_MASK	        (0x7 << GUC_LOG_ISR_SHIFT)
#घोषणा   GUC_LOG_BUF_ADDR_SHIFT	12

#घोषणा GUC_CTL_WA			1
#घोषणा GUC_CTL_FEATURE			2
#घोषणा   GUC_CTL_DISABLE_SCHEDULER	(1 << 14)

#घोषणा GUC_CTL_DEBUG			3
#घोषणा   GUC_LOG_VERBOSITY_SHIFT	0
#घोषणा   GUC_LOG_VERBOSITY_LOW		(0 << GUC_LOG_VERBOSITY_SHIFT)
#घोषणा   GUC_LOG_VERBOSITY_MED		(1 << GUC_LOG_VERBOSITY_SHIFT)
#घोषणा   GUC_LOG_VERBOSITY_HIGH	(2 << GUC_LOG_VERBOSITY_SHIFT)
#घोषणा   GUC_LOG_VERBOSITY_ULTRA	(3 << GUC_LOG_VERBOSITY_SHIFT)
/* Verbosity range-check limits, without the shअगरt */
#घोषणा	  GUC_LOG_VERBOSITY_MIN		0
#घोषणा	  GUC_LOG_VERBOSITY_MAX		3
#घोषणा	  GUC_LOG_VERBOSITY_MASK	0x0000000f
#घोषणा	  GUC_LOG_DESTINATION_MASK	(3 << 4)
#घोषणा   GUC_LOG_DISABLED		(1 << 6)
#घोषणा   GUC_PROखाता_ENABLED		(1 << 7)

#घोषणा GUC_CTL_ADS			4
#घोषणा   GUC_ADS_ADDR_SHIFT		1
#घोषणा   GUC_ADS_ADDR_MASK		(0xFFFFF << GUC_ADS_ADDR_SHIFT)

#घोषणा GUC_CTL_MAX_DWORDS		(SOFT_SCRATCH_COUNT - 2) /* [1..14] */

/* Generic GT SysInfo data types */
#घोषणा GUC_GENERIC_GT_SYSINFO_SLICE_ENABLED		0
#घोषणा GUC_GENERIC_GT_SYSINFO_VDBOX_SFC_SUPPORT_MASK	1
#घोषणा GUC_GENERIC_GT_SYSINFO_DOORBELL_COUNT_PER_SQIDI	2
#घोषणा GUC_GENERIC_GT_SYSINFO_MAX			16

/*
 * The class goes in bits [0..2] of the GuC ID, the instance in bits [3..6].
 * Bit 7 can be used क्रम operations that apply to all engine classes&instances.
 */
#घोषणा GUC_ENGINE_CLASS_SHIFT		0
#घोषणा GUC_ENGINE_CLASS_MASK		(0x7 << GUC_ENGINE_CLASS_SHIFT)
#घोषणा GUC_ENGINE_INSTANCE_SHIFT	3
#घोषणा GUC_ENGINE_INSTANCE_MASK	(0xf << GUC_ENGINE_INSTANCE_SHIFT)
#घोषणा GUC_ENGINE_ALL_INSTANCES	BIT(7)

#घोषणा MAKE_GUC_ID(class, instance) \
	(((class) << GUC_ENGINE_CLASS_SHIFT) | \
	 ((instance) << GUC_ENGINE_INSTANCE_SHIFT))

#घोषणा GUC_ID_TO_ENGINE_CLASS(guc_id) \
	(((guc_id) & GUC_ENGINE_CLASS_MASK) >> GUC_ENGINE_CLASS_SHIFT)
#घोषणा GUC_ID_TO_ENGINE_INSTANCE(guc_id) \
	(((guc_id) & GUC_ENGINE_INSTANCE_MASK) >> GUC_ENGINE_INSTANCE_SHIFT)

/* Work item क्रम submitting workloads पूर्णांकo work queue of GuC. */
काष्ठा guc_wq_item अणु
	u32 header;
	u32 context_desc;
	u32 submit_element_info;
	u32 fence_id;
पूर्ण __packed;

काष्ठा guc_process_desc अणु
	u32 stage_id;
	u64 db_base_addr;
	u32 head;
	u32 tail;
	u32 error_offset;
	u64 wq_base_addr;
	u32 wq_size_bytes;
	u32 wq_status;
	u32 engine_presence;
	u32 priority;
	u32 reserved[30];
पूर्ण __packed;

/* engine id and context id is packed पूर्णांकo guc_execlist_context.context_id*/
#घोषणा GUC_ELC_CTXID_OFFSET		0
#घोषणा GUC_ELC_ENGINE_OFFSET		29

/* The execlist context including software and HW inक्रमmation */
काष्ठा guc_execlist_context अणु
	u32 context_desc;
	u32 context_id;
	u32 ring_status;
	u32 ring_lrca;
	u32 ring_begin;
	u32 ring_end;
	u32 ring_next_मुक्त_location;
	u32 ring_current_tail_poपूर्णांकer_value;
	u8 engine_state_submit_value;
	u8 engine_state_रुको_value;
	u16 pagefault_count;
	u16 engine_submit_queue_count;
पूर्ण __packed;

/*
 * This काष्ठाure describes a stage set arranged क्रम a particular communication
 * between uKernel (GuC) and Driver (KMD). Technically, this is known as a
 * "GuC Context descriptor" in the specs, but we use the term "stage descriptor"
 * to aव्योम confusion with all the other things alपढ़ोy named "context" in the
 * driver. A अटल pool of these descriptors are stored inside a GEM object
 * (stage_desc_pool) which is held क्रम the entire lअगरeसमय of our पूर्णांकeraction
 * with the GuC, being allocated beक्रमe the GuC is loaded with its firmware.
 */
काष्ठा guc_stage_desc अणु
	u32 sched_common_area;
	u32 stage_id;
	u32 pas_id;
	u8 engines_used;
	u64 db_trigger_cpu;
	u32 db_trigger_uk;
	u64 db_trigger_phy;
	u16 db_id;

	काष्ठा guc_execlist_context lrc[GUC_MAX_ENGINES_NUM];

	u8 attribute;

	u32 priority;

	u32 wq_sampled_tail_offset;
	u32 wq_total_submit_enqueues;

	u32 process_desc;
	u32 wq_addr;
	u32 wq_size;

	u32 engine_presence;

	u8 engine_suspended;

	u8 reserved0[3];
	u64 reserved1[1];

	u64 desc_निजी;
पूर्ण __packed;

/**
 * DOC: CTB based communication
 *
 * The CTB (command transport buffer) communication between Host and GuC
 * is based on u32 data stream written to the shared buffer. One buffer can
 * be used to transmit data only in one direction (one-directional channel).
 *
 * Current status of the each buffer is stored in the buffer descriptor.
 * Buffer descriptor holds tail and head fields that represents active data
 * stream. The tail field is updated by the data producer (sender), and head
 * field is updated by the data consumer (receiver)::
 *
 *      +------------+
 *      | DESCRIPTOR |          +=================+============+========+
 *      +============+          |                 | MESSAGE(s) |        |
 *      | address    |--------->+=================+============+========+
 *      +------------+
 *      | head       |          ^-----head--------^
 *      +------------+
 *      | tail       |          ^---------tail-----------------^
 *      +------------+
 *      | size       |          ^---------------size--------------------^
 *      +------------+
 *
 * Each message in data stream starts with the single u32 treated as a header,
 * followed by optional set of u32 data that makes message specअगरic payload::
 *
 *      +------------+---------+---------+---------+
 *      |         MESSAGE                          |
 *      +------------+---------+---------+---------+
 *      |   msg[0]   |   [1]   |   ...   |  [n-1]  |
 *      +------------+---------+---------+---------+
 *      |   MESSAGE  |       MESSAGE PAYLOAD       |
 *      +   HEADER   +---------+---------+---------+
 *      |            |    0    |   ...   |    n    |
 *      +======+=====+=========+=========+=========+
 *      | 31:16| code|         |         |         |
 *      +------+-----+         |         |         |
 *      |  15:5|flags|         |         |         |
 *      +------+-----+         |         |         |
 *      |   4:0|  len|         |         |         |
 *      +------+-----+---------+---------+---------+
 *
 *                   ^-------------len-------------^
 *
 * The message header consists of:
 *
 * - **len**, indicates length of the message payload (in u32)
 * - **code**, indicates message code
 * - **flags**, holds various bits to control message handling
 */

/*
 * Describes single command transport buffer.
 * Used by both guc-master and clients.
 */
काष्ठा guc_ct_buffer_desc अणु
	u32 addr;		/* gfx address */
	u64 host_निजी;	/* host निजी data */
	u32 size;		/* size in bytes */
	u32 head;		/* offset updated by GuC*/
	u32 tail;		/* offset updated by owner */
	u32 is_in_error;	/* error indicator */
	u32 fence;		/* fence updated by GuC */
	u32 status;		/* status updated by GuC */
	u32 owner;		/* id of the channel owner */
	u32 owner_sub_id;	/* owner-defined field क्रम extra tracking */
	u32 reserved[5];
पूर्ण __packed;

/* Type of command transport buffer */
#घोषणा INTEL_GUC_CT_BUFFER_TYPE_SEND	0x0u
#घोषणा INTEL_GUC_CT_BUFFER_TYPE_RECV	0x1u

/*
 * Definition of the command transport message header (DW0)
 *
 * bit[4..0]	message len (in dwords)
 * bit[7..5]	reserved
 * bit[8]	response (G2H only)
 * bit[8]	ग_लिखो fence to desc (H2G only)
 * bit[9]	ग_लिखो status to H2G buff (H2G only)
 * bit[10]	send status back via G2H (H2G only)
 * bit[15..11]	reserved
 * bit[31..16]	action code
 */
#घोषणा GUC_CT_MSG_LEN_SHIFT			0
#घोषणा GUC_CT_MSG_LEN_MASK			0x1F
#घोषणा GUC_CT_MSG_IS_RESPONSE			(1 << 8)
#घोषणा GUC_CT_MSG_WRITE_FENCE_TO_DESC		(1 << 8)
#घोषणा GUC_CT_MSG_WRITE_STATUS_TO_BUFF		(1 << 9)
#घोषणा GUC_CT_MSG_SEND_STATUS			(1 << 10)
#घोषणा GUC_CT_MSG_ACTION_SHIFT			16
#घोषणा GUC_CT_MSG_ACTION_MASK			0xFFFF

#घोषणा GUC_FORCEWAKE_RENDER	(1 << 0)
#घोषणा GUC_FORCEWAKE_MEDIA	(1 << 1)

#घोषणा GUC_POWER_UNSPECIFIED	0
#घोषणा GUC_POWER_D0		1
#घोषणा GUC_POWER_D1		2
#घोषणा GUC_POWER_D2		3
#घोषणा GUC_POWER_D3		4

/* Scheduling policy settings */

/* Reset engine upon preempt failure */
#घोषणा POLICY_RESET_ENGINE		(1<<0)
/* Preempt to idle on quantum expiry */
#घोषणा POLICY_PREEMPT_TO_IDLE		(1<<1)

#घोषणा POLICY_MAX_NUM_WI 15
#घोषणा POLICY_DEFAULT_DPC_PROMOTE_TIME_US 500000
#घोषणा POLICY_DEFAULT_EXECUTION_QUANTUM_US 1000000
#घोषणा POLICY_DEFAULT_PREEMPTION_TIME_US 500000
#घोषणा POLICY_DEFAULT_FAULT_TIME_US 250000

काष्ठा guc_policy अणु
	/* Time क्रम one workload to execute. (in micro seconds) */
	u32 execution_quantum;
	/* Time to रुको क्रम a preemption request to completed beक्रमe issuing a
	 * reset. (in micro seconds). */
	u32 preemption_समय;
	/* How much समय to allow to run after the first fault is observed.
	 * Then preempt afterwards. (in micro seconds) */
	u32 fault_समय;
	u32 policy_flags;
	u32 reserved[8];
पूर्ण __packed;

काष्ठा guc_policies अणु
	काष्ठा guc_policy policy[GUC_CLIENT_PRIORITY_NUM][GUC_MAX_ENGINE_CLASSES];
	u32 submission_queue_depth[GUC_MAX_ENGINE_CLASSES];
	/* In micro seconds. How much समय to allow beक्रमe DPC processing is
	 * called back via पूर्णांकerrupt (to prevent DPC queue drain starving).
	 * Typically 1000s of micro seconds (example only, not granularity). */
	u32 dpc_promote_समय;

	/* Must be set to take these new values. */
	u32 is_valid;

	/* Max number of WIs to process per call. A large value may keep CS
	 * idle. */
	u32 max_num_work_items;

	u32 reserved[4];
पूर्ण __packed;

/* GuC MMIO reg state काष्ठा */
काष्ठा guc_mmio_reg अणु
	u32 offset;
	u32 value;
	u32 flags;
#घोषणा GUC_REGSET_MASKED		(1 << 0)
पूर्ण __packed;

/* GuC रेजिस्टर sets */
काष्ठा guc_mmio_reg_set अणु
	u32 address;
	u16 count;
	u16 reserved;
पूर्ण __packed;

/* HW info */
काष्ठा guc_gt_प्रणाली_info अणु
	u8 mapping_table[GUC_MAX_ENGINE_CLASSES][GUC_MAX_INSTANCES_PER_CLASS];
	u32 engine_enabled_masks[GUC_MAX_ENGINE_CLASSES];
	u32 generic_gt_sysinfo[GUC_GENERIC_GT_SYSINFO_MAX];
पूर्ण __packed;

/* Clients info */
काष्ठा guc_ct_pool_entry अणु
	काष्ठा guc_ct_buffer_desc desc;
	u32 reserved[7];
पूर्ण __packed;

#घोषणा GUC_CT_POOL_SIZE	2

काष्ठा guc_clients_info अणु
	u32 clients_num;
	u32 reserved0[13];
	u32 ct_pool_addr;
	u32 ct_pool_count;
	u32 reserved[4];
पूर्ण __packed;

/* GuC Additional Data Struct */
काष्ठा guc_ads अणु
	काष्ठा guc_mmio_reg_set reg_state_list[GUC_MAX_ENGINE_CLASSES][GUC_MAX_INSTANCES_PER_CLASS];
	u32 reserved0;
	u32 scheduler_policies;
	u32 gt_प्रणाली_info;
	u32 clients_info;
	u32 control_data;
	u32 golden_context_lrca[GUC_MAX_ENGINE_CLASSES];
	u32 eng_state_size[GUC_MAX_ENGINE_CLASSES];
	u32 निजी_data;
	u32 reserved[15];
पूर्ण __packed;

/* GuC logging काष्ठाures */

क्रमागत guc_log_buffer_type अणु
	GUC_ISR_LOG_BUFFER,
	GUC_DPC_LOG_BUFFER,
	GUC_CRASH_DUMP_LOG_BUFFER,
	GUC_MAX_LOG_BUFFER
पूर्ण;

/**
 * काष्ठा guc_log_buffer_state - GuC log buffer state
 *
 * Below state काष्ठाure is used क्रम coordination of retrieval of GuC firmware
 * logs. Separate state is मुख्यtained क्रम each log buffer type.
 * पढ़ो_ptr poपूर्णांकs to the location where i915 पढ़ो last in log buffer and
 * is पढ़ो only क्रम GuC firmware. ग_लिखो_ptr is incremented by GuC with number
 * of bytes written क्रम each log entry and is पढ़ो only क्रम i915.
 * When any type of log buffer becomes half full, GuC sends a flush पूर्णांकerrupt.
 * GuC firmware expects that जबतक it is writing to 2nd half of the buffer,
 * first half would get consumed by Host and then get a flush completed
 * acknowledgment from Host, so that it करोes not end up करोing any overग_लिखो
 * causing loss of logs. So when buffer माला_लो half filled & i915 has requested
 * क्रम पूर्णांकerrupt, GuC will set flush_to_file field, set the sampled_ग_लिखो_ptr
 * to the value of ग_लिखो_ptr and उठाओ the पूर्णांकerrupt.
 * On receiving the पूर्णांकerrupt i915 should पढ़ो the buffer, clear flush_to_file
 * field and also update पढ़ो_ptr with the value of sample_ग_लिखो_ptr, beक्रमe
 * sending an acknowledgment to GuC. marker & version fields are क्रम पूर्णांकernal
 * usage of GuC and opaque to i915. buffer_full_cnt field is incremented every
 * समय GuC detects the log buffer overflow.
 */
काष्ठा guc_log_buffer_state अणु
	u32 marker[2];
	u32 पढ़ो_ptr;
	u32 ग_लिखो_ptr;
	u32 size;
	u32 sampled_ग_लिखो_ptr;
	जोड़ अणु
		काष्ठा अणु
			u32 flush_to_file:1;
			u32 buffer_full_cnt:4;
			u32 reserved:27;
		पूर्ण;
		u32 flags;
	पूर्ण;
	u32 version;
पूर्ण __packed;

काष्ठा guc_ctx_report अणु
	u32 report_वापस_status;
	u32 reserved1[64];
	u32 affected_count;
	u32 reserved2[2];
पूर्ण __packed;

/* GuC Shared Context Data Struct */
काष्ठा guc_shared_ctx_data अणु
	u32 addr_of_last_preempted_data_low;
	u32 addr_of_last_preempted_data_high;
	u32 addr_of_last_preempted_data_high_पंचांगp;
	u32 padding;
	u32 is_mapped_to_proxy;
	u32 proxy_ctx_id;
	u32 engine_reset_ctx_id;
	u32 media_reset_count;
	u32 reserved1[8];
	u32 uk_last_ctx_चयन_reason;
	u32 was_reset;
	u32 lrca_gpu_addr;
	u64 execlist_ctx;
	u32 reserved2[66];
	काष्ठा guc_ctx_report preempt_ctx_report[GUC_MAX_ENGINES_NUM];
पूर्ण __packed;

/**
 * DOC: MMIO based communication
 *
 * The MMIO based communication between Host and GuC uses software scratch
 * रेजिस्टरs, where first रेजिस्टर holds data treated as message header,
 * and other रेजिस्टरs are used to hold message payload.
 *
 * For Gen9+, GuC uses software scratch रेजिस्टरs 0xC180-0xC1B8,
 * but no H2G command takes more than 8 parameters and the GuC FW
 * itself uses an 8-element array to store the H2G message.
 *
 *      +-----------+---------+---------+---------+
 *      |  MMIO[0]  | MMIO[1] |   ...   | MMIO[n] |
 *      +-----------+---------+---------+---------+
 *      | header    |      optional payload       |
 *      +======+====+=========+=========+=========+
 *      | 31:28|type|         |         |         |
 *      +------+----+         |         |         |
 *      | 27:16|data|         |         |         |
 *      +------+----+         |         |         |
 *      |  15:0|code|         |         |         |
 *      +------+----+---------+---------+---------+
 *
 * The message header consists of:
 *
 * - **type**, indicates message type
 * - **code**, indicates message code, is specअगरic क्रम **type**
 * - **data**, indicates message data, optional, depends on **code**
 *
 * The following message **types** are supported:
 *
 * - **REQUEST**, indicates Host-to-GuC request, requested GuC action code
 *   must be priovided in **code** field. Optional action specअगरic parameters
 *   can be provided in reमुख्यing payload रेजिस्टरs or **data** field.
 *
 * - **RESPONSE**, indicates GuC-to-Host response from earlier GuC request,
 *   action response status will be provided in **code** field. Optional
 *   response data can be वापसed in reमुख्यing payload रेजिस्टरs or **data**
 *   field.
 */

#घोषणा GUC_MAX_MMIO_MSG_LEN		8

#घोषणा INTEL_GUC_MSG_TYPE_SHIFT	28
#घोषणा INTEL_GUC_MSG_TYPE_MASK		(0xF << INTEL_GUC_MSG_TYPE_SHIFT)
#घोषणा INTEL_GUC_MSG_DATA_SHIFT	16
#घोषणा INTEL_GUC_MSG_DATA_MASK		(0xFFF << INTEL_GUC_MSG_DATA_SHIFT)
#घोषणा INTEL_GUC_MSG_CODE_SHIFT	0
#घोषणा INTEL_GUC_MSG_CODE_MASK		(0xFFFF << INTEL_GUC_MSG_CODE_SHIFT)

#घोषणा __INTEL_GUC_MSG_GET(T, m) \
	(((m) & INTEL_GUC_MSG_ ## T ## _MASK) >> INTEL_GUC_MSG_ ## T ## _SHIFT)
#घोषणा INTEL_GUC_MSG_TO_TYPE(m)	__INTEL_GUC_MSG_GET(TYPE, m)
#घोषणा INTEL_GUC_MSG_TO_DATA(m)	__INTEL_GUC_MSG_GET(DATA, m)
#घोषणा INTEL_GUC_MSG_TO_CODE(m)	__INTEL_GUC_MSG_GET(CODE, m)

क्रमागत पूर्णांकel_guc_msg_type अणु
	INTEL_GUC_MSG_TYPE_REQUEST = 0x0,
	INTEL_GUC_MSG_TYPE_RESPONSE = 0xF,
पूर्ण;

#घोषणा __INTEL_GUC_MSG_TYPE_IS(T, m) \
	(INTEL_GUC_MSG_TO_TYPE(m) == INTEL_GUC_MSG_TYPE_ ## T)
#घोषणा INTEL_GUC_MSG_IS_REQUEST(m)	__INTEL_GUC_MSG_TYPE_IS(REQUEST, m)
#घोषणा INTEL_GUC_MSG_IS_RESPONSE(m)	__INTEL_GUC_MSG_TYPE_IS(RESPONSE, m)

क्रमागत पूर्णांकel_guc_action अणु
	INTEL_GUC_ACTION_DEFAULT = 0x0,
	INTEL_GUC_ACTION_REQUEST_PREEMPTION = 0x2,
	INTEL_GUC_ACTION_REQUEST_ENGINE_RESET = 0x3,
	INTEL_GUC_ACTION_ALLOCATE_DOORBELL = 0x10,
	INTEL_GUC_ACTION_DEALLOCATE_DOORBELL = 0x20,
	INTEL_GUC_ACTION_LOG_BUFFER_खाता_FLUSH_COMPLETE = 0x30,
	INTEL_GUC_ACTION_UK_LOG_ENABLE_LOGGING = 0x40,
	INTEL_GUC_ACTION_FORCE_LOG_BUFFER_FLUSH = 0x302,
	INTEL_GUC_ACTION_ENTER_S_STATE = 0x501,
	INTEL_GUC_ACTION_EXIT_S_STATE = 0x502,
	INTEL_GUC_ACTION_SLPC_REQUEST = 0x3003,
	INTEL_GUC_ACTION_SAMPLE_FORCEWAKE = 0x3005,
	INTEL_GUC_ACTION_AUTHENTICATE_HUC = 0x4000,
	INTEL_GUC_ACTION_REGISTER_COMMAND_TRANSPORT_BUFFER = 0x4505,
	INTEL_GUC_ACTION_DEREGISTER_COMMAND_TRANSPORT_BUFFER = 0x4506,
	INTEL_GUC_ACTION_LIMIT
पूर्ण;

क्रमागत पूर्णांकel_guc_preempt_options अणु
	INTEL_GUC_PREEMPT_OPTION_DROP_WORK_Q = 0x4,
	INTEL_GUC_PREEMPT_OPTION_DROP_SUBMIT_Q = 0x8,
पूर्ण;

क्रमागत पूर्णांकel_guc_report_status अणु
	INTEL_GUC_REPORT_STATUS_UNKNOWN = 0x0,
	INTEL_GUC_REPORT_STATUS_ACKED = 0x1,
	INTEL_GUC_REPORT_STATUS_ERROR = 0x2,
	INTEL_GUC_REPORT_STATUS_COMPLETE = 0x4,
पूर्ण;

क्रमागत पूर्णांकel_guc_sleep_state_status अणु
	INTEL_GUC_SLEEP_STATE_SUCCESS = 0x1,
	INTEL_GUC_SLEEP_STATE_PREEMPT_TO_IDLE_FAILED = 0x2,
	INTEL_GUC_SLEEP_STATE_ENGINE_RESET_FAILED = 0x3
#घोषणा INTEL_GUC_SLEEP_STATE_INVALID_MASK 0x80000000
पूर्ण;

#घोषणा GUC_LOG_CONTROL_LOGGING_ENABLED	(1 << 0)
#घोषणा GUC_LOG_CONTROL_VERBOSITY_SHIFT	4
#घोषणा GUC_LOG_CONTROL_VERBOSITY_MASK	(0xF << GUC_LOG_CONTROL_VERBOSITY_SHIFT)
#घोषणा GUC_LOG_CONTROL_DEFAULT_LOGGING	(1 << 8)

क्रमागत पूर्णांकel_guc_response_status अणु
	INTEL_GUC_RESPONSE_STATUS_SUCCESS = 0x0,
	INTEL_GUC_RESPONSE_STATUS_GENERIC_FAIL = 0xF000,
पूर्ण;

#घोषणा INTEL_GUC_MSG_IS_RESPONSE_SUCCESS(m) \
	 (typecheck(u32, (m)) && \
	  ((m) & (INTEL_GUC_MSG_TYPE_MASK | INTEL_GUC_MSG_CODE_MASK)) == \
	  ((INTEL_GUC_MSG_TYPE_RESPONSE << INTEL_GUC_MSG_TYPE_SHIFT) | \
	   (INTEL_GUC_RESPONSE_STATUS_SUCCESS << INTEL_GUC_MSG_CODE_SHIFT)))

/* This action will be programmed in C1BC - SOFT_SCRATCH_15_REG */
क्रमागत पूर्णांकel_guc_recv_message अणु
	INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED = BIT(1),
	INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER = BIT(3)
पूर्ण;

#पूर्ण_अगर

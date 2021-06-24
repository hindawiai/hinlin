<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __MES_API_DEF_H__
#घोषणा __MES_API_DEF_H__

#आशय pack(push, 4)

#घोषणा MES_API_VERSION 1

/* Driver submits one API(cmd) as a single Frame and this command size is same
 * क्रम all API to ease the debugging and parsing of ring buffer.
 */
क्रमागत अणु API_FRAME_SIZE_IN_DWORDS = 64 पूर्ण;

/* To aव्योम command in scheduler context to be overwritten whenenver mutilple
 * पूर्णांकerrupts come in, this creates another queue.
 */
क्रमागत अणु API_NUMBER_OF_COMMAND_MAX = 32 पूर्ण;

क्रमागत MES_API_TYPE अणु
	MES_API_TYPE_SCHEDULER = 1,
	MES_API_TYPE_MAX
पूर्ण;

क्रमागत MES_SCH_API_OPCODE अणु
	MES_SCH_API_SET_HW_RSRC			= 0,
	MES_SCH_API_SET_SCHEDULING_CONFIG	= 1, /* agreegated db, quantums, etc */
	MES_SCH_API_ADD_QUEUE			= 2,
	MES_SCH_API_REMOVE_QUEUE		= 3,
	MES_SCH_API_PERFORM_YIELD		= 4,
	MES_SCH_API_SET_GANG_PRIORITY_LEVEL	= 5,
	MES_SCH_API_SUSPEND			= 6,
	MES_SCH_API_RESUME			= 7,
	MES_SCH_API_RESET			= 8,
	MES_SCH_API_SET_LOG_BUFFER		= 9,
	MES_SCH_API_CHANGE_GANG_PRORITY		= 10,
	MES_SCH_API_QUERY_SCHEDULER_STATUS	= 11,
	MES_SCH_API_PROGRAM_GDS			= 12,
	MES_SCH_API_SET_DEBUG_VMID		= 13,
	MES_SCH_API_MISC			= 14,
	MES_SCH_API_MAX				= 0xFF
पूर्ण;

जोड़ MES_API_HEADER अणु
	काष्ठा अणु
		uपूर्णांक32_t type		: 4; /* 0 - Invalid; 1 - Scheduling; 2 - TBD */
		uपूर्णांक32_t opcode		: 8;
		uपूर्णांक32_t dwsize		: 8; /* including header */
		uपूर्णांक32_t reserved	: 12;
	पूर्ण;

	uपूर्णांक32_t	u32All;
पूर्ण;

क्रमागत MES_AMD_PRIORITY_LEVEL अणु
	AMD_PRIORITY_LEVEL_LOW		= 0,
	AMD_PRIORITY_LEVEL_NORMAL	= 1,
	AMD_PRIORITY_LEVEL_MEDIUM	= 2,
	AMD_PRIORITY_LEVEL_HIGH		= 3,
	AMD_PRIORITY_LEVEL_REALTIME	= 4,
	AMD_PRIORITY_NUM_LEVELS
पूर्ण;

क्रमागत MES_QUEUE_TYPE अणु
	MES_QUEUE_TYPE_GFX,
	MES_QUEUE_TYPE_COMPUTE,
	MES_QUEUE_TYPE_SDMA,
	MES_QUEUE_TYPE_MAX,
पूर्ण;

काष्ठा MES_API_STATUS अणु
	uपूर्णांक64_t	api_completion_fence_addr;
	uपूर्णांक64_t	api_completion_fence_value;
पूर्ण;

क्रमागत अणु MAX_COMPUTE_PIPES = 8 पूर्ण;
क्रमागत अणु MAX_GFX_PIPES = 2 पूर्ण;
क्रमागत अणु MAX_SDMA_PIPES = 2 पूर्ण;

क्रमागत अणु MAX_COMPUTE_HQD_PER_PIPE = 8 पूर्ण;
क्रमागत अणु MAX_GFX_HQD_PER_PIPE = 8 पूर्ण;
क्रमागत अणु MAX_SDMA_HQD_PER_PIPE = 10 पूर्ण;

क्रमागत अणु MAX_QUEUES_IN_A_GANG = 8 पूर्ण;

क्रमागत VM_HUB_TYPE अणु
	VM_HUB_TYPE_GC = 0,
	VM_HUB_TYPE_MM = 1,
	VM_HUB_TYPE_MAX,
पूर्ण;

क्रमागत अणु VMID_INVALID = 0xffff पूर्ण;

क्रमागत अणु MAX_VMID_GCHUB = 16 पूर्ण;
क्रमागत अणु MAX_VMID_MMHUB = 16 पूर्ण;

क्रमागत MES_LOG_OPERATION अणु
	MES_LOG_OPERATION_CONTEXT_STATE_CHANGE = 0
पूर्ण;

क्रमागत MES_LOG_CONTEXT_STATE अणु
	MES_LOG_CONTEXT_STATE_IDLE		= 0,
	MES_LOG_CONTEXT_STATE_RUNNING		= 1,
	MES_LOG_CONTEXT_STATE_READY		= 2,
	MES_LOG_CONTEXT_STATE_READY_STANDBY	= 3,
पूर्ण;

काष्ठा MES_LOG_CONTEXT_STATE_CHANGE अणु
	व्योम				*h_context;
	क्रमागत MES_LOG_CONTEXT_STATE	new_context_state;
पूर्ण;

काष्ठा MES_LOG_ENTRY_HEADER अणु
	uपूर्णांक32_t	first_मुक्त_entry_index;
	uपूर्णांक32_t	wraparound_count;
	uपूर्णांक64_t	number_of_entries;
	uपूर्णांक64_t	reserved[2];
पूर्ण;

काष्ठा MES_LOG_ENTRY_DATA अणु
	uपूर्णांक64_t	gpu_समय_stamp;
	uपूर्णांक32_t	operation_type; /* operation_type is of MES_LOG_OPERATION type */
	uपूर्णांक32_t	reserved_operation_type_bits;
	जोड़ अणु
		काष्ठा MES_LOG_CONTEXT_STATE_CHANGE	context_state_change;
		uपूर्णांक64_t				reserved_operation_data[2];
	पूर्ण;
पूर्ण;

काष्ठा MES_LOG_BUFFER अणु
	काष्ठा MES_LOG_ENTRY_HEADER	header;
	काष्ठा MES_LOG_ENTRY_DATA	entries[1];
पूर्ण;

जोड़ MESAPI_SET_HW_RESOURCES अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		uपूर्णांक32_t		vmid_mask_mmhub;
		uपूर्णांक32_t		vmid_mask_gfxhub;
		uपूर्णांक32_t		gds_size;
		uपूर्णांक32_t		paging_vmid;
		uपूर्णांक32_t		compute_hqd_mask[MAX_COMPUTE_PIPES];
		uपूर्णांक32_t		gfx_hqd_mask[MAX_GFX_PIPES];
		uपूर्णांक32_t		sdma_hqd_mask[MAX_SDMA_PIPES];
		uपूर्णांक32_t		agreegated_करोorbells[AMD_PRIORITY_NUM_LEVELS];
		uपूर्णांक64_t		g_sch_ctx_gpu_mc_ptr;
		uपूर्णांक64_t		query_status_fence_gpu_mc_ptr;
		काष्ठा MES_API_STATUS	api_status;
		जोड़ अणु
			काष्ठा अणु
				uपूर्णांक32_t disable_reset	: 1;
				uपूर्णांक32_t reserved	: 31;
			पूर्ण;
			uपूर्णांक32_t	uपूर्णांक32_t_all;
		पूर्ण;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__ADD_QUEUE अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER		header;
		uपूर्णांक32_t			process_id;
		uपूर्णांक64_t			page_table_base_addr;
		uपूर्णांक64_t			process_बहु_शुरू;
		uपूर्णांक64_t			process_बहु_पूर्ण;
		uपूर्णांक64_t			process_quantum;
		uपूर्णांक64_t			process_context_addr;
		uपूर्णांक64_t			gang_quantum;
		uपूर्णांक64_t			gang_context_addr;
		uपूर्णांक32_t			inprocess_gang_priority;
		क्रमागत MES_AMD_PRIORITY_LEVEL	gang_global_priority_level;
		uपूर्णांक32_t			करोorbell_offset;
		uपूर्णांक64_t			mqd_addr;
		uपूर्णांक64_t			wptr_addr;
		क्रमागत MES_QUEUE_TYPE		queue_type;
		uपूर्णांक32_t			gds_base;
		uपूर्णांक32_t			gds_size;
		uपूर्णांक32_t			gws_base;
		uपूर्णांक32_t			gws_size;
		uपूर्णांक32_t			oa_mask;

		काष्ठा अणु
			uपूर्णांक32_t paging			: 1;
			uपूर्णांक32_t debug_vmid		: 4;
			uपूर्णांक32_t program_gds		: 1;
			uपूर्णांक32_t is_gang_suspended	: 1;
			uपूर्णांक32_t is_पंचांगz_queue		: 1;
			uपूर्णांक32_t reserved		: 24;
		पूर्ण;
		काष्ठा MES_API_STATUS		api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__REMOVE_QUEUE अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		uपूर्णांक32_t		करोorbell_offset;
		uपूर्णांक64_t		gang_context_addr;

		काष्ठा अणु
			uपूर्णांक32_t unmap_legacy_gfx_queue	: 1;
			uपूर्णांक32_t reserved		: 31;
		पूर्ण;
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__SET_SCHEDULING_CONFIG अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		/* Grace period when preempting another priority band क्रम this
		 * priority band. The value क्रम idle priority band is ignored,
		 * as it never preempts other bands.
		 */
		uपूर्णांक64_t		grace_period_other_levels[AMD_PRIORITY_NUM_LEVELS];
		/* Default quantum क्रम scheduling across processes within
		 * a priority band.
		 */
		uपूर्णांक64_t		process_quantum_क्रम_level[AMD_PRIORITY_NUM_LEVELS];
		/* Default grace period क्रम processes that preempt each other
		 * within a priority band.
		 */
		uपूर्णांक64_t		process_grace_period_same_level[AMD_PRIORITY_NUM_LEVELS];
		/* For normal level this field specअगरies the target GPU
		 * percentage in situations when it's starved by the high level.
		 * Valid values are between 0 and 50, with the शेष being 10.
		 */
		uपूर्णांक32_t		normal_yield_percent;
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__PERFORM_YIELD अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		uपूर्णांक32_t		dummy;
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__CHANGE_GANG_PRIORITY_LEVEL अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER		header;
		uपूर्णांक32_t			inprocess_gang_priority;
		क्रमागत MES_AMD_PRIORITY_LEVEL	gang_global_priority_level;
		uपूर्णांक64_t			gang_quantum;
		uपूर्णांक64_t			gang_context_addr;
		काष्ठा MES_API_STATUS		api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__SUSPEND अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		/* false - suspend all gangs; true - specअगरic gang */
		काष्ठा अणु
			uपूर्णांक32_t suspend_all_gangs	: 1;
			uपूर्णांक32_t reserved		: 31;
		पूर्ण;
		/* gang_context_addr is valid only अगर suspend_all = false */
		uपूर्णांक64_t		gang_context_addr;

		uपूर्णांक64_t		suspend_fence_addr;
		uपूर्णांक32_t		suspend_fence_value;

		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__RESUME अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		/* false - resume all gangs; true - specअगरied gang */
		काष्ठा अणु
			uपूर्णांक32_t resume_all_gangs	: 1;
			uपूर्णांक32_t reserved		: 31;
		पूर्ण;
		/* valid only अगर resume_all_gangs = false */
		uपूर्णांक64_t		gang_context_addr;

		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__RESET अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;

		काष्ठा अणु
			uपूर्णांक32_t reset_queue	: 1;
			uपूर्णांक32_t reserved	: 31;
		पूर्ण;

		uपूर्णांक64_t		gang_context_addr;
		uपूर्णांक32_t		करोorbell_offset; /* valid only अगर reset_queue = true */
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__SET_LOGGING_BUFFER अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		/* There are separate log buffers क्रम each queue type */
		क्रमागत MES_QUEUE_TYPE	log_type;
		/* Log buffer GPU Address */
		uपूर्णांक64_t		logging_buffer_addr;
		/* number of entries in the log buffer */
		uपूर्णांक32_t		number_of_entries;
		/* Entry index at which CPU पूर्णांकerrupt needs to be संकेतled */
		uपूर्णांक32_t		पूर्णांकerrupt_entry;

		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__QUERY_MES_STATUS अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		bool			mes_healthy; /* 0 - not healthy, 1 - healthy */
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__PROGRAM_GDS अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		uपूर्णांक64_t		process_context_addr;
		uपूर्णांक32_t		gds_base;
		uपूर्णांक32_t		gds_size;
		uपूर्णांक32_t		gws_base;
		uपूर्णांक32_t		gws_size;
		uपूर्णांक32_t		oa_mask;
		काष्ठा MES_API_STATUS	api_status;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

जोड़ MESAPI__SET_DEBUG_VMID अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		काष्ठा MES_API_STATUS	api_status;
		जोड़ अणु
			काष्ठा अणु
				uपूर्णांक32_t use_gds	: 1;
				uपूर्णांक32_t reserved	: 31;
			पूर्ण flags;
			uपूर्णांक32_t	u32All;
		पूर्ण;
		uपूर्णांक32_t		reserved;
		uपूर्णांक32_t		debug_vmid;
		uपूर्णांक64_t		process_context_addr;
		uपूर्णांक64_t		page_table_base_addr;
		uपूर्णांक64_t		process_बहु_शुरू;
		uपूर्णांक64_t		process_बहु_पूर्ण;
		uपूर्णांक32_t		gds_base;
		uपूर्णांक32_t		gds_size;
		uपूर्णांक32_t		gws_base;
		uपूर्णांक32_t		gws_size;
		uपूर्णांक32_t		oa_mask;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

क्रमागत MESAPI_MISC_OPCODE अणु
	MESAPI_MISC__MODIFY_REG,
	MESAPI_MISC__MAX,
पूर्ण;

क्रमागत MODIFY_REG_SUBCODE अणु
	MODIFY_REG__OVERWRITE,
	MODIFY_REG__RMW_OR,
	MODIFY_REG__RMW_AND,
	MODIFY_REG__MAX,
पूर्ण;

क्रमागत अणु MISC_DATA_MAX_SIZE_IN_DWORDS = 20 पूर्ण;

जोड़ MESAPI__MISC अणु
	काष्ठा अणु
		जोड़ MES_API_HEADER	header;
		क्रमागत MESAPI_MISC_OPCODE	opcode;
		काष्ठा MES_API_STATUS	api_status;

		जोड़ अणु
			काष्ठा अणु
				क्रमागत MODIFY_REG_SUBCODE	subcode;
				uपूर्णांक32_t		reg_offset;
				uपूर्णांक32_t		reg_value;
			पूर्ण modअगरy_reg;
			uपूर्णांक32_t	data[MISC_DATA_MAX_SIZE_IN_DWORDS];
		पूर्ण;
	पूर्ण;

	uपूर्णांक32_t	max_dwords_in_api[API_FRAME_SIZE_IN_DWORDS];
पूर्ण;

#आशय pack(pop)
#पूर्ण_अगर

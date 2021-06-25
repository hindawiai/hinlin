<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित F32_MES_PM4_PACKETS_H
#घोषणा F32_MES_PM4_PACKETS_H

#अगर_अघोषित PM4_MES_HEADER_DEFINED
#घोषणा PM4_MES_HEADER_DEFINED
जोड़ PM4_MES_TYPE_3_HEADER अणु
	काष्ठा अणु
		uपूर्णांक32_t reserved1 : 8; /* < reserved */
		uपूर्णांक32_t opcode    : 8; /* < IT opcode */
		uपूर्णांक32_t count     : 14;/* < number of DWORDs - 1 in the
					 *   inक्रमmation body.
					 */
		uपूर्णांक32_t type      : 2; /* < packet identअगरier.
					 *   It should be 3 क्रम type 3 packets
					 */
	पूर्ण;
	uपूर्णांक32_t u32All;
पूर्ण;
#पूर्ण_अगर /* PM4_MES_HEADER_DEFINED */

/*--------------------MES_SET_RESOURCES--------------------*/

#अगर_अघोषित PM4_MES_SET_RESOURCES_DEFINED
#घोषणा PM4_MES_SET_RESOURCES_DEFINED
क्रमागत mes_set_resources_queue_type_क्रमागत अणु
	queue_type__mes_set_resources__kernel_पूर्णांकerface_queue_kiq = 0,
	queue_type__mes_set_resources__hsa_पूर्णांकerface_queue_hiq = 1,
	queue_type__mes_set_resources__hsa_debug_पूर्णांकerface_queue = 4
पूर्ण;


काष्ठा pm4_mes_set_resources अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER	header;		/* header */
		uपूर्णांक32_t			ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t vmid_mask:16;
			uपूर्णांक32_t unmap_latency:8;
			uपूर्णांक32_t reserved1:5;
			क्रमागत mes_set_resources_queue_type_क्रमागत queue_type:3;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	uपूर्णांक32_t queue_mask_lo;
	uपूर्णांक32_t queue_mask_hi;
	uपूर्णांक32_t gws_mask_lo;
	uपूर्णांक32_t gws_mask_hi;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t oac_mask:16;
			uपूर्णांक32_t reserved2:16;
		पूर्ण bitfields7;
		uपूर्णांक32_t ordinal7;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
		uपूर्णांक32_t gds_heap_base:10;
		uपूर्णांक32_t reserved3:1;
		uपूर्णांक32_t gds_heap_size:10;
		uपूर्णांक32_t reserved4:11;
		पूर्ण bitfields8;
		uपूर्णांक32_t ordinal8;
	पूर्ण;

पूर्ण;
#पूर्ण_अगर

/*--------------------MES_RUN_LIST--------------------*/

#अगर_अघोषित PM4_MES_RUN_LIST_DEFINED
#घोषणा PM4_MES_RUN_LIST_DEFINED

काष्ठा pm4_mes_runlist अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header; /* header */
		uपूर्णांक32_t ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved1:2;
			uपूर्णांक32_t ib_base_lo:30;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	uपूर्णांक32_t ib_base_hi;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t ib_size:20;
			uपूर्णांक32_t chain:1;
			uपूर्णांक32_t offload_polling:1;
			uपूर्णांक32_t chained_runlist_idle_disable:1;
			uपूर्णांक32_t valid:1;
			uपूर्णांक32_t process_cnt:4;
			uपूर्णांक32_t reserved3:4;
		पूर्ण bitfields4;
		uपूर्णांक32_t ordinal4;
	पूर्ण;

पूर्ण;
#पूर्ण_अगर

/*--------------------MES_MAP_PROCESS--------------------*/

#अगर_अघोषित PM4_MES_MAP_PROCESS_DEFINED
#घोषणा PM4_MES_MAP_PROCESS_DEFINED

काष्ठा pm4_mes_map_process अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/* header */
		uपूर्णांक32_t ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t pasid:16;
			uपूर्णांक32_t reserved1:8;
			uपूर्णांक32_t diq_enable:1;
			uपूर्णांक32_t process_quantum:7;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	uपूर्णांक32_t vm_context_page_table_base_addr_lo32;

	uपूर्णांक32_t vm_context_page_table_base_addr_hi32;

	uपूर्णांक32_t sh_mem_bases;

	uपूर्णांक32_t sh_mem_config;

	uपूर्णांक32_t sq_shader_tba_lo;

	uपूर्णांक32_t sq_shader_tba_hi;

	uपूर्णांक32_t sq_shader_पंचांगa_lo;

	uपूर्णांक32_t sq_shader_पंचांगa_hi;

	uपूर्णांक32_t reserved6;

	uपूर्णांक32_t gds_addr_lo;

	uपूर्णांक32_t gds_addr_hi;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t num_gws:7;
			uपूर्णांक32_t sdma_enable:1;
			uपूर्णांक32_t num_oac:4;
			uपूर्णांक32_t gds_size_hi:4;
			uपूर्णांक32_t gds_size:6;
			uपूर्णांक32_t num_queues:10;
		पूर्ण bitfields14;
		uपूर्णांक32_t ordinal14;
	पूर्ण;

	uपूर्णांक32_t completion_संकेत_lo;

	uपूर्णांक32_t completion_संकेत_hi;

पूर्ण;

#पूर्ण_अगर

/*--------------------MES_MAP_PROCESS_VM--------------------*/

#अगर_अघोषित PM4_MES_MAP_PROCESS_VM_DEFINED
#घोषणा PM4_MES_MAP_PROCESS_VM_DEFINED

काष्ठा PM4_MES_MAP_PROCESS_VM अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;	/* header */
		uपूर्णांक32_t ordinal1;
	पूर्ण;

	uपूर्णांक32_t reserved1;

	uपूर्णांक32_t vm_context_cntl;

	uपूर्णांक32_t reserved2;

	uपूर्णांक32_t vm_context_page_table_end_addr_lo32;

	uपूर्णांक32_t vm_context_page_table_end_addr_hi32;

	uपूर्णांक32_t vm_context_page_table_start_addr_lo32;

	uपूर्णांक32_t vm_context_page_table_start_addr_hi32;

	uपूर्णांक32_t reserved3;

	uपूर्णांक32_t reserved4;

	uपूर्णांक32_t reserved5;

	uपूर्णांक32_t reserved6;

	uपूर्णांक32_t reserved7;

	uपूर्णांक32_t reserved8;

	uपूर्णांक32_t completion_संकेत_lo32;

	uपूर्णांक32_t completion_संकेत_hi32;

पूर्ण;
#पूर्ण_अगर

/*--------------------MES_MAP_QUEUES--------------------*/

#अगर_अघोषित PM4_MES_MAP_QUEUES_VI_DEFINED
#घोषणा PM4_MES_MAP_QUEUES_VI_DEFINED
क्रमागत mes_map_queues_queue_sel_क्रमागत अणु
	queue_sel__mes_map_queues__map_to_specअगरied_queue_slots_vi = 0,
queue_sel__mes_map_queues__map_to_hws_determined_queue_slots_vi = 1
पूर्ण;

क्रमागत mes_map_queues_queue_type_क्रमागत अणु
	queue_type__mes_map_queues__normal_compute_vi = 0,
	queue_type__mes_map_queues__debug_पूर्णांकerface_queue_vi = 1,
	queue_type__mes_map_queues__normal_latency_अटल_queue_vi = 2,
queue_type__mes_map_queues__low_latency_अटल_queue_vi = 3
पूर्ण;

क्रमागत mes_map_queues_engine_sel_क्रमागत अणु
	engine_sel__mes_map_queues__compute_vi = 0,
	engine_sel__mes_map_queues__sdma0_vi = 2,
	engine_sel__mes_map_queues__sdma1_vi = 3
पूर्ण;

क्रमागत mes_map_queues_extended_engine_sel_क्रमागत अणु
	extended_engine_sel__mes_map_queues__legacy_engine_sel = 0,
	extended_engine_sel__mes_map_queues__sdma0_to_7_sel = 1
पूर्ण;

काष्ठा pm4_mes_map_queues अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER   header;            /* header */
		uपूर्णांक32_t            ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved1:2;
			क्रमागत mes_map_queues_extended_engine_sel_क्रमागत extended_engine_sel:2;
			क्रमागत mes_map_queues_queue_sel_क्रमागत queue_sel:2;
			uपूर्णांक32_t reserved5:6;
			uपूर्णांक32_t gws_control_queue:1;
			uपूर्णांक32_t reserved2:8;
			क्रमागत mes_map_queues_queue_type_क्रमागत queue_type:3;
			uपूर्णांक32_t reserved3:2;
			क्रमागत mes_map_queues_engine_sel_क्रमागत engine_sel:3;
			uपूर्णांक32_t num_queues:3;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved3:1;
			uपूर्णांक32_t check_disable:1;
			uपूर्णांक32_t करोorbell_offset:26;
			uपूर्णांक32_t reserved4:4;
		पूर्ण bitfields3;
		uपूर्णांक32_t ordinal3;
	पूर्ण;

	uपूर्णांक32_t mqd_addr_lo;
	uपूर्णांक32_t mqd_addr_hi;
	uपूर्णांक32_t wptr_addr_lo;
	uपूर्णांक32_t wptr_addr_hi;
पूर्ण;
#पूर्ण_अगर

/*--------------------MES_QUERY_STATUS--------------------*/

#अगर_अघोषित PM4_MES_QUERY_STATUS_DEFINED
#घोषणा PM4_MES_QUERY_STATUS_DEFINED
क्रमागत mes_query_status_पूर्णांकerrupt_sel_क्रमागत अणु
	पूर्णांकerrupt_sel__mes_query_status__completion_status = 0,
	पूर्णांकerrupt_sel__mes_query_status__process_status = 1,
	पूर्णांकerrupt_sel__mes_query_status__queue_status = 2
पूर्ण;

क्रमागत mes_query_status_command_क्रमागत अणु
	command__mes_query_status__पूर्णांकerrupt_only = 0,
	command__mes_query_status__fence_only_immediate = 1,
	command__mes_query_status__fence_only_after_ग_लिखो_ack = 2,
	command__mes_query_status__fence_रुको_क्रम_ग_लिखो_ack_send_पूर्णांकerrupt = 3
पूर्ण;

क्रमागत mes_query_status_engine_sel_क्रमागत अणु
	engine_sel__mes_query_status__compute = 0,
	engine_sel__mes_query_status__sdma0_queue = 2,
	engine_sel__mes_query_status__sdma1_queue = 3
पूर्ण;

काष्ठा pm4_mes_query_status अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER   header;            /* header */
		uपूर्णांक32_t            ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t context_id:28;
			क्रमागत mes_query_status_पूर्णांकerrupt_sel_क्रमागत	पूर्णांकerrupt_sel:2;
			क्रमागत mes_query_status_command_क्रमागत command:2;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t pasid:16;
			uपूर्णांक32_t reserved1:16;
		पूर्ण bitfields3a;
		काष्ठा अणु
			uपूर्णांक32_t reserved2:2;
			uपूर्णांक32_t करोorbell_offset:26;
			क्रमागत mes_query_status_engine_sel_क्रमागत engine_sel:3;
			uपूर्णांक32_t reserved3:1;
		पूर्ण bitfields3b;
		uपूर्णांक32_t ordinal3;
	पूर्ण;

	uपूर्णांक32_t addr_lo;
	uपूर्णांक32_t addr_hi;
	uपूर्णांक32_t data_lo;
	uपूर्णांक32_t data_hi;
पूर्ण;
#पूर्ण_अगर

/*--------------------MES_UNMAP_QUEUES--------------------*/

#अगर_अघोषित PM4_MES_UNMAP_QUEUES_DEFINED
#घोषणा PM4_MES_UNMAP_QUEUES_DEFINED
क्रमागत mes_unmap_queues_action_क्रमागत अणु
	action__mes_unmap_queues__preempt_queues = 0,
	action__mes_unmap_queues__reset_queues = 1,
	action__mes_unmap_queues__disable_process_queues = 2,
	action__mes_unmap_queues__reserved = 3
पूर्ण;

क्रमागत mes_unmap_queues_queue_sel_क्रमागत अणु
	queue_sel__mes_unmap_queues__perक्रमm_request_on_specअगरied_queues = 0,
	queue_sel__mes_unmap_queues__perक्रमm_request_on_pasid_queues = 1,
	queue_sel__mes_unmap_queues__unmap_all_queues = 2,
	queue_sel__mes_unmap_queues__unmap_all_non_अटल_queues = 3
पूर्ण;

क्रमागत mes_unmap_queues_engine_sel_क्रमागत अणु
	engine_sel__mes_unmap_queues__compute = 0,
	engine_sel__mes_unmap_queues__sdma0 = 2,
	engine_sel__mes_unmap_queues__sdmal = 3
पूर्ण;

क्रमागत mes_unmap_queues_extended_engine_sel_क्रमागत अणु
	extended_engine_sel__mes_unmap_queues__legacy_engine_sel = 0,
	extended_engine_sel__mes_unmap_queues__sdma0_to_7_sel = 1
पूर्ण;

काष्ठा pm4_mes_unmap_queues अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER   header;            /* header */
		uपूर्णांक32_t            ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			क्रमागत mes_unmap_queues_action_क्रमागत action:2;
			क्रमागत mes_unmap_queues_extended_engine_sel_क्रमागत extended_engine_sel:2;
			क्रमागत mes_unmap_queues_queue_sel_क्रमागत queue_sel:2;
			uपूर्णांक32_t reserved2:20;
			क्रमागत mes_unmap_queues_engine_sel_क्रमागत engine_sel:3;
			uपूर्णांक32_t num_queues:3;
		पूर्ण bitfields2;
		uपूर्णांक32_t ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t pasid:16;
			uपूर्णांक32_t reserved3:16;
		पूर्ण bitfields3a;
		काष्ठा अणु
			uपूर्णांक32_t reserved4:2;
			uपूर्णांक32_t करोorbell_offset0:26;
			पूर्णांक32_t reserved5:4;
		पूर्ण bitfields3b;
		uपूर्णांक32_t ordinal3;
	पूर्ण;

	जोड़ अणु
	काष्ठा अणु
			uपूर्णांक32_t reserved6:2;
			uपूर्णांक32_t करोorbell_offset1:26;
			uपूर्णांक32_t reserved7:4;
		पूर्ण bitfields4;
		uपूर्णांक32_t ordinal4;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved8:2;
			uपूर्णांक32_t करोorbell_offset2:26;
			uपूर्णांक32_t reserved9:4;
		पूर्ण bitfields5;
		uपूर्णांक32_t ordinal5;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved10:2;
			uपूर्णांक32_t करोorbell_offset3:26;
			uपूर्णांक32_t reserved11:4;
		पूर्ण bitfields6;
		uपूर्णांक32_t ordinal6;
	पूर्ण;
पूर्ण;
#पूर्ण_अगर

#अगर_अघोषित PM4_MEC_RELEASE_MEM_DEFINED
#घोषणा PM4_MEC_RELEASE_MEM_DEFINED

क्रमागत mec_release_mem_event_index_क्रमागत अणु
	event_index__mec_release_mem__end_of_pipe = 5,
	event_index__mec_release_mem__shader_करोne = 6
पूर्ण;

क्रमागत mec_release_mem_cache_policy_क्रमागत अणु
	cache_policy__mec_release_mem__lru = 0,
	cache_policy__mec_release_mem__stream = 1
पूर्ण;

क्रमागत mec_release_mem_pq_exe_status_क्रमागत अणु
	pq_exe_status__mec_release_mem__शेष = 0,
	pq_exe_status__mec_release_mem__phase_update = 1
पूर्ण;

क्रमागत mec_release_mem_dst_sel_क्रमागत अणु
	dst_sel__mec_release_mem__memory_controller = 0,
	dst_sel__mec_release_mem__tc_l2 = 1,
	dst_sel__mec_release_mem__queue_ग_लिखो_poपूर्णांकer_रेजिस्टर = 2,
	dst_sel__mec_release_mem__queue_ग_लिखो_poपूर्णांकer_poll_mask_bit = 3
पूर्ण;

क्रमागत mec_release_mem_पूर्णांक_sel_क्रमागत अणु
	पूर्णांक_sel__mec_release_mem__none = 0,
	पूर्णांक_sel__mec_release_mem__send_पूर्णांकerrupt_only = 1,
	पूर्णांक_sel__mec_release_mem__send_पूर्णांकerrupt_after_ग_लिखो_confirm = 2,
	पूर्णांक_sel__mec_release_mem__send_data_after_ग_लिखो_confirm = 3,
	पूर्णांक_sel__mec_release_mem__unconditionally_send_पूर्णांक_ctxid = 4,
	पूर्णांक_sel__mec_release_mem__conditionally_send_पूर्णांक_ctxid_based_on_32_bit_compare = 5,
	पूर्णांक_sel__mec_release_mem__conditionally_send_पूर्णांक_ctxid_based_on_64_bit_compare = 6
पूर्ण;

क्रमागत mec_release_mem_data_sel_क्रमागत अणु
	data_sel__mec_release_mem__none = 0,
	data_sel__mec_release_mem__send_32_bit_low = 1,
	data_sel__mec_release_mem__send_64_bit_data = 2,
	data_sel__mec_release_mem__send_gpu_घड़ी_counter = 3,
	data_sel__mec_release_mem__send_cp_perfcounter_hi_lo = 4,
	data_sel__mec_release_mem__store_gds_data_to_memory = 5
पूर्ण;

काष्ठा pm4_mec_release_mem अणु
	जोड़ अणु
		जोड़ PM4_MES_TYPE_3_HEADER header;     /*header */
		अचिन्हित पूर्णांक ordinal1;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक event_type:6;
			अचिन्हित पूर्णांक reserved1:2;
			क्रमागत mec_release_mem_event_index_क्रमागत event_index:4;
			अचिन्हित पूर्णांक tcl1_vol_action_ena:1;
			अचिन्हित पूर्णांक tc_vol_action_ena:1;
			अचिन्हित पूर्णांक reserved2:1;
			अचिन्हित पूर्णांक tc_wb_action_ena:1;
			अचिन्हित पूर्णांक tcl1_action_ena:1;
			अचिन्हित पूर्णांक tc_action_ena:1;
			uपूर्णांक32_t reserved3:1;
			uपूर्णांक32_t tc_nc_action_ena:1;
			uपूर्णांक32_t tc_wc_action_ena:1;
			uपूर्णांक32_t tc_md_action_ena:1;
			uपूर्णांक32_t reserved4:3;
			क्रमागत mec_release_mem_cache_policy_क्रमागत cache_policy:2;
			uपूर्णांक32_t reserved5:2;
			क्रमागत mec_release_mem_pq_exe_status_क्रमागत pq_exe_status:1;
			uपूर्णांक32_t reserved6:2;
		पूर्ण bitfields2;
		अचिन्हित पूर्णांक ordinal2;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved7:16;
			क्रमागत mec_release_mem_dst_sel_क्रमागत dst_sel:2;
			uपूर्णांक32_t reserved8:6;
			क्रमागत mec_release_mem_पूर्णांक_sel_क्रमागत पूर्णांक_sel:3;
			uपूर्णांक32_t reserved9:2;
			क्रमागत mec_release_mem_data_sel_क्रमागत data_sel:3;
		पूर्ण bitfields3;
		अचिन्हित पूर्णांक ordinal3;
	पूर्ण;

	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t reserved10:2;
			अचिन्हित पूर्णांक address_lo_32b:30;
		पूर्ण bitfields4;
		काष्ठा अणु
			uपूर्णांक32_t reserved11:3;
			uपूर्णांक32_t address_lo_64b:29;
		पूर्ण bitfields4b;
		uपूर्णांक32_t reserved12;
		अचिन्हित पूर्णांक ordinal4;
	पूर्ण;

	जोड़ अणु
		uपूर्णांक32_t address_hi;
		uपूर्णांक32_t reserved13;
		uपूर्णांक32_t ordinal5;
	पूर्ण;

	जोड़ अणु
		uपूर्णांक32_t data_lo;
		uपूर्णांक32_t cmp_data_lo;
		काष्ठा अणु
			uपूर्णांक32_t dw_offset:16;
			uपूर्णांक32_t num_dwords:16;
		पूर्ण bitfields6c;
		uपूर्णांक32_t reserved14;
		uपूर्णांक32_t ordinal6;
	पूर्ण;

	जोड़ अणु
		uपूर्णांक32_t data_hi;
		uपूर्णांक32_t cmp_data_hi;
		uपूर्णांक32_t reserved15;
		uपूर्णांक32_t reserved16;
		uपूर्णांक32_t ordinal7;
	पूर्ण;

	uपूर्णांक32_t पूर्णांक_ctxid;

पूर्ण;

#पूर्ण_अगर

क्रमागत अणु
	CACHE_FLUSH_AND_INV_TS_EVENT = 0x00000014
पूर्ण;
#पूर्ण_अगर


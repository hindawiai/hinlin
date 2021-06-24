<शैली गुरु>
/*
 * Copyright 2016-2018 Advanced Micro Devices, Inc.
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

#समावेश "kfd_kernel_queue.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_pm4_headers_ai.h"
#समावेश "kfd_pm4_opcodes.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"

अटल पूर्णांक pm_map_process_v9(काष्ठा packet_manager *pm,
		uपूर्णांक32_t *buffer, काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा pm4_mes_map_process *packet;
	uपूर्णांक64_t vm_page_table_base_addr = qpd->page_table_base;

	packet = (काष्ठा pm4_mes_map_process *)buffer;
	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_map_process));

	packet->header.u32All = pm_build_pm4_header(IT_MAP_PROCESS,
					माप(काष्ठा pm4_mes_map_process));
	packet->bitfields2.diq_enable = (qpd->is_debug) ? 1 : 0;
	packet->bitfields2.process_quantum = 10;
	packet->bitfields2.pasid = qpd->pqm->process->pasid;
	packet->bitfields14.gds_size = qpd->gds_size & 0x3F;
	packet->bitfields14.gds_size_hi = (qpd->gds_size >> 6) & 0xF;
	packet->bitfields14.num_gws = (qpd->mapped_gws_queue) ? qpd->num_gws : 0;
	packet->bitfields14.num_oac = qpd->num_oac;
	packet->bitfields14.sdma_enable = 1;
	packet->bitfields14.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	अगर (qpd->tba_addr) अणु
		packet->sq_shader_tba_lo = lower_32_bits(qpd->tba_addr >> 8);
		/* On GFX9, unlike GFX10, bit TRAP_EN of SQ_SHADER_TBA_HI is
		 * not defined, so setting it won't करो any harm.
		 */
		packet->sq_shader_tba_hi = upper_32_bits(qpd->tba_addr >> 8)
				| 1 << SQ_SHADER_TBA_HI__TRAP_EN__SHIFT;

		packet->sq_shader_पंचांगa_lo = lower_32_bits(qpd->पंचांगa_addr >> 8);
		packet->sq_shader_पंचांगa_hi = upper_32_bits(qpd->पंचांगa_addr >> 8);
	पूर्ण

	packet->gds_addr_lo = lower_32_bits(qpd->gds_context_area);
	packet->gds_addr_hi = upper_32_bits(qpd->gds_context_area);

	packet->vm_context_page_table_base_addr_lo32 =
			lower_32_bits(vm_page_table_base_addr);
	packet->vm_context_page_table_base_addr_hi32 =
			upper_32_bits(vm_page_table_base_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक pm_runlist_v9(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			uपूर्णांक64_t ib, माप_प्रकार ib_size_in_dwords, bool chain)
अणु
	काष्ठा pm4_mes_runlist *packet;

	पूर्णांक concurrent_proc_cnt = 0;
	काष्ठा kfd_dev *kfd = pm->dqm->dev;

	/* Determine the number of processes to map together to HW:
	 * it can not exceed the number of VMIDs available to the
	 * scheduler, and it is determined by the smaller of the number
	 * of processes in the runlist and kfd module parameter
	 * hws_max_conc_proc.
	 * Note: the arbitration between the number of VMIDs and
	 * hws_max_conc_proc has been करोne in
	 * kgd2kfd_device_init().
	 */
	concurrent_proc_cnt = min(pm->dqm->processes_count,
			kfd->max_proc_per_quantum);

	packet = (काष्ठा pm4_mes_runlist *)buffer;

	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_runlist));
	packet->header.u32All = pm_build_pm4_header(IT_RUN_LIST,
						माप(काष्ठा pm4_mes_runlist));

	packet->bitfields4.ib_size = ib_size_in_dwords;
	packet->bitfields4.chain = chain ? 1 : 0;
	packet->bitfields4.offload_polling = 0;
	packet->bitfields4.chained_runlist_idle_disable = chain ? 1 : 0;
	packet->bitfields4.valid = 1;
	packet->bitfields4.process_cnt = concurrent_proc_cnt;
	packet->ordinal2 = lower_32_bits(ib);
	packet->ib_base_hi = upper_32_bits(ib);

	वापस 0;
पूर्ण

अटल पूर्णांक pm_set_resources_v9(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
				काष्ठा scheduling_resources *res)
अणु
	काष्ठा pm4_mes_set_resources *packet;

	packet = (काष्ठा pm4_mes_set_resources *)buffer;
	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_set_resources));

	packet->header.u32All = pm_build_pm4_header(IT_SET_RESOURCES,
					माप(काष्ठा pm4_mes_set_resources));

	packet->bitfields2.queue_type =
			queue_type__mes_set_resources__hsa_पूर्णांकerface_queue_hiq;
	packet->bitfields2.vmid_mask = res->vmid_mask;
	packet->bitfields2.unmap_latency = KFD_UNMAP_LATENCY_MS / 100;
	packet->bitfields7.oac_mask = res->oac_mask;
	packet->bitfields8.gds_heap_base = res->gds_heap_base;
	packet->bitfields8.gds_heap_size = res->gds_heap_size;

	packet->gws_mask_lo = lower_32_bits(res->gws_mask);
	packet->gws_mask_hi = upper_32_bits(res->gws_mask);

	packet->queue_mask_lo = lower_32_bits(res->queue_mask);
	packet->queue_mask_hi = upper_32_bits(res->queue_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक pm_map_queues_v9(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
		काष्ठा queue *q, bool is_अटल)
अणु
	काष्ठा pm4_mes_map_queues *packet;
	bool use_अटल = is_अटल;

	packet = (काष्ठा pm4_mes_map_queues *)buffer;
	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_map_queues));

	packet->header.u32All = pm_build_pm4_header(IT_MAP_QUEUES,
					माप(काष्ठा pm4_mes_map_queues));
	packet->bitfields2.num_queues = 1;
	packet->bitfields2.queue_sel =
		queue_sel__mes_map_queues__map_to_hws_determined_queue_slots_vi;

	packet->bitfields2.engine_sel =
		engine_sel__mes_map_queues__compute_vi;
	packet->bitfields2.gws_control_queue = q->gws ? 1 : 0;
	packet->bitfields2.extended_engine_sel =
		extended_engine_sel__mes_map_queues__legacy_engine_sel;
	packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_compute_vi;

	चयन (q->properties.type) अणु
	हाल KFD_QUEUE_TYPE_COMPUTE:
		अगर (use_अटल)
			packet->bitfields2.queue_type =
		queue_type__mes_map_queues__normal_latency_अटल_queue_vi;
		अवरोध;
	हाल KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.queue_type =
			queue_type__mes_map_queues__debug_पूर्णांकerface_queue_vi;
		अवरोध;
	हाल KFD_QUEUE_TYPE_SDMA:
	हाल KFD_QUEUE_TYPE_SDMA_XGMI:
		use_अटल = false; /* no अटल queues under SDMA */
		अगर (q->properties.sdma_engine_id < 2)
			packet->bitfields2.engine_sel = q->properties.sdma_engine_id +
				engine_sel__mes_map_queues__sdma0_vi;
		अन्यथा अणु
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_map_queues__sdma0_to_7_sel;
			packet->bitfields2.engine_sel = q->properties.sdma_engine_id;
		पूर्ण
		अवरोध;
	शेष:
		WARN(1, "queue type %d", q->properties.type);
		वापस -EINVAL;
	पूर्ण
	packet->bitfields3.करोorbell_offset =
			q->properties.करोorbell_off;

	packet->mqd_addr_lo =
			lower_32_bits(q->gart_mqd_addr);

	packet->mqd_addr_hi =
			upper_32_bits(q->gart_mqd_addr);

	packet->wptr_addr_lo =
			lower_32_bits((uपूर्णांक64_t)q->properties.ग_लिखो_ptr);

	packet->wptr_addr_hi =
			upper_32_bits((uपूर्णांक64_t)q->properties.ग_लिखो_ptr);

	वापस 0;
पूर्ण

अटल पूर्णांक pm_unmap_queues_v9(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			क्रमागत kfd_queue_type type,
			क्रमागत kfd_unmap_queues_filter filter,
			uपूर्णांक32_t filter_param, bool reset,
			अचिन्हित पूर्णांक sdma_engine)
अणु
	काष्ठा pm4_mes_unmap_queues *packet;

	packet = (काष्ठा pm4_mes_unmap_queues *)buffer;
	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_unmap_queues));

	packet->header.u32All = pm_build_pm4_header(IT_UNMAP_QUEUES,
					माप(काष्ठा pm4_mes_unmap_queues));
	चयन (type) अणु
	हाल KFD_QUEUE_TYPE_COMPUTE:
	हाल KFD_QUEUE_TYPE_DIQ:
		packet->bitfields2.extended_engine_sel =
			extended_engine_sel__mes_unmap_queues__legacy_engine_sel;
		packet->bitfields2.engine_sel =
			engine_sel__mes_unmap_queues__compute;
		अवरोध;
	हाल KFD_QUEUE_TYPE_SDMA:
	हाल KFD_QUEUE_TYPE_SDMA_XGMI:
		अगर (sdma_engine < 2) अणु
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_unmap_queues__legacy_engine_sel;
			packet->bitfields2.engine_sel =
				engine_sel__mes_unmap_queues__sdma0 + sdma_engine;
		पूर्ण अन्यथा अणु
			packet->bitfields2.extended_engine_sel =
				extended_engine_sel__mes_unmap_queues__sdma0_to_7_sel;
			packet->bitfields2.engine_sel = sdma_engine;
		पूर्ण
		अवरोध;
	शेष:
		WARN(1, "queue type %d", type);
		वापस -EINVAL;
	पूर्ण

	अगर (reset)
		packet->bitfields2.action =
			action__mes_unmap_queues__reset_queues;
	अन्यथा
		packet->bitfields2.action =
			action__mes_unmap_queues__preempt_queues;

	चयन (filter) अणु
	हाल KFD_UNMAP_QUEUES_FILTER_SINGLE_QUEUE:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__perक्रमm_request_on_specअगरied_queues;
		packet->bitfields2.num_queues = 1;
		packet->bitfields3b.करोorbell_offset0 = filter_param;
		अवरोध;
	हाल KFD_UNMAP_QUEUES_FILTER_BY_PASID:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__perक्रमm_request_on_pasid_queues;
		packet->bitfields3a.pasid = filter_param;
		अवरोध;
	हाल KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES:
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__unmap_all_queues;
		अवरोध;
	हाल KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES:
		/* in this हाल, we करो not preempt अटल queues */
		packet->bitfields2.queue_sel =
			queue_sel__mes_unmap_queues__unmap_all_non_अटल_queues;
		अवरोध;
	शेष:
		WARN(1, "filter %d", filter);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक pm_query_status_v9(काष्ठा packet_manager *pm, uपूर्णांक32_t *buffer,
			uपूर्णांक64_t fence_address,	uपूर्णांक64_t fence_value)
अणु
	काष्ठा pm4_mes_query_status *packet;

	packet = (काष्ठा pm4_mes_query_status *)buffer;
	स_रखो(buffer, 0, माप(काष्ठा pm4_mes_query_status));


	packet->header.u32All = pm_build_pm4_header(IT_QUERY_STATUS,
					माप(काष्ठा pm4_mes_query_status));

	packet->bitfields2.context_id = 0;
	packet->bitfields2.पूर्णांकerrupt_sel =
			पूर्णांकerrupt_sel__mes_query_status__completion_status;
	packet->bitfields2.command =
			command__mes_query_status__fence_only_after_ग_लिखो_ack;

	packet->addr_hi = upper_32_bits((uपूर्णांक64_t)fence_address);
	packet->addr_lo = lower_32_bits((uपूर्णांक64_t)fence_address);
	packet->data_hi = upper_32_bits((uपूर्णांक64_t)fence_value);
	packet->data_lo = lower_32_bits((uपूर्णांक64_t)fence_value);

	वापस 0;
पूर्ण

स्थिर काष्ठा packet_manager_funcs kfd_v9_pm_funcs = अणु
	.map_process		= pm_map_process_v9,
	.runlist		= pm_runlist_v9,
	.set_resources		= pm_set_resources_v9,
	.map_queues		= pm_map_queues_v9,
	.unmap_queues		= pm_unmap_queues_v9,
	.query_status		= pm_query_status_v9,
	.release_mem		= शून्य,
	.map_process_size	= माप(काष्ठा pm4_mes_map_process),
	.runlist_size		= माप(काष्ठा pm4_mes_runlist),
	.set_resources_size	= माप(काष्ठा pm4_mes_set_resources),
	.map_queues_size	= माप(काष्ठा pm4_mes_map_queues),
	.unmap_queues_size	= माप(काष्ठा pm4_mes_unmap_queues),
	.query_status_size	= माप(काष्ठा pm4_mes_query_status),
	.release_mem_size	= 0,
पूर्ण;

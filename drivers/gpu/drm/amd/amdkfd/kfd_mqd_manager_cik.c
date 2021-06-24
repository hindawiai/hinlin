<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>

#समावेश "kfd_priv.h"
#समावेश "kfd_mqd_manager.h"
#समावेश "cik_regs.h"
#समावेश "cik_structs.h"
#समावेश "oss/oss_2_4_sh_mask.h"

अटल अंतरभूत काष्ठा cik_mqd *get_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा cik_mqd *)mqd;
पूर्ण

अटल अंतरभूत काष्ठा cik_sdma_rlc_रेजिस्टरs *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा cik_sdma_rlc_रेजिस्टरs *)mqd;
पूर्ण

अटल व्योम update_cu_mask(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा queue_properties *q)
अणु
	काष्ठा cik_mqd *m;
	uपूर्णांक32_t se_mask[4] = अणु0पूर्ण; /* 4 is the max # of SEs */

	अगर (q->cu_mask_count == 0)
		वापस;

	mqd_symmetrically_map_cu_mask(mm,
		q->cu_mask, q->cu_mask_count, se_mask);

	m = get_mqd(mqd);
	m->compute_अटल_thपढ़ो_mgmt_se0 = se_mask[0];
	m->compute_अटल_thपढ़ो_mgmt_se1 = se_mask[1];
	m->compute_अटल_thपढ़ो_mgmt_se2 = se_mask[2];
	m->compute_अटल_thपढ़ो_mgmt_se3 = se_mask[3];

	pr_debug("Update cu mask to %#x %#x %#x %#x\n",
		m->compute_अटल_thपढ़ो_mgmt_se0,
		m->compute_अटल_thपढ़ो_mgmt_se1,
		m->compute_अटल_thपढ़ो_mgmt_se2,
		m->compute_अटल_thपढ़ो_mgmt_se3);
पूर्ण

अटल व्योम set_priority(काष्ठा cik_mqd *m, काष्ठा queue_properties *q)
अणु
	m->cp_hqd_pipe_priority = pipe_priority_map[q->priority];
	m->cp_hqd_queue_priority = q->priority;
पूर्ण

अटल काष्ठा kfd_mem_obj *allocate_mqd(काष्ठा kfd_dev *kfd,
					काष्ठा queue_properties *q)
अणु
	काष्ठा kfd_mem_obj *mqd_mem_obj;

	अगर (kfd_gtt_sa_allocate(kfd, माप(काष्ठा cik_mqd),
			&mqd_mem_obj))
		वापस शून्य;

	वापस mqd_mem_obj;
पूर्ण

अटल व्योम init_mqd(काष्ठा mqd_manager *mm, व्योम **mqd,
		काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
		काष्ठा queue_properties *q)
अणु
	uपूर्णांक64_t addr;
	काष्ठा cik_mqd *m;

	m = (काष्ठा cik_mqd *) mqd_mem_obj->cpu_ptr;
	addr = mqd_mem_obj->gpu_addr;

	स_रखो(m, 0, ALIGN(माप(काष्ठा cik_mqd), 256));

	m->header = 0xC0310800;
	m->compute_pipelinestat_enable = 1;
	m->compute_अटल_thपढ़ो_mgmt_se0 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se1 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se2 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se3 = 0xFFFFFFFF;

	/*
	 * Make sure to use the last queue state saved on mqd when the cp
	 * reassigns the queue, so when queue is चयनed on/off (e.g over
	 * subscription or quantum समयout) the context will be consistent
	 */
	m->cp_hqd_persistent_state =
				DEFAULT_CP_HQD_PERSISTENT_STATE | PRELOAD_REQ;

	m->cp_mqd_control             = MQD_CONTROL_PRIV_STATE_EN;
	m->cp_mqd_base_addr_lo        = lower_32_bits(addr);
	m->cp_mqd_base_addr_hi        = upper_32_bits(addr);

	m->cp_hqd_quantum = QUANTUM_EN | QUANTUM_SCALE_1MS |
				QUANTUM_DURATION(10);

	/*
	 * Pipe Priority
	 * Identअगरies the pipe relative priority when this queue is connected
	 * to the pipeline. The pipe priority is against the GFX pipe and HP3D.
	 * In KFD we are using a fixed pipe priority set to CS_MEDIUM.
	 * 0 = CS_LOW (typically below GFX)
	 * 1 = CS_MEDIUM (typically between HP3D and GFX
	 * 2 = CS_HIGH (typically above HP3D)
	 */
	set_priority(m, q);

	अगर (q->क्रमmat == KFD_QUEUE_FORMAT_AQL)
		m->cp_hqd_iq_rptr = AQL_ENABLE;

	*mqd = m;
	अगर (gart_addr)
		*gart_addr = addr;
	mm->update_mqd(mm, m, q);
पूर्ण

अटल व्योम init_mqd_sdma(काष्ठा mqd_manager *mm, व्योम **mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
			काष्ठा queue_properties *q)
अणु
	काष्ठा cik_sdma_rlc_रेजिस्टरs *m;

	m = (काष्ठा cik_sdma_rlc_रेजिस्टरs *) mqd_mem_obj->cpu_ptr;

	स_रखो(m, 0, माप(काष्ठा cik_sdma_rlc_रेजिस्टरs));

	*mqd = m;
	अगर (gart_addr)
		*gart_addr = mqd_mem_obj->gpu_addr;

	mm->update_mqd(mm, m, q);
पूर्ण

अटल व्योम मुक्त_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj)
अणु
	kfd_gtt_sa_मुक्त(mm->dev, mqd_mem_obj);
पूर्ण


अटल पूर्णांक load_mqd(काष्ठा mqd_manager *mm, व्योम *mqd, uपूर्णांक32_t pipe_id,
		    uपूर्णांक32_t queue_id, काष्ठा queue_properties *p,
		    काष्ठा mm_काष्ठा *mms)
अणु
	/* AQL ग_लिखो poपूर्णांकer counts in 64B packets, PM4/CP counts in dwords. */
	uपूर्णांक32_t wptr_shअगरt = (p->क्रमmat == KFD_QUEUE_FORMAT_AQL ? 4 : 0);
	uपूर्णांक32_t wptr_mask = (uपूर्णांक32_t)((p->queue_size / 4) - 1);

	वापस mm->dev->kfd2kgd->hqd_load(mm->dev->kgd, mqd, pipe_id, queue_id,
					  (uपूर्णांक32_t __user *)p->ग_लिखो_ptr,
					  wptr_shअगरt, wptr_mask, mms);
पूर्ण

अटल पूर्णांक load_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
			 uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			 काष्ठा queue_properties *p, काष्ठा mm_काष्ठा *mms)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_load(mm->dev->kgd, mqd,
					       (uपूर्णांक32_t __user *)p->ग_लिखो_ptr,
					       mms);
पूर्ण

अटल व्योम __update_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा queue_properties *q, अचिन्हित पूर्णांक atc_bit)
अणु
	काष्ठा cik_mqd *m;

	m = get_mqd(mqd);
	m->cp_hqd_pq_control = DEFAULT_RPTR_BLOCK_SIZE |
				DEFAULT_MIN_AVAIL_SIZE;
	m->cp_hqd_ib_control = DEFAULT_MIN_IB_AVAIL_SIZE;
	अगर (atc_bit) अणु
		m->cp_hqd_pq_control |= PQ_ATC_EN;
		m->cp_hqd_ib_control |= IB_ATC_EN;
	पूर्ण

	/*
	 * Calculating queue size which is log base 2 of actual queue size -1
	 * dwords and another -1 क्रम ffs
	 */
	m->cp_hqd_pq_control |= order_base_2(q->queue_size / 4) - 1;
	m->cp_hqd_pq_base_lo = lower_32_bits((uपूर्णांक64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uपूर्णांक64_t)q->queue_address >> 8);
	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_करोorbell_control = DOORBELL_OFFSET(q->करोorbell_off);

	m->cp_hqd_vmid = q->vmid;

	अगर (q->क्रमmat == KFD_QUEUE_FORMAT_AQL)
		m->cp_hqd_pq_control |= NO_UPDATE_RPTR;

	update_cu_mask(mm, mqd, q);
	set_priority(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
पूर्ण

अटल व्योम update_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा queue_properties *q)
अणु
	__update_mqd(mm, mqd, q, 1);
पूर्ण

अटल uपूर्णांक32_t पढ़ो_करोorbell_id(व्योम *mqd)
अणु
	काष्ठा cik_mqd *m = (काष्ठा cik_mqd *)mqd;

	वापस m->queue_करोorbell_id0;
पूर्ण

अटल व्योम update_mqd_hawaii(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा queue_properties *q)
अणु
	__update_mqd(mm, mqd, q, 0);
पूर्ण

अटल व्योम update_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
				काष्ठा queue_properties *q)
अणु
	काष्ठा cik_sdma_rlc_रेजिस्टरs *m;

	m = get_sdma_mqd(mqd);
	m->sdma_rlc_rb_cntl = order_base_2(q->queue_size / 4)
			<< SDMA0_RLC0_RB_CNTL__RB_SIZE__SHIFT |
			q->vmid << SDMA0_RLC0_RB_CNTL__RB_VMID__SHIFT |
			1 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_ENABLE__SHIFT |
			6 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_TIMER__SHIFT;

	m->sdma_rlc_rb_base = lower_32_bits(q->queue_address >> 8);
	m->sdma_rlc_rb_base_hi = upper_32_bits(q->queue_address >> 8);
	m->sdma_rlc_rb_rptr_addr_lo = lower_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->sdma_rlc_rb_rptr_addr_hi = upper_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->sdma_rlc_करोorbell =
		q->करोorbell_off << SDMA0_RLC0_DOORBELL__OFFSET__SHIFT;

	m->sdma_rlc_भव_addr = q->sdma_vm_addr;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;

	q->is_active = QUEUE_IS_ACTIVE(*q);
पूर्ण

अटल पूर्णांक destroy_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			क्रमागत kfd_preempt_type type,
			अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_destroy(mm->dev->kgd, mqd, type, समयout,
					pipe_id, queue_id);
पूर्ण

/*
 * preempt type here is ignored because there is only one way
 * to preempt sdma queue
 */
अटल पूर्णांक destroy_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
				क्रमागत kfd_preempt_type type,
				अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_destroy(mm->dev->kgd, mqd, समयout);
पूर्ण

अटल bool is_occupied(काष्ठा mqd_manager *mm, व्योम *mqd,
			uपूर्णांक64_t queue_address,	uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id)
अणु

	वापस mm->dev->kfd2kgd->hqd_is_occupied(mm->dev->kgd, queue_address,
					pipe_id, queue_id);

पूर्ण

अटल bool is_occupied_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
			uपूर्णांक64_t queue_address,	uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_is_occupied(mm->dev->kgd, mqd);
पूर्ण

/*
 * HIQ MQD Implementation, concrete implementation क्रम HIQ MQD implementation.
 * The HIQ queue in Kaveri is using the same MQD काष्ठाure as all the user mode
 * queues but with dअगरferent initial values.
 */

अटल व्योम init_mqd_hiq(काष्ठा mqd_manager *mm, व्योम **mqd,
		काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
		काष्ठा queue_properties *q)
अणु
	init_mqd(mm, mqd, mqd_mem_obj, gart_addr, q);
पूर्ण

अटल व्योम update_mqd_hiq(काष्ठा mqd_manager *mm, व्योम *mqd,
				काष्ठा queue_properties *q)
अणु
	काष्ठा cik_mqd *m;

	m = get_mqd(mqd);
	m->cp_hqd_pq_control = DEFAULT_RPTR_BLOCK_SIZE |
				DEFAULT_MIN_AVAIL_SIZE |
				PRIV_STATE |
				KMD_QUEUE;

	/*
	 * Calculating queue size which is log base 2 of actual queue
	 * size -1 dwords
	 */
	m->cp_hqd_pq_control |= order_base_2(q->queue_size / 4) - 1;
	m->cp_hqd_pq_base_lo = lower_32_bits((uपूर्णांक64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uपूर्णांक64_t)q->queue_address >> 8);
	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_करोorbell_control = DOORBELL_OFFSET(q->करोorbell_off);

	m->cp_hqd_vmid = q->vmid;

	q->is_active = QUEUE_IS_ACTIVE(*q);

	set_priority(m, q);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक debugfs_show_mqd(काष्ठा seq_file *m, व्योम *data)
अणु
	seq_hex_dump(m, "    ", DUMP_PREFIX_OFFSET, 32, 4,
		     data, माप(काष्ठा cik_mqd), false);
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_show_mqd_sdma(काष्ठा seq_file *m, व्योम *data)
अणु
	seq_hex_dump(m, "    ", DUMP_PREFIX_OFFSET, 32, 4,
		     data, माप(काष्ठा cik_sdma_rlc_रेजिस्टरs), false);
	वापस 0;
पूर्ण

#पूर्ण_अगर


काष्ठा mqd_manager *mqd_manager_init_cik(क्रमागत KFD_MQD_TYPE type,
		काष्ठा kfd_dev *dev)
अणु
	काष्ठा mqd_manager *mqd;

	अगर (WARN_ON(type >= KFD_MQD_TYPE_MAX))
		वापस शून्य;

	mqd = kzalloc(माप(*mqd), GFP_KERNEL);
	अगर (!mqd)
		वापस शून्य;

	mqd->dev = dev;

	चयन (type) अणु
	हाल KFD_MQD_TYPE_CP:
		mqd->allocate_mqd = allocate_mqd;
		mqd->init_mqd = init_mqd;
		mqd->मुक्त_mqd = मुक्त_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा cik_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		अवरोध;
	हाल KFD_MQD_TYPE_HIQ:
		mqd->allocate_mqd = allocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->मुक्त_mqd = मुक्त_mqd_hiq_sdma;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा cik_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		mqd->पढ़ो_करोorbell_id = पढ़ो_करोorbell_id;
		अवरोध;
	हाल KFD_MQD_TYPE_DIQ:
		mqd->allocate_mqd = allocate_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->मुक्त_mqd = मुक्त_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd_hiq;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा cik_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		अवरोध;
	हाल KFD_MQD_TYPE_SDMA:
		mqd->allocate_mqd = allocate_sdma_mqd;
		mqd->init_mqd = init_mqd_sdma;
		mqd->मुक्त_mqd = मुक्त_mqd_hiq_sdma;
		mqd->load_mqd = load_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destroy_mqd = destroy_mqd_sdma;
		mqd->is_occupied = is_occupied_sdma;
		mqd->mqd_size = माप(काष्ठा cik_sdma_rlc_रेजिस्टरs);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd_sdma;
#पूर्ण_अगर
		अवरोध;
	शेष:
		kमुक्त(mqd);
		वापस शून्य;
	पूर्ण

	वापस mqd;
पूर्ण

काष्ठा mqd_manager *mqd_manager_init_cik_hawaii(क्रमागत KFD_MQD_TYPE type,
			काष्ठा kfd_dev *dev)
अणु
	काष्ठा mqd_manager *mqd;

	mqd = mqd_manager_init_cik(type, dev);
	अगर (!mqd)
		वापस शून्य;
	अगर (type == KFD_MQD_TYPE_CP)
		mqd->update_mqd = update_mqd_hawaii;
	वापस mqd;
पूर्ण

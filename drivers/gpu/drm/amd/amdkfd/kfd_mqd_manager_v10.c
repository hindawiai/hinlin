<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#समावेश <linux/uaccess.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_mqd_manager.h"
#समावेश "v10_structs.h"
#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "amdgpu_amdkfd.h"

अटल अंतरभूत काष्ठा v10_compute_mqd *get_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_compute_mqd *)mqd;
पूर्ण

अटल अंतरभूत काष्ठा v10_sdma_mqd *get_sdma_mqd(व्योम *mqd)
अणु
	वापस (काष्ठा v10_sdma_mqd *)mqd;
पूर्ण

अटल व्योम update_cu_mask(काष्ठा mqd_manager *mm, व्योम *mqd,
			   काष्ठा queue_properties *q)
अणु
	काष्ठा v10_compute_mqd *m;
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

	pr_debug("update cu mask to %#x %#x %#x %#x\n",
		m->compute_अटल_thपढ़ो_mgmt_se0,
		m->compute_अटल_thपढ़ो_mgmt_se1,
		m->compute_अटल_thपढ़ो_mgmt_se2,
		m->compute_अटल_thपढ़ो_mgmt_se3);
पूर्ण

अटल व्योम set_priority(काष्ठा v10_compute_mqd *m, काष्ठा queue_properties *q)
अणु
	m->cp_hqd_pipe_priority = pipe_priority_map[q->priority];
	m->cp_hqd_queue_priority = q->priority;
पूर्ण

अटल काष्ठा kfd_mem_obj *allocate_mqd(काष्ठा kfd_dev *kfd,
		काष्ठा queue_properties *q)
अणु
	काष्ठा kfd_mem_obj *mqd_mem_obj;

	अगर (kfd_gtt_sa_allocate(kfd, माप(काष्ठा v10_compute_mqd),
			&mqd_mem_obj))
		वापस शून्य;

	वापस mqd_mem_obj;
पूर्ण

अटल व्योम init_mqd(काष्ठा mqd_manager *mm, व्योम **mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
			काष्ठा queue_properties *q)
अणु
	uपूर्णांक64_t addr;
	काष्ठा v10_compute_mqd *m;

	m = (काष्ठा v10_compute_mqd *) mqd_mem_obj->cpu_ptr;
	addr = mqd_mem_obj->gpu_addr;

	स_रखो(m, 0, माप(काष्ठा v10_compute_mqd));

	m->header = 0xC0310800;
	m->compute_pipelinestat_enable = 1;
	m->compute_अटल_thपढ़ो_mgmt_se0 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se1 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se2 = 0xFFFFFFFF;
	m->compute_अटल_thपढ़ो_mgmt_se3 = 0xFFFFFFFF;

	m->cp_hqd_persistent_state = CP_HQD_PERSISTENT_STATE__PRELOAD_REQ_MASK |
			0x53 << CP_HQD_PERSISTENT_STATE__PRELOAD_SIZE__SHIFT;

	m->cp_mqd_control = 1 << CP_MQD_CONTROL__PRIV_STATE__SHIFT;

	m->cp_mqd_base_addr_lo        = lower_32_bits(addr);
	m->cp_mqd_base_addr_hi        = upper_32_bits(addr);

	m->cp_hqd_quantum = 1 << CP_HQD_QUANTUM__QUANTUM_EN__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_SCALE__SHIFT |
			1 << CP_HQD_QUANTUM__QUANTUM_DURATION__SHIFT;

	अगर (q->क्रमmat == KFD_QUEUE_FORMAT_AQL) अणु
		m->cp_hqd_aql_control =
			1 << CP_HQD_AQL_CONTROL__CONTROL0__SHIFT;
	पूर्ण

	अगर (mm->dev->cwsr_enabled) अणु
		m->cp_hqd_persistent_state |=
			(1 << CP_HQD_PERSISTENT_STATE__QSWITCH_MODE__SHIFT);
		m->cp_hqd_ctx_save_base_addr_lo =
			lower_32_bits(q->ctx_save_restore_area_address);
		m->cp_hqd_ctx_save_base_addr_hi =
			upper_32_bits(q->ctx_save_restore_area_address);
		m->cp_hqd_ctx_save_size = q->ctx_save_restore_area_size;
		m->cp_hqd_cntl_stack_size = q->ctl_stack_size;
		m->cp_hqd_cntl_stack_offset = q->ctl_stack_size;
		m->cp_hqd_wg_state_offset = q->ctl_stack_size;
	पूर्ण

	*mqd = m;
	अगर (gart_addr)
		*gart_addr = addr;
	mm->update_mqd(mm, m, q);
पूर्ण

अटल पूर्णांक load_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			काष्ठा queue_properties *p, काष्ठा mm_काष्ठा *mms)
अणु
	पूर्णांक r = 0;
	/* AQL ग_लिखो poपूर्णांकer counts in 64B packets, PM4/CP counts in dwords. */
	uपूर्णांक32_t wptr_shअगरt = (p->क्रमmat == KFD_QUEUE_FORMAT_AQL ? 4 : 0);

	r = mm->dev->kfd2kgd->hqd_load(mm->dev->kgd, mqd, pipe_id, queue_id,
					  (uपूर्णांक32_t __user *)p->ग_लिखो_ptr,
					  wptr_shअगरt, 0, mms);
	वापस r;
पूर्ण

अटल पूर्णांक hiq_load_mqd_kiq(काष्ठा mqd_manager *mm, व्योम *mqd,
			    uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			    काष्ठा queue_properties *p, काष्ठा mm_काष्ठा *mms)
अणु
	वापस mm->dev->kfd2kgd->hiq_mqd_load(mm->dev->kgd, mqd, pipe_id,
					      queue_id, p->करोorbell_off);
पूर्ण

अटल व्योम update_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
		      काष्ठा queue_properties *q)
अणु
	काष्ठा v10_compute_mqd *m;

	m = get_mqd(mqd);

	m->cp_hqd_pq_control = 5 << CP_HQD_PQ_CONTROL__RPTR_BLOCK_SIZE__SHIFT;
	m->cp_hqd_pq_control |=
			ffs(q->queue_size / माप(अचिन्हित पूर्णांक)) - 1 - 1;
	pr_debug("cp_hqd_pq_control 0x%x\n", m->cp_hqd_pq_control);

	m->cp_hqd_pq_base_lo = lower_32_bits((uपूर्णांक64_t)q->queue_address >> 8);
	m->cp_hqd_pq_base_hi = upper_32_bits((uपूर्णांक64_t)q->queue_address >> 8);

	m->cp_hqd_pq_rptr_report_addr_lo = lower_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_rptr_report_addr_hi = upper_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->cp_hqd_pq_wptr_poll_addr_lo = lower_32_bits((uपूर्णांक64_t)q->ग_लिखो_ptr);
	m->cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits((uपूर्णांक64_t)q->ग_लिखो_ptr);

	m->cp_hqd_pq_करोorbell_control =
		q->करोorbell_off <<
			CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_OFFSET__SHIFT;
	pr_debug("cp_hqd_pq_doorbell_control 0x%x\n",
			m->cp_hqd_pq_करोorbell_control);

	m->cp_hqd_ib_control = 3 << CP_HQD_IB_CONTROL__MIN_IB_AVAIL_SIZE__SHIFT;

	/*
	 * HW करोes not clamp this field correctly. Maximum EOP queue size
	 * is स्थिरrained by per-SE EOP करोne संकेत count, which is 8-bit.
	 * Limit is 0xFF EOP entries (= 0x7F8 dwords). CP will not submit
	 * more than (EOP entry count - 1) so a queue size of 0x800 dwords
	 * is safe, giving a maximum field value of 0xA.
	 */
	m->cp_hqd_eop_control = min(0xA,
		ffs(q->eop_ring_buffer_size / माप(अचिन्हित पूर्णांक)) - 1 - 1);
	m->cp_hqd_eop_base_addr_lo =
			lower_32_bits(q->eop_ring_buffer_address >> 8);
	m->cp_hqd_eop_base_addr_hi =
			upper_32_bits(q->eop_ring_buffer_address >> 8);

	m->cp_hqd_iq_समयr = 0;

	m->cp_hqd_vmid = q->vmid;

	अगर (q->क्रमmat == KFD_QUEUE_FORMAT_AQL) अणु
		/* GC 10 हटाओd WPP_CLAMP from PQ Control */
		m->cp_hqd_pq_control |= CP_HQD_PQ_CONTROL__NO_UPDATE_RPTR_MASK |
				2 << CP_HQD_PQ_CONTROL__SLOT_BASED_WPTR__SHIFT |
				1 << CP_HQD_PQ_CONTROL__QUEUE_FULL_EN__SHIFT ;
		m->cp_hqd_pq_करोorbell_control |=
			1 << CP_HQD_PQ_DOORBELL_CONTROL__DOORBELL_BIF_DROP__SHIFT;
	पूर्ण
	अगर (mm->dev->cwsr_enabled)
		m->cp_hqd_ctx_save_control = 0;

	update_cu_mask(mm, mqd, q);
	set_priority(m, q);

	q->is_active = QUEUE_IS_ACTIVE(*q);
पूर्ण

अटल uपूर्णांक32_t पढ़ो_करोorbell_id(व्योम *mqd)
अणु
	काष्ठा v10_compute_mqd *m = (काष्ठा v10_compute_mqd *)mqd;

	वापस m->queue_करोorbell_id0;
पूर्ण

अटल पूर्णांक destroy_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
		       क्रमागत kfd_preempt_type type,
		       अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
		       uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_destroy
		(mm->dev->kgd, mqd, type, समयout,
		 pipe_id, queue_id);
पूर्ण

अटल व्योम मुक्त_mqd(काष्ठा mqd_manager *mm, व्योम *mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj)
अणु
	kfd_gtt_sa_मुक्त(mm->dev, mqd_mem_obj);
पूर्ण

अटल bool is_occupied(काष्ठा mqd_manager *mm, व्योम *mqd,
			uपूर्णांक64_t queue_address,	uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_is_occupied(
		mm->dev->kgd, queue_address,
		pipe_id, queue_id);
पूर्ण

अटल पूर्णांक get_wave_state(काष्ठा mqd_manager *mm, व्योम *mqd,
			  व्योम __user *ctl_stack,
			  u32 *ctl_stack_used_size,
			  u32 *save_area_used_size)
अणु
	काष्ठा v10_compute_mqd *m;

	m = get_mqd(mqd);

	/* Control stack is written backwards, जबतक workgroup context data
	 * is written क्रमwards. Both starts from m->cp_hqd_cntl_stack_size.
	 * Current position is at m->cp_hqd_cntl_stack_offset and
	 * m->cp_hqd_wg_state_offset, respectively.
	 */
	*ctl_stack_used_size = m->cp_hqd_cntl_stack_size -
		m->cp_hqd_cntl_stack_offset;
	*save_area_used_size = m->cp_hqd_wg_state_offset -
		m->cp_hqd_cntl_stack_size;

	/* Control stack is not copied to user mode क्रम GFXv10 because
	 * it's part of the context save area that is alपढ़ोy
	 * accessible to user mode
	 */

	वापस 0;
पूर्ण

अटल व्योम init_mqd_hiq(काष्ठा mqd_manager *mm, व्योम **mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
			काष्ठा queue_properties *q)
अणु
	काष्ठा v10_compute_mqd *m;

	init_mqd(mm, mqd, mqd_mem_obj, gart_addr, q);

	m = get_mqd(*mqd);

	m->cp_hqd_pq_control |= 1 << CP_HQD_PQ_CONTROL__PRIV_STATE__SHIFT |
			1 << CP_HQD_PQ_CONTROL__KMD_QUEUE__SHIFT;
पूर्ण

अटल व्योम init_mqd_sdma(काष्ठा mqd_manager *mm, व्योम **mqd,
		काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
		काष्ठा queue_properties *q)
अणु
	काष्ठा v10_sdma_mqd *m;

	m = (काष्ठा v10_sdma_mqd *) mqd_mem_obj->cpu_ptr;

	स_रखो(m, 0, माप(काष्ठा v10_sdma_mqd));

	*mqd = m;
	अगर (gart_addr)
		*gart_addr = mqd_mem_obj->gpu_addr;

	mm->update_mqd(mm, m, q);
पूर्ण

अटल पूर्णांक load_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
		uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
		काष्ठा queue_properties *p, काष्ठा mm_काष्ठा *mms)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_load(mm->dev->kgd, mqd,
					       (uपूर्णांक32_t __user *)p->ग_लिखो_ptr,
					       mms);
पूर्ण

#घोषणा SDMA_RLC_DUMMY_DEFAULT 0xf

अटल व्योम update_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
		काष्ठा queue_properties *q)
अणु
	काष्ठा v10_sdma_mqd *m;

	m = get_sdma_mqd(mqd);
	m->sdmax_rlcx_rb_cntl = (ffs(q->queue_size / माप(अचिन्हित पूर्णांक)) - 1)
		<< SDMA0_RLC0_RB_CNTL__RB_SIZE__SHIFT |
		q->vmid << SDMA0_RLC0_RB_CNTL__RB_VMID__SHIFT |
		1 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_ENABLE__SHIFT |
		6 << SDMA0_RLC0_RB_CNTL__RPTR_WRITEBACK_TIMER__SHIFT;

	m->sdmax_rlcx_rb_base = lower_32_bits(q->queue_address >> 8);
	m->sdmax_rlcx_rb_base_hi = upper_32_bits(q->queue_address >> 8);
	m->sdmax_rlcx_rb_rptr_addr_lo = lower_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->sdmax_rlcx_rb_rptr_addr_hi = upper_32_bits((uपूर्णांक64_t)q->पढ़ो_ptr);
	m->sdmax_rlcx_करोorbell_offset =
		q->करोorbell_off << SDMA0_RLC0_DOORBELL_OFFSET__OFFSET__SHIFT;

	m->sdma_engine_id = q->sdma_engine_id;
	m->sdma_queue_id = q->sdma_queue_id;
	m->sdmax_rlcx_dummy_reg = SDMA_RLC_DUMMY_DEFAULT;

	q->is_active = QUEUE_IS_ACTIVE(*q);
पूर्ण

/*
 *  * preempt type here is ignored because there is only one way
 *  * to preempt sdma queue
 */
अटल पूर्णांक destroy_mqd_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
		क्रमागत kfd_preempt_type type,
		अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
		uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_destroy(mm->dev->kgd, mqd, समयout);
पूर्ण

अटल bool is_occupied_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
		uपूर्णांक64_t queue_address, uपूर्णांक32_t pipe_id,
		uपूर्णांक32_t queue_id)
अणु
	वापस mm->dev->kfd2kgd->hqd_sdma_is_occupied(mm->dev->kgd, mqd);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक debugfs_show_mqd(काष्ठा seq_file *m, व्योम *data)
अणु
	seq_hex_dump(m, "    ", DUMP_PREFIX_OFFSET, 32, 4,
		     data, माप(काष्ठा v10_compute_mqd), false);
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_show_mqd_sdma(काष्ठा seq_file *m, व्योम *data)
अणु
	seq_hex_dump(m, "    ", DUMP_PREFIX_OFFSET, 32, 4,
		     data, माप(काष्ठा v10_sdma_mqd), false);
	वापस 0;
पूर्ण

#पूर्ण_अगर

काष्ठा mqd_manager *mqd_manager_init_v10(क्रमागत KFD_MQD_TYPE type,
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
		pr_debug("%s@%i\n", __func__, __LINE__);
		mqd->allocate_mqd = allocate_mqd;
		mqd->init_mqd = init_mqd;
		mqd->मुक्त_mqd = मुक्त_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा v10_compute_mqd);
		mqd->get_wave_state = get_wave_state;
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		pr_debug("%s@%i\n", __func__, __LINE__);
		अवरोध;
	हाल KFD_MQD_TYPE_HIQ:
		pr_debug("%s@%i\n", __func__, __LINE__);
		mqd->allocate_mqd = allocate_hiq_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->मुक्त_mqd = मुक्त_mqd_hiq_sdma;
		mqd->load_mqd = hiq_load_mqd_kiq;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा v10_compute_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		mqd->पढ़ो_करोorbell_id = पढ़ो_करोorbell_id;
		pr_debug("%s@%i\n", __func__, __LINE__);
		अवरोध;
	हाल KFD_MQD_TYPE_DIQ:
		mqd->allocate_mqd = allocate_mqd;
		mqd->init_mqd = init_mqd_hiq;
		mqd->मुक्त_mqd = मुक्त_mqd;
		mqd->load_mqd = load_mqd;
		mqd->update_mqd = update_mqd;
		mqd->destroy_mqd = destroy_mqd;
		mqd->is_occupied = is_occupied;
		mqd->mqd_size = माप(काष्ठा v10_compute_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd;
#पूर्ण_अगर
		अवरोध;
	हाल KFD_MQD_TYPE_SDMA:
		pr_debug("%s@%i\n", __func__, __LINE__);
		mqd->allocate_mqd = allocate_sdma_mqd;
		mqd->init_mqd = init_mqd_sdma;
		mqd->मुक्त_mqd = मुक्त_mqd_hiq_sdma;
		mqd->load_mqd = load_mqd_sdma;
		mqd->update_mqd = update_mqd_sdma;
		mqd->destroy_mqd = destroy_mqd_sdma;
		mqd->is_occupied = is_occupied_sdma;
		mqd->mqd_size = माप(काष्ठा v10_sdma_mqd);
#अगर defined(CONFIG_DEBUG_FS)
		mqd->debugfs_show_mqd = debugfs_show_mqd_sdma;
#पूर्ण_अगर
		pr_debug("%s@%i\n", __func__, __LINE__);
		अवरोध;
	शेष:
		kमुक्त(mqd);
		वापस शून्य;
	पूर्ण

	वापस mqd;
पूर्ण

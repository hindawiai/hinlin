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

#समावेश <linux/ratelimit.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_mqd_manager.h"
#समावेश "cik_regs.h"
#समावेश "kfd_kernel_queue.h"
#समावेश "amdgpu_amdkfd.h"

/* Size of the per-pipe EOP queue */
#घोषणा CIK_HPD_EOP_BYTES_LOG2 11
#घोषणा CIK_HPD_EOP_BYTES (1U << CIK_HPD_EOP_BYTES_LOG2)

अटल पूर्णांक set_pasid_vmid_mapping(काष्ठा device_queue_manager *dqm,
				  u32 pasid, अचिन्हित पूर्णांक vmid);

अटल पूर्णांक execute_queues_cpsch(काष्ठा device_queue_manager *dqm,
				क्रमागत kfd_unmap_queues_filter filter,
				uपूर्णांक32_t filter_param);
अटल पूर्णांक unmap_queues_cpsch(काष्ठा device_queue_manager *dqm,
				क्रमागत kfd_unmap_queues_filter filter,
				uपूर्णांक32_t filter_param);

अटल पूर्णांक map_queues_cpsch(काष्ठा device_queue_manager *dqm);

अटल व्योम deallocate_sdma_queue(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q);

अटल अंतरभूत व्योम deallocate_hqd(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q);
अटल पूर्णांक allocate_hqd(काष्ठा device_queue_manager *dqm, काष्ठा queue *q);
अटल पूर्णांक allocate_sdma_queue(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q);
अटल व्योम kfd_process_hw_exception(काष्ठा work_काष्ठा *work);

अटल अंतरभूत
क्रमागत KFD_MQD_TYPE get_mqd_type_from_queue_type(क्रमागत kfd_queue_type type)
अणु
	अगर (type == KFD_QUEUE_TYPE_SDMA || type == KFD_QUEUE_TYPE_SDMA_XGMI)
		वापस KFD_MQD_TYPE_SDMA;
	वापस KFD_MQD_TYPE_CP;
पूर्ण

अटल bool is_pipe_enabled(काष्ठा device_queue_manager *dqm, पूर्णांक mec, पूर्णांक pipe)
अणु
	पूर्णांक i;
	पूर्णांक pipe_offset = (mec * dqm->dev->shared_resources.num_pipe_per_mec
		+ pipe) * dqm->dev->shared_resources.num_queue_per_pipe;

	/* queue is available क्रम KFD usage अगर bit is 1 */
	क्रम (i = 0; i <  dqm->dev->shared_resources.num_queue_per_pipe; ++i)
		अगर (test_bit(pipe_offset + i,
			      dqm->dev->shared_resources.cp_queue_biपंचांगap))
			वापस true;
	वापस false;
पूर्ण

अचिन्हित पूर्णांक get_cp_queues_num(काष्ठा device_queue_manager *dqm)
अणु
	वापस biपंचांगap_weight(dqm->dev->shared_resources.cp_queue_biपंचांगap,
				KGD_MAX_QUEUES);
पूर्ण

अचिन्हित पूर्णांक get_queues_per_pipe(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->shared_resources.num_queue_per_pipe;
पूर्ण

अचिन्हित पूर्णांक get_pipes_per_mec(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->shared_resources.num_pipe_per_mec;
पूर्ण

अटल अचिन्हित पूर्णांक get_num_sdma_engines(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->device_info->num_sdma_engines;
पूर्ण

अटल अचिन्हित पूर्णांक get_num_xgmi_sdma_engines(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->device_info->num_xgmi_sdma_engines;
पूर्ण

अटल अचिन्हित पूर्णांक get_num_all_sdma_engines(काष्ठा device_queue_manager *dqm)
अणु
	वापस get_num_sdma_engines(dqm) + get_num_xgmi_sdma_engines(dqm);
पूर्ण

अचिन्हित पूर्णांक get_num_sdma_queues(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->device_info->num_sdma_engines
			* dqm->dev->device_info->num_sdma_queues_per_engine;
पूर्ण

अचिन्हित पूर्णांक get_num_xgmi_sdma_queues(काष्ठा device_queue_manager *dqm)
अणु
	वापस dqm->dev->device_info->num_xgmi_sdma_engines
			* dqm->dev->device_info->num_sdma_queues_per_engine;
पूर्ण

व्योम program_sh_mem_settings(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd)
अणु
	वापस dqm->dev->kfd2kgd->program_sh_mem_settings(
						dqm->dev->kgd, qpd->vmid,
						qpd->sh_mem_config,
						qpd->sh_mem_ape1_base,
						qpd->sh_mem_ape1_limit,
						qpd->sh_mem_bases);
पूर्ण

अटल व्योम increment_queue_count(काष्ठा device_queue_manager *dqm,
			क्रमागत kfd_queue_type type)
अणु
	dqm->active_queue_count++;
	अगर (type == KFD_QUEUE_TYPE_COMPUTE || type == KFD_QUEUE_TYPE_DIQ)
		dqm->active_cp_queue_count++;
पूर्ण

अटल व्योम decrement_queue_count(काष्ठा device_queue_manager *dqm,
			क्रमागत kfd_queue_type type)
अणु
	dqm->active_queue_count--;
	अगर (type == KFD_QUEUE_TYPE_COMPUTE || type == KFD_QUEUE_TYPE_DIQ)
		dqm->active_cp_queue_count--;
पूर्ण

अटल पूर्णांक allocate_करोorbell(काष्ठा qcm_process_device *qpd, काष्ठा queue *q)
अणु
	काष्ठा kfd_dev *dev = qpd->dqm->dev;

	अगर (!KFD_IS_SOC15(dev->device_info->asic_family)) अणु
		/* On pre-SOC15 chips we need to use the queue ID to
		 * preserve the user mode ABI.
		 */
		q->करोorbell_id = q->properties.queue_id;
	पूर्ण अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
			q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		/* For SDMA queues on SOC15 with 8-byte करोorbell, use अटल
		 * करोorbell assignments based on the engine and queue id.
		 * The करोobell index distance between RLC (2*i) and (2*i+1)
		 * क्रम a SDMA engine is 512.
		 */
		uपूर्णांक32_t *idx_offset =
				dev->shared_resources.sdma_करोorbell_idx;

		q->करोorbell_id = idx_offset[q->properties.sdma_engine_id]
			+ (q->properties.sdma_queue_id & 1)
			* KFD_QUEUE_DOORBELL_MIRROR_OFFSET
			+ (q->properties.sdma_queue_id >> 1);
	पूर्ण अन्यथा अणु
		/* For CP queues on SOC15 reserve a मुक्त करोorbell ID */
		अचिन्हित पूर्णांक found;

		found = find_first_zero_bit(qpd->करोorbell_biपंचांगap,
					    KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);
		अगर (found >= KFD_MAX_NUM_OF_QUEUES_PER_PROCESS) अणु
			pr_debug("No doorbells available");
			वापस -EBUSY;
		पूर्ण
		set_bit(found, qpd->करोorbell_biपंचांगap);
		q->करोorbell_id = found;
	पूर्ण

	q->properties.करोorbell_off =
		kfd_get_करोorbell_dw_offset_in_bar(dev, qpd_to_pdd(qpd),
					  q->करोorbell_id);
	वापस 0;
पूर्ण

अटल व्योम deallocate_करोorbell(काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q)
अणु
	अचिन्हित पूर्णांक old;
	काष्ठा kfd_dev *dev = qpd->dqm->dev;

	अगर (!KFD_IS_SOC15(dev->device_info->asic_family) ||
	    q->properties.type == KFD_QUEUE_TYPE_SDMA ||
	    q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		वापस;

	old = test_and_clear_bit(q->करोorbell_id, qpd->करोorbell_biपंचांगap);
	WARN_ON(!old);
पूर्ण

अटल पूर्णांक allocate_vmid(काष्ठा device_queue_manager *dqm,
			काष्ठा qcm_process_device *qpd,
			काष्ठा queue *q)
अणु
	पूर्णांक allocated_vmid = -1, i;

	क्रम (i = dqm->dev->vm_info.first_vmid_kfd;
			i <= dqm->dev->vm_info.last_vmid_kfd; i++) अणु
		अगर (!dqm->vmid_pasid[i]) अणु
			allocated_vmid = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (allocated_vmid < 0) अणु
		pr_err("no more vmid to allocate\n");
		वापस -ENOSPC;
	पूर्ण

	pr_debug("vmid allocated: %d\n", allocated_vmid);

	dqm->vmid_pasid[allocated_vmid] = q->process->pasid;

	set_pasid_vmid_mapping(dqm, q->process->pasid, allocated_vmid);

	qpd->vmid = allocated_vmid;
	q->properties.vmid = allocated_vmid;

	program_sh_mem_settings(dqm, qpd);

	/* qpd->page_table_base is set earlier when रेजिस्टर_process()
	 * is called, i.e. when the first queue is created.
	 */
	dqm->dev->kfd2kgd->set_vm_context_page_table_base(dqm->dev->kgd,
			qpd->vmid,
			qpd->page_table_base);
	/* invalidate the VM context after pasid and vmid mapping is set up */
	kfd_flush_tlb(qpd_to_pdd(qpd));

	अगर (dqm->dev->kfd2kgd->set_scratch_backing_va)
		dqm->dev->kfd2kgd->set_scratch_backing_va(dqm->dev->kgd,
				qpd->sh_hidden_निजी_base, qpd->vmid);

	वापस 0;
पूर्ण

अटल पूर्णांक flush_texture_cache_nocpsch(काष्ठा kfd_dev *kdev,
				काष्ठा qcm_process_device *qpd)
अणु
	स्थिर काष्ठा packet_manager_funcs *pmf = qpd->dqm->packets.pmf;
	पूर्णांक ret;

	अगर (!qpd->ib_kaddr)
		वापस -ENOMEM;

	ret = pmf->release_mem(qpd->ib_base, (uपूर्णांक32_t *)qpd->ib_kaddr);
	अगर (ret)
		वापस ret;

	वापस amdgpu_amdkfd_submit_ib(kdev->kgd, KGD_ENGINE_MEC1, qpd->vmid,
				qpd->ib_base, (uपूर्णांक32_t *)qpd->ib_kaddr,
				pmf->release_mem_size / माप(uपूर्णांक32_t));
पूर्ण

अटल व्योम deallocate_vmid(काष्ठा device_queue_manager *dqm,
				काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q)
अणु
	/* On GFX v7, CP करोesn't flush TC at dequeue */
	अगर (q->device->device_info->asic_family == CHIP_HAWAII)
		अगर (flush_texture_cache_nocpsch(q->device, qpd))
			pr_err("Failed to flush TC\n");

	kfd_flush_tlb(qpd_to_pdd(qpd));

	/* Release the vmid mapping */
	set_pasid_vmid_mapping(dqm, 0, qpd->vmid);
	dqm->vmid_pasid[qpd->vmid] = 0;

	qpd->vmid = 0;
	q->properties.vmid = 0;
पूर्ण

अटल पूर्णांक create_queue_nocpsch(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा mqd_manager *mqd_mgr;
	पूर्णांक retval;

	dqm_lock(dqm);

	अगर (dqm->total_queue_count >= max_num_of_queues_per_device) अणु
		pr_warn("Can't create new usermode queue because %d queues were already created\n",
				dqm->total_queue_count);
		retval = -EPERM;
		जाओ out_unlock;
	पूर्ण

	अगर (list_empty(&qpd->queues_list)) अणु
		retval = allocate_vmid(dqm, qpd, q);
		अगर (retval)
			जाओ out_unlock;
	पूर्ण
	q->properties.vmid = qpd->vmid;
	/*
	 * Eviction state logic: mark all queues as evicted, even ones
	 * not currently active. Restoring inactive queues later only
	 * updates the is_evicted flag but is a no-op otherwise.
	 */
	q->properties.is_evicted = !!qpd->evicted;

	q->properties.tba_addr = qpd->tba_addr;
	q->properties.पंचांगa_addr = qpd->पंचांगa_addr;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];
	अगर (q->properties.type == KFD_QUEUE_TYPE_COMPUTE) अणु
		retval = allocate_hqd(dqm, q);
		अगर (retval)
			जाओ deallocate_vmid;
		pr_debug("Loading mqd to hqd on pipe %d, queue %d\n",
			q->pipe, q->queue);
	पूर्ण अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		retval = allocate_sdma_queue(dqm, q);
		अगर (retval)
			जाओ deallocate_vmid;
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	पूर्ण

	retval = allocate_करोorbell(qpd, q);
	अगर (retval)
		जाओ out_deallocate_hqd;

	/* Temporarily release dqm lock to aव्योम a circular lock dependency */
	dqm_unlock(dqm);
	q->mqd_mem_obj = mqd_mgr->allocate_mqd(mqd_mgr->dev, &q->properties);
	dqm_lock(dqm);

	अगर (!q->mqd_mem_obj) अणु
		retval = -ENOMEM;
		जाओ out_deallocate_करोorbell;
	पूर्ण
	mqd_mgr->init_mqd(mqd_mgr, &q->mqd, q->mqd_mem_obj,
				&q->gart_mqd_addr, &q->properties);
	अगर (q->properties.is_active) अणु
		अगर (!dqm->sched_running) अणु
			WARN_ONCE(1, "Load non-HWS mqd while stopped\n");
			जाओ add_queue_to_list;
		पूर्ण

		अगर (WARN(q->process->mm != current->mm,
					"should only run in user thread"))
			retval = -EFAULT;
		अन्यथा
			retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd, q->pipe,
					q->queue, &q->properties, current->mm);
		अगर (retval)
			जाओ out_मुक्त_mqd;
	पूर्ण

add_queue_to_list:
	list_add(&q->list, &qpd->queues_list);
	qpd->queue_count++;
	अगर (q->properties.is_active)
		increment_queue_count(dqm, q->properties.type);

	/*
	 * Unconditionally increment this counter, regardless of the queue's
	 * type or whether the queue is active.
	 */
	dqm->total_queue_count++;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);
	जाओ out_unlock;

out_मुक्त_mqd:
	mqd_mgr->मुक्त_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);
out_deallocate_करोorbell:
	deallocate_करोorbell(qpd, q);
out_deallocate_hqd:
	अगर (q->properties.type == KFD_QUEUE_TYPE_COMPUTE)
		deallocate_hqd(dqm, q);
	अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		deallocate_sdma_queue(dqm, q);
deallocate_vmid:
	अगर (list_empty(&qpd->queues_list))
		deallocate_vmid(dqm, qpd, q);
out_unlock:
	dqm_unlock(dqm);
	वापस retval;
पूर्ण

अटल पूर्णांक allocate_hqd(काष्ठा device_queue_manager *dqm, काष्ठा queue *q)
अणु
	bool set;
	पूर्णांक pipe, bit, i;

	set = false;

	क्रम (pipe = dqm->next_pipe_to_allocate, i = 0;
			i < get_pipes_per_mec(dqm);
			pipe = ((pipe + 1) % get_pipes_per_mec(dqm)), ++i) अणु

		अगर (!is_pipe_enabled(dqm, 0, pipe))
			जारी;

		अगर (dqm->allocated_queues[pipe] != 0) अणु
			bit = ffs(dqm->allocated_queues[pipe]) - 1;
			dqm->allocated_queues[pipe] &= ~(1 << bit);
			q->pipe = pipe;
			q->queue = bit;
			set = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!set)
		वापस -EBUSY;

	pr_debug("hqd slot - pipe %d, queue %d\n", q->pipe, q->queue);
	/* horizontal hqd allocation */
	dqm->next_pipe_to_allocate = (pipe + 1) % get_pipes_per_mec(dqm);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम deallocate_hqd(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q)
अणु
	dqm->allocated_queues[q->pipe] |= (1 << q->queue);
पूर्ण

/* Access to DQM has to be locked beक्रमe calling destroy_queue_nocpsch_locked
 * to aव्योम asynchronized access
 */
अटल पूर्णांक destroy_queue_nocpsch_locked(काष्ठा device_queue_manager *dqm,
				काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q)
अणु
	पूर्णांक retval;
	काष्ठा mqd_manager *mqd_mgr;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	अगर (q->properties.type == KFD_QUEUE_TYPE_COMPUTE)
		deallocate_hqd(dqm, q);
	अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA)
		deallocate_sdma_queue(dqm, q);
	अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		deallocate_sdma_queue(dqm, q);
	अन्यथा अणु
		pr_debug("q->properties.type %d is invalid\n",
				q->properties.type);
		वापस -EINVAL;
	पूर्ण
	dqm->total_queue_count--;

	deallocate_करोorbell(qpd, q);

	अगर (!dqm->sched_running) अणु
		WARN_ONCE(1, "Destroy non-HWS queue while stopped\n");
		वापस 0;
	पूर्ण

	retval = mqd_mgr->destroy_mqd(mqd_mgr, q->mqd,
				KFD_PREEMPT_TYPE_WAVEFRONT_RESET,
				KFD_UNMAP_LATENCY_MS,
				q->pipe, q->queue);
	अगर (retval == -ETIME)
		qpd->reset_wavefronts = true;


	mqd_mgr->मुक्त_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);

	list_del(&q->list);
	अगर (list_empty(&qpd->queues_list)) अणु
		अगर (qpd->reset_wavefronts) अणु
			pr_warn("Resetting wave fronts (nocpsch) on dev %p\n",
					dqm->dev);
			/* dbgdev_wave_reset_wavefronts has to be called beक्रमe
			 * deallocate_vmid(), i.e. when vmid is still in use.
			 */
			dbgdev_wave_reset_wavefronts(dqm->dev,
					qpd->pqm->process);
			qpd->reset_wavefronts = false;
		पूर्ण

		deallocate_vmid(dqm, qpd, q);
	पूर्ण
	qpd->queue_count--;
	अगर (q->properties.is_active) अणु
		decrement_queue_count(dqm, q->properties.type);
		अगर (q->properties.is_gws) अणु
			dqm->gws_queue_count--;
			qpd->mapped_gws_queue = false;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक destroy_queue_nocpsch(काष्ठा device_queue_manager *dqm,
				काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q)
अणु
	पूर्णांक retval;
	uपूर्णांक64_t sdma_val = 0;
	काष्ठा kfd_process_device *pdd = qpd_to_pdd(qpd);

	/* Get the SDMA queue stats */
	अगर ((q->properties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) अणु
		retval = पढ़ो_sdma_queue_counter((uपूर्णांक64_t __user *)q->properties.पढ़ो_ptr,
							&sdma_val);
		अगर (retval)
			pr_err("Failed to read SDMA queue counter for queue: %d\n",
				q->properties.queue_id);
	पूर्ण

	dqm_lock(dqm);
	retval = destroy_queue_nocpsch_locked(dqm, qpd, q);
	अगर (!retval)
		pdd->sdma_past_activity_counter += sdma_val;
	dqm_unlock(dqm);

	वापस retval;
पूर्ण

अटल पूर्णांक update_queue(काष्ठा device_queue_manager *dqm, काष्ठा queue *q)
अणु
	पूर्णांक retval = 0;
	काष्ठा mqd_manager *mqd_mgr;
	काष्ठा kfd_process_device *pdd;
	bool prev_active = false;

	dqm_lock(dqm);
	pdd = kfd_get_process_device_data(q->device, q->process);
	अगर (!pdd) अणु
		retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण
	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	/* Save previous activity state क्रम counters */
	prev_active = q->properties.is_active;

	/* Make sure the queue is unmapped beक्रमe updating the MQD */
	अगर (dqm->sched_policy != KFD_SCHED_POLICY_NO_HWS) अणु
		retval = unmap_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
		अगर (retval) अणु
			pr_err("unmap queue failed\n");
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (prev_active &&
		   (q->properties.type == KFD_QUEUE_TYPE_COMPUTE ||
		    q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		    q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) अणु

		अगर (!dqm->sched_running) अणु
			WARN_ONCE(1, "Update non-HWS queue while stopped\n");
			जाओ out_unlock;
		पूर्ण

		retval = mqd_mgr->destroy_mqd(mqd_mgr, q->mqd,
				KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN,
				KFD_UNMAP_LATENCY_MS, q->pipe, q->queue);
		अगर (retval) अणु
			pr_err("destroy mqd failed\n");
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	mqd_mgr->update_mqd(mqd_mgr, q->mqd, &q->properties);

	/*
	 * check active state vs. the previous state and modअगरy
	 * counter accordingly. map_queues_cpsch uses the
	 * dqm->active_queue_count to determine whether a new runlist must be
	 * uploaded.
	 */
	अगर (q->properties.is_active && !prev_active)
		increment_queue_count(dqm, q->properties.type);
	अन्यथा अगर (!q->properties.is_active && prev_active)
		decrement_queue_count(dqm, q->properties.type);

	अगर (q->gws && !q->properties.is_gws) अणु
		अगर (q->properties.is_active) अणु
			dqm->gws_queue_count++;
			pdd->qpd.mapped_gws_queue = true;
		पूर्ण
		q->properties.is_gws = true;
	पूर्ण अन्यथा अगर (!q->gws && q->properties.is_gws) अणु
		अगर (q->properties.is_active) अणु
			dqm->gws_queue_count--;
			pdd->qpd.mapped_gws_queue = false;
		पूर्ण
		q->properties.is_gws = false;
	पूर्ण

	अगर (dqm->sched_policy != KFD_SCHED_POLICY_NO_HWS)
		retval = map_queues_cpsch(dqm);
	अन्यथा अगर (q->properties.is_active &&
		 (q->properties.type == KFD_QUEUE_TYPE_COMPUTE ||
		  q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		  q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) अणु
		अगर (WARN(q->process->mm != current->mm,
			 "should only run in user thread"))
			retval = -EFAULT;
		अन्यथा
			retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd,
						   q->pipe, q->queue,
						   &q->properties, current->mm);
	पूर्ण

out_unlock:
	dqm_unlock(dqm);
	वापस retval;
पूर्ण

अटल पूर्णांक evict_process_queues_nocpsch(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा queue *q;
	काष्ठा mqd_manager *mqd_mgr;
	काष्ठा kfd_process_device *pdd;
	पूर्णांक retval, ret = 0;

	dqm_lock(dqm);
	अगर (qpd->evicted++ > 0) /* alपढ़ोy evicted, करो nothing */
		जाओ out;

	pdd = qpd_to_pdd(qpd);
	pr_debug_ratelimited("Evicting PASID 0x%x queues\n",
			    pdd->process->pasid);

	pdd->last_evict_बारtamp = get_jअगरfies_64();
	/* Mark all queues as evicted. Deactivate all active queues on
	 * the qpd.
	 */
	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		q->properties.is_evicted = true;
		अगर (!q->properties.is_active)
			जारी;

		mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
				q->properties.type)];
		q->properties.is_active = false;
		decrement_queue_count(dqm, q->properties.type);
		अगर (q->properties.is_gws) अणु
			dqm->gws_queue_count--;
			qpd->mapped_gws_queue = false;
		पूर्ण

		अगर (WARN_ONCE(!dqm->sched_running, "Evict when stopped\n"))
			जारी;

		retval = mqd_mgr->destroy_mqd(mqd_mgr, q->mqd,
				KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN,
				KFD_UNMAP_LATENCY_MS, q->pipe, q->queue);
		अगर (retval && !ret)
			/* Return the first error, but keep going to
			 * मुख्यtain a consistent eviction state
			 */
			ret = retval;
	पूर्ण

out:
	dqm_unlock(dqm);
	वापस ret;
पूर्ण

अटल पूर्णांक evict_process_queues_cpsch(काष्ठा device_queue_manager *dqm,
				      काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा queue *q;
	काष्ठा kfd_process_device *pdd;
	पूर्णांक retval = 0;

	dqm_lock(dqm);
	अगर (qpd->evicted++ > 0) /* alपढ़ोy evicted, करो nothing */
		जाओ out;

	pdd = qpd_to_pdd(qpd);
	pr_debug_ratelimited("Evicting PASID 0x%x queues\n",
			    pdd->process->pasid);

	/* Mark all queues as evicted. Deactivate all active queues on
	 * the qpd.
	 */
	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		q->properties.is_evicted = true;
		अगर (!q->properties.is_active)
			जारी;

		q->properties.is_active = false;
		decrement_queue_count(dqm, q->properties.type);
	पूर्ण
	pdd->last_evict_बारtamp = get_jअगरfies_64();
	retval = execute_queues_cpsch(dqm,
				qpd->is_debug ?
				KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES :
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);

out:
	dqm_unlock(dqm);
	वापस retval;
पूर्ण

अटल पूर्णांक restore_process_queues_nocpsch(काष्ठा device_queue_manager *dqm,
					  काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा mm_काष्ठा *mm = शून्य;
	काष्ठा queue *q;
	काष्ठा mqd_manager *mqd_mgr;
	काष्ठा kfd_process_device *pdd;
	uपूर्णांक64_t pd_base;
	uपूर्णांक64_t eviction_duration;
	पूर्णांक retval, ret = 0;

	pdd = qpd_to_pdd(qpd);
	/* Retrieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_process_page_dir(pdd->vm);

	dqm_lock(dqm);
	अगर (WARN_ON_ONCE(!qpd->evicted)) /* alपढ़ोy restored, करो nothing */
		जाओ out;
	अगर (qpd->evicted > 1) अणु /* ref count still > 0, decrement & quit */
		qpd->evicted--;
		जाओ out;
	पूर्ण

	pr_debug_ratelimited("Restoring PASID 0x%x queues\n",
			    pdd->process->pasid);

	/* Update PD Base in QPD */
	qpd->page_table_base = pd_base;
	pr_debug("Updated PD address to 0x%llx\n", pd_base);

	अगर (!list_empty(&qpd->queues_list)) अणु
		dqm->dev->kfd2kgd->set_vm_context_page_table_base(
				dqm->dev->kgd,
				qpd->vmid,
				qpd->page_table_base);
		kfd_flush_tlb(pdd);
	पूर्ण

	/* Take a safe reference to the mm_काष्ठा, which may otherwise
	 * disappear even जबतक the kfd_process is still referenced.
	 */
	mm = get_task_mm(pdd->process->lead_thपढ़ो);
	अगर (!mm) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* Remove the eviction flags. Activate queues that are not
	 * inactive क्रम other reasons.
	 */
	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		q->properties.is_evicted = false;
		अगर (!QUEUE_IS_ACTIVE(q->properties))
			जारी;

		mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
				q->properties.type)];
		q->properties.is_active = true;
		increment_queue_count(dqm, q->properties.type);
		अगर (q->properties.is_gws) अणु
			dqm->gws_queue_count++;
			qpd->mapped_gws_queue = true;
		पूर्ण

		अगर (WARN_ONCE(!dqm->sched_running, "Restore when stopped\n"))
			जारी;

		retval = mqd_mgr->load_mqd(mqd_mgr, q->mqd, q->pipe,
				       q->queue, &q->properties, mm);
		अगर (retval && !ret)
			/* Return the first error, but keep going to
			 * मुख्यtain a consistent eviction state
			 */
			ret = retval;
	पूर्ण
	qpd->evicted = 0;
	eviction_duration = get_jअगरfies_64() - pdd->last_evict_बारtamp;
	atomic64_add(eviction_duration, &pdd->evict_duration_counter);
out:
	अगर (mm)
		mmput(mm);
	dqm_unlock(dqm);
	वापस ret;
पूर्ण

अटल पूर्णांक restore_process_queues_cpsch(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा queue *q;
	काष्ठा kfd_process_device *pdd;
	uपूर्णांक64_t pd_base;
	uपूर्णांक64_t eviction_duration;
	पूर्णांक retval = 0;

	pdd = qpd_to_pdd(qpd);
	/* Retrieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_process_page_dir(pdd->vm);

	dqm_lock(dqm);
	अगर (WARN_ON_ONCE(!qpd->evicted)) /* alपढ़ोy restored, करो nothing */
		जाओ out;
	अगर (qpd->evicted > 1) अणु /* ref count still > 0, decrement & quit */
		qpd->evicted--;
		जाओ out;
	पूर्ण

	pr_debug_ratelimited("Restoring PASID 0x%x queues\n",
			    pdd->process->pasid);

	/* Update PD Base in QPD */
	qpd->page_table_base = pd_base;
	pr_debug("Updated PD address to 0x%llx\n", pd_base);

	/* activate all active queues on the qpd */
	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		q->properties.is_evicted = false;
		अगर (!QUEUE_IS_ACTIVE(q->properties))
			जारी;

		q->properties.is_active = true;
		increment_queue_count(dqm, q->properties.type);
	पूर्ण
	retval = execute_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
	qpd->evicted = 0;
	eviction_duration = get_jअगरfies_64() - pdd->last_evict_बारtamp;
	atomic64_add(eviction_duration, &pdd->evict_duration_counter);
out:
	dqm_unlock(dqm);
	वापस retval;
पूर्ण

अटल पूर्णांक रेजिस्टर_process(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा device_process_node *n;
	काष्ठा kfd_process_device *pdd;
	uपूर्णांक64_t pd_base;
	पूर्णांक retval;

	n = kzalloc(माप(*n), GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	n->qpd = qpd;

	pdd = qpd_to_pdd(qpd);
	/* Retrieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_process_page_dir(pdd->vm);

	dqm_lock(dqm);
	list_add(&n->list, &dqm->queues);

	/* Update PD Base in QPD */
	qpd->page_table_base = pd_base;
	pr_debug("Updated PD address to 0x%llx\n", pd_base);

	retval = dqm->asic_ops.update_qpd(dqm, qpd);

	dqm->processes_count++;

	dqm_unlock(dqm);

	/* Outside the DQM lock because under the DQM lock we can't करो
	 * reclaim or take other locks that others hold जबतक reclaiming.
	 */
	kfd_inc_compute_active(dqm->dev);

	वापस retval;
पूर्ण

अटल पूर्णांक unरेजिस्टर_process(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd)
अणु
	पूर्णांक retval;
	काष्ठा device_process_node *cur, *next;

	pr_debug("qpd->queues_list is %s\n",
			list_empty(&qpd->queues_list) ? "empty" : "not empty");

	retval = 0;
	dqm_lock(dqm);

	list_क्रम_each_entry_safe(cur, next, &dqm->queues, list) अणु
		अगर (qpd == cur->qpd) अणु
			list_del(&cur->list);
			kमुक्त(cur);
			dqm->processes_count--;
			जाओ out;
		पूर्ण
	पूर्ण
	/* qpd not found in dqm list */
	retval = 1;
out:
	dqm_unlock(dqm);

	/* Outside the DQM lock because under the DQM lock we can't करो
	 * reclaim or take other locks that others hold जबतक reclaiming.
	 */
	अगर (!retval)
		kfd_dec_compute_active(dqm->dev);

	वापस retval;
पूर्ण

अटल पूर्णांक
set_pasid_vmid_mapping(काष्ठा device_queue_manager *dqm, u32 pasid,
			अचिन्हित पूर्णांक vmid)
अणु
	वापस dqm->dev->kfd2kgd->set_pasid_vmid_mapping(
						dqm->dev->kgd, pasid, vmid);
पूर्ण

अटल व्योम init_पूर्णांकerrupts(काष्ठा device_queue_manager *dqm)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0 ; i < get_pipes_per_mec(dqm) ; i++)
		अगर (is_pipe_enabled(dqm, 0, i))
			dqm->dev->kfd2kgd->init_पूर्णांकerrupts(dqm->dev->kgd, i);
पूर्ण

अटल पूर्णांक initialize_nocpsch(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक pipe, queue;

	pr_debug("num of pipes: %d\n", get_pipes_per_mec(dqm));

	dqm->allocated_queues = kसुस्मृति(get_pipes_per_mec(dqm),
					माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!dqm->allocated_queues)
		वापस -ENOMEM;

	mutex_init(&dqm->lock_hidden);
	INIT_LIST_HEAD(&dqm->queues);
	dqm->active_queue_count = dqm->next_pipe_to_allocate = 0;
	dqm->active_cp_queue_count = 0;
	dqm->gws_queue_count = 0;

	क्रम (pipe = 0; pipe < get_pipes_per_mec(dqm); pipe++) अणु
		पूर्णांक pipe_offset = pipe * get_queues_per_pipe(dqm);

		क्रम (queue = 0; queue < get_queues_per_pipe(dqm); queue++)
			अगर (test_bit(pipe_offset + queue,
				     dqm->dev->shared_resources.cp_queue_biपंचांगap))
				dqm->allocated_queues[pipe] |= 1 << queue;
	पूर्ण

	स_रखो(dqm->vmid_pasid, 0, माप(dqm->vmid_pasid));

	dqm->sdma_biपंचांगap = ~0ULL >> (64 - get_num_sdma_queues(dqm));
	dqm->xgmi_sdma_biपंचांगap = ~0ULL >> (64 - get_num_xgmi_sdma_queues(dqm));

	वापस 0;
पूर्ण

अटल व्योम uninitialize(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक i;

	WARN_ON(dqm->active_queue_count > 0 || dqm->processes_count > 0);

	kमुक्त(dqm->allocated_queues);
	क्रम (i = 0 ; i < KFD_MQD_TYPE_MAX ; i++)
		kमुक्त(dqm->mqd_mgrs[i]);
	mutex_destroy(&dqm->lock_hidden);
पूर्ण

अटल पूर्णांक start_nocpsch(काष्ठा device_queue_manager *dqm)
अणु
	pr_info("SW scheduler is used");
	init_पूर्णांकerrupts(dqm);
	
	अगर (dqm->dev->device_info->asic_family == CHIP_HAWAII)
		वापस pm_init(&dqm->packets, dqm);
	dqm->sched_running = true;

	वापस 0;
पूर्ण

अटल पूर्णांक stop_nocpsch(काष्ठा device_queue_manager *dqm)
अणु
	अगर (dqm->dev->device_info->asic_family == CHIP_HAWAII)
		pm_uninit(&dqm->packets, false);
	dqm->sched_running = false;

	वापस 0;
पूर्ण

अटल व्योम pre_reset(काष्ठा device_queue_manager *dqm)
अणु
	dqm_lock(dqm);
	dqm->is_resetting = true;
	dqm_unlock(dqm);
पूर्ण

अटल पूर्णांक allocate_sdma_queue(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q)
अणु
	पूर्णांक bit;

	अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA) अणु
		अगर (dqm->sdma_biपंचांगap == 0) अणु
			pr_err("No more SDMA queue to allocate\n");
			वापस -ENOMEM;
		पूर्ण

		bit = __ffs64(dqm->sdma_biपंचांगap);
		dqm->sdma_biपंचांगap &= ~(1ULL << bit);
		q->sdma_id = bit;
		q->properties.sdma_engine_id = q->sdma_id %
				get_num_sdma_engines(dqm);
		q->properties.sdma_queue_id = q->sdma_id /
				get_num_sdma_engines(dqm);
	पूर्ण अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		अगर (dqm->xgmi_sdma_biपंचांगap == 0) अणु
			pr_err("No more XGMI SDMA queue to allocate\n");
			वापस -ENOMEM;
		पूर्ण
		bit = __ffs64(dqm->xgmi_sdma_biपंचांगap);
		dqm->xgmi_sdma_biपंचांगap &= ~(1ULL << bit);
		q->sdma_id = bit;
		/* sdma_engine_id is sdma id including
		 * both PCIe-optimized SDMAs and XGMI-
		 * optimized SDMAs. The calculation below
		 * assumes the first N engines are always
		 * PCIe-optimized ones
		 */
		q->properties.sdma_engine_id = get_num_sdma_engines(dqm) +
				q->sdma_id % get_num_xgmi_sdma_engines(dqm);
		q->properties.sdma_queue_id = q->sdma_id /
				get_num_xgmi_sdma_engines(dqm);
	पूर्ण

	pr_debug("SDMA engine id: %d\n", q->properties.sdma_engine_id);
	pr_debug("SDMA queue id: %d\n", q->properties.sdma_queue_id);

	वापस 0;
पूर्ण

अटल व्योम deallocate_sdma_queue(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q)
अणु
	अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA) अणु
		अगर (q->sdma_id >= get_num_sdma_queues(dqm))
			वापस;
		dqm->sdma_biपंचांगap |= (1ULL << q->sdma_id);
	पूर्ण अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		अगर (q->sdma_id >= get_num_xgmi_sdma_queues(dqm))
			वापस;
		dqm->xgmi_sdma_biपंचांगap |= (1ULL << q->sdma_id);
	पूर्ण
पूर्ण

/*
 * Device Queue Manager implementation क्रम cp scheduler
 */

अटल पूर्णांक set_sched_resources(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक i, mec;
	काष्ठा scheduling_resources res;

	res.vmid_mask = dqm->dev->shared_resources.compute_vmid_biपंचांगap;

	res.queue_mask = 0;
	क्रम (i = 0; i < KGD_MAX_QUEUES; ++i) अणु
		mec = (i / dqm->dev->shared_resources.num_queue_per_pipe)
			/ dqm->dev->shared_resources.num_pipe_per_mec;

		अगर (!test_bit(i, dqm->dev->shared_resources.cp_queue_biपंचांगap))
			जारी;

		/* only acquire queues from the first MEC */
		अगर (mec > 0)
			जारी;

		/* This situation may be hit in the future अगर a new HW
		 * generation exposes more than 64 queues. If so, the
		 * definition of res.queue_mask needs updating
		 */
		अगर (WARN_ON(i >= (माप(res.queue_mask)*8))) अणु
			pr_err("Invalid queue enabled by amdgpu: %d\n", i);
			अवरोध;
		पूर्ण

		res.queue_mask |= 1ull
			<< amdgpu_queue_mask_bit_to_set_resource_bit(
				(काष्ठा amdgpu_device *)dqm->dev->kgd, i);
	पूर्ण
	res.gws_mask = ~0ull;
	res.oac_mask = res.gds_heap_base = res.gds_heap_size = 0;

	pr_debug("Scheduling resources:\n"
			"vmid mask: 0x%8X\n"
			"queue mask: 0x%8llX\n",
			res.vmid_mask, res.queue_mask);

	वापस pm_send_set_resources(&dqm->packets, &res);
पूर्ण

अटल पूर्णांक initialize_cpsch(काष्ठा device_queue_manager *dqm)
अणु
	uपूर्णांक64_t num_sdma_queues;
	uपूर्णांक64_t num_xgmi_sdma_queues;

	pr_debug("num of pipes: %d\n", get_pipes_per_mec(dqm));

	mutex_init(&dqm->lock_hidden);
	INIT_LIST_HEAD(&dqm->queues);
	dqm->active_queue_count = dqm->processes_count = 0;
	dqm->active_cp_queue_count = 0;
	dqm->gws_queue_count = 0;
	dqm->active_runlist = false;

	num_sdma_queues = get_num_sdma_queues(dqm);
	अगर (num_sdma_queues >= BITS_PER_TYPE(dqm->sdma_biपंचांगap))
		dqm->sdma_biपंचांगap = ULदीर्घ_उच्च;
	अन्यथा
		dqm->sdma_biपंचांगap = (BIT_ULL(num_sdma_queues) - 1);

	num_xgmi_sdma_queues = get_num_xgmi_sdma_queues(dqm);
	अगर (num_xgmi_sdma_queues >= BITS_PER_TYPE(dqm->xgmi_sdma_biपंचांगap))
		dqm->xgmi_sdma_biपंचांगap = ULदीर्घ_उच्च;
	अन्यथा
		dqm->xgmi_sdma_biपंचांगap = (BIT_ULL(num_xgmi_sdma_queues) - 1);

	INIT_WORK(&dqm->hw_exception_work, kfd_process_hw_exception);

	वापस 0;
पूर्ण

अटल पूर्णांक start_cpsch(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक retval;

	retval = 0;

	retval = pm_init(&dqm->packets, dqm);
	अगर (retval)
		जाओ fail_packet_manager_init;

	retval = set_sched_resources(dqm);
	अगर (retval)
		जाओ fail_set_sched_resources;

	pr_debug("Allocating fence memory\n");

	/* allocate fence memory on the gart */
	retval = kfd_gtt_sa_allocate(dqm->dev, माप(*dqm->fence_addr),
					&dqm->fence_mem);

	अगर (retval)
		जाओ fail_allocate_vidmem;

	dqm->fence_addr = (uपूर्णांक64_t *)dqm->fence_mem->cpu_ptr;
	dqm->fence_gpu_addr = dqm->fence_mem->gpu_addr;

	init_पूर्णांकerrupts(dqm);

	dqm_lock(dqm);
	/* clear hang status when driver try to start the hw scheduler */
	dqm->is_hws_hang = false;
	dqm->is_resetting = false;
	dqm->sched_running = true;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
	dqm_unlock(dqm);

	वापस 0;
fail_allocate_vidmem:
fail_set_sched_resources:
	pm_uninit(&dqm->packets, false);
fail_packet_manager_init:
	वापस retval;
पूर्ण

अटल पूर्णांक stop_cpsch(काष्ठा device_queue_manager *dqm)
अणु
	bool hanging;

	dqm_lock(dqm);
	अगर (!dqm->is_hws_hang)
		unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES, 0);
	hanging = dqm->is_hws_hang || dqm->is_resetting;
	dqm->sched_running = false;
	dqm_unlock(dqm);

	pm_release_ib(&dqm->packets);

	kfd_gtt_sa_मुक्त(dqm->dev, dqm->fence_mem);
	pm_uninit(&dqm->packets, hanging);

	वापस 0;
पूर्ण

अटल पूर्णांक create_kernel_queue_cpsch(काष्ठा device_queue_manager *dqm,
					काष्ठा kernel_queue *kq,
					काष्ठा qcm_process_device *qpd)
अणु
	dqm_lock(dqm);
	अगर (dqm->total_queue_count >= max_num_of_queues_per_device) अणु
		pr_warn("Can't create new kernel queue because %d queues were already created\n",
				dqm->total_queue_count);
		dqm_unlock(dqm);
		वापस -EPERM;
	पूर्ण

	/*
	 * Unconditionally increment this counter, regardless of the queue's
	 * type or whether the queue is active.
	 */
	dqm->total_queue_count++;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	list_add(&kq->list, &qpd->priv_queue_list);
	increment_queue_count(dqm, kq->queue->properties.type);
	qpd->is_debug = true;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
	dqm_unlock(dqm);

	वापस 0;
पूर्ण

अटल व्योम destroy_kernel_queue_cpsch(काष्ठा device_queue_manager *dqm,
					काष्ठा kernel_queue *kq,
					काष्ठा qcm_process_device *qpd)
अणु
	dqm_lock(dqm);
	list_del(&kq->list);
	decrement_queue_count(dqm, kq->queue->properties.type);
	qpd->is_debug = false;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES, 0);
	/*
	 * Unconditionally decrement this counter, regardless of the queue's
	 * type.
	 */
	dqm->total_queue_count--;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);
	dqm_unlock(dqm);
पूर्ण

अटल पूर्णांक create_queue_cpsch(काष्ठा device_queue_manager *dqm, काष्ठा queue *q,
			काष्ठा qcm_process_device *qpd)
अणु
	पूर्णांक retval;
	काष्ठा mqd_manager *mqd_mgr;

	अगर (dqm->total_queue_count >= max_num_of_queues_per_device) अणु
		pr_warn("Can't create new usermode queue because %d queues were already created\n",
				dqm->total_queue_count);
		retval = -EPERM;
		जाओ out;
	पूर्ण

	अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		dqm_lock(dqm);
		retval = allocate_sdma_queue(dqm, q);
		dqm_unlock(dqm);
		अगर (retval)
			जाओ out;
	पूर्ण

	retval = allocate_करोorbell(qpd, q);
	अगर (retval)
		जाओ out_deallocate_sdma_queue;

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	q->properties.tba_addr = qpd->tba_addr;
	q->properties.पंचांगa_addr = qpd->पंचांगa_addr;
	q->mqd_mem_obj = mqd_mgr->allocate_mqd(mqd_mgr->dev, &q->properties);
	अगर (!q->mqd_mem_obj) अणु
		retval = -ENOMEM;
		जाओ out_deallocate_करोorbell;
	पूर्ण

	dqm_lock(dqm);
	/*
	 * Eviction state logic: mark all queues as evicted, even ones
	 * not currently active. Restoring inactive queues later only
	 * updates the is_evicted flag but is a no-op otherwise.
	 */
	q->properties.is_evicted = !!qpd->evicted;
	mqd_mgr->init_mqd(mqd_mgr, &q->mqd, q->mqd_mem_obj,
				&q->gart_mqd_addr, &q->properties);

	list_add(&q->list, &qpd->queues_list);
	qpd->queue_count++;

	अगर (q->properties.is_active) अणु
		increment_queue_count(dqm, q->properties.type);

		execute_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
	पूर्ण

	/*
	 * Unconditionally increment this counter, regardless of the queue's
	 * type or whether the queue is active.
	 */
	dqm->total_queue_count++;

	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	dqm_unlock(dqm);
	वापस retval;

out_deallocate_करोorbell:
	deallocate_करोorbell(qpd, q);
out_deallocate_sdma_queue:
	अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA ||
		q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI) अणु
		dqm_lock(dqm);
		deallocate_sdma_queue(dqm, q);
		dqm_unlock(dqm);
	पूर्ण
out:
	वापस retval;
पूर्ण

पूर्णांक amdkfd_fence_रुको_समयout(uपूर्णांक64_t *fence_addr,
				uपूर्णांक64_t fence_value,
				अचिन्हित पूर्णांक समयout_ms)
अणु
	अचिन्हित दीर्घ end_jअगरfies = msecs_to_jअगरfies(समयout_ms) + jअगरfies;

	जबतक (*fence_addr != fence_value) अणु
		अगर (समय_after(jअगरfies, end_jअगरfies)) अणु
			pr_err("qcm fence wait loop timeout expired\n");
			/* In HWS हाल, this is used to halt the driver thपढ़ो
			 * in order not to mess up CP states beक्रमe करोing
			 * scandumps क्रम FW debugging.
			 */
			जबतक (halt_अगर_hws_hang)
				schedule();

			वापस -ETIME;
		पूर्ण
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

/* dqm->lock mutex has to be locked beक्रमe calling this function */
अटल पूर्णांक map_queues_cpsch(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक retval;

	अगर (!dqm->sched_running)
		वापस 0;
	अगर (dqm->active_queue_count <= 0 || dqm->processes_count <= 0)
		वापस 0;
	अगर (dqm->active_runlist)
		वापस 0;

	retval = pm_send_runlist(&dqm->packets, &dqm->queues);
	pr_debug("%s sent runlist\n", __func__);
	अगर (retval) अणु
		pr_err("failed to execute runlist\n");
		वापस retval;
	पूर्ण
	dqm->active_runlist = true;

	वापस retval;
पूर्ण

/* dqm->lock mutex has to be locked beक्रमe calling this function */
अटल पूर्णांक unmap_queues_cpsch(काष्ठा device_queue_manager *dqm,
				क्रमागत kfd_unmap_queues_filter filter,
				uपूर्णांक32_t filter_param)
अणु
	पूर्णांक retval = 0;
	काष्ठा mqd_manager *mqd_mgr;

	अगर (!dqm->sched_running)
		वापस 0;
	अगर (dqm->is_hws_hang)
		वापस -EIO;
	अगर (!dqm->active_runlist)
		वापस retval;

	retval = pm_send_unmap_queue(&dqm->packets, KFD_QUEUE_TYPE_COMPUTE,
			filter, filter_param, false, 0);
	अगर (retval)
		वापस retval;

	*dqm->fence_addr = KFD_FENCE_INIT;
	pm_send_query_status(&dqm->packets, dqm->fence_gpu_addr,
				KFD_FENCE_COMPLETED);
	/* should be समयd out */
	retval = amdkfd_fence_रुको_समयout(dqm->fence_addr, KFD_FENCE_COMPLETED,
				queue_preemption_समयout_ms);
	अगर (retval) अणु
		pr_err("The cp might be in an unrecoverable state due to an unsuccessful queues preemption\n");
		dqm->is_hws_hang = true;
		/* It's possible we're detecting a HWS hang in the
		 * middle of a GPU reset. No need to schedule another
		 * reset in this हाल.
		 */
		अगर (!dqm->is_resetting)
			schedule_work(&dqm->hw_exception_work);
		वापस retval;
	पूर्ण

	/* In the current MEC firmware implementation, अगर compute queue
	 * करोesn't response to the preemption request in समय, HIQ will
	 * abanकरोn the unmap request without वापसing any समयout error
	 * to driver. Instead, MEC firmware will log the करोorbell of the
	 * unresponding compute queue to HIQ.MQD.queue_करोorbell_id fields.
	 * To make sure the queue unmap was successful, driver need to
	 * check those fields
	 */
	mqd_mgr = dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ];
	अगर (mqd_mgr->पढ़ो_करोorbell_id(dqm->packets.priv_queue->queue->mqd)) अणु
		pr_err("HIQ MQD's queue_doorbell_id0 is not 0, Queue preemption time out\n");
		जबतक (halt_अगर_hws_hang)
			schedule();
		वापस -ETIME;
	पूर्ण

	pm_release_ib(&dqm->packets);
	dqm->active_runlist = false;

	वापस retval;
पूर्ण

/* dqm->lock mutex has to be locked beक्रमe calling this function */
अटल पूर्णांक execute_queues_cpsch(काष्ठा device_queue_manager *dqm,
				क्रमागत kfd_unmap_queues_filter filter,
				uपूर्णांक32_t filter_param)
अणु
	पूर्णांक retval;

	अगर (dqm->is_hws_hang)
		वापस -EIO;
	retval = unmap_queues_cpsch(dqm, filter, filter_param);
	अगर (retval)
		वापस retval;

	वापस map_queues_cpsch(dqm);
पूर्ण

अटल पूर्णांक destroy_queue_cpsch(काष्ठा device_queue_manager *dqm,
				काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q)
अणु
	पूर्णांक retval;
	काष्ठा mqd_manager *mqd_mgr;
	uपूर्णांक64_t sdma_val = 0;
	काष्ठा kfd_process_device *pdd = qpd_to_pdd(qpd);

	/* Get the SDMA queue stats */
	अगर ((q->properties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) अणु
		retval = पढ़ो_sdma_queue_counter((uपूर्णांक64_t __user *)q->properties.पढ़ो_ptr,
							&sdma_val);
		अगर (retval)
			pr_err("Failed to read SDMA queue counter for queue: %d\n",
				q->properties.queue_id);
	पूर्ण

	retval = 0;

	/* हटाओ queue from list to prevent rescheduling after preemption */
	dqm_lock(dqm);

	अगर (qpd->is_debug) अणु
		/*
		 * error, currently we करो not allow to destroy a queue
		 * of a currently debugged process
		 */
		retval = -EBUSY;
		जाओ failed_try_destroy_debugged_queue;

	पूर्ण

	mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
			q->properties.type)];

	deallocate_करोorbell(qpd, q);

	अगर ((q->properties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) अणु
		deallocate_sdma_queue(dqm, q);
		pdd->sdma_past_activity_counter += sdma_val;
	पूर्ण

	list_del(&q->list);
	qpd->queue_count--;
	अगर (q->properties.is_active) अणु
		decrement_queue_count(dqm, q->properties.type);
		retval = execute_queues_cpsch(dqm,
				KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES, 0);
		अगर (retval == -ETIME)
			qpd->reset_wavefronts = true;
		अगर (q->properties.is_gws) अणु
			dqm->gws_queue_count--;
			qpd->mapped_gws_queue = false;
		पूर्ण
	पूर्ण

	/*
	 * Unconditionally decrement this counter, regardless of the queue's
	 * type
	 */
	dqm->total_queue_count--;
	pr_debug("Total of %d queues are accountable so far\n",
			dqm->total_queue_count);

	dqm_unlock(dqm);

	/* Do मुक्त_mqd after dqm_unlock(dqm) to aव्योम circular locking */
	mqd_mgr->मुक्त_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);

	वापस retval;

failed_try_destroy_debugged_queue:

	dqm_unlock(dqm);
	वापस retval;
पूर्ण

/*
 * Low bits must be 0000/FFFF as required by HW, high bits must be 0 to
 * stay in user mode.
 */
#घोषणा APE1_FIXED_BITS_MASK 0xFFFF80000000FFFFULL
/* APE1 limit is inclusive and 64K aligned. */
#घोषणा APE1_LIMIT_ALIGNMENT 0xFFFF

अटल bool set_cache_memory_policy(काष्ठा device_queue_manager *dqm,
				   काष्ठा qcm_process_device *qpd,
				   क्रमागत cache_policy शेष_policy,
				   क्रमागत cache_policy alternate_policy,
				   व्योम __user *alternate_aperture_base,
				   uपूर्णांक64_t alternate_aperture_size)
अणु
	bool retval = true;

	अगर (!dqm->asic_ops.set_cache_memory_policy)
		वापस retval;

	dqm_lock(dqm);

	अगर (alternate_aperture_size == 0) अणु
		/* base > limit disables APE1 */
		qpd->sh_mem_ape1_base = 1;
		qpd->sh_mem_ape1_limit = 0;
	पूर्ण अन्यथा अणु
		/*
		 * In FSA64, APE1_Base[63:0] = अणु 16अणुSH_MEM_APE1_BASE[31]पूर्ण,
		 *			SH_MEM_APE1_BASE[31:0], 0x0000 पूर्ण
		 * APE1_Limit[63:0] = अणु 16अणुSH_MEM_APE1_LIMIT[31]पूर्ण,
		 *			SH_MEM_APE1_LIMIT[31:0], 0xFFFF पूर्ण
		 * Verअगरy that the base and size parameters can be
		 * represented in this क्रमmat and convert them.
		 * Additionally restrict APE1 to user-mode addresses.
		 */

		uपूर्णांक64_t base = (uपूर्णांकptr_t)alternate_aperture_base;
		uपूर्णांक64_t limit = base + alternate_aperture_size - 1;

		अगर (limit <= base || (base & APE1_FIXED_BITS_MASK) != 0 ||
		   (limit & APE1_FIXED_BITS_MASK) != APE1_LIMIT_ALIGNMENT) अणु
			retval = false;
			जाओ out;
		पूर्ण

		qpd->sh_mem_ape1_base = base >> 16;
		qpd->sh_mem_ape1_limit = limit >> 16;
	पूर्ण

	retval = dqm->asic_ops.set_cache_memory_policy(
			dqm,
			qpd,
			शेष_policy,
			alternate_policy,
			alternate_aperture_base,
			alternate_aperture_size);

	अगर ((dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) && (qpd->vmid != 0))
		program_sh_mem_settings(dqm, qpd);

	pr_debug("sh_mem_config: 0x%x, ape1_base: 0x%x, ape1_limit: 0x%x\n",
		qpd->sh_mem_config, qpd->sh_mem_ape1_base,
		qpd->sh_mem_ape1_limit);

out:
	dqm_unlock(dqm);
	वापस retval;
पूर्ण

अटल पूर्णांक process_termination_nocpsch(काष्ठा device_queue_manager *dqm,
		काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा queue *q, *next;
	काष्ठा device_process_node *cur, *next_dpn;
	पूर्णांक retval = 0;
	bool found = false;

	dqm_lock(dqm);

	/* Clear all user mode queues */
	list_क्रम_each_entry_safe(q, next, &qpd->queues_list, list) अणु
		पूर्णांक ret;

		ret = destroy_queue_nocpsch_locked(dqm, qpd, q);
		अगर (ret)
			retval = ret;
	पूर्ण

	/* Unरेजिस्टर process */
	list_क्रम_each_entry_safe(cur, next_dpn, &dqm->queues, list) अणु
		अगर (qpd == cur->qpd) अणु
			list_del(&cur->list);
			kमुक्त(cur);
			dqm->processes_count--;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	dqm_unlock(dqm);

	/* Outside the DQM lock because under the DQM lock we can't करो
	 * reclaim or take other locks that others hold जबतक reclaiming.
	 */
	अगर (found)
		kfd_dec_compute_active(dqm->dev);

	वापस retval;
पूर्ण

अटल पूर्णांक get_wave_state(काष्ठा device_queue_manager *dqm,
			  काष्ठा queue *q,
			  व्योम __user *ctl_stack,
			  u32 *ctl_stack_used_size,
			  u32 *save_area_used_size)
अणु
	काष्ठा mqd_manager *mqd_mgr;
	पूर्णांक r;

	dqm_lock(dqm);

	अगर (q->properties.type != KFD_QUEUE_TYPE_COMPUTE ||
	    q->properties.is_active || !q->device->cwsr_enabled) अणु
		r = -EINVAL;
		जाओ dqm_unlock;
	पूर्ण

	mqd_mgr = dqm->mqd_mgrs[KFD_MQD_TYPE_CP];

	अगर (!mqd_mgr->get_wave_state) अणु
		r = -EINVAL;
		जाओ dqm_unlock;
	पूर्ण

	r = mqd_mgr->get_wave_state(mqd_mgr, q->mqd, ctl_stack,
			ctl_stack_used_size, save_area_used_size);

dqm_unlock:
	dqm_unlock(dqm);
	वापस r;
पूर्ण

अटल पूर्णांक process_termination_cpsch(काष्ठा device_queue_manager *dqm,
		काष्ठा qcm_process_device *qpd)
अणु
	पूर्णांक retval;
	काष्ठा queue *q, *next;
	काष्ठा kernel_queue *kq, *kq_next;
	काष्ठा mqd_manager *mqd_mgr;
	काष्ठा device_process_node *cur, *next_dpn;
	क्रमागत kfd_unmap_queues_filter filter =
		KFD_UNMAP_QUEUES_FILTER_DYNAMIC_QUEUES;
	bool found = false;

	retval = 0;

	dqm_lock(dqm);

	/* Clean all kernel queues */
	list_क्रम_each_entry_safe(kq, kq_next, &qpd->priv_queue_list, list) अणु
		list_del(&kq->list);
		decrement_queue_count(dqm, kq->queue->properties.type);
		qpd->is_debug = false;
		dqm->total_queue_count--;
		filter = KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES;
	पूर्ण

	/* Clear all user mode queues */
	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA)
			deallocate_sdma_queue(dqm, q);
		अन्यथा अगर (q->properties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
			deallocate_sdma_queue(dqm, q);

		अगर (q->properties.is_active) अणु
			decrement_queue_count(dqm, q->properties.type);
			अगर (q->properties.is_gws) अणु
				dqm->gws_queue_count--;
				qpd->mapped_gws_queue = false;
			पूर्ण
		पूर्ण

		dqm->total_queue_count--;
	पूर्ण

	/* Unरेजिस्टर process */
	list_क्रम_each_entry_safe(cur, next_dpn, &dqm->queues, list) अणु
		अगर (qpd == cur->qpd) अणु
			list_del(&cur->list);
			kमुक्त(cur);
			dqm->processes_count--;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	retval = execute_queues_cpsch(dqm, filter, 0);
	अगर ((!dqm->is_hws_hang) && (retval || qpd->reset_wavefronts)) अणु
		pr_warn("Resetting wave fronts (cpsch) on dev %p\n", dqm->dev);
		dbgdev_wave_reset_wavefronts(dqm->dev, qpd->pqm->process);
		qpd->reset_wavefronts = false;
	पूर्ण

	dqm_unlock(dqm);

	/* Outside the DQM lock because under the DQM lock we can't करो
	 * reclaim or take other locks that others hold जबतक reclaiming.
	 */
	अगर (found)
		kfd_dec_compute_active(dqm->dev);

	/* Lastly, मुक्त mqd resources.
	 * Do मुक्त_mqd() after dqm_unlock to aव्योम circular locking.
	 */
	list_क्रम_each_entry_safe(q, next, &qpd->queues_list, list) अणु
		mqd_mgr = dqm->mqd_mgrs[get_mqd_type_from_queue_type(
				q->properties.type)];
		list_del(&q->list);
		qpd->queue_count--;
		mqd_mgr->मुक्त_mqd(mqd_mgr, q->mqd, q->mqd_mem_obj);
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक init_mqd_managers(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक i, j;
	काष्ठा mqd_manager *mqd_mgr;

	क्रम (i = 0; i < KFD_MQD_TYPE_MAX; i++) अणु
		mqd_mgr = dqm->asic_ops.mqd_manager_init(i, dqm->dev);
		अगर (!mqd_mgr) अणु
			pr_err("mqd manager [%d] initialization failed\n", i);
			जाओ out_मुक्त;
		पूर्ण
		dqm->mqd_mgrs[i] = mqd_mgr;
	पूर्ण

	वापस 0;

out_मुक्त:
	क्रम (j = 0; j < i; j++) अणु
		kमुक्त(dqm->mqd_mgrs[j]);
		dqm->mqd_mgrs[j] = शून्य;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/* Allocate one hiq mqd (HWS) and all SDMA mqd in a continuous trunk*/
अटल पूर्णांक allocate_hiq_sdma_mqd(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक retval;
	काष्ठा kfd_dev *dev = dqm->dev;
	काष्ठा kfd_mem_obj *mem_obj = &dqm->hiq_sdma_mqd;
	uपूर्णांक32_t size = dqm->mqd_mgrs[KFD_MQD_TYPE_SDMA]->mqd_size *
		get_num_all_sdma_engines(dqm) *
		dev->device_info->num_sdma_queues_per_engine +
		dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ]->mqd_size;

	retval = amdgpu_amdkfd_alloc_gtt_mem(dev->kgd, size,
		&(mem_obj->gtt_mem), &(mem_obj->gpu_addr),
		(व्योम *)&(mem_obj->cpu_ptr), false);

	वापस retval;
पूर्ण

काष्ठा device_queue_manager *device_queue_manager_init(काष्ठा kfd_dev *dev)
अणु
	काष्ठा device_queue_manager *dqm;

	pr_debug("Loading device queue manager\n");

	dqm = kzalloc(माप(*dqm), GFP_KERNEL);
	अगर (!dqm)
		वापस शून्य;

	चयन (dev->device_info->asic_family) अणु
	/* HWS is not available on Hawaii. */
	हाल CHIP_HAWAII:
	/* HWS depends on CWSR क्रम समयly dequeue. CWSR is not
	 * available on Tonga.
	 *
	 * FIXME: This argument also applies to Kaveri.
	 */
	हाल CHIP_TONGA:
		dqm->sched_policy = KFD_SCHED_POLICY_NO_HWS;
		अवरोध;
	शेष:
		dqm->sched_policy = sched_policy;
		अवरोध;
	पूर्ण

	dqm->dev = dev;
	चयन (dqm->sched_policy) अणु
	हाल KFD_SCHED_POLICY_HWS:
	हाल KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION:
		/* initialize dqm क्रम cp scheduling */
		dqm->ops.create_queue = create_queue_cpsch;
		dqm->ops.initialize = initialize_cpsch;
		dqm->ops.start = start_cpsch;
		dqm->ops.stop = stop_cpsch;
		dqm->ops.pre_reset = pre_reset;
		dqm->ops.destroy_queue = destroy_queue_cpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.रेजिस्टर_process = रेजिस्टर_process;
		dqm->ops.unरेजिस्टर_process = unरेजिस्टर_process;
		dqm->ops.uninitialize = uninitialize;
		dqm->ops.create_kernel_queue = create_kernel_queue_cpsch;
		dqm->ops.destroy_kernel_queue = destroy_kernel_queue_cpsch;
		dqm->ops.set_cache_memory_policy = set_cache_memory_policy;
		dqm->ops.process_termination = process_termination_cpsch;
		dqm->ops.evict_process_queues = evict_process_queues_cpsch;
		dqm->ops.restore_process_queues = restore_process_queues_cpsch;
		dqm->ops.get_wave_state = get_wave_state;
		अवरोध;
	हाल KFD_SCHED_POLICY_NO_HWS:
		/* initialize dqm क्रम no cp scheduling */
		dqm->ops.start = start_nocpsch;
		dqm->ops.stop = stop_nocpsch;
		dqm->ops.pre_reset = pre_reset;
		dqm->ops.create_queue = create_queue_nocpsch;
		dqm->ops.destroy_queue = destroy_queue_nocpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.रेजिस्टर_process = रेजिस्टर_process;
		dqm->ops.unरेजिस्टर_process = unरेजिस्टर_process;
		dqm->ops.initialize = initialize_nocpsch;
		dqm->ops.uninitialize = uninitialize;
		dqm->ops.set_cache_memory_policy = set_cache_memory_policy;
		dqm->ops.process_termination = process_termination_nocpsch;
		dqm->ops.evict_process_queues = evict_process_queues_nocpsch;
		dqm->ops.restore_process_queues =
			restore_process_queues_nocpsch;
		dqm->ops.get_wave_state = get_wave_state;
		अवरोध;
	शेष:
		pr_err("Invalid scheduling policy %d\n", dqm->sched_policy);
		जाओ out_मुक्त;
	पूर्ण

	चयन (dev->device_info->asic_family) अणु
	हाल CHIP_CARRIZO:
		device_queue_manager_init_vi(&dqm->asic_ops);
		अवरोध;

	हाल CHIP_KAVERI:
		device_queue_manager_init_cik(&dqm->asic_ops);
		अवरोध;

	हाल CHIP_HAWAII:
		device_queue_manager_init_cik_hawaii(&dqm->asic_ops);
		अवरोध;

	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		device_queue_manager_init_vi_tonga(&dqm->asic_ops);
		अवरोध;

	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
		device_queue_manager_init_v9(&dqm->asic_ops);
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_NAVI14:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		device_queue_manager_init_v10_navi10(&dqm->asic_ops);
		अवरोध;
	शेष:
		WARN(1, "Unexpected ASIC family %u",
		     dev->device_info->asic_family);
		जाओ out_मुक्त;
	पूर्ण

	अगर (init_mqd_managers(dqm))
		जाओ out_मुक्त;

	अगर (allocate_hiq_sdma_mqd(dqm)) अणु
		pr_err("Failed to allocate hiq sdma mqd trunk buffer\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (!dqm->ops.initialize(dqm))
		वापस dqm;

out_मुक्त:
	kमुक्त(dqm);
	वापस शून्य;
पूर्ण

अटल व्योम deallocate_hiq_sdma_mqd(काष्ठा kfd_dev *dev,
				    काष्ठा kfd_mem_obj *mqd)
अणु
	WARN(!mqd, "No hiq sdma mqd trunk to free");

	amdgpu_amdkfd_मुक्त_gtt_mem(dev->kgd, mqd->gtt_mem);
पूर्ण

व्योम device_queue_manager_uninit(काष्ठा device_queue_manager *dqm)
अणु
	dqm->ops.uninitialize(dqm);
	deallocate_hiq_sdma_mqd(dqm->dev, &dqm->hiq_sdma_mqd);
	kमुक्त(dqm);
पूर्ण

पूर्णांक kfd_process_vm_fault(काष्ठा device_queue_manager *dqm, u32 pasid)
अणु
	काष्ठा kfd_process_device *pdd;
	काष्ठा kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	पूर्णांक ret = 0;

	अगर (!p)
		वापस -EINVAL;
	WARN(debug_evictions, "Evicting pid %d", p->lead_thपढ़ो->pid);
	pdd = kfd_get_process_device_data(dqm->dev, p);
	अगर (pdd)
		ret = dqm->ops.evict_process_queues(dqm, &pdd->qpd);
	kfd_unref_process(p);

	वापस ret;
पूर्ण

अटल व्योम kfd_process_hw_exception(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device_queue_manager *dqm = container_of(work,
			काष्ठा device_queue_manager, hw_exception_work);
	amdgpu_amdkfd_gpu_reset(dqm->dev->kgd);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल व्योम seq_reg_dump(काष्ठा seq_file *m,
			 uपूर्णांक32_t (*dump)[2], uपूर्णांक32_t n_regs)
अणु
	uपूर्णांक32_t i, count;

	क्रम (i = 0, count = 0; i < n_regs; i++) अणु
		अगर (count == 0 ||
		    dump[i-1][0] + माप(uपूर्णांक32_t) != dump[i][0]) अणु
			seq_म_लिखो(m, "%s    %08x: %08x",
				   i ? "\n" : "",
				   dump[i][0], dump[i][1]);
			count = 7;
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m, " %08x", dump[i][1]);
			count--;
		पूर्ण
	पूर्ण

	seq_माला_दो(m, "\n");
पूर्ण

पूर्णांक dqm_debugfs_hqds(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा device_queue_manager *dqm = data;
	uपूर्णांक32_t (*dump)[2], n_regs;
	पूर्णांक pipe, queue;
	पूर्णांक r = 0;

	अगर (!dqm->sched_running) अणु
		seq_म_लिखो(m, " Device is stopped\n");

		वापस 0;
	पूर्ण

	r = dqm->dev->kfd2kgd->hqd_dump(dqm->dev->kgd,
					KFD_CIK_HIQ_PIPE, KFD_CIK_HIQ_QUEUE,
					&dump, &n_regs);
	अगर (!r) अणु
		seq_म_लिखो(m, "  HIQ on MEC %d Pipe %d Queue %d\n",
			   KFD_CIK_HIQ_PIPE/get_pipes_per_mec(dqm)+1,
			   KFD_CIK_HIQ_PIPE%get_pipes_per_mec(dqm),
			   KFD_CIK_HIQ_QUEUE);
		seq_reg_dump(m, dump, n_regs);

		kमुक्त(dump);
	पूर्ण

	क्रम (pipe = 0; pipe < get_pipes_per_mec(dqm); pipe++) अणु
		पूर्णांक pipe_offset = pipe * get_queues_per_pipe(dqm);

		क्रम (queue = 0; queue < get_queues_per_pipe(dqm); queue++) अणु
			अगर (!test_bit(pipe_offset + queue,
				      dqm->dev->shared_resources.cp_queue_biपंचांगap))
				जारी;

			r = dqm->dev->kfd2kgd->hqd_dump(
				dqm->dev->kgd, pipe, queue, &dump, &n_regs);
			अगर (r)
				अवरोध;

			seq_म_लिखो(m, "  CP Pipe %d, Queue %d\n",
				  pipe, queue);
			seq_reg_dump(m, dump, n_regs);

			kमुक्त(dump);
		पूर्ण
	पूर्ण

	क्रम (pipe = 0; pipe < get_num_all_sdma_engines(dqm); pipe++) अणु
		क्रम (queue = 0;
		     queue < dqm->dev->device_info->num_sdma_queues_per_engine;
		     queue++) अणु
			r = dqm->dev->kfd2kgd->hqd_sdma_dump(
				dqm->dev->kgd, pipe, queue, &dump, &n_regs);
			अगर (r)
				अवरोध;

			seq_म_लिखो(m, "  SDMA Engine %d, RLC %d\n",
				  pipe, queue);
			seq_reg_dump(m, dump, n_regs);

			kमुक्त(dump);
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक dqm_debugfs_execute_queues(काष्ठा device_queue_manager *dqm)
अणु
	पूर्णांक r = 0;

	dqm_lock(dqm);
	dqm->active_runlist = true;
	r = execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FILTER_ALL_QUEUES, 0);
	dqm_unlock(dqm);

	वापस r;
पूर्ण

#पूर्ण_अगर

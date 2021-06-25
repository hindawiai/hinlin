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

#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_priv.h"
#समावेश "kfd_kernel_queue.h"
#समावेश "amdgpu_amdkfd.h"

अटल अंतरभूत काष्ठा process_queue_node *get_queue_by_qid(
			काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid)
अणु
	काष्ठा process_queue_node *pqn;

	list_क्रम_each_entry(pqn, &pqm->queues, process_queue_list) अणु
		अगर ((pqn->q && pqn->q->properties.queue_id == qid) ||
		    (pqn->kq && pqn->kq->queue->properties.queue_id == qid))
			वापस pqn;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक find_available_queue_slot(काष्ठा process_queue_manager *pqm,
					अचिन्हित पूर्णांक *qid)
अणु
	अचिन्हित दीर्घ found;

	found = find_first_zero_bit(pqm->queue_slot_biपंचांगap,
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);

	pr_debug("The new slot id %lu\n", found);

	अगर (found >= KFD_MAX_NUM_OF_QUEUES_PER_PROCESS) अणु
		pr_info("Cannot open more queues for process with pasid 0x%x\n",
				pqm->process->pasid);
		वापस -ENOMEM;
	पूर्ण

	set_bit(found, pqm->queue_slot_biपंचांगap);
	*qid = found;

	वापस 0;
पूर्ण

व्योम kfd_process_dequeue_from_device(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_dev *dev = pdd->dev;

	अगर (pdd->alपढ़ोy_dequeued)
		वापस;

	dev->dqm->ops.process_termination(dev->dqm, &pdd->qpd);
	pdd->alपढ़ोy_dequeued = true;
पूर्ण

पूर्णांक pqm_set_gws(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			व्योम *gws)
अणु
	काष्ठा kfd_dev *dev = शून्य;
	काष्ठा process_queue_node *pqn;
	काष्ठा kfd_process_device *pdd;
	काष्ठा kgd_mem *mem = शून्य;
	पूर्णांक ret;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (!pqn) अणु
		pr_err("Queue id does not match any known queue\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pqn->q)
		dev = pqn->q->device;
	अगर (WARN_ON(!dev))
		वापस -ENODEV;

	pdd = kfd_get_process_device_data(dev, pqm->process);
	अगर (!pdd) अणु
		pr_err("Process device data doesn't exist\n");
		वापस -EINVAL;
	पूर्ण

	/* Only allow one queue per process can have GWS asचिन्हित */
	अगर (gws && pdd->qpd.num_gws)
		वापस -EBUSY;

	अगर (!gws && pdd->qpd.num_gws == 0)
		वापस -EINVAL;

	अगर (gws)
		ret = amdgpu_amdkfd_add_gws_to_process(pdd->process->kgd_process_info,
			gws, &mem);
	अन्यथा
		ret = amdgpu_amdkfd_हटाओ_gws_from_process(pdd->process->kgd_process_info,
			pqn->q->gws);
	अगर (unlikely(ret))
		वापस ret;

	pqn->q->gws = mem;
	pdd->qpd.num_gws = gws ? amdgpu_amdkfd_get_num_gws(dev->kgd) : 0;

	वापस pqn->q->device->dqm->ops.update_queue(pqn->q->device->dqm,
							pqn->q);
पूर्ण

व्योम kfd_process_dequeue_from_all_devices(काष्ठा kfd_process *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++)
		kfd_process_dequeue_from_device(p->pdds[i]);
पूर्ण

पूर्णांक pqm_init(काष्ठा process_queue_manager *pqm, काष्ठा kfd_process *p)
अणु
	INIT_LIST_HEAD(&pqm->queues);
	pqm->queue_slot_biपंचांगap =
			kzalloc(DIV_ROUND_UP(KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
					BITS_PER_BYTE), GFP_KERNEL);
	अगर (!pqm->queue_slot_biपंचांगap)
		वापस -ENOMEM;
	pqm->process = p;

	वापस 0;
पूर्ण

व्योम pqm_uninit(काष्ठा process_queue_manager *pqm)
अणु
	काष्ठा process_queue_node *pqn, *next;

	list_क्रम_each_entry_safe(pqn, next, &pqm->queues, process_queue_list) अणु
		अगर (pqn->q && pqn->q->gws)
			amdgpu_amdkfd_हटाओ_gws_from_process(pqm->process->kgd_process_info,
				pqn->q->gws);
		uninit_queue(pqn->q);
		list_del(&pqn->process_queue_list);
		kमुक्त(pqn);
	पूर्ण

	kमुक्त(pqm->queue_slot_biपंचांगap);
	pqm->queue_slot_biपंचांगap = शून्य;
पूर्ण

अटल पूर्णांक init_user_queue(काष्ठा process_queue_manager *pqm,
				काष्ठा kfd_dev *dev, काष्ठा queue **q,
				काष्ठा queue_properties *q_properties,
				काष्ठा file *f, अचिन्हित पूर्णांक qid)
अणु
	पूर्णांक retval;

	/* Doorbell initialized in user space*/
	q_properties->करोorbell_ptr = शून्य;

	/* let DQM handle it*/
	q_properties->vmid = 0;
	q_properties->queue_id = qid;

	retval = init_queue(q, q_properties);
	अगर (retval != 0)
		वापस retval;

	(*q)->device = dev;
	(*q)->process = pqm->process;

	pr_debug("PQM After init queue");

	वापस retval;
पूर्ण

पूर्णांक pqm_create_queue(काष्ठा process_queue_manager *pqm,
			    काष्ठा kfd_dev *dev,
			    काष्ठा file *f,
			    काष्ठा queue_properties *properties,
			    अचिन्हित पूर्णांक *qid,
			    uपूर्णांक32_t *p_करोorbell_offset_in_process)
अणु
	पूर्णांक retval;
	काष्ठा kfd_process_device *pdd;
	काष्ठा queue *q;
	काष्ठा process_queue_node *pqn;
	काष्ठा kernel_queue *kq;
	क्रमागत kfd_queue_type type = properties->type;
	अचिन्हित पूर्णांक max_queues = 127; /* HWS limit */

	q = शून्य;
	kq = शून्य;

	pdd = kfd_get_process_device_data(dev, pqm->process);
	अगर (!pdd) अणु
		pr_err("Process device data doesn't exist\n");
		वापस -1;
	पूर्ण

	/*
	 * क्रम debug process, verअगरy that it is within the अटल queues limit
	 * currently limit is set to half of the total avail HQD slots
	 * If we are just about to create DIQ, the is_debug flag is not set yet
	 * Hence we also check the type as well
	 */
	अगर ((pdd->qpd.is_debug) || (type == KFD_QUEUE_TYPE_DIQ))
		max_queues = dev->device_info->max_no_of_hqd/2;

	अगर (pdd->qpd.queue_count >= max_queues)
		वापस -ENOSPC;

	retval = find_available_queue_slot(pqm, qid);
	अगर (retval != 0)
		वापस retval;

	अगर (list_empty(&pdd->qpd.queues_list) &&
	    list_empty(&pdd->qpd.priv_queue_list))
		dev->dqm->ops.रेजिस्टर_process(dev->dqm, &pdd->qpd);

	pqn = kzalloc(माप(*pqn), GFP_KERNEL);
	अगर (!pqn) अणु
		retval = -ENOMEM;
		जाओ err_allocate_pqn;
	पूर्ण

	चयन (type) अणु
	हाल KFD_QUEUE_TYPE_SDMA:
	हाल KFD_QUEUE_TYPE_SDMA_XGMI:
		/* SDMA queues are always allocated अटलally no matter
		 * which scheduler mode is used. We also करो not need to
		 * check whether a SDMA queue can be allocated here, because
		 * allocate_sdma_queue() in create_queue() has the
		 * corresponding check logic.
		 */
		retval = init_user_queue(pqm, dev, &q, properties, f, *qid);
		अगर (retval != 0)
			जाओ err_create_queue;
		pqn->q = q;
		pqn->kq = शून्य;
		retval = dev->dqm->ops.create_queue(dev->dqm, q, &pdd->qpd);
		prपूर्णांक_queue(q);
		अवरोध;

	हाल KFD_QUEUE_TYPE_COMPUTE:
		/* check अगर there is over subscription */
		अगर ((dev->dqm->sched_policy ==
		     KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION) &&
		((dev->dqm->processes_count >= dev->vm_info.vmid_num_kfd) ||
		(dev->dqm->active_queue_count >= get_cp_queues_num(dev->dqm)))) अणु
			pr_debug("Over-subscription is not allowed when amdkfd.sched_policy == 1\n");
			retval = -EPERM;
			जाओ err_create_queue;
		पूर्ण

		retval = init_user_queue(pqm, dev, &q, properties, f, *qid);
		अगर (retval != 0)
			जाओ err_create_queue;
		pqn->q = q;
		pqn->kq = शून्य;
		retval = dev->dqm->ops.create_queue(dev->dqm, q, &pdd->qpd);
		prपूर्णांक_queue(q);
		अवरोध;
	हाल KFD_QUEUE_TYPE_DIQ:
		kq = kernel_queue_init(dev, KFD_QUEUE_TYPE_DIQ);
		अगर (!kq) अणु
			retval = -ENOMEM;
			जाओ err_create_queue;
		पूर्ण
		kq->queue->properties.queue_id = *qid;
		pqn->kq = kq;
		pqn->q = शून्य;
		retval = dev->dqm->ops.create_kernel_queue(dev->dqm,
							kq, &pdd->qpd);
		अवरोध;
	शेष:
		WARN(1, "Invalid queue type %d", type);
		retval = -EINVAL;
	पूर्ण

	अगर (retval != 0) अणु
		pr_err("Pasid 0x%x DQM create queue type %d failed. ret %d\n",
			pqm->process->pasid, type, retval);
		जाओ err_create_queue;
	पूर्ण

	अगर (q && p_करोorbell_offset_in_process)
		/* Return the करोorbell offset within the करोorbell page
		 * to the caller so it can be passed up to user mode
		 * (in bytes).
		 * There are always 1024 करोorbells per process, so in हाल
		 * of 8-byte करोorbells, there are two करोorbell pages per
		 * process.
		 */
		*p_करोorbell_offset_in_process =
			(q->properties.करोorbell_off * माप(uपूर्णांक32_t)) &
			(kfd_करोorbell_process_slice(dev) - 1);

	pr_debug("PQM After DQM create queue\n");

	list_add(&pqn->process_queue_list, &pqm->queues);

	अगर (q) अणु
		pr_debug("PQM done creating queue\n");
		kfd_procfs_add_queue(q);
		prपूर्णांक_queue_properties(&q->properties);
	पूर्ण

	वापस retval;

err_create_queue:
	uninit_queue(q);
	अगर (kq)
		kernel_queue_uninit(kq, false);
	kमुक्त(pqn);
err_allocate_pqn:
	/* check अगर queues list is empty unरेजिस्टर process from device */
	clear_bit(*qid, pqm->queue_slot_biपंचांगap);
	अगर (list_empty(&pdd->qpd.queues_list) &&
	    list_empty(&pdd->qpd.priv_queue_list))
		dev->dqm->ops.unरेजिस्टर_process(dev->dqm, &pdd->qpd);
	वापस retval;
पूर्ण

पूर्णांक pqm_destroy_queue(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid)
अणु
	काष्ठा process_queue_node *pqn;
	काष्ठा kfd_process_device *pdd;
	काष्ठा device_queue_manager *dqm;
	काष्ठा kfd_dev *dev;
	पूर्णांक retval;

	dqm = शून्य;

	retval = 0;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (!pqn) अणु
		pr_err("Queue id does not match any known queue\n");
		वापस -EINVAL;
	पूर्ण

	dev = शून्य;
	अगर (pqn->kq)
		dev = pqn->kq->dev;
	अगर (pqn->q)
		dev = pqn->q->device;
	अगर (WARN_ON(!dev))
		वापस -ENODEV;

	pdd = kfd_get_process_device_data(dev, pqm->process);
	अगर (!pdd) अणु
		pr_err("Process device data doesn't exist\n");
		वापस -1;
	पूर्ण

	अगर (pqn->kq) अणु
		/* destroy kernel queue (DIQ) */
		dqm = pqn->kq->dev->dqm;
		dqm->ops.destroy_kernel_queue(dqm, pqn->kq, &pdd->qpd);
		kernel_queue_uninit(pqn->kq, false);
	पूर्ण

	अगर (pqn->q) अणु
		kfd_procfs_del_queue(pqn->q);
		dqm = pqn->q->device->dqm;
		retval = dqm->ops.destroy_queue(dqm, &pdd->qpd, pqn->q);
		अगर (retval) अणु
			pr_err("Pasid 0x%x destroy queue %d failed, ret %d\n",
				pqm->process->pasid,
				pqn->q->properties.queue_id, retval);
			अगर (retval != -ETIME)
				जाओ err_destroy_queue;
		पूर्ण

		अगर (pqn->q->gws) अणु
			amdgpu_amdkfd_हटाओ_gws_from_process(pqm->process->kgd_process_info,
				pqn->q->gws);
			pdd->qpd.num_gws = 0;
		पूर्ण

		kमुक्त(pqn->q->properties.cu_mask);
		pqn->q->properties.cu_mask = शून्य;
		uninit_queue(pqn->q);
	पूर्ण

	list_del(&pqn->process_queue_list);
	kमुक्त(pqn);
	clear_bit(qid, pqm->queue_slot_biपंचांगap);

	अगर (list_empty(&pdd->qpd.queues_list) &&
	    list_empty(&pdd->qpd.priv_queue_list))
		dqm->ops.unरेजिस्टर_process(dqm, &pdd->qpd);

err_destroy_queue:
	वापस retval;
पूर्ण

पूर्णांक pqm_update_queue(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			काष्ठा queue_properties *p)
अणु
	पूर्णांक retval;
	काष्ठा process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (!pqn) अणु
		pr_debug("No queue %d exists for update operation\n", qid);
		वापस -EFAULT;
	पूर्ण

	pqn->q->properties.queue_address = p->queue_address;
	pqn->q->properties.queue_size = p->queue_size;
	pqn->q->properties.queue_percent = p->queue_percent;
	pqn->q->properties.priority = p->priority;

	retval = pqn->q->device->dqm->ops.update_queue(pqn->q->device->dqm,
							pqn->q);
	अगर (retval != 0)
		वापस retval;

	वापस 0;
पूर्ण

पूर्णांक pqm_set_cu_mask(काष्ठा process_queue_manager *pqm, अचिन्हित पूर्णांक qid,
			काष्ठा queue_properties *p)
अणु
	पूर्णांक retval;
	काष्ठा process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (!pqn) अणु
		pr_debug("No queue %d exists for update operation\n", qid);
		वापस -EFAULT;
	पूर्ण

	/* Free the old CU mask memory अगर it is alपढ़ोy allocated, then
	 * allocate memory क्रम the new CU mask.
	 */
	kमुक्त(pqn->q->properties.cu_mask);

	pqn->q->properties.cu_mask_count = p->cu_mask_count;
	pqn->q->properties.cu_mask = p->cu_mask;

	retval = pqn->q->device->dqm->ops.update_queue(pqn->q->device->dqm,
							pqn->q);
	अगर (retval != 0)
		वापस retval;

	वापस 0;
पूर्ण

काष्ठा kernel_queue *pqm_get_kernel_queue(
					काष्ठा process_queue_manager *pqm,
					अचिन्हित पूर्णांक qid)
अणु
	काष्ठा process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (pqn && pqn->kq)
		वापस pqn->kq;

	वापस शून्य;
पूर्ण

काष्ठा queue *pqm_get_user_queue(काष्ठा process_queue_manager *pqm,
					अचिन्हित पूर्णांक qid)
अणु
	काष्ठा process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	वापस pqn ? pqn->q : शून्य;
पूर्ण

पूर्णांक pqm_get_wave_state(काष्ठा process_queue_manager *pqm,
		       अचिन्हित पूर्णांक qid,
		       व्योम __user *ctl_stack,
		       u32 *ctl_stack_used_size,
		       u32 *save_area_used_size)
अणु
	काष्ठा process_queue_node *pqn;

	pqn = get_queue_by_qid(pqm, qid);
	अगर (!pqn) अणु
		pr_debug("amdkfd: No queue %d exists for operation\n",
			 qid);
		वापस -EFAULT;
	पूर्ण

	वापस pqn->q->device->dqm->ops.get_wave_state(pqn->q->device->dqm,
						       pqn->q,
						       ctl_stack,
						       ctl_stack_used_size,
						       save_area_used_size);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

पूर्णांक pqm_debugfs_mqds(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा process_queue_manager *pqm = data;
	काष्ठा process_queue_node *pqn;
	काष्ठा queue *q;
	क्रमागत KFD_MQD_TYPE mqd_type;
	काष्ठा mqd_manager *mqd_mgr;
	पूर्णांक r = 0;

	list_क्रम_each_entry(pqn, &pqm->queues, process_queue_list) अणु
		अगर (pqn->q) अणु
			q = pqn->q;
			चयन (q->properties.type) अणु
			हाल KFD_QUEUE_TYPE_SDMA:
			हाल KFD_QUEUE_TYPE_SDMA_XGMI:
				seq_म_लिखो(m, "  SDMA queue on device %x\n",
					   q->device->id);
				mqd_type = KFD_MQD_TYPE_SDMA;
				अवरोध;
			हाल KFD_QUEUE_TYPE_COMPUTE:
				seq_म_लिखो(m, "  Compute queue on device %x\n",
					   q->device->id);
				mqd_type = KFD_MQD_TYPE_CP;
				अवरोध;
			शेष:
				seq_म_लिखो(m,
				"  Bad user queue type %d on device %x\n",
					   q->properties.type, q->device->id);
				जारी;
			पूर्ण
			mqd_mgr = q->device->dqm->mqd_mgrs[mqd_type];
		पूर्ण अन्यथा अगर (pqn->kq) अणु
			q = pqn->kq->queue;
			mqd_mgr = pqn->kq->mqd_mgr;
			चयन (q->properties.type) अणु
			हाल KFD_QUEUE_TYPE_DIQ:
				seq_म_लिखो(m, "  DIQ on device %x\n",
					   pqn->kq->dev->id);
				अवरोध;
			शेष:
				seq_म_लिखो(m,
				"  Bad kernel queue type %d on device %x\n",
					   q->properties.type,
					   pqn->kq->dev->id);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_म_लिखो(m,
		"  Weird: Queue node with neither kernel nor user queue\n");
			जारी;
		पूर्ण

		r = mqd_mgr->debugfs_show_mqd(m, q->mqd);
		अगर (r != 0)
			अवरोध;
	पूर्ण

	वापस r;
पूर्ण

#पूर्ण_अगर

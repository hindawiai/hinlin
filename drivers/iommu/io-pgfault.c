<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Handle device page faults
 *
 * Copyright (C) 2020 ARM Ltd.
 */

#समावेश <linux/iommu.h>
#समावेश <linux/list.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "iommu-sva-lib.h"

/**
 * काष्ठा iopf_queue - IO Page Fault queue
 * @wq: the fault workqueue
 * @devices: devices attached to this queue
 * @lock: protects the device list
 */
काष्ठा iopf_queue अणु
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा list_head		devices;
	काष्ठा mutex			lock;
पूर्ण;

/**
 * काष्ठा iopf_device_param - IO Page Fault data attached to a device
 * @dev: the device that owns this param
 * @queue: IOPF queue
 * @queue_list: index पूर्णांकo queue->devices
 * @partial: faults that are part of a Page Request Group क्रम which the last
 *           request hasn't been submitted yet.
 */
काष्ठा iopf_device_param अणु
	काष्ठा device			*dev;
	काष्ठा iopf_queue		*queue;
	काष्ठा list_head		queue_list;
	काष्ठा list_head		partial;
पूर्ण;

काष्ठा iopf_fault अणु
	काष्ठा iommu_fault		fault;
	काष्ठा list_head		list;
पूर्ण;

काष्ठा iopf_group अणु
	काष्ठा iopf_fault		last_fault;
	काष्ठा list_head		faults;
	काष्ठा work_काष्ठा		work;
	काष्ठा device			*dev;
पूर्ण;

अटल पूर्णांक iopf_complete_group(काष्ठा device *dev, काष्ठा iopf_fault *iopf,
			       क्रमागत iommu_page_response_code status)
अणु
	काष्ठा iommu_page_response resp = अणु
		.version		= IOMMU_PAGE_RESP_VERSION_1,
		.pasid			= iopf->fault.prm.pasid,
		.grpid			= iopf->fault.prm.grpid,
		.code			= status,
	पूर्ण;

	अगर ((iopf->fault.prm.flags & IOMMU_FAULT_PAGE_REQUEST_PASID_VALID) &&
	    (iopf->fault.prm.flags & IOMMU_FAULT_PAGE_RESPONSE_NEEDS_PASID))
		resp.flags = IOMMU_PAGE_RESP_PASID_VALID;

	वापस iommu_page_response(dev, &resp);
पूर्ण

अटल क्रमागत iommu_page_response_code
iopf_handle_single(काष्ठा iopf_fault *iopf)
अणु
	vm_fault_t ret;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित पूर्णांक access_flags = 0;
	अचिन्हित पूर्णांक fault_flags = FAULT_FLAG_REMOTE;
	काष्ठा iommu_fault_page_request *prm = &iopf->fault.prm;
	क्रमागत iommu_page_response_code status = IOMMU_PAGE_RESP_INVALID;

	अगर (!(prm->flags & IOMMU_FAULT_PAGE_REQUEST_PASID_VALID))
		वापस status;

	mm = iommu_sva_find(prm->pasid);
	अगर (IS_ERR_OR_शून्य(mm))
		वापस status;

	mmap_पढ़ो_lock(mm);

	vma = find_extend_vma(mm, prm->addr);
	अगर (!vma)
		/* Unmapped area */
		जाओ out_put_mm;

	अगर (prm->perm & IOMMU_FAULT_PERM_READ)
		access_flags |= VM_READ;

	अगर (prm->perm & IOMMU_FAULT_PERM_WRITE) अणु
		access_flags |= VM_WRITE;
		fault_flags |= FAULT_FLAG_WRITE;
	पूर्ण

	अगर (prm->perm & IOMMU_FAULT_PERM_EXEC) अणु
		access_flags |= VM_EXEC;
		fault_flags |= FAULT_FLAG_INSTRUCTION;
	पूर्ण

	अगर (!(prm->perm & IOMMU_FAULT_PERM_PRIV))
		fault_flags |= FAULT_FLAG_USER;

	अगर (access_flags & ~vma->vm_flags)
		/* Access fault */
		जाओ out_put_mm;

	ret = handle_mm_fault(vma, prm->addr, fault_flags, शून्य);
	status = ret & VM_FAULT_ERROR ? IOMMU_PAGE_RESP_INVALID :
		IOMMU_PAGE_RESP_SUCCESS;

out_put_mm:
	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	वापस status;
पूर्ण

अटल व्योम iopf_handle_group(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iopf_group *group;
	काष्ठा iopf_fault *iopf, *next;
	क्रमागत iommu_page_response_code status = IOMMU_PAGE_RESP_SUCCESS;

	group = container_of(work, काष्ठा iopf_group, work);

	list_क्रम_each_entry_safe(iopf, next, &group->faults, list) अणु
		/*
		 * For the moment, errors are sticky: करोn't handle subsequent
		 * faults in the group अगर there is an error.
		 */
		अगर (status == IOMMU_PAGE_RESP_SUCCESS)
			status = iopf_handle_single(iopf);

		अगर (!(iopf->fault.prm.flags &
		      IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE))
			kमुक्त(iopf);
	पूर्ण

	iopf_complete_group(group->dev, &group->last_fault, status);
	kमुक्त(group);
पूर्ण

/**
 * iommu_queue_iopf - IO Page Fault handler
 * @fault: fault event
 * @cookie: काष्ठा device, passed to iommu_रेजिस्टर_device_fault_handler.
 *
 * Add a fault to the device workqueue, to be handled by mm.
 *
 * This module करोesn't handle PCI PASID Stop Marker; IOMMU drivers must discard
 * them beक्रमe reporting faults. A PASID Stop Marker (LRW = 0b100) करोesn't
 * expect a response. It may be generated when disabling a PASID (issuing a
 * PASID stop request) by some PCI devices.
 *
 * The PASID stop request is issued by the device driver beक्रमe unbind(). Once
 * it completes, no page request is generated क्रम this PASID anymore and
 * outstanding ones have been pushed to the IOMMU (as per PCIe 4.0r1.0 - 6.20.1
 * and 10.4.1.2 - Managing PASID TLP Prefix Usage). Some PCI devices will रुको
 * क्रम all outstanding page requests to come back with a response beक्रमe
 * completing the PASID stop request. Others करो not रुको क्रम page responses, and
 * instead issue this Stop Marker that tells us when the PASID can be
 * पुनः_स्मृतिated.
 *
 * It is safe to discard the Stop Marker because it is an optimization.
 * a. Page requests, which are posted requests, have been flushed to the IOMMU
 *    when the stop request completes.
 * b. The IOMMU driver flushes all fault queues on unbind() beक्रमe मुक्तing the
 *    PASID.
 *
 * So even though the Stop Marker might be issued by the device *after* the stop
 * request completes, outstanding faults will have been dealt with by the समय
 * the PASID is मुक्तd.
 *
 * Return: 0 on success and <0 on error.
 */
पूर्णांक iommu_queue_iopf(काष्ठा iommu_fault *fault, व्योम *cookie)
अणु
	पूर्णांक ret;
	काष्ठा iopf_group *group;
	काष्ठा iopf_fault *iopf, *next;
	काष्ठा iopf_device_param *iopf_param;

	काष्ठा device *dev = cookie;
	काष्ठा dev_iommu *param = dev->iommu;

	lockdep_निश्चित_held(&param->lock);

	अगर (fault->type != IOMMU_FAULT_PAGE_REQ)
		/* Not a recoverable page fault */
		वापस -EOPNOTSUPP;

	/*
	 * As दीर्घ as we're holding param->lock, the queue can't be unlinked
	 * from the device and thereक्रमe cannot disappear.
	 */
	iopf_param = param->iopf_param;
	अगर (!iopf_param)
		वापस -ENODEV;

	अगर (!(fault->prm.flags & IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE)) अणु
		iopf = kzalloc(माप(*iopf), GFP_KERNEL);
		अगर (!iopf)
			वापस -ENOMEM;

		iopf->fault = *fault;

		/* Non-last request of a group. Postpone until the last one */
		list_add(&iopf->list, &iopf_param->partial);

		वापस 0;
	पूर्ण

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group) अणु
		/*
		 * The caller will send a response to the hardware. But we करो
		 * need to clean up beक्रमe leaving, otherwise partial faults
		 * will be stuck.
		 */
		ret = -ENOMEM;
		जाओ cleanup_partial;
	पूर्ण

	group->dev = dev;
	group->last_fault.fault = *fault;
	INIT_LIST_HEAD(&group->faults);
	list_add(&group->last_fault.list, &group->faults);
	INIT_WORK(&group->work, iopf_handle_group);

	/* See अगर we have partial faults क्रम this group */
	list_क्रम_each_entry_safe(iopf, next, &iopf_param->partial, list) अणु
		अगर (iopf->fault.prm.grpid == fault->prm.grpid)
			/* Insert *beक्रमe* the last fault */
			list_move(&iopf->list, &group->faults);
	पूर्ण

	queue_work(iopf_param->queue->wq, &group->work);
	वापस 0;

cleanup_partial:
	list_क्रम_each_entry_safe(iopf, next, &iopf_param->partial, list) अणु
		अगर (iopf->fault.prm.grpid == fault->prm.grpid) अणु
			list_del(&iopf->list);
			kमुक्त(iopf);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_queue_iopf);

/**
 * iopf_queue_flush_dev - Ensure that all queued faults have been processed
 * @dev: the endpoपूर्णांक whose faults need to be flushed.
 *
 * The IOMMU driver calls this beक्रमe releasing a PASID, to ensure that all
 * pending faults क्रम this PASID have been handled, and won't hit the address
 * space of the next process that uses this PASID. The driver must make sure
 * that no new fault is added to the queue. In particular it must flush its
 * low-level queue beक्रमe calling this function.
 *
 * Return: 0 on success and <0 on error.
 */
पूर्णांक iopf_queue_flush_dev(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा iopf_device_param *iopf_param;
	काष्ठा dev_iommu *param = dev->iommu;

	अगर (!param)
		वापस -ENODEV;

	mutex_lock(&param->lock);
	iopf_param = param->iopf_param;
	अगर (iopf_param)
		flush_workqueue(iopf_param->queue->wq);
	अन्यथा
		ret = -ENODEV;
	mutex_unlock(&param->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_flush_dev);

/**
 * iopf_queue_discard_partial - Remove all pending partial fault
 * @queue: the queue whose partial faults need to be discarded
 *
 * When the hardware queue overflows, last page faults in a group may have been
 * lost and the IOMMU driver calls this to discard all partial faults. The
 * driver shouldn't be adding new faults to this queue concurrently.
 *
 * Return: 0 on success and <0 on error.
 */
पूर्णांक iopf_queue_discard_partial(काष्ठा iopf_queue *queue)
अणु
	काष्ठा iopf_fault *iopf, *next;
	काष्ठा iopf_device_param *iopf_param;

	अगर (!queue)
		वापस -EINVAL;

	mutex_lock(&queue->lock);
	list_क्रम_each_entry(iopf_param, &queue->devices, queue_list) अणु
		list_क्रम_each_entry_safe(iopf, next, &iopf_param->partial,
					 list) अणु
			list_del(&iopf->list);
			kमुक्त(iopf);
		पूर्ण
	पूर्ण
	mutex_unlock(&queue->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_discard_partial);

/**
 * iopf_queue_add_device - Add producer to the fault queue
 * @queue: IOPF queue
 * @dev: device to add
 *
 * Return: 0 on success and <0 on error.
 */
पूर्णांक iopf_queue_add_device(काष्ठा iopf_queue *queue, काष्ठा device *dev)
अणु
	पूर्णांक ret = -EBUSY;
	काष्ठा iopf_device_param *iopf_param;
	काष्ठा dev_iommu *param = dev->iommu;

	अगर (!param)
		वापस -ENODEV;

	iopf_param = kzalloc(माप(*iopf_param), GFP_KERNEL);
	अगर (!iopf_param)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&iopf_param->partial);
	iopf_param->queue = queue;
	iopf_param->dev = dev;

	mutex_lock(&queue->lock);
	mutex_lock(&param->lock);
	अगर (!param->iopf_param) अणु
		list_add(&iopf_param->queue_list, &queue->devices);
		param->iopf_param = iopf_param;
		ret = 0;
	पूर्ण
	mutex_unlock(&param->lock);
	mutex_unlock(&queue->lock);

	अगर (ret)
		kमुक्त(iopf_param);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_add_device);

/**
 * iopf_queue_हटाओ_device - Remove producer from fault queue
 * @queue: IOPF queue
 * @dev: device to हटाओ
 *
 * Caller makes sure that no more faults are reported क्रम this device.
 *
 * Return: 0 on success and <0 on error.
 */
पूर्णांक iopf_queue_हटाओ_device(काष्ठा iopf_queue *queue, काष्ठा device *dev)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा iopf_fault *iopf, *next;
	काष्ठा iopf_device_param *iopf_param;
	काष्ठा dev_iommu *param = dev->iommu;

	अगर (!param || !queue)
		वापस -EINVAL;

	mutex_lock(&queue->lock);
	mutex_lock(&param->lock);
	iopf_param = param->iopf_param;
	अगर (iopf_param && iopf_param->queue == queue) अणु
		list_del(&iopf_param->queue_list);
		param->iopf_param = शून्य;
		ret = 0;
	पूर्ण
	mutex_unlock(&param->lock);
	mutex_unlock(&queue->lock);
	अगर (ret)
		वापस ret;

	/* Just in हाल some faults are still stuck */
	list_क्रम_each_entry_safe(iopf, next, &iopf_param->partial, list)
		kमुक्त(iopf);

	kमुक्त(iopf_param);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_हटाओ_device);

/**
 * iopf_queue_alloc - Allocate and initialize a fault queue
 * @name: a unique string identअगरying the queue (क्रम workqueue)
 *
 * Return: the queue on success and शून्य on error.
 */
काष्ठा iopf_queue *iopf_queue_alloc(स्थिर अक्षर *name)
अणु
	काष्ठा iopf_queue *queue;

	queue = kzalloc(माप(*queue), GFP_KERNEL);
	अगर (!queue)
		वापस शून्य;

	/*
	 * The WQ is unordered because the low-level handler enqueues faults by
	 * group. PRI requests within a group have to be ordered, but once
	 * that's dealt with, the high-level function can handle groups out of
	 * order.
	 */
	queue->wq = alloc_workqueue("iopf_queue/%s", WQ_UNBOUND, 0, name);
	अगर (!queue->wq) अणु
		kमुक्त(queue);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&queue->devices);
	mutex_init(&queue->lock);

	वापस queue;
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_alloc);

/**
 * iopf_queue_मुक्त - Free IOPF queue
 * @queue: queue to मुक्त
 *
 * Counterpart to iopf_queue_alloc(). The driver must not be queuing faults or
 * adding/removing devices on this queue anymore.
 */
व्योम iopf_queue_मुक्त(काष्ठा iopf_queue *queue)
अणु
	काष्ठा iopf_device_param *iopf_param, *next;

	अगर (!queue)
		वापस;

	list_क्रम_each_entry_safe(iopf_param, next, &queue->devices, queue_list)
		iopf_queue_हटाओ_device(queue, iopf_param->dev);

	destroy_workqueue(queue->wq);
	kमुक्त(queue);
पूर्ण
EXPORT_SYMBOL_GPL(iopf_queue_मुक्त);

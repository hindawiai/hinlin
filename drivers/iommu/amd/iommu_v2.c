<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010-2012 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 */

#घोषणा pr_fmt(fmt)     "AMD-Vi: " fmt

#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/profile.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pci.h>
#समावेश <linux/gfp.h>

#समावेश "amd_iommu.h"

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Joerg Roedel <jroedel@suse.de>");

#घोषणा MAX_DEVICES		0x10000
#घोषणा PRI_QUEUE_SIZE		512

काष्ठा pri_queue अणु
	atomic_t inflight;
	bool finish;
	पूर्णांक status;
पूर्ण;

काष्ठा pasid_state अणु
	काष्ठा list_head list;			/* For global state-list */
	atomic_t count;				/* Reference count */
	अचिन्हित mmu_notअगरier_count;		/* Counting nested mmu_notअगरier
						   calls */
	काष्ठा mm_काष्ठा *mm;			/* mm_काष्ठा क्रम the faults */
	काष्ठा mmu_notअगरier mn;                 /* mmu_notअगरier handle */
	काष्ठा pri_queue pri[PRI_QUEUE_SIZE];	/* PRI tag states */
	काष्ठा device_state *device_state;	/* Link to our device_state */
	u32 pasid;				/* PASID index */
	bool invalid;				/* Used during setup and
						   tearकरोwn of the pasid */
	spinlock_t lock;			/* Protect pri_queues and
						   mmu_notअगरer_count */
	रुको_queue_head_t wq;			/* To रुको क्रम count == 0 */
पूर्ण;

काष्ठा device_state अणु
	काष्ठा list_head list;
	u16 devid;
	atomic_t count;
	काष्ठा pci_dev *pdev;
	काष्ठा pasid_state **states;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	पूर्णांक pasid_levels;
	पूर्णांक max_pasids;
	amd_iommu_invalid_ppr_cb inv_ppr_cb;
	amd_iommu_invalidate_ctx inv_ctx_cb;
	spinlock_t lock;
	रुको_queue_head_t wq;
पूर्ण;

काष्ठा fault अणु
	काष्ठा work_काष्ठा work;
	काष्ठा device_state *dev_state;
	काष्ठा pasid_state *state;
	काष्ठा mm_काष्ठा *mm;
	u64 address;
	u16 devid;
	u32 pasid;
	u16 tag;
	u16 finish;
	u16 flags;
पूर्ण;

अटल LIST_HEAD(state_list);
अटल DEFINE_SPINLOCK(state_lock);

अटल काष्ठा workqueue_काष्ठा *iommu_wq;

अटल व्योम मुक्त_pasid_states(काष्ठा device_state *dev_state);

अटल u16 device_id(काष्ठा pci_dev *pdev)
अणु
	u16 devid;

	devid = pdev->bus->number;
	devid = (devid << 8) | pdev->devfn;

	वापस devid;
पूर्ण

अटल काष्ठा device_state *__get_device_state(u16 devid)
अणु
	काष्ठा device_state *dev_state;

	list_क्रम_each_entry(dev_state, &state_list, list) अणु
		अगर (dev_state->devid == devid)
			वापस dev_state;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा device_state *get_device_state(u16 devid)
अणु
	काष्ठा device_state *dev_state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&state_lock, flags);
	dev_state = __get_device_state(devid);
	अगर (dev_state != शून्य)
		atomic_inc(&dev_state->count);
	spin_unlock_irqrestore(&state_lock, flags);

	वापस dev_state;
पूर्ण

अटल व्योम मुक्त_device_state(काष्ठा device_state *dev_state)
अणु
	काष्ठा iommu_group *group;

	/*
	 * First detach device from करोमुख्य - No more PRI requests will arrive
	 * from that device after it is unbound from the IOMMUv2 करोमुख्य.
	 */
	group = iommu_group_get(&dev_state->pdev->dev);
	अगर (WARN_ON(!group))
		वापस;

	iommu_detach_group(dev_state->करोमुख्य, group);

	iommu_group_put(group);

	/* Everything is करोwn now, मुक्त the IOMMUv2 करोमुख्य */
	iommu_करोमुख्य_मुक्त(dev_state->करोमुख्य);

	/* Finally get rid of the device-state */
	kमुक्त(dev_state);
पूर्ण

अटल व्योम put_device_state(काष्ठा device_state *dev_state)
अणु
	अगर (atomic_dec_and_test(&dev_state->count))
		wake_up(&dev_state->wq);
पूर्ण

/* Must be called under dev_state->lock */
अटल काष्ठा pasid_state **__get_pasid_state_ptr(काष्ठा device_state *dev_state,
						  u32 pasid, bool alloc)
अणु
	काष्ठा pasid_state **root, **ptr;
	पूर्णांक level, index;

	level = dev_state->pasid_levels;
	root  = dev_state->states;

	जबतक (true) अणु

		index = (pasid >> (9 * level)) & 0x1ff;
		ptr   = &root[index];

		अगर (level == 0)
			अवरोध;

		अगर (*ptr == शून्य) अणु
			अगर (!alloc)
				वापस शून्य;

			*ptr = (व्योम *)get_zeroed_page(GFP_ATOMIC);
			अगर (*ptr == शून्य)
				वापस शून्य;
		पूर्ण

		root   = (काष्ठा pasid_state **)*ptr;
		level -= 1;
	पूर्ण

	वापस ptr;
पूर्ण

अटल पूर्णांक set_pasid_state(काष्ठा device_state *dev_state,
			   काष्ठा pasid_state *pasid_state,
			   u32 pasid)
अणु
	काष्ठा pasid_state **ptr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&dev_state->lock, flags);
	ptr = __get_pasid_state_ptr(dev_state, pasid, true);

	ret = -ENOMEM;
	अगर (ptr == शून्य)
		जाओ out_unlock;

	ret = -ENOMEM;
	अगर (*ptr != शून्य)
		जाओ out_unlock;

	*ptr = pasid_state;

	ret = 0;

out_unlock:
	spin_unlock_irqrestore(&dev_state->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clear_pasid_state(काष्ठा device_state *dev_state, u32 pasid)
अणु
	काष्ठा pasid_state **ptr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev_state->lock, flags);
	ptr = __get_pasid_state_ptr(dev_state, pasid, true);

	अगर (ptr == शून्य)
		जाओ out_unlock;

	*ptr = शून्य;

out_unlock:
	spin_unlock_irqrestore(&dev_state->lock, flags);
पूर्ण

अटल काष्ठा pasid_state *get_pasid_state(काष्ठा device_state *dev_state,
					   u32 pasid)
अणु
	काष्ठा pasid_state **ptr, *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev_state->lock, flags);
	ptr = __get_pasid_state_ptr(dev_state, pasid, false);

	अगर (ptr == शून्य)
		जाओ out_unlock;

	ret = *ptr;
	अगर (ret)
		atomic_inc(&ret->count);

out_unlock:
	spin_unlock_irqrestore(&dev_state->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम मुक्त_pasid_state(काष्ठा pasid_state *pasid_state)
अणु
	kमुक्त(pasid_state);
पूर्ण

अटल व्योम put_pasid_state(काष्ठा pasid_state *pasid_state)
अणु
	अगर (atomic_dec_and_test(&pasid_state->count))
		wake_up(&pasid_state->wq);
पूर्ण

अटल व्योम put_pasid_state_रुको(काष्ठा pasid_state *pasid_state)
अणु
	atomic_dec(&pasid_state->count);
	रुको_event(pasid_state->wq, !atomic_पढ़ो(&pasid_state->count));
	मुक्त_pasid_state(pasid_state);
पूर्ण

अटल व्योम unbind_pasid(काष्ठा pasid_state *pasid_state)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	करोमुख्य = pasid_state->device_state->करोमुख्य;

	/*
	 * Mark pasid_state as invalid, no more faults will we added to the
	 * work queue after this is visible everywhere.
	 */
	pasid_state->invalid = true;

	/* Make sure this is visible */
	smp_wmb();

	/* After this the device/pasid can't access the mm anymore */
	amd_iommu_करोमुख्य_clear_gcr3(करोमुख्य, pasid_state->pasid);

	/* Make sure no more pending faults are in the queue */
	flush_workqueue(iommu_wq);
पूर्ण

अटल व्योम मुक्त_pasid_states_level1(काष्ठा pasid_state **tbl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 512; ++i) अणु
		अगर (tbl[i] == शून्य)
			जारी;

		मुक्त_page((अचिन्हित दीर्घ)tbl[i]);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_pasid_states_level2(काष्ठा pasid_state **tbl)
अणु
	काष्ठा pasid_state **ptr;
	पूर्णांक i;

	क्रम (i = 0; i < 512; ++i) अणु
		अगर (tbl[i] == शून्य)
			जारी;

		ptr = (काष्ठा pasid_state **)tbl[i];
		मुक्त_pasid_states_level1(ptr);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_pasid_states(काष्ठा device_state *dev_state)
अणु
	काष्ठा pasid_state *pasid_state;
	पूर्णांक i;

	क्रम (i = 0; i < dev_state->max_pasids; ++i) अणु
		pasid_state = get_pasid_state(dev_state, i);
		अगर (pasid_state == शून्य)
			जारी;

		put_pasid_state(pasid_state);

		/*
		 * This will call the mn_release function and
		 * unbind the PASID
		 */
		mmu_notअगरier_unरेजिस्टर(&pasid_state->mn, pasid_state->mm);

		put_pasid_state_रुको(pasid_state); /* Reference taken in
						      amd_iommu_bind_pasid */

		/* Drop reference taken in amd_iommu_bind_pasid */
		put_device_state(dev_state);
	पूर्ण

	अगर (dev_state->pasid_levels == 2)
		मुक्त_pasid_states_level2(dev_state->states);
	अन्यथा अगर (dev_state->pasid_levels == 1)
		मुक्त_pasid_states_level1(dev_state->states);
	अन्यथा
		BUG_ON(dev_state->pasid_levels != 0);

	मुक्त_page((अचिन्हित दीर्घ)dev_state->states);
पूर्ण

अटल काष्ठा pasid_state *mn_to_state(काष्ठा mmu_notअगरier *mn)
अणु
	वापस container_of(mn, काष्ठा pasid_state, mn);
पूर्ण

अटल व्योम mn_invalidate_range(काष्ठा mmu_notअगरier *mn,
				काष्ठा mm_काष्ठा *mm,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा pasid_state *pasid_state;
	काष्ठा device_state *dev_state;

	pasid_state = mn_to_state(mn);
	dev_state   = pasid_state->device_state;

	अगर ((start ^ (end - 1)) < PAGE_SIZE)
		amd_iommu_flush_page(dev_state->करोमुख्य, pasid_state->pasid,
				     start);
	अन्यथा
		amd_iommu_flush_tlb(dev_state->करोमुख्य, pasid_state->pasid);
पूर्ण

अटल व्योम mn_release(काष्ठा mmu_notअगरier *mn, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा pasid_state *pasid_state;
	काष्ठा device_state *dev_state;
	bool run_inv_ctx_cb;

	might_sleep();

	pasid_state    = mn_to_state(mn);
	dev_state      = pasid_state->device_state;
	run_inv_ctx_cb = !pasid_state->invalid;

	अगर (run_inv_ctx_cb && dev_state->inv_ctx_cb)
		dev_state->inv_ctx_cb(dev_state->pdev, pasid_state->pasid);

	unbind_pasid(pasid_state);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops iommu_mn = अणु
	.release		= mn_release,
	.invalidate_range       = mn_invalidate_range,
पूर्ण;

अटल व्योम set_pri_tag_status(काष्ठा pasid_state *pasid_state,
			       u16 tag, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pasid_state->lock, flags);
	pasid_state->pri[tag].status = status;
	spin_unlock_irqrestore(&pasid_state->lock, flags);
पूर्ण

अटल व्योम finish_pri_tag(काष्ठा device_state *dev_state,
			   काष्ठा pasid_state *pasid_state,
			   u16 tag)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pasid_state->lock, flags);
	अगर (atomic_dec_and_test(&pasid_state->pri[tag].inflight) &&
	    pasid_state->pri[tag].finish) अणु
		amd_iommu_complete_ppr(dev_state->pdev, pasid_state->pasid,
				       pasid_state->pri[tag].status, tag);
		pasid_state->pri[tag].finish = false;
		pasid_state->pri[tag].status = PPR_SUCCESS;
	पूर्ण
	spin_unlock_irqrestore(&pasid_state->lock, flags);
पूर्ण

अटल व्योम handle_fault_error(काष्ठा fault *fault)
अणु
	पूर्णांक status;

	अगर (!fault->dev_state->inv_ppr_cb) अणु
		set_pri_tag_status(fault->state, fault->tag, PPR_INVALID);
		वापस;
	पूर्ण

	status = fault->dev_state->inv_ppr_cb(fault->dev_state->pdev,
					      fault->pasid,
					      fault->address,
					      fault->flags);
	चयन (status) अणु
	हाल AMD_IOMMU_INV_PRI_RSP_SUCCESS:
		set_pri_tag_status(fault->state, fault->tag, PPR_SUCCESS);
		अवरोध;
	हाल AMD_IOMMU_INV_PRI_RSP_INVALID:
		set_pri_tag_status(fault->state, fault->tag, PPR_INVALID);
		अवरोध;
	हाल AMD_IOMMU_INV_PRI_RSP_FAIL:
		set_pri_tag_status(fault->state, fault->tag, PPR_FAILURE);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल bool access_error(काष्ठा vm_area_काष्ठा *vma, काष्ठा fault *fault)
अणु
	अचिन्हित दीर्घ requested = 0;

	अगर (fault->flags & PPR_FAULT_EXEC)
		requested |= VM_EXEC;

	अगर (fault->flags & PPR_FAULT_READ)
		requested |= VM_READ;

	अगर (fault->flags & PPR_FAULT_WRITE)
		requested |= VM_WRITE;

	वापस (requested & ~vma->vm_flags) != 0;
पूर्ण

अटल व्योम करो_fault(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fault *fault = container_of(work, काष्ठा fault, work);
	काष्ठा vm_area_काष्ठा *vma;
	vm_fault_t ret = VM_FAULT_ERROR;
	अचिन्हित पूर्णांक flags = 0;
	काष्ठा mm_काष्ठा *mm;
	u64 address;

	mm = fault->state->mm;
	address = fault->address;

	अगर (fault->flags & PPR_FAULT_USER)
		flags |= FAULT_FLAG_USER;
	अगर (fault->flags & PPR_FAULT_WRITE)
		flags |= FAULT_FLAG_WRITE;
	flags |= FAULT_FLAG_REMOTE;

	mmap_पढ़ो_lock(mm);
	vma = find_extend_vma(mm, address);
	अगर (!vma || address < vma->vm_start)
		/* failed to get a vma in the right range */
		जाओ out;

	/* Check अगर we have the right permissions on the vma */
	अगर (access_error(vma, fault))
		जाओ out;

	ret = handle_mm_fault(vma, address, flags, शून्य);
out:
	mmap_पढ़ो_unlock(mm);

	अगर (ret & VM_FAULT_ERROR)
		/* failed to service fault */
		handle_fault_error(fault);

	finish_pri_tag(fault->dev_state, fault->state, fault->tag);

	put_pasid_state(fault->state);

	kमुक्त(fault);
पूर्ण

अटल पूर्णांक ppr_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ e, व्योम *data)
अणु
	काष्ठा amd_iommu_fault *iommu_fault;
	काष्ठा pasid_state *pasid_state;
	काष्ठा device_state *dev_state;
	काष्ठा pci_dev *pdev = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा fault *fault;
	bool finish;
	u16 tag, devid;
	पूर्णांक ret;

	iommu_fault = data;
	tag         = iommu_fault->tag & 0x1ff;
	finish      = (iommu_fault->tag >> 9) & 1;

	devid = iommu_fault->device_id;
	pdev = pci_get_करोमुख्य_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	अगर (!pdev)
		वापस -ENODEV;

	ret = NOTIFY_DONE;

	/* In kdump kernel pci dev is not initialized yet -> send INVALID */
	अगर (amd_iommu_is_attach_deferred(शून्य, &pdev->dev)) अणु
		amd_iommu_complete_ppr(pdev, iommu_fault->pasid,
				       PPR_INVALID, tag);
		जाओ out;
	पूर्ण

	dev_state = get_device_state(iommu_fault->device_id);
	अगर (dev_state == शून्य)
		जाओ out;

	pasid_state = get_pasid_state(dev_state, iommu_fault->pasid);
	अगर (pasid_state == शून्य || pasid_state->invalid) अणु
		/* We know the device but not the PASID -> send INVALID */
		amd_iommu_complete_ppr(dev_state->pdev, iommu_fault->pasid,
				       PPR_INVALID, tag);
		जाओ out_drop_state;
	पूर्ण

	spin_lock_irqsave(&pasid_state->lock, flags);
	atomic_inc(&pasid_state->pri[tag].inflight);
	अगर (finish)
		pasid_state->pri[tag].finish = true;
	spin_unlock_irqrestore(&pasid_state->lock, flags);

	fault = kzalloc(माप(*fault), GFP_ATOMIC);
	अगर (fault == शून्य) अणु
		/* We are OOM - send success and let the device re-fault */
		finish_pri_tag(dev_state, pasid_state, tag);
		जाओ out_drop_state;
	पूर्ण

	fault->dev_state = dev_state;
	fault->address   = iommu_fault->address;
	fault->state     = pasid_state;
	fault->tag       = tag;
	fault->finish    = finish;
	fault->pasid     = iommu_fault->pasid;
	fault->flags     = iommu_fault->flags;
	INIT_WORK(&fault->work, करो_fault);

	queue_work(iommu_wq, &fault->work);

	ret = NOTIFY_OK;

out_drop_state:

	अगर (ret != NOTIFY_OK && pasid_state)
		put_pasid_state(pasid_state);

	put_device_state(dev_state);

out:
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block ppr_nb = अणु
	.notअगरier_call = ppr_notअगरier,
पूर्ण;

पूर्णांक amd_iommu_bind_pasid(काष्ठा pci_dev *pdev, u32 pasid,
			 काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pasid_state *pasid_state;
	काष्ठा device_state *dev_state;
	काष्ठा mm_काष्ठा *mm;
	u16 devid;
	पूर्णांक ret;

	might_sleep();

	अगर (!amd_iommu_v2_supported())
		वापस -ENODEV;

	devid     = device_id(pdev);
	dev_state = get_device_state(devid);

	अगर (dev_state == शून्य)
		वापस -EINVAL;

	ret = -EINVAL;
	अगर (pasid >= dev_state->max_pasids)
		जाओ out;

	ret = -ENOMEM;
	pasid_state = kzalloc(माप(*pasid_state), GFP_KERNEL);
	अगर (pasid_state == शून्य)
		जाओ out;


	atomic_set(&pasid_state->count, 1);
	init_रुकोqueue_head(&pasid_state->wq);
	spin_lock_init(&pasid_state->lock);

	mm                        = get_task_mm(task);
	pasid_state->mm           = mm;
	pasid_state->device_state = dev_state;
	pasid_state->pasid        = pasid;
	pasid_state->invalid      = true; /* Mark as valid only अगर we are
					     करोne with setting up the pasid */
	pasid_state->mn.ops       = &iommu_mn;

	अगर (pasid_state->mm == शून्य)
		जाओ out_मुक्त;

	mmu_notअगरier_रेजिस्टर(&pasid_state->mn, mm);

	ret = set_pasid_state(dev_state, pasid_state, pasid);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	ret = amd_iommu_करोमुख्य_set_gcr3(dev_state->करोमुख्य, pasid,
					__pa(pasid_state->mm->pgd));
	अगर (ret)
		जाओ out_clear_state;

	/* Now we are पढ़ोy to handle faults */
	pasid_state->invalid = false;

	/*
	 * Drop the reference to the mm_काष्ठा here. We rely on the
	 * mmu_notअगरier release call-back to inक्रमm us when the mm
	 * is going away.
	 */
	mmput(mm);

	वापस 0;

out_clear_state:
	clear_pasid_state(dev_state, pasid);

out_unरेजिस्टर:
	mmu_notअगरier_unरेजिस्टर(&pasid_state->mn, mm);
	mmput(mm);

out_मुक्त:
	मुक्त_pasid_state(pasid_state);

out:
	put_device_state(dev_state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_bind_pasid);

व्योम amd_iommu_unbind_pasid(काष्ठा pci_dev *pdev, u32 pasid)
अणु
	काष्ठा pasid_state *pasid_state;
	काष्ठा device_state *dev_state;
	u16 devid;

	might_sleep();

	अगर (!amd_iommu_v2_supported())
		वापस;

	devid = device_id(pdev);
	dev_state = get_device_state(devid);
	अगर (dev_state == शून्य)
		वापस;

	अगर (pasid >= dev_state->max_pasids)
		जाओ out;

	pasid_state = get_pasid_state(dev_state, pasid);
	अगर (pasid_state == शून्य)
		जाओ out;
	/*
	 * Drop reference taken here. We are safe because we still hold
	 * the reference taken in the amd_iommu_bind_pasid function.
	 */
	put_pasid_state(pasid_state);

	/* Clear the pasid state so that the pasid can be re-used */
	clear_pasid_state(dev_state, pasid_state->pasid);

	/*
	 * Call mmu_notअगरier_unरेजिस्टर to drop our reference
	 * to pasid_state->mm
	 */
	mmu_notअगरier_unरेजिस्टर(&pasid_state->mn, pasid_state->mm);

	put_pasid_state_रुको(pasid_state); /* Reference taken in
					      amd_iommu_bind_pasid */
out:
	/* Drop reference taken in this function */
	put_device_state(dev_state);

	/* Drop reference taken in amd_iommu_bind_pasid */
	put_device_state(dev_state);
पूर्ण
EXPORT_SYMBOL(amd_iommu_unbind_pasid);

पूर्णांक amd_iommu_init_device(काष्ठा pci_dev *pdev, पूर्णांक pasids)
अणु
	काष्ठा device_state *dev_state;
	काष्ठा iommu_group *group;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, पंचांगp;
	u16 devid;

	might_sleep();

	/*
	 * When memory encryption is active the device is likely not in a
	 * direct-mapped करोमुख्य. Forbid using IOMMUv2 functionality क्रम now.
	 */
	अगर (mem_encrypt_active())
		वापस -ENODEV;

	अगर (!amd_iommu_v2_supported())
		वापस -ENODEV;

	अगर (pasids <= 0 || pasids > (PASID_MASK + 1))
		वापस -EINVAL;

	devid = device_id(pdev);

	dev_state = kzalloc(माप(*dev_state), GFP_KERNEL);
	अगर (dev_state == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&dev_state->lock);
	init_रुकोqueue_head(&dev_state->wq);
	dev_state->pdev  = pdev;
	dev_state->devid = devid;

	पंचांगp = pasids;
	क्रम (dev_state->pasid_levels = 0; (पंचांगp - 1) & ~0x1ff; पंचांगp >>= 9)
		dev_state->pasid_levels += 1;

	atomic_set(&dev_state->count, 1);
	dev_state->max_pasids = pasids;

	ret = -ENOMEM;
	dev_state->states = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (dev_state->states == शून्य)
		जाओ out_मुक्त_dev_state;

	dev_state->करोमुख्य = iommu_करोमुख्य_alloc(&pci_bus_type);
	अगर (dev_state->करोमुख्य == शून्य)
		जाओ out_मुक्त_states;

	amd_iommu_करोमुख्य_direct_map(dev_state->करोमुख्य);

	ret = amd_iommu_करोमुख्य_enable_v2(dev_state->करोमुख्य, pasids);
	अगर (ret)
		जाओ out_मुक्त_करोमुख्य;

	group = iommu_group_get(&pdev->dev);
	अगर (!group) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	ret = iommu_attach_group(dev_state->करोमुख्य, group);
	अगर (ret != 0)
		जाओ out_drop_group;

	iommu_group_put(group);

	spin_lock_irqsave(&state_lock, flags);

	अगर (__get_device_state(devid) != शून्य) अणु
		spin_unlock_irqrestore(&state_lock, flags);
		ret = -EBUSY;
		जाओ out_मुक्त_करोमुख्य;
	पूर्ण

	list_add_tail(&dev_state->list, &state_list);

	spin_unlock_irqrestore(&state_lock, flags);

	वापस 0;

out_drop_group:
	iommu_group_put(group);

out_मुक्त_करोमुख्य:
	iommu_करोमुख्य_मुक्त(dev_state->करोमुख्य);

out_मुक्त_states:
	मुक्त_page((अचिन्हित दीर्घ)dev_state->states);

out_मुक्त_dev_state:
	kमुक्त(dev_state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_init_device);

व्योम amd_iommu_मुक्त_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_state *dev_state;
	अचिन्हित दीर्घ flags;
	u16 devid;

	अगर (!amd_iommu_v2_supported())
		वापस;

	devid = device_id(pdev);

	spin_lock_irqsave(&state_lock, flags);

	dev_state = __get_device_state(devid);
	अगर (dev_state == शून्य) अणु
		spin_unlock_irqrestore(&state_lock, flags);
		वापस;
	पूर्ण

	list_del(&dev_state->list);

	spin_unlock_irqrestore(&state_lock, flags);

	/* Get rid of any reमुख्यing pasid states */
	मुक्त_pasid_states(dev_state);

	put_device_state(dev_state);
	/*
	 * Wait until the last reference is dropped beक्रमe मुक्तing
	 * the device state.
	 */
	रुको_event(dev_state->wq, !atomic_पढ़ो(&dev_state->count));
	मुक्त_device_state(dev_state);
पूर्ण
EXPORT_SYMBOL(amd_iommu_मुक्त_device);

पूर्णांक amd_iommu_set_invalid_ppr_cb(काष्ठा pci_dev *pdev,
				 amd_iommu_invalid_ppr_cb cb)
अणु
	काष्ठा device_state *dev_state;
	अचिन्हित दीर्घ flags;
	u16 devid;
	पूर्णांक ret;

	अगर (!amd_iommu_v2_supported())
		वापस -ENODEV;

	devid = device_id(pdev);

	spin_lock_irqsave(&state_lock, flags);

	ret = -EINVAL;
	dev_state = __get_device_state(devid);
	अगर (dev_state == शून्य)
		जाओ out_unlock;

	dev_state->inv_ppr_cb = cb;

	ret = 0;

out_unlock:
	spin_unlock_irqrestore(&state_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_set_invalid_ppr_cb);

पूर्णांक amd_iommu_set_invalidate_ctx_cb(काष्ठा pci_dev *pdev,
				    amd_iommu_invalidate_ctx cb)
अणु
	काष्ठा device_state *dev_state;
	अचिन्हित दीर्घ flags;
	u16 devid;
	पूर्णांक ret;

	अगर (!amd_iommu_v2_supported())
		वापस -ENODEV;

	devid = device_id(pdev);

	spin_lock_irqsave(&state_lock, flags);

	ret = -EINVAL;
	dev_state = __get_device_state(devid);
	अगर (dev_state == शून्य)
		जाओ out_unlock;

	dev_state->inv_ctx_cb = cb;

	ret = 0;

out_unlock:
	spin_unlock_irqrestore(&state_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(amd_iommu_set_invalidate_ctx_cb);

अटल पूर्णांक __init amd_iommu_v2_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("AMD IOMMUv2 driver by Joerg Roedel <jroedel@suse.de>\n");

	अगर (!amd_iommu_v2_supported()) अणु
		pr_info("AMD IOMMUv2 functionality not available on this system\n");
		/*
		 * Load anyway to provide the symbols to other modules
		 * which may use AMD IOMMUv2 optionally.
		 */
		वापस 0;
	पूर्ण

	ret = -ENOMEM;
	iommu_wq = alloc_workqueue("amd_iommu_v2", WQ_MEM_RECLAIM, 0);
	अगर (iommu_wq == शून्य)
		जाओ out;

	amd_iommu_रेजिस्टर_ppr_notअगरier(&ppr_nb);

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास amd_iommu_v2_निकास(व्योम)
अणु
	काष्ठा device_state *dev_state;
	पूर्णांक i;

	अगर (!amd_iommu_v2_supported())
		वापस;

	amd_iommu_unरेजिस्टर_ppr_notअगरier(&ppr_nb);

	flush_workqueue(iommu_wq);

	/*
	 * The loop below might call flush_workqueue(), so call
	 * destroy_workqueue() after it
	 */
	क्रम (i = 0; i < MAX_DEVICES; ++i) अणु
		dev_state = get_device_state(i);

		अगर (dev_state == शून्य)
			जारी;

		WARN_ON_ONCE(1);

		put_device_state(dev_state);
		amd_iommu_मुक्त_device(dev_state->pdev);
	पूर्ण

	destroy_workqueue(iommu_wq);
पूर्ण

module_init(amd_iommu_v2_init);
module_निकास(amd_iommu_v2_निकास);

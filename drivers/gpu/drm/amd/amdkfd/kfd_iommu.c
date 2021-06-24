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
 */

#समावेश <linux/kconfig.h>

#अगर IS_REACHABLE(CONFIG_AMD_IOMMU_V2)

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/amd-iommu.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_dbgmgr.h"
#समावेश "kfd_topology.h"
#समावेश "kfd_iommu.h"

अटल स्थिर u32 required_iommu_flags = AMD_IOMMU_DEVICE_FLAG_ATS_SUP |
					AMD_IOMMU_DEVICE_FLAG_PRI_SUP |
					AMD_IOMMU_DEVICE_FLAG_PASID_SUP;

/** kfd_iommu_check_device - Check whether IOMMU is available क्रम device
 */
पूर्णांक kfd_iommu_check_device(काष्ठा kfd_dev *kfd)
अणु
	काष्ठा amd_iommu_device_info iommu_info;
	पूर्णांक err;

	अगर (!kfd->use_iommu_v2)
		वापस -ENODEV;

	iommu_info.flags = 0;
	err = amd_iommu_device_info(kfd->pdev, &iommu_info);
	अगर (err)
		वापस err;

	अगर ((iommu_info.flags & required_iommu_flags) != required_iommu_flags)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/** kfd_iommu_device_init - Initialize IOMMU क्रम device
 */
पूर्णांक kfd_iommu_device_init(काष्ठा kfd_dev *kfd)
अणु
	काष्ठा amd_iommu_device_info iommu_info;
	अचिन्हित पूर्णांक pasid_limit;
	पूर्णांक err;

	अगर (!kfd->use_iommu_v2)
		वापस 0;

	iommu_info.flags = 0;
	err = amd_iommu_device_info(kfd->pdev, &iommu_info);
	अगर (err < 0) अणु
		dev_err(kfd_device,
			"error getting iommu info. is the iommu enabled?\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((iommu_info.flags & required_iommu_flags) != required_iommu_flags) अणु
		dev_err(kfd_device,
			"error required iommu flags ats %i, pri %i, pasid %i\n",
		       (iommu_info.flags & AMD_IOMMU_DEVICE_FLAG_ATS_SUP) != 0,
		       (iommu_info.flags & AMD_IOMMU_DEVICE_FLAG_PRI_SUP) != 0,
		       (iommu_info.flags & AMD_IOMMU_DEVICE_FLAG_PASID_SUP)
									!= 0);
		वापस -ENODEV;
	पूर्ण

	pasid_limit = min_t(अचिन्हित पूर्णांक,
			(अचिन्हित पूर्णांक)(1 << kfd->device_info->max_pasid_bits),
			iommu_info.max_pasids);

	अगर (!kfd_set_pasid_limit(pasid_limit)) अणु
		dev_err(kfd_device, "error setting pasid limit\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/** kfd_iommu_bind_process_to_device - Have the IOMMU bind a process
 *
 * Binds the given process to the given device using its PASID. This
 * enables IOMMUv2 address translation क्रम the process on the device.
 *
 * This function assumes that the process mutex is held.
 */
पूर्णांक kfd_iommu_bind_process_to_device(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_dev *dev = pdd->dev;
	काष्ठा kfd_process *p = pdd->process;
	पूर्णांक err;

	अगर (!dev->use_iommu_v2 || pdd->bound == PDD_BOUND)
		वापस 0;

	अगर (unlikely(pdd->bound == PDD_BOUND_SUSPENDED)) अणु
		pr_err("Binding PDD_BOUND_SUSPENDED pdd is unexpected!\n");
		वापस -EINVAL;
	पूर्ण

	err = amd_iommu_bind_pasid(dev->pdev, p->pasid, p->lead_thपढ़ो);
	अगर (!err)
		pdd->bound = PDD_BOUND;

	वापस err;
पूर्ण

/** kfd_iommu_unbind_process - Unbind process from all devices
 *
 * This हटाओs all IOMMU device bindings of the process. To be used
 * beक्रमe process termination.
 */
व्योम kfd_iommu_unbind_process(काष्ठा kfd_process *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++)
		अगर (p->pdds[i]->bound == PDD_BOUND)
			amd_iommu_unbind_pasid(p->pdds[i]->dev->pdev, p->pasid);
पूर्ण

/* Callback क्रम process shutकरोwn invoked by the IOMMU driver */
अटल व्योम iommu_pasid_shutकरोwn_callback(काष्ठा pci_dev *pdev, u32 pasid)
अणु
	काष्ठा kfd_dev *dev = kfd_device_by_pci_dev(pdev);
	काष्ठा kfd_process *p;
	काष्ठा kfd_process_device *pdd;

	अगर (!dev)
		वापस;

	/*
	 * Look क्रम the process that matches the pasid. If there is no such
	 * process, we either released it in amdkfd's own notअगरier, or there
	 * is a bug. Unक्रमtunately, there is no way to tell...
	 */
	p = kfd_lookup_process_by_pasid(pasid);
	अगर (!p)
		वापस;

	pr_debug("Unbinding process 0x%x from IOMMU\n", pasid);

	mutex_lock(kfd_get_dbgmgr_mutex());

	अगर (dev->dbgmgr && dev->dbgmgr->pasid == p->pasid) अणु
		अगर (!kfd_dbgmgr_unरेजिस्टर(dev->dbgmgr, p)) अणु
			kfd_dbgmgr_destroy(dev->dbgmgr);
			dev->dbgmgr = शून्य;
		पूर्ण
	पूर्ण

	mutex_unlock(kfd_get_dbgmgr_mutex());

	mutex_lock(&p->mutex);

	pdd = kfd_get_process_device_data(dev, p);
	अगर (pdd)
		/* For GPU relying on IOMMU, we need to dequeue here
		 * when PASID is still bound.
		 */
		kfd_process_dequeue_from_device(pdd);

	mutex_unlock(&p->mutex);

	kfd_unref_process(p);
पूर्ण

/* This function called by IOMMU driver on PPR failure */
अटल पूर्णांक iommu_invalid_ppr_cb(काष्ठा pci_dev *pdev, u32 pasid,
				अचिन्हित दीर्घ address, u16 flags)
अणु
	काष्ठा kfd_dev *dev;

	dev_warn_ratelimited(kfd_device,
			"Invalid PPR device %x:%x.%x pasid 0x%x address 0x%lX flags 0x%X",
			pdev->bus->number,
			PCI_SLOT(pdev->devfn),
			PCI_FUNC(pdev->devfn),
			pasid,
			address,
			flags);

	dev = kfd_device_by_pci_dev(pdev);
	अगर (!WARN_ON(!dev))
		kfd_संकेत_iommu_event(dev, pasid, address,
			flags & PPR_FAULT_WRITE, flags & PPR_FAULT_EXEC);

	वापस AMD_IOMMU_INV_PRI_RSP_INVALID;
पूर्ण

/*
 * Bind processes करो the device that have been temporarily unbound
 * (PDD_BOUND_SUSPENDED) in kfd_unbind_processes_from_device.
 */
अटल पूर्णांक kfd_bind_processes_to_device(काष्ठा kfd_dev *kfd)
अणु
	काष्ठा kfd_process_device *pdd;
	काष्ठा kfd_process *p;
	अचिन्हित पूर्णांक temp;
	पूर्णांक err = 0;

	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		mutex_lock(&p->mutex);
		pdd = kfd_get_process_device_data(kfd, p);

		अगर (WARN_ON(!pdd) || pdd->bound != PDD_BOUND_SUSPENDED) अणु
			mutex_unlock(&p->mutex);
			जारी;
		पूर्ण

		err = amd_iommu_bind_pasid(kfd->pdev, p->pasid,
				p->lead_thपढ़ो);
		अगर (err < 0) अणु
			pr_err("Unexpected pasid 0x%x binding failure\n",
					p->pasid);
			mutex_unlock(&p->mutex);
			अवरोध;
		पूर्ण

		pdd->bound = PDD_BOUND;
		mutex_unlock(&p->mutex);
	पूर्ण

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस err;
पूर्ण

/*
 * Mark currently bound processes as PDD_BOUND_SUSPENDED. These
 * processes will be restored to PDD_BOUND state in
 * kfd_bind_processes_to_device.
 */
अटल व्योम kfd_unbind_processes_from_device(काष्ठा kfd_dev *kfd)
अणु
	काष्ठा kfd_process_device *pdd;
	काष्ठा kfd_process *p;
	अचिन्हित पूर्णांक temp;

	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		mutex_lock(&p->mutex);
		pdd = kfd_get_process_device_data(kfd, p);

		अगर (WARN_ON(!pdd)) अणु
			mutex_unlock(&p->mutex);
			जारी;
		पूर्ण

		अगर (pdd->bound == PDD_BOUND)
			pdd->bound = PDD_BOUND_SUSPENDED;
		mutex_unlock(&p->mutex);
	पूर्ण

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);
पूर्ण

/** kfd_iommu_suspend - Prepare IOMMU क्रम suspend
 *
 * This unbinds processes from the device and disables the IOMMU क्रम
 * the device.
 */
व्योम kfd_iommu_suspend(काष्ठा kfd_dev *kfd)
अणु
	अगर (!kfd->use_iommu_v2)
		वापस;

	kfd_unbind_processes_from_device(kfd);

	amd_iommu_set_invalidate_ctx_cb(kfd->pdev, शून्य);
	amd_iommu_set_invalid_ppr_cb(kfd->pdev, शून्य);
	amd_iommu_मुक्त_device(kfd->pdev);
पूर्ण

/** kfd_iommu_resume - Restore IOMMU after resume
 *
 * This reinitializes the IOMMU क्रम the device and re-binds previously
 * suspended processes to the device.
 */
पूर्णांक kfd_iommu_resume(काष्ठा kfd_dev *kfd)
अणु
	अचिन्हित पूर्णांक pasid_limit;
	पूर्णांक err;

	अगर (!kfd->use_iommu_v2)
		वापस 0;

	pasid_limit = kfd_get_pasid_limit();

	err = amd_iommu_init_device(kfd->pdev, pasid_limit);
	अगर (err)
		वापस -ENXIO;

	amd_iommu_set_invalidate_ctx_cb(kfd->pdev,
					iommu_pasid_shutकरोwn_callback);
	amd_iommu_set_invalid_ppr_cb(kfd->pdev,
				     iommu_invalid_ppr_cb);

	err = kfd_bind_processes_to_device(kfd);
	अगर (err) अणु
		amd_iommu_set_invalidate_ctx_cb(kfd->pdev, शून्य);
		amd_iommu_set_invalid_ppr_cb(kfd->pdev, शून्य);
		amd_iommu_मुक्त_device(kfd->pdev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/** kfd_iommu_add_perf_counters - Add IOMMU perक्रमmance counters to topology
 */
पूर्णांक kfd_iommu_add_perf_counters(काष्ठा kfd_topology_device *kdev)
अणु
	काष्ठा kfd_perf_properties *props;

	अगर (!(kdev->node_props.capability & HSA_CAP_ATS_PRESENT))
		वापस 0;

	अगर (!amd_iommu_pc_supported())
		वापस 0;

	props = kfd_alloc_काष्ठा(props);
	अगर (!props)
		वापस -ENOMEM;
	म_नकल(props->block_name, "iommu");
	props->max_concurrent = amd_iommu_pc_get_max_banks(0) *
		amd_iommu_pc_get_max_counters(0); /* assume one iommu */
	list_add_tail(&props->list, &kdev->perf_props);

	वापस 0;
पूर्ण

#पूर्ण_अगर

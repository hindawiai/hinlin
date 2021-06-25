<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2015 Intel Corporation.
 *
 * Authors: David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकel-svm.h>
#समावेश <linux/rculist.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ats.h>
#समावेश <linux/dmar.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/ioasid.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/fpu/api.h>

#समावेश "pasid.h"

अटल irqवापस_t prq_event_thपढ़ो(पूर्णांक irq, व्योम *d);
अटल व्योम पूर्णांकel_svm_drain_prq(काष्ठा device *dev, u32 pasid);

#घोषणा PRQ_ORDER 0

पूर्णांक पूर्णांकel_svm_enable_prq(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	काष्ठा page *pages;
	पूर्णांक irq, ret;

	pages = alloc_pages(GFP_KERNEL | __GFP_ZERO, PRQ_ORDER);
	अगर (!pages) अणु
		pr_warn("IOMMU: %s: Failed to allocate page request queue\n",
			iommu->name);
		वापस -ENOMEM;
	पूर्ण
	iommu->prq = page_address(pages);

	irq = dmar_alloc_hwirq(DMAR_UNITS_SUPPORTED + iommu->seq_id, iommu->node, iommu);
	अगर (irq <= 0) अणु
		pr_err("IOMMU: %s: Failed to create IRQ vector for page request queue\n",
		       iommu->name);
		ret = -EINVAL;
	err:
		मुक्त_pages((अचिन्हित दीर्घ)iommu->prq, PRQ_ORDER);
		iommu->prq = शून्य;
		वापस ret;
	पूर्ण
	iommu->pr_irq = irq;

	snम_लिखो(iommu->prq_name, माप(iommu->prq_name), "dmar%d-prq", iommu->seq_id);

	ret = request_thपढ़ोed_irq(irq, शून्य, prq_event_thपढ़ो, IRQF_ONESHOT,
				   iommu->prq_name, iommu);
	अगर (ret) अणु
		pr_err("IOMMU: %s: Failed to request IRQ for page request queue\n",
		       iommu->name);
		dmar_मुक्त_hwirq(irq);
		iommu->pr_irq = 0;
		जाओ err;
	पूर्ण
	dmar_ग_लिखोq(iommu->reg + DMAR_PQH_REG, 0ULL);
	dmar_ग_लिखोq(iommu->reg + DMAR_PQT_REG, 0ULL);
	dmar_ग_लिखोq(iommu->reg + DMAR_PQA_REG, virt_to_phys(iommu->prq) | PRQ_ORDER);

	init_completion(&iommu->prq_complete);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_svm_finish_prq(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	dmar_ग_लिखोq(iommu->reg + DMAR_PQH_REG, 0ULL);
	dmar_ग_लिखोq(iommu->reg + DMAR_PQT_REG, 0ULL);
	dmar_ग_लिखोq(iommu->reg + DMAR_PQA_REG, 0ULL);

	अगर (iommu->pr_irq) अणु
		मुक्त_irq(iommu->pr_irq, iommu);
		dmar_मुक्त_hwirq(iommu->pr_irq);
		iommu->pr_irq = 0;
	पूर्ण

	मुक्त_pages((अचिन्हित दीर्घ)iommu->prq, PRQ_ORDER);
	iommu->prq = शून्य;

	वापस 0;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_svm_capable(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	वापस iommu->flags & VTD_FLAG_SVM_CAPABLE;
पूर्ण

व्योम पूर्णांकel_svm_check(काष्ठा पूर्णांकel_iommu *iommu)
अणु
	अगर (!pasid_supported(iommu))
		वापस;

	अगर (cpu_feature_enabled(X86_FEATURE_GBPAGES) &&
	    !cap_fl1gp_support(iommu->cap)) अणु
		pr_err("%s SVM disabled, incompatible 1GB page capability\n",
		       iommu->name);
		वापस;
	पूर्ण

	अगर (cpu_feature_enabled(X86_FEATURE_LA57) &&
	    !cap_5lp_support(iommu->cap)) अणु
		pr_err("%s SVM disabled, incompatible paging mode\n",
		       iommu->name);
		वापस;
	पूर्ण

	iommu->flags |= VTD_FLAG_SVM_CAPABLE;
पूर्ण

अटल व्योम __flush_svm_range_dev(काष्ठा पूर्णांकel_svm *svm,
				  काष्ठा पूर्णांकel_svm_dev *sdev,
				  अचिन्हित दीर्घ address,
				  अचिन्हित दीर्घ pages, पूर्णांक ih)
अणु
	काष्ठा device_करोमुख्य_info *info = get_करोमुख्य_info(sdev->dev);

	अगर (WARN_ON(!pages))
		वापस;

	qi_flush_piotlb(sdev->iommu, sdev->did, svm->pasid, address, pages, ih);
	अगर (info->ats_enabled)
		qi_flush_dev_iotlb_pasid(sdev->iommu, sdev->sid, info->pfsid,
					 svm->pasid, sdev->qdep, address,
					 order_base_2(pages));
पूर्ण

अटल व्योम पूर्णांकel_flush_svm_range_dev(काष्ठा पूर्णांकel_svm *svm,
				      काष्ठा पूर्णांकel_svm_dev *sdev,
				      अचिन्हित दीर्घ address,
				      अचिन्हित दीर्घ pages, पूर्णांक ih)
अणु
	अचिन्हित दीर्घ shअगरt = ilog2(__roundup_घात_of_two(pages));
	अचिन्हित दीर्घ align = (1ULL << (VTD_PAGE_SHIFT + shअगरt));
	अचिन्हित दीर्घ start = ALIGN_DOWN(address, align);
	अचिन्हित दीर्घ end = ALIGN(address + (pages << VTD_PAGE_SHIFT), align);

	जबतक (start < end) अणु
		__flush_svm_range_dev(svm, sdev, start, align >> VTD_PAGE_SHIFT, ih);
		start += align;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_flush_svm_range(काष्ठा पूर्णांकel_svm *svm, अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ pages, पूर्णांक ih)
अणु
	काष्ठा पूर्णांकel_svm_dev *sdev;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdev, &svm->devs, list)
		पूर्णांकel_flush_svm_range_dev(svm, sdev, address, pages, ih);
	rcu_पढ़ो_unlock();
पूर्ण

/* Pages have been मुक्तd at this poपूर्णांक */
अटल व्योम पूर्णांकel_invalidate_range(काष्ठा mmu_notअगरier *mn,
				   काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा पूर्णांकel_svm *svm = container_of(mn, काष्ठा पूर्णांकel_svm, notअगरier);

	पूर्णांकel_flush_svm_range(svm, start,
			      (end - start + PAGE_SIZE - 1) >> VTD_PAGE_SHIFT, 0);
पूर्ण

अटल व्योम पूर्णांकel_mm_release(काष्ठा mmu_notअगरier *mn, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा पूर्णांकel_svm *svm = container_of(mn, काष्ठा पूर्णांकel_svm, notअगरier);
	काष्ठा पूर्णांकel_svm_dev *sdev;

	/* This might end up being called from निकास_mmap(), *beक्रमe* the page
	 * tables are cleared. And __mmu_notअगरier_release() will delete us from
	 * the list of notअगरiers so that our invalidate_range() callback करोesn't
	 * get called when the page tables are cleared. So we need to protect
	 * against hardware accessing those page tables.
	 *
	 * We करो it by clearing the entry in the PASID table and then flushing
	 * the IOTLB and the PASID table caches. This might upset hardware;
	 * perhaps we'll want to poपूर्णांक the PASID to a dummy PGD (like the zero
	 * page) so that we end up taking a fault that the hardware really
	 * *has* to handle gracefully without affecting other processes.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdev, &svm->devs, list)
		पूर्णांकel_pasid_tear_करोwn_entry(sdev->iommu, sdev->dev,
					    svm->pasid, true);
	rcu_पढ़ो_unlock();

पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops पूर्णांकel_mmuops = अणु
	.release = पूर्णांकel_mm_release,
	.invalidate_range = पूर्णांकel_invalidate_range,
पूर्ण;

अटल DEFINE_MUTEX(pasid_mutex);
अटल LIST_HEAD(global_svm_list);

#घोषणा क्रम_each_svm_dev(sdev, svm, d)			\
	list_क्रम_each_entry((sdev), &(svm)->devs, list)	\
		अगर ((d) != (sdev)->dev) अणुपूर्ण अन्यथा

अटल पूर्णांक pasid_to_svm_sdev(काष्ठा device *dev, अचिन्हित पूर्णांक pasid,
			     काष्ठा पूर्णांकel_svm **rsvm,
			     काष्ठा पूर्णांकel_svm_dev **rsdev)
अणु
	काष्ठा पूर्णांकel_svm_dev *d, *sdev = शून्य;
	काष्ठा पूर्णांकel_svm *svm;

	/* The caller should hold the pasid_mutex lock */
	अगर (WARN_ON(!mutex_is_locked(&pasid_mutex)))
		वापस -EINVAL;

	अगर (pasid == INVALID_IOASID || pasid >= PASID_MAX)
		वापस -EINVAL;

	svm = ioasid_find(शून्य, pasid, शून्य);
	अगर (IS_ERR(svm))
		वापस PTR_ERR(svm);

	अगर (!svm)
		जाओ out;

	/*
	 * If we found svm क्रम the PASID, there must be at least one device
	 * bond.
	 */
	अगर (WARN_ON(list_empty(&svm->devs)))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(d, &svm->devs, list) अणु
		अगर (d->dev == dev) अणु
			sdev = d;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	*rsvm = svm;
	*rsdev = sdev;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_svm_bind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			  काष्ठा iommu_gpasid_bind_data *data)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = device_to_iommu(dev, शून्य, शून्य);
	काष्ठा पूर्णांकel_svm_dev *sdev = शून्य;
	काष्ठा dmar_करोमुख्य *dmar_करोमुख्य;
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा पूर्णांकel_svm *svm = शून्य;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक ret = 0;

	अगर (WARN_ON(!iommu) || !data)
		वापस -EINVAL;

	अगर (data->क्रमmat != IOMMU_PASID_FORMAT_INTEL_VTD)
		वापस -EINVAL;

	/* IOMMU core ensures argsz is more than the start of the जोड़ */
	अगर (data->argsz < दुरत्वend(काष्ठा iommu_gpasid_bind_data, venकरोr.vtd))
		वापस -EINVAL;

	/* Make sure no undefined flags are used in venकरोr data */
	अगर (data->venकरोr.vtd.flags & ~(IOMMU_SVA_VTD_GPASID_LAST - 1))
		वापस -EINVAL;

	अगर (!dev_is_pci(dev))
		वापस -ENOTSUPP;

	/* VT-d supports devices with full 20 bit PASIDs only */
	अगर (pci_max_pasids(to_pci_dev(dev)) != PASID_MAX)
		वापस -EINVAL;

	/*
	 * We only check host PASID range, we have no knowledge to check
	 * guest PASID range.
	 */
	अगर (data->hpasid <= 0 || data->hpasid >= PASID_MAX)
		वापस -EINVAL;

	info = get_करोमुख्य_info(dev);
	अगर (!info)
		वापस -EINVAL;

	dmar_करोमुख्य = to_dmar_करोमुख्य(करोमुख्य);

	mutex_lock(&pasid_mutex);
	ret = pasid_to_svm_sdev(dev, data->hpasid, &svm, &sdev);
	अगर (ret)
		जाओ out;

	अगर (sdev) अणु
		/*
		 * Do not allow multiple bindings of the same device-PASID since
		 * there is only one SL page tables per PASID. We may revisit
		 * once sharing PGD across करोमुख्यs are supported.
		 */
		dev_warn_ratelimited(dev, "Already bound with PASID %u\n",
				     svm->pasid);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!svm) अणु
		/* We come here when PASID has never been bond to a device. */
		svm = kzalloc(माप(*svm), GFP_KERNEL);
		अगर (!svm) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		/* REVISIT: upper layer/VFIO can track host process that bind
		 * the PASID. ioasid_set = mm might be sufficient क्रम vfio to
		 * check pasid VMM ownership. We can drop the following line
		 * once VFIO and IOASID set check is in place.
		 */
		svm->mm = get_task_mm(current);
		svm->pasid = data->hpasid;
		अगर (data->flags & IOMMU_SVA_GPASID_VAL) अणु
			svm->gpasid = data->gpasid;
			svm->flags |= SVM_FLAG_GUEST_PASID;
		पूर्ण
		ioasid_set_data(data->hpasid, svm);
		INIT_LIST_HEAD_RCU(&svm->devs);
		mmput(svm->mm);
	पूर्ण
	sdev = kzalloc(माप(*sdev), GFP_KERNEL);
	अगर (!sdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	sdev->dev = dev;
	sdev->sid = PCI_DEVID(info->bus, info->devfn);
	sdev->iommu = iommu;

	/* Only count users अगर device has aux करोमुख्यs */
	अगर (iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX))
		sdev->users = 1;

	/* Set up device context entry क्रम PASID अगर not enabled alपढ़ोy */
	ret = पूर्णांकel_iommu_enable_pasid(iommu, sdev->dev);
	अगर (ret) अणु
		dev_err_ratelimited(dev, "Failed to enable PASID capability\n");
		kमुक्त(sdev);
		जाओ out;
	पूर्ण

	/*
	 * PASID table is per device क्रम better security. Thereक्रमe, क्रम
	 * each bind of a new device even with an existing PASID, we need to
	 * call the nested mode setup function here.
	 */
	spin_lock_irqsave(&iommu->lock, अगरlags);
	ret = पूर्णांकel_pasid_setup_nested(iommu, dev,
				       (pgd_t *)(uपूर्णांकptr_t)data->gpgd,
				       data->hpasid, &data->venकरोr.vtd, dmar_करोमुख्य,
				       data->addr_width);
	spin_unlock_irqrestore(&iommu->lock, अगरlags);
	अगर (ret) अणु
		dev_err_ratelimited(dev, "Failed to set up PASID %llu in nested mode, Err %d\n",
				    data->hpasid, ret);
		/*
		 * PASID entry should be in cleared state अगर nested mode
		 * set up failed. So we only need to clear IOASID tracking
		 * data such that मुक्त call will succeed.
		 */
		kमुक्त(sdev);
		जाओ out;
	पूर्ण

	svm->flags |= SVM_FLAG_GUEST_MODE;

	init_rcu_head(&sdev->rcu);
	list_add_rcu(&sdev->list, &svm->devs);
 out:
	अगर (!IS_ERR_OR_शून्य(svm) && list_empty(&svm->devs)) अणु
		ioasid_set_data(data->hpasid, शून्य);
		kमुक्त(svm);
	पूर्ण

	mutex_unlock(&pasid_mutex);
	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_svm_unbind_gpasid(काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = device_to_iommu(dev, शून्य, शून्य);
	काष्ठा पूर्णांकel_svm_dev *sdev;
	काष्ठा पूर्णांकel_svm *svm;
	पूर्णांक ret;

	अगर (WARN_ON(!iommu))
		वापस -EINVAL;

	mutex_lock(&pasid_mutex);
	ret = pasid_to_svm_sdev(dev, pasid, &svm, &sdev);
	अगर (ret)
		जाओ out;

	अगर (sdev) अणु
		अगर (iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX))
			sdev->users--;
		अगर (!sdev->users) अणु
			list_del_rcu(&sdev->list);
			पूर्णांकel_pasid_tear_करोwn_entry(iommu, dev,
						    svm->pasid, false);
			पूर्णांकel_svm_drain_prq(dev, svm->pasid);
			kमुक्त_rcu(sdev, rcu);

			अगर (list_empty(&svm->devs)) अणु
				/*
				 * We करो not मुक्त the IOASID here in that
				 * IOMMU driver did not allocate it.
				 * Unlike native SVM, IOASID क्रम guest use was
				 * allocated prior to the bind call.
				 * In any हाल, अगर the मुक्त call comes beक्रमe
				 * the unbind, IOMMU driver will get notअगरied
				 * and perक्रमm cleanup.
				 */
				ioasid_set_data(pasid, शून्य);
				kमुक्त(svm);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&pasid_mutex);
	वापस ret;
पूर्ण

अटल व्योम _load_pasid(व्योम *unused)
अणु
	update_pasid();
पूर्ण

अटल व्योम load_pasid(काष्ठा mm_काष्ठा *mm, u32 pasid)
अणु
	mutex_lock(&mm->context.lock);

	/* Synchronize with READ_ONCE in update_pasid(). */
	smp_store_release(&mm->pasid, pasid);

	/* Update PASID MSR on all CPUs running the mm's tasks. */
	on_each_cpu_mask(mm_cpumask(mm), _load_pasid, शून्य, true);

	mutex_unlock(&mm->context.lock);
पूर्ण

/* Caller must hold pasid_mutex, mm reference */
अटल पूर्णांक
पूर्णांकel_svm_bind_mm(काष्ठा device *dev, अचिन्हित पूर्णांक flags,
		  काष्ठा mm_काष्ठा *mm, काष्ठा पूर्णांकel_svm_dev **sd)
अणु
	काष्ठा पूर्णांकel_iommu *iommu = device_to_iommu(dev, शून्य, शून्य);
	काष्ठा पूर्णांकel_svm *svm = शून्य, *t;
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा पूर्णांकel_svm_dev *sdev;
	अचिन्हित दीर्घ अगरlags;
	पूर्णांक pasid_max;
	पूर्णांक ret;

	अगर (!iommu || dmar_disabled)
		वापस -EINVAL;

	अगर (!पूर्णांकel_svm_capable(iommu))
		वापस -ENOTSUPP;

	अगर (dev_is_pci(dev)) अणु
		pasid_max = pci_max_pasids(to_pci_dev(dev));
		अगर (pasid_max < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा
		pasid_max = 1 << 20;

	/* Bind supervisor PASID shuld have mm = शून्य */
	अगर (flags & SVM_FLAG_SUPERVISOR_MODE) अणु
		अगर (!ecap_srs(iommu->ecap) || mm) अणु
			pr_err("Supervisor PASID with user provided mm.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(t, &global_svm_list, list) अणु
		अगर (t->mm != mm)
			जारी;

		svm = t;
		अगर (svm->pasid >= pasid_max) अणु
			dev_warn(dev,
				 "Limited PASID width. Cannot use existing PASID %d\n",
				 svm->pasid);
			ret = -ENOSPC;
			जाओ out;
		पूर्ण

		/* Find the matching device in svm list */
		क्रम_each_svm_dev(sdev, svm, dev) अणु
			sdev->users++;
			जाओ success;
		पूर्ण

		अवरोध;
	पूर्ण

	sdev = kzalloc(माप(*sdev), GFP_KERNEL);
	अगर (!sdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	sdev->dev = dev;
	sdev->iommu = iommu;

	ret = पूर्णांकel_iommu_enable_pasid(iommu, dev);
	अगर (ret) अणु
		kमुक्त(sdev);
		जाओ out;
	पूर्ण

	info = get_करोमुख्य_info(dev);
	sdev->did = FLPT_DEFAULT_DID;
	sdev->sid = PCI_DEVID(info->bus, info->devfn);
	अगर (info->ats_enabled) अणु
		sdev->dev_iotlb = 1;
		sdev->qdep = info->ats_qdep;
		अगर (sdev->qdep >= QI_DEV_EIOTLB_MAX_INVS)
			sdev->qdep = 0;
	पूर्ण

	/* Finish the setup now we know we're keeping it */
	sdev->users = 1;
	init_rcu_head(&sdev->rcu);

	अगर (!svm) अणु
		svm = kzalloc(माप(*svm), GFP_KERNEL);
		अगर (!svm) अणु
			ret = -ENOMEM;
			kमुक्त(sdev);
			जाओ out;
		पूर्ण

		अगर (pasid_max > पूर्णांकel_pasid_max_id)
			pasid_max = पूर्णांकel_pasid_max_id;

		/* Do not use PASID 0, reserved क्रम RID to PASID */
		svm->pasid = ioasid_alloc(शून्य, PASID_MIN,
					  pasid_max - 1, svm);
		अगर (svm->pasid == INVALID_IOASID) अणु
			kमुक्त(svm);
			kमुक्त(sdev);
			ret = -ENOSPC;
			जाओ out;
		पूर्ण
		svm->notअगरier.ops = &पूर्णांकel_mmuops;
		svm->mm = mm;
		svm->flags = flags;
		INIT_LIST_HEAD_RCU(&svm->devs);
		INIT_LIST_HEAD(&svm->list);
		ret = -ENOMEM;
		अगर (mm) अणु
			ret = mmu_notअगरier_रेजिस्टर(&svm->notअगरier, mm);
			अगर (ret) अणु
				ioasid_put(svm->pasid);
				kमुक्त(svm);
				kमुक्त(sdev);
				जाओ out;
			पूर्ण
		पूर्ण

		spin_lock_irqsave(&iommu->lock, अगरlags);
		ret = पूर्णांकel_pasid_setup_first_level(iommu, dev,
				mm ? mm->pgd : init_mm.pgd,
				svm->pasid, FLPT_DEFAULT_DID,
				(mm ? 0 : PASID_FLAG_SUPERVISOR_MODE) |
				(cpu_feature_enabled(X86_FEATURE_LA57) ?
				 PASID_FLAG_FL5LP : 0));
		spin_unlock_irqrestore(&iommu->lock, अगरlags);
		अगर (ret) अणु
			अगर (mm)
				mmu_notअगरier_unरेजिस्टर(&svm->notअगरier, mm);
			ioasid_put(svm->pasid);
			kमुक्त(svm);
			kमुक्त(sdev);
			जाओ out;
		पूर्ण

		list_add_tail(&svm->list, &global_svm_list);
		अगर (mm) अणु
			/* The newly allocated pasid is loaded to the mm. */
			load_pasid(mm, svm->pasid);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Binding a new device with existing PASID, need to setup
		 * the PASID entry.
		 */
		spin_lock_irqsave(&iommu->lock, अगरlags);
		ret = पूर्णांकel_pasid_setup_first_level(iommu, dev,
						mm ? mm->pgd : init_mm.pgd,
						svm->pasid, FLPT_DEFAULT_DID,
						(mm ? 0 : PASID_FLAG_SUPERVISOR_MODE) |
						(cpu_feature_enabled(X86_FEATURE_LA57) ?
						PASID_FLAG_FL5LP : 0));
		spin_unlock_irqrestore(&iommu->lock, अगरlags);
		अगर (ret) अणु
			kमुक्त(sdev);
			जाओ out;
		पूर्ण
	पूर्ण
	list_add_rcu(&sdev->list, &svm->devs);
success:
	sdev->pasid = svm->pasid;
	sdev->sva.dev = dev;
	अगर (sd)
		*sd = sdev;
	ret = 0;
out:
	वापस ret;
पूर्ण

/* Caller must hold pasid_mutex */
अटल पूर्णांक पूर्णांकel_svm_unbind_mm(काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा पूर्णांकel_svm_dev *sdev;
	काष्ठा पूर्णांकel_iommu *iommu;
	काष्ठा पूर्णांकel_svm *svm;
	पूर्णांक ret = -EINVAL;

	iommu = device_to_iommu(dev, शून्य, शून्य);
	अगर (!iommu)
		जाओ out;

	ret = pasid_to_svm_sdev(dev, pasid, &svm, &sdev);
	अगर (ret)
		जाओ out;

	अगर (sdev) अणु
		sdev->users--;
		अगर (!sdev->users) अणु
			list_del_rcu(&sdev->list);
			/* Flush the PASID cache and IOTLB क्रम this device.
			 * Note that we करो depend on the hardware *not* using
			 * the PASID any more. Just as we depend on other
			 * devices never using PASIDs that they have no right
			 * to use. We have a *shared* PASID table, because it's
			 * large and has to be physically contiguous. So it's
			 * hard to be as defensive as we might like. */
			पूर्णांकel_pasid_tear_करोwn_entry(iommu, dev,
						    svm->pasid, false);
			पूर्णांकel_svm_drain_prq(dev, svm->pasid);
			kमुक्त_rcu(sdev, rcu);

			अगर (list_empty(&svm->devs)) अणु
				ioasid_put(svm->pasid);
				अगर (svm->mm) अणु
					mmu_notअगरier_unरेजिस्टर(&svm->notअगरier, svm->mm);
					/* Clear mm's pasid. */
					load_pasid(svm->mm, PASID_DISABLED);
				पूर्ण
				list_del(&svm->list);
				/* We mandate that no page faults may be outstanding
				 * क्रम the PASID when पूर्णांकel_svm_unbind_mm() is called.
				 * If that is not obeyed, subtle errors will happen.
				 * Let's make them less subtle... */
				स_रखो(svm, 0x6b, माप(*svm));
				kमुक्त(svm);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/* Page request queue descriptor */
काष्ठा page_req_dsc अणु
	जोड़ अणु
		काष्ठा अणु
			u64 type:8;
			u64 pasid_present:1;
			u64 priv_data_present:1;
			u64 rsvd:6;
			u64 rid:16;
			u64 pasid:20;
			u64 exe_req:1;
			u64 pm_req:1;
			u64 rsvd2:10;
		पूर्ण;
		u64 qw_0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u64 rd_req:1;
			u64 wr_req:1;
			u64 lpig:1;
			u64 prg_index:9;
			u64 addr:52;
		पूर्ण;
		u64 qw_1;
	पूर्ण;
	u64 priv_data[2];
पूर्ण;

#घोषणा PRQ_RING_MASK	((0x1000 << PRQ_ORDER) - 0x20)

अटल bool access_error(काष्ठा vm_area_काष्ठा *vma, काष्ठा page_req_dsc *req)
अणु
	अचिन्हित दीर्घ requested = 0;

	अगर (req->exe_req)
		requested |= VM_EXEC;

	अगर (req->rd_req)
		requested |= VM_READ;

	अगर (req->wr_req)
		requested |= VM_WRITE;

	वापस (requested & ~vma->vm_flags) != 0;
पूर्ण

अटल bool is_canonical_address(u64 addr)
अणु
	पूर्णांक shअगरt = 64 - (__VIRTUAL_MASK_SHIFT + 1);
	दीर्घ saddr = (दीर्घ) addr;

	वापस (((saddr << shअगरt) >> shअगरt) == saddr);
पूर्ण

/**
 * पूर्णांकel_svm_drain_prq - Drain page requests and responses क्रम a pasid
 * @dev: target device
 * @pasid: pasid क्रम draining
 *
 * Drain all pending page requests and responses related to @pasid in both
 * software and hardware. This is supposed to be called after the device
 * driver has stopped DMA, the pasid entry has been cleared, and both IOTLB
 * and DevTLB have been invalidated.
 *
 * It रुकोs until all pending page requests क्रम @pasid in the page fault
 * queue are completed by the prq handling thपढ़ो. Then follow the steps
 * described in VT-d spec CH7.10 to drain all page requests and page
 * responses pending in the hardware.
 */
अटल व्योम पूर्णांकel_svm_drain_prq(काष्ठा device *dev, u32 pasid)
अणु
	काष्ठा device_करोमुख्य_info *info;
	काष्ठा dmar_करोमुख्य *करोमुख्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	काष्ठा qi_desc desc[3];
	काष्ठा pci_dev *pdev;
	पूर्णांक head, tail;
	u16 sid, did;
	पूर्णांक qdep;

	info = get_करोमुख्य_info(dev);
	अगर (WARN_ON(!info || !dev_is_pci(dev)))
		वापस;

	अगर (!info->pri_enabled)
		वापस;

	iommu = info->iommu;
	करोमुख्य = info->करोमुख्य;
	pdev = to_pci_dev(dev);
	sid = PCI_DEVID(info->bus, info->devfn);
	did = करोमुख्य->iommu_did[iommu->seq_id];
	qdep = pci_ats_queue_depth(pdev);

	/*
	 * Check and रुको until all pending page requests in the queue are
	 * handled by the prq handling thपढ़ो.
	 */
prq_retry:
	reinit_completion(&iommu->prq_complete);
	tail = dmar_पढ़ोq(iommu->reg + DMAR_PQT_REG) & PRQ_RING_MASK;
	head = dmar_पढ़ोq(iommu->reg + DMAR_PQH_REG) & PRQ_RING_MASK;
	जबतक (head != tail) अणु
		काष्ठा page_req_dsc *req;

		req = &iommu->prq[head / माप(*req)];
		अगर (!req->pasid_present || req->pasid != pasid) अणु
			head = (head + माप(*req)) & PRQ_RING_MASK;
			जारी;
		पूर्ण

		रुको_क्रम_completion(&iommu->prq_complete);
		जाओ prq_retry;
	पूर्ण

	/*
	 * Perक्रमm steps described in VT-d spec CH7.10 to drain page
	 * requests and responses in hardware.
	 */
	स_रखो(desc, 0, माप(desc));
	desc[0].qw0 = QI_IWD_STATUS_DATA(QI_DONE) |
			QI_IWD_FENCE |
			QI_IWD_TYPE;
	desc[1].qw0 = QI_EIOTLB_PASID(pasid) |
			QI_EIOTLB_DID(did) |
			QI_EIOTLB_GRAN(QI_GRAN_NONG_PASID) |
			QI_EIOTLB_TYPE;
	desc[2].qw0 = QI_DEV_EIOTLB_PASID(pasid) |
			QI_DEV_EIOTLB_SID(sid) |
			QI_DEV_EIOTLB_QDEP(qdep) |
			QI_DEIOTLB_TYPE |
			QI_DEV_IOTLB_PFSID(info->pfsid);
qi_retry:
	reinit_completion(&iommu->prq_complete);
	qi_submit_sync(iommu, desc, 3, QI_OPT_WAIT_DRAIN);
	अगर (पढ़ोl(iommu->reg + DMAR_PRS_REG) & DMA_PRS_PRO) अणु
		रुको_क्रम_completion(&iommu->prq_complete);
		जाओ qi_retry;
	पूर्ण
पूर्ण

अटल पूर्णांक prq_to_iommu_prot(काष्ठा page_req_dsc *req)
अणु
	पूर्णांक prot = 0;

	अगर (req->rd_req)
		prot |= IOMMU_FAULT_PERM_READ;
	अगर (req->wr_req)
		prot |= IOMMU_FAULT_PERM_WRITE;
	अगर (req->exe_req)
		prot |= IOMMU_FAULT_PERM_EXEC;
	अगर (req->pm_req)
		prot |= IOMMU_FAULT_PERM_PRIV;

	वापस prot;
पूर्ण

अटल पूर्णांक
पूर्णांकel_svm_prq_report(काष्ठा device *dev, काष्ठा page_req_dsc *desc)
अणु
	काष्ठा iommu_fault_event event;

	अगर (!dev || !dev_is_pci(dev))
		वापस -ENODEV;

	/* Fill in event data क्रम device specअगरic processing */
	स_रखो(&event, 0, माप(काष्ठा iommu_fault_event));
	event.fault.type = IOMMU_FAULT_PAGE_REQ;
	event.fault.prm.addr = (u64)desc->addr << VTD_PAGE_SHIFT;
	event.fault.prm.pasid = desc->pasid;
	event.fault.prm.grpid = desc->prg_index;
	event.fault.prm.perm = prq_to_iommu_prot(desc);

	अगर (desc->lpig)
		event.fault.prm.flags |= IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE;
	अगर (desc->pasid_present) अणु
		event.fault.prm.flags |= IOMMU_FAULT_PAGE_REQUEST_PASID_VALID;
		event.fault.prm.flags |= IOMMU_FAULT_PAGE_RESPONSE_NEEDS_PASID;
	पूर्ण
	अगर (desc->priv_data_present) अणु
		/*
		 * Set last page in group bit अगर निजी data is present,
		 * page response is required as it करोes क्रम LPIG.
		 * iommu_report_device_fault() करोesn't understand this venकरोr
		 * specअगरic requirement thus we set last_page as a workaround.
		 */
		event.fault.prm.flags |= IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE;
		event.fault.prm.flags |= IOMMU_FAULT_PAGE_REQUEST_PRIV_DATA;
		स_नकल(event.fault.prm.निजी_data, desc->priv_data,
		       माप(desc->priv_data));
	पूर्ण

	वापस iommu_report_device_fault(dev, &event);
पूर्ण

अटल irqवापस_t prq_event_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा पूर्णांकel_svm_dev *sdev = शून्य;
	काष्ठा पूर्णांकel_iommu *iommu = d;
	काष्ठा पूर्णांकel_svm *svm = शून्य;
	पूर्णांक head, tail, handled = 0;
	अचिन्हित पूर्णांक flags = 0;

	/* Clear PPR bit beक्रमe पढ़ोing head/tail रेजिस्टरs, to
	 * ensure that we get a new पूर्णांकerrupt अगर needed. */
	ग_लिखोl(DMA_PRS_PPR, iommu->reg + DMAR_PRS_REG);

	tail = dmar_पढ़ोq(iommu->reg + DMAR_PQT_REG) & PRQ_RING_MASK;
	head = dmar_पढ़ोq(iommu->reg + DMAR_PQH_REG) & PRQ_RING_MASK;
	जबतक (head != tail) अणु
		काष्ठा vm_area_काष्ठा *vma;
		काष्ठा page_req_dsc *req;
		काष्ठा qi_desc resp;
		पूर्णांक result;
		vm_fault_t ret;
		u64 address;

		handled = 1;
		req = &iommu->prq[head / माप(*req)];
		result = QI_RESP_INVALID;
		address = (u64)req->addr << VTD_PAGE_SHIFT;
		अगर (!req->pasid_present) अणु
			pr_err("%s: Page request without PASID: %08llx %08llx\n",
			       iommu->name, ((अचिन्हित दीर्घ दीर्घ *)req)[0],
			       ((अचिन्हित दीर्घ दीर्घ *)req)[1]);
			जाओ no_pasid;
		पूर्ण
		/* We shall not receive page request क्रम supervisor SVM */
		अगर (req->pm_req && (req->rd_req | req->wr_req)) अणु
			pr_err("Unexpected page request in Privilege Mode");
			/* No need to find the matching sdev as क्रम bad_req */
			जाओ no_pasid;
		पूर्ण
		/* DMA पढ़ो with exec requeset is not supported. */
		अगर (req->exe_req && req->rd_req) अणु
			pr_err("Execution request not supported\n");
			जाओ no_pasid;
		पूर्ण
		अगर (!svm || svm->pasid != req->pasid) अणु
			rcu_पढ़ो_lock();
			svm = ioasid_find(शून्य, req->pasid, शून्य);
			/* It *can't* go away, because the driver is not permitted
			 * to unbind the mm जबतक any page faults are outstanding.
			 * So we only need RCU to protect the पूर्णांकernal idr code. */
			rcu_पढ़ो_unlock();
			अगर (IS_ERR_OR_शून्य(svm)) अणु
				pr_err("%s: Page request for invalid PASID %d: %08llx %08llx\n",
				       iommu->name, req->pasid, ((अचिन्हित दीर्घ दीर्घ *)req)[0],
				       ((अचिन्हित दीर्घ दीर्घ *)req)[1]);
				जाओ no_pasid;
			पूर्ण
		पूर्ण

		अगर (!sdev || sdev->sid != req->rid) अणु
			काष्ठा पूर्णांकel_svm_dev *t;

			sdev = शून्य;
			rcu_पढ़ो_lock();
			list_क्रम_each_entry_rcu(t, &svm->devs, list) अणु
				अगर (t->sid == req->rid) अणु
					sdev = t;
					अवरोध;
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण

		/* Since we're using init_mm.pgd directly, we should never take
		 * any faults on kernel addresses. */
		अगर (!svm->mm)
			जाओ bad_req;

		/* If address is not canonical, वापस invalid response */
		अगर (!is_canonical_address(address))
			जाओ bad_req;

		/*
		 * If prq is to be handled outside iommu driver via receiver of
		 * the fault notअगरiers, we skip the page response here.
		 */
		अगर (svm->flags & SVM_FLAG_GUEST_MODE) अणु
			अगर (sdev && !पूर्णांकel_svm_prq_report(sdev->dev, req))
				जाओ prq_advance;
			अन्यथा
				जाओ bad_req;
		पूर्ण

		/* If the mm is alपढ़ोy defunct, करोn't handle faults. */
		अगर (!mmget_not_zero(svm->mm))
			जाओ bad_req;

		mmap_पढ़ो_lock(svm->mm);
		vma = find_extend_vma(svm->mm, address);
		अगर (!vma || address < vma->vm_start)
			जाओ invalid;

		अगर (access_error(vma, req))
			जाओ invalid;

		flags = FAULT_FLAG_USER | FAULT_FLAG_REMOTE;
		अगर (req->wr_req)
			flags |= FAULT_FLAG_WRITE;

		ret = handle_mm_fault(vma, address, flags, शून्य);
		अगर (ret & VM_FAULT_ERROR)
			जाओ invalid;

		result = QI_RESP_SUCCESS;
invalid:
		mmap_पढ़ो_unlock(svm->mm);
		mmput(svm->mm);
bad_req:
		/* We get here in the error हाल where the PASID lookup failed,
		   and these can be शून्य. Do not use them below this poपूर्णांक! */
		sdev = शून्य;
		svm = शून्य;
no_pasid:
		अगर (req->lpig || req->priv_data_present) अणु
			/*
			 * Per VT-d spec. v3.0 ch7.7, प्रणाली software must
			 * respond with page group response अगर निजी data
			 * is present (PDP) or last page in group (LPIG) bit
			 * is set. This is an additional VT-d feature beyond
			 * PCI ATS spec.
			 */
			resp.qw0 = QI_PGRP_PASID(req->pasid) |
				QI_PGRP_DID(req->rid) |
				QI_PGRP_PASID_P(req->pasid_present) |
				QI_PGRP_PDP(req->priv_data_present) |
				QI_PGRP_RESP_CODE(result) |
				QI_PGRP_RESP_TYPE;
			resp.qw1 = QI_PGRP_IDX(req->prg_index) |
				QI_PGRP_LPIG(req->lpig);
			resp.qw2 = 0;
			resp.qw3 = 0;

			अगर (req->priv_data_present)
				स_नकल(&resp.qw2, req->priv_data,
				       माप(req->priv_data));
			qi_submit_sync(iommu, &resp, 1, 0);
		पूर्ण
prq_advance:
		head = (head + माप(*req)) & PRQ_RING_MASK;
	पूर्ण

	dmar_ग_लिखोq(iommu->reg + DMAR_PQH_REG, tail);

	/*
	 * Clear the page request overflow bit and wake up all thपढ़ोs that
	 * are रुकोing क्रम the completion of this handling.
	 */
	अगर (पढ़ोl(iommu->reg + DMAR_PRS_REG) & DMA_PRS_PRO) अणु
		pr_info_ratelimited("IOMMU: %s: PRQ overflow detected\n",
				    iommu->name);
		head = dmar_पढ़ोq(iommu->reg + DMAR_PQH_REG) & PRQ_RING_MASK;
		tail = dmar_पढ़ोq(iommu->reg + DMAR_PQT_REG) & PRQ_RING_MASK;
		अगर (head == tail) अणु
			ग_लिखोl(DMA_PRS_PRO, iommu->reg + DMAR_PRS_REG);
			pr_info_ratelimited("IOMMU: %s: PRQ overflow cleared",
					    iommu->name);
		पूर्ण
	पूर्ण

	अगर (!completion_करोne(&iommu->prq_complete))
		complete(&iommu->prq_complete);

	वापस IRQ_RETVAL(handled);
पूर्ण

#घोषणा to_पूर्णांकel_svm_dev(handle) container_of(handle, काष्ठा पूर्णांकel_svm_dev, sva)
काष्ठा iommu_sva *
पूर्णांकel_svm_bind(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm, व्योम *drvdata)
अणु
	काष्ठा iommu_sva *sva = ERR_PTR(-EINVAL);
	काष्ठा पूर्णांकel_svm_dev *sdev = शून्य;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक ret;

	/*
	 * TODO: Consolidate with generic iommu-sva bind after it is merged.
	 * It will require shared SVM data काष्ठाures, i.e. combine io_mm
	 * and पूर्णांकel_svm etc.
	 */
	अगर (drvdata)
		flags = *(अचिन्हित पूर्णांक *)drvdata;
	mutex_lock(&pasid_mutex);
	ret = पूर्णांकel_svm_bind_mm(dev, flags, mm, &sdev);
	अगर (ret)
		sva = ERR_PTR(ret);
	अन्यथा अगर (sdev)
		sva = &sdev->sva;
	अन्यथा
		WARN(!sdev, "SVM bind succeeded with no sdev!\n");

	mutex_unlock(&pasid_mutex);

	वापस sva;
पूर्ण

व्योम पूर्णांकel_svm_unbind(काष्ठा iommu_sva *sva)
अणु
	काष्ठा पूर्णांकel_svm_dev *sdev;

	mutex_lock(&pasid_mutex);
	sdev = to_पूर्णांकel_svm_dev(sva);
	पूर्णांकel_svm_unbind_mm(sdev->dev, sdev->pasid);
	mutex_unlock(&pasid_mutex);
पूर्ण

u32 पूर्णांकel_svm_get_pasid(काष्ठा iommu_sva *sva)
अणु
	काष्ठा पूर्णांकel_svm_dev *sdev;
	u32 pasid;

	mutex_lock(&pasid_mutex);
	sdev = to_पूर्णांकel_svm_dev(sva);
	pasid = sdev->pasid;
	mutex_unlock(&pasid_mutex);

	वापस pasid;
पूर्ण

पूर्णांक पूर्णांकel_svm_page_response(काष्ठा device *dev,
			    काष्ठा iommu_fault_event *evt,
			    काष्ठा iommu_page_response *msg)
अणु
	काष्ठा iommu_fault_page_request *prm;
	काष्ठा पूर्णांकel_svm_dev *sdev = शून्य;
	काष्ठा पूर्णांकel_svm *svm = शून्य;
	काष्ठा पूर्णांकel_iommu *iommu;
	bool निजी_present;
	bool pasid_present;
	bool last_page;
	u8 bus, devfn;
	पूर्णांक ret = 0;
	u16 sid;

	अगर (!dev || !dev_is_pci(dev))
		वापस -ENODEV;

	iommu = device_to_iommu(dev, &bus, &devfn);
	अगर (!iommu)
		वापस -ENODEV;

	अगर (!msg || !evt)
		वापस -EINVAL;

	mutex_lock(&pasid_mutex);

	prm = &evt->fault.prm;
	sid = PCI_DEVID(bus, devfn);
	pasid_present = prm->flags & IOMMU_FAULT_PAGE_REQUEST_PASID_VALID;
	निजी_present = prm->flags & IOMMU_FAULT_PAGE_REQUEST_PRIV_DATA;
	last_page = prm->flags & IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE;

	अगर (!pasid_present) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (prm->pasid == 0 || prm->pasid >= PASID_MAX) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = pasid_to_svm_sdev(dev, prm->pasid, &svm, &sdev);
	अगर (ret || !sdev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * For responses from userspace, need to make sure that the
	 * pasid has been bound to its mm.
	 */
	अगर (svm->flags & SVM_FLAG_GUEST_MODE) अणु
		काष्ठा mm_काष्ठा *mm;

		mm = get_task_mm(current);
		अगर (!mm) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (mm != svm->mm) अणु
			ret = -ENODEV;
			mmput(mm);
			जाओ out;
		पूर्ण

		mmput(mm);
	पूर्ण

	/*
	 * Per VT-d spec. v3.0 ch7.7, प्रणाली software must respond
	 * with page group response अगर निजी data is present (PDP)
	 * or last page in group (LPIG) bit is set. This is an
	 * additional VT-d requirement beyond PCI ATS spec.
	 */
	अगर (last_page || निजी_present) अणु
		काष्ठा qi_desc desc;

		desc.qw0 = QI_PGRP_PASID(prm->pasid) | QI_PGRP_DID(sid) |
				QI_PGRP_PASID_P(pasid_present) |
				QI_PGRP_PDP(निजी_present) |
				QI_PGRP_RESP_CODE(msg->code) |
				QI_PGRP_RESP_TYPE;
		desc.qw1 = QI_PGRP_IDX(prm->grpid) | QI_PGRP_LPIG(last_page);
		desc.qw2 = 0;
		desc.qw3 = 0;
		अगर (निजी_present)
			स_नकल(&desc.qw2, prm->निजी_data,
			       माप(prm->निजी_data));

		qi_submit_sync(iommu, &desc, 1, 0);
	पूर्ण
out:
	mutex_unlock(&pasid_mutex);
	वापस ret;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <linux/lockdep.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/suspend.h>
#समावेश <linux/sched/mm.h>
#समावेश <यंत्र/sgx.h>
#समावेश "encl.h"
#समावेश "encls.h"
#समावेश "sgx.h"

/*
 * ELDU: Load an EPC page as unblocked. For more info, see "OS Management of EPC
 * Pages" in the SDM.
 */
अटल पूर्णांक __sgx_encl_eldu(काष्ठा sgx_encl_page *encl_page,
			   काष्ठा sgx_epc_page *epc_page,
			   काष्ठा sgx_epc_page *secs_page)
अणु
	अचिन्हित दीर्घ va_offset = encl_page->desc & SGX_ENCL_PAGE_VA_OFFSET_MASK;
	काष्ठा sgx_encl *encl = encl_page->encl;
	काष्ठा sgx_pageinfo pginfo;
	काष्ठा sgx_backing b;
	pgoff_t page_index;
	पूर्णांक ret;

	अगर (secs_page)
		page_index = PFN_DOWN(encl_page->desc - encl_page->encl->base);
	अन्यथा
		page_index = PFN_DOWN(encl->size);

	ret = sgx_encl_get_backing(encl, page_index, &b);
	अगर (ret)
		वापस ret;

	pginfo.addr = encl_page->desc & PAGE_MASK;
	pginfo.contents = (अचिन्हित दीर्घ)kmap_atomic(b.contents);
	pginfo.metadata = (अचिन्हित दीर्घ)kmap_atomic(b.pcmd) +
			  b.pcmd_offset;

	अगर (secs_page)
		pginfo.secs = (u64)sgx_get_epc_virt_addr(secs_page);
	अन्यथा
		pginfo.secs = 0;

	ret = __eldu(&pginfo, sgx_get_epc_virt_addr(epc_page),
		     sgx_get_epc_virt_addr(encl_page->va_page->epc_page) + va_offset);
	अगर (ret) अणु
		अगर (encls_failed(ret))
			ENCLS_WARN(ret, "ELDU");

		ret = -EFAULT;
	पूर्ण

	kunmap_atomic((व्योम *)(अचिन्हित दीर्घ)(pginfo.metadata - b.pcmd_offset));
	kunmap_atomic((व्योम *)(अचिन्हित दीर्घ)pginfo.contents);

	sgx_encl_put_backing(&b, false);

	वापस ret;
पूर्ण

अटल काष्ठा sgx_epc_page *sgx_encl_eldu(काष्ठा sgx_encl_page *encl_page,
					  काष्ठा sgx_epc_page *secs_page)
अणु

	अचिन्हित दीर्घ va_offset = encl_page->desc & SGX_ENCL_PAGE_VA_OFFSET_MASK;
	काष्ठा sgx_encl *encl = encl_page->encl;
	काष्ठा sgx_epc_page *epc_page;
	पूर्णांक ret;

	epc_page = sgx_alloc_epc_page(encl_page, false);
	अगर (IS_ERR(epc_page))
		वापस epc_page;

	ret = __sgx_encl_eldu(encl_page, epc_page, secs_page);
	अगर (ret) अणु
		sgx_encl_मुक्त_epc_page(epc_page);
		वापस ERR_PTR(ret);
	पूर्ण

	sgx_मुक्त_va_slot(encl_page->va_page, va_offset);
	list_move(&encl_page->va_page->list, &encl->va_pages);
	encl_page->desc &= ~SGX_ENCL_PAGE_VA_OFFSET_MASK;
	encl_page->epc_page = epc_page;

	वापस epc_page;
पूर्ण

अटल काष्ठा sgx_encl_page *sgx_encl_load_page(काष्ठा sgx_encl *encl,
						अचिन्हित दीर्घ addr,
						अचिन्हित दीर्घ vm_flags)
अणु
	अचिन्हित दीर्घ vm_prot_bits = vm_flags & (VM_READ | VM_WRITE | VM_EXEC);
	काष्ठा sgx_epc_page *epc_page;
	काष्ठा sgx_encl_page *entry;

	entry = xa_load(&encl->page_array, PFN_DOWN(addr));
	अगर (!entry)
		वापस ERR_PTR(-EFAULT);

	/*
	 * Verअगरy that the faulted page has equal or higher build समय
	 * permissions than the VMA permissions (i.e. the subset of अणुVM_READ,
	 * VM_WRITE, VM_EXECUTEपूर्ण in vma->vm_flags).
	 */
	अगर ((entry->vm_max_prot_bits & vm_prot_bits) != vm_prot_bits)
		वापस ERR_PTR(-EFAULT);

	/* Entry successfully located. */
	अगर (entry->epc_page) अणु
		अगर (entry->desc & SGX_ENCL_PAGE_BEING_RECLAIMED)
			वापस ERR_PTR(-EBUSY);

		वापस entry;
	पूर्ण

	अगर (!(encl->secs.epc_page)) अणु
		epc_page = sgx_encl_eldu(&encl->secs, शून्य);
		अगर (IS_ERR(epc_page))
			वापस ERR_CAST(epc_page);
	पूर्ण

	epc_page = sgx_encl_eldu(entry, encl->secs.epc_page);
	अगर (IS_ERR(epc_page))
		वापस ERR_CAST(epc_page);

	encl->secs_child_cnt++;
	sgx_mark_page_reclaimable(entry->epc_page);

	वापस entry;
पूर्ण

अटल vm_fault_t sgx_vma_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)vmf->address;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा sgx_encl_page *entry;
	अचिन्हित दीर्घ phys_addr;
	काष्ठा sgx_encl *encl;
	vm_fault_t ret;

	encl = vma->vm_निजी_data;

	/*
	 * It's very unlikely but possible that allocating memory क्रम the
	 * mm_list entry of a विभाजनed process failed in sgx_vma_खोलो(). When
	 * this happens, vm_निजी_data is set to शून्य.
	 */
	अगर (unlikely(!encl))
		वापस VM_FAULT_SIGBUS;

	mutex_lock(&encl->lock);

	entry = sgx_encl_load_page(encl, addr, vma->vm_flags);
	अगर (IS_ERR(entry)) अणु
		mutex_unlock(&encl->lock);

		अगर (PTR_ERR(entry) == -EBUSY)
			वापस VM_FAULT_NOPAGE;

		वापस VM_FAULT_SIGBUS;
	पूर्ण

	phys_addr = sgx_get_epc_phys_addr(entry->epc_page);

	ret = vmf_insert_pfn(vma, addr, PFN_DOWN(phys_addr));
	अगर (ret != VM_FAULT_NOPAGE) अणु
		mutex_unlock(&encl->lock);

		वापस VM_FAULT_SIGBUS;
	पूर्ण

	sgx_encl_test_and_clear_young(vma->vm_mm, entry);
	mutex_unlock(&encl->lock);

	वापस VM_FAULT_NOPAGE;
पूर्ण

अटल व्योम sgx_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sgx_encl *encl = vma->vm_निजी_data;

	/*
	 * It's possible but unlikely that vm_निजी_data is शून्य. This can
	 * happen in a gअक्रमchild of a process, when sgx_encl_mm_add() had
	 * failed to allocate memory in this callback.
	 */
	अगर (unlikely(!encl))
		वापस;

	अगर (sgx_encl_mm_add(encl, vma->vm_mm))
		vma->vm_निजी_data = शून्य;
पूर्ण


/**
 * sgx_encl_may_map() - Check अगर a requested VMA mapping is allowed
 * @encl:		an enclave poपूर्णांकer
 * @start:		lower bound of the address range, inclusive
 * @end:		upper bound of the address range, exclusive
 * @vm_flags:		VMA flags
 *
 * Iterate through the enclave pages contained within [@start, @end) to verअगरy
 * that the permissions requested by a subset of अणुVM_READ, VM_WRITE, VM_EXECपूर्ण
 * करो not contain any permissions that are not contained in the build समय
 * permissions of any of the enclave pages within the given address range.
 *
 * An enclave creator must declare the strongest permissions that will be
 * needed क्रम each enclave page. This ensures that mappings have the identical
 * or weaker permissions than the earlier declared permissions.
 *
 * Return: 0 on success, -EACCES otherwise
 */
पूर्णांक sgx_encl_may_map(काष्ठा sgx_encl *encl, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end, अचिन्हित दीर्घ vm_flags)
अणु
	अचिन्हित दीर्घ vm_prot_bits = vm_flags & (VM_READ | VM_WRITE | VM_EXEC);
	काष्ठा sgx_encl_page *page;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक ret = 0;

	XA_STATE(xas, &encl->page_array, PFN_DOWN(start));

	/*
	 * Disallow READ_IMPLIES_EXEC tasks as their VMA permissions might
	 * conflict with the enclave page permissions.
	 */
	अगर (current->personality & READ_IMPLIES_EXEC)
		वापस -EACCES;

	mutex_lock(&encl->lock);
	xas_lock(&xas);
	xas_क्रम_each(&xas, page, PFN_DOWN(end - 1)) अणु
		अगर (~page->vm_max_prot_bits & vm_prot_bits) अणु
			ret = -EACCES;
			अवरोध;
		पूर्ण

		/* Reschedule on every XA_CHECK_SCHED iteration. */
		अगर (!(++count % XA_CHECK_SCHED)) अणु
			xas_छोड़ो(&xas);
			xas_unlock(&xas);
			mutex_unlock(&encl->lock);

			cond_resched();

			mutex_lock(&encl->lock);
			xas_lock(&xas);
		पूर्ण
	पूर्ण
	xas_unlock(&xas);
	mutex_unlock(&encl->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sgx_vma_mprotect(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end, अचिन्हित दीर्घ newflags)
अणु
	वापस sgx_encl_may_map(vma->vm_निजी_data, start, end, newflags);
पूर्ण

अटल पूर्णांक sgx_encl_debug_पढ़ो(काष्ठा sgx_encl *encl, काष्ठा sgx_encl_page *page,
			       अचिन्हित दीर्घ addr, व्योम *data)
अणु
	अचिन्हित दीर्घ offset = addr & ~PAGE_MASK;
	पूर्णांक ret;


	ret = __edbgrd(sgx_get_epc_virt_addr(page->epc_page) + offset, data);
	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_encl_debug_ग_लिखो(काष्ठा sgx_encl *encl, काष्ठा sgx_encl_page *page,
				अचिन्हित दीर्घ addr, व्योम *data)
अणु
	अचिन्हित दीर्घ offset = addr & ~PAGE_MASK;
	पूर्णांक ret;

	ret = __edbgwr(sgx_get_epc_virt_addr(page->epc_page) + offset, data);
	अगर (ret)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Load an enclave page to EPC अगर required, and take encl->lock.
 */
अटल काष्ठा sgx_encl_page *sgx_encl_reserve_page(काष्ठा sgx_encl *encl,
						   अचिन्हित दीर्घ addr,
						   अचिन्हित दीर्घ vm_flags)
अणु
	काष्ठा sgx_encl_page *entry;

	क्रम ( ; ; ) अणु
		mutex_lock(&encl->lock);

		entry = sgx_encl_load_page(encl, addr, vm_flags);
		अगर (PTR_ERR(entry) != -EBUSY)
			अवरोध;

		mutex_unlock(&encl->lock);
	पूर्ण

	अगर (IS_ERR(entry))
		mutex_unlock(&encl->lock);

	वापस entry;
पूर्ण

अटल पूर्णांक sgx_vma_access(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			  व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा sgx_encl *encl = vma->vm_निजी_data;
	काष्ठा sgx_encl_page *entry = शून्य;
	अक्षर data[माप(अचिन्हित दीर्घ)];
	अचिन्हित दीर्घ align;
	पूर्णांक offset;
	पूर्णांक cnt;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/*
	 * If process was विभाजनed, VMA is still there but vm_निजी_data is set
	 * to शून्य.
	 */
	अगर (!encl)
		वापस -EFAULT;

	अगर (!test_bit(SGX_ENCL_DEBUG, &encl->flags))
		वापस -EFAULT;

	क्रम (i = 0; i < len; i += cnt) अणु
		entry = sgx_encl_reserve_page(encl, (addr + i) & PAGE_MASK,
					      vma->vm_flags);
		अगर (IS_ERR(entry)) अणु
			ret = PTR_ERR(entry);
			अवरोध;
		पूर्ण

		align = ALIGN_DOWN(addr + i, माप(अचिन्हित दीर्घ));
		offset = (addr + i) & (माप(अचिन्हित दीर्घ) - 1);
		cnt = माप(अचिन्हित दीर्घ) - offset;
		cnt = min(cnt, len - i);

		ret = sgx_encl_debug_पढ़ो(encl, entry, align, data);
		अगर (ret)
			जाओ out;

		अगर (ग_लिखो) अणु
			स_नकल(data + offset, buf + i, cnt);
			ret = sgx_encl_debug_ग_लिखो(encl, entry, align, data);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अणु
			स_नकल(buf + i, data + offset, cnt);
		पूर्ण

out:
		mutex_unlock(&encl->lock);

		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret < 0 ? ret : i;
पूर्ण

स्थिर काष्ठा vm_operations_काष्ठा sgx_vm_ops = अणु
	.fault = sgx_vma_fault,
	.mprotect = sgx_vma_mprotect,
	.खोलो = sgx_vma_खोलो,
	.access = sgx_vma_access,
पूर्ण;

/**
 * sgx_encl_release - Destroy an enclave instance
 * @kref:	address of a kref inside &sgx_encl
 *
 * Used together with kref_put(). Frees all the resources associated with the
 * enclave and the instance itself.
 */
व्योम sgx_encl_release(काष्ठा kref *ref)
अणु
	काष्ठा sgx_encl *encl = container_of(ref, काष्ठा sgx_encl, refcount);
	काष्ठा sgx_va_page *va_page;
	काष्ठा sgx_encl_page *entry;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&encl->page_array, index, entry) अणु
		अगर (entry->epc_page) अणु
			/*
			 * The page and its radix tree entry cannot be मुक्तd
			 * अगर the page is being held by the reclaimer.
			 */
			अगर (sgx_unmark_page_reclaimable(entry->epc_page))
				जारी;

			sgx_encl_मुक्त_epc_page(entry->epc_page);
			encl->secs_child_cnt--;
			entry->epc_page = शून्य;
		पूर्ण

		kमुक्त(entry);
	पूर्ण

	xa_destroy(&encl->page_array);

	अगर (!encl->secs_child_cnt && encl->secs.epc_page) अणु
		sgx_encl_मुक्त_epc_page(encl->secs.epc_page);
		encl->secs.epc_page = शून्य;
	पूर्ण

	जबतक (!list_empty(&encl->va_pages)) अणु
		va_page = list_first_entry(&encl->va_pages, काष्ठा sgx_va_page,
					   list);
		list_del(&va_page->list);
		sgx_encl_मुक्त_epc_page(va_page->epc_page);
		kमुक्त(va_page);
	पूर्ण

	अगर (encl->backing)
		fput(encl->backing);

	cleanup_srcu_काष्ठा(&encl->srcu);

	WARN_ON_ONCE(!list_empty(&encl->mm_list));

	/* Detect EPC page leak's. */
	WARN_ON_ONCE(encl->secs_child_cnt);
	WARN_ON_ONCE(encl->secs.epc_page);

	kमुक्त(encl);
पूर्ण

/*
 * 'mm' is निकासing and no दीर्घer needs mmu notअगरications.
 */
अटल व्योम sgx_mmu_notअगरier_release(काष्ठा mmu_notअगरier *mn,
				     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा sgx_encl_mm *encl_mm = container_of(mn, काष्ठा sgx_encl_mm, mmu_notअगरier);
	काष्ठा sgx_encl_mm *पंचांगp = शून्य;

	/*
	 * The enclave itself can हटाओ encl_mm.  Note, objects can't be moved
	 * off an RCU रक्षित list, but deletion is ok.
	 */
	spin_lock(&encl_mm->encl->mm_lock);
	list_क्रम_each_entry(पंचांगp, &encl_mm->encl->mm_list, list) अणु
		अगर (पंचांगp == encl_mm) अणु
			list_del_rcu(&encl_mm->list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&encl_mm->encl->mm_lock);

	अगर (पंचांगp == encl_mm) अणु
		synchronize_srcu(&encl_mm->encl->srcu);
		mmu_notअगरier_put(mn);
	पूर्ण
पूर्ण

अटल व्योम sgx_mmu_notअगरier_मुक्त(काष्ठा mmu_notअगरier *mn)
अणु
	काष्ठा sgx_encl_mm *encl_mm = container_of(mn, काष्ठा sgx_encl_mm, mmu_notअगरier);

	/* 'encl_mm' is going away, put encl_mm->encl reference: */
	kref_put(&encl_mm->encl->refcount, sgx_encl_release);

	kमुक्त(encl_mm);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops sgx_mmu_notअगरier_ops = अणु
	.release		= sgx_mmu_notअगरier_release,
	.मुक्त_notअगरier		= sgx_mmu_notअगरier_मुक्त,
पूर्ण;

अटल काष्ठा sgx_encl_mm *sgx_encl_find_mm(काष्ठा sgx_encl *encl,
					    काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा sgx_encl_mm *encl_mm = शून्य;
	काष्ठा sgx_encl_mm *पंचांगp;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&encl->srcu);

	list_क्रम_each_entry_rcu(पंचांगp, &encl->mm_list, list) अणु
		अगर (पंचांगp->mm == mm) अणु
			encl_mm = पंचांगp;
			अवरोध;
		पूर्ण
	पूर्ण

	srcu_पढ़ो_unlock(&encl->srcu, idx);

	वापस encl_mm;
पूर्ण

पूर्णांक sgx_encl_mm_add(काष्ठा sgx_encl *encl, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा sgx_encl_mm *encl_mm;
	पूर्णांक ret;

	/*
	 * Even though a single enclave may be mapped पूर्णांकo an mm more than once,
	 * each 'mm' only appears once on encl->mm_list. This is guaranteed by
	 * holding the mm's mmap lock क्रम ग_लिखो beक्रमe an mm can be added or
	 * हटाओ to an encl->mm_list.
	 */
	mmap_निश्चित_ग_लिखो_locked(mm);

	/*
	 * It's possible that an entry alपढ़ोy exists in the mm_list, because it
	 * is हटाओd only on VFS release or process निकास.
	 */
	अगर (sgx_encl_find_mm(encl, mm))
		वापस 0;

	encl_mm = kzalloc(माप(*encl_mm), GFP_KERNEL);
	अगर (!encl_mm)
		वापस -ENOMEM;

	/* Grab a refcount क्रम the encl_mm->encl reference: */
	kref_get(&encl->refcount);
	encl_mm->encl = encl;
	encl_mm->mm = mm;
	encl_mm->mmu_notअगरier.ops = &sgx_mmu_notअगरier_ops;

	ret = __mmu_notअगरier_रेजिस्टर(&encl_mm->mmu_notअगरier, mm);
	अगर (ret) अणु
		kमुक्त(encl_mm);
		वापस ret;
	पूर्ण

	spin_lock(&encl->mm_lock);
	list_add_rcu(&encl_mm->list, &encl->mm_list);
	/* Pairs with smp_rmb() in sgx_reclaimer_block(). */
	smp_wmb();
	encl->mm_list_version++;
	spin_unlock(&encl->mm_lock);

	वापस 0;
पूर्ण

अटल काष्ठा page *sgx_encl_get_backing_page(काष्ठा sgx_encl *encl,
					      pgoff_t index)
अणु
	काष्ठा inode *inode = encl->backing->f_path.dentry->d_inode;
	काष्ठा address_space *mapping = inode->i_mapping;
	gfp_t gfpmask = mapping_gfp_mask(mapping);

	वापस shmem_पढ़ो_mapping_page_gfp(mapping, index, gfpmask);
पूर्ण

/**
 * sgx_encl_get_backing() - Pin the backing storage
 * @encl:	an enclave poपूर्णांकer
 * @page_index:	enclave page index
 * @backing:	data क्रम accessing backing storage क्रम the page
 *
 * Pin the backing storage pages क्रम storing the encrypted contents and Paging
 * Crypto MetaData (PCMD) of an enclave page.
 *
 * Return:
 *   0 on success,
 *   -त्रुटि_सं otherwise.
 */
पूर्णांक sgx_encl_get_backing(काष्ठा sgx_encl *encl, अचिन्हित दीर्घ page_index,
			 काष्ठा sgx_backing *backing)
अणु
	pgoff_t pcmd_index = PFN_DOWN(encl->size) + 1 + (page_index >> 5);
	काष्ठा page *contents;
	काष्ठा page *pcmd;

	contents = sgx_encl_get_backing_page(encl, page_index);
	अगर (IS_ERR(contents))
		वापस PTR_ERR(contents);

	pcmd = sgx_encl_get_backing_page(encl, pcmd_index);
	अगर (IS_ERR(pcmd)) अणु
		put_page(contents);
		वापस PTR_ERR(pcmd);
	पूर्ण

	backing->page_index = page_index;
	backing->contents = contents;
	backing->pcmd = pcmd;
	backing->pcmd_offset =
		(page_index & (PAGE_SIZE / माप(काष्ठा sgx_pcmd) - 1)) *
		माप(काष्ठा sgx_pcmd);

	वापस 0;
पूर्ण

/**
 * sgx_encl_put_backing() - Unpin the backing storage
 * @backing:	data क्रम accessing backing storage क्रम the page
 * @करो_ग_लिखो:	mark pages dirty
 */
व्योम sgx_encl_put_backing(काष्ठा sgx_backing *backing, bool करो_ग_लिखो)
अणु
	अगर (करो_ग_लिखो) अणु
		set_page_dirty(backing->pcmd);
		set_page_dirty(backing->contents);
	पूर्ण

	put_page(backing->pcmd);
	put_page(backing->contents);
पूर्ण

अटल पूर्णांक sgx_encl_test_and_clear_young_cb(pte_t *ptep, अचिन्हित दीर्घ addr,
					    व्योम *data)
अणु
	pte_t pte;
	पूर्णांक ret;

	ret = pte_young(*ptep);
	अगर (ret) अणु
		pte = pte_mkold(*ptep);
		set_pte_at((काष्ठा mm_काष्ठा *)data, addr, ptep, pte);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sgx_encl_test_and_clear_young() - Test and reset the accessed bit
 * @mm:		mm_काष्ठा that is checked
 * @page:	enclave page to be tested क्रम recent access
 *
 * Checks the Access (A) bit from the PTE corresponding to the enclave page and
 * clears it.
 *
 * Return: 1 अगर the page has been recently accessed and 0 अगर not.
 */
पूर्णांक sgx_encl_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
				  काष्ठा sgx_encl_page *page)
अणु
	अचिन्हित दीर्घ addr = page->desc & PAGE_MASK;
	काष्ठा sgx_encl *encl = page->encl;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret;

	ret = sgx_encl_find(mm, addr, &vma);
	अगर (ret)
		वापस 0;

	अगर (encl != vma->vm_निजी_data)
		वापस 0;

	ret = apply_to_page_range(vma->vm_mm, addr, PAGE_SIZE,
				  sgx_encl_test_and_clear_young_cb, vma->vm_mm);
	अगर (ret < 0)
		वापस 0;

	वापस ret;
पूर्ण

/**
 * sgx_alloc_va_page() - Allocate a Version Array (VA) page
 *
 * Allocate a मुक्त EPC page and convert it to a Version Array (VA) page.
 *
 * Return:
 *   a VA page,
 *   -त्रुटि_सं otherwise
 */
काष्ठा sgx_epc_page *sgx_alloc_va_page(व्योम)
अणु
	काष्ठा sgx_epc_page *epc_page;
	पूर्णांक ret;

	epc_page = sgx_alloc_epc_page(शून्य, true);
	अगर (IS_ERR(epc_page))
		वापस ERR_CAST(epc_page);

	ret = __epa(sgx_get_epc_virt_addr(epc_page));
	अगर (ret) अणु
		WARN_ONCE(1, "EPA returned %d (0x%x)", ret, ret);
		sgx_encl_मुक्त_epc_page(epc_page);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस epc_page;
पूर्ण

/**
 * sgx_alloc_va_slot - allocate a VA slot
 * @va_page:	a &काष्ठा sgx_va_page instance
 *
 * Allocates a slot from a &काष्ठा sgx_va_page instance.
 *
 * Return: offset of the slot inside the VA page
 */
अचिन्हित पूर्णांक sgx_alloc_va_slot(काष्ठा sgx_va_page *va_page)
अणु
	पूर्णांक slot = find_first_zero_bit(va_page->slots, SGX_VA_SLOT_COUNT);

	अगर (slot < SGX_VA_SLOT_COUNT)
		set_bit(slot, va_page->slots);

	वापस slot << 3;
पूर्ण

/**
 * sgx_मुक्त_va_slot - मुक्त a VA slot
 * @va_page:	a &काष्ठा sgx_va_page instance
 * @offset:	offset of the slot inside the VA page
 *
 * Frees a slot from a &काष्ठा sgx_va_page instance.
 */
व्योम sgx_मुक्त_va_slot(काष्ठा sgx_va_page *va_page, अचिन्हित पूर्णांक offset)
अणु
	clear_bit(offset >> 3, va_page->slots);
पूर्ण

/**
 * sgx_va_page_full - is the VA page full?
 * @va_page:	a &काष्ठा sgx_va_page instance
 *
 * Return: true अगर all slots have been taken
 */
bool sgx_va_page_full(काष्ठा sgx_va_page *va_page)
अणु
	पूर्णांक slot = find_first_zero_bit(va_page->slots, SGX_VA_SLOT_COUNT);

	वापस slot == SGX_VA_SLOT_COUNT;
पूर्ण

/**
 * sgx_encl_मुक्त_epc_page - मुक्त an EPC page asचिन्हित to an enclave
 * @page:	EPC page to be मुक्तd
 *
 * Free an EPC page asचिन्हित to an enclave. It करोes EREMOVE क्रम the page, and
 * only upon success, it माला_दो the page back to मुक्त page list.  Otherwise, it
 * gives a WARNING to indicate page is leaked.
 */
व्योम sgx_encl_मुक्त_epc_page(काष्ठा sgx_epc_page *page)
अणु
	पूर्णांक ret;

	WARN_ON_ONCE(page->flags & SGX_EPC_PAGE_RECLAIMER_TRACKED);

	ret = __eहटाओ(sgx_get_epc_virt_addr(page));
	अगर (WARN_ONCE(ret, EREMOVE_ERROR_MESSAGE, ret, ret))
		वापस;

	sgx_मुक्त_epc_page(page);
पूर्ण

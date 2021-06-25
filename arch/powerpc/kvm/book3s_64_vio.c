<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2010 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 * Copyright 2011 David Gibson, IBM Corporation <dwg@au1.ibm.com>
 * Copyright 2016 Alexey Kardashevskiy, IBM Corporation <aik@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/list.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/iommu.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/mmu_context.h>

अटल अचिन्हित दीर्घ kvmppc_tce_pages(अचिन्हित दीर्घ iommu_pages)
अणु
	वापस ALIGN(iommu_pages * माप(u64), PAGE_SIZE) / PAGE_SIZE;
पूर्ण

अटल अचिन्हित दीर्घ kvmppc_stt_pages(अचिन्हित दीर्घ tce_pages)
अणु
	अचिन्हित दीर्घ stt_bytes = माप(काष्ठा kvmppc_spapr_tce_table) +
			(tce_pages * माप(काष्ठा page *));

	वापस tce_pages + ALIGN(stt_bytes, PAGE_SIZE) / PAGE_SIZE;
पूर्ण

अटल व्योम kvm_spapr_tce_iommu_table_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा kvmppc_spapr_tce_iommu_table *stit = container_of(head,
			काष्ठा kvmppc_spapr_tce_iommu_table, rcu);

	iommu_tce_table_put(stit->tbl);

	kमुक्त(stit);
पूर्ण

अटल व्योम kvm_spapr_tce_liobn_put(काष्ठा kref *kref)
अणु
	काष्ठा kvmppc_spapr_tce_iommu_table *stit = container_of(kref,
			काष्ठा kvmppc_spapr_tce_iommu_table, kref);

	list_del_rcu(&stit->next);

	call_rcu(&stit->rcu, kvm_spapr_tce_iommu_table_मुक्त);
पूर्ण

बाह्य व्योम kvm_spapr_tce_release_iommu_group(काष्ठा kvm *kvm,
		काष्ठा iommu_group *grp)
अणु
	पूर्णांक i;
	काष्ठा kvmppc_spapr_tce_table *stt;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit, *पंचांगp;
	काष्ठा iommu_table_group *table_group = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(stt, &kvm->arch.spapr_tce_tables, list) अणु

		table_group = iommu_group_get_iommudata(grp);
		अगर (WARN_ON(!table_group))
			जारी;

		list_क्रम_each_entry_safe(stit, पंचांगp, &stt->iommu_tables, next) अणु
			क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
				अगर (table_group->tables[i] != stit->tbl)
					जारी;

				kref_put(&stit->kref, kvm_spapr_tce_liobn_put);
			पूर्ण
		पूर्ण
		cond_resched_rcu();
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

बाह्य दीर्घ kvm_spapr_tce_attach_iommu_group(काष्ठा kvm *kvm, पूर्णांक tablefd,
		काष्ठा iommu_group *grp)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt = शून्य;
	bool found = false;
	काष्ठा iommu_table *tbl = शून्य;
	काष्ठा iommu_table_group *table_group;
	दीर्घ i;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;
	काष्ठा fd f;

	f = fdget(tablefd);
	अगर (!f.file)
		वापस -EBADF;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(stt, &kvm->arch.spapr_tce_tables, list) अणु
		अगर (stt == f.file->निजी_data) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	fdput(f);

	अगर (!found)
		वापस -EINVAL;

	table_group = iommu_group_get_iommudata(grp);
	अगर (WARN_ON(!table_group))
		वापस -EFAULT;

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tblपंचांगp = table_group->tables[i];

		अगर (!tblपंचांगp)
			जारी;
		/* Make sure hardware table parameters are compatible */
		अगर ((tblपंचांगp->it_page_shअगरt <= stt->page_shअगरt) &&
				(tblपंचांगp->it_offset << tblपंचांगp->it_page_shअगरt ==
				 stt->offset << stt->page_shअगरt) &&
				(tblपंचांगp->it_size << tblपंचांगp->it_page_shअगरt >=
				 stt->size << stt->page_shअगरt)) अणु
			/*
			 * Reference the table to aव्योम races with
			 * add/हटाओ DMA winकरोws.
			 */
			tbl = iommu_tce_table_get(tblपंचांगp);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!tbl)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(stit, &stt->iommu_tables, next) अणु
		अगर (tbl != stit->tbl)
			जारी;

		अगर (!kref_get_unless_zero(&stit->kref)) अणु
			/* stit is being destroyed */
			iommu_tce_table_put(tbl);
			rcu_पढ़ो_unlock();
			वापस -ENOTTY;
		पूर्ण
		/*
		 * The table is alपढ़ोy known to this KVM, we just increased
		 * its KVM reference counter and can वापस.
		 */
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	stit = kzalloc(माप(*stit), GFP_KERNEL);
	अगर (!stit) अणु
		iommu_tce_table_put(tbl);
		वापस -ENOMEM;
	पूर्ण

	stit->tbl = tbl;
	kref_init(&stit->kref);

	list_add_rcu(&stit->next, &stt->iommu_tables);

	वापस 0;
पूर्ण

अटल व्योम release_spapr_tce_table(काष्ठा rcu_head *head)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt = container_of(head,
			काष्ठा kvmppc_spapr_tce_table, rcu);
	अचिन्हित दीर्घ i, npages = kvmppc_tce_pages(stt->size);

	क्रम (i = 0; i < npages; i++)
		अगर (stt->pages[i])
			__मुक्त_page(stt->pages[i]);

	kमुक्त(stt);
पूर्ण

अटल काष्ठा page *kvm_spapr_get_tce_page(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ sttpage)
अणु
	काष्ठा page *page = stt->pages[sttpage];

	अगर (page)
		वापस page;

	mutex_lock(&stt->alloc_lock);
	page = stt->pages[sttpage];
	अगर (!page) अणु
		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		WARN_ON_ONCE(!page);
		अगर (page)
			stt->pages[sttpage] = page;
	पूर्ण
	mutex_unlock(&stt->alloc_lock);

	वापस page;
पूर्ण

अटल vm_fault_t kvm_spapr_tce_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt = vmf->vma->vm_file->निजी_data;
	काष्ठा page *page;

	अगर (vmf->pgoff >= kvmppc_tce_pages(stt->size))
		वापस VM_FAULT_SIGBUS;

	page = kvm_spapr_get_tce_page(stt, vmf->pgoff);
	अगर (!page)
		वापस VM_FAULT_OOM;

	get_page(page);
	vmf->page = page;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा kvm_spapr_tce_vm_ops = अणु
	.fault = kvm_spapr_tce_fault,
पूर्ण;

अटल पूर्णांक kvm_spapr_tce_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_ops = &kvm_spapr_tce_vm_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक kvm_spapr_tce_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt = filp->निजी_data;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit, *पंचांगp;
	काष्ठा kvm *kvm = stt->kvm;

	mutex_lock(&kvm->lock);
	list_del_rcu(&stt->list);
	mutex_unlock(&kvm->lock);

	list_क्रम_each_entry_safe(stit, पंचांगp, &stt->iommu_tables, next) अणु
		WARN_ON(!kref_पढ़ो(&stit->kref));
		जबतक (1) अणु
			अगर (kref_put(&stit->kref, kvm_spapr_tce_liobn_put))
				अवरोध;
		पूर्ण
	पूर्ण

	account_locked_vm(kvm->mm,
		kvmppc_stt_pages(kvmppc_tce_pages(stt->size)), false);

	kvm_put_kvm(stt->kvm);

	call_rcu(&stt->rcu, release_spapr_tce_table);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations kvm_spapr_tce_fops = अणु
	.mmap           = kvm_spapr_tce_mmap,
	.release	= kvm_spapr_tce_release,
पूर्ण;

दीर्घ kvm_vm_ioctl_create_spapr_tce(काष्ठा kvm *kvm,
				   काष्ठा kvm_create_spapr_tce_64 *args)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt = शून्य;
	काष्ठा kvmppc_spapr_tce_table *siter;
	काष्ठा mm_काष्ठा *mm = kvm->mm;
	अचिन्हित दीर्घ npages, size = args->size;
	पूर्णांक ret;

	अगर (!args->size || args->page_shअगरt < 12 || args->page_shअगरt > 34 ||
		(args->offset + args->size > (ULदीर्घ_उच्च >> args->page_shअगरt)))
		वापस -EINVAL;

	npages = kvmppc_tce_pages(size);
	ret = account_locked_vm(mm, kvmppc_stt_pages(npages), true);
	अगर (ret)
		वापस ret;

	ret = -ENOMEM;
	stt = kzalloc(माप(*stt) + npages * माप(काष्ठा page *),
		      GFP_KERNEL);
	अगर (!stt)
		जाओ fail_acct;

	stt->liobn = args->liobn;
	stt->page_shअगरt = args->page_shअगरt;
	stt->offset = args->offset;
	stt->size = size;
	stt->kvm = kvm;
	mutex_init(&stt->alloc_lock);
	INIT_LIST_HEAD_RCU(&stt->iommu_tables);

	mutex_lock(&kvm->lock);

	/* Check this LIOBN hasn't been previously allocated */
	ret = 0;
	list_क्रम_each_entry(siter, &kvm->arch.spapr_tce_tables, list) अणु
		अगर (siter->liobn == args->liobn) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	kvm_get_kvm(kvm);
	अगर (!ret)
		ret = anon_inode_getfd("kvm-spapr-tce", &kvm_spapr_tce_fops,
				       stt, O_RDWR | O_CLOEXEC);

	अगर (ret >= 0)
		list_add_rcu(&stt->list, &kvm->arch.spapr_tce_tables);
	अन्यथा
		kvm_put_kvm_no_destroy(kvm);

	mutex_unlock(&kvm->lock);

	अगर (ret >= 0)
		वापस ret;

	kमुक्त(stt);
 fail_acct:
	account_locked_vm(mm, kvmppc_stt_pages(npages), false);
	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_tce_to_ua(काष्ठा kvm *kvm, अचिन्हित दीर्घ tce,
		अचिन्हित दीर्घ *ua)
अणु
	अचिन्हित दीर्घ gfn = tce >> PAGE_SHIFT;
	काष्ठा kvm_memory_slot *memslot;

	memslot = search_memslots(kvm_memslots(kvm), gfn);
	अगर (!memslot)
		वापस -EINVAL;

	*ua = __gfn_to_hva_memslot(memslot, gfn) |
		(tce & ~(PAGE_MASK | TCE_PCI_READ | TCE_PCI_WRITE));

	वापस 0;
पूर्ण

अटल दीर्घ kvmppc_tce_validate(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ tce)
अणु
	अचिन्हित दीर्घ gpa = tce & ~(TCE_PCI_READ | TCE_PCI_WRITE);
	क्रमागत dma_data_direction dir = iommu_tce_direction(tce);
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;
	अचिन्हित दीर्घ ua = 0;

	/* Allow userspace to poison TCE table */
	अगर (dir == DMA_NONE)
		वापस H_SUCCESS;

	अगर (iommu_tce_check_gpa(stt->page_shअगरt, gpa))
		वापस H_TOO_HARD;

	अगर (kvmppc_tce_to_ua(stt->kvm, tce, &ua))
		वापस H_TOO_HARD;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(stit, &stt->iommu_tables, next) अणु
		अचिन्हित दीर्घ hpa = 0;
		काष्ठा mm_iommu_table_group_mem_t *mem;
		दीर्घ shअगरt = stit->tbl->it_page_shअगरt;

		mem = mm_iommu_lookup(stt->kvm->mm, ua, 1ULL << shअगरt);
		अगर (!mem || mm_iommu_ua_to_hpa(mem, ua, shअगरt, &hpa)) अणु
			rcu_पढ़ो_unlock();
			वापस H_TOO_HARD;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस H_SUCCESS;
पूर्ण

/*
 * Handles TCE requests क्रम emulated devices.
 * Puts guest TCE values to the table and expects user space to convert them.
 * Cannot fail so kvmppc_tce_validate must be called beक्रमe it.
 */
अटल व्योम kvmppc_tce_put(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ idx, अचिन्हित दीर्घ tce)
अणु
	काष्ठा page *page;
	u64 *tbl;
	अचिन्हित दीर्घ sttpage;

	idx -= stt->offset;
	sttpage = idx / TCES_PER_PAGE;
	page = stt->pages[sttpage];

	अगर (!page) अणु
		/* We allow any TCE, not just with पढ़ो|ग_लिखो permissions */
		अगर (!tce)
			वापस;

		page = kvm_spapr_get_tce_page(stt, sttpage);
		अगर (!page)
			वापस;
	पूर्ण
	tbl = page_to_virt(page);

	tbl[idx % TCES_PER_PAGE] = tce;
पूर्ण

अटल व्योम kvmppc_clear_tce(काष्ठा mm_काष्ठा *mm, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry)
अणु
	अचिन्हित दीर्घ hpa = 0;
	क्रमागत dma_data_direction dir = DMA_NONE;

	iommu_tce_xchg_no_समाप्त(mm, tbl, entry, &hpa, &dir);
पूर्ण

अटल दीर्घ kvmppc_tce_iommu_mapped_dec(काष्ठा kvm *kvm,
		काष्ठा iommu_table *tbl, अचिन्हित दीर्घ entry)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem = शून्य;
	स्थिर अचिन्हित दीर्घ pgsize = 1ULL << tbl->it_page_shअगरt;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry);

	अगर (!pua)
		वापस H_SUCCESS;

	mem = mm_iommu_lookup(kvm->mm, be64_to_cpu(*pua), pgsize);
	अगर (!mem)
		वापस H_TOO_HARD;

	mm_iommu_mapped_dec(mem);

	*pua = cpu_to_be64(0);

	वापस H_SUCCESS;
पूर्ण

अटल दीर्घ kvmppc_tce_iommu_करो_unmap(काष्ठा kvm *kvm,
		काष्ठा iommu_table *tbl, अचिन्हित दीर्घ entry)
अणु
	क्रमागत dma_data_direction dir = DMA_NONE;
	अचिन्हित दीर्घ hpa = 0;
	दीर्घ ret;

	अगर (WARN_ON_ONCE(iommu_tce_xchg_no_समाप्त(kvm->mm, tbl, entry, &hpa,
					&dir)))
		वापस H_TOO_HARD;

	अगर (dir == DMA_NONE)
		वापस H_SUCCESS;

	ret = kvmppc_tce_iommu_mapped_dec(kvm, tbl, entry);
	अगर (ret != H_SUCCESS)
		iommu_tce_xchg_no_समाप्त(kvm->mm, tbl, entry, &hpa, &dir);

	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_tce_iommu_unmap(काष्ठा kvm *kvm,
		काष्ठा kvmppc_spapr_tce_table *stt, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry)
अणु
	अचिन्हित दीर्घ i, ret = H_SUCCESS;
	अचिन्हित दीर्घ subpages = 1ULL << (stt->page_shअगरt - tbl->it_page_shअगरt);
	अचिन्हित दीर्घ io_entry = entry * subpages;

	क्रम (i = 0; i < subpages; ++i) अणु
		ret = kvmppc_tce_iommu_करो_unmap(kvm, tbl, io_entry + i);
		अगर (ret != H_SUCCESS)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_tce_iommu_करो_map(काष्ठा kvm *kvm, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ ua,
		क्रमागत dma_data_direction dir)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ hpa;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY(tbl, entry);
	काष्ठा mm_iommu_table_group_mem_t *mem;

	अगर (!pua)
		/* it_userspace allocation might be delayed */
		वापस H_TOO_HARD;

	mem = mm_iommu_lookup(kvm->mm, ua, 1ULL << tbl->it_page_shअगरt);
	अगर (!mem)
		/* This only handles v2 IOMMU type, v1 is handled via ioctl() */
		वापस H_TOO_HARD;

	अगर (WARN_ON_ONCE(mm_iommu_ua_to_hpa(mem, ua, tbl->it_page_shअगरt, &hpa)))
		वापस H_TOO_HARD;

	अगर (mm_iommu_mapped_inc(mem))
		वापस H_TOO_HARD;

	ret = iommu_tce_xchg_no_समाप्त(kvm->mm, tbl, entry, &hpa, &dir);
	अगर (WARN_ON_ONCE(ret)) अणु
		mm_iommu_mapped_dec(mem);
		वापस H_TOO_HARD;
	पूर्ण

	अगर (dir != DMA_NONE)
		kvmppc_tce_iommu_mapped_dec(kvm, tbl, entry);

	*pua = cpu_to_be64(ua);

	वापस 0;
पूर्ण

अटल दीर्घ kvmppc_tce_iommu_map(काष्ठा kvm *kvm,
		काष्ठा kvmppc_spapr_tce_table *stt, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ ua,
		क्रमागत dma_data_direction dir)
अणु
	अचिन्हित दीर्घ i, pgoff, ret = H_SUCCESS;
	अचिन्हित दीर्घ subpages = 1ULL << (stt->page_shअगरt - tbl->it_page_shअगरt);
	अचिन्हित दीर्घ io_entry = entry * subpages;

	क्रम (i = 0, pgoff = 0; i < subpages;
			++i, pgoff += IOMMU_PAGE_SIZE(tbl)) अणु

		ret = kvmppc_tce_iommu_करो_map(kvm, tbl,
				io_entry + i, ua + pgoff, dir);
		अगर (ret != H_SUCCESS)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

दीर्घ kvmppc_h_put_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
		      अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ tce)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ ret, idx;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;
	अचिन्हित दीर्घ entry, ua = 0;
	क्रमागत dma_data_direction dir;

	/* udbg_म_लिखो("H_PUT_TCE(): liobn=0x%lx ioba=0x%lx, tce=0x%lx\n", */
	/* 	    liobn, ioba, tce); */

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	ret = kvmppc_ioba_validate(stt, ioba, 1);
	अगर (ret != H_SUCCESS)
		वापस ret;

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	ret = kvmppc_tce_validate(stt, tce);
	अगर (ret != H_SUCCESS)
		जाओ unlock_निकास;

	dir = iommu_tce_direction(tce);

	अगर ((dir != DMA_NONE) && kvmppc_tce_to_ua(vcpu->kvm, tce, &ua)) अणु
		ret = H_PARAMETER;
		जाओ unlock_निकास;
	पूर्ण

	entry = ioba >> stt->page_shअगरt;

	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
		अगर (dir == DMA_NONE)
			ret = kvmppc_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbl, entry);
		अन्यथा
			ret = kvmppc_tce_iommu_map(vcpu->kvm, stt, stit->tbl,
					entry, ua, dir);

		iommu_tce_समाप्त(stit->tbl, entry, 1);

		अगर (ret != H_SUCCESS) अणु
			kvmppc_clear_tce(vcpu->kvm->mm, stit->tbl, entry);
			जाओ unlock_निकास;
		पूर्ण
	पूर्ण

	kvmppc_tce_put(stt, entry, tce);

unlock_निकास:
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_put_tce);

दीर्घ kvmppc_h_put_tce_indirect(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_list, अचिन्हित दीर्घ npages)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ i, ret = H_SUCCESS, idx;
	अचिन्हित दीर्घ entry, ua = 0;
	u64 __user *tces;
	u64 tce;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	entry = ioba >> stt->page_shअगरt;
	/*
	 * SPAPR spec says that the maximum size of the list is 512 TCEs
	 * so the whole table fits in 4K page
	 */
	अगर (npages > 512)
		वापस H_PARAMETER;

	अगर (tce_list & (SZ_4K - 1))
		वापस H_PARAMETER;

	ret = kvmppc_ioba_validate(stt, ioba, npages);
	अगर (ret != H_SUCCESS)
		वापस ret;

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	अगर (kvmppc_tce_to_ua(vcpu->kvm, tce_list, &ua)) अणु
		ret = H_TOO_HARD;
		जाओ unlock_निकास;
	पूर्ण
	tces = (u64 __user *) ua;

	क्रम (i = 0; i < npages; ++i) अणु
		अगर (get_user(tce, tces + i)) अणु
			ret = H_TOO_HARD;
			जाओ unlock_निकास;
		पूर्ण
		tce = be64_to_cpu(tce);

		ret = kvmppc_tce_validate(stt, tce);
		अगर (ret != H_SUCCESS)
			जाओ unlock_निकास;
	पूर्ण

	क्रम (i = 0; i < npages; ++i) अणु
		/*
		 * This looks unsafe, because we validate, then regrab
		 * the TCE from userspace which could have been changed by
		 * another thपढ़ो.
		 *
		 * But it actually is safe, because the relevant checks will be
		 * re-executed in the following code.  If userspace tries to
		 * change this करोdgily it will result in a messier failure mode
		 * but won't threaten the host.
		 */
		अगर (get_user(tce, tces + i)) अणु
			ret = H_TOO_HARD;
			जाओ invalidate_निकास;
		पूर्ण
		tce = be64_to_cpu(tce);

		अगर (kvmppc_tce_to_ua(vcpu->kvm, tce, &ua)) अणु
			ret = H_PARAMETER;
			जाओ invalidate_निकास;
		पूर्ण

		list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
			ret = kvmppc_tce_iommu_map(vcpu->kvm, stt,
					stit->tbl, entry + i, ua,
					iommu_tce_direction(tce));

			अगर (ret != H_SUCCESS) अणु
				kvmppc_clear_tce(vcpu->kvm->mm, stit->tbl,
						entry);
				जाओ invalidate_निकास;
			पूर्ण
		पूर्ण

		kvmppc_tce_put(stt, entry + i, tce);
	पूर्ण

invalidate_निकास:
	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next)
		iommu_tce_समाप्त(stit->tbl, entry, npages);

unlock_निकास:
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_put_tce_indirect);

दीर्घ kvmppc_h_stuff_tce(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_value, अचिन्हित दीर्घ npages)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ i, ret;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	ret = kvmppc_ioba_validate(stt, ioba, npages);
	अगर (ret != H_SUCCESS)
		वापस ret;

	/* Check permission bits only to allow userspace poison TCE क्रम debug */
	अगर (tce_value & (TCE_PCI_WRITE | TCE_PCI_READ))
		वापस H_PARAMETER;

	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
		अचिन्हित दीर्घ entry = ioba >> stt->page_shअगरt;

		क्रम (i = 0; i < npages; ++i) अणु
			ret = kvmppc_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbl, entry + i);

			अगर (ret == H_SUCCESS)
				जारी;

			अगर (ret == H_TOO_HARD)
				जाओ invalidate_निकास;

			WARN_ON_ONCE(1);
			kvmppc_clear_tce(vcpu->kvm->mm, stit->tbl, entry);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < npages; ++i, ioba += (1ULL << stt->page_shअगरt))
		kvmppc_tce_put(stt, ioba >> stt->page_shअगरt, tce_value);

invalidate_निकास:
	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next)
		iommu_tce_समाप्त(stit->tbl, ioba >> stt->page_shअगरt, npages);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_stuff_tce);

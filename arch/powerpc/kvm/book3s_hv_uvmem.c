<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Secure pages management: Migration of pages between normal and secure
 * memory of KVM guests.
 *
 * Copyright 2018 Bharata B Rao, IBM Corp. <bharata@linux.ibm.com>
 */

/*
 * A pseries guest can be run as secure guest on Ultravisor-enabled
 * POWER platक्रमms. On such platक्रमms, this driver will be used to manage
 * the movement of guest pages between the normal memory managed by
 * hypervisor (HV) and secure memory managed by Ultravisor (UV).
 *
 * The page-in or page-out requests from UV will come to HV as hcalls and
 * HV will call back पूर्णांकo UV via ultracalls to satisfy these page requests.
 *
 * Private ZONE_DEVICE memory equal to the amount of secure memory
 * available in the platक्रमm क्रम running secure guests is hotplugged.
 * Whenever a page beदीर्घing to the guest becomes secure, a page from this
 * निजी device memory is used to represent and track that secure page
 * on the HV side. Some pages (like virtio buffers, VPA pages etc) are
 * shared between UV and HV. However such pages aren't represented by
 * device निजी memory and mappings to shared memory exist in both
 * UV and HV page tables.
 */

/*
 * Notes on locking
 *
 * kvm->arch.uvmem_lock is a per-guest lock that prevents concurrent
 * page-in and page-out requests क्रम the same GPA. Concurrent accesses
 * can either come via UV (guest vCPUs requesting क्रम same page)
 * or when HV and guest simultaneously access the same page.
 * This mutex serializes the migration of page from HV(normal) to
 * UV(secure) and vice versa. So the serialization poपूर्णांकs are around
 * migrate_vma routines and page-in/out routines.
 *
 * Per-guest mutex comes with a cost though. Mainly it serializes the
 * fault path as page-out can occur when HV faults on accessing secure
 * guest pages. Currently UV issues page-in requests क्रम all the guest
 * PFNs one at a समय during early boot (UV_ESM uvcall), so this is
 * not a cause क्रम concern. Also currently the number of page-outs caused
 * by HV touching secure pages is very very low. If an when UV supports
 * overcommitting, then we might see concurrent guest driven page-outs.
 *
 * Locking order
 *
 * 1. kvm->srcu - Protects KVM memslots
 * 2. kvm->mm->mmap_lock - find_vma, migrate_vma_pages and helpers, ksm_madvise
 * 3. kvm->arch.uvmem_lock - protects पढ़ो/ग_लिखोs to uvmem slots thus acting
 *			     as sync-poपूर्णांकs क्रम page-in/out
 */

/*
 * Notes on page size
 *
 * Currently UV uses 2MB mappings पूर्णांकernally, but will issue H_SVM_PAGE_IN
 * and H_SVM_PAGE_OUT hcalls in PAGE_SIZE(64K) granularity. HV tracks
 * secure GPAs at 64K page size and मुख्यtains one device PFN क्रम each
 * 64K secure GPA. UV_PAGE_IN and UV_PAGE_OUT calls by HV are also issued
 * क्रम 64K page at a समय.
 *
 * HV faulting on secure pages: When HV touches any secure page, it
 * faults and issues a UV_PAGE_OUT request with 64K page size. Currently
 * UV splits and remaps the 2MB page अगर necessary and copies out the
 * required 64K page contents.
 *
 * Shared pages: Whenever guest shares a secure page, UV will split and
 * remap the 2MB page अगर required and issue H_SVM_PAGE_IN with 64K page size.
 *
 * HV invalidating a page: When a regular page beदीर्घing to secure
 * guest माला_लो unmapped, HV inक्रमms UV with UV_PAGE_INVAL of 64K
 * page size. Using 64K page size is correct here because any non-secure
 * page will essentially be of 64K page size. Splitting by UV during sharing
 * and page-out ensures this.
 *
 * Page fault handling: When HV handles page fault of a page beदीर्घing
 * to secure guest, it sends that to UV with a 64K UV_PAGE_IN request.
 * Using 64K size is correct here too as UV would have split the 2MB page
 * पूर्णांकo 64k mappings and would have करोne page-outs earlier.
 *
 * In summary, the current secure pages handling code in HV assumes
 * 64K page size and in fact fails any page-in/page-out requests of
 * non-64K size upfront. If and when UV starts supporting multiple
 * page-sizes, we need to अवरोध this assumption.
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/migrate.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/ksm.h>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s_uvस्मृति.स>

अटल काष्ठा dev_pagemap kvmppc_uvmem_pgmap;
अटल अचिन्हित दीर्घ *kvmppc_uvmem_biपंचांगap;
अटल DEFINE_SPINLOCK(kvmppc_uvmem_biपंचांगap_lock);

/*
 * States of a GFN
 * ---------------
 * The GFN can be in one of the following states.
 *
 * (a) Secure - The GFN is secure. The GFN is associated with
 *	a Secure VM, the contents of the GFN is not accessible
 *	to the Hypervisor.  This GFN can be backed by a secure-PFN,
 *	or can be backed by a normal-PFN with contents encrypted.
 *	The क्रमmer is true when the GFN is paged-in पूर्णांकo the
 *	ultravisor. The latter is true when the GFN is paged-out
 *	of the ultravisor.
 *
 * (b) Shared - The GFN is shared. The GFN is associated with a
 *	a secure VM. The contents of the GFN is accessible to
 *	Hypervisor. This GFN is backed by a normal-PFN and its
 *	content is un-encrypted.
 *
 * (c) Normal - The GFN is a normal. The GFN is associated with
 *	a normal VM. The contents of the GFN is accesible to
 *	the Hypervisor. Its content is never encrypted.
 *
 * States of a VM.
 * ---------------
 *
 * Normal VM:  A VM whose contents are always accessible to
 *	the hypervisor.  All its GFNs are normal-GFNs.
 *
 * Secure VM: A VM whose contents are not accessible to the
 *	hypervisor without the VM's consent.  Its GFNs are
 *	either Shared-GFN or Secure-GFNs.
 *
 * Transient VM: A Normal VM that is transitioning to secure VM.
 *	The transition starts on successful वापस of
 *	H_SVM_INIT_START, and ends on successful वापस
 *	of H_SVM_INIT_DONE. This transient VM, can have GFNs
 *	in any of the three states; i.e Secure-GFN, Shared-GFN,
 *	and Normal-GFN.	The VM never executes in this state
 *	in supervisor-mode.
 *
 * Memory slot State.
 * -----------------------------
 *	The state of a memory slot mirrors the state of the
 *	VM the memory slot is associated with.
 *
 * VM State transition.
 * --------------------
 *
 *  A VM always starts in Normal Mode.
 *
 *  H_SVM_INIT_START moves the VM पूर्णांकo transient state. During this
 *  समय the Ultravisor may request some of its GFNs to be shared or
 *  secured. So its GFNs can be in one of the three GFN states.
 *
 *  H_SVM_INIT_DONE moves the VM entirely from transient state to
 *  secure-state. At this poपूर्णांक any left-over normal-GFNs are
 *  transitioned to Secure-GFN.
 *
 *  H_SVM_INIT_ABORT moves the transient VM back to normal VM.
 *  All its GFNs are moved to Normal-GFNs.
 *
 *  UV_TERMINATE transitions the secure-VM back to normal-VM. All
 *  the secure-GFN and shared-GFNs are tranistioned to normal-GFN
 *  Note: The contents of the normal-GFN is undefined at this poपूर्णांक.
 *
 * GFN state implementation:
 * -------------------------
 *
 * Secure GFN is associated with a secure-PFN; also called uvmem_pfn,
 * when the GFN is paged-in. Its pfn[] has KVMPPC_GFN_UVMEM_PFN flag
 * set, and contains the value of the secure-PFN.
 * It is associated with a normal-PFN; also called mem_pfn, when
 * the GFN is pageकरोut. Its pfn[] has KVMPPC_GFN_MEM_PFN flag set.
 * The value of the normal-PFN is not tracked.
 *
 * Shared GFN is associated with a normal-PFN. Its pfn[] has
 * KVMPPC_UVMEM_SHARED_PFN flag set. The value of the normal-PFN
 * is not tracked.
 *
 * Normal GFN is associated with normal-PFN. Its pfn[] has
 * no flag set. The value of the normal-PFN is not tracked.
 *
 * Lअगरe cycle of a GFN
 * --------------------
 *
 * --------------------------------------------------------------
 * |        |     Share  |  Unshare | SVM       |H_SVM_INIT_DONE|
 * |        |operation   |operation | पात/    |               |
 * |        |            |          | terminate |               |
 * -------------------------------------------------------------
 * |        |            |          |           |               |
 * | Secure |     Shared | Secure   |Normal     |Secure         |
 * |        |            |          |           |               |
 * | Shared |     Shared | Secure   |Normal     |Shared         |
 * |        |            |          |           |               |
 * | Normal |     Shared | Secure   |Normal     |Secure         |
 * --------------------------------------------------------------
 *
 * Lअगरe cycle of a VM
 * --------------------
 *
 * --------------------------------------------------------------------
 * |         |  start    |  H_SVM_  |H_SVM_   |H_SVM_     |UV_SVM_    |
 * |         |  VM       |INIT_START|INIT_DONE|INIT_ABORT |TERMINATE  |
 * |         |           |          |         |           |           |
 * --------- ----------------------------------------------------------
 * |         |           |          |         |           |           |
 * | Normal  | Normal    | Transient|Error    |Error      |Normal     |
 * |         |           |          |         |           |           |
 * | Secure  |   Error   | Error    |Error    |Error      |Normal     |
 * |         |           |          |         |           |           |
 * |Transient|   N/A     | Error    |Secure   |Normal     |Normal     |
 * --------------------------------------------------------------------
 */

#घोषणा KVMPPC_GFN_UVMEM_PFN	(1UL << 63)
#घोषणा KVMPPC_GFN_MEM_PFN	(1UL << 62)
#घोषणा KVMPPC_GFN_SHARED	(1UL << 61)
#घोषणा KVMPPC_GFN_SECURE	(KVMPPC_GFN_UVMEM_PFN | KVMPPC_GFN_MEM_PFN)
#घोषणा KVMPPC_GFN_FLAG_MASK	(KVMPPC_GFN_SECURE | KVMPPC_GFN_SHARED)
#घोषणा KVMPPC_GFN_PFN_MASK	(~KVMPPC_GFN_FLAG_MASK)

काष्ठा kvmppc_uvmem_slot अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ nr_pfns;
	अचिन्हित दीर्घ base_pfn;
	अचिन्हित दीर्घ *pfns;
पूर्ण;
काष्ठा kvmppc_uvmem_page_pvt अणु
	काष्ठा kvm *kvm;
	अचिन्हित दीर्घ gpa;
	bool skip_page_out;
	bool हटाओ_gfn;
पूर्ण;

bool kvmppc_uvmem_available(व्योम)
अणु
	/*
	 * If kvmppc_uvmem_biपंचांगap != शून्य, then there is an ultravisor
	 * and our data काष्ठाures have been initialized successfully.
	 */
	वापस !!kvmppc_uvmem_biपंचांगap;
पूर्ण

पूर्णांक kvmppc_uvmem_slot_init(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *slot)
अणु
	काष्ठा kvmppc_uvmem_slot *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	p->pfns = vzalloc(array_size(slot->npages, माप(*p->pfns)));
	अगर (!p->pfns) अणु
		kमुक्त(p);
		वापस -ENOMEM;
	पूर्ण
	p->nr_pfns = slot->npages;
	p->base_pfn = slot->base_gfn;

	mutex_lock(&kvm->arch.uvmem_lock);
	list_add(&p->list, &kvm->arch.uvmem_pfns);
	mutex_unlock(&kvm->arch.uvmem_lock);

	वापस 0;
पूर्ण

/*
 * All device PFNs are alपढ़ोy released by the समय we come here.
 */
व्योम kvmppc_uvmem_slot_मुक्त(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *slot)
अणु
	काष्ठा kvmppc_uvmem_slot *p, *next;

	mutex_lock(&kvm->arch.uvmem_lock);
	list_क्रम_each_entry_safe(p, next, &kvm->arch.uvmem_pfns, list) अणु
		अगर (p->base_pfn == slot->base_gfn) अणु
			vमुक्त(p->pfns);
			list_del(&p->list);
			kमुक्त(p);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&kvm->arch.uvmem_lock);
पूर्ण

अटल व्योम kvmppc_mark_gfn(अचिन्हित दीर्घ gfn, काष्ठा kvm *kvm,
			अचिन्हित दीर्घ flag, अचिन्हित दीर्घ uvmem_pfn)
अणु
	काष्ठा kvmppc_uvmem_slot *p;

	list_क्रम_each_entry(p, &kvm->arch.uvmem_pfns, list) अणु
		अगर (gfn >= p->base_pfn && gfn < p->base_pfn + p->nr_pfns) अणु
			अचिन्हित दीर्घ index = gfn - p->base_pfn;

			अगर (flag == KVMPPC_GFN_UVMEM_PFN)
				p->pfns[index] = uvmem_pfn | flag;
			अन्यथा
				p->pfns[index] = flag;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* mark the GFN as secure-GFN associated with @uvmem pfn device-PFN. */
अटल व्योम kvmppc_gfn_secure_uvmem_pfn(अचिन्हित दीर्घ gfn,
			अचिन्हित दीर्घ uvmem_pfn, काष्ठा kvm *kvm)
अणु
	kvmppc_mark_gfn(gfn, kvm, KVMPPC_GFN_UVMEM_PFN, uvmem_pfn);
पूर्ण

/* mark the GFN as secure-GFN associated with a memory-PFN. */
अटल व्योम kvmppc_gfn_secure_mem_pfn(अचिन्हित दीर्घ gfn, काष्ठा kvm *kvm)
अणु
	kvmppc_mark_gfn(gfn, kvm, KVMPPC_GFN_MEM_PFN, 0);
पूर्ण

/* mark the GFN as a shared GFN. */
अटल व्योम kvmppc_gfn_shared(अचिन्हित दीर्घ gfn, काष्ठा kvm *kvm)
अणु
	kvmppc_mark_gfn(gfn, kvm, KVMPPC_GFN_SHARED, 0);
पूर्ण

/* mark the GFN as a non-existent GFN. */
अटल व्योम kvmppc_gfn_हटाओ(अचिन्हित दीर्घ gfn, काष्ठा kvm *kvm)
अणु
	kvmppc_mark_gfn(gfn, kvm, 0, 0);
पूर्ण

/* वापस true, अगर the GFN is a secure-GFN backed by a secure-PFN */
अटल bool kvmppc_gfn_is_uvmem_pfn(अचिन्हित दीर्घ gfn, काष्ठा kvm *kvm,
				    अचिन्हित दीर्घ *uvmem_pfn)
अणु
	काष्ठा kvmppc_uvmem_slot *p;

	list_क्रम_each_entry(p, &kvm->arch.uvmem_pfns, list) अणु
		अगर (gfn >= p->base_pfn && gfn < p->base_pfn + p->nr_pfns) अणु
			अचिन्हित दीर्घ index = gfn - p->base_pfn;

			अगर (p->pfns[index] & KVMPPC_GFN_UVMEM_PFN) अणु
				अगर (uvmem_pfn)
					*uvmem_pfn = p->pfns[index] &
						     KVMPPC_GFN_PFN_MASK;
				वापस true;
			पूर्ण अन्यथा
				वापस false;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/*
 * starting from *gfn search क्रम the next available GFN that is not yet
 * transitioned to a secure GFN.  वापस the value of that GFN in *gfn.  If a
 * GFN is found, वापस true, अन्यथा वापस false
 *
 * Must be called with kvm->arch.uvmem_lock  held.
 */
अटल bool kvmppc_next_nontransitioned_gfn(स्थिर काष्ठा kvm_memory_slot *memslot,
		काष्ठा kvm *kvm, अचिन्हित दीर्घ *gfn)
अणु
	काष्ठा kvmppc_uvmem_slot *p;
	bool ret = false;
	अचिन्हित दीर्घ i;

	list_क्रम_each_entry(p, &kvm->arch.uvmem_pfns, list)
		अगर (*gfn >= p->base_pfn && *gfn < p->base_pfn + p->nr_pfns)
			अवरोध;
	अगर (!p)
		वापस ret;
	/*
	 * The code below assumes, one to one correspondence between
	 * kvmppc_uvmem_slot and memslot.
	 */
	क्रम (i = *gfn; i < p->base_pfn + p->nr_pfns; i++) अणु
		अचिन्हित दीर्घ index = i - p->base_pfn;

		अगर (!(p->pfns[index] & KVMPPC_GFN_FLAG_MASK)) अणु
			*gfn = i;
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक kvmppc_memslot_page_merge(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *memslot, bool merge)
अणु
	अचिन्हित दीर्घ gfn = memslot->base_gfn;
	अचिन्हित दीर्घ end, start = gfn_to_hva(kvm, gfn);
	पूर्णांक ret = 0;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक merge_flag = (merge) ? MADV_MERGEABLE : MADV_UNMERGEABLE;

	अगर (kvm_is_error_hva(start))
		वापस H_STATE;

	end = start + (memslot->npages << PAGE_SHIFT);

	mmap_ग_लिखो_lock(kvm->mm);
	करो अणु
		vma = find_vma_पूर्णांकersection(kvm->mm, start, end);
		अगर (!vma) अणु
			ret = H_STATE;
			अवरोध;
		पूर्ण
		ret = ksm_madvise(vma, vma->vm_start, vma->vm_end,
			  merge_flag, &vma->vm_flags);
		अगर (ret) अणु
			ret = H_STATE;
			अवरोध;
		पूर्ण
		start = vma->vm_end;
	पूर्ण जबतक (end > vma->vm_end);

	mmap_ग_लिखो_unlock(kvm->mm);
	वापस ret;
पूर्ण

अटल व्योम __kvmppc_uvmem_memslot_delete(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	uv_unरेजिस्टर_mem_slot(kvm->arch.lpid, memslot->id);
	kvmppc_uvmem_slot_मुक्त(kvm, memslot);
	kvmppc_memslot_page_merge(kvm, memslot, true);
पूर्ण

अटल पूर्णांक __kvmppc_uvmem_memslot_create(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	पूर्णांक ret = H_PARAMETER;

	अगर (kvmppc_memslot_page_merge(kvm, memslot, false))
		वापस ret;

	अगर (kvmppc_uvmem_slot_init(kvm, memslot))
		जाओ out1;

	ret = uv_रेजिस्टर_mem_slot(kvm->arch.lpid,
				   memslot->base_gfn << PAGE_SHIFT,
				   memslot->npages * PAGE_SIZE,
				   0, memslot->id);
	अगर (ret < 0) अणु
		ret = H_PARAMETER;
		जाओ out;
	पूर्ण
	वापस 0;
out:
	kvmppc_uvmem_slot_मुक्त(kvm, memslot);
out1:
	kvmppc_memslot_page_merge(kvm, memslot, true);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ kvmppc_h_svm_init_start(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot, *m;
	पूर्णांक ret = H_SUCCESS;
	पूर्णांक srcu_idx;

	kvm->arch.secure_guest = KVMPPC_SECURE_INIT_START;

	अगर (!kvmppc_uvmem_biपंचांगap)
		वापस H_UNSUPPORTED;

	/* Only radix guests can be secure guests */
	अगर (!kvm_is_radix(kvm))
		वापस H_UNSUPPORTED;

	/* NAK the transition to secure अगर not enabled */
	अगर (!kvm->arch.svm_enabled)
		वापस H_AUTHORITY;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);

	/* रेजिस्टर the memslot */
	slots = kvm_memslots(kvm);
	kvm_क्रम_each_memslot(memslot, slots) अणु
		ret = __kvmppc_uvmem_memslot_create(kvm, memslot);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (ret) अणु
		slots = kvm_memslots(kvm);
		kvm_क्रम_each_memslot(m, slots) अणु
			अगर (m == memslot)
				अवरोध;
			__kvmppc_uvmem_memslot_delete(kvm, memslot);
		पूर्ण
	पूर्ण

	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस ret;
पूर्ण

/*
 * Provision a new page on HV side and copy over the contents
 * from secure memory using UV_PAGE_OUT uvcall.
 * Caller must held kvm->arch.uvmem_lock.
 */
अटल पूर्णांक __kvmppc_svm_page_out(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, अचिन्हित दीर्घ page_shअगरt,
		काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa)
अणु
	अचिन्हित दीर्घ src_pfn, dst_pfn = 0;
	काष्ठा migrate_vma mig;
	काष्ठा page *dpage, *spage;
	काष्ठा kvmppc_uvmem_page_pvt *pvt;
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret = U_SUCCESS;

	स_रखो(&mig, 0, माप(mig));
	mig.vma = vma;
	mig.start = start;
	mig.end = end;
	mig.src = &src_pfn;
	mig.dst = &dst_pfn;
	mig.pgmap_owner = &kvmppc_uvmem_pgmap;
	mig.flags = MIGRATE_VMA_SELECT_DEVICE_PRIVATE;

	/* The requested page is alपढ़ोy paged-out, nothing to करो */
	अगर (!kvmppc_gfn_is_uvmem_pfn(gpa >> page_shअगरt, kvm, शून्य))
		वापस ret;

	ret = migrate_vma_setup(&mig);
	अगर (ret)
		वापस -1;

	spage = migrate_pfn_to_page(*mig.src);
	अगर (!spage || !(*mig.src & MIGRATE_PFN_MIGRATE))
		जाओ out_finalize;

	अगर (!is_zone_device_page(spage))
		जाओ out_finalize;

	dpage = alloc_page_vma(GFP_HIGHUSER, vma, start);
	अगर (!dpage) अणु
		ret = -1;
		जाओ out_finalize;
	पूर्ण

	lock_page(dpage);
	pvt = spage->zone_device_data;
	pfn = page_to_pfn(dpage);

	/*
	 * This function is used in two हालs:
	 * - When HV touches a secure page, क्रम which we करो UV_PAGE_OUT
	 * - When a secure page is converted to shared page, we *get*
	 *   the page to essentially unmap the device page. In this
	 *   हाल we skip page-out.
	 */
	अगर (!pvt->skip_page_out)
		ret = uv_page_out(kvm->arch.lpid, pfn << page_shअगरt,
				  gpa, 0, page_shअगरt);

	अगर (ret == U_SUCCESS)
		*mig.dst = migrate_pfn(pfn) | MIGRATE_PFN_LOCKED;
	अन्यथा अणु
		unlock_page(dpage);
		__मुक्त_page(dpage);
		जाओ out_finalize;
	पूर्ण

	migrate_vma_pages(&mig);

out_finalize:
	migrate_vma_finalize(&mig);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_svm_page_out(काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				      अचिन्हित दीर्घ page_shअगरt,
				      काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa)
अणु
	पूर्णांक ret;

	mutex_lock(&kvm->arch.uvmem_lock);
	ret = __kvmppc_svm_page_out(vma, start, end, page_shअगरt, kvm, gpa);
	mutex_unlock(&kvm->arch.uvmem_lock);

	वापस ret;
पूर्ण

/*
 * Drop device pages that we मुख्यtain क्रम the secure guest
 *
 * We first mark the pages to be skipped from UV_PAGE_OUT when there
 * is HV side fault on these pages. Next we *get* these pages, क्रमcing
 * fault on them, करो fault समय migration to replace the device PTEs in
 * QEMU page table with normal PTEs from newly allocated pages.
 */
व्योम kvmppc_uvmem_drop_pages(स्थिर काष्ठा kvm_memory_slot *slot,
			     काष्ठा kvm *kvm, bool skip_page_out)
अणु
	पूर्णांक i;
	काष्ठा kvmppc_uvmem_page_pvt *pvt;
	काष्ठा page *uvmem_page;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	अचिन्हित दीर्घ uvmem_pfn, gfn;
	अचिन्हित दीर्घ addr;

	mmap_पढ़ो_lock(kvm->mm);

	addr = slot->userspace_addr;

	gfn = slot->base_gfn;
	क्रम (i = slot->npages; i; --i, ++gfn, addr += PAGE_SIZE) अणु

		/* Fetch the VMA अगर addr is not in the latest fetched one */
		अगर (!vma || addr >= vma->vm_end) अणु
			vma = find_vma_पूर्णांकersection(kvm->mm, addr, addr+1);
			अगर (!vma) अणु
				pr_err("Can't find VMA for gfn:0x%lx\n", gfn);
				अवरोध;
			पूर्ण
		पूर्ण

		mutex_lock(&kvm->arch.uvmem_lock);

		अगर (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) अणु
			uvmem_page = pfn_to_page(uvmem_pfn);
			pvt = uvmem_page->zone_device_data;
			pvt->skip_page_out = skip_page_out;
			pvt->हटाओ_gfn = true;

			अगर (__kvmppc_svm_page_out(vma, addr, addr + PAGE_SIZE,
						  PAGE_SHIFT, kvm, pvt->gpa))
				pr_err("Can't page out gpa:0x%lx addr:0x%lx\n",
				       pvt->gpa, addr);
		पूर्ण अन्यथा अणु
			/* Remove the shared flag अगर any */
			kvmppc_gfn_हटाओ(gfn, kvm);
		पूर्ण

		mutex_unlock(&kvm->arch.uvmem_lock);
	पूर्ण

	mmap_पढ़ो_unlock(kvm->mm);
पूर्ण

अचिन्हित दीर्घ kvmppc_h_svm_init_पात(काष्ठा kvm *kvm)
अणु
	पूर्णांक srcu_idx;
	काष्ठा kvm_memory_slot *memslot;

	/*
	 * Expect to be called only after INIT_START and beक्रमe INIT_DONE.
	 * If INIT_DONE was completed, use normal VM termination sequence.
	 */
	अगर (!(kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START))
		वापस H_UNSUPPORTED;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस H_STATE;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);

	kvm_क्रम_each_memslot(memslot, kvm_memslots(kvm))
		kvmppc_uvmem_drop_pages(memslot, kvm, false);

	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	kvm->arch.secure_guest = 0;
	uv_svm_terminate(kvm->arch.lpid);

	वापस H_PARAMETER;
पूर्ण

/*
 * Get a मुक्त device PFN from the pool
 *
 * Called when a normal page is moved to secure memory (UV_PAGE_IN). Device
 * PFN will be used to keep track of the secure page on HV side.
 *
 * Called with kvm->arch.uvmem_lock held
 */
अटल काष्ठा page *kvmppc_uvmem_get_page(अचिन्हित दीर्घ gpa, काष्ठा kvm *kvm)
अणु
	काष्ठा page *dpage = शून्य;
	अचिन्हित दीर्घ bit, uvmem_pfn;
	काष्ठा kvmppc_uvmem_page_pvt *pvt;
	अचिन्हित दीर्घ pfn_last, pfn_first;

	pfn_first = kvmppc_uvmem_pgmap.range.start >> PAGE_SHIFT;
	pfn_last = pfn_first +
		   (range_len(&kvmppc_uvmem_pgmap.range) >> PAGE_SHIFT);

	spin_lock(&kvmppc_uvmem_biपंचांगap_lock);
	bit = find_first_zero_bit(kvmppc_uvmem_biपंचांगap,
				  pfn_last - pfn_first);
	अगर (bit >= (pfn_last - pfn_first))
		जाओ out;
	biपंचांगap_set(kvmppc_uvmem_biपंचांगap, bit, 1);
	spin_unlock(&kvmppc_uvmem_biपंचांगap_lock);

	pvt = kzalloc(माप(*pvt), GFP_KERNEL);
	अगर (!pvt)
		जाओ out_clear;

	uvmem_pfn = bit + pfn_first;
	kvmppc_gfn_secure_uvmem_pfn(gpa >> PAGE_SHIFT, uvmem_pfn, kvm);

	pvt->gpa = gpa;
	pvt->kvm = kvm;

	dpage = pfn_to_page(uvmem_pfn);
	dpage->zone_device_data = pvt;
	get_page(dpage);
	lock_page(dpage);
	वापस dpage;
out_clear:
	spin_lock(&kvmppc_uvmem_biपंचांगap_lock);
	biपंचांगap_clear(kvmppc_uvmem_biपंचांगap, bit, 1);
out:
	spin_unlock(&kvmppc_uvmem_biपंचांगap_lock);
	वापस शून्य;
पूर्ण

/*
 * Alloc a PFN from निजी device memory pool. If @pagein is true,
 * copy page from normal memory to secure memory using UV_PAGE_IN uvcall.
 */
अटल पूर्णांक kvmppc_svm_page_in(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, अचिन्हित दीर्घ gpa, काष्ठा kvm *kvm,
		अचिन्हित दीर्घ page_shअगरt,
		bool pagein)
अणु
	अचिन्हित दीर्घ src_pfn, dst_pfn = 0;
	काष्ठा migrate_vma mig;
	काष्ठा page *spage;
	अचिन्हित दीर्घ pfn;
	काष्ठा page *dpage;
	पूर्णांक ret = 0;

	स_रखो(&mig, 0, माप(mig));
	mig.vma = vma;
	mig.start = start;
	mig.end = end;
	mig.src = &src_pfn;
	mig.dst = &dst_pfn;
	mig.flags = MIGRATE_VMA_SELECT_SYSTEM;

	ret = migrate_vma_setup(&mig);
	अगर (ret)
		वापस ret;

	अगर (!(*mig.src & MIGRATE_PFN_MIGRATE)) अणु
		ret = -1;
		जाओ out_finalize;
	पूर्ण

	dpage = kvmppc_uvmem_get_page(gpa, kvm);
	अगर (!dpage) अणु
		ret = -1;
		जाओ out_finalize;
	पूर्ण

	अगर (pagein) अणु
		pfn = *mig.src >> MIGRATE_PFN_SHIFT;
		spage = migrate_pfn_to_page(*mig.src);
		अगर (spage) अणु
			ret = uv_page_in(kvm->arch.lpid, pfn << page_shअगरt,
					gpa, 0, page_shअगरt);
			अगर (ret)
				जाओ out_finalize;
		पूर्ण
	पूर्ण

	*mig.dst = migrate_pfn(page_to_pfn(dpage)) | MIGRATE_PFN_LOCKED;
	migrate_vma_pages(&mig);
out_finalize:
	migrate_vma_finalize(&mig);
	वापस ret;
पूर्ण

अटल पूर्णांक kvmppc_uv_migrate_mem_slot(काष्ठा kvm *kvm,
		स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	अचिन्हित दीर्घ gfn = memslot->base_gfn;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ start, end;
	पूर्णांक ret = 0;

	mmap_पढ़ो_lock(kvm->mm);
	mutex_lock(&kvm->arch.uvmem_lock);
	जबतक (kvmppc_next_nontransitioned_gfn(memslot, kvm, &gfn)) अणु
		ret = H_STATE;
		start = gfn_to_hva(kvm, gfn);
		अगर (kvm_is_error_hva(start))
			अवरोध;

		end = start + (1UL << PAGE_SHIFT);
		vma = find_vma_पूर्णांकersection(kvm->mm, start, end);
		अगर (!vma || vma->vm_start > start || vma->vm_end < end)
			अवरोध;

		ret = kvmppc_svm_page_in(vma, start, end,
				(gfn << PAGE_SHIFT), kvm, PAGE_SHIFT, false);
		अगर (ret) अणु
			ret = H_STATE;
			अवरोध;
		पूर्ण

		/* relinquish the cpu अगर needed */
		cond_resched();
	पूर्ण
	mutex_unlock(&kvm->arch.uvmem_lock);
	mmap_पढ़ो_unlock(kvm->mm);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ kvmppc_h_svm_init_करोne(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक srcu_idx;
	दीर्घ ret = H_SUCCESS;

	अगर (!(kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START))
		वापस H_UNSUPPORTED;

	/* migrate any unmoved normal pfn to device pfns*/
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	slots = kvm_memslots(kvm);
	kvm_क्रम_each_memslot(memslot, slots) अणु
		ret = kvmppc_uv_migrate_mem_slot(kvm, memslot);
		अगर (ret) अणु
			/*
			 * The pages will reमुख्य transitioned.
			 * Its the callers responsibility to
			 * terminate the VM, which will unकरो
			 * all state of the VM. Till then
			 * this VM is in a erroneous state.
			 * Its KVMPPC_SECURE_INIT_DONE will
			 * reमुख्य unset.
			 */
			ret = H_STATE;
			जाओ out;
		पूर्ण
	पूर्ण

	kvm->arch.secure_guest |= KVMPPC_SECURE_INIT_DONE;
	pr_info("LPID %d went secure\n", kvm->arch.lpid);

out:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस ret;
पूर्ण

/*
 * Shares the page with HV, thus making it a normal page.
 *
 * - If the page is alपढ़ोy secure, then provision a new page and share
 * - If the page is a normal page, share the existing page
 *
 * In the क्रमmer हाल, uses dev_pagemap_ops.migrate_to_ram handler
 * to unmap the device page from QEMU's page tables.
 */
अटल अचिन्हित दीर्घ kvmppc_share_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa,
		अचिन्हित दीर्घ page_shअगरt)
अणु

	पूर्णांक ret = H_PARAMETER;
	काष्ठा page *uvmem_page;
	काष्ठा kvmppc_uvmem_page_pvt *pvt;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ gfn = gpa >> page_shअगरt;
	पूर्णांक srcu_idx;
	अचिन्हित दीर्घ uvmem_pfn;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	mutex_lock(&kvm->arch.uvmem_lock);
	अगर (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) अणु
		uvmem_page = pfn_to_page(uvmem_pfn);
		pvt = uvmem_page->zone_device_data;
		pvt->skip_page_out = true;
		/*
		 * करो not drop the GFN. It is a valid GFN
		 * that is transitioned to a shared GFN.
		 */
		pvt->हटाओ_gfn = false;
	पूर्ण

retry:
	mutex_unlock(&kvm->arch.uvmem_lock);
	pfn = gfn_to_pfn(kvm, gfn);
	अगर (is_error_noslot_pfn(pfn))
		जाओ out;

	mutex_lock(&kvm->arch.uvmem_lock);
	अगर (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, &uvmem_pfn)) अणु
		uvmem_page = pfn_to_page(uvmem_pfn);
		pvt = uvmem_page->zone_device_data;
		pvt->skip_page_out = true;
		pvt->हटाओ_gfn = false; /* it जारीs to be a valid GFN */
		kvm_release_pfn_clean(pfn);
		जाओ retry;
	पूर्ण

	अगर (!uv_page_in(kvm->arch.lpid, pfn << page_shअगरt, gpa, 0,
				page_shअगरt)) अणु
		kvmppc_gfn_shared(gfn, kvm);
		ret = H_SUCCESS;
	पूर्ण
	kvm_release_pfn_clean(pfn);
	mutex_unlock(&kvm->arch.uvmem_lock);
out:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस ret;
पूर्ण

/*
 * H_SVM_PAGE_IN: Move page from normal memory to secure memory.
 *
 * H_PAGE_IN_SHARED flag makes the page shared which means that the same
 * memory in is visible from both UV and HV.
 */
अचिन्हित दीर्घ kvmppc_h_svm_page_in(काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa,
		अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ page_shअगरt)
अणु
	अचिन्हित दीर्घ start, end;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक srcu_idx;
	अचिन्हित दीर्घ gfn = gpa >> page_shअगरt;
	पूर्णांक ret;

	अगर (!(kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START))
		वापस H_UNSUPPORTED;

	अगर (page_shअगरt != PAGE_SHIFT)
		वापस H_P3;

	अगर (flags & ~H_PAGE_IN_SHARED)
		वापस H_P2;

	अगर (flags & H_PAGE_IN_SHARED)
		वापस kvmppc_share_page(kvm, gpa, page_shअगरt);

	ret = H_PARAMETER;
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	mmap_पढ़ो_lock(kvm->mm);

	start = gfn_to_hva(kvm, gfn);
	अगर (kvm_is_error_hva(start))
		जाओ out;

	mutex_lock(&kvm->arch.uvmem_lock);
	/* Fail the page-in request of an alपढ़ोy paged-in page */
	अगर (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, शून्य))
		जाओ out_unlock;

	end = start + (1UL << page_shअगरt);
	vma = find_vma_पूर्णांकersection(kvm->mm, start, end);
	अगर (!vma || vma->vm_start > start || vma->vm_end < end)
		जाओ out_unlock;

	अगर (kvmppc_svm_page_in(vma, start, end, gpa, kvm, page_shअगरt,
				true))
		जाओ out_unlock;

	ret = H_SUCCESS;

out_unlock:
	mutex_unlock(&kvm->arch.uvmem_lock);
out:
	mmap_पढ़ो_unlock(kvm->mm);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस ret;
पूर्ण


/*
 * Fault handler callback that माला_लो called when HV touches any page that
 * has been moved to secure memory, we ask UV to give back the page by
 * issuing UV_PAGE_OUT uvcall.
 *
 * This eventually results in dropping of device PFN and the newly
 * provisioned page/PFN माला_लो populated in QEMU page tables.
 */
अटल vm_fault_t kvmppc_uvmem_migrate_to_ram(काष्ठा vm_fault *vmf)
अणु
	काष्ठा kvmppc_uvmem_page_pvt *pvt = vmf->page->zone_device_data;

	अगर (kvmppc_svm_page_out(vmf->vma, vmf->address,
				vmf->address + PAGE_SIZE, PAGE_SHIFT,
				pvt->kvm, pvt->gpa))
		वापस VM_FAULT_SIGBUS;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * Release the device PFN back to the pool
 *
 * Gets called when secure GFN tranistions from a secure-PFN
 * to a normal PFN during H_SVM_PAGE_OUT.
 * Gets called with kvm->arch.uvmem_lock held.
 */
अटल व्योम kvmppc_uvmem_page_मुक्त(काष्ठा page *page)
अणु
	अचिन्हित दीर्घ pfn = page_to_pfn(page) -
			(kvmppc_uvmem_pgmap.range.start >> PAGE_SHIFT);
	काष्ठा kvmppc_uvmem_page_pvt *pvt;

	spin_lock(&kvmppc_uvmem_biपंचांगap_lock);
	biपंचांगap_clear(kvmppc_uvmem_biपंचांगap, pfn, 1);
	spin_unlock(&kvmppc_uvmem_biपंचांगap_lock);

	pvt = page->zone_device_data;
	page->zone_device_data = शून्य;
	अगर (pvt->हटाओ_gfn)
		kvmppc_gfn_हटाओ(pvt->gpa >> PAGE_SHIFT, pvt->kvm);
	अन्यथा
		kvmppc_gfn_secure_mem_pfn(pvt->gpa >> PAGE_SHIFT, pvt->kvm);
	kमुक्त(pvt);
पूर्ण

अटल स्थिर काष्ठा dev_pagemap_ops kvmppc_uvmem_ops = अणु
	.page_मुक्त = kvmppc_uvmem_page_मुक्त,
	.migrate_to_ram	= kvmppc_uvmem_migrate_to_ram,
पूर्ण;

/*
 * H_SVM_PAGE_OUT: Move page from secure memory to normal memory.
 */
अचिन्हित दीर्घ
kvmppc_h_svm_page_out(काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa,
		      अचिन्हित दीर्घ flags, अचिन्हित दीर्घ page_shअगरt)
अणु
	अचिन्हित दीर्घ gfn = gpa >> page_shअगरt;
	अचिन्हित दीर्घ start, end;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक srcu_idx;
	पूर्णांक ret;

	अगर (!(kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START))
		वापस H_UNSUPPORTED;

	अगर (page_shअगरt != PAGE_SHIFT)
		वापस H_P3;

	अगर (flags)
		वापस H_P2;

	ret = H_PARAMETER;
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	mmap_पढ़ो_lock(kvm->mm);
	start = gfn_to_hva(kvm, gfn);
	अगर (kvm_is_error_hva(start))
		जाओ out;

	end = start + (1UL << page_shअगरt);
	vma = find_vma_पूर्णांकersection(kvm->mm, start, end);
	अगर (!vma || vma->vm_start > start || vma->vm_end < end)
		जाओ out;

	अगर (!kvmppc_svm_page_out(vma, start, end, page_shअगरt, kvm, gpa))
		ret = H_SUCCESS;
out:
	mmap_पढ़ो_unlock(kvm->mm);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस ret;
पूर्ण

पूर्णांक kvmppc_send_page_to_uv(काष्ठा kvm *kvm, अचिन्हित दीर्घ gfn)
अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret = U_SUCCESS;

	pfn = gfn_to_pfn(kvm, gfn);
	अगर (is_error_noslot_pfn(pfn))
		वापस -EFAULT;

	mutex_lock(&kvm->arch.uvmem_lock);
	अगर (kvmppc_gfn_is_uvmem_pfn(gfn, kvm, शून्य))
		जाओ out;

	ret = uv_page_in(kvm->arch.lpid, pfn << PAGE_SHIFT, gfn << PAGE_SHIFT,
			 0, PAGE_SHIFT);
out:
	kvm_release_pfn_clean(pfn);
	mutex_unlock(&kvm->arch.uvmem_lock);
	वापस (ret == U_SUCCESS) ? RESUME_GUEST : -EFAULT;
पूर्ण

पूर्णांक kvmppc_uvmem_memslot_create(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *new)
अणु
	पूर्णांक ret = __kvmppc_uvmem_memslot_create(kvm, new);

	अगर (!ret)
		ret = kvmppc_uv_migrate_mem_slot(kvm, new);

	वापस ret;
पूर्ण

व्योम kvmppc_uvmem_memslot_delete(काष्ठा kvm *kvm, स्थिर काष्ठा kvm_memory_slot *old)
अणु
	__kvmppc_uvmem_memslot_delete(kvm, old);
पूर्ण

अटल u64 kvmppc_get_secmem_size(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक i, len;
	स्थिर __be32 *prop;
	u64 size = 0;

	/*
	 * First try the new ibm,secure-memory nodes which supersede the
	 * secure-memory-ranges property.
	 * If we found some, no need to पढ़ो the deprecated ones.
	 */
	क्रम_each_compatible_node(np, शून्य, "ibm,secure-memory") अणु
		prop = of_get_property(np, "reg", &len);
		अगर (!prop)
			जारी;
		size += of_पढ़ो_number(prop + 2, 2);
	पूर्ण
	अगर (size)
		वापस size;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,uv-firmware");
	अगर (!np)
		जाओ out;

	prop = of_get_property(np, "secure-memory-ranges", &len);
	अगर (!prop)
		जाओ out_put;

	क्रम (i = 0; i < len / (माप(*prop) * 4); i++)
		size += of_पढ़ो_number(prop + (i * 4) + 2, 2);

out_put:
	of_node_put(np);
out:
	वापस size;
पूर्ण

पूर्णांक kvmppc_uvmem_init(व्योम)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ size;
	काष्ठा resource *res;
	व्योम *addr;
	अचिन्हित दीर्घ pfn_last, pfn_first;

	size = kvmppc_get_secmem_size();
	अगर (!size) अणु
		/*
		 * Don't fail the initialization of kvm-hv module अगर
		 * the platक्रमm करोesn't export ibm,uv-firmware node.
		 * Let normal guests run on such PEF-disabled platक्रमm.
		 */
		pr_info("KVMPPC-UVMEM: No support for secure guests\n");
		जाओ out;
	पूर्ण

	res = request_मुक्त_mem_region(&iomem_resource, size, "kvmppc_uvmem");
	अगर (IS_ERR(res)) अणु
		ret = PTR_ERR(res);
		जाओ out;
	पूर्ण

	kvmppc_uvmem_pgmap.type = MEMORY_DEVICE_PRIVATE;
	kvmppc_uvmem_pgmap.range.start = res->start;
	kvmppc_uvmem_pgmap.range.end = res->end;
	kvmppc_uvmem_pgmap.nr_range = 1;
	kvmppc_uvmem_pgmap.ops = &kvmppc_uvmem_ops;
	/* just one global instance: */
	kvmppc_uvmem_pgmap.owner = &kvmppc_uvmem_pgmap;
	addr = memremap_pages(&kvmppc_uvmem_pgmap, NUMA_NO_NODE);
	अगर (IS_ERR(addr)) अणु
		ret = PTR_ERR(addr);
		जाओ out_मुक्त_region;
	पूर्ण

	pfn_first = res->start >> PAGE_SHIFT;
	pfn_last = pfn_first + (resource_size(res) >> PAGE_SHIFT);
	kvmppc_uvmem_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(pfn_last - pfn_first),
				      माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!kvmppc_uvmem_biपंचांगap) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण

	pr_info("KVMPPC-UVMEM: Secure Memory size 0x%lx\n", size);
	वापस ret;
out_unmap:
	memunmap_pages(&kvmppc_uvmem_pgmap);
out_मुक्त_region:
	release_mem_region(res->start, size);
out:
	वापस ret;
पूर्ण

व्योम kvmppc_uvmem_मुक्त(व्योम)
अणु
	अगर (!kvmppc_uvmem_biपंचांगap)
		वापस;

	memunmap_pages(&kvmppc_uvmem_pgmap);
	release_mem_region(kvmppc_uvmem_pgmap.range.start,
			   range_len(&kvmppc_uvmem_pgmap.range));
	kमुक्त(kvmppc_uvmem_biपंचांगap);
पूर्ण

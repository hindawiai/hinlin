<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * AMD SVM-SEV support
 *
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 */

#समावेश <linux/kvm_types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kernel.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/psp-sev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/misc_cgroup.h>
#समावेश <linux/processor.h>
#समावेश <linux/trace_events.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>

#समावेश <यंत्र/trapnr.h>

#समावेश "x86.h"
#समावेश "svm.h"
#समावेश "svm_ops.h"
#समावेश "cpuid.h"
#समावेश "trace.h"

#घोषणा __ex(x) __kvm_handle_fault_on_reboot(x)

#अगर_अघोषित CONFIG_KVM_AMD_SEV
/*
 * When this config is not defined, SEV feature is not supported and APIs in
 * this file are not used but this file still माला_लो compiled पूर्णांकo the KVM AMD
 * module.
 *
 * We will not have MISC_CG_RES_SEV and MISC_CG_RES_SEV_ES entries in the क्रमागत
 * misc_res_type अणुपूर्ण defined in linux/misc_cgroup.h.
 *
 * Below macros allow compilation to succeed.
 */
#घोषणा MISC_CG_RES_SEV MISC_CG_RES_TYPES
#घोषणा MISC_CG_RES_SEV_ES MISC_CG_RES_TYPES
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_AMD_SEV
/* enable/disable SEV support */
अटल bool sev_enabled = true;
module_param_named(sev, sev_enabled, bool, 0444);

/* enable/disable SEV-ES support */
अटल bool sev_es_enabled = true;
module_param_named(sev_es, sev_es_enabled, bool, 0444);
#अन्यथा
#घोषणा sev_enabled false
#घोषणा sev_es_enabled false
#पूर्ण_अगर /* CONFIG_KVM_AMD_SEV */

अटल u8 sev_enc_bit;
अटल DECLARE_RWSEM(sev_deactivate_lock);
अटल DEFINE_MUTEX(sev_biपंचांगap_lock);
अचिन्हित पूर्णांक max_sev_asid;
अटल अचिन्हित पूर्णांक min_sev_asid;
अटल अचिन्हित दीर्घ sev_me_mask;
अटल अचिन्हित दीर्घ *sev_asid_biपंचांगap;
अटल अचिन्हित दीर्घ *sev_reclaim_asid_biपंचांगap;

काष्ठा enc_region अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ npages;
	काष्ठा page **pages;
	अचिन्हित दीर्घ uaddr;
	अचिन्हित दीर्घ size;
पूर्ण;

/* Called with the sev_biपंचांगap_lock held, or on shutकरोwn  */
अटल पूर्णांक sev_flush_asids(पूर्णांक min_asid, पूर्णांक max_asid)
अणु
	पूर्णांक ret, pos, error = 0;

	/* Check अगर there are any ASIDs to reclaim beक्रमe perक्रमming a flush */
	pos = find_next_bit(sev_reclaim_asid_biपंचांगap, max_asid, min_asid);
	अगर (pos >= max_asid)
		वापस -EBUSY;

	/*
	 * DEACTIVATE will clear the WBINVD indicator causing DF_FLUSH to fail,
	 * so it must be guarded.
	 */
	करोwn_ग_लिखो(&sev_deactivate_lock);

	wbinvd_on_all_cpus();
	ret = sev_guest_df_flush(&error);

	up_ग_लिखो(&sev_deactivate_lock);

	अगर (ret)
		pr_err("SEV: DF_FLUSH failed, ret=%d, error=%#x\n", ret, error);

	वापस ret;
पूर्ण

अटल अंतरभूत bool is_mirroring_enc_context(काष्ठा kvm *kvm)
अणु
	वापस !!to_kvm_svm(kvm)->sev_info.enc_context_owner;
पूर्ण

/* Must be called with the sev_biपंचांगap_lock held */
अटल bool __sev_recycle_asids(पूर्णांक min_asid, पूर्णांक max_asid)
अणु
	अगर (sev_flush_asids(min_asid, max_asid))
		वापस false;

	/* The flush process will flush all reclaimable SEV and SEV-ES ASIDs */
	biपंचांगap_xor(sev_asid_biपंचांगap, sev_asid_biपंचांगap, sev_reclaim_asid_biपंचांगap,
		   max_sev_asid);
	biपंचांगap_zero(sev_reclaim_asid_biपंचांगap, max_sev_asid);

	वापस true;
पूर्ण

अटल पूर्णांक sev_asid_new(काष्ठा kvm_sev_info *sev)
अणु
	पूर्णांक pos, min_asid, max_asid, ret;
	bool retry = true;
	क्रमागत misc_res_type type;

	type = sev->es_active ? MISC_CG_RES_SEV_ES : MISC_CG_RES_SEV;
	WARN_ON(sev->misc_cg);
	sev->misc_cg = get_current_misc_cg();
	ret = misc_cg_try_अक्षरge(type, sev->misc_cg, 1);
	अगर (ret) अणु
		put_misc_cg(sev->misc_cg);
		sev->misc_cg = शून्य;
		वापस ret;
	पूर्ण

	mutex_lock(&sev_biपंचांगap_lock);

	/*
	 * SEV-enabled guests must use asid from min_sev_asid to max_sev_asid.
	 * SEV-ES-enabled guest can use from 1 to min_sev_asid - 1.
	 */
	min_asid = sev->es_active ? 0 : min_sev_asid - 1;
	max_asid = sev->es_active ? min_sev_asid - 1 : max_sev_asid;
again:
	pos = find_next_zero_bit(sev_asid_biपंचांगap, max_sev_asid, min_asid);
	अगर (pos >= max_asid) अणु
		अगर (retry && __sev_recycle_asids(min_asid, max_asid)) अणु
			retry = false;
			जाओ again;
		पूर्ण
		mutex_unlock(&sev_biपंचांगap_lock);
		ret = -EBUSY;
		जाओ e_unअक्षरge;
	पूर्ण

	__set_bit(pos, sev_asid_biपंचांगap);

	mutex_unlock(&sev_biपंचांगap_lock);

	वापस pos + 1;
e_unअक्षरge:
	misc_cg_unअक्षरge(type, sev->misc_cg, 1);
	put_misc_cg(sev->misc_cg);
	sev->misc_cg = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक sev_get_asid(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	वापस sev->asid;
पूर्ण

अटल व्योम sev_asid_मुक्त(काष्ठा kvm_sev_info *sev)
अणु
	काष्ठा svm_cpu_data *sd;
	पूर्णांक cpu, pos;
	क्रमागत misc_res_type type;

	mutex_lock(&sev_biपंचांगap_lock);

	pos = sev->asid - 1;
	__set_bit(pos, sev_reclaim_asid_biपंचांगap);

	क्रम_each_possible_cpu(cpu) अणु
		sd = per_cpu(svm_data, cpu);
		sd->sev_vmcbs[pos] = शून्य;
	पूर्ण

	mutex_unlock(&sev_biपंचांगap_lock);

	type = sev->es_active ? MISC_CG_RES_SEV_ES : MISC_CG_RES_SEV;
	misc_cg_unअक्षरge(type, sev->misc_cg, 1);
	put_misc_cg(sev->misc_cg);
	sev->misc_cg = शून्य;
पूर्ण

अटल व्योम sev_decommission(अचिन्हित पूर्णांक handle)
अणु
	काष्ठा sev_data_decommission decommission;

	अगर (!handle)
		वापस;

	decommission.handle = handle;
	sev_guest_decommission(&decommission, शून्य);
पूर्ण

अटल व्योम sev_unbind_asid(काष्ठा kvm *kvm, अचिन्हित पूर्णांक handle)
अणु
	काष्ठा sev_data_deactivate deactivate;

	अगर (!handle)
		वापस;

	deactivate.handle = handle;

	/* Guard DEACTIVATE against WBINVD/DF_FLUSH used in ASID recycling */
	करोwn_पढ़ो(&sev_deactivate_lock);
	sev_guest_deactivate(&deactivate, शून्य);
	up_पढ़ो(&sev_deactivate_lock);

	sev_decommission(handle);
पूर्ण

अटल पूर्णांक sev_guest_init(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	bool es_active = argp->id == KVM_SEV_ES_INIT;
	पूर्णांक asid, ret;

	अगर (kvm->created_vcpus)
		वापस -EINVAL;

	ret = -EBUSY;
	अगर (unlikely(sev->active))
		वापस ret;

	sev->es_active = es_active;
	asid = sev_asid_new(sev);
	अगर (asid < 0)
		जाओ e_no_asid;
	sev->asid = asid;

	ret = sev_platक्रमm_init(&argp->error);
	अगर (ret)
		जाओ e_मुक्त;

	sev->active = true;
	sev->asid = asid;
	INIT_LIST_HEAD(&sev->regions_list);

	वापस 0;

e_मुक्त:
	sev_asid_मुक्त(sev);
	sev->asid = 0;
e_no_asid:
	sev->es_active = false;
	वापस ret;
पूर्ण

अटल पूर्णांक sev_bind_asid(काष्ठा kvm *kvm, अचिन्हित पूर्णांक handle, पूर्णांक *error)
अणु
	काष्ठा sev_data_activate activate;
	पूर्णांक asid = sev_get_asid(kvm);
	पूर्णांक ret;

	/* activate ASID on the given handle */
	activate.handle = handle;
	activate.asid   = asid;
	ret = sev_guest_activate(&activate, error);

	वापस ret;
पूर्ण

अटल पूर्णांक __sev_issue_cmd(पूर्णांक fd, पूर्णांक id, व्योम *data, पूर्णांक *error)
अणु
	काष्ठा fd f;
	पूर्णांक ret;

	f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;

	ret = sev_issue_cmd_बाह्यal_user(f.file, id, data, error);

	fdput(f);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_issue_cmd(काष्ठा kvm *kvm, पूर्णांक id, व्योम *data, पूर्णांक *error)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	वापस __sev_issue_cmd(sev->fd, id, data, error);
पूर्ण

अटल पूर्णांक sev_launch_start(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_launch_start start;
	काष्ठा kvm_sev_launch_start params;
	व्योम *dh_blob, *session_blob;
	पूर्णांक *error = &argp->error;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data, माप(params)))
		वापस -EFAULT;

	स_रखो(&start, 0, माप(start));

	dh_blob = शून्य;
	अगर (params.dh_uaddr) अणु
		dh_blob = psp_copy_user_blob(params.dh_uaddr, params.dh_len);
		अगर (IS_ERR(dh_blob))
			वापस PTR_ERR(dh_blob);

		start.dh_cert_address = __sme_set(__pa(dh_blob));
		start.dh_cert_len = params.dh_len;
	पूर्ण

	session_blob = शून्य;
	अगर (params.session_uaddr) अणु
		session_blob = psp_copy_user_blob(params.session_uaddr, params.session_len);
		अगर (IS_ERR(session_blob)) अणु
			ret = PTR_ERR(session_blob);
			जाओ e_मुक्त_dh;
		पूर्ण

		start.session_address = __sme_set(__pa(session_blob));
		start.session_len = params.session_len;
	पूर्ण

	start.handle = params.handle;
	start.policy = params.policy;

	/* create memory encryption context */
	ret = __sev_issue_cmd(argp->sev_fd, SEV_CMD_LAUNCH_START, &start, error);
	अगर (ret)
		जाओ e_मुक्त_session;

	/* Bind ASID to this guest */
	ret = sev_bind_asid(kvm, start.handle, error);
	अगर (ret) अणु
		sev_decommission(start.handle);
		जाओ e_मुक्त_session;
	पूर्ण

	/* वापस handle to userspace */
	params.handle = start.handle;
	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data, &params, माप(params))) अणु
		sev_unbind_asid(kvm, start.handle);
		ret = -EFAULT;
		जाओ e_मुक्त_session;
	पूर्ण

	sev->handle = start.handle;
	sev->fd = argp->sev_fd;

e_मुक्त_session:
	kमुक्त(session_blob);
e_मुक्त_dh:
	kमुक्त(dh_blob);
	वापस ret;
पूर्ण

अटल काष्ठा page **sev_pin_memory(काष्ठा kvm *kvm, अचिन्हित दीर्घ uaddr,
				    अचिन्हित दीर्घ ulen, अचिन्हित दीर्घ *n,
				    पूर्णांक ग_लिखो)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	अचिन्हित दीर्घ npages, size;
	पूर्णांक npinned;
	अचिन्हित दीर्घ locked, lock_limit;
	काष्ठा page **pages;
	अचिन्हित दीर्घ first, last;
	पूर्णांक ret;

	lockdep_निश्चित_held(&kvm->lock);

	अगर (ulen == 0 || uaddr + ulen < uaddr)
		वापस ERR_PTR(-EINVAL);

	/* Calculate number of pages. */
	first = (uaddr & PAGE_MASK) >> PAGE_SHIFT;
	last = ((uaddr + ulen - 1) & PAGE_MASK) >> PAGE_SHIFT;
	npages = (last - first + 1);

	locked = sev->pages_locked + npages;
	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	अगर (locked > lock_limit && !capable(CAP_IPC_LOCK)) अणु
		pr_err("SEV: %lu locked pages exceed the lock limit of %lu.\n", locked, lock_limit);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (WARN_ON_ONCE(npages > पूर्णांक_उच्च))
		वापस ERR_PTR(-EINVAL);

	/* Aव्योम using vदो_स्मृति क्रम smaller buffers. */
	size = npages * माप(काष्ठा page *);
	अगर (size > PAGE_SIZE)
		pages = __vदो_स्मृति(size, GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अन्यथा
		pages = kदो_स्मृति(size, GFP_KERNEL_ACCOUNT);

	अगर (!pages)
		वापस ERR_PTR(-ENOMEM);

	/* Pin the user भव address. */
	npinned = pin_user_pages_fast(uaddr, npages, ग_लिखो ? FOLL_WRITE : 0, pages);
	अगर (npinned != npages) अणु
		pr_err("SEV: Failure locking %lu pages.\n", npages);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	*n = npages;
	sev->pages_locked = locked;

	वापस pages;

err:
	अगर (npinned > 0)
		unpin_user_pages(pages, npinned);

	kvमुक्त(pages);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम sev_unpin_memory(काष्ठा kvm *kvm, काष्ठा page **pages,
			     अचिन्हित दीर्घ npages)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	unpin_user_pages(pages, npages);
	kvमुक्त(pages);
	sev->pages_locked -= npages;
पूर्ण

अटल व्योम sev_clflush_pages(काष्ठा page *pages[], अचिन्हित दीर्घ npages)
अणु
	uपूर्णांक8_t *page_भव;
	अचिन्हित दीर्घ i;

	अगर (this_cpu_has(X86_FEATURE_SME_COHERENT) || npages == 0 ||
	    pages == शून्य)
		वापस;

	क्रम (i = 0; i < npages; i++) अणु
		page_भव = kmap_atomic(pages[i]);
		clflush_cache_range(page_भव, PAGE_SIZE);
		kunmap_atomic(page_भव);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ get_num_contig_pages(अचिन्हित दीर्घ idx,
				काष्ठा page **inpages, अचिन्हित दीर्घ npages)
अणु
	अचिन्हित दीर्घ paddr, next_paddr;
	अचिन्हित दीर्घ i = idx + 1, pages = 1;

	/* find the number of contiguous pages starting from idx */
	paddr = __sme_page_pa(inpages[idx]);
	जबतक (i < npages) अणु
		next_paddr = __sme_page_pa(inpages[i++]);
		अगर ((paddr + PAGE_SIZE) == next_paddr) अणु
			pages++;
			paddr = next_paddr;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस pages;
पूर्ण

अटल पूर्णांक sev_launch_update_data(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	अचिन्हित दीर्घ vaddr, vaddr_end, next_vaddr, npages, pages, size, i;
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा kvm_sev_launch_update_data params;
	काष्ठा sev_data_launch_update_data data;
	काष्ठा page **inpages;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data, माप(params)))
		वापस -EFAULT;

	vaddr = params.uaddr;
	size = params.len;
	vaddr_end = vaddr + size;

	/* Lock the user memory. */
	inpages = sev_pin_memory(kvm, vaddr, size, &npages, 1);
	अगर (IS_ERR(inpages))
		वापस PTR_ERR(inpages);

	/*
	 * Flush (on non-coherent CPUs) beक्रमe LAUNCH_UPDATE encrypts pages in
	 * place; the cache may contain the data that was written unencrypted.
	 */
	sev_clflush_pages(inpages, npages);

	data.reserved = 0;
	data.handle = sev->handle;

	क्रम (i = 0; vaddr < vaddr_end; vaddr = next_vaddr, i += pages) अणु
		पूर्णांक offset, len;

		/*
		 * If the user buffer is not page-aligned, calculate the offset
		 * within the page.
		 */
		offset = vaddr & (PAGE_SIZE - 1);

		/* Calculate the number of pages that can be encrypted in one go. */
		pages = get_num_contig_pages(i, inpages, npages);

		len = min_t(माप_प्रकार, ((pages * PAGE_SIZE) - offset), size);

		data.len = len;
		data.address = __sme_page_pa(inpages[i]) + offset;
		ret = sev_issue_cmd(kvm, SEV_CMD_LAUNCH_UPDATE_DATA, &data, &argp->error);
		अगर (ret)
			जाओ e_unpin;

		size -= len;
		next_vaddr = vaddr + len;
	पूर्ण

e_unpin:
	/* content of memory is updated, mark pages dirty */
	क्रम (i = 0; i < npages; i++) अणु
		set_page_dirty_lock(inpages[i]);
		mark_page_accessed(inpages[i]);
	पूर्ण
	/* unlock the user pages */
	sev_unpin_memory(kvm, inpages, npages);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_es_sync_vmsa(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb_save_area *save = &svm->vmcb->save;

	/* Check some debug related fields beक्रमe encrypting the VMSA */
	अगर (svm->vcpu.guest_debug || (save->dr7 & ~DR7_FIXED_1))
		वापस -EINVAL;

	/* Sync registgers */
	save->rax = svm->vcpu.arch.regs[VCPU_REGS_RAX];
	save->rbx = svm->vcpu.arch.regs[VCPU_REGS_RBX];
	save->rcx = svm->vcpu.arch.regs[VCPU_REGS_RCX];
	save->rdx = svm->vcpu.arch.regs[VCPU_REGS_RDX];
	save->rsp = svm->vcpu.arch.regs[VCPU_REGS_RSP];
	save->rbp = svm->vcpu.arch.regs[VCPU_REGS_RBP];
	save->rsi = svm->vcpu.arch.regs[VCPU_REGS_RSI];
	save->rdi = svm->vcpu.arch.regs[VCPU_REGS_RDI];
#अगर_घोषित CONFIG_X86_64
	save->r8  = svm->vcpu.arch.regs[VCPU_REGS_R8];
	save->r9  = svm->vcpu.arch.regs[VCPU_REGS_R9];
	save->r10 = svm->vcpu.arch.regs[VCPU_REGS_R10];
	save->r11 = svm->vcpu.arch.regs[VCPU_REGS_R11];
	save->r12 = svm->vcpu.arch.regs[VCPU_REGS_R12];
	save->r13 = svm->vcpu.arch.regs[VCPU_REGS_R13];
	save->r14 = svm->vcpu.arch.regs[VCPU_REGS_R14];
	save->r15 = svm->vcpu.arch.regs[VCPU_REGS_R15];
#पूर्ण_अगर
	save->rip = svm->vcpu.arch.regs[VCPU_REGS_RIP];

	/* Sync some non-GPR रेजिस्टरs beक्रमe encrypting */
	save->xcr0 = svm->vcpu.arch.xcr0;
	save->pkru = svm->vcpu.arch.pkru;
	save->xss  = svm->vcpu.arch.ia32_xss;

	/*
	 * SEV-ES will use a VMSA that is poपूर्णांकed to by the VMCB, not
	 * the traditional VMSA that is part of the VMCB. Copy the
	 * traditional VMSA as it has been built so far (in prep
	 * क्रम LAUNCH_UPDATE_VMSA) to be the initial SEV-ES state.
	 */
	स_नकल(svm->vmsa, save, माप(*save));

	वापस 0;
पूर्ण

अटल पूर्णांक sev_launch_update_vmsa(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_launch_update_vmsa vmsa;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i, ret;

	अगर (!sev_es_guest(kvm))
		वापस -ENOTTY;

	vmsa.reserved = 0;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		काष्ठा vcpu_svm *svm = to_svm(vcpu);

		/* Perक्रमm some pre-encryption checks against the VMSA */
		ret = sev_es_sync_vmsa(svm);
		अगर (ret)
			वापस ret;

		/*
		 * The LAUNCH_UPDATE_VMSA command will perक्रमm in-place
		 * encryption of the VMSA memory content (i.e it will ग_लिखो
		 * the same memory region with the guest's key), so invalidate
		 * it first.
		 */
		clflush_cache_range(svm->vmsa, PAGE_SIZE);

		vmsa.handle = sev->handle;
		vmsa.address = __sme_pa(svm->vmsa);
		vmsa.len = PAGE_SIZE;
		ret = sev_issue_cmd(kvm, SEV_CMD_LAUNCH_UPDATE_VMSA, &vmsa,
				    &argp->error);
		अगर (ret)
			वापस ret;

		svm->vcpu.arch.guest_state_रक्षित = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sev_launch_measure(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	व्योम __user *measure = (व्योम __user *)(uपूर्णांकptr_t)argp->data;
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_launch_measure data;
	काष्ठा kvm_sev_launch_measure params;
	व्योम __user *p = शून्य;
	व्योम *blob = शून्य;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, measure, माप(params)))
		वापस -EFAULT;

	स_रखो(&data, 0, माप(data));

	/* User wants to query the blob length */
	अगर (!params.len)
		जाओ cmd;

	p = (व्योम __user *)(uपूर्णांकptr_t)params.uaddr;
	अगर (p) अणु
		अगर (params.len > SEV_FW_BLOB_MAX_SIZE)
			वापस -EINVAL;

		blob = kदो_स्मृति(params.len, GFP_KERNEL_ACCOUNT);
		अगर (!blob)
			वापस -ENOMEM;

		data.address = __psp_pa(blob);
		data.len = params.len;
	पूर्ण

cmd:
	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_LAUNCH_MEASURE, &data, &argp->error);

	/*
	 * If we query the session length, FW responded with expected data.
	 */
	अगर (!params.len)
		जाओ करोne;

	अगर (ret)
		जाओ e_मुक्त_blob;

	अगर (blob) अणु
		अगर (copy_to_user(p, blob, params.len))
			ret = -EFAULT;
	पूर्ण

करोne:
	params.len = data.len;
	अगर (copy_to_user(measure, &params, माप(params)))
		ret = -EFAULT;
e_मुक्त_blob:
	kमुक्त(blob);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_launch_finish(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_launch_finish data;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	data.handle = sev->handle;
	वापस sev_issue_cmd(kvm, SEV_CMD_LAUNCH_FINISH, &data, &argp->error);
पूर्ण

अटल पूर्णांक sev_guest_status(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा kvm_sev_guest_status params;
	काष्ठा sev_data_guest_status data;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	स_रखो(&data, 0, माप(data));

	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_GUEST_STATUS, &data, &argp->error);
	अगर (ret)
		वापस ret;

	params.policy = data.policy;
	params.state = data.state;
	params.handle = data.handle;

	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data, &params, माप(params)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक __sev_issue_dbg_cmd(काष्ठा kvm *kvm, अचिन्हित दीर्घ src,
			       अचिन्हित दीर्घ dst, पूर्णांक size,
			       पूर्णांक *error, bool enc)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_dbg data;

	data.reserved = 0;
	data.handle = sev->handle;
	data.dst_addr = dst;
	data.src_addr = src;
	data.len = size;

	वापस sev_issue_cmd(kvm,
			     enc ? SEV_CMD_DBG_ENCRYPT : SEV_CMD_DBG_DECRYPT,
			     &data, error);
पूर्ण

अटल पूर्णांक __sev_dbg_decrypt(काष्ठा kvm *kvm, अचिन्हित दीर्घ src_paddr,
			     अचिन्हित दीर्घ dst_paddr, पूर्णांक sz, पूर्णांक *err)
अणु
	पूर्णांक offset;

	/*
	 * Its safe to पढ़ो more than we are asked, caller should ensure that
	 * destination has enough space.
	 */
	offset = src_paddr & 15;
	src_paddr = round_करोwn(src_paddr, 16);
	sz = round_up(sz + offset, 16);

	वापस __sev_issue_dbg_cmd(kvm, src_paddr, dst_paddr, sz, err, false);
पूर्ण

अटल पूर्णांक __sev_dbg_decrypt_user(काष्ठा kvm *kvm, अचिन्हित दीर्घ paddr,
				  व्योम __user *dst_uaddr,
				  अचिन्हित दीर्घ dst_paddr,
				  पूर्णांक size, पूर्णांक *err)
अणु
	काष्ठा page *tpage = शून्य;
	पूर्णांक ret, offset;

	/* अगर inमाला_दो are not 16-byte then use पूर्णांकermediate buffer */
	अगर (!IS_ALIGNED(dst_paddr, 16) ||
	    !IS_ALIGNED(paddr,     16) ||
	    !IS_ALIGNED(size,      16)) अणु
		tpage = (व्योम *)alloc_page(GFP_KERNEL);
		अगर (!tpage)
			वापस -ENOMEM;

		dst_paddr = __sme_page_pa(tpage);
	पूर्ण

	ret = __sev_dbg_decrypt(kvm, paddr, dst_paddr, size, err);
	अगर (ret)
		जाओ e_मुक्त;

	अगर (tpage) अणु
		offset = paddr & 15;
		अगर (copy_to_user(dst_uaddr, page_address(tpage) + offset, size))
			ret = -EFAULT;
	पूर्ण

e_मुक्त:
	अगर (tpage)
		__मुक्त_page(tpage);

	वापस ret;
पूर्ण

अटल पूर्णांक __sev_dbg_encrypt_user(काष्ठा kvm *kvm, अचिन्हित दीर्घ paddr,
				  व्योम __user *vaddr,
				  अचिन्हित दीर्घ dst_paddr,
				  व्योम __user *dst_vaddr,
				  पूर्णांक size, पूर्णांक *error)
अणु
	काष्ठा page *src_tpage = शून्य;
	काष्ठा page *dst_tpage = शून्य;
	पूर्णांक ret, len = size;

	/* If source buffer is not aligned then use an पूर्णांकermediate buffer */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)vaddr, 16)) अणु
		src_tpage = alloc_page(GFP_KERNEL);
		अगर (!src_tpage)
			वापस -ENOMEM;

		अगर (copy_from_user(page_address(src_tpage), vaddr, size)) अणु
			__मुक्त_page(src_tpage);
			वापस -EFAULT;
		पूर्ण

		paddr = __sme_page_pa(src_tpage);
	पूर्ण

	/*
	 *  If destination buffer or length is not aligned then करो पढ़ो-modअगरy-ग_लिखो:
	 *   - decrypt destination in an पूर्णांकermediate buffer
	 *   - copy the source buffer in an पूर्णांकermediate buffer
	 *   - use the पूर्णांकermediate buffer as source buffer
	 */
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)dst_vaddr, 16) || !IS_ALIGNED(size, 16)) अणु
		पूर्णांक dst_offset;

		dst_tpage = alloc_page(GFP_KERNEL);
		अगर (!dst_tpage) अणु
			ret = -ENOMEM;
			जाओ e_मुक्त;
		पूर्ण

		ret = __sev_dbg_decrypt(kvm, dst_paddr,
					__sme_page_pa(dst_tpage), size, error);
		अगर (ret)
			जाओ e_मुक्त;

		/*
		 *  If source is kernel buffer then use स_नकल() otherwise
		 *  copy_from_user().
		 */
		dst_offset = dst_paddr & 15;

		अगर (src_tpage)
			स_नकल(page_address(dst_tpage) + dst_offset,
			       page_address(src_tpage), size);
		अन्यथा अणु
			अगर (copy_from_user(page_address(dst_tpage) + dst_offset,
					   vaddr, size)) अणु
				ret = -EFAULT;
				जाओ e_मुक्त;
			पूर्ण
		पूर्ण

		paddr = __sme_page_pa(dst_tpage);
		dst_paddr = round_करोwn(dst_paddr, 16);
		len = round_up(size, 16);
	पूर्ण

	ret = __sev_issue_dbg_cmd(kvm, paddr, dst_paddr, len, error, true);

e_मुक्त:
	अगर (src_tpage)
		__मुक्त_page(src_tpage);
	अगर (dst_tpage)
		__मुक्त_page(dst_tpage);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_dbg_crypt(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp, bool dec)
अणु
	अचिन्हित दीर्घ vaddr, vaddr_end, next_vaddr;
	अचिन्हित दीर्घ dst_vaddr;
	काष्ठा page **src_p, **dst_p;
	काष्ठा kvm_sev_dbg debug;
	अचिन्हित दीर्घ n;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&debug, (व्योम __user *)(uपूर्णांकptr_t)argp->data, माप(debug)))
		वापस -EFAULT;

	अगर (!debug.len || debug.src_uaddr + debug.len < debug.src_uaddr)
		वापस -EINVAL;
	अगर (!debug.dst_uaddr)
		वापस -EINVAL;

	vaddr = debug.src_uaddr;
	size = debug.len;
	vaddr_end = vaddr + size;
	dst_vaddr = debug.dst_uaddr;

	क्रम (; vaddr < vaddr_end; vaddr = next_vaddr) अणु
		पूर्णांक len, s_off, d_off;

		/* lock userspace source and destination page */
		src_p = sev_pin_memory(kvm, vaddr & PAGE_MASK, PAGE_SIZE, &n, 0);
		अगर (IS_ERR(src_p))
			वापस PTR_ERR(src_p);

		dst_p = sev_pin_memory(kvm, dst_vaddr & PAGE_MASK, PAGE_SIZE, &n, 1);
		अगर (IS_ERR(dst_p)) अणु
			sev_unpin_memory(kvm, src_p, n);
			वापस PTR_ERR(dst_p);
		पूर्ण

		/*
		 * Flush (on non-coherent CPUs) beक्रमe DBG_अणुDE,ENपूर्णCRYPT पढ़ो or modअगरy
		 * the pages; flush the destination too so that future accesses करो not
		 * see stale data.
		 */
		sev_clflush_pages(src_p, 1);
		sev_clflush_pages(dst_p, 1);

		/*
		 * Since user buffer may not be page aligned, calculate the
		 * offset within the page.
		 */
		s_off = vaddr & ~PAGE_MASK;
		d_off = dst_vaddr & ~PAGE_MASK;
		len = min_t(माप_प्रकार, (PAGE_SIZE - s_off), size);

		अगर (dec)
			ret = __sev_dbg_decrypt_user(kvm,
						     __sme_page_pa(src_p[0]) + s_off,
						     (व्योम __user *)dst_vaddr,
						     __sme_page_pa(dst_p[0]) + d_off,
						     len, &argp->error);
		अन्यथा
			ret = __sev_dbg_encrypt_user(kvm,
						     __sme_page_pa(src_p[0]) + s_off,
						     (व्योम __user *)vaddr,
						     __sme_page_pa(dst_p[0]) + d_off,
						     (व्योम __user *)dst_vaddr,
						     len, &argp->error);

		sev_unpin_memory(kvm, src_p, n);
		sev_unpin_memory(kvm, dst_p, n);

		अगर (ret)
			जाओ err;

		next_vaddr = vaddr + len;
		dst_vaddr = dst_vaddr + len;
		size -= len;
	पूर्ण
err:
	वापस ret;
पूर्ण

अटल पूर्णांक sev_launch_secret(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_launch_secret data;
	काष्ठा kvm_sev_launch_secret params;
	काष्ठा page **pages;
	व्योम *blob, *hdr;
	अचिन्हित दीर्घ n, i;
	पूर्णांक ret, offset;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data, माप(params)))
		वापस -EFAULT;

	pages = sev_pin_memory(kvm, params.guest_uaddr, params.guest_len, &n, 1);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	/*
	 * Flush (on non-coherent CPUs) beक्रमe LAUNCH_SECRET encrypts pages in
	 * place; the cache may contain the data that was written unencrypted.
	 */
	sev_clflush_pages(pages, n);

	/*
	 * The secret must be copied पूर्णांकo contiguous memory region, lets verअगरy
	 * that userspace memory pages are contiguous beक्रमe we issue command.
	 */
	अगर (get_num_contig_pages(0, pages, n) != n) अणु
		ret = -EINVAL;
		जाओ e_unpin_memory;
	पूर्ण

	स_रखो(&data, 0, माप(data));

	offset = params.guest_uaddr & (PAGE_SIZE - 1);
	data.guest_address = __sme_page_pa(pages[0]) + offset;
	data.guest_len = params.guest_len;

	blob = psp_copy_user_blob(params.trans_uaddr, params.trans_len);
	अगर (IS_ERR(blob)) अणु
		ret = PTR_ERR(blob);
		जाओ e_unpin_memory;
	पूर्ण

	data.trans_address = __psp_pa(blob);
	data.trans_len = params.trans_len;

	hdr = psp_copy_user_blob(params.hdr_uaddr, params.hdr_len);
	अगर (IS_ERR(hdr)) अणु
		ret = PTR_ERR(hdr);
		जाओ e_मुक्त_blob;
	पूर्ण
	data.hdr_address = __psp_pa(hdr);
	data.hdr_len = params.hdr_len;

	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_LAUNCH_UPDATE_SECRET, &data, &argp->error);

	kमुक्त(hdr);

e_मुक्त_blob:
	kमुक्त(blob);
e_unpin_memory:
	/* content of memory is updated, mark pages dirty */
	क्रम (i = 0; i < n; i++) अणु
		set_page_dirty_lock(pages[i]);
		mark_page_accessed(pages[i]);
	पूर्ण
	sev_unpin_memory(kvm, pages, n);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_get_attestation_report(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	व्योम __user *report = (व्योम __user *)(uपूर्णांकptr_t)argp->data;
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_attestation_report data;
	काष्ठा kvm_sev_attestation_report params;
	व्योम __user *p;
	व्योम *blob = शून्य;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data, माप(params)))
		वापस -EFAULT;

	स_रखो(&data, 0, माप(data));

	/* User wants to query the blob length */
	अगर (!params.len)
		जाओ cmd;

	p = (व्योम __user *)(uपूर्णांकptr_t)params.uaddr;
	अगर (p) अणु
		अगर (params.len > SEV_FW_BLOB_MAX_SIZE)
			वापस -EINVAL;

		blob = kदो_स्मृति(params.len, GFP_KERNEL_ACCOUNT);
		अगर (!blob)
			वापस -ENOMEM;

		data.address = __psp_pa(blob);
		data.len = params.len;
		स_नकल(data.mnonce, params.mnonce, माप(params.mnonce));
	पूर्ण
cmd:
	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_ATTESTATION_REPORT, &data, &argp->error);
	/*
	 * If we query the session length, FW responded with expected data.
	 */
	अगर (!params.len)
		जाओ करोne;

	अगर (ret)
		जाओ e_मुक्त_blob;

	अगर (blob) अणु
		अगर (copy_to_user(p, blob, params.len))
			ret = -EFAULT;
	पूर्ण

करोne:
	params.len = data.len;
	अगर (copy_to_user(report, &params, माप(params)))
		ret = -EFAULT;
e_मुक्त_blob:
	kमुक्त(blob);
	वापस ret;
पूर्ण

/* Userspace wants to query session length. */
अटल पूर्णांक
__sev_send_start_query_session_length(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp,
				      काष्ठा kvm_sev_send_start *params)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_start data;
	पूर्णांक ret;

	स_रखो(&data, 0, माप(data));
	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_SEND_START, &data, &argp->error);

	params->session_len = data.session_len;
	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data, params,
				माप(काष्ठा kvm_sev_send_start)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक sev_send_start(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_start data;
	काष्ठा kvm_sev_send_start params;
	व्योम *amd_certs, *session_data;
	व्योम *pdh_cert, *plat_certs;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data,
				माप(काष्ठा kvm_sev_send_start)))
		वापस -EFAULT;

	/* अगर session_len is zero, userspace wants to query the session length */
	अगर (!params.session_len)
		वापस __sev_send_start_query_session_length(kvm, argp,
				&params);

	/* some sanity checks */
	अगर (!params.pdh_cert_uaddr || !params.pdh_cert_len ||
	    !params.session_uaddr || params.session_len > SEV_FW_BLOB_MAX_SIZE)
		वापस -EINVAL;

	/* allocate the memory to hold the session data blob */
	session_data = kदो_स्मृति(params.session_len, GFP_KERNEL_ACCOUNT);
	अगर (!session_data)
		वापस -ENOMEM;

	/* copy the certअगरicate blobs from userspace */
	pdh_cert = psp_copy_user_blob(params.pdh_cert_uaddr,
				params.pdh_cert_len);
	अगर (IS_ERR(pdh_cert)) अणु
		ret = PTR_ERR(pdh_cert);
		जाओ e_मुक्त_session;
	पूर्ण

	plat_certs = psp_copy_user_blob(params.plat_certs_uaddr,
				params.plat_certs_len);
	अगर (IS_ERR(plat_certs)) अणु
		ret = PTR_ERR(plat_certs);
		जाओ e_मुक्त_pdh;
	पूर्ण

	amd_certs = psp_copy_user_blob(params.amd_certs_uaddr,
				params.amd_certs_len);
	अगर (IS_ERR(amd_certs)) अणु
		ret = PTR_ERR(amd_certs);
		जाओ e_मुक्त_plat_cert;
	पूर्ण

	/* populate the FW SEND_START field with प्रणाली physical address */
	स_रखो(&data, 0, माप(data));
	data.pdh_cert_address = __psp_pa(pdh_cert);
	data.pdh_cert_len = params.pdh_cert_len;
	data.plat_certs_address = __psp_pa(plat_certs);
	data.plat_certs_len = params.plat_certs_len;
	data.amd_certs_address = __psp_pa(amd_certs);
	data.amd_certs_len = params.amd_certs_len;
	data.session_address = __psp_pa(session_data);
	data.session_len = params.session_len;
	data.handle = sev->handle;

	ret = sev_issue_cmd(kvm, SEV_CMD_SEND_START, &data, &argp->error);

	अगर (!ret && copy_to_user((व्योम __user *)(uपूर्णांकptr_t)params.session_uaddr,
			session_data, params.session_len)) अणु
		ret = -EFAULT;
		जाओ e_मुक्त_amd_cert;
	पूर्ण

	params.policy = data.policy;
	params.session_len = data.session_len;
	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data, &params,
				माप(काष्ठा kvm_sev_send_start)))
		ret = -EFAULT;

e_मुक्त_amd_cert:
	kमुक्त(amd_certs);
e_मुक्त_plat_cert:
	kमुक्त(plat_certs);
e_मुक्त_pdh:
	kमुक्त(pdh_cert);
e_मुक्त_session:
	kमुक्त(session_data);
	वापस ret;
पूर्ण

/* Userspace wants to query either header or trans length. */
अटल पूर्णांक
__sev_send_update_data_query_lengths(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp,
				     काष्ठा kvm_sev_send_update_data *params)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_update_data data;
	पूर्णांक ret;

	स_रखो(&data, 0, माप(data));
	data.handle = sev->handle;
	ret = sev_issue_cmd(kvm, SEV_CMD_SEND_UPDATE_DATA, &data, &argp->error);

	params->hdr_len = data.hdr_len;
	params->trans_len = data.trans_len;

	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data, params,
			 माप(काष्ठा kvm_sev_send_update_data)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक sev_send_update_data(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_update_data data;
	काष्ठा kvm_sev_send_update_data params;
	व्योम *hdr, *trans_data;
	काष्ठा page **guest_page;
	अचिन्हित दीर्घ n;
	पूर्णांक ret, offset;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data,
			माप(काष्ठा kvm_sev_send_update_data)))
		वापस -EFAULT;

	/* userspace wants to query either header or trans length */
	अगर (!params.trans_len || !params.hdr_len)
		वापस __sev_send_update_data_query_lengths(kvm, argp, &params);

	अगर (!params.trans_uaddr || !params.guest_uaddr ||
	    !params.guest_len || !params.hdr_uaddr)
		वापस -EINVAL;

	/* Check अगर we are crossing the page boundary */
	offset = params.guest_uaddr & (PAGE_SIZE - 1);
	अगर ((params.guest_len + offset > PAGE_SIZE))
		वापस -EINVAL;

	/* Pin guest memory */
	guest_page = sev_pin_memory(kvm, params.guest_uaddr & PAGE_MASK,
				    PAGE_SIZE, &n, 0);
	अगर (!guest_page)
		वापस -EFAULT;

	/* allocate memory क्रम header and transport buffer */
	ret = -ENOMEM;
	hdr = kदो_स्मृति(params.hdr_len, GFP_KERNEL_ACCOUNT);
	अगर (!hdr)
		जाओ e_unpin;

	trans_data = kदो_स्मृति(params.trans_len, GFP_KERNEL_ACCOUNT);
	अगर (!trans_data)
		जाओ e_मुक्त_hdr;

	स_रखो(&data, 0, माप(data));
	data.hdr_address = __psp_pa(hdr);
	data.hdr_len = params.hdr_len;
	data.trans_address = __psp_pa(trans_data);
	data.trans_len = params.trans_len;

	/* The SEND_UPDATE_DATA command requires C-bit to be always set. */
	data.guest_address = (page_to_pfn(guest_page[0]) << PAGE_SHIFT) + offset;
	data.guest_address |= sev_me_mask;
	data.guest_len = params.guest_len;
	data.handle = sev->handle;

	ret = sev_issue_cmd(kvm, SEV_CMD_SEND_UPDATE_DATA, &data, &argp->error);

	अगर (ret)
		जाओ e_मुक्त_trans_data;

	/* copy transport buffer to user space */
	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)params.trans_uaddr,
			 trans_data, params.trans_len)) अणु
		ret = -EFAULT;
		जाओ e_मुक्त_trans_data;
	पूर्ण

	/* Copy packet header to userspace. */
	ret = copy_to_user((व्योम __user *)(uपूर्णांकptr_t)params.hdr_uaddr, hdr,
				params.hdr_len);

e_मुक्त_trans_data:
	kमुक्त(trans_data);
e_मुक्त_hdr:
	kमुक्त(hdr);
e_unpin:
	sev_unpin_memory(kvm, guest_page, n);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_send_finish(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_finish data;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	data.handle = sev->handle;
	वापस sev_issue_cmd(kvm, SEV_CMD_SEND_FINISH, &data, &argp->error);
पूर्ण

अटल पूर्णांक sev_send_cancel(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_send_cancel data;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	data.handle = sev->handle;
	वापस sev_issue_cmd(kvm, SEV_CMD_SEND_CANCEL, &data, &argp->error);
पूर्ण

अटल पूर्णांक sev_receive_start(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_receive_start start;
	काष्ठा kvm_sev_receive_start params;
	पूर्णांक *error = &argp->error;
	व्योम *session_data;
	व्योम *pdh_data;
	पूर्णांक ret;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	/* Get parameter from the userspace */
	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data,
			माप(काष्ठा kvm_sev_receive_start)))
		वापस -EFAULT;

	/* some sanity checks */
	अगर (!params.pdh_uaddr || !params.pdh_len ||
	    !params.session_uaddr || !params.session_len)
		वापस -EINVAL;

	pdh_data = psp_copy_user_blob(params.pdh_uaddr, params.pdh_len);
	अगर (IS_ERR(pdh_data))
		वापस PTR_ERR(pdh_data);

	session_data = psp_copy_user_blob(params.session_uaddr,
			params.session_len);
	अगर (IS_ERR(session_data)) अणु
		ret = PTR_ERR(session_data);
		जाओ e_मुक्त_pdh;
	पूर्ण

	स_रखो(&start, 0, माप(start));
	start.handle = params.handle;
	start.policy = params.policy;
	start.pdh_cert_address = __psp_pa(pdh_data);
	start.pdh_cert_len = params.pdh_len;
	start.session_address = __psp_pa(session_data);
	start.session_len = params.session_len;

	/* create memory encryption context */
	ret = __sev_issue_cmd(argp->sev_fd, SEV_CMD_RECEIVE_START, &start,
				error);
	अगर (ret)
		जाओ e_मुक्त_session;

	/* Bind ASID to this guest */
	ret = sev_bind_asid(kvm, start.handle, error);
	अगर (ret)
		जाओ e_मुक्त_session;

	params.handle = start.handle;
	अगर (copy_to_user((व्योम __user *)(uपूर्णांकptr_t)argp->data,
			 &params, माप(काष्ठा kvm_sev_receive_start))) अणु
		ret = -EFAULT;
		sev_unbind_asid(kvm, start.handle);
		जाओ e_मुक्त_session;
	पूर्ण

    	sev->handle = start.handle;
	sev->fd = argp->sev_fd;

e_मुक्त_session:
	kमुक्त(session_data);
e_मुक्त_pdh:
	kमुक्त(pdh_data);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_receive_update_data(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा kvm_sev_receive_update_data params;
	काष्ठा sev_data_receive_update_data data;
	व्योम *hdr = शून्य, *trans = शून्य;
	काष्ठा page **guest_page;
	अचिन्हित दीर्घ n;
	पूर्णांक ret, offset;

	अगर (!sev_guest(kvm))
		वापस -EINVAL;

	अगर (copy_from_user(&params, (व्योम __user *)(uपूर्णांकptr_t)argp->data,
			माप(काष्ठा kvm_sev_receive_update_data)))
		वापस -EFAULT;

	अगर (!params.hdr_uaddr || !params.hdr_len ||
	    !params.guest_uaddr || !params.guest_len ||
	    !params.trans_uaddr || !params.trans_len)
		वापस -EINVAL;

	/* Check अगर we are crossing the page boundary */
	offset = params.guest_uaddr & (PAGE_SIZE - 1);
	अगर ((params.guest_len + offset > PAGE_SIZE))
		वापस -EINVAL;

	hdr = psp_copy_user_blob(params.hdr_uaddr, params.hdr_len);
	अगर (IS_ERR(hdr))
		वापस PTR_ERR(hdr);

	trans = psp_copy_user_blob(params.trans_uaddr, params.trans_len);
	अगर (IS_ERR(trans)) अणु
		ret = PTR_ERR(trans);
		जाओ e_मुक्त_hdr;
	पूर्ण

	स_रखो(&data, 0, माप(data));
	data.hdr_address = __psp_pa(hdr);
	data.hdr_len = params.hdr_len;
	data.trans_address = __psp_pa(trans);
	data.trans_len = params.trans_len;

	/* Pin guest memory */
	ret = -EFAULT;
	guest_page = sev_pin_memory(kvm, params.guest_uaddr & PAGE_MASK,
				    PAGE_SIZE, &n, 0);
	अगर (!guest_page)
		जाओ e_मुक्त_trans;

	/* The RECEIVE_UPDATE_DATA command requires C-bit to be always set. */
	data.guest_address = (page_to_pfn(guest_page[0]) << PAGE_SHIFT) + offset;
	data.guest_address |= sev_me_mask;
	data.guest_len = params.guest_len;
	data.handle = sev->handle;

	ret = sev_issue_cmd(kvm, SEV_CMD_RECEIVE_UPDATE_DATA, &data,
				&argp->error);

	sev_unpin_memory(kvm, guest_page, n);

e_मुक्त_trans:
	kमुक्त(trans);
e_मुक्त_hdr:
	kमुक्त(hdr);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_receive_finish(काष्ठा kvm *kvm, काष्ठा kvm_sev_cmd *argp)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा sev_data_receive_finish data;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	data.handle = sev->handle;
	वापस sev_issue_cmd(kvm, SEV_CMD_RECEIVE_FINISH, &data, &argp->error);
पूर्ण

पूर्णांक svm_mem_enc_op(काष्ठा kvm *kvm, व्योम __user *argp)
अणु
	काष्ठा kvm_sev_cmd sev_cmd;
	पूर्णांक r;

	अगर (!sev_enabled)
		वापस -ENOTTY;

	अगर (!argp)
		वापस 0;

	अगर (copy_from_user(&sev_cmd, argp, माप(काष्ठा kvm_sev_cmd)))
		वापस -EFAULT;

	mutex_lock(&kvm->lock);

	/* enc_context_owner handles all memory enc operations */
	अगर (is_mirroring_enc_context(kvm)) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (sev_cmd.id) अणु
	हाल KVM_SEV_ES_INIT:
		अगर (!sev_es_enabled) अणु
			r = -ENOTTY;
			जाओ out;
		पूर्ण
		fallthrough;
	हाल KVM_SEV_INIT:
		r = sev_guest_init(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_LAUNCH_START:
		r = sev_launch_start(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_LAUNCH_UPDATE_DATA:
		r = sev_launch_update_data(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_LAUNCH_UPDATE_VMSA:
		r = sev_launch_update_vmsa(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_LAUNCH_MEASURE:
		r = sev_launch_measure(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_LAUNCH_FINISH:
		r = sev_launch_finish(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_GUEST_STATUS:
		r = sev_guest_status(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_DBG_DECRYPT:
		r = sev_dbg_crypt(kvm, &sev_cmd, true);
		अवरोध;
	हाल KVM_SEV_DBG_ENCRYPT:
		r = sev_dbg_crypt(kvm, &sev_cmd, false);
		अवरोध;
	हाल KVM_SEV_LAUNCH_SECRET:
		r = sev_launch_secret(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_GET_ATTESTATION_REPORT:
		r = sev_get_attestation_report(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_SEND_START:
		r = sev_send_start(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_SEND_UPDATE_DATA:
		r = sev_send_update_data(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_SEND_FINISH:
		r = sev_send_finish(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_SEND_CANCEL:
		r = sev_send_cancel(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_RECEIVE_START:
		r = sev_receive_start(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_RECEIVE_UPDATE_DATA:
		r = sev_receive_update_data(kvm, &sev_cmd);
		अवरोध;
	हाल KVM_SEV_RECEIVE_FINISH:
		r = sev_receive_finish(kvm, &sev_cmd);
		अवरोध;
	शेष:
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(argp, &sev_cmd, माप(काष्ठा kvm_sev_cmd)))
		r = -EFAULT;

out:
	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

पूर्णांक svm_रेजिस्टर_enc_region(काष्ठा kvm *kvm,
			    काष्ठा kvm_enc_region *range)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा enc_region *region;
	पूर्णांक ret = 0;

	अगर (!sev_guest(kvm))
		वापस -ENOTTY;

	/* If kvm is mirroring encryption context it isn't responsible क्रम it */
	अगर (is_mirroring_enc_context(kvm))
		वापस -EINVAL;

	अगर (range->addr > अच_दीर्घ_उच्च || range->size > अच_दीर्घ_उच्च)
		वापस -EINVAL;

	region = kzalloc(माप(*region), GFP_KERNEL_ACCOUNT);
	अगर (!region)
		वापस -ENOMEM;

	mutex_lock(&kvm->lock);
	region->pages = sev_pin_memory(kvm, range->addr, range->size, &region->npages, 1);
	अगर (IS_ERR(region->pages)) अणु
		ret = PTR_ERR(region->pages);
		mutex_unlock(&kvm->lock);
		जाओ e_मुक्त;
	पूर्ण

	region->uaddr = range->addr;
	region->size = range->size;

	list_add_tail(&region->list, &sev->regions_list);
	mutex_unlock(&kvm->lock);

	/*
	 * The guest may change the memory encryption attribute from C=0 -> C=1
	 * or vice versa क्रम this memory range. Lets make sure caches are
	 * flushed to ensure that guest data माला_लो written पूर्णांकo memory with
	 * correct C-bit.
	 */
	sev_clflush_pages(region->pages, region->npages);

	वापस ret;

e_मुक्त:
	kमुक्त(region);
	वापस ret;
पूर्ण

अटल काष्ठा enc_region *
find_enc_region(काष्ठा kvm *kvm, काष्ठा kvm_enc_region *range)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा list_head *head = &sev->regions_list;
	काष्ठा enc_region *i;

	list_क्रम_each_entry(i, head, list) अणु
		अगर (i->uaddr == range->addr &&
		    i->size == range->size)
			वापस i;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __unरेजिस्टर_enc_region_locked(काष्ठा kvm *kvm,
					   काष्ठा enc_region *region)
अणु
	sev_unpin_memory(kvm, region->pages, region->npages);
	list_del(&region->list);
	kमुक्त(region);
पूर्ण

पूर्णांक svm_unरेजिस्टर_enc_region(काष्ठा kvm *kvm,
			      काष्ठा kvm_enc_region *range)
अणु
	काष्ठा enc_region *region;
	पूर्णांक ret;

	/* If kvm is mirroring encryption context it isn't responsible क्रम it */
	अगर (is_mirroring_enc_context(kvm))
		वापस -EINVAL;

	mutex_lock(&kvm->lock);

	अगर (!sev_guest(kvm)) अणु
		ret = -ENOTTY;
		जाओ failed;
	पूर्ण

	region = find_enc_region(kvm, range);
	अगर (!region) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण

	/*
	 * Ensure that all guest tagged cache entries are flushed beक्रमe
	 * releasing the pages back to the प्रणाली क्रम use. CLFLUSH will
	 * not करो this, so issue a WBINVD.
	 */
	wbinvd_on_all_cpus();

	__unरेजिस्टर_enc_region_locked(kvm, region);

	mutex_unlock(&kvm->lock);
	वापस 0;

failed:
	mutex_unlock(&kvm->lock);
	वापस ret;
पूर्ण

पूर्णांक svm_vm_copy_asid_from(काष्ठा kvm *kvm, अचिन्हित पूर्णांक source_fd)
अणु
	काष्ठा file *source_kvm_file;
	काष्ठा kvm *source_kvm;
	काष्ठा kvm_sev_info *mirror_sev;
	अचिन्हित पूर्णांक asid;
	पूर्णांक ret;

	source_kvm_file = fget(source_fd);
	अगर (!file_is_kvm(source_kvm_file)) अणु
		ret = -EBADF;
		जाओ e_source_put;
	पूर्ण

	source_kvm = source_kvm_file->निजी_data;
	mutex_lock(&source_kvm->lock);

	अगर (!sev_guest(source_kvm)) अणु
		ret = -EINVAL;
		जाओ e_source_unlock;
	पूर्ण

	/* Mirrors of mirrors should work, but let's not get silly */
	अगर (is_mirroring_enc_context(source_kvm) || source_kvm == kvm) अणु
		ret = -EINVAL;
		जाओ e_source_unlock;
	पूर्ण

	asid = to_kvm_svm(source_kvm)->sev_info.asid;

	/*
	 * The mirror kvm holds an enc_context_owner ref so its asid can't
	 * disappear until we're करोne with it
	 */
	kvm_get_kvm(source_kvm);

	fput(source_kvm_file);
	mutex_unlock(&source_kvm->lock);
	mutex_lock(&kvm->lock);

	अगर (sev_guest(kvm)) अणु
		ret = -EINVAL;
		जाओ e_mirror_unlock;
	पूर्ण

	/* Set enc_context_owner and copy its encryption context over */
	mirror_sev = &to_kvm_svm(kvm)->sev_info;
	mirror_sev->enc_context_owner = source_kvm;
	mirror_sev->asid = asid;
	mirror_sev->active = true;

	mutex_unlock(&kvm->lock);
	वापस 0;

e_mirror_unlock:
	mutex_unlock(&kvm->lock);
	kvm_put_kvm(source_kvm);
	वापस ret;
e_source_unlock:
	mutex_unlock(&source_kvm->lock);
e_source_put:
	अगर (source_kvm_file)
		fput(source_kvm_file);
	वापस ret;
पूर्ण

व्योम sev_vm_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	काष्ठा list_head *head = &sev->regions_list;
	काष्ठा list_head *pos, *q;

	अगर (!sev_guest(kvm))
		वापस;

	/* If this is a mirror_kvm release the enc_context_owner and skip sev cleanup */
	अगर (is_mirroring_enc_context(kvm)) अणु
		kvm_put_kvm(sev->enc_context_owner);
		वापस;
	पूर्ण

	mutex_lock(&kvm->lock);

	/*
	 * Ensure that all guest tagged cache entries are flushed beक्रमe
	 * releasing the pages back to the प्रणाली क्रम use. CLFLUSH will
	 * not करो this, so issue a WBINVD.
	 */
	wbinvd_on_all_cpus();

	/*
	 * अगर userspace was terminated beक्रमe unरेजिस्टरing the memory regions
	 * then lets unpin all the रेजिस्टरed memory.
	 */
	अगर (!list_empty(head)) अणु
		list_क्रम_each_safe(pos, q, head) अणु
			__unरेजिस्टर_enc_region_locked(kvm,
				list_entry(pos, काष्ठा enc_region, list));
			cond_resched();
		पूर्ण
	पूर्ण

	mutex_unlock(&kvm->lock);

	sev_unbind_asid(kvm, sev->handle);
	sev_asid_मुक्त(sev);
पूर्ण

व्योम __init sev_set_cpu_caps(व्योम)
अणु
	अगर (!sev_enabled)
		kvm_cpu_cap_clear(X86_FEATURE_SEV);
	अगर (!sev_es_enabled)
		kvm_cpu_cap_clear(X86_FEATURE_SEV_ES);
पूर्ण

व्योम __init sev_hardware_setup(व्योम)
अणु
#अगर_घोषित CONFIG_KVM_AMD_SEV
	अचिन्हित पूर्णांक eax, ebx, ecx, edx, sev_asid_count, sev_es_asid_count;
	bool sev_es_supported = false;
	bool sev_supported = false;

	अगर (!sev_enabled || !npt_enabled)
		जाओ out;

	/* Does the CPU support SEV? */
	अगर (!boot_cpu_has(X86_FEATURE_SEV))
		जाओ out;

	/* Retrieve SEV CPUID inक्रमmation */
	cpuid(0x8000001f, &eax, &ebx, &ecx, &edx);

	/* Set encryption bit location क्रम SEV-ES guests */
	sev_enc_bit = ebx & 0x3f;

	/* Maximum number of encrypted guests supported simultaneously */
	max_sev_asid = ecx;
	अगर (!max_sev_asid)
		जाओ out;

	/* Minimum ASID value that should be used क्रम SEV guest */
	min_sev_asid = edx;
	sev_me_mask = 1UL << (ebx & 0x3f);

	/* Initialize SEV ASID biपंचांगaps */
	sev_asid_biपंचांगap = biपंचांगap_zalloc(max_sev_asid, GFP_KERNEL);
	अगर (!sev_asid_biपंचांगap)
		जाओ out;

	sev_reclaim_asid_biपंचांगap = biपंचांगap_zalloc(max_sev_asid, GFP_KERNEL);
	अगर (!sev_reclaim_asid_biपंचांगap) अणु
		biपंचांगap_मुक्त(sev_asid_biपंचांगap);
		sev_asid_biपंचांगap = शून्य;
		जाओ out;
	पूर्ण

	sev_asid_count = max_sev_asid - min_sev_asid + 1;
	अगर (misc_cg_set_capacity(MISC_CG_RES_SEV, sev_asid_count))
		जाओ out;

	pr_info("SEV supported: %u ASIDs\n", sev_asid_count);
	sev_supported = true;

	/* SEV-ES support requested? */
	अगर (!sev_es_enabled)
		जाओ out;

	/* Does the CPU support SEV-ES? */
	अगर (!boot_cpu_has(X86_FEATURE_SEV_ES))
		जाओ out;

	/* Has the प्रणाली been allocated ASIDs क्रम SEV-ES? */
	अगर (min_sev_asid == 1)
		जाओ out;

	sev_es_asid_count = min_sev_asid - 1;
	अगर (misc_cg_set_capacity(MISC_CG_RES_SEV_ES, sev_es_asid_count))
		जाओ out;

	pr_info("SEV-ES supported: %u ASIDs\n", sev_es_asid_count);
	sev_es_supported = true;

out:
	sev_enabled = sev_supported;
	sev_es_enabled = sev_es_supported;
#पूर्ण_अगर
पूर्ण

व्योम sev_hardware_tearकरोwn(व्योम)
अणु
	अगर (!sev_enabled)
		वापस;

	/* No need to take sev_biपंचांगap_lock, all VMs have been destroyed. */
	sev_flush_asids(0, max_sev_asid);

	biपंचांगap_मुक्त(sev_asid_biपंचांगap);
	biपंचांगap_मुक्त(sev_reclaim_asid_biपंचांगap);

	misc_cg_set_capacity(MISC_CG_RES_SEV, 0);
	misc_cg_set_capacity(MISC_CG_RES_SEV_ES, 0);
पूर्ण

पूर्णांक sev_cpu_init(काष्ठा svm_cpu_data *sd)
अणु
	अगर (!sev_enabled)
		वापस 0;

	sd->sev_vmcbs = kसुस्मृति(max_sev_asid + 1, माप(व्योम *), GFP_KERNEL);
	अगर (!sd->sev_vmcbs)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * Pages used by hardware to hold guest encrypted state must be flushed beक्रमe
 * वापसing them to the प्रणाली.
 */
अटल व्योम sev_flush_guest_memory(काष्ठा vcpu_svm *svm, व्योम *va,
				   अचिन्हित दीर्घ len)
अणु
	/*
	 * If hardware enक्रमced cache coherency क्रम encrypted mappings of the
	 * same physical page is supported, nothing to करो.
	 */
	अगर (boot_cpu_has(X86_FEATURE_SME_COHERENT))
		वापस;

	/*
	 * If the VM Page Flush MSR is supported, use it to flush the page
	 * (using the page भव address and the guest ASID).
	 */
	अगर (boot_cpu_has(X86_FEATURE_VM_PAGE_FLUSH)) अणु
		काष्ठा kvm_sev_info *sev;
		अचिन्हित दीर्घ बहु_शुरू;
		u64 start, stop;

		/* Align start and stop to page boundaries. */
		बहु_शुरू = (अचिन्हित दीर्घ)va;
		start = (u64)बहु_शुरू & PAGE_MASK;
		stop = PAGE_ALIGN((u64)बहु_शुरू + len);

		अगर (start < stop) अणु
			sev = &to_kvm_svm(svm->vcpu.kvm)->sev_info;

			जबतक (start < stop) अणु
				wrmsrl(MSR_AMD64_VM_PAGE_FLUSH,
				       start | sev->asid);

				start += PAGE_SIZE;
			पूर्ण

			वापस;
		पूर्ण

		WARN(1, "Address overflow, using WBINVD\n");
	पूर्ण

	/*
	 * Hardware should always have one of the above features,
	 * but अगर not, use WBINVD and issue a warning.
	 */
	WARN_ONCE(1, "Using WBINVD to flush guest memory\n");
	wbinvd_on_all_cpus();
पूर्ण

व्योम sev_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm;

	अगर (!sev_es_guest(vcpu->kvm))
		वापस;

	svm = to_svm(vcpu);

	अगर (vcpu->arch.guest_state_रक्षित)
		sev_flush_guest_memory(svm, svm->vmsa, PAGE_SIZE);
	__मुक्त_page(virt_to_page(svm->vmsa));

	अगर (svm->ghcb_sa_मुक्त)
		kमुक्त(svm->ghcb_sa);
पूर्ण

अटल व्योम dump_ghcb(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा ghcb *ghcb = svm->ghcb;
	अचिन्हित पूर्णांक nbits;

	/* Re-use the dump_invalid_vmcb module parameter */
	अगर (!dump_invalid_vmcb) अणु
		pr_warn_ratelimited("set kvm_amd.dump_invalid_vmcb=1 to dump internal KVM state.\n");
		वापस;
	पूर्ण

	nbits = माप(ghcb->save.valid_biपंचांगap) * 8;

	pr_err("GHCB (GPA=%016llx):\n", svm->vmcb->control.ghcb_gpa);
	pr_err("%-20s%016llx is_valid: %u\n", "sw_exit_code",
	       ghcb->save.sw_निकास_code, ghcb_sw_निकास_code_is_valid(ghcb));
	pr_err("%-20s%016llx is_valid: %u\n", "sw_exit_info_1",
	       ghcb->save.sw_निकास_info_1, ghcb_sw_निकास_info_1_is_valid(ghcb));
	pr_err("%-20s%016llx is_valid: %u\n", "sw_exit_info_2",
	       ghcb->save.sw_निकास_info_2, ghcb_sw_निकास_info_2_is_valid(ghcb));
	pr_err("%-20s%016llx is_valid: %u\n", "sw_scratch",
	       ghcb->save.sw_scratch, ghcb_sw_scratch_is_valid(ghcb));
	pr_err("%-20s%*pb\n", "valid_bitmap", nbits, ghcb->save.valid_biपंचांगap);
पूर्ण

अटल व्योम sev_es_sync_to_ghcb(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;
	काष्ठा ghcb *ghcb = svm->ghcb;

	/*
	 * The GHCB protocol so far allows क्रम the following data
	 * to be वापसed:
	 *   GPRs RAX, RBX, RCX, RDX
	 *
	 * Copy their values, even अगर they may not have been written during the
	 * VM-Exit.  It's the guest's responsibility to not consume अक्रमom data.
	 */
	ghcb_set_rax(ghcb, vcpu->arch.regs[VCPU_REGS_RAX]);
	ghcb_set_rbx(ghcb, vcpu->arch.regs[VCPU_REGS_RBX]);
	ghcb_set_rcx(ghcb, vcpu->arch.regs[VCPU_REGS_RCX]);
	ghcb_set_rdx(ghcb, vcpu->arch.regs[VCPU_REGS_RDX]);
पूर्ण

अटल व्योम sev_es_sync_from_ghcb(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;
	काष्ठा ghcb *ghcb = svm->ghcb;
	u64 निकास_code;

	/*
	 * The GHCB protocol so far allows क्रम the following data
	 * to be supplied:
	 *   GPRs RAX, RBX, RCX, RDX
	 *   XCR0
	 *   CPL
	 *
	 * VMMCALL allows the guest to provide extra रेजिस्टरs. KVM also
	 * expects RSI क्रम hypercalls, so include that, too.
	 *
	 * Copy their values to the appropriate location अगर supplied.
	 */
	स_रखो(vcpu->arch.regs, 0, माप(vcpu->arch.regs));

	vcpu->arch.regs[VCPU_REGS_RAX] = ghcb_get_rax_अगर_valid(ghcb);
	vcpu->arch.regs[VCPU_REGS_RBX] = ghcb_get_rbx_अगर_valid(ghcb);
	vcpu->arch.regs[VCPU_REGS_RCX] = ghcb_get_rcx_अगर_valid(ghcb);
	vcpu->arch.regs[VCPU_REGS_RDX] = ghcb_get_rdx_अगर_valid(ghcb);
	vcpu->arch.regs[VCPU_REGS_RSI] = ghcb_get_rsi_अगर_valid(ghcb);

	svm->vmcb->save.cpl = ghcb_get_cpl_अगर_valid(ghcb);

	अगर (ghcb_xcr0_is_valid(ghcb)) अणु
		vcpu->arch.xcr0 = ghcb_get_xcr0(ghcb);
		kvm_update_cpuid_runसमय(vcpu);
	पूर्ण

	/* Copy the GHCB निकास inक्रमmation पूर्णांकo the VMCB fields */
	निकास_code = ghcb_get_sw_निकास_code(ghcb);
	control->निकास_code = lower_32_bits(निकास_code);
	control->निकास_code_hi = upper_32_bits(निकास_code);
	control->निकास_info_1 = ghcb_get_sw_निकास_info_1(ghcb);
	control->निकास_info_2 = ghcb_get_sw_निकास_info_2(ghcb);

	/* Clear the valid entries fields */
	स_रखो(ghcb->save.valid_biपंचांगap, 0, माप(ghcb->save.valid_biपंचांगap));
पूर्ण

अटल पूर्णांक sev_es_validate_vmgनिकास(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_vcpu *vcpu;
	काष्ठा ghcb *ghcb;
	u64 निकास_code = 0;

	ghcb = svm->ghcb;

	/* Only GHCB Usage code 0 is supported */
	अगर (ghcb->ghcb_usage)
		जाओ vmgनिकास_err;

	/*
	 * Retrieve the निकास code now even though is may not be marked valid
	 * as it could help with debugging.
	 */
	निकास_code = ghcb_get_sw_निकास_code(ghcb);

	अगर (!ghcb_sw_निकास_code_is_valid(ghcb) ||
	    !ghcb_sw_निकास_info_1_is_valid(ghcb) ||
	    !ghcb_sw_निकास_info_2_is_valid(ghcb))
		जाओ vmgनिकास_err;

	चयन (ghcb_get_sw_निकास_code(ghcb)) अणु
	हाल SVM_EXIT_READ_DR7:
		अवरोध;
	हाल SVM_EXIT_WRITE_DR7:
		अगर (!ghcb_rax_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_EXIT_RDTSC:
		अवरोध;
	हाल SVM_EXIT_RDPMC:
		अगर (!ghcb_rcx_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_EXIT_CPUID:
		अगर (!ghcb_rax_is_valid(ghcb) ||
		    !ghcb_rcx_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अगर (ghcb_get_rax(ghcb) == 0xd)
			अगर (!ghcb_xcr0_is_valid(ghcb))
				जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_EXIT_INVD:
		अवरोध;
	हाल SVM_EXIT_IOIO:
		अगर (ghcb_get_sw_निकास_info_1(ghcb) & SVM_IOIO_STR_MASK) अणु
			अगर (!ghcb_sw_scratch_is_valid(ghcb))
				जाओ vmgनिकास_err;
		पूर्ण अन्यथा अणु
			अगर (!(ghcb_get_sw_निकास_info_1(ghcb) & SVM_IOIO_TYPE_MASK))
				अगर (!ghcb_rax_is_valid(ghcb))
					जाओ vmgनिकास_err;
		पूर्ण
		अवरोध;
	हाल SVM_EXIT_MSR:
		अगर (!ghcb_rcx_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अगर (ghcb_get_sw_निकास_info_1(ghcb)) अणु
			अगर (!ghcb_rax_is_valid(ghcb) ||
			    !ghcb_rdx_is_valid(ghcb))
				जाओ vmgनिकास_err;
		पूर्ण
		अवरोध;
	हाल SVM_EXIT_VMMCALL:
		अगर (!ghcb_rax_is_valid(ghcb) ||
		    !ghcb_cpl_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_EXIT_RDTSCP:
		अवरोध;
	हाल SVM_EXIT_WBINVD:
		अवरोध;
	हाल SVM_EXIT_MONITOR:
		अगर (!ghcb_rax_is_valid(ghcb) ||
		    !ghcb_rcx_is_valid(ghcb) ||
		    !ghcb_rdx_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_EXIT_MWAIT:
		अगर (!ghcb_rax_is_valid(ghcb) ||
		    !ghcb_rcx_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_VMGEXIT_MMIO_READ:
	हाल SVM_VMGEXIT_MMIO_WRITE:
		अगर (!ghcb_sw_scratch_is_valid(ghcb))
			जाओ vmgनिकास_err;
		अवरोध;
	हाल SVM_VMGEXIT_NMI_COMPLETE:
	हाल SVM_VMGEXIT_AP_HLT_LOOP:
	हाल SVM_VMGEXIT_AP_JUMP_TABLE:
	हाल SVM_VMGEXIT_UNSUPPORTED_EVENT:
		अवरोध;
	शेष:
		जाओ vmgनिकास_err;
	पूर्ण

	वापस 0;

vmgनिकास_err:
	vcpu = &svm->vcpu;

	अगर (ghcb->ghcb_usage) अणु
		vcpu_unimpl(vcpu, "vmgexit: ghcb usage %#x is not valid\n",
			    ghcb->ghcb_usage);
	पूर्ण अन्यथा अणु
		vcpu_unimpl(vcpu, "vmgexit: exit reason %#llx is not valid\n",
			    निकास_code);
		dump_ghcb(svm);
	पूर्ण

	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_UNEXPECTED_EXIT_REASON;
	vcpu->run->पूर्णांकernal.ndata = 2;
	vcpu->run->पूर्णांकernal.data[0] = निकास_code;
	vcpu->run->पूर्णांकernal.data[1] = vcpu->arch.last_vmentry_cpu;

	वापस -EINVAL;
पूर्ण

व्योम sev_es_unmap_ghcb(काष्ठा vcpu_svm *svm)
अणु
	अगर (!svm->ghcb)
		वापस;

	अगर (svm->ghcb_sa_मुक्त) अणु
		/*
		 * The scratch area lives outside the GHCB, so there is a
		 * buffer that, depending on the operation perक्रमmed, may
		 * need to be synced, then मुक्तd.
		 */
		अगर (svm->ghcb_sa_sync) अणु
			kvm_ग_लिखो_guest(svm->vcpu.kvm,
					ghcb_get_sw_scratch(svm->ghcb),
					svm->ghcb_sa, svm->ghcb_sa_len);
			svm->ghcb_sa_sync = false;
		पूर्ण

		kमुक्त(svm->ghcb_sa);
		svm->ghcb_sa = शून्य;
		svm->ghcb_sa_मुक्त = false;
	पूर्ण

	trace_kvm_vmgनिकास_निकास(svm->vcpu.vcpu_id, svm->ghcb);

	sev_es_sync_to_ghcb(svm);

	kvm_vcpu_unmap(&svm->vcpu, &svm->ghcb_map, true);
	svm->ghcb = शून्य;
पूर्ण

व्योम pre_sev_run(काष्ठा vcpu_svm *svm, पूर्णांक cpu)
अणु
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, cpu);
	पूर्णांक asid = sev_get_asid(svm->vcpu.kvm);

	/* Assign the asid allocated with this SEV guest */
	svm->asid = asid;

	/*
	 * Flush guest TLB:
	 *
	 * 1) when dअगरferent VMCB क्रम the same ASID is to be run on the same host CPU.
	 * 2) or this VMCB was executed on dअगरferent host CPU in previous VMRUNs.
	 */
	अगर (sd->sev_vmcbs[asid] == svm->vmcb &&
	    svm->vcpu.arch.last_vmentry_cpu == cpu)
		वापस;

	sd->sev_vmcbs[asid] = svm->vmcb;
	svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ASID;
	vmcb_mark_dirty(svm->vmcb, VMCB_ASID);
पूर्ण

#घोषणा GHCB_SCRATCH_AREA_LIMIT		(16ULL * PAGE_SIZE)
अटल bool setup_vmgनिकास_scratch(काष्ठा vcpu_svm *svm, bool sync, u64 len)
अणु
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	काष्ठा ghcb *ghcb = svm->ghcb;
	u64 ghcb_scratch_beg, ghcb_scratch_end;
	u64 scratch_gpa_beg, scratch_gpa_end;
	व्योम *scratch_va;

	scratch_gpa_beg = ghcb_get_sw_scratch(ghcb);
	अगर (!scratch_gpa_beg) अणु
		pr_err("vmgexit: scratch gpa not provided\n");
		वापस false;
	पूर्ण

	scratch_gpa_end = scratch_gpa_beg + len;
	अगर (scratch_gpa_end < scratch_gpa_beg) अणु
		pr_err("vmgexit: scratch length (%#llx) not valid for scratch address (%#llx)\n",
		       len, scratch_gpa_beg);
		वापस false;
	पूर्ण

	अगर ((scratch_gpa_beg & PAGE_MASK) == control->ghcb_gpa) अणु
		/* Scratch area begins within GHCB */
		ghcb_scratch_beg = control->ghcb_gpa +
				   दुरत्व(काष्ठा ghcb, shared_buffer);
		ghcb_scratch_end = control->ghcb_gpa +
				   दुरत्व(काष्ठा ghcb, reserved_1);

		/*
		 * If the scratch area begins within the GHCB, it must be
		 * completely contained in the GHCB shared buffer area.
		 */
		अगर (scratch_gpa_beg < ghcb_scratch_beg ||
		    scratch_gpa_end > ghcb_scratch_end) अणु
			pr_err("vmgexit: scratch area is outside of GHCB shared buffer area (%#llx - %#llx)\n",
			       scratch_gpa_beg, scratch_gpa_end);
			वापस false;
		पूर्ण

		scratch_va = (व्योम *)svm->ghcb;
		scratch_va += (scratch_gpa_beg - control->ghcb_gpa);
	पूर्ण अन्यथा अणु
		/*
		 * The guest memory must be पढ़ो पूर्णांकo a kernel buffer, so
		 * limit the size
		 */
		अगर (len > GHCB_SCRATCH_AREA_LIMIT) अणु
			pr_err("vmgexit: scratch area exceeds KVM limits (%#llx requested, %#llx limit)\n",
			       len, GHCB_SCRATCH_AREA_LIMIT);
			वापस false;
		पूर्ण
		scratch_va = kzalloc(len, GFP_KERNEL_ACCOUNT);
		अगर (!scratch_va)
			वापस false;

		अगर (kvm_पढ़ो_guest(svm->vcpu.kvm, scratch_gpa_beg, scratch_va, len)) अणु
			/* Unable to copy scratch area from guest */
			pr_err("vmgexit: kvm_read_guest for scratch area failed\n");

			kमुक्त(scratch_va);
			वापस false;
		पूर्ण

		/*
		 * The scratch area is outside the GHCB. The operation will
		 * dictate whether the buffer needs to be synced beक्रमe running
		 * the vCPU next समय (i.e. a पढ़ो was requested so the data
		 * must be written back to the guest memory).
		 */
		svm->ghcb_sa_sync = sync;
		svm->ghcb_sa_मुक्त = true;
	पूर्ण

	svm->ghcb_sa = scratch_va;
	svm->ghcb_sa_len = len;

	वापस true;
पूर्ण

अटल व्योम set_ghcb_msr_bits(काष्ठा vcpu_svm *svm, u64 value, u64 mask,
			      अचिन्हित पूर्णांक pos)
अणु
	svm->vmcb->control.ghcb_gpa &= ~(mask << pos);
	svm->vmcb->control.ghcb_gpa |= (value & mask) << pos;
पूर्ण

अटल u64 get_ghcb_msr_bits(काष्ठा vcpu_svm *svm, u64 mask, अचिन्हित पूर्णांक pos)
अणु
	वापस (svm->vmcb->control.ghcb_gpa >> pos) & mask;
पूर्ण

अटल व्योम set_ghcb_msr(काष्ठा vcpu_svm *svm, u64 value)
अणु
	svm->vmcb->control.ghcb_gpa = value;
पूर्ण

अटल पूर्णांक sev_handle_vmgनिकास_msr_protocol(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;
	u64 ghcb_info;
	पूर्णांक ret = 1;

	ghcb_info = control->ghcb_gpa & GHCB_MSR_INFO_MASK;

	trace_kvm_vmgनिकास_msr_protocol_enter(svm->vcpu.vcpu_id,
					     control->ghcb_gpa);

	चयन (ghcb_info) अणु
	हाल GHCB_MSR_SEV_INFO_REQ:
		set_ghcb_msr(svm, GHCB_MSR_SEV_INFO(GHCB_VERSION_MAX,
						    GHCB_VERSION_MIN,
						    sev_enc_bit));
		अवरोध;
	हाल GHCB_MSR_CPUID_REQ: अणु
		u64 cpuid_fn, cpuid_reg, cpuid_value;

		cpuid_fn = get_ghcb_msr_bits(svm,
					     GHCB_MSR_CPUID_FUNC_MASK,
					     GHCB_MSR_CPUID_FUNC_POS);

		/* Initialize the रेजिस्टरs needed by the CPUID पूर्णांकercept */
		vcpu->arch.regs[VCPU_REGS_RAX] = cpuid_fn;
		vcpu->arch.regs[VCPU_REGS_RCX] = 0;

		ret = svm_invoke_निकास_handler(vcpu, SVM_EXIT_CPUID);
		अगर (!ret) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		cpuid_reg = get_ghcb_msr_bits(svm,
					      GHCB_MSR_CPUID_REG_MASK,
					      GHCB_MSR_CPUID_REG_POS);
		अगर (cpuid_reg == 0)
			cpuid_value = vcpu->arch.regs[VCPU_REGS_RAX];
		अन्यथा अगर (cpuid_reg == 1)
			cpuid_value = vcpu->arch.regs[VCPU_REGS_RBX];
		अन्यथा अगर (cpuid_reg == 2)
			cpuid_value = vcpu->arch.regs[VCPU_REGS_RCX];
		अन्यथा
			cpuid_value = vcpu->arch.regs[VCPU_REGS_RDX];

		set_ghcb_msr_bits(svm, cpuid_value,
				  GHCB_MSR_CPUID_VALUE_MASK,
				  GHCB_MSR_CPUID_VALUE_POS);

		set_ghcb_msr_bits(svm, GHCB_MSR_CPUID_RESP,
				  GHCB_MSR_INFO_MASK,
				  GHCB_MSR_INFO_POS);
		अवरोध;
	पूर्ण
	हाल GHCB_MSR_TERM_REQ: अणु
		u64 reason_set, reason_code;

		reason_set = get_ghcb_msr_bits(svm,
					       GHCB_MSR_TERM_REASON_SET_MASK,
					       GHCB_MSR_TERM_REASON_SET_POS);
		reason_code = get_ghcb_msr_bits(svm,
						GHCB_MSR_TERM_REASON_MASK,
						GHCB_MSR_TERM_REASON_POS);
		pr_info("SEV-ES guest requested termination: %#llx:%#llx\n",
			reason_set, reason_code);
		fallthrough;
	पूर्ण
	शेष:
		ret = -EINVAL;
	पूर्ण

	trace_kvm_vmgनिकास_msr_protocol_निकास(svm->vcpu.vcpu_id,
					    control->ghcb_gpa, ret);

	वापस ret;
पूर्ण

पूर्णांक sev_handle_vmgनिकास(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	u64 ghcb_gpa, निकास_code;
	काष्ठा ghcb *ghcb;
	पूर्णांक ret;

	/* Validate the GHCB */
	ghcb_gpa = control->ghcb_gpa;
	अगर (ghcb_gpa & GHCB_MSR_INFO_MASK)
		वापस sev_handle_vmgनिकास_msr_protocol(svm);

	अगर (!ghcb_gpa) अणु
		vcpu_unimpl(vcpu, "vmgexit: GHCB gpa is not set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (kvm_vcpu_map(vcpu, ghcb_gpa >> PAGE_SHIFT, &svm->ghcb_map)) अणु
		/* Unable to map GHCB from guest */
		vcpu_unimpl(vcpu, "vmgexit: error mapping GHCB [%#llx] from guest\n",
			    ghcb_gpa);
		वापस -EINVAL;
	पूर्ण

	svm->ghcb = svm->ghcb_map.hva;
	ghcb = svm->ghcb_map.hva;

	trace_kvm_vmgनिकास_enter(vcpu->vcpu_id, ghcb);

	निकास_code = ghcb_get_sw_निकास_code(ghcb);

	ret = sev_es_validate_vmgनिकास(svm);
	अगर (ret)
		वापस ret;

	sev_es_sync_from_ghcb(svm);
	ghcb_set_sw_निकास_info_1(ghcb, 0);
	ghcb_set_sw_निकास_info_2(ghcb, 0);

	ret = -EINVAL;
	चयन (निकास_code) अणु
	हाल SVM_VMGEXIT_MMIO_READ:
		अगर (!setup_vmgनिकास_scratch(svm, true, control->निकास_info_2))
			अवरोध;

		ret = kvm_sev_es_mmio_पढ़ो(vcpu,
					   control->निकास_info_1,
					   control->निकास_info_2,
					   svm->ghcb_sa);
		अवरोध;
	हाल SVM_VMGEXIT_MMIO_WRITE:
		अगर (!setup_vmgनिकास_scratch(svm, false, control->निकास_info_2))
			अवरोध;

		ret = kvm_sev_es_mmio_ग_लिखो(vcpu,
					    control->निकास_info_1,
					    control->निकास_info_2,
					    svm->ghcb_sa);
		अवरोध;
	हाल SVM_VMGEXIT_NMI_COMPLETE:
		ret = svm_invoke_निकास_handler(vcpu, SVM_EXIT_IRET);
		अवरोध;
	हाल SVM_VMGEXIT_AP_HLT_LOOP:
		ret = kvm_emulate_ap_reset_hold(vcpu);
		अवरोध;
	हाल SVM_VMGEXIT_AP_JUMP_TABLE: अणु
		काष्ठा kvm_sev_info *sev = &to_kvm_svm(vcpu->kvm)->sev_info;

		चयन (control->निकास_info_1) अणु
		हाल 0:
			/* Set AP jump table address */
			sev->ap_jump_table = control->निकास_info_2;
			अवरोध;
		हाल 1:
			/* Get AP jump table address */
			ghcb_set_sw_निकास_info_2(ghcb, sev->ap_jump_table);
			अवरोध;
		शेष:
			pr_err("svm: vmgexit: unsupported AP jump table request - exit_info_1=%#llx\n",
			       control->निकास_info_1);
			ghcb_set_sw_निकास_info_1(ghcb, 1);
			ghcb_set_sw_निकास_info_2(ghcb,
						X86_TRAP_UD |
						SVM_EVTINJ_TYPE_EXEPT |
						SVM_EVTINJ_VALID);
		पूर्ण

		ret = 1;
		अवरोध;
	पूर्ण
	हाल SVM_VMGEXIT_UNSUPPORTED_EVENT:
		vcpu_unimpl(vcpu,
			    "vmgexit: unsupported event - exit_info_1=%#llx, exit_info_2=%#llx\n",
			    control->निकास_info_1, control->निकास_info_2);
		अवरोध;
	शेष:
		ret = svm_invoke_निकास_handler(vcpu, निकास_code);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक sev_es_string_io(काष्ठा vcpu_svm *svm, पूर्णांक size, अचिन्हित पूर्णांक port, पूर्णांक in)
अणु
	अगर (!setup_vmgनिकास_scratch(svm, in, svm->vmcb->control.निकास_info_2))
		वापस -EINVAL;

	वापस kvm_sev_es_string_io(&svm->vcpu, size, port,
				    svm->ghcb_sa, svm->ghcb_sa_len, in);
पूर्ण

व्योम sev_es_init_vmcb(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा kvm_vcpu *vcpu = &svm->vcpu;

	svm->vmcb->control.nested_ctl |= SVM_NESTED_CTL_SEV_ES_ENABLE;
	svm->vmcb->control.virt_ext |= LBR_CTL_ENABLE_MASK;

	/*
	 * An SEV-ES guest requires a VMSA area that is a separate from the
	 * VMCB page. Do not include the encryption mask on the VMSA physical
	 * address since hardware will access it using the guest key.
	 */
	svm->vmcb->control.vmsa_pa = __pa(svm->vmsa);

	/* Can't intercept CR register access, HV can't modअगरy CR रेजिस्टरs */
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR0_READ);
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR4_READ);
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR8_READ);
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR0_WRITE);
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR4_WRITE);
	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR8_WRITE);

	svm_clr_पूर्णांकercept(svm, INTERCEPT_SELECTIVE_CR0);

	/* Track EFER/CR रेजिस्टर changes */
	svm_set_पूर्णांकercept(svm, TRAP_EFER_WRITE);
	svm_set_पूर्णांकercept(svm, TRAP_CR0_WRITE);
	svm_set_पूर्णांकercept(svm, TRAP_CR4_WRITE);
	svm_set_पूर्णांकercept(svm, TRAP_CR8_WRITE);

	/* No support क्रम enable_vmware_backकरोor */
	clr_exception_पूर्णांकercept(svm, GP_VECTOR);

	/* Can't intercept XSETBV, HV can't modअगरy XCR0 directly */
	svm_clr_पूर्णांकercept(svm, INTERCEPT_XSETBV);

	/* Clear पूर्णांकercepts on selected MSRs */
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_EFER, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_CR_PAT, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHFROMIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHTOIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTFROMIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTTOIP, 1, 1);
पूर्ण

व्योम sev_es_create_vcpu(काष्ठा vcpu_svm *svm)
अणु
	/*
	 * Set the GHCB MSR value as per the GHCB specअगरication when creating
	 * a vCPU क्रम an SEV-ES guest.
	 */
	set_ghcb_msr(svm, GHCB_MSR_SEV_INFO(GHCB_VERSION_MAX,
					    GHCB_VERSION_MIN,
					    sev_enc_bit));
पूर्ण

व्योम sev_es_prepare_guest_चयन(काष्ठा vcpu_svm *svm, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, cpu);
	काष्ठा vmcb_save_area *hostsa;

	/*
	 * As an SEV-ES guest, hardware will restore the host state on VMEXIT,
	 * of which one step is to perक्रमm a VMLOAD. Since hardware करोes not
	 * perक्रमm a VMSAVE on VMRUN, the host savearea must be updated.
	 */
	vmsave(__sme_page_pa(sd->save_area));

	/* XCR0 is restored on VMEXIT, save the current host value */
	hostsa = (काष्ठा vmcb_save_area *)(page_address(sd->save_area) + 0x400);
	hostsa->xcr0 = xgetbv(XCR_XFEATURE_ENABLED_MASK);

	/* PKRU is restored on VMEXIT, save the current host value */
	hostsa->pkru = पढ़ो_pkru();

	/* MSR_IA32_XSS is restored on VMEXIT, save the currnet host value */
	hostsa->xss = host_xss;
पूर्ण

व्योम sev_vcpu_deliver_sipi_vector(काष्ठा kvm_vcpu *vcpu, u8 vector)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/* First SIPI: Use the values as initially set by the VMM */
	अगर (!svm->received_first_sipi) अणु
		svm->received_first_sipi = true;
		वापस;
	पूर्ण

	/*
	 * Subsequent SIPI: Return from an AP Reset Hold VMGEXIT, where
	 * the guest will set the CS and RIP. Set SW_EXIT_INFO_2 to a
	 * non-zero value.
	 */
	अगर (!svm->ghcb)
		वापस;

	ghcb_set_sw_निकास_info_2(svm->ghcb, 1);
पूर्ण

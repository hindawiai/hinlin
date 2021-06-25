<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver to expose SGX enclave memory to KVM guests.
 *
 * Copyright(c) 2021 Intel Corporation.
 */

#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/xarray.h>
#समावेश <यंत्र/sgx.h>
#समावेश <uapi/यंत्र/sgx.h>

#समावेश "encls.h"
#समावेश "sgx.h"

काष्ठा sgx_vepc अणु
	काष्ठा xarray page_array;
	काष्ठा mutex lock;
पूर्ण;

/*
 * Temporary SECS pages that cannot be EREMOVE'd due to having child in other
 * भव EPC instances, and the lock to protect it.
 */
अटल काष्ठा mutex zombie_secs_pages_lock;
अटल काष्ठा list_head zombie_secs_pages;

अटल पूर्णांक __sgx_vepc_fault(काष्ठा sgx_vepc *vepc,
			    काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	काष्ठा sgx_epc_page *epc_page;
	अचिन्हित दीर्घ index, pfn;
	पूर्णांक ret;

	WARN_ON(!mutex_is_locked(&vepc->lock));

	/* Calculate index of EPC page in भव EPC's page_array */
	index = vma->vm_pgoff + PFN_DOWN(addr - vma->vm_start);

	epc_page = xa_load(&vepc->page_array, index);
	अगर (epc_page)
		वापस 0;

	epc_page = sgx_alloc_epc_page(vepc, false);
	अगर (IS_ERR(epc_page))
		वापस PTR_ERR(epc_page);

	ret = xa_err(xa_store(&vepc->page_array, index, epc_page, GFP_KERNEL));
	अगर (ret)
		जाओ err_मुक्त;

	pfn = PFN_DOWN(sgx_get_epc_phys_addr(epc_page));

	ret = vmf_insert_pfn(vma, addr, pfn);
	अगर (ret != VM_FAULT_NOPAGE) अणु
		ret = -EFAULT;
		जाओ err_delete;
	पूर्ण

	वापस 0;

err_delete:
	xa_erase(&vepc->page_array, index);
err_मुक्त:
	sgx_मुक्त_epc_page(epc_page);
	वापस ret;
पूर्ण

अटल vm_fault_t sgx_vepc_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा sgx_vepc *vepc = vma->vm_निजी_data;
	पूर्णांक ret;

	mutex_lock(&vepc->lock);
	ret = __sgx_vepc_fault(vepc, vma, vmf->address);
	mutex_unlock(&vepc->lock);

	अगर (!ret)
		वापस VM_FAULT_NOPAGE;

	अगर (ret == -EBUSY && (vmf->flags & FAULT_FLAG_ALLOW_RETRY)) अणु
		mmap_पढ़ो_unlock(vma->vm_mm);
		वापस VM_FAULT_RETRY;
	पूर्ण

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा sgx_vepc_vm_ops = अणु
	.fault = sgx_vepc_fault,
पूर्ण;

अटल पूर्णांक sgx_vepc_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sgx_vepc *vepc = file->निजी_data;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	vma->vm_ops = &sgx_vepc_vm_ops;
	/* Don't copy VMA in विभाजन() */
	vma->vm_flags |= VM_PFNMAP | VM_IO | VM_DONTDUMP | VM_DONTCOPY;
	vma->vm_निजी_data = vepc;

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_vepc_मुक्त_page(काष्ठा sgx_epc_page *epc_page)
अणु
	पूर्णांक ret;

	/*
	 * Take a previously guest-owned EPC page and वापस it to the
	 * general EPC page pool.
	 *
	 * Guests can not be trusted to have left this page in a good
	 * state, so run EREMOVE on the page unconditionally.  In the
	 * हाल that a guest properly EREMOVE'd this page, a superfluous
	 * EREMOVE is harmless.
	 */
	ret = __eहटाओ(sgx_get_epc_virt_addr(epc_page));
	अगर (ret) अणु
		/*
		 * Only SGX_CHILD_PRESENT is expected, which is because of
		 * EREMOVE'ing an SECS still with child, in which हाल it can
		 * be handled by EREMOVE'ing the SECS again after all pages in
		 * भव EPC have been EREMOVE'd. See comments in below in
		 * sgx_vepc_release().
		 *
		 * The user of भव EPC (KVM) needs to guarantee there's no
		 * logical processor is still running in the enclave in guest,
		 * otherwise EREMOVE will get SGX_ENCLAVE_ACT which cannot be
		 * handled here.
		 */
		WARN_ONCE(ret != SGX_CHILD_PRESENT, EREMOVE_ERROR_MESSAGE,
			  ret, ret);
		वापस ret;
	पूर्ण

	sgx_मुक्त_epc_page(epc_page);

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_vepc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sgx_vepc *vepc = file->निजी_data;
	काष्ठा sgx_epc_page *epc_page, *पंचांगp, *entry;
	अचिन्हित दीर्घ index;

	LIST_HEAD(secs_pages);

	xa_क्रम_each(&vepc->page_array, index, entry) अणु
		/*
		 * Remove all normal, child pages.  sgx_vepc_मुक्त_page()
		 * will fail अगर EREMOVE fails, but this is OK and expected on
		 * SECS pages.  Those can only be EREMOVE'd *after* all their
		 * child pages. Retries below will clean them up.
		 */
		अगर (sgx_vepc_मुक्त_page(entry))
			जारी;

		xa_erase(&vepc->page_array, index);
	पूर्ण

	/*
	 * Retry EREMOVE'ing pages.  This will clean up any SECS pages that
	 * only had children in this 'epc' area.
	 */
	xa_क्रम_each(&vepc->page_array, index, entry) अणु
		epc_page = entry;
		/*
		 * An EREMOVE failure here means that the SECS page still
		 * has children.  But, since all children in this 'sgx_vepc'
		 * have been हटाओd, the SECS page must have a child on
		 * another instance.
		 */
		अगर (sgx_vepc_मुक्त_page(epc_page))
			list_add_tail(&epc_page->list, &secs_pages);

		xa_erase(&vepc->page_array, index);
	पूर्ण

	/*
	 * SECS pages are "pinned" by child pages, and "unpinned" once all
	 * children have been EREMOVE'd.  A child page in this instance
	 * may have pinned an SECS page encountered in an earlier release(),
	 * creating a zombie.  Since some children were EREMOVE'd above,
	 * try to EREMOVE all zombies in the hopes that one was unpinned.
	 */
	mutex_lock(&zombie_secs_pages_lock);
	list_क्रम_each_entry_safe(epc_page, पंचांगp, &zombie_secs_pages, list) अणु
		/*
		 * Speculatively हटाओ the page from the list of zombies,
		 * अगर the page is successfully EREMOVE'd it will be added to
		 * the list of मुक्त pages.  If EREMOVE fails, throw the page
		 * on the local list, which will be spliced on at the end.
		 */
		list_del(&epc_page->list);

		अगर (sgx_vepc_मुक्त_page(epc_page))
			list_add_tail(&epc_page->list, &secs_pages);
	पूर्ण

	अगर (!list_empty(&secs_pages))
		list_splice_tail(&secs_pages, &zombie_secs_pages);
	mutex_unlock(&zombie_secs_pages_lock);

	xa_destroy(&vepc->page_array);
	kमुक्त(vepc);

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_vepc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sgx_vepc *vepc;

	vepc = kzalloc(माप(काष्ठा sgx_vepc), GFP_KERNEL);
	अगर (!vepc)
		वापस -ENOMEM;
	mutex_init(&vepc->lock);
	xa_init(&vepc->page_array);

	file->निजी_data = vepc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations sgx_vepc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sgx_vepc_खोलो,
	.release	= sgx_vepc_release,
	.mmap		= sgx_vepc_mmap,
पूर्ण;

अटल काष्ठा miscdevice sgx_vepc_dev = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "sgx_vepc",
	.nodename	= "sgx_vepc",
	.fops		= &sgx_vepc_fops,
पूर्ण;

पूर्णांक __init sgx_vepc_init(व्योम)
अणु
	/* SGX भवization requires KVM to work */
	अगर (!cpu_feature_enabled(X86_FEATURE_VMX))
		वापस -ENODEV;

	INIT_LIST_HEAD(&zombie_secs_pages);
	mutex_init(&zombie_secs_pages_lock);

	वापस misc_रेजिस्टर(&sgx_vepc_dev);
पूर्ण

/**
 * sgx_virt_ecreate() - Run ECREATE on behalf of guest
 * @pageinfo:	Poपूर्णांकer to PAGEINFO काष्ठाure
 * @secs:	Userspace poपूर्णांकer to SECS page
 * @trapnr:	trap number injected to guest in हाल of ECREATE error
 *
 * Run ECREATE on behalf of guest after KVM traps ECREATE क्रम the purpose
 * of enक्रमcing policies of guest's enclaves, and वापस the trap number
 * which should be injected to guest in हाल of any ECREATE error.
 *
 * Return:
 * -  0:	ECREATE was successful.
 * - <0:	on error.
 */
पूर्णांक sgx_virt_ecreate(काष्ठा sgx_pageinfo *pageinfo, व्योम __user *secs,
		     पूर्णांक *trapnr)
अणु
	पूर्णांक ret;

	/*
	 * @secs is an untrusted, userspace-provided address.  It comes from
	 * KVM and is assumed to be a valid poपूर्णांकer which poपूर्णांकs somewhere in
	 * userspace.  This can fault and call SGX or other fault handlers when
	 * userspace mapping @secs करोesn't exist.
	 *
	 * Add a WARN() to make sure @secs is alपढ़ोy valid userspace poपूर्णांकer
	 * from caller (KVM), who should alपढ़ोy have handled invalid poपूर्णांकer
	 * हाल (क्रम instance, made by malicious guest).  All other checks,
	 * such as alignment of @secs, are deferred to ENCLS itself.
	 */
	अगर (WARN_ON_ONCE(!access_ok(secs, PAGE_SIZE)))
		वापस -EINVAL;

	__uaccess_begin();
	ret = __ecreate(pageinfo, (व्योम *)secs);
	__uaccess_end();

	अगर (encls_faulted(ret)) अणु
		*trapnr = ENCLS_TRAPNR(ret);
		वापस -EFAULT;
	पूर्ण

	/* ECREATE करोesn't वापस an error code, it faults or succeeds. */
	WARN_ON_ONCE(ret);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sgx_virt_ecreate);

अटल पूर्णांक __sgx_virt_einit(व्योम __user *sigकाष्ठा, व्योम __user *token,
			    व्योम __user *secs)
अणु
	पूर्णांक ret;

	/*
	 * Make sure all userspace poपूर्णांकers from caller (KVM) are valid.
	 * All other checks deferred to ENCLS itself.  Also see comment
	 * क्रम @secs in sgx_virt_ecreate().
	 */
#घोषणा SGX_EINITTOKEN_SIZE	304
	अगर (WARN_ON_ONCE(!access_ok(sigकाष्ठा, माप(काष्ठा sgx_sigकाष्ठा)) ||
			 !access_ok(token, SGX_EINITTOKEN_SIZE) ||
			 !access_ok(secs, PAGE_SIZE)))
		वापस -EINVAL;

	__uaccess_begin();
	ret = __einit((व्योम *)sigकाष्ठा, (व्योम *)token, (व्योम *)secs);
	__uaccess_end();

	वापस ret;
पूर्ण

/**
 * sgx_virt_einit() - Run EINIT on behalf of guest
 * @sigकाष्ठा:		Userspace poपूर्णांकer to SIGSTRUCT काष्ठाure
 * @token:		Userspace poपूर्णांकer to EINITTOKEN काष्ठाure
 * @secs:		Userspace poपूर्णांकer to SECS page
 * @lepubkeyhash:	Poपूर्णांकer to guest's *भव* SGX_LEPUBKEYHASH MSR values
 * @trapnr:		trap number injected to guest in हाल of EINIT error
 *
 * Run EINIT on behalf of guest after KVM traps EINIT. If SGX_LC is available
 * in host, SGX driver may reग_लिखो the hardware values at wish, thereक्रमe KVM
 * needs to update hardware values to guest's भव MSR values in order to
 * ensure EINIT is executed with expected hardware values.
 *
 * Return:
 * -  0:	EINIT was successful.
 * - <0:	on error.
 */
पूर्णांक sgx_virt_einit(व्योम __user *sigकाष्ठा, व्योम __user *token,
		   व्योम __user *secs, u64 *lepubkeyhash, पूर्णांक *trapnr)
अणु
	पूर्णांक ret;

	अगर (!cpu_feature_enabled(X86_FEATURE_SGX_LC)) अणु
		ret = __sgx_virt_einit(sigकाष्ठा, token, secs);
	पूर्ण अन्यथा अणु
		preempt_disable();

		sgx_update_lepubkeyhash(lepubkeyhash);

		ret = __sgx_virt_einit(sigकाष्ठा, token, secs);
		preempt_enable();
	पूर्ण

	/* Propagate up the error from the WARN_ON_ONCE in __sgx_virt_einit() */
	अगर (ret == -EINVAL)
		वापस ret;

	अगर (encls_faulted(ret)) अणु
		*trapnr = ENCLS_TRAPNR(ret);
		वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sgx_virt_einit);

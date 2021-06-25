<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Copyright(c) 2016-20 Intel Corporation. */

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/sgx.h>
#समावेश <linux/mman.h>
#समावेश <linux/delay.h>
#समावेश <linux/file.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश "driver.h"
#समावेश "encl.h"
#समावेश "encls.h"

अटल काष्ठा sgx_va_page *sgx_encl_grow(काष्ठा sgx_encl *encl)
अणु
	काष्ठा sgx_va_page *va_page = शून्य;
	व्योम *err;

	BUILD_BUG_ON(SGX_VA_SLOT_COUNT !=
		(SGX_ENCL_PAGE_VA_OFFSET_MASK >> 3) + 1);

	अगर (!(encl->page_cnt % SGX_VA_SLOT_COUNT)) अणु
		va_page = kzalloc(माप(*va_page), GFP_KERNEL);
		अगर (!va_page)
			वापस ERR_PTR(-ENOMEM);

		va_page->epc_page = sgx_alloc_va_page();
		अगर (IS_ERR(va_page->epc_page)) अणु
			err = ERR_CAST(va_page->epc_page);
			kमुक्त(va_page);
			वापस err;
		पूर्ण

		WARN_ON_ONCE(encl->page_cnt % SGX_VA_SLOT_COUNT);
	पूर्ण
	encl->page_cnt++;
	वापस va_page;
पूर्ण

अटल व्योम sgx_encl_shrink(काष्ठा sgx_encl *encl, काष्ठा sgx_va_page *va_page)
अणु
	encl->page_cnt--;

	अगर (va_page) अणु
		sgx_encl_मुक्त_epc_page(va_page->epc_page);
		list_del(&va_page->list);
		kमुक्त(va_page);
	पूर्ण
पूर्ण

अटल पूर्णांक sgx_encl_create(काष्ठा sgx_encl *encl, काष्ठा sgx_secs *secs)
अणु
	काष्ठा sgx_epc_page *secs_epc;
	काष्ठा sgx_va_page *va_page;
	काष्ठा sgx_pageinfo pginfo;
	काष्ठा sgx_secinfo secinfo;
	अचिन्हित दीर्घ encl_size;
	काष्ठा file *backing;
	दीर्घ ret;

	va_page = sgx_encl_grow(encl);
	अगर (IS_ERR(va_page))
		वापस PTR_ERR(va_page);
	अन्यथा अगर (va_page)
		list_add(&va_page->list, &encl->va_pages);
	/* अन्यथा the tail page of the VA page list had मुक्त slots. */

	/* The extra page goes to SECS. */
	encl_size = secs->size + PAGE_SIZE;

	backing = shmem_file_setup("SGX backing", encl_size + (encl_size >> 5),
				   VM_NORESERVE);
	अगर (IS_ERR(backing)) अणु
		ret = PTR_ERR(backing);
		जाओ err_out_shrink;
	पूर्ण

	encl->backing = backing;

	secs_epc = sgx_alloc_epc_page(&encl->secs, true);
	अगर (IS_ERR(secs_epc)) अणु
		ret = PTR_ERR(secs_epc);
		जाओ err_out_backing;
	पूर्ण

	encl->secs.epc_page = secs_epc;

	pginfo.addr = 0;
	pginfo.contents = (अचिन्हित दीर्घ)secs;
	pginfo.metadata = (अचिन्हित दीर्घ)&secinfo;
	pginfo.secs = 0;
	स_रखो(&secinfo, 0, माप(secinfo));

	ret = __ecreate((व्योम *)&pginfo, sgx_get_epc_virt_addr(secs_epc));
	अगर (ret) अणु
		ret = -EIO;
		जाओ err_out;
	पूर्ण

	अगर (secs->attributes & SGX_ATTR_DEBUG)
		set_bit(SGX_ENCL_DEBUG, &encl->flags);

	encl->secs.encl = encl;
	encl->base = secs->base;
	encl->size = secs->size;
	encl->attributes = secs->attributes;
	encl->attributes_mask = SGX_ATTR_DEBUG | SGX_ATTR_MODE64BIT | SGX_ATTR_KSS;

	/* Set only after completion, as encl->lock has not been taken. */
	set_bit(SGX_ENCL_CREATED, &encl->flags);

	वापस 0;

err_out:
	sgx_encl_मुक्त_epc_page(encl->secs.epc_page);
	encl->secs.epc_page = शून्य;

err_out_backing:
	fput(encl->backing);
	encl->backing = शून्य;

err_out_shrink:
	sgx_encl_shrink(encl, va_page);

	वापस ret;
पूर्ण

/**
 * sgx_ioc_enclave_create() - handler क्रम %SGX_IOC_ENCLAVE_CREATE
 * @encl:	An enclave poपूर्णांकer.
 * @arg:	The ioctl argument.
 *
 * Allocate kernel data काष्ठाures क्रम the enclave and invoke ECREATE.
 *
 * Return:
 * - 0:		Success.
 * - -EIO:	ECREATE failed.
 * - -त्रुटि_सं:	POSIX error.
 */
अटल दीर्घ sgx_ioc_enclave_create(काष्ठा sgx_encl *encl, व्योम __user *arg)
अणु
	काष्ठा sgx_enclave_create create_arg;
	व्योम *secs;
	पूर्णांक ret;

	अगर (test_bit(SGX_ENCL_CREATED, &encl->flags))
		वापस -EINVAL;

	अगर (copy_from_user(&create_arg, arg, माप(create_arg)))
		वापस -EFAULT;

	secs = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!secs)
		वापस -ENOMEM;

	अगर (copy_from_user(secs, (व्योम __user *)create_arg.src, PAGE_SIZE))
		ret = -EFAULT;
	अन्यथा
		ret = sgx_encl_create(encl, secs);

	kमुक्त(secs);
	वापस ret;
पूर्ण

अटल काष्ठा sgx_encl_page *sgx_encl_page_alloc(काष्ठा sgx_encl *encl,
						 अचिन्हित दीर्घ offset,
						 u64 secinfo_flags)
अणु
	काष्ठा sgx_encl_page *encl_page;
	अचिन्हित दीर्घ prot;

	encl_page = kzalloc(माप(*encl_page), GFP_KERNEL);
	अगर (!encl_page)
		वापस ERR_PTR(-ENOMEM);

	encl_page->desc = encl->base + offset;
	encl_page->encl = encl;

	prot = _calc_vm_trans(secinfo_flags, SGX_SECINFO_R, PROT_READ)  |
	       _calc_vm_trans(secinfo_flags, SGX_SECINFO_W, PROT_WRITE) |
	       _calc_vm_trans(secinfo_flags, SGX_SECINFO_X, PROT_EXEC);

	/*
	 * TCS pages must always RW set क्रम CPU access जबतक the SECINFO
	 * permissions are *always* zero - the CPU ignores the user provided
	 * values and silently overग_लिखोs them with zero permissions.
	 */
	अगर ((secinfo_flags & SGX_SECINFO_PAGE_TYPE_MASK) == SGX_SECINFO_TCS)
		prot |= PROT_READ | PROT_WRITE;

	/* Calculate maximum of the VM flags क्रम the page. */
	encl_page->vm_max_prot_bits = calc_vm_prot_bits(prot, 0);

	वापस encl_page;
पूर्ण

अटल पूर्णांक sgx_validate_secinfo(काष्ठा sgx_secinfo *secinfo)
अणु
	u64 perm = secinfo->flags & SGX_SECINFO_PERMISSION_MASK;
	u64 pt   = secinfo->flags & SGX_SECINFO_PAGE_TYPE_MASK;

	अगर (pt != SGX_SECINFO_REG && pt != SGX_SECINFO_TCS)
		वापस -EINVAL;

	अगर ((perm & SGX_SECINFO_W) && !(perm & SGX_SECINFO_R))
		वापस -EINVAL;

	/*
	 * CPU will silently overग_लिखो the permissions as zero, which means
	 * that we need to validate it ourselves.
	 */
	अगर (pt == SGX_SECINFO_TCS && perm)
		वापस -EINVAL;

	अगर (secinfo->flags & SGX_SECINFO_RESERVED_MASK)
		वापस -EINVAL;

	अगर (स_प्रथम_inv(secinfo->reserved, 0, माप(secinfo->reserved)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __sgx_encl_add_page(काष्ठा sgx_encl *encl,
			       काष्ठा sgx_encl_page *encl_page,
			       काष्ठा sgx_epc_page *epc_page,
			       काष्ठा sgx_secinfo *secinfo, अचिन्हित दीर्घ src)
अणु
	काष्ठा sgx_pageinfo pginfo;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा page *src_page;
	पूर्णांक ret;

	/* Deny noexec. */
	vma = find_vma(current->mm, src);
	अगर (!vma)
		वापस -EFAULT;

	अगर (!(vma->vm_flags & VM_MAYEXEC))
		वापस -EACCES;

	ret = get_user_pages(src, 1, 0, &src_page, शून्य);
	अगर (ret < 1)
		वापस -EFAULT;

	pginfo.secs = (अचिन्हित दीर्घ)sgx_get_epc_virt_addr(encl->secs.epc_page);
	pginfo.addr = encl_page->desc & PAGE_MASK;
	pginfo.metadata = (अचिन्हित दीर्घ)secinfo;
	pginfo.contents = (अचिन्हित दीर्घ)kmap_atomic(src_page);

	ret = __eadd(&pginfo, sgx_get_epc_virt_addr(epc_page));

	kunmap_atomic((व्योम *)pginfo.contents);
	put_page(src_page);

	वापस ret ? -EIO : 0;
पूर्ण

/*
 * If the caller requires measurement of the page as a proof क्रम the content,
 * use EEXTEND to add a measurement क्रम 256 bytes of the page. Repeat this
 * operation until the entire page is measured."
 */
अटल पूर्णांक __sgx_encl_extend(काष्ठा sgx_encl *encl,
			     काष्ठा sgx_epc_page *epc_page)
अणु
	अचिन्हित दीर्घ offset;
	पूर्णांक ret;

	क्रम (offset = 0; offset < PAGE_SIZE; offset += SGX_EEXTEND_BLOCK_SIZE) अणु
		ret = __eextend(sgx_get_epc_virt_addr(encl->secs.epc_page),
				sgx_get_epc_virt_addr(epc_page) + offset);
		अगर (ret) अणु
			अगर (encls_failed(ret))
				ENCLS_WARN(ret, "EEXTEND");

			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sgx_encl_add_page(काष्ठा sgx_encl *encl, अचिन्हित दीर्घ src,
			     अचिन्हित दीर्घ offset, काष्ठा sgx_secinfo *secinfo,
			     अचिन्हित दीर्घ flags)
अणु
	काष्ठा sgx_encl_page *encl_page;
	काष्ठा sgx_epc_page *epc_page;
	काष्ठा sgx_va_page *va_page;
	पूर्णांक ret;

	encl_page = sgx_encl_page_alloc(encl, offset, secinfo->flags);
	अगर (IS_ERR(encl_page))
		वापस PTR_ERR(encl_page);

	epc_page = sgx_alloc_epc_page(encl_page, true);
	अगर (IS_ERR(epc_page)) अणु
		kमुक्त(encl_page);
		वापस PTR_ERR(epc_page);
	पूर्ण

	va_page = sgx_encl_grow(encl);
	अगर (IS_ERR(va_page)) अणु
		ret = PTR_ERR(va_page);
		जाओ err_out_मुक्त;
	पूर्ण

	mmap_पढ़ो_lock(current->mm);
	mutex_lock(&encl->lock);

	/*
	 * Adding to encl->va_pages must be करोne under encl->lock.  Ditto क्रम
	 * deleting (via sgx_encl_shrink()) in the error path.
	 */
	अगर (va_page)
		list_add(&va_page->list, &encl->va_pages);

	/*
	 * Insert prior to EADD in हाल of OOM.  EADD modअगरies MRENCLAVE, i.e.
	 * can't be gracefully unwound, जबतक failure on EADD/EXTEND is limited
	 * to userspace errors (or kernel/hardware bugs).
	 */
	ret = xa_insert(&encl->page_array, PFN_DOWN(encl_page->desc),
			encl_page, GFP_KERNEL);
	अगर (ret)
		जाओ err_out_unlock;

	ret = __sgx_encl_add_page(encl, encl_page, epc_page, secinfo,
				  src);
	अगर (ret)
		जाओ err_out;

	/*
	 * Complete the "add" beक्रमe करोing the "extend" so that the "add"
	 * isn't in a half-baked state in the extremely unlikely scenario
	 * the enclave will be destroyed in response to EEXTEND failure.
	 */
	encl_page->encl = encl;
	encl_page->epc_page = epc_page;
	encl->secs_child_cnt++;

	अगर (flags & SGX_PAGE_MEASURE) अणु
		ret = __sgx_encl_extend(encl, epc_page);
		अगर (ret)
			जाओ err_out;
	पूर्ण

	sgx_mark_page_reclaimable(encl_page->epc_page);
	mutex_unlock(&encl->lock);
	mmap_पढ़ो_unlock(current->mm);
	वापस ret;

err_out:
	xa_erase(&encl->page_array, PFN_DOWN(encl_page->desc));

err_out_unlock:
	sgx_encl_shrink(encl, va_page);
	mutex_unlock(&encl->lock);
	mmap_पढ़ो_unlock(current->mm);

err_out_मुक्त:
	sgx_encl_मुक्त_epc_page(epc_page);
	kमुक्त(encl_page);

	वापस ret;
पूर्ण

/**
 * sgx_ioc_enclave_add_pages() - The handler क्रम %SGX_IOC_ENCLAVE_ADD_PAGES
 * @encl:       an enclave poपूर्णांकer
 * @arg:	a user poपूर्णांकer to a काष्ठा sgx_enclave_add_pages instance
 *
 * Add one or more pages to an uninitialized enclave, and optionally extend the
 * measurement with the contents of the page. The SECINFO and measurement mask
 * are applied to all pages.
 *
 * A SECINFO क्रम a TCS is required to always contain zero permissions because
 * CPU silently zeros them. Allowing anything अन्यथा would cause a mismatch in
 * the measurement.
 *
 * mmap()'s protection bits are capped by the page permissions. For each page
 * address, the maximum protection bits are computed with the following
 * heuristics:
 *
 * 1. A regular page: PROT_R, PROT_W and PROT_X match the SECINFO permissions.
 * 2. A TCS page: PROT_R | PROT_W.
 *
 * mmap() is not allowed to surpass the minimum of the maximum protection bits
 * within the given address range.
 *
 * The function deinitializes kernel data काष्ठाures क्रम enclave and वापसs
 * -EIO in any of the following conditions:
 *
 * - Enclave Page Cache (EPC), the physical memory holding enclaves, has
 *   been invalidated. This will cause EADD and EEXTEND to fail.
 * - If the source address is corrupted somehow when executing EADD.
 *
 * Return:
 * - 0:		Success.
 * - -EACCES:	The source page is located in a noexec partition.
 * - -ENOMEM:	Out of EPC pages.
 * - -EINTR:	The call was पूर्णांकerrupted beक्रमe data was processed.
 * - -EIO:	Either EADD or EEXTEND failed because invalid source address
 *		or घातer cycle.
 * - -त्रुटि_सं:	POSIX error.
 */
अटल दीर्घ sgx_ioc_enclave_add_pages(काष्ठा sgx_encl *encl, व्योम __user *arg)
अणु
	काष्ठा sgx_enclave_add_pages add_arg;
	काष्ठा sgx_secinfo secinfo;
	अचिन्हित दीर्घ c;
	पूर्णांक ret;

	अगर (!test_bit(SGX_ENCL_CREATED, &encl->flags) ||
	    test_bit(SGX_ENCL_INITIALIZED, &encl->flags))
		वापस -EINVAL;

	अगर (copy_from_user(&add_arg, arg, माप(add_arg)))
		वापस -EFAULT;

	अगर (!IS_ALIGNED(add_arg.offset, PAGE_SIZE) ||
	    !IS_ALIGNED(add_arg.src, PAGE_SIZE))
		वापस -EINVAL;

	अगर (!add_arg.length || add_arg.length & (PAGE_SIZE - 1))
		वापस -EINVAL;

	अगर (add_arg.offset + add_arg.length - PAGE_SIZE >= encl->size)
		वापस -EINVAL;

	अगर (copy_from_user(&secinfo, (व्योम __user *)add_arg.secinfo,
			   माप(secinfo)))
		वापस -EFAULT;

	अगर (sgx_validate_secinfo(&secinfo))
		वापस -EINVAL;

	क्रम (c = 0 ; c < add_arg.length; c += PAGE_SIZE) अणु
		अगर (संकेत_pending(current)) अणु
			अगर (!c)
				ret = -ERESTARTSYS;

			अवरोध;
		पूर्ण

		अगर (need_resched())
			cond_resched();

		ret = sgx_encl_add_page(encl, add_arg.src + c, add_arg.offset + c,
					&secinfo, add_arg.flags);
		अगर (ret)
			अवरोध;
	पूर्ण

	add_arg.count = c;

	अगर (copy_to_user(arg, &add_arg, माप(add_arg)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक __sgx_get_key_hash(काष्ठा crypto_shash *tfm, स्थिर व्योम *modulus,
			      व्योम *hash)
अणु
	SHASH_DESC_ON_STACK(shash, tfm);

	shash->tfm = tfm;

	वापस crypto_shash_digest(shash, modulus, SGX_MODULUS_SIZE, hash);
पूर्ण

अटल पूर्णांक sgx_get_key_hash(स्थिर व्योम *modulus, व्योम *hash)
अणु
	काष्ठा crypto_shash *tfm;
	पूर्णांक ret;

	tfm = crypto_alloc_shash("sha256", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm))
		वापस PTR_ERR(tfm);

	ret = __sgx_get_key_hash(tfm, modulus, hash);

	crypto_मुक्त_shash(tfm);
	वापस ret;
पूर्ण

अटल पूर्णांक sgx_encl_init(काष्ठा sgx_encl *encl, काष्ठा sgx_sigकाष्ठा *sigकाष्ठा,
			 व्योम *token)
अणु
	u64 mrsigner[4];
	पूर्णांक i, j;
	व्योम *addr;
	पूर्णांक ret;

	/*
	 * Deny initializing enclaves with attributes (namely provisioning)
	 * that have not been explicitly allowed.
	 */
	अगर (encl->attributes & ~encl->attributes_mask)
		वापस -EACCES;

	/*
	 * Attributes should not be enक्रमced *only* against what's available on
	 * platक्रमm (करोne in sgx_encl_create) but checked and enक्रमced against
	 * the mask क्रम enक्रमcement in sigकाष्ठा. For example an enclave could
	 * opt to sign with AVX bit in xfrm, but still be loadable on a platक्रमm
	 * without it अगर the sigकाष्ठा->body.attributes_mask करोes not turn that
	 * bit on.
	 */
	अगर (sigकाष्ठा->body.attributes & sigकाष्ठा->body.attributes_mask &
	    sgx_attributes_reserved_mask)
		वापस -EINVAL;

	अगर (sigकाष्ठा->body.miscselect & sigकाष्ठा->body.misc_mask &
	    sgx_misc_reserved_mask)
		वापस -EINVAL;

	अगर (sigकाष्ठा->body.xfrm & sigकाष्ठा->body.xfrm_mask &
	    sgx_xfrm_reserved_mask)
		वापस -EINVAL;

	ret = sgx_get_key_hash(sigकाष्ठा->modulus, mrsigner);
	अगर (ret)
		वापस ret;

	mutex_lock(&encl->lock);

	/*
	 * ENCLS[EINIT] is पूर्णांकerruptible because it has such a high latency,
	 * e.g. 50k+ cycles on success. If an IRQ/NMI/SMI becomes pending,
	 * EINIT may fail with SGX_UNMASKED_EVENT so that the event can be
	 * serviced.
	 */
	क्रम (i = 0; i < SGX_EINIT_SLEEP_COUNT; i++) अणु
		क्रम (j = 0; j < SGX_EINIT_SPIN_COUNT; j++) अणु
			addr = sgx_get_epc_virt_addr(encl->secs.epc_page);

			preempt_disable();

			sgx_update_lepubkeyhash(mrsigner);

			ret = __einit(sigकाष्ठा, token, addr);

			preempt_enable();

			अगर (ret == SGX_UNMASKED_EVENT)
				जारी;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (ret != SGX_UNMASKED_EVENT)
			अवरोध;

		msleep_पूर्णांकerruptible(SGX_EINIT_SLEEP_TIME);

		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (encls_faulted(ret)) अणु
		अगर (encls_failed(ret))
			ENCLS_WARN(ret, "EINIT");

		ret = -EIO;
	पूर्ण अन्यथा अगर (ret) अणु
		pr_debug("EINIT returned %d\n", ret);
		ret = -EPERM;
	पूर्ण अन्यथा अणु
		set_bit(SGX_ENCL_INITIALIZED, &encl->flags);
	पूर्ण

err_out:
	mutex_unlock(&encl->lock);
	वापस ret;
पूर्ण

/**
 * sgx_ioc_enclave_init() - handler क्रम %SGX_IOC_ENCLAVE_INIT
 * @encl:	an enclave poपूर्णांकer
 * @arg:	userspace poपूर्णांकer to a काष्ठा sgx_enclave_init instance
 *
 * Flush any outstanding enqueued EADD operations and perक्रमm EINIT.  The
 * Launch Enclave Public Key Hash MSRs are rewritten as necessary to match
 * the enclave's MRSIGNER, which is caculated from the provided sigकाष्ठा.
 *
 * Return:
 * - 0:		Success.
 * - -EPERM:	Invalid SIGSTRUCT.
 * - -EIO:	EINIT failed because of a घातer cycle.
 * - -त्रुटि_सं:	POSIX error.
 */
अटल दीर्घ sgx_ioc_enclave_init(काष्ठा sgx_encl *encl, व्योम __user *arg)
अणु
	काष्ठा sgx_sigकाष्ठा *sigकाष्ठा;
	काष्ठा sgx_enclave_init init_arg;
	व्योम *token;
	पूर्णांक ret;

	अगर (!test_bit(SGX_ENCL_CREATED, &encl->flags) ||
	    test_bit(SGX_ENCL_INITIALIZED, &encl->flags))
		वापस -EINVAL;

	अगर (copy_from_user(&init_arg, arg, माप(init_arg)))
		वापस -EFAULT;

	/*
	 * 'sigstruct' must be on a page boundary and 'token' on a 512 byte
	 * boundary.  kदो_स्मृति() will give this alignment when allocating
	 * PAGE_SIZE bytes.
	 */
	sigकाष्ठा = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!sigकाष्ठा)
		वापस -ENOMEM;

	token = (व्योम *)((अचिन्हित दीर्घ)sigकाष्ठा + PAGE_SIZE / 2);
	स_रखो(token, 0, SGX_LAUNCH_TOKEN_SIZE);

	अगर (copy_from_user(sigकाष्ठा, (व्योम __user *)init_arg.sigकाष्ठा,
			   माप(*sigकाष्ठा))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/*
	 * A legacy field used with Intel चिन्हित enclaves. These used to mean
	 * regular and architectural enclaves. The CPU only accepts these values
	 * but they करो not have any other meaning.
	 *
	 * Thus, reject any other values.
	 */
	अगर (sigकाष्ठा->header.venकरोr != 0x0000 &&
	    sigकाष्ठा->header.venकरोr != 0x8086) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = sgx_encl_init(encl, sigकाष्ठा, token);

out:
	kमुक्त(sigकाष्ठा);
	वापस ret;
पूर्ण

/**
 * sgx_ioc_enclave_provision() - handler क्रम %SGX_IOC_ENCLAVE_PROVISION
 * @encl:	an enclave poपूर्णांकer
 * @arg:	userspace poपूर्णांकer to a काष्ठा sgx_enclave_provision instance
 *
 * Allow ATTRIBUTE.PROVISION_KEY क्रम an enclave by providing a file handle to
 * /dev/sgx_provision.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	Otherwise.
 */
अटल दीर्घ sgx_ioc_enclave_provision(काष्ठा sgx_encl *encl, व्योम __user *arg)
अणु
	काष्ठा sgx_enclave_provision params;

	अगर (copy_from_user(&params, arg, माप(params)))
		वापस -EFAULT;

	वापस sgx_set_attribute(&encl->attributes_mask, params.fd);
पूर्ण

दीर्घ sgx_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sgx_encl *encl = filep->निजी_data;
	पूर्णांक ret;

	अगर (test_and_set_bit(SGX_ENCL_IOCTL, &encl->flags))
		वापस -EBUSY;

	चयन (cmd) अणु
	हाल SGX_IOC_ENCLAVE_CREATE:
		ret = sgx_ioc_enclave_create(encl, (व्योम __user *)arg);
		अवरोध;
	हाल SGX_IOC_ENCLAVE_ADD_PAGES:
		ret = sgx_ioc_enclave_add_pages(encl, (व्योम __user *)arg);
		अवरोध;
	हाल SGX_IOC_ENCLAVE_INIT:
		ret = sgx_ioc_enclave_init(encl, (व्योम __user *)arg);
		अवरोध;
	हाल SGX_IOC_ENCLAVE_PROVISION:
		ret = sgx_ioc_enclave_provision(encl, (व्योम __user *)arg);
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	clear_bit(SGX_ENCL_IOCTL, &encl->flags);
	वापस ret;
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common Ultravisor functions and initialization
 *
 * Copyright IBM Corp. 2019, 2020
 */
#घोषणा KMSG_COMPONENT "prot_virt"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/uv.h>

/* the bootdata_preserved fields come from ones in arch/s390/boot/uv.c */
#अगर_घोषित CONFIG_PROTECTED_VIRTUALIZATION_GUEST
पूर्णांक __bootdata_preserved(prot_virt_guest);
#पूर्ण_अगर

काष्ठा uv_info __bootdata_preserved(uv_info);

#अगर IS_ENABLED(CONFIG_KVM)
पूर्णांक __bootdata_preserved(prot_virt_host);
EXPORT_SYMBOL(prot_virt_host);
EXPORT_SYMBOL(uv_info);

अटल पूर्णांक __init uv_init(अचिन्हित दीर्घ stor_base, अचिन्हित दीर्घ stor_len)
अणु
	काष्ठा uv_cb_init uvcb = अणु
		.header.cmd = UVC_CMD_INIT_UV,
		.header.len = माप(uvcb),
		.stor_origin = stor_base,
		.stor_len = stor_len,
	पूर्ण;

	अगर (uv_call(0, (uपूर्णांक64_t)&uvcb)) अणु
		pr_err("Ultravisor init failed with rc: 0x%x rrc: 0%x\n",
		       uvcb.header.rc, uvcb.header.rrc);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम __init setup_uv(व्योम)
अणु
	अचिन्हित दीर्घ uv_stor_base;

	/*
	 * keep these conditions in line with kasan init code has_uv_sec_stor_limit()
	 */
	अगर (!is_prot_virt_host())
		वापस;

	अगर (is_prot_virt_guest()) अणु
		prot_virt_host = 0;
		pr_warn("Protected virtualization not available in protected guests.");
		वापस;
	पूर्ण

	अगर (!test_facility(158)) अणु
		prot_virt_host = 0;
		pr_warn("Protected virtualization not supported by the hardware.");
		वापस;
	पूर्ण

	uv_stor_base = (अचिन्हित दीर्घ)memblock_alloc_try_nid(
		uv_info.uv_base_stor_len, SZ_1M, SZ_2G,
		MEMBLOCK_ALLOC_ACCESSIBLE, NUMA_NO_NODE);
	अगर (!uv_stor_base) अणु
		pr_warn("Failed to reserve %lu bytes for ultravisor base storage\n",
			uv_info.uv_base_stor_len);
		जाओ fail;
	पूर्ण

	अगर (uv_init(uv_stor_base, uv_info.uv_base_stor_len)) अणु
		memblock_मुक्त(uv_stor_base, uv_info.uv_base_stor_len);
		जाओ fail;
	पूर्ण

	pr_info("Reserving %luMB as ultravisor base storage\n",
		uv_info.uv_base_stor_len >> 20);
	वापस;
fail:
	pr_info("Disabling support for protected virtualization");
	prot_virt_host = 0;
पूर्ण

व्योम adjust_to_uv_max(अचिन्हित दीर्घ *vmax)
अणु
	अगर (uv_info.max_sec_stor_addr)
		*vmax = min_t(अचिन्हित दीर्घ, *vmax, uv_info.max_sec_stor_addr);
पूर्ण

/*
 * Requests the Ultravisor to pin the page in the shared state. This will
 * cause an पूर्णांकercept when the guest attempts to unshare the pinned page.
 */
अटल पूर्णांक uv_pin_shared(अचिन्हित दीर्घ paddr)
अणु
	काष्ठा uv_cb_cfs uvcb = अणु
		.header.cmd = UVC_CMD_PIN_PAGE_SHARED,
		.header.len = माप(uvcb),
		.paddr = paddr,
	पूर्ण;

	अगर (uv_call(0, (u64)&uvcb))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Requests the Ultravisor to destroy a guest page and make it
 * accessible to the host. The destroy clears the page instead of
 * exporting.
 *
 * @paddr: Absolute host address of page to be destroyed
 */
पूर्णांक uv_destroy_page(अचिन्हित दीर्घ paddr)
अणु
	काष्ठा uv_cb_cfs uvcb = अणु
		.header.cmd = UVC_CMD_DESTR_SEC_STOR,
		.header.len = माप(uvcb),
		.paddr = paddr
	पूर्ण;

	अगर (uv_call(0, (u64)&uvcb)) अणु
		/*
		 * Older firmware uses 107/d as an indication of a non secure
		 * page. Let us emulate the newer variant (no-op).
		 */
		अगर (uvcb.header.rc == 0x107 && uvcb.header.rrc == 0xd)
			वापस 0;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Requests the Ultravisor to encrypt a guest page and make it
 * accessible to the host क्रम paging (export).
 *
 * @paddr: Absolute host address of page to be exported
 */
पूर्णांक uv_convert_from_secure(अचिन्हित दीर्घ paddr)
अणु
	काष्ठा uv_cb_cfs uvcb = अणु
		.header.cmd = UVC_CMD_CONV_FROM_SEC_STOR,
		.header.len = माप(uvcb),
		.paddr = paddr
	पूर्ण;

	अगर (uv_call(0, (u64)&uvcb))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Calculate the expected ref_count क्रम a page that would otherwise have no
 * further pins. This was cribbed from similar functions in other places in
 * the kernel, but with some slight modअगरications. We know that a secure
 * page can not be a huge page क्रम example.
 */
अटल पूर्णांक expected_page_refs(काष्ठा page *page)
अणु
	पूर्णांक res;

	res = page_mapcount(page);
	अगर (PageSwapCache(page)) अणु
		res++;
	पूर्ण अन्यथा अगर (page_mapping(page)) अणु
		res++;
		अगर (page_has_निजी(page))
			res++;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक make_secure_pte(pte_t *ptep, अचिन्हित दीर्घ addr,
			   काष्ठा page *exp_page, काष्ठा uv_cb_header *uvcb)
अणु
	pte_t entry = READ_ONCE(*ptep);
	काष्ठा page *page;
	पूर्णांक expected, rc = 0;

	अगर (!pte_present(entry))
		वापस -ENXIO;
	अगर (pte_val(entry) & _PAGE_INVALID)
		वापस -ENXIO;

	page = pte_page(entry);
	अगर (page != exp_page)
		वापस -ENXIO;
	अगर (PageWriteback(page))
		वापस -EAGAIN;
	expected = expected_page_refs(page);
	अगर (!page_ref_मुक्तze(page, expected))
		वापस -EBUSY;
	set_bit(PG_arch_1, &page->flags);
	rc = uv_call(0, (u64)uvcb);
	page_ref_unमुक्तze(page, expected);
	/* Return -ENXIO अगर the page was not mapped, -EINVAL otherwise */
	अगर (rc)
		rc = uvcb->rc == 0x10a ? -ENXIO : -EINVAL;
	वापस rc;
पूर्ण

/*
 * Requests the Ultravisor to make a page accessible to a guest.
 * If it's brought in the first समय, it will be cleared. If
 * it has been exported beक्रमe, it will be decrypted and पूर्णांकegrity
 * checked.
 */
पूर्णांक gmap_make_secure(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, व्योम *uvcb)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	bool local_drain = false;
	spinlock_t *ptelock;
	अचिन्हित दीर्घ uaddr;
	काष्ठा page *page;
	pte_t *ptep;
	पूर्णांक rc;

again:
	rc = -EFAULT;
	mmap_पढ़ो_lock(gmap->mm);

	uaddr = __gmap_translate(gmap, gaddr);
	अगर (IS_ERR_VALUE(uaddr))
		जाओ out;
	vma = find_vma(gmap->mm, uaddr);
	अगर (!vma)
		जाओ out;
	/*
	 * Secure pages cannot be huge and userspace should not combine both.
	 * In हाल userspace करोes it anyway this will result in an -EFAULT क्रम
	 * the unpack. The guest is thus never reaching secure mode. If
	 * userspace is playing dirty tricky with mapping huge pages later
	 * on this will result in a segmentation fault.
	 */
	अगर (is_vm_hugetlb_page(vma))
		जाओ out;

	rc = -ENXIO;
	page = follow_page(vma, uaddr, FOLL_WRITE);
	अगर (IS_ERR_OR_शून्य(page))
		जाओ out;

	lock_page(page);
	ptep = get_locked_pte(gmap->mm, uaddr, &ptelock);
	rc = make_secure_pte(ptep, uaddr, page, uvcb);
	pte_unmap_unlock(ptep, ptelock);
	unlock_page(page);
out:
	mmap_पढ़ो_unlock(gmap->mm);

	अगर (rc == -EAGAIN) अणु
		रुको_on_page_ग_लिखोback(page);
	पूर्ण अन्यथा अगर (rc == -EBUSY) अणु
		/*
		 * If we have tried a local drain and the page refcount
		 * still करोes not match our expected safe value, try with a
		 * प्रणाली wide drain. This is needed अगर the pagevecs holding
		 * the page are on a dअगरferent CPU.
		 */
		अगर (local_drain) अणु
			lru_add_drain_all();
			/* We give up here, and let the caller try again */
			वापस -EAGAIN;
		पूर्ण
		/*
		 * We are here अगर the page refcount करोes not match the
		 * expected safe value. The मुख्य culprits are usually
		 * pagevecs. With lru_add_drain() we drain the pagevecs
		 * on the local CPU so that hopefully the refcount will
		 * reach the expected safe value.
		 */
		lru_add_drain();
		local_drain = true;
		/* And now we try again immediately after draining */
		जाओ again;
	पूर्ण अन्यथा अगर (rc == -ENXIO) अणु
		अगर (gmap_fault(gmap, gaddr, FAULT_FLAG_WRITE))
			वापस -EFAULT;
		वापस -EAGAIN;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_make_secure);

पूर्णांक gmap_convert_to_secure(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	काष्ठा uv_cb_cts uvcb = अणु
		.header.cmd = UVC_CMD_CONV_TO_SEC_STOR,
		.header.len = माप(uvcb),
		.guest_handle = gmap->guest_handle,
		.gaddr = gaddr,
	पूर्ण;

	वापस gmap_make_secure(gmap, gaddr, &uvcb);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_convert_to_secure);

/*
 * To be called with the page locked or with an extra reference! This will
 * prevent gmap_make_secure from touching the page concurrently. Having 2
 * parallel make_page_accessible is fine, as the UV calls will become a
 * no-op अगर the page is alपढ़ोy exported.
 */
पूर्णांक arch_make_page_accessible(काष्ठा page *page)
अणु
	पूर्णांक rc = 0;

	/* Hugepage cannot be रक्षित, so nothing to करो */
	अगर (PageHuge(page))
		वापस 0;

	/*
	 * PG_arch_1 is used in 3 places:
	 * 1. क्रम kernel page tables during early boot
	 * 2. क्रम storage keys of huge pages and KVM
	 * 3. As an indication that this page might be secure. This can
	 *    overindicate, e.g. we set the bit beक्रमe calling
	 *    convert_to_secure.
	 * As secure pages are never huge, all 3 variants can co-exists.
	 */
	अगर (!test_bit(PG_arch_1, &page->flags))
		वापस 0;

	rc = uv_pin_shared(page_to_phys(page));
	अगर (!rc) अणु
		clear_bit(PG_arch_1, &page->flags);
		वापस 0;
	पूर्ण

	rc = uv_convert_from_secure(page_to_phys(page));
	अगर (!rc) अणु
		clear_bit(PG_arch_1, &page->flags);
		वापस 0;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(arch_make_page_accessible);

#पूर्ण_अगर

#अगर defined(CONFIG_PROTECTED_VIRTUALIZATION_GUEST) || IS_ENABLED(CONFIG_KVM)
अटल sमाप_प्रकार uv_query_facilities(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "%lx\n%lx\n%lx\n%lx\n",
			uv_info.inst_calls_list[0],
			uv_info.inst_calls_list[1],
			uv_info.inst_calls_list[2],
			uv_info.inst_calls_list[3]);
पूर्ण

अटल काष्ठा kobj_attribute uv_query_facilities_attr =
	__ATTR(facilities, 0444, uv_query_facilities, शून्य);

अटल sमाप_प्रकार uv_query_max_guest_cpus(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "%d\n",
			uv_info.max_guest_cpu_id + 1);
पूर्ण

अटल काष्ठा kobj_attribute uv_query_max_guest_cpus_attr =
	__ATTR(max_cpus, 0444, uv_query_max_guest_cpus, शून्य);

अटल sमाप_प्रकार uv_query_max_guest_vms(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "%d\n",
			uv_info.max_num_sec_conf);
पूर्ण

अटल काष्ठा kobj_attribute uv_query_max_guest_vms_attr =
	__ATTR(max_guests, 0444, uv_query_max_guest_vms, शून्य);

अटल sमाप_प्रकार uv_query_max_guest_addr(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "%lx\n",
			uv_info.max_sec_stor_addr);
पूर्ण

अटल काष्ठा kobj_attribute uv_query_max_guest_addr_attr =
	__ATTR(max_address, 0444, uv_query_max_guest_addr, शून्य);

अटल काष्ठा attribute *uv_query_attrs[] = अणु
	&uv_query_facilities_attr.attr,
	&uv_query_max_guest_cpus_attr.attr,
	&uv_query_max_guest_vms_attr.attr,
	&uv_query_max_guest_addr_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group uv_query_attr_group = अणु
	.attrs = uv_query_attrs,
पूर्ण;

अटल sमाप_प्रकार uv_is_prot_virt_guest(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक val = 0;

#अगर_घोषित CONFIG_PROTECTED_VIRTUALIZATION_GUEST
	val = prot_virt_guest;
#पूर्ण_अगर
	वापस scnम_लिखो(page, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार uv_is_prot_virt_host(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक val = 0;

#अगर IS_ENABLED(CONFIG_KVM)
	val = prot_virt_host;
#पूर्ण_अगर

	वापस scnम_लिखो(page, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल काष्ठा kobj_attribute uv_prot_virt_guest =
	__ATTR(prot_virt_guest, 0444, uv_is_prot_virt_guest, शून्य);

अटल काष्ठा kobj_attribute uv_prot_virt_host =
	__ATTR(prot_virt_host, 0444, uv_is_prot_virt_host, शून्य);

अटल स्थिर काष्ठा attribute *uv_prot_virt_attrs[] = अणु
	&uv_prot_virt_guest.attr,
	&uv_prot_virt_host.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kset *uv_query_kset;
अटल काष्ठा kobject *uv_kobj;

अटल पूर्णांक __init uv_info_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;

	अगर (!test_facility(158))
		वापस 0;

	uv_kobj = kobject_create_and_add("uv", firmware_kobj);
	अगर (!uv_kobj)
		वापस -ENOMEM;

	rc = sysfs_create_files(uv_kobj, uv_prot_virt_attrs);
	अगर (rc)
		जाओ out_kobj;

	uv_query_kset = kset_create_and_add("query", शून्य, uv_kobj);
	अगर (!uv_query_kset) अणु
		rc = -ENOMEM;
		जाओ out_ind_files;
	पूर्ण

	rc = sysfs_create_group(&uv_query_kset->kobj, &uv_query_attr_group);
	अगर (!rc)
		वापस 0;

	kset_unरेजिस्टर(uv_query_kset);
out_ind_files:
	sysfs_हटाओ_files(uv_kobj, uv_prot_virt_attrs);
out_kobj:
	kobject_del(uv_kobj);
	kobject_put(uv_kobj);
	वापस rc;
पूर्ण
device_initcall(uv_info_init);
#पूर्ण_अगर

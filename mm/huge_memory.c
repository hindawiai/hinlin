<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2009  Red Hat, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/shrinker.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/swapops.h>
#समावेश <linux/dax.h>
#समावेश <linux/khugepaged.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/mman.h>
#समावेश <linux/memremap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/migrate.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/oom.h>
#समावेश <linux/numa.h>
#समावेश <linux/page_owner.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश "internal.h"

/*
 * By शेष, transparent hugepage support is disabled in order to aव्योम
 * risking an increased memory footprपूर्णांक क्रम applications that are not
 * guaranteed to benefit from it. When transparent hugepage support is
 * enabled, it is क्रम all mappings, and khugepaged scans all mappings.
 * Defrag is invoked by khugepaged hugepage allocations and by page faults
 * क्रम all hugepage allocations.
 */
अचिन्हित दीर्घ transparent_hugepage_flags __पढ़ो_mostly =
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE_ALWAYS
	(1<<TRANSPARENT_HUGEPAGE_FLAG)|
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE_MADVISE
	(1<<TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG)|
#पूर्ण_अगर
	(1<<TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG)|
	(1<<TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG)|
	(1<<TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG);

अटल काष्ठा shrinker deferred_split_shrinker;

अटल atomic_t huge_zero_refcount;
काष्ठा page *huge_zero_page __पढ़ो_mostly;
अचिन्हित दीर्घ huge_zero_pfn __पढ़ो_mostly = ~0UL;

bool transparent_hugepage_enabled(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* The addr is used to check अगर the vma size fits */
	अचिन्हित दीर्घ addr = (vma->vm_end & HPAGE_PMD_MASK) - HPAGE_PMD_SIZE;

	अगर (!transhuge_vma_suitable(vma, addr))
		वापस false;
	अगर (vma_is_anonymous(vma))
		वापस __transparent_hugepage_enabled(vma);
	अगर (vma_is_shmem(vma))
		वापस shmem_huge_enabled(vma);

	वापस false;
पूर्ण

अटल bool get_huge_zero_page(व्योम)
अणु
	काष्ठा page *zero_page;
retry:
	अगर (likely(atomic_inc_not_zero(&huge_zero_refcount)))
		वापस true;

	zero_page = alloc_pages((GFP_TRANSHUGE | __GFP_ZERO) & ~__GFP_MOVABLE,
			HPAGE_PMD_ORDER);
	अगर (!zero_page) अणु
		count_vm_event(THP_ZERO_PAGE_ALLOC_FAILED);
		वापस false;
	पूर्ण
	count_vm_event(THP_ZERO_PAGE_ALLOC);
	preempt_disable();
	अगर (cmpxchg(&huge_zero_page, शून्य, zero_page)) अणु
		preempt_enable();
		__मुक्त_pages(zero_page, compound_order(zero_page));
		जाओ retry;
	पूर्ण
	WRITE_ONCE(huge_zero_pfn, page_to_pfn(zero_page));

	/* We take additional reference here. It will be put back by shrinker */
	atomic_set(&huge_zero_refcount, 2);
	preempt_enable();
	वापस true;
पूर्ण

अटल व्योम put_huge_zero_page(व्योम)
अणु
	/*
	 * Counter should never go to zero here. Only shrinker can put
	 * last reference.
	 */
	BUG_ON(atomic_dec_and_test(&huge_zero_refcount));
पूर्ण

काष्ठा page *mm_get_huge_zero_page(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (test_bit(MMF_HUGE_ZERO_PAGE, &mm->flags))
		वापस READ_ONCE(huge_zero_page);

	अगर (!get_huge_zero_page())
		वापस शून्य;

	अगर (test_and_set_bit(MMF_HUGE_ZERO_PAGE, &mm->flags))
		put_huge_zero_page();

	वापस READ_ONCE(huge_zero_page);
पूर्ण

व्योम mm_put_huge_zero_page(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (test_bit(MMF_HUGE_ZERO_PAGE, &mm->flags))
		put_huge_zero_page();
पूर्ण

अटल अचिन्हित दीर्घ shrink_huge_zero_page_count(काष्ठा shrinker *shrink,
					काष्ठा shrink_control *sc)
अणु
	/* we can मुक्त zero page only अगर last reference reमुख्यs */
	वापस atomic_पढ़ो(&huge_zero_refcount) == 1 ? HPAGE_PMD_NR : 0;
पूर्ण

अटल अचिन्हित दीर्घ shrink_huge_zero_page_scan(काष्ठा shrinker *shrink,
				       काष्ठा shrink_control *sc)
अणु
	अगर (atomic_cmpxchg(&huge_zero_refcount, 1, 0) == 1) अणु
		काष्ठा page *zero_page = xchg(&huge_zero_page, शून्य);
		BUG_ON(zero_page == शून्य);
		WRITE_ONCE(huge_zero_pfn, ~0UL);
		__मुक्त_pages(zero_page, compound_order(zero_page));
		वापस HPAGE_PMD_NR;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा shrinker huge_zero_page_shrinker = अणु
	.count_objects = shrink_huge_zero_page_count,
	.scan_objects = shrink_huge_zero_page_scan,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार enabled_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	अगर (test_bit(TRANSPARENT_HUGEPAGE_FLAG, &transparent_hugepage_flags))
		output = "[always] madvise never";
	अन्यथा अगर (test_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
			  &transparent_hugepage_flags))
		output = "always [madvise] never";
	अन्यथा
		output = "always madvise [never]";

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल sमाप_प्रकार enabled_store(काष्ठा kobject *kobj,
			     काष्ठा kobj_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = count;

	अगर (sysfs_streq(buf, "always")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "madvise")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "never")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा
		ret = -EINVAL;

	अगर (ret > 0) अणु
		पूर्णांक err = start_stop_khugepaged();
		अगर (err)
			ret = err;
	पूर्ण
	वापस ret;
पूर्ण
अटल काष्ठा kobj_attribute enabled_attr =
	__ATTR(enabled, 0644, enabled_show, enabled_store);

sमाप_प्रकार single_hugepage_flag_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf,
				  क्रमागत transparent_hugepage_flag flag)
अणु
	वापस sysfs_emit(buf, "%d\n",
			  !!test_bit(flag, &transparent_hugepage_flags));
पूर्ण

sमाप_प्रकार single_hugepage_flag_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count,
				 क्रमागत transparent_hugepage_flag flag)
अणु
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &value);
	अगर (ret < 0)
		वापस ret;
	अगर (value > 1)
		वापस -EINVAL;

	अगर (value)
		set_bit(flag, &transparent_hugepage_flags);
	अन्यथा
		clear_bit(flag, &transparent_hugepage_flags);

	वापस count;
पूर्ण

अटल sमाप_प्रकार defrag_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG,
		     &transparent_hugepage_flags))
		output = "[always] defer defer+madvise madvise never";
	अन्यथा अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG,
			  &transparent_hugepage_flags))
		output = "always [defer] defer+madvise madvise never";
	अन्यथा अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG,
			  &transparent_hugepage_flags))
		output = "always defer [defer+madvise] madvise never";
	अन्यथा अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG,
			  &transparent_hugepage_flags))
		output = "always defer defer+madvise [madvise] never";
	अन्यथा
		output = "always defer defer+madvise madvise [never]";

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण

अटल sमाप_प्रकार defrag_store(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (sysfs_streq(buf, "always")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "defer+madvise")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "defer")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "madvise")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "never")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute defrag_attr =
	__ATTR(defrag, 0644, defrag_show, defrag_store);

अटल sमाप_प्रकार use_zero_page_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस single_hugepage_flag_show(kobj, attr, buf,
					 TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG);
पूर्ण
अटल sमाप_प्रकार use_zero_page_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस single_hugepage_flag_store(kobj, attr, buf, count,
				 TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG);
पूर्ण
अटल काष्ठा kobj_attribute use_zero_page_attr =
	__ATTR(use_zero_page, 0644, use_zero_page_show, use_zero_page_store);

अटल sमाप_प्रकार hpage_pmd_size_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%lu\n", HPAGE_PMD_SIZE);
पूर्ण
अटल काष्ठा kobj_attribute hpage_pmd_size_attr =
	__ATTR_RO(hpage_pmd_size);

अटल काष्ठा attribute *hugepage_attr[] = अणु
	&enabled_attr.attr,
	&defrag_attr.attr,
	&use_zero_page_attr.attr,
	&hpage_pmd_size_attr.attr,
#अगर_घोषित CONFIG_SHMEM
	&shmem_enabled_attr.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hugepage_attr_group = अणु
	.attrs = hugepage_attr,
पूर्ण;

अटल पूर्णांक __init hugepage_init_sysfs(काष्ठा kobject **hugepage_kobj)
अणु
	पूर्णांक err;

	*hugepage_kobj = kobject_create_and_add("transparent_hugepage", mm_kobj);
	अगर (unlikely(!*hugepage_kobj)) अणु
		pr_err("failed to create transparent hugepage kobject\n");
		वापस -ENOMEM;
	पूर्ण

	err = sysfs_create_group(*hugepage_kobj, &hugepage_attr_group);
	अगर (err) अणु
		pr_err("failed to register transparent hugepage group\n");
		जाओ delete_obj;
	पूर्ण

	err = sysfs_create_group(*hugepage_kobj, &khugepaged_attr_group);
	अगर (err) अणु
		pr_err("failed to register transparent hugepage group\n");
		जाओ हटाओ_hp_group;
	पूर्ण

	वापस 0;

हटाओ_hp_group:
	sysfs_हटाओ_group(*hugepage_kobj, &hugepage_attr_group);
delete_obj:
	kobject_put(*hugepage_kobj);
	वापस err;
पूर्ण

अटल व्योम __init hugepage_निकास_sysfs(काष्ठा kobject *hugepage_kobj)
अणु
	sysfs_हटाओ_group(hugepage_kobj, &khugepaged_attr_group);
	sysfs_हटाओ_group(hugepage_kobj, &hugepage_attr_group);
	kobject_put(hugepage_kobj);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक hugepage_init_sysfs(काष्ठा kobject **hugepage_kobj)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugepage_निकास_sysfs(काष्ठा kobject *hugepage_kobj)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल पूर्णांक __init hugepage_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा kobject *hugepage_kobj;

	अगर (!has_transparent_hugepage()) अणु
		/*
		 * Hardware करोesn't support hugepages, hence disable
		 * DAX PMD support.
		 */
		transparent_hugepage_flags = 1 << TRANSPARENT_HUGEPAGE_NEVER_DAX;
		वापस -EINVAL;
	पूर्ण

	/*
	 * hugepages can't be allocated by the buddy allocator
	 */
	MAYBE_BUILD_BUG_ON(HPAGE_PMD_ORDER >= MAX_ORDER);
	/*
	 * we use page->mapping and page->index in second tail page
	 * as list_head: assuming THP order >= 2
	 */
	MAYBE_BUILD_BUG_ON(HPAGE_PMD_ORDER < 2);

	err = hugepage_init_sysfs(&hugepage_kobj);
	अगर (err)
		जाओ err_sysfs;

	err = khugepaged_init();
	अगर (err)
		जाओ err_slab;

	err = रेजिस्टर_shrinker(&huge_zero_page_shrinker);
	अगर (err)
		जाओ err_hzp_shrinker;
	err = रेजिस्टर_shrinker(&deferred_split_shrinker);
	अगर (err)
		जाओ err_split_shrinker;

	/*
	 * By शेष disable transparent hugepages on smaller प्रणालीs,
	 * where the extra memory used could hurt more than TLB overhead
	 * is likely to save.  The admin can still enable it through /sys.
	 */
	अगर (totalram_pages() < (512 << (20 - PAGE_SHIFT))) अणु
		transparent_hugepage_flags = 0;
		वापस 0;
	पूर्ण

	err = start_stop_khugepaged();
	अगर (err)
		जाओ err_khugepaged;

	वापस 0;
err_khugepaged:
	unरेजिस्टर_shrinker(&deferred_split_shrinker);
err_split_shrinker:
	unरेजिस्टर_shrinker(&huge_zero_page_shrinker);
err_hzp_shrinker:
	khugepaged_destroy();
err_slab:
	hugepage_निकास_sysfs(hugepage_kobj);
err_sysfs:
	वापस err;
पूर्ण
subsys_initcall(hugepage_init);

अटल पूर्णांक __init setup_transparent_hugepage(अक्षर *str)
अणु
	पूर्णांक ret = 0;
	अगर (!str)
		जाओ out;
	अगर (!म_भेद(str, "always")) अणु
		set_bit(TRANSPARENT_HUGEPAGE_FLAG,
			&transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
			  &transparent_hugepage_flags);
		ret = 1;
	पूर्ण अन्यथा अगर (!म_भेद(str, "madvise")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_FLAG,
			  &transparent_hugepage_flags);
		set_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
			&transparent_hugepage_flags);
		ret = 1;
	पूर्ण अन्यथा अगर (!म_भेद(str, "never")) अणु
		clear_bit(TRANSPARENT_HUGEPAGE_FLAG,
			  &transparent_hugepage_flags);
		clear_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
			  &transparent_hugepage_flags);
		ret = 1;
	पूर्ण
out:
	अगर (!ret)
		pr_warn("transparent_hugepage= cannot parse, ignored\n");
	वापस ret;
पूर्ण
__setup("transparent_hugepage=", setup_transparent_hugepage);

pmd_t maybe_pmd_mkग_लिखो(pmd_t pmd, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->vm_flags & VM_WRITE))
		pmd = pmd_mkग_लिखो(pmd);
	वापस pmd;
पूर्ण

#अगर_घोषित CONFIG_MEMCG
अटल अंतरभूत काष्ठा deferred_split *get_deferred_split_queue(काष्ठा page *page)
अणु
	काष्ठा mem_cgroup *memcg = page_memcg(compound_head(page));
	काष्ठा pglist_data *pgdat = NODE_DATA(page_to_nid(page));

	अगर (memcg)
		वापस &memcg->deferred_split_queue;
	अन्यथा
		वापस &pgdat->deferred_split_queue;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा deferred_split *get_deferred_split_queue(काष्ठा page *page)
अणु
	काष्ठा pglist_data *pgdat = NODE_DATA(page_to_nid(page));

	वापस &pgdat->deferred_split_queue;
पूर्ण
#पूर्ण_अगर

व्योम prep_transhuge_page(काष्ठा page *page)
अणु
	/*
	 * we use page->mapping and page->indexlru in second tail page
	 * as list_head: assuming THP order >= 2
	 */

	INIT_LIST_HEAD(page_deferred_list(page));
	set_compound_page_dtor(page, TRANSHUGE_PAGE_DTOR);
पूर्ण

bool is_transparent_hugepage(काष्ठा page *page)
अणु
	अगर (!PageCompound(page))
		वापस false;

	page = compound_head(page);
	वापस is_huge_zero_page(page) ||
	       page[1].compound_dtor == TRANSHUGE_PAGE_DTOR;
पूर्ण
EXPORT_SYMBOL_GPL(is_transparent_hugepage);

अटल अचिन्हित दीर्घ __thp_get_unmapped_area(काष्ठा file *filp,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		loff_t off, अचिन्हित दीर्घ flags, अचिन्हित दीर्घ size)
अणु
	loff_t off_end = off + len;
	loff_t off_align = round_up(off, size);
	अचिन्हित दीर्घ len_pad, ret;

	अगर (off_end <= off_align || (off_end - off_align) < size)
		वापस 0;

	len_pad = len + size;
	अगर (len_pad < len || (off + len_pad) < off)
		वापस 0;

	ret = current->mm->get_unmapped_area(filp, addr, len_pad,
					      off >> PAGE_SHIFT, flags);

	/*
	 * The failure might be due to length padding. The caller will retry
	 * without the padding.
	 */
	अगर (IS_ERR_VALUE(ret))
		वापस 0;

	/*
	 * Do not try to align to THP boundary अगर allocation at the address
	 * hपूर्णांक succeeds.
	 */
	अगर (ret == addr)
		वापस addr;

	ret += (off - ret) & (size - 1);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ thp_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ ret;
	loff_t off = (loff_t)pgoff << PAGE_SHIFT;

	अगर (!IS_DAX(filp->f_mapping->host) || !IS_ENABLED(CONFIG_FS_DAX_PMD))
		जाओ out;

	ret = __thp_get_unmapped_area(filp, addr, len, off, flags, PMD_SIZE);
	अगर (ret)
		वापस ret;
out:
	वापस current->mm->get_unmapped_area(filp, addr, len, pgoff, flags);
पूर्ण
EXPORT_SYMBOL_GPL(thp_get_unmapped_area);

अटल vm_fault_t __करो_huge_pmd_anonymous_page(काष्ठा vm_fault *vmf,
			काष्ठा page *page, gfp_t gfp)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	pgtable_t pgtable;
	अचिन्हित दीर्घ haddr = vmf->address & HPAGE_PMD_MASK;
	vm_fault_t ret = 0;

	VM_BUG_ON_PAGE(!PageCompound(page), page);

	अगर (mem_cgroup_अक्षरge(page, vma->vm_mm, gfp)) अणु
		put_page(page);
		count_vm_event(THP_FAULT_FALLBACK);
		count_vm_event(THP_FAULT_FALLBACK_CHARGE);
		वापस VM_FAULT_FALLBACK;
	पूर्ण
	cgroup_throttle_swaprate(page, gfp);

	pgtable = pte_alloc_one(vma->vm_mm);
	अगर (unlikely(!pgtable)) अणु
		ret = VM_FAULT_OOM;
		जाओ release;
	पूर्ण

	clear_huge_page(page, vmf->address, HPAGE_PMD_NR);
	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * clear_huge_page ग_लिखोs become visible beक्रमe the set_pmd_at()
	 * ग_लिखो.
	 */
	__SetPageUptodate(page);

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	अगर (unlikely(!pmd_none(*vmf->pmd))) अणु
		जाओ unlock_release;
	पूर्ण अन्यथा अणु
		pmd_t entry;

		ret = check_stable_address_space(vma->vm_mm);
		अगर (ret)
			जाओ unlock_release;

		/* Deliver the page fault to userland */
		अगर (userfaultfd_missing(vma)) अणु
			spin_unlock(vmf->ptl);
			put_page(page);
			pte_मुक्त(vma->vm_mm, pgtable);
			ret = handle_userfault(vmf, VM_UFFD_MISSING);
			VM_BUG_ON(ret & VM_FAULT_FALLBACK);
			वापस ret;
		पूर्ण

		entry = mk_huge_pmd(page, vma->vm_page_prot);
		entry = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(entry), vma);
		page_add_new_anon_rmap(page, vma, haddr, true);
		lru_cache_add_inactive_or_unevictable(page, vma);
		pgtable_trans_huge_deposit(vma->vm_mm, vmf->pmd, pgtable);
		set_pmd_at(vma->vm_mm, haddr, vmf->pmd, entry);
		update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
		add_mm_counter(vma->vm_mm, MM_ANONPAGES, HPAGE_PMD_NR);
		mm_inc_nr_ptes(vma->vm_mm);
		spin_unlock(vmf->ptl);
		count_vm_event(THP_FAULT_ALLOC);
		count_memcg_event_mm(vma->vm_mm, THP_FAULT_ALLOC);
	पूर्ण

	वापस 0;
unlock_release:
	spin_unlock(vmf->ptl);
release:
	अगर (pgtable)
		pte_मुक्त(vma->vm_mm, pgtable);
	put_page(page);
	वापस ret;

पूर्ण

/*
 * always: directly stall क्रम all thp allocations
 * defer: wake kswapd and fail अगर not immediately available
 * defer+madvise: wake kswapd and directly stall क्रम MADV_HUGEPAGE, otherwise
 *		  fail अगर not immediately available
 * madvise: directly stall क्रम MADV_HUGEPAGE, otherwise fail अगर not immediately
 *	    available
 * never: never stall क्रम any thp allocation
 */
gfp_t vma_thp_gfp_mask(काष्ठा vm_area_काष्ठा *vma)
अणु
	स्थिर bool vma_madvised = vma && (vma->vm_flags & VM_HUGEPAGE);

	/* Always करो synchronous compaction */
	अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG, &transparent_hugepage_flags))
		वापस GFP_TRANSHUGE | (vma_madvised ? 0 : __GFP_NORETRY);

	/* Kick kcompactd and fail quickly */
	अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags))
		वापस GFP_TRANSHUGE_LIGHT | __GFP_KSWAPD_RECLAIM;

	/* Synchronous compaction अगर madvised, otherwise kick kcompactd */
	अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags))
		वापस GFP_TRANSHUGE_LIGHT |
			(vma_madvised ? __GFP_सूचीECT_RECLAIM :
					__GFP_KSWAPD_RECLAIM);

	/* Only करो synchronous compaction अगर madvised */
	अगर (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags))
		वापस GFP_TRANSHUGE_LIGHT |
		       (vma_madvised ? __GFP_सूचीECT_RECLAIM : 0);

	वापस GFP_TRANSHUGE_LIGHT;
पूर्ण

/* Caller must hold page table lock. */
अटल व्योम set_huge_zero_page(pgtable_t pgtable, काष्ठा mm_काष्ठा *mm,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ haddr, pmd_t *pmd,
		काष्ठा page *zero_page)
अणु
	pmd_t entry;
	अगर (!pmd_none(*pmd))
		वापस;
	entry = mk_pmd(zero_page, vma->vm_page_prot);
	entry = pmd_mkhuge(entry);
	अगर (pgtable)
		pgtable_trans_huge_deposit(mm, pmd, pgtable);
	set_pmd_at(mm, haddr, pmd, entry);
	mm_inc_nr_ptes(mm);
पूर्ण

vm_fault_t करो_huge_pmd_anonymous_page(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	gfp_t gfp;
	काष्ठा page *page;
	अचिन्हित दीर्घ haddr = vmf->address & HPAGE_PMD_MASK;

	अगर (!transhuge_vma_suitable(vma, haddr))
		वापस VM_FAULT_FALLBACK;
	अगर (unlikely(anon_vma_prepare(vma)))
		वापस VM_FAULT_OOM;
	अगर (unlikely(khugepaged_enter(vma, vma->vm_flags)))
		वापस VM_FAULT_OOM;
	अगर (!(vmf->flags & FAULT_FLAG_WRITE) &&
			!mm_क्रमbids_zeropage(vma->vm_mm) &&
			transparent_hugepage_use_zero_page()) अणु
		pgtable_t pgtable;
		काष्ठा page *zero_page;
		vm_fault_t ret;
		pgtable = pte_alloc_one(vma->vm_mm);
		अगर (unlikely(!pgtable))
			वापस VM_FAULT_OOM;
		zero_page = mm_get_huge_zero_page(vma->vm_mm);
		अगर (unlikely(!zero_page)) अणु
			pte_मुक्त(vma->vm_mm, pgtable);
			count_vm_event(THP_FAULT_FALLBACK);
			वापस VM_FAULT_FALLBACK;
		पूर्ण
		vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
		ret = 0;
		अगर (pmd_none(*vmf->pmd)) अणु
			ret = check_stable_address_space(vma->vm_mm);
			अगर (ret) अणु
				spin_unlock(vmf->ptl);
				pte_मुक्त(vma->vm_mm, pgtable);
			पूर्ण अन्यथा अगर (userfaultfd_missing(vma)) अणु
				spin_unlock(vmf->ptl);
				pte_मुक्त(vma->vm_mm, pgtable);
				ret = handle_userfault(vmf, VM_UFFD_MISSING);
				VM_BUG_ON(ret & VM_FAULT_FALLBACK);
			पूर्ण अन्यथा अणु
				set_huge_zero_page(pgtable, vma->vm_mm, vma,
						   haddr, vmf->pmd, zero_page);
				update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
				spin_unlock(vmf->ptl);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock(vmf->ptl);
			pte_मुक्त(vma->vm_mm, pgtable);
		पूर्ण
		वापस ret;
	पूर्ण
	gfp = vma_thp_gfp_mask(vma);
	page = alloc_hugepage_vma(gfp, vma, haddr, HPAGE_PMD_ORDER);
	अगर (unlikely(!page)) अणु
		count_vm_event(THP_FAULT_FALLBACK);
		वापस VM_FAULT_FALLBACK;
	पूर्ण
	prep_transhuge_page(page);
	वापस __करो_huge_pmd_anonymous_page(vmf, page, gfp);
पूर्ण

अटल व्योम insert_pfn_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pmd_t *pmd, pfn_t pfn, pgprot_t prot, bool ग_लिखो,
		pgtable_t pgtable)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pmd_t entry;
	spinlock_t *ptl;

	ptl = pmd_lock(mm, pmd);
	अगर (!pmd_none(*pmd)) अणु
		अगर (ग_लिखो) अणु
			अगर (pmd_pfn(*pmd) != pfn_t_to_pfn(pfn)) अणु
				WARN_ON_ONCE(!is_huge_zero_pmd(*pmd));
				जाओ out_unlock;
			पूर्ण
			entry = pmd_mkyoung(*pmd);
			entry = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(entry), vma);
			अगर (pmdp_set_access_flags(vma, addr, pmd, entry, 1))
				update_mmu_cache_pmd(vma, addr, pmd);
		पूर्ण

		जाओ out_unlock;
	पूर्ण

	entry = pmd_mkhuge(pfn_t_pmd(pfn, prot));
	अगर (pfn_t_devmap(pfn))
		entry = pmd_mkdevmap(entry);
	अगर (ग_लिखो) अणु
		entry = pmd_mkyoung(pmd_सूची_गढ़ोty(entry));
		entry = maybe_pmd_mkग_लिखो(entry, vma);
	पूर्ण

	अगर (pgtable) अणु
		pgtable_trans_huge_deposit(mm, pmd, pgtable);
		mm_inc_nr_ptes(mm);
		pgtable = शून्य;
	पूर्ण

	set_pmd_at(mm, addr, pmd, entry);
	update_mmu_cache_pmd(vma, addr, pmd);

out_unlock:
	spin_unlock(ptl);
	अगर (pgtable)
		pte_मुक्त(mm, pgtable);
पूर्ण

/**
 * vmf_insert_pfn_pmd_prot - insert a pmd size pfn
 * @vmf: Structure describing the fault
 * @pfn: pfn to insert
 * @pgprot: page protection to use
 * @ग_लिखो: whether it's a ग_लिखो fault
 *
 * Insert a pmd size pfn. See vmf_insert_pfn() क्रम additional info and
 * also consult the vmf_insert_mixed_prot() करोcumentation when
 * @pgprot != @vmf->vma->vm_page_prot.
 *
 * Return: vm_fault_t value.
 */
vm_fault_t vmf_insert_pfn_pmd_prot(काष्ठा vm_fault *vmf, pfn_t pfn,
				   pgprot_t pgprot, bool ग_लिखो)
अणु
	अचिन्हित दीर्घ addr = vmf->address & PMD_MASK;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	pgtable_t pgtable = शून्य;

	/*
	 * If we had pmd_special, we could aव्योम all these restrictions,
	 * but we need to be consistent with PTEs and architectures that
	 * can't support a 'special' bit.
	 */
	BUG_ON(!(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) &&
			!pfn_t_devmap(pfn));
	BUG_ON((vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) ==
						(VM_PFNMAP|VM_MIXEDMAP));
	BUG_ON((vma->vm_flags & VM_PFNMAP) && is_cow_mapping(vma->vm_flags));

	अगर (addr < vma->vm_start || addr >= vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	अगर (arch_needs_pgtable_deposit()) अणु
		pgtable = pte_alloc_one(vma->vm_mm);
		अगर (!pgtable)
			वापस VM_FAULT_OOM;
	पूर्ण

	track_pfn_insert(vma, &pgprot, pfn);

	insert_pfn_pmd(vma, addr, vmf->pmd, pfn, pgprot, ग_लिखो, pgtable);
	वापस VM_FAULT_NOPAGE;
पूर्ण
EXPORT_SYMBOL_GPL(vmf_insert_pfn_pmd_prot);

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल pud_t maybe_pud_mkग_लिखो(pud_t pud, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->vm_flags & VM_WRITE))
		pud = pud_mkग_लिखो(pud);
	वापस pud;
पूर्ण

अटल व्योम insert_pfn_pud(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pud_t *pud, pfn_t pfn, pgprot_t prot, bool ग_लिखो)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pud_t entry;
	spinlock_t *ptl;

	ptl = pud_lock(mm, pud);
	अगर (!pud_none(*pud)) अणु
		अगर (ग_लिखो) अणु
			अगर (pud_pfn(*pud) != pfn_t_to_pfn(pfn)) अणु
				WARN_ON_ONCE(!is_huge_zero_pud(*pud));
				जाओ out_unlock;
			पूर्ण
			entry = pud_mkyoung(*pud);
			entry = maybe_pud_mkग_लिखो(pud_सूची_गढ़ोty(entry), vma);
			अगर (pudp_set_access_flags(vma, addr, pud, entry, 1))
				update_mmu_cache_pud(vma, addr, pud);
		पूर्ण
		जाओ out_unlock;
	पूर्ण

	entry = pud_mkhuge(pfn_t_pud(pfn, prot));
	अगर (pfn_t_devmap(pfn))
		entry = pud_mkdevmap(entry);
	अगर (ग_लिखो) अणु
		entry = pud_mkyoung(pud_सूची_गढ़ोty(entry));
		entry = maybe_pud_mkग_लिखो(entry, vma);
	पूर्ण
	set_pud_at(mm, addr, pud, entry);
	update_mmu_cache_pud(vma, addr, pud);

out_unlock:
	spin_unlock(ptl);
पूर्ण

/**
 * vmf_insert_pfn_pud_prot - insert a pud size pfn
 * @vmf: Structure describing the fault
 * @pfn: pfn to insert
 * @pgprot: page protection to use
 * @ग_लिखो: whether it's a ग_लिखो fault
 *
 * Insert a pud size pfn. See vmf_insert_pfn() क्रम additional info and
 * also consult the vmf_insert_mixed_prot() करोcumentation when
 * @pgprot != @vmf->vma->vm_page_prot.
 *
 * Return: vm_fault_t value.
 */
vm_fault_t vmf_insert_pfn_pud_prot(काष्ठा vm_fault *vmf, pfn_t pfn,
				   pgprot_t pgprot, bool ग_लिखो)
अणु
	अचिन्हित दीर्घ addr = vmf->address & PUD_MASK;
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;

	/*
	 * If we had pud_special, we could aव्योम all these restrictions,
	 * but we need to be consistent with PTEs and architectures that
	 * can't support a 'special' bit.
	 */
	BUG_ON(!(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) &&
			!pfn_t_devmap(pfn));
	BUG_ON((vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) ==
						(VM_PFNMAP|VM_MIXEDMAP));
	BUG_ON((vma->vm_flags & VM_PFNMAP) && is_cow_mapping(vma->vm_flags));

	अगर (addr < vma->vm_start || addr >= vma->vm_end)
		वापस VM_FAULT_SIGBUS;

	track_pfn_insert(vma, &pgprot, pfn);

	insert_pfn_pud(vma, addr, vmf->pud, pfn, pgprot, ग_लिखो);
	वापस VM_FAULT_NOPAGE;
पूर्ण
EXPORT_SYMBOL_GPL(vmf_insert_pfn_pud_prot);
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */

अटल व्योम touch_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pmd_t *pmd, पूर्णांक flags)
अणु
	pmd_t _pmd;

	_pmd = pmd_mkyoung(*pmd);
	अगर (flags & FOLL_WRITE)
		_pmd = pmd_सूची_गढ़ोty(_pmd);
	अगर (pmdp_set_access_flags(vma, addr & HPAGE_PMD_MASK,
				pmd, _pmd, flags & FOLL_WRITE))
		update_mmu_cache_pmd(vma, addr, pmd);
पूर्ण

काष्ठा page *follow_devmap_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pmd_t *pmd, पूर्णांक flags, काष्ठा dev_pagemap **pgmap)
अणु
	अचिन्हित दीर्घ pfn = pmd_pfn(*pmd);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *page;

	निश्चित_spin_locked(pmd_lockptr(mm, pmd));

	/*
	 * When we COW a devmap PMD entry, we split it पूर्णांकo PTEs, so we should
	 * not be in this function with `flags & FOLL_COW` set.
	 */
	WARN_ONCE(flags & FOLL_COW, "mm: In follow_devmap_pmd with FOLL_COW set");

	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE((flags & (FOLL_PIN | FOLL_GET)) ==
			 (FOLL_PIN | FOLL_GET)))
		वापस शून्य;

	अगर (flags & FOLL_WRITE && !pmd_ग_लिखो(*pmd))
		वापस शून्य;

	अगर (pmd_present(*pmd) && pmd_devmap(*pmd))
		/* pass */;
	अन्यथा
		वापस शून्य;

	अगर (flags & FOLL_TOUCH)
		touch_pmd(vma, addr, pmd, flags);

	/*
	 * device mapped pages can only be वापसed अगर the
	 * caller will manage the page reference count.
	 */
	अगर (!(flags & (FOLL_GET | FOLL_PIN)))
		वापस ERR_PTR(-EEXIST);

	pfn += (addr & ~PMD_MASK) >> PAGE_SHIFT;
	*pgmap = get_dev_pagemap(pfn, *pgmap);
	अगर (!*pgmap)
		वापस ERR_PTR(-EFAULT);
	page = pfn_to_page(pfn);
	अगर (!try_grab_page(page, flags))
		page = ERR_PTR(-ENOMEM);

	वापस page;
पूर्ण

पूर्णांक copy_huge_pmd(काष्ठा mm_काष्ठा *dst_mm, काष्ठा mm_काष्ठा *src_mm,
		  pmd_t *dst_pmd, pmd_t *src_pmd, अचिन्हित दीर्घ addr,
		  काष्ठा vm_area_काष्ठा *vma)
अणु
	spinlock_t *dst_ptl, *src_ptl;
	काष्ठा page *src_page;
	pmd_t pmd;
	pgtable_t pgtable = शून्य;
	पूर्णांक ret = -ENOMEM;

	/* Skip अगर can be re-fill on fault */
	अगर (!vma_is_anonymous(vma))
		वापस 0;

	pgtable = pte_alloc_one(dst_mm);
	अगर (unlikely(!pgtable))
		जाओ out;

	dst_ptl = pmd_lock(dst_mm, dst_pmd);
	src_ptl = pmd_lockptr(src_mm, src_pmd);
	spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);

	ret = -EAGAIN;
	pmd = *src_pmd;

	/*
	 * Make sure the _PAGE_UFFD_WP bit is cleared अगर the new VMA
	 * करोes not have the VM_UFFD_WP, which means that the uffd
	 * विभाजन event is not enabled.
	 */
	अगर (!(vma->vm_flags & VM_UFFD_WP))
		pmd = pmd_clear_uffd_wp(pmd);

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
	अगर (unlikely(is_swap_pmd(pmd))) अणु
		swp_entry_t entry = pmd_to_swp_entry(pmd);

		VM_BUG_ON(!is_pmd_migration_entry(pmd));
		अगर (is_ग_लिखो_migration_entry(entry)) अणु
			make_migration_entry_पढ़ो(&entry);
			pmd = swp_entry_to_pmd(entry);
			अगर (pmd_swp_soft_dirty(*src_pmd))
				pmd = pmd_swp_mksoft_dirty(pmd);
			set_pmd_at(src_mm, addr, src_pmd, pmd);
		पूर्ण
		add_mm_counter(dst_mm, MM_ANONPAGES, HPAGE_PMD_NR);
		mm_inc_nr_ptes(dst_mm);
		pgtable_trans_huge_deposit(dst_mm, dst_pmd, pgtable);
		set_pmd_at(dst_mm, addr, dst_pmd, pmd);
		ret = 0;
		जाओ out_unlock;
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(!pmd_trans_huge(pmd))) अणु
		pte_मुक्त(dst_mm, pgtable);
		जाओ out_unlock;
	पूर्ण
	/*
	 * When page table lock is held, the huge zero pmd should not be
	 * under splitting since we करोn't split the page itself, only pmd to
	 * a page table.
	 */
	अगर (is_huge_zero_pmd(pmd)) अणु
		काष्ठा page *zero_page;
		/*
		 * get_huge_zero_page() will never allocate a new page here,
		 * since we alपढ़ोy have a zero page to copy. It just takes a
		 * reference.
		 */
		zero_page = mm_get_huge_zero_page(dst_mm);
		set_huge_zero_page(pgtable, dst_mm, vma, addr, dst_pmd,
				zero_page);
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	src_page = pmd_page(pmd);
	VM_BUG_ON_PAGE(!PageHead(src_page), src_page);

	/*
	 * If this page is a potentially pinned page, split and retry the fault
	 * with smaller page size.  Normally this should not happen because the
	 * userspace should use MADV_DONTFORK upon pinned regions.  This is a
	 * best efक्रमt that the pinned pages won't be replaced by another
	 * अक्रमom page during the coming copy-on-ग_लिखो.
	 */
	अगर (unlikely(page_needs_cow_क्रम_dma(vma, src_page))) अणु
		pte_मुक्त(dst_mm, pgtable);
		spin_unlock(src_ptl);
		spin_unlock(dst_ptl);
		__split_huge_pmd(vma, src_pmd, addr, false, शून्य);
		वापस -EAGAIN;
	पूर्ण

	get_page(src_page);
	page_dup_rmap(src_page, true);
	add_mm_counter(dst_mm, MM_ANONPAGES, HPAGE_PMD_NR);
	mm_inc_nr_ptes(dst_mm);
	pgtable_trans_huge_deposit(dst_mm, dst_pmd, pgtable);

	pmdp_set_wrprotect(src_mm, addr, src_pmd);
	pmd = pmd_mkold(pmd_wrprotect(pmd));
	set_pmd_at(dst_mm, addr, dst_pmd, pmd);

	ret = 0;
out_unlock:
	spin_unlock(src_ptl);
	spin_unlock(dst_ptl);
out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
अटल व्योम touch_pud(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pud_t *pud, पूर्णांक flags)
अणु
	pud_t _pud;

	_pud = pud_mkyoung(*pud);
	अगर (flags & FOLL_WRITE)
		_pud = pud_सूची_गढ़ोty(_pud);
	अगर (pudp_set_access_flags(vma, addr & HPAGE_PUD_MASK,
				pud, _pud, flags & FOLL_WRITE))
		update_mmu_cache_pud(vma, addr, pud);
पूर्ण

काष्ठा page *follow_devmap_pud(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pud_t *pud, पूर्णांक flags, काष्ठा dev_pagemap **pgmap)
अणु
	अचिन्हित दीर्घ pfn = pud_pfn(*pud);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *page;

	निश्चित_spin_locked(pud_lockptr(mm, pud));

	अगर (flags & FOLL_WRITE && !pud_ग_लिखो(*pud))
		वापस शून्य;

	/* FOLL_GET and FOLL_PIN are mutually exclusive. */
	अगर (WARN_ON_ONCE((flags & (FOLL_PIN | FOLL_GET)) ==
			 (FOLL_PIN | FOLL_GET)))
		वापस शून्य;

	अगर (pud_present(*pud) && pud_devmap(*pud))
		/* pass */;
	अन्यथा
		वापस शून्य;

	अगर (flags & FOLL_TOUCH)
		touch_pud(vma, addr, pud, flags);

	/*
	 * device mapped pages can only be वापसed अगर the
	 * caller will manage the page reference count.
	 *
	 * At least one of FOLL_GET | FOLL_PIN must be set, so निश्चित that here:
	 */
	अगर (!(flags & (FOLL_GET | FOLL_PIN)))
		वापस ERR_PTR(-EEXIST);

	pfn += (addr & ~PUD_MASK) >> PAGE_SHIFT;
	*pgmap = get_dev_pagemap(pfn, *pgmap);
	अगर (!*pgmap)
		वापस ERR_PTR(-EFAULT);
	page = pfn_to_page(pfn);
	अगर (!try_grab_page(page, flags))
		page = ERR_PTR(-ENOMEM);

	वापस page;
पूर्ण

पूर्णांक copy_huge_pud(काष्ठा mm_काष्ठा *dst_mm, काष्ठा mm_काष्ठा *src_mm,
		  pud_t *dst_pud, pud_t *src_pud, अचिन्हित दीर्घ addr,
		  काष्ठा vm_area_काष्ठा *vma)
अणु
	spinlock_t *dst_ptl, *src_ptl;
	pud_t pud;
	पूर्णांक ret;

	dst_ptl = pud_lock(dst_mm, dst_pud);
	src_ptl = pud_lockptr(src_mm, src_pud);
	spin_lock_nested(src_ptl, SINGLE_DEPTH_NESTING);

	ret = -EAGAIN;
	pud = *src_pud;
	अगर (unlikely(!pud_trans_huge(pud) && !pud_devmap(pud)))
		जाओ out_unlock;

	/*
	 * When page table lock is held, the huge zero pud should not be
	 * under splitting since we करोn't split the page itself, only pud to
	 * a page table.
	 */
	अगर (is_huge_zero_pud(pud)) अणु
		/* No huge zero pud yet */
	पूर्ण

	/* Please refer to comments in copy_huge_pmd() */
	अगर (unlikely(page_needs_cow_क्रम_dma(vma, pud_page(pud)))) अणु
		spin_unlock(src_ptl);
		spin_unlock(dst_ptl);
		__split_huge_pud(vma, src_pud, addr);
		वापस -EAGAIN;
	पूर्ण

	pudp_set_wrprotect(src_mm, addr, src_pud);
	pud = pud_mkold(pud_wrprotect(pud));
	set_pud_at(dst_mm, addr, dst_pud, pud);

	ret = 0;
out_unlock:
	spin_unlock(src_ptl);
	spin_unlock(dst_ptl);
	वापस ret;
पूर्ण

व्योम huge_pud_set_accessed(काष्ठा vm_fault *vmf, pud_t orig_pud)
अणु
	pud_t entry;
	अचिन्हित दीर्घ haddr;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;

	vmf->ptl = pud_lock(vmf->vma->vm_mm, vmf->pud);
	अगर (unlikely(!pud_same(*vmf->pud, orig_pud)))
		जाओ unlock;

	entry = pud_mkyoung(orig_pud);
	अगर (ग_लिखो)
		entry = pud_सूची_गढ़ोty(entry);
	haddr = vmf->address & HPAGE_PUD_MASK;
	अगर (pudp_set_access_flags(vmf->vma, haddr, vmf->pud, entry, ग_लिखो))
		update_mmu_cache_pud(vmf->vma, vmf->address, vmf->pud);

unlock:
	spin_unlock(vmf->ptl);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */

व्योम huge_pmd_set_accessed(काष्ठा vm_fault *vmf, pmd_t orig_pmd)
अणु
	pmd_t entry;
	अचिन्हित दीर्घ haddr;
	bool ग_लिखो = vmf->flags & FAULT_FLAG_WRITE;

	vmf->ptl = pmd_lock(vmf->vma->vm_mm, vmf->pmd);
	अगर (unlikely(!pmd_same(*vmf->pmd, orig_pmd)))
		जाओ unlock;

	entry = pmd_mkyoung(orig_pmd);
	अगर (ग_लिखो)
		entry = pmd_सूची_गढ़ोty(entry);
	haddr = vmf->address & HPAGE_PMD_MASK;
	अगर (pmdp_set_access_flags(vmf->vma, haddr, vmf->pmd, entry, ग_लिखो))
		update_mmu_cache_pmd(vmf->vma, vmf->address, vmf->pmd);

unlock:
	spin_unlock(vmf->ptl);
पूर्ण

vm_fault_t करो_huge_pmd_wp_page(काष्ठा vm_fault *vmf, pmd_t orig_pmd)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page;
	अचिन्हित दीर्घ haddr = vmf->address & HPAGE_PMD_MASK;

	vmf->ptl = pmd_lockptr(vma->vm_mm, vmf->pmd);
	VM_BUG_ON_VMA(!vma->anon_vma, vma);

	अगर (is_huge_zero_pmd(orig_pmd))
		जाओ fallback;

	spin_lock(vmf->ptl);

	अगर (unlikely(!pmd_same(*vmf->pmd, orig_pmd))) अणु
		spin_unlock(vmf->ptl);
		वापस 0;
	पूर्ण

	page = pmd_page(orig_pmd);
	VM_BUG_ON_PAGE(!PageHead(page), page);

	/* Lock page क्रम reuse_swap_page() */
	अगर (!trylock_page(page)) अणु
		get_page(page);
		spin_unlock(vmf->ptl);
		lock_page(page);
		spin_lock(vmf->ptl);
		अगर (unlikely(!pmd_same(*vmf->pmd, orig_pmd))) अणु
			spin_unlock(vmf->ptl);
			unlock_page(page);
			put_page(page);
			वापस 0;
		पूर्ण
		put_page(page);
	पूर्ण

	/*
	 * We can only reuse the page अगर nobody अन्यथा maps the huge page or it's
	 * part.
	 */
	अगर (reuse_swap_page(page, शून्य)) अणु
		pmd_t entry;
		entry = pmd_mkyoung(orig_pmd);
		entry = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(entry), vma);
		अगर (pmdp_set_access_flags(vma, haddr, vmf->pmd, entry, 1))
			update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
		unlock_page(page);
		spin_unlock(vmf->ptl);
		वापस VM_FAULT_WRITE;
	पूर्ण

	unlock_page(page);
	spin_unlock(vmf->ptl);
fallback:
	__split_huge_pmd(vma, vmf->pmd, vmf->address, false, शून्य);
	वापस VM_FAULT_FALLBACK;
पूर्ण

/*
 * FOLL_FORCE can ग_लिखो to even unwritable pmd's, but only
 * after we've gone through a COW cycle and they are dirty.
 */
अटल अंतरभूत bool can_follow_ग_लिखो_pmd(pmd_t pmd, अचिन्हित पूर्णांक flags)
अणु
	वापस pmd_ग_लिखो(pmd) ||
	       ((flags & FOLL_FORCE) && (flags & FOLL_COW) && pmd_dirty(pmd));
पूर्ण

काष्ठा page *follow_trans_huge_pmd(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr,
				   pmd_t *pmd,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *page = शून्य;

	निश्चित_spin_locked(pmd_lockptr(mm, pmd));

	अगर (flags & FOLL_WRITE && !can_follow_ग_लिखो_pmd(*pmd, flags))
		जाओ out;

	/* Aव्योम dumping huge zero page */
	अगर ((flags & FOLL_DUMP) && is_huge_zero_pmd(*pmd))
		वापस ERR_PTR(-EFAULT);

	/* Full NUMA hपूर्णांकing faults to serialise migration in fault paths */
	अगर ((flags & FOLL_NUMA) && pmd_protnone(*pmd))
		जाओ out;

	page = pmd_page(*pmd);
	VM_BUG_ON_PAGE(!PageHead(page) && !is_zone_device_page(page), page);

	अगर (!try_grab_page(page, flags))
		वापस ERR_PTR(-ENOMEM);

	अगर (flags & FOLL_TOUCH)
		touch_pmd(vma, addr, pmd, flags);

	अगर ((flags & FOLL_MLOCK) && (vma->vm_flags & VM_LOCKED)) अणु
		/*
		 * We करोn't mlock() pte-mapped THPs. This way we can aव्योम
		 * leaking mlocked pages पूर्णांकo non-VM_LOCKED VMAs.
		 *
		 * For anon THP:
		 *
		 * In most हालs the pmd is the only mapping of the page as we
		 * अवरोध COW क्रम the mlock() -- see gup_flags |= FOLL_WRITE क्रम
		 * writable निजी mappings in populate_vma_page_range().
		 *
		 * The only scenario when we have the page shared here is अगर we
		 * mlocking पढ़ो-only mapping shared over विभाजन(). We skip
		 * mlocking such pages.
		 *
		 * For file THP:
		 *
		 * We can expect PageDoubleMap() to be stable under page lock:
		 * क्रम file pages we set it in page_add_file_rmap(), which
		 * requires page to be locked.
		 */

		अगर (PageAnon(page) && compound_mapcount(page) != 1)
			जाओ skip_mlock;
		अगर (PageDoubleMap(page) || !page->mapping)
			जाओ skip_mlock;
		अगर (!trylock_page(page))
			जाओ skip_mlock;
		अगर (page->mapping && !PageDoubleMap(page))
			mlock_vma_page(page);
		unlock_page(page);
	पूर्ण
skip_mlock:
	page += (addr & ~HPAGE_PMD_MASK) >> PAGE_SHIFT;
	VM_BUG_ON_PAGE(!PageCompound(page) && !is_zone_device_page(page), page);

out:
	वापस page;
पूर्ण

/* NUMA hपूर्णांकing page fault entry poपूर्णांक क्रम trans huge pmds */
vm_fault_t करो_huge_pmd_numa_page(काष्ठा vm_fault *vmf, pmd_t pmd)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा anon_vma *anon_vma = शून्य;
	काष्ठा page *page;
	अचिन्हित दीर्घ haddr = vmf->address & HPAGE_PMD_MASK;
	पूर्णांक page_nid = NUMA_NO_NODE, this_nid = numa_node_id();
	पूर्णांक target_nid, last_cpupid = -1;
	bool page_locked;
	bool migrated = false;
	bool was_writable;
	पूर्णांक flags = 0;

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	अगर (unlikely(!pmd_same(pmd, *vmf->pmd)))
		जाओ out_unlock;

	/*
	 * If there are potential migrations, रुको क्रम completion and retry
	 * without disrupting NUMA hपूर्णांकing inक्रमmation. Do not relock and
	 * check_same as the page may no दीर्घer be mapped.
	 */
	अगर (unlikely(pmd_trans_migrating(*vmf->pmd))) अणु
		page = pmd_page(*vmf->pmd);
		अगर (!get_page_unless_zero(page))
			जाओ out_unlock;
		spin_unlock(vmf->ptl);
		put_and_रुको_on_page_locked(page, TASK_UNINTERRUPTIBLE);
		जाओ out;
	पूर्ण

	page = pmd_page(pmd);
	BUG_ON(is_huge_zero_page(page));
	page_nid = page_to_nid(page);
	last_cpupid = page_cpupid_last(page);
	count_vm_numa_event(NUMA_HINT_FAULTS);
	अगर (page_nid == this_nid) अणु
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);
		flags |= TNF_FAULT_LOCAL;
	पूर्ण

	/* See similar comment in करो_numa_page क्रम explanation */
	अगर (!pmd_savedग_लिखो(pmd))
		flags |= TNF_NO_GROUP;

	/*
	 * Acquire the page lock to serialise THP migrations but aव्योम dropping
	 * page_table_lock अगर at all possible
	 */
	page_locked = trylock_page(page);
	target_nid = mpol_misplaced(page, vma, haddr);
	/* Migration could have started since the pmd_trans_migrating check */
	अगर (!page_locked) अणु
		page_nid = NUMA_NO_NODE;
		अगर (!get_page_unless_zero(page))
			जाओ out_unlock;
		spin_unlock(vmf->ptl);
		put_and_रुको_on_page_locked(page, TASK_UNINTERRUPTIBLE);
		जाओ out;
	पूर्ण अन्यथा अगर (target_nid == NUMA_NO_NODE) अणु
		/* There are no parallel migrations and page is in the right
		 * node. Clear the numa hपूर्णांकing info in this pmd.
		 */
		जाओ clear_pmdnuma;
	पूर्ण

	/*
	 * Page is misplaced. Page lock serialises migrations. Acquire anon_vma
	 * to serialises splits
	 */
	get_page(page);
	spin_unlock(vmf->ptl);
	anon_vma = page_lock_anon_vma_पढ़ो(page);

	/* Confirm the PMD did not change जबतक page_table_lock was released */
	spin_lock(vmf->ptl);
	अगर (unlikely(!pmd_same(pmd, *vmf->pmd))) अणु
		unlock_page(page);
		put_page(page);
		page_nid = NUMA_NO_NODE;
		जाओ out_unlock;
	पूर्ण

	/* Bail अगर we fail to protect against THP splits क्रम any reason */
	अगर (unlikely(!anon_vma)) अणु
		put_page(page);
		page_nid = NUMA_NO_NODE;
		जाओ clear_pmdnuma;
	पूर्ण

	/*
	 * Since we took the NUMA fault, we must have observed the !accessible
	 * bit. Make sure all other CPUs agree with that, to aव्योम them
	 * modअगरying the page we're about to migrate.
	 *
	 * Must be करोne under PTL such that we'll observe the relevant
	 * inc_tlb_flush_pending().
	 *
	 * We are not sure a pending tlb flush here is क्रम a huge page
	 * mapping or not. Hence use the tlb range variant
	 */
	अगर (mm_tlb_flush_pending(vma->vm_mm)) अणु
		flush_tlb_range(vma, haddr, haddr + HPAGE_PMD_SIZE);
		/*
		 * change_huge_pmd() released the pmd lock beक्रमe
		 * invalidating the secondary MMUs sharing the primary
		 * MMU pagetables (with ->invalidate_range()). The
		 * mmu_notअगरier_invalidate_range_end() (which
		 * पूर्णांकernally calls ->invalidate_range()) in
		 * change_pmd_range() will run after us, so we can't
		 * rely on it here and we need an explicit invalidate.
		 */
		mmu_notअगरier_invalidate_range(vma->vm_mm, haddr,
					      haddr + HPAGE_PMD_SIZE);
	पूर्ण

	/*
	 * Migrate the THP to the requested node, वापसs with page unlocked
	 * and access rights restored.
	 */
	spin_unlock(vmf->ptl);

	migrated = migrate_misplaced_transhuge_page(vma->vm_mm, vma,
				vmf->pmd, pmd, vmf->address, page, target_nid);
	अगर (migrated) अणु
		flags |= TNF_MIGRATED;
		page_nid = target_nid;
	पूर्ण अन्यथा
		flags |= TNF_MIGRATE_FAIL;

	जाओ out;
clear_pmdnuma:
	BUG_ON(!PageLocked(page));
	was_writable = pmd_savedग_लिखो(pmd);
	pmd = pmd_modअगरy(pmd, vma->vm_page_prot);
	pmd = pmd_mkyoung(pmd);
	अगर (was_writable)
		pmd = pmd_mkग_लिखो(pmd);
	set_pmd_at(vma->vm_mm, haddr, vmf->pmd, pmd);
	update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
	unlock_page(page);
out_unlock:
	spin_unlock(vmf->ptl);

out:
	अगर (anon_vma)
		page_unlock_anon_vma_पढ़ो(anon_vma);

	अगर (page_nid != NUMA_NO_NODE)
		task_numa_fault(last_cpupid, page_nid, HPAGE_PMD_NR,
				flags);

	वापस 0;
पूर्ण

/*
 * Return true अगर we करो MADV_FREE successfully on entire pmd page.
 * Otherwise, वापस false.
 */
bool madvise_मुक्त_huge_pmd(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
		pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next)
अणु
	spinlock_t *ptl;
	pmd_t orig_pmd;
	काष्ठा page *page;
	काष्ठा mm_काष्ठा *mm = tlb->mm;
	bool ret = false;

	tlb_change_page_size(tlb, HPAGE_PMD_SIZE);

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (!ptl)
		जाओ out_unlocked;

	orig_pmd = *pmd;
	अगर (is_huge_zero_pmd(orig_pmd))
		जाओ out;

	अगर (unlikely(!pmd_present(orig_pmd))) अणु
		VM_BUG_ON(thp_migration_supported() &&
				  !is_pmd_migration_entry(orig_pmd));
		जाओ out;
	पूर्ण

	page = pmd_page(orig_pmd);
	/*
	 * If other processes are mapping this page, we couldn't discard
	 * the page unless they all करो MADV_FREE so let's skip the page.
	 */
	अगर (page_mapcount(page) != 1)
		जाओ out;

	अगर (!trylock_page(page))
		जाओ out;

	/*
	 * If user want to discard part-pages of THP, split it so MADV_FREE
	 * will deactivate only them.
	 */
	अगर (next - addr != HPAGE_PMD_SIZE) अणु
		get_page(page);
		spin_unlock(ptl);
		split_huge_page(page);
		unlock_page(page);
		put_page(page);
		जाओ out_unlocked;
	पूर्ण

	अगर (PageDirty(page))
		ClearPageDirty(page);
	unlock_page(page);

	अगर (pmd_young(orig_pmd) || pmd_dirty(orig_pmd)) अणु
		pmdp_invalidate(vma, addr, pmd);
		orig_pmd = pmd_mkold(orig_pmd);
		orig_pmd = pmd_mkclean(orig_pmd);

		set_pmd_at(mm, addr, pmd, orig_pmd);
		tlb_हटाओ_pmd_tlb_entry(tlb, pmd, addr);
	पूर्ण

	mark_page_lazyमुक्त(page);
	ret = true;
out:
	spin_unlock(ptl);
out_unlocked:
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम zap_deposited_table(काष्ठा mm_काष्ठा *mm, pmd_t *pmd)
अणु
	pgtable_t pgtable;

	pgtable = pgtable_trans_huge_withdraw(mm, pmd);
	pte_मुक्त(mm, pgtable);
	mm_dec_nr_ptes(mm);
पूर्ण

पूर्णांक zap_huge_pmd(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
		 pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	pmd_t orig_pmd;
	spinlock_t *ptl;

	tlb_change_page_size(tlb, HPAGE_PMD_SIZE);

	ptl = __pmd_trans_huge_lock(pmd, vma);
	अगर (!ptl)
		वापस 0;
	/*
	 * For architectures like ppc64 we look at deposited pgtable
	 * when calling pmdp_huge_get_and_clear. So करो the
	 * pgtable_trans_huge_withdraw after finishing pmdp related
	 * operations.
	 */
	orig_pmd = pmdp_huge_get_and_clear_full(vma, addr, pmd,
						tlb->fullmm);
	tlb_हटाओ_pmd_tlb_entry(tlb, pmd, addr);
	अगर (vma_is_special_huge(vma)) अणु
		अगर (arch_needs_pgtable_deposit())
			zap_deposited_table(tlb->mm, pmd);
		spin_unlock(ptl);
		अगर (is_huge_zero_pmd(orig_pmd))
			tlb_हटाओ_page_size(tlb, pmd_page(orig_pmd), HPAGE_PMD_SIZE);
	पूर्ण अन्यथा अगर (is_huge_zero_pmd(orig_pmd)) अणु
		zap_deposited_table(tlb->mm, pmd);
		spin_unlock(ptl);
		tlb_हटाओ_page_size(tlb, pmd_page(orig_pmd), HPAGE_PMD_SIZE);
	पूर्ण अन्यथा अणु
		काष्ठा page *page = शून्य;
		पूर्णांक flush_needed = 1;

		अगर (pmd_present(orig_pmd)) अणु
			page = pmd_page(orig_pmd);
			page_हटाओ_rmap(page, true);
			VM_BUG_ON_PAGE(page_mapcount(page) < 0, page);
			VM_BUG_ON_PAGE(!PageHead(page), page);
		पूर्ण अन्यथा अगर (thp_migration_supported()) अणु
			swp_entry_t entry;

			VM_BUG_ON(!is_pmd_migration_entry(orig_pmd));
			entry = pmd_to_swp_entry(orig_pmd);
			page = migration_entry_to_page(entry);
			flush_needed = 0;
		पूर्ण अन्यथा
			WARN_ONCE(1, "Non present huge pmd without pmd migration enabled!");

		अगर (PageAnon(page)) अणु
			zap_deposited_table(tlb->mm, pmd);
			add_mm_counter(tlb->mm, MM_ANONPAGES, -HPAGE_PMD_NR);
		पूर्ण अन्यथा अणु
			अगर (arch_needs_pgtable_deposit())
				zap_deposited_table(tlb->mm, pmd);
			add_mm_counter(tlb->mm, mm_counter_file(page), -HPAGE_PMD_NR);
		पूर्ण

		spin_unlock(ptl);
		अगर (flush_needed)
			tlb_हटाओ_page_size(tlb, page, HPAGE_PMD_SIZE);
	पूर्ण
	वापस 1;
पूर्ण

#अगर_अघोषित pmd_move_must_withdraw
अटल अंतरभूत पूर्णांक pmd_move_must_withdraw(spinlock_t *new_pmd_ptl,
					 spinlock_t *old_pmd_ptl,
					 काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * With split pmd lock we also need to move pपुनः_स्मृतिated
	 * PTE page table अगर new_pmd is on dअगरferent PMD page table.
	 *
	 * We also करोn't deposit and withdraw tables क्रम file pages.
	 */
	वापस (new_pmd_ptl != old_pmd_ptl) && vma_is_anonymous(vma);
पूर्ण
#पूर्ण_अगर

अटल pmd_t move_soft_dirty_pmd(pmd_t pmd)
अणु
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
	अगर (unlikely(is_pmd_migration_entry(pmd)))
		pmd = pmd_swp_mksoft_dirty(pmd);
	अन्यथा अगर (pmd_present(pmd))
		pmd = pmd_mksoft_dirty(pmd);
#पूर्ण_अगर
	वापस pmd;
पूर्ण

bool move_huge_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ old_addr,
		  अचिन्हित दीर्घ new_addr, pmd_t *old_pmd, pmd_t *new_pmd)
अणु
	spinlock_t *old_ptl, *new_ptl;
	pmd_t pmd;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	bool क्रमce_flush = false;

	/*
	 * The destination pmd shouldn't be established, मुक्त_pgtables()
	 * should have release it.
	 */
	अगर (WARN_ON(!pmd_none(*new_pmd))) अणु
		VM_BUG_ON(pmd_trans_huge(*new_pmd));
		वापस false;
	पूर्ण

	/*
	 * We करोn't have to worry about the ordering of src and dst
	 * ptlocks because exclusive mmap_lock prevents deadlock.
	 */
	old_ptl = __pmd_trans_huge_lock(old_pmd, vma);
	अगर (old_ptl) अणु
		new_ptl = pmd_lockptr(mm, new_pmd);
		अगर (new_ptl != old_ptl)
			spin_lock_nested(new_ptl, SINGLE_DEPTH_NESTING);
		pmd = pmdp_huge_get_and_clear(mm, old_addr, old_pmd);
		अगर (pmd_present(pmd))
			क्रमce_flush = true;
		VM_BUG_ON(!pmd_none(*new_pmd));

		अगर (pmd_move_must_withdraw(new_ptl, old_ptl, vma)) अणु
			pgtable_t pgtable;
			pgtable = pgtable_trans_huge_withdraw(mm, old_pmd);
			pgtable_trans_huge_deposit(mm, new_pmd, pgtable);
		पूर्ण
		pmd = move_soft_dirty_pmd(pmd);
		set_pmd_at(mm, new_addr, new_pmd, pmd);
		अगर (क्रमce_flush)
			flush_tlb_range(vma, old_addr, old_addr + PMD_SIZE);
		अगर (new_ptl != old_ptl)
			spin_unlock(new_ptl);
		spin_unlock(old_ptl);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Returns
 *  - 0 अगर PMD could not be locked
 *  - 1 अगर PMD was locked but protections unchanged and TLB flush unnecessary
 *  - HPAGE_PMD_NR अगर protections changed and TLB flush necessary
 */
पूर्णांक change_huge_pmd(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ addr, pgprot_t newprot, अचिन्हित दीर्घ cp_flags)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	spinlock_t *ptl;
	pmd_t entry;
	bool preserve_ग_लिखो;
	पूर्णांक ret;
	bool prot_numa = cp_flags & MM_CP_PROT_NUMA;
	bool uffd_wp = cp_flags & MM_CP_UFFD_WP;
	bool uffd_wp_resolve = cp_flags & MM_CP_UFFD_WP_RESOLVE;

	ptl = __pmd_trans_huge_lock(pmd, vma);
	अगर (!ptl)
		वापस 0;

	preserve_ग_लिखो = prot_numa && pmd_ग_लिखो(*pmd);
	ret = 1;

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
	अगर (is_swap_pmd(*pmd)) अणु
		swp_entry_t entry = pmd_to_swp_entry(*pmd);

		VM_BUG_ON(!is_pmd_migration_entry(*pmd));
		अगर (is_ग_लिखो_migration_entry(entry)) अणु
			pmd_t newpmd;
			/*
			 * A protection check is dअगरficult so
			 * just be safe and disable ग_लिखो
			 */
			make_migration_entry_पढ़ो(&entry);
			newpmd = swp_entry_to_pmd(entry);
			अगर (pmd_swp_soft_dirty(*pmd))
				newpmd = pmd_swp_mksoft_dirty(newpmd);
			set_pmd_at(mm, addr, pmd, newpmd);
		पूर्ण
		जाओ unlock;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Aव्योम trapping faults against the zero page. The पढ़ो-only
	 * data is likely to be पढ़ो-cached on the local CPU and
	 * local/remote hits to the zero page are not पूर्णांकeresting.
	 */
	अगर (prot_numa && is_huge_zero_pmd(*pmd))
		जाओ unlock;

	अगर (prot_numa && pmd_protnone(*pmd))
		जाओ unlock;

	/*
	 * In हाल prot_numa, we are under mmap_पढ़ो_lock(mm). It's critical
	 * to not clear pmd पूर्णांकermittently to aव्योम race with MADV_DONTNEED
	 * which is also under mmap_पढ़ो_lock(mm):
	 *
	 *	CPU0:				CPU1:
	 *				change_huge_pmd(prot_numa=1)
	 *				 pmdp_huge_get_and_clear_notअगरy()
	 * madvise_करोntneed()
	 *  zap_pmd_range()
	 *   pmd_trans_huge(*pmd) == 0 (without ptl)
	 *   // skip the pmd
	 *				 set_pmd_at();
	 *				 // pmd is re-established
	 *
	 * The race makes MADV_DONTNEED miss the huge pmd and करोn't clear it
	 * which may अवरोध userspace.
	 *
	 * pmdp_invalidate() is required to make sure we करोn't miss
	 * dirty/young flags set by hardware.
	 */
	entry = pmdp_invalidate(vma, addr, pmd);

	entry = pmd_modअगरy(entry, newprot);
	अगर (preserve_ग_लिखो)
		entry = pmd_mk_savedग_लिखो(entry);
	अगर (uffd_wp) अणु
		entry = pmd_wrprotect(entry);
		entry = pmd_mkuffd_wp(entry);
	पूर्ण अन्यथा अगर (uffd_wp_resolve) अणु
		/*
		 * Leave the ग_लिखो bit to be handled by PF पूर्णांकerrupt
		 * handler, then things like COW could be properly
		 * handled.
		 */
		entry = pmd_clear_uffd_wp(entry);
	पूर्ण
	ret = HPAGE_PMD_NR;
	set_pmd_at(mm, addr, pmd, entry);
	BUG_ON(vma_is_anonymous(vma) && !preserve_ग_लिखो && pmd_ग_लिखो(entry));
unlock:
	spin_unlock(ptl);
	वापस ret;
पूर्ण

/*
 * Returns page table lock poपूर्णांकer अगर a given pmd maps a thp, शून्य otherwise.
 *
 * Note that अगर it वापसs page table lock poपूर्णांकer, this routine वापसs without
 * unlocking page table lock. So callers must unlock it.
 */
spinlock_t *__pmd_trans_huge_lock(pmd_t *pmd, काष्ठा vm_area_काष्ठा *vma)
अणु
	spinlock_t *ptl;
	ptl = pmd_lock(vma->vm_mm, pmd);
	अगर (likely(is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) ||
			pmd_devmap(*pmd)))
		वापस ptl;
	spin_unlock(ptl);
	वापस शून्य;
पूर्ण

/*
 * Returns true अगर a given pud maps a thp, false otherwise.
 *
 * Note that अगर it वापसs true, this routine वापसs without unlocking page
 * table lock. So callers must unlock it.
 */
spinlock_t *__pud_trans_huge_lock(pud_t *pud, काष्ठा vm_area_काष्ठा *vma)
अणु
	spinlock_t *ptl;

	ptl = pud_lock(vma->vm_mm, pud);
	अगर (likely(pud_trans_huge(*pud) || pud_devmap(*pud)))
		वापस ptl;
	spin_unlock(ptl);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
पूर्णांक zap_huge_pud(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
		 pud_t *pud, अचिन्हित दीर्घ addr)
अणु
	spinlock_t *ptl;

	ptl = __pud_trans_huge_lock(pud, vma);
	अगर (!ptl)
		वापस 0;
	/*
	 * For architectures like ppc64 we look at deposited pgtable
	 * when calling pudp_huge_get_and_clear. So करो the
	 * pgtable_trans_huge_withdraw after finishing pudp related
	 * operations.
	 */
	pudp_huge_get_and_clear_full(tlb->mm, addr, pud, tlb->fullmm);
	tlb_हटाओ_pud_tlb_entry(tlb, pud, addr);
	अगर (vma_is_special_huge(vma)) अणु
		spin_unlock(ptl);
		/* No zero page support yet */
	पूर्ण अन्यथा अणु
		/* No support क्रम anonymous PUD pages yet */
		BUG();
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम __split_huge_pud_locked(काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
		अचिन्हित दीर्घ haddr)
अणु
	VM_BUG_ON(haddr & ~HPAGE_PUD_MASK);
	VM_BUG_ON_VMA(vma->vm_start > haddr, vma);
	VM_BUG_ON_VMA(vma->vm_end < haddr + HPAGE_PUD_SIZE, vma);
	VM_BUG_ON(!pud_trans_huge(*pud) && !pud_devmap(*pud));

	count_vm_event(THP_SPLIT_PUD);

	pudp_huge_clear_flush_notअगरy(vma, haddr, pud);
पूर्ण

व्योम __split_huge_pud(काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
		अचिन्हित दीर्घ address)
अणु
	spinlock_t *ptl;
	काष्ठा mmu_notअगरier_range range;

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address & HPAGE_PUD_MASK,
				(address & HPAGE_PUD_MASK) + HPAGE_PUD_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);
	ptl = pud_lock(vma->vm_mm, pud);
	अगर (unlikely(!pud_trans_huge(*pud) && !pud_devmap(*pud)))
		जाओ out;
	__split_huge_pud_locked(vma, pud, range.start);

out:
	spin_unlock(ptl);
	/*
	 * No need to द्विगुन call mmu_notअगरier->invalidate_range() callback as
	 * the above pudp_huge_clear_flush_notअगरy() did alपढ़ोy call it.
	 */
	mmu_notअगरier_invalidate_range_only_end(&range);
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD */

अटल व्योम __split_huge_zero_page_pmd(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ haddr, pmd_t *pmd)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pgtable_t pgtable;
	pmd_t _pmd;
	पूर्णांक i;

	/*
	 * Leave pmd empty until pte is filled note that it is fine to delay
	 * notअगरication until mmu_notअगरier_invalidate_range_end() as we are
	 * replacing a zero pmd ग_लिखो रक्षित page with a zero pte ग_लिखो
	 * रक्षित page.
	 *
	 * See Documentation/vm/mmu_notअगरier.rst
	 */
	pmdp_huge_clear_flush(vma, haddr, pmd);

	pgtable = pgtable_trans_huge_withdraw(mm, pmd);
	pmd_populate(mm, &_pmd, pgtable);

	क्रम (i = 0; i < HPAGE_PMD_NR; i++, haddr += PAGE_SIZE) अणु
		pte_t *pte, entry;
		entry = pfn_pte(my_zero_pfn(haddr), vma->vm_page_prot);
		entry = pte_mkspecial(entry);
		pte = pte_offset_map(&_pmd, haddr);
		VM_BUG_ON(!pte_none(*pte));
		set_pte_at(mm, haddr, pte, entry);
		pte_unmap(pte);
	पूर्ण
	smp_wmb(); /* make pte visible beक्रमe pmd */
	pmd_populate(mm, pmd, pgtable);
पूर्ण

अटल व्योम __split_huge_pmd_locked(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ haddr, bool मुक्तze)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page *page;
	pgtable_t pgtable;
	pmd_t old_pmd, _pmd;
	bool young, ग_लिखो, soft_dirty, pmd_migration = false, uffd_wp = false;
	अचिन्हित दीर्घ addr;
	पूर्णांक i;

	VM_BUG_ON(haddr & ~HPAGE_PMD_MASK);
	VM_BUG_ON_VMA(vma->vm_start > haddr, vma);
	VM_BUG_ON_VMA(vma->vm_end < haddr + HPAGE_PMD_SIZE, vma);
	VM_BUG_ON(!is_pmd_migration_entry(*pmd) && !pmd_trans_huge(*pmd)
				&& !pmd_devmap(*pmd));

	count_vm_event(THP_SPLIT_PMD);

	अगर (!vma_is_anonymous(vma)) अणु
		old_pmd = pmdp_huge_clear_flush_notअगरy(vma, haddr, pmd);
		/*
		 * We are going to unmap this huge page. So
		 * just go ahead and zap it
		 */
		अगर (arch_needs_pgtable_deposit())
			zap_deposited_table(mm, pmd);
		अगर (vma_is_special_huge(vma))
			वापस;
		अगर (unlikely(is_pmd_migration_entry(old_pmd))) अणु
			swp_entry_t entry;

			entry = pmd_to_swp_entry(old_pmd);
			page = migration_entry_to_page(entry);
		पूर्ण अन्यथा अणु
			page = pmd_page(old_pmd);
			अगर (!PageDirty(page) && pmd_dirty(old_pmd))
				set_page_dirty(page);
			अगर (!PageReferenced(page) && pmd_young(old_pmd))
				SetPageReferenced(page);
			page_हटाओ_rmap(page, true);
			put_page(page);
		पूर्ण
		add_mm_counter(mm, mm_counter_file(page), -HPAGE_PMD_NR);
		वापस;
	पूर्ण

	अगर (is_huge_zero_pmd(*pmd)) अणु
		/*
		 * FIXME: Do we want to invalidate secondary mmu by calling
		 * mmu_notअगरier_invalidate_range() see comments below inside
		 * __split_huge_pmd() ?
		 *
		 * We are going from a zero huge page ग_लिखो रक्षित to zero
		 * small page also ग_लिखो रक्षित so it करोes not seems useful
		 * to invalidate secondary mmu at this समय.
		 */
		वापस __split_huge_zero_page_pmd(vma, haddr, pmd);
	पूर्ण

	/*
	 * Up to this poपूर्णांक the pmd is present and huge and userland has the
	 * whole access to the hugepage during the split (which happens in
	 * place). If we overग_लिखो the pmd with the not-huge version poपूर्णांकing
	 * to the pte here (which of course we could अगर all CPUs were bug
	 * मुक्त), userland could trigger a small page size TLB miss on the
	 * small sized TLB जबतक the hugepage TLB entry is still established in
	 * the huge TLB. Some CPU करोesn't like that.
	 * See http://support.amd.com/TechDocs/41322_10h_Rev_Gd.pdf, Erratum
	 * 383 on page 105. Intel should be safe but is also warns that it's
	 * only safe अगर the permission and cache attributes of the two entries
	 * loaded in the two TLB is identical (which should be the हाल here).
	 * But it is generally safer to never allow small and huge TLB entries
	 * क्रम the same भव address to be loaded simultaneously. So instead
	 * of करोing "pmd_populate(); flush_pmd_tlb_range();" we first mark the
	 * current pmd notpresent (atomically because here the pmd_trans_huge
	 * must reमुख्य set at all बार on the pmd until the split is complete
	 * क्रम this pmd), then we flush the SMP TLB and finally we ग_लिखो the
	 * non-huge version of the pmd entry with pmd_populate.
	 */
	old_pmd = pmdp_invalidate(vma, haddr, pmd);

	pmd_migration = is_pmd_migration_entry(old_pmd);
	अगर (unlikely(pmd_migration)) अणु
		swp_entry_t entry;

		entry = pmd_to_swp_entry(old_pmd);
		page = migration_entry_to_page(entry);
		ग_लिखो = is_ग_लिखो_migration_entry(entry);
		young = false;
		soft_dirty = pmd_swp_soft_dirty(old_pmd);
		uffd_wp = pmd_swp_uffd_wp(old_pmd);
	पूर्ण अन्यथा अणु
		page = pmd_page(old_pmd);
		अगर (pmd_dirty(old_pmd))
			SetPageDirty(page);
		ग_लिखो = pmd_ग_लिखो(old_pmd);
		young = pmd_young(old_pmd);
		soft_dirty = pmd_soft_dirty(old_pmd);
		uffd_wp = pmd_uffd_wp(old_pmd);
	पूर्ण
	VM_BUG_ON_PAGE(!page_count(page), page);
	page_ref_add(page, HPAGE_PMD_NR - 1);

	/*
	 * Withdraw the table only after we mark the pmd entry invalid.
	 * This's critical क्रम some architectures (Power).
	 */
	pgtable = pgtable_trans_huge_withdraw(mm, pmd);
	pmd_populate(mm, &_pmd, pgtable);

	क्रम (i = 0, addr = haddr; i < HPAGE_PMD_NR; i++, addr += PAGE_SIZE) अणु
		pte_t entry, *pte;
		/*
		 * Note that NUMA hपूर्णांकing access restrictions are not
		 * transferred to aव्योम any possibility of altering
		 * permissions across VMAs.
		 */
		अगर (मुक्तze || pmd_migration) अणु
			swp_entry_t swp_entry;
			swp_entry = make_migration_entry(page + i, ग_लिखो);
			entry = swp_entry_to_pte(swp_entry);
			अगर (soft_dirty)
				entry = pte_swp_mksoft_dirty(entry);
			अगर (uffd_wp)
				entry = pte_swp_mkuffd_wp(entry);
		पूर्ण अन्यथा अणु
			entry = mk_pte(page + i, READ_ONCE(vma->vm_page_prot));
			entry = maybe_mkग_लिखो(entry, vma);
			अगर (!ग_लिखो)
				entry = pte_wrprotect(entry);
			अगर (!young)
				entry = pte_mkold(entry);
			अगर (soft_dirty)
				entry = pte_mksoft_dirty(entry);
			अगर (uffd_wp)
				entry = pte_mkuffd_wp(entry);
		पूर्ण
		pte = pte_offset_map(&_pmd, addr);
		BUG_ON(!pte_none(*pte));
		set_pte_at(mm, addr, pte, entry);
		अगर (!pmd_migration)
			atomic_inc(&page[i]._mapcount);
		pte_unmap(pte);
	पूर्ण

	अगर (!pmd_migration) अणु
		/*
		 * Set PG_द्विगुन_map beक्रमe dropping compound_mapcount to aव्योम
		 * false-negative page_mapped().
		 */
		अगर (compound_mapcount(page) > 1 &&
		    !TestSetPageDoubleMap(page)) अणु
			क्रम (i = 0; i < HPAGE_PMD_NR; i++)
				atomic_inc(&page[i]._mapcount);
		पूर्ण

		lock_page_memcg(page);
		अगर (atomic_add_negative(-1, compound_mapcount_ptr(page))) अणु
			/* Last compound_mapcount is gone. */
			__mod_lruvec_page_state(page, NR_ANON_THPS,
						-HPAGE_PMD_NR);
			अगर (TestClearPageDoubleMap(page)) अणु
				/* No need in mapcount reference anymore */
				क्रम (i = 0; i < HPAGE_PMD_NR; i++)
					atomic_dec(&page[i]._mapcount);
			पूर्ण
		पूर्ण
		unlock_page_memcg(page);
	पूर्ण

	smp_wmb(); /* make pte visible beक्रमe pmd */
	pmd_populate(mm, pmd, pgtable);

	अगर (मुक्तze) अणु
		क्रम (i = 0; i < HPAGE_PMD_NR; i++) अणु
			page_हटाओ_rmap(page + i, false);
			put_page(page + i);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __split_huge_pmd(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ address, bool मुक्तze, काष्ठा page *page)
अणु
	spinlock_t *ptl;
	काष्ठा mmu_notअगरier_range range;
	bool करो_unlock_page = false;
	pmd_t _pmd;

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, vma->vm_mm,
				address & HPAGE_PMD_MASK,
				(address & HPAGE_PMD_MASK) + HPAGE_PMD_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);
	ptl = pmd_lock(vma->vm_mm, pmd);

	/*
	 * If caller asks to setup a migration entries, we need a page to check
	 * pmd against. Otherwise we can end up replacing wrong page.
	 */
	VM_BUG_ON(मुक्तze && !page);
	अगर (page) अणु
		VM_WARN_ON_ONCE(!PageLocked(page));
		अगर (page != pmd_page(*pmd))
			जाओ out;
	पूर्ण

repeat:
	अगर (pmd_trans_huge(*pmd)) अणु
		अगर (!page) अणु
			page = pmd_page(*pmd);
			/*
			 * An anonymous page must be locked, to ensure that a
			 * concurrent reuse_swap_page() sees stable mapcount;
			 * but reuse_swap_page() is not used on shmem or file,
			 * and page lock must not be taken when zap_pmd_range()
			 * calls __split_huge_pmd() जबतक i_mmap_lock is held.
			 */
			अगर (PageAnon(page)) अणु
				अगर (unlikely(!trylock_page(page))) अणु
					get_page(page);
					_pmd = *pmd;
					spin_unlock(ptl);
					lock_page(page);
					spin_lock(ptl);
					अगर (unlikely(!pmd_same(*pmd, _pmd))) अणु
						unlock_page(page);
						put_page(page);
						page = शून्य;
						जाओ repeat;
					पूर्ण
					put_page(page);
				पूर्ण
				करो_unlock_page = true;
			पूर्ण
		पूर्ण
		अगर (PageMlocked(page))
			clear_page_mlock(page);
	पूर्ण अन्यथा अगर (!(pmd_devmap(*pmd) || is_pmd_migration_entry(*pmd)))
		जाओ out;
	__split_huge_pmd_locked(vma, pmd, range.start, मुक्तze);
out:
	spin_unlock(ptl);
	अगर (करो_unlock_page)
		unlock_page(page);
	/*
	 * No need to द्विगुन call mmu_notअगरier->invalidate_range() callback.
	 * They are 3 हालs to consider inside __split_huge_pmd_locked():
	 *  1) pmdp_huge_clear_flush_notअगरy() call invalidate_range() obvious
	 *  2) __split_huge_zero_page_pmd() पढ़ो only zero page and any ग_लिखो
	 *    fault will trigger a flush_notअगरy beक्रमe poपूर्णांकing to a new page
	 *    (it is fine अगर the secondary mmu keeps poपूर्णांकing to the old zero
	 *    page in the meanसमय)
	 *  3) Split a huge pmd पूर्णांकo pte poपूर्णांकing to the same page. No need
	 *     to invalidate secondary tlb entry they are all still valid.
	 *     any further changes to inभागidual pte will notअगरy. So no need
	 *     to call mmu_notअगरier->invalidate_range()
	 */
	mmu_notअगरier_invalidate_range_only_end(&range);
पूर्ण

व्योम split_huge_pmd_address(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		bool मुक्तze, काष्ठा page *page)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(vma->vm_mm, address);
	अगर (!pgd_present(*pgd))
		वापस;

	p4d = p4d_offset(pgd, address);
	अगर (!p4d_present(*p4d))
		वापस;

	pud = pud_offset(p4d, address);
	अगर (!pud_present(*pud))
		वापस;

	pmd = pmd_offset(pud, address);

	__split_huge_pmd(vma, pmd, address, मुक्तze, page);
पूर्ण

अटल अंतरभूत व्योम split_huge_pmd_अगर_needed(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	/*
	 * If the new address isn't hpage aligned and it could previously
	 * contain an hugepage: check अगर we need to split an huge pmd.
	 */
	अगर (!IS_ALIGNED(address, HPAGE_PMD_SIZE) &&
	    range_in_vma(vma, ALIGN_DOWN(address, HPAGE_PMD_SIZE),
			 ALIGN(address, HPAGE_PMD_SIZE)))
		split_huge_pmd_address(vma, address, false, शून्य);
पूर्ण

व्योम vma_adjust_trans_huge(काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ start,
			     अचिन्हित दीर्घ end,
			     दीर्घ adjust_next)
अणु
	/* Check अगर we need to split start first. */
	split_huge_pmd_अगर_needed(vma, start);

	/* Check अगर we need to split end next. */
	split_huge_pmd_अगर_needed(vma, end);

	/*
	 * If we're also updating the vma->vm_next->vm_start,
	 * check अगर we need to split it.
	 */
	अगर (adjust_next > 0) अणु
		काष्ठा vm_area_काष्ठा *next = vma->vm_next;
		अचिन्हित दीर्घ nstart = next->vm_start;
		nstart += adjust_next;
		split_huge_pmd_अगर_needed(next, nstart);
	पूर्ण
पूर्ण

अटल व्योम unmap_page(काष्ठा page *page)
अणु
	क्रमागत ttu_flags ttu_flags = TTU_IGNORE_MLOCK | TTU_SYNC |
		TTU_RMAP_LOCKED | TTU_SPLIT_HUGE_PMD;

	VM_BUG_ON_PAGE(!PageHead(page), page);

	अगर (PageAnon(page))
		ttu_flags |= TTU_SPLIT_FREEZE;

	try_to_unmap(page, ttu_flags);

	VM_WARN_ON_ONCE_PAGE(page_mapped(page), page);
पूर्ण

अटल व्योम remap_page(काष्ठा page *page, अचिन्हित पूर्णांक nr)
अणु
	पूर्णांक i;
	अगर (PageTransHuge(page)) अणु
		हटाओ_migration_ptes(page, page, true);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nr; i++)
			हटाओ_migration_ptes(page + i, page + i, true);
	पूर्ण
पूर्ण

अटल व्योम lru_add_page_tail(काष्ठा page *head, काष्ठा page *tail,
		काष्ठा lruvec *lruvec, काष्ठा list_head *list)
अणु
	VM_BUG_ON_PAGE(!PageHead(head), head);
	VM_BUG_ON_PAGE(PageCompound(tail), head);
	VM_BUG_ON_PAGE(PageLRU(tail), head);
	lockdep_निश्चित_held(&lruvec->lru_lock);

	अगर (list) अणु
		/* page reclaim is reclaiming a huge page */
		VM_WARN_ON(PageLRU(head));
		get_page(tail);
		list_add_tail(&tail->lru, list);
	पूर्ण अन्यथा अणु
		/* head is still on lru (and we have it frozen) */
		VM_WARN_ON(!PageLRU(head));
		SetPageLRU(tail);
		list_add_tail(&tail->lru, &head->lru);
	पूर्ण
पूर्ण

अटल व्योम __split_huge_page_tail(काष्ठा page *head, पूर्णांक tail,
		काष्ठा lruvec *lruvec, काष्ठा list_head *list)
अणु
	काष्ठा page *page_tail = head + tail;

	VM_BUG_ON_PAGE(atomic_पढ़ो(&page_tail->_mapcount) != -1, page_tail);

	/*
	 * Clone page flags beक्रमe unमुक्तzing refcount.
	 *
	 * After successful get_page_unless_zero() might follow flags change,
	 * क्रम example lock_page() which set PG_रुकोers.
	 */
	page_tail->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
	page_tail->flags |= (head->flags &
			((1L << PG_referenced) |
			 (1L << PG_swapbacked) |
			 (1L << PG_swapcache) |
			 (1L << PG_mlocked) |
			 (1L << PG_uptodate) |
			 (1L << PG_active) |
			 (1L << PG_workingset) |
			 (1L << PG_locked) |
			 (1L << PG_unevictable) |
#अगर_घोषित CONFIG_64BIT
			 (1L << PG_arch_2) |
#पूर्ण_अगर
			 (1L << PG_dirty)));

	/* ->mapping in first tail page is compound_mapcount */
	VM_BUG_ON_PAGE(tail > 2 && page_tail->mapping != TAIL_MAPPING,
			page_tail);
	page_tail->mapping = head->mapping;
	page_tail->index = head->index + tail;

	/* Page flags must be visible beक्रमe we make the page non-compound. */
	smp_wmb();

	/*
	 * Clear PageTail beक्रमe unमुक्तzing page refcount.
	 *
	 * After successful get_page_unless_zero() might follow put_page()
	 * which needs correct compound_head().
	 */
	clear_compound_head(page_tail);

	/* Finally unमुक्तze refcount. Additional reference from page cache. */
	page_ref_unमुक्तze(page_tail, 1 + (!PageAnon(head) ||
					  PageSwapCache(head)));

	अगर (page_is_young(head))
		set_page_young(page_tail);
	अगर (page_is_idle(head))
		set_page_idle(page_tail);

	page_cpupid_xchg_last(page_tail, page_cpupid_last(head));

	/*
	 * always add to the tail because some iterators expect new
	 * pages to show after the currently processed elements - e.g.
	 * migrate_pages
	 */
	lru_add_page_tail(head, page_tail, lruvec, list);
पूर्ण

अटल व्योम __split_huge_page(काष्ठा page *page, काष्ठा list_head *list,
		pgoff_t end)
अणु
	काष्ठा page *head = compound_head(page);
	काष्ठा lruvec *lruvec;
	काष्ठा address_space *swap_cache = शून्य;
	अचिन्हित दीर्घ offset = 0;
	अचिन्हित पूर्णांक nr = thp_nr_pages(head);
	पूर्णांक i;

	/* complete memcg works beक्रमe add pages to LRU */
	split_page_memcg(head, nr);

	अगर (PageAnon(head) && PageSwapCache(head)) अणु
		swp_entry_t entry = अणु .val = page_निजी(head) पूर्ण;

		offset = swp_offset(entry);
		swap_cache = swap_address_space(entry);
		xa_lock(&swap_cache->i_pages);
	पूर्ण

	/* lock lru list/PageCompound, ref frozen by page_ref_मुक्तze */
	lruvec = lock_page_lruvec(head);

	क्रम (i = nr - 1; i >= 1; i--) अणु
		__split_huge_page_tail(head, i, lruvec, list);
		/* Some pages can be beyond i_size: drop them from page cache */
		अगर (head[i].index >= end) अणु
			ClearPageDirty(head + i);
			__delete_from_page_cache(head + i, शून्य);
			अगर (IS_ENABLED(CONFIG_SHMEM) && PageSwapBacked(head))
				shmem_unअक्षरge(head->mapping->host, 1);
			put_page(head + i);
		पूर्ण अन्यथा अगर (!PageAnon(page)) अणु
			__xa_store(&head->mapping->i_pages, head[i].index,
					head + i, 0);
		पूर्ण अन्यथा अगर (swap_cache) अणु
			__xa_store(&swap_cache->i_pages, offset + i,
					head + i, 0);
		पूर्ण
	पूर्ण

	ClearPageCompound(head);
	unlock_page_lruvec(lruvec);
	/* Caller disabled irqs, so they are still disabled here */

	split_page_owner(head, nr);

	/* See comment in __split_huge_page_tail() */
	अगर (PageAnon(head)) अणु
		/* Additional pin to swap cache */
		अगर (PageSwapCache(head)) अणु
			page_ref_add(head, 2);
			xa_unlock(&swap_cache->i_pages);
		पूर्ण अन्यथा अणु
			page_ref_inc(head);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Additional pin to page cache */
		page_ref_add(head, 2);
		xa_unlock(&head->mapping->i_pages);
	पूर्ण
	local_irq_enable();

	remap_page(head, nr);

	अगर (PageSwapCache(head)) अणु
		swp_entry_t entry = अणु .val = page_निजी(head) पूर्ण;

		split_swap_cluster(entry);
	पूर्ण

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा page *subpage = head + i;
		अगर (subpage == page)
			जारी;
		unlock_page(subpage);

		/*
		 * Subpages may be मुक्तd अगर there wasn't any mapping
		 * like अगर add_to_swap() is running on a lru page that
		 * had its mapping zapped. And मुक्तing these pages
		 * requires taking the lru_lock so we करो the put_page
		 * of the tail pages after the split is complete.
		 */
		put_page(subpage);
	पूर्ण
पूर्ण

पूर्णांक total_mapcount(काष्ठा page *page)
अणु
	पूर्णांक i, compound, nr, ret;

	VM_BUG_ON_PAGE(PageTail(page), page);

	अगर (likely(!PageCompound(page)))
		वापस atomic_पढ़ो(&page->_mapcount) + 1;

	compound = compound_mapcount(page);
	nr = compound_nr(page);
	अगर (PageHuge(page))
		वापस compound;
	ret = compound;
	क्रम (i = 0; i < nr; i++)
		ret += atomic_पढ़ो(&page[i]._mapcount) + 1;
	/* File pages has compound_mapcount included in _mapcount */
	अगर (!PageAnon(page))
		वापस ret - compound * nr;
	अगर (PageDoubleMap(page))
		ret -= nr;
	वापस ret;
पूर्ण

/*
 * This calculates accurately how many mappings a transparent hugepage
 * has (unlike page_mapcount() which isn't fully accurate). This full
 * accuracy is primarily needed to know अगर copy-on-ग_लिखो faults can
 * reuse the page and change the mapping to पढ़ो-ग_लिखो instead of
 * copying them. At the same समय this वापसs the total_mapcount too.
 *
 * The function वापसs the highest mapcount any one of the subpages
 * has. If the वापस value is one, even अगर dअगरferent processes are
 * mapping dअगरferent subpages of the transparent hugepage, they can
 * all reuse it, because each process is reusing a dअगरferent subpage.
 *
 * The total_mapcount is instead counting all भव mappings of the
 * subpages. If the total_mapcount is equal to "one", it tells the
 * caller all mappings beदीर्घ to the same "mm" and in turn the
 * anon_vma of the transparent hugepage can become the vma->anon_vma
 * local one as no other process may be mapping any of the subpages.
 *
 * It would be more accurate to replace page_mapcount() with
 * page_trans_huge_mapcount(), however we only use
 * page_trans_huge_mapcount() in the copy-on-ग_लिखो faults where we
 * need full accuracy to aव्योम अवरोधing page pinning, because
 * page_trans_huge_mapcount() is slower than page_mapcount().
 */
पूर्णांक page_trans_huge_mapcount(काष्ठा page *page, पूर्णांक *total_mapcount)
अणु
	पूर्णांक i, ret, _total_mapcount, mapcount;

	/* hugetlbfs shouldn't call it */
	VM_BUG_ON_PAGE(PageHuge(page), page);

	अगर (likely(!PageTransCompound(page))) अणु
		mapcount = atomic_पढ़ो(&page->_mapcount) + 1;
		अगर (total_mapcount)
			*total_mapcount = mapcount;
		वापस mapcount;
	पूर्ण

	page = compound_head(page);

	_total_mapcount = ret = 0;
	क्रम (i = 0; i < thp_nr_pages(page); i++) अणु
		mapcount = atomic_पढ़ो(&page[i]._mapcount) + 1;
		ret = max(ret, mapcount);
		_total_mapcount += mapcount;
	पूर्ण
	अगर (PageDoubleMap(page)) अणु
		ret -= 1;
		_total_mapcount -= thp_nr_pages(page);
	पूर्ण
	mapcount = compound_mapcount(page);
	ret += mapcount;
	_total_mapcount += mapcount;
	अगर (total_mapcount)
		*total_mapcount = _total_mapcount;
	वापस ret;
पूर्ण

/* Racy check whether the huge page can be split */
bool can_split_huge_page(काष्ठा page *page, पूर्णांक *pextra_pins)
अणु
	पूर्णांक extra_pins;

	/* Additional pins from page cache */
	अगर (PageAnon(page))
		extra_pins = PageSwapCache(page) ? thp_nr_pages(page) : 0;
	अन्यथा
		extra_pins = thp_nr_pages(page);
	अगर (pextra_pins)
		*pextra_pins = extra_pins;
	वापस total_mapcount(page) == page_count(page) - extra_pins - 1;
पूर्ण

/*
 * This function splits huge page पूर्णांकo normal pages. @page can poपूर्णांक to any
 * subpage of huge page to split. Split करोesn't change the position of @page.
 *
 * Only caller must hold pin on the @page, otherwise split fails with -EBUSY.
 * The huge page must be locked.
 *
 * If @list is null, tail pages will be added to LRU list, otherwise, to @list.
 *
 * Both head page and tail pages will inherit mapping, flags, and so on from
 * the hugepage.
 *
 * GUP pin and PG_locked transferred to @page. Rest subpages can be मुक्तd अगर
 * they are not mapped.
 *
 * Returns 0 अगर the hugepage is split successfully.
 * Returns -EBUSY अगर the page is pinned or अगर anon_vma disappeared from under
 * us.
 */
पूर्णांक split_huge_page_to_list(काष्ठा page *page, काष्ठा list_head *list)
अणु
	काष्ठा page *head = compound_head(page);
	काष्ठा deferred_split *ds_queue = get_deferred_split_queue(head);
	काष्ठा anon_vma *anon_vma = शून्य;
	काष्ठा address_space *mapping = शून्य;
	पूर्णांक extra_pins, ret;
	pgoff_t end;

	VM_BUG_ON_PAGE(is_huge_zero_page(head), head);
	VM_BUG_ON_PAGE(!PageLocked(head), head);
	VM_BUG_ON_PAGE(!PageCompound(head), head);

	अगर (PageWriteback(head))
		वापस -EBUSY;

	अगर (PageAnon(head)) अणु
		/*
		 * The caller करोes not necessarily hold an mmap_lock that would
		 * prevent the anon_vma disappearing so we first we take a
		 * reference to it and then lock the anon_vma क्रम ग_लिखो. This
		 * is similar to page_lock_anon_vma_पढ़ो except the ग_लिखो lock
		 * is taken to serialise against parallel split or collapse
		 * operations.
		 */
		anon_vma = page_get_anon_vma(head);
		अगर (!anon_vma) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		end = -1;
		mapping = शून्य;
		anon_vma_lock_ग_लिखो(anon_vma);
	पूर्ण अन्यथा अणु
		mapping = head->mapping;

		/* Truncated ? */
		अगर (!mapping) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		anon_vma = शून्य;
		i_mmap_lock_पढ़ो(mapping);

		/*
		 *__split_huge_page() may need to trim off pages beyond खातापूर्ण:
		 * but on 32-bit, i_size_पढ़ो() takes an irq-unsafe seqlock,
		 * which cannot be nested inside the page tree lock. So note
		 * end now: i_size itself may be changed at any moment, but
		 * head page lock is good enough to serialize the trimming.
		 */
		end = DIV_ROUND_UP(i_size_पढ़ो(mapping->host), PAGE_SIZE);
	पूर्ण

	/*
	 * Racy check अगर we can split the page, beक्रमe unmap_page() will
	 * split PMDs
	 */
	अगर (!can_split_huge_page(head, &extra_pins)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	unmap_page(head);

	/* block पूर्णांकerrupt reentry in xa_lock and spinlock */
	local_irq_disable();
	अगर (mapping) अणु
		XA_STATE(xas, &mapping->i_pages, page_index(head));

		/*
		 * Check अगर the head page is present in page cache.
		 * We assume all tail are present too, अगर head is there.
		 */
		xa_lock(&mapping->i_pages);
		अगर (xas_load(&xas) != head)
			जाओ fail;
	पूर्ण

	/* Prevent deferred_split_scan() touching ->_refcount */
	spin_lock(&ds_queue->split_queue_lock);
	अगर (page_ref_मुक्तze(head, 1 + extra_pins)) अणु
		अगर (!list_empty(page_deferred_list(head))) अणु
			ds_queue->split_queue_len--;
			list_del(page_deferred_list(head));
		पूर्ण
		spin_unlock(&ds_queue->split_queue_lock);
		अगर (mapping) अणु
			पूर्णांक nr = thp_nr_pages(head);

			अगर (PageSwapBacked(head))
				__mod_lruvec_page_state(head, NR_SHMEM_THPS,
							-nr);
			अन्यथा
				__mod_lruvec_page_state(head, NR_खाता_THPS,
							-nr);
		पूर्ण

		__split_huge_page(page, list, end);
		ret = 0;
	पूर्ण अन्यथा अणु
		spin_unlock(&ds_queue->split_queue_lock);
fail:
		अगर (mapping)
			xa_unlock(&mapping->i_pages);
		local_irq_enable();
		remap_page(head, thp_nr_pages(head));
		ret = -EBUSY;
	पूर्ण

out_unlock:
	अगर (anon_vma) अणु
		anon_vma_unlock_ग_लिखो(anon_vma);
		put_anon_vma(anon_vma);
	पूर्ण
	अगर (mapping)
		i_mmap_unlock_पढ़ो(mapping);
out:
	count_vm_event(!ret ? THP_SPLIT_PAGE : THP_SPLIT_PAGE_FAILED);
	वापस ret;
पूर्ण

व्योम मुक्त_transhuge_page(काष्ठा page *page)
अणु
	काष्ठा deferred_split *ds_queue = get_deferred_split_queue(page);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	अगर (!list_empty(page_deferred_list(page))) अणु
		ds_queue->split_queue_len--;
		list_del(page_deferred_list(page));
	पूर्ण
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);
	मुक्त_compound_page(page);
पूर्ण

व्योम deferred_split_huge_page(काष्ठा page *page)
अणु
	काष्ठा deferred_split *ds_queue = get_deferred_split_queue(page);
#अगर_घोषित CONFIG_MEMCG
	काष्ठा mem_cgroup *memcg = page_memcg(compound_head(page));
#पूर्ण_अगर
	अचिन्हित दीर्घ flags;

	VM_BUG_ON_PAGE(!PageTransHuge(page), page);

	/*
	 * The try_to_unmap() in page reclaim path might reach here too,
	 * this may cause a race condition to corrupt deferred split queue.
	 * And, अगर page reclaim is alपढ़ोy handling the same page, it is
	 * unnecessary to handle it again in shrinker.
	 *
	 * Check PageSwapCache to determine अगर the page is being
	 * handled by page reclaim since THP swap would add the page पूर्णांकo
	 * swap cache beक्रमe calling try_to_unmap().
	 */
	अगर (PageSwapCache(page))
		वापस;

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	अगर (list_empty(page_deferred_list(page))) अणु
		count_vm_event(THP_DEFERRED_SPLIT_PAGE);
		list_add_tail(page_deferred_list(page), &ds_queue->split_queue);
		ds_queue->split_queue_len++;
#अगर_घोषित CONFIG_MEMCG
		अगर (memcg)
			set_shrinker_bit(memcg, page_to_nid(page),
					 deferred_split_shrinker.id);
#पूर्ण_अगर
	पूर्ण
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);
पूर्ण

अटल अचिन्हित दीर्घ deferred_split_count(काष्ठा shrinker *shrink,
		काष्ठा shrink_control *sc)
अणु
	काष्ठा pglist_data *pgdata = NODE_DATA(sc->nid);
	काष्ठा deferred_split *ds_queue = &pgdata->deferred_split_queue;

#अगर_घोषित CONFIG_MEMCG
	अगर (sc->memcg)
		ds_queue = &sc->memcg->deferred_split_queue;
#पूर्ण_अगर
	वापस READ_ONCE(ds_queue->split_queue_len);
पूर्ण

अटल अचिन्हित दीर्घ deferred_split_scan(काष्ठा shrinker *shrink,
		काष्ठा shrink_control *sc)
अणु
	काष्ठा pglist_data *pgdata = NODE_DATA(sc->nid);
	काष्ठा deferred_split *ds_queue = &pgdata->deferred_split_queue;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list), *pos, *next;
	काष्ठा page *page;
	पूर्णांक split = 0;

#अगर_घोषित CONFIG_MEMCG
	अगर (sc->memcg)
		ds_queue = &sc->memcg->deferred_split_queue;
#पूर्ण_अगर

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	/* Take pin on all head pages to aव्योम मुक्तing them under us */
	list_क्रम_each_safe(pos, next, &ds_queue->split_queue) अणु
		page = list_entry((व्योम *)pos, काष्ठा page, mapping);
		page = compound_head(page);
		अगर (get_page_unless_zero(page)) अणु
			list_move(page_deferred_list(page), &list);
		पूर्ण अन्यथा अणु
			/* We lost race with put_compound_page() */
			list_del_init(page_deferred_list(page));
			ds_queue->split_queue_len--;
		पूर्ण
		अगर (!--sc->nr_to_scan)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);

	list_क्रम_each_safe(pos, next, &list) अणु
		page = list_entry((व्योम *)pos, काष्ठा page, mapping);
		अगर (!trylock_page(page))
			जाओ next;
		/* split_huge_page() हटाओs page from list on success */
		अगर (!split_huge_page(page))
			split++;
		unlock_page(page);
next:
		put_page(page);
	पूर्ण

	spin_lock_irqsave(&ds_queue->split_queue_lock, flags);
	list_splice_tail(&list, &ds_queue->split_queue);
	spin_unlock_irqrestore(&ds_queue->split_queue_lock, flags);

	/*
	 * Stop shrinker अगर we didn't split any page, but the queue is empty.
	 * This can happen अगर pages were मुक्तd under us.
	 */
	अगर (!split && list_empty(&ds_queue->split_queue))
		वापस SHRINK_STOP;
	वापस split;
पूर्ण

अटल काष्ठा shrinker deferred_split_shrinker = अणु
	.count_objects = deferred_split_count,
	.scan_objects = deferred_split_scan,
	.seeks = DEFAULT_SEEKS,
	.flags = SHRINKER_NUMA_AWARE | SHRINKER_MEMCG_AWARE |
		 SHRINKER_NONSLAB,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम split_huge_pages_all(व्योम)
अणु
	काष्ठा zone *zone;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn, max_zone_pfn;
	अचिन्हित दीर्घ total = 0, split = 0;

	pr_debug("Split all THPs\n");
	क्रम_each_populated_zone(zone) अणु
		max_zone_pfn = zone_end_pfn(zone);
		क्रम (pfn = zone->zone_start_pfn; pfn < max_zone_pfn; pfn++) अणु
			अगर (!pfn_valid(pfn))
				जारी;

			page = pfn_to_page(pfn);
			अगर (!get_page_unless_zero(page))
				जारी;

			अगर (zone != page_zone(page))
				जाओ next;

			अगर (!PageHead(page) || PageHuge(page) || !PageLRU(page))
				जाओ next;

			total++;
			lock_page(page);
			अगर (!split_huge_page(page))
				split++;
			unlock_page(page);
next:
			put_page(page);
			cond_resched();
		पूर्ण
	पूर्ण

	pr_debug("%lu of %lu THP split\n", split, total);
पूर्ण

अटल अंतरभूत bool vma_not_suitable_क्रम_thp_split(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma_is_special_huge(vma) || (vma->vm_flags & VM_IO) ||
		    is_vm_hugetlb_page(vma);
पूर्ण

अटल पूर्णांक split_huge_pages_pid(पूर्णांक pid, अचिन्हित दीर्घ vaddr_start,
				अचिन्हित दीर्घ vaddr_end)
अणु
	पूर्णांक ret = 0;
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ total = 0, split = 0;
	अचिन्हित दीर्घ addr;

	vaddr_start &= PAGE_MASK;
	vaddr_end &= PAGE_MASK;

	/* Find the task_काष्ठा from pid */
	rcu_पढ़ो_lock();
	task = find_task_by_vpid(pid);
	अगर (!task) अणु
		rcu_पढ़ो_unlock();
		ret = -ESRCH;
		जाओ out;
	पूर्ण
	get_task_काष्ठा(task);
	rcu_पढ़ो_unlock();

	/* Find the mm_काष्ठा */
	mm = get_task_mm(task);
	put_task_काष्ठा(task);

	अगर (!mm) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pr_debug("Split huge pages in pid: %d, vaddr: [0x%lx - 0x%lx]\n",
		 pid, vaddr_start, vaddr_end);

	mmap_पढ़ो_lock(mm);
	/*
	 * always increase addr by PAGE_SIZE, since we could have a PTE page
	 * table filled with PTE-mapped THPs, each of which is distinct.
	 */
	क्रम (addr = vaddr_start; addr < vaddr_end; addr += PAGE_SIZE) अणु
		काष्ठा vm_area_काष्ठा *vma = find_vma(mm, addr);
		अचिन्हित पूर्णांक follflags;
		काष्ठा page *page;

		अगर (!vma || addr < vma->vm_start)
			अवरोध;

		/* skip special VMA and hugetlb VMA */
		अगर (vma_not_suitable_क्रम_thp_split(vma)) अणु
			addr = vma->vm_end;
			जारी;
		पूर्ण

		/* FOLL_DUMP to ignore special (like zero) pages */
		follflags = FOLL_GET | FOLL_DUMP;
		page = follow_page(vma, addr, follflags);

		अगर (IS_ERR(page))
			जारी;
		अगर (!page)
			जारी;

		अगर (!is_transparent_hugepage(page))
			जाओ next;

		total++;
		अगर (!can_split_huge_page(compound_head(page), शून्य))
			जाओ next;

		अगर (!trylock_page(page))
			जाओ next;

		अगर (!split_huge_page(page))
			split++;

		unlock_page(page);
next:
		put_page(page);
		cond_resched();
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	pr_debug("%lu of %lu THP split\n", split, total);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक split_huge_pages_in_file(स्थिर अक्षर *file_path, pgoff_t off_start,
				pgoff_t off_end)
अणु
	काष्ठा filename *file;
	काष्ठा file *candidate;
	काष्ठा address_space *mapping;
	पूर्णांक ret = -EINVAL;
	pgoff_t index;
	पूर्णांक nr_pages = 1;
	अचिन्हित दीर्घ total = 0, split = 0;

	file = getname_kernel(file_path);
	अगर (IS_ERR(file))
		वापस ret;

	candidate = file_खोलो_name(file, O_RDONLY, 0);
	अगर (IS_ERR(candidate))
		जाओ out;

	pr_debug("split file-backed THPs in file: %s, page offset: [0x%lx - 0x%lx]\n",
		 file_path, off_start, off_end);

	mapping = candidate->f_mapping;

	क्रम (index = off_start; index < off_end; index += nr_pages) अणु
		काष्ठा page *fpage = pagecache_get_page(mapping, index,
						FGP_ENTRY | FGP_HEAD, 0);

		nr_pages = 1;
		अगर (xa_is_value(fpage) || !fpage)
			जारी;

		अगर (!is_transparent_hugepage(fpage))
			जाओ next;

		total++;
		nr_pages = thp_nr_pages(fpage);

		अगर (!trylock_page(fpage))
			जाओ next;

		अगर (!split_huge_page(fpage))
			split++;

		unlock_page(fpage);
next:
		put_page(fpage);
		cond_resched();
	पूर्ण

	filp_बंद(candidate, शून्य);
	ret = 0;

	pr_debug("%lu of %lu file-backed THP split\n", split, total);
out:
	putname(file);
	वापस ret;
पूर्ण

#घोषणा MAX_INPUT_BUF_SZ 255

अटल sमाप_प्रकार split_huge_pages_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppops)
अणु
	अटल DEFINE_MUTEX(split_debug_mutex);
	sमाप_प्रकार ret;
	/* hold pid, start_vaddr, end_vaddr or file_path, off_start, off_end */
	अक्षर input_buf[MAX_INPUT_BUF_SZ];
	पूर्णांक pid;
	अचिन्हित दीर्घ vaddr_start, vaddr_end;

	ret = mutex_lock_पूर्णांकerruptible(&split_debug_mutex);
	अगर (ret)
		वापस ret;

	ret = -EFAULT;

	स_रखो(input_buf, 0, MAX_INPUT_BUF_SZ);
	अगर (copy_from_user(input_buf, buf, min_t(माप_प्रकार, count, MAX_INPUT_BUF_SZ)))
		जाओ out;

	input_buf[MAX_INPUT_BUF_SZ - 1] = '\0';

	अगर (input_buf[0] == '/') अणु
		अक्षर *tok;
		अक्षर *buf = input_buf;
		अक्षर file_path[MAX_INPUT_BUF_SZ];
		pgoff_t off_start = 0, off_end = 0;
		माप_प्रकार input_len = म_माप(input_buf);

		tok = strsep(&buf, ",");
		अगर (tok) अणु
			म_नकलन(file_path, tok, MAX_INPUT_BUF_SZ);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = माला_पूछो(buf, "0x%lx,0x%lx", &off_start, &off_end);
		अगर (ret != 2) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = split_huge_pages_in_file(file_path, off_start, off_end);
		अगर (!ret)
			ret = input_len;

		जाओ out;
	पूर्ण

	ret = माला_पूछो(input_buf, "%d,0x%lx,0x%lx", &pid, &vaddr_start, &vaddr_end);
	अगर (ret == 1 && pid == 1) अणु
		split_huge_pages_all();
		ret = म_माप(input_buf);
		जाओ out;
	पूर्ण अन्यथा अगर (ret != 3) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = split_huge_pages_pid(pid, vaddr_start, vaddr_end);
	अगर (!ret)
		ret = म_माप(input_buf);
out:
	mutex_unlock(&split_debug_mutex);
	वापस ret;

पूर्ण

अटल स्थिर काष्ठा file_operations split_huge_pages_fops = अणु
	.owner	 = THIS_MODULE,
	.ग_लिखो	 = split_huge_pages_ग_लिखो,
	.llseek  = no_llseek,
पूर्ण;

अटल पूर्णांक __init split_huge_pages_debugfs(व्योम)
अणु
	debugfs_create_file("split_huge_pages", 0200, शून्य, शून्य,
			    &split_huge_pages_fops);
	वापस 0;
पूर्ण
late_initcall(split_huge_pages_debugfs);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
व्योम set_pmd_migration_entry(काष्ठा page_vma_mapped_walk *pvmw,
		काष्ठा page *page)
अणु
	काष्ठा vm_area_काष्ठा *vma = pvmw->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ address = pvmw->address;
	pmd_t pmdval;
	swp_entry_t entry;
	pmd_t pmdswp;

	अगर (!(pvmw->pmd && !pvmw->pte))
		वापस;

	flush_cache_range(vma, address, address + HPAGE_PMD_SIZE);
	pmdval = pmdp_invalidate(vma, address, pvmw->pmd);
	अगर (pmd_dirty(pmdval))
		set_page_dirty(page);
	entry = make_migration_entry(page, pmd_ग_लिखो(pmdval));
	pmdswp = swp_entry_to_pmd(entry);
	अगर (pmd_soft_dirty(pmdval))
		pmdswp = pmd_swp_mksoft_dirty(pmdswp);
	set_pmd_at(mm, address, pvmw->pmd, pmdswp);
	page_हटाओ_rmap(page, true);
	put_page(page);
पूर्ण

व्योम हटाओ_migration_pmd(काष्ठा page_vma_mapped_walk *pvmw, काष्ठा page *new)
अणु
	काष्ठा vm_area_काष्ठा *vma = pvmw->vma;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ address = pvmw->address;
	अचिन्हित दीर्घ mmun_start = address & HPAGE_PMD_MASK;
	pmd_t pmde;
	swp_entry_t entry;

	अगर (!(pvmw->pmd && !pvmw->pte))
		वापस;

	entry = pmd_to_swp_entry(*pvmw->pmd);
	get_page(new);
	pmde = pmd_mkold(mk_huge_pmd(new, vma->vm_page_prot));
	अगर (pmd_swp_soft_dirty(*pvmw->pmd))
		pmde = pmd_mksoft_dirty(pmde);
	अगर (is_ग_लिखो_migration_entry(entry))
		pmde = maybe_pmd_mkग_लिखो(pmde, vma);

	flush_cache_range(vma, mmun_start, mmun_start + HPAGE_PMD_SIZE);
	अगर (PageAnon(new))
		page_add_anon_rmap(new, vma, mmun_start, true);
	अन्यथा
		page_add_file_rmap(new, true);
	set_pmd_at(mm, mmun_start, pvmw->pmd, pmde);
	अगर ((vma->vm_flags & VM_LOCKED) && !PageDoubleMap(new))
		mlock_vma_page(new);
	update_mmu_cache_pmd(vma, address, pvmw->pmd);
पूर्ण
#पूर्ण_अगर

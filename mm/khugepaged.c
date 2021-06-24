<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/khugepaged.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/mman.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/swapops.h>
#समावेश <linux/shmem_fs.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश "internal.h"

क्रमागत scan_result अणु
	SCAN_FAIL,
	SCAN_SUCCEED,
	SCAN_PMD_शून्य,
	SCAN_EXCEED_NONE_PTE,
	SCAN_EXCEED_SWAP_PTE,
	SCAN_EXCEED_SHARED_PTE,
	SCAN_PTE_NON_PRESENT,
	SCAN_PTE_UFFD_WP,
	SCAN_PAGE_RO,
	SCAN_LACK_REFERENCED_PAGE,
	SCAN_PAGE_शून्य,
	SCAN_SCAN_ABORT,
	SCAN_PAGE_COUNT,
	SCAN_PAGE_LRU,
	SCAN_PAGE_LOCK,
	SCAN_PAGE_ANON,
	SCAN_PAGE_COMPOUND,
	SCAN_ANY_PROCESS,
	SCAN_VMA_शून्य,
	SCAN_VMA_CHECK,
	SCAN_ADDRESS_RANGE,
	SCAN_SWAP_CACHE_PAGE,
	SCAN_DEL_PAGE_LRU,
	SCAN_ALLOC_HUGE_PAGE_FAIL,
	SCAN_CGROUP_CHARGE_FAIL,
	SCAN_TRUNCATED,
	SCAN_PAGE_HAS_PRIVATE,
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/huge_memory.h>

अटल काष्ठा task_काष्ठा *khugepaged_thपढ़ो __पढ़ो_mostly;
अटल DEFINE_MUTEX(khugepaged_mutex);

/* शेष scan 8*512 pte (or vmas) every 30 second */
अटल अचिन्हित पूर्णांक khugepaged_pages_to_scan __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक khugepaged_pages_collapsed;
अटल अचिन्हित पूर्णांक khugepaged_full_scans;
अटल अचिन्हित पूर्णांक khugepaged_scan_sleep_millisecs __पढ़ो_mostly = 10000;
/* during fragmentation poll the hugepage allocator once every minute */
अटल अचिन्हित पूर्णांक khugepaged_alloc_sleep_millisecs __पढ़ो_mostly = 60000;
अटल अचिन्हित दीर्घ khugepaged_sleep_expire;
अटल DEFINE_SPINLOCK(khugepaged_mm_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(khugepaged_रुको);
/*
 * शेष collapse hugepages अगर there is at least one pte mapped like
 * it would have happened अगर the vma was large enough during page
 * fault.
 */
अटल अचिन्हित पूर्णांक khugepaged_max_ptes_none __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक khugepaged_max_ptes_swap __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक khugepaged_max_ptes_shared __पढ़ो_mostly;

#घोषणा MM_SLOTS_HASH_BITS 10
अटल __पढ़ो_mostly DEFINE_HASHTABLE(mm_slots_hash, MM_SLOTS_HASH_BITS);

अटल काष्ठा kmem_cache *mm_slot_cache __पढ़ो_mostly;

#घोषणा MAX_PTE_MAPPED_THP 8

/**
 * काष्ठा mm_slot - hash lookup from mm to mm_slot
 * @hash: hash collision list
 * @mm_node: khugepaged scan list headed in khugepaged_scan.mm_head
 * @mm: the mm that this inक्रमmation is valid क्रम
 * @nr_pte_mapped_thp: number of pte mapped THP
 * @pte_mapped_thp: address array corresponding pte mapped THP
 */
काष्ठा mm_slot अणु
	काष्ठा hlist_node hash;
	काष्ठा list_head mm_node;
	काष्ठा mm_काष्ठा *mm;

	/* pte-mapped THP in this mm */
	पूर्णांक nr_pte_mapped_thp;
	अचिन्हित दीर्घ pte_mapped_thp[MAX_PTE_MAPPED_THP];
पूर्ण;

/**
 * काष्ठा khugepaged_scan - cursor क्रम scanning
 * @mm_head: the head of the mm list to scan
 * @mm_slot: the current mm_slot we are scanning
 * @address: the next address inside that to be scanned
 *
 * There is only the one khugepaged_scan instance of this cursor काष्ठाure.
 */
काष्ठा khugepaged_scan अणु
	काष्ठा list_head mm_head;
	काष्ठा mm_slot *mm_slot;
	अचिन्हित दीर्घ address;
पूर्ण;

अटल काष्ठा khugepaged_scan khugepaged_scan = अणु
	.mm_head = LIST_HEAD_INIT(khugepaged_scan.mm_head),
पूर्ण;

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार scan_sleep_millisecs_show(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_scan_sleep_millisecs);
पूर्ण

अटल sमाप_प्रकार scan_sleep_millisecs_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक msecs;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &msecs);
	अगर (err)
		वापस -EINVAL;

	khugepaged_scan_sleep_millisecs = msecs;
	khugepaged_sleep_expire = 0;
	wake_up_पूर्णांकerruptible(&khugepaged_रुको);

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute scan_sleep_millisecs_attr =
	__ATTR(scan_sleep_millisecs, 0644, scan_sleep_millisecs_show,
	       scan_sleep_millisecs_store);

अटल sमाप_प्रकार alloc_sleep_millisecs_show(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_alloc_sleep_millisecs);
पूर्ण

अटल sमाप_प्रकार alloc_sleep_millisecs_store(काष्ठा kobject *kobj,
					   काष्ठा kobj_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक msecs;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &msecs);
	अगर (err)
		वापस -EINVAL;

	khugepaged_alloc_sleep_millisecs = msecs;
	khugepaged_sleep_expire = 0;
	wake_up_पूर्णांकerruptible(&khugepaged_रुको);

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute alloc_sleep_millisecs_attr =
	__ATTR(alloc_sleep_millisecs, 0644, alloc_sleep_millisecs_show,
	       alloc_sleep_millisecs_store);

अटल sमाप_प्रकार pages_to_scan_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_pages_to_scan);
पूर्ण
अटल sमाप_प्रकार pages_to_scan_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक pages;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 10, &pages);
	अगर (err || !pages)
		वापस -EINVAL;

	khugepaged_pages_to_scan = pages;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute pages_to_scan_attr =
	__ATTR(pages_to_scan, 0644, pages_to_scan_show,
	       pages_to_scan_store);

अटल sमाप_प्रकार pages_collapsed_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_pages_collapsed);
पूर्ण
अटल काष्ठा kobj_attribute pages_collapsed_attr =
	__ATTR_RO(pages_collapsed);

अटल sमाप_प्रकार full_scans_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr,
			       अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_full_scans);
पूर्ण
अटल काष्ठा kobj_attribute full_scans_attr =
	__ATTR_RO(full_scans);

अटल sमाप_प्रकार khugepaged_defrag_show(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस single_hugepage_flag_show(kobj, attr, buf,
					 TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG);
पूर्ण
अटल sमाप_प्रकार khugepaged_defrag_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस single_hugepage_flag_store(kobj, attr, buf, count,
				 TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG);
पूर्ण
अटल काष्ठा kobj_attribute khugepaged_defrag_attr =
	__ATTR(defrag, 0644, khugepaged_defrag_show,
	       khugepaged_defrag_store);

/*
 * max_ptes_none controls अगर khugepaged should collapse hugepages over
 * any unmapped ptes in turn potentially increasing the memory
 * footprपूर्णांक of the vmas. When max_ptes_none is 0 khugepaged will not
 * reduce the available मुक्त memory in the प्रणाली as it
 * runs. Increasing max_ptes_none will instead potentially reduce the
 * मुक्त memory in the प्रणाली during the khugepaged scan.
 */
अटल sमाप_प्रकार khugepaged_max_ptes_none_show(काष्ठा kobject *kobj,
					     काष्ठा kobj_attribute *attr,
					     अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_max_ptes_none);
पूर्ण
अटल sमाप_प्रकार khugepaged_max_ptes_none_store(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ max_ptes_none;

	err = kम_से_अदीर्घ(buf, 10, &max_ptes_none);
	अगर (err || max_ptes_none > HPAGE_PMD_NR-1)
		वापस -EINVAL;

	khugepaged_max_ptes_none = max_ptes_none;

	वापस count;
पूर्ण
अटल काष्ठा kobj_attribute khugepaged_max_ptes_none_attr =
	__ATTR(max_ptes_none, 0644, khugepaged_max_ptes_none_show,
	       khugepaged_max_ptes_none_store);

अटल sमाप_प्रकार khugepaged_max_ptes_swap_show(काष्ठा kobject *kobj,
					     काष्ठा kobj_attribute *attr,
					     अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_max_ptes_swap);
पूर्ण

अटल sमाप_प्रकार khugepaged_max_ptes_swap_store(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ max_ptes_swap;

	err  = kम_से_अदीर्घ(buf, 10, &max_ptes_swap);
	अगर (err || max_ptes_swap > HPAGE_PMD_NR-1)
		वापस -EINVAL;

	khugepaged_max_ptes_swap = max_ptes_swap;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute khugepaged_max_ptes_swap_attr =
	__ATTR(max_ptes_swap, 0644, khugepaged_max_ptes_swap_show,
	       khugepaged_max_ptes_swap_store);

अटल sमाप_प्रकार khugepaged_max_ptes_shared_show(काष्ठा kobject *kobj,
					       काष्ठा kobj_attribute *attr,
					       अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%u\n", khugepaged_max_ptes_shared);
पूर्ण

अटल sमाप_प्रकार khugepaged_max_ptes_shared_store(काष्ठा kobject *kobj,
					      काष्ठा kobj_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ max_ptes_shared;

	err  = kम_से_अदीर्घ(buf, 10, &max_ptes_shared);
	अगर (err || max_ptes_shared > HPAGE_PMD_NR-1)
		वापस -EINVAL;

	khugepaged_max_ptes_shared = max_ptes_shared;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute khugepaged_max_ptes_shared_attr =
	__ATTR(max_ptes_shared, 0644, khugepaged_max_ptes_shared_show,
	       khugepaged_max_ptes_shared_store);

अटल काष्ठा attribute *khugepaged_attr[] = अणु
	&khugepaged_defrag_attr.attr,
	&khugepaged_max_ptes_none_attr.attr,
	&khugepaged_max_ptes_swap_attr.attr,
	&khugepaged_max_ptes_shared_attr.attr,
	&pages_to_scan_attr.attr,
	&pages_collapsed_attr.attr,
	&full_scans_attr.attr,
	&scan_sleep_millisecs_attr.attr,
	&alloc_sleep_millisecs_attr.attr,
	शून्य,
पूर्ण;

काष्ठा attribute_group khugepaged_attr_group = अणु
	.attrs = khugepaged_attr,
	.name = "khugepaged",
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSFS */

पूर्णांक hugepage_madvise(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ *vm_flags, पूर्णांक advice)
अणु
	चयन (advice) अणु
	हाल MADV_HUGEPAGE:
#अगर_घोषित CONFIG_S390
		/*
		 * qemu blindly sets MADV_HUGEPAGE on all allocations, but s390
		 * can't handle this properly after s390_enable_sie, so we simply
		 * ignore the madvise to prevent qemu from causing a संक_अंश.
		 */
		अगर (mm_has_pgste(vma->vm_mm))
			वापस 0;
#पूर्ण_अगर
		*vm_flags &= ~VM_NOHUGEPAGE;
		*vm_flags |= VM_HUGEPAGE;
		/*
		 * If the vma become good क्रम khugepaged to scan,
		 * रेजिस्टर it here without रुकोing a page fault that
		 * may not happen any समय soon.
		 */
		अगर (!(*vm_flags & VM_NO_KHUGEPAGED) &&
				khugepaged_enter_vma_merge(vma, *vm_flags))
			वापस -ENOMEM;
		अवरोध;
	हाल MADV_NOHUGEPAGE:
		*vm_flags &= ~VM_HUGEPAGE;
		*vm_flags |= VM_NOHUGEPAGE;
		/*
		 * Setting VM_NOHUGEPAGE will prevent khugepaged from scanning
		 * this vma even अगर we leave the mm रेजिस्टरed in khugepaged अगर
		 * it got रेजिस्टरed beक्रमe VM_NOHUGEPAGE was set.
		 */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init khugepaged_init(व्योम)
अणु
	mm_slot_cache = kmem_cache_create("khugepaged_mm_slot",
					  माप(काष्ठा mm_slot),
					  __alignof__(काष्ठा mm_slot), 0, शून्य);
	अगर (!mm_slot_cache)
		वापस -ENOMEM;

	khugepaged_pages_to_scan = HPAGE_PMD_NR * 8;
	khugepaged_max_ptes_none = HPAGE_PMD_NR - 1;
	khugepaged_max_ptes_swap = HPAGE_PMD_NR / 8;
	khugepaged_max_ptes_shared = HPAGE_PMD_NR / 2;

	वापस 0;
पूर्ण

व्योम __init khugepaged_destroy(व्योम)
अणु
	kmem_cache_destroy(mm_slot_cache);
पूर्ण

अटल अंतरभूत काष्ठा mm_slot *alloc_mm_slot(व्योम)
अणु
	अगर (!mm_slot_cache)	/* initialization failed */
		वापस शून्य;
	वापस kmem_cache_zalloc(mm_slot_cache, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम मुक्त_mm_slot(काष्ठा mm_slot *mm_slot)
अणु
	kmem_cache_मुक्त(mm_slot_cache, mm_slot);
पूर्ण

अटल काष्ठा mm_slot *get_mm_slot(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *mm_slot;

	hash_क्रम_each_possible(mm_slots_hash, mm_slot, hash, (अचिन्हित दीर्घ)mm)
		अगर (mm == mm_slot->mm)
			वापस mm_slot;

	वापस शून्य;
पूर्ण

अटल व्योम insert_to_mm_slots_hash(काष्ठा mm_काष्ठा *mm,
				    काष्ठा mm_slot *mm_slot)
अणु
	mm_slot->mm = mm;
	hash_add(mm_slots_hash, &mm_slot->hash, (दीर्घ)mm);
पूर्ण

अटल अंतरभूत पूर्णांक khugepaged_test_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	वापस atomic_पढ़ो(&mm->mm_users) == 0;
पूर्ण

अटल bool hugepage_vma_check(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ vm_flags)
अणु
	/* Explicitly disabled through madvise. */
	अगर ((vm_flags & VM_NOHUGEPAGE) ||
	    test_bit(MMF_DISABLE_THP, &vma->vm_mm->flags))
		वापस false;

	/* Enabled via shmem mount options or sysfs settings. */
	अगर (shmem_file(vma->vm_file) && shmem_huge_enabled(vma)) अणु
		वापस IS_ALIGNED((vma->vm_start >> PAGE_SHIFT) - vma->vm_pgoff,
				HPAGE_PMD_NR);
	पूर्ण

	/* THP settings require madvise. */
	अगर (!(vm_flags & VM_HUGEPAGE) && !khugepaged_always())
		वापस false;

	/* Read-only file mappings need to be aligned क्रम THP to work. */
	अगर (IS_ENABLED(CONFIG_READ_ONLY_THP_FOR_FS) && vma->vm_file &&
	    (vm_flags & VM_DENYWRITE)) अणु
		वापस IS_ALIGNED((vma->vm_start >> PAGE_SHIFT) - vma->vm_pgoff,
				HPAGE_PMD_NR);
	पूर्ण

	अगर (!vma->anon_vma || vma->vm_ops)
		वापस false;
	अगर (vma_is_temporary_stack(vma))
		वापस false;
	वापस !(vm_flags & VM_NO_KHUGEPAGED);
पूर्ण

पूर्णांक __khugepaged_enter(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *mm_slot;
	पूर्णांक wakeup;

	mm_slot = alloc_mm_slot();
	अगर (!mm_slot)
		वापस -ENOMEM;

	/* __khugepaged_निकास() must not run from under us */
	VM_BUG_ON_MM(khugepaged_test_निकास(mm), mm);
	अगर (unlikely(test_and_set_bit(MMF_VM_HUGEPAGE, &mm->flags))) अणु
		मुक्त_mm_slot(mm_slot);
		वापस 0;
	पूर्ण

	spin_lock(&khugepaged_mm_lock);
	insert_to_mm_slots_hash(mm, mm_slot);
	/*
	 * Insert just behind the scanning cursor, to let the area settle
	 * करोwn a little.
	 */
	wakeup = list_empty(&khugepaged_scan.mm_head);
	list_add_tail(&mm_slot->mm_node, &khugepaged_scan.mm_head);
	spin_unlock(&khugepaged_mm_lock);

	mmgrab(mm);
	अगर (wakeup)
		wake_up_पूर्णांकerruptible(&khugepaged_रुको);

	वापस 0;
पूर्ण

पूर्णांक khugepaged_enter_vma_merge(काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ vm_flags)
अणु
	अचिन्हित दीर्घ hstart, hend;

	/*
	 * khugepaged only supports पढ़ो-only files क्रम non-shmem files.
	 * khugepaged करोes not yet work on special mappings. And
	 * file-निजी shmem THP is not supported.
	 */
	अगर (!hugepage_vma_check(vma, vm_flags))
		वापस 0;

	hstart = (vma->vm_start + ~HPAGE_PMD_MASK) & HPAGE_PMD_MASK;
	hend = vma->vm_end & HPAGE_PMD_MASK;
	अगर (hstart < hend)
		वापस khugepaged_enter(vma, vm_flags);
	वापस 0;
पूर्ण

व्योम __khugepaged_निकास(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_slot *mm_slot;
	पूर्णांक मुक्त = 0;

	spin_lock(&khugepaged_mm_lock);
	mm_slot = get_mm_slot(mm);
	अगर (mm_slot && khugepaged_scan.mm_slot != mm_slot) अणु
		hash_del(&mm_slot->hash);
		list_del(&mm_slot->mm_node);
		मुक्त = 1;
	पूर्ण
	spin_unlock(&khugepaged_mm_lock);

	अगर (मुक्त) अणु
		clear_bit(MMF_VM_HUGEPAGE, &mm->flags);
		मुक्त_mm_slot(mm_slot);
		mmdrop(mm);
	पूर्ण अन्यथा अगर (mm_slot) अणु
		/*
		 * This is required to serialize against
		 * khugepaged_test_निकास() (which is guaranteed to run
		 * under mmap sem पढ़ो mode). Stop here (after we
		 * वापस all pagetables will be destroyed) until
		 * khugepaged has finished working on the pagetables
		 * under the mmap_lock.
		 */
		mmap_ग_लिखो_lock(mm);
		mmap_ग_लिखो_unlock(mm);
	पूर्ण
पूर्ण

अटल व्योम release_pte_page(काष्ठा page *page)
अणु
	mod_node_page_state(page_pgdat(page),
			NR_ISOLATED_ANON + page_is_file_lru(page),
			-compound_nr(page));
	unlock_page(page);
	putback_lru_page(page);
पूर्ण

अटल व्योम release_pte_pages(pte_t *pte, pte_t *_pte,
		काष्ठा list_head *compound_pagelist)
अणु
	काष्ठा page *page, *पंचांगp;

	जबतक (--_pte >= pte) अणु
		pte_t pteval = *_pte;

		page = pte_page(pteval);
		अगर (!pte_none(pteval) && !is_zero_pfn(pte_pfn(pteval)) &&
				!PageCompound(page))
			release_pte_page(page);
	पूर्ण

	list_क्रम_each_entry_safe(page, पंचांगp, compound_pagelist, lru) अणु
		list_del(&page->lru);
		release_pte_page(page);
	पूर्ण
पूर्ण

अटल bool is_refcount_suitable(काष्ठा page *page)
अणु
	पूर्णांक expected_refcount;

	expected_refcount = total_mapcount(page);
	अगर (PageSwapCache(page))
		expected_refcount += compound_nr(page);

	वापस page_count(page) == expected_refcount;
पूर्ण

अटल पूर्णांक __collapse_huge_page_isolate(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address,
					pte_t *pte,
					काष्ठा list_head *compound_pagelist)
अणु
	काष्ठा page *page = शून्य;
	pte_t *_pte;
	पूर्णांक none_or_zero = 0, shared = 0, result = 0, referenced = 0;
	bool writable = false;

	क्रम (_pte = pte; _pte < pte+HPAGE_PMD_NR;
	     _pte++, address += PAGE_SIZE) अणु
		pte_t pteval = *_pte;
		अगर (pte_none(pteval) || (pte_present(pteval) &&
				is_zero_pfn(pte_pfn(pteval)))) अणु
			अगर (!userfaultfd_armed(vma) &&
			    ++none_or_zero <= khugepaged_max_ptes_none) अणु
				जारी;
			पूर्ण अन्यथा अणु
				result = SCAN_EXCEED_NONE_PTE;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (!pte_present(pteval)) अणु
			result = SCAN_PTE_NON_PRESENT;
			जाओ out;
		पूर्ण
		page = vm_normal_page(vma, address, pteval);
		अगर (unlikely(!page)) अणु
			result = SCAN_PAGE_शून्य;
			जाओ out;
		पूर्ण

		VM_BUG_ON_PAGE(!PageAnon(page), page);

		अगर (page_mapcount(page) > 1 &&
				++shared > khugepaged_max_ptes_shared) अणु
			result = SCAN_EXCEED_SHARED_PTE;
			जाओ out;
		पूर्ण

		अगर (PageCompound(page)) अणु
			काष्ठा page *p;
			page = compound_head(page);

			/*
			 * Check अगर we have dealt with the compound page
			 * alपढ़ोy
			 */
			list_क्रम_each_entry(p, compound_pagelist, lru) अणु
				अगर (page == p)
					जाओ next;
			पूर्ण
		पूर्ण

		/*
		 * We can करो it beक्रमe isolate_lru_page because the
		 * page can't be मुक्तd from under us. NOTE: PG_lock
		 * is needed to serialize against split_huge_page
		 * when invoked from the VM.
		 */
		अगर (!trylock_page(page)) अणु
			result = SCAN_PAGE_LOCK;
			जाओ out;
		पूर्ण

		/*
		 * Check अगर the page has any GUP (or other बाह्यal) pins.
		 *
		 * The page table that maps the page has been alपढ़ोy unlinked
		 * from the page table tree and this process cannot get
		 * an additional pin on the page.
		 *
		 * New pins can come later अगर the page is shared across विभाजन,
		 * but not from this process. The other process cannot ग_लिखो to
		 * the page, only trigger CoW.
		 */
		अगर (!is_refcount_suitable(page)) अणु
			unlock_page(page);
			result = SCAN_PAGE_COUNT;
			जाओ out;
		पूर्ण
		अगर (!pte_ग_लिखो(pteval) && PageSwapCache(page) &&
				!reuse_swap_page(page, शून्य)) अणु
			/*
			 * Page is in the swap cache and cannot be re-used.
			 * It cannot be collapsed पूर्णांकo a THP.
			 */
			unlock_page(page);
			result = SCAN_SWAP_CACHE_PAGE;
			जाओ out;
		पूर्ण

		/*
		 * Isolate the page to aव्योम collapsing an hugepage
		 * currently in use by the VM.
		 */
		अगर (isolate_lru_page(page)) अणु
			unlock_page(page);
			result = SCAN_DEL_PAGE_LRU;
			जाओ out;
		पूर्ण
		mod_node_page_state(page_pgdat(page),
				NR_ISOLATED_ANON + page_is_file_lru(page),
				compound_nr(page));
		VM_BUG_ON_PAGE(!PageLocked(page), page);
		VM_BUG_ON_PAGE(PageLRU(page), page);

		अगर (PageCompound(page))
			list_add_tail(&page->lru, compound_pagelist);
next:
		/* There should be enough young pte to collapse the page */
		अगर (pte_young(pteval) ||
		    page_is_young(page) || PageReferenced(page) ||
		    mmu_notअगरier_test_young(vma->vm_mm, address))
			referenced++;

		अगर (pte_ग_लिखो(pteval))
			writable = true;
	पूर्ण

	अगर (unlikely(!writable)) अणु
		result = SCAN_PAGE_RO;
	पूर्ण अन्यथा अगर (unlikely(!referenced)) अणु
		result = SCAN_LACK_REFERENCED_PAGE;
	पूर्ण अन्यथा अणु
		result = SCAN_SUCCEED;
		trace_mm_collapse_huge_page_isolate(page, none_or_zero,
						    referenced, writable, result);
		वापस 1;
	पूर्ण
out:
	release_pte_pages(pte, _pte, compound_pagelist);
	trace_mm_collapse_huge_page_isolate(page, none_or_zero,
					    referenced, writable, result);
	वापस 0;
पूर्ण

अटल व्योम __collapse_huge_page_copy(pte_t *pte, काष्ठा page *page,
				      काष्ठा vm_area_काष्ठा *vma,
				      अचिन्हित दीर्घ address,
				      spinlock_t *ptl,
				      काष्ठा list_head *compound_pagelist)
अणु
	काष्ठा page *src_page, *पंचांगp;
	pte_t *_pte;
	क्रम (_pte = pte; _pte < pte + HPAGE_PMD_NR;
				_pte++, page++, address += PAGE_SIZE) अणु
		pte_t pteval = *_pte;

		अगर (pte_none(pteval) || is_zero_pfn(pte_pfn(pteval))) अणु
			clear_user_highpage(page, address);
			add_mm_counter(vma->vm_mm, MM_ANONPAGES, 1);
			अगर (is_zero_pfn(pte_pfn(pteval))) अणु
				/*
				 * ptl mostly unnecessary.
				 */
				spin_lock(ptl);
				/*
				 * paravirt calls inside pte_clear here are
				 * superfluous.
				 */
				pte_clear(vma->vm_mm, address, _pte);
				spin_unlock(ptl);
			पूर्ण
		पूर्ण अन्यथा अणु
			src_page = pte_page(pteval);
			copy_user_highpage(page, src_page, address, vma);
			अगर (!PageCompound(src_page))
				release_pte_page(src_page);
			/*
			 * ptl mostly unnecessary, but preempt has to
			 * be disabled to update the per-cpu stats
			 * inside page_हटाओ_rmap().
			 */
			spin_lock(ptl);
			/*
			 * paravirt calls inside pte_clear here are
			 * superfluous.
			 */
			pte_clear(vma->vm_mm, address, _pte);
			page_हटाओ_rmap(src_page, false);
			spin_unlock(ptl);
			मुक्त_page_and_swap_cache(src_page);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(src_page, पंचांगp, compound_pagelist, lru) अणु
		list_del(&src_page->lru);
		release_pte_page(src_page);
	पूर्ण
पूर्ण

अटल व्योम khugepaged_alloc_sleep(व्योम)
अणु
	DEFINE_WAIT(रुको);

	add_रुको_queue(&khugepaged_रुको, &रुको);
	मुक्तzable_schedule_समयout_पूर्णांकerruptible(
		msecs_to_jअगरfies(khugepaged_alloc_sleep_millisecs));
	हटाओ_रुको_queue(&khugepaged_रुको, &रुको);
पूर्ण

अटल पूर्णांक khugepaged_node_load[MAX_NUMNODES];

अटल bool khugepaged_scan_पात(पूर्णांक nid)
अणु
	पूर्णांक i;

	/*
	 * If node_reclaim_mode is disabled, then no extra efक्रमt is made to
	 * allocate memory locally.
	 */
	अगर (!node_reclaim_enabled())
		वापस false;

	/* If there is a count क्रम this node alपढ़ोy, it must be acceptable */
	अगर (khugepaged_node_load[nid])
		वापस false;

	क्रम (i = 0; i < MAX_NUMNODES; i++) अणु
		अगर (!khugepaged_node_load[i])
			जारी;
		अगर (node_distance(nid, i) > node_reclaim_distance)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Defrag क्रम khugepaged will enter direct reclaim/compaction अगर necessary */
अटल अंतरभूत gfp_t alloc_hugepage_khugepaged_gfpmask(व्योम)
अणु
	वापस khugepaged_defrag() ? GFP_TRANSHUGE : GFP_TRANSHUGE_LIGHT;
पूर्ण

#अगर_घोषित CONFIG_NUMA
अटल पूर्णांक khugepaged_find_target_node(व्योम)
अणु
	अटल पूर्णांक last_khugepaged_target_node = NUMA_NO_NODE;
	पूर्णांक nid, target_node = 0, max_value = 0;

	/* find first node with max normal pages hit */
	क्रम (nid = 0; nid < MAX_NUMNODES; nid++)
		अगर (khugepaged_node_load[nid] > max_value) अणु
			max_value = khugepaged_node_load[nid];
			target_node = nid;
		पूर्ण

	/* करो some balance अगर several nodes have the same hit record */
	अगर (target_node <= last_khugepaged_target_node)
		क्रम (nid = last_khugepaged_target_node + 1; nid < MAX_NUMNODES;
				nid++)
			अगर (max_value == khugepaged_node_load[nid]) अणु
				target_node = nid;
				अवरोध;
			पूर्ण

	last_khugepaged_target_node = target_node;
	वापस target_node;
पूर्ण

अटल bool khugepaged_pपुनः_स्मृति_page(काष्ठा page **hpage, bool *रुको)
अणु
	अगर (IS_ERR(*hpage)) अणु
		अगर (!*रुको)
			वापस false;

		*रुको = false;
		*hpage = शून्य;
		khugepaged_alloc_sleep();
	पूर्ण अन्यथा अगर (*hpage) अणु
		put_page(*hpage);
		*hpage = शून्य;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा page *
khugepaged_alloc_page(काष्ठा page **hpage, gfp_t gfp, पूर्णांक node)
अणु
	VM_BUG_ON_PAGE(*hpage, *hpage);

	*hpage = __alloc_pages_node(node, gfp, HPAGE_PMD_ORDER);
	अगर (unlikely(!*hpage)) अणु
		count_vm_event(THP_COLLAPSE_ALLOC_FAILED);
		*hpage = ERR_PTR(-ENOMEM);
		वापस शून्य;
	पूर्ण

	prep_transhuge_page(*hpage);
	count_vm_event(THP_COLLAPSE_ALLOC);
	वापस *hpage;
पूर्ण
#अन्यथा
अटल पूर्णांक khugepaged_find_target_node(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *alloc_khugepaged_hugepage(व्योम)
अणु
	काष्ठा page *page;

	page = alloc_pages(alloc_hugepage_khugepaged_gfpmask(),
			   HPAGE_PMD_ORDER);
	अगर (page)
		prep_transhuge_page(page);
	वापस page;
पूर्ण

अटल काष्ठा page *khugepaged_alloc_hugepage(bool *रुको)
अणु
	काष्ठा page *hpage;

	करो अणु
		hpage = alloc_khugepaged_hugepage();
		अगर (!hpage) अणु
			count_vm_event(THP_COLLAPSE_ALLOC_FAILED);
			अगर (!*रुको)
				वापस शून्य;

			*रुको = false;
			khugepaged_alloc_sleep();
		पूर्ण अन्यथा
			count_vm_event(THP_COLLAPSE_ALLOC);
	पूर्ण जबतक (unlikely(!hpage) && likely(khugepaged_enabled()));

	वापस hpage;
पूर्ण

अटल bool khugepaged_pपुनः_स्मृति_page(काष्ठा page **hpage, bool *रुको)
अणु
	/*
	 * If the hpage allocated earlier was briefly exposed in page cache
	 * beक्रमe collapse_file() failed, it is possible that racing lookups
	 * have not yet completed, and would then be unpleasantly surprised by
	 * finding the hpage reused क्रम the same mapping at a dअगरferent offset.
	 * Just release the previous allocation अगर there is any danger of that.
	 */
	अगर (*hpage && page_count(*hpage) > 1) अणु
		put_page(*hpage);
		*hpage = शून्य;
	पूर्ण

	अगर (!*hpage)
		*hpage = khugepaged_alloc_hugepage(रुको);

	अगर (unlikely(!*hpage))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा page *
khugepaged_alloc_page(काष्ठा page **hpage, gfp_t gfp, पूर्णांक node)
अणु
	VM_BUG_ON(!*hpage);

	वापस  *hpage;
पूर्ण
#पूर्ण_अगर

/*
 * If mmap_lock temporarily dropped, revalidate vma
 * beक्रमe taking mmap_lock.
 * Return 0 अगर succeeds, otherwise वापस none-zero
 * value (scan code).
 */

अटल पूर्णांक hugepage_vma_revalidate(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
		काष्ठा vm_area_काष्ठा **vmap)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ hstart, hend;

	अगर (unlikely(khugepaged_test_निकास(mm)))
		वापस SCAN_ANY_PROCESS;

	*vmap = vma = find_vma(mm, address);
	अगर (!vma)
		वापस SCAN_VMA_शून्य;

	hstart = (vma->vm_start + ~HPAGE_PMD_MASK) & HPAGE_PMD_MASK;
	hend = vma->vm_end & HPAGE_PMD_MASK;
	अगर (address < hstart || address + HPAGE_PMD_SIZE > hend)
		वापस SCAN_ADDRESS_RANGE;
	अगर (!hugepage_vma_check(vma, vma->vm_flags))
		वापस SCAN_VMA_CHECK;
	/* Anon VMA expected */
	अगर (!vma->anon_vma || vma->vm_ops)
		वापस SCAN_VMA_CHECK;
	वापस 0;
पूर्ण

/*
 * Bring missing pages in from swap, to complete THP collapse.
 * Only करोne अगर khugepaged_scan_pmd believes it is worthजबतक.
 *
 * Called and वापसs without pte mapped or spinlocks held,
 * but with mmap_lock held to protect against vma changes.
 */

अटल bool __collapse_huge_page_swapin(काष्ठा mm_काष्ठा *mm,
					काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ haddr, pmd_t *pmd,
					पूर्णांक referenced)
अणु
	पूर्णांक swapped_in = 0;
	vm_fault_t ret = 0;
	अचिन्हित दीर्घ address, end = haddr + (HPAGE_PMD_NR * PAGE_SIZE);

	क्रम (address = haddr; address < end; address += PAGE_SIZE) अणु
		काष्ठा vm_fault vmf = अणु
			.vma = vma,
			.address = address,
			.pgoff = linear_page_index(vma, haddr),
			.flags = FAULT_FLAG_ALLOW_RETRY,
			.pmd = pmd,
		पूर्ण;

		vmf.pte = pte_offset_map(pmd, address);
		vmf.orig_pte = *vmf.pte;
		अगर (!is_swap_pte(vmf.orig_pte)) अणु
			pte_unmap(vmf.pte);
			जारी;
		पूर्ण
		swapped_in++;
		ret = करो_swap_page(&vmf);

		/* करो_swap_page वापसs VM_FAULT_RETRY with released mmap_lock */
		अगर (ret & VM_FAULT_RETRY) अणु
			mmap_पढ़ो_lock(mm);
			अगर (hugepage_vma_revalidate(mm, haddr, &vma)) अणु
				/* vma is no दीर्घer available, करोn't जारी to swapin */
				trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
				वापस false;
			पूर्ण
			/* check अगर the pmd is still valid */
			अगर (mm_find_pmd(mm, haddr) != pmd) अणु
				trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
				वापस false;
			पूर्ण
		पूर्ण
		अगर (ret & VM_FAULT_ERROR) अणु
			trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
			वापस false;
		पूर्ण
	पूर्ण

	/* Drain LRU add pagevec to हटाओ extra pin on the swapped in pages */
	अगर (swapped_in)
		lru_add_drain();

	trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 1);
	वापस true;
पूर्ण

अटल व्योम collapse_huge_page(काष्ठा mm_काष्ठा *mm,
				   अचिन्हित दीर्घ address,
				   काष्ठा page **hpage,
				   पूर्णांक node, पूर्णांक referenced, पूर्णांक unmapped)
अणु
	LIST_HEAD(compound_pagelist);
	pmd_t *pmd, _pmd;
	pte_t *pte;
	pgtable_t pgtable;
	काष्ठा page *new_page;
	spinlock_t *pmd_ptl, *pte_ptl;
	पूर्णांक isolated = 0, result = 0;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mmu_notअगरier_range range;
	gfp_t gfp;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);

	/* Only allocate from the target node */
	gfp = alloc_hugepage_khugepaged_gfpmask() | __GFP_THISNODE;

	/*
	 * Beक्रमe allocating the hugepage, release the mmap_lock पढ़ो lock.
	 * The allocation can take potentially a दीर्घ समय अगर it involves
	 * sync compaction, and we करो not need to hold the mmap_lock during
	 * that. We will recheck the vma after taking it again in ग_लिखो mode.
	 */
	mmap_पढ़ो_unlock(mm);
	new_page = khugepaged_alloc_page(hpage, gfp, node);
	अगर (!new_page) अणु
		result = SCAN_ALLOC_HUGE_PAGE_FAIL;
		जाओ out_nolock;
	पूर्ण

	अगर (unlikely(mem_cgroup_अक्षरge(new_page, mm, gfp))) अणु
		result = SCAN_CGROUP_CHARGE_FAIL;
		जाओ out_nolock;
	पूर्ण
	count_memcg_page_event(new_page, THP_COLLAPSE_ALLOC);

	mmap_पढ़ो_lock(mm);
	result = hugepage_vma_revalidate(mm, address, &vma);
	अगर (result) अणु
		mmap_पढ़ो_unlock(mm);
		जाओ out_nolock;
	पूर्ण

	pmd = mm_find_pmd(mm, address);
	अगर (!pmd) अणु
		result = SCAN_PMD_शून्य;
		mmap_पढ़ो_unlock(mm);
		जाओ out_nolock;
	पूर्ण

	/*
	 * __collapse_huge_page_swapin always वापसs with mmap_lock locked.
	 * If it fails, we release mmap_lock and jump out_nolock.
	 * Continuing to collapse causes inconsistency.
	 */
	अगर (unmapped && !__collapse_huge_page_swapin(mm, vma, address,
						     pmd, referenced)) अणु
		mmap_पढ़ो_unlock(mm);
		जाओ out_nolock;
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	/*
	 * Prevent all access to pagetables with the exception of
	 * gup_fast later handled by the ptep_clear_flush and the VM
	 * handled by the anon_vma lock + PG_lock.
	 */
	mmap_ग_लिखो_lock(mm);
	result = hugepage_vma_revalidate(mm, address, &vma);
	अगर (result)
		जाओ out_up_ग_लिखो;
	/* check अगर the pmd is still valid */
	अगर (mm_find_pmd(mm, address) != pmd)
		जाओ out_up_ग_लिखो;

	anon_vma_lock_ग_लिखो(vma->anon_vma);

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, शून्य, mm,
				address, address + HPAGE_PMD_SIZE);
	mmu_notअगरier_invalidate_range_start(&range);

	pte = pte_offset_map(pmd, address);
	pte_ptl = pte_lockptr(mm, pmd);

	pmd_ptl = pmd_lock(mm, pmd); /* probably unnecessary */
	/*
	 * After this gup_fast can't run anymore. This also हटाओs
	 * any huge TLB entry from the CPU so we won't allow
	 * huge and small TLB entries क्रम the same भव address
	 * to aव्योम the risk of CPU bugs in that area.
	 */
	_pmd = pmdp_collapse_flush(vma, address, pmd);
	spin_unlock(pmd_ptl);
	mmu_notअगरier_invalidate_range_end(&range);

	spin_lock(pte_ptl);
	isolated = __collapse_huge_page_isolate(vma, address, pte,
			&compound_pagelist);
	spin_unlock(pte_ptl);

	अगर (unlikely(!isolated)) अणु
		pte_unmap(pte);
		spin_lock(pmd_ptl);
		BUG_ON(!pmd_none(*pmd));
		/*
		 * We can only use set_pmd_at when establishing
		 * hugepmds and never क्रम establishing regular pmds that
		 * poपूर्णांकs to regular pagetables. Use pmd_populate क्रम that
		 */
		pmd_populate(mm, pmd, pmd_pgtable(_pmd));
		spin_unlock(pmd_ptl);
		anon_vma_unlock_ग_लिखो(vma->anon_vma);
		result = SCAN_FAIL;
		जाओ out_up_ग_लिखो;
	पूर्ण

	/*
	 * All pages are isolated and locked so anon_vma rmap
	 * can't run anymore.
	 */
	anon_vma_unlock_ग_लिखो(vma->anon_vma);

	__collapse_huge_page_copy(pte, new_page, vma, address, pte_ptl,
			&compound_pagelist);
	pte_unmap(pte);
	/*
	 * spin_lock() below is not the equivalent of smp_wmb(), but
	 * the smp_wmb() inside __SetPageUptodate() can be reused to
	 * aव्योम the copy_huge_page ग_लिखोs to become visible after
	 * the set_pmd_at() ग_लिखो.
	 */
	__SetPageUptodate(new_page);
	pgtable = pmd_pgtable(_pmd);

	_pmd = mk_huge_pmd(new_page, vma->vm_page_prot);
	_pmd = maybe_pmd_mkग_लिखो(pmd_सूची_गढ़ोty(_pmd), vma);

	spin_lock(pmd_ptl);
	BUG_ON(!pmd_none(*pmd));
	page_add_new_anon_rmap(new_page, vma, address, true);
	lru_cache_add_inactive_or_unevictable(new_page, vma);
	pgtable_trans_huge_deposit(mm, pmd, pgtable);
	set_pmd_at(mm, address, pmd, _pmd);
	update_mmu_cache_pmd(vma, address, pmd);
	spin_unlock(pmd_ptl);

	*hpage = शून्य;

	khugepaged_pages_collapsed++;
	result = SCAN_SUCCEED;
out_up_ग_लिखो:
	mmap_ग_लिखो_unlock(mm);
out_nolock:
	अगर (!IS_ERR_OR_शून्य(*hpage))
		mem_cgroup_unअक्षरge(*hpage);
	trace_mm_collapse_huge_page(mm, isolated, result);
	वापस;
पूर्ण

अटल पूर्णांक khugepaged_scan_pmd(काष्ठा mm_काष्ठा *mm,
			       काष्ठा vm_area_काष्ठा *vma,
			       अचिन्हित दीर्घ address,
			       काष्ठा page **hpage)
अणु
	pmd_t *pmd;
	pte_t *pte, *_pte;
	पूर्णांक ret = 0, result = 0, referenced = 0;
	पूर्णांक none_or_zero = 0, shared = 0;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ _address;
	spinlock_t *ptl;
	पूर्णांक node = NUMA_NO_NODE, unmapped = 0;
	bool writable = false;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);

	pmd = mm_find_pmd(mm, address);
	अगर (!pmd) अणु
		result = SCAN_PMD_शून्य;
		जाओ out;
	पूर्ण

	स_रखो(khugepaged_node_load, 0, माप(khugepaged_node_load));
	pte = pte_offset_map_lock(mm, pmd, address, &ptl);
	क्रम (_address = address, _pte = pte; _pte < pte+HPAGE_PMD_NR;
	     _pte++, _address += PAGE_SIZE) अणु
		pte_t pteval = *_pte;
		अगर (is_swap_pte(pteval)) अणु
			अगर (++unmapped <= khugepaged_max_ptes_swap) अणु
				/*
				 * Always be strict with uffd-wp
				 * enabled swap entries.  Please see
				 * comment below क्रम pte_uffd_wp().
				 */
				अगर (pte_swp_uffd_wp(pteval)) अणु
					result = SCAN_PTE_UFFD_WP;
					जाओ out_unmap;
				पूर्ण
				जारी;
			पूर्ण अन्यथा अणु
				result = SCAN_EXCEED_SWAP_PTE;
				जाओ out_unmap;
			पूर्ण
		पूर्ण
		अगर (pte_none(pteval) || is_zero_pfn(pte_pfn(pteval))) अणु
			अगर (!userfaultfd_armed(vma) &&
			    ++none_or_zero <= khugepaged_max_ptes_none) अणु
				जारी;
			पूर्ण अन्यथा अणु
				result = SCAN_EXCEED_NONE_PTE;
				जाओ out_unmap;
			पूर्ण
		पूर्ण
		अगर (pte_uffd_wp(pteval)) अणु
			/*
			 * Don't collapse the page अगर any of the small
			 * PTEs are armed with uffd ग_लिखो protection.
			 * Here we can also mark the new huge pmd as
			 * ग_लिखो रक्षित अगर any of the small ones is
			 * marked but that could bring unknown
			 * userfault messages that falls outside of
			 * the रेजिस्टरed range.  So, just be simple.
			 */
			result = SCAN_PTE_UFFD_WP;
			जाओ out_unmap;
		पूर्ण
		अगर (pte_ग_लिखो(pteval))
			writable = true;

		page = vm_normal_page(vma, _address, pteval);
		अगर (unlikely(!page)) अणु
			result = SCAN_PAGE_शून्य;
			जाओ out_unmap;
		पूर्ण

		अगर (page_mapcount(page) > 1 &&
				++shared > khugepaged_max_ptes_shared) अणु
			result = SCAN_EXCEED_SHARED_PTE;
			जाओ out_unmap;
		पूर्ण

		page = compound_head(page);

		/*
		 * Record which node the original page is from and save this
		 * inक्रमmation to khugepaged_node_load[].
		 * Khupaged will allocate hugepage from the node has the max
		 * hit record.
		 */
		node = page_to_nid(page);
		अगर (khugepaged_scan_पात(node)) अणु
			result = SCAN_SCAN_ABORT;
			जाओ out_unmap;
		पूर्ण
		khugepaged_node_load[node]++;
		अगर (!PageLRU(page)) अणु
			result = SCAN_PAGE_LRU;
			जाओ out_unmap;
		पूर्ण
		अगर (PageLocked(page)) अणु
			result = SCAN_PAGE_LOCK;
			जाओ out_unmap;
		पूर्ण
		अगर (!PageAnon(page)) अणु
			result = SCAN_PAGE_ANON;
			जाओ out_unmap;
		पूर्ण

		/*
		 * Check अगर the page has any GUP (or other बाह्यal) pins.
		 *
		 * Here the check is racy it may see toपंचांगal_mapcount > refcount
		 * in some हालs.
		 * For example, one process with one विभाजनed child process.
		 * The parent has the PMD split due to MADV_DONTNEED, then
		 * the child is trying unmap the whole PMD, but khugepaged
		 * may be scanning the parent between the child has
		 * PageDoubleMap flag cleared and dec the mapcount.  So
		 * khugepaged may see total_mapcount > refcount.
		 *
		 * But such हाल is ephemeral we could always retry collapse
		 * later.  However it may report false positive अगर the page
		 * has excessive GUP pins (i.e. 512).  Anyway the same check
		 * will be करोne again later the risk seems low.
		 */
		अगर (!is_refcount_suitable(page)) अणु
			result = SCAN_PAGE_COUNT;
			जाओ out_unmap;
		पूर्ण
		अगर (pte_young(pteval) ||
		    page_is_young(page) || PageReferenced(page) ||
		    mmu_notअगरier_test_young(vma->vm_mm, address))
			referenced++;
	पूर्ण
	अगर (!writable) अणु
		result = SCAN_PAGE_RO;
	पूर्ण अन्यथा अगर (!referenced || (unmapped && referenced < HPAGE_PMD_NR/2)) अणु
		result = SCAN_LACK_REFERENCED_PAGE;
	पूर्ण अन्यथा अणु
		result = SCAN_SUCCEED;
		ret = 1;
	पूर्ण
out_unmap:
	pte_unmap_unlock(pte, ptl);
	अगर (ret) अणु
		node = khugepaged_find_target_node();
		/* collapse_huge_page will वापस with the mmap_lock released */
		collapse_huge_page(mm, address, hpage, node,
				referenced, unmapped);
	पूर्ण
out:
	trace_mm_khugepaged_scan_pmd(mm, page, writable, referenced,
				     none_or_zero, result, unmapped);
	वापस ret;
पूर्ण

अटल व्योम collect_mm_slot(काष्ठा mm_slot *mm_slot)
अणु
	काष्ठा mm_काष्ठा *mm = mm_slot->mm;

	lockdep_निश्चित_held(&khugepaged_mm_lock);

	अगर (khugepaged_test_निकास(mm)) अणु
		/* मुक्त mm_slot */
		hash_del(&mm_slot->hash);
		list_del(&mm_slot->mm_node);

		/*
		 * Not strictly needed because the mm निकासed alपढ़ोy.
		 *
		 * clear_bit(MMF_VM_HUGEPAGE, &mm->flags);
		 */

		/* khugepaged_mm_lock actually not necessary क्रम the below */
		मुक्त_mm_slot(mm_slot);
		mmdrop(mm);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SHMEM
/*
 * Notअगरy khugepaged that given addr of the mm is pte-mapped THP. Then
 * khugepaged should try to collapse the page table.
 */
अटल पूर्णांक khugepaged_add_pte_mapped_thp(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_slot *mm_slot;

	VM_BUG_ON(addr & ~HPAGE_PMD_MASK);

	spin_lock(&khugepaged_mm_lock);
	mm_slot = get_mm_slot(mm);
	अगर (likely(mm_slot && mm_slot->nr_pte_mapped_thp < MAX_PTE_MAPPED_THP))
		mm_slot->pte_mapped_thp[mm_slot->nr_pte_mapped_thp++] = addr;
	spin_unlock(&khugepaged_mm_lock);
	वापस 0;
पूर्ण

/**
 * collapse_pte_mapped_thp - Try to collapse a pte-mapped THP क्रम mm at
 * address haddr.
 *
 * @mm: process address space where collapse happens
 * @addr: THP collapse address
 *
 * This function checks whether all the PTEs in the PMD are poपूर्णांकing to the
 * right THP. If so, retract the page table so the THP can refault in with
 * as pmd-mapped.
 */
व्योम collapse_pte_mapped_thp(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ haddr = addr & HPAGE_PMD_MASK;
	काष्ठा vm_area_काष्ठा *vma = find_vma(mm, haddr);
	काष्ठा page *hpage;
	pte_t *start_pte, *pte;
	pmd_t *pmd, _pmd;
	spinlock_t *ptl;
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (!vma || !vma->vm_file ||
	    !range_in_vma(vma, haddr, haddr + HPAGE_PMD_SIZE))
		वापस;

	/*
	 * This vm_flags may not have VM_HUGEPAGE अगर the page was not
	 * collapsed by this mm. But we can still collapse अगर the page is
	 * the valid THP. Add extra VM_HUGEPAGE so hugepage_vma_check()
	 * will not fail the vma क्रम missing VM_HUGEPAGE
	 */
	अगर (!hugepage_vma_check(vma, vma->vm_flags | VM_HUGEPAGE))
		वापस;

	hpage = find_lock_page(vma->vm_file->f_mapping,
			       linear_page_index(vma, haddr));
	अगर (!hpage)
		वापस;

	अगर (!PageHead(hpage))
		जाओ drop_hpage;

	pmd = mm_find_pmd(mm, haddr);
	अगर (!pmd)
		जाओ drop_hpage;

	start_pte = pte_offset_map_lock(mm, pmd, haddr, &ptl);

	/* step 1: check all mapped PTEs are to the right huge page */
	क्रम (i = 0, addr = haddr, pte = start_pte;
	     i < HPAGE_PMD_NR; i++, addr += PAGE_SIZE, pte++) अणु
		काष्ठा page *page;

		/* empty pte, skip */
		अगर (pte_none(*pte))
			जारी;

		/* page swapped out, पात */
		अगर (!pte_present(*pte))
			जाओ पात;

		page = vm_normal_page(vma, addr, *pte);

		/*
		 * Note that uprobe, debugger, or MAP_PRIVATE may change the
		 * page table, but the new page will not be a subpage of hpage.
		 */
		अगर (hpage + i != page)
			जाओ पात;
		count++;
	पूर्ण

	/* step 2: adjust rmap */
	क्रम (i = 0, addr = haddr, pte = start_pte;
	     i < HPAGE_PMD_NR; i++, addr += PAGE_SIZE, pte++) अणु
		काष्ठा page *page;

		अगर (pte_none(*pte))
			जारी;
		page = vm_normal_page(vma, addr, *pte);
		page_हटाओ_rmap(page, false);
	पूर्ण

	pte_unmap_unlock(start_pte, ptl);

	/* step 3: set proper refcount and mm_counters. */
	अगर (count) अणु
		page_ref_sub(hpage, count);
		add_mm_counter(vma->vm_mm, mm_counter_file(hpage), -count);
	पूर्ण

	/* step 4: collapse pmd */
	ptl = pmd_lock(vma->vm_mm, pmd);
	_pmd = pmdp_collapse_flush(vma, haddr, pmd);
	spin_unlock(ptl);
	mm_dec_nr_ptes(mm);
	pte_मुक्त(mm, pmd_pgtable(_pmd));

drop_hpage:
	unlock_page(hpage);
	put_page(hpage);
	वापस;

पात:
	pte_unmap_unlock(start_pte, ptl);
	जाओ drop_hpage;
पूर्ण

अटल व्योम khugepaged_collapse_pte_mapped_thps(काष्ठा mm_slot *mm_slot)
अणु
	काष्ठा mm_काष्ठा *mm = mm_slot->mm;
	पूर्णांक i;

	अगर (likely(mm_slot->nr_pte_mapped_thp == 0))
		वापस;

	अगर (!mmap_ग_लिखो_trylock(mm))
		वापस;

	अगर (unlikely(khugepaged_test_निकास(mm)))
		जाओ out;

	क्रम (i = 0; i < mm_slot->nr_pte_mapped_thp; i++)
		collapse_pte_mapped_thp(mm, mm_slot->pte_mapped_thp[i]);

out:
	mm_slot->nr_pte_mapped_thp = 0;
	mmap_ग_लिखो_unlock(mm);
पूर्ण

अटल व्योम retract_page_tables(काष्ठा address_space *mapping, pgoff_t pgoff)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ addr;
	pmd_t *pmd, _pmd;

	i_mmap_lock_ग_लिखो(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap, pgoff, pgoff) अणु
		/*
		 * Check vma->anon_vma to exclude MAP_PRIVATE mappings that
		 * got written to. These VMAs are likely not worth investing
		 * mmap_ग_लिखो_lock(mm) as PMD-mapping is likely to be split
		 * later.
		 *
		 * Not that vma->anon_vma check is racy: it can be set up after
		 * the check but beक्रमe we took mmap_lock by the fault path.
		 * But page lock would prevent establishing any new ptes of the
		 * page, so we are safe.
		 *
		 * An alternative would be drop the check, but check that page
		 * table is clear beक्रमe calling pmdp_collapse_flush() under
		 * ptl. It has higher chance to recover THP क्रम the VMA, but
		 * has higher cost too.
		 */
		अगर (vma->anon_vma)
			जारी;
		addr = vma->vm_start + ((pgoff - vma->vm_pgoff) << PAGE_SHIFT);
		अगर (addr & ~HPAGE_PMD_MASK)
			जारी;
		अगर (vma->vm_end < addr + HPAGE_PMD_SIZE)
			जारी;
		mm = vma->vm_mm;
		pmd = mm_find_pmd(mm, addr);
		अगर (!pmd)
			जारी;
		/*
		 * We need exclusive mmap_lock to retract page table.
		 *
		 * We use trylock due to lock inversion: we need to acquire
		 * mmap_lock जबतक holding page lock. Fault path करोes it in
		 * reverse order. Trylock is a way to aव्योम deadlock.
		 */
		अगर (mmap_ग_लिखो_trylock(mm)) अणु
			अगर (!khugepaged_test_निकास(mm)) अणु
				spinlock_t *ptl = pmd_lock(mm, pmd);
				/* assume page table is clear */
				_pmd = pmdp_collapse_flush(vma, addr, pmd);
				spin_unlock(ptl);
				mm_dec_nr_ptes(mm);
				pte_मुक्त(mm, pmd_pgtable(_pmd));
			पूर्ण
			mmap_ग_लिखो_unlock(mm);
		पूर्ण अन्यथा अणु
			/* Try again later */
			khugepaged_add_pte_mapped_thp(mm, addr);
		पूर्ण
	पूर्ण
	i_mmap_unlock_ग_लिखो(mapping);
पूर्ण

/**
 * collapse_file - collapse filemap/पंचांगpfs/shmem pages पूर्णांकo huge one.
 *
 * @mm: process address space where collapse happens
 * @file: file that collapse on
 * @start: collapse start address
 * @hpage: new allocated huge page क्रम collapse
 * @node: appoपूर्णांकed node the new huge page allocate from
 *
 * Basic scheme is simple, details are more complex:
 *  - allocate and lock a new huge page;
 *  - scan page cache replacing old pages with the new one
 *    + swap/gup in pages अगर necessary;
 *    + fill in gaps;
 *    + keep old pages around in हाल rollback is required;
 *  - अगर replacing succeeds:
 *    + copy data over;
 *    + मुक्त old pages;
 *    + unlock huge page;
 *  - अगर replacing failed;
 *    + put all pages back and unमुक्तze them;
 *    + restore gaps in the page cache;
 *    + unlock and मुक्त huge page;
 */
अटल व्योम collapse_file(काष्ठा mm_काष्ठा *mm,
		काष्ठा file *file, pgoff_t start,
		काष्ठा page **hpage, पूर्णांक node)
अणु
	काष्ठा address_space *mapping = file->f_mapping;
	gfp_t gfp;
	काष्ठा page *new_page;
	pgoff_t index, end = start + HPAGE_PMD_NR;
	LIST_HEAD(pagelist);
	XA_STATE_ORDER(xas, &mapping->i_pages, start, HPAGE_PMD_ORDER);
	पूर्णांक nr_none = 0, result = SCAN_SUCCEED;
	bool is_shmem = shmem_file(file);
	पूर्णांक nr;

	VM_BUG_ON(!IS_ENABLED(CONFIG_READ_ONLY_THP_FOR_FS) && !is_shmem);
	VM_BUG_ON(start & (HPAGE_PMD_NR - 1));

	/* Only allocate from the target node */
	gfp = alloc_hugepage_khugepaged_gfpmask() | __GFP_THISNODE;

	new_page = khugepaged_alloc_page(hpage, gfp, node);
	अगर (!new_page) अणु
		result = SCAN_ALLOC_HUGE_PAGE_FAIL;
		जाओ out;
	पूर्ण

	अगर (unlikely(mem_cgroup_अक्षरge(new_page, mm, gfp))) अणु
		result = SCAN_CGROUP_CHARGE_FAIL;
		जाओ out;
	पूर्ण
	count_memcg_page_event(new_page, THP_COLLAPSE_ALLOC);

	/* This will be less messy when we use multi-index entries */
	करो अणु
		xas_lock_irq(&xas);
		xas_create_range(&xas);
		अगर (!xas_error(&xas))
			अवरोध;
		xas_unlock_irq(&xas);
		अगर (!xas_nomem(&xas, GFP_KERNEL)) अणु
			result = SCAN_FAIL;
			जाओ out;
		पूर्ण
	पूर्ण जबतक (1);

	__SetPageLocked(new_page);
	अगर (is_shmem)
		__SetPageSwapBacked(new_page);
	new_page->index = start;
	new_page->mapping = mapping;

	/*
	 * At this poपूर्णांक the new_page is locked and not up-to-date.
	 * It's safe to insert it पूर्णांकo the page cache, because nobody would
	 * be able to map it or use it in another way until we unlock it.
	 */

	xas_set(&xas, start);
	क्रम (index = start; index < end; index++) अणु
		काष्ठा page *page = xas_next(&xas);

		VM_BUG_ON(index != xas.xa_index);
		अगर (is_shmem) अणु
			अगर (!page) अणु
				/*
				 * Stop अगर extent has been truncated or
				 * hole-punched, and is now completely
				 * empty.
				 */
				अगर (index == start) अणु
					अगर (!xas_next_entry(&xas, end - 1)) अणु
						result = SCAN_TRUNCATED;
						जाओ xa_locked;
					पूर्ण
					xas_set(&xas, index);
				पूर्ण
				अगर (!shmem_अक्षरge(mapping->host, 1)) अणु
					result = SCAN_FAIL;
					जाओ xa_locked;
				पूर्ण
				xas_store(&xas, new_page);
				nr_none++;
				जारी;
			पूर्ण

			अगर (xa_is_value(page) || !PageUptodate(page)) अणु
				xas_unlock_irq(&xas);
				/* swap in or instantiate fallocated page */
				अगर (shmem_getpage(mapping->host, index, &page,
						  SGP_NOHUGE)) अणु
					result = SCAN_FAIL;
					जाओ xa_unlocked;
				पूर्ण
			पूर्ण अन्यथा अगर (trylock_page(page)) अणु
				get_page(page);
				xas_unlock_irq(&xas);
			पूर्ण अन्यथा अणु
				result = SCAN_PAGE_LOCK;
				जाओ xa_locked;
			पूर्ण
		पूर्ण अन्यथा अणु	/* !is_shmem */
			अगर (!page || xa_is_value(page)) अणु
				xas_unlock_irq(&xas);
				page_cache_sync_पढ़ोahead(mapping, &file->f_ra,
							  file, index,
							  end - index);
				/* drain pagevecs to help isolate_lru_page() */
				lru_add_drain();
				page = find_lock_page(mapping, index);
				अगर (unlikely(page == शून्य)) अणु
					result = SCAN_FAIL;
					जाओ xa_unlocked;
				पूर्ण
			पूर्ण अन्यथा अगर (PageDirty(page)) अणु
				/*
				 * khugepaged only works on पढ़ो-only fd,
				 * so this page is dirty because it hasn't
				 * been flushed since first ग_लिखो. There
				 * won't be new dirty pages.
				 *
				 * Trigger async flush here and hope the
				 * ग_लिखोback is करोne when khugepaged
				 * revisits this page.
				 *
				 * This is a one-off situation. We are not
				 * क्रमcing ग_लिखोback in loop.
				 */
				xas_unlock_irq(&xas);
				filemap_flush(mapping);
				result = SCAN_FAIL;
				जाओ xa_unlocked;
			पूर्ण अन्यथा अगर (trylock_page(page)) अणु
				get_page(page);
				xas_unlock_irq(&xas);
			पूर्ण अन्यथा अणु
				result = SCAN_PAGE_LOCK;
				जाओ xa_locked;
			पूर्ण
		पूर्ण

		/*
		 * The page must be locked, so we can drop the i_pages lock
		 * without racing with truncate.
		 */
		VM_BUG_ON_PAGE(!PageLocked(page), page);

		/* make sure the page is up to date */
		अगर (unlikely(!PageUptodate(page))) अणु
			result = SCAN_FAIL;
			जाओ out_unlock;
		पूर्ण

		/*
		 * If file was truncated then extended, or hole-punched, beक्रमe
		 * we locked the first page, then a THP might be there alपढ़ोy.
		 */
		अगर (PageTransCompound(page)) अणु
			result = SCAN_PAGE_COMPOUND;
			जाओ out_unlock;
		पूर्ण

		अगर (page_mapping(page) != mapping) अणु
			result = SCAN_TRUNCATED;
			जाओ out_unlock;
		पूर्ण

		अगर (!is_shmem && PageDirty(page)) अणु
			/*
			 * khugepaged only works on पढ़ो-only fd, so this
			 * page is dirty because it hasn't been flushed
			 * since first ग_लिखो.
			 */
			result = SCAN_FAIL;
			जाओ out_unlock;
		पूर्ण

		अगर (isolate_lru_page(page)) अणु
			result = SCAN_DEL_PAGE_LRU;
			जाओ out_unlock;
		पूर्ण

		अगर (page_has_निजी(page) &&
		    !try_to_release_page(page, GFP_KERNEL)) अणु
			result = SCAN_PAGE_HAS_PRIVATE;
			putback_lru_page(page);
			जाओ out_unlock;
		पूर्ण

		अगर (page_mapped(page))
			unmap_mapping_pages(mapping, index, 1, false);

		xas_lock_irq(&xas);
		xas_set(&xas, index);

		VM_BUG_ON_PAGE(page != xas_load(&xas), page);
		VM_BUG_ON_PAGE(page_mapped(page), page);

		/*
		 * The page is expected to have page_count() == 3:
		 *  - we hold a pin on it;
		 *  - one reference from page cache;
		 *  - one from isolate_lru_page;
		 */
		अगर (!page_ref_मुक्तze(page, 3)) अणु
			result = SCAN_PAGE_COUNT;
			xas_unlock_irq(&xas);
			putback_lru_page(page);
			जाओ out_unlock;
		पूर्ण

		/*
		 * Add the page to the list to be able to unकरो the collapse अगर
		 * something go wrong.
		 */
		list_add_tail(&page->lru, &pagelist);

		/* Finally, replace with the new page. */
		xas_store(&xas, new_page);
		जारी;
out_unlock:
		unlock_page(page);
		put_page(page);
		जाओ xa_unlocked;
	पूर्ण
	nr = thp_nr_pages(new_page);

	अगर (is_shmem)
		__mod_lruvec_page_state(new_page, NR_SHMEM_THPS, nr);
	अन्यथा अणु
		__mod_lruvec_page_state(new_page, NR_खाता_THPS, nr);
		filemap_nr_thps_inc(mapping);
	पूर्ण

	अगर (nr_none) अणु
		__mod_lruvec_page_state(new_page, NR_खाता_PAGES, nr_none);
		अगर (is_shmem)
			__mod_lruvec_page_state(new_page, NR_SHMEM, nr_none);
	पूर्ण

xa_locked:
	xas_unlock_irq(&xas);
xa_unlocked:

	अगर (result == SCAN_SUCCEED) अणु
		काष्ठा page *page, *पंचांगp;

		/*
		 * Replacing old pages with new one has succeeded, now we
		 * need to copy the content and मुक्त the old pages.
		 */
		index = start;
		list_क्रम_each_entry_safe(page, पंचांगp, &pagelist, lru) अणु
			जबतक (index < page->index) अणु
				clear_highpage(new_page + (index % HPAGE_PMD_NR));
				index++;
			पूर्ण
			copy_highpage(new_page + (page->index % HPAGE_PMD_NR),
					page);
			list_del(&page->lru);
			page->mapping = शून्य;
			page_ref_unमुक्तze(page, 1);
			ClearPageActive(page);
			ClearPageUnevictable(page);
			unlock_page(page);
			put_page(page);
			index++;
		पूर्ण
		जबतक (index < end) अणु
			clear_highpage(new_page + (index % HPAGE_PMD_NR));
			index++;
		पूर्ण

		SetPageUptodate(new_page);
		page_ref_add(new_page, HPAGE_PMD_NR - 1);
		अगर (is_shmem)
			set_page_dirty(new_page);
		lru_cache_add(new_page);

		/*
		 * Remove pte page tables, so we can re-fault the page as huge.
		 */
		retract_page_tables(mapping, start);
		*hpage = शून्य;

		khugepaged_pages_collapsed++;
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		/* Something went wrong: roll back page cache changes */
		xas_lock_irq(&xas);
		mapping->nrpages -= nr_none;

		अगर (is_shmem)
			shmem_unअक्षरge(mapping->host, nr_none);

		xas_set(&xas, start);
		xas_क्रम_each(&xas, page, end - 1) अणु
			page = list_first_entry_or_null(&pagelist,
					काष्ठा page, lru);
			अगर (!page || xas.xa_index < page->index) अणु
				अगर (!nr_none)
					अवरोध;
				nr_none--;
				/* Put holes back where they were */
				xas_store(&xas, शून्य);
				जारी;
			पूर्ण

			VM_BUG_ON_PAGE(page->index != xas.xa_index, page);

			/* Unमुक्तze the page. */
			list_del(&page->lru);
			page_ref_unमुक्तze(page, 2);
			xas_store(&xas, page);
			xas_छोड़ो(&xas);
			xas_unlock_irq(&xas);
			unlock_page(page);
			putback_lru_page(page);
			xas_lock_irq(&xas);
		पूर्ण
		VM_BUG_ON(nr_none);
		xas_unlock_irq(&xas);

		new_page->mapping = शून्य;
	पूर्ण

	unlock_page(new_page);
out:
	VM_BUG_ON(!list_empty(&pagelist));
	अगर (!IS_ERR_OR_शून्य(*hpage))
		mem_cgroup_unअक्षरge(*hpage);
	/* TODO: tracepoपूर्णांकs */
पूर्ण

अटल व्योम khugepaged_scan_file(काष्ठा mm_काष्ठा *mm,
		काष्ठा file *file, pgoff_t start, काष्ठा page **hpage)
अणु
	काष्ठा page *page = शून्य;
	काष्ठा address_space *mapping = file->f_mapping;
	XA_STATE(xas, &mapping->i_pages, start);
	पूर्णांक present, swap;
	पूर्णांक node = NUMA_NO_NODE;
	पूर्णांक result = SCAN_SUCCEED;

	present = 0;
	swap = 0;
	स_रखो(khugepaged_node_load, 0, माप(khugepaged_node_load));
	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, start + HPAGE_PMD_NR - 1) अणु
		अगर (xas_retry(&xas, page))
			जारी;

		अगर (xa_is_value(page)) अणु
			अगर (++swap > khugepaged_max_ptes_swap) अणु
				result = SCAN_EXCEED_SWAP_PTE;
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		अगर (PageTransCompound(page)) अणु
			result = SCAN_PAGE_COMPOUND;
			अवरोध;
		पूर्ण

		node = page_to_nid(page);
		अगर (khugepaged_scan_पात(node)) अणु
			result = SCAN_SCAN_ABORT;
			अवरोध;
		पूर्ण
		khugepaged_node_load[node]++;

		अगर (!PageLRU(page)) अणु
			result = SCAN_PAGE_LRU;
			अवरोध;
		पूर्ण

		अगर (page_count(page) !=
		    1 + page_mapcount(page) + page_has_निजी(page)) अणु
			result = SCAN_PAGE_COUNT;
			अवरोध;
		पूर्ण

		/*
		 * We probably should check अगर the page is referenced here, but
		 * nobody would transfer pte_young() to PageReferenced() क्रम us.
		 * And rmap walk here is just too costly...
		 */

		present++;

		अगर (need_resched()) अणु
			xas_छोड़ो(&xas);
			cond_resched_rcu();
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (result == SCAN_SUCCEED) अणु
		अगर (present < HPAGE_PMD_NR - khugepaged_max_ptes_none) अणु
			result = SCAN_EXCEED_NONE_PTE;
		पूर्ण अन्यथा अणु
			node = khugepaged_find_target_node();
			collapse_file(mm, file, start, hpage, node);
		पूर्ण
	पूर्ण

	/* TODO: tracepoपूर्णांकs */
पूर्ण
#अन्यथा
अटल व्योम khugepaged_scan_file(काष्ठा mm_काष्ठा *mm,
		काष्ठा file *file, pgoff_t start, काष्ठा page **hpage)
अणु
	BUILD_BUG();
पूर्ण

अटल व्योम khugepaged_collapse_pte_mapped_thps(काष्ठा mm_slot *mm_slot)
अणु
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक khugepaged_scan_mm_slot(अचिन्हित पूर्णांक pages,
					    काष्ठा page **hpage)
	__releases(&khugepaged_mm_lock)
	__acquires(&khugepaged_mm_lock)
अणु
	काष्ठा mm_slot *mm_slot;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक progress = 0;

	VM_BUG_ON(!pages);
	lockdep_निश्चित_held(&khugepaged_mm_lock);

	अगर (khugepaged_scan.mm_slot)
		mm_slot = khugepaged_scan.mm_slot;
	अन्यथा अणु
		mm_slot = list_entry(khugepaged_scan.mm_head.next,
				     काष्ठा mm_slot, mm_node);
		khugepaged_scan.address = 0;
		khugepaged_scan.mm_slot = mm_slot;
	पूर्ण
	spin_unlock(&khugepaged_mm_lock);
	khugepaged_collapse_pte_mapped_thps(mm_slot);

	mm = mm_slot->mm;
	/*
	 * Don't रुको क्रम semaphore (to aव्योम दीर्घ रुको बार).  Just move to
	 * the next mm on the list.
	 */
	vma = शून्य;
	अगर (unlikely(!mmap_पढ़ो_trylock(mm)))
		जाओ अवरोधouterloop_mmap_lock;
	अगर (likely(!khugepaged_test_निकास(mm)))
		vma = find_vma(mm, khugepaged_scan.address);

	progress++;
	क्रम (; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ hstart, hend;

		cond_resched();
		अगर (unlikely(khugepaged_test_निकास(mm))) अणु
			progress++;
			अवरोध;
		पूर्ण
		अगर (!hugepage_vma_check(vma, vma->vm_flags)) अणु
skip:
			progress++;
			जारी;
		पूर्ण
		hstart = (vma->vm_start + ~HPAGE_PMD_MASK) & HPAGE_PMD_MASK;
		hend = vma->vm_end & HPAGE_PMD_MASK;
		अगर (hstart >= hend)
			जाओ skip;
		अगर (khugepaged_scan.address > hend)
			जाओ skip;
		अगर (khugepaged_scan.address < hstart)
			khugepaged_scan.address = hstart;
		VM_BUG_ON(khugepaged_scan.address & ~HPAGE_PMD_MASK);
		अगर (shmem_file(vma->vm_file) && !shmem_huge_enabled(vma))
			जाओ skip;

		जबतक (khugepaged_scan.address < hend) अणु
			पूर्णांक ret;
			cond_resched();
			अगर (unlikely(khugepaged_test_निकास(mm)))
				जाओ अवरोधouterloop;

			VM_BUG_ON(khugepaged_scan.address < hstart ||
				  khugepaged_scan.address + HPAGE_PMD_SIZE >
				  hend);
			अगर (IS_ENABLED(CONFIG_SHMEM) && vma->vm_file) अणु
				काष्ठा file *file = get_file(vma->vm_file);
				pgoff_t pgoff = linear_page_index(vma,
						khugepaged_scan.address);

				mmap_पढ़ो_unlock(mm);
				ret = 1;
				khugepaged_scan_file(mm, file, pgoff, hpage);
				fput(file);
			पूर्ण अन्यथा अणु
				ret = khugepaged_scan_pmd(mm, vma,
						khugepaged_scan.address,
						hpage);
			पूर्ण
			/* move to next address */
			khugepaged_scan.address += HPAGE_PMD_SIZE;
			progress += HPAGE_PMD_NR;
			अगर (ret)
				/* we released mmap_lock so अवरोध loop */
				जाओ अवरोधouterloop_mmap_lock;
			अगर (progress >= pages)
				जाओ अवरोधouterloop;
		पूर्ण
	पूर्ण
अवरोधouterloop:
	mmap_पढ़ो_unlock(mm); /* निकास_mmap will destroy ptes after this */
अवरोधouterloop_mmap_lock:

	spin_lock(&khugepaged_mm_lock);
	VM_BUG_ON(khugepaged_scan.mm_slot != mm_slot);
	/*
	 * Release the current mm_slot अगर this mm is about to die, or
	 * अगर we scanned all vmas of this mm.
	 */
	अगर (khugepaged_test_निकास(mm) || !vma) अणु
		/*
		 * Make sure that अगर mm_users is reaching zero जबतक
		 * khugepaged runs here, khugepaged_निकास will find
		 * mm_slot not poपूर्णांकing to the निकासing mm.
		 */
		अगर (mm_slot->mm_node.next != &khugepaged_scan.mm_head) अणु
			khugepaged_scan.mm_slot = list_entry(
				mm_slot->mm_node.next,
				काष्ठा mm_slot, mm_node);
			khugepaged_scan.address = 0;
		पूर्ण अन्यथा अणु
			khugepaged_scan.mm_slot = शून्य;
			khugepaged_full_scans++;
		पूर्ण

		collect_mm_slot(mm_slot);
	पूर्ण

	वापस progress;
पूर्ण

अटल पूर्णांक khugepaged_has_work(व्योम)
अणु
	वापस !list_empty(&khugepaged_scan.mm_head) &&
		khugepaged_enabled();
पूर्ण

अटल पूर्णांक khugepaged_रुको_event(व्योम)
अणु
	वापस !list_empty(&khugepaged_scan.mm_head) ||
		kthपढ़ो_should_stop();
पूर्ण

अटल व्योम khugepaged_करो_scan(व्योम)
अणु
	काष्ठा page *hpage = शून्य;
	अचिन्हित पूर्णांक progress = 0, pass_through_head = 0;
	अचिन्हित पूर्णांक pages = READ_ONCE(khugepaged_pages_to_scan);
	bool रुको = true;

	lru_add_drain_all();

	जबतक (progress < pages) अणु
		अगर (!khugepaged_pपुनः_स्मृति_page(&hpage, &रुको))
			अवरोध;

		cond_resched();

		अगर (unlikely(kthपढ़ो_should_stop() || try_to_मुक्तze()))
			अवरोध;

		spin_lock(&khugepaged_mm_lock);
		अगर (!khugepaged_scan.mm_slot)
			pass_through_head++;
		अगर (khugepaged_has_work() &&
		    pass_through_head < 2)
			progress += khugepaged_scan_mm_slot(pages - progress,
							    &hpage);
		अन्यथा
			progress = pages;
		spin_unlock(&khugepaged_mm_lock);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(hpage))
		put_page(hpage);
पूर्ण

अटल bool khugepaged_should_wakeup(व्योम)
अणु
	वापस kthपढ़ो_should_stop() ||
	       समय_after_eq(jअगरfies, khugepaged_sleep_expire);
पूर्ण

अटल व्योम khugepaged_रुको_work(व्योम)
अणु
	अगर (khugepaged_has_work()) अणु
		स्थिर अचिन्हित दीर्घ scan_sleep_jअगरfies =
			msecs_to_jअगरfies(khugepaged_scan_sleep_millisecs);

		अगर (!scan_sleep_jअगरfies)
			वापस;

		khugepaged_sleep_expire = jअगरfies + scan_sleep_jअगरfies;
		रुको_event_मुक्तzable_समयout(khugepaged_रुको,
					     khugepaged_should_wakeup(),
					     scan_sleep_jअगरfies);
		वापस;
	पूर्ण

	अगर (khugepaged_enabled())
		रुको_event_मुक्तzable(khugepaged_रुको, khugepaged_रुको_event());
पूर्ण

अटल पूर्णांक khugepaged(व्योम *none)
अणु
	काष्ठा mm_slot *mm_slot;

	set_मुक्तzable();
	set_user_nice(current, MAX_NICE);

	जबतक (!kthपढ़ो_should_stop()) अणु
		khugepaged_करो_scan();
		khugepaged_रुको_work();
	पूर्ण

	spin_lock(&khugepaged_mm_lock);
	mm_slot = khugepaged_scan.mm_slot;
	khugepaged_scan.mm_slot = शून्य;
	अगर (mm_slot)
		collect_mm_slot(mm_slot);
	spin_unlock(&khugepaged_mm_lock);
	वापस 0;
पूर्ण

अटल व्योम set_recommended_min_मुक्त_kbytes(व्योम)
अणु
	काष्ठा zone *zone;
	पूर्णांक nr_zones = 0;
	अचिन्हित दीर्घ recommended_min;

	क्रम_each_populated_zone(zone) अणु
		/*
		 * We करोn't need to worry about fragmentation of
		 * ZONE_MOVABLE since it only has movable pages.
		 */
		अगर (zone_idx(zone) > gfp_zone(GFP_USER))
			जारी;

		nr_zones++;
	पूर्ण

	/* Ensure 2 pageblocks are मुक्त to assist fragmentation aव्योमance */
	recommended_min = pageblock_nr_pages * nr_zones * 2;

	/*
	 * Make sure that on average at least two pageblocks are almost मुक्त
	 * of another type, one क्रम a migratetype to fall back to and a
	 * second to aव्योम subsequent fallbacks of other types There are 3
	 * MIGRATE_TYPES we care about.
	 */
	recommended_min += pageblock_nr_pages * nr_zones *
			   MIGRATE_PCPTYPES * MIGRATE_PCPTYPES;

	/* करोn't ever allow to reserve more than 5% of the lowmem */
	recommended_min = min(recommended_min,
			      (अचिन्हित दीर्घ) nr_मुक्त_buffer_pages() / 20);
	recommended_min <<= (PAGE_SHIFT-10);

	अगर (recommended_min > min_मुक्त_kbytes) अणु
		अगर (user_min_मुक्त_kbytes >= 0)
			pr_info("raising min_free_kbytes from %d to %lu to help transparent hugepage allocations\n",
				min_मुक्त_kbytes, recommended_min);

		min_मुक्त_kbytes = recommended_min;
	पूर्ण
	setup_per_zone_wmarks();
पूर्ण

पूर्णांक start_stop_khugepaged(व्योम)
अणु
	पूर्णांक err = 0;

	mutex_lock(&khugepaged_mutex);
	अगर (khugepaged_enabled()) अणु
		अगर (!khugepaged_thपढ़ो)
			khugepaged_thपढ़ो = kthपढ़ो_run(khugepaged, शून्य,
							"khugepaged");
		अगर (IS_ERR(khugepaged_thपढ़ो)) अणु
			pr_err("khugepaged: kthread_run(khugepaged) failed\n");
			err = PTR_ERR(khugepaged_thपढ़ो);
			khugepaged_thपढ़ो = शून्य;
			जाओ fail;
		पूर्ण

		अगर (!list_empty(&khugepaged_scan.mm_head))
			wake_up_पूर्णांकerruptible(&khugepaged_रुको);

		set_recommended_min_मुक्त_kbytes();
	पूर्ण अन्यथा अगर (khugepaged_thपढ़ो) अणु
		kthपढ़ो_stop(khugepaged_thपढ़ो);
		khugepaged_thपढ़ो = शून्य;
	पूर्ण
fail:
	mutex_unlock(&khugepaged_mutex);
	वापस err;
पूर्ण

व्योम khugepaged_min_मुक्त_kbytes_update(व्योम)
अणु
	mutex_lock(&khugepaged_mutex);
	अगर (khugepaged_enabled() && khugepaged_thपढ़ो)
		set_recommended_min_मुक्त_kbytes();
	mutex_unlock(&khugepaged_mutex);
पूर्ण

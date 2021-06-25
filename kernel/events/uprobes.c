<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * User-space Probes (UProbes)
 *
 * Copyright (C) IBM Corporation, 2008-2012
 * Authors:
 *	Srikar Dronamraju
 *	Jim Keniston
 * Copyright (C) 2011-2012 Red Hat, Inc., Peter Zijlstra
 */

#समावेश <linux/kernel.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>	/* पढ़ो_mapping_page */
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/export.h>
#समावेश <linux/rmap.h>		/* anon_vma_prepare */
#समावेश <linux/mmu_notअगरier.h>	/* set_pte_at_notअगरy */
#समावेश <linux/swap.h>		/* try_to_मुक्त_swap */
#समावेश <linux/ptrace.h>	/* user_enable_single_step */
#समावेश <linux/kdebug.h>	/* notअगरier mechanism */
#समावेश "../../mm/internal.h"	/* munlock_vma_page */
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/task_work.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/khugepaged.h>

#समावेश <linux/uprobes.h>

#घोषणा UINSNS_PER_PAGE			(PAGE_SIZE/UPROBE_XOL_SLOT_BYTES)
#घोषणा MAX_UPROBE_XOL_SLOTS		UINSNS_PER_PAGE

अटल काष्ठा rb_root uprobes_tree = RB_ROOT;
/*
 * allows us to skip the uprobe_mmap अगर there are no uprobe events active
 * at this समय.  Probably a fine grained per inode count is better?
 */
#घोषणा no_uprobe_events()	RB_EMPTY_ROOT(&uprobes_tree)

अटल DEFINE_SPINLOCK(uprobes_treelock);	/* serialize rbtree access */

#घोषणा UPROBES_HASH_SZ	13
/* serialize uprobe->pending_list */
अटल काष्ठा mutex uprobes_mmap_mutex[UPROBES_HASH_SZ];
#घोषणा uprobes_mmap_hash(v)	(&uprobes_mmap_mutex[((अचिन्हित दीर्घ)(v)) % UPROBES_HASH_SZ])

DEFINE_STATIC_PERCPU_RWSEM(dup_mmap_sem);

/* Have a copy of original inकाष्ठाion */
#घोषणा UPROBE_COPY_INSN	0

काष्ठा uprobe अणु
	काष्ठा rb_node		rb_node;	/* node in the rb tree */
	refcount_t		ref;
	काष्ठा rw_semaphore	रेजिस्टर_rwsem;
	काष्ठा rw_semaphore	consumer_rwsem;
	काष्ठा list_head	pending_list;
	काष्ठा uprobe_consumer	*consumers;
	काष्ठा inode		*inode;		/* Also hold a ref to inode */
	loff_t			offset;
	loff_t			ref_ctr_offset;
	अचिन्हित दीर्घ		flags;

	/*
	 * The generic code assumes that it has two members of unknown type
	 * owned by the arch-specअगरic code:
	 *
	 * 	insn -	copy_insn() saves the original inकाष्ठाion here क्रम
	 *		arch_uprobe_analyze_insn().
	 *
	 *	ixol -	potentially modअगरied inकाष्ठाion to execute out of
	 *		line, copied to xol_area by xol_get_insn_slot().
	 */
	काष्ठा arch_uprobe	arch;
पूर्ण;

काष्ठा delayed_uprobe अणु
	काष्ठा list_head list;
	काष्ठा uprobe *uprobe;
	काष्ठा mm_काष्ठा *mm;
पूर्ण;

अटल DEFINE_MUTEX(delayed_uprobe_lock);
अटल LIST_HEAD(delayed_uprobe_list);

/*
 * Execute out of line area: anonymous executable mapping installed
 * by the probed task to execute the copy of the original inकाष्ठाion
 * mangled by set_swbp().
 *
 * On a अवरोधpoपूर्णांक hit, thपढ़ो contests क्रम a slot.  It मुक्तs the
 * slot after singlestep. Currently a fixed number of slots are
 * allocated.
 */
काष्ठा xol_area अणु
	रुको_queue_head_t 		wq;		/* अगर all slots are busy */
	atomic_t 			slot_count;	/* number of in-use slots */
	अचिन्हित दीर्घ 			*biपंचांगap;	/* 0 = मुक्त slot */

	काष्ठा vm_special_mapping	xol_mapping;
	काष्ठा page 			*pages[2];
	/*
	 * We keep the vma's vm_start rather than a poपूर्णांकer to the vma
	 * itself.  The probed process or a naughty kernel module could make
	 * the vma go away, and we must handle that reasonably gracefully.
	 */
	अचिन्हित दीर्घ 			vaddr;		/* Page(s) of inकाष्ठाion slots */
पूर्ण;

/*
 * valid_vma: Verअगरy अगर the specअगरied vma is an executable vma
 * Relax restrictions जबतक unरेजिस्टरing: vm_flags might have
 * changed after अवरोधpoपूर्णांक was inserted.
 *	- is_रेजिस्टर: indicates अगर we are in रेजिस्टर context.
 *	- Return 1 अगर the specअगरied भव address is in an
 *	  executable vma.
 */
अटल bool valid_vma(काष्ठा vm_area_काष्ठा *vma, bool is_रेजिस्टर)
अणु
	vm_flags_t flags = VM_HUGETLB | VM_MAYEXEC | VM_MAYSHARE;

	अगर (is_रेजिस्टर)
		flags |= VM_WRITE;

	वापस vma->vm_file && (vma->vm_flags & flags) == VM_MAYEXEC;
पूर्ण

अटल अचिन्हित दीर्घ offset_to_vaddr(काष्ठा vm_area_काष्ठा *vma, loff_t offset)
अणु
	वापस vma->vm_start + offset - ((loff_t)vma->vm_pgoff << PAGE_SHIFT);
पूर्ण

अटल loff_t vaddr_to_offset(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr)
अणु
	वापस ((loff_t)vma->vm_pgoff << PAGE_SHIFT) + (vaddr - vma->vm_start);
पूर्ण

/**
 * __replace_page - replace page in vma by new page.
 * based on replace_page in mm/ksm.c
 *
 * @vma:      vma that holds the pte poपूर्णांकing to page
 * @addr:     address the old @page is mapped at
 * @old_page: the page we are replacing by new_page
 * @new_page: the modअगरied page we replace page by
 *
 * If @new_page is शून्य, only unmap @old_page.
 *
 * Returns 0 on success, negative error code otherwise.
 */
अटल पूर्णांक __replace_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				काष्ठा page *old_page, काष्ठा page *new_page)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा page_vma_mapped_walk pvmw = अणु
		.page = compound_head(old_page),
		.vma = vma,
		.address = addr,
	पूर्ण;
	पूर्णांक err;
	काष्ठा mmu_notअगरier_range range;

	mmu_notअगरier_range_init(&range, MMU_NOTIFY_CLEAR, 0, vma, mm, addr,
				addr + PAGE_SIZE);

	अगर (new_page) अणु
		err = mem_cgroup_अक्षरge(new_page, vma->vm_mm, GFP_KERNEL);
		अगर (err)
			वापस err;
	पूर्ण

	/* For try_to_मुक्त_swap() and munlock_vma_page() below */
	lock_page(old_page);

	mmu_notअगरier_invalidate_range_start(&range);
	err = -EAGAIN;
	अगर (!page_vma_mapped_walk(&pvmw))
		जाओ unlock;
	VM_BUG_ON_PAGE(addr != pvmw.address, old_page);

	अगर (new_page) अणु
		get_page(new_page);
		page_add_new_anon_rmap(new_page, vma, addr, false);
		lru_cache_add_inactive_or_unevictable(new_page, vma);
	पूर्ण अन्यथा
		/* no new page, just dec_mm_counter क्रम old_page */
		dec_mm_counter(mm, MM_ANONPAGES);

	अगर (!PageAnon(old_page)) अणु
		dec_mm_counter(mm, mm_counter_file(old_page));
		inc_mm_counter(mm, MM_ANONPAGES);
	पूर्ण

	flush_cache_page(vma, addr, pte_pfn(*pvmw.pte));
	ptep_clear_flush_notअगरy(vma, addr, pvmw.pte);
	अगर (new_page)
		set_pte_at_notअगरy(mm, addr, pvmw.pte,
				  mk_pte(new_page, vma->vm_page_prot));

	page_हटाओ_rmap(old_page, false);
	अगर (!page_mapped(old_page))
		try_to_मुक्त_swap(old_page);
	page_vma_mapped_walk_करोne(&pvmw);

	अगर ((vma->vm_flags & VM_LOCKED) && !PageCompound(old_page))
		munlock_vma_page(old_page);
	put_page(old_page);

	err = 0;
 unlock:
	mmu_notअगरier_invalidate_range_end(&range);
	unlock_page(old_page);
	वापस err;
पूर्ण

/**
 * is_swbp_insn - check अगर inकाष्ठाion is अवरोधpoपूर्णांक inकाष्ठाion.
 * @insn: inकाष्ठाion to be checked.
 * Default implementation of is_swbp_insn
 * Returns true अगर @insn is a अवरोधpoपूर्णांक inकाष्ठाion.
 */
bool __weak is_swbp_insn(uprobe_opcode_t *insn)
अणु
	वापस *insn == UPROBE_SWBP_INSN;
पूर्ण

/**
 * is_trap_insn - check अगर inकाष्ठाion is अवरोधpoपूर्णांक inकाष्ठाion.
 * @insn: inकाष्ठाion to be checked.
 * Default implementation of is_trap_insn
 * Returns true अगर @insn is a अवरोधpoपूर्णांक inकाष्ठाion.
 *
 * This function is needed क्रम the हाल where an architecture has multiple
 * trap inकाष्ठाions (like घातerpc).
 */
bool __weak is_trap_insn(uprobe_opcode_t *insn)
अणु
	वापस is_swbp_insn(insn);
पूर्ण

अटल व्योम copy_from_page(काष्ठा page *page, अचिन्हित दीर्घ vaddr, व्योम *dst, पूर्णांक len)
अणु
	व्योम *kaddr = kmap_atomic(page);
	स_नकल(dst, kaddr + (vaddr & ~PAGE_MASK), len);
	kunmap_atomic(kaddr);
पूर्ण

अटल व्योम copy_to_page(काष्ठा page *page, अचिन्हित दीर्घ vaddr, स्थिर व्योम *src, पूर्णांक len)
अणु
	व्योम *kaddr = kmap_atomic(page);
	स_नकल(kaddr + (vaddr & ~PAGE_MASK), src, len);
	kunmap_atomic(kaddr);
पूर्ण

अटल पूर्णांक verअगरy_opcode(काष्ठा page *page, अचिन्हित दीर्घ vaddr, uprobe_opcode_t *new_opcode)
अणु
	uprobe_opcode_t old_opcode;
	bool is_swbp;

	/*
	 * Note: We only check अगर the old_opcode is UPROBE_SWBP_INSN here.
	 * We करो not check अगर it is any other 'trap variant' which could
	 * be conditional trap inकाष्ठाion such as the one घातerpc supports.
	 *
	 * The logic is that we करो not care अगर the underlying inकाष्ठाion
	 * is a trap variant; uprobes always wins over any other (gdb)
	 * अवरोधpoपूर्णांक.
	 */
	copy_from_page(page, vaddr, &old_opcode, UPROBE_SWBP_INSN_SIZE);
	is_swbp = is_swbp_insn(&old_opcode);

	अगर (is_swbp_insn(new_opcode)) अणु
		अगर (is_swbp)		/* रेजिस्टर: alपढ़ोy installed? */
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (!is_swbp)		/* unरेजिस्टर: was it changed by us? */
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा delayed_uprobe *
delayed_uprobe_check(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा delayed_uprobe *du;

	list_क्रम_each_entry(du, &delayed_uprobe_list, list)
		अगर (du->uprobe == uprobe && du->mm == mm)
			वापस du;
	वापस शून्य;
पूर्ण

अटल पूर्णांक delayed_uprobe_add(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा delayed_uprobe *du;

	अगर (delayed_uprobe_check(uprobe, mm))
		वापस 0;

	du  = kzalloc(माप(*du), GFP_KERNEL);
	अगर (!du)
		वापस -ENOMEM;

	du->uprobe = uprobe;
	du->mm = mm;
	list_add(&du->list, &delayed_uprobe_list);
	वापस 0;
पूर्ण

अटल व्योम delayed_uprobe_delete(काष्ठा delayed_uprobe *du)
अणु
	अगर (WARN_ON(!du))
		वापस;
	list_del(&du->list);
	kमुक्त(du);
पूर्ण

अटल व्योम delayed_uprobe_हटाओ(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा list_head *pos, *q;
	काष्ठा delayed_uprobe *du;

	अगर (!uprobe && !mm)
		वापस;

	list_क्रम_each_safe(pos, q, &delayed_uprobe_list) अणु
		du = list_entry(pos, काष्ठा delayed_uprobe, list);

		अगर (uprobe && du->uprobe != uprobe)
			जारी;
		अगर (mm && du->mm != mm)
			जारी;

		delayed_uprobe_delete(du);
	पूर्ण
पूर्ण

अटल bool valid_ref_ctr_vma(काष्ठा uprobe *uprobe,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vaddr = offset_to_vaddr(vma, uprobe->ref_ctr_offset);

	वापस uprobe->ref_ctr_offset &&
		vma->vm_file &&
		file_inode(vma->vm_file) == uprobe->inode &&
		(vma->vm_flags & (VM_WRITE|VM_SHARED)) == VM_WRITE &&
		vma->vm_start <= vaddr &&
		vma->vm_end > vaddr;
पूर्ण

अटल काष्ठा vm_area_काष्ठा *
find_ref_ctr_vma(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *पंचांगp;

	क्रम (पंचांगp = mm->mmap; पंचांगp; पंचांगp = पंचांगp->vm_next)
		अगर (valid_ref_ctr_vma(uprobe, पंचांगp))
			वापस पंचांगp;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
__update_ref_ctr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr, लघु d)
अणु
	व्योम *kaddr;
	काष्ठा page *page;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret;
	लघु *ptr;

	अगर (!vaddr || !d)
		वापस -EINVAL;

	ret = get_user_pages_remote(mm, vaddr, 1,
			FOLL_WRITE, &page, &vma, शून्य);
	अगर (unlikely(ret <= 0)) अणु
		/*
		 * We are asking क्रम 1 page. If get_user_pages_remote() fails,
		 * it may वापस 0, in that हाल we have to वापस error.
		 */
		वापस ret == 0 ? -EBUSY : ret;
	पूर्ण

	kaddr = kmap_atomic(page);
	ptr = kaddr + (vaddr & ~PAGE_MASK);

	अगर (unlikely(*ptr + d < 0)) अणु
		pr_warn("ref_ctr going negative. vaddr: 0x%lx, "
			"curr val: %d, delta: %d\n", vaddr, *ptr, d);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*ptr += d;
	ret = 0;
out:
	kunmap_atomic(kaddr);
	put_page(page);
	वापस ret;
पूर्ण

अटल व्योम update_ref_ctr_warn(काष्ठा uprobe *uprobe,
				काष्ठा mm_काष्ठा *mm, लघु d)
अणु
	pr_warn("ref_ctr %s failed for inode: 0x%lx offset: "
		"0x%llx ref_ctr_offset: 0x%llx of mm: 0x%pK\n",
		d > 0 ? "increment" : "decrement", uprobe->inode->i_ino,
		(अचिन्हित दीर्घ दीर्घ) uprobe->offset,
		(अचिन्हित दीर्घ दीर्घ) uprobe->ref_ctr_offset, mm);
पूर्ण

अटल पूर्णांक update_ref_ctr(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm,
			  लघु d)
अणु
	काष्ठा vm_area_काष्ठा *rc_vma;
	अचिन्हित दीर्घ rc_vaddr;
	पूर्णांक ret = 0;

	rc_vma = find_ref_ctr_vma(uprobe, mm);

	अगर (rc_vma) अणु
		rc_vaddr = offset_to_vaddr(rc_vma, uprobe->ref_ctr_offset);
		ret = __update_ref_ctr(mm, rc_vaddr, d);
		अगर (ret)
			update_ref_ctr_warn(uprobe, mm, d);

		अगर (d > 0)
			वापस ret;
	पूर्ण

	mutex_lock(&delayed_uprobe_lock);
	अगर (d > 0)
		ret = delayed_uprobe_add(uprobe, mm);
	अन्यथा
		delayed_uprobe_हटाओ(uprobe, mm);
	mutex_unlock(&delayed_uprobe_lock);

	वापस ret;
पूर्ण

/*
 * NOTE:
 * Expect the अवरोधpoपूर्णांक inकाष्ठाion to be the smallest size inकाष्ठाion क्रम
 * the architecture. If an arch has variable length inकाष्ठाion and the
 * अवरोधpoपूर्णांक inकाष्ठाion is not of the smallest length inकाष्ठाion
 * supported by that architecture then we need to modअगरy is_trap_at_addr and
 * uprobe_ग_लिखो_opcode accordingly. This would never be a problem क्रम archs
 * that have fixed length inकाष्ठाions.
 *
 * uprobe_ग_लिखो_opcode - ग_लिखो the opcode at a given भव address.
 * @mm: the probed process address space.
 * @vaddr: the भव address to store the opcode.
 * @opcode: opcode to be written at @vaddr.
 *
 * Called with mm->mmap_lock held क्रम ग_लिखो.
 * Return 0 (success) or a negative त्रुटि_सं.
 */
पूर्णांक uprobe_ग_लिखो_opcode(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm,
			अचिन्हित दीर्घ vaddr, uprobe_opcode_t opcode)
अणु
	काष्ठा uprobe *uprobe;
	काष्ठा page *old_page, *new_page;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret, is_रेजिस्टर, ref_ctr_updated = 0;
	bool orig_page_huge = false;
	अचिन्हित पूर्णांक gup_flags = FOLL_FORCE;

	is_रेजिस्टर = is_swbp_insn(&opcode);
	uprobe = container_of(auprobe, काष्ठा uprobe, arch);

retry:
	अगर (is_रेजिस्टर)
		gup_flags |= FOLL_SPLIT_PMD;
	/* Read the page with vaddr पूर्णांकo memory */
	ret = get_user_pages_remote(mm, vaddr, 1, gup_flags,
				    &old_page, &vma, शून्य);
	अगर (ret <= 0)
		वापस ret;

	ret = verअगरy_opcode(old_page, vaddr, &opcode);
	अगर (ret <= 0)
		जाओ put_old;

	अगर (WARN(!is_रेजिस्टर && PageCompound(old_page),
		 "uprobe unregister should never work on compound page\n")) अणु
		ret = -EINVAL;
		जाओ put_old;
	पूर्ण

	/* We are going to replace inकाष्ठाion, update ref_ctr. */
	अगर (!ref_ctr_updated && uprobe->ref_ctr_offset) अणु
		ret = update_ref_ctr(uprobe, mm, is_रेजिस्टर ? 1 : -1);
		अगर (ret)
			जाओ put_old;

		ref_ctr_updated = 1;
	पूर्ण

	ret = 0;
	अगर (!is_रेजिस्टर && !PageAnon(old_page))
		जाओ put_old;

	ret = anon_vma_prepare(vma);
	अगर (ret)
		जाओ put_old;

	ret = -ENOMEM;
	new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, vaddr);
	अगर (!new_page)
		जाओ put_old;

	__SetPageUptodate(new_page);
	copy_highpage(new_page, old_page);
	copy_to_page(new_page, vaddr, &opcode, UPROBE_SWBP_INSN_SIZE);

	अगर (!is_रेजिस्टर) अणु
		काष्ठा page *orig_page;
		pgoff_t index;

		VM_BUG_ON_PAGE(!PageAnon(old_page), old_page);

		index = vaddr_to_offset(vma, vaddr & PAGE_MASK) >> PAGE_SHIFT;
		orig_page = find_get_page(vma->vm_file->f_inode->i_mapping,
					  index);

		अगर (orig_page) अणु
			अगर (PageUptodate(orig_page) &&
			    pages_identical(new_page, orig_page)) अणु
				/* let go new_page */
				put_page(new_page);
				new_page = शून्य;

				अगर (PageCompound(orig_page))
					orig_page_huge = true;
			पूर्ण
			put_page(orig_page);
		पूर्ण
	पूर्ण

	ret = __replace_page(vma, vaddr, old_page, new_page);
	अगर (new_page)
		put_page(new_page);
put_old:
	put_page(old_page);

	अगर (unlikely(ret == -EAGAIN))
		जाओ retry;

	/* Revert back reference counter अगर inकाष्ठाion update failed. */
	अगर (ret && is_रेजिस्टर && ref_ctr_updated)
		update_ref_ctr(uprobe, mm, -1);

	/* try collapse pmd क्रम compound page */
	अगर (!ret && orig_page_huge)
		collapse_pte_mapped_thp(mm, vaddr);

	वापस ret;
पूर्ण

/**
 * set_swbp - store अवरोधpoपूर्णांक at a given address.
 * @auprobe: arch specअगरic probepoपूर्णांक inक्रमmation.
 * @mm: the probed process address space.
 * @vaddr: the भव address to insert the opcode.
 *
 * For mm @mm, store the अवरोधpoपूर्णांक inकाष्ठाion at @vaddr.
 * Return 0 (success) or a negative त्रुटि_सं.
 */
पूर्णांक __weak set_swbp(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	वापस uprobe_ग_लिखो_opcode(auprobe, mm, vaddr, UPROBE_SWBP_INSN);
पूर्ण

/**
 * set_orig_insn - Restore the original inकाष्ठाion.
 * @mm: the probed process address space.
 * @auprobe: arch specअगरic probepoपूर्णांक inक्रमmation.
 * @vaddr: the भव address to insert the opcode.
 *
 * For mm @mm, restore the original opcode (opcode) at @vaddr.
 * Return 0 (success) or a negative त्रुटि_सं.
 */
पूर्णांक __weak
set_orig_insn(काष्ठा arch_uprobe *auprobe, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	वापस uprobe_ग_लिखो_opcode(auprobe, mm, vaddr,
			*(uprobe_opcode_t *)&auprobe->insn);
पूर्ण

अटल काष्ठा uprobe *get_uprobe(काष्ठा uprobe *uprobe)
अणु
	refcount_inc(&uprobe->ref);
	वापस uprobe;
पूर्ण

अटल व्योम put_uprobe(काष्ठा uprobe *uprobe)
अणु
	अगर (refcount_dec_and_test(&uprobe->ref)) अणु
		/*
		 * If application munmap(exec_vma) beक्रमe uprobe_unरेजिस्टर()
		 * माला_लो called, we करोn't get a chance to हटाओ uprobe from
		 * delayed_uprobe_list from हटाओ_अवरोधpoपूर्णांक(). Do it here.
		 */
		mutex_lock(&delayed_uprobe_lock);
		delayed_uprobe_हटाओ(uprobe, शून्य);
		mutex_unlock(&delayed_uprobe_lock);
		kमुक्त(uprobe);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत
पूर्णांक uprobe_cmp(स्थिर काष्ठा inode *l_inode, स्थिर loff_t l_offset,
	       स्थिर काष्ठा uprobe *r)
अणु
	अगर (l_inode < r->inode)
		वापस -1;

	अगर (l_inode > r->inode)
		वापस 1;

	अगर (l_offset < r->offset)
		वापस -1;

	अगर (l_offset > r->offset)
		वापस 1;

	वापस 0;
पूर्ण

#घोषणा __node_2_uprobe(node) \
	rb_entry((node), काष्ठा uprobe, rb_node)

काष्ठा __uprobe_key अणु
	काष्ठा inode *inode;
	loff_t offset;
पूर्ण;

अटल अंतरभूत पूर्णांक __uprobe_cmp_key(स्थिर व्योम *key, स्थिर काष्ठा rb_node *b)
अणु
	स्थिर काष्ठा __uprobe_key *a = key;
	वापस uprobe_cmp(a->inode, a->offset, __node_2_uprobe(b));
पूर्ण

अटल अंतरभूत पूर्णांक __uprobe_cmp(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	काष्ठा uprobe *u = __node_2_uprobe(a);
	वापस uprobe_cmp(u->inode, u->offset, __node_2_uprobe(b));
पूर्ण

अटल काष्ठा uprobe *__find_uprobe(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा __uprobe_key key = अणु
		.inode = inode,
		.offset = offset,
	पूर्ण;
	काष्ठा rb_node *node = rb_find(&key, &uprobes_tree, __uprobe_cmp_key);

	अगर (node)
		वापस get_uprobe(__node_2_uprobe(node));

	वापस शून्य;
पूर्ण

/*
 * Find a uprobe corresponding to a given inode:offset
 * Acquires uprobes_treelock
 */
अटल काष्ठा uprobe *find_uprobe(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा uprobe *uprobe;

	spin_lock(&uprobes_treelock);
	uprobe = __find_uprobe(inode, offset);
	spin_unlock(&uprobes_treelock);

	वापस uprobe;
पूर्ण

अटल काष्ठा uprobe *__insert_uprobe(काष्ठा uprobe *uprobe)
अणु
	काष्ठा rb_node *node;

	node = rb_find_add(&uprobe->rb_node, &uprobes_tree, __uprobe_cmp);
	अगर (node)
		वापस get_uprobe(__node_2_uprobe(node));

	/* get access + creation ref */
	refcount_set(&uprobe->ref, 2);
	वापस शून्य;
पूर्ण

/*
 * Acquire uprobes_treelock.
 * Matching uprobe alपढ़ोy exists in rbtree;
 *	increment (access refcount) and वापस the matching uprobe.
 *
 * No matching uprobe; insert the uprobe in rb_tree;
 *	get a द्विगुन refcount (access + creation) and वापस शून्य.
 */
अटल काष्ठा uprobe *insert_uprobe(काष्ठा uprobe *uprobe)
अणु
	काष्ठा uprobe *u;

	spin_lock(&uprobes_treelock);
	u = __insert_uprobe(uprobe);
	spin_unlock(&uprobes_treelock);

	वापस u;
पूर्ण

अटल व्योम
ref_ctr_mismatch_warn(काष्ठा uprobe *cur_uprobe, काष्ठा uprobe *uprobe)
अणु
	pr_warn("ref_ctr_offset mismatch. inode: 0x%lx offset: 0x%llx "
		"ref_ctr_offset(old): 0x%llx ref_ctr_offset(new): 0x%llx\n",
		uprobe->inode->i_ino, (अचिन्हित दीर्घ दीर्घ) uprobe->offset,
		(अचिन्हित दीर्घ दीर्घ) cur_uprobe->ref_ctr_offset,
		(अचिन्हित दीर्घ दीर्घ) uprobe->ref_ctr_offset);
पूर्ण

अटल काष्ठा uprobe *alloc_uprobe(काष्ठा inode *inode, loff_t offset,
				   loff_t ref_ctr_offset)
अणु
	काष्ठा uprobe *uprobe, *cur_uprobe;

	uprobe = kzalloc(माप(काष्ठा uprobe), GFP_KERNEL);
	अगर (!uprobe)
		वापस शून्य;

	uprobe->inode = inode;
	uprobe->offset = offset;
	uprobe->ref_ctr_offset = ref_ctr_offset;
	init_rwsem(&uprobe->रेजिस्टर_rwsem);
	init_rwsem(&uprobe->consumer_rwsem);

	/* add to uprobes_tree, sorted on inode:offset */
	cur_uprobe = insert_uprobe(uprobe);
	/* a uprobe exists क्रम this inode:offset combination */
	अगर (cur_uprobe) अणु
		अगर (cur_uprobe->ref_ctr_offset != uprobe->ref_ctr_offset) अणु
			ref_ctr_mismatch_warn(cur_uprobe, uprobe);
			put_uprobe(cur_uprobe);
			kमुक्त(uprobe);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		kमुक्त(uprobe);
		uprobe = cur_uprobe;
	पूर्ण

	वापस uprobe;
पूर्ण

अटल व्योम consumer_add(काष्ठा uprobe *uprobe, काष्ठा uprobe_consumer *uc)
अणु
	करोwn_ग_लिखो(&uprobe->consumer_rwsem);
	uc->next = uprobe->consumers;
	uprobe->consumers = uc;
	up_ग_लिखो(&uprobe->consumer_rwsem);
पूर्ण

/*
 * For uprobe @uprobe, delete the consumer @uc.
 * Return true अगर the @uc is deleted successfully
 * or वापस false.
 */
अटल bool consumer_del(काष्ठा uprobe *uprobe, काष्ठा uprobe_consumer *uc)
अणु
	काष्ठा uprobe_consumer **con;
	bool ret = false;

	करोwn_ग_लिखो(&uprobe->consumer_rwsem);
	क्रम (con = &uprobe->consumers; *con; con = &(*con)->next) अणु
		अगर (*con == uc) अणु
			*con = uc->next;
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&uprobe->consumer_rwsem);

	वापस ret;
पूर्ण

अटल पूर्णांक __copy_insn(काष्ठा address_space *mapping, काष्ठा file *filp,
			व्योम *insn, पूर्णांक nbytes, loff_t offset)
अणु
	काष्ठा page *page;
	/*
	 * Ensure that the page that has the original inकाष्ठाion is populated
	 * and in page-cache. If ->पढ़ोpage == शून्य it must be shmem_mapping(),
	 * see uprobe_रेजिस्टर().
	 */
	अगर (mapping->a_ops->पढ़ोpage)
		page = पढ़ो_mapping_page(mapping, offset >> PAGE_SHIFT, filp);
	अन्यथा
		page = shmem_पढ़ो_mapping_page(mapping, offset >> PAGE_SHIFT);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	copy_from_page(page, offset, insn, nbytes);
	put_page(page);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_insn(काष्ठा uprobe *uprobe, काष्ठा file *filp)
अणु
	काष्ठा address_space *mapping = uprobe->inode->i_mapping;
	loff_t offs = uprobe->offset;
	व्योम *insn = &uprobe->arch.insn;
	पूर्णांक size = माप(uprobe->arch.insn);
	पूर्णांक len, err = -EIO;

	/* Copy only available bytes, -EIO अगर nothing was पढ़ो */
	करो अणु
		अगर (offs >= i_size_पढ़ो(uprobe->inode))
			अवरोध;

		len = min_t(पूर्णांक, size, PAGE_SIZE - (offs & ~PAGE_MASK));
		err = __copy_insn(mapping, filp, insn, len, offs);
		अगर (err)
			अवरोध;

		insn += len;
		offs += len;
		size -= len;
	पूर्ण जबतक (size);

	वापस err;
पूर्ण

अटल पूर्णांक prepare_uprobe(काष्ठा uprobe *uprobe, काष्ठा file *file,
				काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	पूर्णांक ret = 0;

	अगर (test_bit(UPROBE_COPY_INSN, &uprobe->flags))
		वापस ret;

	/* TODO: move this पूर्णांकo _रेजिस्टर, until then we abuse this sem. */
	करोwn_ग_लिखो(&uprobe->consumer_rwsem);
	अगर (test_bit(UPROBE_COPY_INSN, &uprobe->flags))
		जाओ out;

	ret = copy_insn(uprobe, file);
	अगर (ret)
		जाओ out;

	ret = -ENOTSUPP;
	अगर (is_trap_insn((uprobe_opcode_t *)&uprobe->arch.insn))
		जाओ out;

	ret = arch_uprobe_analyze_insn(&uprobe->arch, mm, vaddr);
	अगर (ret)
		जाओ out;

	smp_wmb(); /* pairs with the smp_rmb() in handle_swbp() */
	set_bit(UPROBE_COPY_INSN, &uprobe->flags);

 out:
	up_ग_लिखो(&uprobe->consumer_rwsem);

	वापस ret;
पूर्ण

अटल अंतरभूत bool consumer_filter(काष्ठा uprobe_consumer *uc,
				   क्रमागत uprobe_filter_ctx ctx, काष्ठा mm_काष्ठा *mm)
अणु
	वापस !uc->filter || uc->filter(uc, ctx, mm);
पूर्ण

अटल bool filter_chain(काष्ठा uprobe *uprobe,
			 क्रमागत uprobe_filter_ctx ctx, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा uprobe_consumer *uc;
	bool ret = false;

	करोwn_पढ़ो(&uprobe->consumer_rwsem);
	क्रम (uc = uprobe->consumers; uc; uc = uc->next) अणु
		ret = consumer_filter(uc, ctx, mm);
		अगर (ret)
			अवरोध;
	पूर्ण
	up_पढ़ो(&uprobe->consumer_rwsem);

	वापस ret;
पूर्ण

अटल पूर्णांक
install_अवरोधpoपूर्णांक(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr)
अणु
	bool first_uprobe;
	पूर्णांक ret;

	ret = prepare_uprobe(uprobe, vma->vm_file, mm, vaddr);
	अगर (ret)
		वापस ret;

	/*
	 * set MMF_HAS_UPROBES in advance क्रम uprobe_pre_sstep_notअगरier(),
	 * the task can hit this अवरोधpoपूर्णांक right after __replace_page().
	 */
	first_uprobe = !test_bit(MMF_HAS_UPROBES, &mm->flags);
	अगर (first_uprobe)
		set_bit(MMF_HAS_UPROBES, &mm->flags);

	ret = set_swbp(&uprobe->arch, mm, vaddr);
	अगर (!ret)
		clear_bit(MMF_RECALC_UPROBES, &mm->flags);
	अन्यथा अगर (first_uprobe)
		clear_bit(MMF_HAS_UPROBES, &mm->flags);

	वापस ret;
पूर्ण

अटल पूर्णांक
हटाओ_अवरोधpoपूर्णांक(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	set_bit(MMF_RECALC_UPROBES, &mm->flags);
	वापस set_orig_insn(&uprobe->arch, mm, vaddr);
पूर्ण

अटल अंतरभूत bool uprobe_is_active(काष्ठा uprobe *uprobe)
अणु
	वापस !RB_EMPTY_NODE(&uprobe->rb_node);
पूर्ण
/*
 * There could be thपढ़ोs that have alपढ़ोy hit the अवरोधpoपूर्णांक. They
 * will recheck the current insn and restart अगर find_uprobe() fails.
 * See find_active_uprobe().
 */
अटल व्योम delete_uprobe(काष्ठा uprobe *uprobe)
अणु
	अगर (WARN_ON(!uprobe_is_active(uprobe)))
		वापस;

	spin_lock(&uprobes_treelock);
	rb_erase(&uprobe->rb_node, &uprobes_tree);
	spin_unlock(&uprobes_treelock);
	RB_CLEAR_NODE(&uprobe->rb_node); /* क्रम uprobe_is_active() */
	put_uprobe(uprobe);
पूर्ण

काष्ठा map_info अणु
	काष्ठा map_info *next;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ vaddr;
पूर्ण;

अटल अंतरभूत काष्ठा map_info *मुक्त_map_info(काष्ठा map_info *info)
अणु
	काष्ठा map_info *next = info->next;
	kमुक्त(info);
	वापस next;
पूर्ण

अटल काष्ठा map_info *
build_map_info(काष्ठा address_space *mapping, loff_t offset, bool is_रेजिस्टर)
अणु
	अचिन्हित दीर्घ pgoff = offset >> PAGE_SHIFT;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा map_info *curr = शून्य;
	काष्ठा map_info *prev = शून्य;
	काष्ठा map_info *info;
	पूर्णांक more = 0;

 again:
	i_mmap_lock_पढ़ो(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap, pgoff, pgoff) अणु
		अगर (!valid_vma(vma, is_रेजिस्टर))
			जारी;

		अगर (!prev && !more) अणु
			/*
			 * Needs GFP_NOWAIT to aव्योम i_mmap_rwsem recursion through
			 * reclaim. This is optimistic, no harm करोne अगर it fails.
			 */
			prev = kदो_स्मृति(माप(काष्ठा map_info),
					GFP_NOWAIT | __GFP_NOMEMALLOC | __GFP_NOWARN);
			अगर (prev)
				prev->next = शून्य;
		पूर्ण
		अगर (!prev) अणु
			more++;
			जारी;
		पूर्ण

		अगर (!mmget_not_zero(vma->vm_mm))
			जारी;

		info = prev;
		prev = prev->next;
		info->next = curr;
		curr = info;

		info->mm = vma->vm_mm;
		info->vaddr = offset_to_vaddr(vma, offset);
	पूर्ण
	i_mmap_unlock_पढ़ो(mapping);

	अगर (!more)
		जाओ out;

	prev = curr;
	जबतक (curr) अणु
		mmput(curr->mm);
		curr = curr->next;
	पूर्ण

	करो अणु
		info = kदो_स्मृति(माप(काष्ठा map_info), GFP_KERNEL);
		अगर (!info) अणु
			curr = ERR_PTR(-ENOMEM);
			जाओ out;
		पूर्ण
		info->next = prev;
		prev = info;
	पूर्ण जबतक (--more);

	जाओ again;
 out:
	जबतक (prev)
		prev = मुक्त_map_info(prev);
	वापस curr;
पूर्ण

अटल पूर्णांक
रेजिस्टर_क्रम_each_vma(काष्ठा uprobe *uprobe, काष्ठा uprobe_consumer *new)
अणु
	bool is_रेजिस्टर = !!new;
	काष्ठा map_info *info;
	पूर्णांक err = 0;

	percpu_करोwn_ग_लिखो(&dup_mmap_sem);
	info = build_map_info(uprobe->inode->i_mapping,
					uprobe->offset, is_रेजिस्टर);
	अगर (IS_ERR(info)) अणु
		err = PTR_ERR(info);
		जाओ out;
	पूर्ण

	जबतक (info) अणु
		काष्ठा mm_काष्ठा *mm = info->mm;
		काष्ठा vm_area_काष्ठा *vma;

		अगर (err && is_रेजिस्टर)
			जाओ मुक्त;

		mmap_ग_लिखो_lock(mm);
		vma = find_vma(mm, info->vaddr);
		अगर (!vma || !valid_vma(vma, is_रेजिस्टर) ||
		    file_inode(vma->vm_file) != uprobe->inode)
			जाओ unlock;

		अगर (vma->vm_start > info->vaddr ||
		    vaddr_to_offset(vma, info->vaddr) != uprobe->offset)
			जाओ unlock;

		अगर (is_रेजिस्टर) अणु
			/* consult only the "caller", new consumer. */
			अगर (consumer_filter(new,
					UPROBE_FILTER_REGISTER, mm))
				err = install_अवरोधpoपूर्णांक(uprobe, mm, vma, info->vaddr);
		पूर्ण अन्यथा अगर (test_bit(MMF_HAS_UPROBES, &mm->flags)) अणु
			अगर (!filter_chain(uprobe,
					UPROBE_FILTER_UNREGISTER, mm))
				err |= हटाओ_अवरोधpoपूर्णांक(uprobe, mm, info->vaddr);
		पूर्ण

 unlock:
		mmap_ग_लिखो_unlock(mm);
 मुक्त:
		mmput(mm);
		info = मुक्त_map_info(info);
	पूर्ण
 out:
	percpu_up_ग_लिखो(&dup_mmap_sem);
	वापस err;
पूर्ण

अटल व्योम
__uprobe_unरेजिस्टर(काष्ठा uprobe *uprobe, काष्ठा uprobe_consumer *uc)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!consumer_del(uprobe, uc)))
		वापस;

	err = रेजिस्टर_क्रम_each_vma(uprobe, शून्य);
	/* TODO : cant unरेजिस्टर? schedule a worker thपढ़ो */
	अगर (!uprobe->consumers && !err)
		delete_uprobe(uprobe);
पूर्ण

/*
 * uprobe_unरेजिस्टर - unरेजिस्टर an alपढ़ोy रेजिस्टरed probe.
 * @inode: the file in which the probe has to be हटाओd.
 * @offset: offset from the start of the file.
 * @uc: identअगरy which probe अगर multiple probes are colocated.
 */
व्योम uprobe_unरेजिस्टर(काष्ठा inode *inode, loff_t offset, काष्ठा uprobe_consumer *uc)
अणु
	काष्ठा uprobe *uprobe;

	uprobe = find_uprobe(inode, offset);
	अगर (WARN_ON(!uprobe))
		वापस;

	करोwn_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	__uprobe_unरेजिस्टर(uprobe, uc);
	up_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	put_uprobe(uprobe);
पूर्ण
EXPORT_SYMBOL_GPL(uprobe_unरेजिस्टर);

/*
 * __uprobe_रेजिस्टर - रेजिस्टर a probe
 * @inode: the file in which the probe has to be placed.
 * @offset: offset from the start of the file.
 * @uc: inक्रमmation on howto handle the probe..
 *
 * Apart from the access refcount, __uprobe_रेजिस्टर() takes a creation
 * refcount (thro alloc_uprobe) अगर and only अगर this @uprobe is getting
 * inserted पूर्णांकo the rbtree (i.e first consumer क्रम a @inode:@offset
 * tuple).  Creation refcount stops uprobe_unरेजिस्टर from मुक्तing the
 * @uprobe even beक्रमe the रेजिस्टर operation is complete. Creation
 * refcount is released when the last @uc क्रम the @uprobe
 * unरेजिस्टरs. Caller of __uprobe_रेजिस्टर() is required to keep @inode
 * (and the containing mount) referenced.
 *
 * Return त्रुटि_सं अगर it cannot successully install probes
 * अन्यथा वापस 0 (success)
 */
अटल पूर्णांक __uprobe_रेजिस्टर(काष्ठा inode *inode, loff_t offset,
			     loff_t ref_ctr_offset, काष्ठा uprobe_consumer *uc)
अणु
	काष्ठा uprobe *uprobe;
	पूर्णांक ret;

	/* Uprobe must have at least one set consumer */
	अगर (!uc->handler && !uc->ret_handler)
		वापस -EINVAL;

	/* copy_insn() uses पढ़ो_mapping_page() or shmem_पढ़ो_mapping_page() */
	अगर (!inode->i_mapping->a_ops->पढ़ोpage && !shmem_mapping(inode->i_mapping))
		वापस -EIO;
	/* Racy, just to catch the obvious mistakes */
	अगर (offset > i_size_पढ़ो(inode))
		वापस -EINVAL;

	/*
	 * This ensures that copy_from_page(), copy_to_page() and
	 * __update_ref_ctr() can't cross page boundary.
	 */
	अगर (!IS_ALIGNED(offset, UPROBE_SWBP_INSN_SIZE))
		वापस -EINVAL;
	अगर (!IS_ALIGNED(ref_ctr_offset, माप(लघु)))
		वापस -EINVAL;

 retry:
	uprobe = alloc_uprobe(inode, offset, ref_ctr_offset);
	अगर (!uprobe)
		वापस -ENOMEM;
	अगर (IS_ERR(uprobe))
		वापस PTR_ERR(uprobe);

	/*
	 * We can race with uprobe_unरेजिस्टर()->delete_uprobe().
	 * Check uprobe_is_active() and retry अगर it is false.
	 */
	करोwn_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	ret = -EAGAIN;
	अगर (likely(uprobe_is_active(uprobe))) अणु
		consumer_add(uprobe, uc);
		ret = रेजिस्टर_क्रम_each_vma(uprobe, uc);
		अगर (ret)
			__uprobe_unरेजिस्टर(uprobe, uc);
	पूर्ण
	up_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	put_uprobe(uprobe);

	अगर (unlikely(ret == -EAGAIN))
		जाओ retry;
	वापस ret;
पूर्ण

पूर्णांक uprobe_रेजिस्टर(काष्ठा inode *inode, loff_t offset,
		    काष्ठा uprobe_consumer *uc)
अणु
	वापस __uprobe_रेजिस्टर(inode, offset, 0, uc);
पूर्ण
EXPORT_SYMBOL_GPL(uprobe_रेजिस्टर);

पूर्णांक uprobe_रेजिस्टर_refctr(काष्ठा inode *inode, loff_t offset,
			   loff_t ref_ctr_offset, काष्ठा uprobe_consumer *uc)
अणु
	वापस __uprobe_रेजिस्टर(inode, offset, ref_ctr_offset, uc);
पूर्ण
EXPORT_SYMBOL_GPL(uprobe_रेजिस्टर_refctr);

/*
 * uprobe_apply - unरेजिस्टर an alपढ़ोy रेजिस्टरed probe.
 * @inode: the file in which the probe has to be हटाओd.
 * @offset: offset from the start of the file.
 * @uc: consumer which wants to add more or हटाओ some अवरोधpoपूर्णांकs
 * @add: add or हटाओ the अवरोधpoपूर्णांकs
 */
पूर्णांक uprobe_apply(काष्ठा inode *inode, loff_t offset,
			काष्ठा uprobe_consumer *uc, bool add)
अणु
	काष्ठा uprobe *uprobe;
	काष्ठा uprobe_consumer *con;
	पूर्णांक ret = -ENOENT;

	uprobe = find_uprobe(inode, offset);
	अगर (WARN_ON(!uprobe))
		वापस ret;

	करोwn_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	क्रम (con = uprobe->consumers; con && con != uc ; con = con->next)
		;
	अगर (con)
		ret = रेजिस्टर_क्रम_each_vma(uprobe, add ? uc : शून्य);
	up_ग_लिखो(&uprobe->रेजिस्टर_rwsem);
	put_uprobe(uprobe);

	वापस ret;
पूर्ण

अटल पूर्णांक unapply_uprobe(काष्ठा uprobe *uprobe, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक err = 0;

	mmap_पढ़ो_lock(mm);
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ vaddr;
		loff_t offset;

		अगर (!valid_vma(vma, false) ||
		    file_inode(vma->vm_file) != uprobe->inode)
			जारी;

		offset = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
		अगर (uprobe->offset <  offset ||
		    uprobe->offset >= offset + vma->vm_end - vma->vm_start)
			जारी;

		vaddr = offset_to_vaddr(vma, uprobe->offset);
		err |= हटाओ_अवरोधpoपूर्णांक(uprobe, mm, vaddr);
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	वापस err;
पूर्ण

अटल काष्ठा rb_node *
find_node_in_range(काष्ठा inode *inode, loff_t min, loff_t max)
अणु
	काष्ठा rb_node *n = uprobes_tree.rb_node;

	जबतक (n) अणु
		काष्ठा uprobe *u = rb_entry(n, काष्ठा uprobe, rb_node);

		अगर (inode < u->inode) अणु
			n = n->rb_left;
		पूर्ण अन्यथा अगर (inode > u->inode) अणु
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			अगर (max < u->offset)
				n = n->rb_left;
			अन्यथा अगर (min > u->offset)
				n = n->rb_right;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण

/*
 * For a given range in vma, build a list of probes that need to be inserted.
 */
अटल व्योम build_probe_list(काष्ठा inode *inode,
				काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				काष्ठा list_head *head)
अणु
	loff_t min, max;
	काष्ठा rb_node *n, *t;
	काष्ठा uprobe *u;

	INIT_LIST_HEAD(head);
	min = vaddr_to_offset(vma, start);
	max = min + (end - start) - 1;

	spin_lock(&uprobes_treelock);
	n = find_node_in_range(inode, min, max);
	अगर (n) अणु
		क्रम (t = n; t; t = rb_prev(t)) अणु
			u = rb_entry(t, काष्ठा uprobe, rb_node);
			अगर (u->inode != inode || u->offset < min)
				अवरोध;
			list_add(&u->pending_list, head);
			get_uprobe(u);
		पूर्ण
		क्रम (t = n; (t = rb_next(t)); ) अणु
			u = rb_entry(t, काष्ठा uprobe, rb_node);
			अगर (u->inode != inode || u->offset > max)
				अवरोध;
			list_add(&u->pending_list, head);
			get_uprobe(u);
		पूर्ण
	पूर्ण
	spin_unlock(&uprobes_treelock);
पूर्ण

/* @vma contains reference counter, not the probed inकाष्ठाion. */
अटल पूर्णांक delayed_ref_ctr_inc(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा list_head *pos, *q;
	काष्ठा delayed_uprobe *du;
	अचिन्हित दीर्घ vaddr;
	पूर्णांक ret = 0, err = 0;

	mutex_lock(&delayed_uprobe_lock);
	list_क्रम_each_safe(pos, q, &delayed_uprobe_list) अणु
		du = list_entry(pos, काष्ठा delayed_uprobe, list);

		अगर (du->mm != vma->vm_mm ||
		    !valid_ref_ctr_vma(du->uprobe, vma))
			जारी;

		vaddr = offset_to_vaddr(vma, du->uprobe->ref_ctr_offset);
		ret = __update_ref_ctr(vma->vm_mm, vaddr, 1);
		अगर (ret) अणु
			update_ref_ctr_warn(du->uprobe, vma->vm_mm, 1);
			अगर (!err)
				err = ret;
		पूर्ण
		delayed_uprobe_delete(du);
	पूर्ण
	mutex_unlock(&delayed_uprobe_lock);
	वापस err;
पूर्ण

/*
 * Called from mmap_region/vma_adjust with mm->mmap_lock acquired.
 *
 * Currently we ignore all errors and always वापस 0, the callers
 * can't handle the failure anyway.
 */
पूर्णांक uprobe_mmap(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा list_head पंचांगp_list;
	काष्ठा uprobe *uprobe, *u;
	काष्ठा inode *inode;

	अगर (no_uprobe_events())
		वापस 0;

	अगर (vma->vm_file &&
	    (vma->vm_flags & (VM_WRITE|VM_SHARED)) == VM_WRITE &&
	    test_bit(MMF_HAS_UPROBES, &vma->vm_mm->flags))
		delayed_ref_ctr_inc(vma);

	अगर (!valid_vma(vma, true))
		वापस 0;

	inode = file_inode(vma->vm_file);
	अगर (!inode)
		वापस 0;

	mutex_lock(uprobes_mmap_hash(inode));
	build_probe_list(inode, vma, vma->vm_start, vma->vm_end, &पंचांगp_list);
	/*
	 * We can race with uprobe_unरेजिस्टर(), this uprobe can be alपढ़ोy
	 * हटाओd. But in this हाल filter_chain() must वापस false, all
	 * consumers have gone away.
	 */
	list_क्रम_each_entry_safe(uprobe, u, &पंचांगp_list, pending_list) अणु
		अगर (!fatal_संकेत_pending(current) &&
		    filter_chain(uprobe, UPROBE_FILTER_MMAP, vma->vm_mm)) अणु
			अचिन्हित दीर्घ vaddr = offset_to_vaddr(vma, uprobe->offset);
			install_अवरोधpoपूर्णांक(uprobe, vma->vm_mm, vma, vaddr);
		पूर्ण
		put_uprobe(uprobe);
	पूर्ण
	mutex_unlock(uprobes_mmap_hash(inode));

	वापस 0;
पूर्ण

अटल bool
vma_has_uprobes(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	loff_t min, max;
	काष्ठा inode *inode;
	काष्ठा rb_node *n;

	inode = file_inode(vma->vm_file);

	min = vaddr_to_offset(vma, start);
	max = min + (end - start) - 1;

	spin_lock(&uprobes_treelock);
	n = find_node_in_range(inode, min, max);
	spin_unlock(&uprobes_treelock);

	वापस !!n;
पूर्ण

/*
 * Called in context of a munmap of a vma.
 */
व्योम uprobe_munmap(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (no_uprobe_events() || !valid_vma(vma, false))
		वापस;

	अगर (!atomic_पढ़ो(&vma->vm_mm->mm_users)) /* called by mmput() ? */
		वापस;

	अगर (!test_bit(MMF_HAS_UPROBES, &vma->vm_mm->flags) ||
	     test_bit(MMF_RECALC_UPROBES, &vma->vm_mm->flags))
		वापस;

	अगर (vma_has_uprobes(vma, start, end))
		set_bit(MMF_RECALC_UPROBES, &vma->vm_mm->flags);
पूर्ण

/* Slot allocation क्रम XOL */
अटल पूर्णांक xol_add_vma(काष्ठा mm_काष्ठा *mm, काष्ठा xol_area *area)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	अगर (mm->uprobes_state.xol_area) अणु
		ret = -EALREADY;
		जाओ fail;
	पूर्ण

	अगर (!area->vaddr) अणु
		/* Try to map as high as possible, this is only a hपूर्णांक. */
		area->vaddr = get_unmapped_area(शून्य, TASK_SIZE - PAGE_SIZE,
						PAGE_SIZE, 0, 0);
		अगर (IS_ERR_VALUE(area->vaddr)) अणु
			ret = area->vaddr;
			जाओ fail;
		पूर्ण
	पूर्ण

	vma = _install_special_mapping(mm, area->vaddr, PAGE_SIZE,
				VM_EXEC|VM_MAYEXEC|VM_DONTCOPY|VM_IO,
				&area->xol_mapping);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ fail;
	पूर्ण

	ret = 0;
	/* pairs with get_xol_area() */
	smp_store_release(&mm->uprobes_state.xol_area, area); /* ^^^ */
 fail:
	mmap_ग_लिखो_unlock(mm);

	वापस ret;
पूर्ण

अटल काष्ठा xol_area *__create_xol_area(अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	uprobe_opcode_t insn = UPROBE_SWBP_INSN;
	काष्ठा xol_area *area;

	area = kदो_स्मृति(माप(*area), GFP_KERNEL);
	अगर (unlikely(!area))
		जाओ out;

	area->biपंचांगap = kसुस्मृति(BITS_TO_LONGS(UINSNS_PER_PAGE), माप(दीर्घ),
			       GFP_KERNEL);
	अगर (!area->biपंचांगap)
		जाओ मुक्त_area;

	area->xol_mapping.name = "[uprobes]";
	area->xol_mapping.fault = शून्य;
	area->xol_mapping.pages = area->pages;
	area->pages[0] = alloc_page(GFP_HIGHUSER);
	अगर (!area->pages[0])
		जाओ मुक्त_biपंचांगap;
	area->pages[1] = शून्य;

	area->vaddr = vaddr;
	init_रुकोqueue_head(&area->wq);
	/* Reserve the 1st slot क्रम get_trampoline_vaddr() */
	set_bit(0, area->biपंचांगap);
	atomic_set(&area->slot_count, 1);
	arch_uprobe_copy_ixol(area->pages[0], 0, &insn, UPROBE_SWBP_INSN_SIZE);

	अगर (!xol_add_vma(mm, area))
		वापस area;

	__मुक्त_page(area->pages[0]);
 मुक्त_biपंचांगap:
	kमुक्त(area->biपंचांगap);
 मुक्त_area:
	kमुक्त(area);
 out:
	वापस शून्य;
पूर्ण

/*
 * get_xol_area - Allocate process's xol_area अगर necessary.
 * This area will be used क्रम storing inकाष्ठाions क्रम execution out of line.
 *
 * Returns the allocated area or शून्य.
 */
अटल काष्ठा xol_area *get_xol_area(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा xol_area *area;

	अगर (!mm->uprobes_state.xol_area)
		__create_xol_area(0);

	/* Pairs with xol_add_vma() smp_store_release() */
	area = READ_ONCE(mm->uprobes_state.xol_area); /* ^^^ */
	वापस area;
पूर्ण

/*
 * uprobe_clear_state - Free the area allocated क्रम slots.
 */
व्योम uprobe_clear_state(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा xol_area *area = mm->uprobes_state.xol_area;

	mutex_lock(&delayed_uprobe_lock);
	delayed_uprobe_हटाओ(शून्य, mm);
	mutex_unlock(&delayed_uprobe_lock);

	अगर (!area)
		वापस;

	put_page(area->pages[0]);
	kमुक्त(area->biपंचांगap);
	kमुक्त(area);
पूर्ण

व्योम uprobe_start_dup_mmap(व्योम)
अणु
	percpu_करोwn_पढ़ो(&dup_mmap_sem);
पूर्ण

व्योम uprobe_end_dup_mmap(व्योम)
अणु
	percpu_up_पढ़ो(&dup_mmap_sem);
पूर्ण

व्योम uprobe_dup_mmap(काष्ठा mm_काष्ठा *oldmm, काष्ठा mm_काष्ठा *newmm)
अणु
	अगर (test_bit(MMF_HAS_UPROBES, &oldmm->flags)) अणु
		set_bit(MMF_HAS_UPROBES, &newmm->flags);
		/* unconditionally, dup_mmap() skips VM_DONTCOPY vmas */
		set_bit(MMF_RECALC_UPROBES, &newmm->flags);
	पूर्ण
पूर्ण

/*
 *  - search क्रम a मुक्त slot.
 */
अटल अचिन्हित दीर्घ xol_take_insn_slot(काष्ठा xol_area *area)
अणु
	अचिन्हित दीर्घ slot_addr;
	पूर्णांक slot_nr;

	करो अणु
		slot_nr = find_first_zero_bit(area->biपंचांगap, UINSNS_PER_PAGE);
		अगर (slot_nr < UINSNS_PER_PAGE) अणु
			अगर (!test_and_set_bit(slot_nr, area->biपंचांगap))
				अवरोध;

			slot_nr = UINSNS_PER_PAGE;
			जारी;
		पूर्ण
		रुको_event(area->wq, (atomic_पढ़ो(&area->slot_count) < UINSNS_PER_PAGE));
	पूर्ण जबतक (slot_nr >= UINSNS_PER_PAGE);

	slot_addr = area->vaddr + (slot_nr * UPROBE_XOL_SLOT_BYTES);
	atomic_inc(&area->slot_count);

	वापस slot_addr;
पूर्ण

/*
 * xol_get_insn_slot - allocate a slot क्रम xol.
 * Returns the allocated slot address or 0.
 */
अटल अचिन्हित दीर्घ xol_get_insn_slot(काष्ठा uprobe *uprobe)
अणु
	काष्ठा xol_area *area;
	अचिन्हित दीर्घ xol_vaddr;

	area = get_xol_area();
	अगर (!area)
		वापस 0;

	xol_vaddr = xol_take_insn_slot(area);
	अगर (unlikely(!xol_vaddr))
		वापस 0;

	arch_uprobe_copy_ixol(area->pages[0], xol_vaddr,
			      &uprobe->arch.ixol, माप(uprobe->arch.ixol));

	वापस xol_vaddr;
पूर्ण

/*
 * xol_मुक्त_insn_slot - If slot was earlier allocated by
 * @xol_get_insn_slot(), make the slot available क्रम
 * subsequent requests.
 */
अटल व्योम xol_मुक्त_insn_slot(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा xol_area *area;
	अचिन्हित दीर्घ vma_end;
	अचिन्हित दीर्घ slot_addr;

	अगर (!tsk->mm || !tsk->mm->uprobes_state.xol_area || !tsk->utask)
		वापस;

	slot_addr = tsk->utask->xol_vaddr;
	अगर (unlikely(!slot_addr))
		वापस;

	area = tsk->mm->uprobes_state.xol_area;
	vma_end = area->vaddr + PAGE_SIZE;
	अगर (area->vaddr <= slot_addr && slot_addr < vma_end) अणु
		अचिन्हित दीर्घ offset;
		पूर्णांक slot_nr;

		offset = slot_addr - area->vaddr;
		slot_nr = offset / UPROBE_XOL_SLOT_BYTES;
		अगर (slot_nr >= UINSNS_PER_PAGE)
			वापस;

		clear_bit(slot_nr, area->biपंचांगap);
		atomic_dec(&area->slot_count);
		smp_mb__after_atomic(); /* pairs with prepare_to_रुको() */
		अगर (रुकोqueue_active(&area->wq))
			wake_up(&area->wq);

		tsk->utask->xol_vaddr = 0;
	पूर्ण
पूर्ण

व्योम __weak arch_uprobe_copy_ixol(काष्ठा page *page, अचिन्हित दीर्घ vaddr,
				  व्योम *src, अचिन्हित दीर्घ len)
अणु
	/* Initialize the slot */
	copy_to_page(page, vaddr, src, len);

	/*
	 * We probably need flush_icache_user_page() but it needs vma.
	 * This should work on most of architectures by शेष. If
	 * architecture needs to करो something dअगरferent it can define
	 * its own version of the function.
	 */
	flush_dcache_page(page);
पूर्ण

/**
 * uprobe_get_swbp_addr - compute address of swbp given post-swbp regs
 * @regs: Reflects the saved state of the task after it has hit a अवरोधpoपूर्णांक
 * inकाष्ठाion.
 * Return the address of the अवरोधpoपूर्णांक inकाष्ठाion.
 */
अचिन्हित दीर्घ __weak uprobe_get_swbp_addr(काष्ठा pt_regs *regs)
अणु
	वापस inकाष्ठाion_poपूर्णांकer(regs) - UPROBE_SWBP_INSN_SIZE;
पूर्ण

अचिन्हित दीर्घ uprobe_get_trap_addr(काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	अगर (unlikely(utask && utask->active_uprobe))
		वापस utask->vaddr;

	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अटल काष्ठा वापस_instance *मुक्त_ret_instance(काष्ठा वापस_instance *ri)
अणु
	काष्ठा वापस_instance *next = ri->next;
	put_uprobe(ri->uprobe);
	kमुक्त(ri);
	वापस next;
पूर्ण

/*
 * Called with no locks held.
 * Called in context of an निकासing or an exec-ing thपढ़ो.
 */
व्योम uprobe_मुक्त_utask(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा uprobe_task *utask = t->utask;
	काष्ठा वापस_instance *ri;

	अगर (!utask)
		वापस;

	अगर (utask->active_uprobe)
		put_uprobe(utask->active_uprobe);

	ri = utask->वापस_instances;
	जबतक (ri)
		ri = मुक्त_ret_instance(ri);

	xol_मुक्त_insn_slot(t);
	kमुक्त(utask);
	t->utask = शून्य;
पूर्ण

/*
 * Allocate a uprobe_task object क्रम the task अगर necessary.
 * Called when the thपढ़ो hits a अवरोधpoपूर्णांक.
 *
 * Returns:
 * - poपूर्णांकer to new uprobe_task on success
 * - शून्य otherwise
 */
अटल काष्ठा uprobe_task *get_utask(व्योम)
अणु
	अगर (!current->utask)
		current->utask = kzalloc(माप(काष्ठा uprobe_task), GFP_KERNEL);
	वापस current->utask;
पूर्ण

अटल पूर्णांक dup_utask(काष्ठा task_काष्ठा *t, काष्ठा uprobe_task *o_utask)
अणु
	काष्ठा uprobe_task *n_utask;
	काष्ठा वापस_instance **p, *o, *n;

	n_utask = kzalloc(माप(काष्ठा uprobe_task), GFP_KERNEL);
	अगर (!n_utask)
		वापस -ENOMEM;
	t->utask = n_utask;

	p = &n_utask->वापस_instances;
	क्रम (o = o_utask->वापस_instances; o; o = o->next) अणु
		n = kदो_स्मृति(माप(काष्ठा वापस_instance), GFP_KERNEL);
		अगर (!n)
			वापस -ENOMEM;

		*n = *o;
		get_uprobe(n->uprobe);
		n->next = शून्य;

		*p = n;
		p = &n->next;
		n_utask->depth++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uprobe_warn(काष्ठा task_काष्ठा *t, स्थिर अक्षर *msg)
अणु
	pr_warn("uprobe: %s:%d failed to %s\n",
			current->comm, current->pid, msg);
पूर्ण

अटल व्योम dup_xol_work(काष्ठा callback_head *work)
अणु
	अगर (current->flags & PF_EXITING)
		वापस;

	अगर (!__create_xol_area(current->utask->dup_xol_addr) &&
			!fatal_संकेत_pending(current))
		uprobe_warn(current, "dup xol area");
पूर्ण

/*
 * Called in context of a new clone/विभाजन from copy_process.
 */
व्योम uprobe_copy_process(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ flags)
अणु
	काष्ठा uprobe_task *utask = current->utask;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा xol_area *area;

	t->utask = शून्य;

	अगर (!utask || !utask->वापस_instances)
		वापस;

	अगर (mm == t->mm && !(flags & CLONE_VFORK))
		वापस;

	अगर (dup_utask(t, utask))
		वापस uprobe_warn(t, "dup ret instances");

	/* The task can विभाजन() after dup_xol_work() fails */
	area = mm->uprobes_state.xol_area;
	अगर (!area)
		वापस uprobe_warn(t, "dup xol area");

	अगर (mm == t->mm)
		वापस;

	t->utask->dup_xol_addr = area->vaddr;
	init_task_work(&t->utask->dup_xol_work, dup_xol_work);
	task_work_add(t, &t->utask->dup_xol_work, TWA_RESUME);
पूर्ण

/*
 * Current area->vaddr notion assume the trampoline address is always
 * equal area->vaddr.
 *
 * Returns -1 in हाल the xol_area is not allocated.
 */
अटल अचिन्हित दीर्घ get_trampoline_vaddr(व्योम)
अणु
	काष्ठा xol_area *area;
	अचिन्हित दीर्घ trampoline_vaddr = -1;

	/* Pairs with xol_add_vma() smp_store_release() */
	area = READ_ONCE(current->mm->uprobes_state.xol_area); /* ^^^ */
	अगर (area)
		trampoline_vaddr = area->vaddr;

	वापस trampoline_vaddr;
पूर्ण

अटल व्योम cleanup_वापस_instances(काष्ठा uprobe_task *utask, bool chained,
					काष्ठा pt_regs *regs)
अणु
	काष्ठा वापस_instance *ri = utask->वापस_instances;
	क्रमागत rp_check ctx = chained ? RP_CHECK_CHAIN_CALL : RP_CHECK_CALL;

	जबतक (ri && !arch_uretprobe_is_alive(ri, ctx, regs)) अणु
		ri = मुक्त_ret_instance(ri);
		utask->depth--;
	पूर्ण
	utask->वापस_instances = ri;
पूर्ण

अटल व्योम prepare_uretprobe(काष्ठा uprobe *uprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा वापस_instance *ri;
	काष्ठा uprobe_task *utask;
	अचिन्हित दीर्घ orig_ret_vaddr, trampoline_vaddr;
	bool chained;

	अगर (!get_xol_area())
		वापस;

	utask = get_utask();
	अगर (!utask)
		वापस;

	अगर (utask->depth >= MAX_URETPROBE_DEPTH) अणु
		prपूर्णांकk_ratelimited(KERN_INFO "uprobe: omit uretprobe due to"
				" nestedness limit pid/tgid=%d/%d\n",
				current->pid, current->tgid);
		वापस;
	पूर्ण

	ri = kदो_स्मृति(माप(काष्ठा वापस_instance), GFP_KERNEL);
	अगर (!ri)
		वापस;

	trampoline_vaddr = get_trampoline_vaddr();
	orig_ret_vaddr = arch_uretprobe_hijack_वापस_addr(trampoline_vaddr, regs);
	अगर (orig_ret_vaddr == -1)
		जाओ fail;

	/* drop the entries invalidated by दीर्घ_लाँघ() */
	chained = (orig_ret_vaddr == trampoline_vaddr);
	cleanup_वापस_instances(utask, chained, regs);

	/*
	 * We करोn't want to keep trampoline address in stack, rather keep the
	 * original वापस address of first caller thru all the consequent
	 * instances. This also makes अवरोधpoपूर्णांक unwrapping easier.
	 */
	अगर (chained) अणु
		अगर (!utask->वापस_instances) अणु
			/*
			 * This situation is not possible. Likely we have an
			 * attack from user-space.
			 */
			uprobe_warn(current, "handle tail call");
			जाओ fail;
		पूर्ण
		orig_ret_vaddr = utask->वापस_instances->orig_ret_vaddr;
	पूर्ण

	ri->uprobe = get_uprobe(uprobe);
	ri->func = inकाष्ठाion_poपूर्णांकer(regs);
	ri->stack = user_stack_poपूर्णांकer(regs);
	ri->orig_ret_vaddr = orig_ret_vaddr;
	ri->chained = chained;

	utask->depth++;
	ri->next = utask->वापस_instances;
	utask->वापस_instances = ri;

	वापस;
 fail:
	kमुक्त(ri);
पूर्ण

/* Prepare to single-step probed inकाष्ठाion out of line. */
अटल पूर्णांक
pre_ssout(काष्ठा uprobe *uprobe, काष्ठा pt_regs *regs, अचिन्हित दीर्घ bp_vaddr)
अणु
	काष्ठा uprobe_task *utask;
	अचिन्हित दीर्घ xol_vaddr;
	पूर्णांक err;

	utask = get_utask();
	अगर (!utask)
		वापस -ENOMEM;

	xol_vaddr = xol_get_insn_slot(uprobe);
	अगर (!xol_vaddr)
		वापस -ENOMEM;

	utask->xol_vaddr = xol_vaddr;
	utask->vaddr = bp_vaddr;

	err = arch_uprobe_pre_xol(&uprobe->arch, regs);
	अगर (unlikely(err)) अणु
		xol_मुक्त_insn_slot(current);
		वापस err;
	पूर्ण

	utask->active_uprobe = uprobe;
	utask->state = UTASK_SSTEP;
	वापस 0;
पूर्ण

/*
 * If we are singlestepping, then ensure this thपढ़ो is not connected to
 * non-fatal संकेतs until completion of singlestep.  When xol insn itself
 * triggers the संकेत,  restart the original insn even अगर the task is
 * alपढ़ोy SIGKILL'ed (since coredump should report the correct ip).  This
 * is even more important अगर the task has a handler क्रम संक_अंश/etc, The
 * _same_ inकाष्ठाion should be repeated again after वापस from the संकेत
 * handler, and SSTEP can never finish in this हाल.
 */
bool uprobe_deny_संकेत(व्योम)
अणु
	काष्ठा task_काष्ठा *t = current;
	काष्ठा uprobe_task *utask = t->utask;

	अगर (likely(!utask || !utask->active_uprobe))
		वापस false;

	WARN_ON_ONCE(utask->state != UTASK_SSTEP);

	अगर (task_संक_बाकी(t)) अणु
		spin_lock_irq(&t->sighand->siglock);
		clear_tsk_thपढ़ो_flag(t, TIF_SIGPENDING);
		spin_unlock_irq(&t->sighand->siglock);

		अगर (__fatal_संकेत_pending(t) || arch_uprobe_xol_was_trapped(t)) अणु
			utask->state = UTASK_SSTEP_TRAPPED;
			set_tsk_thपढ़ो_flag(t, TIF_UPROBE);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम mmf_recalc_uprobes(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (!valid_vma(vma, false))
			जारी;
		/*
		 * This is not strictly accurate, we can race with
		 * uprobe_unरेजिस्टर() and see the alपढ़ोy हटाओd
		 * uprobe अगर delete_uprobe() was not yet called.
		 * Or this uprobe can be filtered out.
		 */
		अगर (vma_has_uprobes(vma, vma->vm_start, vma->vm_end))
			वापस;
	पूर्ण

	clear_bit(MMF_HAS_UPROBES, &mm->flags);
पूर्ण

अटल पूर्णांक is_trap_at_addr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा page *page;
	uprobe_opcode_t opcode;
	पूर्णांक result;

	अगर (WARN_ON_ONCE(!IS_ALIGNED(vaddr, UPROBE_SWBP_INSN_SIZE)))
		वापस -EINVAL;

	pagefault_disable();
	result = __get_user(opcode, (uprobe_opcode_t __user *)vaddr);
	pagefault_enable();

	अगर (likely(result == 0))
		जाओ out;

	/*
	 * The शून्य 'tsk' here ensures that any faults that occur here
	 * will not be accounted to the task.  'mm' *is* current->mm,
	 * but we treat this as a 'remote' access since it is
	 * essentially a kernel access to the memory.
	 */
	result = get_user_pages_remote(mm, vaddr, 1, FOLL_FORCE, &page,
			शून्य, शून्य);
	अगर (result < 0)
		वापस result;

	copy_from_page(page, vaddr, &opcode, UPROBE_SWBP_INSN_SIZE);
	put_page(page);
 out:
	/* This needs to वापस true क्रम any variant of the trap insn */
	वापस is_trap_insn(&opcode);
पूर्ण

अटल काष्ठा uprobe *find_active_uprobe(अचिन्हित दीर्घ bp_vaddr, पूर्णांक *is_swbp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा uprobe *uprobe = शून्य;
	काष्ठा vm_area_काष्ठा *vma;

	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, bp_vaddr);
	अगर (vma && vma->vm_start <= bp_vaddr) अणु
		अगर (valid_vma(vma, false)) अणु
			काष्ठा inode *inode = file_inode(vma->vm_file);
			loff_t offset = vaddr_to_offset(vma, bp_vaddr);

			uprobe = find_uprobe(inode, offset);
		पूर्ण

		अगर (!uprobe)
			*is_swbp = is_trap_at_addr(mm, bp_vaddr);
	पूर्ण अन्यथा अणु
		*is_swbp = -EFAULT;
	पूर्ण

	अगर (!uprobe && test_and_clear_bit(MMF_RECALC_UPROBES, &mm->flags))
		mmf_recalc_uprobes(mm);
	mmap_पढ़ो_unlock(mm);

	वापस uprobe;
पूर्ण

अटल व्योम handler_chain(काष्ठा uprobe *uprobe, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_consumer *uc;
	पूर्णांक हटाओ = UPROBE_HANDLER_REMOVE;
	bool need_prep = false; /* prepare वापस uprobe, when needed */

	करोwn_पढ़ो(&uprobe->रेजिस्टर_rwsem);
	क्रम (uc = uprobe->consumers; uc; uc = uc->next) अणु
		पूर्णांक rc = 0;

		अगर (uc->handler) अणु
			rc = uc->handler(uc, regs);
			WARN(rc & ~UPROBE_HANDLER_MASK,
				"bad rc=0x%x from %ps()\n", rc, uc->handler);
		पूर्ण

		अगर (uc->ret_handler)
			need_prep = true;

		हटाओ &= rc;
	पूर्ण

	अगर (need_prep && !हटाओ)
		prepare_uretprobe(uprobe, regs); /* put bp at वापस */

	अगर (हटाओ && uprobe->consumers) अणु
		WARN_ON(!uprobe_is_active(uprobe));
		unapply_uprobe(uprobe, current->mm);
	पूर्ण
	up_पढ़ो(&uprobe->रेजिस्टर_rwsem);
पूर्ण

अटल व्योम
handle_uretprobe_chain(काष्ठा वापस_instance *ri, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe *uprobe = ri->uprobe;
	काष्ठा uprobe_consumer *uc;

	करोwn_पढ़ो(&uprobe->रेजिस्टर_rwsem);
	क्रम (uc = uprobe->consumers; uc; uc = uc->next) अणु
		अगर (uc->ret_handler)
			uc->ret_handler(uc, ri->func, regs);
	पूर्ण
	up_पढ़ो(&uprobe->रेजिस्टर_rwsem);
पूर्ण

अटल काष्ठा वापस_instance *find_next_ret_chain(काष्ठा वापस_instance *ri)
अणु
	bool chained;

	करो अणु
		chained = ri->chained;
		ri = ri->next;	/* can't be शून्य अगर chained */
	पूर्ण जबतक (chained);

	वापस ri;
पूर्ण

अटल व्योम handle_trampoline(काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask;
	काष्ठा वापस_instance *ri, *next;
	bool valid;

	utask = current->utask;
	अगर (!utask)
		जाओ sigill;

	ri = utask->वापस_instances;
	अगर (!ri)
		जाओ sigill;

	करो अणु
		/*
		 * We should throw out the frames invalidated by दीर्घ_लाँघ().
		 * If this chain is valid, then the next one should be alive
		 * or शून्य; the latter हाल means that nobody but ri->func
		 * could hit this trampoline on वापस. TODO: sigaltstack().
		 */
		next = find_next_ret_chain(ri);
		valid = !next || arch_uretprobe_is_alive(next, RP_CHECK_RET, regs);

		inकाष्ठाion_poपूर्णांकer_set(regs, ri->orig_ret_vaddr);
		करो अणु
			अगर (valid)
				handle_uretprobe_chain(ri, regs);
			ri = मुक्त_ret_instance(ri);
			utask->depth--;
		पूर्ण जबतक (ri != next);
	पूर्ण जबतक (!valid);

	utask->वापस_instances = ri;
	वापस;

 sigill:
	uprobe_warn(current, "handle uretprobe, sending SIGILL.");
	क्रमce_sig(संक_अवैध);

पूर्ण

bool __weak arch_uprobe_ignore(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs)
अणु
	वापस false;
पूर्ण

bool __weak arch_uretprobe_is_alive(काष्ठा वापस_instance *ret, क्रमागत rp_check ctx,
					काष्ठा pt_regs *regs)
अणु
	वापस true;
पूर्ण

/*
 * Run handler and ask thपढ़ो to singlestep.
 * Ensure all non-fatal संकेतs cannot पूर्णांकerrupt thपढ़ो जबतक it singlesteps.
 */
अटल व्योम handle_swbp(काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe *uprobe;
	अचिन्हित दीर्घ bp_vaddr;
	पूर्णांक is_swbp;

	bp_vaddr = uprobe_get_swbp_addr(regs);
	अगर (bp_vaddr == get_trampoline_vaddr())
		वापस handle_trampoline(regs);

	uprobe = find_active_uprobe(bp_vaddr, &is_swbp);
	अगर (!uprobe) अणु
		अगर (is_swbp > 0) अणु
			/* No matching uprobe; संकेत SIGTRAP. */
			क्रमce_sig(SIGTRAP);
		पूर्ण अन्यथा अणु
			/*
			 * Either we raced with uprobe_unरेजिस्टर() or we can't
			 * access this memory. The latter is only possible अगर
			 * another thपढ़ो plays with our ->mm. In both हालs
			 * we can simply restart. If this vma was unmapped we
			 * can pretend this insn was not executed yet and get
			 * the (correct) संक_अंश after restart.
			 */
			inकाष्ठाion_poपूर्णांकer_set(regs, bp_vaddr);
		पूर्ण
		वापस;
	पूर्ण

	/* change it in advance क्रम ->handler() and restart */
	inकाष्ठाion_poपूर्णांकer_set(regs, bp_vaddr);

	/*
	 * TODO: move copy_insn/etc पूर्णांकo _रेजिस्टर and हटाओ this hack.
	 * After we hit the bp, _unरेजिस्टर + _रेजिस्टर can install the
	 * new and not-yet-analyzed uprobe at the same address, restart.
	 */
	अगर (unlikely(!test_bit(UPROBE_COPY_INSN, &uprobe->flags)))
		जाओ out;

	/*
	 * Pairs with the smp_wmb() in prepare_uprobe().
	 *
	 * Guarantees that अगर we see the UPROBE_COPY_INSN bit set, then
	 * we must also see the stores to &uprobe->arch perक्रमmed by the
	 * prepare_uprobe() call.
	 */
	smp_rmb();

	/* Tracing handlers use ->utask to communicate with fetch methods */
	अगर (!get_utask())
		जाओ out;

	अगर (arch_uprobe_ignore(&uprobe->arch, regs))
		जाओ out;

	handler_chain(uprobe, regs);

	अगर (arch_uprobe_skip_sstep(&uprobe->arch, regs))
		जाओ out;

	अगर (!pre_ssout(uprobe, regs, bp_vaddr))
		वापस;

	/* arch_uprobe_skip_sstep() succeeded, or restart अगर can't singlestep */
out:
	put_uprobe(uprobe);
पूर्ण

/*
 * Perक्रमm required fix-ups and disable singlestep.
 * Allow pending संकेतs to take effect.
 */
अटल व्योम handle_singlestep(काष्ठा uprobe_task *utask, काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe *uprobe;
	पूर्णांक err = 0;

	uprobe = utask->active_uprobe;
	अगर (utask->state == UTASK_SSTEP_ACK)
		err = arch_uprobe_post_xol(&uprobe->arch, regs);
	अन्यथा अगर (utask->state == UTASK_SSTEP_TRAPPED)
		arch_uprobe_पात_xol(&uprobe->arch, regs);
	अन्यथा
		WARN_ON_ONCE(1);

	put_uprobe(uprobe);
	utask->active_uprobe = शून्य;
	utask->state = UTASK_RUNNING;
	xol_मुक्त_insn_slot(current);

	spin_lock_irq(&current->sighand->siglock);
	recalc_संक_बाकी(); /* see uprobe_deny_संकेत() */
	spin_unlock_irq(&current->sighand->siglock);

	अगर (unlikely(err)) अणु
		uprobe_warn(current, "execute the probed insn, sending SIGILL.");
		क्रमce_sig(संक_अवैध);
	पूर्ण
पूर्ण

/*
 * On अवरोधpoपूर्णांक hit, अवरोधpoपूर्णांक notअगरier sets the TIF_UPROBE flag and
 * allows the thपढ़ो to वापस from पूर्णांकerrupt. After that handle_swbp()
 * sets utask->active_uprobe.
 *
 * On singlestep exception, singlestep notअगरier sets the TIF_UPROBE flag
 * and allows the thपढ़ो to वापस from पूर्णांकerrupt.
 *
 * While वापसing to userspace, thपढ़ो notices the TIF_UPROBE flag and calls
 * uprobe_notअगरy_resume().
 */
व्योम uprobe_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask;

	clear_thपढ़ो_flag(TIF_UPROBE);

	utask = current->utask;
	अगर (utask && utask->active_uprobe)
		handle_singlestep(utask, regs);
	अन्यथा
		handle_swbp(regs);
पूर्ण

/*
 * uprobe_pre_sstep_notअगरier माला_लो called from पूर्णांकerrupt context as part of
 * notअगरier mechanism. Set TIF_UPROBE flag and indicate अवरोधpoपूर्णांक hit.
 */
पूर्णांक uprobe_pre_sstep_notअगरier(काष्ठा pt_regs *regs)
अणु
	अगर (!current->mm)
		वापस 0;

	अगर (!test_bit(MMF_HAS_UPROBES, &current->mm->flags) &&
	    (!current->utask || !current->utask->वापस_instances))
		वापस 0;

	set_thपढ़ो_flag(TIF_UPROBE);
	वापस 1;
पूर्ण

/*
 * uprobe_post_sstep_notअगरier माला_लो called in पूर्णांकerrupt context as part of notअगरier
 * mechanism. Set TIF_UPROBE flag and indicate completion of singlestep.
 */
पूर्णांक uprobe_post_sstep_notअगरier(काष्ठा pt_regs *regs)
अणु
	काष्ठा uprobe_task *utask = current->utask;

	अगर (!current->mm || !utask || !utask->active_uprobe)
		/* task is currently not uprobed */
		वापस 0;

	utask->state = UTASK_SSTEP_ACK;
	set_thपढ़ो_flag(TIF_UPROBE);
	वापस 1;
पूर्ण

अटल काष्ठा notअगरier_block uprobe_exception_nb = अणु
	.notअगरier_call		= arch_uprobe_exception_notअगरy,
	.priority		= पूर्णांक_उच्च-1,	/* notअगरied after kprobes, kgdb */
पूर्ण;

व्योम __init uprobes_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UPROBES_HASH_SZ; i++)
		mutex_init(&uprobes_mmap_mutex[i]);

	BUG_ON(रेजिस्टर_die_notअगरier(&uprobe_exception_nb));
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/mmap.c
 *
 * Written by obz.
 *
 * Address space accounting code	<alan@lxorguk.ukuu.org.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/shm.h>
#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/personality.h>
#समावेश <linux/security.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/profile.h>
#समावेश <linux/export.h>
#समावेश <linux/mount.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/rmap.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/mmdebug.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/audit.h>
#समावेश <linux/khugepaged.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/rbtree_augmented.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/memory.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/oom.h>
#समावेश <linux/sched/mm.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mmap.h>

#समावेश "internal.h"

#अगर_अघोषित arch_mmap_check
#घोषणा arch_mmap_check(addr, len, flags)	(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_BITS
स्थिर पूर्णांक mmap_rnd_bits_min = CONFIG_ARCH_MMAP_RND_BITS_MIN;
स्थिर पूर्णांक mmap_rnd_bits_max = CONFIG_ARCH_MMAP_RND_BITS_MAX;
पूर्णांक mmap_rnd_bits __पढ़ो_mostly = CONFIG_ARCH_MMAP_RND_BITS;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_COMPAT_BITS
स्थिर पूर्णांक mmap_rnd_compat_bits_min = CONFIG_ARCH_MMAP_RND_COMPAT_BITS_MIN;
स्थिर पूर्णांक mmap_rnd_compat_bits_max = CONFIG_ARCH_MMAP_RND_COMPAT_BITS_MAX;
पूर्णांक mmap_rnd_compat_bits __पढ़ो_mostly = CONFIG_ARCH_MMAP_RND_COMPAT_BITS;
#पूर्ण_अगर

अटल bool ignore_rlimit_data;
core_param(ignore_rlimit_data, ignore_rlimit_data, bool, 0644);

अटल व्योम unmap_region(काष्ठा mm_काष्ठा *mm,
		काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा *prev,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

/* description of effects of mapping type and prot in current implementation.
 * this is due to the limited x86 page protection hardware.  The expected
 * behavior is in parens:
 *
 * map_type	prot
 *		PROT_NONE	PROT_READ	PROT_WRITE	PROT_EXEC
 * MAP_SHARED	r: (no) no	r: (yes) yes	r: (no) yes	r: (no) yes
 *		w: (no) no	w: (no) no	w: (yes) yes	w: (no) no
 *		x: (no) no	x: (no) yes	x: (no) yes	x: (yes) yes
 *
 * MAP_PRIVATE	r: (no) no	r: (yes) yes	r: (no) yes	r: (no) yes
 *		w: (no) no	w: (no) no	w: (copy) copy	w: (no) no
 *		x: (no) no	x: (no) yes	x: (no) yes	x: (yes) yes
 *
 * On arm64, PROT_EXEC has the following behaviour क्रम both MAP_SHARED and
 * MAP_PRIVATE (with Enhanced PAN supported):
 *								r: (no) no
 *								w: (no) no
 *								x: (yes) yes
 */
pgprot_t protection_map[16] __ro_after_init = अणु
	__P000, __P001, __P010, __P011, __P100, __P101, __P110, __P111,
	__S000, __S001, __S010, __S011, __S100, __S101, __S110, __S111
पूर्ण;

#अगर_अघोषित CONFIG_ARCH_HAS_FILTER_PGPROT
अटल अंतरभूत pgprot_t arch_filter_pgprot(pgprot_t prot)
अणु
	वापस prot;
पूर्ण
#पूर्ण_अगर

pgprot_t vm_get_page_prot(अचिन्हित दीर्घ vm_flags)
अणु
	pgprot_t ret = __pgprot(pgprot_val(protection_map[vm_flags &
				(VM_READ|VM_WRITE|VM_EXEC|VM_SHARED)]) |
			pgprot_val(arch_vm_get_page_prot(vm_flags)));

	वापस arch_filter_pgprot(ret);
पूर्ण
EXPORT_SYMBOL(vm_get_page_prot);

अटल pgprot_t vm_pgprot_modअगरy(pgprot_t oldprot, अचिन्हित दीर्घ vm_flags)
अणु
	वापस pgprot_modअगरy(oldprot, vm_get_page_prot(vm_flags));
पूर्ण

/* Update vma->vm_page_prot to reflect vma->vm_flags. */
व्योम vma_set_page_prot(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ vm_flags = vma->vm_flags;
	pgprot_t vm_page_prot;

	vm_page_prot = vm_pgprot_modअगरy(vma->vm_page_prot, vm_flags);
	अगर (vma_wants_ग_लिखोnotअगरy(vma, vm_page_prot)) अणु
		vm_flags &= ~VM_SHARED;
		vm_page_prot = vm_pgprot_modअगरy(vm_page_prot, vm_flags);
	पूर्ण
	/* हटाओ_protection_ptes पढ़ोs vma->vm_page_prot without mmap_lock */
	WRITE_ONCE(vma->vm_page_prot, vm_page_prot);
पूर्ण

/*
 * Requires inode->i_mapping->i_mmap_rwsem
 */
अटल व्योम __हटाओ_shared_vm_काष्ठा(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा file *file, काष्ठा address_space *mapping)
अणु
	अगर (vma->vm_flags & VM_DENYWRITE)
		allow_ग_लिखो_access(file);
	अगर (vma->vm_flags & VM_SHARED)
		mapping_unmap_writable(mapping);

	flush_dcache_mmap_lock(mapping);
	vma_पूर्णांकerval_tree_हटाओ(vma, &mapping->i_mmap);
	flush_dcache_mmap_unlock(mapping);
पूर्ण

/*
 * Unlink a file-based vm काष्ठाure from its पूर्णांकerval tree, to hide
 * vma from rmap and vmtruncate beक्रमe मुक्तing its page tables.
 */
व्योम unlink_file_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;

	अगर (file) अणु
		काष्ठा address_space *mapping = file->f_mapping;
		i_mmap_lock_ग_लिखो(mapping);
		__हटाओ_shared_vm_काष्ठा(vma, file, mapping);
		i_mmap_unlock_ग_लिखो(mapping);
	पूर्ण
पूर्ण

/*
 * Close a vm काष्ठाure and मुक्त it, वापसing the next.
 */
अटल काष्ठा vm_area_काष्ठा *हटाओ_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vm_area_काष्ठा *next = vma->vm_next;

	might_sleep();
	अगर (vma->vm_ops && vma->vm_ops->बंद)
		vma->vm_ops->बंद(vma);
	अगर (vma->vm_file)
		fput(vma->vm_file);
	mpol_put(vma_policy(vma));
	vm_area_मुक्त(vma);
	वापस next;
पूर्ण

अटल पूर्णांक करो_brk_flags(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ request, अचिन्हित दीर्घ flags,
		काष्ठा list_head *uf);
SYSCALL_DEFINE1(brk, अचिन्हित दीर्घ, brk)
अणु
	अचिन्हित दीर्घ newbrk, oldbrk, origbrk;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *next;
	अचिन्हित दीर्घ min_brk;
	bool populate;
	bool करोwngraded = false;
	LIST_HEAD(uf);

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	origbrk = mm->brk;

#अगर_घोषित CONFIG_COMPAT_BRK
	/*
	 * CONFIG_COMPAT_BRK can still be overridden by setting
	 * अक्रमomize_va_space to 2, which will still cause mm->start_brk
	 * to be arbitrarily shअगरted
	 */
	अगर (current->brk_अक्रमomized)
		min_brk = mm->start_brk;
	अन्यथा
		min_brk = mm->end_data;
#अन्यथा
	min_brk = mm->start_brk;
#पूर्ण_अगर
	अगर (brk < min_brk)
		जाओ out;

	/*
	 * Check against rlimit here. If this check is करोne later after the test
	 * of oldbrk with newbrk then it can escape the test and let the data
	 * segment grow beyond its set limit the in हाल where the limit is
	 * not page aligned -Ram Gupta
	 */
	अगर (check_data_rlimit(rlimit(RLIMIT_DATA), brk, mm->start_brk,
			      mm->end_data, mm->start_data))
		जाओ out;

	newbrk = PAGE_ALIGN(brk);
	oldbrk = PAGE_ALIGN(mm->brk);
	अगर (oldbrk == newbrk) अणु
		mm->brk = brk;
		जाओ success;
	पूर्ण

	/*
	 * Always allow shrinking brk.
	 * __करो_munmap() may करोwngrade mmap_lock to पढ़ो.
	 */
	अगर (brk <= mm->brk) अणु
		पूर्णांक ret;

		/*
		 * mm->brk must to be रक्षित by ग_लिखो mmap_lock so update it
		 * beक्रमe करोwngrading mmap_lock. When __करो_munmap() fails,
		 * mm->brk will be restored from origbrk.
		 */
		mm->brk = brk;
		ret = __करो_munmap(mm, newbrk, oldbrk-newbrk, &uf, true);
		अगर (ret < 0) अणु
			mm->brk = origbrk;
			जाओ out;
		पूर्ण अन्यथा अगर (ret == 1) अणु
			करोwngraded = true;
		पूर्ण
		जाओ success;
	पूर्ण

	/* Check against existing mmap mappings. */
	next = find_vma(mm, oldbrk);
	अगर (next && newbrk + PAGE_SIZE > vm_start_gap(next))
		जाओ out;

	/* Ok, looks good - let it rip. */
	अगर (करो_brk_flags(oldbrk, newbrk-oldbrk, 0, &uf) < 0)
		जाओ out;
	mm->brk = brk;

success:
	populate = newbrk > oldbrk && (mm->def_flags & VM_LOCKED) != 0;
	अगर (करोwngraded)
		mmap_पढ़ो_unlock(mm);
	अन्यथा
		mmap_ग_लिखो_unlock(mm);
	userfaultfd_unmap_complete(mm, &uf);
	अगर (populate)
		mm_populate(oldbrk, newbrk - oldbrk);
	वापस brk;

out:
	mmap_ग_लिखो_unlock(mm);
	वापस origbrk;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vma_compute_gap(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ gap, prev_end;

	/*
	 * Note: in the rare हाल of a VM_GROWSDOWN above a VM_GROWSUP, we
	 * allow two stack_guard_gaps between them here, and when choosing
	 * an unmapped area; whereas when expanding we only require one.
	 * That's a little inconsistent, but keeps the code here simpler.
	 */
	gap = vm_start_gap(vma);
	अगर (vma->vm_prev) अणु
		prev_end = vm_end_gap(vma->vm_prev);
		अगर (gap > prev_end)
			gap -= prev_end;
		अन्यथा
			gap = 0;
	पूर्ण
	वापस gap;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VM_RB
अटल अचिन्हित दीर्घ vma_compute_subtree_gap(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ max = vma_compute_gap(vma), subtree_gap;
	अगर (vma->vm_rb.rb_left) अणु
		subtree_gap = rb_entry(vma->vm_rb.rb_left,
				काष्ठा vm_area_काष्ठा, vm_rb)->rb_subtree_gap;
		अगर (subtree_gap > max)
			max = subtree_gap;
	पूर्ण
	अगर (vma->vm_rb.rb_right) अणु
		subtree_gap = rb_entry(vma->vm_rb.rb_right,
				काष्ठा vm_area_काष्ठा, vm_rb)->rb_subtree_gap;
		अगर (subtree_gap > max)
			max = subtree_gap;
	पूर्ण
	वापस max;
पूर्ण

अटल पूर्णांक browse_rb(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा rb_root *root = &mm->mm_rb;
	पूर्णांक i = 0, j, bug = 0;
	काष्ठा rb_node *nd, *pn = शून्य;
	अचिन्हित दीर्घ prev = 0, pend = 0;

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा vm_area_काष्ठा *vma;
		vma = rb_entry(nd, काष्ठा vm_area_काष्ठा, vm_rb);
		अगर (vma->vm_start < prev) अणु
			pr_emerg("vm_start %lx < prev %lx\n",
				  vma->vm_start, prev);
			bug = 1;
		पूर्ण
		अगर (vma->vm_start < pend) अणु
			pr_emerg("vm_start %lx < pend %lx\n",
				  vma->vm_start, pend);
			bug = 1;
		पूर्ण
		अगर (vma->vm_start > vma->vm_end) अणु
			pr_emerg("vm_start %lx > vm_end %lx\n",
				  vma->vm_start, vma->vm_end);
			bug = 1;
		पूर्ण
		spin_lock(&mm->page_table_lock);
		अगर (vma->rb_subtree_gap != vma_compute_subtree_gap(vma)) अणु
			pr_emerg("free gap %lx, correct %lx\n",
			       vma->rb_subtree_gap,
			       vma_compute_subtree_gap(vma));
			bug = 1;
		पूर्ण
		spin_unlock(&mm->page_table_lock);
		i++;
		pn = nd;
		prev = vma->vm_start;
		pend = vma->vm_end;
	पूर्ण
	j = 0;
	क्रम (nd = pn; nd; nd = rb_prev(nd))
		j++;
	अगर (i != j) अणु
		pr_emerg("backwards %d, forwards %d\n", j, i);
		bug = 1;
	पूर्ण
	वापस bug ? -1 : i;
पूर्ण

अटल व्योम validate_mm_rb(काष्ठा rb_root *root, काष्ठा vm_area_काष्ठा *ignore)
अणु
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first(root); nd; nd = rb_next(nd)) अणु
		काष्ठा vm_area_काष्ठा *vma;
		vma = rb_entry(nd, काष्ठा vm_area_काष्ठा, vm_rb);
		VM_BUG_ON_VMA(vma != ignore &&
			vma->rb_subtree_gap != vma_compute_subtree_gap(vma),
			vma);
	पूर्ण
पूर्ण

अटल व्योम validate_mm(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक bug = 0;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ highest_address = 0;
	काष्ठा vm_area_काष्ठा *vma = mm->mmap;

	जबतक (vma) अणु
		काष्ठा anon_vma *anon_vma = vma->anon_vma;
		काष्ठा anon_vma_chain *avc;

		अगर (anon_vma) अणु
			anon_vma_lock_पढ़ो(anon_vma);
			list_क्रम_each_entry(avc, &vma->anon_vma_chain, same_vma)
				anon_vma_पूर्णांकerval_tree_verअगरy(avc);
			anon_vma_unlock_पढ़ो(anon_vma);
		पूर्ण

		highest_address = vm_end_gap(vma);
		vma = vma->vm_next;
		i++;
	पूर्ण
	अगर (i != mm->map_count) अणु
		pr_emerg("map_count %d vm_next %d\n", mm->map_count, i);
		bug = 1;
	पूर्ण
	अगर (highest_address != mm->highest_vm_end) अणु
		pr_emerg("mm->highest_vm_end %lx, found %lx\n",
			  mm->highest_vm_end, highest_address);
		bug = 1;
	पूर्ण
	i = browse_rb(mm);
	अगर (i != mm->map_count) अणु
		अगर (i != -1)
			pr_emerg("map_count %d rb %d\n", mm->map_count, i);
		bug = 1;
	पूर्ण
	VM_BUG_ON_MM(bug, mm);
पूर्ण
#अन्यथा
#घोषणा validate_mm_rb(root, ignore) करो अणु पूर्ण जबतक (0)
#घोषणा validate_mm(mm) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

RB_DECLARE_CALLBACKS_MAX(अटल, vma_gap_callbacks,
			 काष्ठा vm_area_काष्ठा, vm_rb,
			 अचिन्हित दीर्घ, rb_subtree_gap, vma_compute_gap)

/*
 * Update augmented rbtree rb_subtree_gap values after vma->vm_start or
 * vma->vm_prev->vm_end values changed, without modअगरying the vma's position
 * in the rbtree.
 */
अटल व्योम vma_gap_update(काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * As it turns out, RB_DECLARE_CALLBACKS_MAX() alपढ़ोy created
	 * a callback function that करोes exactly what we want.
	 */
	vma_gap_callbacks_propagate(&vma->vm_rb, शून्य);
पूर्ण

अटल अंतरभूत व्योम vma_rb_insert(काष्ठा vm_area_काष्ठा *vma,
				 काष्ठा rb_root *root)
अणु
	/* All rb_subtree_gap values must be consistent prior to insertion */
	validate_mm_rb(root, शून्य);

	rb_insert_augmented(&vma->vm_rb, root, &vma_gap_callbacks);
पूर्ण

अटल व्योम __vma_rb_erase(काष्ठा vm_area_काष्ठा *vma, काष्ठा rb_root *root)
अणु
	/*
	 * Note rb_erase_augmented is a fairly large अंतरभूत function,
	 * so make sure we instantiate it only once with our desired
	 * augmented rbtree callbacks.
	 */
	rb_erase_augmented(&vma->vm_rb, root, &vma_gap_callbacks);
पूर्ण

अटल __always_अंतरभूत व्योम vma_rb_erase_ignore(काष्ठा vm_area_काष्ठा *vma,
						काष्ठा rb_root *root,
						काष्ठा vm_area_काष्ठा *ignore)
अणु
	/*
	 * All rb_subtree_gap values must be consistent prior to erase,
	 * with the possible exception of
	 *
	 * a. the "next" vma being erased अगर next->vm_start was reduced in
	 *    __vma_adjust() -> __vma_unlink()
	 * b. the vma being erased in detach_vmas_to_be_unmapped() ->
	 *    vma_rb_erase()
	 */
	validate_mm_rb(root, ignore);

	__vma_rb_erase(vma, root);
पूर्ण

अटल __always_अंतरभूत व्योम vma_rb_erase(काष्ठा vm_area_काष्ठा *vma,
					 काष्ठा rb_root *root)
अणु
	vma_rb_erase_ignore(vma, root, vma);
पूर्ण

/*
 * vma has some anon_vma asचिन्हित, and is alपढ़ोy inserted on that
 * anon_vma's पूर्णांकerval trees.
 *
 * Beक्रमe updating the vma's vm_start / vm_end / vm_pgoff fields, the
 * vma must be हटाओd from the anon_vma's पूर्णांकerval trees using
 * anon_vma_पूर्णांकerval_tree_pre_update_vma().
 *
 * After the update, the vma will be reinserted using
 * anon_vma_पूर्णांकerval_tree_post_update_vma().
 *
 * The entire update must be रक्षित by exclusive mmap_lock and by
 * the root anon_vma's mutex.
 */
अटल अंतरभूत व्योम
anon_vma_पूर्णांकerval_tree_pre_update_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा anon_vma_chain *avc;

	list_क्रम_each_entry(avc, &vma->anon_vma_chain, same_vma)
		anon_vma_पूर्णांकerval_tree_हटाओ(avc, &avc->anon_vma->rb_root);
पूर्ण

अटल अंतरभूत व्योम
anon_vma_पूर्णांकerval_tree_post_update_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा anon_vma_chain *avc;

	list_क्रम_each_entry(avc, &vma->anon_vma_chain, same_vma)
		anon_vma_पूर्णांकerval_tree_insert(avc, &avc->anon_vma->rb_root);
पूर्ण

अटल पूर्णांक find_vma_links(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, काष्ठा vm_area_काष्ठा **pprev,
		काष्ठा rb_node ***rb_link, काष्ठा rb_node **rb_parent)
अणु
	काष्ठा rb_node **__rb_link, *__rb_parent, *rb_prev;

	__rb_link = &mm->mm_rb.rb_node;
	rb_prev = __rb_parent = शून्य;

	जबतक (*__rb_link) अणु
		काष्ठा vm_area_काष्ठा *vma_पंचांगp;

		__rb_parent = *__rb_link;
		vma_पंचांगp = rb_entry(__rb_parent, काष्ठा vm_area_काष्ठा, vm_rb);

		अगर (vma_पंचांगp->vm_end > addr) अणु
			/* Fail अगर an existing vma overlaps the area */
			अगर (vma_पंचांगp->vm_start < end)
				वापस -ENOMEM;
			__rb_link = &__rb_parent->rb_left;
		पूर्ण अन्यथा अणु
			rb_prev = __rb_parent;
			__rb_link = &__rb_parent->rb_right;
		पूर्ण
	पूर्ण

	*pprev = शून्य;
	अगर (rb_prev)
		*pprev = rb_entry(rb_prev, काष्ठा vm_area_काष्ठा, vm_rb);
	*rb_link = __rb_link;
	*rb_parent = __rb_parent;
	वापस 0;
पूर्ण

/*
 * vma_next() - Get the next VMA.
 * @mm: The mm_काष्ठा.
 * @vma: The current vma.
 *
 * If @vma is शून्य, वापस the first vma in the mm.
 *
 * Returns: The next VMA after @vma.
 */
अटल अंतरभूत काष्ठा vm_area_काष्ठा *vma_next(काष्ठा mm_काष्ठा *mm,
					 काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!vma)
		वापस mm->mmap;

	वापस vma->vm_next;
पूर्ण

/*
 * munmap_vma_range() - munmap VMAs that overlap a range.
 * @mm: The mm काष्ठा
 * @start: The start of the range.
 * @len: The length of the range.
 * @pprev: poपूर्णांकer to the poपूर्णांकer that will be set to previous vm_area_काष्ठा
 * @rb_link: the rb_node
 * @rb_parent: the parent rb_node
 *
 * Find all the vm_area_काष्ठा that overlap from @start to
 * @end and munmap them.  Set @pprev to the previous vm_area_काष्ठा.
 *
 * Returns: -ENOMEM on munmap failure or 0 on success.
 */
अटल अंतरभूत पूर्णांक
munmap_vma_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
		 काष्ठा vm_area_काष्ठा **pprev, काष्ठा rb_node ***link,
		 काष्ठा rb_node **parent, काष्ठा list_head *uf)
अणु

	जबतक (find_vma_links(mm, start, start + len, pprev, link, parent))
		अगर (करो_munmap(mm, start, len, uf))
			वापस -ENOMEM;

	वापस 0;
पूर्ण
अटल अचिन्हित दीर्घ count_vma_pages_range(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ nr_pages = 0;
	काष्ठा vm_area_काष्ठा *vma;

	/* Find first overlapping mapping */
	vma = find_vma_पूर्णांकersection(mm, addr, end);
	अगर (!vma)
		वापस 0;

	nr_pages = (min(end, vma->vm_end) -
		max(addr, vma->vm_start)) >> PAGE_SHIFT;

	/* Iterate over the rest of the overlaps */
	क्रम (vma = vma->vm_next; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ overlap_len;

		अगर (vma->vm_start > end)
			अवरोध;

		overlap_len = min(end, vma->vm_end) - vma->vm_start;
		nr_pages += overlap_len >> PAGE_SHIFT;
	पूर्ण

	वापस nr_pages;
पूर्ण

व्योम __vma_link_rb(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा rb_node **rb_link, काष्ठा rb_node *rb_parent)
अणु
	/* Update tracking inक्रमmation क्रम the gap following the new vma. */
	अगर (vma->vm_next)
		vma_gap_update(vma->vm_next);
	अन्यथा
		mm->highest_vm_end = vm_end_gap(vma);

	/*
	 * vma->vm_prev wasn't known when we followed the rbtree to find the
	 * correct insertion poपूर्णांक क्रम that vma. As a result, we could not
	 * update the vma vm_rb parents rb_subtree_gap values on the way करोwn.
	 * So, we first insert the vma with a zero rb_subtree_gap value
	 * (to be consistent with what we did on the way करोwn), and then
	 * immediately update the gap to the correct value. Finally we
	 * rebalance the rbtree after all augmented values have been set.
	 */
	rb_link_node(&vma->vm_rb, rb_parent, rb_link);
	vma->rb_subtree_gap = 0;
	vma_gap_update(vma);
	vma_rb_insert(vma, &mm->mm_rb);
पूर्ण

अटल व्योम __vma_link_file(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file;

	file = vma->vm_file;
	अगर (file) अणु
		काष्ठा address_space *mapping = file->f_mapping;

		अगर (vma->vm_flags & VM_DENYWRITE)
			put_ग_लिखो_access(file_inode(file));
		अगर (vma->vm_flags & VM_SHARED)
			mapping_allow_writable(mapping);

		flush_dcache_mmap_lock(mapping);
		vma_पूर्णांकerval_tree_insert(vma, &mapping->i_mmap);
		flush_dcache_mmap_unlock(mapping);
	पूर्ण
पूर्ण

अटल व्योम
__vma_link(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
	काष्ठा vm_area_काष्ठा *prev, काष्ठा rb_node **rb_link,
	काष्ठा rb_node *rb_parent)
अणु
	__vma_link_list(mm, vma, prev);
	__vma_link_rb(mm, vma, rb_link, rb_parent);
पूर्ण

अटल व्योम vma_link(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
			काष्ठा vm_area_काष्ठा *prev, काष्ठा rb_node **rb_link,
			काष्ठा rb_node *rb_parent)
अणु
	काष्ठा address_space *mapping = शून्य;

	अगर (vma->vm_file) अणु
		mapping = vma->vm_file->f_mapping;
		i_mmap_lock_ग_लिखो(mapping);
	पूर्ण

	__vma_link(mm, vma, prev, rb_link, rb_parent);
	__vma_link_file(vma);

	अगर (mapping)
		i_mmap_unlock_ग_लिखो(mapping);

	mm->map_count++;
	validate_mm(mm);
पूर्ण

/*
 * Helper क्रम vma_adjust() in the split_vma insert हाल: insert a vma पूर्णांकo the
 * mm's list and rbtree.  It has alपढ़ोy been inserted पूर्णांकo the पूर्णांकerval tree.
 */
अटल व्योम __insert_vm_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vm_area_काष्ठा *prev;
	काष्ठा rb_node **rb_link, *rb_parent;

	अगर (find_vma_links(mm, vma->vm_start, vma->vm_end,
			   &prev, &rb_link, &rb_parent))
		BUG();
	__vma_link(mm, vma, prev, rb_link, rb_parent);
	mm->map_count++;
पूर्ण

अटल __always_अंतरभूत व्योम __vma_unlink(काष्ठा mm_काष्ठा *mm,
						काष्ठा vm_area_काष्ठा *vma,
						काष्ठा vm_area_काष्ठा *ignore)
अणु
	vma_rb_erase_ignore(vma, &mm->mm_rb, ignore);
	__vma_unlink_list(mm, vma);
	/* Kill the cache */
	vmacache_invalidate(mm);
पूर्ण

/*
 * We cannot adjust vm_start, vm_end, vm_pgoff fields of a vma that
 * is alपढ़ोy present in an i_mmap tree without adjusting the tree.
 * The following helper function should be used when such adjusपंचांगents
 * are necessary.  The "insert" vma (अगर any) is to be inserted
 * beक्रमe we drop the necessary locks.
 */
पूर्णांक __vma_adjust(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end, pgoff_t pgoff, काष्ठा vm_area_काष्ठा *insert,
	काष्ठा vm_area_काष्ठा *expand)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *next = vma->vm_next, *orig_vma = vma;
	काष्ठा address_space *mapping = शून्य;
	काष्ठा rb_root_cached *root = शून्य;
	काष्ठा anon_vma *anon_vma = शून्य;
	काष्ठा file *file = vma->vm_file;
	bool start_changed = false, end_changed = false;
	दीर्घ adjust_next = 0;
	पूर्णांक हटाओ_next = 0;

	अगर (next && !insert) अणु
		काष्ठा vm_area_काष्ठा *exporter = शून्य, *importer = शून्य;

		अगर (end >= next->vm_end) अणु
			/*
			 * vma expands, overlapping all the next, and
			 * perhaps the one after too (mprotect हाल 6).
			 * The only other हालs that माला_लो here are
			 * हाल 1, हाल 7 and हाल 8.
			 */
			अगर (next == expand) अणु
				/*
				 * The only हाल where we करोn't expand "vma"
				 * and we expand "next" instead is हाल 8.
				 */
				VM_WARN_ON(end != next->vm_end);
				/*
				 * हटाओ_next == 3 means we're
				 * removing "vma" and that to करो so we
				 * swapped "vma" and "next".
				 */
				हटाओ_next = 3;
				VM_WARN_ON(file != next->vm_file);
				swap(vma, next);
			पूर्ण अन्यथा अणु
				VM_WARN_ON(expand != vma);
				/*
				 * हाल 1, 6, 7, हटाओ_next == 2 is हाल 6,
				 * हटाओ_next == 1 is हाल 1 or 7.
				 */
				हटाओ_next = 1 + (end > next->vm_end);
				VM_WARN_ON(हटाओ_next == 2 &&
					   end != next->vm_next->vm_end);
				/* trim end to next, क्रम हाल 6 first pass */
				end = next->vm_end;
			पूर्ण

			exporter = next;
			importer = vma;

			/*
			 * If next करोesn't have anon_vma, import from vma after
			 * next, अगर the vma overlaps with it.
			 */
			अगर (हटाओ_next == 2 && !next->anon_vma)
				exporter = next->vm_next;

		पूर्ण अन्यथा अगर (end > next->vm_start) अणु
			/*
			 * vma expands, overlapping part of the next:
			 * mprotect हाल 5 shअगरting the boundary up.
			 */
			adjust_next = (end - next->vm_start);
			exporter = next;
			importer = vma;
			VM_WARN_ON(expand != importer);
		पूर्ण अन्यथा अगर (end < vma->vm_end) अणु
			/*
			 * vma shrinks, and !insert tells it's not
			 * split_vma inserting another: so it must be
			 * mprotect हाल 4 shअगरting the boundary करोwn.
			 */
			adjust_next = -(vma->vm_end - end);
			exporter = vma;
			importer = next;
			VM_WARN_ON(expand != importer);
		पूर्ण

		/*
		 * Easily overlooked: when mprotect shअगरts the boundary,
		 * make sure the expanding vma has anon_vma set अगर the
		 * shrinking vma had, to cover any anon pages imported.
		 */
		अगर (exporter && exporter->anon_vma && !importer->anon_vma) अणु
			पूर्णांक error;

			importer->anon_vma = exporter->anon_vma;
			error = anon_vma_clone(importer, exporter);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण
again:
	vma_adjust_trans_huge(orig_vma, start, end, adjust_next);

	अगर (file) अणु
		mapping = file->f_mapping;
		root = &mapping->i_mmap;
		uprobe_munmap(vma, vma->vm_start, vma->vm_end);

		अगर (adjust_next)
			uprobe_munmap(next, next->vm_start, next->vm_end);

		i_mmap_lock_ग_लिखो(mapping);
		अगर (insert) अणु
			/*
			 * Put पूर्णांकo पूर्णांकerval tree now, so instantiated pages
			 * are visible to arm/parisc __flush_dcache_page
			 * throughout; but we cannot insert पूर्णांकo address
			 * space until vma start or end is updated.
			 */
			__vma_link_file(insert);
		पूर्ण
	पूर्ण

	anon_vma = vma->anon_vma;
	अगर (!anon_vma && adjust_next)
		anon_vma = next->anon_vma;
	अगर (anon_vma) अणु
		VM_WARN_ON(adjust_next && next->anon_vma &&
			   anon_vma != next->anon_vma);
		anon_vma_lock_ग_लिखो(anon_vma);
		anon_vma_पूर्णांकerval_tree_pre_update_vma(vma);
		अगर (adjust_next)
			anon_vma_पूर्णांकerval_tree_pre_update_vma(next);
	पूर्ण

	अगर (file) अणु
		flush_dcache_mmap_lock(mapping);
		vma_पूर्णांकerval_tree_हटाओ(vma, root);
		अगर (adjust_next)
			vma_पूर्णांकerval_tree_हटाओ(next, root);
	पूर्ण

	अगर (start != vma->vm_start) अणु
		vma->vm_start = start;
		start_changed = true;
	पूर्ण
	अगर (end != vma->vm_end) अणु
		vma->vm_end = end;
		end_changed = true;
	पूर्ण
	vma->vm_pgoff = pgoff;
	अगर (adjust_next) अणु
		next->vm_start += adjust_next;
		next->vm_pgoff += adjust_next >> PAGE_SHIFT;
	पूर्ण

	अगर (file) अणु
		अगर (adjust_next)
			vma_पूर्णांकerval_tree_insert(next, root);
		vma_पूर्णांकerval_tree_insert(vma, root);
		flush_dcache_mmap_unlock(mapping);
	पूर्ण

	अगर (हटाओ_next) अणु
		/*
		 * vma_merge has merged next पूर्णांकo vma, and needs
		 * us to हटाओ next beक्रमe dropping the locks.
		 */
		अगर (हटाओ_next != 3)
			__vma_unlink(mm, next, next);
		अन्यथा
			/*
			 * vma is not beक्रमe next अगर they've been
			 * swapped.
			 *
			 * pre-swap() next->vm_start was reduced so
			 * tell validate_mm_rb to ignore pre-swap()
			 * "next" (which is stored in post-swap()
			 * "vma").
			 */
			__vma_unlink(mm, next, vma);
		अगर (file)
			__हटाओ_shared_vm_काष्ठा(next, file, mapping);
	पूर्ण अन्यथा अगर (insert) अणु
		/*
		 * split_vma has split insert from vma, and needs
		 * us to insert it beक्रमe dropping the locks
		 * (it may either follow vma or precede it).
		 */
		__insert_vm_काष्ठा(mm, insert);
	पूर्ण अन्यथा अणु
		अगर (start_changed)
			vma_gap_update(vma);
		अगर (end_changed) अणु
			अगर (!next)
				mm->highest_vm_end = vm_end_gap(vma);
			अन्यथा अगर (!adjust_next)
				vma_gap_update(next);
		पूर्ण
	पूर्ण

	अगर (anon_vma) अणु
		anon_vma_पूर्णांकerval_tree_post_update_vma(vma);
		अगर (adjust_next)
			anon_vma_पूर्णांकerval_tree_post_update_vma(next);
		anon_vma_unlock_ग_लिखो(anon_vma);
	पूर्ण

	अगर (file) अणु
		i_mmap_unlock_ग_लिखो(mapping);
		uprobe_mmap(vma);

		अगर (adjust_next)
			uprobe_mmap(next);
	पूर्ण

	अगर (हटाओ_next) अणु
		अगर (file) अणु
			uprobe_munmap(next, next->vm_start, next->vm_end);
			fput(file);
		पूर्ण
		अगर (next->anon_vma)
			anon_vma_merge(vma, next);
		mm->map_count--;
		mpol_put(vma_policy(next));
		vm_area_मुक्त(next);
		/*
		 * In mprotect's हाल 6 (see comments on vma_merge),
		 * we must हटाओ another next too. It would clutter
		 * up the code too much to करो both in one go.
		 */
		अगर (हटाओ_next != 3) अणु
			/*
			 * If "next" was हटाओd and vma->vm_end was
			 * expanded (up) over it, in turn
			 * "next->vm_prev->vm_end" changed and the
			 * "vma->vm_next" gap must be updated.
			 */
			next = vma->vm_next;
		पूर्ण अन्यथा अणु
			/*
			 * For the scope of the comment "next" and
			 * "vma" considered pre-swap(): अगर "vma" was
			 * हटाओd, next->vm_start was expanded (करोwn)
			 * over it and the "next" gap must be updated.
			 * Because of the swap() the post-swap() "vma"
			 * actually poपूर्णांकs to pre-swap() "next"
			 * (post-swap() "next" as opposed is now a
			 * dangling poपूर्णांकer).
			 */
			next = vma;
		पूर्ण
		अगर (हटाओ_next == 2) अणु
			हटाओ_next = 1;
			end = next->vm_end;
			जाओ again;
		पूर्ण
		अन्यथा अगर (next)
			vma_gap_update(next);
		अन्यथा अणु
			/*
			 * If हटाओ_next == 2 we obviously can't
			 * reach this path.
			 *
			 * If हटाओ_next == 3 we can't reach this
			 * path because pre-swap() next is always not
			 * शून्य. pre-swap() "next" is not being
			 * हटाओd and its next->vm_end is not altered
			 * (and furthermore "end" alपढ़ोy matches
			 * next->vm_end in हटाओ_next == 3).
			 *
			 * We reach this only in the हटाओ_next == 1
			 * हाल अगर the "next" vma that was हटाओd was
			 * the highest vma of the mm. However in such
			 * हाल next->vm_end == "end" and the extended
			 * "vma" has vma->vm_end == next->vm_end so
			 * mm->highest_vm_end करोesn't need any update
			 * in हटाओ_next == 1 हाल.
			 */
			VM_WARN_ON(mm->highest_vm_end != vm_end_gap(vma));
		पूर्ण
	पूर्ण
	अगर (insert && file)
		uprobe_mmap(insert);

	validate_mm(mm);

	वापस 0;
पूर्ण

/*
 * If the vma has a ->बंद operation then the driver probably needs to release
 * per-vma resources, so we करोn't attempt to merge those.
 */
अटल अंतरभूत पूर्णांक is_mergeable_vma(काष्ठा vm_area_काष्ठा *vma,
				काष्ठा file *file, अचिन्हित दीर्घ vm_flags,
				काष्ठा vm_userfaultfd_ctx vm_userfaultfd_ctx)
अणु
	/*
	 * VM_SOFTसूचीTY should not prevent from VMA merging, अगर we
	 * match the flags but dirty bit -- the caller should mark
	 * merged VMA as dirty. If dirty bit won't be excluded from
	 * comparison, we increase pressure on the memory प्रणाली क्रमcing
	 * the kernel to generate new VMAs when old one could be
	 * extended instead.
	 */
	अगर ((vma->vm_flags ^ vm_flags) & ~VM_SOFTसूचीTY)
		वापस 0;
	अगर (vma->vm_file != file)
		वापस 0;
	अगर (vma->vm_ops && vma->vm_ops->बंद)
		वापस 0;
	अगर (!is_mergeable_vm_userfaultfd_ctx(vma, vm_userfaultfd_ctx))
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_mergeable_anon_vma(काष्ठा anon_vma *anon_vma1,
					काष्ठा anon_vma *anon_vma2,
					काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * The list_is_singular() test is to aव्योम merging VMA cloned from
	 * parents. This can improve scalability caused by anon_vma lock.
	 */
	अगर ((!anon_vma1 || !anon_vma2) && (!vma ||
		list_is_singular(&vma->anon_vma_chain)))
		वापस 1;
	वापस anon_vma1 == anon_vma2;
पूर्ण

/*
 * Return true अगर we can merge this (vm_flags,anon_vma,file,vm_pgoff)
 * in front of (at a lower भव address and file offset than) the vma.
 *
 * We cannot merge two vmas अगर they have dअगरferently asचिन्हित (non-शून्य)
 * anon_vmas, nor अगर same anon_vma is asचिन्हित but offsets incompatible.
 *
 * We करोn't check here क्रम the merged mmap wrapping around the end of pagecache
 * indices (16TB on ia32) because करो_mmap() करोes not permit mmap's which
 * wrap, nor mmaps which cover the final page at index -1UL.
 */
अटल पूर्णांक
can_vma_merge_beक्रमe(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vm_flags,
		     काष्ठा anon_vma *anon_vma, काष्ठा file *file,
		     pgoff_t vm_pgoff,
		     काष्ठा vm_userfaultfd_ctx vm_userfaultfd_ctx)
अणु
	अगर (is_mergeable_vma(vma, file, vm_flags, vm_userfaultfd_ctx) &&
	    is_mergeable_anon_vma(anon_vma, vma->anon_vma, vma)) अणु
		अगर (vma->vm_pgoff == vm_pgoff)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return true अगर we can merge this (vm_flags,anon_vma,file,vm_pgoff)
 * beyond (at a higher भव address and file offset than) the vma.
 *
 * We cannot merge two vmas अगर they have dअगरferently asचिन्हित (non-शून्य)
 * anon_vmas, nor अगर same anon_vma is asचिन्हित but offsets incompatible.
 */
अटल पूर्णांक
can_vma_merge_after(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vm_flags,
		    काष्ठा anon_vma *anon_vma, काष्ठा file *file,
		    pgoff_t vm_pgoff,
		    काष्ठा vm_userfaultfd_ctx vm_userfaultfd_ctx)
अणु
	अगर (is_mergeable_vma(vma, file, vm_flags, vm_userfaultfd_ctx) &&
	    is_mergeable_anon_vma(anon_vma, vma->anon_vma, vma)) अणु
		pgoff_t vm_pglen;
		vm_pglen = vma_pages(vma);
		अगर (vma->vm_pgoff + vm_pglen == vm_pgoff)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Given a mapping request (addr,end,vm_flags,file,pgoff), figure out
 * whether that can be merged with its predecessor or its successor.
 * Or both (it neatly fills a hole).
 *
 * In most हालs - when called क्रम mmap, brk or mremap - [addr,end) is
 * certain not to be mapped by the समय vma_merge is called; but when
 * called क्रम mprotect, it is certain to be alपढ़ोy mapped (either at
 * an offset within prev, or at the start of next), and the flags of
 * this area are about to be changed to vm_flags - and the no-change
 * हाल has alपढ़ोy been eliminated.
 *
 * The following mprotect हालs have to be considered, where AAAA is
 * the area passed करोwn from mprotect_fixup, never extending beyond one
 * vma, PPPPPP is the prev vma specअगरied, and NNNNNN the next vma after:
 *
 *     AAAA             AAAA                   AAAA
 *    PPPPPPNNNNNN    PPPPPPNNNNNN       PPPPPPNNNNNN
 *    cannot merge    might become       might become
 *                    PPNNNNNNNNNN       PPPPPPPPPPNN
 *    mmap, brk or    हाल 4 below       हाल 5 below
 *    mremap move:
 *                        AAAA               AAAA
 *                    PPPP    NNNN       PPPPNNNNXXXX
 *                    might become       might become
 *                    PPPPPPPPPPPP 1 or  PPPPPPPPPPPP 6 or
 *                    PPPPPPPPNNNN 2 or  PPPPPPPPXXXX 7 or
 *                    PPPPNNNNNNNN 3     PPPPXXXXXXXX 8
 *
 * It is important क्रम हाल 8 that the vma NNNN overlapping the
 * region AAAA is never going to extended over XXXX. Instead XXXX must
 * be extended in region AAAA and NNNN must be हटाओd. This way in
 * all हालs where vma_merge succeeds, the moment vma_adjust drops the
 * rmap_locks, the properties of the merged vma will be alपढ़ोy
 * correct क्रम the whole merged range. Some of those properties like
 * vm_page_prot/vm_flags may be accessed by rmap_walks and they must
 * be correct क्रम the whole merged range immediately after the
 * rmap_locks are released. Otherwise अगर XXXX would be हटाओd and
 * NNNN would be extended over the XXXX range, हटाओ_migration_ptes
 * or other rmap walkers (अगर working on addresses beyond the "end"
 * parameter) may establish ptes with the wrong permissions of NNNN
 * instead of the right permissions of XXXX.
 */
काष्ठा vm_area_काष्ठा *vma_merge(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *prev, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ end, अचिन्हित दीर्घ vm_flags,
			काष्ठा anon_vma *anon_vma, काष्ठा file *file,
			pgoff_t pgoff, काष्ठा mempolicy *policy,
			काष्ठा vm_userfaultfd_ctx vm_userfaultfd_ctx)
अणु
	pgoff_t pglen = (end - addr) >> PAGE_SHIFT;
	काष्ठा vm_area_काष्ठा *area, *next;
	पूर्णांक err;

	/*
	 * We later require that vma->vm_flags == vm_flags,
	 * so this tests vma->vm_flags & VM_SPECIAL, too.
	 */
	अगर (vm_flags & VM_SPECIAL)
		वापस शून्य;

	next = vma_next(mm, prev);
	area = next;
	अगर (area && area->vm_end == end)		/* हालs 6, 7, 8 */
		next = next->vm_next;

	/* verअगरy some invariant that must be enक्रमced by the caller */
	VM_WARN_ON(prev && addr <= prev->vm_start);
	VM_WARN_ON(area && end > area->vm_end);
	VM_WARN_ON(addr >= end);

	/*
	 * Can it merge with the predecessor?
	 */
	अगर (prev && prev->vm_end == addr &&
			mpol_equal(vma_policy(prev), policy) &&
			can_vma_merge_after(prev, vm_flags,
					    anon_vma, file, pgoff,
					    vm_userfaultfd_ctx)) अणु
		/*
		 * OK, it can.  Can we now merge in the successor as well?
		 */
		अगर (next && end == next->vm_start &&
				mpol_equal(policy, vma_policy(next)) &&
				can_vma_merge_beक्रमe(next, vm_flags,
						     anon_vma, file,
						     pgoff+pglen,
						     vm_userfaultfd_ctx) &&
				is_mergeable_anon_vma(prev->anon_vma,
						      next->anon_vma, शून्य)) अणु
							/* हालs 1, 6 */
			err = __vma_adjust(prev, prev->vm_start,
					 next->vm_end, prev->vm_pgoff, शून्य,
					 prev);
		पूर्ण अन्यथा					/* हालs 2, 5, 7 */
			err = __vma_adjust(prev, prev->vm_start,
					 end, prev->vm_pgoff, शून्य, prev);
		अगर (err)
			वापस शून्य;
		khugepaged_enter_vma_merge(prev, vm_flags);
		वापस prev;
	पूर्ण

	/*
	 * Can this new request be merged in front of next?
	 */
	अगर (next && end == next->vm_start &&
			mpol_equal(policy, vma_policy(next)) &&
			can_vma_merge_beक्रमe(next, vm_flags,
					     anon_vma, file, pgoff+pglen,
					     vm_userfaultfd_ctx)) अणु
		अगर (prev && addr < prev->vm_end)	/* हाल 4 */
			err = __vma_adjust(prev, prev->vm_start,
					 addr, prev->vm_pgoff, शून्य, next);
		अन्यथा अणु					/* हालs 3, 8 */
			err = __vma_adjust(area, addr, next->vm_end,
					 next->vm_pgoff - pglen, शून्य, next);
			/*
			 * In हाल 3 area is alपढ़ोy equal to next and
			 * this is a noop, but in हाल 8 "area" has
			 * been हटाओd and next was expanded over it.
			 */
			area = next;
		पूर्ण
		अगर (err)
			वापस शून्य;
		khugepaged_enter_vma_merge(area, vm_flags);
		वापस area;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Rough compatibility check to quickly see अगर it's even worth looking
 * at sharing an anon_vma.
 *
 * They need to have the same vm_file, and the flags can only dअगरfer
 * in things that mprotect may change.
 *
 * NOTE! The fact that we share an anon_vma करोesn't _have_ to mean that
 * we can merge the two vma's. For example, we refuse to merge a vma अगर
 * there is a vm_ops->बंद() function, because that indicates that the
 * driver is करोing some kind of reference counting. But that करोesn't
 * really matter क्रम the anon_vma sharing हाल.
 */
अटल पूर्णांक anon_vma_compatible(काष्ठा vm_area_काष्ठा *a, काष्ठा vm_area_काष्ठा *b)
अणु
	वापस a->vm_end == b->vm_start &&
		mpol_equal(vma_policy(a), vma_policy(b)) &&
		a->vm_file == b->vm_file &&
		!((a->vm_flags ^ b->vm_flags) & ~(VM_ACCESS_FLAGS | VM_SOFTसूचीTY)) &&
		b->vm_pgoff == a->vm_pgoff + ((b->vm_start - a->vm_start) >> PAGE_SHIFT);
पूर्ण

/*
 * Do some basic sanity checking to see अगर we can re-use the anon_vma
 * from 'old'. The 'a'/'b' vma's are in VM order - one of them will be
 * the same as 'old', the other will be the new one that is trying
 * to share the anon_vma.
 *
 * NOTE! This runs with mm_sem held क्रम पढ़ोing, so it is possible that
 * the anon_vma of 'old' is concurrently in the process of being set up
 * by another page fault trying to merge _that_. But that's ok: अगर it
 * is being set up, that स्वतःmatically means that it will be a singleton
 * acceptable क्रम merging, so we can करो all of this optimistically. But
 * we करो that READ_ONCE() to make sure that we never re-load the poपूर्णांकer.
 *
 * IOW: that the "list_is_singular()" test on the anon_vma_chain only
 * matters क्रम the 'stable anon_vma' हाल (ie the thing we want to aव्योम
 * is to वापस an anon_vma that is "complex" due to having gone through
 * a विभाजन).
 *
 * We also make sure that the two vma's are compatible (adjacent,
 * and with the same memory policies). That's all stable, even with just
 * a पढ़ो lock on the mm_sem.
 */
अटल काष्ठा anon_vma *reusable_anon_vma(काष्ठा vm_area_काष्ठा *old, काष्ठा vm_area_काष्ठा *a, काष्ठा vm_area_काष्ठा *b)
अणु
	अगर (anon_vma_compatible(a, b)) अणु
		काष्ठा anon_vma *anon_vma = READ_ONCE(old->anon_vma);

		अगर (anon_vma && list_is_singular(&old->anon_vma_chain))
			वापस anon_vma;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * find_mergeable_anon_vma is used by anon_vma_prepare, to check
 * neighbouring vmas क्रम a suitable anon_vma, beक्रमe it goes off
 * to allocate a new anon_vma.  It checks because a repetitive
 * sequence of mprotects and faults may otherwise lead to distinct
 * anon_vmas being allocated, preventing vma merge in subsequent
 * mprotect.
 */
काष्ठा anon_vma *find_mergeable_anon_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा anon_vma *anon_vma = शून्य;

	/* Try next first. */
	अगर (vma->vm_next) अणु
		anon_vma = reusable_anon_vma(vma->vm_next, vma, vma->vm_next);
		अगर (anon_vma)
			वापस anon_vma;
	पूर्ण

	/* Try prev next. */
	अगर (vma->vm_prev)
		anon_vma = reusable_anon_vma(vma->vm_prev, vma->vm_prev, vma);

	/*
	 * We might reach here with anon_vma == शून्य अगर we can't find
	 * any reusable anon_vma.
	 * There's no असलolute need to look only at touching neighbours:
	 * we could search further afield क्रम "compatible" anon_vmas.
	 * But it would probably just be a waste of समय searching,
	 * or lead to too many vmas hanging off the same anon_vma.
	 * We're trying to allow mprotect remerging later on,
	 * not trying to minimize memory used क्रम anon_vmas.
	 */
	वापस anon_vma;
पूर्ण

/*
 * If a hपूर्णांक addr is less than mmap_min_addr change hपूर्णांक to be as
 * low as possible but still greater than mmap_min_addr
 */
अटल अंतरभूत अचिन्हित दीर्घ round_hपूर्णांक_to_min(अचिन्हित दीर्घ hपूर्णांक)
अणु
	hपूर्णांक &= PAGE_MASK;
	अगर (((व्योम *)hपूर्णांक != शून्य) &&
	    (hपूर्णांक < mmap_min_addr))
		वापस PAGE_ALIGN(mmap_min_addr);
	वापस hपूर्णांक;
पूर्ण

अटल अंतरभूत पूर्णांक mlock_future_check(काष्ठा mm_काष्ठा *mm,
				     अचिन्हित दीर्घ flags,
				     अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ locked, lock_limit;

	/*  mlock MCL_FUTURE? */
	अगर (flags & VM_LOCKED) अणु
		locked = len >> PAGE_SHIFT;
		locked += mm->locked_vm;
		lock_limit = rlimit(RLIMIT_MEMLOCK);
		lock_limit >>= PAGE_SHIFT;
		अगर (locked > lock_limit && !capable(CAP_IPC_LOCK))
			वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u64 file_mmap_size_max(काष्ठा file *file, काष्ठा inode *inode)
अणु
	अगर (S_ISREG(inode->i_mode))
		वापस MAX_LFS_खाताSIZE;

	अगर (S_ISBLK(inode->i_mode))
		वापस MAX_LFS_खाताSIZE;

	अगर (S_ISSOCK(inode->i_mode))
		वापस MAX_LFS_खाताSIZE;

	/* Special "we do even unsigned file positions" हाल */
	अगर (file->f_mode & FMODE_UNSIGNED_OFFSET)
		वापस 0;

	/* Yes, अक्रमom drivers might want more. But I'm tired of buggy drivers */
	वापस अच_दीर्घ_उच्च;
पूर्ण

अटल अंतरभूत bool file_mmap_ok(काष्ठा file *file, काष्ठा inode *inode,
				अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ len)
अणु
	u64 maxsize = file_mmap_size_max(file, inode);

	अगर (maxsize && len > maxsize)
		वापस false;
	maxsize -= len;
	अगर (pgoff > maxsize >> PAGE_SHIFT)
		वापस false;
	वापस true;
पूर्ण

/*
 * The caller must ग_लिखो-lock current->mm->mmap_lock.
 */
अचिन्हित दीर्घ करो_mmap(काष्ठा file *file, अचिन्हित दीर्घ addr,
			अचिन्हित दीर्घ len, अचिन्हित दीर्घ prot,
			अचिन्हित दीर्घ flags, अचिन्हित दीर्घ pgoff,
			अचिन्हित दीर्घ *populate, काष्ठा list_head *uf)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	vm_flags_t vm_flags;
	पूर्णांक pkey = 0;

	*populate = 0;

	अगर (!len)
		वापस -EINVAL;

	/*
	 * Does the application expect PROT_READ to imply PROT_EXEC?
	 *
	 * (the exception is when the underlying fileप्रणाली is noexec
	 *  mounted, in which हाल we करोnt add PROT_EXEC.)
	 */
	अगर ((prot & PROT_READ) && (current->personality & READ_IMPLIES_EXEC))
		अगर (!(file && path_noexec(&file->f_path)))
			prot |= PROT_EXEC;

	/* क्रमce arch specअगरic MAP_FIXED handling in get_unmapped_area */
	अगर (flags & MAP_FIXED_NOREPLACE)
		flags |= MAP_FIXED;

	अगर (!(flags & MAP_FIXED))
		addr = round_hपूर्णांक_to_min(addr);

	/* Careful about overflows.. */
	len = PAGE_ALIGN(len);
	अगर (!len)
		वापस -ENOMEM;

	/* offset overflow? */
	अगर ((pgoff + (len >> PAGE_SHIFT)) < pgoff)
		वापस -EOVERFLOW;

	/* Too many mappings? */
	अगर (mm->map_count > sysctl_max_map_count)
		वापस -ENOMEM;

	/* Obtain the address to map to. we verअगरy (or select) it and ensure
	 * that it represents a valid section of the address space.
	 */
	addr = get_unmapped_area(file, addr, len, pgoff, flags);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	अगर (flags & MAP_FIXED_NOREPLACE) अणु
		काष्ठा vm_area_काष्ठा *vma = find_vma(mm, addr);

		अगर (vma && vma->vm_start < addr + len)
			वापस -EEXIST;
	पूर्ण

	अगर (prot == PROT_EXEC) अणु
		pkey = execute_only_pkey(mm);
		अगर (pkey < 0)
			pkey = 0;
	पूर्ण

	/* Do simple checking here so the lower-level routines won't have
	 * to. we assume access permissions have been handled by the खोलो
	 * of the memory object, so we करोn't करो any here.
	 */
	vm_flags = calc_vm_prot_bits(prot, pkey) | calc_vm_flag_bits(flags) |
			mm->def_flags | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC;

	अगर (flags & MAP_LOCKED)
		अगर (!can_करो_mlock())
			वापस -EPERM;

	अगर (mlock_future_check(mm, vm_flags, len))
		वापस -EAGAIN;

	अगर (file) अणु
		काष्ठा inode *inode = file_inode(file);
		अचिन्हित दीर्घ flags_mask;

		अगर (!file_mmap_ok(file, inode, pgoff, len))
			वापस -EOVERFLOW;

		flags_mask = LEGACY_MAP_MASK | file->f_op->mmap_supported_flags;

		चयन (flags & MAP_TYPE) अणु
		हाल MAP_SHARED:
			/*
			 * Force use of MAP_SHARED_VALIDATE with non-legacy
			 * flags. E.g. MAP_SYNC is dangerous to use with
			 * MAP_SHARED as you करोn't know which consistency model
			 * you will get. We silently ignore unsupported flags
			 * with MAP_SHARED to preserve backward compatibility.
			 */
			flags &= LEGACY_MAP_MASK;
			fallthrough;
		हाल MAP_SHARED_VALIDATE:
			अगर (flags & ~flags_mask)
				वापस -EOPNOTSUPP;
			अगर (prot & PROT_WRITE) अणु
				अगर (!(file->f_mode & FMODE_WRITE))
					वापस -EACCES;
				अगर (IS_SWAPखाता(file->f_mapping->host))
					वापस -ETXTBSY;
			पूर्ण

			/*
			 * Make sure we करोn't allow writing to an append-only
			 * file..
			 */
			अगर (IS_APPEND(inode) && (file->f_mode & FMODE_WRITE))
				वापस -EACCES;

			/*
			 * Make sure there are no mandatory locks on the file.
			 */
			अगर (locks_verअगरy_locked(file))
				वापस -EAGAIN;

			vm_flags |= VM_SHARED | VM_MAYSHARE;
			अगर (!(file->f_mode & FMODE_WRITE))
				vm_flags &= ~(VM_MAYWRITE | VM_SHARED);
			fallthrough;
		हाल MAP_PRIVATE:
			अगर (!(file->f_mode & FMODE_READ))
				वापस -EACCES;
			अगर (path_noexec(&file->f_path)) अणु
				अगर (vm_flags & VM_EXEC)
					वापस -EPERM;
				vm_flags &= ~VM_MAYEXEC;
			पूर्ण

			अगर (!file->f_op->mmap)
				वापस -ENODEV;
			अगर (vm_flags & (VM_GROWSDOWN|VM_GROWSUP))
				वापस -EINVAL;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (flags & MAP_TYPE) अणु
		हाल MAP_SHARED:
			अगर (vm_flags & (VM_GROWSDOWN|VM_GROWSUP))
				वापस -EINVAL;
			/*
			 * Ignore pgoff.
			 */
			pgoff = 0;
			vm_flags |= VM_SHARED | VM_MAYSHARE;
			अवरोध;
		हाल MAP_PRIVATE:
			/*
			 * Set pgoff according to addr क्रम anon_vma.
			 */
			pgoff = addr >> PAGE_SHIFT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Set 'VM_NORESERVE' अगर we should not account क्रम the
	 * memory use of this mapping.
	 */
	अगर (flags & MAP_NORESERVE) अणु
		/* We honor MAP_NORESERVE अगर allowed to overcommit */
		अगर (sysctl_overcommit_memory != OVERCOMMIT_NEVER)
			vm_flags |= VM_NORESERVE;

		/* hugetlb applies strict overcommit unless MAP_NORESERVE */
		अगर (file && is_file_hugepages(file))
			vm_flags |= VM_NORESERVE;
	पूर्ण

	addr = mmap_region(file, addr, len, vm_flags, pgoff, uf);
	अगर (!IS_ERR_VALUE(addr) &&
	    ((vm_flags & VM_LOCKED) ||
	     (flags & (MAP_POPULATE | MAP_NONBLOCK)) == MAP_POPULATE))
		*populate = len;
	वापस addr;
पूर्ण

अचिन्हित दीर्घ ksys_mmap_pgoff(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			      अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			      अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff)
अणु
	काष्ठा file *file = शून्य;
	अचिन्हित दीर्घ retval;

	अगर (!(flags & MAP_ANONYMOUS)) अणु
		audit_mmap_fd(fd, flags);
		file = fget(fd);
		अगर (!file)
			वापस -EBADF;
		अगर (is_file_hugepages(file)) अणु
			len = ALIGN(len, huge_page_size(hstate_file(file)));
		पूर्ण अन्यथा अगर (unlikely(flags & MAP_HUGETLB)) अणु
			retval = -EINVAL;
			जाओ out_fput;
		पूर्ण
	पूर्ण अन्यथा अगर (flags & MAP_HUGETLB) अणु
		काष्ठा user_काष्ठा *user = शून्य;
		काष्ठा hstate *hs;

		hs = hstate_sizelog((flags >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK);
		अगर (!hs)
			वापस -EINVAL;

		len = ALIGN(len, huge_page_size(hs));
		/*
		 * VM_NORESERVE is used because the reservations will be
		 * taken when vm_ops->mmap() is called
		 * A dummy user value is used because we are not locking
		 * memory so no accounting is necessary
		 */
		file = hugetlb_file_setup(HUGETLB_ANON_खाता, len,
				VM_NORESERVE,
				&user, HUGETLB_ANONHUGE_INODE,
				(flags >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK);
		अगर (IS_ERR(file))
			वापस PTR_ERR(file);
	पूर्ण

	flags &= ~(MAP_EXECUTABLE | MAP_DENYWRITE);

	retval = vm_mmap_pgoff(file, addr, len, prot, flags, pgoff);
out_fput:
	अगर (file)
		fput(file);
	वापस retval;
पूर्ण

SYSCALL_DEFINE6(mmap_pgoff, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, pgoff)
अणु
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_OLD_MMAP
काष्ठा mmap_arg_काष्ठा अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ prot;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ fd;
	अचिन्हित दीर्घ offset;
पूर्ण;

SYSCALL_DEFINE1(old_mmap, काष्ठा mmap_arg_काष्ठा __user *, arg)
अणु
	काष्ठा mmap_arg_काष्ठा a;

	अगर (copy_from_user(&a, arg, माप(a)))
		वापस -EFAULT;
	अगर (offset_in_page(a.offset))
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd,
			       a.offset >> PAGE_SHIFT);
पूर्ण
#पूर्ण_अगर /* __ARCH_WANT_SYS_OLD_MMAP */

/*
 * Some shared mappings will want the pages marked पढ़ो-only
 * to track ग_लिखो events. If so, we'll करोwngrade vm_page_prot
 * to the निजी version (using protection_map[] without the
 * VM_SHARED bit).
 */
पूर्णांक vma_wants_ग_लिखोnotअगरy(काष्ठा vm_area_काष्ठा *vma, pgprot_t vm_page_prot)
अणु
	vm_flags_t vm_flags = vma->vm_flags;
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops = vma->vm_ops;

	/* If it was निजी or non-writable, the ग_लिखो bit is alपढ़ोy clear */
	अगर ((vm_flags & (VM_WRITE|VM_SHARED)) != ((VM_WRITE|VM_SHARED)))
		वापस 0;

	/* The backer wishes to know when pages are first written to? */
	अगर (vm_ops && (vm_ops->page_mkग_लिखो || vm_ops->pfn_mkग_लिखो))
		वापस 1;

	/* The खोलो routine did something to the protections that pgprot_modअगरy
	 * won't preserve? */
	अगर (pgprot_val(vm_page_prot) !=
	    pgprot_val(vm_pgprot_modअगरy(vm_page_prot, vm_flags)))
		वापस 0;

	/* Do we need to track softdirty? */
	अगर (IS_ENABLED(CONFIG_MEM_SOFT_सूचीTY) && !(vm_flags & VM_SOFTसूचीTY))
		वापस 1;

	/* Specialty mapping? */
	अगर (vm_flags & VM_PFNMAP)
		वापस 0;

	/* Can the mapping track the dirty pages? */
	वापस vma->vm_file && vma->vm_file->f_mapping &&
		mapping_can_ग_लिखोback(vma->vm_file->f_mapping);
पूर्ण

/*
 * We account क्रम memory अगर it's a निजी ग_लिखोable mapping,
 * not hugepages and VM_NORESERVE wasn't set.
 */
अटल अंतरभूत पूर्णांक accountable_mapping(काष्ठा file *file, vm_flags_t vm_flags)
अणु
	/*
	 * hugetlb has its own accounting separate from the core VM
	 * VM_HUGETLB may not be set yet so we cannot check क्रम that flag.
	 */
	अगर (file && is_file_hugepages(file))
		वापस 0;

	वापस (vm_flags & (VM_NORESERVE | VM_SHARED | VM_WRITE)) == VM_WRITE;
पूर्ण

अचिन्हित दीर्घ mmap_region(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, vm_flags_t vm_flags, अचिन्हित दीर्घ pgoff,
		काष्ठा list_head *uf)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev, *merge;
	पूर्णांक error;
	काष्ठा rb_node **rb_link, *rb_parent;
	अचिन्हित दीर्घ अक्षरged = 0;

	/* Check against address space limit. */
	अगर (!may_expand_vm(mm, vm_flags, len >> PAGE_SHIFT)) अणु
		अचिन्हित दीर्घ nr_pages;

		/*
		 * MAP_FIXED may हटाओ pages of mappings that पूर्णांकersects with
		 * requested mapping. Account क्रम the pages it would unmap.
		 */
		nr_pages = count_vma_pages_range(mm, addr, addr + len);

		अगर (!may_expand_vm(mm, vm_flags,
					(len >> PAGE_SHIFT) - nr_pages))
			वापस -ENOMEM;
	पूर्ण

	/* Clear old maps, set up prev, rb_link, rb_parent, and uf */
	अगर (munmap_vma_range(mm, addr, len, &prev, &rb_link, &rb_parent, uf))
		वापस -ENOMEM;
	/*
	 * Private writable mapping: check memory availability
	 */
	अगर (accountable_mapping(file, vm_flags)) अणु
		अक्षरged = len >> PAGE_SHIFT;
		अगर (security_vm_enough_memory_mm(mm, अक्षरged))
			वापस -ENOMEM;
		vm_flags |= VM_ACCOUNT;
	पूर्ण

	/*
	 * Can we just expand an old mapping?
	 */
	vma = vma_merge(mm, prev, addr, addr + len, vm_flags,
			शून्य, file, pgoff, शून्य, शून्य_VM_UFFD_CTX);
	अगर (vma)
		जाओ out;

	/*
	 * Determine the object being mapped and call the appropriate
	 * specअगरic mapper. the address has alपढ़ोy been validated, but
	 * not unmapped, but the maps are हटाओd from the list.
	 */
	vma = vm_area_alloc(mm);
	अगर (!vma) अणु
		error = -ENOMEM;
		जाओ unacct_error;
	पूर्ण

	vma->vm_start = addr;
	vma->vm_end = addr + len;
	vma->vm_flags = vm_flags;
	vma->vm_page_prot = vm_get_page_prot(vm_flags);
	vma->vm_pgoff = pgoff;

	अगर (file) अणु
		अगर (vm_flags & VM_DENYWRITE) अणु
			error = deny_ग_लिखो_access(file);
			अगर (error)
				जाओ मुक्त_vma;
		पूर्ण
		अगर (vm_flags & VM_SHARED) अणु
			error = mapping_map_writable(file->f_mapping);
			अगर (error)
				जाओ allow_ग_लिखो_and_मुक्त_vma;
		पूर्ण

		/* ->mmap() can change vma->vm_file, but must guarantee that
		 * vma_link() below can deny ग_लिखो-access अगर VM_DENYWRITE is set
		 * and map writably अगर VM_SHARED is set. This usually means the
		 * new file must not have been exposed to user-space, yet.
		 */
		vma->vm_file = get_file(file);
		error = call_mmap(file, vma);
		अगर (error)
			जाओ unmap_and_मुक्त_vma;

		/* Can addr have changed??
		 *
		 * Answer: Yes, several device drivers can करो it in their
		 *         f_op->mmap method. -DaveM
		 * Bug: If addr is changed, prev, rb_link, rb_parent should
		 *      be updated क्रम vma_link()
		 */
		WARN_ON_ONCE(addr != vma->vm_start);

		addr = vma->vm_start;

		/* If vm_flags changed after call_mmap(), we should try merge vma again
		 * as we may succeed this समय.
		 */
		अगर (unlikely(vm_flags != vma->vm_flags && prev)) अणु
			merge = vma_merge(mm, prev, vma->vm_start, vma->vm_end, vma->vm_flags,
				शून्य, vma->vm_file, vma->vm_pgoff, शून्य, शून्य_VM_UFFD_CTX);
			अगर (merge) अणु
				/* ->mmap() can change vma->vm_file and fput the original file. So
				 * fput the vma->vm_file here or we would add an extra fput क्रम file
				 * and cause general protection fault ultimately.
				 */
				fput(vma->vm_file);
				vm_area_मुक्त(vma);
				vma = merge;
				/* Update vm_flags to pick up the change. */
				vm_flags = vma->vm_flags;
				जाओ unmap_writable;
			पूर्ण
		पूर्ण

		vm_flags = vma->vm_flags;
	पूर्ण अन्यथा अगर (vm_flags & VM_SHARED) अणु
		error = shmem_zero_setup(vma);
		अगर (error)
			जाओ मुक्त_vma;
	पूर्ण अन्यथा अणु
		vma_set_anonymous(vma);
	पूर्ण

	/* Allow architectures to sanity-check the vm_flags */
	अगर (!arch_validate_flags(vma->vm_flags)) अणु
		error = -EINVAL;
		अगर (file)
			जाओ unmap_and_मुक्त_vma;
		अन्यथा
			जाओ मुक्त_vma;
	पूर्ण

	vma_link(mm, vma, prev, rb_link, rb_parent);
	/* Once vma denies ग_लिखो, unकरो our temporary denial count */
	अगर (file) अणु
unmap_writable:
		अगर (vm_flags & VM_SHARED)
			mapping_unmap_writable(file->f_mapping);
		अगर (vm_flags & VM_DENYWRITE)
			allow_ग_लिखो_access(file);
	पूर्ण
	file = vma->vm_file;
out:
	perf_event_mmap(vma);

	vm_stat_account(mm, vm_flags, len >> PAGE_SHIFT);
	अगर (vm_flags & VM_LOCKED) अणु
		अगर ((vm_flags & VM_SPECIAL) || vma_is_dax(vma) ||
					is_vm_hugetlb_page(vma) ||
					vma == get_gate_vma(current->mm))
			vma->vm_flags &= VM_LOCKED_CLEAR_MASK;
		अन्यथा
			mm->locked_vm += (len >> PAGE_SHIFT);
	पूर्ण

	अगर (file)
		uprobe_mmap(vma);

	/*
	 * New (or expanded) vma always get soft dirty status.
	 * Otherwise user-space soft-dirty page tracker won't
	 * be able to distinguish situation when vma area unmapped,
	 * then new mapped in-place (which must be aimed as
	 * a completely new data area).
	 */
	vma->vm_flags |= VM_SOFTसूचीTY;

	vma_set_page_prot(vma);

	वापस addr;

unmap_and_मुक्त_vma:
	fput(vma->vm_file);
	vma->vm_file = शून्य;

	/* Unकरो any partial mapping करोne by a device driver. */
	unmap_region(mm, vma, prev, vma->vm_start, vma->vm_end);
	अक्षरged = 0;
	अगर (vm_flags & VM_SHARED)
		mapping_unmap_writable(file->f_mapping);
allow_ग_लिखो_and_मुक्त_vma:
	अगर (vm_flags & VM_DENYWRITE)
		allow_ग_लिखो_access(file);
मुक्त_vma:
	vm_area_मुक्त(vma);
unacct_error:
	अगर (अक्षरged)
		vm_unacct_memory(अक्षरged);
	वापस error;
पूर्ण

अटल अचिन्हित दीर्घ unmapped_area(काष्ठा vm_unmapped_area_info *info)
अणु
	/*
	 * We implement the search by looking क्रम an rbtree node that
	 * immediately follows a suitable gap. That is,
	 * - gap_start = vma->vm_prev->vm_end <= info->high_limit - length;
	 * - gap_end   = vma->vm_start        >= info->low_limit  + length;
	 * - gap_end - gap_start >= length
	 */

	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ length, low_limit, high_limit, gap_start, gap_end;

	/* Adjust search length to account क्रम worst हाल alignment overhead */
	length = info->length + info->align_mask;
	अगर (length < info->length)
		वापस -ENOMEM;

	/* Adjust search limits by the desired length */
	अगर (info->high_limit < length)
		वापस -ENOMEM;
	high_limit = info->high_limit - length;

	अगर (info->low_limit > high_limit)
		वापस -ENOMEM;
	low_limit = info->low_limit + length;

	/* Check अगर rbtree root looks promising */
	अगर (RB_EMPTY_ROOT(&mm->mm_rb))
		जाओ check_highest;
	vma = rb_entry(mm->mm_rb.rb_node, काष्ठा vm_area_काष्ठा, vm_rb);
	अगर (vma->rb_subtree_gap < length)
		जाओ check_highest;

	जबतक (true) अणु
		/* Visit left subtree अगर it looks promising */
		gap_end = vm_start_gap(vma);
		अगर (gap_end >= low_limit && vma->vm_rb.rb_left) अणु
			काष्ठा vm_area_काष्ठा *left =
				rb_entry(vma->vm_rb.rb_left,
					 काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (left->rb_subtree_gap >= length) अणु
				vma = left;
				जारी;
			पूर्ण
		पूर्ण

		gap_start = vma->vm_prev ? vm_end_gap(vma->vm_prev) : 0;
check_current:
		/* Check अगर current node has a suitable gap */
		अगर (gap_start > high_limit)
			वापस -ENOMEM;
		अगर (gap_end >= low_limit &&
		    gap_end > gap_start && gap_end - gap_start >= length)
			जाओ found;

		/* Visit right subtree अगर it looks promising */
		अगर (vma->vm_rb.rb_right) अणु
			काष्ठा vm_area_काष्ठा *right =
				rb_entry(vma->vm_rb.rb_right,
					 काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (right->rb_subtree_gap >= length) अणु
				vma = right;
				जारी;
			पूर्ण
		पूर्ण

		/* Go back up the rbtree to find next candidate node */
		जबतक (true) अणु
			काष्ठा rb_node *prev = &vma->vm_rb;
			अगर (!rb_parent(prev))
				जाओ check_highest;
			vma = rb_entry(rb_parent(prev),
				       काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (prev == vma->vm_rb.rb_left) अणु
				gap_start = vm_end_gap(vma->vm_prev);
				gap_end = vm_start_gap(vma);
				जाओ check_current;
			पूर्ण
		पूर्ण
	पूर्ण

check_highest:
	/* Check highest gap, which करोes not precede any rbtree node */
	gap_start = mm->highest_vm_end;
	gap_end = अच_दीर्घ_उच्च;  /* Only क्रम VM_BUG_ON below */
	अगर (gap_start > high_limit)
		वापस -ENOMEM;

found:
	/* We found a suitable gap. Clip it with the original low_limit. */
	अगर (gap_start < info->low_limit)
		gap_start = info->low_limit;

	/* Adjust gap address to the desired alignment */
	gap_start += (info->align_offset - gap_start) & info->align_mask;

	VM_BUG_ON(gap_start + info->length > info->high_limit);
	VM_BUG_ON(gap_start + info->length > gap_end);
	वापस gap_start;
पूर्ण

अटल अचिन्हित दीर्घ unmapped_area_topकरोwn(काष्ठा vm_unmapped_area_info *info)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ length, low_limit, high_limit, gap_start, gap_end;

	/* Adjust search length to account क्रम worst हाल alignment overhead */
	length = info->length + info->align_mask;
	अगर (length < info->length)
		वापस -ENOMEM;

	/*
	 * Adjust search limits by the desired length.
	 * See implementation comment at top of unmapped_area().
	 */
	gap_end = info->high_limit;
	अगर (gap_end < length)
		वापस -ENOMEM;
	high_limit = gap_end - length;

	अगर (info->low_limit > high_limit)
		वापस -ENOMEM;
	low_limit = info->low_limit + length;

	/* Check highest gap, which करोes not precede any rbtree node */
	gap_start = mm->highest_vm_end;
	अगर (gap_start <= high_limit)
		जाओ found_highest;

	/* Check अगर rbtree root looks promising */
	अगर (RB_EMPTY_ROOT(&mm->mm_rb))
		वापस -ENOMEM;
	vma = rb_entry(mm->mm_rb.rb_node, काष्ठा vm_area_काष्ठा, vm_rb);
	अगर (vma->rb_subtree_gap < length)
		वापस -ENOMEM;

	जबतक (true) अणु
		/* Visit right subtree अगर it looks promising */
		gap_start = vma->vm_prev ? vm_end_gap(vma->vm_prev) : 0;
		अगर (gap_start <= high_limit && vma->vm_rb.rb_right) अणु
			काष्ठा vm_area_काष्ठा *right =
				rb_entry(vma->vm_rb.rb_right,
					 काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (right->rb_subtree_gap >= length) अणु
				vma = right;
				जारी;
			पूर्ण
		पूर्ण

check_current:
		/* Check अगर current node has a suitable gap */
		gap_end = vm_start_gap(vma);
		अगर (gap_end < low_limit)
			वापस -ENOMEM;
		अगर (gap_start <= high_limit &&
		    gap_end > gap_start && gap_end - gap_start >= length)
			जाओ found;

		/* Visit left subtree अगर it looks promising */
		अगर (vma->vm_rb.rb_left) अणु
			काष्ठा vm_area_काष्ठा *left =
				rb_entry(vma->vm_rb.rb_left,
					 काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (left->rb_subtree_gap >= length) अणु
				vma = left;
				जारी;
			पूर्ण
		पूर्ण

		/* Go back up the rbtree to find next candidate node */
		जबतक (true) अणु
			काष्ठा rb_node *prev = &vma->vm_rb;
			अगर (!rb_parent(prev))
				वापस -ENOMEM;
			vma = rb_entry(rb_parent(prev),
				       काष्ठा vm_area_काष्ठा, vm_rb);
			अगर (prev == vma->vm_rb.rb_right) अणु
				gap_start = vma->vm_prev ?
					vm_end_gap(vma->vm_prev) : 0;
				जाओ check_current;
			पूर्ण
		पूर्ण
	पूर्ण

found:
	/* We found a suitable gap. Clip it with the original high_limit. */
	अगर (gap_end > info->high_limit)
		gap_end = info->high_limit;

found_highest:
	/* Compute highest gap address at the desired alignment */
	gap_end -= info->length;
	gap_end -= (gap_end - info->align_offset) & info->align_mask;

	VM_BUG_ON(gap_end < info->low_limit);
	VM_BUG_ON(gap_end < gap_start);
	वापस gap_end;
पूर्ण

/*
 * Search क्रम an unmapped address range.
 *
 * We are looking क्रम a range that:
 * - करोes not पूर्णांकersect with any VMA;
 * - is contained within the [low_limit, high_limit) पूर्णांकerval;
 * - is at least the desired size.
 * - satisfies (begin_addr & align_mask) == (align_offset & align_mask)
 */
अचिन्हित दीर्घ vm_unmapped_area(काष्ठा vm_unmapped_area_info *info)
अणु
	अचिन्हित दीर्घ addr;

	अगर (info->flags & VM_UNMAPPED_AREA_TOPDOWN)
		addr = unmapped_area_topकरोwn(info);
	अन्यथा
		addr = unmapped_area(info);

	trace_vm_unmapped_area(addr, info);
	वापस addr;
पूर्ण

#अगर_अघोषित arch_get_mmap_end
#घोषणा arch_get_mmap_end(addr)	(TASK_SIZE)
#पूर्ण_अगर

#अगर_अघोषित arch_get_mmap_base
#घोषणा arch_get_mmap_base(addr, base) (base)
#पूर्ण_अगर

/* Get an address range which is currently unmapped.
 * For shmat() with addr=0.
 *
 * Ugly calling convention alert:
 * Return value with the low bits set means error value,
 * ie
 *	अगर (ret & ~PAGE_MASK)
 *		error = ret;
 *
 * This function "knows" that -ENOMEM has the bits set.
 */
#अगर_अघोषित HAVE_ARCH_UNMAPPED_AREA
अचिन्हित दीर्घ
arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	काष्ठा vm_unmapped_area_info info;
	स्थिर अचिन्हित दीर्घ mmap_end = arch_get_mmap_end(addr);

	अगर (len > mmap_end - mmap_min_addr)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		वापस addr;

	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma_prev(mm, addr, &prev);
		अगर (mmap_end - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)) &&
		    (!prev || addr >= vm_end_gap(prev)))
			वापस addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_base;
	info.high_limit = mmap_end;
	info.align_mask = 0;
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण
#पूर्ण_अगर

/*
 * This mmap-allocator allocates new areas top-करोwn from below the
 * stack's low limit (the base):
 */
#अगर_अघोषित HAVE_ARCH_UNMAPPED_AREA_TOPDOWN
अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
			  अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma, *prev;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_unmapped_area_info info;
	स्थिर अचिन्हित दीर्घ mmap_end = arch_get_mmap_end(addr);

	/* requested length too big क्रम entire address space */
	अगर (len > mmap_end - mmap_min_addr)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		वापस addr;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma_prev(mm, addr, &prev);
		अगर (mmap_end - len >= addr && addr >= mmap_min_addr &&
				(!vma || addr + len <= vm_start_gap(vma)) &&
				(!prev || addr >= vm_end_gap(prev)))
			वापस addr;
	पूर्ण

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = arch_get_mmap_base(addr, mm->mmap_base);
	info.align_mask = 0;
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (offset_in_page(addr)) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = mmap_end;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ
get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ (*get_area)(काष्ठा file *, अचिन्हित दीर्घ,
				  अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

	अचिन्हित दीर्घ error = arch_mmap_check(addr, len, flags);
	अगर (error)
		वापस error;

	/* Careful about overflows.. */
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	get_area = current->mm->get_unmapped_area;
	अगर (file) अणु
		अगर (file->f_op->get_unmapped_area)
			get_area = file->f_op->get_unmapped_area;
	पूर्ण अन्यथा अगर (flags & MAP_SHARED) अणु
		/*
		 * mmap_region() will call shmem_zero_setup() to create a file,
		 * so use shmem's get_unmapped_area in हाल it can be huge.
		 * करो_mmap() will clear pgoff, so match alignment.
		 */
		pgoff = 0;
		get_area = shmem_get_unmapped_area;
	पूर्ण

	addr = get_area(file, addr, len, pgoff, flags);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	अगर (addr > TASK_SIZE - len)
		वापस -ENOMEM;
	अगर (offset_in_page(addr))
		वापस -EINVAL;

	error = security_mmap_addr(addr);
	वापस error ? error : addr;
पूर्ण

EXPORT_SYMBOL(get_unmapped_area);

/* Look up the first VMA which satisfies  addr < vm_end,  शून्य अगर none. */
काष्ठा vm_area_काष्ठा *find_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा rb_node *rb_node;
	काष्ठा vm_area_काष्ठा *vma;

	/* Check the cache first. */
	vma = vmacache_find(mm, addr);
	अगर (likely(vma))
		वापस vma;

	rb_node = mm->mm_rb.rb_node;

	जबतक (rb_node) अणु
		काष्ठा vm_area_काष्ठा *पंचांगp;

		पंचांगp = rb_entry(rb_node, काष्ठा vm_area_काष्ठा, vm_rb);

		अगर (पंचांगp->vm_end > addr) अणु
			vma = पंचांगp;
			अगर (पंचांगp->vm_start <= addr)
				अवरोध;
			rb_node = rb_node->rb_left;
		पूर्ण अन्यथा
			rb_node = rb_node->rb_right;
	पूर्ण

	अगर (vma)
		vmacache_update(addr, vma);
	वापस vma;
पूर्ण

EXPORT_SYMBOL(find_vma);

/*
 * Same as find_vma, but also वापस a poपूर्णांकer to the previous VMA in *pprev.
 */
काष्ठा vm_area_काष्ठा *
find_vma_prev(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			काष्ठा vm_area_काष्ठा **pprev)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	vma = find_vma(mm, addr);
	अगर (vma) अणु
		*pprev = vma->vm_prev;
	पूर्ण अन्यथा अणु
		काष्ठा rb_node *rb_node = rb_last(&mm->mm_rb);

		*pprev = rb_node ? rb_entry(rb_node, काष्ठा vm_area_काष्ठा, vm_rb) : शून्य;
	पूर्ण
	वापस vma;
पूर्ण

/*
 * Verअगरy that the stack growth is acceptable and
 * update accounting. This is shared with both the
 * grow-up and grow-करोwn हालs.
 */
अटल पूर्णांक acct_stack_growth(काष्ठा vm_area_काष्ठा *vma,
			     अचिन्हित दीर्घ size, अचिन्हित दीर्घ grow)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ new_start;

	/* address space limit tests */
	अगर (!may_expand_vm(mm, vma->vm_flags, grow))
		वापस -ENOMEM;

	/* Stack limit test */
	अगर (size > rlimit(RLIMIT_STACK))
		वापस -ENOMEM;

	/* mlock limit tests */
	अगर (vma->vm_flags & VM_LOCKED) अणु
		अचिन्हित दीर्घ locked;
		अचिन्हित दीर्घ limit;
		locked = mm->locked_vm + grow;
		limit = rlimit(RLIMIT_MEMLOCK);
		limit >>= PAGE_SHIFT;
		अगर (locked > limit && !capable(CAP_IPC_LOCK))
			वापस -ENOMEM;
	पूर्ण

	/* Check to ensure the stack will not grow पूर्णांकo a hugetlb-only region */
	new_start = (vma->vm_flags & VM_GROWSUP) ? vma->vm_start :
			vma->vm_end - size;
	अगर (is_hugepage_only_range(vma->vm_mm, new_start, size))
		वापस -EFAULT;

	/*
	 * Overcommit..  This must be the final test, as it will
	 * update security statistics.
	 */
	अगर (security_vm_enough_memory_mm(mm, grow))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

#अगर defined(CONFIG_STACK_GROWSUP) || defined(CONFIG_IA64)
/*
 * PA-RISC uses this क्रम its stack; IA64 क्रम its Register Backing Store.
 * vma is the last one with address > vma->vm_end.  Have to extend vma.
 */
पूर्णांक expand_upwards(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *next;
	अचिन्हित दीर्घ gap_addr;
	पूर्णांक error = 0;

	अगर (!(vma->vm_flags & VM_GROWSUP))
		वापस -EFAULT;

	/* Guard against exceeding limits of the address space. */
	address &= PAGE_MASK;
	अगर (address >= (TASK_SIZE & PAGE_MASK))
		वापस -ENOMEM;
	address += PAGE_SIZE;

	/* Enक्रमce stack_guard_gap */
	gap_addr = address + stack_guard_gap;

	/* Guard against overflow */
	अगर (gap_addr < address || gap_addr > TASK_SIZE)
		gap_addr = TASK_SIZE;

	next = vma->vm_next;
	अगर (next && next->vm_start < gap_addr && vma_is_accessible(next)) अणु
		अगर (!(next->vm_flags & VM_GROWSUP))
			वापस -ENOMEM;
		/* Check that both stack segments have the same anon_vma? */
	पूर्ण

	/* We must make sure the anon_vma is allocated. */
	अगर (unlikely(anon_vma_prepare(vma)))
		वापस -ENOMEM;

	/*
	 * vma->vm_start/vm_end cannot change under us because the caller
	 * is required to hold the mmap_lock in पढ़ो mode.  We need the
	 * anon_vma lock to serialize against concurrent expand_stacks.
	 */
	anon_vma_lock_ग_लिखो(vma->anon_vma);

	/* Somebody अन्यथा might have raced and expanded it alपढ़ोy */
	अगर (address > vma->vm_end) अणु
		अचिन्हित दीर्घ size, grow;

		size = address - vma->vm_start;
		grow = (address - vma->vm_end) >> PAGE_SHIFT;

		error = -ENOMEM;
		अगर (vma->vm_pgoff + (size >> PAGE_SHIFT) >= vma->vm_pgoff) अणु
			error = acct_stack_growth(vma, size, grow);
			अगर (!error) अणु
				/*
				 * vma_gap_update() करोesn't support concurrent
				 * updates, but we only hold a shared mmap_lock
				 * lock here, so we need to protect against
				 * concurrent vma expansions.
				 * anon_vma_lock_ग_लिखो() करोesn't help here, as
				 * we करोn't guarantee that all growable vmas
				 * in a mm share the same root anon vma.
				 * So, we reuse mm->page_table_lock to guard
				 * against concurrent vma expansions.
				 */
				spin_lock(&mm->page_table_lock);
				अगर (vma->vm_flags & VM_LOCKED)
					mm->locked_vm += grow;
				vm_stat_account(mm, vma->vm_flags, grow);
				anon_vma_पूर्णांकerval_tree_pre_update_vma(vma);
				vma->vm_end = address;
				anon_vma_पूर्णांकerval_tree_post_update_vma(vma);
				अगर (vma->vm_next)
					vma_gap_update(vma->vm_next);
				अन्यथा
					mm->highest_vm_end = vm_end_gap(vma);
				spin_unlock(&mm->page_table_lock);

				perf_event_mmap(vma);
			पूर्ण
		पूर्ण
	पूर्ण
	anon_vma_unlock_ग_लिखो(vma->anon_vma);
	khugepaged_enter_vma_merge(vma, vma->vm_flags);
	validate_mm(mm);
	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_STACK_GROWSUP || CONFIG_IA64 */

/*
 * vma is the first one with address < vma->vm_start.  Have to extend vma.
 */
पूर्णांक expand_करोwnwards(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ address)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *prev;
	पूर्णांक error = 0;

	address &= PAGE_MASK;
	अगर (address < mmap_min_addr)
		वापस -EPERM;

	/* Enक्रमce stack_guard_gap */
	prev = vma->vm_prev;
	/* Check that both stack segments have the same anon_vma? */
	अगर (prev && !(prev->vm_flags & VM_GROWSDOWN) &&
			vma_is_accessible(prev)) अणु
		अगर (address - prev->vm_end < stack_guard_gap)
			वापस -ENOMEM;
	पूर्ण

	/* We must make sure the anon_vma is allocated. */
	अगर (unlikely(anon_vma_prepare(vma)))
		वापस -ENOMEM;

	/*
	 * vma->vm_start/vm_end cannot change under us because the caller
	 * is required to hold the mmap_lock in पढ़ो mode.  We need the
	 * anon_vma lock to serialize against concurrent expand_stacks.
	 */
	anon_vma_lock_ग_लिखो(vma->anon_vma);

	/* Somebody अन्यथा might have raced and expanded it alपढ़ोy */
	अगर (address < vma->vm_start) अणु
		अचिन्हित दीर्घ size, grow;

		size = vma->vm_end - address;
		grow = (vma->vm_start - address) >> PAGE_SHIFT;

		error = -ENOMEM;
		अगर (grow <= vma->vm_pgoff) अणु
			error = acct_stack_growth(vma, size, grow);
			अगर (!error) अणु
				/*
				 * vma_gap_update() करोesn't support concurrent
				 * updates, but we only hold a shared mmap_lock
				 * lock here, so we need to protect against
				 * concurrent vma expansions.
				 * anon_vma_lock_ग_लिखो() करोesn't help here, as
				 * we करोn't guarantee that all growable vmas
				 * in a mm share the same root anon vma.
				 * So, we reuse mm->page_table_lock to guard
				 * against concurrent vma expansions.
				 */
				spin_lock(&mm->page_table_lock);
				अगर (vma->vm_flags & VM_LOCKED)
					mm->locked_vm += grow;
				vm_stat_account(mm, vma->vm_flags, grow);
				anon_vma_पूर्णांकerval_tree_pre_update_vma(vma);
				vma->vm_start = address;
				vma->vm_pgoff -= grow;
				anon_vma_पूर्णांकerval_tree_post_update_vma(vma);
				vma_gap_update(vma);
				spin_unlock(&mm->page_table_lock);

				perf_event_mmap(vma);
			पूर्ण
		पूर्ण
	पूर्ण
	anon_vma_unlock_ग_लिखो(vma->anon_vma);
	khugepaged_enter_vma_merge(vma, vma->vm_flags);
	validate_mm(mm);
	वापस error;
पूर्ण

/* enक्रमced gap between the expanding stack and other mappings. */
अचिन्हित दीर्घ stack_guard_gap = 256UL<<PAGE_SHIFT;

अटल पूर्णांक __init cmdline_parse_stack_guard_gap(अक्षर *p)
अणु
	अचिन्हित दीर्घ val;
	अक्षर *endptr;

	val = simple_म_से_अदीर्घ(p, &endptr, 10);
	अगर (!*endptr)
		stack_guard_gap = val << PAGE_SHIFT;

	वापस 0;
पूर्ण
__setup("stack_guard_gap=", cmdline_parse_stack_guard_gap);

#अगर_घोषित CONFIG_STACK_GROWSUP
पूर्णांक expand_stack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	वापस expand_upwards(vma, address);
पूर्ण

काष्ठा vm_area_काष्ठा *
find_extend_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma, *prev;

	addr &= PAGE_MASK;
	vma = find_vma_prev(mm, addr, &prev);
	अगर (vma && (vma->vm_start <= addr))
		वापस vma;
	/* करोn't alter vm_end अगर the coredump is running */
	अगर (!prev || expand_stack(prev, addr))
		वापस शून्य;
	अगर (prev->vm_flags & VM_LOCKED)
		populate_vma_page_range(prev, addr, prev->vm_end, शून्य);
	वापस prev;
पूर्ण
#अन्यथा
पूर्णांक expand_stack(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address)
अणु
	वापस expand_करोwnwards(vma, address);
पूर्ण

काष्ठा vm_area_काष्ठा *
find_extend_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ start;

	addr &= PAGE_MASK;
	vma = find_vma(mm, addr);
	अगर (!vma)
		वापस शून्य;
	अगर (vma->vm_start <= addr)
		वापस vma;
	अगर (!(vma->vm_flags & VM_GROWSDOWN))
		वापस शून्य;
	start = vma->vm_start;
	अगर (expand_stack(vma, addr))
		वापस शून्य;
	अगर (vma->vm_flags & VM_LOCKED)
		populate_vma_page_range(vma, addr, start, शून्य);
	वापस vma;
पूर्ण
#पूर्ण_अगर

EXPORT_SYMBOL_GPL(find_extend_vma);

/*
 * Ok - we have the memory areas we should मुक्त on the vma list,
 * so release them, and करो the vma updates.
 *
 * Called with the mm semaphore held.
 */
अटल व्योम हटाओ_vma_list(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ nr_accounted = 0;

	/* Update high watermark beक्रमe we lower total_vm */
	update_hiwater_vm(mm);
	करो अणु
		दीर्घ nrpages = vma_pages(vma);

		अगर (vma->vm_flags & VM_ACCOUNT)
			nr_accounted += nrpages;
		vm_stat_account(mm, vma->vm_flags, -nrpages);
		vma = हटाओ_vma(vma);
	पूर्ण जबतक (vma);
	vm_unacct_memory(nr_accounted);
	validate_mm(mm);
पूर्ण

/*
 * Get rid of page table inक्रमmation in the indicated region.
 *
 * Called with the mm semaphore held.
 */
अटल व्योम unmap_region(काष्ठा mm_काष्ठा *mm,
		काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_area_काष्ठा *prev,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा vm_area_काष्ठा *next = vma_next(mm, prev);
	काष्ठा mmu_gather tlb;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm);
	update_hiwater_rss(mm);
	unmap_vmas(&tlb, vma, start, end);
	मुक्त_pgtables(&tlb, vma, prev ? prev->vm_end : FIRST_USER_ADDRESS,
				 next ? next->vm_start : USER_PGTABLES_CEILING);
	tlb_finish_mmu(&tlb);
पूर्ण

/*
 * Create a list of vma's touched by the unmap, removing them from the mm's
 * vma list as we go..
 */
अटल bool
detach_vmas_to_be_unmapped(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
	काष्ठा vm_area_काष्ठा *prev, अचिन्हित दीर्घ end)
अणु
	काष्ठा vm_area_काष्ठा **insertion_poपूर्णांक;
	काष्ठा vm_area_काष्ठा *tail_vma = शून्य;

	insertion_poपूर्णांक = (prev ? &prev->vm_next : &mm->mmap);
	vma->vm_prev = शून्य;
	करो अणु
		vma_rb_erase(vma, &mm->mm_rb);
		mm->map_count--;
		tail_vma = vma;
		vma = vma->vm_next;
	पूर्ण जबतक (vma && vma->vm_start < end);
	*insertion_poपूर्णांक = vma;
	अगर (vma) अणु
		vma->vm_prev = prev;
		vma_gap_update(vma);
	पूर्ण अन्यथा
		mm->highest_vm_end = prev ? vm_end_gap(prev) : 0;
	tail_vma->vm_next = शून्य;

	/* Kill the cache */
	vmacache_invalidate(mm);

	/*
	 * Do not करोwngrade mmap_lock अगर we are next to VM_GROWSDOWN or
	 * VM_GROWSUP VMA. Such VMAs can change their size under
	 * करोwn_पढ़ो(mmap_lock) and collide with the VMA we are about to unmap.
	 */
	अगर (vma && (vma->vm_flags & VM_GROWSDOWN))
		वापस false;
	अगर (prev && (prev->vm_flags & VM_GROWSUP))
		वापस false;
	वापस true;
पूर्ण

/*
 * __split_vma() bypasses sysctl_max_map_count checking.  We use this where it
 * has alपढ़ोy been checked or करोesn't make sense to fail.
 */
पूर्णांक __split_vma(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, पूर्णांक new_below)
अणु
	काष्ठा vm_area_काष्ठा *new;
	पूर्णांक err;

	अगर (vma->vm_ops && vma->vm_ops->may_split) अणु
		err = vma->vm_ops->may_split(vma, addr);
		अगर (err)
			वापस err;
	पूर्ण

	new = vm_area_dup(vma);
	अगर (!new)
		वापस -ENOMEM;

	अगर (new_below)
		new->vm_end = addr;
	अन्यथा अणु
		new->vm_start = addr;
		new->vm_pgoff += ((addr - vma->vm_start) >> PAGE_SHIFT);
	पूर्ण

	err = vma_dup_policy(vma, new);
	अगर (err)
		जाओ out_मुक्त_vma;

	err = anon_vma_clone(new, vma);
	अगर (err)
		जाओ out_मुक्त_mpol;

	अगर (new->vm_file)
		get_file(new->vm_file);

	अगर (new->vm_ops && new->vm_ops->खोलो)
		new->vm_ops->खोलो(new);

	अगर (new_below)
		err = vma_adjust(vma, addr, vma->vm_end, vma->vm_pgoff +
			((addr - new->vm_start) >> PAGE_SHIFT), new);
	अन्यथा
		err = vma_adjust(vma, vma->vm_start, addr, vma->vm_pgoff, new);

	/* Success. */
	अगर (!err)
		वापस 0;

	/* Clean everything up अगर vma_adjust failed. */
	अगर (new->vm_ops && new->vm_ops->बंद)
		new->vm_ops->बंद(new);
	अगर (new->vm_file)
		fput(new->vm_file);
	unlink_anon_vmas(new);
 out_मुक्त_mpol:
	mpol_put(vma_policy(new));
 out_मुक्त_vma:
	vm_area_मुक्त(new);
	वापस err;
पूर्ण

/*
 * Split a vma पूर्णांकo two pieces at address 'addr', a new vma is allocated
 * either क्रम the first part or the tail.
 */
पूर्णांक split_vma(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
	      अचिन्हित दीर्घ addr, पूर्णांक new_below)
अणु
	अगर (mm->map_count >= sysctl_max_map_count)
		वापस -ENOMEM;

	वापस __split_vma(mm, vma, addr, new_below);
पूर्ण

/* Munmap is split पूर्णांकo 2 मुख्य parts -- this part which finds
 * what needs करोing, and the areas themselves, which करो the
 * work.  This now handles partial unmappings.
 * Jeremy Fitzhardinge <jeremy@goop.org>
 */
पूर्णांक __करो_munmap(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, माप_प्रकार len,
		काष्ठा list_head *uf, bool करोwngrade)
अणु
	अचिन्हित दीर्घ end;
	काष्ठा vm_area_काष्ठा *vma, *prev, *last;

	अगर ((offset_in_page(start)) || start > TASK_SIZE || len > TASK_SIZE-start)
		वापस -EINVAL;

	len = PAGE_ALIGN(len);
	end = start + len;
	अगर (len == 0)
		वापस -EINVAL;

	/*
	 * arch_unmap() might करो unmaps itself.  It must be called
	 * and finish any rbtree manipulation beक्रमe this code
	 * runs and also starts to manipulate the rbtree.
	 */
	arch_unmap(mm, start, end);

	/* Find the first overlapping VMA */
	vma = find_vma(mm, start);
	अगर (!vma)
		वापस 0;
	prev = vma->vm_prev;
	/* we have  start < vma->vm_end  */

	/* अगर it करोesn't overlap, we have nothing.. */
	अगर (vma->vm_start >= end)
		वापस 0;

	/*
	 * If we need to split any vma, करो it now to save pain later.
	 *
	 * Note: mremap's move_vma VM_ACCOUNT handling assumes a partially
	 * unmapped vm_area_काष्ठा will reमुख्य in use: so lower split_vma
	 * places पंचांगp vma above, and higher split_vma places पंचांगp vma below.
	 */
	अगर (start > vma->vm_start) अणु
		पूर्णांक error;

		/*
		 * Make sure that map_count on वापस from munmap() will
		 * not exceed its limit; but let map_count go just above
		 * its limit temporarily, to help मुक्त resources as expected.
		 */
		अगर (end < vma->vm_end && mm->map_count >= sysctl_max_map_count)
			वापस -ENOMEM;

		error = __split_vma(mm, vma, start, 0);
		अगर (error)
			वापस error;
		prev = vma;
	पूर्ण

	/* Does it split the last one? */
	last = find_vma(mm, end);
	अगर (last && end > last->vm_start) अणु
		पूर्णांक error = __split_vma(mm, last, end, 1);
		अगर (error)
			वापस error;
	पूर्ण
	vma = vma_next(mm, prev);

	अगर (unlikely(uf)) अणु
		/*
		 * If userfaultfd_unmap_prep वापसs an error the vmas
		 * will reमुख्य split, but userland will get a
		 * highly unexpected error anyway. This is no
		 * dअगरferent than the हाल where the first of the two
		 * __split_vma fails, but we करोn't unकरो the first
		 * split, despite we could. This is unlikely enough
		 * failure that it's not worth optimizing it क्रम.
		 */
		पूर्णांक error = userfaultfd_unmap_prep(vma, start, end, uf);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * unlock any mlock()ed ranges beक्रमe detaching vmas
	 */
	अगर (mm->locked_vm) अणु
		काष्ठा vm_area_काष्ठा *पंचांगp = vma;
		जबतक (पंचांगp && पंचांगp->vm_start < end) अणु
			अगर (पंचांगp->vm_flags & VM_LOCKED) अणु
				mm->locked_vm -= vma_pages(पंचांगp);
				munlock_vma_pages_all(पंचांगp);
			पूर्ण

			पंचांगp = पंचांगp->vm_next;
		पूर्ण
	पूर्ण

	/* Detach vmas from rbtree */
	अगर (!detach_vmas_to_be_unmapped(mm, vma, prev, end))
		करोwngrade = false;

	अगर (करोwngrade)
		mmap_ग_लिखो_करोwngrade(mm);

	unmap_region(mm, vma, prev, start, end);

	/* Fix up all other VM inक्रमmation */
	हटाओ_vma_list(mm, vma);

	वापस करोwngrade ? 1 : 0;
पूर्ण

पूर्णांक करो_munmap(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, माप_प्रकार len,
	      काष्ठा list_head *uf)
अणु
	वापस __करो_munmap(mm, start, len, uf, false);
पूर्ण

अटल पूर्णांक __vm_munmap(अचिन्हित दीर्घ start, माप_प्रकार len, bool करोwngrade)
अणु
	पूर्णांक ret;
	काष्ठा mm_काष्ठा *mm = current->mm;
	LIST_HEAD(uf);

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	ret = __करो_munmap(mm, start, len, &uf, करोwngrade);
	/*
	 * Returning 1 indicates mmap_lock is करोwngraded.
	 * But 1 is not legal वापस value of vm_munmap() and munmap(), reset
	 * it to 0 beक्रमe वापस.
	 */
	अगर (ret == 1) अणु
		mmap_पढ़ो_unlock(mm);
		ret = 0;
	पूर्ण अन्यथा
		mmap_ग_लिखो_unlock(mm);

	userfaultfd_unmap_complete(mm, &uf);
	वापस ret;
पूर्ण

पूर्णांक vm_munmap(अचिन्हित दीर्घ start, माप_प्रकार len)
अणु
	वापस __vm_munmap(start, len, false);
पूर्ण
EXPORT_SYMBOL(vm_munmap);

SYSCALL_DEFINE2(munmap, अचिन्हित दीर्घ, addr, माप_प्रकार, len)
अणु
	addr = untagged_addr(addr);
	profile_munmap(addr);
	वापस __vm_munmap(addr, len, true);
पूर्ण


/*
 * Emulation of deprecated remap_file_pages() syscall.
 */
SYSCALL_DEFINE5(remap_file_pages, अचिन्हित दीर्घ, start, अचिन्हित दीर्घ, size,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, pgoff, अचिन्हित दीर्घ, flags)
अणु

	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ populate = 0;
	अचिन्हित दीर्घ ret = -EINVAL;
	काष्ठा file *file;

	pr_warn_once("%s (%d) uses deprecated remap_file_pages() syscall. See Documentation/vm/remap_file_pages.rst.\n",
		     current->comm, current->pid);

	अगर (prot)
		वापस ret;
	start = start & PAGE_MASK;
	size = size & PAGE_MASK;

	अगर (start + size <= start)
		वापस ret;

	/* Does pgoff wrap? */
	अगर (pgoff + (size >> PAGE_SHIFT) < pgoff)
		वापस ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	vma = find_vma(mm, start);

	अगर (!vma || !(vma->vm_flags & VM_SHARED))
		जाओ out;

	अगर (start < vma->vm_start)
		जाओ out;

	अगर (start + size > vma->vm_end) अणु
		काष्ठा vm_area_काष्ठा *next;

		क्रम (next = vma->vm_next; next; next = next->vm_next) अणु
			/* hole between vmas ? */
			अगर (next->vm_start != next->vm_prev->vm_end)
				जाओ out;

			अगर (next->vm_file != vma->vm_file)
				जाओ out;

			अगर (next->vm_flags != vma->vm_flags)
				जाओ out;

			अगर (start + size <= next->vm_end)
				अवरोध;
		पूर्ण

		अगर (!next)
			जाओ out;
	पूर्ण

	prot |= vma->vm_flags & VM_READ ? PROT_READ : 0;
	prot |= vma->vm_flags & VM_WRITE ? PROT_WRITE : 0;
	prot |= vma->vm_flags & VM_EXEC ? PROT_EXEC : 0;

	flags &= MAP_NONBLOCK;
	flags |= MAP_SHARED | MAP_FIXED | MAP_POPULATE;
	अगर (vma->vm_flags & VM_LOCKED)
		flags |= MAP_LOCKED;

	file = get_file(vma->vm_file);
	ret = करो_mmap(vma->vm_file, start, size,
			prot, flags, pgoff, &populate, शून्य);
	fput(file);
out:
	mmap_ग_लिखो_unlock(mm);
	अगर (populate)
		mm_populate(ret, populate);
	अगर (!IS_ERR_VALUE(ret))
		ret = 0;
	वापस ret;
पूर्ण

/*
 *  this is really a simplअगरied "do_mmap".  it only handles
 *  anonymous maps.  eventually we may be able to करो some
 *  brk-specअगरic accounting here.
 */
अटल पूर्णांक करो_brk_flags(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ flags, काष्ठा list_head *uf)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	काष्ठा rb_node **rb_link, *rb_parent;
	pgoff_t pgoff = addr >> PAGE_SHIFT;
	पूर्णांक error;
	अचिन्हित दीर्घ mapped_addr;

	/* Until we need other flags, refuse anything except VM_EXEC. */
	अगर ((flags & (~VM_EXEC)) != 0)
		वापस -EINVAL;
	flags |= VM_DATA_DEFAULT_FLAGS | VM_ACCOUNT | mm->def_flags;

	mapped_addr = get_unmapped_area(शून्य, addr, len, 0, MAP_FIXED);
	अगर (IS_ERR_VALUE(mapped_addr))
		वापस mapped_addr;

	error = mlock_future_check(mm, mm->def_flags, len);
	अगर (error)
		वापस error;

	/* Clear old maps, set up prev, rb_link, rb_parent, and uf */
	अगर (munmap_vma_range(mm, addr, len, &prev, &rb_link, &rb_parent, uf))
		वापस -ENOMEM;

	/* Check against address space limits *after* clearing old maps... */
	अगर (!may_expand_vm(mm, flags, len >> PAGE_SHIFT))
		वापस -ENOMEM;

	अगर (mm->map_count > sysctl_max_map_count)
		वापस -ENOMEM;

	अगर (security_vm_enough_memory_mm(mm, len >> PAGE_SHIFT))
		वापस -ENOMEM;

	/* Can we just expand an old निजी anonymous mapping? */
	vma = vma_merge(mm, prev, addr, addr + len, flags,
			शून्य, शून्य, pgoff, शून्य, शून्य_VM_UFFD_CTX);
	अगर (vma)
		जाओ out;

	/*
	 * create a vma काष्ठा क्रम an anonymous mapping
	 */
	vma = vm_area_alloc(mm);
	अगर (!vma) अणु
		vm_unacct_memory(len >> PAGE_SHIFT);
		वापस -ENOMEM;
	पूर्ण

	vma_set_anonymous(vma);
	vma->vm_start = addr;
	vma->vm_end = addr + len;
	vma->vm_pgoff = pgoff;
	vma->vm_flags = flags;
	vma->vm_page_prot = vm_get_page_prot(flags);
	vma_link(mm, vma, prev, rb_link, rb_parent);
out:
	perf_event_mmap(vma);
	mm->total_vm += len >> PAGE_SHIFT;
	mm->data_vm += len >> PAGE_SHIFT;
	अगर (flags & VM_LOCKED)
		mm->locked_vm += (len >> PAGE_SHIFT);
	vma->vm_flags |= VM_SOFTसूचीTY;
	वापस 0;
पूर्ण

पूर्णांक vm_brk_flags(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ request, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ len;
	पूर्णांक ret;
	bool populate;
	LIST_HEAD(uf);

	len = PAGE_ALIGN(request);
	अगर (len < request)
		वापस -ENOMEM;
	अगर (!len)
		वापस 0;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	ret = करो_brk_flags(addr, len, flags, &uf);
	populate = ((mm->def_flags & VM_LOCKED) != 0);
	mmap_ग_लिखो_unlock(mm);
	userfaultfd_unmap_complete(mm, &uf);
	अगर (populate && !ret)
		mm_populate(addr, len);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vm_brk_flags);

पूर्णांक vm_brk(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस vm_brk_flags(addr, len, 0);
पूर्ण
EXPORT_SYMBOL(vm_brk);

/* Release all mmaps. */
व्योम निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_gather tlb;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ nr_accounted = 0;

	/* mm's last user has gone, and its about to be pulled करोwn */
	mmu_notअगरier_release(mm);

	अगर (unlikely(mm_is_oom_victim(mm))) अणु
		/*
		 * Manually reap the mm to मुक्त as much memory as possible.
		 * Then, as the oom reaper करोes, set MMF_OOM_SKIP to disregard
		 * this mm from further consideration.  Taking mm->mmap_lock क्रम
		 * ग_लिखो after setting MMF_OOM_SKIP will guarantee that the oom
		 * reaper will not run on this mm again after mmap_lock is
		 * dropped.
		 *
		 * Nothing can be holding mm->mmap_lock here and the above call
		 * to mmu_notअगरier_release(mm) ensures mmu notअगरier callbacks in
		 * __oom_reap_task_mm() will not block.
		 *
		 * This needs to be करोne beक्रमe calling munlock_vma_pages_all(),
		 * which clears VM_LOCKED, otherwise the oom reaper cannot
		 * reliably test it.
		 */
		(व्योम)__oom_reap_task_mm(mm);

		set_bit(MMF_OOM_SKIP, &mm->flags);
		mmap_ग_लिखो_lock(mm);
		mmap_ग_लिखो_unlock(mm);
	पूर्ण

	अगर (mm->locked_vm) अणु
		vma = mm->mmap;
		जबतक (vma) अणु
			अगर (vma->vm_flags & VM_LOCKED)
				munlock_vma_pages_all(vma);
			vma = vma->vm_next;
		पूर्ण
	पूर्ण

	arch_निकास_mmap(mm);

	vma = mm->mmap;
	अगर (!vma)	/* Can happen अगर dup_mmap() received an OOM */
		वापस;

	lru_add_drain();
	flush_cache_mm(mm);
	tlb_gather_mmu_fullmm(&tlb, mm);
	/* update_hiwater_rss(mm) here? but nobody should be looking */
	/* Use -1 here to ensure all VMAs in the mm are unmapped */
	unmap_vmas(&tlb, vma, 0, -1);
	मुक्त_pgtables(&tlb, vma, FIRST_USER_ADDRESS, USER_PGTABLES_CEILING);
	tlb_finish_mmu(&tlb);

	/*
	 * Walk the list again, actually closing and मुक्तing it,
	 * with preemption enabled, without holding any MM locks.
	 */
	जबतक (vma) अणु
		अगर (vma->vm_flags & VM_ACCOUNT)
			nr_accounted += vma_pages(vma);
		vma = हटाओ_vma(vma);
		cond_resched();
	पूर्ण
	vm_unacct_memory(nr_accounted);
पूर्ण

/* Insert vm काष्ठाure पूर्णांकo process list sorted by address
 * and पूर्णांकo the inode's i_mmap tree.  If vm_file is non-शून्य
 * then i_mmap_rwsem is taken here.
 */
पूर्णांक insert_vm_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vm_area_काष्ठा *prev;
	काष्ठा rb_node **rb_link, *rb_parent;

	अगर (find_vma_links(mm, vma->vm_start, vma->vm_end,
			   &prev, &rb_link, &rb_parent))
		वापस -ENOMEM;
	अगर ((vma->vm_flags & VM_ACCOUNT) &&
	     security_vm_enough_memory_mm(mm, vma_pages(vma)))
		वापस -ENOMEM;

	/*
	 * The vm_pgoff of a purely anonymous vma should be irrelevant
	 * until its first ग_लिखो fault, when page's anon_vma and index
	 * are set.  But now set the vm_pgoff it will almost certainly
	 * end up with (unless mremap moves it अन्यथाwhere beक्रमe that
	 * first wfault), so /proc/pid/maps tells a consistent story.
	 *
	 * By setting it to reflect the भव start address of the
	 * vma, merges and splits can happen in a seamless way, just
	 * using the existing file pgoff checks and manipulations.
	 * Similarly in करो_mmap and in करो_brk_flags.
	 */
	अगर (vma_is_anonymous(vma)) अणु
		BUG_ON(vma->anon_vma);
		vma->vm_pgoff = vma->vm_start >> PAGE_SHIFT;
	पूर्ण

	vma_link(mm, vma, prev, rb_link, rb_parent);
	वापस 0;
पूर्ण

/*
 * Copy the vma काष्ठाure to a new location in the same mm,
 * prior to moving page table entries, to effect an mremap move.
 */
काष्ठा vm_area_काष्ठा *copy_vma(काष्ठा vm_area_काष्ठा **vmap,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, pgoff_t pgoff,
	bool *need_rmap_locks)
अणु
	काष्ठा vm_area_काष्ठा *vma = *vmap;
	अचिन्हित दीर्घ vma_start = vma->vm_start;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *new_vma, *prev;
	काष्ठा rb_node **rb_link, *rb_parent;
	bool faulted_in_anon_vma = true;

	/*
	 * If anonymous vma has not yet been faulted, update new pgoff
	 * to match new location, to increase its chance of merging.
	 */
	अगर (unlikely(vma_is_anonymous(vma) && !vma->anon_vma)) अणु
		pgoff = addr >> PAGE_SHIFT;
		faulted_in_anon_vma = false;
	पूर्ण

	अगर (find_vma_links(mm, addr, addr + len, &prev, &rb_link, &rb_parent))
		वापस शून्य;	/* should never get here */
	new_vma = vma_merge(mm, prev, addr, addr + len, vma->vm_flags,
			    vma->anon_vma, vma->vm_file, pgoff, vma_policy(vma),
			    vma->vm_userfaultfd_ctx);
	अगर (new_vma) अणु
		/*
		 * Source vma may have been merged पूर्णांकo new_vma
		 */
		अगर (unlikely(vma_start >= new_vma->vm_start &&
			     vma_start < new_vma->vm_end)) अणु
			/*
			 * The only way we can get a vma_merge with
			 * self during an mremap is अगर the vma hasn't
			 * been faulted in yet and we were allowed to
			 * reset the dst vma->vm_pgoff to the
			 * destination address of the mremap to allow
			 * the merge to happen. mremap must change the
			 * vm_pgoff linearity between src and dst vmas
			 * (in turn preventing a vma_merge) to be
			 * safe. It is only safe to keep the vm_pgoff
			 * linear अगर there are no pages mapped yet.
			 */
			VM_BUG_ON_VMA(faulted_in_anon_vma, new_vma);
			*vmap = vma = new_vma;
		पूर्ण
		*need_rmap_locks = (new_vma->vm_pgoff <= vma->vm_pgoff);
	पूर्ण अन्यथा अणु
		new_vma = vm_area_dup(vma);
		अगर (!new_vma)
			जाओ out;
		new_vma->vm_start = addr;
		new_vma->vm_end = addr + len;
		new_vma->vm_pgoff = pgoff;
		अगर (vma_dup_policy(vma, new_vma))
			जाओ out_मुक्त_vma;
		अगर (anon_vma_clone(new_vma, vma))
			जाओ out_मुक्त_mempol;
		अगर (new_vma->vm_file)
			get_file(new_vma->vm_file);
		अगर (new_vma->vm_ops && new_vma->vm_ops->खोलो)
			new_vma->vm_ops->खोलो(new_vma);
		vma_link(mm, new_vma, prev, rb_link, rb_parent);
		*need_rmap_locks = false;
	पूर्ण
	वापस new_vma;

out_मुक्त_mempol:
	mpol_put(vma_policy(new_vma));
out_मुक्त_vma:
	vm_area_मुक्त(new_vma);
out:
	वापस शून्य;
पूर्ण

/*
 * Return true अगर the calling process may expand its vm space by the passed
 * number of pages
 */
bool may_expand_vm(काष्ठा mm_काष्ठा *mm, vm_flags_t flags, अचिन्हित दीर्घ npages)
अणु
	अगर (mm->total_vm + npages > rlimit(RLIMIT_AS) >> PAGE_SHIFT)
		वापस false;

	अगर (is_data_mapping(flags) &&
	    mm->data_vm + npages > rlimit(RLIMIT_DATA) >> PAGE_SHIFT) अणु
		/* Workaround क्रम Valgrind */
		अगर (rlimit(RLIMIT_DATA) == 0 &&
		    mm->data_vm + npages <= rlimit_max(RLIMIT_DATA) >> PAGE_SHIFT)
			वापस true;

		pr_warn_once("%s (%d): VmData %lu exceed data ulimit %lu. Update limits%s.\n",
			     current->comm, current->pid,
			     (mm->data_vm + npages) << PAGE_SHIFT,
			     rlimit(RLIMIT_DATA),
			     ignore_rlimit_data ? "" : " or use boot option ignore_rlimit_data");

		अगर (!ignore_rlimit_data)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम vm_stat_account(काष्ठा mm_काष्ठा *mm, vm_flags_t flags, दीर्घ npages)
अणु
	mm->total_vm += npages;

	अगर (is_exec_mapping(flags))
		mm->exec_vm += npages;
	अन्यथा अगर (is_stack_mapping(flags))
		mm->stack_vm += npages;
	अन्यथा अगर (is_data_mapping(flags))
		mm->data_vm += npages;
पूर्ण

अटल vm_fault_t special_mapping_fault(काष्ठा vm_fault *vmf);

/*
 * Having a बंद hook prevents vma merging regardless of flags.
 */
अटल व्योम special_mapping_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण

अटल स्थिर अक्षर *special_mapping_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस ((काष्ठा vm_special_mapping *)vma->vm_निजी_data)->name;
पूर्ण

अटल पूर्णांक special_mapping_mremap(काष्ठा vm_area_काष्ठा *new_vma)
अणु
	काष्ठा vm_special_mapping *sm = new_vma->vm_निजी_data;

	अगर (WARN_ON_ONCE(current->mm != new_vma->vm_mm))
		वापस -EFAULT;

	अगर (sm->mremap)
		वापस sm->mremap(sm, new_vma);

	वापस 0;
पूर्ण

अटल पूर्णांक special_mapping_split(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	/*
	 * Forbid splitting special mappings - kernel has expectations over
	 * the number of pages in mapping. Together with VM_DONTEXPAND
	 * the size of vma should stay the same over the special mapping's
	 * lअगरeसमय.
	 */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा special_mapping_vmops = अणु
	.बंद = special_mapping_बंद,
	.fault = special_mapping_fault,
	.mremap = special_mapping_mremap,
	.name = special_mapping_name,
	/* vDSO code relies that VVAR can't be accessed remotely */
	.access = शून्य,
	.may_split = special_mapping_split,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा legacy_special_mapping_vmops = अणु
	.बंद = special_mapping_बंद,
	.fault = special_mapping_fault,
पूर्ण;

अटल vm_fault_t special_mapping_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	pgoff_t pgoff;
	काष्ठा page **pages;

	अगर (vma->vm_ops == &legacy_special_mapping_vmops) अणु
		pages = vma->vm_निजी_data;
	पूर्ण अन्यथा अणु
		काष्ठा vm_special_mapping *sm = vma->vm_निजी_data;

		अगर (sm->fault)
			वापस sm->fault(sm, vmf->vma, vmf);

		pages = sm->pages;
	पूर्ण

	क्रम (pgoff = vmf->pgoff; pgoff && *pages; ++pages)
		pgoff--;

	अगर (*pages) अणु
		काष्ठा page *page = *pages;
		get_page(page);
		vmf->page = page;
		वापस 0;
	पूर्ण

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल काष्ठा vm_area_काष्ठा *__install_special_mapping(
	काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ vm_flags, व्योम *priv,
	स्थिर काष्ठा vm_operations_काष्ठा *ops)
अणु
	पूर्णांक ret;
	काष्ठा vm_area_काष्ठा *vma;

	vma = vm_area_alloc(mm);
	अगर (unlikely(vma == शून्य))
		वापस ERR_PTR(-ENOMEM);

	vma->vm_start = addr;
	vma->vm_end = addr + len;

	vma->vm_flags = vm_flags | mm->def_flags | VM_DONTEXPAND | VM_SOFTसूचीTY;
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);

	vma->vm_ops = ops;
	vma->vm_निजी_data = priv;

	ret = insert_vm_काष्ठा(mm, vma);
	अगर (ret)
		जाओ out;

	vm_stat_account(mm, vma->vm_flags, len >> PAGE_SHIFT);

	perf_event_mmap(vma);

	वापस vma;

out:
	vm_area_मुक्त(vma);
	वापस ERR_PTR(ret);
पूर्ण

bool vma_is_special_mapping(स्थिर काष्ठा vm_area_काष्ठा *vma,
	स्थिर काष्ठा vm_special_mapping *sm)
अणु
	वापस vma->vm_निजी_data == sm &&
		(vma->vm_ops == &special_mapping_vmops ||
		 vma->vm_ops == &legacy_special_mapping_vmops);
पूर्ण

/*
 * Called with mm->mmap_lock held क्रम writing.
 * Insert a new vma covering the given region, with the given flags.
 * Its pages are supplied by the given array of काष्ठा page *.
 * The array can be लघुer than len >> PAGE_SHIFT अगर it's null-terminated.
 * The region past the last page supplied will always produce SIGBUS.
 * The array poपूर्णांकer and the pages it poपूर्णांकs to are assumed to stay alive
 * क्रम as दीर्घ as this mapping might exist.
 */
काष्ठा vm_area_काष्ठा *_install_special_mapping(
	काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ vm_flags, स्थिर काष्ठा vm_special_mapping *spec)
अणु
	वापस __install_special_mapping(mm, addr, len, vm_flags, (व्योम *)spec,
					&special_mapping_vmops);
पूर्ण

पूर्णांक install_special_mapping(काष्ठा mm_काष्ठा *mm,
			    अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			    अचिन्हित दीर्घ vm_flags, काष्ठा page **pages)
अणु
	काष्ठा vm_area_काष्ठा *vma = __install_special_mapping(
		mm, addr, len, vm_flags, (व्योम *)pages,
		&legacy_special_mapping_vmops);

	वापस PTR_ERR_OR_ZERO(vma);
पूर्ण

अटल DEFINE_MUTEX(mm_all_locks_mutex);

अटल व्योम vm_lock_anon_vma(काष्ठा mm_काष्ठा *mm, काष्ठा anon_vma *anon_vma)
अणु
	अगर (!test_bit(0, (अचिन्हित दीर्घ *) &anon_vma->root->rb_root.rb_root.rb_node)) अणु
		/*
		 * The LSB of head.next can't change from under us
		 * because we hold the mm_all_locks_mutex.
		 */
		करोwn_ग_लिखो_nest_lock(&anon_vma->root->rwsem, &mm->mmap_lock);
		/*
		 * We can safely modअगरy head.next after taking the
		 * anon_vma->root->rwsem. If some other vma in this mm shares
		 * the same anon_vma we won't take it again.
		 *
		 * No need of atomic inकाष्ठाions here, head.next
		 * can't change from under us thanks to the
		 * anon_vma->root->rwsem.
		 */
		अगर (__test_and_set_bit(0, (अचिन्हित दीर्घ *)
				       &anon_vma->root->rb_root.rb_root.rb_node))
			BUG();
	पूर्ण
पूर्ण

अटल व्योम vm_lock_mapping(काष्ठा mm_काष्ठा *mm, काष्ठा address_space *mapping)
अणु
	अगर (!test_bit(AS_MM_ALL_LOCKS, &mapping->flags)) अणु
		/*
		 * AS_MM_ALL_LOCKS can't change from under us because
		 * we hold the mm_all_locks_mutex.
		 *
		 * Operations on ->flags have to be atomic because
		 * even अगर AS_MM_ALL_LOCKS is stable thanks to the
		 * mm_all_locks_mutex, there may be other cpus
		 * changing other bitflags in parallel to us.
		 */
		अगर (test_and_set_bit(AS_MM_ALL_LOCKS, &mapping->flags))
			BUG();
		करोwn_ग_लिखो_nest_lock(&mapping->i_mmap_rwsem, &mm->mmap_lock);
	पूर्ण
पूर्ण

/*
 * This operation locks against the VM क्रम all pte/vma/mm related
 * operations that could ever happen on a certain mm. This includes
 * vmtruncate, try_to_unmap, and all page faults.
 *
 * The caller must take the mmap_lock in ग_लिखो mode beक्रमe calling
 * mm_take_all_locks(). The caller isn't allowed to release the
 * mmap_lock until mm_drop_all_locks() वापसs.
 *
 * mmap_lock in ग_लिखो mode is required in order to block all operations
 * that could modअगरy pagetables and मुक्त pages without need of
 * altering the vma layout. It's also needed in ग_लिखो mode to aव्योम new
 * anon_vmas to be associated with existing vmas.
 *
 * A single task can't take more than one mm_take_all_locks() in a row
 * or it would deadlock.
 *
 * The LSB in anon_vma->rb_root.rb_node and the AS_MM_ALL_LOCKS bitflag in
 * mapping->flags aव्योम to take the same lock twice, अगर more than one
 * vma in this mm is backed by the same anon_vma or address_space.
 *
 * We take locks in following order, accordingly to comment at beginning
 * of mm/rmap.c:
 *   - all hugetlbfs_i_mmap_rwsem_key locks (aka mapping->i_mmap_rwsem क्रम
 *     hugetlb mapping);
 *   - all i_mmap_rwsem locks;
 *   - all anon_vma->rwseml
 *
 * We can take all locks within these types अक्रमomly because the VM code
 * करोesn't nest them and we रक्षित from parallel mm_take_all_locks() by
 * mm_all_locks_mutex.
 *
 * mm_take_all_locks() and mm_drop_all_locks are expensive operations
 * that may have to take thousand of locks.
 *
 * mm_take_all_locks() can fail अगर it's पूर्णांकerrupted by संकेतs.
 */
पूर्णांक mm_take_all_locks(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा anon_vma_chain *avc;

	BUG_ON(mmap_पढ़ो_trylock(mm));

	mutex_lock(&mm_all_locks_mutex);

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (संकेत_pending(current))
			जाओ out_unlock;
		अगर (vma->vm_file && vma->vm_file->f_mapping &&
				is_vm_hugetlb_page(vma))
			vm_lock_mapping(mm, vma->vm_file->f_mapping);
	पूर्ण

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (संकेत_pending(current))
			जाओ out_unlock;
		अगर (vma->vm_file && vma->vm_file->f_mapping &&
				!is_vm_hugetlb_page(vma))
			vm_lock_mapping(mm, vma->vm_file->f_mapping);
	पूर्ण

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (संकेत_pending(current))
			जाओ out_unlock;
		अगर (vma->anon_vma)
			list_क्रम_each_entry(avc, &vma->anon_vma_chain, same_vma)
				vm_lock_anon_vma(mm, avc->anon_vma);
	पूर्ण

	वापस 0;

out_unlock:
	mm_drop_all_locks(mm);
	वापस -EINTR;
पूर्ण

अटल व्योम vm_unlock_anon_vma(काष्ठा anon_vma *anon_vma)
अणु
	अगर (test_bit(0, (अचिन्हित दीर्घ *) &anon_vma->root->rb_root.rb_root.rb_node)) अणु
		/*
		 * The LSB of head.next can't change to 0 from under
		 * us because we hold the mm_all_locks_mutex.
		 *
		 * We must however clear the bitflag beक्रमe unlocking
		 * the vma so the users using the anon_vma->rb_root will
		 * never see our bitflag.
		 *
		 * No need of atomic inकाष्ठाions here, head.next
		 * can't change from under us until we release the
		 * anon_vma->root->rwsem.
		 */
		अगर (!__test_and_clear_bit(0, (अचिन्हित दीर्घ *)
					  &anon_vma->root->rb_root.rb_root.rb_node))
			BUG();
		anon_vma_unlock_ग_लिखो(anon_vma);
	पूर्ण
पूर्ण

अटल व्योम vm_unlock_mapping(काष्ठा address_space *mapping)
अणु
	अगर (test_bit(AS_MM_ALL_LOCKS, &mapping->flags)) अणु
		/*
		 * AS_MM_ALL_LOCKS can't change to 0 from under us
		 * because we hold the mm_all_locks_mutex.
		 */
		i_mmap_unlock_ग_लिखो(mapping);
		अगर (!test_and_clear_bit(AS_MM_ALL_LOCKS,
					&mapping->flags))
			BUG();
	पूर्ण
पूर्ण

/*
 * The mmap_lock cannot be released by the caller until
 * mm_drop_all_locks() वापसs.
 */
व्योम mm_drop_all_locks(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा anon_vma_chain *avc;

	BUG_ON(mmap_पढ़ो_trylock(mm));
	BUG_ON(!mutex_is_locked(&mm_all_locks_mutex));

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (vma->anon_vma)
			list_क्रम_each_entry(avc, &vma->anon_vma_chain, same_vma)
				vm_unlock_anon_vma(avc->anon_vma);
		अगर (vma->vm_file && vma->vm_file->f_mapping)
			vm_unlock_mapping(vma->vm_file->f_mapping);
	पूर्ण

	mutex_unlock(&mm_all_locks_mutex);
पूर्ण

/*
 * initialise the percpu counter क्रम VM
 */
व्योम __init mmap_init(व्योम)
अणु
	पूर्णांक ret;

	ret = percpu_counter_init(&vm_committed_as, 0, GFP_KERNEL);
	VM_BUG_ON(ret);
पूर्ण

/*
 * Initialise sysctl_user_reserve_kbytes.
 *
 * This is पूर्णांकended to prevent a user from starting a single memory hogging
 * process, such that they cannot recover (समाप्त the hog) in OVERCOMMIT_NEVER
 * mode.
 *
 * The शेष value is min(3% of मुक्त memory, 128MB)
 * 128MB is enough to recover with sshd/login, bash, and top/समाप्त.
 */
अटल पूर्णांक init_user_reserve(व्योम)
अणु
	अचिन्हित दीर्घ मुक्त_kbytes;

	मुक्त_kbytes = global_zone_page_state(NR_FREE_PAGES) << (PAGE_SHIFT - 10);

	sysctl_user_reserve_kbytes = min(मुक्त_kbytes / 32, 1UL << 17);
	वापस 0;
पूर्ण
subsys_initcall(init_user_reserve);

/*
 * Initialise sysctl_admin_reserve_kbytes.
 *
 * The purpose of sysctl_admin_reserve_kbytes is to allow the sys admin
 * to log in and समाप्त a memory hogging process.
 *
 * Systems with more than 256MB will reserve 8MB, enough to recover
 * with sshd, bash, and top in OVERCOMMIT_GUESS. Smaller प्रणालीs will
 * only reserve 3% of मुक्त pages by शेष.
 */
अटल पूर्णांक init_admin_reserve(व्योम)
अणु
	अचिन्हित दीर्घ मुक्त_kbytes;

	मुक्त_kbytes = global_zone_page_state(NR_FREE_PAGES) << (PAGE_SHIFT - 10);

	sysctl_admin_reserve_kbytes = min(मुक्त_kbytes / 32, 1UL << 13);
	वापस 0;
पूर्ण
subsys_initcall(init_admin_reserve);

/*
 * Reinititalise user and admin reserves अगर memory is added or हटाओd.
 *
 * The शेष user reserve max is 128MB, and the शेष max क्रम the
 * admin reserve is 8MB. These are usually, but not always, enough to
 * enable recovery from a memory hogging process using login/sshd, a shell,
 * and tools like top. It may make sense to increase or even disable the
 * reserve depending on the existence of swap or variations in the recovery
 * tools. So, the admin may have changed them.
 *
 * If memory is added and the reserves have been eliminated or increased above
 * the शेष max, then we'll trust the admin.
 *
 * If memory is हटाओd and there isn't enough मुक्त memory, then we
 * need to reset the reserves.
 *
 * Otherwise keep the reserve set by the admin.
 */
अटल पूर्णांक reserve_mem_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	अचिन्हित दीर्घ पंचांगp, मुक्त_kbytes;

	चयन (action) अणु
	हाल MEM_ONLINE:
		/* Default max is 128MB. Leave alone अगर modअगरied by चालक. */
		पंचांगp = sysctl_user_reserve_kbytes;
		अगर (0 < पंचांगp && पंचांगp < (1UL << 17))
			init_user_reserve();

		/* Default max is 8MB.  Leave alone अगर modअगरied by चालक. */
		पंचांगp = sysctl_admin_reserve_kbytes;
		अगर (0 < पंचांगp && पंचांगp < (1UL << 13))
			init_admin_reserve();

		अवरोध;
	हाल MEM_OFFLINE:
		मुक्त_kbytes = global_zone_page_state(NR_FREE_PAGES) << (PAGE_SHIFT - 10);

		अगर (sysctl_user_reserve_kbytes > मुक्त_kbytes) अणु
			init_user_reserve();
			pr_info("vm.user_reserve_kbytes reset to %lu\n",
				sysctl_user_reserve_kbytes);
		पूर्ण

		अगर (sysctl_admin_reserve_kbytes > मुक्त_kbytes) अणु
			init_admin_reserve();
			pr_info("vm.admin_reserve_kbytes reset to %lu\n",
				sysctl_admin_reserve_kbytes);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block reserve_mem_nb = अणु
	.notअगरier_call = reserve_mem_notअगरier,
पूर्ण;

अटल पूर्णांक __meminit init_reserve_notअगरier(व्योम)
अणु
	अगर (रेजिस्टर_hoपंचांगemory_notअगरier(&reserve_mem_nb))
		pr_err("Failed registering memory add/remove notifier for admin reserve\n");

	वापस 0;
पूर्ण
subsys_initcall(init_reserve_notअगरier);

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pagewalk.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/huge_mm.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/swapops.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/page_idle.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pkeys.h>

#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश "internal.h"

#घोषणा SEQ_PUT_DEC(str, val) \
		seq_put_decimal_ull_width(m, str, (val) << (PAGE_SHIFT-10), 8)
व्योम task_mem(काष्ठा seq_file *m, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ text, lib, swap, anon, file, shmem;
	अचिन्हित दीर्घ hiwater_vm, total_vm, hiwater_rss, total_rss;

	anon = get_mm_counter(mm, MM_ANONPAGES);
	file = get_mm_counter(mm, MM_खाताPAGES);
	shmem = get_mm_counter(mm, MM_SHMEMPAGES);

	/*
	 * Note: to minimize their overhead, mm मुख्यtains hiwater_vm and
	 * hiwater_rss only when about to *lower* total_vm or rss.  Any
	 * collector of these hiwater stats must thereक्रमe get total_vm
	 * and rss too, which will usually be the higher.  Barriers? not
	 * worth the efक्रमt, such snapshots can always be inconsistent.
	 */
	hiwater_vm = total_vm = mm->total_vm;
	अगर (hiwater_vm < mm->hiwater_vm)
		hiwater_vm = mm->hiwater_vm;
	hiwater_rss = total_rss = anon + file + shmem;
	अगर (hiwater_rss < mm->hiwater_rss)
		hiwater_rss = mm->hiwater_rss;

	/* split executable areas between text and lib */
	text = PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK);
	text = min(text, mm->exec_vm << PAGE_SHIFT);
	lib = (mm->exec_vm << PAGE_SHIFT) - text;

	swap = get_mm_counter(mm, MM_SWAPENTS);
	SEQ_PUT_DEC("VmPeak:\t", hiwater_vm);
	SEQ_PUT_DEC(" kB\nVmSize:\t", total_vm);
	SEQ_PUT_DEC(" kB\nVmLck:\t", mm->locked_vm);
	SEQ_PUT_DEC(" kB\nVmPin:\t", atomic64_पढ़ो(&mm->pinned_vm));
	SEQ_PUT_DEC(" kB\nVmHWM:\t", hiwater_rss);
	SEQ_PUT_DEC(" kB\nVmRSS:\t", total_rss);
	SEQ_PUT_DEC(" kB\nRssAnon:\t", anon);
	SEQ_PUT_DEC(" kB\nRssFile:\t", file);
	SEQ_PUT_DEC(" kB\nRssShmem:\t", shmem);
	SEQ_PUT_DEC(" kB\nVmData:\t", mm->data_vm);
	SEQ_PUT_DEC(" kB\nVmStk:\t", mm->stack_vm);
	seq_put_decimal_ull_width(m,
		    " kB\nVmExe:\t", text >> 10, 8);
	seq_put_decimal_ull_width(m,
		    " kB\nVmLib:\t", lib >> 10, 8);
	seq_put_decimal_ull_width(m,
		    " kB\nVmPTE:\t", mm_pgtables_bytes(mm) >> 10, 8);
	SEQ_PUT_DEC(" kB\nVmSwap:\t", swap);
	seq_माला_दो(m, " kB\n");
	hugetlb_report_usage(m, mm);
पूर्ण
#अघोषित SEQ_PUT_DEC

अचिन्हित दीर्घ task_vsize(काष्ठा mm_काष्ठा *mm)
अणु
	वापस PAGE_SIZE * mm->total_vm;
पूर्ण

अचिन्हित दीर्घ task_staपंचांग(काष्ठा mm_काष्ठा *mm,
			 अचिन्हित दीर्घ *shared, अचिन्हित दीर्घ *text,
			 अचिन्हित दीर्घ *data, अचिन्हित दीर्घ *resident)
अणु
	*shared = get_mm_counter(mm, MM_खाताPAGES) +
			get_mm_counter(mm, MM_SHMEMPAGES);
	*text = (PAGE_ALIGN(mm->end_code) - (mm->start_code & PAGE_MASK))
								>> PAGE_SHIFT;
	*data = mm->data_vm + mm->stack_vm;
	*resident = *shared + get_mm_counter(mm, MM_ANONPAGES);
	वापस mm->total_vm;
पूर्ण

#अगर_घोषित CONFIG_NUMA
/*
 * Save get_task_policy() क्रम show_numa_map().
 */
अटल व्योम hold_task_mempolicy(काष्ठा proc_maps_निजी *priv)
अणु
	काष्ठा task_काष्ठा *task = priv->task;

	task_lock(task);
	priv->task_mempolicy = get_task_policy(task);
	mpol_get(priv->task_mempolicy);
	task_unlock(task);
पूर्ण
अटल व्योम release_task_mempolicy(काष्ठा proc_maps_निजी *priv)
अणु
	mpol_put(priv->task_mempolicy);
पूर्ण
#अन्यथा
अटल व्योम hold_task_mempolicy(काष्ठा proc_maps_निजी *priv)
अणु
पूर्ण
अटल व्योम release_task_mempolicy(काष्ठा proc_maps_निजी *priv)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम *m_start(काष्ठा seq_file *m, loff_t *ppos)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;
	अचिन्हित दीर्घ last_addr = *ppos;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;

	/* See m_next(). Zero at the start or after lseek. */
	अगर (last_addr == -1UL)
		वापस शून्य;

	priv->task = get_proc_task(priv->inode);
	अगर (!priv->task)
		वापस ERR_PTR(-ESRCH);

	mm = priv->mm;
	अगर (!mm || !mmget_not_zero(mm)) अणु
		put_task_काष्ठा(priv->task);
		priv->task = शून्य;
		वापस शून्य;
	पूर्ण

	अगर (mmap_पढ़ो_lock_समाप्तable(mm)) अणु
		mmput(mm);
		put_task_काष्ठा(priv->task);
		priv->task = शून्य;
		वापस ERR_PTR(-EINTR);
	पूर्ण

	hold_task_mempolicy(priv);
	priv->tail_vma = get_gate_vma(mm);

	vma = find_vma(mm, last_addr);
	अगर (vma)
		वापस vma;

	वापस priv->tail_vma;
पूर्ण

अटल व्योम *m_next(काष्ठा seq_file *m, व्योम *v, loff_t *ppos)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;
	काष्ठा vm_area_काष्ठा *next, *vma = v;

	अगर (vma == priv->tail_vma)
		next = शून्य;
	अन्यथा अगर (vma->vm_next)
		next = vma->vm_next;
	अन्यथा
		next = priv->tail_vma;

	*ppos = next ? next->vm_start : -1UL;

	वापस next;
पूर्ण

अटल व्योम m_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;
	काष्ठा mm_काष्ठा *mm = priv->mm;

	अगर (!priv->task)
		वापस;

	release_task_mempolicy(priv);
	mmap_पढ़ो_unlock(mm);
	mmput(mm);
	put_task_काष्ठा(priv->task);
	priv->task = शून्य;
पूर्ण

अटल पूर्णांक proc_maps_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			स्थिर काष्ठा seq_operations *ops, पूर्णांक psize)
अणु
	काष्ठा proc_maps_निजी *priv = __seq_खोलो_निजी(file, ops, psize);

	अगर (!priv)
		वापस -ENOMEM;

	priv->inode = inode;
	priv->mm = proc_mem_खोलो(inode, PTRACE_MODE_READ);
	अगर (IS_ERR(priv->mm)) अणु
		पूर्णांक err = PTR_ERR(priv->mm);

		seq_release_निजी(inode, file);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक proc_map_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा proc_maps_निजी *priv = seq->निजी;

	अगर (priv->mm)
		mmdrop(priv->mm);

	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक करो_maps_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			स्थिर काष्ठा seq_operations *ops)
अणु
	वापस proc_maps_खोलो(inode, file, ops,
				माप(काष्ठा proc_maps_निजी));
पूर्ण

/*
 * Indicate अगर the VMA is a stack क्रम the given task; क्रम
 * /proc/PID/maps that is the stack of the मुख्य task.
 */
अटल पूर्णांक is_stack(काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * We make no efक्रमt to guess what a given thपढ़ो considers to be
	 * its "stack".  It's not even well-defined क्रम programs written
	 * languages like Go.
	 */
	वापस vma->vm_start <= vma->vm_mm->start_stack &&
		vma->vm_end >= vma->vm_mm->start_stack;
पूर्ण

अटल व्योम show_vma_header_prefix(काष्ठा seq_file *m,
				   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				   vm_flags_t flags, अचिन्हित दीर्घ दीर्घ pgoff,
				   dev_t dev, अचिन्हित दीर्घ ino)
अणु
	seq_setwidth(m, 25 + माप(व्योम *) * 6 - 1);
	seq_put_hex_ll(m, शून्य, start, 8);
	seq_put_hex_ll(m, "-", end, 8);
	seq_अ_दो(m, ' ');
	seq_अ_दो(m, flags & VM_READ ? 'r' : '-');
	seq_अ_दो(m, flags & VM_WRITE ? 'w' : '-');
	seq_अ_दो(m, flags & VM_EXEC ? 'x' : '-');
	seq_अ_दो(m, flags & VM_MAYSHARE ? 's' : 'p');
	seq_put_hex_ll(m, " ", pgoff, 8);
	seq_put_hex_ll(m, " ", MAJOR(dev), 2);
	seq_put_hex_ll(m, ":", MINOR(dev), 2);
	seq_put_decimal_ull(m, " ", ino);
	seq_अ_दो(m, ' ');
पूर्ण

अटल व्योम
show_map_vma(काष्ठा seq_file *m, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा file *file = vma->vm_file;
	vm_flags_t flags = vma->vm_flags;
	अचिन्हित दीर्घ ino = 0;
	अचिन्हित दीर्घ दीर्घ pgoff = 0;
	अचिन्हित दीर्घ start, end;
	dev_t dev = 0;
	स्थिर अक्षर *name = शून्य;

	अगर (file) अणु
		काष्ठा inode *inode = file_inode(vma->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = ((loff_t)vma->vm_pgoff) << PAGE_SHIFT;
	पूर्ण

	start = vma->vm_start;
	end = vma->vm_end;
	show_vma_header_prefix(m, start, end, flags, pgoff, dev, ino);

	/*
	 * Prपूर्णांक the dentry name क्रम named mappings, and a
	 * special [heap] marker क्रम the heap:
	 */
	अगर (file) अणु
		seq_pad(m, ' ');
		seq_file_path(m, file, "\n");
		जाओ करोne;
	पूर्ण

	अगर (vma->vm_ops && vma->vm_ops->name) अणु
		name = vma->vm_ops->name(vma);
		अगर (name)
			जाओ करोne;
	पूर्ण

	name = arch_vma_name(vma);
	अगर (!name) अणु
		अगर (!mm) अणु
			name = "[vdso]";
			जाओ करोne;
		पूर्ण

		अगर (vma->vm_start <= mm->brk &&
		    vma->vm_end >= mm->start_brk) अणु
			name = "[heap]";
			जाओ करोne;
		पूर्ण

		अगर (is_stack(vma))
			name = "[stack]";
	पूर्ण

करोne:
	अगर (name) अणु
		seq_pad(m, ' ');
		seq_माला_दो(m, name);
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल पूर्णांक show_map(काष्ठा seq_file *m, व्योम *v)
अणु
	show_map_vma(m, v);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_pid_maps_op = अणु
	.start	= m_start,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_map
पूर्ण;

अटल पूर्णांक pid_maps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस करो_maps_खोलो(inode, file, &proc_pid_maps_op);
पूर्ण

स्थिर काष्ठा file_operations proc_pid_maps_operations = अणु
	.खोलो		= pid_maps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_map_release,
पूर्ण;

/*
 * Proportional Set Size(PSS): my share of RSS.
 *
 * PSS of a process is the count of pages it has in memory, where each
 * page is भागided by the number of processes sharing it.  So अगर a
 * process has 1000 pages all to itself, and 1000 shared with one other
 * process, its PSS will be 1500.
 *
 * To keep (accumulated) भागision errors low, we aकरोpt a 64bit
 * fixed-poपूर्णांक pss counter to minimize भागision errors. So (pss >>
 * PSS_SHIFT) would be the real byte count.
 *
 * A shअगरt of 12 beक्रमe भागision means (assuming 4K page size):
 * 	- 1M 3-user-pages add up to 8KB errors;
 * 	- supports mapcount up to 2^24, or 16M;
 * 	- supports PSS up to 2^52 bytes, or 4PB.
 */
#घोषणा PSS_SHIFT 12

#अगर_घोषित CONFIG_PROC_PAGE_MONITOR
काष्ठा mem_size_stats अणु
	अचिन्हित दीर्घ resident;
	अचिन्हित दीर्घ shared_clean;
	अचिन्हित दीर्घ shared_dirty;
	अचिन्हित दीर्घ निजी_clean;
	अचिन्हित दीर्घ निजी_dirty;
	अचिन्हित दीर्घ referenced;
	अचिन्हित दीर्घ anonymous;
	अचिन्हित दीर्घ lazyमुक्त;
	अचिन्हित दीर्घ anonymous_thp;
	अचिन्हित दीर्घ shmem_thp;
	अचिन्हित दीर्घ file_thp;
	अचिन्हित दीर्घ swap;
	अचिन्हित दीर्घ shared_hugetlb;
	अचिन्हित दीर्घ निजी_hugetlb;
	u64 pss;
	u64 pss_anon;
	u64 pss_file;
	u64 pss_shmem;
	u64 pss_locked;
	u64 swap_pss;
	bool check_shmem_swap;
पूर्ण;

अटल व्योम smaps_page_accumulate(काष्ठा mem_size_stats *mss,
		काष्ठा page *page, अचिन्हित दीर्घ size, अचिन्हित दीर्घ pss,
		bool dirty, bool locked, bool निजी)
अणु
	mss->pss += pss;

	अगर (PageAnon(page))
		mss->pss_anon += pss;
	अन्यथा अगर (PageSwapBacked(page))
		mss->pss_shmem += pss;
	अन्यथा
		mss->pss_file += pss;

	अगर (locked)
		mss->pss_locked += pss;

	अगर (dirty || PageDirty(page)) अणु
		अगर (निजी)
			mss->निजी_dirty += size;
		अन्यथा
			mss->shared_dirty += size;
	पूर्ण अन्यथा अणु
		अगर (निजी)
			mss->निजी_clean += size;
		अन्यथा
			mss->shared_clean += size;
	पूर्ण
पूर्ण

अटल व्योम smaps_account(काष्ठा mem_size_stats *mss, काष्ठा page *page,
		bool compound, bool young, bool dirty, bool locked)
अणु
	पूर्णांक i, nr = compound ? compound_nr(page) : 1;
	अचिन्हित दीर्घ size = nr * PAGE_SIZE;

	/*
	 * First accumulate quantities that depend only on |size| and the type
	 * of the compound page.
	 */
	अगर (PageAnon(page)) अणु
		mss->anonymous += size;
		अगर (!PageSwapBacked(page) && !dirty && !PageDirty(page))
			mss->lazyमुक्त += size;
	पूर्ण

	mss->resident += size;
	/* Accumulate the size in pages that have been accessed. */
	अगर (young || page_is_young(page) || PageReferenced(page))
		mss->referenced += size;

	/*
	 * Then accumulate quantities that may depend on sharing, or that may
	 * dअगरfer page-by-page.
	 *
	 * page_count(page) == 1 guarantees the page is mapped exactly once.
	 * If any subpage of the compound page mapped with PTE it would elevate
	 * page_count().
	 */
	अगर (page_count(page) == 1) अणु
		smaps_page_accumulate(mss, page, size, size << PSS_SHIFT, dirty,
			locked, true);
		वापस;
	पूर्ण
	क्रम (i = 0; i < nr; i++, page++) अणु
		पूर्णांक mapcount = page_mapcount(page);
		अचिन्हित दीर्घ pss = PAGE_SIZE << PSS_SHIFT;
		अगर (mapcount >= 2)
			pss /= mapcount;
		smaps_page_accumulate(mss, page, PAGE_SIZE, pss, dirty, locked,
				      mapcount < 2);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SHMEM
अटल पूर्णांक smaps_pte_hole(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			  __always_unused पूर्णांक depth, काष्ठा mm_walk *walk)
अणु
	काष्ठा mem_size_stats *mss = walk->निजी;

	mss->swap += shmem_partial_swap_usage(
			walk->vma->vm_file->f_mapping, addr, end);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smaps_pte_hole		शून्य
#पूर्ण_अगर /* CONFIG_SHMEM */

अटल व्योम smaps_pte_entry(pte_t *pte, अचिन्हित दीर्घ addr,
		काष्ठा mm_walk *walk)
अणु
	काष्ठा mem_size_stats *mss = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	bool locked = !!(vma->vm_flags & VM_LOCKED);
	काष्ठा page *page = शून्य;

	अगर (pte_present(*pte)) अणु
		page = vm_normal_page(vma, addr, *pte);
	पूर्ण अन्यथा अगर (is_swap_pte(*pte)) अणु
		swp_entry_t swpent = pte_to_swp_entry(*pte);

		अगर (!non_swap_entry(swpent)) अणु
			पूर्णांक mapcount;

			mss->swap += PAGE_SIZE;
			mapcount = swp_swapcount(swpent);
			अगर (mapcount >= 2) अणु
				u64 pss_delta = (u64)PAGE_SIZE << PSS_SHIFT;

				करो_भाग(pss_delta, mapcount);
				mss->swap_pss += pss_delta;
			पूर्ण अन्यथा अणु
				mss->swap_pss += (u64)PAGE_SIZE << PSS_SHIFT;
			पूर्ण
		पूर्ण अन्यथा अगर (is_migration_entry(swpent))
			page = migration_entry_to_page(swpent);
		अन्यथा अगर (is_device_निजी_entry(swpent))
			page = device_निजी_entry_to_page(swpent);
	पूर्ण अन्यथा अगर (unlikely(IS_ENABLED(CONFIG_SHMEM) && mss->check_shmem_swap
							&& pte_none(*pte))) अणु
		page = xa_load(&vma->vm_file->f_mapping->i_pages,
						linear_page_index(vma, addr));
		अगर (xa_is_value(page))
			mss->swap += PAGE_SIZE;
		वापस;
	पूर्ण

	अगर (!page)
		वापस;

	smaps_account(mss, page, false, pte_young(*pte), pte_dirty(*pte), locked);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम smaps_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
		काष्ठा mm_walk *walk)
अणु
	काष्ठा mem_size_stats *mss = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	bool locked = !!(vma->vm_flags & VM_LOCKED);
	काष्ठा page *page = शून्य;

	अगर (pmd_present(*pmd)) अणु
		/* FOLL_DUMP will वापस -EFAULT on huge zero page */
		page = follow_trans_huge_pmd(vma, addr, pmd, FOLL_DUMP);
	पूर्ण अन्यथा अगर (unlikely(thp_migration_supported() && is_swap_pmd(*pmd))) अणु
		swp_entry_t entry = pmd_to_swp_entry(*pmd);

		अगर (is_migration_entry(entry))
			page = migration_entry_to_page(entry);
	पूर्ण
	अगर (IS_ERR_OR_शून्य(page))
		वापस;
	अगर (PageAnon(page))
		mss->anonymous_thp += HPAGE_PMD_SIZE;
	अन्यथा अगर (PageSwapBacked(page))
		mss->shmem_thp += HPAGE_PMD_SIZE;
	अन्यथा अगर (is_zone_device_page(page))
		/* pass */;
	अन्यथा
		mss->file_thp += HPAGE_PMD_SIZE;
	smaps_account(mss, page, true, pmd_young(*pmd), pmd_dirty(*pmd), locked);
पूर्ण
#अन्यथा
अटल व्योम smaps_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
		काष्ठा mm_walk *walk)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक smaps_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			   काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *pte;
	spinlock_t *ptl;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		smaps_pmd_entry(pmd, addr, walk);
		spin_unlock(ptl);
		जाओ out;
	पूर्ण

	अगर (pmd_trans_unstable(pmd))
		जाओ out;
	/*
	 * The mmap_lock held all the way back in m_start() is what
	 * keeps khugepaged out of here and from collapsing things
	 * in here.
	 */
	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	क्रम (; addr != end; pte++, addr += PAGE_SIZE)
		smaps_pte_entry(pte, addr, walk);
	pte_unmap_unlock(pte - 1, ptl);
out:
	cond_resched();
	वापस 0;
पूर्ण

अटल व्योम show_smap_vma_flags(काष्ठा seq_file *m, काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * Don't क्रमget to update Documentation/ on changes.
	 */
	अटल स्थिर अक्षर mnemonics[BITS_PER_LONG][2] = अणु
		/*
		 * In हाल अगर we meet a flag we करोn't know about.
		 */
		[0 ... (BITS_PER_LONG-1)] = "??",

		[ilog2(VM_READ)]	= "rd",
		[ilog2(VM_WRITE)]	= "wr",
		[ilog2(VM_EXEC)]	= "ex",
		[ilog2(VM_SHARED)]	= "sh",
		[ilog2(VM_MAYREAD)]	= "mr",
		[ilog2(VM_MAYWRITE)]	= "mw",
		[ilog2(VM_MAYEXEC)]	= "me",
		[ilog2(VM_MAYSHARE)]	= "ms",
		[ilog2(VM_GROWSDOWN)]	= "gd",
		[ilog2(VM_PFNMAP)]	= "pf",
		[ilog2(VM_DENYWRITE)]	= "dw",
		[ilog2(VM_LOCKED)]	= "lo",
		[ilog2(VM_IO)]		= "io",
		[ilog2(VM_SEQ_READ)]	= "sr",
		[ilog2(VM_RAND_READ)]	= "rr",
		[ilog2(VM_DONTCOPY)]	= "dc",
		[ilog2(VM_DONTEXPAND)]	= "de",
		[ilog2(VM_ACCOUNT)]	= "ac",
		[ilog2(VM_NORESERVE)]	= "nr",
		[ilog2(VM_HUGETLB)]	= "ht",
		[ilog2(VM_SYNC)]	= "sf",
		[ilog2(VM_ARCH_1)]	= "ar",
		[ilog2(VM_WIPEONFORK)]	= "wf",
		[ilog2(VM_DONTDUMP)]	= "dd",
#अगर_घोषित CONFIG_ARM64_BTI
		[ilog2(VM_ARM64_BTI)]	= "bt",
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
		[ilog2(VM_SOFTसूचीTY)]	= "sd",
#पूर्ण_अगर
		[ilog2(VM_MIXEDMAP)]	= "mm",
		[ilog2(VM_HUGEPAGE)]	= "hg",
		[ilog2(VM_NOHUGEPAGE)]	= "nh",
		[ilog2(VM_MERGEABLE)]	= "mg",
		[ilog2(VM_UFFD_MISSING)]= "um",
		[ilog2(VM_UFFD_WP)]	= "uw",
#अगर_घोषित CONFIG_ARM64_MTE
		[ilog2(VM_MTE)]		= "mt",
		[ilog2(VM_MTE_ALLOWED)]	= "",
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_HAS_PKEYS
		/* These come out via ProtectionKey: */
		[ilog2(VM_PKEY_BIT0)]	= "",
		[ilog2(VM_PKEY_BIT1)]	= "",
		[ilog2(VM_PKEY_BIT2)]	= "",
		[ilog2(VM_PKEY_BIT3)]	= "",
#अगर VM_PKEY_BIT4
		[ilog2(VM_PKEY_BIT4)]	= "",
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_ARCH_HAS_PKEYS */
#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_MINOR
		[ilog2(VM_UFFD_MINOR)]	= "ui",
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_USERFAULTFD_MINOR */
	पूर्ण;
	माप_प्रकार i;

	seq_माला_दो(m, "VmFlags: ");
	क्रम (i = 0; i < BITS_PER_LONG; i++) अणु
		अगर (!mnemonics[i][0])
			जारी;
		अगर (vma->vm_flags & (1UL << i)) अणु
			seq_अ_दो(m, mnemonics[i][0]);
			seq_अ_दो(m, mnemonics[i][1]);
			seq_अ_दो(m, ' ');
		पूर्ण
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल पूर्णांक smaps_hugetlb_range(pte_t *pte, अचिन्हित दीर्घ hmask,
				 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				 काष्ठा mm_walk *walk)
अणु
	काष्ठा mem_size_stats *mss = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा page *page = शून्य;

	अगर (pte_present(*pte)) अणु
		page = vm_normal_page(vma, addr, *pte);
	पूर्ण अन्यथा अगर (is_swap_pte(*pte)) अणु
		swp_entry_t swpent = pte_to_swp_entry(*pte);

		अगर (is_migration_entry(swpent))
			page = migration_entry_to_page(swpent);
		अन्यथा अगर (is_device_निजी_entry(swpent))
			page = device_निजी_entry_to_page(swpent);
	पूर्ण
	अगर (page) अणु
		पूर्णांक mapcount = page_mapcount(page);

		अगर (mapcount >= 2)
			mss->shared_hugetlb += huge_page_size(hstate_vma(vma));
		अन्यथा
			mss->निजी_hugetlb += huge_page_size(hstate_vma(vma));
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा smaps_hugetlb_range	शून्य
#पूर्ण_अगर /* HUGETLB_PAGE */

अटल स्थिर काष्ठा mm_walk_ops smaps_walk_ops = अणु
	.pmd_entry		= smaps_pte_range,
	.hugetlb_entry		= smaps_hugetlb_range,
पूर्ण;

अटल स्थिर काष्ठा mm_walk_ops smaps_shmem_walk_ops = अणु
	.pmd_entry		= smaps_pte_range,
	.hugetlb_entry		= smaps_hugetlb_range,
	.pte_hole		= smaps_pte_hole,
पूर्ण;

/*
 * Gather mem stats from @vma with the indicated beginning
 * address @start, and keep them in @mss.
 *
 * Use vm_start of @vma as the beginning address अगर @start is 0.
 */
अटल व्योम smap_gather_stats(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा mem_size_stats *mss, अचिन्हित दीर्घ start)
अणु
	स्थिर काष्ठा mm_walk_ops *ops = &smaps_walk_ops;

	/* Invalid start */
	अगर (start >= vma->vm_end)
		वापस;

#अगर_घोषित CONFIG_SHMEM
	/* In हाल of smaps_rollup, reset the value from previous vma */
	mss->check_shmem_swap = false;
	अगर (vma->vm_file && shmem_mapping(vma->vm_file->f_mapping)) अणु
		/*
		 * For shared or पढ़ोonly shmem mappings we know that all
		 * swapped out pages beदीर्घ to the shmem object, and we can
		 * obtain the swap value much more efficiently. For निजी
		 * writable mappings, we might have COW pages that are
		 * not affected by the parent swapped out pages of the shmem
		 * object, so we have to distinguish them during the page walk.
		 * Unless we know that the shmem object (or the part mapped by
		 * our VMA) has no swapped out pages at all.
		 */
		अचिन्हित दीर्घ shmem_swapped = shmem_swap_usage(vma);

		अगर (!start && (!shmem_swapped || (vma->vm_flags & VM_SHARED) ||
					!(vma->vm_flags & VM_WRITE))) अणु
			mss->swap += shmem_swapped;
		पूर्ण अन्यथा अणु
			mss->check_shmem_swap = true;
			ops = &smaps_shmem_walk_ops;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* mmap_lock is held in m_start */
	अगर (!start)
		walk_page_vma(vma, ops, mss);
	अन्यथा
		walk_page_range(vma->vm_mm, start, vma->vm_end, ops, mss);
पूर्ण

#घोषणा SEQ_PUT_DEC(str, val) \
		seq_put_decimal_ull_width(m, str, (val) >> 10, 8)

/* Show the contents common क्रम smaps and smaps_rollup */
अटल व्योम __show_smap(काष्ठा seq_file *m, स्थिर काष्ठा mem_size_stats *mss,
	bool rollup_mode)
अणु
	SEQ_PUT_DEC("Rss:            ", mss->resident);
	SEQ_PUT_DEC(" kB\nPss:            ", mss->pss >> PSS_SHIFT);
	अगर (rollup_mode) अणु
		/*
		 * These are meaningful only क्रम smaps_rollup, otherwise two of
		 * them are zero, and the other one is the same as Pss.
		 */
		SEQ_PUT_DEC(" kB\nPss_Anon:       ",
			mss->pss_anon >> PSS_SHIFT);
		SEQ_PUT_DEC(" kB\nPss_File:       ",
			mss->pss_file >> PSS_SHIFT);
		SEQ_PUT_DEC(" kB\nPss_Shmem:      ",
			mss->pss_shmem >> PSS_SHIFT);
	पूर्ण
	SEQ_PUT_DEC(" kB\nShared_Clean:   ", mss->shared_clean);
	SEQ_PUT_DEC(" kB\nShared_Dirty:   ", mss->shared_dirty);
	SEQ_PUT_DEC(" kB\nPrivate_Clean:  ", mss->निजी_clean);
	SEQ_PUT_DEC(" kB\nPrivate_Dirty:  ", mss->निजी_dirty);
	SEQ_PUT_DEC(" kB\nReferenced:     ", mss->referenced);
	SEQ_PUT_DEC(" kB\nAnonymous:      ", mss->anonymous);
	SEQ_PUT_DEC(" kB\nLazyFree:       ", mss->lazyमुक्त);
	SEQ_PUT_DEC(" kB\nAnonHugePages:  ", mss->anonymous_thp);
	SEQ_PUT_DEC(" kB\nShmemPmdMapped: ", mss->shmem_thp);
	SEQ_PUT_DEC(" kB\nFilePmdMapped:  ", mss->file_thp);
	SEQ_PUT_DEC(" kB\nShared_Hugetlb: ", mss->shared_hugetlb);
	seq_put_decimal_ull_width(m, " kB\nPrivate_Hugetlb: ",
				  mss->निजी_hugetlb >> 10, 7);
	SEQ_PUT_DEC(" kB\nSwap:           ", mss->swap);
	SEQ_PUT_DEC(" kB\nSwapPss:        ",
					mss->swap_pss >> PSS_SHIFT);
	SEQ_PUT_DEC(" kB\nLocked:         ",
					mss->pss_locked >> PSS_SHIFT);
	seq_माला_दो(m, " kB\n");
पूर्ण

अटल पूर्णांक show_smap(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा vm_area_काष्ठा *vma = v;
	काष्ठा mem_size_stats mss;

	स_रखो(&mss, 0, माप(mss));

	smap_gather_stats(vma, &mss, 0);

	show_map_vma(m, vma);

	SEQ_PUT_DEC("Size:           ", vma->vm_end - vma->vm_start);
	SEQ_PUT_DEC(" kB\nKernelPageSize: ", vma_kernel_pagesize(vma));
	SEQ_PUT_DEC(" kB\nMMUPageSize:    ", vma_mmu_pagesize(vma));
	seq_माला_दो(m, " kB\n");

	__show_smap(m, &mss, false);

	seq_म_लिखो(m, "THPeligible:    %d\n",
		   transparent_hugepage_enabled(vma));

	अगर (arch_pkeys_enabled())
		seq_म_लिखो(m, "ProtectionKey:  %8u\n", vma_pkey(vma));
	show_smap_vma_flags(m, vma);

	वापस 0;
पूर्ण

अटल पूर्णांक show_smaps_rollup(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा proc_maps_निजी *priv = m->निजी;
	काष्ठा mem_size_stats mss;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ last_vma_end = 0;
	पूर्णांक ret = 0;

	priv->task = get_proc_task(priv->inode);
	अगर (!priv->task)
		वापस -ESRCH;

	mm = priv->mm;
	अगर (!mm || !mmget_not_zero(mm)) अणु
		ret = -ESRCH;
		जाओ out_put_task;
	पूर्ण

	स_रखो(&mss, 0, माप(mss));

	ret = mmap_पढ़ो_lock_समाप्तable(mm);
	अगर (ret)
		जाओ out_put_mm;

	hold_task_mempolicy(priv);

	क्रम (vma = priv->mm->mmap; vma;) अणु
		smap_gather_stats(vma, &mss, 0);
		last_vma_end = vma->vm_end;

		/*
		 * Release mmap_lock temporarily अगर someone wants to
		 * access it क्रम ग_लिखो request.
		 */
		अगर (mmap_lock_is_contended(mm)) अणु
			mmap_पढ़ो_unlock(mm);
			ret = mmap_पढ़ो_lock_समाप्तable(mm);
			अगर (ret) अणु
				release_task_mempolicy(priv);
				जाओ out_put_mm;
			पूर्ण

			/*
			 * After dropping the lock, there are four हालs to
			 * consider. See the following example क्रम explanation.
			 *
			 *   +------+------+-----------+
			 *   | VMA1 | VMA2 | VMA3      |
			 *   +------+------+-----------+
			 *   |      |      |           |
			 *  4k     8k     16k         400k
			 *
			 * Suppose we drop the lock after पढ़ोing VMA2 due to
			 * contention, then we get:
			 *
			 *	last_vma_end = 16k
			 *
			 * 1) VMA2 is मुक्तd, but VMA3 exists:
			 *
			 *    find_vma(mm, 16k - 1) will वापस VMA3.
			 *    In this हाल, just जारी from VMA3.
			 *
			 * 2) VMA2 still exists:
			 *
			 *    find_vma(mm, 16k - 1) will वापस VMA2.
			 *    Iterate the loop like the original one.
			 *
			 * 3) No more VMAs can be found:
			 *
			 *    find_vma(mm, 16k - 1) will वापस शून्य.
			 *    No more things to करो, just अवरोध.
			 *
			 * 4) (last_vma_end - 1) is the middle of a vma (VMA'):
			 *
			 *    find_vma(mm, 16k - 1) will वापस VMA' whose range
			 *    contains last_vma_end.
			 *    Iterate VMA' from last_vma_end.
			 */
			vma = find_vma(mm, last_vma_end - 1);
			/* Case 3 above */
			अगर (!vma)
				अवरोध;

			/* Case 1 above */
			अगर (vma->vm_start >= last_vma_end)
				जारी;

			/* Case 4 above */
			अगर (vma->vm_end > last_vma_end)
				smap_gather_stats(vma, &mss, last_vma_end);
		पूर्ण
		/* Case 2 above */
		vma = vma->vm_next;
	पूर्ण

	show_vma_header_prefix(m, priv->mm->mmap->vm_start,
			       last_vma_end, 0, 0, 0, 0);
	seq_pad(m, ' ');
	seq_माला_दो(m, "[rollup]\n");

	__show_smap(m, &mss, true);

	release_task_mempolicy(priv);
	mmap_पढ़ो_unlock(mm);

out_put_mm:
	mmput(mm);
out_put_task:
	put_task_काष्ठा(priv->task);
	priv->task = शून्य;

	वापस ret;
पूर्ण
#अघोषित SEQ_PUT_DEC

अटल स्थिर काष्ठा seq_operations proc_pid_smaps_op = अणु
	.start	= m_start,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_smap
पूर्ण;

अटल पूर्णांक pid_smaps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस करो_maps_खोलो(inode, file, &proc_pid_smaps_op);
पूर्ण

अटल पूर्णांक smaps_rollup_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा proc_maps_निजी *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL_ACCOUNT);
	अगर (!priv)
		वापस -ENOMEM;

	ret = single_खोलो(file, show_smaps_rollup, priv);
	अगर (ret)
		जाओ out_मुक्त;

	priv->inode = inode;
	priv->mm = proc_mem_खोलो(inode, PTRACE_MODE_READ);
	अगर (IS_ERR(priv->mm)) अणु
		ret = PTR_ERR(priv->mm);

		single_release(inode, file);
		जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक smaps_rollup_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा proc_maps_निजी *priv = seq->निजी;

	अगर (priv->mm)
		mmdrop(priv->mm);

	kमुक्त(priv);
	वापस single_release(inode, file);
पूर्ण

स्थिर काष्ठा file_operations proc_pid_smaps_operations = अणु
	.खोलो		= pid_smaps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_map_release,
पूर्ण;

स्थिर काष्ठा file_operations proc_pid_smaps_rollup_operations = अणु
	.खोलो		= smaps_rollup_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= smaps_rollup_release,
पूर्ण;

क्रमागत clear_refs_types अणु
	CLEAR_REFS_ALL = 1,
	CLEAR_REFS_ANON,
	CLEAR_REFS_MAPPED,
	CLEAR_REFS_SOFT_सूचीTY,
	CLEAR_REFS_MM_HIWATER_RSS,
	CLEAR_REFS_LAST,
पूर्ण;

काष्ठा clear_refs_निजी अणु
	क्रमागत clear_refs_types type;
पूर्ण;

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY

अटल अंतरभूत bool pte_is_pinned(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t pte)
अणु
	काष्ठा page *page;

	अगर (!pte_ग_लिखो(pte))
		वापस false;
	अगर (!is_cow_mapping(vma->vm_flags))
		वापस false;
	अगर (likely(!atomic_पढ़ो(&vma->vm_mm->has_pinned)))
		वापस false;
	page = vm_normal_page(vma, addr, pte);
	अगर (!page)
		वापस false;
	वापस page_maybe_dma_pinned(page);
पूर्ण

अटल अंतरभूत व्योम clear_soft_dirty(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t *pte)
अणु
	/*
	 * The soft-dirty tracker uses #PF-s to catch ग_लिखोs
	 * to pages, so ग_लिखो-protect the pte as well. See the
	 * Documentation/admin-guide/mm/soft-dirty.rst क्रम full description
	 * of how soft-dirty works.
	 */
	pte_t ptent = *pte;

	अगर (pte_present(ptent)) अणु
		pte_t old_pte;

		अगर (pte_is_pinned(vma, addr, ptent))
			वापस;
		old_pte = ptep_modअगरy_prot_start(vma, addr, pte);
		ptent = pte_wrprotect(old_pte);
		ptent = pte_clear_soft_dirty(ptent);
		ptep_modअगरy_prot_commit(vma, addr, pte, old_pte, ptent);
	पूर्ण अन्यथा अगर (is_swap_pte(ptent)) अणु
		ptent = pte_swp_clear_soft_dirty(ptent);
		set_pte_at(vma->vm_mm, addr, pte, ptent);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम clear_soft_dirty(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pte_t *pte)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MEM_SOFT_सूचीTY) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
अटल अंतरभूत व्योम clear_soft_dirty_pmd(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t old, pmd = *pmdp;

	अगर (pmd_present(pmd)) अणु
		/* See comment in change_huge_pmd() */
		old = pmdp_invalidate(vma, addr, pmdp);
		अगर (pmd_dirty(old))
			pmd = pmd_सूची_गढ़ोty(pmd);
		अगर (pmd_young(old))
			pmd = pmd_mkyoung(pmd);

		pmd = pmd_wrprotect(pmd);
		pmd = pmd_clear_soft_dirty(pmd);

		set_pmd_at(vma->vm_mm, addr, pmdp, pmd);
	पूर्ण अन्यथा अगर (is_migration_entry(pmd_to_swp_entry(pmd))) अणु
		pmd = pmd_swp_clear_soft_dirty(pmd);
		set_pmd_at(vma->vm_mm, addr, pmdp, pmd);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम clear_soft_dirty_pmd(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक clear_refs_pte_range(pmd_t *pmd, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा clear_refs_निजी *cp = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	pte_t *pte, ptent;
	spinlock_t *ptl;
	काष्ठा page *page;

	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		अगर (cp->type == CLEAR_REFS_SOFT_सूचीTY) अणु
			clear_soft_dirty_pmd(vma, addr, pmd);
			जाओ out;
		पूर्ण

		अगर (!pmd_present(*pmd))
			जाओ out;

		page = pmd_page(*pmd);

		/* Clear accessed and referenced bits. */
		pmdp_test_and_clear_young(vma, addr, pmd);
		test_and_clear_page_young(page);
		ClearPageReferenced(page);
out:
		spin_unlock(ptl);
		वापस 0;
	पूर्ण

	अगर (pmd_trans_unstable(pmd))
		वापस 0;

	pte = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	क्रम (; addr != end; pte++, addr += PAGE_SIZE) अणु
		ptent = *pte;

		अगर (cp->type == CLEAR_REFS_SOFT_सूचीTY) अणु
			clear_soft_dirty(vma, addr, pte);
			जारी;
		पूर्ण

		अगर (!pte_present(ptent))
			जारी;

		page = vm_normal_page(vma, addr, ptent);
		अगर (!page)
			जारी;

		/* Clear accessed and referenced bits. */
		ptep_test_and_clear_young(vma, addr, pte);
		test_and_clear_page_young(page);
		ClearPageReferenced(page);
	पूर्ण
	pte_unmap_unlock(pte - 1, ptl);
	cond_resched();
	वापस 0;
पूर्ण

अटल पूर्णांक clear_refs_test_walk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				काष्ठा mm_walk *walk)
अणु
	काष्ठा clear_refs_निजी *cp = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;

	अगर (vma->vm_flags & VM_PFNMAP)
		वापस 1;

	/*
	 * Writing 1 to /proc/pid/clear_refs affects all pages.
	 * Writing 2 to /proc/pid/clear_refs only affects anonymous pages.
	 * Writing 3 to /proc/pid/clear_refs only affects file mapped pages.
	 * Writing 4 to /proc/pid/clear_refs affects all pages.
	 */
	अगर (cp->type == CLEAR_REFS_ANON && vma->vm_file)
		वापस 1;
	अगर (cp->type == CLEAR_REFS_MAPPED && !vma->vm_file)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops clear_refs_walk_ops = अणु
	.pmd_entry		= clear_refs_pte_range,
	.test_walk		= clear_refs_test_walk,
पूर्ण;

अटल sमाप_प्रकार clear_refs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर buffer[PROC_NUMBUF];
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	क्रमागत clear_refs_types type;
	पूर्णांक itype;
	पूर्णांक rv;

	स_रखो(buffer, 0, माप(buffer));
	अगर (count > माप(buffer) - 1)
		count = माप(buffer) - 1;
	अगर (copy_from_user(buffer, buf, count))
		वापस -EFAULT;
	rv = kstrtoपूर्णांक(म_मालाip(buffer), 10, &itype);
	अगर (rv < 0)
		वापस rv;
	type = (क्रमागत clear_refs_types)itype;
	अगर (type < CLEAR_REFS_ALL || type >= CLEAR_REFS_LAST)
		वापस -EINVAL;

	task = get_proc_task(file_inode(file));
	अगर (!task)
		वापस -ESRCH;
	mm = get_task_mm(task);
	अगर (mm) अणु
		काष्ठा mmu_notअगरier_range range;
		काष्ठा clear_refs_निजी cp = अणु
			.type = type,
		पूर्ण;

		अगर (mmap_ग_लिखो_lock_समाप्तable(mm)) अणु
			count = -EINTR;
			जाओ out_mm;
		पूर्ण
		अगर (type == CLEAR_REFS_MM_HIWATER_RSS) अणु
			/*
			 * Writing 5 to /proc/pid/clear_refs resets the peak
			 * resident set size to this mm's current rss value.
			 */
			reset_mm_hiwater_rss(mm);
			जाओ out_unlock;
		पूर्ण

		अगर (type == CLEAR_REFS_SOFT_सूचीTY) अणु
			क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
				अगर (!(vma->vm_flags & VM_SOFTसूचीTY))
					जारी;
				vma->vm_flags &= ~VM_SOFTसूचीTY;
				vma_set_page_prot(vma);
			पूर्ण

			inc_tlb_flush_pending(mm);
			mmu_notअगरier_range_init(&range, MMU_NOTIFY_SOFT_सूचीTY,
						0, शून्य, mm, 0, -1UL);
			mmu_notअगरier_invalidate_range_start(&range);
		पूर्ण
		walk_page_range(mm, 0, mm->highest_vm_end, &clear_refs_walk_ops,
				&cp);
		अगर (type == CLEAR_REFS_SOFT_सूचीTY) अणु
			mmu_notअगरier_invalidate_range_end(&range);
			flush_tlb_mm(mm);
			dec_tlb_flush_pending(mm);
		पूर्ण
out_unlock:
		mmap_ग_लिखो_unlock(mm);
out_mm:
		mmput(mm);
	पूर्ण
	put_task_काष्ठा(task);

	वापस count;
पूर्ण

स्थिर काष्ठा file_operations proc_clear_refs_operations = अणु
	.ग_लिखो		= clear_refs_ग_लिखो,
	.llseek		= noop_llseek,
पूर्ण;

प्रकार काष्ठा अणु
	u64 pme;
पूर्ण pagemap_entry_t;

काष्ठा pagemapपढ़ो अणु
	पूर्णांक pos, len;		/* units: PM_ENTRY_BYTES, not bytes */
	pagemap_entry_t *buffer;
	bool show_pfn;
पूर्ण;

#घोषणा PAGEMAP_WALK_SIZE	(PMD_SIZE)
#घोषणा PAGEMAP_WALK_MASK	(PMD_MASK)

#घोषणा PM_ENTRY_BYTES		माप(pagemap_entry_t)
#घोषणा PM_PFRAME_BITS		55
#घोषणा PM_PFRAME_MASK		GENMASK_ULL(PM_PFRAME_BITS - 1, 0)
#घोषणा PM_SOFT_सूचीTY		BIT_ULL(55)
#घोषणा PM_MMAP_EXCLUSIVE	BIT_ULL(56)
#घोषणा PM_खाता			BIT_ULL(61)
#घोषणा PM_SWAP			BIT_ULL(62)
#घोषणा PM_PRESENT		BIT_ULL(63)

#घोषणा PM_END_OF_BUFFER    1

अटल अंतरभूत pagemap_entry_t make_pme(u64 frame, u64 flags)
अणु
	वापस (pagemap_entry_t) अणु .pme = (frame & PM_PFRAME_MASK) | flags पूर्ण;
पूर्ण

अटल पूर्णांक add_to_pagemap(अचिन्हित दीर्घ addr, pagemap_entry_t *pme,
			  काष्ठा pagemapपढ़ो *pm)
अणु
	pm->buffer[pm->pos++] = *pme;
	अगर (pm->pos >= pm->len)
		वापस PM_END_OF_BUFFER;
	वापस 0;
पूर्ण

अटल पूर्णांक pagemap_pte_hole(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			    __always_unused पूर्णांक depth, काष्ठा mm_walk *walk)
अणु
	काष्ठा pagemapपढ़ो *pm = walk->निजी;
	अचिन्हित दीर्घ addr = start;
	पूर्णांक err = 0;

	जबतक (addr < end) अणु
		काष्ठा vm_area_काष्ठा *vma = find_vma(walk->mm, addr);
		pagemap_entry_t pme = make_pme(0, 0);
		/* End of address space hole, which we mark as non-present. */
		अचिन्हित दीर्घ hole_end;

		अगर (vma)
			hole_end = min(end, vma->vm_start);
		अन्यथा
			hole_end = end;

		क्रम (; addr < hole_end; addr += PAGE_SIZE) अणु
			err = add_to_pagemap(addr, &pme, pm);
			अगर (err)
				जाओ out;
		पूर्ण

		अगर (!vma)
			अवरोध;

		/* Addresses in the VMA. */
		अगर (vma->vm_flags & VM_SOFTसूचीTY)
			pme = make_pme(0, PM_SOFT_सूचीTY);
		क्रम (; addr < min(end, vma->vm_end); addr += PAGE_SIZE) अणु
			err = add_to_pagemap(addr, &pme, pm);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

अटल pagemap_entry_t pte_to_pagemap_entry(काष्ठा pagemapपढ़ो *pm,
		काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t pte)
अणु
	u64 frame = 0, flags = 0;
	काष्ठा page *page = शून्य;

	अगर (pte_present(pte)) अणु
		अगर (pm->show_pfn)
			frame = pte_pfn(pte);
		flags |= PM_PRESENT;
		page = vm_normal_page(vma, addr, pte);
		अगर (pte_soft_dirty(pte))
			flags |= PM_SOFT_सूचीTY;
	पूर्ण अन्यथा अगर (is_swap_pte(pte)) अणु
		swp_entry_t entry;
		अगर (pte_swp_soft_dirty(pte))
			flags |= PM_SOFT_सूचीTY;
		entry = pte_to_swp_entry(pte);
		अगर (pm->show_pfn)
			frame = swp_type(entry) |
				(swp_offset(entry) << MAX_SWAPखाताS_SHIFT);
		flags |= PM_SWAP;
		अगर (is_migration_entry(entry))
			page = migration_entry_to_page(entry);

		अगर (is_device_निजी_entry(entry))
			page = device_निजी_entry_to_page(entry);
	पूर्ण

	अगर (page && !PageAnon(page))
		flags |= PM_खाता;
	अगर (page && page_mapcount(page) == 1)
		flags |= PM_MMAP_EXCLUSIVE;
	अगर (vma->vm_flags & VM_SOFTसूचीTY)
		flags |= PM_SOFT_सूचीTY;

	वापस make_pme(frame, flags);
पूर्ण

अटल पूर्णांक pagemap_pmd_range(pmd_t *pmdp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			     काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	काष्ठा pagemapपढ़ो *pm = walk->निजी;
	spinlock_t *ptl;
	pte_t *pte, *orig_pte;
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	ptl = pmd_trans_huge_lock(pmdp, vma);
	अगर (ptl) अणु
		u64 flags = 0, frame = 0;
		pmd_t pmd = *pmdp;
		काष्ठा page *page = शून्य;

		अगर (vma->vm_flags & VM_SOFTसूचीTY)
			flags |= PM_SOFT_सूचीTY;

		अगर (pmd_present(pmd)) अणु
			page = pmd_page(pmd);

			flags |= PM_PRESENT;
			अगर (pmd_soft_dirty(pmd))
				flags |= PM_SOFT_सूचीTY;
			अगर (pm->show_pfn)
				frame = pmd_pfn(pmd) +
					((addr & ~PMD_MASK) >> PAGE_SHIFT);
		पूर्ण
#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
		अन्यथा अगर (is_swap_pmd(pmd)) अणु
			swp_entry_t entry = pmd_to_swp_entry(pmd);
			अचिन्हित दीर्घ offset;

			अगर (pm->show_pfn) अणु
				offset = swp_offset(entry) +
					((addr & ~PMD_MASK) >> PAGE_SHIFT);
				frame = swp_type(entry) |
					(offset << MAX_SWAPखाताS_SHIFT);
			पूर्ण
			flags |= PM_SWAP;
			अगर (pmd_swp_soft_dirty(pmd))
				flags |= PM_SOFT_सूचीTY;
			VM_BUG_ON(!is_pmd_migration_entry(pmd));
			page = migration_entry_to_page(entry);
		पूर्ण
#पूर्ण_अगर

		अगर (page && page_mapcount(page) == 1)
			flags |= PM_MMAP_EXCLUSIVE;

		क्रम (; addr != end; addr += PAGE_SIZE) अणु
			pagemap_entry_t pme = make_pme(frame, flags);

			err = add_to_pagemap(addr, &pme, pm);
			अगर (err)
				अवरोध;
			अगर (pm->show_pfn) अणु
				अगर (flags & PM_PRESENT)
					frame++;
				अन्यथा अगर (flags & PM_SWAP)
					frame += (1 << MAX_SWAPखाताS_SHIFT);
			पूर्ण
		पूर्ण
		spin_unlock(ptl);
		वापस err;
	पूर्ण

	अगर (pmd_trans_unstable(pmdp))
		वापस 0;
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

	/*
	 * We can assume that @vma always poपूर्णांकs to a valid one and @end never
	 * goes beyond vma->vm_end.
	 */
	orig_pte = pte = pte_offset_map_lock(walk->mm, pmdp, addr, &ptl);
	क्रम (; addr < end; pte++, addr += PAGE_SIZE) अणु
		pagemap_entry_t pme;

		pme = pte_to_pagemap_entry(pm, vma, addr, *pte);
		err = add_to_pagemap(addr, &pme, pm);
		अगर (err)
			अवरोध;
	पूर्ण
	pte_unmap_unlock(orig_pte, ptl);

	cond_resched();

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/* This function walks within one hugetlb entry in the single call */
अटल पूर्णांक pagemap_hugetlb_range(pte_t *ptep, अचिन्हित दीर्घ hmask,
				 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				 काष्ठा mm_walk *walk)
अणु
	काष्ठा pagemapपढ़ो *pm = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	u64 flags = 0, frame = 0;
	पूर्णांक err = 0;
	pte_t pte;

	अगर (vma->vm_flags & VM_SOFTसूचीTY)
		flags |= PM_SOFT_सूचीTY;

	pte = huge_ptep_get(ptep);
	अगर (pte_present(pte)) अणु
		काष्ठा page *page = pte_page(pte);

		अगर (!PageAnon(page))
			flags |= PM_खाता;

		अगर (page_mapcount(page) == 1)
			flags |= PM_MMAP_EXCLUSIVE;

		flags |= PM_PRESENT;
		अगर (pm->show_pfn)
			frame = pte_pfn(pte) +
				((addr & ~hmask) >> PAGE_SHIFT);
	पूर्ण

	क्रम (; addr != end; addr += PAGE_SIZE) अणु
		pagemap_entry_t pme = make_pme(frame, flags);

		err = add_to_pagemap(addr, &pme, pm);
		अगर (err)
			वापस err;
		अगर (pm->show_pfn && (flags & PM_PRESENT))
			frame++;
	पूर्ण

	cond_resched();

	वापस err;
पूर्ण
#अन्यथा
#घोषणा pagemap_hugetlb_range	शून्य
#पूर्ण_अगर /* HUGETLB_PAGE */

अटल स्थिर काष्ठा mm_walk_ops pagemap_ops = अणु
	.pmd_entry	= pagemap_pmd_range,
	.pte_hole	= pagemap_pte_hole,
	.hugetlb_entry	= pagemap_hugetlb_range,
पूर्ण;

/*
 * /proc/pid/pagemap - an array mapping भव pages to pfns
 *
 * For each page in the address space, this file contains one 64-bit entry
 * consisting of the following:
 *
 * Bits 0-54  page frame number (PFN) अगर present
 * Bits 0-4   swap type अगर swapped
 * Bits 5-54  swap offset अगर swapped
 * Bit  55    pte is soft-dirty (see Documentation/admin-guide/mm/soft-dirty.rst)
 * Bit  56    page exclusively mapped
 * Bits 57-60 zero
 * Bit  61    page is file-page or shared-anon
 * Bit  62    page swapped
 * Bit  63    page present
 *
 * If the page is not present but in swap, then the PFN contains an
 * encoding of the swap file number and the page's offset पूर्णांकo the
 * swap. Unmapped pages वापस a null PFN. This allows determining
 * precisely which pages are mapped (or in swap) and comparing mapped
 * pages between processes.
 *
 * Efficient users of this पूर्णांकerface will use /proc/pid/maps to
 * determine which areas of memory are actually mapped and llseek to
 * skip over unmapped regions.
 */
अटल sमाप_प्रकार pagemap_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mm_काष्ठा *mm = file->निजी_data;
	काष्ठा pagemapपढ़ो pm;
	अचिन्हित दीर्घ src;
	अचिन्हित दीर्घ svpfn;
	अचिन्हित दीर्घ start_vaddr;
	अचिन्हित दीर्घ end_vaddr;
	पूर्णांक ret = 0, copied = 0;

	अगर (!mm || !mmget_not_zero(mm))
		जाओ out;

	ret = -EINVAL;
	/* file position must be aligned */
	अगर ((*ppos % PM_ENTRY_BYTES) || (count % PM_ENTRY_BYTES))
		जाओ out_mm;

	ret = 0;
	अगर (!count)
		जाओ out_mm;

	/* करो not disबंद physical addresses: attack vector */
	pm.show_pfn = file_ns_capable(file, &init_user_ns, CAP_SYS_ADMIN);

	pm.len = (PAGEMAP_WALK_SIZE >> PAGE_SHIFT);
	pm.buffer = kदो_स्मृति_array(pm.len, PM_ENTRY_BYTES, GFP_KERNEL);
	ret = -ENOMEM;
	अगर (!pm.buffer)
		जाओ out_mm;

	src = *ppos;
	svpfn = src / PM_ENTRY_BYTES;
	end_vaddr = mm->task_size;

	/* watch out क्रम wraparound */
	start_vaddr = end_vaddr;
	अगर (svpfn <= (अच_दीर्घ_उच्च >> PAGE_SHIFT))
		start_vaddr = untagged_addr(svpfn << PAGE_SHIFT);

	/* Ensure the address is inside the task */
	अगर (start_vaddr > mm->task_size)
		start_vaddr = end_vaddr;

	/*
	 * The odds are that this will stop walking way
	 * beक्रमe end_vaddr, because the length of the
	 * user buffer is tracked in "pm", and the walk
	 * will stop when we hit the end of the buffer.
	 */
	ret = 0;
	जबतक (count && (start_vaddr < end_vaddr)) अणु
		पूर्णांक len;
		अचिन्हित दीर्घ end;

		pm.pos = 0;
		end = (start_vaddr + PAGEMAP_WALK_SIZE) & PAGEMAP_WALK_MASK;
		/* overflow ? */
		अगर (end < start_vaddr || end > end_vaddr)
			end = end_vaddr;
		ret = mmap_पढ़ो_lock_समाप्तable(mm);
		अगर (ret)
			जाओ out_मुक्त;
		ret = walk_page_range(mm, start_vaddr, end, &pagemap_ops, &pm);
		mmap_पढ़ो_unlock(mm);
		start_vaddr = end;

		len = min(count, PM_ENTRY_BYTES * pm.pos);
		अगर (copy_to_user(buf, pm.buffer, len)) अणु
			ret = -EFAULT;
			जाओ out_मुक्त;
		पूर्ण
		copied += len;
		buf += len;
		count -= len;
	पूर्ण
	*ppos += copied;
	अगर (!ret || ret == PM_END_OF_BUFFER)
		ret = copied;

out_मुक्त:
	kमुक्त(pm.buffer);
out_mm:
	mmput(mm);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक pagemap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mm_काष्ठा *mm;

	mm = proc_mem_खोलो(inode, PTRACE_MODE_READ);
	अगर (IS_ERR(mm))
		वापस PTR_ERR(mm);
	file->निजी_data = mm;
	वापस 0;
पूर्ण

अटल पूर्णांक pagemap_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mm_काष्ठा *mm = file->निजी_data;

	अगर (mm)
		mmdrop(mm);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations proc_pagemap_operations = अणु
	.llseek		= mem_lseek, /* borrow this */
	.पढ़ो		= pagemap_पढ़ो,
	.खोलो		= pagemap_खोलो,
	.release	= pagemap_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_PAGE_MONITOR */

#अगर_घोषित CONFIG_NUMA

काष्ठा numa_maps अणु
	अचिन्हित दीर्घ pages;
	अचिन्हित दीर्घ anon;
	अचिन्हित दीर्घ active;
	अचिन्हित दीर्घ ग_लिखोback;
	अचिन्हित दीर्घ mapcount_max;
	अचिन्हित दीर्घ dirty;
	अचिन्हित दीर्घ swapcache;
	अचिन्हित दीर्घ node[MAX_NUMNODES];
पूर्ण;

काष्ठा numa_maps_निजी अणु
	काष्ठा proc_maps_निजी proc_maps;
	काष्ठा numa_maps md;
पूर्ण;

अटल व्योम gather_stats(काष्ठा page *page, काष्ठा numa_maps *md, पूर्णांक pte_dirty,
			अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक count = page_mapcount(page);

	md->pages += nr_pages;
	अगर (pte_dirty || PageDirty(page))
		md->dirty += nr_pages;

	अगर (PageSwapCache(page))
		md->swapcache += nr_pages;

	अगर (PageActive(page) || PageUnevictable(page))
		md->active += nr_pages;

	अगर (PageWriteback(page))
		md->ग_लिखोback += nr_pages;

	अगर (PageAnon(page))
		md->anon += nr_pages;

	अगर (count > md->mapcount_max)
		md->mapcount_max = count;

	md->node[page_to_nid(page)] += nr_pages;
पूर्ण

अटल काष्ठा page *can_gather_numa_stats(pte_t pte, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	पूर्णांक nid;

	अगर (!pte_present(pte))
		वापस शून्य;

	page = vm_normal_page(vma, addr, pte);
	अगर (!page)
		वापस शून्य;

	अगर (PageReserved(page))
		वापस शून्य;

	nid = page_to_nid(page);
	अगर (!node_isset(nid, node_states[N_MEMORY]))
		वापस शून्य;

	वापस page;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल काष्ठा page *can_gather_numa_stats_pmd(pmd_t pmd,
					      काष्ठा vm_area_काष्ठा *vma,
					      अचिन्हित दीर्घ addr)
अणु
	काष्ठा page *page;
	पूर्णांक nid;

	अगर (!pmd_present(pmd))
		वापस शून्य;

	page = vm_normal_page_pmd(vma, addr, pmd);
	अगर (!page)
		वापस शून्य;

	अगर (PageReserved(page))
		वापस शून्य;

	nid = page_to_nid(page);
	अगर (!node_isset(nid, node_states[N_MEMORY]))
		वापस शून्य;

	वापस page;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक gather_pte_stats(pmd_t *pmd, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा numa_maps *md = walk->निजी;
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	spinlock_t *ptl;
	pte_t *orig_pte;
	pte_t *pte;

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
	ptl = pmd_trans_huge_lock(pmd, vma);
	अगर (ptl) अणु
		काष्ठा page *page;

		page = can_gather_numa_stats_pmd(*pmd, vma, addr);
		अगर (page)
			gather_stats(page, md, pmd_dirty(*pmd),
				     HPAGE_PMD_SIZE/PAGE_SIZE);
		spin_unlock(ptl);
		वापस 0;
	पूर्ण

	अगर (pmd_trans_unstable(pmd))
		वापस 0;
#पूर्ण_अगर
	orig_pte = pte = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	करो अणु
		काष्ठा page *page = can_gather_numa_stats(*pte, vma, addr);
		अगर (!page)
			जारी;
		gather_stats(page, md, pte_dirty(*pte), 1);

	पूर्ण जबतक (pte++, addr += PAGE_SIZE, addr != end);
	pte_unmap_unlock(orig_pte, ptl);
	cond_resched();
	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल पूर्णांक gather_hugetlb_stats(pte_t *pte, अचिन्हित दीर्घ hmask,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	pte_t huge_pte = huge_ptep_get(pte);
	काष्ठा numa_maps *md;
	काष्ठा page *page;

	अगर (!pte_present(huge_pte))
		वापस 0;

	page = pte_page(huge_pte);
	अगर (!page)
		वापस 0;

	md = walk->निजी;
	gather_stats(page, md, pte_dirty(huge_pte), 1);
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक gather_hugetlb_stats(pte_t *pte, अचिन्हित दीर्घ hmask,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा mm_walk_ops show_numa_ops = अणु
	.hugetlb_entry = gather_hugetlb_stats,
	.pmd_entry = gather_pte_stats,
पूर्ण;

/*
 * Display pages allocated per node and memory policy via /proc.
 */
अटल पूर्णांक show_numa_map(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा numa_maps_निजी *numa_priv = m->निजी;
	काष्ठा proc_maps_निजी *proc_priv = &numa_priv->proc_maps;
	काष्ठा vm_area_काष्ठा *vma = v;
	काष्ठा numa_maps *md = &numa_priv->md;
	काष्ठा file *file = vma->vm_file;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा mempolicy *pol;
	अक्षर buffer[64];
	पूर्णांक nid;

	अगर (!mm)
		वापस 0;

	/* Ensure we start with an empty set of numa_maps statistics. */
	स_रखो(md, 0, माप(*md));

	pol = __get_vma_policy(vma, vma->vm_start);
	अगर (pol) अणु
		mpol_to_str(buffer, माप(buffer), pol);
		mpol_cond_put(pol);
	पूर्ण अन्यथा अणु
		mpol_to_str(buffer, माप(buffer), proc_priv->task_mempolicy);
	पूर्ण

	seq_म_लिखो(m, "%08lx %s", vma->vm_start, buffer);

	अगर (file) अणु
		seq_माला_दो(m, " file=");
		seq_file_path(m, file, "\n\t= ");
	पूर्ण अन्यथा अगर (vma->vm_start <= mm->brk && vma->vm_end >= mm->start_brk) अणु
		seq_माला_दो(m, " heap");
	पूर्ण अन्यथा अगर (is_stack(vma)) अणु
		seq_माला_दो(m, " stack");
	पूर्ण

	अगर (is_vm_hugetlb_page(vma))
		seq_माला_दो(m, " huge");

	/* mmap_lock is held by m_start */
	walk_page_vma(vma, &show_numa_ops, md);

	अगर (!md->pages)
		जाओ out;

	अगर (md->anon)
		seq_म_लिखो(m, " anon=%lu", md->anon);

	अगर (md->dirty)
		seq_म_लिखो(m, " dirty=%lu", md->dirty);

	अगर (md->pages != md->anon && md->pages != md->dirty)
		seq_म_लिखो(m, " mapped=%lu", md->pages);

	अगर (md->mapcount_max > 1)
		seq_म_लिखो(m, " mapmax=%lu", md->mapcount_max);

	अगर (md->swapcache)
		seq_म_लिखो(m, " swapcache=%lu", md->swapcache);

	अगर (md->active < md->pages && !is_vm_hugetlb_page(vma))
		seq_म_लिखो(m, " active=%lu", md->active);

	अगर (md->ग_लिखोback)
		seq_म_लिखो(m, " writeback=%lu", md->ग_लिखोback);

	क्रम_each_node_state(nid, N_MEMORY)
		अगर (md->node[nid])
			seq_म_लिखो(m, " N%d=%lu", nid, md->node[nid]);

	seq_म_लिखो(m, " kernelpagesize_kB=%lu", vma_kernel_pagesize(vma) >> 10);
out:
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_pid_numa_maps_op = अणु
	.start  = m_start,
	.next   = m_next,
	.stop   = m_stop,
	.show   = show_numa_map,
पूर्ण;

अटल पूर्णांक pid_numa_maps_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस proc_maps_खोलो(inode, file, &proc_pid_numa_maps_op,
				माप(काष्ठा numa_maps_निजी));
पूर्ण

स्थिर काष्ठा file_operations proc_pid_numa_maps_operations = अणु
	.खोलो		= pid_numa_maps_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_map_release,
पूर्ण;

#पूर्ण_अगर /* CONFIG_NUMA */

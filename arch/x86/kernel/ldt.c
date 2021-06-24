<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992 Krishna Balasubramanian and Linus Torvalds
 * Copyright (C) 1999 Ingo Molnar <mingo@redhat.com>
 * Copyright (C) 2002 Andi Kleen
 *
 * This handles calls from both 32bit and 64bit mode.
 *
 * Lock order:
 *	contex.ldt_usr_sem
 *	  mmap_lock
 *	    context.lock
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgtable_areas.h>

#समावेश <xen/xen.h>

/* This is a multiple of PAGE_SIZE. */
#घोषणा LDT_SLOT_STRIDE (LDT_ENTRIES * LDT_ENTRY_SIZE)

अटल अंतरभूत व्योम *ldt_slot_va(पूर्णांक slot)
अणु
	वापस (व्योम *)(LDT_BASE_ADDR + LDT_SLOT_STRIDE * slot);
पूर्ण

व्योम load_mm_ldt(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा ldt_काष्ठा *ldt;

	/* READ_ONCE synchronizes with smp_store_release */
	ldt = READ_ONCE(mm->context.ldt);

	/*
	 * Any change to mm->context.ldt is followed by an IPI to all
	 * CPUs with the mm active.  The LDT will not be मुक्तd until
	 * after the IPI is handled by all such CPUs.  This means that,
	 * अगर the ldt_काष्ठा changes beक्रमe we वापस, the values we see
	 * will be safe, and the new values will be loaded beक्रमe we run
	 * any user code.
	 *
	 * NB: करोn't try to convert this to use RCU without extreme care.
	 * We would still need IRQs off, because we करोn't want to change
	 * the local LDT after an IPI loaded a newer value than the one
	 * that we can see.
	 */

	अगर (unlikely(ldt)) अणु
		अगर (अटल_cpu_has(X86_FEATURE_PTI)) अणु
			अगर (WARN_ON_ONCE((अचिन्हित दीर्घ)ldt->slot > 1)) अणु
				/*
				 * Whoops -- either the new LDT isn't mapped
				 * (अगर slot == -1) or is mapped पूर्णांकo a bogus
				 * slot (अगर slot > 1).
				 */
				clear_LDT();
				वापस;
			पूर्ण

			/*
			 * If page table isolation is enabled, ldt->entries
			 * will not be mapped in the userspace pagetables.
			 * Tell the CPU to access the LDT through the alias
			 * at ldt_slot_va(ldt->slot).
			 */
			set_ldt(ldt_slot_va(ldt->slot), ldt->nr_entries);
		पूर्ण अन्यथा अणु
			set_ldt(ldt->entries, ldt->nr_entries);
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_LDT();
	पूर्ण
पूर्ण

व्योम चयन_ldt(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	/*
	 * Load the LDT अगर either the old or new mm had an LDT.
	 *
	 * An mm will never go from having an LDT to not having an LDT.  Two
	 * mms never share an LDT, so we करोn't gain anything by checking to
	 * see whether the LDT changed.  There's also no guarantee that
	 * prev->context.ldt actually matches LDTR, but, अगर LDTR is non-शून्य,
	 * then prev->context.ldt will also be non-शून्य.
	 *
	 * If we really cared, we could optimize the हाल where prev == next
	 * and we're निकासing lazy mode.  Most of the समय, अगर this happens,
	 * we करोn't actually need to reload LDTR, but modअगरy_ldt() is mostly
	 * used by legacy code and emulators where we करोn't need this level of
	 * perक्रमmance.
	 *
	 * This uses | instead of || because it generates better code.
	 */
	अगर (unlikely((अचिन्हित दीर्घ)prev->context.ldt |
		     (अचिन्हित दीर्घ)next->context.ldt))
		load_mm_ldt(next);

	DEBUG_LOCKS_WARN_ON(preemptible());
पूर्ण

अटल व्योम refresh_ldt_segments(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	अचिन्हित लघु sel;

	/*
	 * Make sure that the cached DS and ES descriptors match the updated
	 * LDT.
	 */
	savesegment(ds, sel);
	अगर ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT)
		loadsegment(ds, sel);

	savesegment(es, sel);
	अगर ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT)
		loadsegment(es, sel);
#पूर्ण_अगर
पूर्ण

/* context.lock is held by the task which issued the smp function call */
अटल व्योम flush_ldt(व्योम *__mm)
अणु
	काष्ठा mm_काष्ठा *mm = __mm;

	अगर (this_cpu_पढ़ो(cpu_tlbstate.loaded_mm) != mm)
		वापस;

	load_mm_ldt(mm);

	refresh_ldt_segments();
पूर्ण

/* The caller must call finalize_ldt_काष्ठा on the result. LDT starts zeroed. */
अटल काष्ठा ldt_काष्ठा *alloc_ldt_काष्ठा(अचिन्हित पूर्णांक num_entries)
अणु
	काष्ठा ldt_काष्ठा *new_ldt;
	अचिन्हित पूर्णांक alloc_size;

	अगर (num_entries > LDT_ENTRIES)
		वापस शून्य;

	new_ldt = kदो_स्मृति(माप(काष्ठा ldt_काष्ठा), GFP_KERNEL);
	अगर (!new_ldt)
		वापस शून्य;

	BUILD_BUG_ON(LDT_ENTRY_SIZE != माप(काष्ठा desc_काष्ठा));
	alloc_size = num_entries * LDT_ENTRY_SIZE;

	/*
	 * Xen is very picky: it requires a page-aligned LDT that has no
	 * trailing nonzero bytes in any page that contains LDT descriptors.
	 * Keep it simple: zero the whole allocation and never allocate less
	 * than PAGE_SIZE.
	 */
	अगर (alloc_size > PAGE_SIZE)
		new_ldt->entries = vzalloc(alloc_size);
	अन्यथा
		new_ldt->entries = (व्योम *)get_zeroed_page(GFP_KERNEL);

	अगर (!new_ldt->entries) अणु
		kमुक्त(new_ldt);
		वापस शून्य;
	पूर्ण

	/* The new LDT isn't aliased क्रम PTI yet. */
	new_ldt->slot = -1;

	new_ldt->nr_entries = num_entries;
	वापस new_ldt;
पूर्ण

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION

अटल व्योम करो_sanity_check(काष्ठा mm_काष्ठा *mm,
			    bool had_kernel_mapping,
			    bool had_user_mapping)
अणु
	अगर (mm->context.ldt) अणु
		/*
		 * We alपढ़ोy had an LDT.  The top-level entry should alपढ़ोy
		 * have been allocated and synchronized with the usermode
		 * tables.
		 */
		WARN_ON(!had_kernel_mapping);
		अगर (boot_cpu_has(X86_FEATURE_PTI))
			WARN_ON(!had_user_mapping);
	पूर्ण अन्यथा अणु
		/*
		 * This is the first समय we're mapping an LDT क्रम this process.
		 * Sync the pgd to the usermode tables.
		 */
		WARN_ON(had_kernel_mapping);
		अगर (boot_cpu_has(X86_FEATURE_PTI))
			WARN_ON(had_user_mapping);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_PAE

अटल pmd_t *pgd_to_pmd_walk(pgd_t *pgd, अचिन्हित दीर्घ va)
अणु
	p4d_t *p4d;
	pud_t *pud;

	अगर (pgd->pgd == 0)
		वापस शून्य;

	p4d = p4d_offset(pgd, va);
	अगर (p4d_none(*p4d))
		वापस शून्य;

	pud = pud_offset(p4d, va);
	अगर (pud_none(*pud))
		वापस शून्य;

	वापस pmd_offset(pud, va);
पूर्ण

अटल व्योम map_ldt_काष्ठा_to_user(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *k_pgd = pgd_offset(mm, LDT_BASE_ADDR);
	pgd_t *u_pgd = kernel_to_user_pgdp(k_pgd);
	pmd_t *k_pmd, *u_pmd;

	k_pmd = pgd_to_pmd_walk(k_pgd, LDT_BASE_ADDR);
	u_pmd = pgd_to_pmd_walk(u_pgd, LDT_BASE_ADDR);

	अगर (boot_cpu_has(X86_FEATURE_PTI) && !mm->context.ldt)
		set_pmd(u_pmd, *k_pmd);
पूर्ण

अटल व्योम sanity_check_ldt_mapping(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *k_pgd = pgd_offset(mm, LDT_BASE_ADDR);
	pgd_t *u_pgd = kernel_to_user_pgdp(k_pgd);
	bool had_kernel, had_user;
	pmd_t *k_pmd, *u_pmd;

	k_pmd      = pgd_to_pmd_walk(k_pgd, LDT_BASE_ADDR);
	u_pmd      = pgd_to_pmd_walk(u_pgd, LDT_BASE_ADDR);
	had_kernel = (k_pmd->pmd != 0);
	had_user   = (u_pmd->pmd != 0);

	करो_sanity_check(mm, had_kernel, had_user);
पूर्ण

#अन्यथा /* !CONFIG_X86_PAE */

अटल व्योम map_ldt_काष्ठा_to_user(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd = pgd_offset(mm, LDT_BASE_ADDR);

	अगर (boot_cpu_has(X86_FEATURE_PTI) && !mm->context.ldt)
		set_pgd(kernel_to_user_pgdp(pgd), *pgd);
पूर्ण

अटल व्योम sanity_check_ldt_mapping(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd = pgd_offset(mm, LDT_BASE_ADDR);
	bool had_kernel = (pgd->pgd != 0);
	bool had_user   = (kernel_to_user_pgdp(pgd)->pgd != 0);

	करो_sanity_check(mm, had_kernel, had_user);
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_PAE */

/*
 * If PTI is enabled, this maps the LDT पूर्णांकo the kernelmode and
 * usermode tables क्रम the given mm.
 */
अटल पूर्णांक
map_ldt_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा ldt_काष्ठा *ldt, पूर्णांक slot)
अणु
	अचिन्हित दीर्घ va;
	bool is_vदो_स्मृति;
	spinlock_t *ptl;
	पूर्णांक i, nr_pages;

	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस 0;

	/*
	 * Any given ldt_काष्ठा should have map_ldt_काष्ठा() called at most
	 * once.
	 */
	WARN_ON(ldt->slot != -1);

	/* Check अगर the current mappings are sane */
	sanity_check_ldt_mapping(mm);

	is_vदो_स्मृति = is_vदो_स्मृति_addr(ldt->entries);

	nr_pages = DIV_ROUND_UP(ldt->nr_entries * LDT_ENTRY_SIZE, PAGE_SIZE);

	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित दीर्घ offset = i << PAGE_SHIFT;
		स्थिर व्योम *src = (अक्षर *)ldt->entries + offset;
		अचिन्हित दीर्घ pfn;
		pgprot_t pte_prot;
		pte_t pte, *ptep;

		va = (अचिन्हित दीर्घ)ldt_slot_va(slot) + offset;
		pfn = is_vदो_स्मृति ? vदो_स्मृति_to_pfn(src) :
			page_to_pfn(virt_to_page(src));
		/*
		 * Treat the PTI LDT range as a *userspace* range.
		 * get_locked_pte() will allocate all needed pagetables
		 * and account क्रम them in this mm.
		 */
		ptep = get_locked_pte(mm, va, &ptl);
		अगर (!ptep)
			वापस -ENOMEM;
		/*
		 * Map it RO so the easy to find address is not a primary
		 * target via some kernel पूर्णांकerface which misses a
		 * permission check.
		 */
		pte_prot = __pgprot(__PAGE_KERNEL_RO & ~_PAGE_GLOBAL);
		/* Filter out unsuppored __PAGE_KERNEL* bits: */
		pgprot_val(pte_prot) &= __supported_pte_mask;
		pte = pfn_pte(pfn, pte_prot);
		set_pte_at(mm, va, ptep, pte);
		pte_unmap_unlock(ptep, ptl);
	पूर्ण

	/* Propagate LDT mapping to the user page-table */
	map_ldt_काष्ठा_to_user(mm);

	ldt->slot = slot;
	वापस 0;
पूर्ण

अटल व्योम unmap_ldt_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा ldt_काष्ठा *ldt)
अणु
	अचिन्हित दीर्घ va;
	पूर्णांक i, nr_pages;

	अगर (!ldt)
		वापस;

	/* LDT map/unmap is only required क्रम PTI */
	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस;

	nr_pages = DIV_ROUND_UP(ldt->nr_entries * LDT_ENTRY_SIZE, PAGE_SIZE);

	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित दीर्घ offset = i << PAGE_SHIFT;
		spinlock_t *ptl;
		pte_t *ptep;

		va = (अचिन्हित दीर्घ)ldt_slot_va(ldt->slot) + offset;
		ptep = get_locked_pte(mm, va, &ptl);
		pte_clear(mm, va, ptep);
		pte_unmap_unlock(ptep, ptl);
	पूर्ण

	va = (अचिन्हित दीर्घ)ldt_slot_va(ldt->slot);
	flush_tlb_mm_range(mm, va, va + nr_pages * PAGE_SIZE, PAGE_SHIFT, false);
पूर्ण

#अन्यथा /* !CONFIG_PAGE_TABLE_ISOLATION */

अटल पूर्णांक
map_ldt_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा ldt_काष्ठा *ldt, पूर्णांक slot)
अणु
	वापस 0;
पूर्ण

अटल व्योम unmap_ldt_काष्ठा(काष्ठा mm_काष्ठा *mm, काष्ठा ldt_काष्ठा *ldt)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PAGE_TABLE_ISOLATION */

अटल व्योम मुक्त_ldt_pgtables(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
	काष्ठा mmu_gather tlb;
	अचिन्हित दीर्घ start = LDT_BASE_ADDR;
	अचिन्हित दीर्घ end = LDT_END_ADDR;

	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस;

	/*
	 * Although मुक्त_pgd_range() is पूर्णांकended क्रम मुक्तing user
	 * page-tables, it also works out क्रम kernel mappings on x86.
	 * We use tlb_gather_mmu_fullmm() to aव्योम confusing the
	 * range-tracking logic in __tlb_adjust_range().
	 */
	tlb_gather_mmu_fullmm(&tlb, mm);
	मुक्त_pgd_range(&tlb, start, end, start, end);
	tlb_finish_mmu(&tlb);
#पूर्ण_अगर
पूर्ण

/* After calling this, the LDT is immutable. */
अटल व्योम finalize_ldt_काष्ठा(काष्ठा ldt_काष्ठा *ldt)
अणु
	paravirt_alloc_ldt(ldt->entries, ldt->nr_entries);
पूर्ण

अटल व्योम install_ldt(काष्ठा mm_काष्ठा *mm, काष्ठा ldt_काष्ठा *ldt)
अणु
	mutex_lock(&mm->context.lock);

	/* Synchronizes with READ_ONCE in load_mm_ldt. */
	smp_store_release(&mm->context.ldt, ldt);

	/* Activate the LDT क्रम all CPUs using currents mm. */
	on_each_cpu_mask(mm_cpumask(mm), flush_ldt, mm, true);

	mutex_unlock(&mm->context.lock);
पूर्ण

अटल व्योम मुक्त_ldt_काष्ठा(काष्ठा ldt_काष्ठा *ldt)
अणु
	अगर (likely(!ldt))
		वापस;

	paravirt_मुक्त_ldt(ldt->entries, ldt->nr_entries);
	अगर (ldt->nr_entries * LDT_ENTRY_SIZE > PAGE_SIZE)
		vमुक्त_atomic(ldt->entries);
	अन्यथा
		मुक्त_page((अचिन्हित दीर्घ)ldt->entries);
	kमुक्त(ldt);
पूर्ण

/*
 * Called on विभाजन from arch_dup_mmap(). Just copy the current LDT state,
 * the new task is not running, so nothing can be installed.
 */
पूर्णांक ldt_dup_context(काष्ठा mm_काष्ठा *old_mm, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा ldt_काष्ठा *new_ldt;
	पूर्णांक retval = 0;

	अगर (!old_mm)
		वापस 0;

	mutex_lock(&old_mm->context.lock);
	अगर (!old_mm->context.ldt)
		जाओ out_unlock;

	new_ldt = alloc_ldt_काष्ठा(old_mm->context.ldt->nr_entries);
	अगर (!new_ldt) अणु
		retval = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	स_नकल(new_ldt->entries, old_mm->context.ldt->entries,
	       new_ldt->nr_entries * LDT_ENTRY_SIZE);
	finalize_ldt_काष्ठा(new_ldt);

	retval = map_ldt_काष्ठा(mm, new_ldt, 0);
	अगर (retval) अणु
		मुक्त_ldt_pgtables(mm);
		मुक्त_ldt_काष्ठा(new_ldt);
		जाओ out_unlock;
	पूर्ण
	mm->context.ldt = new_ldt;

out_unlock:
	mutex_unlock(&old_mm->context.lock);
	वापस retval;
पूर्ण

/*
 * No need to lock the MM as we are the last user
 *
 * 64bit: Don't touch the LDT register - we're alपढ़ोy in the next thपढ़ो.
 */
व्योम destroy_context_ldt(काष्ठा mm_काष्ठा *mm)
अणु
	मुक्त_ldt_काष्ठा(mm->context.ldt);
	mm->context.ldt = शून्य;
पूर्ण

व्योम ldt_arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	मुक्त_ldt_pgtables(mm);
पूर्ण

अटल पूर्णांक पढ़ो_ldt(व्योम __user *ptr, अचिन्हित दीर्घ bytecount)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ entries_size;
	पूर्णांक retval;

	करोwn_पढ़ो(&mm->context.ldt_usr_sem);

	अगर (!mm->context.ldt) अणु
		retval = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (bytecount > LDT_ENTRY_SIZE * LDT_ENTRIES)
		bytecount = LDT_ENTRY_SIZE * LDT_ENTRIES;

	entries_size = mm->context.ldt->nr_entries * LDT_ENTRY_SIZE;
	अगर (entries_size > bytecount)
		entries_size = bytecount;

	अगर (copy_to_user(ptr, mm->context.ldt->entries, entries_size)) अणु
		retval = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	अगर (entries_size != bytecount) अणु
		/* Zero-fill the rest and pretend we पढ़ो bytecount bytes. */
		अगर (clear_user(ptr + entries_size, bytecount - entries_size)) अणु
			retval = -EFAULT;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	retval = bytecount;

out_unlock:
	up_पढ़ो(&mm->context.ldt_usr_sem);
	वापस retval;
पूर्ण

अटल पूर्णांक पढ़ो_शेष_ldt(व्योम __user *ptr, अचिन्हित दीर्घ bytecount)
अणु
	/* CHECKME: Can we use _one_ अक्रमom number ? */
#अगर_घोषित CONFIG_X86_32
	अचिन्हित दीर्घ size = 5 * माप(काष्ठा desc_काष्ठा);
#अन्यथा
	अचिन्हित दीर्घ size = 128;
#पूर्ण_अगर
	अगर (bytecount > size)
		bytecount = size;
	अगर (clear_user(ptr, bytecount))
		वापस -EFAULT;
	वापस bytecount;
पूर्ण

अटल bool allow_16bit_segments(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_X86_16BIT))
		वापस false;

#अगर_घोषित CONFIG_XEN_PV
	/*
	 * Xen PV करोes not implement ESPFIX64, which means that 16-bit
	 * segments will not work correctly.  Until either Xen PV implements
	 * ESPFIX64 and can संकेत this fact to the guest or unless someone
	 * provides compelling evidence that allowing broken 16-bit segments
	 * is worthजबतक, disallow 16-bit segments under Xen PV.
	 */
	अगर (xen_pv_करोमुख्य()) अणु
		pr_info_once("Warning: 16-bit segments do not work correctly in a Xen PV guest\n");
		वापस false;
	पूर्ण
#पूर्ण_अगर

	वापस true;
पूर्ण

अटल पूर्णांक ग_लिखो_ldt(व्योम __user *ptr, अचिन्हित दीर्घ bytecount, पूर्णांक oldmode)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा ldt_काष्ठा *new_ldt, *old_ldt;
	अचिन्हित पूर्णांक old_nr_entries, new_nr_entries;
	काष्ठा user_desc ldt_info;
	काष्ठा desc_काष्ठा ldt;
	पूर्णांक error;

	error = -EINVAL;
	अगर (bytecount != माप(ldt_info))
		जाओ out;
	error = -EFAULT;
	अगर (copy_from_user(&ldt_info, ptr, माप(ldt_info)))
		जाओ out;

	error = -EINVAL;
	अगर (ldt_info.entry_number >= LDT_ENTRIES)
		जाओ out;
	अगर (ldt_info.contents == 3) अणु
		अगर (oldmode)
			जाओ out;
		अगर (ldt_info.seg_not_present == 0)
			जाओ out;
	पूर्ण

	अगर ((oldmode && !ldt_info.base_addr && !ldt_info.limit) ||
	    LDT_empty(&ldt_info)) अणु
		/* The user wants to clear the entry. */
		स_रखो(&ldt, 0, माप(ldt));
	पूर्ण अन्यथा अणु
		अगर (!ldt_info.seg_32bit && !allow_16bit_segments()) अणु
			error = -EINVAL;
			जाओ out;
		पूर्ण

		fill_ldt(&ldt, &ldt_info);
		अगर (oldmode)
			ldt.avl = 0;
	पूर्ण

	अगर (करोwn_ग_लिखो_समाप्तable(&mm->context.ldt_usr_sem))
		वापस -EINTR;

	old_ldt       = mm->context.ldt;
	old_nr_entries = old_ldt ? old_ldt->nr_entries : 0;
	new_nr_entries = max(ldt_info.entry_number + 1, old_nr_entries);

	error = -ENOMEM;
	new_ldt = alloc_ldt_काष्ठा(new_nr_entries);
	अगर (!new_ldt)
		जाओ out_unlock;

	अगर (old_ldt)
		स_नकल(new_ldt->entries, old_ldt->entries, old_nr_entries * LDT_ENTRY_SIZE);

	new_ldt->entries[ldt_info.entry_number] = ldt;
	finalize_ldt_काष्ठा(new_ldt);

	/*
	 * If we are using PTI, map the new LDT पूर्णांकo the userspace pagetables.
	 * If there is alपढ़ोy an LDT, use the other slot so that other CPUs
	 * will जारी to use the old LDT until install_ldt() चयनes
	 * them over to the new LDT.
	 */
	error = map_ldt_काष्ठा(mm, new_ldt, old_ldt ? !old_ldt->slot : 0);
	अगर (error) अणु
		/*
		 * This only can fail क्रम the first LDT setup. If an LDT is
		 * alपढ़ोy installed then the PTE page is alपढ़ोy
		 * populated. Mop up a half populated page table.
		 */
		अगर (!WARN_ON_ONCE(old_ldt))
			मुक्त_ldt_pgtables(mm);
		मुक्त_ldt_काष्ठा(new_ldt);
		जाओ out_unlock;
	पूर्ण

	install_ldt(mm, new_ldt);
	unmap_ldt_काष्ठा(mm, old_ldt);
	मुक्त_ldt_काष्ठा(old_ldt);
	error = 0;

out_unlock:
	up_ग_लिखो(&mm->context.ldt_usr_sem);
out:
	वापस error;
पूर्ण

SYSCALL_DEFINE3(modअगरy_ldt, पूर्णांक , func , व्योम __user * , ptr ,
		अचिन्हित दीर्घ , bytecount)
अणु
	पूर्णांक ret = -ENOSYS;

	चयन (func) अणु
	हाल 0:
		ret = पढ़ो_ldt(ptr, bytecount);
		अवरोध;
	हाल 1:
		ret = ग_लिखो_ldt(ptr, bytecount, 1);
		अवरोध;
	हाल 2:
		ret = पढ़ो_शेष_ldt(ptr, bytecount);
		अवरोध;
	हाल 0x11:
		ret = ग_लिखो_ldt(ptr, bytecount, 0);
		अवरोध;
	पूर्ण
	/*
	 * The SYSCALL_DEFINE() macros give us an 'unsigned long'
	 * वापस type, but tht ABI क्रम sys_modअगरy_ldt() expects
	 * 'int'.  This cast gives us an पूर्णांक-sized value in %rax
	 * क्रम the वापस code.  The 'unsigned' is necessary so
	 * the compiler करोes not try to sign-extend the negative
	 * वापस codes पूर्णांकo the high half of the रेजिस्टर when
	 * taking the value from पूर्णांक->दीर्घ.
	 */
	वापस (अचिन्हित पूर्णांक)ret;
पूर्ण

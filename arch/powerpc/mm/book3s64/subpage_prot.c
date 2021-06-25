<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007-2008 Paul Mackerras, IBM Corp.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/syscalls.h>

#समावेश <linux/pgtable.h>
#समावेश <linux/uaccess.h>

/*
 * Free all pages allocated क्रम subpage protection maps and poपूर्णांकers.
 * Also makes sure that the subpage_prot_table काष्ठाure is
 * reinitialized क्रम the next user.
 */
व्योम subpage_prot_मुक्त(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा subpage_prot_table *spt = mm_ctx_subpage_prot(&mm->context);
	अचिन्हित दीर्घ i, j, addr;
	u32 **p;

	अगर (!spt)
		वापस;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (spt->low_prot[i]) अणु
			मुक्त_page((अचिन्हित दीर्घ)spt->low_prot[i]);
			spt->low_prot[i] = शून्य;
		पूर्ण
	पूर्ण
	addr = 0;
	क्रम (i = 0; i < (TASK_SIZE_USER64 >> 43); ++i) अणु
		p = spt->protptrs[i];
		अगर (!p)
			जारी;
		spt->protptrs[i] = शून्य;
		क्रम (j = 0; j < SBP_L2_COUNT && addr < spt->maxaddr;
		     ++j, addr += PAGE_SIZE)
			अगर (p[j])
				मुक्त_page((अचिन्हित दीर्घ)p[j]);
		मुक्त_page((अचिन्हित दीर्घ)p);
	पूर्ण
	spt->maxaddr = 0;
	kमुक्त(spt);
पूर्ण

अटल व्योम hpte_flush_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			     पूर्णांक npages)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	spinlock_t *ptl;

	pgd = pgd_offset(mm, addr);
	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस;
	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस;
	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस;
	pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	arch_enter_lazy_mmu_mode();
	क्रम (; npages > 0; --npages) अणु
		pte_update(mm, addr, pte, 0, 0, 0);
		addr += PAGE_SIZE;
		++pte;
	पूर्ण
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(pte - 1, ptl);
पूर्ण

/*
 * Clear the subpage protection map क्रम an address range, allowing
 * all accesses that are allowed by the pte permissions.
 */
अटल व्योम subpage_prot_clear(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा subpage_prot_table *spt;
	u32 **spm, *spp;
	अचिन्हित दीर्घ i;
	माप_प्रकार nw;
	अचिन्हित दीर्घ next, limit;

	mmap_ग_लिखो_lock(mm);

	spt = mm_ctx_subpage_prot(&mm->context);
	अगर (!spt)
		जाओ err_out;

	limit = addr + len;
	अगर (limit > spt->maxaddr)
		limit = spt->maxaddr;
	क्रम (; addr < limit; addr = next) अणु
		next = pmd_addr_end(addr, limit);
		अगर (addr < 0x100000000UL) अणु
			spm = spt->low_prot;
		पूर्ण अन्यथा अणु
			spm = spt->protptrs[addr >> SBP_L3_SHIFT];
			अगर (!spm)
				जारी;
		पूर्ण
		spp = spm[(addr >> SBP_L2_SHIFT) & (SBP_L2_COUNT - 1)];
		अगर (!spp)
			जारी;
		spp += (addr >> PAGE_SHIFT) & (SBP_L1_COUNT - 1);

		i = (addr >> PAGE_SHIFT) & (PTRS_PER_PTE - 1);
		nw = PTRS_PER_PTE - i;
		अगर (addr + (nw << PAGE_SHIFT) > next)
			nw = (next - addr) >> PAGE_SHIFT;

		स_रखो(spp, 0, nw * माप(u32));

		/* now flush any existing HPTEs क्रम the range */
		hpte_flush_range(mm, addr, nw);
	पूर्ण

err_out:
	mmap_ग_लिखो_unlock(mm);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल पूर्णांक subpage_walk_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;
	split_huge_pmd(vma, pmd, addr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops subpage_walk_ops = अणु
	.pmd_entry	= subpage_walk_pmd_entry,
पूर्ण;

अटल व्योम subpage_mark_vma_nohuge(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ len)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * We करोn't try too hard, we just mark all the vma in that range
	 * VM_NOHUGEPAGE and split them.
	 */
	vma = find_vma(mm, addr);
	/*
	 * If the range is in unmapped range, just वापस
	 */
	अगर (vma && ((addr + len) <= vma->vm_start))
		वापस;

	जबतक (vma) अणु
		अगर (vma->vm_start >= (addr + len))
			अवरोध;
		vma->vm_flags |= VM_NOHUGEPAGE;
		walk_page_vma(vma, &subpage_walk_ops, शून्य);
		vma = vma->vm_next;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम subpage_mark_vma_nohuge(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ len)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

/*
 * Copy in a subpage protection map क्रम an address range.
 * The map has 2 bits per 4k subpage, so 32 bits per 64k page.
 * Each 2-bit field is 0 to allow any access, 1 to prevent ग_लिखोs,
 * 2 or 3 to prevent all accesses.
 * Note that the normal page protections also apply; the subpage
 * protection mechanism is an additional स्थिरraपूर्णांक, so putting 0
 * in a 2-bit field won't allow ग_लिखोs to a page that is otherwise
 * ग_लिखो-रक्षित.
 */
SYSCALL_DEFINE3(subpage_prot, अचिन्हित दीर्घ, addr,
		अचिन्हित दीर्घ, len, u32 __user *, map)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा subpage_prot_table *spt;
	u32 **spm, *spp;
	अचिन्हित दीर्घ i;
	माप_प्रकार nw;
	अचिन्हित दीर्घ next, limit;
	पूर्णांक err;

	अगर (radix_enabled())
		वापस -ENOENT;

	/* Check parameters */
	अगर ((addr & ~PAGE_MASK) || (len & ~PAGE_MASK) ||
	    addr >= mm->task_size || len >= mm->task_size ||
	    addr + len > mm->task_size)
		वापस -EINVAL;

	अगर (is_hugepage_only_range(mm, addr, len))
		वापस -EINVAL;

	अगर (!map) अणु
		/* Clear out the protection map क्रम the address range */
		subpage_prot_clear(addr, len);
		वापस 0;
	पूर्ण

	अगर (!access_ok(map, (len >> PAGE_SHIFT) * माप(u32)))
		वापस -EFAULT;

	mmap_ग_लिखो_lock(mm);

	spt = mm_ctx_subpage_prot(&mm->context);
	अगर (!spt) अणु
		/*
		 * Allocate subpage prot table अगर not alपढ़ोy करोne.
		 * Do this with mmap_lock held
		 */
		spt = kzalloc(माप(काष्ठा subpage_prot_table), GFP_KERNEL);
		अगर (!spt) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		mm->context.hash_context->spt = spt;
	पूर्ण

	subpage_mark_vma_nohuge(mm, addr, len);
	क्रम (limit = addr + len; addr < limit; addr = next) अणु
		next = pmd_addr_end(addr, limit);
		err = -ENOMEM;
		अगर (addr < 0x100000000UL) अणु
			spm = spt->low_prot;
		पूर्ण अन्यथा अणु
			spm = spt->protptrs[addr >> SBP_L3_SHIFT];
			अगर (!spm) अणु
				spm = (u32 **)get_zeroed_page(GFP_KERNEL);
				अगर (!spm)
					जाओ out;
				spt->protptrs[addr >> SBP_L3_SHIFT] = spm;
			पूर्ण
		पूर्ण
		spm += (addr >> SBP_L2_SHIFT) & (SBP_L2_COUNT - 1);
		spp = *spm;
		अगर (!spp) अणु
			spp = (u32 *)get_zeroed_page(GFP_KERNEL);
			अगर (!spp)
				जाओ out;
			*spm = spp;
		पूर्ण
		spp += (addr >> PAGE_SHIFT) & (SBP_L1_COUNT - 1);

		local_irq_disable();
		demote_segment_4k(mm, addr);
		local_irq_enable();

		i = (addr >> PAGE_SHIFT) & (PTRS_PER_PTE - 1);
		nw = PTRS_PER_PTE - i;
		अगर (addr + (nw << PAGE_SHIFT) > next)
			nw = (next - addr) >> PAGE_SHIFT;

		mmap_ग_लिखो_unlock(mm);
		अगर (__copy_from_user(spp, map, nw * माप(u32)))
			वापस -EFAULT;
		map += nw;
		mmap_ग_लिखो_lock(mm);

		/* now flush any existing HPTEs क्रम the range */
		hpte_flush_range(mm, addr, nw);
	पूर्ण
	अगर (limit > spt->maxaddr)
		spt->maxaddr = limit;
	err = 0;
 out:
	mmap_ग_लिखो_unlock(mm);
	वापस err;
पूर्ण

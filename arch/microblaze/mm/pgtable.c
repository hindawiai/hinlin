<शैली गुरु>
/*
 *  This file contains the routines setting up the linux page tables.
 *
 * Copyright (C) 2008 Michal Simek
 * Copyright (C) 2008 PetaLogix
 *
 *    Copyright (C) 2007 Xilinx, Inc.  All rights reserved.
 *
 *  Derived from arch/ppc/mm/pgtable.c:
 *    -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  This file is subject to the terms and conditions of the GNU General
 *  Public License.  See the file COPYING in the मुख्य directory of this
 *  archive क्रम more details.
 *
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/fixmap.h>

अचिन्हित दीर्घ ioremap_base;
अचिन्हित दीर्घ ioremap_bot;
EXPORT_SYMBOL(ioremap_bot);

अटल व्योम __iomem *__ioremap(phys_addr_t addr, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ v, i;
	phys_addr_t p;
	पूर्णांक err;

	/*
	 * Choose an address to map it to.
	 * Once the vदो_स्मृति प्रणाली is running, we use it.
	 * Beक्रमe then, we use space going करोwn from ioremap_base
	 * (ioremap_bot records where we're up to).
	 */
	p = addr & PAGE_MASK;
	size = PAGE_ALIGN(addr + size) - p;

	/*
	 * Don't allow anybody to remap normal RAM that we're using.
	 * mem_init() sets high_memory so only करो the check after that.
	 *
	 * However, allow remap of rootfs: TBD
	 */

	अगर (mem_init_करोne &&
		p >= memory_start && p < virt_to_phys(high_memory) &&
		!(p >= __virt_to_phys((phys_addr_t)__bss_stop) &&
		p < __virt_to_phys((phys_addr_t)__bss_stop))) अणु
		pr_warn("__ioremap(): phys addr "PTE_FMT" is RAM lr %ps\n",
			(अचिन्हित दीर्घ)p, __builtin_वापस_address(0));
		वापस शून्य;
	पूर्ण

	अगर (size == 0)
		वापस शून्य;

	/*
	 * Is it alपढ़ोy mapped? If the whole area is mapped then we're
	 * करोne, otherwise remap it since we want to keep the virt addrs क्रम
	 * each request contiguous.
	 *
	 * We make the assumption here that अगर the bottom and top
	 * of the range we want are mapped then it's mapped to the
	 * same virt address (and this is contiguous).
	 *  -- Cort
	 */

	अगर (mem_init_करोne) अणु
		काष्ठा vm_काष्ठा *area;
		area = get_vm_area(size, VM_IOREMAP);
		अगर (area == शून्य)
			वापस शून्य;
		v = (अचिन्हित दीर्घ) area->addr;
	पूर्ण अन्यथा अणु
		v = (ioremap_bot -= size);
	पूर्ण

	अगर ((flags & _PAGE_PRESENT) == 0)
		flags |= _PAGE_KERNEL;
	अगर (flags & _PAGE_NO_CACHE)
		flags |= _PAGE_GUARDED;

	err = 0;
	क्रम (i = 0; i < size && err == 0; i += PAGE_SIZE)
		err = map_page(v + i, p + i, flags);
	अगर (err) अणु
		अगर (mem_init_करोne)
			vमुक्त((व्योम *)v);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *) (v + ((अचिन्हित दीर्घ)addr & ~PAGE_MASK));
पूर्ण

व्योम __iomem *ioremap(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(addr, size, _PAGE_NO_CACHE);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	अगर ((__क्रमce व्योम *)addr > high_memory &&
					(अचिन्हित दीर्घ) addr < ioremap_bot)
		vमुक्त((व्योम *) (PAGE_MASK & (अचिन्हित दीर्घ) addr));
पूर्ण
EXPORT_SYMBOL(iounmap);


पूर्णांक map_page(अचिन्हित दीर्घ va, phys_addr_t pa, पूर्णांक flags)
अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pd;
	pte_t *pg;
	पूर्णांक err = -ENOMEM;

	/* Use upper 10 bits of VA to index the first level map */
	p4d = p4d_offset(pgd_offset_k(va), va);
	pud = pud_offset(p4d, va);
	pd = pmd_offset(pud, va);
	/* Use middle 10 bits of VA to index the second-level map */
	pg = pte_alloc_kernel(pd, va); /* from घातerpc - pgtable.c */
	/* pg = pte_alloc_kernel(&init_mm, pd, va); */

	अगर (pg != शून्य) अणु
		err = 0;
		set_pte_at(&init_mm, va, pg, pfn_pte(pa >> PAGE_SHIFT,
				__pgprot(flags)));
		अगर (unlikely(mem_init_करोne))
			_tlbie(va);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Map in all of physical memory starting at CONFIG_KERNEL_START.
 */
व्योम __init mapin_ram(व्योम)
अणु
	अचिन्हित दीर्घ v, p, s, f;

	v = CONFIG_KERNEL_START;
	p = memory_start;
	क्रम (s = 0; s < lowmem_size; s += PAGE_SIZE) अणु
		f = _PAGE_PRESENT | _PAGE_ACCESSED |
				_PAGE_SHARED | _PAGE_HWEXEC;
		अगर ((अक्षर *) v < _stext || (अक्षर *) v >= _etext)
			f |= _PAGE_WRENABLE;
		अन्यथा
			/* On the MicroBlaze, no user access
			   क्रमces R/W kernel access */
			f |= _PAGE_USER;
		map_page(v, p, f);
		v += PAGE_SIZE;
		p += PAGE_SIZE;
	पूर्ण
पूर्ण

/* is x a घातer of 2? */
#घोषणा is_घातer_of_2(x)	((x) != 0 && (((x) & ((x) - 1)) == 0))

/* Scan the real Linux page tables and वापस a PTE poपूर्णांकer क्रम
 * a भव address in a context.
 * Returns true (1) अगर PTE was found, zero otherwise.  The poपूर्णांकer to
 * the PTE poपूर्णांकer is unmodअगरied अगर PTE is not found.
 */
अटल पूर्णांक get_pteptr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t **ptep)
अणु
	pgd_t	*pgd;
	p4d_t	*p4d;
	pud_t	*pud;
	pmd_t	*pmd;
	pte_t	*pte;
	पूर्णांक     retval = 0;

	pgd = pgd_offset(mm, addr & PAGE_MASK);
	अगर (pgd) अणु
		p4d = p4d_offset(pgd, addr & PAGE_MASK);
		pud = pud_offset(p4d, addr & PAGE_MASK);
		pmd = pmd_offset(pud, addr & PAGE_MASK);
		अगर (pmd_present(*pmd)) अणु
			pte = pte_offset_kernel(pmd, addr & PAGE_MASK);
			अगर (pte) अणु
				retval = 1;
				*ptep = pte;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

/* Find physical address क्रम this भव address.  Normally used by
 * I/O functions, but anyone can call it.
 */
अचिन्हित दीर्घ iopa(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ pa;

	pte_t *pte;
	काष्ठा mm_काष्ठा *mm;

	/* Allow mapping of user addresses (within the thपढ़ो)
	 * क्रम DMA अगर necessary.
	 */
	अगर (addr < TASK_SIZE)
		mm = current->mm;
	अन्यथा
		mm = &init_mm;

	pa = 0;
	अगर (get_pteptr(mm, addr, &pte))
		pa = (pte_val(*pte) & PAGE_MASK) | (addr & ~PAGE_MASK);

	वापस pa;
पूर्ण

__ref pte_t *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *pte;
	अगर (mem_init_करोne) अणु
		pte = (pte_t *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	पूर्ण अन्यथा अणु
		pte = (pte_t *)early_get_page();
		अगर (pte)
			clear_page(pte);
	पूर्ण
	वापस pte;
पूर्ण

व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t flags)
अणु
	अचिन्हित दीर्घ address = __fix_to_virt(idx);

	अगर (idx >= __end_of_fixed_addresses)
		BUG();

	map_page(address, phys, pgprot_val(flags));
पूर्ण

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC ioremap.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/tlbflush.h>

बाह्य पूर्णांक mem_init_करोne;

अटल अचिन्हित पूर्णांक fixmaps_used __initdata;

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them पूर्णांकo an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
व्योम __iomem *__ref ioremap(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	phys_addr_t p;
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ offset, last_addr;
	काष्ठा vm_काष्ठा *area = शून्य;

	/* Don't allow wraparound or zero size */
	last_addr = addr + size - 1;
	अगर (!size || last_addr < addr)
		वापस शून्य;

	/*
	 * Mappings have to be page-aligned
	 */
	offset = addr & ~PAGE_MASK;
	p = addr & PAGE_MASK;
	size = PAGE_ALIGN(last_addr + 1) - p;

	अगर (likely(mem_init_करोne)) अणु
		area = get_vm_area(size, VM_IOREMAP);
		अगर (!area)
			वापस शून्य;
		v = (अचिन्हित दीर्घ)area->addr;
	पूर्ण अन्यथा अणु
		अगर ((fixmaps_used + (size >> PAGE_SHIFT)) > FIX_N_IOREMAPS)
			वापस शून्य;
		v = fix_to_virt(FIX_IOREMAP_BEGIN + fixmaps_used);
		fixmaps_used += (size >> PAGE_SHIFT);
	पूर्ण

	अगर (ioremap_page_range(v, v + size, p,
			__pgprot(pgprot_val(PAGE_KERNEL) | _PAGE_CI))) अणु
		अगर (likely(mem_init_करोne))
			vमुक्त(area->addr);
		अन्यथा
			fixmaps_used -= (size >> PAGE_SHIFT);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)(offset + (अक्षर *)v);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम iounmap(व्योम __iomem *addr)
अणु
	/* If the page is from the fixmap pool then we just clear out
	 * the fixmap mapping.
	 */
	अगर (unlikely((अचिन्हित दीर्घ)addr > FIXADDR_START)) अणु
		/* This is a bit broken... we करोn't really know
		 * how big the area is so it's dअगरficult to know
		 * how many fixed pages to invalidate...
		 * just flush tlb and hope क्रम the best...
		 * consider this a FIXME
		 *
		 * Really we should be clearing out one or more page
		 * table entries क्रम these भव addresses so that
		 * future references cause a page fault... क्रम now, we
		 * rely on two things:
		 *   i)  this code never माला_लो called on known boards
		 *   ii) invalid accesses to the मुक्तd areas aren't made
		 */
		flush_tlb_all();
		वापस;
	पूर्ण

	वापस vमुक्त((व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)addr));
पूर्ण
EXPORT_SYMBOL(iounmap);

/**
 * OK, this one's a bit tricky... ioremap can get called beक्रमe memory is
 * initialized (early serial console करोes this) and will want to alloc a page
 * क्रम its mapping.  No userspace pages will ever get allocated beक्रमe memory
 * is initialized so this applies only to kernel pages.  In the event that
 * this is called beक्रमe memory is initialized we allocate the page using
 * the memblock infraकाष्ठाure.
 */

pte_t __ref *pte_alloc_one_kernel(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *pte;

	अगर (likely(mem_init_करोne)) अणु
		pte = (pte_t *)get_zeroed_page(GFP_KERNEL);
	पूर्ण अन्यथा अणु
		pte = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
		अगर (!pte)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);
	पूर्ण

	वापस pte;
पूर्ण

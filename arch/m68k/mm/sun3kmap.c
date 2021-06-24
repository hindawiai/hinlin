<शैली गुरु>
/*
 * linux/arch/m68k/mm/sun3kmap.c
 *
 * Copyright (C) 2002 Sam Creasey <sammy@sammy.net>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sun3mmu.h>

#अघोषित SUN3_KMAP_DEBUG

#अगर_घोषित SUN3_KMAP_DEBUG
बाह्य व्योम prपूर्णांक_pte_vaddr(अचिन्हित दीर्घ vaddr);
#पूर्ण_अगर

बाह्य व्योम mmu_emu_map_pmeg (पूर्णांक context, पूर्णांक vaddr);

अटल अंतरभूत व्योम करो_page_mapin(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ virt,
				 अचिन्हित दीर्घ type)
अणु
	अचिन्हित दीर्घ pte;
	pte_t ptep;

	ptep = pfn_pte(phys >> PAGE_SHIFT, PAGE_KERNEL);
	pte = pte_val(ptep);
	pte |= type;

	sun3_put_pte(virt, pte);

#अगर_घोषित SUN3_KMAP_DEBUG
	pr_info("mapin:");
	prपूर्णांक_pte_vaddr(virt);
#पूर्ण_अगर

पूर्ण

अटल अंतरभूत व्योम करो_pmeg_mapin(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ virt,
				 अचिन्हित दीर्घ type, पूर्णांक pages)
अणु

	अगर(sun3_get_segmap(virt & ~SUN3_PMEG_MASK) == SUN3_INVALID_PMEG)
		mmu_emu_map_pmeg(sun3_get_context(), virt);

	जबतक(pages) अणु
		करो_page_mapin(phys, virt, type);
		phys += PAGE_SIZE;
		virt += PAGE_SIZE;
		pages--;
	पूर्ण
पूर्ण

व्योम __iomem *sun3_ioremap(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size,
		   अचिन्हित दीर्घ type)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ offset, virt, ret;
	पूर्णांक pages;

	अगर(!size)
		वापस शून्य;

	/* page align */
	offset = phys & (PAGE_SIZE-1);
	phys &= ~(PAGE_SIZE-1);

	size += offset;
	size = PAGE_ALIGN(size);
	अगर((area = get_vm_area(size, VM_IOREMAP)) == शून्य)
		वापस शून्य;

#अगर_घोषित SUN3_KMAP_DEBUG
	pr_info("ioremap: got virt %p size %lx(%lx)\n", area->addr, size,
		area->size);
#पूर्ण_अगर

	pages = size / PAGE_SIZE;
	virt = (अचिन्हित दीर्घ)area->addr;
	ret = virt + offset;

	जबतक(pages) अणु
		पूर्णांक seg_pages;

		seg_pages = (SUN3_PMEG_SIZE - (virt & SUN3_PMEG_MASK)) / PAGE_SIZE;
		अगर(seg_pages > pages)
			seg_pages = pages;

		करो_pmeg_mapin(phys, virt, type, seg_pages);

		pages -= seg_pages;
		phys += seg_pages * PAGE_SIZE;
		virt += seg_pages * PAGE_SIZE;
	पूर्ण

	वापस (व्योम __iomem *)ret;

पूर्ण
EXPORT_SYMBOL(sun3_ioremap);


व्योम __iomem *__ioremap(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size, पूर्णांक cache)
अणु

	वापस sun3_ioremap(phys, size, SUN3_PAGE_TYPE_IO);

पूर्ण
EXPORT_SYMBOL(__ioremap);

व्योम iounmap(व्योम __iomem *addr)
अणु
	vमुक्त((व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)addr));
पूर्ण
EXPORT_SYMBOL(iounmap);

/* sun3_map_test(addr, val) -- Reads a byte from addr, storing to val,
 * trapping the potential पढ़ो fault.  Returns 0 अगर the access faulted,
 * 1 on success.
 *
 * This function is primarily used to check addresses on the VME bus.
 *
 * Mucking with the page fault handler seems a little hackish to me, but
 * SunOS, NetBSD, and Mach all implemented this check in such a manner,
 * so I figure we're allowed.
 */
पूर्णांक sun3_map_test(अचिन्हित दीर्घ addr, अक्षर *val)
अणु
	पूर्णांक ret = 0;

	__यंत्र__ __अस्थिर__
		(".globl _sun3_map_test_start\n"
		 "_sun3_map_test_start:\n"
		 "1: moveb (%2), (%0)\n"
		 "   moveq #1, %1\n"
		 "2:\n"
		 ".section .fixup,\"ax\"\n"
		 ".even\n"
		 "3: moveq #0, %1\n"
		 "   jmp 2b\n"
		 ".previous\n"
		 ".section __ex_table,\"a\"\n"
		 ".align 4\n"
		 ".long 1b,3b\n"
		 ".previous\n"
		 ".globl _sun3_map_test_end\n"
		 "_sun3_map_test_end:\n"
		 : "=a"(val), "=r"(ret)
		 : "a"(addr));

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sun3_map_test);

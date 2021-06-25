<शैली गुरु>
/*
 * arch/sh/mm/ioremap.c
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 * (C) Copyright 2005 - 2010  Paul Mundt
 *
 * Re-map IO memory to kernel address space so that we can access it.
 * This is needed क्रम high PCI addresses that aren't mapped in the
 * 640k-1MB IO memory area on PC's
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/io_trapped.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu.h>
#समावेश "ioremap.h"

/*
 * On 32-bit SH, we traditionally have the whole physical address space mapped
 * at all बार (as MIPS करोes), so "ioremap()" and "iounmap()" करो not need to करो
 * anything but place the address in the proper segment.  This is true क्रम P1
 * and P2 addresses, as well as some P3 ones.  However, most of the P3 addresses
 * and newer cores using extended addressing need to map through page tables, so
 * the ioremap() implementation becomes a bit more complicated.
 */
#अगर_घोषित CONFIG_29BIT
अटल व्योम __iomem *
__ioremap_29bit(phys_addr_t offset, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	phys_addr_t last_addr = offset + size - 1;

	/*
	 * For P1 and P2 space this is trivial, as everything is alपढ़ोy
	 * mapped. Uncached access क्रम P1 addresses are करोne through P2.
	 * In the P3 हाल or क्रम addresses outside of the 29-bit space,
	 * mapping must be करोne by the PMB or by using page tables.
	 */
	अगर (likely(PXSEG(offset) < P3SEG && PXSEG(last_addr) < P3SEG)) अणु
		u64 flags = pgprot_val(prot);

		/*
		 * Anything using the legacy PTEA space attributes needs
		 * to be kicked करोwn to page table mappings.
		 */
		अगर (unlikely(flags & _PAGE_PCC_MASK))
			वापस शून्य;
		अगर (unlikely(flags & _PAGE_CACHABLE))
			वापस (व्योम __iomem *)P1SEGADDR(offset);

		वापस (व्योम __iomem *)P2SEGADDR(offset);
	पूर्ण

	/* P4 above the store queues are always mapped. */
	अगर (unlikely(offset >= P3_ADDR_MAX))
		वापस (व्योम __iomem *)P4SEGADDR(offset);

	वापस शून्य;
पूर्ण
#अन्यथा
#घोषणा __ioremap_29bit(offset, size, prot)		शून्य
#पूर्ण_अगर /* CONFIG_29BIT */

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them पूर्णांकo an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
व्योम __iomem * __ref
__ioremap_caller(phys_addr_t phys_addr, अचिन्हित दीर्घ size,
		 pgprot_t pgprot, व्योम *caller)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ offset, last_addr, addr, orig_addr;
	व्योम __iomem *mapped;

	mapped = __ioremap_trapped(phys_addr, size);
	अगर (mapped)
		वापस mapped;

	mapped = __ioremap_29bit(phys_addr, size, pgprot);
	अगर (mapped)
		वापस mapped;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	/*
	 * If we can't yet use the regular approach, go the fixmap route.
	 */
	अगर (!mem_init_करोne)
		वापस ioremap_fixed(phys_addr, size, pgprot);

	/*
	 * First try to remap through the PMB.
	 * PMB entries are all pre-faulted.
	 */
	mapped = pmb_remap_caller(phys_addr, size, pgprot, caller);
	अगर (mapped && !IS_ERR(mapped))
		वापस mapped;

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr+1) - phys_addr;

	/*
	 * Ok, go क्रम it..
	 */
	area = get_vm_area_caller(size, VM_IOREMAP, caller);
	अगर (!area)
		वापस शून्य;
	area->phys_addr = phys_addr;
	orig_addr = addr = (अचिन्हित दीर्घ)area->addr;

	अगर (ioremap_page_range(addr, addr + size, phys_addr, pgprot)) अणु
		vunmap((व्योम *)orig_addr);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)(offset + (अक्षर *)orig_addr);
पूर्ण
EXPORT_SYMBOL(__ioremap_caller);

/*
 * Simple checks क्रम non-translatable mappings.
 */
अटल अंतरभूत पूर्णांक iomapping_nontranslatable(अचिन्हित दीर्घ offset)
अणु
#अगर_घोषित CONFIG_29BIT
	/*
	 * In 29-bit mode this includes the fixed P1/P2 areas, as well as
	 * parts of P3.
	 */
	अगर (PXSEG(offset) < P3SEG || offset >= P3_ADDR_MAX)
		वापस 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम iounmap(व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ __क्रमce)addr;
	काष्ठा vm_काष्ठा *p;

	/*
	 * Nothing to करो अगर there is no translatable mapping.
	 */
	अगर (iomapping_nontranslatable(vaddr))
		वापस;

	/*
	 * There's no VMA if it's from an early fixed mapping.
	 */
	अगर (iounmap_fixed(addr) == 0)
		वापस;

	/*
	 * If the PMB handled it, there's nothing अन्यथा to करो.
	 */
	अगर (pmb_unmap(addr) == 0)
		वापस;

	p = हटाओ_vm_area((व्योम *)(vaddr & PAGE_MASK));
	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR "%s: bad address %p\n", __func__, addr);
		वापस;
	पूर्ण

	kमुक्त(p);
पूर्ण
EXPORT_SYMBOL(iounmap);

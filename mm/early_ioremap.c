<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide common bits of early_ioremap() support क्रम architectures needing
 * temporary mappings during boot beक्रमe ioremap() is available.
 *
 * This is mostly a direct copy of the x86 early_ioremap implementation.
 *
 * (C) Copyright 1995 1996, 2014 Linus Torvalds
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/early_ioremap.h>

#अगर_घोषित CONFIG_MMU
अटल पूर्णांक early_ioremap_debug __initdata;

अटल पूर्णांक __init early_ioremap_debug_setup(अक्षर *str)
अणु
	early_ioremap_debug = 1;

	वापस 0;
पूर्ण
early_param("early_ioremap_debug", early_ioremap_debug_setup);

अटल पूर्णांक after_paging_init __initdata;

pgprot_t __init __weak early_memremap_pgprot_adjust(resource_माप_प्रकार phys_addr,
						    अचिन्हित दीर्घ size,
						    pgprot_t prot)
अणु
	वापस prot;
पूर्ण

व्योम __init __weak early_ioremap_shutकरोwn(व्योम)
अणु
पूर्ण

व्योम __init early_ioremap_reset(व्योम)
अणु
	early_ioremap_shutकरोwn();
	after_paging_init = 1;
पूर्ण

/*
 * Generally, ioremap() is available after paging_init() has been called.
 * Architectures wanting to allow early_ioremap after paging_init() can
 * define __late_set_fixmap and __late_clear_fixmap to करो the right thing.
 */
#अगर_अघोषित __late_set_fixmap
अटल अंतरभूत व्योम __init __late_set_fixmap(क्रमागत fixed_addresses idx,
					    phys_addr_t phys, pgprot_t prot)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __late_clear_fixmap
अटल अंतरभूत व्योम __init __late_clear_fixmap(क्रमागत fixed_addresses idx)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

अटल व्योम __iomem *prev_map[FIX_BTMAPS_SLOTS] __initdata;
अटल अचिन्हित दीर्घ prev_size[FIX_BTMAPS_SLOTS] __initdata;
अटल अचिन्हित दीर्घ slot_virt[FIX_BTMAPS_SLOTS] __initdata;

व्योम __init early_ioremap_setup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FIX_BTMAPS_SLOTS; i++)
		अगर (WARN_ON(prev_map[i]))
			अवरोध;

	क्रम (i = 0; i < FIX_BTMAPS_SLOTS; i++)
		slot_virt[i] = __fix_to_virt(FIX_BTMAP_BEGIN - NR_FIX_BTMAPS*i);
पूर्ण

अटल पूर्णांक __init check_early_ioremap_leak(व्योम)
अणु
	पूर्णांक count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < FIX_BTMAPS_SLOTS; i++)
		अगर (prev_map[i])
			count++;

	अगर (WARN(count, KERN_WARNING
		 "Debug warning: early ioremap leak of %d areas detected.\n"
		 "please boot with early_ioremap_debug and report the dmesg.\n",
		 count))
		वापस 1;
	वापस 0;
पूर्ण
late_initcall(check_early_ioremap_leak);

अटल व्योम __init __iomem *
__early_ioremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ offset;
	resource_माप_प्रकार last_addr;
	अचिन्हित पूर्णांक nrpages;
	क्रमागत fixed_addresses idx;
	पूर्णांक i, slot;

	WARN_ON(प्रणाली_state >= SYSTEM_RUNNING);

	slot = -1;
	क्रम (i = 0; i < FIX_BTMAPS_SLOTS; i++) अणु
		अगर (!prev_map[i]) अणु
			slot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN(slot < 0, "%s(%pa, %08lx) not found slot\n",
		 __func__, &phys_addr, size))
		वापस शून्य;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	अगर (WARN_ON(!size || last_addr < phys_addr))
		वापस शून्य;

	prev_size[slot] = size;
	/*
	 * Mappings have to be page-aligned
	 */
	offset = offset_in_page(phys_addr);
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr + 1) - phys_addr;

	/*
	 * Mappings have to fit in the FIX_BTMAP area.
	 */
	nrpages = size >> PAGE_SHIFT;
	अगर (WARN_ON(nrpages > NR_FIX_BTMAPS))
		वापस शून्य;

	/*
	 * Ok, go क्रम it..
	 */
	idx = FIX_BTMAP_BEGIN - NR_FIX_BTMAPS*slot;
	जबतक (nrpages > 0) अणु
		अगर (after_paging_init)
			__late_set_fixmap(idx, phys_addr, prot);
		अन्यथा
			__early_set_fixmap(idx, phys_addr, prot);
		phys_addr += PAGE_SIZE;
		--idx;
		--nrpages;
	पूर्ण
	WARN(early_ioremap_debug, "%s(%pa, %08lx) [%d] => %08lx + %08lx\n",
	     __func__, &phys_addr, size, slot, offset, slot_virt[slot]);

	prev_map[slot] = (व्योम __iomem *)(offset + slot_virt[slot]);
	वापस prev_map[slot];
पूर्ण

व्योम __init early_iounmap(व्योम __iomem *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ virt_addr;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक nrpages;
	क्रमागत fixed_addresses idx;
	पूर्णांक i, slot;

	slot = -1;
	क्रम (i = 0; i < FIX_BTMAPS_SLOTS; i++) अणु
		अगर (prev_map[i] == addr) अणु
			slot = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (WARN(slot < 0, "%s(%p, %08lx) not found slot\n",
		  __func__, addr, size))
		वापस;

	अगर (WARN(prev_size[slot] != size,
		 "%s(%p, %08lx) [%d] size not consistent %08lx\n",
		  __func__, addr, size, slot, prev_size[slot]))
		वापस;

	WARN(early_ioremap_debug, "%s(%p, %08lx) [%d]\n",
	      __func__, addr, size, slot);

	virt_addr = (अचिन्हित दीर्घ)addr;
	अगर (WARN_ON(virt_addr < fix_to_virt(FIX_BTMAP_BEGIN)))
		वापस;

	offset = offset_in_page(virt_addr);
	nrpages = PAGE_ALIGN(offset + size) >> PAGE_SHIFT;

	idx = FIX_BTMAP_BEGIN - NR_FIX_BTMAPS*slot;
	जबतक (nrpages > 0) अणु
		अगर (after_paging_init)
			__late_clear_fixmap(idx);
		अन्यथा
			__early_set_fixmap(idx, 0, FIXMAP_PAGE_CLEAR);
		--idx;
		--nrpages;
	पूर्ण
	prev_map[slot] = शून्य;
पूर्ण

/* Remap an IO device */
व्योम __init __iomem *
early_ioremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस __early_ioremap(phys_addr, size, FIXMAP_PAGE_IO);
पूर्ण

/* Remap memory */
व्योम __init *
early_memremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = early_memremap_pgprot_adjust(phys_addr, size,
						     FIXMAP_PAGE_NORMAL);

	वापस (__क्रमce व्योम *)__early_ioremap(phys_addr, size, prot);
पूर्ण
#अगर_घोषित FIXMAP_PAGE_RO
व्योम __init *
early_memremap_ro(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = early_memremap_pgprot_adjust(phys_addr, size,
						     FIXMAP_PAGE_RO);

	वापस (__क्रमce व्योम *)__early_ioremap(phys_addr, size, prot);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_USE_MEMREMAP_PROT
व्योम __init *
early_memremap_prot(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size,
		    अचिन्हित दीर्घ prot_val)
अणु
	वापस (__क्रमce व्योम *)__early_ioremap(phys_addr, size,
					       __pgprot(prot_val));
पूर्ण
#पूर्ण_अगर

#घोषणा MAX_MAP_CHUNK	(NR_FIX_BTMAPS << PAGE_SHIFT)

व्योम __init copy_from_early_mem(व्योम *dest, phys_addr_t src, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ slop, clen;
	अक्षर *p;

	जबतक (size) अणु
		slop = offset_in_page(src);
		clen = size;
		अगर (clen > MAX_MAP_CHUNK - slop)
			clen = MAX_MAP_CHUNK - slop;
		p = early_memremap(src & PAGE_MASK, clen + slop);
		स_नकल(dest, p + slop, clen);
		early_memunmap(p, clen + slop);
		dest += clen;
		src += clen;
		size -= clen;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_MMU */

व्योम __init __iomem *
early_ioremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस (__क्रमce व्योम __iomem *)phys_addr;
पूर्ण

/* Remap memory */
व्योम __init *
early_memremap(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस (व्योम *)phys_addr;
पूर्ण
व्योम __init *
early_memremap_ro(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस (व्योम *)phys_addr;
पूर्ण

व्योम __init early_iounmap(व्योम __iomem *addr, अचिन्हित दीर्घ size)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */


व्योम __init early_memunmap(व्योम *addr, अचिन्हित दीर्घ size)
अणु
	early_iounmap((__क्रमce व्योम __iomem *)addr, size);
पूर्ण

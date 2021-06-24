<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/highस्मृति.स>
#समावेश <linux/kprobes.h>

/**
 * flush_coherent_icache() - अगर a CPU has a coherent icache, flush it
 * Return true अगर the cache was flushed, false otherwise
 */
अटल अंतरभूत bool flush_coherent_icache(व्योम)
अणु
	/*
	 * For a snooping icache, we still need a dummy icbi to purge all the
	 * prefetched inकाष्ठाions from the अगरetch buffers. We also need a sync
	 * beक्रमe the icbi to order the the actual stores to memory that might
	 * have modअगरied inकाष्ठाions with the icbi.
	 */
	अगर (cpu_has_feature(CPU_FTR_COHERENT_ICACHE)) अणु
		mb(); /* sync */
		icbi((व्योम *)PAGE_OFFSET);
		mb(); /* sync */
		isync();
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * invalidate_icache_range() - Flush the icache by issuing icbi across an address range
 * @start: the start address
 * @stop: the stop address (exclusive)
 */
अटल व्योम invalidate_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_icache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_icache_bytes();
	अक्षर *addr = (अक्षर *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		icbi(addr);

	mb(); /* sync */
	isync();
पूर्ण

/**
 * flush_icache_range: Write any modअगरied data cache blocks out to memory
 * and invalidate the corresponding blocks in the inकाष्ठाion cache
 *
 * Generic code will call this after writing memory, beक्रमe executing from it.
 *
 * @start: the start address
 * @stop: the stop address (exclusive)
 */
व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अगर (flush_coherent_icache())
		वापस;

	clean_dcache_range(start, stop);

	अगर (IS_ENABLED(CONFIG_44x)) अणु
		/*
		 * Flash invalidate on 44x because we are passed kmapped
		 * addresses and this करोesn't work क्रम userspace pages due to
		 * the भवly tagged icache.
		 */
		iccci((व्योम *)start);
		mb(); /* sync */
		isync();
	पूर्ण अन्यथा
		invalidate_icache_range(start, stop);
पूर्ण
EXPORT_SYMBOL(flush_icache_range);

#अगर_घोषित CONFIG_HIGHMEM
/**
 * flush_dcache_icache_phys() - Flush a page by it's physical address
 * @physaddr: the physical address of the page
 */
अटल व्योम flush_dcache_icache_phys(अचिन्हित दीर्घ physaddr)
अणु
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	अचिन्हित दीर्घ nb = PAGE_SIZE / bytes;
	अचिन्हित दीर्घ addr = physaddr & PAGE_MASK;
	अचिन्हित दीर्घ msr, msr0;
	अचिन्हित दीर्घ loop1 = addr, loop2 = addr;

	msr0 = mfmsr();
	msr = msr0 & ~MSR_DR;
	/*
	 * This must reमुख्य as ASM to prevent potential memory accesses
	 * जबतक the data MMU is disabled
	 */
	यंत्र अस्थिर(
		"   mtctr %2;\n"
		"   mtmsr %3;\n"
		"   isync;\n"
		"0: dcbst   0, %0;\n"
		"   addi    %0, %0, %4;\n"
		"   bdnz    0b;\n"
		"   sync;\n"
		"   mtctr %2;\n"
		"1: icbi    0, %1;\n"
		"   addi    %1, %1, %4;\n"
		"   bdnz    1b;\n"
		"   sync;\n"
		"   mtmsr %5;\n"
		"   isync;\n"
		: "+&r" (loop1), "+&r" (loop2)
		: "r" (nb), "r" (msr), "i" (bytes), "r" (msr0)
		: "ctr", "memory");
पूर्ण
NOKPROBE_SYMBOL(flush_dcache_icache_phys)
#अन्यथा
अटल व्योम flush_dcache_icache_phys(अचिन्हित दीर्घ physaddr)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * __flush_dcache_icache(): Flush a particular page from the data cache to RAM.
 * Note: this is necessary because the inकाष्ठाion cache करोes *not*
 * snoop from the data cache.
 *
 * @p: the address of the page to flush
 */
अटल व्योम __flush_dcache_icache(व्योम *p)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)p & PAGE_MASK;

	clean_dcache_range(addr, addr + PAGE_SIZE);

	/*
	 * We करोn't flush the icache on 44x. Those have a भव icache and we
	 * करोn't have access to the virtual address here (it's not the page
	 * vaddr but where it's mapped in user space). The flushing of the
	 * icache on these is handled अन्यथाwhere, when a change in the address
	 * space occurs, beक्रमe वापसing to user space.
	 */

	अगर (mmu_has_feature(MMU_FTR_TYPE_44x))
		वापस;

	invalidate_icache_range(addr, addr + PAGE_SIZE);
पूर्ण

अटल व्योम flush_dcache_icache_hugepage(काष्ठा page *page)
अणु
	पूर्णांक i;
	पूर्णांक nr = compound_nr(page);

	अगर (!PageHighMem(page)) अणु
		क्रम (i = 0; i < nr; i++)
			__flush_dcache_icache(lowmem_page_address(page + i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < nr; i++) अणु
			व्योम *start = kmap_local_page(page + i);

			__flush_dcache_icache(start);
			kunmap_local(start);
		पूर्ण
	पूर्ण
पूर्ण

व्योम flush_dcache_icache_page(काष्ठा page *page)
अणु
	अगर (flush_coherent_icache())
		वापस;

	अगर (PageCompound(page))
		वापस flush_dcache_icache_hugepage(page);

	अगर (!PageHighMem(page)) अणु
		__flush_dcache_icache(lowmem_page_address(page));
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_BOOKE) || माप(phys_addr_t) > माप(व्योम *)) अणु
		व्योम *start = kmap_local_page(page);

		__flush_dcache_icache(start);
		kunmap_local(start);
	पूर्ण अन्यथा अणु
		flush_dcache_icache_phys(page_to_phys(page));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_dcache_icache_page);

व्योम clear_user_page(व्योम *page, अचिन्हित दीर्घ vaddr, काष्ठा page *pg)
अणु
	clear_page(page);

	/*
	 * We shouldn't have to करो this, but some versions of glibc
	 * require it (ld.so assumes zero filled pages are icache clean)
	 * - Anton
	 */
	flush_dcache_page(pg);
पूर्ण
EXPORT_SYMBOL(clear_user_page);

व्योम copy_user_page(व्योम *vto, व्योम *vfrom, अचिन्हित दीर्घ vaddr,
		    काष्ठा page *pg)
अणु
	copy_page(vto, vfrom);

	/*
	 * We should be able to use the following optimisation, however
	 * there are two problems.
	 * Firstly a bug in some versions of binutils meant PLT sections
	 * were not marked executable.
	 * Secondly the first word in the GOT section is blrl, used
	 * to establish the GOT address. Until recently the GOT was
	 * not marked executable.
	 * - Anton
	 */
#अगर 0
	अगर (!vma->vm_file && ((vma->vm_flags & VM_EXEC) == 0))
		वापस;
#पूर्ण_अगर

	flush_dcache_page(pg);
पूर्ण

व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			     अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	व्योम *maddr;

	maddr = kmap_local_page(page) + (addr & ~PAGE_MASK);
	flush_icache_range((अचिन्हित दीर्घ)maddr, (अचिन्हित दीर्घ)maddr + len);
	kunmap_local(maddr);
पूर्ण

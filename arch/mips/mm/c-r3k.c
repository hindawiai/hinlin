<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r2300.c: R2000 and R3000 specअगरic mmu/cache code.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 *
 * with a lot of changes to make this thing work क्रम R3000s
 * Tx39XX R4k style caches added. HK
 * Copyright (C) 1998, 1999, 2000 Harald Koerfgen
 * Copyright (C) 1998 Gleb Raiko & Vladimir Roganov
 * Copyright (C) 2001, 2004, 2007  Maciej W. Rozycki
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/isadep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>

अटल अचिन्हित दीर्घ icache_size, dcache_size;		/* Size in bytes */
अटल अचिन्हित दीर्घ icache_lsize, dcache_lsize;	/* Size in bytes */

अचिन्हित दीर्घ r3k_cache_size(अचिन्हित दीर्घ ca_flags)
अणु
	अचिन्हित दीर्घ flags, status, dummy, size;
	अस्थिर अचिन्हित दीर्घ *p;

	p = (अस्थिर अचिन्हित दीर्घ *) KSEG0;

	flags = पढ़ो_c0_status();

	/* isolate cache space */
	ग_लिखो_c0_status((ca_flags|flags)&~ST0_IEC);

	*p = 0xa5a55a5a;
	dummy = *p;
	status = पढ़ो_c0_status();

	अगर (dummy != 0xa5a55a5a || (status & ST0_CM)) अणु
		size = 0;
	पूर्ण अन्यथा अणु
		क्रम (size = 128; size <= 0x40000; size <<= 1)
			*(p + size) = 0;
		*p = -1;
		क्रम (size = 128;
		     (size <= 0x40000) && (*(p + size) == 0);
		     size <<= 1)
			;
		अगर (size > 0x40000)
			size = 0;
	पूर्ण

	ग_लिखो_c0_status(flags);

	वापस size * माप(*p);
पूर्ण

अचिन्हित दीर्घ r3k_cache_lsize(अचिन्हित दीर्घ ca_flags)
अणु
	अचिन्हित दीर्घ flags, status, lsize, i;
	अस्थिर अचिन्हित दीर्घ *p;

	p = (अस्थिर अचिन्हित दीर्घ *) KSEG0;

	flags = पढ़ो_c0_status();

	/* isolate cache space */
	ग_लिखो_c0_status((ca_flags|flags)&~ST0_IEC);

	क्रम (i = 0; i < 128; i++)
		*(p + i) = 0;
	*(अस्थिर अचिन्हित अक्षर *)p = 0;
	क्रम (lsize = 1; lsize < 128; lsize <<= 1) अणु
		*(p + lsize);
		status = पढ़ो_c0_status();
		अगर (!(status & ST0_CM))
			अवरोध;
	पूर्ण
	क्रम (i = 0; i < 128; i += lsize)
		*(अस्थिर अचिन्हित अक्षर *)(p + i) = 0;

	ग_लिखो_c0_status(flags);

	वापस lsize * माप(*p);
पूर्ण

अटल व्योम r3k_probe_cache(व्योम)
अणु
	dcache_size = r3k_cache_size(ST0_ISC);
	अगर (dcache_size)
		dcache_lsize = r3k_cache_lsize(ST0_ISC);

	icache_size = r3k_cache_size(ST0_ISC|ST0_SWC);
	अगर (icache_size)
		icache_lsize = r3k_cache_lsize(ST0_ISC|ST0_SWC);
पूर्ण

अटल व्योम r3k_flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ size, i, flags;
	अस्थिर अचिन्हित अक्षर *p;

	size = end - start;
	अगर (size > icache_size || KSEGX(start) != KSEG0) अणु
		start = KSEG0;
		size = icache_size;
	पूर्ण
	p = (अक्षर *)start;

	flags = पढ़ो_c0_status();

	/* isolate cache space */
	ग_लिखो_c0_status((ST0_ISC|ST0_SWC|flags)&~ST0_IEC);

	क्रम (i = 0; i < size; i += 0x080) अणु
		यंत्र(	"sb\t$0, 0x000(%0)\n\t"
			"sb\t$0, 0x004(%0)\n\t"
			"sb\t$0, 0x008(%0)\n\t"
			"sb\t$0, 0x00c(%0)\n\t"
			"sb\t$0, 0x010(%0)\n\t"
			"sb\t$0, 0x014(%0)\n\t"
			"sb\t$0, 0x018(%0)\n\t"
			"sb\t$0, 0x01c(%0)\n\t"
			"sb\t$0, 0x020(%0)\n\t"
			"sb\t$0, 0x024(%0)\n\t"
			"sb\t$0, 0x028(%0)\n\t"
			"sb\t$0, 0x02c(%0)\n\t"
			"sb\t$0, 0x030(%0)\n\t"
			"sb\t$0, 0x034(%0)\n\t"
			"sb\t$0, 0x038(%0)\n\t"
			"sb\t$0, 0x03c(%0)\n\t"
			"sb\t$0, 0x040(%0)\n\t"
			"sb\t$0, 0x044(%0)\n\t"
			"sb\t$0, 0x048(%0)\n\t"
			"sb\t$0, 0x04c(%0)\n\t"
			"sb\t$0, 0x050(%0)\n\t"
			"sb\t$0, 0x054(%0)\n\t"
			"sb\t$0, 0x058(%0)\n\t"
			"sb\t$0, 0x05c(%0)\n\t"
			"sb\t$0, 0x060(%0)\n\t"
			"sb\t$0, 0x064(%0)\n\t"
			"sb\t$0, 0x068(%0)\n\t"
			"sb\t$0, 0x06c(%0)\n\t"
			"sb\t$0, 0x070(%0)\n\t"
			"sb\t$0, 0x074(%0)\n\t"
			"sb\t$0, 0x078(%0)\n\t"
			"sb\t$0, 0x07c(%0)\n\t"
			: : "r" (p) );
		p += 0x080;
	पूर्ण

	ग_लिखो_c0_status(flags);
पूर्ण

अटल व्योम r3k_flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ size, i, flags;
	अस्थिर अचिन्हित अक्षर *p;

	size = end - start;
	अगर (size > dcache_size || KSEGX(start) != KSEG0) अणु
		start = KSEG0;
		size = dcache_size;
	पूर्ण
	p = (अक्षर *)start;

	flags = पढ़ो_c0_status();

	/* isolate cache space */
	ग_लिखो_c0_status((ST0_ISC|flags)&~ST0_IEC);

	क्रम (i = 0; i < size; i += 0x080) अणु
		यंत्र(	"sb\t$0, 0x000(%0)\n\t"
			"sb\t$0, 0x004(%0)\n\t"
			"sb\t$0, 0x008(%0)\n\t"
			"sb\t$0, 0x00c(%0)\n\t"
			"sb\t$0, 0x010(%0)\n\t"
			"sb\t$0, 0x014(%0)\n\t"
			"sb\t$0, 0x018(%0)\n\t"
			"sb\t$0, 0x01c(%0)\n\t"
			"sb\t$0, 0x020(%0)\n\t"
			"sb\t$0, 0x024(%0)\n\t"
			"sb\t$0, 0x028(%0)\n\t"
			"sb\t$0, 0x02c(%0)\n\t"
			"sb\t$0, 0x030(%0)\n\t"
			"sb\t$0, 0x034(%0)\n\t"
			"sb\t$0, 0x038(%0)\n\t"
			"sb\t$0, 0x03c(%0)\n\t"
			"sb\t$0, 0x040(%0)\n\t"
			"sb\t$0, 0x044(%0)\n\t"
			"sb\t$0, 0x048(%0)\n\t"
			"sb\t$0, 0x04c(%0)\n\t"
			"sb\t$0, 0x050(%0)\n\t"
			"sb\t$0, 0x054(%0)\n\t"
			"sb\t$0, 0x058(%0)\n\t"
			"sb\t$0, 0x05c(%0)\n\t"
			"sb\t$0, 0x060(%0)\n\t"
			"sb\t$0, 0x064(%0)\n\t"
			"sb\t$0, 0x068(%0)\n\t"
			"sb\t$0, 0x06c(%0)\n\t"
			"sb\t$0, 0x070(%0)\n\t"
			"sb\t$0, 0x074(%0)\n\t"
			"sb\t$0, 0x078(%0)\n\t"
			"sb\t$0, 0x07c(%0)\n\t"
			: : "r" (p) );
		p += 0x080;
	पूर्ण

	ग_लिखो_c0_status(flags);
पूर्ण

अटल अंतरभूत व्योम r3k_flush_cache_all(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम r3k___flush_cache_all(व्योम)
अणु
	r3k_flush_dcache_range(KSEG0, KSEG0 + dcache_size);
	r3k_flush_icache_range(KSEG0, KSEG0 + icache_size);
पूर्ण

अटल व्योम r3k_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण

अटल व्योम r3k_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल व्योम r3k_flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ kaddr = KSEG0ADDR(pfn << PAGE_SHIFT);
	पूर्णांक exec = vma->vm_flags & VM_EXEC;
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	pmd_t *pmdp;
	pte_t *ptep;

	pr_debug("cpage[%08llx,%08lx]\n",
		 cpu_context(smp_processor_id(), mm), addr);

	/* No ASID => no such page in the cache.  */
	अगर (cpu_context(smp_processor_id(), mm) == 0)
		वापस;

	pmdp = pmd_off(mm, addr);
	ptep = pte_offset_kernel(pmdp, addr);

	/* Invalid => no such page in the cache.  */
	अगर (!(pte_val(*ptep) & _PAGE_PRESENT))
		वापस;

	r3k_flush_dcache_range(kaddr, kaddr + PAGE_SIZE);
	अगर (exec)
		r3k_flush_icache_range(kaddr, kaddr + PAGE_SIZE);
पूर्ण

अटल व्योम local_r3k_flush_data_cache_page(व्योम *addr)
अणु
पूर्ण

अटल व्योम r3k_flush_data_cache_page(अचिन्हित दीर्घ addr)
अणु
पूर्ण

अटल व्योम r3k_flush_kernel_vmap_range(अचिन्हित दीर्घ vaddr, पूर्णांक size)
अणु
	BUG();
पूर्ण

अटल व्योम r3k_dma_cache_wback_inv(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	/* Catch bad driver code */
	BUG_ON(size == 0);

	iob();
	r3k_flush_dcache_range(start, start + size);
पूर्ण

व्योम r3k_cache_init(व्योम)
अणु
	बाह्य व्योम build_clear_page(व्योम);
	बाह्य व्योम build_copy_page(व्योम);

	r3k_probe_cache();

	flush_cache_all = r3k_flush_cache_all;
	__flush_cache_all = r3k___flush_cache_all;
	flush_cache_mm = r3k_flush_cache_mm;
	flush_cache_range = r3k_flush_cache_range;
	flush_cache_page = r3k_flush_cache_page;
	flush_icache_range = r3k_flush_icache_range;
	local_flush_icache_range = r3k_flush_icache_range;
	__flush_icache_user_range = r3k_flush_icache_range;
	__local_flush_icache_user_range = r3k_flush_icache_range;

	__flush_kernel_vmap_range = r3k_flush_kernel_vmap_range;

	local_flush_data_cache_page = local_r3k_flush_data_cache_page;
	flush_data_cache_page = r3k_flush_data_cache_page;

	_dma_cache_wback_inv = r3k_dma_cache_wback_inv;
	_dma_cache_wback = r3k_dma_cache_wback_inv;
	_dma_cache_inv = r3k_dma_cache_wback_inv;

	pr_info("Primary instruction cache %ldkB, linesize %ld bytes.\n",
		icache_size >> 10, icache_lsize);
	pr_info("Primary data cache %ldkB, linesize %ld bytes.\n",
		dcache_size >> 10, dcache_lsize);

	build_clear_page();
	build_copy_page();
पूर्ण

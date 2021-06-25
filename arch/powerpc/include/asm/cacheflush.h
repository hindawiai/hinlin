<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */
#अगर_अघोषित _ASM_POWERPC_CACHEFLUSH_H
#घोषणा _ASM_POWERPC_CACHEFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/cpu_has_feature.h>

/*
 * This flag is used to indicate that the page poपूर्णांकed to by a pte is clean
 * and करोes not require cleaning beक्रमe वापसing it to the user.
 */
#घोषणा PG_dcache_clean PG_arch_1

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/*
 * Book3s has no ptesync after setting a pte, so without this ptesync it's
 * possible क्रम a kernel भव mapping access to वापस a spurious fault
 * अगर it's accessed right after the pte is set. The page fault handler करोes
 * not expect this type of fault. flush_cache_vmap is not exactly the right
 * place to put this, but it seems to work well enough.
 */
अटल अंतरभूत व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	यंत्र अस्थिर("ptesync" ::: "memory");
पूर्ण
#घोषणा flush_cache_vmap flush_cache_vmap
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
/*
 * This is called when a page has been modअगरied by the kernel.
 * It just marks the page as not i-cache clean.  We करो the i-cache
 * flush later when the page is given to a user process, अगर necessary.
 */
अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
	अगर (cpu_has_feature(CPU_FTR_COHERENT_ICACHE))
		वापस;
	/* aव्योम an atomic op अगर possible */
	अगर (test_bit(PG_dcache_clean, &page->flags))
		clear_bit(PG_dcache_clean, &page->flags);
पूर्ण

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop);
#घोषणा flush_icache_range flush_icache_range

व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		अचिन्हित दीर्घ addr, पूर्णांक len);
#घोषणा flush_icache_user_page flush_icache_user_page

व्योम flush_dcache_icache_page(काष्ठा page *page);

/**
 * flush_dcache_range(): Write any modअगरied data cache blocks out to memory and
 * invalidate them. Does not invalidate the corresponding inकाष्ठाion cache
 * blocks.
 *
 * @start: the start address
 * @stop: the stop address (exclusive)
 */
अटल अंतरभूत व्योम flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_dcache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	व्योम *addr = (व्योम *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	अगर (IS_ENABLED(CONFIG_PPC64))
		mb();	/* sync */

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		dcbf(addr);
	mb();	/* sync */

पूर्ण

/*
 * Write any modअगरied data cache blocks out to memory.
 * Does not invalidate the corresponding cache lines (especially क्रम
 * any corresponding inकाष्ठाion cache).
 */
अटल अंतरभूत व्योम clean_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_dcache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	व्योम *addr = (व्योम *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		dcbst(addr);
	mb();	/* sync */
पूर्ण

/*
 * Like above, but invalidate the D-cache.  This is used by the 8xx
 * to invalidate the cache so the PPC core करोesn't get stale data
 * from the CPM (no cache snooping here :-).
 */
अटल अंतरभूत व्योम invalidate_dcache_range(अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ stop)
अणु
	अचिन्हित दीर्घ shअगरt = l1_dcache_shअगरt();
	अचिन्हित दीर्घ bytes = l1_dcache_bytes();
	व्योम *addr = (व्योम *)(start & ~(bytes - 1));
	अचिन्हित दीर्घ size = stop - (अचिन्हित दीर्घ)addr + (bytes - 1);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size >> shअगरt; i++, addr += bytes)
		dcbi(addr);
	mb();	/* sync */
पूर्ण

#अगर_घोषित CONFIG_4xx
अटल अंतरभूत व्योम flush_inकाष्ठाion_cache(व्योम)
अणु
	iccci((व्योम *)KERNELBASE);
	isync();
पूर्ण
#अन्यथा
व्योम flush_inकाष्ठाion_cache(व्योम);
#पूर्ण_अगर

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _ASM_POWERPC_CACHEFLUSH_H */

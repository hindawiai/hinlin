<शैली गुरु>
/*
 * arch/arm/mm/cache-feroceon-l2.c - Feroceon L2 cache controller support
 *
 * Copyright (C) 2008 Marvell Semiconductor
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * References:
 * - Unअगरied Layer 2 Cache क्रम Feroceon CPU Cores,
 *   Document ID MV-S104858-00, Rev. A, October 23 2007.
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/hardware/cache-feroceon-l2.h>

#घोषणा L2_WRITETHROUGH_KIRKWOOD	BIT(4)

/*
 * Low-level cache मुख्यtenance operations.
 *
 * As well as the regular 'clean/invalidate/flush L2 cache line by
 * MVA' inकाष्ठाions, the Feroceon L2 cache controller also features
 * 'clean/invalidate L2 range by MVA' operations.
 *
 * Cache range operations are initiated by writing the start and
 * end addresses to successive cp15 रेजिस्टरs, and process every
 * cache line whose first byte address lies in the inclusive range
 * [start:end].
 *
 * The cache range operations stall the CPU pipeline until completion.
 *
 * The range operations require two successive cp15 ग_लिखोs, in
 * between which we करोn't want to be preempted.
 */

अटल अंतरभूत अचिन्हित दीर्घ l2_get_va(अचिन्हित दीर्घ paddr)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	/*
	 * Because range ops can't be करोne on physical addresses,
	 * we simply install a भव mapping क्रम it only क्रम the
	 * TLB lookup to occur, hence no need to flush the untouched
	 * memory mapping afterwards (note: a cache flush may happen
	 * in some circumstances depending on the path taken in kunmap_atomic).
	 */
	व्योम *vaddr = kmap_atomic_pfn(paddr >> PAGE_SHIFT);
	वापस (अचिन्हित दीर्घ)vaddr + (paddr & ~PAGE_MASK);
#अन्यथा
	वापस __phys_to_virt(paddr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम l2_put_va(अचिन्हित दीर्घ vaddr)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	kunmap_atomic((व्योम *)vaddr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम l2_clean_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c9, 3" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम l2_clean_pa_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ बहु_शुरू, बहु_पूर्ण, flags;

	/*
	 * Make sure 'start' and 'end' reference the same page, as
	 * L2 is PIPT and range operations only करो a TLB lookup on
	 * the start address.
	 */
	BUG_ON((start ^ end) >> PAGE_SHIFT);

	बहु_शुरू = l2_get_va(start);
	बहु_पूर्ण = बहु_शुरू + (end - start);
	raw_local_irq_save(flags);
	__यंत्र__("mcr p15, 1, %0, c15, c9, 4\n\t"
		"mcr p15, 1, %1, c15, c9, 5"
		: : "r" (बहु_शुरू), "r" (बहु_पूर्ण));
	raw_local_irq_restore(flags);
	l2_put_va(बहु_शुरू);
पूर्ण

अटल अंतरभूत व्योम l2_clean_inv_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c10, 3" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम l2_inv_pa(अचिन्हित दीर्घ addr)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c11, 3" : : "r" (addr));
पूर्ण

अटल अंतरभूत व्योम l2_inv_pa_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ बहु_शुरू, बहु_पूर्ण, flags;

	/*
	 * Make sure 'start' and 'end' reference the same page, as
	 * L2 is PIPT and range operations only करो a TLB lookup on
	 * the start address.
	 */
	BUG_ON((start ^ end) >> PAGE_SHIFT);

	बहु_शुरू = l2_get_va(start);
	बहु_पूर्ण = बहु_शुरू + (end - start);
	raw_local_irq_save(flags);
	__यंत्र__("mcr p15, 1, %0, c15, c11, 4\n\t"
		"mcr p15, 1, %1, c15, c11, 5"
		: : "r" (बहु_शुरू), "r" (बहु_पूर्ण));
	raw_local_irq_restore(flags);
	l2_put_va(बहु_शुरू);
पूर्ण

अटल अंतरभूत व्योम l2_inv_all(व्योम)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c11, 0" : : "r" (0));
पूर्ण

/*
 * Linux primitives.
 *
 * Note that the end addresses passed to Linux primitives are
 * noninclusive, जबतक the hardware cache range operations use
 * inclusive start and end addresses.
 */
#घोषणा CACHE_LINE_SIZE		32
#घोषणा MAX_RANGE_SIZE		1024

अटल पूर्णांक l2_wt_override;

अटल अचिन्हित दीर्घ calc_range_end(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ range_end;

	BUG_ON(start & (CACHE_LINE_SIZE - 1));
	BUG_ON(end & (CACHE_LINE_SIZE - 1));

	/*
	 * Try to process all cache lines between 'start' and 'end'.
	 */
	range_end = end;

	/*
	 * Limit the number of cache lines processed at once,
	 * since cache range operations stall the CPU pipeline
	 * until completion.
	 */
	अगर (range_end > start + MAX_RANGE_SIZE)
		range_end = start + MAX_RANGE_SIZE;

	/*
	 * Cache range operations can't straddle a page boundary.
	 */
	अगर (range_end > (start | (PAGE_SIZE - 1)) + 1)
		range_end = (start | (PAGE_SIZE - 1)) + 1;

	वापस range_end;
पूर्ण

अटल व्योम feroceon_l2_inv_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * Clean and invalidate partial first cache line.
	 */
	अगर (start & (CACHE_LINE_SIZE - 1)) अणु
		l2_clean_inv_pa(start & ~(CACHE_LINE_SIZE - 1));
		start = (start | (CACHE_LINE_SIZE - 1)) + 1;
	पूर्ण

	/*
	 * Clean and invalidate partial last cache line.
	 */
	अगर (start < end && end & (CACHE_LINE_SIZE - 1)) अणु
		l2_clean_inv_pa(end & ~(CACHE_LINE_SIZE - 1));
		end &= ~(CACHE_LINE_SIZE - 1);
	पूर्ण

	/*
	 * Invalidate all full cache lines between 'start' and 'end'.
	 */
	जबतक (start < end) अणु
		अचिन्हित दीर्घ range_end = calc_range_end(start, end);
		l2_inv_pa_range(start, range_end - CACHE_LINE_SIZE);
		start = range_end;
	पूर्ण

	dsb();
पूर्ण

अटल व्योम feroceon_l2_clean_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * If L2 is क्रमced to WT, the L2 will always be clean and we
	 * करोn't need to करो anything here.
	 */
	अगर (!l2_wt_override) अणु
		start &= ~(CACHE_LINE_SIZE - 1);
		end = (end + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1);
		जबतक (start != end) अणु
			अचिन्हित दीर्घ range_end = calc_range_end(start, end);
			l2_clean_pa_range(start, range_end - CACHE_LINE_SIZE);
			start = range_end;
		पूर्ण
	पूर्ण

	dsb();
पूर्ण

अटल व्योम feroceon_l2_flush_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start &= ~(CACHE_LINE_SIZE - 1);
	end = (end + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1);
	जबतक (start != end) अणु
		अचिन्हित दीर्घ range_end = calc_range_end(start, end);
		अगर (!l2_wt_override)
			l2_clean_pa_range(start, range_end - CACHE_LINE_SIZE);
		l2_inv_pa_range(start, range_end - CACHE_LINE_SIZE);
		start = range_end;
	पूर्ण

	dsb();
पूर्ण


/*
 * Routines to disable and re-enable the D-cache and I-cache at run
 * समय.  These are necessary because the L2 cache can only be enabled
 * or disabled जबतक the L1 Dcache and Icache are both disabled.
 */
अटल पूर्णांक __init flush_and_disable_dcache(व्योम)
अणु
	u32 cr;

	cr = get_cr();
	अगर (cr & CR_C) अणु
		अचिन्हित दीर्घ flags;

		raw_local_irq_save(flags);
		flush_cache_all();
		set_cr(cr & ~CR_C);
		raw_local_irq_restore(flags);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init enable_dcache(व्योम)
अणु
	u32 cr;

	cr = get_cr();
	set_cr(cr | CR_C);
पूर्ण

अटल व्योम __init __invalidate_icache(व्योम)
अणु
	__यंत्र__("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));
पूर्ण

अटल पूर्णांक __init invalidate_and_disable_icache(व्योम)
अणु
	u32 cr;

	cr = get_cr();
	अगर (cr & CR_I) अणु
		set_cr(cr & ~CR_I);
		__invalidate_icache();
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init enable_icache(व्योम)
अणु
	u32 cr;

	cr = get_cr();
	set_cr(cr | CR_I);
पूर्ण

अटल अंतरभूत u32 पढ़ो_extra_features(व्योम)
अणु
	u32 u;

	__यंत्र__("mrc p15, 1, %0, c15, c1, 0" : "=r" (u));

	वापस u;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_extra_features(u32 u)
अणु
	__यंत्र__("mcr p15, 1, %0, c15, c1, 0" : : "r" (u));
पूर्ण

अटल व्योम __init disable_l2_prefetch(व्योम)
अणु
	u32 u;

	/*
	 * Read the CPU Extra Features रेजिस्टर and verअगरy that the
	 * Disable L2 Prefetch bit is set.
	 */
	u = पढ़ो_extra_features();
	अगर (!(u & 0x01000000)) अणु
		pr_info("Feroceon L2: Disabling L2 prefetch.\n");
		ग_लिखो_extra_features(u | 0x01000000);
	पूर्ण
पूर्ण

अटल व्योम __init enable_l2(व्योम)
अणु
	u32 u;

	u = पढ़ो_extra_features();
	अगर (!(u & 0x00400000)) अणु
		पूर्णांक i, d;

		pr_info("Feroceon L2: Enabling L2\n");

		d = flush_and_disable_dcache();
		i = invalidate_and_disable_icache();
		l2_inv_all();
		ग_लिखो_extra_features(u | 0x00400000);
		अगर (i)
			enable_icache();
		अगर (d)
			enable_dcache();
	पूर्ण अन्यथा
		pr_err(FW_BUG
		       "Feroceon L2: bootloader left the L2 cache on!\n");
पूर्ण

व्योम __init feroceon_l2_init(पूर्णांक __l2_wt_override)
अणु
	l2_wt_override = __l2_wt_override;

	disable_l2_prefetch();

	outer_cache.inv_range = feroceon_l2_inv_range;
	outer_cache.clean_range = feroceon_l2_clean_range;
	outer_cache.flush_range = feroceon_l2_flush_range;

	enable_l2();

	pr_info("Feroceon L2: Cache support initialised%s.\n",
			 l2_wt_override ? ", in WT override mode" : "");
पूर्ण
#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id feroceon_ids[] __initस्थिर = अणु
	अणु .compatible = "marvell,kirkwood-cache"पूर्ण,
	अणु .compatible = "marvell,feroceon-cache"पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक __init feroceon_of_init(व्योम)
अणु
	काष्ठा device_node *node;
	व्योम __iomem *base;
	bool l2_wt_override = false;

#अगर defined(CONFIG_CACHE_FEROCEON_L2_WRITETHROUGH)
	l2_wt_override = true;
#पूर्ण_अगर

	node = of_find_matching_node(शून्य, feroceon_ids);
	अगर (node && of_device_is_compatible(node, "marvell,kirkwood-cache")) अणु
		base = of_iomap(node, 0);
		अगर (!base)
			वापस -ENOMEM;

		अगर (l2_wt_override)
			ग_लिखोl(पढ़ोl(base) | L2_WRITETHROUGH_KIRKWOOD, base);
		अन्यथा
			ग_लिखोl(पढ़ोl(base) & ~L2_WRITETHROUGH_KIRKWOOD, base);
	पूर्ण

	feroceon_l2_init(l2_wt_override);

	वापस 0;
पूर्ण
#पूर्ण_अगर

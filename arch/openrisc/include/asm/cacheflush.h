<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) Jan Henrik Weinstock <jan.weinstock@rwth-aachen.de>
 * et al.
 */

#अगर_अघोषित __ASM_CACHEFLUSH_H
#घोषणा __ASM_CACHEFLUSH_H

#समावेश <linux/mm.h>

/*
 * Helper function क्रम flushing or invalidating entire pages from data
 * and inकाष्ठाion caches. SMP needs a little extra work, since we need
 * to flush the pages on all cpus.
 */
बाह्य व्योम local_dcache_page_flush(काष्ठा page *page);
बाह्य व्योम local_icache_page_inv(काष्ठा page *page);

/*
 * Data cache flushing always happen on the local cpu. Inकाष्ठाion cache
 * invalidations need to be broadcasted to all other cpu in the प्रणाली in
 * हाल of SMP configurations.
 */
#अगर_अघोषित CONFIG_SMP
#घोषणा dcache_page_flush(page)      local_dcache_page_flush(page)
#घोषणा icache_page_inv(page)        local_icache_page_inv(page)
#अन्यथा  /* CONFIG_SMP */
#घोषणा dcache_page_flush(page)      local_dcache_page_flush(page)
#घोषणा icache_page_inv(page)        smp_icache_page_inv(page)
बाह्य व्योम smp_icache_page_inv(काष्ठा page *page);
#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Synchronizes caches. Whenever a cpu ग_लिखोs executable code to memory, this
 * should be called to make sure the processor sees the newly written code.
 */
अटल अंतरभूत व्योम sync_icache_dcache(काष्ठा page *page)
अणु
	अगर (!IS_ENABLED(CONFIG_DCACHE_WRITETHROUGH))
		dcache_page_flush(page);
	icache_page_inv(page);
पूर्ण

/*
 * Pages with this bit set need not be flushed/invalidated, since
 * they have not changed since last flush. New pages start with
 * PG_arch_1 not set and are thereक्रमe dirty by शेष.
 */
#घोषणा PG_dc_clean                  PG_arch_1

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
	clear_bit(PG_dc_clean, &page->flags);
पूर्ण

#घोषणा flush_icache_user_page(vma, page, addr, len)	\
करो अणु							\
	अगर (vma->vm_flags & VM_EXEC)			\
		sync_icache_dcache(page);		\
पूर्ण जबतक (0)

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* __ASM_CACHEFLUSH_H */

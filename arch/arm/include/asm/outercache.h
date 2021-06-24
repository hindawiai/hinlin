<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/include/यंत्र/outercache.h
 *
 * Copyright (C) 2010 ARM Ltd.
 * Written by Catalin Marinas <catalin.marinas@arm.com>
 */

#अगर_अघोषित __ASM_OUTERCACHE_H
#घोषणा __ASM_OUTERCACHE_H

#समावेश <linux/types.h>

काष्ठा l2x0_regs;

काष्ठा outer_cache_fns अणु
	व्योम (*inv_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	व्योम (*clean_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	व्योम (*flush_range)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	व्योम (*flush_all)(व्योम);
	व्योम (*disable)(व्योम);
#अगर_घोषित CONFIG_OUTER_CACHE_SYNC
	व्योम (*sync)(व्योम);
#पूर्ण_अगर
	व्योम (*resume)(व्योम);

	/* This is an ARM L2C thing */
	व्योम (*ग_लिखो_sec)(अचिन्हित दीर्घ, अचिन्हित);
	व्योम (*configure)(स्थिर काष्ठा l2x0_regs *);
पूर्ण;

बाह्य काष्ठा outer_cache_fns outer_cache;

#अगर_घोषित CONFIG_OUTER_CACHE
/**
 * outer_inv_range - invalidate range of outer cache lines
 * @start: starting physical address, inclusive
 * @end: end physical address, exclusive
 */
अटल अंतरभूत व्योम outer_inv_range(phys_addr_t start, phys_addr_t end)
अणु
	अगर (outer_cache.inv_range)
		outer_cache.inv_range(start, end);
पूर्ण

/**
 * outer_clean_range - clean dirty outer cache lines
 * @start: starting physical address, inclusive
 * @end: end physical address, exclusive
 */
अटल अंतरभूत व्योम outer_clean_range(phys_addr_t start, phys_addr_t end)
अणु
	अगर (outer_cache.clean_range)
		outer_cache.clean_range(start, end);
पूर्ण

/**
 * outer_flush_range - clean and invalidate outer cache lines
 * @start: starting physical address, inclusive
 * @end: end physical address, exclusive
 */
अटल अंतरभूत व्योम outer_flush_range(phys_addr_t start, phys_addr_t end)
अणु
	अगर (outer_cache.flush_range)
		outer_cache.flush_range(start, end);
पूर्ण

/**
 * outer_flush_all - clean and invalidate all cache lines in the outer cache
 *
 * Note: depending on implementation, this may not be atomic - it must
 * only be called with पूर्णांकerrupts disabled and no other active outer
 * cache masters.
 *
 * It is पूर्णांकended that this function is only used by implementations
 * needing to override the outer_cache.disable() method due to security.
 * (Some implementations perक्रमm this as a clean followed by an invalidate.)
 */
अटल अंतरभूत व्योम outer_flush_all(व्योम)
अणु
	अगर (outer_cache.flush_all)
		outer_cache.flush_all();
पूर्ण

/**
 * outer_disable - clean, invalidate and disable the outer cache
 *
 * Disable the outer cache, ensuring that any data contained in the outer
 * cache is pushed out to lower levels of प्रणाली memory.  The note and
 * conditions above concerning outer_flush_all() applies here.
 */
बाह्य व्योम outer_disable(व्योम);

/**
 * outer_resume - restore the cache configuration and re-enable outer cache
 *
 * Restore any configuration that the cache had when previously enabled,
 * and re-enable the outer cache.
 */
अटल अंतरभूत व्योम outer_resume(व्योम)
अणु
	अगर (outer_cache.resume)
		outer_cache.resume();
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम outer_inv_range(phys_addr_t start, phys_addr_t end)
अणु पूर्ण
अटल अंतरभूत व्योम outer_clean_range(phys_addr_t start, phys_addr_t end)
अणु पूर्ण
अटल अंतरभूत व्योम outer_flush_range(phys_addr_t start, phys_addr_t end)
अणु पूर्ण
अटल अंतरभूत व्योम outer_flush_all(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम outer_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम outer_resume(व्योम) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर	/* __ASM_OUTERCACHE_H */

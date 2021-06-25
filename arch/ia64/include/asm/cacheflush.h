<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_CACHEFLUSH_H
#घोषणा _ASM_IA64_CACHEFLUSH_H

/*
 * Copyright (C) 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <linux/page-flags.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/page.h>

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
#घोषणा flush_dcache_page(page)			\
करो अणु						\
	clear_bit(PG_arch_1, &(page)->flags);	\
पूर्ण जबतक (0)

बाह्य व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_icache_range flush_icache_range
बाह्य व्योम clflush_cache_range(व्योम *addr, पूर्णांक size);

#घोषणा flush_icache_user_page(vma, page, user_addr, len)					\
करो अणु												\
	अचिन्हित दीर्घ _addr = (अचिन्हित दीर्घ) page_address(page) + ((user_addr) & ~PAGE_MASK);	\
	flush_icache_range(_addr, _addr + (len));						\
पूर्ण जबतक (0)

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _ASM_IA64_CACHEFLUSH_H */

<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/addrspace.h>

/*
 * This is the offset of the uncached section from its cached alias.
 *
 * Legacy platक्रमms handle trivial transitions between cached and
 * uncached segments by making use of the 1:1 mapping relationship in
 * 512MB lowmem, others via a special uncached mapping.
 *
 * Default value only valid in 29 bit mode, in 32bit mode this will be
 * updated by the early PMB initialization code.
 */
अचिन्हित दीर्घ cached_to_uncached = SZ_512M;
अचिन्हित दीर्घ uncached_size = SZ_512M;
अचिन्हित दीर्घ uncached_start, uncached_end;
EXPORT_SYMBOL(uncached_start);
EXPORT_SYMBOL(uncached_end);

पूर्णांक virt_addr_uncached(अचिन्हित दीर्घ kaddr)
अणु
	वापस (kaddr >= uncached_start) && (kaddr < uncached_end);
पूर्ण
EXPORT_SYMBOL(virt_addr_uncached);

व्योम __init uncached_init(व्योम)
अणु
#अगर defined(CONFIG_29BIT) || !defined(CONFIG_MMU)
	uncached_start = P2SEG;
#अन्यथा
	uncached_start = memory_end;
#पूर्ण_अगर
	uncached_end = uncached_start + uncached_size;
पूर्ण

व्योम __init uncached_resize(अचिन्हित दीर्घ size)
अणु
	uncached_size = size;
	uncached_end = uncached_start + uncached_size;
पूर्ण

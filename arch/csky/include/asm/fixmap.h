<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_FIXMAP_H
#घोषणा __ASM_CSKY_FIXMAP_H

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/memory.h>
#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/kmap_size.h>
#पूर्ण_अगर

क्रमागत fixed_addresses अणु
#अगर_घोषित CONFIG_HAVE_TCM
	FIX_TCM = TCM_NR_PAGES,
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,
#पूर्ण_अगर
	__end_of_fixed_addresses
पूर्ण;

#घोषणा FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START	(FIXADDR_TOP - FIXADDR_SIZE)

#समावेश <यंत्र-generic/fixmap.h>

बाह्य व्योम fixrange_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
	pgd_t *pgd_base);
बाह्य व्योम __init fixaddr_init(व्योम);

#पूर्ण_अगर /* __ASM_CSKY_FIXMAP_H */

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_FIXMAP_H
#घोषणा __ASM_NDS32_FIXMAP_H

#अगर_घोषित CONFIG_HIGHMEM
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/kmap_size.h>
#पूर्ण_अगर

क्रमागत fixed_addresses अणु
	FIX_HOLE,
	FIX_KMAP_RESERVED,
	FIX_KMAP_BEGIN,
#अगर_घोषित CONFIG_HIGHMEM
	FIX_KMAP_END = FIX_KMAP_BEGIN + (KM_MAX_IDX * NR_CPUS) - 1,
#पूर्ण_अगर
	FIX_EARLYCON_MEM_BASE,
	__end_of_fixed_addresses
पूर्ण;
#घोषणा FIXADDR_TOP             ((अचिन्हित दीर्घ) (-(16 * PAGE_SIZE)))
#घोषणा FIXADDR_SIZE		((__end_of_fixed_addresses) << PAGE_SHIFT)
#घोषणा FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)
#घोषणा FIXMAP_PAGE_IO		__pgprot(PAGE_DEVICE)
व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t prot);

#समावेश <यंत्र-generic/fixmap.h>
#पूर्ण_अगर /* __ASM_NDS32_FIXMAP_H */

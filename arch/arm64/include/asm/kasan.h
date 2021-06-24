<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/linkage.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mte-kasan.h>
#समावेश <यंत्र/pgtable-types.h>

#घोषणा arch_kasan_set_tag(addr, tag)	__tag_set(addr, tag)
#घोषणा arch_kasan_reset_tag(addr)	__tag_reset(addr)
#घोषणा arch_kasan_get_tag(addr)	__tag_get(addr)

#अगर defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)

व्योम kasan_init(व्योम);

/*
 * KASAN_SHADOW_START: beginning of the kernel भव addresses.
 * KASAN_SHADOW_END: KASAN_SHADOW_START + 1/N of kernel भव addresses,
 * where N = (1 << KASAN_SHADOW_SCALE_SHIFT).
 *
 * KASAN_SHADOW_OFFSET:
 * This value is used to map an address to the corresponding shaकरोw
 * address by the following क्रमmula:
 *     shaकरोw_addr = (address >> KASAN_SHADOW_SCALE_SHIFT) + KASAN_SHADOW_OFFSET
 *
 * (1 << (64 - KASAN_SHADOW_SCALE_SHIFT)) shaकरोw addresses that lie in range
 * [KASAN_SHADOW_OFFSET, KASAN_SHADOW_END) cover all 64-bits of भव
 * addresses. So KASAN_SHADOW_OFFSET should satisfy the following equation:
 *      KASAN_SHADOW_OFFSET = KASAN_SHADOW_END -
 *				(1ULL << (64 - KASAN_SHADOW_SCALE_SHIFT))
 */
#घोषणा _KASAN_SHADOW_START(va)	(KASAN_SHADOW_END - (1UL << ((va) - KASAN_SHADOW_SCALE_SHIFT)))
#घोषणा KASAN_SHADOW_START      _KASAN_SHADOW_START(vabits_actual)

व्योम kasan_copy_shaकरोw(pgd_t *pgdir);
यंत्रlinkage व्योम kasan_early_init(व्योम);

#अन्यथा
अटल अंतरभूत व्योम kasan_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_copy_shaकरोw(pgd_t *pgdir) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 Andes Technology Corporation */

#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_KASAN

/*
 * The following comment was copied from arm64:
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
 *                              (1ULL << (64 - KASAN_SHADOW_SCALE_SHIFT))
 */
#घोषणा KASAN_SHADOW_SCALE_SHIFT	3

#घोषणा KASAN_SHADOW_SIZE	(UL(1) << ((CONFIG_VA_BITS - 1) - KASAN_SHADOW_SCALE_SHIFT))
#घोषणा KASAN_SHADOW_START	KERN_VIRT_START
#घोषणा KASAN_SHADOW_END	(KASAN_SHADOW_START + KASAN_SHADOW_SIZE)
#घोषणा KASAN_SHADOW_OFFSET	(KASAN_SHADOW_END - (1ULL << \
					(64 - KASAN_SHADOW_SCALE_SHIFT)))

व्योम kasan_init(व्योम);
यंत्रlinkage व्योम kasan_early_init(व्योम);

#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर /* __ASM_KASAN_H */

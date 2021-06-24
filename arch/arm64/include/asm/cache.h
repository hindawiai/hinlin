<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_CACHE_H
#घोषणा __ASM_CACHE_H

#समावेश <यंत्र/cputype.h>

#घोषणा CTR_L1IP_SHIFT		14
#घोषणा CTR_L1IP_MASK		3
#घोषणा CTR_DMINLINE_SHIFT	16
#घोषणा CTR_IMINLINE_SHIFT	0
#घोषणा CTR_IMINLINE_MASK	0xf
#घोषणा CTR_ERG_SHIFT		20
#घोषणा CTR_CWG_SHIFT		24
#घोषणा CTR_CWG_MASK		15
#घोषणा CTR_IDC_SHIFT		28
#घोषणा CTR_DIC_SHIFT		29

#घोषणा CTR_CACHE_MINLINE_MASK	\
	(0xf << CTR_DMINLINE_SHIFT | CTR_IMINLINE_MASK << CTR_IMINLINE_SHIFT)

#घोषणा CTR_L1IP(ctr)		(((ctr) >> CTR_L1IP_SHIFT) & CTR_L1IP_MASK)

#घोषणा ICACHE_POLICY_VPIPT	0
#घोषणा ICACHE_POLICY_RESERVED	1
#घोषणा ICACHE_POLICY_VIPT	2
#घोषणा ICACHE_POLICY_PIPT	3

#घोषणा L1_CACHE_SHIFT		(6)
#घोषणा L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)


#घोषणा CLIDR_LOUU_SHIFT	27
#घोषणा CLIDR_LOC_SHIFT		24
#घोषणा CLIDR_LOUIS_SHIFT	21

#घोषणा CLIDR_LOUU(clidr)	(((clidr) >> CLIDR_LOUU_SHIFT) & 0x7)
#घोषणा CLIDR_LOC(clidr)	(((clidr) >> CLIDR_LOC_SHIFT) & 0x7)
#घोषणा CLIDR_LOUIS(clidr)	(((clidr) >> CLIDR_LOUIS_SHIFT) & 0x7)

/*
 * Memory वापसed by kदो_स्मृति() may be used क्रम DMA, so we must make
 * sure that all such allocations are cache aligned. Otherwise,
 * unrelated code may cause parts of the buffer to be पढ़ो पूर्णांकo the
 * cache beक्रमe the transfer is करोne, causing old data to be seen by
 * the CPU.
 */
#घोषणा ARCH_DMA_MINALIGN	(128)

#अगर_घोषित CONFIG_KASAN_SW_TAGS
#घोषणा ARCH_SLAB_MINALIGN	(1ULL << KASAN_SHADOW_SCALE_SHIFT)
#या_अगर defined(CONFIG_KASAN_HW_TAGS)
#घोषणा ARCH_SLAB_MINALIGN	MTE_GRANULE_SIZE
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bitops.h>

#घोषणा ICACHEF_ALIASING	0
#घोषणा ICACHEF_VPIPT		1
बाह्य अचिन्हित दीर्घ __icache_flags;

/*
 * Whilst the D-side always behaves as PIPT on AArch64, aliasing is
 * permitted in the I-cache.
 */
अटल अंतरभूत पूर्णांक icache_is_aliasing(व्योम)
अणु
	वापस test_bit(ICACHEF_ALIASING, &__icache_flags);
पूर्ण

अटल __always_अंतरभूत पूर्णांक icache_is_vpipt(व्योम)
अणु
	वापस test_bit(ICACHEF_VPIPT, &__icache_flags);
पूर्ण

अटल अंतरभूत u32 cache_type_cwg(व्योम)
अणु
	वापस (पढ़ो_cpuid_cachetype() >> CTR_CWG_SHIFT) & CTR_CWG_MASK;
पूर्ण

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

अटल अंतरभूत पूर्णांक cache_line_size_of_cpu(व्योम)
अणु
	u32 cwg = cache_type_cwg();

	वापस cwg ? 4 << cwg : ARCH_DMA_MINALIGN;
पूर्ण

पूर्णांक cache_line_size(व्योम);

/*
 * Read the effective value of CTR_EL0.
 *
 * According to ARM ARM क्रम ARMv8-A (ARM DDI 0487C.a),
 * section D10.2.33 "CTR_EL0, Cache Type Register" :
 *
 * CTR_EL0.IDC reports the data cache clean requirements क्रम
 * inकाष्ठाion to data coherence.
 *
 *  0 - dcache clean to PoU is required unless :
 *     (CLIDR_EL1.LoC == 0) || (CLIDR_EL1.LoUIS == 0 && CLIDR_EL1.LoUU == 0)
 *  1 - dcache clean to PoU is not required क्रम i-to-d coherence.
 *
 * This routine provides the CTR_EL0 with the IDC field updated to the
 * effective state.
 */
अटल अंतरभूत u32 __attribute_स्थिर__ पढ़ो_cpuid_effective_cachetype(व्योम)
अणु
	u32 ctr = पढ़ो_cpuid_cachetype();

	अगर (!(ctr & BIT(CTR_IDC_SHIFT))) अणु
		u64 clidr = पढ़ो_sysreg(clidr_el1);

		अगर (CLIDR_LOC(clidr) == 0 ||
		    (CLIDR_LOUIS(clidr) == 0 && CLIDR_LOUU(clidr) == 0))
			ctr |= BIT(CTR_IDC_SHIFT);
	पूर्ण

	वापस ctr;
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर

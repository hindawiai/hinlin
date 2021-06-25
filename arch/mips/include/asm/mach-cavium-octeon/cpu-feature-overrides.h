<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004 Cavium Networks
 */
#अगर_अघोषित __ASM_MACH_CAVIUM_OCTEON_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_CAVIUM_OCTEON_CPU_FEATURE_OVERRIDES_H

#समावेश <linux/types.h>
#समावेश <यंत्र/mipsregs.h>

/*
 * Cavium Octeons are MIPS64v2 processors
 */
#घोषणा cpu_dcache_line_size()	128
#घोषणा cpu_icache_line_size()	128


#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_3k_cache	0
#घोषणा cpu_has_4k_cache	0
#घोषणा cpu_has_tx39_cache	0
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_watch		1
#घोषणा cpu_has_भागec		1
#घोषणा cpu_has_vce		0
#घोषणा cpu_has_cache_cdex_p	0
#घोषणा cpu_has_cache_cdex_s	0
#घोषणा cpu_has_prefetch	1

#घोषणा cpu_has_llsc		1
/*
 * We Disable LL/SC on non SMP प्रणालीs as it is faster to disable
 * पूर्णांकerrupts क्रम atomic access than a LL/SC.
 */
#अगर_घोषित CONFIG_SMP
# define kernel_uses_llsc	1
#अन्यथा
# define kernel_uses_llsc	0
#पूर्ण_अगर
#घोषणा cpu_has_vtag_icache	1
#घोषणा cpu_has_dc_aliases	0
#घोषणा cpu_has_ic_fills_f_dc	0
#घोषणा cpu_has_64bits		1
#घोषणा cpu_has_octeon_cache	1
#घोषणा cpu_has_mips32r1	1
#घोषणा cpu_has_mips32r2	1
#घोषणा cpu_has_mips64r1	1
#घोषणा cpu_has_mips64r2	1
#घोषणा cpu_has_dsp		0
#घोषणा cpu_has_dsp2		0
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_has_vपूर्णांक		0
#घोषणा cpu_has_veic		0
#घोषणा cpu_hwrena_impl_bits	(MIPS_HWRENA_IMPL1 | MIPS_HWRENA_IMPL2)
#घोषणा cpu_has_wsbh            1

#घोषणा cpu_has_rixi		(cpu_data[0].cputype != CPU_CAVIUM_OCTEON)

#घोषणा ARCH_HAS_SPINLOCK_PREFETCH 1
#घोषणा spin_lock_prefetch(x) prefetch(x)
#घोषणा PREFETCH_STRIDE 128

#अगर_घोषित __OCTEON__
/*
 * All gcc versions that have OCTEON support define __OCTEON__ and have the
 *  __builtin_popcount support.
 */
#घोषणा ARCH_HAS_USABLE_BUILTIN_POPCOUNT 1
#पूर्ण_अगर

/*
 * The last 256MB are reserved क्रम device to device mappings and the
 * BAR1 hole.
 */
#घोषणा MAX_DMA32_PFN (((1ULL << 32) - (1ULL << 28)) >> PAGE_SHIFT)

#पूर्ण_अगर

<शैली गुरु>
/*
 * include/यंत्र-xtensa/cache.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CACHE_H
#घोषणा _XTENSA_CACHE_H

#समावेश <यंत्र/core.h>

#घोषणा L1_CACHE_SHIFT	XCHAL_DCACHE_LINEWIDTH
#घोषणा L1_CACHE_BYTES	XCHAL_DCACHE_LINESIZE
#घोषणा SMP_CACHE_BYTES	L1_CACHE_BYTES

#घोषणा DCACHE_WAY_SIZE	(XCHAL_DCACHE_SIZE/XCHAL_DCACHE_WAYS)
#घोषणा ICACHE_WAY_SIZE	(XCHAL_ICACHE_SIZE/XCHAL_ICACHE_WAYS)
#घोषणा DCACHE_WAY_SHIFT (XCHAL_DCACHE_SETWIDTH + XCHAL_DCACHE_LINEWIDTH)
#घोषणा ICACHE_WAY_SHIFT (XCHAL_ICACHE_SETWIDTH + XCHAL_ICACHE_LINEWIDTH)

/* Maximum cache size per way. */
#अगर DCACHE_WAY_SIZE >= ICACHE_WAY_SIZE
# define CACHE_WAY_SIZE DCACHE_WAY_SIZE
#अन्यथा
# define CACHE_WAY_SIZE ICACHE_WAY_SIZE
#पूर्ण_अगर

#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

/*
 * R/O after init is actually writable, it cannot go to .rodata
 * according to vmlinux linker script.
 */
#घोषणा __ro_after_init __पढ़ो_mostly

#पूर्ण_अगर	/* _XTENSA_CACHE_H */

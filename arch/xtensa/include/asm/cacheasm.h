<शैली गुरु>
/*
 * include/यंत्र-xtensa/cacheयंत्र.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006 Tensilica Inc.
 */

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/यंत्रmacro.h>
#समावेश <linux/stringअगरy.h>

/*
 * Define cache functions as macros here so that they can be used
 * by the kernel and boot loader. We should consider moving them to a
 * library that can be linked by both.
 *
 * Locking
 *
 *   ___unlock_dcache_all
 *   ___unlock_icache_all
 *
 * Flush and invaldating
 *
 *   ___flush_invalidate_dcache_अणुall|range|pageपूर्ण
 *   ___flush_dcache_अणुall|range|pageपूर्ण
 *   ___invalidate_dcache_अणुall|range|pageपूर्ण
 *   ___invalidate_icache_अणुall|range|pageपूर्ण
 *
 */


	.macro	__loop_cache_unroll ar at insn size line_width max_immed

	.अगर	(1 << (\line_width)) > (\max_immed)
	.set	_reps, 1
	.अन्यथाअगर	(2 << (\line_width)) > (\max_immed)
	.set	_reps, 2
	.अन्यथा
	.set	_reps, 4
	.endअगर

	__loopi	\चr, \चt, \size, (_reps << (\line_width))
	.set	_index, 0
	.rep	_reps
	\insn	\चr, _index << (\line_width)
	.set	_index, _index + 1
	.endr
	__endla	\चr, \चt, _reps << (\line_width)

	.endm


	.macro	__loop_cache_all ar at insn size line_width max_immed

	movi	\चr, 0
	__loop_cache_unroll \चr, \चt, \insn, \size, \line_width, \max_immed

	.endm


	.macro	__loop_cache_range ar as at insn line_width

	extui	\चt, \चr, 0, \line_width
	add	\चs, \चs, \चt

	__loops	\चr, \चs, \चt, \line_width
	\insn	\चr, 0
	__endla	\चr, \चt, (1 << (\line_width))

	.endm


	.macro	__loop_cache_page ar at insn line_width max_immed

	__loop_cache_unroll \चr, \चt, \insn, PAGE_SIZE, \line_width, \max_immed

	.endm


	.macro	___unlock_dcache_all ar at

#अगर XCHAL_DCACHE_LINE_LOCKABLE && XCHAL_DCACHE_SIZE
	__loop_cache_all \चr \चt diu XCHAL_DCACHE_SIZE \
		XCHAL_DCACHE_LINEWIDTH 240
#पूर्ण_अगर

	.endm


	.macro	___unlock_icache_all ar at

#अगर XCHAL_ICACHE_LINE_LOCKABLE && XCHAL_ICACHE_SIZE
	__loop_cache_all \चr \चt iiu XCHAL_ICACHE_SIZE \
		XCHAL_ICACHE_LINEWIDTH 240
#पूर्ण_अगर

	.endm


	.macro	___flush_invalidate_dcache_all ar at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_all \चr \चt diwbi XCHAL_DCACHE_SIZE \
		XCHAL_DCACHE_LINEWIDTH 240
#पूर्ण_अगर

	.endm


	.macro	___flush_dcache_all ar at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_all \चr \चt diwb XCHAL_DCACHE_SIZE \
		XCHAL_DCACHE_LINEWIDTH 240
#पूर्ण_अगर

	.endm


	.macro	___invalidate_dcache_all ar at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_all \चr \चt dii XCHAL_DCACHE_SIZE \
			 XCHAL_DCACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm


	.macro	___invalidate_icache_all ar at

#अगर XCHAL_ICACHE_SIZE
	__loop_cache_all \चr \चt iii XCHAL_ICACHE_SIZE \
			 XCHAL_ICACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm



	.macro	___flush_invalidate_dcache_range ar as at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_range \चr \चs \चt dhwbi XCHAL_DCACHE_LINEWIDTH
#पूर्ण_अगर

	.endm


	.macro	___flush_dcache_range ar as at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_range \चr \चs \चt dhwb XCHAL_DCACHE_LINEWIDTH
#पूर्ण_अगर

	.endm


	.macro	___invalidate_dcache_range ar as at

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_range \चr \चs \चt dhi XCHAL_DCACHE_LINEWIDTH
#पूर्ण_अगर

	.endm


	.macro	___invalidate_icache_range ar as at

#अगर XCHAL_ICACHE_SIZE
	__loop_cache_range \चr \चs \चt ihi XCHAL_ICACHE_LINEWIDTH
#पूर्ण_अगर

	.endm



	.macro	___flush_invalidate_dcache_page ar as

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_page \चr \चs dhwbi XCHAL_DCACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm


	.macro ___flush_dcache_page ar as

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_page \चr \चs dhwb XCHAL_DCACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm


	.macro	___invalidate_dcache_page ar as

#अगर XCHAL_DCACHE_SIZE
	__loop_cache_page \चr \चs dhi XCHAL_DCACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm


	.macro	___invalidate_icache_page ar as

#अगर XCHAL_ICACHE_SIZE
	__loop_cache_page \चr \चs ihi XCHAL_ICACHE_LINEWIDTH 1020
#पूर्ण_अगर

	.endm

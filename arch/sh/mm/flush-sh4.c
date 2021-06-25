<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cache_insns.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>

/*
 * Write back the dirty D-caches, but not invalidate them.
 *
 * START: Virtual Address (U0, P1, or P3)
 * SIZE: Size of the region.
 */
अटल व्योम sh4__flush_wback_region(व्योम *start, पूर्णांक size)
अणु
	reg_माप_प्रकार aligned_start, v, cnt, end;

	aligned_start = रेजिस्टर_align(start);
	v = aligned_start & ~(L1_CACHE_BYTES-1);
	end = (aligned_start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	cnt = (end - v) / L1_CACHE_BYTES;

	जबतक (cnt >= 8) अणु
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		__ocbwb(v); v += L1_CACHE_BYTES;
		cnt -= 8;
	पूर्ण

	जबतक (cnt) अणु
		__ocbwb(v); v += L1_CACHE_BYTES;
		cnt--;
	पूर्ण
पूर्ण

/*
 * Write back the dirty D-caches and invalidate them.
 *
 * START: Virtual Address (U0, P1, or P3)
 * SIZE: Size of the region.
 */
अटल व्योम sh4__flush_purge_region(व्योम *start, पूर्णांक size)
अणु
	reg_माप_प्रकार aligned_start, v, cnt, end;

	aligned_start = रेजिस्टर_align(start);
	v = aligned_start & ~(L1_CACHE_BYTES-1);
	end = (aligned_start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	cnt = (end - v) / L1_CACHE_BYTES;

	जबतक (cnt >= 8) अणु
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		__ocbp(v); v += L1_CACHE_BYTES;
		cnt -= 8;
	पूर्ण
	जबतक (cnt) अणु
		__ocbp(v); v += L1_CACHE_BYTES;
		cnt--;
	पूर्ण
पूर्ण

/*
 * No ग_लिखो back please
 */
अटल व्योम sh4__flush_invalidate_region(व्योम *start, पूर्णांक size)
अणु
	reg_माप_प्रकार aligned_start, v, cnt, end;

	aligned_start = रेजिस्टर_align(start);
	v = aligned_start & ~(L1_CACHE_BYTES-1);
	end = (aligned_start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	cnt = (end - v) / L1_CACHE_BYTES;

	जबतक (cnt >= 8) अणु
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		__ocbi(v); v += L1_CACHE_BYTES;
		cnt -= 8;
	पूर्ण

	जबतक (cnt) अणु
		__ocbi(v); v += L1_CACHE_BYTES;
		cnt--;
	पूर्ण
पूर्ण

व्योम __init sh4__flush_region_init(व्योम)
अणु
	__flush_wback_region		= sh4__flush_wback_region;
	__flush_invalidate_region	= sh4__flush_invalidate_region;
	__flush_purge_region		= sh4__flush_purge_region;
पूर्ण

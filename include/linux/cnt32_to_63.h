<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Extend a 32-bit counter to 63 bits
 *
 *  Author:	Nicolas Pitre
 *  Created:	December 3, 2006
 *  Copyright:	MontaVista Software, Inc.
 */

#अगर_अघोषित __LINUX_CNT32_TO_63_H__
#घोषणा __LINUX_CNT32_TO_63_H__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/* this is used only to give gcc a clue about good code generation */
जोड़ cnt32_to_63 अणु
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN)
		u32 lo, hi;
#या_अगर defined(__BIG_ENDIAN)
		u32 hi, lo;
#पूर्ण_अगर
	पूर्ण;
	u64 val;
पूर्ण;


/**
 * cnt32_to_63 - Expand a 32-bit counter to a 63-bit counter
 * @cnt_lo: The low part of the counter
 *
 * Many hardware घड़ी counters are only 32 bits wide and thereक्रमe have
 * a relatively लघु period making wrap-arounds rather frequent.  This
 * is a problem when implementing sched_घड़ी() क्रम example, where a 64-bit
 * non-wrapping monotonic value is expected to be वापसed.
 *
 * To overcome that limitation, let's extend a 32-bit counter to 63 bits
 * in a completely lock मुक्त fashion. Bits 0 to 31 of the घड़ी are provided
 * by the hardware जबतक bits 32 to 62 are stored in memory.  The top bit in
 * memory is used to synchronize with the hardware घड़ी half-period.  When
 * the top bit of both counters (hardware and in memory) dअगरfer then the
 * memory is updated with a new value, incrementing it when the hardware
 * counter wraps around.
 *
 * Because a word store in memory is atomic then the incremented value will
 * always be in synch with the top bit indicating to any potential concurrent
 * पढ़ोer अगर the value in memory is up to date or not with regards to the
 * needed increment.  And any race in updating the value in memory is harmless
 * as the same value would simply be stored more than once.
 *
 * The restrictions क्रम the algorithm to work properly are:
 *
 * 1) this code must be called at least once per each half period of the
 *    32-bit counter;
 *
 * 2) this code must not be preempted क्रम a duration दीर्घer than the
 *    32-bit counter half period minus the दीर्घest period between two
 *    calls to this code;
 *
 * Those requirements ensure proper update to the state bit in memory.
 * This is usually not a problem in practice, but अगर it is then a kernel
 * समयr should be scheduled to manage क्रम this code to be executed often
 * enough.
 *
 * And finally:
 *
 * 3) the cnt_lo argument must be seen as a globally incrementing value,
 *    meaning that it should be a direct reference to the counter data which
 *    can be evaluated according to a specअगरic ordering within the macro,
 *    and not the result of a previous evaluation stored in a variable.
 *
 * For example, this is wrong:
 *
 *	u32 partial = get_hw_count();
 *	u64 full = cnt32_to_63(partial);
 *	वापस full;
 *
 * This is fine:
 *
 *	u64 full = cnt32_to_63(get_hw_count());
 *	वापस full;
 *
 * Note that the top bit (bit 63) in the वापसed value should be considered
 * as garbage.  It is not cleared here because callers are likely to use a
 * multiplier on the वापसed value which can get rid of the top bit
 * implicitly by making the multiplier even, thereक्रमe saving on a runसमय
 * clear-bit inकाष्ठाion. Otherwise caller must remember to clear the top
 * bit explicitly.
 */
#घोषणा cnt32_to_63(cnt_lo) \
(अणु \
	अटल u32 __m_cnt_hi; \
	जोड़ cnt32_to_63 __x; \
	__x.hi = __m_cnt_hi; \
 	smp_rmb(); \
	__x.lo = (cnt_lo); \
	अगर (unlikely((s32)(__x.hi ^ __x.lo) < 0)) \
		__m_cnt_hi = __x.hi = (__x.hi ^ 0x80000000) + (__x.hi >> 31); \
	__x.val; \
पूर्ण)

#पूर्ण_अगर

<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SYNC_BITOPS_H__
#घोषणा __ASM_SYNC_BITOPS_H__

#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/cmpxchg.h>

/* sync_bitops functions are equivalent to the SMP implementation of the
 * original functions, independently from CONFIG_SMP being defined.
 *
 * We need them because _set_bit etc are not SMP safe अगर !CONFIG_SMP. But
 * under Xen you might be communicating with a completely बाह्यal entity
 * who might be on another CPU (e.g. two uniprocessor guests communicating
 * via event channels and grant tables). So we need a variant of the bit
 * ops which are SMP safe even on a UP kernel.
 */

#घोषणा sync_set_bit(nr, p)			set_bit(nr, p)
#घोषणा sync_clear_bit(nr, p)			clear_bit(nr, p)
#घोषणा sync_change_bit(nr, p)			change_bit(nr, p)
#घोषणा sync_test_and_set_bit(nr, p)		test_and_set_bit(nr, p)
#घोषणा sync_test_and_clear_bit(nr, p)		test_and_clear_bit(nr, p)
#घोषणा sync_test_and_change_bit(nr, p)		test_and_change_bit(nr, p)
#घोषणा sync_test_bit(nr, addr)			test_bit(nr, addr)
#घोषणा arch_sync_cmpxchg			arch_cmpxchg

#पूर्ण_अगर

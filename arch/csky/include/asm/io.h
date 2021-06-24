<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_IO_H
#घोषणा __ASM_CSKY_IO_H

#समावेश <linux/pgtable.h>
#समावेश <linux/types.h>
#समावेश <linux/version.h>

/*
 * I/O memory access primitives. Reads are ordered relative to any
 * following Normal memory access. Writes are ordered relative to any prior
 * Normal memory access.
 *
 * For CACHEV1 (807, 810), store inकाष्ठाion could fast retire, so we need
 * another mb() to prevent st fast retire.
 *
 * For CACHEV2 (860), store inकाष्ठाion with PAGE_ATTR_NO_BUFFERABLE won't
 * fast retire.
 */
#घोषणा पढ़ोb(c)		(अणु u8  __v = पढ़ोb_relaxed(c); rmb(); __v; पूर्ण)
#घोषणा पढ़ोw(c)		(अणु u16 __v = पढ़ोw_relaxed(c); rmb(); __v; पूर्ण)
#घोषणा पढ़ोl(c)		(अणु u32 __v = पढ़ोl_relaxed(c); rmb(); __v; पूर्ण)

#अगर_घोषित CONFIG_CPU_HAS_CACHEV2
#घोषणा ग_लिखोb(v,c)		(अणु wmb(); ग_लिखोb_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोw(v,c)		(अणु wmb(); ग_लिखोw_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोl(v,c)		(अणु wmb(); ग_लिखोl_relaxed((v),(c)); पूर्ण)
#अन्यथा
#घोषणा ग_लिखोb(v,c)		(अणु wmb(); ग_लिखोb_relaxed((v),(c)); mb(); पूर्ण)
#घोषणा ग_लिखोw(v,c)		(अणु wmb(); ग_लिखोw_relaxed((v),(c)); mb(); पूर्ण)
#घोषणा ग_लिखोl(v,c)		(अणु wmb(); ग_लिखोl_relaxed((v),(c)); mb(); पूर्ण)
#पूर्ण_अगर

/*
 * I/O memory mapping functions.
 */
#घोषणा ioremap_wc(addr, size) \
	ioremap_prot((addr), (size), \
		(_PAGE_IOREMAP & ~_CACHE_MASK) | _CACHE_UNCACHED)

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* __ASM_CSKY_IO_H */

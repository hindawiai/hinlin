<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/compiler.h>
#अगर defined(__i386__) || defined(__x86_64__)
#समावेश "../../arch/x86/include/asm/barrier.h"
#या_अगर defined(__arm__)
#समावेश "../../arch/arm/include/asm/barrier.h"
#या_अगर defined(__aarch64__)
#समावेश "../../arch/arm64/include/asm/barrier.h"
#या_अगर defined(__घातerpc__)
#समावेश "../../arch/powerpc/include/asm/barrier.h"
#या_अगर defined(__s390__)
#समावेश "../../arch/s390/include/asm/barrier.h"
#या_अगर defined(__sh__)
#समावेश "../../arch/sh/include/asm/barrier.h"
#या_अगर defined(__sparc__)
#समावेश "../../arch/sparc/include/asm/barrier.h"
#या_अगर defined(__tile__)
#समावेश "../../arch/tile/include/asm/barrier.h"
#या_अगर defined(__alpha__)
#समावेश "../../arch/alpha/include/asm/barrier.h"
#या_अगर defined(__mips__)
#समावेश "../../arch/mips/include/asm/barrier.h"
#या_अगर defined(__ia64__)
#समावेश "../../arch/ia64/include/asm/barrier.h"
#या_अगर defined(__xtensa__)
#समावेश "../../arch/xtensa/include/asm/barrier.h"
#या_अगर defined(__nds32__)
#समावेश "../../arch/nds32/include/asm/barrier.h"
#अन्यथा
#समावेश <यंत्र-generic/barrier.h>
#पूर्ण_अगर

/*
 * Generic fallback smp_*() definitions क्रम archs that haven't
 * been updated yet.
 */

#अगर_अघोषित smp_rmb
# define smp_rmb()	rmb()
#पूर्ण_अगर

#अगर_अघोषित smp_wmb
# define smp_wmb()	wmb()
#पूर्ण_अगर

#अगर_अघोषित smp_mb
# define smp_mb()	mb()
#पूर्ण_अगर

#अगर_अघोषित smp_store_release
# define smp_store_release(p, v)		\
करो अणु						\
	smp_mb();				\
	WRITE_ONCE(*p, v);			\
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित smp_load_acquire
# define smp_load_acquire(p)			\
(अणु						\
	typeof(*p) ___p1 = READ_ONCE(*p);	\
	smp_mb();				\
	___p1;					\
पूर्ण)
#पूर्ण_अगर

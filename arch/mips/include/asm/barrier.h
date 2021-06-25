<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006 by Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/sync.h>

अटल अंतरभूत व्योम __sync(व्योम)
अणु
	यंत्र अस्थिर(__SYNC(full, always) ::: "memory");
पूर्ण

अटल अंतरभूत व्योम rmb(व्योम)
अणु
	यंत्र अस्थिर(__SYNC(rmb, always) ::: "memory");
पूर्ण
#घोषणा rmb rmb

अटल अंतरभूत व्योम wmb(व्योम)
अणु
	यंत्र अस्थिर(__SYNC(wmb, always) ::: "memory");
पूर्ण
#घोषणा wmb wmb

#घोषणा fast_mb()	__sync()

#घोषणा __fast_iob()				\
	__यंत्र__ __अस्थिर__(			\
		".set	push\n\t"		\
		".set	noreorder\n\t"		\
		"lw	$0,%0\n\t"		\
		"nop\n\t"			\
		".set	pop"			\
		: /* no output */		\
		: "m" (*(पूर्णांक *)CKSEG1)		\
		: "memory")
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
# define fast_iob()	करो अणु पूर्ण जबतक (0)
#अन्यथा /* ! CONFIG_CPU_CAVIUM_OCTEON */
# अगरdef CONFIG_SGI_IP28
#  define fast_iob()				\
	__यंत्र__ __अस्थिर__(			\
		".set	push\n\t"		\
		".set	noreorder\n\t"		\
		"lw	$0,%0\n\t"		\
		"sync\n\t"			\
		"lw	$0,%0\n\t"		\
		".set	pop"			\
		: /* no output */		\
		: "m" (*(पूर्णांक *)CKSEG1ADDR(0x1fa00004)) \
		: "memory")
# अन्यथा
#  define fast_iob()				\
	करो अणु					\
		__sync();			\
		__fast_iob();			\
	पूर्ण जबतक (0)
# endअगर
#पूर्ण_अगर /* CONFIG_CPU_CAVIUM_OCTEON */

#अगर_घोषित CONFIG_CPU_HAS_WB

#समावेश <यंत्र/wbflush.h>

#घोषणा mb()		wbflush()
#घोषणा iob()		wbflush()

#अन्यथा /* !CONFIG_CPU_HAS_WB */

#घोषणा mb()		fast_mb()
#घोषणा iob()		fast_iob()

#पूर्ण_अगर /* !CONFIG_CPU_HAS_WB */

#अगर defined(CONFIG_WEAK_ORDERING)
# define __smp_mb()	__sync()
# define __smp_rmb()	rmb()
# define __smp_wmb()	wmb()
#अन्यथा
# define __smp_mb()	barrier()
# define __smp_rmb()	barrier()
# define __smp_wmb()	barrier()
#पूर्ण_अगर

/*
 * When LL/SC करोes imply order, it must also be a compiler barrier to aव्योम the
 * compiler from reordering where the CPU will not. When it करोes not imply
 * order, the compiler is also मुक्त to reorder across the LL/SC loop and
 * ordering will be करोne by smp_llsc_mb() and मित्रs.
 */
#अगर defined(CONFIG_WEAK_REORDERING_BEYOND_LLSC) && defined(CONFIG_SMP)
# define __WEAK_LLSC_MB		sync
# define smp_llsc_mb() \
	__यंत्र__ __अस्थिर__(__stringअगरy(__WEAK_LLSC_MB) : : :"memory")
# define __LLSC_CLOBBER
#अन्यथा
# define __WEAK_LLSC_MB
# define smp_llsc_mb()		करो अणु पूर्ण जबतक (0)
# define __LLSC_CLOBBER		"memory"
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
#घोषणा smp_mb__beक्रमe_llsc() smp_wmb()
#घोषणा __smp_mb__beक्रमe_llsc() __smp_wmb()
/* Cause previous ग_लिखोs to become visible on all CPUs as soon as possible */
#घोषणा nudge_ग_लिखोs() __यंत्र__ __अस्थिर__(".set push\n\t"		\
					    ".set arch=octeon\n\t"	\
					    "syncw\n\t"			\
					    ".set pop" : : : "memory")
#अन्यथा
#घोषणा smp_mb__beक्रमe_llsc() smp_llsc_mb()
#घोषणा __smp_mb__beक्रमe_llsc() smp_llsc_mb()
#घोषणा nudge_ग_लिखोs() mb()
#पूर्ण_अगर

/*
 * In the Loongson3 LL/SC workaround हाल, all of our LL/SC loops alपढ़ोy have
 * a completion barrier immediately preceding the LL inकाष्ठाion. Thereक्रमe we
 * can skip emitting a barrier from __smp_mb__beक्रमe_atomic().
 */
#अगर_घोषित CONFIG_CPU_LOONGSON3_WORKAROUNDS
# define __smp_mb__beक्रमe_atomic()
#अन्यथा
# define __smp_mb__beक्रमe_atomic()	__smp_mb__beक्रमe_llsc()
#पूर्ण_अगर

#घोषणा __smp_mb__after_atomic()	smp_llsc_mb()

अटल अंतरभूत व्योम sync_ginv(व्योम)
अणु
	यंत्र अस्थिर(__SYNC(ginv, always));
पूर्ण

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* __ASM_BARRIER_H */

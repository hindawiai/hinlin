<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_CMPXCHG_H
#घोषणा __ASM_ARC_CMPXCHG_H

#समावेश <linux/types.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/smp.h>

#अगर_घोषित CONFIG_ARC_HAS_LLSC

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ expected, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	/*
	 * Explicit full memory barrier needed beक्रमe/after as
	 * LLOCK/SCOND themselves करोn't provide any such semantics
	 */
	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	llock   %0, [%1]	\n"
	"	brne    %0, %2, 2f	\n"
	"	scond   %3, [%1]	\n"
	"	bnz     1b		\n"
	"2:				\n"
	: "=&r"(prev)	/* Early clobber, to prevent reg reuse */
	: "r"(ptr),	/* Not "m": llock only supports reg direct addr mode */
	  "ir"(expected),
	  "r"(new)	/* can't be "ir". scond can't take LIMM क्रम "b" */
	: "cc", "memory"); /* so that gcc knows memory is being written here */

	smp_mb();

	वापस prev;
पूर्ण

#अन्यथा /* !CONFIG_ARC_HAS_LLSC */

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ expected, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक prev;
	अस्थिर अचिन्हित दीर्घ *p = ptr;

	/*
	 * spin lock/unlock provide the needed smp_mb() beक्रमe/after
	 */
	atomic_ops_lock(flags);
	prev = *p;
	अगर (prev == expected)
		*p = new;
	atomic_ops_unlock(flags);
	वापस prev;
पूर्ण

#पूर्ण_अगर

#घोषणा cmpxchg(ptr, o, n) (अणु				\
	(typeof(*(ptr)))__cmpxchg((ptr),		\
				  (अचिन्हित दीर्घ)(o),	\
				  (अचिन्हित दीर्घ)(n));	\
पूर्ण)

/*
 * atomic_cmpxchg is same as cmpxchg
 *   LLSC: only dअगरferent in data-type, semantics are exactly same
 *  !LLSC: cmpxchg() has to use an बाह्यal lock atomic_ops_lock to guarantee
 *         semantics, and this lock also happens to be used by atomic_*()
 */
#घोषणा atomic_cmpxchg(v, o, n) ((पूर्णांक)cmpxchg(&((v)->counter), (o), (n)))


/*
 * xchg (reg with memory) based on "Native atomic" EX insn
 */
अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ val, अस्थिर व्योम *ptr,
				   पूर्णांक size)
अणु
	बाह्य अचिन्हित दीर्घ __xchg_bad_poपूर्णांकer(व्योम);

	चयन (size) अणु
	हाल 4:
		smp_mb();

		__यंत्र__ __अस्थिर__(
		"	ex  %0, [%1]	\n"
		: "+r"(val)
		: "r"(ptr)
		: "memory");

		smp_mb();

		वापस val;
	पूर्ण
	वापस __xchg_bad_poपूर्णांकer();
पूर्ण

#घोषणा _xchg(ptr, with) ((typeof(*(ptr)))__xchg((अचिन्हित दीर्घ)(with), (ptr), \
						 माप(*(ptr))))

/*
 * xchg() maps directly to ARC EX inकाष्ठाion which guarantees atomicity.
 * However in !LLSC config, it also needs to be use @atomic_ops_lock spinlock
 * due to a subtle reason:
 *  - For !LLSC, cmpxchg() needs to use that lock (see above) and there is lot
 *    of  kernel code which calls xchg()/cmpxchg() on same data (see llist.h)
 *    Hence xchg() needs to follow same locking rules.
 *
 * Technically the lock is also needed क्रम UP (boils करोwn to irq save/restore)
 * but we can cheat a bit since cmpxchg() atomic_ops_lock() would cause irqs to
 * be disabled thus can't possibly be पूर्णांकerrupted/preempted/clobbered by xchg()
 * Other way around, xchg is one inकाष्ठाion anyways, so can't be पूर्णांकerrupted
 * as such
 */

#अगर !defined(CONFIG_ARC_HAS_LLSC) && defined(CONFIG_SMP)

#घोषणा xchg(ptr, with)			\
(अणु					\
	अचिन्हित दीर्घ flags;		\
	typeof(*(ptr)) old_val;		\
					\
	atomic_ops_lock(flags);		\
	old_val = _xchg(ptr, with);	\
	atomic_ops_unlock(flags);	\
	old_val;			\
पूर्ण)

#अन्यथा

#घोषणा xchg(ptr, with)  _xchg(ptr, with)

#पूर्ण_अगर

/*
 * "atomic" variant of xchg()
 * REQ: It needs to follow the same serialization rules as other atomic_xxx()
 * Since xchg() करोesn't always करो that, it would seem that following definition
 * is incorrect. But here's the rationale:
 *   SMP : Even xchg() takes the atomic_ops_lock, so OK.
 *   LLSC: atomic_ops_lock are not relevant at all (even अगर SMP, since LLSC
 *         is natively "SMP safe", no serialization required).
 *   UP  : other atomics disable IRQ, so no way a dअगरft ctxt atomic_xchg()
 *         could clobber them. atomic_xchg() itself would be 1 insn, so it
 *         can't be clobbered by others. Thus no serialization required when
 *         atomic_xchg is involved.
 */
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#पूर्ण_अगर

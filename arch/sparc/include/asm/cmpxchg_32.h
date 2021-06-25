<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 32-bit atomic xchg() and cmpxchg() definitions.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 2000 Anton Blanअक्षरd (anton@linuxcare.com.au)
 * Copyright (C) 2007 Kyle McMartin (kyle@parisc-linux.org)
 *
 * Additions by Keith M Wesolowski (wesolows@foobazco.org) based
 * on यंत्र-parisc/atomic.h Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>.
 */

#अगर_अघोषित __ARCH_SPARC_CMPXCHG__
#घोषणा __ARCH_SPARC_CMPXCHG__

अचिन्हित दीर्घ __xchg_u32(अस्थिर u32 *m, u32 new);
व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ __xchg(अचिन्हित दीर्घ x, __अस्थिर__ व्योम * ptr, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:
		वापस __xchg_u32(ptr, x);
	पूर्ण
	__xchg_called_with_bad_poपूर्णांकer();
	वापस x;
पूर्ण

#घोषणा xchg(ptr,x) (अणु(__typeof__(*(ptr)))__xchg((अचिन्हित दीर्घ)(x),(ptr),माप(*(ptr)));पूर्ण)

/* Emulate cmpxchg() the same way we emulate atomics,
 * by hashing the object address and indexing पूर्णांकo an array
 * of spinlocks to get a bit of perक्रमmance...
 *
 * See arch/sparc/lib/atomic32.c क्रम implementation.
 *
 * Cribbed from <यंत्र-parisc/atomic.h>
 */

/* bug catcher क्रम when unsupported size is used - won't link */
व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);
/* we only need to support cmpxchg of a u32 on sparc */
अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर u32 *m, u32 old, u32 new_);

/* करोn't worry...optimizer will get rid of most of this */
अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new_, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:
		वापस __cmpxchg_u32((u32 *)ptr, (u32)old, (u32)new_);
	शेष:
		__cmpxchg_called_with_bad_poपूर्णांकer();
		अवरोध;
	पूर्ण
	वापस old;
पूर्ण

#घोषणा cmpxchg(ptr, o, n)						\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,	\
			(अचिन्हित दीर्घ)_n_, माप(*(ptr)));		\
पूर्ण)

u64 __cmpxchg_u64(u64 *ptr, u64 old, u64 new);
#घोषणा cmpxchg64(ptr, old, new)	__cmpxchg_u64(ptr, old, new)

#समावेश <यंत्र-generic/cmpxchg-local.h>

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#घोषणा cmpxchg_local(ptr, o, n)				  	       \
	((__typeof__(*(ptr)))__cmpxchg_local_generic((ptr), (अचिन्हित दीर्घ)(o),\
			(अचिन्हित दीर्घ)(n), माप(*(ptr))))
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))

#पूर्ण_अगर /* __ARCH_SPARC_CMPXCHG__ */

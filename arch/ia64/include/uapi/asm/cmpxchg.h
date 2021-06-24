<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_CMPXCHG_H
#घोषणा _ASM_IA64_CMPXCHG_H

/*
 * Compare/Exchange, विभाजनed from यंत्र/पूर्णांकrinsics.h
 * which was:
 *
 *	Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
/* include compiler specअगरic पूर्णांकrinsics */
#समावेश <यंत्र/ia64regs.h>
#अगर_घोषित __INTEL_COMPILER
# include <यंत्र/पूर्णांकel_पूर्णांकrin.h>
#अन्यथा
# include <यंत्र/gcc_पूर्णांकrin.h>
#पूर्ण_अगर

/*
 * This function करोesn't exist, so you'll get a linker error अगर
 * something tries to करो an invalid xchg().
 */
बाह्य व्योम ia64_xchg_called_with_bad_poपूर्णांकer(व्योम);

#घोषणा __xchg(x, ptr, size)						\
(अणु									\
	अचिन्हित दीर्घ __xchg_result;					\
									\
	चयन (size) अणु							\
	हाल 1:								\
		__xchg_result = ia64_xchg1((__u8 *)ptr, x);		\
		अवरोध;							\
									\
	हाल 2:								\
		__xchg_result = ia64_xchg2((__u16 *)ptr, x);		\
		अवरोध;							\
									\
	हाल 4:								\
		__xchg_result = ia64_xchg4((__u32 *)ptr, x);		\
		अवरोध;							\
									\
	हाल 8:								\
		__xchg_result = ia64_xchg8((__u64 *)ptr, x);		\
		अवरोध;							\
	शेष:							\
		ia64_xchg_called_with_bad_poपूर्णांकer();			\
	पूर्ण								\
	__xchg_result;							\
पूर्ण)

#घोषणा xchg(ptr, x)							\
(अणु(__typeof__(*(ptr))) __xchg((अचिन्हित दीर्घ) (x), (ptr), माप(*(ptr)));पूर्ण)

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */

/*
 * This function करोesn't exist, so you'll get a linker error
 * अगर something tries to करो an invalid cmpxchg().
 */
बाह्य दीर्घ ia64_cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

#घोषणा ia64_cmpxchg(sem, ptr, old, new, size)				\
(अणु									\
	__u64 _o_, _r_;							\
									\
	चयन (size) अणु							\
	हाल 1:								\
		_o_ = (__u8) (दीर्घ) (old);				\
		अवरोध;							\
	हाल 2:								\
		_o_ = (__u16) (दीर्घ) (old);				\
		अवरोध;							\
	हाल 4:								\
		_o_ = (__u32) (दीर्घ) (old);				\
		अवरोध;							\
	हाल 8:								\
		_o_ = (__u64) (दीर्घ) (old);				\
		अवरोध;							\
	शेष:							\
		अवरोध;							\
	पूर्ण								\
	चयन (size) अणु							\
	हाल 1:								\
		_r_ = ia64_cmpxchg1_##sem((__u8 *) ptr, new, _o_);	\
		अवरोध;							\
									\
	हाल 2:								\
		_r_ = ia64_cmpxchg2_##sem((__u16 *) ptr, new, _o_);	\
		अवरोध;							\
									\
	हाल 4:								\
		_r_ = ia64_cmpxchg4_##sem((__u32 *) ptr, new, _o_);	\
		अवरोध;							\
									\
	हाल 8:								\
		_r_ = ia64_cmpxchg8_##sem((__u64 *) ptr, new, _o_);	\
		अवरोध;							\
									\
	शेष:							\
		_r_ = ia64_cmpxchg_called_with_bad_poपूर्णांकer();		\
		अवरोध;							\
	पूर्ण								\
	(__typeof__(old)) _r_;						\
पूर्ण)

#घोषणा cmpxchg_acq(ptr, o, n)	\
	ia64_cmpxchg(acq, (ptr), (o), (n), माप(*(ptr)))
#घोषणा cmpxchg_rel(ptr, o, n)	\
	ia64_cmpxchg(rel, (ptr), (o), (n), माप(*(ptr)))

/*
 * Worse still - early processor implementations actually just ignored
 * the acquire/release and did a full fence all the समय.  Unक्रमtunately
 * this meant a lot of badly written code that used .acq when they really
 * wanted .rel became legacy out in the wild - so when we made a cpu
 * that strictly did the .acq or .rel ... all that code started अवरोधing - so
 * we had to back-pedal and keep the "legacy" behavior of a full fence :-(
 */

/* क्रम compatibility with other platक्रमms: */
#घोषणा cmpxchg(ptr, o, n)	cmpxchg_acq((ptr), (o), (n))
#घोषणा cmpxchg64(ptr, o, n)	cmpxchg_acq((ptr), (o), (n))

#घोषणा cmpxchg_local		cmpxchg
#घोषणा cmpxchg64_local		cmpxchg64

#अगर_घोषित CONFIG_IA64_DEBUG_CMPXCHG
# define CMPXCHG_BUGCHECK_DECL	पूर्णांक _cmpxchg_bugcheck_count = 128;
# define CMPXCHG_BUGCHECK(v)						\
करो अणु									\
	अगर (_cmpxchg_bugcheck_count-- <= 0) अणु				\
		व्योम *ip;						\
		बाह्य पूर्णांक prपूर्णांकk(स्थिर अक्षर *fmt, ...);		\
		ip = (व्योम *) ia64_getreg(_IA64_REG_IP);		\
		prपूर्णांकk("CMPXCHG_BUGCHECK: stuck at %p on word %p\n", ip, (v));\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)
#अन्यथा /* !CONFIG_IA64_DEBUG_CMPXCHG */
# define CMPXCHG_BUGCHECK_DECL
# define CMPXCHG_BUGCHECK(v)
#पूर्ण_अगर /* !CONFIG_IA64_DEBUG_CMPXCHG */

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_CMPXCHG_H */
